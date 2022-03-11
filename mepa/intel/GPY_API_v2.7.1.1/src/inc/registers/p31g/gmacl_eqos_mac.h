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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/GMACL_EQOS_MAC_def.xml
// Register File Name  : GMACL_EQOS_MAC
// Register File Title : GMACL EQOS MAC
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GMACL_EQOS_MAC_H
#define _GMACL_EQOS_MAC_H

//! \defgroup GMACL_EQOS_MAC Register File GMACL_EQOS_MAC - GMACL EQOS MAC
//! @{

//! Base Address of GMACL_EQOS_MAC for P31G
#define GMACL_EQOS_MAC_MODULE_BASE 0x00D32000u
//! Base Address of GMACL_EQOS_MAC for P34X
#define P34X_GMACL_EQOS_MAC_MODULE_BASE 0x00A30000u

//! \defgroup GMACL_MAC_CONFIGURATION_L Register GMACL_MAC_CONFIGURATION_L - GMACL MAC Configuration low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_CONFIGURATION_L 0x0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_CONFIGURATION_L 0x00D32000u

//! Register Reset Value
#define GMACL_MAC_CONFIGURATION_L_RST 0x00000000u

//! Field RE - Receiver Enable
#define GMACL_MAC_CONFIGURATION_L_RE_POS 0
//! Field RE - Receiver Enable
#define GMACL_MAC_CONFIGURATION_L_RE_MASK 0x1u

//! Field TE - Transmitter Enable
#define GMACL_MAC_CONFIGURATION_L_TE_POS 1
//! Field TE - Transmitter Enable
#define GMACL_MAC_CONFIGURATION_L_TE_MASK 0x2u

//! Field PRELEN - Preamble Length for Transmit packets
#define GMACL_MAC_CONFIGURATION_L_PRELEN_POS 2
//! Field PRELEN - Preamble Length for Transmit packets
#define GMACL_MAC_CONFIGURATION_L_PRELEN_MASK 0xCu

//! Field DC - Deferral Check
#define GMACL_MAC_CONFIGURATION_L_DC_POS 4
//! Field DC - Deferral Check
#define GMACL_MAC_CONFIGURATION_L_DC_MASK 0x10u

//! Field BL - Back-Off Limit
#define GMACL_MAC_CONFIGURATION_L_BL_POS 5
//! Field BL - Back-Off Limit
#define GMACL_MAC_CONFIGURATION_L_BL_MASK 0x60u

//! Field RESERVED_7 - Reserved.
#define GMACL_MAC_CONFIGURATION_L_RESERVED_7_POS 7
//! Field RESERVED_7 - Reserved.
#define GMACL_MAC_CONFIGURATION_L_RESERVED_7_MASK 0x80u

//! Field DR - Disable Retry
#define GMACL_MAC_CONFIGURATION_L_DR_POS 8
//! Field DR - Disable Retry
#define GMACL_MAC_CONFIGURATION_L_DR_MASK 0x100u

//! Field DCRS - Disable Carrier Sense During Transmission
#define GMACL_MAC_CONFIGURATION_L_DCRS_POS 9
//! Field DCRS - Disable Carrier Sense During Transmission
#define GMACL_MAC_CONFIGURATION_L_DCRS_MASK 0x200u

//! Field DO - Disable Receive Own
#define GMACL_MAC_CONFIGURATION_L_DO_POS 10
//! Field DO - Disable Receive Own
#define GMACL_MAC_CONFIGURATION_L_DO_MASK 0x400u

//! Field ECRSFD - Enable Carrier Sense Before Transmission in Full-Duplex Mode
#define GMACL_MAC_CONFIGURATION_L_ECRSFD_POS 11
//! Field ECRSFD - Enable Carrier Sense Before Transmission in Full-Duplex Mode
#define GMACL_MAC_CONFIGURATION_L_ECRSFD_MASK 0x800u

//! Field LM - Loopback Mode
#define GMACL_MAC_CONFIGURATION_L_LM_POS 12
//! Field LM - Loopback Mode
#define GMACL_MAC_CONFIGURATION_L_LM_MASK 0x1000u

//! Field DM - Duplex Mode
#define GMACL_MAC_CONFIGURATION_L_DM_POS 13
//! Field DM - Duplex Mode
#define GMACL_MAC_CONFIGURATION_L_DM_MASK 0x2000u

//! Field FES - Speed
#define GMACL_MAC_CONFIGURATION_L_FES_POS 14
//! Field FES - Speed
#define GMACL_MAC_CONFIGURATION_L_FES_MASK 0x4000u

//! Field PS - Port Select
#define GMACL_MAC_CONFIGURATION_L_PS_POS 15
//! Field PS - Port Select
#define GMACL_MAC_CONFIGURATION_L_PS_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_CONFIGURATION_H Register GMACL_MAC_CONFIGURATION_H - GMACL MAC Configuration high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_CONFIGURATION_H 0x4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_CONFIGURATION_H 0x00D32004u

//! Register Reset Value
#define GMACL_MAC_CONFIGURATION_H_RST 0x00000000u

//! Field JE - Jumbo Packet Enable
#define GMACL_MAC_CONFIGURATION_H_JE_POS 0
//! Field JE - Jumbo Packet Enable
#define GMACL_MAC_CONFIGURATION_H_JE_MASK 0x1u

//! Field JD - Jabber Disable
#define GMACL_MAC_CONFIGURATION_H_JD_POS 1
//! Field JD - Jabber Disable
#define GMACL_MAC_CONFIGURATION_H_JD_MASK 0x2u

//! Field BE - Packet Burst Enable
#define GMACL_MAC_CONFIGURATION_H_BE_POS 2
//! Field BE - Packet Burst Enable
#define GMACL_MAC_CONFIGURATION_H_BE_MASK 0x4u

//! Field WD - Watchdog Disable
#define GMACL_MAC_CONFIGURATION_H_WD_POS 3
//! Field WD - Watchdog Disable
#define GMACL_MAC_CONFIGURATION_H_WD_MASK 0x8u

//! Field ACS - Automatic Pad or CRC Stripping
#define GMACL_MAC_CONFIGURATION_H_ACS_POS 4
//! Field ACS - Automatic Pad or CRC Stripping
#define GMACL_MAC_CONFIGURATION_H_ACS_MASK 0x10u

//! Field CST - CRC stripping for Type packets
#define GMACL_MAC_CONFIGURATION_H_CST_POS 5
//! Field CST - CRC stripping for Type packets
#define GMACL_MAC_CONFIGURATION_H_CST_MASK 0x20u

//! Field S2KP - IEEE 802.3as Support for 2K Packets
#define GMACL_MAC_CONFIGURATION_H_S2KP_POS 6
//! Field S2KP - IEEE 802.3as Support for 2K Packets
#define GMACL_MAC_CONFIGURATION_H_S2KP_MASK 0x40u

//! Field GPSLCE - Giant Packet Size Limit Control Enable
#define GMACL_MAC_CONFIGURATION_H_GPSLCE_POS 7
//! Field GPSLCE - Giant Packet Size Limit Control Enable
#define GMACL_MAC_CONFIGURATION_H_GPSLCE_MASK 0x80u

//! Field IPG - Inter-Packet Gap
#define GMACL_MAC_CONFIGURATION_H_IPG_POS 8
//! Field IPG - Inter-Packet Gap
#define GMACL_MAC_CONFIGURATION_H_IPG_MASK 0x700u

//! Field IPC - Checksum Offload
#define GMACL_MAC_CONFIGURATION_H_IPC_POS 11
//! Field IPC - Checksum Offload
#define GMACL_MAC_CONFIGURATION_H_IPC_MASK 0x800u

//! Field RESERVED_SARC - Reserved.
#define GMACL_MAC_CONFIGURATION_H_RESERVED_SARC_POS 12
//! Field RESERVED_SARC - Reserved.
#define GMACL_MAC_CONFIGURATION_H_RESERVED_SARC_MASK 0x7000u

//! Field RESERVED_ARPEN - Reserved.
#define GMACL_MAC_CONFIGURATION_H_RESERVED_ARPEN_POS 15
//! Field RESERVED_ARPEN - Reserved.
#define GMACL_MAC_CONFIGURATION_H_RESERVED_ARPEN_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_EXT_CONFIGURATION_L Register GMACL_MAC_EXT_CONFIGURATION_L - GMACL MAC Ext Configuration low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_EXT_CONFIGURATION_L 0x8
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_EXT_CONFIGURATION_L 0x00D32008u

//! Register Reset Value
#define GMACL_MAC_EXT_CONFIGURATION_L_RST 0x00000000u

//! Field GPSL - Giant Packet Size Limit
#define GMACL_MAC_EXT_CONFIGURATION_L_GPSL_POS 0
//! Field GPSL - Giant Packet Size Limit
#define GMACL_MAC_EXT_CONFIGURATION_L_GPSL_MASK 0x3FFFu

//! Field RESERVED_15_14 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_L_RESERVED_15_14_POS 14
//! Field RESERVED_15_14 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_L_RESERVED_15_14_MASK 0xC000u

//! @}

//! \defgroup GMACL_MAC_EXT_CONFIGURATION_H Register GMACL_MAC_EXT_CONFIGURATION_H - GMACL MAC Ext Configuration high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_EXT_CONFIGURATION_H 0xC
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_EXT_CONFIGURATION_H 0x00D3200Cu

//! Register Reset Value
#define GMACL_MAC_EXT_CONFIGURATION_H_RST 0x00000000u

//! Field DCRCC - Disable CRC Checking for Received Packets
#define GMACL_MAC_EXT_CONFIGURATION_H_DCRCC_POS 0
//! Field DCRCC - Disable CRC Checking for Received Packets
#define GMACL_MAC_EXT_CONFIGURATION_H_DCRCC_MASK 0x1u

//! Field SPEN - Slow Protocol Detection Enable
#define GMACL_MAC_EXT_CONFIGURATION_H_SPEN_POS 1
//! Field SPEN - Slow Protocol Detection Enable
#define GMACL_MAC_EXT_CONFIGURATION_H_SPEN_MASK 0x2u

//! Field USP - Unicast Slow Protocol Packet Detect
#define GMACL_MAC_EXT_CONFIGURATION_H_USP_POS 2
//! Field USP - Unicast Slow Protocol Packet Detect
#define GMACL_MAC_EXT_CONFIGURATION_H_USP_MASK 0x4u

//! Field RESERVED_PDC - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_PDC_POS 3
//! Field RESERVED_PDC - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_PDC_MASK 0x8u

//! Field RESERVED_HDSMS - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_HDSMS_POS 4
//! Field RESERVED_HDSMS - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_HDSMS_MASK 0x70u

//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_23_MASK 0x80u

//! Field EIPGEN - Extended Inter-Packet Gap Enable
#define GMACL_MAC_EXT_CONFIGURATION_H_EIPGEN_POS 8
//! Field EIPGEN - Extended Inter-Packet Gap Enable
#define GMACL_MAC_EXT_CONFIGURATION_H_EIPGEN_MASK 0x100u

//! Field EIPG - Extended Inter-Packet Gap
#define GMACL_MAC_EXT_CONFIGURATION_H_EIPG_POS 9
//! Field EIPG - Extended Inter-Packet Gap
#define GMACL_MAC_EXT_CONFIGURATION_H_EIPG_MASK 0x3E00u

//! Field RESERVED_31_30 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_31_30_POS 14
//! Field RESERVED_31_30 - Reserved.
#define GMACL_MAC_EXT_CONFIGURATION_H_RESERVED_31_30_MASK 0xC000u

//! @}

