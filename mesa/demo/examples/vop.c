// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

static uint8_t                rx_uc_addr[6] = {0,0,0,0,5,6};
static uint8_t                tx_uc_addr[6] = {0,0,0,0,5,7};
static uint8_t                mc_addr[6] = {0x01,0x80,0xC2,0x00,0x00,0x30};
static uint8_t                megid[MESA_OAM_MEG_ID_LENGTH] = {"Microchip MEG"};
static mesa_prio_t            prio = 5;
static uint16_t               peer_mepid = 1;
static uint16_t               mepid = 2;
static mesa_voe_ccm_period_t  period = MESA_VOE_CCM_PERIOD_1_SEC;
static mesa_vid_t             pvid = 1;

static const char *vop_help_txt = "\
This is a Versatile OAM Processor (VOP) test.\n\
\n\
One port will be in front of the VOP. One port will be behind the VOP.\n\
Either a port Down-VOP or a VLAN Down-VOP is created based on parameter 'vid'.\n\
";

static struct {
    mesa_port_no_t           front_port;
    mesa_port_no_t           back_port;
    mesa_vid_t               vid;
    mesa_vid_t               level;
    mesa_vlan_port_conf_t    vlan_conf[2];
    mesa_qos_port_conf_t     qos_conf[2];
    mesa_voe_idx_t           voe_idx;
    mesa_iflow_id_t          iflow_id;
    mesa_eflow_id_t          eflow_id;
    mesa_vce_id_t            front_vce_id;
    mesa_vce_id_t            back_vce_id;
    mesa_tce_id_t            tce_id;
    mesa_tce_id_t            inj_tce_id;
    uint32_t                 v1, v2;
    uint32_t                 family;
} state;

static int init_port_configuration(mesa_port_no_t port,  mesa_prio_t prio,  uint32_t idx)
{
    mesa_vlan_port_conf_t    vlan_conf;
    mesa_qos_port_conf_t     qos_conf;

    /* Configure port to C tag aware */
    RC(mesa_vlan_port_conf_get(NULL, port, &state.vlan_conf[idx]));
    vlan_conf = state.vlan_conf[idx];
    vlan_conf.port_type = MESA_VLAN_PORT_TYPE_C;
    vlan_conf.frame_type = MESA_VLAN_FRAME_ALL;
    RC(mesa_vlan_port_conf_set(NULL, port, &vlan_conf));

    RC(mesa_qos_port_conf_get(NULL, port, &state.qos_conf[idx]));
    qos_conf = state.qos_conf[idx];
    qos_conf.cosid = prio;
    qos_conf.default_prio = prio;
    qos_conf.tag.pcp = prio;
    qos_conf.tag.class_enable = TRUE;
    qos_conf.tag.pcp_dei_map[0][0].prio = prio;
    RC(mesa_qos_port_conf_set(NULL, port, &qos_conf));

    return 0;
}

static uint32_t vce_level_mask(uint32_t l_level, uint32_t h_level)
{
    uint32_t mask;

    mask = (0x01 << (h_level - l_level)) - 1;   // "don't care" mask value is calculated
    mask <<= l_level;                           // mask is rotated to cover levels
    mask = ~mask;                               // Mask is complimented as "don't care" is '0'
    mask = mask & 0xFF;
    return (mask);
}

static int v1_port_voe_configuration(uint32_t level)
{
    mesa_voe_allocation_t  voe_param;
    mesa_iflow_conf_t      iflow_conf;
    mesa_vce_t             vce_conf;
    mesa_voe_conf_t        voe_conf;

    state.front_vce_id = 1;
    state.back_vce_id = 2;

    // snippet_begin ex-port-voe-alloc
    // Allocate the VOE
    voe_param.type = MESA_VOE_TYPE_PORT;
    voe_param.port = state.front_port;
    voe_param.direction = MESA_OAM_DIRECTION_DOWN;
    RC(mesa_voe_alloc(NULL, &voe_param, &state.voe_idx));

    // snippet_endbegin ex-iflow-alloc
    RC(mesa_iflow_alloc(NULL, &state.iflow_id));
    RC(mesa_iflow_conf_get(NULL, state.iflow_id, &iflow_conf));
    iflow_conf.voe_idx = state.voe_idx;
    iflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_iflow_conf_set(NULL, state.iflow_id, &iflow_conf));

    // snippet_endbegin ex-add-vce
    // Add the front port VCE
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce_conf));
    vce_conf.id = state.front_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.front_port, TRUE);
    vce_conf.key.type = MESA_VCE_TYPE_ETYPE;
    vce_conf.key.tag.tagged = MESA_VCAP_BIT_0;
    vce_conf.key.frame.etype.etype.value[0] = 0x89;
    vce_conf.key.frame.etype.etype.value[1] = 0x02;
    vce_conf.key.frame.etype.etype.mask[0] = 0xFF;
    vce_conf.key.frame.etype.etype.mask[1] = 0xFF;
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = vce_level_mask(0, level);
    vce_conf.action.flow_id = state.iflow_id;
    vce_conf.action.oam_detect = MESA_OAM_DETECT_UNTAGGED;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // Add the back port VCE
    vce_conf.id = state.back_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.back_port, TRUE);
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = 0;
    vce_conf.action.flow_id = MESA_IFLOW_ID_NONE;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // snippet_endbegin ex-port-voe-config
    RC(mesa_voe_conf_get(NULL, state.voe_idx, &voe_conf));
    voe_conf.enable = TRUE;
    memcpy(voe_conf.unicast_mac.addr, rx_uc_addr, sizeof(voe_conf.unicast_mac.addr));
    voe_conf.meg_level = level;
    voe_conf.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_conf.loop_iflow_id = state.iflow_id;
    voe_conf.block_mel_high = FALSE;
    RC(mesa_voe_conf_set(NULL, state.voe_idx, &voe_conf));
    // snippet_end

    return 0;
}

