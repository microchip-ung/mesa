// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static mesa_vid_t  vid = 100;
static mesa_ace_id_t acl_id = 1;

static const char *ts_help_txt = "\
This is a Time Stamping Transparent Clock example\n\
\n\
One port will be ingress. One port will be egress.\n\
When a SYNC frame is injected into the ingress port it will be forwarded to the egress port with updated correction field.\n\
";

static struct {
    mesa_port_no_t           ing_port;
    mesa_port_no_t           eg_port;
    mesa_vlan_port_conf_t    vlan_conf[2];
    mesa_timeinterval_t      delay_asymmetry[2];
} state;

static int init_port_configuration(mesa_port_no_t port,  mesa_timeinterval_t asymmetry,  uint32_t idx)
{
    mesa_vlan_port_conf_t    vlan_conf;

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[idx]));
    vlan_conf = state.vlan_conf[idx];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_UNAWARE;
    vlan_conf.pvid = vid;
    vlan_conf.untagged_vid = vid;
    vlan_conf.frame_type = MESA_VLAN_FRAME_ALL;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    // snippet_begin ex-delay-asymmetry-set
    RC(mesa_ts_delay_asymmetry_get(NULL, port, &state.delay_asymmetry[idx]));
    asymmetry<<=16;
    RC(mesa_ts_delay_asymmetry_set(NULL, port, &asymmetry));
    // snippet_end

    return 0;
}

static int ts_init(int argc, const char *argv[])
{
    mesa_port_no_t    ing_port, eg_port;
    uint32_t          delay_mode, asymmetry;
    mesa_port_list_t  port_list;
    mesa_ace_t        ace;

    ing_port = ARGV_INT("ing-port","Is the ingress port for SYNC frame injection.");
    eg_port =  ARGV_INT("eg-port", "Is the egress port for corrected SYNC frames extraction.");
    delay_mode = ARGV_OPT_INT("delay_mode", "Is the asymmetry delay mode. Value 0 means no delay - 1 means add delay - 2 means subtract delay. Default is 0", 0);
    asymmetry = ARGV_OPT_INT("asymmetry", "The asymmetry delay value in nano seconds. Default is 0", 0);

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.ing_port = ing_port - 1;
    state.eg_port = eg_port - 1;

    RC(init_port_configuration(state.ing_port, asymmetry, 0))
    RC(init_port_configuration(state.eg_port, asymmetry, 1))

    // Only forward on relevant ports
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, state.ing_port, TRUE);
    mesa_port_list_set(&port_list, state.eg_port, TRUE);
    RC(mesa_vlan_port_members_set(NULL, vid, &port_list));

    // snippet_begin ex-one-step-ace-add
    // Add the ONE step SYNCE classification ACE entry
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, state.ing_port, TRUE);
    RC(mesa_ace_init(NULL, MESA_ACE_TYPE_ETYPE, &ace));
    ace.id = acl_id;
    ace.port_list = port_list;
    ace.action.ptp_action = (delay_mode == 0) ? MESA_ACL_PTP_ACTION_ONE_STEP : (delay_mode == 1) ? MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY : MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1;
    RC(mesa_ace_add(NULL, MESA_ACE_ID_LAST, &ace));
    // snippet_end

    return 0;
}

static int ts_clean()
{
    mesa_port_list_t  port_list;

    RC(mesa_vlan_port_conf_set(NULL, state.ing_port, &state.vlan_conf[0]));
    RC(mesa_vlan_port_conf_set(NULL, state.eg_port, &state.vlan_conf[1]));

    RC(mesa_ts_delay_asymmetry_set(NULL, state.ing_port, &state.delay_asymmetry[0]));
    RC(mesa_ts_delay_asymmetry_set(NULL, state.eg_port, &state.delay_asymmetry[1]));

    mesa_port_list_clear(&port_list);
    RC(mesa_vlan_port_members_set(NULL, vid, &port_list));

    RC(mesa_ace_del(NULL, acl_id));

    return 0;
}

static char ret_string[500];
static const char* ts_help()
{
    uint32_t cnt;

    cnt = sprintf(ret_string, "%s", ts_help_txt);
    cnt += sprintf(ret_string+cnt, "VLAN forwarding VID is %u\n", vid);
    return ret_string;
}

EXAMPLE(transparent_clock, ts_init, NULL, ts_clean, ts_help);