//! \defgroup GMACL_MAC_PACKET_FILTER_L Register GMACL_MAC_PACKET_FILTER_L - GMACL MAC Packet Filter low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PACKET_FILTER_L 0x10
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PACKET_FILTER_L 0x00D32010u

//! Register Reset Value
#define GMACL_MAC_PACKET_FILTER_L_RST 0x00000000u

//! Field PR - Promiscuous Mode
#define GMACL_MAC_PACKET_FILTER_L_PR_POS 0
//! Field PR - Promiscuous Mode
#define GMACL_MAC_PACKET_FILTER_L_PR_MASK 0x1u

//! Field RESERVED_HUC - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HUC_POS 1
//! Field RESERVED_HUC - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HUC_MASK 0x2u

//! Field RESERVED_HMC - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HMC_POS 2
//! Field RESERVED_HMC - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HMC_MASK 0x4u

//! Field DAIF - DA Inverse Filtering
#define GMACL_MAC_PACKET_FILTER_L_DAIF_POS 3
//! Field DAIF - DA Inverse Filtering
#define GMACL_MAC_PACKET_FILTER_L_DAIF_MASK 0x8u

//! Field PM - Pass All Multicast
#define GMACL_MAC_PACKET_FILTER_L_PM_POS 4
//! Field PM - Pass All Multicast
#define GMACL_MAC_PACKET_FILTER_L_PM_MASK 0x10u

//! Field DBF - Disable Broadcast Packets
#define GMACL_MAC_PACKET_FILTER_L_DBF_POS 5
//! Field DBF - Disable Broadcast Packets
#define GMACL_MAC_PACKET_FILTER_L_DBF_MASK 0x20u

//! Field PCF - Pass Control Packets
#define GMACL_MAC_PACKET_FILTER_L_PCF_POS 6
//! Field PCF - Pass Control Packets
#define GMACL_MAC_PACKET_FILTER_L_PCF_MASK 0xC0u

//! Field SAIF - SA Inverse Filtering
#define GMACL_MAC_PACKET_FILTER_L_SAIF_POS 8
//! Field SAIF - SA Inverse Filtering
#define GMACL_MAC_PACKET_FILTER_L_SAIF_MASK 0x100u

//! Field SAF - Source Address Filter Enable
#define GMACL_MAC_PACKET_FILTER_L_SAF_POS 9
//! Field SAF - Source Address Filter Enable
#define GMACL_MAC_PACKET_FILTER_L_SAF_MASK 0x200u

//! Field RESERVED_HPF - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HPF_POS 10
//! Field RESERVED_HPF - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_HPF_MASK 0x400u

//! Field RESERVED_15_11 - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_15_11_POS 11
//! Field RESERVED_15_11 - Reserved.
#define GMACL_MAC_PACKET_FILTER_L_RESERVED_15_11_MASK 0xF800u

//! @}

//! \defgroup GMACL_MAC_PACKET_FILTER_H Register GMACL_MAC_PACKET_FILTER_H - GMACL MAC Packet Filter high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PACKET_FILTER_H 0x14
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PACKET_FILTER_H 0x00D32014u

//! Register Reset Value
#define GMACL_MAC_PACKET_FILTER_H_RST 0x00000000u

//! Field VTFE - VLAN Tag Filter Enable
#define GMACL_MAC_PACKET_FILTER_H_VTFE_POS 0
//! Field VTFE - VLAN Tag Filter Enable
#define GMACL_MAC_PACKET_FILTER_H_VTFE_MASK 0x1u

//! Field RESERVED_19_17 - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_19_17_POS 1
//! Field RESERVED_19_17 - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_19_17_MASK 0xEu

//! Field RESERVED_IPFE - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_IPFE_POS 4
//! Field RESERVED_IPFE - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_IPFE_MASK 0x10u

//! Field RESERVED_DNTU - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_DNTU_POS 5
//! Field RESERVED_DNTU - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_DNTU_MASK 0x20u

//! Field RESERVED_30_22 - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_30_22_POS 6
//! Field RESERVED_30_22 - Reserved.
#define GMACL_MAC_PACKET_FILTER_H_RESERVED_30_22_MASK 0x7FC0u

//! Field RA - Receive All
#define GMACL_MAC_PACKET_FILTER_H_RA_POS 15
//! Field RA - Receive All
#define GMACL_MAC_PACKET_FILTER_H_RA_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_WATCHDOG_TIMEOUT_L Register GMACL_MAC_WATCHDOG_TIMEOUT_L - GMACL MAC Watchdog Timeout low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_WATCHDOG_TIMEOUT_L 0x18
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_WATCHDOG_TIMEOUT_L 0x00D32018u

//! Register Reset Value
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_RST 0x00000000u

//! Field WTO - Watchdog Timeout
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_WTO_POS 0
//! Field WTO - Watchdog Timeout
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_WTO_MASK 0xFu

//! Field RESERVED_7_4 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_RESERVED_7_4_POS 4
//! Field RESERVED_7_4 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_RESERVED_7_4_MASK 0xF0u

//! Field PWE - Programmable Watchdog Enable
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_PWE_POS 8
//! Field PWE - Programmable Watchdog Enable
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_PWE_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACL_MAC_WATCHDOG_TIMEOUT_H Register GMACL_MAC_WATCHDOG_TIMEOUT_H - GMACL MAC Watchdog Timeout high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_WATCHDOG_TIMEOUT_H 0x1C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_WATCHDOG_TIMEOUT_H 0x00D3201Cu

//! Register Reset Value
#define GMACL_MAC_WATCHDOG_TIMEOUT_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_WATCHDOG_TIMEOUT_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_VLAN_TAG_L Register GMACL_MAC_VLAN_TAG_L - GMACL MAC VLAN Tag low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_VLAN_TAG_L 0xA0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_VLAN_TAG_L 0x00D320A0u

//! Register Reset Value
#define GMACL_MAC_VLAN_TAG_L_RST 0x00000000u

//! Field VL - VLAN Tag Identifier for Receive Packets
#define GMACL_MAC_VLAN_TAG_L_VL_POS 0
//! Field VL - VLAN Tag Identifier for Receive Packets
#define GMACL_MAC_VLAN_TAG_L_VL_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_VLAN_TAG_H Register GMACL_MAC_VLAN_TAG_H - GMACL MAC VLAN Tag high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_VLAN_TAG_H 0xA4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_VLAN_TAG_H 0x00D320A4u

//! Register Reset Value
#define GMACL_MAC_VLAN_TAG_H_RST 0x00000000u

//! Field ETV - Enable 12-Bit VLAN Tag Comparison
#define GMACL_MAC_VLAN_TAG_H_ETV_POS 0
//! Field ETV - Enable 12-Bit VLAN Tag Comparison
#define GMACL_MAC_VLAN_TAG_H_ETV_MASK 0x1u

//! Field VTIM - VLAN Tag Inverse Match Enable
#define GMACL_MAC_VLAN_TAG_H_VTIM_POS 1
//! Field VTIM - VLAN Tag Inverse Match Enable
#define GMACL_MAC_VLAN_TAG_H_VTIM_MASK 0x2u

//! Field ESVL - Enable S-VLAN
#define GMACL_MAC_VLAN_TAG_H_ESVL_POS 2
//! Field ESVL - Enable S-VLAN
#define GMACL_MAC_VLAN_TAG_H_ESVL_MASK 0x4u

//! Field ERSVLM - Enable Receive S-VLAN Match
#define GMACL_MAC_VLAN_TAG_H_ERSVLM_POS 3
//! Field ERSVLM - Enable Receive S-VLAN Match
#define GMACL_MAC_VLAN_TAG_H_ERSVLM_MASK 0x8u

//! Field DOVLTC - Disable VLAN Type Check
#define GMACL_MAC_VLAN_TAG_H_DOVLTC_POS 4
//! Field DOVLTC - Disable VLAN Type Check
#define GMACL_MAC_VLAN_TAG_H_DOVLTC_MASK 0x10u

//! Field EVLS - Enable VLAN Tag Stripping on Receive
#define GMACL_MAC_VLAN_TAG_H_EVLS_POS 5
//! Field EVLS - Enable VLAN Tag Stripping on Receive
#define GMACL_MAC_VLAN_TAG_H_EVLS_MASK 0x60u

//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_23_MASK 0x80u

//! Field EVLRXS - Enable VLAN Tag in Rx status
#define GMACL_MAC_VLAN_TAG_H_EVLRXS_POS 8
//! Field EVLRXS - Enable VLAN Tag in Rx status
#define GMACL_MAC_VLAN_TAG_H_EVLRXS_MASK 0x100u

//! Field RESERVED_VTHM - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_VTHM_POS 9
//! Field RESERVED_VTHM - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_VTHM_MASK 0x200u

//! Field EDVLP - Enable Double VLAN Processing
#define GMACL_MAC_VLAN_TAG_H_EDVLP_POS 10
//! Field EDVLP - Enable Double VLAN Processing
#define GMACL_MAC_VLAN_TAG_H_EDVLP_MASK 0x400u

//! Field ERIVLT - Enable Inner VLAN Tag
#define GMACL_MAC_VLAN_TAG_H_ERIVLT_POS 11
//! Field ERIVLT - Enable Inner VLAN Tag
#define GMACL_MAC_VLAN_TAG_H_ERIVLT_MASK 0x800u

//! Field EIVLS - Enable Inner VLAN Tag Stripping on Receive
#define GMACL_MAC_VLAN_TAG_H_EIVLS_POS 12
//! Field EIVLS - Enable Inner VLAN Tag Stripping on Receive
#define GMACL_MAC_VLAN_TAG_H_EIVLS_MASK 0x3000u

//! Field RESERVED_30 - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_30_POS 14
//! Field RESERVED_30 - Reserved.
#define GMACL_MAC_VLAN_TAG_H_RESERVED_30_MASK 0x4000u

//! Field EIVLRXS - Enable Inner VLAN Tag in Rx Status
#define GMACL_MAC_VLAN_TAG_H_EIVLRXS_POS 15
//! Field EIVLRXS - Enable Inner VLAN Tag in Rx Status
#define GMACL_MAC_VLAN_TAG_H_EIVLRXS_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_Q0_TX_FLOW_CTRL_L Register GMACL_MAC_Q0_TX_FLOW_CTRL_L - GMACL MAC Q0 Tx Flow Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L 0xE0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_Q0_TX_FLOW_CTRL_L 0x00D320E0u

//! Register Reset Value
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_RST 0x00000000u

//! Field FCB_BPA - Flow Control Busy or Backpressure Activate
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA_POS 0
//! Field FCB_BPA - Flow Control Busy or Backpressure Activate
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA_MASK 0x1u

//! Field TFE - Transmit Flow Control Enable
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_TFE_POS 1
//! Field TFE - Transmit Flow Control Enable
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_TFE_MASK 0x2u

//! Field RESERVED_3_2 - Reserved.
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_3_2_POS 2
//! Field RESERVED_3_2 - Reserved.
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_3_2_MASK 0xCu

//! Field PLT - Pause Low Threshold
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_PLT_POS 4
//! Field PLT - Pause Low Threshold
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_PLT_MASK 0x70u

//! Field DZPQ - Disable Zero-Quanta Pause
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_DZPQ_POS 7
//! Field DZPQ - Disable Zero-Quanta Pause
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_DZPQ_MASK 0x80u

//! Field RESERVED_15_8 - Reserved.
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_15_8_POS 8
//! Field RESERVED_15_8 - Reserved.
#define GMACL_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_15_8_MASK 0xFF00u

//! @}

