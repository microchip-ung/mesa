// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_VOP_L3_H_
#define _VTSS_FA_REGS_VOP_L3_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a VOP_L3
 *
 * The Versatile OAM MEP Processor (VOP) implements the HW support for
 * implementing OAM MEPs.
 * 
 * The HW support for implementing an OAM MEP is implemented in a sub
 * block, referred to as:
 * Versatile OAM Endpoint (VOE).
 * 
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing.
 * 
 * The VOP includes the following:
 * 
 *  * 1024 Service / Path VOEs
 *  * 65 Port VOEs
 * 
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing using the following register:
 *  * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.VOE_ENA
 * 
 * To configure VOEs configured for Y.1731, use CSR target VOP.
 * To configure VOEs configured for MPLS-TP, use CSR target VOP_MPLS.
 * To configure VOEs configured for L3 OAM, use CSR target VOP_L3.
 * 
 * For VOEs not configured for L3 OAM, the register groups in this target
 * are invalid.
 * 
 * Note that the VOP_L3 CSR target shares the same physical RAM as the VOP
 * CSR target. The RAM is initialized to the VOP CSR target values (Y.1731
 * VOE).
 * Hence the initial values listed in the VOP_L3 are not valid.
 * Prior to using a VOE configured for L3 OAM, all registers must be
 * initialized.
 *
 ***********************************************************************/

/**
 * Register Group: \a VOP_L3:VOE_CONF_L3
 *
 * Configuration per Versatile OAM MEP Endpoint (VOE) for L3 OAM
 */


/** 
 * \brief VOE configuration common between VOE types
 *
 * \details
 * This register is identical in VOE_CONF, VOE_CONF_MPLS, and VOE_CONF_L3.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_COMMON_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_COMMON_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,0)

/** 
 * \brief
 * Configures VOE for Down-MEP or Up-MEP operation.Note:Port VOEs only
 * support Down-MEP functionality. UPMEP_ENA must be set to 0.L3 VOEs only
 * support Up-MEP functionality. UPMEP_ENA must be set to 1.
 *
 * \details 
 * 0: Configure VOE for Down-MEP functionality.
 * 1: Configure VOE for Up-MEP functionality.
 *
 * Field: ::VTSS_VOP_L3_VOE_COMMON_CFG . UPMEP_ENA
 */
#define  VTSS_F_VOP_L3_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_L3_VOE_COMMON_CFG_UPMEP_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_L3_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If another VOE is pointing to this VOE as a Path VOE using the following
 * configuration: * PATH_VOEID * PATH_VOE_ENAthis register MUST be set to
 * '1'.If not this register must be set to '0'.
 *
 * \details 
 * '0': This VOE is not configured as PATH VOE in another VOE.
 * '1': This VOE is configured as PATH VOE in another VOE.
 *
 * Field: ::VTSS_VOP_L3_VOE_COMMON_CFG . VOE_IS_PATH
 */
#define  VTSS_F_VOP_L3_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_L3_VOE_COMMON_CFG_VOE_IS_PATH  VTSS_BIT(12)
#define  VTSS_X_VOP_L3_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * The VOE supports hierarchical LM counting.This implies that when a VOE
 * is processing a frame, it can update the LM counter of the VOE
 * configured at the Server Layer, if a Server Layer exists.Within the
 * scope of the register list, a VOE configured at the Server Layer is
 * referred to as Path VOE.This register is used to assign a Path VOE to
 * the current service VOE.Port VOEs are considered as Server Layer VOEs
 * per default, and can not be assigned at Path VOEs.Assigning a Path VOE
 * to the VOE implies that all frames received by this VOE, will also be
 * counted by the Path VOE indicated by the following register: *
 * PATH_VOEIDThe path VOE must be enabled by asserting the following field:
 *  * PATH_VOE_ENANote, that the VOE assigned as Path VOP must be enabled
 * for Path VOE operation: * VOE_IS_PATH
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_COMMON_CFG . PATH_VOE_ENA
 */
#define  VTSS_F_VOP_L3_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_L3_VOE_COMMON_CFG_PATH_VOE_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_L3_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Assigns a Path VOE to the VOE. See description in PATH_VOE_ENA.Must
 * point to a VOE in the pool of Service VOEs (0 - 1023).
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_COMMON_CFG . PATH_VOEID
 */
#define  VTSS_F_VOP_L3_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,1,10)
#define  VTSS_M_VOP_L3_VOE_COMMON_CFG_PATH_VOEID     VTSS_ENCODE_BITMASK(1,10)
#define  VTSS_X_VOP_L3_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,1,10)

/** 
 * \brief
 * If ESDX counter control is enabled, the VOP will signal disabling of
 * ESDX counting to the REW for OAM frames.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_COMMON_CFG . ESDX_CNT_CTRL_ENA
 */
#define  VTSS_F_VOP_L3_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Misc. VOE control configuration
 *
 * \details
 * This register includes configuration of misc. VOE properties.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_CTRL_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_CTRL_L3(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,1)

