// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_RB_H_
#define _VTSS_LAGUNA_REGS_RB_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a RB
 *
 * \see vtss_target_RB_e
 *
 * RedBox
 *
 ***********************************************************************/

/**
 * Register Group: \a RB:COMMON
 *
 * Miscellaneous configuration parameters
 */


/**
 * \brief Configures how the RB is connected to the TAXI bus
 *
 * \details
 * Register: \a RB:COMMON:TAXI_IF_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_TAXI_IF_CFG(target)          VTSS_IOREG(target,0x0)

/**
 * \brief
 * Control how the right RB port (LREB) is connected:0: The LREB is
 * connected to a TAXI bus port. See LREB_PORT_NO1: The LREB is connected
 * to LREA of the RB located to the right of this RBMust be 0 for the right
 * most RB
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREB_NEXT
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREB_NEXT(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_RB_TAXI_IF_CFG_LREB_NEXT      VTSS_BIT(17)
#define  VTSS_X_RB_TAXI_IF_CFG_LREB_NEXT(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Control how the left RB port (LREA) is connected:0: The LREA is
 * connected to a TAXI bus port. See LREA_PORT_NO1: The LREA is connected
 * to LREB of the RB located to the left of this RBMust be 0 for the left
 * most RB
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREA_NEXT
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREA_NEXT(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_RB_TAXI_IF_CFG_LREA_NEXT      VTSS_BIT(16)
#define  VTSS_X_RB_TAXI_IF_CFG_LREA_NEXT(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * The LREB port is connected to this TAXI bus port number. Must always be
 * configured
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREB_PORT_NO
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREB_PORT_NO(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_RB_TAXI_IF_CFG_LREB_PORT_NO     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_RB_TAXI_IF_CFG_LREB_PORT_NO(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * The LREA port is connected to this TAXI bus port number. Must always be
 * configured
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREA_PORT_NO
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREA_PORT_NO(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_RB_TAXI_IF_CFG_LREA_PORT_NO     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_RB_TAXI_IF_CFG_LREA_PORT_NO(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * The amount of outstanding taxi words towards the LREB device. Set to 0
 * to use full device fifo
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREB_STOP_WM
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREB_STOP_WM(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_RB_TAXI_IF_CFG_LREB_STOP_WM     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_RB_TAXI_IF_CFG_LREB_STOP_WM(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * The amount of outstanding taxi words towards the LREA device. Set to 0
 * to use full device fifo
 *
 * \details
 * Field: ::VTSS_RB_TAXI_IF_CFG . LREA_STOP_WM
 */
#define  VTSS_F_RB_TAXI_IF_CFG_LREA_STOP_WM(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_RB_TAXI_IF_CFG_LREA_STOP_WM     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_RB_TAXI_IF_CFG_LREA_STOP_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Configuration and status for redbox queues. Egress port D have queues 2D and 2D+1, whereas the first contains frame from the first LRE not being the port itself. Ie - queue 2 is frames from port 0 to port 1, queue 5 contains frames from port 1 to port 2.
 *
 * \details
 * Register: \a RB:COMMON:QSYS_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_QSYS_CFG(target)             VTSS_IOREG(target,0x1)

/**
 * \brief
 * Enable queue cut-through
 *
 * \details
 * Field: ::VTSS_RB_QSYS_CFG . QUE_CT_ENA
 */
#define  VTSS_F_RB_QSYS_CFG_QUE_CT_ENA(x)     VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_RB_QSYS_CFG_QUE_CT_ENA        VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_RB_QSYS_CFG_QUE_CT_ENA(x)     VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * Enable expansion slot. This is needed for queues that produce more data
 * in the rewriter than what is enqueued
 *
 * \details
 * Field: ::VTSS_RB_QSYS_CFG . QUE_EXPAND_ENA
 */
#define  VTSS_F_RB_QSYS_CFG_QUE_EXPAND_ENA(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_RB_QSYS_CFG_QUE_EXPAND_ENA     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_RB_QSYS_CFG_QUE_EXPAND_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/**
 * \brief
 * Enable passage of preamble through queue. This is needed for frames
 * going towards the interlink port, and should be disabled for ports
 * facing ethernet devices.
 *
 * \details
 * Field: ::VTSS_RB_QSYS_CFG . QUE_PREAMBLE_PASS_ENA
 */
#define  VTSS_F_RB_QSYS_CFG_QUE_PREAMBLE_PASS_ENA(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_RB_QSYS_CFG_QUE_PREAMBLE_PASS_ENA     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_RB_QSYS_CFG_QUE_PREAMBLE_PASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/**
 * \brief
 * One or more frames have been discarded due to queue overflow
 *
 * \details
 * Field: ::VTSS_RB_QSYS_CFG . QUE_DROP_STICKY
 */
#define  VTSS_F_RB_QSYS_CFG_QUE_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_RB_QSYS_CFG_QUE_DROP_STICKY     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_RB_QSYS_CFG_QUE_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief CPU extraction queue configurations
 *
 * \details
 * Register: \a RB:COMMON:CPU_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_CPU_CFG(target)              VTSS_IOREG(target,0x2)

/**
 * \brief
 * If set, CPU destination is also removed when discarding a frame due to
 * duplicate discard.
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . DUPL_DISC_CPU_ENA
 */
#define  VTSS_F_RB_CPU_CFG_DUPL_DISC_CPU_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_RB_CPU_CFG_DUPL_DISC_CPU_ENA  VTSS_BIT(15)
#define  VTSS_X_RB_CPU_CFG_DUPL_DISC_CPU_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * CPU extraction queue used for mode T.Related
 * parameters:RB::RB_CFG.FWD_MODE_T_ENA
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . MODE_T_CPUQ
 */
#define  VTSS_F_RB_CPU_CFG_MODE_T_CPUQ(x)     VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_RB_CPU_CFG_MODE_T_CPUQ        VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_RB_CPU_CFG_MODE_T_CPUQ(x)     VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * CPU extraction queue used for HSR and PRP supervion frames.Related
 * parameters:RB:PORT:PORT_CFG.HSR_SPV_FWD_SELRB:PORT:PORT_CFG.PRP_SPV_FWD_
 * SEL
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . SPV_CPUQ
 */
#define  VTSS_F_RB_CPU_CFG_SPV_CPUQ(x)        VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_RB_CPU_CFG_SPV_CPUQ           VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_RB_CPU_CFG_SPV_CPUQ(x)        VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * CPU extraction queue used for various HSR related cases.Related
 * parameters:RB:PORT:PORT_CFG.HSR_FILTER_CFG
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . HSR_CPUQ
 */
#define  VTSS_F_RB_CPU_CFG_HSR_CPUQ(x)        VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_RB_CPU_CFG_HSR_CPUQ           VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_RB_CPU_CFG_HSR_CPUQ(x)        VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * CPU extraction queue used for BPDU frames.Related
 * parameters:RB:PORT:BPDU_CFG.BPDU_REDIR_ENA
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . BPDU_CPUQ
 */
#define  VTSS_F_RB_CPU_CFG_BPDU_CPUQ(x)       VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_RB_CPU_CFG_BPDU_CPUQ          VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_RB_CPU_CFG_BPDU_CPUQ(x)       VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * CPU extraction queue used for frames destined to a local host.
 *
 * \details
 * Field: ::VTSS_RB_CPU_CFG . LOCAL_CPUQ
 */
#define  VTSS_F_RB_CPU_CFG_LOCAL_CPUQ(x)      VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_RB_CPU_CFG_LOCAL_CPUQ         VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_RB_CPU_CFG_LOCAL_CPUQ(x)      VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief NetId configurations
 *
 * \details
 * Register: \a RB:COMMON:NETID_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_NETID_CFG(target)            VTSS_IOREG(target,0x3)

/**
 * \brief
 * If set, hardware does not auto-learn entries in the host table
 * (RB:HOST_TBL) for frames subject to NetId filtering.Related
 * paramenters:RB::NETID_CFG.NETID_FILTER_ENA
 *
 * \details
 * Field: ::VTSS_RB_NETID_CFG . NETID_HOST_TBL_DIS
 */
#define  VTSS_F_RB_NETID_CFG_NETID_HOST_TBL_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_RB_NETID_CFG_NETID_HOST_TBL_DIS  VTSS_BIT(12)
#define  VTSS_X_RB_NETID_CFG_NETID_HOST_TBL_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * If set, NetId filtering is applied to traffic towards the interlink. If
 * the frame's NetId is cleared in NETID_MASK, then the interlink is
 * removed as destination for the frame. Forwarding to LRE ports is
 * unaffected of this.
 *
 * \details
 * Field: ::VTSS_RB_NETID_CFG . NETID_FILTER_ENA
 */
#define  VTSS_F_RB_NETID_CFG_NETID_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_RB_NETID_CFG_NETID_FILTER_ENA  VTSS_BIT(11)
#define  VTSS_X_RB_NETID_CFG_NETID_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Allowed NetIds towards the interlink.
 *
 * \details
 * Bit n: If set, frames with NetId n are allowed transmission over the
 * interlink.
 *
 * Field: ::VTSS_RB_NETID_CFG . NETID_MASK
 */
#define  VTSS_F_RB_NETID_CFG_NETID_MASK(x)    VTSS_ENCODE_BITFIELD(x,3,8)
#define  VTSS_M_RB_NETID_CFG_NETID_MASK       VTSS_ENCODE_BITMASK(3,8)
#define  VTSS_X_RB_NETID_CFG_NETID_MASK(x)    VTSS_EXTRACT_BITFIELD(x,3,8)

/**
 * \brief
 * Ring NetId. Used in HSR tags by frames injected into the ring from the
 * RedBox. This is controlled by setting RING_NETID_ENA in IRI at
 * injection.
 *
 * \details
 * Field: ::VTSS_RB_NETID_CFG . RING_NETID
 */
#define  VTSS_F_RB_NETID_CFG_RING_NETID(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_RB_NETID_CFG_RING_NETID       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_RB_NETID_CFG_RING_NETID(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Overall configuration of the RedBox
 *
 * \details
 * Register: \a RB:COMMON:RB_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_RB_CFG(target)               VTSS_IOREG(target,0x4)

/**
 * \brief
 * If set, frames missing an RCT are discarded.Only applicable to HSR-PRP
 * mode.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . RCT_MISSING_DISC_ENA
 */
#define  VTSS_F_RB_RB_CFG_RCT_MISSING_DISC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_RB_RB_CFG_RCT_MISSING_DISC_ENA  VTSS_BIT(19)
#define  VTSS_X_RB_RB_CFG_RCT_MISSING_DISC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * If set, frames received on the interlink are validated against their
 * source entries in the host table. If the host table entry has
 * HOST_ENTRY_PROXY_DAN set, frame must have a valid RCT. Otherwise, frame
 * is discarded. If the host table entry has HOST_ENTRY_PROXY_DAN cleared,
 * frame is considered untagged and any RCT in the frame is ignored.Only
 * applicable to HSR-PRP mode.Related
 * parameters:RB::RB_CFG.RCT_MISSING_DISC_ENARB:HOST_TBL:HOST_ACCESS_CFG_2.
 * HOST_ENTRY_RCT_MISSINGRB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_PROXY_DAN
 * RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_TYPERB:PORT:STICKY.RCT_MISSING_
 * STICKYRB:PORT:STICKY.RCT_MISSING_DISC_STICKY
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . RCT_VALIDATE_ENA
 */
#define  VTSS_F_RB_RB_CFG_RCT_VALIDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_RB_RB_CFG_RCT_VALIDATE_ENA    VTSS_BIT(18)
#define  VTSS_X_RB_RB_CFG_RCT_VALIDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * If set, Node-DAN sources are detected when a valid RCT is received from
 * both LRE A and LRE B. Associated host table entry is then changed from
 * Node-SAN to Node-DAN.Only applicable to PRP-SAN mode.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . DAN_DETECT_ENA
 */
#define  VTSS_F_RB_RB_CFG_DAN_DETECT_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_RB_RB_CFG_DAN_DETECT_ENA      VTSS_BIT(17)
#define  VTSS_X_RB_RB_CFG_DAN_DETECT_ENA(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * If set, RedBox looks for pseudo HSR tags on Interlink used for
 * transferring a sequence number from the switch to the RedBox.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . HSR_SEQNO_ENA
 */
#define  VTSS_F_RB_RB_CFG_HSR_SEQNO_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_RB_RB_CFG_HSR_SEQNO_ENA       VTSS_BIT(16)
#define  VTSS_X_RB_RB_CFG_HSR_SEQNO_ENA(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * If set, IRI is extracted from preamble.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . IRI_ENA
 */
#define  VTSS_F_RB_RB_CFG_IRI_ENA(x)          VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_RB_RB_CFG_IRI_ENA             VTSS_BIT(15)
#define  VTSS_X_RB_RB_CFG_IRI_ENA(x)          VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Configuration of overall PTP encapsulation awareness. Also controls
 * latency through RedBox.Related
 * parameters:RB::PTP_FILTER_CFG.PTP_FILTER_SELRB::PTP_FILTER_CFG.PTP_VID_S
 * ELRB::PTP_FILTER_CFG.PTP_HSR_SELRB::PTP_DATA
 *
 * \details
 * 0: PTP not recognized.
 * 1: PTPoE (DMAC, VID)
 * 2: PTPoIP4oUDP (DMAC, VID, HSR, DIP-IPv4, DPORT)
 * 3: PTPoIP6oUDP (DMAC, VID, HSR, DIP-IPv6, DPORT)

 *
 * Field: ::VTSS_RB_RB_CFG . PTP_AWARE_SEL
 */
#define  VTSS_F_RB_RB_CFG_PTP_AWARE_SEL(x)    VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_RB_RB_CFG_PTP_AWARE_SEL       VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_RB_RB_CFG_PTP_AWARE_SEL(x)    VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * If set, host table entries learned on the interlink cannot be relearned
 * on LRE ports. ADD_PORTMASK_ENA must be cleared at the same time.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . KEEP_INT_ENA
 */
