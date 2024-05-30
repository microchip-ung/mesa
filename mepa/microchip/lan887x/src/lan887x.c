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
/*
 * START of PHY Configurations
 */
static const struct phy_reg_map lan887x_phy_en[] = {
    {MDIO_MMD_VEND1, 0xF003U, 0x0008U},
    {MDIO_MMD_VEND1, 0xF005U, 0x0010U},
};

static const struct phy_reg_map lan887x_onetime_setup[] = {
    {MDIO_MMD_PMAPMD, 0x8080, 0x4008},
    {MDIO_MMD_PMAPMD, 0x8089, 0x0000},
    {MDIO_MMD_PMAPMD, 0x808D, 0x0040},
    {MDIO_MMD_PCS,    0x8213, 0x0008},
    {MDIO_MMD_PCS,    0x8204, 0x800D},
    {MDIO_MMD_VEND1,  0x0405, 0x0AB1},
    {MDIO_MMD_VEND1,  0x0411, 0x5274},
    {MDIO_MMD_VEND1,  0x0417, 0x0D74},
    {MDIO_MMD_VEND1,  0x041C, 0x0AEA},
    {MDIO_MMD_VEND1,  0x0425, 0x0360},
    {MDIO_MMD_VEND1,  0x0454, 0x0C30},
    {MDIO_MMD_VEND1,  0x0811, 0x2A78},
    {MDIO_MMD_VEND1,  0x0813, 0x1368},
    {MDIO_MMD_VEND1,  0x0825, 0x1354},
    {MDIO_MMD_VEND1,  0x0843, 0x3C84},
    {MDIO_MMD_VEND1,  0x0844, 0x3CA5},
    {MDIO_MMD_VEND1,  0x0845, 0x3CA5},
    {MDIO_MMD_VEND1,  0x0846, 0x3CA5},
    {MDIO_MMD_VEND1,  0x08EC, 0x0024},
    {MDIO_MMD_VEND1,  0x08EE, 0x227F},
    {MDIO_MMD_PCS,    0x8043, 0x1E00},
    {MDIO_MMD_PCS,    0x8048, 0x0FA1},
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
    { "chiptop_regs:PMA_CONTROL_T1", MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTRL},
    //SGMII or RGMII configuration
    { "mis_regs:MIS_CFG_REG0", MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0},
    { "mx_chip_top_regs:SGMII_CTL", MDIO_MMD_VEND1, LAN887X_MX_CHIP_TOP_REG_SGMII_CTL},
    { "mx_chip_top_regs:SGMII_MPLL_CTL", MDIO_MMD_VEND1, 0xF028},
    { "mx_chip_top_regs:SGMII_CTL_STS", MDIO_MMD_VEND1, 0xF02B},
    { "mx_chip_top_regs:SGMII_PCS_CFG", MDIO_MMD_VEND1, LAN887X_MX_CHIP_TOP_SGMII_PCS_CFG},
    { "mx_chip_top_regs:PCS_ANEG_CFG", MDIO_MMD_VEND1, 0xF035},
    { "mx_chip_top_regs:QSGMII_ANEG", MDIO_MMD_VEND1, LAN887X_MX_CHIP_TOP_QSGMII_ANEG_REG},
    { "mx_chip_top_regs:SGMII_MPLL_CTL", MDIO_MMD_VEND1, LAN887X_MX_CHIP_TOP_SGMII_MPLL_CTL},
    // start - SGMII debugging
    { "mx_chip_top_regs:SKU_DBG_STS", MDIO_MMD_VEND1, 0xF041},
    { "mx_chip_top_regs:EFUSE_READ_DAT9", MDIO_MMD_VEND1, 0xF209},
    { "mx_uvov_regs:UVOV_CFG2_0", MDIO_MMD_VEND1, 0xF22C},
    { "mx_uvov_regs:UVOV_CFG2_1", MDIO_MMD_VEND1, 0xF22D},
    { "mx_uvov_regs:UVOV_CFG2_2", MDIO_MMD_VEND1, 0xF22E},
    { "mx_uvov_regs:UVOV_CFG2_3", MDIO_MMD_VEND1, 0xF22F},
    // end - SGMII debugging
    // start - Aneg debugging
    { "mis_regs:MIS_DLL_CFG_REG0", MDIO_MMD_VEND1, LAN887X_MIS_TX_DLL_CFG_REG0},
    { "mis_regs:MIS_DLL_CFG_REG1", MDIO_MMD_VEND1, LAN887X_MIS_RX_DLL_CFG_REG1},
    { "aneg_regs:ANEG_CNTRL_REG1", MDIO_MMD_AN, 0x200},
    { "aneg_regs:ANEG_STAT_REG1", MDIO_MMD_AN, 0x201},
    { "aneg_regs:ANEG_ADV_REG1", MDIO_MMD_AN, 0x202},
    { "aneg_regs:ANEG_ADV_REG2", MDIO_MMD_AN, 0x203},
    { "aneg_regs:ANEG_ADV_REG3", MDIO_MMD_AN, 0x204},
    { "aneg_regs:ANEG_LP_AB_REG1", MDIO_MMD_AN, 0x205},
    { "aneg_regs:ANEG_LP_AB_REG2", MDIO_MMD_AN, 0x206},
    { "aneg_regs:ANEG_LP_AB_REG3", MDIO_MMD_AN, 0x207},
    { "aneg_regs:VEND_DBG_CTRL_STAT_REG", MDIO_MMD_AN, 0x8013},
    // end - Aneg debugging
    { "tc10_dev30_common:REG15", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_REG_REG15},
    { "tc10_dev30_common:TC10_MISC33", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC33},
    { "tc10_dev30_common:TC10_MISC32", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32},
    { "tc10_dev30_common:TC10_MISC46", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC46},
    { "tc10_dev30_common:TC10_MISC36", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36},
    { "tc10_dev30_common:TC10_SENDZ_MINWAIT_TMR_CFG", MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_SENDZ_MINWAIT_TMR_CFG},
    { "misc_regs:REG16", MDIO_MMD_VEND1, LAN887X_MISC_REGS_REG16},
    { "misc_regs:MISC37", MDIO_MMD_VEND1, LAN887X_MISC_REGS_MISC37},
    { "statistics:TX Good Count", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG0},
    { "statistics:RX Good Count", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG1},
    { "statistics:RX ERR Count detected by PCS", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG3},
    { "statistics:TX CRC ERR Count", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG4},
    { "statistics:RX CRC ERR Count", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG5},
    { "statistics:RX ERR Count for SGMII MII2GMII", MDIO_MMD_VEND1, LAN887X_MIS_PKT_STAT_REG6},
};

