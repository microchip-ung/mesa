// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_L2
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X)

static vtss_rc lan966x_pgid_table_write(vtss_state_t *vtss_state,
                                        u32 pgid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_aggr_table_write(vtss_state_t *vtss_state,
                                        u32 ac, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_src_table_write(vtss_state_t *vtss_state,
                                       vtss_port_no_t port_no, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_aggr_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_pmap_table_write(vtss_state_t *vtss_state,
                                        vtss_port_no_t port_no, vtss_port_no_t l_port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_learn_state_set(vtss_state_t *vtss_state,
                                       const BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_idle(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_add(vtss_state_t *vtss_state,
                                     const vtss_mac_table_entry_t *const entry, u32 pgid)
{
    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_del(vtss_state_t *vtss_state, const vtss_vid_mac_t *const vid_mac)
{
    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_get(vtss_state_t *vtss_state,
                                     vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_get_next(vtss_state_t *vtss_state,
                                          vtss_mac_table_entry_t *const entry, u32 *pgid)
{
    /* Wait until MAC operation is finished */
    return lan966x_mac_table_idle(vtss_state);
}

static vtss_rc lan966x_mac_table_age_time_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_age(vtss_state_t *vtss_state,
                                     BOOL             pgid_age,
                                     u32              pgid,
                                     BOOL             vid_age,
                                     const vtss_vid_t vid)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mac_table_status_get(vtss_state_t *vtss_state,
                                            vtss_mac_table_status_t *status)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_learn_port_mode_set(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - VLAN
 * ================================================================= */

static vtss_rc lan966x_vlan_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_port_conf_update(vtss_state_t *vtss_state,
                                             vtss_port_no_t port_no, vtss_vlan_port_conf_t *conf)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_table_idle(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_vlan_mask_update(vtss_state_t *vtss_state,
                                        vtss_vid_t vid, BOOL member[VTSS_PORT_ARRAY_SIZE])
{
    return lan966x_vlan_table_idle(vtss_state);
}

/* ================================================================= *
 *  Layer 2 - PVLAN / Isolated ports
 * ================================================================= */

static vtss_rc lan966x_isolated_port_members_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - IP Multicast
 * ================================================================= */

static vtss_rc lan966x_flood_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ip_mc_update(vtss_state_t *vtss_state,
                                    vtss_ipmc_data_t *ipmc, vtss_ipmc_cmd_t cmd)
{
    return VTSS_RC_OK;
}

/* ================================================================= *
 *  Layer 2 - Mirror
 * ================================================================= */

static vtss_rc lan966x_mirror_cpu_ingress_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_cpu_egress_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_port_set(vtss_state_t *vtss_state)
{
    return vtss_cmn_vlan_update_all(vtss_state);
}

static vtss_rc lan966x_mirror_ingress_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_mirror_egress_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

#if 0
static vtss_rc lan966x_vcap_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_iflow_conf_set(vtss_state_t *vtss_state, const vtss_iflow_id_t id)
{
    return VTSS_RC_OK;
}
#endif

/* ================================================================= *
 *  SFLOW
 * ================================================================= */

static vtss_rc lan966x_sflow_sampling_rate_convert(struct vtss_state_s *const state,
                                                   const BOOL power2, const u32 rate_in, u32 *const rate_out)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_sflow_port_conf_set(vtss_state_t *vtss_state,
                                           const vtss_port_no_t port_no,
                                           const vtss_sflow_port_conf_t *const new_conf)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_l2_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_l2_port_map_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_l2_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_l2_state_t *state = &vtss_state->l2;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->mac_table_add = lan966x_mac_table_add;
        state->mac_table_del = lan966x_mac_table_del;
        state->mac_table_get = lan966x_mac_table_get;
        state->mac_table_get_next = lan966x_mac_table_get_next;
        state->mac_table_age_time_set = lan966x_mac_table_age_time_set;
        state->mac_table_age = lan966x_mac_table_age;
        state->mac_table_status_get = lan966x_mac_table_status_get;
        state->learn_port_mode_set = lan966x_learn_port_mode_set;
        state->learn_state_set = lan966x_learn_state_set;
        state->mstp_state_set = vtss_cmn_mstp_state_set;
        state->mstp_vlan_msti_set = vtss_cmn_vlan_members_set;
        state->erps_vlan_member_set = vtss_cmn_erps_vlan_member_set;
        state->erps_port_state_set = vtss_cmn_erps_port_state_set;
        state->pgid_table_write = lan966x_pgid_table_write;
        state->src_table_write = lan966x_src_table_write;
        state->aggr_table_write = lan966x_aggr_table_write;
        state->aggr_mode_set = lan966x_aggr_mode_set;
        state->pmap_table_write = lan966x_pmap_table_write;
        state->vlan_conf_set = lan966x_vlan_conf_set;
        state->vlan_port_conf_set = vtss_cmn_vlan_port_conf_set;
        state->vlan_port_conf_update = lan966x_vlan_port_conf_update;
        state->vlan_port_members_set = vtss_cmn_vlan_members_set;
        state->vlan_mask_update = lan966x_vlan_mask_update;
        state->vlan_tx_tag_set = vtss_cmn_vlan_tx_tag_set;
        state->isolated_vlan_set = vtss_cmn_vlan_members_set;
        state->isolated_port_members_set = lan966x_isolated_port_members_set;
        state->flood_conf_set = lan966x_flood_conf_set;
        state->ipv4_mc_add = vtss_cmn_ipv4_mc_add;
        state->ipv4_mc_del = vtss_cmn_ipv4_mc_del;
        state->ipv6_mc_add = vtss_cmn_ipv6_mc_add;
        state->ipv6_mc_del = vtss_cmn_ipv6_mc_del;
        state->ip_mc_update = lan966x_ip_mc_update;
        state->mirror_port_set = lan966x_mirror_port_set;
        state->mirror_ingress_set = lan966x_mirror_ingress_set;
        state->mirror_egress_set = lan966x_mirror_egress_set;
        state->mirror_cpu_ingress_set = lan966x_mirror_cpu_ingress_set;
        state->mirror_cpu_egress_set = lan966x_mirror_cpu_egress_set;
        state->eps_port_set = vtss_cmn_eps_port_set;
        state->sflow_port_conf_set         = lan966x_sflow_port_conf_set;
        state->sflow_sampling_rate_convert = lan966x_sflow_sampling_rate_convert;
        // TBD: state->vcl_port_conf_set = vtss_lan966x_vcap_port_conf_set;
        state->vce_add = vtss_cmn_vce_add;
        state->vce_del = vtss_cmn_vce_del;
        state->vlan_trans_group_add = vtss_cmn_vlan_trans_group_add;
        state->vlan_trans_group_del = vtss_cmn_vlan_trans_group_del;
        state->vlan_trans_group_get = vtss_cmn_vlan_trans_group_get;
        state->vlan_trans_port_conf_set  = vtss_cmn_vlan_trans_port_conf_set;
        state->vlan_trans_port_conf_get  = vtss_cmn_vlan_trans_port_conf_get;
        // TBD: state->vcap_port_conf_set = lan966x_vcap_port_conf_set;
        // TBD: state->iflow_conf_set = lan966x_iflow_conf_set;
        // TBD: state->ac_count = LAN966X_ACS;
        // TBD: state->sdx_info.max_count = LAN966X_EVC_CNT;
        // TBD: if (state->sdx_info.max_count > VTSS_LAN966X_SDX_CNT)
        // TBD      state->sdx_info.max_count = VTSS_LAN966X_SDX_CNT;
        break;

    case VTSS_INIT_CMD_INIT:
        if (!vtss_state->warm_start_cur) {
            VTSS_RC(lan966x_l2_init(vtss_state));
        }
        break;

    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(lan966x_l2_port_map_set(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
