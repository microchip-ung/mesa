// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_ANA_ACL_H_
#define _VTSS_SERVALT_REGS_ANA_ACL_H_


#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a ANA_ACL
 *
 * Access Control List sub block of the Analyzer
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_ACL:PORT
 *
 * VCAP_IS2 configuration per port
 */


/** 
 * \brief VCAP_IS2 key selection
 *
 * \details
 * Key selection for VCAP_IS2 lookups. Replicated per lookup.
 *
 * Register: \a ANA_ACL:PORT:VCAP_S2_KEY_SEL
 *
 * @param gi Replicator: x_FFL_CHIP_NUM_INB_PORTS (??), 0-14
 * @param ri Register: VCAP_S2_KEY_SEL (??), 0-1
 */
#define VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x400,gi,3,ri,0)

/** 
 * \brief
 * Applies to frames where frame_type is set to non Ethernet (CW or MPLS).
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: match against CUSTOM_1 entries.
 * 2: match against CUSTOM_2 entries.
 * 3: No lookup.
 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . NON_ETH_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_NON_ETH_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_NON_ETH_KEY_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_NON_ETH_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Applies to IPv4 multicast frames.
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP4_TCP_UDP for IPv4 TCP/UDP frames and against
 * IP4_OTHER entries for other IPv4 frames.
 * 2: Match against IP_7TUPLE entries.
 * 3: Match against IP4_VID entries.

 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . IP4_MC_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_MC_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Applies to IPv4 unicast frames.
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP4_TCP_UDP for IPv4 TCP/UDP frames and against
 * IP4_OTHER entries for other IPv4 frames.
 * 2: Match against IP_7TUPLE entries.

 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . IP4_UC_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP4_UC_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Applies to IPv6 multicast frames.
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP_7TUPLE entries.
 * 2: Match against IP6_VID entries.

 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . IP6_MC_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_MC_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Applies to IPv6 unicast frames.
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against IP_7TUPLE entries.

 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . IP6_UC_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL  VTSS_BIT(1)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_IP6_UC_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Applies to ARP/RARP frames.
 *
 * \details 
 * 0: Match against MAC_ETYPE entries.
 * 1: Match against ARP entries.

 *
 * Field: ::VTSS_ANA_ACL_PORT_VCAP_S2_KEY_SEL . ARP_KEY_SEL
 */
#define  VTSS_F_ANA_ACL_PORT_VCAP_S2_KEY_SEL_ARP_KEY_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_PORT_VCAP_S2_KEY_SEL_ARP_KEY_SEL  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_PORT_VCAP_S2_KEY_SEL_ARP_KEY_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PTP port configuration
 *
 * \details
 * Clock domain selection and mapping of ingress port number.
 *
 * Register: \a ANA_ACL:PORT:PTP_CFG
 *
 * @param gi Replicator: x_FFL_CHIP_NUM_INB_PORTS (??), 0-14
 */
#define VTSS_ANA_ACL_PORT_PTP_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x400,gi,3,0,2)

/** 
 * \brief
 * Part of portNumber used in portIdentity when
 * ANA_ACL:PTP_DOM:PTP_SRC_PORT_CFG.PORT_NUM_SEL is set. PTP_PORT_NUM
 * specifies bits 5:0 in portNumber. Remaining bits 15:6 in portNumber are
 * taken from ANA_ACL:PTP_DOM:PTP_SRC_PORT_CFG.PORT_NUM
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PORT_PTP_CFG . PTP_PORT_NUM
 */
#define  VTSS_F_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Selects the PTP time domain to use when updating receiveTimestamp in
 * Delay_Resp frames.
 *
 * \details 
 * 0: Use time domain 0
 * 1: Use time domain 1
 * 2: Use time domain 2
 * 3: Reserved.
 *
 * Field: ::VTSS_ANA_ACL_PORT_PTP_CFG . PTP_DOMAIN
 */
#define  VTSS_F_ANA_ACL_PORT_PTP_CFG_PTP_DOMAIN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_ACL_PORT_PTP_CFG_PTP_DOMAIN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_ACL_PORT_PTP_CFG_PTP_DOMAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a ANA_ACL:VCAP_S2
 *
 * Common configurations used by VCAP_IS2
 */