#ifdef MEPA_lan887x_static_mem
static mepa_device_t lan887x_device[LAN887X_PHY_MAX];
static phy_data_t lan887x_data[LAN887X_PHY_MAX];
#endif

static mepa_rc lan887x_phy_cable_diag_start(mepa_device_t *dev, mepa_bool_t is_hybrid, mepa_bool_t ms_mode);
static mepa_rc lan887x_aneg_read_status(mepa_device_t *dev, mepa_status_t *status);
static mepa_rc lan887x_int_reset(mepa_device_t *dev, const lan887x_reset_typ typ);
static mepa_rc lan887x_phy_init(mepa_device_t *const dev);
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

//callout print API
static void phy_dbg_pr (mepa_device_t *const dev, const mepa_debug_print_t pr,
                        uint8_t mmd, uint16_t offset, const char *str)
{
    uint16_t value = 0;

    if (MEPA_RC_OK == phy_mmd_reg_rd(dev, mmd, offset, &value)) {
        (void) pr("%-45s:\t[0X%02X].[0X%X]\t=\t0X%08X \r\n", str, mmd, offset, value);
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
    if (rc == MEPA_RC_OK) {
        rc = phy_mmd_reg_rd(dev, MDIO_MMD_PMAPMD, MDIO_STAT1, &reg_val);
        if (rc == MEPA_RC_OK) {
            status->link = ((reg_val & MDIO_STAT1_LSTATUS) != ZERO);
            data->link_status = status->link;
        }
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

static mepa_rc lan887x_tc10_init(mepa_device_t *const dev)
{
    uint16_t reg_val = LAN887X_DEV30_COMMON_TC10_MISC33_WK_DEB_VAL;
    mepa_rc rc = MEPA_RC_OK;

    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MISC_REGS_REG16,
                                        LAN887X_MISC_REGS_REG16_IGNORE_IDLE_WITH_WUR_LPS,
                                        LAN887X_MISC_REGS_REG16_IGNORE_IDLE_WITH_WUR_LPS));
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_REG_REG15,
                                        LAN887X_DEV30_COMMON_TC10_REG_REG15_WK_OUT_PIN_REQ,
                                        LAN887X_DEV30_COMMON_TC10_REG_REG15_WK_OUT_PIN_REQ));
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC33,
                                    (reg_val << 8) |
                                    LAN887X_DEV30_COMMON_TC10_MISC33_WK_OUT_LEN));
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC32,
                                        LAN887X_DEV30_COMMON_TC10_MISC32_VAL,
                                        LAN887X_DEV30_COMMON_TC10_MISC32_VAL));
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC46,
                                        LAN887X_DEV30_COMMON_TC10_MISC46_WK_PORT_TEST_MASK,
                                        LAN887X_DEV30_COMMON_TC10_MISC46_WK_PORT_TEST_VAL));
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_DEV30_COMMON_TC10_MISC36,
                                        LAN887X_DEV30_COMMON_TC10_MISC36_VAL,
                                        LAN887X_DEV30_COMMON_TC10_MISC36_VAL));
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MISC_REGS_MISC37,
                                        LAN887X_MISC_REGS_MISC37_EN_TC10_SLEEP_SILENT,
                                        LAN887X_MISC_REGS_MISC37_EN_TC10_SLEEP_SILENT));
error:
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

