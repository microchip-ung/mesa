// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_HOST_PCS10G_H_
#define _VTSS_MALIBU_REGS_HOST_PCS10G_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_PCS10G
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PCS10G:PCS_Control_1
 *
 * Not documented
 */


/** 
 * \brief PCS Control 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Control_1:PCS_Control_1
 */
#define VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1  VTSS_IOREG(0x0b, 0, 0x0000)

/** 
 * \brief
 * MDIO Managable Device (MMD) software reset.	Reset all logic in the
 * channel between the host side PMA and the line side PMA, regardless of
 * the cross-connect configuration.  Data path logic and configuration
 * registers are reset.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . SOFT_RST
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_SOFT_RST  VTSS_BIT(15)

/** 
 * \brief
 * PCS System loopback.  Loopback of 64b encoded and scrambled data
 *
 * \details 
 * 0: Disable PCS loopback mode
 * 1: Enable PCS loopback mode
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . PCS_System_loopback
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_PCS_System_loopback  VTSS_BIT(14)

/** 
 * \details 
 * 0: Unspecified
 * 1: Operation at 10 Gb/s and above
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . Speed_selection
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_Speed_selection  VTSS_BIT(13)

/** 
 * \brief
 * The channel's data path is placed into low power mode with this
 * register.  The PMA in this channel is also placed into low power mode
 * regardless of the channel cross connect configuration.  The
 * PMD_TRANSMIT_DISABLE.GLOBAL_PMD_TRANSMIT_DISABLE register state can can
 * be transmitted from a GPIO pin to shut off an optics module's TX driver.
 *
 * \details 
 * 0: Normal Operation
 * 1: Low Power Mode
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . LOW_PWR_PCS
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_LOW_PWR_PCS  VTSS_BIT(11)

/** 
 * \details 
 * 0: Unspecified
 * 1: Operation at 10 Gb/s and above
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . Speed_selection_idx2
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_Speed_selection_idx2  VTSS_BIT(6)

/** 
 * \details 
 * 1xxx: Reserved.
 * x1xx: Reserved.
 * xx1x: Reserved.
 * 0001: Reserved.
 * 0000: 10 Gbps
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_1_PCS_Control_1 . Speed_selection_idx3
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_1_PCS_Control_1_Speed_selection_idx3(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_HOST_PCS10G_PCS_Control_1_PCS_Control_1_Speed_selection_idx3     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_HOST_PCS10G_PCS_Control_1_PCS_Control_1_Speed_selection_idx3(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * Register Group: \a HOST_PCS10G:PCS_Status_1
 *
 * Not documented
 */


/** 
 * \brief PCS Status 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Status_1:PCS_Status_1
 */
#define VTSS_HOST_PCS10G_PCS_Status_1_PCS_Status_1  VTSS_IOREG(0x0b, 0, 0x0001)

/** 
 * \details 
 * 0: Fault condition not detected.  (PCS receive local fault
 * (PCS_Status_2.Receive_fault) = 0) AND (PCS transmit local fault
 * (PCS_Status_2.Transmit_fault) = 0)
 * 1: Fault condition detected. (PCS receive local fault
 * (PCS_Status_2.Receive_fault) = 1) OR (PCS transmit local fault
 * (PCS_Status_2.Transmit_fault) = 1)
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_1_PCS_Status_1 . Fault
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_1_PCS_Status_1_Fault  VTSS_BIT(7)

/** 
 * \brief
 * This is a sticky bit that latches the low state.  The latch-low bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: PCS received link down. BLOCK_LOCK=0 OR HI_BER=1
 * 1: PCS receive link up. BLOCK_LOCK=1 AND HI_BER=0.
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_1_PCS_Status_1 . PCS_receive_link_status
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_1_PCS_Status_1_PCS_receive_link_status  VTSS_BIT(2)

/** 
 * \details 
 * 0: PCS does not support low power mode
 * 1: PCS supports low power mode
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_1_PCS_Status_1 . Low_power_ability
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_1_PCS_Status_1_Low_power_ability  VTSS_BIT(1)

/**
 * Register Group: \a HOST_PCS10G:PCS_Device_Identifier
 *
 * Not documented
 */


/** 
 * \brief PCS Device Identifier 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Device_Identifier:PCS_Device_Identifier_1
 */
#define VTSS_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_1  VTSS_IOREG(0x0b, 0, 0x0002)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique PCS device identifier. Bits 3-18 of the
 * device manufacturer's OUI.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_1 . PCS_Device_Identifier_1
 */
#define  VTSS_F_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_1_PCS_Device_Identifier_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_1_PCS_Device_Identifier_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_1_PCS_Device_Identifier_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Device Identifier 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Device_Identifier:PCS_Device_Identifier_2
 */
#define VTSS_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_2  VTSS_IOREG(0x0b, 0, 0x0003)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique PCS device identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number, and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_2 . PCS_Device_Identifier_2
 */
#define  VTSS_F_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_2_PCS_Device_Identifier_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_2_PCS_Device_Identifier_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Device_Identifier_PCS_Device_Identifier_2_PCS_Device_Identifier_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_Speed_Ability
 *
 * Not documented
 */


/** 
 * \brief PCS Speed Ability
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Speed_Ability:PCS_Speed_Ability
 */
#define VTSS_HOST_PCS10G_PCS_Speed_Ability_PCS_Speed_Ability  VTSS_IOREG(0x0b, 0, 0x0004)

/** 
 * \details 
 * 0: Not capable of 10Gbps
 * 1: Capable of 10Gbps
 *
 * Field: VTSS_HOST_PCS10G_PCS_Speed_Ability_PCS_Speed_Ability . is_10G_capable
 */
#define  VTSS_F_HOST_PCS10G_PCS_Speed_Ability_PCS_Speed_Ability_is_10G_capable  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_Devices_in_Package_1
 *
 * Not documented
 */


/** 
 * \brief PCS Devices in Package 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Devices_in_Package_1:PCS_Devices_in_Package_1
 */
#define VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1  VTSS_IOREG(0x0b, 0, 0x0005)

/** 
 * \brief
 * Indicates whether DTE XS is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . DTE_XS_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_DTE_XS_present  VTSS_BIT(5)

/** 
 * \brief
 * Indicates whether PHY XS is present in the package 
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . PHY_XS_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_PHY_XS_present  VTSS_BIT(4)

/** 
 * \brief
 * Indicates whether PCS is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . PCS_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_PCS_present  VTSS_BIT(3)

/** 
 * \brief
 * Indicates whether WIS is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . WIS_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_WIS_present  VTSS_BIT(2)

/** 
 * \brief
 * Indicates whether PMA/PMD is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . PMD_PMA_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_PMD_PMA_present  VTSS_BIT(1)

/** 
 * \brief
 * Indicates whether Clause 22 registers are present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1 . Clause_22_registers_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_1_PCS_Devices_in_Package_1_Clause_22_registers_present  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_Devices_in_Package_2
 *
 * Not documented
 */


/** 
 * \brief PCS Devices in Package 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Devices_in_Package_2:PCS_Devices_in_Package_2
 */
#define VTSS_HOST_PCS10G_PCS_Devices_in_Package_2_PCS_Devices_in_Package_2  VTSS_IOREG(0x0b, 0, 0x0006)