//! \defgroup GMACL_MAC_Q0_TX_FLOW_CTRL_H Register GMACL_MAC_Q0_TX_FLOW_CTRL_H - GMACL MAC Q0 Tx Flow Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_Q0_TX_FLOW_CTRL_H 0xE4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_Q0_TX_FLOW_CTRL_H 0x00D320E4u

//! Register Reset Value
#define GMACL_MAC_Q0_TX_FLOW_CTRL_H_RST 0x00000000u

//! Field PT - Pause Time
#define GMACL_MAC_Q0_TX_FLOW_CTRL_H_PT_POS 0
//! Field PT - Pause Time
#define GMACL_MAC_Q0_TX_FLOW_CTRL_H_PT_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_RX_FLOW_CTRL_L Register GMACL_MAC_RX_FLOW_CTRL_L - GMACL MAC Rx Flow Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_RX_FLOW_CTRL_L 0x120
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_RX_FLOW_CTRL_L 0x00D32120u

//! Register Reset Value
#define GMACL_MAC_RX_FLOW_CTRL_L_RST 0x00000000u

//! Field RFE - Receive Flow Control Enable
#define GMACL_MAC_RX_FLOW_CTRL_L_RFE_POS 0
//! Field RFE - Receive Flow Control Enable
#define GMACL_MAC_RX_FLOW_CTRL_L_RFE_MASK 0x1u

//! Field UP - Unicast Pause Packet Detect
#define GMACL_MAC_RX_FLOW_CTRL_L_UP_POS 1
//! Field UP - Unicast Pause Packet Detect
#define GMACL_MAC_RX_FLOW_CTRL_L_UP_MASK 0x2u

//! Field RESERVED_7_2 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_7_2_POS 2
//! Field RESERVED_7_2 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_7_2_MASK 0xFCu

//! Field RESERVED_PFCE - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_PFCE_POS 8
//! Field RESERVED_PFCE - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_PFCE_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACL_MAC_RX_FLOW_CTRL_H Register GMACL_MAC_RX_FLOW_CTRL_H - GMACL MAC Rx Flow Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_RX_FLOW_CTRL_H 0x124
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_RX_FLOW_CTRL_H 0x00D32124u

//! Register Reset Value
#define GMACL_MAC_RX_FLOW_CTRL_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_FLOW_CTRL_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_INTERRUPT_STATUS_L Register GMACL_MAC_INTERRUPT_STATUS_L - GMACL MAC Interrupt Status low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_INTERRUPT_STATUS_L 0x160
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_INTERRUPT_STATUS_L 0x00D32160u

//! Register Reset Value
#define GMACL_MAC_INTERRUPT_STATUS_L_RST 0x00000000u

//! Field RESERVED_RGSMIIIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_RGSMIIIS_POS 0
//! Field RESERVED_RGSMIIIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_RGSMIIIS_MASK 0x1u

//! Field RESERVED_PCSLCHGIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PCSLCHGIS_POS 1
//! Field RESERVED_PCSLCHGIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PCSLCHGIS_MASK 0x2u

//! Field RESERVED_PCSANCIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PCSANCIS_POS 2
//! Field RESERVED_PCSANCIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PCSANCIS_MASK 0x4u

//! Field PHYIS - PHY Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_PHYIS_POS 3
//! Field PHYIS - PHY Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_PHYIS_MASK 0x8u

//! Field RESERVED_PMTIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PMTIS_POS 4
//! Field RESERVED_PMTIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_PMTIS_MASK 0x10u

//! Field LPIIS - LPI Interrupt Status
#define GMACL_MAC_INTERRUPT_STATUS_L_LPIIS_POS 5
//! Field LPIIS - LPI Interrupt Status
#define GMACL_MAC_INTERRUPT_STATUS_L_LPIIS_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_7_6_MASK 0xC0u

//! Field RESERVED_MMCIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCIS_POS 8
//! Field RESERVED_MMCIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCIS_MASK 0x100u

//! Field RESERVED_MMCRXIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIS_POS 9
//! Field RESERVED_MMCRXIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIS_MASK 0x200u

//! Field RESERVED_MMCTXIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCTXIS_POS 10
//! Field RESERVED_MMCTXIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCTXIS_MASK 0x400u

//! Field RESERVED_MMCRXIPIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIPIS_POS 11
//! Field RESERVED_MMCRXIPIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIPIS_MASK 0x800u

//! Field TSIS - Timestamp Interrupt Status
#define GMACL_MAC_INTERRUPT_STATUS_L_TSIS_POS 12
//! Field TSIS - Timestamp Interrupt Status
#define GMACL_MAC_INTERRUPT_STATUS_L_TSIS_MASK 0x1000u

//! Field TXSTSIS - Transmit Status Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_TXSTSIS_POS 13
//! Field TXSTSIS - Transmit Status Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_TXSTSIS_MASK 0x2000u

//! Field RXSTSIS - Receive Status Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_RXSTSIS_POS 14
//! Field RXSTSIS - Receive Status Interrupt
#define GMACL_MAC_INTERRUPT_STATUS_L_RXSTSIS_MASK 0x4000u

//! Field RESERVED_GPIIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_GPIIS_POS 15
//! Field RESERVED_GPIIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_L_RESERVED_GPIIS_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_INTERRUPT_STATUS_H Register GMACL_MAC_INTERRUPT_STATUS_H - GMACL MAC Interrupt Status high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_INTERRUPT_STATUS_H 0x164
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_INTERRUPT_STATUS_H 0x00D32164u

//! Register Reset Value
#define GMACL_MAC_INTERRUPT_STATUS_H_RST 0x00000000u

//! Field RESERVED_16 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_16_POS 0
//! Field RESERVED_16 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_16_MASK 0x1u

//! Field RESERVED_FPEIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_FPEIS_POS 1
//! Field RESERVED_FPEIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_FPEIS_MASK 0x2u

//! Field RESERVED_MDIOIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MDIOIS_POS 2
//! Field RESERVED_MDIOIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MDIOIS_MASK 0x4u

//! Field RESERVED_MFTIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MFTIS_POS 3
//! Field RESERVED_MFTIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MFTIS_MASK 0x8u

//! Field RESERVED_MFRIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MFRIS_POS 4
//! Field RESERVED_MFRIS - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_MFRIS_MASK 0x10u

//! Field RESERVED_31_21 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_31_21_POS 5
//! Field RESERVED_31_21 - Reserved.
#define GMACL_MAC_INTERRUPT_STATUS_H_RESERVED_31_21_MASK 0xFFE0u

//! @}

//! \defgroup GMACL_MAC_INTERRUPT_ENABLE_L Register GMACL_MAC_INTERRUPT_ENABLE_L - GMACL MAC Interrupt Enable low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_INTERRUPT_ENABLE_L 0x168
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_INTERRUPT_ENABLE_L 0x00D32168u

//! Register Reset Value
#define GMACL_MAC_INTERRUPT_ENABLE_L_RST 0x00000000u

//! Field RESERVED_RGSMIIIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_RGSMIIIE_POS 0
//! Field RESERVED_RGSMIIIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_RGSMIIIE_MASK 0x1u

//! Field RESERVED_PCSLCHGIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSLCHGIE_POS 1
//! Field RESERVED_PCSLCHGIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSLCHGIE_MASK 0x2u

//! Field RESERVED_PCSANCIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSANCIE_POS 2
//! Field RESERVED_PCSANCIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSANCIE_MASK 0x4u

//! Field PHYIE - PHY Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_PHYIE_POS 3
//! Field PHYIE - PHY Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_PHYIE_MASK 0x8u

//! Field RESERVED_PMTIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PMTIE_POS 4
//! Field RESERVED_PMTIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_PMTIE_MASK 0x10u

//! Field LPIIE - LPI Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_LPIIE_POS 5
//! Field LPIIE - LPI Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_LPIIE_MASK 0x20u

//! Field RESERVED_11_6 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_11_6_POS 6
//! Field RESERVED_11_6 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_11_6_MASK 0xFC0u

//! Field TSIE - Timestamp Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_TSIE_POS 12
//! Field TSIE - Timestamp Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_TSIE_MASK 0x1000u

//! Field TXSTSIE - Transmit Status Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_TXSTSIE_POS 13
//! Field TXSTSIE - Transmit Status Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_TXSTSIE_MASK 0x2000u

//! Field RXSTSIE - Receive Status Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_RXSTSIE_POS 14
//! Field RXSTSIE - Receive Status Interrupt Enable
#define GMACL_MAC_INTERRUPT_ENABLE_L_RXSTSIE_MASK 0x4000u

//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_INTERRUPT_ENABLE_H Register GMACL_MAC_INTERRUPT_ENABLE_H - GMACL MAC Interrupt Enable high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_INTERRUPT_ENABLE_H 0x16C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_INTERRUPT_ENABLE_H 0x00D3216Cu

//! Register Reset Value
#define GMACL_MAC_INTERRUPT_ENABLE_H_RST 0x00000000u

//! Field RESERVED_16 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_16_POS 0
//! Field RESERVED_16 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_16_MASK 0x1u

//! Field RESERVED_FPEIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_FPEIE_POS 1
//! Field RESERVED_FPEIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_FPEIE_MASK 0x2u

//! Field RESERVED_MDIOIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_MDIOIE_POS 2
//! Field RESERVED_MDIOIE - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_MDIOIE_MASK 0x4u

//! Field RESERVED_31_19 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_31_19_POS 3
//! Field RESERVED_31_19 - Reserved.
#define GMACL_MAC_INTERRUPT_ENABLE_H_RESERVED_31_19_MASK 0xFFF8u

//! @}

//! \defgroup GMACL_MAC_RX_TX_STATUS_L Register GMACL_MAC_RX_TX_STATUS_L - GMACL MAC Rx Tx Status low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_RX_TX_STATUS_L 0x170
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_RX_TX_STATUS_L 0x00D32170u

//! Register Reset Value
#define GMACL_MAC_RX_TX_STATUS_L_RST 0x00000000u

//! Field TJT - Transmit Jabber Timeout
#define GMACL_MAC_RX_TX_STATUS_L_TJT_POS 0
//! Field TJT - Transmit Jabber Timeout
#define GMACL_MAC_RX_TX_STATUS_L_TJT_MASK 0x1u

//! Field RESERVED_NCARR - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_NCARR_POS 1
//! Field RESERVED_NCARR - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_NCARR_MASK 0x2u

//! Field RESERVED_LCARR - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_LCARR_POS 2
//! Field RESERVED_LCARR - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_LCARR_MASK 0x4u

//! Field RESERVED_EXDEF - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_EXDEF_POS 3
//! Field RESERVED_EXDEF - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_EXDEF_MASK 0x8u

//! Field RESERVED_LCOL - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_LCOL_POS 4
//! Field RESERVED_LCOL - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_LCOL_MASK 0x10u

//! Field RESERVED_EXCOL - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_EXCOL_POS 5
//! Field RESERVED_EXCOL - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_EXCOL_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_7_6_MASK 0xC0u

//! Field RWT - Receive Watchdog Timeout
#define GMACL_MAC_RX_TX_STATUS_L_RWT_POS 8
//! Field RWT - Receive Watchdog Timeout
#define GMACL_MAC_RX_TX_STATUS_L_RWT_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACL_MAC_RX_TX_STATUS_H Register GMACL_MAC_RX_TX_STATUS_H - GMACL MAC Rx Tx Status high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_RX_TX_STATUS_H 0x174
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_RX_TX_STATUS_H 0x00D32174u

//! Register Reset Value
#define GMACL_MAC_RX_TX_STATUS_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_RX_TX_STATUS_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_LPI_CONTROL_STATUS_L Register GMACL_MAC_LPI_CONTROL_STATUS_L - GMACL MAC LPI Control Status low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_CONTROL_STATUS_L 0x1A0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_CONTROL_STATUS_L 0x00D321A0u

