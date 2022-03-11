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
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/std_def.xml
// Register File Name  : STD
// Register File Title : Standard Management Registers
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _STD_H
#define _STD_H

//! \defgroup STD Register File STD - Standard Management Registers
//! @{

//! Base Address of STD
#define STD_MODULE_BASE 0x00000000u

//! \defgroup STD_CTRL Register STD_CTRL - STD Control (Register 0.0)
//! @{

//! Register Offset (relative)
#define STD_CTRL 0x0
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_CTRL 0x00000000u

//! Register Reset Value
#define STD_CTRL_RST 0x3040u

//! Field RES - Reserved
#define STD_CTRL_RES_POS 0
//! Field RES - Reserved
#define STD_CTRL_RES_MASK 0x3Fu

//! Field SSM - Forced Speed Selection MSB
#define STD_CTRL_SSM_POS 6
//! Field SSM - Forced Speed Selection MSB
#define STD_CTRL_SSM_MASK 0x40u

//! Field COL - Collision Test
#define STD_CTRL_COL_POS 7
//! Field COL - Collision Test
#define STD_CTRL_COL_MASK 0x80u
//! Constant DISABLE - Normal operational mode
#define CONST_STD_CTRL_COL_DISABLE 0x0
//! Constant ENABLE - Activates the collision test
#define CONST_STD_CTRL_COL_ENABLE 0x1

//! Field DPLX - Forced Duplex Mode
#define STD_CTRL_DPLX_POS 8
//! Field DPLX - Forced Duplex Mode
#define STD_CTRL_DPLX_MASK 0x100u
//! Constant HD - Half duplex
#define CONST_STD_CTRL_DPLX_HD 0x0
//! Constant FD - Full duplex
#define CONST_STD_CTRL_DPLX_FD 0x1

//! Field ANRS - Restart Auto-Negotiation
#define STD_CTRL_ANRS_POS 9
//! Field ANRS - Restart Auto-Negotiation
#define STD_CTRL_ANRS_MASK 0x200u
//! Constant NORMAL - Stay in current mode
#define CONST_STD_CTRL_ANRS_NORMAL 0x0
//! Constant RESTART - Restart auto-negotiation
#define CONST_STD_CTRL_ANRS_RESTART 0x1

//! Field ISOL - Isolate
#define STD_CTRL_ISOL_POS 10
//! Field ISOL - Isolate
#define STD_CTRL_ISOL_MASK 0x400u
//! Constant NORMAL - Normal operational mode
#define CONST_STD_CTRL_ISOL_NORMAL 0x0
//! Constant ISOLATE - Isolates the PHY from the MAC
#define CONST_STD_CTRL_ISOL_ISOLATE 0x1

//! Field PD - Power Down
#define STD_CTRL_PD_POS 11
//! Field PD - Power Down
#define STD_CTRL_PD_MASK 0x800u
//! Constant NORMAL - Normal operational mode
#define CONST_STD_CTRL_PD_NORMAL 0x0
//! Constant POWERDOWN - Forces the device into power down mode
#define CONST_STD_CTRL_PD_POWERDOWN 0x1

//! Field ANEN - Auto-Negotiation Enable
#define STD_CTRL_ANEN_POS 12
//! Field ANEN - Auto-Negotiation Enable
#define STD_CTRL_ANEN_MASK 0x1000u
//! Constant DISABLE - Disable the auto-negotiation protocol
#define CONST_STD_CTRL_ANEN_DISABLE 0x0
//! Constant ENABLE - Enable the auto-negotiation protocol
#define CONST_STD_CTRL_ANEN_ENABLE 0x1

//! Field SSL - Forced Speed Selection LSB
#define STD_CTRL_SSL_POS 13
//! Field SSL - Forced Speed Selection LSB
#define STD_CTRL_SSL_MASK 0x2000u

//! Field LB - Loop-Back on GMII
#define STD_CTRL_LB_POS 14
//! Field LB - Loop-Back on GMII
#define STD_CTRL_LB_MASK 0x4000u
//! Constant NORMAL - Normal operational mode
#define CONST_STD_CTRL_LB_NORMAL 0x0
//! Constant ENABLE - Closes the loop-back from TX to RX at xMII
#define CONST_STD_CTRL_LB_ENABLE 0x1

//! Field RST - Reset
#define STD_CTRL_RST_POS 15
//! Field RST - Reset
#define STD_CTRL_RST_MASK 0x8000u
//! Constant NORMAL - Normal operational mode
#define CONST_STD_CTRL_RST_NORMAL 0x0
//! Constant RESET - Resets the device
#define CONST_STD_CTRL_RST_RESET 0x1

//! @}

//! \defgroup STD_STAT Register STD_STAT - Status Register (Register 0.1)
//! @{

//! Register Offset (relative)
#define STD_STAT 0x2
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_STAT 0x00000002u

//! Register Reset Value
#define STD_STAT_RST 0x7949u

//! Field XCAP - Extended Capability
#define STD_STAT_XCAP_POS 0
//! Field XCAP - Extended Capability
#define STD_STAT_XCAP_MASK 0x1u
//! Constant DISABLED - Only base registers are supported
#define CONST_STD_STAT_XCAP_DISABLED 0x0
//! Constant ENABLED - Extended capability registers are supported
#define CONST_STD_STAT_XCAP_ENABLED 0x1

