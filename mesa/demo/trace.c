// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <getopt.h>
#include <libgen.h>
#include <sys/time.h>

#include <vtss_phy_api.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t *trace_module_list;

static mscc_appl_trace_module_t trace_module_ail = {
    .name = "api_ail"
};

static mscc_appl_trace_module_t trace_module_cil = {
    .name = "api_cil"
};

#define TRACE_GROUP_CNT MESA_TRACE_GROUP_COUNT

static mscc_appl_trace_group_t trace_groups_ail[TRACE_GROUP_CNT] = {
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "port",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "phy",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "packet",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "afi",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "qos",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "l2",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "l3",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "security",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "evc",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "fdma",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "fdma_irq",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "reg_check",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "mpls",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "hwprot",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "hqos",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "macsec",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "vcap",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "oam",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "mrp",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "ts",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "clock",
        .level = MESA_TRACE_LEVEL_ERROR
    },
    {
        .name = "emul",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

static mscc_appl_trace_group_t trace_groups_cil[TRACE_GROUP_CNT];

static void printf_trace_head(const char *mname,
                              const char *gname,
                              const mesa_trace_level_t level,
                              const char *file,
                              const int line,
                              const char *function,
                              const char *lcont)
{
    struct timeval tv;
    int            h, m, s;
    const char     *p, *base_name = file;

    for (p = file; *p != 0; p++) {
        if (*p == '/' || *p == '\\') {
            base_name = (p + 1);
        }
    }

    (void)gettimeofday(&tv, NULL);
    h = (tv.tv_sec / 3600 % 24);
    m = (tv.tv_sec / 60 % 60);
    s = (tv.tv_sec % 60);
    printf("%u:%02u:%02u:%05lu %s/%s/%s %s(%u) %s%s",
           h, m, s, tv.tv_usec,
           mname,
           gname,
           level == MESA_TRACE_LEVEL_ERROR ? "error" :
           level == MESA_TRACE_LEVEL_INFO ? "info" :
           level == MESA_TRACE_LEVEL_DEBUG ? "debug" :
           level == MESA_TRACE_LEVEL_NOISE ? "noise" : "?",
           base_name, line, function, lcont);
}

static void mesa_printf_trace_head(const mesa_trace_layer_t layer,
                                   const mesa_trace_group_t group,
                                   const mesa_trace_level_t level,
                                   const char *file,
                                   const int line,
                                   const char *function,
                                   const char *lcont)
{
    printf_trace_head(layer == MESA_TRACE_LAYER_AIL ? "ail" : "cil",
                      group < TRACE_GROUP_CNT ? trace_groups_ail[group].name : "?",
                      level,
                      file,
                      line,
                      function,
                      lcont);
}

void mesa_callout_trace_printf(const mesa_trace_layer_t layer,
                               const mesa_trace_group_t group,
                               const mesa_trace_level_t level,
                               const char *file,
                               const int line,
                               const char *function,
                               const char *format,
                               va_list args)
{
    mesa_printf_trace_head(layer, group, level, file, line, function, ": ");
    vprintf(format, args);
    printf("\n");
    fflush(stdout);
}

void mscc_appl_trace_printf(const char *mname,
                            const char *gname,
                            const mesa_trace_level_t level,
                            const char *file,
                            const int line,
                            const char *function,
                            const char *format,
                            ...)
{
    va_list args;

    va_start(args, format);
    mscc_appl_trace_vprintf(mname, gname, level, file, line, function, format, args);
    va_end(args);
}

void mscc_phy_vtrace_printf(mepa_trace_group_t group,
                            mepa_trace_level_t level,
                            const char *location,
                            uint32_t line,
                            const char *format,
                            va_list args)
{
    mesa_trace_layer_t layer = MESA_TRACE_LAYER_CIL;
    mesa_trace_group_t grp;
    mesa_trace_level_t lvl;

    // Map from MEPA to MESA trace group/level
    grp = (group == MEPA_TRACE_GRP_TS ? MESA_TRACE_GROUP_TS : MESA_TRACE_GROUP_PHY);
    lvl = (level > MEPA_TRACE_LVL_ERROR ? MESA_TRACE_LEVEL_NONE :
           level > MEPA_TRACE_LVL_WARNING ? MESA_TRACE_LEVEL_ERROR :
           level > MEPA_TRACE_LVL_DEBUG ? MESA_TRACE_LEVEL_INFO :
           level > MEPA_TRACE_LVL_NOISE ? MESA_TRACE_LEVEL_DEBUG :
           MESA_TRACE_LEVEL_NOISE);
    if (trace_groups_cil[grp].level >= lvl) {
        mesa_callout_trace_printf(layer, grp, lvl, "x.c", line, location, format, args);
    }
}

void mscc_phy_trace_printf(mepa_trace_group_t group,
                           mepa_trace_level_t level,
                           const char *location,
                           uint32_t line,
                           const char *format,
                           ...)
{
    va_list args;

    va_start(args, format);
    mscc_phy_vtrace_printf(group, level, location, line, format, args);
    va_end(args);
}

void mscc_mepa_trace_printf(const mepa_trace_data_t *data,
                            va_list                  args)
{
    mscc_phy_vtrace_printf(data->group, data->level, data->location, data->line,
                           data->format, args);
}


void mscc_appl_trace_vprintf(const char *mname,
                             const char *gname,
                             const mesa_trace_level_t level,
                             const char *file,
                             const int line,
                             const char *function,
                             const char *format,
                             va_list args)
{
    printf_trace_head(mname, gname, level, file, line, function, ": ");
    vprintf(format, args);
    printf("\n");
    fflush(stdout);
}

static void trace_hex(const unsigned char *byte_p, int byte_cnt)
{
    int i, j;

    for (i = 0; i < byte_cnt; i++) {
        j = (i == (byte_cnt - 1) ? 15 : (i % 16));
        if (j == 0) {
            printf("%04x: ", i);
        }
        printf("%02x%s", byte_p[i], j == 15 ? "\n" : (j & 3) == 3 ? "-" : " ");
        if (j == 15) {
            fflush(stdout);
        }
    }
}

void mscc_appl_trace_hex(const char *mname,
                         const char *gname,
                         const mesa_trace_level_t level,
                         const char *file,
                         const int line,
                         const char *function,
                         const unsigned char *byte_p,
                         const int byte_cnt)
{
    char buf[32];

    sprintf(buf, ": hex dump, %u bytes\n", byte_cnt);
    printf_trace_head(mname, gname, level, file, line, function, buf);
    trace_hex(byte_p, byte_cnt);
}

void mesa_callout_trace_hex_dump(const mesa_trace_layer_t layer,
                                 const mesa_trace_group_t group,
                                 const mesa_trace_level_t level,
                                 const char               *file,
                                 const int                line,
                                 const char               *function,
                                 const unsigned char      *byte_p,
                                 const int                byte_cnt)
{
    mesa_printf_trace_head(layer, group, level, file, line, function, "\n");
    trace_hex(byte_p, byte_cnt);
}

/* ================================================================= *
 *  CLI
 * ================================================================= */

#define TRACE_NAME_MAX 64

typedef struct {
    char               module_name[TRACE_NAME_MAX];
    char               group_name[TRACE_NAME_MAX];
    mesa_trace_level_t level;
} trace_cli_req_t;

static void trace_control(char *module_name, char *group_name, mesa_trace_level_t level, mesa_bool_t set)
{
    mscc_appl_trace_module_t *module;
    mscc_appl_trace_group_t  *group;
    int                      first = 1;
    int                      i;
    mesa_trace_conf_t        conf;

    for (module = trace_module_list; module != NULL; module = module->next) {
        if (strlen(module_name) != 0 && strstr(module->name, module_name) != module->name) {
            continue;
        }

        for (group = module->group_list; group != NULL; group = group->next) {
            if (strlen(group_name) != 0 && strstr(group->name, group_name) != group->name) {
                continue;
            }
            if (set) {
                group->level = level;
            } else {
                if (first) {
                    cli_table_header("Module   Group       Level");
                    first = 0;
                }
                level = group->level;
                cli_printf("%-9s%-12s%s\n",
                           module->name,
                           group->name,
                           level == MESA_TRACE_LEVEL_NONE ? "off" :
                           level == MESA_TRACE_LEVEL_ERROR ? "error" :
                           level == MESA_TRACE_LEVEL_INFO ? "info" :
                           level == MESA_TRACE_LEVEL_DEBUG ? "debug" :
                           level == MESA_TRACE_LEVEL_NOISE ? "noise" : "?");
            }
        }
    }
    if (set) {
        for (i = 0; i < TRACE_GROUP_CNT; i++) {
            if (mesa_trace_conf_get(i, &conf) == MESA_RC_OK) {
                conf.level[MESA_TRACE_LAYER_AIL] = trace_groups_ail[i].level;
                conf.level[MESA_TRACE_LAYER_CIL] = trace_groups_cil[i].level;
                mesa_trace_conf_set(i, &conf);
            }
        }
    }
}

static void cli_cmd_debug_trace(cli_req_t *req)
{
    trace_cli_req_t *mreq = req->module_req;

    trace_control(mreq->module_name, mreq->group_name, mreq->level, req->set);
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Debug Trace [<module>] [<group>] [off|error|info|debug|noise]",
        "Set or show the trace level for group",
        cli_cmd_debug_trace
    },
};