//! Register Reset Value
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RST 0x00000000u

//! Field TLPIEN - Transmit LPI Entry
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIEN_POS 0
//! Field TLPIEN - Transmit LPI Entry
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIEN_MASK 0x1u

//! Field TLPIEX - Transmit LPI Exit
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIEX_POS 1
//! Field TLPIEX - Transmit LPI Exit
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIEX_MASK 0x2u

//! Field RLPIEN - Receive LPI Entry
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIEN_POS 2
//! Field RLPIEN - Receive LPI Entry
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIEN_MASK 0x4u

//! Field RLPIEX - Receive LPI Exit
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIEX_POS 3
//! Field RLPIEX - Receive LPI Exit
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIEX_MASK 0x8u

//! Field RESERVED_7_4 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RESERVED_7_4_POS 4
//! Field RESERVED_7_4 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RESERVED_7_4_MASK 0xF0u

//! Field TLPIST - Transmit LPI State
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIST_POS 8
//! Field TLPIST - Transmit LPI State
#define GMACL_MAC_LPI_CONTROL_STATUS_L_TLPIST_MASK 0x100u

//! Field RLPIST - Receive LPI State
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIST_POS 9
//! Field RLPIST - Receive LPI State
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RLPIST_MASK 0x200u

//! Field RESERVED_15_10 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RESERVED_15_10_POS 10
//! Field RESERVED_15_10 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_L_RESERVED_15_10_MASK 0xFC00u

//! @}

//! \defgroup GMACL_MAC_LPI_CONTROL_STATUS_H Register GMACL_MAC_LPI_CONTROL_STATUS_H - GMACL MAC LPI Control Status high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_CONTROL_STATUS_H 0x1A4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_CONTROL_STATUS_H 0x00D321A4u

//! Register Reset Value
#define GMACL_MAC_LPI_CONTROL_STATUS_H_RST 0x00000000u

//! Field LPIEN - LPI Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPIEN_POS 0
//! Field LPIEN - LPI Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPIEN_MASK 0x1u

//! Field PLS - PHY Link Status
#define GMACL_MAC_LPI_CONTROL_STATUS_H_PLS_POS 1
//! Field PLS - PHY Link Status
#define GMACL_MAC_LPI_CONTROL_STATUS_H_PLS_MASK 0x2u

//! Field RESERVED_PLSEN - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_H_RESERVED_PLSEN_POS 2
//! Field RESERVED_PLSEN - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_H_RESERVED_PLSEN_MASK 0x4u

//! Field LPITXA - LPI Tx Automate
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPITXA_POS 3
//! Field LPITXA - LPI Tx Automate
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPITXA_MASK 0x8u

//! Field LPIATE - LPI Timer Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPIATE_POS 4
//! Field LPIATE - LPI Timer Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPIATE_MASK 0x10u

//! Field LPITCSE - LPI Tx Clock Stop Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPITCSE_POS 5
//! Field LPITCSE - LPI Tx Clock Stop Enable
#define GMACL_MAC_LPI_CONTROL_STATUS_H_LPITCSE_MASK 0x20u

//! Field RESERVED_31_22 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_H_RESERVED_31_22_POS 6
//! Field RESERVED_31_22 - Reserved.
#define GMACL_MAC_LPI_CONTROL_STATUS_H_RESERVED_31_22_MASK 0xFFC0u

//! @}

//! \defgroup GMACL_MAC_LPI_TIMERS_CONTROL_L Register GMACL_MAC_LPI_TIMERS_CONTROL_L - GMACL MAC LPI Timers Control low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_TIMERS_CONTROL_L 0x1A8
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_TIMERS_CONTROL_L 0x00D321A8u

//! Register Reset Value
#define GMACL_MAC_LPI_TIMERS_CONTROL_L_RST 0x00000000u

//! Field TWT - LPI TW Timer
#define GMACL_MAC_LPI_TIMERS_CONTROL_L_TWT_POS 0
//! Field TWT - LPI TW Timer
#define GMACL_MAC_LPI_TIMERS_CONTROL_L_TWT_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_LPI_TIMERS_CONTROL_H Register GMACL_MAC_LPI_TIMERS_CONTROL_H - GMACL MAC LPI Timers Control high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_TIMERS_CONTROL_H 0x1AC
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_TIMERS_CONTROL_H 0x00D321ACu

//! Register Reset Value
#define GMACL_MAC_LPI_TIMERS_CONTROL_H_RST 0x000003E8u

//! Field LST - LPI LS Timer
#define GMACL_MAC_LPI_TIMERS_CONTROL_H_LST_POS 0
//! Field LST - LPI LS Timer
#define GMACL_MAC_LPI_TIMERS_CONTROL_H_LST_MASK 0x3FFu

//! Field RESERVED_31_26 - Reserved.
#define GMACL_MAC_LPI_TIMERS_CONTROL_H_RESERVED_31_26_POS 10
//! Field RESERVED_31_26 - Reserved.
#define GMACL_MAC_LPI_TIMERS_CONTROL_H_RESERVED_31_26_MASK 0xFC00u

//! @}

//! \defgroup GMACL_MAC_LPI_ENTRY_TIMER_L Register GMACL_MAC_LPI_ENTRY_TIMER_L - GMACL MAC LPI Entry Timer low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_ENTRY_TIMER_L 0x1B0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_ENTRY_TIMER_L 0x00D321B0u

//! Register Reset Value
#define GMACL_MAC_LPI_ENTRY_TIMER_L_RST 0x00000000u

//! Field RESERVED_2_0 - Reserved.
#define GMACL_MAC_LPI_ENTRY_TIMER_L_RESERVED_2_0_POS 0
//! Field RESERVED_2_0 - Reserved.
#define GMACL_MAC_LPI_ENTRY_TIMER_L_RESERVED_2_0_MASK 0x7u

//! Field LPIET - LPI Entry Timer
#define GMACL_MAC_LPI_ENTRY_TIMER_L_LPIET_POS 3
//! Field LPIET - LPI Entry Timer
#define GMACL_MAC_LPI_ENTRY_TIMER_L_LPIET_MASK 0xFFF8u

//! @}

//! \defgroup GMACL_MAC_LPI_ENTRY_TIMER_H Register GMACL_MAC_LPI_ENTRY_TIMER_H - GMACL MAC LPI Entry Timer high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_LPI_ENTRY_TIMER_H 0x1B4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_LPI_ENTRY_TIMER_H 0x00D321B4u

//! Register Reset Value
#define GMACL_MAC_LPI_ENTRY_TIMER_H_RST 0x00000000u

//! Field LPIET - LPI Entry Timer
#define GMACL_MAC_LPI_ENTRY_TIMER_H_LPIET_POS 0
//! Field LPIET - LPI Entry Timer
#define GMACL_MAC_LPI_ENTRY_TIMER_H_LPIET_MASK 0xFu

//! Field RESERVED_31_20 - Reserved.
#define GMACL_MAC_LPI_ENTRY_TIMER_H_RESERVED_31_20_POS 4
//! Field RESERVED_31_20 - Reserved.
#define GMACL_MAC_LPI_ENTRY_TIMER_H_RESERVED_31_20_MASK 0xFFF0u

//! @}

//! \defgroup GMACL_MAC_1US_TIC_COUNTER_L Register GMACL_MAC_1US_TIC_COUNTER_L - GMACL MAC 1US Tic Counter low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_1US_TIC_COUNTER_L 0x1B8
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_1US_TIC_COUNTER_L 0x00D321B8u

//! Register Reset Value
#define GMACL_MAC_1US_TIC_COUNTER_L_RST 0x00000063u

//! Field TIC_1US_CNTR - 1US TIC Counter
#define GMACL_MAC_1US_TIC_COUNTER_L_TIC_1US_CNTR_POS 0
//! Field TIC_1US_CNTR - 1US TIC Counter
#define GMACL_MAC_1US_TIC_COUNTER_L_TIC_1US_CNTR_MASK 0xFFFu

//! Field RESERVED_31_12 - Reserved.
#define GMACL_MAC_1US_TIC_COUNTER_L_RESERVED_31_12_POS 12
//! Field RESERVED_31_12 - Reserved.
#define GMACL_MAC_1US_TIC_COUNTER_L_RESERVED_31_12_MASK 0xF000u

//! @}

//! \defgroup GMACL_MAC_1US_TIC_COUNTER_H Register GMACL_MAC_1US_TIC_COUNTER_H - GMACL MAC 1US Tic Counter high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_1US_TIC_COUNTER_H 0x1BC
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_1US_TIC_COUNTER_H 0x00D321BCu

//! Register Reset Value
#define GMACL_MAC_1US_TIC_COUNTER_H_RST 0x00000000u

//! Field RESERVED_31_12 - Reserved.
#define GMACL_MAC_1US_TIC_COUNTER_H_RESERVED_31_12_POS 0
//! Field RESERVED_31_12 - Reserved.
#define GMACL_MAC_1US_TIC_COUNTER_H_RESERVED_31_12_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_VERSION_L Register GMACL_MAC_VERSION_L - GMACL MAC Version low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_VERSION_L 0x220
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_VERSION_L 0x00D32220u

//! Register Reset Value
#define GMACL_MAC_VERSION_L_RST 0x00001050u

//! Field SNPSVER - Synopsys-defined Version
#define GMACL_MAC_VERSION_L_SNPSVER_POS 0
//! Field SNPSVER - Synopsys-defined Version
#define GMACL_MAC_VERSION_L_SNPSVER_MASK 0xFFu

//! Field USERVER - User-defined Version (configured with coreConsultant)
#define GMACL_MAC_VERSION_L_USERVER_POS 8
//! Field USERVER - User-defined Version (configured with coreConsultant)
#define GMACL_MAC_VERSION_L_USERVER_MASK 0xFF00u

//! @}

//! \defgroup GMACL_MAC_VERSION_H Register GMACL_MAC_VERSION_H - GMACL MAC Version high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_VERSION_H 0x224
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_VERSION_H 0x00D32224u

//! Register Reset Value
#define GMACL_MAC_VERSION_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACL_MAC_VERSION_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACL_MAC_VERSION_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_DEBUG_L Register GMACL_MAC_DEBUG_L - GMACL MAC Debug low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_DEBUG_L 0x228
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_DEBUG_L 0x00D32228u

//! Register Reset Value
#define GMACL_MAC_DEBUG_L_RST 0x00000000u

//! Field RPESTS - MAC GMII or MII Receive Protocol Engine Status
#define GMACL_MAC_DEBUG_L_RPESTS_POS 0
//! Field RPESTS - MAC GMII or MII Receive Protocol Engine Status
#define GMACL_MAC_DEBUG_L_RPESTS_MASK 0x1u

//! Field RFCFCSTS - MAC Receive Packet Controller FIFO Status
#define GMACL_MAC_DEBUG_L_RFCFCSTS_POS 1
//! Field RFCFCSTS - MAC Receive Packet Controller FIFO Status
#define GMACL_MAC_DEBUG_L_RFCFCSTS_MASK 0x6u

//! Field RESERVED_15_3 - Reserved.
#define GMACL_MAC_DEBUG_L_RESERVED_15_3_POS 3
//! Field RESERVED_15_3 - Reserved.
#define GMACL_MAC_DEBUG_L_RESERVED_15_3_MASK 0xFFF8u

//! @}

//! \defgroup GMACL_MAC_DEBUG_H Register GMACL_MAC_DEBUG_H - GMACL MAC Debug high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_DEBUG_H 0x22C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_DEBUG_H 0x00D3222Cu

