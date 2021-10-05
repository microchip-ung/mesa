// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "cli.h"
#include "trace.h"
#include "ipc.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "cli"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

#define MAX_CMD_LEN  (500 + 1)
#define MAX_WORD_LEN 64

static mesa_bool_t cli_exit;
static mesa_bool_t cli_mgmt_port_include;
static uint32_t cli_port_cnt;

/****************************************************************************/
/*  Command parsing                                                         */
/****************************************************************************/

const char *cli_bool_txt(mesa_bool_t enabled)
{
    return (enabled ? "Enabled " : "Disabled");
}

/* Convert from internal to user port number */
mesa_port_no_t iport2uport(mesa_port_no_t iport)
{
    return (iport + 1);
}

/* Convert from user to internal port number */
mesa_port_no_t uport2iport(mesa_port_no_t uport)
{
    return (uport == 0 ? MESA_PORT_NO_NONE : (uport - 1));
}

static cli_cmd_t *cli_cmd_list;

static void cli_cmd_help(cli_req_t *req)
{
    cli_printf("Type '<group> ?' to get list of group commands, e.g. 'port ?'.\n");
    cli_printf("Type '<command> ?' to get help on a command, e.g. 'port mode ?'.\n");
    cli_printf("Commands may be abbreviated, e.g. 'po mo' instead of 'port mode'.\n");
}

static void cli_cmd_exit(cli_req_t *req)
{
    cli_exit = 1;
}

static void cli_cmd_debug_mgmt(cli_req_t *req)
{
    if (req->set) {
        cli_mgmt_port_include = req->enable;
    } else {
        cli_printf("Management port is %scluded from port list\n", cli_mgmt_port_include ? "in" : "ex");
    }
}

mesa_bool_t cli_port_list_member(mesa_port_list_t *port_list, mesa_port_no_t iport)
{
    return (iport < cli_port_cnt && (port_list->_private[iport / 8] & (1 << (iport % 8))) != 0);
}

char *cli_port_list_txt(mesa_port_list_t *port_list, char *buf)
{
    char           *p = buf;
    mesa_port_no_t iport, port;
    int            first = 1, count = 0;
    mesa_bool_t    member;

    *p = '\0';
    for (iport = 0; iport < cli_port_cnt; iport++) {
        member = cli_port_list_member(port_list, iport);
        if ((member && 
             (count == 0 || iport == (cli_port_cnt - 1))) || (!member && count > 1)) {
            port = iport2uport(iport);
            p += sprintf(p, "%s%u",
                         first ? "" : count > (member ? 1 : 2) ? "-" : ",",
                         member ? port : (port - 1));
            first = 0;
        }
        if (member)
            count++;
        else
            count=0;
    }
    if (p == buf)
        sprintf(p, "None");
    return buf;
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Help",
        "Show CLI general help text",
        cli_cmd_help
    },
    {
        "Exit",
        "Exit this application",
        cli_cmd_exit
    },
    {
        "Debug Management [include|exclude]",
        "Include or exclude IP management port from commands",
        cli_cmd_debug_mgmt
    },
}; /* cli_cmd_table */

static cli_parm_t *cli_parm_list;

const char *cli_parse_find(const char *cmd, const char *stx)
{
    const char *p, *found = NULL;
    mesa_bool_t parm = 0, start = 1;

    for (p = stx; *p != '\0'; p++) {
        if (parm) {
            /* Look for parameter end character */
            if (*p == '>')
                parm = 0;
        } else if (*p == '<') {
            /* Parameter start character */
            parm = 1;
        } else if (*p == '|' || *p == '[' || *p == '(') {
            /* Next argument character */
            start = 1;
        } else if (start) {
            start = 0;
            if (strstr(p, cmd) == p && found == NULL)
                // First occurence is used
                found = p;
        }
    }
    return found;
}

int cli_parm_u32(cli_req_t *req, uint32_t *val, uint32_t min, uint32_t max)
{
    uint32_t  n;
    char *end;

    n = strtoul(req->cmd, &end, 0);
    if (*end != '\0' || n < min || n > max)
        return 1;

    *val = n;
    return 0;
}

int cli_parm_u16(cli_req_t *req, uint16_t *val, uint32_t min, uint32_t max)
{
    uint32_t value;
    int error;

    error = cli_parm_u32(req, &value, min, max);
    if (!error)
        *val = value;
    return error;
}