static int v2_port_voe_configuration(uint32_t level)
{
    mesa_voe_allocation_t  voe_param;
    mesa_iflow_conf_t      iflow_conf;
    mesa_eflow_conf_t      eflow_conf;
    mesa_vce_t             vce_conf;
    mesa_tce_t             tce_conf;
    mesa_voe_conf_t        voe_conf;

    state.front_vce_id = 1;
    state.back_vce_id = 2;
    state.tce_id = 1;
    state.inj_tce_id = 2;

    // snippet_begin ex-port-voe-alloc
    // Allocate the VOE
    voe_param.type = MESA_VOE_TYPE_PORT;
    voe_param.port = state.front_port;
    voe_param.direction = MESA_OAM_DIRECTION_DOWN;
    RC(mesa_voe_alloc(NULL, &voe_param, &state.voe_idx));

    // snippet_endbegin ex-iflow-alloc
    RC(mesa_iflow_alloc(NULL, &state.iflow_id));
    RC(mesa_iflow_conf_get(NULL, state.iflow_id, &iflow_conf));
    iflow_conf.voe_idx = state.voe_idx;
    iflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_iflow_conf_set(NULL, state.iflow_id, &iflow_conf));

    // snippet_endbegin ex-eflow-alloc
    RC(mesa_eflow_alloc(NULL, &state.eflow_id));
    RC(mesa_eflow_conf_get(NULL, state.eflow_id, &eflow_conf));
    eflow_conf.voe_idx = state.voe_idx;
    eflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_eflow_conf_set(NULL, state.eflow_id, &eflow_conf));

    // snippet_endbegin ex-add-vce
    // Add the front port VCE
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce_conf));
    vce_conf.id = state.front_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.front_port, TRUE);
    vce_conf.key.type = MESA_VCE_TYPE_ETYPE;
    vce_conf.key.tag.tagged = MESA_VCAP_BIT_0;
    vce_conf.key.frame.etype.etype.value[0] = 0x89;
    vce_conf.key.frame.etype.etype.value[1] = 0x02;
    vce_conf.key.frame.etype.etype.mask[0] = 0xFF;
    vce_conf.key.frame.etype.etype.mask[1] = 0xFF;
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = vce_level_mask(0, level);
    vce_conf.action.flow_id = state.iflow_id;
    vce_conf.action.oam_detect = MESA_OAM_DETECT_UNTAGGED;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // Add the back port VCE
    vce_conf.id = state.back_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.back_port, TRUE);
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = 0;
    vce_conf.action.flow_id = MESA_IFLOW_ID_NONE;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // snippet_endbegin ex-add-tce
    // Add injection TCE
    RC(mesa_tce_init(NULL, &tce_conf));
    tce_conf.id = state.inj_tce_id;
    mesa_port_list_clear(&tce_conf.key.port_list);
    mesa_port_list_set(&tce_conf.key.port_list, state.front_port, TRUE);
    tce_conf.key.flow_enable = TRUE;
    tce_conf.key.flow_id = state.iflow_id;
    tce_conf.action.flow_id = state.eflow_id;
    tce_conf.action.tag.tpid = MESA_TPID_SEL_NONE;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce_conf));

    // Add forwarding TCE
    RC(mesa_tce_init(NULL, &tce_conf));
    tce_conf.id = state.tce_id;
    mesa_port_list_clear(&tce_conf.key.port_list);
    mesa_port_list_set(&tce_conf.key.port_list, state.front_port, TRUE);
    tce_conf.key.vid = pvid;
    tce_conf.action.flow_id = state.eflow_id;
    tce_conf.action.tag.tpid = MESA_TPID_SEL_NONE;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce_conf));

    // snippet_endbegin ex-port-voe-config
    RC(mesa_voe_conf_get(NULL, state.voe_idx, &voe_conf));
    voe_conf.enable = TRUE;
    memcpy(voe_conf.unicast_mac.addr, rx_uc_addr, sizeof(voe_conf.unicast_mac.addr));
    voe_conf.meg_level = level;
    voe_conf.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_conf.loop_iflow_id = state.iflow_id;
    voe_conf.block_mel_high = FALSE;
    RC(mesa_voe_conf_set(NULL, state.voe_idx, &voe_conf));
    // snippet_end

    return 0;
}

