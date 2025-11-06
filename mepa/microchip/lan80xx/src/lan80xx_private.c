// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
// Author : Sushovan Dec 2022
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_regs_util.h"
#include "regs_lan80xx.h"
#include "lan80xx_mcu.h"
#include "lan80xx.h"
#include "regs_lan80xx_dump.h"
#include "lan80xx_serdes_config.h"
#include "lan80xx_mcu_dfu.h"
#include "regs_lan80xx_mcu_mailbox.h"
#include "regs_lan80xx_mcu_io_mngt_misc.h"
#include "regs_lan80xx_gpio_ctrl.h"
#include "sha256/sha256.h"

#define BLOCK_RESET_1                                 (0xFFFFU)
#define BLOCK_RESET_2                                 (0xFFFFU)

#define LAN80XX_PCS1G_XMIT_DATA_MODE                  (0x3U)
#define MAX_SOURCE_EVENTS                             (31U)
#define MAX_ACK_TIMER                                 (15U)
#define LAN80XX_IS_BITSET(value, x)                   ( (((value) & (x)) != 0U) ? 1U : 0U )

/* Rx Equalizers Coefficients Maximum Values */
#define LAN80XX_CTLE_VGA_MAX_VAL                      (31U)
#define LAN80XX_CTLE_R_MAX_VAL                        (15U)
#define LAN80XX_CTLE_C_MAX_VAL                        (15U)

#define LAN80XX_XCONNECT_HOSTx_CFG(x)                 (LAN80XX_IOREG(MMD_ID_CROSS_CONN, 1U, (0xF108U + ((x) * 2U))))
#define LAN80XX_XCONNECT_LINEx_CFG(x)                 (LAN80XX_IOREG(MMD_ID_CROSS_CONN, 1U, (0xF110U + ((x) * 2U))))

#define LAN80XX_F_CROSS_CONNECT_SRC_SEL_DEFAULT_CH(x) (LAN80XX_ENCODE_BITFIELD((x), 0U, 2U))
#define LAN80XX_M_CROSS_CONNECT_SRC_SEL_DEFAULT_CH    (LAN80XX_ENCODE_BITMASK(0U, 2U))
#define LAN80XX_X_CROSS_CONNECT_SRC_SEL_DEFAULT_CH(x) (LAN80XX_EXTRACT_BITFIELD((x), 0U, 2U))

/* Tx Equalizers Coefficients Maximum Values */
#define LAN80XX_TX_AMP_CODE_MAX_VAL                   (101U)
#define LAN80XX_TX_TAP_DLY_MAX_VAL                    (31U)
#define LAN80XX_TX_TAP_ADV_MAX_VAL                    (15U)

/* Tx Equalizers Amplitude Control ranges */
#define LAN80XX_TX_AMP_CODE_RANGE_16                  (16U)
#define LAN80XX_TX_AMP_CODE_RANGE_32                  (32U)
#define LAN80XX_TX_AMP_CODE_RANGE_46                  (46U)
#define LAN80XX_TX_AMP_CODE_RANGE_58                  (58U)
#define LAN80XX_TX_AMP_CODE_RANGE_69                  (69U)
#define LAN80XX_TX_AMP_CODE_RANGE_79                  (79U)
#define LAN80XX_TX_AMP_CODE_RANGE_88                  (88U)
#define LAN80XX_TX_AMP_CODE_RANGE_102                 (102U)

/* Feature Disable */
#define LAN80XX_MACSEC_DISABLE     (1 << 0)
#define LAN80XX_1588_DISABLE       (1 << 1)
#define LAN80XX_25G_DISABLE        (1 << 2)
#define LAN80XX_QUAD_DISABLE       (1 << 3)
#define LAN80XX_CLEARTAGS_DISABLE  (1 << 4)
#define LAN80XX_MPLS_DISABLE       (1 << 5)

static uint8_t gau8RespBuffer[1024] = { 0 };

static mepa_rc RevokeAllOtpKeys_priv(const mepa_device_t  *dev);
static mepa_rc RevokeRotKey_priv(const mepa_device_t  *dev);
static mepa_rc OTPProgReplacementKey_priv(const mepa_device_t  *dev,
                                          u8 u8KeyNo,
                                          u8 *pu8KeyData);
static mepa_rc authenticate_fw_image();

mepa_rc lan80xx_block_reset_priv(mepa_device_t *dev)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (!data->base_dev) {
        T_E(MEPA_TRACE_GRP_GEN, "base dev not assigned for port number %u\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    mepa_device_t *base_dev = data->base_dev;
    phy25g_phy_state_t *base_data = (phy25g_phy_state_t *)base_dev->data;
    u16 block_rst1 = BLOCK_RESET_1;
    u16 block_rst2 = BLOCK_RESET_2;
    u32 port_no = data->port_no;
    if (port_no == base_data->port_no) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_GLOBAL_FAST_RESET_GLOBAL_FAST_RESET_0, block_rst1);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_GLOBAL_FAST_RESET_GLOBAL_FAST_RESET_1, block_rst2);

    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_identify_phy(mepa_device_t *dev, mepa_port_no_t port_no)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    uint32_t id = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MCU_IO_MNGT_MISC_DEVICE_ID_REG, &id);
    u16 phy_id = (uint16_t)(id & 0xFFFF);
    if (phy_id == 0) {
        data->dev.devid = LAN80XX_DEV_ID_UNKNOWN;
        data->dev.family = PHY_FAMILY_UNKNOWN;
    } else {
        data->dev.devid = phy_id;
        data->dev.family = PHY_FAMILY_M25G;
    }
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MCU_IO_MNGT_MISC_DEVICE_SILICON_REVISION_REG, &id);
    data->dev.rev = (uint16_t)((id) & 0xFF);

    /* SW Work-arround for A0-silicon */
    if (data->dev.rev == LAN80XX_REV_A0) {
        data->dev.devid = LAN80XX_DEV_ID_8044;
        data->dev.family = PHY_FAMILY_M25G;
    }
    T_I(MEPA_TRACE_GRP_GEN, "model 0x%x rev %d\n", data->dev.devid, data->dev.rev);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_sku_port_cnt(mepa_device_t *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;

    switch (data->dev.devid) {
    case LAN80XX_DEV_ID_8024:
    case LAN80XX_DEV_ID_8022:
    case LAN80XX_DEV_ID_8023:
    case LAN80XX_DEV_ID_8264:
        base_data->max_port_cnt = 2;
        break;
    default:
        base_data->max_port_cnt = 4;
        break;
    }
    return rc;
}

static mepa_rc lan80xx_feature_supported(mepa_device_t  *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;
    u32 val = 0U;

    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_MCU_IO_MNGT_MISC_DEVICE_FEATURE_DISABLE_REG, &val);

    base_data->features.macsec_disable    = (val & LAN80XX_MACSEC_DISABLE);
    base_data->features.ptp_1588_disable  = (val & LAN80XX_1588_DISABLE);
    base_data->features.speed_25g_disable = (val & LAN80XX_25G_DISABLE);
    base_data->features.quad_disable      = (val & LAN80XX_QUAD_DISABLE);
    base_data->features.cleartags_disable = (val & LAN80XX_CLEARTAGS_DISABLE);
    base_data->features.mpls_disable      = (val & LAN80XX_MPLS_DISABLE);

    return rc;
}

/* Sw-Workarround
 * For A0 and A1 silicon revision, default Bootrom code fails so SERDES_INIT strap should be always set to High
 * This function "lan80xx_a0_a1_revision_serd_init_strap_wrkrd" ensures that SERDES INIT strap is high, if it is tied low
 * due to any of board design issues the SERDES INIT strap is configured to high by STRAP OVERRIDE register configuration.
 */
static mepa_rc lan80xx_a0_a1_revision_serd_init_strap_wrkrd(mepa_device_t *dev, mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0;
    if ((data->dev.rev != LAN80XX_REV_A0) && (data->dev.rev != LAN80XX_REV_A1)) {
        return MEPA_RC_OK;
    }
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_READ_REG), &val);

    if (!(val & SERDES_INIT_STRAP)) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &val);
        val |= SERDES_INIT_STRAP;
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), val);
        T_IM(data->port_no,"Forcing Serdes Init strap to high for A0 and A1 silicon revison\n");
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_get_base_adr(const mepa_device_t *dev,
                                    const mepa_port_no_t port_no,
                                    uint32_t mmd_dev,
                                    uint32_t addr,
                                    uint32_t *phy_base,
                                    uint32_t *target_id,
                                    uint32_t *offset,
                                    mepa_bool_t *use_base_port)
{
    *target_id = 0;
    *phy_base = addr;
    *use_base_port = TRUE;
    switch (mmd_dev) {
    case 1:
        if ((addr <= LAN80XX_LINE_PMA_PMA_STD_END_ADDR) ||
            (addr >= LAN80XX_LINE_PMA_PMA_VENDOR_START_ADDR && addr <= LAN80XX_LINE_PMA_PMA_VENDOR_END_ADDR) ) {

            *target_id = LAN80XX_TARGET_ID_LINE_PMA;
        } else if ( (addr >= LAN80XX_LINE_KR_KR_STD_START_ADDR && addr <= LAN80XX_LINE_KR_KR_STD_END_ADDR ) ||
                    (addr >= LAN80XX_LINE_KR_KR_VENDOR_START_ADDR && addr <= LAN80XX_LINE_KR_KR_VENDOR_END_ADDR ) ) {

            *target_id = LAN80XX_TARGET_ID_LINE_KR;
        } else if ( (addr >= LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_START_ADDR && addr <= LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_END_ADDR ) ||
                    (addr >= LAN80XX_LINE_PCS_CFG_FEC_VENDOR_START_ADDR && addr <= LAN80XX_LINE_PCS_CFG_FEC_VENDOR_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_PCS_CFG;
        } else if ((addr >= LAN80XX_LINE_RS_FEC_RS_FEC_STD_START_ADDR && addr <= LAN80XX_LINE_RS_FEC_RS_FEC_STD_END_ADDR ) ||
                   (addr >= LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_START_ADDR && addr <= LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_END_ADDR)) {

            *target_id = LAN80XX_TARGET_ID_LINE_RS_FEC;
        } else if ((addr >= LAN80XX_LINE_SLICE_START_ADDR && addr <= LAN80XX_LINE_SLICE_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_SLICE;
        } else if ((addr >= LAN80XX_SFP_TWS_START_ADDR && addr <= LAN80XX_SFP_TWS_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_SFP_TWS;
        } else if ((addr >= LAN80XX_LINE_INTR_CTRL_START_ADDR && addr <= LAN80XX_LINE_INTR_CTRL_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_INTR_CTRL;
        } else if ((addr >= LAN80XX_LINE_PMA_8BIT_START_ADDR && addr <= LAN80XX_LINE_PMA_8BIT_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_PMA_8BIT;
        }
        break;
    case 3:
        if ((addr <= LAN80XX_LINE_PCS25G_PCS_STD_END_ADDR ) ||
            ((addr >= LAN80XX_LINE_PCS25G_PCS_VENDOR_START_ADDR) && (addr <= LAN80XX_LINE_PCS25G_PCS_VENDOR_END_ADDR) )) {

            *target_id = LAN80XX_TARGET_ID_LINE_PCS25G;
        } else if ((addr >= LAN80XX_LINE_PCS_CFG_START_ADDR && addr <= LAN80XX_LINE_PCS_CFG_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_PCS_CFG;
        } else if ((addr >= LAN80XX_MAC_FC_BUFFER_START_ADDR && addr <= LAN80XX_MAC_FC_BUFFER_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_MAC_FC_BUFFER;
            *phy_base = LAN80XX_MAC_FC_BUFFER_START_ADDR;
        } else if ((addr >= LAN80XX_HOST_MAC_START_ADDR && addr <= LAN80XX_HOST_MAC_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_HOST_MAC;
            *phy_base = LAN80XX_HOST_MAC_START_ADDR;
        } else if ((addr >= LAN80XX_LINE_MAC_START_ADDR && addr <= LAN80XX_LINE_MAC_END_ADDR )) {

            *target_id = LAN80XX_TARGET_ID_LINE_MAC;
            *phy_base = LAN80XX_LINE_MAC_START_ADDR;
        }
        break;
    case 7:
        *target_id = LAN80XX_TARGET_ID_LINE_KR;
        break;
    case 8:
        if (addr >= LAN80XX_MACSEC_START_ADDR && addr <= LAN80XX_MACSEC_END_ADDR) {
            *target_id = LAN80XX_TARGET_ID_MACSEC_INGR;
            *phy_base = LAN80XX_MACSEC_CORE_START_ADDR;

        } else if ((addr <= LAN80XX_MACSEC_CORE_INTR_END_ADDR ) ||
                   (addr >= LAN80XX_MACSEC_CORE_INTR_START_ADDR && addr <= LAN80XX_MACSEC_CORE_END_ADDR)) {

            *target_id = LAN80XX_TARGET_ID_MACSEC_INGR_CORE;
            *phy_base = LAN80XX_MACSEC_CORE_START_ADDR;
        }
        break;
    case 9:
        if (addr >= LAN80XX_HOST_PMA_START_ADDR && addr <= LAN80XX_HOST_PMA_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_HOST_PMA;

        } else if ((addr >= LAN80XX_HOST_KR_KR_STD_START_ADDR && addr <= LAN80XX_HOST_KR_KR_STD_END_ADDR ) ||
                   (addr >= LAN80XX_HOST_KR_KR_VENDOR_START_ADDR && addr <= LAN80XX_HOST_KR_KR_VENDOR_END_ADDR )) {
            *target_id = LAN80XX_TARGET_ID_HOST_KR;

        } else if ((addr >= LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_START_ADDR && addr <= LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_END_ADDR ) ||
                   (addr >= LAN80XX_HOST_PCS_CFG_FEC_VENDOR_START_ADDR && addr <= LAN80XX_HOST_PCS_CFG_FEC_VENDOR_END_ADDR )) {
            *target_id = LAN80XX_TARGET_ID_HOST_PCS_CFG;

        } else if ((addr >= LAN80XX_HOST_RS_FEC_RS_FEC_STD_START_ADDR && addr <= LAN80XX_HOST_RS_FEC_RS_FEC_STD_END_ADDR ) ||
                   (addr >= LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_START_ADDR && addr <= LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_END_ADDR )) {
            *target_id = LAN80XX_TARGET_ID_HOST_RS_FEC;

        } else if (addr >= LAN80XX_HOST_SLICE_START_ADDR && addr <= LAN80XX_HOST_SLICE_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_HOST_SLICE;

        } else if (addr >= LAN80XX_HOST_INTR_CTRL_START_ADDR && addr <= LAN80XX_HOST_INTR_CTRL_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_HOST_INTR_CTRL;

        } else if (addr >= LAN80XX_PKT_BIST_START_ADDR && addr <= LAN80XX_PKT_BIST_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PKT_BIST;

        } else if (addr >= LAN80XX_HOST_PMA_8BIT_START_ADDR && addr <= LAN80XX_HOST_PMA_8BIT_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_HOST_PMA_8BIT;
        }
        break;
    case 0xa:
        if (addr >= LAN80XX_PTP_PROC_START_ADDR && addr <= LAN80XX_PTP_PROC_END_ADDR) {
            *target_id = LAN80XX_TARGET_ID_PTP_PROC;
            *phy_base = LAN80XX_PTP_PROC_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA0_INGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA0_INGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA0_INGR_CFG;
            *phy_base = LAN80XX_PTP_ANA0_INGR_CFG_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA0_EGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA0_EGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA0_EGR_CFG;
            *phy_base = LAN80XX_PTP_ANA0_EGR_CFG_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA1_INGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA1_INGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA1_INGR_CFG;
            *phy_base = LAN80XX_PTP_ANA1_INGR_CFG_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA1_EGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA1_EGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA1_EGR_CFG;
            *phy_base = LAN80XX_PTP_ANA1_EGR_CFG_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA2_INGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA2_INGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA2_INGR_CFG;
            *phy_base = LAN80XX_PTP_ANA2_INGR_CFG_START_ADDR;

        } else if (addr >= LAN80XX_PTP_ANA2_EGR_CFG_START_ADDR && addr <= LAN80XX_PTP_ANA2_EGR_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_ANA2_EGR_CFG;
            *phy_base = LAN80XX_PTP_ANA2_EGR_CFG_START_ADDR;
        }
        break;
    case 0xb:
        if (addr <= LAN80XX_HOST_PCS25G_PCS_VENDOR_END_ADDR) {
            *target_id = LAN80XX_TARGET_ID_HOST_PCS25G;

        } else if (addr >= LAN80XX_HOST_PCS_CFG_START_ADDR && addr <= LAN80XX_HOST_PCS_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_HOST_PCS_CFG;
        }
        break;
    case 0xf:
        *target_id = LAN80XX_TARGET_ID_HOST_KR;
        break;
    case 0x1f:
        if ((addr >= LAN80XX_MACSEC_START_ADDR && addr <= LAN80XX_MACSEC_END_ADDR)) {
            *target_id = LAN80XX_TARGET_ID_MACSEC_EGR;
            *phy_base = LAN80XX_MACSEC_CORE_START_ADDR;

        } else if ((addr <= LAN80XX_MACSEC_CORE_INTR_END_ADDR ) ||
                   (addr >= LAN80XX_MACSEC_CORE_INTR_START_ADDR && addr <= LAN80XX_MACSEC_CORE_END_ADDR)) {
            *target_id = LAN80XX_TARGET_ID_MACSEC_EGR_CORE;
            *phy_base = LAN80XX_MACSEC_CORE_START_ADDR;
        }
        break;
    case 0x1e:
        if (addr <= LAN80XX_MCU_IO_MNGT_MISC_END_ADDR) {
            *target_id = LAN80XX_TARGET_ID_MCU_IO_MNGT_MISC;

        } else if (addr >= LAN80XX_GLOBAL_START_ADDR && addr <= LAN80XX_GLOBAL_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_GLOBAL;

        } else if (addr >= LAN80XX_CLK_CFG_START_ADDR && addr <= LAN80XX_CLK_CFG_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_CLK_CFG;

        } else if (addr >= LAN80XX_PTP_LTC_START_ADDR && addr <= LAN80XX_PTP_LTC_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_LTC;
            *phy_base = LAN80XX_PTP_LTC_START_ADDR;

        } else if (addr >= LAN80XX_PTP_STI_START_ADDR && addr <= LAN80XX_PTP_STI_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_PTP_STI;
            *phy_base = LAN80XX_PTP_STI_START_ADDR;

        } else if (addr >= LAN80XX_CROSS_CONNECT_START_ADDR && addr <= LAN80XX_CROSS_CONNECT_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_CROSS_CONNECT;
            *phy_base = LAN80XX_CROSS_CONNECT_START_ADDR;

        } else if (addr >= LAN80XX_GPIO_CTRL_START_ADDR && addr <= LAN80XX_GPIO_CTRL_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_GPIO_CTRL;
            *phy_base = LAN80XX_GPIO_CTRL_START_ADDR;
        } else if (addr >= LAN80XX_MCU_MAILBOX_START_ADDR && addr <= LAN80XX_MCU_MAILBOX_END_ADDR ) {
            *target_id = LAN80XX_TARGET_ID_MCU_MAILBOX;
            *phy_base = LAN80XX_MCU_MAILBOX_START_ADDR;
        }
        break;
    default:
        return MEPA_RC_ERROR;
    }

    *offset = addr - *phy_base;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_xconnect_conf_get_priv(mepa_device_t  *dev, mepa_port_no_t port_no, phy25g_xconnect_get_conf_t  *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    /* Select switch WPS0 or WPS 1 */
    u8 switch_sel = (data->channel_id < 2) ? 0 : 1;
    uint32_t value = 0;
    uint8_t port = 0;

    LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_CROSS_CONNECT_CFG1, &value);
    conf->failover_conf.enable = !(LAN80XX_X_CROSS_CONNECT_CFG1_BYPASS(value));

    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG), &value);
    conf->failover_conf.active_host = switch_sel ? !(LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL(value)) : LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL(value);
    conf->failover_conf.role = LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_TEST_ROLE(value);
    conf->failover_conf.is_mac_change = LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_MAC_CHANGE(value);
    conf->failover_conf.reversion = data->reversion;
    conf->failover_conf.mode = data->mode;
    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAULT_COND : LAN80XX_CROSS_CONNECT_WPS0_FAULT_COND), &value);
    conf->failover_conf.filter_ena = LAN80XX_X_CROSS_CONNECT_WPS0_FAULT_COND_FILTER_EN(value);
    if (conf->failover_conf.active_host == LAN80XX_WPS_0_1_DEFAULT_ACTIVE_H0_H3) {

        conf->failover_conf.src_event = switch_sel ? LAN80XX_X_CROSS_CONNECT_WPS1_FAULT_COND_H3_FAULT_COND_SRC(value) :
                                        LAN80XX_X_CROSS_CONNECT_WPS0_FAULT_COND_H0_FAULT_COND_SRC(value);
    } else {
        conf->failover_conf.src_event = switch_sel ? LAN80XX_X_CROSS_CONNECT_WPS1_FAULT_COND_H2_FAULT_COND_SRC(value) : LAN80XX_X_CROSS_CONNECT_WPS0_FAULT_COND_H1_FAULT_COND_SRC(value);
    }
    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL), &value);
    conf->failover_conf.ack_timer = LAN80XX_X_CROSS_CONNECT_WPS1_FAILOVER_CTRL_FC_ACK_TIMER(value);
    conf->failover_conf.fc_signal_enable = !(LAN80XX_X_CROSS_CONNECT_WPS1_FAILOVER_CTRL_FC_SIGNAL_DISABLE(value));

    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTA_LSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTA_LSB), &value);

    conf->failover_conf.assert_filter_val = LAN80XX_X_CROSS_CONNECT_WPS0_FILTER_COUNTA_LSB_COUNTA_LSB(value);
    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTA_MSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTA_MSB), &value);
    conf->failover_conf.assert_filter_val |= LAN80XX_X_CROSS_CONNECT_WPS0_FILTER_COUNTA_MSB_COUNTA_MSB(value) << 16;
    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTB_LSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTB_LSB), &value);

    conf->failover_conf.deassert_filter_val = LAN80XX_X_CROSS_CONNECT_WPS0_FILTER_COUNTB_LSB_COUNTB_LSB(value);
    LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTB_MSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTB_MSB), &value);
    conf->failover_conf.deassert_filter_val |= LAN80XX_X_CROSS_CONNECT_WPS0_FILTER_COUNTB_MSB_COUNTB_MSB(value) << 16;

    conf->Lineport_chn = (uint8_t *)malloc(base_data->max_port_cnt * sizeof(uint8_t));
    if (conf->Lineport_chn == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "Memory allocation failed\n");
        return MEPA_RC_ERROR;
    }
    for (port = 0; port < base_data->max_port_cnt; port++) {
        LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_XCONNECT_HOSTx_CFG(port), &value);
        conf->Lineport_chn[port] = LAN80XX_X_CROSS_CONNECT_SRC_SEL_DEFAULT_CH(value);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_xconnect_anylinetoanyhost(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t xconnect_enable, u8 LineDefaultCh[MAX_PORTS])
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    uint8_t port = 0;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    /* Cross connect enable */
    LAN80XX_CSR_WARM_WRM(base_data->port_no, LAN80XX_CROSS_CONNECT_CFG1, xconnect_enable ? 0 : LAN80XX_M_CROSS_CONNECT_CFG1_BYPASS, LAN80XX_M_CROSS_CONNECT_CFG1_BYPASS);

    T_I(MEPA_TRACE_GRP_GEN, "Mapping Hostports 0, 1, 2, and 3 according to the user-specified Lineports\n");
    for (port = 0; port < base_data->max_port_cnt; port++) {
        if (!xconnect_enable) {
            T_D(MEPA_TRACE_GRP_GEN, "Cross connect disabled: Default Host to Line mapping\n");
            LineDefaultCh[port] = port;
        }
        if (LineDefaultCh[port] > base_data->max_port_cnt) {
            T_E(MEPA_TRACE_GRP_GEN, "Maximum port count is %d\n", base_data->max_port_cnt);
        }
        /*Set HOST CFG Registers*/
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_XCONNECT_HOSTx_CFG(port),
                        LAN80XX_F_CROSS_CONNECT_SRC_SEL_DEFAULT_CH(LineDefaultCh[port]),
                        LAN80XX_M_CROSS_CONNECT_SRC_SEL_DEFAULT_CH);
        /*Set LINE CFG Registers*/
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_XCONNECT_LINEx_CFG(LineDefaultCh[port]),
                        LAN80XX_F_CROSS_CONNECT_SRC_SEL_DEFAULT_CH(port),
                        LAN80XX_M_CROSS_CONNECT_SRC_SEL_DEFAULT_CH);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_hostline_channel_configuration(mepa_device_t *dev, mepa_port_no_t port_no,
                                                      u8 switch_sel, mepa_bool_t is_mac_change, phy25g_host_protect_mode_t mode, u8 act_host)
{

    u8 chn, dft_chn, alt_chn = 0;
    u8 channel_id_base = switch_sel * 2;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    for (chn = channel_id_base; chn <= (channel_id_base + 1); chn++) {
        if (is_mac_change) {
            /* With mac change in mac retimer mode for 1:1 host protection */
            dft_chn = alt_chn = act_host ? ((chn == channel_id_base) ? chn + 1 : chn - 1) : chn;
            if (mode == LAN80XX_AUTO_FAILOVER_1_PLUS_1_PROTECTION) {
                /* With mac change in mac retimer mode for 1+1 host protection */
                dft_chn = switch_sel ? (channel_id_base + 1) : channel_id_base;
                alt_chn = act_host ? ((chn == channel_id_base) ? chn + 1 : chn - 1) : chn;
            }
        } else {
            if (mode == LAN80XX_AUTO_FAILOVER_1_ISTO_1_PROTECTION) {
                /* Without mac change for 1:1 host protection */
                dft_chn = act_host ? ((chn == channel_id_base) ? chn + 1 : chn - 1) : chn;
            } else {
                /* Without mac change for 1+1 host protection */
                dft_chn = switch_sel ? (channel_id_base + 1) : channel_id_base;
            }
            alt_chn = act_host ? chn : ((chn == channel_id_base) ? chn + 1 : chn - 1);
        }
        /* Host side - default channel, alternate channel configuration */
        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_HOSTx_CFG(chn),
                        LAN80XX_F_CROSS_CONNECT_H0_SRC_SEL_DEFAULT_CH(dft_chn),
                        LAN80XX_M_CROSS_CONNECT_H0_SRC_SEL_DEFAULT_CH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_HOSTx_CFG(chn),
                        LAN80XX_F_CROSS_CONNECT_H0_SRC_SEL_ALT_CH(alt_chn),
                        LAN80XX_M_CROSS_CONNECT_H0_SRC_SEL_ALT_CH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_HOSTx_CFG(chn),
                        LAN80XX_M_CROSS_CONNECT_H0_SRC_SEL_ALT_EN,
                        LAN80XX_M_CROSS_CONNECT_H0_SRC_SEL_ALT_EN);
        if (!is_mac_change && (((switch_sel == 0) && (chn == 1)) || ((switch_sel == 1) && (chn == 2)))) {
            continue;
        }

        if (mode == LAN80XX_AUTO_FAILOVER_1_PLUS_1_PROTECTION && !is_mac_change) {
            /* Without mac change for 1+1 host protection */
            dft_chn = switch_sel ? (channel_id_base + (!act_host)) : (channel_id_base + act_host);
        }
        /* Line side - default channel, alternate channel configuration */
        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_LINEx_CFG(chn),
                        LAN80XX_F_CROSS_CONNECT_L0_SRC_SEL_DEFAULT_CH(dft_chn),
                        LAN80XX_M_CROSS_CONNECT_L0_SRC_SEL_DEFAULT_CH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_LINEx_CFG(chn),
                        LAN80XX_F_CROSS_CONNECT_L0_SRC_SEL_ALT_CH(alt_chn),
                        LAN80XX_M_CROSS_CONNECT_L0_SRC_SEL_ALT_CH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_XCONNECT_LINEx_CFG(chn),
                        LAN80XX_M_CROSS_CONNECT_L0_SRC_SEL_ALT_EN,
                        LAN80XX_M_CROSS_CONNECT_L0_SRC_SEL_ALT_EN);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_xconnect_hostfailover_Protection(mepa_device_t  *dev, mepa_port_no_t port_no, const phy25g_autofailover_t *conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u8 base_port = base_data->port_no;
    /* Select switch WPS0 or WPS 1 */
    u8 switch_sel = (data->channel_id < 2) ? 0 : 1;

    if (conf->is_mac_change == 1 && data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        T_E(MEPA_TRACE_GRP_GEN, "PHY should be MAC retimer mode for MAC change\n");
        return MEPA_RC_ERROR;
    }
    if (conf->is_mac_change == 1 && conf->role == LAN80XX_WPS_PHY_ROLE) {
        T_E(MEPA_TRACE_GRP_GEN, "MAC change supports only when WPS is in System role\n");
        return MEPA_RC_ERROR;
    }
    if ((conf->role != LAN80XX_WPS_PHY_ROLE) && (conf->role != LAN80XX_WPS_SYSTEM_ROLE)) {
        T_E(MEPA_TRACE_GRP_GEN, "Switch should be configured either as PHY ROLE or SYSTEM ROLE\n");
        return MEPA_RC_ERROR;
    }

    /* Cross connect enable */
    LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_CFG1, conf->enable ? 0 : LAN80XX_M_CROSS_CONNECT_CFG1_BYPASS, LAN80XX_M_CROSS_CONNECT_CFG1_BYPASS);
    /* Switch Configuration */

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                    0, LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM);

    /* WPS switch role */
    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                    LAN80XX_F_CROSS_CONNECT_WPS0_CFG_WPS_TEST_ROLE(conf->role),
                    LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_TEST_ROLE);

    /* WPS MAC change */
    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                    conf->is_mac_change ? LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_MAC_CHANGE : 0,
                    LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_MAC_CHANGE);

    /* Active HOST selection */
    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                    LAN80XX_F_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL(switch_sel ? !conf->active_host : conf->active_host),
                    LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL);

    /* FC Signal Re-arm*/
    if (conf->ack_timer <= MAX_ACK_TIMER) {
        LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                        LAN80XX_F_CROSS_CONNECT_WPS1_FAILOVER_CTRL_FC_ACK_TIMER(conf->ack_timer) |
                        LAN80XX_F_CROSS_CONNECT_WPS0_FAILOVER_CTRL_FC_SIGNAL_DISABLE(!conf->fc_signal_enable),
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_FC_ACK_TIMER | LAN80XX_M_CROSS_CONNECT_WPS0_FAILOVER_CTRL_FC_SIGNAL_DISABLE);
    }
    /* Event Source Configuration */
    if ((conf->active_host == LAN80XX_WPS_0_1_DEFAULT_ACTIVE_H0_H3) && (conf->src_event <= MAX_SOURCE_EVENTS)) {

        LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAULT_COND : LAN80XX_CROSS_CONNECT_WPS0_FAULT_COND,
                        switch_sel ? LAN80XX_F_CROSS_CONNECT_WPS1_FAULT_COND_H3_FAULT_COND_SRC(conf->src_event) :
                        LAN80XX_F_CROSS_CONNECT_WPS0_FAULT_COND_H0_FAULT_COND_SRC(conf->src_event),
                        switch_sel ? LAN80XX_M_CROSS_CONNECT_WPS1_FAULT_COND_H3_FAULT_COND_SRC : LAN80XX_M_CROSS_CONNECT_WPS0_FAULT_COND_H0_FAULT_COND_SRC);

    } else if ((conf->active_host == LAN80XX_WPS_0_1_DEFAULT_ACTIVE_H1_H2) && (conf->src_event <= MAX_SOURCE_EVENTS)) {

        LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAULT_COND : LAN80XX_CROSS_CONNECT_WPS0_FAULT_COND,
                        switch_sel ? LAN80XX_F_CROSS_CONNECT_WPS1_FAULT_COND_H2_FAULT_COND_SRC(conf->src_event) :
                        LAN80XX_F_CROSS_CONNECT_WPS0_FAULT_COND_H1_FAULT_COND_SRC(conf->src_event),
                        switch_sel ? LAN80XX_M_CROSS_CONNECT_WPS1_FAULT_COND_H2_FAULT_COND_SRC : LAN80XX_M_CROSS_CONNECT_WPS0_FAULT_COND_H1_FAULT_COND_SRC);
    }

    /* Filter Enable */
    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAULT_COND : LAN80XX_CROSS_CONNECT_WPS0_FAULT_COND,
                    conf->filter_ena ? LAN80XX_M_CROSS_CONNECT_WPS0_FAULT_COND_FILTER_EN : 0,
                    LAN80XX_M_CROSS_CONNECT_WPS0_FAULT_COND_FILTER_EN);

    /* Host and Line Configuration */
    /* Clock Select */

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                    switch_sel ? LAN80XX_F_CROSS_CONNECT_WPS1_CFG_L3_LOCAL_CLK(!conf->active_host + 2) : LAN80XX_F_CROSS_CONNECT_WPS0_CFG_L0_LOCAL_CLK(conf->active_host),
                    switch_sel ? LAN80XX_M_CROSS_CONNECT_WPS1_CFG_L3_LOCAL_CLK : LAN80XX_M_CROSS_CONNECT_WPS0_CFG_L0_LOCAL_CLK);

    if (conf->is_mac_change) {
        LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                        switch_sel ? LAN80XX_F_CROSS_CONNECT_WPS1_CFG_L2_LOCAL_CLK(conf->active_host + 2) : LAN80XX_F_CROSS_CONNECT_WPS0_CFG_L1_LOCAL_CLK(!conf->active_host),
                        switch_sel ? LAN80XX_M_CROSS_CONNECT_WPS1_CFG_L2_LOCAL_CLK : LAN80XX_M_CROSS_CONNECT_WPS0_CFG_L1_LOCAL_CLK);
    }

    lan80xx_hostline_channel_configuration(dev, base_data->port_no, switch_sel, conf->is_mac_change, conf->mode, conf->active_host);
    /* Copying the conf structure details in data struct in order to use once failover occured */
    data->reversion = conf->reversion;
    data->is_mac_change = conf->is_mac_change;
    data->mode = conf->mode;

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTA_LSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTA_LSB, LAN80XX_F_CROSS_CONNECT_WPS0_FILTER_COUNTA_LSB_COUNTA_LSB(conf->assert_filter_val & 0xFFFF), LAN80XX_M_CROSS_CONNECT_WPS0_FILTER_COUNTA_LSB_COUNTA_LSB);

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTA_MSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTA_MSB, LAN80XX_F_CROSS_CONNECT_WPS0_FILTER_COUNTA_MSB_COUNTA_MSB((conf->assert_filter_val >> 16) & 0xFF), LAN80XX_M_CROSS_CONNECT_WPS0_FILTER_COUNTA_MSB_COUNTA_MSB);

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTB_LSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTB_LSB, LAN80XX_F_CROSS_CONNECT_WPS0_FILTER_COUNTB_LSB_COUNTB_LSB(conf->deassert_filter_val & 0xFFFF), LAN80XX_M_CROSS_CONNECT_WPS0_FILTER_COUNTB_LSB_COUNTB_LSB);

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS0_FILTER_COUNTB_MSB : LAN80XX_CROSS_CONNECT_WPS1_FILTER_COUNTB_MSB, LAN80XX_F_CROSS_CONNECT_WPS0_FILTER_COUNTB_MSB_COUNTB_MSB((conf->deassert_filter_val >> 16) & 0xFF), LAN80XX_M_CROSS_CONNECT_WPS0_FILTER_COUNTB_MSB_COUNTB_MSB);

    LAN80XX_CSR_WRM(base_port, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM);

    return MEPA_RC_OK;
}


static mepa_rc lan80xx_xconnect_failover_set_priv(mepa_device_t  *dev,
                                                  const mepa_port_no_t port_no)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc  rc = MEPA_RC_OK;
    uint32_t value = 0;
    uint8_t hostport_active = 0;
    u8 act_host;
    u8 switch_sel = (data->channel_id < 2) ? 0 : 1;
    if (data->reversion) {
        /* Reversion mode */
        LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL, 0,
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM);
    } else {
        /* Non-Reversion mode */
        LAN80XX_CSR_RD(dev, port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_STATUS : LAN80XX_CROSS_CONNECT_WPS0_STATUS), &value);

        hostport_active = (LAN80XX_X_CROSS_CONNECT_WPS0_STATUS_H0_PROT_STATE_STATUS(value) == 0x1) ? 0 : LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL;

        LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_CFG_MASK,
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_CFG_MASK);

        LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL, 0,
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM);
        /* Choose alternate default select */
        LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG,
                        hostport_active, LAN80XX_M_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL);

        LAN80XX_CSR_RD(dev, base_data->port_no, (switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_CFG : LAN80XX_CROSS_CONNECT_WPS0_CFG ), &value);
        act_host = switch_sel ? !(LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL(value)) : LAN80XX_X_CROSS_CONNECT_WPS0_CFG_WPS_DEFAULT_ACTIVE_SEL(value);
        /* Configuring the alternate and default channel based on active select */
        lan80xx_hostline_channel_configuration(dev, base_data->port_no, switch_sel, data->is_mac_change, data->mode, act_host);

        LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL, 0,
                        LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_CFG_MASK);
    }
    LAN80XX_CSR_WRM(base_data->port_no, switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_ARM);
    return rc;
}

mepa_rc lan80xx_xconnect_failover(mepa_device_t *dev,
                                  const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc  rc = MEPA_RC_OK;

    rc = LAN80XX_RC_COLD(lan80xx_xconnect_failover_set_priv(dev, port_no));
    return rc;
}

mepa_rc lan80xx_xconnect_force_failover(mepa_device_t *dev,
                                        const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc  rc = MEPA_RC_OK;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u8 switch_sel = (data->channel_id < 2) ? 0 : 1;

    LAN80XX_CSR_WRM(base_data->port_no,
                    switch_sel ? LAN80XX_CROSS_CONNECT_WPS1_FAILOVER_CTRL : LAN80XX_CROSS_CONNECT_WPS0_FAILOVER_CTRL,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_FORCE_FAILOVER,
                    LAN80XX_M_CROSS_CONNECT_WPS1_FAILOVER_CTRL_WPS_FORCE_FAILOVER);
    return rc;
}

/*********************************************
 *   Register Read Write Access Funcction
*********************************************/
ioreg_blk *_lan80xx_ioreg(ioreg_blk *io, uint16_t mmd, mepa_bool_t is32, uint32_t off)
{
    io->mmd = mmd;
    io->is32 = is32;
    io->addr = off;
    return io;
}


