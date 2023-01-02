// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_ANA_L3_H_
#define _VTSS_LAGUNA_REGS_ANA_L3_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a ANA_L3
 *
 * ANA_L3 provides the following functionality:
 * - VLAN handling
 * - MSTP handling
 * - IP routing
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_L3:COMMON
 *
 * Common configurations for all ports
 */


/**
 * \brief Miscellaneous control parameters
 *
 * \details
 * Register: \a ANA_L3:COMMON:MISC_CTRL
 */
#define VTSS_ANA_L3_MISC_CTRL                VTSS_IOREG(VTSS_TO_ANA_L3,0x10a10)

/**
 * \brief
 * Enable update of AC for routed frames.
 *
 * \details
 * Field: ::VTSS_ANA_L3_MISC_CTRL . AC_UPDATE_ENA
 */
#define  VTSS_F_ANA_L3_MISC_CTRL_AC_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_MISC_CTRL_AC_UPDATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_MISC_CTRL_AC_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VLAN Control
 *
 * \details
 * Basic VLAN related configuration
 *
 * Register: \a ANA_L3:COMMON:VLAN_CTRL
 */
#define VTSS_ANA_L3_VLAN_CTRL                VTSS_IOREG(VTSS_TO_ANA_L3,0x10a11)

/**
 * \brief
 * Enable/disable VLAN lookup. This field must be enabled to allow VLAN and
 * MSTP filtering. For VLAN unaware operation, this field can be
 * disabled.VLAN lookup is also required when using routing.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CTRL . VLAN_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CTRL_VLAN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_VLAN_CTRL_VLAN_ENA     VTSS_BIT(0)
#define  VTSS_X_ANA_L3_VLAN_CTRL_VLAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Unicast routing control configuration
 *
 * \details
 * Enable of L3 unicast traffic per port.
 *
 * Register: \a ANA_L3:COMMON:L3_UC_ENA
 */
#define VTSS_ANA_L3_L3_UC_ENA                VTSS_IOREG(VTSS_TO_ANA_L3,0x10a12)

/**
 * \brief
 * Enable unicast routing per port.If disabled, IP unicast frames received
 * on the port will not be routed.If disabled and L3_ENA_MODE=1, then
 * routed IP unicast frames will not be transmitted on the port.Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.L3_ENA_MODE.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_UC_ENA . L3_UC_ENA
 */
#define  VTSS_F_ANA_L3_L3_UC_ENA_L3_UC_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_L3_UC_ENA_L3_UC_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_L3_UC_ENA_L3_UC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Multicast routing control configuration
 *
 * \details
 * IP multicast traffic enable per port
 *
 * Register: \a ANA_L3:COMMON:L3_MC_ENA
 */
#define VTSS_ANA_L3_L3_MC_ENA                VTSS_IOREG(VTSS_TO_ANA_L3,0x10a15)

/**
 * \brief
 * Enable multicast routing per port.If disabled, IP multicast frames
 * received on the port will not be routed.If disabled and L3_ENA_MODE=1,
 * then routed IP multicast frames will not be transmitted on the
 * port.Related parameters:ANA_L3:COMMON:ROUTING_CFG.L3_ENA_MODE.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_MC_ENA . L3_MC_ENA
 */
#define  VTSS_F_ANA_L3_L3_MC_ENA_L3_MC_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_L3_MC_ENA_L3_MC_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_L3_MC_ENA_L3_MC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Skip checking of DMAC to determine router leg hit.
 *
 * \details
 * Disable DMAC checking per port.
 *
 * Register: \a ANA_L3:COMMON:SKIP_RLEG_DMAC_CHK
 */
#define VTSS_ANA_L3_SKIP_RLEG_DMAC_CHK       VTSS_IOREG(VTSS_TO_ANA_L3,0x10a18)

/**
 * \brief
 * Skip checking frame's DMAC when determining whether frame has hit a
 * router leg.One bit per port.
 *
 * \details
 * 0: Normal router leg DMAC check.
 * 1: Skip router leg DMAC check.
 *
 * Field: ::VTSS_ANA_L3_SKIP_RLEG_DMAC_CHK . SKIP_RLEG_DMAC_CHK
 */
#define  VTSS_F_ANA_L3_SKIP_RLEG_DMAC_CHK_SKIP_RLEG_DMAC_CHK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_SKIP_RLEG_DMAC_CHK_SKIP_RLEG_DMAC_CHK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_SKIP_RLEG_DMAC_CHK_SKIP_RLEG_DMAC_CHK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Forwarding Control
 *
 * \details
 * Configuration of forwarding state per port
 *
 * Register: \a ANA_L3:COMMON:PORT_FWD_CTRL
 */
#define VTSS_ANA_L3_PORT_FWD_CTRL            VTSS_IOREG(VTSS_TO_ANA_L3,0x10a1b)

/**
 * \brief
 * Enable forwarding per physical port.If disabled, frames received on port
 * are discarded and frames are not forwarded to the port.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.PORT_FWD_DENY_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_PORT_FWD_CTRL . PORT_FWD_ENA
 */
#define  VTSS_F_ANA_L3_PORT_FWD_CTRL_PORT_FWD_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_PORT_FWD_CTRL_PORT_FWD_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_PORT_FWD_CTRL_PORT_FWD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Learning Control
 *
 * \details
 * Configuration of learning state per port
 *
 * Register: \a ANA_L3:COMMON:PORT_LRN_CTRL
 */
#define VTSS_ANA_L3_PORT_LRN_CTRL            VTSS_IOREG(VTSS_TO_ANA_L3,0x10a1e)

/**
 * \brief
 * Enable/disable learning per physical port.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.PORT_LRN_DENY_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_PORT_LRN_CTRL . PORT_LRN_ENA
 */
#define  VTSS_F_ANA_L3_PORT_LRN_CTRL_PORT_LRN_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_PORT_LRN_CTRL_PORT_LRN_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_PORT_LRN_CTRL_PORT_LRN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief VLAN Filter Control
 *
 * \details
 * Configuration of VLAN ingress filtering per port
 *
 * Register: \a ANA_L3:COMMON:VLAN_FILTER_CTRL
 */
#define VTSS_ANA_L3_VLAN_FILTER_CTRL         VTSS_IOREG(VTSS_TO_ANA_L3,0x10a21)

/**
 * \brief
 * Enable VLAN ingress filtering per port. If a port is enabled in this
 * mask, frames received on the port are discarded if the port is not a
 * member of the classified VLAN.VLAN ingress filtering can also be enabled
 * per VLAN.VLAN ingress filtering is performed if either enabled for
 * ingress port or for VLAN.Related
 * parameters:ANA_L3:VLAN:VLAN_CFG.VLAN_IGR_FILTER_ENAANA_L3:VLAN_ARP_L3MC_
 * STICKY:VLAN_STICKY.VLAN_IGR_FILTER_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_FILTER_CTRL . VLAN_IGR_FILTER_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_FILTER_CTRL_VLAN_IGR_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_VLAN_FILTER_CTRL_VLAN_IGR_FILTER_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_VLAN_FILTER_CTRL_VLAN_IGR_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief VLAN isolated port mask
 *
 * \details
 * Configuration of isolated port mask. See description of
 * ANA_L3:VLAN:VLAN_CFG.VLAN_PRIVATE_ENA
 *
 * Register: \a ANA_L3:COMMON:VLAN_ISOLATED_CFG
 */
#define VTSS_ANA_L3_VLAN_ISOLATED_CFG        VTSS_IOREG(VTSS_TO_ANA_L3,0x10a24)

/**
 * \brief
 * Ports marked in this mask are treated as isolated ports, if the VLAN is
 * a private VLAN.Ref. ANA_L3:VLAN:VLAN_CFG.VLAN_PRIVATE_ENA
 *
 * \details
 * 0: Not an Isolated port (i.e. Promiscuous port or Community port)
 * 1: Isolated port.
 *
 * Field: ::VTSS_ANA_L3_VLAN_ISOLATED_CFG . VLAN_ISOLATED_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_ISOLATED_CFG_VLAN_ISOLATED_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_VLAN_ISOLATED_CFG_VLAN_ISOLATED_MASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_VLAN_ISOLATED_CFG_VLAN_ISOLATED_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief VLAN Community port mask
 *
 * \details
 * Configuration of Community port mask. See description of
 * ANA_L3:VLAN:VLAN_CFG.VLAN_PRIVATE_ENA
 *
 * Register: \a ANA_L3:COMMON:VLAN_COMMUNITY_CFG
 */
#define VTSS_ANA_L3_VLAN_COMMUNITY_CFG       VTSS_IOREG(VTSS_TO_ANA_L3,0x10a27)

/**
 * \brief
 * Ports marked in this mask are treated as community ports, if the VLAN is
 * a private VLAN.Ref. ANA_L3:VLAN:VLAN_CFG.VLAN_PRIVATE_ENA
 *
 * \details
 * 0: Not a Community port (i.e. Promiscuous port or Isolated port)
 * 1: Community port.
 *
 * Field: ::VTSS_ANA_L3_VLAN_COMMUNITY_CFG . VLAN_COMMUNITY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_COMMUNITY_CFG_VLAN_COMMUNITY_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_VLAN_COMMUNITY_CFG_VLAN_COMMUNITY_MASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_VLAN_COMMUNITY_CFG_VLAN_COMMUNITY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Routing Configuration
 *
 * \details
 * Configuration of routing checks.
 * Note that these checks only applies to frames matching a router leg.
 *
 * Register: \a ANA_L3:COMMON:ROUTING_CFG
 */
#define VTSS_ANA_L3_ROUTING_CFG              VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2a)

/**
 * \brief
 * Controls whether L3_UC_ENA and L3_MC_ENA affects ingress or
 * ingress+egress behavior.Note that L3_ENA_MODE=1 does not work together
 * with stacking, assuming routing is performed by ingress unit.Related
 * parameters:ANA_L3:COMMON:L3_UC_ENAANA_L3:COMMON:L3_MC_ENA
 *
 * \details
 * 0: L3_UC_ENA/L3_MC_ENA is only applied on ingress.
 * 1: L3_UC_ENA/L3_MC_ENA is applied on ingress and egress.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . L3_ENA_MODE
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_L3_ENA_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_L3_ENA_MODE  VTSS_BIT(30)
#define  VTSS_X_ANA_L3_ROUTING_CFG_L3_ENA_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Route IPv6 multicast frames based on DIP only.I.e. do LPM lookup with
 * only DIP as key.When IP6_MC_DIP_FWD_ENA is not set LPM lookup is
 * performed with DIP+SIP as key.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_MC_DIP_FWD_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_MC_DIP_FWD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_MC_DIP_FWD_ENA  VTSS_BIT(29)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_MC_DIP_FWD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Route IPv4 multicast frames based on DIP only.I.e. do LPM lookup with
 * only DIP as key.When IP4_MC_DIP_FWD_ENA is not set LPM lookup is
 * performed with DIP+SIP as key.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_MC_DIP_FWD_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_MC_DIP_FWD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_MC_DIP_FWD_ENA  VTSS_BIT(28)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_MC_DIP_FWD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Change SMAC of routed frame to the SMAC of egress router leg.Normally
 * SMAC is changed in REW, but if routing and PTP is to be supported
 * concurrently, then RT_SMAC_UPDATE_ENA must be set.When
 * RT_SMAC_UPDATE_ENA is set and ingress mirroring is used, then ingress
 * mirrored frames get SMAC and DMAC values corresponding to the routed
 * frame.Related parameters:ANA_ACL::VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . RT_SMAC_UPDATE_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_RT_SMAC_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_RT_SMAC_UPDATE_ENA  VTSS_BIT(27)
#define  VTSS_X_ANA_L3_ROUTING_CFG_RT_SMAC_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Control which non-IP unicast frames, matching router leg's MAC address,
 * that shall be redirected to CPU.CPU queue is configured in
 * CPU_QU_CFG.CPU_RLEG_QU.
 *
 * \details
 * 0: Redirect all frames.
 * 1: Redirect ARP frames (Ethertype 0x0806)
 * 2: Redirect RARP frames (Ethertype 0x8035)
 * 3: Redirect ARP and RARP frames.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . RLEG_NONIP_UC_REDIR_MODE
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_RLEG_NONIP_UC_REDIR_MODE(x)  VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_ANA_L3_ROUTING_CFG_RLEG_NONIP_UC_REDIR_MODE     VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_ANA_L3_ROUTING_CFG_RLEG_NONIP_UC_REDIR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,25,2)

/**
 * \brief
 * Control handling of IPv6 frames which are otherwise to be L3 forwarded
 * but have Payload Length > ANA_L3:VMID:MAX_LEN.IP6_MAX_LEN for egress
 * router leg.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_IP_LEN_QU
 *
 * \details
 * 0: Drop frame
 * 1: Redirect frame to CPU
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_LEN_REDIR
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_LEN_REDIR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_LEN_REDIR  VTSS_BIT(22)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_LEN_REDIR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Control handling of IPv4 frames which are otherwise to be L3 forwarded
 * but have Total Length > ANA_L3:VMID:MAX_LEN.IP4_MAX_LEN for egress
 * router leg.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_IP_LEN_QU
 *
 * \details
 * 0: Drop frame
 * 1: Redirect frame to CPU
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_LEN_REDIR
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_LEN_REDIR(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_LEN_REDIR  VTSS_BIT(21)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_LEN_REDIR(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Copy IPv6 frames with broadcast DMAC to CPU.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_QU.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_L2_BC_COPY_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_L2_BC_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_L2_BC_COPY_ENA  VTSS_BIT(20)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_L2_BC_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Copy IPv4 frames with broadcast DMAC to CPU.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_QU.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_L2_BC_COPY_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_L2_BC_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_L2_BC_COPY_ENA  VTSS_BIT(19)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_L2_BC_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Redirect IPv6 frames failing SIP RPF check to CPU.CPU queue is
 * configured in ANA_L3:COMMON:CPU_QU_CFG.CPU_SIP_RPF_QU.Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_SIP_RPF_MODEANA_L3:COMMON:CPU_
 * QU_CFG.CPU_SIP_RPF_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . RLEG_IP6_SIP_RPF_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_RLEG_IP6_SIP_RPF_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_RLEG_IP6_SIP_RPF_REDIR_ENA  VTSS_BIT(18)
#define  VTSS_X_ANA_L3_ROUTING_CFG_RLEG_IP6_SIP_RPF_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Redirect IPv4 frames failing SIP RPF check to CPU.CPU queue is
 * configured in ANA_L3:COMMON:CPU_QU_CFG.CPU_SIP_RPF_QU.Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:COMMON:CPU_
 * QU_CFG.CPU_SIP_RPF_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . RLEG_IP4_SIP_RPF_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_RLEG_IP4_SIP_RPF_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_RLEG_IP4_SIP_RPF_REDIR_ENA  VTSS_BIT(17)
#define  VTSS_X_ANA_L3_ROUTING_CFG_RLEG_IP4_SIP_RPF_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Enable DIP checks for IPv6 packets to be routed. If enabled and the
 * frame's DIP falls within the given range then the frame is not
 * routed.Bit 0: ::/128 (Unspecified address)Bit 1: ::1/128 (Loopback
 * address)Frames which are not routed due to DIP check can be redirected
 * to CPU by setting CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * \details
 * '0':
 * Frame is allowed to be routed.
 *
 * '1':
 * Frame is not routed.
 * Frame is redirected to CPU if CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_DIP_ADDR_VIOLATION_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_DIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,15,2)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_DIP_ADDR_VIOLATION_REDIR_ENA     VTSS_ENCODE_BITMASK(15,2)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_DIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,2)

/**
 * \brief
 * Enable DIP checks for IPv4 packets matching a router leg.If enabled and
 * the frame's DIP falls within the given range then the frame is not
 * routed.Bit 0: 0.0.0.0 - 0.255.255.255Bit 1: 127.0.0.0 - 127.255.255.255
 * (Loopback network)Bit 2: 240.0.0.0 - 255.255.255.254
 * (Experimental)Frames which are not routed due to DIP check can be
 * redirected to CPU by setting CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * \details
 * '0':
 * Frame is allowed to be routed.
 *
 * '1':
 * Frame is not routed.
 * Frame is redirected to CPU if CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_DIP_ADDR_VIOLATION_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_DIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_DIP_ADDR_VIOLATION_REDIR_ENA     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_DIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/**
 * \brief
 * Enable SIP checks for IPv6 packets to be routed. If enabled and the
 * frame's SIP falls within the given range then the frame is not
 * routed.Bit 0: ::/128 (Unspecified address)Bit 1: ::1/128 (Loopback
 * address)Bit 2: ff00::/8 (IPv6 multicast addresses)Frames which are not
 * routed due to SIP check can be redirected to CPU by setting
 * CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * \details
 * '0':
 * Frame is allowed to be routed.
 *
 * '1':
 * Frame is not routed.
 * Frame is redirected to CPU if CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_SIP_ADDR_VIOLATION_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_SIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_SIP_ADDR_VIOLATION_REDIR_ENA     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_SIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Enable SIP checks for IPv4 packets matching a router leg.If enabled and
 * the frame's SIP falls within the given range then the frame is not
 * routed.Bit 0: 0.0.0.0 - 0.255.255.255 Bit 1: 127.0.0.0 - 127.255.255.255
 * (Loopback network)Bit 2: 224.0.0.0 - 255.255.255.255
 * (Multicast/experimental/broadcast)Frames which are not routed due to SIP
 * check can be redirected to CPU by setting
 * CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * \details
 * '0':
 * Frame is allowed to be routed.
 *
 * '1':
 * Frame is not routed.
 * Frame is redirected to CPU if CPU_RLEG_IP_HDR_FAIL_REDIR_ENA=1.
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_SIP_ADDR_VIOLATION_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_SIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_SIP_ADDR_VIOLATION_REDIR_ENA     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_SIP_ADDR_VIOLATION_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Control CPU redirection of IP error frames matching a router leg.CPU
 * queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_IP_HDR_FAIL_QU.The following errors
 * are covered:IPv4 header length errorIPv4 header checksum errorSIP
 * violations, if enabled in IP4_SIP_ADDR_VIOLATION_REDIR_ENA /
 * IP6_SIP_ADDR_VIOLATION_REDIR_ENA.DIP violations, if enabled in
 * IP4_DIP_ADDR_VIOLATION_REDIR_ENA / IP4_DIP_ADDR_VIOLATION_REDIR_ENA.IP
 * MC frames with unicast DMAC.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STICKY.RLEG_UC_HDR_ER
 * R_REDIR_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STICKY.RLEG_MC_HDR
 * _ERR_REDIR_STICKY
 *
 * \details
 * 0: Disable redirection (errored frames are discarded)
 * 1: Enable redirection to CPU queue
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . CPU_RLEG_IP_HDR_FAIL_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_CPU_RLEG_IP_HDR_FAIL_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_CPU_RLEG_IP_HDR_FAIL_REDIR_ENA  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_ROUTING_CFG_CPU_RLEG_IP_HDR_FAIL_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable redirection to CPU of IPv6 frames with Hop-by-Hop options.CPU
 * queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_IP_OPT_QU.Packets with Hob-by-Hop
 * options are not subject to routing.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . CPU_IP6_HOPBYHOP_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_CPU_IP6_HOPBYHOP_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_CPU_IP6_HOPBYHOP_REDIR_ENA  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_ROUTING_CFG_CPU_IP6_HOPBYHOP_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable redirection to CPU of IPv4 frames with IP4 options.CPU queue is
 * configured in ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_IP_OPT_QU.Packets with
 * IP options are not subject to routing.Related
 * parameters:ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_IP_OPT_QUANA_L3:VLAN_ARP_L3
 * MC_STICKY:L3_ARP_IPMC_STICKY.RLEG_MC_IP_OPT_REDIR_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . CPU_IP4_OPTIONS_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_CPU_IP4_OPTIONS_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_CPU_IP4_OPTIONS_REDIR_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_ROUTING_CFG_CPU_IP4_OPTIONS_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable redirection to CPU of IPv6 UC packets, which match a router leg
 * and have Hop Limit less than 2.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_IP_TTL_FAIL_QU.
 *
 * \details
 * 0: Disable redirection (errored frames are discarded)
 * 1: Enable redirection to CPU queue
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP6_HC_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP6_HC_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP6_HC_REDIR_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP6_HC_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable redirection to CPU of IPv4 UC packets, which match a router leg
 * and have TTL less than 2.CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_IP_TTL_FAIL_QU.
 *
 * \details
 * 0: Disable redirection (errored frames are discarded)
 * 1: Enable redirection to CPU queue
 *
 * Field: ::VTSS_ANA_L3_ROUTING_CFG . IP4_TTL_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG_IP4_TTL_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG_IP4_TTL_REDIR_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_ROUTING_CFG_IP4_TTL_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Routing Configuration
 *
 * \details
 * Routing related parameters.
 *
 * Register: \a ANA_L3:COMMON:ROUTING_CFG2
 */