#define  VTSS_F_RB_RB_CFG_KEEP_INT_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_RB_RB_CFG_KEEP_INT_ENA        VTSS_BIT(12)
#define  VTSS_X_RB_RB_CFG_KEEP_INT_ENA(x)     VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Controls the location of a pushed HSR tag with respect to existing VLAN
 * tags.
 *
 * \details
 * 0: Push HSR tag as outer tag.
 * 1: Push HSR tag as middle tag if frame is VLAN tagged; otherwise as
 * outer tag if frame is untagged.
 * 2: Push HSR tag as inner tag if frame is double VLAN tagged; otherwise
 * as middle tag if frame is single VLAN tagged; otherwise as outer tag if
 * frame is untagged.
 * 3: Reserved

 *
 * Field: ::VTSS_RB_RB_CFG . HSR_TAG_SEL
 */
#define  VTSS_F_RB_RB_CFG_HSR_TAG_SEL(x)      VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_RB_RB_CFG_HSR_TAG_SEL         VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_RB_RB_CFG_HSR_TAG_SEL(x)      VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * If set, a frame with a PRP trailer with wrong LanId is accepted as a
 * valid PRP trailer.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . ACCEPT_LANID_ERR_ENA
 */
#define  VTSS_F_RB_RB_CFG_ACCEPT_LANID_ERR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_RB_RB_CFG_ACCEPT_LANID_ERR_ENA  VTSS_BIT(9)
#define  VTSS_X_RB_RB_CFG_ACCEPT_LANID_ERR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * If set, frames destined for destinations listed as local in the host
 * table are redirected to the CPU using CPU queue CPU_CFG.LOCAL_CPUQ.
 * Applies only to frames received on LRE ports.Related parameters:
 * RB::STICKY.LOCAL_DST_REDIR_STICKY.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . LOCAL_DST_REDIR_ENA
 */
#define  VTSS_F_RB_RB_CFG_LOCAL_DST_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_RB_RB_CFG_LOCAL_DST_REDIR_ENA  VTSS_BIT(8)
#define  VTSS_X_RB_RB_CFG_LOCAL_DST_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enables PRP-SAN transparent reception mode for frames to a local hosts
 * (HOST_ENTRY_TYPE == 3) when RedBox operates in PRP-SAN mode
 * (RB_CFG.RB_MODE). In transparent reception mode, the PRP trailer is not
 * popped in an inbound frame destined to a local host.
 *
 * \details
 * 0: Normal reception
 * 1: Transparent reception
 *
 * Field: ::VTSS_RB_RB_CFG . KEEP_PRP_ENA
 */
#define  VTSS_F_RB_RB_CFG_KEEP_PRP_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_RB_RB_CFG_KEEP_PRP_ENA        VTSS_BIT(7)
#define  VTSS_X_RB_RB_CFG_KEEP_PRP_ENA(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enables PRP-SAN duplicate accept mode for frames to or from local hosts
 * (HOST_ENTRY_TYPE == 3) when RedBox operates in PRP-SAN mode
 * (RB_CFG.RB_MODE). In duplicate accept mode, outbound frames from a local
 * host are transmitted unchanged on both LRE ports and inbound frames to a
 * local host are all accepted and unchanged.
 *
 * \details
 * 0: Duplicate discard
 * 1: Duplicate accept
 *
 * Field: ::VTSS_RB_RB_CFG . ACCEPT_MODE_ENA
 */
#define  VTSS_F_RB_RB_CFG_ACCEPT_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_RB_CFG_ACCEPT_MODE_ENA     VTSS_BIT(6)
#define  VTSS_X_RB_RB_CFG_ACCEPT_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enables RedBox forwarding mode T. If cleared, RedBox can be configured
 * to operate in either default mode H, U, or mode X.In Mode T, frames are
 * untagged and always forwarded. No duplicate discard actions.Related
 * parameters:RB:PORT:TBL_CFG.UPD_DISC_TBL_SRC_ENA
 *
 * \details
 * 0: Default mode.
 * 1: T - Transparent mode.
 *
 * Field: ::VTSS_RB_RB_CFG . FWD_MODE_T_ENA
 */
#define  VTSS_F_RB_RB_CFG_FWD_MODE_T_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_RB_CFG_FWD_MODE_T_ENA      VTSS_BIT(4)
#define  VTSS_X_RB_RB_CFG_FWD_MODE_T_ENA(x)   VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Overall RedBox mode of operation defining forwarding of frames and use
 * of duplicate discard.
 *
 * \details
 * 0: PRP-SAN
 * 1: HSR-SAN
 * 2: HSR-PRP
 * 3: HSR-HSR
 *
 * Field: ::VTSS_RB_RB_CFG . RB_MODE
 */
#define  VTSS_F_RB_RB_CFG_RB_MODE(x)          VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_RB_RB_CFG_RB_MODE             VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_RB_RB_CFG_RB_MODE(x)          VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * This field must be set to 1 to enable the RB.
 *
 * This field should be written to 1 before accessing any other RB
 * registers.
 * The reason is that some registers are connected to logic that is not
 * running
 * when RB_ENA is 0 and accessing them will cause timeout on the CSR bus.
 *
 * Normally this field should not be set to 0 again after enabling the RB,
 * since there is no protection against stopping the RB in an incomplete
 * state.
 * Only if the RB is completely idle is it safe to disable the RB again.
 *
 * \details
 * Field: ::VTSS_RB_RB_CFG . RB_ENA
 */
#define  VTSS_F_RB_RB_CFG_RB_ENA(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_RB_CFG_RB_ENA              VTSS_BIT(0)
#define  VTSS_X_RB_RB_CFG_RB_ENA(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Custom TPID value
 *
 * \details
 * Register: \a RB:COMMON:TPID_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Register: TPID_CFG (??), 0-2
 */
#define VTSS_RB_TPID_CFG(target,ri)          VTSS_IOREG(target,0x5 + (ri))

/**
 * \brief
 * VLAN TPIDs.
 *
 * \details
 * Field: ::VTSS_RB_TPID_CFG . TPID_VAL
 */
#define  VTSS_F_RB_TPID_CFG_TPID_VAL(x)       VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_RB_TPID_CFG_TPID_VAL          VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_RB_TPID_CFG_TPID_VAL(x)       VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Supervision frame configuration
 *
 * \details
 * Register: \a RB:COMMON:SPV_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_SPV_CFG(target)              VTSS_IOREG(target,0x8)

/**
 * \brief
 * If set, DMAC is used in supervision frame criteria. If cleared, only
 * EtherType is used.
 *
 * \details
 * Field: ::VTSS_RB_SPV_CFG . DMAC_ENA
 */
#define  VTSS_F_RB_SPV_CFG_DMAC_ENA(x)        VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_RB_SPV_CFG_DMAC_ENA           VTSS_BIT(20)
#define  VTSS_X_RB_SPV_CFG_DMAC_ENA(x)        VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Decision for HSR supervision frames forwarded to interlink. LRE ports
 * are not affected.Related parameters: RB::CPU_CFG.SPV_CPUQ
 *
 * \details
 * 0: No change to forwarding
 * 1: Copy to CPU
 * 2: Redirect to CPU
 * 3: Discard
 *
 * Field: ::VTSS_RB_SPV_CFG . HSR_SPV_INT_FWD_SEL
 */
#define  VTSS_F_RB_SPV_CFG_HSR_SPV_INT_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_RB_SPV_CFG_HSR_SPV_INT_FWD_SEL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_RB_SPV_CFG_HSR_SPV_INT_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * HSR supervision frames are identified with DMAC =
 * 01-15-4E-00-01-<HSR_MAC-LSB> and EtherType = 0x88FB.Related
 * parameters:RB::SPV_CFG.DMAC_ENARB::SPV_CFG.HSR_SPV_INT_FWD_SEL
 *
 * \details
 * Field: ::VTSS_RB_SPV_CFG . HSR_MAC_LSB
 */
#define  VTSS_F_RB_SPV_CFG_HSR_MAC_LSB(x)     VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_RB_SPV_CFG_HSR_MAC_LSB        VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_RB_SPV_CFG_HSR_MAC_LSB(x)     VTSS_EXTRACT_BITFIELD(x,10,8)

/**
 * \brief
 * Decision for PRP supervision frames forwarded to interlink. LRE ports
 * are not affected.Related parameters: RB::CPU_CFG.SPV_CPUQ
 *
 * \details
 * 0: No change to forwarding
 * 1: Copy to CPU
 * 2: Redirect to CPU
 * 3: Discard
 *
 * Field: ::VTSS_RB_SPV_CFG . PRP_SPV_INT_FWD_SEL
 */
#define  VTSS_F_RB_SPV_CFG_PRP_SPV_INT_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_RB_SPV_CFG_PRP_SPV_INT_FWD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_RB_SPV_CFG_PRP_SPV_INT_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * PRP supervision frames are identified with DMAC =
 * 01-15-4E-00-01-<PRP_MAC-LSB> and EtherType = 0x88FB.Related
 * parameters:RB::SPV_CFG.DMAC_ENARB::SPV_CFG.PRP_SPV_INT_FWD_SEL
 *
 * \details
 * Field: ::VTSS_RB_SPV_CFG . PRP_MAC_LSB
 */
#define  VTSS_F_RB_SPV_CFG_PRP_MAC_LSB(x)     VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_RB_SPV_CFG_PRP_MAC_LSB        VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_RB_SPV_CFG_PRP_MAC_LSB(x)     VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief PTP data registers
 *
 * \details
 * Generic registers containing match data for PTP filters.
 * PTPoE filter - 8 filters in total. Filter 0:
 * - PTP_DATA[0]: DMAC[31:0]
 * - PTP_DATA[1][27:0]: VID, DMAC[47:32]
 * PTP_DATA[2] and PTP_DATA[3] for filter 1 etc.
 *
 * PTPoIPv4oUDP filter - 4 filters in total. Filter 0:
 * - PTP_DATA[0]: DMAC[31:0]
 * - PTP_DATA[1][27:0]: VID, DMAC[47:32]
 * - PTP_DATA[2]: IPv4 DIP
 * - PTP_DATA[3][15:0]: DPORT
 * PTP_DATA[4]-PTP_DATA[7] for filter 1 etc.
 *
 * PTPoIPv6oUDP filter - 2 filters in total. Filter 0:
 * - PTP_DATA[0]: DMAC[31:0]
 * - PTP_DATA[1][27:0]: VID, DMAC[47:32]
 * - PTP_DATA[2]: IPv6 DIP[31:0]
 * - PTP_DATA[3]: IPv6 DIP[63:32]
 * - PTP_DATA[4]: IPv6 DIP[95:64]
 * - PTP_DATA[5]: IPv6 DIP[127:96]
 * - PTP_DATA[6][15:0]: DPORT
 * PTP_DATA[8]-PTP_DATA[14] for filter 1.

 *
 * Register: \a RB:COMMON:PTP_DATA
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Replicator: x_RB_CFG_NUM_PTP_DATA (??), 0-15
 */
#define VTSS_RB_PTP_DATA(target,ri)          VTSS_IOREG(target,0x9 + (ri))

/**
 * \brief
 * See register description for details.Related
 * parameters:RB::RB_CFG.PTP_AWARE_SELRB::PTP_FILTER_CFG.PTP_FILTER_SELRB::
 * PTP_FILTER_CFG.PTP_VID_SELRB::PTP_FILTER_CFG.PTP_HSR_SEL
 *
 * \details
 * Field: ::VTSS_RB_PTP_DATA . PTP_DATA
 */
#define  VTSS_F_RB_PTP_DATA_PTP_DATA(x)       (x)
#define  VTSS_M_RB_PTP_DATA_PTP_DATA          0xffffffff
#define  VTSS_X_RB_PTP_DATA_PTP_DATA(x)       (x)


/**
 * \brief PTP filter configurations per filter
 *
 * \details
 * Number of active filters depends on the frame depth of the analysis,
 * which is controlled in RB::RB_CFG.PTP_AWARE_SEL.
 *
 * For PTPoE, 8 filters are available.
 * For PTPoIPv4oUDP, 4 filters are available, indexed 0 through 3.
 * For PTPoIPv6oUDP, 2 filters are available, indexed 0 through 1.

 *
 * Register: \a RB:COMMON:PTP_FILTER_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Replicator: x_RB_CFG_NUM_PTP_FILTERS (??), 0-7
 */
#define VTSS_RB_PTP_FILTER_CFG(target,ri)    VTSS_IOREG(target,0x19 + (ri))

/**
 * \brief
 * Configuration of the L2-HSR filter element, used when enabled in
 * PTP_FILTER_SEL.Related
 * parameters:RB::RB_CFG.PTP_AWARE_SELRB::PTP_FILTER_CFG.PTP_FILTER_SELRB::
 * PTP_FILTER_CFG.PTP_HSR_SELRB::PTP_DATA
 *
 * \details
 * 0: Frame must be HSR-tagged
 * 1: Frame must be HSR-untagged
 *
 * Field: ::VTSS_RB_PTP_FILTER_CFG . PTP_HSR_SEL
 */
#define  VTSS_F_RB_PTP_FILTER_CFG_PTP_HSR_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_PTP_FILTER_CFG_PTP_HSR_SEL  VTSS_BIT(6)
#define  VTSS_X_RB_PTP_FILTER_CFG_PTP_HSR_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configuration of the L2-VID filter element, used when enabled in
 * PTP_FILTER_SEL.Related
 * parameters:RB::RB_CFG.PTP_AWARE_SELRB::PTP_FILTER_CFG.PTP_FILTER_SELRB::
 * PTP_FILTER_CFG.PTP_HSR_SELRB::PTP_DATA
 *
 * \details
 * 0: Frame must be untagged
 * 1: Frame must be VLAN tagged and outermost VID must match the filter's
 * match data.

 *
 * Field: ::VTSS_RB_PTP_FILTER_CFG . PTP_VID_SEL
 */