mepa_rc lan80xx_csr_rd(const mepa_device_t         *dev,
                       const mepa_port_no_t        port_no,
                       const uint32_t              mmd_dev,
                       mepa_bool_t                 is32,
                       const uint32_t              addr,
                       uint32_t                    *const value)
{
    mepa_bool_t  use_base_port = TRUE;
    uint32_t     reg_addr = 0;
    uint16_t     reg_value[2];
    uint32_t     offset, target, base_addr;

    if (dev->callout->spi_read != NULL) {
        MEPA_RC(dev->callout->spi_read(dev->callout_ctx, port_no, (uint8_t)mmd_dev, (uint16_t)addr, value));
        T_N(MEPA_TRACE_GRP_GEN, "SPI Read : Port no : %d ,mmd : 0x%x ,addr : 0x%x, value : 0x%x\n", port_no, mmd_dev, addr, *value);
        return MEPA_RC_OK;
    }
    if (dev->callout->mmd_read != NULL && dev->callout->mmd_read_inc != NULL) {
        mepa_mmd_read_t     mmd_read_func = dev->callout->mmd_read;
        mepa_mmd_read_inc_t mmd_read_inc_func = dev->callout->mmd_read_inc;
        if (is32) {
            MEPA_RC(lan80xx_get_base_adr(dev, port_no, mmd_dev, addr, &base_addr, &target, &offset, &use_base_port));
            reg_addr = base_addr | (offset << 1);

            MEPA_RC(mmd_read_inc_func(dev->callout_ctx, mmd_dev, reg_addr, reg_value, 2));
            *value = reg_value[0] + (((uint32_t)reg_value[1]) << LAN80XX_16_BIT_SHIFT);

            T_N(MEPA_TRACE_GRP_GEN, "MDIO Read 32-bit register : Port no : %d ,mmd : 0x%x ,register_addr : 0x%x, 32-bit_reg_addr ; 0x%x, reg_value : 0x%x\n", port_no, mmd_dev, addr, reg_addr, *value);
            return MEPA_RC_OK;
        } else {
            MEPA_RC(mmd_read_func(dev->callout_ctx, mmd_dev, addr, &reg_value[0]));
            *value = (u32)reg_value[0];
            T_N(MEPA_TRACE_GRP_GEN, "MDIO Read 16-bit register : Port no : %d ,mmd : 0x%x ,register_addr : 0x%x, reg_value : 0x%x\n", port_no, mmd_dev, addr, *value);
            return MEPA_RC_OK;
        }
    }
    T_E(MEPA_TRACE_GRP_GEN, "\n SPI and MMD Read Callouts are not assigned on port : %d\n", port_no);
    return MEPA_RC_ERROR;
}

//Function to read two consecutive 32 bit registers and return 64 bit value.
mepa_rc lan80xx_csr_rd_64(const mepa_device_t         *dev,
                          const mepa_port_no_t        port_no,
                          const uint32_t              mmd_dev,
                          mepa_bool_t                 is32,
                          const uint32_t              addr,
                          uint64_t                    *const value)
{
    mepa_bool_t  use_base_port = TRUE;
    uint32_t     reg_addr = 0;
    uint16_t     reg_value[4];
    uint32_t     offset, target, base_addr;
    u32          value_low, value_hi;

    if (!is32) {
        T_D(MEPA_TRACE_GRP_GEN, "Only 32bit registers can be accessed");
        return MEPA_RC_ERROR;
    }

    if (dev->callout->spi_read_64bit != NULL) {
        MEPA_RC(dev->callout->spi_read_64bit(dev->callout_ctx, port_no, (uint8_t)mmd_dev, (uint16_t)addr, value));
        T_N(MEPA_TRACE_GRP_GEN, "SPI Read 64-bit : Port no : %d ,mmd : 0x%x ,addr : 0x%x, value : 0x%x\n", port_no, mmd_dev, addr, *value);
        return MEPA_RC_OK;
    }
    if (dev->callout->spi_read != NULL) {
        MEPA_RC(dev->callout->spi_read(dev->callout_ctx, port_no, (uint8_t)mmd_dev, (uint16_t)addr, &value_low));
        MEPA_RC(dev->callout->spi_read(dev->callout_ctx, port_no, (uint8_t)mmd_dev, (uint16_t)(addr + 1), &value_hi));
        *value = value_hi;
        *value = (*value << LAN80XX_32_BIT_SHIFT) + value_low;
        return MEPA_RC_OK;
    }
    if (dev->callout->mmd_read_inc != NULL) {
        mepa_mmd_read_inc_t mmd_read_inc_func = dev->callout->mmd_read_inc;
        MEPA_RC(lan80xx_get_base_adr(dev, port_no, mmd_dev, addr, &base_addr, &target, &offset, &use_base_port));
        reg_addr = base_addr | (offset << 1);
        MEPA_RC(mmd_read_inc_func(dev->callout_ctx, mmd_dev, reg_addr, reg_value, 4));
        value_low = reg_value[0] + (((u32)reg_value[1]) << LAN80XX_16_BIT_SHIFT);
        value_hi = reg_value[2] + (((u32)reg_value[3]) << LAN80XX_16_BIT_SHIFT);
        *value = value_hi;
        *value = (*value << LAN80XX_32_BIT_SHIFT) + value_low;

        T_N(MEPA_TRACE_GRP_GEN, "MDIO Read two 32-bit register : Port no : %d ,mmd : 0x%x ,register_addr : 0x%x, 32-bit_reg_addr ; 0x%x, reg_value : 0x%x\n",
            port_no, mmd_dev, addr, reg_addr, *value);
        return MEPA_RC_OK;
    }
    T_E(MEPA_TRACE_GRP_GEN, "\n SPI and MMD Read Callouts are not assigned on port : %d\n", port_no);
    return MEPA_RC_ERROR;
}


mepa_rc lan80xx_csr_wr(const mepa_device_t         *dev,
                       const mepa_port_no_t        port_no,
                       const uint32_t              mmd_dev,
                       mepa_bool_t                 is32,
                       const uint32_t              addr,
                       uint32_t                    value)
{
    mepa_bool_t  use_base_port = TRUE;
    uint32_t     reg_addr = 0;
    uint32_t     offset, target, base_addr;
    uint16_t     reg_value_upper, reg_value_lower;

    if (dev->callout->spi_write != NULL) {
        MEPA_RC(dev->callout->spi_write(dev->callout_ctx, port_no, (uint8_t)mmd_dev, (uint16_t)addr, &value));
        T_N(MEPA_TRACE_GRP_GEN, "SPI Write: Port no : %d ,mmd : 0x%x ,addr : 0x%x, value : 0x%x\n", port_no, mmd_dev, addr, value);
        return MEPA_RC_OK;
    }

    /* MMD */
    /* Divide the 32 bit value to [15..0] Bits & [31..16] Bits */
    reg_value_lower = (value & 0xffff);
    reg_value_upper = (value >> LAN80XX_16_BIT_SHIFT);
    if (dev->callout->mmd_write) {
        mepa_mmd_write_t    mmd_write_func = dev->callout->mmd_write;
        if (is32) {
            MEPA_RC(lan80xx_get_base_adr(dev, port_no, mmd_dev, addr, &base_addr, &target, &offset, &use_base_port));
            reg_addr = base_addr | (offset << 1);
            /* Write the Upper 2 Bytes */
            MEPA_RC(mmd_write_func(dev->callout_ctx, mmd_dev, (reg_addr | 1), reg_value_upper));
            /* Write the Lower 2 Bytes */
            MEPA_RC(mmd_write_func(dev->callout_ctx, mmd_dev, reg_addr, reg_value_lower));

            T_N(MEPA_TRACE_GRP_GEN, "MDIO write 32-bit register : Port no : %d ,mmd : 0x%x ,register_addr : 0x%x, 32-bit_reg_addr ; 0x%x, reg_value : 0x%x\n", port_no,             mmd_dev, addr, reg_addr, value);
            return MEPA_RC_OK;
        } else {
            MEPA_RC(mmd_write_func(dev->callout_ctx, mmd_dev, addr, reg_value_lower));
            T_N(MEPA_TRACE_GRP_GEN, "MDIO write 16-bit register : Port no : %d ,mmd : 0x%x ,register_addr : 0x%x, reg_value : 0x%x\n",
                port_no, mmd_dev, addr, reg_value_lower);
            return MEPA_RC_OK;
        }
    }
    T_E(MEPA_TRACE_GRP_GEN, "\n SPI and MMD Read Callouts are not assigned on port : %d\n", port_no);
    return MEPA_RC_ERROR;
}


static mepa_rc lan80xx_csr_wrm(const mepa_device_t     *dev,
                               const mepa_port_no_t    port_no,
                               const uint16_t          mmd,
                               const mepa_bool_t       is32,
                               const uint32_t          addr,
                               uint32_t                value,
                               uint32_t                mask)
{
    mepa_rc rc;
    uint32_t     val;

    if ((rc = lan80xx_csr_rd(dev, port_no, mmd, is32, addr, &val)) == MESA_RC_OK) {
        val = ((val & ~mask) | (value & mask));
        rc = lan80xx_csr_wr(dev, port_no, mmd, is32, addr, val);
    }
    return rc;
}

mepa_rc _lan80xx_csr_wrm(const mepa_device_t          *dev,
                         const mepa_port_no_t        port_no,
                         ioreg_blk                   *io_reg,
                         uint32_t                    const value,
                         uint32_t                    mask)
{
    return lan80xx_csr_wrm(dev, port_no, io_reg->mmd, io_reg->is32, io_reg->addr, value, mask);

}

mepa_rc _lan80xx_csr_rd_64(const mepa_device_t *dev,
                           const mepa_port_no_t port_no,
                           ioreg_blk            *reg,
                           u64                  *value)
{
    return lan80xx_csr_rd_64(dev, port_no, reg->mmd, reg->is32, reg->addr, value);
}

mepa_rc _lan80xx_csr_warm_wrm(const mepa_device_t *dev,
                              const mepa_port_no_t port_no,
                              ioreg_blk *io,
                              uint32_t value,
                              uint32_t mask,
                              uint32_t chk_mask,
                              const char *function,
                              const uint16_t line)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    uint32_t  curr_val;
    if (data->sync_calling_private) {
        /* Read the current register value and compare with requested */
        MEPA_RC(lan80xx_csr_rd(dev, port_no, io->mmd, io->is32, io->addr, &curr_val));
        if ((curr_val ^ value) & mask & chk_mask) { /* Change in bit field */
            T_N(MEPA_TRACE_GRP_GEN, "Warm start synch. field changed: Port:%u MMD:%d Register:0x%X\n", port_no, io->mmd, io->addr);
            T_N(MEPA_TRACE_GRP_GEN, "Mask:0x%X Chip value:0x%X API value:0x%X\n", mask, curr_val, value);
            T_N(MEPA_TRACE_GRP_GEN, "Function:%s, Line:%d (chk_mask:0x%X)\n", function, line, chk_mask);
            //data->warm_start_reg_changed = TRUE; // Signaling that a register for this port has changed.
            MEPA_RC(lan80xx_csr_wrm(dev, port_no, io->mmd, io->is32, io->addr, value, mask));
        }
    } else {
        /* Normal write */
        MEPA_RC(lan80xx_csr_wrm(dev, port_no, io->mmd, io->is32, io->addr, value, mask));
    }
    return MEPA_RC_OK;
}

mepa_rc _lan80xx_csr_warm_wr(const mepa_device_t *dev,
                             const mepa_port_no_t port_no,
                             ioreg_blk *io,
                             uint32_t value,
                             const char *function,
                             const uint16_t line)
{
    return _lan80xx_csr_warm_wrm(dev, port_no, io, value, 0xFFFFFFFF, 0xFFFFFFFF, function, line);
}

/*********************************************
 *   Function definitions starts
*********************************************/

static mepa_rc lan80xx_aneg_status(const mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_oper_speed_mode_t speed = SPEED_NONE;
    u32 val = 0, status = 0;
    u32 prl_detect = 0, an_complete = 0, an_rem_fault = 0;
    for (u8 is_line = 0; is_line < 2; is_line++) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, KR_BP_ETH_STS), &val);

        if ((val & LAN80XX_M_HOST_KR_BP_ETH_STS_AN_NEG_25G_KR) || (val & LAN80XX_M_HOST_KR_BP_ETH_STS_AN_NEG_25G_KR_S)) {
            speed = SPEED_25G;
        } else if ((val & LAN80XX_M_HOST_KR_BP_ETH_STS_AN_NEG_10G_KR)) {
            speed = SPEED_10G;
        } else if ((val & LAN80XX_M_HOST_KR_BP_ETH_STS_AN_NEG_1G_KX)) {
            speed = SPEED_1G;
        } else {
            speed = SPEED_NONE;
        }
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, KR_AN_STS0), &status);
        prl_detect = LAN80XX_X_HOST_KR_AN_STS0_PARDETFLT(status);
        an_complete = LAN80XX_X_HOST_KR_AN_STS0_AN_COMPLETE(status);
        an_rem_fault = LAN80XX_X_HOST_KR_AN_STS0_REM_FLT(status);

        if (is_line) {
            data->line_aneg_status.neg_speed = speed;
            data->line_aneg_status.prl_detect = prl_detect;
            data->line_aneg_status.an_complete = an_complete;
            data->line_aneg_status.an_rem_fault = an_rem_fault;
        } else {
            data->host_aneg_status.neg_speed = speed;
            data->host_aneg_status.prl_detect = prl_detect;
            data->host_aneg_status.an_complete = an_complete;
            data->host_aneg_status.an_rem_fault = an_rem_fault;
        }
    }
    return MEPA_RC_OK;
}



mepa_rc lan80xx_pmac_config(const mepa_device_t *dev, mepa_port_no_t port_no, const mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0;
    val = enable ? (LAN80XX_M_LINE_MAC_LINE_MAC_ENABLE_CONFIG_MM_RX_ENA | LAN80XX_M_LINE_MAC_LINE_MAC_ENABLE_CONFIG_MM_TX_ENA) : 0;
    /* Frame Preemption Config */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_ENABLE_CONFIG, val);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG, val);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG, 0x0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG, 0x0);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_ptp_block_preempt_conf(mepa_device_t *dev, mepa_port_no_t port_no, const mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    /* Enable or Disable Frame Preemption in 1588 Block */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE, enable ? LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION : 0,
                    LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION);

    LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE, enable ? LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION : 0,
                    LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_PREEMPTION);

    return MEPA_RC_OK;
}

/* 'enable' is used for Mac enable or disable */
mepa_rc lan80xx_phy_mac_conf_set(const mepa_device_t  *dev, mepa_port_no_t port_no, mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    if (!enable) {
        T_I(MEPA_TRACE_GRP_GEN, "Disabling the MAC Block on port : %d\n", port_no);
        // Disable TX
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG,
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_CLK_ENA);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG,
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA);

        // Assert Resets
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG,
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                       LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG,
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                       LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PTP_PROC_MODE_CTL, LAN80XX_F_PTP_PROC_MODE_CTL_PROTOCOL_MODE(0));
        return MEPA_RC_OK;
    }
    T_I(MEPA_TRACE_GRP_GEN, "Enabling the MAC Block on port : %d\n", port_no);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_PTP_PROC_MODE_CTL, LAN80XX_F_PTP_PROC_MODE_CTL_PROTOCOL_MODE(4));

    /* Tx and Rx threshold values are configured based on the speed selected by user, the values are provided by validation team UNG_MALIBU_25G-2547 */
    u8 rx_read_thresh = 0, tx_read_thresh = 0;
    switch (data->port_state.speed) {
    case SPEED_1G:
        tx_read_thresh = 0x4;
        rx_read_thresh = 0x5;
        break;
    case SPEED_10G:
        tx_read_thresh = 0x6;
        rx_read_thresh = 0x6;
        break;
    case SPEED_25G:
        tx_read_thresh = data->conf.conf_25g.rs_fec_25g ? 0x10 : 0x6;
        rx_read_thresh = 0x10;
        break;
    default:
        tx_read_thresh = 0x10;
        rx_read_thresh = 0x10;
        break;
    }
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG,
                   (LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG,
                   (LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG,
                   (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG,
                   (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG,
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);


    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_DROP_BEHAVIOUR,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_DROP_BEHAVIOUR);

    /* PPM_RATE_ADAPT_THRESH is configured with (READ_THRESH + 2) */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG,
                    LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH(tx_read_thresh + 2) |
                    LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH(rx_read_thresh + 2),
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH);


    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG,
                    (LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_TX_READ_THRESH(tx_read_thresh) |
                     LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_RX_READ_THRESH(rx_read_thresh)),
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_TX_READ_THRESH |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_RX_READ_THRESH);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_RX_PPM_RATE_ADAPT_ENA |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_PPM_RATE_ADAPT_ENA,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_RX_PPM_RATE_ADAPT_ENA |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_PPM_RATE_ADAPT_ENA);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_CTRL_QUEUE_ENA,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_CTRL_QUEUE_ENA);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADDRESS_LSB, LAN80XX_LINE_MAC_ADDRESS_LSB);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADDRESS_MSB, LAN80XX_LINE_MAC_ADDRESS_MSB);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG,
                   (LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_SFD_CHK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_PRM_CHK_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_OOR_ERR_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG_INR_ERR_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_LFS_CFG, 0x0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_MAXLEN_CFG,
                   LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(1) |
                   LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN(LAN80XX_MAC_MAXLEN));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_NUM_TAGS_CFG,
                   LAN80XX_F_LINE_MAC_LINE_MAC_MAC_NUM_TAGS_CFG_NUM_TAGS(4));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG,
                   (LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_STRIP_FCS_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_INSERT_FCS_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_LPI_RELAY_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_LF_RELAY_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG_RF_RELAY_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(0), LAN80XX_LINE_MAC_TAGS_CFG_0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(1), LAN80XX_LINE_MAC_TAGS_CFG_1);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(2), LAN80XX_LINE_MAC_TAGS_CFG_2);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL,
                    LAN80XX_F_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(0xffff) |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA |
                    LAN80XX_F_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(2),
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_USE_PAUSE_STALL_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_2,
                    LAN80XX_F_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(0xf),
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB, LAN80XX_HOST_MAC_ADDRESS_LSB);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB, LAN80XX_HOST_MAC_ADDRESS_MSB);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG,
                   (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_EOP_CHK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_EXT_SOP_CHK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_SFD_CHK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_PRM_CHK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_OOR_ERR_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG_INR_ERR_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG,
                   (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_CLK_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_ENA));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG, 0x00);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG,
                   LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK(1) |
                   LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN(LAN80XX_MAC_MAXLEN));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG,
                   LAN80XX_F_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG_NUM_TAGS(4));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG,
                   (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_FCS_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_FCS_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_STRIP_PREAMBLE_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_INSERT_PREAMBLE_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LPI_RELAY_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_LF_RELAY_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_RF_RELAY_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG_ENABLE_TX_PADDING));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(0), LAN80XX_HOST_MAC_TAGS_CFG_0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(1), LAN80XX_HOST_MAC_TAGS_CFG_1);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(2), LAN80XX_HOST_MAC_TAGS_CFG_2);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL,
                    LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE(0xffff) |
                    LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE(2),
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_VALUE |
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_REPL_MODE |
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_MAC_TX_PAUSE_MODE);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2,
                    LAN80XX_F_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL(0xf),
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2_MAC_TX_PAUSE_INTERVAL);

    /* JIRA "UNG_MALIBU_25G-2457" Fix */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG,
                    LAN80XX_F_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL(64) |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_MODE_CFG,
                    LAN80XX_F_LINE_MAC_LINE_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL(64) |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_MODE_CFG_DISABLE_DIC,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_MODE_CFG_FORCE_CW_UPDATE_INTERVAL |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_MODE_CFG_UNDERSIZED_FRAME_DROP_DIS |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MODE_CFG_DISABLE_DIC);

    MEPA_RC(lan80xx_pmac_config(dev, port_no, data->frame_preempt_ena));

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_serdes_data_get(mepa_device_t *dev, phy25g_serdes_data_t *const data, phy_media_t media)
{
    phy25g_phy_state_t *phy_data = (phy25g_phy_state_t *)dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Serdes Tx and Rx Equalization values for port %d\n", phy_data->port_no);
    switch (media) {
    case MEPA_MEDIA_TYPE_SR:
    case MEPA_MEDIA_TYPE_LR:
    case MEPA_MEDIA_TYPE_ER:
    case MEPA_MEDIA_TYPE_1000BASE_T:
        data->ln_cfg_en_adv = 1;
        data->ln_cfg_en_main = 1;
        data->ln_cfg_en_dly = 1;
        data->ln_cfg_tap_adv_3_0 = 0;
        data->ln_cfg_tap_main = 1;
        data->ln_cfg_tap_dly_4_0 = 0x14;
        data->pcs_en_adv = 1;
        data->pcs_en_main = 1;
        data->pcs_en_dly = 1;
        data->cfg_tap_adv_3_0 = 0;
        data->cfg_tap_main = 1;
        data->cfg_tap_dly_4_0 = 0x14;
        data->cfg_vga_ctrl_bypass_4_0 = 0x8;
        data->cfg_eqR_force = 4;
        data->cfg_eqC_force_3_0 = 0xf;
        data->ln_cfg_alos_thr_2_0 = 0;
        data->dfe_enable = 0;
        break;
    case MEPA_MEDIA_TYPE_DAC:
        data->ln_cfg_en_adv = 0;
        data->ln_cfg_en_main = 1;
        data->ln_cfg_en_dly = 1;
        data->ln_cfg_tap_adv_3_0 = 0;
        data->ln_cfg_tap_main = 1;
        data->ln_cfg_tap_dly_4_0 = 0xd;
        data->pcs_en_adv = 0;
        data->pcs_en_main = 1;
        data->pcs_en_dly = 0;
        data->cfg_tap_adv_3_0 = 0;
        data->cfg_tap_main = 1;
        data->cfg_tap_dly_4_0 = 0x0;
        data->cfg_vga_ctrl_bypass_4_0 = 0xa;
        data->cfg_eqR_force = 7;
        data->cfg_eqC_force_3_0 = 0x7;
        data->ln_cfg_alos_thr_2_0 = 0;
        data->dfe_enable = 0;
        break;
    case MEPA_MEDIA_TYPE_SFP28_25G_SR:
    case MEPA_MEDIA_TYPE_SFP28_25G_LR:
    case MEPA_MEDIA_TYPE_SFP28_25G_ER:
        data->ln_cfg_en_adv = 1;
        data->ln_cfg_en_main = 1;
        data->ln_cfg_en_dly = 1;
        data->ln_cfg_tap_adv_3_0 = 0x3;
        data->ln_cfg_tap_main = 1;
        data->ln_cfg_tap_dly_4_0 = 0x8;
        data->pcs_en_adv = 1;
        data->pcs_en_main = 1;
        data->pcs_en_dly = 1;
        data->cfg_tap_adv_3_0 = 0x3;
        data->cfg_tap_main = 1;
        data->cfg_tap_dly_4_0 = 0x8;
        data->cfg_vga_ctrl_bypass_4_0 = 0xF;
        data->cfg_eqR_force = 0xa;
        data->cfg_eqC_force_3_0 = 0x0;
        data->ln_cfg_alos_thr_2_0 = 0;
        data->dfe_enable = 1;
        break;

    case MEPA_MEDIA_TYPE_SFP28_25G_DAC1M:
        data->ln_cfg_en_adv = 1;
        data->ln_cfg_en_main = 1;
        data->ln_cfg_en_dly = 1;
        data->ln_cfg_tap_adv_3_0 = 0x8;
        data->ln_cfg_tap_main = 1;
        data->ln_cfg_tap_dly_4_0 = 0x12;
        data->pcs_en_adv = 1;
        data->pcs_en_main = 1;
        data->pcs_en_dly = 1;
        data->cfg_tap_adv_3_0 = 0x8;
        data->cfg_tap_main = 1;
        data->cfg_tap_dly_4_0 = 0x12;
        data->cfg_vga_ctrl_bypass_4_0 = 0xf;
        data->cfg_eqR_force = 0xb;
        data->cfg_eqC_force_3_0 = 0x0;
        data->ln_cfg_alos_thr_2_0 = 0;
        data->dfe_enable = 1;
        break;

    case MEPA_MEDIA_TYPE_SFP28_25G_DAC2M:
        data->ln_cfg_en_adv = 1;
        data->ln_cfg_en_main = 1;
        data->ln_cfg_en_dly = 1;
        data->ln_cfg_tap_adv_3_0 = 0x8;
        data->ln_cfg_tap_main = 1;
        data->ln_cfg_tap_dly_4_0 = 0x12;
        data->pcs_en_adv = 1;
        data->pcs_en_main = 1;
        data->pcs_en_dly = 1;
        data->cfg_tap_adv_3_0 = 0x8;
        data->cfg_tap_main = 1;
        data->cfg_tap_dly_4_0 = 0x12;
        data->cfg_vga_ctrl_bypass_4_0 = 0xf;
        data->cfg_eqR_force = 0xf;
        data->cfg_eqC_force_3_0 = 0x0;
        data->ln_cfg_alos_thr_2_0 = 0;
        data->dfe_enable = 1;
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "Selected Host or Line Media is not supported in PHY on port %d\n", phy_data->port_no);
        break;
    }
    return MEPA_RC_OK;
}

mepa_bool_t lan80xx_target_reg_width(uint16_t target, uint32_t addr)
{
    switch (target) {
    case 3:
        if  ((addr <= 0x07FF) ||
             (addr >= 0x8000 && addr <= 0x8FFF) ||
             (addr >= 0xE000 && addr <= 0xE0FF)) {
            return FALSE;
        } else {
            return TRUE;
        }
        break;
    case 8:
        return TRUE;
        break;
    case 10:
        return TRUE;
        break;
    case 30:
        if ((addr <= 0x01FF) ||
            (addr >= 0x0200 && addr <= 0x05FF) ||
            (addr >= 0x0600 && addr <= 0x06FF) ||
            (addr >= 0x8000 && addr <= 0x800F)) {
            return FALSE;
        } else {
            return TRUE;
        }
        break;
    case 31:
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}


mepa_rc lan80xx_power_set_priv(mepa_device_t           *dev,
                               const mepa_port_no_t    port_no,
                               const phy25g_power_t    power)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    data->port_state.power = (power == LAN80XX_PHY_POWER_ENABLE) ? 1 : 0;

    if (data->port_state.power == LAN80XX_PHY_POWER_ENABLE) {
        /* Performing Serdes Configuration to Power Up Serdes*/
        if (lan80xx_serdes_configuration(dev, port_no, data->conf.speed, &data->port_state.port_mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Serdes Power-Up Configuration failed : %d \n", data->port_no);
            return MEPA_RC_ERROR;
        }

        return MEPA_RC_OK;
    }

    /* Power Down the Serdes */
    /* h_l = 0 for Host Configuration and h_l = 1 for Line Configuration */
    for (int h_l = 1; h_l >= 0; h_l--) {

        /* HOST0 should not be powered down as this provides the Clock for all the Modules of the PHY */
        if ((data->channel_id != MEPA_CHANNELID_0) && (h_l == 0)) {
            continue;
        }

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0xFF); /* Select CMU registers */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_09),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_09_CFG_CTRL_LOGIC_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_09_CFG_CTRL_LOGIC_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0C),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0C_CFG_VCO_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0C_CFG_VCO_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0D),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0D_CFG_CK_TREE_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0D_CFG_CK_TREE_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0C),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_UP(0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_UP);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0C),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_DN(0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_DN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_12),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_12_CFG_PD_DIV64(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_12_CFG_PD_DIV64);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_11),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_11_CFG_PD_DIV66(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_11_CFG_PD_DIV66);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_09),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_09_CFG_REFCK_TERM_EN(0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_09_CFG_REFCK_TERM_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_10),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_10_CFG_REFCK_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_10_CFG_REFCK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_05),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_05_CFG_IBIAS_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_05_CFG_IBIAS_PD);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0x0); /* Select LANE registers */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0F),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_18),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN);


        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_23),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_23_LN_CFG_PI_EN(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_23_LN_CFG_PI_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_CLK(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_CLK);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_CML(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_CML);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU(0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_18),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD(1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD);
    }
    T_I(MEPA_TRACE_GRP_GEN, "Malibu in %d mode on port %d\n", data->port_state.power ? "Power-up" : "Power-down", port_no);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pma_cmu_lane_access_check(mepa_device_t               *dev,
                                                 const mepa_port_no_t        port_no,
                                                 const u16                   mmd,
                                                 const u32                   addr)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 val = 0;
    if (addr >= LAN80XX_PMA_CMU_GRP_START_ADDR && addr <= LAN80XX_PMA_CMU_GRP_END_ADDR) {
        val = 0xFF; /* CMU Access */
    } else if (addr >= LAN80XX_PMA_LANE_GRP_START_ADDR && addr <= LAN80XX_PMA_LANE_GRP_END_ADDR) {
        val = 0x0;  /* LANE Access */
    } else {
        return MEPA_RC_OK;
    }
    if (lan80xx_csr_wr(dev, port_no, mmd, 0, LAN80XX_CMU_FF_REGISTER_ADDRESS, val) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not write CMU FF Register \n");
        return rc;
    }
    return MEPA_RC_OK;
}

