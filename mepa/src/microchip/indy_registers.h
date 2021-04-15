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

#define INDY_EXT_PAGE_2 2
#define INDY_EXT_PAGE_3 3
#define INDY_EXT_PAGE_4 4
#define INDY_EXT_PAGE_5 5
// Direct registers

// Register - 0
#define INDY_BASIC_CONTROL 0
#define INDY_F_BASIC_CTRL_SPEED_SEL_BIT_1 INDY_BIT(6)
#define INDY_F_BASIC_CTRL_DUP_MODE        INDY_BIT(8)
#define INDY_F_BASIC_CTRL_RESTART_ANEG    INDY_BIT(9)
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

// Register - 22
#define INDY_EXT_PAGE_ACCESS_CTRL 22
#define INDY_F_EXT_PAGE_ACCESS_CTRL_EP_FUNC 0x4000

#define INDY_EXT_PAGE_ACCESS_ADDR_DATA 23

// Register - 24
#define INDY_GPHY_INTR_ENA 24
// Same bit fields of this register apply to interrupt status register also
#define INDY_F_GPHY_INTR_ENA_FLF_INTR INDY_BIT(12)
#define INDY_F_GPHY_INTR_ENA_LINK_DOWN INDY_BIT(2)

// Register - 27
#define INDY_GPHY_INTR_STATUS 27

// Register - 30 .... Reserved register for applying connector loopback
#define INDY_RESV_CON_LOOP 30

//====================================================================================
//      Extended Page 2
//====================================================================================
// Register 2
#define INDY_OPERATION_MODE_STRAP_LOW INDY_EXT_PAGE_2, 2

// Register 81
#define INDY_OPERATION_MODE_STRAP_HIGH INDY_EXT_PAGE_2, 81


//====================================================================================
//      Extended Page 4
//====================================================================================
// Register 0
#define INDY_STRAP_STATUS_1 INDY_EXT_PAGE_4, 0
#define INDY_X_STRAP_STATUS_STRAP_PHYAD(x) INDY_EXTRACT_BITFIELD(x, 0, 5)

// Register 32
#define INDY_GPIO_EN1   4, 32

// Register 33
#define INDY_GPIO_EN2   4, 33

// Register 34
#define INDY_GPIO_DIR1  4, 34

// Register 35
#define INDY_GPIO_DIR2  4, 35

// Register 38
#define INDY_GPIO_DATA1 4, 38

// Register 39
#define INDY_GPIO_DATA2 4, 39

// Register 66
#define INDY_QSGMII_HARD_RESET INDY_EXT_PAGE_4, 66

// Register 69
#define INDY_QSGMII_AUTO_ANEG INDY_EXT_PAGE_4, 69
#define INDY_F_QSGMII_AUTO_ANEG_AUTO_ANEG_ENA INDY_BIT(0)

// Register 137
#define INDY_QSGMII_SERDES_MISC_CTRL INDY_EXT_PAGE_4, 137
#define INDY_F_QSGMII_SERDES_MISC_CTRL_LB_MODE INDY_BIT(4)
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

#endif