#define  VTSS_F_RB_PTP_FILTER_CFG_PTP_VID_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_PTP_FILTER_CFG_PTP_VID_SEL  VTSS_BIT(5)
#define  VTSS_X_RB_PTP_FILTER_CFG_PTP_VID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Filter element settings. RB::RB_CFG.PTP_AWARE_SEL defines the overall
 * PTP classification capabilities and L3 and L4 filter elements are only
 * applicable when PTPoIPv4oUDP or PTPoIPv6oUDP are set in
 * PTP_AWARE_SEL.Related
 * parameters:RB::RB_CFG.PTP_AWARE_SELRB::PTP_FILTER_CFG.PTP_VID_SELRB::PTP
 * _FILTER_CFG.PTP_HSR_SELRB::PTP_DATA
 *
 * \details
 * 0: Disabled
 * xxxx1: L2-DMAC enabled (DMAC)
 * xxx1x: L2-VID enabled (VID)
 * xx1xx: L2-HSR enabled (HSR)
 * x1xxx: L3 enabled (DIP)
 * 1xxxx: L4 enabled (DPORT)
 *
 * Field: ::VTSS_RB_PTP_FILTER_CFG . PTP_FILTER_SEL
 */
#define  VTSS_F_RB_PTP_FILTER_CFG_PTP_FILTER_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_RB_PTP_FILTER_CFG_PTP_FILTER_SEL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_RB_PTP_FILTER_CFG_PTP_FILTER_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a RB:PORT
 *
 * Port configurations
 */


/**
 * \brief Learn configurations for tables
 *
 * \details
 * Register: \a RB:PORT:TBL_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_TBL_CFG(target,gi)           VTSS_IOREG_IX(target,0x21,gi,6,0,0)

/**
 * \brief
 * If set, the host table entry's port mask is used for forwarding. Applies
 * to the destination MAC address lookup. If cleared, the port mask is not
 * used.Related parameters:
 * RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_PORTMASK.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . USE_PORTMASK_ENA
 */
#define  VTSS_F_RB_TBL_CFG_USE_PORTMASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_RB_TBL_CFG_USE_PORTMASK_ENA   VTSS_BIT(12)
#define  VTSS_X_RB_TBL_CFG_USE_PORTMASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * If set, the host table entry's port mask is updated with frame's source
 * port by adding it to the existing port mask. Applies to the source MAC
 * address lookup. If cleared, the port mask is set to the new source port.
 * Locked entries are not applicable for port mask updates.Related
 * parameters: RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_PORTMASK.
 *
 * \details
 * 0: HOST_ENTRY_PORTMASK tracks the latest port where the source was seen.
 * 1: HOST_ENTRY_PORTMASK tracks all ports where source has been seen.
 *
 * Field: ::VTSS_RB_TBL_CFG . ADD_PORTMASK_ENA
 */
#define  VTSS_F_RB_TBL_CFG_ADD_PORTMASK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_RB_TBL_CFG_ADD_PORTMASK_ENA   VTSS_BIT(11)
#define  VTSS_X_RB_TBL_CFG_ADD_PORTMASK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If set, frames are subject to duplicate discard.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . DUPL_DISC_ENA
 */
#define  VTSS_F_RB_TBL_CFG_DUPL_DISC_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_RB_TBL_CFG_DUPL_DISC_ENA      VTSS_BIT(10)
#define  VTSS_X_RB_TBL_CFG_DUPL_DISC_ENA(x)   VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * When learning an entry in the host table, the locked flag is set to this
 * configured value.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . HOST_LOCKED
 */
#define  VTSS_F_RB_TBL_CFG_HOST_LOCKED(x)     VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_RB_TBL_CFG_HOST_LOCKED        VTSS_BIT(9)
#define  VTSS_X_RB_TBL_CFG_HOST_LOCKED(x)     VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * When learning an entry in the host table, the type is set to this
 * configured value.
 *
 * \details
 * Same as RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_TYPE.
 *
 * Field: ::VTSS_RB_TBL_CFG . HOST_TYPE
 */
#define  VTSS_F_RB_TBL_CFG_HOST_TYPE(x)       VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_RB_TBL_CFG_HOST_TYPE          VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_RB_TBL_CFG_HOST_TYPE(x)       VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * When learning an entry in the host table, the age interval is set to
 * this configured value.
 *
 * \details
 * Same as RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_AGE_INTERVAL.
 *
 * Field: ::VTSS_RB_TBL_CFG . HOST_AGE_INTERVAL
 */
#define  VTSS_F_RB_TBL_CFG_HOST_AGE_INTERVAL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_TBL_CFG_HOST_AGE_INTERVAL  VTSS_BIT(6)
#define  VTSS_X_RB_TBL_CFG_HOST_AGE_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * If set, the duplicate discard table (RB:DISC_TBL) is updated with source
 * port information for valid frames (FCS valid) preventing frames from
 * being sent to a port where the same frame has been received.
 * UPD_DISC_TBL_SRC_ENA can be used to enable RedBox forwarding mode X.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . UPD_DISC_TBL_SRC_ENA
 */
#define  VTSS_F_RB_TBL_CFG_UPD_DISC_TBL_SRC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_TBL_CFG_UPD_DISC_TBL_SRC_ENA  VTSS_BIT(5)
#define  VTSS_X_RB_TBL_CFG_UPD_DISC_TBL_SRC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If set, the duplicate discard table (RB:DISC_TBL) is updated with
 * new/updated entries.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . UPD_DISC_TBL_ENA
 */
#define  VTSS_F_RB_TBL_CFG_UPD_DISC_TBL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_TBL_CFG_UPD_DISC_TBL_ENA   VTSS_BIT(4)
#define  VTSS_X_RB_TBL_CFG_UPD_DISC_TBL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * If set, the host table (RB:HOST_TBL) is updated with new/updated
 * entries.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . UPD_HOST_TBL_ENA
 */
#define  VTSS_F_RB_TBL_CFG_UPD_HOST_TBL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_RB_TBL_CFG_UPD_HOST_TBL_ENA   VTSS_BIT(3)
#define  VTSS_X_RB_TBL_CFG_UPD_HOST_TBL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If set, the sequence number in RB:HOST_TBL is incremented when used.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . UPD_SEQ_NUM_ENA
 */
#define  VTSS_F_RB_TBL_CFG_UPD_SEQ_NUM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_TBL_CFG_UPD_SEQ_NUM_ENA    VTSS_BIT(2)
#define  VTSS_X_RB_TBL_CFG_UPD_SEQ_NUM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, hardware does not auto-learn new entries in the host table
 * (RB:HOST_TBL). Existing entries (learned by CPU) are updated when used.
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . NEW_HOST_TBL_DIS
 */
#define  VTSS_F_RB_TBL_CFG_NEW_HOST_TBL_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_TBL_CFG_NEW_HOST_TBL_DIS   VTSS_BIT(1)
#define  VTSS_X_RB_TBL_CFG_NEW_HOST_TBL_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If set, hardware does not auto-learn entries for supervision frames in
 * the host table (RB:HOST_TBL).
 *
 * \details
 * Field: ::VTSS_RB_TBL_CFG . SPV_HOST_TBL_DIS
 */
#define  VTSS_F_RB_TBL_CFG_SPV_HOST_TBL_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_TBL_CFG_SPV_HOST_TBL_DIS   VTSS_BIT(0)
#define  VTSS_X_RB_TBL_CFG_SPV_HOST_TBL_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief BPDU handling
 *
 * \details
 * Register: \a RB:PORT:BPDU_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_BPDU_CFG(target,gi)          VTSS_IOREG_IX(target,0x21,gi,6,0,1)

/**
 * \brief
 * Controls CPU redirection to the CPU of reserved DMAC addresses in the
 * range 01-80-C2-00-00-00 to 01-80-C2-00-00-0F. Each bit this fields
 * control a DMAC address: Bit 0 controls address 01-80-C2-00-00-00, bit 1
 * controls address 01-80-C2-00-00-01, and so on. Frames are extracted to
 * the CPU extraction queue defined in CPU_CFG.BPDU_CPUQ.
 *
 * \details
 * 0: No change to forwarding
 * 1: Redirection to CPU
 *
 * Field: ::VTSS_RB_BPDU_CFG . BPDU_REDIR_ENA
 */
#define  VTSS_F_RB_BPDU_CFG_BPDU_REDIR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_RB_BPDU_CFG_BPDU_REDIR_ENA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_RB_BPDU_CFG_BPDU_REDIR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Forwarding configuration
 *
 * \details
 * Forwarding masks per ingress port. Applies to both HSR and PRP, except
 * for frames received on interlink in PRP-SAN mode of operation - such
 * frames are forwarded based on PRP-SAN fowarding rules (port where known
 * Node-SAN recides or both LRE ports).
 *
 * By default, a frame is forwarded to the other two ports in the RedBox.
 * The forwarding masks are used to limit this forwarding by filtering one
 * or more of the ports.
 * For each frame, a source mask and a destination mask are selected based
 * on the entry types retrieved from the lookups in the host table. If
 * there is no match in the host table, a default mask with all ports
 * except the frame's ingress port is used.
 * The forwarding decision is made by AND'ing the forwarding masks with the
 * default forwarding mask.
 *
 * Example: HSR-SAN mode H.
 *
 * Configuration for LRE port 0:
 * - By default, frames are fowarded to LRE port 1 and interlink.
 * - Frames from proxy or local are discarded.
 * - Frames from node are allowed on LRE and interlink.
 * - Frames to proxy or local are allowed on interlink.
 * - Frames to node are allowed on LRE only.
 *
 * PROXY_SRC_FWD_MASK = 0x0
 * LOCAL_SRC_FWD_MASK = 0x0
 * NODE_SRC_FWD_MASK = 0x6
 * PROXY_DST_FWD_MASK = 0x4
 * LOCAL_DST_FWD_MASK = 0x4
 * NODE_DST_FWD_MASK = 0x2
 *
 * Configuration for LRE port 1:
 * - By default, frames are fowarded to LRE port 0 and interlink.
 * - Frames from proxy or local are discarded.
 * - Frames from node are allowed on LRE and interlink.
 * - Frames to proxy or local are allowed on interlink only.
 * - Frames to node are allowed on LRE only.
 *
 * PROXY_SRC_FWD_MASK = 0x0
 * LOCAL_SRC_FWD_MASK = 0x0
 * NODE_SRC_FWD_MASK = 0x5
 * PROXY_DST_FWD_MASK = 0x4
 * LOCAL_DST_FWD_MASK = 0x4
 * NODE_DST_FWD_MASK = 0x1
 *
 * Configuration for Interlink:
 * - By default, frames are fowarded to LRE port 0 and 1.
 * - Frames from proxy or local are allowed on LREs.
 * - Frames from node are discarded.
 * - Frames to proxy or local are discarded.
 * - Frames to node are allowed on LREs.
 *
 * PROXY_SRC_FWD_MASK = 0x3
 * LOCAL_SRC_FWD_MASK = 0x3
 * NODE_SRC_FWD_MASK = 0x0
 * PROXY_DST_FWD_MASK = 0x0
 * LOCAL_DST_FWD_MASK = 0x0
 * NODE_DST_FWD_MASK = 0x3
 *
 * Related parameters: RB:HOST_TBL:HOST_ACCESS_CFG_2.HOST_ENTRY_TYPE.

 *
 * Register: \a RB:PORT:FWD_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_FWD_CFG(target,gi)           VTSS_IOREG_IX(target,0x21,gi,6,0,2)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the destination is listed as a proxy in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is removed if destination is proxy.
 * Bit 1: If cleared, LRE port 1 is removed if destination is proxy.
 * Bit 2: If cleared, interlink is removed if destination is proxy.
 *
 * Field: ::VTSS_RB_FWD_CFG . PROXY_DST_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_PROXY_DST_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_RB_FWD_CFG_PROXY_DST_FWD_MASK     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_RB_FWD_CFG_PROXY_DST_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the destination is listed as a local in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is removed if destination is local.
 * Bit 1: If cleared, LRE port 1 is removed if destination is local.
 * Bit 2: If cleared, interlink is removed if destination is local.
 *
 * Field: ::VTSS_RB_FWD_CFG . LOCAL_DST_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_LOCAL_DST_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_RB_FWD_CFG_LOCAL_DST_FWD_MASK     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_RB_FWD_CFG_LOCAL_DST_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the destination is listed as a node in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is kept as destination if destination is
 * node.
 * Bit 1: If cleared, LRE port 1 is kept as destination if destination is
 * node.
 * Bit 2: If cleared, interlink is kept as destination if destination is
 * node.
 *
 * Field: ::VTSS_RB_FWD_CFG . NODE_DST_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_NODE_DST_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_RB_FWD_CFG_NODE_DST_FWD_MASK     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_RB_FWD_CFG_NODE_DST_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the source is listed as a proxy in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is removed if source is proxy.
 * Bit 1: If cleared, LRE port 1 is removed if source is proxy.
 * Bit 2: If cleared, interlink is removed if source is proxy.
 *
 * Field: ::VTSS_RB_FWD_CFG . PROXY_SRC_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_PROXY_SRC_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_RB_FWD_CFG_PROXY_SRC_FWD_MASK     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_RB_FWD_CFG_PROXY_SRC_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the source is listed as a local in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is removed if source is local.
 * Bit 1: If cleared, LRE port 1 is removed if source is local.
 * Bit 2: If cleared, interlink is removed if source is local.
 *
 * Field: ::VTSS_RB_FWD_CFG . LOCAL_SRC_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_LOCAL_SRC_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_RB_FWD_CFG_LOCAL_SRC_FWD_MASK     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_RB_FWD_CFG_LOCAL_SRC_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Port mask indicating to which egress ports forwarding is applicable when
 * the source is listed as a node in the host table.
 *
 * \details
 * Bit 0: If cleared, LRE port 0 is removed if source is node.
 * Bit 1: If cleared, LRE port 1 is removed if source is node.
 * Bit 2: If cleared, interlink is removed if source is node.
 *
 * Field: ::VTSS_RB_FWD_CFG . NODE_SRC_FWD_MASK
 */
