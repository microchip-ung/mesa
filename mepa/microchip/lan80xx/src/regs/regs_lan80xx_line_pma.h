// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_LINE_PMA_H_
#define _VTSS_MALIBU25G_REGS_LINE_PMA_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a LINE_PMA
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_PMA:PMA_PMD_CONTROL
 *
 *  PMA and PMD Control 1
 */


/**
 * \brief IEEE PMA_Control set
 *
 * \details
 * Register: \a LINE_PMA:PMA_PMD_CONTROL:PMA_PMD_CONTROL_1
 */
#define LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1      LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x0)

/**
 * \brief
 * MDIO Managable Device (MMD) software reset.  This register resets
 * functions associated exclusively with the line side PMA/PMD.  Data path
 * logic and configuration registers are reset. This register is
 * self-clearing.
 *
 * \details
 * 1: Reset
 * 0: Normal operation
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1 . RESET
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_CONTROL_1_RESET(x)  LAN80XX_ENCODE_BITFIELD(!!(x),15,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_CONTROL_1_RESET  LAN80XX_BIT(15)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_CONTROL_1_RESET(x)  LAN80XX_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Speed selection bit13
 *
 * \details
 *  Speed setting with bit6, 11:bit5:2 select speed

 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1 . SPEED_SELECTION_LSB
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_LSB(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_LSB  LAN80XX_BIT(13)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_LSB(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * PMA low power setting
 *
 * \details
 *  default is 0, normal mode
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1 . LOW_POWER
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_CONTROL_1_LOW_POWER(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_CONTROL_1_LOW_POWER  LAN80XX_BIT(11)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_CONTROL_1_LOW_POWER(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Speed selection bit6
 *
 * \details
 *  Speed setting with bit13, 11:bit5:2 select speed

 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1 . SPEED_SELECTION_MSB
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_MSB(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_MSB  LAN80XX_BIT(6)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION_MSB(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Speed selection
 *
 * \details
 *  Speed selection bit(5,4,3,2)
 *  1 1 x x : Reserved
 *  1 0 1 x : Reserved
 *  1 0 0 1 : 400 Gb/s
 *  1 0 0 0 : 200 Gb/s
 *  0 1 1 1 : 5 Gb/s
 *  0 1 1 0 : 2P5 Gb/s
 *  0 1 0 1 : Reserved
 *  0 1 0 0 : 25 Gb/s
 *  0 0 1 1 : 100 Gb/s
 *  0 0 1 0 : 40 Gb/s
 *  0 0 0 1 : 10PASS-TS/2BASE-TL
 *  0 0 0 0 : 10 Gb/s
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_CONTROL_1 . SPEED_SELECTION
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION(x)  LAN80XX_ENCODE_BITFIELD(x,2,4)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION     LAN80XX_ENCODE_BITMASK(2,4)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_CONTROL_1_SPEED_SELECTION(x)  LAN80XX_EXTRACT_BITFIELD(x,2,4)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_STATUS
 *
 *  PMA and PMD Status 1
 */


/**
 * \brief  PMA_Status Register
 *
 * \details
 *  PMA_Status Register
 *
 * Register: \a LINE_PMA:PMA_PMD_STATUS:PMA_PMD_STATUS_1
 */
#define LAN80XX_LINE_PMA_PMA_PMD_STATUS_1       LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x1)

/**
 * \brief
 * Fault condition status.
 *
 * \details
 * 1: Fault condition detected
 * 0:  Fault condition not detected
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_1 . FAULT
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_1_FAULT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_1_FAULT  LAN80XX_BIT(7)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_1_FAULT(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * PMA_PMD_Link status. This is a sticky bit that latches the low state
 * type. The latch-low is set to the current link state when the register
 * is read.
 *
 * \details
 * 1: receive link up
 * 0:  receive link down
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_1 . PMA_LINK
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_1_PMA_LINK(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_1_PMA_LINK  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_1_PMA_LINK(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PMA_PMD_low_power status.
 *
 * \details
 * 1: support_low_power
 * 0: don't support_low_power
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_1 . PMA_LOW_POWER
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_1_PMA_LOW_POWER(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_1_PMA_LOW_POWER  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_1_PMA_LOW_POWER(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_DEVICE_ID
 *
 * PMA and PMD Device Identifier
 */


/**
 * \brief PMA Device Identifier 1
 *
 * \details
 * PMA Device Identifier 1
 *
 * Register: \a LINE_PMA:PMA_PMD_DEVICE_ID:PMA_PMD_DEVICE_ID_1
 */
#define VTSS_LINE_PMA_PMA_PMD_DEVICE_ID_1    VTSS_IOREG(VTSS_TO_LINE_PMA,0x2)

/**
 * \brief
 * Upper 16 bits of a 32-bit unique PMA device identifier. Bits 3-18 of the
 * device manufacturer's OUI.
 *
 * \details
 * Field: ::VTSS_LINE_PMA_PMA_PMD_DEVICE_ID_1 . PMA_DEVICE_ID_1
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_DEVICE_ID_1_PMA_DEVICE_ID_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_PMA_PMD_DEVICE_ID_1_PMA_DEVICE_ID_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_PMA_PMD_DEVICE_ID_1_PMA_DEVICE_ID_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief PMA Device Identifier 2
 *
 * \details
 * PMA Device Identifier 2
 *
 * Register: \a LINE_PMA:PMA_PMD_DEVICE_ID:PMA_PMD_DEVICE_ID_2
 */
#define VTSS_LINE_PMA_PMA_PMD_DEVICE_ID_2    VTSS_IOREG(VTSS_TO_LINE_PMA,0x3)