static int cli_parm_wildcard(cli_req_t *req)
{
    return (strcmp(req->cmd, "*") == 0);
}

static int cli_parm_trace_module(cli_req_t *req)
{
    mscc_appl_trace_module_t *module;
    trace_cli_req_t          *mreq = req->module_req;

    if (cli_parm_wildcard(req)) {
        // Wildcard module accepted
        return 0;
    }

    for (module = trace_module_list; module != NULL; module = module->next) {
        if (strstr(module->name, req->cmd) == module->name) {
            // At least one module matches
            strcpy(mreq->module_name, req->cmd);
            return 0;
        }
    }
    return 1;
}

static int cli_parm_trace_group(cli_req_t *req)
{
    mscc_appl_trace_module_t *module;
    mscc_appl_trace_group_t  *group;
    trace_cli_req_t          *mreq = req->module_req;

    if (cli_parm_wildcard(req)) {
        // Wildcard group accepted
        return 0;
    }

    for (module = trace_module_list; module != NULL; module = module->next) {
        if (strlen(mreq->module_name) != 0 && strstr(module->name, mreq->module_name) != module->name) {
            continue;
        }
        for (group = module->group_list; group != NULL; group = group->next) {
            if (strstr(group->name, req->cmd) == group->name) {
                // At least one group matches
                strcpy(mreq->group_name, req->cmd);
                return 0;
            }
        }
    }
    return 1;
}

