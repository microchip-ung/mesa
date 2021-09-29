// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_VENICE_DEV4_H_
#define _VTSS_VENICE_REGS_VENICE_DEV4_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VENICE_DEV4
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Control_1
 *
 * Not documented
 */


/** 
 * \brief PHY XS Control 1
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Control_1:PHY_XS_Control_1
 */
#define VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1  VTSS_IOREG(0x04, 0, 0x0000)

/** 
 * \brief
 * MDIO Managable Device (MMD) software reset.	This register resets all
 * portions of the channel on the host side of the failover mux.  Data path
 * logic and configuration registers are reset.
 *
 * \details 
 * 0: Normal operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . SOFT_RST
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SOFT_RST  VTSS_BIT(15)

/** 
 * \brief
 * Enable PHY XS Network loopback (Loopback L1)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . LPBK_L1
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_LPBK_L1  VTSS_BIT(14)

/** 
 * \brief
 * PHY XS Speed capability
 *
 * \details 
 * 0: Unspecified
 * 1: Operates at 10 Gbps or above
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . SPEED_SEL_A
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SPEED_SEL_A  VTSS_BIT(13)

/** 
 * \brief
 * PHY XS low power mode control.  The channel's data path is placed into
 * low power mode with this register.  The PMA in this channel is also
 * placed into low power mode regardless of the channel cross connect
 * configuration.  The PMD_TRANSMIT_DISABLE.GLOBAL_PMD_TRANSMIT_DISABLE
 * register state can can be transmitted from a GPIO pin to shut off an
 * optics module's TX driver.
 *
 * \details 
 * 0: Normal Operation
 * 1: Low Power Mode
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . LOW_PWR_PHYXS
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_LOW_PWR_PHYXS  VTSS_BIT(11)

/** 
 * \brief
 * Speed selection
 *
 * \details 
 * 0: Unspecified
 * 1: Operation at 10 Gb/s and above
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . SPEED_SEL_B
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SPEED_SEL_B  VTSS_BIT(6)

/** 
 * \brief
 * Speed selection
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1 . SPEED_SEL_C
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SPEED_SEL_C(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SPEED_SEL_C     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_VENICE_DEV4_PHY_XS_Control_1_PHY_XS_Control_1_SPEED_SEL_C(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Status_1
 *
 * Not documented
 */


/** 
 * \brief PHY XS Status1
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Status_1:PHY_XS_Status_1
 */
#define VTSS_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1  VTSS_IOREG(0x04, 0, 0x0001)

/** 
 * \brief
 * PHY XS fault status. Asserted when either PHY_XS_Status_2:FAULT_RX or
 * PHY_XS_Status_2:FAULT_TX are asserted.
 *
 * \details 
 * 0: No faults asserted
 * 1: Fault(s) asserted
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1 . Fault
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1_Fault  VTSS_BIT(7)

/** 
 * \brief
 * PHY XS transmit link status.  The latch-low bit is cleared when the
 * register is read.
 *
 * \details 
 * 0: PHY XS transmit link is down (PHY_XS_Status_3.LANES_ALIGNED = 0)
 * 1: PHY XS transmit link is up (PHY_XS_Status_3.LANES_ALIGNED = 1) 
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1 . PHY_XS_transmit_link_status
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1_PHY_XS_transmit_link_status  VTSS_BIT(2)

/** 
 * \brief
 * Low power mode support ability
 *
 * \details 
 * 0: Not supported
 * 1: Supported
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1 . Low_power_ability
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_1_PHY_XS_Status_1_Low_power_ability  VTSS_BIT(1)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Device_Identifier
 *
 * Not documented
 */


/** 
 * \brief PHY XS Device Identifier 1
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Device_Identifier:PHY_XS_Device_Identifier_1
 */
#define VTSS_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_1  VTSS_IOREG(0x04, 0, 0x0002)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique PHY XS device identifier. Bits 3-18 of
 * the device manufacturer's OUI.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_1 . DEV_ID_MSW
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_1_DEV_ID_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_1_DEV_ID_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_1_DEV_ID_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PHY XS Device Identifier 2
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Device_Identifier:PHY_XS_Device_Identifier_2
 */
#define VTSS_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_2  VTSS_IOREG(0x04, 0, 0x0003)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique PHY XS device identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number, and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_2 . DEV_ID_LSW
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_2_DEV_ID_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_2_DEV_ID_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_PHY_XS_Device_Identifier_PHY_XS_Device_Identifier_2_DEV_ID_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Speed_Capability
 *
 * Not documented
 */


/** 
 * \brief PHY XS Speed Capability
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Speed_Capability:PHY_XS_Speed_Capability
 */
#define VTSS_VENICE_DEV4_PHY_XS_Speed_Capability_PHY_XS_Speed_Capability  VTSS_IOREG(0x04, 0, 0x0004)

/** 
 * \brief
 * PHY XS rate capability
 *
 * \details 
 * 0: Not capable of 10 Gbps
 * 1: Capable of 10 Gbps
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Speed_Capability_PHY_XS_Speed_Capability . RATE_ABILITY
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Speed_Capability_PHY_XS_Speed_Capability_RATE_ABILITY  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Devices_in_Package
 *
 * Not documented
 */


/** 
 * \brief PHY XS Devices in Package 1
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Devices_in_Package:PHY_XS_Devices_in_Package_1
 */
#define VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1  VTSS_IOREG(0x04, 0, 0x0005)

/** 
 * \brief
 * Indicates whether device includes DTS XS
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . DTE_XS_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_DTE_XS_PRES  VTSS_BIT(5)

/** 
 * \brief
 * Indicates whether device includes PHY XS
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . PHY_XS_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_PHY_XS_PRES  VTSS_BIT(4)

/** 
 * \brief
 * Indicates whether PCS is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . PCS_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_PCS_PRES  VTSS_BIT(3)

/** 
 * \brief
 * Indicates whether device includes WIS
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . WIS_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_WIS_PRES  VTSS_BIT(2)

/** 
 * \brief
 * Indicates whether PMA/PMD is present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . PMD_PMA_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_PMD_PMA_PRES  VTSS_BIT(1)

/** 
 * \brief
 * Indicates whether Clause 22 registers are present in the package
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1 . CLS22_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_1_CLS22_PRES  VTSS_BIT(0)


/** 
 * \brief PHY XS Devices in Package 2
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Devices_in_Package:PHY_XS_Devices_in_Package_2
 */
#define VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_2  VTSS_IOREG(0x04, 0, 0x0006)

