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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/pm_pdi_def.xml
// Register File Name  : PM_PDI
// Register File Title : PM Registers
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PM_PDI_H
#define _PM_PDI_H

//! \defgroup PM_PDI Register File PM_PDI - PM Registers
//! @{

//! Base Address of PM_PDI for P31G
#define PM_PDI_MODULE_BASE 0x00D38000u
//! Base Address of PM_PDI for P34X
#define P34X_PM_PDI_MODULE_BASE 0x00A38000u

//! \defgroup PM_PDI_CFG Register PM_PDI_CFG - PM Configuration Register
//! @{

//! Register Offset (relative)
#define PM_PDI_CFG 0x0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_CFG 0x00D38000u

//! Register Reset Value
#define PM_PDI_CFG_RST 0x0000001Fu

//! Field GMAC_BYP - GMAC Bypass
#define PM_PDI_CFG_GMAC_BYP_POS 0
//! Field GMAC_BYP - GMAC Bypass
#define PM_PDI_CFG_GMAC_BYP_MASK 0x1u
//! Constant DIS - GMAC not bypass
#define CONST_PM_PDI_CFG_GMAC_BYP_DIS 0x0
//! Constant EN - Enable GMAC bypass
#define CONST_PM_PDI_CFG_GMAC_BYP_EN 0x1

//! Field GMACL_BYP - GMAC-Lite Bypass
#define PM_PDI_CFG_GMACL_BYP_POS 1
//! Field GMACL_BYP - GMAC-Lite Bypass
#define PM_PDI_CFG_GMACL_BYP_MASK 0x2u
//! Constant DIS - GMAC-Lite not bypass
#define CONST_PM_PDI_CFG_GMACL_BYP_DIS 0x0
//! Constant EN - Enable GMAC-Lite bypass
#define CONST_PM_PDI_CFG_GMACL_BYP_EN 0x1

//! Field MACSECE_BYP - MACsec Egress Bypass - Chip Static Configuration
#define PM_PDI_CFG_MACSECE_BYP_POS 2
//! Field MACSECE_BYP - MACsec Egress Bypass - Chip Static Configuration
#define PM_PDI_CFG_MACSECE_BYP_MASK 0x4u
//! Constant NOBYP - No MACsec Egress bypass
#define CONST_PM_PDI_CFG_MACSECE_BYP_NOBYP 0x0
//! Constant BYP - MACsec Egress is bypassed
#define CONST_PM_PDI_CFG_MACSECE_BYP_BYP 0x1

//! Field MACSECI_BYP - MACsec Ingress Bypass - Chip Static Configuration
#define PM_PDI_CFG_MACSECI_BYP_POS 3
//! Field MACSECI_BYP - MACsec Ingress Bypass - Chip Static Configuration
#define PM_PDI_CFG_MACSECI_BYP_MASK 0x8u
//! Constant NOBYP - No MACsec Ingress bypass
#define CONST_PM_PDI_CFG_MACSECI_BYP_NOBYP 0x0
//! Constant BYP - MACsec Ingress is bypassed
#define CONST_PM_PDI_CFG_MACSECI_BYP_BYP 0x1

//! Field MACSEC_RST - MACsec Reset
#define PM_PDI_CFG_MACSEC_RST_POS 4
//! Field MACSEC_RST - MACsec Reset
#define PM_PDI_CFG_MACSEC_RST_MASK 0x10u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_MACSEC_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_MACSEC_RST_ON 0x1

//! Field CRC_ERR - Drop packet on CRC error
#define PM_PDI_CFG_CRC_ERR_POS 5
//! Field CRC_ERR - Drop packet on CRC error
#define PM_PDI_CFG_CRC_ERR_MASK 0x20u
//! Constant DISABLE - Keep Packet
#define CONST_PM_PDI_CFG_CRC_ERR_DISABLE 0x0
//! Constant ENABLE - Discard packet
#define CONST_PM_PDI_CFG_CRC_ERR_ENABLE 0x1

//! Field PKT_ERR - Drop packet on PKT error
#define PM_PDI_CFG_PKT_ERR_POS 6
//! Field PKT_ERR - Drop packet on PKT error
#define PM_PDI_CFG_PKT_ERR_MASK 0x40u
//! Constant DISABLE - Keep Packet
#define CONST_PM_PDI_CFG_PKT_ERR_DISABLE 0x0
//! Constant ENABLE - Discard Packet
#define CONST_PM_PDI_CFG_PKT_ERR_ENABLE 0x1

//! Field SEC_FAIL - Drop packet on Security Fail
#define PM_PDI_CFG_SEC_FAIL_POS 7
//! Field SEC_FAIL - Drop packet on Security Fail
#define PM_PDI_CFG_SEC_FAIL_MASK 0x80u
//! Constant DISABLE - Keep Packet
#define CONST_PM_PDI_CFG_SEC_FAIL_DISABLE 0x0
//! Constant ENABLE - Discard Packet
#define CONST_PM_PDI_CFG_SEC_FAIL_ENABLE 0x1

//! Field CLASS_DROP - Drop packet on Classification Drop
#define PM_PDI_CFG_CLASS_DROP_POS 8
//! Field CLASS_DROP - Drop packet on Classification Drop
#define PM_PDI_CFG_CLASS_DROP_MASK 0x100u
//! Constant DISABLE - Keep Packet
#define CONST_PM_PDI_CFG_CLASS_DROP_DISABLE 0x0
//! Constant ENABLE - Discard Packet
#define CONST_PM_PDI_CFG_CLASS_DROP_ENABLE 0x1

//! Field CUST_3G - GMAC lite is in custom 3G overclocked mode
#define PM_PDI_CFG_CUST_3G_POS 9
//! Field CUST_3G - GMAC lite is in custom 3G overclocked mode
#define PM_PDI_CFG_CUST_3G_MASK 0x200u
//! Constant OFF - Custom 3G Speed is OFF
#define CONST_PM_PDI_CFG_CUST_3G_OFF 0x0
//! Constant ON - Custom 3G Speed is ON
#define CONST_PM_PDI_CFG_CUST_3G_ON 0x1

//! Field SGMII_LOOP - SGMII Loopback mode
#define PM_PDI_CFG_SGMII_LOOP_POS 10
//! Field SGMII_LOOP - SGMII Loopback mode
#define PM_PDI_CFG_SGMII_LOOP_MASK 0x400u
//! Constant DISABLE - SGMII Loop is not active
#define CONST_PM_PDI_CFG_SGMII_LOOP_DISABLE 0x0
//! Constant ENABLE - SGMII Loop is active
#define CONST_PM_PDI_CFG_SGMII_LOOP_ENABLE 0x1

//! Field RST - Packet Manager Internal Reset
#define PM_PDI_CFG_PM_RST_POS 11
//! Field RST - Packet Manager Internal Reset
#define PM_PDI_CFG_PM_RST_MASK 0x800u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_RST_ON 0x1

//! Field SB0_EQ_RST - Shared Buffer 0 EQ Hardware Reset
#define PM_PDI_CFG_SB0_EQ_RST_POS 12
//! Field SB0_EQ_RST - Shared Buffer 0 EQ Hardware Reset
#define PM_PDI_CFG_SB0_EQ_RST_MASK 0x1000u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_SB0_EQ_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_SB0_EQ_RST_ON 0x1

//! Field SB0_DQ_RST - Shared Buffer 0 DQ Hardware Reset
#define PM_PDI_CFG_SB0_DQ_RST_POS 13
//! Field SB0_DQ_RST - Shared Buffer 0 DQ Hardware Reset
#define PM_PDI_CFG_SB0_DQ_RST_MASK 0x2000u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_SB0_DQ_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_SB0_DQ_RST_ON 0x1

//! Field SB1_EQ_RST - Shared Buffer 1 EQ Hardware Reset
#define PM_PDI_CFG_SB1_EQ_RST_POS 14
//! Field SB1_EQ_RST - Shared Buffer 1 EQ Hardware Reset
#define PM_PDI_CFG_SB1_EQ_RST_MASK 0x4000u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_SB1_EQ_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_SB1_EQ_RST_ON 0x1

//! Field SB1_DQ_RST - Shared Buffer 1 DQ Hardware Reset
#define PM_PDI_CFG_SB1_DQ_RST_POS 15
//! Field SB1_DQ_RST - Shared Buffer 1 DQ Hardware Reset
#define PM_PDI_CFG_SB1_DQ_RST_MASK 0x8000u
//! Constant OFF - reset is off
#define CONST_PM_PDI_CFG_SB1_DQ_RST_OFF 0x0
//! Constant ON - reset is active
#define CONST_PM_PDI_CFG_SB1_DQ_RST_ON 0x1

//! @}

//! \defgroup PM_PDI_GMAC_CFG Register PM_PDI_GMAC_CFG - PM GMAC Configuration Register
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_CFG 0x4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_CFG 0x00D38004u

//! Register Reset Value
#define PM_PDI_GMAC_CFG_RST 0x00000000u

//! Field GMAC_CRC_PAD - GMAC CRC and Pad Control
#define PM_PDI_GMAC_CFG_GMAC_CRC_PAD_POS 0
//! Field GMAC_CRC_PAD - GMAC CRC and Pad Control
#define PM_PDI_GMAC_CFG_GMAC_CRC_PAD_MASK 0x3u
//! Constant MODE0 - CRC and Pad Insertion
#define CONST_PM_PDI_GMAC_CFG_GMAC_CRC_PAD_MODE0 0x0
//! Constant MODE1 - CRC Insertion and disable Pad insertion
#define CONST_PM_PDI_GMAC_CFG_GMAC_CRC_PAD_MODE1 0x1
//! Constant MODE2 - Disable CRC and Pad Insertion
#define CONST_PM_PDI_GMAC_CFG_GMAC_CRC_PAD_MODE2 0x2
//! Constant MODE3 - CRC Replacement and disable padding
#define CONST_PM_PDI_GMAC_CFG_GMAC_CRC_PAD_MODE3 0x3