int cli_parm_u8(cli_req_t *req, uint8_t *val, uint32_t min, uint32_t max)
{
    uint32_t value;
    int error;

    error = cli_parm_u32(req, &value, min, max);
    if (!error)
        *val = value;
    return error;
}

int cli_parm_port_no(cli_req_t *req)
{
    uint32_t value;
    int error;

    // NB: Port 0 == "PORT_NONE"
    error = cli_parm_u32(req, &value, 0, mesa_port_cnt(NULL));
    if (!error) {
        req->port_no = uport2iport(value);
    }
    return error;
}

/* Convert text to list */
int cli_parse_list(const char *buf, mesa_bool_t *list, uint32_t min, uint32_t max, mesa_bool_t def)
{
    uint32_t   i, start = 0, n;
    const char *p, *end;
    mesa_bool_t  error, range = 0, comma = 0;
    
    /* Clear list by default */
    for (i = min; i <= max; i++)
        list[i] = 0;

    p = buf;
    error = (p == NULL);
    while (p != NULL && *p != '\0') {
        /* Read integer */
        n = strtoul(p, (char **)&end, 0);
        if (end == p) {
            error = 1;
            break;
        }
        p = end;
        
        /* Check legal range */
        if (n < min || n > max) {
            error = 1;
            break;
        }
        
        if (range) {
            /* End of range has been read */
            if (n < start) {
                error = 1;
                break;
            }
            for (i = start ; i <= n; i++)
                list[i] = 1;
            range = 0;
        } else if (*p == '-') {
            /* Start of range has been read */
            start = n;
            range = 1;
            p++;
        } else {
            /* Single value has been read */
            list[n] = 1;
        }
        comma = 0;
        if (!range && *p == ',') {
            comma = 1;
            p++;
        }
    }
    
    /* Check for trailing comma/dash */
    if (comma || range)
        error = 1;
    
    /* Restore defaults if error */
    for (i = min; error && i <= max; i++)
        list[i] = def;

    return error;
}
/* Convert text to array of u32 */
int cli_parse_values(const char *buf, uint32_t *arr, uint32_t *val_cnt, uint32_t min, uint32_t max, uint32_t max_num)
{
    uint32_t n, cnt = 0;
    const char *p, *end;
    mesa_bool_t  error, range = 0, comma = 0;

    p = buf;
    error = (p == NULL);
    while (p != NULL && *p != '\0') {

        /* Read integer */
        n = strtoul(p, (char **)&end, 0);
        if (end == p) {
            error = 1;
            break;
        }
        p = end;

        /* Check legal range */
        if (n < min || n > max) {
            error = 1;
            break;
        }
        /* Single value has been read */
        arr[cnt] = n;
        comma = 0;
        if (!range && *p == ',') {
            comma = 1;
            p++;
        }
        cnt++;
        if (cnt > max_num) {
            break;
        }
    }

    /* Check for trailing comma/dash */
    if (comma || range)
        error = 1;

    if (!error)
        *val_cnt = cnt;
    return error;
}

/* Remove unused ports from the list */
static void cli_remove_unused_ports(cli_req_t *req) 
{
    mesa_port_no_t iport;
    uint32_t       port_cnt = mesa_port_cnt(NULL);
    
    for (iport = cli_port_cnt; iport < port_cnt; iport++) {
        req->port_list[iport2uport(iport)] = 0;
    }

    // Exclude IP management port, if valid
    if (!cli_mgmt_port_include && (req->cmd_flags & CLI_CMD_FLAG_ALL_PORTS) == 0 && ip_port < port_cnt) {
        req->port_list[iport2uport(ip_port)] = 0;
    }
}

static int cli_parm_port_list(cli_req_t *req)
{
    int error;
    
    error = cli_parse_list(req->cmd, req->port_list, 1, mesa_port_cnt(NULL), 1);
    cli_remove_unused_ports(req);
    return error;
}

static int cli_parm_keyword(cli_req_t *req)
{
    const char *found;
    
    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;
   
    if (!strncmp(found, "disable", 7))
        req->disable = 1;
    else if (!strncmp(found, "exclude", 7))
        req->enable = 0;
    else if (!strncmp(found, "enable", 6))
        req->enable = 1;
    else if (!strncmp(found, "include", 7))
        req->enable = 1;
    else
        cli_printf("no match:%s\n",found);
    
    return 0;
}

