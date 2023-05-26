// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN8770_REGISTERS_H
#define LAN8770_REGISTERS_H

// Macros
#define ZERO                    (0)
#define ONE                   (1U)
#define LAN8770_LINKUP        (ONE)
#define LAN8770_LINKDOWN      (ZERO)

#define LAN8770_DEF_MASK    (0xFFFFU)
#define LAN8770_BIT(x)      (ONE << x)
#define LAN8770_CLEAR_BIT(x, n)      (x & ~(LAN8770_BIT(n)))
#define LAN8770_BIT_MASK(x) ((ONE << (x)) - ONE)

#define LAN8770_EXTRACT_BITFIELD(value, offset, width)  (((value) >> (offset)) & LAN8770_BIT_MASK(width))
#define LAN8770_ENCODE_BITFIELD(value, offset, width)   (((value) & LAN8770_BIT_MASK(width)) << (offset))
#define LAN8770_ENCODE_BITMASK(offset, width)           (LAN8770_BIT_MASK(width) << (offset))

// Direct registers
#define LAN8770_PHY_BANK_SMI            (0U)
#define LAN8770_PHY_BANK_MISC           (1U)
#define LAN8770_PHY_BANK_PCS            (2U)
#define LAN8770_PHY_BANK_AFE            (3U)
#define LAN8770_PHY_BANK_DSP            (4U)
#define LAN8770_PHY_BANK_INSTRUMENT     (5U)

/**
 *  BANK-0 : SMI Main Registers
 **/
// Register - 0
/* Basic Control Register */
#define LAN8770_BASIC_CONTROL_OFFSET         (0x00)
/* 0x00 - 0x04  Reserved */
#define LAN8770_BASIC_CTRL_UNIDIR_EN         LAN8770_BIT(5)
#define LAN8770_BASIC_CTRL_SPEED_SEL_MSB     LAN8770_BIT(6)
#define LAN8770_BASIC_CTRL_COLLISION_TEST    LAN8770_BIT(7)
#define LAN8770_BASIC_CTRL_DUPLEX_MODE       LAN8770_BIT(8)
#define LAN8770_BASIC_CTRL_RESTART_AUTO_NEG  LAN8770_BIT(9)
#define LAN8770_BASIC_CTRL_ISOLATE           LAN8770_BIT(10)
#define LAN8770_BASIC_CTRL_POWER_DOWN        LAN8770_BIT(11)
#define LAN8770_BASIC_CTRL_AUTO_NEG_EN       LAN8770_BIT(12)
#define LAN8770_BASIC_CTRL_SPEED_SEL_LSB     LAN8770_BIT(13)
#define LAN8770_BASIC_CTRL_PCS_LOOPBACK      LAN8770_BIT(14)
#define LAN8770_BASIC_CTRL_SW_RESET          LAN8770_BIT(15)

// Register - 1
/*  Basic Status Register */
#define LAN8770_BASIC_STATUS_OFFSET          (0x01)
#define LAN8770_BASIC_STATUS_EXT_CAP         LAN8770_BIT(0)
#define LAN8770_BASIC_STATUS_JAB_DETECT      LAN8770_BIT(1)
#define LAN8770_BASIC_STATUS_RCV_LINK_STATUS LAN8770_BIT(2)
#define LAN8770_BASIC_STATUS_AUTO_NEG_ABL    LAN8770_BIT(3)
#define LAN8770_BASIC_STATUS_RMT_FAULT       LAN8770_BIT(4)
#define LAN8770_BASIC_STATUS_AUTO_NEG_CMP    LAN8770_BIT(5)
#define LAN8770_BASIC_STATUS_MF_PREAM_SUPP   LAN8770_BIT(6)
#define LAN8770_BASIC_STATUS_UNI_DIR_EN      LAN8770_BIT(7)
#define LAN8770_BASIC_STATUS_EXT_STATUS      LAN8770_BIT(8)
#define LAN8770_BASIC_STATUS_100BASE_T2_HD   LAN8770_BIT(9)
#define LAN8770_BASIC_STATUS_100BASE_T2_FD   LAN8770_BIT(10)
#define LAN8770_BASIC_STATUS_10BASE_TX_HD    LAN8770_BIT(11)
#define LAN8770_BASIC_STATUS_10BASE_TX_FD    LAN8770_BIT(12)
#define LAN8770_BASIC_STATUS_100BASE_TX_HD   LAN8770_BIT(13)
#define LAN8770_BASIC_STATUS_100BASE_TX_FD   LAN8770_BIT(14)
#define LAN8770_BASIC_STATUS_100BASE_T4      LAN8770_BIT(15)

// Register - 2
/*
Assigned to the 3rd through 18th bits of the Organizationally Unique
Identifier (OUI), respectively.
*/

/*PHY Identifier 1 Register*/
#define LAN8770_PHY_ID1_OFFSET                  (0x02)
#define LAN8770_PHY_ID_NUM0(x)              ((x << 2) & 0x03FFFCU)