mepa_rc  lan80xx_serdes_data_init(mepa_device_t  *dev, mepa_port_speed_t speed, phy25g_serdes_conf_data_t *serdes_data)
{
    switch (speed) {
    case MESA_SPEED_25G:
        serdes_data->r_dwidthctrl_from_hwt              = LAN80XX_25G_R_DWIDTHCTRL_FROM_HWT;
        serdes_data->r_reg_manual                       = LAN80XX_25G_R_REG_MANUAL;
        serdes_data->cfg_common_reserve                 = LAN80XX_25G_CFG_COMMON_RESERVE_7_0;
        serdes_data->cfg_en_dummy                       = LAN80XX_25G_CFG_EN_DUMMY;
        serdes_data->cfg_pll_reserve_3_0                = LAN80XX_25G_CFG_PLL_RESERVE_3_0;
        serdes_data->l0_cfg_txcal_en                    = LAN80XX_25G_L0_CFG_TXCAL_EN;
        serdes_data->l0_cfg_tx_reserve_15_8             = LAN80XX_25G_L0_CFG_TX_RESERVE_15_8;
        serdes_data->l0_cfg_tx_reserve_7_0              = LAN80XX_25G_L0_CFG_TX_RESERVE_7_0;
        serdes_data->cfg_pll_lol_set                    = LAN80XX_25G_CFG_PLL_LOL_SET;
        serdes_data->cfg_i_vco_3_0                      = LAN80XX_25G_CFG_I_VCO_3_0;
        serdes_data->cfg_icp_base_sel_3_0               = LAN80XX_25G_CFG_ICP_BASE_SEL_3_0;
        serdes_data->cfg_icp_sel_2_0                    = LAN80XX_25G_CFG_ICP_SEL_2_0;
        serdes_data->cfg_rsel_2_0                       = LAN80XX_25G_CFG_RSEL_2_0;
        serdes_data->r_dwidthctrl_2_0                   = LAN80XX_25G_R_DWIDTHCTRL_2_0;
        serdes_data->r_txfifo_ck_div_pmad_2_0           = LAN80XX_25G_R_TXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->r_rxfifo_ck_div_pmad_2_0           = LAN80XX_25G_R_RXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->cfg_vco_div_mode_1_0               = LAN80XX_25G_CFG_VCO_DIV_MODE_1_0;
        serdes_data->cfg_pre_divsel_1_0                 = LAN80XX_25G_CFG_PRE_DIVSEL_1_0;
        serdes_data->cfg_sel_div_3_0                    = LAN80XX_25G_CFG_SEL_DIV_3_0;
        serdes_data->r_multi_lane_mode                  = LAN80XX_25G_R_MULTI_LANE_MODE;
        serdes_data->ln_cfg_pma_tx_ck_bitwidth_2_0      = LAN80XX_25G_LN_CFG_PMA_TX_CK_BITWIDTH_2_0;
        serdes_data->ln_cfg_tx_prediv_1_0               = LAN80XX_25G_LN_CFG_TX_PREDIV_1_0;
        serdes_data->ln_cfg_rxdiv_sel_2_0               = LAN80XX_25G_LN_CFG_RXDIV_SEL_2_0;
        serdes_data->ln_cfg_tx_subrate_2_0              = LAN80XX_25G_LN_CFG_TX_SUBRATE_2_0;
        serdes_data->ln_cfg_rx_subrate_2_0              = LAN80XX_25G_LN_CFG_RX_SUBRATE_2_0;
        serdes_data->ln_cfg_erramp_pd                   = LAN80XX_25G_LN_CFG_ERRAMP_PD;
        serdes_data->ln_cfg_ecdr_pd                     = LAN80XX_25G_LN_CFG_ECDR_PD;
        serdes_data->ln_cfg_itx_ipdriver_base_2_0       = LAN80XX_25G_LN_CFG_ITX_IPDRIVER_BASE_2_0;
        serdes_data->ln_cfg_dmux_pd                     = LAN80XX_25G_LN_CFG_DMUX_PD;
        serdes_data->ln_cfg_pd_cml                      = LAN80XX_25G_LN_CFG_PD_CML;
        serdes_data->ln_cfg_pd_driver                   = LAN80XX_25G_LN_CFG_PD_DRIVER;
        serdes_data->ln_cfg_rx_reg_pu                   = LAN80XX_25G_LN_CFG_RX_REG_PU;
        serdes_data->ln_cfg_pd_rms_det                  = LAN80XX_25G_LN_CFG_PD_RMS_DET;
        serdes_data->ln_cfg_dcdr_pd                     = LAN80XX_25G_LN_CFG_DCDR_PD;
        serdes_data->ln_cfg_pd_sq                       = 0x0;
        serdes_data->ln_cfg_iscan_en                    = LAN80XX_25G_LN_CFG_ISCAN_EN;
        serdes_data->ln_cfg_en_fast_iscan               = LAN80XX_25G_LN_CFG_EN_FAST_ISCAN;
        serdes_data->ln_cfg_dmux_clk_pd                 = LAN80XX_25G_LN_CFG_DMUX_CLK_PD;
        serdes_data->ln_cfg_pi_en                       = LAN80XX_25G_LN_CFG_PI_EN;
        serdes_data->ln_cfg_pd_ctle                     = LAN80XX_25G_LN_CFG_PD_CTLE;
        serdes_data->ln_cfg_summer_en                   = LAN80XX_25G_LN_CFG_SUMMER_EN;
        serdes_data->ln_cfg_pmad_ck_pd                  = LAN80XX_25G_LN_CFG_PMAD_CK_PD;
        serdes_data->ln_cfg_pd_clk                      = LAN80XX_25G_LN_CFG_PD_CLK;
        serdes_data->ln_cfg_filter2nd_yz_6_0            = LAN80XX_25G_LN_CFG_FILTER2ND_YZ_6_0;
        serdes_data->ln_cfg_tx_reserve_15_8             = LAN80XX_25G_LN_CFG_TX_RESERVE_15_8;
        serdes_data->ln_cfg_tx_reserve_7_0              = LAN80XX_25G_LN_CFG_TX_RESERVE_7_0;
        serdes_data->ln_cfg_bw_1_0                      = LAN80XX_25G_LN_CFG_BW_1_0;
        serdes_data->ln_cfg_txcal_man_en                = LAN80XX_25G_LN_CFG_TXCAL_MAN_EN;
        serdes_data->ln_cfg_txcal_shift_code_5_0        = LAN80XX_25G_LN_CFG_TXCAL_SHIFT_CODE_5_0;
        serdes_data->ln_cfg_txcal_valid_sel_3_0         = LAN80XX_25G_LN_CFG_TXCAL_VALID_SEL_3_0;
        serdes_data->ln_cfg_cdr_kf_2_0                  = LAN80XX_25G_LN_CFG_CDR_KF_2_0;
        serdes_data->ln_cfg_cdr_m_7_0                   = LAN80XX_25G_LN_CFG_CDR_M_7_0;
        serdes_data->ln_cfg_pi_bw_3_0                   = LAN80XX_25G_LN_CFG_PI_BW_3_0;
        serdes_data->ln_cfg_dis_2ndorder                = LAN80XX_25G_LN_CFG_DIS_2NDORDER;
        serdes_data->ln_cfg_ctle_rstn                   = LAN80XX_25G_LN_CFG_CTLE_RSTN;
        serdes_data->ln_cfg_rx_reserve_7_0              = LAN80XX_25G_LN_CFG_RX_RESERVE_7_0;
        serdes_data->ln_cfg_rx_reserve_15_8             = LAN80XX_25G_LN_CFG_RX_RESERVE_15_8;
        serdes_data->ln_cfg_rxterm_2_0                  = LAN80XX_25G_LN_CFG_RXTERM_2_0;
        serdes_data->ln_cfg_sum_setcm_en                = LAN80XX_25G_LN_CFG_SUM_SETCM_EN;
        serdes_data->ln_cfg_init_pos_iscan_6_0          = LAN80XX_25G_LN_CFG_INIT_POS_ISCAN_6_0;
        serdes_data->ln_cfg_init_pos_ipi_6_0            = LAN80XX_25G_LN_CFG_INIT_POS_IPI_6_0;
        serdes_data->ln_cfg_dfedig_m_2_0                = LAN80XX_25G_LN_CFG_DFEDIG_M_2_0;
        serdes_data->ln_cfg_en_dfedig                   = LAN80XX_25G_LN_CFG_EN_DFEDIG;
        serdes_data->ln_cfg_cdrck_en                    = LAN80XX_25G_LN_CFG_CDRCK_EN;
        break;
    case MESA_SPEED_10G:
        serdes_data->r_dwidthctrl_from_hwt              = LAN80XX_10G_R_DWIDTHCTRL_FROM_HWT;
        serdes_data->r_reg_manual                       = LAN80XX_10G_R_REG_MANUAL;
        serdes_data->cfg_common_reserve                 = LAN80XX_10G_CFG_COMMON_RESERVE_7_0;
        serdes_data->cfg_en_dummy                       = LAN80XX_10G_CFG_EN_DUMMY;
        serdes_data->cfg_pll_reserve_3_0                = LAN80XX_10G_CFG_PLL_RESERVE_3_0;
        serdes_data->l0_cfg_txcal_en                    = LAN80XX_10G_L0_CFG_TXCAL_EN;
        serdes_data->l0_cfg_tx_reserve_15_8             = LAN80XX_10G_L0_CFG_TX_RESERVE_15_8;
        serdes_data->l0_cfg_tx_reserve_7_0              = LAN80XX_10G_L0_CFG_TX_RESERVE_7_0;
        serdes_data->cfg_pll_lol_set                    = LAN80XX_10G_CFG_PLL_LOL_SET;
        serdes_data->cfg_i_vco_3_0                      = LAN80XX_10G_CFG_I_VCO_3_0;
        serdes_data->cfg_icp_base_sel_3_0               = LAN80XX_10G_CFG_ICP_BASE_SEL_3_0;
        serdes_data->cfg_icp_sel_2_0                    = LAN80XX_10G_CFG_ICP_SEL_2_0;
        serdes_data->cfg_rsel_2_0                       = LAN80XX_10G_CFG_RSEL_2_0;
        serdes_data->r_dwidthctrl_2_0                   = LAN80XX_10G_R_DWIDTHCTRL_2_0;
        serdes_data->r_txfifo_ck_div_pmad_2_0           = LAN80XX_10G_R_TXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->r_rxfifo_ck_div_pmad_2_0           = LAN80XX_10G_R_RXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->cfg_vco_div_mode_1_0               = LAN80XX_10G_CFG_VCO_DIV_MODE_1_0;
        serdes_data->cfg_pre_divsel_1_0                 = LAN80XX_10G_CFG_PRE_DIVSEL_1_0;
        serdes_data->cfg_sel_div_3_0                    = LAN80XX_10G_CFG_SEL_DIV_3_0;
        serdes_data->r_multi_lane_mode                  = LAN80XX_10G_R_MULTI_LANE_MODE;
        serdes_data->ln_cfg_pma_tx_ck_bitwidth_2_0      = LAN80XX_10G_LN_CFG_PMA_TX_CK_BITWIDTH_2_0;
        serdes_data->ln_cfg_tx_prediv_1_0               = LAN80XX_10G_LN_CFG_TX_PREDIV_1_0;
        serdes_data->ln_cfg_rxdiv_sel_2_0               = LAN80XX_10G_LN_CFG_RXDIV_SEL_2_0;
        serdes_data->ln_cfg_tx_subrate_2_0              = LAN80XX_10G_LN_CFG_TX_SUBRATE_2_0;
        serdes_data->ln_cfg_rx_subrate_2_0              = LAN80XX_10G_LN_CFG_RX_SUBRATE_2_0;
        serdes_data->ln_cfg_erramp_pd                   = LAN80XX_10G_LN_CFG_ERRAMP_PD;
        serdes_data->ln_cfg_ecdr_pd                     = LAN80XX_10G_LN_CFG_ECDR_PD;
        serdes_data->ln_cfg_itx_ipdriver_base_2_0       = LAN80XX_10G_LN_CFG_ITX_IPDRIVER_BASE_2_0;
        serdes_data->ln_cfg_dmux_pd                     = LAN80XX_10G_LN_CFG_DMUX_PD;
        serdes_data->ln_cfg_pd_cml                      = LAN80XX_10G_LN_CFG_PD_CML;
        serdes_data->ln_cfg_pd_driver                   = LAN80XX_10G_LN_CFG_PD_DRIVER;
        serdes_data->ln_cfg_rx_reg_pu                   = LAN80XX_10G_LN_CFG_RX_REG_PU;
        serdes_data->ln_cfg_pd_rms_det                  = LAN80XX_10G_LN_CFG_PD_RMS_DET;
        serdes_data->ln_cfg_dcdr_pd                     = LAN80XX_10G_LN_CFG_DCDR_PD;
        serdes_data->ln_cfg_pd_sq                       = 0x0;
        serdes_data->ln_cfg_iscan_en                    = LAN80XX_10G_LN_CFG_ISCAN_EN;
        serdes_data->ln_cfg_en_fast_iscan               = LAN80XX_10G_LN_CFG_EN_FAST_ISCAN;
        serdes_data->ln_cfg_dmux_clk_pd                 = LAN80XX_10G_LN_CFG_DMUX_CLK_PD;
        serdes_data->ln_cfg_pi_en                       = LAN80XX_10G_LN_CFG_PI_EN;
        serdes_data->ln_cfg_pd_ctle                     = LAN80XX_10G_LN_CFG_PD_CTLE;
        serdes_data->ln_cfg_summer_en                   = LAN80XX_10G_LN_CFG_SUMMER_EN;
        serdes_data->ln_cfg_pmad_ck_pd                  = LAN80XX_10G_LN_CFG_PMAD_CK_PD;
        serdes_data->ln_cfg_pd_clk                      = LAN80XX_10G_LN_CFG_PD_CLK;
        serdes_data->ln_cfg_filter2nd_yz_6_0            = LAN80XX_10G_LN_CFG_FILTER2ND_YZ_6_0;
        serdes_data->ln_cfg_tx_reserve_15_8             = LAN80XX_10G_LN_CFG_TX_RESERVE_15_8;
        serdes_data->ln_cfg_tx_reserve_7_0              = LAN80XX_10G_LN_CFG_TX_RESERVE_7_0;
        serdes_data->ln_cfg_bw_1_0                      = LAN80XX_10G_LN_CFG_BW_1_0;
        serdes_data->ln_cfg_txcal_man_en                = LAN80XX_10G_LN_CFG_TXCAL_MAN_EN;
        serdes_data->ln_cfg_txcal_shift_code_5_0        = LAN80XX_10G_LN_CFG_TXCAL_SHIFT_CODE_5_0;
        serdes_data->ln_cfg_txcal_valid_sel_3_0         = LAN80XX_10G_LN_CFG_TXCAL_VALID_SEL_3_0;
        serdes_data->ln_cfg_cdr_kf_2_0                  = LAN80XX_10G_LN_CFG_CDR_KF_2_0;
        serdes_data->ln_cfg_cdr_m_7_0                   = LAN80XX_10G_LN_CFG_CDR_M_7_0;
        serdes_data->ln_cfg_pi_bw_3_0                   = LAN80XX_10G_LN_CFG_PI_BW_3_0;
        serdes_data->ln_cfg_dis_2ndorder                = LAN80XX_10G_LN_CFG_DIS_2NDORDER;
        serdes_data->ln_cfg_ctle_rstn                   = LAN80XX_10G_LN_CFG_CTLE_RSTN;
        serdes_data->ln_cfg_rx_reserve_7_0              = LAN80XX_10G_LN_CFG_RX_RESERVE_7_0;
        serdes_data->ln_cfg_rx_reserve_15_8             = LAN80XX_10G_LN_CFG_RX_RESERVE_15_8;
        serdes_data->ln_cfg_rxterm_2_0                  = LAN80XX_10G_LN_CFG_RXTERM_2_0;
        serdes_data->ln_cfg_sum_setcm_en                = LAN80XX_10G_LN_CFG_SUM_SETCM_EN;
        serdes_data->ln_cfg_init_pos_iscan_6_0          = LAN80XX_10G_LN_CFG_INIT_POS_ISCAN_6_0;
        serdes_data->ln_cfg_init_pos_ipi_6_0            = LAN80XX_10G_LN_CFG_INIT_POS_IPI_6_0;
        serdes_data->ln_cfg_dfedig_m_2_0                = LAN80XX_10G_LN_CFG_DFEDIG_M_2_0;
        serdes_data->ln_cfg_en_dfedig                   = LAN80XX_10G_LN_CFG_EN_DFEDIG;
        serdes_data->ln_cfg_cdrck_en                    = LAN80XX_10G_LN_CFG_CDRCK_EN;
        break;
    case MESA_SPEED_1G:
        serdes_data->r_dwidthctrl_from_hwt              = LAN80XX_1G_R_DWIDTHCTRL_FROM_HWT;
        serdes_data->r_reg_manual                       = LAN80XX_1G_R_REG_MANUAL;
        serdes_data->cfg_common_reserve                 = LAN80XX_1G_CFG_COMMON_RESERVE_7_0;
        serdes_data->cfg_en_dummy                       = LAN80XX_1G_CFG_EN_DUMMY;
        serdes_data->cfg_pll_reserve_3_0                = LAN80XX_1G_CFG_PLL_RESERVE_3_0;
        serdes_data->l0_cfg_txcal_en                    = LAN80XX_1G_L0_CFG_TXCAL_EN;
        serdes_data->l0_cfg_tx_reserve_15_8             = LAN80XX_1G_L0_CFG_TX_RESERVE_15_8;
        serdes_data->l0_cfg_tx_reserve_7_0              = LAN80XX_1G_L0_CFG_TX_RESERVE_7_0;
        serdes_data->cfg_pll_lol_set                    = LAN80XX_1G_CFG_PLL_LOL_SET;
        serdes_data->cfg_i_vco_3_0                      = LAN80XX_1G_CFG_I_VCO_3_0;
        serdes_data->cfg_icp_base_sel_3_0               = LAN80XX_1G_CFG_ICP_BASE_SEL_3_0;
        serdes_data->cfg_icp_sel_2_0                    = LAN80XX_1G_CFG_ICP_SEL_2_0;
        serdes_data->cfg_rsel_2_0                       = LAN80XX_1G_CFG_RSEL_2_0;
        serdes_data->r_dwidthctrl_2_0                   = LAN80XX_1G_R_DWIDTHCTRL_2_0;
        serdes_data->r_txfifo_ck_div_pmad_2_0           = LAN80XX_1G_R_TXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->r_rxfifo_ck_div_pmad_2_0           = LAN80XX_1G_R_RXFIFO_CK_DIV_PMAD_2_0;
        serdes_data->cfg_vco_div_mode_1_0               = LAN80XX_1G_CFG_VCO_DIV_MODE_1_0;
        serdes_data->cfg_pre_divsel_1_0                 = LAN80XX_1G_CFG_PRE_DIVSEL_1_0;
        serdes_data->cfg_sel_div_3_0                    = LAN80XX_1G_CFG_SEL_DIV_3_0;
        serdes_data->r_multi_lane_mode                  = LAN80XX_1G_R_MULTI_LANE_MODE;
        serdes_data->ln_cfg_pma_tx_ck_bitwidth_2_0      = LAN80XX_1G_LN_CFG_PMA_TX_CK_BITWIDTH_2_0;
        serdes_data->ln_cfg_tx_prediv_1_0               = LAN80XX_1G_LN_CFG_TX_PREDIV_1_0;
        serdes_data->ln_cfg_rxdiv_sel_2_0               = LAN80XX_1G_LN_CFG_RXDIV_SEL_2_0;
        serdes_data->ln_cfg_tx_subrate_2_0              = LAN80XX_1G_LN_CFG_TX_SUBRATE_2_0;
        serdes_data->ln_cfg_rx_subrate_2_0              = LAN80XX_1G_LN_CFG_RX_SUBRATE_2_0;
        serdes_data->ln_cfg_erramp_pd                   = LAN80XX_1G_LN_CFG_ERRAMP_PD;
        serdes_data->ln_cfg_ecdr_pd                     = LAN80XX_1G_LN_CFG_ECDR_PD;
        serdes_data->ln_cfg_itx_ipdriver_base_2_0       = LAN80XX_1G_LN_CFG_ITX_IPDRIVER_BASE_2_0;
        serdes_data->ln_cfg_dmux_pd                     = LAN80XX_1G_LN_CFG_DMUX_PD;
        serdes_data->ln_cfg_pd_cml                      = LAN80XX_1G_LN_CFG_PD_CML;
        serdes_data->ln_cfg_pd_driver                   = LAN80XX_1G_LN_CFG_PD_DRIVER;
        serdes_data->ln_cfg_rx_reg_pu                   = LAN80XX_1G_LN_CFG_RX_REG_PU;
        serdes_data->ln_cfg_pd_rms_det                  = LAN80XX_1G_LN_CFG_PD_RMS_DET;
        serdes_data->ln_cfg_dcdr_pd                     = LAN80XX_1G_LN_CFG_DCDR_PD;
        serdes_data->ln_cfg_pd_sq                       = 0x0;
        serdes_data->ln_cfg_iscan_en                    = LAN80XX_1G_LN_CFG_ISCAN_EN;
        serdes_data->ln_cfg_en_fast_iscan               = LAN80XX_1G_LN_CFG_EN_FAST_ISCAN;
        serdes_data->ln_cfg_dmux_clk_pd                 = LAN80XX_1G_LN_CFG_DMUX_CLK_PD;
        serdes_data->ln_cfg_pi_en                       = LAN80XX_1G_LN_CFG_PI_EN;
        serdes_data->ln_cfg_pd_ctle                     = LAN80XX_1G_LN_CFG_PD_CTLE;
        serdes_data->ln_cfg_summer_en                   = LAN80XX_1G_LN_CFG_SUMMER_EN;
        serdes_data->ln_cfg_pmad_ck_pd                  = LAN80XX_1G_LN_CFG_PMAD_CK_PD;
        serdes_data->ln_cfg_pd_clk                      = LAN80XX_1G_LN_CFG_PD_CLK;
        serdes_data->ln_cfg_filter2nd_yz_6_0            = LAN80XX_1G_LN_CFG_FILTER2ND_YZ_6_0;
        serdes_data->ln_cfg_tx_reserve_15_8             = LAN80XX_1G_LN_CFG_TX_RESERVE_15_8;
        serdes_data->ln_cfg_tx_reserve_7_0              = LAN80XX_1G_LN_CFG_TX_RESERVE_7_0;
        serdes_data->ln_cfg_bw_1_0                      = LAN80XX_1G_LN_CFG_BW_1_0;
        serdes_data->ln_cfg_txcal_man_en                = LAN80XX_1G_LN_CFG_TXCAL_MAN_EN;
        serdes_data->ln_cfg_txcal_shift_code_5_0        = LAN80XX_1G_LN_CFG_TXCAL_SHIFT_CODE_5_0;
        serdes_data->ln_cfg_txcal_valid_sel_3_0         = LAN80XX_1G_LN_CFG_TXCAL_VALID_SEL_3_0;
        serdes_data->ln_cfg_cdr_kf_2_0                  = LAN80XX_1G_LN_CFG_CDR_KF_2_0;
        serdes_data->ln_cfg_cdr_m_7_0                   = LAN80XX_1G_LN_CFG_CDR_M_7_0;
        serdes_data->ln_cfg_pi_bw_3_0                   = LAN80XX_1G_LN_CFG_PI_BW_3_0;
        serdes_data->ln_cfg_dis_2ndorder                = LAN80XX_1G_LN_CFG_DIS_2NDORDER;
        serdes_data->ln_cfg_ctle_rstn                   = LAN80XX_1G_LN_CFG_CTLE_RSTN;
        serdes_data->ln_cfg_rx_reserve_7_0              = LAN80XX_1G_LN_CFG_RX_RESERVE_7_0;
        serdes_data->ln_cfg_rx_reserve_15_8             = LAN80XX_1G_LN_CFG_RX_RESERVE_15_8;
        serdes_data->ln_cfg_rxterm_2_0                  = LAN80XX_1G_LN_CFG_RXTERM_2_0;
        serdes_data->ln_cfg_sum_setcm_en                = LAN80XX_1G_LN_CFG_SUM_SETCM_EN;
        serdes_data->ln_cfg_init_pos_iscan_6_0          = LAN80XX_1G_LN_CFG_INIT_POS_ISCAN_6_0;
        serdes_data->ln_cfg_init_pos_ipi_6_0            = LAN80XX_1G_LN_CFG_INIT_POS_IPI_6_0;
        serdes_data->ln_cfg_dfedig_m_2_0                = LAN80XX_1G_LN_CFG_DFEDIG_M_2_0;
        serdes_data->ln_cfg_en_dfedig                   = LAN80XX_1G_LN_CFG_EN_DFEDIG;
        serdes_data->ln_cfg_cdrck_en                    = LAN80XX_1G_LN_CFG_CDRCK_EN;
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "\nSerdes init, Speed Not Supported\n");
        break;
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_sd25_los_enable(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;

    /* Enable LOS in LINE */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PMA_8BIT_CMU_FF, 0x0);
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_3F, LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_ALOS_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_ALOS_EN);
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_2E, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_SQ);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS,
                    LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(1),
                    LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN |
                    LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_INV);

    /* Enable LOS in HOST */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PMA_8BIT_CMU_FF, 0x0);
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_3F, LAN80XX_M_HOST_PMA_8BIT_LANE_3F_LN_R_ALOS_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_3F_LN_R_ALOS_EN);
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_2E, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_DIS_SQ);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_SERDES_LOS,
                    LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(1),
                    LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN |
                    LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_INV);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_serdes_loopback_check(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    if (data->port_state.loopback_conf.h1_lp == 0 && data->port_state.loopback_conf.h6_lp == 0 && data->port_state.loopback_conf.h5_lp == 0 &&
        data->port_state.loopback_conf.l1_lp == 0 && data->port_state.loopback_conf.l5_lp == 0 && data->port_state.loopback_conf.l6_lp == 0) {
        return MEPA_RC_OK;
    }

    /* If any of Serdes Loopbacks are enabled before configuring serdes, then reconfiguring the same loopback */
    mepa_loopback_t loopback = {0};
    loopback.mac_serdes_equip_ena    = data->port_state.loopback_conf.h1_lp;
    loopback.mac_serdes_input_ena    = data->port_state.loopback_conf.h6_lp;
    loopback.mac_serdes_facility_ena = data->port_state.loopback_conf.h5_lp;
    loopback.media_serdes_equip_ena  = data->port_state.loopback_conf.l1_lp;
    loopback.media_serdes_facility_ena = data->port_state.loopback_conf.l5_lp;
    loopback.media_serdes_input_ena    = data->port_state.loopback_conf.l6_lp;

    if (lan80xx_loopback_set_priv(dev, port_no, &loopback) != MEPA_RC_OK) {
        return MEPA_RC_ERROR;
    }
    return MEPA_RC_OK;
}


mepa_rc lan80xx_serdes_configuration(mepa_device_t *dev, mepa_port_no_t port_no, mepa_port_speed_t speed, phy25g_port_mode_t  *mode)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_serdes_conf_data_t serdes_data = {0};
    phy25g_serdes_data_t serdes_media_val = {0};
    u32 rd_val = 0;
    u8 u8timeout = 0;

    lan80xx_serdes_data_init(dev, speed, &serdes_data);
    phy25g_media_t media = {0};

    /* h_l = 0 for Host Configuration and h_l = 1 for Line Configuration */
    for (u8 h_l = 0; h_l < 2; h_l++) {
        /* Serdes data depending on the serdes media */
        media = h_l ? data->conf.conf_25g.line_media : data->conf.conf_25g.host_media;
        if (lan80xx_serdes_data_get(dev, &serdes_media_val, media) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in getting serdes data on port no : %d\n", port_no);
            return MEPA_RC_ERROR;
        }

        /* Toggle Reset */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_SD_LANE_CFG_0), LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST(1),
                        LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_SD_LANE_CFG_0), LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST(0),
                        LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST);

        if (h_l == 0) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_HOST_SD25G_RESET,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST |
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST |
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST);
        } else {

            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_LINE_SD25G_RESET,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST |
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST |
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST);
        }

        if (h_l == 0) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_HOST_SD25G_RESET, 0, LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_BASECK_RST);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_LINE_SD25G_RESET, 0, LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST);
        }

        /* CMU Register Configurations */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0xFF); /* Select CMU registers */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_1A),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_FROM_HWT(serdes_data.r_dwidthctrl_from_hwt),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_FROM_HWT);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_1A), LAN80XX_F_LINE_PMA_8BIT_CMU_1A_R_REG_MANUAL(serdes_data.r_reg_manual),
                        LAN80XX_M_LINE_PMA_8BIT_CMU_1A_R_REG_MANUAL);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_31),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_31_CFG_COMMON_RESERVE_7_0(serdes_data.cfg_common_reserve),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_31_CFG_COMMON_RESERVE_7_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_09), LAN80XX_F_HOST_PMA_8BIT_CMU_09_CFG_EN_DUMMY(serdes_data.cfg_en_dummy),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_09_CFG_EN_DUMMY);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_13),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_13_CFG_PLL_RESERVE_3_0(serdes_data.cfg_pll_reserve_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_13_CFG_PLL_RESERVE_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_40), LAN80XX_F_HOST_PMA_8BIT_CMU_40_L0_CFG_TXCAL_EN(serdes_data.l0_cfg_txcal_en),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_40_L0_CFG_TXCAL_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_46),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_46_L0_CFG_TX_RESERVE_15_8(serdes_data.l0_cfg_tx_reserve_15_8),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_46_L0_CFG_TX_RESERVE_15_8);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_45),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_45_L0_CFG_TX_RESERVE_7_0(serdes_data.l0_cfg_tx_reserve_7_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_45_L0_CFG_TX_RESERVE_7_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0B), 0, LAN80XX_M_HOST_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0B), LAN80XX_M_HOST_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN,
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_19), 0, LAN80XX_M_HOST_PMA_8BIT_CMU_19_R_CK_RESETB);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_19), LAN80XX_M_HOST_PMA_8BIT_CMU_19_R_CK_RESETB,
                        LAN80XX_M_HOST_PMA_8BIT_CMU_19_R_CK_RESETB);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_18), 0, LAN80XX_M_HOST_PMA_8BIT_CMU_18_R_PLL_RSTN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_18), LAN80XX_M_HOST_PMA_8BIT_CMU_18_R_PLL_RSTN,
                        LAN80XX_M_HOST_PMA_8BIT_CMU_18_R_PLL_RSTN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0C),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0C_CFG_PLL_LOL_SET(serdes_data.cfg_pll_lol_set),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0C_CFG_PLL_LOL_SET);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_12), LAN80XX_F_HOST_PMA_8BIT_CMU_12_CFG_I_VCO_3_0(serdes_data.cfg_i_vco_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_12_CFG_I_VCO_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0F),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0F_CFG_ICP_BASE_SEL_3_0(serdes_data.cfg_icp_base_sel_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0F_CFG_ICP_BASE_SEL_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_11), LAN80XX_F_HOST_PMA_8BIT_CMU_11_CFG_ICP_SEL_2_0(serdes_data.cfg_icp_sel_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_11_CFG_ICP_SEL_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0F), LAN80XX_F_HOST_PMA_8BIT_CMU_0F_CFG_RSEL_2_0(serdes_data.cfg_rsel_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0F_CFG_RSEL_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_1A), LAN80XX_F_HOST_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_2_0(serdes_data.r_dwidthctrl_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_30),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(serdes_data.r_txfifo_ck_div_pmad_2_0) |
                        LAN80XX_F_HOST_PMA_8BIT_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(serdes_data.r_rxfifo_ck_div_pmad_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0 |
                        LAN80XX_M_HOST_PMA_8BIT_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0C),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0C_CFG_VCO_DIV_MODE_1_0(serdes_data.cfg_vco_div_mode_1_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0C_CFG_VCO_DIV_MODE_1_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0D),
                        LAN80XX_F_HOST_PMA_8BIT_CMU_0D_CFG_PRE_DIVSEL_1_0(serdes_data.cfg_pre_divsel_1_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0D_CFG_PRE_DIVSEL_1_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_0E), LAN80XX_F_HOST_PMA_8BIT_CMU_0E_CFG_SEL_DIV_3_0(serdes_data.cfg_sel_div_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_0E_CFG_SEL_DIV_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_1F), LAN80XX_F_HOST_PMA_8BIT_CMU_1F_R_MULTI_LANE_MODE(serdes_data.r_multi_lane_mode),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_1F_R_MULTI_LANE_MODE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_17), 0, LAN80XX_M_HOST_PMA_8BIT_CMU_17_R_LBSLV_IN_PMAD);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(serdes_data.ln_cfg_pma_tx_ck_bitwidth_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_01),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_01_LN_CFG_TX_PREDIV_1_0(serdes_data.ln_cfg_tx_prediv_1_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_01_LN_CFG_TX_PREDIV_1_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_18),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_18_LN_CFG_RXDIV_SEL_2_0(serdes_data.ln_cfg_rxdiv_sel_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_RXDIV_SEL_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_2C_LN_CFG_TX_SUBRATE_2_0(serdes_data.ln_cfg_tx_subrate_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2C_LN_CFG_TX_SUBRATE_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_28),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_28_LN_CFG_RX_SUBRATE_2_0(serdes_data.ln_cfg_rx_subrate_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_28_LN_CFG_RX_SUBRATE_2_0);

        /* DFE Tap Values Enable */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0F),
                       LAN80XX_F_HOST_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1(serdes_media_val.dfe_enable ? 0x1f : 0));

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_18), LAN80XX_F_HOST_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(serdes_data.ln_cfg_erramp_pd),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1D), LAN80XX_F_HOST_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN(serdes_media_val.dfe_enable),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19), LAN80XX_F_HOST_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD(serdes_data.ln_cfg_ecdr_pd),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_01),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(serdes_data.ln_cfg_itx_ipdriver_base_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0);

        /* DFE Tap Values Enable */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_03),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0(serdes_media_val.ln_cfg_tap_dly_4_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_06),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0(serdes_media_val.ln_cfg_tap_adv_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_07),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_07_LN_CFG_EN_ADV(serdes_media_val.ln_cfg_en_adv) |
                        LAN80XX_F_HOST_PMA_8BIT_LANE_07_LN_CFG_EN_DLY(serdes_media_val.ln_cfg_en_dly),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_07_LN_CFG_EN_ADV |
                        LAN80XX_M_HOST_PMA_8BIT_LANE_07_LN_CFG_EN_DLY);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D), LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD(serdes_data.ln_cfg_dmux_pd),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CML(serdes_data.ln_cfg_pd_cml),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CML);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER(serdes_data.ln_cfg_pd_driver),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU(serdes_data.ln_cfg_rx_reg_pu) |
                        LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET(serdes_data.ln_cfg_pd_rms_det),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU |
                        LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD(serdes_data.ln_cfg_dcdr_pd),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ(serdes_data.ln_cfg_pd_sq),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ);

        /* Enable TAP MAIN */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN(serdes_media_val.ln_cfg_tap_main),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_06),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN(serdes_media_val.ln_cfg_en_main),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN(serdes_data.ln_cfg_iscan_en),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN(serdes_data.ln_cfg_en_fast_iscan),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN(serdes_media_val.dfe_enable),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(serdes_media_val.dfe_enable ? 0 : 1),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0E),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD(serdes_data.ln_cfg_dmux_clk_pd),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_23),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_23_LN_CFG_PI_EN(serdes_data.ln_cfg_pi_en),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_23_LN_CFG_PI_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE(serdes_data.ln_cfg_pd_ctle),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN(serdes_data.ln_cfg_summer_en),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1E),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD(serdes_data.ln_cfg_pmad_ck_pd),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CLK(serdes_data.ln_cfg_pd_clk),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CLK);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_29),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_29_LN_CFG_FILTER2ND_YZ_6_0(serdes_data.ln_cfg_filter2nd_yz_6_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_29_LN_CFG_FILTER2ND_YZ_6_0);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_43), serdes_data.ln_cfg_tx_reserve_15_8);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_42), serdes_data.ln_cfg_tx_reserve_7_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_05), LAN80XX_F_HOST_PMA_8BIT_CMU_41_L0_CFG_BW_1_0(serdes_data.ln_cfg_bw_1_0),
                        LAN80XX_M_HOST_PMA_8BIT_CMU_41_L0_CFG_BW_1_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0B),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_MAN_EN(serdes_data.ln_cfg_txcal_man_en),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_MAN_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0A),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(serdes_data.ln_cfg_txcal_shift_code_5_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_09),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(serdes_data.ln_cfg_txcal_valid_sel_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1A),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1A_LN_CFG_CDR_KF_2_0(serdes_data.ln_cfg_cdr_kf_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1A_LN_CFG_CDR_KF_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1B), LAN80XX_F_HOST_PMA_8BIT_LANE_1B_LN_CFG_CDR_M_7_0(serdes_data.ln_cfg_cdr_m_7_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1B_LN_CFG_CDR_M_7_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2B), LAN80XX_F_HOST_PMA_8BIT_LANE_2B_LN_CFG_PI_BW_3_0(serdes_data.ln_cfg_pi_bw_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2B_LN_CFG_PI_BW_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_2C_LN_CFG_DIS_2NDORDER(serdes_data.ln_cfg_dis_2ndorder),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2C_LN_CFG_DIS_2NDORDER);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E), LAN80XX_F_HOST_PMA_8BIT_LANE_2E_LN_CFG_CTLE_RSTN(serdes_data.ln_cfg_ctle_rstn),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_CTLE_RSTN);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_44), serdes_data.ln_cfg_rx_reserve_7_0);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_45), serdes_data.ln_cfg_rx_reserve_15_8);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0D_LN_CFG_RXTERM_2_0(serdes_data.ln_cfg_rxterm_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0D_LN_CFG_RXTERM_2_0);

        /* Rx Equalization configuration */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_21),
                       LAN80XX_F_HOST_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(serdes_media_val.cfg_vga_ctrl_bypass_4_0));


        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_22),
                       LAN80XX_F_HOST_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0(serdes_media_val.cfg_eqR_force));

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0(serdes_media_val.cfg_eqC_force_3_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_1E_LN_CFG_SUM_SETCM_EN(serdes_data.ln_cfg_sum_setcm_en),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_SUM_SETCM_EN);


        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_25),
                       LAN80XX_F_HOST_PMA_8BIT_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(serdes_data.ln_cfg_init_pos_iscan_6_0));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_26),
                       LAN80XX_F_HOST_PMA_8BIT_LANE_26_LN_CFG_INIT_POS_IPI_6_0(serdes_data.ln_cfg_init_pos_ipi_6_0));

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_0E),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(serdes_media_val.dfe_enable) |
                        LAN80XX_F_HOST_PMA_8BIT_LANE_0E_LN_CFG_DFEDIG_M_2_0(serdes_data.ln_cfg_dfedig_m_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG |
                        LAN80XX_M_HOST_PMA_8BIT_LANE_0E_LN_CFG_DFEDIG_M_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2E), LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG,
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG);

        if (h_l == 0) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_HOST_SD25G_RESET,
                            0,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_LINE_SD25G_RESET,
                            0,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST);
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1C), LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN,
                        LAN80XX_M_HOST_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0xFF);

        u8timeout = 0;
        /* Check Whether PMA Reset Completed max delay of 0.05ms*/
        while (1) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_SD_LANE_STAT_0), &rd_val);
            rd_val = LAN80XX_X_LINE_PMA_SD_LANE_STAT_0_LANE_RST_DONE(rd_val);
            if (rd_val == 1) {
                break;
            }
            MEPA_NSLEEP(1000); /* 1000 ns delay */
            u8timeout++;
            if (u8timeout >= 50) {
                T_E(MEPA_TRACE_GRP_GEN, "\n %s PMA Reset not Done, Expected value 0x1 but actual value is 0x%x on Port %d\n", h_l ? "LINE" : "HOST", rd_val, port_no);
                break;
            }
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_2A), LAN80XX_M_HOST_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS,
                        LAN80XX_M_HOST_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0xFF);

        rd_val = 0;
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_C0), &rd_val);
        rd_val = LAN80XX_X_LINE_PMA_8BIT_CMU_C0_PLL_LOL_UDL(rd_val);
        if (rd_val) {
            T_E(MEPA_TRACE_GRP_GEN, "\n %s PLL Loss of lock Detected, Expected value 0x0 but actual value is 0x%x on Port %d\n", h_l ? "LINE" : "HOST", rd_val, port_no);
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_2A), LAN80XX_M_HOST_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS,
                        LAN80XX_M_HOST_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_CMU_FF), 0x0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_SD_SER_RST),
                        0,
                        LAN80XX_M_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_SD_DES_RST),
                        0,
                        LAN80XX_M_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST);

        /* TX and RX Polarity Swap */
        /* By default, RX polarity is inverted inside the chip package so inverting the polarity variable here to handle
         * the polarity inversion inside the chip within API.
         * The variables "polarity.host_tx", "polarity.host_rx", "polarity.line_tx", "polarity.line_rx" will indicate the Polarity configurations outside the chip
         * (i.e, in User board PCB)
         */
        if (h_l == 0) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, mode->polarity.host_tx ? LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_TX_POL_INV : 0,
                            LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_TX_POL_INV);

            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, (!mode->polarity.host_rx) ? LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV : 0,
                            LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, mode->polarity.line_tx ? LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_TX_POL_INV : 0,
                            LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_TX_POL_INV);

            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, (!mode->polarity.line_rx) ? LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV : 0,
                            LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_18), LAN80XX_F_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN(serdes_data.ln_cfg_cdrck_en),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_04), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_1E), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_19), 0, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, h_l, PMA_8BIT_LANE_2D),
                        LAN80XX_F_HOST_PMA_8BIT_LANE_2D_LN_CFG_ALOS_THR_2_0(serdes_media_val.ln_cfg_alos_thr_2_0),
                        LAN80XX_M_HOST_PMA_8BIT_LANE_2D_LN_CFG_ALOS_THR_2_0);

    }
    data->port_state.power = LAN80XX_PHY_POWER_ENABLE;
    /* Serdes LOS Signal Enable */
    if (lan80xx_sd25_los_enable(dev, port_no) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Error in enabling SD LOS on port : %d\n", port_no);
    }

    if (lan80xx_serdes_loopback_check(dev, port_no) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Error in configuring Serdes Loopback on port no : %d\n", port_no);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_fec_configuration(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0, h_val = 0, l_val = 0;

    if (data->conf.conf_25g.base_r_10gfec || data->conf.conf_25g.base_r_25gfec) {
        val = (LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_RX |
               LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ENA_TX |
               LAN80XX_M_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL_FEC74_ERR_ENA);
        T_I(MEPA_TRACE_GRP_GEN, "BASE-R FEC Enabled on port : %d\n", port_no);
    } else {
        val = 0;
        T_I(MEPA_TRACE_GRP_GEN, "BASE-R FEC Disabled on port : %d\n", port_no);
    }
    switch (data->conf.aneg.advertise_dir) {
    case MEPA_ADV_SIDE_LINE:
        l_val = val;
        break;
    case MEPA_ADV_SIDE_HOST:
        h_val = val;
        break;
    case MEPA_ADV_SIDE_HOST_LINE:
        h_val = l_val = val;
        break;
    default:
        h_val = l_val = 0;
        data->conf.conf_25g.base_r_10gfec = 0;
        data->conf.conf_25g.base_r_25gfec = 0;
        break;
    }

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL, h_val);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_BASE_R_FEC_CONTROL, l_val);

    val = 0;
    if (data->conf.conf_25g.rs_fec_25g) {
        val = (LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA | LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_RADAPT_ENA);
        T_I(MEPA_TRACE_GRP_GEN, "25G RS FEC Enabled on port : %d\n", port_no);
    } else {
        val = 0;
        T_I(MEPA_TRACE_GRP_GEN, "25G RS FEC Disabled on port : %d\n", port_no);
    }
    switch (data->conf.aneg.advertise_dir) {
    case MEPA_ADV_SIDE_LINE:
        l_val = val;
        h_val = 0;
        break;
    case MEPA_ADV_SIDE_HOST:
        h_val = val;
        l_val = 0;
        break;
    case MEPA_ADV_SIDE_HOST_LINE:
        h_val = l_val = val;
        break;
    default:
        h_val = l_val = 0;
        data->conf.conf_25g.rs_fec_25g = 0;
        break;
    }

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_RSFEC_CFG, h_val);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_RSFEC_CFG, l_val);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_CWM_RADAPT_CFG,
                    LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG(0x1) |
                    LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL(0x3) |
                    LAN80XX_F_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL(0x8),
                    LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG |
                    LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL |
                    LAN80XX_M_HOST_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_CWM_RADAPT_CFG,
                    LAN80XX_F_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG(0x1) |
                    LAN80XX_F_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL(0x3) |
                    LAN80XX_F_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL(0x8),
                    LAN80XX_M_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_MIN_IFG |
                    LAN80XX_M_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_ADD_LVL |
                    LAN80XX_M_LINE_PCS_CFG_CWM_RADAPT_CFG_CWM_RADAPT_DROP_LVL);

    if (!data->conf.conf_25g.rs_fec_25g) {
        return MEPA_RC_OK;
    }

    /* MEPA-1028 SW Workarround to avoid hanging of RA FIFO when RSFEC in Enabled */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_SD_SER_RST,
                    LAN80XX_M_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST,
                    LAN80XX_M_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_SD_DES_RST,
                    LAN80XX_M_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST,
                    LAN80XX_M_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_SD_SER_RST, 0, LAN80XX_M_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_SD_DES_RST, 0, LAN80XX_M_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_SD_SER_RST,
                    LAN80XX_M_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST,
                    LAN80XX_M_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_SD_DES_RST,
                    LAN80XX_M_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST,
                    LAN80XX_M_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_SD_SER_RST, 0, LAN80XX_M_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_SD_DES_RST, 0, LAN80XX_M_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_operating_mode_set_priv(const mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_oper_mode_t phy_mode)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    if (phy_mode == PCS_RETIMER) {
        /* Configuring PHY in PCS Retimer Mode */
        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE);
        /* Disabling MAC Block */
        if (lan80xx_phy_mac_conf_set(dev, port_no, FALSE) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error is disabling MAC block in port : %d", port_no);
            return MEPA_RC_ERROR;
        }

        /* 1588 EGR and INGR in PCS Retimer Mode */
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE, LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE,
                        LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE, LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE,
                        LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE);

        data->port_state.port_mode.oper_mode = PCS_RETIMER;

        if (data->flow_control_ena) {
            if (lan80xx_flow_control_set_priv(dev, port_no, FALSE) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "Error is Disabling Flow Control in port : %d", port_no);
                return MEPA_RC_ERROR;
            }
        }
    } else {
        /* Configuring PHY in MAC Retimer Mode */
        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE,
                             LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE);

        /* In MAC Retimer Mode MAC block needs to be configured */
        if (lan80xx_phy_mac_conf_set(dev, port_no, TRUE) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error is configuring MAC block in port : %d", port_no);
            return MEPA_RC_ERROR;
        }
        /* 1588 EGR and INGR in MAC Retimer Mode */
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE, 0, LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE, 0, LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE);

        data->port_state.port_mode.oper_mode = MAC_RETIMER;
    }
    T_I(MEPA_TRACE_GRP_GEN, "PHY is in %s mode on port_no : %d\n", data->port_state.port_mode.oper_mode ? "MAC-RETIMER" : "PCS-RETIMER", port_no);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mode_conf_set(mepa_device_t *dev, mepa_port_no_t port_no, phy25g_port_mode_t  *mode)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "lan80xx_mode_conf_set - %u\n", port_no);
    if (mode->speed_oper_mode ==  LAN80XX_PHY_ANEG) {
        /* PCS and PMA Configurations are Done by Firmware */
        return MEPA_RC_OK;
    }

    /* Disable ANEG for fixed speed configurations */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_KR_AN_CFG0, 0, LAN80XX_M_LINE_KR_AN_CFG0_AN_ENABLE);
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_KR_AN_CFG0, 0, LAN80XX_M_HOST_KR_AN_CFG0_AN_ENABLE);

    if (mode->speed_oper_mode == LAN80XX_PHY_1G_MODE) {

        /* Disable 25G PCS */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS25G_CFG, 0, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS25G_CFG, 0, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);

        /* Enable SGMII for 1000BASE-T Media type */
        if (data->conf.conf_25g.line_media == MEPA_MEDIA_TYPE_1000BASE_T) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_MODE_CFG, LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA,
                            LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA);
            T_I(MEPA_TRACE_GRP_GEN, "LINE PCS1G SGMII Enabled \n");
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_MODE_CFG, 0,
                            LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA);
        }

        if (lan80xx_clause37_conf_set_priv(dev, port_no, &data->conf.cl37_conf) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Failed to configure Clause37 on port : %d\n", port_no);
            return MEPA_RC_ERROR;
        } 

        /* Line side configurations */
        /*line pcs enable */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_CFG, LAN80XX_M_LINE_PCS_CFG_PCS1G_CFG_PCS_ENA,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_CFG_PCS_ENA);

        /* line signal detect */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_SD_CFG,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_SD_CFG_SD_ENA |
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_SD_CFG_SD_SEL,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_SD_CFG_SD_ENA |
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_SD_CFG_SD_SEL);

        /*HOST pcs enable */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_CFG, LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA);

        /* HOST signal detect */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_SD_CFG,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_ENA |
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_SEL,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_ENA |
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_SD_CFG_SD_SEL);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG, LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_MODE_CFG, LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SAVE_PREAMBLE_ENA);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_MODE_CFG, 0, LAN80XX_M_HOST_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA);

        T_I(MEPA_TRACE_GRP_GEN, "PCS1G Enabled \n");
        if (lan80xx_serdes_configuration(dev, port_no, MESA_SPEED_1G, mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in configuring Serdes in 10G Mode on port : %d", port_no);
            return MEPA_RC_ERROR;
        }
    }
    if (mode->speed_oper_mode == LAN80XX_PHY_10G_LAN_MODE) {
        /* Disable 1G PCS */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_CFG, 0, LAN80XX_M_LINE_PCS_CFG_PCS1G_CFG_PCS_ENA);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_CFG, 0, LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA);

        /* PCS 25G Reset */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_CONTROL1, LAN80XX_M_HOST_PCS25G_CONTROL1_RESET, LAN80XX_M_HOST_PCS25G_CONTROL1_RESET);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_CONTROL1, LAN80XX_M_LINE_PCS25G_CONTROL1_RESET, LAN80XX_M_LINE_PCS25G_CONTROL1_RESET);

        /* Enable PCS */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS25G_CFG, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS25G_CFG, LAN80XX_M_LINE_PCS_CFG_PCS25G_CFG_PCS25G_ENA, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);

        /* PCS Speed Selection */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_CONTROL1, LAN80XX_F_HOST_PCS25G_CONTROL1_SPEED_SELECTION(0), LAN80XX_M_HOST_PCS25G_CONTROL1_SPEED_SELECTION);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_CONTROL1, LAN80XX_F_LINE_PCS25G_CONTROL1_SPEED_SELECTION(0), LAN80XX_M_LINE_PCS25G_CONTROL1_SPEED_SELECTION);

        /* Select 10G Hi-BER */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_VENDOR_PCS_MODE, 0, LAN80XX_M_HOST_PCS25G_VENDOR_PCS_MODE_HI_BER25);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_VENDOR_PCS_MODE, 0, LAN80XX_M_LINE_PCS25G_VENDOR_PCS_MODE_HI_BER25);

        /* Select 10G Hi-BER */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_VENDOR_PCS_MODE, 0, LAN80XX_M_HOST_PCS25G_VENDOR_PCS_MODE_HI_BER5);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_VENDOR_PCS_MODE, 0, LAN80XX_M_HOST_PCS25G_VENDOR_PCS_MODE_HI_BER5);

        T_I(MEPA_TRACE_GRP_GEN, "PCS10G Enabled on port : %d\n", port_no);

        if (lan80xx_serdes_configuration(dev, port_no, MESA_SPEED_10G, mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in configuring Serdes in 10G Mode on port : %d", port_no);
            return MEPA_RC_ERROR;
        }

        if (lan80xx_fec_configuration(dev, port_no) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in configuring FEC on port : %d", port_no);
            return MEPA_RC_ERROR;
        }

        /* PCS Signal Detect Enabled */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_SD_CFG,
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_SEL |
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_POL |
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_ENA);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG,
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_SEL |
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_POL |
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_ENA);
    }
    if (mode->speed_oper_mode == LAN80XX_PHY_25G_LAN_MODE) {

        /* Disable 1G PCS */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_CFG, 0, LAN80XX_M_LINE_PCS_CFG_PCS1G_CFG_PCS_ENA);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_CFG, 0, LAN80XX_M_HOST_PCS_CFG_PCS1G_CFG_PCS_ENA);

        /* PCS 25G Reset */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_CONTROL1, LAN80XX_M_HOST_PCS25G_CONTROL1_RESET, LAN80XX_M_HOST_PCS25G_CONTROL1_RESET);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_CONTROL1, LAN80XX_M_LINE_PCS25G_CONTROL1_RESET, LAN80XX_M_LINE_PCS25G_CONTROL1_RESET);

        /* Enable PCS */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS25G_CFG, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS25G_CFG, LAN80XX_M_LINE_PCS_CFG_PCS25G_CFG_PCS25G_ENA, LAN80XX_M_HOST_PCS_CFG_PCS25G_CFG_PCS25G_ENA);

        T_I(MEPA_TRACE_GRP_GEN, "PCS25G Enabled on port : %d\n", port_no);

        /* PCS Speed Selection */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_CONTROL1, LAN80XX_F_HOST_PCS25G_CONTROL1_SPEED_SELECTION(5), LAN80XX_M_HOST_PCS25G_CONTROL1_SPEED_SELECTION);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_CONTROL1, LAN80XX_F_LINE_PCS25G_CONTROL1_SPEED_SELECTION(5), LAN80XX_M_LINE_PCS25G_CONTROL1_SPEED_SELECTION);

        /* Select 25G Hi-BER */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS25G_VENDOR_PCS_MODE, LAN80XX_M_HOST_PCS25G_VENDOR_PCS_MODE_HI_BER25, LAN80XX_M_HOST_PCS25G_VENDOR_PCS_MODE_HI_BER25);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS25G_VENDOR_PCS_MODE, LAN80XX_M_LINE_PCS25G_VENDOR_PCS_MODE_HI_BER25, LAN80XX_M_LINE_PCS25G_VENDOR_PCS_MODE_HI_BER25);

        if (lan80xx_serdes_configuration(dev, port_no, MESA_SPEED_25G, mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in configuring Serdes in 25G Mode on port : %d", port_no);
            return MEPA_RC_ERROR;
        }

        if (lan80xx_fec_configuration(dev, port_no) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in configuring FEC on port : %d", port_no);
            return MEPA_RC_ERROR;
        }

        /* PCS Signal Detect Enabled */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_SD_CFG,
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_SEL |
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_POL |
                       LAN80XX_M_LINE_PCS_CFG_PCS25G_SD_CFG_SD_ENA);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_SD_CFG,
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_SEL |
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_POL |
                       LAN80XX_M_HOST_PCS_CFG_PCS25G_SD_CFG_SD_ENA);
    }
    return MEPA_RC_OK;
}


