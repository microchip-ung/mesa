// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan887x_registers.h"
#include "lan887x_private.h"
#include <string.h>

/* LAN887X is a Single-Port 100/1000BASE-T1 Ethernet Phy*/
/*
 * START of PHY Configurations
 */
static const struct phy_reg_map lan887x_onetime_setup[] = {
    // eFUSE emulation enable
    {MDIO_MMD_VEND1, 0xF003U, 0x0008U},
    // used with EFUSE emulation mode to manually assert the efuse_done signal
    {MDIO_MMD_VEND1, 0xF005U, 0x0010U},
};

static const struct phy_reg_map lan887x_setup[] = {
    // OFFSET +2
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_ZQCAL_OFFSET_REG, 0x8040U},
    // TX_DAC_CLK_SEL=1; LPF = 237.6MHz
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG, 0x0084U},
    // TX_DAC_CLK_SEL=1; LPF = 237.6MHz
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_TX_AMPLT_1000T1_REG, 0x001FU},
    // Clear FIR_LOADER_EN
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_TX_FIR_CTRL_STATUS, 0x0000U},
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_COEFF_2_1_1000T1_REG, 0x0014U},
    // Set FIR_LOADER_EN [bit 0] and FIR_MAX_TAP=7 [bits 5:3]
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_TX_FIR_CTRL_STATUS, 0x0039U},
    // 2. Molineux_A0_BG.txt
    // BG_TC_TRIM = 31, and BG_MAG_TRIM = 0 ==> VBG = 1.2V
    {MDIO_MMD_PMAPMD, LAN887X_COMMON_AFE_COMMON_BLOCK_CONTROL_2, 0x001FU},
    // keep both 600 and 750
    {MDIO_MMD_PMAPMD, LAN887X_T1_AFE_PORT_TESTBUS_CTRL2_REG, 0x0080U},
    //TX_DRV_ENB
    {MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26, LAN887X_MIS_100T1_SMI_REG26_TX_DRV_EN_},
    // TURN_ON_LINK_SYNC
    {MDIO_MMD_PMAPMD, LAN887X_PMA_1000T1_DSP_PMA_CTL_REG, LAN887X_PMA_1000T1_DSP_PMA_LNK_SYNC}
};
/*
 * END of PHY Configurations
 */

static const struct phy_reg_dbg lan887x_regs[] = {
    { "Basic Control Register", 0, MII_BMCR},
    { "Basic Status Register", 0, MII_BMSR},
    { "Device Identifier 1 Register", 0, MII_PHYSID1},
    { "Device Identifier 2 Register", 0, MII_PHYSID2},
    { "MMD Access Control Register", 0, MII_MMD_CTRL},
    { "MMD Access Address/Data Register", 0, MII_MMD_DATA},
    { "chiptop_regs::PMA_CONTROL_T1", MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTRL},
    { "mx_chip_top_regs::SGMII_CTL", MDIO_MMD_VEND1, LAN887X_MX_CHIP_TOP_REG_SGMII_CTL},
    { "mis_regs::MIS_CFG_REG0", MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0},
    { "mis_regs::MIS_DLL_CFG_REG0", MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0},
    { "mis_regs::MIS_DLL_CFG_REG1", MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1},
    { "aneg_regs:ANEG_CNTRL_REG1", MDIO_MMD_AN, 0x200},
    { "aneg_regs:ANEG_STAT_REG1", MDIO_MMD_AN, 0x201},
    { "aneg_regs:ANEG_ADV_REG1", MDIO_MMD_AN, 0x202},
    { "aneg_regs:ANEG_ADV_REG2", MDIO_MMD_AN, 0x203},
    { "aneg_regs:ANEG_ADV_REG3", MDIO_MMD_AN, 0x204},
    { "aneg_regs:ANEG_LP_AB_REG1", MDIO_MMD_AN, 0x205},
    { "aneg_regs:ANEG_LP_AB_REG2", MDIO_MMD_AN, 0x206},
    { "aneg_regs:ANEG_LP_AB_REG3", MDIO_MMD_AN, 0x207},
    { "aneg_regs:VEND_DBG_CTRL_STAT_REG", MDIO_MMD_AN, 0x8013},
    {
        "LAN887X_DEV30_COMMON_TC10_REG_REG15", MDIO_MMD_VEND1,
        LAN887X_DEV30_COMMON_TC10_REG_REG15
    },
    { "LAN887X_DEV30_COMMON_TC10_MISC33", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC33},
    { "LAN887X_DEV30_COMMON_TC10_MISC32", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32},
    { "LAN887X_DEV30_COMMON_TC10_MISC46", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC46},
    { "LAN887X_DEV30_COMMON_TC10_MISC36", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36},
    { "LAN887X_MISC_REGS_MISC37", MDIO_MMD_VEND1, LAN887X_MISC_REGS_MISC37},
    {
        "LAN887X_DEV30_COMMON_TC10_SENDZ_MINWAIT_TMR_CFG", MDIO_MMD_VEND1,
        LAN887X_DEV30_COMMON_TC10_SENDZ_MINWAIT_TMR_CFG
    },
};

#ifdef MEPA_lan887x_static_mem
static mepa_device_t lan887x_device[LAN887X_PHY_MAX];
static phy_data_t lan887x_data[LAN887X_PHY_MAX];
#endif

static mepa_rc lan887x_phy_cable_diag_start(mepa_device_t *dev, mepa_bool_t is_hybrid, mepa_bool_t ms_mode);
static mepa_rc lan887x_reset_phy(mepa_device_t *dev, mepa_bool_t from_confset);
static mepa_rc lan887x_aneg_read_status(mepa_device_t *dev, mepa_status_t *status);

/**********************************
 * Internal APIs
 *********************************/
//Retrieve PHY information
static mepa_rc phy_get_device_info(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    uint32_t id1 = 0, id2 = 0;
    uint16_t val = 0;

    //Init structure
    data->dev.id = ZERO;
    data->dev.model = ZERO;
    data->dev.rev = ZERO;
    data->dev.is_master = PHY_FALSE;
    data->dev.is_master_fault = PHY_FALSE;

    (void) phy_reg_rd(dev, MII_PHYSID1, &val);
    id1 = val;

    val = 0;
    (void) phy_reg_rd(dev, MII_PHYSID2, &val);
    id2 = val;

    //Setup structure
    data->dev.rev   = (uint16_t)GET_PHY_REV(id2);
    data->dev.model = (uint16_t)GET_PHY_MODEL(id2);
    /**
     *  PHY_ID_NUM0: Assigned to the 3rd through 18th bits of the Organizationally Unique Identifier (OUI), respectively.
     */
    data->dev.id = GET_PHY_ID1(id1);
    /**
     *  PHY_ID_NUM1: Assigned to the 19th through 24th bits of the OUI.
     */
    data->dev.id |= GET_PHY_ID2(id2);

    return MEPA_RC_OK;
}

#if 0
static mepa_rc phy_get_link_status(mepa_device_t *const dev, mepa_status_t *const status)
{
    uint16_t reg_val = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    (void) phy_reg_rd(dev, MII_BMSR, &reg_val);

    status->link = (reg_val & BMSR_LSTATUS) ? PHY_LINKUP : PHY_LINKDOWN;
    data->link_status = status->link;

    return MEPA_RC_OK;
}
#endif

//callout print API
static void phy_dbg_pr (mepa_device_t *const dev, const mepa_debug_print_t pr,
                        uint8_t mmd, uint16_t offset, const char *str)
{
    uint16_t value = 0;

    if (MEPA_RC_OK == phy_mmd_reg_rd(dev, mmd, offset, &value)) {
        (void) pr("%-45s:\t[0X%02X].[0X%X]\t=\t%u \r\n", str, mmd, offset, value);
    }
}

//Register dump
static void phy_reg_dump(struct mepa_device *const dev,
                         const mepa_debug_print_t pr,
                         const struct phy_reg_dbg *const regs, const uint8_t reglen)
{
    uint8_t i;
    phy_data_t *data = (phy_data_t *)dev->data;
    uint32_t port_no = data->port_no;
    uint32_t dev_id = dev->drv->id;

    //Direct registers
    (void) pr("************ Register Dump for PHY-0x%x @ Port-%u ************ \r\n", dev_id, port_no);
    (void) pr("%-45s:\tPAGE.REG\t=\tVALUE \r\n", "REG_NAME");
    for (i = 0; i < reglen; i++) {
        phy_dbg_pr(dev, pr, regs[i].mmd, regs[i].reg, regs[i].string);
    }
}

//Configure set of registers
static void phy_cfg_regs(mepa_device_t *const dev, const struct phy_reg_map *regs, const uint8_t reglen, const mepa_bool_t is_rmw)
{
    uint8_t i;

    if (!is_rmw) {
        for (i = 0; i < reglen; i++) {
            (void) phy_mmd_reg_wr(dev, regs[i].mmd, regs[i].offset, regs[i].val);
        }
    } else {
        for (i = 0; i < reglen; i++) {
            (void) phy_mmd_reg_modify(dev, regs[i].mmd, regs[i].offset, regs[i].val, regs[i].val);
        }
    }
}

