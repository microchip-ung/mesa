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
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/pmapmd_def.xml
// Register File Name  : PMAPMD
// Register File Title : Standard PMAPMD Registers for MMD=0x01
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PMAPMD_H
#define _PMAPMD_H

//! \defgroup PMAPMD Register File PMAPMD - Standard PMAPMD Registers for MMD=0x01
//! @{

//! Base Address of PMAPMD
#define PMAPMD_MODULE_BASE 0x00200000u

//! \defgroup PMA_CTRL1 Register PMA_CTRL1 - PMA/PMD Control 1 (Register 1.0)
//! @{

//! Register Offset (relative)
#define PMA_CTRL1 0x0
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_CTRL1 0x00200000u

//! Register Reset Value
#define PMA_CTRL1_RST 0x2058u

//! Field NS2 - Not Supported
#define PMA_CTRL1_NS2_POS 0
//! Field NS2 - Not Supported
#define PMA_CTRL1_NS2_MASK 0x1u

//! Field NS1 - Not Supported
#define PMA_CTRL1_NS1_POS 1
//! Field NS1 - Not Supported
#define PMA_CTRL1_NS1_MASK 0x2u

//! Field SPEED_SEL - Speed Selection
#define PMA_CTRL1_SPEED_SEL_POS 2
//! Field SPEED_SEL - Speed Selection
#define PMA_CTRL1_SPEED_SEL_MASK 0x3Cu
//! Constant S2G5 - Forced Speed is 2G5
#define CONST_PMA_CTRL1_SPEED_SEL_S2G5 0x6

//! Field SSM - Speed Selection (MSB)
#define PMA_CTRL1_SSM_POS 6
//! Field SSM - Speed Selection (MSB)
#define PMA_CTRL1_SSM_MASK 0x40u

//! Field LOW_POWER - Low power
#define PMA_CTRL1_LOW_POWER_POS 11
//! Field LOW_POWER - Low power
#define PMA_CTRL1_LOW_POWER_MASK 0x800u

//! Field SSL - Speed Selection (LSB)
#define PMA_CTRL1_SSL_POS 13
//! Field SSL - Speed Selection (LSB)
#define PMA_CTRL1_SSL_MASK 0x2000u

//! Field RST - Reset
#define PMA_CTRL1_RST_POS 15
//! Field RST - Reset
#define PMA_CTRL1_RST_MASK 0x8000u

//! @}

//! \defgroup PMA_STAT1 Register PMA_STAT1 - PMA/PMD status 1 (Register 1.1)
//! @{

//! Register Offset (relative)
#define PMA_STAT1 0x2
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_STAT1 0x00200002u

//! Register Reset Value
#define PMA_STAT1_RST 0x0000u

//! Field LOW_POWER_ABILITY - Low Power Ability
#define PMA_STAT1_LOW_POWER_ABILITY_POS 1
//! Field LOW_POWER_ABILITY - Low Power Ability
#define PMA_STAT1_LOW_POWER_ABILITY_MASK 0x2u

//! Field RX_LINK_STATUS - Receive Link Status
#define PMA_STAT1_RX_LINK_STATUS_POS 2
//! Field RX_LINK_STATUS - Receive Link Status
#define PMA_STAT1_RX_LINK_STATUS_MASK 0x4u

//! Field FAULT - Fault
#define PMA_STAT1_FAULT_POS 7
//! Field FAULT - Fault
#define PMA_STAT1_FAULT_MASK 0x80u

//! @}

//! \defgroup PMA_DEVID1 Register PMA_DEVID1 - PHY Identifier 1 (Register 1.2)
//! @{

//! Register Offset (relative)
#define PMA_DEVID1 0x4
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_DEVID1 0x00200004u

//! Register Reset Value
#define PMA_DEVID1_RST 0x67C9u

//! Field OUI - Organizationally Unique Identifier
#define PMA_DEVID1_OUI_POS 0
//! Field OUI - Organizationally Unique Identifier
#define PMA_DEVID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup PMA_DEVID2 Register PMA_DEVID2 - PHY Identifier 2 (Register 1.3)
//! @{

//! Register Offset (relative)
#define PMA_DEVID2 0x6
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_DEVID2 0x00200006u

//! Register Reset Value
#define PMA_DEVID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define PMA_DEVID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define PMA_DEVID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define PMA_DEVID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define PMA_DEVID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PMA_DEVID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PMA_DEVID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup PMA_SPEED_ABILITY Register PMA_SPEED_ABILITY - PMA/PMD speed ability (Register 1.4)
//! @{

//! Register Offset (relative)
#define PMA_SPEED_ABILITY 0x8
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_SPEED_ABILITY 0x00200008u

//! Register Reset Value
#define PMA_SPEED_ABILITY_RST 0x2070u

//! Field CAP_10G_CAP - Not Supported
#define PMA_SPEED_ABILITY_CAP_10G_CAP_POS 0
//! Field CAP_10G_CAP - Not Supported
#define PMA_SPEED_ABILITY_CAP_10G_CAP_MASK 0x1u

//! Field CAP_2BASE_TL - Not Supported
#define PMA_SPEED_ABILITY_CAP_2BASE_TL_POS 1
//! Field CAP_2BASE_TL - Not Supported
#define PMA_SPEED_ABILITY_CAP_2BASE_TL_MASK 0x2u

