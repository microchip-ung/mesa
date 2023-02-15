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
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/aneg_def.xml
// Register File Name  : ANEG
// Register File Title : Standard Auto-Negotiation Registers for MMD=0x07
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _ANEG_H
#define _ANEG_H

//! \defgroup ANEG Register File ANEG - Standard Auto-Negotiation Registers for MMD=0x07
//! @{

//! Base Address of ANEG
#define ANEG_MODULE_BASE 0x00E00000u

//! \defgroup ANEG_CTRL Register ANEG_CTRL - Auto-Negotiation Control (Register 7.0)
//! @{

//! Register Offset (relative)
#define ANEG_CTRL 0x0
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_CTRL 0x00E00000u

//! Register Reset Value
#define ANEG_CTRL_RST 0x3000u

//! Field RES1 - Reserved
#define ANEG_CTRL_RES1_POS 0
//! Field RES1 - Reserved
#define ANEG_CTRL_RES1_MASK 0x1FFu

//! Field ANEG_RESTART - Restart Auto-Negotiation
#define ANEG_CTRL_ANEG_RESTART_POS 9
//! Field ANEG_RESTART - Restart Auto-Negotiation
#define ANEG_CTRL_ANEG_RESTART_MASK 0x200u
//! Constant ZERO - Normal Operation
#define CONST_ANEG_CTRL_ANEG_RESTART_ZERO 0x0
//! Constant RESTART - Restart Auto-Negotiation process
#define CONST_ANEG_CTRL_ANEG_RESTART_RESTART 0x1

//! Field RES2 - Reserved
#define ANEG_CTRL_RES2_POS 10
//! Field RES2 - Reserved
#define ANEG_CTRL_RES2_MASK 0xC00u

//! Field ANEG_ENAB - Auto-Negotiation Enable
#define ANEG_CTRL_ANEG_ENAB_POS 12
//! Field ANEG_ENAB - Auto-Negotiation Enable
#define ANEG_CTRL_ANEG_ENAB_MASK 0x1000u
//! Constant ZERO - disable auto-negotiation process
#define CONST_ANEG_CTRL_ANEG_ENAB_ZERO 0x0
//! Constant ONE - enable auto-negotiation process
#define CONST_ANEG_CTRL_ANEG_ENAB_ONE 0x1

//! Field XNP - Extended Next Page Control
#define ANEG_CTRL_XNP_POS 13
//! Field XNP - Extended Next Page Control
#define ANEG_CTRL_XNP_MASK 0x2000u
//! Constant ZERO - Extended Next Page is disabled
#define CONST_ANEG_CTRL_XNP_ZERO 0x0
//! Constant ONE - Extended Next Page is enabled
#define CONST_ANEG_CTRL_XNP_ONE 0x1

//! Field RES3 - Reserved
#define ANEG_CTRL_RES3_POS 14
//! Field RES3 - Reserved
#define ANEG_CTRL_RES3_MASK 0x4000u

//! Field RST - Reset
#define ANEG_CTRL_RST_POS 15
//! Field RST - Reset
#define ANEG_CTRL_RST_MASK 0x8000u
//! Constant NORMAL - GPY Normal Operation
#define CONST_ANEG_CTRL_RST_NORMAL 0x0
//! Constant RESET - GPY Reset
#define CONST_ANEG_CTRL_RST_RESET 0x1

//! @}

//! \defgroup ANEG_STAT Register ANEG_STAT - Auto-Negotiation Status (Register 7.1)
//! @{

//! Register Offset (relative)
#define ANEG_STAT 0x2
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_STAT 0x00E00002u

//! Register Reset Value
#define ANEG_STAT_RST 0x0008u

//! Field LP_ANEG_ABLE - Link partner auto-negotiation ability
#define ANEG_STAT_LP_ANEG_ABLE_POS 0
//! Field LP_ANEG_ABLE - Link partner auto-negotiation ability
#define ANEG_STAT_LP_ANEG_ABLE_MASK 0x1u
//! Constant UNABLE - Link partner is not capable of auto-negotiation.
#define CONST_ANEG_STAT_LP_ANEG_ABLE_UNABLE 0x0
//! Constant ABLE - Link partner is capable of auto-negotiation
#define CONST_ANEG_STAT_LP_ANEG_ABLE_ABLE 0x1

//! Field RES1 - Value always zero, write ignored
#define ANEG_STAT_RES1_POS 1
//! Field RES1 - Value always zero, write ignored
#define ANEG_STAT_RES1_MASK 0x2u

//! Field LINKSTA - Link Status
#define ANEG_STAT_LINKSTA_POS 2
//! Field LINKSTA - Link Status
#define ANEG_STAT_LINKSTA_MASK 0x4u
//! Constant DOWN - Link is down
#define CONST_ANEG_STAT_LINKSTA_DOWN 0x0
//! Constant UP - Link is Up
#define CONST_ANEG_STAT_LINKSTA_UP 0x1

//! Field ANEG_ABLE - Auto-Negotiation Ability
#define ANEG_STAT_ANEG_ABLE_POS 3
//! Field ANEG_ABLE - Auto-Negotiation Ability
#define ANEG_STAT_ANEG_ABLE_MASK 0x8u
//! Constant UNABLE - PHY is not able to perform Auto-Negotiation
#define CONST_ANEG_STAT_ANEG_ABLE_UNABLE 0x0
//! Constant ABLE - PHY is able to perform Auto-Negotiation
#define CONST_ANEG_STAT_ANEG_ABLE_ABLE 0x1

//! Field ANEG_RF - Remote Fault
#define ANEG_STAT_ANEG_RF_POS 4
//! Field ANEG_RF - Remote Fault
#define ANEG_STAT_ANEG_RF_MASK 0x10u
//! Constant NORMAL - No remote fault condition detected
#define CONST_ANEG_STAT_ANEG_RF_NORMAL 0x0
//! Constant FAULT - Remote fault condition detected
#define CONST_ANEG_STAT_ANEG_RF_FAULT 0x1

//! Field ANEG_COMPLETE - Auto-Negotiation Complete
#define ANEG_STAT_ANEG_COMPLETE_POS 5
//! Field ANEG_COMPLETE - Auto-Negotiation Complete
#define ANEG_STAT_ANEG_COMPLETE_MASK 0x20u
//! Constant ZERO - Auto-Negotiation process has not completed
#define CONST_ANEG_STAT_ANEG_COMPLETE_ZERO 0x0
//! Constant ONE - Auto-Negotiation process has completed
#define CONST_ANEG_STAT_ANEG_COMPLETE_ONE 0x1