/** 
 * \brief
 * The IP version of this VOE (IPv4 or IPv6).
 *
 * \details 
 * 0: IPv4
 * 1: IPv6
 *
 * Field: ::VTSS_VOP_L3_VOE_CTRL_L3 . IP_VERSION
 */
#define  VTSS_F_VOP_L3_VOE_CTRL_L3_IP_VERSION(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_VOE_CTRL_L3_IP_VERSION  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_VOE_CTRL_L3_IP_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enables DMAC check of Rx UDP frames against the VOE MAC configured in: *
 * VOP_L3:VOE_CONF_L3:VOE_MAC_CFGIf the check is enabled and fails, the
 * frame will be discarded and the following sticky bit will be asserted: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_MAC_RX_ERR_STICKYThe frames can
 * optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_CTRL_L3 . VOE_MAC_RX_CHK_ENA
 */
#define  VTSS_F_VOP_L3_VOE_CTRL_L3_VOE_MAC_RX_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_VOE_CTRL_L3_VOE_MAC_RX_CHK_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_VOE_CTRL_L3_VOE_MAC_RX_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables DIP check of Rx UDP frames against the VOE IP configured in: *
 * VOP_L3:VOE_CONF_L3:VOE_IP_CFGIf the check is enabled and fails, the
 * frame will be discarded and the following sticky bit will be asserted: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_IP_RX_ERR_STICKYThe frames can
 * optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_CTRL_L3 . VOE_IP_RX_CHK_ENA
 */
#define  VTSS_F_VOP_L3_VOE_CTRL_L3_VOE_IP_RX_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_VOE_CTRL_L3_VOE_IP_RX_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_VOE_CTRL_L3_VOE_IP_RX_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VOE MAC
 *
 * \details
 * Configures the VOE MAC.
 * 
 * The MAC is split into the following registers:
 * 
 *  * VOE_MAC_CFG: Bits 0-31 (LSB).
 *  * VOE_MAC_CFG1: Bits 32-48 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_MAC_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_MAC_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,2)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_MAC_CFG . VOE_MAC
 */
#define  VTSS_F_VOP_L3_VOE_MAC_CFG_VOE_MAC(x)  (x)
#define  VTSS_M_VOP_L3_VOE_MAC_CFG_VOE_MAC     0xffffffff
#define  VTSS_X_VOP_L3_VOE_MAC_CFG_VOE_MAC(x)  (x)


/** 
 * \brief VOE MAC
 *
 * \details
 * Configures the VOE MAC.
 * 
 * The MAC is split into the following registers:
 * 
 *  * VOE_MAC_CFG: Bits 0-31 (LSB).
 *  * VOE_MAC_CFG1: Bits 32-48 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_MAC_CFG1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_MAC_CFG1(gi)         VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,3)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_MAC_CFG1 . VOE_MAC1
 */
#define  VTSS_F_VOP_L3_VOE_MAC_CFG1_VOE_MAC1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_L3_VOE_MAC_CFG1_VOE_MAC1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_L3_VOE_MAC_CFG1_VOE_MAC1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief VOE IP
 *
 * \details
 * Configures the VOE IP.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in VOE_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * VOE_IP_CFG: Bits 0-31 (LSB).
 *  * VOE_IP_CFG1: Bits 32-63.
 *  * VOE_IP_CFG2: Bits 64-95.
 *  * VOE_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_IP_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_IP_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,4)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_IP_CFG . VOE_IP
 */
#define  VTSS_F_VOP_L3_VOE_IP_CFG_VOE_IP(x)   (x)
#define  VTSS_M_VOP_L3_VOE_IP_CFG_VOE_IP      0xffffffff
#define  VTSS_X_VOP_L3_VOE_IP_CFG_VOE_IP(x)   (x)


/** 
 * \brief VOE IP
 *
 * \details
 * Configures the VOE IP.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in VOE_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * VOE_IP_CFG: Bits 0-31 (LSB).
 *  * VOE_IP_CFG1: Bits 32-63.
 *  * VOE_IP_CFG2: Bits 64-95.
 *  * VOE_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_IP_CFG1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_IP_CFG1(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,5)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_IP_CFG1 . VOE_IP1
 */
#define  VTSS_F_VOP_L3_VOE_IP_CFG1_VOE_IP1(x)  (x)
#define  VTSS_M_VOP_L3_VOE_IP_CFG1_VOE_IP1     0xffffffff
#define  VTSS_X_VOP_L3_VOE_IP_CFG1_VOE_IP1(x)  (x)


/** 
 * \brief VOE IP
 *
 * \details
 * Configures the VOE IP.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in VOE_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * VOE_IP_CFG: Bits 0-31 (LSB).
 *  * VOE_IP_CFG1: Bits 32-63.
 *  * VOE_IP_CFG2: Bits 64-95.
 *  * VOE_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_IP_CFG2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_IP_CFG2(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,6)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_IP_CFG2 . VOE_IP2
 */
#define  VTSS_F_VOP_L3_VOE_IP_CFG2_VOE_IP2(x)  (x)
#define  VTSS_M_VOP_L3_VOE_IP_CFG2_VOE_IP2     0xffffffff
#define  VTSS_X_VOP_L3_VOE_IP_CFG2_VOE_IP2(x)  (x)


