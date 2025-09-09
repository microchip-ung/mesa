// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN887X_REGISTERS_H
#define LAN887X_REGISTERS_H

#define LAN887X_DEF_MASK    DEF_MASK

#define LAN887X_BIT_MASK(x) BIT_MASK
#define LAN887X_EXTRACT_BITFIELD(value, offset, width)  EXTRACT_BITFIELD(value, offset, width)
#define LAN887X_ENCODE_BITFIELD(value, offset, width)   ENCODE_BITFIELD(value, offset, width)

#define LAN8870_PHY_REG_ADDR(addr)      ((addr) & 0x00FFU)
#define PHY_REG_ADDR(addr) ((addr) & 0xFFFFU)
#define PHY_MMD_DEVAD(addr) (((addr) & 0x00FF0000U) >> 16)
#define PHY_PACK_MMD_ADDR(devad, addr) ((((devad) & 0xFFU) << 16) | ((addr) & 0xFFFFU))

/* Start:: DEV-0x1 Registers */
/* 100T1 PMA Commmon Registers */
#define     LAN887X_PMA_COMM_100T1_CTL_T1_TYPE_1000             (0x1U)

/* 1000T1 PMA Registers */
#define     LAN887X_PMA_1000T1_DSP_PMA_CTL_REG                  (0x810eU)
#define     LAN887X_PMA_1000T1_DSP_PMA_LNK_SYNC                 BIT(4)

/* t1_phy_port_afe_regs Registers */
#define LAN887X_T1_AFE                                          (0x8000U)
#define LAN887X_T1_AFE_PORT_ZQCAL_OFFSET_REG                    (LAN887X_T1_AFE | 0x93U)
#define LAN887X_T1_AFE_PORT_TESTBUS_CTRL2_REG                   (LAN887X_T1_AFE | 0x89U)
#define LAN887X_T1_AFE_PORT_TESTBUS_CTRL4_REG                   (LAN887X_T1_AFE | 0x8BU)
#define LAN887X_T1_AFE_PORT_TX_AMPLT_1000T1_REG                 (LAN887X_T1_AFE | 0xB0U)
#define LAN887X_T1_AFE_PORT_TX_FIR_CTRL_STATUS                  (LAN887X_T1_AFE | 0x94U)
#define LAN887X_T1_AFE_PORT_COEFF_2_1_1000T1_REG                (LAN887X_T1_AFE | 0x95U)

/* t1_phy_common_afe_regs Registers */
#define LAN887X_COMMON_AFE_COMMON_BLOCK_CONTROL_2               (0xF001U)
#define LAN887X_COMMON_AFE_COMMON_BLOCK_TESTBUS_CTRL1           (0xF00CU)
#define LAN887X_COMMON_AFE_COMMON_BLOCK_TESTBUS_CTRL1_MCM_CLK_EN BIT(6)

/* End:: DEV-0x1 Registers */

/* Start:: DEV-0x3 Registers */
/* 1000T1 PCS Regsiters */
#define        LAN887X_1000T1_PCS_CTL_REG                       (0x900U)
#define        LAN887X_1000T1_PCS_LPBK                          BIT(14)

#define        LAN887X_1000T1_PCS_DBG_BUS_CFG                   (0x802FU)
/* End:: DEV-0x3 Registers */

/* Start:: DEV-0x1E Registers */
/* SQI Registers*/
#define         LAN887X_DSP_REGS_COEFF_MOD_CONFIG               (0x80dU)
#define         LAN887X_DSP_REGS_COEFF_MOD_CONFIG_DCQ_COEFF_EN  BIT(8)
#define         LAN887X_DSP_REGS_DCQ_SQI_STATUS                 (0x8b2U)
#define         T1_DCQ_SQI_MSK                                  GENMASK(1, 3)


/* CABLE DIAGONISTCS Registers */
#define LAN887X_DSP_CALIB_CONFIG_100                            (0x437U)
#define LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_USE_LOCAL_SMPL    BIT(5)
#define LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_STB_SYNC_MODE     BIT(4)
#define LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_CLK_ALGN_MODE     BIT(3)
#define LAN887X_DSP_CALIB_CONFIG_100_VAL \
    (LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_CLK_ALGN_MODE |\
    LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_STB_SYNC_MODE |\
    LAN887X_DSP_CALIB_CONFIG_100_CBL_DIAG_USE_LOCAL_SMPL)