static mepa_rc lan887x_rgmii_setup(mepa_device_t *const dev, mepa_port_interface_t mac_if)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t txc = 0;
    uint16_t rxc = 0;
    mepa_bool_t updated = PHY_TRUE;

    // Disable SGMII_CTL
    MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                            LAN887X_MX_CHIP_TOP_REG_SGMII_CTL,
                                            LAN887X_MX_CHIP_TOP_REG_SGMII_MUX_EN));

    // Enable MAC_MODE = RGMII
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                        LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL,
                                        LAN887X_MIS_CFG_REG0_MAC_MODE_RGMII));

    // PCS_ENA  = 0
    MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                            LAN887X_MX_CHIP_TOP_SGMII_PCS_CFG,
                                            LAN887X_MX_CHIP_TOP_SGMII_PCS_ENA));

    // Errata enabled in SGMII, need to disable bit for RGMII
    MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                            LAN887X_MIS_CFG_REG0_RCLKOUT_DIS));

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
        T_I( MEPA_TRACE_GRP_GEN, "PHY MAC interface is not RGMII(%d)!\n", mac_if);
        updated = PHY_FALSE;
        break;
    }

    if (updated == PHY_TRUE) {
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

static mepa_rc lan887x_sgmii_setup(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;

    // Enable SGMII_CTL
    MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                          LAN887X_MX_CHIP_TOP_REG_SGMII_CTL,
                                          LAN887X_MX_CHIP_TOP_REG_SGMII_MUX_EN));

    if (IS_LAN887X_B0_PROTOS(data->dev.id)) {
        //FIXME: LAN9692 specific WA
        //      Remove this code one parts are efused for 3.3v
        //       this might cause damage to boards
        MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                              LAN887X_MX_CHIP_TOP_REG_SGMII_CTL,
                                              (LAN887X_MX_CHIP_TOP_REG_SGMII_VREG_BYP_CTL |
                                               LAN887X_MX_CHIP_TOP_REG_SGMII_XAUI_RST)));
    }

    // Enable MAC_MODE = SGMII
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                        LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL,
                                        LAN887X_MIS_CFG_REG0_MAC_MODE_SGMII));

    // ERRATA: RCLKOUT disable for disabling RGMII clock and reduce power consumption
    MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1, LAN887X_MIS_CFG_REG0,
                                          LAN887X_MIS_CFG_REG0_RCLKOUT_DIS));

    // PCS_ENA  = 1
    MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                          LAN887X_MX_CHIP_TOP_SGMII_PCS_CFG,
                                          LAN887X_MX_CHIP_TOP_SGMII_PCS_ENA));

    // restart SGMII_PCS_ANEG
    if (data->conf.mac_if_aneg_ena == PHY_TRUE) {
        MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                              LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG,
                                              (LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG_EN |
                                               LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG_RST)));
        //QSGMII ANEG Enable
        MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1,
                                              LAN887X_MX_CHIP_TOP_QSGMII_ANEG_REG,
                                              LAN887X_MX_CHIP_TOP_QSGMII_ANEG_EN));

        T_I( MEPA_TRACE_GRP_GEN, "PHY port=%u SGMII aneg enabled!\n", data->port_no);
    } else {
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                                LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG,
                                                LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG_EN));

        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                                LAN887X_MX_CHIP_TOP_QSGMII_ANEG_REG,
                                                LAN887X_MX_CHIP_TOP_QSGMII_ANEG_EN));

        T_I( MEPA_TRACE_GRP_GEN, "PHY port=%u SGMII aneg disabled!\n", data->port_no);
    }

    T_I( MEPA_TRACE_GRP_GEN, "PHY SGMII setup complete!\n");

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

static mepa_rc lan887x_config_mac(struct mepa_device *dev)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (data->mac_if >= MESA_PORT_INTERFACE_RGMII &&
        data->mac_if <= MESA_PORT_INTERFACE_RGMII_TXID) {
        MEPA_RC_GOTO(rc, lan887x_rgmii_setup(dev, data->mac_if));
    } else if (data->mac_if == MESA_PORT_INTERFACE_SGMII) {
        MEPA_RC_GOTO(rc, lan887x_sgmii_setup(dev));
    } else {
        // Disable RGMII
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1,
                                                LAN887X_MIS_CFG_REG0,
                                                LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL));
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_setup(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *) dev->data;

    MEPA_RC_GOTO(rc, phy_get_device_info(dev));

    if (!data->init_done) {
        //LAN887X B0 Protos ONLY!
        if (IS_LAN887X_B0_PROTOS(data->dev.id)) {
            phy_cfg_regs(dev, lan887x_phy_en, ARRAY_SIZE(lan887x_phy_en), PHY_TRUE);
        }
    }

    data->init_done = PHY_TRUE;

    //LAN887X B0 PHY Setup
    phy_cfg_regs(dev, lan887x_onetime_setup, ARRAY_SIZE(lan887x_onetime_setup), PHY_FALSE);

    // Initialize TC10 required config
    MEPA_RC_GOTO(rc, lan887x_tc10_init(dev));

    MEPA_RC_GOTO(rc, lan887x_phy_init(dev));

    //T_D( MEPA_TRACE_GRP_GEN, "PHY port=%u setup complete!\n", data->port_no);

    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_phy_cfg_clr(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    mepa_rc rc = MEPA_RC_OK;

    //clear isolate bit
    MEPA_RC_GOTO(rc, phy_reg_clear_bits(dev, MII_BMCR, BMCR_ISOLATE));

    //clear loopback if it is setup in prev. config
    MEPA_RC_GOTO(rc, lan887x_setup_lpbk(dev, NULL));

    //Setup events
    MEPA_RC_GOTO(rc, lan887x_int_events_set(dev, data->events, PHY_TRUE));

error:
    return rc;
}

static mepa_rc lan887x_phy_init(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *) dev->data;
    mepa_rc rc = MEPA_RC_OK;

    //MAC Setup
    MEPA_RC_GOTO(rc, lan887x_config_mac(dev));

    //LED setup
    MEPA_RC_GOTO(rc, lan887x_config_led(dev, &data->led3_conf));

    //clear config
    MEPA_RC_GOTO(rc, lan887x_phy_cfg_clr(dev));

    rc = MEPA_RC_OK;

error:
    return rc;
}

struct lan887x_regwr_map {
    u8  mmd;
    u16 reg;
    u16 val;
};

static int lan887x_100m_scripts(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    int ret;
    uint16_t i;
    mepa_rc rc = MEPA_RC_OK;

    if (data->conf.speed != MESA_SPEED_AUTO) {
        if (data->conf.man_neg == MEPA_MANUAL_NEG_REF) {
            static const struct lan887x_regwr_map phy_cfg[] = {
                {MDIO_MMD_PMAPMD, 0x808B, 0x00B8},
                {MDIO_MMD_PMAPMD, 0x80B0, 0x0038},
                {MDIO_MMD_VEND1,  0x0422, 0x000F},
            };

            for (i = 0; i < ARRAY_SIZE(phy_cfg); i++) {
                ret = phy_mmd_reg_wr(dev, phy_cfg[i].mmd, phy_cfg[i].reg, phy_cfg[i].val);
                if (ret < 0) {
                    return ret;
                }
            }
        } else {
            static const struct lan887x_regwr_map phy_cfg[] = {
                {MDIO_MMD_PMAPMD, 0x808B, 0x0038},
                {MDIO_MMD_VEND1, 0x0422, 0x0014},
            };

            for (i = 0; i < ARRAY_SIZE(phy_cfg); i++) {
                ret = phy_mmd_reg_wr(dev, phy_cfg[i].mmd, phy_cfg[i].reg, phy_cfg[i].val);
                if (ret < 0) {
                    return ret;
                }
            }
        }
    } else {
        static const struct lan887x_regwr_map phy_cfg[] = {
            {MDIO_MMD_PMAPMD, 0x808B, 0x00B8},
            {MDIO_MMD_PMAPMD, 0x80B0, 0x0038},
            {MDIO_MMD_VEND1,  0x0422, 0x000F},
        };

        for (i = 0; i < ARRAY_SIZE(phy_cfg); i++) {
            ret = phy_mmd_reg_wr(dev, phy_cfg[i].mmd, phy_cfg[i].reg, phy_cfg[i].val);
            if (ret < 0) {
                return ret;
            }
        }
    }

    MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26,
                                          LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN));