static int cli_parm_vid(cli_req_t *req)
{
    return cli_parm_u16(req, &req->vid, MESA_VID_DEFAULT, MESA_VID_RESERVED);
}

static cli_parm_t cli_parm_table[] = {
    {
        "<port_no>",
        "Port number or zero",
        CLI_PARM_FLAG_SET,
        cli_parm_port_no
    },
    {
        "<port_list>",
        "Port list, default: All ports",
        CLI_PARM_FLAG_NONE,
        cli_parm_port_list
    },
    {
        "enable|disable",
        "enable     : Enable\n"
        "disable    : Disable\n"
        "(default: Show mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "include|exclude",
        "include : Include management port\n"
        "exclude : Exclude management port\n"
        "(default: Show mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "<vid>",
        "VLAN ID",
        CLI_PARM_FLAG_SET,
        cli_parm_vid
    },
};  /* cli_parm_table */

static cli_req_t cli_req;

/* Register CLI command */
void mscc_appl_cli_cmd_reg(cli_cmd_t *cmd)
{
    cli_cmd_t *cur, *prev = NULL;
    mesa_bool_t      cur_debug, cmd_debug;

    if (!cmd->func && !cmd->func2) {
        cli_printf("Missing command function: %s\n", cmd->syntax);
        return;
    }

    cmd_debug = (strstr(cmd->syntax, "Debug") == cmd->syntax ? 1 : 0);
    for (cur = cli_cmd_list; cur != NULL; prev = cur, cur = cur->next) {
        /* The Help/Exit commands always first */
        if (strstr(cur->syntax, "Help") == cur->syntax || strstr(cur->syntax, "Exit") == cur->syntax)
            continue;
        
        /* Debug commands are at the end */
        cur_debug = (strstr(cur->syntax, "Debug") == cur->syntax ? 1 : 0);
        if (cur_debug == cmd_debug) {
            /* Alphabetic sorting within 'debug' and 'non-debug' blocks */
            if (strcmp(cur->syntax, cmd->syntax) > 0)
                break;
        } else if (cur_debug) {
            /* Insert non-debug command before debug commands */
            break;
        }
    }
    if (prev == NULL) {
        cmd->next = cli_cmd_list;
        cli_cmd_list = cmd;
    } else {
        cmd->next = prev->next;
        prev->next = cmd;
    }
}

/* Register CLI parameter */
void mscc_appl_cli_parm_reg(cli_parm_t *parm)
{
    if (parm->parse_func == NULL) {
        cli_printf("Missing parser function: %s\n", parm->txt);
    } else {
        /* Insert first in list */
        parm->next = cli_parm_list;
        cli_parm_list = parm;
    }
}

static cli_parm_t *cli_parm_lookup(char *stx, cli_cmd_t *cmd)
{
    cli_parm_t *parm, *found = NULL;
    char stx_buf[MAX_WORD_LEN], *stx_start, *stx_end;

    strcpy(stx_buf, stx);
    stx_start = stx_buf;
    /* Remove the brackets/paranthesis from the beginning and end of syntax */
    while ((*stx_start == '(') || (*stx_start == '['))
        stx_start++;
    if ((stx_end = strchr(stx_start, ')')) != NULL)
        *stx_end = '\0';
    if ((stx_end = strchr(stx_start, ']')) != NULL)
        *stx_end = '\0';

    for (parm = cli_parm_list; parm != NULL; parm = parm->next) {
        if (strcmp(stx_start, parm->txt) == 0) {
            if (parm->cmd_func == NULL) {
                /* Default match found */
                found = parm;
            } else if (parm->cmd_func == cmd->func) {
                /* Specific match found */
                return parm;
            }
        }
    }
    return found;
}

static void cli_req_default_set(cli_req_t *req, cli_cmd_t *cmd)
{
    meba_inst_t inst = req->inst; // Preserve MEBA instance

    memset(req, 0, sizeof(*req));
    req->inst = inst;
    req->cmd_flags = cmd->flags;
    cli_parse_list(NULL, req->port_list, 0, mesa_port_cnt(NULL), 1);
    cli_remove_unused_ports(req);
    req->vid = MESA_VID_DEFAULT;
#if defined(MESA_GPIOS)
    cli_parse_list(NULL, req->gpio_list, 0, MESA_GPIO_NO_END - 1, 1);
#endif /* MESA_GPIOS */
    req->module_req = &req->module_data;
}

