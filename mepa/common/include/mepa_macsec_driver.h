// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_MACSEC_DRV_API_H_
#define _MEPA_MACSEC_DRV_API_H_

#include <microchip/ethernet/phy/api.h>

typedef mepa_rc (*mepa_macsec_init_set_t)(struct mepa_device *dev, const mepa_macsec_init_t *const macsec_init);
typedef mepa_rc (*mepa_macsec_init_get_t)(struct mepa_device *dev, mepa_macsec_init_t *const macsec_init);
typedef mepa_rc (*mepa_macsec_secy_conf_add_t)(struct mepa_device *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf);

/** \brief PHY MACsec Driver */
typedef struct mepa_macsec_driver {
    mepa_macsec_init_set_t mepa_macsec_init_set;
    mepa_macsec_init_get_t mepa_macsec_init_get;
    mepa_macsec_secy_conf_add_t mepa_macsec_secy_conf_add;

} mepa_macsec_driver_t;

#endif
