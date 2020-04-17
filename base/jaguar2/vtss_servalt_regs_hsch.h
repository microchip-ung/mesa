// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_HSCH_H_
#define _VTSS_SERVALT_REGS_HSCH_H_


#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HSCH
 *
 * Hierarchical Scheduler Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a HSCH:HSCH_L0_CFG
 *
 * Hierarchy configuration
 */


/** 
 * \brief Hierarchy configuration
 *
 * \details
 * Register: \a HSCH:HSCH_L0_CFG:HSCH_L0_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_L0_CFG_HSCH_L0_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xe00,gi,1,0,0)

/** 
 * \brief
 * Index of layer 1 element connected to. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_L0_CFG_HSCH_L0_CFG . L1_IDX
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_IDX(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_IDX     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_IDX(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Input of layer 1 element connected to
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_L0_CFG_HSCH_L0_CFG . L1_INP
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_INP(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_INP     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HSCH_HSCH_L0_CFG_HSCH_L0_CFG_L1_INP(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a HSCH:HSCH_L1_CFG
 *
 * Hierarchy configuration
 */


/** 
 * \brief Hierarchy configuration
 *
 * \details
 * Register: \a HSCH:HSCH_L1_CFG:HSCH_L1_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L1_CNT (??), 0-63
 */
#define VTSS_HSCH_HSCH_L1_CFG_HSCH_L1_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xd00,gi,1,0,0)

/** 
 * \brief
 * Index of layer 2 element connected to by this layer 1 element
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_L1_CFG_HSCH_L1_CFG . L2_IDX
 */
#define  VTSS_F_HSCH_HSCH_L1_CFG_HSCH_L1_CFG_L2_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSCH_HSCH_L1_CFG_HSCH_L1_CFG_L2_IDX     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSCH_HSCH_L1_CFG_HSCH_L1_CFG_L2_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a HSCH:HSCH_L1W
 *
 * Win data for layer 1
 */


/** 
 * \brief Winner table
 *
 * \details
 * Register: \a HSCH:HSCH_L1W:HSCH_L1W
 *
 * @param gi Replicator: x_GAZ_HSCH_L1_CNT (??), 0-63
 * @param ri Replicator: x_GAZ_HSCH_L1_WID (??), 0-31
 */
#define VTSS_HSCH_HSCH_L1W_HSCH_L1W(gi,ri)   VTSS_IOREG_IX(VTSS_TO_HSCH,0x1000,gi,32,ri,0)

/** 
 * \brief
 * Contains the layer 0 scheduling history descriptor for a frames passing
 * through layer-1 element A, input B. Group replication index is A and
 * register replication is B.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_L1W_HSCH_L1W . WIN_SHIST
 */
#define  VTSS_F_HSCH_HSCH_L1W_HSCH_L1W_WIN_SHIST(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_HSCH_HSCH_L1W_HSCH_L1W_WIN_SHIST     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_HSCH_HSCH_L1W_HSCH_L1W_WIN_SHIST(x)  VTSS_EXTRACT_BITFIELD(x,0,18)

/**
 * Register Group: \a HSCH:HSCH_CFG
 *
 * Configuration of scheduling system and shapers
 */


/** 
 * \brief Shaping configuration of the SE
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:CIR_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_CFG_CIR_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,0)

/** 
 * \brief
 * Leak rate for this shaper. Unit is defined by the leak list period the
 * shaper is attached to (see HSCH_LEAK_CFG.LEAK_TIME).
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_HSCH_HSCH_CFG_CIR_CFG_CIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_HSCH_CFG_CIR_CFG_CIR_RATE     VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_HSCH_CFG_CIR_CFG_CIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,17)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4096 bytes. The shaper is
 * disabled when CIR_BURST=0.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_HSCH_HSCH_CFG_CIR_CFG_CIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_HSCH_CFG_CIR_CFG_CIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_HSCH_CFG_CIR_CFG_CIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Excess rate configuration
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:EIR_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_CFG_EIR_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,1)

/** 
 * \brief
 * Leak rate for this shaper. Same unit as CIR_RATE unit. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_EIR_CFG . EIR_RATE
 */
#define  VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE     VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,17)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4096 bytes. The dual leaky bucket
 * shaper operates as a single leaky bucket shaper when EIR_BURST=0. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_EIR_CFG . EIR_BURST
 */