#define VTSS_ANA_L3_ROUTING_CFG2             VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2b)

/**
 * \brief
 * Enable LPM lookup of IP6 SIP.This parameter must be set if DECAP_SIP_ID
 * is used.SIP lookup is also enabled if either SIP_CMP_ENA or SIP_RPF_ENA
 * is set.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_SIP_IDANA_L3:COMMON:SIP_SECURE_E
 * NA.SIP_CMP_ENAANA_L3:COMMON:SIP_RPF_ENA.SIP_RPF_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG2 . IP6_SIP_LOOKUP_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG2_IP6_SIP_LOOKUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG2_IP6_SIP_LOOKUP_ENA  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_ROUTING_CFG2_IP6_SIP_LOOKUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable LPM lookup of IP4 SIP.This parameter must be set if DECAP_SIP_ID
 * is used.SIP lookup is also enabled if either SIP_CMP_ENA or SIP_RPF_ENA
 * is set.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_SIP_IDANA_L3:COMMON:SIP_SECURE_E
 * NA.SIP_CMP_ENAANA_L3:COMMON:SIP_RPF_ENA.SIP_RPF_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG2 . IP4_SIP_LOOKUP_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG2_IP4_SIP_LOOKUP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG2_IP4_SIP_LOOKUP_ENA  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_ROUTING_CFG2_IP4_SIP_LOOKUP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable SIP lookup in VCAP IP6PFX for IPv6 frames.VCAP IP6PFX can be used
 * to reduce the key size required for IPv6 LPM lookups.All local IPv6
 * prefixes (64 most significant bits of the IPv6 address) can be installed
 * in VCAP IP6PFX together with a non-zero IP6PFX_ID action.If no match is
 * found in VCAP IP6PFX lookup, then IP6PFX_ID=0 is returned, i.e.
 * signaling "remote prefix".VCAP IP6PFX lookup will be performed for IPv6
 * frames if  SIP_IP6PFX_ENA==1 and will use the following key:Key type:
 * IP6PFXKey fields:DST_FLAG=0AFFIX=Value determined by classification by
 * ANA_CL.IP6_XIP=64 most significant bits of IPv6 SIP.When
 * SIP_IP6PFX_ENA==1 and IP6PFX_ID!=0, then VCAP LPM SIP lookup will use
 * the following key:Key type: IP6PFX_IDKey fields:DST_FLAG=0AFFIX=Value
 * determined by classification by ANA_CL.IP6PFX_ID=Value determined by
 * VCAP IP6PFX SIP lookupIP6_XIP=64 least significant bits of IPv6 SIP.When
 * SIP_IP6PFX_ENA==1 and IP6PFX_ID==0, then VCAP LPM SIP lookup will use
 * the following key:Key type: IP6PFX_IDKey fields:DST_FLAG=0AFFIX=Value
 * determined by classification by ANA_CL.IP6PFX_ID=0IP6_XIP=64 most
 * significant bits of IPv6 SIP.Related
 * parameters:ANA_L3:COMMON:SIP_RPF_ENA.SIP_RPF_ENAANA_L3:COMMON:SIP_SECURE
 * _ENA.SIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG2 . SIP_IP6PFX_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG2_SIP_IP6PFX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG2_SIP_IP6PFX_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_ROUTING_CFG2_SIP_IP6PFX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable DIP lookup in VCAP IP6PFX for IPv6 frames.VCAP IP6PFX can be used
 * to reduce the key size required for IPv6 LPM lookups.All local IPv6
 * prefixes (64 most significant bits of the IPv6 address) can be installed
 * in VCAP IP6PFX together with a non-zero IP6PFX_ID action.If no match is
 * found in VCAP IP6PFX lookup, then IP6PFX_ID=0 is returned, i.e.
 * signaling "remote prefix".VCAP IP6PFX lookup will be performed for IPv6
 * frames if  DIP_IP6PFX_ENA==1 && (IsUnicast(frame) ||
 * IP6_MC_DIP_FWD_ENA==1)and will use the following key:Key type: IP6PFXKey
 * fields:DST_FLAG=1AFFIX=Value determined by classification by
 * ANA_CL.IP6_XIP=64 most significant bits of IPv6 DIP.When
 * DIP_IP6PFX_ENA==1 and IP6PFX_ID!=0, then VCAP LPM DIP lookup will use
 * the following key:Key type: IP6PFX_IDKey fields:DST_FLAG=1AFFIX=Value
 * determined by classification by ANA_CL.IP6PFX_ID=Value determined by
 * VCAP IP6PFX SIP lookupIP6_XIP=64 least significant bits of IPv6 DIP.When
 * DIP_IP6PFX_ENA==1 and IP6PFX_ID==0, then VCAP LPM DIP lookup will use
 * the following key:Key type: IP6PFX_IDKey fields:DST_FLAG=1AFFIX=Value
 * determined by classification by ANA_CL.IP6PFX_ID=0IP6_XIP=64 most
 * significant bits of IPv6 DIP.Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.IP6_MC_DIP_FWD_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG2 . DIP_IP6PFX_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG2_DIP_IP6PFX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG2_DIP_IP6PFX_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_ROUTING_CFG2_DIP_IP6PFX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable redirection to CPU of IPv4 frames failing decapsulation
 * checks.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:VMID:VMID_ENCAP.DECAP_SIP_IDANA_L3:ARP:ARP_ENCAP.SIP
 * _IDANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUTING_CFG2 . IP4_DECAP_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_ROUTING_CFG2_IP4_DECAP_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_ROUTING_CFG2_IP4_DECAP_REDIR_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_ROUTING_CFG2_IP4_DECAP_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Router leg base MAC address
 *
 * \details
 * Configuration of router leg base MAC address.
 *
 * Register: \a ANA_L3:COMMON:RLEG_CFG_0
 */
#define VTSS_ANA_L3_RLEG_CFG_0               VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2c)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in REW and possibly EACL.Related
 * parameters:ANA_L3:COMMON:RLEG_CFG_1.RLEG_MAC_TYPE_SELREW:COMMON:RLEG_CFG
 * _0.RLEG_MAC_LSBEACL:COMMON:RLEG_CFG_0.RLEG_MAC_LSB
 *
 * \details
 * Bit 0: MAC address, bit 0
 * ...
 * Bit 23: MAC address, bit 23
 *
 * Field: ::VTSS_ANA_L3_RLEG_CFG_0 . RLEG_MAC_LSB
 */
#define  VTSS_F_ANA_L3_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_ANA_L3_RLEG_CFG_0_RLEG_MAC_LSB     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_ANA_L3_RLEG_CFG_0_RLEG_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/**
 * \brief Router Leg base MAC address
 *
 * \details
 * Configuration of router leg base MAC address.
 *
 * Register: \a ANA_L3:COMMON:RLEG_CFG_1
 */
#define VTSS_ANA_L3_RLEG_CFG_1               VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2d)

/**
 * \brief
 * Configuration of router leg specific MAC address.This must be configured
 * consistently in REW and possibly EACL.Related
 * parameters:REW:COMMON:RLEG_CFG_1.RLEG_MAC_TYPE_SELEACL:COMMON:RLEG_CFG_1
 * .RLEG_MAC_TYPE_SEL
 *
 * \details
 * 0: VMID used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB[23:0] . ((RLEG_MAC_LSB[23:0] + VMID[4-1:0]) mod
 * 2**24)
 *
 * 1: VID used to increment base MAC address:
 * RLEG_MAC = RLEG_MAC_MSB[23:0] . ((RLEG_MAC_LSB[23:0] + XVID) mod 2**24)
 *
 * 2: Base MAC address used for all router legs
 * RLEG_MAC = RLEG_MAC_MSB[23:0] . RLEG_MAC_LSB[23:0]
 *
 * 3: Reserved.
 *
 * Field: ::VTSS_ANA_L3_RLEG_CFG_1 . RLEG_MAC_TYPE_SEL
 */
#define  VTSS_F_ANA_L3_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_ANA_L3_RLEG_CFG_1_RLEG_MAC_TYPE_SEL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_ANA_L3_RLEG_CFG_1_RLEG_MAC_TYPE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Router leg base MAC address, least significant bits.In order to have
 * different MAC addresses per router leg, the base address may be
 * incremented using VID or VMID, ref. RLEG_MAC_TYPE_SEL.This must be
 * configured consistently in REW and possibly EACL.Related
 * parameters:REW:COMMON:RLEG_CFG_1.RLEG_MAC_MSBEACL:COMMON:RLEG_CFG_1.RLEG
 * _MAC_MSB
 *
 * \details
 * Bit 0: MAC address, bit 24
 * ...
 * Bit 23: MAC address, bit 47
 *
 * Field: ::VTSS_ANA_L3_RLEG_CFG_1 . RLEG_MAC_MSB
 */
#define  VTSS_F_ANA_L3_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ANA_L3_RLEG_CFG_1_RLEG_MAC_MSB     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ANA_L3_RLEG_CFG_1_RLEG_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief CPU Queue
 *
 * \details
 * Configuration of CPU queues relevant for routing
 *
 * Register: \a ANA_L3:COMMON:CPU_QU_CFG
 */
#define VTSS_ANA_L3_CPU_QU_CFG               VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2e)

/**
 * \brief
 * CPU queue number for non-IP unicast frames matching an ingress router
 * leg, e.g. ARP PDUs.CPU queue for IP frames with L2 broadcast DMAC,
 * received by router leg.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_RLEG_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_QU(x)  VTSS_ENCODE_BITFIELD(x,28,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_RLEG_QU     VTSS_ENCODE_BITMASK(28,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_RLEG_QU(x)  VTSS_EXTRACT_BITFIELD(x,28,3)

/**
 * \brief
 * CPU queue number for IPv4 frames with options and IPv6 frames with
 * Hop-by-Hop option. Redirection of such frames is enabled
 * usingROUTING_CFG.CPU_IP4_OPTIONS_REDIR_ENAROUTING_CFG.CPU_IP6_HOPBYHOP_R
 * EDIR_ENA
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_RLEG_IP_OPT_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_OPT_QU(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/**
 * \brief
 * CPU queue number for IPv4 frames with IP header errors. Redirection of
 * such frames is enabled usingROUTING_CFG.CPU_RLEG_IP_HDR_FAIL_REDIR_ENA
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_RLEG_IP_HDR_FAIL_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_RLEG_IP_HDR_FAIL_QU(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/**
 * \brief
 * CPU queue for frames failing SIP RPF check.Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.RLEG_IP4_SIP_RPF_REDIR_ENAANA_L3:CO
 * MMON:ROUTING_CFG.RLEG_IP6_SIP_RPF_REDIR_ENAANA_L3:VMID:RLEG_CTRL.RLEG_IP
 * 4_SIP_RPF_MODEANA_L3:VMID:RLEG_CTRL.RLEG_IP6_SIP_RPF_MODE
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_SIP_RPF_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_SIP_RPF_QU(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_SIP_RPF_QU     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_SIP_RPF_QU(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * CPU queue for IPv4/IPv6 frames failing MTU check.Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.IP4_LEN_REDIRANA_L3:COMMON:ROUTING_
 * CFG.IP6_LEN_REDIRANA_L3:VMID:MAX_LEN.IP4_MAX_LENANA_L3:VMID:MAX_LEN.IP6_
 * MAX_LEN
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_IP_LEN_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_LEN_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_IP_LEN_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_IP_LEN_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * CPU queue for failed RPF check.Related enable
 * bits:ANA_L3:L3MC:L3MC_CTRL.RPF_CHK_ENA
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_MC_FAIL_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_MC_FAIL_QU(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_MC_FAIL_QU     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_MC_FAIL_QU(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * CPU queue for failed IPv4/IPv6 unicast LPM lookup, invalid ARP entry
 * (ARP_ENA=0) or failed ICMP redirect check.Related enable
 * bits:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_ICMP_REDIR_ENAANA_L3:VMID:RLEG_CTRL.
 * RLEG_IP6_ICMP_REDIR_ENA
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_UC_FAIL_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_UC_FAIL_QU(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_UC_FAIL_QU     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_UC_FAIL_QU(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * CPU queue for IP unicast frames with a TTL/HL <2 and with successful ARP
 * lookup yielding a non-zero DMAC.CPU queue for IP multicast frames with a
 * TTL/HL <2 and with successful VCAP lookup.Related enable
 * bits:ANA_L3:COMMON:ROUTING_CFG.IP4_TTL_REDIR_ENAANA_L3:COMMON:ROUTING_CF
 * G.IP6_HC_REDIR_ENAANA_L3:L3MC:L3MC_CTRL.IPMC_TTL_COPY_ENA
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * n: CPU queue n.
 *
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG . CPU_IP_TTL_FAIL_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG_CPU_IP_TTL_FAIL_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CPU Queue
 *
 * \details
 * Configuration of CPU queues relevant for routing
 *
 * Register: \a ANA_L3:COMMON:CPU_QU_CFG2
 */
#define VTSS_ANA_L3_CPU_QU_CFG2              VTSS_IOREG(VTSS_TO_ANA_L3,0x10a2f)

/**
 * \brief
 * Queue for redirection of frames failing decapsulation checks.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:VMID:VMID_ENCAP.DECAP_SIP_IDANA_L3:ARP:ARP_ENCAP.SIP
 * _IDANA_L3:COMMON:ROUTING_CFG2.IP4_DECAP_REDIR_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_CPU_QU_CFG2 . CPU_IP_DECAP_QU
 */