/**
 * \brief
 * Lower 16 bits of a 32-bit unique PMA device identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number, and a four-bit
 * revision number.
 *
 * \details
 * Field: ::VTSS_LINE_PMA_PMA_PMD_DEVICE_ID_2 . PMA_DEVICE_ID_2
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_DEVICE_ID_2_PMA_DEVICE_ID_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_PMA_PMD_DEVICE_ID_2_PMA_DEVICE_ID_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_PMA_PMD_DEVICE_ID_2_PMA_DEVICE_ID_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_SPEED_ABILITY
 *
 * PMA and PMD Speed Ability
 */


/**
 * \brief PMA and PMD Speed Ability
 *
 * \details
 * Register: \a LINE_PMA:PMA_PMD_SPEED_ABILITY:PMA_PMD_SPEED_ABILITY
 */
#define VTSS_LINE_PMA_PMA_PMD_SPEED_ABILITY  VTSS_IOREG(VTSS_TO_LINE_PMA,0x4)

/**
 * \brief
 * 25G Capable
 *
 * \details
 * 1: capable of operating at 25Gb/s
 * 0:  not capable of operating at 25Gb/s
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_SPEED_ABILITY . SPEED_25G
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_25G(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_25G  VTSS_BIT(11)
#define  VTSS_X_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_25G(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * 1G Capable
 *
 * \details
 * 1: capable of operating at 1Gb/s
 * 0:  not capable of operating at 1Gb/s
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_SPEED_ABILITY . SPEED_1G
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_1G(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_1G  VTSS_BIT(4)
#define  VTSS_X_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_1G(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 10G Capable
 *
 * \details
 * 1: capable of operating at 10Gb/s
 * 0:  not capable of operating at 10Gb/s
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_SPEED_ABILITY . SPEED_10G
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_10G(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_10G  VTSS_BIT(0)
#define  VTSS_X_LINE_PMA_PMA_PMD_SPEED_ABILITY_SPEED_10G(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_DEV_IN_PACKAGE
 *
 * PMA and PMD Devices In Package
 */


/**
 * \brief PMA and PMD Devices In Package 1
 *
 * \details
 * PMA and PMD Devices In Package 1
 *
 * Register: \a LINE_PMA:PMA_PMD_DEV_IN_PACKAGE:PMA_PMD_DEV_IN_PACKAGE_1
 */
#define VTSS_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1  VTSS_IOREG(VTSS_TO_LINE_PMA,0x5)

/**
 * \brief
 * Indicates if the PCS is present
 *
 * \details
 * 0: PCS is not present in package
 * 1: PCS is present in package
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1 . PCS_PRESENT
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PCS_PRESENT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PCS_PRESENT  VTSS_BIT(3)
#define  VTSS_X_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PCS_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Indicates if the PMA/PMD is present
 *
 * \details
 * 0: PMD/PMA is not present in package
 * 1: PMD/PMA is present in package
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1 . PMD_PMA_PRESENT
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PMD_PMA_PRESENT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PMD_PMA_PRESENT  VTSS_BIT(1)
#define  VTSS_X_LINE_PMA_PMA_PMD_DEV_IN_PACKAGE_1_PMD_PMA_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_CONTROL_2
 *
 * PMA and PMD Control 2
 */


/**
 * \brief PMA and PMD Control 2
 *
 * \details
 * PMA and PMD Control 2
 *
 * Register: \a LINE_PMA:PMA_PMD_CONTROL_2:PMA_PMD_CONTROL_2
 */
#define VTSS_LINE_PMA_PMA_PMD_CONTROL_2      VTSS_IOREG(VTSS_TO_LINE_PMA,0x7)

/**
 * \brief
 * Indicates the PMA type selected
 *
 * \details
 * 0111010: 25GBASE-SR PMA/PMD
 * 0111001: 25GBASE-KR or 25GBASE-KR-S PMA/PMD
 * 0111000: 25GBASE-CR or 25GBASE-CR-S PMA/PMD
 * 0110110: 25GBASE-ER PMA/PMD
 * 0110101: 25GBASE-LR PMA/PMD
 * 0001011: 10GBASE-KR PMA/PMD
 * 0000111: 10GBASE-SR PMA/PMD
 * 0000110: 10GBASE-LR PMA/PMD
 * 0000101: 10GBASE-ER PMA/PMD
 * 0001101: 1000BASE-KX PMA/PMD
 *
 * Field: ::VTSS_LINE_PMA_PMA_PMD_CONTROL_2 . PMA_PMD_TYPE_SELECTION
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_CONTROL_2_PMA_PMD_TYPE_SELECTION(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_LINE_PMA_PMA_PMD_CONTROL_2_PMA_PMD_TYPE_SELECTION     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_LINE_PMA_PMA_PMD_CONTROL_2_PMA_PMD_TYPE_SELECTION(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_STATUS_2
 *
 * PMA and PMD Status 2
 */


/**
 * \brief PMA and PMD Status 2
 *
 * \details
 * PMA and PMD Status 2
 *
 * Register: \a LINE_PMA:PMA_PMD_STATUS_2:PMA_PMD_STATUS_2
 */
#define LAN80XX_LINE_PMA_PMA_PMD_STATUS_2       LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8)

