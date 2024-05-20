// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan887x_private.h"

/**********************************
 * Internal APIs
 *********************************/
// LAN887X Driver MEPA TC10 APIs
static mepa_rc lan887x_phy_tc10_set_sleep_support(struct mepa_device        *dev,
                                                  const mepa_bool_t         enable)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, &reg_data));

    if (enable) {
        reg_data |= LAN887X_DEV30_COMMON_TC10_MISC32_SLEEP_EN;
    } else {
        reg_data &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_SLEEP_EN)) & 0xFFFFU;
    }

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, reg_data));

    data->tc10_cfg.sleep_enable = enable;

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_sleep_support(struct mepa_device    *dev,
                                                  mepa_bool_t           *const enable)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *enable = data->tc10_cfg.sleep_enable;

    return MEPA_RC_OK;
}

static mepa_rc lan887x_phy_tc10_set_wakeup_support(struct mepa_device               *dev,
                                                   const mepa_tc10_wakeup_mode_t    mode)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t reg_data1 = 0, reg_data2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36, &reg_data1));
    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, &reg_data2));

    switch (mode) {
    case MEPA_TC10_WAKEUP_DISABLE: {
        reg_data1 &= (~(LAN887X_DEV30_COMMON_TC10_MISC36_WK_MDI_EN)) & 0xFFFFU;
        reg_data2 &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_EN)) & 0xFFFFU;
    }
    break;
    case MEPA_TC10_WAKEUP_WUP_ENABLE: {
        reg_data1 |= LAN887X_DEV30_COMMON_TC10_MISC36_WK_MDI_EN;
        reg_data2 &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_EN)) & 0xFFFFU;
    }
    break;
    case MEPA_TC10_WAKEUP_WAKEIN_ENABLE: {
        reg_data1 &= (~(LAN887X_DEV30_COMMON_TC10_MISC36_WK_MDI_EN)) & 0xFFFFU;
        reg_data2 |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_EN;
    }
    break;
    default: {
        reg_data1 |= LAN887X_DEV30_COMMON_TC10_MISC36_WK_MDI_EN;
        reg_data2 |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_EN;
    }
    break;
    }

    reg_data1 |= (LAN887X_DEV30_COMMON_TC10_MISC36_VBAT_PORT_WR);
    reg_data2 |= (LAN887X_DEV30_COMMON_TC10_MISC32_VBAT_COM_WR);

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36, reg_data1));
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, reg_data2));

    data->tc10_cfg.wakeup_mode = mode;

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_wakeup_support(struct mepa_device           *dev,
                                                   mepa_tc10_wakeup_mode_t      *const mode)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *mode = data->tc10_cfg.wakeup_mode;

    return MEPA_RC_OK;
}

static mepa_rc lan887x_phy_tc10_set_wakeup_fwd_support(struct mepa_device                       *dev,
                                                       const mepa_tc10_wakeup_fwd_mode_t        mode)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t reg_data1 = 0, reg_data2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36, &reg_data1));
    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, &reg_data2));

    switch (mode) {
    case MEPA_TC10_WAKEUP_FWD_DISABLE: {
        reg_data1 &= (~(LAN887X_DEV30_COMMON_TC10_MISC36_WUP_AUTO_FWD_EN) & 0xFFFFU);
        reg_data2 &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_AUTO_FWD_EN) & 0xFFFFU);
    }
    break;
    case  MEPA_TC10_WAKEUP_FWD_WUP_ENABLE: {
        reg_data1 |= LAN887X_DEV30_COMMON_TC10_MISC36_WUP_AUTO_FWD_EN;
        reg_data2 &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_AUTO_FWD_EN) & 0xFFFFU);
    }
    break;
    case  MEPA_TC10_WAKEUP_FWD_WAKEOUT_ENABLE: {
        reg_data1 &= (~(LAN887X_DEV30_COMMON_TC10_MISC36_WUP_AUTO_FWD_EN) & 0xFFFFU);
        reg_data2 |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_AUTO_FWD_EN;
    }
    break;
    default: {
        reg_data1 |= LAN887X_DEV30_COMMON_TC10_MISC36_WUP_AUTO_FWD_EN;
        reg_data2 |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_AUTO_FWD_EN;
    }
    break;
    }

    reg_data1 |= (LAN887X_DEV30_COMMON_TC10_MISC36_VBAT_PORT_WR);
    reg_data2 |= (LAN887X_DEV30_COMMON_TC10_MISC32_VBAT_COM_WR);

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36, reg_data1));
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, reg_data2));

    data->tc10_cfg.wakeup_fwd_mode = mode;

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_wakeup_fwd_support(struct mepa_device              *dev,
                                                       mepa_tc10_wakeup_fwd_mode_t     *const mode)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *mode = data->tc10_cfg.wakeup_fwd_mode;

    return MEPA_RC_OK;
}