#define LAN887X_DSP_REGS_MAX_PGA_GAIN_100                       (0x44FU)
#define LAN887X_DSP_REGS_MIN_PGA_GAIN_100                       (0x450U)
#define LAN887X_DSP_REGS_START_CBL_DIAG_100                     (0x45AU)
#define LAN887X_DSP_REGS_START_CBL_DIAG_DONE                    BIT(1)
#define LAN887X_DSP_REGS_START_CBL_DIAG_EN                      BIT(0)

#define LAN887X_DSP_REGS_CBL_DIAG_TDR_THRESH_100                (0x45BU)
#define LAN887X_DSP_REGS_CBL_DIAG_AGC_THRESH_100                (0x45CU)
#define LAN887X_DSP_REGS_CBL_DIAG_MIN_WAIT_CONFIG_100           (0x45DU)
#define LAN887X_DSP_REGS_CBL_DIAG_MAX_WAIT_CONFIG_100           (0x45EU)
#define LAN887X_DSP_REGS_CBL_DIAG_CYC_CONFIG_100                (0x45FU)
#define LAN887X_DSP_REGS_CBL_DIAG_TX_PULSE_CONFIG_100           (0x460U)
#define LAN887X_DSP_REGS_CBL_DIAG_MIN_PGA_GAIN_100              (0x462U)

/* Chiptop Common Registers */
#define        LAN887X_CHIPTOP_COMM_REG_1                       (0xC00U)
#define        LAN887X_CHIPTOP_COMM_REG_1_AFE_LPBK_EN           BIT(1)
#define        LAN887X_CHIPTOP_COMM_LED1_LED0                   (0xc04U)
#define        LAN887X_CHIPTOP_COMM_LED3_LED2                   (0xc05U)
#define        LAN887X_CHIPTOP_LED_LINK_ACT_ANY_SPEED           (0x0U)
#define        LAN887X_CHIPTOP_LED_LINK_ACT_1000_SPEED          (0x1U)
#define        LAN887X_CHIPTOP_LED_LINK_ACT_100_SPEED           (0x2U)
#define        LAN887X_CHIPTOP_LED_LINK_NO_ACT_ANY_SPEED        (0x3U)
#define        LAN887X_CHIPTOP_LED_LOCAL_RXER_STATUS            (0x5U)
#define        LAN887X_CHIPTOP_LED_REMOTE_RXER_STATUS           (0x6U)
#define        LAN887X_CHIPTOP_LED_NEGOTIATED_SPEED         (0x7U)
#define        LAN887X_CHIPTOP_LED_MASTER_SLAVE_MODE            (0x8U)
#define        LAN887X_CHIPTOP_LED_PCS_TX_ERR_STATUS            (0x9U)
#define        LAN887X_CHIPTOP_LED_PCS_RX_ERR_STATUS            (0xAU)
#define        LAN887X_CHIPTOP_LED_PCS_TX_ACTIVITY          (0xBU)
#define        LAN887X_CHIPTOP_LED_PCS_RX_ACTIVITY          (0xCU)
#define        LAN887X_CHIPTOP_LED_WAKE_ON_LAN              (0xDU)
#define        LAN887X_CHIPTOP_LED_FORCED_LED_OFF           (0xEU)
#define        LAN887X_CHIPTOP_LED_FORCED_LED_ON            (0xFU)

/* MIS Regsiters */
#define        LAN887X_MIS_100T1_SMI_REG26                      (0x1AU)
#define        LAN887X_MIS_100T1_SMI_HW_INIT_SEQ_EN             BIT(8)

#define        LAN887X_MIS_CFG_REG0                             (0xa00U)
#define        LAN887X_MIS_CFG_REG0_RX_BIT_REV                  BIT(4)
#define        LAN887X_MIS_CFG_REG0_RCLKOUT_DIS                 BIT(5)
#define        LAN887X_MIS_CFG_REG0_MAC_MAC_MODE_SEL            GENMASK(0, 2)
#define        LAN887X_MIS_CFG_REG0_MAC_MODE_RGMII              (0x01U)
#define        LAN887X_MIS_CFG_REG0_MAC_MODE_SGMII              (0x03U)