/**
 * \brief
 * Indicates if the PMA device is present
 *
 * \details
 * 00: Device not Present
 * 01: Reserved
 * 10: Device Present
 * 11: Reserved
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . DEVICE_PRESENT
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_DEVICE_PRESENT(x)  LAN80XX_ENCODE_BITFIELD(x,14,2)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_DEVICE_PRESENT     LAN80XX_ENCODE_BITMASK(14,2)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_DEVICE_PRESENT(x)  LAN80XX_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * PMA and PMD transmit path fault detection ability
 *
 * \details
 * 0: PMA and PMD does not have the ability to detect a fault condition on
 * the transmit path
 * 1: PMA/PMD has the ability to detect a fault condition on the transmit
 * path
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . TRANSMIT_FAULT_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),13,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT_ABILITY  LAN80XX_BIT(13)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * PMA and PMD receive path fault detection ability
 *
 * \details
 * 0: PMA and PMD does not have the ability to detect a fault condition on
 * the receive path
 * 1: PMA/PMD has the ability to detect a fault condition on the receive
 * path
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . RECEIVE_FAULT_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),12,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT_ABILITY  LAN80XX_BIT(12)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Indicates a fault condition on this interface's transmit path.  This is
 * a sticky bit that latches the high state.  The latch-high bit is cleared
 * when the register is read.
 *
 * \details
 * 0: No fault condition on transmit path
 * 1: Fault condition on transmit path
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . TRANSMIT_FAULT
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT  LAN80XX_BIT(11)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_TRANSMIT_FAULT(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Indicates a fault condition on this interface's receive path.  This is a
 * sticky bit that latches the high state.  The latch-high bit is cleared
 * when the register is read.
 *
 * \details
 * 0: No fault condition on receive path
 * 1: Fault condition on receive path
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . RECEIVE_FAULT
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_RECEIVE_FAULT(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Disable the PMA and PMD transmit path ability
 *
 * \details
 * 0: PMD does not have the ability to disable the transmit path
 * 1: PMD has the ability to disable the transmit path
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . PMD_TRANSMIT_DISABLE_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_PMD_TRANSMIT_DISABLE_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_PMD_TRANSMIT_DISABLE_ABILITY  LAN80XX_BIT(8)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_PMD_TRANSMIT_DISABLE_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * 10GBASE-SR ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-SR
 * 1: PMA and PMD is able to perform 10GBASE-SR
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_SR_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SR_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SR_ABILITY  LAN80XX_BIT(7)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SR_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * 10GBASE-LR ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-LR
 * 1: PMA and PMD is able to perform 10GBASE-LR
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_LR_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LR_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LR_ABILITY  LAN80XX_BIT(6)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LR_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * 10GBASE-ER ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-ER
 * 1: PMA and PMD is able to perform 10GBASE-ER
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_ER_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_ER_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_ER_ABILITY  LAN80XX_BIT(5)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_ER_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * 10GBASE-LX4 ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-LX4
 * 1: PMA and PMD is able to perform 10GBASE-LX4
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_LX4_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LX4_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LX4_ABILITY  LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LX4_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * 10GBASE-SW ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-SW
 * 1: PMA and PMD is able to perform 10GBASE-SW
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_SW_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SW_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SW_ABILITY  LAN80XX_BIT(3)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_SW_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * 10GBASE-LW ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-LW
 * 1: PMA and PMD is able to perform 10GBASE-LW
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_LW_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LW_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LW_ABILITY  LAN80XX_BIT(2)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_LW_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * 10GBASE-EW ability
 *
 * \details
 * 0: PMA and PMD is not able to perform 10GBASE-EW
 * 1: PMA and PMD is able to perform 10GBASE-EW
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . ETH_10GBASE_EW_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_EW_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_EW_ABILITY  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_ETH_10GBASE_EW_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Ability to perform a loopback function
 *
 * \details
 * 0: PMA does not have the ability to perform a loopback function
 * 1: PMA has the ability to perform a loopback function
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_PMD_STATUS_2 . PMA_LOOPBACK_ABILITY
 */
#define  LAN80XX_F_LINE_PMA_PMA_PMD_STATUS_2_PMA_LOOPBACK_ABILITY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_PMA_PMD_STATUS_2_PMA_LOOPBACK_ABILITY  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_PMA_PMD_STATUS_2_PMA_LOOPBACK_ABILITY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a LINE_PMA:PMA_PMD_PACKAGE_ID
 *
 * PMA and PMD Package Identifier
 */


/**
 * \brief PMA and PMD Package Identifier 1
 *
 * \details
 * PMA and PMD Package Identifier 1
 *
 * Register: \a LINE_PMA:PMA_PMD_PACKAGE_ID:PMA_PMD_PACKAGE_ID_1
 */
#define VTSS_LINE_PMA_PMA_PMD_PACKAGE_ID_1   VTSS_IOREG(VTSS_TO_LINE_PMA,0xe)

/**
 * \brief
 * PMA and PMD package identifier 1
 *
 * \details
 * Field: ::VTSS_LINE_PMA_PMA_PMD_PACKAGE_ID_1 . PMA_PMD_PACKAGE_ID_1
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief PMA and PMD package identifier 2
 *
 * \details
 * PMA and PMD package identifier 2
 *
 * Register: \a LINE_PMA:PMA_PMD_PACKAGE_ID:PMA_PMD_PACKAGE_ID_2
 */
#define VTSS_LINE_PMA_PMA_PMD_PACKAGE_ID_2   VTSS_IOREG(VTSS_TO_LINE_PMA,0xf)

/**
 * \brief
 * PMA and PMD Package Identifier 2
 *
 * \details
 * Field: ::VTSS_LINE_PMA_PMA_PMD_PACKAGE_ID_2 . PMA_PMD_PACKAGE_ID_2
 */
#define  VTSS_F_LINE_PMA_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_PMA:SD_RESET
 *
 *  Software Reset for Serdes Tx/Rx
 */


/**
 * \brief Software reset bit for the PCS25G, PCS1G, and KR IP transmit functions
 *
 * \details
 * Register: \a LINE_PMA:SD_RESET:SD_SER_RST
 */
#define LAN80XX_LINE_PMA_SD_SER_RST             LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8000)

