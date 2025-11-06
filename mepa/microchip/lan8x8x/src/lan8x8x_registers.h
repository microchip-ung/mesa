// Copyright (c) 2004-2024 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN8X8X_REGISTERS_H
#define LAN8X8X_REGISTERS_H

#define LAN8X8X_PHY_REG_ADDR(addr)      ((addr) & 0x00FFU)
#define PHY_REG_ADDR(addr) ((addr) & 0xFFFFU)
#define PHY_MMD_DEVAD(addr) (((addr) & 0x00FF0000U) >> 16U)

#define LAN8X8X_DEF_MASK    DEF_MASK

#define LAN8X8X_PMA_COMM_100T1_CTL_T1_TYPE_1000 (0x1U)

/* GPIO Registers */
#define LAN8X8X_GPIO_BASE_REG   (0xF020U)
#define LAN8X8X_GPIO_DIR    (LAN8X8X_GPIO_BASE_REG + 0U)
#define LAN8X8X_GPIO_DATA   (LAN8X8X_GPIO_BASE_REG + 2U)
/* Not found in ewood cml*/
#define LAN8X8X_REG_CONTROL1    (0xFFFF)

/* LED Registers */
#define LAN8X8X_LED_BASE_REG            (0xF010U)
#define LAN8X8X_COMM_LED1_LED0          (LAN8X8X_LED_BASE_REG + 1U)
#define LAN8X8X_COMM_LED3_LED2          (LAN8X8X_LED_BASE_REG + 2U)
#define LAN8X8X_LED_LINK_ACT_ANY_SPEED      (0x0U)
#define LAN8X8X_LED_LINK_ACT_1000_SPEED     (0x1U)
#define LAN8X8X_LED_LINK_ACT_100_SPEED      (0x2U)
#define LAN8X8X_LED_LINK_NO_ACT_ANY_SPEED   (0x3U)
#define LAN8X8X_LED_LOCAL_RXER_STATUS       (0x5U)
#define LAN8X8X_LED_REMOTE_RXER_STATUS      (0x6U)
#define LAN8X8X_LED_NEGOTIATED_SPEED        (0x7U)
#define LAN8X8X_LED_MASTER_SLAVE_MODE       (0x8U)
#define LAN8X8X_LED_PCS_TX_ERR_STATUS       (0x9U)
#define LAN8X8X_LED_PCS_RX_ERR_STATUS       (0xAU)
#define LAN8X8X_LED_PCS_TX_ACTIVITY         (0xBU)
#define LAN8X8X_LED_PCS_RX_ACTIVITY     (0xCU)
#define LAN8X8X_LED_WAKE_ON_LAN         (0xDU)
#define LAN8X8X_LED_FORCED_LED_OFF      (0xEU)
#define LAN8X8X_LED_FORCED_LED_ON       (0xFU)

#define CLK_RST_REG                 (0xF070U)

#define SERDES_CLOCK_CONTROL        (CLK_RST_REG + 0x0U)
#define SERDES_CMOS_IN_EN       BIT(3)
#define SERDES_CML_OUT_EN       BIT(1)
#define SERDES_CLOCK_CTL_EN         (SERDES_CMOS_IN_EN |\
                     SERDES_CML_OUT_EN)

#define LAN8X8X_RGMII_RX_DLL_CFG        (CLK_RST_REG + 0xAU)
#define LAN8X8X_RGMII_TX_DLL_CFG        (CLK_RST_REG + 0xBU)

#define LAN8X8X_RGMII_DELAY_EN          BIT(15)
#define LAN8X8X_RGMII_DLL_EN            BIT(0)
#define LAN8X8X_RGMII_DLL_CONF  (LAN8X8X_RGMII_DELAY_EN |\
                                 LAN8X8X_RGMII_DLL_EN)

#define SERDES_REG          (0xF502U)
#define SERDES_LANEA_DATAPATH_0     (SERDES_REG + 0x12U)
#define SERDES_TXPLL_CONTROL_0      (SERDES_REG + 0xBEU)
#define SERDES_TXPLL_DIVIDER_0      (SERDES_REG + 0xC0U)
#define SERDES_TXPLL_DIVIDER_1      (SERDES_REG + 0xC2U)
#define SERDES_TXPLL_DIVIDER_2      (SERDES_REG + 0xC4U)