/** 
 * \brief VOE IP
 *
 * \details
 * Configures the VOE IP.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in VOE_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * VOE_IP_CFG: Bits 0-31 (LSB).
 *  * VOE_IP_CFG1: Bits 32-63.
 *  * VOE_IP_CFG2: Bits 64-95.
 *  * VOE_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:VOE_IP_CFG3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_VOE_IP_CFG3(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,7)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_VOE_IP_CFG3 . VOE_IP3
 */
#define  VTSS_F_VOP_L3_VOE_IP_CFG3_VOE_IP3(x)  (x)
#define  VTSS_M_VOP_L3_VOE_IP_CFG3_VOE_IP3     0xffffffff
#define  VTSS_X_VOP_L3_VOE_IP_CFG3_VOE_IP3(x)  (x)


/** 
 * \brief Peer IP
 *
 * \details
 * Configures the Peer IP per UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in PEER_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * PEER_IP_CFG: Bits 0-31 (LSB).
 *  * PEER_IP_CFG1: Bits 32-63.
 *  * PEER_IP_CFG2: Bits 64-95.
 *  * PEER_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:PEER_IP_SESSION_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_PEER_IP_SESSION_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,8)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_PEER_IP_SESSION_CFG . PEER_IP
 */
#define  VTSS_F_VOP_L3_PEER_IP_SESSION_CFG_PEER_IP(x)  (x)
#define  VTSS_M_VOP_L3_PEER_IP_SESSION_CFG_PEER_IP     0xffffffff
#define  VTSS_X_VOP_L3_PEER_IP_SESSION_CFG_PEER_IP(x)  (x)


/** 
 * \brief Peer IP
 *
 * \details
 * Configures the Peer IP per UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in PEER_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * PEER_IP_CFG: Bits 0-31 (LSB).
 *  * PEER_IP_CFG1: Bits 32-63.
 *  * PEER_IP_CFG2: Bits 64-95.
 *  * PEER_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:PEER_IP_SESSION_CFG1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_PEER_IP_SESSION_CFG1(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,11)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_PEER_IP_SESSION_CFG1 . PEER_IP1
 */
#define  VTSS_F_VOP_L3_PEER_IP_SESSION_CFG1_PEER_IP1(x)  (x)
#define  VTSS_M_VOP_L3_PEER_IP_SESSION_CFG1_PEER_IP1     0xffffffff
#define  VTSS_X_VOP_L3_PEER_IP_SESSION_CFG1_PEER_IP1(x)  (x)


/** 
 * \brief Peer IP
 *
 * \details
 * Configures the Peer IP per UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in PEER_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * PEER_IP_CFG: Bits 0-31 (LSB).
 *  * PEER_IP_CFG1: Bits 32-63.
 *  * PEER_IP_CFG2: Bits 64-95.
 *  * PEER_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:PEER_IP_SESSION_CFG2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_PEER_IP_SESSION_CFG2(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,14)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_PEER_IP_SESSION_CFG2 . PEER_IP2
 */
#define  VTSS_F_VOP_L3_PEER_IP_SESSION_CFG2_PEER_IP2(x)  (x)
#define  VTSS_M_VOP_L3_PEER_IP_SESSION_CFG2_PEER_IP2     0xffffffff
#define  VTSS_X_VOP_L3_PEER_IP_SESSION_CFG2_PEER_IP2(x)  (x)


/** 
 * \brief Peer IP
 *
 * \details
 * Configures the Peer IP per UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 * 
 * The configuration depends on the IP version configured in:
 * 
 *  * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.IP_VERSION
 * 
 * For IPv4, the VOE IP is configured in PEER_IP_CFG.
 * 
 * For IPv6, the IP is split into the following registers:
 * 
 *  * PEER_IP_CFG: Bits 0-31 (LSB).
 *  * PEER_IP_CFG1: Bits 32-63.
 *  * PEER_IP_CFG2: Bits 64-95.
 *  * PEER_IP_CFG3: Bits 96-127 (MSB).
 *
 * Register: \a VOP_L3:VOE_CONF_L3:PEER_IP_SESSION_CFG3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_PEER_IP_SESSION_CFG3(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,17)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_PEER_IP_SESSION_CFG3 . PEER_IP3
 */
#define  VTSS_F_VOP_L3_PEER_IP_SESSION_CFG3_PEER_IP3(x)  (x)
#define  VTSS_M_VOP_L3_PEER_IP_SESSION_CFG3_PEER_IP3     0xffffffff
#define  VTSS_X_VOP_L3_PEER_IP_SESSION_CFG3_PEER_IP3(x)  (x)