/* Initial function. Sets the operating mode of the Phy.   */
static mepa_rc lan80xx_mode_set_init(mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_port_mode_t  *mode)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_rc rc = MEPA_RC_ERROR;

    data->port_state.gpio_count = LAN80XX_GPIO_COUNT;
    //Mode set enable PCS and PMA
    rc = LAN80XX_RC_COLD(lan80xx_mode_conf_set(dev, port_no, mode));

    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Error in configuring lan80xx_mode_conf_set on port no : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Configuring PHY in PCS Retimer Mode */
        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE);
        /* Disabling MAC Block */
        if (lan80xx_phy_mac_conf_set(dev, port_no, FALSE) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error is disabling MAC block in port : %d", port_no);
            return MEPA_RC_ERROR;
        }
        /* 1588 EGR and INGR in PCS Retimer Mode */
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE, LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE,
                        LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE, LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE,
                        LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE);
    }

    if (data->port_state.port_mode.oper_mode == MAC_RETIMER) {

        u8 rx_read_thresh = 0, tx_read_thresh = 0;
        switch (mode->speed_oper_mode) {
        case LAN80XX_PHY_1G_MODE:
            tx_read_thresh = 0x4;
            rx_read_thresh = 0x5;
            break;
        case LAN80XX_PHY_10G_LAN_MODE:
            tx_read_thresh = 0x6;
            rx_read_thresh = 0x6;
            break;
        case LAN80XX_PHY_25G_LAN_MODE:
            tx_read_thresh = data->conf.conf_25g.rs_fec_25g ? 0x10 : 0x6;
            rx_read_thresh = 0x10;
            break;
        default:
            tx_read_thresh = 0x10;
            rx_read_thresh = 0x10;
            break;
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG,
                        LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH(tx_read_thresh + 2) |
                        LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH(rx_read_thresh + 2),
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH |
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH);


        LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG,
                        (LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_TX_READ_THRESH(tx_read_thresh) |
                         LAN80XX_F_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_RX_READ_THRESH(rx_read_thresh)),
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_TX_READ_THRESH |
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG_RX_READ_THRESH);
    }

    mode->oper_mode = data->port_state.port_mode.oper_mode;
    /* MAC Retimer configuration will be done by "lan80xx_operating_mode_set" API */
    T_D(MEPA_TRACE_GRP_GEN, "Serdes and PCS Configuration Done on port : %d\n", port_no);
    T_I(MEPA_TRACE_GRP_GEN, "PHY is on %s mode on port : %d\n", data->port_state.port_mode.oper_mode ? "MAC_RETIMER" : "PCS_RETIMER", port_no);

    memcpy(&data->port_state.port_mode, mode, sizeof(phy25g_port_mode_t));
    switch (mode->speed_oper_mode) {
    case LAN80XX_PHY_1G_MODE:
        data->port_state.speed = SPEED_1G;
        break;
    case LAN80XX_PHY_10G_LAN_MODE:
    case LAN80XX_PHY_10G_LAN_SYNC_MODE:
        data->port_state.speed = SPEED_10G;
        break;
    case LAN80XX_PHY_25G_LAN_MODE:
    case LAN80XX_PHY_25G_LAN_SYNC_MODE:
        data->port_state.speed = SPEED_25G;
        break;
    default:
        data->port_state.speed = SPEED_NONE;
        break;
    }
    return rc;
}

mepa_rc lan80xx_reset_point(mepa_device_t *dev, const mepa_reset_param_t *rst_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u32 val = 0;
    switch (rst_conf->reset_point) {
    case MEPA_RESET_POINT_PRE:
        /* Identify and store the Phy id */
        MEPA_RC(lan80xx_identify_phy(dev, data->port_no));

        base_data->chip_ports[base_data->port_cnt] = data->port_no;
        base_data->other_port_dev[base_data->port_cnt] = dev;
        base_data->port_cnt++;

        if (data->port_no != base_data->port_no) {
            return MEPA_RC_OK;
        }
        base_data->post1_passed = 1; /* Set POST1 Pass Variable as 1 */

        if (lan80xx_sku_port_cnt(dev) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Error in getting Port Count of SKU on Port : %d\n", data->port_no);
            return MEPA_RC_ERROR;
        }

        /* Following Resets and MCU Configurations are done only for Base Port of the PHY */
        if (lan80xx_block_reset_priv(dev) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in Getting PHY status");
            return MEPA_RC_ERROR;
        }
        if (lan80xx_a0_a1_revision_serd_init_strap_wrkrd(dev, data->port_no) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Failed to configure Strap over-ride register\n");
            return MEPA_RC_ERROR;
        }

        if (lan80xx_feature_supported(dev) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\nError in reading feature supported");
            return MEPA_RC_ERROR;
        }

        if (lan80xx_mcu_mailbox_init_priv(dev, MAILBOX_INTR_ENABLE, MAILBOX_HOST_INTR_MASK) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Mailbox init failed");
            return MEPA_RC_ERROR;
        }
        if (lan80xx_glb_workarround(dev, data->port_no)) {
            T_E(MEPA_TRACE_GRP_GEN, "Configured Global Workarrounds for A0,A1\n");
            return MEPA_RC_ERROR;
        }
        base_data->reset_done = TRUE;
        break;
    case MEPA_RESET_POINT_DEFAULT:

        if (lan80xx_channel_workarround(dev, data->port_no)) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in Configuring Per Channel Workarrounds \n");
            return MEPA_RC_ERROR;
        }

        /* Read Strap */
        LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &val);
        if ((base_data->port_cnt == base_data->max_port_cnt) && (val & DFU_STRAP)) {
            if (lan80xx_fw_update_priv(dev) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "Firware Update Failed on Port %d \n", base_data->port_no);
                return MEPA_RC_ERROR;
            }
        } else if ((base_data->port_cnt == base_data->max_port_cnt) && (val & SERDES_INIT_STRAP)) {
            if (lan80xx_post1_init_priv(dev, data->port_no) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "POST1 Failed on Port %d \n", data->port_no);
                return MEPA_RC_ERROR;
            }
        }
        break;
    case MEPA_RESET_POINT_POST:
        if (base_data->port_cnt != base_data->max_port_cnt) {
            return MEPA_RC_OK;
        }
        MEPA_MSLEEP(10);
        if (lan80xx_check_mcu_rdy_priv(dev) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "MCU boot up failed");
            return MEPA_RC_ERROR;
        }
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, " Reset Point Not Supported on port : %d \n", data->port_no);
        return MEPA_RC_ERROR;
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_mail_box_command_set(mepa_device_t *dev, uint8_t u8PacketId, uint16_t u16CmdParamLen,
                                            uint8_t *cmd_parm)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "KR Configuring on port : %d\n", data->port_no);
    u32 pkt_len = 0;
    u16 payload_len = 0;
    u8 status = 0;
    u8 aby_cmd_buffer[32] = { 0 };
    u8 resp_buffer[1024] = { 0 };
    pkt_len = lan80xx_CreatePacket(u8PacketId, u16CmdParamLen, aby_cmd_buffer, cmd_parm, RESERVED_ID);

    status = lan80xx_MB_SendRequest(dev, aby_cmd_buffer, pkt_len);
    if (status != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Mailbox send command failed : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    /*Read response from Mailbox area into response buffer*/
    status = lan80xx_MB_ReadResponse(dev, resp_buffer, &payload_len, MAILBOX_INTR_TIMEOUT);
    if (status != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Mailbox read response failed : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    if (lan80xx_ValidatePacket(resp_buffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "CRC check failed : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&resp_buffer[0];
    u8 *pbyPayload = NULL;
    pbyPayload = &resp_buffer[4];
    if (recvPkt->u8PktId == u8PacketId + 0x80) {
        T_D(MEPA_TRACE_GRP_GEN, "Mailbox command %d Enable success port_no %d", u8PacketId, data->port_no);
        return MEPA_RC_OK;
    } else {
        if (recvPkt->u8PktId == u8PacketId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd Failed with %d", __FUNCTION__, pbyPayload[0]);
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Packet receive error , Expected error code : %2x , Received Error code : %2x", __FUNCTION__, u8PacketId + 0x80, recvPkt->u8PktId);
        }
        return MEPA_RC_ERROR;
    }


}

/* Aneg Adevertisement command formate expected by Firware
 * BIT0  : 10G FEC Request
 * BIT1  : 10G FEC Ability
 * BIT2  : 25G R-FEC Request
 * BIT3  : 25G RS-FEC Request
 * BIT4  : 1G fdx Advertise
 * BIT5  : 10G fdx Advertise
 * BIT6  : 25G KR-S Advertise
 * BIT7  : 25G KR Advertise
 * BIT8  : Next page Enable
 * BIT9  : Next page 25G KR
 * BIT10 : Next page 25G CR
 * BIT11 : Next page R-FEC
 * BIT12 : Next page RS-FEC
 * BIT18 : Bypass KR Training
*/
mepa_rc lan80xx_kr_aneg_enable(mepa_device_t *dev, mepa_port_no_t port_no, const mepa_conf_t *const config)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Clause 73: Aneg KR Configuring on port : %d\n", port_no);
    u32 conf_info = 0;
    u8 cmd_param[7] = { 0 };

    /* MAILBOX Packet Create */
    conf_info = (config->conf_25g.base_r_10gfec        << 0 |
                 config->conf_25g.base_r_10gfec        << 1 |
                 config->conf_25g.base_r_25gfec        << 2 |
                 config->conf_25g.rs_fec_25g           << 3 |
                 config->aneg.speed_1g_fdx             << 4 |
                 config->aneg.speed_10g_fdx            << 5 |
                 config->aneg.speed_25g_kr_s_fdx       << 6 |
                 config->aneg.speed_25g_fdx            << 7 |
                 config->aneg.next_page_enable         << 8 |
                 config->aneg.next_page_enable         << 9 |
                 config->aneg.next_page_enable         << 10 |
                 config->conf_25g.np_rs_fec            << 11 |
                 config->conf_25g.np_base_r_fec        << 12 |
                 !(config->conf_25g.kr_train_enable)   << 18) ;

    switch (config->aneg.advertise_dir) {
    case MEPA_ADV_SIDE_LINE:
        cmd_param[0] = (1 << data->channel_id);
        break;
    case MEPA_ADV_SIDE_HOST:
        cmd_param[0] = (1 << (data->channel_id + 4));
        break;
    case MEPA_ADV_SIDE_HOST_LINE:
        cmd_param[0] = (1 << data->channel_id) | (1 << (data->channel_id + 4));
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "\nAneg Ability Direction not selected on Port : %d\n", port_no);
        return MEPA_RC_ERROR;
    }
    cmd_param[1] = (conf_info) & 0xFF;
    cmd_param[2] = (conf_info >> 8) & 0xFF;
    cmd_param[3] = (conf_info >> 16) & 0xFF;
    cmd_param[4] = (conf_info >> 24) & 0xFF;

    T_D(MEPA_TRACE_GRP_GEN, "\n Port : %d, cmd_param[1] : 0x%x, cmd_param[2] : 0x%x, cmd_param[3] : 0x%x, cmd_param[4] : 0x%x\n", port_no, cmd_param[1], cmd_param[2], cmd_param[3], cmd_param[4]);
    if (lan80xx_mail_box_command_set(dev, eSET_PORT_ANEGKR_CFG, 5, &cmd_param[0]) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Error in config aneg set on Port %d\n", port_no);
        return MEPA_RC_OK;
    }

    if (lan80xx_mail_box_command_set(dev, eANEGKR_ENABLE, 1, &cmd_param[0]) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Error in Enabling Aneg on Port %d\n", port_no);
        return MEPA_RC_OK;
    }

    if (config->aneg.no_restart_aneg) {
        return MEPA_RC_OK;
    }
    if (lan80xx_mail_box_command_set(dev, ePORT_RESTART_ANEG, 1, &cmd_param[0]) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Error in Restarting ANEG on Port %d\n", port_no);
        return MEPA_RC_OK;
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_pcs_pma_status_get_priv(const mepa_device_t    *dev,
                                               const mepa_port_no_t   port_no,
                                               phy25g_status_t        *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value = 0, state = 0;
    memset(status, 0, sizeof(phy25g_status_t));
    phy25g_oper_speed_mode_t phy_speed;
    mepa_bool_t line_lp_enabled = 0;
    u8 xmit_mode = 0;
    u8 line_xmit_mode = 0, host_xmit_mode = 0;

    /* When H3P or H3M Loopback is Enabled Line side Rx Link Goes down, eliminating LINE Side link
     * check in poll when H3M or H3P loopback is enabled, so traffic can be forwared from HOST */
    if (data->port_state.loopback_conf.h3p_lp || data->port_state.loopback_conf.h3m_lp) {
        line_lp_enabled = 1;
    }

    //Line PMA status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PMA_PMA_PMD_STATUS_1, &value);
    status->pma.rx_link = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_1_PMA_LINK);
    status->pma.link_down = !(LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_1_PMA_LINK));
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PMA_PMA_PMD_STATUS_2, &value);
    status->pma.rx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT);
    status->pma.tx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT);

    //HOST PCS25G status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS25G_STATUS1, &value);
    status->host_pcs25g.rx_link = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS25G_STATUS1_PCS_RECEIVE_LINK);
    status->host_pcs25g.link_down = !(LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS25G_STATUS1_PCS_RECEIVE_LINK));
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS25G_STATUS2, &value);
    status->host_pcs25g.rx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS25G_STATUS2_RECEIVE_FAULT);
    status->host_pcs25g.tx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS25G_STATUS2_TRANSMIT_FAULT);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_STATUS, &value);
    status->host_pcs25g.hi_ber = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_HI_BER);

    //LINE PCS25G status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS25G_STATUS1, &value);
    status->line_pcs25g.rx_link = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS25G_STATUS1_PCS_RECEIVE_LINK);
    status->line_pcs25g.link_down = !(LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS25G_STATUS1_PCS_RECEIVE_LINK));
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS25G_STATUS2, &value);
    status->line_pcs25g.rx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS25G_STATUS2_RECEIVE_FAULT);
    status->line_pcs25g.tx_fault = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS25G_STATUS2_TRANSMIT_FAULT);


    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_STATUS, &value);
    status->line_pcs25g.hi_ber = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS_CFG_PCS25G_STATUS_HI_BER);

    //LINE PCS1G Status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS1G_LINK_STATUS, &value);
    status->line_pcs1g.link_status = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS_CFG_PCS1G_LINK_STATUS_LINK_STATUS);
    status->line_pcs1g.sync_status = LAN80XX_IS_BITSET(value, LAN80XX_M_LINE_PCS_CFG_PCS1G_LINK_STATUS_SYNC_STATUS);
    line_xmit_mode = LAN80XX_X_LINE_PCS_CFG_PCS1G_LINK_STATUS_XMIT_MODE(value);

    if (line_xmit_mode != LAN80XX_PCS1G_XMIT_DATA_MODE) {
        status->line_pcs1g.link_status = 0;
    }

    //HOST PCS1G Status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS1G_LINK_STATUS, &value);
    status->host_pcs1g.link_status = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_LINK_STATUS);
    status->host_pcs1g.sync_status = LAN80XX_IS_BITSET(value, LAN80XX_M_HOST_PCS_CFG_PCS1G_LINK_STATUS_SYNC_STATUS);
    host_xmit_mode = LAN80XX_X_HOST_PCS_CFG_PCS1G_LINK_STATUS_XMIT_MODE(value);

    if (host_xmit_mode != LAN80XX_PCS1G_XMIT_DATA_MODE) {
        status->host_pcs1g.link_status = 0;
    }


    /* SW Workarround for Clause37 RTL Bug
     * As per Clause-37 Auto-Negotiation when the HCD of Link partner is not matching with advertised abilities then its RTL
     * responsiblity to send IDLE signals by changing XMIT_MODE to IDLE and clear LINK_STATUS, but in LAN80XX PHYs the LINK_STATUS
     * bit is not cleared even the LP Abilties are not matched with advertised abilities by XMIT_MODE is changed to IDLE mode
     */
    if ((line_xmit_mode == LAN80XX_PCS1G_XMIT_DATA_MODE) && (host_xmit_mode == LAN80XX_PCS1G_XMIT_DATA_MODE)) {
        xmit_mode = 1;
    }

    //Check RS-FEC status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_RSFEC_CFG, &value);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS25G_STATUS, &state);

    //RS-FEC enabled then check for Align done bit
    if (value & LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA) {
        status->lpcs25g_block_lock = LAN80XX_IS_BITSET(state, LAN80XX_M_LINE_PCS_CFG_PCS25G_STATUS_ALIGN_DONE);
    } else {
        status->lpcs25g_block_lock = LAN80XX_IS_BITSET(state, LAN80XX_M_LINE_PCS_CFG_PCS25G_STATUS_BLOCK_LOCK);
    }

    //Check RS-FEC status
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_RSFEC_CFG, &value);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS25G_STATUS, &state);

    //RS-FEC enabled then check for Align done bit
    if (value & LAN80XX_M_HOST_PCS_CFG_PCS25G_RSFEC_CFG_FEC91_ENA) {
        status->hpcs25g_block_lock = LAN80XX_IS_BITSET(state, LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_ALIGN_DONE);
    } else {
        status->hpcs25g_block_lock = LAN80XX_IS_BITSET(state, LAN80XX_M_HOST_PCS_CFG_PCS25G_STATUS_BLOCK_LOCK);
    }

    if (data->conf.speed == MESA_SPEED_AUTO) {
        MEPA_RC(lan80xx_aneg_status(dev, port_no));
        data->port_state.speed = data->line_aneg_status.neg_speed;
    }
    phy_speed = data->port_state.speed;
    switch (phy_speed) {
    case SPEED_1G :
        if (line_lp_enabled) {
            status->phy_status = (status->host_pcs1g.link_status) ? TRUE : FALSE;
        } else {
            status->phy_status = (status->pma.rx_link && status->line_pcs1g.link_status && status->host_pcs1g.link_status &&
                                  xmit_mode) ? TRUE : FALSE;
        }
        break;
    case SPEED_10G:
    case SPEED_25G:
        if (line_lp_enabled) {
            status->phy_status = (status->host_pcs25g.rx_link) ? TRUE : FALSE;
        } else {
            status->phy_status = (status->pma.rx_link && status->line_pcs25g.rx_link && status->host_pcs25g.rx_link) ? TRUE : FALSE;
        }
        break;
    default:
        status->phy_status = 0;
        break;
    }

    return MEPA_RC_OK;
}

/* Gives the status of all sublayers of PHY and status of PHY*/
mepa_rc lan80xx_status_get_priv(const mepa_device_t   *dev,
                                const mepa_port_no_t port_no,
                                phy25g_status_t       *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    rc = LAN80XX_RC_COLD(lan80xx_pcs_pma_status_get_priv(dev, port_no, status));
    status->oper_mode = data->port_state.port_mode.oper_mode;
    status->host_neg_speed = data->host_aneg_status.neg_speed;
    status->line_neg_speed = data->line_aneg_status.neg_speed;
    return rc;
}

mepa_rc lan80xx_warmrestart_conf_get_priv(mepa_device_t *dev)
{

    uint32_t val = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev = (mepa_device_t *)data->base_dev;
    phy25g_phy_state_t *base_data = (phy25g_phy_state_t *)base_dev->data;

    LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_GLOBAL_WARM_RESTART_REG(data->channel_id), &val);
    data->restart_cur = LAN80XX_X_GLOBAL_WARM_RESTART_REG_WARM_RESTART(val);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_restart_type_set(mepa_device_t *dev)
{

    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev = (mepa_device_t *)data->base_dev;
    phy25g_phy_state_t *base_data = (phy25g_phy_state_t *)base_dev->data;

    /* Set restart information in Malibu25G PHY */
    LAN80XX_CSR_WARM_WRM(base_data->port_no, LAN80XX_GLOBAL_WARM_RESTART_REG(data->channel_id),
                         LAN80XX_F_GLOBAL_WARM_RESTART_REG_WARM_RESTART(data->restart_cur),
                         LAN80XX_M_GLOBAL_WARM_RESTART_REG_WARM_RESTART);
    return rc;
}

mepa_rc lan80xx_prbs_generator_conf_set(mepa_device_t *dev, mepa_bool_t enable, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                        const mepa_phy_prbs_generator_conf_t *const prbs_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_port_no_t port_no = data->port_no;
    u16 speed = data->port_state.speed;
    uint32_t value = 0;
    uint32_t address = 0;
    mepa_bool_t is_line = (direction == MEPA_PHY_DIRECTION_LINE) ? TRUE : FALSE;

    if (type == MEPA_PHY_PRBS_TYPE_SERDES) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

        /* BIST Disable */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_33),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_33_LN_R_BIST_EN(0)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_33_LN_R_BIST_EN));

        if (enable == 0) {
            if (is_line) {
                data->line_prbs_conf = *prbs_conf;
            } else {
                data->host_prbs_conf = *prbs_conf;
            }
            return MEPA_RC_OK;
        }

        /* BIST pattern selection */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_33),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_33_LN_R_BIST_MODE_2_0(prbs_conf->prbsn_sel)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_33_LN_R_BIST_MODE_2_0));

        if (prbs_conf->prbsn_sel == MEPA_USER_DEFINED_PATTERN) {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0xFF); /* Select CMU */

            ioreg_blk *io = LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_21);
            address = io->addr;
            for (u8 i = 0; i < 8; i++) {
                MEPA_RC(lan80xx_csr_wr(dev, port_no, io->mmd, io->is32, address, prbs_conf->user_pattern[i]));
                address++;
            }
        }
        if (is_line) {

            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_LINE_SD25G_RESET,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST);

            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_LINE_SD25G_RESET,
                            0,
                            LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_HOST_SD25G_RESET,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST);

            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_HOST_SD25G_RESET,
                            0,
                            LAN80XX_M_HOST_SLICE_HOST_SD25G_RESET_HOST_SD25G_MACRO_RST);
        }

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_34),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_FREE_RUN_MODE),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_FREE_RUN_MODE));

        /* BIST enable */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_33),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_33_LN_R_BIST_EN(enable)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_33_LN_R_BIST_EN));

        if (is_line) {
            data->line_prbs_conf = *prbs_conf;
        } else {
            data->host_prbs_conf = *prbs_conf;
        }

        //Read BIST result register
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E0), &value);

        if (value & (LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_OK)) {
            T_I(MEPA_TRACE_GRP_GEN, "Bist Run OK\n");
            return MEPA_RC_OK;
        }
        T_I(MEPA_TRACE_GRP_GEN, "Bist Run Not OK\n");

    } else if (type == MEPA_PHY_PRBS_TYPE_PCS) {

        if (prbs_conf->prbsn_sel == MEPA_PCS_SCRAMBLED_TEST_PATTERN && speed != SPEED_25G) {
            T_E(MEPA_TRACE_GRP_GEN, "\nScrambled Test pattern can be generated only when link speed is 25G\n");
            return MEPA_RC_ERROR;
        }
        if (prbs_conf->prbsn_sel != MEPA_PCS_SCRAMBLED_TEST_PATTERN && speed != SPEED_10G) {
            T_E(MEPA_TRACE_GRP_GEN, "\nThe configured test pattern can be generated only when link speed is 10G\n");
            return MEPA_RC_ERROR;
        }

        switch (prbs_conf->prbsn_sel) {
        case MEPA_PCS_SQAURE_PATTERN:
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_CONTROL),
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_SELECT_SQUARE) |
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_TX_TESTPATTERN));

            break;
        case MEPA_PCS_LOCAL_FAULT_SEQ:
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_CONTROL),
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_TX_TESTPATTERN));

            break;
        case MEPA_PCS_ZERO_SEQ:
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_CONTROL),
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_DATA_PATTERN_SEL) |
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_TX_TESTPATTERN));
            break;
        case MEPA_PCS_SCRAMBLED_TEST_PATTERN:
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_CONTROL),
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_SCRAMBLED_IDLE) |
                           LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_TX_TESTPATTERN));
            break;
        default:
            T_E(MEPA_TRACE_GRP_GEN, "\n PCS PRBS not support selected PRBS Pattern \n");
            break;
        }
        if (is_line) {
            data->line_pcs_prbs_conf = *prbs_conf;
        } else {
            data->host_pcs_prbs_conf = *prbs_conf;
        }

    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_prbs_monitor_conf_set(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                      const mepa_phy_prbs_monitor_conf_t *const conf_value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_port_no_t port_no = data->port_no;
    uint32_t value = 0;
    mepa_bool_t is_line = (direction == MEPA_PHY_DIRECTION_LINE) ? TRUE : FALSE;

    if (type == MEPA_PHY_PRBS_TYPE_SERDES) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

        if (conf_value->bist_check_zero) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E0), &value);

            if (!(value & LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_OK)) {
                T_E(MEPA_TRACE_GRP_GEN, "\n Check Zero can be Set only if Bist Ok bit is Set \n");
                return MEPA_RC_ERROR;
            }
        }
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_34),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK(0)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK));

        /* bist_err will assert if rx all zero data in PRBS mode */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_34),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK_ZERO(conf_value->bist_check_zero)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK_ZERO));

        /* bist_err counter will stop when reaching 0xffff_ffff if error_counter_saturation is set */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_34),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_34_LN_R_BIST_ERRSTOP(conf_value->bist_error_stop)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_BIST_ERRSTOP));

        /*  BIST error injection enable */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_33),
                             (conf_value->no_of_errors == 0) ? 0 : LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_33_LN_R_BIST_ERRINJEC),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_33_LN_R_BIST_ERRINJEC));

        /* PRBS Checker Enable */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_34),
                             LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK(conf_value->enable)),
                             LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_34_LN_R_BIST_CHK));

    } else if (type == MEPA_PHY_PRBS_TYPE_PCS) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_CONTROL),
                        LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PCS25G_BASER_TEST_CONTROL_RX_TESTPATTERN(conf_value->enable)),
                        LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PCS25G_BASER_TEST_CONTROL_RX_TESTPATTERN));
    }
    if (is_line) {
        data->line_prbs_mon_conf = *conf_value;
    } else {
        data->host_prbs_mon_conf = *conf_value;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_prbs_monitor_status_get(mepa_device_t *dev, mepa_phy_prbs_type_t type, mepa_phy_prbs_direction_t direction,
                                        mepa_phy_prbs_monitor_conf_t *const mon_status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_port_no_t port_no = data->port_no;
    uint32_t read_value = 0;
    mepa_bool_t is_line = (direction == MEPA_PHY_DIRECTION_LINE) ? TRUE : FALSE;
    if (is_line) {
        memcpy(mon_status, &data->line_prbs_mon_conf, sizeof(mepa_phy_prbs_monitor_conf_t));
    } else {
        memcpy(mon_status, &data->host_prbs_mon_conf, sizeof(mepa_phy_prbs_monitor_conf_t));
    }
    if (!mon_status->enable) {
        memset(mon_status, 0, sizeof(mepa_phy_prbs_monitor_conf_t));
        return MEPA_RC_OK;
    }

    if (type == MEPA_PHY_PRBS_TYPE_SERDES) {

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E0), &read_value);

        mon_status->active       = (read_value & LAN80XX_BIT(0)) ? TRUE : FALSE;
        mon_status->bist_status  = (read_value & LAN80XX_BIT(1)) ? TRUE : FALSE;
        mon_status->error_status = (read_value & LAN80XX_BIT(2)) ? TRUE : FALSE;
        mon_status->incomplete   = (read_value & LAN80XX_BIT(3)) ? TRUE : FALSE;

        //BIST Error counter
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E4), &read_value);
        mon_status->bist_error_count = read_value << LAN80XX_24_BIT_SHIFT;

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E3), &read_value);
        mon_status->bist_error_count |= read_value << LAN80XX_16_BIT_SHIFT;

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E2), &read_value);
        mon_status->bist_error_count |= read_value << LAN80XX_8_BIT_SHIFT;

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_E1), &read_value);
        mon_status->bist_error_count |= read_value;
    } else if (type == MEPA_PHY_PRBS_TYPE_PCS) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PCS25G_BASER_TEST_ERR_CNT), &read_value);
        mon_status->bist_error_count = (read_value & 0xFFFF);
        T_I(MEPA_TRACE_GRP_GEN, "PCS Error counter : %d", mon_status->bist_error_count);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_pkt_gen_conf_priv(const mepa_device_t    *dev,
                                  const mepa_port_no_t   port_no,
                                  const phy25g_pkt_gen_conf_t  *const conf)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u16 tmac = 0, ts = 0;
    u32 msg_type_spec_msb, msg_type_spec_lsb;
    msg_type_spec_lsb = (conf->message_type_spec) & 0xFFFF;
    msg_type_spec_msb = ((conf->message_type_spec) >> LAN80XX_16_BIT_SHIFT) & 0xFFFF;
    ts = (conf->ptp_ts_sec) << LAN80XX_8_BIT_SHIFT;
    ts = ts | conf-> ptp_ts_ns;

    if (conf->enable == FALSE) {

        /* Datapath selection */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_DATAPATH_CONTROL, 0, LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL |
                        LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, 0x0,
                        LAN80XX_M_PKT_BIST_GEN_CFG_SRATE |
                        LAN80XX_M_PKT_BIST_GEN_CFG_SINGLE |
                        LAN80XX_M_PKT_BIST_GEN_CFG_IDLES |
                        LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE |
                        LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE);

        T_I(MEPA_TRACE_GRP_GEN, "Packet Generator Disabled on Port : %d\n", port_no);
        return MEPA_RC_OK;
    }

    /* Resetting PKT_BIST Register Before Config */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, 0x0,
                    LAN80XX_M_PKT_BIST_GEN_CFG_SRATE |
                    LAN80XX_M_PKT_BIST_GEN_CFG_SINGLE |
                    LAN80XX_M_PKT_BIST_GEN_CFG_IDLES |
                    LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE |
                    LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE);

    /* Idles */
    if (conf->frames == FALSE) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, LAN80XX_M_PKT_BIST_GEN_CFG_IDLES | LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE,
                        LAN80XX_M_PKT_BIST_GEN_CFG_IDLES | LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE);

        return MEPA_RC_OK;
    }

    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, conf->frame_single ? LAN80XX_M_PKT_BIST_GEN_CFG_IDLES : 0, LAN80XX_M_PKT_BIST_GEN_CFG_IDLES);

    if (conf->ptp == FALSE) {

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_MINOR_VERSION, 0x0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID, 0x0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_MINOR_SDOID, 0x0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI, 0x0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO, 0x0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, 0, LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE);
        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_TIME, LAN80XX_F_PKT_BIST_GEN_TIME_PTPTIME(0), LAN80XX_M_PKT_BIST_GEN_TIME_PTPTIME);
    } else {

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_MINOR_VERSION,
                        conf->is_v2_1 ? LAN80XX_F_PKT_BIST_MINOR_VERSION_MINOR_VERSION(1) : 0,
                        LAN80XX_M_PKT_BIST_MINOR_VERSION_MINOR_VERSION);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID,
                        conf->is_v2_1 ? LAN80XX_F_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID_TRANSPORT_SPECIFIC_MAJOR_SDOID(conf->trans_spec_majorSid) : 0,
                        LAN80XX_M_PKT_BIST_TRANSPORT_SPECIFIC_MAJOR_SDOID_TRANSPORT_SPECIFIC_MAJOR_SDOID);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_MINOR_SDOID,
                        conf->is_v2_1 ? LAN80XX_F_PKT_BIST_MINOR_SDOID_MINOR_SDOID(conf->minorSid) : 0,
                        LAN80XX_M_PKT_BIST_MINOR_SDOID_MINOR_SDOID);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI,
                        conf->is_v2_1 ? LAN80XX_F_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI_MESSAGE_TYPE_SPECIFIC_HI(msg_type_spec_msb) : 0,
                        LAN80XX_M_PKT_BIST_MESSAGE_TYPE_SPECIFIC_HI_MESSAGE_TYPE_SPECIFIC_HI);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO,
                        conf->is_v2_1 ? LAN80XX_F_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO_MESSAGE_TYPE_SPECIFIC_LO(msg_type_spec_lsb) : 0,
                        LAN80XX_M_PKT_BIST_MESSAGE_TYPE_SPECIFIC_LO_MESSAGE_TYPE_SPECIFIC_LO);

        /* PTP Seconds, Nanoseconds field Configuration */
        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_TIME, LAN80XX_F_PKT_BIST_GEN_TIME_PTPTIME(ts), LAN80XX_M_PKT_BIST_GEN_TIME_PTPTIME);

        /* Number of Standard Frames between PTP Packets */
        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, LAN80XX_F_PKT_BIST_GEN_CFG_SRATE(conf->srate), LAN80XX_M_PKT_BIST_GEN_CFG_SRATE);

        // PTP Enable
        LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE, LAN80XX_M_PKT_BIST_GEN_CFG_PTP_ENABLE);

    }

    /* Ethype conf */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_ETYPE, LAN80XX_F_PKT_BIST_GEN_ETYPE_ETYPE(conf->etype), LAN80XX_M_PKT_BIST_GEN_ETYPE_ETYPE);

    /* SMAC Configuration */
    tmac = LAN80XX_WORD(conf->smac.addr[4], conf->smac.addr[5]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_SA0, LAN80XX_F_PKT_BIST_GEN_SA0_SA0(tmac), LAN80XX_M_PKT_BIST_GEN_SA0_SA0);

    tmac = LAN80XX_WORD(conf->smac.addr[2], conf->smac.addr[3]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_SA1, LAN80XX_F_PKT_BIST_GEN_SA1_SA1(tmac), LAN80XX_M_PKT_BIST_GEN_SA1_SA1);

    tmac = LAN80XX_WORD(conf->smac.addr[0], conf->smac.addr[1]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_SA2, LAN80XX_F_PKT_BIST_GEN_SA2_SA2(tmac | conf->smac.addr[1]), LAN80XX_M_PKT_BIST_GEN_SA2_SA2);

    /* DMAC Configuration */
    tmac = LAN80XX_WORD(conf->dmac.addr[4], conf->dmac.addr[5]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_DA0, LAN80XX_F_PKT_BIST_GEN_DA0_DA0(tmac), LAN80XX_M_PKT_BIST_GEN_DA0_DA0);

    tmac = LAN80XX_WORD(conf->dmac.addr[2], conf->dmac.addr[3]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_DA1, LAN80XX_F_PKT_BIST_GEN_DA1_DA1(tmac | conf->dmac.addr[3]), LAN80XX_M_PKT_BIST_GEN_DA1_DA1);

    tmac = LAN80XX_WORD(conf->dmac.addr[0], conf->dmac.addr[1]);
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_DA2, LAN80XX_F_PKT_BIST_GEN_DA2_DA2(tmac | conf->dmac.addr[1]), LAN80XX_M_PKT_BIST_GEN_DA2_DA2);

    /* Packet Length Configuration */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_PKTLEN, LAN80XX_F_PKT_BIST_GEN_PKTLEN_PKTLEN(conf->pkt_len), LAN80XX_M_PKT_BIST_GEN_PKTLEN_PKTLEN);

    /* Inter packet gap */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_IPGLEN_LSW, LAN80XX_F_PKT_BIST_GEN_IPGLEN_LSW_IPGLEN_LSW((conf->ipg_len)& LAN80XX_BYTE_MASK),
                    LAN80XX_M_PKT_BIST_GEN_IPGLEN_LSW_IPGLEN_LSW);

    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_IPGLEN_MSW, LAN80XX_F_PKT_BIST_GEN_IPGLEN_MSW_IPGLEN_MSW(((conf->ipg_len) >> LAN80XX_16_BIT_SHIFT)&LAN80XX_BYTE_MASK),
                    LAN80XX_M_PKT_BIST_GEN_IPGLEN_MSW_IPGLEN_MSW);

    /* Enable Packet Generation */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE, LAN80XX_M_PKT_BIST_GEN_CFG_ENABLE);

    /* Datapath selection */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_DATAPATH_CONTROL,
                    conf->ingress == TRUE ? LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL : LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL,
                    conf->ingress == TRUE ? LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL : LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_EGR_XGMII_PG_SEL);

    /* Single Frame or Continuous Frame */
    LAN80XX_CSR_WRM(port_no, LAN80XX_PKT_BIST_GEN_CFG, conf->frame_single ? LAN80XX_M_PKT_BIST_GEN_CFG_SINGLE : 0, LAN80XX_M_PKT_BIST_GEN_CFG_SINGLE);

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_timestamp_read (const mepa_device_t     *dev,
                                           const mepa_port_no_t    port_no,
                                           phy25g_timestamp_val_t  *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // reading all the timestamp registers.
    u32 rd_var;
    u8 timestamp = 0, size = 0;
    ioreg_blk *io = LAN80XX_PKT_BIST_MON_TSTAMP0_0;
    u32 address = io->addr;

    /* Freeze most recent 10 timestamps for readback */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_UPDATE, LAN80XX_M_PKT_BIST_UPDATE_TS_HOLD, LAN80XX_M_PKT_BIST_UPDATE_TS_HOLD);
    /*Read 10 timestamp where each time stamp is of 80 bits(5 registers each 16bit register) */
    for (timestamp = 0; timestamp < 10; timestamp++) {
        for (size = 0 ; size < 5; size ++) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, MMD_ID_PKT_BIST, 0, address, &rd_var));
            conf->timestamp[timestamp][size] = rd_var;
            address++;
        }
    }
    /* Unfreeze the Timestamp counters */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_UPDATE, 0, LAN80XX_M_PKT_BIST_UPDATE_TS_HOLD);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_pkt_mon_conf_priv(const mepa_device_t   *dev,
                                  const mepa_port_no_t  port_no,
                                  mepa_bool_t           mon_enable,
                                  phy25g_pkt_mon_rst_t  reset_cnt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (mon_enable == TRUE) {
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_MON_CFG, LAN80XX_M_PKT_BIST_MON_CFG_ENABLE, LAN80XX_M_PKT_BIST_MON_CFG_ENABLE);
    } else {
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_MON_CFG, 0, LAN80XX_M_PKT_BIST_MON_CFG_ENABLE);
    }
    /* Reset the Counters */
    if (reset_cnt == LAN80XX_PKT_MON_RST_NONE) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_PKT_BIST_MON_RST, 0x0);
    } else {
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_MON_RST, LAN80XX_BIT(reset_cnt), LAN80XX_BIT(reset_cnt));
    }
    data->pkt_bist_mon_ena = mon_enable;
    data->pkt_bist_reset = reset_cnt;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_pkt_mon_get_priv(const mepa_device_t   *dev,
                                 const mepa_port_no_t  port_no,
                                 mepa_bool_t           *const mon_enable,
                                 phy25g_pkt_mon_rst_t  *const reset_cnt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *mon_enable = data->pkt_bist_mon_ena;
    *reset_cnt = data->pkt_bist_reset;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_pkt_mon_counters_get_priv(const mepa_device_t        *dev,
                                          const mepa_port_no_t       port_no,
                                          mepa_bool_t                ts_rd,
                                          phy25g_pkt_mon_counters_t  *const pkt_counters,
                                          phy25g_timestamp_val_t     *const ts_packet)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    u32 rd_var = 0;
    memset(ts_packet, 0, sizeof(phy25g_timestamp_val_t));
    /* Freeze all generator and monitor counters for readback */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_UPDATE, LAN80XX_M_PKT_BIST_UPDATE_CNTR_UPDATE, LAN80XX_M_PKT_BIST_UPDATE_CNTR_UPDATE);

    /* Reading all the monitor counters */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_GOOD_LSW, &rd_var);
    pkt_counters->good_crc = rd_var;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_GOOD_MSW, &rd_var);
    pkt_counters->good_crc |= rd_var << LAN80XX_16_BIT_SHIFT;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_BAD_LSW, &rd_var);
    pkt_counters->bad_crc = rd_var;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_BAD_MSW, &rd_var);
    pkt_counters->bad_crc |= rd_var << LAN80XX_16_BIT_SHIFT;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_FRAG_LSW, &rd_var);
    pkt_counters->fragmented = rd_var;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_FRAG_MSW, &rd_var);
    pkt_counters->fragmented |= rd_var << LAN80XX_16_BIT_SHIFT;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_LFAULT_LSW, &rd_var);
    pkt_counters->lfault = rd_var;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_LFAULT_MSW, &rd_var);
    pkt_counters->lfault |= rd_var << LAN80XX_16_BIT_SHIFT;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_BER_LSW, &rd_var);
    pkt_counters->ber = rd_var;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PKT_BIST_MON_BER_MSW, &rd_var);
    pkt_counters->ber |= rd_var << LAN80XX_16_BIT_SHIFT;

    if (ts_rd == TRUE) {
        rc = lan80xx_phy_timestamp_read(dev, port_no, ts_packet);
    }

    /* Unfreeze the monitor counters */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_PKT_BIST_UPDATE, 0, LAN80XX_M_PKT_BIST_UPDATE_CNTR_UPDATE);

    return rc;
}

