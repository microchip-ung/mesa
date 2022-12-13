// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <mepa_driver.h>
#include <vtss_phy_api.h>
#include "vtss_private.h"

static mepa_rc vtss_phy_macsec_init_set(struct mepa_device       *dev,
                                        const mepa_macsec_init_t *const macsec_init)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_macsec_init_set(NULL, data->port_no, macsec_init);
}

static mepa_rc vtss_phy_macsec_init_get(struct mepa_device *dev,
                                        mepa_macsec_init_t *const macsec_init)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    return vtss_macsec_init_get(NULL, data->port_no, macsec_init);
}

static mepa_rc vtss_phy_macsec_secy_conf_add(struct mepa_device *dev,
                                             const mepa_macsec_port_t port,
                                             const mepa_macsec_secy_conf_t *const conf)
{
    return vtss_macsec_secy_conf_add(NULL, port, conf);
}

static mepa_rc vtss_phy_macsec_secy_conf_update(struct mepa_device *dev,
                                                const mepa_macsec_port_t port,
                                                const mepa_macsec_secy_conf_t *const conf)
{
    return vtss_macsec_secy_conf_update(NULL, port, conf);
}

static mepa_rc vtss_phy_macsec_secy_conf_get(struct mepa_device *dev,
                                             const mepa_macsec_port_t port,
                                             mepa_macsec_secy_conf_t *const conf)
{
    return vtss_macsec_secy_conf_get(NULL, port, conf);
}

static mepa_rc vtss_phy_macsec_secy_conf_del(struct mepa_device *dev,
                                             const mepa_macsec_port_t port)
{
    return vtss_macsec_secy_conf_del(NULL, port);
}

static mepa_rc vtss_phy_macsec_secy_controlled_set(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port,
                                                   const mepa_bool_t enable)
{
    return vtss_macsec_secy_controlled_set(NULL, port, enable);
}

static mepa_rc vtss_phy_macsec_secy_controlled_get(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port,
                                                   mepa_bool_t *const enable)
{
    return vtss_macsec_secy_controlled_get(NULL, port, enable);
}

static mepa_rc vtss_phy_macsec_secy_port_status_get(struct mepa_device *dev,
                                                    const mepa_macsec_port_t port,
                                                    mepa_macsec_secy_port_status_t *const status)
{
    return vtss_macsec_secy_port_status_get(NULL, port, status);
}

static mepa_rc vtss_phy_macsec_port_get_next(struct mepa_device *dev,
                                             const mepa_port_no_t port_no,
                                             const mepa_macsec_port_t *const search_macsec_port,
                                             mepa_macsec_port_t *const found_macsec_port)
{
    return vtss_macsec_port_get_next(NULL, port_no, search_macsec_port, found_macsec_port);
}

static mepa_rc vtss_phy_macsec_rx_sc_add(struct mepa_device *dev,
	                                 const mepa_macsec_port_t port,
                                         const mepa_macsec_sci_t *const sci)
{
    return vtss_macsec_rx_sc_add(NULL, port, sci);
}

static mepa_rc vtss_phy_macsec_rx_sc_update(struct mepa_device *dev,
                                            const mepa_macsec_port_t port,
                                            const mepa_macsec_sci_t *const sci,
                                            const mepa_macsec_rx_sc_conf_t *const conf)
{
    return vtss_macsec_rx_sc_update(NULL, port, sci, conf);
}

static mepa_rc vtss_phy_macsec_rx_sc_get_conf(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              const mepa_macsec_sci_t *const sci,
                                              mepa_macsec_rx_sc_conf_t *const conf)
{
    return vtss_macsec_rx_sc_get_conf(NULL, port, sci, conf);
}

static mepa_rc vtss_phy_macsec_rx_sc_get_next(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              const mepa_macsec_sci_t *const search_sci,
                                              mepa_macsec_sci_t *const found_sci)
{
    return vtss_macsec_rx_sc_get_next(NULL, port, search_sci, found_sci);
}

static mepa_rc vtss_phy_macsec_rx_sc_del(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const mepa_macsec_sci_t *const sci)
{
    return vtss_macsec_rx_sc_del(NULL, port, sci);
}

static mepa_rc vtss_phy_macsec_rx_sc_status_get(struct mepa_device *dev,
                                                const mepa_macsec_port_t port,
                                                const mepa_macsec_sci_t *const sci,
                                                mepa_macsec_rx_sc_status_t *const status)
{
    return vtss_macsec_rx_sc_status_get(NULL, port, sci, status);
}

static mepa_rc vtss_phy_macsec_tx_sc_set(struct mepa_device *dev,
                                         const mepa_macsec_port_t port)
{
    return vtss_macsec_tx_sc_set(NULL, port);
}

static mepa_rc vtss_phy_macsec_tx_sc_update(struct mepa_device *dev,
                                            const mepa_macsec_port_t port,
                                            const mepa_macsec_tx_sc_conf_t *const conf)
{
    return vtss_macsec_tx_sc_update(NULL, port, conf);
}