#define  VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of shaper and scheduling algorithm
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_CFG_SE_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,2)

/** 
 * \brief
 * Number of inputs running with DWRR algorithm, otherwise strict. Strict
 * inputs always have the highest input index.
 *
 * \details 
 * 0: No inputs uses DWRR
 * 1: 2 lowest inputs used DWRR
 * n: (n+1) lowest inputs uses DWRR
 *
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_DWRR_CNT
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Enable AVB mode for this shaper, creating burst capacity only when data
 * is available.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_AVB_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA  VTSS_BIT(5)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Accounting mode for this shaper.
 *
 * \details 
 * 0: Line rate. Shape bytes including HSCH_MISC_CFG.FRM_ADJ.
 * 1: Data rate. Shape bytes excluding IPG.
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape framed with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_FRM_MODE
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Accounting mode for the dwrr distribution.
 *
 * \details 
 * 0: Line rate. Cost is frame length including HSCH_MISC_CFG.FRM_ADJ.
 * 1: Data rate. Cost is frame length excluding IPG.
 * 2. Frame rate. Cost is 1.
 * 3: Reserved.
 *
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_DWRR_FRM_MODE
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Block traffic through this element. This can be used for transfering
 * element to other locations in the scheduling hierarchy
 *
 * \details 
 * 0: Traffic can flow through this element
 * 1: This element will block its output
 *
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_STOP
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_STOP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_STOP  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of the connections between SEs
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CONNECT
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_CFG_SE_CONNECT(gi)    VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,3)

/** 
 * \brief
 * Forms the leak chains.

 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CONNECT . SE_LEAK_LINK
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_LINK(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_LINK     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_LINK(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Configuration of which fill levels in the queue system that the DLB shapers use to trigger excess information rate
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_DLB_SENSE
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,4)

/** 
 * \brief
 * QoS class used when SE_DLB_PRIO_ENA is set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_PRIO
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Destination port used when SE_DLB_DPORT_ENA is set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_DPORT
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Not connected.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_SPORT_OBSOLETE
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_OBSOLETE(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_OBSOLETE     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_OBSOLETE(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Enable priority awareness by the DLB shaper. If set, the DLB shaper
 * allows excess information rate when the egress buffer use for QoS class
 * SE_DLB_PRIO has reached threshold BUF_PRIO_SHR_E[SE_DLB_PRIO] minus 3000
 * bytes.
 * 
 * If both SE_DLB_PRIO_ENA and SE_DLB_SPORT_ENA are set, the excess
 * information rate is alllowed when the ingress buffer use for QoS class
 * per source port has reached threshold BUF_Q_RSRV_I[SE_DLB_PRIO,
 * SE_DLB_SPORT] minus 3000 bytes. 
 * 
 * If both SE_DLB_PRIO_ENA and SE_DLB_DPORT_ENA are set, the excess
 * information rate is alllowed when the egress buffer use for QoS class
 * per destination port has reached threshold BUF_Q_RSRV_E[SE_DLB_PRIO,
 * SE_DLB_DPORT] minus 3000 bytes. 
 * 
 * If multiple awareness functions (SE_DLB_PRIO_ENA, SE_DLB_SPORT_ENA,
 * SE_DLB_DPORT_ENA) are enabled, all relevant thresholds must be exceeded
 * before excess information rate is allowed.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_PRIO_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO_ENA  VTSS_BIT(2)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable destination port awareness by the DLB shaper. If set, the DLB
 * shaper allows excess information rate when the egress buffer use for
 * destination port SE_DLB_SPORT has reached threshold
 * BUF_P_RSRV_E[SE_DLB_DPORT] minus 3000 bytes.
 * 
 * If multiple awareness functions (SE_DLB_PRIO_ENA, SE_DLB_SPORT_ENA,
 * SE_DLB_DPORT_ENA) are enabled, all relevant thresholds must be exceeded
 * before excess information rate is allowed.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_DPORT_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA  VTSS_BIT(1)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable scheduling element awareness by the DLB shaper. If set, the DLB
 * shaper allows excess information rate when the egress buffer use for the
 * scheduling element has reached threshold SE_RSRV_E[SE_IDX] minus 3000
 * bytes.

 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_SE_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SE_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:HSCH_STATUS
 *
 * Status of scheduling system and shapers
 */


/** 
 * \brief CIR status
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:CIR_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_IDX_MAX (??), 0-415
 */