#define  VTSS_F_RB_FWD_CFG_NODE_SRC_FWD_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_RB_FWD_CFG_NODE_SRC_FWD_MASK     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_RB_FWD_CFG_NODE_SRC_FWD_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Port configurations
 *
 * \details
 * Register: \a RB:PORT:PORT_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_PORT_CFG(target,gi)          VTSS_IOREG_IX(target,0x21,gi,6,0,3)

/**
 * \brief
 * Cut-through egress enabling. Cut-through is enabled if source port has
 * cut-through enabled and egress port has cut-through enabled.Related
 * parameters: RB:PORT:PORT_CFG.CT_IGR_ENA.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . CT_EGR_ENA
 */
#define  VTSS_F_RB_PORT_CFG_CT_EGR_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_RB_PORT_CFG_CT_EGR_ENA        VTSS_BIT(22)
#define  VTSS_X_RB_PORT_CFG_CT_EGR_ENA(x)     VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Cut-through ingress enabling. Cut-through is enabled if source port has
 * cut-through enabled and egress port has cut-through enabled.Related
 * parameters: RB:PORT:PORT_CFG.CT_EGR_ENA.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . CT_IGR_ENA
 */
#define  VTSS_F_RB_PORT_CFG_CT_IGR_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_RB_PORT_CFG_CT_IGR_ENA        VTSS_BIT(21)
#define  VTSS_X_RB_PORT_CFG_CT_IGR_ENA(x)     VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Selects egress port's tag mode. TAG_MODE controls popping and pushing of
 * HSR tags and PRP trailers so that egress frames are correctly formatted.
 * For instance, if TAG_MODE==2, an egress frame has exactly one HSR tag
 * (either detected at ingress or pushed by the egress port) and any PRP
 * trailer detected at ingress is popped.Proposed
 * settings:PRP-SAN:Interlink: 0LRE ports: 1HSR-SANInterlink: 0LRE port:
 * 2HSR-PRPInterlink: 3LRE port: 2HSR-HSRInterlink: 2LRE port: 2
 *
 * \details
 * 0: All frames are untagged. Any HSR tags and PRP trailers in incoming
 * frames are popped.
 * 1: Frames are either untagged or contain a PRP-trailer when rfh.push_seq
 * is set. Any HSR tags and PRP trailers in incoming frames are popped.
 * 2: All frames are HSR-tagged. Any PRP trailers in incoming frames are
 * popped.
 * 3: All frames contain a PRP-trailer. Any HSR tags in incoming frames are
 * popped.
 *
 * Field: ::VTSS_RB_PORT_CFG . TAG_MODE
 */
#define  VTSS_F_RB_PORT_CFG_TAG_MODE(x)       VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_RB_PORT_CFG_TAG_MODE          VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_RB_PORT_CFG_TAG_MODE(x)       VTSS_EXTRACT_BITFIELD(x,19,2)

/**
 * \brief
 * If set, HSR tagged frames where the frame's LSDU size does not match the
 * LSDU size indicated in the HSR tag are discarded towards the interlink.
 *
 * \details
 * 0: No action - treat as valid tag.
 * 1: Discard
 *
 * Field: ::VTSS_RB_PORT_CFG . HSR_LSDU_ERR_INT_DISC_ENA
 */
#define  VTSS_F_RB_PORT_CFG_HSR_LSDU_ERR_INT_DISC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_RB_PORT_CFG_HSR_LSDU_ERR_INT_DISC_ENA  VTSS_BIT(18)
#define  VTSS_X_RB_PORT_CFG_HSR_LSDU_ERR_INT_DISC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Configures acceptance filtering of HSR-tagged frames.Related parameters:
 * RB::CPU_CFG.HSR_CPUQ.
 *
 * \details
 * 0: No action
 * 1: Discard HSR-tagged frames
 * 2: Discard non-HSR-tagged frames
 * 3: Redirect non-HSR-tagged frames to the CPU (LRE ports only)
 *
 * Field: ::VTSS_RB_PORT_CFG . HSR_FILTER_CFG
 */
#define  VTSS_F_RB_PORT_CFG_HSR_FILTER_CFG(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_RB_PORT_CFG_HSR_FILTER_CFG     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_RB_PORT_CFG_HSR_FILTER_CFG(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Configures handling of HSR supervision frames on ingress port.Related
 * parameters: RB::CPU_CFG.SPV_CPUQRB::SPV_CFG.HSR_SPV_INT_FWD_SEL
 *
 * \details
 * 0: No change to forwarding
 * 1: Copy to CPU (not applicable to frames from Interlink)
 * 2: Redirect to CPU (not applicable to frames from Interlink)
 * 3: Discard
 *
 * Field: ::VTSS_RB_PORT_CFG . HSR_SPV_FWD_SEL
 */
#define  VTSS_F_RB_PORT_CFG_HSR_SPV_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_RB_PORT_CFG_HSR_SPV_FWD_SEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_RB_PORT_CFG_HSR_SPV_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Configures handling of PRP supervision frames on ingress port.Related
 * parameters: RB::CPU_CFG.SPV_CPUQRB::SPV_CFG.PRP_SPV_INT_FWD_SEL
 *
 * \details
 * 0: No change to forwarding
 * 1: Copy to CPU (not applicable to frames from Interlink)
 * 2: Redirect to CPU (not applicable to frames from Interlink)
 * 3: Discard
 *
 * Field: ::VTSS_RB_PORT_CFG . PRP_SPV_FWD_SEL
 */
#define  VTSS_F_RB_PORT_CFG_PRP_SPV_FWD_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_RB_PORT_CFG_PRP_SPV_FWD_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_RB_PORT_CFG_PRP_SPV_FWD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \details
 * Field: ::VTSS_RB_PORT_CFG . TRANS_NETID
 */
#define  VTSS_F_RB_PORT_CFG_TRANS_NETID(x)    VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_RB_PORT_CFG_TRANS_NETID       VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_RB_PORT_CFG_TRANS_NETID(x)    VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Enables ingress NetId translation. If a frame's NetId matches the
 * ingress port configuration RB:PORT:PORT_CFG.TRANS_NETID, then the
 * frame's NetId is replaced with RB:PORT:PORT_CFG.NETID. Frames with other
 * NetId values are unchanged. Applies to HSR-tagged frames
 * only.Example:TRANS_NETID_SEL = 1TRANS_NETID = 4NETID = 5NetId = 4 is
 * translated to NetId = 5. Other NetIds are untoched.
 *
 * \details
 * 0: No translation
 * 1: Translation for TRANS_NETID
 * 2: Translation for all NetIds
 * 3: Reserved
 *
 * Field: ::VTSS_RB_PORT_CFG . TRANS_NETID_SEL
 */
#define  VTSS_F_RB_PORT_CFG_TRANS_NETID_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_RB_PORT_CFG_TRANS_NETID_SEL     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_RB_PORT_CFG_TRANS_NETID_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * NetId used by egress port.In addtion, the common
 * RB::NETID_CFG.RING_NETID is used for injected frames into ring, signaled
 * by IRI.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . NETID
 */
#define  VTSS_F_RB_PORT_CFG_NETID(x)          VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_RB_PORT_CFG_NETID             VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_RB_PORT_CFG_NETID(x)          VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * LanId used by port for injected frames.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . RING_LANID
 */
#define  VTSS_F_RB_PORT_CFG_RING_LANID(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_RB_PORT_CFG_RING_LANID        VTSS_BIT(3)
#define  VTSS_X_RB_PORT_CFG_RING_LANID(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * LanId used by port.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . LANID
 */
#define  VTSS_F_RB_PORT_CFG_LANID(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_PORT_CFG_LANID             VTSS_BIT(2)
#define  VTSS_X_RB_PORT_CFG_LANID(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, HSR tags are detected and used by RedBox.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . HSR_AWARE_ENA
 */
#define  VTSS_F_RB_PORT_CFG_HSR_AWARE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_PORT_CFG_HSR_AWARE_ENA     VTSS_BIT(1)
#define  VTSS_X_RB_PORT_CFG_HSR_AWARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If set, PRP trailers are detected and used by RedBox.
 *
 * \details
 * Field: ::VTSS_RB_PORT_CFG . PRP_AWARE_ENA
 */
#define  VTSS_F_RB_PORT_CFG_PRP_AWARE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_PORT_CFG_PRP_AWARE_ENA     VTSS_BIT(0)
#define  VTSS_X_RB_PORT_CFG_PRP_AWARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PTP configurations
 *
 * \details
 * Register: \a RB:PORT:PTP_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_PTP_CFG(target,gi)           VTSS_IOREG_IX(target,0x21,gi,6,0,4)

/**
 * \brief
 * If set, frames matching the PTP filter are no subject to duplicate
 * discard on any egress ports.
 *
 * \details
 * Field: ::VTSS_RB_PTP_CFG . PTP_DUPL_DISC_DIS
 */
#define  VTSS_F_RB_PTP_CFG_PTP_DUPL_DISC_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_PTP_CFG_PTP_DUPL_DISC_DIS  VTSS_BIT(1)
#define  VTSS_X_RB_PTP_CFG_PTP_DUPL_DISC_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Handling of frames matching the PTP filter.HSR-xxx:Frames received on an
 * LRE port:- Frames matching PTP filter and forwarded to the other LRE
 * port are redirected to the interlink. Frames received on Interlink:- No
 * specific actions
 *
 * \details
 * 0: No action
 * 1: Redirect to Interlink
 * 2: ?
 *
 * Field: ::VTSS_RB_PTP_CFG . PTP_ENA
 */
#define  VTSS_F_RB_PTP_CFG_PTP_ENA(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_PTP_CFG_PTP_ENA            VTSS_BIT(0)
#define  VTSS_X_RB_PTP_CFG_PTP_ENA(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Sticky diagnostic status
 *
 * \details
 * Register: \a RB:PORT:STICKY
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: PORT (??), 0-2
 */
#define VTSS_RB_STICKY(target,gi)            VTSS_IOREG_IX(target,0x21,gi,6,0,5)

/**
 * \brief
 * Set if frame was discarded due to RCT missing condition.Related
 * parameters:RB::RB_CFG.RCT_MISSING_DISC_ENA
 *
 * \details
 * Field: ::VTSS_RB_STICKY . RCT_MISSING_DISC_STICKY
 */
#define  VTSS_F_RB_STICKY_RCT_MISSING_DISC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_RB_STICKY_RCT_MISSING_DISC_STICKY  VTSS_BIT(23)
#define  VTSS_X_RB_STICKY_RCT_MISSING_DISC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Set if frames was discarded due to missing RCT (HSR-PRP mode with
 * RB_CFG.RCT_VALIDATE_ENA set).Related
 * parameters:RB::RB_CFG.RCT_VALIDATE_ENARB:HOST_TBL:HOST_ACCESS_CFG_2.HOST
 * _ENTRY_RCT_MISSING
 *
 * \details
 * Field: ::VTSS_RB_STICKY . RCT_MISSING_STICKY
 */
#define  VTSS_F_RB_STICKY_RCT_MISSING_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_RB_STICKY_RCT_MISSING_STICKY  VTSS_BIT(22)
#define  VTSS_X_RB_STICKY_RCT_MISSING_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Set if PTP frame destined for a LRE port was redirected to interlink.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PTP_INT_STICKY
 */
#define  VTSS_F_RB_STICKY_PTP_INT_STICKY(x)   VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_RB_STICKY_PTP_INT_STICKY      VTSS_BIT(21)
#define  VTSS_X_RB_STICKY_PTP_INT_STICKY(x)   VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Set if PTPoE frame was detected.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PTP_ETH_STICKY
 */
#define  VTSS_F_RB_STICKY_PTP_ETH_STICKY(x)   VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_RB_STICKY_PTP_ETH_STICKY      VTSS_BIT(20)
#define  VTSS_X_RB_STICKY_PTP_ETH_STICKY(x)   VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Set if PTPoIPv4oUDP frame was detected.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PTP_IP4_STICKY
 */
#define  VTSS_F_RB_STICKY_PTP_IP4_STICKY(x)   VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_RB_STICKY_PTP_IP4_STICKY      VTSS_BIT(19)
#define  VTSS_X_RB_STICKY_PTP_IP4_STICKY(x)   VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Set if PTPoIPv6oUDP frame was detected.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PTP_IP6_STICKY
 */
#define  VTSS_F_RB_STICKY_PTP_IP6_STICKY(x)   VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_RB_STICKY_PTP_IP6_STICKY      VTSS_BIT(18)
#define  VTSS_X_RB_STICKY_PTP_IP6_STICKY(x)   VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Set if HSR-tagged frame with LSDU size error was received.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . HSR_LSDU_ERR_STICKY
 */
#define  VTSS_F_RB_STICKY_HSR_LSDU_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_RB_STICKY_HSR_LSDU_ERR_STICKY  VTSS_BIT(17)
#define  VTSS_X_RB_STICKY_HSR_LSDU_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Set if forwarding mode T is in use.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . MODE_T_STICKY
 */
#define  VTSS_F_RB_STICKY_MODE_T_STICKY(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_RB_STICKY_MODE_T_STICKY       VTSS_BIT(16)
#define  VTSS_X_RB_STICKY_MODE_T_STICKY(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set if sequence number is generated by RedBox.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . SEQUENCE_STICKY
 */
#define  VTSS_F_RB_STICKY_SEQUENCE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_RB_STICKY_SEQUENCE_STICKY     VTSS_BIT(15)
#define  VTSS_X_RB_STICKY_SEQUENCE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set if PRP processing resulted in duplicate accept.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_ACCEPT_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_ACCEPT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_RB_STICKY_PRP_ACCEPT_STICKY   VTSS_BIT(14)
#define  VTSS_X_RB_STICKY_PRP_ACCEPT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Set if source registered as a SanA node is seen on LanB or vice versa.
 * Applicable to PRP-SAN mode.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_SAN_LAN_MISMATCH_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_SAN_LAN_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_RB_STICKY_PRP_SAN_LAN_MISMATCH_STICKY  VTSS_BIT(13)