//! Field GMAC_ERR - GMAC Transmit Error Input
#define PM_PDI_GMAC_CFG_GMAC_ERR_POS 2
//! Field GMAC_ERR - GMAC Transmit Error Input
#define PM_PDI_GMAC_CFG_GMAC_ERR_MASK 0x4u
//! Constant MODE0 - Normal operation
#define CONST_PM_PDI_GMAC_CFG_GMAC_ERR_MODE0 0x0
//! Constant MODE1 - Force CRC error
#define CONST_PM_PDI_GMAC_CFG_GMAC_ERR_MODE1 0x1

//! Field GMAC_FLW_CTRL - GMAC Transmit Flow Control
#define PM_PDI_GMAC_CFG_GMAC_FLW_CTRL_POS 3
//! Field GMAC_FLW_CTRL - GMAC Transmit Flow Control
#define PM_PDI_GMAC_CFG_GMAC_FLW_CTRL_MASK 0x8u
//! Constant DIS - No flow control
#define CONST_PM_PDI_GMAC_CFG_GMAC_FLW_CTRL_DIS 0x0
//! Constant EN - Flow control enable
#define CONST_PM_PDI_GMAC_CFG_GMAC_FLW_CTRL_EN 0x1

//! Field GMAC_ENDIAN - Data Endianness
#define PM_PDI_GMAC_CFG_GMAC_ENDIAN_POS 4
//! Field GMAC_ENDIAN - Data Endianness
#define PM_PDI_GMAC_CFG_GMAC_ENDIAN_MASK 0x10u
//! Constant LITTLE - Little Endian
#define CONST_PM_PDI_GMAC_CFG_GMAC_ENDIAN_LITTLE 0x0
//! Constant BIG - Big Endian
#define CONST_PM_PDI_GMAC_CFG_GMAC_ENDIAN_BIG 0x1

//! Field GMAC_PTP_DET - PTP Packet Detection
#define PM_PDI_GMAC_CFG_GMAC_PTP_DET_POS 5
//! Field GMAC_PTP_DET - PTP Packet Detection
#define PM_PDI_GMAC_CFG_GMAC_PTP_DET_MASK 0x20u
//! Constant DIS - Disable PTP packet detection
#define CONST_PM_PDI_GMAC_CFG_GMAC_PTP_DET_DIS 0x0
//! Constant EN - Enable PTP packet detection
#define CONST_PM_PDI_GMAC_CFG_GMAC_PTP_DET_EN 0x1

//! @}

//! \defgroup PM_PDI_GMACL_CFG Register PM_PDI_GMACL_CFG - PM GMAC-Lite Configuration Register
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_CFG 0x8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_CFG 0x00D38008u

//! Register Reset Value
#define PM_PDI_GMACL_CFG_RST 0x00000020u

//! Field GMACL_CRC_PAD - GMAC-Lite CRC and Pad Control
#define PM_PDI_GMACL_CFG_GMACL_CRC_PAD_POS 0
//! Field GMACL_CRC_PAD - GMAC-Lite CRC and Pad Control
#define PM_PDI_GMACL_CFG_GMACL_CRC_PAD_MASK 0x3u
//! Constant MODE0 - CRC and Pad Insertion
#define CONST_PM_PDI_GMACL_CFG_GMACL_CRC_PAD_MODE0 0x0
//! Constant MODE1 - CRC Insertion and disable Pad insertion
#define CONST_PM_PDI_GMACL_CFG_GMACL_CRC_PAD_MODE1 0x1
//! Constant MODE2 - Disable CRC and Pad Insertion
#define CONST_PM_PDI_GMACL_CFG_GMACL_CRC_PAD_MODE2 0x2
//! Constant MODE3 - CRC Replacement and disable padding
#define CONST_PM_PDI_GMACL_CFG_GMACL_CRC_PAD_MODE3 0x3

//! Field GMACL_ERR - GMAC-Lite Transmit Error Input
#define PM_PDI_GMACL_CFG_GMACL_ERR_POS 2
//! Field GMACL_ERR - GMAC-Lite Transmit Error Input
#define PM_PDI_GMACL_CFG_GMACL_ERR_MASK 0x4u
//! Constant MODE0 - Normal operation
#define CONST_PM_PDI_GMACL_CFG_GMACL_ERR_MODE0 0x0
//! Constant MODE1 - Force CRC error
#define CONST_PM_PDI_GMACL_CFG_GMACL_ERR_MODE1 0x1

//! Field GMACL_FLW_CTRL - GMAC-Lite Transmit Flow Control
#define PM_PDI_GMACL_CFG_GMACL_FLW_CTRL_POS 3
//! Field GMACL_FLW_CTRL - GMAC-Lite Transmit Flow Control
#define PM_PDI_GMACL_CFG_GMACL_FLW_CTRL_MASK 0x8u
//! Constant DIS - No flow control
#define CONST_PM_PDI_GMACL_CFG_GMACL_FLW_CTRL_DIS 0x0
//! Constant EN - Flow control enable
#define CONST_PM_PDI_GMACL_CFG_GMACL_FLW_CTRL_EN 0x1

//! Field GMACL_ENDIAN - Data Endianness
#define PM_PDI_GMACL_CFG_GMACL_ENDIAN_POS 4
//! Field GMACL_ENDIAN - Data Endianness
#define PM_PDI_GMACL_CFG_GMACL_ENDIAN_MASK 0x10u
//! Constant LITTLE - Little Endian
#define CONST_PM_PDI_GMACL_CFG_GMACL_ENDIAN_LITTLE 0x0
//! Constant BIG - Big Endian
#define CONST_PM_PDI_GMACL_CFG_GMACL_ENDIAN_BIG 0x1

//! Field GMACL_PTP_DET - PTP Packet Detection
#define PM_PDI_GMACL_CFG_GMACL_PTP_DET_POS 5
//! Field GMACL_PTP_DET - PTP Packet Detection
#define PM_PDI_GMACL_CFG_GMACL_PTP_DET_MASK 0x20u
//! Constant DIS - Disable PTP packet detection
#define CONST_PM_PDI_GMACL_CFG_GMACL_PTP_DET_DIS 0x0
//! Constant EN - Enable PTP packet detection
#define CONST_PM_PDI_GMACL_CFG_GMACL_PTP_DET_EN 0x1

//! Field PM_PEN - PCH_EN mode Enabling of PM
#define PM_PDI_XGMAC_CFG_PM_PEN_POS 6
//! Field PM_PEN - PCH_EN mode Enabling of PM
#define PM_PDI_XGMAC_CFG_PM_PEN_MASK 0x40u
//! Constant DISABLE - PCH mode is disabled
#define CONST_PM_PDI_XGMAC_CFG_PM_PEN_DISABLE 0x0
//! Constant ENABLE - PCH mode is enabled
#define CONST_PM_PDI_XGMAC_CFG_PM_PEN_ENABLE 0x1

//! @}

//! \defgroup PM_PDI_GMAC_TXSTAT_0 Register PM_PDI_GMAC_TXSTAT_0 - PM Status of the GMAC TX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TXSTAT_0 0xC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TXSTAT_0 0x00D3800Cu

//! Register Reset Value
#define PM_PDI_GMAC_TXSTAT_0_RST 0x00000000u

//! Field TXSTAT - Status of GMAC Tx
#define PM_PDI_GMAC_TXSTAT_0_TXSTAT_POS 0
//! Field TXSTAT - Status of GMAC Tx
#define PM_PDI_GMAC_TXSTAT_0_TXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TXSTAT_1 Register PM_PDI_GMAC_TXSTAT_1 - PM Status of the GMAC TX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TXSTAT_1 0x10
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TXSTAT_1 0x00D38010u

//! Register Reset Value
#define PM_PDI_GMAC_TXSTAT_1_RST 0x00000000u

//! Field TXSTAT - Status of GMAC Tx
#define PM_PDI_GMAC_TXSTAT_1_TXSTAT_POS 0
//! Field TXSTAT - Status of GMAC Tx
#define PM_PDI_GMAC_TXSTAT_1_TXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_0 Register PM_PDI_GMAC_RXSTAT_0 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_0 0x14
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_0 0x00D38014u

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_0_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_0_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_0_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_1 Register PM_PDI_GMAC_RXSTAT_1 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_1 0x18
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_1 0x00D38018u

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_1_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_1_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_1_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_2 Register PM_PDI_GMAC_RXSTAT_2 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_2 0x1C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_2 0x00D3801Cu

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_2_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_2_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_2_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_3 Register PM_PDI_GMAC_RXSTAT_3 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_3 0x20
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_3 0x00D38020u

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_3_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_3_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_3_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_4 Register PM_PDI_GMAC_RXSTAT_4 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_4 0x24
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_4 0x00D38024u

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_4_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_4_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_4_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_5 Register PM_PDI_GMAC_RXSTAT_5 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_5 0x28
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_5 0x00D38028u

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_5_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_5_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_5_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RXSTAT_6 Register PM_PDI_GMAC_RXSTAT_6 - PM Status of the GMAC RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RXSTAT_6 0x2C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RXSTAT_6 0x00D3802Cu

//! Register Reset Value
#define PM_PDI_GMAC_RXSTAT_6_RST 0x00000000u

