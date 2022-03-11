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
// LSD Source          : /home/p31g/p31g_chip/v_emouchel.priv.p31g_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/GMACF_EQOS_MAC_def.xml
// Register File Name  : GMACF_EQOS_MAC
// Register File Title : GMACF EQOS MAC
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GMACF_EQOS_MAC_H
#define _GMACF_EQOS_MAC_H

//! \defgroup GMACF_EQOS_MAC Register File GMACF_EQOS_MAC - GMACF EQOS MAC
//! @{

//! Base Address of GMACF_EQOS_MAC for P31G
#define GMACF_EQOS_MAC_MODULE_BASE 0x00D30000u
//! Base Address of GMACF_EQOS_MAC for P34X
#define P34X_GMACF_EQOS_MAC_MODULE_BASE 0x00A32000u

//! \defgroup GMACF_MAC_CONFIGURATION_L Register GMACF_MAC_CONFIGURATION_L - GMACF MAC Configuration low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_CONFIGURATION_L 0x0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_CONFIGURATION_L 0x00D30000u

//! Register Reset Value
#define GMACF_MAC_CONFIGURATION_L_RST 0x00000000u

//! Field RE - Receiver Enable
#define GMACF_MAC_CONFIGURATION_L_RE_POS 0
//! Field RE - Receiver Enable
#define GMACF_MAC_CONFIGURATION_L_RE_MASK 0x1u

//! Field TE - Transmitter Enable
#define GMACF_MAC_CONFIGURATION_L_TE_POS 1
//! Field TE - Transmitter Enable
#define GMACF_MAC_CONFIGURATION_L_TE_MASK 0x2u

//! Field PRELEN - Preamble Length for Transmit packets
#define GMACF_MAC_CONFIGURATION_L_PRELEN_POS 2
//! Field PRELEN - Preamble Length for Transmit packets
#define GMACF_MAC_CONFIGURATION_L_PRELEN_MASK 0xCu

//! Field DC - Deferral Check
#define GMACF_MAC_CONFIGURATION_L_DC_POS 4
//! Field DC - Deferral Check
#define GMACF_MAC_CONFIGURATION_L_DC_MASK 0x10u

//! Field BL - Back-Off Limit
#define GMACF_MAC_CONFIGURATION_L_BL_POS 5
//! Field BL - Back-Off Limit
#define GMACF_MAC_CONFIGURATION_L_BL_MASK 0x60u

//! Field RESERVED_7 - Reserved.
#define GMACF_MAC_CONFIGURATION_L_RESERVED_7_POS 7
//! Field RESERVED_7 - Reserved.
#define GMACF_MAC_CONFIGURATION_L_RESERVED_7_MASK 0x80u

//! Field DR - Disable Retry
#define GMACF_MAC_CONFIGURATION_L_DR_POS 8
//! Field DR - Disable Retry
#define GMACF_MAC_CONFIGURATION_L_DR_MASK 0x100u

//! Field DCRS - Disable Carrier Sense During Transmission
#define GMACF_MAC_CONFIGURATION_L_DCRS_POS 9
//! Field DCRS - Disable Carrier Sense During Transmission
#define GMACF_MAC_CONFIGURATION_L_DCRS_MASK 0x200u

//! Field DO - Disable Receive Own
#define GMACF_MAC_CONFIGURATION_L_DO_POS 10
//! Field DO - Disable Receive Own
#define GMACF_MAC_CONFIGURATION_L_DO_MASK 0x400u

//! Field ECRSFD - Enable Carrier Sense Before Transmission in Full-Duplex Mode
#define GMACF_MAC_CONFIGURATION_L_ECRSFD_POS 11
//! Field ECRSFD - Enable Carrier Sense Before Transmission in Full-Duplex Mode
#define GMACF_MAC_CONFIGURATION_L_ECRSFD_MASK 0x800u

//! Field LM - Loopback Mode
#define GMACF_MAC_CONFIGURATION_L_LM_POS 12
//! Field LM - Loopback Mode
#define GMACF_MAC_CONFIGURATION_L_LM_MASK 0x1000u

//! Field DM - Duplex Mode
#define GMACF_MAC_CONFIGURATION_L_DM_POS 13
//! Field DM - Duplex Mode
#define GMACF_MAC_CONFIGURATION_L_DM_MASK 0x2000u

//! Field FES - Speed
#define GMACF_MAC_CONFIGURATION_L_FES_POS 14
//! Field FES - Speed
#define GMACF_MAC_CONFIGURATION_L_FES_MASK 0x4000u

//! Field PS - Port Select
#define GMACF_MAC_CONFIGURATION_L_PS_POS 15
//! Field PS - Port Select
#define GMACF_MAC_CONFIGURATION_L_PS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_CONFIGURATION_H Register GMACF_MAC_CONFIGURATION_H - GMACF MAC Configuration high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_CONFIGURATION_H 0x4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_CONFIGURATION_H 0x00D30004u

//! Register Reset Value
#define GMACF_MAC_CONFIGURATION_H_RST 0x00000000u

//! Field JE - Jumbo Packet Enable
#define GMACF_MAC_CONFIGURATION_H_JE_POS 0
//! Field JE - Jumbo Packet Enable
#define GMACF_MAC_CONFIGURATION_H_JE_MASK 0x1u

//! Field JD - Jabber Disable
#define GMACF_MAC_CONFIGURATION_H_JD_POS 1
//! Field JD - Jabber Disable
#define GMACF_MAC_CONFIGURATION_H_JD_MASK 0x2u

//! Field BE - Packet Burst Enable
#define GMACF_MAC_CONFIGURATION_H_BE_POS 2
//! Field BE - Packet Burst Enable
#define GMACF_MAC_CONFIGURATION_H_BE_MASK 0x4u

//! Field WD - Watchdog Disable
#define GMACF_MAC_CONFIGURATION_H_WD_POS 3
//! Field WD - Watchdog Disable
#define GMACF_MAC_CONFIGURATION_H_WD_MASK 0x8u

//! Field ACS - Automatic Pad or CRC Stripping
#define GMACF_MAC_CONFIGURATION_H_ACS_POS 4
//! Field ACS - Automatic Pad or CRC Stripping
#define GMACF_MAC_CONFIGURATION_H_ACS_MASK 0x10u

//! Field CST - CRC stripping for Type packets
#define GMACF_MAC_CONFIGURATION_H_CST_POS 5
//! Field CST - CRC stripping for Type packets
#define GMACF_MAC_CONFIGURATION_H_CST_MASK 0x20u

//! Field S2KP - IEEE 802.3as Support for 2K Packets
#define GMACF_MAC_CONFIGURATION_H_S2KP_POS 6
//! Field S2KP - IEEE 802.3as Support for 2K Packets
#define GMACF_MAC_CONFIGURATION_H_S2KP_MASK 0x40u

//! Field GPSLCE - Giant Packet Size Limit Control Enable
#define GMACF_MAC_CONFIGURATION_H_GPSLCE_POS 7
//! Field GPSLCE - Giant Packet Size Limit Control Enable
#define GMACF_MAC_CONFIGURATION_H_GPSLCE_MASK 0x80u

//! Field IPG - Inter-Packet Gap
#define GMACF_MAC_CONFIGURATION_H_IPG_POS 8
//! Field IPG - Inter-Packet Gap
#define GMACF_MAC_CONFIGURATION_H_IPG_MASK 0x700u

//! Field IPC - Checksum Offload
#define GMACF_MAC_CONFIGURATION_H_IPC_POS 11
//! Field IPC - Checksum Offload
#define GMACF_MAC_CONFIGURATION_H_IPC_MASK 0x800u

//! Field RESERVED_SARC - Reserved.
#define GMACF_MAC_CONFIGURATION_H_RESERVED_SARC_POS 12
//! Field RESERVED_SARC - Reserved.
#define GMACF_MAC_CONFIGURATION_H_RESERVED_SARC_MASK 0x7000u

//! Field RESERVED_ARPEN - Reserved.
#define GMACF_MAC_CONFIGURATION_H_RESERVED_ARPEN_POS 15
//! Field RESERVED_ARPEN - Reserved.
#define GMACF_MAC_CONFIGURATION_H_RESERVED_ARPEN_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_EXT_CONFIGURATION_L Register GMACF_MAC_EXT_CONFIGURATION_L - GMACF MAC Ext Configuration low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_EXT_CONFIGURATION_L 0x8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_EXT_CONFIGURATION_L 0x00D30008u

//! Register Reset Value
#define GMACF_MAC_EXT_CONFIGURATION_L_RST 0x00000000u

//! Field GPSL - Giant Packet Size Limit
#define GMACF_MAC_EXT_CONFIGURATION_L_GPSL_POS 0
//! Field GPSL - Giant Packet Size Limit
#define GMACF_MAC_EXT_CONFIGURATION_L_GPSL_MASK 0x3FFFu

//! Field RESERVED_15_14 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_L_RESERVED_15_14_POS 14
//! Field RESERVED_15_14 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_L_RESERVED_15_14_MASK 0xC000u

//! @}

//! \defgroup GMACF_MAC_EXT_CONFIGURATION_H Register GMACF_MAC_EXT_CONFIGURATION_H - GMACF MAC Ext Configuration high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_EXT_CONFIGURATION_H 0xC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_EXT_CONFIGURATION_H 0x00D3000Cu

//! Register Reset Value
#define GMACF_MAC_EXT_CONFIGURATION_H_RST 0x00000000u

//! Field DCRCC - Disable CRC Checking for Received Packets
#define GMACF_MAC_EXT_CONFIGURATION_H_DCRCC_POS 0
//! Field DCRCC - Disable CRC Checking for Received Packets
#define GMACF_MAC_EXT_CONFIGURATION_H_DCRCC_MASK 0x1u

//! Field SPEN - Slow Protocol Detection Enable
#define GMACF_MAC_EXT_CONFIGURATION_H_SPEN_POS 1
//! Field SPEN - Slow Protocol Detection Enable
#define GMACF_MAC_EXT_CONFIGURATION_H_SPEN_MASK 0x2u

//! Field USP - Unicast Slow Protocol Packet Detect
#define GMACF_MAC_EXT_CONFIGURATION_H_USP_POS 2
//! Field USP - Unicast Slow Protocol Packet Detect
#define GMACF_MAC_EXT_CONFIGURATION_H_USP_MASK 0x4u

//! Field RESERVED_PDC - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_PDC_POS 3
//! Field RESERVED_PDC - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_PDC_MASK 0x8u

//! Field RESERVED_HDSMS - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_HDSMS_POS 4
//! Field RESERVED_HDSMS - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_HDSMS_MASK 0x70u

//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_23_MASK 0x80u

//! Field EIPGEN - Extended Inter-Packet Gap Enable
#define GMACF_MAC_EXT_CONFIGURATION_H_EIPGEN_POS 8
//! Field EIPGEN - Extended Inter-Packet Gap Enable
#define GMACF_MAC_EXT_CONFIGURATION_H_EIPGEN_MASK 0x100u

//! Field EIPG - Extended Inter-Packet Gap
#define GMACF_MAC_EXT_CONFIGURATION_H_EIPG_POS 9
//! Field EIPG - Extended Inter-Packet Gap
#define GMACF_MAC_EXT_CONFIGURATION_H_EIPG_MASK 0x3E00u

//! Field RESERVED_31_30 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_31_30_POS 14
//! Field RESERVED_31_30 - Reserved.
#define GMACF_MAC_EXT_CONFIGURATION_H_RESERVED_31_30_MASK 0xC000u

//! @}

//! \defgroup GMACF_MAC_PACKET_FILTER_L Register GMACF_MAC_PACKET_FILTER_L - GMACF MAC Packet Filter low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PACKET_FILTER_L 0x10
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PACKET_FILTER_L 0x00D30010u

//! Register Reset Value
#define GMACF_MAC_PACKET_FILTER_L_RST 0x00000000u

//! Field PR - Promiscuous Mode
#define GMACF_MAC_PACKET_FILTER_L_PR_POS 0
//! Field PR - Promiscuous Mode
#define GMACF_MAC_PACKET_FILTER_L_PR_MASK 0x1u

//! Field RESERVED_HUC - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HUC_POS 1
//! Field RESERVED_HUC - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HUC_MASK 0x2u

//! Field RESERVED_HMC - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HMC_POS 2
//! Field RESERVED_HMC - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HMC_MASK 0x4u

//! Field DAIF - DA Inverse Filtering
#define GMACF_MAC_PACKET_FILTER_L_DAIF_POS 3
//! Field DAIF - DA Inverse Filtering
#define GMACF_MAC_PACKET_FILTER_L_DAIF_MASK 0x8u

//! Field PM - Pass All Multicast
#define GMACF_MAC_PACKET_FILTER_L_PM_POS 4
//! Field PM - Pass All Multicast
#define GMACF_MAC_PACKET_FILTER_L_PM_MASK 0x10u

//! Field DBF - Disable Broadcast Packets
#define GMACF_MAC_PACKET_FILTER_L_DBF_POS 5
//! Field DBF - Disable Broadcast Packets
#define GMACF_MAC_PACKET_FILTER_L_DBF_MASK 0x20u

//! Field PCF - Pass Control Packets
#define GMACF_MAC_PACKET_FILTER_L_PCF_POS 6
//! Field PCF - Pass Control Packets
#define GMACF_MAC_PACKET_FILTER_L_PCF_MASK 0xC0u

//! Field SAIF - SA Inverse Filtering
#define GMACF_MAC_PACKET_FILTER_L_SAIF_POS 8
//! Field SAIF - SA Inverse Filtering
#define GMACF_MAC_PACKET_FILTER_L_SAIF_MASK 0x100u

//! Field SAF - Source Address Filter Enable
#define GMACF_MAC_PACKET_FILTER_L_SAF_POS 9
//! Field SAF - Source Address Filter Enable
#define GMACF_MAC_PACKET_FILTER_L_SAF_MASK 0x200u

//! Field RESERVED_HPF - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HPF_POS 10
//! Field RESERVED_HPF - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_HPF_MASK 0x400u

//! Field RESERVED_15_11 - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_15_11_POS 11
//! Field RESERVED_15_11 - Reserved.
#define GMACF_MAC_PACKET_FILTER_L_RESERVED_15_11_MASK 0xF800u

//! @}

//! \defgroup GMACF_MAC_PACKET_FILTER_H Register GMACF_MAC_PACKET_FILTER_H - GMACF MAC Packet Filter high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PACKET_FILTER_H 0x14
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PACKET_FILTER_H 0x00D30014u

//! Register Reset Value
#define GMACF_MAC_PACKET_FILTER_H_RST 0x00000000u

//! Field VTFE - VLAN Tag Filter Enable
#define GMACF_MAC_PACKET_FILTER_H_VTFE_POS 0
//! Field VTFE - VLAN Tag Filter Enable
#define GMACF_MAC_PACKET_FILTER_H_VTFE_MASK 0x1u

//! Field RESERVED_19_17 - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_19_17_POS 1
//! Field RESERVED_19_17 - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_19_17_MASK 0xEu

//! Field RESERVED_IPFE - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_IPFE_POS 4
//! Field RESERVED_IPFE - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_IPFE_MASK 0x10u

//! Field RESERVED_DNTU - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_DNTU_POS 5
//! Field RESERVED_DNTU - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_DNTU_MASK 0x20u

//! Field RESERVED_30_22 - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_30_22_POS 6
//! Field RESERVED_30_22 - Reserved.
#define GMACF_MAC_PACKET_FILTER_H_RESERVED_30_22_MASK 0x7FC0u

//! Field RA - Receive All
#define GMACF_MAC_PACKET_FILTER_H_RA_POS 15
//! Field RA - Receive All
#define GMACF_MAC_PACKET_FILTER_H_RA_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_WATCHDOG_TIMEOUT_L Register GMACF_MAC_WATCHDOG_TIMEOUT_L - GMACF MAC Watchdog Timeout low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_WATCHDOG_TIMEOUT_L 0x18
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_WATCHDOG_TIMEOUT_L 0x00D30018u

//! Register Reset Value
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_RST 0x00000000u

//! Field WTO - Watchdog Timeout
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_WTO_POS 0
//! Field WTO - Watchdog Timeout
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_WTO_MASK 0xFu

//! Field RESERVED_7_4 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_RESERVED_7_4_POS 4
//! Field RESERVED_7_4 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_RESERVED_7_4_MASK 0xF0u

//! Field PWE - Programmable Watchdog Enable
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_PWE_POS 8
//! Field PWE - Programmable Watchdog Enable
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_PWE_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACF_MAC_WATCHDOG_TIMEOUT_H Register GMACF_MAC_WATCHDOG_TIMEOUT_H - GMACF MAC Watchdog Timeout high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_WATCHDOG_TIMEOUT_H 0x1C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_WATCHDOG_TIMEOUT_H 0x00D3001Cu

//! Register Reset Value
#define GMACF_MAC_WATCHDOG_TIMEOUT_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_WATCHDOG_TIMEOUT_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_VLAN_TAG_L Register GMACF_MAC_VLAN_TAG_L - GMACF MAC VLAN Tag low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_VLAN_TAG_L 0xA0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_VLAN_TAG_L 0x00D300A0u

//! Register Reset Value
#define GMACF_MAC_VLAN_TAG_L_RST 0x00000000u

//! Field VL - VLAN Tag Identifier for Receive Packets
#define GMACF_MAC_VLAN_TAG_L_VL_POS 0
//! Field VL - VLAN Tag Identifier for Receive Packets
#define GMACF_MAC_VLAN_TAG_L_VL_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_VLAN_TAG_H Register GMACF_MAC_VLAN_TAG_H - GMACF MAC VLAN Tag high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_VLAN_TAG_H 0xA4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_VLAN_TAG_H 0x00D300A4u

//! Register Reset Value
#define GMACF_MAC_VLAN_TAG_H_RST 0x00000000u

//! Field ETV - Enable 12-Bit VLAN Tag Comparison
#define GMACF_MAC_VLAN_TAG_H_ETV_POS 0
//! Field ETV - Enable 12-Bit VLAN Tag Comparison
#define GMACF_MAC_VLAN_TAG_H_ETV_MASK 0x1u

//! Field VTIM - VLAN Tag Inverse Match Enable
#define GMACF_MAC_VLAN_TAG_H_VTIM_POS 1
//! Field VTIM - VLAN Tag Inverse Match Enable
#define GMACF_MAC_VLAN_TAG_H_VTIM_MASK 0x2u

//! Field ESVL - Enable S-VLAN
#define GMACF_MAC_VLAN_TAG_H_ESVL_POS 2
//! Field ESVL - Enable S-VLAN
#define GMACF_MAC_VLAN_TAG_H_ESVL_MASK 0x4u

//! Field ERSVLM - Enable Receive S-VLAN Match
#define GMACF_MAC_VLAN_TAG_H_ERSVLM_POS 3
//! Field ERSVLM - Enable Receive S-VLAN Match
#define GMACF_MAC_VLAN_TAG_H_ERSVLM_MASK 0x8u

//! Field DOVLTC - Disable VLAN Type Check
#define GMACF_MAC_VLAN_TAG_H_DOVLTC_POS 4
//! Field DOVLTC - Disable VLAN Type Check
#define GMACF_MAC_VLAN_TAG_H_DOVLTC_MASK 0x10u