#define  VTSS_X_RB_STICKY_PRP_SAN_LAN_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Set if frame was forwarded to the LRE ports due to destination
 * registered as Node-DAN.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_DAN_FWD_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_DAN_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_RB_STICKY_PRP_DAN_FWD_STICKY  VTSS_BIT(12)
#define  VTSS_X_RB_STICKY_PRP_DAN_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Set if frame was forwarded to the LRE port(s) due to destination
 * registered as Node-SAN.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_SAN_FWD_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_SAN_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_RB_STICKY_PRP_SAN_FWD_STICKY  VTSS_BIT(11)
#define  VTSS_X_RB_STICKY_PRP_SAN_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Set if frame was filtered (no destinations).
 *
 * \details
 * Field: ::VTSS_RB_STICKY . FILTERING_STICKY
 */
#define  VTSS_F_RB_STICKY_FILTERING_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_RB_STICKY_FILTERING_STICKY    VTSS_BIT(10)
#define  VTSS_X_RB_STICKY_FILTERING_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Set if frame was forwarded to one or more ports.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . FORWARDING_STICKY
 */
#define  VTSS_F_RB_STICKY_FORWARDING_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_RB_STICKY_FORWARDING_STICKY   VTSS_BIT(9)
#define  VTSS_X_RB_STICKY_FORWARDING_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Set if HSR candidate for duplicate discard was detected.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . HSR_DUPL_DISC_STICKY
 */
#define  VTSS_F_RB_STICKY_HSR_DUPL_DISC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_RB_STICKY_HSR_DUPL_DISC_STICKY  VTSS_BIT(8)
#define  VTSS_X_RB_STICKY_HSR_DUPL_DISC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Set if PRP candidate for duplicate discard was detected.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_DUPL_DISC_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_DUPL_DISC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_RB_STICKY_PRP_DUPL_DISC_STICKY  VTSS_BIT(7)
#define  VTSS_X_RB_STICKY_PRP_DUPL_DISC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if interlink was filtered due to NetId match.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . NETID_INT_STICKY
 */
#define  VTSS_F_RB_STICKY_NETID_INT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_STICKY_NETID_INT_STICKY    VTSS_BIT(6)
#define  VTSS_X_RB_STICKY_NETID_INT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if frame was redicted to CPU due to destination registered as local.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . LOCAL_DST_REDIR_STICKY
 */
#define  VTSS_F_RB_STICKY_LOCAL_DST_REDIR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_STICKY_LOCAL_DST_REDIR_STICKY  VTSS_BIT(5)
#define  VTSS_X_RB_STICKY_LOCAL_DST_REDIR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if frame was filtered due to HSR tagging.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . HSR_FILTER_STICKY
 */
#define  VTSS_F_RB_STICKY_HSR_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_STICKY_HSR_FILTER_STICKY   VTSS_BIT(4)
#define  VTSS_X_RB_STICKY_HSR_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if frame was filtered due to BPDU handling.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . BPDU_FILTER_STICKY
 */
#define  VTSS_F_RB_STICKY_BPDU_FILTER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_RB_STICKY_BPDU_FILTER_STICKY  VTSS_BIT(3)
#define  VTSS_X_RB_STICKY_BPDU_FILTER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if HSR tag was identified.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . HSR_TAG_STICKY
 */
#define  VTSS_F_RB_STICKY_HSR_TAG_STICKY(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_STICKY_HSR_TAG_STICKY      VTSS_BIT(2)
#define  VTSS_X_RB_STICKY_HSR_TAG_STICKY(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if PRP trailer was identified.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_TRAILER_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_TRAILER_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_STICKY_PRP_TRAILER_STICKY  VTSS_BIT(1)
#define  VTSS_X_RB_STICKY_PRP_TRAILER_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if PRP trailer with mismatching LANID was received.
 *
 * \details
 * Field: ::VTSS_RB_STICKY . PRP_LANID_MISMATCH_STICKY
 */
#define  VTSS_F_RB_STICKY_PRP_LANID_MISMATCH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_STICKY_PRP_LANID_MISMATCH_STICKY  VTSS_BIT(0)
#define  VTSS_X_RB_STICKY_PRP_LANID_MISMATCH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a RB:STAT
 *
 * Port statistics
 */


/**
 * \brief Tx HSR/PRP counter
 *
 * \details
 * Counts number of frames sent over port with HSR-tag or PRP trailer. Link
 * local frames are counted in CNT_TX_LL.
 *
 * Register: \a RB:STAT:CNT_TX_TAG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_TX_TAG(target,gi)        VTSS_IOREG_IX(target,0x33,gi,11,0,0)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_TX_TAG . CNT_TX_TAG
 */
#define  VTSS_F_RB_CNT_TX_TAG_CNT_TX_TAG(x)   (x)
#define  VTSS_M_RB_CNT_TX_TAG_CNT_TX_TAG      0xffffffff
#define  VTSS_X_RB_CNT_TX_TAG_CNT_TX_TAG(x)   (x)


/**
 * \brief Tx untagged counter
 *
 * \details
 * Counts number of frames sent over port without HSR-tag or PRP trailer.
 * Link local frames are counted in CNT_TX_LL.
 *
 * Register: \a RB:STAT:CNT_TX_UNT
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_TX_UNT(target,gi)        VTSS_IOREG_IX(target,0x33,gi,11,0,1)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_TX_UNT . CNT_TX_UNT
 */
#define  VTSS_F_RB_CNT_TX_UNT_CNT_TX_UNT(x)   (x)
#define  VTSS_M_RB_CNT_TX_UNT_CNT_TX_UNT      0xffffffff
#define  VTSS_X_RB_CNT_TX_UNT_CNT_TX_UNT(x)   (x)


/**
 * \brief Tx link local counter
 *
 * \details
 * Counts number of link local frames (BPDUs) sent over port.
 *
 * Register: \a RB:STAT:CNT_TX_LL
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_TX_LL(target,gi)         VTSS_IOREG_IX(target,0x33,gi,11,0,2)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_TX_LL . CNT_TX_LL
 */
#define  VTSS_F_RB_CNT_TX_LL_CNT_TX_LL(x)     (x)
#define  VTSS_M_RB_CNT_TX_LL_CNT_TX_LL        0xffffffff
#define  VTSS_X_RB_CNT_TX_LL_CNT_TX_LL(x)     (x)


/**
 * \brief Rx HSR/PRP counter
 *
 * \details
 * Counts number of frames received from port with HSR-tag or PRP trailer.
 * Link local frames are counted in CNT_RX_LL.
 *
 * Register: \a RB:STAT:CNT_RX_TAG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_RX_TAG(target,gi)        VTSS_IOREG_IX(target,0x33,gi,11,0,3)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_RX_TAG . CNT_RX_TAG
 */
#define  VTSS_F_RB_CNT_RX_TAG_CNT_RX_TAG(x)   (x)
#define  VTSS_M_RB_CNT_RX_TAG_CNT_RX_TAG      0xffffffff
#define  VTSS_X_RB_CNT_RX_TAG_CNT_RX_TAG(x)   (x)


/**
 * \brief Rx untagged counter
 *
 * \details
 * Counts number of frames received from port without HSR-tag or PRP
 * trailer. Link local frames are counted in CNT_RX_LL.
 *
 * Register: \a RB:STAT:CNT_RX_UNT
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_RX_UNT(target,gi)        VTSS_IOREG_IX(target,0x33,gi,11,0,4)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_RX_UNT . CNT_RX_UNT
 */
#define  VTSS_F_RB_CNT_RX_UNT_CNT_RX_UNT(x)   (x)
#define  VTSS_M_RB_CNT_RX_UNT_CNT_RX_UNT      0xffffffff
#define  VTSS_X_RB_CNT_RX_UNT_CNT_RX_UNT(x)   (x)


/**
 * \brief Rx link local counter
 *
 * \details
 * Counts number of link local frames (BPDUs) received from port.
 *
 * Register: \a RB:STAT:CNT_RX_LL
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_RX_LL(target,gi)         VTSS_IOREG_IX(target,0x33,gi,11,0,5)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_RX_LL . CNT_RX_LL
 */
#define  VTSS_F_RB_CNT_RX_LL_CNT_RX_LL(x)     (x)
#define  VTSS_M_RB_CNT_RX_LL_CNT_RX_LL        0xffffffff
#define  VTSS_X_RB_CNT_RX_LL_CNT_RX_LL(x)     (x)


/**
 * \brief Rx Wrong LAN counter
 *
 * \details
 * lreCntErrWrongLan counter. Counts number of frames with the wrong LanId
 * received on port.
 *
 * Register: \a RB:STAT:CNT_RX_WRONG_LAN
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_RX_WRONG_LAN(target,gi)  VTSS_IOREG_IX(target,0x33,gi,11,0,6)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_RX_WRONG_LAN . CNT_RX_WRONG_LAN
 */
#define  VTSS_F_RB_CNT_RX_WRONG_LAN_CNT_RX_WRONG_LAN(x)  (x)
#define  VTSS_M_RB_CNT_RX_WRONG_LAN_CNT_RX_WRONG_LAN     0xffffffff
#define  VTSS_X_RB_CNT_RX_WRONG_LAN_CNT_RX_WRONG_LAN(x)  (x)


/**
 * \brief Rx Own counter
 *
 * \details
 * lreCntOwn counter. Counts number of HSR tagged frames received on port
 * that originated from this device. Frames originate from this device if
 * frame's SMAC matches a local host or proxy host in the host table.
 *
 * Register: \a RB:STAT:CNT_RX_OWN
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_RX_OWN(target,gi)        VTSS_IOREG_IX(target,0x33,gi,11,0,7)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_RX_OWN . CNT_RX_OWN
 */
#define  VTSS_F_RB_CNT_RX_OWN_CNT_RX_OWN(x)   (x)
#define  VTSS_M_RB_CNT_RX_OWN_CNT_RX_OWN      0xffffffff
#define  VTSS_X_RB_CNT_RX_OWN_CNT_RX_OWN(x)   (x)


/**
 * \brief Zero duplicate discards counter
 *
 * \details
 * lreCntUnique counter. Counts number of entries in the duplicate discard
 * table for port for which zero duplicates were received.
 *
 * When aging an entry in DISC_TBL, CNT_DUPL_ZERO for port x is increment
 * when removed entries DISC_CNT_x equals 1.
 *
 * Register: \a RB:STAT:CNT_DUPL_ZERO
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_DUPL_ZERO(target,gi)     VTSS_IOREG_IX(target,0x33,gi,11,0,8)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_DUPL_ZERO . CNT_DUPL_ZERO
 */
#define  VTSS_F_RB_CNT_DUPL_ZERO_CNT_DUPL_ZERO(x)  (x)
#define  VTSS_M_RB_CNT_DUPL_ZERO_CNT_DUPL_ZERO     0xffffffff
#define  VTSS_X_RB_CNT_DUPL_ZERO_CNT_DUPL_ZERO(x)  (x)


/**
 * \brief One duplicate discards counter
 *
 * \details
 * lreCntDuplicate counter. Counts number of entries in the duplicate
 * discard table for port for which a single duplicate was received.
 *
 * When aging an entry in DISC_TBL, CNT_DUPL_ONE for port x is increment
 * when removed entries DISC_CNT_x equals 2.
 *
 * Register: \a RB:STAT:CNT_DUPL_ONE
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_DUPL_ONE(target,gi)      VTSS_IOREG_IX(target,0x33,gi,11,0,9)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_DUPL_ONE . CNT_DUPL_ONE
 */
#define  VTSS_F_RB_CNT_DUPL_ONE_CNT_DUPL_ONE(x)  (x)
#define  VTSS_M_RB_CNT_DUPL_ONE_CNT_DUPL_ONE     0xffffffff
#define  VTSS_X_RB_CNT_DUPL_ONE_CNT_DUPL_ONE(x)  (x)


/**
 * \brief Two duplicate discards counter
 *
 * \details
 * lreCntMulti counter. Counts number of entries in the duplicate discard
 * table for port for which two or more duplicates were received.
 *
 * When aging an entry in DISC_TBL, CNT_DUPL_TWO for port x is increment
 * when removed entries DISC_CNT_x equals 3.
 *
 * Register: \a RB:STAT:CNT_DUPL_TWO
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param gi Register: STAT (??), 0-2
 */
#define VTSS_RB_CNT_DUPL_TWO(target,gi)      VTSS_IOREG_IX(target,0x33,gi,11,0,10)

/**
 * \brief
 * Counter. See register description.
 *
 * \details
 * Field: ::VTSS_RB_CNT_DUPL_TWO . CNT_DUPL_TWO
 */
#define  VTSS_F_RB_CNT_DUPL_TWO_CNT_DUPL_TWO(x)  (x)
#define  VTSS_M_RB_CNT_DUPL_TWO_CNT_DUPL_TWO     0xffffffff
#define  VTSS_X_RB_CNT_DUPL_TWO_CNT_DUPL_TWO(x)  (x)

/**
 * Register Group: \a RB:HOST_TBL
 *
 * Host table configurations
 */