/** 
 * \brief
 * Indicates whether vendor specific device 2 is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_2_PCS_Devices_in_Package_2 . Vendor_spec_dev_2_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_2_PCS_Devices_in_Package_2_Vendor_spec_dev_2_present  VTSS_BIT(15)

/** 
 * \brief
 * Indicates whether vendor specific device 1 is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_HOST_PCS10G_PCS_Devices_in_Package_2_PCS_Devices_in_Package_2 . Vendor_spec_dev_1_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Devices_in_Package_2_PCS_Devices_in_Package_2_Vendor_spec_dev_1_present  VTSS_BIT(14)

/**
 * Register Group: \a HOST_PCS10G:PCS_Control_2
 *
 * Not documented
 */


/** 
 * \brief PCS Control 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Control_2:PCS_Control_2
 */
#define VTSS_HOST_PCS10G_PCS_Control_2_PCS_Control_2  VTSS_IOREG(0x0b, 0, 0x0007)

/** 
 * \brief
 * Indicates the PCS type selected
 *
 * \details 
 * 11: Reserved
 * 10: 10GBASE-W PCS
 * 01: Reserved
 * 00: 10GBASE-R PCS
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_2_PCS_Control_2 . Select_WAN_mode_or_10GBASE_R
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_2_PCS_Control_2_Select_WAN_mode_or_10GBASE_R(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PCS10G_PCS_Control_2_PCS_Control_2_Select_WAN_mode_or_10GBASE_R     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PCS10G_PCS_Control_2_PCS_Control_2_Select_WAN_mode_or_10GBASE_R(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HOST_PCS10G:PCS_Status_2
 *
 * Not documented
 */


/** 
 * \brief PCS Status 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Status_2:PCS_Status_2
 */
#define VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2  VTSS_IOREG(0x0b, 0, 0x0008)

/** 
 * \details 
 * 00: No device responding at this address
 * 01: No device responding at this address
 * 10: Device responding at this address
 * 11: No device responding at this address
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . Device_present
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_Device_present(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HOST_PCS10G_PCS_Status_2_PCS_Status_2_Device_present     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HOST_PCS10G_PCS_Status_2_PCS_Status_2_Device_present(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No fault condition on transmit path
 * 1: Fault condition on transmit path
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . Transmit_fault
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_Transmit_fault  VTSS_BIT(11)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No fault condition on receive path
 * 1: Fault condition on receive path
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . Receive_fault
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_Receive_fault  VTSS_BIT(10)

/** 
 * \details 
 * 0: Not supported
 * 1: Supported
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . is_10GBASE_W_ability
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_is_10GBASE_W_ability  VTSS_BIT(2)

/** 
 * \details 
 * 0: Not supported
 * 1: Supported
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . is_10GBASE_X_ability
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_is_10GBASE_X_ability  VTSS_BIT(1)

/** 
 * \details 
 * 0: Not supported
 * 1: Supported
 *
 * Field: VTSS_HOST_PCS10G_PCS_Status_2_PCS_Status_2 . is_10GBASE_R_ability
 */
#define  VTSS_F_HOST_PCS10G_PCS_Status_2_PCS_Status_2_is_10GBASE_R_ability  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_Package_Identifier
 *
 * Not documented
 */


/** 
 * \brief PCS Package Identifier 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Package_Identifier:PCS_Package_Identifier_1
 */
#define VTSS_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_1  VTSS_IOREG(0x0b, 0, 0x000e)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique PCS package identifier. Bits 3-18 of
 * the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_1 . PCS_package_identifier_1
 */
#define  VTSS_F_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_1_PCS_package_identifier_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_1_PCS_package_identifier_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_1_PCS_package_identifier_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Package Identifier 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Package_Identifier:PCS_Package_Identifier_2
 */
#define VTSS_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_2  VTSS_IOREG(0x0b, 0, 0x000f)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique PCS package identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_2 . PCS_package_identifier_2
 */
#define  VTSS_F_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_2_PCS_package_identifier_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_2_PCS_package_identifier_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Package_Identifier_PCS_Package_Identifier_2_PCS_package_identifier_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:Eth_10Gbase_X_Status
 *
 * Not documented
 */


/** 
 * \brief Eth_10Gbase-X Status
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10Gbase_X_Status:Eth_10Gbase_X_Status
 */
#define VTSS_HOST_PCS10G_Eth_10Gbase_X_Status_Eth_10Gbase_X_Status  VTSS_IOREG(0x0b, 0, 0x0018)

/** 
 * \brief
 * Not supported
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10Gbase_X_Status_Eth_10Gbase_X_Status . is_10Gbase_X_Status
 */
#define  VTSS_F_HOST_PCS10G_Eth_10Gbase_X_Status_Eth_10Gbase_X_Status_is_10Gbase_X_Status(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10Gbase_X_Status_Eth_10Gbase_X_Status_is_10Gbase_X_Status     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10Gbase_X_Status_Eth_10Gbase_X_Status_is_10Gbase_X_Status(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:Eth_10Gbase_X_Control
 *
 * Not documented
 */


/** 
 * \brief Eth_10Gbase-X Control
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10Gbase_X_Control:Eth_10Gbase_X_Control
 */
#define VTSS_HOST_PCS10G_Eth_10Gbase_X_Control_Eth_10Gbase_X_Control  VTSS_IOREG(0x0b, 0, 0x0019)

/** 
 * \brief
 * Not supported
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10Gbase_X_Control_Eth_10Gbase_X_Control . is_10Gbase_X_Control
 */
#define  VTSS_F_HOST_PCS10G_Eth_10Gbase_X_Control_Eth_10Gbase_X_Control_is_10Gbase_X_Control(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10Gbase_X_Control_Eth_10Gbase_X_Control_is_10Gbase_X_Control     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10Gbase_X_Control_Eth_10Gbase_X_Control_is_10Gbase_X_Control(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Status_1
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS Status 1
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Status_1:Eth_10GBASE_R_PCS_Status_1
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1  VTSS_IOREG(0x0b, 0, 0x0020)

