// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_
#define _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_

#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api/phy_macsec.h>
#include <microchip/ethernet/hdr_start.h>

mepa_rc meba_phy_macsec_init_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_init_t *const macsec_init);
mepa_rc meba_phy_macsec_init_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_init_t *const macsec_init);
mepa_rc meba_phy_macsec_secy_conf_add(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);
mepa_rc meba_phy_macsec_secy_conf_update(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);
mepa_rc meba_phy_macsec_secy_conf_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf);
mepa_rc meba_phy_macsec_secy_conf_del(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_secy_controlled_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_bool_t *const enable);
mepa_rc meba_phy_macsec_secy_controlled_set(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, const mepa_bool_t enable);
mepa_rc meba_phy_macsec_secy_port_status_get(meba_inst_t inst, mepa_port_no_t port_no, mepa_macsec_port_t port, mepa_macsec_secy_port_status_t *const status);
mepa_rc meba_phy_macsec_port_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t *const search_macsec_port, mepa_macsec_port_t *const found_macsec_port);
mepa_rc meba_phy_macsec_rx_sc_add(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci);
mepa_rc meba_phy_macsec_rx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const mepa_macsec_rx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_rx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_rx_sc_get_next(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const search_sci, mepa_macsec_sci_t *const found_sci);
mepa_rc meba_phy_macsec_rx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci);
mepa_rc meba_phy_macsec_rx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_status_t *const status);
mepa_rc meba_phy_macsec_tx_sc_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_tx_sc_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_tx_sc_get_conf(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf);
mepa_rc meba_phy_macsec_tx_sc_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_tx_sc_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status);
mepa_rc meba_phy_macsec_rx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mepa_macsec_sak_t *const sak);
mepa_rc meba_phy_macsec_rx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active);
mepa_rc meba_phy_macsec_rx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rx_sa_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn);
mepa_rc meba_phy_macsec_rx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_status_t *const status);
mepa_rc meba_phy_macsec_rx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_rx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_pkt_num_t *const lowest_pn, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_rx_seca_lowest_pn_update(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, const mepa_macsec_pkt_num_t lowest_pn);
mepa_rc meba_phy_macsec_tx_sa_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak);
mepa_rc meba_phy_macsec_tx_sa_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active);
mepa_rc meba_phy_macsec_tx_sa_activate(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_disable(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an);
mepa_rc meba_phy_macsec_tx_sa_status_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_status_t *const status);
mepa_rc meba_phy_macsec_tx_seca_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, const mepa_macsec_pkt_num_t next_pn, const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_tx_seca_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_pkt_num_t *const next_pn, mepa_bool_t *const confidentiality, mepa_macsec_sak_t *const sak, mepa_bool_t *const active, mepa_macsec_ssci_t *const ssci);
mepa_rc meba_phy_macsec_controlled_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_secy_port_counters_t *const counters);
mepa_rc meba_phy_macsec_uncontrolled_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_uncontrolled_counters_t *const counters);
mepa_rc meba_phy_macsec_common_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_common_counters_t *const counters);
mepa_rc meba_phy_macsec_secy_cap_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_secy_cap_t *const cap);
mepa_rc meba_phy_macsec_secy_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_secy_counters_t *const counters);
mepa_rc meba_phy_macsec_counters_update(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_rx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_counters_t *const counters);
mepa_rc meba_phy_macsec_tx_sc_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tx_sc_counters_t *const counters);
mepa_rc meba_phy_macsec_tx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const uint16_t an, mepa_macsec_tx_sa_counters_t *const counters);
mepa_rc meba_phy_macsec_rx_sa_counters_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_macsec_rx_sa_counters_t *const counters);
mepa_rc meba_phy_macsec_control_frame_match_conf_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id);
mepa_rc meba_phy_macsec_control_frame_match_conf_del(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t rule_id);
mepa_rc meba_phy_macsec_control_frame_match_conf_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id);
mepa_rc meba_phy_macsec_pattern_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, const mepa_macsec_match_pattern_t *const pattern);
mepa_rc meba_phy_macsec_pattern_del(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action);
mepa_rc meba_phy_macsec_pattern_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_direction_t direction, const mepa_macsec_match_action_t action, mepa_macsec_match_pattern_t *const pattern);
mepa_rc meba_phy_macsec_default_action_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy);
mepa_rc meba_phy_macsec_default_action_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy);
mepa_rc meba_phy_macsec_bypass_mode_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_bypass_mode_t *const bypass);
mepa_rc meba_phy_macsec_bypass_mode_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_bypass_mode_t *const bypass);
mepa_rc meba_phy_macsec_bypass_tag_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_tag_bypass_t tag);
mepa_rc meba_phy_macsec_bypass_tag_get(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, mepa_macsec_tag_bypass_t *const tag);
mepa_rc meba_phy_macsec_mtu_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_mtu_t *const mtu_conf);
mepa_rc meba_phy_macsec_mtu_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mtu_t *mtu_conf);
mepa_rc meba_phy_macsec_frame_capture_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_frame_capture_t capture);
mepa_rc meba_phy_macsec_frame_get(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame);
mepa_rc meba_phy_macsec_event_enable_set(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_macsec_event_t ev_mask, const mepa_bool_t enable);
mepa_rc meba_phy_macsec_event_enable_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_event_t *const ev_mask);
mepa_rc meba_phy_macsec_event_poll(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_event_t *const ev_mask);
mepa_rc meba_phy_macsec_event_seq_threshold_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t threshold);
mepa_rc meba_phy_macsec_event_seq_threshold_get(meba_inst_t inst, const mepa_port_no_t port_no, uint32_t *const threshold);
mepa_rc meba_phy_macsec_egr_intr_sa_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_port_t *const port, uint16_t *const an);
mepa_rc meba_phy_macsec_csr_read(meba_inst_t inst, const mepa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value);
mepa_rc meba_phy_macsec_csr_write(meba_inst_t inst, const mepa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value);
mepa_rc meba_phy_macsec_dbg_counter_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters);
mepa_rc meba_phy_macsec_hmac_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mac_counters_t *const counters, const mepa_bool_t clear);
mepa_rc meba_phy_macsec_lmac_counters_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_mac_counters_t *const counters, const mepa_bool_t clear);
mepa_rc meba_phy_macsec_is_capable(meba_inst_t inst, const mepa_port_no_t port_no, mepa_bool_t *capable);
mepa_rc meba_phy_macsec_dbg_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr);
mepa_rc meba_phy_macsec_inst_count_get(meba_inst_t inst, const mepa_port_no_t port_no, mepa_macsec_inst_count_t *count);
mepa_rc meba_phy_macsec_lmac_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_hmac_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_debug_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_common_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_uncontrolled_counters_clear(meba_inst_t inst, const mepa_port_no_t port_no);
mepa_rc meba_phy_macsec_controlled_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_rxsa_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an);
mepa_rc meba_phy_macsec_rxsc_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci);
mepa_rc meba_phy_macsec_txsa_counters_clear(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t  port, const uint16_t  an);
mepa_rc meba_phy_macsec_txsc_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_secy_counters_clear (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port);
mepa_rc meba_phy_macsec_port_enable_status_get (meba_inst_t inst, const mepa_port_no_t port_no, mepa_bool_t *status);
mepa_rc meba_phy_macsec_rxsa_an_status_get (meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const uint16_t an, mepa_bool_t *status);
mepa_rc meba_phy_mac_block_mtu_get(meba_inst_t inst, const mepa_port_no_t port_no, uint16_t *const mtu_value, mepa_bool_t *const mtu_tag_check);
mepa_rc meba_phy_mac_block_mtu_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint16_t mtu_value, const mepa_bool_t mtu_tag_check);
mepa_rc meba_phy_macsec_fcbuf_frame_gap_comp_set(meba_inst_t inst, const mepa_port_no_t port_no, const uint8_t frm_gap);
mepa_rc meba_phy_macsec_dbg_fcb_block_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr);
mepa_rc meba_phy_macsec_dbg_frm_match_handling_ctrl_reg_dump(meba_inst_t inst, const mepa_port_no_t port_no, const mepa_debug_print_t pr);
#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND
mepa_rc meba_phy_macsec_dbg_reconfig(meba_inst_t inst, const mepa_port_no_t port_no);
#endif
mepa_rc meba_phy_macsec_dbg_update_seq_set(meba_inst_t inst, mepa_port_no_t port_no, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, uint16_t an, mepa_bool_t egr, const mepa_bool_t disable);

#include <microchip/ethernet/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_PHY_MACSEC_DRIVER_H_
