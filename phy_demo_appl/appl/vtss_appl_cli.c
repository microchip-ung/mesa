/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_api.h"

#include <termios.h>
#include <unistd.h>

#undef __USE_EXTERN_INLINES /* Avoid warning */
#include <sys/socket.h>

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#include "vtss_version.h"
#include "vtss_appl.h"
#include "vtss_appl_cli.h"

#define MAX_CMD_LEN      (500 + 1)
#define MAX_CMD_HISTORY_LEN 20
#define MAX_WORD_LEN        64

#define CURSOR_UP    0x41
#define CURSOR_DOWN  0x42
#define CURSOR_RIGHT 0x43
#define CURSOR_LEFT  0x44

#define CURSOR_HOME  0x48
#define CURSOR_END   0x4B

#define BS  0x08
#define BEL 0x07
#define LF  0x0a
#define CR  0x0d
#define ESC 0x1b

static char cmd_buf[MAX_CMD_LEN];
static u32  cmd_len = 0;
static u32  cmd_cursor = 0;
static BOOL suspended = 0;

struct {
    u32 idx;
    u32 len;
    u32 scroll;
    struct {
        u32  cmd_len;
        char cmd[MAX_CMD_LEN];
    } buf[MAX_CMD_HISTORY_LEN];
} cmd_history;

static vtss_appl_inst_t cli_appl_inst;
static vtss_appl_board_t *cli_board;

static int cli_char_available(unsigned char *c)
{
    fd_set fdset;
    struct timeval tv;

    FD_ZERO(&fdset);
    FD_SET(0, &fdset);
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    if(select(1, &fdset, NULL, NULL, &tv) > 0) {
        *c = getchar();
        return 1;
    }
    return 0;
}

static void prompt(void)
{
    printf("%s>", cli_board->descr);
    fflush(stdout);
}

static void cursor_left(void)
{
    if (cmd_cursor > 0) {
        cmd_cursor--;
        putchar(ESC);
        putchar(0x5b);
        putchar(CURSOR_LEFT);
        fflush(stdout);
    }
}

static void cursor_right(void)
{
    if (cmd_cursor < cmd_len) {
        cmd_cursor++;
        putchar(ESC);
        putchar(0x5b);
        putchar(CURSOR_RIGHT);
        fflush(stdout);
    }
}

static void cursor_home(void)
{
    while (cmd_cursor > 0) {
        cursor_left();
    }
}

static void delete_to_eol(void)
{
    putchar(ESC);
    putchar(0x5b);
    putchar(CURSOR_END);
    fflush(stdout);
}

static void rewrite_to_eol(void)
{
    while (cmd_cursor < cmd_len) {
        putchar(cmd_buf[cmd_cursor++]);
    }
    fflush(stdout);
}

static void delete_line(void)
{
    cursor_home();
    delete_to_eol();
}

static void append_line(void)
{
    u32 cursor_save;

    cursor_save = cmd_cursor;
    rewrite_to_eol();
    while (cmd_cursor > cursor_save) {
        cursor_left();
    }
}

static void delete_char(int backspace)
{
    u32 j;

    if (cmd_len == 0 ||
        (backspace && cmd_cursor == 0) ||
        (!backspace && cmd_cursor == cmd_len))
        return;

    if (backspace)
        cursor_left();
    delete_to_eol();

    /* concatenate command string */
    cmd_len--;
    for (j = cmd_cursor; j < cmd_len; j++) {
        cmd_buf[j] = cmd_buf[j + 1];
    }

    /* rewrite command part to the right of cursor */
    append_line();
}

static void insert_char(char ch)
{
    u32 j;

    delete_to_eol();
    for (j = cmd_len; j > cmd_cursor; j--) {
        cmd_buf[j] = cmd_buf[j - 1];
    }
    cmd_len++;
    cmd_buf[cmd_cursor++] = ch;

    append_line();
}

static void cmd_history_put(void)
{
    memcpy(&cmd_history.buf[cmd_history.idx].cmd, &cmd_buf, cmd_len);
    cmd_history.buf[cmd_history.idx].cmd_len = cmd_len - 1; /* don't include CR */
    if (cmd_history.len < MAX_CMD_HISTORY_LEN) {
        cmd_history.len++;
    }
    if (++cmd_history.idx >= MAX_CMD_HISTORY_LEN) {
        cmd_history.idx = 0;
    }
    cmd_history.scroll = 0;
}

static void cmd_history_get(void)
{
    u32 idx;

    if (cmd_history.idx >= cmd_history.scroll) {
        idx = cmd_history.idx - cmd_history.scroll;
    }
    else {
        idx = MAX_CMD_HISTORY_LEN - (cmd_history.scroll - cmd_history.idx);
    }

    cmd_len = cmd_history.buf[idx].cmd_len;
    memcpy(&cmd_buf, &cmd_history.buf[idx].cmd, cmd_len);

}

static void get_old_cmd(void)
{
    delete_line();
    cmd_history_get();
    rewrite_to_eol();
}

static void process_escape_seq(char ch_1, char ch_2)
{
    if (ch_1 == 0x5b) {
        switch (ch_2) {
        case CURSOR_UP:
            if (cmd_history.scroll < cmd_history.len) {
                cmd_history.scroll++;
                get_old_cmd();
            }
            else {
                putchar(BEL);
                fflush(stdout);
            }
            break;

        case CURSOR_DOWN:
            if (cmd_history.scroll > 0) {
                cmd_history.scroll--;

                if (cmd_history.scroll > 0) {
                    get_old_cmd();
                }
                else {
                    delete_line();
                    cmd_len = 0;
                    cmd_cursor = 0;
                }
            }
            else {
                putchar(BEL);
                fflush(stdout);
            }
            break;

        case CURSOR_RIGHT:
            cursor_right();
            break;

        case CURSOR_LEFT:
            cursor_left();
            break;

        case CURSOR_HOME:
            cursor_home();
            break;

        case CURSOR_END:
            while (cmd_cursor < cmd_len) {
                cursor_right();
            }
            break;

        default:
            break;
        }
    }
}