/** 
 * \brief
 * Vendor specific device 2 present
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_2 . VS2_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_2_VS2_PRES  VTSS_BIT(15)

/** 
 * \brief
 * Vendor specific device 1 present
 *
 * \details 
 * 0: Not present
 * 1: Present
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_2 . VS1_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Devices_in_Package_PHY_XS_Devices_in_Package_2_VS1_PRES  VTSS_BIT(14)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Status_2
 *
 * Not documented
 */


/** 
 * \brief PHY XS Status 2
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Status_2:PHY_XS_Status_2
 */
#define VTSS_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2  VTSS_IOREG(0x04, 0, 0x0008)

/** 
 * \brief
 * Reflects the presence of a MMD responding at this address
 *
 * \details 
 * 10: Device responding at this address
 * 11: No device responding at this address
 * 10: No device responding at this address
 * 00: No device responding at this address
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2 . DEV_PRES
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2_DEV_PRES(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2_DEV_PRES     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2_DEV_PRES(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Indicates a fault condition on the transmit path.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: No fault condition.  XGXS lanes are aligned,
 * PHY_XS_Status_3.LANES_ALIGNED=1 and no Tx FIFO underflow/overflow
 * condition.
 * 1: Fault condition.	XGXS lanes are not aligned,
 * PHY_XS_Status_3.LANES_ALIGNED=0, or Tx FIFO had underflow/overflow
 * condition. 
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2 . FAULT_TX
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2_FAULT_TX  VTSS_BIT(11)

/** 
 * \brief
 * Indicates a fault condition on the receive path.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0: Rx PCS is locked to the data, and is not reporting a high bit error
 * rate, and no Rx FIFO underflow/overflow condition.
 * 1: Rx PCS block is not locked to the data, or is reporting a high bit
 * error rate, or Rx FIFO had underflow/overflow condition.  
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2 . FAULT_RX
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_2_PHY_XS_Status_2_FAULT_RX  VTSS_BIT(10)

/**
 * Register Group: \a VENICE_DEV4:PHYXS_Package_Identifier
 *
 * Not documented
 */


/** 
 * \brief PHYXS Package Identifier 1
 *
 * \details
 * Register: \a VENICE_DEV4:PHYXS_Package_Identifier:PHYXS_Package_Identifier_1
 */
#define VTSS_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_1  VTSS_IOREG(0x04, 0, 0x0009)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique PHY XS package identifier. Bits 3-18 of
 * the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_1 . PKG_ID_MSW
 */
#define  VTSS_F_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_1_PKG_ID_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_1_PKG_ID_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_1_PKG_ID_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PHYXS Package Identifier 2
 *
 * \details
 * Register: \a VENICE_DEV4:PHYXS_Package_Identifier:PHYXS_Package_Identifier_2
 */
#define VTSS_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_2  VTSS_IOREG(0x04, 0, 0x000a)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique PHY XS package identifier. Bits 19-24
 * of the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_2 . PKG_ID_LSW
 */
#define  VTSS_F_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_2_PKG_ID_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_2_PKG_ID_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_PHYXS_Package_Identifier_PHYXS_Package_Identifier_2_PKG_ID_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV4:PHY_XS_Status_3
 *
 * Not documented
 */


/** 
 * \brief PHY XS Status 3
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XS_Status_3:PHY_XS_Status_3
 */
#define VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3  VTSS_IOREG(0x04, 0, 0x0018)

/** 
 * \brief
 * PHY XGXS lane alignment status.
 * Register bit applies only when the device is operating in 10G mode.
 *
 * \details 
 * 0: Incoming PHY XS transmit path lanes are not aligned.
 * 1: Incoming PHY XS transmit path lanes are aligned.
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LANES_ALIGNED
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LANES_ALIGNED  VTSS_BIT(12)

/** 
 * \brief
 * PHY XGXS test pattern generation ability
 *
 * \details 
 * 0: PHY XS is not able to generate test patterns.
 * 1: PHY XS is able to generate test patterns.
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . PATT_ABILITY
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_PATT_ABILITY  VTSS_BIT(11)

/** 
 * \brief
 * PHY XGXS loopback ability
 *
 * \details 
 * 0: PHY XS does not have the ability to perform a loopback function
 * 1: PHY XS has the ability to perform a loopback function
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LPBK_ABILITY
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LPBK_ABILITY  VTSS_BIT(10)

/** 
 * \brief
 * PHY XGXS lane 3 synchronization status.
 * Register bit applies only when the device is operating in 10G mode and
 * the XAUI client interface is enabled.  This lane is not used in 10G
 * RXAUI mode.	Status bit does not apply in 1G mode.
 *
 * \details 
 * 0: Not synchronized
 * 1: Synchronized
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LANE3_SYNC
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LANE3_SYNC  VTSS_BIT(3)

/** 
 * \brief
 * PHY XGXS lane 2 synchronization status.
 * Register bit applies only when the device is operating in 10G mode.
 *
 * \details 
 * 0: Not synchronized
 * 1: Synchronized
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LANE2_SYNC
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LANE2_SYNC  VTSS_BIT(2)

/** 
 * \brief
 * PHY XGXS lane 1 synchronization status.
 * Register bit applies only when the device is operating in 10G mode and
 * the XAUI client interface is enabled.  This lane is not used in 10G
 * RXAUI mode.	Status bit does not apply in 1G mode.
 *
 * \details 
 * 0: Not synchronized
 * 1: Synchronized
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LANE1_SYNC
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LANE1_SYNC  VTSS_BIT(1)

/** 
 * \brief
 * PHY XGXS lane 0 synchronization status.
 * Register bit applies only when the device is operating in 10G mode.
 *
 * \details 
 * 0: Not synchronized
 * 1: Synchronized
 *
 * Field: VTSS_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3 . LANE0_SYNC
 */
#define  VTSS_F_VENICE_DEV4_PHY_XS_Status_3_PHY_XS_Status_3_LANE0_SYNC  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_DEV4:PHY_XGXS_Test_Control_1
 *
 * Not documented
 */


/** 
 * \brief PHY XGXS Test Control 1
 *
 * \details
 * Register: \a VENICE_DEV4:PHY_XGXS_Test_Control_1:PHY_XGXS_Test_Control_1
 */
#define VTSS_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1  VTSS_IOREG(0x04, 0, 0x0019)

/** 
 * \brief
 * PHYXS test pattern generator enable
 * Not supported, implemented elsewhere in the XGXS
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1 . TST_PATT_GEN_ENA
 */
#define  VTSS_F_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1_TST_PATT_GEN_ENA  VTSS_BIT(2)

/** 
 * \brief
 * PHYXS test pattern generator selection
 * Not supported, implemented elsewhere in the XGXS
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1 . TST_PATT_GEN_SEL1
 */
