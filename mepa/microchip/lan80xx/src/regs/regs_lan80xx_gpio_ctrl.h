// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_GPIO_CTRL_H_
#define _LAN80XX_MALIBU25G_REGS_GPIO_CTRL_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a GPIO_CTRL
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a GPIO_CTRL:GPIO_CFG_STAT
 *
 * Configuration and status of chip level GPIO
 */



/**
 * \brief Output enable of GPIOs SLOT Select
 * x = 0 then GPIO_CFG1
 * x = 1 then GPIO_CFG0
 */
#define LAN80XX_GPIO_CTRL_GPIO_CFGX_SLOT(x)     LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf200 + x))

/**
 * \brief Output Inverse of GPIOs with SLOT Select
 * x = 0 then GPIO_INV1
 * x = 1 then GPIO_INV0
 */
#define LAN80XX_GPIO_CTRL_GPIO_OUT_INV_CFGX_SLOT(x)     LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf202 + x))

/**
 * \brief Current status of GPIO with Slot Select
 *  x = 0 then GPIO_STAT1
 *  x = 1 then GPIO_STAT0
 */
#define LAN80XX_GPIO_CTRL_GPIO_STATX_SLOT(x)       LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf204 + x))



/**
 * \brief Current status of GPIO outputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_STAT1
 */
#define LAN80XX_GPIO_CTRL_GPIO_OUT_STAT1        LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf206)

/**
 * \brief
 * State of each GPIO output [39:32]
 *
 * \details
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_OUT_STAT1 . GPIO_OUT1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_OUT_STAT1_GPIO_OUT1_STAT(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_GPIO_CTRL_GPIO_OUT_STAT1_GPIO_OUT1_STAT     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_GPIO_CTRL_GPIO_OUT_STAT1_GPIO_OUT1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current status of GPIO outputs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_OUT_STAT0
 */
#define LAN80XX_GPIO_CTRL_GPIO_OUT_STAT0        LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf207)

/**
 * \brief
 * State of each GPIO output [31:0]
 *
 * \details
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_OUT_STAT0 . GPIO_OUT_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_OUT_STAT0_GPIO_OUT_STAT(x)  (x)
#define  LAN80XX_M_GPIO_CTRL_GPIO_OUT_STAT0_GPIO_OUT_STAT     0xffffffff
#define  LAN80XX_X_GPIO_CTRL_GPIO_OUT_STAT0_GPIO_OUT_STAT(x)  (x)


/**
 * \brief Input State Change Detection of GPIO with Slot Select
 * x = 0 then GPIO_CHANGE1
 * x = 1 then GPIO_CHANGE0
 */
#define LAN80XX_GPIO_CTRL_GPIO_CHANGEX_SLOT(x)     LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf208 + x))


/**
 * \brief
 * function selection for GPIO[39:32].  Each bit corresponds to the
 * function selection of that GPIO.  e.g. bit 1 -> GPIO[33]
 *
 * \details
 * 1 = GPIO
 * 0 = Alternate function
 *
 * The alternate function of GPIO pins are:
 * GPIO_0:    N/A (GPIO is LP0 RATESEL0)
 * GPIO_1:    N/A (GPIO is LP0 MOD_ABS)
 * GPIO_2:    LP0 TWI_MST_SCL
 * GPIO_3:    LP0 TWI_MST_SDA
 * GPIO_4:    N/A (GPIO is LP0 TX_DIS)
 * GPIO_5:    N/A (GPIO is LP0 TX_FAULT)
 * GPIO_6:    LP0 RXLOS
 * GPIO_7:    LP0 LINK_LED
 * GPIO_8:    N/A (GPIO is LP1 RATESEL0)
 * GPIO_9:    N/A (GPIO is LP1 MOD_ABS)
 * GPIO_10:  LP1 TWI_MST_SCL
 * GPIO_11:  LP1 TWI_MST_SDA
 * GPIO_12:  N/A (GPIO is LP1 TX_DIS)
 * GPIO_13:  N/A (GPIO is LP1 TX_FAULT)
 * GPIO_14:  LP1 RXLOS
 * GPIO_15:  LP1 LINK_LED
 * GPIO_16:  N/A (GPIO is LP2 RATESEL0)
 * GPIO_17:  N/A (GPIO is LP2 MOD_ABS)
 * GPIO_18:  LP2 TWI_MST_SCL
 * GPIO_19:  LP2 TWI_MST_SDA
 * GPIO_20:  N/A (GPIO is LP2 TX_DIS)
 * GPIO_21:  N/A (GPIO is LP2 TX_FAULT)
 * GPIO_22:  LP2 RXLOS
 * GPIO_23:  LP2 LINK_LED
 * GPIO_24:  N/A (GPIO is LP3 RATESEL0)
 * GPIO_25:  N/A (GPIO is LP3 MOD_ABS)
 * GPIO_26:  LP3 TWI_MST_SCL
 * GPIO_27:  LP3 TWI_MST_SDA
 * GPIO_28:  N/A (GPIO is LP3 TX_DIS)
 * GPIO_29:  N/A (GPIO is LP3 TX_FAULT)
 * GPIO_30:  LP3 RXLOS
 * GPIO_31:  LP3 LINK_LED
 * GPIO_32:  UART TX
 * GPIO_33:  UART RX
 * GPIO_34:  INTR_A
 * GPIO_35:  INTR_B
 * GPIO_36:  LP0 ACTIVITY LED
 * GPIO_37:  LP1 ACTIVITY LED
 * GPIO_38:  LP2 ACTIVITY LED
 * GPIO_39:  LP3 ACTIVITY LED
 *
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_FUN_SEL1 . GPIO_FUN1_SEL
 */