//! Field R10PASS_TS_CAPABLE - Not Supported
#define PMA_SPEED_ABILITY_R10PASS_TS_CAPABLE_POS 2
//! Field R10PASS_TS_CAPABLE - Not Supported
#define PMA_SPEED_ABILITY_R10PASS_TS_CAPABLE_MASK 0x4u

//! Field CAP_1000M - 1000M capable
#define PMA_SPEED_ABILITY_CAP_1000M_POS 4
//! Field CAP_1000M - 1000M capable
#define PMA_SPEED_ABILITY_CAP_1000M_MASK 0x10u

//! Field CAP_100M - 100M capable
#define PMA_SPEED_ABILITY_CAP_100M_POS 5
//! Field CAP_100M - 100M capable
#define PMA_SPEED_ABILITY_CAP_100M_MASK 0x20u

//! Field CAP_10M - 10M capable
#define PMA_SPEED_ABILITY_CAP_10M_POS 6
//! Field CAP_10M - 10M capable
#define PMA_SPEED_ABILITY_CAP_10M_MASK 0x40u

//! Field CAP_10_1G - Not Supported
#define PMA_SPEED_ABILITY_CAP_10_1G_POS 7
//! Field CAP_10_1G - Not Supported
#define PMA_SPEED_ABILITY_CAP_10_1G_MASK 0x80u

//! Field CAP_40G - Not Supported
#define PMA_SPEED_ABILITY_CAP_40G_POS 8
//! Field CAP_40G - Not Supported
#define PMA_SPEED_ABILITY_CAP_40G_MASK 0x100u

//! Field CAP_100G - Not Supported
#define PMA_SPEED_ABILITY_CAP_100G_POS 9
//! Field CAP_100G - Not Supported
#define PMA_SPEED_ABILITY_CAP_100G_MASK 0x200u

//! Field RES2 - Reserved
#define PMA_SPEED_ABILITY_RES2_POS 12
//! Field RES2 - Reserved
#define PMA_SPEED_ABILITY_RES2_MASK 0x1000u

//! Field CAP_2G5 - 2.5 G capable
#define PMA_SPEED_ABILITY_CAP_2G5_POS 13
//! Field CAP_2G5 - 2.5 G capable
#define PMA_SPEED_ABILITY_CAP_2G5_MASK 0x2000u

//! Field CAP_5G - Not Supported
#define PMA_SPEED_ABILITY_CAP_5G_POS 14
//! Field CAP_5G - Not Supported
#define PMA_SPEED_ABILITY_CAP_5G_MASK 0x4000u

//! @}

//! \defgroup PMA_DIP1 Register PMA_DIP1 - Devices in package 1 (Register 1.5)
//! @{

//! Register Offset (relative)
#define PMA_DIP1 0xA
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_DIP1 0x0020000Au

//! Register Reset Value
#define PMA_DIP1_RST 0x008Bu

//! Field CLAUSE_22 - Clause 22 registers present
#define PMA_DIP1_CLAUSE_22_POS 0
//! Field CLAUSE_22 - Clause 22 registers present
#define PMA_DIP1_CLAUSE_22_MASK 0x1u

//! Field PMD_PMA - PMD/PMA present
#define PMA_DIP1_PMD_PMA_POS 1
//! Field PMD_PMA - PMD/PMA present
#define PMA_DIP1_PMD_PMA_MASK 0x2u

//! Field WIS - WIS present
#define PMA_DIP1_WIS_POS 2
//! Field WIS - WIS present
#define PMA_DIP1_WIS_MASK 0x4u

//! Field PCS - PCS present
#define PMA_DIP1_PCS_POS 3
//! Field PCS - PCS present
#define PMA_DIP1_PCS_MASK 0x8u

//! Field PHY_XS - PHY XS present
#define PMA_DIP1_PHY_XS_POS 4
//! Field PHY_XS - PHY XS present
#define PMA_DIP1_PHY_XS_MASK 0x10u

//! Field DTE_XS - DTE XS present
#define PMA_DIP1_DTE_XS_POS 5
//! Field DTE_XS - DTE XS present
#define PMA_DIP1_DTE_XS_MASK 0x20u

//! Field TC - TC present
#define PMA_DIP1_TC_POS 6
//! Field TC - TC present
#define PMA_DIP1_TC_MASK 0x40u

//! Field ANEG - Auto-Negotiation present
#define PMA_DIP1_ANEG_POS 7
//! Field ANEG - Auto-Negotiation present
#define PMA_DIP1_ANEG_MASK 0x80u

//! Field SEP_PMA_1 - Separate PMA (1)
#define PMA_DIP1_SEP_PMA_1_POS 8
//! Field SEP_PMA_1 - Separate PMA (1)
#define PMA_DIP1_SEP_PMA_1_MASK 0x100u

//! Field SEP_PMA_2 - Separate PMA (2)
#define PMA_DIP1_SEP_PMA_2_POS 9
//! Field SEP_PMA_2 - Separate PMA (2)
#define PMA_DIP1_SEP_PMA_2_MASK 0x200u

//! Field SEP_PMA_3 - Separate PMA (3)
#define PMA_DIP1_SEP_PMA_3_POS 10
//! Field SEP_PMA_3 - Separate PMA (3)
#define PMA_DIP1_SEP_PMA_3_MASK 0x400u

//! Field SEP_PMA_4 - Separate PMA (4)
#define PMA_DIP1_SEP_PMA_4_POS 11
//! Field SEP_PMA_4 - Separate PMA (4)
#define PMA_DIP1_SEP_PMA_4_MASK 0x800u