error:
    return rc;
}

static int lan887x_1000m_scripts(mepa_device_t *const dev)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    static const struct lan887x_regwr_map phy_cfg[] = {
        {MDIO_MMD_PMAPMD, 0x80B0, 0x003F},
        {MDIO_MMD_PMAPMD, 0x808B, 0x00B8},
    };
    int ret;
    uint16_t i;
    mepa_rc rc = MEPA_RC_OK;

    for (i = 0; i < ARRAY_SIZE(phy_cfg); i++) {
        ret = phy_mmd_reg_wr(dev, phy_cfg[i].mmd, phy_cfg[i].reg, phy_cfg[i].val);
        if (ret < 0) {
            return ret;
        }
    }

    if (data->conf.speed == MESA_SPEED_AUTO) {
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_PMAPMD,
                                                LAN887X_PMA_1000T1_DSP_PMA_CTL_REG,
                                                LAN887X_PMA_1000T1_DSP_PMA_LNK_SYNC));
        MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26,
                                              LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN));

    } else {
        MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_PMAPMD, LAN887X_PMA_1000T1_DSP_PMA_CTL_REG,
                                              LAN887X_PMA_1000T1_DSP_PMA_LNK_SYNC));
    }

error:
    return rc;
}

static mepa_bool_t lan887x_is_1g(struct mepa_device *dev)
{
    mepa_bool_t gig_en = PHY_FALSE;
    phy_data_t *data = (phy_data_t *)dev->data;

    if (data->conf.speed == MESA_SPEED_AUTO) {
        if (data->media_intf != MESA_PHY_MEDIA_IF_T1_100FX &&
            data->conf.aneg.speed_1g_fdx == PHY_TRUE) {
            gig_en = PHY_TRUE;
        }
    } else {
        if (data->media_intf != MESA_PHY_MEDIA_IF_T1_100FX &&
            data->conf.speed == MESA_SPEED_1G) {
            gig_en = PHY_TRUE;
        }
    }

    return gig_en;
}

static void lan887x_link_setup(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;

    if (lan887x_is_1g(dev) == PHY_TRUE) {
        MEPA_RC_GOTO(rc, lan887x_1000m_scripts(dev));
    } else {
        MEPA_RC_GOTO(rc, lan887x_100m_scripts(dev));
    }

error:
    return;
}

static int lan887x_pma_baset1_setup_forced(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    uint16_t reg_val = 0;

    /* mode configuration */
    if (data->conf.man_neg == MEPA_MANUAL_NEG_REF) {
        reg_val |= MDIO_PMA_PMD_BT1_CTRL_CFG_MST;
    }

    /* speed configuration */
    if (lan887x_is_1g(dev) == PHY_TRUE) {
        reg_val |= LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_1000;
    }

    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTRL, reg_val));

error:
    return rc;
}

static mepa_rc lan887x_init_conf(mepa_device_t *const dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_manual_neg_t mode_ms = data->conf.man_neg;

    if (data->conf.admin.enable == PHY_TRUE) {

        //clear power down bit
        MEPA_RC_GOTO(rc, phy_reg_clear_bits(dev, MII_BMCR, BMCR_PDOWN));

        if (data->conf.speed == MESA_SPEED_AUTO) {
            u16 adv_r1 = 0;
            u16 adv_r2_mask = 0;
            u16 adv_r2 = 0;

            //Errata-949: 100M master issue. Dual speed in Aneg is not supported.
            //Recommendations:
            //  1. speed can be Speed_1000T1(0x80) or Speed_100T1(0x20)
            //     and only advertise one speed (recommended),
            //     or ANEG(0xA0) for dual speed (not currently recommended)
            //  2. mode can be MASTER/SLAVE for forcing the DUT to a certain resolution (not recommended)
            //     or ANEG to allow ANEG state machine to determine mode (recommended).

            adv_r2_mask = (MDIO_AN_T1_ADV_M_B1000 |
                           MDIO_AN_T1_ADV_M_B100 |
                           MDIO_AN_T1_ADV_M_MST);

            // Advertise preferred master/slave mode
            if (mode_ms != MEPA_MANUAL_NEG_CLIENT) {
                adv_r2 |= MDIO_AN_T1_ADV_M_MST;
            }

            //Errata-949: 100M master issue. Dual speed in Aneg is not supported.
            if (lan887x_is_1g(dev) == PHY_TRUE) {
                //adv_r2 |= MDIO_AN_T1_ADV_M_B100 | MDIO_AN_T1_ADV_M_B1000;
                adv_r2 |= MDIO_AN_T1_ADV_M_B1000;
            } else {
                adv_r2 |= MDIO_AN_T1_ADV_M_B100;
            }

            MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_M, adv_r2_mask, adv_r2));

            /* NOTE:
             *  The Base Page value is transferred to mr_adv_ability when register 7.514 is written.
             *  Therefore, registers 7.515 and 7.516 should be written before 7.514.
             */
            MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_AN, MDIO_AN_T1_ADV_L, adv_r1));
        } else {
            MEPA_RC_GOTO(rc, lan887x_pma_baset1_setup_forced(dev));
        }

        T_I( MEPA_TRACE_GRP_GEN, "PHY port-%u init_conf aneg %sabled, mode %s-%s speed %sM!\n",
             data->port_no, (data->conf.speed == MESA_SPEED_AUTO ? "en" : "dis"),
             (data->conf.speed == MESA_SPEED_AUTO ? "preferred" : "forced"),
             (mode_ms == MEPA_MANUAL_NEG_REF ? "master" : "slave"),
             (data->conf.speed == MESA_SPEED_100M ? "100" :
              (data->conf.speed == MESA_SPEED_1G ? "1000" :
               (data->conf.speed == MESA_SPEED_AUTO ? "auto" : "unknown"))));

        // MLX link setup
        lan887x_link_setup(dev);

        if (data->conf.speed == MESA_SPEED_AUTO) {
            MEPA_RC_GOTO(rc, phy_mmd_reg_set_bits(dev, MDIO_MMD_AN, MDIO_AN_T1_CTRL,
                                                  MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART));
        }
    }

    //T_D( MEPA_TRACE_GRP_GEN, "PHY port-%u configuration complete!\n", data->port_no);

    rc = MEPA_RC_OK;

