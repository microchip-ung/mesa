// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

#define NO_EXP 0xFFFFFFFF
#define IFLOW_ID_NONE 0

static uint8_t                test_mc_addr[6] = {0x01,0x15,0x4E,0x00,0x00,0x01};
static uint8_t                test_uc_addr[6] = {0,0,0,0,5,7};
static mesa_mrp_ring_role_t   ring_role = MESA_MRP_RING_ROLE_MANAGER;
static mesa_mrp_ring_role_t   in_ring_role = MESA_MRP_RING_ROLE_CLIENT;
static uint32_t               tst_interval = 333333;
static uint32_t               tst_mon_count = 3;
static uint32_t               itst_interval = 333333;
static uint32_t               itst_mon_count = 3;

static const char *mrp_help_txt = "\
This is a Media Redundancy Protocol (MRP) test.\n\
\n\
There will be configured a MRP instance in a interconnected node with Manager ring role\n\
and Client interconnect role.\n\
There will be tree ports - the primary, the secondary and the interconnection port.\n\
Test frames are transmitted on the Primary and Secondary port.\n\
In_Test frames are transmitted on the Interconnection port.\n\
After MRP instance is added the ring state is default closed.\n\
The ring is opened after add to increment the Test PDU transaction counter.\n\
";

static struct {
    mesa_port_no_t           p_port;
    mesa_port_no_t           s_port;
    mesa_port_no_t           i_port;
    mesa_mrp_idx_t           mrp_idx;
    mesa_vlan_port_conf_t    vlan_conf[2];
} state;

static int init_port_configuration(mesa_port_no_t port,  uint32_t idx)
{
    mesa_vlan_port_conf_t    vlan_conf;

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[idx]));
    vlan_conf = state.vlan_conf[idx];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.frame_type = MESA_VLAN_FRAME_ALL;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    return 0;
}

static int mrp_init(int argc, const char *argv[])
{
    mesa_port_no_t         p_port = ARGV_INT("p-port", "Is the primary port.");
    mesa_port_no_t         s_port = ARGV_INT("s-port", "Is the secondary port.");
    mesa_port_no_t         i_port = ARGV_INT("i-port", "Is the interconnection port.");
    mesa_mrp_conf_t        mrp_conf;
    mesa_mrp_tst_loc_conf_t loc_conf;
    mesa_packet_rx_queue_t cpu_queue = 7;
    uint8_t                frame[1600];
    mesa_packet_rx_info_t  rx_info;
    mesa_vop_conf_t        vop_conf;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.mrp_idx = 0;
    state.p_port = p_port - 1;
    state.s_port = s_port - 1;
    state.i_port = i_port - 1;

    // Must be called to enable rx packet polling
    (void)mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info);

    RC(init_port_configuration(state.p_port, 0))
    RC(init_port_configuration(state.s_port, 0))
    RC(init_port_configuration(state.i_port, 0))

    // snippet_begin ex-vop-config
    // Enable the VOP
    RC(mesa_vop_conf_get(NULL, &vop_conf));
    vop_conf.mrp_queue = cpu_queue;
    RC(mesa_vop_conf_set(NULL, &vop_conf));
    // snippet_end

    // snippet_begin ex-mrp-add
    RC(mesa_mrp_get(NULL, state.mrp_idx, &mrp_conf))
    mrp_conf.ring_role = ring_role;
    mrp_conf.in_ring_role = in_ring_role;
    mrp_conf.in_rc_mode = TRUE;
    mrp_conf.p_port = state.p_port;
    mrp_conf.s_port = state.s_port;
    mrp_conf.i_port = state.i_port;
    mrp_conf.mra = FALSE;
    memcpy(mrp_conf.mac.addr, test_uc_addr, sizeof(mrp_conf.mac.addr));
    RC(mesa_mrp_add(NULL, state.mrp_idx, &mrp_conf));
    RC(mesa_mrp_port_state_set(NULL, state.mrp_idx, state.p_port, MESA_MRP_PORT_STATE_FORWARDING));
    RC(mesa_mrp_port_state_set(NULL, state.mrp_idx, state.s_port, MESA_MRP_PORT_STATE_FORWARDING));
    RC(mesa_mrp_port_state_set(NULL, state.mrp_idx, state.i_port, MESA_MRP_PORT_STATE_FORWARDING));
    // snippet_end

    // snippet_begin ex-mrp-loc
    RC(mesa_mrp_tst_loc_conf_get(NULL, state.mrp_idx, &loc_conf))
    loc_conf.tst_interval = tst_interval;
    loc_conf.tst_mon_count = tst_mon_count;
    loc_conf.itst_interval = itst_interval;
    loc_conf.itst_mon_count = itst_mon_count;
    RC(mesa_mrp_tst_loc_conf_set(NULL, state.mrp_idx, &loc_conf))
    // snippet_end

    // snippet_begin ex-mrp-events-enable
    RC(mesa_mrp_event_mask_set(NULL, state.mrp_idx, MESA_MRP_EVENT_MASK_ALL, TRUE));
    // snippet_end

    // snippet_begin ex-mrp-ring-state-closed
    RC(mesa_mrp_ring_state_set(NULL, state.mrp_idx, MESA_MRP_RING_STATE_CLOSED));
    // snippet_end

    return 0;
}

