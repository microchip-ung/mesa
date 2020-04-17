// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_VENICE_DEV1_H_
#define _VTSS_VENICE_REGS_VENICE_DEV1_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VENICE_DEV1
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMA_CONTROL
 *
 * Device 1 IEEE MDIO Configuration and Status Register set
 */


/** 
 * \brief PMA Control Register 1
 *
 * \details
 * PMA Control Register 1
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_CONTROL:PMA_CONTROL_1
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1  VTSS_IOREG(0x01, 0, 0x0000)

/** 
 * \brief
 * MDIO Managable Device (MMD) software reset.	This register resets
 * functions associated exclusively with the line side PMA.  Data path
 * logic and configuration registers are reset. This register is
 * self-clearing.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . RST
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_RST  VTSS_BIT(15)

/** 
 * \brief
 * Indicates whether the device operates at 10 Gbps and above.
 *
 * \details 
 * 0: Unspecified
 * 1: Operation at 10 Gbps and above
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . SPEED_SEL_A
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_SPEED_SEL_A  VTSS_BIT(13)

/** 
 * \brief
 * The channel's data path is placed into low power mode with this
 * register.  The PMA in this channel is also placed into low power mode
 * regardless of the channel cross connect configuration.  The
 * PMD_TRANSMIT_DISABLE.GLOBAL_PMD_TRANSMIT_DISABLE register state can can
 * be transmitted from a GPIO pin to shut off an optics module's TX driver.
 *
 * \details 
 * 1: Low Power Mode.
 * 0: Normal Operation.
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . LOW_PWR_PMA
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_LOW_PWR_PMA  VTSS_BIT(11)

/** 
 * \brief
 * Indicates whether the device operates at 10 Gbps and above.
 *
 * \details 
 * 0: Unspecified
 * 1: 10 Gbps an above
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . SPEED_SEL_B
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_SPEED_SEL_B  VTSS_BIT(6)

/** 
 * \brief
 * Device speed selection
 *
 * \details 
 * 1xxx: Reserved
 * x1xx: Reserved
 * xx1x: Reserved
 * 0001: Reserved
 * 0000: 10 Gbps
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . SPEED_SEL_C
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_SPEED_SEL_C(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_SPEED_SEL_C     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_SPEED_SEL_C(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/** 
 * \brief
 * Enable PMA Pad Loopback H5
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1 . EN_PAD_LOOP
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_CONTROL_PMA_CONTROL_1_EN_PAD_LOOP  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMA_STATUS
 *
 * Device 1 IEEE MDIO Status Register set
 */


/** 
 * \brief PMA Status Register 1
 *
 * \details
 * PMA Status Register 1
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_STATUS:PMA_STATUS_1
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1  VTSS_IOREG(0x01, 0, 0x0001)

/** 
 * \brief
 * Indicates a fault condition for this interface in either the transmit or
 * the receive paths.
 *
 * \details 
 * 0: Fault condition not detected.  Latch-high alarm status bits
 * TRANSMIT_FAULT=0 AND RECEIVE_FAULT=0.
 * 1: Fault condition detected.  Latch-high alarm status bits
 * TRANSMIT_FAULT=1 OR RECEIVE_FAULT=1.
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1 . FAULT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1_FAULT  VTSS_BIT(7)

/** 
 * \brief
 * Indicates the receive link status for this interface
 * This is a sticky bit that latches the low state. The latch-low bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: PMA/PMD receive link down
 * 1: PMA/PMD receive link up
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1 . RECEIVE_LINK_STATUS
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1_RECEIVE_LINK_STATUS  VTSS_BIT(2)

/** 
 * \brief
 * Indicates PMA/PMD supports Low Power Mode
 *
 * \details 
 * 0: PMA/PMD does not support low power mode
 * 1: PMA/PMD supports low power mode
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1 . LOW_POWER_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_STATUS_PMA_STATUS_1_LOW_POWER_ABILITY  VTSS_BIT(1)

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID
 *
 * Device 1 IEEE MDIO Configuration and Status Register set
 */


/** 
 * \brief PMA Device Identifier 1
 *
 * \details
 * PMA Device Identifier 1
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_DEVICE_ID_1
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_1  VTSS_IOREG(0x01, 0, 0x0002)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique PMA device identifier. Bits 3-18 of the
 * device manufacturer's OUI.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_1 . PMA_DEVICE_ID_1
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_1_PMA_DEVICE_ID_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_1_PMA_DEVICE_ID_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_1_PMA_DEVICE_ID_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PMA Device Identifier 2
 *
 * \details
 * PMA Device Identifier 2
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_DEVICE_ID_2
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_2  VTSS_IOREG(0x01, 0, 0x0003)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique PMA device identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number, and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_2 . PMA_DEVICE_ID_2
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_2_PMA_DEVICE_ID_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_2_PMA_DEVICE_ID_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_DEVICE_ID_2_PMA_DEVICE_ID_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PMA/PMD Speed Ability
 *
 * \details
 * PMA/PMD Speed Ability
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_PMD_SPEED_ABILITY
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_SPEED_ABILITY  VTSS_IOREG(0x01, 0, 0x0004)

/** 
 * \brief
 * Indicates PMA/PMD capability to run at 10 Gbps
 *
 * \details 
 * 0: PMA/PMD is not capable of operating at 10 Gbps
 * 1: PMA/PMD is capable of operating at 10 Gbps
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_SPEED_ABILITY . ETH_10G_CAPABLE
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_SPEED_ABILITY_ETH_10G_CAPABLE  VTSS_BIT(0)


/** 
 * \brief PMA/PMD Devices In Package 1
 *
 * \details
 * PMA/PMD Devices In Package 1
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_PMD_DEV_IN_PACKAGE_1
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1  VTSS_IOREG(0x01, 0, 0x0005)

/** 
 * \brief
 * Indicates if the DTE XS is present
 *
 * \details 
 * 0: DTE XS is not present in package
 * 1: DTE XS is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . DTE_XS_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_DTE_XS_PRESENT  VTSS_BIT(5)

/** 
 * \brief
 * Indicates if the PHY XS is present
 *
 * \details 
 * 0: PHY XS is not present in package
 * 1: PHY iXS is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . PHY_XS_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_PHY_XS_PRESENT  VTSS_BIT(4)

/** 
 * \brief
 * Indicates if the PCS is present
 *
 * \details 
 * 0: PCS is not present in package
 * 1: PCS is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . PCS_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_PCS_PRESENT  VTSS_BIT(3)

/** 
 * \brief
 * Indicates if the WIS is present
 *
 * \details 
 * 0: WIS is not present in package
 * 1: WIS is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . WIS_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_WIS_PRESENT  VTSS_BIT(2)

/** 
 * \brief
 * Indicates if the PMA/PMD is present
 *
 * \details 
 * 0: PMD/PMA is not present in package
 * 1: PMD/PMA is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . PMD_PMA_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_PMD_PMA_PRESENT  VTSS_BIT(1)

/** 
 * \brief
 * Indicates if the clause 22 registers are present
 *
 * \details 
 * 0: Clause 22 registers are not present in package
 * 1: Clause 22 registers are present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1 . CLAUSE_22_REG_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_1_CLAUSE_22_REG_PRESENT  VTSS_BIT(0)


/** 
 * \brief PMA/PMD Devices In Package 2
 *
 * \details
 * PMA/PMD Devices In Package 2
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_PMD_DEV_IN_PACKAGE_2
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_2  VTSS_IOREG(0x01, 0, 0x0006)

/** 
 * \brief
 * Indicates if the vendor specific device 2 is present
 *
 * \details 
 * 0: Vendor specific device 2 is not present in package
 * 1: Vendor specific device 2 is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_2 . VENDOR_SPECIFIC_DEV2_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_2_VENDOR_SPECIFIC_DEV2_PRESENT  VTSS_BIT(15)

/** 
 * \brief
 * Indicates if the vendor specific device 1 is present
 *
 * \details 
 * 0: Vendor specific device 1 is not present in package
 * 1: Vendor specific device 1 is present in package
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_2 . VENDOR_SPECIFIC_DEV1_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_DEV_IN_PACKAGE_2_VENDOR_SPECIFIC_DEV1_PRESENT  VTSS_BIT(14)


/** 
 * \brief PMA/PMD Control 2
 *
 * \details
 * PMA/PMD Control 2
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_DEVICE_ID:PMA_PMD_CONTROL_2
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_CONTROL_2  VTSS_IOREG(0x01, 0, 0x0007)

/** 
 * \brief
 * Indicates the PMA type selected
 * WAN mode is enabled when 10GBASE-SW, 10GBASE-LW or 10GBASE-EW is
 * selected.
 *
 * \details 
 * 1111: 10BASE-T (not supported)
 * 1110: 100BASE-TX (not supported)
 * 1101: 1000BASE-KX
 * 1100: 1000BASE-T (not supported)
 * 1011: 10GBASE-KR
 * 1010: 10GBASE-KX4 (not supported)
 * 1001: 10GBASE-T (not supported)
 * 1000: 10GBASE-LRM
 * 0111: 10GBASE-SR
 * 0110: 10GBASE-LR
 * 0101: 10GBASE-ER
 * 0100: 10GBASE-LX-4
 * 0011: 10GBASE-SW
 * 0010: 10GBASE-LW
 * 0001: 10GBASE-EW
 * 0000: Reserved
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_CONTROL_2 . VENDOR_SPECIFIC_DEV2_PRESENT_CTRL
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_CONTROL_2_VENDOR_SPECIFIC_DEV2_PRESENT_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_CONTROL_2_VENDOR_SPECIFIC_DEV2_PRESENT_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_DEVICE_ID_PMA_PMD_CONTROL_2_VENDOR_SPECIFIC_DEV2_PRESENT_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMA_PMD_STATUS
 *
 * Device 1 IEEE MDIO Configuration and Status Register set
 */


/** 
 * \brief PMA/PMD Status 2
 *
 * \details
 * PMA/PMD Status 2
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_PMD_STATUS:PMA_PMD_STATUS_2
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2  VTSS_IOREG(0x01, 0, 0x0008)

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
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . DEVICE_PRESENT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_DEVICE_PRESENT(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_DEVICE_PRESENT     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_DEVICE_PRESENT(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * PMA/PMD transmit path fault detection ability
 *
 * \details 
 * 0: PMA/PMD does not have the ability to detect a fault condition on the
 * transmit path
 * 1: PMA/PMD has the ability to detect a fault condition on the transmit
 * path
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . TRANSMIT_FAULT_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_TRANSMIT_FAULT_ABILITY  VTSS_BIT(13)

/** 
 * \brief
 * PMA/PMD receive path fault detection ability
 *
 * \details 
 * 0: PMA/PMD does not have the ability to detect a fault condition on the
 * receive path
 * 1: PMA/PMD has the ability to detect a fault condition on the receive
 * path
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . RECEIVE_FAULT_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_RECEIVE_FAULT_ABILITY  VTSS_BIT(12)

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
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . TRANSMIT_FAULT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_TRANSMIT_FAULT  VTSS_BIT(11)

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
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . RECEIVE_FAULT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_RECEIVE_FAULT  VTSS_BIT(10)

/** 
 * \brief
 * Disable the PMA/PMD transmit path ability
 *
 * \details 
 * 0: PMD does not have the ability to disable the transmit path
 * 1: PMD has the ability to disable the transmit path
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . PMD_TRANSMIT_DISABLE_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_PMD_TRANSMIT_DISABLE_ABILITY  VTSS_BIT(8)

/** 
 * \brief
 * 10GBASE-SR ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-SR
 * 1: PMA/PMD is able to perform 10GBASE-SR
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_SR_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_SR_ABILITY  VTSS_BIT(7)

/** 
 * \brief
 * 10GBASE-LR ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-LR
 * 1: PMA/PMD is able to perform 10GBASE-LR
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_LR_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_LR_ABILITY  VTSS_BIT(6)

/** 
 * \brief
 * 10GBASE-ER ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-ER
 * 1: PMA/PMD is able to perform 10GBASE-ER
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_ER_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_ER_ABILITY  VTSS_BIT(5)

/** 
 * \brief
 * 10GBASE-LX4 ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-LX4
 * 1: PMA/PMD is able to perform 10GBASE-LX4
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_LX4_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_LX4_ABILITY  VTSS_BIT(4)

/** 
 * \brief
 * 10GBASE-SW ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-SW
 * 1: PMA/PMD is able to perform 10GBASE-SW
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_SW_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_SW_ABILITY  VTSS_BIT(3)

/** 
 * \brief
 * 10GBASE-LW ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-LW
 * 1: PMA/PMD is able to perform 10GBASE-LW
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_LW_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_LW_ABILITY  VTSS_BIT(2)

/** 
 * \brief
 * 10GBASE-EW ability
 *
 * \details 
 * 0: PMA/PMD is not able to perform 10GBASE-EW
 * 1: PMA/PMD is able to perform 10GBASE-EW
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . ETH_10GBASE_EW_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_ETH_10GBASE_EW_ABILITY  VTSS_BIT(1)

/** 
 * \brief
 * Ability to perform a loopback function
 *
 * \details 
 * 0: PMA does not have the ability to perform a loopback function
 * 1: PMA has the ability to perform a loopback function
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2 . PMA_LOOPBACK_ABILITY
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_STATUS_PMA_PMD_STATUS_2_PMA_LOOPBACK_ABILITY  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMD_CONTROL_AND_STATUS
 *
 * Device 1 IEEE MDIO Configuration and Status Register set
 */