static int v1_service_voe_configuration(uint32_t level)
{
    mesa_voe_allocation_t  voe_param;
    mesa_iflow_conf_t      iflow_conf;
    mesa_eflow_conf_t      eflow_conf;
    mesa_vce_t             vce_conf;
    mesa_tce_t             tce_conf;
    mesa_voe_conf_t        voe_conf;

    state.front_vce_id = 1;
    state.back_vce_id = 2;
    state.tce_id = 1;
    state.inj_tce_id = 2;

    // snippet_begin ex-service-voe-alloc
    // Allocate the VOE
    voe_param.type = MESA_VOE_TYPE_SERVICE;
    voe_param.port = state.front_port;
    voe_param.direction = MESA_OAM_DIRECTION_DOWN;
    RC(mesa_voe_alloc(NULL, &voe_param, &state.voe_idx));

    // snippet_endbegin ex-iflow-alloc
    // Allocate the ingress IFLOW
    RC(mesa_iflow_alloc(NULL, &state.iflow_id));
    RC(mesa_iflow_conf_get(NULL, state.iflow_id, &iflow_conf));
    iflow_conf.voe_idx = state.voe_idx;
    iflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_iflow_conf_set(NULL, state.iflow_id, &iflow_conf));

    // snippet_endbegin ex-eflow-alloc
    RC(mesa_eflow_alloc(NULL, &state.eflow_id));
    RC(mesa_eflow_conf_get(NULL, state.eflow_id, &eflow_conf));
    eflow_conf.voe_idx = state.voe_idx;
    eflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_eflow_conf_set(NULL, state.eflow_id, &eflow_conf));

    // snippet_endbegin ex-add-vce
    // Add the front port VCE
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce_conf));
    vce_conf.id = state.front_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.front_port, TRUE);
    vce_conf.key.type = MESA_VCE_TYPE_ETYPE;
    vce_conf.key.tag.tagged = MESA_VCAP_BIT_1;
    vce_conf.key.tag.s_tag = MESA_VCAP_BIT_ANY;
    vce_conf.key.tag.vid.value = state.vid;
    vce_conf.key.tag.vid.mask = 0xFFFF;
    vce_conf.key.tag.dei = MESA_VCAP_BIT_ANY;
    vce_conf.key.tag.pcp.mask = 0;
    vce_conf.key.frame.etype.etype.value[0] = 0x89;
    vce_conf.key.frame.etype.etype.value[1] = 0x02;
    vce_conf.key.frame.etype.etype.mask[0] = 0xFF;
    vce_conf.key.frame.etype.etype.mask[1] = 0xFF;
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = vce_level_mask(0, level);
    vce_conf.action.flow_id = state.iflow_id;
    vce_conf.action.oam_detect = MESA_OAM_DETECT_SINGLE_TAGGED;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // Add the back port VCE
    vce_conf.id = state.back_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.back_port, TRUE);
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = 0;
    vce_conf.action.flow_id = MESA_IFLOW_ID_NONE;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // snippet_endbegin ex-add-tce
    // Add injection TCE
    RC(mesa_tce_init(NULL, &tce_conf));
    tce_conf.id = state.inj_tce_id;
    mesa_port_list_clear(&tce_conf.key.port_list);
    mesa_port_list_set(&tce_conf.key.port_list, state.front_port, TRUE);
    tce_conf.key.flow_enable = TRUE;
    tce_conf.key.flow_id = state.iflow_id;
    tce_conf.action.flow_id = state.eflow_id;
    tce_conf.action.tag.tpid = MESA_TPID_SEL_PORT;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce_conf));

    // Add forwarding TCE
    RC(mesa_tce_init(NULL, &tce_conf));
    tce_conf.id = state.tce_id;
    mesa_port_list_clear(&tce_conf.key.port_list);
    mesa_port_list_set(&tce_conf.key.port_list, state.front_port, TRUE);
    tce_conf.key.vid = state.vid;
    tce_conf.action.flow_id = state.eflow_id;
    tce_conf.action.tag.tpid = MESA_TPID_SEL_PORT;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce_conf));

    // snippet_endbegin ex-service-voe-config
    RC(mesa_voe_conf_get(NULL, state.voe_idx, &voe_conf));
    voe_conf.enable = TRUE;
    memcpy(voe_conf.unicast_mac.addr, rx_uc_addr, sizeof(voe_conf.unicast_mac.addr));
    voe_conf.meg_level = level;
    voe_conf.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_conf.loop_iflow_id = state.iflow_id;
    voe_conf.block_mel_high = FALSE;
    RC(mesa_voe_conf_set(NULL, state.voe_idx, &voe_conf));
    // snippet_end

    return 0;
}