#define  VTSS_F_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1_TST_PATT_GEN_SEL1(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1_TST_PATT_GEN_SEL1     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VENICE_DEV4_PHY_XGXS_Test_Control_1_PHY_XGXS_Test_Control_1_TST_PATT_GEN_SEL1(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VENICE_DEV4:SERDES6G_DIG_CFG
 *
 * SERDES6G Digital Configuration Registers
 */


/** 
 * \brief SERDES6G Digital Configuration register
 *
 * \details
 * Configuration register for SERDES6G digital functions
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DIG_CFG
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG  VTSS_IOREG(0x04, 0, 0xe600)

/** 
 * \brief
 * Signal detect assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 35 us
 * 2: 70 us
 * 3: 105 us
 * 4: 140 us
 * 5..7: reserved
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_AST
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Signal detect de-assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 250 us
 * 2: 350 us
 * 3: 450 us
 * 4: 550 us
 * 5..7: reserved
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_DST
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G DFT Configuration register 0
 *
 * \details
 * Configuration register 0 for SERDES6G DFT functions
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG0
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0  VTSS_IOREG(0x04, 0, 0xe601)


/** 
 * \brief SERDES6G DFT Configuration register 1A
 *
 * \details
 * Configuration register 1A for SERDES6G DFT functions (TX direction)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG1A
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1A  VTSS_IOREG(0x04, 0, 0xe602)


/** 
 * \brief SERDES6G DFT Configuration register 1B
 *
 * \details
 * Configuration register 1B for SERDES6G DFT functions (TX direction)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG1B
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1B  VTSS_IOREG(0x04, 0, 0xe603)


/** 
 * \brief SERDES6G DFT Configuration register 2A
 *
 * \details
 * Configuration register 2A for SERDES6G DFT functions (RX direction)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG2A
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2A  VTSS_IOREG(0x04, 0, 0xe604)


/** 
 * \brief SERDES6G DFT Configuration register 2B
 *
 * \details
 * Configuration register 2B for SERDES6G DFT functions (RX direction)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG2B
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2B  VTSS_IOREG(0x04, 0, 0xe605)


/** 
 * \brief SERDES6G Test Pattern Configuration A
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_TP_CFG0A
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0A  VTSS_IOREG(0x04, 0, 0xe606)


/** 
 * \brief SERDES6G Test Pattern Configuration B
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_TP_CFG0B
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0B  VTSS_IOREG(0x04, 0, 0xe607)


/** 
 * \brief SERDES6G Test Pattern Configuration A
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern) and
 * Lane_cfg.hr_mode_ena = '0'. In 20 bit modes bits from static_pattern and
 * static_pattern2 are transmitted alternating.
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_TP_CFG1A
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1A  VTSS_IOREG(0x04, 0, 0xe608)


/** 
 * \brief SERDES6G Test Pattern Configuration B
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern) and
 * Lane_cfg.hr_mode_ena = '0'. In 20 bit modes bits from static_pattern and
 * static_pattern2 are transmitted alternating.
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_TP_CFG1B
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1B  VTSS_IOREG(0x04, 0, 0xe609)


/** 
 * \brief SERDES6G RCPLL BIST Configuration A
 *
 * \details
 * Configuration register A for the 6G RC-PLL BIST
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_RC_PLL_BIST_CFGA
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFGA  VTSS_IOREG(0x04, 0, 0xe60a)


/** 
 * \brief SERDES6G RCPLL BIST Configuration B
 *
 * \details
 * Configuration register B for the 6G RC-PLL BIST
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_RC_PLL_BIST_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFGB  VTSS_IOREG(0x04, 0, 0xe60b)


/** 
 * \brief SERDES6G Misc Configuration
 *
 * \details
 * Configuration register for miscellaneous functions
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_MISC_CFG
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG  VTSS_IOREG(0x04, 0, 0xe60c)

/** 
 * \brief
 * Select recovered clock divider
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . SEL_RECO_CLK
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Enable deserializer cp/md handling for 100fx mode
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_CPMD_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable flipping rx databus (MSB - LSB)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_BUS_FLIP_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_BUS_FLIP_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Enable flipping tx databus (MSB - LSB)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_BUS_FLIP_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_BUS_FLIP_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable RX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_LPI_MODE_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enable TX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_LPI_MODE_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable data inversion received from Deserializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_DATA_INV_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_DATA_INV_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable data inversion sent to Serializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_DATA_INV_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_DATA_INV_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Lane Reset
 *
 * \details 
 * 0: No reset
 * 1: Reset (not self-clearing)
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . LANE_RST
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST  VTSS_BIT(0)


/** 
 * \brief SERDES6G OB ANEG Configuration A
 *
 * \details
 * Configuration register A for ANEG Output Buffer overwrite parameter. The
 * values are used during Backplane Ethernet Auto-Negotiation when the
 * output level of transmitter (OB output) have to be reduced.
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_OB_ANEG_CFGA
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFGA  VTSS_IOREG(0x04, 0, 0xe60d)


/** 
 * \brief SERDES6G OB ANEG Configuration B
 *
 * \details
 * Configuration register B for ANEG Output Buffer overwrite parameter. The
 * values are used during Backplane Ethernet Auto-Negotiation when the
 * output level of transmitter (OB output) have to be reduced.
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_CFG:SERDES6G_OB_ANEG_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFGB  VTSS_IOREG(0x04, 0, 0xe60e)

/**
 * Register Group: \a VENICE_DEV4:SERDES6G_DIG_STATUS
 *
 * SERDES6G Digital Status Register
 */


/** 
 * \brief SERDES6G DFT Status
 *
 * \details
 * Status register of SERDES6G DFT functions
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_STATUS:SERDES6G_DFT_STATUS
 *
 * @param gi Register: SERDES6G_DIG_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS(gi)  VTSS_IOREG_IX(0x04, 0, 0xe60f, gi, 2, 0, 0)


/** 
 * \brief SERDES6G Error Counter
 *
 * \details
 * Error counter for SERDES6G PRBS
 *
 * Register: \a VENICE_DEV4:SERDES6G_DIG_STATUS:SERDES6G_ERR_CNT
 *
 * @param gi Register: SERDES6G_DIG_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT(gi)  VTSS_IOREG_IX(0x04, 0, 0xe60f, gi, 2, 0, 1)

/**
 * Register Group: \a VENICE_DEV4:SERDES6G_ANA_CFG
 *
 * SERDES6G Analog ConfigStatus Registers
 */


