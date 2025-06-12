// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <mepa_driver.h>
#include <lan867x_private.h>

// LAN867X Driver MEPA T1S APIs.

static mepa_rc lan867x_t1s_set_plca_config(struct mepa_device *dev,
                                                 const mepa_t1s_plca_cfg_t cfg)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *pdata = dev->data;

    MEPA_ENTER(dev);

    MEPA_RC(rc, lan867x_init_conf(dev, cfg));
    (void)memcpy(&pdata->t1s_cfg.plca_cfg, &cfg, sizeof(mepa_t1s_plca_cfg_t));

error:
    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan867x_t1s_get_plca_config(struct mepa_device *dev,
                                                 mepa_t1s_plca_cfg_t *const cfg)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *pdata = dev->data;

    MEPA_ENTER(dev);

    (void)memcpy(cfg, &pdata->t1s_cfg.plca_cfg, sizeof(mepa_t1s_plca_cfg_t));

    MEPA_EXIT(dev);

    return rc;
}

mepa_t1s_driver_t lan867x_t1s_driver = {
    .mepa_t1s_set_plca_config = lan867x_t1s_set_plca_config,
    .mepa_t1s_get_plca_config = lan867x_t1s_get_plca_config,
};