/** 
 * \details 
 * 0: 10GBASE-R PCS receive link down BLOCK_LOCK
 * (Eth_10GBASE_R_PCS_Status_1.is_10GBASE_R_PCS_block_lock) = 0 OR BER_HI
 * (Eth_10GBASE_R_PCS_Status_1.is_10GBASE_R_PCS_high_BER) = 1
 * 1: 10GBASE-R PCS receive link up BLOCK_LOCK
 * (Eth_10GBASE_R_PCS_Status_1.is_10GBASE_R_PCS_block_lock) = 1 AND BER_HI
 * (Eth_10GBASE_R_PCS_Status_1.is_10GBASE_R_PCS_high_BER) = 0
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1 . is_10GBASE_R_receive_lock_status
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1_is_10GBASE_R_receive_lock_status  VTSS_BIT(12)

/** 
 * \details 
 * 0: PCS does not support PRBS31 pattern testing
 * 1: PCS is able to support PRBS31 pattern testing
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1 . PRBS31_pattern_testing_ability
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1_PRBS31_pattern_testing_ability  VTSS_BIT(2)

/** 
 * \details 
 * 0: 10GBASE-R PCS not reporting a high BER.
 * 1: 10GBASE-R PCS reporting a high BER.
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1 . is_10GBASE_R_PCS_high_BER
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1_is_10GBASE_R_PCS_high_BER  VTSS_BIT(1)

/** 
 * \details 
 * 0: 10GBASE-R PCS is not locked to receive blocks.
 * 1: 10GBASE-R PCS is locked to receive blocks.
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1 . is_10GBASE_R_PCS_block_lock
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_1_Eth_10GBASE_R_PCS_Status_1_is_10GBASE_R_PCS_block_lock  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Status_2
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS Status 2
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Status_2:Eth_10GBASE_R_PCS_Status_2
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2  VTSS_IOREG(0x0b, 0, 0x0021)

/** 
 * \brief
 * This is a sticky bit that latches the low state.  The latch-low bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: 10GBASE-R PCS does not have block lock
 * 1: 10GBASE-R PCS has block lock
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2 . BLOCK_LOCK
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_BLOCK_LOCK  VTSS_BIT(15)

/** 
 * \brief
 * This is a sticky bit that latches the high state.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: 10GBASE-R PCS has not reported a high BER
 * 1: 10GBASE-R PCS has reported a high BER
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2 . PCS_HIGHBER
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_PCS_HIGHBER  VTSS_BIT(14)

/** 
 * \brief
 * BER counter.  The counter saturates when the maximum value is exceeded. 
 * The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2 . BER
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_BER(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_BER     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_BER(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Errored blocks counter.  The counter saturates when the maximum value is
 * exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2 . PCS_ERRORED_BLOCKS
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_PCS_ERRORED_BLOCKS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_PCS_ERRORED_BLOCKS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Status_2_Eth_10GBASE_R_PCS_Status_2_PCS_ERRORED_BLOCKS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed A 0
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0  VTSS_IOREG(0x0b, 0, 0x0022)

/** 
 * \brief
 * Test pattern seed A bits 0-15
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0 . PCS_SEEDA_0
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0_PCS_SEEDA_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0_PCS_SEEDA_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_0_PCS_SEEDA_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed A 1
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1  VTSS_IOREG(0x0b, 0, 0x0023)

/** 
 * \brief
 * Test pattern seed A bits 16-31
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1 . PCS_SEEDA_1
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1_PCS_SEEDA_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1_PCS_SEEDA_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_1_PCS_SEEDA_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed A 2
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2  VTSS_IOREG(0x0b, 0, 0x0024)

/** 
 * \brief
 * Test pattern seed A bits 32-47
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2 . PCS_SEEDA_2
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2_PCS_SEEDA_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2_PCS_SEEDA_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_2_PCS_SEEDA_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed A 3
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A:Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3  VTSS_IOREG(0x0b, 0, 0x0025)

/** 
 * \brief
 * Test pattern seed A bits 48-57
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3 . PCS_SEEDA_3
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3_PCS_SEEDA_3(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3_PCS_SEEDA_3     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_Eth_10GBASE_R_PCS_Test_Pattern_Seed_A_3_PCS_SEEDA_3(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed B 0
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0  VTSS_IOREG(0x0b, 0, 0x0026)

/** 
 * \brief
 * Test pattern seed B bits 0-15
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0 . PCS_SEEDB_0
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0_PCS_SEEDB_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0_PCS_SEEDB_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_0_PCS_SEEDB_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed B 1
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1  VTSS_IOREG(0x0b, 0, 0x0027)

/** 
 * \brief
 * Test pattern seed B bits 16-31
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1 . PCS_SEEDB_1
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1_PCS_SEEDB_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1_PCS_SEEDB_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_1_PCS_SEEDB_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed B 2
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2  VTSS_IOREG(0x0b, 0, 0x0028)

/** 
 * \brief
 * Test pattern seed B bits 32-47
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2 . PCS_SEEDB_2
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2_PCS_SEEDB_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2_PCS_SEEDB_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_2_PCS_SEEDB_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Eth_10GBASE-R PCS Test Pattern Seed B 3
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B:Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3  VTSS_IOREG(0x0b, 0, 0x0029)

/** 
 * \brief
 * Test pattern seed B bits 48-57
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3 . PCS_SEEDB_3
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3_PCS_SEEDB_3(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3_PCS_SEEDB_3     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_Eth_10GBASE_R_PCS_Test_Pattern_Seed_B_3_PCS_SEEDB_3(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_test_pattern_control
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS test-pattern control
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_test_pattern_control:Eth_10GBASE_R_PCS_test_pattern_control
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control  VTSS_IOREG(0x0b, 0, 0x002a)

/** 
 * \details 
 * 0: Disable PRBS31 test pattern mode on the receive path
 * 1: Enable PRBS31 test pattern mode on the receive path
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_PRBS31_ANA
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_PRBS31_ANA  VTSS_BIT(5)

/** 
 * \details 
 * 0: Disable PRBS31 test pattern mode on the transmit path
 * 1: Enable PRBS31 test pattern mode on the transmit path
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_PRBS31_GEN
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_PRBS31_GEN  VTSS_BIT(4)

/** 
 * \details 
 * 0: Disable transmit test pattern
 * 1: Enable transmit test pattern
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_TSTPAT_GEN
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_TSTPAT_GEN  VTSS_BIT(3)

/** 
 * \details 
 * 0: Disable receive test pattern
 * 1: Enable receive test pattern
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_TSTPAT_ENA
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_TSTPAT_ENA  VTSS_BIT(2)

/** 
 * \details 
 * 0: Pseudo random test pattern
 * 1: Square wave test pattern
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_TSTPAT_SEL
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_TSTPAT_SEL  VTSS_BIT(1)

/** 
 * \details 
 * 0: LF data pettern
 * 1: Zero data pattern
 *
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control . PCS_TSTDAT_SEL
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_control_Eth_10GBASE_R_PCS_test_pattern_control_PCS_TSTDAT_SEL  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:Eth_10GBASE_R_PCS_test_pattern_counter
 *
 * Not documented
 */


/** 
 * \brief Eth_10GBASE-R PCS test-pattern counter
 *
 * \details
 * Register: \a HOST_PCS10G:Eth_10GBASE_R_PCS_test_pattern_counter:Eth_10GBASE_R_PCS_test_pattern_counter
 */
#define VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_counter_Eth_10GBASE_R_PCS_test_pattern_counter  VTSS_IOREG(0x0b, 0, 0x002b)

/** 
 * \brief
 * (COR) Error counter
 *	     This is the 16-bit test pattern error counter defined by IEEE.
 *  The counter is cleared upon read of this register.	There is a 32-bit
 * version of this counter in registers Test_Error_Counter_0 and
 * Test_Error_Counter_1.  If reading the 32-bit version, read
 * Test_Error_Counter_1, followed by Test_Error_Counter_0.  A read of
 * register Test_Error_Counter_0 or Eth_10GBASE_R_PCS_test_pattern_counter
 * will clear the 32-bit error counter.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_counter_Eth_10GBASE_R_PCS_test_pattern_counter . PCS_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_counter_Eth_10GBASE_R_PCS_test_pattern_counter_PCS_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_counter_Eth_10GBASE_R_PCS_test_pattern_counter_PCS_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Eth_10GBASE_R_PCS_test_pattern_counter_Eth_10GBASE_R_PCS_test_pattern_counter_PCS_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:USR_Test
 *
 * Not documented
 */


/** 
 * \brief USR Test 0
 *
 * \details
 * Register: \a HOST_PCS10G:USR_Test:USR_Test_0
 */
#define VTSS_HOST_PCS10G_USR_Test_USR_Test_0  VTSS_IOREG(0x0b, 0, 0x8000)

/** 
 * \brief
 * User-defined data pattern [15:0]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_USR_Test_USR_Test_0 . PCS_USRPAT_0
 */
#define  VTSS_F_HOST_PCS10G_USR_Test_USR_Test_0_PCS_USRPAT_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_USR_Test_USR_Test_0_PCS_USRPAT_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_USR_Test_USR_Test_0_PCS_USRPAT_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief USR Test 1
 *
 * \details
 * Register: \a HOST_PCS10G:USR_Test:USR_Test_1
 */
