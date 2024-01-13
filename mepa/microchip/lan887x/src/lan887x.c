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
    { "tc10_regs:LAN887X_MISC_REGS_REG16", MDIO_MMD_VEND1, LAN887X_MISC_REGS_REG16},
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
    mepa_rc rc = MEPA_RC_NOT_IMPLEMENTED;
    uint16_t reg_val = 0;
    phy_data_t *data = (phy_data_t *) dev->data;

    rc = phy_reg_rd(dev, MII_BMSR, &reg_val);
    if (rc < 0) {
        return rc;
    }

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

    rc = phy_mmd_reg_rd(dev, MDIO_MMD_PMAPMD, MDIO_STAT1, &reg_val);
    if (rc == MEPA_RC_OK) {
        status->link = ((reg_val & MDIO_STAT1_LSTATUS) != ZERO);
        data->link_status = status->link;
    }

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

static void lan887x_phy_100m_cfg_script(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (data->conf.mac_if_aneg_ena == PHY_FALSE) {
        // MLNX_MISC_SPEED_100T1
        MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                             LAN887X_PMA_COMM_100T1_CTL_T1,
                                             LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_MASK,
                                             LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_100));
    }

    // MLNX_100T1_000
    // RMW PORT_AFE->AFE_PORT_TESTBUS_CTRL4->bit 7 = 1
    MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
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
        MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD, LAN887X_PMA_COMM_100T1_CTL_T1,
                                             LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_MASK,
                                             LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_1000));
    }

    // MLNX_1000T1_000
    // RMW PORT_AFE->AFE_PORT_TESTBUS_CTRL4->bit 7 = 1
    MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_PMAPMD,
                                         LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG, 0x0084U, 0x0084U));

    // ECHO_DELAY_CONFIG
    MEPA_RC_GOTO (rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, 0x8ECU, 0x0024U));

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