#define SERDES_TXPLL_REFCLK_CTRL_0  (SERDES_REG + 0xC6U)
#define SERDES_TXPLL_REFCLK_TXCMOSREF   (0x100U)
#define SERDES_TXPLL_REFCLK_CMLOUTEN_L  BIT(4)
#define SERDES_TXPLL_REFCLK_CMLINEN_R   BIT(3)
#define SERDES_TXPLL_REFCLK_SET     (SERDES_TXPLL_REFCLK_CMLINEN_R | \
                     SERDES_TXPLL_REFCLK_CMLOUTEN_L | \
                     SERDES_TXPLL_REFCLK_TXCMOSREF)

#define SERDES_LANEA_DATAPATH_0     (SERDES_REG + 0x12U)
#define SERDES_LANEA_DRIVER_0       (SERDES_REG + 0x14U)
#define SERDES_LANEA_DRIVER_1       (SERDES_REG + 0x16U)
#define SERDES_LANEA_TRIM_0     (SERDES_REG + 0x2EU)
#define SERDES_TXA_DRVR_FSM_0       (SERDES_REG + 0xB6U)
#define SERDES_LANEA_TEST3_0        (SERDES_REG + 0x28U)
#define SERDES_LANEA_TXPWR_CTRL_0   (SERDES_REG + 0x30U)
#define SERDES_RXA_CDR_DIVIDERS_0   (SERDES_REG + 0x34U)
#define SERDES_RXA_FREQUENCY_DET_0  (SERDES_REG + 0x5EU)
#define SERDES_RXA_DESCAL_OVR_0     (SERDES_REG + 0x4CU)
#define SERDES_RXA_CTLE_CTRL_0      (SERDES_REG + 0x36U)
#define SERDES_RXA_DFEEM_CTRL_0     (SERDES_REG + 0x56U)
#define SERDES_LANEA_POWERDOWN_0    (SERDES_REG + 0x18U)
#define SERDES_RXA_PHCTRL_0     (SERDES_REG + 0x64U)
#define SERDES_TOP_PD_RST_0     (SERDES_REG + 0xB4U)

#define PCS1G_REG                       (0xF080U)
#define QSGMII_PCS1G_SOFT_RESET_REG     (PCS1G_REG + 0x1U)
#define QSGMII_PCS1G_SOFT_RESET_EN      BIT(0)

#define QSGMII_PCS1G_CONFIG         (PCS1G_REG + 0x2U)
#define QSGMII_SAVE_PREAMBLE_EN     BIT(11)
#define QSGMII_PCS_ENA          BIT(9)
#define QSGMII_SD_POL           BIT(7)
#define QSGMII_SD_ENA           BIT(6)
#define QSGMII_PCS1G_CFG_EN     (QSGMII_SD_ENA |\
                     QSGMII_SD_POL |\
                     QSGMII_PCS_ENA |\
                     QSGMII_SAVE_PREAMBLE_EN)

#define QSGMII_PCS1G_ANEG_CONFIG        (PCS1G_REG + 0x3U)
#define QSGMII_PCS1G_SW_RESOLVE_PRIORITY   BIT(5)
#define QSGMII_PCS1G_ANEG_RESTART   BIT(4)
#define QSGMII_PCS1G_ANEG_ENA       BIT(3)
#define QSGMII_PCS1G_ANEG_SET       (QSGMII_PCS1G_ANEG_ENA | \
                     QSGMII_PCS1G_SW_RESOLVE_PRIORITY | \
                     QSGMII_PCS1G_ANEG_RESTART)

#define QSGMII_ANEG_EN_REG                  (PCS1G_REG + 0xBU)
#define QSGMII_NP_DISABLE           BIT(2)
#define QSGMII_SGMII_USGMII_TX_CFG_EN       BIT(1)
#define QSGMII_ANEG_EN              BIT(0)
#define QSGMII_ANEG_CFG             (QSGMII_SGMII_USGMII_TX_CFG_EN |\
                         QSGMII_NP_DISABLE)

#define LAN8X8X_XGMII_GMII_BYPASS       (0xF0D8U)
#define LAN8X8X_XGMII_BYPASS_SEL        BIT(0)