/** 
 * \brief PMD Transmit Disable
 *
 * \details
 * PMD Transmit Disable
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMD_CONTROL_AND_STATUS:PMD_TRANSMIT_DISABLE
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE  VTSS_IOREG(0x01, 0, 0x0009)

/** 
 * \brief
 * Value always 0, writes ignored.
 *
 * \details 
 * 0: Normal operation
 * 1: Transmit disable
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE . PMD_TRANSMIT_DISABLE_3
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE_PMD_TRANSMIT_DISABLE_3  VTSS_BIT(4)

/** 
 * \brief
 * Value always 0, writes ignored
 *
 * \details 
 * 0: Normal operation
 * 1: Transmit disable
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE . PMD_TRANSMIT_DISABLE_2
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE_PMD_TRANSMIT_DISABLE_2  VTSS_BIT(3)

/** 
 * \brief
 * Value always 0, writes ignored.
 *
 * \details 
 * 0: Normal operation
 * 1: Transmit disable
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE . PMD_TRANSMIT_DISABLE_1
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE_PMD_TRANSMIT_DISABLE_1  VTSS_BIT(2)

/** 
 * \brief
 * Value always 0, writes ignored.
 *
 * \details 
 * 0: Normal operation
 * 1: Transmit disable
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE . PMD_TRANSMIT_DISABLE_0
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE_PMD_TRANSMIT_DISABLE_0  VTSS_BIT(1)

/** 
 * \brief
 * PMD Transmit Disable.  This register bit can be transmitted from a GPIO
 * pin to shut off an optics module's TX driver.  This TXEN signal
 * automatically disables the TX driver when the channel is in low power
 * mode.  The GPIO configuration controls whether the transmitted signal is
 * active high or active low.
 *
 * \details 
 * 0: Transmit enabled
 * 1: Transmit disabled
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE . GLOBAL_PMD_TRANSMIT_DISABLE
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_TRANSMIT_DISABLE_GLOBAL_PMD_TRANSMIT_DISABLE  VTSS_BIT(0)


/** 
 * \brief PMD Receive Signal Detect 
 *
 * \details
 * PMD Receive Signal Detect 
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMD_CONTROL_AND_STATUS:PMD_RECEIVE_SIGNAL_DETECT
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT  VTSS_IOREG(0x01, 0, 0x000a)

/** 
 * \brief
 * Do not support this function, value always 0
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT . PMD_RECEIVE_SIGNAL_DETECT_3
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT_PMD_RECEIVE_SIGNAL_DETECT_3  VTSS_BIT(4)

/** 
 * \brief
 * Do not support this function, value always 0
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT . PMD_RECEIVE_SIGNAL_DETECT_2
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT_PMD_RECEIVE_SIGNAL_DETECT_2  VTSS_BIT(3)

/** 
 * \brief
 * Do not support this function, value always 0
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT . PMD_RECEIVE_SIGNAL_DETECT_1
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT_PMD_RECEIVE_SIGNAL_DETECT_1  VTSS_BIT(2)

/** 
 * \brief
 * Do not support this function, value always 0
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT . PMD_RECEIVE_SIGNAL_DETECT_0
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT_PMD_RECEIVE_SIGNAL_DETECT_0  VTSS_BIT(1)

/** 
 * \brief
 * PMD receiver signal detect
 *
 * \details 
 * 0: Signal not detected by receiver
 * 1: Signal detected by receiver
 *
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT . GLOBAL_PMD_RECEIVE_SIGNAL_DETECT
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMD_CONTROL_AND_STATUS_PMD_RECEIVE_SIGNAL_DETECT_GLOBAL_PMD_RECEIVE_SIGNAL_DETECT  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:DEV1_IEEE_PMA_PMD_PACKAGE_ID
 *
 * Device 1 IEEE MDIO Configuration and Status Register set
 */


/** 
 * \brief PMA/PMD Package Identifier 1
 *
 * \details
 * PMA/PMD Package Identifier 1
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_PMD_PACKAGE_ID:PMA_PMD_PACKAGE_ID_1
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_1  VTSS_IOREG(0x01, 0, 0x001e)

/** 
 * \brief
 * PMA/PMD package identifier 1
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_1 . PMA_PMD_PACKAGE_ID_1
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_1_PMA_PMD_PACKAGE_ID_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PMA/PMD package identifier 2
 *
 * \details
 * PMA/PMD package identifier 2
 *
 * Register: \a VENICE_DEV1:DEV1_IEEE_PMA_PMD_PACKAGE_ID:PMA_PMD_PACKAGE_ID_2
 */
#define VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_2  VTSS_IOREG(0x01, 0, 0x001f)

/** 
 * \brief
 * PMA/PMD Package Identifier 2
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_2 . PMA_PMD_PACKAGE_ID_2
 */
#define  VTSS_F_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_DEV1_IEEE_PMA_PMD_PACKAGE_ID_PMA_PMD_PACKAGE_ID_2_PMA_PMD_PACKAGE_ID_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:KR_FEC_ABILITY
 *
 * KR FEC IEEE ABILITY REGISTER
 */


/** 
 * \brief KR FEC ability
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_ABILITY:KR_FEC_ABILITY
 */
#define VTSS_VENICE_DEV1_KR_FEC_ABILITY_KR_FEC_ABILITY  VTSS_IOREG(0x01, 0, 0x00aa)

/** 
 * \brief
 * FEC error reporting ability
 *
 * \details 
 * 
 * 0: This PHY device is not able to report FEC decoding errors to the PCS
 * layer.
 * 1: This PHY device is able to report FEC decoding errors to the PCS
 * layer.

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_ABILITY_KR_FEC_ABILITY . FEC_error_indication_ability
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_ABILITY_KR_FEC_ABILITY_FEC_error_indication_ability  VTSS_BIT(1)

/** 
 * \brief
 * FEC ability
 *
 * \details 
 * 
 * 0: This PHY device does not support FEC.
 * 1: This PHY device supports FEC.

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_ABILITY_KR_FEC_ABILITY . FEC_ability
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_ABILITY_KR_FEC_ABILITY_FEC_ability  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:KR_FEC_CONTROL_1
 *
 * KR FEC IEEE CONTROL REGISTER
 */


/** 
 * \brief KR FEC control 1
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_CONTROL_1:KR_FEC_CONTROL_1
 */
#define VTSS_VENICE_DEV1_KR_FEC_CONTROL_1_KR_FEC_CONTROL_1  VTSS_IOREG(0x01, 0, 0x00ab)

/** 
 * \details 
 * 
 * 0: Decoding errors have no effect on PCS sync bits
 * 1: Enable decoder to indicate errors to PCS sync bits

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_CONTROL_1_KR_FEC_CONTROL_1 . FEC_enable_error_indication
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_CONTROL_1_KR_FEC_CONTROL_1_FEC_enable_error_indication  VTSS_BIT(1)

/** 
 * \brief
 * FEC enable
 *
 * \details 
 * 
 * 0: Disable FEC
 * 1: Enable FEC

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_CONTROL_1_KR_FEC_CONTROL_1 . FEC_enable
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_CONTROL_1_KR_FEC_CONTROL_1_FEC_enable  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:KR_FEC_STATUS
 *
 * KR FEC IEEE STATUS REGISTER
 */


/** 
 * \brief KR FEC corrected lower
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_STATUS:KR_FEC_CORRECTED_LOWER
 */
#define VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_LOWER  VTSS_IOREG(0x01, 0, 0x00ac)

/** 
 * \brief
 * The FEC corrected block count is split across two registers,
 * KR_FEC_corrected_lower and KR_FEC_corrected_upper. 
 * KR_FEC_corrected_lower contains the least significant 16 bits of the
 * count.  KR_FEC_corrected_upper contains the most significant 16 bits of
 * the count.
 * Reading address KR_FEC_corrected_lower latches the 16 most significant
 * bits of the counter in KR_FEC_corrected_upper for future read out.  The
 * block count register is cleared when KR_FEC_corrected_lower is read.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_LOWER . FEC_CORRECTED_BLOCKS_LOWER
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_LOWER_FEC_CORRECTED_BLOCKS_LOWER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_LOWER_FEC_CORRECTED_BLOCKS_LOWER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_LOWER_FEC_CORRECTED_BLOCKS_LOWER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief KR FEC corrected upper
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_STATUS:KR_FEC_CORRECTED_UPPER
 */
#define VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_UPPER  VTSS_IOREG(0x01, 0, 0x00ad)

/** 
 * \brief
 * The FEC corrected block count is split across two registers,
 * KR_FEC_corrected_lower and KR_FEC_corrected_upper. 
 * KR_FEC_corrected_lower contains the least significant 16 bits of the
 * count.  KR_FEC_corrected_upper contains the most significant 16 bits of
 * the count.
 * Reading address KR_FEC_corrected_lower latches the 16 most significant
 * bits of the counter in KR_FEC_corrected_upper for future read out.  The
 * block count register is cleared when KR_FEC_corrected_lower is read.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_UPPER . FEC_CORRECTED_BLOCKS_UPPER
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_UPPER_FEC_CORRECTED_BLOCKS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_UPPER_FEC_CORRECTED_BLOCKS_UPPER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_CORRECTED_UPPER_FEC_CORRECTED_BLOCKS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief KR FEC uncorrected lower
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_STATUS:KR_FEC_UNCORRECTED_LOWER
 */
#define VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_LOWER  VTSS_IOREG(0x01, 0, 0x00ae)

/** 
 * \brief
 * The FEC uncorrectable block count is split across two registers,
 * KR_FEC_uncorrected_lower and KR_FEC_uncorrected_upper. 
 * KR_FEC_uncorrected_lower contains the least significant 16 bits of the
 * count.  KR_FEC_uncorrected_upper contains the most significant 16 bits
 * of the count.
 * Reading address KR_FEC_uncorrected_lower latches the 16 most significant
 * bits of the counter in KR_FEC_uncorrected_upper for future read out. 
 * The block count register is cleared when KR_FEC_uncorrected_lower is
 * read.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_LOWER . FEC_UNCORRECTED_BLOCKS_LOWER
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_LOWER_FEC_UNCORRECTED_BLOCKS_LOWER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_LOWER_FEC_UNCORRECTED_BLOCKS_LOWER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_LOWER_FEC_UNCORRECTED_BLOCKS_LOWER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief KR FEC uncorrected upper
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_STATUS:KR_FEC_UNCORRECTED_UPPER
 */
#define VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_UPPER  VTSS_IOREG(0x01, 0, 0x00af)

/** 
 * \brief
 * The FEC uncorrectable block count is split across two registers,
 * KR_FEC_uncorrected_lower and KR_FEC_uncorrected_upper. 
 * KR_FEC_uncorrected_lower contains the least significant 16 bits of the
 * count.  KR_FEC_uncorrected_upper contains the most significant 16 bits
 * of the count.
 * Reading address KR_FEC_uncorrected_lower latches the 16 most significant
 * bits of the counter in KR_FEC_uncorrected_upper for future read out. 
 * The block count register is cleared when KR_FEC_uncorrected_lower is
 * read.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_UPPER . FEC_UNCORRECTED_BLOCKS_UPPER
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_UPPER_FEC_UNCORRECTED_BLOCKS_UPPER(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_UPPER_FEC_UNCORRECTED_BLOCKS_UPPER     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_KR_FEC_STATUS_KR_FEC_UNCORRECTED_UPPER_FEC_UNCORRECTED_BLOCKS_UPPER(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:KR_FEC_CONTROL_2
 *
 * KR FEC Configuration and Status Vendor Register set
 */


/** 
 * \brief KR_FEC_Control_2
 *
 * \details
 * Register: \a VENICE_DEV1:KR_FEC_CONTROL_2:KR_FEC_Control_2
 */
#define VTSS_VENICE_DEV1_KR_FEC_CONTROL_2_KR_FEC_Control_2  VTSS_IOREG(0x01, 0, 0x8300)

/** 
 * \brief
 * FEC in frame lock indication.  This is a sticky bit that latches the low
 * state. The latch-low bit is cleared when the register is read.
 *
 * \details 
 * 
 * 0: FEC has not achieved lock
 * 1: FEC has achieved lock

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_CONTROL_2_KR_FEC_Control_2 . fec_inframe
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_CONTROL_2_KR_FEC_Control_2_fec_inframe  VTSS_BIT(1)

/** 
 * \brief
 * FEC counters reset
 *
 * \details 
 * 
 * 0: no effect
 * 1: reset FEC counters

 *
 * Field: VTSS_VENICE_DEV1_KR_FEC_CONTROL_2_KR_FEC_Control_2 . fec_rstmon
 */
#define  VTSS_F_VENICE_DEV1_KR_FEC_CONTROL_2_KR_FEC_Control_2_fec_rstmon  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:RX_ALARM_Control_Register
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a VENICE_DEV1:RX_ALARM_Control_Register:RX_ALARM_Control_Register
 */
#define VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register  VTSS_IOREG(0x01, 0, 0x9000)

/** 
 * \brief
 * Vendor specific
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . Vendor_Specific
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific  VTSS_BIT(10)

/** 
 * \brief
 * WIS Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . WIS_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_WIS_Local_Fault_Enable  VTSS_BIT(9)

/** 
 * \brief
 * Vendor Specific
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . Vendor_Specific_idx2
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx2(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx2     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx2(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * PMA/PMD Receiver Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . PMA_PMD_Receiver_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_PMA_PMD_Receiver_Local_Fault_Enable  VTSS_BIT(4)

/** 
 * \brief
 * PCS Receive Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . PCS_Receive_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_PCS_Receive_Local_Fault_Enable  VTSS_BIT(3)

/** 
 * \brief
 * Vendor Specific
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . Vendor_Specific_idx3
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx3(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx3     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_Vendor_Specific_idx3(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * PHY XS Receive Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register . PHY_XS_Receive_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Control_Register_RX_ALARM_Control_Register_PHY_XS_Receive_Local_Fault_Enable  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:TX_ALARM_Control_Register
 *
 * Not documented
 */


/** 
 * \brief TX_ALARM Control Register
 *
 * \details
 * Register: \a VENICE_DEV1:TX_ALARM_Control_Register:TX_ALARM_Control_Register
 */
#define VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register  VTSS_IOREG(0x01, 0, 0x9001)

/** 
 * \brief
 * Vendor Specific
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register . Vendor_Specific
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * PMA/PMD Transmitter Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register . PMA_PMD_Transmitter_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_PMA_PMD_Transmitter_Local_Fault_Enable  VTSS_BIT(4)

/** 
 * \brief
 * PCS Transmit Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register . PCS_Transmit_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_PCS_Transmit_Local_Fault_Enable  VTSS_BIT(3)

/** 
 * \brief
 * Vendor Specific
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register . Vendor_Specific_idx2
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific_idx2(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific_idx2     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_Vendor_Specific_idx2(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * PHY XS Transmit Local Fault Enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register . PHY_XS_Transmit_Local_Fault_Enable
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Control_Register_TX_ALARM_Control_Register_PHY_XS_Transmit_Local_Fault_Enable  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:RX_ALARM_Status_Register
 *
 * Not documented
 */


/** 
 * \brief RX_ALARM Status Register
 *
 * \details
 * Register: \a VENICE_DEV1:RX_ALARM_Status_Register:RX_ALARM_Status_Register
 */
#define VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register  VTSS_IOREG(0x01, 0, 0x9003)

/** 
 * \brief
 * For future use.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . Vendor_Specific
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific  VTSS_BIT(10)

/** 
 * \brief
 * WIS Local Fault
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No WIS Local Fault
 * 1: WIS Local Fault
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . WIS_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_WIS_Local_Fault  VTSS_BIT(9)

/** 
 * \brief
 * For future use. 
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . Vendor_Specific_idx2
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx2(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx2     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx2(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * PMA/PMD Receiver Local Fault
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PMA/PMD Receiver Local Fault
 * 1: PMA/PMD Receiver Local Fault
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . PMA_PMD_Receiver_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_PMA_PMD_Receiver_Local_Fault  VTSS_BIT(4)

/** 
 * \brief
 * PCS Receive Local Fault
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PCS Receive Local Fault
 * 1: PCS Receive Local Fault
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . PCS_Receive_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_PCS_Receive_Local_Fault  VTSS_BIT(3)

/** 
 * \brief
 * For future use. 
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . Vendor_Specific_idx3
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx3(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx3     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_Vendor_Specific_idx3(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * PHY XS Receive Local Fault
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PHY XS Receive Local Fault
 * 1: PHY XS Receive Local Fault
 *
 * Field: VTSS_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register . PHY_XS_Receive_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_RX_ALARM_Status_Register_RX_ALARM_Status_Register_PHY_XS_Receive_Local_Fault  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:TX_ALARM_Status_Register
 *
 * Not documented
 */


/** 
 * \brief TX_ALARM Status Register
 *
 * \details
 * Register: \a VENICE_DEV1:TX_ALARM_Status_Register:TX_ALARM_Status_Register
 */
#define VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register  VTSS_IOREG(0x01, 0, 0x9004)

