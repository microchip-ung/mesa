// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_WIS_H_
#define _VTSS_MALIBU_REGS_WIS_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a WIS
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a WIS:WIS_Control_1
 *
 * Not documented
 */


/** 
 * \brief WIS Control 1
 *
 * \details
 * Register: \a WIS:WIS_Control_1:WIS_CTRL1
 */
#define VTSS_WIS_WIS_Control_1_WIS_CTRL1     VTSS_IOREG(0x02, 0, 0x0000)

/** 
 * \brief
 * MDIO Managable Device (MMD) software reset.	Reset all logic in the
 * channel between the host side PMA and the line side PMA, regardless of
 * the cross-connect configuration.  Data path logic and configuration
 * registers are reset.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Reset
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . SOFT_RST
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_SOFT_RST  VTSS_BIT(15)

/** 
 * \brief
 * Enables WIS system loopback (loopback H4)
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . LPBK_H4
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_LPBK_H4  VTSS_BIT(14)

/** 
 * \brief
 * Speed selection
 *
 * \details 
 * 0 = Unspecified
 * 1 = Operates at 10 Gbps or above
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . SPEED_SEL_A
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_SPEED_SEL_A  VTSS_BIT(13)

/** 
 * \brief
 * The channel's data path is placed into low power mode with this
 * register.  The PMA in this channel is also placed into low power mode
 * regardless of the channel cross connect configuration.  The
 * PMD_TRANSMIT_DISABLE.GLOBAL_PMD_TRANSMIT_DISABLE register state can can
 * be transmitted from a GPIO pin to shut off an optics module's TX driver.
 *
 * \details 
 * 0 = Normal Operation
 * 1 = Low Power Mode.
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . LOW_PWR_WIS
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_LOW_PWR_WIS  VTSS_BIT(11)

/** 
 * \brief
 * Speed selection
 *
 * \details 
 * 0 = Unspecified
 * 1 = Operates at 10 Gbps or above
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . SPEED_SEL_B
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_SPEED_SEL_B  VTSS_BIT(6)

/** 
 * \brief
 * Speed selection
 *
 * \details 
 * 1xxx: Reserved.
 * x1xx: Reserved.
 * xx1x: Reserved.
 * 0001: Reserved.
 * 0000: 10 Gbps
 *
 * Field: VTSS_WIS_WIS_Control_1_WIS_CTRL1 . SPEED_SEL_C
 */
#define  VTSS_F_WIS_WIS_Control_1_WIS_CTRL1_SPEED_SEL_C(x)  VTSS_ENCODE_BITFIELD(x,2,4)
#define  VTSS_M_WIS_WIS_Control_1_WIS_CTRL1_SPEED_SEL_C     VTSS_ENCODE_BITMASK(2,4)
#define  VTSS_X_WIS_WIS_Control_1_WIS_CTRL1_SPEED_SEL_C(x)  VTSS_EXTRACT_BITFIELD(x,2,4)

/**
 * Register Group: \a WIS:WIS_Status_1
 *
 * Not documented
 */


/** 
 * \brief WIS Status 1
 *
 * \details
 * Register: \a WIS:WIS_Status_1:WIS_STAT1
 */
#define VTSS_WIS_WIS_Status_1_WIS_STAT1      VTSS_IOREG(0x02, 0, 0x0001)

/** 
 * \brief
 * WIS fault status. The alarm conditions that cause the WIS fault status
 * to be asserted are configured in the WIS_FAULT_MASK register.  Based on
 * the WIS_FAULT_MASK setting, the WIS fault status can be asserted when
 * the following alarm conditions exist:  OOF, LOS, LOF, LOP-P, AIS-L,
 * AIS-P, LCD-P, PLM-P, RDI-L, far-end AIS-P and far-end PLM-P.  This is a
 * sticky bit that latches the high state.  The latch-high bit is cleared
 * when the register is read.
 *
 * \details 
 * 0 = No faults asserted
 * 1 = Fault asserted
 *
 * Field: VTSS_WIS_WIS_Status_1_WIS_STAT1 . FAULT
 */
#define  VTSS_F_WIS_WIS_Status_1_WIS_STAT1_FAULT  VTSS_BIT(7)

/** 
 * \brief
 * WIS receive link status. Link up means no AIS-P, AIS-L, PLM-P, LOP-P or
 * SEF alarms.	This is a sticky bit that latches the low state.  The
 * latch-low bit is cleared when the register is read.
 *
 * \details 
 * 0 = WIS link down.  (AIS-P=1 OR AIS-L=1 OR PLM-P=1 OR WIS SEF=1 or
 * LOP-P=1)
 * 1 = WIS link up.  (AIS-P=0 AND AIS-L=0 AND PLM-P=0 AND SEF=0 AND
 * LOP-P=0)
 *
 * Field: VTSS_WIS_WIS_Status_1_WIS_STAT1 . LNK_STAT
 */
#define  VTSS_F_WIS_WIS_Status_1_WIS_STAT1_LNK_STAT  VTSS_BIT(2)

/** 
 * \brief
 * Low power mode support ability.
 *
 * \details 
 * 0 = Supported
 * 1 = Not supported
 *
 * Field: VTSS_WIS_WIS_Status_1_WIS_STAT1 . LOW_PWR_ABILITY
 */
#define  VTSS_F_WIS_WIS_Status_1_WIS_STAT1_LOW_PWR_ABILITY  VTSS_BIT(1)

/**
 * Register Group: \a WIS:WIS_Device_Identifier
 *
 * Not documented
 */


/** 
 * \brief WIS Device Identifier 1
 *
 * \details
 * Register: \a WIS:WIS_Device_Identifier:WIS_DEVID1
 */
#define VTSS_WIS_WIS_Device_Identifier_WIS_DEVID1  VTSS_IOREG(0x02, 0, 0x0002)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique WIS device identifier. Bits 3-18 of the
 * device manufacturer's OUI.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Device_Identifier_WIS_DEVID1 . DEV_ID_MSW
 */
#define  VTSS_F_WIS_WIS_Device_Identifier_WIS_DEVID1_DEV_ID_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Device_Identifier_WIS_DEVID1_DEV_ID_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Device_Identifier_WIS_DEVID1_DEV_ID_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Device Identifier 2
 *
 * \details
 * Register: \a WIS:WIS_Device_Identifier:WIS_DEVID2
 */
#define VTSS_WIS_WIS_Device_Identifier_WIS_DEVID2  VTSS_IOREG(0x02, 0, 0x0003)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique WIS device identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number, and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Device_Identifier_WIS_DEVID2 . DEV_ID_LSW
 */
#define  VTSS_F_WIS_WIS_Device_Identifier_WIS_DEVID2_DEV_ID_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Device_Identifier_WIS_DEVID2_DEV_ID_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Device_Identifier_WIS_DEVID2_DEV_ID_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Speed_Capability
 *
 * Not documented
 */


/** 
 * \brief WIS Speed Capability
 *
 * \details
 * Register: \a WIS:WIS_Speed_Capability:WIS_SPEED
 */
#define VTSS_WIS_WIS_Speed_Capability_WIS_SPEED  VTSS_IOREG(0x02, 0, 0x0004)

/** 
 * \brief
 * WIS rate capability
 *
 * \details 
 * 0 = Not capable of 10Gbps
 * 1 = Capable of 10Gbps
 *
 * Field: VTSS_WIS_WIS_Speed_Capability_WIS_SPEED . RATE_ABILITY
 */
#define  VTSS_F_WIS_WIS_Speed_Capability_WIS_SPEED_RATE_ABILITY  VTSS_BIT(0)

/**
 * Register Group: \a WIS:WIS_Devices_in_Package
 *
 * Not documented
 */


/** 
 * \brief WIS Devices in Package 1
 *
 * \details
 * Register: \a WIS:WIS_Devices_in_Package:WIS_DEVPKG1
 */
#define VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1  VTSS_IOREG(0x02, 0, 0x0005)

/** 
 * \brief
 * Indicates whether DTE XS is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . DTE_XS_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_DTE_XS_PRES  VTSS_BIT(5)

/** 
 * \brief
 * Indicates whether PHY XS is present in the package 
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . PHY_XS_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_PHY_XS_PRES  VTSS_BIT(4)

/** 
 * \brief
 * Indicates whether PCS is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . PCS_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_PCS_PRES  VTSS_BIT(3)

/** 
 * \brief
 * Indicates whether WIS is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . WIS_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_WIS_PRES  VTSS_BIT(2)

/** 
 * \brief
 * Indicates whether PMA/PMD is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . PMD_PMA_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_PMD_PMA_PRES  VTSS_BIT(1)

/** 
 * \brief
 * Indicates whether Clause 22 registers are present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG1 . CLS22_PRES
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG1_CLS22_PRES  VTSS_BIT(0)


/** 
 * \brief WIS Devices in Package 2
 *
 * \details
 * Register: \a WIS:WIS_Devices_in_Package:WIS_DEVPKG2
 */
#define VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG2  VTSS_IOREG(0x02, 0, 0x0006)

/** 
 * \brief
 * Indicates whether vendor specific device 2 is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG2 . Vendor_spec_dev_2_present
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG2_Vendor_spec_dev_2_present  VTSS_BIT(15)

/** 
 * \brief
 * Indicates whether vendor specific device 1 is present in the package
 *
 * \details 
 * 0 = Not present
 * 1 = Present
 *
 * Field: VTSS_WIS_WIS_Devices_in_Package_WIS_DEVPKG2 . Vendor_spec_dev_1_present
 */
#define  VTSS_F_WIS_WIS_Devices_in_Package_WIS_DEVPKG2_Vendor_spec_dev_1_present  VTSS_BIT(14)

/**
 * Register Group: \a WIS:WIS_Control_2
 *
 * Not documented
 */


/** 
 * \brief WIS Control 2
 *
 * \details
 * Register: \a WIS:WIS_Control_2:WIS_CTRL2
 */
#define VTSS_WIS_WIS_Control_2_WIS_CTRL2     VTSS_IOREG(0x02, 0, 0x0007)

/** 
 * \brief
 * Enable WIS PRBS31 test pattern checking function
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . TEST_PRBS31_ANA
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_TEST_PRBS31_ANA  VTSS_BIT(5)

/** 
 * \brief
 * Enable WIS PRBS31 test pattern generation function.	Transmission of the
 * PRBS31 pattern has priority over the square wave and mixed frequency
 * test patterns if TEST_PAT_GEN in this register is also high.
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . TEST_PRBS31_GEN
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_TEST_PRBS31_GEN  VTSS_BIT(4)

/** 
 * \brief
 * Selects the pattern type sent by the transmitter when bit TEST_PAT_GEN
 * in this register is high.
 *
 * \details 
 * 0 = Mixed frequency test pattern
 * 1 = Square wave
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . TEST_PAT_SEL
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_TEST_PAT_SEL  VTSS_BIT(3)

/** 
 * \brief
 * Enables the WIS test pattern checker. Doing so prevents the loss of
 * code-group delineation (LCD-P) alarm from being set while the WIS is
 * receiving the mixed frequency test pattern.
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . TEST_PAT_ANA
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_TEST_PAT_ANA  VTSS_BIT(2)

/** 
 * \brief
 * Enable WIS test pattern generation
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . TEST_PAT_GEN
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_TEST_PAT_GEN  VTSS_BIT(1)

/** 
 * \brief
 * Enable 10GBASE-W logic and sets the speed of the WIS-PMA interface to
 * 9.95328 Gbps. The proper reference clock frequency must be provided to
 * set the data rate. Note: there are multiple ways to enable WAN mode.
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Control_2_WIS_CTRL2 . WAN_MODE
 */
#define  VTSS_F_WIS_WIS_Control_2_WIS_CTRL2_WAN_MODE  VTSS_BIT(0)

/**
 * Register Group: \a WIS:WIS_Status_2
 *
 * Not documented
 */


/** 
 * \brief WIS Status 2
 *
 * \details
 * Register: \a WIS:WIS_Status_2:WIS_STAT2
 */
#define VTSS_WIS_WIS_Status_2_WIS_STAT2      VTSS_IOREG(0x02, 0, 0x0008)

/** 
 * \brief
 * Reflects the presence of a MMD responding at this address
 *
 * \details 
 * 00: No device responding at this address
 * 01: No device responding at this address
 * 10: Device responding at this address
 * 11: No device responding at this address
 *
 * Field: VTSS_WIS_WIS_Status_2_WIS_STAT2 . DEV_PRES
 */
#define  VTSS_F_WIS_WIS_Status_2_WIS_STAT2_DEV_PRES(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_WIS_WIS_Status_2_WIS_STAT2_DEV_PRES     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_WIS_WIS_Status_2_WIS_STAT2_DEV_PRES(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Indicates if WIS supports PRBS31 pattern testing
 *
 * \details 
 * 0 = Not supported
 * 1 = Supported
 *
 * Field: VTSS_WIS_WIS_Status_2_WIS_STAT2 . PRBS31_ABILITY
 */
#define  VTSS_F_WIS_WIS_Status_2_WIS_STAT2_PRBS31_ABILITY  VTSS_BIT(1)

/** 
 * \brief
 * Indicates if WIS supports a bypass to allow support of 10GBASE-R
 *
 * \details 
 * 0 = Not supported
 * 1 = Supported
 *
 * Field: VTSS_WIS_WIS_Status_2_WIS_STAT2 . BASE_R_ABILITY
 */
#define  VTSS_F_WIS_WIS_Status_2_WIS_STAT2_BASE_R_ABILITY  VTSS_BIT(0)

/**
 * Register Group: \a WIS:WIS_Test_Pattern_Error_Counter
 *
 * Not documented
 */


/** 
 * \brief WIS Test Pattern Error Counter
 *
 * \details
 * Register: \a WIS:WIS_Test_Pattern_Error_Counter:WIS_TSTPAT_CNT
 */
#define VTSS_WIS_WIS_Test_Pattern_Error_Counter_WIS_TSTPAT_CNT  VTSS_IOREG(0x02, 0, 0x0009)

/** 
 * \brief
 * PRBS31 test pattern error counter. The saturating counter is cleared
 * when the register is read. The error count is not valid until the sync
 * status in register bit EWIS_PRBS31_ANA_STAT.PRBS31_ANA_STATE is
 * asserted.  The error count in this register can be incremented while the
 * checker is acquiring sync.  Read this register to clear the invalid
 * error count when sync is achieved.  Once synchronization is achieved,
 * any future loss of synchronization will not prevent the error counter
 * from accummulating.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Test_Pattern_Error_Counter_WIS_TSTPAT_CNT . TSTPAT_CNT
 */
#define  VTSS_F_WIS_WIS_Test_Pattern_Error_Counter_WIS_TSTPAT_CNT_TSTPAT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Test_Pattern_Error_Counter_WIS_TSTPAT_CNT_TSTPAT_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Test_Pattern_Error_Counter_WIS_TSTPAT_CNT_TSTPAT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Package_Identifier
 *
 * Not documented
 */


/** 
 * \brief WIS Package Identifier 1
 *
 * \details
 * Register: \a WIS:WIS_Package_Identifier:WIS_PKGID1
 */
#define VTSS_WIS_WIS_Package_Identifier_WIS_PKGID1  VTSS_IOREG(0x02, 0, 0x000e)

/** 
 * \brief
 * Upper 16 bits of a 32-bit unique WIS package identifier. Bits 3-18 of
 * the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Package_Identifier_WIS_PKGID1 . PKG_ID_MSW
 */
#define  VTSS_F_WIS_WIS_Package_Identifier_WIS_PKGID1_PKG_ID_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Package_Identifier_WIS_PKGID1_PKG_ID_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Package_Identifier_WIS_PKGID1_PKG_ID_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Package Identifier 2
 *
 * \details
 * Register: \a WIS:WIS_Package_Identifier:WIS_PKGID2
 */
#define VTSS_WIS_WIS_Package_Identifier_WIS_PKGID2  VTSS_IOREG(0x02, 0, 0x000f)

/** 
 * \brief
 * Lower 16 bits of a 32-bit unique WIS package identifier. Bits 19-24 of
 * the device manufacturer's OUI. Six-bit model number and a four-bit
 * revision number.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Package_Identifier_WIS_PKGID2 . PKG_ID_LSW
 */
#define  VTSS_F_WIS_WIS_Package_Identifier_WIS_PKGID2_PKG_ID_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Package_Identifier_WIS_PKGID2_PKG_ID_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Package_Identifier_WIS_PKGID2_PKG_ID_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Status_3
 *
 * Not documented
 */


/** 
 * \brief WIS Status 3
 *
 * \details
 * Register: \a WIS:WIS_Status_3:WIS_STAT3
 */
#define VTSS_WIS_WIS_Status_3_WIS_STAT3      VTSS_IOREG(0x02, 0, 0x0021)

/** 
 * \brief
 * Severely errored frame.  This is a sticky bit that latches the high
 * state.  The latch-high bit is cleared when the register is read.
 *
 * \details 
 * 0 = No SEF detected
 * 1 = SEF detected
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . SEF
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_SEF  VTSS_BIT(11)

/** 
 * \brief
 * Indicates far-end PLM-P/LCD-P defect in WIS RX.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0 = No far-end path label mismatch / Loss of code-group delineation
 * 1 = far-end path label mismatch / Loss of code-group delineation
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . FEPLMP_LCDP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_FEPLMP_LCDP  VTSS_BIT(10)

/** 
 * \brief
 * Indicates far-end AIS-P/LOP-P defect in WIS RX.  The latch-high bit is
 * cleared when the register is read.
 *
 * \details 
 * 0 = far-end path Alarm Indication Signal / Path Loss of Pointer
 * 1 = No far-end path alarm indication signal / Path loss of pointer
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . FEAISP_LOPP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_FEAISP_LOPP  VTSS_BIT(9)

/** 
 * \brief
 * Loss of frame .  The latch-high bit is cleared when the register is
 * read.
 *
 * \details 
 * 0 = Loss of frame flag lowered
 * 1 = Loss of frame flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . LOF
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_LOF  VTSS_BIT(7)

/** 
 * \brief
 * Loss of signal .  The latch-high bit is cleared when the register is
 * read.
 *
 * \details 
 * 0 = Loss of signal flag lowered
 * 1 = Loss of signal flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . LOS
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_LOS  VTSS_BIT(6)

/** 
 * \brief
 * Line remote defect indication.  The latch-high bit is cleared when the
 * register is read.
 *
 * \details 
 * 0 = Line remote defect flag lowered
 * 1 = Line remote defect flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . RDIL
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_RDIL  VTSS_BIT(5)

/** 
 * \brief
 * Line alarm indication signal.  The latch-high bit is cleared when the
 * register is read.
 *
 * \details 
 * 0 = Line alarm indication flag lowered
 * 1 = Line alarm indication flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . AISL
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_AISL  VTSS_BIT(4)

/** 
 * \brief
 * Path loss of code-group delineation.  The latch-high bit is cleared when
 * the register is read.
 *
 * \details 
 * 0 = Path loss of code-group delineation flag lowered
 * 1 = Path loss of code-group delineation flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . LCDP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_LCDP  VTSS_BIT(3)

/** 
 * \brief
 * Path label mismatch.  The latch-high bit is cleared when the register is
 * read.
 *
 * \details 
 * 0 = Path label mismatch flag lowered
 * 1 = Path label mismatch flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . PLMP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_PLMP  VTSS_BIT(2)

/** 
 * \brief
 * Path alarm indication signal.  The latch-high bit is cleared when the
 * register is read.
 *
 * \details 
 * 0 = Path alarm indication signal lowered
 * 1 = Path alarm indication signal raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . AISP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_AISP  VTSS_BIT(1)

/** 
 * \brief
 * Loss of pointer.  The latch-high bit is cleared when the register is
 * read.
 *
 * \details 
 * 0 = Loss of pointer flag lowered
 * 1 = Loss of pointer flag raised
 *
 * Field: VTSS_WIS_WIS_Status_3_WIS_STAT3 . LOPP
 */
#define  VTSS_F_WIS_WIS_Status_3_WIS_STAT3_LOPP  VTSS_BIT(0)

/**
 * Register Group: \a WIS:WIS_Far_End_Path_Block_Error_Count
 *
 * Not documented
 */