/** 
 * \brief VCAP S2 configuration
 *
 * \details
 * Configuration of advanced classification per port.
 * 
 * For the 2-bit fields of this register the following applies:
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2
 *
 * Register: \a ANA_ACL:VCAP_S2:VCAP_S2_CFG
 *
 * @param ri Replicator: x_FFL_CHIP_NUM_INB_PORTS (??), 0-14
 */
#define VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_ACL,0x42d + (ri))

/** 
 * \brief
 * For frames to be routed, enable/disable the use of IRLEG VID and ERLEG
 * VID as the value for the VID field in the VCAP_IS2 keys. First VCAP_IS2
 * lookup uses IRLEG VID, second lookup uses ERLEG VID.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_ROUTE_HANDLING_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ROUTE_HANDLING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ROUTE_HANDLING_ENA  VTSS_BIT(26)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ROUTE_HANDLING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * For OAM frames (with up to three VLAN tags), enable matching against
 * control entries of type OAM in VCAP_IS2. Otherwise, OAM frames are
 * matched against control entries of type MAC_ETYPE.
 * 
 * OAM frames are identified by the following EtherType values:
 * 0x8902 - ITU-T Y.1731
 * 0x8809 - Link Level OAM 
 * 0x88EE - MEF-16 (E-LMI)
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_OAM_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_OAM_ENA(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_OAM_ENA     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_OAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * For IPv6 frames, enable matching against control entries of types
 * IP4_TCP_UDP and IP4_OTHER in VCAP_IS2.
 * 
 * The SIP and DIP fields of IP4_TCP_UDP and IP4_OTHER control entries are
 * used to match against bits 63:0 of IPv6 SIP.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable the classification.
 * 1: Enable the classification.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP6_TCPUDP_OTHER_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_OTHER_ENA(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_OTHER_ENA     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_OTHER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * For IPv6 multicast frames, enable matching against control entries of
 * type IP6_VID in VCAP_IS2. Otherwise, IPv6 multicast frames are handled
 * as either IPv6 TCP/UDP frames or IPv6 Other frames, see
 * SEC_TYPE_IP6_TCPUDP_ENA and SEC_TYPE_IP6_OTHER_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP6_VID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_VID_ENA(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_VID_ENA     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_VID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * For IPv6 frames, enable matching against control entries of type IP6_STD
 * in VCAP_IS2. Otherwise, IPv6 frames are handled as IPv4 frames, see
 * SEC_TYPE_IP6_TCPUDP_OTHER_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP6_STD_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_STD_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_STD_ENA     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_STD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * For IPv6 TCP/UDP frames, enable matching against control entries of type
 * IP6_TCP_UDP in VCAP_IS2. Otherwise, IPv6 TCP/UDP frames are handled as
 * IPv6 standard frames, SEC_TYPE_IP6_STD_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP6_TCPUDP_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_ENA(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_ENA     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_TCPUDP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * For IPv6 frames, enable matching against control entries of type
 * IP6_OTHER in VCAP_IS2. Otherwise, IPv6 Other frames are handled as IPv6
 * standard frames, SEC_TYPE_IP6_STD_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP6_OTHER_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_OTHER_ENA(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_OTHER_ENA     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP6_OTHER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * For IPv4 multicast frames, enable matching against control entries of
 * type IP4_VID in VCAP_IS2. Otherwise, IPv4 multicast frames are handled
 * as either IPv4 TCP/UDP frames or IPv4 Other frames, see
 * SEC_TYPE_IP4_TCPUDP_ENA and SEC_TYPE_IP4_OTHER_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP4_VID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_VID_ENA(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_VID_ENA     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_VID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * For IPv4 TCP/UDP frames, enable matching against control entries of type
 * IP_TCP_UDP in VCAP_IS2. Otherwise, IPv4 TCP/UDP frames are handled as
 * IPv4 Other frames, see SEC_TYPE_IP4_OTHER_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP4_TCPUDP_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_TCPUDP_ENA(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_TCPUDP_ENA     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_TCPUDP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * For IPv4 frames, enable matching against control entries of type
 * IP4_OTHER in VCAP_IS2. Otherwise, IPv4 frames are matched against
 * control entries of type MAC_ETYPE.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_IP4_OTHER_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_OTHER_ENA(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_OTHER_ENA     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_IP4_OTHER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * For ARP frames (EtherType 0x0806), enable matching against control
 * entries of type ARP in VCAP_IS2. Otherwise, ARP frames are matched
 * against control entries of type MAC_ETYPE.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_ARP_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_ARP_ENA(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_ARP_ENA     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_ARP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * For SNAP frames, enable matching against control entries of type
 * MAC_SNAP in VCAP_IS2. Otherwise SNAP frames frames are handled as LLC
 * frames, see SEC_TYPE_MAC_LLC_ENA.
 * 
 * SNAP frames are identified by
 * * EtherType < 0x0600
 * * DSAP = 0xAA
 * * SSAP = 0xAA
 * * CTRL = 0x03
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_MAC_SNAP_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_SNAP_ENA(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_SNAP_ENA     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_SNAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * For LLC frames, enable matching against control entries of type MAC_LLC
 * in VCAP_IS2. Otherwise, LLC frames are matched against control entries
 * of type MAC_ETYPE.
 * 
 * LLC frames are identified as frames with EtherType < 0x0600 that are not
 * SNAP frames. Note that SNAP frames can be handled as LLC frames by
 * disabling SEC_TYPE_MAC_SNAP_ENA.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_TYPE_MAC_LLC_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_LLC_ENA(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_LLC_ENA     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_TYPE_MAC_LLC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enable/disable VCAP_IS2 lookups.
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2

 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_CFG . SEC_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ENA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_CFG_SEC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Source IP table used for multicast IP address swapping
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:SWAP_SIP
 *
 * @param ri Register: SWAP_SIP (??), 0-31
 */