/** 
 * \brief
 * For future use.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register . Vendor_Specific
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * PMA/PMD Transmitter Local Fault Enable
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PMA/PMD Transmitter Local Fault
 * 1: PMA/PMD Transmitter Local Fault
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register . PMA_PMD_Transmitter_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_PMA_PMD_Transmitter_Local_Fault  VTSS_BIT(4)

/** 
 * \brief
 * PCS Transmit Local Fault Enable
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PCS Transmit Local Fault
 * 1: PCS Transmit Local Fault
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register . PCS_Transmit_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_PCS_Transmit_Local_Fault  VTSS_BIT(3)

/** 
 * \brief
 * For future use.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register . Vendor_Specific_idx2
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific_idx2(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific_idx2     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_Vendor_Specific_idx2(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * PHY XS Transmit Local Fault Enable
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No PHY XS Transmit Local Fault
 * 1: PHY XS Transmit Local Fault
 *
 * Field: VTSS_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register . PHY_XS_Transmit_Local_Fault
 */
#define  VTSS_F_VENICE_DEV1_TX_ALARM_Status_Register_TX_ALARM_Status_Register_PHY_XS_Transmit_Local_Fault  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:CLOCK_OUTPUT_CONTROL
 *
 * Control Signal Clock Output
 */


/** 
 * \brief Interface's RXCKOUT configuration register
 *
 * \details
 * Configuration register for channel's RXCKOUT
 *
 * Register: \a VENICE_DEV1:CLOCK_OUTPUT_CONTROL:RXCK_CFG
 */
#define VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG  VTSS_IOREG(0x01, 0, 0xa000)

/** 
 * \brief
 * Mask RXPLLF_LOCK from affecting the RXCK64 auto-squelch at the channel's
 * RXCKOUT pin
 *
 * \details 
 * 0: RXPLLF_LOCK does not affect RXCK64 auto-squelch
 * 1: RXPLLF_LOCK affects RXCK64 auto-squelch
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCK_RXPLLF_LOCK_MASK
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCK_RXPLLF_LOCK_MASK  VTSS_BIT(7)

/** 
 * \brief
 * Mask PCS_FAULT from affecting the RXCK64 auto-squelch at the channel's
 * RXCKOUT pin
 *
 * \details 
 * 0: PCS_FAULT does not affect RXCK64 auto-squelch
 * 1: PCS_FAULT affects RXCK64 auto-squelch
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCK_PCS_FAULT_MASK
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCK_PCS_FAULT_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Mask LOPC from affecting the RXCK64 auto-squelch at the channel's
 * RXCKOUT pin
 *
 * \details 
 * 0: LOPC does not affect RXCK64 auto-squelch
 * 1: LOPC affects RXCK64 auto-squelch
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCK_LOPC_MASK
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCK_LOPC_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Mask IB_SIGNAL_DETECT from affecting the RXCK64 auto-squelch at the
 * channel's RXCKOUT pin
 *
 * \details 
 * 0: IB_SIGNAL_DETECT does not affect RXCK64 auto-squelch
 * 1: IB_SIGNAL_DETECT affects RXCK64 auto-squelch
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCK_IB_SIGNAL_DETECT_MASK
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCK_IB_SIGNAL_DETECT_MASK  VTSS_BIT(4)

/** 
 * \brief
 * Enable the channel's RXCKOUT pin
 * RXCKOUT is also affected by TXCKOUT_ENABLE bit and
 * OB_TST_OUT_CFG.OB_CTRL[10]
 * To enable the RXCKOUT pin either RXCKOUT_ENABLE or TXCKOUT_ENABLE must
 * be set to 1 and OB_CTRL[10] must be set to 1
 *
 * \details 
 * 0 = RXCKOUT disable
 * 1 = RXCKOUT enable 
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCKOUT_ENABLE
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCKOUT_ENABLE  VTSS_BIT(3)

/** 
 * \brief
 * Configure the channel's RXCKOUT pin
 *
 * \details 
 * 000 = line side rx recovered clock (LAN: 322.26 Mhz, WAN: 311.04 Mhz,
 * 1G: 125 MHz)
 * 001 = line side rx recovered clock div by 2	(LAN: 161.13 MHz, WAN:
 * 155.52 MHz, 1G: 62.5 Mhz)
 * 010 = line side tx clock (LAN: 322.26 Mhz, WAN: 311.04 Mhz, 1G: 125 MHz)
 * 011 = line side tx clock div by 2 (LAN: 161.13 MHz, WAN: 155.52 MHz, 1G:
 * 62.5 Mhz)
 * 100 = line side pll test clock
 * 101 = factory test
 * 110 = host side rx recovered clock (LAN/WAN: 312.5 MHz, 78.125 MHz or
 * 62.5 MHz, 1G: 125 MHz, 31.25 MHz or 25 MHz)
 * 111 = host side pll test clock
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG . RXCKOUT_SEL
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCKOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCKOUT_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_RXCK_CFG_RXCKOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Interface's TXCKOUT configuration register
 *
 * \details
 * Configuration register for channel's TXCKOUT
 *
 * Register: \a VENICE_DEV1:CLOCK_OUTPUT_CONTROL:TXCK_CFG
 */
#define VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG  VTSS_IOREG(0x01, 0, 0xa001)

/** 
 * \brief
 * Enable the channel's TXCKOUT pin
 * TXCKOUT is also affected by RXCKOUT_ENABLE bit and
 * OB_TST_OUT_CFG.OB_CTRL[10]
 * To enable the TXCKOUT pin either TXCKOUT_ENABLE or RXCKOUT_ENABLE must
 * be set to 1 and OB_CTRL[10] must be set to 1
 *
 * \details 
 * 0 = TXCKOUT disable
 * 1 = TXCKOUT enable
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG . TXCKOUT_ENABLE
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG_TXCKOUT_ENABLE  VTSS_BIT(3)

/** 
 * \brief
 * Configure the channel's TXCKOUT pin
 *
 * \details 
 * 000 = line side tx clock (LAN: 322.26 Mhz, WAN: 311.04 Mhz, 1G: 125 MHz)
 * 001 = line side tx clock div by 2  (LAN: 161.13 MHz, WAN: 155.52 MHz,
 * 1G: 62.5 Mhz)
 * 010 = line side rx recovered clock (LAN: 322.26 Mhz, WAN: 311.04 Mhz,
 * 1G: 125 MHz)
 * 011 = line side rx recovered clock div by 2 (LAN: 161.13 MHz, WAN:
 * 155.52 MHz, 1G: 62.5 Mhz)
 * 100 = line side pll test clock
 * 101 = factory test
 * 110 = host side rx recovered clock (LAN/WAN: 312.5 MHz, 78.125 MHz or
 * 62.5 MHz, 1G: 125 MHz, 31.25 MHz or 25 MHz)
 * 111 = host side pll test clock
 *
 * Field: VTSS_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG . TXCKOUT_SEL
 */
#define  VTSS_F_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG_TXCKOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG_TXCKOUT_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV1_CLOCK_OUTPUT_CONTROL_TXCK_CFG_TXCKOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a VENICE_DEV1:DATAPATH_CONTROL
 *
 * Control Signal for Data Path
 */


/** 
 * \brief 10G or 1G mode in datapath
 *
 * \details
 * Determine the datapath mode
 *
 * Register: \a VENICE_DEV1:DATAPATH_CONTROL:DATAPATH_MODE
 */
#define VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE  VTSS_IOREG(0x01, 0, 0xa002)

/** 
 * \brief
 * Configure Lineside Serdes to 10G WAN mode with the ROM Engine. This
 * register is self-clearing.
 *
 * \details 
 * 0 = Do Nothing
 * 1 = Configure Lineside Serdes to 10G WAN mode with the ROM Engine
 *
 * Field: VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE . USR_10G_WAN
 */
#define  VTSS_F_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE_USR_10G_WAN  VTSS_BIT(6)

/** 
 * \brief
 * Configure Lineside Serdes to 10G LAN mode with the ROM Engine.This
 * register is self-clearing.
 *
 * \details 
 * 0 = Do Nothing
 * 1 = Configure Lineside Serdes to 10G LAN mode with the ROM Engine
 *
 * Field: VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE . USR_10G_LAN
 */
#define  VTSS_F_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE_USR_10G_LAN  VTSS_BIT(5)

/** 
 * \brief
 * Configure Lineside Serdes to 1G mode with the ROM Engine.This register
 * is self-clearing.
 *
 * \details 
 * 0 = Do Nothing
 * 1 = Configure Lineside Serdes to 1G mode with the ROM Engine
 *
 * Field: VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE . USR_1G
 */
#define  VTSS_F_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE_USR_1G  VTSS_BIT(4)

/** 
 * \brief
 * In 1G mode of operation, select the lane used for data on the client
 * side interface
 *
 * \details 
 * 0 = lane 0 is used for 1G data
 * 1 = lane 3 is used for 1G data
 *
 * Field: VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE . SEL_1G_LANE_3
 */
#define  VTSS_F_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE_SEL_1G_LANE_3  VTSS_BIT(1)

/** 
 * \brief
 * Configure datapath and host side serdes into 1G mode
 *
 * \details 
 * 0 = 10G LAN or WAN
 * 1 = 1G 
 *
 * Field: VTSS_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE . ETH_1G_ENA
 */
#define  VTSS_F_VENICE_DEV1_DATAPATH_CONTROL_DATAPATH_MODE_ETH_1G_ENA  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:LOOPBACK_CONTROL
 *
 * Control Signal for Loopback
 */


/** 
 * \brief Datapath Loopback Control
 *
 * \details
 * Datapath Loopback Control
 *
 * Register: \a VENICE_DEV1:LOOPBACK_CONTROL:PMA_LOOPBACK_CONTROL
 */
#define VTSS_VENICE_DEV1_LOOPBACK_CONTROL_PMA_LOOPBACK_CONTROL  VTSS_IOREG(0x01, 0, 0xa003)

/** 
 * \brief
 * Loopback L3 Enable
 *
 * \details 
 * 0 = Normal Operation
 * 1 = Enable L3 Loopback 
 *
 * Field: VTSS_VENICE_DEV1_LOOPBACK_CONTROL_PMA_LOOPBACK_CONTROL . L3_CONTROL
 */
#define  VTSS_F_VENICE_DEV1_LOOPBACK_CONTROL_PMA_LOOPBACK_CONTROL_L3_CONTROL  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:MAC_ENABLE
 *
 * Enable MAC in the datapath
 */


/** 
 * \brief Enable MAC in the datapath
 *
 * \details
 * Enable MAC in the datapath
 *
 * Register: \a VENICE_DEV1:MAC_ENABLE:MAC_ENA
 */
#define VTSS_VENICE_DEV1_MAC_ENABLE_MAC_ENA  VTSS_IOREG(0x01, 0, 0xa006)

/** 
 * \brief
 * Clock enable for the MACsec logic.  Deasserting this bit when MACsec is
 * disabled and MACs are enabled will save power.  Note:  the CLK_EN
 * register bits within the MACsec register space must be asserted along
 * with this bit when the MACsec logic is to be used.  This bit usage
 * applies to the VSC8490 and VSC8491 products only.
 *
 * \details 
 * 0 = MACsec clock is squelched
 * 1 = MACsec clock is enabled
 *
 * Field: VTSS_VENICE_DEV1_MAC_ENABLE_MAC_ENA . MACSEC_CLK_ENA
 */
#define  VTSS_F_VENICE_DEV1_MAC_ENABLE_MAC_ENA_MACSEC_CLK_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable MAC in the datapath
 *
 * \details 
 * 0 = MAC is not in the datapath
 * 1 = MAC is in the datapath
 *
 * Field: VTSS_VENICE_DEV1_MAC_ENABLE_MAC_ENA . MAC_ENA
 */
#define  VTSS_F_VENICE_DEV1_MAC_ENABLE_MAC_ENA_MAC_ENA  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:OB_TST_OUT_CFG
 *
 * Configuration Registers for Clock Output Buffer
 */


/** 
 * \brief Clock Output Buffer Bias Control
 *
 * \details
 * Clock Output Buffer Bias Control
 *
 * Register: \a VENICE_DEV1:OB_TST_OUT_CFG:OB_BIAS_CTRL
 */
#define VTSS_VENICE_DEV1_OB_TST_OUT_CFG_OB_BIAS_CTRL  VTSS_IOREG(0x01, 0, 0xa00c)

/** 
 * \brief
 * Clock Output Buffer Bias Control
 * [2:0] = Sets the class AB bias current in the common mode control
 * circuit. 0.5 mA is expected to give sufficient performance and is
 * default. Other settings are for debug. Current range is 0 to 1.75 mA in
 * 0.25mA steps. Default is set to 0 (disable)
 * [3] = enable internal CML to CMOS converter for input to test output
 * path
 * [5:4] = reserved
 * [7:6] = slope/slew rate control, 0: 45ps, 1: 85ps, 2: 105ps, 3: 115ps
 * rise/fall time (all values are typical)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_OB_TST_OUT_CFG_OB_BIAS_CTRL . OB_BIAS_CTRL
 */
#define  VTSS_F_VENICE_DEV1_OB_TST_OUT_CFG_OB_BIAS_CTRL_OB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_OB_TST_OUT_CFG_OB_BIAS_CTRL_OB_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_OB_TST_OUT_CFG_OB_BIAS_CTRL_OB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Clock Output Buffer Control Registers
 *
 * \details
 * Clock Output Buffer Control Registers
 *
 * Register: \a VENICE_DEV1:OB_TST_OUT_CFG:OB_CTRL
 */
#define VTSS_VENICE_DEV1_OB_TST_OUT_CFG_OB_CTRL  VTSS_IOREG(0x01, 0, 0xa00d)

/** 
 * \brief
 * Clock Output Buffer Control Registers
 * [3:0] = value for resistor calibration (RCOMP), 15: lowest value 0:
 * highest value
 * [7:4] = Adjustment for Common Mode Voltage, 0: off --> results in a
 * value around 500mV, 1: 440mV, 2: 480mV, 3: 460mV, 4: 530mV, 6: 500mV, 8:
 * 570mV, 12: 550mV
 * [8] =  disable VCM control, 1: disable, 0: enable
 * [9] = enable VREG measure, 1: enable, 0: disable
 * [10] = enable output buffer, 1: enable, 0: disable (powerdown)
 * [11] = reserved
 * [15:12] = select output level, 400mVppd (0) to 1100mVppd (15) in 50mVppd
 * steps
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_OB_TST_OUT_CFG_OB_CTRL . OB_CTRL
 */
#define  VTSS_F_VENICE_DEV1_OB_TST_OUT_CFG_OB_CTRL_OB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_OB_TST_OUT_CFG_OB_CTRL_OB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_OB_TST_OUT_CFG_OB_CTRL_OB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:Vendor_Specific_PMA_Control_2
 *
 * Not documented
 */


/** 
 * \brief Vendor Specific PMA Control 2
 *
 * \details
 * Register: \a VENICE_DEV1:Vendor_Specific_PMA_Control_2:Vendor_Specific_PMA_Control_2
 */
#define VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2  VTSS_IOREG(0x01, 0, 0xa100)