/** 
 * \brief UDP session configuration
 *
 * \details
 * Configures the UDP sessions of the VOE. Each VOE supports up to 3
 * sessions.
 * 
 * A UDP session is defined by a UDP port:
 * 
 *  * VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG.UDP_PORT
 * 
 * And must be enabled to be used:
 * 
 *  * VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG.SESSION_ENA
 * 
 * A frame is matched to a session using the UDP destination port for Rx
 * frames and the UDP source port for Tx frames.
 * 
 * If no session is found for a frame, the following sticky bit is
 * asserted:
 * 
 *  * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.UNKNOWN_SESSION_RX_ERR_STICKY
 * 
 * The frames can optionally be extracted to CPU. See:
 * 
 *  * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_EXTR
 *
 * Register: \a VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_UDP_SESSION_CFG(gi,ri)   VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,20)

/** 
 * \brief
 * Configures the UDP port of the UDP session.See
 * VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for details.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_UDP_SESSION_CFG . UDP_PORT
 */
#define  VTSS_F_VOP_L3_UDP_SESSION_CFG_UDP_PORT(x)  VTSS_ENCODE_BITFIELD(x,2,16)
#define  VTSS_M_VOP_L3_UDP_SESSION_CFG_UDP_PORT     VTSS_ENCODE_BITMASK(2,16)
#define  VTSS_X_VOP_L3_UDP_SESSION_CFG_UDP_PORT(x)  VTSS_EXTRACT_BITFIELD(x,2,16)

/** 
 * \brief
 * Enables the UDP session.See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for
 * details.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_UDP_SESSION_CFG . SESSION_ENA
 */
#define  VTSS_F_VOP_L3_UDP_SESSION_CFG_SESSION_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_UDP_SESSION_CFG_SESSION_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_UDP_SESSION_CFG_SESSION_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables SIP check of RX UDP frames against the Peer IP configured in: *
 * VOP_L3:VOE_CONF_L3:PEER_IP_SESSION_CFGIf the check is enabled and fails,
 * the frame will be discarded and the following sticky bit will be
 * asserted: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.PEER_IP_RX_ERR_STICKYThe
 * frames can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_UDP_SESSION_CFG . PEER_IP_RX_CHK_ENA
 */
#define  VTSS_F_VOP_L3_UDP_SESSION_CFG_PEER_IP_RX_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_UDP_SESSION_CFG_PEER_IP_RX_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_UDP_SESSION_CFG_PEER_IP_RX_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TCP configuration
 *
 * \details
 * Configures the TCP behavior of the VOE.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:TCP_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_TCP_CFG(gi)              VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,23)

/** 
 * \brief
 * TCP frames that hit the VOE are discarded, but can optionally be
 * extracted to CPU by asserting this register.The frames are extracted to
 * the CPU queue configured in: * VOP:COMMON:CPU_EXTR_L3.TCP_CPU_QU
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TCP_CFG . TCP_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_L3_TCP_CFG_TCP_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_TCP_CFG_TCP_CPU_COPY_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_TCP_CFG_TCP_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If this register is asserted, TCP frames are counted in the data
 * counters.The data counters are located:Service
 * VOE:---------------------Egress:
 * REW:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSBIngress:
 * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSBPort
 * VOE:-------------------Egress:
 * REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSBIngress:
 * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TCP_CFG . TCP_CNT_DATA_ENA
 */
#define  VTSS_F_VOP_L3_TCP_CFG_TCP_CNT_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_TCP_CFG_TCP_CNT_DATA_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_TCP_CFG_TCP_CNT_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VOE TWAMP configuration
 *
 * \details
 * Configures the TWAMP configuration that is common for all UDP sessions.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:TWAMP_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_TWAMP_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,0,24)

/** 
 * \brief
 * Configures the Error Estimate field that is inserted into Tx TWAMP
 * frames.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_CFG . TWAMP_ERROR_ESTIMATE
 */
#define  VTSS_F_VOP_L3_TWAMP_CFG_TWAMP_ERROR_ESTIMATE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_L3_TWAMP_CFG_TWAMP_ERROR_ESTIMATE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_L3_TWAMP_CFG_TWAMP_ERROR_ESTIMATE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief TWAMP session configuration
 *
 * \details
 * Configures the TWAMP configuration that is specific for each UDP
 * session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:TWAMP_SESSION_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_TWAMP_SESSION_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,25)

/** 
 * \brief
 * Enables hardware modifications of TWAMP frames.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Configures the TWAMP session as either a sender or a responder session.
 *
 * \details 
 * 0: Sender.
 * 1: Responder.
 *
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_MODE
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MODE  VTSS_BIT(5)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Extract valid TWAMP Rx frames to CPU.The frames are extracted to the CPU
 * queue configured in: * VOP:COMMON:CPU_EXTR_L3.TWAMP_CPU_QU
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CPU_COPY_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Update the Sequence Number field in Tx TWAMP frames.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_SEQ_NUM_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_SEQ_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_SEQ_NUM_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_SEQ_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable looping of Rx TWAMP frames.Frames can only be looped in responder
 * sessions, see: * VOP_L3:VOE_CONF_L3:TWAMP_SESSION_CFG.TWAMP_MODELooping
 * also requires that hardware modifications are enabled: *
 * VOP_L3:VOE_CONF_L3:TWAMP_SESSION_CFG.TWAMP_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_LOOPBACK_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_LOOPBACK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_LOOPBACK_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_LOOPBACK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If this register is asserted, TWAMP frames in this session are counted
 * in the data counters.The data counters are located:Service
 * VOE:---------------------Egress:
 * REW:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSBIngress:
 * ANA_AC_OAM_MOD:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSBPort
 * VOE:-------------------Egress:
 * REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSBIngress:
 * ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_CNT_DATA_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CNT_DATA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CNT_DATA_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_CNT_DATA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Check that the Multiplier part of the Error Estimation field (the least
 * significant 8 bits) is not zero in Rx TWAMP frames.If the check is
 * enabled and fails, the frame will be discarded and the following sticky
 * bit will be asserted: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.TWAMP_MULT_RX_ERR_STICKYThe
 * frames can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_SESSION_CFG . TWAMP_MULT_RX_CHK_ENA
 */
