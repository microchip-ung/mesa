// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan8770_registers.h"
#include "lan8770_private.h"

// LAN8770 Driver Register Access APIs

mepa_rc phy_direct_reg_rd(mepa_device_t *const dev, uint16_t const offset,
                          uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if (dev->callout->miim_read != NULL) {
        rc = dev->callout->miim_read(dev->callout_ctx, offset, value);
    }

    return rc;
}

mepa_rc phy_direct_reg_wr(mepa_device_t *const dev, uint16_t const offset,
                          uint16_t const value)
{
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;

    if (dev->callout->miim_write != NULL) {
        rc = dev->callout->miim_write(dev->callout_ctx, offset, value);
    }

    return rc;
}

mepa_rc phy_direct_read_mod_write_register(mepa_device_t *const dev,
                                           uint16_t const offset,
                                           uint16_t const value,
                                           uint16_t const mask)
{
    uint16_t val = 0x0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_direct_reg_rd(dev, offset, &val));
    val = (val & (mask ^ 0xFFFF)) | value;
    MEPA_RC(rc, phy_direct_reg_wr(dev, offset, val));
    T_D( MEPA_TRACE_GRP_GEN, "modify_register addr=0x%x, set=0x%x,"
         "clr=0x%x, reg_val=0x%x, ret_code=%d \r\n",
         offset, value, mask, val, rc);
error:
    return rc;
}

mepa_rc phy_ext_bank_reg_rd(mepa_device_t *const dev, uint16_t const bank,
                            uint16_t const offset, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (bank == LAN8770_PHY_BANK_SMI) {
        MEPA_RC(rc, phy_direct_reg_rd(dev, offset, value));
    } else if (bank <= LAN8770_PHY_BANK_INSTRUMENT) {
        uint16_t regdata = 0, timeout = 200;

        regdata = offset;
        regdata |= LAN8770_EXT_REG_CTRL_REG_BANK_SET(bank);
        regdata |= LAN8770_EXT_REG_CTRL_WRT_CTRL;
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_CTRL_OFFSET, regdata));
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
        while (regdata & LAN8770_EXT_REG_CTRL_READ_CTRL) {
            MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
            timeout--;
            if (timeout) {
                MEPA_NSLEEP(10);
            }
        }

        if (!timeout) {
            T_E(MEPA_TRACE_GRP_GEN, "PHY bank register read timeout\r\n");
            rc = MEPA_RC_ERROR;
            goto error;
        }

        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_RD_DATA, value));
    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

mepa_rc phy_ext_bank_reg_wr(mepa_device_t *const dev, uint16_t const bank,
                            uint16_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (bank == LAN8770_PHY_BANK_SMI) {
        MEPA_RC(rc, phy_direct_reg_wr(dev, offset, value));
    } else if (bank <= LAN8770_PHY_BANK_INSTRUMENT) {
        uint16_t regdata = 0, timeout = 200;

        regdata = offset;
        regdata |= LAN8770_EXT_REG_CTRL_REG_BANK_SET(bank);
        regdata |= LAN8770_EXT_REG_CTRL_WRT_CTRL;
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_WR_DATA, value));
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_EXT_REG_CTRL_OFFSET, regdata));

        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
        while (regdata & LAN8770_EXT_REG_CTRL_WRT_CTRL) {
            MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_EXT_REG_CTRL_OFFSET, &regdata));
            timeout--;
            if (timeout) {
                MEPA_NSLEEP(10);
            }
        }

        if (!timeout) {
            T_E(MEPA_TRACE_GRP_GEN, "PHY bank register write timeout\r\n");
            rc = MEPA_RC_ERROR;
            goto error;
        }

    } else {
        rc = MEPA_RC_ERR_PARM;
    }

error:
    return rc;
}

mepa_rc phy_read_mod_write_register(mepa_device_t *const dev,
                                    uint16_t const phy_bank,
                                    uint16_t const offset,
                                    uint16_t const value,
                                    uint16_t const mask)
{
    uint16_t val = 0x0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, phy_bank, offset, &val));
    val = (val & (mask ^ 0xFFFF)) | value;
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, phy_bank, offset, val));

error:
    return rc;
}

// LAN8770 Driver config APIs