/**
 * \brief
 * Software reset bit for the PCS25G, PCS1G, and KR IP transmit functions.
 * This bit does not reset any PMA/SerDes functions, but the reset signal
 * is synchronized to the PMA_TX_CK. The clock itself is not reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_LINE_PMA_SD_SER_RST . PCS_KR_TX_RST
 */
#define  LAN80XX_F_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_SER_RST_PCS_KR_TX_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Software reset bit for the PCS25G, PCS1G, and KR IP receive functions.
 *
 * \details
 * Register: \a LINE_PMA:SD_RESET:SD_DES_RST
 */
#define LAN80XX_LINE_PMA_SD_DES_RST             LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8001)

/**
 * \brief
 * Software reset bit for the PCS25G, PCS1G, and KR IP receive functions.
 * This bit does not reset any PMA/SerDes functions, but the reset signal
 * is synchronized to the PMA_RX_CK. The clock itself is no reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_LINE_PMA_SD_DES_RST . PCS_KR_RX_RST
 */
#define  LAN80XX_F_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_DES_RST_PCS_KR_RX_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a LINE_PMA:SD_LANE_CFG_STAT
 *
 * SD Lane configuration and Status
 */


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_0
 */
#define LAN80XX_LINE_PMA_SD_LANE_CFG_0          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8002)
/**
 * \brief
 * Software Reset for SD Lane macro fundamental reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . MACRO_RST
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_MACRO_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_MACRO_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_MACRO_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)
/**
 * \brief
 * Software Reset for SD configuration interface.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . EXT_CFG_RST
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_EXT_CFG_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_EXT_CFG_RST  LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_EXT_CFG_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . PCS2PMA_PHYMODE
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE(x)  LAN80XX_ENCODE_BITFIELD(x,5,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE     LAN80XX_ENCODE_BITMASK(5,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE(x)  LAN80XX_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Software Reset for SD Lane reset.

 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . LANE_RST
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_LANE_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_LANE_RST  LAN80XX_BIT(8)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_LANE_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PCS link train control: pre-equalization control of TX
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . PCS_EN_ADV
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_PCS_EN_ADV(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_PCS_EN_ADV  LAN80XX_BIT(9)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_PCS_EN_ADV(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * PCS link train control: TX data path control
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . PCS_EN_MAIN
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_PCS_EN_MAIN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_PCS_EN_MAIN  LAN80XX_BIT(10)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_PCS_EN_MAIN(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * PCS link train control: 1st-stage post-equalization
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . PCS_EN_DLY
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_PCS_EN_DLY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_PCS_EN_DLY  LAN80XX_BIT(11)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_PCS_EN_DLY(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * PCS link train control: pre-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_0 . PCS_TAP_ADV
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_0_PCS_TAP_ADV(x)  LAN80XX_ENCODE_BITFIELD(x,12,4)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_0_PCS_TAP_ADV     LAN80XX_ENCODE_BITMASK(12,4)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_0_PCS_TAP_ADV(x)  LAN80XX_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_1
 */
#define LAN80XX_LINE_PMA_SD_LANE_CFG_1          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8003)
/**
 * \brief
 * PCS link train control: TX data path setting
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_1 . PCS_TAP_MAIN
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * PCS link train control: 1st-stage post-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_CFG_1 . PCS_TAP_DLY
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_DLY(x)  LAN80XX_ENCODE_BITFIELD(x,1,5)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_DLY     LAN80XX_ENCODE_BITMASK(1,5)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_1_PCS_TAP_DLY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,5)

/**
 * \brief
 * RX traditional eye scan monitor enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS_ISCAN_EN
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN  VTSS_BIT(6)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RX fast eye scan monitor enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS_EN_FAST_ISCAN
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN  VTSS_BIT(7)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Controls transmitter voltage swing level
 *
 * \details
 * 0: full swing
 * 1: low swing
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS2PMA_TXSWING
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING  VTSS_BIT(8)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Transmit path electrical idle
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS2PMA_TXEI
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI  VTSS_BIT(9)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Transmitter voltage level control
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS2PMA_TXMARGIN
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_1 . PCS2PMA_TX_SPEED
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,13,2)


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_2
 */
#define VTSS_LINE_PMA_SD_LANE_CFG_2          VTSS_IOREG(VTSS_TO_LINE_PMA,0x8004)
#define LAN80XX_LINE_PMA_SD_LANE_CFG_2       LAN80XX_IOREG(MMD_ID_LINE_PMA, 0 , 0x8004)
/**
 * \brief
 * RXFIFO clock divider
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_2 . RXFIFO_CK_DIV
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)



/**
 * \brief
 * TXFIFO clock divider
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_2 . TXFIFO_CK_DIV
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,3,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV     LAN80XX_ENCODE_BITMASK(3,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * PMA transmit clock frequency selection
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_2 . PMA_TXCK_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,3)


#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,6,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL     LAN80XX_ENCODE_BITMASK(6,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,6,3)
/**
 * \brief
 * PMA receiver clock frequency selection
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_2 . PMA_RXDIV_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)


#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)


/**
 * \brief
 * TX/RX data width selection
 *
 * \details
 * 000: 10-bit mode
 * 001: 16-bit mode
 * 010: 20-bit mode
 * 011: 32-bit mode
 * 100: 40-bit mode
 * 101: 64-bit mode
 * 110: Reserved
 * 111: Reserved
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_2 . DATA_WIDTH_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  VTSS_EXTRACT_BITFIELD(x,13,3)
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,13,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL     LAN80XX_ENCODE_BITMASK(13,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_3
 */