static int mrp_clean()
{
    RC(mesa_vlan_port_conf_set(NULL, state.p_port, &state.vlan_conf[0]));
    RC(mesa_vlan_port_conf_set(NULL, state.s_port, &state.vlan_conf[0]));
    RC(mesa_vlan_port_conf_set(NULL, state.i_port, &state.vlan_conf[0]));

    RC(mesa_mrp_del(NULL, state.mrp_idx));

    return 0;
}

static char ret_string[600];
static const char* mrp_help()
{
    uint32_t cnt;

    cnt = sprintf(ret_string, "%s", mrp_help_txt);
    cnt += sprintf(ret_string+cnt, "MRP Ring Role is %s\n", (ring_role == MESA_MRP_RING_ROLE_MANAGER) ? "Manager" : "Client");
    cnt += sprintf(ret_string+cnt, "MRP Interconnect Role is %s\n", (in_ring_role == MESA_MRP_RING_ROLE_MANAGER) ? "Manager" : "Client");
    cnt += sprintf(ret_string+cnt, "MRP Test frame Unicast MAC is %X-%X-%X-%X-%X-%X\n", test_uc_addr[0], test_uc_addr[1], test_uc_addr[2], test_uc_addr[3], test_uc_addr[4], test_uc_addr[5]);
    cnt += sprintf(ret_string+cnt, "MRP Test Interval is %u\n", tst_interval);
    cnt += sprintf(ret_string+cnt, "MRP Test Monitor Count is %u\n", tst_mon_count);
    cnt += sprintf(ret_string+cnt, "MRP InTest Interval is %u\n", itst_interval);
    cnt += sprintf(ret_string+cnt, "MRP InTest Monitor Count is %u\n", itst_mon_count);
    return ret_string;
}

static const char* mrp_type_text(uint32_t mrp_type)
{
    switch(mrp_type)
    {
        case 2: return("MRP_Test");
        case 3: return("MRP_TopologyChange");
        case 4: return("MRP_LinkDown");
        case 5: return("MRP_LinkUp");
        case 6: return("MRP_InTest");
        case 7: return("MRP_InTopologyChange");
        case 8: return("MRP_InLinkDown");
        case 9: return("MRP_InLinkUp");
        default: return("Unknown");
    }
}

