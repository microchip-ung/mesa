// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include <mepa_ts_driver.h>

#include "lan8814_registers.h"
#include "lan8814_ts_registers.h"

#include "lan8814_private.h"

extern mepa_ts_driver_t indy_ts_drivers;

static mepa_rc indy_conf_set(mepa_device_t *dev, const mepa_driver_conf_t *config);
static mepa_rc indy_qsgmii_aneg(mepa_device_t *dev, mepa_bool_t ena);
static mepa_rc indy_event_enable_set(mepa_device_t *dev, mepa_event_t event, mepa_bool_t enable);

mepa_rc indy_direct_reg_rd(mepa_device_t *dev, uint16_t addr, uint16_t *value)
{
    if (dev->callout->miim_read(dev->callout_cxt, addr, value) != MESA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "miim read failed\n");
    }
    return MEPA_RC_OK;
}
mepa_rc indy_direct_reg_wr(mepa_device_t *dev, uint16_t addr, uint16_t value, uint16_t mask)
{
    uint16_t reg_val = value;
    mesa_rc rc;

    rc = dev->callout->miim_read(dev->callout_cxt, addr, &reg_val);
    if (rc == MESA_RC_OK) {
        if (mask != INDY_DEF_MASK) {
            reg_val = (reg_val & ~mask) | (value & mask);
        } else {
            reg_val = value;
        }
        rc = dev->callout->miim_write(dev->callout_cxt, addr, reg_val);
        if (rc != MESA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "miim write failed\n");
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "miim write failed\n");
    }
    return MEPA_RC_OK;
}

// Extended page read and write functions
// Extended page numbers range : 0 - 31
mepa_rc indy_ext_reg_rd(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t *value)
{
    // Set-up to access extended page register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL, page, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL,
                INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC | page, INDY_DEF_MASK));

    // Read the value
    MEPA_RC(indy_direct_reg_rd(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}
mepa_rc indy_ext_reg_wr(mepa_device_t *dev, uint16_t page, uint16_t addr, uint16_t value, uint16_t mask)
{
    // Set-up to access extended page register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL, page, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_CTRL,
                INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC | page, INDY_DEF_MASK));

    // write the value
    MEPA_RC(indy_direct_reg_wr(dev, INDY_EXT_PAGE_ACCESS_ADDR_DATA, value, mask));
    return MEPA_RC_OK;
}

// MMD read and write functions
// MMD device range : 0 - 31
mepa_rc indy_mmd_reg_rd(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t *value)
{
    // Set-up to MMD register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // Read the value
    MEPA_RC(indy_direct_reg_rd(dev, INDY_MMD_ACCESS_ADDR_DATA, value));
    return MEPA_RC_OK;
}

mepa_rc indy_mmd_reg_wr(mepa_device_t *dev, uint16_t mmd, uint16_t addr, uint16_t value, uint16_t mask)
{
    // Set-up to MMD register.
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL, mmd, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, addr, INDY_DEF_MASK));
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_CTRL,
                INDY_F_MMD_ACCESS_CTRL_MMD_FUNC | mmd, INDY_DEF_MASK));

    // write the value
    MEPA_RC(indy_direct_reg_wr(dev, INDY_MMD_ACCESS_ADDR_DATA, value, mask));
    return MEPA_RC_OK;
}

static mepa_rc indy_delete(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    free(data);
    free(dev);
    dev = NULL;
    return MEPA_RC_OK;
}

static mepa_rc indy_get_device_info(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t id_1, id_2;

    RD(dev, INDY_DEVICE_ID_2, &id_2);

    data->dev.model = INDY_X_DEV_ID_MODEL(id_2);
    data->dev.rev = INDY_X_DEV_ID_REV(id_2);
    T_I(MEPA_TRACE_GRP_GEN, "model 0x%x rev %d\n", data->dev.model, data->dev.rev);

    return MEPA_RC_OK;
}

static mepa_device_t *indy_probe(mepa_driver_t *drv,
                                 const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                 struct mepa_callout_cxt MEPA_SHARED_PTR *callout_cxt,
                                 struct mepa_board_conf              *board_conf)
{
    mepa_device_t *dev =
        (mepa_device_t *)calloc(1, sizeof(mepa_device_t));

    if (dev == NULL) goto out_device;

    phy_data_t *data =
        (phy_data_t *)calloc(1, sizeof(phy_data_t));

    if (data == NULL) goto out_data;

    dev->drv = drv;
    dev->data = data;
    dev->callout = callout;
    dev->callout_cxt = callout_cxt;
    dev->numeric_handle = board_conf->numeric_handle;

    data->port_no = board_conf->numeric_handle;
    data->mac_if = board_conf->mac_if;
    data->events = 0;

    T_I(MEPA_TRACE_GRP_GEN, "indy driver probed for port %d", data->port_no);
    return dev;

out_data:
    free(dev);
out_device:
    return NULL;
}

static mepa_rc indy_init_conf(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val;

    indy_get_device_info(dev);

    // Set config only for base port of phy.
    if (data->dev.model == 0x26) {
        if (data->packet_idx == 0) {
            //EP_WR(dev, INDY_CHIP_HARD_RESET, 1);
            PHY_MSLEEP(1);

            if (!data->qsgmii_phy_aneg_dis) {
                // Disable QSGMII auto-negotiation common for 4 ports.
                EP_WRM(dev, INDY_QSGMII_AUTO_ANEG, 0, INDY_F_QSGMII_AUTO_ANEG_AUTO_ANEG_ENA);
                data->qsgmii_phy_aneg_dis = TRUE;
            }
        }
    }

    // Enable Fast link config
    val = INDY_FLF_CFG_STAT_LINK_DOWN | INDY_FLF_CFG_STAT_FLF_ENABLE;
    EP_WRM(dev, INDY_FLF_CONFIG_STATUS, val, val);

    // Clear all GPHY interrupts during initialisation
    WR(dev, INDY_GPHY_INTR_ENA, 0);
    EP_WRM(dev, INDY_PTP_TSU_INT_EN, 0, INDY_DEF_MASK);
    RD(dev, INDY_GPHY_INTR_STATUS, &val);
    // Enable chip level interrupt
    EP_WRM(dev, INDY_INTR_CTRL, INDY_INTR_CTRL_CHIP_LVL_ENA, INDY_INTR_CTRL_CHIP_LVL_ENA);
    return MEPA_RC_OK;
}

