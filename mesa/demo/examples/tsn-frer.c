// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

static struct {
    mesa_vid_t             vid;
    int                    iflow_cnt;
    mesa_iflow_id_t        iflow_id[3];
    int                    vce_cnt;
    int                    tce_cnt;
    int                    mid_cnt;
    mesa_frer_mstream_id_t mid[2];
    mesa_frer_cstream_id_t cid;
} state;

static int frer_init(int argc, const char *argv[])
{
    mesa_port_no_t          uport = ARGV_INT("uport", "Untagged port");
    mesa_port_no_t          rport = ARGV_INT("rport", "R-tagged port");
    mesa_port_no_t          cport = ARGV_INT("cport", "C-tagged port (inner R-tag)");
    mesa_port_list_t        port_list; 
    mesa_iflow_id_t         *iflow_id;
    mesa_iflow_conf_t       iflow_conf; 
    mesa_frer_stream_conf_t stream_conf;
    mesa_frer_mstream_id_t  *mid;
    mesa_vlan_vid_conf_t    vid_conf;
    mesa_vcl_port_conf_t    vcl_conf;
    mesa_vce_t              vce;
    mesa_tce_t              tce;
    int                     i;

    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_L2_FRER) == 0) {
        cli_printf("FRER not supported\n");
        return -1;
    }

    memset(&state, 0, sizeof(state));
    state.vid = 10;
    state.cid = 10;

    // Disable learning in VLAN
    RC(mesa_vlan_vid_conf_get(NULL, state.vid, &vid_conf));
    vid_conf.learning = 0;
    RC(mesa_vlan_vid_conf_set(NULL, state.vid, &vid_conf));

    // Add ports to VLAN
    RC(mesa_vlan_port_members_get(NULL, state.vid, &port_list));
    mesa_port_list_set(&port_list, uport, 1);
    mesa_port_list_set(&port_list, rport, 1);
    mesa_port_list_set(&port_list, cport, 1);
    RC(mesa_vlan_port_members_set(NULL, state.vid, &port_list));

    // Allocate ingress flow for untagged port, with sequence generation
    iflow_id = &state.iflow_id[state.iflow_cnt];
    RC(mesa_iflow_alloc(NULL, iflow_id));
    state.iflow_cnt++;
    RC(mesa_iflow_conf_get(NULL, *iflow_id, &iflow_conf));
    iflow_conf.frer.generation = 1;
    RC(mesa_iflow_conf_set(NULL, *iflow_id, &iflow_conf));

    // Enable DMAC classification for untagged port
    RC(mesa_vcl_port_conf_get(NULL, uport, &vcl_conf));
    vcl_conf.dmac_dip = 1;
    RC(mesa_vcl_port_conf_set(NULL, uport, &vcl_conf));

    // Add untagged port VCE matching DMAC 00:00:00:00:00:02
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = (1 + state.vce_cnt);
    mesa_port_list_set(&vce.key.port_list, uport, 1);
    for (i = 0; i < 6; i++) {
        vce.key.mac.dmac.value[i] = (i == 5 ? 2 : 0);
        vce.key.mac.dmac.mask[i] = 0xff;
    }
    vce.action.vid = state.vid;
    vce.action.flow_id = *iflow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));
    state.vce_cnt++;

    // Setup compound stream with sequence recovery
    RC(mesa_frer_cstream_conf_get(NULL, state.cid, &stream_conf));
    stream_conf.recovery = 1;
    stream_conf.alg = MESA_FRER_RECOVERY_ALG_MATCH;
    stream_conf.reset_time = 1000;
    RC(mesa_frer_cstream_conf_set(NULL, state.cid, &stream_conf));    

    // Allocate and setup member stream from R-tagged port to untagged port
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, uport, 1);
    mid = &state.mid[state.mid_cnt];
    RC(mesa_frer_mstream_alloc(NULL, &port_list, mid));
    state.mid_cnt++;
    RC(mesa_frer_mstream_conf_get(NULL, *mid, uport, &stream_conf));
    stream_conf.cstream_id = state.cid;
    RC(mesa_frer_mstream_conf_set(NULL, *mid, uport, &stream_conf));

    // Allocate ingress flow for R-tagged port, mapping to member stream
    iflow_id = &state.iflow_id[state.iflow_cnt];
    RC(mesa_iflow_alloc(NULL, iflow_id));
    state.iflow_cnt++;
    RC(mesa_iflow_conf_get(NULL, *iflow_id, &iflow_conf));
    iflow_conf.frer.mstream_enable = 1;
    iflow_conf.frer.mstream_id = *mid;
    iflow_conf.cut_through_disable = 1;
    RC(mesa_iflow_conf_set(NULL, *iflow_id, &iflow_conf));

    // Enable DMAC classification for R-tagged port
    RC(mesa_vcl_port_conf_get(NULL, rport, &vcl_conf));
    vcl_conf.dmac_dip = 1;
    RC(mesa_vcl_port_conf_set(NULL, rport, &vcl_conf));

    // Add R-tagged port VCE matching DMAC 00:00:00:00:00:01
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = (1 + state.vce_cnt);
    mesa_port_list_set(&vce.key.port_list, rport, 1);
    for (i = 0; i < 6; i++) {
        vce.key.mac.dmac.value[i] = (i == 5 ? 1 : 0);
        vce.key.mac.dmac.mask[i] = 0xff;
    }
    vce.action.vid = state.vid;
    vce.action.flow_id = *iflow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));
    state.vce_cnt++;

    // Allocate and setup member stream from C-tagged port to untagged port
    mesa_port_list_clear(&port_list);
    mesa_port_list_set(&port_list, uport, 1);
    mid = &state.mid[state.mid_cnt];
    RC(mesa_frer_mstream_alloc(NULL, &port_list, mid));
    state.mid_cnt++;
    RC(mesa_frer_mstream_conf_get(NULL, *mid, uport, &stream_conf));
    stream_conf.cstream_id = state.cid;
    RC(mesa_frer_mstream_conf_set(NULL, *mid, uport, &stream_conf));

    // Allocate ingress flow for C-tagged port, mapping to member stream
    iflow_id = &state.iflow_id[state.iflow_cnt];
    RC(mesa_iflow_alloc(NULL, iflow_id));
    state.iflow_cnt++;
    RC(mesa_iflow_conf_get(NULL, *iflow_id, &iflow_conf));
    iflow_conf.frer.mstream_enable = 1;
    iflow_conf.frer.mstream_id = *mid;
    iflow_conf.cut_through_disable = 1;
    RC(mesa_iflow_conf_set(NULL, *iflow_id, &iflow_conf));
    
    // Enable DMAC classification for C-tagged port
    RC(mesa_vcl_port_conf_get(NULL, cport, &vcl_conf));
    vcl_conf.dmac_dip = 1;
    RC(mesa_vcl_port_conf_set(NULL, cport, &vcl_conf));

    // Add C-tagged port VCE matching DMAC 00:00:00:00:00:01 and popping tag
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = (1 + state.vce_cnt);
    mesa_port_list_set(&vce.key.port_list, cport, 1);
    for (i = 0; i < 6; i++) {
        vce.key.mac.dmac.value[i] = (i == 5 ? 1 : 0);
        vce.key.mac.dmac.mask[i] = 0xff;
    }
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;
    vce.key.tag.tagged = MESA_VCAP_BIT_1;
    vce.key.tag.vid.value = state.vid;
    vce.key.tag.vid.mask = 0xfff;
    vce.action.pop_enable = 1;
    vce.action.pop_cnt = 1;
    vce.action.vid = state.vid;
    vce.action.flow_id = *iflow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));
    state.vce_cnt++;

    // Add untagged port TCE
    RC(mesa_tce_init(NULL, &tce));
    tce.id = (1 + state.tce_cnt);
    mesa_port_list_set(&tce.key.port_list, uport, 1);
    tce.key.vid = state.vid;
    tce.action.tag.tpid = MESA_TPID_SEL_NONE;
    tce.action.rtag.pop = 1;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));
    state.tce_cnt++;

    // Add R-tagged port TCE
    RC(mesa_tce_init(NULL, &tce));
    tce.id = (1 + state.tce_cnt);
    mesa_port_list_set(&tce.key.port_list, rport, 1);
    tce.key.vid = state.vid;
    tce.action.tag.tpid = MESA_TPID_SEL_NONE;
    tce.action.rtag.sel = MESA_RTAG_SEL_OUTER;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));
    state.tce_cnt++;

    // Add C-tagged port TCE
    RC(mesa_tce_init(NULL, &tce));
    tce.id = (1 + state.tce_cnt);
    mesa_port_list_set(&tce.key.port_list, cport, 1);
    tce.key.vid = state.vid;
    tce.action.tag.tpid = MESA_TPID_SEL_C;
    tce.action.rtag.sel = MESA_RTAG_SEL_INNER;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));
    state.tce_cnt++;

    return 0;
}