static mepa_rc phy_c45_get_link_status(mepa_device_t *const dev, mepa_status_t *const status)
{
	mepa_rc rc = MEPA_RC_ERROR;
    uint16_t reg_val = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    //LATCH-LOW BIT
    rc = phy_mmd_reg_rd(dev, MDIO_MMD_PMAPMD, MDIO_STAT1, &reg_val);
    rc = phy_mmd_reg_rd(dev, MDIO_MMD_PMAPMD, MDIO_STAT1, &reg_val);
    if (rc == MEPA_RC_OK) {
		status->link = ((reg_val & MDIO_STAT1_LSTATUS) != ZERO);
		data->link_status = status->link;
    }

    //T_D( MEPA_TRACE_GRP_GEN, "Link Status is %s!!\n", (data->link_status ? "UP" : "DOWN"));

    return rc;
}

static mepa_rc lan887x_config_led(mepa_device_t *const dev, const mepa_gpio_conf_t *conf)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t reg_offset = LAN887X_CHIPTOP_COMM_LED3_LED2;
    uint16_t reg_val = LAN887X_CHIPTOP_LED_LINK_ACT_ANY_SPEED;

    switch (conf->mode) {
    case MEPA_GPIO_MODE_LED_LINK1000_ACTIVITY:
        reg_val = LAN887X_CHIPTOP_LED_LINK_ACT_1000_SPEED;
        break;
    case MEPA_GPIO_MODE_LED_LINK100_ACTIVITY:
        reg_val = LAN887X_CHIPTOP_LED_LINK_ACT_100_SPEED;
        break;
    case MEPA_GPIO_MODE_LED_LINK_NO_ACT_ANY_SPEED:
        reg_val = LAN887X_CHIPTOP_LED_LINK_NO_ACT_ANY_SPEED;
        break;
    case MEPA_GPIO_MODE_LED_LOCAL_RXER_STATUS:
        reg_val = LAN887X_CHIPTOP_LED_LOCAL_RXER_STATUS;
        break;
    case MEPA_GPIO_MODE_LED_REMOTE_RXER_STATUS:
        reg_val = LAN887X_CHIPTOP_LED_REMOTE_RXER_STATUS;
        break;
    case MEPA_GPIO_MODE_LED_NEGOTIATED_SPEED:
        reg_val = LAN887X_CHIPTOP_LED_NEGOTIATED_SPEED;
        break;
    case MEPA_GPIO_MODE_LED_MASTER_SLAVE_MODE:
        reg_val = LAN887X_CHIPTOP_LED_MASTER_SLAVE_MODE;
        break;
    case MEPA_GPIO_MODE_LED_PCS_TX_ERR_STATUS:
        reg_val = LAN887X_CHIPTOP_LED_PCS_TX_ERR_STATUS;
        break;
    case MEPA_GPIO_MODE_LED_PCS_RX_ERR_STATUS:
        reg_val = LAN887X_CHIPTOP_LED_PCS_RX_ERR_STATUS;
        break;
    case MEPA_GPIO_MODE_LED_PCS_TX_ACTIVITY:
        reg_val = LAN887X_CHIPTOP_LED_PCS_TX_ACTIVITY;
        break;
    case MEPA_GPIO_MODE_LED_PCS_RX_ACTIVITY:
        reg_val = LAN887X_CHIPTOP_LED_PCS_RX_ACTIVITY;
        break;
    case MEPA_GPIO_MODE_LED_WAKE_ON_LAN:
        reg_val = LAN887X_CHIPTOP_LED_WAKE_ON_LAN;
        break;
    case MEPA_GPIO_MODE_LED_FORCE_LED_OFF:
        reg_val = LAN887X_CHIPTOP_LED_FORCED_LED_OFF;
        break;
    case MEPA_GPIO_MODE_LED_FORCE_LED_ON:
        reg_val = LAN887X_CHIPTOP_LED_FORCED_LED_ON;
        break;
    case MEPA_GPIO_MODE_LED_LINK_ACTIVITY:
        reg_val = LAN887X_CHIPTOP_LED_LINK_ACT_ANY_SPEED;
        break;
    default:
        rc = MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED;
        break;
    }

    if (rc == MEPA_RC_OK) {
        //updata metadata
        (void) memcpy(&data->led3_conf, conf, sizeof(mepa_gpio_conf_t));
        rc = phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, reg_offset, reg_val);
    }

    return rc;
}

static mepa_rc lan887x_setup_lpbk(mepa_device_t *const dev, const mepa_loopback_t *loopback)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t val = 0;
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t mask = (LAN887X_MIS_CFG_REG2_FE_LPBK_EN |
                     LAN887X_MIS_CFG_REG2_NE_LPBK_EN |
                     LAN887X_MIS_CFG_REG2_IO_LPBK_EN);

    (void) memset(&data->loopback, 0, sizeof(mepa_loopback_t));

    //if loopback == NULL, it could be during init clear loopback case
    if (loopback != NULL) {
        if (loopback->far_end_ena == PHY_TRUE) {
            val = LAN887X_MIS_CFG_REG2_FE_LPBK_EN;
            data->loopback.far_end_ena = PHY_TRUE;
        } else if (loopback->near_end_ena == PHY_TRUE) {
            val = LAN887X_MIS_CFG_REG2_NE_LPBK_EN;
            data->loopback.near_end_ena = PHY_TRUE;
        } else {
            if (loopback->connector_ena == PHY_TRUE) {
                MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                                LAN887X_CHIPTOP_COMM_REG_1,
                                                LAN887X_CHIPTOP_COMM_REG_1_AFE_LPBK_EN));
                data->loopback.connector_ena = PHY_TRUE;
            } else {
                MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                                LAN887X_CHIPTOP_COMM_REG_1, 0x0U));
            }
        }
    }

    // Enable/Disable loopback
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1,
                                        LAN887X_MIS_CFG_REG2, mask, val));
    rc = MEPA_RC_OK;

error:
    return rc;
}

static void lan887x_phy_100m_cfg_script(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (data->conf.mac_if_aneg_ena == PHY_FALSE) {
        // MLNX_MISC_SPEED_100T1
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                            LAN887X_PMA_COMM_100T1_CTL_T1,
                                            LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_MASK,
                                            LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_100));
    }

    // MLNX_100T1_000
    // RMW PORT_AFE->AFE_PORT_TESTBUS_CTRL4->bit 7 = 1
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                        ((uint16_t)LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG),
                                        0x0080U, 0x0080U));
error:
    return;
}

static void lan887x_phy_1000m_cfg_script(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (data->conf.mac_if_aneg_ena == PHY_FALSE) {
        // MLNX_MISC_SPEED_1000T1
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD, LAN887X_PMA_COMM_100T1_CTL_T1,
                                            LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_MASK,
                                            LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_1000));
    }

    // MLNX_1000T1_000
    // RMW PORT_AFE->AFE_PORT_TESTBUS_CTRL4->bit 7 = 1
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                        LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG, 0x0084U, 0x0084U));

    // ECHO_DELAY_CONFIG
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, 0x8ECU, 0x0024U));

error:
    return;
}

static void lan887x_link_setup(mepa_device_t *const dev, mesa_port_speed_t speed)
{
    // speed specific initialization
    if (speed == MESA_SPEED_100M) {
        lan887x_phy_100m_cfg_script(dev);
    } else {
        lan887x_phy_1000m_cfg_script(dev);
    }
}

static mepa_rc lan887x_master_slave_mode_set(mepa_device_t *const dev, const mepa_bool_t value)
{
    uint16_t reg_val = 0;

    if (value) {
        reg_val = MDIO_PMA_PMD_BT1_CTRL_CFG_MST;
    }

    return phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTRL,
                              MDIO_PMA_PMD_BT1_CTRL_CFG_MST, reg_val);
}