// Register - 3
/*PHY Identifier 2 Register*/
#define LAN8770_PHY_ID2_OFFSET                  (0x03)
#define LAN8770_PHY_REV_NUM(x)              LAN8770_EXTRACT_BITFIELD(x, 0, 4)
#define LAN8770_PHY_MODEL_NUM(x)            LAN8770_EXTRACT_BITFIELD(x, 4, 6)
#define LAN8770_PHY_ID_NUM1(x)              ((LAN8770_EXTRACT_BITFIELD(x, 10, 6) << 18) & 0xFFFFFFFFU)

/* 0x04 - 0x08  Reserved for future expansion*/

/**
 TABLE 3-4: MODE0 CONFIGURATION STRAP
----------------------------------------------------------------------------------------------
| MODE0  |    Definition                     |   Default Register Bit Values                 |
|        |                                   |------------------------------------------------
|        |                                   |   Register 0x09        |      Register 0x0A   |
|        |                                   |   [Bit 11, Bit 12]     |      [Bit 14]        |
|--------|-----------------------------------|------------------------|-----------------------
| 0b     |    PHY is placed in slave mode    |   01b                  |      0b              |
| 1b     |    PHY is placed in master mode   |   11b                  |      1b              |
----------------------------------------------------------------------------------------------
 */
// Register - 9
#define LAN8770_MASTER_SLAVE_CTRL_OFFSET              (0x09) /*Master Slave Control Register*/
/* 0x00 - 0x07  Reserved */
#define LAN8770_MASTER_SLAVE_CTRL_1000BASE_T_HD     LAN8770_BIT(8)
#define LAN8770_MASTER_SLAVE_CTRL_1000BASE_T_FD     LAN8770_BIT(9)
#define LAN8770_MASTER_SLAVE_CTRL_PORT_TYP          LAN8770_BIT(10)
#define LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_VAL       LAN8770_BIT(11)
#define LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_EN        LAN8770_BIT(12) //Always 1
#define LAN8770_MASTER_SLAVE_CTRL_TEST_MODE_SET(x)  LAN8770_ENCODE_BITFIELD(x, 13, 3)
//Supporting macros
#define LAN8770_MASTER_SLAVE_CTRL_SET_MASTER          (LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_EN | LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_VAL)
#define LAN8770_MASTER_SLAVE_CTRL_SET_SLAVE         (LAN8770_MASTER_SLAVE_CTRL_MAN_CFG_EN)

// Register - 10
#define LAN8770_MASTER_SLAVE_STATUS_OFFSET                      (0x0A) /*Master Slave Status Register*/
#define LAN8770_MASTER_SLAVE_STATUS_IDLE_ERR_CNT(x)             LAN8770_EXTRACT_BITFIELD(x, 0, 8)
/* 0x08 - 0x09  Reserved */
#define LAN8770_MASTER_SLAVE_STATUS_LINK_PART_1000BASE_T_HD_CAP  LAN8770_BIT(10)
#define LAN8770_MASTER_SLAVE_STATUS_LINK_PART_1000BASE_T_FD_CAP  LAN8770_BIT(11)
#define LAN8770_MASTER_SLAVE_STATUS_RMT_RCV_STATUS               LAN8770_BIT(12)
#define LAN8770_MASTER_SLAVE_STATUS_LOC_RCV_STATUS               LAN8770_BIT(13)
#define LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL                    LAN8770_BIT(14)
#define LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL_MASK               LAN8770_ENCODE_BITMASK(14, 1)
#define LAN8770_MASTER_SLAVE_STATUS_CFG_FAULT                    LAN8770_BIT(15)
#define LAN8770_MASTER_SLAVE_STATUS_CFG_FAULT_MASK               LAN8770_ENCODE_BITMASK(15, 1)
//Supporting macros
#define LAN8770_MASTER_SLAVE_STATUS_IS_MASTER(x)                     ((x & LAN8770_MASTER_SLAVE_STATUS_CFG_RESOL_MASK) ? ONE : ZERO)
#define LAN8770_MASTER_SLAVE_STATUS_IS_FAULT(x)                    ((x & LAN8770_MASTER_SLAVE_STATUS_CFG_FAULT_MASK) ? ONE : ZERO)

/*0Bh - 0Eh Reserved for future expansion*/

// Register - 15
#define LAN8770_MDIO_CTRL1_OFFSET                             (0x0F) /*MDIO Control 1 Register*/
#define LAN8770_MDIO_CTRL1_TO_EN                        LAN8770_BIT(0)
#define LAN8770_MDIO_CTRL1_TO_CNT_GET(x)                LAN8770_EXTRACT_BITFIELD(x, 1, 4)
#define LAN8770_MDIO_CTRL1_TO_CNT_SET(x)                LAN8770_ENCODE_BITFIELD(x, 1, 4)
#define LAN8770_MDIO_CTRL1_IGN_IDLE_WUR_LPS             LAN8770_BIT(5)
#define LAN8770_MDIO_CTRL1_EN_DET_MST_MODE              LAN8770_BIT(6)
#define LAN8770_MDIO_CTRL1_WAKE_OUT_PIN_REQ             LAN8770_BIT(7)
#define LAN8770_MDIO_CTRL1_TX_SYM_DBG_GET(x)            LAN8770_EXTRACT_BITFIELD(x, 8, 2)
#define LAN8770_MDIO_CTRL1_TX_SYM_DBG_SET(x)            LAN8770_ENCODE_BITFIELD(x, 8, 2)
#define LAN8770_MDIO_CTRL1_CNTR_GET(x)                  LAN8770_EXTRACT_BITFIELD(x, 10, 2)
#define LAN8770_MDIO_CTRL1_CNTR_SET(x)                  LAN8770_ENCODE_BITFIELD(x, 10, 2)
#define LAN8770_MDIO_CTRL1_SLEEP_REQ                    LAN8770_BIT(12)
#define LAN8770_MDIO_CTRL1_WAKE_REQ                     LAN8770_BIT(13)
#define LAN8770_MDIO_CTRL1_PHYADBP                      LAN8770_BIT(14)
#define LAN8770_MDIO_CTRL1_MDPREBP                      LAN8770_BIT(15)