// Configure qsgmii aneg advertisement capabilities
static void indy_qsgmii_tx_abilities(mepa_device_t *dev, mepa_port_speed_t speed, mepa_bool_t duplex)
{
    uint16_t value = 0x1; // default disable EEE enable & EEE clock stop
    uint16_t eee_val;

    MMD_RD(dev, INDY_LINK_PARTNER_EEE_ABILITY, &eee_val);
    if (speed == MEPA_SPEED_1G) {
        value |= (eee_val & INDY_F_LP_EEE_ABILITY_1000_BT) ? 0x180 : 0;
    } else if (speed == MEPA_SPEED_100M) {
        value |= (eee_val & INDY_F_LP_EEE_ABILITY_100_BT) ? 0x180 : 0;
    }
    if (duplex) {
        value |= INDY_BIT(12);
    }
    value |= (speed == MEPA_SPEED_1G) ? INDY_BIT(10) : (speed == MEPA_SPEED_100M) ? INDY_BIT(9): 0;
    value |= INDY_BIT(14);
    EP_WR(dev, INDY_QSGMII_PCS1G_ANEG_TX_ADVERTISE_CAP, value);

    EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_RESTART, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_RESTART);
}

static mepa_rc indy_qsgmii_aneg(mepa_device_t *dev, mepa_bool_t ena)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    if (data->dev.model != 0x26) {
        return MEPA_RC_OK;
    }
    T_I(MEPA_TRACE_GRP_GEN, "qsgmii aneg ena %d", ena);
    if (!ena) {
        // Disable QSGMII auto-negotiation
        EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, 0, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA);
    } else {
        // Enable QSGMII auto-negotiation.
        EP_WRM(dev, INDY_QSGMII_PCS1G_ANEG_CONFIG, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA, INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA);
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_rev_workaround(mepa_device_t *dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val;

    // work-arounds applicable for both models 0x26 & 0x27
    do {
        // work-around for Rev C done.
        if (data->dev.rev >= 2) {
            break;
        }
        // MDI-X setting for swap A,B transmit
        EP_WRM(dev, INDY_ALIGN_SWAP, INDY_F_ALIGN_TX_A_B_SWAP, INDY_M_ALIGN_TX_SWAP);
    } while(0);
    // work-around for model 0x27 only
    if (data->dev.model == 0x27 && data->dev.rev <= 2) {
        // In Indy internal phy clock generation stops when link goes down.
        EP_WR(dev, INDY_CLOCK_MANAGEMENT_MODE_5, 0x27e);
        EP_RD(dev, INDY_LINK_QUALITY_MONITOR_SETTING, &val);
    }
    // work-around for model 0x27 done.
    if (data->dev.model != 0x26) {
        return MEPA_RC_OK;
    }
    // work-arounds applicable for only model 0x26
    // Rev A, B, C
    // PLL trim
    EP_WR(dev, INDY_ANALOG_CONTROL_1, 0x40);
    EP_WR(dev, INDY_ANALOG_CONTROL_10, 0x1);

    // Magjack center tapped ports
    EP_WR(dev, INDY_POWER_MGMT_MODE_3, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_4, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_5, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_6, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_7, 0x0077);
    EP_WR(dev, INDY_POWER_MGMT_MODE_8, 0x4377);
    EP_WR(dev, INDY_POWER_MGMT_MODE_9, 0x4377);
    EP_WR(dev, INDY_POWER_MGMT_MODE_10, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_11, 0x0777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_12, 0x0777);
    EP_WR(dev, INDY_POWER_MGMT_MODE_13, 0x6677);
    EP_WR(dev, INDY_POWER_MGMT_MODE_14, 0x6677);

    // Rev C work-around done.
    if (data->dev.rev >= 2) {
        return MEPA_RC_OK;
    }
    // Rev B work-around done.
    if (data->dev.rev >= 1) {
        return MEPA_RC_OK;
    }
    EP_WR(dev, INDY_OPERATION_MODE_STRAP_LOW, 0x2);
    EP_WR(dev, INDY_OPERATION_MODE_STRAP_HIGH, 0xc001);

    T_D(MEPA_TRACE_GRP_GEN, "rev A work-around configured");
    return MEPA_RC_OK;
}

static mepa_rc indy_workaround_after_reset(mepa_device_t *dev)
{
    // Improve cable reach beyond 130m
    EP_WR(dev, INDY_PD_CONTROLS, 0x248b);
    EP_WR(dev, INDY_DFE_INIT2_100, 0x3c30);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_0, 0x10a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_1, 0xed);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_2, 0xd3);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_3, 0xbc);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_4, 0xa8);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_5, 0x96);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_6, 0x85);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_7, 0x77);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_8, 0x6a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_9, 0x5e);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_10, 0x54);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_11, 0x4b);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_12, 0x43);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_13, 0x3c);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_14, 0x35);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_15, 0x2f);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_16, 0x2a);
    EP_WR(dev, INDY_PGA_TABLE_1G_ENTRY_17, 0x26);

    // Set Rx-clk to avoid crc errors in near-end loopback
    WRM(dev, INDY_UNH_TEST, INDY_F_TEST_RX_CLK, INDY_F_TEST_RX_CLK);

    return MEPA_RC_OK;
}