static int v2_service_voe_configuration(uint32_t level)
{
    mesa_voe_allocation_t  voe_param;
    mesa_iflow_conf_t      iflow_conf;
    mesa_eflow_conf_t      eflow_conf;
    mesa_vce_t             vce_conf;
    mesa_tce_t             tce_conf;
    mesa_voe_conf_t        voe_conf;

    state.front_vce_id = 1;
    state.back_vce_id = 2;
    state.tce_id = 1;

    // snippet_begin ex-service-voe-alloc
    // Allocate the VOE
    voe_param.type = MESA_VOE_TYPE_SERVICE;
    voe_param.port = state.front_port;
    voe_param.direction = MESA_OAM_DIRECTION_DOWN;
    RC(mesa_voe_alloc(NULL, &voe_param, &state.voe_idx));

    // snippet_endbegin ex-iflow-alloc
    // Allocate the ingress IFLOW
    RC(mesa_iflow_alloc(NULL, &state.iflow_id));
    RC(mesa_iflow_conf_get(NULL, state.iflow_id, &iflow_conf));
    iflow_conf.voe_idx = state.voe_idx;
    iflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_iflow_conf_set(NULL, state.iflow_id, &iflow_conf));

    // snippet_endbegin ex-eflow-alloc
    RC(mesa_eflow_alloc(NULL, &state.eflow_id));
    RC(mesa_eflow_conf_get(NULL, state.eflow_id, &eflow_conf));
    eflow_conf.voe_idx = state.voe_idx;
    eflow_conf.voi_idx = MESA_VOI_IDX_NONE;
    RC(mesa_eflow_conf_set(NULL, state.eflow_id, &eflow_conf));

    // snippet_endbegin ex-add-vce
    // Add the front port VCE
    RC(mesa_vce_init(NULL, MESA_VCE_TYPE_ETYPE, &vce_conf));
    vce_conf.id = state.front_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.front_port, TRUE);
    vce_conf.key.type = MESA_VCE_TYPE_ETYPE;
    vce_conf.key.tag.tagged = MESA_VCAP_BIT_1;
    vce_conf.key.tag.s_tag = MESA_VCAP_BIT_ANY;
    vce_conf.key.tag.vid.value = state.vid;
    vce_conf.key.tag.vid.mask = 0xFFFF;
    vce_conf.key.tag.dei = MESA_VCAP_BIT_ANY;
    vce_conf.key.tag.pcp.mask = 0;
    vce_conf.key.frame.etype.etype.value[0] = 0x89;
    vce_conf.key.frame.etype.etype.value[1] = 0x02;
    vce_conf.key.frame.etype.etype.mask[0] = 0xFF;
    vce_conf.key.frame.etype.etype.mask[1] = 0xFF;
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = vce_level_mask(0, level);
    vce_conf.action.flow_id = state.iflow_id;
    vce_conf.action.oam_detect = MESA_OAM_DETECT_SINGLE_TAGGED;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // Add the back port VCE
    vce_conf.id = state.back_vce_id;
    mesa_port_list_clear(&vce_conf.key.port_list);
    mesa_port_list_set(&vce_conf.key.port_list, state.back_port, TRUE);
    vce_conf.key.frame.etype.mel.value = 0;
    vce_conf.key.frame.etype.mel.mask = 0;
    vce_conf.action.flow_id = MESA_IFLOW_ID_NONE;
    RC(mesa_vce_add(NULL, MESA_VCE_ID_LAST, &vce_conf));

    // snippet_endbegin ex-add-tce
    RC(mesa_tce_init(NULL, &tce_conf));
    tce_conf.id = state.tce_id;
    mesa_port_list_clear(&tce_conf.key.port_list);
    mesa_port_list_set(&tce_conf.key.port_list, state.front_port, TRUE);
    tce_conf.key.vid = state.vid;
    tce_conf.action.flow_id = state.eflow_id;
    tce_conf.action.tag.tpid = MESA_TPID_SEL_PORT;
    RC(mesa_tce_add(NULL, MESA_TCE_ID_LAST, &tce_conf));

    // snippet_endbegin ex-service-voe-config
    RC(mesa_voe_conf_get(NULL, state.voe_idx, &voe_conf));
    voe_conf.enable = TRUE;
    memcpy(voe_conf.unicast_mac.addr, rx_uc_addr, sizeof(voe_conf.unicast_mac.addr));
    voe_conf.meg_level = level;
    voe_conf.dmac_check_type = MESA_VOE_DMAC_CHECK_BOTH;
    voe_conf.loop_iflow_id = MESA_IFLOW_ID_NONE;
    voe_conf.block_mel_high = FALSE;
    RC(mesa_voe_conf_set(NULL, state.voe_idx, &voe_conf));
    // snippet_end

    return 0;
}