static mepa_rc lan80xx_rx_eye_scan_disable(const mepa_device_t     *dev,
                                           const  mepa_port_no_t    port_no,
                                           mepa_bool_t              is_line)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_eye_backup_t eye_reg_val;
    eye_reg_val = data->port_state.eye_reg_backup;

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C),
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(eye_reg_val.dfe_pd)) |
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD(eye_reg_val.dfedmx_pd)),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFE_PD) |
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18),
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(eye_reg_val.erramp_pd)),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E),
                    LAN80XX_HOST_LINE_REG(LAN80XX_F, is_line, PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(eye_reg_val.dfedig)),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG));

    /* Disabling Eye Scan */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_19), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_28), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_2E), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN));

    T_I(MEPA_TRACE_GRP_GEN, "\n Eye Scan Disabled on Port %d \n", port_no);

    return MEPA_RC_OK;
}


mepa_rc lan80xx_rx_eye_scan_conf_set_priv (const mepa_device_t          *dev,
                                           const mepa_port_no_t         port_no,
                                           mepa_bool_t                  is_line,
                                           const phy25g_rx_eye_scan_t   conf)

{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value = 0;
    u16 cnt = 0;
    u32 address, vref = 0;
    mepa_bool_t max_vref = FALSE;
    phy25g_rx_eye_scan_status_t   status;
    memset(&status, 0, sizeof(phy25g_rx_eye_scan_status_t));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

    /* Storing the current DFE Configurations */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), &value);
    data->port_state.eye_reg_backup.dfe_pd = LAN80XX_HOST_LINE_REG(LAN80XX_X, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(value));
    data->port_state.eye_reg_backup.dfedmx_pd = LAN80XX_HOST_LINE_REG(LAN80XX_X, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD(value));

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), &value);
    data->port_state.eye_reg_backup.erramp_pd = LAN80XX_HOST_LINE_REG(LAN80XX_X, is_line, PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(value));

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), &value);
    data->port_state.eye_reg_backup.dfedig = LAN80XX_HOST_LINE_REG(LAN80XX_X, is_line, PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(value));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), 0, LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFE_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0D), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1D), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_19), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_2E), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0xFF);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_1A), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_CMU_1A_R_REG_MANUAL),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_CMU_1A_R_REG_MANUAL));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

    /* Enable Eye Scan */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_28),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN));

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN),
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN));

    if (conf == LAN80XX_RX_EYE_FAST_SCAN) {
        /* Fast Scan */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_2E),
                        LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN),
                        LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN));
        cnt = 0;
        while (cnt <= LAN80XX_EYE_SCAN_POLL_DELAY_10MS) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_DD), &value);
            if (value & LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE) {
                break;
            }
            MEPA_MSLEEP(1);
            cnt++;
        }
        if (!(value & LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE)) {
            T_E(MEPA_TRACE_GRP_GEN, "Timed out after %d ms - bailing out", cnt);
            MEPA_RC(lan80xx_rx_eye_scan_disable(dev, port_no, is_line));
            return MEPA_RC_ERROR;
        }
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_D0), &value);
        status.eye_height = value;  /* Eye Height after FAST SCAN */
        memcpy(&data->eye_scan, &status, sizeof(phy25g_rx_eye_scan_status_t));
        rc = lan80xx_rx_eye_scan_disable(dev, port_no, is_line);
        return rc;
    }

    /* Normal Eye Scan */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_2E), 0,
                    LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN));

    while (!max_vref) {
        cnt = 0;
        /* Polling the EYE Scan status bit for 10 ms */
        while (cnt <= LAN80XX_EYE_SCAN_POLL_DELAY_10MS) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_DD), &value);
            if (value & LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE) {
                break;
            }
            MEPA_MSLEEP(1);
            cnt++;
        }
        if (!(value & LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE)) {
            T_E(MEPA_TRACE_GRP_GEN, "Timed out after %d ms - bailing out", cnt);
            MEPA_RC(lan80xx_rx_eye_scan_disable(dev, port_no, is_line));
            return MEPA_RC_ERROR;
        }
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_DA), &vref);
        /* Reading Eye Scan Results from the Register LANE_D0 to LANE_D8*/
        ioreg_blk *io = LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_D0);
        address = io->addr;
        for (u8 i = 0; i <= LAN80XX_EYE_SCAN_RESULT_REG_COUNT; i++) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, io->mmd, io->is32, address, &value));
            value = value & 0xFF;
            if (i == LAN80XX_EYE_SCAN_RESULT_REG_COUNT) {
                status.eye_res_msb[vref] = (value & 1U);
            } else {
                status.eye_res[vref] |= (uint64_t)value << (i * 8U);
            }
            address++;
        }
        if (vref == LAN80XX_EYE_SCAN_MAX_VREF_AMPLITUDE) {
            max_vref = TRUE;
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), 0,
                        LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT));

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT),
                        LAN80XX_HOST_LINE_REG(LAN80XX_M, is_line, PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT));
    }
    status.eye_height = 0;
    memcpy(&data->eye_scan, &status, sizeof(phy25g_rx_eye_scan_status_t));

    /* Restore Settings and Disable Eye Scan */
    rc = lan80xx_rx_eye_scan_disable(dev, port_no, is_line);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Error in Disabling the Eye Scan on Port %d \n", port_no);
    }
    return rc;
}

mepa_rc lan80xx_rx_eye_scan_status_get_priv (const mepa_device_t                *dev,
                                             const mepa_port_no_t               port_no,
                                             const phy25g_rx_eye_scan_t         scan,
                                             phy25g_rx_eye_scan_status_t        *const status)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *status = data->eye_scan;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_dfe_ena_dis(const mepa_device_t  *dev,
                                   const mepa_port_no_t port_no,
                                   mepa_bool_t          is_line,
                                   mepa_bool_t          enable,
                                   mepa_bool_t          man_ena)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 dfe_h1, dfe_h2, dfe_h3, dfe_h4, dfe_h5, dfe_dlev;

    if (enable == 1 && man_ena == 1) {
        T_E(MEPA_TRACE_GRP_GEN, "Both Adaptive and Manual mode of DFE can't be enabled");
        return MEPA_RC_ERROR;
    }
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0D), LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN(enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(!enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0F),
                    LAN80XX_F_LINE_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1(enable ? LAN80XX_DFE_ADAP_TAP_ENABLE : 0),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_18), LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(!enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1D), LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN(enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1D), LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN,
                    LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG(enable),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_15),
                    LAN80XX_F_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0(man_ena ? LAN80XX_DFE_MANUAL_MODE_ENABLE : 0),
                    LAN80XX_M_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0);

    if (man_ena) {
        /* Reading the Current DFE Coefficients */
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CA), &dfe_h1);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CB), &dfe_h2);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CC), &dfe_h3);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CD), &dfe_h4);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CE), &dfe_h5);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CF), &dfe_dlev);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_14), dfe_h1);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_13), dfe_h2);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_12), dfe_h3);
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_11), LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0(dfe_h4),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_11), LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0(dfe_h5),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_10), dfe_dlev);
    }
    return MEPA_RC_OK;
}


mepa_rc lan80xx_phy_tx_rx_equalization_set_priv(const mepa_device_t              *dev,
                                                const mepa_port_no_t             port_no,
                                                mepa_bool_t                      is_line,
                                                const phy25g_tx_rx_equa_conf_t   *const conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_bool_t dfe_rstn = 0;
    u8 ipdriver_base_2_0 = 0, vc_driver_3_0 = 0;
    u32 val = 0;

    if (conf->dfe_man_ena) {
        T_E(MEPA_TRACE_GRP_GEN, "\nDFE Manual Mode is Not Supported on Port : %d\n", port_no);
        return MEPA_RC_ERROR;
    }
    if ((conf->equalizer_conf == LAN80XX_CONF_RX_EQUALIZER) || (conf->equalizer_conf == LAN80XX_CONF_TX_RX_EQUALIZER)) {

        if (conf->rx_vga > LAN80XX_CTLE_VGA_MAX_VAL || conf->rx_ctle_c > LAN80XX_CTLE_C_MAX_VAL || conf->rx_ctle_r > LAN80XX_CTLE_R_MAX_VAL) {
            T_E(MEPA_TRACE_GRP_GEN, "\nInvalid Range of Coeffients (Expected range : vga = (0-31), ctle_c = (0-15), ctle_r = (0-15)\n");
            return MEPA_RC_ERROR;
        }

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x0); /* Select LANE registers */

        /* VGA and CTLE in Manual Mode */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_23), LAN80XX_M_LINE_PMA_8BIT_LANE_23_LN_CFG_VGA_BYP,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_23_LN_CFG_VGA_BYP);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1F), LAN80XX_M_LINE_PMA_8BIT_LANE_1F_LN_CFG_EQR_BYP,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_1F_LN_CFG_EQR_BYP);

        /* VGA */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_21), LAN80XX_F_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(conf->rx_vga),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0);

        /* CTLE C */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0(conf->rx_ctle_c),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0);

        /* CTLE R */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_22), LAN80XX_F_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0(conf->rx_ctle_r),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0);

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_40), &val);

        dfe_rstn =  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN(val);
        /* LANE Reset */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_40), LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_40), LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN(dfe_rstn),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_44), 0, LAN80XX_BIT(6));

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0D), 0, LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), 0, LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), 0, LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), 0, LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD);

        /* Enable or Disable DFE*/
        rc = lan80xx_dfe_ena_dis(dev, port_no, is_line, conf->dfe_adp_ena, conf->dfe_man_ena);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error is Configuring DFE");
            return MEPA_RC_ERROR;
        }
    }
    if ((conf->equalizer_conf == LAN80XX_CONF_TX_EQUALIZER) || (conf->equalizer_conf == LAN80XX_CONF_TX_RX_EQUALIZER)) {

        if (conf->amp_code > LAN80XX_TX_AMP_CODE_MAX_VAL || conf->tx_tap_dly > LAN80XX_TX_TAP_DLY_MAX_VAL || conf->tx_tap_adv > LAN80XX_TX_TAP_ADV_MAX_VAL) {
            T_E(MEPA_TRACE_GRP_GEN, "\nInvalid Range of Coeffients (Expected range : amp_code = (0-102), tap_dly = (0-31), tap_adv = (0-15)\n");
            return MEPA_RC_ERROR;
        }

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x0); /* Select LANE registers */

        /* Tx Amplitude is tuned based on Current and Resistance value where "ipdriver_base_2_0" controls the current flow
         * and  "vc_driver_3_0" controls the Resistance
         */
        if ((conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_16)) {
            ipdriver_base_2_0 = 6;
            vc_driver_3_0 = conf->amp_code - 0;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_16) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_32)) {
            ipdriver_base_2_0 = 5;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_16;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_32) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_46)) {
            ipdriver_base_2_0 = 7;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_32;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_46) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_58)) {
            ipdriver_base_2_0 = 4;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_46;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_58) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_69)) {
            ipdriver_base_2_0 = 3;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_58;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_69) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_79)) {
            ipdriver_base_2_0 = 2;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_69;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_79) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_88)) {
            ipdriver_base_2_0 = 0;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_79;
        } else if ((conf->amp_code >= LAN80XX_TX_AMP_CODE_RANGE_88) & (conf->amp_code < LAN80XX_TX_AMP_CODE_RANGE_102)) {
            ipdriver_base_2_0 = 1;
            vc_driver_3_0 = conf->amp_code - LAN80XX_TX_AMP_CODE_RANGE_88;
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_01),
                        LAN80XX_F_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(ipdriver_base_2_0),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_00), LAN80XX_F_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(vc_driver_3_0),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0);

        /* TX TAP DLY Coefficient */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_03), LAN80XX_F_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0(conf->tx_tap_dly),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0);

        /* TAP ADV Coefficient */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_06), LAN80XX_F_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0(conf->tx_tap_adv),
                        LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0);

        /* Enable TAP ADV */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_07), LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_ADV,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_ADV);

        /* Enable TAP DLY */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_07), LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY);

        /* Enable TAP MAIN */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_04), LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_06), LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN,
                        LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN);

    }
    return MEPA_RC_OK;
}


mepa_rc lan80xx_phy_tx_rx_equalization_status_get_priv(const mepa_device_t        *dev,
                                                       const mepa_port_no_t       port_no,
                                                       mepa_bool_t                is_line,
                                                       phy25g_tx_rx_equ_status_t  *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value1 = 0, value2 = 0;
    u32 ipdriver_base_2_0, vc_driver_3_0;

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_0E), &value1);
    value1 =  LAN80XX_X_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(value1);
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_15), &value2);
    value2 = LAN80XX_X_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0(value2);
    if ((value1 == LAN80XX_DFE_ADAPTIVE_MODE_ENA) || (value2 == LAN80XX_DFE_MANUAL_MODE_ENABLE)) {
        status->dfe_enable = TRUE;
        status->dfe_adaptive_mode = value1 ? TRUE : FALSE;
        if (value1) { /* 5-tap DFE Adaptive Mode Coefficients*/
            ioreg_blk *io = LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_CA);
            for (u8 i = 0; i <= LAN80XX_DFE_NUM_OF_TAP; i++) {
                MEPA_RC(lan80xx_csr_rd(dev, port_no, io->mmd, io->is32, io->addr, &value1));
                status->dfe_coefficients[i] = value1;
            }
        } else { /* DFE Manual Mode coefficients */
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_14), &value1);
            status->dfe_coefficients[0] = value1;
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_13), &value1);
            status->dfe_coefficients[1] = value1;
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_12), &value1);
            status->dfe_coefficients[2] = value1;
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_11), &value1);
            value2 = LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0(value1);
            status->dfe_coefficients[3] = value2;
            value2 = LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0(value1);
            status->dfe_coefficients[4] = value2;
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PMA_8BIT_LANE_10, &value1);
            status->dfe_coefficients[5] = value1;
        }
    } else {
        status->dfe_enable = FALSE;
        status->dfe_adaptive_mode = FALSE;
        memset(status->dfe_coefficients, 0, sizeof(status->dfe_coefficients));
    }
    /* VGA Value */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_21), &value1);
    status->vga_value = LAN80XX_X_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(value1);

    /* CTLE R value */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_22), &value1);
    status->ctle_r_value = LAN80XX_X_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0(value1);

    /* CTLE C Value */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_1C), &value1);
    status->ctle_c_value = LAN80XX_X_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0(value1);

    /* TX TAP DLY Coefficient */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_03), &value1);
    status->tx_tap_dly = LAN80XX_X_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0(value1);

    /* TX TAP ADV  Coefficient */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_06), &value1);
    status->tx_tap_adv = LAN80XX_X_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0(value1);


    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_01), &value1);
    ipdriver_base_2_0 = LAN80XX_X_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(value1);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, is_line, PMA_8BIT_LANE_00), &value1);
    vc_driver_3_0 = LAN80XX_X_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(value1);

    switch (ipdriver_base_2_0) {
    case 0:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_79;
        break;
    case 1:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_88;
        break;
    case 2:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_69;
        break;
    case 3:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_58;
        break;
    case 4:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_46;
        break;
    case 5:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_16;
        break;
    case 6:
        status->amp_code = vc_driver_3_0 + 0;
        break;
    case 7:
        status->amp_code = vc_driver_3_0 + LAN80XX_TX_AMP_CODE_RANGE_32;
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "\n Invalid ipdriver value \n");
        break;
    }

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_gpio_alt_fn_channel_map(mepa_device_t         *dev,
                                               const uint8_t         gpio_num)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t  *data = (phy25g_phy_state_t *)dev->data;
    uint8_t channel = 0U;

    if (gpio_num <= LAN80XX_GPIO_31) {
        channel = (uint8_t)(gpio_num / 8U);
    } else if (gpio_num == LAN80XX_GPIO_36) {
        channel = 0U;
    } else if (gpio_num == LAN80XX_GPIO_37) {
        channel = 1U;
    } else if (gpio_num == LAN80XX_GPIO_38) {
        channel = 2U;
    } else if (gpio_num == LAN80XX_GPIO_39) {
        channel = 3U;
    } else {
        return rc;
    }

    if (data->channel_id != channel) {
        rc = MEPA_RC_ERROR;
    }
    return rc;
}


mepa_rc lan80xx_gpio_mode_set_priv(mepa_device_t                 *dev,
                                   const mepa_port_no_t            port_no,
                                   const mepa_gpio_conf_t         *gpio_conf)
{
    phy25g_phy_state_t  *data = (phy25g_phy_state_t *)dev->data;
    mepa_bool_t       is_zero_slt;
    u32 led_rate, value, channel = 0;
    u8 t_gpio_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t  *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    is_zero_slt = !(gpio_conf->gpio_no / LAN80XX_GPIO_PINS_SLOT_0);
    t_gpio_no = gpio_conf->gpio_no % LAN80XX_GPIO_PINS_SLOT_0;
    mepa_bool_t intr_b = 0;

    /* GPIO PAD Changed to Function Controlled from Ovrride - A0, A1 Worarround*/
    LAN80XX_CSR_WRM(port_no, LAN80XX_GLOBAL_IO_PAD_CTRL(gpio_conf->gpio_no), 0, LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_OVR);
    LAN80XX_CSR_WRM(port_no, LAN80XX_GLOBAL_IO_PAD_CTRL(gpio_conf->gpio_no), LAN80XX_F_GLOBAL_IO_PAD_CTRL_PUPD_EN(0), LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_EN);

    if (gpio_conf->mode == MEPA_GPIO_MODE_ALT) {
        if ((gpio_conf->gpio_no < 31) && (((gpio_conf->gpio_no & 0x03) == 0x00) || ((gpio_conf->gpio_no & 0x03) == 0x01))) {
            T_E(MEPA_TRACE_GRP_GEN, "Alt function is not supported by GPIO# %d", gpio_conf->gpio_no);
            return MEPA_RC_ERROR;
        }

        if (lan80xx_gpio_alt_fn_channel_map(dev, gpio_conf->gpio_no) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Mismatch in Port number and Alt function of GPIO Pin selected");
            return MEPA_RC_ERROR;
        }

        switch (data->port_state.speed) {
        case SPEED_1G:
            led_rate = 1;
            break;
        case SPEED_10G:
            led_rate = 2;
            break;
        default:
            led_rate = 3;
            break;
        }

        /* Out Enable Conf */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CFGX_SLOT(is_zero_slt), LAN80XX_BIT(t_gpio_no), LAN80XX_BIT(t_gpio_no));

        /* Alternate Function Not Inverted */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_OUT_INV_CFGX_SLOT(is_zero_slt), 0, LAN80XX_BIT(t_gpio_no));

        /* Enables the Alternate function */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_FUN_SELX_SLOT(is_zero_slt), 0U, LAN80XX_BIT(t_gpio_no));

        switch (gpio_conf->gpio_no) {
        case LAN80XX_GPIO_34: /* Aggregate interrupt 0/1 */
        case LAN80XX_GPIO_35:
            intr_b = (gpio_conf->gpio_no == LAN80XX_GPIO_35) ? 1U : 0U;
            LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_INTR_SRC_EN(intr_b), 0U, LAN80XX_MASK_THIRD_BYTE);
            break;
        case LAN80XX_GPIO_7:
        case LAN80XX_GPIO_36:
        case LAN80XX_GPIO_15:
        case LAN80XX_GPIO_37:
        case LAN80XX_GPIO_23:
        case LAN80XX_GPIO_38:
        case LAN80XX_GPIO_31:
        case LAN80XX_GPIO_39:
            /* Port LED Configuration */
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_LED_CONTROL,
                           ((gpio_conf->led_num == MEPA_LED1) ? LAN80XX_M_LINE_SLICE_LED_CONTROL_LED_ENABLE : 0U) |
                           LAN80XX_F_LINE_SLICE_LED_CONTROL_BLINK_TIME_SET(led_rate));
            break;
        case LAN80XX_GPIO_2:
        case LAN80XX_GPIO_3:
        case LAN80XX_GPIO_10:
        case LAN80XX_GPIO_11:
        case LAN80XX_GPIO_18:
        case LAN80XX_GPIO_19:
        case LAN80XX_GPIO_26:
        case LAN80XX_GPIO_27:
            /* Reset TWI Host */
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_MISC_BLOCKS_RESET, LAN80XX_M_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST, LAN80XX_M_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST);
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_MISC_BLOCKS_RESET, 0U, LAN80XX_M_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST);
            break;
        }
    } else if (gpio_conf->mode == MEPA_GPIO_MODE_OUT) {
        /* Configure Pin as GPIO Pin */
        LAN80XX_CSR_WRM(port_no, LAN80XX_GPIO_CTRL_GPIO_FUN_SELX_SLOT(is_zero_slt), LAN80XX_BIT(t_gpio_no), LAN80XX_BIT(t_gpio_no));

        /* Out Enable Conf */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CFGX_SLOT(is_zero_slt), LAN80XX_BIT(t_gpio_no), LAN80XX_BIT(t_gpio_no));

        /* By default GPIO will be in low level */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_OUT_INV_CFGX_SLOT(is_zero_slt), 0, LAN80XX_BIT(t_gpio_no));

    } else if (gpio_conf->mode == MEPA_GPIO_MODE_IN) {
        /* Configure Pin as GPIO Pin */
        LAN80XX_CSR_WRM(port_no, LAN80XX_GPIO_CTRL_GPIO_FUN_SELX_SLOT(is_zero_slt), LAN80XX_BIT(t_gpio_no), LAN80XX_BIT(t_gpio_no));

        /* Input Enable Conf */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CFGX_SLOT(is_zero_slt), 0, LAN80XX_BIT(t_gpio_no));
        /* GPIO Input change Interrupt configuration Enable*/
        if ((gpio_conf->gpio_intrpt == MEPA_GPIO_INTR_0) || (gpio_conf->gpio_intrpt == MEPA_GPIO_INTR_1)) {
            channel = gpio_conf->gpio_intrpt - 1;
            LAN80XX_CSR_RD(base_dev, base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(is_zero_slt), &value);
            LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(is_zero_slt), LAN80XX_BIT(t_gpio_no) & value, LAN80XX_BIT(t_gpio_no));
            LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_INTR_SRC_ENX_SLOT(channel, is_zero_slt), LAN80XX_BIT(t_gpio_no), LAN80XX_BIT(t_gpio_no));
        } else {
            LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_INTR_SRC_ENX_SLOT(channel, is_zero_slt), 0, LAN80XX_BIT(t_gpio_no));
        }
    }
    /* Push Pull Enab configuration (By default open drain configuration)*/
    LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_OUT_PPX_SLOT(is_zero_slt), gpio_conf->pp_enable ? LAN80XX_BIT(t_gpio_no) : 0, LAN80XX_BIT(t_gpio_no));

    return MEPA_RC_OK;
}

mepa_rc lan80xx_gpio_read_priv(mepa_device_t        *dev,
                               mepa_port_no_t       port_no,
                               u8                   gpio_no,
                               mepa_bool_t          *const value)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t  *base_data;
    u32 val = 0;
    mepa_device_t *base_dev;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_bool_t is_zero_slt = TRUE;
    is_zero_slt = !(gpio_no / LAN80XX_GPIO_PINS_SLOT_0);
    u8 t_gpio = gpio_no % LAN80XX_GPIO_PINS_SLOT_0;
    LAN80XX_CSR_RD(base_dev, base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_STATX_SLOT(is_zero_slt), &val);
    *value = (val & LAN80XX_BIT(t_gpio)) ? TRUE : FALSE;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_gpio_write_priv(mepa_device_t   *dev,
                                mepa_port_no_t  port_no,
                                u8              gpio_no,
                                mepa_bool_t     value)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t  *base_data;
    mepa_bool_t is_zero_slt = TRUE;
    mepa_device_t *base_dev;
    u32 reg_value = 0;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    is_zero_slt = !(gpio_no / LAN80XX_GPIO_PINS_SLOT_0);
    u8 t_gpio = gpio_no % LAN80XX_GPIO_PINS_SLOT_0;

    LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_CFGX_SLOT(is_zero_slt), &reg_value);
    if (reg_value & LAN80XX_BIT(t_gpio)) {
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GPIO_CTRL_GPIO_OUT_INV_CFGX_SLOT(is_zero_slt),  (value ? (LAN80XX_BIT(t_gpio)) : 0), LAN80XX_BIT(t_gpio));
        return MEPA_RC_OK;
    }
    T_E(MEPA_TRACE_GRP_GEN, "GPIO %d should held in output mode\n", gpio_no);
    return MEPA_RC_ERROR;
}

mepa_rc lan80xx_phy_i2c_write_priv(mepa_device_t  *dev,
                                   const mepa_port_no_t  port_no,
                                   const u8              reg_addr,
                                   u8                    cnt,
                                   const u8              *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0;
    u8 addr = 0;

    if (((reg_addr + cnt) > LAN80XX_UINT_8_MAX_VALUE) || (cnt == 0)) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Inaccessible I2C Address (greater than 255 or cnt is zero) on Port : %d\n", port_no);
        return MEPA_RC_ERROR;
    }

    for (u8 i = 0; i < cnt; i++) {

        addr = reg_addr + i;
        // Check if Bus is not busy
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_SFP_TWS_TWI_BUS_STATUS, &val);
        if (val & LAN80XX_M_SFP_TWS_TWI_BUS_STATUS_TWI_BUS_BUSY) {
            T_E(MEPA_TRACE_GRP_GEN, "previous write operation failed or causes error ");
            return MEPA_RC_ERROR;
        }
        val = 0;
        // [15:8] = data ; [7:0] = address
        val |= LAN80XX_F_SFP_TWS_TWI_WRITE_CTRL_WRITE_DATA(value[i]);
        val |= LAN80XX_F_SFP_TWS_TWI_WRITE_CTRL_WRITE_ADDR(addr);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_SFP_TWS_TWI_WRITE_CTRL, val);
        MEPA_MSLEEP(1);
        val = 0;
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_SFP_TWS_TWI_BUS_STATUS, &val);
        if (!(val & LAN80XX_M_SFP_TWS_TWI_BUS_STATUS_TWI_WRITE_ACK)) {
            T_E(MEPA_TRACE_GRP_GEN, "\n I2C Write not Acknowledged \n");
            return MEPA_RC_ERROR;
        }
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_i2c_read_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const u8              reg_addr,
                                  u8                    cnt,
                                  u8                    *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0;
    *value = 0;
    u8 addr = 0;
    if (((reg_addr + cnt) > LAN80XX_UINT_8_MAX_VALUE) || (cnt == 0)) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Inaccessible I2C Address (greater than 255 or cnt is zero) on Port : %d\n", port_no);
        return MEPA_RC_ERROR;
    }

    for (u8 i = 0; i < cnt; i++) {
        addr = reg_addr + i;
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_SFP_TWS_TWI_READ_ADDR, addr);
        MEPA_MSLEEP(1);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_SFP_TWS_TWI_READ_STATUS_DATA, &val);
        if (val & LAN80XX_M_SFP_TWS_TWI_READ_STATUS_DATA_TWI_BUS_BUSY) {
            T_E(MEPA_TRACE_GRP_GEN, "read operation failed for address %d", addr);
            return MEPA_RC_ERROR;
        }
        value[i] = LAN80XX_X_SFP_TWS_TWI_READ_STATUS_DATA_READ_DATA(val);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_i2c_init_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const u8              client_id,
                                  const u16             prescalar)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (prescalar < LAN80XX_I2C_SCL_PRESCALAR_INVALID) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid prescaler value %d", prescalar);
        return MEPA_RC_ERROR;
    }
    //Default Prescalar 0x0095 = 400 kHz,
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_SFP_TWS_TWI_PRESCALE, prescalar);
    //Write Client ID. Default 0x50
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_SFP_TWS_TWI_CLIENT_ID, client_id);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_loopback_set_priv(mepa_device_t         *dev,
                                  const mepa_port_no_t  port_no,
                                  const mepa_loopback_t *loopback)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    T_I(MEPA_TRACE_GRP_GEN, "Port No : %d Loopback set private configuration", port_no);
    if (loopback->connector_ena == 1 || loopback->qsgmii_pcs_tbi_ena == 1 || loopback->qsgmii_pcs_gmii_ena == 1 || loopback->qsgmii_serdes_ena == 1) {

        T_E(MEPA_TRACE_GRP_GEN, "Port No : %d Loopback type Not supported", port_no);
        return MEPA_RC_ERROR;
    }

    /* L2 Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_L2_LPBK, loopback->far_end_ena ? LAN80XX_M_HOST_SLICE_L2_LPBK_L2_LPBK : 0,
                    LAN80XX_M_HOST_SLICE_L2_LPBK_L2_LPBK);
    data->port_state.loopback_conf.l2_lp = loopback->far_end_ena;

    /* H2 Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_H2_LPBK, loopback->near_end_ena ? LAN80XX_M_LINE_SLICE_H2_LPBK_H2_LPBK : 0,
                    LAN80XX_M_LINE_SLICE_H2_LPBK_H2_LPBK);
    data->port_state.loopback_conf.h2_lp = loopback->near_end_ena;


    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, 1, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_LINE_REG(LAN80XX, 0, PMA_8BIT_CMU_FF), 0x00); /* Select LANE */

    if (loopback->mac_serdes_equip_ena) {
        /* H1 Loopback */

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_19, LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_1E, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_18, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

    } else if (loopback->mac_serdes_facility_ena) {
        /* H5 Loopback */

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_1E, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_19, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_18, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

    } else if (loopback->mac_serdes_input_ena) {
        /* H6 Loopback */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_1E, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_19, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_18, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

    } else {

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_40, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_1E, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_04, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_19, 0, LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PMA_8BIT_LANE_18, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);
    }

    data->port_state.loopback_conf.h1_lp = loopback->mac_serdes_equip_ena;
    data->port_state.loopback_conf.h6_lp = loopback->mac_serdes_input_ena;
    data->port_state.loopback_conf.h5_lp = loopback->mac_serdes_facility_ena;
    if (loopback->media_serdes_equip_ena) {
        /* L1 Loopback */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_19, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_1E, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_18, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);
    } else if (loopback->media_serdes_facility_ena) {
        /* L5 Loopback */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_1E, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_19, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_18, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);
    } else if (loopback->media_serdes_input_ena) {
        /* L6 Loopback */

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_1E, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_19, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_18, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);

    } else {

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_40, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV, LAN80XX_M_HOST_PMA_8BIT_LANE_40_LN_R_RX_POL_INV);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_1E, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_04, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_19, 0, LAN80XX_M_HOST_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PMA_8BIT_LANE_18, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN, LAN80XX_M_HOST_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN);
    }
    data->port_state.loopback_conf.l1_lp = loopback->media_serdes_equip_ena;
    data->port_state.loopback_conf.l5_lp = loopback->media_serdes_facility_ena;
    data->port_state.loopback_conf.l6_lp = loopback->media_serdes_input_ena;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_loopback_conf_set_priv(mepa_device_t            *dev,
                                           const mepa_port_no_t     port_no,
                                           const phy25g_lp_types_t  *loopback)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    T_I(MEPA_TRACE_GRP_GEN, "Port no : %d PHY loopback configuration", port_no);
    /* L3P Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_L3P_LPBK, loopback->l3p_lp_ena ? LAN80XX_M_HOST_SLICE_L3P_LPBK_L3P_LPBK : 0,
                    LAN80XX_M_HOST_SLICE_L3P_LPBK_L3P_LPBK);
    data->port_state.loopback_conf.l3p_lp = loopback->l3p_lp_ena;

    /* H3P Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_H3P_LPBK, loopback->h3p_lp_ena ? LAN80XX_M_LINE_SLICE_H3P_LPBK_H3P_LPBK : 0,
                    LAN80XX_M_LINE_SLICE_H3P_LPBK_H3P_LPBK);
    data->port_state.loopback_conf.h3p_lp = loopback->h3p_lp_ena;

    /* L3M Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_LB_CFG, loopback->l3m_lp_ena ? LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA : 0,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA);
    data->port_state.loopback_conf.l3m_lp = loopback->l3m_lp_ena;

    /* H3M Loopback */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_LB_CFG, loopback->h3m_lp_ena ? LAN80XX_M_LINE_MAC_LINE_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA : 0,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_LB_CFG_XGMII_HOST_LB_ENA);
    data->port_state.loopback_conf.h3m_lp = loopback->h3m_lp_ena;

    /* H7 Loopback */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_HOST_SLICE_DATAPATH_CONTROL,
                         loopback->h7_lp_ena ? LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL2 : 0,
                         LAN80XX_M_HOST_SLICE_DATAPATH_CONTROL_IGR_XGMII_PG_SEL2);
    data->port_state.loopback_conf.h7_lp = loopback->h7_lp_ena;

    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_loopback_conf_get_priv(mepa_device_t         *dev,
                                           const mepa_port_no_t  port_no,
                                           phy25g_lp_get_t       *const loopback)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    memcpy(loopback, &data->port_state.loopback_conf, sizeof(phy25g_lp_get_t));
    return MEPA_RC_OK;
}

