/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/tbi_pdi_def.xml
// Register File Name  : TBI_PDI
// Register File Title : TBI Submodule PDI Register File
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _TBI_PDI_H
#define _TBI_PDI_H

//! \defgroup TBI_PDI Register File TBI_PDI - TBI Submodule PDI Register File
//! @{

//! Base Address of TBI_PDI
#define TBI_PDI_MODULE_BASE 0x00D34C00u

//! \defgroup TBI_PDI_TXANEGH Register TBI_PDI_TXANEGH - Transmit Register Autonegotiation High Byte(15:8)
//! @{

//! Register Offset (relative)
#define TBI_PDI_TXANEGH 0x0
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TXANEGH 0x00D34C00u

//! Register Reset Value
#define TBI_PDI_TXANEGH_RST 0x00000000u

//! Field DATAH - Higher Data or Control Bits for Autonegotiation
#define TBI_PDI_TXANEGH_DATAH_POS 0
//! Field DATAH - Higher Data or Control Bits for Autonegotiation
#define TBI_PDI_TXANEGH_DATAH_MASK 0x3Fu

//! Field NP - Next Page
#define TBI_PDI_TXANEGH_NP_POS 7
//! Field NP - Next Page
#define TBI_PDI_TXANEGH_NP_MASK 0x80u
//! Constant LAST - Last Page
#define CONST_TBI_PDI_TXANEGH_NP_LAST 0x0
//! Constant NEXT - Additional next page to follow
#define CONST_TBI_PDI_TXANEGH_NP_NEXT 0x1

//! @}

//! \defgroup TBI_PDI_TXANEGL Register TBI_PDI_TXANEGL - Transmit Register Autonegotiation Low Byte (7:0)
//! @{

//! Register Offset (relative)
#define TBI_PDI_TXANEGL 0x4
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TXANEGL 0x00D34C04u

//! Register Reset Value
#define TBI_PDI_TXANEGL_RST 0x00000000u

//! Field DATAL - Lower Data or Control Bits for Autonegotiation
#define TBI_PDI_TXANEGL_DATAL_POS 0
//! Field DATAL - Lower Data or Control Bits for Autonegotiation
#define TBI_PDI_TXANEGL_DATAL_MASK 0xFFu

//! @}

//! \defgroup TBI_PDI_RXANEGH Register TBI_PDI_RXANEGH - Receive Register Autonegotiation High Byte(15:8)
//! @{

//! Register Offset (relative)
#define TBI_PDI_RXANEGH 0x8
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_RXANEGH 0x00D34C08u

//! Register Reset Value
#define TBI_PDI_RXANEGH_RST 0x00000000u

//! Field DATAH1 - Higher Data or Control Bits for Autonegotiation
#define TBI_PDI_RXANEGH_DATAH1_POS 0
//! Field DATAH1 - Higher Data or Control Bits for Autonegotiation
#define TBI_PDI_RXANEGH_DATAH1_MASK 0x3Fu

//! Field ACK - Acknowledge
#define TBI_PDI_RXANEGH_ACK_POS 6
//! Field ACK - Acknowledge
#define TBI_PDI_RXANEGH_ACK_MASK 0x40u
//! Constant NAK - No Acknowlegde received
#define CONST_TBI_PDI_RXANEGH_ACK_NAK 0x0
//! Constant ACK - Acknowlegde received
#define CONST_TBI_PDI_RXANEGH_ACK_ACK 0x1

//! Field NP1 - Next Page
#define TBI_PDI_RXANEGH_NP1_POS 7
//! Field NP1 - Next Page
#define TBI_PDI_RXANEGH_NP1_MASK 0x80u
//! Constant LAST - Last Page
#define CONST_TBI_PDI_RXANEGH_NP1_LAST 0x0
//! Constant NEXT - Additional next page to follow
#define CONST_TBI_PDI_RXANEGH_NP1_NEXT 0x1

//! @}

//! \defgroup TBI_PDI_RXANEGL Register TBI_PDI_RXANEGL - Receive Register Autonegotiation Low Byte(7:0)
//! @{

//! Register Offset (relative)
#define TBI_PDI_RXANEGL 0xC
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_RXANEGL 0x00D34C0Cu

//! Register Reset Value
#define TBI_PDI_RXANEGL_RST 0x00000000u

//! Field DATAL1 - Lower Data or Control Bits for Autonegotiation
#define TBI_PDI_RXANEGL_DATAL1_POS 0
//! Field DATAL1 - Lower Data or Control Bits for Autonegotiation
#define TBI_PDI_RXANEGL_DATAL1_MASK 0xFFu

//! @}

//! \defgroup TBI_PDI_ANEGCTL Register TBI_PDI_ANEGCTL - Autonegotiation Control Bits of TBI
//! @{

//! Register Offset (relative)
#define TBI_PDI_ANEGCTL 0x10
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_ANEGCTL 0x00D34C10u

//! Register Reset Value
#define TBI_PDI_ANEGCTL_RST 0x000000B2u

//! Field LT - Link Timer Value
#define TBI_PDI_ANEGCTL_LT_POS 0
//! Field LT - Link Timer Value
#define TBI_PDI_ANEGCTL_LT_MASK 0x3u
//! Constant T_10US - Timer Delay is 10 us (Simulation)
#define CONST_TBI_PDI_ANEGCTL_LT_T_10US 0x0
//! Constant T_1_6MS - Timer Delay is 1.6 ms (SGMII)
#define CONST_TBI_PDI_ANEGCTL_LT_T_1_6MS 0x1
//! Constant T_5MS - Timer Delay is 5 ms
#define CONST_TBI_PDI_ANEGCTL_LT_T_5MS 0x2
//! Constant T_10MS - Timer Delay is 10 ms (TBI)
#define CONST_TBI_PDI_ANEGCTL_LT_T_10MS 0x3

