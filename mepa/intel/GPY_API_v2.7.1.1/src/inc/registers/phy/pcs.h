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
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/pcs_def.xml
// Register File Name  : PCS
// Register File Title : Standard PCS Registers for MMD=0x03
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PCS_H
#define _PCS_H

//! \defgroup PCS Register File PCS - Standard PCS Registers for MMD=0x03
//! @{

//! Base Address of PCS
#define PCS_MODULE_BASE 0x00600000u

//! \defgroup PCS_CTRL1 Register PCS_CTRL1 - PCS control 1 (Register 3.0)
//! @{

//! Register Offset (relative)
#define PCS_CTRL1 0x0
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_CTRL1 0x00600000u

//! Register Reset Value
#define PCS_CTRL1_RST 0x205Cu

//! Field SPEED_SEL - Forced Speed selection Values
#define PCS_CTRL1_SPEED_SEL_POS 2
//! Field SPEED_SEL - Forced Speed selection Values
#define PCS_CTRL1_SPEED_SEL_MASK 0x3Cu
//! Constant S2G5 - Forced Speed is 2G5
#define CONST_PCS_CTRL1_SPEED_SEL_S2G5 0x7

//! Field SSM - Forced Speed selection (MSB)
#define PCS_CTRL1_SSM_POS 6
//! Field SSM - Forced Speed selection (MSB)
#define PCS_CTRL1_SSM_MASK 0x40u

//! Field RXCKST - Clock stop enable
#define PCS_CTRL1_RXCKST_POS 10
//! Field RXCKST - Clock stop enable
#define PCS_CTRL1_RXCKST_MASK 0x400u

//! Field LOW_POWER - Low power
#define PCS_CTRL1_LOW_POWER_POS 11
//! Field LOW_POWER - Low power
#define PCS_CTRL1_LOW_POWER_MASK 0x800u

//! Field SSL - Forced Speed selection (LSB)
#define PCS_CTRL1_SSL_POS 13
//! Field SSL - Forced Speed selection (LSB)
#define PCS_CTRL1_SSL_MASK 0x2000u

//! Field LOOPBACK - Loopback
#define PCS_CTRL1_LOOPBACK_POS 14
//! Field LOOPBACK - Loopback
#define PCS_CTRL1_LOOPBACK_MASK 0x4000u

//! Field RST - Reset
#define PCS_CTRL1_RST_POS 15
//! Field RST - Reset
#define PCS_CTRL1_RST_MASK 0x8000u

//! @}

//! \defgroup PCS_STAT1 Register PCS_STAT1 - PCS status 1 (Register 3.1)
//! @{

//! Register Offset (relative)
#define PCS_STAT1 0x2
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_STAT1 0x00600002u

//! Register Reset Value
#define PCS_STAT1_RST 0x0000u

//! Field LOW_POWER_ABILITY - Low-power ability
#define PCS_STAT1_LOW_POWER_ABILITY_POS 1
//! Field LOW_POWER_ABILITY - Low-power ability
#define PCS_STAT1_LOW_POWER_ABILITY_MASK 0x2u

//! Field PCS_RX_LINK_STATUS - PCS receive link status
#define PCS_STAT1_PCS_RX_LINK_STATUS_POS 2
//! Field PCS_RX_LINK_STATUS - PCS receive link status
#define PCS_STAT1_PCS_RX_LINK_STATUS_MASK 0x4u

//! Field TXCKST - Clock stop capable
#define PCS_STAT1_TXCKST_POS 6
//! Field TXCKST - Clock stop capable
#define PCS_STAT1_TXCKST_MASK 0x40u

//! Field FAULT - Fault
#define PCS_STAT1_FAULT_POS 7
//! Field FAULT - Fault
#define PCS_STAT1_FAULT_MASK 0x80u

//! Field RX_LPI_INDICATION - Rx LPI indication
#define PCS_STAT1_RX_LPI_INDICATION_POS 8
//! Field RX_LPI_INDICATION - Rx LPI indication
#define PCS_STAT1_RX_LPI_INDICATION_MASK 0x100u

//! Field TX_LPI_INDICATION - Tx LPI indication
#define PCS_STAT1_TX_LPI_INDICATION_POS 9
//! Field TX_LPI_INDICATION - Tx LPI indication
#define PCS_STAT1_TX_LPI_INDICATION_MASK 0x200u

//! Field RX_LPI_RXD - Rx LPI received
#define PCS_STAT1_RX_LPI_RXD_POS 10
//! Field RX_LPI_RXD - Rx LPI received
#define PCS_STAT1_RX_LPI_RXD_MASK 0x400u