//! Field EVLS - Enable VLAN Tag Stripping on Receive
#define GMACF_MAC_VLAN_TAG_H_EVLS_POS 5
//! Field EVLS - Enable VLAN Tag Stripping on Receive
#define GMACF_MAC_VLAN_TAG_H_EVLS_MASK 0x60u

//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_23_MASK 0x80u

//! Field EVLRXS - Enable VLAN Tag in Rx status
#define GMACF_MAC_VLAN_TAG_H_EVLRXS_POS 8
//! Field EVLRXS - Enable VLAN Tag in Rx status
#define GMACF_MAC_VLAN_TAG_H_EVLRXS_MASK 0x100u

//! Field RESERVED_VTHM - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_VTHM_POS 9
//! Field RESERVED_VTHM - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_VTHM_MASK 0x200u

//! Field EDVLP - Enable Double VLAN Processing
#define GMACF_MAC_VLAN_TAG_H_EDVLP_POS 10
//! Field EDVLP - Enable Double VLAN Processing
#define GMACF_MAC_VLAN_TAG_H_EDVLP_MASK 0x400u

//! Field ERIVLT - Enable Inner VLAN Tag
#define GMACF_MAC_VLAN_TAG_H_ERIVLT_POS 11
//! Field ERIVLT - Enable Inner VLAN Tag
#define GMACF_MAC_VLAN_TAG_H_ERIVLT_MASK 0x800u

//! Field EIVLS - Enable Inner VLAN Tag Stripping on Receive
#define GMACF_MAC_VLAN_TAG_H_EIVLS_POS 12
//! Field EIVLS - Enable Inner VLAN Tag Stripping on Receive
#define GMACF_MAC_VLAN_TAG_H_EIVLS_MASK 0x3000u

//! Field RESERVED_30 - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_30_POS 14
//! Field RESERVED_30 - Reserved.
#define GMACF_MAC_VLAN_TAG_H_RESERVED_30_MASK 0x4000u

//! Field EIVLRXS - Enable Inner VLAN Tag in Rx Status
#define GMACF_MAC_VLAN_TAG_H_EIVLRXS_POS 15
//! Field EIVLRXS - Enable Inner VLAN Tag in Rx Status
#define GMACF_MAC_VLAN_TAG_H_EIVLRXS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_Q0_TX_FLOW_CTRL_L Register GMACF_MAC_Q0_TX_FLOW_CTRL_L - GMACF MAC Q0 Tx Flow Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L 0xE0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_Q0_TX_FLOW_CTRL_L 0x00D300E0u

//! Register Reset Value
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_RST 0x00000000u

//! Field FCB_BPA - Flow Control Busy or Backpressure Activate
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA_POS 0
//! Field FCB_BPA - Flow Control Busy or Backpressure Activate
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_FCB_BPA_MASK 0x1u

//! Field TFE - Transmit Flow Control Enable
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_TFE_POS 1
//! Field TFE - Transmit Flow Control Enable
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_TFE_MASK 0x2u

//! Field RESERVED_3_2 - Reserved.
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_3_2_POS 2
//! Field RESERVED_3_2 - Reserved.
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_3_2_MASK 0xCu

//! Field PLT - Pause Low Threshold
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_PLT_POS 4
//! Field PLT - Pause Low Threshold
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_PLT_MASK 0x70u

//! Field DZPQ - Disable Zero-Quanta Pause
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_DZPQ_POS 7
//! Field DZPQ - Disable Zero-Quanta Pause
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_DZPQ_MASK 0x80u

//! Field RESERVED_15_8 - Reserved.
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_15_8_POS 8
//! Field RESERVED_15_8 - Reserved.
#define GMACF_MAC_Q0_TX_FLOW_CTRL_L_RESERVED_15_8_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_Q0_TX_FLOW_CTRL_H Register GMACF_MAC_Q0_TX_FLOW_CTRL_H - GMACF MAC Q0 Tx Flow Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_Q0_TX_FLOW_CTRL_H 0xE4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_Q0_TX_FLOW_CTRL_H 0x00D300E4u

//! Register Reset Value
#define GMACF_MAC_Q0_TX_FLOW_CTRL_H_RST 0x00000000u

//! Field PT - Pause Time
#define GMACF_MAC_Q0_TX_FLOW_CTRL_H_PT_POS 0
//! Field PT - Pause Time
#define GMACF_MAC_Q0_TX_FLOW_CTRL_H_PT_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_RX_FLOW_CTRL_L Register GMACF_MAC_RX_FLOW_CTRL_L - GMACF MAC Rx Flow Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_RX_FLOW_CTRL_L 0x120
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_RX_FLOW_CTRL_L 0x00D30120u

//! Register Reset Value
#define GMACF_MAC_RX_FLOW_CTRL_L_RST 0x00000000u

//! Field RFE - Receive Flow Control Enable
#define GMACF_MAC_RX_FLOW_CTRL_L_RFE_POS 0
//! Field RFE - Receive Flow Control Enable
#define GMACF_MAC_RX_FLOW_CTRL_L_RFE_MASK 0x1u

//! Field UP - Unicast Pause Packet Detect
#define GMACF_MAC_RX_FLOW_CTRL_L_UP_POS 1
//! Field UP - Unicast Pause Packet Detect
#define GMACF_MAC_RX_FLOW_CTRL_L_UP_MASK 0x2u

//! Field RESERVED_7_2 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_7_2_POS 2
//! Field RESERVED_7_2 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_7_2_MASK 0xFCu

//! Field RESERVED_PFCE - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_PFCE_POS 8
//! Field RESERVED_PFCE - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_PFCE_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACF_MAC_RX_FLOW_CTRL_H Register GMACF_MAC_RX_FLOW_CTRL_H - GMACF MAC Rx Flow Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_RX_FLOW_CTRL_H 0x124
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_RX_FLOW_CTRL_H 0x00D30124u

//! Register Reset Value
#define GMACF_MAC_RX_FLOW_CTRL_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_FLOW_CTRL_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_INTERRUPT_STATUS_L Register GMACF_MAC_INTERRUPT_STATUS_L - GMACF MAC Interrupt Status low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_INTERRUPT_STATUS_L 0x160
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_INTERRUPT_STATUS_L 0x00D30160u

//! Register Reset Value
#define GMACF_MAC_INTERRUPT_STATUS_L_RST 0x00000000u

//! Field RESERVED_RGSMIIIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_RGSMIIIS_POS 0
//! Field RESERVED_RGSMIIIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_RGSMIIIS_MASK 0x1u

//! Field RESERVED_PCSLCHGIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PCSLCHGIS_POS 1
//! Field RESERVED_PCSLCHGIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PCSLCHGIS_MASK 0x2u

//! Field RESERVED_PCSANCIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PCSANCIS_POS 2
//! Field RESERVED_PCSANCIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PCSANCIS_MASK 0x4u

//! Field PHYIS - PHY Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_PHYIS_POS 3
//! Field PHYIS - PHY Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_PHYIS_MASK 0x8u

//! Field RESERVED_PMTIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PMTIS_POS 4
//! Field RESERVED_PMTIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_PMTIS_MASK 0x10u

//! Field LPIIS - LPI Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_LPIIS_POS 5
//! Field LPIIS - LPI Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_LPIIS_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_7_6_MASK 0xC0u

//! Field MMCIS - MMC Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCIS_POS 8
//! Field MMCIS - MMC Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCIS_MASK 0x100u

//! Field MMCRXIS - MMC Receive Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCRXIS_POS 9
//! Field MMCRXIS - MMC Receive Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCRXIS_MASK 0x200u

//! Field MMCTXIS - MMC Transmit Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCTXIS_POS 10
//! Field MMCTXIS - MMC Transmit Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_MMCTXIS_MASK 0x400u

//! Field RESERVED_MMCRXIPIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIPIS_POS 11
//! Field RESERVED_MMCRXIPIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_MMCRXIPIS_MASK 0x800u

//! Field TSIS - Timestamp Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_TSIS_POS 12
//! Field TSIS - Timestamp Interrupt Status
#define GMACF_MAC_INTERRUPT_STATUS_L_TSIS_MASK 0x1000u

//! Field TXSTSIS - Transmit Status Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_TXSTSIS_POS 13
//! Field TXSTSIS - Transmit Status Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_TXSTSIS_MASK 0x2000u

//! Field RXSTSIS - Receive Status Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_RXSTSIS_POS 14
//! Field RXSTSIS - Receive Status Interrupt
#define GMACF_MAC_INTERRUPT_STATUS_L_RXSTSIS_MASK 0x4000u

//! Field RESERVED_GPIIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_GPIIS_POS 15
//! Field RESERVED_GPIIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_L_RESERVED_GPIIS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_INTERRUPT_STATUS_H Register GMACF_MAC_INTERRUPT_STATUS_H - GMACF MAC Interrupt Status high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_INTERRUPT_STATUS_H 0x164
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_INTERRUPT_STATUS_H 0x00D30164u

//! Register Reset Value
#define GMACF_MAC_INTERRUPT_STATUS_H_RST 0x00000000u

//! Field RESERVED_16 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_16_POS 0
//! Field RESERVED_16 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_16_MASK 0x1u

//! Field RESERVED_FPEIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_FPEIS_POS 1
//! Field RESERVED_FPEIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_FPEIS_MASK 0x2u

//! Field RESERVED_MDIOIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MDIOIS_POS 2
//! Field RESERVED_MDIOIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MDIOIS_MASK 0x4u

//! Field RESERVED_MFTIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MFTIS_POS 3
//! Field RESERVED_MFTIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MFTIS_MASK 0x8u

//! Field RESERVED_MFRIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MFRIS_POS 4
//! Field RESERVED_MFRIS - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_MFRIS_MASK 0x10u

//! Field RESERVED_31_21 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_31_21_POS 5
//! Field RESERVED_31_21 - Reserved.
#define GMACF_MAC_INTERRUPT_STATUS_H_RESERVED_31_21_MASK 0xFFE0u

//! @}

//! \defgroup GMACF_MAC_INTERRUPT_ENABLE_L Register GMACF_MAC_INTERRUPT_ENABLE_L - GMACF MAC Interrupt Enable low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_INTERRUPT_ENABLE_L 0x168
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_INTERRUPT_ENABLE_L 0x00D30168u

//! Register Reset Value
#define GMACF_MAC_INTERRUPT_ENABLE_L_RST 0x00000000u

//! Field RESERVED_RGSMIIIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_RGSMIIIE_POS 0
//! Field RESERVED_RGSMIIIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_RGSMIIIE_MASK 0x1u

//! Field RESERVED_PCSLCHGIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSLCHGIE_POS 1
//! Field RESERVED_PCSLCHGIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSLCHGIE_MASK 0x2u

//! Field RESERVED_PCSANCIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSANCIE_POS 2
//! Field RESERVED_PCSANCIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PCSANCIE_MASK 0x4u

//! Field PHYIE - PHY Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_PHYIE_POS 3
//! Field PHYIE - PHY Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_PHYIE_MASK 0x8u

//! Field RESERVED_PMTIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PMTIE_POS 4
//! Field RESERVED_PMTIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_PMTIE_MASK 0x10u

//! Field LPIIE - LPI Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_LPIIE_POS 5
//! Field LPIIE - LPI Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_LPIIE_MASK 0x20u

//! Field RESERVED_11_6 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_11_6_POS 6
//! Field RESERVED_11_6 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_11_6_MASK 0xFC0u

//! Field TSIE - Timestamp Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_TSIE_POS 12
//! Field TSIE - Timestamp Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_TSIE_MASK 0x1000u

//! Field TXSTSIE - Transmit Status Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_TXSTSIE_POS 13
//! Field TXSTSIE - Transmit Status Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_TXSTSIE_MASK 0x2000u

//! Field RXSTSIE - Receive Status Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_RXSTSIE_POS 14
//! Field RXSTSIE - Receive Status Interrupt Enable
#define GMACF_MAC_INTERRUPT_ENABLE_L_RXSTSIE_MASK 0x4000u

//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_INTERRUPT_ENABLE_H Register GMACF_MAC_INTERRUPT_ENABLE_H - GMACF MAC Interrupt Enable high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_INTERRUPT_ENABLE_H 0x16C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_INTERRUPT_ENABLE_H 0x00D3016Cu

//! Register Reset Value
#define GMACF_MAC_INTERRUPT_ENABLE_H_RST 0x00000000u

//! Field RESERVED_16 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_16_POS 0
//! Field RESERVED_16 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_16_MASK 0x1u

//! Field RESERVED_FPEIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_FPEIE_POS 1
//! Field RESERVED_FPEIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_FPEIE_MASK 0x2u

//! Field RESERVED_MDIOIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_MDIOIE_POS 2
//! Field RESERVED_MDIOIE - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_MDIOIE_MASK 0x4u

//! Field RESERVED_31_19 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_31_19_POS 3
//! Field RESERVED_31_19 - Reserved.
#define GMACF_MAC_INTERRUPT_ENABLE_H_RESERVED_31_19_MASK 0xFFF8u

//! @}

//! \defgroup GMACF_MAC_RX_TX_STATUS_L Register GMACF_MAC_RX_TX_STATUS_L - GMACF MAC Rx Tx Status low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_RX_TX_STATUS_L 0x170
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_RX_TX_STATUS_L 0x00D30170u

//! Register Reset Value
#define GMACF_MAC_RX_TX_STATUS_L_RST 0x00000000u

//! Field TJT - Transmit Jabber Timeout
#define GMACF_MAC_RX_TX_STATUS_L_TJT_POS 0
//! Field TJT - Transmit Jabber Timeout
#define GMACF_MAC_RX_TX_STATUS_L_TJT_MASK 0x1u

//! Field RESERVED_NCARR - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_NCARR_POS 1
//! Field RESERVED_NCARR - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_NCARR_MASK 0x2u

//! Field RESERVED_LCARR - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_LCARR_POS 2
//! Field RESERVED_LCARR - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_LCARR_MASK 0x4u

//! Field RESERVED_EXDEF - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_EXDEF_POS 3
//! Field RESERVED_EXDEF - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_EXDEF_MASK 0x8u

//! Field RESERVED_LCOL - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_LCOL_POS 4
//! Field RESERVED_LCOL - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_LCOL_MASK 0x10u

//! Field RESERVED_EXCOL - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_EXCOL_POS 5
//! Field RESERVED_EXCOL - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_EXCOL_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_7_6_MASK 0xC0u

//! Field RWT - Receive Watchdog Timeout
#define GMACF_MAC_RX_TX_STATUS_L_RWT_POS 8
//! Field RWT - Receive Watchdog Timeout
#define GMACF_MAC_RX_TX_STATUS_L_RWT_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACF_MAC_RX_TX_STATUS_H Register GMACF_MAC_RX_TX_STATUS_H - GMACF MAC Rx Tx Status high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_RX_TX_STATUS_H 0x174
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_RX_TX_STATUS_H 0x00D30174u

//! Register Reset Value
#define GMACF_MAC_RX_TX_STATUS_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_RX_TX_STATUS_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_LPI_CONTROL_STATUS_L Register GMACF_MAC_LPI_CONTROL_STATUS_L - GMACF MAC LPI Control Status low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_CONTROL_STATUS_L 0x1A0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_CONTROL_STATUS_L 0x00D301A0u

//! Register Reset Value
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RST 0x00000000u

//! Field TLPIEN - Transmit LPI Entry
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIEN_POS 0
//! Field TLPIEN - Transmit LPI Entry
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIEN_MASK 0x1u

//! Field TLPIEX - Transmit LPI Exit
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIEX_POS 1
//! Field TLPIEX - Transmit LPI Exit
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIEX_MASK 0x2u

//! Field RLPIEN - Receive LPI Entry
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIEN_POS 2
//! Field RLPIEN - Receive LPI Entry
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIEN_MASK 0x4u

//! Field RLPIEX - Receive LPI Exit
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIEX_POS 3
//! Field RLPIEX - Receive LPI Exit
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIEX_MASK 0x8u

//! Field RESERVED_7_4 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RESERVED_7_4_POS 4
//! Field RESERVED_7_4 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RESERVED_7_4_MASK 0xF0u

//! Field TLPIST - Transmit LPI State
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIST_POS 8
//! Field TLPIST - Transmit LPI State
#define GMACF_MAC_LPI_CONTROL_STATUS_L_TLPIST_MASK 0x100u

//! Field RLPIST - Receive LPI State
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIST_POS 9
//! Field RLPIST - Receive LPI State
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RLPIST_MASK 0x200u

//! Field RESERVED_15_10 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RESERVED_15_10_POS 10
//! Field RESERVED_15_10 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_L_RESERVED_15_10_MASK 0xFC00u

//! @}

//! \defgroup GMACF_MAC_LPI_CONTROL_STATUS_H Register GMACF_MAC_LPI_CONTROL_STATUS_H - GMACF MAC LPI Control Status high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_CONTROL_STATUS_H 0x1A4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_CONTROL_STATUS_H 0x00D301A4u

//! Register Reset Value
#define GMACF_MAC_LPI_CONTROL_STATUS_H_RST 0x00000000u

//! Field LPIEN - LPI Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPIEN_POS 0
//! Field LPIEN - LPI Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPIEN_MASK 0x1u

//! Field PLS - PHY Link Status
#define GMACF_MAC_LPI_CONTROL_STATUS_H_PLS_POS 1
//! Field PLS - PHY Link Status
#define GMACF_MAC_LPI_CONTROL_STATUS_H_PLS_MASK 0x2u

//! Field RESERVED_PLSEN - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_H_RESERVED_PLSEN_POS 2
//! Field RESERVED_PLSEN - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_H_RESERVED_PLSEN_MASK 0x4u

//! Field LPITXA - LPI Tx Automate
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPITXA_POS 3
//! Field LPITXA - LPI Tx Automate
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPITXA_MASK 0x8u

//! Field LPIATE - LPI Timer Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPIATE_POS 4
//! Field LPIATE - LPI Timer Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPIATE_MASK 0x10u

//! Field LPITCSE - LPI Tx Clock Stop Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPITCSE_POS 5
//! Field LPITCSE - LPI Tx Clock Stop Enable
#define GMACF_MAC_LPI_CONTROL_STATUS_H_LPITCSE_MASK 0x20u

//! Field RESERVED_31_22 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_H_RESERVED_31_22_POS 6
//! Field RESERVED_31_22 - Reserved.
#define GMACF_MAC_LPI_CONTROL_STATUS_H_RESERVED_31_22_MASK 0xFFC0u

//! @}

//! \defgroup GMACF_MAC_LPI_TIMERS_CONTROL_L Register GMACF_MAC_LPI_TIMERS_CONTROL_L - GMACF MAC LPI Timers Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_TIMERS_CONTROL_L 0x1A8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_TIMERS_CONTROL_L 0x00D301A8u

//! Register Reset Value
#define GMACF_MAC_LPI_TIMERS_CONTROL_L_RST 0x00000000u

//! Field TWT - LPI TW Timer
#define GMACF_MAC_LPI_TIMERS_CONTROL_L_TWT_POS 0
//! Field TWT - LPI TW Timer
#define GMACF_MAC_LPI_TIMERS_CONTROL_L_TWT_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_LPI_TIMERS_CONTROL_H Register GMACF_MAC_LPI_TIMERS_CONTROL_H - GMACF MAC LPI Timers Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_TIMERS_CONTROL_H 0x1AC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_TIMERS_CONTROL_H 0x00D301ACu