/** 
 * \brief
 * WIS_INTB active edge
 *
 * \details 
 * 0: WIS_INTB is active low
 * 1: WIS_INTB is active high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . wis_intb_activeh
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_wis_intb_activeh  VTSS_BIT(15)

/** 
 * \brief
 * WIS_INTA active edge
 *
 * \details 
 * 0: WIS_INTA is active low
 * 1: WIS_INTA is active high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . wis_inta_activeh
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_wis_inta_activeh  VTSS_BIT(14)

/** 
 * \brief
 * LOS circuitry is driven by a signal detection status signal in the
 * line-side input buffer.  The signal detection alarm driving the LOS
 * curcuitry can be squelched with this register bit.
 *
 * \details 
 * LOS detection is
 * 0: Allowed
 * 1: Suppressed
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . Suppress_LOS_detection
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_Suppress_LOS_detection  VTSS_BIT(10)

/** 
 * \brief
 * LOL circuitry is driven by a status signal in the line-side CRU.  The
 * status signal driving the LOL curcuitry can be squelched with this
 * register bit.
 *
 * \details 
 * LOL detection is
 * 0: Allowed
 * 1: Suppressed
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . Suppress_LOL_detection
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_Suppress_LOL_detection  VTSS_BIT(9)

/** 
 * \brief
 * TX data activity LED blink time
 *
 * \details 
 * 0: 50ms interval
 * 1: 100ms interval
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . TX_LED_BLINK_TIME
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_BLINK_TIME  VTSS_BIT(8)

/** 
 * \brief
 * RX data activity LED blink time
 *
 * \details 
 * 0: 50ms interval
 * 1: 100ms interval
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . RX_LED_BLINK_TIME
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_BLINK_TIME  VTSS_BIT(7)

/** 
 * \brief
 * Tx LED mode control
 *
 * \details 
 * 00:	Display Tx link status
 * 01:	Reserved
 * 10:	Display combination of Tx link (host Rx Link) and Tx data activity
 * status
 * 11:	Display combination of Tx link (host Rx Link) and Tx+Rx data
 * activity status
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . TX_LED_MODE
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Rx LED mode control
 *
 * \details 
 * 00:	Display Rx link status
 * 01:	Reserved
 * 10:	Display combination of Rx link and Rx data activity status
 * 11:	Display combination of Rx link and Rx+Tx data activity status
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . RX_LED_MODE
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_MODE(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_MODE     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * System loopback data override
 *
 * \details 
 * 0: Data sent out XFI output matches default.
 * 1: Use 'PMA system loopback data select' to select XFI ouput data.
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . Override_system_loopback_data
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_Override_system_loopback_data  VTSS_BIT(2)

/** 
 * \brief
 * When Override system loopback data (bit 2) is set and the data channel
 * is in 10G mode, the data transmitted from TX PMA is determined by these
 * register bits.
 *
 * \details 
 * 00:	repeating 0x00FF pattern
 * 01: continuously send 0's
 * 10: continuously send 1's
 * 11: data from TX WIS block
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2 . PMA_system_loopback_data_select
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_PMA_system_loopback_data_select(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_PMA_system_loopback_data_select     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV1_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_PMA_system_loopback_data_select(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_DEV1:Vendor_Specific_PMA_Status_2
 *
 * Not documented
 */


/** 
 * \brief Vendor Specific PMA Status 2
 *
 * \details
 * Register: \a VENICE_DEV1:Vendor_Specific_PMA_Status_2:Vendor_Specific_PMA_Status_2
 */
#define VTSS_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2  VTSS_IOREG(0x01, 0, 0xa101)

/** 
 * \brief
 * Indicates if the device is in WAN mode
 * WAN mode is enable when
 * WIS_CTRL2.WAN_MODE = 1 OR 
 * PCS_Control_2.Select_WAN_mode_or_10GBASE_R = 2 OR 
 * PMA_PMD_CONTROL_2.VENDOR_SPECIFIC_DEV2_PRESENT_CTRL = 1 OR 
 * PMA_PMD_CONTROL_2.VENDOR_SPECIFIC_DEV2_PRESENT_CTRL = 2 OR 
 * PMA_PMD_CONTROL_2.VENDOR_SPECIFIC_DEV2_PRESENT_CTRL = 3

 *
 * \details 
 * 0: Not in Wan Mode
 * 1: WAN Mode
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2 . WAN_ENABLED_status
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2_WAN_ENABLED_status  VTSS_BIT(3)

/** 
 * \brief
 * WIS_INTA pin status
 *
 * \details 
 * 0: WIS_INTA pin is low
 * 1: WIS_INTA pin is high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2 . WIS_INTA_pin_status
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2_WIS_INTA_pin_status  VTSS_BIT(2)

/** 
 * \brief
 * WIS_INTB pin status
 *
 * \details 
 * 0: WIS_INTB pin is low
 * 1: WIS_INTB pin is high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2 . WIS_INTB_pin_status
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2_WIS_INTB_pin_status  VTSS_BIT(1)

/** 
 * \brief
 * PMTICK pin status
 *
 * \details 
 * 0: PMTICK pin is low
 * 1: PMTICK pin is high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2 . PMTICK_pin_status
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_PMA_Status_2_Vendor_Specific_PMA_Status_2_PMTICK_pin_status  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:APC_SIGDET_FILT_GOOD_CNT_HI
 *
 * Not documented
 */


/** 
 * \brief APC signal_detect filter good count (high)
 *
 * \details
 * Register: \a VENICE_DEV1:APC_SIGDET_FILT_GOOD_CNT_HI:APC_SIGDET_FILT_GOOD_CNT_HI
 */
#define VTSS_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SIGDET_FILT_GOOD_CNT_HI  VTSS_IOREG(0x01, 0, 0xa105)

/** 
 * \brief
 * APC signal_detect filter count.  The status signals contributing to the
 * APC's signal_detect must all persist in a detected signal state for the
 * duration defined in this good count register before signaling the APC a
 * signal has been detected.
 *
 * \details 
 * In 10Gbps operation (LAN and WAN), the counter's clock frequency is the
 * 10G rate divided by 64.  In 1Gbps operation, the counter's clock
 * frequency is the 1G rate divided by 10.
 * Setting either APC_SIGDET_FILT_GOOD_CNT or APC_SIGDET_FILT_BAD_CNT to a
 * value less than 2 disables the filter.
 *
 * Field: VTSS_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SIGDET_FILT_GOOD_CNT_HI . APC_SDET_FILT_GOOD_CNT_HI
 */
#define  VTSS_F_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SDET_FILT_GOOD_CNT_HI(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SDET_FILT_GOOD_CNT_HI     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SIGDET_FILT_GOOD_CNT_HI_APC_SDET_FILT_GOOD_CNT_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_DEV1:APC_SIGDET_FILT_GOOD_CNT_LO
 *
 * Not documented
 */


/** 
 * \brief APC signal_detect filter good count (low)
 *
 * \details
 * Register: \a VENICE_DEV1:APC_SIGDET_FILT_GOOD_CNT_LO:APC_SIGDET_FILT_GOOD_CNT_LO
 */
#define VTSS_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SIGDET_FILT_GOOD_CNT_LO  VTSS_IOREG(0x01, 0, 0xa106)

/** 
 * \brief
 * APC signal_detect filter count.  The status signals contributing to the
 * APC's signal_detect must all persist in a detected signal state for the
 * duration defined in this good count register before signaling the APC a
 * signal has been detected.
 *
 * \details 
 * In 10Gbps operation (LAN and WAN), the counter's clock frequency is the
 * 10G rate divided by 64.  In 1Gbps operation, the counter's clock
 * frequency is the 1G rate divided by 10.
 * Setting either APC_SIGDET_FILT_GOOD_CNT or APC_SIGDET_FILT_BAD_CNT to a
 * value less than 2 disables the filter.
 *
 * Field: VTSS_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SIGDET_FILT_GOOD_CNT_LO . APC_SDET_FILT_GOOD_CNT_LO
 */
#define  VTSS_F_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SDET_FILT_GOOD_CNT_LO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SDET_FILT_GOOD_CNT_LO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SIGDET_FILT_GOOD_CNT_LO_APC_SDET_FILT_GOOD_CNT_LO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:APC_SIGDET_FILT_BAD_CNT_HI
 *
 * Not documented
 */


/** 
 * \brief APC signal_detect filter bad count (high)
 *
 * \details
 * Register: \a VENICE_DEV1:APC_SIGDET_FILT_BAD_CNT_HI:APC_SIGDET_FILT_BAD_CNT_HI
 */
#define VTSS_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_HI_APC_SIGDET_FILT_BAD_CNT_HI  VTSS_IOREG(0x01, 0, 0xa107)

/** 
 * \brief
 * APC signal_detect filter count.  The APC is informed the signal has been
 * lost after the combined result of signals contributing to signal_detect
 * persist in a lost signal state for the duration defined in this bad
 * count register.
 *
 * \details 
 * In 10Gbps operation (LAN and WAN), the counter's clock frequency is the
 * 10G rate divided by 64.  In 1Gbps operation, the counter's clock
 * frequency is the 1G rate divided by 10.
 * Setting either APC_SIGDET_FILT_GOOD_CNT or APC_SIGDET_FILT_BAD_CNT to a
 * value less than 2 disables the filter.
 *
 * Field: VTSS_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_HI_APC_SIGDET_FILT_BAD_CNT_HI . APC_SDET_FILT_BAD_CNT_HI
 */
#define  VTSS_F_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_HI_APC_SIGDET_FILT_BAD_CNT_HI_APC_SDET_FILT_BAD_CNT_HI(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_HI_APC_SIGDET_FILT_BAD_CNT_HI_APC_SDET_FILT_BAD_CNT_HI     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_HI_APC_SIGDET_FILT_BAD_CNT_HI_APC_SDET_FILT_BAD_CNT_HI(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a VENICE_DEV1:APC_SIGDET_FILT_BAD_CNT_LO
 *
 * Not documented
 */


/** 
 * \brief APC signal_detect filter bad count (low)
 *
 * \details
 * Register: \a VENICE_DEV1:APC_SIGDET_FILT_BAD_CNT_LO:APC_SIGDET_FILT_BAD_CNT_LO
 */
#define VTSS_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_LO_APC_SIGDET_FILT_BAD_CNT_LO  VTSS_IOREG(0x01, 0, 0xa108)

/** 
 * \brief
 * APC signal_detect filter count.  The APC is informed the signal has been
 * lost after the combined result of signals contributing to signal_detect
 * persist in a lost signal state for the duration defined in this bad
 * count register.
 *
 * \details 
 * In 10Gbps operation (LAN and WAN), the counter's clock frequency is the
 * 10G rate divided by 64.  In 1Gbps operation, the counter's clock
 * frequency is the 1G rate divided by 10.
 * Setting either APC_SIGDET_FILT_GOOD_CNT or APC_SIGDET_FILT_BAD_CNT to a
 * value less than 2 disables the filter.
 *
 * Field: VTSS_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_LO_APC_SIGDET_FILT_BAD_CNT_LO . APC_SDET_FILT_BAD_CNT_LO
 */
#define  VTSS_F_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_LO_APC_SIGDET_FILT_BAD_CNT_LO_APC_SDET_FILT_BAD_CNT_LO(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_LO_APC_SIGDET_FILT_BAD_CNT_LO_APC_SDET_FILT_BAD_CNT_LO     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_APC_SIGDET_FILT_BAD_CNT_LO_APC_SIGDET_FILT_BAD_CNT_LO_APC_SDET_FILT_BAD_CNT_LO(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:Vendor_Specific_LOPC_Status
 *
 * Not documented
 */


/** 
 * \brief Vendor Specific LOPC Status
 *
 * \details
 * Register: \a VENICE_DEV1:Vendor_Specific_LOPC_Status:Vendor_Specific_LOPC_Status
 */
#define VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status  VTSS_IOREG(0x01, 0, 0xa200)

/** 
 * \brief
 * Present state of the LOPC pin which taking into account the lopc logic
 * inversion register bit
 * (Vendor_Specific_LOPC_Control.LOPC_state_inversion_select)
 *
 * \details 
 * 0: LOPC pin is low when
 * Vendor_Specific_LOPC_Control.LOPC_state_inversion_select=0, LOPC is high
 * when Vendor_Specific_LOPC_Control.LOPC_state_inversion_select=1
 * 1: LOPC pin is high when
 * Vendor_Specific_LOPC_Control.LOPC_state_inversion_select=0, LOPC is low
 * when Vendor_Specific_LOPC_Control.LOPC_state_inversion_select=1
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status . Present_state_of_the_LOPC_pin_with_reginv
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status_Present_state_of_the_LOPC_pin_with_reginv  VTSS_BIT(2)

/** 
 * \brief
 * Present state of the LOPC pin which does not take into account the lopc
 * logic inversion register bit
 * (Vendor_Specific_LOPC_Control.LOPC_state_inversion_select)
 *
 * \details 
 * 0: LOPC pin is low
 * 1: LOPC pin is high
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status . Present_state_of_the_LOPC_pin_without_reginv
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status_Present_state_of_the_LOPC_pin_without_reginv  VTSS_BIT(1)

/** 
 * \brief
 * LOPC interupt pending status.  The latch-high bit is cleared when the
 * register is read.
 *
 * \details 
 * 0: An interrupt event has not occurred since the last time this bit was
 * read
 * 1: An interrupt event determined by lopc_intr_mode has occurred
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status . Interrupt_pending_bit
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_LOPC_Status_Vendor_Specific_LOPC_Status_Interrupt_pending_bit  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:Vendor_Specific_LOPC_Control
 *
 * Not documented
 */


/** 
 * \brief Vendor Specific LOPC Control
 *
 * \details
 * Register: \a VENICE_DEV1:Vendor_Specific_LOPC_Control:Vendor_Specific_LOPC_Control
 */
#define VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control  VTSS_IOREG(0x01, 0, 0xa201)

/** 
 * \brief
 * LOPC pin polarity
 *
 * \details 
 * 0: The part is in a LOPC alarm state when the LOPC pin is logic low.
 * 1: The part is in a LOPC alarm state when the LOPC pin is logic high.
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control . LOPC_state_inversion_select
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control_LOPC_state_inversion_select  VTSS_BIT(2)

/** 
 * \brief
 * This bit group determines how the LOPC interrupt pending register bit in
 * Vendor_Specific_LOPC_Status.Interrupt_pending_bit is asserted
 *
 * \details 
 * 00: interrupt generation is disable
 * 01: lopc_intr_pend is set on a rising edge of the LOPC pin, regardless
 * of the Vendor_Specific_LOPC_Control.LOPC_state_inversion_select setting
 * 10: lopc_intr_pend is set on a falling edge of the LOPC pin, regardless
 * of the Vendor_Specific_LOPC_Control.LOPC_state_inversion_select setting
 * 11: lopc_intr_pend is set on both edges of the LOPC pin
 *
 * Field: VTSS_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control . lopc_intr_pend_bit_select
 */
#define  VTSS_F_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control_lopc_intr_pend_bit_select(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control_lopc_intr_pend_bit_select     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV1_Vendor_Specific_LOPC_Control_Vendor_Specific_LOPC_Control_lopc_intr_pend_bit_select(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_DEV1:BLOCK_LEVEL_RESET
 *
 * Block Level Reset
 */


/** 
 * \brief Block Level Soft Reset1
 *
 * \details
 * Register: \a VENICE_DEV1:BLOCK_LEVEL_RESET:BLOCK_LEVEL_RESET1
 */
#define VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1  VTSS_IOREG(0x01, 0, 0xae00)