//! Field TX_LPI_RXD - Tx LPI received
#define PCS_STAT1_TX_LPI_RXD_POS 11
//! Field TX_LPI_RXD - Tx LPI received
#define PCS_STAT1_TX_LPI_RXD_MASK 0x800u

//! @}

//! \defgroup PCS_DEVID1 Register PCS_DEVID1 - PHY Identifier 1 (Register 3.2)
//! @{

//! Register Offset (relative)
#define PCS_DEVID1 0x4
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_DEVID1 0x00600004u

//! Register Reset Value
#define PCS_DEVID1_RST 0x67C9u

//! Field OUI
#define PCS_DEVID1_OUI_POS 0
//! Field OUI
#define PCS_DEVID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup PCS_DEVID2 Register PCS_DEVID2 - PHY Identifier 2 (Register 3.3)
//! @{

//! Register Offset (relative)
#define PCS_DEVID2 0x6
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_DEVID2 0x00600006u

//! Register Reset Value
#define PCS_DEVID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define PCS_DEVID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define PCS_DEVID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define PCS_DEVID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define PCS_DEVID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PCS_DEVID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PCS_DEVID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup PCS_SPEED_ABILITY Register PCS_SPEED_ABILITY - PCS speed ability (Register 3.4)
//! @{

//! Register Offset (relative)
#define PCS_SPEED_ABILITY 0x8
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_SPEED_ABILITY 0x00600008u

//! Register Reset Value
#define PCS_SPEED_ABILITY_RST 0x0040u

//! Field R10G_CAPABLE - 10G capable
#define PCS_SPEED_ABILITY_R10G_CAPABLE_POS 0
//! Field R10G_CAPABLE - 10G capable
#define PCS_SPEED_ABILITY_R10G_CAPABLE_MASK 0x1u

//! Field R10PASS_TS_2BASE_TL - 10PASS-TS/2BASE-TL Capable
#define PCS_SPEED_ABILITY_R10PASS_TS_2BASE_TL_POS 1
//! Field R10PASS_TS_2BASE_TL - 10PASS-TS/2BASE-TL Capable
#define PCS_SPEED_ABILITY_R10PASS_TS_2BASE_TL_MASK 0x2u

//! Field R40G_CAPABLE - 40G capable
#define PCS_SPEED_ABILITY_R40G_CAPABLE_POS 2
//! Field R40G_CAPABLE - 40G capable
#define PCS_SPEED_ABILITY_R40G_CAPABLE_MASK 0x4u

//! Field R100G_CAPABLE - 100G capable
#define PCS_SPEED_ABILITY_R100G_CAPABLE_POS 3
//! Field R100G_CAPABLE - 100G capable
#define PCS_SPEED_ABILITY_R100G_CAPABLE_MASK 0x8u

//! Field R2G5_CAPABLE - 2G5 capable
#define PCS_SPEED_ABILITY_R2G5_CAPABLE_POS 6
//! Field R2G5_CAPABLE - 2G5 capable
#define PCS_SPEED_ABILITY_R2G5_CAPABLE_MASK 0x40u

//! @}

//! \defgroup PCS_DIP1 Register PCS_DIP1 - PCS Devices in package 1 (Register 3.5)
//! @{

//! Register Offset (relative)
#define PCS_DIP1 0xA
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_DIP1 0x0060000Au

//! Register Reset Value
#define PCS_DIP1_RST 0x008Bu

//! Field CL22 - Clause 22 registers present
#define PCS_DIP1_CL22_POS 0
//! Field CL22 - Clause 22 registers present
#define PCS_DIP1_CL22_MASK 0x1u

//! Field PMD_PMA - PMD/PMA present
#define PCS_DIP1_PMD_PMA_POS 1
//! Field PMD_PMA - PMD/PMA present
#define PCS_DIP1_PMD_PMA_MASK 0x2u

//! Field WIS_PRESENT - WIS present
#define PCS_DIP1_WIS_PRESENT_POS 2
//! Field WIS_PRESENT - WIS present
#define PCS_DIP1_WIS_PRESENT_MASK 0x4u

//! Field PCS - PCS present
#define PCS_DIP1_PCS_POS 3
//! Field PCS - PCS present
#define PCS_DIP1_PCS_MASK 0x8u

//! Field PHY_XS - PHY XS present
#define PCS_DIP1_PHY_XS_POS 4
//! Field PHY_XS - PHY XS present
#define PCS_DIP1_PHY_XS_MASK 0x10u

