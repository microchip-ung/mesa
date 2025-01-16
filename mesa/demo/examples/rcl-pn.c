// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static int rcl_pn_init(int argc, const char *argv[])
{
    mesa_port_no_t      iport = ARGV_INT("iport", "Ingress port");
    mesa_rc             rc = MESA_RC_ERROR;
    mesa_port_map_t    *port_map;
    uint32_t            port_cnt = mesa_port_cnt(NULL);
    mesa_port_no_t      port_no;
    mesa_rcl_vid_conf_t conf;
    int                 pcp;
    mesa_rce_t          rce;

    EXAMPLE_BARRIER(argc);

    // Find port number mapping to RTE port
    if ((port_map = calloc(port_cnt, sizeof(*port_map))) == NULL) {
        return -1;
    }
    if (mesa_port_map_get(NULL, port_cnt, port_map) == MESA_RC_OK) {
        for (port_no = 0; port_no < port_cnt; port_no++) {
            if (port_map[port_no].chip_port == 4) {
                rc = MESA_RC_OK;
                break;
            }
        }
    }
    free(port_map);
    RC(rc);

    // Enable untagged RTP processing
    for (pcp = 0; pcp < MESA_PCP_CNT; pcp++) {
        conf.pcp[pcp] = 1;
    }
    RC(mesa_rcl_vid_add(NULL, 0, &conf));

    // Add RCE mapping to RTP ID
    RC(mesa_rce_init(NULL, &rce));
    rce.id = 1;
    rce.key.port_no = iport;
    rce.key.etype = MESA_RCL_ETYPE_PROFINET;
    rce.action.rtp_id = 1;
    rce.action.port_enable = 1;
    mesa_port_list_set(&rce.action.port_list, port_no, 1);
    RC(mesa_rce_add(NULL, MESA_RCE_ID_LAST, &rce));

    return 0;
}

static int rcl_pn_uninit(void)
{
    RC(mesa_rcl_vid_del(NULL, 0));
    RC(mesa_rce_del(NULL, 1));
    return 0;
}

static const char *rcl_pn_help(void) { return "RCL Profinet example\n"; }

EXAMPLE(pn, rcl_pn_init, NULL, rcl_pn_uninit, rcl_pn_help);