#define VTSS_ANA_ACL_VCAP_S2_SWAP_SIP(ri)    VTSS_IOREG(VTSS_TO_ANA_ACL,0x43c + (ri))

/** 
 * \brief
 * New source IP address used when frame's IP addresses are swapped and the
 * original destination IP address was a multicast address. IP address
 * swapping is enabled in VCAP_IS2 action ACL_RT_MODE.
 * 
 * IPv4: Each entry configures one IPv4 address.
 * IPv6: Four consecutive entries configures one IPv6 address. Entries must
 * start at 4 x n, n=0, 1, ..., 7. First entry encodes bits 31:0 of IPv6
 * address, second entry encoded bits 63:32, and so on.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_SIP . SIP
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_SIP_SIP(x)  (x)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_SIP_SIP     0xffffffff
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_SIP_SIP(x)  (x)


/** 
 * \brief Configuration of various ACL PTP features
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:PTP_MISC_CTRL
 */
#define VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL   VTSS_IOREG(VTSS_TO_ANA_ACL,0x45c)

/** 
 * \brief
 * CPU extraction queue for PTP Delay_Resp frames redirected to the CPU.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_REDIR_QU
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_QU(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_QU     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_QU(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * If set, PTP Delay_resp frames expanded beyond one cell is redirected to
 * the CPU. If cleared, such frames are discarded.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_REDIR_TOO_BIG_REDIR
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_TOO_BIG_REDIR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_TOO_BIG_REDIR  VTSS_BIT(6)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REDIR_TOO_BIG_REDIR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * If set, logMessageInterval in multicast Delay_Resp frames is updated
 * with VCAP_S2 action: SWAP_MAC_ENA & DLB_OFFSET.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_REQ_MC_UPD_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_MC_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_MC_UPD_ENA  VTSS_BIT(5)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_MC_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Allow length of Delay_resp with requestingPortIdentity
 * 
 * If set, Delay_Req frames are made 10 bytes longer to include
 * requestingPortIdentity. Appropriate header lengths (PTP, UDP, IP) are
 * increased with 10 bytes. 
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_REQ_CHG_LEN_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_CHG_LEN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_CHG_LEN_ENA  VTSS_BIT(4)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_CHG_LEN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * IP6 PTP operation.
 *
 * \details 
 * 0: No IP6 PTP updates.
 * 1: IP6 PTP updates with UDP chksum updates.
 * 2: IP6 PTP updates with UDP chksum updates, redirect frame to CPU using
 * extraction queue PTP_DELAY_REDIR_QU.
 * 3: IP6 PTP updates with UDP chksum clear.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_IP6_SEL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_IP6_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_IP6_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_IP6_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Require received UDP length to be 44 before PTP_DELAY_REQ_CHG_LEN_ENA
 * takes action.
 *  
 * Frames with UDP len different from 44 are either discarded or optional
 * redirected by means of PTP_DELAY_REDIR_TOO_BIG_REDIR.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_DELAY_REQ_UDP_LEN52
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52  VTSS_BIT(1)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If set, and VCAP_IS2 action REW_CMD[5] is set, ANA_ACL rewrites
 * Delay_Req frames. The following PTP fields can be modified in ANA_ACL
 * depending on configuration in PTP_MISC_CTRL and ANA_ACL:PTP_DOM:
 * - messageType (set to Delay_Resp)
 * - messageLength
 * - flagField
 * - sourcePortIdentity
 * - controlField
 * - logMessageInterval
 * - receiveTimestamp
 * - requestingPortIdentity
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL . PTP_ALLOW_ACL_REW_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of various swap features
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:SWAP_IP_CTRL
 */