#define VTSS_HOST_PCS10G_USR_Test_USR_Test_1  VTSS_IOREG(0x0b, 0, 0x8001)

/** 
 * \brief
 * User-defined data pattern [31:16]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_USR_Test_USR_Test_1 . PCS_USRPAT_1
 */
#define  VTSS_F_HOST_PCS10G_USR_Test_USR_Test_1_PCS_USRPAT_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_USR_Test_USR_Test_1_PCS_USRPAT_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_USR_Test_USR_Test_1_PCS_USRPAT_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief USR Test 2
 *
 * \details
 * Register: \a HOST_PCS10G:USR_Test:USR_Test_2
 */
#define VTSS_HOST_PCS10G_USR_Test_USR_Test_2  VTSS_IOREG(0x0b, 0, 0x8002)

/** 
 * \brief
 * User-defined data pattern [47:32]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_USR_Test_USR_Test_2 . PCS_USRPAT_2
 */
#define  VTSS_F_HOST_PCS10G_USR_Test_USR_Test_2_PCS_USRPAT_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_USR_Test_USR_Test_2_PCS_USRPAT_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_USR_Test_USR_Test_2_PCS_USRPAT_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief USR Test 3
 *
 * \details
 * Register: \a HOST_PCS10G:USR_Test:USR_Test_3
 */
#define VTSS_HOST_PCS10G_USR_Test_USR_Test_3  VTSS_IOREG(0x0b, 0, 0x8003)

/** 
 * \brief
 * User-defined data pattern [63:48]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_USR_Test_USR_Test_3 . PCS_USRPAT_3
 */
#define  VTSS_F_HOST_PCS10G_USR_Test_USR_Test_3_PCS_USRPAT_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_USR_Test_USR_Test_3_PCS_USRPAT_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_USR_Test_USR_Test_3_PCS_USRPAT_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:Square_Wave_Pulse_Width
 *
 * Not documented
 */


/** 
 * \brief Square Wave Pulse Width
 *
 * \details
 * Register: \a HOST_PCS10G:Square_Wave_Pulse_Width:Square_Wave_Pulse_Width
 */
#define VTSS_HOST_PCS10G_Square_Wave_Pulse_Width_Square_Wave_Pulse_Width  VTSS_IOREG(0x0b, 0, 0x8004)

/** 
 * \brief
 * Square wave pulse width
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Square_Wave_Pulse_Width_Square_Wave_Pulse_Width . PCS_SQPW
 */
#define  VTSS_F_HOST_PCS10G_Square_Wave_Pulse_Width_Square_Wave_Pulse_Width_PCS_SQPW(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HOST_PCS10G_Square_Wave_Pulse_Width_Square_Wave_Pulse_Width_PCS_SQPW     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HOST_PCS10G_Square_Wave_Pulse_Width_Square_Wave_Pulse_Width_PCS_SQPW(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a HOST_PCS10G:PCS_Control_3
 *
 * Not documented
 */


/** 
 * \brief PCS Control 3
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Control_3:PCS_Control_3
 */
#define VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3  VTSS_IOREG(0x0b, 0, 0x8005)

/** 
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3 . DSCR_DIS
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_3_PCS_Control_3_DSCR_DIS  VTSS_BIT(10)

/** 
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3 . SCR_DIS
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_3_PCS_Control_3_SCR_DIS  VTSS_BIT(9)

/** 
 * \details 
 * 0: Blocks errors are  generated when an invalid block sequence is
 * encoutnered in the Rx path
 * 1: Blocks errors are not generated when an invalid block sequence is
 * encoutnered in the Rx path
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3 . Disable_RX_block_sequence_check
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_3_PCS_Control_3_Disable_RX_block_sequence_check  VTSS_BIT(5)

/** 
 * \details 
 * 0: Blocks errors are  generated when an invalid block sequence is
 * encoutnered in the Tx path
 * 1: Blocks errors are not generated when an invalid block sequence is
 * encoutnered in the Tx path
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3 . Disable_TX_block_sequence_check
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_3_PCS_Control_3_Disable_TX_block_sequence_check  VTSS_BIT(4)

/** 
 * \brief
 * User test pattern enable
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_3_PCS_Control_3 . PCS_USRPAT_ENA
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_3_PCS_Control_3_PCS_USRPAT_ENA  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:Test_Error_Counter
 *
 * Not documented
 */


/** 
 * \brief Test Error Counter 0
 *
 * \details
 * Register: \a HOST_PCS10G:Test_Error_Counter:Test_Error_Counter_0
 */
#define VTSS_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_0  VTSS_IOREG(0x0b, 0, 0x8007)

/** 
 * \brief
 * (COR) Lower 16 bits of 32-bit version of PCS_ERR_CNT
 * (Eth_10GBASE_R_PCS_test_pattern_counter)
 *	     This register should only be read directly after reading
 * Test_Error_Counter_1.  Upon read of this register or
 * Eth_10GBASE_R_PCS_test_pattern_counter, the 32-bit error counter is
 * cleared.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_0 . PCS_VSERR_CNT_0
 */
#define  VTSS_F_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_0_PCS_VSERR_CNT_0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_0_PCS_VSERR_CNT_0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_0_PCS_VSERR_CNT_0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Test Error Counter 1
 *
 * \details
 * Register: \a HOST_PCS10G:Test_Error_Counter:Test_Error_Counter_1
 */
#define VTSS_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_1  VTSS_IOREG(0x0b, 0, 0x8008)

/** 
 * \brief
 * (COR) Upper 16 bits of 32-bit version of PCS_ERR_CNT
 * (Eth_10GBASE_R_PCS_test_pattern_counter)
 *	     This register should be read, followed immediately by
 * Test_Error_Counter_0.  Upon read of Test_Error_Counter_0 or
 * Eth_10GBASE_R_PCS_test_pattern_counter, the 32-bit error counter is
 * cleared.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_1 . PCS_VSERR_CNT_1
 */
#define  VTSS_F_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_1_PCS_VSERR_CNT_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_1_PCS_VSERR_CNT_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_Test_Error_Counter_Test_Error_Counter_1_PCS_VSERR_CNT_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_TX_SEQ_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Tx Sequencing Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_TX_SEQ_ERR_CNT:PCS_TX_SEQ_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_TX_SEQ_ERR_CNT_PCS_TX_SEQ_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8010)

