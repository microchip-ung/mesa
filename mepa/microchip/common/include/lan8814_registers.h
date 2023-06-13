// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_INDY_REGISTERS_H
#define _MEPA_INDY_REGISTERS_H

// Macros
#define INDY_DEF_MASK 0xffff
#define INDY_BIT(x) (1 << x)
#define INDY_BIT_MASK(x) ((1U << (x)) - 1)

#define INDY_EXTRACT_BITFIELD(value, offset, width)  (((value) >> (offset)) & INDY_BIT_MASK(width))
#define INDY_ENCODE_BITFIELD(value, offset, width)   (((value) & INDY_BIT_MASK(width)) << (offset))
#define INDY_ENCODE_BITMASK(offset, width) (INDY_BIT_MASK(width) << (offset))

#define INDY_EXT_PAGE_0  0
#define INDY_EXT_PAGE_1  1
#define INDY_EXT_PAGE_2  2
#define INDY_EXT_PAGE_3  3
#define INDY_EXT_PAGE_4  4
#define INDY_EXT_PAGE_5  5
#define INDY_EXT_PAGE_28 28
#define INDY_EXT_PAGE_29 29
#define INDY_EXT_PAGE_31 31

#define INDY_MMD_7      7
// Direct registers

// Register - 0
#define INDY_BASIC_CONTROL 0
#define INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1 INDY_BIT(6)
#define INDY_F_BASIC_CTRL_DUP_MODE        INDY_BIT(8)
#define INDY_F_BASIC_CTRL_RESTART_ANEG    INDY_BIT(9)
#define INDY_F_BASIC_CTRL_ISO_MODE_EN     INDY_BIT(10)
#define INDY_F_BASIC_CTRL_SOFT_POW_DOWN   INDY_BIT(11)
#define INDY_F_BASIC_CTRL_ANEG_ENA        INDY_BIT(12)
#define INDY_F_BASIC_CTRL_SPEED_SEL_BIT_0 INDY_BIT(13)
#define INDY_F_BASIC_CTRL_LOOPBACK        INDY_BIT(14)
#define INDY_F_BASIC_CTRL_SOFT_RESET      INDY_BIT(15)

// Register - 1
#define INDY_BASIC_STATUS 1
#define INDY_F_BASIC_STATUS_LINK_STATUS     INDY_BIT(2)
#define INDY_F_BASIC_STATUS_ANEG_COMPLETE   INDY_BIT(5)
#define INDY_F_BASIC_STATUS_EXT_STATUS      INDY_BIT(8)
#define INDY_F_BASIC_STATUS_100_T2_HALF_DUP INDY_BIT(9)
#define INDY_F_BASIC_STATUS_100_T2_FULL_DUP INDY_BIT(10)
#define INDY_F_BASIC_STATUS_10_T_HALF_DUP   INDY_BIT(11)
#define INDY_F_BASIC_STATUS_10_T_FULL_DUP   INDY_BIT(12)

// Register - 3
#define INDY_DEVICE_ID_2 3
#define INDY_X_DEV_ID_PHY_ID(x)    INDY_EXTRACT_BITFIELD(x, 10, 6)
#define INDY_X_DEV_ID_MODEL(x)     INDY_EXTRACT_BITFIELD(x, 4, 6)
#define INDY_X_DEV_ID_REV(x)       INDY_EXTRACT_BITFIELD(x, 0, 4)

// Register - 4
#define INDY_ANEG_ADVERTISEMENT 4

// Register - 5
#define INDY_ANEG_LP_BASE 5
#define INDY_F_ANEG_LP_BASE_10_T_HALF_DUP INDY_BIT(5)
#define INDY_F_ANEG_LP_BASE_10_T_FULL_DUP INDY_BIT(6)
#define INDY_F_ANEG_LP_BASE_100_X_HALF_DUP INDY_BIT(7)
#define INDY_F_ANEG_LP_BASE_100_X_FULL_DUP INDY_BIT(8)
#define INDY_F_ANEG_LP_BASE_SYM_PAUSE  INDY_BIT(10)
#define INDY_F_ANEG_LP_BASE_ASYM_PAUSE INDY_BIT(11)

// Register - 9
#define INDY_ANEG_MSTR_SLV_CTRL 9
#define INDY_F_ANEG_MSTR_SLV_CTRL_1000_T_FULL_DUP INDY_BIT(9)
#define INDY_F_ANEG_MSTR_SLV_CTRL_CFG_VAL         INDY_BIT(11)
#define INDY_F_ANEG_MSTR_SLV_CTRL_CFG_ENA         INDY_BIT(12)