/** 
 * \brief SERDES6G Deserializer CfgA
 *
 * \details
 * Configuration register A for SERDES6G deserializer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_DES_CFGA
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGA  VTSS_IOREG(0x04, 0, 0xe617)

/** 
 * \brief
 * Control of phase regulator logic (bit 3 selects input to integrator
 * block - 0: cp/md from DES, 1: cp/md from core)
 *
 * \details 
 * 0: Disabled
 * 1: Enabled with 99 ppm limit
 * 2: Enabled with 202 ppm limit
 * 3: Enabled with 485 ppm limit
 * 4: Enabled if corresponding PCS is in sync with 50 ppm limit
 * 5: Enabled if corresponding PCS is in sync with 99 ppm limit
 * 6: Enabled if corresponding PCS is in sync with 202 ppm limit
 * 7: Enabled if corresponding PCS is in sync with 485 ppm limit
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGA . DES_PHS_CTRL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGA_DES_PHS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGA_DES_PHS_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGA_DES_PHS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES6G Deserializer CfgB
 *
 * \details
 * Configuration register B for SERDES6G deserializer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_DES_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB  VTSS_IOREG(0x04, 0, 0xe618)

/** 
 * \brief
 * Des phase control for 180 degrees deadlock block mode of operation
 *
 * \details 
 * 000: Depending on density of input pattern
 * 001: Active until PCS has synchronized
 * 010: Depending on density of input pattern until PCS has synchronized
 * 011: Never
 * 100: Always
 * 111: Debug feature: Add cp/md of DES and cp/md from core
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB . DES_MBTR_CTRL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_MBTR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_MBTR_CTRL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_MBTR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * DES phase control, main cp/md select
 *
 * \details 
 * 00: Directly from DES
 * 01: Through hysteresis stage from DES
 * 10: From core
 * 11: Disabled
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB . DES_CPMD_SEL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_CPMD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: Divide by 2
 * 1: Divide by 4
 * 2: Divide by 8
 * 3: Divide by 16
 * 4: Divide by 32
 * 5: Divide by 64
 * 6: Divide by 128
 * 7: Divide by 256
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB . DES_BW_HYST
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_HYST(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_HYST     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_HYST(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for non-hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: No division
 * 1: Divide by 2
 * 2: Divide by 4
 * 3: Divide by 8
 * 4: Divide by 16
 * 5: Divide by 32
 * 6: Divide by 64
 * 7: Divide by 128
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB . DES_BW_ANA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_ANA(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_ANA     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_DES_CFGB_DES_BW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,3)


/** 
 * \brief SERDES6G IB Configuration register 0A
 *
 * \details
 * Configuration settings 0A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG0A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A  VTSS_IOREG(0x04, 0, 0xe619)

/** 
 * \brief
 * ???
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_SOFSI
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SOFSI(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SOFSI     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SOFSI(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Controls Bulk Voltage of High Speed Cells
 *
 * \details 
 * 0: High
 * 1: Low (mission mode)
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_VBULK_SEL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_VBULK_SEL  VTSS_BIT(13)

/** 
 * \brief
 * Resistance adjustment for termination and CML cell regulation
 *
 * \details 
 * 0: High R
 * 15: Low R
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_RTRM_ADJ
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_RTRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,9,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_RTRM_ADJ     VTSS_ENCODE_BITMASK(9,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_RTRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,9,4)

/** 
 * \brief
 * Current adjustment for CML cells
 *
 * \details 
 * 0: Low current
 * 1: high current
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_ICML_ADJ
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_ICML_ADJ(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_ICML_ADJ     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_ICML_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Select common mode termination voltage
 *
 * \details 
 * 0: Open
 * 1: VCM ref (mission mode)
 * 2: VDDI
 * 3: capacitance only
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_TERM_MODE_SEL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_TERM_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_TERM_MODE_SEL     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_TERM_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Select signal detect clock: Frequency = 125 MHz / 2**n
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A . IB_SIG_DET_CLK_SEL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SIG_DET_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SIG_DET_CLK_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0A_IB_SIG_DET_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G IB Configuration register 0B
 *
 * \details
 * Configuration settings 0B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG0B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B  VTSS_IOREG(0x04, 0, 0xe61a)

/** 
 * \brief
 * Selects pattern detection for regulation of high-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified
 * basic and critical pattern are detected.
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_REG_PAT_SEL_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_HP(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_HP     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_HP(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Selects pattern detection for regulation of mid-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified
 * basic and critical pattern are detected.
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_REG_PAT_SEL_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_MID(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_MID     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_MID(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Selects pattern detection for regulation of low-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified
 * basic and critical pattern are detected.
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_REG_PAT_SEL_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_LP(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_LP     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_LP(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Selects pattern detection for regulation of offset
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified
 * basic and critical pattern are detected.
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_REG_PAT_SEL_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_OFFSET     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_PAT_SEL_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Enable analog test output.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_ANA_TEST_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_ANA_TEST_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable signal detection.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_SIG_DET_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_SIG_DET_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Constant current mode for CML cells
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_CONCUR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_CONCUR  VTSS_BIT(4)

/** 
 * \brief
 * Enable calibration
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_CAL_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_CAL_ENA  VTSS_BIT(3)

/** 
 * \brief
 * Enable SAMpling stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_SAM_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_SAM_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable EQualiZation-Stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_EQZ_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_EQZ_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable equalizer REGulation stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B . IB_REG_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG0B_IB_REG_ENA  VTSS_BIT(0)


/** 
 * \brief SERDES6G IB Configuration register 1A
 *
 * \details
 * Configuration settings 1A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG1A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A  VTSS_IOREG(0x04, 0, 0xe61b)

/** 
 * \brief
 * Selects threshold voltage for ac-jtag. Voltage = (n + 1) * 20 mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A . IB_TJTAG
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TJTAG(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TJTAG     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TJTAG(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Selects threshold voltage for signal detect. Voltage = (n + 1) * 20 mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A . IB_TSDET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TSDET(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TSDET     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1A_IB_TSDET(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SERDES6G IB Configuration register 1B
 *
 * \details
 * Configuration settings 1B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG1B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B  VTSS_IOREG(0x04, 0, 0xe61c)

/** 
 * \brief
 * Selects number of calibration cycles. Zero means no calibartion, i.e.
 * keep default values
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_SCALY
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_SCALY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_SCALY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_SCALY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects doubled filtering of high-pass-gain regulation or set it to hold
 * if ib_frc_hp = 1
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FILT_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FILT_HP  VTSS_BIT(7)

/** 
 * \brief
 * Selects doubled filtering of mid-pass-gain regulation or set it to hold
 * if ib_frc_mid = 1
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FILT_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FILT_MID  VTSS_BIT(6)

/** 
 * \brief
 * Selects doubled filtering of low-pass-gain regulation or set it to hold
 * if ib_frc_lp = 1
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FILT_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FILT_LP  VTSS_BIT(5)

/** 
 * \brief
 * Selects doubled filtering of offset regulation or set it to hold if
 * ib_frc_offset = 1
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FILT_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FILT_OFFSET  VTSS_BIT(4)

/** 
 * \brief
 * Selects manual control for high-pass-gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FRC_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FRC_HP  VTSS_BIT(3)

/** 
 * \brief
 * Selects manual control for mid-pass-gain regulaltion
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FRC_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FRC_MID  VTSS_BIT(2)

/** 
 * \brief
 * Selects manual control for low-pass-gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FRC_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FRC_LP  VTSS_BIT(1)

/** 
 * \brief
 * Selects manual control for offset regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B . IB_FRC_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1B_IB_FRC_OFFSET  VTSS_BIT(0)


/** 
 * \brief SERDES6G IB Configuration register 2A
 *
 * \details
 * Configuration settings 2A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG2A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A  VTSS_IOREG(0x04, 0, 0xe61d)

/** 
 * \brief
 * Selects maximum threshold influence for threshold calibration of vscope
 * samplers. Coding: 0: 40mV, 1: 80mV, ..., 7: 320mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A . IB_TINFV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_TINFV(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_TINFV     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_TINFV(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/** 
 * \brief
 * Selects maximum offset influence for offset regulation. Coding: 0: 10mV,
 * 1: 20mV, ...
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A . IB_OINFI
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFI(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFI     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFI(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Selects maximum offset influence for offset calibration of main
 * samplers. Coding: 0: 40mV, 1: 80mV, ..., 7: 320mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A . IB_OINFS
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFS(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFS     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2A_IB_OINFS(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G IB Configuration register 2B
 *
 * \details
 * Configuration settings 2B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG2B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B  VTSS_IOREG(0x04, 0, 0xe61e)

/** 
 * \brief
 * Selects offset voltage for main sampler calibration. Coding: 0: -75mV,
 * 1: -70mV, ..., 15: 0mV, 16: 0mV, ..., 31: 75mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B . IB_OCALS
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_OCALS(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_OCALS     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_OCALS(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Selects threshold voltage for vscope sampler calibration. Coding: 0:
 * 10mV, 1: 20mV, ..., 31: 320mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B . IB_TCALV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_TCALV(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_TCALV     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_TCALV(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Max. voltage of input signal. Coding: 0: 320mVppd, 1: 480mVppd, 2:
 * 640mVppd, 3: 800mVppd.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B . IB_UMAX
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UMAX(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UMAX     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UMAX(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * 0dB regulation voltage for high-speed-cells. Coding: 0: 160mV, 1: 180mV,
 * 2: 200mV, 3: 220mV, 4: 240mV, 5: 260mV, 6: 280mV, 7: 300mV.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B . IB_UREG
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UREG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UREG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2B_IB_UREG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G IB Configuration register 3A
 *
 * \details
 * Configuration settings 3A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG3A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A  VTSS_IOREG(0x04, 0, 0xe61f)

/** 
 * \brief
 * Init force value for high-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A . IB_INI_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_HP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_HP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_HP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Init force value for mid-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A . IB_INI_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_MID(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_MID     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3A_IB_INI_MID(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 3B
 *
 * \details
 * Configuration settings 3B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG3B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B  VTSS_IOREG(0x04, 0, 0xe620)

/** 
 * \brief
 * Init force value for low-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B . IB_INI_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_LP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_LP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_LP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Init force value for offset gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B . IB_INI_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3B_IB_INI_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 4A
 *
 * \details
 * Configuration settings 4A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG4A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A  VTSS_IOREG(0x04, 0, 0xe621)

/** 
 * \brief
 * Max value for high-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A . IB_MAX_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_HP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_HP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_HP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Max value for mid-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A . IB_MAX_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_MID(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_MID     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4A_IB_MAX_MID(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 4B
 *
 * \details
 * Configuration settings 4B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG4B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B  VTSS_IOREG(0x04, 0, 0xe622)

/** 
 * \brief
 * Max value for low-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B . IB_MAX_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_LP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_LP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_LP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Max value for offset gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B . IB_MAX_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4B_IB_MAX_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 5A
 *
 * \details
 * Configuration settings 5A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG5A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A  VTSS_IOREG(0x04, 0, 0xe623)

/** 
 * \brief
 * Min value for high-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A . IB_MIN_HP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_HP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_HP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_HP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Min value for mid-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A . IB_MIN_MID
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_MID(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_MID     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5A_IB_MIN_MID(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 5B
 *
 * \details
 * Configuration settings 5B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_IB_CFG5B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B  VTSS_IOREG(0x04, 0, 0xe624)

/** 
 * \brief
 * Min value for low-pass gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B . IB_MIN_LP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_LP(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_LP     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_LP(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Min value for offset gain regulation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B . IB_MIN_OFFSET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5B_IB_MIN_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G Output Buffer Cfg 0A
 *
 * \details
 * Configuration register 0A for SERDES6G output buffer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_OB_CFG0A
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A  VTSS_IOREG(0x04, 0, 0xe625)

/** 
 * \brief
 * PCIe support
 *
 * \details 
 * 1: idle - force to 0V differential
 * 0: Normal mode
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A . OB_IDLE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_IDLE  VTSS_BIT(15)

/** 
 * \brief
 * Output buffer supply voltage
 *
 * \details 
 * 1: Set to nominal 1V
 * 0: Set to higher voltage
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A . OB_ENA1V_MODE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_ENA1V_MODE  VTSS_BIT(14)

/** 
 * \brief
 * Polarity of output signal
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A . OB_POL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_POL  VTSS_BIT(13)

/** 
 * \brief
 * Coefficients for 1st Post Cursor (MSB is sign)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A . OB_POST0
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_POST0(x)  VTSS_ENCODE_BITFIELD(x,7,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_POST0     VTSS_ENCODE_BITMASK(7,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_POST0(x)  VTSS_EXTRACT_BITFIELD(x,7,6)

/** 
 * \brief
 * Coefficients for Pre Cursor (MSB is sign)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A . OB_PREC
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_PREC(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_PREC     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0A_OB_PREC(x)  VTSS_EXTRACT_BITFIELD(x,2,5)


/** 
 * \brief SERDES6G Output Buffer Cfg 0B
 *
 * \details
 * Configuration register 0B for SERDES6G output buffer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_OB_CFG0B
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B  VTSS_IOREG(0x04, 0, 0xe626)

/** 
 * \brief
 * Coefficients for 2nd Post Cursor (MSB is sign)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B . OB_POST1
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_POST1(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_POST1     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_POST1(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/** 
 * \brief
 * Half the predriver speed, use for slew rate control
 *
 * \details 
 * 0: Disable - slew rate < 60 ps
 * 1: Enable - slew rate > 60 ps
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B . OB_SR_H
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_SR_H  VTSS_BIT(8)

/** 
 * \brief
 * Driver speed, fine adjustment of slew rate 30-60ps (if OB_SR_H = 0),
 * 60-140ps (if OB_SR_H = 1)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B . OB_SR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_SR(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_SR     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_SR(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Resistor offset (correction value) added to measured RCOMP value
 * (2-bit-complement, -8...7).
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B . OB_RESISTOR_CTRL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG0B_OB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES6G Output Buffer Cfg1
 *
 * \details
 * Configuration register 1 for SERDES6G output buffer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_OB_CFG1
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1  VTSS_IOREG(0x04, 0, 0xe627)

/** 
 * \brief
 * Output skew, used for skew adjustment in SGMII mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_ENA_CAS
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Level of output amplitude
 *
 * \details 
 * 0: lowest level
 * 63: highest level
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_LEV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G Serializer Cfg
 *
 * \details
 * Configuration register for SERDES6G serializer
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_SER_CFG
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG  VTSS_IOREG(0x04, 0, 0xe628)

/** 
 * \brief
 * Select reference clock source for phase alignment
 *
 * \details 
 * 00: RXCLKP
 * 01: RefClk15MHz
 * 10: RXCLKN
 * 11: ext. ALICLK
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ALISEL
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable hysteresis for phase alignment
 *
 * \details 
 * 0: Disable hysteresis
 * 1: Enable hysteresis
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENHYS
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENHYS  VTSS_BIT(3)

/** 
 * \brief
 * Enable window for phase alignment
 *
 * \details 
 * 0: Disable window
 * 1: Enable window
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_EN_WIN
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN  VTSS_BIT(1)

/** 
 * \brief
 * Enable phase alignment
 *
 * \details 
 * 0: Disable phase alignment
 * 1: Enable phase alignment
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENALI
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI  VTSS_BIT(0)


/** 
 * \brief SERDES6G Common CfgA
 *
 * \details
 * Configuration register A for common SERDES6G functions
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_COMMON_CFGA
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA  VTSS_IOREG(0x04, 0, 0xe629)

/** 
 * \brief
 * System reset (low active)
 *
 * \details 
 * 0: Apply reset (not self-clearing)
 * 1: Reset released
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . SYS_RST
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_SYS_RST  VTSS_BIT(15)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus B
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . SE_AUTO_SQUELCH_B_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_SE_AUTO_SQUELCH_B_ENA  VTSS_BIT(6)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet bus A
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . SE_AUTO_SQUELCH_A_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_SE_AUTO_SQUELCH_A_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus B
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . RECO_SEL_B
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_RECO_SEL_B  VTSS_BIT(4)

/** 
 * \brief
 * Select recovered clock of this lane on sync. ethernet bus A
 *
 * \details 
 * 0: Lane not selected
 * 1: Lane selected
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . RECO_SEL_A
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_RECO_SEL_A  VTSS_BIT(3)

/** 
 * \brief
 * Enable lane
 *
 * \details 
 * 0: Disable lane
 * 1: Enable line
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA . ENA_LANE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGA_ENA_LANE  VTSS_BIT(2)


/** 
 * \brief SERDES6G Common CfgB
 *
 * \details
 * Configuration register B for common SERDES6G functions Note: When
 * enabling the facility loop (ena_floop) also the phase alignment in the
 * serializer has to be enabled and configured adequate.
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_COMMON_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB  VTSS_IOREG(0x04, 0, 0xe62a)

/** 
 * \brief
 * Enable equipment loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB . ENA_ELOOP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_ENA_ELOOP  VTSS_BIT(11)

/** 
 * \brief
 * Enable facility loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB . ENA_FLOOP
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_ENA_FLOOP  VTSS_BIT(10)

/** 
 * \brief
 * Enable half rate
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB . HRATE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_HRATE  VTSS_BIT(7)

/** 
 * \brief
 * Enable quarter rate
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB . QRATE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_QRATE  VTSS_BIT(6)

/** 
 * \brief
 * Interface mode
 *
 * \details 
 * 0: 8-bit mode
 * 1: 10-bit mode
 * 2: 16-bit mode
 * 3: 20-bit mode
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB . IF_MODE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_IF_MODE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFGB_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief SERDES6G Pll CfgA
 *
 * \details
 * Configuration register A for SERDES6G RCPLL
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_PLL_CFGA
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA  VTSS_IOREG(0x04, 0, 0xe62b)

/** 
 * \brief
 * Enable offset compensation B1: Feedback path; B0: VCO.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA . PLL_ENA_OFFS
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA_PLL_ENA_OFFS(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA_PLL_ENA_OFFS     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA_PLL_ENA_OFFS(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enable div4 mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA . PLL_DIV4
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA_PLL_DIV4  VTSS_BIT(1)

/** 
 * \brief
 * Enable rotation
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA . PLL_ENA_ROT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGA_PLL_ENA_ROT  VTSS_BIT(0)


/** 
 * \brief SERDES6G Pll CfgB
 *
 * \details
 * Configuration register B for SERDES6G RCPLL
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_PLL_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB  VTSS_IOREG(0x04, 0, 0xe62c)

/** 
 * \brief
 * Control data for FSM
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB . PLL_FSM_CTRL_DATA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_FSM_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_FSM_CTRL_DATA     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_FSM_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enable FSM
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB . PLL_FSM_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_FSM_ENA  VTSS_BIT(7)

/** 
 * \brief
 * Select rotation direction
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB . PLL_ROT_DIR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_ROT_DIR  VTSS_BIT(2)

/** 
 * \brief
 * Select rotation frequency
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB . PLL_ROT_FRQ
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_PLL_CFGB_PLL_ROT_FRQ  VTSS_BIT(1)


/** 
 * \brief SERDES6G ACJTAG Cfg
 *
 * \details
 * Configuration register for (AC)JTAG debug capability
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_ACJTAG_CFG
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG  VTSS_IOREG(0x04, 0, 0xe62d)

/** 
 * \brief
 * ACJTAG init data for n leg
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_DATA_N
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_N  VTSS_BIT(5)

/** 
 * \brief
 * ACJTAG init data for p leg
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_DATA_P
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_P  VTSS_BIT(4)

/** 
 * \brief
 * ACJTAG clock line
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_CLK
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_CLK  VTSS_BIT(3)

/** 
 * \brief
 * JTAG direct output (directly driven)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . OB_DIRECT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_OB_DIRECT  VTSS_BIT(2)

/** 
 * \brief
 * ACJTAG enable (ac_mode)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable JTAG control via CSR
 *
 * \details 
 * 0: External controlled
 * 1: CSR controlled
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . JTAG_CTRL_ENA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_JTAG_CTRL_ENA  VTSS_BIT(0)


/** 
 * \brief SERDES6G GP CFGB
 *
 * \details
 * General purpose register B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_CFG:SERDES6G_GP_CFGB
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_GP_CFGB  VTSS_IOREG(0x04, 0, 0xe62f)

/** 
 * \brief
 * To be defined
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_GP_CFGB . GP_LSB
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_GP_CFGB_GP_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_GP_CFGB_GP_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_CFG_SERDES6G_GP_CFGB_GP_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_DEV4:SERDES6G_ANA_STATUS
 *
 * SERDES6G Analog Status Registers
 */