static mepa_rc lan887x_rgmii_setup(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_bool_t rgmii_set = PHY_TRUE;
    uint16_t txc = 0;
    uint16_t rxc = 0;

    // Disable SGMII_CTL
    MEPA_RC_GOTO (rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                             LAN887X_MX_CHIP_TOP_REG_SGMII_CTL,
                                             LAN887X_MX_CHIP_TOP_REG_SGMII_MUX_EN));

    MEPA_RC_GOTO (rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0, &txc));

    MEPA_RC_GOTO (rc, phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1, &rxc));

    switch (data->mac_if) {
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
        T_I( MEPA_TRACE_GRP_GEN, "PHY MAC interface is not RGMII(%d)!\n", data->mac_if);
        rc = MEPA_RC_OK;
        break;
    }

    if (rgmii_set) {
        // Enable RGMII
        MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                             LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL,
                                             LAN887X_MIS_CFG_REG0_MAC_MODE_RGMII));

        // Set RX DELAY
        MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1,
                                             LAN887X_MIS_DLL_EN_, rxc));

        // Set TX DELAY
        MEPA_RC_GOTO (rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0,
                                             LAN887X_MIS_DLL_EN_, txc));

        T_I( MEPA_TRACE_GRP_GEN, "PHY RGMII setup complete!\n");
    }
    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_init_phy(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    if (!data->init_done) {
        data->init_done = PHY_TRUE;

        //FIXME: LAN887X A0 onetime eFuse setup
        phy_cfg_regs(dev, lan887x_onetime_setup, ARRAY_SIZE(lan887x_onetime_setup), PHY_TRUE);

        T_I( MEPA_TRACE_GRP_GEN, "PHY efuse setup complete!\n");
    }

    //LAN887X A0 PHY Setup
    phy_cfg_regs(dev, lan887x_setup, ARRAY_SIZE(lan887x_setup), PHY_FALSE);

    //setup SGMII/RGMII interface
    MEPA_RC_GOTO (rc, lan887x_rgmii_setup(dev));

    //LED setup
    MEPA_RC_GOTO (rc, lan887x_config_led(dev, &data->led3_conf));
    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_init_conf(mepa_device_t *const dev, mesa_port_speed_t speed, mepa_bool_t master)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t reg_speed = BMCR_FULLDPLX;
    phy_data_t *data = (phy_data_t *)dev->data;

    // speed selection based on media type
    if ((data->media_intf == MESA_PHY_MEDIA_IF_T1_100FX) ||
        ((data->media_intf == MESA_PHY_MEDIA_IF_T1_1000FX) && (speed == MESA_SPEED_100M))) {
        reg_speed |= BMCR_SPEED100;
        speed = MESA_SPEED_100M;
    } else {
        //setup speed
        reg_speed |= BMCR_SPEED1000;
        speed = MESA_SPEED_1G;
    }
    //Update speed
    data->conf.speed = speed;

    /**
     * NOTE: UNG_MOLINEUX-675
     *   CL22 RESET(2) bit is causing link issues
     *   Even interrupts are not properly generated
     *   So use MX_CHIP_TOP:CHIP_SOFT_RST registers
     */
    MEPA_RC_GOTO (rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                     LAN887X_MX_CHIP_TOP_REG_SOFT_RST,
                                     LAN887X_MX_CHIP_TOP_RESET_));

    LAN887X_NSLEEP(50U);

    MEPA_RC_GOTO (rc, lan887x_init_phy(dev));

    /* Setup MASTER/SLAVE */
    MEPA_RC_GOTO (rc, lan887x_master_slave_mode_set(dev, master));

    /* Setup Speed & Duplex */
    MEPA_RC_GOTO (rc, phy_reg_set_bits(dev, MII_BMCR, reg_speed));

    // MLX 100/1000 link setup
    lan887x_link_setup(dev, speed);

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

    /**
     * NOTE: Following are always fixed. Change in conf set will be ignored.
     *  speed = (100Mbps or 1000Mbps)
     *  fdx always enabled.
     */
    if (!(config->man_neg == MEPA_MANUAL_NEG_REF ||
          config->man_neg == MEPA_MANUAL_NEG_CLIENT) ||
        (config->fdx != PHY_TRUE) ||
        (config->speed != MESA_SPEED_100M &&
         config->speed != MESA_SPEED_1G &&
         config->speed != MESA_SPEED_AUTO)) {
        rc = MEPA_RC_ERR_PARM;
    } else if (config->mac_if_aneg_ena == PHY_TRUE) {
        rc = MEPA_RC_NOT_IMPLEMENTED;
    } else {
        data->conf.fdx = PHY_TRUE;
        data->conf.flow_control = config->flow_control;

        if (!data->init_done) {
            MEPA_RC_GOTO (rc, lan887x_init_conf(dev, config->speed, (config->man_neg == MEPA_MANUAL_NEG_REF)));

            data->init_done = PHY_TRUE;
            data->conf.speed = config->speed;
            data->conf.man_neg = config->man_neg;
            data->conf.admin.enable = config->admin.enable;
        }

        // Setup Speed
        if (data->conf.speed != config->speed) {
            re_config = PHY_TRUE;
            T_D( MEPA_TRACE_GRP_GEN, "Speed changed from %s to %s!!\n",
                 (data->conf.speed == MESA_SPEED_100M ? "100M" : (data->conf.speed == MESA_SPEED_AUTO ? "AUTO" : "1G")),
                 (config->speed == MESA_SPEED_100M ? "100M" : (config->speed == MESA_SPEED_AUTO ? "AUTO" : "1G")));
            data->conf.speed = config->speed;
        }

        // Setup Master/Slave Mode
        if (data->conf.man_neg != config->man_neg) {
            re_config = PHY_TRUE;
            T_D( MEPA_TRACE_GRP_GEN, "Master/Slave Mode changed from %s to %s!!\n",
                 (data->conf.man_neg == MEPA_MANUAL_NEG_REF ? "Master" : "Slave"),
                 (config->man_neg == MEPA_MANUAL_NEG_REF ? "Master" : "Slave"));
            data->conf.man_neg = config->man_neg;
        }

        // handle admin enable/disable
        if (data->conf.admin.enable != config->admin.enable ||
            (data->conf.admin.enable == config->admin.enable && data->conf.admin.enable == PHY_FALSE)) {
            T_D( MEPA_TRACE_GRP_GEN, "Admin State changed from %sabled to %sabled!!\n",
                 (data->conf.admin.enable ? "En" : "Dis"),
                 (config->admin.enable ? "En" : "Dis"));
            if (config->admin.enable) {
                MEPA_RC_GOTO (rc, phy_reg_clear_bits(dev, MII_BMCR, BMCR_PDOWN));
                re_config = PHY_TRUE;
            } else {
                /* Setup low power */
                re_config = PHY_FALSE;
                MEPA_RC_GOTO (rc, phy_reg_set_bits(dev, MII_BMCR, BMCR_PDOWN));
            }
        }

        if (re_config) {
            MEPA_RC_GOTO (rc, lan887x_init_conf(dev, config->speed, (config->man_neg == MEPA_MANUAL_NEG_REF)));
        }

        data->conf.admin = config->admin;
        rc = MEPA_RC_OK;
    }