static mepa_rc lan887x_phy_tc10_set_wake_pin_polarity(struct mepa_device           *dev,
                                                      const mepa_tc10_pin_t        pin,
                                                      const mepa_gpio_mode_t       polarity)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, &reg_data));

    switch (pin) {
    case MEPA_TC10_WAKE_IN: {
        if (polarity == MEPA_GPIO_MODE_ACTIVE_LOW) {
            reg_data &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_POL)) & 0xFFFFU;
        } else if (polarity == MEPA_GPIO_MODE_ACTIVE_HIGH) {
            reg_data |= (LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_POL);
        } else {
            rc = MEPA_RC_ERR_PARM;
            goto error;
        }
    }
    break;
    case MEPA_TC10_WAKE_OUT: {
        if (polarity == MEPA_GPIO_MODE_ACTIVE_LOW) {
            reg_data &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_POL)) & 0xFFFFU;
        } else if (polarity == MEPA_GPIO_MODE_ACTIVE_HIGH) {
            reg_data |= (LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_POL);
        } else {
            rc = MEPA_RC_ERR_PARM;
            goto error;
        }
    }
    break;
    default: {
        rc = MEPA_RC_ERR_PARM;
        break;
    }
    }

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, reg_data));

    if (pin == MEPA_TC10_WAKE_IN) {
        data->tc10_cfg.wake_in_pol = polarity;
    } else if (pin == MEPA_TC10_WAKE_OUT) {
        data->tc10_cfg.wake_out_pol = polarity;
    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_wake_pin_polarity(struct mepa_device            *dev,
                                                      const mepa_tc10_pin_t         pin,
                                                      mepa_gpio_mode_t              *const polarity)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    if (pin == MEPA_TC10_WAKE_IN) {
        *polarity = data->tc10_cfg.wake_in_pol;
    } else if (pin == MEPA_TC10_WAKE_OUT) {
        *polarity = data->tc10_cfg.wake_out_pol;
    } else {
        return MEPA_RC_ERR_PARM;
    }

    return MEPA_RC_OK;
}

static mepa_rc lan887x_phy_tc10_set_pin_mode(struct mepa_device          *dev,
                                             const mepa_tc10_pin_t       pin,
                                             const mepa_gpio_mode_t      mode)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, &reg_data));

    switch (pin) {
    case MEPA_TC10_WAKE_OUT: {
        /* clearing wakeout mode bits */
        reg_data &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_SET(3U)) & 0xFFFFU);
        if (mode == MEPA_GPIO_MODE_PUSH_PULL) {
            reg_data |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_SET(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_PUSH_PULL);
        } else if (mode == MEPA_GPIO_MODE_OPEN_SOURCE) {
            reg_data |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_SET(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_OPEN_SOURCE);
        } else if (mode == MEPA_GPIO_MODE_OPEN_DRAIN) {
            reg_data |= LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_SET(LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_OPEN_DRAIN);
        } else {
            rc = MEPA_RC_ERR_PARM;
            goto error;
        }
    }
    break;
    case MEPA_TC10_INH: {
        if (mode == MEPA_GPIO_MODE_OPEN_SOURCE) {
            reg_data &= (~(LAN887X_DEV30_COMMON_TC10_MISC32_INH_MODE_OPEN_DRAIN) & 0xFFFFU);
        } else if (mode == MEPA_GPIO_MODE_OPEN_DRAIN) {
            reg_data |= (LAN887X_DEV30_COMMON_TC10_MISC32_INH_MODE_OPEN_DRAIN);
        } else {
            rc = MEPA_RC_ERR_PARM;
            goto error;
        }
    }
    break;
    default: {
        rc = MEPA_RC_ERR_PARM;
        break;
    }
    }

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32, reg_data));

    if (pin == MEPA_TC10_INH) {
        data->tc10_cfg.inh_mode = mode;
    } else if (pin == MEPA_TC10_WAKE_OUT) {
        data->tc10_cfg.wake_out_mode = mode;
    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_pin_mode(struct mepa_device          *dev,
                                             const mepa_tc10_pin_t       pin,
                                             mepa_gpio_mode_t            *const mode)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    switch (pin) {
    case MEPA_TC10_INH: {
        *mode = data->tc10_cfg.inh_mode;
    }
    break;
    case MEPA_TC10_WAKE_OUT: {
        *mode = data->tc10_cfg.wake_out_mode;
    }
    break;
    default: {
        rc = MEPA_RC_ERR_PARM;
    }
    break;
    }

    return rc;
}