//! Field ANEGEN - Auto-Negotiation Enable
#define TBI_PDI_ANEGCTL_ANEGEN_POS 2
//! Field ANEGEN - Auto-Negotiation Enable
#define TBI_PDI_ANEGCTL_ANEGEN_MASK 0x4u
//! Constant DISABLE - Autonegotiation is disabled
#define CONST_TBI_PDI_ANEGCTL_ANEGEN_DISABLE 0x0
//! Constant ENABLE - Autonegotiation is enabled
#define CONST_TBI_PDI_ANEGCTL_ANEGEN_ENABLE 0x1

//! Field RANEG - Restart Autonegotiation Process
#define TBI_PDI_ANEGCTL_RANEG_POS 3
//! Field RANEG - Restart Autonegotiation Process
#define TBI_PDI_ANEGCTL_RANEG_MASK 0x8u
//! Constant NORMAL - Normal Operation
#define CONST_TBI_PDI_ANEGCTL_RANEG_NORMAL 0x0
//! Constant RESTART - Restart Autonegotiation Process
#define CONST_TBI_PDI_ANEGCTL_RANEG_RESTART 0x1

//! Field OVRABL - Override Ability for tx_config_reg
#define TBI_PDI_ANEGCTL_OVRABL_POS 4
//! Field OVRABL - Override Ability for tx_config_reg
#define TBI_PDI_ANEGCTL_OVRABL_MASK 0x10u
//! Constant HW_INT - Hardware mode: Ability Values are taken from Interface Signals
#define CONST_TBI_PDI_ANEGCTL_OVRABL_HW_INT 0x0
//! Constant OVERRIDE - Register Mode: Override, Ability Values are taken from Registers
#define CONST_TBI_PDI_ANEGCTL_OVRABL_OVERRIDE 0x1

//! Field OVRANEG - Override Ability for ANEG control
#define TBI_PDI_ANEGCTL_OVRANEG_POS 5
//! Field OVRANEG - Override Ability for ANEG control
#define TBI_PDI_ANEGCTL_OVRANEG_MASK 0x20u
//! Constant HW_INT - Hardware mode: ANEG Mode, Enable ANEG and restart ANEG are taken from fro...
#define CONST_TBI_PDI_ANEGCTL_OVRANEG_HW_INT 0x0
//! Constant OVERRIDE - Register Mode: ANEG Mode, Enable ANEG and restart ANEG are taken from bit...
#define CONST_TBI_PDI_ANEGCTL_OVRANEG_OVERRIDE 0x1

//! Field ANMODE - Mode of ANEG
#define TBI_PDI_ANEGCTL_ANMODE_POS 6
//! Field ANMODE - Mode of ANEG
#define TBI_PDI_ANEGCTL_ANMODE_MASK 0xC0u
//! Constant RESERVED - RESERVED
#define CONST_TBI_PDI_ANEGCTL_ANMODE_RESERVED 0x0
//! Constant SGMII_1000BX - 1000bX mode: ANEG will done as defined by 1000bX
#define CONST_TBI_PDI_ANEGCTL_ANMODE_SGMII_1000BX 0x1
//! Constant SGMII_MAC - SGMII PHY mode: ANEG will done as defined by SGMII standard, as PHY
#define CONST_TBI_PDI_ANEGCTL_ANMODE_SGMII_MAC 0x2
//! Constant SGMII_PHY - SGMII MAC mode: ANEG will done as defined by SGMII standard, as MAC
#define CONST_TBI_PDI_ANEGCTL_ANMODE_SGMII_PHY 0x3

//! Field BCOMP - Backwards compatibilty control
#define TBI_PDI_ANEGCTL_BCOMP_POS 15
//! Field BCOMP - Backwards compatibilty control
#define TBI_PDI_ANEGCTL_BCOMP_MASK 0x8000u
//! Constant INCOMP - Backwards incompatible mode
#define CONST_TBI_PDI_ANEGCTL_BCOMP_INCOMP 0x0
//! Constant COMP - Backwards compatible mode
#define CONST_TBI_PDI_ANEGCTL_BCOMP_COMP 0x1

//! @}

//! \defgroup TBI_PDI_TBICTL Register TBI_PDI_TBICTL - TBI Control Bits
//! @{

//! Register Offset (relative)
#define TBI_PDI_TBICTL 0x14
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TBICTL 0x00D34C14u

//! Register Reset Value
#define TBI_PDI_TBICTL_RST 0x00000001u

//! Field INITTBI - Reset of TBI FSM's
#define TBI_PDI_TBICTL_INITTBI_POS 0
//! Field INITTBI - Reset of TBI FSM's
#define TBI_PDI_TBICTL_INITTBI_MASK 0x1u
//! Constant NORMAL - normal operation
#define CONST_TBI_PDI_TBICTL_INITTBI_NORMAL 0x0
//! Constant INIT - Initialisation of TBI
#define CONST_TBI_PDI_TBICTL_INITTBI_INIT 0x1

//! Field ENTBI - Enable of TBI Interface
#define TBI_PDI_TBICTL_ENTBI_POS 1
//! Field ENTBI - Enable of TBI Interface
#define TBI_PDI_TBICTL_ENTBI_MASK 0x2u
//! Constant DISABLE - TBI Interface is disabled
#define CONST_TBI_PDI_TBICTL_ENTBI_DISABLE 0x0
//! Constant ENABLE - TBI Interface is enabled
#define CONST_TBI_PDI_TBICTL_ENTBI_ENABLE 0x1