/** 
 * \brief SERDES6G IB Status register 0
 *
 * \details
 * Status register for Signal Detect
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_IB_STATUS0
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 0)

/** 
 * \brief
 * Signals mission mode after calibration was done.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_CAL_DONE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_CAL_DONE  VTSS_BIT(8)

/** 
 * \brief
 * Flag high-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_HP_GAIN_ACT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_HP_GAIN_ACT  VTSS_BIT(7)

/** 
 * \brief
 * Flag mid-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_MID_GAIN_ACT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_MID_GAIN_ACT  VTSS_BIT(6)

/** 
 * \brief
 * Flag low-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_LP_GAIN_ACT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_LP_GAIN_ACT  VTSS_BIT(5)

/** 
 * \brief
 * Flag offset regulation activity. Caution: currently this signal is
 * generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_ACT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ACT  VTSS_BIT(4)

/** 
 * \brief
 * Valid average data of calibration process at ib_offset_stat available.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_VLD
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_VLD  VTSS_BIT(3)

/** 
 * \brief
 * Overflow error during calibration process. Value at ib_offset_stat not
 * valid.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_ERR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ERR  VTSS_BIT(2)

/** 
 * \brief
 * Detection of offset direction in selected (ib_offsx) sampling channels
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSDIR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSDIR  VTSS_BIT(1)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_SIG_DET
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_SIG_DET  VTSS_BIT(0)


/** 
 * \brief SERDES6G IB Status register 1A
 *
 * \details
 * Regulation stage status register A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_IB_STATUS1A
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 1)

/** 
 * \brief
 * Current high-pass-gain regulation value
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A . IB_HP_GAIN_STAT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_HP_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_HP_GAIN_STAT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_HP_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Current mid-pass-gain regulation value
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A . IB_MID_GAIN_STAT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_MID_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_MID_GAIN_STAT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1A_IB_MID_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Status register 1B
 *
 * \details
 * Regulation stage status register B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_IB_STATUS1B
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 2)

/** 
 * \brief
 * Current low-pass-gain regulation value
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B . IB_LP_GAIN_STAT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_LP_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_LP_GAIN_STAT     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_LP_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Current offset regulation value
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B . IB_OFFSET_STAT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_OFFSET_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_OFFSET_STAT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1B_IB_OFFSET_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G ACJTAG Status
 *
 * \details
 * Status register of (AC)JTAG debug capability
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_ACJTAG_STATUS
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 3)

/** 
 * \brief
 * ACJTAG captured data for n leg
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . ACJTAG_CAPT_DATA_N
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_N  VTSS_BIT(5)

/** 
 * \brief
 * ACJTAG captured data for p leg
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . ACJTAG_CAPT_DATA_P
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_P  VTSS_BIT(4)

/** 
 * \brief
 * JTAG direct input (directly driven)
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . IB_DIRECT
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_IB_DIRECT  VTSS_BIT(2)


/** 
 * \brief SERDES6G Pll Status
 *
 * \details
 * Status register of SERDES6G RCPLL
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_PLL_STATUS
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 4)

/** 
 * \brief
 * Calibration status
 *
 * \details 
 * 0: Calibration not started or ongoing
 * 1: Calibration finished
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_CAL_NOT_DONE
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE  VTSS_BIT(12)

/** 
 * \brief
 * Calibration error
 *
 * \details 
 * 0: No error during calibration
 * 1: Errors occured during calibration
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_CAL_ERR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR  VTSS_BIT(11)

/** 
 * \brief
 * Out of range error
 *
 * \details 
 * 0: No out of range condition detected
 * 1: Out of range condition since last calibration detected
 *
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_OUT_OF_RANGE_ERR
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR  VTSS_BIT(10)

/** 
 * \brief
 * PLL read-back data, depending on "pll_rb_data_sel" either the calibrated
 * setting or the measured period
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_RB_DATA
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief SERDES6G REVID A
 *
 * \details
 * Revision ID register A
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_REVIDA
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 5)

/** 
 * \brief
 * Serdes revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA . SERDES_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SERDES_REV(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SERDES_REV     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SERDES_REV(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * RCPLL revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA . RCPLL_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_RCPLL_REV(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_RCPLL_REV     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_RCPLL_REV(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * SER revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA . SER_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SER_REV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SER_REV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDA_SER_REV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SERDES6G REVID B
 *
 * \details
 * Revision ID register B
 *
 * Register: \a VENICE_DEV4:SERDES6G_ANA_STATUS:SERDES6G_REVIDB
 *
 * @param gi Register: SERDES6G_ANA_STATUS, 0-3
 */