// Register - 16
#define LAN8770_MDIO_CTRL2_OFFSET                             (0x10) /*MDIO Control 2 Register*/
#define LAN8770_MDIO_CTRL2_TO_EN                        LAN8770_BIT(0)
#define LAN8770_MDIO_CTRL2_TO_CNT_GET(x)                LAN8770_EXTRACT_BITFIELD(x, 1, 4)
#define LAN8770_MDIO_CTRL2_TO_CNT_SET(x)                LAN8770_ENCODE_BITFIELD(x, 1, 4)
#define LAN8770_MDIO_CTRL2_IGN_IDLE_WUR_LPS             LAN8770_BIT(5)
#define LAN8770_MDIO_CTRL2_EN_DET_MST_MODE              LAN8770_BIT(6)
#define LAN8770_MDIO_CTRL2_WAKE_OUT_PIN_REQ             LAN8770_BIT(7)
#define LAN8770_MDIO_CTRL2_TX_SYM_DBG_GET(x)            LAN8770_EXTRACT_BITFIELD(x, 8, 2)
#define LAN8770_MDIO_CTRL2_TX_SYM_DBG_SET(x)            LAN8770_ENCODE_BITFIELD(x, 8, 2)
#define LAN8770_MDIO_CTRL2_CNTR_GET(x)                  LAN8770_EXTRACT_BITFIELD(x, 10, 2)
#define LAN8770_MDIO_CTRL2_CNTR_SET(x)                  LAN8770_ENCODE_BITFIELD(x, 10, 2)
#define LAN8770_MDIO_CTRL2_SLEEP_REQ                    LAN8770_BIT(12)
#define LAN8770_MDIO_CTRL2_WAKE_REQ                     LAN8770_BIT(13)
#define LAN8770_MDIO_CTRL2_PHYADBP                      LAN8770_BIT(14)
#define LAN8770_MDIO_CTRL2_MDPREBP                      LAN8770_BIT(15)

// Register - 17
#define LAN8770_MODE_STATUS_OFFSET                            (0x11) /*Mode Status Register*/

// Register - 18
#define LAN8770_LOOPBACK_CTRL_OFFSET                        (0x12) /*Loopback Control Register*/
#define LAN8770_LPBK_CTRL_PMA                           LAN8770_BIT(0)
#define LAN8770_LPBK_CTRL_FAR                           LAN8770_BIT(9)

// Register - 19
#define LAN8770_RESET_CTRL_OFFSET                         (0x13) /*Reset Control Register*/
#define LAN8770_CTRL_REG_RST                        LAN8770_BIT(0)
#define LAN8770_CTRL_MISC_REG_RST                   LAN8770_BIT(1)
#define LAN8770_CTRL_PWRDWN_MISC_REG_RST            LAN8770_BIT(2)
#define LAN8770_CTRL_PCS_RST                        LAN8770_BIT(3)
#define LAN8770_CTRL_PCS_Reg_RST                    LAN8770_BIT(4)
#define LAN8770_CTRL_PWRDWN_PCS_REG_RST             LAN8770_BIT(5)
#define LAN8770_CTRL_DSP_RST                        LAN8770_BIT(6)
#define LAN8770_CTRL_DSP_REG_RST                    LAN8770_BIT(7)
#define LAN8770_CTRL_PWRDN_DSP_REG_RST              LAN8770_BIT(8)
#define LAN8770_CTRL_AFE_REG_RST                    LAN8770_BIT(9)
#define LAN8770_CTRL_PWRDWN_AFE_REG_RST             LAN8770_BIT(10)
#define LAN8770_CTRL_PHY_ADDR_RST_GET(x)            LAN8770_EXTRACT_BITFIELD(x, 11, 5)
#define LAN8770_CTRL_PHY_ADDR_RST_SET(x)            LAN8770_ENCODE_BITFIELD(x, 11, 5)

// Register - 20
#define LAN8770_EXT_REG_CTRL_OFFSET                       (0x14) /*External Register Control Register*/
#define LAN8770_EXT_REG_CTRL_REG_ADDR(x)            LAN8770_EXTRACT_BITFIELD(x, 0, 8)
#define LAN8770_EXT_REG_CTRL_REG_BANK_GET(x)        LAN8770_EXTRACT_BITFIELD(x, 8, 3)
#define LAN8770_EXT_REG_CTRL_REG_BANK_SET(x)        LAN8770_ENCODE_BITFIELD(x, 8, 3)
#define LAN8770_EXT_REG_CTRL_WRT_CTRL               LAN8770_BIT(11)
#define LAN8770_EXT_REG_CTRL_READ_CTRL              LAN8770_BIT(12)
/* 0x0D - 0x0F  Reserved */