//! Field PR - Page Received
#define ANEG_STAT_PR_POS 6
//! Field PR - Page Received
#define ANEG_STAT_PR_MASK 0x40u
//! Constant ZERO - A page has not been received
#define CONST_ANEG_STAT_PR_ZERO 0x0
//! Constant ONE - A page has been received
#define CONST_ANEG_STAT_PR_ONE 0x1

//! Field XNPS - Extended Next Page Status
#define ANEG_STAT_XNPS_POS 7
//! Field XNPS - Extended Next Page Status
#define ANEG_STAT_XNPS_MASK 0x80u
//! Constant ZERO - Extended Next Page is not allowed.
#define CONST_ANEG_STAT_XNPS_ZERO 0x0
//! Constant ONE - Extended Next Page format is used.
#define CONST_ANEG_STAT_XNPS_ONE 0x1

//! Field RES2 - Reserved
#define ANEG_STAT_RES2_POS 8
//! Field RES2 - Reserved
#define ANEG_STAT_RES2_MASK 0x100u

//! Field PDF - Parallel detection fault
#define ANEG_STAT_PDF_POS 9
//! Field PDF - Parallel detection fault
#define ANEG_STAT_PDF_MASK 0x200u
//! Constant NOFAULT - No fault was detected.
#define CONST_ANEG_STAT_PDF_NOFAULT 0x0
//! Constant FAULT - Fault is detected via the parallel detection
#define CONST_ANEG_STAT_PDF_FAULT 0x1

//! Field RES3 - Reserved
#define ANEG_STAT_RES3_POS 10
//! Field RES3 - Reserved
#define ANEG_STAT_RES3_MASK 0xFC00u

//! @}

//! \defgroup ANEG_DEVID1 Register ANEG_DEVID1 - PHY Identifier 1 (Register 7.2)
//! @{

//! Register Offset (relative)
#define ANEG_DEVID1 0x4
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_DEVID1 0x00E00004u

//! Register Reset Value
#define ANEG_DEVID1_RST 0x67C9u

//! Field OUI - Organizationally Unique Identifier
#define ANEG_DEVID1_OUI_POS 0
//! Field OUI - Organizationally Unique Identifier
#define ANEG_DEVID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_DEVID2 Register ANEG_DEVID2 - PHY Identifier 2 (Register 7.3)
//! @{

//! Register Offset (relative)
#define ANEG_DEVID2 0x6
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_DEVID2 0x00E00006u

//! Register Reset Value
#define ANEG_DEVID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define ANEG_DEVID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define ANEG_DEVID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define ANEG_DEVID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define ANEG_DEVID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier
#define ANEG_DEVID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier
#define ANEG_DEVID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup ANEG_DIP1 Register ANEG_DIP1 - Device in Package 1 (Register 7.5)
//! @{

//! Register Offset (relative)
#define ANEG_DIP1 0xA
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_DIP1 0x00E0000Au

//! Register Reset Value
#define ANEG_DIP1_RST 0x008Bu

//! Field CL22 - Clause 22 register present in package
#define ANEG_DIP1_CL22_POS 0
//! Field CL22 - Clause 22 register present in package
#define ANEG_DIP1_CL22_MASK 0x1u
//! Constant ABSENT - Clause 22 registers no present in package
#define CONST_ANEG_DIP1_CL22_ABSENT 0x0
//! Constant PRESENT - Clause 22 registers present in package
#define CONST_ANEG_DIP1_CL22_PRESENT 0x1

//! Field PMAPMD - PMA PMD presence in package
#define ANEG_DIP1_PMAPMD_POS 1
//! Field PMAPMD - PMA PMD presence in package
#define ANEG_DIP1_PMAPMD_MASK 0x2u
//! Constant ABSENT - PMA PMD registers not present in package
#define CONST_ANEG_DIP1_PMAPMD_ABSENT 0x0
//! Constant PRESENT - PMA PMD registers present in package
#define CONST_ANEG_DIP1_PMAPMD_PRESENT 0x1

//! Field WIS - WIS present in package
#define ANEG_DIP1_WIS_POS 2
//! Field WIS - WIS present in package
#define ANEG_DIP1_WIS_MASK 0x4u
//! Constant ABSENT - WIS registers present in package
#define CONST_ANEG_DIP1_WIS_ABSENT 0x0
//! Constant PRESENT - WIS registers present in package
#define CONST_ANEG_DIP1_WIS_PRESENT 0x1

//! Field PCS - PCS present in package
#define ANEG_DIP1_PCS_POS 3
//! Field PCS - PCS present in package
#define ANEG_DIP1_PCS_MASK 0x8u
//! Constant ABSENT - PCS registers not present in package
#define CONST_ANEG_DIP1_PCS_ABSENT 0x0
//! Constant PRESENT - PCS registers present in package
#define CONST_ANEG_DIP1_PCS_PRESENT 0x1

//! Field PHYXS - PHYXS present in package
#define ANEG_DIP1_PHYXS_POS 4
//! Field PHYXS - PHYXS present in package
#define ANEG_DIP1_PHYXS_MASK 0x10u
//! Constant ABSENT - PHYXS registers not present in package
#define CONST_ANEG_DIP1_PHYXS_ABSENT 0x0
//! Constant PRESENT - PHYXS registers present in package
#define CONST_ANEG_DIP1_PHYXS_PRESENT 0x1

//! Field DTEXS - DTE XS present in package
#define ANEG_DIP1_DTEXS_POS 5
//! Field DTEXS - DTE XS present in package
#define ANEG_DIP1_DTEXS_MASK 0x20u
//! Constant ABSENT - DTE XS registers not present in package
#define CONST_ANEG_DIP1_DTEXS_ABSENT 0x0
//! Constant PRESENT - DTE XS registers present in package
#define CONST_ANEG_DIP1_DTEXS_PRESENT 0x1

//! Field TC - TC present in package
#define ANEG_DIP1_TC_POS 6
//! Field TC - TC present in package
#define ANEG_DIP1_TC_MASK 0x40u
//! Constant ABSENT - TC registers not present in package
#define CONST_ANEG_DIP1_TC_ABSENT 0x0
//! Constant PRESENT - TC registers present in package
#define CONST_ANEG_DIP1_TC_PRESENT 0x1

//! Field ANEG - Auto-negotiation present in package
#define ANEG_DIP1_ANEG_POS 7
//! Field ANEG - Auto-negotiation present in package
#define ANEG_DIP1_ANEG_MASK 0x80u
//! Constant ABSENT - ANEG not present inn package
#define CONST_ANEG_DIP1_ANEG_ABSENT 0x0
//! Constant PRESENT - ANEG present in package
#define CONST_ANEG_DIP1_ANEG_PRESENT 0x1

