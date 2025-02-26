// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {.name = "mac"};

enum { TRACE_GROUP_DEFAULT, TRACE_GROUP_CNT };

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {.name = "default", .level = MESA_TRACE_LEVEL_ERROR},
};

typedef struct {
    uint8_t  mac[6];
    uint32_t age_time;
} mac_cli_req_t;

static void cli_cmd_mac_add(cli_req_t *req)
{
    mesa_mac_table_entry_t entry;
    int                    i;
    mesa_port_no_t         iport;
    mac_cli_req_t         *mreq = req->module_req;

    memset(&entry, 0, sizeof(entry));
    entry.locked = 1;
    entry.vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++) {
        entry.vid_mac.mac.addr[i] = mreq->mac[i];
    }
    for (iport = 0; iport < mesa_port_cnt(NULL); iport++) {
        mesa_port_list_set(&entry.destination, iport, req->port_list[iport2uport(iport)]);
    }
    mesa_mac_table_add(NULL, &entry);
}

static void cli_cmd_mac_del(cli_req_t *req)
{
    mesa_vid_mac_t vid_mac;
    int            i;
    mac_cli_req_t *mreq = req->module_req;

    vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++) {
        vid_mac.mac.addr[i] = mreq->mac[i];
    }
    mesa_mac_table_del(NULL, &vid_mac);
}

static void cli_mac_print(mesa_mac_table_entry_t *entry, mesa_bool_t first)
{
    char buf[64];

    if (first)
        cli_table_header("Type    VID  MAC Address        Ports");
    cli_printf("%-7s %-4d %s  ",
               entry->index_table ? "Index"
               : entry->locked    ? "Static"
                                  : "Dynamic",
               entry->vid_mac.vid, cli_mac_txt(entry->vid_mac.mac.addr, buf));
    cli_printf("%s%s\n", cli_port_list_txt(&entry->destination, buf),
               entry->copy_to_cpu ? ",CPU" : "");
}

static void cli_cmd_mac_lookup(cli_req_t *req)
{
    mesa_mac_table_entry_t entry;
    int                    i;
    mac_cli_req_t         *mreq = req->module_req;

    entry.vid_mac.vid = req->vid;
    for (i = 0; i < 6; i++) {
        entry.vid_mac.mac.addr[i] = mreq->mac[i];
    }
    if (mesa_mac_table_get(NULL, &entry.vid_mac, &entry) == MESA_RC_OK) {
        cli_mac_print(&entry, 1);
    }
}

static void cli_cmd_mac_dump(cli_req_t *req)
{
    mesa_mac_table_entry_t entry;
    mesa_bool_t            first = 1;

    memset(&entry, 0, sizeof(entry));
    while (mesa_mac_table_get_next(NULL, &entry.vid_mac, &entry) == MESA_RC_OK) {
        cli_mac_print(&entry, first);
        first = 0;
    }
}

static void cli_cmd_mac_flush(cli_req_t *req) { mesa_mac_table_flush(NULL); }

static void cli_cmd_mac_age_time(cli_req_t *req)
{
    mesa_mac_table_age_time_t age_time;
    mac_cli_req_t            *mreq = req->module_req;

    if (req->set) {
        mesa_mac_table_age_time_set(NULL, mreq->age_time);
    } else if (mesa_mac_table_age_time_get(NULL, &age_time) == MESA_RC_OK) {
        cli_printf("Age Time: %u\n", age_time);
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {"MAC Add <mac_addr> <port_list> [<vid>]", "Add MAC address table entry",             cli_cmd_mac_add     },
    {"MAC Delete <mac_addr> [<vid>]",          "Delete MAC address entry",                cli_cmd_mac_del     },
    {"MAC Lookup <mac_addr> [<vid>]",          "Lookup MAC address entry",                cli_cmd_mac_lookup  },
    {"MAC Dump",                               "Show sorted list of MAC address entries", cli_cmd_mac_dump    },
    {"MAC Flush",                              "Flush all learned entries",               cli_cmd_mac_flush   },
    {"MAC Agetime [<age_time>]",               "Set or show the MAC address age timer",   cli_cmd_mac_age_time},
};

static int cli_parm_mac(cli_req_t *req)
{
    uint32_t       i, mac[6];
    int            error = 1;
    mac_cli_req_t *mreq = req->module_req;

    if (sscanf(req->cmd, "%2x-%2x-%2x-%2x-%2x-%2x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4],
               &mac[5]) == 6) {
        for (i = 0; i < 6; i++)
            mreq->mac[i] = (mac[i] & 0xff);
        error = 0;
    }
    return error;
}

static int cli_parm_age_time(cli_req_t *req)
{
    int            error;
    uint32_t       value;
    mac_cli_req_t *mreq = req->module_req;

    error = (cli_parm_u32(req, &value, 0, 1000000) || (value != 0 && value < 10));
    if (!error)
        mreq->age_time = value;
    return error;
}

static cli_parm_t cli_parm_table[] = {
    {"<mac_addr>", "MAC address (xx-xx-xx-xx-xx-xx)",                           CLI_PARM_FLAG_SET, cli_parm_mac},
    {"<age_time>", "MAC address age time (10-1000000), default: Show age time", CLI_PARM_FLAG_SET,
     cli_parm_age_time                                                                                         },
};

static void mac_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table) / sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }

    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table) / sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

void mscc_appl_mac_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT: mac_cli_init(); break;

    default: break;
    }
}