static int empty_cmd_line(void)
{
    u32 j;

    for (j = 0; j < cmd_len; j++) {
        if ((cmd_buf[j] != ' ') && (cmd_buf[j] != CR)) {
            return 0;
        }
    }
    return 1;
}

static int cmd_ready(void)
{
    unsigned char ch;
    u32 loop_count;

    loop_count = 0;
    while (cli_char_available(&ch) && (loop_count++ < 20)) {

        /* convert LF into CR for linux terminal usage */
        if(ch==LF) ch=CR;
        if (ch != LF) { /* discard LF chars */

            if (ch == BS) /* Backspace */
                delete_char(1);
            else if (ch == 0x7f) /* DEL */
                delete_char(1);
            else if (ch == ESC) {
                ch = getc(stdin);
                process_escape_seq(ch, getc(stdin));
            } else {

                if (cmd_len < MAX_CMD_LEN) {
                    /* echo */
                    putchar(ch);
                    fflush(stdout);
                }

                if (ch != CR) {
                    if (cmd_len < MAX_CMD_LEN) {
                        if (cmd_cursor < cmd_len) {
                            insert_char(ch);
                        }
                        else {
                            cmd_buf[cmd_cursor++] = ch;
                            if (cmd_len < cmd_cursor) {
                                cmd_len++;
                            }
                        }
                    }
                }
                else {
                    putchar(LF);
                    fflush(stdout);

                    /* Ensure that CR is present in buffer in case of buffer overflow */
                    if (cmd_len >= (MAX_CMD_LEN-2)) {
		        cmd_len = MAX_CMD_LEN - 2;
                    }
		    cmd_buf[cmd_len++] = CR;
                    if (!empty_cmd_line()) {
                        cmd_history_put();
                    }
                    cmd_buf[cmd_len++] = '\0';

                    fflush(stdout);
                    return 1;
                }
            }
        }
    }
    return 0;
}

static char *cmd_get(void)
{
    cmd_len = 0;
    cmd_cursor = 0;

    return &cmd_buf[0];
}

static struct termios stored_settings;

static void restore_keypress(void)
{
    tcsetattr(0, TCSANOW, &stored_settings);
}

static void cli_inst_update(vtss_appl_inst_t inst)
{
    cli_appl_inst = inst;
    cli_board = vtss_appl_board_get(inst);
}

/****************************************************************************/
/*  Command parsing                                                         */
/****************************************************************************/

static cli_cmd_t *cli_cmd_list;

static void cli_cmd_help(cli_req_t *req)
{
    printf("Type '<group> ?' to get list of group commands, e.g. 'system ?'.\n");
    printf("Type '<command> ?' to get help on a command, e.g. 'system reboot ?'.\n");
    printf("Commands may be abbreviated, e.g. 'sy re' instead of 'system reboot'.\n");
}

static void cli_cmd_exit(cli_req_t *req)
{
    exit(0);
}

static void cli_cmd_sys_conf(cli_req_t *req)
{
    printf("Version: %s\n", vtss_version_string);
    printf("Date   : %s\n", vtss_compile_time);
}

#if defined(VTSS_FEATURE_WARM_START)
static const char *cli_restart_txt(vtss_restart_t restart)
{
    return (restart == VTSS_RESTART_COLD ? "Cold" :
            restart == VTSS_RESTART_COOL ? "Cool" :
            restart == VTSS_RESTART_WARM ? "Warm" : "?");
}

static void cli_cmd_system_restart(cli_req_t *req)
{
    if (req->set) {
        vtss_restart_conf_set(req->api_inst,
                              req->warm ? VTSS_RESTART_WARM : VTSS_RESTART_COOL);
    } else {
        vtss_restart_status_t status;
        vtss_restart_t        restart;

        if (vtss_restart_conf_get(req->api_inst, &restart) == VTSS_RC_OK)
            printf("Next Restart    : %s\n", cli_restart_txt(restart));
        if (vtss_restart_status_get(req->api_inst, &status) == VTSS_RC_OK) {
            printf("Previous Restart: %s\n", cli_restart_txt(status.restart));
            printf("Current Version : %u\n", status.cur_version);
            printf("Previous Version: %u\n", status.prev_version);
        }
    }
}
#endif /* VTSS_FEATURE_WARM_START */

/* Show port map table */
static void cli_cmd_port_map(cli_req_t *req)
{
    BOOL            first = 1;
    vtss_port_no_t  port, port_no;
    vtss_port_map_t port_map[VTSS_PORT_ARRAY_SIZE], *map;

    if (vtss_port_map_get(req->api_inst, port_map) != VTSS_RC_OK)
        return;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        if (req->port_list[port] == 0)
            continue;
        if (first) {
            first = 0;
            cli_table_header("Port  Chip Port  MIIM Bus  MIIM Addr");
        }
        map = &port_map[port_no];
        printf("%-6u", port);
        if (map->chip_port < 0)
            printf("%-11s", "-");
        else
            printf("%-11d", map->chip_port);
        if (map->miim_controller == VTSS_MIIM_CONTROLLER_NONE)
            printf("%-10s%s", "-", "-");
        else
            printf("%-10d%-2u", map->miim_controller, map->miim_addr);
        printf("\n");
    }
}

