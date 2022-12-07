// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_MACSEC_DRV_API_H_
#define _MEPA_MACSEC_DRV_API_H_

#include <microchip/ethernet/phy/api.h>

typedef mepa_rc (*mepa_macsec_init_set_t)(struct mepa_device *dev, const mepa_macsec_init_t *const macsec_init);
typedef mepa_rc (*mepa_macsec_init_get_t)(struct mepa_device *dev, mepa_macsec_init_t *const macsec_init);
typedef mepa_rc (*mepa_macsec_secy_conf_add_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);
typedef mepa_rc (*mepa_macsec_secy_conf_update_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);
typedef mepa_rc (*mepa_macsec_secy_conf_get_t)(struct mepa_device *dev, const mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf);
typedef mepa_rc (*mepa_macsec_secy_conf_del_t)(struct mepa_device *dev, const mepa_macsec_port_t port);
typedef mepa_rc (*mepa_macsec_secy_controlled_set_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_bool_t enable);
typedef mepa_rc (*mepa_macsec_secy_controlled_get_t)(struct mepa_device *dev, const mepa_macsec_port_t port, mepa_bool_t *const enable);
typedef mepa_rc (*mepa_macsec_secy_port_status_get_t)(struct mepa_device *dev, const mepa_macsec_port_t port, mepa_macsec_secy_port_status_t *const status);
typedef mepa_rc (*mepa_macsec_port_get_next_t)(struct mepa_device *dev, const mepa_port_no_t port_no, const mepa_macsec_port_t *const search_macsec_port, mepa_macsec_port_t *const found_macsec_port);
typedef mepa_rc (*mepa_macsec_rx_sc_add_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci);
typedef mepa_rc (*mepa_macsec_rx_sc_update_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, const mepa_macsec_rx_sc_conf_t *const conf);
typedef mepa_rc (*mepa_macsec_rx_sc_get_conf_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t *const sci, mepa_macsec_rx_sc_conf_t *const conf);

/** \brief PHY MACsec Driver */
typedef struct mepa_macsec_driver {
    mepa_macsec_init_set_t mepa_macsec_init_set;
    mepa_macsec_init_get_t mepa_macsec_init_get;
    mepa_macsec_secy_conf_add_t mepa_macsec_secy_conf_add;
    mepa_macsec_secy_conf_update_t mepa_macsec_secy_conf_update;
    mepa_macsec_secy_conf_get_t mepa_macsec_secy_conf_get;
    mepa_macsec_secy_conf_del_t mepa_macsec_secy_conf_del;
    mepa_macsec_secy_controlled_set_t mepa_macsec_secy_controlled_set;
    mepa_macsec_secy_controlled_get_t mepa_macsec_secy_controlled_get;
    mepa_macsec_secy_port_status_get_t mepa_macsec_secy_port_status_get;
    mepa_macsec_port_get_next_t mepa_macsec_port_get_next;
    mepa_macsec_rx_sc_add_t mepa_macsec_rx_sc_add;
    mepa_macsec_rx_sc_update_t mepa_macsec_rx_sc_update;
    mepa_macsec_rx_sc_get_conf_t mepa_macsec_rx_sc_get_conf;

} mepa_macsec_driver_t;

#endif
