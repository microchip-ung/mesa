// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static const char *ot_help_txt = "\
This is a OT Scheduling test. Currently only able to run on 1G link\n\
speed.\n\
\n\
Three ports will be ingress. One port will be egress.\n\
On egress port a shaper will be created to assure buffers are full\n\
On ingress ports frames are classified to priority 0 - 3 -7\n\
\n";

static struct {
    mesa_port_conf_t         port_conf[4];
    mesa_vlan_port_conf_t    vlan_conf[4];
    mesa_qos_port_conf_t     qos_conf[4];
    mesa_qos_port_dpl_conf_t dpl_conf[4][4];
    mesa_vlan_vid_conf_t     vlan_vid_conf;
} state;

#define ot_vid 100
#define egress_port 3
#define frame_size 500
#define cycle_frames 1000*3
#define offset_time 3

static int init_port_configuration(mesa_port_no_t port)
{
    mesa_port_conf_t         port_conf;
    mesa_vlan_port_conf_t    vlan_conf;
    mesa_qos_port_conf_t     qos_conf;
    mesa_qos_port_dpl_conf_t dpl_conf[4];
    uint32_t                 dpl_cnt;
    static mesa_tagprio_t    pcp[MESA_PRIO_ARRAY_SIZE] = {0,1,2,3,4,5,6,7};
    static mesa_dei_t        dei0[MESA_PRIO_ARRAY_SIZE] = {0,0,0,0,0,0,0,0};
    static mesa_dei_t        dei1[MESA_PRIO_ARRAY_SIZE] = {1,1,1,1,1,1,1,1};

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    /* Disable flow control */
    RC(mesa_port_conf_get(NULL, port, &state.port_conf[port]));
    port_conf = state.port_conf[port];
    port_conf.flow_control.obey = FALSE;
    port_conf.flow_control.generate = FALSE;
    RC(mesa_port_conf_set(NULL, port, &port_conf));

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[port]));
    vlan_conf = state.vlan_conf[port];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.untagged_vid = MESA_VID_NULL;
    vlan_conf.pvid = ot_vid;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    /* Configure ingress prio classification and prio and dpl mapping to 1:1 */
    RC(mesa_qos_port_conf_get(NULL, port, &state.qos_conf[port]));
    qos_conf = state.qos_conf[port];
    qos_conf.tag.class_enable = TRUE;
    qos_conf.tag.remark_mode = MESA_TAG_REMARK_MODE_MAPPED;
    qos_conf.tag.pcp_dei_map[0][0].prio = 0;
    qos_conf.tag.pcp_dei_map[0][0].dpl = 0;
    qos_conf.tag.pcp_dei_map[0][1].prio = 0;
    qos_conf.tag.pcp_dei_map[0][1].dpl = 1;
    qos_conf.tag.pcp_dei_map[1][0].prio = 1;
    qos_conf.tag.pcp_dei_map[1][0].dpl = 0;
    qos_conf.tag.pcp_dei_map[1][1].prio = 1;
    qos_conf.tag.pcp_dei_map[1][1].dpl = 1;
    qos_conf.default_prio = 2;
    qos_conf.default_dpl = 0;
    RC(mesa_qos_port_conf_set(NULL, port, &qos_conf));

    /* Configure egress prio and dpl mapping to 1:1 */
    RC(mesa_qos_port_dpl_conf_get(NULL, port, dpl_cnt, &state.dpl_conf[port][0]));
    dpl_conf[0] = state.dpl_conf[port][0];
    dpl_conf[1] = state.dpl_conf[port][1];
    memcpy(dpl_conf[0].pcp, pcp, sizeof(dpl_conf[0].pcp));
    memcpy(dpl_conf[0].dei, dei0, sizeof(dpl_conf[0].dei));
    memcpy(dpl_conf[1].pcp, pcp, sizeof(dpl_conf[1].pcp));
    memcpy(dpl_conf[1].dei, dei1, sizeof(dpl_conf[1].dei));
    RC(mesa_qos_port_dpl_conf_set(NULL, port, dpl_cnt, &dpl_conf[0]));

    return 0;
}