static const char * const cli_api_group_table[VTSS_DEBUG_GROUP_COUNT] = {
    [VTSS_DEBUG_GROUP_ALL]       = "all",
    [VTSS_DEBUG_GROUP_INIT]      = "init",
    [VTSS_DEBUG_GROUP_MISC]      = "misc",
    [VTSS_DEBUG_GROUP_PORT]      = "port",
    [VTSS_DEBUG_GROUP_PORT_CNT]  = "counters",
    [VTSS_DEBUG_GROUP_PHY]       = "phy",
    [VTSS_DEBUG_GROUP_VLAN]      = "vlan",
    [VTSS_DEBUG_GROUP_PVLAN]     = "pvlan",
    [VTSS_DEBUG_GROUP_MAC_TABLE] = "mac_table",
    [VTSS_DEBUG_GROUP_ACL]       = "acl",
    [VTSS_DEBUG_GROUP_QOS]       = "qos",
    [VTSS_DEBUG_GROUP_AGGR]      = "aggr",
    [VTSS_DEBUG_GROUP_GLAG]      = "glag",
    [VTSS_DEBUG_GROUP_STP]       = "stp",
    [VTSS_DEBUG_GROUP_MIRROR]    = "mirror",
    [VTSS_DEBUG_GROUP_EVC]       = "evc",
    [VTSS_DEBUG_GROUP_ERPS]      = "erps",
    [VTSS_DEBUG_GROUP_EPS]       = "eps",
    [VTSS_DEBUG_GROUP_SR]        = "sr",
    [VTSS_DEBUG_GROUP_PACKET]    = "packet",
    [VTSS_DEBUG_GROUP_FDMA]      = "fdma",
    [VTSS_DEBUG_GROUP_TS]        = "ts",
    [VTSS_DEBUG_GROUP_WM]        = "wm",
    [VTSS_DEBUG_GROUP_LRN]       = "lrn",
    [VTSS_DEBUG_GROUP_IPMC]      = "ipmc",
    [VTSS_DEBUG_GROUP_STACK]     = "stack",
    [VTSS_DEBUG_GROUP_CMEF]      = "cmef",
    [VTSS_DEBUG_GROUP_HOST]      = "host",
    [VTSS_DEBUG_GROUP_MPLS]      = "mpls",
    [VTSS_DEBUG_GROUP_HW_PROT]   = "hwprot",
    [VTSS_DEBUG_GROUP_VXLAT]     = "vxlat",
    [VTSS_DEBUG_GROUP_OAM]       = "oam",
    [VTSS_DEBUG_GROUP_SER_GPIO]  = "sgpio",
    [VTSS_DEBUG_GROUP_L3]        = "l3",
    [VTSS_DEBUG_GROUP_AFI]       = "afi",
    [VTSS_DEBUG_GROUP_MACSEC]    = "macsec",
};

static void cli_cmd_debug_api(cli_req_t *req)
{
    vtss_debug_info_t  info;
    vtss_debug_group_t group;
    vtss_port_no_t     iport;

    if (req->api_group == VTSS_DEBUG_GROUP_COUNT) {
        printf("Legal groups are:\n\n");
        for (group = VTSS_DEBUG_GROUP_ALL; group < VTSS_DEBUG_GROUP_COUNT; group++) {
            if (cli_api_group_table[group]) {
                printf("%s\n", cli_api_group_table[group]);
            } else {
                printf("%d - unknown\n", group);
            }
        }
    } else if (vtss_debug_info_get(&info) == VTSS_RC_OK) {
        info.layer = req->api_layer;
        info.group = req->api_group;
        info.full = req->full;
        info.clear = req->clear;
        for (iport = VTSS_PORT_NO_START; iport < VTSS_PORT_NO_END; iport++)
            info.port_list[iport] = req->port_list[iport2uport(iport)];
        vtss_debug_info_print(NULL, printf, &info);
    }
}

/* MMD (MDIO Management Devices) read/write */
static void cli_cmd_debug_mmd(cli_req_t *req, BOOL write)
{
    vtss_port_no_t port_no, port;
    int            i, mmd, first = 1;
    ushort         value;
    vtss_rc        rc = VTSS_RC_OK;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        port = iport2uport(port_no);
        if (req->port_list[port] == 0)
            continue;
        for (mmd = 0; mmd < CLI_PHY_MAX; mmd++) {
            if (req->mmd_list[mmd] == 0)
                continue;
            if (write) {
                /* Write */
                vtss_port_mmd_write(req->api_inst, port_no, mmd, req->mmd_addr, req->value);
            } else {
                /* Read */
                if (VTSS_RC_OK == (rc = vtss_port_mmd_read(req->api_inst, port_no, mmd, req->mmd_addr, &value))) {
                    if (first) {
                        first = 0;
                        printf("Port  MMD  Addr    15******8*7*******0  Value\n");
                    }

                    printf("%-6u0x%02x  0x%04x", port, mmd, req->mmd_addr);
                    for (i = 15; i >= 0; i--)
                        printf("%d%s",
                               value & (1<<i) ? 1 : 0, (i % 4) || i == 0 ? "" : ".");
                    if (req->decimal)
                        printf("  %6d", value);
                    else
                        printf("  0x%04x", value);
                    printf("\n");
                }
            }
        }
    }
}

static void cli_cmd_debug_mmd_read(cli_req_t *req)
{
    cli_cmd_debug_mmd(req, 0);
}

static void cli_cmd_debug_mmd_write(cli_req_t *req)
{
    cli_cmd_debug_mmd(req, 1);
}

static void cli_cmd_debug_chip_id(cli_req_t *req)
{
    vtss_chip_id_t id;

    if (vtss_chip_id_get(req->api_inst,&id) == VTSS_RC_OK) {
        printf("Part Number: 0x%04x\n", id.part_number);
        printf("Revision   : %u\n", id.revision);
    }
}

static void cli_cmd_debug_suspend(cli_req_t *req)
{
    if (!suspended) {
        suspended = TRUE;
        printf("Application suspended\n");
    }
}

static void cli_cmd_debug_resume(cli_req_t *req)
{
    if (suspended) {
        suspended = FALSE;
        printf("Application resumed\n");
    }
}

