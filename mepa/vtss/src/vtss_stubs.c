// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <vtss_phy_api.h>

#if !defined(VTSS_FEATURE_MACSEC)
vtss_rc vtss_macsec_init_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_init_t *const init)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_init_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_init_t *const init)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_conf_add(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_secy_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_conf_update(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_secy_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_conf_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_secy_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_conf_del(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_controlled_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_controlled_get(const vtss_inst_t inst, const vtss_macsec_port_t port, BOOL *const enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_port_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_secy_port_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_port_get_next(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_port_t *const search_macsec_port, vtss_macsec_port_t *const found_macsec_port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_add(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_update(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const vtss_macsec_rx_sc_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_get_conf(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, vtss_macsec_rx_sc_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_get_next(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const search_sci, vtss_macsec_sci_t *const found_sci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_del(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, vtss_macsec_rx_sc_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_set(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_update(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_tx_sc_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_get_conf(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_tx_sc_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_del(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_tx_sc_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, const u32 lowest_pn, const vtss_macsec_sak_t *const sak)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, u32 *const lowest_pn, vtss_macsec_sak_t *const sak, BOOL *const active)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_activate(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_disable(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_del(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_lowest_pn_update(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, const u32 lowest_pn)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, vtss_macsec_rx_sa_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_seca_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, const vtss_macsec_pkt_num_t lowest_pn, const vtss_macsec_sak_t *const sak, const vtss_macsec_ssci_t *const ssci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_seca_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, vtss_macsec_pkt_num_t *const lowest_pn, vtss_macsec_sak_t *const sak, BOOL *const active, vtss_macsec_ssci_t *const ssci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_seca_lowest_pn_update(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, const vtss_macsec_pkt_num_t lowest_pn)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, const u32 next_pn, const BOOL confidentiality, const vtss_macsec_sak_t *const sak)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, u32 *const next_pn, BOOL *const confidentiality, vtss_macsec_sak_t *const sak, BOOL *const active)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_activate(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_disable(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_del(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, vtss_macsec_tx_sa_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_seca_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, const vtss_macsec_pkt_num_t next_pn, const BOOL confidentiality, const vtss_macsec_sak_t *const sak, const vtss_macsec_ssci_t *const ssci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_seca_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, vtss_macsec_pkt_num_t *const next_pn, BOOL *const confidentiality, vtss_macsec_sak_t *const sak, BOOL *const active, vtss_macsec_ssci_t *const ssci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_controlled_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_secy_port_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_uncontrolled_counters_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_uncontrolled_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_common_counters_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_common_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_cap_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_secy_cap_t *const cap)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_secy_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_counters_update(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sc_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, vtss_macsec_rx_sc_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sc_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_tx_sc_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_tx_sa_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an, vtss_macsec_tx_sa_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rx_sa_counters_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, vtss_macsec_rx_sa_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_control_frame_match_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_control_frame_match_conf_t *const conf, u32 *const rule_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_control_frame_match_conf_del(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 rule_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_control_frame_match_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_control_frame_match_conf_t *const conf, u32 rule_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_pattern_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_direction_t direction, const vtss_macsec_match_action_t action, const vtss_macsec_match_pattern_t *const pattern)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_pattern_del(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_direction_t direction, const vtss_macsec_match_action_t action)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_pattern_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_direction_t direction, const vtss_macsec_match_action_t action, vtss_macsec_match_pattern_t *const pattern)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_default_action_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_default_action_policy_t *const policy)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_default_action_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_default_action_policy_t *const policy)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_bypass_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_bypass_mode_t *const bypass)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_bypass_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_bypass_mode_t *const bypass)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_bypass_tag_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_tag_bypass_t tag)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_bypass_tag_get(const vtss_inst_t inst, const vtss_macsec_port_t port, vtss_macsec_tag_bypass_t *const tag)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_mtu_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_mtu_t *const mtu_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_mtu_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_mtu_t *mtu_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_frame_capture_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_frame_capture_t capture)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_frame_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 buf_length, u32 *const return_length, u8 *const frame)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_event_enable_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_macsec_event_t ev_mask, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_event_enable_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_event_seq_threshold_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 threshold)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_event_seq_threshold_get(const vtss_inst_t inst, const vtss_port_no_t port_no, u32 *const threshold)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_csr_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 mmd, const u32 addr, u32 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_csr_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 mmd, const u32 addr, const u32 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_dbg_counter_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_rc_dbg_counters_t *const counters)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_hmac_counters_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_mac_counters_t *const counters, const BOOL clear)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_lmac_counters_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_mac_counters_t *const counters, const BOOL clear)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_is_capable(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *capable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_dbg_reg_dump(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_debug_printf_t pr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_lmac_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_hmac_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_debug_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_common_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_uncontrolled_counters_clear(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_controlled_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rxsa_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rxsc_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_txsa_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port, const u16 an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_txsc_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_secy_counters_clear(const vtss_inst_t inst, const vtss_macsec_port_t port)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_port_enable_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_rxsa_an_status_get(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, const u16 an, BOOL *status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_mac_block_mtu_get(const vtss_inst_t inst, const vtss_port_no_t port_no, u16 *const mtu_value, BOOL *const mtu_tag_check)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_mac_block_mtu_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 mtu_value, const BOOL mtu_tag_check)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_fcbuf_frame_gap_comp_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 frm_gap)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_dbg_fcb_block_reg_dump(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_debug_printf_t pr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_debug_printf_t pr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_dbg_update_seq_set(const vtss_inst_t inst, const vtss_macsec_port_t port, const vtss_macsec_sci_t *const sci, u16 an, BOOL egr, const BOOL disable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_egr_intr_sa_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_port_t *const port, u16 *const an)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_macsec_inst_count_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_macsec_inst_count_t *count)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#endif // !defined(VTSS_FEATURE_MACSEC)

#if !defined(VTSS_CHIP_10G_PHY)
vtss_rc vtss_phy_10g_init(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_init_parm_t *const init_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_ib_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_ib_conf_t *const ib_conf, BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_ib_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL is_host, vtss_phy_10g_ib_conf_t *const ib_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_ib_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_ib_status_t *const ib_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_apc_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_apc_conf_t *const apc_conf, const BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_apc_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL is_host, vtss_phy_10g_apc_conf_t *const apc_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_apc_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL is_host, vtss_phy_10g_apc_status_t *const apc_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_apc_restart(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_jitter_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_jitter_conf_t *const jitter_conf, BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_jitter_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_jitter_conf_t *jitter_conf, BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_jitter_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_jitter_conf_t *const jitter_conf, BOOL is_host)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_fc_buffer_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#if !defined(VTSS_FEATURE_SYNCE_10G)
vtss_rc vtss_phy_10g_synce_clkout_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *const synce_clkout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_synce_clkout_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL synce_clkout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_xfp_clkout_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *const xfp_clkout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_xfp_clkout_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL xfp_clkout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_rxckout_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_rxckout_conf_t *const rxckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_rxckout_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_rxckout_conf_t *const rxckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_txckout_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_txckout_conf_t *const txckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_txckout_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_txckout_conf_t *const txckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_srefclk_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_srefclk_mode_t *const srefclk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_srefclk_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_srefclk_mode_t *const srefclk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_sckout_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_sckout_conf_t *const sckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_ckout_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_ckout_conf_t *const ckout)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_line_clk_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_line_clk_conf_t *const line_clk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_host_clk_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_host_clk_conf_t *const host_clk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_line_recvrd_clk_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_line_clk_conf_t *const line_clk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_host_recvrd_clk_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_host_clk_conf_t *const host_clk)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_FEATURE_SYNCE_10G)

vtss_rc vtss_phy_10g_lane_sync_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_lane_sync_conf_t *const lane_sync)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_debug_register_dump(const vtss_inst_t inst, const vtss_debug_printf_t pr, BOOL clear, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#if !defined(VTSS_FEATURE_10GBASE_KR)
vtss_rc vtss_phy_10g_base_kr_train_aneg_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_base_kr_train_aneg_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_base_host_kr_train_aneg_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
vtss_rc vtss_phy_10g_kr_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL direction, vtss_phy_10g_base_kr_status_t *const kr_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_FEATURE_10GBASE_KR)

vtss_rc vtss_phy_10g_base_kr_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_base_kr_conf_t *const kr_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_base_kr_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_base_kr_conf_t *const kr_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_base_kr_host_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_base_kr_conf_t *const kr_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_base_kr_host_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_base_kr_conf_t *const kr_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_ob_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_ob_status_t *const ob_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_serdes_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_serdes_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_clause_37_status_get(const vtss_inst_t inst, vtss_port_no_t port_no, vtss_phy_10g_clause_37_cmn_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_clause_37_control_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_clause_37_control_t *const control)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
vtss_rc vtss_phy_10g_clause_37_control_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_clause_37_control_t *const control)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_loopback_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_loopback_t *const loopback)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_loopback_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_loopback_t *const loopback)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_cnt_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_cnt_t *const cnt)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_power_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_power_t *const power)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
vtss_rc vtss_phy_10g_power_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_power_t *const power)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