#define  VTSS_F_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MULT_RX_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MULT_RX_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_TWAMP_SESSION_CFG_TWAMP_MULT_RX_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Loopback session configuration
 *
 * \details
 * Loopback configuration that is specific for each UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:LOOPBACK_SESSION_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_LOOPBACK_SESSION_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,28)

/** 
 * \brief
 * Used for Down-MEP only - has no effect for Up-MEP.When a frame is
 * looped, the ISDX for the frame will be changed to the value configured
 * in: * LB_ISDXWhen the frame passes through the REW, the value in this
 * register will overwrite the IFH.FWD.ES0_ISDX_KEY_ENA.This allows the
 * value of IFH.FWD.ES0_ISDX_KEY_ENA to reflect the new ISDX of the frame.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG . LB_ES0_ISDX_ENA
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG_LB_ES0_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG_LB_ES0_ISDX_ENA  VTSS_BIT(29)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG_LB_ES0_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * The ISDX value of looped frames will be changed to the value configured
 * in this register.
 *
 * \details 
 * Valid ISDX value: 1-4095
 *
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG . LB_ISDX
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG_LB_ISDX(x)  VTSS_ENCODE_BITFIELD(x,17,12)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG_LB_ISDX     VTSS_ENCODE_BITMASK(17,12)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG_LB_ISDX(x)  VTSS_EXTRACT_BITFIELD(x,17,12)

/** 
 * \brief
 * The UDP destination port of looped frames will be changed to the value
 * configured in this register.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG . LB_UDP_PORT
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG_LB_UDP_PORT(x)  VTSS_ENCODE_BITFIELD(x,1,16)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG_LB_UDP_PORT     VTSS_ENCODE_BITMASK(1,16)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG_LB_UDP_PORT(x)  VTSS_EXTRACT_BITFIELD(x,1,16)

/** 
 * \brief
 * When frames are looped, the DP bits can be cleared or keep their value
 * depending on the setting of this bit.
 *
 * \details 
 * 0: DP bits to be looped with the frame.
 * 1: DP bits are cleared when frame is looped.
 *
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG . CLEAR_DP_ON_LOOP
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG_CLEAR_DP_ON_LOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG_CLEAR_DP_ON_LOOP  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG_CLEAR_DP_ON_LOOP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Loopback session configuration
 *
 * \details
 * Loopback configuration that is specific for each UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_CONF_L3:LOOPBACK_SESSION_CFG1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_LOOPBACK_SESSION_CFG1(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x0,gi,64,ri,31)

/** 
 * \brief
 * The IPv4 TTL/IPv6 hoplimit of looped frames will be changed to the value
 * configured in this register.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG1 . LB_TTL
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG1_LB_TTL(x)  VTSS_ENCODE_BITFIELD(x,9,8)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG1_LB_TTL     VTSS_ENCODE_BITMASK(9,8)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG1_LB_TTL(x)  VTSS_EXTRACT_BITFIELD(x,9,8)

/** 
 * \brief
 * Used for Down-MEP only - has no effect for Up-MEP.The router leg value
 * of looped frames will be changed to the value configured in this
 * register.
 *
 * \details 
 * Valid RLEG value: 0-510
 *
 * Field: ::VTSS_VOP_L3_LOOPBACK_SESSION_CFG1 . LB_RLEG
 */
#define  VTSS_F_VOP_L3_LOOPBACK_SESSION_CFG1_LB_RLEG(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_VOP_L3_LOOPBACK_SESSION_CFG1_LB_RLEG     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_VOP_L3_LOOPBACK_SESSION_CFG1_LB_RLEG(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a VOP_L3:VOE_STAT_L3
 *
 * Per VOE statistics and counters (L3 OAM)
 */


/** 
 * \brief RX TCP Frame Count
 *
 * \details
 * Holds the number of received TCP frames.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:TCP_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_TCP_RX_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,0,0)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TCP_RX_CNT . TCP_RX_CNT
 */
#define  VTSS_F_VOP_L3_TCP_RX_CNT_TCP_RX_CNT(x)  (x)
#define  VTSS_M_VOP_L3_TCP_RX_CNT_TCP_RX_CNT     0xffffffff
#define  VTSS_X_VOP_L3_TCP_RX_CNT_TCP_RX_CNT(x)  (x)