#define VTSS_LINE_PMA_SD_LANE_CFG_3          VTSS_IOREG(VTSS_TO_LINE_PMA,0x8005)
#define LAN80XX_LINE_PMA_SD_LANE_CFG_3       LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8005)
/**
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_3 . HWT_PRE_DIVSEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief
 * PMA VCO post divider ratio selection (or reference clock multiplying
 * factor)
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_3 . HWT_VCO_DIV_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,2,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL     LAN80XX_ENCODE_BITMASK(2,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,2,3)
/**
 * \brief
 * PLL multiplying factor (Fref*N)
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_3 . HWT_CFG_SEL_DIV
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,5,4)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV     LAN80XX_ENCODE_BITMASK(5,4)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,5,4)
/**
 * \brief
 * PMA transmit clock full/subrate frequency selection
 *
 * \details
 * 00: full
 * 01: 1/2
 * 10: 1/4
 * 11: 1/8
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_3 . TXRATE_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)
#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * PMA receive clock full/subrate frequency selection
 *
 * \details
 * 00: full
 * 01: 1/2
 * 10: 1/4
 * 11: 1/8
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_CFG_3 . RXRATE_SEL
 */
#define  VTSS_F_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

#define  LAN80XX_F_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,13,3)
#define  LAN80XX_M_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL     LAN80XX_ENCODE_BITMASK(13,3)
#define  LAN80XX_X_LINE_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_STAT_0
 */
#define LAN80XX_LINE_PMA_SD_LANE_STAT_0         LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x8006)

/**
 * \brief
 * PMA Reset done. Asserted when reset is completed following MACRO_RST
 * deassertion.
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::LAN80XX_LINE_PMA_SD_LANE_STAT_0 . PMA_RST_DONE
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_STAT_0_PMA_RST_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_STAT_0_PMA_RST_DONE     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_LANE_STAT_0_PMA_RST_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Lane Reset done. Asserted when reset is completed following LANE_RST
 * deassertion
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::VTSS_LINE_PMA_SD_LANE_STAT_0 . LANE_RST_DONE
 */
#define  LAN80XX_F_LINE_PMA_SD_LANE_STAT_0_LANE_RST_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_SD_LANE_STAT_0_LANE_RST_DONE     LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_SD_LANE_STAT_0_LANE_RST_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a LINE_PMA:SD_LANE_CFG_STAT:SD_LANE_STAT_1
 */
#define VTSS_LINE_PMA_SD_LANE_STAT_1         VTSS_IOREG(VTSS_TO_LINE_PMA,0x8007)

/**
 * \brief
 * Access to internal serdes state
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_LANE_STAT_1 . DBG_OBS
 */
#define  VTSS_F_LINE_PMA_SD_LANE_STAT_1_DBG_OBS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_SD_LANE_STAT_1_DBG_OBS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_SD_LANE_STAT_1_DBG_OBS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_PMA:SD_CFG
 *
 * SD Signal Detect Configuration
 */


/**
 * \brief SD Signal Detect Configuration
 *
 * \details
 * Serdes Signal Detect Configuration
 *
 * Register: \a LINE_PMA:SD_CFG:SD_CFG
 */
#define VTSS_LINE_PMA_SD_CFG                 VTSS_IOREG(VTSS_TO_LINE_PMA,0x8008)

/**
 * \brief
 * Signal Detect Enable
 *
 * \details
 * 0: The Signal Detect input pin is ignored active Signal Detect is
 * assumed at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_LINE_PMA_SD_CFG . SD_ENA
 */
#define  VTSS_F_LINE_PMA_SD_CFG_SD_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LINE_PMA_SD_CFG_SD_ENA        VTSS_BIT(0)
#define  VTSS_X_LINE_PMA_SD_CFG_SD_ENA(x)     VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_LINE_PMA_SD_CFG . SD_POL
 */
#define  VTSS_F_LINE_PMA_SD_CFG_SD_POL(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LINE_PMA_SD_CFG_SD_POL        VTSS_BIT(1)
#define  VTSS_X_LINE_PMA_SD_CFG_SD_POL(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_LINE_PMA_SD_CFG . SD_SEL
 */
#define  VTSS_F_LINE_PMA_SD_CFG_SD_SEL(x)     VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_LINE_PMA_SD_CFG_SD_SEL        VTSS_BIT(2)
#define  VTSS_X_LINE_PMA_SD_CFG_SD_SEL(x)     VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 *  50 ohm Termination of REFCKP/N control from pin
 *
 * \details
 * 0: Choose the SerDes IP register for Termination control
 * 1: Line 0 and Line 3 terminations controlled by CLKTERML0 and CLKTERML3.
 * Line 1 and Line 2 terminations disabled.
 *
 * Field: ::VTSS_LINE_PMA_SD_CFG . HWT_REFCLK_R_SEL
 */
#define  VTSS_F_LINE_PMA_SD_CFG_HWT_REFCLK_R_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_LINE_PMA_SD_CFG_HWT_REFCLK_R_SEL  VTSS_BIT(5)
#define  VTSS_X_LINE_PMA_SD_CFG_HWT_REFCLK_R_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * Register Group: \a LINE_PMA:SD_CLK_GATE
 *
 * Gating all macro generated clocks
 */


/**
 * \brief Gating all macro generated clocks
 *
 * \details
 * Gate SD generated clocks during speed change
 *
 * Register: \a LINE_PMA:SD_CLK_GATE:SD_CLK_GATE
 */
#define LAN80XX_LINE_PMA_SD_CLK_GATE            LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x8009)

/**
 * \details
 * 0 :  enable macro clock generation towards core (RX & TX)
 * 1 :  disable (gate) macro clock generation towards core (TX & TX)
 *
 * Field: ::LAN80XX_LINE_PMA_SD_CLK_GATE . SD_CLK_GATE
 */
#define  LAN80XX_F_LINE_PMA_SD_CLK_GATE_SD_CLK_GATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_SD_CLK_GATE_SD_CLK_GATE     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_SD_CLK_GATE_SD_CLK_GATE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a LINE_PMA:SD_PWR_CFG
 *
 * SD Power configuration
 */