//! Field JD - Jabber Detect
#define STD_STAT_JD_POS 1
//! Field JD - Jabber Detect
#define STD_STAT_JD_MASK 0x2u
//! Constant NONE - No jabber condition detected
#define CONST_STD_STAT_JD_NONE 0x0
//! Constant DETECTED - Jabber condition detected
#define CONST_STD_STAT_JD_DETECTED 0x1

//! Field LS - Link Status
#define STD_STAT_LS_POS 2
//! Field LS - Link Status
#define STD_STAT_LS_MASK 0x4u
//! Constant INACTIVE - The link is down. No communication with link partner possible.
#define CONST_STD_STAT_LS_INACTIVE 0x0
//! Constant ACTIVE - The link is up. Data communication with link partner is possible.
#define CONST_STD_STAT_LS_ACTIVE 0x1

//! Field ANAB - Auto-Negotiation Ability
#define STD_STAT_ANAB_POS 3
//! Field ANAB - Auto-Negotiation Ability
#define STD_STAT_ANAB_MASK 0x8u
//! Constant DISABLED - PHY is not able to perform auto-negotiation
#define CONST_STD_STAT_ANAB_DISABLED 0x0
//! Constant ENABLED - PHY is able to perform auto-negotiation
#define CONST_STD_STAT_ANAB_ENABLED 0x1

//! Field RF - Remote Fault
#define STD_STAT_RF_POS 4
//! Field RF - Remote Fault
#define STD_STAT_RF_MASK 0x10u
//! Constant INACTIVE - No remote fault condition detected
#define CONST_STD_STAT_RF_INACTIVE 0x0
//! Constant ACTIVE - Remote fault condition detected
#define CONST_STD_STAT_RF_ACTIVE 0x1

//! Field ANOK - Auto-Negotiation Completed
#define STD_STAT_ANOK_POS 5
//! Field ANOK - Auto-Negotiation Completed
#define STD_STAT_ANOK_MASK 0x20u
//! Constant RUNNING - Auto-negotiation process is in progress
#define CONST_STD_STAT_ANOK_RUNNING 0x0
//! Constant COMPLETED - Auto-negotiation process is completed
#define CONST_STD_STAT_ANOK_COMPLETED 0x1

//! Field MFPS - Management Preamble Suppression
#define STD_STAT_MFPS_POS 6
//! Field MFPS - Management Preamble Suppression
#define STD_STAT_MFPS_MASK 0x40u
//! Constant DISABLED - PHY requires management frames with preamble
#define CONST_STD_STAT_MFPS_DISABLED 0x0
//! Constant ENABLED - PHY accepts management frames without preamble
#define CONST_STD_STAT_MFPS_ENABLED 0x1

//! Field RES - Reserved
#define STD_STAT_RES_POS 7
//! Field RES - Reserved
#define STD_STAT_RES_MASK 0x80u

//! Field EXT - Extended Status
#define STD_STAT_EXT_POS 8
//! Field EXT - Extended Status
#define STD_STAT_EXT_MASK 0x100u
//! Constant DISABLED - No extended status information available in register 15
#define CONST_STD_STAT_EXT_DISABLED 0x0
//! Constant ENABLED - Extended status information available in register 15
#define CONST_STD_STAT_EXT_ENABLED 0x1

//! Field CBT2H - IEEE 100BASE-T2 Half-Duplex
#define STD_STAT_CBT2H_POS 9
//! Field CBT2H - IEEE 100BASE-T2 Half-Duplex
#define STD_STAT_CBT2H_MASK 0x200u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_CBT2H_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_CBT2H_ENABLED 0x1

//! Field CBT2F - IEEE 100BASE-T2 Full-Duplex
#define STD_STAT_CBT2F_POS 10
//! Field CBT2F - IEEE 100BASE-T2 Full-Duplex
#define STD_STAT_CBT2F_MASK 0x400u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_CBT2F_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_CBT2F_ENABLED 0x1

//! Field XBTH - IEEE 10BASE-T Half-Duplex
#define STD_STAT_XBTH_POS 11
//! Field XBTH - IEEE 10BASE-T Half-Duplex
#define STD_STAT_XBTH_MASK 0x800u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_XBTH_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_XBTH_ENABLED 0x1

//! Field XBTF - IEEE 10BASE-T Full-Duplex
#define STD_STAT_XBTF_POS 12
//! Field XBTF - IEEE 10BASE-T Full-Duplex
#define STD_STAT_XBTF_MASK 0x1000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_XBTF_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_XBTF_ENABLED 0x1

//! Field CBTXH - IEEE 100BASE-TX Half-Duplex
#define STD_STAT_CBTXH_POS 13
//! Field CBTXH - IEEE 100BASE-TX Half-Duplex
#define STD_STAT_CBTXH_MASK 0x2000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_CBTXH_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_CBTXH_ENABLED 0x1

//! Field CBTXF - IEEE 100BASE-TX Full-Duplex
#define STD_STAT_CBTXF_POS 14
//! Field CBTXF - IEEE 100BASE-TX Full-Duplex
#define STD_STAT_CBTXF_MASK 0x4000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_CBTXF_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_CBTXF_ENABLED 0x1

//! Field CBT4 - IEEE 100BASE-T4
#define STD_STAT_CBT4_POS 15
//! Field CBT4 - IEEE 100BASE-T4
#define STD_STAT_CBT4_MASK 0x8000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_STAT_CBT4_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_STAT_CBT4_ENABLED 0x1