static int ot_init(int argc, const char *argv[])
{
    uint32_t                   ot_support, i;
    mesa_port_list_t           port_list;
    mesa_vlan_vid_conf_t       vlan_vid_conf;
    mesa_qos_port_conf_t       qos_conf;

    EXAMPLE_BARRIER(argc);

    // snippet_begin ex-qos-ot-check-capability
    ot_support = mesa_capability(NULL, MESA_CAP_QOS_OT);
    if (!ot_support) {
        cli_printf("IT/OT is not supported on this platform\n");
        return 0;
    }
    // snippet_end

    memset(&state, 0, sizeof(state));

    // snippet_begin ex-qos-ot-vid-config
    // Configure VID to be OT
    RC(mesa_vlan_vid_conf_get(NULL, ot_vid, &state.vlan_vid_conf));
    vlan_vid_conf = state.vlan_vid_conf;
    vlan_vid_conf.ot = TRUE;
    RC(mesa_vlan_vid_conf_set(NULL, ot_vid, &vlan_vid_conf));
    // snippet_end

    mesa_port_list_clear(&port_list);

    for (i=0; i<4; ++i) {
        RC(init_port_configuration(i))
        mesa_port_list_set(&port_list, i, TRUE);
    }

    // Only forward on relevant ports
    RC(mesa_vlan_port_members_set(NULL, ot_vid, &port_list));

    /* Configure egress port shaper to assure queues are never emptied in the following tests */
    RC(mesa_qos_port_conf_get(NULL, egress_port, &qos_conf));
    qos_conf.shaper.level = 25000;
    qos_conf.shaper.rate = 990000;
    RC(mesa_qos_port_conf_set(NULL, egress_port, &qos_conf));

    return 0;
}

static int ot_clean()
{
    uint32_t                   i, dpl_cnt;
    mesa_qos_tas_port_conf_t   tas_conf;

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    for (i=0; i<4; ++i) {
        RC(mesa_port_conf_set(NULL, i, &state.port_conf[i]));
        RC(mesa_vlan_port_conf_set(NULL, i, &state.vlan_conf[i]));
        RC(mesa_qos_port_conf_set(NULL, i, &state.qos_conf[i]));
        RC(mesa_qos_port_dpl_conf_set(NULL, i, dpl_cnt, &state.dpl_conf[i][0]));
    }
    RC(mesa_vlan_vid_conf_set(NULL, ot_vid, &state.vlan_vid_conf));

    // Stop GCL
    RC(mesa_qos_tas_port_conf_get(NULL, egress_port, &tas_conf));
    tas_conf.gate_enabled = FALSE;
    tas_conf.config_change = FALSE;
    RC(mesa_qos_tas_port_conf_set(NULL, egress_port, &tas_conf));

    return 0;
}

static const char* ot_help()
{
    return ot_help_txt;
}

#define NO_EXP 0xFFFFFFFF