/** 
 * \brief
 * Tx sequencing error count.  The counter saturates when the maximum value
 * is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_TX_SEQ_ERR_CNT_PCS_TX_SEQ_ERR_CNT . TX_SEQ_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_TX_SEQ_ERR_CNT_PCS_TX_SEQ_ERR_CNT_TX_SEQ_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_TX_SEQ_ERR_CNT_PCS_TX_SEQ_ERR_CNT_TX_SEQ_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_TX_SEQ_ERR_CNT_PCS_TX_SEQ_ERR_CNT_TX_SEQ_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_RX_SEQ_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Rx Sequencing Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_RX_SEQ_ERR_CNT:PCS_RX_SEQ_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_RX_SEQ_ERR_CNT_PCS_RX_SEQ_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8011)

/** 
 * \brief
 * RX sequencing error count.  The counter saturates when the maximum value
 * is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_RX_SEQ_ERR_CNT_PCS_RX_SEQ_ERR_CNT . RX_SEQ_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_RX_SEQ_ERR_CNT_PCS_RX_SEQ_ERR_CNT_RX_SEQ_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_RX_SEQ_ERR_CNT_PCS_RX_SEQ_ERR_CNT_RX_SEQ_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_RX_SEQ_ERR_CNT_PCS_RX_SEQ_ERR_CNT_RX_SEQ_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_TX_BLK_ENC_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Tx Block Encode Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_TX_BLK_ENC_ERR_CNT:PCS_TX_BLK_ENC_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_TX_BLK_ENC_ERR_CNT_PCS_TX_BLK_ENC_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8012)

/** 
 * \brief
 * Tx block encode error count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_TX_BLK_ENC_ERR_CNT_PCS_TX_BLK_ENC_ERR_CNT . TX_BLK_ENC_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_TX_BLK_ENC_ERR_CNT_PCS_TX_BLK_ENC_ERR_CNT_TX_BLK_ENC_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_TX_BLK_ENC_ERR_CNT_PCS_TX_BLK_ENC_ERR_CNT_TX_BLK_ENC_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_TX_BLK_ENC_ERR_CNT_PCS_TX_BLK_ENC_ERR_CNT_TX_BLK_ENC_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_PCS_RX_BLK_DEC_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Rx Block Decode Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_PCS_RX_BLK_DEC_ERR_CNT:PCS_PCS_RX_BLK_DEC_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_PCS_RX_BLK_DEC_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8013)

/** 
 * \brief
 * Rx block decode error count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_PCS_RX_BLK_DEC_ERR_CNT . PCS_RX_BLK_DEC_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_RX_BLK_DEC_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_RX_BLK_DEC_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_PCS_RX_BLK_DEC_ERR_CNT_PCS_RX_BLK_DEC_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_TX_CHAR_ENC_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Tx Character Encode Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_TX_CHAR_ENC_ERR_CNT:PCS_TX_CHAR_ENC_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_TX_CHAR_ENC_ERR_CNT_PCS_TX_CHAR_ENC_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8014)

/** 
 * \brief
 * Tx character encode error count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_TX_CHAR_ENC_ERR_CNT_PCS_TX_CHAR_ENC_ERR_CNT . TX_CHAR_ENC_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_TX_CHAR_ENC_ERR_CNT_PCS_TX_CHAR_ENC_ERR_CNT_TX_CHAR_ENC_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_TX_CHAR_ENC_ERR_CNT_PCS_TX_CHAR_ENC_ERR_CNT_TX_CHAR_ENC_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_TX_CHAR_ENC_ERR_CNT_PCS_TX_CHAR_ENC_ERR_CNT_TX_CHAR_ENC_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_RX_CHAR_DEC_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief PCS Rx Character Decode Error Count
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_RX_CHAR_DEC_ERR_CNT:PCS_RX_CHAR_DEC_ERR_CNT
 */
#define VTSS_HOST_PCS10G_PCS_RX_CHAR_DEC_ERR_CNT_PCS_RX_CHAR_DEC_ERR_CNT  VTSS_IOREG(0x0b, 0, 0x8015)

/** 
 * \brief
 * Rx character decode error count.  The counter saturates when the maximum
 * value is exceeded.  The counter is cleared when the register is read.
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_RX_CHAR_DEC_ERR_CNT_PCS_RX_CHAR_DEC_ERR_CNT . RX_CHAR_DEC_ERR_CNT
 */
#define  VTSS_F_HOST_PCS10G_PCS_RX_CHAR_DEC_ERR_CNT_PCS_RX_CHAR_DEC_ERR_CNT_RX_CHAR_DEC_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_RX_CHAR_DEC_ERR_CNT_PCS_RX_CHAR_DEC_ERR_CNT_RX_CHAR_DEC_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_RX_CHAR_DEC_ERR_CNT_PCS_RX_CHAR_DEC_ERR_CNT_RX_CHAR_DEC_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:Loopback_FIFOs_Stat_Ctrl
 *
 * Not documented
 */


/** 
 * \brief Loopback FIFOs Stat/Ctrl
 *
 * \details
 * Register: \a HOST_PCS10G:Loopback_FIFOs_Stat_Ctrl:Loopback_FIFOs_Stat_Ctrl
 */
#define VTSS_HOST_PCS10G_Loopback_FIFOs_Stat_Ctrl_Loopback_FIFOs_Stat_Ctrl  VTSS_IOREG(0x0b, 0, 0x8016)

/** 
 * \brief
 * Loopback_64b FIFO overflow status.  This is a sticky bit that latches
 * the high state.  The latch-high bit is cleared when the register is
 * read.
 *
 * \details 
 * 0: normal operation
 * 1: over/under flow condition
 *
 * Field: VTSS_HOST_PCS10G_Loopback_FIFOs_Stat_Ctrl_Loopback_FIFOs_Stat_Ctrl . Loop_64b_FIFO_Overflow
 */
#define  VTSS_F_HOST_PCS10G_Loopback_FIFOs_Stat_Ctrl_Loopback_FIFOs_Stat_Ctrl_Loop_64b_FIFO_Overflow  VTSS_BIT(1)

/** 
 * \brief
 * Selects whether loopback_64b FIFO's sync inhibit feature is enabled.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_HOST_PCS10G_Loopback_FIFOs_Stat_Ctrl_Loopback_FIFOs_Stat_Ctrl . Loop_64b_FIFO_Sync_Inhibit
 */
#define  VTSS_F_HOST_PCS10G_Loopback_FIFOs_Stat_Ctrl_Loopback_FIFOs_Stat_Ctrl_Loop_64b_FIFO_Sync_Inhibit  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_Control_4
 *
 * Not documented
 */


/** 
 * \brief PCS Control 4
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Control_4:PCS_Control_4
 */
#define VTSS_HOST_PCS10G_PCS_Control_4_PCS_Control_4  VTSS_IOREG(0x0b, 0, 0x8600)

/** 
 * \details 
 * 0:  Inversion is enabled
 * 1: Disable inversion of input pattern during PRBS58 test pattern
 * generation
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_4_PCS_Control_4 . Disable_inversion_of_input_pattern
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_4_PCS_Control_4_Disable_inversion_of_input_pattern  VTSS_BIT(1)

/** 
 * \details 
 * 0: rx_status = block_lock
 * 1: rx_status = block_lock * !hi_ber (IEEE compliant)
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_4_PCS_Control_4 . RX_fault_sel
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_4_PCS_Control_4_RX_fault_sel  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_Control_5
 *
 * Not documented
 */


/** 
 * \brief PCS Control 5
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Control_5:PCS_Control_5
 */
#define VTSS_HOST_PCS10G_PCS_Control_5_PCS_Control_5  VTSS_IOREG(0x0b, 0, 0x8601)

/** 
 * \brief
 * Enables re-mapping of Local_Faults to Idles in Tx path
 *
 * \details 
 * 0: Disable re-mapping
 * 1: Enable re-mapping
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_5_PCS_Control_5 . TX_LF_FILT_EN
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_5_PCS_Control_5_TX_LF_FILT_EN  VTSS_BIT(1)

/** 
 * \brief
 * Enable re-mapping of Local_Faults to Idles in Rx path
 *
 * \details 
 * 0: Disable re-mapping
 * 1: Enable re-mapping
 *
 * Field: VTSS_HOST_PCS10G_PCS_Control_5_PCS_Control_5 . RX_LF_FILT_EN
 */
#define  VTSS_F_HOST_PCS10G_PCS_Control_5_PCS_Control_5_RX_LF_FILT_EN  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_LF_filt_linkup_timer
 *
 * Not documented
 */


/** 
 * \brief PCS LF_filt linkup timer
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_LF_filt_linkup_timer:PCS_LF_filt_linkup_timer
 */