//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_6_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC Rx
#define PM_PDI_GMAC_RXSTAT_6_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TXSTAT_0 Register PM_PDI_GMACL_TXSTAT_0 - PM Status of the GMAC-Lite TX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TXSTAT_0 0x30
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TXSTAT_0 0x00D38030u

//! Register Reset Value
#define PM_PDI_GMACL_TXSTAT_0_RST 0x00000000u

//! Field TXSTAT - Status of GMAC-Lite Tx
#define PM_PDI_GMACL_TXSTAT_0_TXSTAT_POS 0
//! Field TXSTAT - Status of GMAC-Lite Tx
#define PM_PDI_GMACL_TXSTAT_0_TXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TXSTAT_1 Register PM_PDI_GMACL_TXSTAT_1 - PM Status of the GMAC-Lite TX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TXSTAT_1 0x34
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TXSTAT_1 0x00D38034u

//! Register Reset Value
#define PM_PDI_GMACL_TXSTAT_1_RST 0x00000000u

//! Field TXSTAT - Status of GMAC-Lite Tx
#define PM_PDI_GMACL_TXSTAT_1_TXSTAT_POS 0
//! Field TXSTAT - Status of GMAC-Lite Tx
#define PM_PDI_GMACL_TXSTAT_1_TXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_0 Register PM_PDI_GMACL_RXSTAT_0 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_0 0x38
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_0 0x00D38038u

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_0_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_0_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_0_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_1 Register PM_PDI_GMACL_RXSTAT_1 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_1 0x3C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_1 0x00D3803Cu

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_1_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_1_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_1_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_2 Register PM_PDI_GMACL_RXSTAT_2 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_2 0x40
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_2 0x00D38040u

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_2_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_2_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_2_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_3 Register PM_PDI_GMACL_RXSTAT_3 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_3 0x44
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_3 0x00D38044u

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_3_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_3_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_3_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_4 Register PM_PDI_GMACL_RXSTAT_4 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_4 0x48
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_4 0x00D38048u

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_4_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_4_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_4_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_5 Register PM_PDI_GMACL_RXSTAT_5 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_5 0x4C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_5 0x00D3804Cu

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_5_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_5_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_5_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RXSTAT_6 Register PM_PDI_GMACL_RXSTAT_6 - PM Status of the GMAC-Lite RX
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RXSTAT_6 0x50
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RXSTAT_6 0x00D38050u

//! Register Reset Value
#define PM_PDI_GMACL_RXSTAT_6_RST 0x00000000u

//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_6_RXSTAT_POS 0
//! Field RXSTAT - Status of GMAC-Lite Rx
#define PM_PDI_GMACL_RXSTAT_6_RXSTAT_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_LPI_STAT Register PM_PDI_LPI_STAT - PM GMAC LPI Status Register
//! @{

//! Register Offset (relative)
#define PM_PDI_LPI_STAT 0x54
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_LPI_STAT 0x00D38054u

//! Register Reset Value
#define PM_PDI_LPI_STAT_RST 0x00000000u

//! Field GMAC_LPI - GMAC LPI Status
#define PM_PDI_LPI_STAT_GMAC_LPI_POS 0
//! Field GMAC_LPI - GMAC LPI Status
#define PM_PDI_LPI_STAT_GMAC_LPI_MASK 0x1u

//! Field GMACL_LPI - GMAC-Lite LPI Status
#define PM_PDI_LPI_STAT_GMACL_LPI_POS 1
//! Field GMACL_LPI - GMAC-Lite LPI Status
#define PM_PDI_LPI_STAT_GMACL_LPI_MASK 0x2u

//! @}

//! \defgroup PM_PDI_TS_CFG Register PM_PDI_TS_CFG - PM configuration of GMAC Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_TS_CFG 0x58
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TS_CFG 0x00D38058u

//! Register Reset Value
#define PM_PDI_TS_CFG_RST 0x00000000u

//! Field TS_RESN - GMAC PTP Reference Clock Reset
#define PM_PDI_TS_CFG_TS_RESN_POS 0
//! Field TS_RESN - GMAC PTP Reference Clock Reset
#define PM_PDI_TS_CFG_TS_RESN_MASK 0x1u
//! Constant ON - reset is active
#define CONST_PM_PDI_TS_CFG_TS_RESN_ON 0x0
//! Constant OFF - reset is off
#define CONST_PM_PDI_TS_CFG_TS_RESN_OFF 0x1

//! Field TX_OST_EN - Transmit One-Step Time Correction Enable
#define PM_PDI_TS_CFG_TX_OST_EN_POS 1
//! Field TX_OST_EN - Transmit One-Step Time Correction Enable
#define PM_PDI_TS_CFG_TX_OST_EN_MASK 0x2u
//! Constant DIS - One-step time correction is off
#define CONST_PM_PDI_TS_CFG_TX_OST_EN_DIS 0x0
//! Constant EN - One-step time correction is active
#define CONST_PM_PDI_TS_CFG_TX_OST_EN_EN 0x1

//! Field TSL_RESN - GMAC-Lite PTP Reference Clock Reset
#define PM_PDI_TS_CFG_TSL_RESN_POS 2
//! Field TSL_RESN - GMAC-Lite PTP Reference Clock Reset
#define PM_PDI_TS_CFG_TSL_RESN_MASK 0x4u
//! Constant ON - reset is active
#define CONST_PM_PDI_TS_CFG_TSL_RESN_ON 0x0
//! Constant OFF - reset is off
#define CONST_PM_PDI_TS_CFG_TSL_RESN_OFF 0x1

//! Field TX_FIFO_EN - TX Timestamp FIFO Enable
#define PM_PDI_TS_CFG_TX_FIFO_EN_POS 4
//! Field TX_FIFO_EN - TX Timestamp FIFO Enable
#define PM_PDI_TS_CFG_TX_FIFO_EN_MASK 0x10u
//! Constant DIS - FIFO Disable
#define CONST_PM_PDI_TS_CFG_TX_FIFO_EN_DIS 0x0
//! Constant EN - FIFO Enable
#define CONST_PM_PDI_TS_CFG_TX_FIFO_EN_EN 0x1

//! Field RX_FIFO_EN - RX Timestamp FIFO Enable
#define PM_PDI_TS_CFG_RX_FIFO_EN_POS 5
//! Field RX_FIFO_EN - RX Timestamp FIFO Enable
#define PM_PDI_TS_CFG_RX_FIFO_EN_MASK 0x20u
//! Constant DIS - FIFO Disable
#define CONST_PM_PDI_TS_CFG_RX_FIFO_EN_DIS 0x0
//! Constant EN - FIFO Enable
#define CONST_PM_PDI_TS_CFG_RX_FIFO_EN_EN 0x1

//! Field TX_FIFO_RSTN - TX Timestamp FIFO Reset
#define PM_PDI_TS_CFG_TX_FIFO_RSTN_POS 6
//! Field TX_FIFO_RSTN - TX Timestamp FIFO Reset
#define PM_PDI_TS_CFG_TX_FIFO_RSTN_MASK 0x40u
//! Constant ON - reset is active
#define CONST_PM_PDI_TS_CFG_TX_FIFO_RSTN_ON 0x0
//! Constant OFF - reset is off
#define CONST_PM_PDI_TS_CFG_TX_FIFO_RSTN_OFF 0x1

//! Field RX_FIFO_RSTN - RX Timestamp FIFO Reset
#define PM_PDI_TS_CFG_RX_FIFO_RSTN_POS 7
//! Field RX_FIFO_RSTN - RX Timestamp FIFO Reset
#define PM_PDI_TS_CFG_RX_FIFO_RSTN_MASK 0x80u
//! Constant ON - reset is active
#define CONST_PM_PDI_TS_CFG_RX_FIFO_RSTN_ON 0x0
//! Constant OFF - reset is off
#define CONST_PM_PDI_TS_CFG_RX_FIFO_RSTN_OFF 0x1

//! Field PHY_TXTS - PHY TX Timestamp
#define PM_PDI_TS_CFG_PHY_TXTS_POS 8
//! Field PHY_TXTS - PHY TX Timestamp
#define PM_PDI_TS_CFG_PHY_TXTS_MASK 0x100u
//! Constant DIS - Disable Timestamping using PHY TX Frame Start Toggle
#define CONST_PM_PDI_TS_CFG_PHY_TXTS_DIS 0x0
//! Constant EN - Enable Timestamping using PHY TX Frame Start Toggle
#define CONST_PM_PDI_TS_CFG_PHY_TXTS_EN 0x1

//! Field PHY_RXTS - PHY RX Timestamp
#define PM_PDI_TS_CFG_PHY_RXTS_POS 9
//! Field PHY_RXTS - PHY RX Timestamp
#define PM_PDI_TS_CFG_PHY_RXTS_MASK 0x200u
//! Constant DIS - Disable Timestamping using PHY RX Frame Start Toggle
#define CONST_PM_PDI_TS_CFG_PHY_RXTS_DIS 0x0
//! Constant EN - Enable Timestamping using PHY RX Frame Start Toggle
#define CONST_PM_PDI_TS_CFG_PHY_RXTS_EN 0x1

//! @}

//! \defgroup PM_PDI_TS_FIFO_STAT Register PM_PDI_TS_FIFO_STAT - Status of Timestamp FIFO
//! @{

//! Register Offset (relative)
#define PM_PDI_TS_FIFO_STAT 0x5C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TS_FIFO_STAT 0x00D3805Cu

//! Register Reset Value
#define PM_PDI_TS_FIFO_STAT_RST 0x00000000u

//! Field TX_FILL_LVL - TX FIFO Fill Level
#define PM_PDI_TS_FIFO_STAT_TX_FILL_LVL_POS 0
//! Field TX_FILL_LVL - TX FIFO Fill Level
#define PM_PDI_TS_FIFO_STAT_TX_FILL_LVL_MASK 0x1Fu