#define VTSS_HSCH_HSCH_STATUS_CIR_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x1800,gi,4,0,0)

/** 
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief EIR status
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:EIR_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_IDX_MAX (??), 0-415
 */
#define VTSS_HSCH_HSCH_STATUS_EIR_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x1800,gi,4,0,1)

/** 
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_EIR_STATE . EIR_LVL
 */
#define  VTSS_F_HSCH_HSCH_STATUS_EIR_STATE_EIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_HSCH_STATUS_EIR_STATE_EIR_LVL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_HSCH_STATUS_EIR_STATE_EIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief State of the inputs to this SE
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:SE_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_IDX_MAX (??), 0-415
 */
#define VTSS_HSCH_HSCH_STATUS_SE_STATE(gi)   VTSS_IOREG_IX(VTSS_TO_HSCH,0x1800,gi,4,0,2)

/** 
 * \brief
 * The queue selector must be updated about the state of this element
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_SE_STATE . FORCE_UPD
 */
#define  VTSS_F_HSCH_HSCH_STATUS_SE_STATE_FORCE_UPD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_STATUS_SE_STATE_FORCE_UPD  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_STATUS_SE_STATE_FORCE_UPD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:QSHP_CFG
 *
 * Configuration of queue shapers
 */


/** 
 * \brief Queue Shaping configuration
 *
 * \details
 * Register: \a HSCH:QSHP_CFG:QSHP_CIR_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_WID (??), 0-15
 */
#define VTSS_HSCH_QSHP_CFG_QSHP_CIR_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xd80,gi,2,0,0)

/** 
 * \brief
 * Leak rate for this shaper. Unit is defined by the leak list period the
 * shaper is attached to (see HSCH_LEAK_CFG.LEAK_TIME).
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_CFG_QSHP_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_RATE     VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,17)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4096 kilobytes. The shaper is
 * disabled when CIR_BURST=0.
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_CFG_QSHP_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_QSHP_CFG_QSHP_CIR_CFG_CIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of queue shaper
 *
 * \details
 * Register: \a HSCH:QSHP_CFG:QSHP_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_WID (??), 0-15
 */
#define VTSS_HSCH_QSHP_CFG_QSHP_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_HSCH,0xd80,gi,2,0,1)

/** 
 * \brief
 * Accounting mode for this shaper.
 *
 * \details 
 * 0: Line rate. Shape bytes including HSCH_MISC_CFG.FRM_ADJ.
 * 1: Data rate. Shape bytes excluding IPG.
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape framed with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_HSCH_QSHP_CFG_QSHP_CFG . SE_FRM_MODE
 */
#define  VTSS_F_HSCH_QSHP_CFG_QSHP_CFG_SE_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_QSHP_CFG_QSHP_CFG_SE_FRM_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_QSHP_CFG_QSHP_CFG_SE_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HSCH:QSHP_ALLOC_CFG
 *
 * Assign queue shapers to queues
 */


/** 
 * \brief Assign queue shapers to queues
 *
 * \details
 * Register: \a HSCH:QSHP_ALLOC_CFG:QSHP_ALLOC_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x2000,gi,2,0,0)

/** 
 * \brief
 * First input using queue shapers.
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG . QSHP_MIN
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MIN(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MIN     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * Last input using queue shapers. A value lower than the SHP_MIN input
 * disables queue shaping.
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG . QSHP_MAX
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MAX(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MAX     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/** 
 * \brief
 * First input using queue shapers are using this queue shaper index.
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG . QSHP_BASE
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_BASE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_BASE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_ALLOC_CFG_QSHP_BASE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Configuration of the connections between queue shapers
 *
 * \details
 * Register: \a HSCH:QSHP_ALLOC_CFG:QSHP_CONNECT
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_CNT (??), 0-415
 */
#define VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x2000,gi,2,0,1)

/** 
 * \brief
 * Forms the leak chains.

 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT . SE_LEAK_LINK
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT_SE_LEAK_LINK(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT_SE_LEAK_LINK     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_CONNECT_SE_LEAK_LINK(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a HSCH:QSHP_STATUS
 *
 * Status of queue shapers
 */


/** 
 * \brief CIR status
 *
 * \details
 * Register: \a HSCH:QSHP_STATUS:QSHP_CIR_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_L0_WID (??), 0-15
 */