/**
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a LINE_PMA:SD_PWR_CFG:NORMAL_MODE_0
 */
#define LAN80XX_LINE_PMA_NORMAL_MODE_0          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x800a)

/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_LINE_PMA_NORMAL_MODE_0 . NORMAL_MODE_0
 */
#define  LAN80XX_F_LINE_PMA_NORMAL_MODE_0_NORMAL_MODE_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_PMA_NORMAL_MODE_0_NORMAL_MODE_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_PMA_NORMAL_MODE_0_NORMAL_MODE_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a LINE_PMA:SD_PWR_CFG:NORMAL_MODE_1
 */
#define LAN80XX_LINE_PMA_NORMAL_MODE_1          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x800b)
/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode
 * Bits 17 to 19 are for TX direction, other bits are for RX direction.
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_LINE_PMA_NORMAL_MODE_1 . NORMAL_MODE_1
 */
#define  LAN80XX_F_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1     LAN80XX_ENCODE_BITMASK(0,9)
#define  LAN80XX_X_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Power Control Select. Use to switch SerDes power mode state.
 * SerDes comes up in a low power state after reset from the default value
 *
 * \details
 * 0: Select SD lane low power setting from register LOWPWR_MODE_0 and LOWPWR_MODE_1.
 * 1: Select SD lane normal power setting from register NORMAL_MODE_0 and NORMAL_MODE_1.
 *
 * Field: ::LAN80XX_LINE_PMA_NORMAL_MODE_1 . PWR_CTRL_SEL
 */
#define  LAN80XX_F_LINE_PMA_NORMAL_MODE_1_PWR_CTRL_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_LINE_PMA_NORMAL_MODE_1_PWR_CTRL_SEL     LAN80XX_BIT(15)
#define  LAN80XX_X_LINE_PMA_NORMAL_MODE_1_PWR_CTRL_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief Power settings for Low Power mode.
 *
 * \details
 * Register: \a LINE_PMA:SD_PWR_CFG:LOWPWR_MODE_0
 */
#define LAN80XX_LINE_PMA_LOWPWR_MODE_0          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x800c)

/**
 * \brief
 * Power Down Control settings for SD Lane in Low Power Mode
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_LINE_PMA_LOWPWR_MODE_0 . LOWPWR_MODE_0
 */
#define  LAN80XX_F_LINE_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_LINE_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_LINE_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief Power settings for Low Power mode.
 *
 * \details
 * Register: \a LINE_PMA:SD_PWR_CFG:LOWPWR_MODE_1
 */
#define LAN80XX_LINE_PMA_LOWPWR_MODE_1          LAN80XX_IOREG(MMD_ID_LINE_PMA, 0, 0x800d)

/**
 * \brief
 * Power Down Control settings for SD Lane in Low Power Mode
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_LINE_PMA_LOWPWR_MODE_1 . LOWPWR_MODE_1
 */
#define  LAN80XX_F_LINE_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_LINE_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1     LAN80XX_ENCODE_BITMASK(0,9)
#define  LAN80XX_X_LINE_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

#define  LAN80XX_F_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1     LAN80XX_ENCODE_BITMASK(0,9)
#define  LAN80XX_X_LINE_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a LINE_PMA:SD_ANEG_CFG
 *
 * PCS and ANEG data selection control for TX
 */


/**
 * \brief SD_KR_ANEG_MODE
 *
 * \details
 * Configure ANEG to SerDes (TX) behavior
 *
 * Register: \a LINE_PMA:SD_ANEG_CFG:SD_KR_ANEG_MODE
 */
#define VTSS_LINE_PMA_SD_KR_ANEG_MODE        VTSS_IOREG(VTSS_TO_LINE_PMA,0x8010)

/**
 * \brief
 * Configure how ANEG TX data is multiplexed into Serial Data stream
 *
 * \details
 * 00: auto (TX connection to Serializer controlled by KR block)
 * 01: reserved
 * 10: force off (i.e. ANEG TX data never connected to Serializer)
 * 11: force on (i.e. ANEG TX data always connected to Serializer)
 *
 * Field: ::VTSS_LINE_PMA_SD_KR_ANEG_MODE . TX_ANEG_MODE
 */
#define  VTSS_F_LINE_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_LINE_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_LINE_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a LINE_PMA:SD_EXTCFG_CFG
 *
 * Configuration of SD local parallel configuration interface (EXT_CFG)
 */


/**
 * \brief Configuration of SD local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a LINE_PMA:SD_EXTCFG_CFG:SD_EXTCFG_CFG
 */
#define VTSS_LINE_PMA_SD_EXTCFG_CFG          VTSS_IOREG(VTSS_TO_LINE_PMA,0x8011)
#define LAN80XX_LINE_PMA_SD_EXTCFG_CFG        LAN80XX_IOREG(MMD_ID_LINE_PMA, 0 , 0x8011)
/**
 * \brief
 * Clock divider for EXTCFG Master.
 * Divide the system clock by N + 2 to be used as EXTCFG master clock for
 * SerDes configuration.
 *
 * \details
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::VTSS_LINE_PMA_SD_EXTCFG_CFG . CLK_DIV
 */
#define  VTSS_F_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

#define  LAN80XX_F_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_LINE_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * EXTCFG Interface Timing configuration.
 *
 * Additional N wait states before write enable is asserted after driving
 * address and write data.
 *
 * \details
 * Total Wait States are N+2 clock cycles of EXT_CFG clock signal.
 *
 * Field: ::VTSS_LINE_PMA_SD_EXTCFG_CFG . WS_SETUP_WR
 */