error:
    return rc;
}

static mepa_rc lan887x_phy_reset(mepa_device_t *dev, mepa_bool_t hard_reset)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_bool_t done = PHY_FALSE;
    mepa_bool_t timeout = PHY_FALSE;
    mepa_mtimer_t   timer = { 0 };

    if (hard_reset) {
        MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                        LAN887X_MX_CHIP_TOP_REG_HARD_RST,
                                        LAN887X_MX_CHIP_TOP_RESET_));
        LAN887X_NSLEEP(5000U);
    } else {
        // clear 1000m link sync
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_PMAPMD, LAN887X_PMA_1000T1_DSP_PMA_CTL_REG,
                                                LAN887X_PMA_1000T1_DSP_PMA_LNK_SYNC));

        // clear 100m link sync
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26,
                                                LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN));

        // disable aneg
        MEPA_RC_GOTO(rc, phy_mmd_reg_clear_bits(dev, MDIO_MMD_AN, MDIO_AN_T1_CTRL,
                                                MDIO_AN_CTRL1_ENABLE));

        // chiptop soft-reset to allow the speed/mode change
        MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                        LAN887X_MX_CHIP_TOP_REG_SOFT_RST,
                                        LAN887X_MX_CHIP_TOP_RESET_));

        // CL22 soft-reset to let the link re-train
        MEPA_RC_GOTO(rc, phy_reg_set_bits(dev, MII_BMCR, BMCR_RESET));

        LAN887X_MTIMER_START(&timer, 4000U);

        // wait for cable diag to finish or timeout (4 seconds)
        while (done == PHY_FALSE && timeout == PHY_FALSE) {
            uint16_t tmp = 0;

            timeout = MEPA_MTIMER_TIMEOUT(&timer);
            (void) phy_reg_rd(dev, MII_BMCR, &tmp);
            if (!((tmp & BMCR_RESET) == BMCR_RESET)) {
                done = PHY_TRUE;
            }
        }
        if (done == PHY_FALSE) {
            T_E( MEPA_TRACE_GRP_GEN, "PHY soft-reset timedout! \r\n");
        }
    }

    //T_D( MEPA_TRACE_GRP_GEN, "PHY %s reset done! \r\n", (hard_reset ? "hard" : "soft"));

error:
    return rc;
}

static mepa_rc lan887x_check_media(struct mepa_device *dev, mepa_media_interface_t media_if, mesa_port_speed_t speed)
{
    int rc = MEPA_RC_ERR_KR_CONF_NOT_SUPPORTED;

    if ((media_if == MESA_PHY_MEDIA_IF_T1_100FX) || (media_if == MESA_PHY_MEDIA_IF_T1_1000FX)) {
        phy_data_t *data = (phy_data_t *)dev->data;

        // speed selection based on media type
        if (media_if == MESA_PHY_MEDIA_IF_T1_100FX) {
            if ((speed == MESA_SPEED_AUTO &&
                 data->conf.aneg.speed_100m_fdx != PHY_TRUE) ||
                (speed != MESA_SPEED_AUTO &&
                 speed != MESA_SPEED_100M)) {
                rc = MEPA_RC_ERR_PARM;
                goto error;
            }
        }
        rc = MEPA_RC_OK;
    }

error:
    return rc;
}