//! Register Reset Value
#define GMACL_MAC_DEBUG_H_RST 0x00000000u

//! Field TPESTS - MAC GMII or MII Transmit Protocol Engine Status
#define GMACL_MAC_DEBUG_H_TPESTS_POS 0
//! Field TPESTS - MAC GMII or MII Transmit Protocol Engine Status
#define GMACL_MAC_DEBUG_H_TPESTS_MASK 0x1u

//! Field TFCSTS - MAC Transmit Packet Controller Status
#define GMACL_MAC_DEBUG_H_TFCSTS_POS 1
//! Field TFCSTS - MAC Transmit Packet Controller Status
#define GMACL_MAC_DEBUG_H_TFCSTS_MASK 0x6u

//! Field RESERVED_31_19 - Reserved.
#define GMACL_MAC_DEBUG_H_RESERVED_31_19_POS 3
//! Field RESERVED_31_19 - Reserved.
#define GMACL_MAC_DEBUG_H_RESERVED_31_19_MASK 0xFFF8u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE0_L Register GMACL_MAC_HW_FEATURE0_L - GMACL MAC HW Feature0 low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE0_L 0x238
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE0_L 0x00D32238u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE0_L_RST 0x00003007u

//! Field MIISEL - 10 or 100 Mbps Support
#define GMACL_MAC_HW_FEATURE0_L_MIISEL_POS 0
//! Field MIISEL - 10 or 100 Mbps Support
#define GMACL_MAC_HW_FEATURE0_L_MIISEL_MASK 0x1u

//! Field GMIISEL - 1000 Mbps Support
#define GMACL_MAC_HW_FEATURE0_L_GMIISEL_POS 1
//! Field GMIISEL - 1000 Mbps Support
#define GMACL_MAC_HW_FEATURE0_L_GMIISEL_MASK 0x2u

//! Field HDSEL - Half-duplex Support
#define GMACL_MAC_HW_FEATURE0_L_HDSEL_POS 2
//! Field HDSEL - Half-duplex Support
#define GMACL_MAC_HW_FEATURE0_L_HDSEL_MASK 0x4u

//! Field PCSSEL - PCS Registers (TBI, SGMII, or RTBI PHY interface)
#define GMACL_MAC_HW_FEATURE0_L_PCSSEL_POS 3
//! Field PCSSEL - PCS Registers (TBI, SGMII, or RTBI PHY interface)
#define GMACL_MAC_HW_FEATURE0_L_PCSSEL_MASK 0x8u

//! Field VLHASH - VLAN Hash Filter Selected
#define GMACL_MAC_HW_FEATURE0_L_VLHASH_POS 4
//! Field VLHASH - VLAN Hash Filter Selected
#define GMACL_MAC_HW_FEATURE0_L_VLHASH_MASK 0x10u

//! Field SMASEL - SMA (MDIO) Interface
#define GMACL_MAC_HW_FEATURE0_L_SMASEL_POS 5
//! Field SMASEL - SMA (MDIO) Interface
#define GMACL_MAC_HW_FEATURE0_L_SMASEL_MASK 0x20u

//! Field RWKSEL - PMT Remote Wake-up Packet Enable
#define GMACL_MAC_HW_FEATURE0_L_RWKSEL_POS 6
//! Field RWKSEL - PMT Remote Wake-up Packet Enable
#define GMACL_MAC_HW_FEATURE0_L_RWKSEL_MASK 0x40u

//! Field MGKSEL - PMT Magic Packet Enable
#define GMACL_MAC_HW_FEATURE0_L_MGKSEL_POS 7
//! Field MGKSEL - PMT Magic Packet Enable
#define GMACL_MAC_HW_FEATURE0_L_MGKSEL_MASK 0x80u

//! Field MMCSEL - RMON Module Enable
#define GMACL_MAC_HW_FEATURE0_L_MMCSEL_POS 8
//! Field MMCSEL - RMON Module Enable
#define GMACL_MAC_HW_FEATURE0_L_MMCSEL_MASK 0x100u

//! Field ARPOFFSEL - ARP Offload Enabled
#define GMACL_MAC_HW_FEATURE0_L_ARPOFFSEL_POS 9
//! Field ARPOFFSEL - ARP Offload Enabled
#define GMACL_MAC_HW_FEATURE0_L_ARPOFFSEL_MASK 0x200u

//! Field RESERVED_11_10 - Reserved.
#define GMACL_MAC_HW_FEATURE0_L_RESERVED_11_10_POS 10
//! Field RESERVED_11_10 - Reserved.
#define GMACL_MAC_HW_FEATURE0_L_RESERVED_11_10_MASK 0xC00u

//! Field TSSEL - IEEE 1588-2008 Timestamp Enabled
#define GMACL_MAC_HW_FEATURE0_L_TSSEL_POS 12
//! Field TSSEL - IEEE 1588-2008 Timestamp Enabled
#define GMACL_MAC_HW_FEATURE0_L_TSSEL_MASK 0x1000u

//! Field EEESEL - Energy Efficient Ethernet Enabled
#define GMACL_MAC_HW_FEATURE0_L_EEESEL_POS 13
//! Field EEESEL - Energy Efficient Ethernet Enabled
#define GMACL_MAC_HW_FEATURE0_L_EEESEL_MASK 0x2000u

//! Field TXCOESEL - Transmit Checksum Offload Enabled
#define GMACL_MAC_HW_FEATURE0_L_TXCOESEL_POS 14
//! Field TXCOESEL - Transmit Checksum Offload Enabled
#define GMACL_MAC_HW_FEATURE0_L_TXCOESEL_MASK 0x4000u

//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_HW_FEATURE0_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_HW_FEATURE0_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE0_H Register GMACL_MAC_HW_FEATURE0_H - GMACL MAC HW Feature0 high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE0_H 0x23C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE0_H 0x00D3223Cu

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE0_H_RST 0x00000201u

//! Field RXCOESEL - Receive Checksum Offload Enabled
#define GMACL_MAC_HW_FEATURE0_H_RXCOESEL_POS 0
//! Field RXCOESEL - Receive Checksum Offload Enabled
#define GMACL_MAC_HW_FEATURE0_H_RXCOESEL_MASK 0x1u

//! Field RESERVED_17 - Reserved.
#define GMACL_MAC_HW_FEATURE0_H_RESERVED_17_POS 1
//! Field RESERVED_17 - Reserved.
#define GMACL_MAC_HW_FEATURE0_H_RESERVED_17_MASK 0x2u

//! Field ADDMACADRSEL - MAC Addresses 1-31 Selected
#define GMACL_MAC_HW_FEATURE0_H_ADDMACADRSEL_POS 2
//! Field ADDMACADRSEL - MAC Addresses 1-31 Selected
#define GMACL_MAC_HW_FEATURE0_H_ADDMACADRSEL_MASK 0x7Cu

//! Field MACADR32SEL - MAC Addresses 32-63 Selected
#define GMACL_MAC_HW_FEATURE0_H_MACADR32SEL_POS 7
//! Field MACADR32SEL - MAC Addresses 32-63 Selected
#define GMACL_MAC_HW_FEATURE0_H_MACADR32SEL_MASK 0x80u

//! Field MACADR64SEL - MAC Addresses 64-127 Selected
#define GMACL_MAC_HW_FEATURE0_H_MACADR64SEL_POS 8
//! Field MACADR64SEL - MAC Addresses 64-127 Selected
#define GMACL_MAC_HW_FEATURE0_H_MACADR64SEL_MASK 0x100u

//! Field TSSTSSEL - Timestamp System Time Source
#define GMACL_MAC_HW_FEATURE0_H_TSSTSSEL_POS 9
//! Field TSSTSSEL - Timestamp System Time Source
#define GMACL_MAC_HW_FEATURE0_H_TSSTSSEL_MASK 0x600u

//! Field SAVLANINS - Source Address or VLAN Insertion Enable
#define GMACL_MAC_HW_FEATURE0_H_SAVLANINS_POS 11
//! Field SAVLANINS - Source Address or VLAN Insertion Enable
#define GMACL_MAC_HW_FEATURE0_H_SAVLANINS_MASK 0x800u

//! Field ACTPHYSEL - Active PHY Selected
#define GMACL_MAC_HW_FEATURE0_H_ACTPHYSEL_POS 12
//! Field ACTPHYSEL - Active PHY Selected
#define GMACL_MAC_HW_FEATURE0_H_ACTPHYSEL_MASK 0x7000u

//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE0_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE0_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE1_L Register GMACL_MAC_HW_FEATURE1_L - GMACL MAC HW Feature1 low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE1_L 0x240
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE1_L 0x00D32240u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE1_L_RST 0x00000000u

//! Field RXFIFOSIZE - MTL Receive FIFO Size
#define GMACL_MAC_HW_FEATURE1_L_RXFIFOSIZE_POS 0
//! Field RXFIFOSIZE - MTL Receive FIFO Size
#define GMACL_MAC_HW_FEATURE1_L_RXFIFOSIZE_MASK 0x1Fu

//! Field SPRAM - Single Port RAM Enable
#define GMACL_MAC_HW_FEATURE1_L_SPRAM_POS 5
//! Field SPRAM - Single Port RAM Enable
#define GMACL_MAC_HW_FEATURE1_L_SPRAM_MASK 0x20u

//! Field TXFIFOSIZE - MTL Transmit FIFO Size
#define GMACL_MAC_HW_FEATURE1_L_TXFIFOSIZE_POS 6
//! Field TXFIFOSIZE - MTL Transmit FIFO Size
#define GMACL_MAC_HW_FEATURE1_L_TXFIFOSIZE_MASK 0x7C0u

//! Field OSTEN - One-Step Timestamping Enable
#define GMACL_MAC_HW_FEATURE1_L_OSTEN_POS 11
//! Field OSTEN - One-Step Timestamping Enable
#define GMACL_MAC_HW_FEATURE1_L_OSTEN_MASK 0x800u

//! Field PTOEN - PTP Offload Enable
#define GMACL_MAC_HW_FEATURE1_L_PTOEN_POS 12
//! Field PTOEN - PTP Offload Enable
#define GMACL_MAC_HW_FEATURE1_L_PTOEN_MASK 0x1000u

//! Field ADVTHWORD - IEEE 1588 High Word Register Enable
#define GMACL_MAC_HW_FEATURE1_L_ADVTHWORD_POS 13
//! Field ADVTHWORD - IEEE 1588 High Word Register Enable
#define GMACL_MAC_HW_FEATURE1_L_ADVTHWORD_MASK 0x2000u

//! Field ADDR64 - Address Width.
#define GMACL_MAC_HW_FEATURE1_L_ADDR64_POS 14
//! Field ADDR64 - Address Width.
#define GMACL_MAC_HW_FEATURE1_L_ADDR64_MASK 0xC000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE1_H Register GMACL_MAC_HW_FEATURE1_H - GMACL MAC HW Feature1 high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE1_H 0x244
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE1_H 0x00D32244u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE1_H_RST 0x00000000u

//! Field DCBEN - DCB Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_DCBEN_POS 0
//! Field DCBEN - DCB Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_DCBEN_MASK 0x1u

//! Field SPHEN - Split Header Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_SPHEN_POS 1
//! Field SPHEN - Split Header Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_SPHEN_MASK 0x2u

//! Field TSOEN - TCP Segmentation Offload Enable
#define GMACL_MAC_HW_FEATURE1_H_TSOEN_POS 2
//! Field TSOEN - TCP Segmentation Offload Enable
#define GMACL_MAC_HW_FEATURE1_H_TSOEN_MASK 0x4u