/** 
 * \brief
 * Reset the I2C(master) used to communicate with an optics module.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . I2CM_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_I2CM_RESET  VTSS_BIT(15)

/** 
 * \brief
 * Reset the chip's ingress data path in the 1588 processing block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . IP1588_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_IP1588_INGR_RESET  VTSS_BIT(14)

/** 
 * \brief
 * Reset the 1588 LTC clock domain for this channel.  This register resets
 * the same logic as register IP1588_LTC2_RESET.  The reset function is
 * duplicated here in case there is a need to reset the LTC clock domain
 * and 1588 ingress data path registers simultaneously. 
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . IP1588_LTC1_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_IP1588_LTC1_RESET  VTSS_BIT(13)

/** 
 * \brief
 * Reset the 1588 LTC clock domain logic within the channel's ingress and
 * egress TSP blocks.  This register resets the same logic as register
 * IP1588_TSP_LTC2_RESET. 
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . IP1588_TSP_LTC1_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_IP1588_TSP_LTC1_RESET  VTSS_BIT(12)

/** 
 * \brief
 * Reset WIS interrupt tree logic
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . WIS_INTR_TREE_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_WIS_INTR_TREE_RESET  VTSS_BIT(9)

/** 
 * \brief
 * Reset the chip's ingress data path in the XGXS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . XGXS_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_XGXS_INGR_RESET  VTSS_BIT(8)

/** 
 * \brief
 * Reset the chip's ingress data path in the host 1G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . HOST_1G_PCS_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_HOST_1G_PCS_INGR_RESET  VTSS_BIT(7)

/** 
 * \brief
 * Reset the rate compensating FIFO in the chip's ingress data path.  The
 * FIFO is used when the MACs are disabled.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . FIFO_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_FIFO_INGR_RESET  VTSS_BIT(6)

/** 
 * \brief
 * Reset the chip's ingress data path in the host MAC and flow control
 * buffer
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . HOST_MAC_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_HOST_MAC_INGR_RESET  VTSS_BIT(5)

/** 
 * \brief
 * Reset the chip's ingress data path in the line MAC, MACsec (applies to
 * 8490/91) and flow control buffer blocks as well as configuration
 * registers in the MACsec decryption processor
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . LINE_MAC_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_LINE_MAC_INGR_RESET  VTSS_BIT(4)

/** 
 * \brief
 * Reset the chip's ingress data path in the line side 10G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . LINE_10G_PCS_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_LINE_10G_PCS_INGR_RESET  VTSS_BIT(3)

/** 
 * \brief
 * Reset the chip's ingress data path in the line side 1G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . LINE_1G_PCS_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_LINE_1G_PCS_INGR_RESET  VTSS_BIT(2)

/** 
 * \brief
 * Reset the chip's ingress data path in the WIS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . WIS_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_WIS_INGR_RESET  VTSS_BIT(1)

/** 
 * \brief
 * Reset the chip's ingress data path in the PMA and PMA_INT blocks.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1 . PMA_INGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET1_PMA_INGR_RESET  VTSS_BIT(0)


/** 
 * \brief Block Level Soft Reset2
 *
 * \details
 * Register: \a VENICE_DEV1:BLOCK_LEVEL_RESET:BLOCK_LEVEL_RESET2
 */
#define VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2  VTSS_IOREG(0x01, 0, 0xae01)

/** 
 * \brief
 * Reset the chip's egress data path in the 1588 processing block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . IP1588_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_IP1588_EGR_RESET  VTSS_BIT(14)

/** 
 * \brief
 * Reset the 1588 LTC clock domain for this channel.  This register resets
 * the same logic as register IP1588_LTC1_RESET.  The reset function is
 * duplicated here in case there is a need to reset the LTC clock domain
 * and 1588 egress data path registers simultaneously. 
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . IP1588_LTC2_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_IP1588_LTC2_RESET  VTSS_BIT(13)

/** 
 * \brief
 * Reset the 1588 LTC clock domain logic within the channel's ingress and
 * egress TSP blocks.  This register resets the same logic as register
 * IP1588_TSP_LTC1_RESET. 
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . IP1588_TSP_LTC2_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_IP1588_TSP_LTC2_RESET  VTSS_BIT(12)

/** 
 * \brief
 * Reset both the egress and ingress data paths in the HSIO_MACRO_HOST
 * block (client-side serdes)
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . CLIENT_SERDES_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_CLIENT_SERDES_RESET  VTSS_BIT(10)

/** 
 * \brief
 * Reset the chip's egress data path in the XGXS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . XGXS_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_XGXS_EGR_RESET  VTSS_BIT(8)

/** 
 * \brief
 * Reset the chip's egress data path in the host 1G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . HOST_1G_PCS_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_HOST_1G_PCS_EGR_RESET  VTSS_BIT(7)

/** 
 * \brief
 * Reset the rate compensating FIFO in the chip's egress data path.  The
 * FIFO is used when the MACs are disabled
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . FIFO_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_FIFO_EGR_RESET  VTSS_BIT(6)

/** 
 * \brief
 * Reset the chip's egress data path in the host MAC and flow control
 * buffer
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . HOST_MAC_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_HOST_MAC_EGR_RESET  VTSS_BIT(5)

/** 
 * \brief
 * Reset the chip's egress data path in the line MAC, MACsec (applies to
 * 8490/91) and flow control buffer blocks as well as configuration
 * registers in the MACsec encryption processor
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . LINE_MAC_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_LINE_MAC_EGR_RESET  VTSS_BIT(4)

/** 
 * \brief
 * Reset the chip's egress data path in the line side 10G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . LINE_10G_PCS_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_LINE_10G_PCS_EGR_RESET  VTSS_BIT(3)

/** 
 * \brief
 * Reset the chip's egress data path in the line side 1G PCS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . LINE_1G_PCS_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_LINE_1G_PCS_EGR_RESET  VTSS_BIT(2)

/** 
 * \brief
 * Reset the chip's egress data path in the WIS block
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . WIS_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_WIS_EGR_RESET  VTSS_BIT(1)

/** 
 * \brief
 * Reset the chip's egress data path in the PMA and PMA_INT blocks.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2 . PMA_EGR_RESET
 */
#define  VTSS_F_VENICE_DEV1_BLOCK_LEVEL_RESET_BLOCK_LEVEL_RESET2_PMA_EGR_RESET  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:SPARE_RW_REGISTERS
 *
 * Spare R/W Registers
 */


/** 
 * \brief Device1 Spare R/W 0
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW0
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW0  VTSS_IOREG(0x01, 0, 0xaef0)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW0 . dev1_spare_rw0
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW0_dev1_spare_rw0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW0_dev1_spare_rw0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW0_dev1_spare_rw0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 1
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW1
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW1  VTSS_IOREG(0x01, 0, 0xaef1)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW1 . dev1_spare_rw1
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW1_dev1_spare_rw1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW1_dev1_spare_rw1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW1_dev1_spare_rw1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 2
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW2
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW2  VTSS_IOREG(0x01, 0, 0xaef2)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW2 . dev1_spare_rw2
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW2_dev1_spare_rw2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW2_dev1_spare_rw2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW2_dev1_spare_rw2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 3
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW3
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW3  VTSS_IOREG(0x01, 0, 0xaef3)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW3 . dev1_spare_rw3
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW3_dev1_spare_rw3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW3_dev1_spare_rw3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW3_dev1_spare_rw3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 4
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW4
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW4  VTSS_IOREG(0x01, 0, 0xaef4)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW4 . dev1_spare_rw4
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW4_dev1_spare_rw4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW4_dev1_spare_rw4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW4_dev1_spare_rw4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 5
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW5
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW5  VTSS_IOREG(0x01, 0, 0xaef5)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW5 . dev1_spare_rw5
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW5_dev1_spare_rw5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW5_dev1_spare_rw5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW5_dev1_spare_rw5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 6
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW6
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW6  VTSS_IOREG(0x01, 0, 0xaef6)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW6 . dev1_spare_rw6
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW6_dev1_spare_rw6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW6_dev1_spare_rw6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW6_dev1_spare_rw6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 7
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW7
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW7  VTSS_IOREG(0x01, 0, 0xaef7)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW7 . dev1_spare_rw7
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW7_dev1_spare_rw7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW7_dev1_spare_rw7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW7_dev1_spare_rw7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 8
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW8
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW8  VTSS_IOREG(0x01, 0, 0xaef8)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW8 . dev1_spare_rw8
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW8_dev1_spare_rw8(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW8_dev1_spare_rw8     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW8_dev1_spare_rw8(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 9
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW9
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW9  VTSS_IOREG(0x01, 0, 0xaef9)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW9 . dev1_spare_rw9
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW9_dev1_spare_rw9(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW9_dev1_spare_rw9     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW9_dev1_spare_rw9(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 10
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW10
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW10  VTSS_IOREG(0x01, 0, 0xaefa)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW10 . dev1_spare_rw10
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW10_dev1_spare_rw10(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW10_dev1_spare_rw10     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW10_dev1_spare_rw10(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 11
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW11
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW11  VTSS_IOREG(0x01, 0, 0xaefb)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW11 . dev1_spare_rw11
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW11_dev1_spare_rw11(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW11_dev1_spare_rw11     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW11_dev1_spare_rw11(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 12
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW12
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW12  VTSS_IOREG(0x01, 0, 0xaefc)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW12 . dev1_spare_rw12
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW12_dev1_spare_rw12(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW12_dev1_spare_rw12     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW12_dev1_spare_rw12(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 13
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW13
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW13  VTSS_IOREG(0x01, 0, 0xaefd)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW13 . dev1_spare_rw13
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW13_dev1_spare_rw13(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW13_dev1_spare_rw13     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW13_dev1_spare_rw13(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 14
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW14
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW14  VTSS_IOREG(0x01, 0, 0xaefe)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW14 . dev1_spare_rw14
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW14_dev1_spare_rw14(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW14_dev1_spare_rw14     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW14_dev1_spare_rw14(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device1 Spare R/W 15
 *
 * \details
 * Register: \a VENICE_DEV1:SPARE_RW_REGISTERS:DEV1_SPARE_RW15
 */
#define VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW15  VTSS_IOREG(0x01, 0, 0xaeff)

/** 
 * \brief
 * Bits [15:9]	Reserved.
 * Bit [8]  Software reset for TX 10G serdes analog macro.
 *   0:  Normal operation
 *   1:  Reset state
 * Note the software reset register is not self-clearing.
 * 
 * Bits [7:1]  Reserved.
 * Bit [0]  Software reset for RX 10G serdes analog macro.
 *   0:  Normal operation
 *   1:  Reset state
 * Note the software reset register is not self-clearing.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW15 . dev1_spare_rw15
 */
#define  VTSS_F_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW15_dev1_spare_rw15(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW15_dev1_spare_rw15     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SPARE_RW_REGISTERS_DEV1_SPARE_RW15_dev1_spare_rw15(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:SD10G65_VSCOPE2
 *
 * SD10G65 VSCOPE Configuration and Status Register set
 */