#define CLI_TRACE_GROUP_ALL (VTSS_TRACE_GROUP_COUNT + 1)
static void cli_cmd_debug_trace(cli_req_t *req)
{
    vtss_trace_layer_t layer;
    vtss_trace_group_t group;
    vtss_trace_conf_t  conf;
    vtss_trace_level_t level;
    int                first = 1;

    for (layer = 0; layer < VTSS_TRACE_LAYER_COUNT; layer++) {
        if (req->trace_layer != VTSS_TRACE_LAYER_COUNT && layer != req->trace_layer)
            continue;

        for (group = 0; group <= VTSS_TRACE_GROUP_COUNT; group++) {
            if (req->group != CLI_TRACE_GROUP_ALL && group != req->group)
                continue;

            if (group == VTSS_APPL_TRACE_GROUP)
                conf = vtss_appl_trace_conf;
            else
                vtss_trace_conf_get(group, &conf);

            if (req->set) {
                conf.level[layer] = req->level;
                if (group == VTSS_APPL_TRACE_GROUP)
                    vtss_appl_trace_conf = conf;
                else
                    vtss_trace_conf_set(group, &conf);
            } else {
                if (first) {
                    cli_table_header("Layer  Group       Level");
                    first = 0;
                }
                level = conf.level[layer];
                printf("%-7s%-12s%s\n",
                       layer == VTSS_TRACE_LAYER_AIL ? "ail" : "cil",
                       group == VTSS_TRACE_GROUP_COUNT ? "main" :
                       group == VTSS_TRACE_GROUP_DEFAULT ? "default" :
                       group == VTSS_TRACE_GROUP_PORT ? "port" :
                       group == VTSS_TRACE_GROUP_PHY ? "phy" :
                       group == VTSS_TRACE_GROUP_PACKET ? "packet" :
                       group == VTSS_TRACE_GROUP_AFI ? "afi" :
                       group == VTSS_TRACE_GROUP_QOS ? "qos" :
                       group == VTSS_TRACE_GROUP_L2 ? "l2" :
                       group == VTSS_TRACE_GROUP_L3 ? "l3" :
                       group == VTSS_TRACE_GROUP_SECURITY ? "security" :
                       group == VTSS_TRACE_GROUP_EVC ? "evc" :
                       group == VTSS_TRACE_GROUP_FDMA_NORMAL ? "fdma_normal" :
                       group == VTSS_TRACE_GROUP_FDMA_IRQ ? "fdma_irq" :
                       group == VTSS_TRACE_GROUP_REG_CHECK ? "reg_check" :
                       group == VTSS_TRACE_GROUP_MPLS ? "mpls" :
                       group == VTSS_TRACE_GROUP_HW_PROT ? "hwprot" :
                       group == VTSS_TRACE_GROUP_HQOS ? "hqos" :
                       group == VTSS_TRACE_GROUP_MACSEC ? "macsec" :
                       group == VTSS_TRACE_GROUP_VCAP ? "vcap" :
                       group == VTSS_TRACE_GROUP_OAM ? "oam":
                       group == VTSS_TRACE_GROUP_TS ? "ts" : "?",
                       level == VTSS_TRACE_LEVEL_NONE ? "off" :
                       level == VTSS_TRACE_LEVEL_ERROR ? "error" :
                       level == VTSS_TRACE_LEVEL_INFO ? "info" :
                       level == VTSS_TRACE_LEVEL_DEBUG ? "debug" :
                       level == VTSS_TRACE_LEVEL_NOISE ? "noise" : "?");
            }
        }
    }
}

static void cli_cmd_debug_test(cli_req_t *req)
{
    printf("Test %s !\n",
           cli_board->debug_test == NULL ? "function not installed" :
           cli_board->debug_test(req->value) == VTSS_RC_OK ? "success" : "failed");
}

#if defined(VTSS_GPIOS)
#define CLI_CMD_GPIO_DIR   0
#define CLI_CMD_GPIO_READ  1
#define CLI_CMD_GPIO_WRITE 2
static void cli_cmd_debug_gpio(cli_req_t *req, u32 cmd)
{
    vtss_gpio_no_t gpio;
    BOOL           first = 1, value;

    for (gpio = VTSS_GPIO_NO_START; gpio < VTSS_GPIO_NO_END; gpio++) {
        if (req->gpio_list[gpio] == 0)
            continue;
        if (cmd == CLI_CMD_GPIO_DIR)
            vtss_gpio_direction_set(req->api_inst, 0, gpio, req->set ? req->enable : 1);
        else if (cmd == CLI_CMD_GPIO_WRITE)
            vtss_gpio_write(req->api_inst, 0, gpio, req->value);
        else if (vtss_gpio_read(req->api_inst, 0, gpio, &value) == VTSS_RC_OK) {
            if (first)
                cli_table_header("GPIO  Value");
            first = 0;
            printf("%-4u  %u\n", gpio, value);
        }
    }
}

static void cli_cmd_debug_gpio_dir(cli_req_t *req)
{
    cli_cmd_debug_gpio(req, CLI_CMD_GPIO_DIR);
}

static void cli_cmd_debug_gpio_read(cli_req_t *req)
{
    cli_cmd_debug_gpio(req, CLI_CMD_GPIO_READ);
}

static void cli_cmd_debug_gpio_write(cli_req_t *req)
{
    cli_cmd_debug_gpio(req, CLI_CMD_GPIO_WRITE);
}
#endif /* VTSS_GPIOS */

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
        "System Configuration",
        "Show system information",
        cli_cmd_sys_conf,
    },
#if defined(VTSS_CHIP_CU_PHY)
#if defined(VTSS_FEATURE_WARM_START)
    {
        "System Restart [warm|cool]",
        "Set or show the restart mode",
        cli_cmd_system_restart
    },
#endif /* VTSS_FEATURE_WARM_START */
#endif
    {
        "Port Map [<port_list>]",
        "Show port map",
        cli_cmd_port_map
    },
    {
        "Debug API [<layer>] [<group>] [<port_list>] [full] [clear]",
        "Show API debug information",
        cli_cmd_debug_api
    },
    {
        "Debug MMD Read <port_list> <mmd_list> <mmd_addr> [decimal]",
        "Read MMD register",
        cli_cmd_debug_mmd_read
    },
    {
        "Debug MMD Write <port_list> <mmd_list> <mmd_addr> <value>",
        "Write MMD register",
        cli_cmd_debug_mmd_write
    },
    {
        "Debug Chip ID",
        "Read chip ID",
        cli_cmd_debug_chip_id
    },
    {
        "Debug Suspend",
        "Suspend application",
        cli_cmd_debug_suspend
    },
    {
        "Debug Resume",
        "Resume application",
        cli_cmd_debug_resume
    },
