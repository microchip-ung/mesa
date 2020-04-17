// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "vtss_api.h"

#if defined(VTSS_FEATURE_LAYER2)

#include <stdarg.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include "vtss_appl.h"
#include "vtss_appl_cli.h"
#include "vtss_version.h"

BOOL vtss_appl_quiet;

/* ================================================================= *
 *  Trace
 * ================================================================= */

vtss_trace_conf_t vtss_appl_trace_conf = {
    .level = {VTSS_TRACE_LEVEL_ERROR, VTSS_TRACE_LEVEL_ERROR}
};

static void printf_trace_head(const vtss_trace_layer_t layer,
                              const vtss_trace_group_t group,
                              const vtss_trace_level_t level,
                              const char *file,
                              const int line,
                              const char *function,
                              const char *lcont)
{
    time_t  t;
    int     h, m, s;

    t = time(NULL);
    h = (t / 3600 % 24);
    m = (t / 60 % 60);
    s = (t % 60);
    printf("%u:%02u:%02u %s/%s %s%s",
           h, m, s,
           layer == VTSS_APPL_TRACE_LAYER ? "APPL": layer == VTSS_TRACE_LAYER_AIL ? "AIL" : "CIL",
           level == VTSS_TRACE_LEVEL_ERROR ? "Error" :
           level == VTSS_TRACE_LEVEL_INFO ? "Info " :
           level == VTSS_TRACE_LEVEL_DEBUG ? "Debug" :
           level == VTSS_TRACE_LEVEL_NOISE ? "Noise" : "?????",
           function, lcont);
}

/* Trace callout function */
void vtss_callout_trace_printf(const vtss_trace_layer_t layer,
                               const vtss_trace_group_t group,
                               const vtss_trace_level_t level,
                               const char *file,
                               const int line,
                               const char *function,
                               const char *format,
                               ...)
{
    va_list va;
    printf_trace_head(layer, group, level, file, line, function, ": ");

    va_start(va, format);
    vprintf(format, va);
    va_end(va);
    printf("\n");
}

/* Trace hex-dump callout function */
void vtss_callout_trace_hex_dump(const vtss_trace_layer_t layer,
                                 const vtss_trace_group_t group,
                                 const vtss_trace_level_t level,
                                 const char               *file,
                                 const int                line,
                                 const char               *function,
                                 const unsigned char      *byte_p,
                                 const int                byte_cnt)
{
    int i;

    printf_trace_head(layer, group, level, file, line, function, "\n");

    for (i= 0; i < byte_cnt; i += 16) {
        int j = 0;
        printf("%04x:", i);
        while (j+i < byte_cnt && j < 16) {
            printf(" %02x", byte_p[i+j]);
            j++;
        }
        putchar('\n');
    }
}

/* ================================================================= *
 *  Memory allocation
 * ================================================================= */

// Pre-declare these to avoid warnings when built on some platforms.
void *vtss_callout_malloc(size_t size, vtss_mem_flags_t flags);
void  vtss_callout_free(void *ptr, vtss_mem_flags_t flags);

/* Alloc/Free callout functions */
void *vtss_callout_malloc(size_t size, vtss_mem_flags_t flags)
{
    return malloc(size);
}

void vtss_callout_free(void *ptr, vtss_mem_flags_t flags)
{
    free(ptr);
}

/* ================================================================= *
 *  API lock/unlock functions
 * ================================================================= */
BOOL api_locked = FALSE;

void vtss_callout_lock(const vtss_api_lock_t *const lock)
{
    T_N("Locking function %s", lock->function);
    // For testing we don't get a deadlock. The API must be unlocked before "locking"
    if (api_locked) {
        T_E("API lock problem");
    }
    api_locked = TRUE;
}

void vtss_callout_unlock(const vtss_api_lock_t *const lock)
{
    T_N("Unlocking function %s", lock->function);
    // For testing we don't get a deadlock. vtss_callout_lock must have been called before vtss_callout_unlock is called.
    if (!api_locked) {
        T_E("API unlock problem");
    }
    api_locked = FALSE;
}

/* ================================================================= *
 *  Option parsing
 * ================================================================= */

static struct {
    int group;
    const char *name;
} groups[] = {
    { VTSS_TRACE_GROUP_DEFAULT,      "default" },
    { VTSS_TRACE_GROUP_PORT,         "port" },
    { VTSS_TRACE_GROUP_PHY,          "phy" },
    { VTSS_TRACE_GROUP_PACKET,       "packet" },
    { VTSS_TRACE_GROUP_QOS,          "qos" },
    { VTSS_TRACE_GROUP_L2,           "l2" },
    { VTSS_TRACE_GROUP_L3,           "l3" },
    { VTSS_TRACE_GROUP_SECURITY,     "security" },
    { VTSS_TRACE_GROUP_EVC,          "evc" },
    { VTSS_TRACE_GROUP_FDMA_NORMAL,  "fdma_normal" },
    { VTSS_TRACE_GROUP_FDMA_IRQ,     "fdma_irq" },
    { VTSS_TRACE_GROUP_REG_CHECK,    "reg_check" },
    { VTSS_TRACE_GROUP_MPLS,         "mpls" },
    { VTSS_TRACE_GROUP_HW_PROT,      "hwprot" },
    { VTSS_TRACE_GROUP_HQOS,         "hqos" },
    { VTSS_TRACE_GROUP_MACSEC,       "macsec" },
    { VTSS_TRACE_GROUP_VCAP,         "vcap" },
    { VTSS_TRACE_GROUP_OAM,          "oam" },
    { VTSS_TRACE_GROUP_TS,           "ts" },
    { VTSS_TRACE_GROUP_CLOCK,        "clock"},
    { VTSS_TRACE_GROUP_COUNT,        NULL },
};