/** 
 * \brief Vscope main config register A
 *
 * \details
 * Vscope main configuration register A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_MAIN_CFG_A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A  VTSS_IOREG(0x01, 0, 0xb000)

/** 
 * \brief
 * Disables writing of synth_phase_aux in synthesizer
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A . SYN_PHASE_WR_DIS
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_SYN_PHASE_WR_DIS  VTSS_BIT(8)

/** 
 * \brief
 * Disables writing of ib_auxl_offset and ib_auxh_offset in IB
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A . IB_AUX_OFFS_WR_DIS
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_IB_AUX_OFFS_WR_DIS  VTSS_BIT(7)

/** 
 * \brief
 * Disables writing of ib_jumpl_ena and ib_jumph_ena in IB
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A . IB_JUMP_ENA_WR_DIS
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_IB_JUMP_ENA_WR_DIS  VTSS_BIT(6)

/** 
 * \brief
 * Counter output selection
 *
 * \details 
 * 0-3: error counter 0-3
 * 4: hit counter
 * 5: clock counter
 * 6: 8 LSBs of error counter 3-1 and hit counter
 * 7: 8 LSBs of error counter 3-0
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A . CNT_OUT_SEL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_CNT_OUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_CNT_OUT_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_CNT_OUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Comparator input selection
 *
 * \details 
 * [REF] 0
 * 1: auxL
 * 4
 * 5: auxH
 * 2
 * 7: main; [SUB] 5
 * 7: auxL
 * 0
 * 2: auxH
 * 1
 * 4: main (3
 * 6: reserved)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A . COMP_SEL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_COMP_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_COMP_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_A_COMP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Vscope main config register B
 *
 * \details
 * Vscope main configuration register B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_MAIN_CFG_B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B  VTSS_IOREG(0x01, 0, 0xb001)

/** 
 * \brief
 * Select GP reg input
 *
 * \details 
 * 0: rx (main)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B . GP_SELECT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_GP_SELECT(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_GP_SELECT     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_GP_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Allows to freeze the GP register value to assure valid reading
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B . GP_REG_FREEZE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_GP_REG_FREEZE  VTSS_BIT(7)

/** 
 * \brief
 * Scan limit, selects which counter saturation limits the other counters
 *
 * \details 
 * 0: clock counter
 * 1: hit counter
 * 2: error counters
 * 3: no limit
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B . SCAN_LIM
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_SCAN_LIM(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_SCAN_LIM     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_SCAN_LIM(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Preload value for error counter
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B . PRELOAD_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_PRELOAD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_PRELOAD_VAL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_B_PRELOAD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Vscope main config register C
 *
 * \details
 * Vscope main configuration register C
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_MAIN_CFG_C
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C  VTSS_IOREG(0x01, 0, 0xb002)

/** 
 * \brief
 * Disable interrupt output
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . INTR_DIS
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_INTR_DIS  VTSS_BIT(12)

/** 
 * \brief
 * Enable trigger
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . TRIG_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_TRIG_ENA  VTSS_BIT(11)

/** 
 * \brief
 * Counter enable (bit 4) implicitly done by reading the counter; unused in
 * hw-scan mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . QUICK_SCAN
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_QUICK_SCAN  VTSS_BIT(10)

/** 
 * \brief
 * Counter period: preload value for clock counter
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . COUNT_PER
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_COUNT_PER(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_COUNT_PER     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_COUNT_PER(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Enable Counting; unused in hw-scan mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . CNT_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_CNT_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Interface Width
 *
 * \details 
 * 0: 8 bit
 * 1: 10 bit
 * 2: 16 bit
 * 3: 20 bit
 * 4: 32 bit
 * 5: 40 bit
 * others: reserved
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . IF_MODE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_IF_MODE     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Enable Vscope
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C . VSCOPE_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_MAIN_CFG_C_VSCOPE_ENA  VTSS_BIT(0)


/** 
 * \brief Vscope pattern lock config register A
 *
 * \details
 * Vscope pattern lock configuration register A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_PAT_LOCK_CFG_A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A  VTSS_IOREG(0x01, 0, 0xb003)

/** 
 * \brief
 * Preload value for hit counter
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A . PRELOAD_HIT_CNT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_PRELOAD_HIT_CNT(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_PRELOAD_HIT_CNT     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_PRELOAD_HIT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * Don't Care mask: Enable history mask usage.
 *
 * \details 
 * 0: enable history mask bit
 * 1: history mask bit is "don't care"
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A . DC_MASK
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_DC_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_DC_MASK     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_A_DC_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Vscope pattern lock config register B
 *
 * \details
 * Vscope pattern lock configuration register B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_PAT_LOCK_CFG_B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_B  VTSS_IOREG(0x01, 0, 0xb004)

/** 
 * \brief
 * History mask: Respective sequence is expected in reference input
 * (comp_sel); if enabled (dc_mask) before hit and error counting is
 * enabled
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_B . HIST_MASK
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_B_HIST_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_B_HIST_MASK     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_PAT_LOCK_CFG_B_HIST_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Vscope hw scan config register 1A
 *
 * \details
 * Vscope HW scan configuration register 1A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG_1A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A  VTSS_IOREG(0x01, 0, 0xb005)

/** 
 * \brief
 * Invert the jumph_ena and jumpl_ena bit in HW scan mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A . PHASE_JUMP_INV
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_PHASE_JUMP_INV  VTSS_BIT(13)

/** 
 * \brief
 * Offset between AuxL amplitude (reference) and AuxH amplitude, signed
 * (2s-complement), +- 1/4 amplitude max.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A . AMPL_OFFS_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_AMPL_OFFS_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_AMPL_OFFS_VAL     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_AMPL_OFFS_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Maximum phase increment value before wrapping
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A . MAX_PHASE_INCR_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_MAX_PHASE_INCR_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_MAX_PHASE_INCR_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1A_MAX_PHASE_INCR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vscope hw scan config register 1B
 *
 * \details
 * Vscope HW scan configuration register 1B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG_1B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B  VTSS_IOREG(0x01, 0, 0xb006)

/** 
 * \brief
 * Maximum amplitude increment value before wrapping
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B . MAX_AMPL_INCR_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_MAX_AMPL_INCR_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_MAX_AMPL_INCR_VAL     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_MAX_AMPL_INCR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Phase increment per scan step
 *
 * \details 
 * Increment = phase_incr + 1
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B . PHASE_INCR
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_PHASE_INCR(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_PHASE_INCR     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_PHASE_INCR(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Amplitude increment per scan step
 *
 * \details 
 * Increment = ampl_incr + 1
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B . AMPL_INCR
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_AMPL_INCR(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_AMPL_INCR     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_AMPL_INCR(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Number of scans per iteration in N-point-scan mode
 *
 * \details 
 * 0: 1
 * 1: 2
 * 2: 4
 * 3: 8
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B . NUM_SCANS_PER_ITR
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_NUM_SCANS_PER_ITR(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_NUM_SCANS_PER_ITR     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_NUM_SCANS_PER_ITR(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enables HW scan with N results per scan or fast-scan
 *
 * \details 
 * 0: off
 * 1: N-point scan
 * 2: fast-scan (sq)
 * 3: fast-scan (diag)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B . HW_SCAN_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_HW_SCAN_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_HW_SCAN_ENA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_1B_HW_SCAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Vscope hw config register 2A
 *
 * \details
 * Vscope HW scan configuration register 2A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG_2A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A  VTSS_IOREG(0x01, 0, 0xb007)

/** 
 * \brief
 * Threshold for error_counter in fast-scan mode
 *
 * \details 
 * N+1
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A . FAST_SCAN_THRES
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FAST_SCAN_THRES(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FAST_SCAN_THRES     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FAST_SCAN_THRES(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * Left shift for threshold of error_counter in fast-scan mode
 *
 * \details 
 * threshold = (fast_scan_thres+1) shift_left fs_thres_shift
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A . FS_THRES_SHIFT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FS_THRES_SHIFT(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FS_THRES_SHIFT     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_FS_THRES_SHIFT(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Value at which jumpl_ena and jumph_ena in IB must be toggled
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A . PHASE_JUMP_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_PHASE_JUMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_PHASE_JUMP_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2A_PHASE_JUMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vscope hw config register 2B
 *
 * \details
 * Vscope HW scan configuration register 2B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_HW_SCAN_CFG_2B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B  VTSS_IOREG(0x01, 0, 0xb008)

/** 
 * \brief
 * Disable IB amplitude symmetry compensation for AuxH and AuxL
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B . AUX_AMPL_SYM_DIS
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_AUX_AMPL_SYM_DIS  VTSS_BIT(15)

/** 
 * \brief
 * Start value for VScope amplitude in N-point-scan mode and fast-scan mode
 * (before IB amplitude symmetry compensation)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B . AMPL_START_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_AMPL_START_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_AMPL_START_VAL     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_AMPL_START_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Start value for VScope phase in N-point-scan mode and fast-scan mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B . PHASE_START_VAL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_PHASE_START_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_PHASE_START_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_HW_SCAN_CFG_2B_PHASE_START_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Vscope status register
 *
 * \details
 * Vscope status register
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_STAT
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT  VTSS_IOREG(0x01, 0, 0xb009)

/** 
 * \brief
 * 8 MSBs of general purpose register
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT . GP_REG_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_GP_REG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Fast scan mode: Indicator per cursor position whether threshold was
 * reached
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT . FAST_SCAN_HIT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_FAST_SCAN_HIT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Done sticky
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT . DONE_STICKY
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_STAT_DONE_STICKY  VTSS_BIT(0)


/** 
 * \brief Vscope counter register A
 *
 * \details
 * Vscope counter register A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_CNT_A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_A  VTSS_IOREG(0x01, 0, 0xb00a)

/** 
 * \brief
 * Counter value higher 16-bit MSB [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_A . COUNTER_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_A_COUNTER_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_A_COUNTER_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_A_COUNTER_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vscope counter register B
 *
 * \details
 * Vscope counter register B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_CNT_B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_B  VTSS_IOREG(0x01, 0, 0xb00b)

/** 
 * \brief
 * Counter value lower 16-bit LSB [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_B . COUNTER_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_B_COUNTER_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_B_COUNTER_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_CNT_B_COUNTER_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vscope general purpose register A
 *
 * \details
 * Vscope general purpose  register A
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_DBG_LSB_A
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_A  VTSS_IOREG(0x01, 0, 0xb00c)

/** 
 * \brief
 * 16 bit MSB of a 32 bit general purpose register [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_A . GP_REG_LSB_A
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_A_GP_REG_LSB_A(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_A_GP_REG_LSB_A     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_A_GP_REG_LSB_A(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Vscope general purpose register A
 *
 * \details
 * Vscope general purpose  register B
 *
 * Register: \a VENICE_DEV1:SD10G65_VSCOPE2:VSCOPE_DBG_LSB_B
 */
#define VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_B  VTSS_IOREG(0x01, 0, 0xb00d)

/** 
 * \brief
 * 16 bit LSB of a 32 bit general purpose register [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_B . GP_REG_LSB_B
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_B_GP_REG_LSB_B(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_B_GP_REG_LSB_B     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_VSCOPE2_VSCOPE_DBG_LSB_B_GP_REG_LSB_B(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:SD10G65_DFT
 *
 * SD10G65 DFT Configuration and Status Register set
 */