static mepa_rc vtss_phy_macsec_tx_sc_get_conf(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              mepa_macsec_tx_sc_conf_t *const conf)
{
    return vtss_macsec_tx_sc_get_conf(NULL, port, conf);
}

static mepa_rc vtss_phy_macsec_tx_sc_del(struct mepa_device *dev,
                                         const mepa_macsec_port_t port)
{
    return vtss_macsec_tx_sc_del(NULL, port);
}

static mepa_rc vtss_phy_macsec_tx_sc_status_get(struct mepa_device *dev,
                                                const mepa_macsec_port_t port,
                                                mepa_macsec_tx_sc_status_t *const status)
{
    return vtss_macsec_tx_sc_status_get(NULL, port, status);
}

static mepa_rc vtss_phy_macsec_rx_sa_set(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const mepa_macsec_sci_t *const sci,
                                         const uint16_t an, const uint32_t lowest_pn,
                                         const mepa_macsec_sak_t *const sak)
{
    return vtss_macsec_rx_sa_set(NULL, port, sci, an, lowest_pn, sak);
}

static mepa_rc vtss_phy_macsec_rx_sa_get(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const mepa_macsec_sci_t *const sci,
                                         const uint16_t an,
                                         uint32_t *const lowest_pn,
                                         mepa_macsec_sak_t *const sak,
                                         mepa_bool_t *const active)
{
    return vtss_macsec_rx_sa_get(NULL, port, sci, an, lowest_pn, sak, active);
}

static mepa_rc vtss_phy_macsec_rx_sa_activate(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              const mepa_macsec_sci_t *const sci,
                                              const uint16_t an)
{
    return vtss_macsec_rx_sa_activate(NULL, port, sci, an);
}

static mepa_rc vtss_phy_macsec_rx_sa_disable(struct mepa_device  *dev,
                                             const mepa_macsec_port_t port,
                                             const mepa_macsec_sci_t *const sci,
                                             const uint16_t an)
{
    return vtss_macsec_rx_sa_disable(NULL, port, sci, an);
}

static mepa_rc vtss_phy_macsec_rx_sa_del(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const mepa_macsec_sci_t *const sci,
                                         const uint16_t an)
{
    return vtss_macsec_rx_sa_del(NULL, port, sci, an);
}

static mepa_rc vtss_phy_macsec_rx_sa_lowest_pn_update(struct mepa_device *dev,
                                                      const mepa_macsec_port_t port,
                                                      const mepa_macsec_sci_t *const sci,
                                                      const uint16_t an,
                                                      const uint32_t lowest_pn)
{
    return vtss_macsec_rx_sa_lowest_pn_update(NULL, port, sci, an, lowest_pn);
}

static mepa_rc vtss_phy_macsec_rx_sa_status_get(struct mepa_device *dev,
                                                const mepa_macsec_port_t port,
                                                const mepa_macsec_sci_t *const sci,
                                                const uint16_t an,
                                                mepa_macsec_rx_sa_status_t *const status)
{
    return vtss_macsec_rx_sa_status_get(NULL, port, sci, an, status);
}

static mepa_rc vtss_phy_macsec_rx_seca_set(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_sci_t *const sci,
                                           const uint16_t an,
                                           const mepa_macsec_pkt_num_t lowest_pn,
                                           const mepa_macsec_sak_t *const sak,
                                           const mepa_macsec_ssci_t *const ssci)
{
    return vtss_macsec_rx_seca_set(NULL, port, sci, an, lowest_pn, sak, ssci);
}

static mepa_rc vtss_phy_macsec_rx_seca_get(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_sci_t *const sci,
                                           const uint16_t an,
                                           mepa_macsec_pkt_num_t *const lowest_pn,
                                           mepa_macsec_sak_t *const sak,
                                           mepa_bool_t *const active,
                                           mepa_macsec_ssci_t *const ssci)
{
    return vtss_macsec_rx_seca_get(NULL, port, sci, an, lowest_pn, sak, active, ssci);
}

static mepa_rc vtss_phy_macsec_rx_seca_lowest_pn_update(struct mepa_device *dev,
                                                        const mepa_macsec_port_t port,
                                                        const mepa_macsec_sci_t *const sci,
                                                        const uint16_t an,
                                                        const mepa_macsec_pkt_num_t lowest_pn)
{
    return vtss_macsec_rx_seca_lowest_pn_update(NULL, port, sci, an, lowest_pn);
}

static mepa_rc vtss_phy_macsec_tx_sa_set(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const uint16_t an,
                                         const uint32_t next_pn,
                                         const mepa_bool_t confidentiality,
                                         const mepa_macsec_sak_t *const sak)
{
    return vtss_macsec_tx_sa_set(NULL, port, an, next_pn, confidentiality, sak);
}

