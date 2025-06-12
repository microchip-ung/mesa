// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_types.h"
#include "lan80xx_macsec_private.h"
#include "lan80xx_macsec.h"

static mepa_rc lan80xx_macsec_init_set(mepa_device_t *dev, const mepa_macsec_init_t *const init)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_init_set_priv(dev, init);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_init_get(mepa_device_t *dev, mepa_macsec_init_t *const init)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_init_get_priv(dev, init);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_is_capable(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_bool_t *capable)
{
    mepa_rc rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    *capable = lan80xx_phy_is_macsec_capable(dev);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_default_action_set(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_default_action_set_priv(dev, port_no, policy);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_default_action_get(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_default_action_get_priv(dev, port_no, policy);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_conf_add(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_conf_add_priv(dev, port, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_conf_get(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_conf_get_priv(dev, port, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_conf_del(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_conf_del_priv(dev, port);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_conf_update(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_conf_update_priv(dev, port, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_controlled_set(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_controlled_set_priv(dev, port, enable);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_controlled_get(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_bool_t *const enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_controlled_get_priv(dev, port, enable);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_pattern_set(mepa_device_t                      *dev,
                                          const mepa_macsec_port_t           port,
                                          const mepa_macsec_direction_t      direction,
                                          const mepa_macsec_match_action_t   action,
                                          const mepa_macsec_match_pattern_t  *const pattern)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_pattern_set_priv(dev, port, direction, action, pattern);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_pattern_get(mepa_device_t                      *dev,
                                          const mepa_macsec_port_t           port,
                                          const mepa_macsec_direction_t      direction,
                                          const mepa_macsec_match_action_t  action,
                                          mepa_macsec_match_pattern_t        *const pattern)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_pattern_get_priv(dev, port, direction, action, pattern);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_pattern_del(mepa_device_t                    *dev,
                                          const mepa_macsec_port_t           port,
                                          const mepa_macsec_direction_t      direction,
                                          const mepa_macsec_match_action_t   action)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_pattern_del_priv(dev, port, direction, action);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_set(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_set_priv(dev, port);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_update(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_update_priv(dev, port, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_del(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_del_priv(dev, port);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_status_get(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_status_get_priv(dev, port, status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_get_conf(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_get_conf_priv(dev, port, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_add(mepa_device_t *dev, const mepa_macsec_port_t  port, const mepa_macsec_sci_t  *const sci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_add_priv(dev, port, sci);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_update(mepa_device_t                  *dev,
                                           const mepa_macsec_port_t       port,
                                           const mepa_macsec_sci_t        *const sci,
                                           const mepa_macsec_rx_sc_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_update_priv(dev, port, sci, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_get_conf(mepa_device_t                  *dev,
                                             const mepa_macsec_port_t       port,
                                             const mepa_macsec_sci_t        *const sci,
                                             mepa_macsec_rx_sc_conf_t       *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_get_conf_priv(dev, port, sci, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_status_get(mepa_device_t *dev,
                                               const mepa_macsec_port_t        port,
                                               const mepa_macsec_sci_t         *const sci,
                                               mepa_macsec_rx_sc_status_t      *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_status_get_priv(dev, port, sci, status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_del(mepa_device_t *dev,
                                        const mepa_macsec_port_t    port,
                                        const mepa_macsec_sci_t     *const sci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_del_priv(dev, port, sci);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_macsec_tx_sa_set(mepa_device_t *dev,
                                        const mepa_macsec_port_t port,
                                        const u16          an,
                                        const u32          next_pn,
                                        const mepa_bool_t  confidentiality,
                                        const mepa_macsec_sak_t *const sak)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_set_priv(dev, port, an, next_pn, confidentiality, sak);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_get(mepa_device_t            *dev,
                                        const mepa_macsec_port_t port,
                                        const u16                an,
                                        u32 *const               next_pn,
                                        mepa_bool_t              *const confidentiality,
                                        mepa_macsec_sak_t        *const sak,
                                        mepa_bool_t              *const active)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_get_priv(dev, port, an, next_pn, confidentiality, sak, active);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_seca_set(mepa_device_t                *dev,
                                          const mepa_macsec_port_t     port,
                                          const u16                    an,
                                          const mepa_macsec_pkt_num_t  next_pn,
                                          const mepa_bool_t            confidentiality,
                                          const mepa_macsec_sak_t      *const sak,
                                          const mepa_macsec_ssci_t     *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_seca_set_priv(dev, port, an, next_pn, confidentiality, sak, ssci);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_macsec_tx_seca_get(mepa_device_t  *dev,
                                          const mepa_macsec_port_t  port,
                                          const u16                 an,
                                          mepa_macsec_pkt_num_t     *const next_pn,
                                          mepa_bool_t               *const confidentiality,
                                          mepa_macsec_sak_t         *const sak,
                                          mepa_bool_t               *const active,
                                          mepa_macsec_ssci_t        *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_seca_get_priv(dev, port, an, next_pn, confidentiality, sak, active, ssci);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_del(mepa_device_t  *dev,
                                        const mepa_macsec_port_t  port,
                                        const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_del_priv(dev, port, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_activate(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_activate_priv(dev, port, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_disable(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16  an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_disable_priv(dev, port, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_status_get(mepa_device_t  *dev,
                                               const mepa_macsec_port_t  port,
                                               const u16 an,
                                               mepa_macsec_tx_sa_status_t  *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_status_get_priv(dev, port, an, status);
    MEPA_EXIT(dev);
    return rc;
}


static mepa_rc lan80xx_macsec_rx_sa_set(mepa_device_t                 *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        const u32                     lowest_pn,
                                        const mepa_macsec_sak_t       *const sak)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_set_priv(dev, port, sci, an, lowest_pn, sak);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_get(mepa_device_t                 *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        u32                           *const lowest_pn,
                                        mepa_macsec_sak_t             *const sak,
                                        mepa_bool_t                   *const active)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_get_priv(dev, port, sci, an, lowest_pn, sak, active);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_seca_set(mepa_device_t *dev,
                                          const mepa_macsec_port_t      port,
                                          const mepa_macsec_sci_t       *const sci,
                                          const u16                     an,
                                          const mepa_macsec_pkt_num_t   lowest_pn,
                                          const mepa_macsec_sak_t       *const sak,
                                          const mepa_macsec_ssci_t      *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_seca_set_priv(dev, port, sci, an, lowest_pn, sak, ssci);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_seca_get(mepa_device_t  *dev,
                                          const mepa_macsec_port_t      port,
                                          const mepa_macsec_sci_t       *const sci,
                                          const u16                     an,
                                          mepa_macsec_pkt_num_t         *const lowest_pn,
                                          mepa_macsec_sak_t             *const sak,
                                          mepa_bool_t                   *const active,
                                          mepa_macsec_ssci_t            *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_seca_get_priv(dev, port, sci, an, lowest_pn, sak, active, ssci);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_activate(mepa_device_t  *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci, const u16 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_activate_priv(dev, port, sci, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_disable(mepa_device_t *dev,
                                            const mepa_macsec_port_t  port,
                                            const mepa_macsec_sci_t   *const sci,
                                            const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_disable_priv(dev, port, sci, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_del(mepa_device_t  *dev,
                                        const mepa_macsec_port_t  port,
                                        const mepa_macsec_sci_t   *const sci,
                                        const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_del_priv(dev, port, sci, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_status_get(mepa_device_t    *dev,
                                               const mepa_macsec_port_t    port,
                                               const mepa_macsec_sci_t     *const sci,
                                               const u16                   an,
                                               mepa_macsec_rx_sa_status_t  *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_status_get_priv(dev, port, sci, an, status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_lowest_pn_update(mepa_device_t  *dev,
                                                     const mepa_macsec_port_t     port,
                                                     const mepa_macsec_sci_t      *const sci,
                                                     const u16                    an,
                                                     const u32                    lowest_pn)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_lowest_pn_update_priv(dev, port, sci, an, lowest_pn);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rxsa_an_status_get (mepa_device_t             *dev,
                                                  const mepa_macsec_port_t  port,
                                                  const mepa_macsec_sci_t   *const sci,
                                                  const u16                 an,
                                                  mepa_bool_t               *status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rxsa_an_status_get_priv(dev, port, sci, an, status);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sa_counters_get(mepa_device_t                   *dev,
                                                 const mepa_macsec_port_t        port,
                                                 const u16                       an,
                                                 mepa_macsec_tx_sa_counters_t    *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sa_counters_get_priv(dev, port, an, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_tx_sc_counters_get(mepa_device_t                   *dev,
                                                 const mepa_macsec_port_t        port,
                                                 mepa_macsec_tx_sc_counters_t    *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_tx_sc_counters_get_priv(dev, port, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sc_counters_get(mepa_device_t                   *dev,
                                                 const mepa_macsec_port_t        port,
                                                 const mepa_macsec_sci_t         *const sci,
                                                 mepa_macsec_rx_sc_counters_t    *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sc_counters_get_priv(dev, port, sci, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rx_sa_counters_get(mepa_device_t                *dev,
                                                 const mepa_macsec_port_t     port,
                                                 const mepa_macsec_sci_t      *const sci,
                                                 const u16                    an,
                                                 mepa_macsec_rx_sa_counters_t *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rx_sa_counters_get_priv(dev, port, sci, an, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_txsc_counters_clear (mepa_device_t  *dev,
                                                   const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_txsc_counters_clear_priv(dev, port);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_txsa_counters_clear(mepa_device_t  *dev,
                                                  const mepa_macsec_port_t  port,
                                                  const u16  an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_txsa_counters_clear_priv(dev, port, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rxsc_counters_clear(mepa_device_t *dev,
                                                  const mepa_macsec_port_t  port,
                                                  const mepa_macsec_sci_t  *const sci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rxsc_counters_clear_priv(dev, port, sci);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_rxsa_counters_clear(mepa_device_t  *dev,
                                                  const mepa_macsec_port_t  port,
                                                  const mepa_macsec_sci_t  *const sci,
                                                  const u16  an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_rxsa_counters_clear_priv(dev, port, sci, an);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_counters_get(mepa_device_t                 *dev,
                                                const mepa_macsec_port_t      port,
                                                mepa_macsec_secy_counters_t   *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_counters_get_priv(dev, port, counters);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_controlled_counters_get(mepa_device_t                       *dev,
                                               const mepa_port_no_t                port_no,
                                               const mepa_macsec_port_t            port,
                                               mepa_macsec_secy_port_counters_t    *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_controlled_counters_get_priv(dev, port_no, port, counters);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_get(mepa_device_t                       *dev,
                                                 const mepa_port_no_t                port_no,
                                                 const mepa_macsec_port_t            port,
                                                 mepa_macsec_uncontrolled_counters_t *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_uncontrolled_counters_get_priv(dev, port_no, port, counters);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_common_counters_get(mepa_device_t                       *dev,
                                           const mepa_port_no_t                port_no,
                                           const mepa_macsec_port_t            port,
                                           mepa_macsec_common_counters_t       *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_common_counters_get_priv(dev, port_no, port, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_counters_update(mepa_device_t  *dev,
                                              const mepa_port_no_t  port_no)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_counters_update_priv(dev, port_no);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_counters_clear (mepa_device_t  *dev,
                                                   const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_counters_clear_priv(dev, port);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_clear (mepa_device_t  *dev,
                                                    const mepa_port_no_t      port_no,
                                                    const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_uncontrolled_counters_clear_priv(dev, port_no, port);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_controlled_counters_clear (mepa_device_t  *dev,
                                                  const mepa_port_no_t      port_no,
                                                  const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_controlled_counters_clear_priv(dev, port_no, port);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_common_counters_clear (mepa_device_t  *dev,
                                              const mepa_port_no_t      port_no,
                                              const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_common_counters_clear_priv(dev, port_no, port);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_lmac_counters_get(mepa_device_t               *dev,
                                                const mepa_port_no_t        port_no,
                                                mepa_macsec_mac_counters_t  *const counters,
                                                mepa_bool_t                 clear)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_lmac_counters_get_priv(dev, port_no, counters, clear);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_hmac_counters_get(mepa_device_t               *dev,
                                                const mepa_port_no_t        port_no,
                                                mepa_macsec_mac_counters_t  *const counters,
                                                mepa_bool_t                 clear)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_hmac_counters_get_priv(dev, port_no, counters, clear);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_lmac_counters_clear(mepa_device_t         *dev,
                                                  const mepa_port_no_t  port_no)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_lmac_counters_clear_priv(dev, port_no);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_hmac_counters_clear(mepa_device_t      *dev,
                                                  const mepa_port_no_t  port_no)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_hmac_counters_clear_priv(dev, port_no);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_debug_counters_clear(mepa_device_t          *dev,
                                                   const mepa_port_no_t   port_no)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_debug_counters_clear_priv(dev, port_no);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_csr_read(mepa_device_t               *dev,
                                       const mepa_port_no_t        port_no,
                                       const u16                   mmd,
                                       const u32                   addr,
                                       u32                         *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_csr_read_priv(dev, port_no, mmd, addr, value);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_csr_write(mepa_device_t               *dev,
                                        const mepa_port_no_t        port_no,
                                        const u32                   mmd,
                                        const u32                   addr,
                                        const u32                   value)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_csr_write_priv(dev, port_no, mmd, addr, value);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_mtu_set(mepa_device_t            *dev,
                                      const mepa_port_no_t     port_no,
                                      const mepa_macsec_mtu_t  *const mtu_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_mtu_set_priv(dev, port_no, mtu_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_mtu_get(mepa_device_t           *dev,
                                      const mepa_port_no_t    port_no,
                                      mepa_macsec_mtu_t       *mtu_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_mtu_get_priv(dev, port_no, mtu_conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_mac_block_mtu_set(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         const u16             mtu_value,
                                         const mepa_bool_t     mtu_tag_check)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_mac_block_mtu_set_priv(dev, port_no, mtu_value, mtu_tag_check);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_mac_block_mtu_get(mepa_device_t        *dev,
                                         const mepa_port_no_t port_no,
                                         u16                  *const mtu_value,
                                         mepa_bool_t          *const mtu_tag_check)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_mac_block_mtu_get_priv(dev, port_no, mtu_value, mtu_tag_check);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_dbg_update_seq_set(mepa_device_t             *dev,
                                                 const mepa_macsec_port_t  port,
                                                 const mepa_macsec_sci_t   *const sci,
                                                 u16                       an,
                                                 mepa_bool_t               egr,
                                                 const mepa_bool_t         disable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_dbg_update_seq_set_priv(dev, port, sci, an, egr, disable);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_frame_capture_set(mepa_device_t                       *dev,
                                                const mepa_port_no_t                port_no,
                                                const mepa_macsec_frame_capture_t   capture)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_frame_capture_set_priv(dev, port_no, capture);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_frame_get(mepa_device_t                 *dev,
                                        const mepa_port_no_t          port_no,
                                        const u32                     buf_length,
                                        u32                           *const frm_length,
                                        u8                            *const frame)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_frame_get_priv(dev, port_no, buf_length, frm_length, frame);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_seq_threshold_set(mepa_device_t         *dev,
                                                      const mepa_port_no_t  port_no,
                                                      const u32             threshold)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_seq_threshold_set_priv(dev, port_no, threshold);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_seq_threshold_get(mepa_device_t         *dev,
                                                      const mepa_port_no_t  port_no,
                                                      u32                   *const threshold)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_seq_threshold_get_priv(dev, port_no, threshold);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_xpn_seq_threshold_set(mepa_device_t         *dev,
                                                          const mepa_port_no_t  port_no,
                                                          const u64             threshold)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_xpn_seq_threshold_set_priv(dev, port_no, threshold);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_xpn_seq_threshold_get(mepa_device_t         *dev,
                                                          const mepa_port_no_t  port_no,
                                                          u64                   *const threshold)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_xpn_seq_threshold_get_priv(dev, port_no, threshold);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_secy_cap_get(mepa_device_t                 *dev,
                                           const mepa_port_no_t          port_no,
                                           mepa_macsec_secy_cap_t        *const cap)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_secy_cap_get_priv(dev, port_no, cap);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_enable_set(mepa_device_t        *dev,
                                               const mepa_port_no_t        port_no,
                                               const mepa_macsec_event_t   ev_mask,
                                               const mepa_bool_t           enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_enable_set_priv(dev, port_no, ev_mask, enable);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_enable_get(mepa_device_t    *dev,
                                               const mepa_port_no_t   port_no,
                                               mepa_macsec_event_t    *const ev_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_enable_get_priv(dev, port_no, ev_mask);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_event_poll(mepa_device_t         *dev,
                                         const mepa_port_no_t  port_no,
                                         mepa_macsec_event_t  *const ev_mask)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_event_poll_priv(dev, port_no, ev_mask);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_port_get_next(mepa_device_t               *dev,
                                            const mepa_port_no_t        port_no,
                                            const mepa_macsec_port_t    *const search_macsec_port,
                                            mepa_macsec_port_t          *const found_macsec_port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_port_get_next_priv(dev, port_no, search_macsec_port, found_macsec_port);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_egr_policy_mode_set(mepa_device_t                   *dev,
                                           const mepa_port_no_t            port_no,
                                           const phy25g_macsec_egr_mode_t  egr_policy_mode,
                                           const mepa_etype_t              hdr_eth_type)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_egr_policy_mode_set_priv(dev, port_no, egr_policy_mode, hdr_eth_type);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_egr_policy_mode_get(mepa_device_t             *dev,
                                           const mepa_port_no_t      port_no,
                                           phy25g_macsec_egr_mode_t  egr_policy_mode)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_egr_policy_mode_get_priv(dev, port_no, egr_policy_mode);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_bypass_mode_set(mepa_device_t                    *dev,
                                              const mepa_port_no_t             port_no,
                                              const mepa_macsec_bypass_mode_t  *const bypass)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_bypass_mode_set_priv(dev, port_no, bypass);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_bypass_mode_get(mepa_device_t              *dev,
                                              const mepa_port_no_t       port_no,
                                              mepa_macsec_bypass_mode_t  *const bypass)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_bypass_mode_get_priv(dev, port_no, bypass);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_bypass_tag_set(mepa_device_t                     *dev,
                                             const mepa_macsec_port_t          port,
                                             const mepa_macsec_tag_bypass_t    tag)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_bypass_tag_set_priv(dev, port, tag);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_bypass_tag_get(mepa_device_t                 *dev,
                                             const mepa_macsec_port_t      port,
                                             mepa_macsec_tag_bypass_t      *const tag)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_bypass_tag_get_priv(dev, port, tag);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_cleartags_conf_set(mepa_device_t                         *dev,
                                          const mepa_port_no_t                  port_no,
                                          const mepa_bool_t                     enable,
                                          const phy25g_macsec_cleartags_conf_t  *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_cleartags_conf_set_priv(dev, port_no, enable, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_control_frame_match_conf_set(mepa_device_t                                 *dev,
                                                           const mepa_port_no_t                          port_no,
                                                           const mepa_macsec_control_frame_match_conf_t *const conf,
                                                           u32                                          *const rule_id)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_control_frame_match_conf_set_priv(dev, port_no, conf, rule_id);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_control_frame_match_conf_del(mepa_device_t             *dev,
                                                           const mepa_port_no_t      port_no,
                                                           const u32                 rule_id)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_control_frame_match_conf_del_priv(dev, port_no, rule_id);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_control_frame_match_conf_get(mepa_device_t                              *dev,
                                                           const mepa_port_no_t                       port_no,
                                                           mepa_macsec_control_frame_match_conf_t     *const conf,
                                                           u32                                        rule_id)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_control_frame_match_conf_get_priv(dev, port_no, conf, rule_id);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_macsec_cleartags_conf_get(mepa_device_t                      *dev,
                                          const mepa_port_no_t               port_no,
                                          mepa_bool_t                        enable,
                                          phy25g_macsec_cleartags_conf_t     *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\nPort instance not created in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (!lan80xx_driver_check(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "\nAPI not supported for PHY in port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_cleartags_conf_get_priv(dev, port_no, enable, conf);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_inst_count_get(mepa_device_t             *dev,
                                             const mepa_port_no_t      port_no,
                                             mepa_macsec_inst_count_t  *counts)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_inst_count_get_priv(dev, port_no, counts);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_dbg_reg_dump(mepa_device_t     *dev,
                                           mepa_port_no_t     port_no,
                                           mepa_debug_print_t pr)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_dbg_reg_dump_priv(dev, port_no, pr);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_dbg_counter_get(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_dbg_counter_get_priv(dev, port_no, counters);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_macsec_port_enable_status_get(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_bool_t  *status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    MEPA_ENTER(dev);
    rc = lan80xx_macsec_port_enable_status_get_priv(dev, port_no, status);
    MEPA_EXIT(dev);
    return rc;
}


/*MEPA macsec driver*/
mepa_macsec_driver_t lan80xx_macsec_drivers = {
    .mepa_macsec_init_set                     = lan80xx_macsec_init_set,
    .mepa_macsec_init_get                     = lan80xx_macsec_init_get,
    .mepa_macsec_is_capable                   = lan80xx_macsec_is_capable,
    .mepa_macsec_default_action_set           = lan80xx_macsec_default_action_set,
    .mepa_macsec_default_action_get           = lan80xx_macsec_default_action_get,
    .mepa_macsec_secy_conf_add                = lan80xx_macsec_secy_conf_add,
    .mepa_macsec_secy_conf_get                = lan80xx_macsec_secy_conf_get,
    .mepa_macsec_secy_conf_del                = lan80xx_macsec_secy_conf_del,
    .mepa_macsec_secy_conf_update             = lan80xx_macsec_secy_conf_update,
    .mepa_macsec_secy_controlled_set          = lan80xx_macsec_secy_controlled_set,
    .mepa_macsec_secy_controlled_get          = lan80xx_macsec_secy_controlled_get,
    .mepa_macsec_pattern_set                  = lan80xx_macsec_pattern_set,
    .mepa_macsec_pattern_get                  = lan80xx_macsec_pattern_get,
    .mepa_macsec_pattern_del                  = lan80xx_macsec_pattern_del,
    .mepa_macsec_tx_sc_set                    = lan80xx_macsec_tx_sc_set,
    .mepa_macsec_tx_sc_update                 = lan80xx_macsec_tx_sc_update,
    .mepa_macsec_tx_sc_del                    = lan80xx_macsec_tx_sc_del,
    .mepa_macsec_tx_sc_status_get             = lan80xx_macsec_tx_sc_status_get,
    .mepa_macsec_tx_sc_get_conf               = lan80xx_macsec_tx_sc_get_conf,
    .mepa_macsec_rx_sc_add                    = lan80xx_macsec_rx_sc_add,
    .mepa_macsec_rx_sc_update                 = lan80xx_macsec_rx_sc_update,
    .mepa_macsec_rx_sc_get_conf               = lan80xx_macsec_rx_sc_get_conf,
    .mepa_macsec_rx_sc_status_get             = lan80xx_macsec_rx_sc_status_get,
    .mepa_macsec_rx_sc_del                    = lan80xx_macsec_rx_sc_del,
    .mepa_macsec_tx_sa_set                    = lan80xx_macsec_tx_sa_set,
    .mepa_macsec_tx_sa_get                    = lan80xx_macsec_tx_sa_get,
    .mepa_macsec_tx_sa_del                    = lan80xx_macsec_tx_sa_del,
    .mepa_macsec_tx_sa_activate               = lan80xx_macsec_tx_sa_activate,
    .mepa_macsec_tx_sa_disable                = lan80xx_macsec_tx_sa_disable,
    .mepa_macsec_tx_sa_status_get             = lan80xx_macsec_tx_sa_status_get,
    .mepa_macsec_tx_seca_set                  = lan80xx_macsec_tx_seca_set,
    .mepa_macsec_tx_seca_get                  = lan80xx_macsec_tx_seca_get,
    .mepa_macsec_rx_sa_set                    = lan80xx_macsec_rx_sa_set,
    .mepa_macsec_rx_sa_get                    = lan80xx_macsec_rx_sa_get,
    .mepa_macsec_rx_sa_activate               = lan80xx_macsec_rx_sa_activate,
    .mepa_macsec_rx_sa_disable                = lan80xx_macsec_rx_sa_disable,
    .mepa_macsec_rx_sa_del                    = lan80xx_macsec_rx_sa_del,
    .mepa_macsec_rx_sa_status_get             = lan80xx_macsec_rx_sa_status_get,
    .mepa_macsec_rx_seca_set                  = lan80xx_macsec_rx_seca_set,
    .mepa_macsec_rx_seca_get                  = lan80xx_macsec_rx_seca_get,
    .mepa_macsec_rx_sa_lowest_pn_update       = lan80xx_macsec_rx_sa_lowest_pn_update,
    .mepa_macsec_rxsa_an_status_get           = lan80xx_macsec_rxsa_an_status_get,
    .mepa_macsec_port_enable_status_get       = lan80xx_macsec_port_enable_status_get,
    .mepa_macsec_secy_counters_get            = lan80xx_macsec_secy_counters_get,
    .mepa_macsec_tx_sa_counters_get           = lan80xx_macsec_tx_sa_counters_get,
    .mepa_macsec_tx_sc_counters_get           = lan80xx_macsec_tx_sc_counters_get,
    .mepa_macsec_rx_sa_counters_get           = lan80xx_macsec_rx_sa_counters_get,
    .mepa_macsec_rx_sc_counters_get           = lan80xx_macsec_rx_sc_counters_get,
    .mepa_macsec_uncontrolled_counters_get    = NULL,
    .mepa_macsec_uncontrolled_counters_clear  = NULL,
    .mepa_macsec_common_counters_get          = NULL,
    .mepa_macsec_common_counters_clear        = NULL,
    .mepa_macsec_controlled_counters_get      = NULL,
    .mepa_macsec_controlled_counters_clear    = NULL,
    .mepa_macsec_txsc_counters_clear          = lan80xx_macsec_txsc_counters_clear,
    .mepa_macsec_txsa_counters_clear          = lan80xx_macsec_txsa_counters_clear,
    .mepa_macsec_rxsc_counters_clear          = lan80xx_macsec_rxsc_counters_clear,
    .mepa_macsec_rxsa_counters_clear          = lan80xx_macsec_rxsa_counters_clear,
    .mepa_macsec_secy_counters_clear          = lan80xx_macsec_secy_counters_clear,
    .mepa_macsec_counters_update              = lan80xx_macsec_counters_update,
    .mepa_macsec_lmac_counters_get            = lan80xx_macsec_lmac_counters_get,
    .mepa_macsec_hmac_counters_get            = lan80xx_macsec_hmac_counters_get,
    .mepa_macsec_lmac_counters_clear          = lan80xx_macsec_lmac_counters_clear,
    .mepa_macsec_hmac_counters_clear          = lan80xx_macsec_hmac_counters_clear,
    .mepa_macsec_csr_read                     = lan80xx_macsec_csr_read,
    .mepa_macsec_csr_write                    = lan80xx_macsec_csr_write,
    .mepa_macsec_mtu_set                      = lan80xx_macsec_mtu_set,
    .mepa_macsec_mtu_get                      = lan80xx_macsec_mtu_get,
    .mepa_mac_block_mtu_set                   = lan80xx_mac_block_mtu_set,
    .mepa_mac_block_mtu_get                   = lan80xx_mac_block_mtu_get,
    .mepa_macsec_frame_capture_set            = lan80xx_macsec_frame_capture_set,
    .mepa_macsec_frame_get                    = lan80xx_macsec_frame_get,
    .mepa_macsec_event_seq_threshold_set      = lan80xx_macsec_event_seq_threshold_set,
    .mepa_macsec_event_seq_threshold_get      = lan80xx_macsec_event_seq_threshold_get,
    .mepa_macsec_event_xpn_seq_threshold_set  = lan80xx_macsec_event_xpn_seq_threshold_set,
    .mepa_macsec_event_xpn_seq_threshold_get  = lan80xx_macsec_event_xpn_seq_threshold_get,
    .mepa_macsec_control_frame_match_conf_set = lan80xx_macsec_control_frame_match_conf_set,
    .mepa_macsec_control_frame_match_conf_del = lan80xx_macsec_control_frame_match_conf_del,
    .mepa_macsec_control_frame_match_conf_get = lan80xx_macsec_control_frame_match_conf_get,
    .mepa_macsec_secy_cap_get                 = lan80xx_macsec_secy_cap_get,
    .mepa_macsec_event_enable_set             = lan80xx_macsec_event_enable_set,
    .mepa_macsec_event_enable_get             = lan80xx_macsec_event_enable_get,
    .mepa_macsec_event_poll                   = lan80xx_macsec_event_poll,
    .mepa_macsec_port_get_next                = lan80xx_macsec_port_get_next,
    .mepa_macsec_bypass_mode_set              = lan80xx_macsec_bypass_mode_set,
    .mepa_macsec_bypass_mode_get              = lan80xx_macsec_bypass_mode_get,
    .mepa_macsec_bypass_tag_set               = lan80xx_macsec_bypass_tag_set,
    .mepa_macsec_bypass_tag_get               = lan80xx_macsec_bypass_tag_get,
    .mepa_macsec_inst_count_get               = lan80xx_macsec_inst_count_get,
    .mepa_macsec_dbg_counter_get              = lan80xx_macsec_dbg_counter_get,
    .mepa_macsec_debug_counters_clear         = lan80xx_macsec_debug_counters_clear,
    .mepa_macsec_dbg_reg_dump                 = lan80xx_macsec_dbg_reg_dump,
    .mepa_macsec_dbg_update_seq_set           = lan80xx_macsec_dbg_update_seq_set,
};