#if VTSS_OPT_TRACE
    {
        "Debug Trace [<layer>] [<group>] [off|error|info|debug|noise]",
        "Set or show the trace level for group",
        cli_cmd_debug_trace
    },
#endif /* VTSS_OPT_TRACE */
    {
        "Debug Test [<test_no>]",
        "Run platform specific test",
        cli_cmd_debug_test
    },
#if defined(VTSS_GPIOS)
    {
        "Debug GPIO Output [<gpio_list>] [enable|disable]",
        "Setup GPIO direction",
        cli_cmd_debug_gpio_dir
    },
    {
        "Debug GPIO Read [<gpio_list>]",
        "Read value from GPIO input pin",
        cli_cmd_debug_gpio_read
    },
    {
        "Debug GPIO Write [<gpio_list>] <gpio_value>",
        "Write value to GPIO output pin",
        cli_cmd_debug_gpio_write
    },
#endif /* VTSS_GPIOS */
}; /* cli_cmd_table */

static cli_parm_t *cli_parm_list;

char *cli_parse_find(char *cmd, char *stx)
{
    char *p, *found = NULL;
    BOOL parm = 0, start = 1;

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
            if (strstr(p, cmd) == p) {
                if (found != NULL)
                    return NULL;
                found = p;
            }
        }
    }
    return found;
}

int cli_parm_u32(cli_req_t *req, u32 *val, u32 min, u32 max)
{
    u32  n;
    char *end;

    n = strtoul(req->cmd, &end, 0);
    if (*end != '\0' || n < min || n > max)
        return 1;

    *val = n;
    return 0;
}

int cli_parm_u16(cli_req_t *req, u16 *val, u32 min, u32 max)
{
    u32 value;
    int error;

    error = cli_parm_u32(req, &value, min, max);
    if (!error)
        *val = value;
    return error;
}

int cli_parm_u8(cli_req_t *req, u8 *val, u32 min, u32 max)
{
    u32 value;
    int error;

    error = cli_parm_u32(req, &value, min, max);
    if (!error)
        *val = value;
    return error;
}

static int cli_parm_port(cli_req_t *req)
{
    int error;
    u32 value;

    error = cli_parm_u32(req, &value, 1, VTSS_PORTS);
    if (!error)
        req->port = (value - 1);
    return error;
}

static int cli_parm_port_no(cli_req_t *req)
{
    return cli_parm_u32(req, &req->port_no, 1, VTSS_PORTS);
}

/* Convert text to list */
int cli_parse_list(char *buf, BOOL *list, u32 min, u32 max, BOOL def)
{
    u32   i, start = 0, n;
    char  *p, *end;
    BOOL  error, range = 0, comma = 0;

    /* Clear list by default */
    for (i = min; i <= max; i++)
        list[i] = 0;

    p = buf;
    error = (p == NULL);
    while (p != NULL && *p != '\0') {
        /* Read integer */
        n = strtoul(p, &end, 0);
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

/* Remove unused ports from the list */
static void cli_remove_unused_ports(cli_req_t *req)
{
    vtss_port_no_t  port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++)
        if (cli_board->port_map[port_no].chip_port < 0)
            req->port_list[iport2uport(port_no)] = 0;
}

static int cli_parm_port_list(cli_req_t *req)
{
    int error;

    error = cli_parse_list(req->cmd, req->port_list, 1, VTSS_PORTS, 1);
    cli_remove_unused_ports(req);
    return error;
}

static int cli_parm_keyword(cli_req_t *req)
{
    char *found;

    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncmp(found, "bytes", 5))
        req->bytes = 1;
    else if (!strncmp(found, "clear", 5))
        req->clear = 1;
    else if (!strncmp(found, "cool", 4))
        req->warm = 0;
    else if (!strncmp(found, "debug", 5))
        req->level = VTSS_TRACE_LEVEL_DEBUG;
    else if (!strncmp(found, "disable", 7))
        req->disable = 1;
    else if (!strncmp(found, "decimal", 7))
        req->decimal = 1;
    else if (!strncmp(found, "errors", 6))
        req->errors = 1;
    else if (!strncmp(found, "error", 5))
        req->level = VTSS_TRACE_LEVEL_ERROR;
    else if (!strncmp(found, "enable", 6))
        req->enable = 1;
    else if (!strncmp(found, "full", 4))
        req->full = 1;
    else if (!strncmp(found, "info", 4))
        req->level = VTSS_TRACE_LEVEL_INFO;
    else if (!strncmp(found, "noise", 5))
        req->level = VTSS_TRACE_LEVEL_NOISE;
    else if (!strncmp(found, "off", 3))
        req->level = VTSS_TRACE_LEVEL_NONE;
    else if (!strncmp(found, "packets", 7))
        req->packets = 1;
    else if (!strncmp(found, "warm", 4)) {
        req->warm = 1;
#if defined(VTSS_CHIP_10G_PHY)
    } else if (!strncmp(found, "a", 1)) {
        req->lb.lb_type = VTSS_LB_NETWORK_XS_DEEP;
    } else if (!strncmp(found, "b", 1)) {
        req->lb.lb_type = VTSS_LB_SYSTEM_XS_SHALLOW;
    } else if (!strncmp(found, "c", 1)) {
        req->lb.lb_type = VTSS_LB_SYSTEM_XS_DEEP;
    } else if (!strncmp(found, "d", 1)) {
        req->lb.lb_type = VTSS_LB_NETWORK_XS_SHALLOW;
    } else if (!strncmp(found, "e", 1)) {
        req->lb.lb_type = VTSS_LB_SYSTEM_PCS_SHALLOW;
    } else if (!strncmp(found, "f", 1)) {
        req->lb.lb_type = VTSS_LB_NETWORK_PCS;
    } else if (!strncmp(found, "g", 1)) {
        req->lb.lb_type = VTSS_LB_SYSTEM_PCS_DEEP;
    } else if (!strncmp(found, "h", 1)) {
        req->lb.lb_type = VTSS_LB_NETWORK_WIS;
    } else if (!strncmp(found, "j", 1)) {
        req->lb.lb_type = VTSS_LB_SYSTEM_PMA;
    } else if (!strncmp(found, "k", 1)) {
        req->lb.lb_type = VTSS_LB_NETWORK_PMA;
#endif /* VTSS_CHIP_10G_PHY */
    } else
        printf("no match:%s\n",found);

    return 0;
}