#define VTSS_HSCH_QSHP_STATUS_QSHP_CIR_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xda0,gi,1,0,0)

/** 
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details 
 * Field: ::VTSS_HSCH_QSHP_STATUS_QSHP_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_HSCH_QSHP_STATUS_QSHP_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_QSHP_STATUS_QSHP_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_QSHP_STATUS_QSHP_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

/**
 * Register Group: \a HSCH:HSCH_INP_STATE
 *
 * Status of scheduling element inputs
 */


/** 
 * \brief INPUT state
 *
 * \details
 * Register: \a HSCH:HSCH_INP_STATE:INP_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_INPST_CNT (??), 0-1
 */
#define VTSS_HSCH_HSCH_INP_STATE_INP_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xdb0,gi,1,0,0)

/** 
 * \brief
 * Returns the 32 input states for se cfg_se_idx, from offset
 * 32*replication
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_INP_STATE_INP_STATE . INP_STATE
 */
#define  VTSS_F_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE(x)  (x)
#define  VTSS_M_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE     0xffffffff
#define  VTSS_X_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE(x)  (x)

/**
 * Register Group: \a HSCH:HSCH_DWRR
 *
 * Configure DWRR weights
 */


/** 
 * \brief Configuration and status of a dwrr entry
 *
 * \details
 * Register: \a HSCH:HSCH_DWRR:DWRR_ENTRY
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_INP_MAX (??), 0-63
 */
#define VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY(gi)   VTSS_IOREG_IX(VTSS_TO_HSCH,0xd40,gi,1,0,0)

/** 
 * \brief
 * When a specific input to an element is used, the cost is used when
 * updating the balance.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY . DWRR_COST
 */
#define  VTSS_F_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_COST(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Current balance of the input
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY . DWRR_BALANCE
 */
#define  VTSS_F_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_BALANCE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_BALANCE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_HSCH_HSCH_DWRR_DWRR_ENTRY_DWRR_BALANCE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a HSCH:HSCH_MISC
 *
 * Miscellaneous scheduler configuration
 */


/** 
 * \brief Common config for HSCH and policer module
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_MISC_CFG
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG    VTSS_IOREG(VTSS_TO_HSCH,0xdb2)

/** 
 * \brief
 * Set this to one to disabled all leaking from leaky bucket shapers
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . LEAK_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS  VTSS_BIT(5)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Values to add each frame when frame length adjustment is in use.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . FRM_ADJ
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Configuration selection register
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_CFG_CFG
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG     VTSS_IOREG(VTSS_TO_HSCH,0xdb3)

/** 
 * \brief
 * The DWRR balances and queue shapers will be accessed for the scheduling
 * element indexed by this field.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG . CFG_SE_IDX
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(x)  VTSS_ENCODE_BITFIELD(x,14,9)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX     VTSS_ENCODE_BITMASK(14,9)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_CFG_CFG_CFG_SE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,14,9)

/** 
 * \brief
 * The HSCH layer set in this field will be accessed by the configuration
 * interfaces.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG . HSCH_LAYER
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Skip a hierarchy update every time this number of updates has been done.
 * If zero, the feature is disabled. Setting to 4095 will disable hierachy
 * updates.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG . CSR_GRANT
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_CSR_GRANT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_CSR_GRANT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_CFG_CFG_CSR_GRANT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per front port and for each of the two CPU
 * ports (11+12).
 *
 * Register: \a HSCH:HSCH_MISC:PORT_MODE
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 */
#define VTSS_HSCH_HSCH_MISC_PORT_MODE(ri)    VTSS_IOREG(VTSS_TO_HSCH,0xdb4 + (ri))