//! Field LPB1 - Loopback Mode of TBI
#define TBI_PDI_TBICTL_LPB1_POS 2
//! Field LPB1 - Loopback Mode of TBI
#define TBI_PDI_TBICTL_LPB1_MASK 0x4u
//! Constant NORMAL - normal operation
#define CONST_TBI_PDI_TBICTL_LPB1_NORMAL 0x0
//! Constant LOOPBACK - loopback enabled
#define CONST_TBI_PDI_TBICTL_LPB1_LOOPBACK 0x1

//! Field RPM - Repeater Mode of TBI
#define TBI_PDI_TBICTL_RPM_POS 3
//! Field RPM - Repeater Mode of TBI
#define TBI_PDI_TBICTL_RPM_MASK 0x8u
//! Constant NORMAL - normal operation
#define CONST_TBI_PDI_TBICTL_RPM_NORMAL 0x0
//! Constant REPEATER - repeater mode enabled
#define CONST_TBI_PDI_TBICTL_RPM_REPEATER 0x1

//! Field CRSTRR - Carrier Sense Extension for Sequence T/R/R/
#define TBI_PDI_TBICTL_CRSTRR_POS 4
//! Field CRSTRR - Carrier Sense Extension for Sequence T/R/R/
#define TBI_PDI_TBICTL_CRSTRR_MASK 0x10u
//! Constant NO - No Generate Carrier Extension
#define CONST_TBI_PDI_TBICTL_CRSTRR_NO 0x0
//! Constant YES - Generate Carrier Extension
#define CONST_TBI_PDI_TBICTL_CRSTRR_YES 0x1

//! Field CRSOFF - Carrier Sense OFF
#define TBI_PDI_TBICTL_CRSOFF_POS 5
//! Field CRSOFF - Carrier Sense OFF
#define TBI_PDI_TBICTL_CRSOFF_MASK 0x20u
//! Constant ON - Carrier Sense is always generated in HD and FD
#define CONST_TBI_PDI_TBICTL_CRSOFF_ON 0x0
//! Constant OFF - Carrier Sense is never generated, forced to 0
#define CONST_TBI_PDI_TBICTL_CRSOFF_OFF 0x1

//! Field RVBI - Reverse Bit Order Input
#define TBI_PDI_TBICTL_RVBI_POS 6
//! Field RVBI - Reverse Bit Order Input
#define TBI_PDI_TBICTL_RVBI_MASK 0x40u
//! Constant NORMAL - 10 Bit Input according to Standard
#define CONST_TBI_PDI_TBICTL_RVBI_NORMAL 0x0
//! Constant REVERS - 10 Bit Input with reversed Bit Order
#define CONST_TBI_PDI_TBICTL_RVBI_REVERS 0x1

//! Field RVBO - Reverse Bit Order Output
#define TBI_PDI_TBICTL_RVBO_POS 7
//! Field RVBO - Reverse Bit Order Output
#define TBI_PDI_TBICTL_RVBO_MASK 0x80u
//! Constant NORMAL - 10 Bit Output according to Standard
#define CONST_TBI_PDI_TBICTL_RVBO_NORMAL 0x0
//! Constant REVERS - 10 Bit Output with reversed Bit Order
#define CONST_TBI_PDI_TBICTL_RVBO_REVERS 0x1

//! @}

//! \defgroup TBI_PDI_TBICTLT Register TBI_PDI_TBICTLT - TBI Control Bits TX
//! @{

//! Register Offset (relative)
#define TBI_PDI_TBICTLT 0x18
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TBICTLT 0x00D34C18u

//! Register Reset Value
#define TBI_PDI_TBICTLT_RST 0x00000000u

//! Field TXFS - Transmit False Carrier Insertion
#define TBI_PDI_TBICTLT_TXFS_POS 0
//! Field TXFS - Transmit False Carrier Insertion
#define TBI_PDI_TBICTLT_TXFS_MASK 0x1u
//! Constant NO - No False Carrier Insertion
#define CONST_TBI_PDI_TBICTLT_TXFS_NO 0x0
//! Constant YES - False Carrier Insertion
#define CONST_TBI_PDI_TBICTLT_TXFS_YES 0x1

//! @}

//! \defgroup TBI_PDI_TBITEST Register TBI_PDI_TBITEST - TBI TEST Control Bits
//! @{

//! Register Offset (relative)
#define TBI_PDI_TBITEST 0x1C
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TBITEST 0x00D34C1Cu

//! Register Reset Value
#define TBI_PDI_TBITEST_RST 0x00000000u

//! Field JITE - Jitter Test pattern for Transmit
#define TBI_PDI_TBITEST_JITE_POS 0
//! Field JITE - Jitter Test pattern for Transmit
#define TBI_PDI_TBITEST_JITE_MASK 0x3u
//! Constant NO - Normal Function
#define CONST_TBI_PDI_TBITEST_JITE_NO 0x0
//! Constant HIGH - Transmit High Frequency test pattern 36A.1
#define CONST_TBI_PDI_TBITEST_JITE_HIGH 0x1
//! Constant LOW - Transmit Low Frequency test pattern 36A.2
#define CONST_TBI_PDI_TBITEST_JITE_LOW 0x2
//! Constant MIXED - Transmit Mixed Frequency test pattern 36A.3
#define CONST_TBI_PDI_TBITEST_JITE_MIXED 0x3