/**
 * \brief Host Table Control
 *
 * \details
 * Configures command and access parameters when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_CTRL
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_CTRL(target)     VTSS_IOREG(target,0x54)

/**
 * \brief
 * Configures the host table bucket or column index that holds the
 * HOST_ENTRY that is accessed when CPU_ACCESS_CMD command is READ or
 * WRITE.
 *
 * \details
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . CPU_ACCESS_DIRECT_COL
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * Configures the host table row index that holds the HOST_ENTRY that is
 * accessed when CPU_ACCESS_CMD command is READ or WRITE.Configures the
 * host table starting row index when CPU_ACCESS_CMD command is FIND NEXT.
 * If the Command succeeds in finding a matching entry this field is
 * updated with the row index for the (last) matching entry.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . CPU_ACCESS_DIRECT_ROW
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_ENCODE_BITFIELD(x,7,10)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW     VTSS_ENCODE_BITMASK(7,10)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,7,10)

/**
 * \brief
 * Configures the host table access command:LEARN, UNLEARN, and LOOKUP
 * Command accesses a HOST_ENTRY at the HASH(MAC) index. The MAC address
 * must to be written to the respective bitgroups in registers
 * HOST_ACCESS_CFG_[0|1|2].READ and WRITE Command accesses a HOST_ENTRY at
 * the index specified by means of CPU_ACCESS_DIRECT_ROW and
 * CPU_ACCESS_DIRECT_COL fields.CLEAR ALL Command traverses the entire
 * table and resets all entries.
 *
 * \details
 * 0: LEARN
 * 1: UNLEARN
 * 2: LOOKUP
 * 3: READ
 * 4: WRITE
 * 7: CLEAR ALL
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . CPU_ACCESS_CMD
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_CPU_ACCESS_CMD     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/**
 * \brief
 * Overwrite sequence number entry when CPU_ACCESS_CMD==LEARN.
 *
 * \details
 * 0: Keep old values1: Overwrite with CPU provided values

 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . CPU_ACCESS_LEARN_SEQNO
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO  VTSS_BIT(2)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Overwrite cnt_rx[2:0] and cnt_rx_wrong_lan[2:0] when
 * CPU_ACCESS_CMD==LEARN.
 *
 * \details
 * 0: Keep old values1: Overwrite with CPU provided values

 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . CPU_ACCESS_LEARN_STATS
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_STATS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_STATS  VTSS_BIT(1)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_CPU_ACCESS_LEARN_STATS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Perform the access command specified by CPU_ACCESS_CMD. Cleared when the
 * access completes.
 *
 * \details
 * 0: Idle
 * 1: Initiate CPU ACCESS
 *
 * The bit is cleared upon completion
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CTRL . HOST_TABLE_ACCESS_SHOT
 */
#define  VTSS_F_RB_HOST_ACCESS_CTRL_HOST_TABLE_ACCESS_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_HOST_ACCESS_CTRL_HOST_TABLE_ACCESS_SHOT  VTSS_BIT(0)
#define  VTSS_X_RB_HOST_ACCESS_CTRL_HOST_TABLE_ACCESS_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Host Entry Data 0
 *
 * \details
 * Configures MAC address when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_CFG_0
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_CFG_0(target)    VTSS_IOREG(target,0x55)

/**
 * \brief
 * Last sequence number used.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_0 . HOST_ENTRY_SEQ_NO
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_SEQ_NO     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Configures 16 MSB bits of the MAC address for the HOST_ENTRY.Used as
 * starting MAC address value during FIND SMALLEST Command.
 *
 * \details
 * Upper 16 bits of MAC address.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_0 . HOST_ENTRY_MAC_MSB
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_RB_HOST_ACCESS_CFG_0_HOST_ENTRY_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Host Entry Data 1
 *
 * \details
 * Configures MAC address when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_CFG_1
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_CFG_1(target)    VTSS_IOREG(target,0x56)

/**
 * \brief
 * Configures 32 LSB bits of the MAC address for the HOST_ENTRY.Used as
 * starting MAC address value during FIND SMALLEST Command.
 *
 * \details
 * 0xXXXXXXXX: Lower 32 bits of MAC address.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_1 . HOST_ENTRY_MAC_LSB
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_1_HOST_ENTRY_MAC_LSB(x)  (x)
#define  VTSS_M_RB_HOST_ACCESS_CFG_1_HOST_ENTRY_MAC_LSB     0xffffffff
#define  VTSS_X_RB_HOST_ACCESS_CFG_1_HOST_ENTRY_MAC_LSB(x)  (x)


/**
 * \brief Host Entry Data 2
 *
 * \details
 * Configures warious HOST_ENTRY parameters when accessing the host table
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_CFG_2
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_CFG_2(target)    VTSS_IOREG(target,0x57)

/**
 * \brief
 * Extra bit for future additions.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_SPARE
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_SPARE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_SPARE  VTSS_BIT(22)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_SPARE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Set if frame was received without a valid RCT when HOST_ENTRY_PROXY_DAN
 * is set and HOST_ENTRY_TYPE is PROXY. RB::RB_CFG.RCT_VALIDATE_ENA must be
 * set.Related
 * parameters:RB::RB_CFG.RCT_VALIDATE_ENARB:PORT:STICKY.RCT_MISSING_STICKY
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_RCT_MISSING
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_MISSING(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_MISSING  VTSS_BIT(21)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_MISSING(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Set if entry is considered a Proxy-DAN entry. HOST_ENTRY_TYPE must be
 * PROXY. Related parameters:RB::RB_CFG.RCT_VALIDATE_ENA
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_PROXY_DAN
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PROXY_DAN(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PROXY_DAN  VTSS_BIT(20)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PROXY_DAN(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Flag indicates whether a frame was received with a valid RCT on LRE B
 * port.
 *
 * \details
 * 0: Last frame received did not have a valid RCT
 * 1: Last received had a valid RCT.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_RCT_VALID_1
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_1(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_1  VTSS_BIT(19)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_1(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Flag indicates whether a frame was received with a valid RCT on LRE A
 * port.
 *
 * \details
 * 0: Last frame received did not have a valid RCT
 * 1: Last received had a valid RCT.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_RCT_VALID_0
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_0(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_0  VTSS_BIT(18)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_RCT_VALID_0(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_AGE_FLAG_2
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_2(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_2     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_2(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_AGE_FLAG_1
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_1(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_1     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_1(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * HOST_ENTRY AGE flag used to identify if a HOST_ENTRY is active of
 * not.Cleared by HW when a entry is used as source entry. Used to ensure
 * that entries associated with inactive stations can be located and
 * discarded. The host table can be aged by HW either a CPU Scan command or
 * through automatic ageing (RB::HOST_AUTOAGE_CFG).
 *
 * \details
 * 0:  Not aged
 * n:  Aged n times.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_AGE_FLAG_0
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_0(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_0     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_FLAG_0(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * HOST_ENTRY AGE Interval is used to select which age timer is associated
 * with the entry. The host table can be aged by HW either a CPU Scan
 * command or through Automatic ageing (RB::HOST_AUTOAGE_CFG).
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_AGE_INTERVAL
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_INTERVAL(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_INTERVAL     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_AGE_INTERVAL(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * Configures the HOST_ENTRY locked flag. Used to install static host table
 * entries that can not be removed by learning and ageing.
 *
 * \details
 * 0: Not locked
 * 1: Locked.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_LOCKED
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED  VTSS_BIT(6)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_LOCKED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configures the HOST_ENTRY valid flag. Used to indicate that this entry
 * is active. This bit can be cleared for non locked entries by auto
 * learning or through the CPU_ACCESS_CMD UNLEARN command.
 *
 * \details
 * 0: Invalid
 * 1: Valid.
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_VLD
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_VLD  VTSS_BIT(5)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_VLD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Configures HOST_ENTRY type. Can be used as filter value during SCAN or
 * FIND SMALLEST Command.
 *
 * \details
 * 0: Proxy
 * 1: Node-DAN
 * 2: Node-SAN
 * 3: Local
 *
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_TYPE
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Configures the port mask for the HOST_ENTRY.Port mask: Bit 0: LRE_A, bit
 * 1: LRE_B, bit 2: Interlink
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_CFG_2 . HOST_ENTRY_PORTMASK
 */
#define  VTSS_F_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PORTMASK     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_RB_HOST_ACCESS_CFG_2_HOST_ENTRY_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Host Entry Stat 0
 *
 * \details
 * Configures statistics when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_STAT_0
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_STAT_0(target)   VTSS_IOREG(target,0x58)

/**
 * \brief
 * Number of frames received from host on port 0.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_0 . CNT_RX_0
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_0_CNT_RX_0(x)  (x)
#define  VTSS_M_RB_HOST_ACCESS_STAT_0_CNT_RX_0     0xffffffff
#define  VTSS_X_RB_HOST_ACCESS_STAT_0_CNT_RX_0(x)  (x)


/**
 * \brief Host Entry Stat 1
 *
 * \details
 * Configures statistics when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_STAT_1
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_STAT_1(target)   VTSS_IOREG(target,0x59)

/**
 * \brief
 * Number of frames received from host on port 1.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_1 . CNT_RX_1
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_1_CNT_RX_1(x)  (x)
#define  VTSS_M_RB_HOST_ACCESS_STAT_1_CNT_RX_1     0xffffffff
#define  VTSS_X_RB_HOST_ACCESS_STAT_1_CNT_RX_1(x)  (x)


/**
 * \brief Host Entry Stat 2
 *
 * \details
 * Configures statistics when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_STAT_2
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_STAT_2(target)   VTSS_IOREG(target,0x5a)

/**
 * \brief
 * Number of frames received from host on port 2.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_2 . CNT_RX_2
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_2_CNT_RX_2(x)  (x)
#define  VTSS_M_RB_HOST_ACCESS_STAT_2_CNT_RX_2     0xffffffff
#define  VTSS_X_RB_HOST_ACCESS_STAT_2_CNT_RX_2(x)  (x)


/**
 * \brief Host Entry Stat 3
 *
 * \details
 * Configures statistics when accessing the host table.
 *
 * Register: \a RB:HOST_TBL:HOST_ACCESS_STAT_3
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_ACCESS_STAT_3(target)   VTSS_IOREG(target,0x5b)

/**
 * \brief
 * Number of frames with from LAN identifier from host on port 2.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_3 . CNT_RX_WRONG_LAN_2
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Number of frames with from LAN identifier from host on port 1.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_3 . CNT_RX_WRONG_LAN_1
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Number of frames with from LAN identifier from host on port 0.
 *
 * \details
 * Field: ::VTSS_RB_HOST_ACCESS_STAT_3 . CNT_RX_WRONG_LAN_0
 */
#define  VTSS_F_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_RB_HOST_ACCESS_STAT_3_CNT_RX_WRONG_LAN_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Automated age scan configuration
 *
 * \details
 * Configures automated age scan of host table.
 *
 * This register is replicated for the two age intervals supported.
 *
 * Age interval are configured for auto learned entries through:
 * RB:PORT:TBL_CFG.HOST_AGE_INTERVAL
 *
 * Age intervals are configured for CPU learned entries through:
 * RB::HOST_ACCESS_CFG_2.HOST_ENTRY_AGE_INTERVAL
 *
 * Register: \a RB:HOST_TBL:HOST_AUTOAGE_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Replicator: x_RB_CFG_NUM_HOST_AUTOAGE_INTERVALS (??), 0-1
 */
#define VTSS_RB_HOST_AUTOAGE_CFG(target,ri)  VTSS_IOREG(target,0x5c + (ri))

/**
 * \brief
 * Sets the unit time of PERIOD_VAL. Internally the auto aging
 * state-machine computes the aging period by shifting
 * RB:HOST_TBL:HOST_AUTOAGE_CFG.PERIOD_VAL by 3, 7, 11, 15 respectively.
 *
 * \details
 * 0: 161: 2562: 40963: 65536
 *
 * Field: ::VTSS_RB_HOST_AUTOAGE_CFG . UNIT_SIZE
 */
#define  VTSS_F_RB_HOST_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_RB_HOST_AUTOAGE_CFG_UNIT_SIZE     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_RB_HOST_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * Time between automatic ageing of a row in
 * RB:HOST_TBL:HOST_AUTOAGE_CFG.UNIT_SIZE units of clock cycles.
 *
 * \details
 * n: Age period in RB:HOST_TBL:HOST_AUTOAGE_CFG.UNIT_SIZE amount of clock
 * cycles, i.e. for an RB:HOST_TBL:HOST_AUTOAGE_CFG.PERIOD_VAL = 1 the
 * hardware will age an row every RB:HOST_TBL:HOST_AUTOAGE_CFG.UNIT_SIZE
 * clock cycles.
 *	   e.g. To achieve a 60s aging period per entry (i.e. 256 rows),
 * then every row should age every ~234375 us. At 1 GHz frequency we can
 * choose UNIT_SIZE = 3 and PERIOD_VAL = ceil((234375 us *
 * 1000MHz)/(32768)) = 7153
 *
 * Field: ::VTSS_RB_HOST_AUTOAGE_CFG . PERIOD_VAL
 */
#define  VTSS_F_RB_HOST_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_RB_HOST_AUTOAGE_CFG_PERIOD_VAL     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_RB_HOST_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of host table
 *
 * Register: \a RB:HOST_TBL:HOST_AUTOAGE_CFG_1
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Replicator: x_RB_CFG_NUM_HOST_AUTOAGE_INTERVALS (??), 0-1
 */
#define VTSS_RB_HOST_AUTOAGE_CFG_1(target,ri)  VTSS_IOREG(target,0x5e + (ri))

/**
 * \brief
 * Enable autoage scan per interval.
 *
 * \details
 * Field: ::VTSS_RB_HOST_AUTOAGE_CFG_1 . AUTOAGE_INTERVAL_ENA
 */
#define  VTSS_F_RB_HOST_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_HOST_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA  VTSS_BIT(1)
#define  VTSS_X_RB_HOST_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Triggers an instant hardware autoage scan (once current scan
 * completes).The bit is cleared by HW when a full scan completes.
 *
 * \details
 * 0: No force
 * 1: Force start of autoage scan
 *
 * Field: ::VTSS_RB_HOST_AUTOAGE_CFG_1 . FORCE_HW_SCAN_SHOT
 */
#define  VTSS_F_RB_HOST_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_HOST_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT  VTSS_BIT(0)
#define  VTSS_X_RB_HOST_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of host table
 *
 * Register: \a RB:HOST_TBL:HOST_AUTOAGE_CFG_2
 *
 * @param target A \a ::vtss_target_RB_e target
 * @param ri Replicator: x_RB_CFG_NUM_HOST_AUTOAGE_INTERVALS (??), 0-1
 */