error:
    return rc;
}

static void lan887x_int_media_set(struct mepa_device *dev, mepa_media_interface_t const media_if)
{
    phy_data_t *data = (phy_data_t *)dev->data;

    data->media_intf = ((media_if == MESA_PHY_MEDIA_IF_T1_100FX) ? (MESA_PHY_MEDIA_IF_T1_100FX) : (MESA_PHY_MEDIA_IF_T1_1000FX));
}

static mepa_rc lan887x_int_reset(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    T_I( MEPA_TRACE_GRP_GEN, "Initializing PHY! \r\n");
    if (rst_conf != NULL) {
        //re-configure media interface
        lan887x_int_media_set(dev, rst_conf->media_intf);
    }

    //configure PHY
    MEPA_RC_GOTO (rc, lan887x_init_conf(dev, data->conf.speed, (data->conf.man_neg == MEPA_MANUAL_NEG_REF)));
    data->init_done = PHY_TRUE;

    MEPA_RC_GOTO (rc, phy_get_device_info(dev));
    T_I( MEPA_TRACE_GRP_GEN, "phy_info phy_id=0x%x, mode=%s[fault=%u],"
         "model=0x%x, rev=%u, error=%d  \r\n",
         data->dev.id, (data->dev.is_master ? "master" : "slave"),
         data->dev.is_master_fault, data->dev.model, data->dev.rev, rc);

    // re-configure the phy after reset
    MEPA_RC_GOTO (rc, lan887x_config_set(dev, &data->conf));

error:
    T_D( MEPA_TRACE_GRP_GEN, "reset rc=%d  \r\n", rc);

    return rc;
}

/**********************************
 * Internal APIs must be above this
 *********************************/

/**********************************
 * External driver callbacks
 * MEPA_RC must be used to unlock and return!
 *********************************/
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
    data->cdiags_start = PHY_FALSE;
    data->events = 0;
    data->conf.man_neg = MEPA_MANUAL_NEG_REF;
    data->conf.admin.enable = PHY_TRUE;
    data->conf.speed = MESA_SPEED_1G;
    data->conf.fdx = PHY_TRUE;
    data->conf.mac_if_aneg_ena = PHY_FALSE;
    data->media_intf = MESA_PHY_MEDIA_IF_T1_1000FX;
    data->mac_if = MESA_PORT_INTERFACE_RGMII_RXID;
    data->led3_conf.led_num = MEPA_LED3;
    data->led3_conf.mode = MEPA_GPIO_MODE_LED_LINK_ACTIVITY;

    (void) lan887x_init_phy(dev);

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

    if (dev != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        if (data != NULL) {
            rc = MEPA_RC_OK;
            MEPA_ENTER(dev);
            (void) memcpy(config, &(data->conf), sizeof(mepa_conf_t));
            MEPA_EXIT(dev);
        }
    }

    return rc;
}