//! @}

//! \defgroup STD_PHYID1 Register STD_PHYID1 - PHY Identifier 1 (Register 0.2)
//! @{

//! Register Offset (relative)
#define STD_PHYID1 0x4
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_PHYID1 0x00000004u

//! Register Reset Value
#define STD_PHYID1_RST 0x67C9u

//! Field OUI - Organizationally Unique Identifier Bits 3:18
#define STD_PHYID1_OUI_POS 0
//! Field OUI - Organizationally Unique Identifier Bits 3:18
#define STD_PHYID1_OUI_MASK 0xFFFFu

//! @}

//! \defgroup STD_PHYID2 Register STD_PHYID2 - PHY Identifier 2 (Register 0.3)
//! @{

//! Register Offset (relative)
#define STD_PHYID2 0x6
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_PHYID2 0x00000006u

//! Register Reset Value
#define STD_PHYID2_RST 0xDC00u

//! Field LDRN - Intel Device Revision Number
#define STD_PHYID2_LDRN_POS 0
//! Field LDRN - Intel Device Revision Number
#define STD_PHYID2_LDRN_MASK 0xFu

//! Field LDN - Intel Device Number
#define STD_PHYID2_LDN_POS 4
//! Field LDN - Intel Device Number
#define STD_PHYID2_LDN_MASK 0x3F0u

//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define STD_PHYID2_OUI_POS 10
//! Field OUI - Organizationally Unique Identifier Bits 19:24
#define STD_PHYID2_OUI_MASK 0xFC00u

//! @}

//! \defgroup STD_AN_ADV Register STD_AN_ADV - Auto-Negotiation Advertisement (Register 0.4)
//! @{

//! Register Offset (relative)
#define STD_AN_ADV 0x8
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_AN_ADV 0x00000008u

//! Register Reset Value
#define STD_AN_ADV_RST 0x0DE1u

//! Field SF - Selector Field
#define STD_AN_ADV_SF_POS 0
//! Field SF - Selector Field
#define STD_AN_ADV_SF_MASK 0x1Fu
//! Constant IEEE802DOT3 - Select the IEEE 802.3 technology
#define CONST_STD_AN_ADV_SF_IEEE802DOT3 0x1

//! Field TAF - Technology Ability Field
#define STD_AN_ADV_TAF_POS 5
//! Field TAF - Technology Ability Field
#define STD_AN_ADV_TAF_MASK 0xFE0u
//! Constant PS_ASYM - Advertise asymmetric pause
#define CONST_STD_AN_ADV_TAF_PS_ASYM 0x40u
//! Constant PS_SYM - Advertise symmetric pause
#define CONST_STD_AN_ADV_TAF_PS_SYM 0x20u
//! Constant DBT4 - Advertise 100BASE-T4
#define CONST_STD_AN_ADV_TAF_DBT4 0x10u
//! Constant DBT_FDX - Advertise 100BASE-TX full duplex
#define CONST_STD_AN_ADV_TAF_DBT_FDX 0x08u
//! Constant DBT_HDX - Advertise 100BASE-TX half duplex
#define CONST_STD_AN_ADV_TAF_DBT_HDX 0x04u
//! Constant XBT_FDX - Advertise 10BASE-T full duplex
#define CONST_STD_AN_ADV_TAF_XBT_FDX 0x02u
//! Constant XBT_HDX - Advertise 10BASE-T half duplex
#define CONST_STD_AN_ADV_TAF_XBT_HDX 0x01u

//! Field XNP - Extended Next Page
#define STD_AN_ADV_XNP_POS 12
//! Field XNP - Extended Next Page
#define STD_AN_ADV_XNP_MASK 0x1000u
//! Constant UNABLE - GPY is XNP unable
#define CONST_STD_AN_ADV_XNP_UNABLE 0x0
//! Constant ABLE - GPY is XNP able
#define CONST_STD_AN_ADV_XNP_ABLE 0x1

//! Field RF - Remote Fault
#define STD_AN_ADV_RF_POS 13
//! Field RF - Remote Fault
#define STD_AN_ADV_RF_MASK 0x2000u
//! Constant NONE - No remote fault is indicated
#define CONST_STD_AN_ADV_RF_NONE 0x0
//! Constant FAULT - A remote fault is indicated
#define CONST_STD_AN_ADV_RF_FAULT 0x1

//! Field RES - Reserved
#define STD_AN_ADV_RES_POS 14
//! Field RES - Reserved
#define STD_AN_ADV_RES_MASK 0x4000u

//! Field NP - Next Page
#define STD_AN_ADV_NP_POS 15
//! Field NP - Next Page
#define STD_AN_ADV_NP_MASK 0x8000u
//! Constant INACTIVE - No next page(s) will follow
#define CONST_STD_AN_ADV_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next page(s) will follow
#define CONST_STD_AN_ADV_NP_ACTIVE 0x1

//! @}

//! \defgroup STD_AN_LPA Register STD_AN_LPA - Auto-Negotiation Link Partner Ability (Register 0.5)
//! @{

//! Register Offset (relative)
#define STD_AN_LPA 0xA
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_AN_LPA 0x0000000Au

//! Register Reset Value
#define STD_AN_LPA_RST 0x11E0u

//! Field SF - Selector Field
#define STD_AN_LPA_SF_POS 0
//! Field SF - Selector Field
#define STD_AN_LPA_SF_MASK 0x1Fu
//! Constant IEEE802DOT3 - Select the IEEE 802.3 technology
#define CONST_STD_AN_LPA_SF_IEEE802DOT3 0x1