/** 
 * \brief
 * Disable dequeuing from the egress queues. Frames are not discarded, but
 * may become aged when dequeuing is reenabled.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . DEQUEUE_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS  VTSS_BIT(4)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Disable aging of all frames transmitted to the port.
 * 
 * Frame aging related parameters:
 * QSYS:SYSTEM:FRM_AGING.MAX_AGE
 * HSCH:HSCH_MISC:PORT_MODE.AGE_DIS
 * DSM:CFG:BUF_CFG.AGING_ENA
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . AGE_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS  VTSS_BIT(3)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_AGE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable truncation of stack learnall frames.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . TRUNC_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_TRUNC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_TRUNC_ENA  VTSS_BIT(2)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_TRUNC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Increase DP by one in case scheduled frame passed due to excess rate
 * shaper.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . EIR_REMARK_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_EIR_REMARK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_EIR_REMARK_ENA  VTSS_BIT(1)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_EIR_REMARK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Select the priority mode for CPU copies transmitted on the port.
 *
 * \details 
 * 0: IFH CPU mask shows all CPU queues the frame applies to. Priority of
 * frame set to the CPU queue the frame copy is generated for
 * 1: IFH CPU mask shows the CPU queue number the frame copy is generated
 * for. Priority of frame set to the priority selected for the particular
 * frame copy (see QFWD::FRAME_COPY_CFG)
 *
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . CPU_PRIO_MODE
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Per port PFC configuration
 *
 * \details
 * These configurations exists per front port.
 *
 * Register: \a HSCH:HSCH_MISC:PFC_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-10
 */
#define VTSS_HSCH_HSCH_MISC_PFC_CFG(ri)      VTSS_IOREG(VTSS_TO_HSCH,0xdc3 + (ri))

/** 
 * \brief
 * Set the layer at which PFC status should be applied for this port. Only
 * layers 1 and 2 supports PFC blocking of the hierarchy.
 *
 * \details 
 * 0: Dont block any branches through PFC status
 * 1: Use pfc status for the port on layer 1
 * 2: Use pfc status for the port on layer 2
 * 3: Reserved
 *
 * Field: ::VTSS_HSCH_HSCH_MISC_PFC_CFG . PFC_LAYER
 */
#define  VTSS_F_HSCH_HSCH_MISC_PFC_CFG_PFC_LAYER(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_HSCH_HSCH_MISC_PFC_CFG_PFC_LAYER     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_HSCH_HSCH_MISC_PFC_CFG_PFC_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Set to the scheduling element number which should be affected by pfc
 * status for this port.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PFC_CFG . PFC_SE
 */
#define  VTSS_F_HSCH_HSCH_MISC_PFC_CFG_PFC_SE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_HSCH_MISC_PFC_CFG_PFC_SE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_HSCH_MISC_PFC_CFG_PFC_SE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Enable large scheduling elements
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_LARGE_ENA
 *
 * @param ri Replicator: x_GAZ_HSCH_LARGE_CFG_SIZE (??), 0-6
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_LARGE_ENA(ri)  VTSS_IOREG(VTSS_TO_HSCH,0xdce + (ri))

/** 
 * \brief
 * Bit n in replication k enables extended width on scheduling element
 * (32k+n)*2. Scheduling element (32k+n)*2+1 must not be used if enabled.
 * Fx. if scheduling element 180 should handle 16 inputs, HSCH_LARGE_ENA[2]
 * bit 26 should be set to 1, and element 181 must not be used. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_LARGE_ENA . HSCH_LARGE_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_LARGE_ENA_HSCH_LARGE_ENA(x)  (x)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_LARGE_ENA_HSCH_LARGE_ENA     0xffffffff
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_LARGE_ENA_HSCH_LARGE_ENA(x)  (x)


/** 
 * \brief Cellbus configuration
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:OUTB_CPU_SHARE_ENA
 */
#define VTSS_HSCH_HSCH_MISC_OUTB_CPU_SHARE_ENA  VTSS_IOREG(VTSS_TO_HSCH,0xdd5)

/** 
 * \brief
 * When enabled, unused bandwidth sharing will be granted to the an
 * internal CPUport, only when the calendar designated port is another
 * internal CPU port. The OUTB_SHARE_ENA must be configured for the CPU
 * ports when this is enabled
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_OUTB_CPU_SHARE_ENA . OUTB_CPU_SHARE_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Cellbus configuration
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:OUTB_SHARE_ENA
 *
 * @param ri Register: OUTB_SHARE_ENA (??), 0-3
 */
#define VTSS_HSCH_HSCH_MISC_OUTB_SHARE_ENA(ri)  VTSS_IOREG(VTSS_TO_HSCH,0xdd6 + (ri))