//! Field TX_OVF - TX FIFO Overflow
#define PM_PDI_TS_FIFO_STAT_TX_OVF_POS 6
//! Field TX_OVF - TX FIFO Overflow
#define PM_PDI_TS_FIFO_STAT_TX_OVF_MASK 0x40u
//! Constant NONE - No overflow
#define CONST_PM_PDI_TS_FIFO_STAT_TX_OVF_NONE 0x0
//! Constant OVF - Overflow
#define CONST_PM_PDI_TS_FIFO_STAT_TX_OVF_OVF 0x1

//! Field TX_UDF - TX FIFO Underflow
#define PM_PDI_TS_FIFO_STAT_TX_UDF_POS 7
//! Field TX_UDF - TX FIFO Underflow
#define PM_PDI_TS_FIFO_STAT_TX_UDF_MASK 0x80u
//! Constant NONE - No underflow
#define CONST_PM_PDI_TS_FIFO_STAT_TX_UDF_NONE 0x0
//! Constant UDF - Underflow
#define CONST_PM_PDI_TS_FIFO_STAT_TX_UDF_UDF 0x1

//! Field RX_FILL_LVL - RX FIFO Fill Level
#define PM_PDI_TS_FIFO_STAT_RX_FILL_LVL_POS 8
//! Field RX_FILL_LVL - RX FIFO Fill Level
#define PM_PDI_TS_FIFO_STAT_RX_FILL_LVL_MASK 0x1F00u

//! Field RX_OVF - RX FIFO Overflow
#define PM_PDI_TS_FIFO_STAT_RX_OVF_POS 14
//! Field RX_OVF - RX FIFO Overflow
#define PM_PDI_TS_FIFO_STAT_RX_OVF_MASK 0x4000u
//! Constant NONE - No overflow
#define CONST_PM_PDI_TS_FIFO_STAT_RX_OVF_NONE 0x0
//! Constant OVF - Overflow
#define CONST_PM_PDI_TS_FIFO_STAT_RX_OVF_OVF 0x1

//! Field RX_UDF - RX FIFO Underflow
#define PM_PDI_TS_FIFO_STAT_RX_UDF_POS 15
//! Field RX_UDF - RX FIFO Underflow
#define PM_PDI_TS_FIFO_STAT_RX_UDF_MASK 0x8000u
//! Constant NONE - No underflow
#define CONST_PM_PDI_TS_FIFO_STAT_RX_UDF_NONE 0x0
//! Constant UDF - Underflow
#define CONST_PM_PDI_TS_FIFO_STAT_RX_UDF_UDF 0x1

//! @}

//! \defgroup PM_PDI_GMAC_PTP_CFG Register PM_PDI_GMAC_PTP_CFG - PM configuration of GMAC PTP
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_PTP_CFG 0x60
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_PTP_CFG 0x00D38060u

//! Register Reset Value
#define PM_PDI_GMAC_PTP_CFG_RST 0x00000000u

//! Field PTP_OFFSET - Transmit PTP Offset
#define PM_PDI_GMAC_PTP_CFG_PTP_OFFSET_POS 0
//! Field PTP_OFFSET - Transmit PTP Offset
#define PM_PDI_GMAC_PTP_CFG_PTP_OFFSET_MASK 0x3FFFu

//! Field PTP_TPT - Transmit PTP Transport Protocol Type
#define PM_PDI_GMAC_PTP_CFG_PTP_TPT_POS 14
//! Field PTP_TPT - Transmit PTP Transport Protocol Type
#define PM_PDI_GMAC_PTP_CFG_PTP_TPT_MASK 0xC000u
//! Constant ETHERNET - PTP over Ethernet
#define CONST_PM_PDI_GMAC_PTP_CFG_PTP_TPT_ETHERNET 0x1
//! Constant IPV4 - PTP over UDP/IPv4
#define CONST_PM_PDI_GMAC_PTP_CFG_PTP_TPT_IPV4 0x2
//! Constant IPV6 - PTP over UDP/IPv6
#define CONST_PM_PDI_GMAC_PTP_CFG_PTP_TPT_IPV6 0x3

//! @}

//! \defgroup PM_PDI_SPARE Register PM_PDI_SPARE - Spare Register
//! @{

//! Register Offset (relative)
#define PM_PDI_SPARE 0x64
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SPARE 0x00D38064u

//! Register Reset Value
#define PM_PDI_SPARE_RST 0x00000000u

//! Field SPARE - Spare
#define PM_PDI_SPARE_SPARE_POS 0
//! Field SPARE - Spare
#define PM_PDI_SPARE_SPARE_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_TS_STAT_0 Register PM_PDI_GMAC_TX_TS_STAT_0 - PM GMAC Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_TS_STAT_0 0x68
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_TS_STAT_0 0x00D38068u

//! Register Reset Value
#define PM_PDI_GMAC_TX_TS_STAT_0_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_0_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_0_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_TS_STAT_1 Register PM_PDI_GMAC_TX_TS_STAT_1 - PM GMAC Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_TS_STAT_1 0x6C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_TS_STAT_1 0x00D3806Cu

//! Register Reset Value
#define PM_PDI_GMAC_TX_TS_STAT_1_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_1_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_1_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_TS_STAT_2 Register PM_PDI_GMAC_TX_TS_STAT_2 - PM GMAC Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_TS_STAT_2 0x70
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_TS_STAT_2 0x00D38070u

//! Register Reset Value
#define PM_PDI_GMAC_TX_TS_STAT_2_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_2_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_2_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_TS_STAT_3 Register PM_PDI_GMAC_TX_TS_STAT_3 - PM GMAC Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_TS_STAT_3 0x74
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_TS_STAT_3 0x00D38074u

//! Register Reset Value
#define PM_PDI_GMAC_TX_TS_STAT_3_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_3_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMAC_TX_TS_STAT_3_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_CRC_STAT_0 Register PM_PDI_GMAC_TX_CRC_STAT_0 - PM GMAC Tx PTP Frame CRC0
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_CRC_STAT_0 0x78
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_CRC_STAT_0 0x00D38078u

//! Register Reset Value
#define PM_PDI_GMAC_TX_CRC_STAT_0_RST 0x00000000u

//! Field CRC_L - Frame CRC Low
#define PM_PDI_GMAC_TX_CRC_STAT_0_CRC_L_POS 0
//! Field CRC_L - Frame CRC Low
#define PM_PDI_GMAC_TX_CRC_STAT_0_CRC_L_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_TX_CRC_STAT_1 Register PM_PDI_GMAC_TX_CRC_STAT_1 - PM GMAC Tx PTP Frame CRC1
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_TX_CRC_STAT_1 0x7C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_TX_CRC_STAT_1 0x00D3807Cu

//! Register Reset Value
#define PM_PDI_GMAC_TX_CRC_STAT_1_RST 0x00000000u

//! Field CRC_U - Frame CRC Upper
#define PM_PDI_GMAC_TX_CRC_STAT_1_CRC_U_POS 0
//! Field CRC_U - Frame CRC Upper
#define PM_PDI_GMAC_TX_CRC_STAT_1_CRC_U_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TX_TS_STAT_0 Register PM_PDI_GMACL_TX_TS_STAT_0 - PM GMAC-Lite Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TX_TS_STAT_0 0x80
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TX_TS_STAT_0 0x00D38080u

//! Register Reset Value
#define PM_PDI_GMACL_TX_TS_STAT_0_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_0_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_0_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TX_TS_STAT_1 Register PM_PDI_GMACL_TX_TS_STAT_1 - PM GMAC-Lite Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TX_TS_STAT_1 0x84
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TX_TS_STAT_1 0x00D38084u

//! Register Reset Value
#define PM_PDI_GMACL_TX_TS_STAT_1_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_1_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_1_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TX_TS_STAT_2 Register PM_PDI_GMACL_TX_TS_STAT_2 - PM GMAC-Lite Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TX_TS_STAT_2 0x88
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TX_TS_STAT_2 0x00D38088u

//! Register Reset Value
#define PM_PDI_GMACL_TX_TS_STAT_2_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_2_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_2_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_TX_TS_STAT_3 Register PM_PDI_GMACL_TX_TS_STAT_3 - PM GMAC-Lite Transmit Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_TX_TS_STAT_3 0x8C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_TX_TS_STAT_3 0x00D3808Cu

//! Register Reset Value
#define PM_PDI_GMACL_TX_TS_STAT_3_RST 0x00000000u

//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_3_MTI_TS_POS 0
//! Field MTI_TS - Transmit Frame Timestamping
#define PM_PDI_GMACL_TX_TS_STAT_3_MTI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_TS_STAT_0 Register PM_PDI_GMAC_RX_TS_STAT_0 - PM GMAC Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_TS_STAT_0 0x90
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_TS_STAT_0 0x00D38090u

//! Register Reset Value
#define PM_PDI_GMAC_RX_TS_STAT_0_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_0_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_0_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_TS_STAT_1 Register PM_PDI_GMAC_RX_TS_STAT_1 - PM GMAC Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_TS_STAT_1 0x94
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_TS_STAT_1 0x00D38094u

//! Register Reset Value
#define PM_PDI_GMAC_RX_TS_STAT_1_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_1_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_1_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_TS_STAT_2 Register PM_PDI_GMAC_RX_TS_STAT_2 - PM GMAC Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_TS_STAT_2 0x98
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_TS_STAT_2 0x00D38098u