static int vop_init(int argc, const char *argv[])
{
    mesa_port_no_t         front_port = ARGV_INT("front-port", "Is the port in front of the VOP.");
    mesa_port_no_t         back_port = ARGV_INT("back-port", "Is the port behind the VOP.");
    uint32_t               level = ARGV_OPT_INT("level", "Is the MEG level. Default is 4", 4);
    mesa_vid_t             vid = ARGV_OPT_INT("vid", "Is the VLAN VOP classified VID. Value 0 means a Port VOP is created - otherwise a VLAN VOP. Default is 0", 0);
    mesa_vlan_port_conf_t  vlan_conf;
    mesa_vop_conf_t        vop_conf;
    mesa_voe_cc_conf_t     cc_conf;
    mesa_voe_lb_conf_t     lb_conf;
    mesa_voe_lt_conf_t     lt_conf;
    mesa_voe_laps_conf_t   laps_conf;
    mesa_packet_rx_queue_t cpu_queue = 7;
    mesa_port_list_t       port_list;
    uint8_t                frame[1600];
    mesa_packet_rx_info_t  rx_info;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.v1 = mesa_capability(NULL, MESA_CAP_VOP_V1);
    state.v2 = mesa_capability(NULL, MESA_CAP_VOP_V2);
    if (!state.v1 && !state.v2) {
        cli_printf("VOP is not supported on this platform\n");
        return -1;
    }
    state.family = mesa_capability(NULL, MESA_CAP_MISC_CHIP_FAMILY);
    state.front_port = front_port - 1;
    state.back_port = back_port - 1;
    state.vid = vid;
    state.level = level;
    state.iflow_id = MESA_IFLOW_ID_NONE;
    state.eflow_id = MESA_IFLOW_ID_NONE;
    state.front_vce_id = MESA_VCE_ID_LAST;
    state.back_vce_id = MESA_VCE_ID_LAST;
    state.tce_id = MESA_TCE_ID_LAST;
    state.inj_tce_id = MESA_TCE_ID_LAST;

    // Must be called to enable rx packet polling
    (void)mesa_packet_rx_frame(NULL, frame, sizeof(frame), &rx_info);

    RC(init_port_configuration(state.front_port, prio, 0))
    RC(init_port_configuration(state.back_port, prio, 1))

    // Get the front port PVID
    RC(mesa_vlan_port_conf_get(NULL, state.front_port, &vlan_conf));
    pvid = vlan_conf.pvid;

    // snippet_begin ex-port-vop-config
    // Enable the VOP
    RC(mesa_vop_conf_get(NULL, &vop_conf));
    memcpy(vop_conf.multicast_dmac.addr, mc_addr, sizeof(vop_conf.multicast_dmac.addr));
    vop_conf.auto_copy_period[0] = 4*1000*1000;
    vop_conf.auto_copy_period[1] = 1000*1000;
    vop_conf.voe_queue_ccm = cpu_queue;
    vop_conf.voe_queue_lt = cpu_queue;
    vop_conf.voe_queue_lbm = cpu_queue;
    vop_conf.voe_queue_lbr = cpu_queue;
    vop_conf.voe_queue_aps = cpu_queue;
    vop_conf.voe_queue_err = cpu_queue;
    vop_conf.voi_queue = cpu_queue;
    RC(mesa_vop_conf_set(NULL, &vop_conf));
    // snippet_end

    // Do basic VOP configuration depending on Port or VLAN VOE
    if (state.vid == 0) {   // When vid is zero then it is the port domain
        if (state.v1 != 0) {
            v1_port_voe_configuration(level);
        } else if (state.v2 != 0) {
            v2_port_voe_configuration(level);
        }
    } else {    // This is the VLAN domain
        // Only forward on relevant ports
        mesa_port_list_clear(&port_list);
        mesa_port_list_set(&port_list, state.front_port, TRUE);
        mesa_port_list_set(&port_list, state.back_port, TRUE);
        RC(mesa_vlan_port_members_set(NULL, state.vid, &port_list));

        if (state.v1 != 0) {
            v1_service_voe_configuration(level);
        } else if (state.v2 != 0) {
            v2_service_voe_configuration(level);
        }
    }

    // snippet_begin ex-voe-cc-enable
    RC(mesa_voe_cc_conf_get(NULL, state.voe_idx, &cc_conf));
    cc_conf.enable = TRUE;
    cc_conf.cpu_copy = MESA_OAM_CPU_COPY_NONE;
    cc_conf.seq_no_update = TRUE;
    cc_conf.count_as_selected = FALSE;
    cc_conf.expected_period = period;
    cc_conf.expected_priority = prio;
    memcpy(cc_conf.expected_megid, megid, sizeof(cc_conf.expected_megid));
    cc_conf.expected_peer_mepid = peer_mepid;
    RC(mesa_voe_cc_conf_set(NULL, state.voe_idx, &cc_conf));

    // snippet_begin ex-voe-events-enable
    RC(mesa_voe_event_mask_set(NULL, state.voe_idx, MESA_VOE_EVENT_MASK_ALL, TRUE));

    // snippet_begin ex-voe-lb-enable
    RC(mesa_voe_lb_conf_get(NULL, state.voe_idx, &lb_conf));
    lb_conf.enable = TRUE;
    lb_conf.count_as_selected = FALSE;
    lb_conf.lbm_cpu_copy = FALSE;
    lb_conf.lbr_cpu_copy = MESA_OAM_CPU_COPY_NONE;
    lb_conf.trans_id = 1;
    RC(mesa_voe_lb_conf_set(NULL, state.voe_idx, &lb_conf));

    // snippet_begin ex-voe-lt-enable
    RC(mesa_voe_lt_conf_get(NULL, state.voe_idx, &lt_conf));
    lt_conf.enable = TRUE;
    lt_conf.count_as_selected = FALSE;
    lt_conf.ltm_cpu_copy = TRUE;
    lt_conf.ltr_cpu_copy = TRUE;
    RC(mesa_voe_lt_conf_set(NULL, state.voe_idx, &lt_conf));

    // snippet_begin ex-voe-laps-enable
    RC(mesa_voe_laps_conf_get(NULL, state.voe_idx, &laps_conf));
    laps_conf.enable = TRUE;
    laps_conf.cpu_copy = TRUE;
    laps_conf.count_as_selected = FALSE;
    RC(mesa_voe_laps_conf_set(NULL, state.voe_idx, &laps_conf));

    return 0;
}