static mepa_rc indy_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    MEPA_ENTER(dev);
    if (!data->init_done) {
        indy_init_conf(dev);
        indy_rev_workaround(dev);
        indy_qsgmii_aneg(dev, FALSE);
        data->init_done = TRUE;
    }
    if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_RESET, INDY_F_BASIC_CTRL_SOFT_RESET);
    } else if (rst_conf->reset_point == MEPA_RESET_POINT_POST_MAC) {
        // To avoid qsgmii serdes and Gphy blocks settling in different speeds, use qsgmii soft reset and restart aneg.
        // This must be applied after Mac serdes is configured.
        if (data->dev.model == 0x26) {
            EP_WR(dev, INDY_QSGMII_SOFT_RESET, 0x1);
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_RESTART_ANEG, INDY_F_BASIC_CTRL_RESTART_ANEG);
        }
    }

    PHY_MSLEEP(1);
    // Some of the work-around registers get cleared after reset. So, they are called here
    // after every reset.
    indy_workaround_after_reset(dev);
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "Reconfiguring the phy after reset");
    // Reconfigure the phy after reset
    if (rst_conf->reset_point == MEPA_RESET_POINT_DEFAULT) {
        indy_conf_set(dev, &data->conf);
        if (data->events) {
            indy_event_enable_set(dev, data->events, TRUE);
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc indy_poll(mepa_device_t *dev, mepa_driver_status_t *status)
{
    uint16_t val, val2 = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);
    RD(dev, INDY_BASIC_STATUS, &val);
    status->link = (val & INDY_F_BASIC_STATUS_LINK_STATUS) ? 1 : 0;

    if (data->loopback.near_end_ena == TRUE) {
        // loops back to Mac. Ignore Line side status to Link partner.
        status->link = 1;
    }
    if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
        uint16_t lp_sym_pause = 0, lp_asym_pause = 0;
        uint8_t ext_status = 0;
        // Default values
        status->speed = MEPA_SPEED_UNDEFINED;
        status->fdx = 1;
        // check if auto-negotiation is completed or not.
        if (!data->loopback.near_end_ena && status->link && !(val & INDY_F_BASIC_STATUS_ANEG_COMPLETE)) {
            T_I(MEPA_TRACE_GRP_GEN, "Aneg is not completed for port %d", data->port_no);
            status->link = 0;
        } else if (data->loopback.near_end_ena) {
            status->speed = MEPA_SPEED_1G;
        }
        if (!status->link || data->loopback.near_end_ena) {
            // No need to read aneg values when link is down or when near-end loopback enabled.
            goto end;
        }
        // Obtain speed and duplex from link partner's advertised capability.
        RD(dev, INDY_ANEG_LP_BASE, &val);
        RD(dev, INDY_ANEG_MSTR_SLV_STATUS, &val2);
        // 1G half duplex is not supported. Refer direct register - 9
        if ((val2 & INDY_F_ANEG_MSTR_SLV_STATUS_1000_T_FULL_DUP) &&
            data->conf.aneg.speed_1g_fdx) {
            status->speed = MEPA_SPEED_1G;
            status->fdx = 1;
        } else if ((val & INDY_F_ANEG_LP_BASE_100_X_FULL_DUP) &&
            data->conf.aneg.speed_100m_fdx) {
            status->speed = MEPA_SPEED_100M;
            status->fdx = 1;
        } else if ((val & INDY_F_ANEG_LP_BASE_100_X_HALF_DUP) &&
            data->conf.aneg.speed_100m_hdx) {
            status->speed = MEPA_SPEED_100M;
            status->fdx = 0;
        } else if ((val & INDY_F_ANEG_LP_BASE_10_T_FULL_DUP) &&
            data->conf.aneg.speed_10m_fdx) {
            status->speed = MEPA_SPEED_10M;
            status->fdx = 1;
        } else if ((val & INDY_F_ANEG_LP_BASE_10_T_HALF_DUP) &&
            data->conf.aneg.speed_10m_hdx) {
            status->speed = MEPA_SPEED_10M;
            status->fdx = 0;
        }
        // Get flow control status
        lp_sym_pause = (val & INDY_F_ANEG_LP_BASE_SYM_PAUSE) ? 1 : 0;
        lp_asym_pause = (val & INDY_F_ANEG_LP_BASE_ASYM_PAUSE) ? 1 : 0;
        status->aneg.obey_pause = data->conf.flow_control && (lp_sym_pause || lp_asym_pause);
        status->aneg.generate_pause = data->conf.flow_control && lp_sym_pause;
    } else {
        uint8_t speed;
        // Forced speed
        RD(dev, INDY_BASIC_CONTROL, &val2);
        speed = !!(val2 & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0) |
                (!!(val2 & INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1) << 1);
        status->speed = (speed == 0) ? MEPA_SPEED_10M :
                        (speed == 1) ? MEPA_SPEED_100M :
                        (speed == 2) ? MEPA_SPEED_1G : MEPA_SPEED_UNDEFINED;
        status->fdx = !!(val & INDY_F_BASIC_CTRL_DUP_MODE);
        //check that aneg is not enabled.
        if (val2 & INDY_F_BASIC_CTRL_ANEG_ENA) {
            T_W(MEPA_TRACE_GRP_GEN, "Aneg is enabled for forced speed config on port %d", data->port_no);
        }
    }

    end:
    if (data->dev.model == 0x26 && data->conf.speed == MEPA_SPEED_AUTO &&
        data->conf.mac_if_aneg_ena) {
        if (status->link && status->link != data->link_status) {
            // copy the capabilities on host side
            indy_qsgmii_tx_abilities(dev, status->speed, status->fdx);
        }
    }
    data->link_status = status->link;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "port %d status link %d, speed %d, fdx %d", data->port_no, status->link, status->speed, status->fdx);
    return MEPA_RC_OK;
}