#define VTSS_HOST_PCS10G_PCS_LF_filt_linkup_timer_PCS_LF_filt_linkup_timer  VTSS_IOREG(0x0b, 0, 0x8602)

/** 
 * \brief
 * When no LF's, the filt_timer block will count up to this value before
 * enabling filters. The counter increments once every 49.6ns
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_LF_filt_linkup_timer_PCS_LF_filt_linkup_timer . LF_FILT_UP_TMR
 */
#define  VTSS_F_HOST_PCS10G_PCS_LF_filt_linkup_timer_PCS_LF_filt_linkup_timer_LF_FILT_UP_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_LF_filt_linkup_timer_PCS_LF_filt_linkup_timer_LF_FILT_UP_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_LF_filt_linkup_timer_PCS_LF_filt_linkup_timer_LF_FILT_UP_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_LF_filt_linkdown_timer
 *
 * Not documented
 */


/** 
 * \brief PCS LF_filt linkdown timer
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_LF_filt_linkdown_timer:PCS_LF_filt_linkdown_timer
 */
#define VTSS_HOST_PCS10G_PCS_LF_filt_linkdown_timer_PCS_LF_filt_linkdown_timer  VTSS_IOREG(0x0b, 0, 0x8603)

/** 
 * \brief
 * Upon stream of LF's, the filt_timer block will count up to this value
 * before disabling filters. The counter increments once every 49.6ns
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_LF_filt_linkdown_timer_PCS_LF_filt_linkdown_timer . LF_FILT_DOWN_TMR
 */
#define  VTSS_F_HOST_PCS10G_PCS_LF_filt_linkdown_timer_PCS_LF_filt_linkdown_timer_LF_FILT_DOWN_TMR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_LF_filt_linkdown_timer_PCS_LF_filt_linkdown_timer_LF_FILT_DOWN_TMR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_LF_filt_linkdown_timer_PCS_LF_filt_linkdown_timer_LF_FILT_DOWN_TMR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_INTR_PEND1
 *
 * Not documented
 */


/** 
 * \brief PCS Interrupt Pending 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_INTR_PEND1:PCS_INTR_PEND1
 */
#define VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1  VTSS_IOREG(0x0b, 0, 0x8e00)

/** 
 * \brief
 * The interrupt pending bit is asserted when the status signal driving
 * PCS_Status_1::PCS_RECEIVE_LINK_STATUS changes state.  The sticky bit is
 * cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . RX_LINK_STAT_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_RX_LINK_STAT_INTR_PEND  VTSS_BIT(9)

/** 
 * \brief
 * The interrupt pending bit is asserted when
 * Eth_10GBASE_R_PCS_Status_2::PCS_HIGHBER status changes state.  The
 * sticky bit is cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . HIGHBER_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_HIGHBER_INTR_PEND  VTSS_BIT(8)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * KR_FEC_CORRECTED_BLOCKS counter exceeds the FEC_FIXED_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . FEC_FIXED_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_FEC_FIXED_CNT_THRESH_INTR_PEND  VTSS_BIT(7)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * KR_FEC_UNCORRECTED_BLOCKS counter exceeds the FEC_UNFIXED_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . FEC_UNFIXED_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_FEC_UNFIXED_CNT_THRESH_INTR_PEND  VTSS_BIT(6)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_TX_SEQ_ERR_CNT counter exceeds the TX_SEQ_ERR_CNT_THRESH value.	The
 * bit is asserted when the counter transitions from being less than the
 * threshold to being greater than the threshold.  The sticky bit is
 * cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . TX_SEQ_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_TX_SEQ_CNT_THRESH_INTR_PEND  VTSS_BIT(5)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_RX_SEQ_ERR_CNT counter exceeds the RX_SEQ_ERR_CNT_THRESH value.	The
 * bit is asserted when the counter transitions from being less than the
 * threshold to being greater than the threshold.  The sticky bit is
 * cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . RX_SEQ_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_RX_SEQ_CNT_THRESH_INTR_PEND  VTSS_BIT(4)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_TX_BLK_ENC_ERR_CNT counter exceeds the TX_BLK_ENC_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . TX_BLK_ENC_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_TX_BLK_ENC_CNT_THRESH_INTR_PEND  VTSS_BIT(3)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_RX_BLK_DEC_ERR_CNT counter exceeds the RX_BLK_DEC_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . RX_BLK_DEC_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_RX_BLK_DEC_CNT_THRESH_INTR_PEND  VTSS_BIT(2)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_TX_CHAR_ENC_ERR_CNT counter exceeds the TX_CHAR_ENC_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . TX_CHAR_ENC_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_TX_CHAR_ENC_CNT_THRESH_INTR_PEND  VTSS_BIT(1)

/** 
 * \brief
 * This interrupt pending register bit is asserted when the
 * PCS_RX_CHAR_DEC_ERR_CNT counter exceeds the RX_CHAR_DEC_ERR_CNT_THRESH
 * value.  The bit is asserted when the counter transitions from being less
 * than the threshold to being greater than the threshold.  The sticky bit
 * is cleared when a 1 is written to the bit.
 *
 * \details 
 * 0: An interrupt event has not occurred.
 * 1: An interrupt event has occurred.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1 . RX_CHAR_DEC_CNT_THRESH_INTR_PEND
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_PEND1_PCS_INTR_PEND1_RX_CHAR_DEC_CNT_THRESH_INTR_PEND  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_INTR_MASK1
 *
 * Not documented
 */


/** 
 * \brief PCS Interrupt Mask 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_INTR_MASK1:PCS_INTR_MASK1
 */
#define VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1  VTSS_IOREG(0x0b, 0, 0x8e01)

/** 
 * \brief
 * Interrupt mask for RX_LINK_STAT_INTR_PEND.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . RX_LINK_STAT_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_RX_LINK_STAT_MASK  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt mask for HIGHBER_INTR_PEND.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . HIGHBER_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_HIGHBER_MASK  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt mask for KR_FEC_CORRECTED_BLOCKS error counter exceeding
 * threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . FEC_FIXED_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_FEC_FIXED_CNT_THRESH_MASK  VTSS_BIT(7)

/** 
 * \brief
 * Interrupt mask for KR_FEC_UNCORRECTED_BLOCKS error counter exceeding
 * threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . FEC_UNFIXED_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_FEC_UNFIXED_CNT_THRESH_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt mask for PCS_TX_SEQ_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . TX_SEQ_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_TX_SEQ_CNT_THRESH_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for PCS_RX_SEQ_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . RX_SEQ_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_RX_SEQ_CNT_THRESH_MASK  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt mask for PCS_TX_BLK_ENC_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . TX_BLK_ENC_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_TX_BLK_ENC_CNT_THRESH_MASK  VTSS_BIT(3)

/** 
 * \brief
 * Interrupt mask for PCS_RX_BLK_DEC_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . RX_BLK_DEC_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_RX_BLK_DEC_CNT_THRESH_MASK  VTSS_BIT(2)

/** 
 * \brief
 * Interrupt mask for PCS_TX_CHAR_ENC_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . TX_CHAR_ENC_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_TX_CHAR_ENC_CNT_THRESH_MASK  VTSS_BIT(1)

/** 
 * \brief
 * Interrupt mask for PCS_RX_CHAR_DEC_ERR_CNT exceeding threshold level.
 *
 * \details 
 * 0: Interrupt disabled
 * 1: Interrupt enabled
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1 . RX_CHAR_DEC_CNT_THRESH_MASK
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_MASK1_PCS_INTR_MASK1_RX_CHAR_DEC_CNT_THRESH_MASK  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:PCS_INTR_STATUS
 *
 * Not documented
 */