/** 
 * \brief RX TCP Frame Count
 *
 * \details
 * Holds the number of transmitted TCP frames.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:TCP_TX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_TCP_TX_CNT(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,0,1)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TCP_TX_CNT . TCP_TX_CNT
 */
#define  VTSS_F_VOP_L3_TCP_TX_CNT_TCP_TX_CNT(x)  (x)
#define  VTSS_M_VOP_L3_TCP_TX_CNT_TCP_TX_CNT     0xffffffff
#define  VTSS_X_VOP_L3_TCP_TX_CNT_TCP_TX_CNT(x)  (x)


/** 
 * \brief RX UDP Session Frame Count
 *
 * \details
 * Holds the number of received frames in this UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:UDP_SESSION_RX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_UDP_SESSION_RX_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,2)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_UDP_SESSION_RX_CNT . UDP_SESSION_RX_CNT
 */
#define  VTSS_F_VOP_L3_UDP_SESSION_RX_CNT_UDP_SESSION_RX_CNT(x)  (x)
#define  VTSS_M_VOP_L3_UDP_SESSION_RX_CNT_UDP_SESSION_RX_CNT     0xffffffff
#define  VTSS_X_VOP_L3_UDP_SESSION_RX_CNT_UDP_SESSION_RX_CNT(x)  (x)


/** 
 * \brief RX UDP Session Frame Count
 *
 * \details
 * Holds the number of transmitted frames in this UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:UDP_SESSION_TX_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_UDP_SESSION_TX_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,5)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_UDP_SESSION_TX_CNT . UDP_SESSION_TX_CNT
 */
#define  VTSS_F_VOP_L3_UDP_SESSION_TX_CNT_UDP_SESSION_TX_CNT(x)  (x)
#define  VTSS_M_VOP_L3_UDP_SESSION_TX_CNT_UDP_SESSION_TX_CNT     0xffffffff
#define  VTSS_X_VOP_L3_UDP_SESSION_TX_CNT_UDP_SESSION_TX_CNT(x)  (x)


/** 
 * \brief VOE sticky bits with interrupt capability
 *
 * \details
 * The sticky bits in this register will cause a VOE interrupt if the
 * interrupt is enabled by the corresponding enable bit field in:
 * 
 *  * VOP_L3:VOE_STAT_L3:INTR_ENA_L3.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:INTR_STICKY_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_INTR_STICKY_L3(gi)       VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,0,8)

/** 
 * \brief
 * This sticky bit is asserted when a TWAMP frame received by the VOE could
 * not be mapped to a UDP session and is not a TCP frame.See
 * VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.The sticky bit can optionally cause a VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_L3.UNKNOWN_SESSION_RX_ERR_INT_ENAThe frames
 * can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_L3 . UNKNOWN_SESSION_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_L3_UNKNOWN_SESSION_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_L3_UNKNOWN_SESSION_RX_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_INTR_STICKY_L3_UNKNOWN_SESSION_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This sticky bit is asserted when a frame received by the VOE fails the
 * DMAC check. See: * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.VOE_MAC_RX_CHK_ENAThe
 * sticky bit can optionally cause a VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_L3.VOE_MAC_RX_ERR_INT_ENAThe frames can
 * optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_L3 . VOE_MAC_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_L3_VOE_MAC_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_L3_VOE_MAC_RX_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_INTR_STICKY_L3_VOE_MAC_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This sticky bit is asserted when a frame received by the VOE fails the
 * DIP check. See: * VOP_L3:VOE_CONF_L3:VOE_CTRL_L3.VOE_IP_RX_CHK_ENAThe
 * sticky bit can optionally cause a VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_L3.VOE_IP_RX_ERR_INT_ENAThe frames can
 * optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_L3 . VOE_IP_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_L3_VOE_IP_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_L3_VOE_IP_RX_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_INTR_STICKY_L3_VOE_IP_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VOE sticky bit interrupt enable
 *
 * \details
 * The bitfields in this register are interrupt enable for the
 * corresponding sticky bits in the following register:
 * 
 *  * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:INTR_ENA_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_INTR_ENA_L3(gi)          VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,0,9)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.UNKNOWN_SESSION_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_L3 . UNKNOWN_SESSION_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_L3_UNKNOWN_SESSION_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_INTR_ENA_L3_UNKNOWN_SESSION_RX_ERR_INT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_INTR_ENA_L3_UNKNOWN_SESSION_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_MAC_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_L3 . VOE_MAC_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_L3_VOE_MAC_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_INTR_ENA_L3_VOE_MAC_RX_ERR_INT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_INTR_ENA_L3_VOE_MAC_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_IP_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_L3 . VOE_IP_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_L3_VOE_IP_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_INTR_ENA_L3_VOE_IP_RX_ERR_INT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_INTR_ENA_L3_VOE_IP_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief VOE CPU extraction
 *
 * \details
 * Configures the CPU extraction configuration that is common for all UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:EXTRACT_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 */