static int cli_parm_keyword(cli_req_t *req)
{
    const char      *found;
    trace_cli_req_t *mreq = req->module_req;

    if ((found = cli_parse_find(req->cmd, req->stx)) == NULL)
        return 1;

    if (!strncmp(found, "debug", 5))
        mreq->level = MESA_TRACE_LEVEL_DEBUG;
    else if (!strncmp(found, "error", 5))
        mreq->level = MESA_TRACE_LEVEL_ERROR;
    else if (!strncmp(found, "info", 4))
        mreq->level = MESA_TRACE_LEVEL_INFO;
    else if (!strncmp(found, "noise", 5))
        mreq->level = MESA_TRACE_LEVEL_NOISE;
    else if (!strncmp(found, "off", 3))
        mreq->level = MESA_TRACE_LEVEL_NONE;
    else
        cli_printf("no match:%s\n",found);

    return 0;
}

static cli_parm_t cli_parm_table[] = {
    {
        "<module>",
        "Trace module, default: All modules",
        CLI_PARM_FLAG_NONE,
        cli_parm_trace_module
    },
    {
        "<group>",
        "Trace group name, default: All groups",
        CLI_PARM_FLAG_NONE,
        cli_parm_trace_group,
        cli_cmd_debug_trace
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
};

static void trace_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table)/sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