//! Register Reset Value
#define GMACF_MAC_LPI_TIMERS_CONTROL_H_RST 0x000003E8u

//! Field LST - LPI LS Timer
#define GMACF_MAC_LPI_TIMERS_CONTROL_H_LST_POS 0
//! Field LST - LPI LS Timer
#define GMACF_MAC_LPI_TIMERS_CONTROL_H_LST_MASK 0x3FFu

//! Field RESERVED_31_26 - Reserved.
#define GMACF_MAC_LPI_TIMERS_CONTROL_H_RESERVED_31_26_POS 10
//! Field RESERVED_31_26 - Reserved.
#define GMACF_MAC_LPI_TIMERS_CONTROL_H_RESERVED_31_26_MASK 0xFC00u

//! @}

//! \defgroup GMACF_MAC_LPI_ENTRY_TIMER_L Register GMACF_MAC_LPI_ENTRY_TIMER_L - GMACF MAC LPI Entry Timer low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_ENTRY_TIMER_L 0x1B0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_ENTRY_TIMER_L 0x00D301B0u

//! Register Reset Value
#define GMACF_MAC_LPI_ENTRY_TIMER_L_RST 0x00000000u

//! Field RESERVED_2_0 - Reserved.
#define GMACF_MAC_LPI_ENTRY_TIMER_L_RESERVED_2_0_POS 0
//! Field RESERVED_2_0 - Reserved.
#define GMACF_MAC_LPI_ENTRY_TIMER_L_RESERVED_2_0_MASK 0x7u

//! Field LPIET - LPI Entry Timer
#define GMACF_MAC_LPI_ENTRY_TIMER_L_LPIET_POS 3
//! Field LPIET - LPI Entry Timer
#define GMACF_MAC_LPI_ENTRY_TIMER_L_LPIET_MASK 0xFFF8u

//! @}

//! \defgroup GMACF_MAC_LPI_ENTRY_TIMER_H Register GMACF_MAC_LPI_ENTRY_TIMER_H - GMACF MAC LPI Entry Timer high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LPI_ENTRY_TIMER_H 0x1B4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LPI_ENTRY_TIMER_H 0x00D301B4u

//! Register Reset Value
#define GMACF_MAC_LPI_ENTRY_TIMER_H_RST 0x00000000u

//! Field LPIET - LPI Entry Timer
#define GMACF_MAC_LPI_ENTRY_TIMER_H_LPIET_POS 0
//! Field LPIET - LPI Entry Timer
#define GMACF_MAC_LPI_ENTRY_TIMER_H_LPIET_MASK 0xFu

//! Field RESERVED_31_20 - Reserved.
#define GMACF_MAC_LPI_ENTRY_TIMER_H_RESERVED_31_20_POS 4
//! Field RESERVED_31_20 - Reserved.
#define GMACF_MAC_LPI_ENTRY_TIMER_H_RESERVED_31_20_MASK 0xFFF0u

//! @}

//! \defgroup GMACF_MAC_1US_TIC_COUNTER_L Register GMACF_MAC_1US_TIC_COUNTER_L - GMACF MAC 1US Tic Counter low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_1US_TIC_COUNTER_L 0x1B8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_1US_TIC_COUNTER_L 0x00D301B8u

//! Register Reset Value
#define GMACF_MAC_1US_TIC_COUNTER_L_RST 0x00000063u

//! Field TIC_1US_CNTR - 1US TIC Counter
#define GMACF_MAC_1US_TIC_COUNTER_L_TIC_1US_CNTR_POS 0
//! Field TIC_1US_CNTR - 1US TIC Counter
#define GMACF_MAC_1US_TIC_COUNTER_L_TIC_1US_CNTR_MASK 0xFFFu

//! Field RESERVED_31_12 - Reserved.
#define GMACF_MAC_1US_TIC_COUNTER_L_RESERVED_31_12_POS 12
//! Field RESERVED_31_12 - Reserved.
#define GMACF_MAC_1US_TIC_COUNTER_L_RESERVED_31_12_MASK 0xF000u

//! @}

//! \defgroup GMACF_MAC_1US_TIC_COUNTER_H Register GMACF_MAC_1US_TIC_COUNTER_H - GMACF MAC 1US Tic Counter high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_1US_TIC_COUNTER_H 0x1BC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_1US_TIC_COUNTER_H 0x00D301BCu

//! Register Reset Value
#define GMACF_MAC_1US_TIC_COUNTER_H_RST 0x00000000u

//! Field RESERVED_31_12 - Reserved.
#define GMACF_MAC_1US_TIC_COUNTER_H_RESERVED_31_12_POS 0
//! Field RESERVED_31_12 - Reserved.
#define GMACF_MAC_1US_TIC_COUNTER_H_RESERVED_31_12_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_VERSION_L Register GMACF_MAC_VERSION_L - GMACF MAC Version low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_VERSION_L 0x220
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_VERSION_L 0x00D30220u

//! Register Reset Value
#define GMACF_MAC_VERSION_L_RST 0x00001050u

//! Field SNPSVER - Synopsys-defined Version
#define GMACF_MAC_VERSION_L_SNPSVER_POS 0
//! Field SNPSVER - Synopsys-defined Version
#define GMACF_MAC_VERSION_L_SNPSVER_MASK 0xFFu

//! Field USERVER - User-defined Version (configured with coreConsultant)
#define GMACF_MAC_VERSION_L_USERVER_POS 8
//! Field USERVER - User-defined Version (configured with coreConsultant)
#define GMACF_MAC_VERSION_L_USERVER_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_VERSION_H Register GMACF_MAC_VERSION_H - GMACF MAC Version high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_VERSION_H 0x224
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_VERSION_H 0x00D30224u

//! Register Reset Value
#define GMACF_MAC_VERSION_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_VERSION_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_VERSION_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_DEBUG_L Register GMACF_MAC_DEBUG_L - GMACF MAC Debug low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_DEBUG_L 0x228
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_DEBUG_L 0x00D30228u

//! Register Reset Value
#define GMACF_MAC_DEBUG_L_RST 0x00000000u

//! Field RPESTS - MAC GMII or MII Receive Protocol Engine Status
#define GMACF_MAC_DEBUG_L_RPESTS_POS 0
//! Field RPESTS - MAC GMII or MII Receive Protocol Engine Status
#define GMACF_MAC_DEBUG_L_RPESTS_MASK 0x1u

//! Field RFCFCSTS - MAC Receive Packet Controller FIFO Status
#define GMACF_MAC_DEBUG_L_RFCFCSTS_POS 1
//! Field RFCFCSTS - MAC Receive Packet Controller FIFO Status
#define GMACF_MAC_DEBUG_L_RFCFCSTS_MASK 0x6u

//! Field RESERVED_15_3 - Reserved.
#define GMACF_MAC_DEBUG_L_RESERVED_15_3_POS 3
//! Field RESERVED_15_3 - Reserved.
#define GMACF_MAC_DEBUG_L_RESERVED_15_3_MASK 0xFFF8u

//! @}

//! \defgroup GMACF_MAC_DEBUG_H Register GMACF_MAC_DEBUG_H - GMACF MAC Debug high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_DEBUG_H 0x22C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_DEBUG_H 0x00D3022Cu

//! Register Reset Value
#define GMACF_MAC_DEBUG_H_RST 0x00000000u

//! Field TPESTS - MAC GMII or MII Transmit Protocol Engine Status
#define GMACF_MAC_DEBUG_H_TPESTS_POS 0
//! Field TPESTS - MAC GMII or MII Transmit Protocol Engine Status
#define GMACF_MAC_DEBUG_H_TPESTS_MASK 0x1u

//! Field TFCSTS - MAC Transmit Packet Controller Status
#define GMACF_MAC_DEBUG_H_TFCSTS_POS 1
//! Field TFCSTS - MAC Transmit Packet Controller Status
#define GMACF_MAC_DEBUG_H_TFCSTS_MASK 0x6u

//! Field RESERVED_31_19 - Reserved.
#define GMACF_MAC_DEBUG_H_RESERVED_31_19_POS 3
//! Field RESERVED_31_19 - Reserved.
#define GMACF_MAC_DEBUG_H_RESERVED_31_19_MASK 0xFFF8u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE0_L Register GMACF_MAC_HW_FEATURE0_L - GMACF MAC HW Feature0 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE0_L 0x238
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE0_L 0x00D30238u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE0_L_RST 0x00007107u

//! Field MIISEL - 10 or 100 Mbps Support
#define GMACF_MAC_HW_FEATURE0_L_MIISEL_POS 0
//! Field MIISEL - 10 or 100 Mbps Support
#define GMACF_MAC_HW_FEATURE0_L_MIISEL_MASK 0x1u

//! Field GMIISEL - 1000 Mbps Support
#define GMACF_MAC_HW_FEATURE0_L_GMIISEL_POS 1
//! Field GMIISEL - 1000 Mbps Support
#define GMACF_MAC_HW_FEATURE0_L_GMIISEL_MASK 0x2u

//! Field HDSEL - Half-duplex Support
#define GMACF_MAC_HW_FEATURE0_L_HDSEL_POS 2
//! Field HDSEL - Half-duplex Support
#define GMACF_MAC_HW_FEATURE0_L_HDSEL_MASK 0x4u

//! Field PCSSEL - PCS Registers (TBI, SGMII, or RTBI PHY interface)
#define GMACF_MAC_HW_FEATURE0_L_PCSSEL_POS 3
//! Field PCSSEL - PCS Registers (TBI, SGMII, or RTBI PHY interface)
#define GMACF_MAC_HW_FEATURE0_L_PCSSEL_MASK 0x8u

//! Field VLHASH - VLAN Hash Filter Selected
#define GMACF_MAC_HW_FEATURE0_L_VLHASH_POS 4
//! Field VLHASH - VLAN Hash Filter Selected
#define GMACF_MAC_HW_FEATURE0_L_VLHASH_MASK 0x10u

//! Field SMASEL - SMA (MDIO) Interface
#define GMACF_MAC_HW_FEATURE0_L_SMASEL_POS 5
//! Field SMASEL - SMA (MDIO) Interface
#define GMACF_MAC_HW_FEATURE0_L_SMASEL_MASK 0x20u

//! Field RWKSEL - PMT Remote Wake-up Packet Enable
#define GMACF_MAC_HW_FEATURE0_L_RWKSEL_POS 6
//! Field RWKSEL - PMT Remote Wake-up Packet Enable
#define GMACF_MAC_HW_FEATURE0_L_RWKSEL_MASK 0x40u

//! Field MGKSEL - PMT Magic Packet Enable
#define GMACF_MAC_HW_FEATURE0_L_MGKSEL_POS 7
//! Field MGKSEL - PMT Magic Packet Enable
#define GMACF_MAC_HW_FEATURE0_L_MGKSEL_MASK 0x80u

//! Field MMCSEL - RMON Module Enable
#define GMACF_MAC_HW_FEATURE0_L_MMCSEL_POS 8
//! Field MMCSEL - RMON Module Enable
#define GMACF_MAC_HW_FEATURE0_L_MMCSEL_MASK 0x100u

//! Field ARPOFFSEL - ARP Offload Enabled
#define GMACF_MAC_HW_FEATURE0_L_ARPOFFSEL_POS 9
//! Field ARPOFFSEL - ARP Offload Enabled
#define GMACF_MAC_HW_FEATURE0_L_ARPOFFSEL_MASK 0x200u

//! Field RESERVED_11_10 - Reserved.
#define GMACF_MAC_HW_FEATURE0_L_RESERVED_11_10_POS 10
//! Field RESERVED_11_10 - Reserved.
#define GMACF_MAC_HW_FEATURE0_L_RESERVED_11_10_MASK 0xC00u

//! Field TSSEL - IEEE 1588-2008 Timestamp Enabled
#define GMACF_MAC_HW_FEATURE0_L_TSSEL_POS 12
//! Field TSSEL - IEEE 1588-2008 Timestamp Enabled
#define GMACF_MAC_HW_FEATURE0_L_TSSEL_MASK 0x1000u

//! Field EEESEL - Energy Efficient Ethernet Enabled
#define GMACF_MAC_HW_FEATURE0_L_EEESEL_POS 13
//! Field EEESEL - Energy Efficient Ethernet Enabled
#define GMACF_MAC_HW_FEATURE0_L_EEESEL_MASK 0x2000u

//! Field TXCOESEL - Transmit Checksum Offload Enabled
#define GMACF_MAC_HW_FEATURE0_L_TXCOESEL_POS 14
//! Field TXCOESEL - Transmit Checksum Offload Enabled
#define GMACF_MAC_HW_FEATURE0_L_TXCOESEL_MASK 0x4000u

//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_HW_FEATURE0_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_HW_FEATURE0_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE0_H Register GMACF_MAC_HW_FEATURE0_H - GMACF MAC HW Feature0 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE0_H 0x23C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE0_H 0x00D3023Cu

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE0_H_RST 0x00000201u

//! Field RXCOESEL - Receive Checksum Offload Enabled
#define GMACF_MAC_HW_FEATURE0_H_RXCOESEL_POS 0
//! Field RXCOESEL - Receive Checksum Offload Enabled
#define GMACF_MAC_HW_FEATURE0_H_RXCOESEL_MASK 0x1u

//! Field RESERVED_17 - Reserved.
#define GMACF_MAC_HW_FEATURE0_H_RESERVED_17_POS 1
//! Field RESERVED_17 - Reserved.
#define GMACF_MAC_HW_FEATURE0_H_RESERVED_17_MASK 0x2u

//! Field ADDMACADRSEL - MAC Addresses 1-31 Selected
#define GMACF_MAC_HW_FEATURE0_H_ADDMACADRSEL_POS 2
//! Field ADDMACADRSEL - MAC Addresses 1-31 Selected
#define GMACF_MAC_HW_FEATURE0_H_ADDMACADRSEL_MASK 0x7Cu

//! Field MACADR32SEL - MAC Addresses 32-63 Selected
#define GMACF_MAC_HW_FEATURE0_H_MACADR32SEL_POS 7
//! Field MACADR32SEL - MAC Addresses 32-63 Selected
#define GMACF_MAC_HW_FEATURE0_H_MACADR32SEL_MASK 0x80u

//! Field MACADR64SEL - MAC Addresses 64-127 Selected
#define GMACF_MAC_HW_FEATURE0_H_MACADR64SEL_POS 8
//! Field MACADR64SEL - MAC Addresses 64-127 Selected
#define GMACF_MAC_HW_FEATURE0_H_MACADR64SEL_MASK 0x100u

//! Field TSSTSSEL - Timestamp System Time Source
#define GMACF_MAC_HW_FEATURE0_H_TSSTSSEL_POS 9
//! Field TSSTSSEL - Timestamp System Time Source
#define GMACF_MAC_HW_FEATURE0_H_TSSTSSEL_MASK 0x600u

//! Field SAVLANINS - Source Address or VLAN Insertion Enable
#define GMACF_MAC_HW_FEATURE0_H_SAVLANINS_POS 11
//! Field SAVLANINS - Source Address or VLAN Insertion Enable
#define GMACF_MAC_HW_FEATURE0_H_SAVLANINS_MASK 0x800u

//! Field ACTPHYSEL - Active PHY Selected
#define GMACF_MAC_HW_FEATURE0_H_ACTPHYSEL_POS 12
//! Field ACTPHYSEL - Active PHY Selected
#define GMACF_MAC_HW_FEATURE0_H_ACTPHYSEL_MASK 0x7000u

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE0_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE0_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE1_L Register GMACF_MAC_HW_FEATURE1_L - GMACF MAC HW Feature1 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE1_L 0x240
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE1_L 0x00D30240u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE1_L_RST 0x00003800u

//! Field RXFIFOSIZE - MTL Receive FIFO Size
#define GMACF_MAC_HW_FEATURE1_L_RXFIFOSIZE_POS 0
//! Field RXFIFOSIZE - MTL Receive FIFO Size
#define GMACF_MAC_HW_FEATURE1_L_RXFIFOSIZE_MASK 0x1Fu

//! Field SPRAM - Single Port RAM Enable
#define GMACF_MAC_HW_FEATURE1_L_SPRAM_POS 5
//! Field SPRAM - Single Port RAM Enable
#define GMACF_MAC_HW_FEATURE1_L_SPRAM_MASK 0x20u

//! Field TXFIFOSIZE - MTL Transmit FIFO Size
#define GMACF_MAC_HW_FEATURE1_L_TXFIFOSIZE_POS 6
//! Field TXFIFOSIZE - MTL Transmit FIFO Size
#define GMACF_MAC_HW_FEATURE1_L_TXFIFOSIZE_MASK 0x7C0u

//! Field OSTEN - One-Step Timestamping Enable
#define GMACF_MAC_HW_FEATURE1_L_OSTEN_POS 11
//! Field OSTEN - One-Step Timestamping Enable
#define GMACF_MAC_HW_FEATURE1_L_OSTEN_MASK 0x800u

//! Field PTOEN - PTP Offload Enable
#define GMACF_MAC_HW_FEATURE1_L_PTOEN_POS 12
//! Field PTOEN - PTP Offload Enable
#define GMACF_MAC_HW_FEATURE1_L_PTOEN_MASK 0x1000u

//! Field ADVTHWORD - IEEE 1588 High Word Register Enable
#define GMACF_MAC_HW_FEATURE1_L_ADVTHWORD_POS 13
//! Field ADVTHWORD - IEEE 1588 High Word Register Enable
#define GMACF_MAC_HW_FEATURE1_L_ADVTHWORD_MASK 0x2000u

//! Field ADDR64 - Address Width.
#define GMACF_MAC_HW_FEATURE1_L_ADDR64_POS 14
//! Field ADDR64 - Address Width.
#define GMACF_MAC_HW_FEATURE1_L_ADDR64_MASK 0xC000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE1_H Register GMACF_MAC_HW_FEATURE1_H - GMACF MAC HW Feature1 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE1_H 0x244
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE1_H 0x00D30244u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE1_H_RST 0x00000080u

//! Field DCBEN - DCB Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_DCBEN_POS 0
//! Field DCBEN - DCB Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_DCBEN_MASK 0x1u

//! Field SPHEN - Split Header Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_SPHEN_POS 1
//! Field SPHEN - Split Header Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_SPHEN_MASK 0x2u

//! Field TSOEN - TCP Segmentation Offload Enable
#define GMACF_MAC_HW_FEATURE1_H_TSOEN_POS 2
//! Field TSOEN - TCP Segmentation Offload Enable
#define GMACF_MAC_HW_FEATURE1_H_TSOEN_MASK 0x4u

//! Field DBGMEMA - DMA Debug Registers Enable
#define GMACF_MAC_HW_FEATURE1_H_DBGMEMA_POS 3
//! Field DBGMEMA - DMA Debug Registers Enable
#define GMACF_MAC_HW_FEATURE1_H_DBGMEMA_MASK 0x8u

//! Field AVSEL - AV Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_AVSEL_POS 4
//! Field AVSEL - AV Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_AVSEL_MASK 0x10u

//! Field RAVSEL - Rx Side Only AV Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_RAVSEL_POS 5
//! Field RAVSEL - Rx Side Only AV Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_RAVSEL_MASK 0x20u

//! Field RESERVED_22 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_22_POS 6
//! Field RESERVED_22 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_22_MASK 0x40u