BOOL vtss_phy_10G_is_valid(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_failover_set(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_failover_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_failover_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_failover_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_auto_failover_set(const vtss_inst_t inst, vtss_phy_10g_auto_failover_conf_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_auto_failover_get(const vtss_inst_t inst, vtss_phy_10g_auto_failover_conf_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_vscope_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_vscope_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_vscope_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_vscope_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_vscope_scan_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_vscope_scan_status_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_generator_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_prbs_type_t type, const vtss_phy_10g_direction_t direction, vtss_phy_10g_prbs_generator_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_generator_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_prbs_type_t type, const vtss_phy_10g_direction_t direction, const vtss_phy_10g_prbs_generator_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
vtss_rc vtss_phy_10g_prbs_monitor_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_prbs_type_t type, const vtss_phy_10g_direction_t direction, vtss_phy_10g_prbs_monitor_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_monitor_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_prbs_type_t type, const vtss_phy_10g_direction_t direction, const vtss_phy_10g_prbs_monitor_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_monitor_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_prbs_type_t type, const vtss_phy_10g_direction_t direction, const BOOL reset, vtss_phy_10g_prbs_monitor_status_t *const mon_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_gen_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_prbs_gen_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_gen_conf(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_prbs_gen_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_mon_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_prbs_mon_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_prbs_mon_conf(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_prbs_mon_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_pkt_gen_conf(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_pkt_gen_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_pkt_mon_conf(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL ts_rd, vtss_phy_10g_pkt_mon_conf_t *const conf, vtss_phy_10g_timestamp_val_t *const conf_ts)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_pkt_mon_counters_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_pkt_mon_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_id_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_id_t *const phy_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_gpio_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_gpio_10g_no_t gpio_no, const vtss_gpio_10g_gpio_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_gpio_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_gpio_10g_no_t gpio_no, vtss_gpio_10g_gpio_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_gpio_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_gpio_10g_no_t gpio_no, BOOL *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_gpio_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_gpio_10g_no_t gpio_no, const BOOL value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_event_enable_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_event_t ev_mask, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_event_enable_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_extended_event_enable_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_extnd_event_t *const ex_ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_pcs_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_extnd_event_t *const ex_events)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_extended_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_extnd_event_t *const ex_events)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_extended_event_enable_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_10g_extnd_event_t ex_ev_mask, const BOOL extnd_enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_poll_1sec(const vtss_inst_t inst)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_edc_fw_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_fw_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_csr_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 dev, const u32 addr, u32 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_csr_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 dev, const u32 addr, const u32 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_warm_start_10g_failed_get(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_sgmii_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_i2c_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 addr, u16 *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_i2c_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 addr, const u16 *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_i2c_slave_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_i2c_slave_conf_t *const i2c_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_i2c_slave_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_10g_i2c_slave_conf_t *i2c_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_10g_get_user_data(const vtss_inst_t inst, const vtss_port_no_t port_no, void **user_data)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_CHIP_10G_PHY)

#if !defined(VTSS_CHIP_CU_PHY)
vtss_rc vtss_phy_pre_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_post_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_pre_system_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_reset(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_reset_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_reset_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_reset_conf_t *conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_chip_temp_get(const vtss_inst_t inst, const vtss_port_no_t port_no, i16 *const temp)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_chip_temp_init(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_port_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_cl37_lp_abil_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_port_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_id_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_type_t *phy_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ring_resiliency_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ring_resiliency_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_conf_1g_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_conf_1g_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_conf_1g_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_conf_1g_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_status_1g_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_status_1g_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_power_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_power_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_power_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_power_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_power_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_power_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_clock_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_recov_clk_t clock_port, const vtss_phy_clock_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_clock_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_recov_clk_t clock_port, vtss_phy_clock_conf_t *const conf, vtss_port_no_t *const clock_source)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_i2c_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 i2c_mux, const u8 i2c_reg_addr, const u8 i2c_device_addr, BOOL word_access, u8 cnt, u8 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_i2c_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 i2c_mux, const u8 i2c_reg_addr, const u8 i2c_device_addr, BOOL word_access, u8 cnt, const u8 *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 addr, u16 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_read_page(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 page, const u32 addr, u16 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_mmd_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 devad, const u32 addr, u16 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_mmd_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 devad, const u32 addr, u16 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 addr, const u16 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_write_masked(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 addr, const u16 value, const u16 mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_write_masked_page(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 page, const u16 addr, const u16 value, const u16 mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_gpio_mode(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 gpio_no, const vtss_phy_gpio_mode_t mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_gpio_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 gpio_no, BOOL *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_gpio_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 gpio_no, BOOL value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#if !VTSS_PHY_OPT_VERIPHY
vtss_rc vtss_phy_veriphy_start(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_veriphy_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_veriphy_result_t *const result)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif  // !VTSS_PHY_OPT_VERIPHY

vtss_rc vtss_phy_led_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_led_mode_select_t led_mode_select)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#if !defined(VTSS_FEATURE_LED_POW_REDUC)
vtss_rc vtss_phy_led_intensity_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_led_intensity intensity)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_led_intensity_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_led_intensity *intensity)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_enhanced_led_control_init(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_enhanced_led_control_t conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_enhanced_led_control_init_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_enhanced_led_control_t *conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_FEATURE_LED_POW_REDUC)

vtss_rc vtss_phy_coma_mode_disable(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_coma_mode_enable(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_port_eee_capable(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *eee_capable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_eee_ena(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_eee_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_eee_conf_t *conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_eee_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_eee_conf_t conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_eee_power_save_state_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *rx_in_power_save_state, BOOL *tx_in_power_save_state)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_eee_link_partner_advertisements_get(const vtss_inst_t inst, const vtss_port_no_t port_no, u8 *advertisement)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_event_enable_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_event_t ev_mask, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_event_enable_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_event_t *ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_squelch_workaround(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_csr_wr(const vtss_inst_t inst, const u16 page, const vtss_port_no_t port_no, const u16 target, const u32 csr_reg_addr, const u32 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_csr_rd(const vtss_inst_t inst, const u16 page, const vtss_port_no_t port_no, const u16 target, const u32 csr_reg_addr, u32 *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_statistic_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_statistic_t *statistics)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_do_page_chk_set(const vtss_inst_t inst, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_do_page_chk_get(const vtss_inst_t inst, BOOL *enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_loopback_set(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_loopback_t loopback)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_loopback_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_loopback_t *loopback)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_is_8051_crc_ok(const vtss_inst_t inst, const vtss_port_no_t port_no, u16 code_length, u16 expected_crc)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_cfg_ob_post0(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_cfg_ib_cterm(const vtss_inst_t inst, const vtss_port_no_t port_no, const u8 ib_cterm_ena, const u8 ib_eq_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_serdes6g_rcpll_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_rcpll_status_t *rcpll_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_serdes1g_rcpll_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_rcpll_status_t *rcpll_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_lcpll_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_lcpll_status_t *lcpll_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

void vtss_phy_reg_decode_status(vtss_port_no_t port_no, u16 lp_auto_neg_advertisment_reg, u16 lp_1000base_t_status_reg, u16 mii_status_reg, const vtss_phy_conf_t phy_setup, vtss_port_status_t *const status)
{
}

vtss_rc vtss_phy_flowcontrol_decode_status(const vtss_inst_t inst, const vtss_port_no_t port_no, u16 lp_auto_neg_advertisment_reg, const vtss_phy_conf_t phy_setup, vtss_port_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_debug_stat_print(const vtss_inst_t inst, const vtss_debug_printf_t pr, const vtss_port_no_t port_no, const BOOL print_hdr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_warm_start_failed_get(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_debug_phyinfo_print(const vtss_inst_t inst, const vtss_debug_printf_t pr, const vtss_port_no_t port_no, const BOOL print_hdr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_debug_register_dump(const vtss_inst_t inst, const vtss_debug_printf_t pr, BOOL clear, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_detect_base_ports(const vtss_inst_t inst)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ext_connector_loopback(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL lpback)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_serdes_sgmii_loopback(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_serdes_fmedia_loopback(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_debug_regdump_print(const vtss_inst_t inst, const vtss_debug_printf_t pr, const vtss_port_no_t port_no, const vtss_port_no_t page_no, const BOOL print_hdr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_wol_enable(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_wol_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_wol_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_wol_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_wol_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_reset_lcpll(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_sd6g_ob_post_rd(vtss_inst_t inst, const vtss_port_no_t port_no, u8 *ob_post0, u8 *ob_post1)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_sd6g_ob_post_wr(vtss_inst_t inst, const vtss_port_no_t port_no, const u8 ob_post0, const u8 ob_post1)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_sd6g_ob_lev_rd(vtss_inst_t inst, const vtss_port_no_t port_no, u8 *ob_level)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_sd6g_ob_lev_wr(vtss_inst_t inst, const vtss_port_no_t port_no, const u8 ob_level)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_mac_media_inhibit_odd_start(vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL mac_inhibit, const BOOL media_inhibit)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_fefi_get(vtss_inst_t inst, const vtss_port_no_t port_no, vtss_fefi_mode_t *fefi)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_fefi_set(vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_fefi_mode_t fefi)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_fefi_detect(vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *fefi_detect)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_mse_100m_get(vtss_inst_t inst, const vtss_port_no_t port_no, u32 *mse)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_mse_1000m_get(vtss_inst_t inst, const vtss_port_no_t port_no, u32 *mseA, u32 *mseB, u32 *mseC, u32 *mseD)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_read_tr_addr(vtss_inst_t inst, const vtss_port_no_t port_no, u16 tr_addr, u16 *tr_lower, u16 *tr_upper)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_is_viper_revB(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *is_viper_revB)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ext_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_firmware_update(const vtss_inst_t inst, const vtss_port_no_t port_no, u8 *const fw, u32 *const len)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_macsec_csr_sd6g_rd(vtss_inst_t inst, const vtss_port_no_t port_no, const u16 target, const u32 csr_reg_addr, u32 *value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_macsec_csr_sd6g_wr(vtss_inst_t inst, const vtss_port_no_t port_no, const u16 target, const u32 csr_reg_addr, u32 value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // defined(VTSS_CHIP_CU_PHY)

#if !defined(VTSS_OPT_PHY_TIMESTAMP)
vtss_rc vtss_phy_ts_alt_clock_saved_get(const vtss_inst_t inst, const vtss_port_no_t port_no, u32 *const saved)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_alt_clock_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_alt_clock_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_pps_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_pps_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_latency_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_timeinterval_t *const latency)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_latency_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_timeinterval_t *const latency)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_latency_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_timeinterval_t *const latency)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_latency_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_timeinterval_t *const latency)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_path_delay_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_timeinterval_t *const path_delay)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_path_delay_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_timeinterval_t *const path_delay)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_delay_asymmetry_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_timeinterval_t *const delay_asym)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_delay_asymmetry_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_timeinterval_t *const delay_asym)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ptptime_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_timestamp_t *const ts)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ptptime_set_done(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ptptime_arm(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ptptime_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_timestamp_t *const ts)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_load_ptptime_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_timestamp_t *const ts)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_sertod_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_sertod_conf_t *const sertod_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_sertod_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_sertod_conf_t *const sertod_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_loadpulse_delay_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const u16 *const delay)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_loadpulse_delay_get(const vtss_inst_t inst, const vtss_port_no_t port_no, u16 *const delay)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_clock_rateadj_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_scaled_ppb_t *const adj)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_clock_rateadj_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_scaled_ppb_t *const adj)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ptptime_adj1ns(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL incr)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_timeofday_offset_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const i32 offset)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ongoing_adjustment(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_todadj_status_t *const ongoing_adjustment)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ltc_freq_synth_pulse_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ltc_freq_synth_pulse_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

#if !defined(VTSS_CHIP_CU_PHY)
vtss_rc vtss_phy_daisy_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_daisy_chain_conf_t *const daisy_chain)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_daisy_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_daisy_chain_conf_t *const daisy_chain)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // defined(VTSS_CHIP_CU_PHY

vtss_rc vtss_phy_ts_fifo_sig_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_fifo_sig_mask_t sig_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_fifo_sig_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_fifo_sig_mask_t *const sig_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_fifo_empty(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_fifo_read_install(const vtss_inst_t inst, vtss_phy_ts_fifo_read rd_cb, void *cntxt)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_fifo_read_cb_get(const vtss_inst_t inst, vtss_phy_ts_fifo_read *rd_cb, void **cntxt)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_fifo_get(const vtss_inst_t inst,  const vtss_port_no_t port_no, vtss_phy_ts_fifo_entry_t ts_list[], const size_t size, uint32_t *const num)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_init(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_encap_t encap_type, const u8 flow_st_index, const u8 flow_end_index, const vtss_phy_ts_engine_flow_match_t flow_match_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_init_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_eng_init_conf_t *const init_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_clear(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_init(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_encap_t encap_type, const u8 flow_st_index, const u8 flow_end_index, const vtss_phy_ts_engine_flow_match_t flow_match_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_init_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_eng_init_conf_t *const init_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_clear(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_action_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_engine_action_t *const action_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_ingress_engine_action_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_engine_action_t *const action_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_action_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, const vtss_phy_ts_engine_action_t *const action_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_egress_engine_action_get(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_engine_t eng_id, vtss_phy_ts_engine_action_t *const action_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_event_enable_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable, const vtss_phy_ts_event_t ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_event_enable_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_event_t *const ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_event_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_stats_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_stats_t *const statistics)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_correction_overflow_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *const ingr_overflow, BOOL *const egr_overflow)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *const enable)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_init(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_init_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_init_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL *const init_done, vtss_phy_ts_init_conf_t *const conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_nphase_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_phy_ts_nphase_sampler_t sampler, vtss_phy_ts_nphase_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_1588_csr_reg_write(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 blk_id, const u16 csr_address, const u32 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_1588_csr_reg_read(const vtss_inst_t inst, const vtss_port_no_t port_no, const u32 blk_id, const u16 csr_address, u32 *const value)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_viper_fifo_reset(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_phy_ts_fifo_conf_t *fifo_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_phy_ts_flow_clear_cf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, BOOL ingress, const vtss_phy_ts_engine_t eng_id, u8 act_id, const vtss_phy_ts_ptp_message_type_t msgtype)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_OPT_PHY_TIMESTAMP)

#if !defined(VTSS_OPT_PHY_TIMESTAMP) || !defined(VTSS_CHIP_10G_PHY)
vtss_rc vtss_phy_ts_phy_oper_mode_change(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_OPT_PHY_TIMESTAMP) || !defined(VTSS_CHIP_10G_PHY)

#if !defined(VTSS_FEATURE_WIS)
vtss_rc vtss_ewis_event_enable(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable, const vtss_ewis_event_t ev_mask)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_event_poll(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_event_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_event_force(const vtss_inst_t inst, const vtss_port_no_t port_no, const BOOL enable, const vtss_ewis_event_t ev_force)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_static_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_static_conf_t *const stat_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_force_conf_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_force_mode_t *const force_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_force_conf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_force_mode_t *const force_conf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_tx_oh_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_tx_oh_t *const tx_oh)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_tx_oh_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tx_oh_t *const tx_oh)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_tx_oh_passthru_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_tx_oh_passthru_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_mode_t *const mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_reset(const vtss_inst_t inst, const vtss_port_no_t port_no)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_cons_act_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_cons_act_t *const cons_act)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_cons_act_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_cons_act_t *const cons_act)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_section_txti_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_tti_t *const txti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_section_txti_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tti_t *const txti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_exp_sl_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_sl_conf_t *const sl)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_path_txti_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_tti_t *const txti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_path_txti_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tti_t *const txti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_test_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_test_conf_t *const test_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_test_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_test_conf_t *const test_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_prbs31_err_inj_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_prbs31_err_inj_t *const inj)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_test_counter_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_test_status_t *const test_status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_defects_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_defects_t *const def)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_status_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_status_t *const status)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_section_acti_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tti_t *const acti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_path_acti_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_tti_t *const acti)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_counter_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_counter_t *const counter)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_perf_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_perf_t *const perf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_counter_threshold_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_counter_threshold_t *const threshold)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_counter_threshold_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_counter_threshold_t *const threshold)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_perf_mode_set(const vtss_inst_t inst, const vtss_port_no_t port_no, const vtss_ewis_perf_mode_t *const perf_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}

vtss_rc vtss_ewis_perf_mode_get(const vtss_inst_t inst, const vtss_port_no_t port_no, vtss_ewis_perf_mode_t *const perf_mode)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_FEATURE_WIS)

#if !defined(VTSS_CHIP_CU_PHY)
vtss_rc vtss_phy_patch_settings_get(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    u8                   *mcb_bus,
                                    u8                   *cfg_buf,
                                    u8                   *stat_buf)
{
    return VTSS_RC_NOT_IMPLEMENTED;
}
#endif // !defined(VTSS_CHIP_CU_PHY)