// Register - 10
#define INDY_ANEG_MSTR_SLV_STATUS 10
#define INDY_F_ANEG_MSTR_SLV_STATUS_CFG_FAULT INDY_BIT(15)
#define INDY_F_ANEG_MSTR_SLV_STATUS_CFG_RES   INDY_BIT(14)
#define INDY_F_ANEG_MSTR_SLV_LOCAL_RCVR_STATUS      INDY_BIT(13)
#define INDY_F_ANEG_MSTR_SLV_REMOTE_RCVR_STATUS     INDY_BIT(12)
#define INDY_F_ANEG_MSTR_SLV_STATUS_1000_T_FULL_DUP INDY_BIT(11)
#define INDY_F_ANEG_MSTR_SLV_STATUS_1000_T_HALF_DUP INDY_BIT(10)

#define INDY_MMD_ACCESS_CTRL 13
#define INDY_F_MMD_ACCESS_CTRL_MMD_FUNC 0x4000

#define INDY_MMD_ACCESS_ADDR_DATA 14

// Register - 15
#define INDY_EXTENDED_STATUS 15
#define INDY_F_EXT_STATUS_1000_T_HALF_DUP INDY_BIT(12)
#define INDY_F_EXT_STATUS_1000_T_FULL_DUP INDY_BIT(13)
#define INDY_F_EXT_STATUS_1000_X_HALF_DUP INDY_BIT(14)
#define INDY_F_EXT_STATUS_1000_X_FULL_DUP INDY_BIT(15)

// Register - 17
#define INDY_PCS_LOOP_POLARITY_CTRL 17
#define INDY_F_PCS_LOOP_CTRL_PORT_LOOP INDY_BIT(8)

// Register - 18
#define INDY_CABLE_DIAG 18
#define INDY_F_CABLE_DIAG_TEST_ENA   INDY_BIT(15)
#define INDY_F_CABLE_DIAG_DISABLE_TX INDY_BIT(14)
#define INDY_F_CABLE_TEST_PAIR(x)    INDY_ENCODE_BITFIELD(x, 12, 2)
#define INDY_M_CABLE_TEST_PAIR       INDY_ENCODE_BITMASK(12, 2)
#define INDY_X_CABLE_DIAG_STATUS(x)  INDY_EXTRACT_BITFIELD(x, 8, 2)
#define INDY_X_CABLE_DIAG_DATA(x)    INDY_EXTRACT_BITFIELD(x, 0, 8)

// Register - 22
#define INDY_EXT_PAGE_ACCESS_CTRL 22
#define INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC 0x4000
#define INDY_F_EXT_PAGE_ACCESS_CTRL_INCR_RD_WR 0x8000

#define INDY_EXT_PAGE_ACCESS_ADDR_DATA 23

// Register - 24
#define INDY_GPHY_INTR_ENA 24
// Same bit fields of this register apply to interrupt status register also
#define INDY_F_GPHY_INTR_ENA_FLF_INTR INDY_BIT(12)
#define INDY_F_GPHY_INTR_ENA_LINK_DOWN INDY_BIT(2)

// Register - 26
#define INDY_UNH_TEST 26
#define INDY_F_TEST_RX_CLK INDY_BIT(8)

// Register - 27
#define INDY_GPHY_INTR_STATUS 27

// Register - 28
#define INDY_GPHY_DBG_CTL1 28
#define INDY_F_MDI_SET INDY_BIT(7)
#define INDY_F_SWAPOFF INDY_BIT(6)

// Register - 30 .... Reserved register for applying connector loopback
#define INDY_RESV_CON_LOOP 30
#define INDY_F_EXT_LPBK INDY_BIT(3)

//====================================================================================
//      Extended Page 0
//====================================================================================
// Register 15
#define INDY_FLF_CONFIG_STATUS INDY_EXT_PAGE_0, 15
#define INDY_FLF_CFG_STAT_LINK_DOWN INDY_BIT(0)
#define INDY_FLF_CFG_STAT_FLF_ENABLE INDY_BIT(1)
#define INDY_FLF_CFG_STAT_FLF_STATUS INDY_BIT(2)