//! Field PMA1 - Separate PMA1 present in package
#define ANEG_DIP1_PMA1_POS 8
//! Field PMA1 - Separate PMA1 present in package
#define ANEG_DIP1_PMA1_MASK 0x100u
//! Constant ABSENT - Separate PMA1 not present inn package
#define CONST_ANEG_DIP1_PMA1_ABSENT 0x0
//! Constant PRESENT - Separate PMA1 present in package
#define CONST_ANEG_DIP1_PMA1_PRESENT 0x1

//! Field PMA2 - Separate PMA2 present in package
#define ANEG_DIP1_PMA2_POS 9
//! Field PMA2 - Separate PMA2 present in package
#define ANEG_DIP1_PMA2_MASK 0x200u
//! Constant ABSENT - Separate PMA2 not present in package
#define CONST_ANEG_DIP1_PMA2_ABSENT 0x0
//! Constant PRESENT - Separate PMA2 present in package
#define CONST_ANEG_DIP1_PMA2_PRESENT 0x1

//! Field PMA3 - Separate PMA3 present in package
#define ANEG_DIP1_PMA3_POS 10
//! Field PMA3 - Separate PMA3 present in package
#define ANEG_DIP1_PMA3_MASK 0x400u
//! Constant ABSENT - Separate PMA3 not present in package
#define CONST_ANEG_DIP1_PMA3_ABSENT 0x0
//! Constant PRESENT - Separate PMA3 present in package
#define CONST_ANEG_DIP1_PMA3_PRESENT 0x1

//! Field PMA4 - Separate PMA4 present in package
#define ANEG_DIP1_PMA4_POS 11
//! Field PMA4 - Separate PMA4 present in package
#define ANEG_DIP1_PMA4_MASK 0x800u
//! Constant ABSENT - Separate PMA4 not present in package
#define CONST_ANEG_DIP1_PMA4_ABSENT 0x0
//! Constant PRESENT - Separate PMA4 present in package
#define CONST_ANEG_DIP1_PMA4_PRESENT 0x1

//! Field RES - Reserved
#define ANEG_DIP1_RES_POS 12
//! Field RES - Reserved
#define ANEG_DIP1_RES_MASK 0xF000u

//! @}

//! \defgroup ANEG_DIP2 Register ANEG_DIP2 - Device in Package 2 (Register 7.6)
//! @{

//! Register Offset (relative)
#define ANEG_DIP2 0xC
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_DIP2 0x00E0000Cu

//! Register Reset Value
#define ANEG_DIP2_RST 0xC000u

//! Field RES - Reserved
#define ANEG_DIP2_RES_POS 0
//! Field RES - Reserved
#define ANEG_DIP2_RES_MASK 0x1FFFu

//! Field CL22EXT - Clause 22 extension present in package
#define ANEG_DIP2_CL22EXT_POS 13
//! Field CL22EXT - Clause 22 extension present in package
#define ANEG_DIP2_CL22EXT_MASK 0x2000u
//! Constant ABSENT - Clause 22 extension not present in package
#define CONST_ANEG_DIP2_CL22EXT_ABSENT 0x0
//! Constant PRESENT - Clause 22 extension present in package
#define CONST_ANEG_DIP2_CL22EXT_PRESENT 0x1

//! Field VSPEC1 - Vendor Specific Device 1 present in package
#define ANEG_DIP2_VSPEC1_POS 14
//! Field VSPEC1 - Vendor Specific Device 1 present in package
#define ANEG_DIP2_VSPEC1_MASK 0x4000u
//! Constant ABSENT - Vendor Specific Device 1 not present in package
#define CONST_ANEG_DIP2_VSPEC1_ABSENT 0x0
//! Constant PRESENT - Vendor Specific Device 1 present in package
#define CONST_ANEG_DIP2_VSPEC1_PRESENT 0x1

//! Field VSPEC2 - Vendor Specific Device 2 present in package
#define ANEG_DIP2_VSPEC2_POS 15
//! Field VSPEC2 - Vendor Specific Device 2 present in package
#define ANEG_DIP2_VSPEC2_MASK 0x8000u
//! Constant ABSENT - Vendor Specific Device 2 not present in package
#define CONST_ANEG_DIP2_VSPEC2_ABSENT 0x0
//! Constant PRESENT - Vendor Specific Device 2 present in package
#define CONST_ANEG_DIP2_VSPEC2_PRESENT 0x1

//! @}

//! \defgroup ANEG_PACKID1 Register ANEG_PACKID1 - AN package identifier (Register 7.14)
//! @{

//! Register Offset (relative)
#define ANEG_PACKID1 0x1C
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_PACKID1 0x00E0001Cu

//! Register Reset Value
#define ANEG_PACKID1_RST 0x67C9u

//! Field OUI - Organizationally Unique Identifier
#define ANEG_PACKID1_OUI_POS 0
//! Field OUI - Organizationally Unique Identifier
#define ANEG_PACKID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_PACKID2 Register ANEG_PACKID2 - AN package identifier (Register 7.15)
//! @{

//! Register Offset (relative)
#define ANEG_PACKID2 0x1E
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_PACKID2 0x00E0001Eu

//! Register Reset Value
#define ANEG_PACKID2_RST 0xDC00u

//! Field LDRN - Intel Device revision Number
#define ANEG_PACKID2_LDRN_POS 0
//! Field LDRN - Intel Device revision Number
#define ANEG_PACKID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define ANEG_PACKID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define ANEG_PACKID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define ANEG_PACKID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define ANEG_PACKID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup ANEG_ADV Register ANEG_ADV - ANEG Adv. for GPY (Register 7.16)
//! @{

//! Register Offset (relative)
#define ANEG_ADV 0x20
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_ADV 0x00E00020u

//! Register Reset Value
#define ANEG_ADV_RST 0x91E1u

//! Field SF - Selector Field
#define ANEG_ADV_SF_POS 0
//! Field SF - Selector Field
#define ANEG_ADV_SF_MASK 0x1Fu
//! Constant IEEE8023 - IEEE802.3
#define CONST_ANEG_ADV_SF_IEEE8023 0x1