static void trace_module_register(mscc_appl_trace_module_t *module)
{
    mscc_appl_trace_module_t *cur, *prev = NULL;
    int                      cmp;

    // Build sorted list of modules
    for (cur = trace_module_list; cur != NULL; prev = cur, cur = cur->next) {
        cmp = strcmp(cur->name, module->name);
        if (cmp == 0) {
            fprintf(stderr, "duplicate trace module: %s\n", cur->name);
            return;
        } else if (cmp > 0) {
            // Found greater name
            break;
        }
    }
    if (prev == NULL) {
        // Insert first
        module->next = trace_module_list;
        trace_module_list = module;
    } else {
        // Insert after previous entry
        module->next = prev->next;
        prev->next = module;
    }
}

void mscc_appl_trace_register(mscc_appl_trace_module_t *module,
                              mscc_appl_trace_group_t *group_table,
                              uint32_t group_count)
{
    mscc_appl_trace_group_t *group, *cur, *prev;
    int                     i, cmp;

    /* Build sorted list of groups */
    module->group_list = NULL;
    for (i = 0; i < group_count; i++) {
        group = &group_table[i];
        for (cur = module->group_list, prev = NULL; cur != NULL; prev = cur, cur = cur->next) {
            cmp = strcmp(cur->name, group->name);
            if (cmp == 0) {
                fprintf(stderr, "duplicate trace group: %s for module: %s\n", cur->name, module->name);
                return;
            } else if (cmp > 0) {
                // Found greater name
                break;
            }
        }
        if (prev == NULL) {
            // Insert first
            group->next = module->group_list;
            module->group_list = group;
        } else {
            // Insert after previous entry
            group->next = prev->next;
            prev->next = group;
        }
    }
    trace_module_register(module);
}

static mesa_rc trace_option(char *parm)
{
    char               *module_name, *group_name, *level_name, c;
    mesa_trace_level_t level;

    module_name = strtok(parm, ":");
    group_name = strtok(NULL, ":");
    level_name = strtok(NULL, ":");

    if (module_name == NULL || group_name == NULL || level_name == NULL) {
        fprintf(stderr, "please specify <module>:<group>:<level>\n");
        return MESA_RC_ERROR;
    }
    if (*module_name == '*') {
        *module_name = 0;
    }
    if (*group_name == '*') {
        *group_name = 0;
    }
    c = (level_name != NULL && strlen(level_name) ? level_name[0] : 'z');
    level = (c == 'o' ? MESA_TRACE_LEVEL_NONE :
             c == 'e' ? MESA_TRACE_LEVEL_ERROR :
             c == 'i' ? MESA_TRACE_LEVEL_INFO :
             c == 'd' ? MESA_TRACE_LEVEL_DEBUG :
             c == 'n' ? MESA_TRACE_LEVEL_NOISE : MESA_TRACE_LEVEL_COUNT);
    if (level == MESA_TRACE_LEVEL_COUNT) {
        fprintf(stderr, "illegal trace level\n");
        return MESA_RC_ERROR;
    }
    trace_control(module_name, group_name, level, 1);
    return MESA_RC_OK;
}

static mscc_appl_opt_t trace_opt = {
    "t:",
    "<module>:<group>:<level>",
    "Set trace level for <module> and <group>, use '*' for wildcard" ,
    trace_option
};

void mscc_appl_trace_init(mscc_appl_init_t *init)
{
    int i;

    switch (init->cmd) {
        // Register API trace groups for AIL/CIL*/
    case MSCC_INIT_CMD_REG:
        for (i = 0; i < TRACE_GROUP_CNT; i++) {
            trace_groups_cil[i] = trace_groups_ail[i];
        }
        mscc_appl_trace_register(&trace_module_ail, trace_groups_ail, TRACE_GROUP_CNT);
        mscc_appl_trace_register(&trace_module_cil, trace_groups_cil, TRACE_GROUP_CNT);

        // Register startup options
        mscc_appl_opt_reg(&trace_opt);
        break;

    case MSCC_INIT_CMD_INIT:
        trace_cli_init();
        break;

    default:
        break;
    }
}