int cli_parse_mac(char *cmd, uchar *mac_addr)
{
    u32 mac[6];
    u32 i;
    int error = 1;

    if (sscanf(cmd, "%2x-%2x-%2x-%2x-%2x-%2x",
               &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]) == 6) {
        for (i = 0; i < 6; i++)
            mac_addr[i] = (mac[i] & 0xff);
        error = 0;
    }
    return error;
}

static int cli_parm_mac(cli_req_t *req)
{
    return cli_parse_mac(req->cmd, req->mac);
}

static int cli_parm_vid(cli_req_t *req)
{
    return cli_parm_u16(req, &req->vid, VTSS_VID_DEFAULT, VTSS_VID_RESERVED);
}

static int cli_parm_phy_value(cli_req_t *req)
{
    return cli_parm_u32(req, &req->value, 0, 0xffff);
}

static int cli_parm_mmd_list(cli_req_t *req)
{
    return cli_parse_list(req->cmd, req->mmd_list, 0, 31, 0);
}

static int cli_parm_mmd_addr(cli_req_t *req)
{
    return cli_parm_u16(req, &req->mmd_addr, 0, 0xffff);
}

static int cli_parm_api_layer(cli_req_t *req)
{
    switch (req->cmd[0]) {
    case 'a':
        req->api_layer = VTSS_DEBUG_LAYER_AIL;
        break;
    case 'c':
        req->api_layer = VTSS_DEBUG_LAYER_CIL;
        break;
    default:
        return 1;
    }
    return 0;
}

static int cli_parm_api_group(cli_req_t *req)
{
    int                error = 1;
    const char         *txt = "show";
    vtss_debug_group_t group;

    /* Accept 'show' keyword to display groups */
    if (strstr(txt, req->cmd) == txt) {
        req->api_group = VTSS_DEBUG_GROUP_COUNT;
        return 0;
    }

    for (group = VTSS_DEBUG_GROUP_ALL; group < VTSS_DEBUG_GROUP_COUNT; group++) {
        txt = cli_api_group_table[group];
        if (txt != NULL && strstr(txt, req->cmd) == txt) {
            /* Found matching group */
            if (error) {
                error = 0;
                req->api_group = group;
            } else {
                error = 1;
                break;
            }
        }
    }
    return error;
}

static int cli_parm_trace_layer(cli_req_t *req)
{
    switch (req->cmd[0]) {
    case 'a':
        req->trace_layer = VTSS_TRACE_LAYER_AIL;
        break;
    case 'c':
        req->trace_layer = VTSS_TRACE_LAYER_CIL;
        break;
    default:
        return 1;
    }
    return 0;
}

static int cli_parm_trace_group(cli_req_t *req)
{
    char c = req->cmd[1];

    switch (req->cmd[0]) {
    case 'd':
        req->group = VTSS_TRACE_GROUP_DEFAULT;
        break;
    case 'p':
        req->group = (c == 'o' ? VTSS_TRACE_GROUP_PORT :
                      c == 'h' ? VTSS_TRACE_GROUP_PHY : VTSS_TRACE_GROUP_PACKET);
        break;
    case 'q':
        req->group = VTSS_TRACE_GROUP_QOS;
        break;
    case 'l':
        req->group = VTSS_TRACE_GROUP_L2;
        break;
    case 'm':
        req->group = VTSS_APPL_TRACE_GROUP;
        break;
    default:
        return 1;
    }
    return 0;
}

static int cli_parm_test_no(cli_req_t *req)
{
    return cli_parm_u32(req, &req->value, 0, 1000);
}

#if defined(VTSS_GPIOS)
static int cli_parm_gpio_list(cli_req_t *req)
{
    return cli_parse_list(req->cmd, req->gpio_list, VTSS_GPIO_NO_START, VTSS_GPIO_NO_END - 1, 1);
}

static int cli_parm_gpio_value(cli_req_t *req)
{
    return cli_parm_u32(req, &req->value, 0, 1);
}
#endif /* VTSS_GPIOS */