#define VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL    VTSS_IOREG(VTSS_TO_ANA_ACL,0x45d)

/** 
 * \brief
 * Number of bits in frame's DMAC counting from LSB which are not replaced
 * if replacing the DMAC (IS2 action ACL_RT_MODE) and reduced DMAC is
 * enabled (IS2 action SAM_SEQ_ENA). New DMAC is provided by IS2 action
 * ACL_MAC. 
 * For example, if set to 16, the 16 LSB bits in the frame's DMAC are not
 * replaced while the 32 MSB bits are replaced with corresponding 32 bits
 * from ACL_MAC.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL . DMAC_REPL_OFFSET_VAL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_DMAC_REPL_OFFSET_VAL(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * New hop count value when swapping IPv6 addresses.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL . IP_SWAP_IP6_HOPC_VAL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_VAL     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * New TTL value when swapping IPv4 addresses.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL . IP_SWAP_IP4_TTL_VAL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_VAL     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/** 
 * \brief
 * Replace hop count with value configured in IP_SWAP_IP6_HOPC_VAL when
 * swapping IPv6 addresses.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL . IP_SWAP_IP6_HOPC_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP6_HOPC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Replace TTL with value configured in IP_SWAP_IP4_TTL_VAL when swapping
 * IPv4 addresses.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_SWAP_IP_CTRL . IP_SWAP_IP4_TTL_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_VCAP_S2_SWAP_IP_CTRL_IP_SWAP_IP4_TTL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of various features
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:VCAP_S2_MISC_CTRL
 */
#define VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL  VTSS_IOREG(VTSS_TO_ANA_ACL,0x45e)