static mepa_rc vtss_phy_macsec_tx_sa_get(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const uint16_t an,
                                         uint32_t *const next_pn,
                                         mepa_bool_t *const confidentiality,
                                         mepa_macsec_sak_t *const sak,
                                         mepa_bool_t *const active)
{
    return vtss_macsec_tx_sa_get(NULL, port, an, next_pn, confidentiality, sak, active);
}

static mepa_rc vtss_phy_macsec_tx_sa_activate(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              const uint16_t an)
{
    return vtss_macsec_tx_sa_activate(NULL, port, an);
}

static mepa_rc vtss_phy_macsec_tx_sa_disable(struct mepa_device *dev,
                                             const mepa_macsec_port_t port,
                                             const uint16_t an)
{
    return vtss_macsec_tx_sa_disable(NULL, port, an);
}

static mepa_rc vtss_phy_macsec_tx_sa_del(struct mepa_device *dev,
                                         const mepa_macsec_port_t port,
                                         const uint16_t an)
{
    return vtss_macsec_tx_sa_del(NULL, port, an);
}

static mepa_rc vtss_phy_macsec_tx_sa_status_get(struct mepa_device *dev,
                                                const mepa_macsec_port_t port,
                                                const uint16_t an,
                                                mepa_macsec_tx_sa_status_t *const status)
{
    return vtss_macsec_tx_sa_status_get(NULL, port, an, status);
}

static mepa_rc vtss_phy_macsec_tx_seca_set(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const uint16_t an,
                                           const mepa_macsec_pkt_num_t next_pn,
                                           const mepa_bool_t confidentiality,
                                           const mepa_macsec_sak_t *const sak,
                                           const mepa_macsec_ssci_t *const ssci)
{
    return vtss_macsec_tx_seca_set(NULL, port, an, next_pn, confidentiality, sak, ssci);
}

static mepa_rc vtss_phy_macsec_tx_seca_get(struct mepa_device *dev,
			                   const mepa_macsec_port_t port,
                                           const uint16_t an,
                                           mepa_macsec_pkt_num_t *const next_pn,
                                           mepa_bool_t *const confidentiality,
                                           mepa_macsec_sak_t *const sak,
                                           mepa_bool_t *const active,
                                           mepa_macsec_ssci_t *const ssci)
{
    return vtss_macsec_tx_seca_get(NULL, port, an, next_pn, confidentiality, sak, active, ssci);
}

static mepa_rc vtss_phy_macsec_controlled_counters_get(struct mepa_device *dev,
                                                       const mepa_macsec_port_t port,
                                                       mepa_macsec_secy_port_counters_t *const counters)
{
    return vtss_macsec_controlled_counters_get(NULL, port, counters);
}

static mepa_rc vtss_phy_macsec_uncontrolled_counters_get(struct mepa_device *dev,
                                                         const mepa_port_no_t port_no,
                                                         mepa_macsec_uncontrolled_counters_t *const counters)
{
    return vtss_macsec_uncontrolled_counters_get(NULL, port_no, counters);
}

static mepa_rc vtss_phy_macsec_common_counters_get(struct mepa_device *dev,
                                                   const mepa_port_no_t port_no,
                                                   mepa_macsec_common_counters_t *const counters)
{
    return vtss_macsec_common_counters_get(NULL, port_no, counters);
}

static mepa_rc vtss_phy_macsec_secy_cap_get(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            mepa_macsec_secy_cap_t *const cap)
{
    return vtss_macsec_secy_cap_get(NULL, port_no, cap);
}

static mepa_rc vtss_phy_macsec_secy_counters_get(struct mepa_device *dev,
                                                 const mepa_macsec_port_t port,
                                                 mepa_macsec_secy_counters_t *const counters)
{
    return vtss_macsec_secy_counters_get(NULL, port, counters);
}

