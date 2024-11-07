// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>

#define MEBA_PORT_CAP_10M_HDX           0x000000002
#define MEBA_PORT_CAP_10M_FDX           0x000000004
#define MEBA_PORT_CAP_100M_HDX          0x000000008
#define MEBA_PORT_CAP_100M_FDX          0x000000010
#define MEBA_PORT_CAP_1G_FDX            0x000000020
#define MEBA_PORT_CAP_2_5G_FDX          0x000000040

typedef struct {
    u32 cap;
} priv_data_t;

static mepa_rc dummy_1g_poll(mepa_device_t *dev,
                            mepa_status_t *status)
{
    priv_data_t *priv;
    priv = dev->data;

    status->link = 1;
    status->speed = (priv->cap & MEBA_PORT_CAP_2_5G_FDX) ?  MESA_SPEED_2500M
        : (priv->cap & MEBA_PORT_CAP_1G_FDX) ? MESA_SPEED_1G
        : (priv->cap & MEBA_PORT_CAP_100M_FDX) ? MESA_SPEED_100M : MESA_SPEED_10M;
    status->fdx = 1;

    return MEPA_RC_OK;
}

static mepa_rc dummy_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    return MEPA_RC_OK;
}

static mepa_rc dummy_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_info->cap = 0;
    phy_info->part_number = 1234;
    phy_info->revision = 5678;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_10G;
    return MEPA_RC_OK;
}

static mepa_device_t *dummy_probe(mepa_driver_t                       *drv,
                                const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                struct mepa_board_conf              *board_conf)
{
    priv_data_t *priv;
    mepa_device_t *dev;

    dev = mepa_create_int(drv, callout, callout_ctx, board_conf, sizeof(priv_data_t));
    if (!dev) {
        return 0;
    }

    priv = dev->data;
    priv->cap = board_conf->dummy_phy_cap;

    return dev;
}

mepa_drivers_t mepa_dummy_driver_init()
{
    mepa_drivers_t res;
    static mepa_driver_t dummy[1] = {};

    dummy[0].id = 0xdeadbeef;
    dummy[0].mask = 0xffffffff;
    dummy[0].mepa_driver_poll = dummy_1g_poll;
    dummy[0].mepa_driver_conf_set = dummy_conf_set;
    dummy[0].mepa_driver_probe = dummy_probe;
    dummy[0].mepa_driver_phy_info_get = dummy_info_get,
    res.phy_drv = dummy;
    res.count = 1;

    return res;
}