static mepa_rc indy_conf_set(mepa_device_t *dev, const mepa_driver_conf_t *config)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t new_value, mask, old_value;
    mepa_bool_t restart_aneg = FALSE;
    mepa_bool_t qsgmii_aneg = config->speed != MEPA_SPEED_AUTO ? FALSE : config->mac_if_aneg_ena;

    MEPA_ENTER(dev);
    if (config->admin.enable) {
        if (qsgmii_aneg != data->conf.mac_if_aneg_ena) {
            indy_qsgmii_aneg(dev, qsgmii_aneg);
        }
        if (config->speed == MEPA_SPEED_AUTO || config->speed == MEPA_SPEED_1G) {
            if (data->conf.admin.enable != config->admin.enable) {
                restart_aneg = TRUE;
            }

            // 1G manual negotiation & speed
            new_value = config->aneg.speed_1g_fdx ? INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP : 0;
            mask = INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP;
            if (config->man_neg) {
                new_value |= INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA;
                new_value |= config->man_neg == MEPA_MANUAL_NEG_REF ? INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL : 0;
            }
            mask |= (INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL | INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA);
            if (config->aneg.speed_1g_fdx != data->conf.aneg.speed_1g_fdx ||
                config->man_neg           != data->conf.man_neg) {
                restart_aneg = TRUE;
            }
            WRM(dev, INDY_ANEG_MSTR_SLV_CTRL, new_value, mask);

            // Set up auo-negotiation advertisement in register 4
            new_value = (((config->aneg.tx_remote_fault ? 1 : 0) << 13) |
                     ((config->flow_control ? 1 : 0) << 11) |
                     ((config->flow_control ? 1 : 0) << 10) |
                     ((config->aneg.speed_100m_fdx ? 1 : 0) << 8) |
                     ((config->aneg.speed_100m_hdx ? 1 : 0) << 7) |
                     ((config->aneg.speed_10m_fdx ? 1 : 0) << 6) |
                     ((config->aneg.speed_10m_hdx ? 1 : 0) << 5) |
                     (1 << 0)); // default selector field - 1
            RD(dev, INDY_ANEG_ADVERTISEMENT, &old_value);
            if (old_value != new_value) {
                restart_aneg = TRUE;
            }
            WR(dev, INDY_ANEG_ADVERTISEMENT, new_value);
            // Enable & restart auto-negotiation
            new_value = INDY_F_BASIC_CTRL_ANEG_ENA;
            WRM(dev, INDY_BASIC_CONTROL, new_value, new_value | INDY_F_BASIC_CTRL_SOFT_POW_DOWN);
            if (restart_aneg) {
                T_I(MEPA_TRACE_GRP_GEN, "Aneg restarted on port %d", data->port_no);
                WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_RESTART_ANEG, INDY_F_BASIC_CTRL_RESTART_ANEG);
            }
        } else if (config->speed != MEPA_SPEED_UNDEFINED) {
            T_I(MEPA_TRACE_GRP_GEN, "forced speed %d configured\n", config->speed);
            new_value = ((config->speed == MEPA_SPEED_100M ? 1 : 0) << 13) | (0 << 12) |
                    ((config->fdx ? 1 : 0) << 8) |
                    ((config->speed == MEPA_SPEED_1G ? 1 : 0) << 6);
            mask = INDY_BIT(13) | INDY_BIT(12) | INDY_BIT(8) | INDY_BIT(6) | INDY_F_BASIC_CTRL_SOFT_POW_DOWN | INDY_F_BASIC_CTRL_ANEG_ENA;
            WRM(dev, INDY_BASIC_CONTROL, new_value, mask);
        }
    } else {
        T_I(MEPA_TRACE_GRP_GEN, "set power down\n");
        // set soft power down bit
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SOFT_POW_DOWN, INDY_F_BASIC_CTRL_SOFT_POW_DOWN);
    }
    data->conf = *config;
    data->conf.mac_if_aneg_ena = qsgmii_aneg;
    MEPA_EXIT(dev);

    return MEPA_RC_OK;
}

static mepa_rc indy_conf_get(mepa_device_t *dev, mepa_driver_conf_t *const config)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *config = data->conf;
    MEPA_EXIT(dev);
    T_D(MEPA_TRACE_GRP_GEN, "returning phy config on port %d", data->port_no);
    return MEPA_RC_OK;
}
static mepa_rc indy_if_get(mepa_device_t *dev, mepa_port_speed_t speed,
                           mepa_port_interface_t *mac_if)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    *mac_if = data->mac_if;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_cable_diag_start(mepa_device_t *dev, int mode)
{
    uint16_t value, mask = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    //check if cable diagnostics has not started.
    RD(dev, INDY_CABLE_DIAG, &value);
    if (!(value & INDY_F_CABLE_DIAG_TEST_ENA)) {
        value |= INDY_F_CABLE_DIAG_TEST_ENA;
        value |= INDY_F_CABLE_TEST_PAIR(0); // Pair A by default
        mask |= INDY_F_CABLE_DIAG_TEST_ENA | INDY_M_CABLE_TEST_PAIR;
        WRM(dev, INDY_CABLE_DIAG, value, mask);
    }
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "cable diagnostics started");
    return MEPA_RC_OK;
}

static mepa_rc indy_cable_diag_get(mepa_device_t *dev, mepa_cable_diag_result_t *res)
{
    uint16_t value, status;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    RD(dev, INDY_CABLE_DIAG, &value);
    if (value & INDY_F_CABLE_DIAG_TEST_ENA) {
        res->status[0] = MEPA_CABLE_DIAG_STATUS_RUNNING; // only Pair A status currently. Other pairs need to be added.
        rc = MEPA_RC_INCOMPLETE;
    } else {
        status = INDY_X_CABLE_DIAG_STATUS(value);
        switch (status) { // Only Pair A result
        case 0: res->status[0] = MEPA_CABLE_DIAG_STATUS_OK;
                res->length[0] = 0; // cannot measure length
                res->link = TRUE;
                break;
        case 1: res->status[0] = MEPA_CABLE_DIAG_STATUS_OPEN;
                break;
        case 2: res->status[0] = MEPA_CABLE_DIAG_STATUS_SHORT;
                break;
        case 3: res->status[0] = MEPA_CABLE_DIAG_STATUS_ABNORM;
                break;
        default:res->status[0] = MEPA_CABLE_DIAG_STATUS_OPEN;
                break;
        }
    }
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "cable diagnostics result status[0] %d", res->status[0]);
    return MEPA_RC_OK;
}