/**
 * \brief Function Select of GPIOs with SLOT Select
 * x = 0 then GPIO_SEL1
 * x = 1 then GPIO_SEL0
 */
#define LAN80XX_GPIO_CTRL_GPIO_FUN_SELX_SLOT(x)     LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf20a + x))

/**
 * \brief Function selection of GPIOs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_FUN_SEL1
 */
#define LAN80XX_GPIO_CTRL_GPIO_FUN_SEL1         LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf20a)

/**
 * \brief Function selection of GPIOs
 *
 * \details
 * Register: \a GPIO_CTRL:GPIO_CFG_STAT:GPIO_FUN_SEL0
 */
#define LAN80XX_GPIO_CTRL_GPIO_FUN_SEL0         LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf20b)

/**
 * \brief Output control type GPIOs with SLOT Select
 * x = 0 then GPIO_PP!
 * x = 1 then GPIO_PP0
 */
#define LAN80XX_GPIO_CTRL_GPIO_OUT_PPX_SLOT(x)     LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf20c + x))

/**
 * Register Group: \a GPIO_CTRL:INTR_CFG_STAT
 *
 * Configuration and status of chip level Interrupts
 */


/**
 * \brief Aggregate Interrupt Source Enable bits
 *
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:INTR_SRC_EN
 *
 * @param ri Register: INTR_SRC_EN (??), 0-1
 */
#define LAN80XX_GPIO_CTRL_INTR_SRC_EN(ri)       LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf20e + (ri))

/**
 * \brief
 * MCU SRAMs ECC interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . MCU_ECC_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_MCU_ECC_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),23,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_ECC_INTR_EN  LAN80XX_BIT(23)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_MCU_ECC_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * MCU WDT interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . MCU_WDT_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_MCU_WDT_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),22,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_WDT_INTR_EN  LAN80XX_BIT(22)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_MCU_WDT_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MCU mailbox interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . MCU_MBOX_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),21,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN  LAN80XX_BIT(21)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_MCU_MBOX_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Aggregate GPIO interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . GPIO_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR1_EN  LAN80XX_BIT(20)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Aggregate GPIO interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . GPIO_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),19,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR0_EN  LAN80XX_BIT(19)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_GPIO_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Cross-connect interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CROSS_CONNECT_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),18,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN  LAN80XX_BIT(18)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CROSS_CONNECT_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * PTP LTC interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . PTP_LTC_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_PTP_LTC_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),17,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_PTP_LTC_INTR_EN  LAN80XX_BIT(17)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_PTP_LTC_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * PTP STI interrupt enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . PTP_STI_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_PTP_STI_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_PTP_STI_INTR_EN  LAN80XX_BIT(16)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_PTP_STI_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * slice 0 line interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH3_L_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),15,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR1_EN  LAN80XX_BIT(15)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * slice 3 line interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH3_L_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),14,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR0_EN  LAN80XX_BIT(14)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH3_L_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * slice 0 line interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH2_L_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR1_EN  LAN80XX_BIT(13)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * slice 2 line interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH2_L_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR0_EN  LAN80XX_BIT(12)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH2_L_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * slice 1 line interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH1_L_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR1_EN  LAN80XX_BIT(11)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * slice 1 line interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH1_L_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR0_EN  LAN80XX_BIT(10)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH1_L_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * slice 0 line interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH0_L_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR1_EN  LAN80XX_BIT(9)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * slice 0 line interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH0_L_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR0_EN  LAN80XX_BIT(8)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH0_L_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * slice 3 host interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH3_H_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR1_EN  LAN80XX_BIT(7)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * slice 3 host interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH3_H_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR0_EN  LAN80XX_BIT(6)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH3_H_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * slice 2 host interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH2_H_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR1_EN  LAN80XX_BIT(5)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * slice 2 host interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH2_H_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR0_EN  LAN80XX_BIT(4)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH2_H_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * slice 1 host interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH1_H_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR1_EN  LAN80XX_BIT(3)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * slice 1 host interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH1_H_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR0_EN  LAN80XX_BIT(2)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH1_H_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * slice 0 host interrupt 1 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH0_H_INTR1_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR1_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR1_EN  LAN80XX_BIT(1)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR1_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * slice 0 host interrupt 0 enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_SRC_EN . CH0_H_INTR0_EN
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR0_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR0_EN  LAN80XX_BIT(0)
#define  LAN80XX_X_GPIO_CTRL_INTR_SRC_EN_CH0_H_INTR0_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Aggregate Interrupt Status bits
 *
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:INTR_STAT
 *
 * @param ri Register: INTR_STAT (??), 0-1
 */