//! Field TAF - Technology Ability Field
#define ANEG_ADV_TAF_POS 5
//! Field TAF - Technology Ability Field
#define ANEG_ADV_TAF_MASK 0xFE0u
//! Constant PS_ASYM - Advertise asymmetric pause
#define CONST_ANEG_ADV_TAF_PS_ASYM 0x40u
//! Constant PS_SYM - Advertise symmetric pause
#define CONST_ANEG_ADV_TAF_PS_SYM 0x20u
//! Constant DBT4 - Advertise 100BASE-T4
#define CONST_ANEG_ADV_TAF_DBT4 0x10u
//! Constant DBT_FDX - Advertise 100BASE-TX full duplex
#define CONST_ANEG_ADV_TAF_DBT_FDX 0x08u
//! Constant DBT_HDX - Advertise 100BASE-TX half duplex
#define CONST_ANEG_ADV_TAF_DBT_HDX 0x04u
//! Constant XBT_FDX - Advertise 10BASE-T full duplex
#define CONST_ANEG_ADV_TAF_XBT_FDX 0x02u
//! Constant XBT_HDX - Advertise 10BASE-T half duplex
#define CONST_ANEG_ADV_TAF_XBT_HDX 0x01u

//! Field XNP - Indicates that GPY supports transmission of Extended Next Pages
#define ANEG_ADV_XNP_POS 12
//! Field XNP - Indicates that GPY supports transmission of Extended Next Pages
#define ANEG_ADV_XNP_MASK 0x1000u
//! Constant UNABLE - GPY is XNP unable
#define CONST_ANEG_ADV_XNP_UNABLE 0x0
//! Constant ABLE - GPY is XNP able
#define CONST_ANEG_ADV_XNP_ABLE 0x1

//! Field RF - Remote Fault
#define ANEG_ADV_RF_POS 13
//! Field RF - Remote Fault
#define ANEG_ADV_RF_MASK 0x2000u

//! Field RES - Reserved
#define ANEG_ADV_RES_POS 14
//! Field RES - Reserved
#define ANEG_ADV_RES_MASK 0x4000u

//! Field NP - Next Page Able
#define ANEG_ADV_NP_POS 15
//! Field NP - Next Page Able
#define ANEG_ADV_NP_MASK 0x8000u
//! Constant INACTIVE - No Next page allowed
#define CONST_ANEG_ADV_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional Next Page will follow.
#define CONST_ANEG_ADV_NP_ACTIVE 0x1

//! @}

//! \defgroup ANEG_LP_BP_AB Register ANEG_LP_BP_AB - AN Link Partner Base Page Ability (Register 7.19)
//! @{

//! Register Offset (relative)
#define ANEG_LP_BP_AB 0x26
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_LP_BP_AB 0x00E00026u

//! Register Reset Value
#define ANEG_LP_BP_AB_RST 0x01E0u

//! Field SF - Link Partner Selector Field
#define ANEG_LP_BP_AB_SF_POS 0
//! Field SF - Link Partner Selector Field
#define ANEG_LP_BP_AB_SF_MASK 0x1Fu
//! Constant IEEE8023 - IEEE802.3
#define CONST_ANEG_LP_BP_AB_SF_IEEE8023 0x1

//! Field TAF - Technology Ability Field
#define ANEG_LP_BP_AB_TAF_POS 5
//! Field TAF - Technology Ability Field
#define ANEG_LP_BP_AB_TAF_MASK 0xFE0u
//! Constant PS_ASYM - Advertise asymmetric pause
#define CONST_ANEG_LP_BP_AB_TAF_PS_ASYM 0x40u
//! Constant PS_SYM - Advertise symmetric pause
#define CONST_ANEG_LP_BP_AB_TAF_PS_SYM 0x20u
//! Constant DBT4 - Advertise 100BASE-T4
#define CONST_ANEG_LP_BP_AB_TAF_DBT4 0x10u
//! Constant DBT_FDX - Advertise 100BASE-TX full duplex
#define CONST_ANEG_LP_BP_AB_TAF_DBT_FDX 0x08u
//! Constant DBT_HDX - Advertise 100BASE-TX half duplex
#define CONST_ANEG_LP_BP_AB_TAF_DBT_HDX 0x04u
//! Constant XBT_FDX - Advertise 10BASE-T full duplex
#define CONST_ANEG_LP_BP_AB_TAF_XBT_FDX 0x02u
//! Constant XBT_HDX - Advertise 10BASE-T half duplex
#define CONST_ANEG_LP_BP_AB_TAF_XBT_HDX 0x01u

//! Field XNP - Link Partner XNP Ability
#define ANEG_LP_BP_AB_XNP_POS 12
//! Field XNP - Link Partner XNP Ability
#define ANEG_LP_BP_AB_XNP_MASK 0x1000u
//! Constant UNABLE - Link Partner is not XNP able
#define CONST_ANEG_LP_BP_AB_XNP_UNABLE 0x0
//! Constant ABLE - Link Partner is XNP able
#define CONST_ANEG_LP_BP_AB_XNP_ABLE 0x1

//! Field RF - Link Partner Remote Fault
#define ANEG_LP_BP_AB_RF_POS 13
//! Field RF - Link Partner Remote Fault
#define ANEG_LP_BP_AB_RF_MASK 0x2000u
//! Constant NONE - Remote fault is not indicated by the link partner
#define CONST_ANEG_LP_BP_AB_RF_NONE 0x0
//! Constant FAULT - Remote fault is indicated by the link partner
#define CONST_ANEG_LP_BP_AB_RF_FAULT 0x1

//! Field ACK - Link Partner Acknowledge
#define ANEG_LP_BP_AB_ACK_POS 14
//! Field ACK - Link Partner Acknowledge
#define ANEG_LP_BP_AB_ACK_MASK 0x4000u
//! Constant INACTIVE - Device did not successfully receive its Link Partner's LCW
#define CONST_ANEG_LP_BP_AB_ACK_INACTIVE 0x0
//! Constant ACTIVE
#define CONST_ANEG_LP_BP_AB_ACK_ACTIVE 0x1

//! Field NP - Link Partner Next Page
#define ANEG_LP_BP_AB_NP_POS 15
//! Field NP - Link Partner Next Page
#define ANEG_LP_BP_AB_NP_MASK 0x8000u
//! Constant INACTIVE - No Next Page to Follow
#define CONST_ANEG_LP_BP_AB_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional Next Page will follow
#define CONST_ANEG_LP_BP_AB_NP_ACTIVE 0x1

//! @}

//! \defgroup ANEG_XNP_TX1 Register ANEG_XNP_TX1 - ANEG Local Dev XNP TX1 (Register 7.22)
//! @{

//! Register Offset (relative)
#define ANEG_XNP_TX1 0x2C
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_XNP_TX1 0x00E0002Cu

//! Register Reset Value
#define ANEG_XNP_TX1_RST 0x0000u