//! Field TAF - Technology Ability Field
#define STD_AN_LPA_TAF_POS 5
//! Field TAF - Technology Ability Field
#define STD_AN_LPA_TAF_MASK 0xFE0u
//! Constant PS_ASYM - Advertise asymmetric pause
#define CONST_STD_AN_LPA_TAF_PS_ASYM 0x40u
//! Constant PS_SYM - Advertise symmetric pause
#define CONST_STD_AN_LPA_TAF_PS_SYM 0x20u
//! Constant DBT4 - Advertise 100BASE-T4
#define CONST_STD_AN_LPA_TAF_DBT4 0x10u
//! Constant DBT_FDX - Advertise 100BASE-TX full duplex
#define CONST_STD_AN_LPA_TAF_DBT_FDX 0x08u
//! Constant DBT_HDX - Advertise 100BASE-TX half duplex
#define CONST_STD_AN_LPA_TAF_DBT_HDX 0x04u
//! Constant XBT_FDX - Advertise 10BASE-T full duplex
#define CONST_STD_AN_LPA_TAF_XBT_FDX 0x02u
//! Constant XBT_HDX - Advertise 10BASE-T half duplex
#define CONST_STD_AN_LPA_TAF_XBT_HDX 0x01u

//! Field XNP - Extended Next Page
#define STD_AN_LPA_XNP_POS 12
//! Field XNP - Extended Next Page
#define STD_AN_LPA_XNP_MASK 0x1000u
//! Constant UNABLE - Link partner is XNP unable
#define CONST_STD_AN_LPA_XNP_UNABLE 0x0
//! Constant ABLE - Link partner is XNP able
#define CONST_STD_AN_LPA_XNP_ABLE 0x1

//! Field RF - Remote Fault
#define STD_AN_LPA_RF_POS 13
//! Field RF - Remote Fault
#define STD_AN_LPA_RF_MASK 0x2000u
//! Constant NONE - Remote fault is not indicated by the link partner
#define CONST_STD_AN_LPA_RF_NONE 0x0
//! Constant FAULT - Remote fault is indicated by the link partner
#define CONST_STD_AN_LPA_RF_FAULT 0x1

//! Field ACK - Acknowledge
#define STD_AN_LPA_ACK_POS 14
//! Field ACK - Acknowledge
#define STD_AN_LPA_ACK_MASK 0x4000u
//! Constant INACTIVE - The device did not successfully receive its link partner's link code word
#define CONST_STD_AN_LPA_ACK_INACTIVE 0x0
//! Constant ACTIVE - The device has successfully received its link partner's link code word
#define CONST_STD_AN_LPA_ACK_ACTIVE 0x1

//! Field NP - Next Page
#define STD_AN_LPA_NP_POS 15
//! Field NP - Next Page
#define STD_AN_LPA_NP_MASK 0x8000u
//! Constant INACTIVE - No next page(s) will follow
#define CONST_STD_AN_LPA_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next pages will follow
#define CONST_STD_AN_LPA_NP_ACTIVE 0x1

//! @}

//! \defgroup STD_AN_EXP Register STD_AN_EXP - Auto-Negotiation Expansion (Register 0.6)
//! @{

//! Register Offset (relative)
#define STD_AN_EXP 0xC
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_AN_EXP 0x0000000Cu

//! Register Reset Value
#define STD_AN_EXP_RST 0x0064u

//! Field LPANC - Link Partner Auto-Negotiation Capable
#define STD_AN_EXP_LPANC_POS 0
//! Field LPANC - Link Partner Auto-Negotiation Capable
#define STD_AN_EXP_LPANC_MASK 0x1u
//! Constant UNABLE - Link partner is unable to auto-negotiate
#define CONST_STD_AN_EXP_LPANC_UNABLE 0x0
//! Constant CAPABLE - Link partner is auto-negotiation capable
#define CONST_STD_AN_EXP_LPANC_CAPABLE 0x1

//! Field PR - Page Received
#define STD_AN_EXP_PR_POS 1
//! Field PR - Page Received
#define STD_AN_EXP_PR_MASK 0x2u
//! Constant NONE - A new page has not been received
#define CONST_STD_AN_EXP_PR_NONE 0x0
//! Constant RECEIVED - A new page has been received
#define CONST_STD_AN_EXP_PR_RECEIVED 0x1

//! Field NPC - Next Page Capable
#define STD_AN_EXP_NPC_POS 2
//! Field NPC - Next Page Capable
#define STD_AN_EXP_NPC_MASK 0x4u
//! Constant UNABLE - GPY is unable to exchange next pages
#define CONST_STD_AN_EXP_NPC_UNABLE 0x0
//! Constant CAPABLE - GPY is capable of exchanging next pages
#define CONST_STD_AN_EXP_NPC_CAPABLE 0x1

//! Field LPNPC - Link Partner Next Page Capable
#define STD_AN_EXP_LPNPC_POS 3
//! Field LPNPC - Link Partner Next Page Capable
#define STD_AN_EXP_LPNPC_MASK 0x8u
//! Constant UNABLE - Link partner is unable to exchange next pages
#define CONST_STD_AN_EXP_LPNPC_UNABLE 0x0
//! Constant CAPABLE - Link partner is capable of exchanging next pages
#define CONST_STD_AN_EXP_LPNPC_CAPABLE 0x1