static int str2layer(const char *layer)
{
    if (strcmp(layer, "ail") == 0) {
        return VTSS_TRACE_LAYER_AIL;
    } else if (strcmp(layer, "cil") == 0) {
        return VTSS_TRACE_LAYER_CIL;
    }
    printf("'%s': layer unrecognized - use (app|ail|cil))\n", layer);
    return -1;
}

static int str2group(const char *group)
{
    int i;
    for(i = 0; groups[i].name != NULL; i++) {
        if(strcmp(groups[i].name, group) == 0) {
            return groups[i].group;
        }
    }
    if (strcmp(group, "show") != 0) {
        printf("'%s': group unrecognized - use 'show' to list\n", group);
    }
    return -1;
}

static int str2level(const char *level)
{
    if (strcmp(level, "none") == 0) {
        return VTSS_TRACE_LEVEL_NONE;
    } else if (strcmp(level, "error") == 0) {
        return VTSS_TRACE_LEVEL_ERROR;
    } else if (strcmp(level, "info") == 0) {
        return VTSS_TRACE_LEVEL_INFO;
    } else if (strcmp(level, "debug") == 0) {
        return VTSS_TRACE_LEVEL_DEBUG;
    } else if (strcmp(level, "noise") == 0) {
        return VTSS_TRACE_LEVEL_NOISE;
    }
    printf("'%s': level unrecognized - use (none|error|info|debug|noise)\n", level);
    return -1;
}

int vtss_appl_parse_options(int argc, char **argv, vtss_appl_opt *opt)
{
    int option;

    while ((option = getopt(argc, argv, "hvqd:t:")) != -1) {
        switch (option) {
        case '?':
        case 'h': /* Help */
            printf("vtss_appl [-v] [-q] [-d <level>] [-t[<layer>][:<group>][:<level>]] [-- <board-specific args>]\n");
            printf("-v: Show version\n");
            printf("-d: Enable application trace\n");
            printf("-q: Quiet opertation (no CLI)\n");
            printf("-t: Show or set trace level for a specific layer and group. (Multiple occurrences allowed)\n");
            return 1;
        case 'v': /* Version */
            printf("Version: %s\n", vtss_version_string);
            printf("Date   : %s\n", __DATE__ ", " __TIME__);
            return 1;
        case 'q': /* Quiet */
            opt->quiet = TRUE;
            break;
        case 'd':
        {
            int level = str2level(optarg);
            if (level < 0) {
                return 1;
            } else {
                printf("Setting trace level for: layer '%s', group '%s', level '%s'\n", "app", "all", optarg);
                vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL]  = level;
                vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL]  = level;
            }
        }
        break;
        case 't':
        {
            int group, layer, level;
            const char *s_layer, *s_group, *s_level;
            char *saveptr = NULL;

            s_layer = strtok_r(optarg, ":", &saveptr);
            s_group = strtok_r(NULL, ":", &saveptr);
            s_level = strtok_r(NULL, ":", &saveptr);

            if(s_layer == NULL) {
                s_layer = "ail"; /* Default */
            }
            if(s_group == NULL) {
                s_group = "default"; /* Default */
            }
            if(s_level == NULL) {
                s_level = "debug"; /* Default */
            }

            layer = str2layer(s_layer);
            if (layer < 0) {
                return 1;
            }
            group = str2group(s_group);
            if (group < 0) {
                if (strcmp(s_group, "show") == 0) {
                    int i;
                    printf("Trace groups: ");
                    for(i = 0; groups[i].name != NULL; i++) {
                        printf("'%s'| ", groups[i].name);
                    }
                    printf("'show'\n");
                }
                return 1;
            }
            level = str2level(s_level);
            if(level < 0) {
                return 1;
            }

            printf("Setting trace level for: layer '%s', group '%s', level '%s'\n", s_layer, s_group, s_level);

            {
                vtss_trace_conf_t  conf;
                if(vtss_trace_conf_get(group, &conf) == VTSS_RC_OK) {
                    conf.level[layer]  = level;
                    vtss_trace_conf_set(group, &conf);
                } else {
                    T_E("vtss_trace_conf_get(%d) fails", group);
                }
            }
            break;
        }
        default:
            break;              /* Unknow/board option */
        }
    }
    opt->count = optind;
    return 0;
}

/* ================================================================= *
 *  Utilities
 * ================================================================= */

/* Convert from internal to user port number */
vtss_uport_no_t iport2uport(vtss_port_no_t iport)
{
    return (iport + 1 - VTSS_PORT_NO_START);
}

/* Convert from user to internal port number */
vtss_port_no_t uport2iport(vtss_uport_no_t uport)
{
    return (uport == 0 ? VTSS_PORT_NO_NONE : (uport - 1 + VTSS_PORT_NO_START));
}
#endif /* VTSS_FEATURE_LAYER2/OTN */