//! Field MCF - Message Code Field
#define ANEG_XNP_TX1_MCF_POS 0
//! Field MCF - Message Code Field
#define ANEG_XNP_TX1_MCF_MASK 0x7FFu
//! Constant MCF_2G5BT - Message Code Field is 9 for 2.5G Base T
#define CONST_ANEG_XNP_TX1_MCF_MCF_2G5BT 0x009u

//! Field TOGG - Toggle
#define ANEG_XNP_TX1_TOGG_POS 11
//! Field TOGG - Toggle
#define ANEG_XNP_TX1_TOGG_MASK 0x800u
//! Constant ZERO - Previous value of the Tx LCW was ONE
#define CONST_ANEG_XNP_TX1_TOGG_ZERO 0x0
//! Constant ONE - Previous value of the Tx LCW was ZERO
#define CONST_ANEG_XNP_TX1_TOGG_ONE 0x1

//! Field ACK2 - Acknowledge 2
#define ANEG_XNP_TX1_ACK2_POS 12
//! Field ACK2 - Acknowledge 2
#define ANEG_XNP_TX1_ACK2_MASK 0x1000u
//! Constant INACTIVE - Device cannot comply with message
#define CONST_ANEG_XNP_TX1_ACK2_INACTIVE 0x0
//! Constant ACTIVE - Device will comply with message
#define CONST_ANEG_XNP_TX1_ACK2_ACTIVE 0x1

//! Field MP - Message Page
#define ANEG_XNP_TX1_MP_POS 13
//! Field MP - Message Page
#define ANEG_XNP_TX1_MP_MASK 0x2000u
//! Constant UNFOR - Unformatted Page
#define CONST_ANEG_XNP_TX1_MP_UNFOR 0x0
//! Constant MESSG - Message Page
#define CONST_ANEG_XNP_TX1_MP_MESSG 0x1

//! Field RES - Reserved
#define ANEG_XNP_TX1_RES_POS 14
//! Field RES - Reserved
#define ANEG_XNP_TX1_RES_MASK 0x4000u

//! Field NP - Next Page
#define ANEG_XNP_TX1_NP_POS 15
//! Field NP - Next Page
#define ANEG_XNP_TX1_NP_MASK 0x8000u
//! Constant INACTIVE - No Next Page to Follow
#define CONST_ANEG_XNP_TX1_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next page(s) will follow
#define CONST_ANEG_XNP_TX1_NP_ACTIVE 0x1

//! @}

//! \defgroup ANEG_XNP_TX2 Register ANEG_XNP_TX2 - ANEG Local Dev XNP TX2 (Register 7.23)
//! @{

//! Register Offset (relative)
#define ANEG_XNP_TX2 0x2E
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_XNP_TX2 0x00E0002Eu

//! Register Reset Value
#define ANEG_XNP_TX2_RST 0x0000u

//! Field UCF1 - Unformatted Code Field 1
#define ANEG_XNP_TX2_UCF1_POS 0
//! Field UCF1 - Unformatted Code Field 1
#define ANEG_XNP_TX2_UCF1_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_XNP_TX3 Register ANEG_XNP_TX3 - ANEG Local Dev XNP TX3 (Register 7.24)
//! @{

//! Register Offset (relative)
#define ANEG_XNP_TX3 0x30
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_XNP_TX3 0x00E00030u

//! Register Reset Value
#define ANEG_XNP_TX3_RST 0x0000u

//! Field UCF2 - Unformatted Code Field 2
#define ANEG_XNP_TX3_UCF2_POS 0
//! Field UCF2 - Unformatted Code Field 2
#define ANEG_XNP_TX3_UCF2_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_LP_XNP_AB1 Register ANEG_LP_XNP_AB1 - ANEG Link Partner XNP RX (Register 7.25)
//! @{

//! Register Offset (relative)
#define ANEG_LP_XNP_AB1 0x32
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_LP_XNP_AB1 0x00E00032u

//! Register Reset Value
#define ANEG_LP_XNP_AB1_RST 0x0000u

//! Field MCF - Link Partner Message Code Field
#define ANEG_LP_XNP_AB1_MCF_POS 0
//! Field MCF - Link Partner Message Code Field
#define ANEG_LP_XNP_AB1_MCF_MASK 0x7FFu
//! Constant MC_2G5BT - Message Code for 2G5BT
#define CONST_ANEG_LP_XNP_AB1_MCF_MC_2G5BT 0x009u

//! Field TOGG - Link Partner Toggle
#define ANEG_LP_XNP_AB1_TOGG_POS 11
//! Field TOGG - Link Partner Toggle
#define ANEG_LP_XNP_AB1_TOGG_MASK 0x800u
//! Constant ZERO - Previous value of the TX LCW was ONE
#define CONST_ANEG_LP_XNP_AB1_TOGG_ZERO 0x0
//! Constant ONE - Previous value of the TX LCW was ZERO
#define CONST_ANEG_LP_XNP_AB1_TOGG_ONE 0x1

//! Field ACK2 - Link Partner Acknowledge 2
#define ANEG_LP_XNP_AB1_ACK2_POS 12
//! Field ACK2 - Link Partner Acknowledge 2
#define ANEG_LP_XNP_AB1_ACK2_MASK 0x1000u
//! Constant INACTIVE - Device cannot comply with message
#define CONST_ANEG_LP_XNP_AB1_ACK2_INACTIVE 0x0
//! Constant ACTIVE - Device will comply with message
#define CONST_ANEG_LP_XNP_AB1_ACK2_ACTIVE 0x1

//! Field MP - Link Partner Message Page
#define ANEG_LP_XNP_AB1_MP_POS 13
//! Field MP - Link Partner Message Page
#define ANEG_LP_XNP_AB1_MP_MASK 0x2000u
//! Constant UNFOR - Unformatted Page
#define CONST_ANEG_LP_XNP_AB1_MP_UNFOR 0x0
//! Constant MESSG - Message Page
#define CONST_ANEG_LP_XNP_AB1_MP_MESSG 0x1

//! Field ACK - Link Partner Acknowledge
#define ANEG_LP_XNP_AB1_ACK_POS 14
//! Field ACK - Link Partner Acknowledge
#define ANEG_LP_XNP_AB1_ACK_MASK 0x4000u

//! Field NP - Link Partner Next Page
#define ANEG_LP_XNP_AB1_NP_POS 15
//! Field NP - Link Partner Next Page
#define ANEG_LP_XNP_AB1_NP_MASK 0x8000u
//! Constant INACTIVE - Last Page
#define CONST_ANEG_LP_XNP_AB1_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next page(s) will follow
#define CONST_ANEG_LP_XNP_AB1_NP_ACTIVE 0x1

