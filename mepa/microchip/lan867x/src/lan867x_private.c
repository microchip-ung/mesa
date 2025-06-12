// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <string.h>
#include <stdbool.h>

#include <mepa_driver.h>
#include <lan867x_registers.h>
#include <lan867x_private.h>

// Private APIs
mepa_rc lan867x_miim_reg_rd(mepa_device_t *const dev, uint16_t const offset, uint16_t *const value)
{
    *value = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    if(dev->callout->miim_read != NULL) {
        rc = dev->callout->miim_read(dev->callout_ctx, offset, value);
    }

    return rc;
}

mepa_rc lan867x_miim_reg_wr(mepa_device_t *const dev, uint16_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if(dev->callout->miim_write != NULL) {
        rc = dev->callout->miim_write(dev->callout_ctx, offset, value);
    }

    return rc;
}

mepa_rc lan867x_mmd_reg_rd(mepa_device_t *const dev, uint8_t const devaddr, uint16_t const offset, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if(dev->callout->mmd_read != NULL) {
        rc = dev->callout->mmd_read(dev->callout_ctx, devaddr, offset, value);
    }
    else if((dev->callout->miim_read != NULL) && (dev->callout->miim_write != NULL)) {
        *value = 0;
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDCTRL_REG, (MMDCTRL_ADDRESS | devaddr)));
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDAD_REG, offset));
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDCTRL_REG, (MMDCTRL_NO_POST_INC | devaddr)));
        rc = dev->callout->miim_read(dev->callout_ctx, LAN867X_MMDAD_REG, value);
    } else {
        // misra_c_2023_rule_15_6_violation
        // taken care by > rc = MEPA_RC_ERROR;
    }

error:
    return rc;
}

mepa_rc lan867x_mmd_reg_wr(mepa_device_t *const dev, uint8_t const devaddr, uint16_t const offset, uint16_t const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if(dev->callout->mmd_write != NULL)
    {
        rc = dev->callout->mmd_write(dev->callout_ctx, devaddr, offset, value);
    }
    else if((dev->callout->miim_read != NULL) && (dev->callout->miim_write != NULL))
    {
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDCTRL_REG, (MMDCTRL_ADDRESS | devaddr)));
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDAD_REG, offset));
        MEPA_RC(rc, dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDCTRL_REG, (MMDCTRL_NO_POST_INC | devaddr)));
        rc = dev->callout->miim_write(dev->callout_ctx, LAN867X_MMDAD_REG, value);
    } else {
        // misra_c_2023_rule_15_6_violation
        // taken care by > rc = MEPA_RC_ERROR;
    }

error:
    return rc;
}

static mepa_rc lan867x_mmd_modify(mepa_device_t *const dev, uint8_t const devid, uint16_t const offset, uint16_t const mask, uint16_t const val)
{
    uint16_t data = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, lan867x_mmd_reg_rd(dev, devid, offset, &data));
    data &= ~mask;
    data |= val;
    rc = lan867x_mmd_reg_wr(dev, devid, offset, data);

error:
    return rc;
}

static mepa_rc lan867x_indirect_reg_rd(mepa_device_t *const dev, uint8_t addr, uint16_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;

    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00D8, addr));
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00DA, 0x2));
    rc = lan867x_mmd_reg_rd(dev, MMD_MISC, 0x00D9, value);

error:
    return rc;
}

mepa_rc lan867x_init_conf(mepa_device_t *const dev, const mepa_t1s_plca_cfg_t cfg)
{
    uint16_t id = 0;
    mepa_rc rc = MESA_RC_OK;
    int itemp1 = 0, itemp2 = 0;
    int offset1 = 0, offset2 = 0;
    uint16_t temp1 = 0, temp2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val1 = 0, val2 = 0, cfgparam1 = 0, cfgparam2 = 0;

    if (data->dev.rev == LAN867X_REVB) {
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x00D0, 0x0E03, 0x0002));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x00D1, 0x0300, 0x0000));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0084, 0xFFC0, 0x3380));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0085, 0x000F, 0x0006));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x008A, 0xF800, 0xC000));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0087, 0x801C, 0x801C));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0088, 0x1FFF, 0x033F));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x008B, 0x0404));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0080, 0x0600, 0x0600));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x00F1, 0x7F00, 0x2400));
        MEPA_RC(rc, lan867x_mmd_modify(dev, MMD_MISC, 0x0096, 0x2000, 0x2000));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x0099, 0x7F80));
    }
    else if (data->dev.rev > LAN867X_REVB) {
        MEPA_RC(rc, lan867x_indirect_reg_rd(dev, 0x04, &val1));
        val1 &= (0x1FU);
        MEPA_RC(rc, lan867x_indirect_reg_rd(dev, 0x08, &val2));
        val2 &= (0x1FU);

        /* offset 1 calculation */
        if ((val1 & 0x10U) != 0U) {
            //offset1 = (int8_t)((uint8_t)val1 - 0x20U);
            temp1 = (val1 - 0x20U);
            offset1 = (int8_t)temp1;
        }
        else {
            offset1 = (int8_t)val1;
        }

        /* offset 2 calculation */
        if ((val2 & 0x10U) != 0U) {
            //offset2 = (int8_t)((uint8_t)val2 - 0x20U);
            temp2 = (val2 - 0x20U);
            offset2 = (int8_t)temp2;
        }
        else {
            offset2 = (int8_t)val2;
        }
        itemp1 = (9 + offset1);
        itemp2 = (14 + offset1);
        temp1 = (uint16_t)itemp1;
        temp2 = (uint16_t)itemp2;
        cfgparam1 = (((temp1 & (uint16_t)0x3FU) << 10U) | ((temp2 & (uint16_t)0x3FU) << 4U) | ((uint16_t)0x03U));

        itemp1 = (40 + offset2);
        temp1 = (uint16_t)itemp1;
        cfgparam2 = ((temp1 & (uint16_t)0x3FU) << 10U);

        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00D0, 0x3F31));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00E0, 0xC000));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x0084, cfgparam1));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x008A, cfgparam2));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00E9, 0x9E50));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00F5, 0x1CF8));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00F4, 0xC020));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00F8, 0xB900));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x00F9, 0x4E53));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x0081, 0x0080));
        MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, 0x0091, 0x9660));
    } else {
        // misra_c_2023_rule_15_6_violation
        // taken care by > if (data->dev.rev > LAN867X_REVB)
    }

    temp1 = (((uint16_t)cfg.node_count << 8U) | (uint16_t)cfg.node_id);
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, PLCA_CTRL_1, temp1));
    temp2 = (((uint16_t)cfg.max_burst_cnt << 8U) | (uint16_t)cfg.burst_timer);
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, PLCA_BURST, temp2));
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, PLCA_CTRL_0, cfg.plca_enable ? PLCA_ENABLE : 0U));
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, PLCA_TO_TIMER, cfg.tx_oppr_timer));

    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_RX_MATCH_MASK_L, 0x0003));
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_RX_MATCH_CTRL, RX_MATCH_ENABLE));
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_TX_MATCH_MASK_L, 0x0003));
#ifdef USE_PMCH_TX
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_TX_MATCH_CTRL, TX_MATCH_ENABLE));
#else
#ifdef VERIFY_PMCH_TX
    /* TX_MACTH_ENABLE will be disabled after PHY transmit delay is known. */
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_TX_MATCH_CTRL,
                     TX_MAC_TS_ENABLE | TX_MATCH_ENABLE));