//! Field DBGMEMA - DMA Debug Registers Enable
#define GMACL_MAC_HW_FEATURE1_H_DBGMEMA_POS 3
//! Field DBGMEMA - DMA Debug Registers Enable
#define GMACL_MAC_HW_FEATURE1_H_DBGMEMA_MASK 0x8u

//! Field AVSEL - AV Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_AVSEL_POS 4
//! Field AVSEL - AV Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_AVSEL_MASK 0x10u

//! Field RAVSEL - Rx Side Only AV Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_RAVSEL_POS 5
//! Field RAVSEL - Rx Side Only AV Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_RAVSEL_MASK 0x20u

//! Field RESERVED_22 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_22_POS 6
//! Field RESERVED_22 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_22_MASK 0x40u

//! Field POUOST - One Step for PTP over UDP/IP Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_POUOST_POS 7
//! Field POUOST - One Step for PTP over UDP/IP Feature Enable
#define GMACL_MAC_HW_FEATURE1_H_POUOST_MASK 0x80u

//! Field HASHTBLSZ - Hash Table Size
#define GMACL_MAC_HW_FEATURE1_H_HASHTBLSZ_POS 8
//! Field HASHTBLSZ - Hash Table Size
#define GMACL_MAC_HW_FEATURE1_H_HASHTBLSZ_MASK 0x300u

//! Field RESERVED_26 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_26_POS 10
//! Field RESERVED_26 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_26_MASK 0x400u

//! Field L3L4FNUM - Total number of L3 or L4 Filters
#define GMACL_MAC_HW_FEATURE1_H_L3L4FNUM_POS 11
//! Field L3L4FNUM - Total number of L3 or L4 Filters
#define GMACL_MAC_HW_FEATURE1_H_L3L4FNUM_MASK 0x7800u

//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE1_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE2_L Register GMACL_MAC_HW_FEATURE2_L - GMACL MAC HW Feature2 low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE2_L 0x248
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE2_L 0x00D32248u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE2_L_RST 0x00000000u

//! Field RXQCNT - Number of MTL Receive Queues
#define GMACL_MAC_HW_FEATURE2_L_RXQCNT_POS 0
//! Field RXQCNT - Number of MTL Receive Queues
#define GMACL_MAC_HW_FEATURE2_L_RXQCNT_MASK 0xFu

//! Field RESERVED_5_4 - Reserved.
#define GMACL_MAC_HW_FEATURE2_L_RESERVED_5_4_POS 4
//! Field RESERVED_5_4 - Reserved.
#define GMACL_MAC_HW_FEATURE2_L_RESERVED_5_4_MASK 0x30u

//! Field TXQCNT - Number of MTL Transmit Queues
#define GMACL_MAC_HW_FEATURE2_L_TXQCNT_POS 6
//! Field TXQCNT - Number of MTL Transmit Queues
#define GMACL_MAC_HW_FEATURE2_L_TXQCNT_MASK 0x3C0u

//! Field RESERVED_11_10 - Reserved.
#define GMACL_MAC_HW_FEATURE2_L_RESERVED_11_10_POS 10
//! Field RESERVED_11_10 - Reserved.
#define GMACL_MAC_HW_FEATURE2_L_RESERVED_11_10_MASK 0xC00u

//! Field RXCHCNT - Number of DMA Receive Channels
#define GMACL_MAC_HW_FEATURE2_L_RXCHCNT_POS 12
//! Field RXCHCNT - Number of DMA Receive Channels
#define GMACL_MAC_HW_FEATURE2_L_RXCHCNT_MASK 0xF000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE2_H Register GMACL_MAC_HW_FEATURE2_H - GMACL MAC HW Feature2 high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE2_H 0x24C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE2_H 0x00D3224Cu

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE2_H_RST 0x00000000u

//! Field RESERVED_17_16 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_17_16_POS 0
//! Field RESERVED_17_16 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_17_16_MASK 0x3u

//! Field TXCHCNT - Number of DMA Transmit Channels
#define GMACL_MAC_HW_FEATURE2_H_TXCHCNT_POS 2
//! Field TXCHCNT - Number of DMA Transmit Channels
#define GMACL_MAC_HW_FEATURE2_H_TXCHCNT_MASK 0x3Cu

//! Field RESERVED_23_22 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_23_22_POS 6
//! Field RESERVED_23_22 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_23_22_MASK 0xC0u

//! Field PPSOUTNUM - Number of PPS Outputs
#define GMACL_MAC_HW_FEATURE2_H_PPSOUTNUM_POS 8
//! Field PPSOUTNUM - Number of PPS Outputs
#define GMACL_MAC_HW_FEATURE2_H_PPSOUTNUM_MASK 0x700u

//! Field RESERVED_27 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_27_POS 11
//! Field RESERVED_27 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_27_MASK 0x800u

//! Field AUXSNAPNUM - Number of Auxiliary Snapshot Inputs
#define GMACL_MAC_HW_FEATURE2_H_AUXSNAPNUM_POS 12
//! Field AUXSNAPNUM - Number of Auxiliary Snapshot Inputs
#define GMACL_MAC_HW_FEATURE2_H_AUXSNAPNUM_MASK 0x7000u

//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_HW_FEATURE2_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE3_L Register GMACL_MAC_HW_FEATURE3_L - GMACL MAC HW Feature3 low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE3_L 0x250
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE3_L 0x00D32250u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE3_L_RST 0x00000000u

//! Field NRVF - Number of Extended VLAN Tag Filters Enabled
#define GMACL_MAC_HW_FEATURE3_L_NRVF_POS 0
//! Field NRVF - Number of Extended VLAN Tag Filters Enabled
#define GMACL_MAC_HW_FEATURE3_L_NRVF_MASK 0x7u

//! Field RESERVED_3 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_3_POS 3
//! Field RESERVED_3 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_3_MASK 0x8u

//! Field CBTISEL - Queue/Channel based VLAN tag insertion on Tx Enable
#define GMACL_MAC_HW_FEATURE3_L_CBTISEL_POS 4
//! Field CBTISEL - Queue/Channel based VLAN tag insertion on Tx Enable
#define GMACL_MAC_HW_FEATURE3_L_CBTISEL_MASK 0x10u

//! Field DVLAN - No Content.
#define GMACL_MAC_HW_FEATURE3_L_DVLAN_POS 5
//! Field DVLAN - No Content.
#define GMACL_MAC_HW_FEATURE3_L_DVLAN_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_7_6_MASK 0xC0u

//! Field DBGSSEL - Debug Bus Support Enable
#define GMACL_MAC_HW_FEATURE3_L_DBGSSEL_POS 8
//! Field DBGSSEL - Debug Bus Support Enable
#define GMACL_MAC_HW_FEATURE3_L_DBGSSEL_MASK 0x100u

//! Field PDUPSEL - Broadcast/Multicast Packet Duplication
#define GMACL_MAC_HW_FEATURE3_L_PDUPSEL_POS 9
//! Field PDUPSEL - Broadcast/Multicast Packet Duplication
#define GMACL_MAC_HW_FEATURE3_L_PDUPSEL_MASK 0x200u

//! Field RESERVED_15_10 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_15_10_POS 10
//! Field RESERVED_15_10 - Reserved.
#define GMACL_MAC_HW_FEATURE3_L_RESERVED_15_10_MASK 0xFC00u

//! @}

//! \defgroup GMACL_MAC_HW_FEATURE3_H Register GMACL_MAC_HW_FEATURE3_H - GMACL MAC HW Feature3 high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_HW_FEATURE3_H 0x254
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_HW_FEATURE3_H 0x00D32254u

//! Register Reset Value
#define GMACL_MAC_HW_FEATURE3_H_RST 0x00000032u

//! Field ESTSEL - Enhancements to Scheduling Traffic Enable
#define GMACL_MAC_HW_FEATURE3_H_ESTSEL_POS 0
//! Field ESTSEL - Enhancements to Scheduling Traffic Enable
#define GMACL_MAC_HW_FEATURE3_H_ESTSEL_MASK 0x1u

//! Field ESTDEP - Depth of the Gate Control List
#define GMACL_MAC_HW_FEATURE3_H_ESTDEP_POS 1
//! Field ESTDEP - Depth of the Gate Control List
#define GMACL_MAC_HW_FEATURE3_H_ESTDEP_MASK 0xEu

//! Field ESTWID - Width of the Time Interval field in the Gate Control List
#define GMACL_MAC_HW_FEATURE3_H_ESTWID_POS 4
//! Field ESTWID - Width of the Time Interval field in the Gate Control List
#define GMACL_MAC_HW_FEATURE3_H_ESTWID_MASK 0x30u

//! Field RESERVED_22 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_22_POS 6
//! Field RESERVED_22 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_22_MASK 0x40u

//! Field ESTTISW - Width of the Left Shift Amount for Time Interval
#define GMACL_MAC_HW_FEATURE3_H_ESTTISW_POS 7
//! Field ESTTISW - Width of the Left Shift Amount for Time Interval
#define GMACL_MAC_HW_FEATURE3_H_ESTTISW_MASK 0x180u

//! Field RESERVED_25 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_25_POS 9
//! Field RESERVED_25 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_25_MASK 0x200u

//! Field FPESEL - Frame Preemption Enable
#define GMACL_MAC_HW_FEATURE3_H_FPESEL_POS 10
//! Field FPESEL - Frame Preemption Enable
#define GMACL_MAC_HW_FEATURE3_H_FPESEL_MASK 0x400u

//! Field TBSSEL - Time Based Scheduling Enable
#define GMACL_MAC_HW_FEATURE3_H_TBSSEL_POS 11
//! Field TBSSEL - Time Based Scheduling Enable
#define GMACL_MAC_HW_FEATURE3_H_TBSSEL_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACL_MAC_HW_FEATURE3_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACL_MAC_CSR_SW_CTRL_L Register GMACL_MAC_CSR_SW_CTRL_L - GMACL MAC CSR SW Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_CSR_SW_CTRL_L 0x460
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_CSR_SW_CTRL_L 0x00D32460u

//! Register Reset Value
#define GMACL_MAC_CSR_SW_CTRL_L_RST 0x00000000u

//! Field RCWE - Register Clear on Write 1 Enable
#define GMACL_MAC_CSR_SW_CTRL_L_RCWE_POS 0
//! Field RCWE - Register Clear on Write 1 Enable
#define GMACL_MAC_CSR_SW_CTRL_L_RCWE_MASK 0x1u

//! Field RESERVED_7_1 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_7_1_POS 1
//! Field RESERVED_7_1 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_7_1_MASK 0xFEu

//! Field RESERVED_SEEN - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_SEEN_POS 8
//! Field RESERVED_SEEN - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_SEEN_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACL_MAC_CSR_SW_CTRL_H Register GMACL_MAC_CSR_SW_CTRL_H - GMACL MAC CSR SW Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_CSR_SW_CTRL_H 0x464
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_CSR_SW_CTRL_H 0x00D32464u

//! Register Reset Value
#define GMACL_MAC_CSR_SW_CTRL_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACL_MAC_CSR_SW_CTRL_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_ADDRESS0_HIGH_L Register GMACL_MAC_ADDRESS0_HIGH_L - GMACL MAC Address0 High low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_ADDRESS0_HIGH_L 0x600
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_ADDRESS0_HIGH_L 0x00D32600u

//! Register Reset Value
#define GMACL_MAC_ADDRESS0_HIGH_L_RST 0x0000FFFFu