#define        LAN887X_MIS_TX_DLL_CFG_REG0                      (0xa01U)
#define        LAN887X_MIS_RX_DLL_CFG_REG1                      (0xa02U)
#define        LAN887X_MIS_DLL_DELAY_EN                         BIT(15)
#define        LAN887X_MIS_DLL_EN                               BIT(0)
#define        LAN887X_MIS_DLL_EN_  \
                    (LAN887X_MIS_DLL_DELAY_EN | \
                     LAN887X_MIS_DLL_EN)

#define        LAN887X_MIS_CFG_REG2                             (0xa03U)
#define        LAN887X_MIS_CFG_REG2_IO_LPBK_EN                  BIT(3)
#define        LAN887X_MIS_CFG_REG2_FE_LPBK_EN                  BIT(2)
#define        LAN887X_MIS_CFG_REG2_NE_LPBK_EN                  BIT(1)

#define        LAN887X_MIS_PKT_STAT_REG0                        (0xa06U)
#define        LAN887X_MIS_PKT_STAT_REG1                        (0xa07U)
#define        LAN887X_MIS_PKT_STAT_REG3                        (0xa09U)
#define        LAN887X_MIS_PKT_STAT_REG4                        (0xa0aU)
#define        LAN887X_MIS_PKT_STAT_REG5                        (0xa0bU)
#define        LAN887X_MIS_PKT_STAT_REG6                        (0xa0cU)
#define        LAN887X_MIS_EPG_CFG1_REG                         (0xa0dU)

/* Common */
#define        LAN887X_COMM_PORT_INTC_REG                       (0xc10U)
#define        LAN887X_COMM_PORT_INTS_REG                       (0xc11U)
#define        LAN887X_COMM_PORT_INT_PHY_EN                     BIT(15)
#define        LAN887X_COMM_PORT_INT_RECV_LPS_EN                BIT(5)
#define        LAN887X_COMM_PORT_INT_MIS_EN                     BIT(2)
#define        LAN887X_COMM_PORT_INT_S100                       BIT(1)
#define        LAN887X_COMM_PORT_INT_S1000                      BIT(0)

#define        LAN887X_COMM_PORT_INT_ALL \
                     (LAN887X_COMM_PORT_INT_PHY_EN |\
                      LAN887X_COMM_PORT_INT_MIS_EN |\
                      LAN887X_COMM_PORT_INT_S1000)

/* mx_chip_top_regs */
#define LAN887X_MX_CHIP_TOP_REG_INT_STS                         (0xF000U)
#define LAN887X_MX_CHIP_TOP_REG_INT_MSK                         (0xF001U)
#define LAN887X_MX_CHIP_TOP_T1_PHY_INT_MSK                      BIT(2)
#define LAN887X_MX_CHIP_TOP_LINK_UP_MSK                         BIT(1)
#define LAN887X_MX_CHIP_TOP_LINK_DOWN_MSK                       BIT(0)
#define LAN887X_MX_CHIP_TOP_LINK_MSK \
            (LAN887X_MX_CHIP_TOP_LINK_UP_MSK |\
             LAN887X_MX_CHIP_TOP_LINK_DOWN_MSK)
#define LAN887X_MX_CHIP_TOP_ALL_MSK \
            (LAN887X_MX_CHIP_TOP_T1_PHY_INT_MSK |\
             LAN887X_MX_CHIP_TOP_LINK_MSK |\
             LAN887X_MX_CHIP_TOP_P1588_MOD_INT_STS)

#define LAN887X_MX_CHIP_TOP_REG_CONTROL1                        (0xF002U)
#define LAN887X_MX_CHIP_TOP_REG_GPIO_DIR                        (0xF00AU)
#define LAN887X_MX_CHIP_TOP_REG_GPIO_DATA                       (0xF00CU)

#define LAN887X_MX_CHIP_TOP_REG_HARD_RST                        (0xF03EU)
#define LAN887X_MX_CHIP_TOP_REG_SOFT_RST                        (0xF03FU)
#define LAN887X_MX_CHIP_TOP_RESET_                              BIT(0)