mepa_rc lan80xx_temp_sensor_init(mepa_device_t          *dev,
                                 const mepa_port_no_t   port_no,
                                 u8                     threshold,
                                 mepa_bool_t            enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t  *base_data;
    mepa_device_t *base_dev;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    T_I(MEPA_TRACE_GRP_GEN, "Port No : %d Temperature Sensor Intialization", base_data->port_no);
    if (!enable) {
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0, 0, LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA);
        return MEPA_RC_OK;
    }

    MEPA_RC(lan80xx_memory_write(dev, MCU_TEMP_THRESHOLD_REG_ADDR, &threshold, MCU_TEMP_THRESHOLD_BYTE_LEN));

    LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0, LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA,
                    LAN80XX_M_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA);

    /* A temperature measurement takes ~16 ms, so Application needs to have 16ms after Enabling Temeprature Sensor to get the valid Temperature*/
    return MEPA_RC_OK;
}

mepa_rc lan80xx_temp_sensor_get_priv(mepa_device_t          *dev,
                                     const mepa_port_no_t   port_no,
                                     i16                    *const value)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t  *base_data;
    mepa_device_t *base_dev;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u32 val = 0;
    u32 sampling = 0;
    LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_GLOBAL_TEMP_SENSOR_CFG_0, &val);
    sampling = LAN80XX_X_GLOBAL_TEMP_SENSOR_CFG_0_SAMPLE_ENA(val);

    if (!sampling) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Temeperature Sensor is not Enabled on Port : %d \n", data->port_no);
        return MEPA_RC_ERROR;
    }

    LAN80XX_CSR_RD(base_dev, base_data->port_no, LAN80XX_GLOBAL_TEMP_SENSOR_STAT, &val);
    val = val & 0xFFFF;
    if (!LAN80XX_X_GLOBAL_TEMP_SENSOR_STAT_TEMP_VALID(val)) {
        T_E(MEPA_TRACE_GRP_GEN, "Temeperature Value is Invalid on Port : %d \n", port_no);
        return MEPA_RC_ERROR;
    }
    /* The constant values are from the silicon DOS */
    *value = (i16) (((LAN80XX_X_GLOBAL_TEMP_SENSOR_STAT_TEMP(val) * LAN80XX_PVT_CONST_Y) / LAN80XX_PVT_RESOL) - LAN80XX_PVT_CONST_K);
    T_I(MEPA_TRACE_GRP_GEN, "Port No : %d Temperature : %d", port_no, *value);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_rckout_conf_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no,
                                     phy_25g_rckout_conf_t *const rckout_conf_a,
                                     phy_25g_rckout_conf_t *const rckout_conf_b)
{
    uint32_t get_conf;
    mepa_rc rc =  MEPA_RC_OK;
    uint8_t clk_div = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    T_I(MEPA_TRACE_GRP_GEN, "Port no : %d SyncE Configuration get", port_no);

    if ((NULL == rckout_conf_a) || (NULL == rckout_conf_b)) {
        T_E(MEPA_TRACE_GRP_GEN, "%s Invalid pointer", __FUNCTION__);
        rc = MEPA_RC_ERROR;
        return rc;
    }
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, &get_conf);
    /* Clock A Enable*/
    rckout_conf_a->rcvd_clk_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE(get_conf);
    /* Clock source select */
    rckout_conf_a->src = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL(get_conf);
    clk_div = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV(get_conf);
    if (rckout_conf_a->src == LAN80XX_SREFCLK) {
        if (clk_div == LAN80XX_PHY_DIVIDER_4) {
            rckout_conf_a->freq = LAN80XX_RCKOUT_75_00;
        } else if (clk_div ==  LAN80XX_PHY_DIVIDER_8) {
            rckout_conf_a->freq = LAN80XX_RCKOUT_37_50;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
        }
    } else if (rckout_conf_a->src == LAN80XX_PTP_LTC) {
        if (clk_div == LAN80XX_PHY_DIVIDER_4) {
            rckout_conf_a->freq = LAN80XX_RCKOUT_79_58;
        } else if (clk_div ==  LAN80XX_PHY_DIVIDER_8) {
            rckout_conf_a->freq = LAN80XX_RCKOUT_39_79;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
        }
    } else {
        if (data->port_state.speed == SPEED_1G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_1) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_125_00;
            } else if (clk_div ==  LAN80XX_PHY_DIVIDER_2) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_62_50;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_4) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_31_25;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_15_625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else if (data->port_state.speed == SPEED_10G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_2) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_128_90625;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_4) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_64_453125;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_32_2265625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else if (data->port_state.speed == SPEED_25G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_a->freq = LAN80XX_RCKOUT_80_56640625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid port speed\n");
        }
    }
    /* LOS Squelch Enable*/
    rckout_conf_a->los_squelch_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA(get_conf);
    /* PCS Link status */
    rckout_conf_a->link_sts_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA(get_conf);
    /* AUTO squelch Enable - 1, Disable -0 for disabling PCS link, LOS, Link KR squelch*/
    rckout_conf_a->auto_squelch_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA(get_conf);
    rckout_conf_b->rckout_sel = LAN80XX_RCKOUTA;
    get_conf = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, &get_conf);
    /* Clock B Enable*/
    rckout_conf_b->rcvd_clk_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE(get_conf);
    /* Clock source select */
    rckout_conf_b->src = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL(get_conf);
    /* Clock Divider select */
    clk_div = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV(get_conf);
    if (rckout_conf_b->src == LAN80XX_SREFCLK) {
        if (clk_div == LAN80XX_PHY_DIVIDER_4) {
            rckout_conf_b->freq = LAN80XX_RCKOUT_75_00;
        } else if (clk_div ==  LAN80XX_PHY_DIVIDER_8) {
            rckout_conf_b->freq = LAN80XX_RCKOUT_37_50;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
        }
    } else if (rckout_conf_b->src == LAN80XX_PTP_LTC) {
        if (clk_div == LAN80XX_PHY_DIVIDER_4) {
            rckout_conf_b->freq = LAN80XX_RCKOUT_79_58;
        } else if (clk_div ==  LAN80XX_PHY_DIVIDER_8) {
            rckout_conf_b->freq = LAN80XX_RCKOUT_39_79;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
        }
    } else {
        if (data->port_state.speed == SPEED_1G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_1) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_125_00;
            } else if (clk_div ==  LAN80XX_PHY_DIVIDER_2) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_62_50;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_4) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_31_25;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_15_625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else if (data->port_state.speed == SPEED_10G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_2) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_128_90625;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_4) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_64_453125;
            } else if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_32_2265625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else if (data->port_state.speed == SPEED_25G) {
            if (clk_div == LAN80XX_PHY_DIVIDER_8) {
                rckout_conf_b->freq = LAN80XX_RCKOUT_80_56640625;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid Divider value\n");
            }
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid port speed\n");
        }
    }
    /* LOS Squelch Enable*/
    rckout_conf_b->los_squelch_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA(get_conf);
    /* PCS Link status */
    rckout_conf_b->link_sts_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA(get_conf);
    /* AUTO squelch Enable - 1, Disable -0 for disabling PCS link, LOS, Link KR squelch*/
    rckout_conf_b->auto_squelch_enable = LAN80XX_X_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA(get_conf);
    rckout_conf_b->rckout_sel = LAN80XX_RCKOUTB;

    return rc;
}

static mepa_rc lan80xx_frequency_divider(phy25g_phy_state_t *data,
                                         phy_25g_clk_sel_t src,
                                         phy_25g_rckout_freq_t freq,
                                         uint8_t *divider)
{
    mepa_rc rc = MEPA_RC_OK;

    switch (src) {
    case LAN80XX_SREFCLK:
        switch (freq) {
        case LAN80XX_RCKOUT_75_00:
            *divider = LAN80XX_PHY_DIVIDER_4;
            break;
        case LAN80XX_RCKOUT_37_50:
            *divider =  LAN80XX_PHY_DIVIDER_8;
            break;
        default:
            T_E(MEPA_TRACE_GRP_GEN, "Invalid frequency %d configured", freq);
            rc = MEPA_RC_ERROR;
            break;
        }
        break;
    case LAN80XX_PTP_LTC:
        switch (freq) {
        case LAN80XX_RCKOUT_79_58:
            *divider = LAN80XX_PHY_DIVIDER_4;
            break;
        case LAN80XX_RCKOUT_39_79:
            *divider =  LAN80XX_PHY_DIVIDER_8;
            break;
        default:
            T_E(MEPA_TRACE_GRP_GEN, "Invalid frequency %d configured", freq);
            rc = MEPA_RC_ERROR;
            break;
        }
        break;
    case LAN80XX_LINE0_RECVRD_CLOCK:
    case LAN80XX_LINE1_RECVRD_CLOCK:
    case LAN80XX_LINE2_RECVRD_CLOCK:
    case LAN80XX_LINE3_RECVRD_CLOCK:
    case LAN80XX_HOST0_RECVRD_CLOCK:
    case LAN80XX_HOST1_RECVRD_CLOCK:
    case LAN80XX_HOST2_RECVRD_CLOCK:
    case LAN80XX_HOST3_RECVRD_CLOCK:
        if (data->port_state.speed == SPEED_1G) {
            switch (freq) {
            case LAN80XX_RCKOUT_125_00:
                *divider = LAN80XX_PHY_DIVIDER_1;
                break;
            case LAN80XX_RCKOUT_62_50:
                *divider =  LAN80XX_PHY_DIVIDER_2;
                break;
            case LAN80XX_RCKOUT_31_25:
                *divider =  LAN80XX_PHY_DIVIDER_4;
                break;
            case LAN80XX_RCKOUT_15_625:
                *divider =  LAN80XX_PHY_DIVIDER_8;
                break;
            default:
                T_E(MEPA_TRACE_GRP_GEN, "Invalid frequency %d configured", freq);
                rc = MEPA_RC_ERROR;
                break;
            }
        } else if (data->port_state.speed == SPEED_10G) {
            switch (freq) {
            case LAN80XX_RCKOUT_128_90625:
                *divider = LAN80XX_PHY_DIVIDER_2;
                break;
            case LAN80XX_RCKOUT_64_453125:
                *divider =  LAN80XX_PHY_DIVIDER_4;
                break;
            case LAN80XX_RCKOUT_32_2265625:
                *divider =  LAN80XX_PHY_DIVIDER_8;
                break;
            default:
                T_E(MEPA_TRACE_GRP_GEN, "Invalid frequency %d configured", freq);
                rc = MEPA_RC_ERROR;
                break;
            }
        } else if (data->port_state.speed == SPEED_25G) {
            if (freq == LAN80XX_RCKOUT_80_56640625) {
                *divider = LAN80XX_PHY_DIVIDER_8;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid frequency %d configured", freq);
                rc = MEPA_RC_ERROR;
            }
        }
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "Invalid clock source %d", src);
        rc = MEPA_RC_ERROR;
        break;
    }
    return rc;
}

mepa_rc lan80xx_rckout_conf_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no,
                                     const phy_25g_rckout_conf_t *rckout_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    T_I(MEPA_TRACE_GRP_GEN, "Port no : %d SyncE Configuration set", port_no);
    uint8_t divider = 0;
    mepa_rc rc = MEPA_RC_OK;
    uint32_t value = 0;
    uint8_t gpio_no[4] = {LAN80XX_GPIO_6, LAN80XX_GPIO_14, LAN80XX_GPIO_22, LAN80XX_GPIO_30};

    if (rckout_conf->rckout_sel == LAN80XX_RCKOUTA) {
        /* Clock source select */
        LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                        LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL(rckout_conf->src), \
                        LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_SEL);
        /* Clock Divider select */
        rc = lan80xx_frequency_divider(data, rckout_conf->src, rckout_conf->freq, &divider);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s Invalid configuration for clock divider", __FUNCTION__);
            return rc;
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                        LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV(divider), \
                        LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_RCVRD_CLK_DIV);
        /* LOS Squelch Enable*/
        if (rckout_conf->los_squelch_enable) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_GPIO_CTRL_GPIO_FUN_SEL0, &value);
            if (value & LAN80XX_BIT(gpio_no[data->channel_id])) {
                T_E(MEPA_TRACE_GRP_GEN, "GPIO No-%d should held in alternate mode for LOS squelch", gpio_no[data->channel_id]);
                return MEPA_RC_ERROR;
            }
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(1), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_SERDES_LOS, \
                            LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(1), \
                            LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(1), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA(1),
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(0), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_SERDES_LOS, \
                            LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(0), \
                            LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(0), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA(0),
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_SD_LOS_SQUELCH_ENA);
        }
        /* PCS Link status */
        if (rckout_conf->link_sts_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_PCS_LINK_STS_SQUELCH_ENA);
        }
        /* AUTO squelch Enable - 1, Disable -0 for disabling PCS link, LOS, Link KR squelch*/
        if (rckout_conf->auto_squelch_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_AUTO_SQUELCH_ENA);
        }
        /* Clock A Enable*/
        if (rckout_conf->rcvd_clk_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKA_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKA_CFG_CLKA_ENABLE);
        }
    } else if (rckout_conf->rckout_sel == LAN80XX_RCKOUTB) {
        /* Clock source select */
        LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                        LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL(rckout_conf->src), \
                        LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_SEL);
        /* Clock Divider select */
        rc = lan80xx_frequency_divider(data, rckout_conf->src, rckout_conf->freq, &divider);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s Invalid configuration for clock divider", __FUNCTION__);
            return rc;
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                        LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV(divider), \
                        LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_RCVRD_CLK_DIV);
        /* LOS Squelch Enable*/
        if (rckout_conf->los_squelch_enable) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_GPIO_CTRL_GPIO_FUN_SEL0, &value);
            if (value & LAN80XX_BIT(gpio_no[data->channel_id])) {
                T_E(MEPA_TRACE_GRP_GEN, "GPIO No-%d should held in alternate mode for LOS squelch", gpio_no[data->channel_id]);
                return MEPA_RC_ERROR;
            }
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(1), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_SERDES_LOS, \
                            LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(1), \
                            LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(1), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA(1),
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(0), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_SLICE_SERDES_LOS, \
                            LAN80XX_F_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN(0), \
                            LAN80XX_M_HOST_SLICE_SERDES_LOS_SD25G_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SERDES_LOS, \
                            LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(0), \
                            LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_EN);
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_SD_LOS_SQUELCH_ENA);
        }
        /* PCS Link status */
        if (rckout_conf->link_sts_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_PCS_LINK_STS_SQUELCH_ENA);
        }
        /* AUTO squelch Enable - 1, Disable -0 for disabling PCS link, LOS, Link KR squelch*/
        if (rckout_conf->auto_squelch_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_AUTO_SQUELCH_ENA);
        }
        /* Clock B Enable*/
        if (rckout_conf->rcvd_clk_enable) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE(1), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_CLK_CFG_RCVRD_CLKB_CFG, \
                            LAN80XX_F_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE(0), \
                            LAN80XX_M_CLK_CFG_RCVRD_CLKB_CFG_CLKB_ENABLE);
        }
    }
    return rc;
}

mepa_rc lan80xx_conf_set_priv(struct mepa_device *dev, const mepa_conf_t *config)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_port_mode_t mode;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    /* Channel ID Will be configured only Once */
    if (!data->channel_id_lock) {
        if (config->conf_25g.channel_id == MEPA_CHANNELID_NONE) {
            T_E(MEPA_TRACE_GRP_GEN, "channel id is not supported for port %d", data->port_no);
            return MEPA_RC_ERROR;
        }
        data->channel_id = (config->conf_25g.channel_id - 1);
        data->channel_id_lock = 1;
    }

    if ((base_data->features.quad_disable != 0) && (data->channel_id >= 2U)) {
        T_E(MEPA_TRACE_GRP_GEN, "\n PHY on Port %d is Dual SKU\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    if (config->fdx == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "\n PHY on Port %d Supports only Full-Duplex Mode \n", data->port_no);
        return MEPA_RC_ERROR;
    }
    if (config->speed == MESA_SPEED_10G && config->conf_25g.rs_fec_25g) {
        T_E(MEPA_TRACE_GRP_GEN, "\n RS-FEC Supported only at 25G Speed \n", data->port_no);
        return MEPA_RC_ERROR;
    }
    if (config->speed == MESA_SPEED_1G && (config->conf_25g.rs_fec_25g || config->conf_25g.base_r_10gfec)) {
        T_E(MEPA_TRACE_GRP_GEN, "\n FEC not supported only at 1G Speed \n", data->port_no);
        return MEPA_RC_ERROR;
    }
    if (data->dev.devid == LAN80XX_DEV_ID_UNKNOWN) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Unknow SKU on Port : %d Pre Reset Should be called be conf_set\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    if ((base_data->features.speed_25g_disable != 0U) && (config->speed == MESA_SPEED_25G)) {
        T_E(MEPA_TRACE_GRP_GEN, "The PHY SKU on port %d doesnot support 25G speed\n", data->port_no);
        return MEPA_RC_ERROR;
    }
    if (config->flow_control) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Use API lan80xx_flow_control_set API on Port : %d to configure Flow Control \n", data->port_no);
    }

    if (config->conf_25g.host_media == MEPA_MEDIA_TYPE_1000BASE_T) {
        T_E(MEPA_TRACE_GRP_GEN, "\n 1000BASE-T Media not supported on HOST side on port : %d \n", data->port_no);
        return MEPA_RC_ERROR;
    }

    if ((config->speed != MESA_SPEED_1G) && (config->conf_25g.line_media == MEPA_MEDIA_TYPE_1000BASE_T)) {
        T_E(MEPA_TRACE_GRP_GEN, "\n 1000BASE-T Media type is supported only at 1G speed on port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    memset(&mode, 0, sizeof(phy25g_port_mode_t));
    T_I(MEPA_TRACE_GRP_GEN, "Conf_set on port : %d\n", data->port_no);
    mepa_rc rc = MEPA_RC_ERROR;

    /* Serdes Polarity Swap Config */
    /* The below Polarity configurations handles any polarity swap outside the M25G chip(i.e, in user board PCB)
     */
    mode.polarity.line_rx = config->conf_25g.polarity.line_rx;
    mode.polarity.line_tx = config->conf_25g.polarity.line_tx;
    mode.polarity.host_rx = config->conf_25g.polarity.host_rx;
    mode.polarity.host_tx = config->conf_25g.polarity.host_tx;

    if (config->speed == MESA_SPEED_AUTO) {

        if (config->aneg.speed_10m_hdx || config->aneg.speed_10m_fdx || config->aneg.speed_100m_hdx || config->aneg.speed_100m_fdx ||
            config->aneg.speed_1g_hdx  || config->aneg.speed_2g5_fdx || config->aneg.speed_5g_fdx) {

            T_E(MEPA_TRACE_GRP_GEN, "\n Advertised Speed is Not Supported By PHY on Port : %d (Supports 1G, 10G, 25G)\n", data->port_no);
            return MEPA_RC_ERROR;
        }

        if ((config->conf_25g.np_base_r_fec || config->conf_25g.np_rs_fec) && (!config->aneg.next_page_enable)) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Enable Next Page on Port %d to advertise FEC on Next Page\n", data->port_no);
            return MEPA_RC_ERROR;
        }
        if (lan80xx_check_mcu_rdy_priv(dev) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "MCU boot up failed");
            return MEPA_RC_ERROR;
        }
        if (config->adv_dis == TRUE) {
            /* Disable ANEG */
            LAN80XX_CSR_WRM(data->port_no, LAN80XX_LINE_KR_AN_CFG0, 0, LAN80XX_M_LINE_KR_AN_CFG0_AN_ENABLE);
            LAN80XX_CSR_WRM(data->port_no, LAN80XX_HOST_KR_AN_CFG0, 0, LAN80XX_M_HOST_KR_AN_CFG0_AN_ENABLE);
        } else if (lan80xx_kr_aneg_enable(dev, data->port_no, config) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Error in KR Configuration on port %d", data->port_no);
            return MEPA_RC_ERROR;
        }
        mode.speed_oper_mode = LAN80XX_PHY_ANEG;

    } else if (config->speed == MESA_SPEED_1G) {
        /* Forced 1G Speed */
        mode.speed_oper_mode = LAN80XX_PHY_1G_MODE;
    } else if (config->speed == MESA_SPEED_10G) {
        /* Forced 10G Speed */
        mode.speed_oper_mode = LAN80XX_PHY_10G_LAN_MODE;
    } else if (config->speed == MESA_SPEED_25G) {
        /* Forced 25G Speed */
        mode.speed_oper_mode = LAN80XX_PHY_25G_LAN_MODE;
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "\n Configured Speed Not Supported on Port %d \n", data->port_no);
        return MEPA_RC_ERROR;
    }
    /* Software Context of Only LINE Side ANEG abilities is stored, so "mepa_conf_get()" will give
     * the ANEG abilites advertised in LINE Side only, the HOST side abilities needs to be adjusted
     * based on Abilities advertised on LINE Side
     */
    if ((config->speed != MESA_SPEED_AUTO) || (config->aneg.advertise_dir != MEPA_ADV_SIDE_HOST)) {
        data->conf = *config;
    }
    rc = lan80xx_mode_set_init(dev, data->port_no, &mode);
    return rc;
}

mepa_rc lan80xx_kr_reg_dump(mepa_device_t            *dev,
                            const mepa_port_no_t     port_no,
                            const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = FALSE;
    u32 val1 = 0, val2 = 0;
    pr("\n\n\t\t:-:-:-:  HOST KR  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_KR;
    for (u8 i = 0; i < 10; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_kr[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_kr[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_kr[i].str, val1, dump_kr[i + 1].str, val2);
    }
    pr("\n\n\t\t:-:-:-:  LINE KR  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_KR;
    for (u8 i = 0; i < 10; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_kr[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_kr[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_kr[i].str, val1, dump_kr[i + 1].str, val2);
    }
    return MEPA_RC_OK;
}


mepa_rc lan80xx_pcs_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = FALSE;
    u32 val1 = 0, val2 = 0;
    pr("\n\n\t\t:-:-:-:  HOST_PCS_CFG  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_PCS_CFG;
    for (u8 i = 0; i < LAN80XX_PCS_CFG_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs[i].str, val1, host_line_pcs[i + 1].str, val2);
    }
    mmd = MMD_ID_HOST_RSFEC;

    for (u8 i = LAN80XX_PCS_CFG_REG_NUM; i < LAN80XX_PCS_CFG_RSFEC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs[i].str, val1, host_line_pcs[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  LINE_PCS_CFG  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_PCS_CFG;
    for (u8 i = 0; i < LAN80XX_PCS_CFG_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs[i].str, val1, host_line_pcs[i + 1].str, val2);
    }
    mmd = MMD_ID_LINE_RSFEC;

    for (u8 i = LAN80XX_PCS_CFG_REG_NUM; i < LAN80XX_PCS_CFG_RSFEC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs[i].str, val1, host_line_pcs[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  HOST_PCS25G  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_PCS25G;
    for (u8 i = 0; i < LAN80XX_PCS25G_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs25g[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs25g[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs25g[i].str, val1, host_line_pcs25g[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  LINE_PCS25G  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_PCS25G;
    for (u8 i = 0; i < LAN80XX_PCS25G_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs25g[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pcs25g[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pcs25g[i].str, val1, host_line_pcs25g[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  HOST_RSFEC  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_RSFEC;
    for (u8 i = 0; i < LAN80XX_RSFEC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_rsfec_reg[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_rsfec_reg[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_rsfec_reg[i].str, val1, dump_rsfec_reg[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  LINE_RSFEC  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_RSFEC;
    for (u8 i = 0; i < LAN80XX_RSFEC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_rsfec_reg[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_rsfec_reg[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_rsfec_reg[i].str, val1, dump_rsfec_reg[i + 1].str, val2);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_gpio_glb_slice_reg_dump(mepa_device_t            *dev,
                                        const mepa_port_no_t     port_no,
                                        const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = FALSE;
    u32 val1 = 0, val2 = 0;
    pr("\n\n\t\t:-:-:-:  GLOBAL  :-:-:-:\n\n");
    mmd = MMD_ID_GLOBAL_REGISTERS;
    for (u8 i = 0; i < LAN80XX_GLOBAL_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_global[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_global[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_global[i].str, val1, dump_global[i + 1].str, val2);
    }
    u32 addr = LAN80XX_GPIO_PAD_CTRL_BASE_ADDR;
    char *str = "IO_PAD_CTRL_";
    for (u8 i = 0; i < LAN80XX_GPIO_PAD_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (addr + i), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (addr + i + 1), &val2));
        pr("%s%-13d: 0x%08X     %s%-13d: 0x%08X\n", str,  i, val1, str, (i + 1), val2);
    }
    pr("\n\n\t\t:-:-:-:  MCU_IO_MNGT_MISC  :-:-:-:\n\n");
    mmd = MMD_ID_GLOBAL_REGISTERS;
    for (u8 i = 0; i < LAN80XX_MCU_MISC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_mcu_misc[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_mcu_misc[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_mcu_misc[i].str, val1, dump_mcu_misc[i + 1].str, val2);
    }

    is_32 = TRUE;
    pr("\n\n\t\t:-:-:-:  GPIO_CTRL  :-:-:-:\n\n");
    mmd = MMD_ID_GPIO_CTRL;
    for (u8 i = 0; i < LAN80XX_GPIO_CTRL_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_gpio_ctrl[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_gpio_ctrl[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_gpio_ctrl[i].str, val1, dump_gpio_ctrl[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  CROSS_CONNECT  :-:-:-:\n\n");
    mmd = MMD_ID_CROSS_CONN;
    for (u8 i = 0; i < LAN80XX_XC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_cross_cnt[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_cross_cnt[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_cross_cnt[i].str, val1, dump_cross_cnt[i + 1].str, val2);
    }
    is_32 = FALSE;
    pr("\n\n\t\t:-:-:-:  HOST_INTR_CTRL  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_INTR_CTL;
    for (u8 i = 0; i < LAN80XX_INTR_CTRL_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_intr_ctrl[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_intr_ctrl[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_intr_ctrl[i].str, val1, dump_intr_ctrl[i + 1].str, val2);
    }
    pr("\n\n\t\t:-:-:-:  LINE_INTR_CTRL  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_INTR_CTL;
    for (u8 i = 0; i < LAN80XX_INTR_CTRL_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_intr_ctrl[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_intr_ctrl[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_intr_ctrl[i].str, val1, dump_intr_ctrl[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  HOST_SLICE  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_SLICE;
    for (u8 i = 0; i < LAN80XX_HOST_SLICE_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_host_slice[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_host_slice[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_host_slice[i].str, val1, dump_host_slice[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  LINE_SLICE  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_SLICE;
    for (u8 i = 0; i < LAN80XX_LINE_SLICE_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_line_slice[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_line_slice[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_line_slice[i].str, val1, dump_line_slice[i + 1].str, val2);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_mac_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = TRUE;
    u32 val1 = 0, val2 = 0;
    pr("\n\n\t\t:-:-:-:  HOST MAC  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_MAC;
    for (u8 i = 0; i < LAN80XX_MAC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_host_mac[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_host_mac[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_host_mac[i].str, val1, dump_host_mac[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  LINE MAC  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_MAC;
    for (u8 i = 0; i < LAN80XX_MAC_REG_NUM; i += 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_line_mac[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_line_mac[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_line_mac[i].str, val1, dump_line_mac[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  MAC_FC_BUFFER  :-:-:-:\n\n");
    mmd = MMD_ID_MAC_FC_BUFF;
    for (u8 i = 0; i < LAN80XX_FC_BUFFER_RG_NUM; i++) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_fc_buf[i].addr, &val1));
        pr("%-40s: 0x%08X\n", dump_fc_buf[i].str, val1);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_pma_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = FALSE;
    u32 val1 = 0, val2 = 0;
    char *str;
    pr("\n\n\t\t:-:-:-:  LINE_PMA  :-:-:-:\n\n");
    mmd = MMD_ID_LINE_PMA_8BIT;
    for (u8 i = 0; i < LAN80XX_LINE_PMA_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, line_pma[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, line_pma[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", line_pma[i].str, val1, line_pma[i + 1].str, val2);
    }
    for (u8 i = 0; i < LAN80XX_PMA_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pma[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pma[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pma[i].str, val1, host_line_pma[i + 1].str, val2);
    }
    pr("\n\n\t\t:-:-:-:  HOST_PMA  :-:-:-:\n\n");
    mmd = MMD_ID_HOST_PMA_8BIT;
    for (u8 i = 0; i < LAN80XX_PMA_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pma[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, host_line_pma[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", host_line_pma[i].str, val1, host_line_pma[i + 1].str, val2);
    }

    for (u8 is_host = 0; is_host < 2; is_host++) {
        mmd = is_host ? MMD_ID_HOST_PMA_8BIT : MMD_ID_LINE_PMA_8BIT;
        str = is_host ? "HOST_PMA_EXT" : "LINE_PMA_EXT";
        pr("\n\n\t\t:-:-:-:  %s :-:-:-:\n\n", str);

        MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, is_32, 0xf0ff, 0xff));

        for (u8 i = dump_cmu_grp_0.grp_start; i <= dump_cmu_grp_0.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_0.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_0.base_addr + i + 1), &val2));
            pr("%s%-17X: 0x%08X     %s%-17X: 0x%08X\n", dump_cmu_grp_0.str, i, val1, dump_cmu_grp_0.str, (i + 1), val2);
        }

        for (u8 i = dump_cmu_grp_1.grp_start; i <= dump_cmu_grp_1.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_1.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_1.base_addr + i + 1), &val2));
            pr("%s%-17X: 0x%08X     %s%-17X: 0x%08X\n", dump_cmu_grp_1.str, i, val1, dump_cmu_grp_1.str, (i + 1), val2);
        }

        for (u8 i = dump_cmu_grp_2.grp_start; i <= dump_cmu_grp_2.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_2.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_cmu_grp_2.base_addr + i + 1), &val2));
            pr("%s%-17X: 0x%08X     %s%-17X: 0x%08X\n", dump_cmu_grp_2.str, i, val1, dump_cmu_grp_2.str, (i + 1), val2);
        }

        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, 0xF0C0, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, 0xF0FF, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", "PMA_CMU_C0", val1, "PMA_CMU_FF", val2);

        MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, is_32, 0xf0ff, 0x0));
        for (u8 i = dump_lane_grp_0.grp_start; i <= dump_lane_grp_0.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_0.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_0.base_addr + i + 1), &val2));
            pr("%s%-16X: 0x%08X     %s%-16X: 0x%08X\n", dump_lane_grp_0.str, i, val1, dump_lane_grp_0.str, (i + 1), val2);
        }

        for (u8 i = dump_lane_grp_1.grp_start; i <= dump_lane_grp_1.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_1.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_1.base_addr + i + 1), &val2));
            pr("%s%-16X: 0x%08X     %s%-16X: 0x%08X\n", dump_lane_grp_1.str, i, val1, dump_lane_grp_1.str, (i + 1), val2);
        }

        for (u8 i = dump_lane_grp_2.grp_start; i <= dump_lane_grp_2.grp_end; i += 2) {
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_2.base_addr + i), &val1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_lane_grp_2.base_addr + i + 1), &val2));
            pr("%s%-16X: 0x%08X     %s%-16X: 0x%08X\n", dump_lane_grp_2.str, i, val1, dump_lane_grp_2.str, (i + 1), val2);
        }
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_pmac_counters_get_priv(mepa_device_t                     *dev,
                                       const mepa_port_no_t              port_no,
                                       mepa_bool_t                       is_host,
                                       phy25g_pmac_counters_t            *const counters)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 cnt = 0;
    u64 cnt_64 = 0;
    memset(counters, 0, sizeof(phy25g_pmac_counters_t));

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_OK_BYTES_CNT), &cnt_64);
    counters->if_rx_good_octets = cnt_64;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_BAD_BYTES_CNT), &cnt_64);
    counters->if_rx_bad_octets = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_PAUSE_CNT), &cnt);
    counters->if_rx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_UC_CNT), &cnt);
    counters->if_rx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_MC_CNT), &cnt);
    counters->if_rx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_BC_CNT), &cnt);
    counters->if_rx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_CRC_ERR_CNT), &cnt);
    counters->if_rx_CRCAlignErrors = cnt;
    counters->if_rx_errors = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_UNDERSIZE_CNT), &cnt);
    counters->if_rx_UndersizePkts = cnt;
    if (counters->if_rx_errors > LAN80XX_32BIT_REG_MASK - cnt) {
        T_E(MEPA_TRACE_GRP_GEN, "\n if_rx_errors Overflows on port %d, Old rx_errors : %ld Last rx_errors : %ld \n", port_no, counters->if_rx_errors, cnt);
    } else {
        counters->if_rx_errors += cnt;
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_FRAGMENTS_CNT), &cnt);
    counters->if_rx_Fragments = cnt;
    if (counters->if_rx_errors > LAN80XX_32BIT_REG_MASK - cnt) {
        T_E(MEPA_TRACE_GRP_GEN, "\n if_rx_errors Overflows on port %d, Old rx_errors : %ld Last rx_errors : %ld \n", port_no, counters->if_rx_errors, cnt);
    } else {
        counters->if_rx_errors += cnt;
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_JABBERS_CNT), &cnt);
    counters->if_rx_Jabbers = cnt;
    if (counters->if_rx_errors > LAN80XX_32BIT_REG_MASK - cnt) {
        T_E(MEPA_TRACE_GRP_GEN, "\n if_rx_errors Overflows on port %d, Old rx_errors : %ld Last rx_errors : %ld \n", port_no, counters->if_rx_errors, cnt);
    } else {
        counters->if_rx_errors += cnt;
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_OVERSIZE_CNT), &cnt);
    counters->if_rx_OversizePkts = cnt;
    if (counters->if_rx_errors > LAN80XX_32BIT_REG_MASK - cnt) {
        T_E(MEPA_TRACE_GRP_GEN, "\n if_rx_errors Overflows on port %d, Old rx_errors : %ld Last rx_errors : %ld \n", port_no, counters->if_rx_errors, cnt);
    } else {
        counters->if_rx_errors += cnt;
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE64_CNT), &cnt);
    counters->if_rx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE65TO127_CNT), &cnt);
    counters->if_rx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE128TO255_CNT), &cnt);
    counters->if_rx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE256TO511_CNT), &cnt);
    counters->if_rx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE512TO1023_CNT), &cnt);
    counters->if_rx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE1024TO1518_CNT), &cnt);
    counters->if_rx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE1519TOMAX_CNT), &cnt);
    counters->if_rx_Pkts1519toMaxOctets = cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_OK_BYTES_CNT), &cnt_64);
    counters->if_tx_octets = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_PAUSE_CNT), &cnt);
    counters->if_tx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_UC_CNT), &cnt);
    counters->if_tx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_MC_CNT), &cnt);
    counters->if_tx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_BC_CNT), &cnt);
    counters->if_tx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE64_CNT), &cnt);
    counters->if_tx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE65TO127_CNT), &cnt);
    counters->if_tx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE128TO255_CNT), &cnt);
    counters->if_tx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE256TO511_CNT), &cnt);
    counters->if_tx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE512TO1023_CNT), &cnt);
    counters->if_tx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE1024TO1518_CNT), &cnt);
    counters->if_tx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE1519TOMAX_CNT), &cnt);
    counters->if_tx_Pkts1519toMaxOctets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_ALIGNMENT_LOST_CNT), &cnt);
    counters->if_rx_align_lost = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_ASSEMBLY_ERR_CNT), &cnt);
    counters->if_rx_assmbly_err = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_SMD_ERR_CNT), &cnt);
    counters->if_rx_smd_err = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_ASSEMBLY_OK_CNT), &cnt);
    counters->if_rx_assmblt_ok = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_MERGE_FRAG_CNT), &cnt);
    counters->if_rx_merge_frag = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_TX_PFRAGMENT_CNT), &cnt);
    counters->if_tx_pfrag_cnt = cnt;


    return MEPA_RC_OK;
}