#define VTSS_VOP_L3_EXTRACT_L3(gi)           VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,0,10)

/** 
 * \brief
 * Is used to configure whether frame extraction on this VOE is implemented
 * as "Hit Me Once" or "Extract all".The extraction can also be enabled for
 * "Auto Hit Me Once".When "Auto Hit Me Once" is enabled, the extraction is
 * always done "Hit Me Once" regardless of the configuration of the
 * 'EXTRACT_HIT_ME_ONCE' bit field.For information on "Auto Hit Me Once"
 * see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * 0: Extract all frames meeting the condition of the extract bits (Extract
 * all).
 * 1: Extract only the next frame which meets the condition of the extract
 * bits (Hit Me once).
 *
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . EXTRACT_HIT_ME_ONCE
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_EXTRACT_HIT_ME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_EXTRACT_HIT_ME_ONCE  VTSS_BIT(9)
#define  VTSS_X_VOP_L3_EXTRACT_L3_EXTRACT_HIT_ME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * The VOE can be configured to extract certain frames with regular
 * intervals using the 2 HMO scan timers (Auto Hit Me Once).When a HMO scan
 * is active, the VOE will update the HMO extraction bits which are
 * configured for the active HMO scan, provided that the currently active
 * HMO SLOT matches the HMO SLOT configured for the VOE.If the current HMO
 * scan matches the HMO_SLOT of an active HMO scan, the VOE will assert the
 * HMO extract bits configured for the active HMO scan.This register
 * configures which of the HMO scan timers that is active for this VOE.HMO
 * scan timer configuration: * VOP::HMO_TIMER_CFG.*
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . HMO_SLOT
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_HMO_SLOT(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_L3_EXTRACT_L3_HMO_SLOT     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_L3_EXTRACT_L3_HMO_SLOT(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.UNKNOWN_SESSION_RX_ERR_STICKYFrames
 * will be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . UNKNOWN_SESSION_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_EXTR  VTSS_BIT(5)
#define  VTSS_X_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_EXTRFor information
 * on "Auto Hit Me Once" see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . UNKNOWN_SESSION_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_HMO_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_L3_EXTRACT_L3_UNKNOWN_SESSION_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_MAC_RX_ERR_STICKYFrames will be
 * extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . VOE_MAC_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_EXTR  VTSS_BIT(3)
#define  VTSS_X_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_EXTRFor information on
 * "Auto Hit Me Once" see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . VOE_MAC_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_HMO_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_EXTRACT_L3_VOE_MAC_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_L3.VOE_IP_RX_ERR_STICKYFrames will be
 * extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . VOE_IP_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_EXTR  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_EXTRFor information on "Auto
 * Hit Me Once" see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_L3 . VOE_IP_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_HMO_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_EXTRACT_L3_VOE_IP_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Session sticky bits with interrupt capability
 *
 * \details
 * The sticky bits in this register will cause a VOE interrupt if the
 * interrupt is enabled by the corresponding enable bit field in:
 * 
 *  * VOP_L3:VOE_STAT_L3:INTR_ENA_SESSION_L3.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_INTR_STICKY_SESSION_L3(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,11)

/** 
 * \brief
 * This sticky bit is asserted when a frame received by the VOE fails the
 * SIP check. See: *
 * VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG.PEER_IP_RX_CHK_ENAThe sticky bit can
 * optionally cause a VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_SESSION_L3.PEER_IP_RX_ERR_INT_ENAThe frames
 * can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_SESSION_L3 . PEER_IP_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_SESSION_L3_PEER_IP_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_SESSION_L3_PEER_IP_RX_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_INTR_STICKY_SESSION_L3_PEER_IP_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * This sticky bit is asserted when a frame received by the VOE fails the
 * Error Estimate Multiplier check. See: *
 * VOP_L3:VOE_CONF_L3:TWAMP_SESSION_CFG.TWAMP_MULT_RX_CHK_ENAThe sticky bit
 * can optionally cause a VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_SESSION_L3.TWAMP_MULT_RX_ERR_INT_ENAThe
 * frames can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_SESSION_L3 . TWAMP_MULT_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_MULT_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_MULT_RX_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_MULT_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * This sticky bit is asserted when a TWAMP frame received by the VOE has
 * an unexpected Sequence Number.The expected value of the Sequence Number
 * is one higher than the value in this register: *
 * VOP_L3:VOE_STAT_L3:TWAMP_RX_SEQ_NUMThe sticky bit can optionally cause a
 * VOE interrupt. See: *
 * VOP_L3:VOE_STAT_L3:INTR_ENA_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_INT_ENAThe
 * frames can optionally be extracted to CPU. See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_EXTR
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_STICKY_SESSION_L3 . TWAMP_SEQ_NUM_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_INTR_STICKY_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Session sticky bit interrupt enable
 *
 * \details
 * The bitfields in this register are interrupt enable for the
 * corresponding sticky bits in the following register:
 * 
 *  * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.*
 * 
 * If an interrupt is enabled, the interrupt is asserted when the
 * corresponding sticky bit is asserted.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:INTR_ENA_SESSION_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_INTR_ENA_SESSION_L3(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,14)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.PEER_IP_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_SESSION_L3 . PEER_IP_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_SESSION_L3_PEER_IP_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_INTR_ENA_SESSION_L3_PEER_IP_RX_ERR_INT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_INTR_ENA_SESSION_L3_PEER_IP_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.TWAMP_MULT_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_SESSION_L3 . TWAMP_MULT_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_MULT_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_MULT_RX_ERR_INT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_MULT_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When asserted, the following sticky bit will cause a VOE interrupt: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_STICKY
 *
 * \details 
 * Field: ::VTSS_VOP_L3_INTR_ENA_SESSION_L3 . TWAMP_SEQ_NUM_RX_ERR_INT_ENA
 */
