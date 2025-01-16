// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static const char *tas_help_txt = "\
This is a Time Aware Scheduling test. Currently only able to run on 1G link\n\
speed.\n\
\n\
One port will be ingress. One port will be egress.\n\
On egress port a GCL will be created with three entries where only one\n\
priority is open in each entry.\n\
The interval time for the three entries are 10% - 30% - 60% of the cycle time.\n\
Optionally a start time offset can be given. Default is three second.\n\
The priorities open in each entry is 0 - 4 - 7.\n\
Injecting the three priorities on ingress port at line rate as a priority\n\
tagged frame with PCP 0 or 4 or 7. \n\
On egress port it is observed that the three priorities are transmitted with\n\
the percentage given by the interval percentage.\n\
On egress port it is observed that there is cycle time gap in transmission of\n\
frames.\n";

static struct {
    mesa_port_conf_t         port_conf[2];
    mesa_vlan_port_conf_t    vlan_conf[2];
    mesa_qos_port_conf_t     qos_conf[2];
    mesa_qos_port_dpl_conf_t dpl_conf[2][4];

    mesa_qos_tas_port_conf_t tas_conf;
    mesa_qos_tas_gce_t       tas_gcl[2];

    mesa_port_no_t ing_port;
    mesa_port_no_t eg_port;
} state;

static int init_port_configuration(mesa_port_no_t port, uint32_t idx)
{
    mesa_port_conf_t         port_conf;
    mesa_vlan_port_conf_t    vlan_conf;
    mesa_qos_port_conf_t     qos_conf;
    mesa_qos_port_dpl_conf_t dpl_conf[4];
    uint32_t                 dpl_cnt;
    static mesa_tagprio_t pcp[MESA_PRIO_ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7};
    static mesa_dei_t     dei1[MESA_PRIO_ARRAY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
    static mesa_dei_t     dei0[MESA_PRIO_ARRAY_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    /* Disable flow control */
    RC(mesa_port_conf_get(NULL, port, &state.port_conf[idx]));
    port_conf = state.port_conf[idx];
    port_conf.flow_control.obey = FALSE;
    port_conf.flow_control.generate = FALSE;
    RC(mesa_port_conf_set(NULL, port, &port_conf));

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[idx]));
    vlan_conf = state.vlan_conf[idx];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.untagged_vid = MESA_VID_NULL;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    /* Configure ingress prio classificationand prio and dpl mapping to 1:1 */
    RC(mesa_qos_port_conf_get(NULL, port, &state.qos_conf[idx]));
    qos_conf = state.qos_conf[idx];
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
    RC(mesa_qos_port_dpl_conf_get(NULL, port, dpl_cnt,
                                  &state.dpl_conf[idx][0]));
    dpl_conf[0] = state.dpl_conf[idx][0];
    dpl_conf[1] = state.dpl_conf[idx][1];
    memcpy(dpl_conf[0].pcp, pcp, sizeof(dpl_conf[0].pcp));
    memcpy(dpl_conf[0].dei, dei0, sizeof(dpl_conf[0].dei));
    memcpy(dpl_conf[1].pcp, pcp, sizeof(dpl_conf[1].pcp));
    memcpy(dpl_conf[1].dei, dei1, sizeof(dpl_conf[1].dei));
    RC(mesa_qos_port_dpl_conf_set(NULL, port, dpl_cnt, &dpl_conf[0]));

    return 0;
}