#define LAN80XX_GPIO_CTRL_INTR_STAT(ri)         LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf210 + (ri))

/**
 * \brief
 * MCU SRAMs ECC interrupt status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . MCU_ECC_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_MCU_ECC_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),23,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_MCU_ECC_INTR_STAT  LAN80XX_BIT(23)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_MCU_ECC_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * MCU WDT interrupt status. Indicates interrupt is pending or is masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . MCU_WDT_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_MCU_WDT_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),22,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_MCU_WDT_INTR_STAT  LAN80XX_BIT(22)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_MCU_WDT_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * MCU mailbox interrupt status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . MCU_MBOX_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_MCU_MBOX_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),21,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_MCU_MBOX_INTR_STAT  LAN80XX_BIT(21)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_MCU_MBOX_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Aggregate GPIO interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . GPIO_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_GPIO_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_GPIO_INTR1_STAT  LAN80XX_BIT(20)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_GPIO_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Aggregate GPIO interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . GPIO_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_GPIO_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),19,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_GPIO_INTR0_STAT  LAN80XX_BIT(19)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_GPIO_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * cross-connect interrupt status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CROSS_CONNECT_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CROSS_CONNECT_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),18,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CROSS_CONNECT_INTR_STAT  LAN80XX_BIT(18)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CROSS_CONNECT_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * PTP LTC interrupt status. Indicates interrupt is pending or is masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . PTP_LTC_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_PTP_LTC_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),17,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_PTP_LTC_INTR_STAT  LAN80XX_BIT(17)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_PTP_LTC_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * PTP STI interrupt status. Indicates interrupt is pending or is masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . PTP_STI_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_PTP_STI_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_PTP_STI_INTR_STAT  LAN80XX_BIT(16)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_PTP_STI_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * slice 3 line interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH3_L_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH3_L_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),15,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH3_L_INTR1_STAT  LAN80XX_BIT(15)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH3_L_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * slice 3 line interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH3_L_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH3_L_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),14,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH3_L_INTR0_STAT  LAN80XX_BIT(14)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH3_L_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * slice 2 line interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH2_L_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH2_L_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH2_L_INTR1_STAT  LAN80XX_BIT(13)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH2_L_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * slice 2 line interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH2_L_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH2_L_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH2_L_INTR0_STAT  LAN80XX_BIT(12)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH2_L_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * slice 1 line interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH1_L_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH1_L_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH1_L_INTR1_STAT  LAN80XX_BIT(11)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH1_L_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * slice 1 line interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH1_L_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH1_L_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH1_L_INTR0_STAT  LAN80XX_BIT(10)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH1_L_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * slice 0 line interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH0_L_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH0_L_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH0_L_INTR1_STAT  LAN80XX_BIT(9)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH0_L_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * slice 0 line interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH0_L_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH0_L_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH0_L_INTR0_STAT  LAN80XX_BIT(8)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH0_L_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * slice 3 host interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH3_H_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH3_H_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH3_H_INTR1_STAT  LAN80XX_BIT(7)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH3_H_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * slice 3 host interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH3_H_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH3_H_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH3_H_INTR0_STAT  LAN80XX_BIT(6)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH3_H_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * slice 2 host interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH2_H_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH2_H_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH2_H_INTR1_STAT  LAN80XX_BIT(5)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH2_H_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * slice 2 host interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH2_H_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH2_H_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH2_H_INTR0_STAT  LAN80XX_BIT(4)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH2_H_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * slice 1 host interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH1_H_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH1_H_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH1_H_INTR1_STAT  LAN80XX_BIT(3)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH1_H_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * slice 1 host interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH1_H_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH1_H_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH1_H_INTR0_STAT  LAN80XX_BIT(2)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH1_H_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * slice 0 host interrupt 1 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH0_H_INTR1_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH0_H_INTR1_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH0_H_INTR1_STAT  LAN80XX_BIT(1)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH0_H_INTR1_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * slice 0 host interrupt 0 status. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_INTR_STAT . CH0_H_INTR0_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_INTR_STAT_CH0_H_INTR0_STAT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_GPIO_CTRL_INTR_STAT_CH0_H_INTR0_STAT  LAN80XX_BIT(0)
#define  LAN80XX_X_GPIO_CTRL_INTR_STAT_CH0_H_INTR0_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


#define LAN80XX_GPIO_CTRL_GPIO_INTR_SRC_ENX_SLOT(ri,s)  LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1, (0xf212 + (ri) + (s * 2)))
/**
 * \brief
 * Interrupt enable mask for each GPIO[39:32]
 *
 * \details
 * 0 = GPIO_IN_CHG_STICKY will not propagate to INTR
 * 1 = GPIO_IN_CHG_STICKY will propagate to INTR
 *
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_INTR_SRC_EN1 . GPIO_IN1_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_INTR_SRC_EN1_GPIO_IN1_INTR_EN(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_GPIO_CTRL_GPIO_INTR_SRC_EN1_GPIO_IN1_INTR_EN     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_GPIO_CTRL_GPIO_INTR_SRC_EN1_GPIO_IN1_INTR_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief
 * Interrupt enable mask for each GPIO[31:0]
 *
 * \details
 * 0 = GPIO_IN_CHG_STICKY will not propagate to INTR
 * 1 = GPIO_IN_CHG_STICKY will propagate to INTR
 *
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_INTR_SRC_EN . GPIO_IN_INTR_EN
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_INTR_SRC_EN_GPIO_IN_INTR_EN(x)  (x)
#define  LAN80XX_M_GPIO_CTRL_GPIO_INTR_SRC_EN_GPIO_IN_INTR_EN     0xffffffff
#define  LAN80XX_X_GPIO_CTRL_GPIO_INTR_SRC_EN_GPIO_IN_INTR_EN(x)  (x)


/**
 * \brief Interrupt status of GPIOs
 *
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:GPIO_INTR_STAT1
 *
 * @param ri Register: GPIO_INTR_STAT1 (??), 0-1
 */