//! @}

//! \defgroup ANEG_LP_XNP_AB2 Register ANEG_LP_XNP_AB2 - ANEG Link Partner XNP RX (Register 7.26)
//! @{

//! Register Offset (relative)
#define ANEG_LP_XNP_AB2 0x34
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_LP_XNP_AB2 0x00E00034u

//! Register Reset Value
#define ANEG_LP_XNP_AB2_RST 0x0000u

//! Field UCF1 - Unformatted Code Field 1
#define ANEG_LP_XNP_AB2_UCF1_POS 0
//! Field UCF1 - Unformatted Code Field 1
#define ANEG_LP_XNP_AB2_UCF1_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_LP_XNP_AB3 Register ANEG_LP_XNP_AB3 - ANEG Link Partner XNP RX (Register 7.27)
//! @{

//! Register Offset (relative)
#define ANEG_LP_XNP_AB3 0x36
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_LP_XNP_AB3 0x00E00036u

//! Register Reset Value
#define ANEG_LP_XNP_AB3_RST 0x0000u

//! Field UCF2 - Unformatted Code Field 2
#define ANEG_LP_XNP_AB3_UCF2_POS 0
//! Field UCF2 - Unformatted Code Field 2
#define ANEG_LP_XNP_AB3_UCF2_MASK 0xFFFFu

//! @}

//! \defgroup ANEG_MGBT_AN_CTRL Register ANEG_MGBT_AN_CTRL - MULTI GBT AN Control Register (Register 7.32)
//! @{

//! Register Offset (relative)
#define ANEG_MGBT_AN_CTRL 0x40
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_MGBT_AN_CTRL 0x00E00040u

//! Register Reset Value
#define ANEG_MGBT_AN_CTRL_RST 0x40A2u

//! Field LDL - GPY Loop Timing Ability
#define ANEG_MGBT_AN_CTRL_LDL_POS 0
//! Field LDL - GPY Loop Timing Ability
#define ANEG_MGBT_AN_CTRL_LDL_MASK 0x1u

//! Field FR - Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_POS 1
//! Field FR - Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_MASK 0x2u

//! Field LDPMA - GPY PMA training reset request
#define ANEG_MGBT_AN_CTRL_LDPMA_POS 2
//! Field LDPMA - GPY PMA training reset request
#define ANEG_MGBT_AN_CTRL_LDPMA_MASK 0x4u

//! Field RES1 - Reserved
#define ANEG_MGBT_AN_CTRL_RES1_POS 3
//! Field RES1 - Reserved
#define ANEG_MGBT_AN_CTRL_RES1_MASK 0x18u

//! Field FR_2G5BT - 2.5 G BASE-T Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_2G5BT_POS 5
//! Field FR_2G5BT - 2.5 G BASE-T Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_2G5BT_MASK 0x20u
//! Constant UNABLE - Do not Advertise PHY as 2.5G Fast Retrain Able
#define CONST_ANEG_MGBT_AN_CTRL_FR_2G5BT_UNABLE 0x0
//! Constant ABLE - Advertise PHY as 2.5G Fast retrain able
#define CONST_ANEG_MGBT_AN_CTRL_FR_2G5BT_ABLE 0x1

//! Field FR_5GBT - 5 G BASE-T Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_5GBT_POS 6
//! Field FR_5GBT - 5 G BASE-T Fast Retrain Ability
#define ANEG_MGBT_AN_CTRL_FR_5GBT_MASK 0x40u
//! Constant UNABLE - Do not Advertise PHY as 5GBT Fast retrain able
#define CONST_ANEG_MGBT_AN_CTRL_FR_5GBT_UNABLE 0x0
//! Constant ABLE - Advertise PHY as 5GBASE-T Fast Retrain capable
#define CONST_ANEG_MGBT_AN_CTRL_FR_5GBT_ABLE 0x1

//! Field AB_2G5BT - 2.5 G BASE-T ability
#define ANEG_MGBT_AN_CTRL_AB_2G5BT_POS 7
//! Field AB_2G5BT - 2.5 G BASE-T ability
#define ANEG_MGBT_AN_CTRL_AB_2G5BT_MASK 0x80u
//! Constant UNABLE - Do not Advertise PHY as 2.5GBASE-T capable
#define CONST_ANEG_MGBT_AN_CTRL_AB_2G5BT_UNABLE 0x0
//! Constant ABLE - Advertise PHY as 2.5GBASE-T capable
#define CONST_ANEG_MGBT_AN_CTRL_AB_2G5BT_ABLE 0x1

//! Field AB_5GBT - 5GBASE-T ability
#define ANEG_MGBT_AN_CTRL_AB_5GBT_POS 8
//! Field AB_5GBT - 5GBASE-T ability
#define ANEG_MGBT_AN_CTRL_AB_5GBT_MASK 0x100u
//! Constant UNABLE - Do not Advertise PHY as 5GBASE-T capable
#define CONST_ANEG_MGBT_AN_CTRL_AB_5GBT_UNABLE 0x0
//! Constant ABLE - Advertise PHY as 5GBASE-T capable
#define CONST_ANEG_MGBT_AN_CTRL_AB_5GBT_ABLE 0x1

//! Field RES2 - Reserved
#define ANEG_MGBT_AN_CTRL_RES2_POS 9
//! Field RES2 - Reserved
#define ANEG_MGBT_AN_CTRL_RES2_MASK 0xE00u

//! Field AB_10GBT - 10GBASE-T Ability
#define ANEG_MGBT_AN_CTRL_AB_10GBT_POS 12
//! Field AB_10GBT - 10GBASE-T Ability
#define ANEG_MGBT_AN_CTRL_AB_10GBT_MASK 0x1000u

//! Field PT - Port Type
#define ANEG_MGBT_AN_CTRL_PT_POS 13
//! Field PT - Port Type
#define ANEG_MGBT_AN_CTRL_PT_MASK 0x2000u
//! Constant MASTER - Preference as Master - Single Port Device
#define CONST_ANEG_MGBT_AN_CTRL_PT_MASTER 0x0
//! Constant SLAVE - Preference as Slave - Multiport Device
#define CONST_ANEG_MGBT_AN_CTRL_PT_SLAVE 0x1

//! Field MSCV - Master Slave Config Value
#define ANEG_MGBT_AN_CTRL_MSCV_POS 14
//! Field MSCV - Master Slave Config Value
#define ANEG_MGBT_AN_CTRL_MSCV_MASK 0x4000u
//! Constant SLAVE - Manual set to SLAVE
#define CONST_ANEG_MGBT_AN_CTRL_MSCV_SLAVE 0x0
//! Constant MASTER - Manual set to MASTER
#define CONST_ANEG_MGBT_AN_CTRL_MSCV_MASTER 0x1