/** 
 * \brief
 * Sets the minimum distance between grants to an internal port. Extra
 * grants are disabled when configured value is 0, otherwise the port seeks
 * extra bandwidth, and the minimim distance in clock cycles is given by
 * this value. The four replications are for internal CPU 0, internal CPU
 * 1, VD0 and VD1.
 * 
 * Setting a value of 14 grants extra bandwidth every 14 cycles, which for
 * minimum sized frames corresponds to 84 bytes per 14 x 6,4 ns, or
 * 7.5Gbps.
 * 
 * Setting a value of 10 grants every 10 cycles, corresponding to 84 bytes
 * per 64 ns, or 10.5Gbps.
 * 
 * Minimum value for VD0 is 14, and 8 for the other internal ports.

 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_OUTB_SHARE_ENA . OUTB_SHARE_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_HSCH_MISC_OUTB_SHARE_ENA_OUTB_SHARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Enable flushing of selected framesy
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:FLUSH_CTRL
 */
#define VTSS_HSCH_HSCH_MISC_FLUSH_CTRL       VTSS_IOREG(VTSS_TO_HSCH,0xdda)

/** 
 * \brief
 * Set to enable flushing of all frames matching the flush criterias in
 * this register
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA  VTSS_BIT(20)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Frame received on the configured port will be flushed if set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_SRC
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SRC(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SRC  VTSS_BIT(19)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Frame transmitted on the configured port will be flushed if set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_DST
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_DST(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_DST  VTSS_BIT(18)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_DST(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Flushing will only affect frames on this port.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_PORT
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_PORT(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * Frames transmitted from the configured queue specified in FLUSH_HIER
 * will be flushed.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_QUEUE
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_QUEUE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_QUEUE  VTSS_BIT(13)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_QUEUE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Frames transmitted from the configured SE index specified in FLUSH_HIER
 * will be flushed.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_SE
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SE  VTSS_BIT(12)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_SE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Flushing will only affect frames from this queue or SE.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_FLUSH_CTRL . FLUSH_HIER
 */
#define  VTSS_F_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_HIER(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_HIER     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_HSCH_MISC_FLUSH_CTRL_FLUSH_HIER(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Internal events for debugging only
 *
 * \details
 * Core events.
 *
 * Register: \a HSCH:HSCH_MISC:EVENTS_CORE
 */
#define VTSS_HSCH_HSCH_MISC_EVENTS_CORE      VTSS_IOREG(VTSS_TO_HSCH,0xddb)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_EVENTS_CORE . EV_HSCH
 */
#define  VTSS_F_HSCH_HSCH_MISC_EVENTS_CORE_EV_HSCH(x)  VTSS_ENCODE_BITFIELD(x,5,7)
#define  VTSS_M_HSCH_HSCH_MISC_EVENTS_CORE_EV_HSCH     VTSS_ENCODE_BITMASK(5,7)
#define  VTSS_X_HSCH_HSCH_MISC_EVENTS_CORE_EV_HSCH(x)  VTSS_EXTRACT_BITFIELD(x,5,7)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_EVENTS_CORE . EV_FRD
 */
#define  VTSS_F_HSCH_HSCH_MISC_EVENTS_CORE_EV_FRD(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_HSCH_HSCH_MISC_EVENTS_CORE_EV_FRD     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_HSCH_HSCH_MISC_EVENTS_CORE_EV_FRD(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * If an frame is added to an invalid queue in the scheduling hierarchy,
 * this sticky bit will be set, and the violating request is see the
 * EVENT_ENQ_ERR register.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_EVENTS_CORE . EV_ENQ_ERR
 */
#define  VTSS_F_HSCH_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Internal control for debugging only
 *
 * \details
 * Core events.
 *
 * Register: \a HSCH:HSCH_MISC:DEBUG_CTRL
 */
#define VTSS_HSCH_HSCH_MISC_DEBUG_CTRL       VTSS_IOREG(VTSS_TO_HSCH,0xddc)

/** 
 * \brief
 * Force port to be frame pending. To be used when a port for some unknown
 * reason gets stuck. The port configured in FLUSH_PORT will be marked
 * pending.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_DEBUG_CTRL . PORT_KICK
 */
#define  VTSS_F_HSCH_HSCH_MISC_DEBUG_CTRL_PORT_KICK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_DEBUG_CTRL_PORT_KICK  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_DEBUG_CTRL_PORT_KICK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Return information about scheduler busyness
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_UPDATE_STAT
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_UPDATE_STAT  VTSS_IOREG(VTSS_TO_HSCH,0xddd)