//! Field PDF - Parallel Detection Fault
#define STD_AN_EXP_PDF_POS 4
//! Field PDF - Parallel Detection Fault
#define STD_AN_EXP_PDF_MASK 0x10u
//! Constant NONE - A fault has not been detected via the parallel detection function
#define CONST_STD_AN_EXP_PDF_NONE 0x0
//! Constant FAULT - A fault has been detected via the parallel detection function
#define CONST_STD_AN_EXP_PDF_FAULT 0x1

//! Field RNPSL - Receive Next Page Storage Location
#define STD_AN_EXP_RNPSL_POS 5
//! Field RNPSL - Receive Next Page Storage Location
#define STD_AN_EXP_RNPSL_MASK 0x20u
//! Constant FIVE - Link partner Next Pages are stored in Register 5
#define CONST_STD_AN_EXP_RNPSL_FIVE 0x0
//! Constant EIGHT - Link partner Next Pages are stored in Register 8
#define CONST_STD_AN_EXP_RNPSL_EIGHT 0x1

//! Field RNPLA - Receive Next Page Location Able
#define STD_AN_EXP_RNPLA_POS 6
//! Field RNPLA - Receive Next Page Location Able
#define STD_AN_EXP_RNPLA_MASK 0x40u
//! Constant UNABLE - Received Next Page storage location is not specified by bit (6.5)
#define CONST_STD_AN_EXP_RNPLA_UNABLE 0x0
//! Constant ABLE - Received Next Page storage location is specified by bit (6.5)
#define CONST_STD_AN_EXP_RNPLA_ABLE 0x1

//! Field RES - Reserved
#define STD_AN_EXP_RES_POS 7
//! Field RES - Reserved
#define STD_AN_EXP_RES_MASK 0xFF80u

//! @}

//! \defgroup STD_AN_NPTX Register STD_AN_NPTX - Auto-Negotiation Next Page Transmit Register (Register 0.7)
//! @{

//! Register Offset (relative)
#define STD_AN_NPTX 0xE
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_AN_NPTX 0x0000000Eu

//! Register Reset Value
#define STD_AN_NPTX_RST 0x2001u

//! Field MCF - Message or Unformatted Code Field
#define STD_AN_NPTX_MCF_POS 0
//! Field MCF - Message or Unformatted Code Field
#define STD_AN_NPTX_MCF_MASK 0x7FFu
//! Constant MCF_2G5BT - Message Page Type is 2.5G BT
#define CONST_STD_AN_NPTX_MCF_MCF_2G5BT 0x009u
//! Constant MCF_1GBT - Message Page Type is 1GBT
#define CONST_STD_AN_NPTX_MCF_MCF_1GBT 0x008u

//! Field TOGG - Toggle
#define STD_AN_NPTX_TOGG_POS 11
//! Field TOGG - Toggle
#define STD_AN_NPTX_TOGG_MASK 0x800u
//! Constant ZERO - Previous value of the transmitted link code word was ONE
#define CONST_STD_AN_NPTX_TOGG_ZERO 0x0
//! Constant ONE - Previous value of the transmitted link code word was ZERO
#define CONST_STD_AN_NPTX_TOGG_ONE 0x1

//! Field ACK2 - Acknowledge 2. GPY doesn't comply
#define STD_AN_NPTX_ACK2_POS 12
//! Field ACK2 - Acknowledge 2. GPY doesn't comply
#define STD_AN_NPTX_ACK2_MASK 0x1000u
//! Constant INACTIVE - Device cannot comply with message
#define CONST_STD_AN_NPTX_ACK2_INACTIVE 0x0
//! Constant ACTIVE - Device will comply with message
#define CONST_STD_AN_NPTX_ACK2_ACTIVE 0x1

//! Field MP - Message Page
#define STD_AN_NPTX_MP_POS 13
//! Field MP - Message Page
#define STD_AN_NPTX_MP_MASK 0x2000u
//! Constant UNFOR - Unformatted page
#define CONST_STD_AN_NPTX_MP_UNFOR 0x0
//! Constant MESSG - Message page
#define CONST_STD_AN_NPTX_MP_MESSG 0x1

//! Field RES - Reserved
#define STD_AN_NPTX_RES_POS 14
//! Field RES - Reserved
#define STD_AN_NPTX_RES_MASK 0x4000u

//! Field NP - Next Page
#define STD_AN_NPTX_NP_POS 15
//! Field NP - Next Page
#define STD_AN_NPTX_NP_MASK 0x8000u
//! Constant INACTIVE - Last page
#define CONST_STD_AN_NPTX_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next page(s) will follow
#define CONST_STD_AN_NPTX_NP_ACTIVE 0x1

//! @}

//! \defgroup STD_AN_NPRX Register STD_AN_NPRX - Auto-Negotiation Link Partner Received Next Page Register (Register 0.8)
//! @{

//! Register Offset (relative)
#define STD_AN_NPRX 0x10
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_AN_NPRX 0x00000010u

//! Register Reset Value
#define STD_AN_NPRX_RST 0x0000u

//! Field MCF - Message or Unformatted Code Field
#define STD_AN_NPRX_MCF_POS 0
//! Field MCF - Message or Unformatted Code Field
#define STD_AN_NPRX_MCF_MASK 0x7FFu
//! Constant MCF_2G5BT - Message Page Type is 2.5G BT
#define CONST_STD_AN_NPRX_MCF_MCF_2G5BT 0x009u
//! Constant MCF_1GBT - Message Page Type is 1GBT
#define CONST_STD_AN_NPRX_MCF_MCF_1GBT 0x008u