/** 
 * \brief PCS Interrupt Status Signals
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_INTR_STATUS:PCS_INTR_STATUS
 */
#define VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS  VTSS_IOREG(0x0b, 0, 0x8e03)

/** 
 * \brief
 * This is the status signal used to assert the RX_LINK_STAT_INTR_PEND
 * register.  It is the same status used to assert the latch-low
 * PCS_Status_1::PCS_RECEIVE_LINK_STATUS register.
 *
 * \details 
 * 0: PCS received link down. BLOCK_LOCK=0 OR HI_BER=1
 * 1: PCS receive link up. BLOCK_LOCK=1 AND HI_BER=0.
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . PCS_receive_link_status
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_PCS_receive_link_status  VTSS_BIT(9)

/** 
 * \brief
 * This is the status signal used to assert the HIGHBER_INTR_PEND register.
 *  It is the same status used to assert the latch-high
 * Eth_10GBASE_R_PCS_Status_2::PCS_HIGHBER register.
 *
 * \details 
 * 0: 10GBASE-R PCS has not reported a high BER
 * 1: 10GBASE-R PCS has reported a high BER
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . PCS_HIGHBER
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_PCS_HIGHBER  VTSS_BIT(8)

/** 
 * \brief
 * Present result of comparing KR FEC's corrected block count
 * (KR_FEC_CORRECTED_UPPER/KR_FEC_CORRECTED_LOWER) to the threshold setting
 * in FEC_FIXED_ERR_CNT_THRESH1/FEC_FIXED_ERR_CNT_THRESH0.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . FEC_FIXED_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_FEC_FIXED_THRESH_COMP  VTSS_BIT(7)

/** 
 * \brief
 * Present result of comparing KR FEC's uncorrectable block count
 * (KR_FEC_UNCORRECTED_UPPER/KR_FEC_UNCORRECTED_LOWER) to the threshold
 * setting in FEC_UNFIXED_ERR_CNT_THRESH1/FEC_UNFIXED_ERR_CNT_THRESH0.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . FEC_UNFIXED_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_FEC_UNFIXED_THRESH_COMP  VTSS_BIT(6)

/** 
 * \brief
 * Present result of comparing TX sequencing error count
 * (PCS_TX_SEQ_ERR_CNT) to the threshold setting in register
 * TX_SEQ_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . TX_SEQ_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_TX_SEQ_THRESH_COMP  VTSS_BIT(5)

/** 
 * \brief
 * Present result of comparing RX sequencing error count
 * (PCS_RX_SEQ_ERR_CNT) to the threshold setting in register
 * RX_SEQ_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . RX_SEQ_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_RX_SEQ_THRESH_COMP  VTSS_BIT(4)

/** 
 * \brief
 * Present result of comparing TX block encode error count
 * (PCS_TX_BLK_ENC_ERR_CNT) to the threshold setting in register
 * TX_BLK_ENC_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . TX_BLK_ENC_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_TX_BLK_ENC_THRESH_COMP  VTSS_BIT(3)

/** 
 * \brief
 * Present result of comparing RX block decode error count
 * (PCS_RX_BLK_DEC_ERR_CNT) to the threshold setting in register
 * RX_BLK_DEC_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . RX_BLK_DEC_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_RX_BLK_DEC_THRESH_COMP  VTSS_BIT(2)

/** 
 * \brief
 * Present result of comparing TX character encode error count
 * (PCS_TX_CHAR_ENC_ERR_CNT) to the threshold setting in register
 * TX_CHAR_ENC_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . TX_CHAR_ENC_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_TX_CHAR_ENC_THRESH_COMP  VTSS_BIT(1)

/** 
 * \brief
 * Present result of comparing RX character decode error count
 * (PCS_RX_CHAR_DEC_ERR_CNT) to the threshold setting in register
 * RX_CHAR_DEC_ERR_CNT_THRESH.
 *
 * \details 
 * 0: counter does not exceed threshold setting
 * 1: counter exceeds threshold setting
 *
 * Field: VTSS_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS . RX_CHAR_DEC_THRESH_COMP
 */
#define  VTSS_F_HOST_PCS10G_PCS_INTR_STATUS_PCS_INTR_STATUS_RX_CHAR_DEC_THRESH_COMP  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL
 *
 * Not documented
 */


/** 
 * \brief TX Sequencing Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:TX_SEQ_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_SEQ_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e04)

/** 
 * \brief
 * TX sequencing error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_SEQ_ERR_CNT_THRESH . TX_SEQ_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_SEQ_ERR_CNT_THRESH_TX_SEQ_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_SEQ_ERR_CNT_THRESH_TX_SEQ_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_SEQ_ERR_CNT_THRESH_TX_SEQ_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX Sequencing Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:RX_SEQ_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_SEQ_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e05)

/** 
 * \brief
 * RX sequencing error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_SEQ_ERR_CNT_THRESH . RX_SEQ_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_SEQ_ERR_CNT_THRESH_RX_SEQ_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_SEQ_ERR_CNT_THRESH_RX_SEQ_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_SEQ_ERR_CNT_THRESH_RX_SEQ_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief TX Block Encode Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:TX_BLK_ENC_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_BLK_ENC_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e06)

/** 
 * \brief
 * TX block encode error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_BLK_ENC_ERR_CNT_THRESH . TX_BLK_ENC_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_BLK_ENC_ERR_CNT_THRESH_TX_BLK_ENC_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_BLK_ENC_ERR_CNT_THRESH_TX_BLK_ENC_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_BLK_ENC_ERR_CNT_THRESH_TX_BLK_ENC_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX Block Decode Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:RX_BLK_DEC_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_BLK_DEC_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e07)

/** 
 * \brief
 * RX block decode error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_BLK_DEC_ERR_CNT_THRESH . RX_BLK_DEC_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_BLK_DEC_ERR_CNT_THRESH_RX_BLK_DEC_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_BLK_DEC_ERR_CNT_THRESH_RX_BLK_DEC_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_BLK_DEC_ERR_CNT_THRESH_RX_BLK_DEC_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief TX Character Encode Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:TX_CHAR_ENC_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_CHAR_ENC_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e08)

/** 
 * \brief
 * TX character encode error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_CHAR_ENC_ERR_CNT_THRESH . TX_CHAR_ENC_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_CHAR_ENC_ERR_CNT_THRESH_TX_CHAR_ENC_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_CHAR_ENC_ERR_CNT_THRESH_TX_CHAR_ENC_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_TX_CHAR_ENC_ERR_CNT_THRESH_TX_CHAR_ENC_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX Character Decode Error Count Threshold
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:RX_CHAR_DEC_ERR_CNT_THRESH
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_CHAR_DEC_ERR_CNT_THRESH  VTSS_IOREG(0x0b, 0, 0x8e09)

/** 
 * \brief
 * RX character decode error count threshold
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_CHAR_DEC_ERR_CNT_THRESH . RX_CHAR_DEC_ERR_CNT_THRESH
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_CHAR_DEC_ERR_CNT_THRESH_RX_CHAR_DEC_ERR_CNT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_CHAR_DEC_ERR_CNT_THRESH_RX_CHAR_DEC_ERR_CNT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_RX_CHAR_DEC_ERR_CNT_THRESH_RX_CHAR_DEC_ERR_CNT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FEC Fixed Error Count Threshold 1
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:FEC_FIXED_ERR_CNT_THRESH1
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH1  VTSS_IOREG(0x0b, 0, 0x8e0a)

/** 
 * \brief
 * FEC fixed error count Threshold[31:16]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH1 . FEC_FIXED_ERR_CNT_THRESH1
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH1_FEC_FIXED_ERR_CNT_THRESH1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH1_FEC_FIXED_ERR_CNT_THRESH1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH1_FEC_FIXED_ERR_CNT_THRESH1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FEC Fixed Error Count Threshold 0
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:FEC_FIXED_ERR_CNT_THRESH0
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH0  VTSS_IOREG(0x0b, 0, 0x8e0b)

/** 
 * \brief
 * FEC fixed error count Threshold[15:0]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH0 . FEC_FIXED_ERR_CNT_THRESH0
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH0_FEC_FIXED_ERR_CNT_THRESH0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH0_FEC_FIXED_ERR_CNT_THRESH0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_FIXED_ERR_CNT_THRESH0_FEC_FIXED_ERR_CNT_THRESH0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FEC Unfixable Error Count Threshold 1
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:FEC_UNFIXED_ERR_CNT_THRESH1
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH1  VTSS_IOREG(0x0b, 0, 0x8e0c)

/** 
 * \brief
 * FEC unfixable error count Threshold[31:16]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH1 . FEC_UNFIXED_ERR_CNT_THRESH1
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH1_FEC_UNFIXED_ERR_CNT_THRESH1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH1_FEC_UNFIXED_ERR_CNT_THRESH1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH1_FEC_UNFIXED_ERR_CNT_THRESH1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief FEC Unfixable Error Count Threshold 0
 *
 * \details
 * Register: \a HOST_PCS10G:INTR_THRESHOLD_LEVEL:FEC_UNFIXED_ERR_CNT_THRESH0
 */