//! Field POUOST - One Step for PTP over UDP/IP Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_POUOST_POS 7
//! Field POUOST - One Step for PTP over UDP/IP Feature Enable
#define GMACF_MAC_HW_FEATURE1_H_POUOST_MASK 0x80u

//! Field HASHTBLSZ - Hash Table Size
#define GMACF_MAC_HW_FEATURE1_H_HASHTBLSZ_POS 8
//! Field HASHTBLSZ - Hash Table Size
#define GMACF_MAC_HW_FEATURE1_H_HASHTBLSZ_MASK 0x300u

//! Field RESERVED_26 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_26_POS 10
//! Field RESERVED_26 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_26_MASK 0x400u

//! Field L3L4FNUM - Total number of L3 or L4 Filters
#define GMACF_MAC_HW_FEATURE1_H_L3L4FNUM_POS 11
//! Field L3L4FNUM - Total number of L3 or L4 Filters
#define GMACF_MAC_HW_FEATURE1_H_L3L4FNUM_MASK 0x7800u

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE1_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE2_L Register GMACF_MAC_HW_FEATURE2_L - GMACF MAC HW Feature2 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE2_L 0x248
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE2_L 0x00D30248u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE2_L_RST 0x00000000u

//! Field RXQCNT - Number of MTL Receive Queues
#define GMACF_MAC_HW_FEATURE2_L_RXQCNT_POS 0
//! Field RXQCNT - Number of MTL Receive Queues
#define GMACF_MAC_HW_FEATURE2_L_RXQCNT_MASK 0xFu

//! Field RESERVED_5_4 - Reserved.
#define GMACF_MAC_HW_FEATURE2_L_RESERVED_5_4_POS 4
//! Field RESERVED_5_4 - Reserved.
#define GMACF_MAC_HW_FEATURE2_L_RESERVED_5_4_MASK 0x30u

//! Field TXQCNT - Number of MTL Transmit Queues
#define GMACF_MAC_HW_FEATURE2_L_TXQCNT_POS 6
//! Field TXQCNT - Number of MTL Transmit Queues
#define GMACF_MAC_HW_FEATURE2_L_TXQCNT_MASK 0x3C0u

//! Field RESERVED_11_10 - Reserved.
#define GMACF_MAC_HW_FEATURE2_L_RESERVED_11_10_POS 10
//! Field RESERVED_11_10 - Reserved.
#define GMACF_MAC_HW_FEATURE2_L_RESERVED_11_10_MASK 0xC00u

//! Field RXCHCNT - Number of DMA Receive Channels
#define GMACF_MAC_HW_FEATURE2_L_RXCHCNT_POS 12
//! Field RXCHCNT - Number of DMA Receive Channels
#define GMACF_MAC_HW_FEATURE2_L_RXCHCNT_MASK 0xF000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE2_H Register GMACF_MAC_HW_FEATURE2_H - GMACF MAC HW Feature2 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE2_H 0x24C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE2_H 0x00D3024Cu

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE2_H_RST 0x00004100u

//! Field RESERVED_17_16 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_17_16_POS 0
//! Field RESERVED_17_16 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_17_16_MASK 0x3u

//! Field TXCHCNT - Number of DMA Transmit Channels
#define GMACF_MAC_HW_FEATURE2_H_TXCHCNT_POS 2
//! Field TXCHCNT - Number of DMA Transmit Channels
#define GMACF_MAC_HW_FEATURE2_H_TXCHCNT_MASK 0x3Cu

//! Field RESERVED_23_22 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_23_22_POS 6
//! Field RESERVED_23_22 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_23_22_MASK 0xC0u

//! Field PPSOUTNUM - Number of PPS Outputs
#define GMACF_MAC_HW_FEATURE2_H_PPSOUTNUM_POS 8
//! Field PPSOUTNUM - Number of PPS Outputs
#define GMACF_MAC_HW_FEATURE2_H_PPSOUTNUM_MASK 0x700u

//! Field RESERVED_27 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_27_POS 11
//! Field RESERVED_27 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_27_MASK 0x800u

//! Field AUXSNAPNUM - Number of Auxiliary Snapshot Inputs
#define GMACF_MAC_HW_FEATURE2_H_AUXSNAPNUM_POS 12
//! Field AUXSNAPNUM - Number of Auxiliary Snapshot Inputs
#define GMACF_MAC_HW_FEATURE2_H_AUXSNAPNUM_MASK 0x7000u

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_HW_FEATURE2_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE3_L Register GMACF_MAC_HW_FEATURE3_L - GMACF MAC HW Feature3 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE3_L 0x250
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE3_L 0x00D30250u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE3_L_RST 0x00000000u

//! Field NRVF - Number of Extended VLAN Tag Filters Enabled
#define GMACF_MAC_HW_FEATURE3_L_NRVF_POS 0
//! Field NRVF - Number of Extended VLAN Tag Filters Enabled
#define GMACF_MAC_HW_FEATURE3_L_NRVF_MASK 0x7u

//! Field RESERVED_3 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_3_POS 3
//! Field RESERVED_3 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_3_MASK 0x8u

//! Field CBTISEL - Queue/Channel based VLAN tag insertion on Tx Enable
#define GMACF_MAC_HW_FEATURE3_L_CBTISEL_POS 4
//! Field CBTISEL - Queue/Channel based VLAN tag insertion on Tx Enable
#define GMACF_MAC_HW_FEATURE3_L_CBTISEL_MASK 0x10u

//! Field DVLAN - No Content.
#define GMACF_MAC_HW_FEATURE3_L_DVLAN_POS 5
//! Field DVLAN - No Content.
#define GMACF_MAC_HW_FEATURE3_L_DVLAN_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_7_6_MASK 0xC0u

//! Field DBGSSEL - Debug Bus Support Enable
#define GMACF_MAC_HW_FEATURE3_L_DBGSSEL_POS 8
//! Field DBGSSEL - Debug Bus Support Enable
#define GMACF_MAC_HW_FEATURE3_L_DBGSSEL_MASK 0x100u

//! Field PDUPSEL - Broadcast/Multicast Packet Duplication
#define GMACF_MAC_HW_FEATURE3_L_PDUPSEL_POS 9
//! Field PDUPSEL - Broadcast/Multicast Packet Duplication
#define GMACF_MAC_HW_FEATURE3_L_PDUPSEL_MASK 0x200u

//! Field RESERVED_15_10 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_15_10_POS 10
//! Field RESERVED_15_10 - Reserved.
#define GMACF_MAC_HW_FEATURE3_L_RESERVED_15_10_MASK 0xFC00u

//! @}

//! \defgroup GMACF_MAC_HW_FEATURE3_H Register GMACF_MAC_HW_FEATURE3_H - GMACF MAC HW Feature3 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_HW_FEATURE3_H 0x254
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_HW_FEATURE3_H 0x00D30254u

//! Register Reset Value
#define GMACF_MAC_HW_FEATURE3_H_RST 0x00000032u

//! Field ESTSEL - Enhancements to Scheduling Traffic Enable
#define GMACF_MAC_HW_FEATURE3_H_ESTSEL_POS 0
//! Field ESTSEL - Enhancements to Scheduling Traffic Enable
#define GMACF_MAC_HW_FEATURE3_H_ESTSEL_MASK 0x1u

//! Field ESTDEP - Depth of the Gate Control List
#define GMACF_MAC_HW_FEATURE3_H_ESTDEP_POS 1
//! Field ESTDEP - Depth of the Gate Control List
#define GMACF_MAC_HW_FEATURE3_H_ESTDEP_MASK 0xEu

//! Field ESTWID - Width of the Time Interval field in the Gate Control List
#define GMACF_MAC_HW_FEATURE3_H_ESTWID_POS 4
//! Field ESTWID - Width of the Time Interval field in the Gate Control List
#define GMACF_MAC_HW_FEATURE3_H_ESTWID_MASK 0x30u

//! Field RESERVED_22 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_22_POS 6
//! Field RESERVED_22 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_22_MASK 0x40u

//! Field ESTTISW - Width of the Left Shift Amount for Time Interval
#define GMACF_MAC_HW_FEATURE3_H_ESTTISW_POS 7
//! Field ESTTISW - Width of the Left Shift Amount for Time Interval
#define GMACF_MAC_HW_FEATURE3_H_ESTTISW_MASK 0x180u

//! Field RESERVED_25 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_25_POS 9
//! Field RESERVED_25 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_25_MASK 0x200u

//! Field FPESEL - Frame Preemption Enable
#define GMACF_MAC_HW_FEATURE3_H_FPESEL_POS 10
//! Field FPESEL - Frame Preemption Enable
#define GMACF_MAC_HW_FEATURE3_H_FPESEL_MASK 0x400u

//! Field TBSSEL - Time Based Scheduling Enable
#define GMACF_MAC_HW_FEATURE3_H_TBSSEL_POS 11
//! Field TBSSEL - Time Based Scheduling Enable
#define GMACF_MAC_HW_FEATURE3_H_TBSSEL_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACF_MAC_HW_FEATURE3_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACF_MAC_CSR_SW_CTRL_L Register GMACF_MAC_CSR_SW_CTRL_L - GMACF MAC CSR SW Ctrl low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_CSR_SW_CTRL_L 0x460
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_CSR_SW_CTRL_L 0x00D30460u

//! Register Reset Value
#define GMACF_MAC_CSR_SW_CTRL_L_RST 0x00000000u

//! Field RCWE - Register Clear on Write 1 Enable
#define GMACF_MAC_CSR_SW_CTRL_L_RCWE_POS 0
//! Field RCWE - Register Clear on Write 1 Enable
#define GMACF_MAC_CSR_SW_CTRL_L_RCWE_MASK 0x1u

//! Field RESERVED_7_1 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_7_1_POS 1
//! Field RESERVED_7_1 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_7_1_MASK 0xFEu

//! Field RESERVED_SEEN - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_SEEN_POS 8
//! Field RESERVED_SEEN - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_SEEN_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACF_MAC_CSR_SW_CTRL_H Register GMACF_MAC_CSR_SW_CTRL_H - GMACF MAC CSR SW Ctrl high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_CSR_SW_CTRL_H 0x464
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_CSR_SW_CTRL_H 0x00D30464u

//! Register Reset Value
#define GMACF_MAC_CSR_SW_CTRL_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MAC_CSR_SW_CTRL_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_ADDRESS0_HIGH_L Register GMACF_MAC_ADDRESS0_HIGH_L - GMACF MAC Address0 High low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_ADDRESS0_HIGH_L 0x600
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_ADDRESS0_HIGH_L 0x00D30600u

//! Register Reset Value
#define GMACF_MAC_ADDRESS0_HIGH_L_RST 0x0000FFFFu

//! Field ADDRHI - MAC Address0[47:32]
#define GMACF_MAC_ADDRESS0_HIGH_L_ADDRHI_POS 0
//! Field ADDRHI - MAC Address0[47:32]
#define GMACF_MAC_ADDRESS0_HIGH_L_ADDRHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_ADDRESS0_HIGH_H Register GMACF_MAC_ADDRESS0_HIGH_H - GMACF MAC Address0 High high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_ADDRESS0_HIGH_H 0x604
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_ADDRESS0_HIGH_H 0x00D30604u

//! Register Reset Value
#define GMACF_MAC_ADDRESS0_HIGH_H_RST 0x00008000u

//! Field RESERVED_DCS - Reserved.
#define GMACF_MAC_ADDRESS0_HIGH_H_RESERVED_DCS_POS 0
//! Field RESERVED_DCS - Reserved.
#define GMACF_MAC_ADDRESS0_HIGH_H_RESERVED_DCS_MASK 0x1u

//! Field RESERVED_30_Y - Reserved.
#define GMACF_MAC_ADDRESS0_HIGH_H_RESERVED_30_Y_POS 1
//! Field RESERVED_30_Y - Reserved.
#define GMACF_MAC_ADDRESS0_HIGH_H_RESERVED_30_Y_MASK 0x7FFEu

//! Field AE - Address Enable
#define GMACF_MAC_ADDRESS0_HIGH_H_AE_POS 15
//! Field AE - Address Enable
#define GMACF_MAC_ADDRESS0_HIGH_H_AE_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_ADDRESS0_LOW_L Register GMACF_MAC_ADDRESS0_LOW_L - GMACF MAC Address0 Low low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_ADDRESS0_LOW_L 0x608
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_ADDRESS0_LOW_L 0x00D30608u

//! Register Reset Value
#define GMACF_MAC_ADDRESS0_LOW_L_RST 0x00000000u

//! Field ADDRLO - MAC Address0[31:0]
#define GMACF_MAC_ADDRESS0_LOW_L_ADDRLO_POS 0
//! Field ADDRLO - MAC Address0[31:0]
#define GMACF_MAC_ADDRESS0_LOW_L_ADDRLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_ADDRESS0_LOW_H Register GMACF_MAC_ADDRESS0_LOW_H - GMACF MAC Address0 Low high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_ADDRESS0_LOW_H 0x60C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_ADDRESS0_LOW_H 0x00D3060Cu

//! Register Reset Value
#define GMACF_MAC_ADDRESS0_LOW_H_RST 0x00000000u

//! Field ADDRLO - MAC Address0[31:0]
#define GMACF_MAC_ADDRESS0_LOW_H_ADDRLO_POS 0
//! Field ADDRLO - MAC Address0[31:0]
#define GMACF_MAC_ADDRESS0_LOW_H_ADDRLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MMC_CONTROL_L Register GMACF_MMC_CONTROL_L - GMACF MMC Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_CONTROL_L 0xE00
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_CONTROL_L 0x00D30E00u

//! Register Reset Value
#define GMACF_MMC_CONTROL_L_RST 0x00000000u

//! Field CNTRST - Counters Reset
#define GMACF_MMC_CONTROL_L_CNTRST_POS 0
//! Field CNTRST - Counters Reset
#define GMACF_MMC_CONTROL_L_CNTRST_MASK 0x1u

//! Field CNTSTOPRO - Counter Stop Rollover
#define GMACF_MMC_CONTROL_L_CNTSTOPRO_POS 1
//! Field CNTSTOPRO - Counter Stop Rollover
#define GMACF_MMC_CONTROL_L_CNTSTOPRO_MASK 0x2u

//! Field RSTONRD - Reset on Read
#define GMACF_MMC_CONTROL_L_RSTONRD_POS 2
//! Field RSTONRD - Reset on Read
#define GMACF_MMC_CONTROL_L_RSTONRD_MASK 0x4u

//! Field CNTFREEZ - MMC Counter Freeze
#define GMACF_MMC_CONTROL_L_CNTFREEZ_POS 3
//! Field CNTFREEZ - MMC Counter Freeze
#define GMACF_MMC_CONTROL_L_CNTFREEZ_MASK 0x8u

//! Field CNTPRST - Counters Preset
#define GMACF_MMC_CONTROL_L_CNTPRST_POS 4
//! Field CNTPRST - Counters Preset
#define GMACF_MMC_CONTROL_L_CNTPRST_MASK 0x10u

//! Field CNTPRSTLVL - Full-Half Preset
#define GMACF_MMC_CONTROL_L_CNTPRSTLVL_POS 5
//! Field CNTPRSTLVL - Full-Half Preset
#define GMACF_MMC_CONTROL_L_CNTPRSTLVL_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACF_MMC_CONTROL_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACF_MMC_CONTROL_L_RESERVED_7_6_MASK 0xC0u

//! Field UCDBC - Update MMC Counters for Dropped Broadcast Packets
#define GMACF_MMC_CONTROL_L_UCDBC_POS 8
//! Field UCDBC - Update MMC Counters for Dropped Broadcast Packets
#define GMACF_MMC_CONTROL_L_UCDBC_MASK 0x100u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MMC_CONTROL_L_RESERVED_31_9_POS 9
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MMC_CONTROL_L_RESERVED_31_9_MASK 0xFE00u

//! @}

//! \defgroup GMACF_MMC_CONTROL_H Register GMACF_MMC_CONTROL_H - GMACF MMC Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_CONTROL_H 0xE04
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_CONTROL_H 0x00D30E04u

//! Register Reset Value
#define GMACF_MMC_CONTROL_H_RST 0x00000000u

//! Field RESERVED_31_9 - Reserved.
#define GMACF_MMC_CONTROL_H_RESERVED_31_9_POS 0
//! Field RESERVED_31_9 - Reserved.
#define GMACF_MMC_CONTROL_H_RESERVED_31_9_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MMC_RX_INTERRUPT_L Register GMACF_MMC_RX_INTERRUPT_L - GMACF MMC Rx Interrupt low word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_RX_INTERRUPT_L 0xE08
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_RX_INTERRUPT_L 0x00D30E08u

//! Register Reset Value
#define GMACF_MMC_RX_INTERRUPT_L_RST 0x00000000u

//! Field RXGBPKTIS - MMC Receive Good Bad Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXGBPKTIS_POS 0
//! Field RXGBPKTIS - MMC Receive Good Bad Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXGBPKTIS_MASK 0x1u

//! Field RESERVED_RXGBOCTIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXGBOCTIS_POS 1
//! Field RESERVED_RXGBOCTIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXGBOCTIS_MASK 0x2u

//! Field RESERVED_RXGOCTIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXGOCTIS_POS 2
//! Field RESERVED_RXGOCTIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXGOCTIS_MASK 0x4u

//! Field RESERVED_RXBCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXBCGPIS_POS 3
//! Field RESERVED_RXBCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXBCGPIS_MASK 0x8u

//! Field RESERVED_RXMCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXMCGPIS_POS 4
//! Field RESERVED_RXMCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXMCGPIS_MASK 0x10u

//! Field RXCRCERPIS - MMC Receive CRC Error Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXCRCERPIS_POS 5
//! Field RXCRCERPIS - MMC Receive CRC Error Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXCRCERPIS_MASK 0x20u

//! Field RESERVED_RXALGNERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXALGNERPIS_POS 6
//! Field RESERVED_RXALGNERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXALGNERPIS_MASK 0x40u

//! Field RESERVED_RXRUNTPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXRUNTPIS_POS 7
//! Field RESERVED_RXRUNTPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXRUNTPIS_MASK 0x80u

//! Field RESERVED_RXJABERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXJABERPIS_POS 8
//! Field RESERVED_RXJABERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RXJABERPIS_MASK 0x100u

//! Field RXUSIZEGPIS - MMC Receive Undersize Good Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXUSIZEGPIS_POS 9
//! Field RXUSIZEGPIS - MMC Receive Undersize Good Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXUSIZEGPIS_MASK 0x200u

//! Field RXOSIZEGPIS - MMC Receive Oversize Good Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXOSIZEGPIS_POS 10
//! Field RXOSIZEGPIS - MMC Receive Oversize Good Packet Counter Interrupt Status
#define GMACF_MMC_RX_INTERRUPT_L_RXOSIZEGPIS_MASK 0x400u

//! Field RESERVED_RX64OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX64OCTGBPIS_POS 11
//! Field RESERVED_RX64OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX64OCTGBPIS_MASK 0x800u

//! Field RESERVED_RX65T127OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX65T127OCTGBPIS_POS 12
//! Field RESERVED_RX65T127OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX65T127OCTGBPIS_MASK 0x1000u

//! Field RESERVED_RX128T255OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX128T255OCTGBPIS_POS 13
//! Field RESERVED_RX128T255OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX128T255OCTGBPIS_MASK 0x2000u

//! Field RESERVED_RX256T511OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX256T511OCTGBPIS_POS 14
//! Field RESERVED_RX256T511OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX256T511OCTGBPIS_MASK 0x4000u