/* Header with optional new line before and after */
static void cli_header_nl_char(const char *txt, mesa_bool_t pre, mesa_bool_t post, char c)
{
    int i, len;
    
    if (pre)
        cli_printf("\n");
    cli_printf("%s:\n", txt);
    len = (strlen(txt) + 1);
    for (i = 0; i < len; i++)
        cli_printf("%c", c);
    cli_printf("\n");
    if (post)
        cli_printf("\n");
}

/* Underlined header with optional new line before and after */
static void cli_header_nl(const char *txt, mesa_bool_t pre, mesa_bool_t post)
{
    cli_header_nl_char(txt, pre, post, '-');
}

void cli_table_header(const char *txt)
{
    int i, j, len, count = 0;

    len = strlen(txt);
    for (i = 0; i < len; i++)
        cli_printf("%c", txt[i] == '*' ? ' ' : txt[i]);
    cli_printf("\n");
    
    while (*txt == ' ') {
        cli_printf(" ");
        txt++;
    }
    for (i = 0; i < len; i++) {
        if (txt[i] == ' ') {
            count++;
        } else {
            for (j = 0; j < count; j++)
                cli_printf("%c", count > 1 && (j >= (count - 2)) ? ' ' : '-');
            cli_printf("-");
            count = 0;
        }
    }
    for (j = 0; j < count; j++)
        cli_printf("%c", count > 1 && (j >= (count - 2)) ? ' ' : '-');
    cli_printf("\n");
}

char *cli_mac_txt(const uint8_t *mac, char *buf)
{
    sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buf;
}

/* Build array of command/syntax words */
static void cli_build_words(char *str, int *count, char **words, mesa_bool_t lower)
{
    int  i, j, len;
    char *p;
    
    len = strlen(str);
    j = 0;
    *count = 0;
    for (i = 0; i < len; i++) {
        p = &str[i];
        if (isspace(*p)) {
            j = 0;
            *p = '\0';
        } else {
            if (j == 0) {
                words[*count] = p;
                (*count)++;
            }
            if (lower)
                *p = tolower(*p);
            j++;
        }
    }
}