//! Field RXEREN - Enable RX Error Counter
#define TBI_PDI_TBITEST_RXEREN_POS 2
//! Field RXEREN - Enable RX Error Counter
#define TBI_PDI_TBITEST_RXEREN_MASK 0x4u
//! Constant DISABLE - RX Error Counter is disabled
#define CONST_TBI_PDI_TBITEST_RXEREN_DISABLE 0x0
//! Constant ENABLE - RX Error Counter is enabled
#define CONST_TBI_PDI_TBITEST_RXEREN_ENABLE 0x1

//! @}

//! \defgroup TBI_PDI_RXERR Register TBI_PDI_RXERR - RX Error Counter
//! @{

//! Register Offset (relative)
#define TBI_PDI_RXERR 0x20
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_RXERR 0x00D34C20u

//! Register Reset Value
#define TBI_PDI_RXERR_RST 0x00000000u

//! Field RXERRC - RX Error Counter
#define TBI_PDI_RXERR_RXERRC_POS 0
//! Field RXERRC - RX Error Counter
#define TBI_PDI_RXERR_RXERRC_MASK 0xFFu

//! @}

//! \defgroup TBI_PDI_TBISTAT Register TBI_PDI_TBISTAT - TBI Status Register
//! @{

//! Register Offset (relative)
#define TBI_PDI_TBISTAT 0x24
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TBISTAT 0x00D34C24u

//! Register Reset Value
#define TBI_PDI_TBISTAT_RST 0x00000000u

//! Field LSTAT - Link Status of TBI
#define TBI_PDI_TBISTAT_LSTAT_POS 0
//! Field LSTAT - Link Status of TBI
#define TBI_PDI_TBISTAT_LSTAT_MASK 0x1u
//! Constant NOK - Autonegotiation State Machine is not in LINK_OK state
#define CONST_TBI_PDI_TBISTAT_LSTAT_NOK 0x0
//! Constant OK - Autonegotiation State Machine is in LINK_OK state
#define CONST_TBI_PDI_TBISTAT_LSTAT_OK 0x1

//! Field ABMSTAT - Ability match of TBI
#define TBI_PDI_TBISTAT_ABMSTAT_POS 1
//! Field ABMSTAT - Ability match of TBI
#define TBI_PDI_TBISTAT_ABMSTAT_MASK 0x2u
//! Constant NOK - Autonegotiation State Machine ability does not match
#define CONST_TBI_PDI_TBISTAT_ABMSTAT_NOK 0x0
//! Constant OK - Autonegotiation State Machine ability match
#define CONST_TBI_PDI_TBISTAT_ABMSTAT_OK 0x1

//! Field ANEGERR - Autonegotiation Error
#define TBI_PDI_TBISTAT_ANEGERR_POS 2
//! Field ANEGERR - Autonegotiation Error
#define TBI_PDI_TBISTAT_ANEGERR_MASK 0x4u
//! Constant NO_ERROR - No Autonegotiation Error
#define CONST_TBI_PDI_TBISTAT_ANEGERR_NO_ERROR 0x0
//! Constant ERROR - Autonegotiation Error
#define CONST_TBI_PDI_TBISTAT_ANEGERR_ERROR 0x1

//! Field SSTAT - Sync Status of the TBI Sync FSM
#define TBI_PDI_TBISTAT_SSTAT_POS 3
//! Field SSTAT - Sync Status of the TBI Sync FSM
#define TBI_PDI_TBISTAT_SSTAT_MASK 0x8u
//! Constant NOK - Sync Status of TBI is not OK
#define CONST_TBI_PDI_TBISTAT_SSTAT_NOK 0x0
//! Constant OK - SYnc Status of TBI is OK
#define CONST_TBI_PDI_TBISTAT_SSTAT_OK 0x1

//! @}

//! \defgroup TBI_PDI_LPSTAT Register TBI_PDI_LPSTAT - Link Partner Status Register
//! @{

//! Register Offset (relative)
#define TBI_PDI_LPSTAT 0x28
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_LPSTAT 0x00D34C28u

//! Register Reset Value
#define TBI_PDI_LPSTAT_RST 0x00000000u

//! Field DPX - Duplex Status
#define TBI_PDI_LPSTAT_DPX_POS 0
//! Field DPX - Duplex Status
#define TBI_PDI_LPSTAT_DPX_MASK 0x1u
//! Constant HD - Half Duplex Mode
#define CONST_TBI_PDI_LPSTAT_DPX_HD 0x0
//! Constant FD - Full Duplex Mode
#define CONST_TBI_PDI_LPSTAT_DPX_FD 0x1

//! Field PS - Pause
#define TBI_PDI_LPSTAT_PS_POS 1
//! Field PS - Pause
#define TBI_PDI_LPSTAT_PS_MASK 0x6u
//! Constant NO - No Pause
#define CONST_TBI_PDI_LPSTAT_PS_NO 0x0
//! Constant RECEIVE - Receive PAUSE
#define CONST_TBI_PDI_LPSTAT_PS_RECEIVE 0x1
//! Constant TRANSMIT - Transmit PAUSE
#define CONST_TBI_PDI_LPSTAT_PS_TRANSMIT 0x2
//! Constant BOTH - Receive and Transmit PAUSE
#define CONST_TBI_PDI_LPSTAT_PS_BOTH 0x3