static mepa_rc lan887x_rgmii_setup(mepa_device_t *const dev, mepa_port_interface_t mac_if)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_bool_t rgmii_set = PHY_TRUE;
    uint16_t txc = 0;
    uint16_t rxc = 0;

    // Disable SGMII_CTL
    MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                            LAN887X_MX_CHIP_TOP_REG_SGMII_CTL,
                                            LAN887X_MX_CHIP_TOP_REG_SGMII_MUX_EN));

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0, &txc));

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1, &rxc));

    switch (mac_if) {
    case MESA_PORT_INTERFACE_RGMII:
        txc &= ((~LAN887X_MIS_DLL_EN_) & 0xFFFFU);
        rxc &= ((~LAN887X_MIS_DLL_EN_) & 0xFFFFU);
        break;
    case MESA_PORT_INTERFACE_RGMII_ID:
        txc |= LAN887X_MIS_DLL_EN_;
        rxc |= LAN887X_MIS_DLL_EN_;
        break;
    case MESA_PORT_INTERFACE_RGMII_RXID:
        txc &= ((~LAN887X_MIS_DLL_EN_) & 0xFFFFU);
        rxc |= LAN887X_MIS_DLL_EN_;
        break;
    case MESA_PORT_INTERFACE_RGMII_TXID:
        txc |= LAN887X_MIS_DLL_EN_;
        rxc &= ((~LAN887X_MIS_DLL_EN_) & 0xFFFFU);
        break;
    default:
        rgmii_set = PHY_FALSE;
        T_I( MEPA_TRACE_GRP_GEN, "PHY MAC interface is not RGMII(%d)!\n", mac_if);
        rc = MEPA_RC_OK;
        break;
    }

    if (rgmii_set) {
        // Enable RGMII
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                            LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL,
                                            LAN887X_MIS_CFG_REG0_MAC_MODE_RGMII));

        // Set RX DELAY
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1,
                                            LAN887X_MIS_DLL_EN_, rxc));

        // Set TX DELAY
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0,
                                            LAN887X_MIS_DLL_EN_, txc));

        T_I( MEPA_TRACE_GRP_GEN, "PHY RGMII setup complete!\n");
    }
    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_int_events_set(struct mepa_device *dev, mepa_event_t event, mesa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint32_t tmp_evt = (event & LAN887X_DEF_MASK);
    uint16_t int_mask = LAN887X_DEF_MASK, i;
    phy_data_t *data = (phy_data_t *)dev->data;

    data->events = enable ? (data->events | tmp_evt) : (data->events & ~tmp_evt);
    for (i = 0; i < INTR_BIT_LEN; i++) {
        uint16_t mask = BIT(i);
        if ((data->events & mask) != ZERO) {
            int_mask = int_mask &  ~mask;
        }
    }
    rc = phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                        LAN887X_MX_CHIP_TOP_REG_INT_MSK, int_mask);

    /* T_D( MEPA_TRACE_GRP_GEN, "set events=0x%x, int_mask=0x%x! rc=%d\r\n",
            data->events, int_mask, rc); */

    return rc;
}

static mepa_rc lan887x_init_phy(mepa_device_t *const dev, mepa_bool_t from_confset)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    if (!data->init_done) {
        data->init_done = PHY_TRUE;

        //FIXME: LAN887X A0 onetime eFuse setup
        phy_cfg_regs(dev, lan887x_onetime_setup, ARRAY_SIZE(lan887x_onetime_setup), PHY_TRUE);

        T_I( MEPA_TRACE_GRP_GEN, "PHY efuse setup complete!\n");
    }

    //Setup events
    MEPA_RC_GOTO(rc, lan887x_int_events_set(dev, data->events, PHY_TRUE));

    //LAN887X A0 PHY Setup
    phy_cfg_regs(dev, lan887x_setup, ARRAY_SIZE(lan887x_setup), PHY_FALSE);

    //setup SGMII/RGMII interface
    MEPA_RC_GOTO(rc, lan887x_rgmii_setup(dev, data->mac_if));

    //LED setup
    MEPA_RC_GOTO(rc, lan887x_config_led(dev, &data->led3_conf));

    if (from_confset == PHY_FALSE) {
        //clear isolate bit
        MEPA_RC_GOTO(rc, phy_reg_clear_bits(dev, MII_BMCR, BMCR_ISOLATE));

        //clear loopback if it is setup in prev. config
        MEPA_RC_GOTO(rc, lan887x_setup_lpbk(dev, NULL));

    }

    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_init_conf(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t reg_speed = BMCR_FULLDPLX;
    uint16_t reg_mask = (BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000);
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_manual_neg_t mode_ms = data->conf.man_neg;

    // speed selection based on media type
    if ((data->media_intf == MESA_PHY_MEDIA_IF_T1_100FX) ||
        ((data->media_intf == MESA_PHY_MEDIA_IF_T1_1000FX) &&
         (data->conf.mac_if_aneg_ena == PHY_FALSE) &&
         (data->conf.speed == MESA_SPEED_100M))) {
        //Update speed incase if it is not 100 when 100M media is selected
        data->conf.speed = MESA_SPEED_100M;
        reg_speed |= BMCR_SPEED100;
    } else {
        data->conf.speed = MESA_SPEED_1G;
        reg_speed |= BMCR_SPEED1000;
    }

    if (data->conf.admin.enable == PHY_FALSE) {
        //Power down
        MEPA_RC_GOTO(rc, phy_reg_set_bits(dev, MII_BMCR, BMCR_PDOWN));
    } else {
        //clear power down bit
        MEPA_RC_GOTO(rc, phy_reg_clear_bits(dev, MII_BMCR, BMCR_PDOWN));
        if (data->conf.mac_if_aneg_ena == PHY_TRUE) {
            u16 adv_r1 = 0;
            u16 adv_r2_mask = 0;
            u16 adv_r2 = 0;

            // Clear ANEG Master/Slave
            MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_L, &adv_r1));

            //clear Force MS bit
            adv_r1 &= ((~MDIO_AN_T1_ADV_L_FORCE_MS) & LAN887X_DEF_MASK);

            adv_r2_mask = (MDIO_AN_T1_ADV_M_B1000 |
                           MDIO_AN_T1_ADV_M_B100 |
                           MDIO_AN_T1_ADV_M_MST);

            // Advertise preferred master/slave mode
            if (mode_ms != MEPA_MANUAL_NEG_CLIENT) {
                adv_r2 |= MDIO_AN_T1_ADV_M_MST;
            }

            // Advertise speeds based on media type
            if (data->conf.speed == MESA_SPEED_100M) {
                data->conf.aneg.speed_100m_fdx = PHY_TRUE;
                data->conf.aneg.speed_1g_fdx = PHY_FALSE;
                adv_r2 |= MDIO_AN_T1_ADV_M_B100;
            } else {
                data->conf.aneg.speed_1g_fdx = PHY_TRUE;
                data->conf.aneg.speed_100m_fdx = PHY_TRUE;
                adv_r2 |= MDIO_AN_T1_ADV_M_B100 | MDIO_AN_T1_ADV_M_B1000;
            }

            MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_M, adv_r2_mask, adv_r2));

            /* NOTE:
             *  The Base Page value is transferred to mr_adv_ability when register 7.514 is written.
             *  Therefore, registers 7.515 and 7.516 should be written before 7.514.
             */
            MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_L, adv_r1));
        } else {
            //Disable aneg
            MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_AN, MDIO_AN_T1_CTRL,
                                                    MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART));

            /* Setup MASTER/SLAVE */
            MEPA_RC_GOTO(rc, lan887x_master_slave_mode_set(dev, (mode_ms == MEPA_MANUAL_NEG_REF)));

            /* Setup Speed */
            MEPA_RC_GOTO(rc, phy_reg_modify(dev, MII_BMCR, reg_mask, reg_speed));
        }

        // MLX 100/1000 link setup
        lan887x_link_setup(dev, data->conf.speed);

        if (data->conf.mac_if_aneg_ena == PHY_TRUE) {
            MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_AN, MDIO_AN_T1_CTRL,
                                                  MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART));
        }
    }

    T_I( MEPA_TRACE_GRP_GEN, "PHY setup complete!\n");
    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_config_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_bool_t re_config = PHY_FALSE;

    /** Mode and speed settings are as following
     * Speed Settings are advertised as following
     *
     *  Autoneg:
     *      Speed will be advertised based on media type.
     *      if media type is 100M then,
     *          advertised speed is 100M
     *      otherwise
     *          advertised speed is 100M and 1000M
     *  Fixed Speeds:
     *      speed = (100Mbps or 1000Mbps)
     *
     * Mode Settings are advertised as following
     *  Autoneg:
     *      When mode = MEPA_MANUAL_NEG_REF,
     *          Mode = Preferred master
     *      When mode = MEPA_MANUAL_NEG_CLIENT,
     *          Mode = Preferred slave
     *  Fixed Mode:
     *      When mode = MEPA_MANUAL_NEG_REF,
     *          Mode = Forced master
     *      When mode = MEPA_MANUAL_NEG_CLIENT,
     *          Mode = Forced slave
     *
     * fdx always enabled.
     * AUTO is treated as 1G speed always
     *
     */
    if ((config->man_neg != MEPA_MANUAL_NEG_CLIENT &&
         config->man_neg != MEPA_MANUAL_NEG_REF) ||
        (config->fdx != PHY_TRUE) ||
        (config->speed != MESA_SPEED_100M &&
         config->speed != MESA_SPEED_1G &&
         config->speed != MESA_SPEED_AUTO)) {
        rc = MEPA_RC_ERR_PARM;
    } else {
        //AUTO is always 1G
        mesa_port_speed_t speed = config->speed;

        if (speed == MESA_SPEED_AUTO) {
            speed = MESA_SPEED_1G;
        }

        data->conf.fdx = PHY_TRUE;
        data->conf.flow_control = config->flow_control;

        if (!data->init_done) {
            data->conf.mac_if_aneg_ena = config->mac_if_aneg_ena;
            data->conf.speed = speed;
            data->conf.admin.enable = config->admin.enable;
            data->conf.man_neg = config->man_neg;

            MEPA_RC_GOTO(rc, lan887x_init_conf(dev));
            data->init_done = PHY_TRUE;
        }

        // Check if aneg is changed
        if (data->conf.mac_if_aneg_ena != config->mac_if_aneg_ena) {
            re_config = PHY_TRUE;
            data->conf.mac_if_aneg_ena = config->mac_if_aneg_ena;
            //Due to chip bug, we need to reset PHY
            MEPA_RC_GOTO(rc, lan887x_reset_phy(dev, PHY_TRUE));
        }

        // Setup Speed
        if (data->conf.speed != speed) {
            if (data->conf.mac_if_aneg_ena == PHY_TRUE) { /*speed change will be rejected when aneg is enabled */
                rc = MEPA_RC_ERR_PARM;
                goto error;
            } else if (speed != MESA_SPEED_100M &&
                       data->media_intf == MESA_PHY_MEDIA_IF_T1_100FX) { /* speed change to other than 100M will be rejected when media type is 100M */
                rc = MEPA_RC_ERR_PARM;
                goto error;
            } else {
                re_config = PHY_TRUE;
                data->conf.speed = speed;
            }
        }

        // Setup Master/Slave Mode
        if (data->conf.man_neg != config->man_neg) {
            re_config = PHY_TRUE;
            data->conf.man_neg = config->man_neg;
        }

        // handle admin enable/disable
        if (data->conf.admin.enable != config->admin.enable) {
            re_config = PHY_TRUE;
            data->conf.admin.enable = config->admin.enable;
            if (data->conf.admin.enable == PHY_TRUE) {
                //Due to chip bug, we need to reset PHY
                MEPA_RC_GOTO(rc, lan887x_reset_phy(dev, PHY_TRUE));
            }
        }

        if (re_config == PHY_TRUE) {
            MEPA_RC_GOTO(rc, lan887x_init_conf(dev));
        }

        rc = MEPA_RC_OK;
    }