// Register - 21
#define LAN8770_EXT_REG_RD_DATA                         (0x15) /*External Register Read Data Register*/

// Register - 22
#define LAN8770_EXT_REG_WR_DATA                           (0x16) /*External Register Write Data Register*/

// Register - 23
#define LAN8770_PCS_CTRL_OFFSET                     (0x17) /*PCS Control Register*/

// Register - 24
#define LAN8770_INTR_SRC_OFFSET                           (0x18) /*Interrupt Source Register*/
#define LAN8770_INTR_SRC_ENERGY_ON                       LAN8770_BIT(0)
#define LAN8770_INTR_SRC_LINK_DOWN                       LAN8770_BIT(1)
#define LAN8770_INTR_SRC_LINK_UP                         LAN8770_BIT(2)
#define LAN8770_INTR_SRC_JAB_DET                         LAN8770_BIT(3)
#define LAN8770_INTR_SRC_LINK_NEW_UP                     LAN8770_BIT(4)
#define LAN8770_INTR_SRC_RCV_LPS                         LAN8770_BIT(5)
#define LAN8770_INTR_SRC_ENERGY_OFF                      LAN8770_BIT(6)
#define LAN8770_INTR_SRC_ZERO_TD                         LAN8770_BIT(7)
#define LAN8770_INTR_SRC_PHY_CTRL_MAXWAIT_TD             LAN8770_BIT(8)
#define LAN8770_INTR_SRC_LINK_UP_TO_EVT                  LAN8770_BIT(9)
#define LAN8770_INTR_SRC_RCV_WAKE                        LAN8770_BIT(10)
#define LAN8770_INTR_SRC_OVR_TMP_ERR                     LAN8770_BIT(11)
#define LAN8770_INTR_SRC_SQI_ERR                         LAN8770_BIT(12)
#define LAN8770_INTR_SRC_SQI_TOGGLE                      LAN8770_BIT(13)
#define LAN8770_INTR_SRC_WAKE_IN                         LAN8770_BIT(14)
#define LAN8770_INTR_SRC_SW                              LAN8770_BIT(15)

// Register - 25
#define LAN8770_INTR_MASK_OFFSET                                 (0x19) /*Interrupt Mask Register*/
#define LAN8770_INTR_MASK_ENERGY_ON                       LAN8770_BIT(0)
#define LAN8770_INTR_MASK_LINK_DOWN                       LAN8770_BIT(1)
#define LAN8770_INTR_MASK_LINK_UP                         LAN8770_BIT(2)
#define LAN8770_INTR_MASK_JAB_DET                         LAN8770_BIT(3)
#define LAN8770_INTR_MASK_LINK_NEW_UP                     LAN8770_BIT(4)
#define LAN8770_INTR_MASK_RCV_LPS                         LAN8770_BIT(5)
#define LAN8770_INTR_MASK_ENERGY_OFF                      LAN8770_BIT(6)
#define LAN8770_INTR_MASK_ZERO_TD                         LAN8770_BIT(7)
#define LAN8770_INTR_MASK_PHY_CTRL_MAXWAIT_TD             LAN8770_BIT(8)
#define LAN8770_INTR_MASK_LINK_UP_TO_EVT                  LAN8770_BIT(9)
#define LAN8770_INTR_MASK_RCV_WAKE                        LAN8770_BIT(10)
#define LAN8770_INTR_MASK_OVR_TMP_ERR                     LAN8770_BIT(11)
#define LAN8770_INTR_MASK_SQI_ERR                         LAN8770_BIT(12)
#define LAN8770_INTR_MASK_SQI_TOGGLE                      LAN8770_BIT(13)
#define LAN8770_INTR_MASK_WAKE_IN                         LAN8770_BIT(14)
#define LAN8770_INTR_MASK_SW                              LAN8770_BIT(15)

/**
TABLE 3-5: MODE1 CONFIGURATION STRAP
----------------------------------------------------------------------------------------------------------------
| MODE1  |    Definition                                                    |   Default Register Bit Values    |
|        |                                                                  |   Register 26 [Bit 8]            |
|--------|------------------------------------------------------------------|-----------------------------------
| 0b     |    PHY is placed in managed mode                                 |   0b                             |
| 1b     |    PHY is placed in autonomous mode                              |   1b                             |
|        |    (basic dataflow enabled, no software configuration required)  |                                  |
----------------------------------------------------------------------------------------------------------------
 */
// Register - 26
#define LAN8770_POWER_DOWN_CTRL_OFFSET                     (0x1A) /*Power Down Control Register*/
/* 0x09 - 0x0F  Reserved */
#define LAN8770_POWER_DOWN_CTRL_HW_INIT_EN               LAN8770_BIT(8)
#define LAN8770_POWER_DOWN_CTRL_FORCE_TX_EN              LAN8770_BIT(9)
/* 0x00 - 0x07  Reserved */

/**
 *  BANK-1 : Miscellaneous Registers
 **/
/* 0x00h - 0x07h  Reserved */