//! Field TOGG - Toggle
#define STD_AN_NPRX_TOGG_POS 11
//! Field TOGG - Toggle
#define STD_AN_NPRX_TOGG_MASK 0x800u
//! Constant ZERO - Previous value of the transmitted link code word was equal to ONE
#define CONST_STD_AN_NPRX_TOGG_ZERO 0x0
//! Constant ONE - Previous value of the transmitted link code word was equal to ZERO
#define CONST_STD_AN_NPRX_TOGG_ONE 0x1

//! Field ACK2 - Acknowledge 2
#define STD_AN_NPRX_ACK2_POS 12
//! Field ACK2 - Acknowledge 2
#define STD_AN_NPRX_ACK2_MASK 0x1000u
//! Constant INACTIVE - Device cannot comply with message
#define CONST_STD_AN_NPRX_ACK2_INACTIVE 0x0
//! Constant ACTIVE - Device will comply with message
#define CONST_STD_AN_NPRX_ACK2_ACTIVE 0x1

//! Field MP - Message Page
#define STD_AN_NPRX_MP_POS 13
//! Field MP - Message Page
#define STD_AN_NPRX_MP_MASK 0x2000u
//! Constant UNFOR - Unformatted page
#define CONST_STD_AN_NPRX_MP_UNFOR 0x0
//! Constant MESSG - Message page
#define CONST_STD_AN_NPRX_MP_MESSG 0x1

//! Field ACK - Acknowledge
#define STD_AN_NPRX_ACK_POS 14
//! Field ACK - Acknowledge
#define STD_AN_NPRX_ACK_MASK 0x4000u
//! Constant INACTIVE - The device did not successfully receive its link partner's link code word
#define CONST_STD_AN_NPRX_ACK_INACTIVE 0x0
//! Constant ACTIVE - The device has successfully received its link partner's link code word
#define CONST_STD_AN_NPRX_ACK_ACTIVE 0x1

//! Field NP - Next Page
#define STD_AN_NPRX_NP_POS 15
//! Field NP - Next Page
#define STD_AN_NPRX_NP_MASK 0x8000u
//! Constant INACTIVE - No next pages to follow
#define CONST_STD_AN_NPRX_NP_INACTIVE 0x0
//! Constant ACTIVE - Additional next page(s) will follow
#define CONST_STD_AN_NPRX_NP_ACTIVE 0x1

//! @}

//! \defgroup STD_GCTRL Register STD_GCTRL - Gigabit Control Register (Register 0.9)
//! @{

//! Register Offset (relative)
#define STD_GCTRL 0x12
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_GCTRL 0x00000012u

//! Register Reset Value
#define STD_GCTRL_RST 0x0200u

//! Field RES - Reserved
#define STD_GCTRL_RES_POS 0
//! Field RES - Reserved
#define STD_GCTRL_RES_MASK 0xFFu

//! Field MBTHD - 1000BASE-T Half-Duplex
#define STD_GCTRL_MBTHD_POS 8
//! Field MBTHD - 1000BASE-T Half-Duplex
#define STD_GCTRL_MBTHD_MASK 0x100u
//! Constant DISABLED - Advertise PHY as not 1000BASE-T half-duplex capable
#define CONST_STD_GCTRL_MBTHD_DISABLED 0x0
//! Constant ENABLED - Advertise PHY as 1000BASE-T half-duplex capable
#define CONST_STD_GCTRL_MBTHD_ENABLED 0x1

//! Field MBTFD - 1000BASE-T Full-Duplex
#define STD_GCTRL_MBTFD_POS 9
//! Field MBTFD - 1000BASE-T Full-Duplex
#define STD_GCTRL_MBTFD_MASK 0x200u
//! Constant DISABLED - Advertise PHY as not 1000BASE-T full-duplex capable
#define CONST_STD_GCTRL_MBTFD_DISABLED 0x0
//! Constant ENABLED - Advertise PHY as 1000BASE-T full-duplex capable
#define CONST_STD_GCTRL_MBTFD_ENABLED 0x1

//! Field MSPT - Master/Slave Port Type
#define STD_GCTRL_MSPT_POS 10
//! Field MSPT - Master/Slave Port Type
#define STD_GCTRL_MSPT_MASK 0x400u
//! Constant SPD - Single-port device
#define CONST_STD_GCTRL_MSPT_SPD 0x0
//! Constant MPD - Multi-port device
#define CONST_STD_GCTRL_MSPT_MPD 0x1

//! Field MS - Master/Slave Config Value
#define STD_GCTRL_MS_POS 11
//! Field MS - Master/Slave Config Value
#define STD_GCTRL_MS_MASK 0x800u
//! Constant SLAVE - Configure PHY as SLAVE during master/slave negotiation
#define CONST_STD_GCTRL_MS_SLAVE 0x0
//! Constant MASTER - Configure PHY as MASTER during master/slave negotiation
#define CONST_STD_GCTRL_MS_MASTER 0x1