//! Field RF - Remote Fault
#define TBI_PDI_LPSTAT_RF_POS 3
//! Field RF - Remote Fault
#define TBI_PDI_LPSTAT_RF_MASK 0x18u
//! Constant LINK_OK - No Error, link OK
#define CONST_TBI_PDI_LPSTAT_RF_LINK_OK 0x0
//! Constant LINK_FAIL - Link Failure, Link Down in SGMII Mode
#define CONST_TBI_PDI_LPSTAT_RF_LINK_FAIL 0x1
//! Constant OFFLINE - Offline, not used in SGMII Mode
#define CONST_TBI_PDI_LPSTAT_RF_OFFLINE 0x2
//! Constant ANEG_ERROR - Autonegotiation_Error, not used in SGMII Mode
#define CONST_TBI_PDI_LPSTAT_RF_ANEG_ERROR 0x3

//! Field DR - SGMII DATA RATE
#define TBI_PDI_LPSTAT_DR_POS 5
//! Field DR - SGMII DATA RATE
#define TBI_PDI_LPSTAT_DR_MASK 0x60u
//! Constant DR10 - Data Rate is 10 Mb/s
#define CONST_TBI_PDI_LPSTAT_DR_DR10 0x0
//! Constant DR100 - Data Rate is 100 Mb/s
#define CONST_TBI_PDI_LPSTAT_DR_DR100 0x1
//! Constant DR1000 - Data Rate is 1000 Mb/s
#define CONST_TBI_PDI_LPSTAT_DR_DR1000 0x2
//! Constant INVALID - Not SGMII Mode
#define CONST_TBI_PDI_LPSTAT_DR_INVALID 0x3

//! @}

//! \defgroup TBI_PDI_ISTAT Register TBI_PDI_ISTAT - Interrupt Status Register
//! @{

//! Register Offset (relative)
#define TBI_PDI_ISTAT 0x2C
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_ISTAT 0x00D34C2Cu

//! Register Reset Value
#define TBI_PDI_ISTAT_RST 0x00000000u

//! Field ANEG_BP - Autonegotiation Interrupt Base Page
#define TBI_PDI_ISTAT_ANEG_BP_POS 0
//! Field ANEG_BP - Autonegotiation Interrupt Base Page
#define TBI_PDI_ISTAT_ANEG_BP_MASK 0x1u

//! Field ANEG_NP - Autonegotiation Interrupt Next Page
#define TBI_PDI_ISTAT_ANEG_NP_POS 1
//! Field ANEG_NP - Autonegotiation Interrupt Next Page
#define TBI_PDI_ISTAT_ANEG_NP_MASK 0x2u

//! Field LKSC - Link Status Change
#define TBI_PDI_ISTAT_LKSC_POS 2
//! Field LKSC - Link Status Change
#define TBI_PDI_ISTAT_LKSC_MASK 0x4u

//! Field SYNCSC - Sync Status Change
#define TBI_PDI_ISTAT_SYNCSC_POS 3
//! Field SYNCSC - Sync Status Change
#define TBI_PDI_ISTAT_SYNCSC_MASK 0x8u

//! Field LOSSC - Sync Status Change
#define TBI_PDI_ISTAT_LOSSC_POS 4
//! Field LOSSC - Sync Status Change
#define TBI_PDI_ISTAT_LOSSC_MASK 0x10u

//! @}

//! \defgroup TBI_PDI_IMASK Register TBI_PDI_IMASK - Interrupt Mask Register
//! @{

//! Register Offset (relative)
#define TBI_PDI_IMASK 0x30
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_IMASK 0x00D34C30u

//! Register Reset Value
#define TBI_PDI_IMASK_RST 0x0000001Fu

//! Field MANEG_BP - Mask Autonegotiation Base Page
#define TBI_PDI_IMASK_MANEG_BP_POS 0
//! Field MANEG_BP - Mask Autonegotiation Base Page
#define TBI_PDI_IMASK_MANEG_BP_MASK 0x1u
//! Constant UMASK - Unmask Autonegotiation Interrupt
#define CONST_TBI_PDI_IMASK_MANEG_BP_UMASK 0x0
//! Constant MASK - Mask Autonegotiation Interrupt
#define CONST_TBI_PDI_IMASK_MANEG_BP_MASK 0x1

//! Field MANEG_NP - Mask Autonegotiation Next Page
#define TBI_PDI_IMASK_MANEG_NP_POS 1
//! Field MANEG_NP - Mask Autonegotiation Next Page
#define TBI_PDI_IMASK_MANEG_NP_MASK 0x2u
//! Constant UMASK - Unmask Autonegotiation Interrupt
#define CONST_TBI_PDI_IMASK_MANEG_NP_UMASK 0x0
//! Constant MASK - Mask Autonegotiation Interrupt
#define CONST_TBI_PDI_IMASK_MANEG_NP_MASK 0x1

//! Field MLKSC - Link Status change
#define TBI_PDI_IMASK_MLKSC_POS 2
//! Field MLKSC - Link Status change
#define TBI_PDI_IMASK_MLKSC_MASK 0x4u
//! Constant UMASK - Unmask LKSC Interrupt
#define CONST_TBI_PDI_IMASK_MLKSC_UMASK 0x0
//! Constant MASK - Mask LKSC Interrupt
#define CONST_TBI_PDI_IMASK_MLKSC_MASK 0x1

//! Field MSYNCSC - Sync Status change
#define TBI_PDI_IMASK_MSYNCSC_POS 3
//! Field MSYNCSC - Sync Status change
#define TBI_PDI_IMASK_MSYNCSC_MASK 0x8u
//! Constant UMASK - Unmask SYNCSC Interrupt
#define CONST_TBI_PDI_IMASK_MSYNCSC_UMASK 0x0
//! Constant MASK - Mask SYNCSC Interrupt
#define CONST_TBI_PDI_IMASK_MSYNCSC_MASK 0x1