//! Field RESERVED_RX512T1023OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX512T1023OCTGBPIS_POS 15
//! Field RESERVED_RX512T1023OCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_L_RESERVED_RX512T1023OCTGBPIS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MMC_RX_INTERRUPT_H Register GMACF_MMC_RX_INTERRUPT_H - GMACF MMC Rx Interrupt high word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_RX_INTERRUPT_H 0xE0C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_RX_INTERRUPT_H 0x00D30E0Cu

//! Register Reset Value
#define GMACF_MMC_RX_INTERRUPT_H_RST 0x00000000u

//! Field RESERVED_RX1024TMAXOCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RX1024TMAXOCTGBPIS_POS 0
//! Field RESERVED_RX1024TMAXOCTGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RX1024TMAXOCTGBPIS_MASK 0x1u

//! Field RESERVED_RXUCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXUCGPIS_POS 1
//! Field RESERVED_RXUCGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXUCGPIS_MASK 0x2u

//! Field RESERVED_RXLENERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXLENERPIS_POS 2
//! Field RESERVED_RXLENERPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXLENERPIS_MASK 0x4u

//! Field RESERVED_RXORANGEPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXORANGEPIS_POS 3
//! Field RESERVED_RXORANGEPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXORANGEPIS_MASK 0x8u

//! Field RESERVED_RXPAUSPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXPAUSPIS_POS 4
//! Field RESERVED_RXPAUSPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXPAUSPIS_MASK 0x10u

//! Field RESERVED_RXFOVPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXFOVPIS_POS 5
//! Field RESERVED_RXFOVPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXFOVPIS_MASK 0x20u

//! Field RESERVED_RXVLANGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXVLANGBPIS_POS 6
//! Field RESERVED_RXVLANGBPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXVLANGBPIS_MASK 0x40u

//! Field RESERVED_RXWDOGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXWDOGPIS_POS 7
//! Field RESERVED_RXWDOGPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXWDOGPIS_MASK 0x80u

//! Field RESERVED_RXRCVERRPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXRCVERRPIS_POS 8
//! Field RESERVED_RXRCVERRPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXRCVERRPIS_MASK 0x100u

//! Field RESERVED_RXCTRLPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXCTRLPIS_POS 9
//! Field RESERVED_RXCTRLPIS - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_RXCTRLPIS_MASK 0x200u

//! Field RXLPIUSCIS - MMC Receive LPI microsecond counter interrupt status
#define GMACF_MMC_RX_INTERRUPT_H_RXLPIUSCIS_POS 10
//! Field RXLPIUSCIS - MMC Receive LPI microsecond counter interrupt status
#define GMACF_MMC_RX_INTERRUPT_H_RXLPIUSCIS_MASK 0x400u

//! Field RXLPITRCIS - MMC Receive LPI transition counter interrupt status
#define GMACF_MMC_RX_INTERRUPT_H_RXLPITRCIS_POS 11
//! Field RXLPITRCIS - MMC Receive LPI transition counter interrupt status
#define GMACF_MMC_RX_INTERRUPT_H_RXLPITRCIS_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_RX_INTERRUPT_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACF_MMC_TX_INTERRUPT_L Register GMACF_MMC_TX_INTERRUPT_L - GMACF MMC Tx Interrupt low word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_TX_INTERRUPT_L 0xE10
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_TX_INTERRUPT_L 0x00D30E10u

//! Register Reset Value
#define GMACF_MMC_TX_INTERRUPT_L_RST 0x00000000u

//! Field RESERVED_TXGBOCTIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXGBOCTIS_POS 0
//! Field RESERVED_TXGBOCTIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXGBOCTIS_MASK 0x1u

//! Field TXGBPKTIS - MMC Transmit Good Bad Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_L_TXGBPKTIS_POS 1
//! Field TXGBPKTIS - MMC Transmit Good Bad Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_L_TXGBPKTIS_MASK 0x2u

//! Field RESERVED_TXBCGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXBCGPIS_POS 2
//! Field RESERVED_TXBCGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXBCGPIS_MASK 0x4u

//! Field RESERVED_TXMCGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCGPIS_POS 3
//! Field RESERVED_TXMCGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCGPIS_MASK 0x8u

//! Field RESERVED_TX64OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX64OCTGBPIS_POS 4
//! Field RESERVED_TX64OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX64OCTGBPIS_MASK 0x10u

//! Field RESERVED_TX65T127OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX65T127OCTGBPIS_POS 5
//! Field RESERVED_TX65T127OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX65T127OCTGBPIS_MASK 0x20u

//! Field RESERVED_TX128T255OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX128T255OCTGBPIS_POS 6
//! Field RESERVED_TX128T255OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX128T255OCTGBPIS_MASK 0x40u

//! Field RESERVED_TX256T511OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX256T511OCTGBPIS_POS 7
//! Field RESERVED_TX256T511OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX256T511OCTGBPIS_MASK 0x80u

//! Field RESERVED_TX512T1023OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX512T1023OCTGBPIS_POS 8
//! Field RESERVED_TX512T1023OCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX512T1023OCTGBPIS_MASK 0x100u

//! Field RESERVED_TX1024TMAXOCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX1024TMAXOCTGBPIS_POS 9
//! Field RESERVED_TX1024TMAXOCTGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TX1024TMAXOCTGBPIS_MASK 0x200u

//! Field RESERVED_TXUCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXUCGBPIS_POS 10
//! Field RESERVED_TXUCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXUCGBPIS_MASK 0x400u

//! Field RESERVED_TXMCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCGBPIS_POS 11
//! Field RESERVED_TXMCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCGBPIS_MASK 0x800u

//! Field RESERVED_TXBCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXBCGBPIS_POS 12
//! Field RESERVED_TXBCGBPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXBCGBPIS_MASK 0x1000u

//! Field TXUFLOWERPIS - MMC Transmit Underflow Error Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_L_TXUFLOWERPIS_POS 13
//! Field TXUFLOWERPIS - MMC Transmit Underflow Error Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_L_TXUFLOWERPIS_MASK 0x2000u

//! Field RESERVED_TXSCOLGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXSCOLGPIS_POS 14
//! Field RESERVED_TXSCOLGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXSCOLGPIS_MASK 0x4000u

//! Field RESERVED_TXMCOLGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCOLGPIS_POS 15
//! Field RESERVED_TXMCOLGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_L_RESERVED_TXMCOLGPIS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MMC_TX_INTERRUPT_H Register GMACF_MMC_TX_INTERRUPT_H - GMACF MMC Tx Interrupt high word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_TX_INTERRUPT_H 0xE14
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_TX_INTERRUPT_H 0x00D30E14u

//! Register Reset Value
#define GMACF_MMC_TX_INTERRUPT_H_RST 0x00000000u

//! Field RESERVED_TXDEFPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXDEFPIS_POS 0
//! Field RESERVED_TXDEFPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXDEFPIS_MASK 0x1u

//! Field RESERVED_TXLATCOLPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXLATCOLPIS_POS 1
//! Field RESERVED_TXLATCOLPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXLATCOLPIS_MASK 0x2u

//! Field RESERVED_TXEXCOLPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXEXCOLPIS_POS 2
//! Field RESERVED_TXEXCOLPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXEXCOLPIS_MASK 0x4u

//! Field RESERVED_TXCARERPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXCARERPIS_POS 3
//! Field RESERVED_TXCARERPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXCARERPIS_MASK 0x8u

//! Field RESERVED_TXGOCTIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXGOCTIS_POS 4
//! Field RESERVED_TXGOCTIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXGOCTIS_MASK 0x10u

//! Field TXGPKTIS - MMC Transmit Good Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_H_TXGPKTIS_POS 5
//! Field TXGPKTIS - MMC Transmit Good Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_H_TXGPKTIS_MASK 0x20u

//! Field RESERVED_TXEXDEFPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXEXDEFPIS_POS 6
//! Field RESERVED_TXEXDEFPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXEXDEFPIS_MASK 0x40u

//! Field RESERVED_TXPAUSPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXPAUSPIS_POS 7
//! Field RESERVED_TXPAUSPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXPAUSPIS_MASK 0x80u

//! Field RESERVED_TXVLANGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXVLANGPIS_POS 8
//! Field RESERVED_TXVLANGPIS - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_TXVLANGPIS_MASK 0x100u

//! Field TXOSIZEGPIS - MMC Transmit Oversize Good Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_H_TXOSIZEGPIS_POS 9
//! Field TXOSIZEGPIS - MMC Transmit Oversize Good Packet Counter Interrupt Status
#define GMACF_MMC_TX_INTERRUPT_H_TXOSIZEGPIS_MASK 0x200u

//! Field TXLPIUSCIS - MMC Transmit LPI microsecond counter interrupt status
#define GMACF_MMC_TX_INTERRUPT_H_TXLPIUSCIS_POS 10
//! Field TXLPIUSCIS - MMC Transmit LPI microsecond counter interrupt status
#define GMACF_MMC_TX_INTERRUPT_H_TXLPIUSCIS_MASK 0x400u

//! Field TXLPITRCIS - MMC Transmit LPI transition counter interrupt status
#define GMACF_MMC_TX_INTERRUPT_H_TXLPITRCIS_POS 11
//! Field TXLPITRCIS - MMC Transmit LPI transition counter interrupt status
#define GMACF_MMC_TX_INTERRUPT_H_TXLPITRCIS_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_TX_INTERRUPT_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACF_MMC_RX_INTERRUPT_MASK_L Register GMACF_MMC_RX_INTERRUPT_MASK_L - GMACF MMC Rx Interrupt Mask low word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_RX_INTERRUPT_MASK_L 0xE18
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_RX_INTERRUPT_MASK_L 0x00D30E18u

//! Register Reset Value
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RST 0x00000000u

//! Field RXGBPKTIM - MMC Receive Good Bad Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXGBPKTIM_POS 0
//! Field RXGBPKTIM - MMC Receive Good Bad Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXGBPKTIM_MASK 0x1u

//! Field RESERVED_RXGBOCTIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXGBOCTIM_POS 1
//! Field RESERVED_RXGBOCTIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXGBOCTIM_MASK 0x2u

//! Field RESERVED_RXGOCTIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXGOCTIM_POS 2
//! Field RESERVED_RXGOCTIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXGOCTIM_MASK 0x4u

//! Field RESERVED_RXBCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXBCGPIM_POS 3
//! Field RESERVED_RXBCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXBCGPIM_MASK 0x8u

//! Field RESERVED_RXMCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXMCGPIM_POS 4
//! Field RESERVED_RXMCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXMCGPIM_MASK 0x10u

//! Field RXCRCERPIM - MMC Receive CRC Error Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXCRCERPIM_POS 5
//! Field RXCRCERPIM - MMC Receive CRC Error Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXCRCERPIM_MASK 0x20u

//! Field RESERVED_RXALGNERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXALGNERPIM_POS 6
//! Field RESERVED_RXALGNERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXALGNERPIM_MASK 0x40u

//! Field RESERVED_RXRUNTPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXRUNTPIM_POS 7
//! Field RESERVED_RXRUNTPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXRUNTPIM_MASK 0x80u

//! Field RESERVED_RXJABERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXJABERPIM_POS 8
//! Field RESERVED_RXJABERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RXJABERPIM_MASK 0x100u

//! Field RXUSIZEGPIM - MMC Receive Undersize Good Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXUSIZEGPIM_POS 9
//! Field RXUSIZEGPIM - MMC Receive Undersize Good Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXUSIZEGPIM_MASK 0x200u

//! Field RXOSIZEGPIM - MMC Receive Oversize Good Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXOSIZEGPIM_POS 10
//! Field RXOSIZEGPIM - MMC Receive Oversize Good Packet Counter Interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RXOSIZEGPIM_MASK 0x400u

//! Field RESERVED_RX64OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX64OCTGBPIM_POS 11
//! Field RESERVED_RX64OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX64OCTGBPIM_MASK 0x800u

//! Field RESERVED_RX65T127OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX65T127OCTGBPIM_POS 12
//! Field RESERVED_RX65T127OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX65T127OCTGBPIM_MASK 0x1000u

//! Field RESERVED_RX128T255OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX128T255OCTGBPIM_POS 13
//! Field RESERVED_RX128T255OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX128T255OCTGBPIM_MASK 0x2000u

//! Field RESERVED_RX256T511OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX256T511OCTGBPIM_POS 14
//! Field RESERVED_RX256T511OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX256T511OCTGBPIM_MASK 0x4000u

//! Field RESERVED_RX512T1023OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX512T1023OCTGBPIM_POS 15
//! Field RESERVED_RX512T1023OCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_L_RESERVED_RX512T1023OCTGBPIM_MASK 0x8000u

//! @}

//! \defgroup GMACF_MMC_RX_INTERRUPT_MASK_H Register GMACF_MMC_RX_INTERRUPT_MASK_H - GMACF MMC Rx Interrupt Mask high word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_RX_INTERRUPT_MASK_H 0xE1C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_RX_INTERRUPT_MASK_H 0x00D30E1Cu

//! Register Reset Value
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RST 0x00000000u

//! Field RESERVED_RX1024TMAXOCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RX1024TMAXOCTGBPIM_POS 0
//! Field RESERVED_RX1024TMAXOCTGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RX1024TMAXOCTGBPIM_MASK 0x1u

//! Field RESERVED_RXUCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXUCGPIM_POS 1
//! Field RESERVED_RXUCGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXUCGPIM_MASK 0x2u

//! Field RESERVED_RXLENERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXLENERPIM_POS 2
//! Field RESERVED_RXLENERPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXLENERPIM_MASK 0x4u

//! Field RESERVED_RXORANGEPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXORANGEPIM_POS 3
//! Field RESERVED_RXORANGEPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXORANGEPIM_MASK 0x8u

//! Field RESERVED_RXPAUSPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXPAUSPIM_POS 4
//! Field RESERVED_RXPAUSPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXPAUSPIM_MASK 0x10u

//! Field RESERVED_RXFOVPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXFOVPIM_POS 5
//! Field RESERVED_RXFOVPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXFOVPIM_MASK 0x20u

//! Field RESERVED_RXVLANGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXVLANGBPIM_POS 6
//! Field RESERVED_RXVLANGBPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXVLANGBPIM_MASK 0x40u

//! Field RESERVED_RXWDOGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXWDOGPIM_POS 7
//! Field RESERVED_RXWDOGPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXWDOGPIM_MASK 0x80u

//! Field RESERVED_RXRCVERRPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXRCVERRPIM_POS 8
//! Field RESERVED_RXRCVERRPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXRCVERRPIM_MASK 0x100u

//! Field RESERVED_RXCTRLPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXCTRLPIM_POS 9
//! Field RESERVED_RXCTRLPIM - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_RXCTRLPIM_MASK 0x200u

//! Field RXLPIUSCIM - MMC Receive LPI microsecond counter interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RXLPIUSCIM_POS 10
//! Field RXLPIUSCIM - MMC Receive LPI microsecond counter interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RXLPIUSCIM_MASK 0x400u

//! Field RXLPITRCIM - MMC Receive LPI transition counter interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RXLPITRCIM_POS 11
//! Field RXLPITRCIM - MMC Receive LPI transition counter interrupt Mask
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RXLPITRCIM_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_RX_INTERRUPT_MASK_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACF_MMC_TX_INTERRUPT_MASK_L Register GMACF_MMC_TX_INTERRUPT_MASK_L - GMACF MMC Tx Interrupt Mask low word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_TX_INTERRUPT_MASK_L 0xE20
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_TX_INTERRUPT_MASK_L 0x00D30E20u

//! Register Reset Value
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RST 0x00000000u

//! Field RESERVED_TXGBOCTIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXGBOCTIM_POS 0
//! Field RESERVED_TXGBOCTIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXGBOCTIM_MASK 0x1u

//! Field TXGBPKTIM - MMC Transmit Good Bad Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_L_TXGBPKTIM_POS 1
//! Field TXGBPKTIM - MMC Transmit Good Bad Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_L_TXGBPKTIM_MASK 0x2u

//! Field RESERVED_TXBCGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXBCGPIM_POS 2
//! Field RESERVED_TXBCGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXBCGPIM_MASK 0x4u

//! Field RESERVED_TXMCGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCGPIM_POS 3
//! Field RESERVED_TXMCGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCGPIM_MASK 0x8u

//! Field RESERVED_TX64OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX64OCTGBPIM_POS 4
//! Field RESERVED_TX64OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX64OCTGBPIM_MASK 0x10u

//! Field RESERVED_TX65T127OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX65T127OCTGBPIM_POS 5
//! Field RESERVED_TX65T127OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX65T127OCTGBPIM_MASK 0x20u

//! Field RESERVED_TX128T255OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX128T255OCTGBPIM_POS 6
//! Field RESERVED_TX128T255OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX128T255OCTGBPIM_MASK 0x40u

//! Field RESERVED_TX256T511OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX256T511OCTGBPIM_POS 7
//! Field RESERVED_TX256T511OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX256T511OCTGBPIM_MASK 0x80u

//! Field RESERVED_TX512T1023OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX512T1023OCTGBPIM_POS 8
//! Field RESERVED_TX512T1023OCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX512T1023OCTGBPIM_MASK 0x100u

//! Field RESERVED_TX1024TMAXOCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX1024TMAXOCTGBPIM_POS 9
//! Field RESERVED_TX1024TMAXOCTGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TX1024TMAXOCTGBPIM_MASK 0x200u

//! Field RESERVED_TXUCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXUCGBPIM_POS 10
//! Field RESERVED_TXUCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXUCGBPIM_MASK 0x400u

//! Field RESERVED_TXMCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCGBPIM_POS 11
//! Field RESERVED_TXMCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCGBPIM_MASK 0x800u

//! Field RESERVED_TXBCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXBCGBPIM_POS 12
//! Field RESERVED_TXBCGBPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXBCGBPIM_MASK 0x1000u

//! Field TXUFLOWERPIM - MMC Transmit Underflow Error Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_L_TXUFLOWERPIM_POS 13
//! Field TXUFLOWERPIM - MMC Transmit Underflow Error Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_L_TXUFLOWERPIM_MASK 0x2000u

//! Field RESERVED_TXSCOLGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXSCOLGPIM_POS 14
//! Field RESERVED_TXSCOLGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXSCOLGPIM_MASK 0x4000u

//! Field RESERVED_TXMCOLGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCOLGPIM_POS 15
//! Field RESERVED_TXMCOLGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_L_RESERVED_TXMCOLGPIM_MASK 0x8000u

//! @}

//! \defgroup GMACF_MMC_TX_INTERRUPT_MASK_H Register GMACF_MMC_TX_INTERRUPT_MASK_H - GMACF MMC Tx Interrupt Mask high word
//! @{

//! Register Offset (relative)
#define GMACF_MMC_TX_INTERRUPT_MASK_H 0xE24
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MMC_TX_INTERRUPT_MASK_H 0x00D30E24u

//! Register Reset Value
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RST 0x00000000u

//! Field RESERVED_TXDEFPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXDEFPIM_POS 0
//! Field RESERVED_TXDEFPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXDEFPIM_MASK 0x1u

//! Field RESERVED_TXLATCOLPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXLATCOLPIM_POS 1
//! Field RESERVED_TXLATCOLPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXLATCOLPIM_MASK 0x2u