//! Field RES - Reserved
#define PMA_DIP1_RES_POS 12
//! Field RES - Reserved
#define PMA_DIP1_RES_MASK 0xF000u

//! @}

//! \defgroup PMA_DIP2 Register PMA_DIP2 - Devices in package 2 (Register 1.6)
//! @{

//! Register Offset (relative)
#define PMA_DIP2 0xC
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_DIP2 0x0020000Cu

//! Register Reset Value
#define PMA_DIP2_RST 0xC000u

//! Field RES - Reserved
#define PMA_DIP2_RES_POS 0
//! Field RES - Reserved
#define PMA_DIP2_RES_MASK 0x1FFFu

//! Field CLA_22_EXT - Clause 22 extension
#define PMA_DIP2_CLA_22_EXT_POS 13
//! Field CLA_22_EXT - Clause 22 extension
#define PMA_DIP2_CLA_22_EXT_MASK 0x2000u

//! Field VSPEC1 - Vendor-specific device 1
#define PMA_DIP2_VSPEC1_POS 14
//! Field VSPEC1 - Vendor-specific device 1
#define PMA_DIP2_VSPEC1_MASK 0x4000u

//! Field VSPEC2 - Vendor-specific device 2
#define PMA_DIP2_VSPEC2_POS 15
//! Field VSPEC2 - Vendor-specific device 2
#define PMA_DIP2_VSPEC2_MASK 0x8000u

//! @}

//! \defgroup PMA_CTL2 Register PMA_CTL2 - PMA/PMD control 2 (Register 1.7)
//! @{

//! Register Offset (relative)
#define PMA_CTL2 0xE
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_CTL2 0x0020000Eu

//! Register Reset Value
#define PMA_CTL2_RST 0x0030u

//! Field PMA_PMD_TYPE_SEL - PMA/PMD type selection
#define PMA_CTL2_PMA_PMD_TYPE_SEL_POS 0
//! Field PMA_PMD_TYPE_SEL - PMA/PMD type selection
#define PMA_CTL2_PMA_PMD_TYPE_SEL_MASK 0x3Fu

//! @}

//! \defgroup PMA_STAT2 Register PMA_STAT2 - PMA/PMD status 2 (Register 1.8)
//! @{

//! Register Offset (relative)
#define PMA_STAT2 0x10
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_STAT2 0x00200010u

//! Register Reset Value
#define PMA_STAT2_RST 0x8200u

//! Field PMA_LOCAL_LOOPBACK - PMA Local Loop-back
#define PMA_STAT2_PMA_LOCAL_LOOPBACK_POS 0
//! Field PMA_LOCAL_LOOPBACK - PMA Local Loop-back
#define PMA_STAT2_PMA_LOCAL_LOOPBACK_MASK 0x1u

//! Field RMGBT_EW_ABILITY - MULTIGBASE-EW ability
#define PMA_STAT2_RMGBT_EW_ABILITY_POS 1
//! Field RMGBT_EW_ABILITY - MULTIGBASE-EW ability
#define PMA_STAT2_RMGBT_EW_ABILITY_MASK 0x2u

//! Field RMGBT_LW_ABILITY - MULTIGBASE-LW ability
#define PMA_STAT2_RMGBT_LW_ABILITY_POS 2
//! Field RMGBT_LW_ABILITY - MULTIGBASE-LW ability
#define PMA_STAT2_RMGBT_LW_ABILITY_MASK 0x4u

//! Field RMGBT_SW_ABILITY - MULTIGBASE-SW ability
#define PMA_STAT2_RMGBT_SW_ABILITY_POS 3
//! Field RMGBT_SW_ABILITY - MULTIGBASE-SW ability
#define PMA_STAT2_RMGBT_SW_ABILITY_MASK 0x8u

//! Field RMGBT_LX4_ABILITY - MULTIGBASE-LX4 ability
#define PMA_STAT2_RMGBT_LX4_ABILITY_POS 4
//! Field RMGBT_LX4_ABILITY - MULTIGBASE-LX4 ability
#define PMA_STAT2_RMGBT_LX4_ABILITY_MASK 0x10u

//! Field RMGBT_ER_ABILITY - MULTIGBASE-ER ability
#define PMA_STAT2_RMGBT_ER_ABILITY_POS 5
//! Field RMGBT_ER_ABILITY - MULTIGBASE-ER ability
#define PMA_STAT2_RMGBT_ER_ABILITY_MASK 0x20u

//! Field RMGBT_LR_ABILITY - MULTIGBASE-LR ability
#define PMA_STAT2_RMGBT_LR_ABILITY_POS 6
//! Field RMGBT_LR_ABILITY - MULTIGBASE-LR ability
#define PMA_STAT2_RMGBT_LR_ABILITY_MASK 0x40u

//! Field RMGBT_SR_ABILITY - MULTIGBASE-SR ability
#define PMA_STAT2_RMGBT_SR_ABILITY_POS 7
//! Field RMGBT_SR_ABILITY - MULTIGBASE-SR ability
#define PMA_STAT2_RMGBT_SR_ABILITY_MASK 0x80u

//! Field PMD_TX_DISABLE - PMD transmit disable
#define PMA_STAT2_PMD_TX_DISABLE_POS 8
//! Field PMD_TX_DISABLE - PMD transmit disable
#define PMA_STAT2_PMD_TX_DISABLE_MASK 0x100u