//! Field MLOSSC - LOS Status change
#define TBI_PDI_IMASK_MLOSSC_POS 4
//! Field MLOSSC - LOS Status change
#define TBI_PDI_IMASK_MLOSSC_MASK 0x10u
//! Constant UMASK - Unmask LOSSC Interrupt
#define CONST_TBI_PDI_IMASK_MLOSSC_UMASK 0x0
//! Constant MASK - Mask LOSSC Interrupt
#define CONST_TBI_PDI_IMASK_MLOSSC_MASK 0x1

//! @}

//! \defgroup TBI_PDI_TX_FSM_STAT Register TBI_PDI_TX_FSM_STAT - trasmitter state
//! @{

//! Register Offset (relative)
#define TBI_PDI_TX_FSM_STAT 0x34
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TX_FSM_STAT 0x00D34C34u

//! Register Reset Value
#define TBI_PDI_TX_FSM_STAT_RST 0x00000000u

//! Field TX_FSM_STATUS - state of transmit fsm
#define TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_POS 0
//! Field TX_FSM_STATUS - state of transmit fsm
#define TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_MASK 0x1Fu
//! Constant RESET_TX - reset txstate
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_RESET_TX 0x0
//! Constant TX_TEST_TRANSMIT - check xmit state
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_TEST_TRANSMIT 0x1
//! Constant CONFIGURATION_ST - send config part
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_CONFIGURATION_ST 0x2
//! Constant IDLE_TX - send idle
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_IDLE_TX 0x3
//! Constant XMIT_DATA - send indication for tx data
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_XMIT_DATA 0x4
//! Constant TX_START_OF_PACKET - send sfd
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_START_OF_PACKET 0x5
//! Constant TX_DATA - send data
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_DATA 0x6
//! Constant TX_END_OF_PACKET_NOEXT - send epd
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_END_OF_PACKET_NOEXT 0x7
//! Constant END_OF_PACKET_EXT - send end of packet at txeven is zero and err is zero
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_END_OF_PACKET_EXT 0x8
//! Constant EPD2_NOEXT - align to tx_even is zero
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_EPD2_NOEXT 0x9
//! Constant EPD3 - send R if txeven is one
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_EPD3 0xA
//! Constant EXTEND_BY_1 - send r for carrier ext
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_EXTEND_BY_1 0xB
//! Constant CARRIER_EXTEND - err is one then send sfd or send start of err
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_CARRIER_EXTEND 0xC
//! Constant ALIGN_ERR_START - send error at txeven
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_ALIGN_ERR_START 0xD
//! Constant START_ERROR - send start of error at one
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_START_ERROR 0xE
//! Constant TX_DATA_ERROR - send error data
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_DATA_ERROR 0xF
//! Constant TX_FALSE_CARRIER - send false carrier
#define CONST_TBI_PDI_TX_FSM_STAT_TX_FSM_STATUS_TX_FALSE_CARRIER 0x10

//! @}

//! \defgroup TBI_PDI_RX_FSM_STAT Register TBI_PDI_RX_FSM_STAT - receiver state
//! @{

//! Register Offset (relative)
#define TBI_PDI_RX_FSM_STAT 0x38
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_RX_FSM_STAT 0x00D34C38u

//! Register Reset Value
#define TBI_PDI_RX_FSM_STAT_RST 0x00000000u

//! Field RX_FSM_STATUS - state of recieve fsm
#define TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_POS 0
//! Field RX_FSM_STATUS - state of recieve fsm
#define TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_MASK 0x1Fu
//! Constant RESET - reset state
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RESET 0x0
//! Constant LINK_FAILED - link failed
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_LINK_FAILED 0x1
//! Constant WAIT_FOR_K - wait for comma state
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_WAIT_FOR_K 0x2
//! Constant RX_K - recieved comma
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_K 0x3
//! Constant RX_CB - recieved config bit
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_CB 0x4
//! Constant RX_CC - recieved config1 bit
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_CC 0x5
//! Constant RX_CD - recieved config2 bit
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_CD 0x6
//! Constant RX_INVALID - recieved data is invalid
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_INVALID 0x7
//! Constant IDLE_D - idle state
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_IDLE_D 0x8
//! Constant FALSE_CARRIER - false carrier detection
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_FALSE_CARRIER 0x9
//! Constant START_OF_PACKET - start of packet detected
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_START_OF_PACKET 0xA
//! Constant EARLY_END - early end of packet detected
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_EARLY_END 0xB
//! Constant TRI_RRI - packet termination recieved correctly
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_TRI_RRI 0xC
//! Constant TRR_EXTEND - packet termination recieved correctly with carrier extend&check epd
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_TRR_EXTEND 0xD
//! Constant TRR_EXTEND_A - packet termination recieved correctly with carrier extend
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_TRR_EXTEND_A 0xE
//! Constant PACKET_BURST_RRS - recieving packet burst
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_PACKET_BURST_RRS 0xF
//! Constant EXTEND_ERR - carrier extend err
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_EXTEND_ERR 0x10
//! Constant RX_DATA_ERROR - recieving wrong data
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_DATA_ERROR 0x11
//! Constant RX_DATA - recieving data
#define CONST_TBI_PDI_RX_FSM_STAT_RX_FSM_STATUS_RX_DATA 0x12

//! @}

//! \defgroup TBI_PDI_LPISTAT1 Register TBI_PDI_LPISTAT1 - lpi wtf status
//! @{

//! Register Offset (relative)
#define TBI_PDI_LPISTAT1 0x3C
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_LPISTAT1 0x00D34C3Cu

//! Register Reset Value
#define TBI_PDI_LPISTAT1_RST 0x00000000u