#define VTSS_RB_HOST_AUTOAGE_CFG_2(target,ri)  VTSS_IOREG(target,0x60 + (ri))

/**
 * \brief
 * Current autoage row. Changed on every autoage period. Indicate the host
 * table row to be autoaged aged next.Incremented by hardware during auto
 * ageing.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_RB_HOST_AUTOAGE_CFG_2 . NEXT_AGED_ROW
 */
#define  VTSS_F_RB_HOST_AUTOAGE_CFG_2_NEXT_AGED_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_RB_HOST_AUTOAGE_CFG_2_NEXT_AGED_ROW     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_RB_HOST_AUTOAGE_CFG_2_NEXT_AGED_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief Sticky diagnostic status
 *
 * \details
 * Register: \a RB:HOST_TBL:HOST_EVENT_STICKY
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_EVENT_STICKY(target)    VTSS_IOREG(target,0x62)

/**
 * \brief
 * Set when Autoage scan completes.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE scan completes
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTOAGE_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/**
 * \brief
 * Set when Autoage scan starts.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE scan started
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTOAGE_SCAN_STARTED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/**
 * \brief
 * Set when Autoage scan should be started before the last scan completed.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE could not start before the current scan completed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTOAGE_START_DELAYED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/**
 * \brief
 * Set if a MAC address entry has been aged due to an autoage operation.
 *
 * \details
 * 0: No entries have been aged due to autoage.
 * 1: At least 1 entry has been aged due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTOAGE_AGED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTOAGE_AGED_STICKY  VTSS_BIT(16)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set if a MAC address entry has been removed due to an autoage operation.
 *
 * \details
 * 0: No entries have been removed due to autoage.
 * 1: At least 1 entry has been removed due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTOAGE_REMOVE_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTOAGE_REMOVE_STICKY  VTSS_BIT(15)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set if an autonomous learning operation has failed due to hash table
 * depletion (i.e. all entries in a row were locked). Write '1' to clear
 * this field.
 *
 * \details
 * 0: No autonomous learning operations have failed.
 * 1: An autonomous learning operation has failed.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTO_LRN_FAILED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTO_LRN_FAILED_STICKY  VTSS_BIT(14)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Set if a MAC address entry has been inserted into a MAC address table
 * column (bucket). Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been inserted into empty buckets
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTO_LRN_INSERT_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTO_LRN_INSERT_STICKY  VTSS_BIT(13)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Set if host entry has been updated. Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTO_LRN_REFRESH_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY  VTSS_BIT(12)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Set if a randomly selected non-locked and valid MAC address entry has
 * been overwritten by a new SMAC. Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . AUTO_LRN_REPLACE_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY  VTSS_BIT(11)
#define  VTSS_X_RB_HOST_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Set when a direct CPU READ operation has occurred. Write '1' to clear
 * this field.
 *
 * \details
 * 0:  No update
 * 1: CPU read direct operation has occurred.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_READ_DIRECT_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_READ_DIRECT_STICKY  VTSS_BIT(10)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Set when a direct CPU WRITE operation has occurred. Write '1' to clear
 * this field.
 *
 * \details
 * 0:  No update
 * 1: CPU write direct operation has occurred.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_WRITE_DIRECT_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY  VTSS_BIT(9)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Set if a CPU LOOKUP operation has failed due to not found an entry.
 * Write '1' to clear this field.
 *
 * \details
 * 0:  No fail
 * 1: CPU lookup operation failed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LOOKUP_FAILED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY  VTSS_BIT(8)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Set if a CPU LOOKUP operation has succeeded. Write '1' to clear this
 * field.
 *
 * \details
 * 0:  No successful lookup
 * 1: Successful lookup.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LOOKUP_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LOOKUP_STICKY  VTSS_BIT(7)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if a CPU UNLEARN operation has failed because the respective (valid)
 * entry was not found. Write '1' to clear this field.
 *
 * \details
 * 0:  No UNLEARN operation failed
 * 1: CPU UNLEARN operation failed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_UNLRN_FAILED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY  VTSS_BIT(6)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if a CPU UNLEARN operation has succeeded. Write '1' to clear this
 * field.
 *
 * \details
 * 0:  No CPU UNLEARN operation took place
 * 1:  CPU UNLEARN operations has succeeded.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_UNLRN_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_UNLRN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_UNLRN_STICKY  VTSS_BIT(5)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_UNLRN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if a valid host entry has been updated (refreshed), i.e. a write
 * access to the same bucket with the same MAC has occurred. Write '1' to
 * clear this field.
 *
 * \details
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LRN_REFRESH_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LRN_REFRESH_STICKY  VTSS_BIT(4)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if a valid host entry has been overwritten, i.e. a write access to
 * the same bucket with a changed MAC has occurred. Write '1' to clear this
 * field.
 *
 * \details
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LRN_REPLACE_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_STICKY  VTSS_BIT(3)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if CPU learn replace can not be performed due to configuration.
 * Write '1' to clear this field.
 *
 * \details
 * 0: No learn based replacement failed.
 * 1: The replacement of 1 or more entries failed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LRN_REPLACE_FAILED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY  VTSS_BIT(2)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if a host entry has been inserted into an empty host table
 * row,column (=bucket). Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been inserted into an empty bucket
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LRN_INSERT_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LRN_INSERT_STICKY  VTSS_BIT(1)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if an CPU learning operation has failed due to hash table depletion
 * (i.e. all entries in a row were locked). Write '1' to clear this field.
 *
 * \details
 * 0: No CPU LEARN operations has failed.
 * 1: A CPU LEARN operation has failed.
 *
 * Field: ::VTSS_RB_HOST_EVENT_STICKY . CPU_LRN_FAILED_STICKY
 */
#define  VTSS_F_RB_HOST_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_HOST_EVENT_STICKY_CPU_LRN_FAILED_STICKY  VTSS_BIT(0)
#define  VTSS_X_RB_HOST_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Learn Diagnostic
 *
 * \details
 * Register: \a RB:HOST_TBL:HOST_LATEST_POS_STATUS
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_HOST_LATEST_POS_STATUS(target)  VTSS_IOREG(target,0x63)

/**
 * \brief
 * This field holds the current (i.e. latest accessed) host table row
 * number after a CPU_ACCESS_CMD has been finished.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n
 *
 * Field: ::VTSS_RB_HOST_LATEST_POS_STATUS . LATEST_ROW
 */
#define  VTSS_F_RB_HOST_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_RB_HOST_LATEST_POS_STATUS_LATEST_ROW     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_RB_HOST_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/**
 * \brief
 * This field holds the current (i.e. latest accessed) column number after
 * a CPU_ACCESS_CMD has been finished.
 *
 * \details
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n
 *
 * Field: ::VTSS_RB_HOST_LATEST_POS_STATUS . LATEST_COL
 */
#define  VTSS_F_RB_HOST_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_RB_HOST_LATEST_POS_STATUS_LATEST_COL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_RB_HOST_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a RB:DISC_TBL
 *
 * Duplicate discard table configurations
 */


/**
 * \brief Duplicast discard Table Control
 *
 * \details
 * Configures command and access parameters when accessing the host table.
 *
 * Register: \a RB:DISC_TBL:DISC_ACCESS_CTRL
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_ACCESS_CTRL(target)     VTSS_IOREG(target,0x64)

/**
 * \brief
 * Configures the host table bucket or column index that holds the
 * DISC_ENTRY that is accessed when CPU_ACCESS_CMD command is READ or
 * WRITE.
 *
 * \details
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . CPU_ACCESS_DIRECT_COL
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_COL(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * Configures the host table row index that holds the DISC_ENTRY that is
 * accessed when CPU_ACCESS_CMD command is READ or WRITE.Configures the
 * host table starting row index when CPU_ACCESS_CMD command is FIND NEXT.
 * If the Command succeeds in finding a matching entry this field is
 * updated with the row index for the (last) matching entry.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . CPU_ACCESS_DIRECT_ROW
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_CPU_ACCESS_DIRECT_ROW(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/**
 * \brief
 * Configures the host table access command:LEARN, UNLEARN, and LOOKUP
 * Command accesses a DISC_ENTRY at the HASH(MAC) index. The MAC address
 * must to be written to the respective bitgroups in registers
 * DISC_ACCESS_CFG_[0|1|2].READ and WRITE Command accesses a DISC_ENTRY at
 * the index specified by means of CPU_ACCESS_DIRECT_ROW and
 * CPU_ACCESS_DIRECT_COL fields.CLEAR ALL Command traverses the entire
 * table and resets all entries.
 *
 * \details
 * 0: LEARN
 * 1: UNLEARN
 * 2: LOOKUP
 * 3: READ
 * 4: WRITE
 * 7: CLEAR ALL
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . CPU_ACCESS_CMD
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_CPU_ACCESS_CMD     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_CPU_ACCESS_CMD(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \brief
 * Overwrite sequence number entry when CPU_ACCESS_CMD==LEARN.
 *
 * \details
 * 0: Keep old values1: Overwrite with CPU provided values

 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . CPU_ACCESS_LEARN_SEQNO
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO  VTSS_BIT(5)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_CPU_ACCESS_LEARN_SEQNO(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Perform the access command specified by CPU_ACCESS_CMD. Cleared when the
 * access completes.
 *
 * \details
 * 0: Idle
 * 1: Initiate CPU ACCESS
 *
 * The bit is cleared upon completion
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . DISC_TABLE_ACCESS_SHOT
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_DISC_TABLE_ACCESS_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_DISC_TABLE_ACCESS_SHOT  VTSS_BIT(4)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_DISC_TABLE_ACCESS_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables each rule to execute during replacement of an entry in the same
 * row. The rules are in order and priority based.
 *
 * \details
 *
 *	     Bit:1 - Enables find and replace entries that have seen more
 * than one duplicate.
 *	     Bit:2 - Enables find and replace the max. seqno entry with the
 * same SMAC.
 *	     Bit:4 - Enables find and replace the oldest entry over half
 * the age limit.
 *	     Bit:8 - Enables find and replace a random entry if all else
 * fails.

 *
 * Field: ::VTSS_RB_DISC_ACCESS_CTRL . AUTOLRN_REPLACE_RULE_ENA
 */
#define  VTSS_F_RB_DISC_ACCESS_CTRL_AUTOLRN_REPLACE_RULE_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_RB_DISC_ACCESS_CTRL_AUTOLRN_REPLACE_RULE_ENA     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_RB_DISC_ACCESS_CTRL_AUTOLRN_REPLACE_RULE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Duplicast Discard Entry Data 0
 *
 * \details
 * Configures MAC address when accessing the host table.
 *
 * Register: \a RB:DISC_TBL:DISC_ACCESS_CFG_0
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_ACCESS_CFG_0(target)    VTSS_IOREG(target,0x65)

/**
 * \brief
 * Configures sequence number for the DISC_ENTRY.
 *
 * \details
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_0 . DISC_ENTRY_SEQ_NO
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SEQ_NO     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Configures 16 MSB bits of the MAC address for the DISC_ENTRY.Used as
 * starting MAC address value during FIND SMALLEST Command.
 *
 * \details
 * Upper 16 bits of MAC address.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_0 . DISC_ENTRY_SMAC_MSB
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SMAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SMAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_RB_DISC_ACCESS_CFG_0_DISC_ENTRY_SMAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Duplicast Discard Entry Data 1
 *
 * \details
 * Configures MAC address when accessing the host table.
 *
 * Register: \a RB:DISC_TBL:DISC_ACCESS_CFG_1
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_ACCESS_CFG_1(target)    VTSS_IOREG(target,0x66)

/**
 * \brief
 * Configures 32 LSB bits of the MAC address for the DISC_ENTRY.Used as
 * starting MAC address value during FIND SMALLEST Command.
 *
 * \details
 * 0xXXXXXXXX: Lower 32 bits of MAC address.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_1 . DISC_ENTRY_SMAC_LSB
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_1_DISC_ENTRY_SMAC_LSB(x)  (x)
#define  VTSS_M_RB_DISC_ACCESS_CFG_1_DISC_ENTRY_SMAC_LSB     0xffffffff
#define  VTSS_X_RB_DISC_ACCESS_CFG_1_DISC_ENTRY_SMAC_LSB(x)  (x)


/**
 * \brief Duplicast Discard Entry Data 2
 *
 * \details
 * Configures warious DISC_ENTRY parameters when accessing the host table
 *
 * Register: \a RB:DISC_TBL:DISC_ACCESS_CFG_2
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_ACCESS_CFG_2(target)    VTSS_IOREG(target,0x67)

/**
 * \brief
 * Duplicate counter for egress port 2. Incremented each time the entry is
 * used by a duplicate frame on port 2. Counter saturates at 3.
 *
 * \details
 * 0: No duplicates seen. If DISC_ENTRY_PORT_MASK[2] is set, the first copy
 * of the frame is seen on the port.
 * 1: First duplicate frame seen on port.
 * 2: Second duplicate seen on port.
 * 3: Third duplicate or higher seen on port.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_CNT_2
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_CNT_2(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_CNT_2     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_2(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * Duplicate counter for egress port 1. Incremented each time the entry is
 * used by a duplicate frame on port 1. Counter saturates at 3.
 *
 * \details
 * 0: No duplicates seen. If DISC_ENTRY_PORT_MASK[1] is set, the first copy
 * of the frame is seen on the port.
 * 1: First duplicate frame seen on port.
 * 2: Second duplicate seen on port.
 * 3: Third duplicate or higher seen on port.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_CNT_1
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_CNT_1(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_CNT_1     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_1(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/**
 * \brief
 * Duplicate counter for egress port 0. Incremented each time the entry is
 * used by a duplicate frame on port 0. Counter saturates at 3.
 *
 * \details
 * 0: No duplicates seen. If DISC_ENTRY_PORT_MASK[0] is set, the first copy
 * of the frame is seen on the port.
 * 1: First duplicate frame seen on port.
 * 2: Second duplicate seen on port.
 * 3: Third duplicate or higher seen on port.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_CNT_0
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_CNT_0(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_CNT_0     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_CNT_0(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * DISC_ENTRY age flag used to identify if a DISC_ENTRY is active of
 * not.The age flag is not cleared by HW. This ensures that the entry is
 * removed from the duplicate discard table after a maximum time after the
 * entry was created.The duplicate discard table can be aged by HW either a
 * CPU Scan command or through Automatic ageing (RB::DISC_AUTOAGE_CFG).
 *
 * \details
 * 0:  Not aged
 * n:  Aged n times.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_ENTRY_AGE_FLAG
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_AGE_FLAG(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_AGE_FLAG     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_AGE_FLAG(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Configures the port mask for the DISC_ENTRY.Port mask: Bit 0: LRE_A, bit
 * 1: LRE_B, bit 2: Interlink
 *
 * \details
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_ENTRY_PORTMASK
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_PORTMASK(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_PORTMASK     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_PORTMASK(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * Configures the DISC_ENTRY valid flag. Used to indicate that this entry
 * is active. This bit can be cleared for non locked entries by auto
 * learning or through the CPU_ACCESS_CMD UNLEARN command.
 *
 * \details
 * 0: Invalid
 * 1: Valid.
 *
 * Field: ::VTSS_RB_DISC_ACCESS_CFG_2 . DISC_ENTRY_VLD
 */