//! Field EXT_ABILITIES - Extended abilities
#define PMA_STAT2_EXT_ABILITIES_POS 9
//! Field EXT_ABILITIES - Extended abilities
#define PMA_STAT2_EXT_ABILITIES_MASK 0x200u

//! Field RX_FAULT - Receive fault
#define PMA_STAT2_RX_FAULT_POS 10
//! Field RX_FAULT - Receive fault
#define PMA_STAT2_RX_FAULT_MASK 0x400u

//! Field TX_FAULT - Transmit fault
#define PMA_STAT2_TX_FAULT_POS 11
//! Field TX_FAULT - Transmit fault
#define PMA_STAT2_TX_FAULT_MASK 0x800u

//! Field RX_FAULT_ABILITY - Receive fault ability
#define PMA_STAT2_RX_FAULT_ABILITY_POS 12
//! Field RX_FAULT_ABILITY - Receive fault ability
#define PMA_STAT2_RX_FAULT_ABILITY_MASK 0x1000u

//! Field TX_FAULT_ABILITY - Transmit fault ability
#define PMA_STAT2_TX_FAULT_ABILITY_POS 13
//! Field TX_FAULT_ABILITY - Transmit fault ability
#define PMA_STAT2_TX_FAULT_ABILITY_MASK 0x2000u

//! Field DEVICE_PRESENT - Device present
#define PMA_STAT2_DEVICE_PRESENT_POS 14
//! Field DEVICE_PRESENT - Device present
#define PMA_STAT2_DEVICE_PRESENT_MASK 0xC000u

//! @}

//! \defgroup PMA_EXT_ABILITY Register PMA_EXT_ABILITY - PMA/PMD Extended Ability (Register 1.11)
//! @{

//! Register Offset (relative)
#define PMA_EXT_ABILITY 0x16
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_EXT_ABILITY 0x00200016u

//! Register Reset Value
#define PMA_EXT_ABILITY_RST 0x41A0u

//! Field RMGBT_CX4_ABILITY - MULTIGBASE-CX4 ability
#define PMA_EXT_ABILITY_RMGBT_CX4_ABILITY_POS 0
//! Field RMGBT_CX4_ABILITY - MULTIGBASE-CX4 ability
#define PMA_EXT_ABILITY_RMGBT_CX4_ABILITY_MASK 0x1u

//! Field RMGBT_LRM_ABILITY - MULTIGBASE-LRM ability
#define PMA_EXT_ABILITY_RMGBT_LRM_ABILITY_POS 1
//! Field RMGBT_LRM_ABILITY - MULTIGBASE-LRM ability
#define PMA_EXT_ABILITY_RMGBT_LRM_ABILITY_MASK 0x2u

//! Field RMGBT_ABILITY - 10GBASE-T ability
#define PMA_EXT_ABILITY_RMGBT_ABILITY_POS 2
//! Field RMGBT_ABILITY - 10GBASE-T ability
#define PMA_EXT_ABILITY_RMGBT_ABILITY_MASK 0x4u

//! Field RMGBT_KX4_ABILITY - MULTIGBASE-KX4 ability
#define PMA_EXT_ABILITY_RMGBT_KX4_ABILITY_POS 3
//! Field RMGBT_KX4_ABILITY - MULTIGBASE-KX4 ability
#define PMA_EXT_ABILITY_RMGBT_KX4_ABILITY_MASK 0x8u

//! Field RMGBT_KR_ABILITY - MULTIGBASE-KR ability
#define PMA_EXT_ABILITY_RMGBT_KR_ABILITY_POS 4
//! Field RMGBT_KR_ABILITY - MULTIGBASE-KR ability
#define PMA_EXT_ABILITY_RMGBT_KR_ABILITY_MASK 0x10u

//! Field R1000BASE_T_ABILITY - 1000BASE-T ability
#define PMA_EXT_ABILITY_R1000BASE_T_ABILITY_POS 5
//! Field R1000BASE_T_ABILITY - 1000BASE-T ability
#define PMA_EXT_ABILITY_R1000BASE_T_ABILITY_MASK 0x20u

//! Field R1000BASE_KX_ABILITY - 1000BASE-KX ability
#define PMA_EXT_ABILITY_R1000BASE_KX_ABILITY_POS 6
//! Field R1000BASE_KX_ABILITY - 1000BASE-KX ability
#define PMA_EXT_ABILITY_R1000BASE_KX_ABILITY_MASK 0x40u

//! Field R100BASE_TX_ABILITY - 100BASE-TX ability
#define PMA_EXT_ABILITY_R100BASE_TX_ABILITY_POS 7
//! Field R100BASE_TX_ABILITY - 100BASE-TX ability
#define PMA_EXT_ABILITY_R100BASE_TX_ABILITY_MASK 0x80u

//! Field R10BASE_T_ABILITY - 10BASE-T ability
#define PMA_EXT_ABILITY_R10BASE_T_ABILITY_POS 8
//! Field R10BASE_T_ABILITY - 10BASE-T ability
#define PMA_EXT_ABILITY_R10BASE_T_ABILITY_MASK 0x100u

//! Field P2MP_ABILITY - P2MP ability
#define PMA_EXT_ABILITY_P2MP_ABILITY_POS 9
//! Field P2MP_ABILITY - P2MP ability
#define PMA_EXT_ABILITY_P2MP_ABILITY_MASK 0x200u