#define LAN8770_MISC_INT2_SRC_OFFSET                    (0x8)  /* Interrupt Status Register */
#define LAN8770_MISC_INT2_MASK_OFFSET                   (0x9)  /* Interrupt Mask Register */

/* 0x09h  Reserved */

#define LAN8770_MISC_CTRL_0_OFFSET                      (0x10) /* Control 0 Register */
#define LAN8770_MISC_CTRL_0_LED_MODE(x)                 LAN8770_EXTRACT_BITFIELD(x, 0, 3)
#define LAN8770_MISC_CTRL_0_LED_EN                      LAN8770_BIT(3)
#define LAN8770_MISC_CTRL_0_MODE0_CFG_STRAP             LAN8770_BIT(4)
#define LAN8770_MISC_CTRL_0_MODE1_CFG_STRAP             LAN8770_BIT(5)
#define LAN8770_MISC_CTRL_0_MODE2_CFG_STRAP             LAN8770_BIT(6)
#define LAN8770_MISC_CTRL_0_MODE3_CFG_STRAP             LAN8770_BIT(7)
#define LAN8770_MISC_CTRL_0_PHYAD0_CFG_STRAP            LAN8770_BIT(8)
#define LAN8770_MISC_CTRL_0_PHYAD1_CFG_STRAP            LAN8770_BIT(9)
#define LAN8770_MISC_CTRL_0_REG_OFF_CFG_STRAP           LAN8770_BIT(10)
/* 0x0B - 0x0E  Reserved */
#define LAN8770_MISC_CTRL_0_TXER_EN                     LAN8770_BIT(15)
//Supporting macros
#define LAN8770_MISC_CTRL_0_LED_DIS                     LAN8770_MISC_CTRL_0_LED_EN
#define LAN8770_MISC_CTRL_0_LED_MODE_LINK_UP            (0x0)
#define LAN8770_MISC_CTRL_0_LED_MODE_LINK_UP_RMT_RCV    (0x1)
#define LAN8770_MISC_CTRL_0_LED_MODE_LINK_UP_LCL_RCV    (0x2)
#define LAN8770_MISC_CTRL_0_LED_MODE_ACTIVITY           (0x3)
#define LAN8770_MISC_CTRL_0_LED_MODE_RX_ACTIVITY        (0x4)
#define LAN8770_MISC_CTRL_0_LED_MODE_TX_ACTIVITY        (0x5)
#define LAN8770_MISC_CTRL_0_LED_MODE_SLAVE                    (0x6)
#define LAN8770_MISC_CTRL_0_LED_MODE_MASTER                   (0x7)

#define LAN8770_MISC_CTRL_1_OFFSET                      (0x11) /* Control 1 Register */
/* 0x00 - 0x0B  Reserved */
#define LAN8770_MISC_CTRL_1_BCST_ADDR_EN                LAN8770_BIT(12)
#define LAN8770_MISC_CTRL_1_RGMII_RXC_INT_DELAY_EN      LAN8770_BIT(13)
#define LAN8770_MISC_CTRL_1_RGMII_TXC_INT_DELAY_EN      LAN8770_BIT(14)
/* 0x0F Reserved */

/* 0x12h - 0x14h  Reserved */

#define LAN8770_MISC_CTRL_2_OFFSET                      (0x15) /* Control 2 Register */
#define LAN8770_MISC_CTRL_2_CLK_125_EN                  LAN8770_BIT(15)
/* 0xA - 0xE  Reserved */
#define LAN8770_MISC_CTRL_2_XMII_MODE_SET(x)            LAN8770_ENCODE_BITFIELD(x, 7, 3)
#define LAN8770_MISC_CTRL_2_XMII_MODE_GET(x)            LAN8770_EXTRACT_BITFIELD(x, 7, 3)
/* 0x3 - 0x6  Reserved */
#define LAN8770_MISC_CTRL_2_DCQ_INT_SEL_SET(x)          LAN8770_ENCODE_BITFIELD(x, 0, 3)
#define LAN8770_MISC_CTRL_2_DCQ_INT_SEL_GET(x)          LAN8770_EXTRACT_BITFIELD(x, 0, 3)

/* 0x16h Reserved */

#define LAN8770_MISC_CTRL_3_OFFSET                      (0x17) /* Control 3 Register */
#define LAN8770_MISC_CTRL_3_OVER_TMP_DET_EN             LAN8770_BIT(0)
/* 0x01 - 0x08  Reserved */
#define LAN8770_MISC_CTRL_3_OVER_TMP_DET_STATUS         LAN8770_BIT(9)
/* 0x0A - 0x0F  Reserved */

/* 0x18h - 0x19h  Reserved */

#define LAN8770_DCQ_ERR_MAX_OFFSET                  (0x1A) /* DCQ Error Max Register */

/* 0x1Bh - 0x1Fh  Reserved */