#define  VTSS_F_ANA_L3_CPU_QU_CFG2_CPU_IP_DECAP_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_L3_CPU_QU_CFG2_CPU_IP_DECAP_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_L3_CPU_QU_CFG2_CPU_IP_DECAP_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief IPv4 Virtual Router Leg Configuration
 *
 * \details
 * Configuration of VRRP MAC address for IPv4.
 *
 * Use of VRRP for IPv4 is enabled per router leg in
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_VRID_ENA
 *
 * Register: \a ANA_L3:COMMON:VRRP_IP4_CFG_0
 */
#define VTSS_ANA_L3_VRRP_IP4_CFG_0           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a30)

/**
 * \brief
 * Mid part of IPv4 Virtual Router Redundancy Protocol MAC address.
 *
 * \details
 * IPv4 VRRP MAC address Bit 31 down to 8.
 *
 * Field: ::VTSS_ANA_L3_VRRP_IP4_CFG_0 . VRRP_IP4_BASE_MAC_MID
 */
#define  VTSS_F_ANA_L3_VRRP_IP4_CFG_0_VRRP_IP4_BASE_MAC_MID(x)  VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_ANA_L3_VRRP_IP4_CFG_0_VRRP_IP4_BASE_MAC_MID     VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_ANA_L3_VRRP_IP4_CFG_0_VRRP_IP4_BASE_MAC_MID(x)  VTSS_EXTRACT_BITFIELD(x,8,24)


/**
 * \brief IPv4 Virtual Router Leg Configuration
 *
 * \details
 * Configuration of VRRP MAC address for IPv4.
 *
 * Use of VRRP for IPv4 is enabled per router leg in
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_VRID_ENA
 *
 * Register: \a ANA_L3:COMMON:VRRP_IP4_CFG_1
 */
#define VTSS_ANA_L3_VRRP_IP4_CFG_1           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a31)

/**
 * \brief
 * Upper part of IPv4 Virtual Router Redundancy Protocol MAC address.
 *
 * \details
 * IPv4 VRRP MAC address Bit 47 down to 32.
 *
 * Field: ::VTSS_ANA_L3_VRRP_IP4_CFG_1 . VRRP_IP4_BASE_MAC_HIGH
 */
#define  VTSS_F_ANA_L3_VRRP_IP4_CFG_1_VRRP_IP4_BASE_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_L3_VRRP_IP4_CFG_1_VRRP_IP4_BASE_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_L3_VRRP_IP4_CFG_1_VRRP_IP4_BASE_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief IPv6 Virtual Router Leg Configuration
 *
 * \details
 * Configuration of VRRP MAC address for IPv6.
 *
 * Use of VRRP for IPv6 is enabled per router leg in
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_VRID_ENA
 *
 * Register: \a ANA_L3:COMMON:VRRP_IP6_CFG_0
 */
#define VTSS_ANA_L3_VRRP_IP6_CFG_0           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a32)

/**
 * \brief
 * Mid part of IPv6 Virtual Router Redundancy Protocol MAC address.
 *
 * \details
 * IPv6 VRRP MAC address Bit 31 down to 8.
 *
 * Field: ::VTSS_ANA_L3_VRRP_IP6_CFG_0 . VRRP_IP6_BASE_MAC_MID
 */
#define  VTSS_F_ANA_L3_VRRP_IP6_CFG_0_VRRP_IP6_BASE_MAC_MID(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_ANA_L3_VRRP_IP6_CFG_0_VRRP_IP6_BASE_MAC_MID     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_ANA_L3_VRRP_IP6_CFG_0_VRRP_IP6_BASE_MAC_MID(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief IPv6 Virtual Router Leg Configuration
 *
 * \details
 * Configuration of VRRP MAC address for IPv6.
 *
 * Use of VRRP for IPv6 is enabled per router leg in
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_VRID_ENA
 *
 * Register: \a ANA_L3:COMMON:VRRP_IP6_CFG_1
 */
#define VTSS_ANA_L3_VRRP_IP6_CFG_1           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a33)

/**
 * \brief
 * Upper part of IPv6 Virtual Router Redundancy Protocol MAC address.
 *
 * \details
 * IPv6 VRRP MAC address Bit 47 down to 32.
 *
 * Field: ::VTSS_ANA_L3_VRRP_IP6_CFG_1 . VRRP_IP6_BASE_MAC_HIGH
 */
#define  VTSS_F_ANA_L3_VRRP_IP6_CFG_1_VRRP_IP6_BASE_MAC_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_L3_VRRP_IP6_CFG_1_VRRP_IP6_BASE_MAC_HIGH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_L3_VRRP_IP6_CFG_1_VRRP_IP6_BASE_MAC_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Enable (SIP,SMAC) / (SIP,VMID) check
 *
 * \details
 * Bit per port that enables (SIP, SMAC) and/or (SIP, VMID) check.
 *
 * Register: \a ANA_L3:COMMON:SIP_SECURE_ENA
 */
#define VTSS_ANA_L3_SIP_SECURE_ENA           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a34)

/**
 * \brief
 * Lookup SIP in LPM and check that a) SMAC corresponds to MAC address in
 * ARP table entry and/or b) Frame has been received on the router leg
 * specified in ARP table entry.Any mismatch is signaled to ANA_ACL for use
 * in security rules.Note: This parameter can also be configured for CPU
 * ports and VD0-2. However the parameter is ignored for CPU ports and
 * VD0-1.Related
 * parameters:ANA_L3:ARP:ARP_CFG_0.MAC_MSBANA_L3:ARP:ARP_CFG_1.MAC_LSBANA_L
 * 3:ARP:ARP_CFG_0.ARP_VMIDANA_L3:ARP:ARP_CFG_0.SECUR_MATCH_VMID_ENAANA_L3:
 * ARP:ARP_CFG_0.SECUR_MATCH_MAC_ENAANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC
 * _STICKY.SECUR_DIP_FAIL_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STI
 * CKY.SECUR_IP4_SIP_MATCH_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_ST
 * ICKY.SECUR_IP6_SIP_MATCH_STICKY
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_L3_SIP_SECURE_ENA . SIP_CMP_ENA
 */
#define  VTSS_F_ANA_L3_SIP_SECURE_ENA_SIP_CMP_ENA(x)  (x)
#define  VTSS_M_ANA_L3_SIP_SECURE_ENA_SIP_CMP_ENA     0xffffffff
#define  VTSS_X_ANA_L3_SIP_SECURE_ENA_SIP_CMP_ENA(x)  (x)


/**
 * \brief Enable (SIP,SMAC) / (SIP,VMID) check
 *
 * \details
 * Bit per port that enables (SIP, SMAC) and/or (SIP, VMID) check.
 *
 * Register: \a ANA_L3:COMMON:SIP_SECURE_ENA1
 */
#define VTSS_ANA_L3_SIP_SECURE_ENA1          VTSS_IOREG(VTSS_TO_ANA_L3,0x10a35)

/**
 * \brief
 * Lookup SIP in LPM and check that a) SMAC corresponds to MAC address in
 * ARP table entry and/or b) Frame has been received on the router leg
 * specified in ARP table entry.Any mismatch is signaled to ANA_ACL for use
 * in security rules.Note: This parameter can also be configured for CPU
 * ports and VD0-2. However the parameter is ignored for CPU ports and
 * VD0-1.Related
 * parameters:ANA_L3:ARP:ARP_CFG_0.MAC_MSBANA_L3:ARP:ARP_CFG_1.MAC_LSBANA_L
 * 3:ARP:ARP_CFG_0.ARP_VMIDANA_L3:ARP:ARP_CFG_0.SECUR_MATCH_VMID_ENAANA_L3:
 * ARP:ARP_CFG_0.SECUR_MATCH_MAC_ENAANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC
 * _STICKY.SECUR_DIP_FAIL_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STI
 * CKY.SECUR_IP4_SIP_MATCH_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_ST
 * ICKY.SECUR_IP6_SIP_MATCH_STICKY
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_L3_SIP_SECURE_ENA1 . SIP_CMP_ENA1
 */
#define  VTSS_F_ANA_L3_SIP_SECURE_ENA1_SIP_CMP_ENA1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_L3_SIP_SECURE_ENA1_SIP_CMP_ENA1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_L3_SIP_SECURE_ENA1_SIP_CMP_ENA1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Enable (DIP,SMAC) / (DIP,VMID) check
 *
 * \details
 * Bit per port that enables (DIP, DMAC) and/or (DIP, VMID) check.
 *
 * Register: \a ANA_L3:COMMON:DIP_SECURE_ENA
 */
#define VTSS_ANA_L3_DIP_SECURE_ENA           VTSS_IOREG(VTSS_TO_ANA_L3,0x10a37)

/**
 * \brief
 * Lookup DIP in LPM and check that a) DMAC corresponds to MAC address in
 * ARP table entry and/or b) Frame has been received on a VLAN with a VMID
 * value matching the ARP_VMID in the ARP table entry.Any mismatch is
 * signaled to ANA_ACL for use in security rules.DIP check is only
 * performed for L2 forwarded IP unicast frames.Related
 * parameters:ANA_L3:ARP:ARP_CFG_0.MAC_MSBANA_L3:ARP:ARP_CFG_1.MAC_LSBANA_L
 * 3:ARP:ARP_CFG_0.ARP_VMIDANA_L3:ARP:ARP_CFG_0.SECUR_MATCH_VMID_ENAANA_L3:
 * ARP:ARP_CFG_0.SECUR_MATCH_MAC_ENAANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC
 * _STICKY.SECUR_DIP_FAIL_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STI
 * CKY.SECUR_IP4_DIP_MATCH_STICKYANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_ST
 * ICKY.SECUR_IP6_DIP_MATCH_STICKY
 *
 * \details
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_L3_DIP_SECURE_ENA . DIP_CMP_ENA
 */
#define  VTSS_F_ANA_L3_DIP_SECURE_ENA_DIP_CMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_DIP_SECURE_ENA_DIP_CMP_ENA     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_DIP_SECURE_ENA_DIP_CMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Enable SIP RPF check
 *
 * \details
 * Bit per port that enables SIP RPF check.
 *
 * Register: \a ANA_L3:COMMON:SIP_RPF_ENA
 */
#define VTSS_ANA_L3_SIP_RPF_ENA              VTSS_IOREG(VTSS_TO_ANA_L3,0x10a3a)

/**
 * \brief
 * Enable SIP RPF check per ingress port.Note: This parameter can also be
 * configured for CPU ports and VD0-2. However the parameter is ignored for
 * CPU ports and VD0-1.For more information, refer to
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:VMID:RLEG_CTRL.RLEG_IP
 * 6_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_SIP_RPF_ENA . SIP_RPF_ENA
 */
#define  VTSS_F_ANA_L3_SIP_RPF_ENA_SIP_RPF_ENA(x)  (x)
#define  VTSS_M_ANA_L3_SIP_RPF_ENA_SIP_RPF_ENA     0xffffffff
#define  VTSS_X_ANA_L3_SIP_RPF_ENA_SIP_RPF_ENA(x)  (x)


/**
 * \brief Enable SIP RPF check
 *
 * \details
 * Bit per port that enables SIP RPF check.
 *
 * Register: \a ANA_L3:COMMON:SIP_RPF_ENA1
 */
#define VTSS_ANA_L3_SIP_RPF_ENA1             VTSS_IOREG(VTSS_TO_ANA_L3,0x10a3b)

/**
 * \brief
 * Enable SIP RPF check per ingress port.Note: This parameter can also be
 * configured for CPU ports and VD0-2. However the parameter is ignored for
 * CPU ports and VD0-1.For more information, refer to
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:VMID:RLEG_CTRL.RLEG_IP
 * 6_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_SIP_RPF_ENA1 . SIP_RPF_ENA1
 */
#define  VTSS_F_ANA_L3_SIP_RPF_ENA1_SIP_RPF_ENA1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_L3_SIP_RPF_ENA1_SIP_RPF_ENA1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_L3_SIP_RPF_ENA1_SIP_RPF_ENA1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Service Control
 *
 * \details
 * Miscellaneous service configuration.
 *
 * Register: \a ANA_L3:COMMON:SERVICE_CFG
 */
#define VTSS_ANA_L3_SERVICE_CFG              VTSS_IOREG(VTSS_TO_ANA_L3,0x10a3d)

/**
 * \brief
 * Force Egress FID=ANA_L3:VLAN:VLAN_CFG.VLAN_FID when ISDX > 0 and frame
 * has multicast DMAC.
 *
 * \details
 * 0: Normal EFID behavior for multicast  DMAC.
 * 1: Force EFID=ANA_L3:VLAN:VLAN_CFG.VLAN_FID for multicast DMAC when ISDX
 * > 0.
 *
 * Field: ::VTSS_ANA_L3_SERVICE_CFG . ISDX_FORCE_MC_EFID_ENA
 */
#define  VTSS_F_ANA_L3_SERVICE_CFG_ISDX_FORCE_MC_EFID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_SERVICE_CFG_ISDX_FORCE_MC_EFID_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_SERVICE_CFG_ISDX_FORCE_MC_EFID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_L3:VLAN
 *
 * VLAN table configuration
 */


/**
 * \brief Router Leg Identification / Mapped VLAN ID
 *
 * \details
 * Register: \a ANA_L3:VLAN:VMID_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_VMID_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,0)

/**
 * \brief
 * Routing:VMID, identifying VLAN's router leg.Security check: "Mapped VLAN
 * ID".
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_CFG . VMID
 */
#define  VTSS_F_ANA_L3_VMID_CFG_VMID(x)       VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_L3_VMID_CFG_VMID          VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_L3_VMID_CFG_VMID(x)       VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Bundle dual leaky bucket policer index
 *
 * \details
 * Specifies BUM policer index.
 *
 * Register: \a ANA_L3:VLAN:BUM_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_BUM_CFG(gi)              VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,1)

/**
 * \brief
 * Broadcast, Unknown and Multicast traffic leaky bucket indexThis index
 * can be overruled by index from ISDX table if
 * ANA_L2:ISDX:MISC_CFG.BUM_SLB_ENA is set.Related
 * parameters:ANA_AC_POL:BUM_SLB
 *
 * \details
 * Field: ::VTSS_ANA_L3_BUM_CFG . BUM_SLB_IDX
 */
#define  VTSS_F_ANA_L3_BUM_CFG_BUM_SLB_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_L3_BUM_CFG_BUM_SLB_IDX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_L3_BUM_CFG_BUM_SLB_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief VLAN Configuration
 *
 * \details
 * Various configuration of VLAN handles
 *
 * Register: \a ANA_L3:VLAN:VLAN_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_VLAN_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,2)

/**
 * \brief
 * If set, and ANA_AC:PGID:PGID_MISC_CFG.OBEY_VLAN is also set, the CPU
 * copy information from the PGID table is ignored.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_PGID_CPU_DIS
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_PGID_CPU_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_PGID_CPU_DIS  VTSS_BIT(31)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_PGID_CPU_DIS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Pointer to STP instance associated with VLAN.The value must not exceed
 * the size of the MSTP table, ref. MSTP.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_MSTP_PTR
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_MSTP_PTR(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * FID to be used for learning and forwarding.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_FID
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_FID(x)   VTSS_ENCODE_BITFIELD(x,8,13)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_FID      VTSS_ENCODE_BITMASK(8,13)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_FID(x)   VTSS_EXTRACT_BITFIELD(x,8,13)

/**
 * \brief
 * Enable VLAN ingress filtering per VLAN. If a enabled, frames received on
 * a port, which is not a member of the classified VLAN, are discarded.VLAN
 * ingress filtering can also be enabled per ingress port.VLAN ingress
 * filtering is performed if either enabled for ingress port or for
 * VLAN.Related
 * parameters:ANA_L3:COMMON:VLAN_FILTER_CTRLANA_L3:VLAN_ARP_L3MC_STICKY:VLA
 * N_STICKY.VLAN_IGR_FILTER_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_IGR_FILTER_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_IGR_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable secure forwarding on a per VLAN basis.When secure forwarding is
 * enabled, only frames with known SMAC are forwarded.
 *
 * \details
 * 0: Forwarding is allowed regardless of SMAC being known or unknown.
 * 1: Forwarding is only allowed for frames with known SMAC.
 *
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_SEC_FWD_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_SEC_FWD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_SEC_FWD_ENA  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_SEC_FWD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Disable flooding of frames with unknown DMAC on a per VLAN basis.Note
 * that when VLAN_FLOOD_DIS=1, then frames with broadcast or multicast DMAC
 * are only forwarded if installed in MAC table.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_FLOOD_DIS
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_FLOOD_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Disable learning of SMAC of frames received on this VLAN.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.VLAN_LRN_DENY_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_LRN_DIS
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_LRN_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_LRN_DIS  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_LRN_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable router leg in VLAN.If enabled, the ID of the router leg is
 * configured in VMID_CFG.VMID.Related parameters:ANA_L3:VLAN:VMID_CFG.VMID
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_RLEG_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_RLEG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_RLEG_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_RLEG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable / disable this VLAN as a Private VLAN (PVLAN). Ports within a
 * PVLAN are categorized into three different port types:Promiscuous ports:
 * A promiscuous port can communicate with all ports in the PVLAN,
 * including the isolated and community ports.Isolated ports: An isolated
 * port has complete Layer 2 separation from the other ports within the
 * same PVLAN, but not from the promiscuous ports. PVLANs block all traffic
 * to isolated ports except traffic from promiscuous ports. Traffic from
 * isolated port is forwarded only to promiscuous ports.Community ports:
 * Community ports communicate among themselves and with the PVLAN's
 * promiscuous ports. Community ports cannot communicate with isolated
 * ports.Related
 * parameters:ANA_L3:COMMON:VLAN_ISOLATED_CFGANA_L3:COMMON:VLAN_COMMUNITY_C
 * FG
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_PRIVATE_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_PRIVATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * VLAN mirror enable flag. If this field is set, frames classified to this
 * ingress VLAN are mirrored.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_CFG . VLAN_MIRROR_ENA
 */