/** 
 * \brief WIS Far-End Path Block Error Count
 *
 * \details
 * Register: \a WIS:WIS_Far_End_Path_Block_Error_Count:WIS_REIP_CNT
 */
#define VTSS_WIS_WIS_Far_End_Path_Block_Error_Count_WIS_REIP_CNT  VTSS_IOREG(0x02, 0, 0x0025)

/** 
 * \brief
 * Far end path block error count.  Counter wraps around to 0 when it is
 * incremented beyond its maximum error count of 65,535.  Cleared on
 * channel reset. 
 *
 * \details 
 * Field: VTSS_WIS_WIS_Far_End_Path_Block_Error_Count_WIS_REIP_CNT . REIP_CNT
 */
#define  VTSS_F_WIS_WIS_Far_End_Path_Block_Error_Count_WIS_REIP_CNT_REIP_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Far_End_Path_Block_Error_Count_WIS_REIP_CNT_REIP_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Far_End_Path_Block_Error_Count_WIS_REIP_CNT_REIP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Tx_J1_Octets_0_15
 *
 * Transmitted Path Trace Message Octets
 */


/** 
 * \brief WIS Tx J1 Octets 1-0
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_1_0
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0  VTSS_IOREG(0x02, 0, 0x0027)

/** 
 * \brief
 * Contains octet 1 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0 . TX_J1_octet_1
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 0 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0 . TX_J1_octet_0
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_1_0_TX_J1_octet_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 3-2
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_3_2
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2  VTSS_IOREG(0x02, 0, 0x0028)

/** 
 * \brief
 * Contains octet 3 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2 . TX_J1_octet_3
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_3(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_3     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_3(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 2 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2 . TX_J1_octet_2
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_3_2_TX_J1_octet_2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 5-4
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_5_4
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4  VTSS_IOREG(0x02, 0, 0x0029)

/** 
 * \brief
 * Contains octet 5 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4 . TX_J1_octet_5
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 4 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4 . TX_J1_octet_4
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_5_4_TX_J1_octet_4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 7-6
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_7_6
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6  VTSS_IOREG(0x02, 0, 0x002a)

/** 
 * \brief
 * Contains octet 7 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6 . TX_J1_octet_7
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 6 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6 . TX_J1_octet_6
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_6(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_6     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_7_6_TX_J1_octet_6(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 9-8
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_9_8
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8  VTSS_IOREG(0x02, 0, 0x002b)

/** 
 * \brief
 * Contains octet 9 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8 . TX_J1_octet_9
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_9(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_9     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_9(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 8 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8 . TX_J1_octet_8
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_9_8_TX_J1_octet_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 11-10
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_11_10
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10  VTSS_IOREG(0x02, 0, 0x002c)

/** 
 * \brief
 * Contains octet 11 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10 . TX_J1_octet_11
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_11(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_11     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_11(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 10 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10 . TX_J1_octet_10
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_10(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_10     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_11_10_TX_J1_octet_10(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 13-12
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_13_12
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12  VTSS_IOREG(0x02, 0, 0x002d)

/** 
 * \brief
 * Contains octet 13 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12 . TX_J1_octet_13
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_13(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_13     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_13(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 12 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12 . TX_J1_octet_12
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_12(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_12     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_13_12_TX_J1_octet_12(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J1 Octets 15-14
 *
 * \details
 * Register: \a WIS:WIS_Tx_J1_Octets_0_15:WIS_Tx_J1_Octets_15_14
 */
#define VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14  VTSS_IOREG(0x02, 0, 0x002e)

/** 
 * \brief
 * Contains octet 15 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14 . TX_J1_octet_15
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_15(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_15     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_15(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 14 of the transmitted path trace message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14 . TX_J1_octet_14
 */
#define  VTSS_F_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_14(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_14     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J1_Octets_0_15_WIS_Tx_J1_Octets_15_14_TX_J1_octet_14(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:WIS_Rx_J1_Octets_0_15
 *
 * Received Path Trace Message Octets
 */


/** 
 * \brief WIS Rx J1 Octets 1-0
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_1_0
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0  VTSS_IOREG(0x02, 0, 0x002f)

/** 
 * \brief
 * Contains octet 1 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0 . RX_J1_octet_1
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 0 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0 . RX_J1_octet_0
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_1_0_RX_J1_octet_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 3-2
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_3_2
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2  VTSS_IOREG(0x02, 0, 0x0030)

/** 
 * \brief
 * Contains octet 3 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2 . RX_J1_octet_3
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_3(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_3     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_3(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 2 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2 . RX_J1_octet_2
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_3_2_RX_J1_octet_2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 5-4
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_5_4
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4  VTSS_IOREG(0x02, 0, 0x0031)

/** 
 * \brief
 * Contains octet 5 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4 . RX_J1_octet_5
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 4 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4 . RX_J1_octet_4
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_5_4_RX_J1_octet_4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 7-6
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_7_6
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6  VTSS_IOREG(0x02, 0, 0x0032)

/** 
 * \brief
 * Contains octet 7 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6 . RX_J1_octet_7
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 6 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6 . RX_J1_octet_6
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_6(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_6     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_7_6_RX_J1_octet_6(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 9-8
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_9_8
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8  VTSS_IOREG(0x02, 0, 0x0033)

/** 
 * \brief
 * Contains octet 9 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8 . RX_J1_octet_9
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_9(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_9     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_9(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 8 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8 . RX_J1_octet_8
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_9_8_RX_J1_octet_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 11-10
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_11_10
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10  VTSS_IOREG(0x02, 0, 0x0034)

/** 
 * \brief
 * Contains octet 11 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10 . RX_J1_octet_11
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_11(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_11     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_11(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 10 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10 . RX_J1_octet_10
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_10(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_10     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_11_10_RX_J1_octet_10(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 13-12
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_13_12
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12  VTSS_IOREG(0x02, 0, 0x0035)

/** 
 * \brief
 * Contains octet 13 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12 . RX_J1_octet_13
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_13(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_13     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_13(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 12 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12 . RX_J1_octet_12
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_12(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_12     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_13_12_RX_J1_octet_12(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J1 Octets 15-14
 *
 * \details
 * Register: \a WIS:WIS_Rx_J1_Octets_0_15:WIS_Rx_J1_Octets_15_14
 */
#define VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14  VTSS_IOREG(0x02, 0, 0x0036)

/** 
 * \brief
 * Contains octet 15 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14 . RX_J1_octet_15
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_15(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_15     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_15(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 14 of the received path trace message
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14 . RX_J1_octet_14
 */
#define  VTSS_F_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_14(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_14     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J1_Octets_0_15_WIS_Rx_J1_Octets_15_14_RX_J1_octet_14(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:WIS_IEEE_Error_Counters
 *
 * Not documented
 */


/** 
 * \brief WIS Far-End Line BIP Errors 1
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_REIL_CNT1
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT1  VTSS_IOREG(0x02, 0, 0x0037)

/** 
 * \brief
 * Most significant word of the WIS far end line BIP error counter.  The
 * counter does not saturate when the maximum count has been exceeded. 
 * Reading register WIS_REIL_CNT1 latches the 32-bit counter value into a
 * pair of 16-bit registers.  The most significant counter bits are located
 * in WIS_REIL_CNT1.   The least significant bits are located in
 * WIS_REIL_CNT0.  Subsequest reads of address WIS_REIL_CNT0 will return
 * the latched value and will not change the latched register contents. 
 * The counter can only be cleared by reseting the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT1 . REIL_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT1_REIL_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT1_REIL_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT1_REIL_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Far-End Line BIP Errors 0
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_REIL_CNT0
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT0  VTSS_IOREG(0x02, 0, 0x0038)

/** 
 * \brief
 * Least significant word of the WIS far end line BIP error counter.  The
 * counter does not saturate when the maximum count has been exceeded. 
 * Reading register WIS_REIL_CNT1 latches the 32-bit counter value into a
 * pair of 16-bit registers.  The most significant counter bits are located
 * in WIS_REIL_CNT1.   The least significant bits are located in
 * WIS_REIL_CNT0.  Subsequest reads of address WIS_REIL_CNT0 will return
 * the latched value and will not change the latched register contents. 
 * The counter can only be cleared by reseting the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT0 . REIL_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT0_REIL_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT0_REIL_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_REIL_CNT0_REIL_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS L-BIP Error Count 1
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_B2_CNT1
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT1  VTSS_IOREG(0x02, 0, 0x0039)

/** 
 * \brief
 * Most significant word of the WIS line BIP error counter.  The counter
 * does not saturate when the maximum count has been exceeded.	Reading
 * register WIS_B2_CNT1 latches the 32-bit counter value into a pair of
 * 16-bit registers.  The most significant counter bits are associated with
 * WIS_B2_CNT1.   The least significant bits appear in WIS_B2_CNT0. 
 * Subsequest reads of address WIS_B2_CNT0 will return the latched value
 * and will not change the latched register contents.  The counter can only
 * be cleared by reseting the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT1 . B2_CNT_MSW
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT1_B2_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT1_B2_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT1_B2_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS L-BIP Error Count 0
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_B2_CNT0
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT0  VTSS_IOREG(0x02, 0, 0x003a)

/** 
 * \brief
 * Least significant word of the WIS line BIP error counter.  The counter
 * does not saturate when the maximum count has been exceeded.	Reading
 * register WIS_B2_CNT1 latches the 32-bit counter value into a pair of
 * 16-bit registers.  The most significant counter bits are associated with
 * WIS_B2_CNT1.   The least significant bits appear in WIS_B2_CNT0. 
 * Subsequest reads of address WIS_B2_CNT0 will return the latched value
 * and will not change the latched register contents.  The counter can only
 * be cleared by reseting the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT0 . B2_CNT_LSW
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT0_B2_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT0_B2_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_B2_CNT0_B2_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS P-BIP Block Error Count
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_B3_CNT
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B3_CNT  VTSS_IOREG(0x02, 0, 0x003b)

/** 
 * \brief
 * Path block error count.  The counter does not saturate when the maximum
 * count has been exceeded.  The counter can only be cleared by reseting
 * the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B3_CNT . B3_CNT
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_B3_CNT_B3_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_B3_CNT_B3_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_B3_CNT_B3_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS S-BIP Error Count
 *
 * \details
 * Register: \a WIS:WIS_IEEE_Error_Counters:WIS_B1_CNT
 */
#define VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B1_CNT  VTSS_IOREG(0x02, 0, 0x003c)

/** 
 * \brief
 * Section BIP error count.  The counter does not saturate when the maximum
 * count has been exceeded.  The counter can only be cleared by reseting
 * the WIS logic block.
 *
 * \details 
 * Field: VTSS_WIS_WIS_IEEE_Error_Counters_WIS_B1_CNT . B1_CNT
 */
#define  VTSS_F_WIS_WIS_IEEE_Error_Counters_WIS_B1_CNT_B1_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_IEEE_Error_Counters_WIS_B1_CNT_B1_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_IEEE_Error_Counters_WIS_B1_CNT_B1_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Tx_J0_Octets_0_15
 *
 * Transmitted Section Trace Message Octets
 */


/** 
 * \brief WIS Tx J0 Octets 1-0
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_1_0
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0  VTSS_IOREG(0x02, 0, 0x0040)

/** 
 * \brief
 * Contains octet 1 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0 . TX_J0_octet_1
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 0 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0 . TX_J0_octet_0
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_1_0_TX_J0_octet_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 3-2
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_3_2
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2  VTSS_IOREG(0x02, 0, 0x0041)

/** 
 * \brief
 * Contains octet 3 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2 . TX_J0_octet_3
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_3(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_3     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_3(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 2 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2 . TX_J0_octet_2
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_3_2_TX_J0_octet_2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 5-4
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_5_4
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4  VTSS_IOREG(0x02, 0, 0x0042)

/** 
 * \brief
 * Contains octet 5 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4 . TX_J0_octet_5
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 4 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4 . TX_J0_octet_4
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_5_4_TX_J0_octet_4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 7-6
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_7_6
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6  VTSS_IOREG(0x02, 0, 0x0043)

/** 
 * \brief
 * Contains octet 7 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6 . TX_J0_octet_7
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 6 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6 . TX_J0_octet_6
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_6(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_6     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_7_6_TX_J0_octet_6(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 9-8
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_9_8
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8  VTSS_IOREG(0x02, 0, 0x0044)

/** 
 * \brief
 * Contains octet 9 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8 . TX_J0_octet_9
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_9(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_9     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_9(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 8 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8 . TX_J0_octet_8
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_9_8_TX_J0_octet_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 11-10
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_11_10
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10  VTSS_IOREG(0x02, 0, 0x0045)

/** 
 * \brief
 * Contains octet 11 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10 . TX_J0_octet_11
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_11(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_11     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_11(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 10 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10 . TX_J0_octet_10
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_10(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_10     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_11_10_TX_J0_octet_10(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 13-12
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_13_12
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12  VTSS_IOREG(0x02, 0, 0x0046)

/** 
 * \brief
 * Contains octet 13 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12 . TX_J0_octet_13
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_13(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_13     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_13(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 12 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12 . TX_J0_octet_12
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_12(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_12     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_13_12_TX_J0_octet_12(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Tx J0 Octets 15-14
 *
 * \details
 * Register: \a WIS:WIS_Tx_J0_Octets_0_15:WIS_Tx_J0_Octets_15_14
 */
#define VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14  VTSS_IOREG(0x02, 0, 0x0047)

/** 
 * \brief
 * Contains octet 15 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14 . TX_J0_octet_15
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_15(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_15     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_15(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 14 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14 . TX_J0_octet_14
 */
#define  VTSS_F_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_14(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_14     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Tx_J0_Octets_0_15_WIS_Tx_J0_Octets_15_14_TX_J0_octet_14(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:WIS_Rx_J0_Octets_0_15
 *
 * Received Section Trace Message Octets
 */


/** 
 * \brief WIS Rx J0 Octets 1-0
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_1_0
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0  VTSS_IOREG(0x02, 0, 0x0048)

/** 
 * \brief
 * Contains octet 1 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0 . RX_J0_octet_1
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 0 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0 . RX_J0_octet_0
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_1_0_RX_J0_octet_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 3-2
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_3_2
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2  VTSS_IOREG(0x02, 0, 0x0049)

/** 
 * \brief
 * Contains octet 3 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2 . RX_J0_octet_3
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_3(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_3     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_3(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 2 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2 . RX_J0_octet_2
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_3_2_RX_J0_octet_2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 5-4
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_5_4
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4  VTSS_IOREG(0x02, 0, 0x004a)

/** 
 * \brief
 * Contains octet 5 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4 . RX_J0_octet_5
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 4 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4 . RX_J0_octet_4
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_5_4_RX_J0_octet_4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 7-6
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_7_6
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6  VTSS_IOREG(0x02, 0, 0x004b)

/** 
 * \brief
 * Contains octet 7 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6 . RX_J0_octet_7
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 6 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6 . RX_J0_octet_6
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_6(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_6     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_7_6_RX_J0_octet_6(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 9-8
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_9_8
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8  VTSS_IOREG(0x02, 0, 0x004c)

/** 
 * \brief
 * Contains octet 9 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8 . RX_J0_octet_9
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_9(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_9     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_9(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 8 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8 . RX_J0_octet_8
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_9_8_RX_J0_octet_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 11-10
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_11_10
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10  VTSS_IOREG(0x02, 0, 0x004d)

/** 
 * \brief
 * Contains octet 11 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10 . RX_J0_octet_11
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_11(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_11     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_11(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 10 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10 . RX_J0_octet_10
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_10(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_10     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_11_10_RX_J0_octet_10(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 13-12
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_13_12
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12  VTSS_IOREG(0x02, 0, 0x004e)

/** 
 * \brief
 * Contains octet 13 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12 . RX_J0_octet_13
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_13(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_13     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_13(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 12 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12 . RX_J0_octet_12
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_12(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_12     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_13_12_RX_J0_octet_12(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief WIS Rx J0 Octets 15-14
 *
 * \details
 * Register: \a WIS:WIS_Rx_J0_Octets_0_15:WIS_Rx_J0_Octets_15_14
 */
#define VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14  VTSS_IOREG(0x02, 0, 0x004f)

/** 
 * \brief
 * Contains octet 15 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14 . RX_J0_octet_15
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_15(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_15     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_15(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 14 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14 . RX_J0_octet_14
 */
#define  VTSS_F_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_14(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_14     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_WIS_Rx_J0_Octets_0_15_WIS_Rx_J0_Octets_15_14_RX_J0_octet_14(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:WIS_Tx_Control
 *
 * Not documented
 */


/** 
 * \brief WIS Tx Control 1
 *
 * \details
 * Register: \a WIS:WIS_Tx_Control:EWIS_TXCTRL1
 */
#define VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL1  VTSS_IOREG(0x02, 0, 0xe5ff)

/** 
 * \brief
 * Contents of SS bits in transmitted H1 overhead bytes 2-192.	(State of
 * SS bits in the first H1 byte is determined by EWIS_TX_C2_H1.TX_H1.)
 *
 * \details 
 * 0 = SS bits set to 2'b00.
 * 1 = SS bits set to 2'b10.
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL1 . TX_SS
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL1_TX_SS  VTSS_BIT(0)


/** 
 * \brief WIS Tx Control 2
 *
 * \details
 * Register: \a WIS:WIS_Tx_Control:EWIS_TXCTRL2
 */
#define VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2  VTSS_IOREG(0x02, 0, 0xe600)

/** 
 * \brief
 * Selects use of B2 block error count or bit error count mode to generate
 * the M0/M1 bytes for REI-L back reporting
 *
 * \details 
 * 0 = Bit error mode
 * 1 = Block error mode
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . REIL_TXBLK_MODE
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_REIL_TXBLK_MODE  VTSS_BIT(15)

/** 
 * \brief
 * Selects use of B3 block error count or bit error count mode to generate
 * the G1 byte for REI-P back reporting
 *
 * \details 
 * 0 = Bit error mode
 * 1 = Block error mode
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . REIP_TXBLK_MODE
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_REIP_TXBLK_MODE  VTSS_BIT(14)

/** 
 * \brief
 * Enable transmit WIS scrambler
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . SCR
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_SCR  VTSS_BIT(12)

/** 
 * \brief
 * Force transmission of a TIM-P condition within the G1 byte 
 *
 * \details 
 * 0 = Normal operation.
 * 1 = Force TIM-P
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . FRC_TX_TIMP
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_FRC_TX_TIMP  VTSS_BIT(11)

/** 
 * \brief
 * Selects ERDI as the transmit WIS G1 byte mode
 *
 * \details 
 * 0 = RDI mode
 * 1 = ERDI mode
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . ERDI_TX_MODE
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_ERDI_TX_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Selects the format of the WIS frame structure
 *
 * \details 
 * 0 = SONET mode
 * 1 = SDH mode
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . SDH_TX_MODE
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_SDH_TX_MODE  VTSS_BIT(9)

/** 
 * \brief
 * WIS transmit clear B
 *
 * \details 
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . TX_CLEAR_B
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_TX_CLEAR_B  VTSS_BIT(8)

/** 
 * \brief
 * Select the transmit WIS square wave test pattern length
 *
 * \details 
 * 0000 - 0011: Invalid
 * 0100: 4 zeros and 4 ones
 * 0101: 5 zeros and 5 ones
 * 0110: 6 zeros and 6 ones
 * 0111: 7 zeros and 7 ones
 * 1000: 8 zeros and 8 ones
 * 1001: 9 zeros and 9 ones
 * 1010: 10 zeros and 10 ones
 * 1011: 11 zeros and 11 ones
 * 1100 - 1111: Invalid
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . SQ_WV_PW
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_SQ_WV_PW(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_WIS_WIS_Tx_Control_EWIS_TXCTRL2_SQ_WV_PW     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_WIS_WIS_Tx_Control_EWIS_TXCTRL2_SQ_WV_PW(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Performance monitor
 *
 * \details 
 * 0 = Normal operation.
 * 1 = Disable AIS-L
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . TX_PERF_MON
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_TX_PERF_MON  VTSS_BIT(3)

/** 
 * \brief
 * Force transmission of RDI-L in the K2 byte
 *
 * \details 
 * 0 = Normal operation.
 * 1 = Force RDI-L
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . FRC_TX_RDI
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_FRC_TX_RDI  VTSS_BIT(2)

/** 
 * \brief
 * Force transmission of AIS-L in the K2 byte. AIS-L will take precedence
 * over RDI-L if both are asserted.
 *
 * \details 
 * 0 = Normal operation.
 * 1 = Force AIS-L
 *
 * Field: VTSS_WIS_WIS_Tx_Control_EWIS_TXCTRL2 . FRC_TX_AISL
 */