static mepa_rc indy_aneg_status_get(mepa_device_t *dev, mepa_aneg_status_t *status)
{
    uint16_t val;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    RD(dev, INDY_ANEG_MSTR_SLV_STATUS, &val);
    status->master_cfg_fault = (val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_FAULT) ? TRUE : FALSE;
    status->master = val & INDY_F_ANEG_MSTR_SLV_STATUS_CFG_RES ? TRUE : FALSE;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "aneg status get mstr %d", status->master);
    return MEPA_RC_OK;
}

// read direct registers for debugging
static mepa_rc indy_direct_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = indy_direct_reg_rd(dev, addr, value);
    MEPA_EXIT(dev);
    return rc;
}

// write direct registers. Used for debugging.
static mepa_rc indy_direct_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc;
    uint16_t addr = address & 0x1f;

    MEPA_ENTER(dev);
    rc = indy_direct_reg_wr(dev, addr, value, 0xFFFF);
    MEPA_EXIT(dev);
    return rc;
}

// read extended page/mmd register for debugging
static mepa_rc indy_ext_mmd_reg_read(mepa_device_t *dev, uint32_t address, uint16_t *const value)
{
    mepa_rc rc;
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;
    uint16_t mmd = (page_mmd >> 11);

    MEPA_ENTER(dev);
    if (mmd) {
        rc = indy_mmd_reg_rd(dev, mmd, addr, value);
    } else {
        rc = indy_ext_reg_rd(dev, page_mmd, addr, value);
    }
    MEPA_EXIT(dev);
    return rc;
}

// write extended page/mmd register. Used for debugging.
static mepa_rc indy_ext_mmd_reg_write(mepa_device_t *dev, uint32_t address, uint16_t value)
{
    mepa_rc rc;
    uint16_t page_mmd = (address >> 16) & 0xffff;
    uint16_t addr = address & 0xffff;
    uint16_t mmd = (page_mmd >> 11);

    MEPA_ENTER(dev);
    if (mmd) {
        rc = indy_mmd_reg_wr(dev, mmd, addr, value, 0xFFFF);
    } else {
        rc = indy_ext_reg_wr(dev, page_mmd, addr, value, 0xFFFF);
    }
    MEPA_EXIT(dev);
    return rc;
}

// Enable events
static mepa_rc indy_event_enable_set(mepa_device_t *dev, mepa_event_t event, mepa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t ev_mask = 0, i, val;
    phy_data_t *data = (phy_data_t *)dev->data;
    data->events = enable ? (data->events | event) :
                            (data->events & ~event);
    MEPA_ENTER(dev);
    for (i = 0; i < sizeof(mepa_event_t)*8; i++) {
        switch(event & (1 << i)) {
            case MEPA_LINK_LOS:
                ev_mask = ev_mask | INDY_F_GPHY_INTR_ENA_LINK_DOWN;
                break;
            case MEPA_FAST_LINK_FAIL:
                ev_mask = ev_mask | INDY_F_GPHY_INTR_ENA_FLF_INTR;
                break;
            default:
                // Not yet implemented
                break;
        }
    }
    WRM(dev, INDY_GPHY_INTR_ENA, enable ? ev_mask : 0, ev_mask);
    T_I(MEPA_TRACE_GRP_GEN, "events enabled 0x%x \n", data->events);
    MEPA_EXIT(dev);
    return rc;
}

// Get current enabled events
static mepa_rc indy_event_enable_get(mepa_device_t *dev, mepa_event_t *const event)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    MEPA_ENTER(dev);
    *event = data->events;
    MEPA_EXIT(dev);
    return rc;
}

// Poll the status of currently enabled events
static mepa_rc indy_event_status_poll(mepa_device_t *dev, mepa_event_t *const status)
{
    uint16_t val;
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    *status = 0;
    MEPA_ENTER(dev);
    rc = RD(dev, INDY_GPHY_INTR_STATUS, &val);
    if (val & INDY_F_GPHY_INTR_ENA_LINK_DOWN) {
        *status |= data->events & MEPA_LINK_LOS;
    }
    if (val & INDY_F_GPHY_INTR_ENA_FLF_INTR) {
        *status |= data->events & MEPA_FAST_LINK_FAIL;
    }
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, " port %d events polled 0x%x val %x\n", data->port_no, *status, val);
    return rc;
}