mepa_rc phy_tc10_set_sleep_support(struct mepa_device          *dev,
                                   const mepa_bool_t           enable)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_PCS, LAN8770_PCS_SLEEP_WAKE_CTL_OFFSET, &reg_data));

    if (enable) {
        reg_data &= ~(LAN8770_PCS_SLEEP_WAKE_CTL_SLEEP_REJECT_EN);
    } else {
        reg_data |= LAN8770_PCS_SLEEP_WAKE_CTL_SLEEP_REJECT_EN;
    }

    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_PCS, LAN8770_PCS_SLEEP_WAKE_CTL_OFFSET, reg_data));

    data->tc10.sleep_enable = enable;

error:
    return rc;
}

mepa_rc phy_tc10_get_sleep_support(struct mepa_device       *dev,
                                   mepa_bool_t              *const enable)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *enable = data->tc10.sleep_enable;

    return MEPA_RC_OK;
}

mepa_rc phy_tc10_set_wakeup_support(struct mepa_device                  *dev,
                                    const mepa_tc10_wakeup_mode_t       mode)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint16_t reg_data1 = 0, reg_data2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, &reg_data1));
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, &reg_data2));

    switch (mode) {
    case MEPA_TC10_WAKEUP_DISABLE:
        reg_data1 &= ~(LAN8770_MISC_WKP_PRT_CTL1_WK_MDI_EN);
        reg_data2 &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_IN_EN);
        break;
    case MEPA_TC10_WAKEUP_WUP_ENABLE:
        reg_data1 |= LAN8770_MISC_WKP_PRT_CTL1_WK_MDI_EN;
        reg_data2 &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_IN_EN);
        break;
    case MEPA_TC10_WAKEUP_WAKEIN_ENABLE:
        reg_data1 &= ~(LAN8770_MISC_WKP_PRT_CTL1_WK_MDI_EN);
        reg_data2 |= LAN8770_MISC_WKP_COM_CTL0_WK_IN_EN;
        break;
    case MEPA_TC10_WAKEUP_WUP_WAKEIN_ENABLE:
        reg_data1 |= LAN8770_MISC_WKP_PRT_CTL1_WK_MDI_EN;
        reg_data2 |= LAN8770_MISC_WKP_COM_CTL0_WK_IN_EN;
        break;
    default:
        return MEPA_RC_ERR_PARM;
    }

    reg_data1 |= (LAN8770_MISC_WKP_PRT_CTL1_VBAT_PORT_WR);
    reg_data2 |= (LAN8770_MISC_WKP_COM_CTL0_VBAT_COMM_WR);

    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, reg_data1));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, reg_data2));

    data->tc10.wakeup_mode = mode;

error:
    return rc;
}

mepa_rc phy_tc10_get_wakeup_support(struct mepa_device          *dev,
                                    mepa_tc10_wakeup_mode_t     *const mode)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *mode = data->tc10.wakeup_mode;

    return MEPA_RC_OK;
}

mepa_rc phy_tc10_set_wakeup_fwd_support(struct mepa_device                      *dev,
                                        const mepa_tc10_wakeup_fwd_mode_t       mode)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint16_t reg_data1 = 0, reg_data2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, &reg_data1));
    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, &reg_data2));

    switch (mode) {
    case MEPA_TC10_WAKEUP_FWD_DISABLE:
        reg_data1 &= ~(LAN8770_MISC_WKP_PTR_CTL1_WUP_AUTO_FWD_EN);
        reg_data2 &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_AUTO_FWD_EN);
        break;
    case MEPA_TC10_WAKEUP_FWD_WUP_ENABLE:
        reg_data1 |= LAN8770_MISC_WKP_PTR_CTL1_WUP_AUTO_FWD_EN;
        reg_data2 &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_AUTO_FWD_EN);
        break;
    case MEPA_TC10_WAKEUP_FWD_WAKEOUT_ENABLE:
        reg_data1 &= ~(LAN8770_MISC_WKP_PTR_CTL1_WUP_AUTO_FWD_EN);
        reg_data2 |= LAN8770_MISC_WKP_COM_CTL0_WK_OUT_AUTO_FWD_EN;
        break;
    case MEPA_TC10_WAKEUP_FWD_WUP_WAKEOUT_ENABLE:
        reg_data1 |= LAN8770_MISC_WKP_PTR_CTL1_WUP_AUTO_FWD_EN;
        reg_data2 |= LAN8770_MISC_WKP_COM_CTL0_WK_OUT_AUTO_FWD_EN;
        break;
    default:
        return MEPA_RC_ERR_PARM;
    }

    reg_data1 |= (LAN8770_MISC_WKP_PRT_CTL1_VBAT_PORT_WR);
    reg_data2 |= (LAN8770_MISC_WKP_COM_CTL0_VBAT_COMM_WR);

    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_PRT_CTL1_OFFSET, reg_data1));
    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, reg_data2));

    data->tc10.wakeup_fwd_mode = mode;