#define  VTSS_F_WIS_WIS_Tx_Control_EWIS_TXCTRL2_FRC_TX_AISL  VTSS_BIT(1)

/**
 * Register Group: \a WIS:EWIS_Tx_A1A2_Error_Injection
 *
 * Not documented
 */


/** 
 * \brief E-WIS Tx A1/A2 Error Injection 1
 *
 * \details
 * Register: \a WIS:EWIS_Tx_A1A2_Error_Injection:EWIS_FRM_ERR_INJ1
 */
#define VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ1  VTSS_IOREG(0x02, 0, 0xe601)

/** 
 * \brief
 * Enables continuous insertion of errors in transmitted frame's A1/A2
 * bytes. The A1/A2 bits in error depends on the error mask registers.
 *
 * \details 
 * 0 = Normal operation.
 * 1 = continuously send errored frame alignment words.
 *
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ1 . Send_continuous_errored_FAWs
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ1_Send_continuous_errored_FAWs  VTSS_BIT(1)

/** 
 * \brief
 * Sends a specific number of frames with errors in A1/A2 bytes when set.
 * This is a self clearing register. The number of frames sent with errors
 * depends on the FAW error count register (EWIS_FRM_ERR_INJ2).
 *
 * \details 
 * 0 = Normal operation
 * 1 = Enable sending out specific number of frames with errors FAWs.
 *
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ1 . Send_numbered_errored_FAWs
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ1_Send_numbered_errored_FAWs  VTSS_BIT(0)


/** 
 * \brief E-WIS Tx A1/A2 Error Injection 2
 *
 * \details
 * Register: \a WIS:EWIS_Tx_A1A2_Error_Injection:EWIS_FRM_ERR_INJ2
 */
#define VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ2  VTSS_IOREG(0x02, 0, 0xe602)

/** 
 * \brief
 * Sets the number of frames to send out with errors in A1/A2 bytes when
 * register bit EWIS_FRM_ERR_INJ1.Send_numbered_errored_FAWs is set high.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ2 . Frame_error_count_register
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ2_Frame_error_count_register(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ2_Frame_error_count_register     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_FRM_ERR_INJ2_Frame_error_count_register(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx First A1 Mask
 *
 * \details
 * Register: \a WIS:EWIS_Tx_A1A2_Error_Injection:EWIS_MASK_A1A
 */
#define VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1A  VTSS_IOREG(0x02, 0, 0xe603)

/** 
 * \brief
 * forces an error in the most significant bit position of the A1 byte.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1A . First_A1_mask
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1A_First_A1_mask(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1A_First_A1_mask     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1A_First_A1_mask(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS Tx Second A1 Mask
 *
 * \details
 * Register: \a WIS:EWIS_Tx_A1A2_Error_Injection:EWIS_MASK_A1B
 */
#define VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1B  VTSS_IOREG(0x02, 0, 0xe604)

/** 
 * \brief
 * forces an error in the most significant bit position of the A1 byte.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1B . Second_A1_mask
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1B_Second_A1_mask(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1B_Second_A1_mask     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A1B_Second_A1_mask(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS Tx A2 Mask
 *
 * \details
 * Register: \a WIS:EWIS_Tx_A1A2_Error_Injection:EWIS_MASK_A2
 */
#define VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A2  VTSS_IOREG(0x02, 0, 0xe605)

/** 
 * \brief
 * forces an error in the most significant bit position of the A2 byte.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A2 . A2_mask
 */
#define  VTSS_F_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A2_A2_mask(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A2_A2_mask     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_Tx_A1A2_Error_Injection_EWIS_MASK_A2_A2_mask(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:LOOP_H4_FIFO_STAT
 *
 * Not documented
 */


/** 
 * \brief LOOP_H4_FIFO_STAT
 *
 * \details
 * Register: \a WIS:LOOP_H4_FIFO_STAT:LOOP_H4_FIFO_STAT
 */
#define VTSS_WIS_LOOP_H4_FIFO_STAT_LOOP_H4_FIFO_STAT  VTSS_IOREG(0x02, 0, 0xe606)

/** 
 * \brief
 * Loopback H4 FIFO overflow status.  This is a sticky bit that latches the
 * high state.	The latch-high bit is cleared when the register is read.
 *
 * \details 
 * 0 = normal operation
 * 1 = over/under flow condition
 *
 * Field: VTSS_WIS_LOOP_H4_FIFO_STAT_LOOP_H4_FIFO_STAT . Loop_H4_FIFO_Overflow
 */
#define  VTSS_F_WIS_LOOP_H4_FIFO_STAT_LOOP_H4_FIFO_STAT_Loop_H4_FIFO_Overflow  VTSS_BIT(1)

/** 
 * \brief
 * Selects whether FIFO's sync inhibit feature is enabled
 *
 * \details 
 * 0 = Disabled
 * 1 = Enabled
 *
 * Field: VTSS_WIS_LOOP_H4_FIFO_STAT_LOOP_H4_FIFO_STAT . Loop_H4_FIFO_Sync_Inhibit
 */
#define  VTSS_F_WIS_LOOP_H4_FIFO_STAT_LOOP_H4_FIFO_STAT_Loop_H4_FIFO_Sync_Inhibit  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Tx_Overhead_Octets
 *
 * Not documented
 */


/** 
 * \brief E-WIS Tx A1/A2 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_A1_A2
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2  VTSS_IOREG(0x02, 0, 0xe611)

/** 
 * \brief
 * A1 byte to be transmitted when the TOSI data is inactive.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2 . TX_A1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * A2 byte to be transmitted when the TOSI data is inactive.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2 . TX_A2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_A1_A2_TX_A2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx Z0/E1 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_Z0_E1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1  VTSS_IOREG(0x02, 0, 0xe612)

/** 
 * \brief
 * Z0 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1 . TX_Z0
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_Z0(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_Z0     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_Z0(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * E1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1 . TX_E1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_E1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_E1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z0_E1_TX_E1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx F1/D1 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_F1_D1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1  VTSS_IOREG(0x02, 0, 0xe613)

/** 
 * \brief
 * F1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1 . TX_F1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_F1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_F1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_F1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * D1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1 . TX_D1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_D1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_D1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_F1_D1_TX_D1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D2/D3 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D2_D3
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3  VTSS_IOREG(0x02, 0, 0xe614)

/** 
 * \brief
 * D2 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3 . TX_D2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * D3 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3 . TX_D3
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D2_D3_TX_D3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx C2/H1 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_C2_H1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1  VTSS_IOREG(0x02, 0, 0xe615)

/** 
 * \brief
 * C2 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1 . TX_C2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_C2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_C2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_C2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * H1 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1 . TX_H1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_H1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_H1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_C2_H1_TX_H1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx H2/H3 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_H2_H3
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3  VTSS_IOREG(0x02, 0, 0xe616)

/** 
 * \brief
 * H2 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3 . TX_H2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * H3 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3 . TX_H3
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_H2_H3_TX_H3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx G1/K1 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_G1_K1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1  VTSS_IOREG(0x02, 0, 0xe617)

/** 
 * \brief
 * G1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1 . TX_G1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_G1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_G1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_G1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * K1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1 . TX_K1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_K1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_K1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_G1_K1_TX_K1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx K2/F2 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_K2_F2
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2  VTSS_IOREG(0x02, 0, 0xe618)

/** 
 * \brief
 * K2 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2 . TX_K2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_K2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_K2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_K2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * F2 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2 . TX_F2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_F2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_F2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_K2_F2_TX_F2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D4/D5 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D4_D5
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5  VTSS_IOREG(0x02, 0, 0xe619)

/** 
 * \brief
 * D4 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5 . TX_D4
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D4(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D4     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D4(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * D5 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5 . TX_D5
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D5(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D5     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D4_D5_TX_D5(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D6/H4 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D6_H4
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4  VTSS_IOREG(0x02, 0, 0xe61a)

/** 
 * \brief
 * D6 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4 . TX_D6
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_D6(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_D6     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_D6(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * H4 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4 . TX_H4
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_H4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_H4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D6_H4_TX_H4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D7/D8 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D7_D8
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8  VTSS_IOREG(0x02, 0, 0xe61b)

/** 
 * \brief
 * D7 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8 . TX_D7
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D7(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D7     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D7(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * D8 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8 . TX_D8
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D7_D8_TX_D8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D9/Z3 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D9_Z3
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3  VTSS_IOREG(0x02, 0, 0xe61c)

/** 
 * \brief
 * D9 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3 . TX_D9
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_D9(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_D9     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_D9(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Z3 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3 . TX_Z3
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_Z3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_Z3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D9_Z3_TX_Z3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D10/D11 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D10_D11
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11  VTSS_IOREG(0x02, 0, 0xe61d)

/** 
 * \brief
 * D10 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11 . TX_D10
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D10(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D10     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D10(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * D11 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11 . TX_D11
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D11(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D11     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D10_D11_TX_D11(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx D12/Z4 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_D12_Z4
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4  VTSS_IOREG(0x02, 0, 0xe61e)

/** 
 * \brief
 * D12 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4 . TX_D12
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_D12(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_D12     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_D12(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Z4 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4 . TX_Z4
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_Z4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_Z4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_D12_Z4_TX_Z4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx S1/Z1 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_S1_Z1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1  VTSS_IOREG(0x02, 0, 0xe61f)

/** 
 * \brief
 * S1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1 . TX_S1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_S1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_S1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_S1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Z1 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1 . TX_Z1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_Z1(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_Z1     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_S1_Z1_TX_Z1(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx Z2/E2 Octets
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_Z2_E2
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2  VTSS_IOREG(0x02, 0, 0xe620)

/** 
 * \brief
 * Z2 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2 . TX_Z2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_Z2(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_Z2     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_Z2(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * E2 byte to be transmitted when the TOSI data is inactive
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2 . TX_E2
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_E2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_E2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_Z2_E2_TX_E2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx N1 Octet
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Overhead_Octets:EWIS_TX_N1
 */
#define VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_N1  VTSS_IOREG(0x02, 0, 0xe621)

/** 
 * \brief
 * N1 byte to be transmitted
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_N1 . TX_N1
 */
#define  VTSS_F_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_N1_TX_N1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_N1_TX_N1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_Overhead_Octets_EWIS_TX_N1_TX_N1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * Register Group: \a WIS:EWIS_Tx_Trace_Message_Length_Control
 *
 * Not documented
 */


/** 
 * \brief E-WIS Tx Trace Message Length Control
 *
 * \details
 * Register: \a WIS:EWIS_Tx_Trace_Message_Length_Control:EWIS_TX_MSGLEN
 */
#define VTSS_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN  VTSS_IOREG(0x02, 0, 0xe700)

/** 
 * \brief
 * Selects length of transmitted section trace message (J0).
 *
 * \details 
 * Trace length:
 * 00:	16 bytes
 * 01:	64 bytes
 * 10:	1 byte
 * 11:	1 byte
 *
 * Field: VTSS_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN . J0_TXLEN
 */
#define  VTSS_F_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J0_TXLEN(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J0_TXLEN     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J0_TXLEN(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Selects length of transmitted path trace message (J1).
 *
 * \details 
 * Trace length:
 * 00:	16 bytes
 * 01:	64 bytes
 * 10:	1 byte
 * 11:	1 byte
 *
 * Field: VTSS_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN . J1_TXLEN
 */
#define  VTSS_F_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J1_TXLEN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J1_TXLEN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_WIS_EWIS_Tx_Trace_Message_Length_Control_EWIS_TX_MSGLEN_J1_TXLEN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a WIS:EWIS_Tx_J0_Octets_16_63
 *
 * Transmitted Section Trace Message Octets
 */


/** 
 * \brief E-WIS Tx J0 Octets 17-16
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_17_16
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16  VTSS_IOREG(0x02, 0, 0xe800)

/** 
 * \brief
 * Contains octet 17 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16 . TX_J0_octet_17
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_17(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_17     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_17(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 16 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16 . TX_J0_octet_16
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_17_16_TX_J0_octet_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 19-18
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_19_18
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18  VTSS_IOREG(0x02, 0, 0xe801)

/** 
 * \brief
 * Contains octet 19 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18 . TX_J0_octet_19
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_19(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_19     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_19(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 18 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18 . TX_J0_octet_18
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_18(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_18     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_19_18_TX_J0_octet_18(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 21-20
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_21_20
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20  VTSS_IOREG(0x02, 0, 0xe802)

/** 
 * \brief
 * Contains octet 21 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20 . TX_J0_octet_21
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_21(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_21     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_21(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 20 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20 . TX_J0_octet_20
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_20(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_20     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_21_20_TX_J0_octet_20(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 23-22
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_23_22
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22  VTSS_IOREG(0x02, 0, 0xe803)

/** 
 * \brief
 * Contains octet 23 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22 . TX_J0_octet_23
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_23(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_23     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_23(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 22 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22 . TX_J0_octet_22
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_22(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_22     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_23_22_TX_J0_octet_22(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 25-24
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_25_24
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24  VTSS_IOREG(0x02, 0, 0xe804)

/** 
 * \brief
 * Contains octet 25 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24 . TX_J0_octet_25
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_25(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_25     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_25(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 24 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24 . TX_J0_octet_24
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_25_24_TX_J0_octet_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 27-26
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_27_26
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26  VTSS_IOREG(0x02, 0, 0xe805)

/** 
 * \brief
 * Contains octet 27 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26 . TX_J0_octet_27
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_27(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_27     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_27(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 26 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26 . TX_J0_octet_26
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_26(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_26     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_27_26_TX_J0_octet_26(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 29-28
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_29_28
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28  VTSS_IOREG(0x02, 0, 0xe806)

/** 
 * \brief
 * Contains octet 29 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28 . TX_J0_octet_29
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_29(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_29     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_29(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 28 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28 . TX_J0_octet_28
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_28(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_28     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_29_28_TX_J0_octet_28(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 31-30
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_31_30
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30  VTSS_IOREG(0x02, 0, 0xe807)

/** 
 * \brief
 * Contains octet 31 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30 . TX_J0_octet_31
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_31(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_31     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_31(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 30 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30 . TX_J0_octet_30
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_30(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_30     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_31_30_TX_J0_octet_30(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 33-32
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_33_32
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32  VTSS_IOREG(0x02, 0, 0xe808)

/** 
 * \brief
 * Contains octet 33 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32 . TX_J0_octet_33
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_33(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_33     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_33(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 32 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32 . TX_J0_octet_32
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_33_32_TX_J0_octet_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 35-34
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_35_34
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34  VTSS_IOREG(0x02, 0, 0xe809)

/** 
 * \brief
 * Contains octet 35 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34 . TX_J0_octet_35
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_35(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_35     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_35(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 34 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34 . TX_J0_octet_34
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_34(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_34     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_35_34_TX_J0_octet_34(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 37-36
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_37_36
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36  VTSS_IOREG(0x02, 0, 0xe80a)

/** 
 * \brief
 * Contains octet 37 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36 . TX_J0_octet_37
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_37(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_37     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_37(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 36 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36 . TX_J0_octet_36
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_36(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_36     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_37_36_TX_J0_octet_36(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 39-38
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_39_38
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38  VTSS_IOREG(0x02, 0, 0xe80b)

/** 
 * \brief
 * Contains octet 39 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38 . TX_J0_octet_39
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_39(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_39     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_39(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 38 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38 . TX_J0_octet_38
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_38(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_38     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_39_38_TX_J0_octet_38(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 41-40
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_41_40
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40  VTSS_IOREG(0x02, 0, 0xe80c)

/** 
 * \brief
 * Contains octet 41 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40 . TX_J0_octet_41
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_41(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_41     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_41(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 40 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40 . TX_J0_octet_40
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_41_40_TX_J0_octet_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 43-42
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_43_42
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42  VTSS_IOREG(0x02, 0, 0xe80d)

/** 
 * \brief
 * Contains octet 43 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42 . TX_J0_octet_43
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_43(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_43     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_43(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 42 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42 . TX_J0_octet_42
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_42(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_42     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_43_42_TX_J0_octet_42(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 45-44
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_45_44
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44  VTSS_IOREG(0x02, 0, 0xe80e)

/** 
 * \brief
 * Contains octet 45 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44 . TX_J0_octet_45
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_45(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_45     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_45(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 44 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44 . TX_J0_octet_44
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_44(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_44     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_45_44_TX_J0_octet_44(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 47-46
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_47_46
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46  VTSS_IOREG(0x02, 0, 0xe80f)

/** 
 * \brief
 * Contains octet 47 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46 . TX_J0_octet_47
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_47(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_47     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_47(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 46 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46 . TX_J0_octet_46
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_46(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_46     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_47_46_TX_J0_octet_46(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 49-48
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_49_48
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48  VTSS_IOREG(0x02, 0, 0xe810)

/** 
 * \brief
 * Contains octet 49 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48 . TX_J0_octet_49
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_49(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_49     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_49(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 48 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48 . TX_J0_octet_48
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_49_48_TX_J0_octet_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 51-50
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_51_50
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50  VTSS_IOREG(0x02, 0, 0xe811)

/** 
 * \brief
 * Contains octet 51 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50 . TX_J0_octet_51
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_51(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_51     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_51(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 50 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50 . TX_J0_octet_50
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_50(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_50     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_51_50_TX_J0_octet_50(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 53-52
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_53_52
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52  VTSS_IOREG(0x02, 0, 0xe812)

/** 
 * \brief
 * Contains octet 53 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52 . TX_J0_octet_53
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_53(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_53     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_53(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 52 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52 . TX_J0_octet_52
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_52(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_52     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_53_52_TX_J0_octet_52(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 55-54
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_55_54
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54  VTSS_IOREG(0x02, 0, 0xe813)

/** 
 * \brief
 * Contains octet 55 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54 . TX_J0_octet_55
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_55(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_55     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_55(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 54 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54 . TX_J0_octet_54
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_54(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_54     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_55_54_TX_J0_octet_54(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 57-56
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_57_56
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56  VTSS_IOREG(0x02, 0, 0xe814)

/** 
 * \brief
 * Contains octet 57 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56 . TX_J0_octet_57
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_57(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_57     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_57(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 56 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56 . TX_J0_octet_56
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_57_56_TX_J0_octet_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 59-58
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_59_58
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58  VTSS_IOREG(0x02, 0, 0xe815)

/** 
 * \brief
 * Contains octet 59 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58 . TX_J0_octet_59
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_59(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_59     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_59(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 58 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58 . TX_J0_octet_58
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_58(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_58     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_59_58_TX_J0_octet_58(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 61-60
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_61_60
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60  VTSS_IOREG(0x02, 0, 0xe816)

/** 
 * \brief
 * Contains octet 61 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60 . TX_J0_octet_61
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_61(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_61     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_61(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 60 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60 . TX_J0_octet_60
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_60(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_60     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_61_60_TX_J0_octet_60(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J0 Octets 63-62
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J0_Octets_16_63:EWIS_Tx_J0_Octets_63_62
 */
#define VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62  VTSS_IOREG(0x02, 0, 0xe817)

/** 
 * \brief
 * Contains octet 63 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62 . TX_J0_octet_63
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_63(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_63     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_63(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 62 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62 . TX_J0_octet_62
 */
#define  VTSS_F_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_62(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_62     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J0_Octets_16_63_EWIS_Tx_J0_Octets_63_62_TX_J0_octet_62(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:EWIS_Rx_J0_Octets_16_63
 *
 * Received Section Trace Message Octets
 */