static int ot_run(int argc, const char *argv[])
{
    uint32_t                   cycle_time, gce_cnt, i;
    uint32_t                   time_interval_0, time_interval_4, time_interval_7;
    uint32_t                   frame_tx_time_nano, gce_count, tas_support;
    mesa_qos_tas_gce_t         *gcl;
    mesa_timestamp_t           base_time;
    mesa_qos_tas_port_conf_t   tas_conf;
    mesa_qos_port_conf_t       qos_conf;
    mesa_qos_tas_port_status_t tas_status;
    uint64_t                   tc;

    uint32_t command = ARGV_RUN_INT("command", "The command to run.\n\
        value 0 is Configure OT DWRR.\n\
        value 1 is Configure OT TAS.\n\
        value 2 is Configure OT Queue shaper.\n\
        value 3 is Configure OT shaper.\n");

    EXAMPLE_BARRIER(argc);

    tas_support = mesa_capability(NULL, MESA_CAP_QOS_TAS);
    gce_count = mesa_capability(NULL, MESA_CAP_QOS_TAS_GCE_CNT);

    // Restore to default
    RC(mesa_qos_port_conf_get(NULL, egress_port, &qos_conf));
    qos_conf.ot_dwrr_enable = FALSE;
    qos_conf.ot_dwrr_cnt = 0;
    for(i=0; i<8; ++i) {
        qos_conf.ot_queue[i].shaper.level = 0;
        qos_conf.ot_queue[i].shaper.rate = MESA_BITRATE_DISABLED;
    }
    qos_conf.ot_shaper.level = 0;
    qos_conf.ot_shaper.rate = MESA_BITRATE_DISABLED;
    RC(mesa_qos_port_conf_set(NULL, egress_port, &qos_conf));

    if (tas_support) {
        // Stop GCL
        RC(mesa_qos_tas_port_conf_get(NULL, egress_port, &tas_conf));
        tas_conf.gate_enabled = FALSE;
        tas_conf.config_change = FALSE;
        RC(mesa_qos_tas_port_conf_set(NULL, egress_port, &tas_conf));
    }

    switch (command) {
    case 0:
        // snippet_begin ex-qos-ot-dwrr-config
        // Configure OT DWRR
        RC(mesa_qos_port_conf_get(NULL, egress_port, &qos_conf));
        qos_conf.ot_dwrr_enable = TRUE;
        qos_conf.ot_dwrr_cnt = 3;
        qos_conf.ot_queue[0].pct = 10;
        qos_conf.ot_queue[1].pct = 30;
        qos_conf.ot_queue[2].pct = 60;
        RC(mesa_qos_port_conf_set(NULL, egress_port, &qos_conf));
        // snippet_end
        break;

    case 1:
        if (!tas_support) {
            cli_printf("TAS is not supported on this platform\n");
            return 0;
        }

        frame_tx_time_nano = (frame_size+20)*8;                           // One bit takes one nano sec to transmit at 1G
        time_interval_0 = (cycle_frames*10*frame_tx_time_nano)/100;   // number of nano for each interval
        time_interval_4 = (cycle_frames*30*frame_tx_time_nano)/100;   // number of nano for each interval
        time_interval_7 = (cycle_frames*60*frame_tx_time_nano)/100;   // number of nano for each interval
        cycle_time = time_interval_0 + time_interval_4 + time_interval_7; // GCL cycle time

        gcl = malloc(gce_count);
        if (gcl == NULL) {
            cli_printf("GCL malloc failed\n");
            return 0;
        }

        // Create GCL
        RC(mesa_qos_tas_port_gcl_conf_get(NULL, egress_port, gce_count, gcl, &gce_cnt));
        gcl[0].gate_operation = MESA_QOS_TAS_GCO_SET_GATE_STATES;
        memset(gcl[0].gate_open, FALSE, sizeof(gcl[0].gate_open));
        gcl[0].gate_open[0] = TRUE;
        gcl[0].time_interval = time_interval_0;
        gcl[1].gate_operation = MESA_QOS_TAS_GCO_SET_GATE_STATES;
        memset(gcl[1].gate_open, FALSE, sizeof(gcl[1].gate_open));
        gcl[1].gate_open[4] = TRUE;
        gcl[1].time_interval = time_interval_4;
        gcl[2].gate_operation = MESA_QOS_TAS_GCO_SET_GATE_STATES;
        memset(gcl[2].gate_open, FALSE, sizeof(gcl[2].gate_open));
        gcl[2].gate_open[7] = TRUE;
        gcl[2].time_interval = time_interval_7;
        RC(mesa_qos_tas_port_gcl_conf_set(NULL, egress_port, 3, gcl));
        // snippet_end

        // Set TOD of domain 0 to zero")
        RC(mesa_ts_timeofday_get(NULL, &base_time, &tc));
        base_time.seconds = 0;
        base_time.nanoseconds = 0;
        RC(mesa_ts_timeofday_set(NULL, &base_time));

        // snippet_begin ex-qos-ot-tas-start
        // Start GCL
        base_time.seconds = offset_time;
        RC(mesa_qos_tas_port_conf_get(NULL, egress_port, &tas_conf));
        tas_conf.max_sdu[0] = frame_size + (frame_size/2);
        tas_conf.max_sdu[4] = frame_size + (frame_size/2);
        tas_conf.max_sdu[7] = frame_size + (frame_size/2);
        tas_conf.gate_enabled = TRUE;
        tas_conf.ot = TRUE;
        memset(tas_conf.gate_open, TRUE, sizeof(tas_conf.gate_open));
        tas_conf.cycle_time = cycle_time;
        tas_conf.cycle_time_ext = 256;
        tas_conf.base_time = base_time;
        tas_conf.gate_enabled = TRUE;
        tas_conf.config_change = TRUE;
        RC(mesa_qos_tas_port_conf_set(NULL, egress_port, &tas_conf));
        // snippet_end

        // Wait for GCL to start
        sleep(offset_time + 1);

        // Check GCL is started
        RC(mesa_qos_tas_port_status_get(NULL, egress_port, &tas_status));
        if (tas_status.config_pending == TRUE) {
            cli_printf("GCL unexpected config_pending = %u\n", tas_status.config_pending);
        }

        free(gcl);

        break;

    case 2:
        // Configure OT Queue Shaper
        // snippet_begin ex-qos-ot-queue-shaper-config
        RC(mesa_qos_port_conf_get(NULL, egress_port, &qos_conf));
        for(i=0; i<8; ++i) {
            if ((i==0) || (i==3) || (i==7)) {
                qos_conf.ot_queue[i].shaper.level = 1;
                qos_conf.ot_queue[i].shaper.rate = 100000;
                qos_conf.ot_queue[i].shaper.mode = MESA_SHAPER_MODE_LINE;
            }
        }
        RC(mesa_qos_port_conf_set(NULL, egress_port, &qos_conf));
        // snippet_end
        break;

    case 3:
        // Configure OT Shaper
        // snippet_begin ex-qos-ot-shaper-config
        RC(mesa_qos_port_conf_get(NULL, egress_port, &qos_conf));
        qos_conf.ot_shaper.level = 25000;
        qos_conf.ot_shaper.rate = 500000;
        qos_conf.ot_shaper.mode = MESA_SHAPER_MODE_LINE;
        RC(mesa_qos_port_conf_set(NULL, egress_port, &qos_conf));
        // snippet_end
        break;

    default:
        cli_printf("Unknown command\n");
        break;
    }

    return 0;
}

EXAMPLE(ot, ot_init, ot_run, ot_clean, ot_help);