/* SQI Registers */
#define LAN8X8X_SQI_1000_REG         (0x8820U)
#define LAN8X8X_SQI_100_REG          (0x8218U)
#define T1_DCQ_SQI_MSK          GENMASK(1, 3)
#define LAN8X8X_SQI_GET(v)  (((v) & T1_DCQ_SQI_MSK) >> ONE)

/* Cable Diagonistics Registers */
#define LAN8X8X_CD_CFG      (0x8918U)
#define LAN8X8X_CD_DONE     BIT(1)
#define LAN8X8X_CD_EN       BIT(0)

/*CONFIG DONE */
#define T1_1G_TOP_CTRL                          0x8900U
#define T1_1G_TOP_CTRL_CONFIG                   (T1_1G_TOP_CTRL + 0x2U)
#define T1_1G_TOP_CTRL_CONFIG_DONE              BIT(3)
#define T1_1G_TOP_CTRL_CONFIG_LINK_CTRL         BIT(0)
#define T1_1G_TOP_CTRL_CONFIG_SET               (T1_1G_TOP_CTRL_CONFIG_DONE | \
                                                 T1_1G_TOP_CTRL_CONFIG_LINK_CTRL)

#define T1_1G_E1000T1_PCS                       0x8300U
#define T1_1G_E1000T1_PCS_EN                    (T1_1G_E1000T1_PCS)
#define T1_1G_E1000T1_PCS_EN_LINK_SYNC_SW       BIT(2)
#define T1_1G_E1000T1_PCS_EN_RXPCS_DEFRAMER     BIT(1)
#define T1_1G_E1000T1_PCS_EN_TXPCS_FRAMER       BIT(0)
#define T1_1G_E1000T1_PCS_EN_                   (T1_1G_E1000T1_PCS_EN_LINK_SYNC_SW | \
                                                 T1_1G_E1000T1_PCS_EN_RXPCS_DEFRAMER | \
                                                 T1_1G_E1000T1_PCS_EN_TXPCS_FRAMER)

/* Loopback Registers */
#define T1_1G_E100T1_PCS_REMOTE_LPBK    (32768U)
#define T1_1G_E1000T1_PCS_REMOTE_LPBK   (33570U)
#define T1_1G_PCS_REMOTE_LPBK       BIT(0)

#define CHIPTOP         (0xF0C0U)

#define XGMII_GMII_BYPASS       (CHIPTOP + 0x18U)
#define MACSEC_MEGABLK_BYPASS_SEL   BIT(2)
#define GMII_BYPASS_SEL         BIT(1)
#define XGMII_BYPASS_SEL        BIT(0)

#define OTP_STRAP_READ_REG              (CHIPTOP + 0x38U)
#define OTP_STRAP_READ_AUTO_MODE_EN     BIT(3)
#define OTP_STRAP_READ_SPEED_SEL        BIT(2)
#define OTP_STRAP_READ_AUTO_NEG_EN      BIT(1)
#define OTP_STRAP_READ_MST_SLV_SEL      BIT(0)

#define T1_OTP_RO                       (0xF040U)

#define T1_OTP_RO_FEAT_DIS              (T1_OTP_RO + 0x12U)
#define T1_OTP_RO_FEAT_DIS_1000M        BIT(4)
#define T1_OTP_RO_FEAT_DIS_100M         BIT(3)
#define T1_OTP_RO_FEAT_DIS_1588         BIT(2)
#define T1_OTP_RO_FEAT_DIS_MS256        BIT(1)
#define T1_OTP_RO_FEAT_DIS_MS           BIT(0)

#define T1_OTP_RO_PART_ID               (T1_OTP_RO + 0x13U)

#define OTP_STRAP_OVERRIDE              (T1_OTP_RO + 0x15U)
#define OTP_STRAP_OVERRIDE_EN           BIT(7)
#define OTP_STRAP_AUTO_MODE_EN          BIT(5)
#define OTP_STRAP_SPEED_SEL             BIT(4)
#define OTP_STRAP_MAC_MODE              GENMASK(3, 2)
#define OTP_STRAP_AUTO_NEG_EN           BIT(1)
#define OTP_STRAP_MST_SLV_SEL           BIT(0)