static mepa_rc vtss_phy_macsec_counters_update(struct mepa_device *dev,
                                               const mepa_port_no_t port_no)
{
    return vtss_macsec_counters_update(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_counters_clear(struct mepa_device *dev,
                                              const mepa_port_no_t port_no)
{
    return vtss_macsec_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_rx_sc_counters_get(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
	                                          const mepa_macsec_sci_t *const sci,
						  mepa_macsec_rx_sc_counters_t *const counters)
{
    return vtss_macsec_rx_sc_counters_get(NULL, port, sci, counters);
}

static mepa_rc vtss_phy_macsec_tx_sc_counters_get(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
						  mepa_macsec_tx_sc_counters_t *const counters)
{
    return vtss_macsec_tx_sc_counters_get(NULL, port, counters);
}

static mepa_rc vtss_phy_macsec_tx_sa_counters_get(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
						  const uint16_t an,
						  mepa_macsec_tx_sa_counters_t *const counters)
{
    return vtss_macsec_tx_sa_counters_get(NULL, port, an, counters);
}

static mepa_rc vtss_phy_macsec_rx_sa_counters_get(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
						  const mepa_macsec_sci_t *const sci,
						  const uint16_t an,
						  mepa_macsec_rx_sa_counters_t *const counters)
{
    return vtss_macsec_rx_sa_counters_get(NULL, port, sci, an, counters);
}

static mepa_rc vtss_phy_macsec_control_frame_match_conf_set(struct mepa_device *dev ,
                                                            const mepa_port_no_t port_no,
                                                            const mepa_macsec_control_frame_match_conf_t *const conf,
                                                            uint32_t *const rule_id)
{
    return vtss_macsec_control_frame_match_conf_set(NULL, port_no, conf, rule_id);
}


static mepa_rc vtss_phy_macsec_control_frame_match_conf_del(struct mepa_device *dev,
                                                            const mepa_port_no_t port_no,
                                                            const uint32_t rule_id)
{
    return vtss_macsec_control_frame_match_conf_del(NULL, port_no, rule_id);
}

static mepa_rc vtss_phy_macsec_control_frame_match_conf_get(struct mepa_device *dev,
                                                            const mepa_port_no_t port_no,
                                                            mepa_macsec_control_frame_match_conf_t *const conf,
                                                            uint32_t rule_id)
{
    return vtss_macsec_control_frame_match_conf_get(NULL, port_no, conf, rule_id);
}

static mepa_rc vtss_phy_macsec_pattern_set(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_direction_t direction,
                                           const mepa_macsec_match_action_t action,
                                           const mepa_macsec_match_pattern_t *const pattern)
{
    return vtss_macsec_pattern_set(NULL, port, direction, action, pattern);
}

static mepa_rc vtss_phy_macsec_pattern_del(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_direction_t direction,
                                           const mepa_macsec_match_action_t action)
{
    return vtss_macsec_pattern_del(NULL, port, direction, action);
}

static mepa_rc vtss_phy_macsec_pattern_get(struct mepa_device *dev,
                                           const mepa_macsec_port_t port,
                                           const mepa_macsec_direction_t direction,
                                           const mepa_macsec_match_action_t action,
                                           mepa_macsec_match_pattern_t *const pattern)
{
    return vtss_macsec_pattern_get(NULL, port, direction, action, pattern);
}

static mepa_rc vtss_phy_macsec_default_action_set(struct mepa_device *dev,
                                                  const mepa_port_no_t port_no,
                                                  const mepa_macsec_default_action_policy_t *const policy)
{
    return vtss_macsec_default_action_set(NULL, port_no, policy);
}

static mepa_rc vtss_phy_macsec_default_action_get(struct mepa_device *dev,
                                                  const mepa_port_no_t port_no,
                                                  mepa_macsec_default_action_policy_t *const policy)
{
    return vtss_macsec_default_action_get(NULL, port_no, policy);
}

static mepa_rc vtss_phy_macsec_bypass_mode_set(struct mepa_device *dev,
                                               const mepa_port_no_t port_no,
                                               const mepa_macsec_bypass_mode_t *const bypass)
{
    return vtss_macsec_bypass_mode_set(NULL, port_no, bypass);
}

static mepa_rc vtss_phy_macsec_bypass_mode_get(struct mepa_device *dev,
                                               const mepa_port_no_t port_no,
                                               mepa_macsec_bypass_mode_t *const bypass)
{
    return vtss_macsec_bypass_mode_get(NULL, port_no, bypass);
}

static mepa_rc vtss_phy_macsec_bypass_tag_set(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              const mepa_macsec_tag_bypass_t tag)
{
    return vtss_macsec_bypass_tag_set(NULL, port, tag);
}

static mepa_rc vtss_phy_macsec_bypass_tag_get(struct mepa_device *dev,
                                              const mepa_macsec_port_t port,
                                              mepa_macsec_tag_bypass_t *const tag)
{
    return vtss_macsec_bypass_tag_get(NULL, port, tag);
}

static mepa_rc vtss_phy_macsec_mtu_set(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       const mepa_macsec_mtu_t *const mtu_conf)
{
    return vtss_macsec_mtu_set(NULL, port_no, mtu_conf);
}

static mepa_rc vtss_phy_macsec_mtu_get(struct mepa_device *dev,
                                       const mepa_port_no_t port_no,
                                       mepa_macsec_mtu_t *mtu_conf)
{
    return vtss_macsec_mtu_get(NULL, port_no, mtu_conf);
}

static mepa_rc vtss_phy_macsec_frame_capture_set(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 const mepa_macsec_frame_capture_t capture)
{
    return vtss_macsec_frame_capture_set(NULL, port_no, capture);
}

static mepa_rc vtss_phy_macsec_frame_get(struct mepa_device *dev,
                                         const mepa_port_no_t port_no,
                                         const uint32_t buf_length,
                                         uint32_t *const return_length,
                                         uint8_t *const frame)
{
    return vtss_macsec_frame_get(NULL, port_no, buf_length, return_length, frame);
}

static mepa_rc vtss_phy_macsec_event_enable_set(struct mepa_device *dev,
                                                const mepa_port_no_t port_no,
                                                const mepa_macsec_event_t ev_mask,
                                                const mepa_bool_t enable)
{
    return vtss_macsec_event_enable_set(NULL, port_no, ev_mask, enable);
}

static mepa_rc vtss_phy_macsec_event_enable_get(struct mepa_device *dev,
                                                const mepa_port_no_t port_no,
                                                mepa_macsec_event_t *const ev_mask)

{
    return vtss_macsec_event_enable_get(NULL, port_no, ev_mask);
}

static mepa_rc vtss_phy_macsec_event_poll(struct mepa_device *dev,
                                          const mepa_port_no_t port_no,
                                          mepa_macsec_event_t *const ev_mask)
{
    return vtss_macsec_event_poll(NULL, port_no, ev_mask);
}

static mepa_rc vtss_phy_macsec_event_seq_threshold_set(struct mepa_device *dev,
                                                       const mepa_port_no_t port_no,
                                                       const uint32_t threshold)
{
    return vtss_macsec_event_seq_threshold_set(NULL, port_no, threshold);
}

static mepa_rc vtss_phy_macsec_event_seq_threshold_get(struct mepa_device *dev,
                                                       const mepa_port_no_t port_no,
                                                       uint32_t *const threshold)
{
    return vtss_macsec_event_seq_threshold_get(NULL, port_no, threshold);
}

static mepa_rc vtss_phy_macsec_egr_intr_sa_get(struct mepa_device *dev,
                                               const mepa_port_no_t port_no,
                                               mepa_macsec_port_t *const port,
                                               uint16_t *const an)
{
    return vtss_macsec_egr_intr_sa_get(NULL, port_no, port, an);
}

static mepa_rc vtss_phy_macsec_csr_read(struct mepa_device *dev,
                                        const mepa_port_no_t port_no,
                                        const uint16_t mmd,
                                        const uint32_t addr,
                                        uint32_t *const value)
{
    return vtss_macsec_csr_read(NULL, port_no, mmd, addr, value);
}

static mepa_rc vtss_phy_macsec_csr_write(struct mepa_device *dev,
                                         const mepa_port_no_t port_no,
                                         const uint32_t mmd,
                                         const uint32_t addr,
                                         const uint32_t value)
{
    return vtss_macsec_csr_write(NULL, port_no, mmd, addr, value);
}


static mepa_rc vtss_phy_macsec_dbg_counter_get(struct mepa_device *dev,
                                               const mepa_port_no_t port_no,
                                               mepa_macsec_rc_dbg_counters_t *const counters)
{
    return vtss_macsec_dbg_counter_get(NULL, port_no, counters);
}

static mepa_rc vtss_phy_macsec_hmac_counters_get(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 mepa_macsec_mac_counters_t *const counters,
                                                 const mepa_bool_t clear)
{
    return vtss_macsec_hmac_counters_get(NULL, port_no, counters, clear);
}

static mepa_rc vtss_phy_macsec_lmac_counters_get(struct mepa_device *dev,
                                                 const mepa_port_no_t port_no,
                                                 mepa_macsec_mac_counters_t *const counters,
                                                 const mepa_bool_t clear)
{
    return vtss_macsec_lmac_counters_get(NULL, port_no, counters, clear);
}

static mepa_rc vtss_phy_macsec_is_capable(struct mepa_device *dev,
                                          const mepa_port_no_t port_no,
                                          mepa_bool_t *capable)
{
    return vtss_macsec_is_capable(NULL, port_no, capable);
}

static mepa_rc vtss_phy_macsec_dbg_reg_dump(struct mepa_device *dev,
                                            const mepa_port_no_t port_no,
                                            const mepa_debug_print_t pr)
{
    return vtss_macsec_dbg_reg_dump(NULL, port_no, pr);
}

static mepa_rc vtss_phy_macsec_inst_count_get(struct mepa_device *dev,
                                              const vtss_port_no_t   port_no,
                                              mepa_macsec_inst_count_t *count)
{
    return vtss_macsec_inst_count_get(NULL, port_no, count);
}

static mepa_rc vtss_phy_macsec_lmac_counters_clear(struct mepa_device *dev,
                                                   const mepa_port_no_t port_no)
{
    return vtss_macsec_lmac_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_hmac_counters_clear(struct mepa_device *dev,
                                                   const mepa_port_no_t port_no)
{
    return vtss_macsec_hmac_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_debug_counters_clear(struct mepa_device *dev,
                                                    const mepa_port_no_t port_no)
{
    return vtss_macsec_debug_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_common_counters_clear(struct mepa_device *dev,
                                                     const mepa_port_no_t port_no)
{
    return vtss_macsec_common_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_uncontrolled_counters_clear(struct mepa_device *dev,
                                                           const mepa_port_no_t port_no)
{
    return vtss_macsec_uncontrolled_counters_clear(NULL, port_no);
}

static mepa_rc vtss_phy_macsec_controlled_counters_clear (struct mepa_device *dev,
                                                          const mepa_macsec_port_t port)
{
    return vtss_macsec_controlled_counters_clear(NULL, port);
}

static mepa_rc vtss_phy_macsec_rxsa_counters_clear(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port,
                                                   const mepa_macsec_sci_t *const sci,
                                                   const uint16_t an)
{
    return vtss_macsec_rxsa_counters_clear(NULL, port, sci, an);
}

static mepa_rc vtss_phy_macsec_rxsc_counters_clear(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port,
                                                   const mepa_macsec_sci_t  *const sci)
{
    return vtss_macsec_rxsc_counters_clear(NULL, port, sci);
}

static mepa_rc vtss_phy_macsec_txsa_counters_clear(struct mepa_device *dev,
                                                   const mepa_macsec_port_t  port,
                                                   const uint16_t  an)
{
    return vtss_macsec_txsa_counters_clear(NULL, port, an);
}

static mepa_rc vtss_phy_macsec_txsc_counters_clear(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port)
{
    return vtss_macsec_txsc_counters_clear(NULL, port);
}

static mepa_rc vtss_phy_macsec_secy_counters_clear(struct mepa_device *dev,
                                                   const mepa_macsec_port_t port)
{
    return vtss_macsec_secy_counters_clear(NULL, port);
}

static mepa_rc vtss_phy_macsec_port_enable_status_get(struct mepa_device *dev,
                                                      const mepa_port_no_t port_no,
                                                      mepa_bool_t *status)
{
    return vtss_macsec_port_enable_status_get(NULL, port_no, status);
}

static mepa_rc vtss_phy_macsec_rxsa_an_status_get(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
                                                  const mepa_macsec_sci_t *const sci,
                                                  const uint16_t an,
                                                  mepa_bool_t *status)
{
    return vtss_macsec_rxsa_an_status_get(NULL, port, sci, an, status);
}

static mepa_rc vtss_phy_mac_block_mtu_get(struct mepa_device *dev,
                                          const mepa_port_no_t port_no,
                                          uint16_t *const mtu_value,
                                          mepa_bool_t *const mtu_tag_check)
{
    return vtss_mac_block_mtu_get(NULL, port_no, mtu_value, mtu_tag_check);
}

static mepa_rc vtss_phy_mac_block_mtu_set(struct mepa_device *dev,
                                          const mepa_port_no_t port_no,
                                          const uint16_t mtu_value,
                                          const mepa_bool_t mtu_tag_check)
{
    return vtss_mac_block_mtu_set(NULL, port_no, mtu_value, mtu_tag_check);
}

static mepa_rc vtss_phy_macsec_fcbuf_frame_gap_comp_set(struct mepa_device *dev,
                                                        const mepa_port_no_t port_no,
                                                        const uint8_t frm_gap)
{
    return vtss_macsec_fcbuf_frame_gap_comp_set(NULL, port_no, frm_gap);
}

static mepa_rc vtss_phy_macsec_dbg_fcb_block_reg_dump(struct mepa_device *dev,
                                                      const mepa_port_no_t port_no,
                                                      const mepa_debug_print_t pr)
{
    return vtss_macsec_dbg_fcb_block_reg_dump(NULL, port_no, pr);
}

static mepa_rc vtss_phy_macsec_dbg_frm_match_handling_ctrl_reg_dump(struct mepa_device *dev,
                                                                    const mepa_port_no_t port_no,
                                                                    const mepa_debug_print_t pr)

{
    return vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump(NULL, port_no, pr);
}

#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND

static mepa_rc vtss_phy_macsec_dbg_reconfig(struct mepa_device *dev,
                                            const mepa_port_no_t port_no)
{
    return vtss_macsec_dbg_reconfig(NULL, port_no, pr);
}

#endif


static mepa_rc vtss_phy_macsec_dbg_update_seq_set(struct mepa_device *dev,
                                                  const mepa_macsec_port_t port,
                                                  const mepa_macsec_sci_t *const sci,
                                                  uint16_t an,
                                                  mepa_bool_t egr,
                                                  const mepa_bool_t disable)
{
    return vtss_macsec_dbg_update_seq_set(NULL, port, sci, an, egr, disable);
}

mepa_macsec_driver_t vtss_macsec_drivers = {
    .mepa_macsec_init_set = vtss_phy_macsec_init_set,
    .mepa_macsec_init_get = vtss_phy_macsec_init_get,
    .mepa_macsec_secy_conf_add = vtss_phy_macsec_secy_conf_add,
    .mepa_macsec_secy_conf_update = vtss_phy_macsec_secy_conf_update,
    .mepa_macsec_secy_conf_get = vtss_phy_macsec_secy_conf_get,
    .mepa_macsec_secy_conf_del = vtss_phy_macsec_secy_conf_del,
    .mepa_macsec_secy_controlled_set = vtss_phy_macsec_secy_controlled_set,
    .mepa_macsec_secy_controlled_get = vtss_phy_macsec_secy_controlled_get,
    .mepa_macsec_secy_port_status_get = vtss_phy_macsec_secy_port_status_get,
    .mepa_macsec_port_get_next = vtss_phy_macsec_port_get_next,
    .mepa_macsec_rx_sc_add = vtss_phy_macsec_rx_sc_add,
    .mepa_macsec_rx_sc_update = vtss_phy_macsec_rx_sc_update,
    .mepa_macsec_rx_sc_get_conf = vtss_phy_macsec_rx_sc_get_conf,
    .mepa_macsec_rx_sc_get_next = vtss_phy_macsec_rx_sc_get_next,
    .mepa_macsec_rx_sc_del = vtss_phy_macsec_rx_sc_del,
    .mepa_macsec_rx_sc_status_get = vtss_phy_macsec_rx_sc_status_get,
    .mepa_macsec_tx_sc_set = vtss_phy_macsec_tx_sc_set,
    .mepa_macsec_tx_sc_update = vtss_phy_macsec_tx_sc_update,
    .mepa_macsec_tx_sc_get_conf = vtss_phy_macsec_tx_sc_get_conf,
    .mepa_macsec_tx_sc_del = vtss_phy_macsec_tx_sc_del,
    .mepa_macsec_tx_sc_status_get = vtss_phy_macsec_tx_sc_status_get,
    .mepa_macsec_rx_sa_set = vtss_phy_macsec_rx_sa_set,
    .mepa_macsec_rx_sa_get =  vtss_phy_macsec_rx_sa_get,
    .mepa_macsec_rx_sa_activate = vtss_phy_macsec_rx_sa_activate,
    .mepa_macsec_rx_sa_disable = vtss_phy_macsec_rx_sa_disable,
    .mepa_macsec_rx_sa_del = vtss_phy_macsec_rx_sa_del,
    .mepa_macsec_rx_sa_lowest_pn_update = vtss_phy_macsec_rx_sa_lowest_pn_update,
    .mepa_macsec_rx_sa_status_get = vtss_phy_macsec_rx_sa_status_get,
    .mepa_macsec_rx_seca_set = vtss_phy_macsec_rx_seca_set,
    .mepa_macsec_rx_seca_get = vtss_phy_macsec_rx_seca_get,
    .mepa_macsec_rx_seca_lowest_pn_update = vtss_phy_macsec_rx_seca_lowest_pn_update,
    .mepa_macsec_tx_sa_set = vtss_phy_macsec_tx_sa_set,
    .mepa_macsec_tx_sa_get = vtss_phy_macsec_tx_sa_get,
    .mepa_macsec_tx_sa_activate = vtss_phy_macsec_tx_sa_activate,
    .mepa_macsec_tx_sa_disable = vtss_phy_macsec_tx_sa_disable,
    .mepa_macsec_tx_sa_del = vtss_phy_macsec_tx_sa_del,
    .mepa_macsec_tx_sa_status_get = vtss_phy_macsec_tx_sa_status_get,
    .mepa_macsec_tx_seca_set = vtss_phy_macsec_tx_seca_set,
    .mepa_macsec_tx_seca_get = vtss_phy_macsec_tx_seca_get,
    .mepa_macsec_controlled_counters_get = vtss_phy_macsec_controlled_counters_get,
    .mepa_macsec_uncontrolled_counters_get = vtss_phy_macsec_uncontrolled_counters_get,
    .mepa_macsec_common_counters_get = vtss_phy_macsec_common_counters_get,
    .mepa_macsec_secy_cap_get = vtss_phy_macsec_secy_cap_get,
    .mepa_macsec_secy_counters_get = vtss_phy_macsec_secy_counters_get,
    .mepa_macsec_counters_update = vtss_phy_macsec_counters_update,
    .mepa_macsec_counters_clear = vtss_phy_macsec_counters_clear,
    .mepa_macsec_rx_sc_counters_get = vtss_phy_macsec_rx_sc_counters_get,
    .mepa_macsec_tx_sc_counters_get = vtss_phy_macsec_tx_sc_counters_get,
    .mepa_macsec_tx_sa_counters_get = vtss_phy_macsec_tx_sa_counters_get,
    .mepa_macsec_rx_sa_counters_get = vtss_phy_macsec_rx_sa_counters_get,
    .mepa_macsec_control_frame_match_conf_set = vtss_phy_macsec_control_frame_match_conf_set,
    .mepa_macsec_control_frame_match_conf_del = vtss_phy_macsec_control_frame_match_conf_del,
    .mepa_macsec_control_frame_match_conf_get = vtss_phy_macsec_control_frame_match_conf_get,
    .mepa_macsec_pattern_set = vtss_phy_macsec_pattern_set,
    .mepa_macsec_pattern_del = vtss_phy_macsec_pattern_del,
    .mepa_macsec_pattern_get = vtss_phy_macsec_pattern_get,
    .mepa_macsec_default_action_set = vtss_phy_macsec_default_action_set,
    .mepa_macsec_default_action_get = vtss_phy_macsec_default_action_get,
    .mepa_macsec_bypass_mode_set = vtss_phy_macsec_bypass_mode_set,
    .mepa_macsec_bypass_mode_get = vtss_phy_macsec_bypass_mode_get,
    .mepa_macsec_bypass_tag_set = vtss_phy_macsec_bypass_tag_set,
    .mepa_macsec_bypass_tag_get = vtss_phy_macsec_bypass_tag_get,
    .mepa_macsec_mtu_set = vtss_phy_macsec_mtu_set,
    .mepa_macsec_mtu_get = vtss_phy_macsec_mtu_get,
    .mepa_macsec_frame_capture_set = vtss_phy_macsec_frame_capture_set,
    .mepa_macsec_frame_get = vtss_phy_macsec_frame_get,
    .mepa_macsec_event_enable_set = vtss_phy_macsec_event_enable_set,
    .mepa_macsec_event_enable_get = vtss_phy_macsec_event_enable_get,
    .mepa_macsec_event_poll = vtss_phy_macsec_event_poll,
    .mepa_macsec_event_seq_threshold_set = vtss_phy_macsec_event_seq_threshold_set,
    .mepa_macsec_event_seq_threshold_get = vtss_phy_macsec_event_seq_threshold_get,
    .mepa_macsec_egr_intr_sa_get = vtss_phy_macsec_egr_intr_sa_get,
    .mepa_macsec_csr_read = vtss_phy_macsec_csr_read,
    .mepa_macsec_csr_write = vtss_phy_macsec_csr_write,
    .mepa_macsec_dbg_counter_get = vtss_phy_macsec_dbg_counter_get,
    .mepa_macsec_hmac_counters_get = vtss_phy_macsec_hmac_counters_get,
    .mepa_macsec_lmac_counters_get = vtss_phy_macsec_lmac_counters_get,
    .mepa_macsec_is_capable = vtss_phy_macsec_is_capable,
    .mepa_macsec_dbg_reg_dump = vtss_phy_macsec_dbg_reg_dump,
    .mepa_macsec_inst_count_get = vtss_phy_macsec_inst_count_get,
    .mepa_macsec_lmac_counters_clear = vtss_phy_macsec_lmac_counters_clear,
    .mepa_macsec_hmac_counters_clear = vtss_phy_macsec_hmac_counters_clear,
    .mepa_macsec_debug_counters_clear = vtss_phy_macsec_debug_counters_clear,
    .mepa_macsec_common_counters_clear = vtss_phy_macsec_common_counters_clear,
    .mepa_macsec_uncontrolled_counters_clear = vtss_phy_macsec_uncontrolled_counters_clear,
    .mepa_macsec_controlled_counters_clear = vtss_phy_macsec_controlled_counters_clear,
    .mepa_macsec_rxsa_counters_clear = vtss_phy_macsec_rxsa_counters_clear,
    .mepa_macsec_rxsc_counters_clear = vtss_phy_macsec_rxsc_counters_clear,
    .mepa_macsec_txsa_counters_clear = vtss_phy_macsec_txsa_counters_clear,
    .mepa_macsec_txsc_counters_clear = vtss_phy_macsec_txsc_counters_clear,
    .mepa_macsec_secy_counters_clear = vtss_phy_macsec_secy_counters_clear,
    .mepa_macsec_port_enable_status_get = vtss_phy_macsec_port_enable_status_get,
    .mepa_macsec_rxsa_an_status_get = vtss_phy_macsec_rxsa_an_status_get,
    .mepa_mac_block_mtu_get = vtss_phy_mac_block_mtu_get,
    .mepa_mac_block_mtu_set = vtss_phy_mac_block_mtu_set,
    .mepa_macsec_fcbuf_frame_gap_comp_set = vtss_phy_macsec_fcbuf_frame_gap_comp_set,
    .mepa_macsec_dbg_fcb_block_reg_dump = vtss_phy_macsec_dbg_fcb_block_reg_dump,
    .mepa_macsec_dbg_frm_match_handling_ctrl_reg_dump = vtss_phy_macsec_dbg_frm_match_handling_ctrl_reg_dump,
#ifdef MEPA_MACSEC_FIFO_OVERFLOW_WORKAROUND
    .mepa_macsec_dbg_reconfig = vtss_phy_macsec_dbg_reconfig,
#endif
    .mepa_macsec_dbg_update_seq_set = vtss_phy_macsec_dbg_update_seq_set,

};