#define  VTSS_F_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_VLD  VTSS_BIT(0)
#define  VTSS_X_RB_DISC_ACCESS_CFG_2_DISC_ENTRY_VLD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Automated age scan configuration
 *
 * \details
 * Configures automated age scan of duplicate discard table.
 *
 * Register: \a RB:DISC_TBL:DISC_AUTOAGE_CFG
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_AUTOAGE_CFG(target)     VTSS_IOREG(target,0x68)

/**
 * \brief
 * Sets the unit time of PERIOD_VAL. Internally the auto aging
 * state-machine computes the aging period by shifting
 * RB:DISC_TBL:DISC_AUTOAGE_CFG.PERIOD_VAL by 3, 7, 11, 15 respectively.
 *
 * \details
 * 0: 161: 2562: 40963: 65536
 *
 * Field: ::VTSS_RB_DISC_AUTOAGE_CFG . UNIT_SIZE
 */
#define  VTSS_F_RB_DISC_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_RB_DISC_AUTOAGE_CFG_UNIT_SIZE     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_RB_DISC_AUTOAGE_CFG_UNIT_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * Time between automatic ageing of a row in
 * RB:DISC_TBL:DISC_AUTOAGE_CFG.UNIT_SIZE units of clock cycles.
 *
 * \details
 * n: Age period in RB:DISC_TBL:DISC_AUTOAGE_CFG.UNIT_SIZE amount of clock
 * cycles, i.e. for an RB:DISC_TBL:DISC_AUTOAGE_CFG.PERIOD_VAL = 1 the
 * hardware will age an row every RB:DISC_TBL:DISC_AUTOAGE_CFG.UNIT_SIZE
 * clock cycles.
 *	   e.g. To achieve a 60s aging period per entry (i.e. 256 rows),
 * then every row should age every ~234375 us. At 1 GHz frequency we can
 * choose UNIT_SIZE = 3 and PERIOD_VAL = ceil((234375 us *
 * 1000MHz)/(32768)) = 7153
 *
 * Field: ::VTSS_RB_DISC_AUTOAGE_CFG . PERIOD_VAL
 */
#define  VTSS_F_RB_DISC_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_RB_DISC_AUTOAGE_CFG_PERIOD_VAL     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_RB_DISC_AUTOAGE_CFG_PERIOD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of duplicate discard table
 *
 * Register: \a RB:DISC_TBL:DISC_AUTOAGE_CFG_1
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_AUTOAGE_CFG_1(target)   VTSS_IOREG(target,0x69)

/**
 * \brief
 * Enable autoage scan interval.
 *
 * \details
 * Field: ::VTSS_RB_DISC_AUTOAGE_CFG_1 . AUTOAGE_INTERVAL_ENA
 */
#define  VTSS_F_RB_DISC_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_DISC_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA  VTSS_BIT(1)
#define  VTSS_X_RB_DISC_AUTOAGE_CFG_1_AUTOAGE_INTERVAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Triggers an instant hardware autoage scan (once current scan
 * completes).The bit is cleared by HW when a full scan completes.
 *
 * \details
 * 0: No force
 * 1: Force start of autoage scan
 *
 * Field: ::VTSS_RB_DISC_AUTOAGE_CFG_1 . FORCE_HW_SCAN_SHOT
 */
#define  VTSS_F_RB_DISC_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_DISC_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT  VTSS_BIT(0)
#define  VTSS_X_RB_DISC_AUTOAGE_CFG_1_FORCE_HW_SCAN_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Automated age scan configuration and status
 *
 * \details
 * Configures automated age scan of host table
 *
 * Register: \a RB:DISC_TBL:DISC_AUTOAGE_CFG_2
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_AUTOAGE_CFG_2(target)   VTSS_IOREG(target,0x6a)

/**
 * \brief
 * Current autoage row. Changed on every autoage period. Indicate the
 * duplicate discard table row to be autoaged aged next.Incremented by
 * hardware during auto ageing.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n.
 *
 * Field: ::VTSS_RB_DISC_AUTOAGE_CFG_2 . NEXT_AGED_ROW
 */
#define  VTSS_F_RB_DISC_AUTOAGE_CFG_2_NEXT_AGED_ROW(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_RB_DISC_AUTOAGE_CFG_2_NEXT_AGED_ROW     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_RB_DISC_AUTOAGE_CFG_2_NEXT_AGED_ROW(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Sticky diagnostic status
 *
 * \details
 * Register: \a RB:DISC_TBL:DISC_EVENT_STICKY
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_EVENT_STICKY(target)    VTSS_IOREG(target,0x6b)

/**
 * \brief
 * Set when AUTOAGE scan completes.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE scan completes
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTOAGE_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY  VTSS_BIT(23)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Set when Autoage scan starts.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE scan started
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTOAGE_SCAN_STARTED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY  VTSS_BIT(22)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTOAGE_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Set when Autoage scan should be started before the last scan completed.
 *
 * \details
 * 0: No event has occurred
 * 1: AUTOAGE could not start before the current scan completed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTOAGE_START_DELAYED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY  VTSS_BIT(21)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTOAGE_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Set if a MAC address entry has been aged due to an autoage operation.
 *
 * \details
 * 0: No entries have been aged due to autoage.
 * 1: At least 1 entry has been aged due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTOAGE_AGED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTOAGE_AGED_STICKY  VTSS_BIT(20)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTOAGE_AGED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Set if a MAC address entry has been removed due to an autoage operation.
 *
 * \details
 * 0: No entries have been removed due to autoage.
 * 1: At least 1 entry has been removed due to autoage.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTOAGE_REMOVE_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTOAGE_REMOVE_STICKY  VTSS_BIT(19)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTOAGE_REMOVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Set if an autonomous learning operation has failed due to hash table
 * depletion (i.e. all entries in a row were locked). Write '1' to clear
 * this field.
 *
 * \details
 * 0: No autonomous learning operations have failed.
 * 1: An autonomous learning operation has failed.
 * Write '1' to clear this field.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_FAILED_STICKY  VTSS_BIT(18)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Set if a MAC address entry has been inserted into a MAC address table
 * column (bucket). Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been inserted into empty buckets
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_INSERT_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_INSERT_STICKY  VTSS_BIT(17)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Set if host entry has been updated. Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_REFRESH_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY  VTSS_BIT(16)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Set if a randomly selected non-locked and valid MAC address entry can
 * not be overwritten by a new SMAC. Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been replaced.
 * 1: An entry has not been replaced due to configuration.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_REPLACE_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY  VTSS_BIT(15)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Set if a randomly selected non-locked and valid MAC address entry has
 * been overwritten by a new SMAC. Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_REPLACE_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY  VTSS_BIT(14)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Set according to the replacement rule that was activated during
 * learning. Write '1' to clear this field.
 *
 * \details
 *
 *		      0: No action performed.
 *		      1: Replaced a free entry (same as
 * AUTO_LRN_INSERT_STICKY).
 *		      2: Replaced an entry with two or more seen
 * duplicates.
 *		      3: Replaced an entry with the same mac and the max.
 * sequence number.
 *		      4: Replaced an entry with the older age_flag.
 *		      5: Replaced a random entry.

 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . AUTO_LRN_REPLACE_ACTION_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_ACTION_STICKY(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_ACTION_STICKY     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_RB_DISC_EVENT_STICKY_AUTO_LRN_REPLACE_ACTION_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/**
 * \brief
 * Set when a direct CPU READ operation has occurred. Write '1' to clear
 * this field.
 *
 * \details
 * 0:  No update
 * 1: CPU read direct operation has occurred.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_READ_DIRECT_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_READ_DIRECT_STICKY  VTSS_BIT(10)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_READ_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Set when a direct CPU WRITE operation has occurred. Write '1' to clear
 * this field.
 *
 * \details
 * 0:  No update
 * 1: CPU write direct operation has occurred.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_WRITE_DIRECT_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY  VTSS_BIT(9)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_WRITE_DIRECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Set if a CPU LOOKUP operation has failed due to not found an entry.
 * Write '1' to clear this field.
 *
 * \details
 * 0:  No fail
 * 1: CPU lookup operation failed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LOOKUP_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY  VTSS_BIT(8)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LOOKUP_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Set if a CPU LOOKUP operation has succeeded. Write '1' to clear this
 * field.
 *
 * \details
 * 0:  No successful lookup
 * 1: Successful lookup.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LOOKUP_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LOOKUP_STICKY  VTSS_BIT(7)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LOOKUP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Set if a CPU UNLEARN operation has failed because the respective (valid)
 * entry was not found. Write '1' to clear this field.
 *
 * \details
 * 0:  No UNLEARN operation failed
 * 1: CPU UNLEARN operation failed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_UNLRN_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY  VTSS_BIT(6)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_UNLRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Set if a CPU UNLEARN operation has succeeded. Write '1' to clear this
 * field.
 *
 * \details
 * 0:  No CPU UNLEARN operation took place
 * 1:  CPU UNLEARN operations has succeeded.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_UNLRN_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_UNLRN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_UNLRN_STICKY  VTSS_BIT(5)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_UNLRN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Set if CPU learn replace can not be performed due to configuration.
 * Write '1' to clear this field.
 *
 * \details
 * 0: No learn based replacement failed.
 * 1: The replacement of 1 or more entries failed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LRN_REPLACE_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY  VTSS_BIT(4)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Set if a valid host entry has been updated (refreshed), i.e. a write
 * access to the same bucket with the same MAC has occurred. Write '1' to
 * clear this field.
 *
 * \details
 * 0: No entries have been refreshed.
 * 1: An entry has been refreshed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LRN_REFRESH_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LRN_REFRESH_STICKY  VTSS_BIT(3)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LRN_REFRESH_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Set if a valid host entry has been overwritten, i.e. a write access to
 * the same bucket with a changed MAC has occurred. Write '1' to clear this
 * field.
 *
 * \details
 * 0: No entries have been replaced.
 * 1: An entry has been replaced.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LRN_REPLACE_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_STICKY  VTSS_BIT(2)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LRN_REPLACE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Set if a host entry has been inserted into an empty host table
 * row,column (=bucket). Write '1' to clear this field.
 *
 * \details
 * 0: No entries have been inserted into an empty bucket
 * 1: An entry has been inserted into an empty bucket.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LRN_INSERT_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LRN_INSERT_STICKY  VTSS_BIT(1)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LRN_INSERT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set if an CPU learning operation has failed due to hash table depletion
 * (i.e. all entries in a row were locked). Write '1' to clear this field.
 *
 * \details
 * 0: No CPU LEARN operations has failed.
 * 1: A CPU LEARN operation has failed.
 *
 * Field: ::VTSS_RB_DISC_EVENT_STICKY . CPU_LRN_FAILED_STICKY
 */
#define  VTSS_F_RB_DISC_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_RB_DISC_EVENT_STICKY_CPU_LRN_FAILED_STICKY  VTSS_BIT(0)
#define  VTSS_X_RB_DISC_EVENT_STICKY_CPU_LRN_FAILED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Learn Diagnostic
 *
 * \details
 * Register: \a RB:DISC_TBL:DISC_LATEST_POS_STATUS
 *
 * @param target A \a ::vtss_target_RB_e target
 */
#define VTSS_RB_DISC_LATEST_POS_STATUS(target)  VTSS_IOREG(target,0x6c)

/**
 * \brief
 * This field holds the current (i.e. latest accessed) host table row
 * number after a CPU_ACCESS_CMD has been finished.
 *
 * \details
 * 0: Row 0
 * 1: Row 1
 * ...
 * n: Row n
 *
 * Field: ::VTSS_RB_DISC_LATEST_POS_STATUS . LATEST_ROW
 */
#define  VTSS_F_RB_DISC_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_ENCODE_BITFIELD(x,4,8)
#define  VTSS_M_RB_DISC_LATEST_POS_STATUS_LATEST_ROW     VTSS_ENCODE_BITMASK(4,8)
#define  VTSS_X_RB_DISC_LATEST_POS_STATUS_LATEST_ROW(x)  VTSS_EXTRACT_BITFIELD(x,4,8)

/**
 * \brief
 * This field holds the current (i.e. latest accessed) column number after
 * a CPU_ACCESS_CMD has been finished.
 *
 * \details
 * 0: Column (bucket) 0
 * 1: Column (bucket) 1
 * ...
 * n: Column (bucket) n
 *
 * Field: ::VTSS_RB_DISC_LATEST_POS_STATUS . LATEST_COL
 */
#define  VTSS_F_RB_DISC_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_RB_DISC_LATEST_POS_STATUS_LATEST_COL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_RB_DISC_LATEST_POS_STATUS_LATEST_COL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


#endif /* _VTSS_LAGUNA_REGS_RB_H_ */