//! Field MS_MAN_EN - Master Slave Config Manual Config Enable
#define ANEG_MGBT_AN_CTRL_MS_MAN_EN_POS 15
//! Field MS_MAN_EN - Master Slave Config Manual Config Enable
#define ANEG_MGBT_AN_CTRL_MS_MAN_EN_MASK 0x8000u
//! Constant ANEG - ANEG is used to determine Master-Slave selection
#define CONST_ANEG_MGBT_AN_CTRL_MS_MAN_EN_ANEG 0x0
//! Constant MAN - Manual Config, MSCV bit determines Master-Slave
#define CONST_ANEG_MGBT_AN_CTRL_MS_MAN_EN_MAN 0x1

//! @}

//! \defgroup ANEG_MGBT_AN_STA Register ANEG_MGBT_AN_STA - MultiGBASE-T AN Status register (Register 7.33)
//! @{

//! Register Offset (relative)
#define ANEG_MGBT_AN_STA 0x42
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_MGBT_AN_STA 0x00E00042u

//! Register Reset Value
#define ANEG_MGBT_AN_STA_RST 0x0000u

//! Field FR_2G5BT - 2.5 G BASE-T Fast Retrain Ability of Link Partner
#define ANEG_MGBT_AN_STA_FR_2G5BT_POS 3
//! Field FR_2G5BT - 2.5 G BASE-T Fast Retrain Ability of Link Partner
#define ANEG_MGBT_AN_STA_FR_2G5BT_MASK 0x8u
//! Constant UNABLE - Link partner is not capable of 2.5GBT fast retrain
#define CONST_ANEG_MGBT_AN_STA_FR_2G5BT_UNABLE 0x0
//! Constant ABLE - Link partner is capable of 2.5GBASE-T fast retrain
#define CONST_ANEG_MGBT_AN_STA_FR_2G5BT_ABLE 0x1

//! Field FR_5GBT - 5 G BASE-T Fast Retrain Ability of Link Partner
#define ANEG_MGBT_AN_STA_FR_5GBT_POS 4
//! Field FR_5GBT - 5 G BASE-T Fast Retrain Ability of Link Partner
#define ANEG_MGBT_AN_STA_FR_5GBT_MASK 0x10u
//! Constant UNABLE - Link partner is not capable of 5GBT fast retrain
#define CONST_ANEG_MGBT_AN_STA_FR_5GBT_UNABLE 0x0
//! Constant ABLE - Link partner is capable of 5GBASE-T fast retrain
#define CONST_ANEG_MGBT_AN_STA_FR_5GBT_ABLE 0x1

//! Field AB_2G5BT - 2.5 G BASE-T Ability of Link Partner
#define ANEG_MGBT_AN_STA_AB_2G5BT_POS 5
//! Field AB_2G5BT - 2.5 G BASE-T Ability of Link Partner
#define ANEG_MGBT_AN_STA_AB_2G5BT_MASK 0x20u
//! Constant UNABLE - Link partner is not capable of 2.5GBASE-T
#define CONST_ANEG_MGBT_AN_STA_AB_2G5BT_UNABLE 0x0
//! Constant ABLE - Link partner is capable of 2.5GBASE-T
#define CONST_ANEG_MGBT_AN_STA_AB_2G5BT_ABLE 0x1

//! Field AB_5GBT - 5G BASE-T Ability of Link Partner
#define ANEG_MGBT_AN_STA_AB_5GBT_POS 6
//! Field AB_5GBT - 5G BASE-T Ability of Link Partner
#define ANEG_MGBT_AN_STA_AB_5GBT_MASK 0x40u
//! Constant UNABLE - Link partner is not capable of 5GBASE-T
#define CONST_ANEG_MGBT_AN_STA_AB_5GBT_UNABLE 0x0
//! Constant ABLE - Link partner is capable of 5GBASE-T
#define CONST_ANEG_MGBT_AN_STA_AB_5GBT_ABLE 0x1

//! @}

//! \defgroup ANEG_EEE_AN_ADV1 Register ANEG_EEE_AN_ADV1 - EEE Advertisement 1 (Register 7.60)
//! @{

//! Register Offset (relative)
#define ANEG_EEE_AN_ADV1 0x78
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_EEE_AN_ADV1 0x00E00078u

//! Register Reset Value
#define ANEG_EEE_AN_ADV1_RST 0x0006u

//! Field EEE_100BTX - Support of 100BASE-TX EEE
#define ANEG_EEE_AN_ADV1_EEE_100BTX_POS 1
//! Field EEE_100BTX - Support of 100BASE-TX EEE
#define ANEG_EEE_AN_ADV1_EEE_100BTX_MASK 0x2u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_100BTX_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_100BTX_ENABLE 0x1

//! Field EEE_1000BT - Support of 1000BASE-T EEE
#define ANEG_EEE_AN_ADV1_EEE_1000BT_POS 2
//! Field EEE_1000BT - Support of 1000BASE-T EEE
#define ANEG_EEE_AN_ADV1_EEE_1000BT_MASK 0x4u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_1000BT_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_1000BT_ENABLE 0x1

//! Field EEE_10GBT - Support of 10GBASE-T EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBT_POS 3
//! Field EEE_10GBT - Support of 10GBASE-T EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBT_MASK 0x8u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBT_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBT_ENABLE 0x1

//! Field EEE_1000BKX - Support of 1000BASE-KX EEE
#define ANEG_EEE_AN_ADV1_EEE_1000BKX_POS 4
//! Field EEE_1000BKX - Support of 1000BASE-KX EEE
#define ANEG_EEE_AN_ADV1_EEE_1000BKX_MASK 0x10u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_1000BKX_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_1000BKX_ENABLE 0x1

//! Field EEE_10GBKX4 - Support of 10GBASE-KX4 EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBKX4_POS 5
//! Field EEE_10GBKX4 - Support of 10GBASE-KX4 EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBKX4_MASK 0x20u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBKX4_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBKX4_ENABLE 0x1

//! Field EEE_10GBKR - Support of 10GBASE-KR EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBKR_POS 6
//! Field EEE_10GBKR - Support of 10GBASE-KR EEE
#define ANEG_EEE_AN_ADV1_EEE_10GBKR_MASK 0x40u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBKR_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_ADV1_EEE_10GBKR_ENABLE 0x1

//! @}

//! \defgroup ANEG_EEE_AN_LPAB1 Register ANEG_EEE_AN_LPAB1 - EEE Link Partner Ability 1 (Register 7.61)
//! @{