//! Register Reset Value
#define PM_PDI_GMAC_RX_TS_STAT_2_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_2_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_2_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_TS_STAT_3 Register PM_PDI_GMAC_RX_TS_STAT_3 - PM GMAC Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_TS_STAT_3 0x9C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_TS_STAT_3 0x00D3809Cu

//! Register Reset Value
#define PM_PDI_GMAC_RX_TS_STAT_3_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_3_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMAC_RX_TS_STAT_3_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_CRC_STAT_0 Register PM_PDI_GMAC_RX_CRC_STAT_0 - PM GMAC Rx PTP Frame CRC0
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_CRC_STAT_0 0xA0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_CRC_STAT_0 0x00D380A0u

//! Register Reset Value
#define PM_PDI_GMAC_RX_CRC_STAT_0_RST 0x00000000u

//! Field CRC_L - Frame CRC Low
#define PM_PDI_GMAC_RX_CRC_STAT_0_CRC_L_POS 0
//! Field CRC_L - Frame CRC Low
#define PM_PDI_GMAC_RX_CRC_STAT_0_CRC_L_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_RX_CRC_STAT_1 Register PM_PDI_GMAC_RX_CRC_STAT_1 - PM GMAC Rx PTP Frame CRC1
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_RX_CRC_STAT_1 0xA4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_RX_CRC_STAT_1 0x00D380A4u

//! Register Reset Value
#define PM_PDI_GMAC_RX_CRC_STAT_1_RST 0x00000000u

//! Field CRC_U - Frame CRC Upper
#define PM_PDI_GMAC_RX_CRC_STAT_1_CRC_U_POS 0
//! Field CRC_U - Frame CRC Upper
#define PM_PDI_GMAC_RX_CRC_STAT_1_CRC_U_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RX_TS_STAT_0 Register PM_PDI_GMACL_RX_TS_STAT_0 - PM GMAC-Lite Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RX_TS_STAT_0 0xA8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RX_TS_STAT_0 0x00D380A8u

//! Register Reset Value
#define PM_PDI_GMACL_RX_TS_STAT_0_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_0_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_0_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RX_TS_STAT_1 Register PM_PDI_GMACL_RX_TS_STAT_1 - PM GMAC-Lite Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RX_TS_STAT_1 0xAC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RX_TS_STAT_1 0x00D380ACu

//! Register Reset Value
#define PM_PDI_GMACL_RX_TS_STAT_1_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_1_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_1_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RX_TS_STAT_2 Register PM_PDI_GMACL_RX_TS_STAT_2 - PM GMAC-Lite Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RX_TS_STAT_2 0xB0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RX_TS_STAT_2 0x00D380B0u

//! Register Reset Value
#define PM_PDI_GMACL_RX_TS_STAT_2_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_2_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_2_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_RX_TS_STAT_3 Register PM_PDI_GMACL_RX_TS_STAT_3 - PM GMAC-Lite Receive Frame Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_RX_TS_STAT_3 0xB4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_RX_TS_STAT_3 0x00D380B4u

//! Register Reset Value
#define PM_PDI_GMACL_RX_TS_STAT_3_RST 0x00000000u

//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_3_MRI_TS_POS 0
//! Field MRI_TS - Receive Timestamp Value
#define PM_PDI_GMACL_RX_TS_STAT_3_MRI_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_TX_OST_CFG_0 Register PM_PDI_TX_OST_CFG_0 - PM GMAC Transmit One-Step Time Correction
//! @{

//! Register Offset (relative)
#define PM_PDI_TX_OST_CFG_0 0xB8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TX_OST_CFG_0 0x00D380B8u

//! Register Reset Value
#define PM_PDI_TX_OST_CFG_0_RST 0x00000000u

//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_0_MTI_OST_POS 0
//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_0_MTI_OST_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_TX_OST_CFG_1 Register PM_PDI_TX_OST_CFG_1 - PM GMAC Transmit One-Step Time Correction
//! @{

//! Register Offset (relative)
#define PM_PDI_TX_OST_CFG_1 0xBC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TX_OST_CFG_1 0x00D380BCu

//! Register Reset Value
#define PM_PDI_TX_OST_CFG_1_RST 0x00000000u

//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_1_MTI_OST_POS 0
//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_1_MTI_OST_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_TX_OST_CFG_2 Register PM_PDI_TX_OST_CFG_2 - PM GMAC Transmit One-Step Time Correction
//! @{

//! Register Offset (relative)
#define PM_PDI_TX_OST_CFG_2 0xC0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TX_OST_CFG_2 0x00D380C0u

//! Register Reset Value
#define PM_PDI_TX_OST_CFG_2_RST 0x00000000u

//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_2_MTI_OST_POS 0
//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_2_MTI_OST_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_TX_OST_CFG_3 Register PM_PDI_TX_OST_CFG_3 - PM GMAC Transmit One-Step Time Correction
//! @{

//! Register Offset (relative)
#define PM_PDI_TX_OST_CFG_3 0xC4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_TX_OST_CFG_3 0x00D380C4u

//! Register Reset Value
#define PM_PDI_TX_OST_CFG_3_RST 0x00000000u

//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_3_MTI_OST_POS 0
//! Field MTI_OST - Transmit One-Step Time Correction Input
#define PM_PDI_TX_OST_CFG_3_MTI_OST_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_PTP_TS_STAT_0 Register PM_PDI_GMAC_PTP_TS_STAT_0 - PM GMAC PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_PTP_TS_STAT_0 0xC8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_PTP_TS_STAT_0 0x00D380C8u

//! Register Reset Value
#define PM_PDI_GMAC_PTP_TS_STAT_0_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_0_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_0_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_PTP_TS_STAT_1 Register PM_PDI_GMAC_PTP_TS_STAT_1 - PM GMAC PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_PTP_TS_STAT_1 0xCC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_PTP_TS_STAT_1 0x00D380CCu

//! Register Reset Value
#define PM_PDI_GMAC_PTP_TS_STAT_1_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_1_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_1_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_PTP_TS_STAT_2 Register PM_PDI_GMAC_PTP_TS_STAT_2 - PM GMAC PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_PTP_TS_STAT_2 0xD0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_PTP_TS_STAT_2 0x00D380D0u

//! Register Reset Value
#define PM_PDI_GMAC_PTP_TS_STAT_2_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_2_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_2_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMAC_PTP_TS_STAT_3 Register PM_PDI_GMAC_PTP_TS_STAT_3 - PM GMAC PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMAC_PTP_TS_STAT_3 0xD4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMAC_PTP_TS_STAT_3 0x00D380D4u

//! Register Reset Value
#define PM_PDI_GMAC_PTP_TS_STAT_3_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_3_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMAC_PTP_TS_STAT_3_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_PTP_TS_STAT_0 Register PM_PDI_GMACL_PTP_TS_STAT_0 - PM GMAC-Lite PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_PTP_TS_STAT_0 0xD8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_PTP_TS_STAT_0 0x00D380D8u

//! Register Reset Value
#define PM_PDI_GMACL_PTP_TS_STAT_0_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_0_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_0_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_PTP_TS_STAT_1 Register PM_PDI_GMACL_PTP_TS_STAT_1 - PM GMAC-Lite PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_PTP_TS_STAT_1 0xDC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_PTP_TS_STAT_1 0x00D380DCu

//! Register Reset Value
#define PM_PDI_GMACL_PTP_TS_STAT_1_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_1_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_1_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_PTP_TS_STAT_2 Register PM_PDI_GMACL_PTP_TS_STAT_2 - PM GMAC-Lite PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_PTP_TS_STAT_2 0xE0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_PTP_TS_STAT_2 0x00D380E0u

//! Register Reset Value
#define PM_PDI_GMACL_PTP_TS_STAT_2_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_2_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_2_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_GMACL_PTP_TS_STAT_3 Register PM_PDI_GMACL_PTP_TS_STAT_3 - PM GMAC-Lite PTP Reference Timestamp
//! @{

//! Register Offset (relative)
#define PM_PDI_GMACL_PTP_TS_STAT_3 0xE4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_GMACL_PTP_TS_STAT_3 0x00D380E4u

//! Register Reset Value
#define PM_PDI_GMACL_PTP_TS_STAT_3_RST 0x00000000u

//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_3_PTP_TS_POS 0
//! Field PTP_TS - Reference Timestamp Output
#define PM_PDI_GMACL_PTP_TS_STAT_3_PTP_TS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_BM_STAT Register PM_PDI_BM_STAT - PM BM Status
//! @{

//! Register Offset (relative)
#define PM_PDI_BM_STAT 0xE8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_BM_STAT 0x00D380E8u

//! Register Reset Value
#define PM_PDI_BM_STAT_RST 0x00000000u

//! Field SB0_OV - Shared Buffer 0 Overflow Indicator
#define PM_PDI_BM_STAT_SB0_OV_POS 0
//! Field SB0_OV - Shared Buffer 0 Overflow Indicator
#define PM_PDI_BM_STAT_SB0_OV_MASK 0x1u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB0_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB0_OV_OFL 0x1

//! Field SB0_TX_REG_OV - Shared Buffer 0 Transmit Register Overflow Indicator
#define PM_PDI_BM_STAT_SB0_TX_REG_OV_POS 1
//! Field SB0_TX_REG_OV - Shared Buffer 0 Transmit Register Overflow Indicator
#define PM_PDI_BM_STAT_SB0_TX_REG_OV_MASK 0x2u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB0_TX_REG_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB0_TX_REG_OV_OFL 0x1

//! Field SB0_RX_REG_OV - Shared Buffer 0 Receive Register Overflow Indicator
#define PM_PDI_BM_STAT_SB0_RX_REG_OV_POS 2
//! Field SB0_RX_REG_OV - Shared Buffer 0 Receive Register Overflow Indicator
#define PM_PDI_BM_STAT_SB0_RX_REG_OV_MASK 0x4u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB0_RX_REG_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB0_RX_REG_OV_OFL 0x1