/** 
 * \brief E-WIS Rx J0 Octets 17-16
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_17_16
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16  VTSS_IOREG(0x02, 0, 0xe900)

/** 
 * \brief
 * Contains octet 17 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16 . RX_J0_octet_17
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_17(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_17     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_17(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 16 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16 . RX_J0_octet_16
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_17_16_RX_J0_octet_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 19-18
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_19_18
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18  VTSS_IOREG(0x02, 0, 0xe901)

/** 
 * \brief
 * Contains octet 19 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18 . RX_J0_octet_19
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_19(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_19     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_19(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 18 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18 . RX_J0_octet_18
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_18(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_18     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_19_18_RX_J0_octet_18(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 21-20
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_21_20
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20  VTSS_IOREG(0x02, 0, 0xe902)

/** 
 * \brief
 * Contains octet 21 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20 . RX_J0_octet_21
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_21(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_21     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_21(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 20 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20 . RX_J0_octet_20
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_20(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_20     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_21_20_RX_J0_octet_20(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 23-22
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_23_22
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22  VTSS_IOREG(0x02, 0, 0xe903)

/** 
 * \brief
 * Contains octet 23 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22 . RX_J0_octet_23
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_23(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_23     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_23(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 22 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22 . RX_J0_octet_22
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_22(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_22     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_23_22_RX_J0_octet_22(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 25-24
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_25_24
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24  VTSS_IOREG(0x02, 0, 0xe904)

/** 
 * \brief
 * Contains octet 25 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24 . RX_J0_octet_25
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_25(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_25     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_25(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 24 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24 . RX_J0_octet_24
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_25_24_RX_J0_octet_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 27-26
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_27_26
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26  VTSS_IOREG(0x02, 0, 0xe905)

/** 
 * \brief
 * Contains octet 27 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26 . RX_J0_octet_27
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_27(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_27     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_27(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 26 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26 . RX_J0_octet_26
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_26(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_26     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_27_26_RX_J0_octet_26(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 29-28
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_29_28
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28  VTSS_IOREG(0x02, 0, 0xe906)

/** 
 * \brief
 * Contains octet 29 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28 . RX_J0_octet_29
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_29(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_29     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_29(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 28 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28 . RX_J0_octet_28
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_28(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_28     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_29_28_RX_J0_octet_28(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 31-30
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_31_30
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30  VTSS_IOREG(0x02, 0, 0xe907)

/** 
 * \brief
 * Contains octet 31 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30 . RX_J0_octet_31
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_31(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_31     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_31(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 30 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30 . RX_J0_octet_30
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_30(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_30     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_31_30_RX_J0_octet_30(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 33-32
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_33_32
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32  VTSS_IOREG(0x02, 0, 0xe908)

/** 
 * \brief
 * Contains octet 33 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32 . RX_J0_octet_33
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_33(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_33     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_33(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 32 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32 . RX_J0_octet_32
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_33_32_RX_J0_octet_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 35-34
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_35_34
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34  VTSS_IOREG(0x02, 0, 0xe909)

/** 
 * \brief
 * Contains octet 35 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34 . RX_J0_octet_35
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_35(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_35     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_35(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 34 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34 . RX_J0_octet_34
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_34(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_34     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_35_34_RX_J0_octet_34(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 37-36
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_37_36
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36  VTSS_IOREG(0x02, 0, 0xe90a)

/** 
 * \brief
 * Contains octet 37 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36 . RX_J0_octet_37
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_37(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_37     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_37(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 36 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36 . RX_J0_octet_36
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_36(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_36     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_37_36_RX_J0_octet_36(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 39-38
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_39_38
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38  VTSS_IOREG(0x02, 0, 0xe90b)

/** 
 * \brief
 * Contains octet 39 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38 . RX_J0_octet_39
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_39(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_39     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_39(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 38 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38 . RX_J0_octet_38
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_38(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_38     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_39_38_RX_J0_octet_38(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 41-40
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_41_40
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40  VTSS_IOREG(0x02, 0, 0xe90c)

/** 
 * \brief
 * Contains octet 41 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40 . RX_J0_octet_41
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_41(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_41     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_41(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 40 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40 . RX_J0_octet_40
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_41_40_RX_J0_octet_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 43-42
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_43_42
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42  VTSS_IOREG(0x02, 0, 0xe90d)

/** 
 * \brief
 * Contains octet 43 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42 . RX_J0_octet_43
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_43(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_43     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_43(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 42 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42 . RX_J0_octet_42
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_42(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_42     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_43_42_RX_J0_octet_42(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 45-44
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_45_44
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44  VTSS_IOREG(0x02, 0, 0xe90e)

/** 
 * \brief
 * Contains octet 45 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44 . RX_J0_octet_45
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_45(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_45     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_45(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 44 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44 . RX_J0_octet_44
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_44(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_44     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_45_44_RX_J0_octet_44(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 47-46
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_47_46
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46  VTSS_IOREG(0x02, 0, 0xe90f)

/** 
 * \brief
 * Contains octet 47 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46 . RX_J0_octet_47
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_47(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_47     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_47(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 46 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46 . RX_J0_octet_46
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_46(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_46     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_47_46_RX_J0_octet_46(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 49-48
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_49_48
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48  VTSS_IOREG(0x02, 0, 0xe910)

/** 
 * \brief
 * Contains octet 49 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48 . RX_J0_octet_49
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_49(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_49     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_49(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 48 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48 . RX_J0_octet_48
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_49_48_RX_J0_octet_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 51-50
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_51_50
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50  VTSS_IOREG(0x02, 0, 0xe911)

/** 
 * \brief
 * Contains octet 51 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50 . RX_J0_octet_51
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_51(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_51     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_51(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 50 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50 . RX_J0_octet_50
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_50(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_50     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_51_50_RX_J0_octet_50(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 53-52
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_53_52
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52  VTSS_IOREG(0x02, 0, 0xe912)

/** 
 * \brief
 * Contains octet 53 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52 . RX_J0_octet_53
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_53(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_53     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_53(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 52 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52 . RX_J0_octet_52
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_52(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_52     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_53_52_RX_J0_octet_52(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 55-54
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_55_54
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54  VTSS_IOREG(0x02, 0, 0xe913)

/** 
 * \brief
 * Contains octet 55 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54 . RX_J0_octet_55
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_55(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_55     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_55(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 54 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54 . RX_J0_octet_54
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_54(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_54     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_55_54_RX_J0_octet_54(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 57-56
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_57_56
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56  VTSS_IOREG(0x02, 0, 0xe914)

/** 
 * \brief
 * Contains octet 57 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56 . RX_J0_octet_57
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_57(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_57     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_57(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 56 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56 . RX_J0_octet_56
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_57_56_RX_J0_octet_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 59-58
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_59_58
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58  VTSS_IOREG(0x02, 0, 0xe915)

/** 
 * \brief
 * Contains octet 59 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58 . RX_J0_octet_59
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_59(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_59     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_59(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 58 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58 . RX_J0_octet_58
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_58(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_58     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_59_58_RX_J0_octet_58(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 61-60
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_61_60
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60  VTSS_IOREG(0x02, 0, 0xe916)

/** 
 * \brief
 * Contains octet 61 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60 . RX_J0_octet_61
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_61(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_61     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_61(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 60 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60 . RX_J0_octet_60
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_60(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_60     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_61_60_RX_J0_octet_60(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J0 Octets 63-62
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J0_Octets_16_63:EWIS_Rx_J0_Octets_63_62
 */
#define VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62  VTSS_IOREG(0x02, 0, 0xe917)

/** 
 * \brief
 * Contains octet 63 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62 . RX_J0_octet_63
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_63(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_63     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_63(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 62 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62 . RX_J0_octet_62
 */
#define  VTSS_F_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_62(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_62     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J0_Octets_16_63_EWIS_Rx_J0_Octets_63_62_RX_J0_octet_62(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:EWIS_Tx_J1_Octets_16_63
 *
 * Transmitted Path Trace Message Octets
 */


/** 
 * \brief E-WIS Tx J1 Octets 17-16
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_17_16
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16  VTSS_IOREG(0x02, 0, 0xea00)

/** 
 * \brief
 * Contains octet 17 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16 . TX_J1_octet_17
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_17(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_17     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_17(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 16 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16 . TX_J1_octet_16
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_17_16_TX_J1_octet_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 19-18
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_19_18
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18  VTSS_IOREG(0x02, 0, 0xea01)

/** 
 * \brief
 * Contains octet 19 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18 . TX_J1_octet_19
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_19(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_19     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_19(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 18 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18 . TX_J1_octet_18
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_18(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_18     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_19_18_TX_J1_octet_18(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 21-20
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_21_20
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20  VTSS_IOREG(0x02, 0, 0xea02)

/** 
 * \brief
 * Contains octet 21 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20 . TX_J1_octet_21
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_21(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_21     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_21(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 20 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20 . TX_J1_octet_20
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_20(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_20     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_21_20_TX_J1_octet_20(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 23-22
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_23_22
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22  VTSS_IOREG(0x02, 0, 0xea03)

/** 
 * \brief
 * Contains octet 23 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22 . TX_J1_octet_23
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_23(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_23     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_23(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 22 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22 . TX_J1_octet_22
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_22(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_22     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_23_22_TX_J1_octet_22(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 25-24
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_25_24
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24  VTSS_IOREG(0x02, 0, 0xea04)

/** 
 * \brief
 * Contains octet 25 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24 . TX_J1_octet_25
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_25(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_25     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_25(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 24 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24 . TX_J1_octet_24
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_25_24_TX_J1_octet_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 27-26
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_27_26
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26  VTSS_IOREG(0x02, 0, 0xea05)

/** 
 * \brief
 * Contains octet 27 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26 . TX_J1_octet_27
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_27(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_27     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_27(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 26 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26 . TX_J1_octet_26
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_26(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_26     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_27_26_TX_J1_octet_26(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 29-28
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_29_28
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28  VTSS_IOREG(0x02, 0, 0xea06)

/** 
 * \brief
 * Contains octet 29 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28 . TX_J1_octet_29
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_29(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_29     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_29(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 28 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28 . TX_J1_octet_28
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_28(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_28     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_29_28_TX_J1_octet_28(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 31-30
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_31_30
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30  VTSS_IOREG(0x02, 0, 0xea07)

/** 
 * \brief
 * Contains octet 31 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30 . TX_J1_octet_31
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_31(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_31     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_31(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 30 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30 . TX_J1_octet_30
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_30(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_30     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_31_30_TX_J1_octet_30(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 33-32
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_33_32
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32  VTSS_IOREG(0x02, 0, 0xea08)

/** 
 * \brief
 * Contains octet 33 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32 . TX_J1_octet_33
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_33(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_33     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_33(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 32 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32 . TX_J1_octet_32
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_33_32_TX_J1_octet_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 35-34
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_35_34
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34  VTSS_IOREG(0x02, 0, 0xea09)

/** 
 * \brief
 * Contains octet 35 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34 . TX_J1_octet_35
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_35(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_35     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_35(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 34 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34 . TX_J1_octet_34
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_34(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_34     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_35_34_TX_J1_octet_34(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 37-36
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_37_36
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36  VTSS_IOREG(0x02, 0, 0xea0a)

/** 
 * \brief
 * Contains octet 37 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36 . TX_J1_octet_37
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_37(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_37     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_37(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 36 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36 . TX_J1_octet_36
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_36(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_36     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_37_36_TX_J1_octet_36(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 39-38
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_39_38
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38  VTSS_IOREG(0x02, 0, 0xea0b)

/** 
 * \brief
 * Contains octet 39 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38 . TX_J1_octet_39
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_39(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_39     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_39(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 38 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38 . TX_J1_octet_38
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_38(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_38     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_39_38_TX_J1_octet_38(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 41-40
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_41_40
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40  VTSS_IOREG(0x02, 0, 0xea0c)

/** 
 * \brief
 * Contains octet 41 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40 . TX_J1_octet_41
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_41(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_41     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_41(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 40 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40 . TX_J1_octet_40
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_41_40_TX_J1_octet_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 43-42
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_43_42
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42  VTSS_IOREG(0x02, 0, 0xea0d)

/** 
 * \brief
 * Contains octet 43 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42 . TX_J1_octet_43
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_43(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_43     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_43(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 42 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42 . TX_J1_octet_42
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_42(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_42     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_43_42_TX_J1_octet_42(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 45-44
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_45_44
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44  VTSS_IOREG(0x02, 0, 0xea0e)

/** 
 * \brief
 * Contains octet 45 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44 . TX_J1_octet_45
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_45(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_45     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_45(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 44 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44 . TX_J1_octet_44
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_44(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_44     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_45_44_TX_J1_octet_44(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 47-46
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_47_46
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46  VTSS_IOREG(0x02, 0, 0xea0f)

/** 
 * \brief
 * Contains octet 47 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46 . TX_J1_octet_47
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_47(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_47     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_47(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 46 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46 . TX_J1_octet_46
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_46(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_46     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_47_46_TX_J1_octet_46(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 49-48
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_49_48
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48  VTSS_IOREG(0x02, 0, 0xea10)

/** 
 * \brief
 * Contains octet 49 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48 . TX_J1_octet_49
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_49(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_49     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_49(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 48 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48 . TX_J1_octet_48
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_49_48_TX_J1_octet_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 51-50
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_51_50
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50  VTSS_IOREG(0x02, 0, 0xea11)

/** 
 * \brief
 * Contains octet 51 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50 . TX_J1_octet_51
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_51(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_51     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_51(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 50 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50 . TX_J1_octet_50
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_50(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_50     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_51_50_TX_J1_octet_50(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 53-52
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_53_52
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52  VTSS_IOREG(0x02, 0, 0xea12)

/** 
 * \brief
 * Contains octet 53 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52 . TX_J1_octet_53
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_53(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_53     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_53(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 52 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52 . TX_J1_octet_52
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_52(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_52     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_53_52_TX_J1_octet_52(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 55-54
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_55_54
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54  VTSS_IOREG(0x02, 0, 0xea13)

/** 
 * \brief
 * Contains octet 55 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54 . TX_J1_octet_55
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_55(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_55     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_55(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 54 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54 . TX_J1_octet_54
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_54(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_54     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_55_54_TX_J1_octet_54(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 57-56
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_57_56
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56  VTSS_IOREG(0x02, 0, 0xea14)

/** 
 * \brief
 * Contains octet 57 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56 . TX_J1_octet_57
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_57(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_57     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_57(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 56 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56 . TX_J1_octet_56
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_57_56_TX_J1_octet_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 59-58
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_59_58
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58  VTSS_IOREG(0x02, 0, 0xea15)

/** 
 * \brief
 * Contains octet 59 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58 . TX_J1_octet_59
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_59(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_59     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_59(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 58 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58 . TX_J1_octet_58
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_58(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_58     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_59_58_TX_J1_octet_58(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 61-60
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_61_60
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60  VTSS_IOREG(0x02, 0, 0xea16)

/** 
 * \brief
 * Contains octet 61 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60 . TX_J1_octet_61
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_61(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_61     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_61(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 60 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60 . TX_J1_octet_60
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_60(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_60     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_61_60_TX_J1_octet_60(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Tx J1 Octets 63-62
 *
 * \details
 * Register: \a WIS:EWIS_Tx_J1_Octets_16_63:EWIS_Tx_J1_Octets_63_62
 */
#define VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62  VTSS_IOREG(0x02, 0, 0xea17)

/** 
 * \brief
 * Contains octet 63 of the transmitted Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62 . TX_J1_octet_63
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_63(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_63     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_63(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 62 of the transmitted Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62 . TX_J1_octet_62
 */
#define  VTSS_F_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_62(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_62     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Tx_J1_Octets_16_63_EWIS_Tx_J1_Octets_63_62_TX_J1_octet_62(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:EWIS_Rx_J1_Octets_16_63
 *
 * Received Path Trace Message Octets
 */


/** 
 * \brief E-WIS Rx J1 Octets 17-16
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_17_16
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16  VTSS_IOREG(0x02, 0, 0xeb00)

/** 
 * \brief
 * Contains octet 17 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16 . RX_J1_octet_17
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_17(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_17     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_17(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 16 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16 . RX_J1_octet_16
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_17_16_RX_J1_octet_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 19-18
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_19_18
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18  VTSS_IOREG(0x02, 0, 0xeb01)

/** 
 * \brief
 * Contains octet 19 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18 . RX_J1_octet_19
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_19(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_19     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_19(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 18 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18 . RX_J1_octet_18
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_18(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_18     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_19_18_RX_J1_octet_18(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 21-20
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_21_20
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20  VTSS_IOREG(0x02, 0, 0xeb02)

/** 
 * \brief
 * Contains octet 21 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20 . RX_J1_octet_21
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_21(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_21     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_21(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 20 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20 . RX_J1_octet_20
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_20(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_20     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_21_20_RX_J1_octet_20(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 23-22
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_23_22
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22  VTSS_IOREG(0x02, 0, 0xeb03)

/** 
 * \brief
 * Contains octet 23 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22 . RX_J1_octet_23
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_23(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_23     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_23(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 22 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22 . RX_J1_octet_22
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_22(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_22     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_23_22_RX_J1_octet_22(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 25-24
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_25_24
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24  VTSS_IOREG(0x02, 0, 0xeb04)

/** 
 * \brief
 * Contains octet 25 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24 . RX_J1_octet_25
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_25(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_25     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_25(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 24 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24 . RX_J1_octet_24
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_25_24_RX_J1_octet_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 27-26
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_27_26
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26  VTSS_IOREG(0x02, 0, 0xeb05)

/** 
 * \brief
 * Contains octet 27 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26 . RX_J1_octet_27
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_27(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_27     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_27(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 26 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26 . RX_J1_octet_26
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_26(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_26     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_27_26_RX_J1_octet_26(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 29-28
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_29_28
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28  VTSS_IOREG(0x02, 0, 0xeb06)

/** 
 * \brief
 * Contains octet 29 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28 . RX_J1_octet_29
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_29(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_29     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_29(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 28 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28 . RX_J1_octet_28
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_28(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_28     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_29_28_RX_J1_octet_28(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 31-30
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_31_30
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30  VTSS_IOREG(0x02, 0, 0xeb07)

/** 
 * \brief
 * Contains octet 31 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30 . RX_J1_octet_31
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_31(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_31     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_31(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 30 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30 . RX_J1_octet_30
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_30(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_30     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_31_30_RX_J1_octet_30(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 33-32
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_33_32
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32  VTSS_IOREG(0x02, 0, 0xeb08)

/** 
 * \brief
 * Contains octet 33 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32 . RX_J1_octet_33
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_33(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_33     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_33(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 32 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32 . RX_J1_octet_32
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_33_32_RX_J1_octet_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 35-34
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_35_34
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34  VTSS_IOREG(0x02, 0, 0xeb09)

/** 
 * \brief
 * Contains octet 35 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34 . RX_J1_octet_35
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_35(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_35     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_35(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 34 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34 . RX_J1_octet_34
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_34(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_34     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_35_34_RX_J1_octet_34(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 37-36
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_37_36
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36  VTSS_IOREG(0x02, 0, 0xeb0a)

/** 
 * \brief
 * Contains octet 37 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36 . RX_J1_octet_37
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_37(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_37     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_37(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 36 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36 . RX_J1_octet_36
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_36(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_36     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_37_36_RX_J1_octet_36(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 39-38
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_39_38
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38  VTSS_IOREG(0x02, 0, 0xeb0b)

/** 
 * \brief
 * Contains octet 39 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38 . RX_J1_octet_39
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_39(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_39     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_39(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 38 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38 . RX_J1_octet_38
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_38(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_38     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_39_38_RX_J1_octet_38(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 41-40
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_41_40
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40  VTSS_IOREG(0x02, 0, 0xeb0c)

/** 
 * \brief
 * Contains octet 41 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40 . RX_J1_octet_41
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_41(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_41     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_41(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 40 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40 . RX_J1_octet_40
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_41_40_RX_J1_octet_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 43-42
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_43_42
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42  VTSS_IOREG(0x02, 0, 0xeb0d)

/** 
 * \brief
 * Contains octet 43 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42 . RX_J1_octet_43
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_43(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_43     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_43(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 42 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42 . RX_J1_octet_42
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_42(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_42     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_43_42_RX_J1_octet_42(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 45-44
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_45_44
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44  VTSS_IOREG(0x02, 0, 0xeb0e)

/** 
 * \brief
 * Contains octet 45 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44 . RX_J1_octet_45
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_45(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_45     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_45(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 44 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44 . RX_J1_octet_44
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_44(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_44     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_45_44_RX_J1_octet_44(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 47-46
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_47_46
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46  VTSS_IOREG(0x02, 0, 0xeb0f)

/** 
 * \brief
 * Contains octet 47 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46 . RX_J1_octet_47
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_47(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_47     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_47(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 46 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46 . RX_J1_octet_46
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_46(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_46     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_47_46_RX_J1_octet_46(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 49-48
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_49_48
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48  VTSS_IOREG(0x02, 0, 0xeb10)

/** 
 * \brief
 * Contains octet 49 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48 . RX_J1_octet_49
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_49(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_49     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_49(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 48 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48 . RX_J1_octet_48
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_49_48_RX_J1_octet_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 51-50
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_51_50
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50  VTSS_IOREG(0x02, 0, 0xeb11)

/** 
 * \brief
 * Contains octet 51 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50 . RX_J1_octet_51
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_51(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_51     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_51(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 50 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50 . RX_J1_octet_50
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_50(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_50     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_51_50_RX_J1_octet_50(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 53-52
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_53_52
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52  VTSS_IOREG(0x02, 0, 0xeb12)

/** 
 * \brief
 * Contains octet 53 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52 . RX_J1_octet_53
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_53(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_53     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_53(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 52 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52 . RX_J1_octet_52
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_52(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_52     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_53_52_RX_J1_octet_52(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 55-54
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_55_54
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54  VTSS_IOREG(0x02, 0, 0xeb13)

/** 
 * \brief
 * Contains octet 55 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54 . RX_J1_octet_55
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_55(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_55     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_55(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 54 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54 . RX_J1_octet_54
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_54(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_54     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_55_54_RX_J1_octet_54(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 57-56
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_57_56
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56  VTSS_IOREG(0x02, 0, 0xeb14)

/** 
 * \brief
 * Contains octet 57 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56 . RX_J1_octet_57
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_57(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_57     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_57(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 56 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56 . RX_J1_octet_56
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_57_56_RX_J1_octet_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 59-58
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_59_58
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58  VTSS_IOREG(0x02, 0, 0xeb15)

/** 
 * \brief
 * Contains octet 59 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58 . RX_J1_octet_59
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_59(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_59     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_59(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 58 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58 . RX_J1_octet_58
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_58(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_58     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_59_58_RX_J1_octet_58(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 61-60
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_61_60
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60  VTSS_IOREG(0x02, 0, 0xeb16)

/** 
 * \brief
 * Contains octet 61 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60 . RX_J1_octet_61
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_61(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_61     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_61(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 60 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60 . RX_J1_octet_60
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_60(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_60     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_61_60_RX_J1_octet_60(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief E-WIS Rx J1 Octets 63-62
 *
 * \details
 * Register: \a WIS:EWIS_Rx_J1_Octets_16_63:EWIS_Rx_J1_Octets_63_62
 */