#define  VTSS_F_LINE_PMA_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_LINE_PMA_SD_EXTCFG_CFG_WS_SETUP_WR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_LINE_PMA_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.
 *
 * Additional N wait states before write enable is deasserted again.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_LINE_PMA_SD_EXTCFG_CFG . WS_EXEC_WR
 */
#define  VTSS_F_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_WR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.
 *
 * Additional N wait states before start of next write access.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_LINE_PMA_SD_EXTCFG_CFG . WS_HOLD_WR
 */
#define  VTSS_F_LINE_PMA_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_LINE_PMA_SD_EXTCFG_CFG_WS_HOLD_WR     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_LINE_PMA_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.
 *
 * Additional N wait states before read data is sampled.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+3 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_LINE_PMA_SD_EXTCFG_CFG . WS_EXEC_RD
 */
#define  VTSS_F_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_RD     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_LINE_PMA_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * Register Group: \a LINE_PMA:SD_FIFO_DELAY
 *
 * Registers for precise FIFO delay measurement
 */


/**
 * \brief FIFO delay measurement configuration
 *
 * \details
 * FIFO delay measurement configuration register
 *
 * Register: \a LINE_PMA:SD_FIFO_DELAY:SD_DELAY_CFG
 */
#define VTSS_LINE_PMA_SD_DELAY_CFG           VTSS_IOREG(VTSS_TO_LINE_PMA,0x8012)

/**
 * \brief
 * Configures the number of cycles the skew detector should run before
 * returning serdes delay
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_DELAY_CFG . SAMPLE_TIME
 */
#define  VTSS_F_LINE_PMA_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_LINE_PMA_SD_DELAY_CFG_SAMPLE_TIME     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_LINE_PMA_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a LINE_PMA:SD_FIFO_DELAY:SD_RX_DELAY_VAR
 */
#define VTSS_LINE_PMA_SD_RX_DELAY_VAR        VTSS_IOREG(VTSS_TO_LINE_PMA,0x8013)

/**
 * \brief
 * Link-up dynamic delay to be added to the PTP RX I/O link delay
 * configuration. Value is the fraction of 65536 of the maximum delay at a
 * given speed and lane index.1.0 Gbps: 128 ns10.0 Gbps: 24.8 ns25.0 Gbps:
 * 6.2 ns
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_RX_DELAY_VAR . RX_DELAY_VAR
 */
#define  VTSS_F_LINE_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a LINE_PMA:SD_FIFO_DELAY:SD_TX_DELAY_VAR
 */
#define VTSS_LINE_PMA_SD_TX_DELAY_VAR        VTSS_IOREG(VTSS_TO_LINE_PMA,0x8014)

/**
 * \brief
 * Link-up dynamic delay to be added to the PTP TX I/O link delay
 * configuration. Value is the fraction of 65536 of the maximum delay at a
 * given speed and lane index.1.0 Gbps: 128 ns10.0 Gbps: 18.6 ns25.0 Gbps:
 * 6.2 ns
 *
 * \details
 * Field: ::VTSS_LINE_PMA_SD_TX_DELAY_VAR . TX_DELAY_VAR
 */
#define  VTSS_F_LINE_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a LINE_PMA:HW_CFG
 *
 * Hardware Configuration
 */


/**
 * \brief KR ANEG Configuration
 *
 * \details
 * KR ANEG configuration
 *
 * Register: \a LINE_PMA:HW_CFG:KR_DATA_CFG
 */
#define VTSS_LINE_PMA_KR_DATA_CFG            VTSS_IOREG(VTSS_TO_LINE_PMA,0x8016)

/**
 * \brief
 * Revert 10B data bus portion.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_LINE_PMA_KR_DATA_CFG . REVERT_10B
 */
#define  VTSS_F_LINE_PMA_KR_DATA_CFG_REVERT_10B(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LINE_PMA_KR_DATA_CFG_REVERT_10B  VTSS_BIT(0)
#define  VTSS_X_LINE_PMA_KR_DATA_CFG_REVERT_10B(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_LINE_PMA_KR_DATA_CFG . REVERT_64B_TX
 */
#define  VTSS_F_LINE_PMA_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LINE_PMA_KR_DATA_CFG_REVERT_64B_TX  VTSS_BIT(1)
#define  VTSS_X_LINE_PMA_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_LINE_PMA_KR_DATA_CFG . REVERT_64B_RX
 */
#define  VTSS_F_LINE_PMA_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_LINE_PMA_KR_DATA_CFG_REVERT_64B_RX  VTSS_BIT(2)
#define  VTSS_X_LINE_PMA_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * The bus width selection of KR with Serdes interface.
 *
 * \details
 * 1 : Configure the data bus width to 64 bits.
 * 0 : Configure the data bus width to 40 bits, this is default
 *
 * Field: ::VTSS_LINE_PMA_KR_DATA_CFG . KR_DATA_BUS_MODE
 */
#define  VTSS_F_LINE_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_LINE_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE  VTSS_BIT(3)
#define  VTSS_X_LINE_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * Register Group: \a LINE_PMA:PMA_INT
 *
 * PMA_INT
 */

/**
 * \brief PMA interrupt register. All sticky
 *
 * \details
 * Register: \a LINE_PMA:PMA_INT:PMA_IRQ_VEC
 */
#define LAN80XX_LINE_PMA_PMA_IRQ_VEC            LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8018)

/**
 * \brief
 * pma rx electrical idle signal interrupt, write 1 to clear
 *
 * \details
 * 0 : pma doesn't detect RX electrical idle
 * 1 : pma detects RX electrical idle
 *
 * Field: ::VTSS_LINE_PMA_PMA_IRQ_VEC . PMA_RXEI_FILTERED_INT
 */