/** 
 * \brief
 * Controls if PAG(7) forces VID for service frames (ISDX > 0).
 * 
 * Bit[0]: Relates to first lookup in VCAP_IS2
 * Bit[1]: Relates to second lookup in VCAP_IS2
 *
 * \details 
 * 0: Disable 
 * 1: Force VID when isdx >0
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . PAG_FORCE_VID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_PAG_FORCE_VID_ENA(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_PAG_FORCE_VID_ENA     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_PAG_FORCE_VID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * If set, PIPELINE_PT is set to ANA_VLAN and PIPELINE_ACT is set to XTR if
 * the frame is discarded in ANA_L3.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . VLAN_PIPELINE_ACT_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VLAN_PIPELINE_ACT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VLAN_PIPELINE_ACT_ENA  VTSS_BIT(13)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VLAN_PIPELINE_ACT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Controls how to update routing statistics events for ingress ANA_ACL
 * actions.
 *
 * \details 
 * 0:
 * UC: If frame is dropped by VCAP_IS2 rule, then clear
 * ivmid_ip_uc_received (as if frame never reached the router)
 * MC: If frame is dropped by VCAP_IS2 rule, then leave
 * ivmid_ip_mc_received unchanged (as if frame may reach the router)
 * 1: If frame is dropped by VCAP_IS2 rule, then clear
 * ivmid_ip_uc_received/ivmid_ip_mc_received (as if frame never reached the
 * router, but was dropped in the L2 switch)
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_IGR_RLEG_STAT_MODE
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_IGR_RLEG_STAT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_IGR_RLEG_STAT_MODE  VTSS_BIT(12)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_IGR_RLEG_STAT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Controls how to update routing statistics events for egress ACL actions.
 *
 * \details 
 * 0: If routed frame is dropped by VCAP_IS2 rule, then clear
 * ivmid_ip_uc_received/ivmid_ip_mc_received (as if frame never left the
 * router)
 * 1: If routed frame is dropped by VCAP_IS2 rule, then leave
 * ivmid_ip_uc_received/ivmid_ip_mc_received set (as if frame did leave the
 * router and was dropped in the L2 switch)
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_EGR_RLEG_STAT_MODE
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_EGR_RLEG_STAT_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_EGR_RLEG_STAT_MODE  VTSS_BIT(11)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_EGR_RLEG_STAT_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * If set, force use of VID key type in VCAP_ES0 when routing in ANA_ACL.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_FORCE_ES0_VID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_FORCE_ES0_VID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_FORCE_ES0_VID_ENA  VTSS_BIT(10)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_FORCE_ES0_VID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * If set, classified VID is set to egress VID.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_UPDATE_CL_VID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_CL_VID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_CL_VID_ENA  VTSS_BIT(9)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_CL_VID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * If set, IFH.GEN_IDX is set to egress RLEG.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_UPDATE_GEN_IDX_ERLEG_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_ERLEG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_ERLEG_ENA  VTSS_BIT(8)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_ERLEG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If set, IFH.GEN_IDX is set to egress VID.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_UPDATE_GEN_IDX_EVID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_EVID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_EVID_ENA  VTSS_BIT(7)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_UPDATE_GEN_IDX_EVID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Controls routing related frame edits in ANA_ACL block.
 * 
 * By default, routing related frame edits are done in REW, but when
 * combining routing with PTP, ANA_ACL must be configured to change DMAC to
 * next-hop DMAC in order to allow other information to be stored in the
 * IFH.
 * 
 * ANA_ACL can rewrite the following routing related fields:
 * 1) Change DMAC to next-hop MAC address (as determined by ANA_L3).
 * 2) Set IFH.FWD.DST_MODE=ENCAP to prevent REW from doing routing related
 * frame editting.
 * 
 * Decrement of TTL/Hop limit is still performed by REW. 
 * 
 * When performing routing related frame edits in ANA_ACL, editing of SMAC
 * must be performed by ANA_L3 (ANA_L3::ROUTING_CFG.RT_SMAC_UPDATE_ENA).
 *
 * \details 
 * 0: Disable routing in ANA_ACL block.
 * 1: Enable routing related frame edits independently of VCAP_IS2 action
 * ACL_RT_MODE.
 * 2: Enable routing related frame edits if VCAP_IS2 action ACL_RT_MODE
 * allows routing.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . ACL_RT_SEL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_SEL     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_ACL_RT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Force VCAP_IS2 lookup to use IGR_PORT_MASK_SEL=3 for looped frames
 * instead of IGR_PORT_MASK_SEL=1.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . LBK_IGR_MASK_SEL3_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_LBK_IGR_MASK_SEL3_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_LBK_IGR_MASK_SEL3_ENA  VTSS_BIT(4)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_LBK_IGR_MASK_SEL3_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable VCAP_IS2 key field IGR_PORT_MASK_SEL=2 for masqueraded frames.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . MASQ_IGR_MASK_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_MASQ_IGR_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_MASQ_IGR_MASK_ENA  VTSS_BIT(3)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_MASQ_IGR_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable VCAP_IS2 key field IGR_PORT_MASK_SEL=3 for frames received with
 * VStaX header.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . FP_VS2_IGR_MASK_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_FP_VS2_IGR_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_FP_VS2_IGR_MASK_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_FP_VS2_IGR_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable VCAP_IS2 key field IGR_PORT_MASK_SEL=3 for frames from VD0 or
 * VD1.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . VD_IGR_MASK_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VD_IGR_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VD_IGR_MASK_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_VD_IGR_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable VCAP_IS2 key field IGR_PORT_MASK_SEL=3 for CPU injected frames.
 *
 * \details 
 * 0: Disable
 * 1: Enable.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL . CPU_IGR_MASK_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_CPU_IGR_MASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_CPU_IGR_MASK_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_MISC_CTRL_CPU_IGR_MASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of TCP range generation
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:VCAP_S2_RNG_CTRL
 *
 * @param ri Replicator: x_FFL_ANA_NUM_TCP_RANGES (??), 0-7
 */
#define VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_ACL,0x45f + (ri))

/** 
 * \brief
 * Selected field matched against the range
 *
 * \details 
 * 0: Idle (No match)
 * 1: TCP / UDP dport value is matched against range
 * 2: TCP / UDP sport value is matched against range
 * 3: TCP / UDP dport or sport values are matched against range
 * 4: Classified VIDvalue is matched against range
 * 5: Classified DSCP value is matched against range
 * 6: Selected value from frame is matched against range, see
 * ANA_ACL::VCAP_S2_RNG_OFFSET_CFG for details.
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL . RNG_TYPE_SEL
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL_RNG_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL_RNG_TYPE_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_RNG_CTRL_RNG_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Configuration of  matcher range generation
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:VCAP_S2_RNG_VALUE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_NUM_TCP_RANGES (??), 0-7
 */