static mepa_rc lan887x_phy_tc10_send_sleep_request(struct mepa_device                *dev,
                                                   const mepa_tc10_sleep_request_t   req)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERR_PARM;

    if (req == MEPA_TC10_LPS) {
        rc = MEPA_RC_OK;
        MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                                        LAN887X_DEV30_COMMON_TC10_REG_REG16, &reg_data));
        reg_data |= LAN887X_DEV30_COMMON_TC10_REG_REG16_RW_SEND_LPS;
        MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                        LAN887X_DEV30_COMMON_TC10_REG_REG16, reg_data));
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_get_state(struct mepa_device     *dev,
                                          mepa_tc10_state_t      *const state)
{
    uint16_t reg_data = 0, sts = 0;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_TC10_DEV30_COMMON_MISC34, &reg_data));

    sts = LAN887X_STS_TC10_STATE_GET(reg_data);
    switch (sts) {
    case LAN887X_STS_TC10_STATE_START: {
        *state = MEPA_TC10_START;
    }
    break;
    case LAN887X_STS_TC10_STATE_NORMAL: {
        *state = MEPA_TC10_NORMAL;
    }
    break;
    case LAN887X_STS_TC10_STATE_SLEEP_ACK: {
        *state = MEPA_TC10_SLEEP_ACK;
    }
    break;
    case LAN887X_STS_TC10_STATE_SLEEP_REQ: {
        *state = MEPA_TC10_SLEEP_REQ;
    }
    break;
    case LAN887X_STS_TC10_STATE_SLEEP_FAIL: {
        *state = MEPA_TC10_SLEEP_FAIL;
    }
    break;
    case LAN887X_STS_TC10_STATE_SLEEP_SILENT: {
        *state = MEPA_TC10_SLEEP_SILENT;
    }
    break;
    case LAN887X_STS_TC10_STATE_SLEEP: {
        *state = MEPA_TC10_SLEEP;
    }
    break;
    default: {
        rc = MEPA_RC_INV_STATE;
    }
    break;
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_tc10_send_wake_request(struct mepa_device *dev)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                                    LAN887X_DEV30_COMMON_TC10_REG_REG16, &reg_data));
    reg_data |=  LAN887X_DEV30_COMMON_TC10_REG_REG16_RW_SEND_WUR;
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                    LAN887X_DEV30_COMMON_TC10_REG_REG16, reg_data));

error:
    return rc;
}

mepa_rc lan887x_phy_tc10_set_config(struct mepa_device *dev, lan887x_tc10_data_t *cfg)
{
    mepa_rc rc = MEPA_RC_OK;

    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_sleep_support(dev, cfg->sleep_enable));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_wakeup_support(dev, cfg->wakeup_mode));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_wakeup_fwd_support(dev, cfg->wakeup_fwd_mode));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_wake_pin_polarity(dev, MEPA_TC10_WAKE_IN, cfg->wake_in_pol));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_wake_pin_polarity(dev, MEPA_TC10_WAKE_OUT, cfg->wake_out_pol));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_pin_mode(dev, MEPA_TC10_WAKE_OUT, cfg->wake_out_mode));
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_pin_mode(dev, MEPA_TC10_INH, cfg->inh_mode));