error:
    return rc;
}

static uint32_t lan887x_get_sqi_100m(mepa_device_t *dev)
{
    mepa_rc rc;
    uint16_t temp;
    int32_t i, j;
    uint32_t sqiavg = 0, linkavg = 0;
    uint32_t sqinum = 0;
    uint16_t rawtable[200];
    uint8_t linktable[200];
    phy_data_t *data = (phy_data_t *) dev->data;

    (void) memset(rawtable, 0, sizeof(rawtable));
    (void) memset(linktable, 1, sizeof(linktable));

    // method 1 config
    (void) phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, 0x404U, 0x16D6U);
    (void) phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, 0x42EU, 0x9572U);

    rc = phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x042EU, &temp);
    if ( rc < 0 || temp != 0x9572U) {
        T_I( MEPA_TRACE_GRP_GEN, "not configured properly\n");
        return 0;
    }

    (void) phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, 0x40dU, 0x0001U, 0x0001U);

    LAN887X_NSLEEP(50U);

    // get 200 raw readings
    for (i = 0; i < 200; i++) {
        (void) phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, 0x40dU, 0x0001U);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x483U, &temp);
        rawtable[i] = temp;
        linktable[i] = ((data->link_status == PHY_TRUE) ? 1U : 0U);
    }
    // sort raw sqi values in ascending order
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 200; j++) {
            if (rawtable[j] > rawtable[i]) {
                uint8_t linktemp;

                temp = rawtable[i]; // sqi values
                rawtable[i] = rawtable[j];
                rawtable[j] = temp;

                linktemp = linktable[i]; // link statuses
                linktable[i] = linktable[j];
                linktable[j] = linktemp;
            }
        }
    }
    // sum middle 120 values
    for (i = 0; i < 200; i++) {
        if (i >= 40 && i < 160) {
            sqiavg += rawtable[i];
        }
        linkavg += linktable[i];
    }

    // get averages
    sqiavg /= 120U;
    linkavg /= 200U;

    if (sqiavg >= 299U) {
        sqinum = ZERO;
    } else if (sqiavg >= 237U) {
        sqinum = 1U;
    } else if (sqiavg >= 189U) {
        sqinum = 2U;
    } else if (sqiavg >= 150U) {
        sqinum = 3U;
    } else if (sqiavg >= 119U) {
        sqinum = 4U;
    } else if (sqiavg >= 94U) {
        sqinum = 5U;
    } else if (sqiavg >= 75U) {
        sqinum = 6U;
    } else if (sqiavg > ZERO) {
        sqinum = 7U;
    } else {
        sqinum = ZERO;
    }

    if (linkavg < 1U) {
        sqinum = ZERO;
    }
    T_I( MEPA_TRACE_GRP_GEN, "sqiavg=%d, linkavg=%d, sqinum=%d\n", sqiavg, linkavg, sqinum);

    return sqinum;
}

static uint32_t lan887x_get_sqi(mepa_device_t *const dev)
{
    int32_t count = 0;
    uint16_t sqi_value = 0;
    phy_data_t *data = (phy_data_t *) dev->data;
    uint16_t val = 0;
    mepa_status_t link_status;
    mesa_port_speed_t speed = data->conf.speed;

    // Resolve speed
    if (data->conf.mac_if_aneg_ena == PHY_TRUE) {
        (void) lan887x_aneg_read_status(dev, &link_status);
        speed = link_status.speed;
    }

    //verify speed
    if (speed != MESA_SPEED_100M &&
        speed != MESA_SPEED_1G &&
        speed != MESA_SPEED_AUTO) {
        T_I( MEPA_TRACE_GRP_GEN, "invalid speed!!\n");
        goto done;
    }

    (void)  phy_c45_get_link_status(dev, &link_status);
    // If link is down
    if (data->link_status == PHY_LINKDOWN) {
        T_I( MEPA_TRACE_GRP_GEN, "Link is Down!!\n");
        goto done;
    }

    if (speed == MESA_SPEED_100M) {
        return lan887x_get_sqi_100m(dev);
    }

    (void) phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                LAN887X_DSP_REGS_COEFF_MOD_CONFIG,
                                LAN887X_DSP_REGS_COEFF_MOD_CONFIG_DCQ_COEFF_EN);

    /* Waiting time for register to get clear */
    do {
        //FIXME: Should we wait more time???
        LAN887X_NSLEEP(200U);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                              LAN887X_DSP_REGS_COEFF_MOD_CONFIG, &val);
        if ((val & 0x0100U) != 0x0100U) {
            break;
        }

        count++;
    } while (count < 20);

    if (count >= 20) {
        goto done;
    }

    (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                          LAN887X_DSP_REGS_DCQ_SQI_STATUS, &val);

    //FIXME: Check the bit shifting
    sqi_value = (T1_DCQ_SQI_MSK & val) >> 1U;

done:
    return sqi_value;
}

static mepa_rc lan887x_reset_phy(mepa_device_t *dev, mepa_bool_t from_confset)
{
    mepa_rc rc = MEPA_RC_OK;

    /**
     * NOTE: UNG_MOLINEUX-675
     *   CL22 RESET(2) bit is causing link issues
     *   Even interrupts are not properly generated
     *   So use MX_CHIP_TOP:CHIP_SOFT_RST registers
     */
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                    LAN887X_MX_CHIP_TOP_REG_SOFT_RST,
                                    LAN887X_MX_CHIP_TOP_RESET_));
    LAN887X_NSLEEP(50U);

    //setup phy & work arounds after reset
    MEPA_RC_GOTO(rc, lan887x_init_phy(dev, from_confset));

error:
    return rc;
}

static mepa_rc lan887x_int_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    T_I( MEPA_TRACE_GRP_GEN, "Initializing PHY! \r\n");
    if ((rst_conf != NULL) &&
        ((rst_conf->media_intf == MESA_PHY_MEDIA_IF_T1_100FX) ||
         (rst_conf->media_intf == MESA_PHY_MEDIA_IF_T1_1000FX))) {
        //re-configure media interface
        data->media_intf = rst_conf->media_intf;
    }

    //reset PHY
    MEPA_RC_GOTO(rc, lan887x_reset_phy(dev, PHY_FALSE));

    //initialize PHY with configuration
    MEPA_RC_GOTO(rc, lan887x_init_conf(dev));

    MEPA_RC_GOTO(rc, phy_get_device_info(dev));
    T_I( MEPA_TRACE_GRP_GEN, "phy_info phy_id=0x%x, mode=%s[fault=%u],"
         "model=0x%x, rev=%u, error=%d  \r\n",
         data->dev.id, (data->dev.is_master ? "master" : "slave"),
         data->dev.is_master_fault, data->dev.model, data->dev.rev, rc);

error:
    return rc;
}

struct cable_test_start {
    uint16_t reg;
    uint16_t value;
};