#else
    MEPA_RC(rc, lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_TX_MATCH_CTRL, TX_MAC_TS_ENABLE));
#endif
#endif
    MEPA_RC(rc, lan867x_mmd_reg_rd(dev, MMD_MISC, MISC_PIN_CTRL, &id));

#ifdef USE_PMCH_RX
    /* PMCH_RX signal always indicates receive match. */
    id = GPIO0_SIGNAL_PMCH_TX << GPIO0_SIGNAL_SEL_S;
#else
#ifdef USE_PMCH_TX
    id = GPIO0_SIGNAL_PMCH << GPIO0_SIGNAL_SEL_S;
#else
    id = GPIO0_SIGNAL_PMCH_RX << GPIO0_SIGNAL_SEL_S;
#ifdef VERIFY_PMCH_TX
    id = GPIO0_SIGNAL_PMCH << GPIO0_SIGNAL_SEL_S;
#endif
#endif
#endif
    rc = lan867x_mmd_reg_wr(dev, MMD_MISC, MISC_PIN_CTRL, id);

error:
    return rc;
}

mepa_rc lan867x_phy_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    uint16_t bmcr = 0;
    mepa_rc rc=MEPA_RC_OK;

    /**
     *  NOTE: return an error if config is wrong.
     *  speed = 10Mbps
     *  auto-neg always disabled
     *  fdx always disabled.
     */
    if (!(config->man_neg == MEPA_MANUAL_NEG_REF || config->man_neg == MEPA_MANUAL_NEG_CLIENT) ||
        (config->fdx == true) || (config->speed != MESA_SPEED_10M) || (config->mac_if_aneg_ena != false)) {
        return MEPA_RC_ERR_PARM;
    }

    MEPA_RC(rc, lan867x_miim_reg_rd(dev, LAN867X_BASIC_CONTROL_REG, &bmcr));

    if(config->admin.enable) {
        bmcr = (bmcr & ((uint16_t)(~LAN867X_BASIC_CONTROL_POWER_DOWN)));
    } else {
        bmcr = (bmcr | ((uint16_t)LAN867X_BASIC_CONTROL_POWER_DOWN));
    }

    rc = lan867x_miim_reg_wr(dev, LAN867X_BASIC_CONTROL_REG, bmcr);

error:
    return rc;
}

mepa_rc lan867x_get_link_status(mepa_device_t *const dev, mepa_status_t *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;

    uint16_t plca = 0, id = 0, beacon = 0;

    MEPA_RC(rc, lan867x_mmd_reg_rd(dev, MMD_MISC, PLCA_CTRL_0, &plca));
    MEPA_RC(rc, lan867x_mmd_reg_rd(dev, MMD_MISC, PLCA_CTRL_1, &id));
    MEPA_RC(rc, lan867x_mmd_reg_rd(dev, MMD_MISC, PLCA_STATUS, &beacon));

    /* T1S PHY cannot detect link. */
    status->link = true;
    status->speed = MESA_SPEED_10M;
    status->fdx = false;

    /* Simulate link down if the beacon status is down for node that is not
     * the coordinator (node id 0).
     */
    if ((plca & PLCA_ENABLE) != 0U) {
        if ((id & PLCA_LOCAL_NODE_ID_M) != 0U) {
            status->link = ((beacon & BEACON_ACTIVE) != 0U) ? true : false;
        }
    }

error:
    return rc;
}