static cli_parm_t cli_parm_table[] = {
    {
        "<port>",
        "port number",
        CLI_PARM_FLAG_NONE,
        cli_parm_port
    },
    {
        "<port_no>",
        "port number",
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
        "clear",
        "Clear sticky bits",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "clear",
        "Clear counters",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "<mac_addr>",
        "MAC address (xx-xx-xx-xx-xx-xx)",
        CLI_PARM_FLAG_SET,
        cli_parm_mac
    },
    {
        "<vid>",
        "VLAN ID",
        CLI_PARM_FLAG_SET,
        cli_parm_vid
    },
    {
        "warm|cool",
        "warm: Warm restart\n"
        "cool: Cool restart\n"
        "(default: Show restart mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "<value>",
        "Register value (0-0xffff)",
        CLI_PARM_FLAG_SET,
        cli_parm_phy_value
    },
    {
        "decimal",
        "decimal    : Show value in decimal format\n"
        "(default: Show value in hexadecimal format)",
        CLI_PARM_FLAG_NO_TXT,
        cli_parm_keyword
    },
    {
        "<mmd_list>",
        "MMD address list (0-31)",
        CLI_PARM_FLAG_NONE,
        cli_parm_mmd_list,
    },
    {
        "<mmd_addr>",
        "MMD register address (0-0xffff)",
        CLI_PARM_FLAG_NONE,
        cli_parm_mmd_addr
    },
    {
        "<layer>",
        "API Layer, 'ail' or 'cil' (default: All layers)",
        CLI_PARM_FLAG_NONE,
        cli_parm_api_layer
    },
    {
        "<group>",
        "API Function Group or 'show' to list groups (default: All groups)",
        CLI_PARM_FLAG_NONE,
        cli_parm_api_group
    },
    {
        "full",
        "Show full information",
        CLI_PARM_FLAG_NONE,
        cli_parm_keyword
    },
    {
        "<layer>",
        "Trace layer, 'ail' or 'cil', default: All layers",
        CLI_PARM_FLAG_NONE,
        cli_parm_trace_layer
    },
    {
        "<group>",
        "Trace group name, default: All groups",
        CLI_PARM_FLAG_NONE,
        cli_parm_trace_group
    },
    {
        "off|error|info|debug|noise",
        "off     : No trace\n"
        "error   : Error trace level\n"
        "info    : Information trace level\n"
        "debug   : Debug trace level\n"
        "noise   : Noise trace level\n"
        "(default: Show trace level)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "<test_no>",
        "Test number",
        CLI_PARM_FLAG_NONE,
        cli_parm_test_no
    },
#if defined(VTSS_GPIOS)
    {
        "<gpio_list>",
        "GPIO list, default: All GPIOs",
        CLI_PARM_FLAG_NONE,
        cli_parm_gpio_list
    },
    {
        "enable|disable",
        "enable     : Use output mode\n"
        "disable    : Use input mode\n"
        "(default: Enable output mode)",
        CLI_PARM_FLAG_NO_TXT | CLI_PARM_FLAG_SET,
        cli_parm_keyword
    },
    {
        "gpio_value",
        "\n        : The GPIO pin output value 0/1\n",
        CLI_PARM_FLAG_SET,
        cli_parm_gpio_value
    },
#endif /* VTSS_GPIOS */
};  /* cli_parm_table */

static cli_req_t cli_req;

