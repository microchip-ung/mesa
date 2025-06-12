// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_macsec_private.h"
#include "lan80xx_macsec.h"


#ifndef MEPA_LAN80XX_MSEC

mepa_rc lan80xx_macsec_init_set_priv(mepa_device_t *dev, const mepa_macsec_init_t *const init)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_init_get_priv(mepa_device_t *dev, mepa_macsec_init_t *const init)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_is_capable_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_bool_t *capable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_default_action_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_default_action_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_conf_add_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_conf_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_conf_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_secy_conf_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_controlled_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_bool_t enable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_controlled_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_bool_t *const enable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_pattern_set_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action,
                                        const mepa_macsec_match_pattern_t  *const pattern)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_pattern_get_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t  action,
                                        mepa_macsec_match_pattern_t        *const pattern)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_pattern_del_priv(mepa_device_t                    *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_set_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t port,
                                      const u16          an,
                                      const u32          next_pn,
                                      const mepa_bool_t  confidentiality,
                                      const mepa_macsec_sak_t *const sak)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_status_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_get_conf_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_add_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const mepa_macsec_sci_t  *const sci)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_update_priv(mepa_device_t                  *dev,
                                         const mepa_macsec_port_t       port,
                                         const mepa_macsec_sci_t        *const sci,
                                         const mepa_macsec_rx_sc_conf_t *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_get_conf_priv(mepa_device_t                  *dev,
                                           const mepa_macsec_port_t       port,
                                           const mepa_macsec_sci_t        *const sci,
                                           mepa_macsec_rx_sc_conf_t       *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_status_get_priv(mepa_device_t *dev,
                                             const mepa_macsec_port_t        port,
                                             const mepa_macsec_sci_t         *const sci,
                                             mepa_macsec_rx_sc_status_t      *const status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_port_enable_status_get_priv(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_bool_t  *status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_get_priv(mepa_device_t            *dev,
                                      const mepa_macsec_port_t port,
                                      const u16                an,
                                      u32 *const               next_pn,
                                      mepa_bool_t              *const confidentiality,
                                      mepa_macsec_sak_t        *const sak,
                                      mepa_bool_t              *const active)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_seca_set_priv(mepa_device_t                *dev,
                                        const mepa_macsec_port_t     port,
                                        const u16                    an,
                                        const mepa_macsec_pkt_num_t  next_pn,
                                        const mepa_bool_t            confidentiality,
                                        const mepa_macsec_sak_t      *const sak,
                                        const mepa_macsec_ssci_t     *const ssci)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t  port,
                                        const u16                 an,
                                        mepa_macsec_pkt_num_t     *const next_pn,
                                        mepa_bool_t               *const confidentiality,
                                        mepa_macsec_sak_t         *const sak,
                                        mepa_bool_t               *const active,
                                        mepa_macsec_ssci_t        *const ssci)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_set_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      const u32                     lowest_pn,
                                      const mepa_macsec_sak_t       *const sak)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_get_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      u32                           *const lowest_pn,
                                      mepa_macsec_sak_t             *const sak,
                                      mepa_bool_t                   *const active)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_seca_set_priv(mepa_device_t *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        const mepa_macsec_pkt_num_t   lowest_pn,
                                        const mepa_macsec_sak_t       *const sak,
                                        const mepa_macsec_ssci_t      *const ssci)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        mepa_macsec_pkt_num_t         *const lowest_pn,
                                        mepa_macsec_sak_t             *const sak,
                                        mepa_bool_t                   *const active,
                                        mepa_macsec_ssci_t            *const ssci)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_del_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t    port,
                                      const mepa_macsec_sci_t     *const sci)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const u16                 an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_activate_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16 an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_disable_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16  an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_status_get_priv(mepa_device_t  *dev, const mepa_macsec_port_t  port, const u16 an, mepa_macsec_tx_sa_status_t  *const status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_activate_priv(mepa_device_t  *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci, const u16 an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_disable_priv(mepa_device_t *dev,
                                          const mepa_macsec_port_t  port,
                                          const mepa_macsec_sci_t   *const sci,
                                          const u16                 an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const mepa_macsec_sci_t   *const sci,
                                      const u16                 an)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_status_get_priv(mepa_device_t    *dev,
                                             const mepa_macsec_port_t    port,
                                             const mepa_macsec_sci_t     *const sci,
                                             const u16                   an,
                                             mepa_macsec_rx_sa_status_t  *const status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sa_lowest_pn_update_priv(mepa_device_t  *dev,
                                                   const mepa_macsec_port_t     port,
                                                   const mepa_macsec_sci_t      *const sci,
                                                   const u16                    an,
                                                   const u32                    lowest_pn)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rxsa_an_status_get_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               const u16                 an,
                                               mepa_bool_t               *status)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sa_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const u16                       an,
                                               mepa_macsec_tx_sa_counters_t    *const counters)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_tx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               mepa_macsec_tx_sc_counters_t    *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const mepa_macsec_sci_t         *const sci,
                                               mepa_macsec_rx_sc_counters_t    *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_rx_sa_counters_get_priv(mepa_device_t                *dev,
                                               const mepa_macsec_port_t     port,
                                               const mepa_macsec_sci_t      *const sci,
                                               const u16                    an,
                                               mepa_macsec_rx_sa_counters_t *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_txsc_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_txsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const u16  an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_rxsc_counters_clear_priv(mepa_device_t *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_rxsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci,
                                                const u16  an)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_counters_get_priv(mepa_device_t                 *dev,
                                              const mepa_macsec_port_t      port,
                                              mepa_macsec_secy_counters_t   *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_controlled_counters_get_priv(mepa_device_t                       *dev,
                                                    const mepa_port_no_t                port_no,
                                                    const mepa_macsec_port_t            port,
                                                    mepa_macsec_secy_port_counters_t    *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_get_priv(mepa_device_t                       *dev,
                                                      const mepa_port_no_t                port_no,
                                                      const mepa_macsec_port_t            port,
                                                      mepa_macsec_uncontrolled_counters_t *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_common_counters_get_priv(mepa_device_t                       *dev,
                                                const mepa_port_no_t                port_no,
                                                const mepa_macsec_port_t            port,
                                                mepa_macsec_common_counters_t       *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_counters_update_priv(mepa_device_t  *dev,
                                            const mepa_port_no_t  port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_clear_priv(mepa_device_t  *dev,
                                                        const mepa_port_no_t      port_no,
                                                        const mepa_macsec_port_t  port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_controlled_counters_clear_priv(mepa_device_t  *dev,
                                                      const mepa_port_no_t      port_no,
                                                      const mepa_macsec_port_t  port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_common_counters_clear_priv(mepa_device_t  *dev,
                                                  const mepa_port_no_t      port_no,
                                                  const mepa_macsec_port_t  port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_lmac_counters_get_priv(mepa_device_t               *dev,
                                              const mepa_port_no_t        port_no,
                                              mepa_macsec_mac_counters_t  *const counters,
                                              mepa_bool_t                 clear)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_hmac_counters_get_priv(mepa_device_t               *dev,
                                              const mepa_port_no_t        port_no,
                                              mepa_macsec_mac_counters_t  *const counters,
                                              mepa_bool_t                 clear)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_lmac_counters_clear_priv(mepa_device_t         *dev,
                                                const mepa_port_no_t  port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}


mepa_rc lan80xx_macsec_hmac_counters_clear_priv(mepa_device_t      *dev,
                                                const mepa_port_no_t  port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_debug_counters_clear_priv(mepa_device_t          *dev,
                                                 const mepa_port_no_t   port_no)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_csr_read_priv(mepa_device_t               *dev,
                                     const mepa_port_no_t        port_no,
                                     const u16                   mmd,
                                     const u32                   addr,
                                     u32                         *const value)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_csr_write_priv(mepa_device_t               *dev,
                                      const mepa_port_no_t        port_no,
                                      const u32                   mmd,
                                      const u32                   addr,
                                      const u32                   value)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_mtu_set_priv(mepa_device_t            *dev,
                                    const mepa_port_no_t     port_no,
                                    const mepa_macsec_mtu_t  *const mtu_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_mtu_get_priv(mepa_device_t           *dev,
                                    const mepa_port_no_t    port_no,
                                    mepa_macsec_mtu_t       *mtu_conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_mac_block_mtu_set_priv(mepa_device_t         *dev,
                                       const mepa_port_no_t  port_no,
                                       const u16             mtu_value,
                                       const mepa_bool_t     mtu_tag_check)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_mac_block_mtu_get_priv(mepa_device_t        *dev,
                                       const mepa_port_no_t port_no,
                                       u16                  *const mtu_value,
                                       mepa_bool_t          *const mtu_tag_check)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_dbg_update_seq_set_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               u16                       an,
                                               mepa_bool_t               egr,
                                               const mepa_bool_t         disable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_frame_capture_set_priv(mepa_device_t                       *dev,
                                              const mepa_port_no_t                port_no,
                                              const mepa_macsec_frame_capture_t   capture)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_frame_get_priv(mepa_device_t                 *dev,
                                      const mepa_port_no_t          port_no,
                                      const u32                     buf_length,
                                      u32                           *const frm_length,
                                      u8                            *const frame)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_seq_threshold_set_priv(mepa_device_t         *dev,
                                                    const mepa_port_no_t  port_no,
                                                    const u32             threshold)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_seq_threshold_get_priv(mepa_device_t         *dev,
                                                    const mepa_port_no_t  port_no,
                                                    u32                   *const threshold)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_set_priv(mepa_device_t         *dev,
                                                        const mepa_port_no_t  port_no,
                                                        const u64             threshold)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_get_priv(mepa_device_t         *dev,
                                                        const mepa_port_no_t  port_no,
                                                        u64                   *const threshold)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_secy_cap_get_priv(mepa_device_t                 *dev,
                                         const mepa_port_no_t          port_no,
                                         mepa_macsec_secy_cap_t        *const cap)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_enable_set_priv(mepa_device_t        *dev,
                                             const mepa_port_no_t        port_no,
                                             const mepa_macsec_event_t   ev_mask,
                                             const mepa_bool_t           enable)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_enable_get_priv(mepa_device_t    *dev,
                                             const mepa_port_no_t   port_no,
                                             mepa_macsec_event_t    *const ev_mask)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_event_poll_priv(mepa_device_t         *dev,
                                       const mepa_port_no_t  port_no,
                                       mepa_macsec_event_t  *const ev_mask)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_port_get_next_priv(mepa_device_t               *dev,
                                          const mepa_port_no_t        port_no,
                                          const mepa_macsec_port_t    *const search_macsec_port,
                                          mepa_macsec_port_t          *const found_macsec_port)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_egr_policy_mode_set_priv(mepa_device_t                   *dev,
                                                const mepa_port_no_t            port_no,
                                                const phy25g_macsec_egr_mode_t  egr_policy_mode,
                                                const mepa_etype_t              hdr_eth_type)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_egr_policy_mode_get_priv(mepa_device_t             *dev,
                                                const mepa_port_no_t      port_no,
                                                phy25g_macsec_egr_mode_t  egr_policy_mode)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_bypass_mode_set_priv(mepa_device_t                    *dev,
                                            const mepa_port_no_t             port_no,
                                            const mepa_macsec_bypass_mode_t  *const bypass)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_bypass_mode_get_priv(mepa_device_t              *dev,
                                            const mepa_port_no_t       port_no,
                                            mepa_macsec_bypass_mode_t  *const bypass)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_bypass_tag_set_priv(mepa_device_t                     *dev,
                                           const mepa_macsec_port_t          port,
                                           const mepa_macsec_tag_bypass_t    tag)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_bypass_tag_get_priv(mepa_device_t                 *dev,
                                           const mepa_macsec_port_t      port,
                                           mepa_macsec_tag_bypass_t      *const tag)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_cleartags_conf_set_priv(mepa_device_t                         *dev,
                                               const mepa_port_no_t                  port_no,
                                               const mepa_bool_t                     enable,
                                               const phy25g_macsec_cleartags_conf_t  *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_control_frame_match_conf_set_priv(mepa_device_t                                 *dev,
                                                         const mepa_port_no_t                          port_no,
                                                         const mepa_macsec_control_frame_match_conf_t *const conf,
                                                         u32                                          *const rule_id)

{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_control_frame_match_conf_del_priv(mepa_device_t             *dev,
                                                         const mepa_port_no_t      port_no,
                                                         const u32                 rule_id)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_control_frame_match_conf_get_priv(mepa_device_t                              *dev,
                                                         const mepa_port_no_t                       port_no,
                                                         mepa_macsec_control_frame_match_conf_t     *const conf,
                                                         u32                                        rule_id)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_cleartags_conf_get_priv(mepa_device_t                      *dev,
                                               const mepa_port_no_t               port_no,
                                               mepa_bool_t                        enable,
                                               phy25g_macsec_cleartags_conf_t     *const conf)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_inst_count_get_priv(mepa_device_t             *dev,
                                           const mepa_port_no_t      port_no,
                                           mepa_macsec_inst_count_t  *counts)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_dbg_reg_dump_priv(mepa_device_t     *dev,
                                         mepa_port_no_t     port_no,
                                         mepa_debug_print_t pr)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_rc lan80xx_macsec_dbg_counter_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}

mepa_bool_t lan80xx_phy_is_macsec_capable(mepa_device_t *dev)
{
    return MEPA_RC_NOT_IMPLEMENTED;
}
#endif