#define LAN8770_MISC_WKP_COM_CTL0_OFFSET            (0x20) /* Wakeup Common Control 0 Register */
#define LAN8770_MISC_WKP_COM_CTL0_WK_IN_EN          LAN8770_BIT(0)
#define LAN8770_MISC_WKP_COM_CTL0_INH_EN_TC10       LAN8770_BIT(1)
#define LAN8770_MISC_WKP_COM_CTL0_SLEEP_EN          LAN8770_BIT(2)
#define LAN8770_MISC_WKP_COM_CTL0_WK_DEB_UNITS      LAN8770_BIT(3)
#define LAN8770_MISC_WKP_COM_CTL0_WK_OUT_UNITS      LAN8770_BIT(4)
#define LAN8770_MISC_WKP_COM_CTL0_ROSC_EN           LAN8770_BIT(5) /* Ring Oscillator Enable */
#define LAN8770_MISC_WKP_COM_CTL0_ROSC_STS          LAN8770_BIT(6) /* Ring Oscillator Status */
#define LAN8770_MISC_WKP_COM_CTL0_INH_DIS           LAN8770_BIT(7) /* Wake Out Auto-Forwarding Enable */
/* 0x08 - 0x0E  Reserved */
#define LAN8770_MISC_WKP_COM_CTL0_VBAT_COMM_WR      LAN8770_BIT(15)

#define LAN8770_MISC_WKP_COM_CTL1_OFFSET            (0x21) /* Wakeup Common Control 1 Register */
#define LAN8770_MISC_WKP_DBG_STS_OFFSET             (0x22) /* Wakeup Debug Status Register */
#define LAN8770_MISC_WKP_DBG_STS_TC10_STATE_GET(x)      LAN8770_EXTRACT_BITFIELD(x,0,3)

/* 0x23h  Reserved */

#define LAN8770_MISC_WKP_PRT_CTL1_OFFSET             (0x24) /* Wakeup Port Control1 Register */
#define LAN8770_MISC_WKP_PRT_CTL1_WUP_DEB_VAL(x)     LAN8770_EXTRACT_BITFIELD(x, 0, 8)
#define LAN8770_MISC_WKP_PRT_CTL1_WK_MDI_EN          LAN8770_BIT(8)
#define LAN8770_MISC_WKP_PRT_CTL1_SD_TUNE(x)         LAN8770_EXTRACT_BITFIELD(x, 9, 2)
/* 0x0B - 0x0E  Reserved */
#define LAN8770_MISC_WKP_PRT_CTL1_VBAT_PORT_WR       LAN8770_BIT(15)

#define LAN8770_MISC_WKP_PRT_CTL2_OFFSET             (0x25) /* Wakeup Port Control2 Register */

/* 0x1Bh - 0xFFh  Reserved */

/**
 *  BANK-2 : PCS and Energy Registers
 **/
/* 0x00h - 0x15h  Reserved */
#define LAN8770_PCS_DESCM_CONTROL0          (0x00)
#define LAN8770_PCS_DEBUG_BUS_STS_OFFSET    (0x16)

/* 0x17h - 0x1Fh  Reserved */

#define LAN8770_PCS_SLEEP_WAKE_DET_OFFSET               (0x20) /* Sleep Wake Detect Register */
#define LAN8770_PCS_SLEEP_WAKE_DET_WUR_LEN_SET(x)       LAN8770_ENCODE_BITFIELD(x, 8, 8)
#define LAN8770_PCS_SLEEP_WAKE_DET_WUR_LEN_GET(x)       LAN8770_EXTRACT_BITFIELD(x, 8, 8)
#define LAN8770_PCS_SLEEP_WAKE_DET_LPS_LEN_SET(x)       LAN8770_ENCODE_BITFIELD(x, 0, 8)
#define LAN8770_PCS_SLEEP_WAKE_DET_LPS_LEN_GET(x)       LAN8770_EXTRACT_BITFIELD(x, 0, 8)

/* 0x21h - 0xFFh  Reserved */

/**
 *  BANK-3 : AFE Registers
 **/
/* 0x00h - 0x0Ah  Reserved */

#define LAN8770_AFE_PORT_CFG1_OFFSET   (0x0B) /* AFE Port Configuration 1 Register */
/* 0x06 - 0x0F  Reserved */
#define LAN8770_AFE_PORT_CFG1_TX_PD     LAN8770_BIT(5)
/* 0x01 - 0x04  Reserved */
#define LAN8770_AFE_PORT_CFG1_TX_SRC    LAN8770_BIT(0)
//Supporting macros
#define LAN8770_AFE_PORT_CFG1_MASK      (0x001E)

/* 0x0Ch - 0x0Dh  Reserved */

#define LAN8770_AFE_AFE_PORT_CFG4_OFFSET   (0x0E) /* AFE Port Configuration 4 Register */

/* 0x0Fh - 0xFFh  Reserved */


/**
 *  BANK-4 : DSP Registers
 **/