#define LAN887X_MX_CHIP_TOP_REG_SGMII_CTL                       (0xF01AU)
#define LAN887X_MX_CHIP_TOP_REG_SGMII_XAUI_RST                  BIT(2)
#define LAN887X_MX_CHIP_TOP_REG_SGMII_VREG_BYP_CTL              BIT(1)
#define LAN887X_MX_CHIP_TOP_REG_SGMII_MUX_EN                    BIT(0)

#define LAN887X_MX_CHIP_TOP_SGMII_PCS_CFG                       (0xF034U)
#define LAN887X_MX_CHIP_TOP_SGMII_PCS_LNK_STS_TYP               BIT(10)
#define LAN887X_MX_CHIP_TOP_SGMII_PCS_ENA                       BIT(9)

#define LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG                      (0xF035U)
#define LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG_RST                  BIT(4)
#define LAN887X_MX_CHIP_TOP_SGMII_PCS_ANEG_EN                   BIT(3)

#define LAN887X_MX_CHIP_TOP_QSGMII_ANEG_REG                     (0xF020U)
#define LAN887X_MX_CHIP_TOP_QSGMII_ANEG_EN                      BIT(0)

#define LAN887X_MX_CHIP_TOP_SGMII_MPLL_CTL                      (0xF028U)

#ifdef MEPA_OPT_TC10
/**********************************/
//     TC10 Registers
/**********************************/

/**
 * PHY states in TC10 Mode are
 * 0: PHY start
 * 1: PHY Normal
 * 2: SLEEP ACK - When PHY receives LPS(Low Power Sleep) signal from Link partner
 * 3: SLEEP_REQ - When Sleep request is asserted on PHY.
 * 4: SLEEP_FAIL - If Sleep handshaking is not done before sleep_req_timer timeout.
 * 5: SLEEP_SILENT - If the PHY detects that it has sent and received LPS commands.
 * 6: PHY_SLEEP - PHY is in SLEEP state.
 *
 */
#define LAN887X_STS_TC10_STATE_GET(x)          LAN887X_EXTRACT_BITFIELD(x,0,3)
#define LAN887X_STS_TC10_STATE_START           (0U)
#define LAN887X_STS_TC10_STATE_NORMAL          (1U)
#define LAN887X_STS_TC10_STATE_SLEEP_ACK       (2U)
#define LAN887X_STS_TC10_STATE_SLEEP_REQ       (3U)
#define LAN887X_STS_TC10_STATE_SLEEP_FAIL      (4U)
#define LAN887X_STS_TC10_STATE_SLEEP_SILENT    (5U)
#define LAN887X_STS_TC10_STATE_SLEEP           (6U)

#define LAN887X_TC10_DEV30_COMMON_MISC34                    (0x0C26U)

#define LAN887X_MISC_REGS_REG16                             (0x10U)
#define LAN887X_MISC_REGS_REG16_IGNORE_IDLE_WITH_WUR_LPS    BIT(5)

#define LAN887X_MISC_REGS_MISC37                            (0x0125U)
#define LAN887X_MISC_REGS_MISC37_EN_TC10_SLEEP_SILENT       BIT(5)

#define LAN887X_DEV30_COMMON_TC10_REG_REG15                 (0x0C20U)
#define LAN887X_DEV30_COMMON_TC10_REG_REG15_WK_OUT_PIN_REQ  BIT(0)

#define LAN887X_DEV30_COMMON_TC10_REG_REG16                 (0x0C21U)
#define LAN887X_DEV30_COMMON_TC10_REG_REG16_RW_SEND_LPS BIT(12)
#define LAN887X_DEV30_COMMON_TC10_REG_REG16_RW_SEND_WUR BIT(13)

#define LAN887X_DEV30_COMMON_TC10_REG_REG24                 (0x0C22U)