//! Field RESERVED_TXEXCOLPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXEXCOLPIM_POS 2
//! Field RESERVED_TXEXCOLPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXEXCOLPIM_MASK 0x4u

//! Field RESERVED_TXCARERPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXCARERPIM_POS 3
//! Field RESERVED_TXCARERPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXCARERPIM_MASK 0x8u

//! Field RESERVED_TXGOCTIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXGOCTIM_POS 4
//! Field RESERVED_TXGOCTIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXGOCTIM_MASK 0x10u

//! Field TXGPKTIM - MMC Transmit Good Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXGPKTIM_POS 5
//! Field TXGPKTIM - MMC Transmit Good Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXGPKTIM_MASK 0x20u

//! Field RESERVED_TXEXDEFPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXEXDEFPIM_POS 6
//! Field RESERVED_TXEXDEFPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXEXDEFPIM_MASK 0x40u

//! Field RESERVED_TXPAUSPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXPAUSPIM_POS 7
//! Field RESERVED_TXPAUSPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXPAUSPIM_MASK 0x80u

//! Field RESERVED_TXVLANGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXVLANGPIM_POS 8
//! Field RESERVED_TXVLANGPIM - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_TXVLANGPIM_MASK 0x100u

//! Field TXOSIZEGPIM - MMC Transmit Oversize Good Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXOSIZEGPIM_POS 9
//! Field TXOSIZEGPIM - MMC Transmit Oversize Good Packet Counter Interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXOSIZEGPIM_MASK 0x200u

//! Field TXLPIUSCIM - MMC Transmit LPI microsecond counter interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXLPIUSCIM_POS 10
//! Field TXLPIUSCIM - MMC Transmit LPI microsecond counter interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXLPIUSCIM_MASK 0x400u

//! Field TXLPITRCIM - MMC Transmit LPI transition counter interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXLPITRCIM_POS 11
//! Field TXLPITRCIM - MMC Transmit LPI transition counter interrupt Mask
#define GMACF_MMC_TX_INTERRUPT_MASK_H_TXLPITRCIM_MASK 0x800u

//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_31_28_POS 12
//! Field RESERVED_31_28 - Reserved.
#define GMACF_MMC_TX_INTERRUPT_MASK_H_RESERVED_31_28_MASK 0xF000u

//! @}

//! \defgroup GMACF_TX_PACKET_COUNT_GOOD_BAD_L Register GMACF_TX_PACKET_COUNT_GOOD_BAD_L - GMACF Tx Packet Count Good Bad low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_L 0xE30
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_PACKET_COUNT_GOOD_BAD_L 0x00D30E30u

//! Register Reset Value
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_L_RST 0x00000000u

//! Field TXPKTGB - Tx Packet Count Good Bad
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_L_TXPKTGB_POS 0
//! Field TXPKTGB - Tx Packet Count Good Bad
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_L_TXPKTGB_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_PACKET_COUNT_GOOD_BAD_H Register GMACF_TX_PACKET_COUNT_GOOD_BAD_H - GMACF Tx Packet Count Good Bad high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_H 0xE34
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_PACKET_COUNT_GOOD_BAD_H 0x00D30E34u

//! Register Reset Value
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_H_RST 0x00000000u

//! Field TXPKTGB - Tx Packet Count Good Bad
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_H_TXPKTGB_POS 0
//! Field TXPKTGB - Tx Packet Count Good Bad
#define GMACF_TX_PACKET_COUNT_GOOD_BAD_H_TXPKTGB_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_UNDERFLOW_ERROR_PACKETS_L Register GMACF_TX_UNDERFLOW_ERROR_PACKETS_L - GMACF Tx Underflow Error Packets low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_L 0xE90
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_UNDERFLOW_ERROR_PACKETS_L 0x00D30E90u

//! Register Reset Value
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_L_RST 0x00000000u

//! Field TXUNDRFLW - Tx Underflow Error Packets
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_L_TXUNDRFLW_POS 0
//! Field TXUNDRFLW - Tx Underflow Error Packets
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_L_TXUNDRFLW_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_UNDERFLOW_ERROR_PACKETS_H Register GMACF_TX_UNDERFLOW_ERROR_PACKETS_H - GMACF Tx Underflow Error Packets high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_H 0xE94
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_UNDERFLOW_ERROR_PACKETS_H 0x00D30E94u

//! Register Reset Value
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_H_RST 0x00000000u

//! Field TXUNDRFLW - Tx Underflow Error Packets
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_H_TXUNDRFLW_POS 0
//! Field TXUNDRFLW - Tx Underflow Error Packets
#define GMACF_TX_UNDERFLOW_ERROR_PACKETS_H_TXUNDRFLW_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_PACKET_COUNT_GOOD_L Register GMACF_TX_PACKET_COUNT_GOOD_L - GMACF Tx Packet Count Good low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_PACKET_COUNT_GOOD_L 0xED0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_PACKET_COUNT_GOOD_L 0x00D30ED0u

//! Register Reset Value
#define GMACF_TX_PACKET_COUNT_GOOD_L_RST 0x00000000u

//! Field TXPKTG - Tx Packet Count Good
#define GMACF_TX_PACKET_COUNT_GOOD_L_TXPKTG_POS 0
//! Field TXPKTG - Tx Packet Count Good
#define GMACF_TX_PACKET_COUNT_GOOD_L_TXPKTG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_PACKET_COUNT_GOOD_H Register GMACF_TX_PACKET_COUNT_GOOD_H - GMACF Tx Packet Count Good high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_PACKET_COUNT_GOOD_H 0xED4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_PACKET_COUNT_GOOD_H 0x00D30ED4u

//! Register Reset Value
#define GMACF_TX_PACKET_COUNT_GOOD_H_RST 0x00000000u

//! Field TXPKTG - Tx Packet Count Good
#define GMACF_TX_PACKET_COUNT_GOOD_H_TXPKTG_POS 0
//! Field TXPKTG - Tx Packet Count Good
#define GMACF_TX_PACKET_COUNT_GOOD_H_TXPKTG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_OSIZE_PACKETS_GOOD_L Register GMACF_TX_OSIZE_PACKETS_GOOD_L - GMACF Tx OSize Packets Good low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_OSIZE_PACKETS_GOOD_L 0xEF0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_OSIZE_PACKETS_GOOD_L 0x00D30EF0u

//! Register Reset Value
#define GMACF_TX_OSIZE_PACKETS_GOOD_L_RST 0x00000000u

//! Field TXOSIZG - Tx OSize Packets Good
#define GMACF_TX_OSIZE_PACKETS_GOOD_L_TXOSIZG_POS 0
//! Field TXOSIZG - Tx OSize Packets Good
#define GMACF_TX_OSIZE_PACKETS_GOOD_L_TXOSIZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_OSIZE_PACKETS_GOOD_H Register GMACF_TX_OSIZE_PACKETS_GOOD_H - GMACF Tx OSize Packets Good high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_OSIZE_PACKETS_GOOD_H 0xEF4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_OSIZE_PACKETS_GOOD_H 0x00D30EF4u

//! Register Reset Value
#define GMACF_TX_OSIZE_PACKETS_GOOD_H_RST 0x00000000u

//! Field TXOSIZG - Tx OSize Packets Good
#define GMACF_TX_OSIZE_PACKETS_GOOD_H_TXOSIZG_POS 0
//! Field TXOSIZG - Tx OSize Packets Good
#define GMACF_TX_OSIZE_PACKETS_GOOD_H_TXOSIZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_PACKETS_COUNT_GOOD_BAD_L Register GMACF_RX_PACKETS_COUNT_GOOD_BAD_L - GMACF Rx Packets Count Good Bad low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_L 0xF00
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_PACKETS_COUNT_GOOD_BAD_L 0x00D30F00u

//! Register Reset Value
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_L_RST 0x00000000u

//! Field RXPKTGB - Rx Packets Count Good Bad
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_L_RXPKTGB_POS 0
//! Field RXPKTGB - Rx Packets Count Good Bad
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_L_RXPKTGB_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_PACKETS_COUNT_GOOD_BAD_H Register GMACF_RX_PACKETS_COUNT_GOOD_BAD_H - GMACF Rx Packets Count Good Bad high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_H 0xF04
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_PACKETS_COUNT_GOOD_BAD_H 0x00D30F04u

//! Register Reset Value
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_H_RST 0x00000000u

//! Field RXPKTGB - Rx Packets Count Good Bad
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_H_RXPKTGB_POS 0
//! Field RXPKTGB - Rx Packets Count Good Bad
#define GMACF_RX_PACKETS_COUNT_GOOD_BAD_H_RXPKTGB_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_CRC_ERROR_PACKETS_L Register GMACF_RX_CRC_ERROR_PACKETS_L - GMACF Rx CRC Error Packets low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_CRC_ERROR_PACKETS_L 0xF28
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_CRC_ERROR_PACKETS_L 0x00D30F28u

//! Register Reset Value
#define GMACF_RX_CRC_ERROR_PACKETS_L_RST 0x00000000u

//! Field RXCRCERR - Rx CRC Error Packets
#define GMACF_RX_CRC_ERROR_PACKETS_L_RXCRCERR_POS 0
//! Field RXCRCERR - Rx CRC Error Packets
#define GMACF_RX_CRC_ERROR_PACKETS_L_RXCRCERR_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_CRC_ERROR_PACKETS_H Register GMACF_RX_CRC_ERROR_PACKETS_H - GMACF Rx CRC Error Packets high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_CRC_ERROR_PACKETS_H 0xF2C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_CRC_ERROR_PACKETS_H 0x00D30F2Cu

//! Register Reset Value
#define GMACF_RX_CRC_ERROR_PACKETS_H_RST 0x00000000u

//! Field RXCRCERR - Rx CRC Error Packets
#define GMACF_RX_CRC_ERROR_PACKETS_H_RXCRCERR_POS 0
//! Field RXCRCERR - Rx CRC Error Packets
#define GMACF_RX_CRC_ERROR_PACKETS_H_RXCRCERR_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_UNDERSIZE_PACKETS_GOOD_L Register GMACF_RX_UNDERSIZE_PACKETS_GOOD_L - GMACF Rx Undersize Packets Good low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_L 0xF48
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_UNDERSIZE_PACKETS_GOOD_L 0x00D30F48u

//! Register Reset Value
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_L_RST 0x00000000u

//! Field RXUNDERSZG - Rx Undersize Packets Good
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_L_RXUNDERSZG_POS 0
//! Field RXUNDERSZG - Rx Undersize Packets Good
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_L_RXUNDERSZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_UNDERSIZE_PACKETS_GOOD_H Register GMACF_RX_UNDERSIZE_PACKETS_GOOD_H - GMACF Rx Undersize Packets Good high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_H 0xF4C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_UNDERSIZE_PACKETS_GOOD_H 0x00D30F4Cu

//! Register Reset Value
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_H_RST 0x00000000u

//! Field RXUNDERSZG - Rx Undersize Packets Good
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_H_RXUNDERSZG_POS 0
//! Field RXUNDERSZG - Rx Undersize Packets Good
#define GMACF_RX_UNDERSIZE_PACKETS_GOOD_H_RXUNDERSZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_OVERSIZE_PACKETS_GOOD_L Register GMACF_RX_OVERSIZE_PACKETS_GOOD_L - GMACF Rx Oversize Packets Good low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_L 0xF50
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_OVERSIZE_PACKETS_GOOD_L 0x00D30F50u

//! Register Reset Value
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_L_RST 0x00000000u

//! Field RXOVERSZG - Rx Oversize Packets Good
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_L_RXOVERSZG_POS 0
//! Field RXOVERSZG - Rx Oversize Packets Good
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_L_RXOVERSZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_OVERSIZE_PACKETS_GOOD_H Register GMACF_RX_OVERSIZE_PACKETS_GOOD_H - GMACF Rx Oversize Packets Good high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_H 0xF54
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_OVERSIZE_PACKETS_GOOD_H 0x00D30F54u

//! Register Reset Value
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_H_RST 0x00000000u

//! Field RXOVERSZG - Rx Oversize Packets Good
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_H_RXOVERSZG_POS 0
//! Field RXOVERSZG - Rx Oversize Packets Good
#define GMACF_RX_OVERSIZE_PACKETS_GOOD_H_RXOVERSZG_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_LPI_USEC_CNTR_L Register GMACF_TX_LPI_USEC_CNTR_L - GMACF Tx LPI USEC Cntr low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_LPI_USEC_CNTR_L 0xFD8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_LPI_USEC_CNTR_L 0x00D30FD8u

//! Register Reset Value
#define GMACF_TX_LPI_USEC_CNTR_L_RST 0x00000000u

//! Field TXLPIUSC - Tx LPI Microseconds Counter
#define GMACF_TX_LPI_USEC_CNTR_L_TXLPIUSC_POS 0
//! Field TXLPIUSC - Tx LPI Microseconds Counter
#define GMACF_TX_LPI_USEC_CNTR_L_TXLPIUSC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_LPI_USEC_CNTR_H Register GMACF_TX_LPI_USEC_CNTR_H - GMACF Tx LPI USEC Cntr high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_LPI_USEC_CNTR_H 0xFDC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_LPI_USEC_CNTR_H 0x00D30FDCu

//! Register Reset Value
#define GMACF_TX_LPI_USEC_CNTR_H_RST 0x00000000u

//! Field TXLPIUSC - Tx LPI Microseconds Counter
#define GMACF_TX_LPI_USEC_CNTR_H_TXLPIUSC_POS 0
//! Field TXLPIUSC - Tx LPI Microseconds Counter
#define GMACF_TX_LPI_USEC_CNTR_H_TXLPIUSC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_LPI_TRAN_CNTR_L Register GMACF_TX_LPI_TRAN_CNTR_L - GMACF Tx LPI Tran Cntr low word
//! @{

//! Register Offset (relative)
#define GMACF_TX_LPI_TRAN_CNTR_L 0xFE0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_LPI_TRAN_CNTR_L 0x00D30FE0u

//! Register Reset Value
#define GMACF_TX_LPI_TRAN_CNTR_L_RST 0x00000000u

//! Field TXLPITRC - Tx LPI Transition counter
#define GMACF_TX_LPI_TRAN_CNTR_L_TXLPITRC_POS 0
//! Field TXLPITRC - Tx LPI Transition counter
#define GMACF_TX_LPI_TRAN_CNTR_L_TXLPITRC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_TX_LPI_TRAN_CNTR_H Register GMACF_TX_LPI_TRAN_CNTR_H - GMACF Tx LPI Tran Cntr high word
//! @{

//! Register Offset (relative)
#define GMACF_TX_LPI_TRAN_CNTR_H 0xFE4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_TX_LPI_TRAN_CNTR_H 0x00D30FE4u

//! Register Reset Value
#define GMACF_TX_LPI_TRAN_CNTR_H_RST 0x00000000u

//! Field TXLPITRC - Tx LPI Transition counter
#define GMACF_TX_LPI_TRAN_CNTR_H_TXLPITRC_POS 0
//! Field TXLPITRC - Tx LPI Transition counter
#define GMACF_TX_LPI_TRAN_CNTR_H_TXLPITRC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_LPI_USEC_CNTR_L Register GMACF_RX_LPI_USEC_CNTR_L - GMACF Rx LPI USEC Cntr low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_LPI_USEC_CNTR_L 0xFE8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_LPI_USEC_CNTR_L 0x00D30FE8u

//! Register Reset Value
#define GMACF_RX_LPI_USEC_CNTR_L_RST 0x00000000u

//! Field RXLPIUSC - Rx LPI Microseconds Counter
#define GMACF_RX_LPI_USEC_CNTR_L_RXLPIUSC_POS 0
//! Field RXLPIUSC - Rx LPI Microseconds Counter
#define GMACF_RX_LPI_USEC_CNTR_L_RXLPIUSC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_LPI_USEC_CNTR_H Register GMACF_RX_LPI_USEC_CNTR_H - GMACF Rx LPI USEC Cntr high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_LPI_USEC_CNTR_H 0xFEC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_LPI_USEC_CNTR_H 0x00D30FECu

//! Register Reset Value
#define GMACF_RX_LPI_USEC_CNTR_H_RST 0x00000000u

//! Field RXLPIUSC - Rx LPI Microseconds Counter
#define GMACF_RX_LPI_USEC_CNTR_H_RXLPIUSC_POS 0
//! Field RXLPIUSC - Rx LPI Microseconds Counter
#define GMACF_RX_LPI_USEC_CNTR_H_RXLPIUSC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_LPI_TRAN_CNTR_L Register GMACF_RX_LPI_TRAN_CNTR_L - GMACF Rx LPI Tran Cntr low word
//! @{

//! Register Offset (relative)
#define GMACF_RX_LPI_TRAN_CNTR_L 0xFF0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_LPI_TRAN_CNTR_L 0x00D30FF0u

//! Register Reset Value
#define GMACF_RX_LPI_TRAN_CNTR_L_RST 0x00000000u

//! Field RXLPITRC - Rx LPI Transition counter
#define GMACF_RX_LPI_TRAN_CNTR_L_RXLPITRC_POS 0
//! Field RXLPITRC - Rx LPI Transition counter
#define GMACF_RX_LPI_TRAN_CNTR_L_RXLPITRC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_RX_LPI_TRAN_CNTR_H Register GMACF_RX_LPI_TRAN_CNTR_H - GMACF Rx LPI Tran Cntr high word
//! @{

//! Register Offset (relative)
#define GMACF_RX_LPI_TRAN_CNTR_H 0xFF4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_RX_LPI_TRAN_CNTR_H 0x00D30FF4u

//! Register Reset Value
#define GMACF_RX_LPI_TRAN_CNTR_H_RST 0x00000000u

//! Field RXLPITRC - Rx LPI Transition counter
#define GMACF_RX_LPI_TRAN_CNTR_H_RXLPITRC_POS 0
//! Field RXLPITRC - Rx LPI Transition counter
#define GMACF_RX_LPI_TRAN_CNTR_H_RXLPITRC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_CONTROL_L Register GMACF_MAC_TIMESTAMP_CONTROL_L - GMACF MAC Timestamp Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_CONTROL_L 0x1600
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_CONTROL_L 0x00D31600u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_CONTROL_L_RST 0x00002000u

//! Field TSENA - Enable Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSENA_POS 0
//! Field TSENA - Enable Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSENA_MASK 0x1u

//! Field TSCFUPDT - Fine or Coarse Timestamp Update
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSCFUPDT_POS 1
//! Field TSCFUPDT - Fine or Coarse Timestamp Update
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSCFUPDT_MASK 0x2u

//! Field TSINIT - Initialize Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSINIT_POS 2
//! Field TSINIT - Initialize Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSINIT_MASK 0x4u

//! Field TSUPDT - Update Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSUPDT_POS 3
//! Field TSUPDT - Update Timestamp
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSUPDT_MASK 0x8u

//! Field RESERVED_TSTRIG - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_L_RESERVED_TSTRIG_POS 4
//! Field RESERVED_TSTRIG - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_L_RESERVED_TSTRIG_MASK 0x10u

//! Field TSADDREG - Update Addend Register
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSADDREG_POS 5
//! Field TSADDREG - Update Addend Register
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSADDREG_MASK 0x20u

//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_L_RESERVED_7_6_POS 6
//! Field RESERVED_7_6 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_L_RESERVED_7_6_MASK 0xC0u