//! Field DTE_XS - DTE XS present
#define PCS_DIP1_DTE_XS_POS 5
//! Field DTE_XS - DTE XS present
#define PCS_DIP1_DTE_XS_MASK 0x20u

//! Field TC - TC present
#define PCS_DIP1_TC_POS 6
//! Field TC - TC present
#define PCS_DIP1_TC_MASK 0x40u

//! Field ANEG - Auto-Negotiation present
#define PCS_DIP1_ANEG_POS 7
//! Field ANEG - Auto-Negotiation present
#define PCS_DIP1_ANEG_MASK 0x80u

//! Field SEPARATED_PMA_1 - Separate PMA (1)
#define PCS_DIP1_SEPARATED_PMA_1_POS 8
//! Field SEPARATED_PMA_1 - Separate PMA (1)
#define PCS_DIP1_SEPARATED_PMA_1_MASK 0x100u

//! Field SEPARATED_PMA_2 - Separate PMA (2)
#define PCS_DIP1_SEPARATED_PMA_2_POS 9
//! Field SEPARATED_PMA_2 - Separate PMA (2)
#define PCS_DIP1_SEPARATED_PMA_2_MASK 0x200u

//! Field SEP_PMA_3 - Separate PMA (3)
#define PCS_DIP1_SEP_PMA_3_POS 10
//! Field SEP_PMA_3 - Separate PMA (3)
#define PCS_DIP1_SEP_PMA_3_MASK 0x400u

//! Field SEPARATED_PMA_4 - Separate PMA (4)
#define PCS_DIP1_SEPARATED_PMA_4_POS 11
//! Field SEPARATED_PMA_4 - Separate PMA (4)
#define PCS_DIP1_SEPARATED_PMA_4_MASK 0x800u

//! Field RES - Reserved
#define PCS_DIP1_RES_POS 12
//! Field RES - Reserved
#define PCS_DIP1_RES_MASK 0xF000u

//! @}

//! \defgroup PCS_DIP2 Register PCS_DIP2 - PCS Devices in package 2 (Register 3.6)
//! @{

//! Register Offset (relative)
#define PCS_DIP2 0xC
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_DIP2 0x0060000Cu

//! Register Reset Value
#define PCS_DIP2_RST 0xC000u

//! Field RES - Reserved
#define PCS_DIP2_RES_POS 0
//! Field RES - Reserved
#define PCS_DIP2_RES_MASK 0x1FFFu

//! Field CLAUSE_22_EXTENSION - Clause 22 extension
#define PCS_DIP2_CLAUSE_22_EXTENSION_POS 13
//! Field CLAUSE_22_EXTENSION - Clause 22 extension
#define PCS_DIP2_CLAUSE_22_EXTENSION_MASK 0x2000u

//! Field VENDOR_SPECIFIC_DEVICE_1 - Vendor-specific device 1
#define PCS_DIP2_VENDOR_SPECIFIC_DEVICE_1_POS 14
//! Field VENDOR_SPECIFIC_DEVICE_1 - Vendor-specific device 1
#define PCS_DIP2_VENDOR_SPECIFIC_DEVICE_1_MASK 0x4000u

//! Field VENDOR_SPECIFIC_DEVICE_2 - Vendor-specific device 2
#define PCS_DIP2_VENDOR_SPECIFIC_DEVICE_2_POS 15
//! Field VENDOR_SPECIFIC_DEVICE_2 - Vendor-specific device 2
#define PCS_DIP2_VENDOR_SPECIFIC_DEVICE_2_MASK 0x8000u

//! @}

//! \defgroup PCS_CTRL2 Register PCS_CTRL2 - PCS control 2 (Register 3.7)
//! @{

//! Register Offset (relative)
#define PCS_CTRL2 0xE
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_CTRL2 0x0060000Eu

//! Register Reset Value
#define PCS_CTRL2_RST 0x000Au

//! Field PCS_TYPE_SEL - PCS type selection
#define PCS_CTRL2_PCS_TYPE_SEL_POS 0
//! Field PCS_TYPE_SEL - PCS type selection
#define PCS_CTRL2_PCS_TYPE_SEL_MASK 0xFu

//! @}

//! \defgroup PCS_STAT2 Register PCS_STAT2 - PCS status 2 (Register 3.8)
//! @{

//! Register Offset (relative)
#define PCS_STAT2 0x10
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_STAT2 0x00600010u