// Set loopback modes in phy
static mepa_rc indy_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    if ((loopback->mac_serdes_input_ena == TRUE) || (loopback->mac_serdes_facility_ena == TRUE) ||
        (loopback->mac_serdes_equip_ena == TRUE) || (loopback->media_serdes_input_ena == TRUE) ||
        (loopback->media_serdes_facility_ena == TRUE) || (loopback->media_serdes_equip_ena == TRUE)) {
        // Not supported on Indy
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    // Far end loopback
    if (loopback->far_end_ena == TRUE) {
        WRM(dev, INDY_PCS_LOOP_POLARITY_CTRL, INDY_F_PCS_LOOP_CTRL_PORT_LOOP,
                 INDY_F_PCS_LOOP_CTRL_PORT_LOOP);
    } else if (data->loopback.far_end_ena == TRUE) {
        WRM(dev, INDY_PCS_LOOP_POLARITY_CTRL, 0, INDY_F_PCS_LOOP_CTRL_PORT_LOOP);
    }
    if (loopback->near_end_ena == TRUE) {
        WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_LOOPBACK, INDY_F_BASIC_CTRL_LOOPBACK);
        if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
            // Set 1000mbps speed for loopback when there is auto-negotiation mode. While removing loopback, restore the original mode.
            // Disable auto-negotiation
            WRM(dev, INDY_BASIC_CONTROL, 0, INDY_F_BASIC_CTRL_ANEG_ENA);
            // Set 1000mbps speed
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1, INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1 | INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0);
        }
    } else if (data->loopback.near_end_ena == TRUE) {
        WRM(dev, INDY_BASIC_CONTROL, 0, INDY_F_BASIC_CTRL_LOOPBACK);
        if (data->conf.speed == MEPA_SPEED_AUTO || data->conf.speed == MEPA_SPEED_1G) {
            // Remove 1000mbps config applied while setting loopback.
            WRM(dev, INDY_ANEG_MSTR_SLV_CTRL, 0, INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA |
                INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL);
            // Enable aneg
            WRM(dev, INDY_BASIC_CONTROL, INDY_F_BASIC_CTRL_ANEG_ENA | INDY_F_BASIC_CTRL_RESTART_ANEG,
                INDY_F_BASIC_CTRL_ANEG_ENA | INDY_F_BASIC_CTRL_RESTART_ANEG);
        }
        if (data->dev.rev <= 1) {
            EP_WR(dev, INDY_POWER_MGMT_MODE_5, 0x6677);
            EP_WR(dev, INDY_POWER_MGMT_MODE_6, 0x6677);
            EP_WR(dev, INDY_POWER_MGMT_MODE_8, 0x4377);
            EP_WR(dev, INDY_POWER_MGMT_MODE_11, 0x4377);
        }
    }
    if (loopback->connector_ena == TRUE) {
        WR(dev, INDY_RESV_CON_LOOP, 0xfc08);
    } else if (data->loopback.connector_ena == TRUE) {
        WR(dev, INDY_RESV_CON_LOOP, 0xfc00);
    }
    if (loopback->qsgmii_pcs_tbi_ena == TRUE) { // Enable tbi loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK,
               INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK);
    } else if (data->loopback.qsgmii_pcs_tbi_ena == TRUE) { // Disable tbi loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, 0, INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK);
    }
    if (loopback->qsgmii_pcs_gmii_ena == TRUE) { // Enable gmii loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK,
               INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK);
    } else if (data->loopback.qsgmii_pcs_gmii_ena == TRUE) { // Disable gmii loopback
        EP_WRM(dev, INDY_QSGMII_PCS1G_DEBUG, 0, INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK);
    }
    if (loopback->qsgmii_serdes_ena == TRUE) { // Enable qsgmii serdes loopback.
        // Serdes configuration would affect all the 4 ports.
        EP_WRM(dev, INDY_QSGMII_SERDES_MISC_CTRL, INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE,
               INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE);
    } else if (data->loopback.qsgmii_serdes_ena == TRUE) {
        EP_WRM(dev, INDY_QSGMII_SERDES_MISC_CTRL, 0, INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE);
    }
    data->loopback = *loopback;
    MEPA_EXIT(dev);
    T_I(MEPA_TRACE_GRP_GEN, "loopback enabled\n");
    return MEPA_RC_OK;
}
mepa_rc indy_loopback_get(struct mepa_device *dev, mepa_loopback_t *const loopback)
{
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_ENTER(dev);
    *loopback = data->loopback;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}
