// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan8770_private.h"

// LAN8770 Driver MEPA TC10 APIs

static mepa_rc lan8770_tc10_set_sleep_support(struct mepa_device        *dev,
                                              const mepa_bool_t         enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_set_sleep_support(dev, enable);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_sleep_support(struct mepa_device    *dev,
                                              mepa_bool_t           *const enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_sleep_support(dev, enable);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_set_wakeup_support(struct mepa_device               *dev,
                                               const mepa_tc10_wakeup_mode_t    mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_set_wakeup_support(dev, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_wakeup_support(struct mepa_device           *dev,
                                               mepa_tc10_wakeup_mode_t      *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_wakeup_support(dev, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_set_wakeup_fwd_support(struct mepa_device                       *dev,
                                                   const mepa_tc10_wakeup_fwd_mode_t        mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_set_wakeup_fwd_support(dev, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_wakeup_fwd_support(struct mepa_device              *dev,
                                                   mepa_tc10_wakeup_fwd_mode_t     *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_wakeup_fwd_support(dev, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_set_wake_pin_polarity(struct mepa_device            *dev,
                                                  const mepa_tc10_pin_t         pin,
                                                  const mepa_gpio_mode_t        polarity)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_set_wake_pin_polarity(dev, pin, polarity);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_wake_pin_polarity(struct mepa_device            *dev,
                                                  const mepa_tc10_pin_t         pin,
                                                  mepa_gpio_mode_t              *const polarity)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_wake_pin_polarity(dev, pin, polarity);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_set_pin_mode(struct mepa_device         *dev,
                                         const mepa_tc10_pin_t      pin,
                                         const mepa_gpio_mode_t     mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_set_pin_mode(dev, pin, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_pin_mode(struct mepa_device         *dev,
                                         const mepa_tc10_pin_t      pin,
                                         mepa_gpio_mode_t           *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_pin_mode(dev, pin, mode);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_send_sleep_request(struct mepa_device                       *dev,
                                               const mepa_tc10_sleep_request_t          req)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_send_sleep_request(dev, req);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_get_state(struct mepa_device        *dev,
                                      mepa_tc10_state_t         *const state)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_get_state(dev, state);

    MEPA_EXIT(dev);

    return rc;
}

static mepa_rc lan8770_tc10_send_wake_request(struct mepa_device *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_ENTER(dev);

    rc = phy_tc10_send_wake_request(dev);

    MEPA_EXIT(dev);

    return rc;
}

mepa_tc10_driver_t lan8770_tc10_drivers = {
    .mepa_tc10_set_sleep_support           = lan8770_tc10_set_sleep_support,
    .mepa_tc10_get_sleep_support           = lan8770_tc10_get_sleep_support,
    .mepa_tc10_set_wakeup_support          = lan8770_tc10_set_wakeup_support,
    .mepa_tc10_get_wakeup_support          = lan8770_tc10_get_wakeup_support,
    .mepa_tc10_set_wakeup_fwd_support      = lan8770_tc10_set_wakeup_fwd_support,
    .mepa_tc10_get_wakeup_fwd_support      = lan8770_tc10_get_wakeup_fwd_support,
    .mepa_tc10_set_wake_pin_polarity       = lan8770_tc10_set_wake_pin_polarity,
    .mepa_tc10_get_wake_pin_polarity       = lan8770_tc10_get_wake_pin_polarity,
    .mepa_tc10_set_pin_mode                = lan8770_tc10_set_pin_mode,
    .mepa_tc10_get_pin_mode                = lan8770_tc10_get_pin_mode,
    .mepa_tc10_send_sleep_request          = lan8770_tc10_send_sleep_request,
    .mepa_tc10_get_state                   = lan8770_tc10_get_state,
    .mepa_tc10_send_wake_request           = lan8770_tc10_send_wake_request,
};