//! Register Reset Value
#define PCS_STAT2_RST 0x9000u

//! Field R10GBASE_R_CAPABLE - 10GBASE-R capable
#define PCS_STAT2_R10GBASE_R_CAPABLE_POS 0
//! Field R10GBASE_R_CAPABLE - 10GBASE-R capable
#define PCS_STAT2_R10GBASE_R_CAPABLE_MASK 0x1u

//! Field R10GBASE_X_CAPABLE - 10GBASE-X capable
#define PCS_STAT2_R10GBASE_X_CAPABLE_POS 1
//! Field R10GBASE_X_CAPABLE - 10GBASE-X capable
#define PCS_STAT2_R10GBASE_X_CAPABLE_MASK 0x2u

//! Field R10GBASE_W_CAPABLE - 10GBASE-W capable
#define PCS_STAT2_R10GBASE_W_CAPABLE_POS 2
//! Field R10GBASE_W_CAPABLE - 10GBASE-W capable
#define PCS_STAT2_R10GBASE_W_CAPABLE_MASK 0x4u

//! Field R10GBASE_T_CAPABLE - 10GBASE-T capable
#define PCS_STAT2_R10GBASE_T_CAPABLE_POS 3
//! Field R10GBASE_T_CAPABLE - 10GBASE-T capable
#define PCS_STAT2_R10GBASE_T_CAPABLE_MASK 0x8u

//! Field R40GBASE_R_CAPABLE - 40GBASE-R capable
#define PCS_STAT2_R40GBASE_R_CAPABLE_POS 4
//! Field R40GBASE_R_CAPABLE - 40GBASE-R capable
#define PCS_STAT2_R40GBASE_R_CAPABLE_MASK 0x10u

//! Field R100GBASE_R_CAPABLE - 100GBASE-R capable
#define PCS_STAT2_R100GBASE_R_CAPABLE_POS 5
//! Field R100GBASE_R_CAPABLE - 100GBASE-R capable
#define PCS_STAT2_R100GBASE_R_CAPABLE_MASK 0x20u

//! Field RX_FAULT - Receive fault
#define PCS_STAT2_RX_FAULT_POS 10
//! Field RX_FAULT - Receive fault
#define PCS_STAT2_RX_FAULT_MASK 0x400u

//! Field TX_FAULT - Transmit fault
#define PCS_STAT2_TX_FAULT_POS 11
//! Field TX_FAULT - Transmit fault
#define PCS_STAT2_TX_FAULT_MASK 0x800u

//! Field R2G5_CAPABLE - 2G5BASE-T capable
#define PCS_STAT2_R2G5_CAPABLE_POS 12
//! Field R2G5_CAPABLE - 2G5BASE-T capable
#define PCS_STAT2_R2G5_CAPABLE_MASK 0x1000u

//! Field DEVICE_PRESENT - Device present
#define PCS_STAT2_DEVICE_PRESENT_POS 14
//! Field DEVICE_PRESENT - Device present
#define PCS_STAT2_DEVICE_PRESENT_MASK 0xC000u

//! @}

//! \defgroup PCS_PACKID1 Register PCS_PACKID1 - PCS package identifier 1 (Register 3.14)
//! @{

//! Register Offset (relative)
#define PCS_PACKID1 0x1C
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_PACKID1 0x0060001Cu

//! Register Reset Value
#define PCS_PACKID1_RST 0x67C9u

//! Field OUI
#define PCS_PACKID1_OUI_POS 0
//! Field OUI
#define PCS_PACKID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup PCS_PACKID2 Register PCS_PACKID2 - PCS package identifier 2 (Register 3.15)
//! @{

//! Register Offset (relative)
#define PCS_PACKID2 0x1E
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_PACKID2 0x0060001Eu

//! Register Reset Value
#define PCS_PACKID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define PCS_PACKID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define PCS_PACKID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define PCS_PACKID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define PCS_PACKID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PCS_PACKID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PCS_PACKID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup PCS_EEE_CAP Register PCS_EEE_CAP - PCS EEE capability (Register 3.20)
//! @{

//! Register Offset (relative)
#define PCS_EEE_CAP 0x28
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_EEE_CAP 0x00600028u

//! Register Reset Value
#define PCS_EEE_CAP_RST 0x0006u

//! Field R100BASE_TX_EEE - 100BASE-TX EEE
#define PCS_EEE_CAP_R100BASE_TX_EEE_POS 1
//! Field R100BASE_TX_EEE - 100BASE-TX EEE
#define PCS_EEE_CAP_R100BASE_TX_EEE_MASK 0x2u

