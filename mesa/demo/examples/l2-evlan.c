// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static struct {
    mesa_ingress_cnt_id_t icnt_id;
    mesa_egress_cnt_id_t  ecnt_id;
    mesa_dlb_policer_id_t dlb_id;
    mesa_iflow_id_t       iflow_id;
    mesa_eflow_id_t       eflow_id;
} evlan_state;

static int evlan_init(int argc, const char *argv[])
{
    mesa_port_no_t          iport = ARGV_INT("iport", "Ingress port");
    mesa_port_no_t          eport = ARGV_INT("eport", "Egress port");
    mesa_dlb_policer_conf_t dlb_conf;
    mesa_iflow_conf_t       iflow_conf;
    mesa_vce_t              vce;
    mesa_eflow_conf_t       eflow_conf;
    mesa_tce_t              tce;
    mesa_port_list_t        port_list;
    uint32_t                cap = mesa_capability(NULL, MESA_CAP_L2_XDLB);

    EXAMPLE_BARRIER(argc);

    memset(&evlan_state, 0, sizeof(evlan_state));

    if (cap) {
        // Allocate and setup DLB policer
        RC(mesa_dlb_policer_alloc(NULL, 1, &evlan_state.dlb_id));
        RC(mesa_dlb_policer_conf_get(NULL, evlan_state.dlb_id, 0, &dlb_conf));
        dlb_conf.type = MESA_POLICER_TYPE_SINGLE;
        dlb_conf.enable = 1;
        dlb_conf.cbs = 4096;
        dlb_conf.cir = 1000;
        RC(mesa_dlb_policer_conf_set(NULL, evlan_state.dlb_id, 0, &dlb_conf));

        // Allocate ingress counters
        RC(mesa_ingress_cnt_alloc(NULL, 1, &evlan_state.icnt_id));

        // Allocate and setup ingress flow mapping to ingress counters and DLB
        // policer
        RC(mesa_iflow_alloc(NULL, &evlan_state.iflow_id));
        RC(mesa_iflow_conf_get(NULL, evlan_state.iflow_id, &iflow_conf));
        iflow_conf.cnt_enable = 1;
        iflow_conf.cnt_id = evlan_state.icnt_id;
        iflow_conf.dlb_enable = 1;
        iflow_conf.dlb_id = evlan_state.dlb_id;
        RC(mesa_iflow_conf_set(NULL, evlan_state.iflow_id, &iflow_conf));
    }

    // Add ingress port VCE matching C-VID 10
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = 1;
    mesa_port_list_set(&vce.key.port_list, iport, 1);
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;
    vce.key.tag.tagged = MESA_VCAP_BIT_1;
    vce.key.tag.vid.value = 10;
    vce.key.tag.vid.mask = 0xfff;
    vce.action.pop_enable = 1;
    vce.action.pop_cnt = 1;
    vce.action.vid = 10;
    vce.action.flow_id = evlan_state.iflow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    if (cap) {
        // Allocate egress counters
        RC(mesa_egress_cnt_alloc(NULL, 1, &evlan_state.ecnt_id));

        // Allocate and setup egress flow mapping to egress counters
        RC(mesa_eflow_alloc(NULL, &evlan_state.eflow_id));
        RC(mesa_eflow_conf_get(NULL, evlan_state.eflow_id, &eflow_conf));
        eflow_conf.cnt_enable = 1;
        eflow_conf.cnt_id = evlan_state.icnt_id;
        RC(mesa_eflow_conf_set(NULL, evlan_state.eflow_id, &eflow_conf));
    }

    // Add trunk port TCE mapping to S-VID 20
    RC(mesa_tce_init(NULL, &tce));
    tce.id = 1;
    mesa_port_list_set(&tce.key.port_list, eport, 1);
    tce.key.vid = 10;
    tce.action.tag.tpid = MESA_TPID_SEL_S;
    tce.action.tag.vid = 20;
    tce.action.flow_id = evlan_state.eflow_id;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));

    // Add ports to classified VLAN
    RC(mesa_vlan_port_members_get(NULL, 10, &port_list));
    mesa_port_list_set(&port_list, iport, 1);
    mesa_port_list_set(&port_list, eport, 1);
    RC(mesa_vlan_port_members_set(NULL, 10, &port_list));

    return 0;
}

static void evlan_stat(const char *name, uint64_t cnt)
{
    char buf[80];

    sprintf(buf, "%s:", name);
    cli_printf("%-19s%19llu\n", buf, cnt);
}

static int evlan_run(int argc, const char *argv[])
{
    mesa_ingress_counters_t icnt;
    mesa_egress_counters_t  ecnt;

    EXAMPLE_BARRIER(argc);

    if (mesa_capability(NULL, MESA_CAP_L2_XSTAT)) {
        RC(mesa_ingress_cnt_get(NULL, evlan_state.icnt_id, 0, &icnt));
        RC(mesa_egress_cnt_get(NULL, evlan_state.ecnt_id, 0, &ecnt));
        evlan_stat("Rx Green Frames", icnt.rx_green.frames);
        evlan_stat("Rx Yellow Frames", icnt.rx_yellow.frames);
        evlan_stat("Rx Red Frames", icnt.rx_red.frames);
        evlan_stat("Rx Green Bytes", icnt.rx_green.bytes);
        evlan_stat("Rx Yellow Bytes", icnt.rx_yellow.bytes);
        evlan_stat("Tx Green Frames", ecnt.tx_green.frames);
        evlan_stat("Tx Yellow Frames", ecnt.tx_yellow.frames);
        evlan_stat("Tx Green Bytes", ecnt.tx_green.bytes);
        evlan_stat("Tx Yellow Bytes", ecnt.tx_yellow.bytes);
    }
    return 0;
}

static int evlan_uninit(void)
{
    mesa_port_list_t port_list;

    if (mesa_capability(NULL, MESA_CAP_L2_XDLB)) {
        RC(mesa_dlb_policer_free(NULL, evlan_state.dlb_id));
        RC(mesa_ingress_cnt_free(NULL, evlan_state.icnt_id));
        RC(mesa_iflow_free(NULL, evlan_state.iflow_id));
        RC(mesa_egress_cnt_free(NULL, evlan_state.ecnt_id));
        RC(mesa_eflow_free(NULL, evlan_state.eflow_id));
    }
    RC(mesa_vce_del(NULL, 1));
    RC(mesa_tce_del(NULL, 1));
    mesa_port_list_clear(&port_list);
    RC(mesa_vlan_port_members_set(NULL, 10, &port_list));

    return 0;
}

static const char *evlan_help(void) { return "Enhanced VLAN example\n"; }

EXAMPLE(evlan, evlan_init, evlan_run, evlan_uninit, evlan_help);