mepa_rc lan80xx_pmac_counters_clear_priv(mepa_device_t                 *dev,
                                         const mepa_port_no_t          port_no,
                                         mepa_bool_t                   is_host)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_OK_BYTES_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_OK_BYTES_MSB_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_BAD_BYTES_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_BAD_BYTES_MSB_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_PAUSE_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_UC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_MC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_BC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_CRC_ERR_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_UNDERSIZE_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_FRAGMENTS_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_JABBERS_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_OVERSIZE_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE64_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE65TO127_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE128TO255_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE256TO511_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE512TO1023_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE1024TO1518_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_SIZE1519TOMAX_CNT), 0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_OK_BYTES_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_OK_BYTES_MSB_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_PAUSE_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_UC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_MC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_BC_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE64_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE65TO127_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE128TO255_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE256TO511_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE512TO1023_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE1024TO1518_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_TX_SIZE1519TOMAX_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, PMAC_RX_ALIGNMENT_LOST_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_ASSEMBLY_ERR_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_SMD_ERR_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_ASSEMBLY_OK_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_RX_MERGE_FRAG_CNT), 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_HOST_MAC_REG_EXPAN(LAN80XX, is_host, MM_TX_PFRAGMENT_CNT), 0);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_glb_workarround(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    for (u8 i = 0; i < LAN80XX_GPIO_COUNT; i++) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_GLOBAL_IO_PAD_CTRL(i), LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_OVR | LAN80XX_F_GLOBAL_IO_PAD_CTRL_PUPD_EN(1),
                        LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_OVR | LAN80XX_M_GLOBAL_IO_PAD_CTRL_PUPD_EN);
    }
    T_I(MEPA_TRACE_GRP_GEN, "\nGPIO PAD Configured to Pull Up Mode\n");

    /* JIRA "UNG_MALIBU_25G-2454" fix */
    LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_WPS0_CFG, LAN80XX_F_CROSS_CONNECT_WPS0_CFG_L0_LOCAL_CLK(0),
                    LAN80XX_M_CROSS_CONNECT_WPS0_CFG_L0_LOCAL_CLK);

    LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_WPS0_CFG, LAN80XX_F_CROSS_CONNECT_WPS0_CFG_L1_LOCAL_CLK(1),
                    LAN80XX_M_CROSS_CONNECT_WPS0_CFG_L1_LOCAL_CLK);

    LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_WPS1_CFG, LAN80XX_F_CROSS_CONNECT_WPS1_CFG_L2_LOCAL_CLK(2),
                    LAN80XX_M_CROSS_CONNECT_WPS1_CFG_L2_LOCAL_CLK);

    LAN80XX_CSR_WRM(port_no, LAN80XX_CROSS_CONNECT_WPS1_CFG, LAN80XX_F_CROSS_CONNECT_WPS1_CFG_L3_LOCAL_CLK(3),
                    LAN80XX_M_CROSS_CONNECT_WPS1_CFG_L3_LOCAL_CLK);
    T_I(MEPA_TRACE_GRP_GEN, "\nConfigured Cross-Connect Clock\n");

    return MEPA_RC_OK;
}

mepa_rc lan80xx_channel_workarround(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    /* JIRA "UNG_MALIBU_25G-2457" fix */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_SLICE_SPARE_RW_0, 0x3);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_SPARE_RW_0, 0x3);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_csr_write_priv(mepa_device_t               *dev,
                                   const mepa_port_no_t        port_no,
                                   const u32                   mmd,
                                   const u32                   addr,
                                   const u32                   value)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_bool_t is32 = lan80xx_target_reg_width(mmd, addr);
    if (mmd == MMD_ID_HOST_PMA_8BIT || mmd == MMD_ID_LINE_PMA_8BIT) {
        if (lan80xx_pma_cmu_lane_access_check(dev, port_no, mmd, addr) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Could Configure CMU_FF Register\n");
            rc = MEPA_RC_ERROR;
        }
    }

    if (lan80xx_csr_wr(dev, port_no, mmd, is32, addr, value) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not do CSR write, port_no:%d, mmd:%d, addr:%d, value:%d", port_no, mmd, addr, value);
        rc = MEPA_RC_ERROR;
    }
    return rc;
}


mepa_rc lan80xx_phy_csr_read_priv(mepa_device_t               *dev,
                                  const mepa_port_no_t        port_no,
                                  const u16                   mmd,
                                  const u32                   addr,
                                  u32                         *const value)
{
    mepa_rc rc = MEPA_RC_OK;
    mepa_bool_t is32 = lan80xx_target_reg_width(mmd, addr);
    u32 read;

    if (mmd == MMD_ID_HOST_PMA_8BIT || mmd == MMD_ID_LINE_PMA_8BIT) {
        if (lan80xx_pma_cmu_lane_access_check(dev, port_no, mmd, addr) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Could Configure CMU_FF Register\n");
            rc = MEPA_RC_ERROR;
        }
    }

    if (lan80xx_csr_rd(dev, port_no, mmd, is32, addr, &read) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not do CSR read, port_no:%d, mmd:%d,  addr:%d", port_no, mmd, addr);
        rc = MEPA_RC_ERROR;
    }
    *value = read;
    return rc;
}

mepa_rc lan80xx_mamcsec_mem_free(mepa_device_t *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    T_I(MEPA_TRACE_GRP_GEN, "\n Deallocating MACsec Memory if allocated on port : %d\n", data->port_no);
    if (data->inst_counts.secy_vport != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, data->inst_counts.secy_vport);
        data->inst_counts.secy_vport = NULL;
    }

    if (data->inst_counts.secy_inst_count != NULL) {
        if (data->inst_counts.secy_inst_count->rxsc_id != NULL) {
            mepa_mem_free_int(dev->callout, dev->callout_ctx, data->inst_counts.secy_inst_count->rxsc_id);
            data->inst_counts.secy_inst_count->rxsc_id = NULL;
        }

        if (data->inst_counts.secy_inst_count->rx_sci != NULL) {
            mepa_mem_free_int(dev->callout, dev->callout_ctx, data->inst_counts.secy_inst_count->rx_sci);
            data->inst_counts.secy_inst_count->rx_sci = NULL;
        }

        if (data->inst_counts.secy_inst_count->rxsc_inst_count != NULL) {
            mepa_mem_free_int(dev->callout, dev->callout_ctx, data->inst_counts.secy_inst_count->rxsc_inst_count);
            data->inst_counts.secy_inst_count->rxsc_inst_count = NULL;
        }
        mepa_mem_free_int(dev->callout, dev->callout_ctx, data->inst_counts.secy_inst_count);
        data->inst_counts.secy_inst_count = NULL;
    }
    return MEPA_RC_OK;
}

uint32_t lan80xx_phy_capability_priv(struct mepa_device *dev, uint32_t capability)
{
    uint32_t c = 0;
    switch (capability) {
    case MEPA_CAP_MACSEC_SECY_CNT:
        c = LAN80XX_MACSEC_MAX_SA / 2;
        break;
    case MEPA_CAP_MACSEC_MAX_SA:
        c = LAN80XX_MACSEC_MAX_SA;
        break;
    case MEPA_CAP_MACSEC_MAX_SC:
        c = LAN80XX_MACSEC_MAX_SA / 2;
        break;
    }
    return c;
}

mepa_rc lan80xx_flow_control_set_priv(const mepa_device_t     *dev,
                                      mepa_port_no_t          port_no,
                                      mepa_bool_t             enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        T_E(MEPA_TRACE_GRP_GEN, "\n Flow Control not supported in PCS Retimer Mode, switch Port : %d to MAC Retimer\n", port_no);
        return MEPA_RC_ERROR;
    }
    if (enable) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG,
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_PAUSE_GEN_ENA,
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_PAUSE_REACT_ENA |
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_PAUSE_GEN_ENA |
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_CTRL_QUEUE_ENA |
                        LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_INCLUDE_PAUSE_RCVD_IN_PAUSE_GEN);

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL,
                        LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE,
                        LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA |
                        LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA |
                        LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE |
                        LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL,
                        LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE,
                        LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA |
                        LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE |
                        LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA |
                        LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA);

        data->flow_control_ena = 1;
        return MEPA_RC_OK;
    }

    LAN80XX_CSR_WRM(port_no, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG, 0,
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_PAUSE_REACT_ENA |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_PAUSE_GEN_ENA |
                    LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_INCLUDE_PAUSE_RCVD_IN_PAUSE_GEN);

    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL,
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA,
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_EARLY_PAUSE_DETECT_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE |
                    LAN80XX_M_LINE_MAC_LINE_MAC_PAUSE_RX_FRAME_CONTROL_MAC_TX_PAUSE_REACT_ENA);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL,
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA,
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_TIMER_ENA |
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_MODE |
                    LAN80XX_M_HOST_MAC_HOST_MAC_PAUSE_RX_FRAME_CONTROL_MAC_RX_PAUSE_FRAME_DROP_ENA);

    data->flow_control_ena = 0;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ram_init(mepa_device_t    *dev, mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;
    u32 val = 0;

    T_IM(data->port_no,"POST 1 RAM INIT Triggered on Port : %d\n", port_no);
    /* Read Channel ID */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_SLICE_SPARE_RW_0, &val);
    u8 channel_id =  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(val);

    /* Update BIST BYPASS Strap Configuration */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS,
                    LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_BIST_BYPASS);

    /* As BIST is Bypass Consider BIST is Passed */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, (LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS << channel_id),
                    (LAN80XX_M_MCU_IO_MNGT_MISC_POST1_POST_STATUS_P1_POST_SLICE0_PASS << channel_id));

    /* UNG_MALIBU_25G-1973: Configure TX & RX clock of SERDES muxing and enable MAC_RETIMING MODE */
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Enable MAC Retimer Mode (Bit 7) and Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, (LAN80XX_BIT(7) | LAN80XX_BIT(8)),
                        (LAN80XX_BIT(7) | LAN80XX_BIT(8)));
    } else {
        /* Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_BIT(8), LAN80XX_BIT(8));
    }

    /* UNG_MALIBU_25G-2469: some synchronizers in path and some MAC and MACSEC SW_RST bits have to be first cleared */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST);

    /* POST 1 RAM Init */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT, LAN80XX_POST1_TRIGGER);

    /* Wait for 50us to do RAM Initialization */
    MEPA_NSLEEP(50000);

    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Switch to PCS Retimer mode back and Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0x0, LAN80XX_BIT(7) | LAN80XX_BIT(8));
    } else {
        /* Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_BIT(8));
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT_BUSY, &val);

    if (val != 0) {
        T_E(MEPA_TRACE_GRP_GEN, "POST 1 Ram Initialization Failed on Port : %d \n", port_no);
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_INIT_STATUS_ADDR + channel_id)),  0, LAN80XX_POST1_TRIGGER);
        base_data->post1_passed = 0;
        rc = MEPA_RC_ERROR;
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_INIT_STATUS_ADDR + channel_id)),  LAN80XX_POST1_TRIGGER,
                        LAN80XX_POST1_TRIGGER);
    }
    return rc;
}

static mepa_rc lan80xx_post1_bist_trigger(mepa_device_t  *dev, mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    mepa_rc rc = MEPA_RC_OK;
    u32 val = 0;

    T_IM(data->port_no,"POST 1 BIST Trigger on Port : %d\n", port_no);
    /* Read Channel ID */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_SLICE_SPARE_RW_0, &val);
    u8 channel_id =  LAN80XX_X_HOST_SLICE_SPARE_RW_0_SPARE_RW_0_CHN_ID(val);

    /* UNG_MALIBU_25G-1973: Configure TX & RX clock of SERDES muxing and enable MAC_RETIMING MODE */
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Enable MAC Retimer Mode (Bit 7) and Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, (LAN80XX_BIT(7) | LAN80XX_BIT(8)),
                        (LAN80XX_BIT(7) | LAN80XX_BIT(8)));
    } else {
        /* Switch DESCLK with SERCLK at BIST (Bit 8) */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_BIT(8), LAN80XX_BIT(8));
    }

    /* UNG_MALIBU_25G-2469: some synchronizers in path and some MAC and MACSEC SW_RST bits have to be first cleared */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_LINE_MAC_LINE_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG, 0,
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_RX_SW_RST |
                    LAN80XX_M_HOST_MAC_HOST_MAC_MAC_ENA_CFG_TX_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST);

    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, 0, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_BIST1_GO, LAN80XX_POST1_TRIGGER);

    /* Wait for 350us to run BIST */
    MEPA_NSLEEP(350000);

    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        /* Switch to PCS Retimer mode back and Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0x0, LAN80XX_BIT(7) | LAN80XX_BIT(8));
    } else {
        /* Do not replace DESCLK with SERCLK */
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_BIT(8));
    }

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_BIST1_STATUS, &val);
    T_I(MEPA_TRACE_GRP_GEN, "POST 1 BIST Status on Port : 0x%x\n", val);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_STATUS_ADDR + channel_id)), val);

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_SLICE_BIST1_RESULT, &val);
    T_I(MEPA_TRACE_GRP_GEN, "POST 1 BIST Result on Port : 0x%x\n", val);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_RESULT_ADDR + channel_id)), val);

    if (val != LAN80XX_POST1_TRIGGER) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_IOREG(MMD_ID_MCU_IO_MNGT_MISC, 0, (LAN80XX_POST1_SLICE0_BIST_STATUS_ADDR + channel_id)),
                        LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO,
                        LAN80XX_M_MCU_IO_MNGT_MISC_POST1_SLICE0_BIST_STATUS_P1_SLICE0_BIST_TO)

        T_EM(data->port_no,"POST 1 Init Failed on Port : %d\n", port_no);
        base_data->post1_passed = 0;
        rc = MEPA_RC_ERROR;
    }
    return rc;
}

mepa_rc lan80xx_post1_init_priv(mepa_device_t   *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    u32 val = 0;
    mepa_rc rc = MEPA_RC_OK;
    base_data->post1_passed = 1;

    if (data->port_state.power != LAN80XX_PHY_POWER_ENABLE) {
        /* Performing Serdes Configuration to Enable Serdes Clocks to Perform POST 1 */
        if (lan80xx_serdes_configuration(dev, port_no, MESA_SPEED_10G, &data->port_state.port_mode) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Serdes Init Failed on Port : %d \n", data->port_no);
            return MEPA_RC_ERROR;
        }
    }
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &val);

    /* A0 and A1 BIST Failed in RTL, so BIST BYPASS STRAP should be 1 */
    if (data->dev.rev == LAN80XX_REV_A0 || data->dev.rev == LAN80XX_REV_A1) {
        val = val | LAN80XX_BIST_BYPASS_STRAP;
    }
    for (u8 i = 0; i < base_data->max_port_cnt; i++) {

        if (base_data->other_port_dev[i] == NULL) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Port %d Instance is not available in Base Dev \n", base_data->chip_ports[i]);
            base_data->post1_passed = 0;
            return MEPA_RC_ERROR;
        }

        if (val & LAN80XX_BIST_BYPASS_STRAP) {
            rc = lan80xx_ram_init(base_data->other_port_dev[i], base_data->chip_ports[i]);
        } else {
            rc = lan80xx_post1_bist_trigger(base_data->other_port_dev[i], base_data->chip_ports[i]);
        }
    }
    if ((base_data->post1_passed == 1)) {
        /* Update POST 1 Done */
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, LAN80XX_POST1_STATUS_P1_POST_DONE, LAN80XX_POST1_STATUS_P1_POST_DONE);
    } else {
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_MCU_IO_MNGT_MISC_POST1_POST_STATUS, 0, LAN80XX_POST1_STATUS_P1_POST_DONE);
        rc = MEPA_RC_ERROR;
    }
    T_IM(data->port_no,"POST1 INIT Done\n");
    return rc;
}

mepa_rc lan80xx_check_mcu_rdy_priv(mepa_device_t *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val;
    mepa_rc rc = MEPA_RC_ERROR;

    T_DM(data->port_no,"Checking MCU ready status...\n");
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &val);
    if (val & 0x4) {
        T_IM(data->port_no,"%s MCU ready ", __FUNCTION__);
        rc = MEPA_RC_OK;
    } else {
        T_EM(data->port_no,"%s Error in MCU ready ", __FUNCTION__);
        rc = MEPA_RC_ERROR;
    }
    return rc;
}

mepa_rc lan80xx_mcu_mailbox_init_priv(const mepa_device_t *dev, u32 u32McuIntMask, u32 u32HostIntMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;

    T_IM(data->port_no,"Enabling MB host mask...\n");
    /* Enable Host interrupt mask register */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_HOST_INT_MASK, u32HostIntMask, LAN80XX_BIT(1));
    T_IM(data->port_no,"Enabling MB mcu mask...\n");
    /* Enable MCU interrupt mask register */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_MCU_MAILBOX_MAILBOX_MCU_INT_MASK, u32McuIntMask, LAN80XX_BIT(0));
    T_IM(data->port_no,"Enabling MB src en...\n");
    /* Enable INTR_SRC_EN_1 with mailbox interrupt */
    LAN80XX_CSR_WRM(data->port_no, LAN80XX_GPIO_CTRL_INTR_SRC_EN(1), LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN,
                    LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN);
    return rc;
}

static uint16_t crc_16(const unsigned char *input, size_t num_bytes)
{
    uint8_t i;
    uint16_t u16crc;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    T_D(MEPA_TRACE_GRP_GEN, "calculating CRC");
    u16crc = CRC_START_CCITT;
    while (num_bytes--) {
        u16crc ^= *(unsigned char *)input++ << 8;
        for (i = 0; i < 8; i++) {
            u16crc = u16crc & 0x8000 ? (u16crc << 1) ^ CRC_POLY_CCITT : u16crc << 1;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "CRC: 0x%04x", u16crc);

    return u16crc & CRC_START_CCITT;
}

static void packet_dump(u8 *pu8PktBuf)
{
    u8 idx = 0;
    PKT_HDR_T *pPktHdr = (PKT_HDR_T *)pu8PktBuf;
    u16 u16Len = (pPktHdr->u16PktLen > MB_MAX_PAYLOAD_LEN) ? MB_MAX_PAYLOAD_LEN : pPktHdr->u16PktLen;

    T_E(MEPA_TRACE_GRP_GEN, "***** PKT DUMP BEGIN *****\n");
    for (idx = 0; idx < u16Len; idx += 4) {
        T_E(MEPA_TRACE_GRP_GEN, "0x%02x 0x%02x 0x%02x 0x%02x\n",
            pu8PktBuf[idx], pu8PktBuf[idx + 1], pu8PktBuf[idx + 2], pu8PktBuf[idx + 3]);
    }
    T_E(MEPA_TRACE_GRP_GEN, "***** PKT DUMP END *****\n");
}

/*
* FN: lan80xx_CreatePacket
* This function is used to create request packet to used for Host communication
* Reference: DOS-05247 Malibu-25G Optical PHY Product Firmware DOS
* Section 8.3.1 Request Packet Format
* offset    Size(B)     Name                        Value
* 0x00      1           Request Packet ID           PKT_ID
* 0x01      1           Reserved                    0xFF
* 0x02      2           Request Packet Length       Total Request packet length (max is 1024)
* 0x04      N           Request Data                Request data of N bytes
* 0x04+N    2           CRC16                       CRC16
*
* Device Commands:
* GET_DEVICE_INFO - 0x00
* DEVICE_RESET - 0x01
* MEM_READ  -   0x06
* MEM_WRITE - 0x07
* DFU_UPDATE - 0x0B
*/
uint16_t lan80xx_CreatePacket(uint8_t u8PacketId, uint16_t u16CmdParamLen, uint8_t *pu8PktBuf, uint8_t *pu8CmdData, uint8_t u8Reserved)
{
    uint16_t u16Len = 0;
    PKT_HDR_T *PktHdr = (PKT_HDR_T *)pu8PktBuf;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    u16Len = u16CmdParamLen + MB_MAX_PKT_HEADER_LEN + MB_MAX_CRC_LEN;
    T_D(MEPA_TRACE_GRP_GEN, "Creating packet with pkt id: 0x%x of len: 0x%x", u8PacketId, u16Len);
    PktHdr->u8PktId = u8PacketId;
    PktHdr->u8Reserved = u8Reserved;
    PktHdr->u16PktLen = u16Len;
    if ((pu8CmdData != NULL) && (u16CmdParamLen > 0)) {
        T_D(MEPA_TRACE_GRP_GEN, "Copying cmd parameter data of length %d", u16CmdParamLen);
        memcpy(&pu8PktBuf[MB_PKT_DATA_OFFSET], pu8CmdData, u16CmdParamLen);
    }

    //Add CRC16 to the end
    T_D(MEPA_TRACE_GRP_GEN, "Adding CRC")
    uint16_t u16CRC = crc_16(pu8PktBuf, u16CmdParamLen + MB_MAX_PKT_HEADER_LEN);
    uint16_t *pu16PktCrc = (uint16_t *)(pu8PktBuf + MB_PKT_DATA_OFFSET + u16CmdParamLen);
    *pu16PktCrc = u16CRC;
    T_D(MEPA_TRACE_GRP_GEN, "Created packet of length %d", u16Len);

    return u16Len;
}

static mepa_rc ValidateCRC(uint8_t *pu8PktBuf, uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16CRC = 0, u16PktCRC = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    /* compute crc */
    u16CRC = crc_16(pu8PktBuf, u16Len);
    /* extract packet crc */
    u16PktCRC = MAKEWORD(pu8PktBuf[u16Len], pu8PktBuf[u16Len + 1]);
    /* Now compare crc */
    if (u16CRC != u16PktCRC) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. CRC Error , Expected CRC : %lu ,\
            Calculated CRC : %lu", __FUNCTION__, u16CRC, u16PktCRC);
        /* crc match failed */
        rc = MEPA_RC_ERR_MB_INVALID_CRC;
    }

    return rc;
}

mepa_rc lan80xx_ValidatePacket(uint8_t *u8PktBuf)
{
    mepa_rc rc = MEPA_RC_OK;
    PKT_HDR_T *pPktHdr = (PKT_HDR_T *)u8PktBuf;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    /* Payload can not be more than MAX_PKT_LEN */
    if (pPktHdr->u16PktLen > MB_MAX_PKT_LEN) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid Pkt length 0x%x, \
                Validate Packet failed ", __FUNCTION__, pPktHdr->u16PktLen);
        /* invalid packet payload length */
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }
    rc = ValidateCRC(u8PktBuf, (pPktHdr->u16PktLen - MB_MAX_CRC_LEN));
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid CRC, Validate Packet failed", __FUNCTION__);
        /* Packet crc validation failed */
        packet_dump(u8PktBuf);
    }
    return rc;
}


/*
* Fn: MB_ClearResponseFlag
* This function is used to clear Response Flag
* Mailbox Flag Register - 0xDA00 (Bit 31:24)
*/
static mepa_rc lan80xx_MB_ClearFlag(const mepa_device_t *dev, uint32_t u32ClearMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Clear flag mask: 0x%x", u32ClearMask);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), u32ClearMask);

    return rc;
}

/*
* Fn: MB_SetRequestFlag
* This function is used to set Request Flag
* Mailbox MCU Interrupt Mask Register - 0xDA01
* Mailbox Flag Register - 0xDA00 (Bit 23:16)
*/
static mepa_rc lan80xx_MB_SetFlag(const mepa_device_t *dev, uint32_t u32SetMask)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "Device not created!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    T_D(MEPA_TRACE_GRP_GEN, "Set flag mask: 0x%x", u32SetMask);
    LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), u32SetMask);

    return rc;
}

mepa_rc lan80xx_MB_SendRequest(const mepa_device_t *dev, uint8_t *au8CmdPkt, uint16_t u16DataLen)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint16_t u16Counter = 0;
    uint32_t u32SpiData = 0x00000000;
    uint16_t u16Reg = MAILBOX_CMD_ADDR;

    T_I(MEPA_TRACE_GRP_GEN, "%s\n", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "device not registered!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);
    /* Rounding off the packet length into multiples of 4 to facilitate SPI read/write */
    if (u16DataLen % SPI_VAL_LEN != 0) {
        u16DataLen += (SPI_VAL_LEN - (u16DataLen % 4));
    }

    T_D(MEPA_TRACE_GRP_GEN, "Writing pkt to mailbox request area\n");
    while (u16DataLen) {
        u32SpiData = 0;
        u32SpiData = (au8CmdPkt[u16Counter + 3] << 24 | au8CmdPkt[u16Counter + 2] << 16 | \
                      au8CmdPkt[u16Counter + 1] << 8 | au8CmdPkt[u16Counter]);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, u16Reg), u32SpiData);

        u16Reg++;
        u16Counter += SPI_VAL_LEN;
        u16DataLen -= SPI_VAL_LEN;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Pkt written, checking MCU busy status...\n");
    uint8_t u8McuInterrupt = 0;
    if (base_data->ft_gpio_read == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "INTR_A/B callback not registered!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;

    }
    u8McuInterrupt = base_data->ft_gpio_read(dev);
    uint32_t u32Val = 0;
    if (1 == u8McuInterrupt) {
        /*
         * The Host interrupt shall be set due to multiple reasons
         * check MCU interrupt flag is set or not
         * If set, wait until it clears
         * We should not overwrite the request area
         */
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
        if (u32Val & MAILBOX_INTR_ENABLE) {
            T_W(MEPA_TRACE_GRP_GEN, "MCU busy with older command, Waiting for MCU ready...");
        }
        while (u32Val & MAILBOX_INTR_ENABLE) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "Raising MCU interrupt");
    /* Enable MCU interrupt mask register */
    u32Val = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), &u32Val);
    u32Val |= MAILBOX_INTR_ENABLE;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), u32Val);
    /* Set flag */
    rc = lan80xx_MB_SetFlag(dev, MAILBOX_FLAG_SET_BIT0);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Failed to Set Mailbox Request Flag: %d", __FUNCTION__, rc);
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Request packet sent");
    }
    return rc;
}

/*
* Fn: MB_ReadResponse
* This function is uses Host communication protocol to receive data from the Host application
* Response buffer - D900 to D9FF
*/
mepa_rc lan80xx_MB_ReadResponse(const mepa_device_t *dev, uint8_t *u8ResponsePkt, uint16_t *u16PayloadLen, uint16_t u16MailboxTimeout)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16Timeout = 0;
    uint8_t u8McuInterrupt = 0;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint32_t u32Val = 0x00000000;
    uint16_t u16PktLen;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    T_D (MEPA_TRACE_GRP_GEN, "Waiting for HOST interrupt...");
    while (1) {
        u8McuInterrupt = base_data->ft_gpio_read(dev);
        /*
         * If interrupt is set, then make sure HOST interrupt is set before reading response
         */
        if (u8McuInterrupt) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
            if (u32Val & MAILBOX_HOST_INTR_MASK) {
                /* This is valid for mailbox command */
                T_I(MEPA_TRACE_GRP_GEN, "Got Host interrupt! Took %d msec", u16Timeout);
                break;
            }
        }
        MEPA_MSLEEP(1);
        u16Timeout++;
        if (u16Timeout > u16MailboxTimeout) {
            break;
        }
    }
    if (u16Timeout > u16MailboxTimeout) {
        T_EM(data->port_no,"%s: Timeout. No response from MCU", __FUNCTION__);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
        T_E(MEPA_TRACE_GRP_GEN, "MB Flag:0x%x\n", u32Val);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_HOST_INTR_MASK_REGISTER), &u32Val);
        T_E(MEPA_TRACE_GRP_GEN, "MB HOST INTR Mask reg:0x%x\n", u32Val);
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), &u32Val);
        T_E(MEPA_TRACE_GRP_GEN, "MB MCU INTR Mask reg:0x%x\n", u32Val);
        /*
        * Clear MCU request flag using Set function
        */
        lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT0);
        rc = MEPA_RC_ERR_MB_RESP_TIMEOUT;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Reading response packet...");
    if (u8McuInterrupt) {
        //Read Response

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_RESP_ADDR), &u32Val);

        PKT_HDR_T *pPktHdr = (PKT_HDR_T *)&u32Val;
        if (pPktHdr->u16PktLen == 0) {
            /* Clear HOST interrupt flag */
            lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);
            T_EM(data->port_no,"%s: Response packet length is 0, pkt: 0x%x\n", __FUNCTION__, u32Val);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        *u16PayloadLen = pPktHdr->u16PktLen;

        u8ResponsePkt[0] = u32Val & 0xFF;
        u8ResponsePkt[1] = u32Val >> 8 & 0xFF;
        u8ResponsePkt[2] = u32Val >> 16 & 0xFF;
        u8ResponsePkt[3] = u32Val >> 24 & 0xFF;

        /*Rounding off the pktlen to read in multiples of 4 (Mailbox read size)*/
        if (pPktHdr->u16PktLen & 0x03) {
            u16PktLen = (pPktHdr->u16PktLen) + (4 - (pPktHdr->u16PktLen & 0x03));
        } else {
            u16PktLen = pPktHdr->u16PktLen;
        }

        /*Read rest of the mailbox response*/
        uint16_t u16Counter = 4;
        uint16_t u16Reg = MAILBOX_RESP_ADDR + 1;

        while (u16Counter < u16PktLen) {
            u32Val = 0x00000000;

            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, u16Reg), &u32Val);

            u8ResponsePkt[u16Counter] = u32Val & 0xFF;
            u8ResponsePkt[u16Counter + 1] = u32Val >> 8 & 0xFF;
            u8ResponsePkt[u16Counter + 2] = u32Val >> 16 & 0xFF;
            u8ResponsePkt[u16Counter + 3] = u32Val >> 24 & 0xFF;
            u16Reg += 1;
            u16Counter += 4;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "Read full response of length 0x%x", u16PktLen);
    T_D(MEPA_TRACE_GRP_GEN, "clearing HOST interrupt...");

    rc = lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);
    if ((rc != MEPA_RC_OK)) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Failed to clear response flag", __FUNCTION__);
    }

    return rc;
}

mepa_rc lan80xx_get_fw_info_priv(const mepa_device_t *dev, DEVICE_INFO *psDevInfo)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(eGET_DEVICE_INFO, 0, au8CmdBuffer, NULL, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eGET_DEVICE_INFO + 0x80) {
        psDevInfo->PartId = (uint16_t)(pu8Payload[0]) | (pu8Payload[1] << 8);
        psDevInfo->TargetId = pu8Payload[2];
        psDevInfo->ImageType = (enIMAGE_TYPE_T)(pu8Payload[3]);
        psDevInfo->FirmwareVersion = ((uint16_t)pu8Payload[4] << 8) | pu8Payload[5];
        T_I(MEPA_TRACE_GRP_GEN, "%s. Success", __FUNCTION__);
        T_I(MEPA_TRACE_GRP_GEN, "Part ID: 0x%x\n", psDevInfo->PartId);
        T_I(MEPA_TRACE_GRP_GEN, "Target ID: 0x%x\n", psDevInfo->TargetId);
        T_I(MEPA_TRACE_GRP_GEN, "Image Type: 0x%x\n", psDevInfo->ImageType);
        T_I(MEPA_TRACE_GRP_GEN, "Firmware Version: %02d.%02d\n", pu8Payload[4], pu8Payload[5]);
    } else {
        if (recvPkt->u8PktId == eGET_DEVICE_INFO + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eGET_DEVICE_INFO);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

mepa_rc lan80xx_memory_read_priv(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PayloadLen = 0;
    uint8_t au8CmdParam[8] = { 0 };

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    if (u16Len > MB_MAX_PAYLOAD_LEN) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid length. Max supported length is: %d", __FUNCTION__, MB_MAX_PAYLOAD_LEN);
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }

    T_D (MEPA_TRACE_GRP_GEN, "Reading from address 0x%04X of length %d", u32Addres, u16Len);
    /* Step 1: Create Packet */
    /* 32 bit address */
    au8CmdParam[0] = (u32Addres) & 0xff;
    au8CmdParam[1] = (u32Addres >> 8) & 0xff;
    au8CmdParam[2] = (u32Addres >> 16) & 0xff;
    au8CmdParam[3] = (u32Addres >> 24) & 0xff;

    /*16 bit length */
    au8CmdParam[4] = (u16Len) & 0xFF;
    au8CmdParam[5] = (u16Len >> 8) & 0xFF;

    uint16_t u16PktLen = lan80xx_CreatePacket(eMEM_READ, 6, au8CmdBuffer, &au8CmdParam[0], RESERVED_ID);

    /* Step 2: Send Command */
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /*Step 4: Validate Response packet */
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: pkt validate failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    /*If response parameter length < 2, error response */
    if (recvPkt->u8PktId == eMEM_READ + 0x80) {
        /*Extracting len and data bytes from packet */
        uint16_t u16DataLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        memcpy(pu8Data, &pu8Payload[0], u16DataLen);
        T_I(MEPA_TRACE_GRP_GEN, "%s: Success with len %d", __FUNCTION__, u16DataLen);
    } else {
        if (recvPkt->u8PktId == eMEM_READ + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eMEM_READ);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

mepa_rc lan80xx_memory_write_priv(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16RespLen = 0;
    uint16_t u16CmdParamLen = 0;

    /* Form command parameter array for Packet data */
    uint8_t au8cmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    if (u16Len > (MB_MAX_PAYLOAD_LEN - 6)) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: Invalid length! Maximum writable per packet is (%d) Bytes", \
            __FUNCTION__, (MB_MAX_PAYLOAD_LEN - 6));
        rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
        return rc;
    }

    T_D (MEPA_TRACE_GRP_GEN, "MEM Write at 0x%04X of length %d", u32Addres, u16Len);
    /* Step 1: Create Packet */
    /* 32 bit address */
    au8cmdParam[0] = (u32Addres) & 0xff;
    au8cmdParam[1] = (u32Addres >> 8) & 0xff;
    au8cmdParam[2] = (u32Addres >> 16) & 0xff;
    au8cmdParam[3] = (u32Addres >> 24) & 0xff;

    /*16 bit length */
    au8cmdParam[4] = (u16Len) & 0xFF;
    au8cmdParam[5] = (u16Len >> 8) & 0xFF;
    u16CmdParamLen = 6;

    /* Copy Data bytes of length wLen */
    memcpy(&au8cmdParam[u16CmdParamLen], &pu8Data[0], u16Len);
    u16CmdParamLen += u16Len;

    uint16_t u16PktLen = lan80xx_CreatePacket(eMEM_WRITE, u16CmdParamLen, au8CmdBuffer, &au8cmdParam[0], RESERVED_ID);

    /* Step 2: Send Command*/
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox send command failed ", __FUNCTION__);
        return rc;
    }

    /* Step 3: Read response from Mailbox area into response buffer */
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16RespLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox read response failed ", __FUNCTION__);
        return rc;
    }

    /* Step 4: Validate packet */
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s: pkt validate failed", __FUNCTION__);
        return rc;
    }

    /* Decode the response packet to read the message */
    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    if (recvPkt->u8PktId == eMEM_WRITE + 0x80) {
        T_I(MEPA_TRACE_GRP_GEN, "%s:Memory write success", __FUNCTION__);
    } else {
        if (recvPkt->u8PktId == eMEM_WRITE + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eMEM_WRITE);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

mepa_rc lan80xx_mcu_reset_priv(const mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    // Step 1: Create Packet for Reset
    u16PktLen = lan80xx_CreatePacket(eDEVICE_RESET, 0, au8CmdBuffer, NULL, RESERVED_ID);

    // Step 2: Send command
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Mailbox send command failed ", __FUNCTION__);
        return rc;
    }

    //Step 3: Clear Response Flasg
    rc = lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT1);

    return rc;
}

static mepa_rc authenticate_fw_image()
{
    mepa_rc rc = MEPA_RC_OK;
    struct sha256_buff sha256_ctx;
    unsigned char sha256_out[32] = {0};

    sha256_init(&sha256_ctx);
    sha256_update(&sha256_ctx, gau8FwImageData, gu32FwImageLen);
    sha256_finalize(&sha256_ctx);
    sha256_read(&sha256_ctx, sha256_out);
    /*
     * Compare the calculated sha256 checksum
     * with one that come along with firmware image
     */
    if (memcmp(sha256_out, gau8Sha256Sum, 32) != 0) {
        T_E(MEPA_TRACE_GRP_GEN, "SHA checksum failed!");
        rc = MEPA_RC_ERROR;
    }

    return rc;
}

mepa_rc lan80xx_fw_update_priv(mepa_device_t *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = NULL;
    mepa_port_no_t port_no = 0;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16RespLen = 0;
    uint8_t au8CmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };
    uint32_t u32Val = 0;
    uint16_t u16Timeout = 0;
    uint8_t u8McuInterrupt = 0;
    uint16_t u16Count = 0;
    uint32_t u32Offset = 0, u32BytesWritten = 0;
    uint16_t u16CmdParamLen = 0;
    uint32_t u32Size = gu32FwImageLen;
    uint8_t *pu8FwData = gau8FwImageData;
#ifdef DFU_PROFILING_EN
    uint64_t u64Dfu_time_ms = 0;
    uint64_t u64DfuStart_time_ms = 0, u64DfuStop_time_ms = 0;
#endif

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);

    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

#ifdef DFU_PROFILING_EN
    u64DfuStart_time_ms = MEPA_UPTIME_MSECONDS();