/* Parse command */
static int cli_parse_command(int argc, const char **argv)
{
    char        *stx;
    char        stx_buf[MAX_CMD_LEN], *stx_words[64];
    int         i = 0, i_cmd = 0, i_stx, i_parm = 0, stx_count, max, len, j, error;
    cli_cmd_t   *cli_cmd, *match_list = NULL, *match_prev = NULL;
    mesa_bool_t match, help = 0;
    cli_req_t   *req;
    cli_parm_t  *parm;

    /* Remove trailing 'help' or '?' command */
    if (argc > 1) {
        if (strcmp(argv[argc - 1], "?") == 0 ||
            strcasecmp(argv[argc - 1], "help") == 0) {
            argc--;
            help = 1;
        }
    }

    /* Compare entered command with each entry in CLI command table */
    for (cli_cmd = cli_cmd_list; cli_cmd != NULL; cli_cmd = cli_cmd->next) {

        /* Command too long */
        if (strlen(cli_cmd->syntax) > MAX_CMD_LEN)
            return -1;

        /* Build array of syntax words */
        strcpy(stx_buf, cli_cmd->syntax);
        cli_build_words(stx_buf, &stx_count, stx_words, 1);

        match = 1;
        for (i_cmd = 0, i_stx = 0; i_stx < stx_count; i_cmd++, i_stx++) {
            stx = stx_words[i_stx];
            if (*stx == '<' || *stx == '[') {
                /* Parameters start here */
                i_parm = i_stx;
                break;
            }

            if (i_cmd >= argc)
                continue;

            if (strcasestr(stx, argv[i_cmd]) != stx) {
                /* Command word mismatch */
                match = 0;
                break;
            }
        }

        if (match) {
            /* Add to list of matching commands */
            if (match_prev == NULL)
                match_list = cli_cmd;
            else
                match_prev->match_next = cli_cmd;
            match_prev = cli_cmd;
            cli_cmd->match_next = NULL;
        }
    }

    if (match_list == NULL) {
        /* No matching commands */
        cli_printf("Invalid command\n");
    } else if (match_list->match_next == NULL) {
        /* One matching command */
        cli_cmd = match_list;
        
        /* Rebuild array of syntax words */
        strcpy(stx_buf, cli_cmd->syntax);
        cli_build_words(stx_buf, &stx_count, stx_words, 1);

        if (help) {
            for (parm = cli_parm_list; parm != NULL; parm = parm->next) {
                parm->done = 0;
            }
            cli_header_nl("Description", 0, 0);
            cli_printf("%s.\n\n", cli_cmd->descr);
            cli_header_nl("Syntax", 0, 0);
            cli_printf("%s\n\n", cli_cmd->syntax);
            for (max = 0, i = 0; i_parm && i < 2; i++) {
                for (i_stx = i_parm; i_stx < stx_count; i_stx++) {
                    if ((parm = cli_parm_lookup(stx_words[i_stx], cli_cmd)) == NULL)
                        continue;
                    len = strlen(parm->txt);
                    if (i == 0) {
                        if (!(parm->flags & CLI_PARM_FLAG_NO_TXT)) {
                            if (len > max)
                                max = len;
                        }
                    } else if (!parm->done) {
                        parm->done = 1;
                        if (i_stx == i_parm)
                            cli_header_nl("Parameters", 0, 0);
                        if (!(parm->flags & CLI_PARM_FLAG_NO_TXT)) {
                            cli_printf("%s", parm->txt);
                            for (j = len; j < max; j++)
                                cli_printf(" ");
                            cli_printf(": ");
                        }
                        cli_printf("%s\n", parm->help);
                    }
                }
            }

        } else {
            enum {
                CLI_STATE_IDLE,
                CLI_STATE_PARSING,
                CLI_STATE_DONE,
                CLI_STATE_ERROR
            } state;
            mesa_bool_t end = 0, separator, skip_parm;

            if (cli_cmd->func2)
                return cli_cmd->func2(argc, argv);

            /* Create default parameters */
            req = &cli_req;
            cli_req_default_set(req, cli_cmd);

            /* Parse arguments */
            state = CLI_STATE_IDLE;
            for (i_cmd = i_parm, i_stx = i_parm; i_parm && i_stx < stx_count; i_stx++) {
                stx = stx_words[i_stx];

                separator = (strcmp(stx, "|") == 0);
                skip_parm = 0;
                switch (state) {
                case CLI_STATE_IDLE:
                    if (stx[0] == '(' || stx[1] == '(') {
                        i = i_cmd;
                        state = CLI_STATE_PARSING;
                    }
                    break;
                case CLI_STATE_PARSING:
                    break;
                case CLI_STATE_ERROR:
                    if (end && separator) {
                        /* Parse next group */
                        i_cmd = i;
                        state = CLI_STATE_PARSING;
                    } else if (strstr(stx, ")]") != NULL) {
                        i_cmd = i;
                        state = CLI_STATE_IDLE;
                    }
                    skip_parm = 1;
                    break;
                case CLI_STATE_DONE:
                    if (end && !separator)
                        state = CLI_STATE_IDLE;
                    else
                        skip_parm = 1;
                    break;
                default:
                    cli_printf("Illegal state: %d\n", state);
                    return -1;
                }
                end = (strstr(stx, ")") != NULL);
                
#if 0
                cli_printf("stx: %s, cmd: %s, state: %s\n",
                           stx, i_cmd < argc ? argv[i_cmd] : NULL,
                           state == CLI_STATE_IDLE ? "IDLE" :
                           state == CLI_STATE_PARSING ? "PARSING" :
                           state == CLI_STATE_ERROR ? "ERROR" : "DONE");
#endif                
                /* Skip if separator or not in parsing state */
                if (separator || skip_parm)
                    continue;

                /* Lookup parameter */
                if ((parm = cli_parm_lookup(stx, cli_cmd)) == NULL) {
                    cli_printf("Unknown parameter: %s\n", stx);
                    return -1;
                }

                if (i_cmd >= argc) {
                    /* No more command words */
                    error = 1;
                } else {
                    if (parm->parse_func == NULL) {
                        cli_printf("missing parser function: %s\n", parm->txt);
                        error = 1;
                    } else {
                        req->parm_parsed = 1;
                        req->cmd = argv[i_cmd];
                        req->stx = stx;
                        req->cmd_org = argv[i_cmd];
                        error = parm->parse_func(req);
                    }

#if 0
                    cli_printf("stx: %s, cmd: %s, error: %d\n", stx, req->cmd, error);
#endif
                    if (!error) {
                        if (parm->flags & CLI_PARM_FLAG_SET)
                            req->set = 1;
                        i_cmd += req->parm_parsed;
                    }
                }

                /* No error or error in optional parameter */
                if (!error ||
                    (stx[0] == '[' && (stx[1] != '(' || stx[2] == '['))) {
                    if (state == CLI_STATE_PARSING && end)
                        state = CLI_STATE_DONE;
                    continue;
                }

                /* Error in mandatory parameter of group */
                if (state == CLI_STATE_PARSING) {
                    state = CLI_STATE_ERROR;
                    continue;
                }

                /* Error in mandatory parameter */
                if (i_cmd >= argc)
                    cli_printf("Missing %s parameter\n\n", parm->txt);
                else
                    cli_printf("Invalid %s parameter: %s\n\n", parm->txt,
                               argv[i_cmd]);
                cli_printf("Syntax:\n%s\n", cli_cmd->syntax);
                return -1;
            } /* for loop */

            if (i_parm) {
                if (i_cmd < argc) {
                    //cli_printf("i_cmd:%d  < argc:%d \n",i_cmd,argc);
                    cli_printf("Invalid parameter: %s\n\n", argv[i_cmd]);
                    cli_printf("Syntax:\n%s\n", cli_cmd->syntax);
                    return -1;
                }
                if (state == CLI_STATE_ERROR) {
                    cli_printf("Invalid parameter\n\n");
                    cli_printf("Syntax:\n%s\n", cli_cmd->syntax);
                    return -1;
                }
            } /* Parameter handling */

            /* Handle CLI command */
            if (cli_cmd->func) {
                cli_cmd->func(req);
                return 0; // TODO - return value
            } else {
                cli_printf("Command not implemented\n");
                return -1;
            }
        }

    } else {
        cli_printf("Available Commands:\n\n");
        for (cli_cmd = match_list; cli_cmd != NULL; cli_cmd = cli_cmd->match_next)
            cli_printf("%s\n", cli_cmd->syntax);
        return -1;
    }

    return -1;
} /* cli_parse_command */