//! Field TSENALL - Enable Timestamp for All Packets
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSENALL_POS 8
//! Field TSENALL - Enable Timestamp for All Packets
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSENALL_MASK 0x100u

//! Field TSCTRLSSR - Timestamp Digital or Binary Rollover Control
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSCTRLSSR_POS 9
//! Field TSCTRLSSR - Timestamp Digital or Binary Rollover Control
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSCTRLSSR_MASK 0x200u

//! Field TSVER2ENA - Enable PTP Packet Processing for Version 2 Format
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSVER2ENA_POS 10
//! Field TSVER2ENA - Enable PTP Packet Processing for Version 2 Format
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSVER2ENA_MASK 0x400u

//! Field TSIPENA - Enable Processing of PTP over Ethernet Packets
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPENA_POS 11
//! Field TSIPENA - Enable Processing of PTP over Ethernet Packets
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPENA_MASK 0x800u

//! Field TSIPV6ENA - Enable Processing of PTP Packets Sent over IPv6-UDP
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPV6ENA_POS 12
//! Field TSIPV6ENA - Enable Processing of PTP Packets Sent over IPv6-UDP
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPV6ENA_MASK 0x1000u

//! Field TSIPV4ENA - Enable Processing of PTP Packets Sent over IPv4-UDP
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPV4ENA_POS 13
//! Field TSIPV4ENA - Enable Processing of PTP Packets Sent over IPv4-UDP
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSIPV4ENA_MASK 0x2000u

//! Field TSEVNTENA - Enable Timestamp Snapshot for Event Messages
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSEVNTENA_POS 14
//! Field TSEVNTENA - Enable Timestamp Snapshot for Event Messages
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSEVNTENA_MASK 0x4000u

//! Field TSMSTRENA - Enable Snapshot for Messages Relevant to Master
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSMSTRENA_POS 15
//! Field TSMSTRENA - Enable Snapshot for Messages Relevant to Master
#define GMACF_MAC_TIMESTAMP_CONTROL_L_TSMSTRENA_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_CONTROL_H Register GMACF_MAC_TIMESTAMP_CONTROL_H - GMACF MAC Timestamp Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_CONTROL_H 0x1604
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_CONTROL_H 0x00D31604u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RST 0x00000000u

//! Field SNAPTYPSEL - Select PTP packets for Taking Snapshots
#define GMACF_MAC_TIMESTAMP_CONTROL_H_SNAPTYPSEL_POS 0
//! Field SNAPTYPSEL - Select PTP packets for Taking Snapshots
#define GMACF_MAC_TIMESTAMP_CONTROL_H_SNAPTYPSEL_MASK 0x3u

//! Field TSENMACADDR - Enable MAC Address for PTP Packet Filtering
#define GMACF_MAC_TIMESTAMP_CONTROL_H_TSENMACADDR_POS 2
//! Field TSENMACADDR - Enable MAC Address for PTP Packet Filtering
#define GMACF_MAC_TIMESTAMP_CONTROL_H_TSENMACADDR_MASK 0x4u

//! Field CSC - Enable checksum correction during OST for PTP over UDP/IPv4 packets
#define GMACF_MAC_TIMESTAMP_CONTROL_H_CSC_POS 3
//! Field CSC - Enable checksum correction during OST for PTP over UDP/IPv4 packets
#define GMACF_MAC_TIMESTAMP_CONTROL_H_CSC_MASK 0x8u

//! Field RESERVED_ESTI - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_ESTI_POS 4
//! Field RESERVED_ESTI - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_ESTI_MASK 0x10u

//! Field RESERVED_23_21 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_23_21_POS 5
//! Field RESERVED_23_21 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_23_21_MASK 0xE0u

//! Field TXTSSTSM - Transmit Timestamp Status Mode
#define GMACF_MAC_TIMESTAMP_CONTROL_H_TXTSSTSM_POS 8
//! Field TXTSSTSM - Transmit Timestamp Status Mode
#define GMACF_MAC_TIMESTAMP_CONTROL_H_TXTSSTSM_MASK 0x100u

//! Field RESERVED_27_25 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_27_25_POS 9
//! Field RESERVED_27_25 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_27_25_MASK 0xE00u

//! Field AV8021ASMEN - AV 802.1AS Mode Enable
#define GMACF_MAC_TIMESTAMP_CONTROL_H_AV8021ASMEN_POS 12
//! Field AV8021ASMEN - AV 802.1AS Mode Enable
#define GMACF_MAC_TIMESTAMP_CONTROL_H_AV8021ASMEN_MASK 0x1000u

//! Field RESERVED_31_29 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_31_29_POS 13
//! Field RESERVED_31_29 - Reserved.
#define GMACF_MAC_TIMESTAMP_CONTROL_H_RESERVED_31_29_MASK 0xE000u

//! @}

//! \defgroup GMACF_MAC_SUB_SECOND_INCREMENT_L Register GMACF_MAC_SUB_SECOND_INCREMENT_L - GMACF MAC Sub Second Increment low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SUB_SECOND_INCREMENT_L 0x1608
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SUB_SECOND_INCREMENT_L 0x00D31608u

//! Register Reset Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_L_RST 0x00000000u

//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_SUB_SECOND_INCREMENT_L_RESERVED_7_0_POS 0
//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_SUB_SECOND_INCREMENT_L_RESERVED_7_0_MASK 0xFFu

//! Field SNSINC - Sub-nanosecond Increment Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_L_SNSINC_POS 8
//! Field SNSINC - Sub-nanosecond Increment Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_L_SNSINC_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_SUB_SECOND_INCREMENT_H Register GMACF_MAC_SUB_SECOND_INCREMENT_H - GMACF MAC Sub Second Increment high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SUB_SECOND_INCREMENT_H 0x160C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SUB_SECOND_INCREMENT_H 0x00D3160Cu

//! Register Reset Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_H_RST 0x00000000u

//! Field SSINC - Sub-second Increment Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_H_SSINC_POS 0
//! Field SSINC - Sub-second Increment Value
#define GMACF_MAC_SUB_SECOND_INCREMENT_H_SSINC_MASK 0xFFu

//! Field RESERVED_31_24 - Reserved.
#define GMACF_MAC_SUB_SECOND_INCREMENT_H_RESERVED_31_24_POS 8
//! Field RESERVED_31_24 - Reserved.
#define GMACF_MAC_SUB_SECOND_INCREMENT_H_RESERVED_31_24_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_SECONDS_L Register GMACF_MAC_SYSTEM_TIME_SECONDS_L - GMACF MAC System Time Seconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_SECONDS_L 0x1610
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_SECONDS_L 0x00D31610u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_SECONDS_L_RST 0x00000000u

//! Field TSS - Timestamp Second
#define GMACF_MAC_SYSTEM_TIME_SECONDS_L_TSS_POS 0
//! Field TSS - Timestamp Second
#define GMACF_MAC_SYSTEM_TIME_SECONDS_L_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_SECONDS_H Register GMACF_MAC_SYSTEM_TIME_SECONDS_H - GMACF MAC System Time Seconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_SECONDS_H 0x1614
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_SECONDS_H 0x00D31614u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_SECONDS_H_RST 0x00000000u

//! Field TSS - Timestamp Second
#define GMACF_MAC_SYSTEM_TIME_SECONDS_H_TSS_POS 0
//! Field TSS - Timestamp Second
#define GMACF_MAC_SYSTEM_TIME_SECONDS_H_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L Register GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L - GMACF MAC System Time Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L 0x1618
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L 0x00D31618u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L_TSSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H Register GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H - GMACF MAC System Time Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H 0x161C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H 0x00D3161Cu

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_TSSS_MASK 0x7FFFu

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L Register GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L - GMACF MAC System Time Seconds Update low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L 0x1620
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L 0x00D31620u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_RST 0x00000000u

//! Field TSS - Timestamp Seconds
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_POS 0
//! Field TSS - Timestamp Seconds
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H Register GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H - GMACF MAC System Time Seconds Update high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H 0x1624
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H 0x00D31624u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_RST 0x00000000u

//! Field TSS - Timestamp Seconds
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_TSS_POS 0
//! Field TSS - Timestamp Seconds
#define GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H_TSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L Register GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L - GMACF MAC System Time Nanoseconds Update low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L 0x1628
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L 0x00D31628u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H Register GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H - GMACF MAC System Time Nanoseconds Update high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H 0x162C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H 0x00D3162Cu

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_RST 0x00000000u

//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_TSSS_POS 0
//! Field TSSS - Timestamp Sub Seconds
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_TSSS_MASK 0x7FFFu

//! Field ADDSUB - Add or Subtract Time
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_ADDSUB_POS 15
//! Field ADDSUB - Add or Subtract Time
#define GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_ADDSUB_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_ADDEND_L Register GMACF_MAC_TIMESTAMP_ADDEND_L - GMACF MAC Timestamp Addend low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_ADDEND_L 0x1630
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_ADDEND_L 0x00D31630u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_ADDEND_L_RST 0x00000000u

//! Field TSAR - Timestamp Addend Register
#define GMACF_MAC_TIMESTAMP_ADDEND_L_TSAR_POS 0
//! Field TSAR - Timestamp Addend Register
#define GMACF_MAC_TIMESTAMP_ADDEND_L_TSAR_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_ADDEND_H Register GMACF_MAC_TIMESTAMP_ADDEND_H - GMACF MAC Timestamp Addend high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_ADDEND_H 0x1634
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_ADDEND_H 0x00D31634u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_ADDEND_H_RST 0x00000000u

//! Field TSAR - Timestamp Addend Register
#define GMACF_MAC_TIMESTAMP_ADDEND_H_TSAR_POS 0
//! Field TSAR - Timestamp Addend Register
#define GMACF_MAC_TIMESTAMP_ADDEND_H_TSAR_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L Register GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L - GMACF MAC System Time Higher Word Seconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L 0x1638
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L 0x00D31638u

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L_RST 0x00000000u

//! Field TSHWR - Timestamp Higher Word Register
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L_TSHWR_POS 0
//! Field TSHWR - Timestamp Higher Word Register
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_L_TSHWR_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H Register GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H - GMACF MAC System Time Higher Word Seconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H 0x163C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H 0x00D3163Cu

//! Register Reset Value
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_STATUS_L Register GMACF_MAC_TIMESTAMP_STATUS_L - GMACF MAC Timestamp Status low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_STATUS_L 0x1640
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_STATUS_L 0x00D31640u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_STATUS_L_RST 0x00000000u

//! Field TSSOVF - Timestamp Seconds Overflow
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSSOVF_POS 0
//! Field TSSOVF - Timestamp Seconds Overflow
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSSOVF_MASK 0x1u

//! Field TSTARGT0 - Timestamp Target Time Reached
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT0_POS 1
//! Field TSTARGT0 - Timestamp Target Time Reached
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT0_MASK 0x2u

//! Field AUXTSTRIG - Auxiliary Timestamp Trigger Snapshot
#define GMACF_MAC_TIMESTAMP_STATUS_L_AUXTSTRIG_POS 2
//! Field AUXTSTRIG - Auxiliary Timestamp Trigger Snapshot
#define GMACF_MAC_TIMESTAMP_STATUS_L_AUXTSTRIG_MASK 0x4u

//! Field TSTRGTERR0 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR0_POS 3
//! Field TSTRGTERR0 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR0_MASK 0x8u

//! Field TSTARGT1 - Timestamp Target Time Reached for Target Time PPS1
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT1_POS 4
//! Field TSTARGT1 - Timestamp Target Time Reached for Target Time PPS1
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT1_MASK 0x10u

//! Field TSTRGTERR1 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR1_POS 5
//! Field TSTRGTERR1 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR1_MASK 0x20u

//! Field TSTARGT2 - Timestamp Target Time Reached for Target Time PPS2
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT2_POS 6
//! Field TSTARGT2 - Timestamp Target Time Reached for Target Time PPS2
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT2_MASK 0x40u

//! Field TSTRGTERR2 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR2_POS 7
//! Field TSTRGTERR2 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR2_MASK 0x80u

//! Field TSTARGT3 - Timestamp Target Time Reached for Target Time PPS3
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT3_POS 8
//! Field TSTARGT3 - Timestamp Target Time Reached for Target Time PPS3
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTARGT3_MASK 0x100u

//! Field TSTRGTERR3 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR3_POS 9
//! Field TSTRGTERR3 - Timestamp Target Time Error
#define GMACF_MAC_TIMESTAMP_STATUS_L_TSTRGTERR3_MASK 0x200u

//! Field RESERVED_14_10 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_L_RESERVED_14_10_POS 10
//! Field RESERVED_14_10 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_L_RESERVED_14_10_MASK 0x7C00u

//! Field TXTSSIS - Tx Timestamp Status Interrupt Status
#define GMACF_MAC_TIMESTAMP_STATUS_L_TXTSSIS_POS 15
//! Field TXTSSIS - Tx Timestamp Status Interrupt Status
#define GMACF_MAC_TIMESTAMP_STATUS_L_TXTSSIS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_STATUS_H Register GMACF_MAC_TIMESTAMP_STATUS_H - GMACF MAC Timestamp Status high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_STATUS_H 0x1644
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_STATUS_H 0x00D31644u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_STATUS_H_RST 0x00000000u

//! Field ATSSTN - Auxiliary Timestamp Snapshot Trigger Identifier
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSSTN_POS 0
//! Field ATSSTN - Auxiliary Timestamp Snapshot Trigger Identifier
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSSTN_MASK 0xFu

//! Field RESERVED_23_20 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_H_RESERVED_23_20_POS 4
//! Field RESERVED_23_20 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_H_RESERVED_23_20_MASK 0xF0u

//! Field ATSSTM - Auxiliary Timestamp Snapshot Trigger Missed
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSSTM_POS 8
//! Field ATSSTM - Auxiliary Timestamp Snapshot Trigger Missed
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSSTM_MASK 0x100u

//! Field ATSNS - Number of Auxiliary Timestamp Snapshots
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSNS_POS 9
//! Field ATSNS - Number of Auxiliary Timestamp Snapshots
#define GMACF_MAC_TIMESTAMP_STATUS_H_ATSNS_MASK 0x3E00u

//! Field RESERVED_31_30 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_H_RESERVED_31_30_POS 14
//! Field RESERVED_31_30 - Reserved.
#define GMACF_MAC_TIMESTAMP_STATUS_H_RESERVED_31_30_MASK 0xC000u

//! @}

//! \defgroup GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L Register GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L - GMACF MAC Tx Timestamp Status Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L 0x1660
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L 0x00D31660u

//! Register Reset Value
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L_RST 0x00000000u

//! Field TXTSSLO - Transmit Timestamp Status Low
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L_TXTSSLO_POS 0
//! Field TXTSSLO - Transmit Timestamp Status Low
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L_TXTSSLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H Register GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H - GMACF MAC Tx Timestamp Status Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H 0x1664
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H 0x00D31664u

//! Register Reset Value
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_RST 0x00000000u

//! Field TXTSSLO - Transmit Timestamp Status Low
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSLO_POS 0
//! Field TXTSSLO - Transmit Timestamp Status Low
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSLO_MASK 0x7FFFu

//! Field TXTSSMIS - Transmit Timestamp Status Missed
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSMIS_POS 15
//! Field TXTSSMIS - Transmit Timestamp Status Missed
#define GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSMIS_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L Register GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L - GMACF MAC Tx Timestamp Status Seconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L 0x1668
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L 0x00D31668u

//! Register Reset Value
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L_RST 0x00000000u

//! Field TXTSSHI - Transmit Timestamp Status High
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L_TXTSSHI_POS 0
//! Field TXTSSHI - Transmit Timestamp Status High
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L_TXTSSHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H Register GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H - GMACF MAC Tx Timestamp Status Seconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H 0x166C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H 0x00D3166Cu

//! Register Reset Value
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H_RST 0x00000000u

//! Field TXTSSHI - Transmit Timestamp Status High
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H_TXTSSHI_POS 0
//! Field TXTSSHI - Transmit Timestamp Status High
#define GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H_TXTSSHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_CONTROL_L Register GMACF_MAC_AUXILIARY_CONTROL_L - GMACF MAC Auxiliary Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_CONTROL_L 0x1680
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_CONTROL_L 0x00D31680u

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_CONTROL_L_RST 0x00000000u

//! Field ATSFC - Auxiliary Snapshot FIFO Clear
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSFC_POS 0
//! Field ATSFC - Auxiliary Snapshot FIFO Clear
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSFC_MASK 0x1u

//! Field RESERVED_3_1 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_L_RESERVED_3_1_POS 1
//! Field RESERVED_3_1 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_L_RESERVED_3_1_MASK 0xEu

//! Field ATSEN0 - Auxiliary Snapshot 0 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN0_POS 4
//! Field ATSEN0 - Auxiliary Snapshot 0 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN0_MASK 0x10u

//! Field ATSEN1 - Auxiliary Snapshot 1 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN1_POS 5
//! Field ATSEN1 - Auxiliary Snapshot 1 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN1_MASK 0x20u

//! Field ATSEN2 - Auxiliary Snapshot 2 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN2_POS 6
//! Field ATSEN2 - Auxiliary Snapshot 2 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN2_MASK 0x40u

//! Field ATSEN3 - Auxiliary Snapshot 3 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN3_POS 7
//! Field ATSEN3 - Auxiliary Snapshot 3 Enable
#define GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN3_MASK 0x80u

//! Field RESERVED_31_8 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_L_RESERVED_31_8_POS 8
//! Field RESERVED_31_8 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_L_RESERVED_31_8_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_CONTROL_H Register GMACF_MAC_AUXILIARY_CONTROL_H - GMACF MAC Auxiliary Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_CONTROL_H 0x1684
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_CONTROL_H 0x00D31684u

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_CONTROL_H_RST 0x00000000u

//! Field RESERVED_31_8 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_H_RESERVED_31_8_POS 0
//! Field RESERVED_31_8 - Reserved.
#define GMACF_MAC_AUXILIARY_CONTROL_H_RESERVED_31_8_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L Register GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L - GMACF MAC Auxiliary Timestamp Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L 0x1690
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L 0x00D31690u

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L_RST 0x00000000u

//! Field AUXTSLO - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L_AUXTSLO_POS 0
//! Field AUXTSLO - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L_AUXTSLO_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H Register GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H - GMACF MAC Auxiliary Timestamp Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H 0x1694
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H 0x00D31694u

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_RST 0x00000000u

//! Field AUXTSLO - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_AUXTSLO_POS 0
//! Field AUXTSLO - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_AUXTSLO_MASK 0x7FFFu

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L Register GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L - GMACF MAC Auxiliary Timestamp Seconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L 0x1698
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L 0x00D31698u

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L_RST 0x00000000u

//! Field AUXTSHI - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L_AUXTSHI_POS 0
//! Field AUXTSHI - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L_AUXTSHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H Register GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H - GMACF MAC Auxiliary Timestamp Seconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H 0x169C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H 0x00D3169Cu

//! Register Reset Value
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H_RST 0x00000000u

//! Field AUXTSHI - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H_AUXTSHI_POS 0
//! Field AUXTSHI - Auxiliary Timestamp
#define GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H_AUXTSHI_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L Register GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L - GMACF MAC Timestamp Ingress Asym Corr low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L 0x16A0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L 0x00D316A0u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L_RST 0x00000000u