static void frer_stat(const char *name, uint64_t cnt)
{
    char buf[80];
    
    sprintf(buf, "%s:", name);
    cli_printf("%-19s%19llu\n", buf, cnt);
}

static int frer_run(int argc, const char *argv[])
{
    mesa_frer_counters_t c;

    EXAMPLE_BARRIER(argc);

    RC(mesa_frer_cstream_cnt_get(NULL, state.cid, &c));
    cli_printf("Compound Stream %u counters:\n", state.cid);
    frer_stat("OutOfOrder", c.out_of_order_packets);
    frer_stat("Rogue", c.rogue_packets);
    frer_stat("Passed", c.passed_packets);
    frer_stat("Discarded", c.discarded_packets);
    frer_stat("Lost", c.lost_packets);
    frer_stat("Tagless", c.tagless_packets);
    frer_stat("Resets", c.resets);

    return 0;
}

static int frer_uninit(void)
{
    mesa_port_list_t port_list; 
    int              i;
    
    mesa_port_list_clear(&port_list);
    RC(mesa_vlan_port_members_set(NULL, state.vid, &port_list));
    for (i = 0; i < state.iflow_cnt; i++) {
        RC(mesa_iflow_free(NULL, state.iflow_id[i]));
    }
    for (i = 0; i < state.mid_cnt; i++) {
        RC(mesa_frer_mstream_free(NULL, state.mid[i]));
    }
    for (i = 0; i < state.vce_cnt; i++) {
        RC(mesa_vce_del(NULL, i + 1));
    }
    for (i = 0; i < state.tce_cnt; i++) {
        RC(mesa_tce_del(NULL, i + 1));
    }
    return 0;
}

static const char *frer_help(void)
{
    return "FRER example\n";
}

EXAMPLE(frer, frer_init, frer_run, frer_uninit, frer_help);