#define LAN887X_DEV30_COMMON_TC10_MISC32                            (0x0C24U)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_EN                   BIT(0)
#define LAN887X_DEV30_COMMON_TC10_MISC32_INH_EN_TC10                BIT(1)
#define LAN887X_DEV30_COMMON_TC10_MISC32_SLEEP_EN                   BIT(2)
#define LAN887X_DEV30_COMMON_TC10_MISC32_ROSC_EN                    BIT(5)
#define LAN887X_DEV30_COMMON_TC10_MISC32_ROSC_STS                   BIT(6)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_AUTO_FWD_EN         BIT(7)
#define LAN887X_DEV30_COMMON_TC10_MISC32_INH_MODE_OPEN_DRAIN        BIT(8)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_SET(x)        LAN887X_ENCODE_BITFIELD(x, 9, 2)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_PUSH_PULL     (0U)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_OPEN_SOURCE   (1U)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_MODE_OPEN_DRAIN    (2U)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_OUT_POL                 BIT(11)
#define LAN887X_DEV30_COMMON_TC10_MISC32_WK_IN_POL                  BIT(12)
#define LAN887X_DEV30_COMMON_TC10_MISC32_VBAT_COM_WR                BIT(15)
#define LAN887X_DEV30_COMMON_TC10_MISC32_VAL \
                     (LAN887X_DEV30_COMMON_TC10_MISC32_INH_EN_TC10 |\
                     LAN887X_DEV30_COMMON_TC10_MISC32_ROSC_EN |\
                     LAN887X_DEV30_COMMON_TC10_MISC32_ROSC_STS |\
                     LAN887X_DEV30_COMMON_TC10_MISC32_VBAT_COM_WR)

#define LAN887X_DEV30_COMMON_TC10_MISC33                    (0x0C25U)
#define LAN887X_DEV30_COMMON_TC10_MISC33_WK_OUT_LEN         (0x004FU)
#define LAN887X_DEV30_COMMON_TC10_MISC33_WK_DEB_VAL         (0x0027U)

#define LAN887X_DEV30_COMMON_TC10_MISC36                    (0x0C27U)
#define LAN887X_DEV30_COMMON_TC10_MISC36_WUP_DEB_VAL        (0x0010U)
#define LAN887X_DEV30_COMMON_TC10_MISC36_SD_TUNE            (0x0200U)
#define LAN887X_DEV30_COMMON_TC10_MISC36_WK_MDI_EN          BIT(8)
#define LAN887X_DEV30_COMMON_TC10_MISC36_WUP_AUTO_FWD_EN    BIT(12)
#define LAN887X_DEV30_COMMON_TC10_MISC36_WUP_DET_FILT_LEN   (0x2000U)
#define LAN887X_DEV30_COMMON_TC10_MISC36_VBAT_PORT_WR       BIT(15)
#define LAN887X_DEV30_COMMON_TC10_MISC36_VAL \
                 (LAN887X_DEV30_COMMON_TC10_MISC36_WUP_DEB_VAL |\
                 LAN887X_DEV30_COMMON_TC10_MISC36_WUP_DET_FILT_LEN |\
                 LAN887X_DEV30_COMMON_TC10_MISC36_SD_TUNE |\
                 LAN887X_DEV30_COMMON_TC10_MISC36_VBAT_PORT_WR)

#define LAN887X_DEV30_COMMON_TC10_MISC37                    (0x0C28U)
#define LAN887X_DEV30_COMMON_TC10_MISC37_FORCE_SLEEP        BIT(0)

#define LAN887X_DEV30_COMMON_TC10_MISC46                    (0x0C29U)
#define LAN887X_DEV30_COMMON_TC10_MISC46_WK_PORT_TEST_MASK  GENMASK(7, 0)
#define LAN887X_DEV30_COMMON_TC10_MISC46_WK_PORT_TEST_VAL   (0x04U)

#define LAN887X_DEV30_COMMON_TC10_SLEEP_ABRT                (0x0C2D)
#define LAN887X_DEV30_COMMON_TC10_SLEEP_ABRT_SLEEP_ABORT    BIT(5)
#define LAN887X_DEV30_COMMON_TC10_SLEEP_ABRT_SLEEP_RJCT     BIT(4)

#define LAN887X_DEV30_COMMON_TC10_SENDZ_MINWAIT_TMR_CFG     (0xC2FU)
#endif //MEPA_OPT_TC10

#define LAN887X_VEND_CTRL_STAT_REG      (0x8013U)
#define LAN887X_AN_LOCAL_CFG_FAULT      BIT(10)
#define LAN887X_AN_LOCAL_SLAVE          BIT(9)
#define LAN887X_AN_LOCAL_MASTER         BIT(8)

/* End:: DEV-0x1E Registers */

#endif //LAN887X_REGISTERS_H