static int vop_clean()
{
    mesa_port_list_t       port_list;

    RC(mesa_vlan_port_conf_set(NULL, state.front_port, &state.vlan_conf[0]));
    RC(mesa_vlan_port_conf_set(NULL, state.back_port, &state.vlan_conf[1]));
    RC(mesa_qos_port_conf_set(NULL, state.front_port, &state.qos_conf[0]));
    RC(mesa_qos_port_conf_set(NULL, state.back_port, &state.qos_conf[1]));

    if (state.iflow_id != MESA_IFLOW_ID_NONE) {
        RC(mesa_iflow_free(NULL, state.iflow_id));
    }
    if (state.eflow_id != MESA_EFLOW_ID_NONE) {
        RC(mesa_eflow_free(NULL, state.eflow_id));
    }
    if (state.front_vce_id != MESA_VCE_ID_LAST) {
        RC(mesa_vce_del(NULL, state.front_vce_id));
    }
    if (state.back_vce_id != MESA_VCE_ID_LAST) {
        RC(mesa_vce_del(NULL, state.back_vce_id));
    }
    if (state.tce_id != MESA_TCE_ID_LAST) {
        RC(mesa_tce_del(NULL, state.tce_id));
    }
    if (state.inj_tce_id != MESA_TCE_ID_LAST) {
        RC(mesa_tce_del(NULL, state.inj_tce_id));
    }
    RC(mesa_voe_free(NULL, state.voe_idx));

    if (state.vid != 0) {
        mesa_port_list_clear(&port_list);
        RC(mesa_vlan_port_members_set(NULL, state.vid, &port_list));
    }

    return 0;
}

static char ret_string[500];
static const char* vop_help()
{
    uint32_t cnt;

    cnt = sprintf(ret_string, "%s", vop_help_txt);
    cnt += sprintf(ret_string+cnt, "CC MEG-ID is %s\n", megid);
    cnt += sprintf(ret_string+cnt, "CC Peer MEP-ID is %u\n", peer_mepid);
    cnt += sprintf(ret_string+cnt, "CC MEP-ID is %u\n", mepid);
    cnt += sprintf(ret_string+cnt, "CC Priority is %u\n", prio);
    cnt += sprintf(ret_string+cnt, "CC Period is %s\n", (period == MESA_VOE_CCM_PERIOD_1_SEC) ? "1 second" : (period == MESA_VOE_CCM_PERIOD_10_SEC) ? "10 second" : (period == MESA_VOE_CCM_PERIOD_100_MS) ? "100 milisecond" : "Unknown");
    cnt += sprintf(ret_string+cnt, "Expected source Unicast MAC is %X-%X-%X-%X-%X-%X\n", rx_uc_addr[0], rx_uc_addr[1], rx_uc_addr[2], rx_uc_addr[3], rx_uc_addr[4], rx_uc_addr[5]);
    cnt += sprintf(ret_string+cnt, "Transmitted source Unicast MAC is %X-%X-%X-%X-%X-%X\n", tx_uc_addr[0], tx_uc_addr[1], tx_uc_addr[2], tx_uc_addr[3], tx_uc_addr[4], tx_uc_addr[5]);
    return ret_string;
}

#define NO_EXP 0xFFFFFFFF