#define  VTSS_F_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_VLAN_CFG_VLAN_MIRROR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TUPE Control
 *
 * \details
 * Control value for Table UPdate Engine (TUPE).
 *
 * See ANA_L3:TUPE.
 *
 * Register: \a ANA_L3:VLAN:TUPE_CTRL
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_TUPE_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,3)

/**
 * \brief
 * Control value for Table UPdate Engine (TUPE).Note that unused bits in
 * VLAN_PORT_MASK may also be used to control which VLAN table entries TUPE
 * shall update.See ANA_L3:TUPE.
 *
 * \details
 * Field: ::VTSS_ANA_L3_TUPE_CTRL . TUPE_CTRL
 */
#define  VTSS_F_ANA_L3_TUPE_CTRL_TUPE_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_TUPE_CTRL_TUPE_CTRL    VTSS_BIT(0)
#define  VTSS_X_ANA_L3_TUPE_CTRL_TUPE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VLAN Port Mask Configuration
 *
 * \details
 * Configuration of VLAN port mask.
 *
 * Register: \a ANA_L3:VLAN:VLAN_MASK_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_VLAN_MASK_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,4)

/**
 * \brief
 * Specify mask of ports belonging to VLAN.Note:  Initialization value for
 * addresses 0,1 and 4095 is '1...1'  Initialization value for all other
 * addresses is 0Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.VLAN_LOOKUP_INVLD_STI
 * CKY
 *
 * \details
 * 0: Port does not belong to the VLAN
 * 1: Port belongs to the VLAN
 *
 * Field: ::VTSS_ANA_L3_VLAN_MASK_CFG . VLAN_PORT_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MASK_CFG_VLAN_PORT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_VLAN_MASK_CFG_VLAN_PORT_MASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_VLAN_MASK_CFG_VLAN_PORT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief QGRP configuration
 *
 * \details
 * Configuration of QGRP index and QSYS OAM drop counting.
 *
 * Register: \a ANA_L3:VLAN:QGRP_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_QGRP_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,7)

/**
 * \brief
 * Configures QGRP used to lookup the VPORT table in XQS. The QGRP may be
 * overwritten by the ISDX table.  Related
 * parameters:ANA_L2:ISDX:QGRP_CFGXQS:QMAP_VPORT_TBL.
 *
 * \details
 * Field: ::VTSS_ANA_L3_QGRP_CFG . QGRP_IDX
 */
#define  VTSS_F_ANA_L3_QGRP_CFG_QGRP_IDX(x)   VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_L3_QGRP_CFG_QGRP_IDX      VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_L3_QGRP_CFG_QGRP_IDX(x)   VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Configures OAM type for traffic detected as OAM by classification to be
 * used by XQS to determining if dropped frames should be counted or not.
 * Related
 * parameters:ANA_L2:ISDX:QGRP_CFGXQS:QMAP_QOS_TBL:DROP_STAT_CTRL.DROP_STAT
 * _OAM_CNT_SEL
 *
 * \details
 * 0: Not OAM - Frames dropped by QSYS are always counted in QSYS drop
 * stat.
 * 1: EVC OAM - Frames dropped by QSYS which are classified as OAM will
 * selectively be counted in QSYS drop stat as EVC OAM.
 * 2: OVC / PW OAM - Frames dropped by QSYS which are classified as OAM
 * will selectively be counted in QSYS drop stat as OVC / PW OAM.
 * 3: DOWN MEP OAM - Frames dropped by QSYS which are classified as OAM
 * will never be counted in QSYS drop stat.
 *
 * Field: ::VTSS_ANA_L3_QGRP_CFG . QGRP_OAM_TYPE
 */
#define  VTSS_F_ANA_L3_QGRP_CFG_QGRP_OAM_TYPE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_L3_QGRP_CFG_QGRP_OAM_TYPE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_L3_QGRP_CFG_QGRP_OAM_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/**
 * \brief Miscellaneous VLAN parameters
 *
 * \details
 * Register: \a ANA_L3:VLAN:MISC
 *
 * @param gi Replicator: x_FFL_ANA_L3_VLAN_TABLE_LEN (??), 0-4223
 */
#define VTSS_ANA_L3_MISC(gi)                 VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x0,gi,16,0,8)

/**
 * \brief
 * Selects forwarder virtual LAG profile in ANA_AC. The FV_LAG controls
 * flooding and which link aggregation groups are seen by the forwarder.
 * See ANA_AC:PGID and ANA_AC:LAG_RST for details.
 *
 * \details
 * Field: ::VTSS_ANA_L3_MISC . FV_LAG_IDX
 */
#define  VTSS_F_ANA_L3_MISC_FV_LAG_IDX(x)     VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_L3_MISC_FV_LAG_IDX        VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_L3_MISC_FV_LAG_IDX(x)     VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a ANA_L3:MSTP
 *
 * MSTP table configuration
 */


/**
 * \brief MSTP Forwarding Control
 *
 * \details
 * Configuration of forwarding state per MSTP
 *
 * Register: \a ANA_L3:MSTP:MSTP_FWD_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_MSTPS (??), 0-65
 */
#define VTSS_ANA_L3_MSTP_FWD_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10800,gi,8,0,0)

/**
 * \brief
 * Enable/disable forwarding per port.	Ports in MSTP Forwarding state must
 * be enabled in this port mask. If a port is disabled in this mask, frames
 * received on the port are not forwarded, and frames are not forwarded to
 * the port.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.MSTP_DISCARD_STICKYAN
 * A_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.MSTP_FWD_ALLOWED_STICKY
 *
 * \details
 * '0': forwarding is disabled from/to respective port
 * '1': forwarding is enabled from/to respective port
 *
 * Field: ::VTSS_ANA_L3_MSTP_FWD_CFG . MSTP_FWD_MASK
 */
#define  VTSS_F_ANA_L3_MSTP_FWD_CFG_MSTP_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_MSTP_FWD_CFG_MSTP_FWD_MASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_MSTP_FWD_CFG_MSTP_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief MSTP Learning Control
 *
 * \details
 * Configuration of learning state per MSTP.
 *
 * Register: \a ANA_L3:MSTP:MSTP_LRN_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_MSTPS (??), 0-65
 */
#define VTSS_ANA_L3_MSTP_LRN_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10800,gi,8,0,3)

/**
 * \brief
 * Enable/disable learning per port.If a port is disabled in the mask, L2
 * learning of the (FID, SMAC) pair is not done.Ports in MSTP Learning and
 * Forwarding state must be enabled in this mask.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.MSTP_LRN_DENY_STICKYA
 * NA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY.MSTP_LRN_ALLOWED_STICKY
 *
 * \details
 * '0': Learning is disabled for frames from respective port
 * '1': Learning is enabled for frames from respective port
 *
 * Field: ::VTSS_ANA_L3_MSTP_LRN_CFG . MSTP_LRN_MASK
 */
#define  VTSS_F_ANA_L3_MSTP_LRN_CFG_MSTP_LRN_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_ANA_L3_MSTP_LRN_CFG_MSTP_LRN_MASK     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_ANA_L3_MSTP_LRN_CFG_MSTP_LRN_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,30)

/**
 * Register Group: \a ANA_L3:VMID
 *
 * Router Leg Table
 */


/**
 * \brief Router leg control
 *
 * \details
 * Register: \a ANA_L3:VMID:RLEG_CTRL
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_RLEG_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,0)

/**
 * \brief
 * XVID for egress router leg.This must be configured consistently in
 * REW:VMID:RLEG_CTRL.RLEG_EVID.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_EVID
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_EVID(x)  VTSS_ENCODE_BITFIELD(x,19,13)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_EVID     VTSS_ENCODE_BITMASK(19,13)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_EVID(x)  VTSS_EXTRACT_BITFIELD(x,19,13)

/**
 * \brief
 * For IPv6 frames, configure router leg counters to only count IP part of
 * frame.Default is to count the full Ethernet frame.Only applicable to
 * router leg counters configured to count bytes.Related
 * parameters:ANA_AC:STAT_GLOBAL_CFG_IRLEGANA_AC:STAT_CNT_CFG_IRLEGANA_AC:S
 * TAT_GLOBAL_CFG_ERLEGANA_AC:STAT_CNT_CFG_ERLEG
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_STAT_IP_ONLY_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_STAT_IP_ONLY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_STAT_IP_ONLY_ENA  VTSS_BIT(18)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_STAT_IP_ONLY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * For IPv4 frames, configure router leg counters to only count IP part of
 * frame.Default is to count the full Ethernet frame.Only applicable to
 * router leg counters configured to count bytes.Related
 * parameters:ANA_AC:STAT_GLOBAL_CFG_IRLEGANA_AC:STAT_CNT_CFG_IRLEGANA_AC:S
 * TAT_GLOBAL_CFG_ERLEGANA_AC:STAT_CNT_CFG_ERLEG
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_STAT_IP_ONLY_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_STAT_IP_ONLY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_STAT_IP_ONLY_ENA  VTSS_BIT(17)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_STAT_IP_ONLY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * SIP RPF mode for IPv6.If SIP RPF check fails, then frame is not allowed
 * to be L3 forwarded.Disabled:No SIP RPF check.RGID Mode:Verify that SIP
 * belongs to a known subnet and verify that SIP's RGID is enabled in
 * ingress router leg's RGID_MASK.Rleg Mode:Verify that SIP belongs to a
 * known subnet, and that the frame is received on the router leg through
 * which that subnet is reached.If SIP is reached through an ECMP path then
 * no SIP RPF check is performed.Combined Mode:Apply Rleg Mode for non ECMP
 * paths and RGID Mode for ECMP paths.Related
 * parameters:ANA_L3:COMMON:SIP_RPF_ENAANA_L3:COMMON:ROUTING_CFG.RLEG_IP6_S
 * IP_RPF_REDIR_ENAANA_L3:COMMON:CPU_QU_CFG.CPU_SIP_RPF_QUANA_L3:VLAN_ARP_L
 * 3MC_STICKY:L3_ARP_IPMC_STICKY.IP6_SIP_RPF_FILTER_STICKYANA_L3:VMID:SIP_R
 * PF.RLEG_RGID_MASK
 *
 * \details
 * 0: Disabled
 * 1: RGID Mode
 * 2: Rleg Mode
 * 3: Combined Mode
 *
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_SIP_RPF_MODE
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_SIP_RPF_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_SIP_RPF_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_SIP_RPF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * SIP RPF mode for IPv4.If SIP RPF check fails, then frame is not allowed
 * to be L3 forwarded.Disabled:No SIP RPF check.RGID Mode:Verify that SIP
 * belongs to a known subnet and verify that SIP's RGID is enabled in
 * ingress router leg's RLEG_RGID_MASK.Rleg Mode:Verify that SIP belongs to
 * a known subnet, and that the frame is received on the router leg through
 * which that subnet is reached.If SIP is reached through an ECMP path then
 * no SIP RPF check is performed.Combined Mode:Apply Rleg Mode for non ECMP
 * paths and RGID Mode for ECMP paths.Related
 * parameters:ANA_L3:COMMON:SIP_RPF_ENAANA_L3:COMMON:ROUTING_CFG.RLEG_IP4_S
 * IP_RPF_REDIR_ENAANA_L3:COMMON:CPU_QU_CFG.CPU_SIP_RPF_QUANA_L3:VLAN_ARP_L
 * 3MC_STICKY:L3_ARP_IPMC_STICKY.IP4_SIP_RPF_FILTER_STICKYANA_L3:VMID:SIP_R
 * PF.RLEG_RGID_MASK
 *
 * \details
 * 0: Disabled
 * 1: RGID Mode
 * 2: Rleg Mode
 * 3: Combined Mode
 *
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_SIP_RPF_MODE
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_SIP_RPF_MODE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_SIP_RPF_MODE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_SIP_RPF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Disable Hop Limit decrement for frames received on this router leg.This
 * parameter only works when ACL_RT_SEL=1.Related
 * parameters:ANA_L3:ARP:ARP_CFG_2.TTL_DECR_DISANA_L3:L3MC:L3MC_CTRL.TTL_DE
 * CR_DISANA_ACL:COMMON:VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_TTL_DECR_DIS
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_TTL_DECR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_TTL_DECR_DIS  VTSS_BIT(9)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_TTL_DECR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Disable TTL/Hop Limit decrement for frames received on this router
 * leg.This parameter only works when ACL_RT_SEL=1.Related
 * parameters:ANA_L3:ARP:ARP_CFG_2.TTL_DECR_DISANA_L3:L3MC:L3MC_CTRL.TTL_DE
 * CR_DISANA_ACL:COMMON:VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_TTL_DECR_DIS
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_TTL_DECR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_TTL_DECR_DIS  VTSS_BIT(8)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_TTL_DECR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable IPv6 unicast routing for frames received on this router leg.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_UC_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_UC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_UC_ENA  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_UC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable IPv4 unicast routing for frames received on this router leg.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_UC_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_UC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_UC_ENA  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_UC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable IPv6 multicast routing for frames received on this router leg.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_MC_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_MC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_MC_ENA  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_MC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable IPv4 multicast routing for frames received on this router leg.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_MC_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_MC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_MC_ENA  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_MC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable redirection to CPU of IPv6 packets with IVMID==EVMID (i.e.
 * packets that are to be routed back to the router leg, they were received
 * on).CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_UC_FAIL_QU.Related
 * parameters:ANA_L3:COMMON:CPU_QU_CFG.CPU_UC_FAIL_QUANA_L3:VLAN_ARP_L3MC_S
 * TICKY:L3_ARP_IPMC_STICKY.UC_ICMP_REDIR_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_ICMP_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_ICMP_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_ICMP_REDIR_ENA  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_ICMP_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable redirection to CPU of IPv4 packets with IVMID==EVMID (i.e.
 * packets that are to be routed back to the router leg, they were received
 * on).CPU queue is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_UC_FAIL_QU.Related
 * parameters:ANA_L3:COMMON:CPU_QU_CFG.CPU_UC_FAIL_QUANA_L3:VLAN_ARP_L3MC_S
 * TICKY:L3_ARP_IPMC_STICKY.UC_ICMP_REDIR_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_ICMP_REDIR_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_ICMP_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_ICMP_REDIR_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_ICMP_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable IPv6 virtual router leg. If enabled, the router leg can also be
 * addressed using a MAC address constructed using the following
 * fields:Bits 47-32: ANA_L3:COMMON:VRRP_IP6_CFG_1.VRRP_IP6_BASE_MAC_HIGH
 * Bits 31-8: ANA_L3:COMMON:VRRP_IP6_CFG_0.VRRP_IP6_BASE_MAC_MID Bits 7-0:
 * ANA_L3:VMID:VRRP_CFG.RLEG_IP6_VRID
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP6_VRID_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP6_VRID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP6_VRID_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP6_VRID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable IPv4 virtual router leg. If enabled, the router leg can also be
 * addressed using a MAC address constructed using the following
 * fields:Bits 47-32: ANA_L3:COMMON:VRRP_IP4_CFG_1.VRRP_IP4_BASE_MAC_HIGH
 * Bits 31-8: ANA_L3:COMMON:VRRP_IP4_CFG_0.VRRP_IP4_BASE_MAC_MID Bits 7-0:
 * ANA_L3:VMID:VRRP_CFG.RLEG_IP4_VRID
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_CTRL . RLEG_IP4_VRID_ENA
 */
#define  VTSS_F_ANA_L3_RLEG_CTRL_RLEG_IP4_VRID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_RLEG_CTRL_RLEG_IP4_VRID_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_RLEG_CTRL_RLEG_IP4_VRID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Virtual router leg configuration
 *
 * \details
 * Configuration of Virtual Router Interface MAC address
 *
 * Register: \a ANA_L3:VMID:VRRP_CFG
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 * @param ri Replicator: x_FFL_ANA_L3_NUM_VRID (??), 0-3
 */
#define VTSS_ANA_L3_VRRP_CFG(gi,ri)          VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,ri,1)

/**
 * \brief
 * Router leg's VRID for IPv4.The configured VRID is used as part of the
 * VRRP router MAC address.Only applicable if VRRP is enabled for router
 * leg.See RLEG_IP4_VRID_ENA for further details.If not all VRIDs are used,
 * then any unused VRID(s) must be set to the same value as one of the VRID
 * in use.Related parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_VRID_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_VRRP_CFG . RLEG_IP4_VRID
 */
