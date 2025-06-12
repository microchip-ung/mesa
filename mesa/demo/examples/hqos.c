// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static struct {
    mesa_port_conf_t         port_conf[4];
    mesa_vlan_port_conf_t    vlan_conf[4];
    mesa_qos_port_conf_t     qos_conf[4];
    mesa_vlan_vid_conf_t     vlan_vid_conf[4];
    mesa_port_no_t           ports[4];
    mesa_hqos_port_conf_t    hqos_port_conf;
    mesa_qos_port_dpl_conf_t dpl_conf[4][4];
    mesa_port_no_t           port_eg;
} state;
static mesa_pct_t    hqos_input_pct[MESA_PRIO_ARRAY_SIZE] = {10, 30, 70};
static uint32_t      hqos_min_rate[4] = {100000, 10000, 190000, 700000};
static mesa_shaper_t hqos_shaper[4] = {
    {100,   100000, 0, MESA_BITRATE_DISABLED, MESA_SHAPER_MODE_LINE, 0},
    {10,    10000,  0, MESA_BITRATE_DISABLED, MESA_SHAPER_MODE_LINE, 0},
    {100,   190000, 0, MESA_BITRATE_DISABLED, MESA_SHAPER_MODE_LINE, 0},
    {10000, 700000, 0, MESA_BITRATE_DISABLED, MESA_SHAPER_MODE_LINE, 0}
};