error:
    return rc;
}

mepa_rc phy_tc10_get_wakeup_fwd_support(struct mepa_device              *dev,
                                        mepa_tc10_wakeup_fwd_mode_t     *const mode)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    *mode = data->tc10.wakeup_fwd_mode;

    return MEPA_RC_OK;
}

mepa_rc phy_tc10_set_wake_pin_polarity(struct mepa_device               *dev,
                                       const mepa_tc10_pin_t            pin,
                                       const mepa_gpio_mode_t           polarity)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, &reg_data));

    switch (pin) {
    case MEPA_TC10_WAKE_IN:
        if (polarity == MEPA_GPIO_MODE_ACTIVE_LOW) {
            reg_data |= (LAN8770_MISC_WKP_COM_CTL0_WK_IN_POL_ACTIVE_LOW);
        } else if (polarity == MEPA_GPIO_MODE_ACTIVE_HIGH) {
            reg_data &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_IN_POL_ACTIVE_LOW);
        } else {
            return MEPA_RC_ERR_PARM;
        }
        break;
    case MEPA_TC10_WAKE_OUT:
        if (polarity == MEPA_GPIO_MODE_ACTIVE_LOW) {
            reg_data |= (LAN8770_MISC_WKP_COM_CTL0_WK_OUT_POL_ACTIVE_LOW);
        } else if (polarity == MEPA_GPIO_MODE_ACTIVE_HIGH) {
            reg_data &= ~(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_POL_ACTIVE_LOW);
        } else {
            return MEPA_RC_ERR_PARM;
        }
        break;
    default:
        return MEPA_RC_ERR_PARM;
    }

    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, reg_data));

    if (pin == MEPA_TC10_WAKE_IN) {
        data->tc10.wake_in_pol = polarity;
    } else {
        data->tc10.wake_out_pol = polarity;
    }

error:
    return rc;
}

mepa_rc phy_tc10_get_wake_pin_polarity(struct mepa_device           *dev,
                                       const mepa_tc10_pin_t        pin,
                                       mepa_gpio_mode_t             *const polarity)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    if (pin == MEPA_TC10_WAKE_IN) {
        *polarity = data->tc10.wake_in_pol;
    } else if (pin == MEPA_TC10_WAKE_OUT) {
        *polarity = data->tc10.wake_out_pol;
    } else {
        return MEPA_RC_ERR_PARM;
    }

    return MEPA_RC_OK;
}

mepa_rc phy_tc10_set_pin_mode(struct mepa_device            *dev,
                              const mepa_tc10_pin_t         pin,
                              const mepa_gpio_mode_t        mode)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, &reg_data));

    switch (pin) {
    case MEPA_TC10_WAKE_OUT:
        if (mode == MEPA_GPIO_MODE_PUSH_PULL) {
            reg_data |= LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_SET(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_PUSH_PULL);
        } else if (mode == MEPA_GPIO_MODE_OPEN_SOURCE) {
            reg_data |= LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_SET(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_OPEN_SOURCE);
        } else if (mode == MEPA_GPIO_MODE_OPEN_DRAIN) {
            reg_data |= LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_SET(LAN8770_MISC_WKP_COM_CTL0_WK_OUT_MODE_OPEN_DRAIN);
        } else {
            return MEPA_RC_ERR_PARM;
        }
        break;
    case MEPA_TC10_INH:
        if (mode == MEPA_GPIO_MODE_OPEN_SOURCE) {
            reg_data &= ~(LAN8770_MISC_WKP_COM_CTL0_INH_MODE_OPEN_DRAIN);
        } else if (mode == MEPA_GPIO_MODE_OPEN_DRAIN) {
            reg_data |= (LAN8770_MISC_WKP_COM_CTL0_INH_MODE_OPEN_DRAIN);
        } else {
            return MEPA_RC_ERR_PARM;
        }
        break;
    default:
        return MEPA_RC_ERR_PARM;
    }

    MEPA_RC(rc, phy_ext_bank_reg_wr(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_COM_CTL0_OFFSET, reg_data));

    if (pin == MEPA_TC10_INH) {
        data->tc10.inh_mode = mode;
    } else {
        data->tc10.wake_out_mode = mode;
    }