#define VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62  VTSS_IOREG(0x02, 0, 0xeb17)

/** 
 * \brief
 * Contains octet 63 of the received Section Trace Message. 
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62 . RX_J1_octet_63
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_63(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_63     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_63(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Contains octet 62 of the received Section Trace Message.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62 . RX_J1_octet_62
 */
#define  VTSS_F_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_62(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_62     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Rx_J1_Octets_16_63_EWIS_Rx_J1_Octets_63_62_RX_J1_octet_62(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:EWIS_RX_FRMR_CFG
 *
 * Not documented
 */


/** 
 * \brief E-WIS Rx Framer Control 1
 *
 * \details
 * Register: \a WIS:EWIS_RX_FRMR_CFG:EWIS_RX_FRM_CTRL1
 */
#define VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1  VTSS_IOREG(0x02, 0, 0xec00)

/** 
 * \brief
 * The number of consecutive A1 octets the receive framer must find before
 * it can exit the HUNT state.
 *
 * \details 
 * 0: Undefined
 * 1-16: 1-16
 * 17-31: Undefined
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1 . HUNT_A1
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_HUNT_A1(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_HUNT_A1     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_HUNT_A1(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/** 
 * \brief
 * The number of consecutive A1 octets in the presync pattern preceding the
 * first A2 octet.
 *
 * \details 
 * 0: 1
 * 1-16: 1-16
 * 17-31: 16
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1 . PRESYNC_A1
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A1(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A1     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A1(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * The number of consecutive A2 octets in the presync pattern following the
 * last A1 octet.
 *
 * \details 
 * 0: Only the four MSB of the first A2 byte are compared
 * 1-16: 1-16
 * 17-31: 16
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1 . PRESYNC_A2
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A2(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A2     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL1_PRESYNC_A2(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief E-WIS Rx Framer Control 2
 *
 * \details
 * Register: \a WIS:EWIS_RX_FRMR_CFG:EWIS_RX_FRM_CTRL2
 */
#define VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2  VTSS_IOREG(0x02, 0, 0xec01)

/** 
 * \brief
 * Synchronization pattern to be used after the presync pattern has been
 * detected
 *
 * \details 
 * 0: Sync pattern is A1 plus 4 most significant bits of A2
 * 1: Sync pattern is 2 A1s plus 1 A2 (A1A1A2)
 * 2-16: Sync pattern is the number of consecutive A1s followed by the same
 * number of A2s I.e. the sync pattern is A1A1A2A2 when 2 is the setting)
 * 17-31: Undefined
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2 . SYNC_PAT
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_PAT(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_PAT     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_PAT(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Number of consecutive frame boundaries to be detected after finding the
 * presync pattern before the framer can enter the SYNC state.
 *
 * \details 
 * 0: 1
 * 1-15: 1-15
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2 . SYNC_ENTRY_CNT
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_ENTRY_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_ENTRY_CNT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_ENTRY_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Number of consecutive frame boundary location errors tolerated/detected
 * before exiting the SYNC state.
 *
 * \details 
 * 0: 1
 * 1-15: 1-15
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2 . SYNC_EXIT_CNT
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_EXIT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_EXIT_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_RX_FRM_CTRL2_SYNC_EXIT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief E-WIS Loss of Frame Control 1
 *
 * \details
 * Register: \a WIS:EWIS_RX_FRMR_CFG:EWIS_LOF_CTRL1
 */
#define VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1  VTSS_IOREG(0x02, 0, 0xec02)

/** 
 * \brief
 * Defines the number of frames periods (nominally 125 uS) during which OOF
 * must persist to trigger LOF. This is not a count of continuous frames.
 * An integrating counter is used.
 *
 * \details 
 * 0x0: Undefined
 * 0x1: 1 frame time (125us)
 * 0x2: 2 frame times 250us)
 *  :
 * 0x18: 24 frame times 3ms)
 * 0x3F: 63 frame times 7.875ms)
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1 . LOF_T1
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T1(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T1     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T1(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Defines the number of consecutive frame periods (nominally 125 uS)
 * during which OOF status must not be true in order to clear loss of frame
 * set count (the counter associated with EWIS_LOF_CTRL1.LOF_T1).
 *
 * \details 
 * 0x0: Undefined
 * 0x1: 1 frame time (125us)
 * 0x2: 2 frame times 250us)
 *  :
 * 0x18: 24 frame times 3ms)
 * 0x3F: 63 frame times 7.875ms)
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1 . LOF_T2
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T2(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T2     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL1_LOF_T2(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief E-WIS Loss of Frame Control 2
 *
 * \details
 * Register: \a WIS:EWIS_RX_FRMR_CFG:EWIS_LOF_CTRL2
 */
#define VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL2  VTSS_IOREG(0x02, 0, 0xec03)

/** 
 * \brief
 * Defines number of consecutive frames (nominally 125 uS) for which the
 * receive framer must be in its sync state in order to clear the LOF
 * status
 *
 * \details 
 * 0x0: Undefined
 * 0x1: 1 frame time (125us)
 * 0x2: 2 frame times 250us)
 *  :
 * 0x18: 24 frame times 3ms)
 * 0x3F: 63 frame times 7.875ms)
 *
 * Field: VTSS_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL2 . LOF_T3
 */
#define  VTSS_F_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL2_LOF_T3(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL2_LOF_T3     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_WIS_EWIS_RX_FRMR_CFG_EWIS_LOF_CTRL2_LOF_T3(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/**
 * Register Group: \a WIS:EWIS_Rx_Control_1
 *
 * Not documented
 */


/** 
 * \brief E-WIS Rx Control 1
 *
 * \details
 * Register: \a WIS:EWIS_Rx_Control_1:EWIS_RX_CTRL1
 */
#define VTSS_WIS_EWIS_Rx_Control_1_EWIS_RX_CTRL1  VTSS_IOREG(0x02, 0, 0xec10)

/** 
 * \brief
 * Enable the WIS descrambler
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Rx_Control_1_EWIS_RX_CTRL1 . DSCR_ENA
 */
#define  VTSS_F_WIS_EWIS_Rx_Control_1_EWIS_RX_CTRL1_DSCR_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Selects whether or not the fixed stuff bytes are included in the receive
 * Path BIP error calculation
 *
 * \details 
 * 0 = The fixed stuff bytes are excluded from the B3 calculation.
 * 1 = The fixed stuff bytes are included in the B3 calculation.
 *
 * Field: VTSS_WIS_EWIS_Rx_Control_1_EWIS_RX_CTRL1 . B3_CALC_MODE
 */
#define  VTSS_F_WIS_EWIS_Rx_Control_1_EWIS_RX_CTRL1_B3_CALC_MODE  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Rx_Trace_Message_Length_Control
 *
 * Not documented
 */


/** 
 * \brief E-WIS Rx Trace Message Length Control
 *
 * \details
 * Register: \a WIS:EWIS_Rx_Trace_Message_Length_Control:EWIS_RX_MSGLEN
 */
#define VTSS_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN  VTSS_IOREG(0x02, 0, 0xec20)

/** 
 * \brief
 * Selects the expected length of the received section trace message (J0).
 *
 * \details 
 * Trace length:
 * 00:	16 bytes
 * 01:	64 bytes
 * 10:	1 byte
 * 11:	1 byte
 *
 * Field: VTSS_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN . J0_RX_LEN
 */
#define  VTSS_F_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J0_RX_LEN(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J0_RX_LEN     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J0_RX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Selects the length of the expected path trace message (J1).
 *
 * \details 
 * Trace length:
 * 00:	16 bytes
 * 01:	64 bytes
 * 10:	1 byte
 * 11:	1 byte
 *
 * Field: VTSS_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN . J1_RX_LEN
 */
#define  VTSS_F_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J1_RX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J1_RX_LEN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_WIS_EWIS_Rx_Trace_Message_Length_Control_EWIS_RX_MSGLEN_J1_RX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a WIS:EWIS_RX_ERR_FRC
 *
 * Not documented
 */


/** 
 * \brief E-WIS Rx Error Force Control 1
 *
 * \details
 * Register: \a WIS:EWIS_RX_ERR_FRC:EWIS_RX_ERR_FRC1
 */
#define VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1  VTSS_IOREG(0x02, 0, 0xec30)

/** 
 * \brief
 * Force a Loss of Optical Carrier (LOPC) condition.  The LOPC alarm state
 * is asserted in EWIS_INTR_STAT2.LOPC_STAT when this bit is set and
 * changes the SONET framer to an Out of Frame (OOF) state when
 * RXLOF_ON_LOPC=1.  The LOPC interrupt pending register in the GPIO
 * regsiter space is not affected by this bit.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Force LOPC
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_LOPC
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_LOPC  VTSS_BIT(12)

/** 
 * \brief
 * Force a Loss of Signal (LOS) conditon in the WIS receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Forced receive LOS
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_LOS
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_LOS  VTSS_BIT(11)

/** 
 * \brief
 * Force the receive framer into the out-of-frame (OOF) state
 *
 * \details 
 * 0 = Normal operation.
 * 1 = Force receive OOF
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_OOF
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_OOF  VTSS_BIT(10)

/** 
 * \brief
 * Selects whether or not the LOPC input has any effect on alarm conditions
 * detected by the device
 *
 * \details 
 * 0 = A LOPC condition does not effect the state of the LOF or SEF status,
 * nor the state of the receive path framer.
 * 1 = LOF and SEF are asserted and the receive path framer is put into its
 * out-of-frame state during a LOPC condition.
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . RXLOF_ON_LOPC
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_RXLOF_ON_LOPC  VTSS_BIT(8)

/** 
 * \brief
 * The number of consecutive frames required to qualify the setting and
 * clearing of AIS-L and RDI-L flags received in the K1/K2 overhead bytes.
 *
 * \details 
 * 3-15: Threshold value
 * All others: Reserved
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . APS_THRES
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_APS_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_APS_THRES     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_APS_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Force a Line Alarm Indication Signal (AIS-L) condition in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx AIS-L condition
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_RX_AISL
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_RX_AISL  VTSS_BIT(3)

/** 
 * \brief
 * Force a Line Remote Defect Identifier (RDI-L) condition in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx RDI-L condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_RX_RDIL
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_RX_RDIL  VTSS_BIT(2)

/** 
 * \brief
 * Force a Path Alarm Indication Signal (AIS-P) condition in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx AIS-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_RX_AISP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_RX_AISP  VTSS_BIT(1)

/** 
 * \brief
 * Force a Loss of Pointer (LOP) condition to the starting location of the
 * frame's SPE (synchronous payload envelope) in the WIS receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx LOP condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1 . FRC_RX_LOP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC1_FRC_RX_LOP  VTSS_BIT(0)


/** 
 * \brief E-WIS Rx Error Force Control 2
 *
 * \details
 * Register: \a WIS:EWIS_RX_ERR_FRC:EWIS_RX_ERR_FRC2
 */
#define VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2  VTSS_IOREG(0x02, 0, 0xec31)

/** 
 * \brief
 * Force a Unequiped Path (UNEQ-P) defect in the WIS receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx UNEQ-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_UNEQP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_UNEQP  VTSS_BIT(15)

/** 
 * \brief
 * Force a Payload Label Mismatch (PLM-P) defect in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx PLM-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_PLMP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_PLMP  VTSS_BIT(14)

/** 
 * \brief
 * Force a far-end Path Remote Defect Identifier condition in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end RDI-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_RDIP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_RDIP  VTSS_BIT(13)

/** 
 * \brief
 * Force a far-end Path Alarm Indication Signal condition in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end AIS-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_FE_AISP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_FE_AISP  VTSS_BIT(12)

/** 
 * \brief
 * Force a far-end Unequiped Path defect in the WIS receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end UNEQ-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_FE_UNEQP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_FE_UNEQP  VTSS_BIT(11)

/** 
 * \brief
 * Force a far-end Payload Label Mismatch defect in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end PLM-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_FE_PLMP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_FE_PLMP  VTSS_BIT(10)

/** 
 * \brief
 * Force a Path Remote Error Indication (REI-P) condition in the WIS
 * receive data path.  The error is reflected in register
 * EWIS_INTR_STAT2.REIP_STAT.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx REI-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_REIP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_REIP  VTSS_BIT(9)

/** 
 * \brief
 * Force a Line Remote Error Indication (REI-L) condition in the WIS
 * receive data path.  The error is reflected in register
 * EWIS_INTR_STAT2.REIL_STAT.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx REI-L condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_REIL
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_REIL  VTSS_BIT(8)

/** 
 * \brief
 * Force a Severely Errored Frame (SEF) condition in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx SEF condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_SEF
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_SEF  VTSS_BIT(7)

/** 
 * \brief
 * Force a Loss of Frame (LOF) condition in the WIS receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx LOF condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_LOF
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_LOF  VTSS_BIT(6)

/** 
 * \brief
 * Force a PMTICK B1 BIP error condition (B1NZ) in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into PMTICK B1 BIP error condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_B1
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_B1  VTSS_BIT(5)

/** 
 * \brief
 * Force a PMTICK B2 BIP error condition (B2NZ) in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into PMTICK B2 BIP error condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_B2
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_B2  VTSS_BIT(4)

/** 
 * \brief
 * Force a PMTICK B3 BIP error condition (B3NZ) in the WIS receive data
 * path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into PMTICK B3 BIP error condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_RX_B3
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_RX_B3  VTSS_BIT(3)

/** 
 * \brief
 * Force a Loss of Code-group Delineation (LCD-P) defect in the WIS receive
 * data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx LCD-P condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_LCDP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_LCDP  VTSS_BIT(2)

/** 
 * \brief
 * Force a far-end line BIP error condition (far-end B2NZ) in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end line BIP error condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_REIL
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_REIL  VTSS_BIT(1)

/** 
 * \brief
 * Force a far-end path BIP error condition (far-end B3NZ) in the WIS
 * receive data path
 *
 * \details 
 * 0 = Normal operation
 * 1 = Device forced into Rx far-end path BIP error condition 
 *
 * Field: VTSS_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2 . FRC_REIP
 */
#define  VTSS_F_WIS_EWIS_RX_ERR_FRC_EWIS_RX_ERR_FRC2_FRC_REIP  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Mode_Control
 *
 * Not documented
 */


/** 
 * \brief E-WIS Mode Control
 *
 * \details
 * Register: \a WIS:EWIS_Mode_Control:EWIS_MODE_CTRL
 */
#define VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL  VTSS_IOREG(0x02, 0, 0xec40)

/** 
 * \brief
 * Selects pointer type interpretation mode
 *
 * \details 
 * 0 = SONET mode.  All 192 H1 and H2 bytes are used to determine the
 * pointer type.
 * 1 = SDH mode.  Only the first 64 H1 and H2 bytes are used to determine
 * the pointer type.
 *
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . PTR_MODE
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_PTR_MODE  VTSS_BIT(14)

/** 
 * \brief
 * Selects pointer increment/decrement rules.
 *
 * \details 
 * 0 = Pointer increment/ decrement is declared when 8 of the 10 D/I bits
 * in the H1 and H2 bytes match
 * 1 = Pointer increment/ decrement is declared by majority rules
 *
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . PTR_RULES
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_PTR_RULES  VTSS_BIT(13)

/** 
 * \brief
 * Selects how REI is extracted from the M0/M1 bytes in the WIS receive
 * data path.
 *
 * \details 
 * 0 = SONET mode enabled. Uses M0 only.
 * 1 = SDH mode enabled. Uses M0 and M1.
 *
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . REI_MODE
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_REI_MODE  VTSS_BIT(12)

/** 
 * \brief
 * Determines whether the SS bits in the H1 byte are checked when
 * processing the received H1/H2 pointer.
 *
 * \details 
 * 0 = SS bits are ignored
 * 1 = SS bits must match 2'b10 to be considered a valid H1 byte
 *
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . RX_SS_MODE
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_RX_SS_MODE  VTSS_BIT(11)

/** 
 * \brief
 * Selects how ERDI-P/RDI-P is extracted from the G1 byte in the WIS
 * received data
 *
 * \details 
 * 0 = RDI-P is reported in bit 5.  Bits 6 and 7 are unused.
 * 1 = ERDI is reported in bits 5-7
 *
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . RX_ERDI_MODE
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_RX_ERDI_MODE  VTSS_BIT(8)

/** 
 * \brief
 * Expected C2 receive octet. A PLM-P alarm is generated if this octet
 * value is not received.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL . C2_EXP
 */
#define  VTSS_F_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_C2_EXP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_C2_EXP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WIS_EWIS_Mode_Control_EWIS_MODE_CTRL_C2_EXP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a WIS:EWIS_PRBS31_CFG_STAT
 *
 * Not documented
 */


/** 
 * \brief E-WIS PRBS31 Analyzer Control
 *
 * \details
 * Register: \a WIS:EWIS_PRBS31_CFG_STAT:EWIS_PRBS31_ANA_CTRL
 */
#define VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_CTRL  VTSS_IOREG(0x02, 0, 0xec50)

/** 
 * \brief
 * Inject a single bit error into the WIS PRBS31 pattern checker. A single
 * bit error injected in the data stream will result in the error counter
 * incrementing by 3 (1 error for each tap of the checker).
 *
 * \details 
 * 0 = Normal operation
 * 1 = Inject error
 *
 * Field: VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_CTRL . PRBS31_FRC_ERR
 */
#define  VTSS_F_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_CTRL_PRBS31_FRC_ERR  VTSS_BIT(1)