//! Field ADDRHI - MAC Address0[47:32]
#define GMACL_MAC_ADDRESS0_HIGH_L_ADDRHI_POS 0
//! Field ADDRHI - MAC Address0[47:32]
#define GMACL_MAC_ADDRESS0_HIGH_L_ADDRHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_ADDRESS0_HIGH_H Register GMACL_MAC_ADDRESS0_HIGH_H - GMACL MAC Address0 High high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_ADDRESS0_HIGH_H 0x604
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_ADDRESS0_HIGH_H 0x00D32604u

//! Register Reset Value
#define GMACL_MAC_ADDRESS0_HIGH_H_RST 0x00008000u

//! Field RESERVED_DCS - Reserved.
#define GMACL_MAC_ADDRESS0_HIGH_H_RESERVED_DCS_POS 0
//! Field RESERVED_DCS - Reserved.
#define GMACL_MAC_ADDRESS0_HIGH_H_RESERVED_DCS_MASK 0x1u

//! Field RESERVED_30_Y - Reserved.
#define GMACL_MAC_ADDRESS0_HIGH_H_RESERVED_30_Y_POS 1
//! Field RESERVED_30_Y - Reserved.
#define GMACL_MAC_ADDRESS0_HIGH_H_RESERVED_30_Y_MASK 0x7FFEu

//! Field AE - Address Enable
#define GMACL_MAC_ADDRESS0_HIGH_H_AE_POS 15
//! Field AE - Address Enable
#define GMACL_MAC_ADDRESS0_HIGH_H_AE_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_ADDRESS0_LOW_L Register GMACL_MAC_ADDRESS0_LOW_L - GMACL MAC Address0 Low low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_ADDRESS0_LOW_L 0x608
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_ADDRESS0_LOW_L 0x00D32608u

//! Register Reset Value
#define GMACL_MAC_ADDRESS0_LOW_L_RST 0x00000000u

//! Field ADDRLO - MAC Address0[31:0]
#define GMACL_MAC_ADDRESS0_LOW_L_ADDRLO_POS 0
//! Field ADDRLO - MAC Address0[31:0]
#define GMACL_MAC_ADDRESS0_LOW_L_ADDRLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_ADDRESS0_LOW_H Register GMACL_MAC_ADDRESS0_LOW_H - GMACL MAC Address0 Low high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_ADDRESS0_LOW_H 0x60C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_ADDRESS0_LOW_H 0x00D3260Cu

//! Register Reset Value
#define GMACL_MAC_ADDRESS0_LOW_H_RST 0x00000000u

//! Field ADDRLO - MAC Address0[31:0]
#define GMACL_MAC_ADDRESS0_LOW_H_ADDRLO_POS 0
//! Field ADDRLO - MAC Address0[31:0]
#define GMACL_MAC_ADDRESS0_LOW_H_ADDRLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_CONTROL_L Register GMACL_MAC_TIMESTAMP_CONTROL_L - GMACL MAC Timestamp Control low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_CONTROL_L 0x1600
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_CONTROL_L 0x00D33600u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_CONTROL_L_RST 0x00002000u

//! Field TSENA - Enable Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSENA_POS 0
//! Field TSENA - Enable Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSENA_MASK 0x1u

//! Field TSCFUPDT - Fine or Coarse Timestamp Update
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSCFUPDT_POS 1
//! Field TSCFUPDT - Fine or Coarse Timestamp Update
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSCFUPDT_MASK 0x2u

//! Field TSINIT - Initialize Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSINIT_POS 2
//! Field TSINIT - Initialize Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSINIT_MASK 0x4u

//! Field TSUPDT - Update Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSUPDT_POS 3
//! Field TSUPDT - Update Timestamp
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSUPDT_MASK 0x8u

//! Field TSTRIG - Enable Timestamp Interrupt Trigger
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSTRIG_POS 4
//! Field TSTRIG - Enable Timestamp Interrupt Trigger
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSTRIG_MASK 0x10u

//! Field TSADDREG - Update Addend Register
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSADDREG_POS 5
//! Field TSADDREG - Update Addend Register
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSADDREG_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_L_RESERVED_7_6_MASK 0xC0u

//! Field TSENALL - Enable Timestamp for All Packets
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSENALL_POS 8
//! Field TSENALL - Enable Timestamp for All Packets
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSENALL_MASK 0x100u

//! Field TSCTRLSSR - Timestamp Digital or Binary Rollover Control
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSCTRLSSR_POS 9
//! Field TSCTRLSSR - Timestamp Digital or Binary Rollover Control
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSCTRLSSR_MASK 0x200u

//! Field TSVER2ENA - Enable PTP Packet Processing for Version 2 Format
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSVER2ENA_POS 10
//! Field TSVER2ENA - Enable PTP Packet Processing for Version 2 Format
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSVER2ENA_MASK 0x400u

//! Field TSIPENA - Enable Processing of PTP over Ethernet Packets
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPENA_POS 11
//! Field TSIPENA - Enable Processing of PTP over Ethernet Packets
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPENA_MASK 0x800u

//! Field TSIPV6ENA - Enable Processing of PTP Packets Sent over IPv6-UDP
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPV6ENA_POS 12
//! Field TSIPV6ENA - Enable Processing of PTP Packets Sent over IPv6-UDP
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPV6ENA_MASK 0x1000u

//! Field TSIPV4ENA - Enable Processing of PTP Packets Sent over IPv4-UDP
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPV4ENA_POS 13
//! Field TSIPV4ENA - Enable Processing of PTP Packets Sent over IPv4-UDP
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSIPV4ENA_MASK 0x2000u

//! Field TSEVNTENA - Enable Timestamp Snapshot for Event Messages
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSEVNTENA_POS 14
//! Field TSEVNTENA - Enable Timestamp Snapshot for Event Messages
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSEVNTENA_MASK 0x4000u

//! Field TSMSTRENA - Enable Snapshot for Messages Relevant to Master
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSMSTRENA_POS 15
//! Field TSMSTRENA - Enable Snapshot for Messages Relevant to Master
#define GMACL_MAC_TIMESTAMP_CONTROL_L_TSMSTRENA_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_CONTROL_H Register GMACL_MAC_TIMESTAMP_CONTROL_H - GMACL MAC Timestamp Control high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_CONTROL_H 0x1604
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_CONTROL_H 0x00D33604u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RST 0x00000000u

//! Field SNAPTYPSEL - Select PTP packets for Taking Snapshots
#define GMACL_MAC_TIMESTAMP_CONTROL_H_SNAPTYPSEL_POS 0
//! Field SNAPTYPSEL - Select PTP packets for Taking Snapshots
#define GMACL_MAC_TIMESTAMP_CONTROL_H_SNAPTYPSEL_MASK 0x3u

//! Field TSENMACADDR - Enable MAC Address for PTP Packet Filtering
#define GMACL_MAC_TIMESTAMP_CONTROL_H_TSENMACADDR_POS 2
//! Field TSENMACADDR - Enable MAC Address for PTP Packet Filtering
#define GMACL_MAC_TIMESTAMP_CONTROL_H_TSENMACADDR_MASK 0x4u

//! Field CSC - Enable checksum correction during OST for PTP over UDP/IPv4 packets
#define GMACL_MAC_TIMESTAMP_CONTROL_H_CSC_POS 3
//! Field CSC - Enable checksum correction during OST for PTP over UDP/IPv4 packets
#define GMACL_MAC_TIMESTAMP_CONTROL_H_CSC_MASK 0x8u

//! Field RESERVED_ESTI - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_ESTI_POS 4
//! Field RESERVED_ESTI - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_ESTI_MASK 0x10u

//! Field RESERVED_23_21 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_23_21_POS 5
//! Field RESERVED_23_21 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_23_21_MASK 0xE0u

//! Field TXTSSTSM - Transmit Timestamp Status Mode
#define GMACL_MAC_TIMESTAMP_CONTROL_H_TXTSSTSM_POS 8
//! Field TXTSSTSM - Transmit Timestamp Status Mode
#define GMACL_MAC_TIMESTAMP_CONTROL_H_TXTSSTSM_MASK 0x100u

//! Field RESERVED_27_25 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_27_25_POS 9
//! Field RESERVED_27_25 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_27_25_MASK 0xE00u

//! Field AV8021ASMEN - AV 802.1AS Mode Enable
#define GMACL_MAC_TIMESTAMP_CONTROL_H_AV8021ASMEN_POS 12
//! Field AV8021ASMEN - AV 802.1AS Mode Enable
#define GMACL_MAC_TIMESTAMP_CONTROL_H_AV8021ASMEN_MASK 0x1000u

//! Field RESERVED_31_29 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_31_29_POS 13
//! Field RESERVED_31_29 - Reserved.
#define GMACL_MAC_TIMESTAMP_CONTROL_H_RESERVED_31_29_MASK 0xE000u

//! @}

//! \defgroup GMACL_MAC_SUB_SECOND_INCREMENT_L Register GMACL_MAC_SUB_SECOND_INCREMENT_L - GMACL MAC Sub Second Increment low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SUB_SECOND_INCREMENT_L 0x1608
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SUB_SECOND_INCREMENT_L 0x00D33608u

//! Register Reset Value
#define GMACL_MAC_SUB_SECOND_INCREMENT_L_RST 0x00000000u

//! Field RESERVED_7_0 - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_L_RESERVED_7_0_POS 0
//! Field RESERVED_7_0 - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_L_RESERVED_7_0_MASK 0xFFu

//! Field RESERVED_SNSINC - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_L_RESERVED_SNSINC_POS 8
//! Field RESERVED_SNSINC - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_L_RESERVED_SNSINC_MASK 0xFF00u

//! @}

//! \defgroup GMACL_MAC_SUB_SECOND_INCREMENT_H Register GMACL_MAC_SUB_SECOND_INCREMENT_H - GMACL MAC Sub Second Increment high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SUB_SECOND_INCREMENT_H 0x160C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SUB_SECOND_INCREMENT_H 0x00D3360Cu

//! Register Reset Value
#define GMACL_MAC_SUB_SECOND_INCREMENT_H_RST 0x00000000u

//! Field SSINC - Sub-second Increment Value
#define GMACL_MAC_SUB_SECOND_INCREMENT_H_SSINC_POS 0
//! Field SSINC - Sub-second Increment Value
#define GMACL_MAC_SUB_SECOND_INCREMENT_H_SSINC_MASK 0xFFu

//! Field RESERVED_31_24 - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_H_RESERVED_31_24_POS 8
//! Field RESERVED_31_24 - Reserved.
#define GMACL_MAC_SUB_SECOND_INCREMENT_H_RESERVED_31_24_MASK 0xFF00u

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_SECONDS_L Register GMACL_MAC_SYSTEM_TIME_SECONDS_L - GMACL MAC System Time Seconds low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_SECONDS_L 0x1610
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_SECONDS_L 0x00D33610u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_SECONDS_L_RST 0x00000000u

//! Field TSS - Timestamp Second
#define GMACL_MAC_SYSTEM_TIME_SECONDS_L_TSS_POS 0
//! Field TSS - Timestamp Second
#define GMACL_MAC_SYSTEM_TIME_SECONDS_L_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_SECONDS_H Register GMACL_MAC_SYSTEM_TIME_SECONDS_H - GMACL MAC System Time Seconds high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_SECONDS_H 0x1614
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_SECONDS_H 0x00D33614u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_SECONDS_H_RST 0x00000000u

//! Field TSS - Timestamp Second
#define GMACL_MAC_SYSTEM_TIME_SECONDS_H_TSS_POS 0
//! Field TSS - Timestamp Second
#define GMACL_MAC_SYSTEM_TIME_SECONDS_H_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L Register GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L - GMACL MAC System Time Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L 0x1618
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L 0x00D33618u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_L_TSSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H Register GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H - GMACL MAC System Time Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H 0x161C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H 0x00D3361Cu

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H_TSSS_MASK 0x7FFFu