//! Field SB1_OV - Shared Buffer 1 Overflow Indicator
#define PM_PDI_BM_STAT_SB1_OV_POS 4
//! Field SB1_OV - Shared Buffer 1 Overflow Indicator
#define PM_PDI_BM_STAT_SB1_OV_MASK 0x10u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB1_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB1_OV_OFL 0x1

//! Field SB1_TX_REG_OV - Shared Buffer 1 Transmit Register Overflow Indicator
#define PM_PDI_BM_STAT_SB1_TX_REG_OV_POS 5
//! Field SB1_TX_REG_OV - Shared Buffer 1 Transmit Register Overflow Indicator
#define PM_PDI_BM_STAT_SB1_TX_REG_OV_MASK 0x20u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB1_TX_REG_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB1_TX_REG_OV_OFL 0x1

//! Field SB1_RX_REG_OV - Shared Buffer 1 Receive Register Overflow Indicator
#define PM_PDI_BM_STAT_SB1_RX_REG_OV_POS 6
//! Field SB1_RX_REG_OV - Shared Buffer 1 Receive Register Overflow Indicator
#define PM_PDI_BM_STAT_SB1_RX_REG_OV_MASK 0x40u
//! Constant NONE - Overflow never detected
#define CONST_PM_PDI_BM_STAT_SB1_RX_REG_OV_NONE 0x0
//! Constant OFL - Overflow occurred at least once
#define CONST_PM_PDI_BM_STAT_SB1_RX_REG_OV_OFL 0x1

//! Field SB0_RETRY - Shared Buffer 0 Retry Indicator
#define PM_PDI_BM_STAT_SB0_RETRY_POS 8
//! Field SB0_RETRY - Shared Buffer 0 Retry Indicator
#define PM_PDI_BM_STAT_SB0_RETRY_MASK 0x100u
//! Constant NONE - No Retransmission
#define CONST_PM_PDI_BM_STAT_SB0_RETRY_NONE 0x0
//! Constant RETRY - Retransmission
#define CONST_PM_PDI_BM_STAT_SB0_RETRY_RETRY 0x1

//! Field SB0_SENT - Shared Buffer 0 Sent Indicator
#define PM_PDI_BM_STAT_SB0_SENT_POS 9
//! Field SB0_SENT - Shared Buffer 0 Sent Indicator
#define PM_PDI_BM_STAT_SB0_SENT_MASK 0x200u
//! Constant NONE - Current Frame Not Sent
#define CONST_PM_PDI_BM_STAT_SB0_SENT_NONE 0x0
//! Constant SENT - Current Frame Sent
#define CONST_PM_PDI_BM_STAT_SB0_SENT_SENT 0x1

//! Field SB1_RETRY - Shared Buffer 1 Retry Indicator
#define PM_PDI_BM_STAT_SB1_RETRY_POS 10
//! Field SB1_RETRY - Shared Buffer 1 Retry Indicator
#define PM_PDI_BM_STAT_SB1_RETRY_MASK 0x400u
//! Constant NONE - No Retransmission
#define CONST_PM_PDI_BM_STAT_SB1_RETRY_NONE 0x0
//! Constant RETRY - Retransmission
#define CONST_PM_PDI_BM_STAT_SB1_RETRY_RETRY 0x1

//! Field SB1_SENT - Shared Buffer 1 Sent Indicator
#define PM_PDI_BM_STAT_SB1_SENT_POS 11
//! Field SB1_SENT - Shared Buffer 1 Sent Indicator
#define PM_PDI_BM_STAT_SB1_SENT_MASK 0x800u
//! Constant NONE - Current Frame Not Sent
#define CONST_PM_PDI_BM_STAT_SB1_SENT_NONE 0x0
//! Constant SENT - Current Frame Sent
#define CONST_PM_PDI_BM_STAT_SB1_SENT_SENT 0x1

//! Field SB0_COMPLETE - Shared Buffer 0 Complete Indicator
#define PM_PDI_BM_STAT_SB0_COMPLETE_POS 12
//! Field SB0_COMPLETE - Shared Buffer 0 Complete Indicator
#define PM_PDI_BM_STAT_SB0_COMPLETE_MASK 0x1000u
//! Constant NONE - Not complete
#define CONST_PM_PDI_BM_STAT_SB0_COMPLETE_NONE 0x0
//! Constant COMPLETE - Complete
#define CONST_PM_PDI_BM_STAT_SB0_COMPLETE_COMPLETE 0x1

//! Field SB1_COMPLETE - Shared Buffer 1 Complete Indicator
#define PM_PDI_BM_STAT_SB1_COMPLETE_POS 13
//! Field SB1_COMPLETE - Shared Buffer 1 Complete Indicator
#define PM_PDI_BM_STAT_SB1_COMPLETE_MASK 0x2000u
//! Constant NONE - Not complete
#define CONST_PM_PDI_BM_STAT_SB1_COMPLETE_NONE 0x0
//! Constant COMPLETE - Complete
#define CONST_PM_PDI_BM_STAT_SB1_COMPLETE_COMPLETE 0x1

//! @}

//! \defgroup PM_PDI_SB0_START Register PM_PDI_SB0_START - PM Shared Buffer 0 Start
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_START 0xEC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_START 0x00D380ECu

//! Register Reset Value
#define PM_PDI_SB0_START_RST 0x00000000u

//! Field START - Shared Buffer Start
#define PM_PDI_SB0_START_START_POS 4
//! Field START - Shared Buffer Start
#define PM_PDI_SB0_START_START_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_START Register PM_PDI_SB1_START - PM Shared Buffer 1 Start
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_START 0xF0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_START 0x00D380F0u

//! Register Reset Value
#define PM_PDI_SB1_START_RST 0x00000000u

//! Field START - Shared Buffer Start
#define PM_PDI_SB1_START_START_POS 4
//! Field START - Shared Buffer Start
#define PM_PDI_SB1_START_START_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_END Register PM_PDI_SB0_END - PM Shared Buffer 0 End
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_END 0xF4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_END 0x00D380F4u

//! Register Reset Value
#define PM_PDI_SB0_END_RST 0x00000000u

//! Field END - Shared Buffer End
#define PM_PDI_SB0_END_END_POS 4
//! Field END - Shared Buffer End
#define PM_PDI_SB0_END_END_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_END Register PM_PDI_SB1_END - PM Shared Buffer 1 End
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_END 0xF8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_END 0x00D380F8u

//! Register Reset Value
#define PM_PDI_SB1_END_RST 0x00000000u

//! Field END - Shared Buffer End
#define PM_PDI_SB1_END_END_POS 4
//! Field END - Shared Buffer End
#define PM_PDI_SB1_END_END_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_WPTR Register PM_PDI_SB0_WPTR - PM shared buffer 0 write pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_WPTR 0xFC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_WPTR 0x00D380FCu

//! Register Reset Value
#define PM_PDI_SB0_WPTR_RST 0x00000000u

//! Field SB0_WPTR - Shared Buffer 0 Write Pointer
#define PM_PDI_SB0_WPTR_SB0_WPTR_POS 4
//! Field SB0_WPTR - Shared Buffer 0 Write Pointer
#define PM_PDI_SB0_WPTR_SB0_WPTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_RPTR Register PM_PDI_SB0_RPTR - PM shared buffer 0 read pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RPTR 0x100
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RPTR 0x00D38100u

//! Register Reset Value
#define PM_PDI_SB0_RPTR_RST 0x00000000u

//! Field SB0_RPTR - Shared Buffer 0 Read Pointer
#define PM_PDI_SB0_RPTR_SB0_RPTR_POS 4
//! Field SB0_RPTR - Shared Buffer 0 Read Pointer
#define PM_PDI_SB0_RPTR_SB0_RPTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_WPTR Register PM_PDI_SB1_WPTR - PM shared buffer 1 write pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_WPTR 0x104
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_WPTR 0x00D38104u

//! Register Reset Value
#define PM_PDI_SB1_WPTR_RST 0x00000000u

//! Field SB1_WPTR - Shared Buffer 1 Write Pointer
#define PM_PDI_SB1_WPTR_SB1_WPTR_POS 4
//! Field SB1_WPTR - Shared Buffer 1 Write Pointer
#define PM_PDI_SB1_WPTR_SB1_WPTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_RPTR Register PM_PDI_SB1_RPTR - PM shared buffer 1 read pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RPTR 0x108
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RPTR 0x00D38108u

//! Register Reset Value
#define PM_PDI_SB1_RPTR_RST 0x00000000u

//! Field SB1_RPTR - Shared Buffer 1 Read Pointer
#define PM_PDI_SB1_RPTR_SB1_RPTR_POS 4
//! Field SB1_RPTR - Shared Buffer 1 Read Pointer
#define PM_PDI_SB1_RPTR_SB1_RPTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_SOP_RPTR Register PM_PDI_SB0_SOP_RPTR - Shared Buffer 0 Start of Packet Read Pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_SOP_RPTR 0x10C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_SOP_RPTR 0x00D3810Cu

//! Register Reset Value
#define PM_PDI_SB0_SOP_RPTR_RST 0x00000000u

//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB0_SOP_RPTR_SOP_PTR_POS 4
//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB0_SOP_RPTR_SOP_PTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_SOP_RPTR Register PM_PDI_SB1_SOP_RPTR - Shared Buffer 1 Start of Packet Read Pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_SOP_RPTR 0x110
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_SOP_RPTR 0x00D38110u

//! Register Reset Value
#define PM_PDI_SB1_SOP_RPTR_RST 0x00000000u