//! Field WTF_ERROR_CNT - wtf error count
#define TBI_PDI_LPISTAT1_WTF_ERROR_CNT_POS 0
//! Field WTF_ERROR_CNT - wtf error count
#define TBI_PDI_LPISTAT1_WTF_ERROR_CNT_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_LPISTAT2 Register TBI_PDI_LPISTAT2 - LPI Status Register
//! @{

//! Register Offset (relative)
#define TBI_PDI_LPISTAT2 0x40
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_LPISTAT2 0x00D34C40u

//! Register Reset Value
#define TBI_PDI_LPISTAT2_RST 0x0000000Cu

//! Field RXQUIET - Receive FSM Quiet Status
#define TBI_PDI_LPISTAT2_RXQUIET_POS 0
//! Field RXQUIET - Receive FSM Quiet Status
#define TBI_PDI_LPISTAT2_RXQUIET_MASK 0x1u
//! Constant OFF - RXFSM is in ACTIVE state
#define CONST_TBI_PDI_LPISTAT2_RXQUIET_OFF 0x0
//! Constant ON - RXFSM is in QUIET state
#define CONST_TBI_PDI_LPISTAT2_RXQUIET_ON 0x1

//! Field TXQUIET - Transmit FSM Quiet Status
#define TBI_PDI_LPISTAT2_TXQUIET_POS 1
//! Field TXQUIET - Transmit FSM Quiet Status
#define TBI_PDI_LPISTAT2_TXQUIET_MASK 0x2u
//! Constant OFF - TXFSM is in ACTIVE state
#define CONST_TBI_PDI_LPISTAT2_TXQUIET_OFF 0x0
//! Constant ON - TXFSM is in QUIET state
#define CONST_TBI_PDI_LPISTAT2_TXQUIET_ON 0x1

//! Field RX_LPI_EN - Enable RX LPI
#define TBI_PDI_LPISTAT2_RX_LPI_EN_POS 2
//! Field RX_LPI_EN - Enable RX LPI
#define TBI_PDI_LPISTAT2_RX_LPI_EN_MASK 0x4u
//! Constant DISABLE - RX LPI is disabled
#define CONST_TBI_PDI_LPISTAT2_RX_LPI_EN_DISABLE 0x0
//! Constant ENABLE - RX LPI is enabled
#define CONST_TBI_PDI_LPISTAT2_RX_LPI_EN_ENABLE 0x1

//! Field TX_LPI_EN - Enable TX LPI
#define TBI_PDI_LPISTAT2_TX_LPI_EN_POS 3
//! Field TX_LPI_EN - Enable TX LPI
#define TBI_PDI_LPISTAT2_TX_LPI_EN_MASK 0x8u
//! Constant DISABLE - TX LPI is disabled
#define CONST_TBI_PDI_LPISTAT2_TX_LPI_EN_DISABLE 0x0
//! Constant ENABLE - TX LPI is enabled
#define CONST_TBI_PDI_LPISTAT2_TX_LPI_EN_ENABLE 0x1

//! @}

//! \defgroup TBI_PDI_SGMII_GPHY_LINK_AR_REG Register TBI_PDI_SGMII_GPHY_LINK_AR_REG - Aneg Restart Behavior
//! @{

//! Register Offset (relative)
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG 0x44
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_SGMII_GPHY_LINK_AR_REG 0x00D34C44u

//! Register Reset Value
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG_RST 0x00000002u

//! Field GPHY_LINK_AR_EN - Enable GPHY Link ANEG RESTART
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG_GPHY_LINK_AR_EN_POS 0
//! Field GPHY_LINK_AR_EN - Enable GPHY Link ANEG RESTART
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG_GPHY_LINK_AR_EN_MASK 0x1u
//! Constant DISABLE - Aneg Restart based on SGMII link status
#define CONST_TBI_PDI_SGMII_GPHY_LINK_AR_REG_GPHY_LINK_AR_EN_DISABLE 0x0
//! Constant ENABLE - ANEG Restart based on GPHY/SGMII link status
#define CONST_TBI_PDI_SGMII_GPHY_LINK_AR_REG_GPHY_LINK_AR_EN_ENABLE 0x1

//! Field MASK_SGMII_LINK_STAT - Mask SGMII Link Status for Restart ANEG
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG_MASK_SGMII_LINK_STAT_POS 1
//! Field MASK_SGMII_LINK_STAT - Mask SGMII Link Status for Restart ANEG
#define TBI_PDI_SGMII_GPHY_LINK_AR_REG_MASK_SGMII_LINK_STAT_MASK 0x2u
//! Constant UMASK - Unmask SGMII Link Status for Restart ANEG
#define CONST_TBI_PDI_SGMII_GPHY_LINK_AR_REG_MASK_SGMII_LINK_STAT_UMASK 0x0
//! Constant MASK - Mask SGMII Link Status for Restart ANEG
#define CONST_TBI_PDI_SGMII_GPHY_LINK_AR_REG_MASK_SGMII_LINK_STAT_MASK 0x1

//! @}

//! \defgroup TBI_PDI_ONEMSEC Register TBI_PDI_ONEMSEC
//! @{

//! Register Offset (relative)
#define TBI_PDI_ONEMSEC 0x48
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_ONEMSEC 0x00D34C48u

//! Register Reset Value
#define TBI_PDI_ONEMSEC_RST 0x0000B8D8u

//! Field ONEMSEC_TIMELSB - one ms time lsb
#define TBI_PDI_ONEMSEC_ONEMSEC_TIMELSB_POS 0
//! Field ONEMSEC_TIMELSB - one ms time lsb
#define TBI_PDI_ONEMSEC_ONEMSEC_TIMELSB_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_ONEMSEC2 Register TBI_PDI_ONEMSEC2
//! @{