// For now queue shaper is not implemented due to chip restrictions
#if 0
static mesa_hqos_queue_shaper_t hqos_shaper_queue[4][MESA_PRIO_ARRAY_SIZE] = {
    {{100,  5000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {100, 25000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {100, 70000, MESA_SHAPER_MODE_LINE}},
    {{10, 1000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {10, 3000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {10, 6000, MESA_SHAPER_MODE_LINE}},
    {{100,  7000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {100, 23000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {100, 160000, MESA_SHAPER_MODE_LINE}},
    {{200,  10000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {200, 190000, MESA_SHAPER_MODE_LINE},
     {0, MESA_BITRATE_DISABLED, 0},
     {0, MESA_BITRATE_DISABLED, 0},
     {200, 500000, MESA_SHAPER_MODE_LINE}}};
#endif

static const char *hqos_help_txt = "\
This is a HQOS example.\n\
\n\
One port will be egress and configured in Hierarchical mode.\n\
Other three ports are ingress ports.\n\
Flow control is disabled on all ports.\n\
All ports are TAG aware and will classify ingress frames based on the TAG VID.\n\
All ports will classify ingress frames to priority based on TAG PCP in a one-to-one fashion.\n\
Vlans with VID 100-200-300-400 is created with all ports as members.\n\
Vlans are classifying to HQOS-ID as follow: (100 -> 0) (200 -> 1) (300 -> 2) (400 -> 3)\n\
On the egress port a Priority HQOS entry is added with HQOS-ID 0\n\
On the egress port three HQOS entries are added with HQOS-ID 1-3\n\
Injecting frames with TAG VID 100 on an ingress port will hit the Priority HQOS entry 0 on egress port\n\
Injecting frames with TAG VID 200-300-400 will hit the HQOS entry 1-2-3 on egress port\n\
\n\
Command 0 will delete a HQOS entry\n\
\n\
Command 1 will configuring Shaper like this:\n\
HQOS-ID 0 Burst-level 100 Bytes - Rate 200000 Kbps - Mode Line-rate\n\
HQOS-ID 1 Burst-level  10 Bytes - Rate  10000 Kbps - Mode Line-rate\n\
HQOS-ID 2 Burst-level 100 Bytes - Rate 290000 Kbps - Mode Line-rate\n\
HQOS-ID 3 Burst-level 200 Bytes - Rate 700000 Kbps - Mode Line-rate\n\
\n\
Command 2 will configuring DWRR like this:\n\
HQOS-ID 0-3 Priority 0 10 Percent\n\
            Priority 1 30 Percent\n\
            Priority 2 70 Percent\n\
\n\
Command 3 will return the actual minimum rate in kbps:\n\
Actual min_rate: 19760\n\
\n";

#if 0
Command 2 will configuring Queue Shaper like this:
HQOS-ID 0 Priority 0: Burst-level 100 Bytes - Rate  10000 Kbps - Mode Line-rate
          Priority 4: Burst-level 100 Bytes - Rate  90000 Kbps - Mode Line-rate
          Priority 7: Burst-level 100 Bytes - Rate 100000 Kbps - Mode Line-rate
HQOS-ID 1 Priority 0: Burst-level  10 Bytes - Rate   1000 Kbps - Mode Line-rate
          Priority 4: Burst-level  10 Bytes - Rate   3000 Kbps - Mode Line-rate
          Priority 7: Burst-level  10 Bytes - Rate   6000 Kbps - Mode Line-rate
HQOS-ID 2 Priority 0: Burst-level 100 Bytes - Rate  10000 Kbps - Mode Line-rate
          Priority 4: Burst-level 100 Bytes - Rate  90000 Kbps - Mode Line-rate
          Priority 7: Burst-level 100 Bytes - Rate 190000 Kbps - Mode Line-rate
HQOS-ID 3 Priority 0: Burst-level 200 Bytes - Rate  10000 Kbps - Mode Line-rate
          Priority 4: Burst-level 200 Bytes - Rate 190000 Kbps - Mode Line-rate
          Priority 7: Burst-level 200 Bytes - Rate 500000 Kbps - Mode Line-rate
#endif

static int port_configuration(mesa_port_no_t port, uint32_t index, mesa_port_list_t *port_list)
{
    mesa_qos_port_conf_t     qos_conf;
    mesa_port_conf_t         port_conf;
    mesa_vlan_port_conf_t    vlan_conf;
    mesa_qos_port_dpl_conf_t dpl_conf[4];
    uint32_t                 dpl_cnt;
    static mesa_tagprio_t    pcp[MESA_PRIO_ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7};
    static mesa_dei_t        dei1[MESA_PRIO_ARRAY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
    static mesa_dei_t        dei0[MESA_PRIO_ARRAY_SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    state.ports[index] = port;

    /* Disable flow control */
    RC(mesa_port_conf_get(NULL, port, &state.port_conf[index]));
    port_conf = state.port_conf[index];
    port_conf.flow_control.obey = FALSE;
    port_conf.flow_control.generate = FALSE;
    RC(mesa_port_conf_set(NULL, port, &port_conf));

    mesa_port_list_set(port_list, port, TRUE);

    // Set VLAN port configuration
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[index]));
    vlan_conf = state.vlan_conf[index];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.untagged_vid = MESA_VID_NULL;
    vlan_conf.frame_type = MESA_VLAN_FRAME_ALL;
    vlan_conf.pvid = 1000;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    /* Configure ingress prio classification and prio and dpl mapping to 1:1 */
    RC(mesa_qos_port_conf_get(NULL, port, &state.qos_conf[index]));
    qos_conf = state.qos_conf[index];
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
    qos_conf.default_prio = 0;
    qos_conf.default_dpl = 0;
    RC(mesa_qos_port_conf_set(NULL, port, &qos_conf));

    /* Configure egress prio and dpl mapping to 1:1 */
    RC(mesa_qos_port_dpl_conf_get(NULL, port, dpl_cnt, &state.dpl_conf[index][0]));
    dpl_conf[0] = state.dpl_conf[index][0];
    dpl_conf[1] = state.dpl_conf[index][1];
    memcpy(dpl_conf[0].pcp, pcp, sizeof(dpl_conf[0].pcp));
    memcpy(dpl_conf[0].dei, dei0, sizeof(dpl_conf[0].dei));
    memcpy(dpl_conf[1].pcp, pcp, sizeof(dpl_conf[1].pcp));
    memcpy(dpl_conf[1].dei, dei1, sizeof(dpl_conf[1].dei));
    RC(mesa_qos_port_dpl_conf_set(NULL, port, dpl_cnt, &dpl_conf[0]));

    return 0;
}

static int hqos_init(int argc, const char *argv[])
{
    mesa_port_no_t        port_eg = ARGV_INT("port_eg", "Port-Egress");
    mesa_port_no_t        port_ig1 = ARGV_INT("port_ig1", "Port-Ingress-1");
    mesa_port_no_t        port_ig2 = ARGV_INT("port_ig2", "Port-Ingress-2");
    mesa_port_no_t        port_ig3 = ARGV_INT("port_ig3", "Port-Ingress-3");
    uint32_t              hqos_support, i;
    mesa_vid_t            vid;
    mesa_port_list_t      port_list;
    mesa_vlan_vid_conf_t  vlan_vid_conf;
    mesa_hqos_port_conf_t hqos_port_conf;
    mesa_hqos_conf_t      hqos_conf;

    EXAMPLE_BARRIER(argc);

    // snippet_begin ex-hqos-check-capability
    hqos_support = mesa_capability(NULL, MESA_CAP_HQOS);
    if (!hqos_support) {
        cli_printf("HQOS is not supported on this platform\n");
        return 0;
    }
    // snippet_end

    port_eg -= 1;
    port_ig1 -= 1;
    port_ig2 -= 1;
    port_ig3 -= 1;

    memset(&state, 0, sizeof(state));
    mesa_port_list_clear(&port_list);
    state.port_eg = port_eg;

    // Set egress port to Hierarchical mode
    // snippet_begin ex-hqos-hierarchical-config
    RC(mesa_hqos_port_conf_get(NULL, port_eg, &state.hqos_port_conf));
    hqos_port_conf = state.hqos_port_conf;
    hqos_port_conf.sch_mode = MESA_HQOS_SCH_MODE_HIERARCHICAL;
    RC(mesa_hqos_port_conf_set(NULL, port_eg, &hqos_port_conf));
    // snippet_end

    // snippet_begin ex-hqos-port-configuration
    RC(port_configuration(port_eg, 0, &port_list));
    RC(port_configuration(port_ig1, 1, &port_list));
    RC(port_configuration(port_ig2, 2, &port_list));
    RC(port_configuration(port_ig3, 3, &port_list));
    // snippet_end

    // snippet_begin ex-hqos-vid-config
    for (i = 0, vid = 100; i < 4; ++i, vid += 100) {
        // Configure VID to classify frames to hqos_id
        RC(mesa_vlan_vid_conf_get(NULL, vid, &state.vlan_vid_conf[i]));
        vlan_vid_conf = state.vlan_vid_conf[i];
        vlan_vid_conf.fid = vid;
        vlan_vid_conf.hqos_id = i;
        RC(mesa_vlan_vid_conf_set(NULL, vid, &vlan_vid_conf));

        // Configure the VLAN port membership
        RC(mesa_vlan_port_members_set(NULL, vid, &port_list));

        RC(mesa_hqos_get(NULL, port_eg, i, &hqos_conf));
        hqos_conf.priority_service = (i == 0) ? TRUE : FALSE;
        hqos_conf.min_rate = hqos_min_rate[i];
        RC(mesa_hqos_add(NULL, port_eg, i, &hqos_conf));
    }
    // snippet_end

    return 0;
}

static int hqos_clean()
{
    mesa_vid_t       vid;
    uint32_t         i;
    mesa_port_list_t port_list;
    uint32_t         dpl_cnt;

    dpl_cnt = mesa_capability(NULL, MESA_CAP_QOS_DPL_CNT);

    mesa_port_list_clear(&port_list);

    for (i = 0; i < 4; ++i) {
        RC(mesa_port_conf_set(NULL, state.ports[i], &state.port_conf[i]));
        RC(mesa_vlan_port_conf_set(NULL, state.ports[i], &state.vlan_conf[i]));
        RC(mesa_qos_port_conf_set(NULL, state.ports[i], &state.qos_conf[i]));
        RC(mesa_qos_port_dpl_conf_set(NULL, state.ports[i], dpl_cnt, &state.dpl_conf[i][0]));
    }

    for (i = 0, vid = 100; i < 4; ++i, vid += 100) {
        RC(mesa_hqos_del(NULL, state.port_eg, i));
        RC(mesa_vlan_vid_conf_set(NULL, vid, &state.vlan_vid_conf[i]));

        // Configure the VLAN port membership
        RC(mesa_vlan_port_members_set(NULL, vid, &port_list));
    }

    RC(mesa_hqos_port_conf_set(NULL, state.port_eg, &state.hqos_port_conf));

    return 0;
}

static const char *hqos_help() { return hqos_help_txt; }

#define NO_OPT 0xFFFFFFFF

static int hqos_run(int argc, const char *argv[])
{
    mesa_hqos_conf_t   hqos_conf;
    mesa_hqos_status_t hqos_status;
    uint32_t           hqos_id = ARGV_RUN_OPT_INT("hqos-id", "The HQOS-ID ", NO_OPT);

    uint32_t command = ARGV_RUN_INT("command", "The command to run.\n\
        value 0 is HQOS DEL.\n\
        value 1 is Configure HQOS shaper.\n\
        value 2 is Configure HQOS DWRR.\n\
        value 3 is Get actual Minimum Rate.\n");

    EXAMPLE_BARRIER(argc);

    if (hqos_id == NO_OPT) {
        cli_printf("hqos-id option is missing\n");
        return -1;
    }
    if (hqos_id >= 4) {
        cli_printf("hqos-id is invalid\n");
        return -1;
    }

    switch (command) {
    case 0:
        // snippet_begin ex-hqos-delete
        RC(mesa_hqos_del(NULL, state.port_eg, hqos_id));
        // snippet_end
        break;

    case 1:
        // Configure output shaper
        // snippet_begin ex-hqos-shaper-config
        RC(mesa_hqos_get(NULL, state.port_eg, hqos_id, &hqos_conf));
        //        // Disable queue shaper and queue DWRR
        //        for (i = 0; i < MESA_PRIO_ARRAY_SIZE; ++i) {
        //            hqos_conf.shaper_queue[i].rate = MESA_BITRATE_DISABLED;
        //        }
        hqos_conf.dwrr_cnt = 0;

        hqos_conf.shaper = hqos_shaper[hqos_id];
        RC(mesa_hqos_add(NULL, state.port_eg, hqos_id, &hqos_conf));
        // snippet_end
        break;

#if 0
    case 2:
        // Configure Queue Shaper
        // snippet_begin ex-hqos-queue-shaper-config
        RC(mesa_hqos_get(NULL, state.port_eg, hqos_id, &hqos_conf));
        // Disable output shaper and queue DWRR
        hqos_conf.dwrr_cnt = 0;
        hqos_conf.shaper.rate = MESA_BITRATE_DISABLED;

        memcpy(hqos_conf.shaper_queue, &hqos_shaper_queue[hqos_id],
               sizeof(hqos_conf.shaper_queue));
        RC(mesa_hqos_add(NULL, state.port_eg, hqos_id, &hqos_conf));
        // snippet_end
        break;
#endif

    case 2:
        // Configure HQOS DWRR
        // snippet_begin ex-hqos-dwrr-config
        RC(mesa_hqos_get(NULL, state.port_eg, hqos_id, &hqos_conf));
        // Disable output shaper and queue shaper
        hqos_conf.shaper.rate = MESA_BITRATE_DISABLED;
        //        for (i = 0; i < MESA_PRIO_ARRAY_SIZE; ++i) {
        //            hqos_conf.shaper_queue[i].rate = MESA_BITRATE_DISABLED;
        //        }

        hqos_conf.dwrr_cnt = 3;
        memcpy(hqos_conf.input_pct, hqos_input_pct, sizeof(hqos_conf.input_pct));
        RC(mesa_hqos_add(NULL, state.port_eg, hqos_id, &hqos_conf));
        // snippet_end
        break;

    case 3:
        // Get actual min_rate
        // snippet_begin ex-hqos-min-rate-get
        RC(mesa_hqos_status_get(NULL, state.port_eg, hqos_id, &hqos_status));
        cli_printf("Actual min_rate: %u\n", hqos_status.min_rate);
        // snippet_end
        break;

    default: cli_printf("Unknown command\n"); break;
    }

    return 0;
}

EXAMPLE(hqos, hqos_init, hqos_run, hqos_clean, hqos_help);