static mepa_rc lan887x_config_set(mepa_device_t *dev, const mepa_conf_t *config)
{
    mepa_rc rc = MEPA_RC_OK;
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_bool_t re_config = PHY_FALSE;
    lan887x_reset_typ type = LAN887X_RST_SOFT;

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

        data->conf.fdx = PHY_TRUE;
        data->conf.flow_control = config->flow_control;
        data->conf.aneg.speed_100m_fdx = config->aneg.speed_100m_fdx;
        data->conf.aneg.speed_1g_fdx = config->aneg.speed_1g_fdx;

        // Setup MAC ANEG
        if (data->conf.mac_if_aneg_ena != config->mac_if_aneg_ena) {
            re_config = PHY_TRUE;
            data->conf.mac_if_aneg_ena = config->mac_if_aneg_ena;
            type = LAN887X_RST_SOFT_MAC;
        }

        // Setup Speed
        if (data->conf.speed != speed) {
            //check media/speed/aneg capabilities
            MEPA_RC_GOTO(rc, lan887x_check_media(dev, data->media_intf, speed));
            re_config = PHY_TRUE;
            data->conf.speed = speed;
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
        }

        if (re_config == PHY_TRUE) {
            //config change and admin enable
            if (data->conf.admin.enable == PHY_TRUE) {
                MEPA_RC_GOTO(rc, lan887x_int_reset(dev, type));
            } else {
                //Power down
                MEPA_RC_GOTO(rc, phy_reg_set_bits(dev, MII_BMCR, BMCR_PDOWN));
            }
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
    if (data->conf.speed == MESA_SPEED_AUTO) {
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

static mepa_rc lan887x_cd_reset(mepa_device_t *dev, mepa_bool_t cd_done)
{
    mepa_rc rc = MEPA_RC_OK;
    lan887x_reset_typ typ = LAN887X_RST_HARD_ONLY;


    if (cd_done) {
        typ = LAN887X_RST_HARD;
    }
    MEPA_RC_GOTO(rc, lan887x_int_reset(dev, typ));

error:
    return rc;

}

static mepa_rc lan887x_int_reset(mepa_device_t *dev, const lan887x_reset_typ typ)
{
    mepa_rc rc = MEPA_RC_OK;

    T_I( MEPA_TRACE_GRP_GEN, "PHY reset & initialize! \r\n");

    //reset PHY
    if (typ == LAN887X_RST_HARD || typ == LAN887X_RST_HARD_ONLY) { //hard-reset
        MEPA_RC_GOTO(rc, lan887x_phy_reset(dev, PHY_TRUE));

        if (typ == LAN887X_RST_HARD_ONLY) {
            rc = MEPA_RC_OK;
            goto error;
        }
        MEPA_RC_GOTO(rc, lan887x_phy_setup(dev));
        T_I( MEPA_TRACE_GRP_GEN, "PHY re-configured after reset!\n");
    } else {
        if (typ != LAN887X_RST_SKIP_TO_CONF) { //soft-reset
            MEPA_RC_GOTO(rc, lan887x_phy_reset(dev, PHY_FALSE));
        }
    }

    if (typ == LAN887X_RST_SOFT_EXT ||
        typ == LAN887X_RST_HARD) {
        //clear config
        MEPA_RC_GOTO(rc, lan887x_phy_cfg_clr(dev));
    }

    //configure after reset
    if (typ == LAN887X_RST_SOFT_MAC ||
        typ == LAN887X_RST_SKIP_TO_CONF) {
        MEPA_RC_GOTO(rc, lan887x_config_mac(dev));
    }

    //For the first time init_conf will take care of all phy setup
    MEPA_RC_GOTO(rc, lan887x_init_conf(dev));

    MEPA_RC_GOTO(rc, phy_get_device_info(dev));

#if 0 //FIXME: we may not need this phy reset will not affect registers
    // tc10 config
    MEPA_RC_GOTO(rc, lan887x_phy_tc10_set_config(dev, &data->tc10_cfg));
#endif

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
    mepa_rc rc = MEPA_RC_OK;
    float distance = -1.0F;
    lan887x_cd_status_t detect = LAN87XX_CABLE_TEST_OK;

    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_cable_diag_result_t *res = &(data->cd_res);

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
    neg_peak_cycle = (neg_peak_time >> 7) & 0x7FU;
    neg_peak_phase = neg_peak_time & 0x7FU;
    neg_peak_in_phases = (neg_peak_cycle * 96U) + neg_peak_phase;

    /* Deriving the status of cable */
    if (pos_peak > noise_margin && neg_peak > noise_margin && gain_idx > 0U) {
        if (pos_peak_in_phases > 0U &&
            pos_peak_in_phases > neg_peak_in_phases &&
            ((pos_peak_in_phases - neg_peak_in_phases) >= min_time_diff) &&
            ((pos_peak_in_phases - neg_peak_in_phases) < max_time_diff)) {
            detect = LAN87XX_CABLE_TEST_SHORT;
        } else if (neg_peak_in_phases > 0U &&
                   neg_peak_in_phases > pos_peak_in_phases &&
                   ((neg_peak_in_phases - pos_peak_in_phases) >= min_time_diff) &&
                   ((neg_peak_in_phases - pos_peak_in_phases) < max_time_diff)) {
            detect = LAN87XX_CABLE_TEST_OPEN;
        } else {
            detect = LAN87XX_CABLE_TEST_OK;
        }
    } else {
        detect = LAN87XX_CABLE_TEST_OK;
    }


    if (detect == LAN87XX_CABLE_TEST_OK) {
        distance = 0.0F;
        /*** SOFT RESET to restore configuration ***/
        MEPA_RC_GOTO(rc, lan887x_cd_reset(dev, PHY_TRUE));
    } else {
        //For Hybrid values
        MEPA_RC_GOTO(rc, lan887x_phy_cable_diag_start(dev, PHY_TRUE, ms_mode));
        /* read hybrid results */
        (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, 0x49CU, &pos_peak_time_hybrid);

        /*** SOFT RESET to restore configuration ***/
        (void) lan887x_cd_reset(dev, PHY_FALSE);

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
        if (detect == LAN87XX_CABLE_TEST_SHORT) {
            diff_dist = (neg_peak_in_phases - pos_peak_in_phases_hybrid);
        } else {
            diff_dist = (pos_peak_in_phases - pos_peak_in_phases_hybrid);
        }
        distance = ((((float)diff_dist) * 15953.0F) / 1000000.0F);
    }

    /* Set cable length.
     * Note: Length will have no decimal part as it is defined
     * in unsigned int and have variation of -/+ 1 meter.
     */
    res->length[0] = ((uint8_t)distance) & 0xFFU;

    // Set status
    switch (detect) {
    case LAN87XX_CABLE_TEST_SHORT:
        //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status SHORT!\r\n");
        res->status[0] = MESA_VERIPHY_STATUS_SHORT;
        break;
    case LAN87XX_CABLE_TEST_OK:
        //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status OK!\r\n");
        res->status[0] = MESA_VERIPHY_STATUS_OK;
        break;
    case LAN87XX_CABLE_TEST_OPEN:
    default:
        //T_D( MEPA_TRACE_GRP_GEN, "PHY cable diag status OPEN!\r\n");
        res->status[0] = MESA_VERIPHY_STATUS_OPEN;
        break;
    }

error:
    return rc;
}

static mepa_rc lan887x_phy_cable_diag_common(mepa_device_t *dev, mepa_bool_t is_hybrid, mepa_bool_t ms_mode)
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
    mepa_rc rc = MEPA_RC_OK;
    uint8_t i;

    //setup master/slave based on ms_mode
    uint16_t ms_val = (ms_mode == PHY_TRUE ? MDIO_PMA_PMD_BT1_CTRL_CFG_MST : 0U);

    /*** SOFT RESET ONLY ***/
    MEPA_RC_GOTO(rc, lan887x_cd_reset(dev, PHY_FALSE));

    /* Forcing DUT to master mode, avoids headaches and
     * we don't care about mode during diagnostics
     */
    MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_PMAPMD, MDIO_PMA_PMD_BT1_CTRL, ms_val));

    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1,
                                        LAN887X_DSP_CALIB_CONFIG_100, 0x0U,
                                        LAN887X_DSP_CALIB_CONFIG_100_VAL));

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

    /* HW_INIT 100T1, Get DUT running in 100T1 mode */
    MEPA_RC_GOTO(rc, phy_mmd_reg_modify(dev, MDIO_MMD_VEND1, LAN887X_MIS_100T1_SMI_REG26,
                                        LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN,
                                        LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN));

    LAN887X_NSLEEP(1U);