//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB1_SOP_RPTR_SOP_PTR_POS 4
//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB1_SOP_RPTR_SOP_PTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_SOP_WPTR Register PM_PDI_SB0_SOP_WPTR - Shared Buffer 0 Start of Packet Write Pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_SOP_WPTR 0x114
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_SOP_WPTR 0x00D38114u

//! Register Reset Value
#define PM_PDI_SB0_SOP_WPTR_RST 0x00000000u

//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB0_SOP_WPTR_SOP_PTR_POS 4
//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB0_SOP_WPTR_SOP_PTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_SOP_WPTR Register PM_PDI_SB1_SOP_WPTR - Shared Buffer 1 Start of Packet Write Pointer
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_SOP_WPTR 0x118
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_SOP_WPTR 0x00D38118u

//! Register Reset Value
#define PM_PDI_SB1_SOP_WPTR_RST 0x00000000u

//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB1_SOP_WPTR_SOP_PTR_POS 4
//! Field SOP_PTR - Shared Buffer Start of Packet Pointer
#define PM_PDI_SB1_SOP_WPTR_SOP_PTR_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_PKT_THRES Register PM_PDI_SB0_PKT_THRES - Shared Buffer 0 Packet Threshold
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_PKT_THRES 0x11C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_PKT_THRES 0x00D3811Cu

//! Register Reset Value
#define PM_PDI_SB0_PKT_THRES_RST 0x00000080u

//! Field PKT_THRES - Packet Threshold
#define PM_PDI_SB0_PKT_THRES_PKT_THRES_POS 4
//! Field PKT_THRES - Packet Threshold
#define PM_PDI_SB0_PKT_THRES_PKT_THRES_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB1_PKT_THRES Register PM_PDI_SB1_PKT_THRES - Shared Buffer 1 Packet Threshold
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_PKT_THRES 0x120
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_PKT_THRES 0x00D38120u

//! Register Reset Value
#define PM_PDI_SB1_PKT_THRES_RST 0x00000080u

//! Field PKT_THRES - Packet Threshold
#define PM_PDI_SB1_PKT_THRES_PKT_THRES_POS 4
//! Field PKT_THRES - Packet Threshold
#define PM_PDI_SB1_PKT_THRES_PKT_THRES_MASK 0xFFF0u

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_0 Register PM_PDI_SB0_TXREG_DATA_0 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_0 0x124
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_0 0x00D38124u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_0_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_0_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_0_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_1 Register PM_PDI_SB0_TXREG_DATA_1 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_1 0x128
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_1 0x00D38128u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_1_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_1_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_1_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_2 Register PM_PDI_SB0_TXREG_DATA_2 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_2 0x12C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_2 0x00D3812Cu

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_2_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_2_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_2_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_3 Register PM_PDI_SB0_TXREG_DATA_3 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_3 0x130
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_3 0x00D38130u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_3_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_3_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_3_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_4 Register PM_PDI_SB0_TXREG_DATA_4 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_4 0x134
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_4 0x00D38134u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_4_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_4_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_4_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_5 Register PM_PDI_SB0_TXREG_DATA_5 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_5 0x138
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_5 0x00D38138u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_5_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_5_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_5_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_6 Register PM_PDI_SB0_TXREG_DATA_6 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_6 0x13C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_6 0x00D3813Cu

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_6_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_6_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_6_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_DATA_7 Register PM_PDI_SB0_TXREG_DATA_7 - PM shared buffer 0 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_DATA_7 0x140
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_DATA_7 0x00D38140u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_DATA_7_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_7_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_TXREG_DATA_7_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_TXREG_CTRL Register PM_PDI_SB0_TXREG_CTRL - PM shared buffer 0 Tx Register for MTI Control Information
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_TXREG_CTRL 0x144
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_TXREG_CTRL 0x00D38144u

//! Register Reset Value
#define PM_PDI_SB0_TXREG_CTRL_RST 0x00000000u

//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB0_TXREG_CTRL_BE_POS 0
//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB0_TXREG_CTRL_BE_MASK 0xFu

//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB0_TXREG_CTRL_EOP_POS 4
//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB0_TXREG_CTRL_EOP_MASK 0x10u

//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB0_TXREG_CTRL_SOP_POS 5
//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB0_TXREG_CTRL_SOP_MASK 0x20u

//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB0_TXREG_CTRL_TS_POS 6
//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB0_TXREG_CTRL_TS_MASK 0x40u

//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB0_TXREG_CTRL_C_POS 7
//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB0_TXREG_CTRL_C_MASK 0x80u

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_0 Register PM_PDI_SB1_TXREG_DATA_0 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_0 0x148
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_0 0x00D38148u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_0_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_0_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_0_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_1 Register PM_PDI_SB1_TXREG_DATA_1 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_1 0x14C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_1 0x00D3814Cu

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_1_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_1_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_1_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_2 Register PM_PDI_SB1_TXREG_DATA_2 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_2 0x150
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_2 0x00D38150u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_2_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_2_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_2_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_3 Register PM_PDI_SB1_TXREG_DATA_3 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_3 0x154
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_3 0x00D38154u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_3_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_3_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_3_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_4 Register PM_PDI_SB1_TXREG_DATA_4 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_4 0x158
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_4 0x00D38158u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_4_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_4_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_4_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_5 Register PM_PDI_SB1_TXREG_DATA_5 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_5 0x15C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_5 0x00D3815Cu

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_5_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_5_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_5_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_6 Register PM_PDI_SB1_TXREG_DATA_6 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_6 0x160
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_6 0x00D38160u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_6_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_6_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_6_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_DATA_7 Register PM_PDI_SB1_TXREG_DATA_7 - PM shared buffer 1 Tx Register for MTI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_DATA_7 0x164
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_DATA_7 0x00D38164u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_DATA_7_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_7_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_TXREG_DATA_7_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_TXREG_CTRL Register PM_PDI_SB1_TXREG_CTRL - PM shared buffer 1 Tx Register for MTI Control Information
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_TXREG_CTRL 0x168
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_TXREG_CTRL 0x00D38168u

//! Register Reset Value
#define PM_PDI_SB1_TXREG_CTRL_RST 0x00000000u

//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB1_TXREG_CTRL_BE_POS 0
//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB1_TXREG_CTRL_BE_MASK 0xFu

//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB1_TXREG_CTRL_EOP_POS 4
//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB1_TXREG_CTRL_EOP_MASK 0x10u

//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB1_TXREG_CTRL_SOP_POS 5
//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB1_TXREG_CTRL_SOP_MASK 0x20u

//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB1_TXREG_CTRL_TS_POS 6
//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB1_TXREG_CTRL_TS_MASK 0x40u

//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB1_TXREG_CTRL_C_POS 7
//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB1_TXREG_CTRL_C_MASK 0x80u

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_0 Register PM_PDI_SB0_RXREG_DATA_0 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_0 0x16C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_0 0x00D3816Cu

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_0_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_0_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_0_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_1 Register PM_PDI_SB0_RXREG_DATA_1 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_1 0x170
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_1 0x00D38170u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_1_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_1_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_1_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_2 Register PM_PDI_SB0_RXREG_DATA_2 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_2 0x174
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_2 0x00D38174u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_2_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_2_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_2_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_3 Register PM_PDI_SB0_RXREG_DATA_3 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_3 0x178
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_3 0x00D38178u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_3_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_3_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_3_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_4 Register PM_PDI_SB0_RXREG_DATA_4 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_4 0x17C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_4 0x00D3817Cu

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_4_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_4_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_4_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_5 Register PM_PDI_SB0_RXREG_DATA_5 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_5 0x180
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_5 0x00D38180u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_5_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_5_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_5_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_6 Register PM_PDI_SB0_RXREG_DATA_6 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_6 0x184
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_6 0x00D38184u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_6_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_6_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_6_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_DATA_7 Register PM_PDI_SB0_RXREG_DATA_7 - PM shared buffer 0 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_DATA_7 0x188
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_DATA_7 0x00D38188u

//! Register Reset Value
#define PM_PDI_SB0_RXREG_DATA_7_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_7_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB0_RXREG_DATA_7_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB0_RXREG_CTRL Register PM_PDI_SB0_RXREG_CTRL - PM shared buffer 0 Rx Register for MRI Control Information
//! @{

//! Register Offset (relative)
#define PM_PDI_SB0_RXREG_CTRL 0x18C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB0_RXREG_CTRL 0x00D3818Cu

//! Register Reset Value
#define PM_PDI_SB0_RXREG_CTRL_RST 0x00000000u

//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB0_RXREG_CTRL_BE_POS 0
//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB0_RXREG_CTRL_BE_MASK 0xFu

//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB0_RXREG_CTRL_EOP_POS 4
//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB0_RXREG_CTRL_EOP_MASK 0x10u

//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB0_RXREG_CTRL_SOP_POS 5
//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB0_RXREG_CTRL_SOP_MASK 0x20u

//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB0_RXREG_CTRL_TS_POS 6
//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB0_RXREG_CTRL_TS_MASK 0x40u