/** 
 * \brief SD10G65 DFT Main configuration register 1
 *
 * \details
 * Main configuration register 1 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1  VTSS_IOREG(0x01, 0, 0xb100)

/** 
 * \brief
 * Disables error generation based on stuck_at_par errors,
 *
 * \details 
 * 0: stuck_at_par error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_par error does not generate errors
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . STUCK_AT_PAR_MASK_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_STUCK_AT_PAR_MASK_CFG  VTSS_BIT(12)

/** 
 * \brief
 * Disables error generation based on stuck_at_01 errors,
 *
 * \details 
 * 0: stuck_at_01 error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_01 error does not generate errors
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . STUCK_AT_01_MASK_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_STUCK_AT_01_MASK_CFG  VTSS_BIT(11)

/** 
 * \brief
 * Enables data through from gearbox to gearbox
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . DIRECT_THROUGH_ENA_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_DIRECT_THROUGH_ENA_CFG  VTSS_BIT(10)

/** 
 * \brief
 * Captures data from error counter to allow reading of stable data
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . ERR_CNT_CAPT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_ERR_CNT_CAPT_CFG  VTSS_BIT(9)

/** 
 * \brief
 * Data source selection
 *
 * \details 
 * 0: main path
 * 1: vscope high path
 * 2: vscope low path
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . RX_DATA_SRC_SEL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_DATA_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_DATA_SRC_SEL     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_DATA_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * States in which error counting is enabled
 *
 * \details 
 * 3:all but IDLE; 2:check 1:stable+check
 * 0:wait_stable+stable+check
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . BIST_CNT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_BIST_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_BIST_CNT_CFG     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_BIST_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Disable change of stored patterns (e.g. to avoid changes during
 * read-out)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . FREEZE_PATTERN_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_FREEZE_PATTERN_CFG  VTSS_BIT(4)

/** 
 * \brief
 * Selects pattern to check
 *
 * \details 
 * 0: PRBS pattern
 * 1: constant pattern
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . CHK_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_CHK_MODE_CFG  VTSS_BIT(3)

/** 
 * \brief
 * Selects DES interface width
 *
 * \details 
 * 0:8
 * 1:10
 * 2:16
 * 3:20
 * 4:32
 * 5:40 (default)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1 . RX_WID_SEL_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_WID_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_WID_SEL_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_1_RX_WID_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SD10G65 DFT Main configuration register 2
 *
 * \details
 * Main configuration register 2 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2  VTSS_IOREG(0x01, 0, 0xb101)

/** 
 * \brief
 * Pattern generator: 0:bytes mode; 1:10-bits word mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . RX_WORD_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_RX_WORD_MODE_CFG  VTSS_BIT(14)

/** 
 * \brief
 * Selects PRBS check
 *
 * \details 
 * 0: prbs7
 * 1: prbs15
 * 2: prbs23
 * 3: prbs11
 * 4: prbs31 (default)
 * 5: prbs9
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . RX_PRBS_SEL_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_RX_PRBS_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_RX_PRBS_SEL_CFG     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_RX_PRBS_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Enables PRBS checker input inversion
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . INV_ENA_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_INV_ENA_CFG  VTSS_BIT(10)

/** 
 * \brief
 * Selects compare mode
 *
 * \details 
 * 0: compare mode possible
 * 1 learn mode is forced
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . CMP_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_CMP_MODE_CFG  VTSS_BIT(9)

/** 
 * \brief
 * Number of consecutive errors/non-errors before transitioning to
 * respective state
 *
 * \details 
 * value = num-40-bits-words + 1
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . LRN_CNT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_LRN_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_LRN_CNT_CFG     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_LRN_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * SW reset of error counter; rising edge activates reset
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . CNT_RST
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_CNT_RST  VTSS_BIT(5)

/** 
 * \brief
 * Selects modes in which error counter is active
 *
 * \details 
 * 0:learn and compare mode
 * 1:transition between modes
 * 2:learn mode
 * 3:compare mode
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . CNT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_CNT_CFG     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * BIST mode
 *
 * \details 
 * 0: off
 * 1: BIST
 * 2: BER
 * 3:CONT (infinite mode)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . BIST_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_BIST_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_BIST_MODE_CFG     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_BIST_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enable RX DFT capability
 *
 * \details 
 * 0: Disable DFT
 * 1: Enable DFT
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2 . DFT_RX_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_CFG_2_DFT_RX_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 DFT pattern mask configuration register 1 
 *
 * \details
 * Configuration register 1 for SD10G65 DFT to mask data bits preventing
 * error counting for these bits.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_MASK_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_1  VTSS_IOREG(0x01, 0, 0xb102)

/** 
 * \brief
 * Mask out (active high) errors in 16 bit MSB data bits [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_1 . LSB_MASK_CFG_1
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_1_LSB_MASK_CFG_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_1_LSB_MASK_CFG_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_1_LSB_MASK_CFG_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT pattern mask configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 DFT to mask data bits preventing
 * error counting for these bits.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_MASK_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_2  VTSS_IOREG(0x01, 0, 0xb103)

/** 
 * \brief
 * Mask out (active high) errors in 16 LSB data bits [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_2 . LSB_MASK_CFG_2
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_2_LSB_MASK_CFG_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_2_LSB_MASK_CFG_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_MASK_CFG_2_LSB_MASK_CFG_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT Pattern checker configuration register 1
 *
 * \details
 * Pattern checker configuration register 1 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_PAT_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1  VTSS_IOREG(0x01, 0, 0xb104)

/** 
 * \brief
 * Mask out (active high) errors in 8 MSB data bits
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1 . MSB_MASK_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1_MSB_MASK_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1_MSB_MASK_CFG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1_MSB_MASK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Pattern read enable
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1 . PAT_READ_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_1_PAT_READ_CFG  VTSS_BIT(0)


/** 
 * \brief SD10G65 DFT Pattern checker configuration register 2
 *
 * \details
 * Pattern checker configuration register 2 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_RX_PAT_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2  VTSS_IOREG(0x01, 0, 0xb105)

/** 
 * \brief
 * Maximum address in Checker (before continuing with address 0)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2 . MAX_ADDR_CHK_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_MAX_ADDR_CHK_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_MAX_ADDR_CHK_CFG     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_MAX_ADDR_CHK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Address to read patterns from used by SW
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2 . READ_ADDR_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_READ_ADDR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_READ_ADDR_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_RX_PAT_CFG_2_READ_ADDR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for SD10G65 DFT controlling 'check and
 * wait-stable' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG0A
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0A  VTSS_IOREG(0x01, 0, 0xb106)

/** 
 * \brief
 * BIST FSM: threshold to leave DOZE state
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0A . WAKEUP_DLY_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0A_WAKEUP_DLY_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0A_WAKEUP_DLY_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0A_WAKEUP_DLY_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for SD10G65 DFT controlling 'check and
 * wait-stable' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG0B
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0B  VTSS_IOREG(0x01, 0, 0xb107)

/** 
 * \brief
 * BIST FSM: threshold to enter FINISHED state
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0B . MAX_BIST_FRAMES_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0B_MAX_BIST_FRAMES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0B_MAX_BIST_FRAMES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG0B_MAX_BIST_FRAMES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for SD10G65 DFT  controlling 'stable'
 * mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG1A
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1A  VTSS_IOREG(0x01, 0, 0xb108)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_stable_attempts
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1A . MAX_UNSTABLE_CYC_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1A_MAX_UNSTABLE_CYC_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1A_MAX_UNSTABLE_CYC_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1A_MAX_UNSTABLE_CYC_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for SD10G65 DFT  controlling 'stable'
 * mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG1B
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1B  VTSS_IOREG(0x01, 0, 0xb109)

/** 
 * \brief
 * BIST FSM: threshold to enter CHECK state
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1B . STABLE_THRES_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1B_STABLE_THRES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1B_STABLE_THRES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG1B_STABLE_THRES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register A
 *
 * \details
 * BIST configuration register B for SD10G65 DFT controlling frame length
 * in 'check' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG2A
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2A  VTSS_IOREG(0x01, 0, 0xb10a)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_bist_frames [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2A . FRAME_LEN_CFG_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2A_FRAME_LEN_CFG_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2A_FRAME_LEN_CFG_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2A_FRAME_LEN_CFG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for SD10G65 DFT controlling frame length
 * in 'check' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG2B
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2B  VTSS_IOREG(0x01, 0, 0xb10b)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_bist_frames [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2B . FRAME_LEN_CFG_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2B_FRAME_LEN_CFG_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2B_FRAME_LEN_CFG_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG2B_FRAME_LEN_CFG_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for SD10G65 DFT controlling stable
 * attempts in ' wait-stable' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG3A
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3A  VTSS_IOREG(0x01, 0, 0xb10c)

/** 
 * \brief
 * BIST FSM: threshold to enter SYNC_ERR state [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3A . MAX_STABLE_ATTEMPTS_CFG_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for SD10G65 DFT controlling stable
 * attempts in ' wait-stable' mode.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_BIST_CFG3B
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3B  VTSS_IOREG(0x01, 0, 0xb10d)

/** 
 * \brief
 * BIST FSM: threshold to enter SYNC_ERR state [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3B . MAX_STABLE_ATTEMPTS_CFG_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_BIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT error status register 1
 *
 * \details
 * Status register 1 for SD10G65 DFT containing the error counter value
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_ERR_STAT_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_1  VTSS_IOREG(0x01, 0, 0xb10e)

/** 
 * \brief
 * Counter output depending on cnt_cfg [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_1 . ERR_CNT_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_1_ERR_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_1_ERR_CNT_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_1_ERR_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT error status register 2
 *
 * \details
 * Status register B2 for SD10G65 DFT containing the error counter value
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_ERR_STAT_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_2  VTSS_IOREG(0x01, 0, 0xb10f)

/** 
 * \brief
 * Counter output depending on cnt_cfg [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_2 . ERR_CNT_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_2_ERR_CNT_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_2_ERR_CNT_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_ERR_STAT_2_ERR_CNT_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT PRBS status register 1
 *
 * \details
 * Status register 1 for SD10G65 DFT containing the PRBS data related to
 * 1st sync lost event
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_PRBS_STAT_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_1  VTSS_IOREG(0x01, 0, 0xb110)

/** 
 * \brief
 * PRBS data after first sync lost [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_1 . PRBS_DATA_STAT_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_1_PRBS_DATA_STAT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_1_PRBS_DATA_STAT_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_1_PRBS_DATA_STAT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT PRBS status register 2
 *
 * \details
 * Status register 2 for SD10G65 DFT containing the PRBS data related to
 * 1st sync lost event
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_PRBS_STAT_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_2  VTSS_IOREG(0x01, 0, 0xb111)

/** 
 * \brief
 * PRBS data after first sync lost [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_2 . PRBS_DATA_STAT_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_2_PRBS_DATA_STAT_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_2_PRBS_DATA_STAT_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_PRBS_STAT_2_PRBS_DATA_STAT_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 DFT miscellaneous status register 1
 *
 * \details
 * Status register 1 for SD10G65 DFT
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_MAIN_STAT_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_1  VTSS_IOREG(0x01, 0, 0xb112)

/** 
 * \brief
 * 10 bits data word at address 'read_addr_cfg' used for further
 * observation by SW
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_1 . CMP_DATA_STAT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_1_CMP_DATA_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_1_CMP_DATA_STAT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_1_CMP_DATA_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SD10G65 DFT miscellaneous status register 2
 *
 * \details
 * Status register 2 for SD10G65 DFT
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_MAIN_STAT_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2  VTSS_IOREG(0x01, 0, 0xb113)

/** 
 * \brief
 * Data input is unchanged for all 40 parallel bits for at least 7 clock
 * cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . STUCK_AT_PAR
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_STUCK_AT_PAR  VTSS_BIT(5)

/** 
 * \brief
 * Data input is constantly 0 or constantly 1 for all 40 parallel bits for
 * at least 7 clock cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . STUCK_AT_01
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_STUCK_AT_01  VTSS_BIT(4)

/** 
 * \brief
 * BIST: no sync found since BIST enabled
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . NO_SYNC
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_NO_SYNC  VTSS_BIT(3)

/** 
 * \brief
 * BIST: input data not stable
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . INSTABLE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_INSTABLE  VTSS_BIT(2)

/** 
 * \brief
 * BIST not complete (i.e. not reached stable state or following)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . INCOMPLETE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_INCOMPLETE  VTSS_BIT(1)

/** 
 * \brief
 * BIST is active (i.e. left DOZE but did not enter a final state)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2 . ACTIVE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_MAIN_STAT_2_ACTIVE  VTSS_BIT(0)


/** 
 * \brief SD10G65 DFT Main configuration register
 *
 * \details
 * Main configuration register for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_CFG
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG  VTSS_IOREG(0x01, 0, 0xb114)

/** 
 * \brief
 * Enables (1) reset of PRBS generator in case of unchanged data
 * ('stuck-at') for at least 511 clock cycles. Can be disabled (0) e.g. in
 * scrambler mode to avoid the very rare case that input patterns allow to
 * keep the generator's shift register filled with a constant value.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . RST_ON_STUCK_AT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_RST_ON_STUCK_AT_CFG  VTSS_BIT(12)

/** 
 * \brief
 * Selects SER interface width
 *
 * \details 
 * 0:8
 * 1:10
 * 2:16
 * 3:20
 * 4:32
 * 5:40 (default)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . TX_WID_SEL_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_WID_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Selects PRBS generator
 *
 * \details 
 * 0: prbs7
 * 1: prbs15
 * 2: prbs23
 * 3: prbs11
 * 4: prbs31 (default)
 * 5: prbs9
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . TX_PRBS_SEL_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_PRBS_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Inverts the scrambler output
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . SCRAM_INV_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_SCRAM_INV_CFG  VTSS_BIT(5)

/** 
 * \brief
 * Selects PRBS generator input
 *
 * \details 
 * 0:pat-gen
 * 1:core
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . IPATH_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_IPATH_CFG  VTSS_BIT(4)

/** 
 * \brief
 * Selects DFT-TX output
 *
 * \details 
 * 0:PRBS/scrambler (default)
 * 1:bypass

 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . OPATH_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_OPATH_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Word width of constant pattern generator
 *
 * \details 
 * 0:bytes mode; 1:10-bits word mode
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . TX_WORD_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_TX_WORD_MODE_CFG  VTSS_BIT(1)

/** 
 * \brief
 * Enable TX DFT capability
 *
 * \details 
 * 0: Disable DFT
 * 1: Enable DFT
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG . DFT_TX_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CFG_DFT_TX_ENA  VTSS_BIT(0)


/** 
 * \brief SD10G65 DFT TX Constant pattern configuration register 1
 *
 * \details
 * TX Constant MSB pattern configuration register 1 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_PAT_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1  VTSS_IOREG(0x01, 0, 0xb115)

/** 
 * \brief
 * Constant patterns are valid to store
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1 . PAT_VLD_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1_PAT_VLD_CFG  VTSS_BIT(4)

/** 
 * \brief
 * Maximum address in generator (before continuing with address 0)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1 . MAX_ADDR_GEN_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1_MAX_ADDR_GEN_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1_MAX_ADDR_GEN_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_1_MAX_ADDR_GEN_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 DFT TX Constant pattern configuration register 2
 *
 * \details
 * TX Constant MSB pattern configuration register 2 for SD10G65 DFT.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_PAT_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2  VTSS_IOREG(0x01, 0, 0xb116)

/** 
 * \brief
 * Current storage address for patterns in generator
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2 . STORE_ADDR_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_STORE_ADDR_CFG(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_STORE_ADDR_CFG     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_STORE_ADDR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * 10 bits word of constant patterns for transmission
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2 . PATTERN_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_PATTERN_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_PATTERN_CFG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_PAT_CFG_2_PATTERN_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SD10G65 DFT TX constant pattern status register
 *
 * \details
 * Status register for SD10G65 DFT containing the constant patterns used
 * for comparison (last in LEARN mode)
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_CMP_DAT_STAT
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT  VTSS_IOREG(0x01, 0, 0xb117)

/** 
 * \brief
 * Scrambler/PRBS generator output unchanged for at least 511 clock cycles.
 *  The high state is cleared by writing a 1 to the bit.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT . TX_STUCK_AT_STICKY
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_TX_STUCK_AT_STICKY  VTSS_BIT(12)

/** 
 * \brief
 * 10 bits data word at address 'store_addr_cfg' used for further
 * observation by SW
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT . PAT_STAT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_CMP_DAT_STAT_PAT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief DFT clock compare config
 *
 * \details
 * Configuration register for Clock Compare logic. Compared clocks are
 * always divided by 4 before any further processing. A clock edge on
 * tx_clk increments the counter, a clock edge on rx_clk decrements the
 * counter. If only one clock is selected for clock comparison, the number
 * of clock cycles within a given time can be measured.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_CFG
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG  VTSS_IOREG(0x01, 0, 0xb118)

/** 
 * \brief
 * Clock compare value updated toggle bit. Toggles on each update of
 * CLK_CMP_VALUE
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_UPDTOG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_UPDTOG  VTSS_BIT(12)

/** 
 * \brief
 * Enable clock comparison counter wrap
 *
 * \details 
 * 0: counter saturates
 * 1: counter wraps
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_WRAP_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_WRAP_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Clock compare divider for TX clock
 *
 * \details 
 * 0: tx clk
 * 1: tx_clk/2
 * 2: tx_clk/4
 * 3: tx_clk/8
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_DIV_TX
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_TX(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_TX     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_TX(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Clock compare divider for RX clock
 *
 * \details 
 * 0: rx clk
 * 1: rx_clk/2
 * 2: rx_clk/4
 * 3: rx_clk/8
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_DIV_RX
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_RX(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_RX     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_DIV_RX(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Clock compare selection
 *
 * \details 
 * 0: rx_clk vs. tx_clk
 * 1: rx_clk
 * 2: tx_clk
 * 3: Reserved
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_SEL
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Clock comparison mode
 *
 * \details 
 * 0: single shot
 * 1: continuous
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_MODE
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_MODE  VTSS_BIT(1)

/** 
 * \brief
 * Enable clock comparison (enabling automatically clears comparison
 * counter)
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG . CLK_CMP_ENA
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_CFG_CLK_CMP_ENA  VTSS_BIT(0)


/** 
 * \brief DFT clock compare timer
 *
 * \details
 * Upper half of clock comparison timer.  After timer has expired, current
 * clock comparison value is stored.  The timer is clocked at 156.25 MHz.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_TIMERA
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERA  VTSS_IOREG(0x01, 0, 0xb119)

/** 
 * \brief
 * Clock comparison timer, bits [31:16].  Counter interval is N + 1 clock
 * cycles where the clock frequency is 156.25 MHz.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERA . CLK_CMP_TIMER_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERA_CLK_CMP_TIMER_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERA_CLK_CMP_TIMER_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERA_CLK_CMP_TIMER_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT clock compare timer
 *
 * \details
 * Lower half of clock comparison timer.  After timer has expired, current
 * clock comparison value is stored.  The timer is clocked at 156.25 MHz.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_TIMERB
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERB  VTSS_IOREG(0x01, 0, 0xb11a)

/** 
 * \brief
 * Clock comparison timer, bits [15:0].  Counter interval is N + 1 clock
 * cycles where the clock frequency is 156.25 MHz.
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERB . CLK_CMP_TIMER_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERB_CLK_CMP_TIMER_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERB_CLK_CMP_TIMER_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_TIMERB_CLK_CMP_TIMER_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT clock comparison value
 *
 * \details
 * Upper half of clock comparison result. This register is updated after
 * clock comparison timer has expired.	In continuous mode this register is
 * periodically updated.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_VALUEA
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEA  VTSS_IOREG(0x01, 0, 0xb11b)

/** 
 * \brief
 * Clock comparison value (difference between clk0 and clk1), bits [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEA . CLK_CMP_VALUE_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEA_CLK_CMP_VALUE_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEA_CLK_CMP_VALUE_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEA_CLK_CMP_VALUE_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT clock comparison value
 *
 * \details
 * Lower half of clock comparison result. This register is updated after
 * clock comparison timer has expired.	In continuous mode this register is
 * periodically updated.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_VALUEB
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEB  VTSS_IOREG(0x01, 0, 0xb11c)

/** 
 * \brief
 * Clock comparison value (difference between clk0 and clk1), bits [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEB . CLK_CMP_VALUE_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEB_CLK_CMP_VALUE_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEB_CLK_CMP_VALUE_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_VALUEB_CLK_CMP_VALUE_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT clock comparison maximum value
 *
 * \details
 * Upper half of clock comparison max result.  Can be used to judge e.g.
 * SSC clock deviation.  This register is updated after clock comparison
 * timer has expired.  In continuous mode this register is periodically
 * updated.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_MAXVALA
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALA  VTSS_IOREG(0x01, 0, 0xb11d)

/** 
 * \brief
 * Clock comparison max value (maximum measured difference between clk0 and
 * clk1), bits [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALA . CLK_CMP_MAXVAL_MSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALA_CLK_CMP_MAXVAL_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALA_CLK_CMP_MAXVAL_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALA_CLK_CMP_MAXVAL_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT clock comparison maximum value
 *
 * \details
 * Lower half of clock comparison max result.  Can be used to judge e.g.
 * SSC clock deviation.  This register is updated after clock comparison
 * timer has expired.  In continuous mode this register is periodically
 * updated.
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_CMP_MAXVALB
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALB  VTSS_IOREG(0x01, 0, 0xb11e)

/** 
 * \brief
 * Clock comparison max value (maximum measured difference between clk0 and
 * clk1), bits [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALB . CLK_CMP_MAXVAL_LSB
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALB_CLK_CMP_MAXVAL_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALB_CLK_CMP_MAXVAL_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_CMP_MAXVALB_CLK_CMP_MAXVAL_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief DFT TX Error insertion configuration register
 *
 * \details
 * Configuration register for explicit error insertion into DFT driven data
 * stream. Allows to insert expected errors to check e.g. TX/RX
 * connectivity
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_ERR_INSERT_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1  VTSS_IOREG(0x01, 0, 0xb11f)

/** 
 * \brief
 * Preload value for clock generator timer
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1 . CG_TIMER_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_CG_TIMER_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_CG_TIMER_CFG     VTSS_ENCODE_BITMASK(6,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_CG_TIMER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,10)

/** 
 * \brief
 * Trigger a single error or a burst of errors (refer to num_err_cfg)
 *
 * \details 
 * 0 to 1 (edge) activates this function
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1 . ERR_TRIG_ONESHOT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_ERR_TRIG_ONESHOT_CFG  VTSS_BIT(4)

/** 
 * \brief
 * Frequency of continous/limited error insertion in steps of 40 bits
 *
 * \details 
 * 0: disable continous insertion 1-15: step between 2 errors =
 * 2^(err_freq_cfg + 5) 40 bit words (refer also to err_posit_offs_cfg)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1 . ERR_FREQ_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_ERR_FREQ_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_ERR_FREQ_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_1_ERR_FREQ_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief DFT TX Error insertion configuration register
 *
 * \details
 * Configuration register for explicit error insertion into DFT driven data
 * stream. Allows to insert expected errors to check e.g. TX/RX
 * connectivity
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_TX_ERR_INSERT_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2  VTSS_IOREG(0x01, 0, 0xb120)

/** 
 * \brief
 * Position within 40 bit word where an error is inserted by inverting the
 * bit value
 *
 * \details 
 * 0: LSB
 * 39: MSB
 * 40-63: reserved
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2 . ERR_POSIT_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_CFG(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_CFG     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Offset of bitposition increased per inserted error; allows 'walking'
 * error. Offset is reset when continous/limited error insertion is
 * disabled or burst mode is enabled and burst insertion is finished or
 * err_posit_offs_cfg = 0
 *
 * \details 
 * 0: disabled
 * 1: move 1 bit (from LSB to MSB)
 * ...
 * 39: move 39 bit (from LSB to MSB)
 * 40-63: reserved
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2 . ERR_POSIT_OFFS_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_OFFS_CFG(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_OFFS_CFG     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_ERR_POSIT_OFFS_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * limited error insertion: burst mode (err_freq_cfg must be > 0)
 *
 * \details 
 * 0: burst mode is disabled 1-15: number of errors after each error
 * triggering = 2^(num_err_cfg + 5)
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2 . NUM_ERR_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_NUM_ERR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_NUM_ERR_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_TX_ERR_INSERT_CFG_2_NUM_ERR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief DFT clock generator configuration register
 *
 * \details
 * Configuration register for clock generator to build a low speed clock
 * signal of variable length and variable duty cycle provided on all data
 * bits simultaniously
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_GEN_CFG_1
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_1  VTSS_IOREG(0x01, 0, 0xb121)

/** 
 * \brief
 * (Half) clock period cfg in normal mode: high period = cg_per_cfg +
 * cg_dcd_cfg, low period = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_1 . CG_PER_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_1_CG_PER_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_1_CG_PER_CFG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_1_CG_PER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief DFT clock generator configuration register
 *
 * \details
 * Configuration register for clock generator to build a low speed clock
 * signal of variable length and variable duty cycle provided on all data
 * bits simultaniously
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_GEN_CFG_2
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_2  VTSS_IOREG(0x01, 0, 0xb122)

/** 
 * \brief
 * (Half) clock period cfg in jump mode: high period = cg_per_cfg +
 * cg_dcd_cfg, low period = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_2 . CG_PER_JUMP_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_2_CG_PER_JUMP_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_2_CG_PER_JUMP_CFG     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_2_CG_PER_JUMP_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief DFT clock generator configuration register
 *
 * \details
 * Configuration register for clock generator to build a low speed clock
 * signal of variable length and variable duty cycle provided on all data
 * bits simultaniously
 *
 * Register: \a VENICE_DEV1:SD10G65_DFT:DFT_CLK_GEN_CFG_3
 */