static mepa_rc lan887x_cable_test_report(mepa_device_t *const dev, mepa_bool_t ms_mode)
{
    uint16_t pos_peak_cycle_hybrid = 0, pos_peak_in_phases_hybrid = 0;
    uint16_t pos_peak = 0, neg_peak = 0;
    uint16_t pos_peak_cycle = 0, neg_peak_cycle = 0;
    uint16_t pos_peak_phase = 0, neg_peak_phase = 0;
    uint16_t pos_peak_time = 0,  neg_peak_time = 0;
    uint16_t pos_peak_in_phases = 0, neg_peak_in_phases = 0;
    uint16_t pos_peak_phase_hybrid = 0, pos_peak_time_hybrid = 0;
    uint16_t gain_idx = 0, diff_dist = 0;

    const uint16_t noise_margin = 20U, time_margin = 89U;
    const uint16_t min_time_diff = 96U, max_time_diff = 96U + time_margin;
    mepa_bool_t  fault = PHY_FALSE;
    mepa_bool_t diagTimeout = PHY_FALSE;
    mepa_bool_t bDone = PHY_FALSE;
    mepa_rc rc = MEPA_RC_INCOMPLETE;
    float distance = -1.0F;
    int16_t detect = -1;

    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_cable_diag_result_t *res = &(data->cd_res);

    mepa_mtimer_t   timer = { 0 };

    LAN887X_MTIMER_START(&timer, 4000U);

    res->status[0] = MESA_VERIPHY_STATUS_ABNORM;
    // wait for cable diag to finish or timeout (4 seconds)
    while (bDone == PHY_FALSE && diagTimeout == PHY_FALSE) {
        uint16_t tmp = 0;

        diagTimeout = MEPA_MTIMER_TIMEOUT(&timer);
        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100, &tmp);
        if ((tmp & LAN887X_DSP_REGS_START_CBL_DIAG_DONE) == LAN887X_DSP_REGS_START_CBL_DIAG_DONE) {
            bDone = PHY_TRUE;
        }
    }

    // return diagnostic error if timeout occurred
    if (diagTimeout == PHY_TRUE) {
        T_E( MEPA_TRACE_GRP_GEN, "PHY diags error\r\n");
    } else {
        rc = MEPA_RC_OK;

        /* stop cable diag */
        (void) phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                      LAN887X_DSP_REGS_START_CBL_DIAG_EN);
        // read non-hybrid results
        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x497U, &gain_idx);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x49AU, &neg_peak);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x49DU, &neg_peak_time);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x499U, &pos_peak);

        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x49CU, &pos_peak_time);

        // calculate non-hybrid values
        pos_peak_cycle = (pos_peak_time >> 7) & 0x7FU;
        pos_peak_phase = pos_peak_time & 0x7FU;
        pos_peak_in_phases = (pos_peak_cycle * 96U) + pos_peak_phase;
        /* T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag non-hybrid POS results! pos_peak_time=%d, pos_peak_cycle=%d, pos_peak_phase=%d, pos_peak_in_phases=%d\r\n",
                    pos_peak_time, pos_peak_cycle, pos_peak_phase, pos_peak_in_phases); */

        neg_peak_cycle = (neg_peak_time >> 7) & 0x7FU;
        neg_peak_phase = neg_peak_time & 0x7FU;
        neg_peak_in_phases = (neg_peak_cycle * 96U) + neg_peak_phase;
        /* T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag non-hybrid NEG results! neg_peak_time%d, neg_peak_cycle=%d, neg_peak_phase=%d, neg_peak_in_phases=%d\r\n",
                neg_peak_time, neg_peak_cycle, neg_peak_phase, neg_peak_in_phases); */
        /* Deriving the status of cable */
        if ((pos_peak_in_phases > neg_peak_in_phases) &&
            ((pos_peak_in_phases - neg_peak_in_phases) >= min_time_diff) &&
            ((pos_peak_in_phases - neg_peak_in_phases) < max_time_diff)) {
            detect = 2;
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag detect 2!\r\n");
        } else if ((neg_peak_in_phases > pos_peak_in_phases) &&
                   ((neg_peak_in_phases - pos_peak_in_phases) >= min_time_diff) &&
                   ((neg_peak_in_phases - pos_peak_in_phases) < max_time_diff)) {
            detect = 1;
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag detect 1!\r\n");
        } else {
            detect = -1;
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag detect -1!\r\n");
        }

        if ((pos_peak > noise_margin) && (neg_peak > noise_margin) && (gain_idx > ZERO)) {
            fault = (detect == 1 || detect == 2);
        }

        if (!fault) {
            detect = 0;
            distance = 0.0F;
            /*** SOFT RESET to restore configuration ***/
            MEPA_RC_GOTO(rc, lan887x_int_reset(dev, NULL));
        } else {

            //For Hybrid values
            LAN887X_MTIMER_START(&timer, 4000U);
            MEPA_RC_GOTO(rc, lan887x_phy_cable_diag_start(dev, PHY_TRUE, ms_mode));
            diagTimeout = bDone = PHY_FALSE;
            // wait for cable diag to finish or timeout (4 seconds)
            while (bDone == PHY_FALSE && diagTimeout == PHY_FALSE) {
                uint16_t tmp = 0;

                diagTimeout = MEPA_MTIMER_TIMEOUT(&timer);
                (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100, &tmp);
                if ((tmp & LAN887X_DSP_REGS_START_CBL_DIAG_DONE) == LAN887X_DSP_REGS_START_CBL_DIAG_DONE) {
                    bDone = PHY_TRUE;
                }
            }
            // return diagnostic error if timeout occurred
            if (diagTimeout == PHY_TRUE) {
                T_E( MEPA_TRACE_GRP_GEN, "PHY diags error\r\n");
                rc = MEPA_RC_INCOMPLETE;
            } else {
                /* stop cable diag */
                (void) phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                              LAN887X_DSP_REGS_START_CBL_DIAG_EN);

                /* read hybrid results */
                (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x49CU, &pos_peak_time_hybrid);

                /*** SOFT RESET to restore configuration ***/
                (void) lan887x_int_reset(dev, NULL);

                /* calculate hybrid values */
                pos_peak_cycle_hybrid = (pos_peak_time_hybrid >> 7) & 0x7FU;
                pos_peak_phase_hybrid = pos_peak_time_hybrid & 0x7FU;
                pos_peak_in_phases_hybrid = (pos_peak_cycle_hybrid * 96U) + pos_peak_phase_hybrid;

                /* float wavePropagationVelocity = 0.6811 * 2.9979;
                 * distance = (neg_peak_in_phases - pos_peak_in_phases) * 156.2499 *
                 * 0.0001 * wavePropagationVelocity * 0.5;
                 * distance = (neg_peak_in_phases - pos_peak_in_phases)
                 * * 0.0159520967437766;
                 */
                if (detect == 2) {
                    diff_dist = (neg_peak_in_phases - pos_peak_in_phases_hybrid);
                } else {
                    diff_dist = (pos_peak_in_phases - pos_peak_in_phases_hybrid);
                }
                distance = ((((float)diff_dist) * 15953.0F) / 1000000.0F);
            }
        }

        /* Set cable length.
         * Note: Length will have no decimal part as it is defined
         * in unsigned int and have variation of -/+ 1 meter.
         */
        res->length[0] = ((uint8_t)distance) & 0xFFU;

        // Set status
        switch (detect) {
        case 2:
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status SHORT!\r\n");
            res->status[0] = MESA_VERIPHY_STATUS_SHORT;
            break;
        case 0:
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status OK!\r\n");
            res->status[0] = MESA_VERIPHY_STATUS_OK;
            break;
        case 1:
        default:
            //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status OPEN!\r\n");
            res->status[0] = MESA_VERIPHY_STATUS_OPEN;
            break;
        }
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_cable_diag_start(mepa_device_t *dev, mepa_bool_t is_hybrid, mepa_bool_t ms_mode)
{
    static const struct cable_test_start values[] = {
        {LAN887X_DSP_REGS_MAX_PGA_GAIN_100, 0x1FU},
        {LAN887X_DSP_REGS_MIN_PGA_GAIN_100, 0x0U},
        {LAN887X_DSP_REGS_CBL_DIAG_TDR_THRESH_100, 0x1U},
        {LAN887X_DSP_REGS_CBL_DIAG_AGC_THRESH_100, 0x3cU},
        {LAN887X_DSP_REGS_CBL_DIAG_MIN_WAIT_CONFIG_100, 0x0U},
        {LAN887X_DSP_REGS_CBL_DIAG_MAX_WAIT_CONFIG_100, 0x46U},
        {LAN887X_DSP_REGS_CBL_DIAG_CYC_CONFIG_100, 0x5AU},
        {LAN887X_DSP_REGS_CBL_DIAG_TX_PULSE_CONFIG_100, 0x44D5U},
        {LAN887X_DSP_REGS_CBL_DIAG_MIN_PGA_GAIN_100, 0x0U},

    };
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_INV_STATE;
    uint8_t i;

    if (data->init_done && data->conf.admin.enable) {
        //setup master/slave based on ms_mode
        uint16_t ms_val = (ms_mode == PHY_TRUE ? LAN887X_PMA_COMM_100T1_CTL_T1_MAS_SLV_CFG : 0U);

        rc = MEPA_RC_OK;

        /* Disable Autoneg */
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_AN, MDIO_CTRL1, MDIO_AN_CTRL1_ENABLE));

        /*** SOFT RESET ONLY ***/
        MEPA_RC_GOTO(rc, lan887x_reset_phy(dev, PHY_FALSE));

        /* Forcing DUT to master mode, avoids headaches and
         * we don't care about mode during diagnostics
         */
        MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_PMAPMD, LAN887X_PMA_COMM_100T1_CTL_T1, ms_val));

        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1,
                                            LAN887X_DSP_CALIB_CONFIG_100, 0x0U,
                                            LAN887X_DSP_CALIB_CONFIG_100_VAL));

        /* HW_INIT 100T1, Get DUT running in 100T1 mode */
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26,
                                            LAN887X_MIS_100T1_SMI_REG26_SEL_,
                                            LAN887X_MIS_100T1_SMI_REG26_SEL_));

        for (i = 0; i < ARRAY_SIZE(values); i++) {
            uint16_t val = values[i].value;

            (void) phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, values[i].reg, val);
            if (is_hybrid && LAN887X_DSP_REGS_CBL_DIAG_MAX_WAIT_CONFIG_100 == values[i].reg) {
                val = 0xAU;
                (void) phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, values[i].reg, val);
            }
        }

        if (is_hybrid == PHY_TRUE) {
            MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                                LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG, 0x0001U, 0x0001U));
        }

        /* start cable diag */
        MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1,
                                            LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                            (LAN887X_DSP_REGS_START_CBL_DIAG_DONE | LAN887X_DSP_REGS_START_CBL_DIAG_EN),
                                            LAN887X_DSP_REGS_START_CBL_DIAG_EN));
    }