error:
    return rc;
}

mepa_rc phy_tc10_get_pin_mode(struct mepa_device            *dev,
                              const mepa_tc10_pin_t         pin,
                              mepa_gpio_mode_t              *const mode)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    if (pin == MEPA_TC10_INH) {
        *mode = data->tc10.inh_mode;
    } else if (pin == MEPA_TC10_WAKE_OUT) {
        *mode = data->tc10.wake_out_mode;
    } else {
        return MEPA_RC_ERR_PARM;
    }

    return MEPA_RC_OK;
}

mepa_rc phy_tc10_send_sleep_request(struct mepa_device                  *dev,
                                    const mepa_tc10_sleep_request_t     req)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERR_PARM;

    if (req == MEPA_TC10_LPS) {
        MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MDIO_CTRL2_OFFSET, &reg_data));
        reg_data |=  LAN8770_MDIO_CTRL2_SLEEP_REQ;
        MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_MDIO_CTRL2_OFFSET, reg_data));
    }

error:
    return rc;
}

mepa_rc phy_tc10_get_state(struct mepa_device       *dev,
                           mepa_tc10_state_t        *const state)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_ext_bank_reg_rd(dev, LAN8770_PHY_BANK_MISC, LAN8770_MISC_WKP_DBG_STS_OFFSET, &reg_data));

    switch (LAN8770_MISC_WKP_DBG_STS_TC10_STATE_GET(reg_data)) {
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_START:
        *state = MEPA_TC10_START;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_NORMAL:
        *state = MEPA_TC10_NORMAL;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_SLEEP_ACK:
        *state = MEPA_TC10_SLEEP_ACK;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_SLEEP_REQ:
        *state = MEPA_TC10_SLEEP_REQ;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_SLEEP_FAIL:
        *state = MEPA_TC10_SLEEP_FAIL;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_SLEEP_SILENT:
        *state = MEPA_TC10_SLEEP_SILENT;
        break;
    case LAN8770_MISC_WKP_DBG_STS_TC10_STATE_SLEEP:
        *state = MEPA_TC10_SLEEP;
        break;
    default:
        return MEPA_RC_INV_STATE;
    }

error:
    return rc;
}

mepa_rc phy_tc10_send_wake_request(struct mepa_device *dev)
{
    uint16_t reg_data = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_direct_reg_rd(dev, LAN8770_MDIO_CTRL2_OFFSET, &reg_data));
    reg_data |=  LAN8770_MDIO_CTRL2_WAKE_REQ;
    MEPA_RC(rc, phy_direct_reg_wr(dev, LAN8770_MDIO_CTRL2_OFFSET, reg_data));

error:
    return rc;
}

mepa_rc phy_tc10_set_config(struct mepa_device *dev, phy_tc10_data_t *cfg)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, phy_tc10_set_sleep_support(dev, cfg->sleep_enable));
    MEPA_RC(rc, phy_tc10_set_wakeup_support(dev, cfg->wakeup_mode));
    MEPA_RC(rc, phy_tc10_set_wakeup_fwd_support(dev, cfg->wakeup_fwd_mode));
    MEPA_RC(rc, phy_tc10_set_wake_pin_polarity(dev, MEPA_TC10_WAKE_IN, cfg->wake_in_pol));
    MEPA_RC(rc, phy_tc10_set_wake_pin_polarity(dev, MEPA_TC10_WAKE_OUT, cfg->wake_out_pol));
    MEPA_RC(rc, phy_tc10_set_pin_mode(dev, MEPA_TC10_WAKE_OUT, cfg->wake_out_mode));
    MEPA_RC(rc, phy_tc10_set_pin_mode(dev, MEPA_TC10_INH, cfg->inh_mode));

error:
    return rc;
}