static mepa_rc lan887x_conf_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL) {
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

static mepa_rc lan887x_poll(struct mepa_device *dev, mepa_status_t *status)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && status != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        if (data != NULL) {
            rc = MEPA_RC_ERROR;

            //Resolve speed
            if (data->conf.mac_if_aneg_ena != PHY_TRUE) {
                rc = MEPA_RC_OK;
                MEPA_ENTER(dev);
                //Set link status
#if 0
                MEPA_RC_GOTO (rc, phy_get_link_status(dev, status));
#else
                MEPA_RC_GOTO (rc, phy_c45_get_link_status(dev, status));
#endif
                T_D( MEPA_TRACE_GRP_GEN, "link poll complete \r\n");

error:
                MEPA_EXIT(dev);
                T_D( MEPA_TRACE_GRP_GEN, "poll rc=%d link is %s \r\n", rc, (status->link ? "up" : "down"));
            }
        }
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

            MEPA_ENTER(dev);
            //Setup mac_if
            if (data->mac_if != mac_if) {
                //setup SGMII/RGMII interface
                rc = lan887x_rgmii_setup(dev);
                T_D( MEPA_TRACE_GRP_GEN, "Re-configure MAC Interface type %d\r\n", mac_if);
            }
            data->mac_if = mac_if;
            MEPA_EXIT(dev);

            T_D( MEPA_TRACE_GRP_GEN, "Set MAC Interface type %d\r\n", data->mac_if);
        }
    }

    return rc;
}

static mepa_rc lan887x_if_get( struct mepa_device *dev,
                               mepa_port_speed_t speed, mepa_port_interface_t *mac_if)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *mac_if = data->mac_if;
        MEPA_EXIT(dev);

        T_D( MEPA_TRACE_GRP_GEN, "Get MAC Interface type %d\r\n", *mac_if);
    }

    return rc;
}

static mepa_rc lan887x_media_set(struct mepa_device *dev, mepa_media_interface_t media_if)
{
    mepa_rc rc = MESA_RC_ERROR;
    mepa_reset_param_t rst_conf = {media_if, MEPA_RESET_POINT_DEFAULT};

    if (dev != NULL) {
        rc = MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED;
        if ((media_if == MESA_PHY_MEDIA_IF_T1_100FX) || (media_if == MESA_PHY_MEDIA_IF_T1_1000FX)) {
            MEPA_ENTER(dev);
            //re-configure media interface
            rc = lan887x_int_reset(dev, &rst_conf);
            MEPA_EXIT(dev);
            T_D( MEPA_TRACE_GRP_GEN, "Set media type %d\r\n", media_if);
        }
    }

    return rc;
}

static mepa_rc lan887x_media_get(struct mepa_device *dev, mepa_media_interface_t *media_if)
{
    mepa_rc rc = MESA_RC_ERROR;

    if (dev != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);
        *media_if = data->media_intf;
        MEPA_EXIT(dev);

        T_D( MEPA_TRACE_GRP_GEN, "Get media type %d\r\n", *media_if);
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

    if (dev != NULL) {
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
    uint16_t int_mask = LAN887X_DEF_MASK, i;

    if (dev != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        MEPA_ENTER(dev);
        data->events = enable ? (data->events | event) : (data->events & ~event);
        for (i = 0; i < INTR_BIT_LEN; i++) {
            uint16_t mask = BIT(i);
            if ((data->events & mask) != ZERO) {
                int_mask = int_mask &  ~mask;
            }
        }
        rc = phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                            LAN887X_MX_CHIP_TOP_REG_INT_MSK, int_mask);
        MEPA_EXIT(dev);

        T_D( MEPA_TRACE_GRP_GEN, "set events=0x%x, int_mask=0x%x! rc=%d\r\n",
             data->events, int_mask, rc);
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

        T_D( MEPA_TRACE_GRP_GEN, "events configured 0x%x \r\n", *event);
    }

    return rc;
}