error:
    return rc;
}

static mepa_rc lan887x_aneg_resolve_master_slave(mepa_device_t *dev, uint8_t *mode)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t forced_ms, forced_ms_lp, forced_master, forced_master_lp;
    uint16_t lp_l, lp_m, adv_l, adv_m;
    uint8_t master_slave_state = MASTER_SLAVE_STATE_ERR;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_LP_L, &lp_l));
    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_LP_M, &lp_m));
    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_L, &adv_l));
    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_M, &adv_m));

    forced_ms = (adv_l & MDIO_AN_T1_ADV_L_FORCE_MS);
    forced_ms_lp =  (lp_l & MDIO_AN_T1_LP_L_FORCE_MS);
    forced_master = (adv_m & MDIO_AN_T1_ADV_M_MST);
    forced_master_lp = (lp_m & MDIO_AN_T1_LP_M_MST);

    if (forced_ms == ZERO) {
        if (forced_ms_lp > ZERO ) {
            master_slave_state = MASTER_SLAVE_STATE_MASTER;
            if (forced_master_lp > ZERO) {
                master_slave_state = MASTER_SLAVE_STATE_SLAVE;
            }
        } else {
            /* From 802.3bp-2016 standard
             * Table 98.4 Master-Slave configuration
             * Device with higher T[4:0] is master otherwise slave
             */
            if ((adv_m & 0x1FU) > (lp_m & 0x1FU)) {
                master_slave_state = MASTER_SLAVE_STATE_MASTER;
            } else {
                master_slave_state = MASTER_SLAVE_STATE_SLAVE;
            }
        }
    } else {
        if (forced_ms_lp > ZERO) {
            if (((forced_master > ZERO) && (forced_master_lp > ZERO)) ||
                (forced_master == ZERO && forced_master_lp == ZERO)) {
                master_slave_state = MASTER_SLAVE_STATE_ERR;
            } else  {
                master_slave_state = MASTER_SLAVE_STATE_MASTER;
                if (forced_master_lp > ZERO) {
                    master_slave_state = MASTER_SLAVE_STATE_SLAVE;
                }
            }
        } else {
            master_slave_state = MASTER_SLAVE_STATE_SLAVE;
            if (forced_master > ZERO) {
                master_slave_state = MASTER_SLAVE_STATE_MASTER;
            }
        }
    }

    *mode = master_slave_state;

    T_I(MEPA_TRACE_GRP_GEN, "aneg status get master_slave_state %u\r\n", master_slave_state);

error:
    return rc;
}

static mepa_rc lan887x_aneg_read_status(mepa_device_t *dev, mepa_status_t *status)
{
    mepa_rc rc = MEPA_RC_INCOMPLETE;
    //mepa_bool_t lp_sym_pause, lp_asym_pause;
    uint16_t val = 0, lp_l = 0, lp_m = 0;
    phy_data_t *data = (phy_data_t *)dev->data;

    status->aneg.obey_pause = PHY_FALSE;
    status->aneg.generate_pause = PHY_FALSE;
    status->fdx = PHY_TRUE;
    status->link = PHY_FALSE;
    status->speed = MESA_SPEED_UNDEFINED;

    MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_STAT, &val));
    if ((val & MDIO_AN_STAT1_COMPLETE) == ZERO) {
        //T_D( MEPA_TRACE_GRP_GEN, "aneg is not completed \r\n");
    } else {
        rc = MEPA_RC_OK;

        MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_LP_L, &lp_l));
        MEPA_RC_GOTO(rc, phy_mmd_reg_rd(dev, MDIO_MMD_AN, MDIO_AN_T1_LP_M, &lp_m));

        if (((lp_m & LPA_1000FULL) == LPA_1000FULL) && (data->conf.aneg.speed_1g_fdx == PHY_TRUE)) {
            status->speed = MEPA_SPEED_1G;
        } else if (((lp_m & LPA_100FULL) == LPA_100FULL) && (data->conf.aneg.speed_100m_fdx == PHY_TRUE)) {
            status->speed = MEPA_SPEED_100M;
        } else {
            status->speed = MESA_SPEED_UNDEFINED;
        }
#if 0
        lp_sym_pause = ((lp_l & MDIO_AN_T1_ADV_L_PAUSE_CAP) != ZERO) ? PHY_TRUE : PHY_FALSE;
        lp_asym_pause = ((lp_l & MDIO_AN_T1_ADV_L_PAUSE_ASYM) != ZERO) ? PHY_TRUE : PHY_FALSE;
        status->aneg.obey_pause = data->conf.flow_control && (lp_sym_pause || lp_asym_pause);
        status->aneg.generate_pause = data->conf.flow_control && lp_sym_pause;
#endif

        //T_D( MEPA_TRACE_GRP_GEN, "aneg link resolved \r\n");
    }

error:
    return rc;
}

/**********************************
 * Internal APIs must be above this
 *********************************/

/**********************************
 * External driver callbacks
 * MEPA_RC must be used to unlock and return!
 *********************************/