error:
    return rc;
}

static mepa_rc lan887x_phy_cable_diag_start(mepa_device_t *dev, mepa_bool_t is_hybrid, mepa_bool_t ms_mode)
{
    phy_data_t *data = (phy_data_t *)dev->data;
    mepa_rc rc = MEPA_RC_INV_STATE;

    if (data->init_done && data->conf.admin.enable) {
        mepa_bool_t diagTimeout = PHY_FALSE;
        mepa_bool_t bDone = PHY_FALSE;
        mepa_mtimer_t   timer = { 0 };
        mepa_cable_diag_result_t *res = &(data->cd_res);

        MEPA_RC_GOTO(rc, lan887x_phy_cable_diag_common(dev, is_hybrid, ms_mode));

        /* start cable diag */
        MEPA_RC_GOTO(rc, phy_mmd_reg_wr(dev, MDIO_MMD_VEND1,
                                        LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                        LAN887X_DSP_REGS_START_CBL_DIAG_EN));

        LAN887X_MTIMER_START(&timer, 4000U);

        // wait for cable diag to finish or timeout (4 seconds)
        while (bDone == PHY_FALSE && diagTimeout == PHY_FALSE) {
            uint16_t tmp = 0;

            diagTimeout = MEPA_MTIMER_TIMEOUT(&timer);
            (void) phy_mmd_reg_rd(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100, &tmp);
            if ((tmp & LAN887X_DSP_REGS_START_CBL_DIAG_DONE) == LAN887X_DSP_REGS_START_CBL_DIAG_DONE) {
                bDone = PHY_TRUE;
            }
        }
        if (bDone == PHY_FALSE) {
            rc = MEPA_RC_INCOMPLETE;
            res->status[0] = MESA_VERIPHY_STATUS_ABNORM;
            T_E( MEPA_TRACE_GRP_GEN, "PHY cable_diag failed to start\r\n");
        } else {
            /* stop cable diag */
            (void) phy_mmd_reg_clear_bits(dev, MDIO_MMD_VEND1, LAN887X_DSP_REGS_START_CBL_DIAG_100,
                                          LAN887X_DSP_REGS_START_CBL_DIAG_EN);
            rc = MEPA_RC_OK;
        }
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

        //T_D( MEPA_TRACE_GRP_GEN, "static driver cleanup!!\n");
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
        //T_D( MEPA_TRACE_GRP_GEN, "dynamic driver cleanup!!\n");
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
    data->conf.fdx = PHY_TRUE;
    //mac-if aneg must be enabled always
    data->conf.mac_if_aneg_ena = PHY_TRUE;
    //phy aneg
    data->conf.speed = MESA_SPEED_AUTO;
    data->conf.aneg.speed_100m_fdx = PHY_TRUE;
    data->conf.aneg.speed_1g_fdx = PHY_TRUE;

    data->media_intf = MESA_PHY_MEDIA_IF_T1_1000FX;
    data->mac_if = MESA_PORT_INTERFACE_RGMII_RXID;

    data->led3_conf.led_num = MEPA_LED3;
    data->led3_conf.mode = MEPA_GPIO_MODE_LED_LINK_ACTIVITY;
    data->tc10_cfg.sleep_enable = PHY_TRUE;
    data->tc10_cfg.wakeup_mode = MEPA_TC10_WAKEUP_WUP_WAKEIN_ENABLE;
    data->tc10_cfg.wakeup_fwd_mode = MEPA_TC10_WAKEUP_FWD_WUP_WAKEOUT_ENABLE;
    data->tc10_cfg.wake_in_pol = MEPA_GPIO_MODE_ACTIVE_HIGH;
    data->tc10_cfg.wake_out_pol = MEPA_GPIO_MODE_ACTIVE_HIGH;
    data->tc10_cfg.wake_out_mode = MEPA_GPIO_MODE_PUSH_PULL;
    data->tc10_cfg.inh_mode = MEPA_GPIO_MODE_OPEN_SOURCE;

    //Cable diag data reset
    data->cd_res.link = PHY_LINKDOWN;
    data->cd_res.length[0] = 0;
    data->cd_res.status[0] = MESA_VERIPHY_STATUS_UNKNOWN;

    (void) lan887x_phy_setup(dev);

    T_I( MEPA_TRACE_GRP_GEN, "phy probe port=%u probed phy_id=0x%x", data->port_no, data->dev.id);
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

        //T_D( MEPA_TRACE_GRP_GEN, "static driver create!!\n");
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
        //T_D( MEPA_TRACE_GRP_GEN, "dynamic driver create!!\n");
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
        phy_data_t *data = (phy_data_t *)dev->data;

        MEPA_ENTER(dev);
        if (rst_conf != NULL) {
            // reset points are not supported
            if (rst_conf->reset_point != MEPA_RESET_POINT_DEFAULT &&
                rst_conf->reset_point != MEPA_RESET_POINT_PRE) {
                rc = MEPA_RC_OK;
                goto error;
            }

            if ((rst_conf->media_intf == MESA_PHY_MEDIA_IF_T1_100FX) ||
                (rst_conf->media_intf == MESA_PHY_MEDIA_IF_T1_1000FX)) {
                //re-configure media interface
                data->media_intf = rst_conf->media_intf;
            }
        }
        rc = lan887x_int_reset(dev, LAN887X_RST_SOFT_EXT);

error:
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
        if (data->conf.speed == MESA_SPEED_AUTO) {

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
        mepa_bool_t old_link = data->link_status;

        rc = MEPA_RC_OK;
        MEPA_ENTER(dev);

        //Current link status
        data->link_status = PHY_FALSE;

        if (data->conf.speed == MESA_SPEED_AUTO) {
            //Resolve speed
            MEPA_RC_GOTO(rc, lan887x_aneg_read_status(dev, status));
            //Resolve speed
            MEPA_RC_GOTO(rc, lan887x_aneg_resolve_master_slave(dev, &master_slave_state));
            status->master = (master_slave_state == MASTER_SLAVE_STATE_MASTER) ? PHY_TRUE : PHY_FALSE;
        } else {
            status->master = (data->conf.man_neg == MEPA_MANUAL_NEG_REF ? PHY_TRUE : PHY_FALSE);
            status->speed = data->conf.speed;
        }
        //T1 PHY supports only Full Duplex
        status->fdx = PHY_TRUE;
        data->dev.is_master = status->master;

        rc = phy_c45_get_link_status(dev, status);

        if (old_link != data->link_status) {
            T_D(MEPA_TRACE_GRP_GEN, "port=%u phy_id=0x%x poll state change %s[speed=%s, master=%s, aneg=%s]\r\n",
                data->port_no, data->dev.id,
                (status->link ? "up" : "down"),
                (status->speed == MESA_SPEED_1G ? "1G" :
                 (status->speed == MESA_SPEED_100M ? "100M" :
                  (status->speed == MESA_SPEED_AUTO ? "auto" : "Unknown"))),
                (status->master ? "master" : "slave"),
                (data->conf.speed == MESA_SPEED_AUTO ? "on" : "off"));
        }

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

        if ((mac_if >= MESA_PORT_INTERFACE_RGMII && mac_if <= MESA_PORT_INTERFACE_RGMII_TXID) ||
            mac_if == MESA_PORT_INTERFACE_SGMII) {
            phy_data_t *data = (phy_data_t *)dev->data;

            rc = MEPA_RC_OK;
            if (data->mac_if != mac_if) {
                MEPA_ENTER(dev);
                //Setup mac_if
                data->mac_if = mac_if;
                //reset PHY
                MEPA_RC_GOTO(rc, lan887x_int_reset(dev, LAN887X_RST_SOFT_MAC));
error:
                MEPA_EXIT(dev);
            }
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
            MEPA_ENTER(dev);

            if (data->media_intf != media_if) {
                //check media/speed/aneg capabilities
                MEPA_RC_GOTO(rc, lan887x_check_media(dev, media_if, data->conf.speed));
                data->media_intf = media_if;

                /* re-configure media interface
                   when aneg = true, apply change
                   when aneg = false, then following
                   old_media_type new_media_type old_speed  new_speed
                   1000_t1         100_t1        1000       100    ==> reset
                   1000_t1         100_t1         100       100    ===> No reset
                   100t1           1000t1         100       100   ===> No reset */
                if (data->conf.speed != MESA_SPEED_100M ||
                    data->conf.speed == MESA_SPEED_AUTO) {
                    MEPA_RC_GOTO(rc, lan887x_int_reset(dev, LAN887X_RST_SOFT));
                }
                //T_D( MEPA_TRACE_GRP_GEN, "Set media type %d! rc=%d.\r\n", media_if, rc);
            }
error:
            MEPA_EXIT(dev);
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

        MEPA_ENTER(dev);
        if (data->init_done == PHY_TRUE) {
            phy_info->part_number = data->dev.model;
            phy_info->revision = data->dev.rev;
            phy_info->cap = (data->conf.speed == MESA_SPEED_100M ? MEPA_CAP_SPEED_MASK_1G : MEPA_CAP_TS_MASK_NONE);

            rc = MEPA_RC_OK;
        }
        MEPA_EXIT(dev);
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
            MEPA_RC_GOTO(rc, lan887x_cd_reset(dev, PHY_TRUE));

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

mepa_drivers_t mepa_lan887x_driver_init(void)
{
    mepa_drivers_t result;
    static mepa_driver_t lan887x_driver[LAN887X_PHY_MAX];
    uint8_t idx = 0;

    for (idx = 0; idx < LAN887X_PHY_MAX; idx++) {
        mepa_driver_t *lan887x_drv = &lan887x_driver[idx];

        //Device ID & Mask
        lan887x_drv->id = LAN887X_PHY_ID_PRTO;//LAN8870_PHY_ID;
//        lan887x_drv->mask = LAN887X_PHY_ID_MASK;
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
        lan887x_drv->mepa_driver_isolate_mode_conf  = lan887x_isolate_mode_set;
        lan887x_drv->mepa_driver_cable_diag_start   = lan887x_cable_diag_start;
        lan887x_drv->mepa_driver_cable_diag_get     = lan887x_cable_diag_get;
        lan887x_drv->mepa_tc10                      = &lan887x_tc10_drivers;
    }

    result.phy_drv = &lan887x_driver[0];
    result.count = LAN887X_PHY_MAX;

    return result;
}