//====================================================================================
//      Extended Page 1
//====================================================================================
#define INDY_DFE_INIT2_100                INDY_EXT_PAGE_1, 119
#define INDY_PGA_TABLE_1G_ENTRY_0         INDY_EXT_PAGE_1, 121
#define INDY_PGA_TABLE_1G_ENTRY_1         INDY_EXT_PAGE_1, 122
#define INDY_PGA_TABLE_1G_ENTRY_2         INDY_EXT_PAGE_1, 123
#define INDY_PGA_TABLE_1G_ENTRY_3         INDY_EXT_PAGE_1, 124
#define INDY_PGA_TABLE_1G_ENTRY_4         INDY_EXT_PAGE_1, 125
#define INDY_PGA_TABLE_1G_ENTRY_5         INDY_EXT_PAGE_1, 126
#define INDY_PGA_TABLE_1G_ENTRY_6         INDY_EXT_PAGE_1, 127
#define INDY_PGA_TABLE_1G_ENTRY_7         INDY_EXT_PAGE_1, 128
#define INDY_PGA_TABLE_1G_ENTRY_8         INDY_EXT_PAGE_1, 129
#define INDY_PGA_TABLE_1G_ENTRY_9         INDY_EXT_PAGE_1, 130
#define INDY_PGA_TABLE_1G_ENTRY_10        INDY_EXT_PAGE_1, 131
#define INDY_PGA_TABLE_1G_ENTRY_11        INDY_EXT_PAGE_1, 132
#define INDY_PGA_TABLE_1G_ENTRY_12        INDY_EXT_PAGE_1, 133
#define INDY_PGA_TABLE_1G_ENTRY_13        INDY_EXT_PAGE_1, 134
#define INDY_PGA_TABLE_1G_ENTRY_14        INDY_EXT_PAGE_1, 135
#define INDY_PGA_TABLE_1G_ENTRY_15        INDY_EXT_PAGE_1, 136
#define INDY_PGA_TABLE_1G_ENTRY_16        INDY_EXT_PAGE_1, 137
#define INDY_PGA_TABLE_1G_ENTRY_17        INDY_EXT_PAGE_1, 138
#define INDY_PD_CONTROLS                  INDY_EXT_PAGE_1, 157
#define INDY_LINK_QUALITY_MONITOR_SETTING INDY_EXT_PAGE_1, 142

#define INDY_DCQ_CTRL                     INDY_EXT_PAGE_1, 230
#define INDY_F_DCQ_CTRL_READ_CAPTURE      INDY_BIT(15)
#define INDY_M_DCQ_CTRL_CHANNEL_MASK      INDY_ENCODE_BITMASK(0, 2)
#define INDY_DCQ_SQI                      INDY_EXT_PAGE_1, 228
#define INDY_X_DCQ_SQI_VALUE(x)           INDY_EXTRACT_BITFIELD(x, 1, 3)

//====================================================================================
//      Extended Page 2
//====================================================================================
// Register 2
#define INDY_OPERATION_MODE_STRAP_LOW INDY_EXT_PAGE_2, 2

// Register 9
#define INDY_SELFTEST_PKT_CNT_LO INDY_EXT_PAGE_2, 9

// Register 10
#define INDY_SELFTEST_PKT_CNT_HI INDY_EXT_PAGE_2, 10

// Register 11
#define INDY_SELFTEST_STATUS INDY_EXT_PAGE_2, 11
#define INDY_F_SELFTEST_DONE      INDY_BIT(0)

// Register 12
#define INDY_SELFTEST_FRAME_CNT INDY_EXT_PAGE_2, 12
#define INDY_F_SELFTEST_FRAME_CNT_EN      INDY_BIT(0)

// Register 13
#define INDY_SELFTEST_PGEN_EN INDY_EXT_PAGE_2, 13
#define INDY_F_SELFTEST_PGEN_EN      INDY_BIT(0)

// Register 14
#define INDY_SELFTEST_EN_REG INDY_EXT_PAGE_2, 14
#define INDY_F_SELFTEST_RX_CRC_CHK_EN		INDY_BIT(8)
#define INDY_F_SELFTEST_TX_CRC_CHK_EN		INDY_BIT(4)
#define INDY_F_SELFTEST_EN			INDY_BIT(0)

// Register 15
#define INDY_1000BT_FIX_LATENCY_ENABLE INDY_EXT_PAGE_2, 15

// Register 60
#define INDY_SELFTEST_GOOD_CNT_LO INDY_EXT_PAGE_2, 60

// Register 61
#define INDY_SELFTEST_GOOD_CNT_HI INDY_EXT_PAGE_2, 61

// Register 62
#define INDY_SELFTEST_ERR_CNT_LO INDY_EXT_PAGE_2, 62

// Register 63
#define INDY_SELFTEST_ERR_CNT_HI INDY_EXT_PAGE_2, 63