/** 
 * \brief
 * Force the PRBS31 pattern error counter (WIS_TSTPAT_CNT) to a value of
 * 65528. This can be useful for testing the saturating feature of the
 * counter.  Forcing the counter to 65528 with this bit has no affect on
 * register EWIS_PRBS31_ANA_STAT.PRBS31_ERR.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Force the PRBS31 error counter to a value of 65528
 *
 * Field: VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_CTRL . PRBS31_FRC_SAT
 */
#define  VTSS_F_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_CTRL_PRBS31_FRC_SAT  VTSS_BIT(0)


/** 
 * \brief E-WIS PRBS31 Analyzer Status
 *
 * \details
 * Register: \a WIS:EWIS_PRBS31_CFG_STAT:EWIS_PRBS31_ANA_STAT
 */
#define VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_STAT  VTSS_IOREG(0x02, 0, 0xec51)

/** 
 * \brief
 * Status bit indicating if the WIS PRBS31 error counter is non-zero.
 *
 * \details 
 * 0 = Counter is zero
 * 1 = Counter is non-zero
 *
 * Field: VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_STAT . PRBS31_ERR
 */
#define  VTSS_F_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_STAT_PRBS31_ERR  VTSS_BIT(1)

/** 
 * \brief
 * Indicates when the Rx WIS PRBS31 pattern checker is synchronized to the
 * incoming data.
 *
 * \details 
 * 0 = PRBS31 pattern checker is not synchronized to the data. PRBS31 error
 * counter value is not valid
 * 1 = PRBS31 pattern checker is synchronized to the data
 *
 * Field: VTSS_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_STAT . PRBS31_ANA_STATE
 */
#define  VTSS_F_WIS_EWIS_PRBS31_CFG_STAT_EWIS_PRBS31_ANA_STAT_PRBS31_ANA_STATE  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Performance_Monitor_Control
 *
 * Not documented
 */


/** 
 * \brief E-WIS Performance Monitor Control
 *
 * \details
 * Register: \a WIS:EWIS_Performance_Monitor_Control:EWIS_PMTICK_CTRL
 */
#define VTSS_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL  VTSS_IOREG(0x02, 0, 0xec60)

/** 
 * \brief
 * Sets the interval for updating the PMTICK error counters when the
 * PMTICK_SRC bit is 1. The value represents the number of 125uS increments
 * between PMTICK events.
 *
 * \details 
 * 0: Undefined
 * 1: Undefined
 * 2: 250 uS
 *  :
 * 8: 1 mS
 * 8000: 1 sec
 * 8191: 1.024 sec
 *
 * Field: VTSS_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL . PMTICK_DUR
 */
#define  VTSS_F_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_DUR(x)  VTSS_ENCODE_BITFIELD(x,3,13)
#define  VTSS_M_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_DUR     VTSS_ENCODE_BITMASK(3,13)
#define  VTSS_X_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_DUR(x)  VTSS_EXTRACT_BITFIELD(x,3,13)

/** 
 * \brief
 * Enable the PMTICK counters to be updated on a PMTICK event. The source
 * of the PMTICK event is determined by the PMTICK_SRC bit.
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL . PMTICK_ENA
 */
#define  VTSS_F_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Selects how the PMTICK counters are updated. The PMTICK counters are
 * updated with the selected source only if the PMTICK enable bit is set.
 *
 * \details 
 * 0 = PMTICK counters updated on a rising edge of the (GPIO) PMTICK pin
 * 1 = PMTICK counters updated when the PMTICK counter reaches its terminal
 * count (PMTICK_DUR).
 *
 * Field: VTSS_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL . PMTICK_SRC
 */
#define  VTSS_F_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_SRC  VTSS_BIT(1)

/** 
 * \brief
 * Force the PMTICK counters to update, regardless of the PMTICK_ENA or
 * PMTICK_SRC settings.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Forces PMTICK event
 *
 * Field: VTSS_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL . PMTICK_FRC
 */
#define  VTSS_F_WIS_EWIS_Performance_Monitor_Control_EWIS_PMTICK_CTRL_PMTICK_FRC  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Counter_Configuration
 *
 * Not documented
 */


/** 
 * \brief E-WIS Counter Configuration
 *
 * \details
 * Register: \a WIS:EWIS_Counter_Configuration:EWIS_CNT_CFG
 */
#define VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG  VTSS_IOREG(0x02, 0, 0xec61)

/** 
 * \brief
 * Enable block mode (increment once for each errored frame) counting for
 * the B1 BIP PMTICK counter.
 *
 * \details 
 * 0 = Bit mode
 * 1 = Block mode
 *
 * Field: VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG . B1_BLK_MODE
 */
#define  VTSS_F_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG_B1_BLK_MODE  VTSS_BIT(11)

/** 
 * \brief
 * Enable block mode (increment once for each errored frame) counting for
 * the B2 BIP PMTICK counter
 *
 * \details 
 * 0 = Bit mode
 * 1 = Block mode
 *
 * Field: VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG . B2_BLK_MODE
 */
#define  VTSS_F_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG_B2_BLK_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Enable block mode (increment once for each errored frame) counting for
 * the B3 BIP PMTICK counter
 *
 * \details 
 * 0 = Bit mode
 * 1 = Block mode
 *
 * Field: VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG . B3_BLK_MODE
 */
#define  VTSS_F_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG_B3_BLK_MODE  VTSS_BIT(9)

/** 
 * \brief
 * Enable block mode (increment once for each errored frame) counting for
 * the REI-P (far-end B3 error count in the G1 byte) PMTICK counter
 *
 * \details 
 * 0 = Bit mode
 * 1 = Block mode
 *
 * Field: VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG . REIP_BLK_MODE
 */
#define  VTSS_F_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG_REIP_BLK_MODE  VTSS_BIT(5)

/** 
 * \brief
 * Enable block mode (increment once for each errored frame) counting for
 * the REI-L (far-end B2 error count in the M0/M1 byte) PMTICK counter
 *
 * \details 
 * 0 = Bit mode
 * 1 = Block mode
 *
 * Field: VTSS_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG . REIL_BLK_MODE
 */
#define  VTSS_F_WIS_EWIS_Counter_Configuration_EWIS_CNT_CFG_REIL_BLK_MODE  VTSS_BIT(4)

/**
 * Register Group: \a WIS:EWIS_Counter_Status
 *
 * Not documented
 */


/** 
 * \brief E-WIS Counter Status
 *
 * \details
 * Register: \a WIS:EWIS_Counter_Status:EWIS_CNT_STAT
 */
#define VTSS_WIS_EWIS_Counter_Status_EWIS_CNT_STAT  VTSS_IOREG(0x02, 0, 0xec62)

/** 
 * \brief
 * Status bit indicating if the REI-P (far-end B3) PMTICK counter is
 * non-zero
 *
 * \details 
 * 0 = Counter is zero
 * 1 = Counter is non-zero
 *
 * Field: VTSS_WIS_EWIS_Counter_Status_EWIS_CNT_STAT . REIP_CNT_STAT
 */
#define  VTSS_F_WIS_EWIS_Counter_Status_EWIS_CNT_STAT_REIP_CNT_STAT  VTSS_BIT(2)

/** 
 * \brief
 * Status bit indicating if the REI-L (far-end B2) PMTICK counter is
 * non-zero
 *
 * \details 
 * 0 = Counter is zero
 * 1 = Counter is non-zero
 *
 * Field: VTSS_WIS_EWIS_Counter_Status_EWIS_CNT_STAT . REIL_CNT_STAT
 */
#define  VTSS_F_WIS_EWIS_Counter_Status_EWIS_CNT_STAT_REIL_CNT_STAT  VTSS_BIT(1)

/** 
 * \details 
 * 0 = B2 error counter is zero
 * 1 = B2 error counter is non zero
 *
 * Field: VTSS_WIS_EWIS_Counter_Status_EWIS_CNT_STAT . B2_statistical_error_event
 */
#define  VTSS_F_WIS_EWIS_Counter_Status_EWIS_CNT_STAT_B2_statistical_error_event  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_REIP_CNT
 *
 * Not documented
 */


/** 
 * \brief E-WIS P-REI Counter 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_REIP_CNT:EWIS_REIP_CNT1
 */
#define VTSS_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT1  VTSS_IOREG(0x02, 0, 0xec80)

/** 
 * \brief
 * PMTICK statistical error count of the far-end B3 errors reported in the
 * G1 byte. 16 MSB are in this register, 16 LSB are in the next register.
 * The count is updated only on a PMTICK event. The counter saturates when
 * the maximum error count is exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT1 . REIP_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT1_REIP_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT1_REIP_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT1_REIP_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS P-REI Counter 0 LSW
 *
 * \details
 * Register: \a WIS:EWIS_REIP_CNT:EWIS_REIP_CNT0
 */
#define VTSS_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT0  VTSS_IOREG(0x02, 0, 0xec81)

/** 
 * \brief
 * PMTICK statistical error count of the far-end B3 errors reported in the
 * G1 byte. 16 LSB are in this register, 16 MSB are in the previous
 * register. The count is updated only on a PMTICK event. The counter
 * saturates when the maximum error count is exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT0 . REIP_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT0_REIP_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT0_REIP_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_REIP_CNT_EWIS_REIP_CNT0_REIP_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:EWIS_REIL_CNT
 *
 * Not documented
 */


/** 
 * \brief E-WIS L-REI Counter 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_REIL_CNT:EWIS_REIL_CNT1
 */
#define VTSS_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT1  VTSS_IOREG(0x02, 0, 0xec90)

/** 
 * \brief
 * PMTICK statistical error count of the far-end B2 errors reported in the
 * M0/M1 bytes. 16 MSB are in this register, 16 LSB are in the next
 * register. The count is updated only on a PMTICK event. The counter
 * saturates when the maximum error count is exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT1 . REIL_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT1_REIL_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT1_REIL_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT1_REIL_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS L-REI Counter 0 LSW
 *
 * \details
 * Register: \a WIS:EWIS_REIL_CNT:EWIS_REIL_CNT0
 */
#define VTSS_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT0  VTSS_IOREG(0x02, 0, 0xec91)

/** 
 * \brief
 * PMTICK statistical error count of the far-end B2 errors reported in the
 * M0/M1 bytes. 16 LSB are in this register, 16 MSB are in the previous
 * register. The count is updated only on a PMTICK event. The counter
 * saturates when the maximum error count is exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT0 . REIL_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT0_REIL_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT0_REIL_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_REIL_CNT_EWIS_REIL_CNT0_REIL_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:EWIS_B1_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief E-WIS S-BIP Error Counter 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_B1_ERR_CNT:EWIS_B1_ERR_CNT1
 */
#define VTSS_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT1  VTSS_IOREG(0x02, 0, 0xecb0)

/** 
 * \brief
 * PMTICK statistical error count of the B1 BIP errors. 16 MSB are in this
 * register, 16 LSB are in the next register. The count is updated only on
 * a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT1 . B1_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT1_B1_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT1_B1_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT1_B1_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS S-BIP Error Counter 0 LSW
 *
 * \details
 * Register: \a WIS:EWIS_B1_ERR_CNT:EWIS_B1_ERR_CNT0
 */
#define VTSS_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT0  VTSS_IOREG(0x02, 0, 0xecb1)

/** 
 * \brief
 * PMTICK statistical error count of the B1 BIP errors. 16 LSB are in this
 * register, 16 MSB are in the previous register. The count is updated only
 * on a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT0 . B1_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT0_B1_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT0_B1_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B1_ERR_CNT_EWIS_B1_ERR_CNT0_B1_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:EWIS_B2_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief E-WIS L-BIP Error Counter 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_B2_ERR_CNT:EWIS_B2_ERR_CNT1
 */
#define VTSS_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT1  VTSS_IOREG(0x02, 0, 0xecb2)

/** 
 * \brief
 * PMTICK statistical error count of the B2 BIP errors. 16 MSB are in this
 * register, 16 LSB are in the next register. The count is updated only on
 * a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT1 . B2_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT1_B2_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT1_B2_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT1_B2_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS L-BIP Error Counter 0 LSW
 *
 * \details
 * Register: \a WIS:EWIS_B2_ERR_CNT:EWIS_B2_ERR_CNT0
 */
#define VTSS_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT0  VTSS_IOREG(0x02, 0, 0xecb3)

/** 
 * \brief
 * PMTICK statistical error count of the B2 BIP errors. 16 LSB are in this
 * register, 16 MSB are in the previous register. The count is updated only
 * on a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT0 . B2_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT0_B2_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT0_B2_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B2_ERR_CNT_EWIS_B2_ERR_CNT0_B2_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:EWIS_B3_ERR_CNT
 *
 * Not documented
 */


/** 
 * \brief E-WIS P-BIP Error Counter 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_B3_ERR_CNT:EWIS_B3_ERR_CNT1
 */
#define VTSS_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT1  VTSS_IOREG(0x02, 0, 0xecb4)

/** 
 * \brief
 * PMTICK statistical error count of the B3 BIP errors. 16 MSB are in this
 * register, 16 LSB are in the next register. The count is updated only on
 * a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT1 . B3_ERR_CNT_MSW
 */
#define  VTSS_F_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT1_B3_ERR_CNT_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT1_B3_ERR_CNT_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT1_B3_ERR_CNT_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief E-WIS P-BIP Error Counter 0 LSW
 *
 * \details
 * Register: \a WIS:EWIS_B3_ERR_CNT:EWIS_B3_ERR_CNT0
 */
#define VTSS_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT0  VTSS_IOREG(0x02, 0, 0xecb5)

/** 
 * \brief
 * PMTICK statistical error count of the B3 BIP errors. 16 LSB are in this
 * register, 16 MSB are in the previous register. The count is updated only
 * on a PMTICK event. The counter saturates when the maximum error count is
 * exceeded.
 *
 * \details 
 * Field: VTSS_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT0 . B3_ERR_CNT_LSW
 */
#define  VTSS_F_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT0_B3_ERR_CNT_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT0_B3_ERR_CNT_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_B3_ERR_CNT_EWIS_B3_ERR_CNT0_B3_ERR_CNT_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:EWIS_RX_DEBUG
 *
 * Not documented
 */


/** 
 * \brief Framer Debug 1
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:FRMR_DBG1
 */
#define VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG1     VTSS_IOREG(0x02, 0, 0xed00)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG1 . Framer_Debug_1
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_FRMR_DBG1_Framer_Debug_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_FRMR_DBG1_Framer_Debug_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_FRMR_DBG1_Framer_Debug_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Framer Debug 2
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:FRMR_DBG2
 */
#define VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG2     VTSS_IOREG(0x02, 0, 0xed01)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG2 . Framer_Debug_2
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_FRMR_DBG2_Framer_Debug_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_FRMR_DBG2_Framer_Debug_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_FRMR_DBG2_Framer_Debug_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Framer Debug 3
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:FRMR_DBG3
 */
#define VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG3     VTSS_IOREG(0x02, 0, 0xed02)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG3 . Framer_Debug_3
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_FRMR_DBG3_Framer_Debug_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_FRMR_DBG3_Framer_Debug_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_FRMR_DBG3_Framer_Debug_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Framer Debug 4
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:FRMR_DBG4
 */
#define VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG4     VTSS_IOREG(0x02, 0, 0xed03)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG4 . Framer_Debug_4
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_FRMR_DBG4_Framer_Debug_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_FRMR_DBG4_Framer_Debug_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_FRMR_DBG4_Framer_Debug_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Framer Debug 5
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:FRMR_DBG5
 */
#define VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG5     VTSS_IOREG(0x02, 0, 0xed04)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_FRMR_DBG5 . Framer_Debug_5
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_FRMR_DBG5_Framer_Debug_5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_FRMR_DBG5_Framer_Debug_5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_FRMR_DBG5_Framer_Debug_5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX SPE Debug Bus 1 MSW
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:RX_SPE_DBG1A
 */
#define VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1A  VTSS_IOREG(0x02, 0, 0xed05)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1A . RX_SPE_Debug_1_MSW
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1A_RX_SPE_Debug_1_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1A_RX_SPE_Debug_1_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1A_RX_SPE_Debug_1_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX SPE Debug Bus 1 LSW
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:RX_SPE_DBG1B
 */
#define VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1B  VTSS_IOREG(0x02, 0, 0xed06)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1B . RX_SPE_Debug_1_LSW
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1B_RX_SPE_Debug_1_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1B_RX_SPE_Debug_1_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_RX_SPE_DBG1B_RX_SPE_Debug_1_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX SPE Debug Bus 2 MSW
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:RX_SPE_DBG2A
 */
#define VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2A  VTSS_IOREG(0x02, 0, 0xed07)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2A . RX_SPE_Debug_2_MSW
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2A_RX_SPE_Debug_2_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2A_RX_SPE_Debug_2_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2A_RX_SPE_Debug_2_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief RX SPE Debug Bus 2 LSW
 *
 * \details
 * Register: \a WIS:EWIS_RX_DEBUG:RX_SPE_DBG2B
 */
#define VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2B  VTSS_IOREG(0x02, 0, 0xed08)

/** 
 * \details 
 * Field: VTSS_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2B . RX_SPE_Debug_2_LSW
 */
#define  VTSS_F_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2B_RX_SPE_Debug_2_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2B_RX_SPE_Debug_2_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_EWIS_RX_DEBUG_RX_SPE_DBG2B_RX_SPE_Debug_2_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_DEBUG_STAT
 *
 * Not documented
 */


/** 
 * \brief WIS Debug Status
 *
 * \details
 * Register: \a WIS:WIS_DEBUG_STAT:WIS_DEBUG_STATUS
 */
#define VTSS_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS  VTSS_IOREG(0x02, 0, 0xed10)

/** 
 * \brief
 * Latch-high status register for WIS_SIGNAL_OK status.  The latch-high bit
 * is cleared when the register is read.
 *
 * \details 
 * 1 = WIS_SIGNAL_OK (bit [0]) has been asserted at least once since the
 * last time this register was read.
 * 0 = WIS_SIGNAL_OK (bit [0]) has not been asserted since the last time
 * this register was read.
 *
 * Field: VTSS_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS . WIS_SIGNAL_OK_LH
 */
#define  VTSS_F_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS_WIS_SIGNAL_OK_LH  VTSS_BIT(2)

/** 
 * \brief
 * Latch-low status register for WIS_SIGNAL_OK status.	The latch-low bit
 * is cleared when the register is read.
 *
 * \details 
 * 1 = WIS_SIGNAL_OK (bit [0]) has not been de-asserted since the last time
 * this register was read.
 * 0 = WIS_SIGNAL_OK (bit [0]) has been de-asserted at least once since the
 * last time this register was read.
 *
 * Field: VTSS_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS . WIS_SIGNAL_OK_LL
 */
#define  VTSS_F_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS_WIS_SIGNAL_OK_LL  VTSS_BIT(1)

/** 
 * \brief
 * Real-time state of WIS_SIGNAL_OK status.
 *
 * \details 
 * 1 = Received SONET/SDH data is good.
 * 0 = Received SONET/SDH data is bad.	This is the alarm state.
 *
 * Field: VTSS_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS . WIS_SIGNAL_OK
 */
#define  VTSS_F_WIS_WIS_DEBUG_STAT_WIS_DEBUG_STATUS_WIS_SIGNAL_OK  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Rx_to_Tx_Control
 *
 * Not documented
 */


/** 
 * \brief E-WIS Rx to Tx Control
 *
 * \details
 * Register: \a WIS:EWIS_Rx_to_Tx_Control:EWIS_RXTX_CTRL
 */
#define VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL  VTSS_IOREG(0x02, 0, 0xedff)