//! Field MSEN - Master/Slave Manual Configuration Enable
#define STD_GCTRL_MSEN_POS 12
//! Field MSEN - Master/Slave Manual Configuration Enable
#define STD_GCTRL_MSEN_MASK 0x1000u
//! Constant DISABLED - Disable master/slave manual configuration value
#define CONST_STD_GCTRL_MSEN_DISABLED 0x0
//! Constant ENABLED - Enable master/slave manual configuration value
#define CONST_STD_GCTRL_MSEN_ENABLED 0x1

//! Field TM - Transmitter Test Mode
#define STD_GCTRL_TM_POS 13
//! Field TM - Transmitter Test Mode
#define STD_GCTRL_TM_MASK 0xE000u
//! Constant NOP - Normal operation
#define CONST_STD_GCTRL_TM_NOP 0x0
//! Constant WAV - Test mode 1 transmit waveform test
#define CONST_STD_GCTRL_TM_WAV 0x1
//! Constant JITM - Test mode 2 transmit jitter test in MASTER mode
#define CONST_STD_GCTRL_TM_JITM 0x2
//! Constant JITS - Test mode 3 transmit jitter test in SLAVE mode
#define CONST_STD_GCTRL_TM_JITS 0x3
//! Constant DIST - Test mode 4 transmitter distortion test
#define CONST_STD_GCTRL_TM_DIST 0x4

//! @}

//! \defgroup STD_GSTAT Register STD_GSTAT - Gigabit Status Register (Register 0.10)
//! @{

//! Register Offset (relative)
#define STD_GSTAT 0x14
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_GSTAT 0x00000014u

//! Register Reset Value
#define STD_GSTAT_RST 0x0000u

//! Field IEC - Idle Error Count
#define STD_GSTAT_IEC_POS 0
//! Field IEC - Idle Error Count
#define STD_GSTAT_IEC_MASK 0xFFu

//! Field RES - Reserved
#define STD_GSTAT_RES_POS 8
//! Field RES - Reserved
#define STD_GSTAT_RES_MASK 0x300u

//! Field MBTHD - Link Partner Capable of Operating 1000BASE-T Half-Duplex
#define STD_GSTAT_MBTHD_POS 10
//! Field MBTHD - Link Partner Capable of Operating 1000BASE-T Half-Duplex
#define STD_GSTAT_MBTHD_MASK 0x400u
//! Constant DISABLED - Link partner is not capable of operating 1000BASE-T half-duplex
#define CONST_STD_GSTAT_MBTHD_DISABLED 0x0
//! Constant ENABLED - Link partner is capable of operating 1000BASE-T half-duplex
#define CONST_STD_GSTAT_MBTHD_ENABLED 0x1

//! Field MBTFD - Link Partner Capable of Operating 1000BASE-T Full-Duplex
#define STD_GSTAT_MBTFD_POS 11
//! Field MBTFD - Link Partner Capable of Operating 1000BASE-T Full-Duplex
#define STD_GSTAT_MBTFD_MASK 0x800u
//! Constant DISABLED - Link partner is not capable of operating 1000BASE-T full-duplex
#define CONST_STD_GSTAT_MBTFD_DISABLED 0x0
//! Constant ENABLED - Link partner is capable of operating 1000BASE-T full-duplex
#define CONST_STD_GSTAT_MBTFD_ENABLED 0x1

//! Field RRXSTAT - Remote Receiver Status
#define STD_GSTAT_RRXSTAT_POS 12
//! Field RRXSTAT - Remote Receiver Status
#define STD_GSTAT_RRXSTAT_MASK 0x1000u
//! Constant NOK - Remote receiver not OK
#define CONST_STD_GSTAT_RRXSTAT_NOK 0x0
//! Constant OK - Remote receiver OK
#define CONST_STD_GSTAT_RRXSTAT_OK 0x1

//! Field LRXSTAT - Local Receiver Status
#define STD_GSTAT_LRXSTAT_POS 13
//! Field LRXSTAT - Local Receiver Status
#define STD_GSTAT_LRXSTAT_MASK 0x2000u
//! Constant NOK - Local receiver not OK
#define CONST_STD_GSTAT_LRXSTAT_NOK 0x0
//! Constant OK - Local receiver OK
#define CONST_STD_GSTAT_LRXSTAT_OK 0x1

//! Field MSRES - Master/Slave Configuration Resolution
#define STD_GSTAT_MSRES_POS 14
//! Field MSRES - Master/Slave Configuration Resolution
#define STD_GSTAT_MSRES_MASK 0x4000u
//! Constant SLAVE - Local PHY configuration resolved to SLAVE
#define CONST_STD_GSTAT_MSRES_SLAVE 0x0
//! Constant MASTER - Local PHY configuration resolved to MASTER
#define CONST_STD_GSTAT_MSRES_MASTER 0x1

//! Field MSFAULT - Master/Slave Manual Configuration Fault
#define STD_GSTAT_MSFAULT_POS 15
//! Field MSFAULT - Master/Slave Manual Configuration Fault
#define STD_GSTAT_MSFAULT_MASK 0x8000u
//! Constant OK - Master/slave manual configuration resolved successfully
#define CONST_STD_GSTAT_MSFAULT_OK 0x0
//! Constant NOK - Master/slave manual configuration resolved with a fault
#define CONST_STD_GSTAT_MSFAULT_NOK 0x1

//! @}

//! \defgroup STD_RES1 Register STD_RES1 - Reserved
//! @{

//! Register Offset (relative)
#define STD_RES1 0x16
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_RES1 0x00000016u