//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L Register GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L - GMACL MAC System Time Seconds Update low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L 0x1620
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L 0x00D33620u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_RST 0x00000000u

//! Field TSS - Timestamp Seconds
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_POS 0
//! Field TSS - Timestamp Seconds
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H Register GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H - GMACL MAC System Time Seconds Update high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H 0x1624
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H 0x00D33624u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_RST 0x00000000u

//! Field TSS - Timestamp Seconds
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_TSS_POS 0
//! Field TSS - Timestamp Seconds
#define GMACL_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L Register GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L - GMACL MAC System Time Nanoseconds Update low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L 0x1628
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L 0x00D33628u

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H Register GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H - GMACL MAC System Time Nanoseconds Update high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H 0x162C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H 0x00D3362Cu

//! Register Reset Value
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_TSSS_MASK 0x7FFFu

//! Field ADDSUB - Add or Subtract Time
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_ADDSUB_POS 15
//! Field ADDSUB - Add or Subtract Time
#define GMACL_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_ADDSUB_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_ADDEND_L Register GMACL_MAC_TIMESTAMP_ADDEND_L - GMACL MAC Timestamp Addend low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_ADDEND_L 0x1630
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_ADDEND_L 0x00D33630u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_ADDEND_L_RST 0x00000000u

//! Field TSAR - Timestamp Addend Register
#define GMACL_MAC_TIMESTAMP_ADDEND_L_TSAR_POS 0
//! Field TSAR - Timestamp Addend Register
#define GMACL_MAC_TIMESTAMP_ADDEND_L_TSAR_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_ADDEND_H Register GMACL_MAC_TIMESTAMP_ADDEND_H - GMACL MAC Timestamp Addend high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_ADDEND_H 0x1634
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_ADDEND_H 0x00D33634u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_ADDEND_H_RST 0x00000000u

//! Field TSAR - Timestamp Addend Register
#define GMACL_MAC_TIMESTAMP_ADDEND_H_TSAR_POS 0
//! Field TSAR - Timestamp Addend Register
#define GMACL_MAC_TIMESTAMP_ADDEND_H_TSAR_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_STATUS_L Register GMACL_MAC_TIMESTAMP_STATUS_L - GMACL MAC Timestamp Status low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_STATUS_L 0x1640
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_STATUS_L 0x00D33640u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_STATUS_L_RST 0x00000000u

//! Field TSSOVF - Timestamp Seconds Overflow
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSSOVF_POS 0
//! Field TSSOVF - Timestamp Seconds Overflow
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSSOVF_MASK 0x1u

//! Field TSTARGT0 - Timestamp Target Time Reached
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT0_POS 1
//! Field TSTARGT0 - Timestamp Target Time Reached
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT0_MASK 0x2u

//! Field RESERVED_AUXTSTRIG - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_AUXTSTRIG_POS 2
//! Field RESERVED_AUXTSTRIG - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_AUXTSTRIG_MASK 0x4u

//! Field TSTRGTERR0 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR0_POS 3
//! Field TSTRGTERR0 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR0_MASK 0x8u

//! Field TSTARGT1 - Timestamp Target Time Reached for Target Time PPS1
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT1_POS 4
//! Field TSTARGT1 - Timestamp Target Time Reached for Target Time PPS1
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT1_MASK 0x10u

//! Field TSTRGTERR1 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR1_POS 5
//! Field TSTRGTERR1 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR1_MASK 0x20u

//! Field TSTARGT2 - Timestamp Target Time Reached for Target Time PPS2
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT2_POS 6
//! Field TSTARGT2 - Timestamp Target Time Reached for Target Time PPS2
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT2_MASK 0x40u

//! Field TSTRGTERR2 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR2_POS 7
//! Field TSTRGTERR2 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR2_MASK 0x80u

//! Field TSTARGT3 - Timestamp Target Time Reached for Target Time PPS3
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT3_POS 8
//! Field TSTARGT3 - Timestamp Target Time Reached for Target Time PPS3
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTARGT3_MASK 0x100u

//! Field TSTRGTERR3 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR3_POS 9
//! Field TSTRGTERR3 - Timestamp Target Time Error
#define GMACL_MAC_TIMESTAMP_STATUS_L_TSTRGTERR3_MASK 0x200u

//! Field RESERVED_14_10 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_14_10_POS 10
//! Field RESERVED_14_10 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_14_10_MASK 0x7C00u

//! Field RESERVED_TXTSSIS - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_TXTSSIS_POS 15
//! Field RESERVED_TXTSSIS - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_L_RESERVED_TXTSSIS_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_STATUS_H Register GMACL_MAC_TIMESTAMP_STATUS_H - GMACL MAC Timestamp Status high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_STATUS_H 0x1644
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_STATUS_H 0x00D33644u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_STATUS_H_RST 0x00000000u

//! Field RESERVED_ATSSTN - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSSTN_POS 0
//! Field RESERVED_ATSSTN - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSSTN_MASK 0xFu

//! Field RESERVED_23_20 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_23_20_POS 4
//! Field RESERVED_23_20 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_23_20_MASK 0xF0u

//! Field RESERVED_ATSSTM - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSSTM_POS 8
//! Field RESERVED_ATSSTM - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSSTM_MASK 0x100u

//! Field RESERVED_ATSNS - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSNS_POS 9
//! Field RESERVED_ATSNS - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_ATSNS_MASK 0x3E00u

//! Field RESERVED_31_30 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_31_30_POS 14
//! Field RESERVED_31_30 - Reserved.
#define GMACL_MAC_TIMESTAMP_STATUS_H_RESERVED_31_30_MASK 0xC000u

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L Register GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L - GMACL MAC Timestamp Ingress Corr Nanosecond low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L 0x16B0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L 0x00D336B0u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_RST 0x00000000u

//! Field TSIC - Timestamp Ingress Correction
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_TSIC_POS 0
//! Field TSIC - Timestamp Ingress Correction
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_TSIC_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H Register GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H - GMACL MAC Timestamp Ingress Corr Nanosecond high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H 0x16B4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H 0x00D336B4u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_RST 0x00000000u

//! Field TSIC - Timestamp Ingress Correction
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_TSIC_POS 0
//! Field TSIC - Timestamp Ingress Correction
#define GMACL_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_TSIC_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L Register GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L - GMACL MAC Timestamp Egress Corr Nanosecond low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L 0x16B8
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L 0x00D336B8u

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_RST 0x00000000u

//! Field TSEC - Timestamp Egress Correction
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_TSEC_POS 0
//! Field TSEC - Timestamp Egress Correction
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_TSEC_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H Register GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H - GMACL MAC Timestamp Egress Corr Nanosecond high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H 0x16BC
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H 0x00D336BCu

//! Register Reset Value
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_RST 0x00000000u

//! Field TSEC - Timestamp Egress Correction
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_TSEC_POS 0
//! Field TSEC - Timestamp Egress Correction
#define GMACL_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_TSEC_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_PPS_CONTROL_L Register GMACL_MAC_PPS_CONTROL_L - GMACL MAC PPS Control low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS_CONTROL_L 0x16E0
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS_CONTROL_L 0x00D336E0u

//! Register Reset Value
#define GMACL_MAC_PPS_CONTROL_L_RST 0x00000000u

//! Field PPSCTRL_PPSCMD - PPS Output Frequency Control
#define GMACL_MAC_PPS_CONTROL_L_PPSCTRL_PPSCMD_POS 0
//! Field PPSCTRL_PPSCMD - PPS Output Frequency Control
#define GMACL_MAC_PPS_CONTROL_L_PPSCTRL_PPSCMD_MASK 0xFu

//! Field RESERVED_PPSEN0 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_PPSEN0_POS 4
//! Field RESERVED_PPSEN0 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_PPSEN0_MASK 0x10u

//! Field RESERVED_TRGTMODSEL0 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL0_POS 5
//! Field RESERVED_TRGTMODSEL0 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL0_MASK 0x60u

//! Field RESERVED_7 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_7_POS 7
//! Field RESERVED_7 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_7_MASK 0x80u

//! Field RESERVED_PPSCMD1 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_PPSCMD1_POS 8
//! Field RESERVED_PPSCMD1 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_PPSCMD1_MASK 0x700u

//! Field RESERVED_12_11 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_12_11_POS 11
//! Field RESERVED_12_11 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_12_11_MASK 0x1800u

//! Field RESERVED_TRGTMODSEL1 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL1_POS 13
//! Field RESERVED_TRGTMODSEL1 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL1_MASK 0x6000u

//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACL_MAC_PPS_CONTROL_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_PPS_CONTROL_H Register GMACL_MAC_PPS_CONTROL_H - GMACL MAC PPS Control high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS_CONTROL_H 0x16E4
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS_CONTROL_H 0x00D336E4u

//! Register Reset Value
#define GMACL_MAC_PPS_CONTROL_H_RST 0x00000000u

//! Field RESERVED_PPSCMD2 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_PPSCMD2_POS 0
//! Field RESERVED_PPSCMD2 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_PPSCMD2_MASK 0x7u

//! Field RESERVED_20_19 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_20_19_POS 3
//! Field RESERVED_20_19 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_20_19_MASK 0x18u

//! Field RESERVED_TRGTMODSEL2 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL2_POS 5
//! Field RESERVED_TRGTMODSEL2 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL2_MASK 0x60u

//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_23_MASK 0x80u

//! Field RESERVED_PPSCMD3 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_PPSCMD3_POS 8
//! Field RESERVED_PPSCMD3 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_PPSCMD3_MASK 0x700u

//! Field RESERVED_28_27 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_28_27_POS 11
//! Field RESERVED_28_27 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_28_27_MASK 0x1800u

//! Field RESERVED_TRGTMODSEL3 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL3_POS 13
//! Field RESERVED_TRGTMODSEL3 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL3_MASK 0x6000u

//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACL_MAC_PPS_CONTROL_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L Register GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L - GMACL MAC PPS0 Target Time Seconds low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L 0x1700
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L 0x00D33700u

//! Register Reset Value
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L_RST 0x00000000u

//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L_TSTRH0_POS 0
//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_L_TSTRH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H Register GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H - GMACL MAC PPS0 Target Time Seconds high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H 0x1704
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H 0x00D33704u

//! Register Reset Value
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H_RST 0x00000000u

//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H_TSTRH0_POS 0
//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACL_MAC_PPS0_TARGET_TIME_SECONDS_H_TSTRH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L Register GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L - GMACL MAC PPS0 Target Time Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L 0x1708
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L 0x00D33708u

//! Register Reset Value
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_RST 0x00000000u

//! Field TTSL0 - Target Time Low for PPS Register
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_TTSL0_POS 0
//! Field TTSL0 - Target Time Low for PPS Register
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_TTSL0_MASK 0xFFFFu

//! @}

//! \defgroup GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H Register GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H - GMACL MAC PPS0 Target Time Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H 0x170C
//! Register Offset (absolute) for 1st Instance GMACL_EQOS_MAC
#define GMACL_EQOS_MAC_GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H 0x00D3370Cu

//! Register Reset Value
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_RST 0x00000000u

//! Field TTSL0 - Target Time Low for PPS Register
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TTSL0_POS 0
//! Field TTSL0 - Target Time Low for PPS Register
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TTSL0_MASK 0x7FFFu

//! Field TRGTBUSY0 - PPS Target Time Register Busy
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TRGTBUSY0_POS 15
//! Field TRGTBUSY0 - PPS Target Time Register Busy
#define GMACL_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TRGTBUSY0_MASK 0x8000u

//! @}

//! @}

#endif