static int mrp_run(int argc, const char *argv[])
{
    uint32_t command = ARGV_RUN_INT("command", "The command to run.\n\
        value 0 is MRP status show.\n\
        value 1 is MRP event status show.\n\
        value 2 is CPU RX frame print.\n\
        value 3 is CPU TX Test frame.\n");

    uint32_t exp_mrp_type = ARGV_RUN_OPT_INT("exp-mrp-type", "The MRP Frame RX expected MRP type. Default is nothing expected", NO_EXP);

    uint32_t exp_mrp_seen_p = ARGV_RUN_OPT_INT("exp-seen-p-mrp", "The MRP status show expected MRP seen. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_state_loc_p = ARGV_RUN_OPT_INT("exp-state-p-loc", "The MRP status show expected Test LOC state. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_state_iloc_p = ARGV_RUN_OPT_INT("exp-state-p-iloc", "The MRP status show expected InTest LOC state. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_event_loc_p = ARGV_RUN_OPT_INT("exp-event-p-loc", "The MRP event status show expected Test LOC event. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_event_iloc_p = ARGV_RUN_OPT_INT("exp-event-p-iloc", "The MRP event status show expected InTest LOC event. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_count_tst_p = ARGV_RUN_OPT_INT("exp-count-p-tst", "The MRP status show expected Test RX count. Primary. Default is nothing expected", NO_EXP);
    uint32_t exp_count_itst_p = ARGV_RUN_OPT_INT("exp-count-p-itst", "The MRP status show expected InTest RX count. Primary. Default is nothing expected", NO_EXP);

    uint32_t exp_mrp_seen_s = ARGV_RUN_OPT_INT("exp-seen-s-mrp", "The MRP status show expected MRP seen. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_state_loc_s = ARGV_RUN_OPT_INT("exp-state-s-loc", "The MRP status show expected Test LOC state. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_state_iloc_s = ARGV_RUN_OPT_INT("exp-state-s-iloc", "The MRP status show expected InTest LOC state. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_event_loc_s = ARGV_RUN_OPT_INT("exp-event-s-loc", "The MRP event status show expected Test LOC event. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_event_iloc_s = ARGV_RUN_OPT_INT("exp-event-s-iloc", "The MRP event status show expected InTest LOC event. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_count_tst_s = ARGV_RUN_OPT_INT("exp-count-s-tst", "The MRP status show expected Test RX count. Secondary. Default is nothing expected", NO_EXP);
    uint32_t exp_count_itst_s = ARGV_RUN_OPT_INT("exp-count-s-itst", "The MRP status show expected InTest RX count. Secondary. Default is nothing expected", NO_EXP);

    uint32_t exp_mrp_seen_i = ARGV_RUN_OPT_INT("exp-seen-i-mrp", "The MRP status show expected MRP seen. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_state_loc_i = ARGV_RUN_OPT_INT("exp-state-i-loc", "The MRP status show expected Test LOC state. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_state_iloc_i = ARGV_RUN_OPT_INT("exp-state-i-iloc", "The MRP status show expected InTest LOC state. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_event_loc_i = ARGV_RUN_OPT_INT("exp-event-i-loc", "The MRP event status show expected Test LOC event. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_event_iloc_i = ARGV_RUN_OPT_INT("exp-event-i-iloc", "The MRP event status show expected InTest LOC event. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_count_tst_i = ARGV_RUN_OPT_INT("exp-count-i-tst", "The MRP status show expected Test RX count. Interconnect. Default is nothing expected", NO_EXP);
    uint32_t exp_count_itst_i = ARGV_RUN_OPT_INT("exp-count-i-itst", "The MRP status show expected InTest RX count. Interconnect. Default is nothing expected", NO_EXP);

    mesa_mrp_status_t      mrp_status;
    mesa_mrp_counters_t    mrp_counters;
    mesa_packet_tx_info_t  tx_info;
    mesa_packet_rx_info_t  rx_info;
    mesa_vlan_port_conf_t  vlan_conf;
    mesa_mrp_event_t       mrp_event;
    uint8_t                frame[1600], *et_ptr, mrp_type;
    uint32_t               rcode, ether_type, idx;

    EXAMPLE_BARRIER(argc);

    switch (command) {
    case 0:
        RC(mesa_mrp_status_get(NULL, state.mrp_idx, &mrp_status));
        cli_printf("MRP status:\n");
        cli_printf("    Primary Port:\n");
        cli_printf("      tst_loc:       %u\n", mrp_status.p_status.tst_loc);
        cli_printf("      itst_loc:      %u\n", mrp_status.p_status.itst_loc);
        cli_printf("      mrp_seen:      %u\n", mrp_status.p_status.mrp_seen);
        cli_printf("      mrp_proc_seen: %u\n", mrp_status.p_status.mrp_proc_seen);
        cli_printf("      dmac_err_seen: %u\n", mrp_status.p_status.dmac_err_seen);
        cli_printf("      vers_err_seen: %u\n", mrp_status.p_status.vers_err_seen);
        cli_printf("\n");
        cli_printf("    Secondary Port:\n");
        cli_printf("      tst_loc:       %u\n", mrp_status.s_status.tst_loc);
        cli_printf("      itst_loc:      %u\n", mrp_status.s_status.itst_loc);
        cli_printf("      mrp_seen:      %u\n", mrp_status.s_status.mrp_seen);
        cli_printf("      mrp_proc_seen: %u\n", mrp_status.s_status.mrp_proc_seen);
        cli_printf("      dmac_err_seen: %u\n", mrp_status.s_status.dmac_err_seen);
        cli_printf("      vers_err_seen: %u\n", mrp_status.s_status.vers_err_seen);
        cli_printf("\n");
        cli_printf("    Interconnect Port:\n");
        cli_printf("      tst_loc:       %u\n", mrp_status.i_status.tst_loc);
        cli_printf("      itst_loc:      %u\n", mrp_status.i_status.itst_loc);
        cli_printf("      mrp_seen:      %u\n", mrp_status.i_status.mrp_seen);
        cli_printf("      mrp_proc_seen: %u\n", mrp_status.i_status.mrp_proc_seen);
        cli_printf("      dmac_err_seen: %u\n", mrp_status.i_status.dmac_err_seen);
        cli_printf("      vers_err_seen: %u\n", mrp_status.i_status.vers_err_seen);
        if ((exp_mrp_seen_p != NO_EXP) && (exp_mrp_seen_p != mrp_status.p_status.mrp_seen)) {
            cli_printf("Primary MRP seen %u is not as expected %u\n", mrp_status.p_status.mrp_seen, exp_mrp_seen_p);
            return -1;
        }
        if ((exp_state_loc_p != NO_EXP) && (exp_state_loc_p != mrp_status.p_status.tst_loc)) {
            cli_printf("Primary Test LOC state %u is not as expected %u\n", mrp_status.p_status.tst_loc, exp_state_loc_p);
            return -1;
        }
        if ((exp_state_iloc_p != NO_EXP) && (exp_state_iloc_p != mrp_status.p_status.itst_loc)) {
            cli_printf("Primary InTest LOC state %u is not as expected %u\n", mrp_status.p_status.itst_loc, exp_state_iloc_p);
            return -1;
        }

        if ((exp_mrp_seen_s != NO_EXP) && (exp_mrp_seen_s != mrp_status.s_status.mrp_seen)) {
            cli_printf("Secondary MRP seen %u is not as expected %u\n", mrp_status.s_status.mrp_seen, exp_mrp_seen_s);
            return -1;
        }
        if ((exp_state_loc_s != NO_EXP) && (exp_state_loc_s != mrp_status.s_status.tst_loc)) {
            cli_printf("Secondary Test LOC state %u is not as expected %u\n", mrp_status.s_status.tst_loc, exp_state_loc_s);
            return -1;
        }
        if ((exp_state_iloc_s != NO_EXP) && (exp_state_iloc_s != mrp_status.s_status.itst_loc)) {
            cli_printf("Secondary InTest LOC state %u is not as expected %u\n", mrp_status.s_status.itst_loc, exp_state_iloc_s);
            return -1;
        }

        if ((exp_mrp_seen_i != NO_EXP) && (exp_mrp_seen_i != mrp_status.i_status.mrp_seen)) {
            cli_printf("Interconnect MRP seen %u is not as expected %u\n", mrp_status.i_status.mrp_seen, exp_mrp_seen_i);
            return -1;
        }
        if ((exp_state_loc_i != NO_EXP) && (exp_state_loc_i != mrp_status.i_status.tst_loc)) {
            cli_printf("Interconnect Test LOC state %u is not as expected %u\n", mrp_status.i_status.tst_loc, exp_state_loc_i);
            return -1;
        }
        if ((exp_state_iloc_i != NO_EXP) && (exp_state_iloc_i != mrp_status.i_status.itst_loc)) {
            cli_printf("Interconnect InTest LOC state %u is not as expected %u\n", mrp_status.i_status.itst_loc, exp_state_iloc_i);
            return -1;
        }

        RC(mesa_mrp_counters_get(NULL, state.mrp_idx, &mrp_counters));
        cli_printf("\nMRP counters:\n");
        cli_printf("    Primary Port:\n");
        cli_printf("      tst_rx_count:  %llu\n", mrp_counters.p_counters.tst_rx_count);
        cli_printf("      itst_rx_count: %llu\n", mrp_counters.p_counters.itst_rx_count);
        cli_printf("\n");
        cli_printf("    Secondary Port:\n");
        cli_printf("      tst_rx_count:  %llu\n", mrp_counters.s_counters.tst_rx_count);
        cli_printf("      itst_rx_count: %llu\n", mrp_counters.s_counters.itst_rx_count);
        cli_printf("\n");
        cli_printf("    Interconnect Port:\n");
        cli_printf("      tst_rx_count:  %llu\n", mrp_counters.i_counters.tst_rx_count);
        cli_printf("      itst_rx_count: %llu\n", mrp_counters.i_counters.itst_rx_count);
        break;
        if ((exp_count_tst_p != NO_EXP) && (exp_count_tst_p != mrp_counters.p_counters.tst_rx_count)) {
            cli_printf("Primary MRP Test RX count %u is not as expected %u\n", mrp_counters.p_counters.tst_rx_count, exp_count_tst_p);
            return -1;
        }
        if ((exp_count_itst_p != NO_EXP) && (exp_count_itst_p != mrp_counters.p_counters.itst_rx_count)) {
            cli_printf("Primary MRP InTest RX count %u is not as expected %u\n", mrp_counters.p_counters.tst_rx_count, exp_count_tst_p);
            return -1;
        }
        if ((exp_count_tst_s != NO_EXP) && (exp_count_tst_s != mrp_counters.s_counters.tst_rx_count)) {
            cli_printf("Secondary MRP Test RX count %u is not as expected %u\n", mrp_counters.s_counters.tst_rx_count, exp_count_tst_s);
            return -1;
        }
        if ((exp_count_itst_i != NO_EXP) && (exp_count_itst_i != mrp_counters.i_counters.itst_rx_count)) {
            cli_printf("Interconnect MRP InTest RX count %u is not as expected %u\n", mrp_counters.i_counters.tst_rx_count, exp_count_tst_i);
            return -1;
        }
        if ((exp_count_tst_i != NO_EXP) && (exp_count_tst_i != mrp_counters.i_counters.tst_rx_count)) {
            cli_printf("Interconnect MRP Test RX count %u is not as expected %u\n", mrp_counters.i_counters.tst_rx_count, exp_count_tst_i);
            return -1;
        }
        if ((exp_count_itst_s != NO_EXP) && (exp_count_itst_s != mrp_counters.s_counters.itst_rx_count)) {
            cli_printf("Secondary MRP InTest RX count %u is not as expected %u\n", mrp_counters.s_counters.tst_rx_count, exp_count_tst_s);
            return -1;
        }

    case 1:
        RC(mesa_mrp_event_get(NULL, state.mrp_idx, &mrp_event));
        cli_printf("MRP event:\n");
        cli_printf("    Primary Port:\n");
        cli_printf("      tst_loc:  %u\n", (MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.p_mask) ? 1 : 0);
        cli_printf("      itst_loc: %u\n", (MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.p_mask) ? 1 : 0);
        cli_printf("\n");
        cli_printf("    Secondary Port:\n");
        cli_printf("      tst_loc:  %u\n", (MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.s_mask) ? 1 : 0);
        cli_printf("      itst_loc: %u\n", (MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.s_mask) ? 1 : 0);
        cli_printf("\n");
        cli_printf("    Interconnect Port:\n");
        cli_printf("      tst_loc:  %u\n", (MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.i_mask) ? 1 : 0);
        cli_printf("      itst_loc: %u\n", (MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.i_mask) ? 1 : 0);
        if ((exp_event_loc_p != NO_EXP) && (exp_event_loc_p != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.p_mask) ? 1 : 0))) {
            cli_printf("Primary loc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.p_mask) ? 1 : 0), exp_event_loc_p);
            return -1;
        }
        if ((exp_event_iloc_p != NO_EXP) && (exp_event_iloc_p != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.p_mask) ? 1 : 0))) {
            cli_printf("Primary iloc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.p_mask) ? 1 : 0), exp_event_loc_p);
            return -1;
        }

        if ((exp_event_loc_s != NO_EXP) && (exp_event_loc_s != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.s_mask) ? 1 : 0))) {
            cli_printf("Secondary loc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.s_mask) ? 1 : 0), exp_event_loc_s);
            return -1;
        }
        if ((exp_event_iloc_s != NO_EXP) && (exp_event_iloc_s != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.s_mask) ? 1 : 0))) {
            cli_printf("Secondary iloc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.s_mask) ? 1 : 0), exp_event_loc_s);
            return -1;
        }

        if ((exp_event_loc_i != NO_EXP) && (exp_event_loc_i != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.i_mask) ? 1 : 0))) {
            cli_printf("Interconnect loc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.i_mask) ? 1 : 0), exp_event_loc_p);
            return -1;
        }
        if ((exp_event_iloc_i != NO_EXP) && (exp_event_iloc_i != ((MESA_MRP_EVENT_MASK_TST_LOC & mrp_event.i_mask) ? 1 : 0))) {
            cli_printf("Interconnect iloc event %u is not as expected %u\n", ((MESA_MRP_EVENT_MASK_ITST_LOC & mrp_event.i_mask) ? 1 : 0), exp_event_loc_p);
            return -1;
        }
        break;

    case 2:
        if ((rcode = mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info)) != MESA_RC_OK) {
            cli_printf("mesa_packet_rx_frame() failed  rc %X  Incomplete %u\n", rcode, (rcode == MESA_RC_INCOMPLETE));
            return -1;
        }

        if ((frame[12] == 0x81) && (frame[13] == 0x00)) {
            et_ptr = &frame[12 + 4];
        } else {
            et_ptr = &frame[12];
        }
        ether_type = (et_ptr[0] << 8) + et_ptr[1];
        mrp_type = et_ptr[4];

        cli_printf("Frame received:\n");
        cli_printf("    Port:   %u:\n", rx_info.port_no);
        cli_printf("    Length: %u:\n", rx_info.length);
        cli_printf("    Tag type: %s:\n", (rx_info.tag_type == MESA_TAG_TYPE_UNTAGGED) ? "Un-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_C_TAGGED) ? "C-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_S_TAGGED) ? "S-tagged" : "Unknown");
        cli_printf("    Ether type: %X:\n", ether_type);
        cli_printf("    MRP Type: %s:\n", mrp_type_text(mrp_type));
        if (exp_mrp_type != NO_EXP) {
            if (exp_mrp_type != mrp_type) {
                cli_printf("MRP type %u is not as expected %u\n", mrp_type, exp_mrp_type);
                return -1;
            }
        }
        break;

    case 3:
        // Initialize the TX frame Test
        memset(frame, 0, sizeof(frame));
        idx = 0;
        memcpy(frame+idx, test_mc_addr, sizeof(test_mc_addr));
        idx += 6;
        memcpy(frame+idx, test_uc_addr, sizeof(test_uc_addr));
        idx += 6;
        *(frame+idx+0) = 0x88;
        *(frame+idx+1) = 0xE3;
        idx += 2;
        *(frame+idx+0) = 0;    // Version
        *(frame+idx+1) = 1;
        idx += 2;
        *(frame+idx) = 2;   // Type Test
        idx += 1;
        *(frame+idx) = 21;  // Length
        idx += 1;
        idx += 2;  //Prio
        idx += 6;  //SA
        idx += 2;  //Role
        idx += 2;  //State
        idx += 2;  //Trans
        idx += 4;  //TS
        idx += 1;  //C Type
        idx += 1;  //C Length
        idx += 2;  //C Sequence
        idx += 16; //C Domain
        idx += 1;  //E Type
        idx += 1;  //E Length
        idx += 20;  //Padding

        // Initialize the TX info
        RC(mesa_vlan_port_conf_get(NULL, state.p_port, &vlan_conf));
        RC(mesa_packet_tx_info_init(NULL, &tx_info));
        tx_info.dst_port_mask = 0x01 << state.p_port;
        tx_info.switch_frm = FALSE;
        tx_info.masquerade_port = MESA_PORT_NO_NONE;
        tx_info.pdu_offset = 14;
        tx_info.oam_type = MESA_PACKET_OAM_TYPE_MRP_TST;
        tx_info.pipeline_pt = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
        tx_info.tag.vid = vlan_conf.pvid;
        tx_info.iflow_id = IFLOW_ID_NONE;

        // Transmit the frame on Primary port
        RC(mesa_packet_tx_frame(NULL, &tx_info, frame, idx));

        // Initialize the TX info
        RC(mesa_vlan_port_conf_get(NULL, state.s_port, &vlan_conf));
        RC(mesa_packet_tx_info_init(NULL, &tx_info));
        tx_info.dst_port_mask = 0x01 << state.s_port;
        tx_info.switch_frm = FALSE;
        tx_info.masquerade_port = MESA_PORT_NO_NONE;
        tx_info.pdu_offset = 14;
        tx_info.oam_type = MESA_PACKET_OAM_TYPE_MRP_TST;
        tx_info.pipeline_pt = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
        tx_info.tag.vid = vlan_conf.pvid;
        tx_info.iflow_id = IFLOW_ID_NONE;

        // Transmit the frame on Secondary
        RC(mesa_packet_tx_frame(NULL, &tx_info, frame, idx));
        break;

    default:
        cli_printf("Unknown command\n");
        break;
    }

    return 0;
}

EXAMPLE(mrp, mrp_init, mrp_run, mrp_clean, mrp_help);