//! Register Reset Value
#define STD_RES1_RST 0x0000u

//! Field RES - Reserved
#define STD_RES1_RES_POS 0
//! Field RES - Reserved
#define STD_RES1_RES_MASK 0xFFFFu

//! @}

//! \defgroup STD_RES2 Register STD_RES2 - Reserved
//! @{

//! Register Offset (relative)
#define STD_RES2 0x18
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_RES2 0x00000018u

//! Register Reset Value
#define STD_RES2_RST 0x0000u

//! Field RES - Reserved
#define STD_RES2_RES_POS 0
//! Field RES - Reserved
#define STD_RES2_RES_MASK 0xFFFFu

//! @}

//! \defgroup STD_MMDCTRL Register STD_MMDCTRL - MMD Access Control Register (Register 0.13)
//! @{

//! Register Offset (relative)
#define STD_MMDCTRL 0x1A
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_MMDCTRL 0x0000001Au

//! Register Reset Value
#define STD_MMDCTRL_RST 0x0000u

//! Field DEVAD - Device Address
#define STD_MMDCTRL_DEVAD_POS 0
//! Field DEVAD - Device Address
#define STD_MMDCTRL_DEVAD_MASK 0x1Fu

//! Field RESL - Reserved
#define STD_MMDCTRL_RESL_POS 5
//! Field RESL - Reserved
#define STD_MMDCTRL_RESL_MASK 0xE0u

//! Field RESH - Reserved
#define STD_MMDCTRL_RESH_POS 8
//! Field RESH - Reserved
#define STD_MMDCTRL_RESH_MASK 0x3F00u

//! Field ACTYPE - Access Type Function
#define STD_MMDCTRL_ACTYPE_POS 14
//! Field ACTYPE - Access Type Function
#define STD_MMDCTRL_ACTYPE_MASK 0xC000u
//! Constant ADDRESS - Accesses to register MMDDATA access the MMD individual address register
#define CONST_STD_MMDCTRL_ACTYPE_ADDRESS 0x0
//! Constant DATA - Accesses to register MMDDATA access the register within the MMD selected
#define CONST_STD_MMDCTRL_ACTYPE_DATA 0x1
//! Constant DATA_PI - Accesses to register MMDDATA access the register within the MMD selected
#define CONST_STD_MMDCTRL_ACTYPE_DATA_PI 0x2
//! Constant DATA_PIWR - Accesses to register MMDDATA access the register within the MMD selected
#define CONST_STD_MMDCTRL_ACTYPE_DATA_PIWR 0x3

//! @}

//! \defgroup STD_MMDDATA Register STD_MMDDATA - MMD Access Data Register (Register 0.14)
//! @{

//! Register Offset (relative)
#define STD_MMDDATA 0x1C
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_MMDDATA 0x0000001Cu

//! Register Reset Value
#define STD_MMDDATA_RST 0x0000u

//! Field ADDR_DATA - Address or Data Register
#define STD_MMDDATA_ADDR_DATA_POS 0
//! Field ADDR_DATA - Address or Data Register
#define STD_MMDDATA_ADDR_DATA_MASK 0xFFFFu

//! @}

//! \defgroup STD_XSTAT Register STD_XSTAT - Extended Status Register (Register 0.15)
//! @{

//! Register Offset (relative)
#define STD_XSTAT 0x1E
//! Register Offset (absolute) for 1st Instance STD
#define STD_STD_XSTAT 0x0000001Eu

//! Register Reset Value
#define STD_XSTAT_RST 0x2000u

//! Field RESL - Reserved
#define STD_XSTAT_RESL_POS 0
//! Field RESL - Reserved
#define STD_XSTAT_RESL_MASK 0xFFu

//! Field RESH - Reserved
#define STD_XSTAT_RESH_POS 8
//! Field RESH - Reserved
#define STD_XSTAT_RESH_MASK 0xF00u

//! Field MBTH - 1000BASE-T Half-Duplex Capability
#define STD_XSTAT_MBTH_POS 12
//! Field MBTH - 1000BASE-T Half-Duplex Capability
#define STD_XSTAT_MBTH_MASK 0x1000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_XSTAT_MBTH_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_XSTAT_MBTH_ENABLED 0x1

//! Field MBTF - 1000BASE-T Full-Duplex Capability
#define STD_XSTAT_MBTF_POS 13
//! Field MBTF - 1000BASE-T Full-Duplex Capability
#define STD_XSTAT_MBTF_MASK 0x2000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_XSTAT_MBTF_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_XSTAT_MBTF_ENABLED 0x1

//! Field MBXH - 1000BASE-X Half-Duplex Capability
#define STD_XSTAT_MBXH_POS 14
//! Field MBXH - 1000BASE-X Half-Duplex Capability
#define STD_XSTAT_MBXH_MASK 0x4000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_XSTAT_MBXH_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_XSTAT_MBXH_ENABLED 0x1

//! Field MBXF - 1000BASE-X Full-Duplex Capability
#define STD_XSTAT_MBXF_POS 15
//! Field MBXF - 1000BASE-X Full-Duplex Capability
#define STD_XSTAT_MBXF_MASK 0x8000u
//! Constant DISABLED - PHY does not support this mode
#define CONST_STD_XSTAT_MBXF_DISABLED 0x0
//! Constant ENABLED - PHY supports this mode
#define CONST_STD_XSTAT_MBXF_ENABLED 0x1

//! @}

//! @}

#endif