//! Field R40G_100G_EXT_ABILITIES - 40G/100G extended abilities
#define PMA_EXT_ABILITY_R40G_100G_EXT_ABILITIES_POS 10
//! Field R40G_100G_EXT_ABILITIES - 40G/100G extended abilities
#define PMA_EXT_ABILITY_R40G_100G_EXT_ABILITIES_MASK 0x400u

//! Field R2G5_EXT_ABILITIES - 2.5G/5G extended abilities
#define PMA_EXT_ABILITY_R2G5_EXT_ABILITIES_POS 14
//! Field R2G5_EXT_ABILITIES - 2.5G/5G extended abilities
#define PMA_EXT_ABILITY_R2G5_EXT_ABILITIES_MASK 0x4000u

//! @}

//! \defgroup PMA_PACKID1 Register PMA_PACKID1 - AN package identifier (Register 1.14)
//! @{

//! Register Offset (relative)
#define PMA_PACKID1 0x1C
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_PACKID1 0x0020001Cu

//! Register Reset Value
#define PMA_PACKID1_RST 0x67C9u

//! Field OUI - Organizationally Unique Identifier
#define PMA_PACKID1_OUI_POS 0
//! Field OUI - Organizationally Unique Identifier
#define PMA_PACKID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup PMA_PACKID2 Register PMA_PACKID2 - AN package identifier (Register 1.15)
//! @{

//! Register Offset (relative)
#define PMA_PACKID2 0x1E
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_PACKID2 0x0020001Eu

//! Register Reset Value
#define PMA_PACKID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define PMA_PACKID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define PMA_PACKID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define PMA_PACKID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define PMA_PACKID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PMA_PACKID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define PMA_PACKID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup PMA_MGBT_EXTAB Register PMA_MGBT_EXTAB - PMAPMD Extended Ability (Register 1.21)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_EXTAB 0x2A
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_EXTAB 0x0020002Au

//! Register Reset Value
#define PMA_MGBT_EXTAB_RST 0x0001u

//! Field AB2G5 - PMA Ability to perform 2G5BT
#define PMA_MGBT_EXTAB_AB2G5_POS 0
//! Field AB2G5 - PMA Ability to perform 2G5BT
#define PMA_MGBT_EXTAB_AB2G5_MASK 0x1u
//! Constant UNABLE - PMA is not able to perform 2G5BT
#define CONST_PMA_MGBT_EXTAB_AB2G5_UNABLE 0x0
//! Constant ABLE - PMA Able to perform 2G5BT
#define CONST_PMA_MGBT_EXTAB_AB2G5_ABLE 0x1

//! Field AB5G - PMA Ability to perform 5GBT
#define PMA_MGBT_EXTAB_AB5G_POS 1
//! Field AB5G - PMA Ability to perform 5GBT
#define PMA_MGBT_EXTAB_AB5G_MASK 0x2u
//! Constant UNABLE - PMA is not able to perform 5GBT
#define CONST_PMA_MGBT_EXTAB_AB5G_UNABLE 0x0
//! Constant ABLE - PMA Able to perform 5GBT
#define CONST_PMA_MGBT_EXTAB_AB5G_ABLE 0x1

//! Field RES - Reserved
#define PMA_MGBT_EXTAB_RES_POS 2
//! Field RES - Reserved
#define PMA_MGBT_EXTAB_RES_MASK 0xFFFCu

//! @}

//! \defgroup PMA_MGBT_STAT Register PMA_MGBT_STAT - MULTIGBASE-T status (Register 1.129)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_STAT 0x102
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_STAT 0x00200102u

//! Register Reset Value
#define PMA_MGBT_STAT_RST 0x0000u

//! Field LP_INFORMATION_VALID - LP information valid
#define PMA_MGBT_STAT_LP_INFORMATION_VALID_POS 0
//! Field LP_INFORMATION_VALID - LP information valid
#define PMA_MGBT_STAT_LP_INFORMATION_VALID_MASK 0x1u

//! @}

//! \defgroup PMA_MGBT_POLARITY Register PMA_MGBT_POLARITY - MULTIGBASE-T pair swap and polarity (Register 1.130)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_POLARITY 0x104
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_POLARITY 0x00200104u

//! Register Reset Value
#define PMA_MGBT_POLARITY_RST 0x0003u

//! Field MDI_MDI_X - MDI/MDI-X
#define PMA_MGBT_POLARITY_MDI_MDI_X_POS 0
//! Field MDI_MDI_X - MDI/MDI-X
#define PMA_MGBT_POLARITY_MDI_MDI_X_MASK 0x3u
//! Constant ABCDCROSS - Pair AB and Pair CD crossover
#define CONST_PMA_MGBT_POLARITY_MDI_MDI_X_ABCDCROSS 0x0
//! Constant CDCROSS - Pair CD crossover only
#define CONST_PMA_MGBT_POLARITY_MDI_MDI_X_CDCROSS 0x1
//! Constant ABCROSS - Pair AB crossover only
#define CONST_PMA_MGBT_POLARITY_MDI_MDI_X_ABCROSS 0x2
//! Constant NORMAL - No crossover
#define CONST_PMA_MGBT_POLARITY_MDI_MDI_X_NORMAL 0x3

//! Field PAIR_A_POLARITY - Pair A polarity
#define PMA_MGBT_POLARITY_PAIR_A_POLARITY_POS 8
//! Field PAIR_A_POLARITY - Pair A polarity
#define PMA_MGBT_POLARITY_PAIR_A_POLARITY_MASK 0x100u