/* Register CLI command */
void vtss_appl_cli_cmd_reg(cli_cmd_t *cmd)
{
    cli_cmd_t *cur, *prev = NULL;
    BOOL      cur_debug, cmd_debug;

    if (cmd->func == NULL) {
        printf("Missing command function: %s\n", cmd->syntax);
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
void vtss_appl_cli_parm_reg(cli_parm_t *parm)
{
    if (parm->parse_func == NULL) {
        printf("Missing parser function: %s\n", parm->txt);
    } else {
        /* Insert first in list */
        parm->next = cli_parm_list;
        cli_parm_list = parm;
    }
}

void vtss_appl_cli_init(void)
{
    struct termios new_settings;
    int            i;

    tcgetattr(0,&stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);

    atexit(restore_keypress);

    cmd_history.len = 0;
    cmd_history.idx = 0;
    cmd_history.scroll = 0;

    cli_inst_update(0);

    /* Register general commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        vtss_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register general parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        vtss_appl_cli_parm_reg(&cli_parm_table[i]);
    }

#if defined(VTSS_FEATURE_LAYER2)
    vtss_appl_cli_l2_init();
#endif /* VTSS_FEATURE_LAYER2 */

    printf("\n\nWelcome to the Microsemi Corporation Command Line Interface.\n");
    printf("Press <enter> to get the list of commands.\n");
    prompt();
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

static void cli_req_default_set(cli_req_t *req)
{
    memset(req, 0, sizeof(*req));
    cli_parse_list(NULL, req->port_list, 0, VTSS_PORTS, 1);
    cli_remove_unused_ports(req);
    req->vid = VTSS_VID_DEFAULT;
    req->trace_layer = VTSS_TRACE_LAYER_COUNT;
    req->group = CLI_TRACE_GROUP_ALL;
#if defined(VTSS_GPIOS)
    cli_parse_list(NULL, req->gpio_list, 0, VTSS_GPIO_NO_END - 1, 1);
#endif /* VTSS_GPIOS */
    req->api_inst = cli_board->inst;
    req->appl_inst = cli_appl_inst;
    req->board = cli_board;
}

/* Header with optional new line before and after */
static void cli_header_nl_char(const char *txt, BOOL pre, BOOL post, char c)
{
    int i, len;

    if (pre)
        printf("\n");
    printf("%s:\n", txt);
    len = (strlen(txt) + 1);
    for (i = 0; i < len; i++)
        printf("%c", c);
    printf("\n");
    if (post)
        printf("\n");
}

/* Underlined header with optional new line before and after */
static void cli_header_nl(const char *txt, BOOL pre, BOOL post)
{
    cli_header_nl_char(txt, pre, post, '-');
}

void cli_table_header(const char *txt)
{
    int i, j, len, count = 0;

    len = strlen(txt);
    for (i = 0; i < len; i++)
        printf("%c", txt[i] == '*' ? ' ' : txt[i]);
    printf("\n");

    while (*txt == ' ') {
        printf(" ");
        txt++;
    }
    for (i = 0; i < len; i++) {
        if (txt[i] == ' ') {
            count++;
        } else {
            for (j = 0; j < count; j++)
                printf("%c", count > 1 && (j >= (count - 2)) ? ' ' : '-');
            printf("-");
            count = 0;
        }
    }
    for (j = 0; j < count; j++)
        printf("%c", count > 1 && (j >= (count - 2)) ? ' ' : '-');
    printf("\n");
}

char *cli_mac_txt(const uchar *mac, char *buf)
{
    sprintf(buf, "%02x-%02x-%02x-%02x-%02x-%02x",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buf;
}

static char *cli_lower_word(char *in, char *out)
{
    int i, len;

    len = strlen(in);
    for (i = 0; i <= len; i++)
        out[i] = tolower(in[i]);
    return out;
}

/* Build array of command/syntax words */
static void cli_build_words(char *str, int *count, char **words, BOOL lower)
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
static void cli_parse_command(void)
{
    char       *cmd, *stx, *cmd2;
    char       cmd_buf[MAX_CMD_LEN], stx_buf[MAX_CMD_LEN], *cmd_words[64], *stx_words[64];
    char       cmd1_buf[MAX_WORD_LEN], cmd2_buf[MAX_WORD_LEN];
    int        i, i_cmd, i_stx, i_parm = 0, cmd_count, stx_count, max, len, j, error;
    cli_cmd_t  *cli_cmd, *match_list = NULL, *match_prev = NULL;
    BOOL       match, help = 0;
    cli_req_t  *req;
    cli_parm_t *parm;

    /* Read command and skip leading spaces */
    cmd = cmd_get();

    /* Remove CR */
    i = strlen(cmd);
    if (i)
        cmd[i-1] = '\0';

    /* Build array of command words */
    strcpy(cmd_buf, cmd);
    cli_build_words(cmd_buf, &cmd_count, cmd_words, 0);

    /* Remove trailing 'help' or '?' command */
    if (cmd_count > 1) {
        cmd = cli_lower_word(cmd_words[cmd_count-1], cmd1_buf);
        if (strcmp(cmd, "?") == 0 || strcmp(cmd, "help") == 0) {
            cmd_count--;
            help = 1;
        }
    }

    /* Compare entered command with each entry in CLI command table */
    for (cli_cmd = cli_cmd_list; cli_cmd != NULL; cli_cmd = cli_cmd->next) {
        if (strlen(cli_cmd->syntax) > MAX_CMD_LEN) {
            /* Command too long */
            continue;
        }

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

            if (i_cmd >= cmd_count)
                continue;

            cmd = cli_lower_word(cmd_words[i_cmd], cmd1_buf);
            if (strstr(stx, cmd) != stx) {
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
        printf("Invalid command\n");
    } else if (match_list->match_next == NULL) {
        /* One matching command */
        cli_cmd = match_list;

        /* Rebuild array of syntax words */
        strcpy(stx_buf, cli_cmd->syntax);
        cli_build_words(stx_buf, &stx_count, stx_words, 1);

        if (help) {
            for (parm = cli_parm_list; parm != NULL; parm = parm->next) {
                parm->done = FALSE;
            }
            cli_header_nl("Description", 0, 0);
            printf("%s.\n\n", cli_cmd->descr);
            cli_header_nl("Syntax", 0, 0);
            printf("%s\n\n", cli_cmd->syntax);
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
                        parm->done = TRUE;
                        if (i_stx == i_parm)
                            cli_header_nl("Parameters", 0, 0);
                        if (!(parm->flags & CLI_PARM_FLAG_NO_TXT)) {
                            printf("%s", parm->txt);
                            for (j = len; j < max; j++)
                                printf(" ");
                            printf(": ");
                        }
                        printf("%s\n", parm->help);
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
            BOOL end = 0, separator, skip_parm;

            /* Create default parameters */
            req = &cli_req;
            cli_req_default_set(req);

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
                    printf("Illegal state: %d\n", state);
                    return;
                }
                end = (strstr(stx, ")") != NULL);

#if 0
                printf("stx: %s, cmd: %s, state: %s->s\n",
                        stx, i_cmd < cmd_count ? cmd_words[i_cmd] : NULL,
                        state == CLI_STATE_IDLE ? "IDLE" :
                        state == CLI_STATE_PARSING ? "PARSING" :
                        state == CLI_STATE_ERROR ? "ERROR" : "DONE");
#endif
                /* Skip if separator or not in parsing state */
                if (separator || skip_parm)
                    continue;

                /* Lookup parameter */
                if ((parm = cli_parm_lookup(stx, cli_cmd)) == NULL) {
                    printf("Unknown parameter: %s\n", stx);
                    return;
                }

                if (i_cmd >= cmd_count) {
                    /* No more command words */
                    cmd = NULL;
                    error = 1;
                } else {
                    /* Parse command parameter */
                    do {
                        cmd = cli_lower_word(cmd_words[i_cmd], cmd1_buf);
                        cmd2 = ((i_cmd + 1) < cmd_count ?
                                cli_lower_word(cmd_words[i_cmd + 1], cmd2_buf) : NULL);

                        if (parm->parse_func == NULL) {
                            printf("missing parser function: %s\n", parm->txt);
                            error = 1;
                        } else {
                            req->parm_parsed = 1;
                            req->cmd = cmd;
                            req->cmd2 = cmd2;
                            req->stx = stx;
                            req->cmd_org = cmd_words[i_cmd];
                            error = parm->parse_func(req);
                        }

#if 0
                        printf("stx: %s, cmd: %s, error: %d\n", stx, cmd, error);
#endif
                        if (error)
                            break;
                        if (parm->flags & CLI_PARM_FLAG_SET)
                            req->set = 1;
                        i_cmd += req->parm_parsed;
                    } while (i_cmd < cmd_count && (parm->flags & CLI_PARM_FLAG_DUAL));
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
                if (cmd == NULL)
                    printf("Missing %s parameter\n\n", parm->txt);
                else
                    printf("Invalid %s parameter: %s\n\n", parm->txt, cmd);
                printf("Syntax:\n%s\n", cli_cmd->syntax);
                return;
            } /* for loop */
            if (i_parm) {
                if (i_cmd < cmd_count) {
                    printf("Invalid parameter: %s\n\n", cmd_words[i_cmd]);
                    printf("Syntax:\n%s\n", cli_cmd->syntax);
                    return;
                }
                if (state == CLI_STATE_ERROR) {
                    printf("Invalid parameter\n\n");
                    printf("Syntax:\n%s\n", cli_cmd->syntax);
                    return;
                }
            } /* Parameter handling */

            /* Handle CLI command */
            if (cli_cmd->func != NULL)
                cli_cmd->func(req);
            else
                printf("Command not implemented\n");
        }
    } else {
        printf("Available Commands:\n\n");
        for (cli_cmd = match_list; cli_cmd != NULL; cli_cmd = cli_cmd->match_next)
            printf("%s\n", cli_cmd->syntax);
    }
} /* cli_parse_command */

void vtss_appl_cli_task(void)
{
    do {
        if (cmd_ready()) {
            cli_parse_command();
            prompt();
        }
    } while (suspended);
}