error:
    return rc;
}
/**********************************
 * Internal APIs must be above this
 *********************************/

/**********************************
 * External driver callbacks
 *********************************/
// LAN887X Driver MEPA TC10 APIs
static mepa_rc lan887x_tc10_set_sleep_support(struct mepa_device        *dev,
                                              const mepa_bool_t         enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_set_sleep_support(dev, enable);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_sleep_support(struct mepa_device    *dev,
                                              mepa_bool_t           *const enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && enable != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_sleep_support(dev, enable);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_set_wakeup_support(struct mepa_device               *dev,
                                               const mepa_tc10_wakeup_mode_t    mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_set_wakeup_support(dev, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_wakeup_support(struct mepa_device           *dev,
                                               mepa_tc10_wakeup_mode_t      *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && mode != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_wakeup_support(dev, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_set_wakeup_fwd_support(struct mepa_device                       *dev,
                                                   const mepa_tc10_wakeup_fwd_mode_t        mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_set_wakeup_fwd_support(dev, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_wakeup_fwd_support(struct mepa_device              *dev,
                                                   mepa_tc10_wakeup_fwd_mode_t     *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && mode != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_wakeup_fwd_support(dev, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_set_wake_pin_polarity(struct mepa_device            *dev,
                                                  const mepa_tc10_pin_t         pin,
                                                  const mepa_gpio_mode_t        polarity)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_set_wake_pin_polarity(dev, pin, polarity);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_wake_pin_polarity(struct mepa_device            *dev,
                                                  const mepa_tc10_pin_t         pin,
                                                  mepa_gpio_mode_t              *const polarity)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && polarity != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_wake_pin_polarity(dev, pin, polarity);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_set_pin_mode(struct mepa_device         *dev,
                                         const mepa_tc10_pin_t      pin,
                                         const mepa_gpio_mode_t     mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_set_pin_mode(dev, pin, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_pin_mode(struct mepa_device         *dev,
                                         const mepa_tc10_pin_t      pin,
                                         mepa_gpio_mode_t           *const mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && mode != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_pin_mode(dev, pin, mode);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_send_sleep_request(struct mepa_device                       *dev,
                                               const mepa_tc10_sleep_request_t          req)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_send_sleep_request(dev, req);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_get_state(struct mepa_device        *dev,
                                      mepa_tc10_state_t         *const state)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && state != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_get_state(dev, state);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_tc10_send_wake_request(struct mepa_device *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_phy_tc10_send_wake_request(dev);
        MEPA_EXIT(dev);
    }

    return rc;
}

mepa_tc10_driver_t lan887x_tc10_drivers = {
    .mepa_tc10_set_sleep_support           = lan887x_tc10_set_sleep_support,
    .mepa_tc10_get_sleep_support           = lan887x_tc10_get_sleep_support,
    .mepa_tc10_set_wakeup_support          = lan887x_tc10_set_wakeup_support,
    .mepa_tc10_get_wakeup_support          = lan887x_tc10_get_wakeup_support,
    .mepa_tc10_set_wakeup_fwd_support      = lan887x_tc10_set_wakeup_fwd_support,
    .mepa_tc10_get_wakeup_fwd_support      = lan887x_tc10_get_wakeup_fwd_support,
    .mepa_tc10_set_wake_pin_polarity       = lan887x_tc10_set_wake_pin_polarity,
    .mepa_tc10_get_wake_pin_polarity       = lan887x_tc10_get_wake_pin_polarity,
    .mepa_tc10_set_pin_mode                = lan887x_tc10_set_pin_mode,
    .mepa_tc10_get_pin_mode                = lan887x_tc10_get_pin_mode,
    .mepa_tc10_send_sleep_request          = lan887x_tc10_send_sleep_request,
    .mepa_tc10_get_state                   = lan887x_tc10_get_state,
    .mepa_tc10_send_wake_request           = lan887x_tc10_send_wake_request,
};
