// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static mesa_rc eflow_port_conf_set(mesa_port_no_t port_no, int access)
{
    mesa_vlan_port_conf_t conf;

    RC(mesa_vlan_port_conf_get(NULL, port_no, &conf));
    if (access) {
        // Access ports are unaware, mapping to unused VLAN
        conf.port_type = MESA_VLAN_PORT_TYPE_UNAWARE;
        conf.pvid = 4095;
    } else {
        // Trunk ports are C-ports, tagging all VLANs
        conf.port_type = MESA_VLAN_PORT_TYPE_C;
        conf.untagged_vid = MESA_VID_NULL;
    }
    RC(mesa_vlan_port_conf_set(NULL, port_no, &conf));
    return MESA_RC_OK;
}

#define EFLOW_VID_UNTAG 4096
#define EFLOW_PCP_ANY   8

#define VCE_ID_OFFSET   10000

typedef struct {
    mesa_port_no_t          aport;      // Access port
    mesa_port_no_t          tport;      // Trunk port
    mesa_vid_t              avid;       // Access port matching VID or EFLOW_VID_UNTAG
    mesa_pcp_t              apcp;       // Access port matching PCP or EFLOW_PCP_ANY
    mesa_vid_t              tvid;       // Trunk port VID (classified VID)
    mesa_pcp_t              tpcp;       // Trunk port PCP (classified PCP)
    mesa_dlb_policer_conf_t dlb;        // Classified VLAN policer
    mesa_dlb_policer_id_t   dlb_id;     // Allocated DLB ID
    mesa_iflow_id_t         flow_id;    // Allocated ingress flow ID
} eflow_t;

static struct {
    mesa_vlan_port_conf_t conf;
    eflow_t               eflow[MESA_VIDS];
} *eflow_state;

static mesa_rc eflow_add(eflow_t *f)
{
    mesa_vce_t        vce;
    mesa_tce_t        tce;
    mesa_iflow_conf_t conf;
    mesa_port_list_t  port_list;

    // Allocate and setup DLB policer
    RC(mesa_dlb_policer_alloc(NULL, 1, &f->dlb_id));
    RC(mesa_dlb_policer_conf_set(NULL, f->dlb_id, 0, &f->dlb));

    // Allocate and setup ingress flow mapping to DLB policer
    RC(mesa_iflow_alloc(NULL, &f->flow_id));
    RC(mesa_iflow_conf_get(NULL, f->flow_id, &conf));
    conf.dlb_enable = 1;
    conf.dlb_id = f->dlb_id;
    RC(mesa_iflow_conf_set(NULL, f->flow_id, &conf));

    // Add access port VCE mapping to classified VID, PCP and ingress flow
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = f->tvid;
    mesa_port_list_set(&vce.key.port_list, f->aport, 1);
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;
    if (f->avid == EFLOW_VID_UNTAG) {
        // Match untagged
        vce.key.tag.tagged = MESA_VCAP_BIT_0;
    } else {
        // Match and pop C-tag
        vce.key.tag.tagged = MESA_VCAP_BIT_1;
        vce.key.tag.vid.value = f->avid;
        vce.key.tag.vid.mask = 0xfff;
        if (f->apcp != EFLOW_PCP_ANY) {
            vce.key.tag.pcp.value = f->apcp;
            vce.key.tag.pcp.mask = 0x7;
        }
        vce.action.pop_enable = 1;
        vce.action.pop_cnt = 1;
    }
    vce.action.vid = f->tvid;
    vce.action.pcp_enable = 1;
    vce.action.pcp = f->tpcp;
    vce.action.prio_enable = 1;
    vce.action.prio = f->tpcp;
    vce.action.flow_id = f->flow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    // Add trunk port VCE mapping to ingress flow
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ANY, &vce));
    vce.id = (f->tvid + VCE_ID_OFFSET);
    mesa_port_list_set(&vce.key.port_list, f->tport, 1);
    // Match C-tag
    vce.key.tag.s_tag = MESA_VCAP_BIT_0;
    vce.key.tag.tagged = MESA_VCAP_BIT_1;
    vce.key.tag.vid.value = f->tvid;
    vce.key.tag.vid.mask = 0xfff;
    vce.action.flow_id = f->flow_id;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce));

    // Add access port TCE mapping back to VID and PCP
    RC(mesa_tce_init(NULL, &tce));
    tce.id = f->tvid;
    mesa_port_list_set(&tce.key.port_list, f->aport, 1);
    tce.key.vid = f->tvid;
    if (f->avid == EFLOW_VID_UNTAG) {
        tce.action.tag.tpid = MESA_TPID_SEL_NONE;
    } else {
        tce.action.tag.tpid = MESA_TPID_SEL_C;
        tce.action.tag.vid = (f->avid ? f->avid : MESA_TCE_VID_PRIORITY);
        if (f->apcp != EFLOW_PCP_ANY) {
            tce.action.tag.pcp_sel = MESA_PCP_SEL_FIXED;
            tce.action.tag.pcp = f->apcp;
        }
    }
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce));

    // Add ports to classified VLAN
    RC(mesa_vlan_port_members_get(NULL, f->tvid, &port_list));
    mesa_port_list_set(&port_list, f->aport, 1);
    mesa_port_list_set(&port_list, f->tport, 1);
    RC(mesa_vlan_port_members_set(NULL, f->tvid, &port_list));

    return MESA_RC_OK;
}