#define  LAN80XX_F_LINE_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * pma reset done interrupt, write 1 to clear
 *
 * \details
 * 0 : pma reset sequence is not complete
 * 1 : pma accomplished the global reset
 *
 * Field: ::VTSS_LINE_PMA_PMA_IRQ_VEC . PMA_RESET_DONE
 */
#define  LAN80XX_F_LINE_PMA_PMA_IRQ_VEC_PMA_RESET_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_PMA_IRQ_VEC_PMA_RESET_DONE     LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_PMA_IRQ_VEC_PMA_RESET_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief interrupt mask
 *
 * \details
 * Register: \a LINE_PMA:PMA_INT:PMA_IRQ_MASK
 */
#define LAN80XX_LINE_PMA_PMA_IRQ_MASK           LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x8019)

/**
 * \brief
 * Interrupt enable for pma rx signal idle
 *
 * \details
 * 0 : pma_rxei_filtered_int will not propagate to interrupt
 * 1 : pma_rxei_filtered_int will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_IRQ_MASK . PMA_RXEI_FILTERED_INT_EN
 */
#define  LAN80XX_F_LINE_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_LINE_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN     LAN80XX_BIT(0)
#define  LAN80XX_X_LINE_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Interrupt enable for pma reset done
 *
 * \details
 * 0 : pma_reset_done will not propagate to interrupt
 * 1 : pma_reset_done will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_PMA_PMA_IRQ_MASK . PMA_RESET_DONE_INT_EN
 */
#define  LAN80XX_F_LINE_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_LINE_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN     LAN80XX_BIT(1)
#define  LAN80XX_X_LINE_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a LINE_PMA:LINE_PMA_DEBUG
 *
 * LINE_PMA debug registers
 */


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 7
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_7
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_7   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80f8)

/**
 * \brief
 * LINE_PMA debug register 7
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_7 . LINE_PMA_DBG_REG_7
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_7_LINE_PMA_DBG_REG_7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_7_LINE_PMA_DBG_REG_7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_7_LINE_PMA_DBG_REG_7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 6
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_6
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_6   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80f9)

/**
 * \brief
 * LINE_PMA debug register 6
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_6 . LINE_PMA_DBG_REG_6
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_6_LINE_PMA_DBG_REG_6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_6_LINE_PMA_DBG_REG_6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_6_LINE_PMA_DBG_REG_6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 5
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_5
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_5   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80fa)

/**
 * \brief
 * LINE_PMA debug register 5
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_5 . LINE_PMA_DBG_REG_5
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_5_LINE_PMA_DBG_REG_5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_5_LINE_PMA_DBG_REG_5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_5_LINE_PMA_DBG_REG_5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 4
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_4
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_4   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80fb)

/**
 * \brief
 * LINE_PMA debug register 4
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_4 . LINE_PMA_DBG_REG_4
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_4_LINE_PMA_DBG_REG_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_4_LINE_PMA_DBG_REG_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_4_LINE_PMA_DBG_REG_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 3
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_3
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_3   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80fc)

/**
 * \brief
 * LINE_PMA debug register 3
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_3 . LINE_PMA_DBG_REG_3
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_3_LINE_PMA_DBG_REG_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_3_LINE_PMA_DBG_REG_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_3_LINE_PMA_DBG_REG_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 2
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_2
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_2   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80fd)

/**
 * \brief
 * LINE_PMA debug register 2
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_2 . LINE_PMA_DBG_REG_2
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_2_LINE_PMA_DBG_REG_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_2_LINE_PMA_DBG_REG_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_2_LINE_PMA_DBG_REG_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 1
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_1
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_1   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80fe)

/**
 * \brief
 * LINE_PMA debug register 1
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_1 . LINE_PMA_DBG_REG_1
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_1_LINE_PMA_DBG_REG_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_1_LINE_PMA_DBG_REG_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_1_LINE_PMA_DBG_REG_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * LINE_PMA debug register 0
 *
 * Register: \a LINE_PMA:LINE_PMA_DEBUG:LINE_PMA_DEBUG_REG_0
 */
#define VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_0   VTSS_IOREG(VTSS_TO_LINE_PMA,0x80ff)

/**
 * \brief
 * LINE_PMA debug register 0
 *
 * \details
 * Field: ::VTSS_LINE_PMA_LINE_PMA_DEBUG_REG_0 . LINE_PMA_DBG_REG_0
 */
#define  VTSS_F_LINE_PMA_LINE_PMA_DEBUG_REG_0_LINE_PMA_DBG_REG_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LINE_PMA_LINE_PMA_DEBUG_REG_0_LINE_PMA_DBG_REG_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LINE_PMA_LINE_PMA_DEBUG_REG_0_LINE_PMA_DBG_REG_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief PMA external registers cmu group 0
 *
 * \details
 * LINE_PMA_EXT
 *
 * Register: \a LINE_PMA_EXT:CMU_GRP_0
 */

#define LAN80XX_LINE_PMA_EXT_CMU_GRP_0_CMU_13  LAN80XX_IOREG(MMD_ID_LINE_PMA, 0 , 0xf013)


/**
 * \brief PMA external registers cmu group 0
 *
 * \details
 * Internal use
 *
 * Register: \a LINE_PMA_EXT:CMU_GRP_0:CFG_JT_EN
 */

#define  LAN80XX_F_LINE_PMA_EXT_CMU_GRP_0_CMU_13_CFG_JT_EN(x)  LAN80XX_ENCODE_BITFIELD(x,4,1)
#define  LAN80XX_M_LINE_PMA_EXT_CMU_GRP_0_CMU_13_CFG_JT_EN     LAN80XX_BIT(4)
#define  LAN80XX_X_LINE_PMA_EXT_CMU_GRP_0_CMU_13_CFG_JT_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)




#endif /* _VTSS_MALIBU25G_REGS_LINE_PMA_H_ */