// Returns gpio using port number and led number
static uint8_t led_num_to_gpio_mapping(mepa_device_t *dev, mepa_led_num_t led_num)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    uint8_t gpio = 11;// port 0 as default.
    switch(data->packet_idx) {
        case 0:
               gpio = led_num == MEPA_LED0 ? 11 : 12;
               break;
        case 1:
               gpio = led_num == MEPA_LED0 ? 17 : 18;
               break;
        case 2:
               gpio = led_num == MEPA_LED0 ? 19 : 20;
               break;
        case 3:
               gpio = led_num == MEPA_LED0 ? 13 : 14;
               break;
        default:
               // invalid.
               break;
    }
    T_I(MEPA_TRACE_GRP_GEN, "gpio mapped %d\n", gpio);
    return gpio;
}
static uint8_t led_mepa_mode_to_indy(mepa_gpio_mode_t mode)
{
    uint8_t ret=0;
    switch(mode) {
        case MEPA_GPIO_MODE_LED_LINK_ACTIVITY: ret = 0;
             break;
        case MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY: ret = 1;
             break;
        case MEPA_GPIO_MODE_LED_LINK100_ACTIVITY: ret = 2;
             break;
        case MEPA_GPIO_MODE_LED_LINK10_ACTIVITY: ret = 3;
             break;
        case MEPA_GPIO_MODE_LED_LINK100_1000_ACTIVITY: ret = 4;
             break;
        case MEPA_GPIO_MODE_LED_LINK10_1000_ACTIVITY: ret = 5;
             break;
        case MEPA_GPIO_MODE_LED_LINK10_100_ACTIVITY: ret = 6;
             break;
        case MEPA_GPIO_MODE_LED_DUPLEX_COLLISION: ret = 8;
             break;
        case MEPA_GPIO_MODE_LED_COLLISION: ret = 9;
             break;
        case MEPA_GPIO_MODE_LED_ACTIVITY: ret = 10;
             break;
        case MEPA_GPIO_MODE_LED_AUTONEGOTIATION_FAULT: ret = 12;
             break;
        case MEPA_GPIO_MODE_LED_FORCE_LED_OFF: ret = 14;
            break;
        case MEPA_GPIO_MODE_LED_FORCE_LED_ON: ret = 15;
            break;
        case MEPA_GPIO_MODE_LED_DISABLE_EXTENDED: ret = 0xf0;
            break;
        default:
            ret = 0xff; // Not valid for indy
            break;
    }
    return ret;
}
// In Indy, LED0 of software Api maps to LED1 of hardware,
//          LED1 of software Api maps to LED2 of hardware.
static mepa_rc indy_led_mode_set(mepa_device_t *dev, mepa_gpio_mode_t led_mode, mepa_led_num_t led_num)
{
    uint16_t mode;
    phy_data_t *phy_data = (phy_data_t *) dev->data;
    // Indy supports only LED0 and LED1
    if ((led_num != MEPA_LED0) && (led_num != MEPA_LED1)) {
        T_W(MEPA_TRACE_GRP_GEN, "8814 supports only leds 0 & 1\n");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if ((mode = led_mepa_mode_to_indy(led_mode)) == 0xff) {// Not valid
        T_W(MEPA_TRACE_GRP_GEN, "Not valid led mode");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    if (mode == MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        // Normal operation
        EP_WRM(dev, INDY_LED_CONTROL_REG1, INDY_F_LED_CONTROL_KSZ_LED_MODE, INDY_F_LED_CONTROL_KSZ_LED_MODE);
    } else { // extended mode
        EP_WRM(dev, INDY_LED_CONTROL_REG1, 0, INDY_F_LED_CONTROL_KSZ_LED_MODE);
        EP_WRM(dev, INDY_LED_CONTROL_REG2, INDY_ENCODE_BITFIELD(mode, led_num * 4, 4), INDY_ENCODE_BITMASK(led_num * 4, 4));
    }
}
static mepa_rc indy_gpio_mode_private(mepa_device_t *dev, const mepa_gpio_conf_t *data)
{
    uint16_t gpio_en = 0, dir, val = 0, gpio_no = data->gpio_no;
    mepa_gpio_mode_t mode = data->mode;
    phy_data_t *phy_data = (phy_data_t *) dev->data;

    if (mode == MEPA_GPIO_MODE_OUT || mode == MEPA_GPIO_MODE_IN) {
        gpio_en = 1;
        dir = mode == MEPA_GPIO_MODE_OUT ? 1 : 0;
    } else if (mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY && mode <= MEPA_GPIO_MODE_LED_DISABLE_EXTENDED) {
        MEPA_RC(indy_led_mode_set(dev, mode, data->led_num));
        // Enable alternative gpio mode for led.
        gpio_no = led_num_to_gpio_mapping(dev, data->led_num);
    } else if (mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT1 || mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT2) {
        gpio_no = mode == MEPA_GPIO_MODE_RCVRD_CLK_OUT1 ? 9 : 10;
    }
    if (gpio_no < 16) {
        val = 1 << gpio_no;
        dir = dir << gpio_no;
        EP_WRM(dev, INDY_GPIO_EN2, gpio_en ? val : 0, val);
        if (gpio_en) {
            EP_WRM(dev, INDY_GPIO_DIR2, dir, val);
        }
    } else if (gpio_no < 24) {
        val = 1 << (gpio_no - 16);
        dir = dir << (gpio_no - 16);
        EP_WRM(dev, INDY_GPIO_EN1, gpio_en ? val : 0, val);
        if (gpio_en) {
            EP_WRM(dev, INDY_GPIO_DIR1, dir, val);
        }
    } else {
        // Not supported. Illegal for Indy.
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
    }
    return MEPA_RC_OK;
}

// Set gpio mode to input, output or alternate function
static mepa_rc indy_gpio_mode_set(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    // Indy has 0-23 gpios.
    if (gpio_conf->gpio_no > 23) {
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    rc = indy_gpio_mode_private(dev, gpio_conf);
    MEPA_EXIT(dev);
    return rc;
}
static mepa_rc indy_gpio_out_set(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t value)
{
    uint16_t val = 0;
    phy_data_t *phy_data = (phy_data_t *) dev->data;
    // Indy has 0-23 gpios.
    if (gpio_no > 23) {
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    if (gpio_no < 16) {
        val = 1 << gpio_no;
        EP_WRM(dev, INDY_GPIO_DATA2, value ? val : 0, val);
    } else if (gpio_no < 24) {
        val = 1 << (gpio_no - 16);
        EP_WRM(dev, INDY_GPIO_DATA1, value ? val : 0, val);
    } else {
        // Not supported. Illegal for Indy.
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
    }

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}
static mepa_rc indy_gpio_in_get(mepa_device_t *dev, uint8_t gpio_no, mepa_bool_t * const value)
{
    uint16_t val = 0;
    phy_data_t *phy_data = (phy_data_t *) dev->data;
    // Indy has 0-23 gpios.
    if (gpio_no > 23) {
        T_W(MEPA_TRACE_GRP_GEN, "Not valid gpio on 8814 phy");
        return MEPA_RC_NOT_IMPLEMENTED;
    }
    MEPA_ENTER(dev);
    if (gpio_no < 16) {
        EP_RD(dev, INDY_GPIO_DATA2, &val);
        *value = (val >> gpio_no) & 0x1 ? TRUE : FALSE;
    } else if (gpio_no < 24) {
        EP_RD(dev, INDY_GPIO_DATA1, &val);
        *value = ((val >> (gpio_no - 16)) & 0x1) ? TRUE : FALSE;
    }
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_recovered_clk_set(mepa_device_t *dev, const mepa_synce_clock_conf_t *conf)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    mepa_gpio_conf_t gpio_conf;
    uint16_t divider = 1;
    uint16_t clkout_src = 7;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    // Enable recovered clock outputs in gpio
    gpio_conf.mode = (conf->dst == MEPA_SYNCE_CLOCK_DST_1) ? MEPA_GPIO_MODE_RCVRD_CLK_OUT1 : MEPA_GPIO_MODE_RCVRD_CLK_OUT2;
    rc = indy_gpio_mode_private(dev, &gpio_conf);

    switch(conf->freq) {
        case MEPA_FREQ_25M:
            divider = 5; // 125Mhz/25Mhz = 5
            break;
        case MEPA_FREQ_31_25M:
            divider = 4; // 125Mhz/31.25Mhz = 4
            break;
        case MEPA_FREQ_125M:
        default:
            divider = 1; // 125Mhz/125Mhz = 1
            break;
    }
    switch(conf->src) {
        case MEPA_SYNCE_CLOCK_SRC_DISABLED:
            clkout_src = 7; // Forces Recovered Clock Output to 0
            break;
        case MEPA_SYNCE_CLOCK_SRC_COPPER_MEDIA:
            clkout_src = data->packet_idx;
            //clkout_src = 0b000; // Recovered Clock Input Port-0/Channel-0
            break;
        case MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_1:
            clkout_src = 0b100; // Recovered Clock Input 1
            break;
        case MEPA_SYNCE_CLOCK_SRC_CLOCK_IN_2:
            clkout_src = 0b101; // Recovered Clock Input 2
            break;
        case MEPA_SYNCE_CLOCK_SRC_SERDES_MEDIA:
        default:
            T_W(MEPA_TRACE_GRP_GEN, "Invalid valid clock source, port-no : %d\n", dev->numeric_handle);
            break;
    }
    T_I(MEPA_TRACE_GRP_GEN, "port_ena %d divider %d\n", clkout_src, divider);
    if (conf->dst == MEPA_SYNCE_CLOCK_DST_1) {
        EP_WR(dev, INDY_RCVRD_CLK_OUT_SEL_1, clkout_src);
        EP_WR(dev, INDY_RCVRD_CLK_OUT_DIV_1, divider);
    } else {
        EP_WR(dev, INDY_RCVRD_CLK_OUT_SEL_2, clkout_src);
        EP_WR(dev, INDY_RCVRD_CLK_OUT_DIV_2, divider);
    }

    MEPA_EXIT(dev);

    data->synce_conf = *conf;
    return rc;
}
// Link the base port
static mepa_rc indy_link_base_port(mepa_device_t *dev, mepa_device_t *base_dev, uint8_t packet_idx)
{
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    MEPA_ENTER(dev);
    data->base_dev = base_dev;
    data->packet_idx = packet_idx;
    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

static mepa_rc indy_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    phy_data_t *data = (phy_data_t *)(dev->data);
    phy_data_t *base_data = data->base_dev ? ((phy_data_t *)(data->base_dev->data)) : NULL;

    phy_info->cap = 0;
    phy_info->part_number = 8814;
    phy_info->revision = data->dev.rev;
    phy_info->cap |= (data->dev.model == 0x26) ? MEPA_CAP_TS_MASK_GEN_3: MEPA_CAP_TS_MASK_NONE;
    phy_info->cap |= MEPA_CAP_SPEED_MASK_1G;
    phy_info->ts_base_port = base_data ? base_data->port_no : 0;

    return MEPA_RC_OK;
}

mepa_drivers_t mepa_lan8814_driver_init() {
    static const int nr_indy_drivers = 2;
    static mepa_driver_t indy_drivers[] = {
        {
            .id = 0x221660,  // LAN8814 QSGMII standalone PHY
            .mask = 0xfffff0,
            .mepa_driver_delete = indy_delete,
            .mepa_driver_reset = indy_reset,
            .mepa_driver_poll = indy_poll,
            .mepa_driver_conf_set = indy_conf_set,
            .mepa_driver_conf_get = indy_conf_get,
            .mepa_driver_if_get = indy_if_get,
            .mepa_driver_cable_diag_start = indy_cable_diag_start,
            .mepa_driver_cable_diag_get = indy_cable_diag_get,
            .mepa_driver_probe = indy_probe,
            .mepa_driver_aneg_status_get = indy_aneg_status_get,
            .mepa_driver_clause22_read = indy_direct_reg_read,
            .mepa_driver_clause22_write = indy_direct_reg_write,
            .mepa_driver_clause45_read  = indy_ext_mmd_reg_read,
            .mepa_driver_clause45_write = indy_ext_mmd_reg_write,
            .mepa_driver_event_enable_set = indy_event_enable_set,
            .mepa_driver_event_enable_get = indy_event_enable_get,
            .mepa_driver_event_poll = indy_event_status_poll,
            .mepa_driver_loopback_set = indy_loopback_set,
            .mepa_driver_loopback_get = indy_loopback_get,
            .mepa_driver_gpio_mode_set = indy_gpio_mode_set,
            .mepa_driver_gpio_out_set = indy_gpio_out_set,
            .mepa_driver_gpio_in_get = indy_gpio_in_get,
            .mepa_driver_link_base_port = indy_link_base_port,
            .mepa_ts = &indy_ts_drivers,
            .mepa_driver_synce_clock_conf_set = indy_recovered_clk_set,
            .mepa_driver_phy_info_get = indy_info_get,
        },
        {
            .id = 0x221670,  // Single PHY based on LAN8814 instantiated in LAN966x
            .mask = 0xfffff0,
            .mepa_driver_delete = indy_delete,
            .mepa_driver_reset = indy_reset,
            .mepa_driver_poll = indy_poll,
            .mepa_driver_conf_set = indy_conf_set,
            .mepa_driver_conf_get = indy_conf_get,
            .mepa_driver_if_get = indy_if_get,
            .mepa_driver_cable_diag_start = indy_cable_diag_start,
            .mepa_driver_cable_diag_get = indy_cable_diag_get,
            .mepa_driver_probe = indy_probe,
            .mepa_driver_aneg_status_get = indy_aneg_status_get,
            .mepa_driver_clause22_read = indy_direct_reg_read,
            .mepa_driver_clause22_write = indy_direct_reg_write,
            .mepa_driver_clause45_read  = indy_ext_mmd_reg_read,
            .mepa_driver_clause45_write = indy_ext_mmd_reg_write,
            .mepa_driver_event_enable_set = indy_event_enable_set,
            .mepa_driver_event_enable_get = indy_event_enable_get,
            .mepa_driver_event_poll = indy_event_status_poll,
            .mepa_driver_loopback_set = indy_loopback_set,
            .mepa_driver_loopback_get = indy_loopback_get,
            .mepa_driver_gpio_mode_set = indy_gpio_mode_set,
            .mepa_driver_gpio_out_set = indy_gpio_out_set,
            .mepa_driver_gpio_in_get = indy_gpio_in_get,
            .mepa_driver_synce_clock_conf_set = indy_recovered_clk_set,
            .mepa_driver_phy_info_get = indy_info_get,
        },
    };

    mepa_drivers_t result;
    result.phy_drv = indy_drivers;
    result.count = nr_indy_drivers;

    return result;
}