//! Register Offset (relative)
#define TBI_PDI_ONEMSEC2 0x4C
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_ONEMSEC2 0x00D34C4Cu

//! Register Reset Value
#define TBI_PDI_ONEMSEC2_RST 0x00000005u

//! Field ONEMSEC2_TIMEMSB - one me time msb
#define TBI_PDI_ONEMSEC2_ONEMSEC2_TIMEMSB_POS 0
//! Field ONEMSEC2_TIMEMSB - one me time msb
#define TBI_PDI_ONEMSEC2_ONEMSEC2_TIMEMSB_MASK 0xFu

//! @}

//! \defgroup TBI_PDI_ELEVENUSEC Register TBI_PDI_ELEVENUSEC
//! @{

//! Register Offset (relative)
#define TBI_PDI_ELEVENUSEC 0x50
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_ELEVENUSEC 0x00D34C50u

//! Register Reset Value
#define TBI_PDI_ELEVENUSEC_RST 0x0000101Du

//! Field ELEVENUSEC_TIME - eleven micro second time
#define TBI_PDI_ELEVENUSEC_ELEVENUSEC_TIME_POS 0
//! Field ELEVENUSEC_TIME - eleven micro second time
#define TBI_PDI_ELEVENUSEC_ELEVENUSEC_TIME_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_THREE_FOURMSEC Register TBI_PDI_THREE_FOURMSEC
//! @{

//! Register Offset (relative)
#define TBI_PDI_THREE_FOURMSEC 0x54
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_THREE_FOURMSEC 0x00D34C54u

//! Register Reset Value
#define TBI_PDI_THREE_FOURMSEC_RST 0x00001382u

//! Field THREE_FOURMSEC_TIMELSB - three dot four msec time
#define TBI_PDI_THREE_FOURMSEC_THREE_FOURMSEC_TIMELSB_POS 0
//! Field THREE_FOURMSEC_TIMELSB - three dot four msec time
#define TBI_PDI_THREE_FOURMSEC_THREE_FOURMSEC_TIMELSB_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_THREE_FOURMSEC2 Register TBI_PDI_THREE_FOURMSEC2
//! @{

//! Register Offset (relative)
#define TBI_PDI_THREE_FOURMSEC2 0x58
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_THREE_FOURMSEC2 0x00D34C58u

//! Register Reset Value
#define TBI_PDI_THREE_FOURMSEC2_RST 0x00000015u

//! Field THREE_FOURMSEC2_TIMEMSB - three dot four msec time MSB
#define TBI_PDI_THREE_FOURMSEC2_THREE_FOURMSEC2_TIMEMSB_POS 0
//! Field THREE_FOURMSEC2_TIMEMSB - three dot four msec time MSB
#define TBI_PDI_THREE_FOURMSEC2_THREE_FOURMSEC2_TIMEMSB_MASK 0xFFu

//! @}

//! \defgroup TBI_PDI_TWENTYUSEC Register TBI_PDI_TWENTYUSEC
//! @{

//! Register Offset (relative)
#define TBI_PDI_TWENTYUSEC 0x5C
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TWENTYUSEC 0x00D34C5Cu

//! Register Reset Value
#define TBI_PDI_TWENTYUSEC_RST 0x00001D4Cu

//! Field TWENTYUSEC_TIME - twenty micro sec time
#define TBI_PDI_TWENTYUSEC_TWENTYUSEC_TIME_POS 0
//! Field TWENTYUSEC_TIME - twenty micro sec time
#define TBI_PDI_TWENTYUSEC_TWENTYUSEC_TIME_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_TWO_P_SIX_MSEC Register TBI_PDI_TWO_P_SIX_MSEC
//! @{

//! Register Offset (relative)
#define TBI_PDI_TWO_P_SIX_MSEC 0x60
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TWO_P_SIX_MSEC 0x00D34C60u

//! Register Reset Value
#define TBI_PDI_TWO_P_SIX_MSEC_RST 0x0000E098u

//! Field TWO_P_SIX_MSEC_TIMELSB - two point six msec time
#define TBI_PDI_TWO_P_SIX_MSEC_TWO_P_SIX_MSEC_TIMELSB_POS 0
//! Field TWO_P_SIX_MSEC_TIMELSB - two point six msec time
#define TBI_PDI_TWO_P_SIX_MSEC_TWO_P_SIX_MSEC_TIMELSB_MASK 0xFFFFu

//! @}

//! \defgroup TBI_PDI_TWO_P_SIX_MSEC2 Register TBI_PDI_TWO_P_SIX_MSEC2
//! @{

//! Register Offset (relative)
#define TBI_PDI_TWO_P_SIX_MSEC2 0x64
//! Register Offset (absolute) for 1st Instance TBI_PDI
#define TBI_PDI_TBI_PDI_TWO_P_SIX_MSEC2 0x00D34C64u

//! Register Reset Value
#define TBI_PDI_TWO_P_SIX_MSEC2_RST 0x0000000Eu

//! Field TWO_P_SIX_MSEC2_TIMEMSB - two point six msec time msb
#define TBI_PDI_TWO_P_SIX_MSEC2_TWO_P_SIX_MSEC2_TIMEMSB_POS 0
//! Field TWO_P_SIX_MSEC2_TIMEMSB - two point six msec time msb
#define TBI_PDI_TWO_P_SIX_MSEC2_TWO_P_SIX_MSEC2_TIMEMSB_MASK 0xFu

//! @}

//! @}

#endif