#define  VTSS_F_ANA_L3_VRRP_CFG_RLEG_IP4_VRID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_L3_VRRP_CFG_RLEG_IP4_VRID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_L3_VRRP_CFG_RLEG_IP4_VRID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Router leg's VRID for IPv6.The configured VRID is used as part of the
 * VRRP router MAC address.Only applicable if VRRP is enabled for router
 * leg.See RLEG_IP6_VRID_ENA for further details.If not all VRIDs are used,
 * then any unused VRID(s) must be set to the same value as one of the VRID
 * in use.Related parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_VRID_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_VRRP_CFG . RLEG_IP6_VRID
 */
#define  VTSS_F_ANA_L3_VRRP_CFG_RLEG_IP6_VRID(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ANA_L3_VRRP_CFG_RLEG_IP6_VRID     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ANA_L3_VRRP_CFG_RLEG_IP6_VRID(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief IP multicast router leg configuration
 *
 * \details
 * Register: \a ANA_L3:VMID:VMID_MC
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_VMID_MC(gi)              VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,5)

/**
 * \brief
 * Enable checking of DMAC for IPv6 multicast packets.I.e. verify that
 * DMAC[47:32] == 0x3333ref. RFC 2464.If the check fails, the packet is not
 * routed.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_MC . RLEG_IP6_MC_DMAC_CHK_ENA
 */
#define  VTSS_F_ANA_L3_VMID_MC_RLEG_IP6_MC_DMAC_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_L3_VMID_MC_RLEG_IP6_MC_DMAC_CHK_ENA  VTSS_BIT(17)
#define  VTSS_X_ANA_L3_VMID_MC_RLEG_IP6_MC_DMAC_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Enable checking of DMAC for IPv4 multicast packets.I.e. verify that
 * DMAC[47:24] == 0x01005e  DMAC[23] == 0ref. RFC 1112.If the check fails,
 * the packet is not routed.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_MC . RLEG_IP4_MC_DMAC_CHK_ENA
 */
#define  VTSS_F_ANA_L3_VMID_MC_RLEG_IP4_MC_DMAC_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_VMID_MC_RLEG_IP4_MC_DMAC_CHK_ENA  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_VMID_MC_RLEG_IP4_MC_DMAC_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * IPv4 multicast TTL limit.Packets with TTL below the configured limit are
 * not routed.TTL is checked against RLEG_IP4_MC_TTL before transmission on
 * egress router leg.Note: Regardless of the value configured for this
 * parameter, IPv4 MC packets with TTL<2 are not routed.
 *
 * \details
 * 0: Router leg based MC TTL check disabled.
 * 1-2: N/A - such packets are not routed anyway.
 * 3: If packet's TTL is < 3 then packet is not routed.
 * 4: If packet's TTL is < 4 then packet is not routed.
 * ...
 *
 * Field: ::VTSS_ANA_L3_VMID_MC . RLEG_IP4_MC_TTL
 */
#define  VTSS_F_ANA_L3_VMID_MC_RLEG_IP4_MC_TTL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_L3_VMID_MC_RLEG_IP4_MC_TTL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_L3_VMID_MC_RLEG_IP4_MC_TTL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * IPv6 multicast HL limit.Packets with HL below the configured limit are
 * not routed.HL is checked against RLEG_IP6_MC_TTL before transmission on
 * egress router leg.Note: Regardless of the value configured for this
 * parameter, IPv6 MC packets with HC<2 are not routed.
 *
 * \details
 * 0: Router leg based MC HL check disabled
 * 1-2: N/A - such packets are not routed anyway.
 * 3: If packet's HC is < 3 then packet is not routed.
 * 4: If packet's HC is < 4 then packet is not routed.
 * ...
 *
 * Field: ::VTSS_ANA_L3_VMID_MC . RLEG_IP6_MC_TTL
 */
#define  VTSS_F_ANA_L3_VMID_MC_RLEG_IP6_MC_TTL(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_ANA_L3_VMID_MC_RLEG_IP6_MC_TTL     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_ANA_L3_VMID_MC_RLEG_IP6_MC_TTL(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/**
 * \brief SIP RPF check parameters
 *
 * \details
 * Register: \a ANA_L3:VMID:SIP_RPF
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_SIP_RPF(gi)              VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,6)

/**
 * \brief
 * Route Group IDs (RGIDs) accepted for this router leg when SIP_RPF_MODE
 * is set to "RGID Mode".See description of RLEG_IP4_SIP_RPF_MODE /
 * RLEG_IP6_SIP_RPF_MODE.Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:VMID:RLEG_C
 * TRL.RLEG_IP6_SIP_RPF_MODE
 *
 * \details
 * Bit 0: Accept routes with RGID=0
 * Bit 1: Accept routes with RGID=1
 * ...

 *
 * Field: ::VTSS_ANA_L3_SIP_RPF . RLEG_RGID_MASK
 */
#define  VTSS_F_ANA_L3_SIP_RPF_RLEG_RGID_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_L3_SIP_RPF_RLEG_RGID_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_L3_SIP_RPF_RLEG_RGID_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Maximum length for frames routed to this router leg
 *
 * \details
 * Register: \a ANA_L3:VMID:MAX_LEN
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_MAX_LEN(gi)              VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,7)

/**
 * \brief
 * Max "Payload Length" (ref. RFC2460) of IPv6 frames using this egress
 * router leg.Note that for frames being encapsulated in an additional IPv4
 * layer, the IP6_MAX_LEN parmeter is the maximum length of the inner IP
 * layer. Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.IP6_LEN_REDIRANA_L3:COMMON:CPU_QU_C
 * FG.CPU_IP_LEN_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_MAX_LEN . IP6_MAX_LEN
 */
#define  VTSS_F_ANA_L3_MAX_LEN_IP6_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ANA_L3_MAX_LEN_IP6_MAX_LEN     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ANA_L3_MAX_LEN_IP6_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Max "Total Length" (ref. RFC791) of IPv4 frames using this egress router
 * leg.Note that for frames being encapsulated in an additional IPv4 layer,
 * the IP4_MAX_LEN parmeter is the maximum length of the inner IP
 * layer.Related
 * parameters:ANA_L3:COMMON:ROUTING_CFG.IP4_LEN_REDIRANA_L3:COMMON:CPU_QU_C
 * FG.CPU_IP_LEN_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_MAX_LEN . IP4_MAX_LEN
 */
#define  VTSS_F_ANA_L3_MAX_LEN_IP4_MAX_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_ANA_L3_MAX_LEN_IP4_MAX_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_ANA_L3_MAX_LEN_IP4_MAX_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Parameters related to IP-in-IP encapsulation.
 *
 * \details
 * Register: \a ANA_L3:VMID:VMID_ENCAP
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_VMID_ENCAP(gi)           VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,8)

/**
 * \brief
 * Index into REW:ENCAP_IP4 when encapsulating IP packet in IPv4.Disabled
 * when set to 0.Note that ENCAP_ID can also be controlled
 * usingANA_L3:ARP:ARP_ENCAP.ENCAP_ID (IP UC only)LPM action of type
 * ARP_ENTRY (IP UC only)ANA_L3:L3MC:EVMID_MASK_CFG by setting
 * EVMID_MASK_MODE=2 (IP MC only)LPM action of type L3MC_PTR (IP MC only)
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_ENCAP . ENCAP_ID
 */
#define  VTSS_F_ANA_L3_VMID_ENCAP_ENCAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_L3_VMID_ENCAP_ENCAP_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_L3_VMID_ENCAP_ENCAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Encapsulation type accepted when decapsulation is enabled for router
 * leg.For non-zero values only frames with matching IP_ENCAP_TYPE are
 * accepted.Frames with encapsulation type mismatch may optionally be
 * redirected to CPU.For frames with GRE checksum, GRE_CHKSUM_SKIP controls
 * whether to verify the checksum.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * SIP_IDANA_L3:ARP:ARP_ENCAP.SIP_IDANA_L3:COMMON:ROUTING_CFG2.IP4_DECAP_RE
 * DIR_ENAANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QUANA_L3:LPM_REMAP_STICKY:
 * L3_LPM_REMAP_STICKY.DECAP_WRONG_IP_ENCAP_TYPE_STICKYANA_L3:LPM_REMAP_STI
 * CKY:L3_LPM_REMAP_STICKY.DECAP_BUT_NO_ENCAP_STICKYANA_L3:VMID:VMID_ENCAP.
 * GRE_CHKSUM_SKIP
 *
 * \details
 * 0: Any encapsulation is accepted, i.e. encapsulation type check
 * disabled.
 * 1: Only IP protocol 4 encapsulation (IPv4) is accepted.
 * 2: Only IP protocol 41 encapsulation (IPv6) is accepted.
 * 3: Only GRE encapsulation of IPv4/6 without checksum is accepted.
 * 4: Only GRE encapsulation with checksum of IPv4/6  is accepted.
 * 5: Only GRE encapsulation with or without checksum of IPv4/6  is
 * accepted.

 *
 * Field: ::VTSS_ANA_L3_VMID_ENCAP . DECAP_IP_ENCAP_TYPE
 */
#define  VTSS_F_ANA_L3_VMID_ENCAP_DECAP_IP_ENCAP_TYPE(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_ANA_L3_VMID_ENCAP_DECAP_IP_ENCAP_TYPE     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_ANA_L3_VMID_ENCAP_DECAP_IP_ENCAP_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Decapsulate IP-in-IP frames forwarded on this (egress) router
 * leg.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_IP_ENCAP_TYPEANA_L3:VMID:VMID_EN
 * CAP.DECAP_SIP_IDANA_L3:ARP:ARP_ENCAP.SIP_IDANA_L3:COMMON:ROUTING_CFG2.IP
 * 4_DECAP_REDIR_ENAANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_ENCAP . DECAP_ENA
 */
#define  VTSS_F_ANA_L3_VMID_ENCAP_DECAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_VMID_ENCAP_DECAP_ENA   VTSS_BIT(15)
#define  VTSS_X_ANA_L3_VMID_ENCAP_DECAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Expected SIP_ID when decapsulating.For non-zero values of DECAP_SIP_ID
 * only frames with matching SIP_ID are accepted.Frames with SIP_ID
 * mismatch may optionally be redirected to CPU.When DECAP_SIP_ID is used,
 * IPx_SIP_LOOKUP_ENA must be set to 1.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:ARP:ARP_ENCAP.SIP_IDANA_L3:COMMON:ROUTING_CFG2.IP4_D
 * ECAP_REDIR_ENAANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QUANA_L3:LPM_REMAP_
 * STICKY:L3_LPM_REMAP_STICKY.DECAP_WRONG_SIP_ID_STICKYANA_L3:COMMON:ROUTIN
 * G_CFG2.IP4_SIP_LOOKUP_ENA
 *
 * \details
 * 0: Any SIP_ID is accepted.
 * Other values: Only frames with matching SIP_ID (from ANA_L3:ARP lookup)
 * are accepted.
 *
 * Field: ::VTSS_ANA_L3_VMID_ENCAP . DECAP_SIP_ID
 */
#define  VTSS_F_ANA_L3_VMID_ENCAP_DECAP_SIP_ID(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ANA_L3_VMID_ENCAP_DECAP_SIP_ID     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ANA_L3_VMID_ENCAP_DECAP_SIP_ID(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * For frames, which contain a GRE checksum and which are to be
 * decapsulated, do not verify the GRE checksum.I.e. such frames are
 * forwarded normally regardless of whether checksum is correct.Default is
 * to verify GRE checksum, if present, and discard frame if the checksum is
 * incorrect.This parameter only applies if DECAP_ENA=1 and
 * DECAP_IP_ENCAP_TYPE specifies acceptance of GRE frames.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:LPM_REMAP_STICKY:L3_LPM_REMAP_STICKY.DECAP_BAD_GRE_C
 * HKSUM_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_ENCAP . GRE_CHKSUM_SKIP
 */
#define  VTSS_F_ANA_L3_VMID_ENCAP_GRE_CHKSUM_SKIP(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_ANA_L3_VMID_ENCAP_GRE_CHKSUM_SKIP  VTSS_BIT(28)
#define  VTSS_X_ANA_L3_VMID_ENCAP_GRE_CHKSUM_SKIP(x)  VTSS_EXTRACT_BITFIELD(x,28,1)


/**
 * \brief Miscellaneous router leg parameters
 *
 * \details
 * Register: \a ANA_L3:VMID:VMID_MISC
 *
 * @param gi Replicator: x_FFL_CHIP_RLEG_CNT (??), 0-14
 */
#define VTSS_ANA_L3_VMID_MISC(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10e00,gi,16,0,9)

/**
 * \brief
 * VCAP_S2 key selection in ANA_ACL:KEY_SEL used by the ingress router
 * leg.Note that the actual index into KEY_SEL is calculated as
 * followsIRLEG_S2_KEY_SEL_IDX+35It is recommended to reserve KEY_SEL_IDX=0
 * to signal "unspecified", since this is the default value for both
 * IRLEG_S2_KEY_SEL_IDX and ERLEG_S2_KEY_SEL_IDX.Related
 * parameters:ANA_ACL:KEY_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_MISC . IRLEG_S2_KEY_SEL_IDX
 */
#define  VTSS_F_ANA_L3_VMID_MISC_IRLEG_S2_KEY_SEL_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_L3_VMID_MISC_IRLEG_S2_KEY_SEL_IDX     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_L3_VMID_MISC_IRLEG_S2_KEY_SEL_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * VCAP_S2 key selection in ANA_ACL:KEY_SEL used by the egress router
 * leg.Note that the actual index into KEY_SEL is calculated as
 * followsERLEG_S2_KEY_SEL_IDX+35It is recommended to reserve KEY_SEL_IDX=0
 * to signal "unspecified", since this is the default value for both
 * IRLEG_S2_KEY_SEL_IDX and ERLEG_S2_KEY_SEL_IDX.Related
 * parameters:ANA_ACL:KEY_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_MISC . ERLEG_S2_KEY_SEL_IDX
 */
#define  VTSS_F_ANA_L3_VMID_MISC_ERLEG_S2_KEY_SEL_IDX(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_ANA_L3_VMID_MISC_ERLEG_S2_KEY_SEL_IDX     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_ANA_L3_VMID_MISC_ERLEG_S2_KEY_SEL_IDX(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * Router Leg Service Index for egress router leg.If RSDX is different from
 * 0, then ANA_L2:ISDX[RSDX] will be read.Among others this can be used to
 * control QGRP_IDX per egress router leg.Related
 * parameters:ANA_L2:ISDXANA_L3:ARP:ARP_MISC.RSDX
 *
 * \details
 * Field: ::VTSS_ANA_L3_VMID_MISC . RSDX
 */
#define  VTSS_F_ANA_L3_VMID_MISC_RSDX(x)      VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_ANA_L3_VMID_MISC_RSDX         VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_ANA_L3_VMID_MISC_RSDX(x)      VTSS_EXTRACT_BITFIELD(x,16,5)

/**
 * Register Group: \a ANA_L3:ARP_PTR_REMAP
 *
 * ARP Pointer Remap Table
 */


/**
 * \brief ARP Pointer Remap Configuration
 *
 * \details
 * This information is used for LPM VCAP actions of type ARP_PTR and with
 * ARP_PTR_REMAP_ENA=1.
 *
 * Register: \a ANA_L3:ARP_PTR_REMAP:ARP_PTR_REMAP_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_PTR_REMAP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_PTR_REMAP_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10a40,gi,1,0,0)

/**
 * \brief
 * Address of ARP entry in ARP Table (ANA_L3:ARP).
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_PTR_REMAP_CFG . ARP_PTR
 */
#define  VTSS_F_ANA_L3_ARP_PTR_REMAP_CFG_ARP_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_L3_ARP_PTR_REMAP_CFG_ARP_PTR     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_L3_ARP_PTR_REMAP_CFG_ARP_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Number of Equal Cost Multiple Paths.Overrules any value in LPM VCAP
 * action.The classifier generates an ECMP aggregation code for IPv4 and
 * IPv6 frames. The following protocol fields contribute to the ECMP
 * aggregation code:- Source IP address for IPv4 and IPv6 frames - all bits
 * contribute.- IPv6 flow label - all bits contribute.- TCP/UDP source and
 * destination ports for TCP/UDP frames with no fragments and no IPv4
 * options - all bits contribute.All contributions are 4-bit XOR'ed, and
 * the resulting code is used as ECMP aggregation code to select which path
 * is chosen for a given frame.
 *
 * \details
 * 0: 1 path
 * 1: 2 paths
 * 2: 3 paths
 * ...
 *
 * Field: ::VTSS_ANA_L3_ARP_PTR_REMAP_CFG . ECMP_CNT
 */
#define  VTSS_F_ANA_L3_ARP_PTR_REMAP_CFG_ECMP_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ANA_L3_ARP_PTR_REMAP_CFG_ECMP_CNT     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ANA_L3_ARP_PTR_REMAP_CFG_ECMP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * Register Group: \a ANA_L3:ARP
 *
 * Next-hop table configuration
 */