static int vop_run(int argc, const char *argv[])
{
    uint32_t command = ARGV_RUN_INT("command", "The command to run.\n\
        value 0 is CC status show.\n\
        value 1 is VOE event status show.\n\
        value 2 is LT status show.\n\
        value 3 is LAPS status show.\n\
        value 4 is CPU RX frame print.\n\
        value 5 is CPU TX CCM frame.\n\
        value 6 is CPU TX LBM frame.\n");
    uint32_t exp_ccm_seen = ARGV_RUN_OPT_INT("exp-seen-ccm", "The CC status show expected CCM seen. Default is nothing expected", NO_EXP);
    uint32_t exp_ltm_seen = ARGV_RUN_OPT_INT("exp-seen-ltm", "The LT status show expected LTM seen. Default is nothing expected", NO_EXP);
    uint32_t exp_laps_seen = ARGV_RUN_OPT_INT("exp-seen-laps", "The LAPS status show expected LAPS seen. Default is nothing expected", NO_EXP);
    uint32_t exp_state_loc = ARGV_RUN_OPT_INT("exp-state-loc", "The CC status show expected LOC state. Default is nothing expected", NO_EXP);
    uint32_t exp_state_level = ARGV_RUN_OPT_INT("exp-state-level", "The CC status show expected Level state. Default is nothing expected", NO_EXP);
    uint32_t exp_event_loc = ARGV_RUN_OPT_INT("exp-event-loc", "The VOE event status show expected LOC event. Default is nothing expected", NO_EXP);
    uint32_t exp_oam_opcode = ARGV_RUN_OPT_INT("exp-oam-opcode", "The CPU frame expected opcode. Default is nothing expected", NO_EXP);
    mesa_voe_cc_status_t    cc_status;
    mesa_voe_counters_t     voe_counters;
    mesa_voe_lt_status_t    lt_status;
    mesa_voe_laps_status_t  laps_status;
    mesa_packet_tx_info_t   tx_info;
    mesa_packet_rx_info_t   rx_info;
    uint32_t                voe_event, ether_type, opcode, idx, rcode;
    char                    rx_port[20];
    uint8_t                 frame[1600], *et_ptr;

    EXAMPLE_BARRIER(argc);

    switch (command) {
    case 0:
        RC(mesa_voe_cc_status_get(NULL, state.voe_idx, &cc_status));
        sprintf(rx_port, "%u", cc_status.rx_port);
        cli_printf("CC status:\n");
        cli_printf("    zero_period:     %u\n", cc_status.zero_period);
        cli_printf("    rdi:             %u\n", cc_status.rdi);
        cli_printf("    loc:             %u\n", cc_status.loc);
        cli_printf("    period_unexp:    %u\n", cc_status.period_unexp);
        cli_printf("    priority_unexp:  %u\n", cc_status.priority_unexp);
        cli_printf("    mep_id_unexp:    %u\n", cc_status.mep_id_unexp);
        cli_printf("    meg_id_unexp:    %u\n", cc_status.meg_id_unexp);
        cli_printf("    mel_unexp:       %u\n", cc_status.mel_unexp);
        cli_printf("    rx_port:         %s\n", (cc_status.rx_port == MESA_PORT_NO_NONE) ? "None" : rx_port);
        cli_printf("    port_status_tlv: %u\n", cc_status.port_status_tlv);
        cli_printf("    if_status_tlv:   %u\n", cc_status.if_status_tlv);
        cli_printf("    seen:            %u\n", cc_status.seen);
        cli_printf("    tlv_seen:        %u\n", cc_status.tlv_seen);
        cli_printf("    seq_unexp_seen:  %u\n", cc_status.seq_unexp_seen);
        if ((exp_ccm_seen != NO_EXP) && (exp_ccm_seen != cc_status.seen)) {
            cli_printf("CCM seen %u is not as expected %u\n", cc_status.seen, exp_ccm_seen);
            return -1;
        }
        if ((exp_state_loc != NO_EXP) && (exp_state_loc != cc_status.loc)) {
            cli_printf("loc state %u is not as expected %u\n", cc_status.loc, exp_state_loc);
            return -1;
        }
        if ((exp_state_level != NO_EXP) && (exp_state_level != cc_status.mel_unexp)) {
            cli_printf("level state %u is not as expected %u\n", cc_status.mel_unexp, exp_state_level);
            return -1;
        }

        RC(mesa_voe_counters_get(NULL, state.voe_idx, &voe_counters));
        cli_printf("\nVOE counters:\n");
        cli_printf("    rx_counter:     %llu\n", voe_counters.rx_counter);
        cli_printf("    tx_counter:     %llu\n", voe_counters.tx_counter);
        break;

    case 1:
        RC(mesa_voe_event_get(NULL, state.voe_idx, &voe_event));
        cli_printf("VOE event:\n");
        cli_printf("    ccm_period:          %u\n", (MESA_VOE_EVENT_MASK_CCM_PERIOD & voe_event) ? 1 : 0);
        cli_printf("    ccm_zero_period:     %u\n", (MESA_VOE_EVENT_MASK_CCM_ZERO_PERIOD & voe_event) ? 1 : 0);
        cli_printf("    ccm_priority:        %u\n", (MESA_VOE_EVENT_MASK_CCM_PRIORITY & voe_event) ? 1 : 0);
        cli_printf("    ccm_loc:             %u\n", (MESA_VOE_EVENT_MASK_CCM_LOC & voe_event) ? 1 : 0);
        cli_printf("    ccm_mep_id:          %u\n", (MESA_VOE_EVENT_MASK_CCM_MEP_ID & voe_event) ? 1 : 0);
        cli_printf("    ccm_meg_id:          %u\n", (MESA_VOE_EVENT_MASK_CCM_MEG_ID & voe_event) ? 1 : 0);
        cli_printf("    ccm_level:           %u\n", (MESA_VOE_EVENT_MASK_CCM_MEG_LEVEL & voe_event) ? 1 : 0);
        cli_printf("    ccm_rdi:             %u\n", (MESA_VOE_EVENT_MASK_CCM_RX_RDI & voe_event) ? 1 : 0);
        cli_printf("    ccm_port_move:       %u\n", (MESA_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE & voe_event) ? 1 : 0);
        cli_printf("    ccm_tlv_port_status: %u\n", (MESA_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS & voe_event) ? 1 : 0);
        cli_printf("    ccm_tlv_if_status:   %u\n", (MESA_VOE_EVENT_MASK_CCM_TLV_IF_STATUS & voe_event) ? 1 : 0);
        if ((exp_event_loc != NO_EXP) && (exp_event_loc != ((MESA_VOE_EVENT_MASK_CCM_LOC & voe_event) ? 1 : 0))) {
            cli_printf("loc event %u is not as expected %u\n", ((MESA_VOE_EVENT_MASK_CCM_LOC & voe_event) ? 1 : 0), exp_event_loc);
            return -1;
        }
        break;

    case 2:
        RC(mesa_voe_lt_status_get(NULL, state.voe_idx, &lt_status));
        cli_printf("LT status:\n");
        cli_printf("    ltm_seen:     %u\n", lt_status.ltm_seen);
        cli_printf("    ltr_seen:     %u\n", lt_status.ltr_seen);
        if ((exp_ltm_seen != NO_EXP) && (exp_ltm_seen != lt_status.ltm_seen)) {
            cli_printf("LTM seen %u is not as expected %u\n", lt_status.ltm_seen, exp_ltm_seen);
            return -1;
        }
        break;

    case 3:
        RC(mesa_voe_laps_status_get(NULL, state.voe_idx, &laps_status));
        cli_printf("LAPS status:\n");
        cli_printf("    seen:     %u\n", laps_status.seen);
        if ((exp_laps_seen != NO_EXP) && (exp_laps_seen != laps_status.seen)) {
            cli_printf("LAPS seen %u is not as expected %u\n", laps_status.seen, exp_laps_seen);
            return -1;
        }
        break;

    case 4:
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
        opcode = et_ptr[3];

        cli_printf("Frame received:\n");
        cli_printf("    Port:   %u:\n", rx_info.port_no);
        cli_printf("    Length: %u:\n", rx_info.length);
        cli_printf("    Tag type: %s:\n", (rx_info.tag_type == MESA_TAG_TYPE_UNTAGGED) ? "Un-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_C_TAGGED) ? "C-tagged" : (rx_info.tag_type == MESA_TAG_TYPE_S_TAGGED) ? "S-tagged" : "Unknown");
        cli_printf("    Ether type: %X:\n", ether_type);
        cli_printf("    OAM Opcode: %u:\n", opcode);
        if (exp_oam_opcode != NO_EXP) {
            if (exp_oam_opcode != opcode) {
                cli_printf("Opcode %u is not as expected %u\n", opcode, exp_oam_opcode);
                return -1;
            }
        }
        break;

    case 5:
        // Initialize the TX info
        RC(mesa_packet_tx_info_init(NULL, &tx_info));
        if (state.family == MESA_CHIP_FAMILY_SPARX5) {
            tx_info.dst_port = state.front_port;
        } else {
            tx_info.dst_port_mask = 0x01 << state.front_port;
        }
        tx_info.switch_frm = FALSE;
        tx_info.masquerade_port = MESA_PORT_NO_NONE;
        tx_info.pdu_offset = 14;
        tx_info.oam_type = MESA_PACKET_OAM_TYPE_CCM;
        tx_info.pipeline_pt = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
        tx_info.tag.vid = (state.vid == 0) ? pvid : state.vid;
        tx_info.iflow_id = state.v2 ? ((state.vid == 0) ? state.iflow_id : 0) : ((state.vid == 0) ? 0 : state.iflow_id);

        // Initialize the TX frame
        memset(frame, 0, sizeof(frame));
        idx = 0;
        memcpy(frame+idx, mc_addr, sizeof(mc_addr));
        idx += 6;
        memcpy(frame+idx, tx_uc_addr, sizeof(tx_uc_addr));
        idx += 6;
        *(frame+idx+0) = 0x89;
        *(frame+idx+1) = 0x02;
        idx += 2;
        *(frame+idx+0) = (state.level & 0x07) << 5;    // Level
        *(frame+idx+1) = 1;                            // Opcode CCM
        *(frame+idx+2) = 4;                            // Flags period 1 f/s
        *(frame+idx+3) = 70;                           // TLV offset
        *(frame+idx+4) = 0;                            // Sequence number
        *(frame+idx+5) = 0;                            // Sequence number
        *(frame+idx+6) = 0;                            // Sequence number
        *(frame+idx+7) = 0;                            // Sequence number
        *(frame+idx+8) = (mepid & 0x1F00) >> 8;        // MEP ID
        *(frame+idx+9) = (mepid & 0xFF);               // MEP ID
        idx += 10;
        memcpy(frame+idx, megid, sizeof(megid));
        idx += sizeof(megid);
        idx += 12;  // This is LM counters
        idx += 4;  // This is Reserved bytes
        idx += 1;  // This is end TLV
        idx += 2;  // This is end TLV length
        idx += 1;  // This is end TLV value

        // Transmit the frame
        RC(mesa_packet_tx_frame(NULL, &tx_info, frame, idx));
        break;

    case 6:
        // Initialize the TX info
        RC(mesa_packet_tx_info_init(NULL, &tx_info));
        if (state.family == MESA_CHIP_FAMILY_SPARX5) {
            tx_info.dst_port = state.front_port;
        } else {
            tx_info.dst_port_mask = 0x01 << state.front_port;
        }
        tx_info.switch_frm = FALSE;
        tx_info.masquerade_port = MESA_PORT_NO_NONE;
        tx_info.pdu_offset = 14;
        tx_info.oam_type = MESA_PACKET_OAM_TYPE_LBM;
        tx_info.pipeline_pt = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
        tx_info.tag.vid = (state.vid == 0) ? pvid : state.vid;
        tx_info.iflow_id = state.v2 ? ((state.vid == 0) ? state.iflow_id : 0) : ((state.vid == 0) ? 0 : state.iflow_id);

        // Initialize the TX frame
        memset(frame, 0, sizeof(frame));
        idx = 0;
        memcpy(frame+idx, mc_addr, sizeof(mc_addr));
        idx += 6;
        memcpy(frame+idx, tx_uc_addr, sizeof(tx_uc_addr));
        idx += 6;
        *(frame+idx+0) = 0x89;
        *(frame+idx+1) = 0x02;
        idx += 2;
        *(frame+idx+0) = (state.level & 0x07) << 5;    // Level
        *(frame+idx+1) = 3;                            // Opcode LBM
        *(frame+idx+2) = 0;                            // Flags period 1 f/s
        *(frame+idx+3) = 4;                            // TLV offset
        idx += 4;  // This is Sequence number
        idx += 1;  // This is end TLV
        idx += 2;  // This is end TLV length
        idx += 1;  // This is end TLV value
        idx += (87 - idx); // This is fill

        // Transmit the frame
        RC(mesa_packet_tx_frame(NULL, &tx_info, frame, idx));
        break;

    default:
        cli_printf("Unknown command\n");
        break;
    }

    return 0;
}

EXAMPLE(vop, vop_init, vop_run, vop_clean, vop_help);