//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB0_RXREG_CTRL_C_POS 7
//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB0_RXREG_CTRL_C_MASK 0x80u

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_0 Register PM_PDI_SB1_RXREG_DATA_0 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_0 0x190
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_0 0x00D38190u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_0_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_0_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_0_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_1 Register PM_PDI_SB1_RXREG_DATA_1 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_1 0x194
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_1 0x00D38194u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_1_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_1_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_1_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_2 Register PM_PDI_SB1_RXREG_DATA_2 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_2 0x198
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_2 0x00D38198u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_2_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_2_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_2_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_3 Register PM_PDI_SB1_RXREG_DATA_3 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_3 0x19C
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_3 0x00D3819Cu

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_3_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_3_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_3_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_4 Register PM_PDI_SB1_RXREG_DATA_4 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_4 0x1A0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_4 0x00D381A0u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_4_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_4_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_4_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_5 Register PM_PDI_SB1_RXREG_DATA_5 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_5 0x1A4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_5 0x00D381A4u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_5_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_5_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_5_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_6 Register PM_PDI_SB1_RXREG_DATA_6 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_6 0x1A8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_6 0x00D381A8u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_6_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_6_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_6_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_DATA_7 Register PM_PDI_SB1_RXREG_DATA_7 - PM shared buffer 1 Rx Register for MRI Data
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_DATA_7 0x1AC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_DATA_7 0x00D381ACu

//! Register Reset Value
#define PM_PDI_SB1_RXREG_DATA_7_RST 0x00000000u

//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_7_DATA_POS 0
//! Field DATA - Shared Buffer Register for Data
#define PM_PDI_SB1_RXREG_DATA_7_DATA_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_SB1_RXREG_CTRL Register PM_PDI_SB1_RXREG_CTRL - PM shared buffer 1 Rx Register for MRI Control Information
//! @{

//! Register Offset (relative)
#define PM_PDI_SB1_RXREG_CTRL 0x1B0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_SB1_RXREG_CTRL 0x00D381B0u

//! Register Reset Value
#define PM_PDI_SB1_RXREG_CTRL_RST 0x00000000u

//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB1_RXREG_CTRL_BE_POS 0
//! Field BE - Shared Buffer Register BE Control Information
#define PM_PDI_SB1_RXREG_CTRL_BE_MASK 0xFu

//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB1_RXREG_CTRL_EOP_POS 4
//! Field EOP - Shared Buffer Register EOP Control Information
#define PM_PDI_SB1_RXREG_CTRL_EOP_MASK 0x10u

//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB1_RXREG_CTRL_SOP_POS 5
//! Field SOP - Shared Buffer Register SOP Control Information
#define PM_PDI_SB1_RXREG_CTRL_SOP_MASK 0x20u

//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB1_RXREG_CTRL_TS_POS 6
//! Field TS - Shared Buffer Register Timestamp Control Information
#define PM_PDI_SB1_RXREG_CTRL_TS_MASK 0x40u

//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB1_RXREG_CTRL_C_POS 7
//! Field C - Shared Buffer Register Complete Control Information
#define PM_PDI_SB1_RXREG_CTRL_C_MASK 0x80u

//! @}

//! \defgroup PM_PDI_PAUSE_THRES Register PM_PDI_PAUSE_THRES - Pause assertion threshold
//! @{

//! Register Offset (relative)
#define PM_PDI_PAUSE_THRES 0x1B4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PAUSE_THRES 0x00D381B4u

//! Register Reset Value
#define PM_PDI_PAUSE_THRES_RST 0x00000500u

//! Field PAUSE_THRES - Pause threshold
#define PM_PDI_PAUSE_THRES_PAUSE_THRES_POS 0
//! Field PAUSE_THRES - Pause threshold
#define PM_PDI_PAUSE_THRES_PAUSE_THRES_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PAUSE_DEASSERT_THRES Register PM_PDI_PAUSE_DEASSERT_THRES - Pause de-assertion threshold
//! @{

//! Register Offset (relative)
#define PM_PDI_PAUSE_DEASSERT_THRES 0x1B8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PAUSE_DEASSERT_THRES 0x00D381B8u

//! Register Reset Value
#define PM_PDI_PAUSE_DEASSERT_THRES_RST 0x00000560u

//! Field PAUSE_OFF_THRES - Pause de-assertion threshold
#define PM_PDI_PAUSE_DEASSERT_THRES_PAUSE_OFF_THRES_POS 0
//! Field PAUSE_OFF_THRES - Pause de-assertion threshold
#define PM_PDI_PAUSE_DEASSERT_THRES_PAUSE_OFF_THRES_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_CTRL Register PM_PDI_CTRL - Packet Manager Indirect Access Control Register
//! @{

//! Register Offset (relative)
#define PM_PDI_CTRL 0x1BC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_CTRL 0x00D381BCu

//! Register Reset Value
#define PM_PDI_CTRL_RST 0x00000000u

//! Field REN - Read Enable
#define PM_PDI_CTRL_REN_POS 0
//! Field REN - Read Enable
#define PM_PDI_CTRL_REN_MASK 0x1u
//! Constant DIS - Read Disable
#define CONST_PM_PDI_CTRL_REN_DIS 0x0
//! Constant EN - Read Enable
#define CONST_PM_PDI_CTRL_REN_EN 0x1

//! Field WEN - Write Enable
#define PM_PDI_CTRL_WEN_POS 1
//! Field WEN - Write Enable
#define PM_PDI_CTRL_WEN_MASK 0x2u
//! Constant DIS - Write Disable
#define CONST_PM_PDI_CTRL_WEN_DIS 0x0
//! Constant EN - Write Enable
#define CONST_PM_PDI_CTRL_WEN_EN 0x1

//! @}

//! \defgroup PM_PDI_ADDRL Register PM_PDI_ADDRL - Packet Manager Address Low Register
//! @{

//! Register Offset (relative)
#define PM_PDI_ADDRL 0x1C0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_ADDRL 0x00D381C0u

//! Register Reset Value
#define PM_PDI_ADDRL_RST 0x00000000u

//! Field ADDRL - PM Address Low
#define PM_PDI_ADDRL_ADDRL_POS 0
//! Field ADDRL - PM Address Low
#define PM_PDI_ADDRL_ADDRL_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_ADDRH Register PM_PDI_ADDRH - Packet Manager Address High Register
//! @{

//! Register Offset (relative)
#define PM_PDI_ADDRH 0x1C4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_ADDRH 0x00D381C4u

//! Register Reset Value
#define PM_PDI_ADDRH_RST 0x00000000u

//! Field ADDRH - PM Address High
#define PM_PDI_ADDRH_ADDRH_POS 0
//! Field ADDRH - PM Address High
#define PM_PDI_ADDRH_ADDRH_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_DATAL Register PM_PDI_DATAL - Packet Manager Data Low Register
//! @{

//! Register Offset (relative)
#define PM_PDI_DATAL 0x1C8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_DATAL 0x00D381C8u

//! Register Reset Value
#define PM_PDI_DATAL_RST 0x00000000u

//! Field DATAL - Data Low 16 bits
#define PM_PDI_DATAL_DATAL_POS 0
//! Field DATAL - Data Low 16 bits
#define PM_PDI_DATAL_DATAL_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_DATAH Register PM_PDI_DATAH - Packet Manager Data High Register
//! @{

//! Register Offset (relative)
#define PM_PDI_DATAH 0x1CC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_DATAH 0x00D381CCu

//! Register Reset Value
#define PM_PDI_DATAH_RST 0x00000000u

//! Field DATAH - Data High 16 bits
#define PM_PDI_DATAH_DATAH_POS 0
//! Field DATAH - Data High 16 bits
#define PM_PDI_DATAH_DATAH_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_TTSE_GPHY_POSL Register PM_PDI_PCH_CTL_TTSE_GPHY_POSL - Position of TTSE_GPHY bit in the Lower 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSL 0x1D0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_TTSE_GPHY_POSL 0x00A381D0u

//! Register Reset Value
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSL_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSL_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSL_POS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_TTSE_GPHY_POSH Register PM_PDI_PCH_CTL_TTSE_GPHY_POSH - Position of TTSE_GPHY bit in the Higher 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSH 0x1D4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_TTSE_GPHY_POSH 0x00A381D4u

//! Register Reset Value
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSH_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSH_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GPHY_POSH_POS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_TTSE_GMAC_POSL Register PM_PDI_PCH_CTL_TTSE_GMAC_POSL - Position of TTSE_GMAC bit in the Lower 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSL 0x1D8
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_TTSE_GMAC_POSL 0x00A381D8u

//! Register Reset Value
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSL_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSL_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSL_POS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_TTSE_GMAC_POSH Register PM_PDI_PCH_CTL_TTSE_GMAC_POSH - Position of TTSE_GMAC bit in the Higher 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSH 0x1DC
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_TTSE_GMAC_POSH 0x00A381DCu

//! Register Reset Value
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSH_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSH_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_TTSE_GMAC_POSH_POS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_OSTC_POSL Register PM_PDI_PCH_CTL_OSTC_POSL - Position of OSTC bit in the Lower 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_OSTC_POSL 0x1E0
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_OSTC_POSL 0x00A381E0u

//! Register Reset Value
#define PM_PDI_PCH_CTL_OSTC_POSL_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_OSTC_POSL_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_OSTC_POSL_POS_MASK 0xFFFFu

//! @}

//! \defgroup PM_PDI_PCH_CTL_OSTC_POSH Register PM_PDI_PCH_CTL_OSTC_POSH - Position of OSTC bit in the Higher 16 bits of the PCH_CTRL
//! @{

//! Register Offset (relative)
#define PM_PDI_PCH_CTL_OSTC_POSH 0x1E4
//! Register Offset (absolute) for 1st Instance PM_PDI
#define PM_PDI_PM_PDI_PCH_CTL_OSTC_POSH 0x00A381E4u

//! Register Reset Value
#define PM_PDI_PCH_CTL_OSTC_POSH_RST 0x00000000u

//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_OSTC_POSH_POS_POS 0
//! Field POS - One bit selection
#define PM_PDI_PCH_CTL_OSTC_POSH_POS_MASK 0xFFFFu

//! @}

//! @}

#endif