/**
 * \brief ARP table configuration
 *
 * \details
 * Configuration registers for ARP table
 *
 * Register: \a ANA_L3:ARP:ARP_CFG_0
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_CFG_0(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10c00,gi,8,0,0)

/**
 * \brief
 * 16 most significant bits of MAC address.Used for ARP entry and/or
 * (SMAC,SIP)/(DMAC,DIP) check.Least significant bits are configured in
 * ARP_CFG_1.MAC_LSB.If MAC address for ARP entry is all-zeros, then the
 * frame is redirected to CPU. CPU queue used for such frames is configured
 * in ZERO_DMAC_CPU_QU.The only exception to this are TWAMP PDUs (as
 * classified by ANA_CL) hitting an ARP entry with TWAMP_ROUTING_ENA=1.For
 * such frames it is left to ANA_ACL to decide CPU redirection, regardless
 * of the MAC address being all-zeros.When an ARP entry is used for
 * forwarding into a tunnel through VD2, then the MAC address can be set to
 * any non-zero value.Related
 * parameters:ANA_L3:ARP:ARP_MISC.TWAMP_ROUTING_ENA
 *
 * \details
 * Bit 0: MAC address bit 32
 * ...
 * Bit 15: MAC address bit 47
 *
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . MAC_MSB
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_MAC_MSB(x)   VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_ANA_L3_ARP_CFG_0_MAC_MSB      VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_ANA_L3_ARP_CFG_0_MAC_MSB(x)   VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Routing lookup:Egress router leg (EVMID). Security lookup:VMID value to
 * be matched against VLAN's VMID when SECUR_MATCH_VMID_ENA is enabled.SIP
 * RPF:Expected ingress VMID if SIP_RPF_ENA==1 and IPv4:
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODE==Rleg ModeIPv6:
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_SIP_RPF_MODE==Rleg Mode
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . ARP_VMID
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_ARP_VMID(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_ANA_L3_ARP_CFG_0_ARP_VMID     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_ANA_L3_ARP_CFG_0_ARP_VMID(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/**
 * \brief
 * CPU queue used for CPU redirect if MAC address in ARP entry is
 * all-zeros.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . ZERO_DMAC_CPU_QU
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_ZERO_DMAC_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ANA_L3_ARP_CFG_0_ZERO_DMAC_CPU_QU     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ANA_L3_ARP_CFG_0_ZERO_DMAC_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Enable use for SIP RPF
 * check.Ref.ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:VMID:RLEG_CT
 * RL.RLEG_IP6_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . SIP_RPF_ENA
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_SIP_RPF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_ARP_CFG_0_SIP_RPF_ENA  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_ARP_CFG_0_SIP_RPF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable Security VMID check. SIP check: If SECUR_MATCH_VMID_ENA=1 and the
 * IVMID is not equal to the VMID in the ARP table (ARP_VMID) when looking
 * up SIP, then the L3_SMAC_SIP_MATCH input to ANA_ACL is deasserted.DIP
 * check: If SECUR_MATCH_VMID_ENA=1 and the IVMID is not equal to the VMID
 * in the ARP table (ARP_VMID) when looking up DIP, then the
 * L3_DMAC_DIP_MATCH input to ANA_ACL is deasserted.DIP check is only
 * performed for L2 forwarded IP unicast frames.Related
 * parameters:ANA_L3:COMMON:SIP_SECURE_ENAANA_L3:COMMON:DIP_SECURE_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . SECUR_MATCH_VMID_ENA
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_SECUR_MATCH_VMID_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_ARP_CFG_0_SECUR_MATCH_VMID_ENA  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_ARP_CFG_0_SECUR_MATCH_VMID_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable Security MAC check. SIP check: If SECUR_MATCH_MAC_ENA=1 and the
 * frame's SMAC is not equal to the MAC in the ARP table (ARP_MAC) when
 * looking up SIP then the L3_SMAC_SIP_MATCH input to ANA_ACL is
 * deasserted.DIP check: If SECUR_MATCH_MAC_ENA=1 and the frame's DMAC is
 * not equal to the MAC in the ARP table (ARP_MAC) when looking up DIP then
 * the L3_DMAC_DIP_MATCH input to ANA_ACL is deasserted.DIP check is only
 * performed for L2 forwarded IP unicast frames.Related
 * parameters:ANA_L3:COMMON:SIP_SECURE_ENAANA_L3:COMMON:DIP_SECURE_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . SECUR_MATCH_MAC_ENA
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_SECUR_MATCH_MAC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_ARP_CFG_0_SECUR_MATCH_MAC_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_ARP_CFG_0_SECUR_MATCH_MAC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable entry for address resolution usage.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_0 . ARP_ENA
 */
#define  VTSS_F_ANA_L3_ARP_CFG_0_ARP_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_ARP_CFG_0_ARP_ENA      VTSS_BIT(0)
#define  VTSS_X_ANA_L3_ARP_CFG_0_ARP_ENA(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ARP table configuration
 *
 * \details
 * Configuration registers for ARP table
 *
 * Register: \a ANA_L3:ARP:ARP_CFG_1
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_CFG_1(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10c00,gi,8,0,1)

/**
 * \brief
 * 32 least significant bits of MAC address.Used for ARP entry and/or
 * (SMAC,SIP)/(DMAC,DIP) check.Most significant bits are configured in
 * ARP_CFG_0.MAC_MSB.If MAC address for ARP entry is all-zeros, then the
 * frame is redirected to CPU. CPU queue used for such frames is configured
 * in ZERO_DMAC_CPU_QU.The only exception to this are TWAMP PDUs (as
 * classified by ANA_CL) hitting an ARP entry with TWAMP_ROUTING_ENA=1.For
 * such frames it is left to ANA_ACL to decide CPU redirection, regardless
 * of the MAC address being all-zeros.When an ARP entry is used for
 * forwarding into a tunnel through VD2, then the MAC address can be set to
 * any non-zero value.Related
 * parameters:ANA_L3:ARP:ARP_MISC.TWAMP_ROUTING_ENA
 *
 * \details
 * Bit 0: MAC bit 0
 * ...
 * Bit 31: MAC bit 31
 *
 * Field: ::VTSS_ANA_L3_ARP_CFG_1 . MAC_LSB
 */
#define  VTSS_F_ANA_L3_ARP_CFG_1_MAC_LSB(x)   (x)
#define  VTSS_M_ANA_L3_ARP_CFG_1_MAC_LSB      0xffffffff
#define  VTSS_X_ANA_L3_ARP_CFG_1_MAC_LSB(x)   (x)


/**
 * \brief ARP table configuration
 *
 * \details
 * Configuration registers for ARP table
 *
 * Register: \a ANA_L3:ARP:ARP_CFG_2
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_CFG_2(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10c00,gi,8,0,2)

/**
 * \brief
 * Disable update of SMAC and DMAC for routed IPv4/IPv6 UC frames.This
 * parameter is for non-standard, proprietary frame processing.This
 * parameter only works when RT_SMAC_UPDATE_ENA=1 and ACL_RT_SEL=1.Related
 * parameters:ANA_L3:L3MC:L3MC_CTRL.L3_MAC_UPDATE_DISANA_L3:COMMON:ROUTING_
 * CFG.RT_SMAC_UPDATE_ENAANA_ACL::VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_2 . L3_MAC_UPDATE_DIS
 */
#define  VTSS_F_ANA_L3_ARP_CFG_2_L3_MAC_UPDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_ARP_CFG_2_L3_MAC_UPDATE_DIS  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_ARP_CFG_2_L3_MAC_UPDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Disable decrement of TTL/Hop Limit for routed IPv4/IPv6 frames.This
 * parameter only works when ACL_RT_SEL=1.This parameter is for
 * non-standard, proprietary frame processing.Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_TTL_DECR_DISANA_L3:VMID:RLEG_C
 * TRL.RLEG_IP6_TTL_DECR_DISANA_L3:L3MC:L3MC_CTRL.TTL_DECR_DISANA_ACL:COMMO
 * N:VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_CFG_2 . TTL_DECR_DIS
 */
#define  VTSS_F_ANA_L3_ARP_CFG_2_TTL_DECR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_ARP_CFG_2_TTL_DECR_DIS  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_ARP_CFG_2_TTL_DECR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Encapsulation/decapsulation parameters
 *
 * \details
 * Register: \a ANA_L3:ARP:ARP_ENCAP
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_ENCAP(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10c00,gi,8,0,3)

/**
 * \brief
 * Index into REW:ENCAP_IP4 when encapsulating IP packet in IPv4.Disabled
 * when set to 0.Note that ENCAP_ID can also be controlled
 * usingANA_L3:VMID:VMID_ENCAP.ENCAP_IDLPM action of type ARP_ENTRY (IP UC
 * only)ANA_L3:L3MC:EVMID_MASK_CFG by setting EVMID_MASK_MODE=2 (IP MC
 * only)LPM action of type L3MC_PTR (IP MC only)
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_ENCAP . ENCAP_ID
 */
#define  VTSS_F_ANA_L3_ARP_ENCAP_ENCAP_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_L3_ARP_ENCAP_ENCAP_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_L3_ARP_ENCAP_ENCAP_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * SIP_ID, used for validating SIP when decapsulating.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:VMID:VMID_ENCAP.DECAP_SIP_IDANA_L3:COMMON:ROUTING_CF
 * G2.IP4_DECAP_REDIR_ENAANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QUANA_L3:LP
 * M_REMAP_STICKY:L3_LPM_REMAP_STICKY.DECAP_WRONG_SIP_ID_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_ENCAP . SIP_ID
 */
#define  VTSS_F_ANA_L3_ARP_ENCAP_SIP_ID(x)    VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ANA_L3_ARP_ENCAP_SIP_ID       VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ANA_L3_ARP_ENCAP_SIP_ID(x)    VTSS_EXTRACT_BITFIELD(x,16,8)


/**
 * \brief Miscellaneous ARP parameters
 *
 * \details
 * Register: \a ANA_L3:ARP:ARP_MISC
 *
 * @param gi Replicator: x_FFL_ANA_NUM_ARP_ENTRIES (??), 0-63
 */
#define VTSS_ANA_L3_ARP_MISC(gi)             VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10c00,gi,8,0,4)

/**
 * \brief
 * Enable special routing of TWAMP and IP BFD PDUs.Such PDUs are routed to
 * a dummy EVMID+EVLAN to be processed by the reflector.The routing is
 * special in that- Frames with TTL=1 are accepted.- TTL decrement is
 * disabled (regardless of TTL_DECR_DIS).Related
 * parameters:ANA_L3:ARP:ARP_CFG_2.TTL_DECR_DIS
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_MISC . TWAMP_ROUTING_ENA
 */
#define  VTSS_F_ANA_L3_ARP_MISC_TWAMP_ROUTING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_ARP_MISC_TWAMP_ROUTING_ENA  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_ARP_MISC_TWAMP_ROUTING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Router Leg Service Index for ARP table entry.If RSDX is different from
 * 0, then ANA_L2:ISDX[RSDX] will be read.Among others this can be used to
 * control QGRP_IDX per ARP entry.Related
 * parameters:ANA_L2:ISDXANA_L3:VMID:VMID_MISC.RSDX
 *
 * \details
 * Field: ::VTSS_ANA_L3_ARP_MISC . RSDX
 */
#define  VTSS_F_ANA_L3_ARP_MISC_RSDX(x)       VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_L3_ARP_MISC_RSDX          VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_L3_ARP_MISC_RSDX(x)       VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a ANA_L3:L3MC
 *
 * L3 Multicast Table
 */


/**
 * \brief Multicast router leg mask
 *
 * \details
 * Register: \a ANA_L3:L3MC:EVMID_MASK_CFG
 *
 * @param gi Replicator: x_FFL_ANA_L3_IPMC_TABLE_LEN (??), 0-31
 * @param ri Replicator: x_FFL_ANA_EVMID_MASK_RLEG_CNT_DIV32_CEIL (??), 0-3
 */
#define VTSS_ANA_L3_EVMID_MASK_CFG(gi,ri)    VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10b00,gi,8,ri,0)

/**
 * \brief
 * The 4 replications of EVMID_MASK are converted into a bit array of
 * length 128 .In the following termed EVMID_BIT_ARRAY.EVMID_BIT_ARRAY is
 * constructed as follows:for (i = 0; i < 4; i++) {
 * EVMID_BIT_ARRAY[(i+1)*32-1:i*32] = EVMID_MASK_CFG[i].EVMID_MASK;}The
 * interpretation of EVMID_BIT_ARRAY depends on the configured
 * EVMID_MASK_MODE.EVMID_MASK_MODE=0 (a.k.a. "List Simple Mode"):In List
 * Simple Mode, EVMID_BIT_ARRAY holds up to 32 router leg numbers
 * (VMIDs).L3MC_NEXT_PTR can be used to create a linked list of such
 * EVMID_MASKs in order to specify forwarding to more router legs.For the
 * first EVMID_MASK entry in a linked list, the first VMID value
 * (EVMID_BIT_ARRAY[4-1:0]) is used to hold a counter for the total number
 * of VMIDs in the linked list. I.e. the first EVMID_MASK can only specify
 * 31 router leg numbers. This also applies even if the linked list
 * consists of only one EVMID_MASK.The first VMID is located at
 * EVMID_BIT_ARRAY[3:0].The second VMID is located at
 * EVMID_BIT_ARRAY[4*2-1:4]And so forth.If not all VMID values in
 * EVMID_MASK are used, then unused values must be set to 15.Except for the
 * last EVMID_MASK in a linked list, each EVMID_MASK must hold at least two
 * valid VMID values.EVMID_MASK_MODE=1 (a.k.a. "Mask Mode"):In Mask Mode,
 * EVMID_BIT_ARRAY is interpreted as a router leg bit mask with one bit for
 * each router leg.If the bit at position N is set, then a copy has to be
 * sent to router leg N.If the frame has been received on router leg N,
 * then bit N in the EVMID_BIT_ARRAY is ignored (i.e. IP multicast frames
 * are not routed back to the ingress router leg).Mask Mode cannot be used
 * for router leg number 128 and above.L3MC_NEXT_PTR cannot be used with
 * Mask Mode.EVMID_MASK_MODE=2 (a.k.a. "List Encap Mode"):In List Encap
 * Mode, EVMID_BIT_ARRAY is divided into _EVMID_LIST_ENCAP_RLEG_CNT
 * entries, each consisting of (EVMID, RSDX, ENCAP_ID).Bits
 * EVMID_BIT_ARRAY[3:0] are used to hold a counter for the total number of
 * VMIDs in the linked list.  This is only used for the first EVMID_MASK in
 * a linked list and must be set to 0 for any later entries in a linked
 * list.The first EVMID is located right-most in EVMID_BIT_ARRAY[127:4] ,
 * followed by RSDX and then ENCAP_ID.EVMID is 4 bits wide.RSDX is 5 bits
 * wide.ENCAP_ID is 8 bits wide.L3MC_NEXT_PTR can be used to create a
 * linked list of such EVMID_MASKs in order to specify forwarding to more
 * router legs.If not all VMID values in EVMID_MASK are used, then unused
 * values must be set to 15.Except for the last EVMID_MASK in a linked
 * list, each EVMID_MASK must hold at least two valid VMID values.Related
 * parameters:ANA_L3:L3MC:L3MC_CTRL.EVMID_MASK_MODEANA_L3:L3MC:L3MC_NEXT_PT
 * R.L3MC_NEXT_PTR
 *
 * \details
 * Field: ::VTSS_ANA_L3_EVMID_MASK_CFG . EVMID_MASK
 */
#define  VTSS_F_ANA_L3_EVMID_MASK_CFG_EVMID_MASK(x)  (x)
#define  VTSS_M_ANA_L3_EVMID_MASK_CFG_EVMID_MASK     0xffffffff
#define  VTSS_X_ANA_L3_EVMID_MASK_CFG_EVMID_MASK(x)  (x)


/**
 * \brief L3 multicast control register
 *
 * \details
 * L3 multicast control register
 *
 * Register: \a ANA_L3:L3MC:L3MC_CTRL
 *
 * @param gi Replicator: x_FFL_ANA_L3_IPMC_TABLE_LEN (??), 0-31
 */
#define VTSS_ANA_L3_L3MC_CTRL(gi)            VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10b00,gi,8,0,4)