//! Field PAIR_B_POLARITY - Pair B polarity
#define PMA_MGBT_POLARITY_PAIR_B_POLARITY_POS 9
//! Field PAIR_B_POLARITY - Pair B polarity
#define PMA_MGBT_POLARITY_PAIR_B_POLARITY_MASK 0x200u

//! Field PAIR_C_POLARITY - Pair C polarity
#define PMA_MGBT_POLARITY_PAIR_C_POLARITY_POS 10
//! Field PAIR_C_POLARITY - Pair C polarity
#define PMA_MGBT_POLARITY_PAIR_C_POLARITY_MASK 0x400u

//! Field PAIR_D_POLARITY - Pair D polarity
#define PMA_MGBT_POLARITY_PAIR_D_POLARITY_POS 11
//! Field PAIR_D_POLARITY - Pair D polarity
#define PMA_MGBT_POLARITY_PAIR_D_POLARITY_MASK 0x800u

//! @}

//! \defgroup PMA_MGBT_TX_PBO Register PMA_MGBT_TX_PBO - MULTIGBASE-T TX power backoff and PHY short reach setting (Register 1.131)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_TX_PBO 0x106
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_TX_PBO 0x00200106u

//! Register Reset Value
#define PMA_MGBT_TX_PBO_RST 0x0000u

//! Field SHORT_REACH_MODE - Short reach mode
#define PMA_MGBT_TX_PBO_SHORT_REACH_MODE_POS 0
//! Field SHORT_REACH_MODE - Short reach mode
#define PMA_MGBT_TX_PBO_SHORT_REACH_MODE_MASK 0x1u

//! Field TX_POWER_BACKOFF - TX power backoff
#define PMA_MGBT_TX_PBO_TX_POWER_BACKOFF_POS 10
//! Field TX_POWER_BACKOFF - TX power backoff
#define PMA_MGBT_TX_PBO_TX_POWER_BACKOFF_MASK 0x1C00u

//! Field LP_TX - Link partner TX
#define PMA_MGBT_TX_PBO_LP_TX_POS 13
//! Field LP_TX - Link partner TX
#define PMA_MGBT_TX_PBO_LP_TX_MASK 0xE000u

//! @}

//! \defgroup PMA_MGBT_TEST_MODE Register PMA_MGBT_TEST_MODE - MULTIGBASE-T test mode (Register 1.132)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_TEST_MODE 0x108
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_TEST_MODE 0x00200108u

//! Register Reset Value
#define PMA_MGBT_TEST_MODE_RST 0x0000u

//! Field TXTER_TEST - Transmitter test
#define PMA_MGBT_TEST_MODE_TXTER_TEST_POS 10
//! Field TXTER_TEST - Transmitter test
#define PMA_MGBT_TEST_MODE_TXTER_TEST_MASK 0x1C00u

//! Field TEST_MODE_CTL - Test mode control
#define PMA_MGBT_TEST_MODE_TEST_MODE_CTL_POS 13
//! Field TEST_MODE_CTL - Test mode control
#define PMA_MGBT_TEST_MODE_TEST_MODE_CTL_MASK 0xE000u

//! @}

//! \defgroup PMA_MGBT_SNR_OPMARGIN_A Register PMA_MGBT_SNR_OPMARGIN_A - MULTIGBASE-T SNR Margin Channel A (Register 1.133)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SNR_OPMARGIN_A 0x10A
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SNR_OPMARGIN_A 0x0020010Au

//! Register Reset Value
#define PMA_MGBT_SNR_OPMARGIN_A_RST 0x0000u

//! Field OPMARGIN_A - OPMARGIN_A
#define PMA_MGBT_SNR_OPMARGIN_A_OPMARGIN_A_POS 0
//! Field OPMARGIN_A - OPMARGIN_A
#define PMA_MGBT_SNR_OPMARGIN_A_OPMARGIN_A_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_SNR_OPMARGIN_B Register PMA_MGBT_SNR_OPMARGIN_B - MULTIGBASE-T SNR Margin Channel B (Register 1.134)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SNR_OPMARGIN_B 0x10C
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SNR_OPMARGIN_B 0x0020010Cu

//! Register Reset Value
#define PMA_MGBT_SNR_OPMARGIN_B_RST 0x0000u

//! Field OPMARGIN_B - OPMARGIN_B
#define PMA_MGBT_SNR_OPMARGIN_B_OPMARGIN_B_POS 0
//! Field OPMARGIN_B - OPMARGIN_B
#define PMA_MGBT_SNR_OPMARGIN_B_OPMARGIN_B_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_SNR_OPMARGIN_C Register PMA_MGBT_SNR_OPMARGIN_C - MULTIGBASE-T SNR Margin Channel C (Register 1.135)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SNR_OPMARGIN_C 0x10E
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SNR_OPMARGIN_C 0x0020010Eu

//! Register Reset Value
#define PMA_MGBT_SNR_OPMARGIN_C_RST 0x0000u

//! Field OPMARGIN_C - OPMARGIN_C
#define PMA_MGBT_SNR_OPMARGIN_C_OPMARGIN_C_POS 0
//! Field OPMARGIN_C - OPMARGIN_C
#define PMA_MGBT_SNR_OPMARGIN_C_OPMARGIN_C_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_SNR_OPMARGIN_D Register PMA_MGBT_SNR_OPMARGIN_D - MULTIGBASE-T SNR Margin Channel D (Register 1.136)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SNR_OPMARGIN_D 0x110
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SNR_OPMARGIN_D 0x00200110u