//! Field R1000BASE_T_EEE - 1000BASE-T EEE
#define PCS_EEE_CAP_R1000BASE_T_EEE_POS 2
//! Field R1000BASE_T_EEE - 1000BASE-T EEE
#define PCS_EEE_CAP_R1000BASE_T_EEE_MASK 0x4u

//! Field R10GBASE_T_EEE - 10GBASE-T EEE
#define PCS_EEE_CAP_R10GBASE_T_EEE_POS 3
//! Field R10GBASE_T_EEE - 10GBASE-T EEE
#define PCS_EEE_CAP_R10GBASE_T_EEE_MASK 0x8u

//! Field R1000BASE_KX_EEE - 1000BASE-KX EEE
#define PCS_EEE_CAP_R1000BASE_KX_EEE_POS 4
//! Field R1000BASE_KX_EEE - 1000BASE-KX EEE
#define PCS_EEE_CAP_R1000BASE_KX_EEE_MASK 0x10u

//! Field R10GBASE_KX4_EEE - 10GBASE-KX4 EEE
#define PCS_EEE_CAP_R10GBASE_KX4_EEE_POS 5
//! Field R10GBASE_KX4_EEE - 10GBASE-KX4 EEE
#define PCS_EEE_CAP_R10GBASE_KX4_EEE_MASK 0x20u

//! Field R10GBASE_KR_EEE - 10GBASE-KR EEE
#define PCS_EEE_CAP_R10GBASE_KR_EEE_POS 6
//! Field R10GBASE_KR_EEE - 10GBASE-KR EEE
#define PCS_EEE_CAP_R10GBASE_KR_EEE_MASK 0x40u

//! @}

//! \defgroup PCS_EEE_CAP2 Register PCS_EEE_CAP2 - EEE control and capability 2 (Register 3.21)
//! @{

//! Register Offset (relative)
#define PCS_EEE_CAP2 0x2A
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_EEE_CAP2 0x0060002Au

//! Register Reset Value
#define PCS_EEE_CAP2_RST 0x0001u

//! Field AB2G5EEE - EEE supported for 2G5BT
#define PCS_EEE_CAP2_AB2G5EEE_POS 0
//! Field AB2G5EEE - EEE supported for 2G5BT
#define PCS_EEE_CAP2_AB2G5EEE_MASK 0x1u
//! Constant UNABLE - EEE not supported for 2G5BT
#define CONST_PCS_EEE_CAP2_AB2G5EEE_UNABLE 0x0
//! Constant ABLE - EEE supported for 2G5BT
#define CONST_PCS_EEE_CAP2_AB2G5EEE_ABLE 0x1

//! Field AB5GEEE - EEE supported for 5GBT
#define PCS_EEE_CAP2_AB5GEEE_POS 1
//! Field AB5GEEE - EEE supported for 5GBT
#define PCS_EEE_CAP2_AB5GEEE_MASK 0x2u
//! Constant UNABLE - EEE supported for 5GBT
#define CONST_PCS_EEE_CAP2_AB5GEEE_UNABLE 0x0
//! Constant ABLE - EEE supported for 5GBT
#define CONST_PCS_EEE_CAP2_AB5GEEE_ABLE 0x1

//! Field RES - Reserved
#define PCS_EEE_CAP2_RES_POS 2
//! Field RES - Reserved
#define PCS_EEE_CAP2_RES_MASK 0xFFFCu

//! @}

//! \defgroup PCS_EEE_WAKERR Register PCS_EEE_WAKERR - PCS EEE Status Register 1 (Register 3.22)
//! @{

//! Register Offset (relative)
#define PCS_EEE_WAKERR 0x2C
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_EEE_WAKERR 0x0060002Cu

//! Register Reset Value
#define PCS_EEE_WAKERR_RST 0x0000u

//! Field ERRCNT - EEE Wake Error Counter
#define PCS_EEE_WAKERR_ERRCNT_POS 0
//! Field ERRCNT - EEE Wake Error Counter
#define PCS_EEE_WAKERR_ERRCNT_MASK 0xFFFFu

//! @}

//! \defgroup PCS_2G5_STAT1 Register PCS_2G5_STAT1 - BASE-R and 10GBASE-T PCS status 1 (Register 3.32)
//! @{

//! Register Offset (relative)
#define PCS_2G5_STAT1 0x40
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_2G5_STAT1 0x00600040u