#define VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB(gi)  VTSS_IOREG_IX(0x04, 0, 0xe630, gi, 7, 0, 6)

/** 
 * \brief
 * DES revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB . DES_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_DES_REV(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_DES_REV     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_DES_REV(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * OB revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB . OB_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_OB_REV(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_OB_REV     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_OB_REV(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * IB revision
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB . IB_REV
 */
#define  VTSS_F_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_IB_REV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_IB_REV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VENICE_DEV4_SERDES6G_ANA_STATUS_SERDES6G_REVIDB_IB_REV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a VENICE_DEV4:MACRO_CTRL_CFG
 *
 * MACRO_CTRL Configuration Registers
 */


/** 
 * \brief MACRO CTRL FSM Cfg0
 *
 * \details
 * Configuration register 0 for MACRO_CTRL state machine (FSM). Timer is
 * only used when MACRO_CTRL_FSM_CFG3.USE_PLL_CAL_DONE = 0.
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_CFG:MACRO_CTRL_FSM_CFG0
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG0  VTSS_IOREG(0x04, 0, 0xe800)

/** 
 * \brief
 * Setup (wait) time for RCPLL to calibrate. Wait time in number of
 * core_clk cycles.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG0 . SETUP_TIME_RCPLL
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG0_SETUP_TIME_RCPLL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG0_SETUP_TIME_RCPLL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG0_SETUP_TIME_RCPLL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MACRO CTRL FSM Cfg1
 *
 * \details
 * Configuration register 1 for MACRO_CTRL state machine (FSM)
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_CFG:MACRO_CTRL_FSM_CFG1
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG1  VTSS_IOREG(0x04, 0, 0xe801)

/** 
 * \brief
 * Setup (wait) time for Input-Buffer. Wait time in number of core_clk
 * cycles.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG1 . SETUP_TIME_IB
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG1_SETUP_TIME_IB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG1_SETUP_TIME_IB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG1_SETUP_TIME_IB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MACRO CTRL FSM Cfg2
 *
 * \details
 * Configuration register 2 for MACRO_CTRL state machine (FSM)
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_CFG:MACRO_CTRL_FSM_CFG2
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG2  VTSS_IOREG(0x04, 0, 0xe802)

/** 
 * \brief
 * Wait time after changing the operating mode. Wait time in number of
 * core_clk cycles.
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG2 . SETUP_TIME_CHG_MODE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG2_SETUP_TIME_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG2_SETUP_TIME_CHG_MODE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG2_SETUP_TIME_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MACRO CTRL FSM Cfg3
 *
 * \details
 * Configuration register 3 for MACRO_CTRL state machine (FSM)
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_CFG:MACRO_CTRL_FSM_CFG3
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3  VTSS_IOREG(0x04, 0, 0xe803)

/** 
 * \brief
 * Enable IB calibration after mode change additionally
 *
 * \details 
 * 0: Calibrate IB only after power-up
 * 1: Calibrate IB after power up and every automatic mode change
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3 . ALWAYS_CAL_IB
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_ALWAYS_CAL_IB  VTSS_BIT(6)

/** 
 * \brief
 * During automatic configuration wait on pll_cal_done instead of using the
 * rcpll_timer
 *
 * \details 
 * 0: use timer
 * 1: use pll_cal_done status bit
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3 . USE_PLL_CAL_DONE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_USE_PLL_CAL_DONE  VTSS_BIT(5)

/** 
 * \brief
 * Lane enable in manual mode
 *
 * \details 
 * 0: Automatic Mode
 * 1: Manual Mode
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3 . LANE_ENA_MAN
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_LANE_ENA_MAN(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_LANE_ENA_MAN     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_LANE_ENA_MAN(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * Disable automatic configuration mode (manual mode)
 *
 * \details 
 * 0: Automatic Configuration Mode
 * 1: Manual Configuration Mode
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3 . DISABLE_AUTO_MODE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_MACRO_CTRL_FSM_CFG3_DISABLE_AUTO_MODE  VTSS_BIT(0)


/** 
 * \brief SYNC ETH CFG
 *
 * \details
 * Configuration register for Synchronous Ethernet
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_CFG:SYNC_ETH_CFG
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG  VTSS_IOREG(0x04, 0, 0xe804)

/** 
 * \brief
 * Select active (recovered) clock B source for sync ethernet. Each bit
 * matches clock of one lane.
 *
 * \details 
 * 0000: clock disabled
 * 0001: lane 0 clock active
 * 0010: lane 1 clock active
 * 0100: lane 2 clock active
 * 1000: lane 3 clock active
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG . RECO_CLK_B_ACTIVE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_B_ACTIVE(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_B_ACTIVE     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_B_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Select active (recovered) clock A source for sync ethernet. Each bit
 * matches clock of one lane.
 *
 * \details 
 * 0000: clock disabled
 * 0001: lane 0 clock active
 * 0010: lane 1 clock active
 * 0100: lane 2 clock active
 * 1000: lane 3 clock active
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG . RECO_CLK_A_ACTIVE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_A_ACTIVE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_A_ACTIVE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_CFG_SYNC_ETH_CFG_RECO_CLK_A_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a VENICE_DEV4:MACRO_CTRL_STATUS
 *
 * MACRO_CTRL Status Registers
 */