// Poll the status of currently enabled events/interrupts
static mepa_rc lan887x_event_status_poll(struct mepa_device *dev, mepa_event_t *const status)
{
    uint16_t val = 0;
    uint16_t int_mask = 0;
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && status != NULL) {
        phy_data_t *data = (phy_data_t *)dev->data;

        *status = 0;
        if (data != NULL) {
            MEPA_ENTER(dev);

            rc = phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                                LAN887X_MX_CHIP_TOP_REG_INT_MSK, &int_mask);
            if (rc == MEPA_RC_OK) {
                rc = phy_mmd_reg_rd(dev, MDIO_MMD_VEND1,
                                    LAN887X_MX_CHIP_TOP_REG_INT_STS, &val);
                if (rc == MEPA_RC_OK) {
                    //When 0, this interrupt is enabled.
                    //When 1, this interrupt is disabled.
                    val = val & ~(int_mask);
                    *status = val;
                    T_D( MEPA_TRACE_GRP_GEN, "events=0x%x(0x%x) polled 0x%x rc=%d\r\n", data->events, int_mask, *status, rc);
                }
            }
            MEPA_EXIT(dev);
        }
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
            (gpio_conf->mode >= MEPA_GPIO_MODE_LED_LINK_ACTIVITY &&
             gpio_conf->mode <= MEPA_GPIO_MODE_LED_DISABLE_EXTENDED)) {
            MEPA_ENTER(dev);
            rc = lan887x_config_led(dev, gpio_conf);
            MEPA_EXIT(dev);
        }
    }

    return rc;
}

static mepa_rc lan887x_info_get(mepa_device_t *dev, mepa_phy_info_t *const phy_info)
{
    mepa_rc rc = MEPA_RC_ERROR;

    if (dev != NULL && phy_info != NULL) {
        phy_data_t *data = (phy_data_t *)(dev->data);

        if (data != NULL) {
            if (data->init_done == PHY_TRUE) {
                MEPA_ENTER(dev);
                phy_info->part_number = data->dev.model;
                phy_info->revision = data->dev.rev;
                phy_info->cap = (data->conf.speed == MESA_SPEED_100M ? MEPA_CAP_SPEED_MASK_1G : MEPA_CAP_TS_MASK_NONE);
                MEPA_EXIT(dev);

                rc = MEPA_RC_OK;
            }
        }
    }
    T_D( MEPA_TRACE_GRP_GEN, "phy_info_get rc=%d\r\n", rc);

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

mepa_drivers_t mepa_lan887x_driver_init(void)
{
    mepa_drivers_t result;
    uint8_t idx = 0;
    static mepa_driver_t lan887x_driver[LAN887X_PHY_ID_MAX];

    for (idx = 0; idx < ARRAY_SIZE(lan887x_driver); idx++) {
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
        lan887x_drv->mepa_driver_phy_info_get       = lan887x_info_get;
        lan887x_drv->mepa_debug_info_dump           = lan887x_debug_info;
        lan887x_drv->mepa_driver_clause22_read      = lan887x_reg_read;
        lan887x_drv->mepa_driver_clause22_write     = lan887x_reg_write;
        lan887x_drv->mepa_driver_clause45_read      = lan887x_mmd_reg_read;
        lan887x_drv->mepa_driver_clause45_write     = lan887x_mmd_reg_write;
        lan887x_drv->mepa_tc10 = NULL;
    }

    result.phy_drv = &lan887x_driver[0];
    result.count = LAN887X_PHY_ID_MAX;

    return result;
}