static mepa_rc lan887x_sqi_read(struct mepa_device *dev, uint32_t *const value)
{
    mepa_rc rc = MEPA_RC_ERROR;
    if (dev != NULL && value != NULL) {
        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *value = lan887x_get_sqi(dev);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_delete(struct mepa_device *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;

    //cleanup
    if (dev != NULL) {
#ifdef MEPA_lan887x_static_mem
        uint8_t pidx = 0;

        T_D( MEPA_TRACE_GRP_GEN, "static driver cleanup!!\n");
        for (pidx = 0; pidx < LAN887X_PHY_MAX; pidx++) {

            if (lan887x_data[pidx].ctx_status &&
                lan887x_data[pidx].port_no == dev->numeric_handle &&
                lan887x_device[pidx].numeric_handle  == dev->numeric_handle) {
                T_D( MEPA_TRACE_GRP_GEN, "LAN887X port-%d driver delete @ idx=%d!!\n", lan887x_device[pidx].numeric_handle, pidx);
                (void) memset(&lan887x_data[pidx], 0, sizeof(phy_data_t));
                (void) memset(&lan887x_device[pidx], 0, sizeof(mepa_device_t));
                break;
            }
        }
        rc = MEPA_RC_OK;
#else
        T_D( MEPA_TRACE_GRP_GEN, "dynamic driver cleanup!!\n");
        rc = mepa_delete_int(dev);
#endif
    }

    return rc;
}

static void lan887x_fill_probe_data(mepa_driver_t *drv,
                                    mepa_device_t *dev,
                                    phy_data_t *data,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                    struct mepa_board_conf                  *conf)
{
    data->ctx_status = PHY_TRUE;
    data->port_no = conf->numeric_handle;

    dev->numeric_handle  = conf->numeric_handle;
    dev->drv = drv;
    dev->data = (void *)data;
    dev->callout = callout;
    dev->callout_ctx = callout_ctx;
    data->init_done = PHY_FALSE;
    data->events = 0;
    //Default is preferred master when autoneg is enabled and forced master when aneg is disabled
    data->conf.man_neg = MEPA_MANUAL_NEG_REF;
    data->conf.admin.enable = PHY_TRUE;
    data->conf.speed = MESA_SPEED_1G;
    data->conf.fdx = PHY_TRUE;
    data->conf.mac_if_aneg_ena = PHY_TRUE;
    data->media_intf = MESA_PHY_MEDIA_IF_T1_1000FX;
    data->mac_if = MESA_PORT_INTERFACE_RGMII_RXID;
    data->led3_conf.led_num = MEPA_LED3;
    data->led3_conf.mode = MEPA_GPIO_MODE_LED_LINK_ACTIVITY;

    //Cable diag data reset
    data->cd_res.link = PHY_LINKDOWN;
    data->cd_res.length[0] = 0;
    data->cd_res.status[0] = MESA_VERIPHY_STATUS_UNKNOWN;

    (void) lan887x_init_phy(dev, PHY_FALSE);

    T_I(MEPA_TRACE_GRP_GEN, "LAN887X driver probed for port %u  \r\n", data->port_no);
}

static mepa_device_t *lan887x_probe(mepa_driver_t *drv,
                                    const mepa_callout_t    MEPA_SHARED_PTR *callout,
                                    struct mepa_callout_ctx MEPA_SHARED_PTR *callout_ctx,
                                    struct mepa_board_conf                  *conf)
{
    mepa_device_t   *dev = NULL;

    if (drv != NULL) {
        phy_data_t      *data = NULL;

#ifdef MEPA_lan887x_static_mem
        uint8_t pidx = 0;

        T_D( MEPA_TRACE_GRP_GEN, "static driver create!!\n");
        for (pidx = 0; pidx < LAN887X_PHY_MAX; pidx++) {
            if (lan887x_data[pidx].ctx_status) {
                T_D( MEPA_TRACE_GRP_GEN, "LAN887X driver already @ idx=%d[port-%d]!!\n", pidx, lan887x_device[pidx].numeric_handle);
                continue;
            }

            dev = &lan887x_device[pidx];
            data = &lan887x_data[pidx];

            T_D( MEPA_TRACE_GRP_GEN, "LAN887X driver probe @ idx=%d, port=%d!!\n", pidx, conf->numeric_handle);
            lan887x_fill_probe_data(drv, dev, data, callout, callout_ctx, conf);

            break;
        }
#else
        T_D( MEPA_TRACE_GRP_GEN, "dynamic driver create!!\n");
        dev = mepa_create_int(drv, callout, callout_ctx, conf, (int32_t)(sizeof(phy_data_t)));
        if (dev != NULL) {
            data = dev->data;
            data->port_no = conf->numeric_handle;

            lan887x_fill_probe_data(drv, dev, data, callout, callout_ctx, conf);
        }
#endif
    }

    return dev;
}

static mepa_rc lan887x_conf_get(struct mepa_device *dev, mepa_conf_t *const config)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && config != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        (void) memcpy(config, &(data->conf), sizeof(mepa_conf_t));
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && config != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_config_set(dev, config);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_int_reset(dev, rst_conf);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_aneg_status_get(mepa_device_t *dev, mepa_aneg_status_t *status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint8_t master_slave_state;

    if (dev != NULL && status != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_INV_STATE;
        if (data->conf.mac_if_aneg_ena == PHY_TRUE) {

            MEPA_ENTER(dev);

            rc = lan887x_aneg_resolve_master_slave(dev, &master_slave_state);
            if (rc == MEPA_RC_OK) {
                status->master_cfg_fault = (master_slave_state == MASTER_SLAVE_STATE_ERR) ? PHY_TRUE : PHY_FALSE;
                status->master = (master_slave_state == MASTER_SLAVE_STATE_MASTER) ? PHY_TRUE : PHY_FALSE;
            }

            MEPA_EXIT(dev);
        }
    }

    return rc;
}

static mepa_rc lan887x_poll(struct mepa_device *dev, mepa_status_t *status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    uint8_t master_slave_state;

    if (dev != NULL && status != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);

        //Current link status
        data->link_status = PHY_FALSE;

        if (data->conf.mac_if_aneg_ena == PHY_TRUE) {
            //Resolve speed
            MEPA_RC_GOTO(rc, lan887x_aneg_read_status(dev, status));
            //Resolve speed
            MEPA_RC_GOTO(rc, lan887x_aneg_resolve_master_slave(dev, &master_slave_state));
            status->master = (master_slave_state == MASTER_SLAVE_STATE_MASTER) ? PHY_TRUE : PHY_FALSE;
        } else {
            status->master = (data->conf.man_neg == MEPA_MANUAL_NEG_REF ? PHY_TRUE : PHY_FALSE);
            status->speed = data->conf.speed;
        }

        //Set link status
#if 0
        rc = phy_get_link_status(dev, status);
#else
        rc = phy_c45_get_link_status(dev, status);
#endif
        //T_D( MEPA_TRACE_GRP_GEN, "poll complete! ink is %s \r\n", (status->link?"up":"down"));

error:
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_if_set( struct mepa_device *dev, mepa_port_interface_t mac_if)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        rc = MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED;

        if (mac_if >= MESA_PORT_INTERFACE_RGMII && mac_if <= MESA_PORT_INTERFACE_RGMII_TXID) {
            phy_data_t *data = (phy_data_t *)dev->data;

            rc = MEPA_RC_OK;
            if (data->mac_if != mac_if) {
                MEPA_ENTER(dev);
                //Setup mac_if
                data->mac_if = mac_if;
                //reset PHY
                MEPA_RC_GOTO(rc, lan887x_int_reset(dev, NULL));
                //T_D( MEPA_TRACE_GRP_GEN, "Re-configure MAC Interface type from %d to %d\r\n", data->mac_if, mac_if);
error:
                MEPA_EXIT(dev);
            }
            //T_D( MEPA_TRACE_GRP_GEN, "Set MAC Interface type %d\r\n", data->mac_if);
        }
    }

    return rc;
}

static mepa_rc lan887x_if_get( struct mepa_device *dev,
                               mepa_port_speed_t speed, mepa_port_interface_t *mac_if)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL && mac_if != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *mac_if = data->mac_if;
        MEPA_EXIT(dev);

        //T_D( MEPA_TRACE_GRP_GEN, "Get MAC Interface type %d\r\n", *mac_if);
    }

    return rc;
}

static mepa_rc lan887x_media_set(struct mepa_device *dev, mepa_media_interface_t media_if)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL) {
        rc = MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED;
        if ((media_if == MESA_PHY_MEDIA_IF_T1_100FX) || (media_if == MESA_PHY_MEDIA_IF_T1_1000FX)) {
            phy_data_t *data = (phy_data_t *)dev->data;

            rc = MEPA_RC_OK;
            if (data->media_intf != media_if) {
                MEPA_ENTER(dev);
                data->media_intf = media_if;
                /* re-configure media interface
                   when aneg = true, apply change
                   when aneg = false, then following
                   old_media_type new_media_type old_speed  new_speed
                   1000_t1         100_t1        1000       100    ==> reset
                   1000_t1         100_t1         100       100    ===> No reset
                   100t1           1000t1         100       100   ===> No reset */
                if (data->conf.speed != MESA_SPEED_100M ||
                    data->conf.mac_if_aneg_ena == PHY_TRUE) {
                    rc = lan887x_int_reset(dev, NULL);
                }
                MEPA_EXIT(dev);
                //T_D( MEPA_TRACE_GRP_GEN, "Set media type %d! rc=%d.\r\n", media_if, rc);
            }
        }
    }

    return rc;
}

static mepa_rc lan887x_media_get(struct mepa_device *dev, mepa_media_interface_t *media_if)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL && media_if != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *media_if = data->media_intf;
        MEPA_EXIT(dev);

        //T_D( MEPA_TRACE_GRP_GEN, "Get media type %d\r\n", *media_if);
    }

    return rc;
}

// read direct registers
static mepa_rc lan887x_reg_read (struct mepa_device *dev, uint32_t addr, uint16_t *const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL && value != NULL) {
        MEPA_ENTER(dev);
        rc = phy_reg_rd(dev, LAN8870_PHY_REG_ADDR(addr), value);
        MEPA_EXIT(dev);
    }

    return rc;
}
// write direct registers
static mepa_rc lan887x_reg_write(struct mepa_device *dev, uint32_t addr, uint16_t value)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = phy_reg_wr(dev, LAN8870_PHY_REG_ADDR(addr), value);
        MEPA_EXIT(dev);
    }

    return rc;
}

// read mmd registers
static mepa_rc lan887x_mmd_reg_read(struct mepa_device *dev, uint32_t addr, uint16_t *const value)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL && value != NULL) {
        MEPA_ENTER(dev);
        rc = phy_mmd_reg_rd(dev, PHY_MMD_DEVAD(addr), PHY_REG_ADDR(addr), value);
        MEPA_EXIT(dev);
    }

    return rc;
}
// write mmd registers
static mepa_rc lan887x_mmd_reg_write(struct mepa_device *dev, uint32_t addr, uint16_t value)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = phy_mmd_reg_wr(dev, PHY_MMD_DEVAD(addr), PHY_REG_ADDR(addr), value);
        MEPA_EXIT(dev);
    }

    return rc;
}

// Enable events/interrupts
static mepa_rc lan887x_event_enable_set(struct mepa_device *dev, mepa_event_t event, mesa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_int_events_set(dev, event, enable);
        MEPA_EXIT(dev);
    }

    return rc;
}

// Get current enabled events/interrupts
static mepa_rc lan887x_event_enable_get(struct mepa_device *dev, mepa_event_t *const event)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && event != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *event = data->events;
        MEPA_EXIT(dev);

        //T_D( MEPA_TRACE_GRP_GEN, "events configured 0x%x \r\n", *event);
    }

    return rc;
}

// Poll the status of currently enabled events/interrupts
static mepa_rc lan887x_event_status_poll(struct mepa_device *dev, mepa_event_t *const status)
{
    uint16_t val = 0, int_mask = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && status != NULL) {
        phy_data_t *data = (phy_data_t *) dev->data;

        *status = 0;

        MEPA_ENTER(dev);

        rc = phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                            LAN887X_MX_CHIP_TOP_REG_INT_MSK, &int_mask);

        if (rc == MEPA_RC_OK) {
            rc = phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                                LAN887X_MX_CHIP_TOP_REG_INT_STS, &val);

            if (rc == MEPA_RC_OK) {
                //When 0, this interrupt is enabled.
                //When 1, this interrupt is disabled.
                val = val & (~int_mask & ((uint16_t)data->events));
                *status = val;
            }
        }
        MEPA_EXIT(dev);
    }

    return rc;
}