//! Register Reset Value
#define PMA_MGBT_SNR_OPMARGIN_D_RST 0x0000u

//! Field OPMARGIN_D - OPMARGIN_D
#define PMA_MGBT_SNR_OPMARGIN_D_OPMARGIN_D_POS 0
//! Field OPMARGIN_D - OPMARGIN_D
#define PMA_MGBT_SNR_OPMARGIN_D_OPMARGIN_D_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_MINMARGIN_A Register PMA_MGBT_MINMARGIN_A - MULTIGBASE-T SNR Min Margin Channel A (Register 1.137)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_MINMARGIN_A 0x112
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_MINMARGIN_A 0x00200112u

//! Register Reset Value
#define PMA_MGBT_MINMARGIN_A_RST 0x0000u

//! Field MINMARGIN_A - MINMARGIN_A
#define PMA_MGBT_MINMARGIN_A_MINMARGIN_A_POS 0
//! Field MINMARGIN_A - MINMARGIN_A
#define PMA_MGBT_MINMARGIN_A_MINMARGIN_A_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_MINMARGIN_B Register PMA_MGBT_MINMARGIN_B - MULTIGBASE-T SNR Min Margin Channel B (Register 1.138)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_MINMARGIN_B 0x114
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_MINMARGIN_B 0x00200114u

//! Register Reset Value
#define PMA_MGBT_MINMARGIN_B_RST 0x0000u

//! Field MINMARGIN_B - MINMARGIN_B
#define PMA_MGBT_MINMARGIN_B_MINMARGIN_B_POS 0
//! Field MINMARGIN_B - MINMARGIN_B
#define PMA_MGBT_MINMARGIN_B_MINMARGIN_B_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_MINMARGIN_C Register PMA_MGBT_MINMARGIN_C - MULTIGBASE-T SNR Min Margin Chan C (Register 1.139)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_MINMARGIN_C 0x116
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_MINMARGIN_C 0x00200116u

//! Register Reset Value
#define PMA_MGBT_MINMARGIN_C_RST 0x0000u

//! Field MINMARGIN_C - MINMARGIN_C
#define PMA_MGBT_MINMARGIN_C_MINMARGIN_C_POS 0
//! Field MINMARGIN_C - MINMARGIN_C
#define PMA_MGBT_MINMARGIN_C_MINMARGIN_C_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_MINMARGIN_D Register PMA_MGBT_MINMARGIN_D - MULTIGBASE-T SNR Min Margin Chan D (Register 1.140)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_MINMARGIN_D 0x118
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_MINMARGIN_D 0x00200118u

//! Register Reset Value
#define PMA_MGBT_MINMARGIN_D_RST 0x0000u

//! Field MINMARGIN_D - MINMARGIN_D
#define PMA_MGBT_MINMARGIN_D_MINMARGIN_D_POS 0
//! Field MINMARGIN_D - MINMARGIN_D
#define PMA_MGBT_MINMARGIN_D_MINMARGIN_D_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_POWER_A Register PMA_MGBT_POWER_A - MULTIGBASE-T Rx Power Channel A (Register 1.141)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_POWER_A 0x11A
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_POWER_A 0x0020011Au

//! Register Reset Value
#define PMA_MGBT_POWER_A_RST 0x0000u

//! Field POWER_A - POWER_A
#define PMA_MGBT_POWER_A_POWER_A_POS 0
//! Field POWER_A - POWER_A
#define PMA_MGBT_POWER_A_POWER_A_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_POWER_B Register PMA_MGBT_POWER_B - MULTIGBASE-T Rx Power Channel B (Register 1.142)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_POWER_B 0x11C
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_POWER_B 0x0020011Cu

//! Register Reset Value
#define PMA_MGBT_POWER_B_RST 0x0000u

//! Field POWER_B - POWER_B
#define PMA_MGBT_POWER_B_POWER_B_POS 0
//! Field POWER_B - POWER_B
#define PMA_MGBT_POWER_B_POWER_B_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_POWER_C Register PMA_MGBT_POWER_C - MULTIGBASE-T Rx Power Chan C (Register 1.143)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_POWER_C 0x11E
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_POWER_C 0x0020011Eu

//! Register Reset Value
#define PMA_MGBT_POWER_C_RST 0x0000u

//! Field POWER_C - POWER_C
#define PMA_MGBT_POWER_C_POWER_C_POS 0
//! Field POWER_C - POWER_C
#define PMA_MGBT_POWER_C_POWER_C_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_POWER_D Register PMA_MGBT_POWER_D - MULTIGBASE-T Rx Power Chan D (Register 1.144)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_POWER_D 0x120
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_POWER_D 0x00200120u

//! Register Reset Value
#define PMA_MGBT_POWER_D_RST 0x0000u

//! Field POWER_D - POWER_D
#define PMA_MGBT_POWER_D_POWER_D_POS 0
//! Field POWER_D - POWER_D
#define PMA_MGBT_POWER_D_POWER_D_MASK 0xFFFFu

//! @}

//! \defgroup PMA_MGBT_SKEW_DELAY_0 Register PMA_MGBT_SKEW_DELAY_0 - MULTIGBASE-T skew delay 0 (Register 1.145)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SKEW_DELAY_0 0x122
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SKEW_DELAY_0 0x00200122u