#endif

    data = (phy25g_phy_state_t *)dev->data;
    port_no = data->port_no;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    /* Without INTR_A/B DFU can't be handled */
    if (base_data->ft_gpio_read == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "INTR_A/B callback not registered!\n");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    /* perform SHA256 authentication, send to MCU only if SHA is valid */
    rc = authenticate_fw_image();
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "FW image SHA Authentication failed\n");
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "FW image SHA authentication success!!\n");
    /* Set the DFU Strap Register*/
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
    u32Val |= DFU_STRAP;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);

    /* Read back DFU Strap */
    u16Timeout = 0;
    while (1) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        if (u32Val & DFU_STRAP) {
            break;
        }
        MEPA_NSLEEP(1000);
        u16Timeout++;
        if (u16Timeout > MAILBOX_INTR_TIMEOUT) {
            break;
        }
    }

    if (u16Timeout > MAILBOX_INTR_TIMEOUT) {
        T_EM(data->port_no,"%s. DFU Strap not set, Abort Firmware Update", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Resetting MCU...");
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_GLOBAL_REGISTERS, 1, BLOCK_LVL_SOFT_RESET2), SW_RESET_MCU);

    T_IM(data->port_no,"Waiting for FW to enter DFU mode...\n");
    u16Timeout = 0;
    while (u16Timeout <= MAILBOX_INTR_TIMEOUT)
    {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_MCU_IO_MNGT_MISC_MCU_BOOT_STATUS_REG, &u32Val);
        if (u32Val == BOOT_STS_DFU_MODE)
        {
            /* DFU mode */
            break;
        }
        MEPA_MSLEEP(1);
        u16Timeout++;
        if (u16Timeout > MAILBOX_INTR_TIMEOUT)
        {
            T_E(MEPA_TRACE_GRP_GEN, "FW Failed to enter DFU mode [BOOT_STS: %d]\n", u32Val);
            rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
            return rc;
        }
    }
    /* Configure Mailbox MCU and Host interrupt mask after reset */
    rc = lan80xx_mcu_mailbox_init_priv(dev, MAILBOX_INTR_ENABLE, MAILBOX_HOST_INTR_MASK);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "mailbox init failed\n");
        return rc;
    }
    T_IM(data->port_no,"Waiting for First packet interrupt...\n");
    // Wait for DFU first packet Interrupt
    u16Timeout = 0;
    while (1) {
        u8McuInterrupt = base_data->ft_gpio_read(dev);
        if (u8McuInterrupt) {
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
            if (u32Val & MAILBOX_DFU_FIRST_PKT) {
                /* This is valid for mailbox command */
                T_I(MEPA_TRACE_GRP_GEN, "Got first packet interrupt! Took %d msec", u16Timeout);
                break;
            }
        }

        MEPA_MSLEEP(1);
        u16Timeout++;
        if (u16Timeout > (MAILBOX_INTR_TIMEOUT)) {
            break;
        }
    }
    /* Clear first packet interrupt */
    lan80xx_MB_ClearFlag(dev, MAILBOX_FLAG_CLEAR_BIT6);

    if (u8McuInterrupt && (u16Timeout < MAILBOX_INTR_TIMEOUT)) {
        /* UNG_MALIBU_25G-2476 Workaround */
        uint8_t byDataBuffer[4] = {0};
        lan80xx_memory_read_priv(dev, LAN80XX_MCU_CODE_RAM_START_REGION, byDataBuffer, 4);
        lan80xx_memory_read_priv(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_ONE_OFFSET, byDataBuffer, 4);
        lan80xx_memory_read_priv(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_TWO_OFFSET, byDataBuffer, 4);
        lan80xx_memory_read_priv(dev, LAN80XX_MCU_CODE_RAM_START_REGION + LAN80XX_MEMORY_SLICE_THREE_OFFSET, byDataBuffer, 4);
        do {
            u16Count++;
            T_IM(data->port_no,"Sending DFU packet %d...\n", u16Count);
            if ((u32Offset + MB_MAX_PAYLOAD_LEN) > u32Size) {
                u16CmdParamLen = u32Size - u32Offset;
            } else {
                u16CmdParamLen = MB_MAX_PAYLOAD_LEN;
            }
            u32BytesWritten += u16CmdParamLen;

            memcpy(&au8CmdParam[0], &pu8FwData[u32Offset], u16CmdParamLen);

            /* Create Packet */
            uint16_t u16PktLen = lan80xx_CreatePacket(eDFU_UPDATE, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

            if (MEPA_RC_OK != (rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Mailbox send command failed at packet %d", __FUNCTION__, u16Count);
                break;
            }

            if (MEPA_RC_OK != (rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16RespLen, MAILBOX_INTR_TIMEOUT))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Mailbox read response for DFU command failed at packet %d", __FUNCTION__, u16Count);
                break;
            }

            PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
            if (recvPkt->u8PktId == eDFU_UPDATE + 0x80) {
                T_IM(data->port_no,"%s:DFU Packet %d success", __FUNCTION__, u16Count);
            } else {
                if (recvPkt->u8PktId == eDFU_UPDATE + 0x81) {
                    T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
                    rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
                } else {
                    T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                        __FUNCTION__, (recvPkt->u8PktId - 0x80), eDFU_UPDATE);
                    rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
                }
                packet_dump(&gau8RespBuffer[0]);
                break;
            }
            u32Offset += MB_MAX_PAYLOAD_LEN;
        } while ((u32Offset < u32Size));

        /* Clearing DFU Strap */
        T_D(MEPA_TRACE_GRP_GEN, "Clearing DFU strap");
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        u32Val &= ~(DFU_STRAP);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);
        if (u32BytesWritten == u32Size) {
            T_I(MEPA_TRACE_GRP_GEN, "All packets sent, Raise Last packet interrupt");
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), MAILBOX_DFU_LAST_PKT);
            if (MEPA_RC_OK != (rc = lan80xx_MB_SetFlag(dev, MAILBOX_FLAG_SET_BIT7))) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Failed to set last packet interrupt", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Sent last packet interrupt");
            /* Read Strap */
            LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
            /* Perform POST1 when Serdes Init Strap is Set */
            if (u32Val & SERDES_INIT_STRAP) {
                if (lan80xx_post1_init_priv(dev, data->port_no) != MEPA_RC_OK) {
                    T_E(MEPA_TRACE_GRP_GEN, "POST1 Failed on Port %d \n", data->port_no);
                    return MEPA_RC_ERROR;
                }
            }
            LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
            T_IM(data->port_no,"Waiting for FW ready interrupt...\n");
            u16Timeout = 0;
            while (u16Timeout < MAILBOX_INTR_TIMEOUT) {
                /* Read FW Status */
                LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_FLAG_REGISTER), &u32Val);
                /* As endianess is different, bit 0 goes to MSB*/
                if (u32Val & 0x04) {
                    /* If BIT0 set, FW status active*/
                    T_DM(data->port_no,"Switched to Application. Took %d msecs", u16Timeout);
                    break;
                }
                MEPA_MSLEEP(1);
                u16Timeout++;
            }
            if (u16Timeout == MAILBOX_INTR_TIMEOUT) {
                T_EM(data->port_no,"MB Flag reg value : 0x%x", u32Val);
                LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, MAILBOX_MCU_INTR_MASK_REGISTER), &u32Val);
                T_EM(data->port_no,"MB mask reg value : 0x%x", u32Val);
                T_E(MEPA_TRACE_GRP_GEN, "Failed to start Application, aborting");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }

            /* Memory read DFU_STATUS_REG to check if Signature Verification is successful */
            uint8_t u8ReadBytes[4] = { 0 };
            rc = lan80xx_memory_read_priv(dev, (MCU_DATA_RAM_OFFSET + DFU_STATUS_REG_OFFSET), u8ReadBytes, 4);
            if (rc != MEPA_RC_OK) {
                /* Memory read failed */
                T_E(MEPA_TRACE_GRP_GEN, "DFU STATUS REG read failed");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            if (u8ReadBytes[0] & DFU_SIGN_VERIFY_FAIL_POS) {
                T_E(MEPA_TRACE_GRP_GEN, "MCHP Signature Verification failed");
                rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
                return rc;
            }
            T_D(MEPA_TRACE_GRP_GEN, "%s. Signature Verification passed", __FUNCTION__);
            T_IM(data->port_no,"DFU Success!!\n");
        } else {
            T_EM(data->port_no,"DFU aborted!!\n");
        }
    } else {
        T_EM(data->port_no,"Timeout! No first packet interrupt received");
        rc = MEPA_RC_ERR_MB_FW_UPDATE_FAIL;
        /* Clearing DFU Strap  for failure case before return */
        T_D(MEPA_TRACE_GRP_GEN, "Clearing DFU strap");
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), &u32Val);
        u32Val &= ~(DFU_STRAP);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, STRAP_OVERRIDE_REG), u32Val);
    }
#ifdef DFU_PROFILING_EN
    u64DfuStop_time_ms = MEPA_UPTIME_MSECONDS();
    u64Dfu_time_ms = u64DfuStop_time_ms - u64DfuStart_time_ms;
    T_D(MEPA_TRACE_GRP_GEN, "DFU start (ms): %u", u64DfuStart_time_ms);
    T_D(MEPA_TRACE_GRP_GEN, "DFU stop (ms): %u", u64DfuStop_time_ms);
    T_E(MEPA_TRACE_GRP_GEN, "DFU Time (ms): %u", u64Dfu_time_ms);
#endif

    return rc;
}

mepa_rc lan80xx_otp_cfg_read_priv(const mepa_device_t  *dev,
                                  u8 u8RecIdx,
                                  u8 *pu8Cfg,
                                  u16 *pu16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (u8RecIdx > MAX_OTP_CFG_RECORDS) || (pu8Cfg == NULL) || (pu16Len == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP Cfg read request with index: %d", u8RecIdx);
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(eOTP_CFG_READ, 1, au8CmdBuffer, &u8RecIdx, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eOTP_CFG_READ + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen == 0) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            *pu16Len = 0;
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_D(MEPA_TRACE_GRP_GEN, "Read cfg with len: %d", u16PktLen);
        /* Copy the payload to record data buffer */
        memcpy(pu8Cfg, &pu8Payload[0], u16PktLen);
        *pu16Len = u16PktLen;
        T_I(MEPA_TRACE_GRP_GEN, "OTP Config read success");
    } else {
        if (recvPkt->u8PktId == eOTP_CFG_READ + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_CFG_READ);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

mepa_rc lan80xx_otp_read_priv(const mepa_device_t  *dev,
                              u8 *pu8Data,
                              u16 u16Offset,
                              const u16 u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16DataLen, u16PayloadLen = 0x00;
    /* Form command parameter array for Packet data */
    uint8_t u8cmdParam[4] = { 0 };
    uint16_t u16OtpAddr, u16CurLen;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8Data == NULL) || (u16Len == 0) || (u16Len > MAX_OTP_SIZE) || ((u16Offset + u16Len) > MAX_OTP_SIZE)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    u16OtpAddr = u16Offset;
    u16PktLen = 0;
    u16CurLen = 0;
    u16DataLen = 0;
    while (u16CurLen < u16Len) {
        u16DataLen = ((u16Len - u16CurLen) > (MB_MAX_PAYLOAD_LEN - 4)) ? (MB_MAX_PAYLOAD_LEN - 4) : (u16Len - u16CurLen);
        T_D(MEPA_TRACE_GRP_GEN, "OTP Read at Addr: %04x Len: %d", u16OtpAddr, u16DataLen);
        /* 16 bit address */
        u8cmdParam[0] = (u16OtpAddr) & 0xff;
        u8cmdParam[1] = (u16OtpAddr >> 8) & 0xff;
        /*16 bit length */
        u8cmdParam[2] = (u16DataLen) & 0xFF;
        u8cmdParam[3] = (u16DataLen >> 8) & 0xFF;
        /* Create command request Packet */
        u16PktLen = lan80xx_CreatePacket(eOTP_READ, 4, au8CmdBuffer, &u8cmdParam[0], RESERVED_ID);
        /* Send command Request Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
        rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
            break;
        }
        /* Read Response Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
        rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
            break;
        }
        /* Validate Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
        if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
            break;
        }
        PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
        uint8_t *pu8Payload = NULL;
        pu8Payload = &gau8RespBuffer[4];
        if (recvPkt->u8PktId == eOTP_READ + 0x80) {
            u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
            if ((u16PktLen == 0) || (u16PktLen != u16DataLen)) {
                T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
                T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
                break;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Otp Read with len: %d", u16PktLen);
            /* Copy the payload to data buffer */
            memcpy(pu8Data + u16CurLen, &pu8Payload[0], u16PktLen);
            u16CurLen += u16DataLen;
            u16OtpAddr += u16DataLen;
            T_I(MEPA_TRACE_GRP_GEN, "OTP read success");
        } else {
            if (recvPkt->u8PktId == eOTP_READ + 0x81) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
                rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                    __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_READ);
                rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            }
            packet_dump(&gau8RespBuffer[0]);
            break;
        }
    }

    return rc;
}

mepa_rc lan80xx_otp_write_priv(const mepa_device_t  *dev,
                               u8 *pu8Data,
                               u16 u16Offset,
                               const u16 u16Len,
                               u8 u8WriteMode)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[1024] = { 0 };
    uint16_t u16PktLen, u16DataLen, u16PayloadLen = 0x00;
    /* Form command parameter array for Packet data */
    uint8_t u8cmdParam[MB_MAX_PAYLOAD_LEN] = { 0 };
    uint16_t u16OtpAddr, u16CurLen, u16CmdParamLen = 0, u16Idx = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8Data == NULL) || (u16Len == 0) || (u16Len > MAX_OTP_SIZE) || ((u16Offset + u16Len) > MAX_OTP_SIZE)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    u16OtpAddr = u16Offset;
    u16PktLen = 0;
    u16CurLen = 0;
    u16DataLen = 0;
    while (u16CurLen < u16Len) {
        u16DataLen = ((u16Len - u16CurLen) > (MB_MAX_PAYLOAD_LEN - 4)) ? (MB_MAX_PAYLOAD_LEN - 4) : (u16Len - u16CurLen);
        T_D(MEPA_TRACE_GRP_GEN, "OTP Write at Addr: %04x Len: %d", u16OtpAddr, u16DataLen);
        /* 16 bit address */
        u8cmdParam[0] = (u16OtpAddr) & 0xff;
        u8cmdParam[1] = (u16OtpAddr >> 8) & 0xff;
        /*16 bit length */
        u8cmdParam[2] = (u16DataLen) & 0xFF;
        u8cmdParam[3] = (u16DataLen >> 8) & 0xFF;
        u16CmdParamLen = 4;
        /* Updating command parameter */
        memcpy(&u8cmdParam[u16CmdParamLen], &pu8Data[u16Idx], u16DataLen);
        u16CmdParamLen += u16DataLen;
        /* Create command request Packet */
        u16PktLen = lan80xx_CreatePacket(eOTP_WRITE, u16CmdParamLen, au8CmdBuffer, &u8cmdParam[0], u8WriteMode);
        /* Send command Request Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
        rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
            break;
        }
        /* Read Response Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
        if (u8WriteMode == eOTPWRITE_AUTH) {
            rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
        } else {
            rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
        }

        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
            break;
        }
        /* Validate Packet */
        T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
        if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
            break;
        }
        PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
        if (recvPkt->u8PktId == eOTP_WRITE + 0x80) {
            u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
            if (u16PktLen != 1) {
                T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
                T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
                rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
                break;
            }
            T_D(MEPA_TRACE_GRP_GEN, "Otp write done with len: %d", u16PktLen);
            u16CurLen += u16DataLen;
            u16OtpAddr += u16DataLen;
            u16Idx += u16DataLen;
            T_I(MEPA_TRACE_GRP_GEN, "OTP write success");
        } else {
            if (recvPkt->u8PktId == eOTP_WRITE + 0x81) {
                T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
                rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                    __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_WRITE);
                rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            }
            packet_dump(&gau8RespBuffer[0]);
            break;
        }
    }

    return rc;
}

mepa_rc lan80xx_otp_getKey_Status_priv(const mepa_device_t  *dev,
                                       enOTP_ACTIVE_KEY *pKey)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pKey == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP get active key");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(eOTP_KEY_STATUS, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    uint8_t *pu8Payload = NULL;
    pu8Payload = &gau8RespBuffer[4];

    if (recvPkt->u8PktId == eOTP_KEY_STATUS + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        *pKey = pu8Payload[0];
        switch (*pKey) {
        case eMCHP_PUB_KEY:
            /* MCHP Public key */
            T_D(MEPA_TRACE_GRP_GEN, "MCHP Public key is active");
            break;
        case eREPLACEMENT_KEY1:
            /* Reaplcement key 1 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 1 is active");
            break;
        case eREPLACEMENT_KEY2:
            /* Reaplcement key 2 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 2 is active");
            break;
        case eREPLACEMENT_KEY3:
            /* Reaplcement key 3 */
            T_D(MEPA_TRACE_GRP_GEN, "Replacement key 3 is active");
            break;
        case eALL_KEYS_COMPROMISED:
            /* Key None, all keys revoked */
            T_D(MEPA_TRACE_GRP_GEN, "All Keys compromised");
            break;
        default:
            /* Unknown data, Needs protocol update */
            T_E(MEPA_TRACE_GRP_GEN, "Needs protocol update!!");
            break;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP Get key status success");
    } else {
        if (recvPkt->u8PktId == eOTP_KEY_STATUS + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eOTP_KEY_STATUS);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

mepa_rc lan80xx_otp_revoke_AllKeys_priv(const mepa_device_t  *dev,
                                        u8 *pu8OTPBuffer,
                                        OTPRAMUpdatedDB_t *pCfgUpdates,
                                        u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16OffsetAddr;
    uint8_t i;
    enOTP_ACTIVE_KEY KeyStatus = eMCHP_PUB_KEY;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        if (KeyStatus == eALL_KEYS_COMPROMISED) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            return rc;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Revoking all otp keys...");
    rc = RevokeAllOtpKeys_priv(dev);
    /*If revoke all keys command success, set register value for all keys compromised */
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates */
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Revoke OTP Keys failed with authentication");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Revoke OTP keys success");
    }

    return rc;
}

mepa_rc lan80xx_otp_revoke_ROTKey_priv(const mepa_device_t  *dev,
                                       u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    enOTP_ACTIVE_KEY KeyStatus = eMCHP_PUB_KEY;
    uint16_t u16OffsetAddr;
    uint8_t i;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        if (KeyStatus == eALL_KEYS_COMPROMISED) {
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            return rc;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Revoking ROT key...");
    rc = RevokeRotKey_priv(dev);
    /*IF revoke ROT key command success, set Key Revocation register bit */
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Revoke OTP Keys failed with authentication");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Revoke ROT key success");
    }

    return rc;
}

mepa_rc lan80xx_otp_prog_RepKey_priv(const mepa_device_t  *dev,
                                     u8 *pu8SignedKey,
                                     u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    enOTP_ACTIVE_KEY KeyStatus = eMCHP_PUB_KEY;
    uint8_t u8KeyNo, i;
    uint16_t u16OffsetAddr;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Getting Key status...");
    rc = lan80xx_otp_getKey_Status(dev, &KeyStatus);
    if (rc == MEPA_RC_OK) {
        switch (KeyStatus) {
        case eMCHP_PUB_KEY:
            /* MCHP Public key */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 1...");
            u8KeyNo = ePROG_OTP_KEY1;
            break;
        case eREPLACEMENT_KEY1:
            /* Reaplcement key 1 */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 2...");
            u8KeyNo = ePROG_OTP_KEY2;
            break;
        case eREPLACEMENT_KEY2:
            /* Reaplcement key 2 */
            T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement Key 3...");
            u8KeyNo = ePROG_OTP_KEY3;
            break;
        case eREPLACEMENT_KEY3:
            /* Reaplcement key 3 */
            T_I(MEPA_TRACE_GRP_GEN, "No more key programming is allowed");
            rc = MEPA_RC_ERR_OTP_ALL_KEY_PROGRAMMED;
            break;
        case eALL_KEYS_COMPROMISED:
            /* Key None, all keys revoked */
            T_E(MEPA_TRACE_GRP_GEN, "%s - All OTP Keys revoked", __FUNCTION__);
            rc = MEPA_RC_ERR_OTP_ALL_KEY_COMPROMISED;
            break;
        default:
            /* Unknown data, Needs protocol update */
            T_E(MEPA_TRACE_GRP_GEN, "Needs protocol update!!");
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
            break;
        }
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "%s - OTP get key status failed", __FUNCTION__);
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    }
    if (rc != MEPA_RC_OK) {
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement key%d...", u8KeyNo);
    rc = OTPProgReplacementKey_priv(dev, u8KeyNo, pu8SignedKey);

    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "program Replacement Key failed");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "Programming Replacement key%d success", u8KeyNo);
    }

    return rc;
}

mepa_rc lan80xx_otp_cfg_program_priv(const mepa_device_t  *dev,
                                     u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt)
{
    mepa_rc rc = MEPA_RC_OK;
    uint16_t u16OffsetAddr;
    uint8_t i;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    for (i = 0; i < u8UpdateCnt - 1; i++) {
        T_D(MEPA_TRACE_GRP_GEN, "------ Sending OTP Writes ------");
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d offset 0X%X", i, pCfgUpdates[i].u16Offset);
        T_D(MEPA_TRACE_GRP_GEN, "Otp update %d len 0X%X", i, pCfgUpdates[i].u16Len);

        /* writeMode set to BUFF for Record, Index and PRG CTR updates*/
        u16OffsetAddr = pCfgUpdates[i].u16Offset;
        rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, pCfgUpdates[i].u16Len, eOTPWRITE_BUFF);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "OTP Write failed");
            return rc;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "sending signature...");
    u16OffsetAddr = pCfgUpdates[i].u16Offset;
    rc = lan80xx_otp_write(dev, &pu8OTPBuffer[u16OffsetAddr], u16OffsetAddr, OTP_SIGNATURE_LEN, eOTPWRITE_AUTH);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "OTP cfg program failed");
        rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
    } else {
        T_D(MEPA_TRACE_GRP_GEN, "OTP cfg program success");
    }

    return rc;
}

static mepa_rc OTPProgReplacementKey_priv(const mepa_device_t  *dev,
                                          u8 u8KeyNo,
                                          u8 *pu8KeyData)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[256] = { 0 };
    uint8_t u8CmdParam[OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if ((dev == NULL) || (pu8KeyData == NULL)) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP PRG replacement key");
    /* Copy the key data into cmdparam */
    T_D(MEPA_TRACE_GRP_GEN, "Copying key data...");
    memcpy(&u8CmdParam[0], pu8KeyData, OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN);
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8KeyNo, OTP_REP_KEY_LEN + OTP_REP_KEY_SIGN_LEN, au8CmdBuffer, u8CmdParam, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == u8KeyNo + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP PRG replacement key success");
    } else {
        if (recvPkt->u8PktId == u8KeyNo + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8KeyNo);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

static mepa_rc RevokeAllOtpKeys_priv(const mepa_device_t  *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;
    const uint8_t u8PktId = eREVOKE_OTP_KEYS;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (dev == NULL) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP revoke all keys");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8PktId, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP revoke all keys success");
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

static mepa_rc RevokeRotKey_priv(const mepa_device_t  *dev)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen, u16PayloadLen = 0x00;
    const uint8_t u8PktId = eREVOKE_ROT_KEY;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (dev == NULL) {
        rc = MEPA_RC_ERR_PARM;
        T_E(MEPA_TRACE_GRP_GEN, "%s - Invalid parameter",  __FUNCTION__);
        return rc;
    }
    T_D(MEPA_TRACE_GRP_GEN, "OTP revoke ROT key");
    /* Create command request Packet */
    u16PktLen = lan80xx_CreatePacket(u8PktId, 0, au8CmdBuffer, NULL, RESERVED_ID);

    /* Send command Request Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Sending command request...");
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Send Command", __FUNCTION__);
        return rc;
    }

    /* Read Response Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Reading command response...");
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_SIGN_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Fail to Read Response", __FUNCTION__);
        return rc;
    }

    /* Validate Packet */
    T_D(MEPA_TRACE_GRP_GEN, "Validating packet...");
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s - Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        u16PktLen = recvPkt->u16PktLen - MB_MAX_PKT_HEADER_LEN - MB_MAX_CRC_LEN;
        if (u16PktLen != 1) {
            T_D(MEPA_TRACE_GRP_GEN, "%s - Invalid data length (%d)", __FUNCTION__, u16PktLen);
            T_E(MEPA_TRACE_GRP_GEN, "%s - Cmd protocol needs update!!", __FUNCTION__);
            rc = MEPA_RC_ERR_MB_INVALID_PKT_LEN;
            return rc;
        }
        T_I(MEPA_TRACE_GRP_GEN, "OTP revoke ROT key success");
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

mepa_rc lan80xx_get_serdes_config_priv(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, __SERDES_CONFIG_T *const data)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00, u16Len = 0;
    uint8_t au8CmdParam[8] = { 0 };
    uint16_t u16CmdParamLen = 0;
    const uint8_t u8PktId = eGET_SERDES_CONFIG;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    au8CmdParam[u16CmdParamLen++] = speed;
    au8CmdParam[u16CmdParamLen++] = cfgType;
    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(u8PktId, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];
    unsigned char *pCfg = NULL;
    pCfg = (unsigned char *) &gau8RespBuffer[MB_PKT_DATA_OFFSET];
    /* Strip off the packet header length to get payload length */
    u16PayloadLen -= (MB_MAX_PKT_HEADER_LEN + MB_MAX_CRC_LEN);

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        switch (cfgType) {
        case eTX_EQ_CFG:
            u16Len = sizeof(tx_eq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *)&data->sTx_eq_cfg, (void *)pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eCDR_CFG:
            u16Len = sizeof(cdr_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sCdr_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eSPEED_CHANGE_CFG:
            u16Len = sizeof(speed_change_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sSpeed_change_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eRX_EQ_CFG:
            u16Len = sizeof(rx_eq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sRx_eq_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eDFE_CFG:
            u16Len = sizeof(dfe_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sDfe_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case ePOL_SQ_CFG:
            u16Len = sizeof(pol_sq_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sPol_sq_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eTX_SWING_CFG:
            u16Len = sizeof(tx_swing_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sTx_swing_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eMISC_CFG:
            u16Len = sizeof(misc_cfg_t);
            if (u16PayloadLen == u16Len) {
                memcpy((void *) &data->sMisc_cfg, (void *) pCfg, u16Len);
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eALL_CFG:
            u16Len = sizeof(tx_eq_cfg_t) + sizeof(cdr_cfg_t) + sizeof(speed_change_cfg_t) +
                     sizeof(rx_eq_cfg_t) + sizeof(dfe_cfg_t) + sizeof(pol_sq_cfg_t) +
                     sizeof(tx_swing_cfg_t) + sizeof(misc_cfg_t);
            if (u16PayloadLen == u16Len) {
                u16Len = sizeof(tx_eq_cfg_t);
                memcpy((void *)&data->sTx_eq_cfg, (void *)pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(cdr_cfg_t);
                memcpy((void *) &data->sCdr_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(speed_change_cfg_t);
                memcpy((void *) &data->sSpeed_change_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(rx_eq_cfg_t);
                memcpy((void *) &data->sRx_eq_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(dfe_cfg_t);
                memcpy((void *) &data->sDfe_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(pol_sq_cfg_t);
                memcpy((void *) &data->sPol_sq_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(tx_swing_cfg_t);
                memcpy((void *) &data->sTx_swing_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;

                u16Len = sizeof(misc_cfg_t);
                memcpy((void *) &data->sMisc_cfg, (void *) pCfg, u16Len);
                pCfg = (unsigned char *) pCfg + u16Len;
            } else {
                T_E(MEPA_TRACE_GRP_GEN, "Invalid payload length %d, expected %d\n", u16PayloadLen, u16Len);
                rc = MESA_RC_ERROR;
            }
            break;
        case eUNKNOWN_CFG:
        default:
            T_E(MEPA_TRACE_GRP_GEN, "Invalid config type!!");
            rc = MESA_RC_ERROR;
            break;
        }
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

mepa_rc lan80xx_set_serdes_config_priv(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, const __SERDES_CONFIG_T *data)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[128] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00, u16Len = 0;
    uint8_t au8CmdParam[128] = { 0 };
    const uint8_t u8PktId = eSET_SERDES_CONFIG;
    uint16_t u16CmdParamLen = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }
    au8CmdParam[u16CmdParamLen++] = speed;
    au8CmdParam[u16CmdParamLen++] = cfgType;
    /* Increment len, as 2 cmd param added */
    unsigned char *pCfg = (unsigned char *) &au8CmdParam[u16CmdParamLen];
    switch (cfgType) {
    case eTX_EQ_CFG:
        u16Len = sizeof(tx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eCDR_CFG:
        u16Len = sizeof(cdr_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sCdr_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eSPEED_CHANGE_CFG:
        u16Len = sizeof(speed_change_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sSpeed_change_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eRX_EQ_CFG:
        u16Len = sizeof(rx_eq_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sRx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eDFE_CFG:
        u16Len = sizeof(dfe_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sDfe_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case ePOL_SQ_CFG:
        u16Len = sizeof(pol_sq_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sPol_sq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eTX_SWING_CFG:
        u16Len = sizeof(tx_swing_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sTx_swing_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eMISC_CFG:
        u16Len = sizeof(misc_cfg_t);
        memcpy((void *)pCfg, (void *) &data->sMisc_cfg, u16Len);
        u16CmdParamLen += u16Len;
        break;
    case eALL_CFG:
        u16Len = sizeof(tx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(cdr_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sCdr_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(speed_change_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sSpeed_change_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(rx_eq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sRx_eq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(dfe_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sDfe_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(pol_sq_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sPol_sq_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(tx_swing_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sTx_swing_cfg, u16Len);
        u16CmdParamLen += u16Len;
        pCfg = (unsigned char *)pCfg + u16Len;

        u16Len = sizeof(misc_cfg_t);
        memcpy((void *)pCfg, (void *)&data->sMisc_cfg, u16Len);
        u16CmdParamLen += u16Len;

        break;
    case eUNKNOWN_CFG:
    default:
        T_E(MEPA_TRACE_GRP_GEN, "Invalid config type!!");
        rc = MESA_RC_ERROR;
        return rc;
    }

    // Step 1: Create Packet for Device Info
    u16PktLen = lan80xx_CreatePacket(u8PktId, u16CmdParamLen, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == u8PktId + 0x80) {
        T_I(MEPA_TRACE_GRP_GEN, "SD Config set success\n");
    } else {
        if (recvPkt->u8PktId == u8PktId + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), u8PktId);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

mepa_rc lan80xx_KRLog_Enable_priv(const mepa_device_t *dev, mepa_bool_t bkrlog_enable, mepa_bool_t bline_port_en, mepa_bool_t  bhost_port_en)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint8_t au8CmdParam[8] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00;
    uint8_t  byKRportsToEnable = 0, KRNOfports = 0;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);
    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    T_D(MEPA_TRACE_GRP_GEN, "Enabling KR Log on port : %d, channel id: %d, kr log enabled ports: %x\n\n", data->port_no, data->channel_id, base_data->krlog_en_ports);

    // Check if KR Log Maximum port supported (4 - host + line)
    byKRportsToEnable = base_data->krlog_en_ports;

    if (bline_port_en) {
        if (bkrlog_enable) {
            byKRportsToEnable |= (1 << data->channel_id);
        } else {
            byKRportsToEnable &= ~(1 << data->channel_id);
        }
    }
    if (bhost_port_en) {
        if (bkrlog_enable) {
            byKRportsToEnable |= (1 << (data->channel_id + 4));
        } else {
            byKRportsToEnable &= ~(1 << (data->channel_id + 4));
        }
    }
    au8CmdParam[0] = byKRportsToEnable;

    if (!bkrlog_enable) {
        base_data->krlog_en_ports = byKRportsToEnable;
        return rc;
    }

    while (byKRportsToEnable != 0) {
        byKRportsToEnable = byKRportsToEnable & (byKRportsToEnable - 1);
        KRNOfports++;
    }

    // Check if the number of ports exceeds the maximum allowed
    if (KRNOfports > 4) {
        T_E(MEPA_TRACE_GRP_GEN, "%s KR Logging is allowed only for maximum of 4 ports", \
            __FUNCTION__);
        rc = MESA_RC_ERR_PARM;
        return rc;
    }
    if (KRNOfports <= 0) {
        T_E(MEPA_TRACE_GRP_GEN, "%s Atleast one port needs to enabled for KR Logging ", \
            __FUNCTION__);
        rc = MESA_RC_ERR_PARM;
        return rc;
    }

    // Step 1: Create Packet
    u16PktLen = lan80xx_CreatePacket(eENABLE_KR_LOG, 1, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == eENABLE_KR_LOG + 0x80) {
        base_data->krlog_en_ports = au8CmdParam[0];
        T_I(MEPA_TRACE_GRP_GEN, "%s: Success", __FUNCTION__);
    } else {
        if (recvPkt->u8PktId == eENABLE_KR_LOG + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eENABLE_KR_LOG);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }

    return rc;
}

mepa_rc lan80xx_KRLog_Reset_priv(const mepa_device_t *dev, uint32_t u32KRLogOffset, uint16_t u16Len)
{
    mepa_rc rc = MEPA_RC_OK;
    uint8_t au8CmdBuffer[32] = { 0 };
    uint8_t au8CmdParam[8] = { 0 };
    uint16_t u16PktLen = 0, u16PayloadLen = 0x00;

    T_I(MEPA_TRACE_GRP_GEN, "%s", __FUNCTION__);

    if (!dev) {
        T_E(MEPA_TRACE_GRP_GEN, "No device found!");
        rc = MEPA_RC_ERR_PARM;
        return rc;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Sending RESET KR Log Memory at address:%2X, length: %2X \n\n", u32KRLogOffset, u16Len);


    // Step 1: Create Packet for Device Info
    /* 32 bit address */
    au8CmdParam[0] = (u32KRLogOffset) & 0xff;
    au8CmdParam[1] = (u32KRLogOffset >> 8) & 0xff;
    au8CmdParam[2] = (u32KRLogOffset >> 16) & 0xff;
    au8CmdParam[3] = (u32KRLogOffset >> 24) & 0xff;
    /*16 bit length */
    au8CmdParam[4] = (u16Len) & 0xFF;
    au8CmdParam[5] = (u16Len >> 8) & 0xFF;

    u16PktLen = lan80xx_CreatePacket(eRESET_KR_LOG_MEMORY, 6, au8CmdBuffer, au8CmdParam, RESERVED_ID);

    // Step 2: Send Request Packet
    rc = lan80xx_MB_SendRequest(dev, au8CmdBuffer, u16PktLen);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Send Command", __FUNCTION__);
        return rc;
    }

    // Step 3: Read Response Packet
    rc = lan80xx_MB_ReadResponse(dev, gau8RespBuffer, &u16PayloadLen, MAILBOX_INTR_TIMEOUT);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Fail to Read Response", __FUNCTION__);
        return rc;
    }

    // Step 4: Validate Packet
    if (lan80xx_ValidatePacket(gau8RespBuffer) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "%s. Validate Packet Failed", __FUNCTION__);
        return rc;
    }

    PKT_HDR_T *recvPkt = (PKT_HDR_T *)&gau8RespBuffer[0];

    if (recvPkt->u8PktId == eRESET_KR_LOG_MEMORY + 0x80) {
        T_I(MEPA_TRACE_GRP_GEN, "%s: Success", __FUNCTION__);
    } else {
        if (recvPkt->u8PktId == eRESET_KR_LOG_MEMORY + 0x81) {
            T_E(MEPA_TRACE_GRP_GEN, "%s. Fail with error code %d", __FUNCTION__, gau8RespBuffer[MB_PKT_DATA_OFFSET]);
            rc = MEPA_RC_ERR_MB_FAIL_RESPONSE;
        } else {
            T_E(MEPA_TRACE_GRP_GEN, "%s Wrong packet received (%d), expected (%d)", \
                __FUNCTION__, (recvPkt->u8PktId - 0x80), eRESET_KR_LOG_MEMORY);
            rc = MEPA_RC_ERR_MB_CMD_PROTO_NO_SYNC;
        }
        packet_dump(&gau8RespBuffer[0]);
    }
    return rc;
}

/**
 * Advertisement Word (Refer to IEEE 802.3 Clause 37):
 *  MSB                                                                         LSB
 *  D15  D14  D13  D12  D11  D10   D9   D8   D7   D6   D5   D4   D3   D2   D1   D0
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 * | NP | Ack| RF2| RF1|rsvd|rsvd|rsvd| PS2| PS1| HD | FD |rsvd|rsvd|rsvd|rsvd|rsvd|
 * +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 **/
mepa_rc lan80xx_clause37_conf_set_priv(mepa_device_t        *dev,
                                       mepa_port_no_t       port_no,
                                       mepa_cl37_conf_t     *cl37_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    u32 adv_abilities = 0;
    u32 val = 0;
    if (cl37_conf->enable == FALSE) {
        T_D(MEPA_TRACE_GRP_GEN, "Disabling Clause37 on port : %d\n", port_no);
        if (cl37_conf->advertise_dir == MEPA_ADV_SIDE_LINE || cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST_LINE || cl37_conf->advertise_dir == MEPA_ADV_SIDE_NONE) {
             LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_CFG_1, LAN80XX_F_LINE_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(adv_abilities));
             LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_CFG_0, LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT,
                             LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT |
                             LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA);
        }
        if (cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST || cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST_LINE || cl37_conf->advertise_dir == MEPA_ADV_SIDE_NONE) {
             LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_1, LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(adv_abilities));
             LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0, LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT,
                             LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT |
                             LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA);
        }
        return MEPA_RC_OK;
    }

	u8 full_duplex_1g = 1;
    u8 half_duplex_1g = 0;
    adv_abilities =((full_duplex_1g              << LAN80XX_CLAUSE37_ADV_1G_FDX_BIT) |
                    (half_duplex_1g              << LAN80XX_CLAUSE37_ADV_1G_HDX_BIT) |
                    (cl37_conf->symmetric_pause  << LAN80XX_CLAUSE37_ADV_SYMMETRIC_PAUSE) |
                    (cl37_conf->asymmetric_pause << LAN80XX_CLAUSE37_ADV_ASYMMETRIC_PAUSE) |
                    (cl37_conf->remote_fault     << LAN80XX_CLAUSE37_ADV_REMOTE_FAULT) |
                    (cl37_conf->acknowledge      << LAN80XX_CLAUSE37_ADV_ACK) |
                    (cl37_conf->next_page        << LAN80XX_CLAUSE37_ADV_NEXT_PAGE));

    T_D(MEPA_TRACE_GRP_GEN, "Clause 37, base page ability : 0x%x on port : %d \n", adv_abilities, port_no);
    T_D(MEPA_TRACE_GRP_GEN, "Clause 37, Next page state : %d , next page ability : 0x%x on port : %d \n", cl37_conf->next_page, cl37_conf->next_page_abilities,  port_no);

    if (cl37_conf->advertise_dir == MEPA_ADV_SIDE_LINE || cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST_LINE) {

        T_D(MEPA_TRACE_GRP_GEN, "Enabling Clause37 on Line side of the port : %d\n", port_no);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_CFG_1, LAN80XX_F_LINE_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(adv_abilities));

        if (cl37_conf->next_page == TRUE) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_1, LAN80XX_F_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX(cl37_conf->next_page_abilities),
                            LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX);

            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_0, LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT, LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_0, 0, LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT);
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_CFG_0,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA | LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT,
                        LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA | LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT);

        LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_PCS_CFG_PCS1G_MODE_CFG, &val);

        if (val & LAN80XX_M_LINE_PCS_CFG_PCS1G_MODE_CFG_SGMII_MODE_ENA) {
            val = LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_SW_RESOLVE_ENA;
        } else {
            val = 0;
        }
        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_PCS_CFG_PCS1G_ANEG_CFG_0, val, LAN80XX_M_LINE_PCS_CFG_PCS1G_ANEG_CFG_0_SW_RESOLVE_ENA);
    }

    if (cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST || cl37_conf->advertise_dir == MEPA_ADV_SIDE_HOST_LINE) {

        T_D(MEPA_TRACE_GRP_GEN, "Enabling Clause37 on Host side of the port : %d\n", port_no);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_1, LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_CFG_1_ADV_ABILITY(adv_abilities));

        if (cl37_conf->next_page == TRUE) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1, LAN80XX_F_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX(cl37_conf->next_page_abilities),
                            LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_1_NP_TX);

            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0, LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT, LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT);
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0, 0, LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_NP_CFG_0_NP_LOADED_ONE_SHOT);
        }

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_PCS_CFG_PCS1G_ANEG_CFG_0,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA | LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT,
                        LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_ENA | LAN80XX_M_HOST_PCS_CFG_PCS1G_ANEG_CFG_0_ANEG_RESTART_ONE_SHOT);
    }
    return MEPA_RC_OK;
}
