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

mepa_macsec_driver_t vtss_macsec_drivers = {
    .mepa_macsec_init_set = vtss_phy_macsec_init_set,
    .mepa_macsec_init_get = vtss_phy_macsec_init_get,
    .mepa_macsec_secy_conf_add = vtss_phy_macsec_secy_conf_add,

};