//! Register Offset (relative)
#define ANEG_EEE_AN_LPAB1 0x7A
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_EEE_AN_LPAB1 0x00E0007Au

//! Register Reset Value
#define ANEG_EEE_AN_LPAB1_RST 0x0000u

//! Field EEE_100BTX - Support of 100BASE-TX EEE
#define ANEG_EEE_AN_LPAB1_EEE_100BTX_POS 1
//! Field EEE_100BTX - Support of 100BASE-TX EEE
#define ANEG_EEE_AN_LPAB1_EEE_100BTX_MASK 0x2u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_100BTX_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_100BTX_ENABLE 0x1

//! Field EEE_1000BT - Support of 1000BASE-T EEE
#define ANEG_EEE_AN_LPAB1_EEE_1000BT_POS 2
//! Field EEE_1000BT - Support of 1000BASE-T EEE
#define ANEG_EEE_AN_LPAB1_EEE_1000BT_MASK 0x4u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_1000BT_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_1000BT_ENABLE 0x1

//! Field EEE_10GBT - Support of 10GBASE-T EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBT_POS 3
//! Field EEE_10GBT - Support of 10GBASE-T EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBT_MASK 0x8u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBT_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBT_ENABLE 0x1

//! Field EEE_1000BKX - Support of 1000BASE-KX EEE
#define ANEG_EEE_AN_LPAB1_EEE_1000BKX_POS 4
//! Field EEE_1000BKX - Support of 1000BASE-KX EEE
#define ANEG_EEE_AN_LPAB1_EEE_1000BKX_MASK 0x10u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_1000BKX_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_1000BKX_ENABLE 0x1

//! Field EEE_10GBKX4 - Support of 10GBASE-KX4 EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBKX4_POS 5
//! Field EEE_10GBKX4 - Support of 10GBASE-KX4 EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBKX4_MASK 0x20u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBKX4_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBKX4_ENABLE 0x1

//! Field EEE_10GBKR - Support of 10GBASE-KR EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBKR_POS 6
//! Field EEE_10GBKR - Support of 10GBASE-KR EEE
#define ANEG_EEE_AN_LPAB1_EEE_10GBKR_MASK 0x40u
//! Constant DISABLED - This PHY mode is not supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBKR_DISABLED 0x0
//! Constant ENABLE - This PHY mode is supported for EEE
#define CONST_ANEG_EEE_AN_LPAB1_EEE_10GBKR_ENABLE 0x1

//! @}

//! \defgroup ANEG_EEE_AN_ADV2 Register ANEG_EEE_AN_ADV2 - EEE Advertisement 2 (Register 7.62)
//! @{

//! Register Offset (relative)
#define ANEG_EEE_AN_ADV2 0x7C
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_EEE_AN_ADV2 0x00E0007Cu

//! Register Reset Value
#define ANEG_EEE_AN_ADV2_RST 0x0001u

//! Field EEE2G5 - Advertise 2G5BT EEE capability
#define ANEG_EEE_AN_ADV2_EEE2G5_POS 0
//! Field EEE2G5 - Advertise 2G5BT EEE capability
#define ANEG_EEE_AN_ADV2_EEE2G5_MASK 0x1u
//! Constant DISABLED - This PHY mode does not advertise 2G5BT EEE
#define CONST_ANEG_EEE_AN_ADV2_EEE2G5_DISABLED 0x0
//! Constant ENABLE - This PHY mode does advertise 2G5BT EEE
#define CONST_ANEG_EEE_AN_ADV2_EEE2G5_ENABLE 0x1

//! Field RES - Reserved
#define ANEG_EEE_AN_ADV2_RES_POS 1
//! Field RES - Reserved
#define ANEG_EEE_AN_ADV2_RES_MASK 0xFFFEu

//! @}

//! \defgroup ANEG_EEE_LP_AB2 Register ANEG_EEE_LP_AB2 - EEE Link Partner Ability 2 (Register 7.63)
//! @{

//! Register Offset (relative)
#define ANEG_EEE_LP_AB2 0x7E
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_EEE_LP_AB2 0x00E0007Eu

//! Register Reset Value
#define ANEG_EEE_LP_AB2_RST 0x0001u

//! Field EEE2G5 - Link Partner advertised 2G5BT EEE capability
#define ANEG_EEE_LP_AB2_EEE2G5_POS 0
//! Field EEE2G5 - Link Partner advertised 2G5BT EEE capability
#define ANEG_EEE_LP_AB2_EEE2G5_MASK 0x1u
//! Constant DISABLED - LP advertise 2G5BT EEE
#define CONST_ANEG_EEE_LP_AB2_EEE2G5_DISABLED 0x0
//! Constant ENABLE - LP advertise 2G5BT EEE
#define CONST_ANEG_EEE_LP_AB2_EEE2G5_ENABLE 0x1

//! Field RES - Reserved
#define ANEG_EEE_LP_AB2_RES_POS 1
//! Field RES - Reserved
#define ANEG_EEE_LP_AB2_RES_MASK 0xFFFEu

//! @}

//! \defgroup ANEG_MGBT_AN_CTRL2 Register ANEG_MGBT_AN_CTRL2 - MGBT ANEG Control 2 (Register 7.64)
//! @{

//! Register Offset (relative)
#define ANEG_MGBT_AN_CTRL2 0x80
//! Register Offset (absolute) for 1st Instance ANEG
#define ANEG_ANEG_MGBT_AN_CTRL2 0x00E00080u

//! Register Reset Value
#define ANEG_MGBT_AN_CTRL2_RST 0x0008u

//! Field THPBYP2G5 - GPY Requests a THP bypass during fast retrain.
#define ANEG_MGBT_AN_CTRL2_THPBYP2G5_POS 3
//! Field THPBYP2G5 - GPY Requests a THP bypass during fast retrain.
#define ANEG_MGBT_AN_CTRL2_THPBYP2G5_MASK 0x8u
//! Constant NORST - GPY requests partner NOT to initially reset THP during fast retrain
#define CONST_ANEG_MGBT_AN_CTRL2_THPBYP2G5_NORST 0x0
//! Constant RST - GPY requests partner to initially reset THP during fast retrain
#define CONST_ANEG_MGBT_AN_CTRL2_THPBYP2G5_RST 0x1

//! Field RES - Reserved
#define ANEG_MGBT_AN_CTRL2_RES_POS 4
//! Field RES - Reserved
#define ANEG_MGBT_AN_CTRL2_RES_MASK 0x7FF0u

//! @}

//! @}

#endif