#define LAN80XX_GPIO_CTRL_GPIO_INTR_STAT1(ri)   LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf216 + (ri))

/**
 * \brief
 * interrupt status of GPIO[39:32]. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_INTR_STAT1 . GPIO_IN1_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_INTR_STAT1_GPIO_IN1_INTR_STAT(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_GPIO_CTRL_GPIO_INTR_STAT1_GPIO_IN1_INTR_STAT     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_GPIO_CTRL_GPIO_INTR_STAT1_GPIO_IN1_INTR_STAT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Interrupt status of GPIOs
 *
 * \details
 * Register: \a GPIO_CTRL:INTR_CFG_STAT:GPIO_INTR_STAT0
 *
 * @param ri Register: GPIO_INTR_STAT0 (??), 0-1
 */
#define LAN80XX_GPIO_CTRL_GPIO_INTR_STAT0(ri)   LAN80XX_IOREG(MMD_ID_GPIO_CTRL, 1,0xf218 + (ri))

/**
 * \brief
 * interrupt status of GPIO[31:0]. Indicates interrupt is pending or is
 * masked
 *
 * \details
 * 0 = interrupt not pending or corresponding INTR_EN is cleared
 * 1 = interrupt pending and corresponding INTR_EN is set
 *
 * Field: ::LAN80XX_GPIO_CTRL_GPIO_INTR_STAT0 . GPIO_IN_INTR_STAT
 */
#define  LAN80XX_F_GPIO_CTRL_GPIO_INTR_STAT0_GPIO_IN_INTR_STAT(x)  (x)
#define  LAN80XX_M_GPIO_CTRL_GPIO_INTR_STAT0_GPIO_IN_INTR_STAT     0xffffffff
#define  LAN80XX_X_GPIO_CTRL_GPIO_INTR_STAT0_GPIO_IN_INTR_STAT(x)  (x)


#endif /* _LAN80XX_MALIBU25G_REGS_GPIO_CTRL_H_ */