// Register 74
#define INDY_ALIGN_SWAP INDY_EXT_PAGE_2, 74
#define INDY_F_ALIGN_TX_A_B_SWAP INDY_BIT(1)
#define INDY_M_ALIGN_TX_SWAP     INDY_ENCODE_BITMASK(0,2)

// Register 75
#define INDY_SOF INDY_EXT_PAGE_2, 75
#define INDY_M_SOF_PREEMPTION_ENABLE     INDY_ENCODE_BITMASK(8,2)

// Register 81
#define INDY_OPERATION_MODE_STRAP_HIGH INDY_EXT_PAGE_2, 81

//====================================================================================
//      Extended Page 3
//====================================================================================
// Register 14
#define INDY_EEE_WAKE_TX_TIMER            INDY_EXT_PAGE_3, 14

//====================================================================================
//      Extended Page 4
//====================================================================================
// Register 0
#define INDY_STRAP_STATUS_1 INDY_EXT_PAGE_4, 0
#define INDY_X_STRAP_STATUS_STRAP_PHYAD(x) INDY_EXTRACT_BITFIELD(x, 0, 5)

// Register 8
#define INDY_CHIP_HARD_RESET INDY_EXT_PAGE_4, 8

// Register 32
#define INDY_GPIO_EN1   INDY_EXT_PAGE_4, 32

// Register 33
#define INDY_GPIO_EN2   INDY_EXT_PAGE_4, 33

// Register 34
#define INDY_GPIO_DIR1  INDY_EXT_PAGE_4, 34

// Register 35
#define INDY_GPIO_DIR2  INDY_EXT_PAGE_4, 35

// Register 38
#define INDY_GPIO_DATA1 INDY_EXT_PAGE_4, 38

// Register 39
#define INDY_GPIO_DATA2 INDY_EXT_PAGE_4, 39

// Register 49
#define INDY_GPIO_SOF_SEL INDY_EXT_PAGE_4, 49
#define INDY_M_GPIO_SOF_SEL_SOF0 INDY_ENCODE_BITMASK(0, 3)
#define INDY_M_GPIO_SOF_SEL_SOF1 INDY_ENCODE_BITMASK(3, 3)
#define INDY_M_GPIO_SOF_SEL_SOF2 INDY_ENCODE_BITMASK(6, 3)
#define INDY_M_GPIO_SOF_SEL_SOF3 INDY_ENCODE_BITMASK(9, 3)

// Register 51
#define INDY_CHIP_LVL_INTR_STATUS INDY_EXT_PAGE_4, 51

// Register 52
#define INDY_INTR_CTRL  INDY_EXT_PAGE_4, 52
#define INDY_INTR_CTRL_CHIP_LVL_ENA INDY_BIT(0)

// Register 66
#define INDY_QSGMII_HARD_RESET INDY_EXT_PAGE_4, 66

// Register 67
#define INDY_QSGMII_SOFT_RESET INDY_EXT_PAGE_4, 67

// Register 69
#define INDY_QSGMII_AUTO_ANEG INDY_EXT_PAGE_4, 69
#define INDY_F_QSGMII_AUTO_ANEG_AUTO_ANEG_ENA INDY_BIT(0)

// Register 137
#define INDY_QSGMII_SERDES_MISC_CTRL INDY_EXT_PAGE_4, 137
#define INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE INDY_BIT(4)

#define INDY_RCVRD_CLK_OUT_SEL_1 INDY_EXT_PAGE_4, 256
#define INDY_RCVRD_CLK_OUT_DIV_1 INDY_EXT_PAGE_4, 257
#define INDY_RCVRD_CLK_OUT_SEL_2 INDY_EXT_PAGE_4, 258
#define INDY_RCVRD_CLK_OUT_DIV_2 INDY_EXT_PAGE_4, 259

// Register 139
#define INDY_SERDES_CR_CONTROL INDY_EXT_PAGE_4, 139
#define INDY_F_SERDES_CR_CONTROL_0 INDY_BIT(0)
#define INDY_F_SERDES_CR_CONTROL_1 INDY_BIT(1)

// Register 140
#define INDY_SERDES_CR_ADDR INDY_EXT_PAGE_4, 140

// Register 141
#define INDY_SERDES_CR_DATA INDY_EXT_PAGE_4, 141

// Register 142
#define INDY_SERDES_CLOCK_CONF INDY_EXT_PAGE_4, 142

//====================================================================================
//      Extended Page 5
//====================================================================================
// Register 0
#define INDY_LED_CONTROL_REG1 INDY_EXT_PAGE_5, 0
#define INDY_F_LED_CONTROL_KSZ_LED_MODE INDY_BIT(6)