/** 
 * \brief
 * Return the maximum period of constant update need. Clear by writing one
 * to the lsb of the register.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_UPDATE_STAT . HSCH_UPDATE_CNT
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Information about enqueueing error
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:EVENT_ENQ_ERR
 */
#define VTSS_HSCH_HSCH_MISC_EVENT_ENQ_ERR    VTSS_IOREG(VTSS_TO_HSCH,0xdde)

/** 
 * \brief
 * Contains last enqueuing error egress port number
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_EVENT_ENQ_ERR . ENQ_ERR_PORT
 */
#define  VTSS_F_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Scheduling element being violated.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_EVENT_ENQ_ERR . ENQ_ERR_QNO
 */
#define  VTSS_F_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_QNO(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_QNO     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_QNO(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief System clock period configuration
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:SYS_CLK_PER
 */
#define VTSS_HSCH_HSCH_MISC_SYS_CLK_PER      VTSS_IOREG(VTSS_TO_HSCH,0xddf)

/** 
 * \brief
 * Must be set to the system clock period with unit 100 picoseconds.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_SYS_CLK_PER . SYS_CLK_PER_100PS
 */
#define  VTSS_F_HSCH_HSCH_MISC_SYS_CLK_PER_SYS_CLK_PER_100PS(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_HSCH_MISC_SYS_CLK_PER_SYS_CLK_PER_100PS     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_HSCH_MISC_SYS_CLK_PER_SYS_CLK_PER_100PS(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Force update of an element in the hierarchy
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_FORCE_CTRL
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_FORCE_CTRL  VTSS_IOREG(VTSS_TO_HSCH,0xde0)

/** 
 * \brief
 * Set to layer in which an element must be updated.
 *
 * \details 
 * 0: Update a layer 0 element
 * 1: Update a layer 1 element
 * 2: Update a layer 2 element
 * 3: Reserved

 *
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_FORCE_CTRL . HFORCE_LAYER
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_LAYER(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_LAYER     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Set to index of element to force
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_FORCE_CTRL . HFORCE_SE_IDX
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_SE_IDX(x)  VTSS_ENCODE_BITFIELD(x,1,9)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_SE_IDX     VTSS_ENCODE_BITMASK(1,9)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_SE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,1,9)

/** 
 * \brief
 * Update the requested scheduling element
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_FORCE_CTRL . HFORCE_1SHOT
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_1SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_1SHOT  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_FORCE_CTRL_HFORCE_1SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:HSCH_LEAK_LISTS
 *
 * Configuration of leak lists
 */


/** 
 * \brief Leak configuration per leak group
 *
 * \details
 * Register: \a HSCH:HSCH_LEAK_LISTS:HSCH_LEAK_CFG
 *
 * @param gi Register: HSCH_LEAK_LISTS (??), 0-3
 * @param ri Register: HSCH_LEAK_CFG (??), 0-3
 */
#define VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xde1,gi,4,ri,0)

/** 
 * \brief
 * Number of nanoseconds between each traversal of the leak list. A value
 * of 10000 correspond to 10us. Each traversal subtracts the configured
 * rate from the shaper buckets, counting bits. With the value of 10000, a
 * rate of 1 corresponds to 1 bit per 10us, or 100kbps.
 * A leak group can be set up for 16kbps unit by seting the leak_time to 1
 * bit per 62500 nanoseconds.

 *
 * \details 
 * 0: Leaking disabled
 * 62500: 16kbps unit
 * 10000: 100kbps unit
 * 1000:  1Mbps unit
 * (any other)
 *
 * Field: ::VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG . LEAK_TIME
 */
#define  VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME(x)  VTSS_ENCODE_BITFIELD(x,13,18)
#define  VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME     VTSS_ENCODE_BITMASK(13,18)
#define  VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME(x)  VTSS_EXTRACT_BITFIELD(x,13,18)

/** 
 * \brief
 * First shaper in the leak group
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG . LEAK_FIRST
 */
#define  VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST(x)  VTSS_ENCODE_BITFIELD(x,1,12)
#define  VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST     VTSS_ENCODE_BITMASK(1,12)
#define  VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_FIRST(x)  VTSS_EXTRACT_BITFIELD(x,1,12)

/** 
 * \brief
 * The leak group didnt succeed traversing all shapers. Rates will be
 * wrong.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG . LEAK_ERR
 */
#define  VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_ERR  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_SERVALT_REGS_HSCH_H_ */