#define T1_1G_TOP_CTRL              0x8900U
#define T1_1G_TOP_CTRL_CONFIG           (T1_1G_TOP_CTRL + 0x2U)
#define T1_1G_TOP_CTRL_IEEE_POWERDOWN_PMD   BIT(4)
#define T1_1G_TOP_CTRL_CONFIG_DONE      BIT(3)
#define T1_1G_TOP_CTRL_SOFT_RESET       BIT(1)
#define T1_1G_TOP_CTRL_CONFIG_LINK_CTRL     BIT(0)
#define T1_1G_TOP_CTRL_CONFIG_SET       (T1_1G_TOP_CTRL_CONFIG_DONE | \
                         T1_1G_TOP_CTRL_CONFIG_LINK_CTRL)

#define T1_100M_CD_CFG          (T1_1G_TOP_CTRL + 0x18U)
#define T1_100M_CD_DONE         BIT(1)
#define T1_100M_CD_EN           BIT(0)

#define TC12_HDD_TDR            (T1_1G_TOP_CTRL + 0x30U)
#define TC12_HDD_TDR_LOC        GENMASK(8, 5)
#define T1_100M_CD_LOC          GENMASK(8, 4)
;
//Cable diag length to fault
#define TC12_HDD_TDR_CD_NO_ERR  (0x0U) //No Error
#define TC12_HDD_TDR_CD_LOC1  (0x1U) // Error between 0-1.5 m away
#define TC12_HDD_TDR_CD_LOC2  (0x3U) // Error between 1.5-3m away
#define TC12_HDD_TDR_CD_LOC3  (0x4U) // Error between 3 -4.5m away
#define TC12_HDD_TDR_CD_LOC4  (0x6U) // Error between 4.5 - 6m away
#define TC12_HDD_TDR_CD_LOC5  (0x7U) // Error between 6 - 7.5m away
#define TC12_HDD_TDR_CD_LOC6  (0x9U) // Error between 7.5-9m away
#define TC12_HDD_TDR_CD_LOC7  (0xAU) // Error between 9 - 10.5m away
#define TC12_HDD_TDR_CD_LOC8  (0xCU) // Error between 10.5 - 12m away
#define TC12_HDD_TDR_CD_LOC9  (0xDU) // Error between 12 - 13.5m away
#define TC12_HDD_TDR_CD_LOC10  (0xFU) // Error between 13.5 - 15m away
#define TC12_HDD_TDR_CD_LOC11  (0x3FU) // Error about 15m

#define TC12_HDD_TDR_PAIR_0 (0U)

#define TC12_HDD_TDR_LEN_0_M  (0U)
#define TC12_HDD_TDR_LEN_2_M  (2U)
#define TC12_HDD_TDR_LEN_3_M  (3U)
#define TC12_HDD_TDR_LEN_5_M  (5U)
#define TC12_HDD_TDR_LEN_6_M  (6U)
#define TC12_HDD_TDR_LEN_8_M  (8U)
#define TC12_HDD_TDR_LEN_9_M  (9U)
#define TC12_HDD_TDR_LEN_11_M (11U)
#define TC12_HDD_TDR_LEN_12_M (12U)
#define TC12_HDD_TDR_LEN_14_M (14U)
#define TC12_HDD_TDR_LEN_15_M (15U)
#define TC12_HDD_TDR_LEN_MAX_M  (16U)

#define TC12_HDD_TDR_STS        GENMASK(4, 8)

//Cable diag status
#define TC12_HDD_TDR_LINK_UP      0xDU
#define TC12_HDD_TDR_TST_ACTIVE   0x8U
#define TC12_HDD_TDR_CBL_OK       0x7U
#define TC12_HDD_TDR_CBL_OPEN     0x6U
#define TC12_HDD_TDR_HIG_NOISE    0x5U
#define TC12_HDD_TDR_CBL_SHORT    0x3U

#define TC12_HDD_TDR_STS_DONE       (TC12_HDD_TDR_TST_ACTIVE << 4U)
#define TC12_HDD_TDR_STS_GET(x)         (((x) & TC12_HDD_TDR_STS) >> 4U)