//! Register Reset Value
#define PCS_2G5_STAT1_RST 0x0000u

//! Field PCS2G5_BLO_LOCK - PCS 2G5 Block Lock
#define PCS_2G5_STAT1_PCS2G5_BLO_LOCK_POS 0
//! Field PCS2G5_BLO_LOCK - PCS 2G5 Block Lock
#define PCS_2G5_STAT1_PCS2G5_BLO_LOCK_MASK 0x1u

//! Field PCS2G5_HI_BER - PCS 2G5 high BER
#define PCS_2G5_STAT1_PCS2G5_HI_BER_POS 1
//! Field PCS2G5_HI_BER - PCS 2G5 high BER
#define PCS_2G5_STAT1_PCS2G5_HI_BER_MASK 0x2u

//! Field PCS2G5_PAT_TEST_AB - 10GBASE-R PRBS9 pattern testing ability
#define PCS_2G5_STAT1_PCS2G5_PAT_TEST_AB_POS 3
//! Field PCS2G5_PAT_TEST_AB - 10GBASE-R PRBS9 pattern testing ability
#define PCS_2G5_STAT1_PCS2G5_PAT_TEST_AB_MASK 0x8u

//! Field PCS2G5_LINK_STATUS - BASE-R and 10GBase-T RX Link Status
#define PCS_2G5_STAT1_PCS2G5_LINK_STATUS_POS 12
//! Field PCS2G5_LINK_STATUS - BASE-R and 10GBase-T RX Link Status
#define PCS_2G5_STAT1_PCS2G5_LINK_STATUS_MASK 0x1000u

//! @}

//! \defgroup PCS_2G5_STAT2 Register PCS_2G5_STAT2 - MULTIGBASE-T PCS status 2 (Register 3.33)
//! @{

//! Register Offset (relative)
#define PCS_2G5_STAT2 0x42
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_2G5_STAT2 0x00600042u

//! Register Reset Value
#define PCS_2G5_STAT2_RST 0x0000u

//! Field ERRED_BLK - Errored blocks
#define PCS_2G5_STAT2_ERRED_BLK_POS 0
//! Field ERRED_BLK - Errored blocks
#define PCS_2G5_STAT2_ERRED_BLK_MASK 0xFFu

//! Field BER - BER
#define PCS_2G5_STAT2_BER_POS 8
//! Field BER - BER
#define PCS_2G5_STAT2_BER_MASK 0x3F00u

//! Field LATCHED_HIGH_BER - Latched high BER
#define PCS_2G5_STAT2_LATCHED_HIGH_BER_POS 14
//! Field LATCHED_HIGH_BER - Latched high BER
#define PCS_2G5_STAT2_LATCHED_HIGH_BER_MASK 0x4000u

//! Field LATCHED_BLOCK_LOCK - Latched block lock
#define PCS_2G5_STAT2_LATCHED_BLOCK_LOCK_POS 15
//! Field LATCHED_BLOCK_LOCK - Latched block lock
#define PCS_2G5_STAT2_LATCHED_BLOCK_LOCK_MASK 0x8000u

//! @}

//! \defgroup PCS_TIMESYNC_CAP Register PCS_TIMESYNC_CAP - PCS TimeSync capability register (Register 3.1800)
//! @{

//! Register Offset (relative)
#define PCS_TIMESYNC_CAP 0xE10
//! Register Offset (absolute) for 1st Instance PCS
#define PCS_PCS_TIMESYNC_CAP 0x00600E10u

//! Register Reset Value
#define PCS_TIMESYNC_CAP_RST 0x0000u

//! Field TIMESYNC_RX_PATH_DATA_DELAY - TimeSync receive path data delay
#define PCS_TIMESYNC_CAP_TIMESYNC_RX_PATH_DATA_DELAY_POS 0
//! Field TIMESYNC_RX_PATH_DATA_DELAY - TimeSync receive path data delay
#define PCS_TIMESYNC_CAP_TIMESYNC_RX_PATH_DATA_DELAY_MASK 0x1u

//! Field TIMESYNC_TX_PATH_DATA_DELAY - TimeSync transmit path data delay
#define PCS_TIMESYNC_CAP_TIMESYNC_TX_PATH_DATA_DELAY_POS 1
//! Field TIMESYNC_TX_PATH_DATA_DELAY - TimeSync transmit path data delay
#define PCS_TIMESYNC_CAP_TIMESYNC_TX_PATH_DATA_DELAY_MASK 0x2u

//! @}

//! @}

#endif