/* 0x00h - 0x0Ch  Reserved */
#define LAN8770_TX_RX_FIFO_CFG                  (0x02)
#define LAN8770_DSP_CDR_CFG_PRE_LOCK            (0x05)
#define LAN8770_DSP_CDR_CFG_POST_LOCK           (0x06)
#define LAN8770_DSP_COEF_RW_CTL_CFG_OFFSET      (0x0D) /* Coefficient Control Configuration Register */
/* 0x06 - 0x0F  Reserved */
#define LAN8770_DSP_COEF_RW_CTL_CFG_TAP_EN      LAN8770_BIT(5)
#define LAN8770_DSP_COEF_RW_CTL_CFG_TAP_DIS     LAN8770_BIT(4)
#define LAN8770_DSP_COEF_RW_CTL_CFG_OVR_DIS     LAN8770_BIT(3)
#define LAN8770_DSP_COEF_RW_CTL_CFG_OVR_EN      LAN8770_BIT(2)
#define LAN8770_DSP_COEF_RW_CTL_CFG_POKE_EN     LAN8770_BIT(1)
#define LAN8770_DSP_COEF_RW_CTL_CFG_POKE_DIS    LAN8770_BIT(0)

/* 0x0Eh - 0x2Dh  Reserved */

#define LAN8770_DSP_EQU_LOCK_STG1_THR                   (0x11)
#define LAN8770_DSP_SLV_HD_MULT_CFG                     (0x17)
#define LAN8770_DSP_SLV_FD_MULT_CFG                     (0x18)
#define LAN8770_DSP_LCK_STG2_MUFACT_CFG                 (0x1A)
#define LAN8770_DSP_LCK_STG3_MUFACT_CFG                 (0x1B)
#define LAN8770_DSP_POST_LCK_MUFACT_CFG                 (0x1C)
#define LAN8770_DSP_COEF_PROT_DIS                       (0x25)
#define LAN8770_DSP_DCQ_CFG1_OFFSET                     (0x2E) /* DCQ Configuration 1 Register */
#define LAN8770_DSP_DCQ_CFG1_PMSE_SCA_FACT_SET(x)       LAN8770_ENCODE_BITFIELD(x, 14, 2)
#define LAN8770_DSP_DCQ_CFG1_PMSE_SCA_FACT_GET(x)       LAN8770_EXTRACT_BITFIELD(x, 14, 2)
#define LAN8770_DSP_DCQ_CFG1_PMSE_KP_FACT_SET(x)        LAN8770_ENCODE_BITFIELD(x, 10, 4)
#define LAN8770_DSP_DCQ_CFG1_PMSE_KP_FACT_GET(x)        LAN8770_EXTRACT_BITFIELD(x, 10, 4)
#define LAN8770_DSP_DCQ_CFG1_MSE_SCA_FACT_SET(x)        LAN8770_ENCODE_BITFIELD(x, 8, 2)
#define LAN8770_DSP_DCQ_CFG1_MSE_SCA_FACT_GET(x)        LAN8770_EXTRACT_BITFIELD(x, 8, 2)
#define LAN8770_DSP_DCQ_CFG1_RESET                      LAN8770_BIT(7)
#define LAN8770_DSP_DCQ_CFG1_SQI_METH_B_MODE_SEL        LAN8770_BIT(6)
#define LAN8770_DSP_DCQ_CFG1_SQI_METH_B_EN              LAN8770_BIT(5)
#define LAN8770_DSP_DCQ_CFG1_SQI_KP_SET(x)              LAN8770_ENCODE_BITFIELD(x, 0, 5)
#define LAN8770_DSP_DCQ_CFG1_SQI_KP_GET(x)              LAN8770_EXTRACT_BITFIELD(x, 0, 5)
// Supporting macros
#define LAN8770_DSP_DCQ_CFG1_SQI_MASK                   (0x7F)

/* 0x2Fh - 0x3Bh  Reserved */

#define LAN8770_DSP_DCQ_CF2_OFFSET                      (0x3C) /* DCQ Configuration 2 Register */
/* 0x02 - 0x0F  Reserved */
#define LAN8770_DSP_DCQ_CFG2_PMSE_EN                    LAN8770_BIT(1)
#define LAN8770_DSP_DCQ_CFG2_MSE_SQI_METH_A_EN          LAN8770_BIT(0)

/* 0x3Dh - 0x81h  Reserved */

#define LAN8770_DSP_SQI_SQU_MEAN_LSB_OFFSET     (0x82) /* SQI Method B Square Mean LSB Register */

#define LAN8770_DSP_SQI_SQU_MEAN_MSB_OFFSET     (0x83) /* SQI Method B Square Mean MSB Register */

/* 0x84h - 0x86h  Reserved */

#define LAN8770_DSP_SQI_TBLx_OFFSET             (0x87) /* SQI Method A Tablex Registers */
/* 0x09 - 0x0F  Reserved */
#define LAN8770_DSP_SQI_METH_A_SQI_VAL(x)       LAN8770_EXTRACT_BITFIELD(x, 0, 9)

/* 0x8Eh - 0xAFh  Reserved */

#define LAN8770_DSP_DCQ_MSE_OFFSET              (0xB0) /* DCQ Mean Square Error Register */
#define LAN8770_DSP_DCQ_MSE_VALID               LAN8770_BIT(9)
#define LAN8770_DSP_DCQ_MSE_VAL_SET(x)          LAN8770_ENCODE_BITFIELD(x, 0, 9)
#define LAN8770_DSP_DCQ_MSE_VAL_GET(x)          LAN8770_EXTRACT_BITFIELD(x, 0, 9)