/** 
 * \brief
 * Select if a LOPC condition contributes to the Rx AIS-L alarm
 *
 * \details 
 * 0 = A LOPC condition does not cause the AIS-L alarm to be set
 * 1 = A LOPC condition will cause the AIS-L alarm to be set
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . RXAISL_ON_LOPC
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_RXAISL_ON_LOPC  VTSS_BIT(6)

/** 
 * \brief
 * Selects if a LOS condition contributes to the Rx AIS-L alarm
 *
 * \details 
 * 0 = A LOS condition does not cause the AIS-L alarm to be set
 * 1 = A LOS condition will cause the AIS-L alarm to be set
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . RXAISL_ON_LOS
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_RXAISL_ON_LOS  VTSS_BIT(5)

/** 
 * \brief
 * Select if a LOF condition contributes to the Rx AIS-L alarm
 *
 * \details 
 * 0 = A LOF condition does not cause the AIS-L alarm to be set
 * 1 = A LOF condition will cause the AIS-L alarm to be set
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . RXAISL_ON_LOF
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_RXAISL_ON_LOF  VTSS_BIT(4)

/** 
 * \brief
 * Select if a RDI-L is reported in the TX frame's K2 byte when a LOPC
 * condition is detected
 *
 * \details 
 * 0 = RDI-L will not be reported when LOPC is detected
 * 1 = RDI-L will be reported when LOPC is detected
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . TXRDIL_ON_LOPC
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_TXRDIL_ON_LOPC  VTSS_BIT(3)

/** 
 * \brief
 * Selects whether or not RDI-L is reported in the TX frame's K2 byte when
 * a LOS condition is detected
 *
 * \details 
 * 0 = RDI-L will not be reported when LOS is detected
 * 1 = RDI-L will be reported when LOS is detected
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . TXRDIL_ON_LOS
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_TXRDIL_ON_LOS  VTSS_BIT(2)

/** 
 * \brief
 * Selects whether or not RDI-L is reported in the TX frame's K2 byte when
 * a LOF condition is detected
 *
 * \details 
 * 0 = RDI-L will not be reported when LOF is detected
 * 1 = RDI-L will be reported when LOF is detected
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . TXRDIL_ON_LOF
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_TXRDIL_ON_LOF  VTSS_BIT(1)

/** 
 * \brief
 * Selects whether or not RDI-L is reported in the TX frame's K2 byte when
 * a Rx AIS-L condition is detected
 *
 * \details 
 * 0 = RDI-L will not be reported when a Rx AIS-L condition is detected
 * 1 = RDI-L will be reported when a Rx AIS-L condition is detected
 *
 * Field: VTSS_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL . TXRDIL_ON_AISL
 */
#define  VTSS_F_WIS_EWIS_Rx_to_Tx_Control_EWIS_RXTX_CTRL_TXRDIL_ON_AISL  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Pending_1
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Pending 1
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Pending_1:EWIS_INTR_PEND1
 */
#define VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1  VTSS_IOREG(0x02, 0, 0xee00)

/** 
 * \brief
 * The interrupt pending bit is asserted when the SEF status changes state.
 *  The sticky bit is cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = SEF condition has not changed state
 * 1 = SEF condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . SEF_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_SEF_PEND  VTSS_BIT(11)

/** 
 * \brief
 * The interrupt pending bit is asserted when the far-end path label
 * mismatch (PLM-P) / Loss of Code-group Delineation(LCD-P) condition
 * changes state.  The sticky bit is cleared when a 1 is written to the
 * register bit.
 *
 * \details 
 * 0 = PLM-P/LCD-P has not changed state
 * 1 = PLM-P/LCD-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . FEPLMP_LCDP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_FEPLMP_LCDP_PEND  VTSS_BIT(10)

/** 
 * \brief
 * The interrupt pending bit is asserted when the far-end path Alarm
 * Indication Signal (AIS-P)/ Path Loss of Pointer (LOP) condition changes
 * state.  The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = Far-end AIS-P/LOP-P condition has not changed state
 * 1 = Far-end AIS-P/LOP-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . FEAISP_LOPP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_FEAISP_LOPP_PEND  VTSS_BIT(9)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Loss of Frame (LOF)
 * condition changes state.  The sticky bit is cleared when a 1 is written
 * to the register bit.
 *
 * \details 
 * 0 = LOF condition has not changed state
 * 1 = LOF condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . LOF_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_LOF_PEND  VTSS_BIT(7)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Loss of Signal (LOS)
 * condition changes state.  This bit does not assert if LOPC is asserted
 * at the time LOS changes state.  The sticky bit is cleared when a 1 is
 * written to the register bit.
 *
 * \details 
 * 0 = LOS condition has not changed state
 * 1 = LOS condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . LOS_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_LOS_PEND  VTSS_BIT(6)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Line Remote Defect
 * Indication (RDI-L) status changes state.  The sticky bit is cleared when
 * a 1 is written to the register bit.
 *
 * \details 
 * 0 = RDI-L condition has not changed state
 * 1 = RDI-L condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . RDIL_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_RDIL_PEND  VTSS_BIT(5)

/** 
 * \brief
 * The interrupt pending bit is asserted when Line Alarm Indication Signal
 * (AIS-L) status changes state.  This bit does not assert if LOPC, LOS,
 * LOF or SEF are asserted at the time AIS-L changes state.  The sticky bit
 * is cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = AIS-L condition has not changed state 
 * 1 = AIS-L condition has changed state 
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . AISL_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_AISL_PEND  VTSS_BIT(4)

/** 
 * \brief
 * The interrupt pending bit is asserted wehen the Loss of Code-group
 * Delineation (LCD-P) condition changes state.  This bit will not assert
 * if AIS-L, AIS-P, UNEQ-P, or PLM-P are asserted at the time LCD-P changes
 * state.  The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = LCD-P condition has not changed state
 * 1 = LCD-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . LCDP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_LCDP_PEND  VTSS_BIT(3)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Path Label Mismatch
 * (PLM-P) condition changes state.  This bit will not assert if LOP-P or
 * AIS-P are asserted at the time PLM-P changes state.	The sticky bit is
 * cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = PLM-P condition has not changed state
 * 1 = PLM-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . PLMP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_PLMP_PEND  VTSS_BIT(2)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Path Alarm Indication
 * Signal (AIS-P) condition changes state.  This bit will not assert if
 * LOPC, LOS, SEF, LOF, or AIS-L are asserted at the time AIS-P changes
 * state.  The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = AIS-P condition has not changed state
 * 1 = AIS-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . AISP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_AISP_PEND  VTSS_BIT(1)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Path Loss of Pointer
 * (LOP-P) condition changes state.  The sticky bit is cleared when a 1 is
 * written to the register bit.
 *
 * \details 
 * 0 = LOP-P condition has not changed state
 * 1 = LOP-P condition has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1 . LOPP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_1_EWIS_INTR_PEND1_LOPP_PEND  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Mask_1
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Mask A 1
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_1:EWIS_INTR_MASKA_1
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1  VTSS_IOREG(0x02, 0, 0xee01)

/** 
 * \brief
 * Enable propagation of SEF_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . SEF_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_SEF_MASKA  VTSS_BIT(11)

/** 
 * \brief
 * Enable propagation of FEPLMP_LCDP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . FEPLMP_LCDP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_FEPLMP_LCDP_MASKA  VTSS_BIT(10)

/** 
 * \brief
 * Enable propagation of FEAISP_LOPP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . FEAISP_LOPP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_FEAISP_LOPP_MASKA  VTSS_BIT(9)

/** 
 * \brief
 * Enable propagation of LOF_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . LOF_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_LOF_MASKA  VTSS_BIT(7)

/** 
 * \brief
 * Enable propagation of LOS_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . LOS_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_LOS_MASKA  VTSS_BIT(6)

/** 
 * \brief
 * Enable propagation of RDIL_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . RDIL_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_RDIL_MASKA  VTSS_BIT(5)

/** 
 * \brief
 * Enable propagation of AISL_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . AISL_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_AISL_MASKA  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of LCDP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . LCDP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_LCDP_MASKA  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of PLMP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . PLMP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_PLMP_MASKA  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of AISP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . AISP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_AISP_MASKA  VTSS_BIT(1)

/** 
 * \brief
 * Enable propagation of LOPP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1 . LOPP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKA_1_LOPP_MASKA  VTSS_BIT(0)


/** 
 * \brief E-WIS Interrupt Mask B 1
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_1:EWIS_INTR_MASKB_1
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1  VTSS_IOREG(0x02, 0, 0xee02)

/** 
 * \brief
 * Enable propagation of SEF_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . SEF_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_SEF_MASKB  VTSS_BIT(11)

/** 
 * \brief
 * Enable propagation of FEPLMP_LCDP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . FEPLMP_LCDP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_FEPLMP_LCDP_MASKB  VTSS_BIT(10)

/** 
 * \brief
 * Enable propagation of FEAISP_LOPP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . FEAISP_LOPP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_FEAISP_LOPP_MASKB  VTSS_BIT(9)

/** 
 * \brief
 * Enable propagation of LOF_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . LOF_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_LOF_MASKB  VTSS_BIT(7)

/** 
 * \brief
 * Enable propagation of LOS_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . LOS_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_LOS_MASKB  VTSS_BIT(6)

/** 
 * \brief
 * Enable propagation of RDIL_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . RDIL_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_RDIL_MASKB  VTSS_BIT(5)

/** 
 * \brief
 * Enable propagation of AISL_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . AISL_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_AISL_MASKB  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of LCDP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . LCDP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_LCDP_MASKB  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of PLMP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . PLMP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_PLMP_MASKB  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of AISP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . AISP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_AISP_MASKB  VTSS_BIT(1)

/** 
 * \brief
 * Enable propagation of LOPP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1 . LOPP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_1_EWIS_INTR_MASKB_1_LOPP_MASKB  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Status_2
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Status 2
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Status_2:EWIS_INTR_STAT2
 */
#define VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2  VTSS_IOREG(0x02, 0, 0xee03)

/** 
 * \brief
 * Loss of Optical Carrier (LOPC) status
 *
 * \details 
 * 0 = The LOPC input pin is de-asserted
 * 1 = The LOPC input pin is asserted
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . LOPC_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_LOPC_STAT  VTSS_BIT(11)

/** 
 * \brief
 * Unequiped Path (UNEQ-P) status
 *
 * \details 
 * 0 = UNEQ-P is de-asserted
 * 1 = UNEQ-P is asserted
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . UNEQP_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_UNEQP_STAT  VTSS_BIT(10)

/** 
 * \brief
 * Far-end Unequiped Path (UNEQ-P) status
 *
 * \details 
 * 0 = Far-end UNEQ-P is de-asserted
 * 1 = Far-end UNEQ-P is asserted
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . FEUNEQP_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_FEUNEQP_STAT  VTSS_BIT(9)

/** 
 * \brief
 * Far-end Path Remote Defect Identifier (RDI-P) status
 *
 * \details 
 * 0 = Far-end RDI-P is de-asserted
 * 1 = Far-end RDI-P is asserted
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . FERDIP_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_FERDIP_STAT  VTSS_BIT(8)

/** 
 * \brief
 * PMTICK B1 BIP (B1_ERR_CNT) counter status
 *
 * \details 
 * 0 = B1_ERR_CNT is zero
 * 1 = B1_ERR_CNT is non-zero
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . B1_NZ_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_B1_NZ_STAT  VTSS_BIT(7)

/** 
 * \brief
 * PMTICK B2 BIP (B2_ERR_CNT) counter status
 *
 * \details 
 * 0 = B2_ERR_CNT is zero
 * 1 = B2_ERR_CNT is non-zero
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . B2_NZ_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_B2_NZ_STAT  VTSS_BIT(6)

/** 
 * \brief
 * PMTICK B3 BIP (B3_ERR_CNT) counter status
 *
 * \details 
 * 0 = B3_ERR_CNT is zero
 * 1 = B3_ERR_CNT is non-zero
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . B3_NZ_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_B3_NZ_STAT  VTSS_BIT(5)

/** 
 * \brief
 * Line Remote Error Indication (REI-L) value status
 *
 * \details 
 * 0 = The REI-L value in the last received frame reported no errors
 * 1 = The REI-L value in the last received frame reported errors
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . REIL_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_REIL_STAT  VTSS_BIT(4)

/** 
 * \brief
 * Path Remote Error Indication (REI-P) value status
 *
 * \details 
 * 0 = The REI-P value in the last received frame reported no errors
 * 1 = The REI-P value in the last received frame reported errors
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . REIP_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_REIP_STAT  VTSS_BIT(3)

/** 
 * \brief
 * PMTICK REI-L (REIL_ERR_CNT) counter status
 *
 * \details 
 * 0 = REIL_ERR_CNT is zero
 * 1 = REIL_ERR_CNT is non-zero
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . REIL_NZ_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_REIL_NZ_STAT  VTSS_BIT(2)

/** 
 * \brief
 * PMTICK REI-P (REIP_ERR_CNT) counter status
 *
 * \details 
 * 0 = REIP_ERR_CNT is zero
 * 1 = REIP_ERR_CNT is non-zero
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2 . REIP_NZ_STAT
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Status_2_EWIS_INTR_STAT2_REIP_NZ_STAT  VTSS_BIT(1)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Pending_2
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Pending 2
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Pending_2:EWIS_INTR_PEND2
 */
#define VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2  VTSS_IOREG(0x02, 0, 0xee04)

/** 
 * \brief
 * The interrupt pending bit is asserted when a PMTICK event (regardless of
 * the source) has occurred.  The sticky bit is cleared when a 1 is written
 * to the register bit.
 *
 * \details 
 * 0 = A PMTICK event has not occurred
 * 1 = A PMTICK event occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . PMTICK_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_PMTICK_PEND  VTSS_BIT(14)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Unequiped Path
 * (UNEQP_STAT) status changes state.  This bit does not assert if LOP-P or
 * AIS-P are asserted at the time UNEQ-P changes state.  The sticky bit is
 * cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = UNEQP_STAT has not changed state
 * 1 = UNEQP_STAT has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . UNEQP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_UNEQP_PEND  VTSS_BIT(10)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Far-end Unequiped Path
 * (FEUNEQP_STAT) status changes state.  The sticky bit is cleared when a 1
 * is written to the register bit.
 *
 * \details 
 * 0 = FEUNEQP_STAT has not changed state
 * 1 = FEUNEQP_STAT has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . FEUNEQP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_FEUNEQP_PEND  VTSS_BIT(9)

/** 
 * \brief
 * The interrupt pending bit is asserted when the Far-end Path Remote
 * Defect Identifier (FERDIP_STAT) status changes state.  The sticky bit is
 * cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = FERDIP_STAT has not changed state
 * 1 = FERDIP_STAT has changed state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . FERDIP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_FERDIP_PEND  VTSS_BIT(8)

/** 
 * \brief
 * The interrupt pending bit is asserted when the PMTICK B1 error counter
 * (B1_ERR_CNT) has changed from zero to a non-zero value.  This bit will
 * not assert if LOS or LOF are asserted at the time B1_NZ_STAT changes
 * state.  The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = B1_NZ_STAT has not changed from a 0 to 1 state
 * 1 = B1_NZ_STAT has changed from a 0 to 1 state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . B1_NZ_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_B1_NZ_PEND  VTSS_BIT(7)

/** 
 * \brief
 * The interrupt pending bit is asserted when the PMTICK B2 error counter
 * (B2_ERR_CNT) has changed from zero to a non-zero value.  This bit will
 * not assert if AIS-L is asserted at the time B2_NZ_STAT changes state. 
 * The sticky bit is cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = B2_NZ_STAT has not changed from a 0 to 1 state
 * 1 = B2_NZ_STAT has changed from a 0 to 1 state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . B2_NZ_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_B2_NZ_PEND  VTSS_BIT(6)

/** 
 * \brief
 * The interrupt pending bit is asserted when the PMTICK B3 error counter
 * (B3_ERR_CNT) has changed from zero to a non-zero value.  This bit will
 * not assert if LOP-P or AIS-P are asserted at the time B3_NZ_STAT changes
 * state. The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = B3_NZ_STAT has not changed from a 0 to 1 state
 * 1 = B3_NZ_STAT has changed from a 0 to 1 state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . B3_NZ_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_B3_NZ_PEND  VTSS_BIT(5)

/** 
 * \brief
 * The interrupt pending bit is asserted when a non-zero REI-L value is
 * received.  The sticky bit is cleared when a 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = REI-L has not received a non-zero value
 * 1 = REI-L has received a non-zero value
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . REIL_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_REIL_PEND  VTSS_BIT(4)

/** 
 * \brief
 * The interrupt pending bit is asserted when a non-zero REI-P value is
 * received.  The sticky bit is cleared when 1 is written to the register
 * bit.
 *
 * \details 
 * 0 = REI-P has not received a non-zero value
 * 1 = REI-P has received a non-zero value
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . REIP_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_REIP_PEND  VTSS_BIT(3)

/** 
 * \brief
 * The interrupt pending bit is asserted when the PMTICK far-end B2 error
 * counter (REIL_ERR_CNT) has changed from zero to a non-zero value status
 * changes state.  The sticky bit is cleared when a 1 is written to the
 * register bit.
 *
 * \details 
 * 0 = REIL_NZ_STAT has not changed from a 0 to 1 state
 * 1 = REIL_NZ_STAT has changed from a 0 to 1 state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . REIL_NZ_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_REIL_NZ_PEND  VTSS_BIT(2)

/** 
 * \brief
 * The interrupt pending bit is asserted when the PMTICK far-end B3 error
 * counter (REIP_ERR_CNT) has changed from zero to a non-zero value.  The
 * sticky bit is cleared when a 1 is written to the register bit.
 *
 * \details 
 * 0 = REIP_NZ_STAT has changed from a 0 to 1 state
 * 1 = REIP_NZ_STAT has changed from a 0 to 1 state
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2 . REIP_NZ_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_2_EWIS_INTR_PEND2_REIP_NZ_PEND  VTSS_BIT(1)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Mask_2
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Mask A 2
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_2:EWIS_INTR_MASKA_2
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2  VTSS_IOREG(0x02, 0, 0xee05)

/** 
 * \brief
 * Enable propagation of PMTICK_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . PMTICK_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_PMTICK_MASKA  VTSS_BIT(14)

/** 
 * \brief
 * Enable propagation of UNEQP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . UNEQP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_UNEQP_MASKA  VTSS_BIT(10)

/** 
 * \brief
 * Enable propagation of FEUNEQP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . FEUNEQP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_FEUNEQP_MASKA  VTSS_BIT(9)

/** 
 * \brief
 * Enable propagation of FERDIP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . FERDIP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_FERDIP_MASKA  VTSS_BIT(8)

/** 
 * \brief
 * Enable propagation of B1_NZ_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . B1_NZ_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_B1_NZ_MASKA  VTSS_BIT(7)

/** 
 * \brief
 * Enable propagation of B2_NZ_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . B2_NZ_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_B2_NZ_MASKA  VTSS_BIT(6)

/** 
 * \brief
 * Enable propagation of B3_NZ_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . B3_NZ_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_B3_NZ_MASKA  VTSS_BIT(5)

/** 
 * \brief
 * Enable propagation of REIL_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . REIL_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_REIL_MASKA  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of REIP_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . REIP_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_REIP_MASKA  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of REIL_NZ_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . REIL_NZ_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_REIL_NZ_MASKA  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of REIP_NZ_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2 . REIP_NZ_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKA_2_REIP_NZ_MASKA  VTSS_BIT(1)


/** 
 * \brief E-WIS Interrupt Mask B 2
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_2:EWIS_INTR_MASKB_2
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2  VTSS_IOREG(0x02, 0, 0xee06)

/** 
 * \brief
 * Enable propagation of PMTICK_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . PMTICK_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_PMTICK_MASKB  VTSS_BIT(14)

/** 
 * \brief
 * Enable propagation of UNEQP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . UNEQP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_UNEQP_MASKB  VTSS_BIT(10)

/** 
 * \brief
 * Enable propagation of FEUNEQP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . FEUNEQP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_FEUNEQP_MASKB  VTSS_BIT(9)

/** 
 * \brief
 * Enable propagation of FERDIP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . FERDIP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_FERDIP_MASKB  VTSS_BIT(8)

/** 
 * \brief
 * Enable propagation of B1_NZ_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . B1_NZ_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_B1_NZ_MASKB  VTSS_BIT(7)

/** 
 * \brief
 * Enable propagation of B2_NZ_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . B2_NZ_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_B2_NZ_MASKB  VTSS_BIT(6)

/** 
 * \brief
 * Enable propagation of B3_NZ_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . B3_NZ_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_B3_NZ_MASKB  VTSS_BIT(5)

/** 
 * \brief
 * Enable propagation of REIL_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . REIL_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_REIL_MASKB  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of REIP_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . REIP_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_REIP_MASKB  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of REIL_NZ_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . REIL_NZ_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_REIL_NZ_MASKB  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of REIP_NZ_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2 . REIP_NZ_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_2_EWIS_INTR_MASKB_2_REIP_NZ_MASKB  VTSS_BIT(1)

/**
 * Register Group: \a WIS:WIS_FAULT_MASK
 *
 * Not documented
 */