#define VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_ACL,0x467 + (ri))

/** 
 * \brief
 * Upper range value
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG . RNG_MAX_VALUE
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MAX_VALUE(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MAX_VALUE     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MAX_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Lower range value
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG . RNG_MIN_VALUE
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MIN_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MIN_VALUE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_RNG_VALUE_CFG_RNG_MIN_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Configuration of selected range generation
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:VCAP_S2_RNG_OFFSET_CFG
 */
#define VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_OFFSET_CFG  VTSS_IOREG(VTSS_TO_ANA_ACL,0x46f)

/** 
 * \brief
 * 16-bit offset position of selectable range matcher input counting from
 * the EtherType (up to three VLAN tags skipped).
 *
 * \details 
 * 0: EtherType
 * 1: frame byte 0 and 1 after EtherType
 * ...
 * n: frame byte 2n-2 and 2n-1 after EtherType
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VCAP_S2_RNG_OFFSET_CFG . RNG_OFFSET_POS
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VCAP_S2_RNG_OFFSET_CFG_RNG_OFFSET_POS(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_ACL_VCAP_S2_VCAP_S2_RNG_OFFSET_CFG_RNG_OFFSET_POS     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_ACL_VCAP_S2_VCAP_S2_RNG_OFFSET_CFG_RNG_OFFSET_POS(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of how VOE loopback is performed
 *
 * \details
 * Register: \a ANA_ACL:VCAP_S2:VOE_LOOPBACK_CFG
 */
#define VTSS_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG  VTSS_IOREG(VTSS_TO_ANA_ACL,0x470)

/** 
 * \brief
 * Controls how loopback port is selected.
 *
 * \details 
 * 0: Loop to req.port_num
 * 1: Loop to logical port found in
 * ANA_AC:PGID[req.port_num+VOE_LOOP_PGID_OFFSET]
 *
 * Field: ::VTSS_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG . VOE_LOOP_PGID_ENA
 */
#define  VTSS_F_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG_VOE_LOOP_PGID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG_VOE_LOOP_PGID_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_VCAP_S2_VOE_LOOPBACK_CFG_VOE_LOOP_PGID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_ACL:STICKY
 *
 * Sticky diagnostic status
 */


/** 
 * \brief Sticky bits register for events generated by VCAP_IS2
 *
 * \details
 * Register: \a ANA_ACL:STICKY:SEC_LOOKUP_STICKY
 *
 * @param ri Register: SEC_LOOKUP_STICKY (??), 0-1
 */
#define VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY(ri)  VTSS_IOREG(VTSS_TO_ANA_ACL,0x471 + (ri))

/** 
 * \brief
 * This sticky bit signals a CUSTOM2 lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_CUSTOM2_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM2_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM2_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM2_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * This sticky bit signals a CUSTOM1 lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_CUSTOM1_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM1_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM1_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_CUSTOM1_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * This sticky bit signals OAM lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_OAM_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_OAM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_OAM_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_OAM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * This sticky bit signals an IP6_VID lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP6_VID_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY  VTSS_BIT(10)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_VID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * This sticky bit signals IP6_STD lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP6_STD_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_STD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * This sticky bit signals IP6_TCPUDP lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP6_TCPUDP_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_TCPUDP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_TCPUDP_STICKY  VTSS_BIT(8)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP6_TCPUDP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * This sticky bit signals an IP_7TUPLE lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP_7TUPLE_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY  VTSS_BIT(7)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP_7TUPLE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * This sticky bit signals an IP4_VID lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_VID_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_VID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * This sticky bit signals an IP4_TCPUDP lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_TCPUDP_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_TCPUDP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * This sticky bit signals an IP4_OTHER lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_IP4_OTHER_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_IP4_OTHER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * This sticky bit signals an ARP lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_ARP_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_ARP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * This sticky bit signals MAC_SNAP lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_MAC_SNAP_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_SNAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_SNAP_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_SNAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This sticky bit signals MAC_LLC lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_MAC_LLC_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_LLC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_LLC_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_LLC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This sticky bit signals a MAC_ETYPE lookup was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_STICKY_SEC_LOOKUP_STICKY . SEC_TYPE_MAC_ETYPE_STICKY
 */