/** 
 * \brief MACRO CTRL Status
 *
 * \details
 * Status register of MACRO_CTRL state machine (FSM)
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_STATUS:MACRO_CTRL_STAT
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_STAT  VTSS_IOREG(0x04, 0, 0xe805)

/** 
 * \brief
 * State machine error occured
 *
 * \details 
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_STAT . FSM_ERR_STICKY
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_STAT_FSM_ERR_STICKY  VTSS_BIT(0)


/** 
 * \brief MACRO CTRL signal drive Status
 *
 * \details
 * Register allowing to observe the signals driven by the macro control
 * state machine (FSM).
 *
 * Register: \a VENICE_DEV4:MACRO_CTRL_STATUS:MACRO_CTRL_SIGDRV_STAT
 */
#define VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT  VTSS_IOREG(0x04, 0, 0xe806)

/** 
 * \brief
 * Current status of driven signal ena_lane(3:0), one bit per lane
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . ENA_LANE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_ENA_LANE(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_ENA_LANE     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_ENA_LANE(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Current status of driven signal ena_loop
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . ENA_LOOP
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_ENA_LOOP  VTSS_BIT(6)

/** 
 * \brief
 * Current status of driven signal lane_rst
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . LANE_RST
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_LANE_RST  VTSS_BIT(5)

/** 
 * \brief
 * Current status of driven signal system_rst_n
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . SYS_RST_N
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_SYS_RST_N  VTSS_BIT(4)

/** 
 * \brief
 * Initialization done, device in normal operation mode
 *
 * \details 
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . INIT_DONE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_INIT_DONE  VTSS_BIT(3)

/** 
 * \brief
 * Current operation mode
 *
 * \details 
 * 0: XAUI
 * 1: RXAUI
 * 2: SGMII on lane 0
 * 3: SGMII on lane 3
 * 4-7: Reserved
 *
 * Field: VTSS_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT . OP_MODE
 */
#define  VTSS_F_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_OP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_OP_MODE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_DEV4_MACRO_CTRL_STATUS_MACRO_CTRL_SIGDRV_STAT_OP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


#endif /* _VTSS_VENICE_REGS_VENICE_DEV4_H_ */