//! Register Reset Value
#define PMA_MGBT_SKEW_DELAY_0_RST 0x0000u

//! Field SKEW_DELAY_B - Skew delay B
#define PMA_MGBT_SKEW_DELAY_0_SKEW_DELAY_B_POS 8
//! Field SKEW_DELAY_B - Skew delay B
#define PMA_MGBT_SKEW_DELAY_0_SKEW_DELAY_B_MASK 0x7F00u

//! @}

//! \defgroup PMA_MGBT_SKEW_DELAY_1 Register PMA_MGBT_SKEW_DELAY_1 - MULTIGBASE-T skew delay 1 (Register 1.146)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_SKEW_DELAY_1 0x124
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_SKEW_DELAY_1 0x00200124u

//! Register Reset Value
#define PMA_MGBT_SKEW_DELAY_1_RST 0x0000u

//! Field SKEW_DELAY_C - Skew delay C
#define PMA_MGBT_SKEW_DELAY_1_SKEW_DELAY_C_POS 0
//! Field SKEW_DELAY_C - Skew delay C
#define PMA_MGBT_SKEW_DELAY_1_SKEW_DELAY_C_MASK 0x7Fu

//! Field SKEW_DELAY_D - Skew delay D
#define PMA_MGBT_SKEW_DELAY_1_SKEW_DELAY_D_POS 8
//! Field SKEW_DELAY_D - Skew delay D
#define PMA_MGBT_SKEW_DELAY_1_SKEW_DELAY_D_MASK 0x7F00u

//! @}

//! \defgroup PMA_MGBT_FAST_RETRAIN_STA_CTRL Register PMA_MGBT_FAST_RETRAIN_STA_CTRL - MULTIGBASE-T skew delay 2 (Register 1.147)
//! @{

//! Register Offset (relative)
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL 0x126
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_MGBT_FAST_RETRAIN_STA_CTRL 0x00200126u

//! Register Reset Value
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_RST 0x0000u

//! Field FAST_RETRAIN_ENABLE - Fast retrain enable
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_ENABLE_POS 0
//! Field FAST_RETRAIN_ENABLE - Fast retrain enable
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_ENABLE_MASK 0x1u

//! Field FAST_RETRAIN_SIG_TYPE - Fast retrain signal type
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_SIG_TYPE_POS 1
//! Field FAST_RETRAIN_SIG_TYPE - Fast retrain signal type
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_SIG_TYPE_MASK 0x6u

//! Field FAST_RETRAIN_NEGOTIATED - Fast retrain negotiated
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_NEGOTIATED_POS 3
//! Field FAST_RETRAIN_NEGOTIATED - Fast retrain negotiated
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_NEGOTIATED_MASK 0x8u

//! Field FAST_RETRAIN_ABILITY - Fast retrain ability
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_ABILITY_POS 4
//! Field FAST_RETRAIN_ABILITY - Fast retrain ability
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_FAST_RETRAIN_ABILITY_MASK 0x10u

//! Field LD_FAST_RETRAIN_COUNT - LD fast retrain count
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_LD_FAST_RETRAIN_COUNT_POS 6
//! Field LD_FAST_RETRAIN_COUNT - LD fast retrain count
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_LD_FAST_RETRAIN_COUNT_MASK 0x7C0u

//! Field LP_FAST_RETRAIN_COUNT - LP fast retrain count
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_LP_FAST_RETRAIN_COUNT_POS 11
//! Field LP_FAST_RETRAIN_COUNT - LP fast retrain count
#define PMA_MGBT_FAST_RETRAIN_STA_CTRL_LP_FAST_RETRAIN_COUNT_MASK 0xF800u

//! @}

//! \defgroup PMA_TIMESYNC_CAP Register PMA_TIMESYNC_CAP - PMA TimeSync Capability Indication (Register 1.1800)
//! @{

//! Register Offset (relative)
#define PMA_TIMESYNC_CAP 0xE10
//! Register Offset (absolute) for 1st Instance PMAPMD
#define PMAPMD_PMA_TIMESYNC_CAP 0x00200E10u

//! Register Reset Value
#define PMA_TIMESYNC_CAP_RST 0x0000u

//! Field RXDEL - Receive Data Path Delay Information
#define PMA_TIMESYNC_CAP_RXDEL_POS 0
//! Field RXDEL - Receive Data Path Delay Information
#define PMA_TIMESYNC_CAP_RXDEL_MASK 0x1u
//! Constant NONE - PHYs do not have this capability
#define CONST_PMA_TIMESYNC_CAP_RXDEL_NONE 0x0
//! Constant CAPABLE - min and max RX data path delay available
#define CONST_PMA_TIMESYNC_CAP_RXDEL_CAPABLE 0x1

//! Field TXDEL - Transmit Data Path Delay Information
#define PMA_TIMESYNC_CAP_TXDEL_POS 1
//! Field TXDEL - Transmit Data Path Delay Information
#define PMA_TIMESYNC_CAP_TXDEL_MASK 0x2u
//! Constant NONE - PHYs do not have this capability
#define CONST_PMA_TIMESYNC_CAP_TXDEL_NONE 0x0
//! Constant CAPABLE - min and max TX data path delay available
#define CONST_PMA_TIMESYNC_CAP_TXDEL_CAPABLE 0x1

//! @}

//! @}

#endif