#define LAN8770_DSP_DCQ_MSE_WC_OFFSET           (0xB1) /* DCQ Mean Square Error Worst Case Register */
#define LAN8770_DSP_DCQ_MSE_WC_VALID            LAN8770_BIT(9)
#define LAN8770_DSP_DCQ_MSE_WC_VAL_SET(x)       LAN8770_ENCODE_BITFIELD(x, 0, 9)
#define LAN8770_DSP_DCQ_MSE_WC_VAL_GET(x)       LAN8770_EXTRACT_BITFIELD(x, 0, 9)

#define LAN8770_DSP_DCQ_SQI_OFFSET              (0xB2) /* DCQ SQI Method A Register */
/* 0x08 - 0x0F  Reserved */
#define LAN8770_DSP_DCQ_SQI_METH_A_WC_SET(x)    LAN8770_ENCODE_BITFIELD(x, 5, 3)
#define LAN8770_DSP_DCQ_SQI_METH_A_WC_GET(x)    LAN8770_EXTRACT_BITFIELD(x, 5, 3)
/* 0x04  Reserved */
#define LAN8770_DSP_DCQ_SQI_METH_A_VAL_SET(x)   LAN8770_ENCODE_BITFIELD(x, 1, 3)
#define LAN8770_DSP_DCQ_SQI_METH_A_VAL_GET(x)   LAN8770_EXTRACT_BITFIELD(x, 1, 3)
/* 0x00  Reserved */

#define LAN8770_DSP_DCQ_PMSE_OFFSET             (0xB3) /* DCQ Peak MSE Register */
#define LAN8770_DSP_DCQ_PMSE_WC_SET(x)          LAN8770_ENCODE_BITFIELD(x, 8, 8)
#define LAN8770_DSP_DCQ_PMSE_WC_GET(x)          LAN8770_EXTRACT_BITFIELD(x, 8, 8)
#define LAN8770_DSP_DCQ_PMSE_VAL_SET(x)         LAN8770_ENCODE_BITFIELD(x, 0, 8)
#define LAN8770_DSP_DCQ_PMSE_VAL_GET(x)         LAN8770_EXTRACT_BITFIELD(x, 0, 8)

/* 0xB4h - 0xF2h  Reserved */

#define LAN8770_DSP_BER_RATE_CNT_OFFSET         (0xF3) /* BER Rate Counter Register */

#define LAN8770_DSP_BER_RATE_WIN_TOG_OFFSET     (0xF4) /* BER Window Toggle Register */
/* 0x01 - 0x0F  Reserved */
#define LAN8770_DSP_BER_RATE_WIN_TOG            LAN8770_BIT(0)

/* 0xF5h - 0xFFh  Reserved */
#define LAN8770_DSP_DFE_TAP1_INIT_COEF          (0x22)
#define LAN8770_DSP_SQI_CONFIG                  (0x2E)
#define LAN8770_DSP_CALIB_CFG                   (0x37)
#define LAN8770_DSP_MAX_PGA_GAIN                (0x4F)
#define LAN8770_DSP_KP_LOOP_SAT_CFG             (0x54)
#define LAN8770_DSP_TX_LPF_FIR_CFG              (0x55)
#define LAN8770_DSP_CABLE_DIAG_STS_CTL          (0x5A)
#define LAN8770_DSP_CABLE_DIAG_ADC_OUT_THR      (0x5B)
#define LAN8770_DSP_CABLE_DIAG_PGA_THR          (0x5C)
#define LAN8770_DSP_CABLE_DIAG_MIN_WAIT_CFG     (0x5D)
#define LAN8770_DSP_CABLE_DIAG_MAX_WAIT_CFG     (0x5E)
#define LAN8770_DSP_CABLE_DIAG_CYC_WAIT_CFG     (0x5F)
#define LAN8770_DSP_CABLE_DIAG_TX_PUL_CFG       (0x60)
#define LAN8770_DSP_CABLE_DIAG_CAP_TDR_THR      (0x61)
#define LAN8770_DSP_CABLE_DIAG_MIN_PGA_GAIN     (0x62)
#define LAN8770_DSP_CABLE_DIAG_CAP_CYC_PHS      (0x63)
#define LAN8770_DSP_EQ_FD_STG1_FRZ_CFG          (0x69)
#define LAN8770_DSP_EQ_FD_STG2_FRZ_CFG          (0x6A)
#define LAN8770_DSP_EQ_FD_STG3_FRZ_CFG          (0x6B)
#define LAN8770_DSP_EQ_FD_STG4_FRZ_CFG          (0x6C)
#define LAN8770_EQ_WT_FD_LCK_FRZ_CFG            (0x6D)
#define LAN8770_PST_EQ_LCK_STG1_FRZ_CFG         (0x6E)

/* cable diag read non-hybrid results */
#define LAN8770_DSP_CABLE_DIAG_GAIN_IDX         (0x97)
#define LAN8770_DSP_CABLE_DIAG_PEAK             (0x99)
#define LAN8770_DSP_CABLE_DIAG_NEG_PEAK         (0x9A)
#define LAN8770_DSP_CABLE_DIAG_PEAK_TIME        (0x9C)
#define LAN8770_DSP_CABLE_DIAG_NEG_PEAK_TIME    (0x9D)

/**
 *  BANK-5 : Instrumentation Registers
 **/

#endif //LAN8770_REGISTERS_H