static int tas_init(int argc, const char *argv[])
{
    mesa_port_no_t           ing_port, eg_port;
    uint64_t                 cycle_frames;
    uint32_t                 frame_size, offset_time, cycle_time, gce_cnt;
    uint32_t                 time_interval_0, time_interval_4, time_interval_7;
    uint32_t                 frame_tx_time_nano, gce_count, tas_support;
    mesa_qos_tas_gce_t      *gcl;
    mesa_timestamp_t         base_time;
    uint64_t                 tc;
    mesa_qos_tas_port_conf_t tas_conf;
    mesa_qos_tas_port_status_t tas_status;
    mesa_port_list_t           port_list;

    ing_port = ARGV_INT("ing-port", "Is the ingress port for frame injection.");
    eg_port = ARGV_INT("eg-port", "Is the egress port with configured GCL.");
    cycle_frames =
        ARGV_INT("cycle",
                 "Is GCL cycle time in number of frames of size frame_size.");
    frame_size = ARGV_INT(
        "size",
        "Used as MAX PDU size in bytes for calculation of guard band time and cycle time calculation.");
    offset_time =
        ARGV_OPT_INT("start", "Is GCL start offset time in seconds.", 3);

    EXAMPLE_BARRIER(argc);

    tas_support = mesa_capability(NULL, MESA_CAP_QOS_TAS);
    gce_count = mesa_capability(NULL, MESA_CAP_QOS_TAS_GCE_CNT);
    if (!tas_support) {
        cli_printf("TAS is not supported on this platform\n");
        return 0;
    }

    memset(&state, 0, sizeof(state));
    ing_port -= 1;
    ;
    eg_port -= 1;
    ;
    state.ing_port = ing_port;
    state.eg_port = eg_port;

    frame_tx_time_nano =
        (frame_size + 20) * 8; // One bit takes one nano sec to transmit at 1G
    time_interval_0 = (cycle_frames * 10 * frame_tx_time_nano) /
                      100; // number of nano for each interval
    time_interval_4 = (cycle_frames * 30 * frame_tx_time_nano) /
                      100; // number of nano for each interval
    time_interval_7 = (cycle_frames * 60 * frame_tx_time_nano) /
                      100; // number of nano for each interval
    cycle_time =
        time_interval_0 + time_interval_4 + time_interval_7; // GCL cycle time

    gcl = malloc(gce_count);
    if (gcl == NULL) {
        cli_printf("GCL malloc failed\n");
        return 0;
    }

    // Only forward on relevant ports
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, ing_port, TRUE);
    mesa_port_list_set(&port_list, eg_port, TRUE);
    RC(mesa_vlan_port_members_set(NULL, 1, &port_list));

    RC(init_port_configuration(ing_port, 0))
    RC(init_port_configuration(eg_port, 1))

    // snippet_begin ex-qos-tas-gcl-config
    // Create GCL
    RC(mesa_qos_tas_port_gcl_conf_get(NULL, eg_port, gce_count, gcl, &gce_cnt));
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
    RC(mesa_qos_tas_port_gcl_conf_set(NULL, eg_port, 3, gcl));
    // snippet_end

    // Set TOD of domain 0 to zero")
    RC(mesa_ts_timeofday_get(NULL, &base_time, &tc));
    base_time.seconds = 0;
    base_time.nanoseconds = 0;
    RC(mesa_ts_timeofday_set(NULL, &base_time));

    // snippet_begin ex-qos-tas-gcl-start
    // Start GCL
    base_time.seconds = offset_time;
    RC(mesa_qos_tas_port_conf_get(NULL, eg_port, &tas_conf));
    tas_conf.max_sdu[0] = frame_size + (frame_size / 2);
    tas_conf.max_sdu[4] = frame_size + (frame_size / 2);
    tas_conf.max_sdu[7] = frame_size + (frame_size / 2);
    tas_conf.gate_enabled = TRUE;
    memset(tas_conf.gate_open, TRUE, sizeof(tas_conf.gate_open));
    tas_conf.cycle_time = cycle_time;
    tas_conf.cycle_time_ext = 256;
    tas_conf.base_time = base_time;
    tas_conf.gate_enabled = TRUE;
    tas_conf.config_change = TRUE;
    RC(mesa_qos_tas_port_conf_set(NULL, eg_port, &tas_conf));

    // snippet_endbegin ex-qos-tas-gcl-status-start
    // Wait for GCL to start
    sleep(offset_time + 1);

    // Check GCL is started
    RC(mesa_qos_tas_port_status_get(NULL, eg_port, &tas_status));
    if (tas_status.config_pending == TRUE) {
        cli_printf("GCL unexpected config_pending = %u\n",
                   tas_status.config_pending);
    }
    // snippet_end

    free(gcl);
    return 0;
}

static int tas_clean()
{
    mesa_qos_tas_port_conf_t   tas_conf;
    mesa_qos_tas_port_status_t tas_status;
    uint32_t                   dpl_cnt;

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    // snippet_endbegin ex-qos-tas-gcl_stop
    // Stop GCL
    RC(mesa_qos_tas_port_conf_get(NULL, state.eg_port, &tas_conf));
    tas_conf.gate_enabled = FALSE;
    tas_conf.config_change = FALSE;
    RC(mesa_qos_tas_port_conf_set(NULL, state.eg_port, &tas_conf));

    // snippet_endbegin ex-qos-tas-gcl_status_stop
    // Wait for GCL to stop
    sleep(3);

    // Check GCL is stopped
    RC(mesa_qos_tas_port_status_get(NULL, state.eg_port, &tas_status));
    if (tas_status.config_pending == TRUE) {
        cli_printf("GCL unexpected config_pending = %u\n",
                   tas_status.config_pending);
        return -1;
    }
    // snippet_end

    RC(mesa_port_conf_set(NULL, state.ing_port, &state.port_conf[0]));
    RC(mesa_vlan_port_conf_set(NULL, state.ing_port, &state.vlan_conf[0]));
    RC(mesa_qos_port_conf_set(NULL, state.ing_port, &state.qos_conf[0]));
    RC(mesa_qos_port_dpl_conf_set(NULL, state.ing_port, dpl_cnt,
                                  &state.dpl_conf[0][0]));

    RC(mesa_port_conf_set(NULL, state.eg_port, &state.port_conf[1]));
    RC(mesa_vlan_port_conf_set(NULL, state.eg_port, &state.vlan_conf[1]));
    RC(mesa_qos_port_conf_set(NULL, state.eg_port, &state.qos_conf[1]));
    RC(mesa_qos_port_dpl_conf_set(NULL, state.eg_port, dpl_cnt,
                                  &state.dpl_conf[1][0]));

    return 0;
}

static const char *tas_help() { return tas_help_txt; }

EXAMPLE(tas, tas_init, NULL, tas_clean, tas_help);