static int eflow_init(int argc, const char *argv[])
{
    if ((eflow_state = calloc(1, sizeof(*eflow_state))) == NULL) {
        cli_printf("calloc failed\n");
        return -1;
    }
    RC(mesa_vlan_port_conf_get(NULL, 0, &eflow_state->conf));
    return 0;
}

static int eflow_run(int argc, const char *argv[])
{
    mesa_port_no_t aport = ARGV_RUN_INT("aport", "Access port");
    mesa_vid_t     avid = ARGV_RUN_OPT_INT("avid", "Access port VID, default untagged", EFLOW_VID_UNTAG);
    mesa_vid_t     apcp = ARGV_RUN_OPT_INT("apcp", "Access port PCP, default any", EFLOW_PCP_ANY);
    mesa_port_no_t tport = ARGV_RUN_INT("tport", "Trunk port");
    mesa_vid_t     tvid = ARGV_RUN_INT("tvid", "Trunk port VID (classified VID)");
    mesa_vid_t     tpcp = ARGV_RUN_INT("tpcp", "Trunk port PCP (classified PCP)");
    mesa_bitrate_t rate = ARGV_RUN_OPT_INT("rate", "VLAN policer rate [kbps], default disabled", MESA_BITRATE_DISABLED);
    eflow_t        f;

    EXAMPLE_BARRIER(argc);

    if (tvid >= MESA_VIDS) {
        cli_printf("Illegal tvid: %u\n", tvid);
        return -1;
    }

    // VLAN port configuration
    RC(eflow_port_conf_set(aport, 1));
    RC(eflow_port_conf_set(tport, 0));

    // Flow configuration
    memset(&f, 0, sizeof(f));
    f.aport = aport;
    f.tport = tport;
    f.avid = avid;
    f.apcp = apcp;
    f.tvid = tvid;
    f.tpcp = tpcp;
    f.dlb.type = MESA_POLICER_TYPE_SINGLE;
    f.dlb.enable = 1;
    f.dlb.cbs = 4096;
    f.dlb.cir = rate;
    RC(eflow_add(&f));
    eflow_state->eflow[tvid] = f;

    return 0;
}

static int eflow_uninit(void)
{
    mesa_vid_t       vid;
    eflow_t          *f;
    mesa_port_list_t port_list;

    for (vid = 1; vid < MESA_VIDS; vid++) {
        f = &eflow_state->eflow[vid];
        if (f->tvid != MESA_VID_NULL) {
            RC(mesa_dlb_policer_free(NULL, f->dlb_id));
            RC(mesa_iflow_free(NULL, f->flow_id));
            RC(mesa_vce_del(NULL, f->tvid));
            RC(mesa_vce_del(NULL, f->tvid + VCE_ID_OFFSET));
            RC(mesa_tce_del(NULL, f->tvid));
            RC(mesa_vlan_port_members_get(NULL, f->tvid, &port_list));
            mesa_port_list_set(&port_list, f->aport, 0);
            mesa_port_list_set(&port_list, f->tport, 0);
            RC(mesa_vlan_port_members_set(NULL, f->tvid, &port_list));
            RC(mesa_vlan_port_conf_set(NULL, f->aport, &eflow_state->conf));
            RC(mesa_vlan_port_conf_set(NULL, f->tport, &eflow_state->conf));
        }
    }
    free(eflow_state);
    return 0;
}

static const char *eflow_help(void)
{
    return "Enhanced VLAN example\n";
}

EXAMPLE(eflow, eflow_init, eflow_run, eflow_uninit, eflow_help);
