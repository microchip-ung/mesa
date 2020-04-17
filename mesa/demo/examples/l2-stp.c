// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static const char *stp_help_txt = "\
This is a Spanning Tree example configuration.\n\
\n\
One port is in blocked state. One port is in forwarding state.\n\
The VID of the VLAN used in MSTP is set through parameter 'vid'. Value 0 means MSTP is NOT selected\n\
If MSTP is selected then MSTP instance 2 is used. Observe that only frames in selected VLAN are blocked on port in blocked state\n\
If MSTP is selected then the ingress port must also be selected.\n\
If MSTP is NOT selected any other ports can be used as ingress ports.\n\
";

static struct {
    mesa_msti_t            msti;
    mesa_vid_t             vid;
    mesa_port_no_t         ing_port;
    mesa_port_no_t         b_port;
    mesa_port_no_t         f_port;
    mesa_vlan_port_conf_t  vlan_conf;
} state;

static int init_port_configuration(mesa_port_no_t port)
{
    mesa_vlan_port_conf_t    vlan_conf;

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf));
    vlan_conf = state.vlan_conf;
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.untagged_vid = MESA_VID_NULL;
    vlan_conf.pvid = 1;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    return 0;
}

static int stp_init(int argc, const char *argv[])
{
    mesa_port_no_t     b_port = ARGV_INT("b-port", "Is the port in blocked state.");
    mesa_port_no_t     f_port = ARGV_INT("f-port", "Is the port in forwarding state.");
    mesa_port_no_t     ing_port = ARGV_OPT_INT("ing-port", "Is the ingress port when vid != 0. Default is 1", 1);
    uint32_t           vid = ARGV_OPT_INT("vid", "Is the classified VID of the MSTP VLAN. If != 0 then configured as MSTP. If == 0 then configured as STP. Default is 0", 0);
    mesa_port_list_t   port_list;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.msti = 2;
    state.vid = vid;
    state.b_port = b_port - 1;
    state.f_port = f_port - 1;
    state.ing_port = ing_port - 1;

    if (vid == 0) {
        // snippet_begin ex-stp-state-set
        RC(mesa_stp_port_state_set(NULL, state.b_port, MESA_STP_STATE_DISCARDING));
        RC(mesa_stp_port_state_set(NULL, state.f_port, MESA_STP_STATE_FORWARDING));
        // snippet_end
    } else {
        // Only forward on relevant ports
        mesa_port_list_clear(&port_list);
        mesa_port_list_set(&port_list, state.ing_port, TRUE);
        mesa_port_list_set(&port_list, state.b_port, TRUE);
        mesa_port_list_set(&port_list, state.f_port, TRUE);
        RC(mesa_vlan_port_members_set(NULL, vid, &port_list));

        RC(init_port_configuration(state.ing_port))

        // snippet_begin ex-mstp-state-set
        RC(mesa_mstp_vlan_msti_set(NULL, state.vid, state.msti));
        RC(mesa_mstp_port_msti_state_set(NULL, state.ing_port, state.msti, MESA_STP_STATE_FORWARDING));
        RC(mesa_mstp_port_msti_state_set(NULL, state.f_port, state.msti, MESA_STP_STATE_FORWARDING));
        RC(mesa_mstp_port_msti_state_set(NULL, state.b_port, state.msti, MESA_STP_STATE_DISCARDING));
        // snippet_end
    }

    return 0;
}

static int stp_clean()
{
    // Disable aggregation
    // snippet_begin ex-stp-disable
    RC(mesa_stp_port_state_set(NULL, state.b_port, MESA_STP_STATE_FORWARDING));
    RC(mesa_stp_port_state_set(NULL, state.f_port, MESA_STP_STATE_FORWARDING));
    if (state.vid != 0) {
        RC(mesa_mstp_vlan_msti_set(NULL, state.vid, 1));    /* MSTI 1 is default */
        RC(mesa_mstp_port_msti_state_set(NULL, state.b_port, state.msti, MESA_STP_STATE_FORWARDING));
        RC(mesa_mstp_port_msti_state_set(NULL, state.f_port, state.msti, MESA_STP_STATE_FORWARDING));
        RC(mesa_vlan_port_conf_set(NULL, state.ing_port, &state.vlan_conf));
    }
    // snippet_end

    return 0;
}

static const char* stp_help()
{
    return stp_help_txt;
}

EXAMPLE(stp, stp_init, NULL, stp_clean, stp_help);