/**
 * \brief
 * Disable update of SMAC for routed IPv4/IPv6 MC frames.This parameter is
 * for non-standard, proprietary frame processing.This parameter only works
 * when RT_SMAC_UPDATE_ENA=1 and ACL_RT_SEL=1.Related
 * parameters:ANA_L3:ARP:ARP_CFG_2.L3_MAC_UPDATE_DISANA_L3:COMMON:ROUTING_C
 * FG.RT_SMAC_UPDATE_ENAANA_ACL::VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . L3_MAC_UPDATE_DIS
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_L3_MAC_UPDATE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_ANA_L3_L3MC_CTRL_L3_MAC_UPDATE_DIS  VTSS_BIT(27)
#define  VTSS_X_ANA_L3_L3MC_CTRL_L3_MAC_UPDATE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Disable decrement of TTL/Hop Limit for routed IPv4/IPv6 frames.This
 * parameter only works when ACL_RT_SEL=1.This parameter is for
 * non-standard, proprietary frame processing.Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_TTL_DECR_DISANA_L3:VMID:RLEG_C
 * TRL.RLEG_IP6_TTL_DECR_DISANA_L3:ARP:ARP_CFG_2.TTL_DECR_DISANA_ACL:COMMON
 * :VCAP_S2_MISC_CTRL.ACL_RT_SEL
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . TTL_DECR_DIS
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_TTL_DECR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_ANA_L3_L3MC_CTRL_TTL_DECR_DIS  VTSS_BIT(26)
#define  VTSS_X_ANA_L3_L3MC_CTRL_TTL_DECR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Controls whether EVMID_MASK shall be interpreted as a router leg mask or
 * as a list of EVMIDs.When multiple ANA_L3:L3MC entries are linked
 * together to form a linked list of EVMIDs, then EVMID_MASK_MODE of all
 * entries must be set to the same value.Mask Mode cannot be used for
 * router leg number 128 and above.Related
 * parameters:ANA_L3:L3MC:EVMID_MASK_CFG.EVMID_MASKANA_L3:L3MC:L3MC_NEXT_PT
 * R.L3MC_NEXT_PTR
 *
 * \details
 * 0: List Simple Mode, i.e. EVMID_MASK holds a list of EVMIDs.
 * 1: Mask Mode, i.e. EVMID_MASK is a router leg mask.
 * 2: List Encap Mode, i.e. EVMID_MASK holds a list of (EVMID, ENCAP_ID,
 * RSDX)s.
 *
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . EVMID_MASK_MODE
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_EVMID_MASK_MODE(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_ANA_L3_L3MC_CTRL_EVMID_MASK_MODE     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_ANA_L3_L3MC_CTRL_EVMID_MASK_MODE(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Expected IVMID if RPF check is enabled, ref. RPF_CHK_ENA.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . RPF_VMID
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_RPF_VMID(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ANA_L3_L3MC_CTRL_RPF_VMID     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ANA_L3_L3MC_CTRL_RPF_VMID(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * CPU queue used for frames redirected due to CPU_REDIR_MODE.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . CPU_QU
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_CPU_QU(x)    VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_ANA_L3_L3MC_CTRL_CPU_QU       VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_ANA_L3_L3MC_CTRL_CPU_QU(x)    VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Redirect/copy frame to CPU.CPU queue used is configured in CPU_QU.
 *
 * \details
 * 0b00: No CPU redirection/copy.
 * 0b01: Copy CPU
 * 0b10: Copy to CPU, skip L3 forwarding but preserve L2 forwarding.
 * 0b11: Redirect to CPU, skip L2 and L3 forwarding.
 *
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . CPU_REDIR_MODE
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_CPU_REDIR_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_L3_L3MC_CTRL_CPU_REDIR_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_L3_L3MC_CTRL_CPU_REDIR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Enable reverse path forwarding check, i.e. only allow routing of frames
 * received on a specific router leg (RPF_VMID), i.e.
 * IVMID=RPF_VMID.Related
 * parameters:ANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STICKY.MC_RPF_FILTER_
 * STICKYANA_L3:COMMON:CPU_QU_CFG.CPU_MC_FAIL_QUNote that this check is a
 * different check than SIP RPF check, ref.
 * ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODEANA_L3:VMID:RLEG_CTRL.RLEG_IP
 * 6_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . RPF_CHK_ENA
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_RPF_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_L3MC_CTRL_RPF_CHK_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_L3MC_CTRL_RPF_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable CPU copy of frames, which are otherwise candidates for routing,
 * but have TTL/HL<2.Such frames are not L3 forwarded, but may still be
 * subject to L2 forwarding.CPU queue used is configured in
 * ANA_L3:COMMON:CPU_QU_CFG.CPU_IP_TTL_FAIL_QU.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_CTRL . IPMC_TTL_COPY_ENA
 */
#define  VTSS_F_ANA_L3_L3MC_CTRL_IPMC_TTL_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_L3MC_CTRL_IPMC_TTL_COPY_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_L3MC_CTRL_IPMC_TTL_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Address of next L3MC entry when using EVMID_MASK_MODE=0.
 *
 * \details
 * Register: \a ANA_L3:L3MC:L3MC_NEXT_PTR
 *
 * @param gi Replicator: x_FFL_ANA_L3_IPMC_TABLE_LEN (??), 0-31
 */
#define VTSS_ANA_L3_L3MC_NEXT_PTR(gi)        VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10b00,gi,8,0,5)

/**
 * \brief
 * Address of next L3MC entry when using EVMID_MASK_MODE=0.A value of 0
 * marks end of linked list.Related
 * parameters:ANA_L3:L3MC:L3MC_CTRL.EVMID_MASK_MODEANA_L3:L3MC:EVMID_MASK_C
 * FG.EVMID_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3MC_NEXT_PTR . L3MC_NEXT_PTR
 */
#define  VTSS_F_ANA_L3_L3MC_NEXT_PTR_L3MC_NEXT_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_ANA_L3_L3MC_NEXT_PTR_L3MC_NEXT_PTR     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_ANA_L3_L3MC_NEXT_PTR_L3MC_NEXT_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a ANA_L3:LPM_REMAP_STICKY
 *
 * Diagnostic information
 */


/**
 * \brief Router Leg Diagnostic
 *
 * \details
 * Diagnostic bits related to longest prefix matching.
 *
 * Register: \a ANA_L3:LPM_REMAP_STICKY:L3_LPM_REMAP_STICKY
 */
#define VTSS_ANA_L3_L3_LPM_REMAP_STICKY      VTSS_IOREG(VTSS_TO_ANA_L3,0x10a3e)

/**
 * \brief
 * Frame shall be forwarded to VD2 (for IP-in-IP encap/decap).
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . VD2_FWD_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_VD2_FWD_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_VD2_FWD_FOUND_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_VD2_FWD_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Frame shall be decapsulated, i.e. outer IP layer to be popped.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . DECAP_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_FOUND_STICKY  VTSS_BIT(14)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Frame processing has resulted in ENCAP_ID!=0.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . ENCAP_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_ENCAP_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_ENCAP_FOUND_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_ENCAP_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * A frame has been discarded due to bad GRE checksum.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . DECAP_BAD_GRE_CHKSUM_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BAD_GRE_CHKSUM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BAD_GRE_CHKSUM_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BAD_GRE_CHKSUM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Egress router leg with DECAP_ENA=1 received frame with invalid IP
 * encapsulation type.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:COMMON:ROUTING_CFG2.IP4_DECAP_REDIR_ENAANA_L3:COMMON
 * :CPU_QU_CFG2.CPU_IP_DECAP_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . DECAP_WRONG_IP_ENCAP_TYPE_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_IP_ENCAP_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_IP_ENCAP_TYPE_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_IP_ENCAP_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Egress router leg with DECAP_ENA=1 received frame with invalid
 * SIP_IP.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * SIP_IDANA_L3:ARP:ARP_ENCAP.SIP_IDANA_L3:COMMON:ROUTING_CFG2.IP4_DECAP_RE
 * DIR_ENAANA_L3:COMMON:CPU_QU_CFG2.CPU_IP_DECAP_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . DECAP_WRONG_SIP_ID_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_SIP_ID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_SIP_ID_STICKY  VTSS_BIT(10)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_WRONG_SIP_ID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Egress router leg with DECAP_ENA=1 received frame with no IP
 * encapsulation.Related
 * parameters:ANA_L3:VMID:VMID_ENCAP.DECAP_ENAANA_L3:VMID:VMID_ENCAP.DECAP_
 * IP_ENCAP_TYPEANA_L3:COMMON:ROUTING_CFG2.IP4_DECAP_REDIR_ENAANA_L3:COMMON
 * :CPU_QU_CFG2.CPU_IP_DECAP_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . DECAP_BUT_NO_ENCAP_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BUT_NO_ENCAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BUT_NO_ENCAP_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_DECAP_BUT_NO_ENCAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * SIP IP6PFX lookup has resulted in match with unsupported action
 * type.Related parameters:ANA_L3:COMMON:ROUTING_CFG2.SIP_IP6PFX_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . WRONG_SIP_IP6PFX_ACTION_TYPE_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_SIP_IP6PFX_ACTION_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_SIP_IP6PFX_ACTION_TYPE_STICKY  VTSS_BIT(8)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_SIP_IP6PFX_ACTION_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DIP IP6PFX lookup has resulted in match with unsupported action
 * type.Related parameters:ANA_L3:COMMON:ROUTING_CFG2.DIP_IP6PFX_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . WRONG_DIP_IP6PFX_ACTION_TYPE_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_DIP_IP6PFX_ACTION_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_DIP_IP6PFX_ACTION_TYPE_STICKY  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_WRONG_DIP_IP6PFX_ACTION_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if an IPv6 SIP security lookup has found a match in LPM lookup.Note
 * that this bit is not set for DIP security LPM lookups
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . SECUR_IP6_LPM_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP6_LPM_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP6_LPM_FOUND_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP6_LPM_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if an IPv4 SIP security lookup has found a match in LPM lookup.Note
 * that this bit is not set for DIP security LPM lookups
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . SECUR_IP4_LPM_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP4_LPM_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP4_LPM_FOUND_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_SECUR_IP4_LPM_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if routing lookup found an IPv6 unicast longest prefix match based
 * on 128 bit LPM lookup.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . LPM_IP6UC_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6UC_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6UC_FOUND_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6UC_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if routing lookup found an IPv4 unicast longest prefix match.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . LPM_IP4UC_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4UC_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4UC_FOUND_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4UC_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if an IPv6 multicast longest prefix match has been found and the
 * returned L3MC_IDX is less than the number of L3MC table entries.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . LPM_IP6MC_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6MC_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6MC_FOUND_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP6MC_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if an IPv4 multicast longest prefix match has been found and the
 * returned L3MC_IDX is less than the number of L3MC table entries.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_LPM_REMAP_STICKY . LPM_IP4MC_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4MC_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4MC_FOUND_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_L3_LPM_REMAP_STICKY_LPM_IP4MC_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_L3:VLAN_ARP_L3MC_STICKY
 *
 * Diagnostic information
 */


/**
 * \brief VLAN Diagnostic
 *
 * \details
 * Register: \a ANA_L3:VLAN_ARP_L3MC_STICKY:VLAN_STICKY
 */
#define VTSS_ANA_L3_VLAN_STICKY              VTSS_IOREG(VTSS_TO_ANA_L3,0x10a80)

/**
 * \brief
 * Set if learning has been denied for a frame due to
 * ANA_L3:COMMON:PORT_LRN_CTRL.PORT_LRN_ENA = 0
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . PORT_LRN_DENY_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_PORT_LRN_DENY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_PORT_LRN_DENY_STICKY  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_VLAN_STICKY_PORT_LRN_DENY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set if a frame has been denied forwarding due to
 * ANA_L3:COMMON:PORT_FWD_CTRL.PORT_FWD_ENA = 0
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . PORT_FWD_DENY_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_PORT_FWD_DENY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_PORT_FWD_DENY_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_L3_VLAN_STICKY_PORT_FWD_DENY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set if MSTP_FWD_MASK has allowed forwarding of a frame.Related
 * parameters:ANA_L3:MSTP:MSTP_FWD_CFG.MSTP_FWD_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . MSTP_FWD_ALLOWED_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_MSTP_FWD_ALLOWED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_MSTP_FWD_ALLOWED_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_VLAN_STICKY_MSTP_FWD_ALLOWED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if a frame has been filtered due to MSTP_FWD_MASK.Related
 * parameters:ANA_L3:MSTP:MSTP_FWD_CFG.MSTP_FWD_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . MSTP_DISCARD_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_MSTP_DISCARD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_MSTP_DISCARD_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_VLAN_STICKY_MSTP_DISCARD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if VLAN_LRN_DIS has denied learning for a frame.Related
 * parameters:ANA_L3:VLAN:VLAN_CFG.VLAN_LRN_DIS
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . VLAN_LRN_DENY_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_VLAN_LRN_DENY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_VLAN_LRN_DENY_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_VLAN_STICKY_VLAN_LRN_DENY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if MSTP_LRN_MASK has denied learning for a frame.Related
 * parameters:ANA_L3:MSTP:MSTP_LRN_CFG.MSTP_LRN_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . MSTP_LRN_DENY_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_MSTP_LRN_DENY_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_MSTP_LRN_DENY_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_VLAN_STICKY_MSTP_LRN_DENY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if MSTP_LRN_MASK has allowed learning for a frame.Related
 * parameters:ANA_L3:MSTP:MSTP_LRN_CFG.MSTP_LRN_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . MSTP_LRN_ALLOWED_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_MSTP_LRN_ALLOWED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_MSTP_LRN_ALLOWED_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_VLAN_STICKY_MSTP_LRN_ALLOWED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if a frame has been classified to a VLAN with an empty port
 * mask.Related parameters:ANA_L3:VLAN:VLAN_MASK_CFG.VLAN_PORT_MASK
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . VLAN_LOOKUP_INVLD_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_VLAN_LOOKUP_INVLD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_VLAN_LOOKUP_INVLD_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_VLAN_STICKY_VLAN_LOOKUP_INVLD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if a frame has been filtered due to VLAN ingress filtering.Related
 * parameters:ANA_L3:COMMON:VLAN_FILTER_CTRL.VLAN_IGR_FILTER_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_STICKY . VLAN_IGR_FILTER_STICKY
 */
#define  VTSS_F_ANA_L3_VLAN_STICKY_VLAN_IGR_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_VLAN_STICKY_VLAN_IGR_FILTER_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_VLAN_STICKY_VLAN_IGR_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief ARP and L3MC table related diagnostic registers
 *
 * \details
 * ARP and L3MC table related diagnostic registers.
 *
 * Register: \a ANA_L3:VLAN_ARP_L3MC_STICKY:L3_ARP_IPMC_STICKY
 */
#define VTSS_ANA_L3_L3_ARP_IPMC_STICKY       VTSS_IOREG(VTSS_TO_ANA_L3,0x10a81)