static void cli_init(void)
{
    int             i;
    mesa_port_no_t  iport;
    mesa_port_map_t *port_map;
    uint32_t        port_cnt = mesa_port_cnt(NULL);

    /* Determine board port count */
    if ((port_map = calloc(port_cnt, sizeof(*port_map))) != NULL) {
        if (mesa_port_map_get(NULL, port_cnt, port_map) == MESA_RC_OK) {
            for (iport = 0; iport < port_cnt; iport++) {
                if (port_map[iport].chip_port < 0) {
                    break;
                }
            }
            cli_port_cnt = iport;
        }
        free(port_map);
    }

    /* Register general commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register general parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

static int write_block(int fd, const char *b, size_t s)
{
    int c = 0, res = 0;

    while (s) {
        res = write(fd, b, s);
        if (res < 0) {
            return -1;

        } else if (res == 0) {
            return c;

        } else {
            b += res;
            c += res;
            s -= res;
        }
    }

    return c;
}

static int cli_con;

int cli_printf(const char *fmt, ...)
{
#define BUF_SIZE 1024
    va_list ap;
    int size = 0;
    char *p = NULL, *buf;
    char local_buf[1024];
    struct ipc_msg *m;

    va_start(ap, fmt);
    size = vsnprintf(local_buf + sizeof(*m), BUF_SIZE - sizeof(*m), fmt, ap);
    va_end(ap);

    if (size >= BUF_SIZE - sizeof(*m)) {
        T_N("Alloc %d", size + sizeof(*m) + 1);
        p = malloc(size + sizeof(*m) + 1);
        if (p == NULL) {
            T_E("Alloc error %d", size + sizeof(*m) + 1);
            return -1;
        }
        buf = p;

        va_start(ap, fmt);
        vsnprintf(buf + sizeof(*m), size + 1, fmt, ap);
        va_end(ap);

    } else {
        buf = local_buf;
    }

    m = (struct ipc_msg *)buf;
    m->type = IPC_STDOUT;
    m->len = size;

    T_N("Write: %d", size + sizeof(*m));
    write_block(cli_con, buf, size + sizeof(*m));

    if (p)
        free(p);

    return size;
#undef BUF_SIZE
}

static int read_block(int fd, char *b, size_t s)
{
    int c = 0, res = 0;

    while (s) {
        res = read(fd, b, s);
        if (res < 0) {
            return -1;

        } else if (res == 0) {
            return c;

        } else {
            b += res;
            c += res;
            s -= res;
        }
    }

    return c;
}

static void cli_connection(int fd, void *ref)
{
    int res, i, return_val;
    struct ipc_msg m;
    int argc = 0;
    char **argv = 0;

    T_N("data on connection");

    // Get number of arguments
    res = read_block(fd, (char *)&m, sizeof(m));
    if (res != sizeof(m)) {
        T_E("Short read %d/%d", res, sizeof(m));
        close(fd);
        return;
    }

    T_N("Msg: type: %d, len: %d", m.type, m.len);
    if (m.type != IPC_ARG_CNT || m.len != sizeof(argc)) {
        T_E("Unexpected opening message (%d/%d)", m.type, m.len);
        close(fd);
        return;
    }

    res = read_block(fd, (char *)&argc, sizeof(argc));
    if (res != sizeof(argc)) {
        T_E("Short read %d/%d", res, sizeof(argc));
        close(fd);
        return;
    }

    T_N("Msg: argc: %d", argc);
    argv = calloc(argc, sizeof(void *));
    if (!argv) {
        T_E("Alloc error %d x %d", argc, sizeof(void *));
        goto OUT;
    }

    // Read arguments
    for (i = 0; i < argc; ++i) {
        res = read_block(fd, (char *)&m, sizeof(m));
        if (res != sizeof(m)) {
            T_E("Short read %d/%d", res, sizeof(m));
            goto OUT;
        }

        if (m.type != IPC_ARG) {
            T_E("Unexpected message (%d/%d)", m.type, m.len);
            goto OUT;
        }

        if (m.len <= 0) {
            T_E("Invalid length %d", m.len);
            goto OUT;
        }

        T_N("Msg: arg-len: %d", m.len);
        argv[i] = malloc(m.len);
        if (!argv[i]) {
            T_E("Alloc error %d", m.len);
            goto OUT;
        }

        res = read_block(fd, argv[i], m.len);
        if (res != m.len) {
            T_E("Short read %d/%d", res, m.len);
            goto OUT;
        }

        if (argv[i][m.len - 1] != 0) {
            T_E("Argument not null terminated");
            goto OUT;
        }
    }

    T_N("Before cli parse");
    return_val = cli_parse_command(argc, (const char **)argv);
    T_N("After cli parse -> %d", return_val);

    m.type = IPC_RETURN;
    m.len = sizeof(return_val);
    res = write_block(fd, (const char *)&m, sizeof(m));
    if (res != sizeof(m)) {
        T_E("Short write %d/%d", res, sizeof(m));
        goto OUT;
    }

    res = write_block(fd, (const char *)&return_val, sizeof(return_val));
    if (res != sizeof(return_val)) {
        T_E("Short write %d/%d", res, return_val);
        goto OUT;
    }

OUT:
    if (argv) {
        for (i = 0; i < argc; i++)
            if (argv[i])
                free(argv[i]);

        free(argv);
    }

    close(fd);
    (void)fd_read_register(fd, NULL, NULL);
    cli_con = -1;

    // Exit after closing
    if (cli_exit) {
        exit(0);
    }
}

static void cli_accept(int fd, void *ref)
{
    if (cli_con > 0) {
        T_E("already connected");
    } else if ((cli_con = accept(fd, NULL, NULL)) <= 0) {
        T_E("accept() failed");
    } else if (fd_read_register(cli_con, cli_connection, NULL) < 0) {
        T_E("fd_read_register() failed");
        close(cli_con);
        cli_con = -1;
    } else {
        T_N("new connection accepted");
    }
}

static void cli_socket_init(void)
{
    int                fd;
    struct sockaddr_un local;

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, IPC_FILE);
    unlink(local.sun_path);

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        T_E("socket failed");
    } else if (bind(fd, (struct sockaddr *)&local, sizeof(local.sun_family) + strlen(local.sun_path)) < 0) {
        T_E("bind failed");
        close(fd);
    } else if (listen(fd, 1) < 0) {
        T_E("listen failed");
        close(fd);
    } else if (fd_read_register(fd, cli_accept, NULL) < 0) {
        T_E("fd_read_register() failed");
        close(fd);
    }
}

void mscc_appl_cli_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        cli_req.inst = init->board_inst;
        cli_socket_init();
        cli_init();
        break;

    default:
        break;
    }
}