// Register 1
#define INDY_LED_CONTROL_REG2 INDY_EXT_PAGE_5, 1

// Register - 5.19
#define INDY_QSGMII_PCS1G_ANEG_CONFIG INDY_EXT_PAGE_5, 19
#define INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_ENA INDY_BIT(3)
#define INDY_F_QSGMII_PCS1G_ANEG_CONFIG_ANEG_RESTART INDY_BIT(4)

// Register - 5.20
#define INDY_QSGMII_PCS1G_ANEG_TX_ADVERTISE_CAP INDY_EXT_PAGE_5, 20

// Register - 5.24
#define INDY_QSGMII_PCS1G_DEBUG INDY_EXT_PAGE_5, 24
#define INDY_F_QSGMII_PCS1G_DBG_GMII_LOOPBACK INDY_BIT(0)
#define INDY_F_QSGMII_PCS1G_DBG_TBI_HOST_LOOPBACK INDY_BIT(1)

// Register - 5.32,33,34
#define INDY_RX_RA_FIFO_THRESHOLDS_1 INDY_EXT_PAGE_5, 32
#define INDY_RX_RA_FIFO_THRESHOLDS_2 INDY_EXT_PAGE_5, 33
#define INDY_RX_RA_FIFO_THRESHOLDS_3 INDY_EXT_PAGE_5, 34

// Register - 5.38,39,40
#define INDY_TX_RA_FIFO_THRESHOLDS_1 INDY_EXT_PAGE_5, 38
#define INDY_TX_RA_FIFO_THRESHOLDS_2 INDY_EXT_PAGE_5, 39
#define INDY_TX_RA_FIFO_THRESHOLDS_3 INDY_EXT_PAGE_5, 40

//Register - 5.44,45
#define INDY_TX_RA_FIFO_RESET INDY_EXT_PAGE_5, 44
#define INDY_RX_RA_FIFO_RESET INDY_EXT_PAGE_5, 45

//====================================================================================
//      Extended Page 28
//====================================================================================
#define INDY_POWER_MGMT_MODE_0  INDY_EXT_PAGE_28, 16
#define INDY_POWER_MGMT_MODE_1  INDY_EXT_PAGE_28, 17
#define INDY_POWER_MGMT_MODE_2  INDY_EXT_PAGE_28, 18
#define INDY_POWER_MGMT_MODE_3  INDY_EXT_PAGE_28, 19
#define INDY_POWER_MGMT_MODE_4  INDY_EXT_PAGE_28, 20
#define INDY_POWER_MGMT_MODE_5  INDY_EXT_PAGE_28, 21
#define INDY_POWER_MGMT_MODE_6  INDY_EXT_PAGE_28, 22
#define INDY_POWER_MGMT_MODE_7  INDY_EXT_PAGE_28, 23
#define INDY_POWER_MGMT_MODE_8  INDY_EXT_PAGE_28, 24
#define INDY_POWER_MGMT_MODE_9  INDY_EXT_PAGE_28, 25
#define INDY_POWER_MGMT_MODE_10 INDY_EXT_PAGE_28, 26
#define INDY_POWER_MGMT_MODE_11 INDY_EXT_PAGE_28, 27
#define INDY_POWER_MGMT_MODE_12 INDY_EXT_PAGE_28, 28
#define INDY_POWER_MGMT_MODE_13 INDY_EXT_PAGE_28, 29
#define INDY_POWER_MGMT_MODE_14 INDY_EXT_PAGE_28, 30
#define INDY_POWER_MGMT_MODE_15 INDY_EXT_PAGE_28, 31

// Register 4
#define INDY_ANALOG_CONTROL_4   INDY_EXT_PAGE_28, 4

// Register 9
#define INDY_AFED_CONTROL       INDY_EXT_PAGE_28, 9

//====================================================================================
//      Extended Page 29
//====================================================================================
// Register 1
#define INDY_ANALOG_CONTROL_1 INDY_EXT_PAGE_29, 1

// Register 13
#define INDY_ANALOG_CONTROL_10 INDY_EXT_PAGE_29, 13

//====================================================================================
//      Extended Page 31
//====================================================================================
#define INDY_CLOCK_MANAGEMENT_MODE_5 INDY_EXT_PAGE_31, 13

//====================================================================================
//      MMD 7
//====================================================================================
// Register 61
#define INDY_LINK_PARTNER_EEE_ABILITY INDY_MMD_7, 61
#define INDY_F_LP_EEE_ABILITY_100_BT INDY_BIT(1)
#define INDY_F_LP_EEE_ABILITY_1000_BT INDY_BIT(2)

#endif