#define  VTSS_F_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_ACL_STICKY_SEC_LOOKUP_STICKY_SEC_TYPE_MAC_ETYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_ACL:CNT_TBL
 *
 * VCAP_IS2 counter table
 */


/** 
 * \brief VCAP_IS2 counter
 *
 * \details
 * The CNT_TBL counters count number of hits in VCAP_IS2. For each of the
 * two VCAP_IS2 lookups, a VCAP match results in the associated counter
 * being incremented using the VCAP_IS2 action CNT_ID as index.
 *
 * Register: \a ANA_ACL:CNT_TBL:CNT
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ACL_CNT (??), 0-1023
 */
#define VTSS_ANA_ACL_CNT_TBL_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x0,gi,1,0,0)

/** 
 * \brief
 * VCAP_IS2 counter value.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_CNT_TBL_CNT . CNT
 */
#define  VTSS_F_ANA_ACL_CNT_TBL_CNT_CNT(x)    (x)
#define  VTSS_M_ANA_ACL_CNT_TBL_CNT_CNT       0xffffffff
#define  VTSS_X_ANA_ACL_CNT_TBL_CNT_CNT(x)    (x)

/**
 * Register Group: \a ANA_ACL:PTP_DOM
 *
 * PTP domain configuration
 */


/** 
 * \brief PTP clock identifier MSB
 *
 * \details
 * Register: \a ANA_ACL:PTP_DOM:PTP_CLOCK_ID_MSB
 *
 * @param gi Register: PTP_DOM (??), 0-2
 */
#define VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x473,gi,4,0,0)

/** 
 * \brief
 * Bits 63:32 of clockIdentifier used in portIdentity.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB . CLOCK_ID_MSB
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(x)  (x)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB     0xffffffff
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(x)  (x)


/** 
 * \brief PTP clock identifier LSB
 *
 * \details
 * Register: \a ANA_ACL:PTP_DOM:PTP_CLOCK_ID_LSB
 *
 * @param gi Register: PTP_DOM (??), 0-2
 */
#define VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x473,gi,4,0,1)

/** 
 * \brief
 * Bits 31:0 of clockIdentifier used in portIdentity.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB . CLOCK_ID_LSB
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(x)  (x)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB     0xffffffff
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(x)  (x)


/** 
 * \brief PTP domain configuration used in sourcePortIdentity
 *
 * \details
 * Register: \a ANA_ACL:PTP_DOM:PTP_SRC_PORT_CFG
 *
 * @param gi Register: PTP_DOM (??), 0-2
 */
#define VTSS_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x473,gi,4,0,2)

/** 
 * \brief
 * If set, lowest 6 bits in portIdentity is taken from
 * ANA_ACL:PORT:PTP_CFG.PTP_PORT_NUM. Otherwise, portIdentity is taken from
 * PTP_SRC_PORT_CFG.PORT_NUM.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG . PORT_NUM_SEL
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM_SEL  VTSS_BIT(16)
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Port number used in portIdentity.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG . PORT_NUM
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Miscellaneous PTP domain configuration
 *
 * \details
 * Register: \a ANA_ACL:PTP_DOM:PTP_MISC_CFG
 *
 * @param gi Register: PTP_DOM (??), 0-2
 */
#define VTSS_ANA_ACL_PTP_DOM_PTP_MISC_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_ACL,0x473,gi,4,0,3)

/** 
 * \brief
 * Mask used to configure which bits in flagField, byte 0, are overwriteen
 * with value configured in PTP_MISC_CFG.FLAG_FIELD.
 *
 * \details 
 * Bit x=0: Do not overwrite bit x in flagField, byte 0.
 * Bit x=1: Overwrite bit x in flagField, byte 0, with FLAG_FIELD, bit x.
 *
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_MISC_CFG . FLAG_FIELD_MASK
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD_MASK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * New values for byte 0 in flagField. Only bits with the corresponding
 * bits set in FLAG_FIELD_MASK, are used.
 *
 * \details 
 * Field: ::VTSS_ANA_ACL_PTP_DOM_PTP_MISC_CFG . FLAG_FIELD
 */
#define  VTSS_F_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_SERVALT_REGS_ANA_ACL_H_ */