#define  VTSS_F_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_INT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_INT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_INTR_ENA_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Session CPU extraction
 *
 * \details
 * Configures the CPU extraction configuration that is specific for each
 * UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_EXTRACT_SESSION_L3(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,17)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.PEER_IP_RX_ERR_STICKYFrames
 * will be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . PEER_IP_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_EXTR  VTSS_BIT(7)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_EXTRFor information
 * on "Auto Hit Me Once" see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . PEER_IP_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_HMO_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_PEER_IP_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * If asserted, the next valid TWAMP frame will be extracted to the
 * CPU.Frames will be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_L3.TWAMP_CPU_QUThe extraction will always be "Hit Me
 * Once", but can also be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_RX_NXT_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_RX_NXT_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_EXTR  VTSS_BIT(5)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_RX_NXT_EXTRFor information
 * on "Auto Hit Me Once" see: * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_RX_NXT_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_HMO_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_RX_NXT_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.TWAMP_MULT_RX_ERR_STICKYFrames
 * will be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_MULT_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_EXTR  VTSS_BIT(3)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_EXTRFor
 * information on "Auto Hit Me Once" see: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_MULT_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_HMO_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_MULT_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If asserted, all frames which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP_L3:VOE_STAT_L3:INTR_STICKY_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_STICKYFra
 * mes will be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG.CPU_ERR_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.EXTRACT_HIT_ME_ONCEThe extraction can also
 * be enabled for "Auto Hit Me Once". See: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_HMO_ENA
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_SEQ_NUM_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_EXTR  VTSS_BIT(1)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_EXTRFor
 * information on "Auto Hit Me Once" see: *
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.HMO_SLOT
 *
 * \details 
 * Field: ::VTSS_VOP_L3_EXTRACT_SESSION_L3 . TWAMP_SEQ_NUM_RX_ERR_HMO_ENA
 */
#define  VTSS_F_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_HMO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_HMO_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_L3_EXTRACT_SESSION_L3_TWAMP_SEQ_NUM_RX_ERR_HMO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief TWAMP RX Sequence Number
 *
 * \details
 * Holds the Sequence Number from the last valid received TWAMP frame in
 * this UDP session.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:TWAMP_RX_SEQ_NUM
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_TWAMP_RX_SEQ_NUM(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,20)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_RX_SEQ_NUM . TWAMP_RX_SEQ_NUM
 */
#define  VTSS_F_VOP_L3_TWAMP_RX_SEQ_NUM_TWAMP_RX_SEQ_NUM(x)  (x)
#define  VTSS_M_VOP_L3_TWAMP_RX_SEQ_NUM_TWAMP_RX_SEQ_NUM     0xffffffff
#define  VTSS_X_VOP_L3_TWAMP_RX_SEQ_NUM_TWAMP_RX_SEQ_NUM(x)  (x)


/** 
 * \brief TWAMP LX Sequence Number
 *
 * \details
 * Holds the Sequence Number from the last transmitted TWAMP frame in this
 * UDP session.
 * 
 * When a TWAMP frame is transmitted, this register will automatically be
 * increased by one before the Sequence Number is updated in the frame.
 * 
 * See VOP_L3:VOE_CONF_L3:UDP_SESSION_CFG for how to configure the UDP
 * sessions.
 *
 * Register: \a VOP_L3:VOE_STAT_L3:TWAMP_TX_SEQ_NUM
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-1088
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_L3_SESSIONS (??), 0-2
 */
#define VTSS_VOP_L3_TWAMP_TX_SEQ_NUM(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP_L3,0x20000,gi,32,ri,23)

/** 
 * \brief
 * See register description.
 *
 * \details 
 * Field: ::VTSS_VOP_L3_TWAMP_TX_SEQ_NUM . TWAMP_TX_SEQ_NUM
 */
#define  VTSS_F_VOP_L3_TWAMP_TX_SEQ_NUM_TWAMP_TX_SEQ_NUM(x)  (x)
#define  VTSS_M_VOP_L3_TWAMP_TX_SEQ_NUM_TWAMP_TX_SEQ_NUM     0xffffffff
#define  VTSS_X_VOP_L3_TWAMP_TX_SEQ_NUM_TWAMP_TX_SEQ_NUM(x)  (x)


#endif /* _VTSS_FA_REGS_VOP_L3_H_ */