#define TC12_HDD_TDR_ACTIVE     GENMASK(0, 2)
#define TC12_HDD_TDR_ENABLE     BIT(1)
#define TC12_HDD_TDR_DISABLE    BIT(0)

#define T1_100M_E100T1_PCS          0x8000U

#define T1_1G_ECMT1_PMD             0x8000U
#define T1_1G_ECMT1_PMD_LDRV_TMR        (T1_1G_ECMT1_PMD + 0xEU)

#define T1_1G_E100T1_PMD            0x8000U
#define T1_1G_E100T1_PMD_ADPLL_CFG_0        (T1_1G_E100T1_PMD + 0x40U)

#define T1_1G_E1000T1_PMD           0x8100U
#define T1_1G_E1000T1_PMD_LCPLL_CFG_0       (T1_1G_E1000T1_PMD)

#define T1_1G_E100T1_PMA        0x8200U
#define T1_1G_E1000T1_PMA       0x8800U

#define T1_1G_E100T1_PMA_ADFE_CFG2      (T1_1G_E100T1_PMA + 0x2AU)
#define T1_1G_E100T1_PMA_ADFE_CFG3      (T1_1G_E100T1_PMA + 0x2CU)
#define T1_1G_E1000T1_PMA_ADFE_CFG3     (T1_1G_E1000T1_PMA + 0x34U)

#define T1_1G_RI_ABB_CTRL_0         0x8300U

#define T1_AUTONEG_STATUS           0x8002U
#define T1_AUTONEG_MS_CONFIG_FAULT      BIT(1)
#define T1_AUTONEG_CONFIG_AS_MASTER     BIT(0)

/* Interrupts */
#define LAN8X8X_INT_STS0_SC     (CHIPTOP + 0x20U)
#define LAN8X8X_INT_EN0_SC              (CHIPTOP + 0x24U)
#define LAN8X8X_INT_EN0_MAC_INTRF       BIT(11)
#define LAN8X8X_INT_EN0_EPG     BIT(10)
#define LAN8X8X_INT_EN0_GPIO            BIT(9)
#define LAN8X8X_INT_EN0_WDT     BIT(8)
#define LAN8X8X_INT_EN0_TC10_PRT        BIT(7)
#define LAN8X8X_INT_EN0_CHIP_TOP        BIT(6)
#define LAN8X8X_INT_EN0_PVT     BIT(5)
#define LAN8X8X_INT_EN0_TC10_COM        BIT(4)
#define LAN8X8X_INT_EN0_UVOV            BIT(3)
#define LAN8X8X_INT_EN0_T1_DATA_FAULT   BIT(2)
#define LAN8X8X_INT_EN0_T1_FUNC_SC      BIT(1)
#define LAN8X8X_INT_EN0_T1_FUNC         BIT(0)

#define LAN8X8X_INT_STS1_SC     (CHIPTOP + 0x21U)
#define LAN8X8X_INT_EN1_SC      (CHIPTOP + 0x25U)
#define LAN8X8X_INT_EN1_MS_EG_EN    BIT(8)
#define LAN8X8X_INT_EN1_MS_IG_EN    BIT(7)
#define LAN8X8X_INT_EN1_MS_FCB_EN   BIT(6)
#define LAN8X8X_INT_EN1_MS_HMAC_EN  BIT(5)
#define LAN8X8X_INT_EN1_MS_LMAC_EN  BIT(4)
#define LAN8X8X_INT_EN1_PTP_PRT     BIT(0)

#define T1_IRQ              (0x8500U)
#define LAN8X8X_INT_IRQ_FUNC_STS    (T1_IRQ)
#define LAN8X8X_INT_IRQ_FUNC_MSK    (T1_IRQ + 2U)
#define LAN8X8X_INT_IRQ_FUNC_CLR    (T1_IRQ + 4U)
#define LAN8X8X_INT_SLEEP_FAIL      BIT(8)
#define LAN8X8X_INT_SLEEP_MODE      BIT(7)
#define LAN8X8X_INT_MS_TRAINING_COMP    BIT(6)
#define LAN8X8X_INT_LINK_CHANGE_1G  BIT(2)
#define LAN8X8X_INT_LINK_CHANGE     BIT(1)

#endif //LAN8X8X_REGISTERS_H