/**
 * \brief
 * Insufficiently spaced VD0 SoF cells on inbound cell bus observed.This
 * sticky bit must never get set.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . VD0_SOF_CELL_SLOT_DIST_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_VD0_SOF_CELL_SLOT_DIST_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_VD0_SOF_CELL_SLOT_DIST_STICKY  VTSS_BIT(31)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_VD0_SOF_CELL_SLOT_DIST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Too few copies were received for second pass IP MC forwarding.This
 * sticky bit only works for EVMID_MASK_MODE=0.This bit should only be set
 * in special situations such as frame loss due to queue flush.Related
 * parameters:ANA_L3:L3MC:L3MC_CTRL.EVMID_MASK_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . TOO_FEW_IPMC_COPIES_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_TOO_FEW_IPMC_COPIES_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_TOO_FEW_IPMC_COPIES_STICKY  VTSS_BIT(30)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_TOO_FEW_IPMC_COPIES_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * SIP LPM lookup has resulted in match with unsupported action type.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . WRONG_SIP_LPM_ACTION_TYPE_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_SIP_LPM_ACTION_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_SIP_LPM_ACTION_TYPE_STICKY  VTSS_BIT(29)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_SIP_LPM_ACTION_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * DIP or (DIP,SIP) LPM lookup has resulted in match with unsupported
 * action type.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . WRONG_DIP_LPM_ACTION_TYPE_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_DIP_LPM_ACTION_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_DIP_LPM_ACTION_TYPE_STICKY  VTSS_BIT(28)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_WRONG_DIP_LPM_ACTION_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Set if IPv6 SIP RPF check results in a frame not being L3
 * forwarded.Related parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP6_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . IP6_SIP_RPF_FILTER_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_IP6_SIP_RPF_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_IP6_SIP_RPF_FILTER_STICKY  VTSS_BIT(27)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_IP6_SIP_RPF_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Set if IPv4 SIP RPF check results in a frame not being L3
 * forwarded.Related parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_SIP_RPF_MODE
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . IP4_SIP_RPF_FILTER_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_IP4_SIP_RPF_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_IP4_SIP_RPF_FILTER_STICKY  VTSS_BIT(26)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_IP4_SIP_RPF_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Set if IPv4/IPv6 multicast forwarding fails because no there is no
 * router leg  in ANA_L3:L3MC:EVMID_MASK_CFG.EVMID_MASK to forward to.This
 * may happen during normal operation if EVMID_MASK_MODE=0 is used and the
 * ingress router leg is not located within the first EVMID_MASK in a
 * linked list of EVMID_MASKs.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . NO_MC_VMID_AVAIL_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_VMID_AVAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_VMID_AVAIL_STICKY  VTSS_BIT(25)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_VMID_AVAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Set if a frame has exceeded IP4_MAX_LEN/IP6_MAX_LEN for an egress router
 * leg.Ref. ANA_L3:VMID:MAX_LEN.IP4_MAX_LENANA_L3:VMID:MAX_LEN.IP6_MAX_LEN
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . IP_MAX_LEN_EXCEEDED_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_IP_MAX_LEN_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_IP_MAX_LEN_EXCEEDED_STICKY  VTSS_BIT(24)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_IP_MAX_LEN_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Set if the IPv4/IPv6 DIP or (DIP,SIP) lookup failed due to - No match in
 * LPM table - Unsupported action type in LPM table- ARP table lookup
 * returns an invalid entry.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . ENTRY_NOT_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_ENTRY_NOT_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_ENTRY_NOT_FOUND_STICKY  VTSS_BIT(23)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_ENTRY_NOT_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Set if an IP MC frame copy from VD0 does not get L3 forwarded (i.e. gets
 * dropped).This may happen during normal operation if EVMID_MASK_MODE=0 is
 * used and the ingress router leg is not located within the first
 * EVMID_MASK in a linked list of EVMID_MASKs.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . MC_LOOPED_CP_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_MC_LOOPED_CP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_MC_LOOPED_CP_STICKY  VTSS_BIT(22)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_MC_LOOPED_CP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Set if neither L2 nor L3 forwarding is performed for an IP multicast
 * frame.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . NO_MC_FWD_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_FWD_STICKY  VTSS_BIT(21)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_NO_MC_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Set when IP multicast L3 forwarding has been completed for a frame.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . L3_MC_FWD_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_L3_MC_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_L3_MC_FWD_STICKY  VTSS_BIT(20)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_L3_MC_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Set if an IP MC frame has failed RPF check.Related
 * parameters:ANA_L3:L3MC:L3MC_CTRL.RPF_CHK_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . MC_RPF_FILTER_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_MC_RPF_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_MC_RPF_FILTER_STICKY  VTSS_BIT(19)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_MC_RPF_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Set when L2 forwarding of IPv4 multicast frame has completed.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . L2_MC_FWD_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_L2_MC_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_L2_MC_FWD_STICKY  VTSS_BIT(18)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_L2_MC_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Set if a frame has been redirected to CPU due to ICMP Redirect check.
 * Related
 * parameters:ANA_L3:VMID:RLEG_CTRL.RLEG_IP4_ICMP_REDIR_ENAANA_L3:VMID:RLEG
 * _CTRL.RLEG_IP6_ICMP_REDIR_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . UC_ICMP_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_UC_ICMP_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_UC_ICMP_REDIR_STICKY  VTSS_BIT(17)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_UC_ICMP_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Set if a frame has been redirected to CPU due to a zero DMAC address in
 * the ARP entry.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . UC_ZERO_DMAC_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_UC_ZERO_DMAC_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_UC_ZERO_DMAC_FOUND_STICKY  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_UC_ZERO_DMAC_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set in case of an IP unicast frame being filtered due to TTL.I.e. a
 * frame with TTL<2 which hits a valid ARP table entry with non-zero MAC
 * address.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . UC_TTL_FILTERING_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_UC_TTL_FILTERING_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_UC_TTL_FILTERING_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_UC_TTL_FILTERING_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set if IP unicast routing lookup results in a valid ARP entry allowing
 * the frame to be routed.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . UC_ENTRY_FOUND_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_UC_ENTRY_FOUND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_UC_ENTRY_FOUND_STICKY  VTSS_BIT(14)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_UC_ENTRY_FOUND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Set if ingress router leg match has been found for an IP multicast frame
 * with a TTL less than 2.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_MC_TTL_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_TTL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_TTL_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_TTL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Set for successful IPv4 SIP security lookup, i.e. matching for
 * (DMAC,SIP) and/or (VMID,SIP).Related
 * parameters:ANA_L3:COMMON:SIP_SECURE_ENA.SIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_IP4_SIP_MATCH_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_SIP_MATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_SIP_MATCH_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_SIP_MATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Set for successful IPv6 DIP security lookup, i.e. matching for
 * (DMAC,DIP) and/or (VMID,DIP).Related
 * parameters:ANA_L3:COMMON:DIP_SECURE_ENA.DIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_IP6_DIP_MATCH_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_DIP_MATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_DIP_MATCH_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_DIP_MATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Set for successful IPv4 DIP security lookup, i.e. matching for
 * (DMAC,DIP) and/or (VMID,DIP).Related
 * parameters:ANA_L3:COMMON:DIP_SECURE_ENA.DIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_IP4_DIP_MATCH_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_DIP_MATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_DIP_MATCH_STICKY  VTSS_BIT(10)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP4_DIP_MATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Set for successful IPv6 SIP security lookup, i.e. matching for
 * (DMAC,SIP) and/or (VMID,SIP).Related
 * parameters:ANA_L3:COMMON:SIP_SECURE_ENA.SIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_IP6_SIP_MATCH_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_SIP_MATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_SIP_MATCH_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_IP6_SIP_MATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Set if security lookup fails for DIP, i.e. mismatch for (DMAC,DIP) /
 * (VMID,DIP).Related parameters:ANA_L3:COMMON:DIP_SECURE_ENA.DIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_DIP_FAIL_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_DIP_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_DIP_FAIL_STICKY  VTSS_BIT(8)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_DIP_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Set if security lookup fails for SIP, i.e. mismatch for (DMAC,DIP) /
 * (VMID,DIP).Related parameters:ANA_L3:COMMON:SIP_SECURE_ENA.SIP_CMP_ENA
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . SECUR_SIP_FAIL_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_SIP_FAIL_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_SIP_FAIL_STICKY  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_SECUR_SIP_FAIL_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if an ingress router leg match has been found for an IP multicast
 * frame.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_MC_HIT_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HIT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HIT_STICKY  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HIT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if an ingress router leg match has been found for an IP unicast
 * frame.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_UC_HIT_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HIT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HIT_STICKY  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HIT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if ingress router leg match has been found for an IPv4/IPv6
 * multicast frame with options/hop-by-hop options. Such frames may
 * optionally be redirected to CPU,
 * ref.ANA_L3:COMMON:ROUTING_CFG.CPU_IP4_OPTIONS_REDIR_ENAANA_L3:COMMON:ROU
 * TING_CFG.CPU_IP6_HOPBYHOP_REDIR_ENAA similar sticky bit is available for
 * IP unicast frames:RLEG_UC_IP_OPT_REDIR_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_MC_IP_OPT_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_IP_OPT_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_IP_OPT_REDIR_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_IP_OPT_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if ingress router leg match has been found for an IPv4/IPv6 unicast
 * frame with options/hop-by-hop options. Such frames may optionally be
 * redirected to CPU,
 * ref.ANA_L3:COMMON:ROUTING_CFG.CPU_IP4_OPTIONS_REDIR_ENAANA_L3:COMMON:ROU
 * TING_CFG.CPU_IP6_HOPBYHOP_REDIR_ENAA similar sticky bit is available for
 * IP multicast frames:RLEG_MC_IP_OPT_REDIR_STICKY
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_UC_IP_OPT_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_IP_OPT_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_IP_OPT_REDIR_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_IP_OPT_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if an ingress router leg match has been found for an IP multicast
 * frame with header errors.Refer to
 * ANA_L3:COMMON:ROUTING_CFG.CPU_RLEG_IP_HDR_FAIL_REDIR_ENAfor list of
 * covered errors.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_MC_HDR_ERR_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HDR_ERR_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HDR_ERR_REDIR_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_MC_HDR_ERR_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if an ingress router leg match has been found for an IP unicast
 * frame with header errors.Refer to
 * ANA_L3:COMMON:ROUTING_CFG.CPU_RLEG_IP_HDR_FAIL_REDIR_ENAfor list of
 * covered errors.
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_UC_HDR_ERR_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HDR_ERR_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HDR_ERR_REDIR_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_UC_HDR_ERR_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if ingress router leg match has been found for a non-IP frame. Such
 * frames are redirected to ANA_L3:COMMON:CPU_QU_CFG.CPU_RLEG_QU
 *
 * \details
 * Field: ::VTSS_ANA_L3_L3_ARP_IPMC_STICKY . RLEG_NONIP_UC_REDIR_STICKY
 */
#define  VTSS_F_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_NONIP_UC_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_NONIP_UC_REDIR_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_L3_ARP_IPMC_STICKY_RLEG_NONIP_UC_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_L3:L3_STICKY_MASK
 *
 * Counter configuration for diagnostic information
 */


/**
 * \brief Enable per concurrent counter for each sticky bit
 *
 * \details
 * Each ANA_L3 sticky bit can be counted in each of the concurrent
 * counters.
 *
 * Register: \a ANA_L3:L3_STICKY_MASK:RLEG_STICKY_MASK
 *
 * @param gi Replicator: x_FFL_ANA_NUM_CONCURRENT_CNTS (??), 0-3
 */
#define VTSS_ANA_L3_RLEG_STICKY_MASK(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10a82,gi,4,0,0)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_UC_IP_OPT_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_IP_OPT_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_IP_OPT_REDIR_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_IP_OPT_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_UC_HIT_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HIT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HIT_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HIT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_UC_HDR_ERR_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HDR_ERR_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HDR_ERR_REDIR_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_UC_HDR_ERR_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_MC_TTL_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_TTL_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_TTL_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_TTL_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_MC_IP_OPT_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_IP_OPT_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_IP_OPT_REDIR_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_IP_OPT_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_MC_HIT_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HIT_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HIT_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HIT_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_MC_HDR_ERR_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HDR_ERR_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HDR_ERR_REDIR_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_MC_HDR_ERR_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_RLEG_STICKY_MASK . RLEG_NONIP_UC_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_RLEG_STICKY_MASK_RLEG_NONIP_UC_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_RLEG_STICKY_MASK_RLEG_NONIP_UC_REDIR_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_RLEG_STICKY_MASK_RLEG_NONIP_UC_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Enable per concurrent counter for each sticky bit
 *
 * \details
 * Each ANA_L3 sticky bit can be counted in each of the concurrent
 * counters.
 *
 * Register: \a ANA_L3:L3_STICKY_MASK:ROUT_STICKY_MASK
 *
 * @param gi Replicator: x_FFL_ANA_NUM_CONCURRENT_CNTS (??), 0-3
 */
#define VTSS_ANA_L3_ROUT_STICKY_MASK(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10a82,gi,4,0,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . IP6_SIP_RPF_FILTER_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_IP6_SIP_RPF_FILTER_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_IP6_SIP_RPF_FILTER_STICKY_MASK  VTSS_BIT(17)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_IP6_SIP_RPF_FILTER_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . IP4_SIP_RPF_FILTER_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_IP4_SIP_RPF_FILTER_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_IP4_SIP_RPF_FILTER_STICKY_MASK  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_IP4_SIP_RPF_FILTER_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . NO_MC_VMID_AVAIL_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_NO_MC_VMID_AVAIL_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_NO_MC_VMID_AVAIL_STICKY_MASK  VTSS_BIT(15)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_NO_MC_VMID_AVAIL_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . ENTRY_NOT_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_ENTRY_NOT_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_ENTRY_NOT_FOUND_STICKY_MASK  VTSS_BIT(14)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_ENTRY_NOT_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . MC_LOOPED_CP_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_MC_LOOPED_CP_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_MC_LOOPED_CP_STICKY_MASK  VTSS_BIT(13)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_MC_LOOPED_CP_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . UC_ZERO_DMAC_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_UC_ZERO_DMAC_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_UC_ZERO_DMAC_FOUND_STICKY_MASK  VTSS_BIT(12)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_UC_ZERO_DMAC_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . UC_TTL_FILTERING_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_UC_TTL_FILTERING_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_UC_TTL_FILTERING_STICKY_MASK  VTSS_BIT(11)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_UC_TTL_FILTERING_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . UC_ICMP_REDIR_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_UC_ICMP_REDIR_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_UC_ICMP_REDIR_STICKY_MASK  VTSS_BIT(10)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_UC_ICMP_REDIR_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . UC_ENTRY_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_UC_ENTRY_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_UC_ENTRY_FOUND_STICKY_MASK  VTSS_BIT(9)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_UC_ENTRY_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . NO_MC_FWD_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_NO_MC_FWD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_NO_MC_FWD_STICKY_MASK  VTSS_BIT(8)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_NO_MC_FWD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . L3_MC_FWD_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_L3_MC_FWD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_L3_MC_FWD_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_L3_MC_FWD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . MC_RPF_FILTER_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_MC_RPF_FILTER_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_MC_RPF_FILTER_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_MC_RPF_FILTER_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . L2_MC_FWD_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_L2_MC_FWD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_L2_MC_FWD_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_L2_MC_FWD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . IP_MAX_LEN_EXCEEDED_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_IP_MAX_LEN_EXCEEDED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_IP_MAX_LEN_EXCEEDED_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_IP_MAX_LEN_EXCEEDED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . LPM_IP6UC_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_LPM_IP6UC_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_LPM_IP6UC_FOUND_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_LPM_IP6UC_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . LPM_IP4UC_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_LPM_IP4UC_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_LPM_IP4UC_FOUND_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_LPM_IP4UC_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . LPM_IP6MC_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_LPM_IP6MC_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_LPM_IP6MC_FOUND_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_LPM_IP6MC_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_ROUT_STICKY_MASK . LPM_IP4MC_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_ROUT_STICKY_MASK_LPM_IP4MC_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_ROUT_STICKY_MASK_LPM_IP4MC_FOUND_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_ROUT_STICKY_MASK_LPM_IP4MC_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Enable per concurrent counter for each sticky bit
 *
 * \details
 * Each ANA_L3 sticky bit can be counted in each of the concurrent
 * counters.
 *
 * Register: \a ANA_L3:L3_STICKY_MASK:SECUR_STICKY_MASK
 *
 * @param gi Replicator: x_FFL_ANA_NUM_CONCURRENT_CNTS (??), 0-3
 */
#define VTSS_ANA_L3_SECUR_STICKY_MASK(gi)    VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10a82,gi,4,0,2)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP6_DIP_MATCH_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_DIP_MATCH_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_DIP_MATCH_STICKY_MASK  VTSS_BIT(7)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_DIP_MATCH_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP4_SIP_MATCH_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_SIP_MATCH_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_SIP_MATCH_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_SIP_MATCH_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_SIP_FAIL_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_SIP_FAIL_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_SIP_FAIL_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_SIP_FAIL_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP6_SIP_MATCH_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_SIP_MATCH_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_SIP_MATCH_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_SIP_MATCH_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP6_LPM_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_LPM_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_LPM_FOUND_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP6_LPM_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP4_DIP_MATCH_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_DIP_MATCH_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_DIP_MATCH_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_DIP_MATCH_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_IP4_LPM_FOUND_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_LPM_FOUND_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_LPM_FOUND_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_IP4_LPM_FOUND_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_SECUR_STICKY_MASK . SECUR_DIP_FAIL_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_SECUR_STICKY_MASK_SECUR_DIP_FAIL_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_SECUR_STICKY_MASK_SECUR_DIP_FAIL_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_SECUR_STICKY_MASK_SECUR_DIP_FAIL_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Enable per concurrent counter for each sticky bit
 *
 * \details
 * Each ANA_L3 sticky bit can be counted in each of the concurrent
 * counters.
 *
 * Register: \a ANA_L3:L3_STICKY_MASK:VLAN_MSTP_STICKY_MASK
 *
 * @param gi Replicator: x_FFL_ANA_NUM_CONCURRENT_CNTS (??), 0-3
 */
#define VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_L3,0x10a82,gi,4,0,3)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . PORT_LRN_DENY_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_LRN_DENY_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_LRN_DENY_STICKY_MASK  VTSS_BIT(16)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_LRN_DENY_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . PORT_FWD_DENY_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_FWD_DENY_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_FWD_DENY_STICKY_MASK  VTSS_BIT(15)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_PORT_FWD_DENY_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . MSTP_FWD_ALLOWED_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_FWD_ALLOWED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_FWD_ALLOWED_STICKY_MASK  VTSS_BIT(6)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_FWD_ALLOWED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . MSTP_DISCARD_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_DISCARD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_DISCARD_STICKY_MASK  VTSS_BIT(5)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_DISCARD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . VLAN_LRN_DENY_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LRN_DENY_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LRN_DENY_STICKY_MASK  VTSS_BIT(4)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LRN_DENY_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . MSTP_LRN_DENY_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_DENY_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_DENY_STICKY_MASK  VTSS_BIT(3)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_DENY_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . MSTP_LRN_ALLOWED_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_ALLOWED_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_ALLOWED_STICKY_MASK  VTSS_BIT(2)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_MSTP_LRN_ALLOWED_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . VLAN_LOOKUP_INVLD_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LOOKUP_INVLD_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LOOKUP_INVLD_STICKY_MASK  VTSS_BIT(1)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_LOOKUP_INVLD_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable counting of sticky event per concurrent counter.
 *
 * \details
 * Field: ::VTSS_ANA_L3_VLAN_MSTP_STICKY_MASK . VLAN_IGR_FILTER_STICKY_MASK
 */
#define  VTSS_F_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_IGR_FILTER_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_IGR_FILTER_STICKY_MASK  VTSS_BIT(0)
#define  VTSS_X_ANA_L3_VLAN_MSTP_STICKY_MASK_VLAN_IGR_FILTER_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_ANA_L3_H_ */