#define VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3  VTSS_IOREG(0x01, 0, 0xb123)

/** 
 * \brief
 * Duty cycle distortion: high period = cg_per_cfg + cg_dcd_cfg, low period
 * = cg_per_cfg - cg_dcd_cfg
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3 . CG_DCD_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_DCD_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,10)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_DCD_CFG     VTSS_ENCODE_BITMASK(2,10)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_DCD_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,10)

/** 
 * \brief
 * clock generator mode
 *
 * \details 
 * 0: normal operation
 * cg_per_cfg controls period; 0->1 transition: after current period has
 * finished (only) the next period is controlled by cg_per_jump_cfg
 * afterwards normal operation; 2: every N'th period the high value is
 * replaced by a low value
 * N is defined by cg_timer_cfg; 3: every N'th period the low value is
 * replaced by a high value
 * N is defined by cg_timer_cfg
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3 . CG_MODE_CFG
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_MODE_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_DFT_DFT_CLK_GEN_CFG_3_CG_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_DEV1:ROMENG_1
 *
 * Register Collection for Rom Engine 1
 */


/** 
 * \brief SPI address field of ROM table entry ... replication_count=135
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_1:spi_adr
 *
 * @param ri Register: spi_adr, 0-134
 */
#define VTSS_VENICE_DEV1_ROMENG_1_spi_adr(ri)  VTSS_IOREG(0x01, 0, 0xb200 | (ri))

/** 
 * \brief
 * SPI address to write
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_1_spi_adr . spi_adr
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_1_spi_adr_spi_adr(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VENICE_DEV1_ROMENG_1_spi_adr_spi_adr     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VENICE_DEV1_ROMENG_1_spi_adr_spi_adr(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Lower 16 bits of SPI data field of ROM table entry ... replication_count=135
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_1:data_lsw
 *
 * @param ri Register: data_lsw, 0-134
 */
#define VTSS_VENICE_DEV1_ROMENG_1_data_lsw(ri)  VTSS_IOREG(0x01, 0, 0xb300 | (ri))

/** 
 * \brief
 * SPI data lsw
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_1_data_lsw . spi_dat_lsw
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_1_data_lsw_spi_dat_lsw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_ROMENG_1_data_lsw_spi_dat_lsw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_ROMENG_1_data_lsw_spi_dat_lsw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Upper 16 bits of SPI data field of ROM table entry ... replication_count=135
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_1:data_msw
 *
 * @param ri Register: data_msw, 0-134
 */
#define VTSS_VENICE_DEV1_ROMENG_1_data_msw(ri)  VTSS_IOREG(0x01, 0, 0xb400 | (ri))

/** 
 * \brief
 * SPI data msw
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_1_data_msw . spi_dat_msw
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_1_data_msw_spi_dat_msw(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV1_ROMENG_1_data_msw_spi_dat_msw     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV1_ROMENG_1_data_msw_spi_dat_msw(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV1:ROMENG_2
 *
 * Register Collection for Rom Engine 2
 */


/** 
 * \brief ROM table start/end addresses of Tx 10G setting routine
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_2:adr_tx10g
 */
#define VTSS_VENICE_DEV1_ROMENG_2_adr_tx10g  VTSS_IOREG(0x01, 0, 0xb600)

/** 
 * \brief
 * Starting ROM address of Tx 10G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_tx10g . adr_tx10g_start
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_start(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_start     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_start(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Ending   ROM address of Tx 10G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_tx10g . adr_tx10g_end
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_end(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_end     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_tx10g_adr_tx10g_end(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ROM table start/end addresses of Rx 10G setting routine
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_2:adr_rx10g
 */
#define VTSS_VENICE_DEV1_ROMENG_2_adr_rx10g  VTSS_IOREG(0x01, 0, 0xb601)

/** 
 * \brief
 * Starting ROM address of Rx 10G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_rx10g . adr_rx10g_start
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_start(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_start     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_start(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Ending   ROM address of Rx 10G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_rx10g . adr_rx10g_end
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_end(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_end     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_rx10g_adr_rx10g_end(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ROM table start/end addresses of Tx 1G setting routine
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_2:adr_tx1g
 */
#define VTSS_VENICE_DEV1_ROMENG_2_adr_tx1g   VTSS_IOREG(0x01, 0, 0xb602)

/** 
 * \brief
 * Starting ROM address of Tx 1G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_tx1g . adr_tx1g_start
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_start(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_start     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_start(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Ending   ROM address of Tx 1G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_tx1g . adr_tx1g_end
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_end(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_end     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_tx1g_adr_tx1g_end(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ROM table start/end addresses of Rx 1G setting routine
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_2:adr_rx1g
 */
#define VTSS_VENICE_DEV1_ROMENG_2_adr_rx1g   VTSS_IOREG(0x01, 0, 0xb603)

/** 
 * \brief
 * Starting ROM address of Rx 1G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_rx1g . adr_rx1g_start
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_start(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_start     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_start(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Ending   ROM address of Rx 1G routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_rx1g . adr_rx1g_end
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_end(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_end     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_rx1g_adr_rx1g_end(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief ROM table start/end addresses of WAN setting routine
 *
 * \details
 * Register: \a VENICE_DEV1:ROMENG_2:adr_wan
 */
#define VTSS_VENICE_DEV1_ROMENG_2_adr_wan    VTSS_IOREG(0x01, 0, 0xb604)

/** 
 * \brief
 * Starting ROM address of WAN routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_wan . adr_wan_start
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_start(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_start     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_start(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Ending   ROM address of WAN routine
 *
 * \details 
 * Field: VTSS_VENICE_DEV1_ROMENG_2_adr_wan . adr_wan_end
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_end(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_end     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV1_ROMENG_2_adr_wan_adr_wan_end(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_DEV1:ROMENG_STATUS
 *
 * Rom Engine Status
 */


/** 
 * \brief Rom Engine Status
 *
 * \details
 * Rom Engine Status
 *
 * Register: \a VENICE_DEV1:ROMENG_STATUS:ROMENG_STATUS
 */
#define VTSS_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS  VTSS_IOREG(0x01, 0, 0xb6ff)

/** 
 * \brief
 * Rom Engine last routine executed
 *
 * \details 
 * 00000: 10G	- configured for 10G mode
 * 00001: TX10G - Tx configured for 10G mode
 * 00010: RX10G - Rx configured for 10G mode
 * 00011: 1G	- configured for 1G mode
 * 00100: TX1G	- Rx configured for 1G mode
 * 00101: RX1G	- Rx configured for 1G mode
 * 00110: 3G	- configured for 3G mode
 * 00111: TX3G	- Rx configured for 3G mode
 * 01000: RX3G	- Rx configured for 3G mode
 * 01001: WAN	- configured for WAN mode
 * 01010: RST	- configured to Reset condition
 * 01011: LBON	- configured for Loopback enabled
 * 01100: LBOFF - configured for Loopback disabled
 * 01101: LPON	- LowPower mode enabled
 * 01110: LPOFF - LowPower mode disabled
 * 01111: RC	- RCOMP routine
 * 10000: LRON	- Lock2Ref enabled
 * 10001: LROFF - Lock2Ref disabled
 * others: invalid
 *
 * Field: VTSS_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS . exe_last
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS_exe_last(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS_exe_last     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS_exe_last(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/** 
 * \brief
 * Rom Engine status
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.

 *
 * \details 
 * 0: Rom Engine has not executed a new routine since the last time this
 * bit is read
 * 1: Rom Engine has executed a new routine since the last time this bit is
 * read
 *
 * Field: VTSS_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS . exe_done
 */
#define  VTSS_F_VENICE_DEV1_ROMENG_STATUS_ROMENG_STATUS_exe_done  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:SD10G65_SYNC_CTRL
 *
 * SYNC_CTRL Configuration and Status Register set
 */


/** 
 * \brief SYNC_CTRL config register
 *
 * \details
 * Sync control configuration register
 *
 * Register: \a VENICE_DEV1:SD10G65_SYNC_CTRL:SYNC_CTRL_CFG
 */
#define VTSS_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG  VTSS_IOREG(0x01, 0, 0xb700)

/** 
 * \brief
 * Clear sync ctrl status register
 *
 * \details 
 * 0: Idle
 * 1: Clear
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG . CLR_SYNC_STAT
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_CLR_SYNC_STAT  VTSS_BIT(4)

/** 
 * \brief
 * Source selection for lane synchronization
 *
 * \details 
 * 0: Select DES_0
 * 1: Select DES_1
 * 2: Select F to Delta F
 * 3: Synchronization Disabled
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG . LANE_SYNC_SRC
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_CFG_LANE_SYNC_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SYNC_CTRL status register
 *
 * \details
 * Sync control status register
 *
 * Register: \a VENICE_DEV1:SD10G65_SYNC_CTRL:SYNC_CTRL_STAT
 */
#define VTSS_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT  VTSS_IOREG(0x01, 0, 0xb701)

/** 
 * \brief
 * Lane synchronization fifo overflow.	The status bit is cleared by a 1 to
 * CLR_SYNC_STAT.
 *
 * \details 
 * 0: FIFO normal operation
 * 1: FIFO overflow
 *
 * Field: VTSS_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT . LANE_SYNC_FIFO_OF
 */
#define  VTSS_F_VENICE_DEV1_SD10G65_SYNC_CTRL_SYNC_CTRL_STAT_LANE_SYNC_FIFO_OF  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST
 *
 * SD10G65 RX RCPLL BIST Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 0A
 *
 * \details
 * Configuration register 0A for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG0A
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG0A  VTSS_IOREG(0x01, 0, 0xb800)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 0B
 *
 * \details
 * Configuration register 0B for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG0B
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG0B  VTSS_IOREG(0x01, 0, 0xb801)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 1A
 *
 * \details
 * Configuration register 1A for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG1A
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG1A  VTSS_IOREG(0x01, 0, 0xb802)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 1B
 *
 * \details
 * Configuration register 1B for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG1B
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG1B  VTSS_IOREG(0x01, 0, 0xb803)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG2
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG2  VTSS_IOREG(0x01, 0, 0xb804)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG3
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG3  VTSS_IOREG(0x01, 0, 0xb805)


/** 
 * \brief SD10G65 RX RCPLL BIST Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_CFG4
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_CFG4  VTSS_IOREG(0x01, 0, 0xb806)


/** 
 * \brief SD10G65 RX RCPLL BIST Status register 0A
 *
 * \details
 * Status register 0A for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_STAT0A
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_STAT0A  VTSS_IOREG(0x01, 0, 0xb807)


/** 
 * \brief SD10G65 RX RCPLL BIST Status register 0B
 *
 * \details
 * Status register 0B for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_STAT0B
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_STAT0B  VTSS_IOREG(0x01, 0, 0xb808)


/** 
 * \brief SD10G65 RX RCPLL BIST Status register 1
 *
 * \details
 * Status register 1 for SD10G65 RX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_RX_RCPLL_BIST:SD10G65_RX_RCPLL_BIST_STAT1
 */
#define VTSS_VENICE_DEV1_SD10G65_RX_RCPLL_BIST_SD10G65_RX_RCPLL_BIST_STAT1  VTSS_IOREG(0x01, 0, 0xb809)

/**
 * Register Group: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST
 *
 * SD10G65 TX RCPLL BIST Configuration and Status Register set
 */


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 0A
 *
 * \details
 * Configuration register 0A for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG0A
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG0A  VTSS_IOREG(0x01, 0, 0xb810)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 0B
 *
 * \details
 * Configuration register 0B for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG0B
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG0B  VTSS_IOREG(0x01, 0, 0xb811)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 1A
 *
 * \details
 * Configuration register 1A for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG1A
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG1A  VTSS_IOREG(0x01, 0, 0xb812)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 1B
 *
 * \details
 * Configuration register 1B for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG1B
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG1B  VTSS_IOREG(0x01, 0, 0xb813)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG2
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG2  VTSS_IOREG(0x01, 0, 0xb814)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG3
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG3  VTSS_IOREG(0x01, 0, 0xb815)


/** 
 * \brief SD10G65 TX RCPLL BIST Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_CFG4
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_CFG4  VTSS_IOREG(0x01, 0, 0xb816)


/** 
 * \brief SD10G65 TX RCPLL BIST Status register 0A
 *
 * \details
 * Status register 0A for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_STAT0A
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_STAT0A  VTSS_IOREG(0x01, 0, 0xb817)


/** 
 * \brief SD10G65 TX RCPLL BIST Status register 0B
 *
 * \details
 * Status register 0B for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_STAT0B
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_STAT0B  VTSS_IOREG(0x01, 0, 0xb818)


/** 
 * \brief SD10G65 TX RCPLL BIST Status register 1
 *
 * \details
 * Status register 1 for SD10G65 TX RCPLL BIST.
 *
 * Register: \a VENICE_DEV1:SD10G65_TX_RCPLL_BIST:SD10G65_TX_RCPLL_BIST_STAT1
 */
#define VTSS_VENICE_DEV1_SD10G65_TX_RCPLL_BIST_SD10G65_TX_RCPLL_BIST_STAT1  VTSS_IOREG(0x01, 0, 0xb819)


#endif /* _VTSS_VENICE_REGS_VENICE_DEV1_H_ */
