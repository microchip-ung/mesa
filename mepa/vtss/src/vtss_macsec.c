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

};