#define VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH0  VTSS_IOREG(0x0b, 0, 0x8e0d)

/** 
 * \brief
 * FEC unfixable error count Threshold[15:0]
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH0 . FEC_UNFIXED_ERR_CNT_THRESH0
 */
#define  VTSS_F_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH0_FEC_UNFIXED_ERR_CNT_THRESH0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH0_FEC_UNFIXED_ERR_CNT_THRESH0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_INTR_THRESHOLD_LEVEL_FEC_UNFIXED_ERR_CNT_THRESH0_FEC_UNFIXED_ERR_CNT_THRESH0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PCS10G:PCS_Spare_CFG_STAT
 *
 * Not documented
 */


/** 
 * \brief PCS Spare Control 0
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_0
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_0  VTSS_IOREG(0x0b, 0, 0x8f00)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_0 . Spare_cfg0
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_0_Spare_cfg0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_0_Spare_cfg0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_0_Spare_cfg0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_1
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_1  VTSS_IOREG(0x0b, 0, 0x8f01)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_1 . Spare_cfg1
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_1_Spare_cfg1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_1_Spare_cfg1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_1_Spare_cfg1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_2
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_2  VTSS_IOREG(0x0b, 0, 0x8f02)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_2 . Spare_cfg2
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_2_Spare_cfg2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_2_Spare_cfg2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_2_Spare_cfg2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 3
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_3
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_3  VTSS_IOREG(0x0b, 0, 0x8f03)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_3 . Spare_cfg3
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_3_Spare_cfg3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_3_Spare_cfg3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_3_Spare_cfg3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 4
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_4
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_4  VTSS_IOREG(0x0b, 0, 0x8f04)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_4 . Spare_cfg4
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_4_Spare_cfg4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_4_Spare_cfg4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_4_Spare_cfg4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 5
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_5
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_5  VTSS_IOREG(0x0b, 0, 0x8f05)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_5 . Spare_cfg5
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_5_Spare_cfg5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_5_Spare_cfg5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_5_Spare_cfg5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 6
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_6
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_6  VTSS_IOREG(0x0b, 0, 0x8f06)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_6 . Spare_cfg6
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_6_Spare_cfg6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_6_Spare_cfg6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_6_Spare_cfg6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 7
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_7
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_7  VTSS_IOREG(0x0b, 0, 0x8f07)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_7 . Spare_cfg7
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_7_Spare_cfg7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_7_Spare_cfg7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_7_Spare_cfg7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 8
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_8
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_8  VTSS_IOREG(0x0b, 0, 0x8f08)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_8 . Spare_cfg8
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_8_Spare_cfg8(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_8_Spare_cfg8     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_8_Spare_cfg8(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 9
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_9
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_9  VTSS_IOREG(0x0b, 0, 0x8f09)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_9 . Spare_cfg9
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_9_Spare_cfg9(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_9_Spare_cfg9     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_9_Spare_cfg9(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 10
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_10
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_10  VTSS_IOREG(0x0b, 0, 0x8f0a)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_10 . Spare_cfg10
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_10_Spare_cfg10(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_10_Spare_cfg10     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_10_Spare_cfg10(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 11
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_11
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_11  VTSS_IOREG(0x0b, 0, 0x8f0b)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_11 . Spare_cfg11
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_11_Spare_cfg11(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_11_Spare_cfg11     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_11_Spare_cfg11(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 12
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_12
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_12  VTSS_IOREG(0x0b, 0, 0x8f0c)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_12 . Spare_cfg12
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_12_Spare_cfg12(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_12_Spare_cfg12     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_12_Spare_cfg12(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 13
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_13
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_13  VTSS_IOREG(0x0b, 0, 0x8f0d)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_13 . Spare_cfg13
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_13_Spare_cfg13(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_13_Spare_cfg13     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_13_Spare_cfg13(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 14
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_14
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_14  VTSS_IOREG(0x0b, 0, 0x8f0e)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_14 . Spare_cfg14
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_14_Spare_cfg14(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_14_Spare_cfg14     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_14_Spare_cfg14(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Control 15
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Control_15
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_15  VTSS_IOREG(0x0b, 0, 0x8f0f)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_15 . Spare_cfg15
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_15_Spare_cfg15(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_15_Spare_cfg15     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Control_15_Spare_cfg15(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 0
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_0
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_0  VTSS_IOREG(0x0b, 0, 0x8f10)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_0 . Spare_stat0
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_0_Spare_stat0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_0_Spare_stat0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_0_Spare_stat0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 1
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_1
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_1  VTSS_IOREG(0x0b, 0, 0x8f11)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_1 . Spare_stat1
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_1_Spare_stat1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_1_Spare_stat1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_1_Spare_stat1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 2
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_2
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_2  VTSS_IOREG(0x0b, 0, 0x8f12)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_2 . Spare_stat2
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_2_Spare_stat2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_2_Spare_stat2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_2_Spare_stat2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 3
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_3
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_3  VTSS_IOREG(0x0b, 0, 0x8f13)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_3 . Spare_stat3
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_3_Spare_stat3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_3_Spare_stat3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_3_Spare_stat3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 4
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_4
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_4  VTSS_IOREG(0x0b, 0, 0x8f14)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_4 . Spare_stat4
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_4_Spare_stat4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_4_Spare_stat4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_4_Spare_stat4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Spare Status 5
 *
 * \details
 * Register: \a HOST_PCS10G:PCS_Spare_CFG_STAT:PCS_Spare_Status_5
 */
#define VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_5  VTSS_IOREG(0x0b, 0, 0x8f15)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_5 . Spare_stat5
 */
#define  VTSS_F_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_5_Spare_stat5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_5_Spare_stat5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PCS10G_PCS_Spare_CFG_STAT_PCS_Spare_Status_5_Spare_stat5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_MALIBU_REGS_HOST_PCS10G_H_ */