// Set gpio mode to input, output or alternate function
static mepa_rc lan887x_gpio_mode_set(mepa_device_t *dev, const mepa_gpio_conf_t *gpio_conf)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        rc = MEPA_RC_NOT_IMPLEMENTED;

        // Note: For now only LED3 is supported
        if (gpio_conf != NULL &&
            (gpio_conf->led_num == MEPA_LED3) &&
            (gpio_conf->mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY && gpio_conf->mode <= MEPA_GPIO_MODE_LED_DISABLE_EXTENDED)) {
            MEPA_ENTER(dev);
            rc = lan887x_config_led(dev, gpio_conf);
            MEPA_EXIT(dev);
        }
    }

    return rc;
}

/**
 * Loopback Modes:
 * MAC Loopback: Digital loopback at PCS.
 * PMA Loopback: Analog loopback inside AFE.
 * Far End Loopback: Loopback from wire to PCS and back to wire.
**/
static mepa_rc lan887x_loopback_set(mepa_device_t *dev, const mepa_loopback_t *loopback)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        MEPA_ENTER(dev);
        rc = lan887x_setup_lpbk(dev, loopback);
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_loopback_get(mepa_device_t *dev, mepa_loopback_t *const loopback)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && loopback != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        (void) memcpy(loopback, &data->loopback, sizeof(mepa_loopback_t));
        MEPA_EXIT(dev);

        //T_D( MEPA_TRACE_GRP_GEN, "loopback_get\r\n");
    }

    return rc;
}

static mepa_rc lan887x_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && phy_info != NULL) {
        phy_data_t *data = (phy_data_t *)(dev->data);

        if (data->init_done == PHY_TRUE) {
            MEPA_ENTER(dev);
            phy_info->part_number = data->dev.model;
            phy_info->revision = data->dev.rev;
            phy_info->cap = (data->conf.speed == MESA_SPEED_100M ? MEPA_CAP_SPEED_MASK_1G : MEPA_CAP_TS_MASK_NONE);
            MEPA_EXIT(dev);

            rc = MEPA_RC_OK;
        }
    }
    //T_D( MEPA_TRACE_GRP_GEN, "phy_info_get rc=%d\r\n", rc);

    return rc;
}

static mepa_rc lan887x_debug_info(struct mepa_device *dev,
                                  const mepa_debug_print_t pr,
                                  const mepa_debug_info_t   *const info)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && pr != NULL && info != NULL) {
        //PHY Debugging
        switch (info->group) {
        case MEPA_DEBUG_GROUP_ALL:
        case MEPA_DEBUG_GROUP_PHY: {
            MEPA_ENTER(dev);
            phy_reg_dump(dev, pr, lan887x_regs, ARRAY_SIZE(lan887x_regs));
            rc = MEPA_RC_OK;
            MEPA_EXIT(dev);
        }
        break;
        default:
            rc = MEPA_RC_OK;
            break;
        }
    }
    return rc;
}

// Mode is assumed as Masetr mode always
// Slave mode to be supported in future
static mepa_rc lan887x_cable_diag_start(mepa_device_t *dev, int32_t mode)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;
        mepa_status_t link_status;
        mepa_bool_t is_master = PHY_TRUE;

        rc = MEPA_RC_OK;

        MEPA_ENTER(dev);

        (void)  phy_c45_get_link_status(dev, &link_status);
        /* read cable diag status*/
        data->cd_res.link = data->link_status;
        data->cd_res.length[0] = 0;// cannot measure length
        data->cd_res.status[0] = MESA_VERIPHY_STATUS_UNKNOWN;

        if (data->link_status == PHY_LINKUP) { /* Link is up*/

            data->cd_res.status[0] = MESA_VERIPHY_STATUS_OK;
            (void) phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                          LAN887X_DSP_REGS_START_CBL_DIAG_EN);
            /*** SOFT RESET to restore configuration ***/
            MEPA_RC_GOTO(rc, lan887x_int_reset(dev, NULL));

        } else { /* Link is down. Start cable diag */

            MEPA_RC_GOTO(rc, lan887x_phy_cable_diag_start(dev, PHY_FALSE, is_master));

            //Update current link status
            (void)  phy_c45_get_link_status(dev, &link_status);

            MEPA_RC_GOTO(rc, lan887x_cable_test_report(dev, is_master));
        }

        //Update current link status
        (void)  phy_c45_get_link_status(dev, &link_status);

error:
        MEPA_EXIT(dev);
    }

    return rc;
}

static mepa_rc lan887x_cable_diag_get(struct mepa_device *dev, mepa_cable_diag_result_t *res)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if ((dev != NULL) && (res != NULL)) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;

        MEPA_ENTER(dev);
        *res = data->cd_res;
        data->cd_res.length[0] = 0;
        data->cd_res.status[0] = MESA_VERIPHY_STATUS_UNKNOWN;

        MEPA_EXIT(dev);
    }

    return rc;
}

#if 0
static mepa_rc lan887x_isolate_mode_set(struct mepa_device *dev, mepa_bool_t const val)
{
    uint16_t reg_val = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);

        MEPA_RC_GOTO(rc, phy_reg_rd(dev, MII_BMCR, &reg_val));
        //Enabled so set the bit
        if (val == PHY_TRUE) {
            reg_val |= BMCR_ISOLATE;
        } else {
            //Disabled so clear the bit
            reg_val &= (~BMCR_ISOLATE) & 0xFFFFU;
        }
        MEPA_RC_GOTO(rc, phy_reg_wr(dev, MII_BMCR, reg_val));

error:
        MEPA_EXIT(dev);
    }

    return rc;
}
#endif

mepa_drivers_t mepa_lan887x_driver_init(void)
{
    mepa_drivers_t result;
    static mepa_driver_t lan887x_driver[LAN887X_PHY_ID_MAX];
    uint8_t idx = 0;

    for (idx = 0; idx < LAN887X_PHY_ID_MAX; idx++) {
        mepa_driver_t *lan887x_drv = &lan887x_driver[idx];

        //Device ID & Mask
        //lan887x_drv->id = LAN8870_PHY_ID;
        //lan887x_drv->mask = LAN887X_PHY_ID_MASK;
        lan887x_drv->id = LAN887X_PHY_ID_PRTO;
        lan887x_drv->mask = LAN887X_PHY_ID_PRTO_MSK;
        /* LAN887X Driver APIs */
        lan887x_drv->mepa_driver_delete             = lan887x_delete;
        lan887x_drv->mepa_driver_reset              = lan887x_reset;
        lan887x_drv->mepa_driver_poll               = lan887x_poll;
        lan887x_drv->mepa_driver_probe              = lan887x_probe;
        lan887x_drv->mepa_driver_aneg_status_get    = lan887x_aneg_status_get;
        lan887x_drv->mepa_driver_conf_set           = lan887x_conf_set;
        lan887x_drv->mepa_driver_conf_get           = lan887x_conf_get;
        lan887x_drv->mepa_driver_if_set             = lan887x_if_set;
        lan887x_drv->mepa_driver_if_get             = lan887x_if_get;
        lan887x_drv->mepa_driver_media_set          = lan887x_media_set;
        lan887x_drv->mepa_driver_media_get          = lan887x_media_get;
        lan887x_drv->mepa_driver_event_enable_set   = lan887x_event_enable_set;
        lan887x_drv->mepa_driver_event_enable_get   = lan887x_event_enable_get;
        lan887x_drv->mepa_driver_event_poll         = lan887x_event_status_poll;
        lan887x_drv->mepa_driver_gpio_mode_set      = lan887x_gpio_mode_set;
        lan887x_drv->mepa_driver_loopback_set       = lan887x_loopback_set;
        lan887x_drv->mepa_driver_loopback_get       = lan887x_loopback_get;
        lan887x_drv->mepa_driver_phy_info_get       = lan887x_info_get;
        lan887x_drv->mepa_debug_info_dump           = lan887x_debug_info;
        lan887x_drv->mepa_driver_clause22_read      = lan887x_reg_read;
        lan887x_drv->mepa_driver_clause22_write     = lan887x_reg_write;
        lan887x_drv->mepa_driver_clause45_read      = lan887x_mmd_reg_read;
        lan887x_drv->mepa_driver_clause45_write     = lan887x_mmd_reg_write;
        lan887x_drv->mepa_driver_sqi_read           = lan887x_sqi_read;
        //lan887x_drv->mepa_driver_isolate_mode_conf  = lan887x_isolate_mode_set;
        lan887x_drv->mepa_driver_cable_diag_start   = lan887x_cable_diag_start;
        lan887x_drv->mepa_driver_cable_diag_get     = lan887x_cable_diag_get;
        lan887x_drv->mepa_tc10                      = NULL;
    }

    result.phy_drv = &lan887x_driver[0];
    result.count = LAN887X_PHY_ID_MAX;

    return result;
}