/** 
 * \brief WIS_FAULT_MASK
 *
 * \details
 * Register: \a WIS:WIS_FAULT_MASK:WIS_FAULT_MASK
 */
#define VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK  VTSS_IOREG(0x02, 0, 0xee07)

/** 
 * \brief
 * Selects if the far-end PLM-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_FEPLMP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_FEPLMP  VTSS_BIT(10)

/** 
 * \brief
 * Selects if the far-end AIS-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_FEAISP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_FEAISP  VTSS_BIT(9)

/** 
 * \brief
 * Selects if the RDI-L condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_RDIL
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_RDIL  VTSS_BIT(8)

/** 
 * \brief
 * Selects if the SEF condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_SEF
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_SEF  VTSS_BIT(7)

/** 
 * \brief
 * Selects if the LOF condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_LOF
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_LOF  VTSS_BIT(6)

/** 
 * \brief
 * Selects if the LOS condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_LOS
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_LOS  VTSS_BIT(5)

/** 
 * \brief
 * Selects if the AIS-L condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_AISL
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_AISL  VTSS_BIT(4)

/** 
 * \brief
 * Selects if the LCD-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_LCDP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_LCDP  VTSS_BIT(3)

/** 
 * \brief
 * Selects if the PLM-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_PLMP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_PLMP  VTSS_BIT(2)

/** 
 * \brief
 * Selects if the AIS-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_AISP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_AISP  VTSS_BIT(1)

/** 
 * \brief
 * Selects if the LOP-P condition triggers the WIS fault alarm
 * (WIS_STAT1.FAULT register)
 *
 * \details 
 * 0 = No trigger
 * 1 = Triggers WIS_FAULT
 *
 * Field: VTSS_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK . WIS_FAULT_ON_LOPP
 */
#define  VTSS_F_WIS_WIS_FAULT_MASK_WIS_FAULT_MASK_WIS_FAULT_ON_LOPP  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Pending_3
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Pending 3
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Pending_3:EWIS_INTR_PEND3
 */
#define VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3  VTSS_IOREG(0x02, 0, 0xee08)

/** 
 * \brief
 * The interrupt pending bit is asserted when the REI-P threshold error
 * level is exceeded (REIP_THRESH_ERR=1).  The sticky bit is cleared when a
 * 1 is written to the register bit.
 *
 * \details 
 * 0 = A counter thresold error has not occurred
 * 1 = A counter thresold error occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3 . REIP_THRESH_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3_REIP_THRESH_PEND  VTSS_BIT(4)

/** 
 * \brief
 * The interrupt pending bit is asserted when the REI-L threshold error
 * level is exceeded (REIL_THRESH_ERR=1).  The sticky bit is cleared when a
 * 1 is written to the register bit.
 *
 * \details 
 * 0 = A counter thresold error has not occurred
 * 1 = A counter thresold error occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3 . REIL_THRESH_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3_REIL_THRESH_PEND  VTSS_BIT(3)

/** 
 * \brief
 * The interrupt pending bit is asserted when the B1 PMTICK threshold error
 * level is exceeded (B1_THRESH_ERR=1).  The sticky bit is cleared when a 1
 * is written to the register bit.
 *
 * \details 
 * 0 = A counter thresold error has not occurred
 * 1 = A counter thresold error occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3 . B1_THRESH_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3_B1_THRESH_PEND  VTSS_BIT(2)

/** 
 * \brief
 * The interrupt pending bit is asserted when the B2 PMTICK threshold error
 * level is exceeded (B2_THRESH_ERR=1).  The sticky bit is cleared when a 1
 * is written to the register bit.
 *
 * \details 
 * 0 = A counter thresold error has not occurred
 * 1 = A counter thresold error occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3 . B2_THRESH_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3_B2_THRESH_PEND  VTSS_BIT(1)

/** 
 * \brief
 * The interrupt pending bit is asserted when the B3 PMTICK threshold error
 * level is exceeded (B3_THRESH_ERR=1).  The sticky bit is cleared when a 1
 * is written to the register bit.
 *
 * \details 
 * 0 = A counter thresold error has not occurred
 * 1 = A counter thresold error occurred
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3 . B3_THRESH_PEND
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Pending_3_EWIS_INTR_PEND3_B3_THRESH_PEND  VTSS_BIT(0)

/**
 * Register Group: \a WIS:EWIS_Interrupt_Mask_3
 *
 * Not documented
 */


/** 
 * \brief E-WIS Interrupt Mask A 3
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_3:EWIS_INTR_MASKA_3
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3  VTSS_IOREG(0x02, 0, 0xee09)

/** 
 * \brief
 * Enable propagation of REIP_THRESH_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3 . REIP_THRESH_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3_REIP_THRESH_MASKA  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of REIL_THRESH_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3 . REIL_THRESH_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3_REIL_THRESH_MASKA  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of B1_THRESH_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3 . B1_THRESH_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3_B1_THRESH_MASKA  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of B2_THRESH_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3 . B2_THRESH_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3_B2_THRESH_MASKA  VTSS_BIT(1)

/** 
 * \brief
 * Enable propagation of B3_THRESH_PEND to the WIS0 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3 . B3_THRESH_MASKA
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKA_3_B3_THRESH_MASKA  VTSS_BIT(0)


/** 
 * \brief E-WIS Interrupt Mask B 3
 *
 * \details
 * Register: \a WIS:EWIS_Interrupt_Mask_3:EWIS_INTR_MASKB_3
 */
#define VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3  VTSS_IOREG(0x02, 0, 0xee0a)

/** 
 * \brief
 * Enable propagation of REIP_THRESH_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3 . REIP_THRESH_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3_REIP_THRESH_MASKB  VTSS_BIT(4)

/** 
 * \brief
 * Enable propagation of REIL_THRESH_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3 . REIL_THRESH_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3_REIL_THRESH_MASKB  VTSS_BIT(3)

/** 
 * \brief
 * Enable propagation of B1_THRESH_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3 . B1_THRESH_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3_B1_THRESH_MASKB  VTSS_BIT(2)

/** 
 * \brief
 * Enable propagation of B2_THRESH_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3 . B2_THRESH_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3_B2_THRESH_MASKB  VTSS_BIT(1)

/** 
 * \brief
 * Enable propagation of B3_THRESH_PEND to the WIS1 interrupt
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3 . B3_THRESH_MASKB
 */
#define  VTSS_F_WIS_EWIS_Interrupt_Mask_3_EWIS_INTR_MASKB_3_B3_THRESH_MASKB  VTSS_BIT(0)

/**
 * Register Group: \a WIS:Threshold_Error_Status
 *
 * Not documented
 */


/** 
 * \brief Threshold Error Status
 *
 * \details
 * Register: \a WIS:Threshold_Error_Status:THRESH_ERR_STAT
 */
#define VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT  VTSS_IOREG(0x02, 0, 0xee0b)

/** 
 * \brief
 * Indicates when the REI-P PMTICK counter exceeds the threshold level
 * defined in REIP_THRESH_ERR.	The threshold is compared to an internal
 * error accumulator, not the value captured and stored in REIP_ERR_CNT.
 *
 * \details 
 * 0 = Counter does not exceed threshold level
 * 1 = Counter exceeds threshold level
 *
 * Field: VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT . REIP_THRESH_ERR
 */
#define  VTSS_F_WIS_Threshold_Error_Status_THRESH_ERR_STAT_REIP_THRESH_ERR  VTSS_BIT(4)

/** 
 * \brief
 * Indicates when the REI-L PMTICK counter exceeds the threshold level
 * defined in REIL_THRESH_ERR.	The threshold is compared to an internal
 * error accumulator, not the value captured and stored in REIL_ERR_CNT.
 *
 * \details 
 * 0 = Counter does not exceed threshold level
 * 1 = Counter exceeds threshold level
 *
 * Field: VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT . REIL_THRESH_ERR
 */
#define  VTSS_F_WIS_Threshold_Error_Status_THRESH_ERR_STAT_REIL_THRESH_ERR  VTSS_BIT(3)

/** 
 * \brief
 * Indicates when the B1 PMTICK counter exceeds the threshold level defined
 * in B1_THRESH_ERR.  The threshold is compared to an internal error
 * accumulator, not the value captured and stored in B1_ERR_CNT.
 *
 * \details 
 * 0 = Counter does not exceed threshold level
 * 1 = Counter exceeds threshold level
 *
 * Field: VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT . B1_THRESH_ERR
 */
#define  VTSS_F_WIS_Threshold_Error_Status_THRESH_ERR_STAT_B1_THRESH_ERR  VTSS_BIT(2)

/** 
 * \brief
 * Indicates when the B2 PMTICK counter exceeds the threshold level defined
 * in B2_THRESH_ERR.  The threshold is compared to an internal error
 * accumulator, not the value captured and stored in B2_ERR_CNT.
 *
 * \details 
 * 0 = Counter does not exceed threshold level
 * 1 = Counter exceeds threshold level
 *
 * Field: VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT . B2_THRESH_ERR
 */
#define  VTSS_F_WIS_Threshold_Error_Status_THRESH_ERR_STAT_B2_THRESH_ERR  VTSS_BIT(1)

/** 
 * \brief
 * Indicates when the B3 PMTICK counter exceeds the threshold level defined
 * in B3_THRESH_ERR.  The threshold is compared to an internal error
 * accumulator, not the value captured and stored in B3_ERR_CNT.
 *
 * \details 
 * 0 = Counter does not exceed threshold level
 * 1 = Counter exceeds threshold level
 *
 * Field: VTSS_WIS_Threshold_Error_Status_THRESH_ERR_STAT . B3_THRESH_ERR
 */
#define  VTSS_F_WIS_Threshold_Error_Status_THRESH_ERR_STAT_B3_THRESH_ERR  VTSS_BIT(0)

/**
 * Register Group: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels
 *
 * Not documented
 */


/** 
 * \brief WIS REI-P Threshold Level 1
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_REIP_THRESH_LVL1
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL1  VTSS_IOREG(0x02, 0, 0xee10)

/** 
 * \brief
 * REIP_THRESH_ERR is asserted when the REI-P PMTICK error counter is
 * greater than the REI-P threshold level defined by this register and the
 * next register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL1 . REIP_THRESH_LVL_MSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL1_REIP_THRESH_LVL_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL1_REIP_THRESH_LVL_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL1_REIP_THRESH_LVL_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS REI-P Threshold Level 0
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_REIP_THRESH_LVL0
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL0  VTSS_IOREG(0x02, 0, 0xee11)

/** 
 * \brief
 * REIP_THRESH_ERR is asserted when the REI-P PMTICK error counter is
 * greater than the REI-P threshold level defined by this register and the
 * previous register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL0 . REIP_THRESH_LVL_LSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL0_REIP_THRESH_LVL_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL0_REIP_THRESH_LVL_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIP_THRESH_LVL0_REIP_THRESH_LVL_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS REI-L Threshold Level 1
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_REIL_THRESH_LVL1
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL1  VTSS_IOREG(0x02, 0, 0xee12)

/** 
 * \brief
 * REIL_THRESH_ERR is asserted when the REI-L PMTICK error counter is
 * greater than the REI-L threshold level defined by this register and the
 * next register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL1 . REIL_THRESH_LVL_MSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL1_REIL_THRESH_LVL_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL1_REIL_THRESH_LVL_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL1_REIL_THRESH_LVL_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS REI-L Threshold Level 0
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_REIL_THRESH_LVL0
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL0  VTSS_IOREG(0x02, 0, 0xee13)

/** 
 * \brief
 * REIL_THRESH_ERR is asserted when the REI-L PMTICK error counter is
 * greater than the REI-L threshold level defined by this register and the
 * previous register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL0 . REIL_THRESH_LVL_LSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL0_REIL_THRESH_LVL_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL0_REIL_THRESH_LVL_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_REIL_THRESH_LVL0_REIL_THRESH_LVL_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B1 Threshold Level 1
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B1_THRESH_LVL1
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL1  VTSS_IOREG(0x02, 0, 0xee14)

/** 
 * \brief
 * B1_THRESH_ERR is asserted when the B1 PMTICK error counter is greater
 * than the B1 threshold level defined by this register and the next
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL1 . B1_THRESH_LVL_MSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL1_B1_THRESH_LVL_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL1_B1_THRESH_LVL_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL1_B1_THRESH_LVL_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B1 Threshold Level 0
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B1_THRESH_LVL0
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL0  VTSS_IOREG(0x02, 0, 0xee15)

/** 
 * \brief
 * B1_THRESH_ERR is asserted when the B1 PMTICK error counter is greater
 * than the B1 threshold level defined by this register and the previous
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL0 . B1_THRESH_LVL_LSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL0_B1_THRESH_LVL_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL0_B1_THRESH_LVL_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B1_THRESH_LVL0_B1_THRESH_LVL_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B2 Threshold Level 1
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B2_THRESH_LVL1
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL1  VTSS_IOREG(0x02, 0, 0xee16)

/** 
 * \brief
 * B2_THRESH_ERR is asserted when the B2 PMTICK error counter is greater
 * than the B2 threshold level defined by this register and the next
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL1 . B2_THRESH_LVL_MSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL1_B2_THRESH_LVL_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL1_B2_THRESH_LVL_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL1_B2_THRESH_LVL_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B2 Threshold Level 0
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B2_THRESH_LVL0
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL0  VTSS_IOREG(0x02, 0, 0xee17)

/** 
 * \brief
 * B2_THRESH_ERR is asserted when the B2 PMTICK error counter is greater
 * than the B2 threshold level defined by this register and the previous
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL0 . B2_THRESH_LVL_LSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL0_B2_THRESH_LVL_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL0_B2_THRESH_LVL_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B2_THRESH_LVL0_B2_THRESH_LVL_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B3 Threshold Level 1
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B3_THRESH_LVL1
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL1  VTSS_IOREG(0x02, 0, 0xee18)

/** 
 * \brief
 * B3_THRESH_ERR is asserted when the B3 PMTICK error counter is greater
 * than the B3 threshold level defined by this register and the next
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL1 . B3_THRESH_LVL_MSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL1_B3_THRESH_LVL_MSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL1_B3_THRESH_LVL_MSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL1_B3_THRESH_LVL_MSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS B3 Threshold Level 0
 *
 * \details
 * Register: \a WIS:PMTICK_Cntr_Intr_Threshold_Levels:WIS_B3_THRESH_LVL0
 */
#define VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL0  VTSS_IOREG(0x02, 0, 0xee19)

/** 
 * \brief
 * B3_THRESH_ERR is asserted when the B3 PMTICK error counter is greater
 * than the B3 threshold level defined by this register and the previous
 * register.
 *
 * \details 
 * Field: VTSS_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL0 . B3_THRESH_LVL_LSW
 */
#define  VTSS_F_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL0_B3_THRESH_LVL_LSW(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL0_B3_THRESH_LVL_LSW     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_PMTICK_Cntr_Intr_Threshold_Levels_WIS_B3_THRESH_LVL0_B3_THRESH_LVL_LSW(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a WIS:WIS_Spare_CFG_STAT
 *
 * Not documented
 */


/** 
 * \brief WIS Spare Control 0
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_0
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_0  VTSS_IOREG(0x02, 0, 0xef00)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_0 . Spare_cfg0
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_0_Spare_cfg0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_0_Spare_cfg0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_0_Spare_cfg0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 1
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_1
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_1  VTSS_IOREG(0x02, 0, 0xef01)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_1 . Spare_cfg1
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_1_Spare_cfg1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_1_Spare_cfg1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_1_Spare_cfg1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 2
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_2
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_2  VTSS_IOREG(0x02, 0, 0xef02)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_2 . Spare_cfg2
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_2_Spare_cfg2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_2_Spare_cfg2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_2_Spare_cfg2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 3
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_3
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_3  VTSS_IOREG(0x02, 0, 0xef03)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_3 . Spare_cfg3
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_3_Spare_cfg3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_3_Spare_cfg3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_3_Spare_cfg3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 4
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_4
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_4  VTSS_IOREG(0x02, 0, 0xef04)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_4 . Spare_cfg4
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_4_Spare_cfg4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_4_Spare_cfg4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_4_Spare_cfg4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 5
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_5
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_5  VTSS_IOREG(0x02, 0, 0xef05)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_5 . Spare_cfg5
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_5_Spare_cfg5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_5_Spare_cfg5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_5_Spare_cfg5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 6
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_6
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_6  VTSS_IOREG(0x02, 0, 0xef06)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_6 . Spare_cfg6
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_6_Spare_cfg6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_6_Spare_cfg6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_6_Spare_cfg6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 7
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_7
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_7  VTSS_IOREG(0x02, 0, 0xef07)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_7 . Spare_cfg7
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_7_Spare_cfg7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_7_Spare_cfg7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_7_Spare_cfg7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 8
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_8
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_8  VTSS_IOREG(0x02, 0, 0xef08)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_8 . Spare_cfg8
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_8_Spare_cfg8(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_8_Spare_cfg8     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_8_Spare_cfg8(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 9
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_9
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_9  VTSS_IOREG(0x02, 0, 0xef09)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_9 . Spare_cfg9
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_9_Spare_cfg9(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_9_Spare_cfg9     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_9_Spare_cfg9(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 10
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_10
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_10  VTSS_IOREG(0x02, 0, 0xef0a)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_10 . Spare_cfg10
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_10_Spare_cfg10(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_10_Spare_cfg10     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_10_Spare_cfg10(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 11
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_11
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_11  VTSS_IOREG(0x02, 0, 0xef0b)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_11 . Spare_cfg11
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_11_Spare_cfg11(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_11_Spare_cfg11     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_11_Spare_cfg11(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 12
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_12
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_12  VTSS_IOREG(0x02, 0, 0xef0c)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_12 . Spare_cfg12
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_12_Spare_cfg12(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_12_Spare_cfg12     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_12_Spare_cfg12(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 13
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_13
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_13  VTSS_IOREG(0x02, 0, 0xef0d)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_13 . Spare_cfg13
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_13_Spare_cfg13(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_13_Spare_cfg13     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_13_Spare_cfg13(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 14
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_14
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_14  VTSS_IOREG(0x02, 0, 0xef0e)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_14 . Spare_cfg14
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_14_Spare_cfg14(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_14_Spare_cfg14     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_14_Spare_cfg14(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Control 15
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Control_15
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_15  VTSS_IOREG(0x02, 0, 0xef0f)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_15 . Spare_cfg15
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_15_Spare_cfg15(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_15_Spare_cfg15     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Control_15_Spare_cfg15(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 0
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_0
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_0  VTSS_IOREG(0x02, 0, 0xef10)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_0 . Spare_stat0
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_0_Spare_stat0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_0_Spare_stat0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_0_Spare_stat0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 1
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_1
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_1  VTSS_IOREG(0x02, 0, 0xef11)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_1 . Spare_stat1
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_1_Spare_stat1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_1_Spare_stat1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_1_Spare_stat1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 2
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_2
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_2  VTSS_IOREG(0x02, 0, 0xef12)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_2 . Spare_stat2
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_2_Spare_stat2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_2_Spare_stat2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_2_Spare_stat2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 3
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_3
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_3  VTSS_IOREG(0x02, 0, 0xef13)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_3 . Spare_stat3
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_3_Spare_stat3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_3_Spare_stat3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_3_Spare_stat3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 4
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_4
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_4  VTSS_IOREG(0x02, 0, 0xef14)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_4 . Spare_stat4
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_4_Spare_stat4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_4_Spare_stat4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_4_Spare_stat4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief WIS Spare Status 5
 *
 * \details
 * Register: \a WIS:WIS_Spare_CFG_STAT:WIS_Spare_Status_5
 */
#define VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_5  VTSS_IOREG(0x02, 0, 0xef15)

/** 
 * \brief
 * Spare
 *
 * \details 
 * Field: VTSS_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_5 . Spare_stat5
 */
#define  VTSS_F_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_5_Spare_stat5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_5_Spare_stat5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_WIS_WIS_Spare_CFG_STAT_WIS_Spare_Status_5_Spare_stat5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_MALIBU_REGS_WIS_H_ */