//! Field OSTIAC - One-Step Timestamp Ingress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L_OSTIAC_POS 0
//! Field OSTIAC - One-Step Timestamp Ingress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_L_OSTIAC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H Register GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H - GMACF MAC Timestamp Ingress Asym Corr high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H 0x16A4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H 0x00D316A4u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H_RST 0x00000000u

//! Field OSTIAC - One-Step Timestamp Ingress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H_OSTIAC_POS 0
//! Field OSTIAC - One-Step Timestamp Ingress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_ASYM_CORR_H_OSTIAC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L Register GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L - GMACF MAC Timestamp Egress Asym Corr low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L 0x16A8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L 0x00D316A8u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L_RST 0x00000000u

//! Field OSTEAC - One-Step Timestamp Egress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L_OSTEAC_POS 0
//! Field OSTEAC - One-Step Timestamp Egress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_L_OSTEAC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H Register GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H - GMACF MAC Timestamp Egress Asym Corr high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H 0x16AC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H 0x00D316ACu

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H_RST 0x00000000u

//! Field OSTEAC - One-Step Timestamp Egress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H_OSTEAC_POS 0
//! Field OSTEAC - One-Step Timestamp Egress Asymmetry Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_ASYM_CORR_H_OSTEAC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L Register GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L - GMACF MAC Timestamp Ingress Corr Nanosecond low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L 0x16B0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L 0x00D316B0u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_RST 0x00000000u

//! Field TSIC - Timestamp Ingress Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_TSIC_POS 0
//! Field TSIC - Timestamp Ingress Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_L_TSIC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H Register GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H - GMACF MAC Timestamp Ingress Corr Nanosecond high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H 0x16B4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H 0x00D316B4u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_RST 0x00000000u

//! Field TSIC - Timestamp Ingress Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_TSIC_POS 0
//! Field TSIC - Timestamp Ingress Correction
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_H_TSIC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L Register GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L - GMACF MAC Timestamp Egress Corr Nanosecond low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L 0x16B8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L 0x00D316B8u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_RST 0x00000000u

//! Field TSEC - Timestamp Egress Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_TSEC_POS 0
//! Field TSEC - Timestamp Egress Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_L_TSEC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H Register GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H - GMACF MAC Timestamp Egress Corr Nanosecond high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H 0x16BC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H 0x00D316BCu

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_RST 0x00000000u

//! Field TSEC - Timestamp Egress Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_TSEC_POS 0
//! Field TSEC - Timestamp Egress Correction
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_H_TSEC_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L Register GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L - GMACF MAC Timestamp Ingress Corr Subnanosec low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L 0x16C0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L 0x00D316C0u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L_RST 0x00000000u

//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L_RESERVED_7_0_POS 0
//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L_RESERVED_7_0_MASK 0xFFu

//! Field TSICSNS - Timestamp Ingress Correction, sub-nanoseconds
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L_TSICSNS_POS 8
//! Field TSICSNS - Timestamp Ingress Correction, sub-nanoseconds
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_L_TSICSNS_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H Register GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H - GMACF MAC Timestamp Ingress Corr Subnanosec high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H 0x16C4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H 0x00D316C4u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L Register GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L - GMACF MAC Timestamp Egress Corr Subnanosec low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L 0x16C8
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L 0x00D316C8u

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L_RST 0x00000000u

//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L_RESERVED_7_0_POS 0
//! Field RESERVED_7_0 - Reserved.
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L_RESERVED_7_0_MASK 0xFFu

//! Field TSECSNS - Timestamp Egress Correction, sub-nanoseconds
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L_TSECSNS_POS 8
//! Field TSECSNS - Timestamp Egress Correction, sub-nanoseconds
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_L_TSECSNS_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H Register GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H - GMACF MAC Timestamp Egress Corr Subnanosec high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H 0x16CC
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H 0x00D316CCu

//! Register Reset Value
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS_CONTROL_L Register GMACF_MAC_PPS_CONTROL_L - GMACF MAC PPS Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS_CONTROL_L 0x16E0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS_CONTROL_L 0x00D316E0u

//! Register Reset Value
#define GMACF_MAC_PPS_CONTROL_L_RST 0x00000000u

//! Field PPSCTRL_PPSCMD - PPS Output Frequency Control
#define GMACF_MAC_PPS_CONTROL_L_PPSCTRL_PPSCMD_POS 0
//! Field PPSCTRL_PPSCMD - PPS Output Frequency Control
#define GMACF_MAC_PPS_CONTROL_L_PPSCTRL_PPSCMD_MASK 0xFu

//! Field PPSEN0 - Flexible PPS Output Mode Enable
#define GMACF_MAC_PPS_CONTROL_L_PPSEN0_POS 4
//! Field PPSEN0 - Flexible PPS Output Mode Enable
#define GMACF_MAC_PPS_CONTROL_L_PPSEN0_MASK 0x10u

//! Field TRGTMODSEL0 - Target Time Register Mode for PPS0 Output
#define GMACF_MAC_PPS_CONTROL_L_TRGTMODSEL0_POS 5
//! Field TRGTMODSEL0 - Target Time Register Mode for PPS0 Output
#define GMACF_MAC_PPS_CONTROL_L_TRGTMODSEL0_MASK 0x60u

//! Field RESERVED_7 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_7_POS 7
//! Field RESERVED_7 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_7_MASK 0x80u

//! Field RESERVED_PPSCMD1 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_PPSCMD1_POS 8
//! Field RESERVED_PPSCMD1 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_PPSCMD1_MASK 0x700u

//! Field RESERVED_12_11 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_12_11_POS 11
//! Field RESERVED_12_11 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_12_11_MASK 0x1800u

//! Field RESERVED_TRGTMODSEL1 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL1_POS 13
//! Field RESERVED_TRGTMODSEL1 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_TRGTMODSEL1_MASK 0x6000u

//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_15_POS 15
//! Field RESERVED_15 - Reserved.
#define GMACF_MAC_PPS_CONTROL_L_RESERVED_15_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_PPS_CONTROL_H Register GMACF_MAC_PPS_CONTROL_H - GMACF MAC PPS Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS_CONTROL_H 0x16E4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS_CONTROL_H 0x00D316E4u

//! Register Reset Value
#define GMACF_MAC_PPS_CONTROL_H_RST 0x00000000u

//! Field RESERVED_PPSCMD2 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_PPSCMD2_POS 0
//! Field RESERVED_PPSCMD2 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_PPSCMD2_MASK 0x7u

//! Field RESERVED_20_19 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_20_19_POS 3
//! Field RESERVED_20_19 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_20_19_MASK 0x18u

//! Field RESERVED_TRGTMODSEL2 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL2_POS 5
//! Field RESERVED_TRGTMODSEL2 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL2_MASK 0x60u

//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_23_POS 7
//! Field RESERVED_23 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_23_MASK 0x80u

//! Field RESERVED_PPSCMD3 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_PPSCMD3_POS 8
//! Field RESERVED_PPSCMD3 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_PPSCMD3_MASK 0x700u

//! Field RESERVED_28_27 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_28_27_POS 11
//! Field RESERVED_28_27 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_28_27_MASK 0x1800u

//! Field RESERVED_TRGTMODSEL3 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL3_POS 13
//! Field RESERVED_TRGTMODSEL3 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_TRGTMODSEL3_MASK 0x6000u

//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_31_POS 15
//! Field RESERVED_31 - Reserved.
#define GMACF_MAC_PPS_CONTROL_H_RESERVED_31_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L Register GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L - GMACF MAC PPS0 Target Time Seconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L 0x1700
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L 0x00D31700u

//! Register Reset Value
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L_RST 0x00000000u

//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L_TSTRH0_POS 0
//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L_TSTRH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H Register GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H - GMACF MAC PPS0 Target Time Seconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H 0x1704
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H 0x00D31704u

//! Register Reset Value
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H_RST 0x00000000u

//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H_TSTRH0_POS 0
//! Field TSTRH0 - PPS Target Time Seconds Register
#define GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H_TSTRH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L Register GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L - GMACF MAC PPS0 Target Time Nanoseconds low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L 0x1708
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L 0x00D31708u

//! Register Reset Value
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_RST 0x00000000u

//! Field TTSL0 - Target Time Low for PPS Register
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_TTSL0_POS 0
//! Field TTSL0 - Target Time Low for PPS Register
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_TTSL0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H Register GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H - GMACF MAC PPS0 Target Time Nanoseconds high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H 0x170C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H 0x00D3170Cu

//! Register Reset Value
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_RST 0x00000000u

//! Field TTSL0 - Target Time Low for PPS Register
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TTSL0_POS 0
//! Field TTSL0 - Target Time Low for PPS Register
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TTSL0_MASK 0x7FFFu

//! Field TRGTBUSY0 - PPS Target Time Register Busy
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TRGTBUSY0_POS 15
//! Field TRGTBUSY0 - PPS Target Time Register Busy
#define GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TRGTBUSY0_MASK 0x8000u

//! @}

//! \defgroup GMACF_MAC_PPS0_INTERVAL_L Register GMACF_MAC_PPS0_INTERVAL_L - GMACF MAC PPS0 Interval low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_INTERVAL_L 0x1710
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_INTERVAL_L 0x00D31710u

//! Register Reset Value
#define GMACF_MAC_PPS0_INTERVAL_L_RST 0x00000000u

//! Field PPSINT0 - PPS Output Signal Interval
#define GMACF_MAC_PPS0_INTERVAL_L_PPSINT0_POS 0
//! Field PPSINT0 - PPS Output Signal Interval
#define GMACF_MAC_PPS0_INTERVAL_L_PPSINT0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_INTERVAL_H Register GMACF_MAC_PPS0_INTERVAL_H - GMACF MAC PPS0 Interval high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_INTERVAL_H 0x1714
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_INTERVAL_H 0x00D31714u

//! Register Reset Value
#define GMACF_MAC_PPS0_INTERVAL_H_RST 0x00000000u

//! Field PPSINT0 - PPS Output Signal Interval
#define GMACF_MAC_PPS0_INTERVAL_H_PPSINT0_POS 0
//! Field PPSINT0 - PPS Output Signal Interval
#define GMACF_MAC_PPS0_INTERVAL_H_PPSINT0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_WIDTH_L Register GMACF_MAC_PPS0_WIDTH_L - GMACF MAC PPS0 Width low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_WIDTH_L 0x1718
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_WIDTH_L 0x00D31718u

//! Register Reset Value
#define GMACF_MAC_PPS0_WIDTH_L_RST 0x00000000u

//! Field PPSWIDTH0 - PPS Output Signal Width
#define GMACF_MAC_PPS0_WIDTH_L_PPSWIDTH0_POS 0
//! Field PPSWIDTH0 - PPS Output Signal Width
#define GMACF_MAC_PPS0_WIDTH_L_PPSWIDTH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PPS0_WIDTH_H Register GMACF_MAC_PPS0_WIDTH_H - GMACF MAC PPS0 Width high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PPS0_WIDTH_H 0x171C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PPS0_WIDTH_H 0x00D3171Cu

//! Register Reset Value
#define GMACF_MAC_PPS0_WIDTH_H_RST 0x00000000u

//! Field PPSWIDTH0 - PPS Output Signal Width
#define GMACF_MAC_PPS0_WIDTH_H_PPSWIDTH0_POS 0
//! Field PPSWIDTH0 - PPS Output Signal Width
#define GMACF_MAC_PPS0_WIDTH_H_PPSWIDTH0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_PTO_CONTROL_L Register GMACF_MAC_PTO_CONTROL_L - GMACF MAC PTO Control low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PTO_CONTROL_L 0x1780
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PTO_CONTROL_L 0x00D31780u

//! Register Reset Value
#define GMACF_MAC_PTO_CONTROL_L_RST 0x00000000u

//! Field PTOEN - PTP Offload Enable
#define GMACF_MAC_PTO_CONTROL_L_PTOEN_POS 0
//! Field PTOEN - PTP Offload Enable
#define GMACF_MAC_PTO_CONTROL_L_PTOEN_MASK 0x1u

//! Field ASYNCEN - Automatic PTP SYNC message Enable
#define GMACF_MAC_PTO_CONTROL_L_ASYNCEN_POS 1
//! Field ASYNCEN - Automatic PTP SYNC message Enable
#define GMACF_MAC_PTO_CONTROL_L_ASYNCEN_MASK 0x2u

//! Field APDREQEN - Automatic PTP Pdelay_Req message Enable
#define GMACF_MAC_PTO_CONTROL_L_APDREQEN_POS 2
//! Field APDREQEN - Automatic PTP Pdelay_Req message Enable
#define GMACF_MAC_PTO_CONTROL_L_APDREQEN_MASK 0x4u

//! Field RESERVED_3 - Reserved.
#define GMACF_MAC_PTO_CONTROL_L_RESERVED_3_POS 3
//! Field RESERVED_3 - Reserved.
#define GMACF_MAC_PTO_CONTROL_L_RESERVED_3_MASK 0x8u

//! Field ASYNCTRIG - Automatic PTP SYNC message Trigger
#define GMACF_MAC_PTO_CONTROL_L_ASYNCTRIG_POS 4
//! Field ASYNCTRIG - Automatic PTP SYNC message Trigger
#define GMACF_MAC_PTO_CONTROL_L_ASYNCTRIG_MASK 0x10u

//! Field APDREQTRIG - Automatic PTP Pdelay_Req message Trigger
#define GMACF_MAC_PTO_CONTROL_L_APDREQTRIG_POS 5
//! Field APDREQTRIG - Automatic PTP Pdelay_Req message Trigger
#define GMACF_MAC_PTO_CONTROL_L_APDREQTRIG_MASK 0x20u

//! Field DRRDIS - Disable PTO Delay Request/Response response generation
#define GMACF_MAC_PTO_CONTROL_L_DRRDIS_POS 6
//! Field DRRDIS - Disable PTO Delay Request/Response response generation
#define GMACF_MAC_PTO_CONTROL_L_DRRDIS_MASK 0x40u

//! Field PDRDIS - Disable Peer Delay Response response generation
#define GMACF_MAC_PTO_CONTROL_L_PDRDIS_POS 7
//! Field PDRDIS - Disable Peer Delay Response response generation
#define GMACF_MAC_PTO_CONTROL_L_PDRDIS_MASK 0x80u

//! Field DN - Domain Number
#define GMACF_MAC_PTO_CONTROL_L_DN_POS 8
//! Field DN - Domain Number
#define GMACF_MAC_PTO_CONTROL_L_DN_MASK 0xFF00u

//! @}

//! \defgroup GMACF_MAC_PTO_CONTROL_H Register GMACF_MAC_PTO_CONTROL_H - GMACF MAC PTO Control high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_PTO_CONTROL_H 0x1784
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_PTO_CONTROL_H 0x00D31784u

//! Register Reset Value
#define GMACF_MAC_PTO_CONTROL_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_PTO_CONTROL_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_PTO_CONTROL_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY0_L Register GMACF_MAC_SOURCE_PORT_IDENTITY0_L - GMACF MAC Source Port Identity0 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_L 0x1788
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY0_L 0x00D31788u

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_L_RST 0x00000000u

//! Field SPI0 - Source Port Identity 0
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_L_SPI0_POS 0
//! Field SPI0 - Source Port Identity 0
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_L_SPI0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY0_H Register GMACF_MAC_SOURCE_PORT_IDENTITY0_H - GMACF MAC Source Port Identity0 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_H 0x178C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY0_H 0x00D3178Cu

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_H_RST 0x00000000u

//! Field SPI0 - Source Port Identity 0
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_H_SPI0_POS 0
//! Field SPI0 - Source Port Identity 0
#define GMACF_MAC_SOURCE_PORT_IDENTITY0_H_SPI0_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY1_L Register GMACF_MAC_SOURCE_PORT_IDENTITY1_L - GMACF MAC Source Port Identity1 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_L 0x1790
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY1_L 0x00D31790u

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_L_RST 0x00000000u

//! Field SPI1 - Source Port Identity 1
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_L_SPI1_POS 0
//! Field SPI1 - Source Port Identity 1
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_L_SPI1_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY1_H Register GMACF_MAC_SOURCE_PORT_IDENTITY1_H - GMACF MAC Source Port Identity1 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_H 0x1794
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY1_H 0x00D31794u

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_H_RST 0x00000000u

//! Field SPI1 - Source Port Identity 1
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_H_SPI1_POS 0
//! Field SPI1 - Source Port Identity 1
#define GMACF_MAC_SOURCE_PORT_IDENTITY1_H_SPI1_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY2_L Register GMACF_MAC_SOURCE_PORT_IDENTITY2_L - GMACF MAC Source Port Identity2 low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_L 0x1798
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY2_L 0x00D31798u

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_L_RST 0x00000000u

//! Field SPI2 - Source Port Identity 2
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_L_SPI2_POS 0
//! Field SPI2 - Source Port Identity 2
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_L_SPI2_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_SOURCE_PORT_IDENTITY2_H Register GMACF_MAC_SOURCE_PORT_IDENTITY2_H - GMACF MAC Source Port Identity2 high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_H 0x179C
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_SOURCE_PORT_IDENTITY2_H 0x00D3179Cu

//! Register Reset Value
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_H_RST 0x00000000u

//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_H_RESERVED_31_16_POS 0
//! Field RESERVED_31_16 - Reserved.
#define GMACF_MAC_SOURCE_PORT_IDENTITY2_H_RESERVED_31_16_MASK 0xFFFFu

//! @}

//! \defgroup GMACF_MAC_LOG_MESSAGE_INTERVAL_L Register GMACF_MAC_LOG_MESSAGE_INTERVAL_L - GMACF MAC Log Message Interval low word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L 0x17A0
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LOG_MESSAGE_INTERVAL_L 0x00D317A0u

//! Register Reset Value
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_RST 0x00000000u

//! Field LSI - Log Sync Interval
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_LSI_POS 0
//! Field LSI - Log Sync Interval
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_LSI_MASK 0xFFu

//! Field DRSYNCR - Delay_Req to SYNC Ratio
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_DRSYNCR_POS 8
//! Field DRSYNCR - Delay_Req to SYNC Ratio
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_DRSYNCR_MASK 0x700u

//! Field RESERVED_23_11 - Reserved.
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_RESERVED_23_11_POS 11
//! Field RESERVED_23_11 - Reserved.
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_L_RESERVED_23_11_MASK 0xF800u

//! @}

//! \defgroup GMACF_MAC_LOG_MESSAGE_INTERVAL_H Register GMACF_MAC_LOG_MESSAGE_INTERVAL_H - GMACF MAC Log Message Interval high word
//! @{

//! Register Offset (relative)
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H 0x17A4
//! Register Offset (absolute) for 1st Instance GMACF_EQOS_MAC
#define GMACF_EQOS_MAC_GMACF_MAC_LOG_MESSAGE_INTERVAL_H 0x00D317A4u

//! Register Reset Value
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H_RST 0x00000000u

//! Field RESERVED_23_11 - Reserved.
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H_RESERVED_23_11_POS 0
//! Field RESERVED_23_11 - Reserved.
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H_RESERVED_23_11_MASK 0xFFu

//! Field LMPDRI - Log Min Pdelay_Req Interval
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H_LMPDRI_POS 8
//! Field LMPDRI - Log Min Pdelay_Req Interval
#define GMACF_MAC_LOG_MESSAGE_INTERVAL_H_LMPDRI_MASK 0xFF00u

//! @}

//! @}

#endif
