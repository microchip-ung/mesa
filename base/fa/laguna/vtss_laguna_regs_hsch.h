// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_HSCH_H_
#define _VTSS_LAGUNA_REGS_HSCH_H_

#include "vtss_laguna_regs_common.h"

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
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_HSCH_L0_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_HSCH,0x2800,gi,1,0,0)

/**
 * \brief
 * Next layer for queue scheduled through the layer 0 element.
 *
 * \details
 * 0: Layer 1 is the next layer
 * 1: Layer 2 is the next layer
 *
 * Field: ::VTSS_HSCH_HSCH_L0_CFG . NEXT_LAYER
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_HSCH_HSCH_L0_CFG_NEXT_LAYER   VTSS_BIT(21)
#define  VTSS_X_HSCH_HSCH_L0_CFG_NEXT_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Index of element connected to in selected layer
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_L0_CFG . NEXT_IDX
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_HSCH_HSCH_L0_CFG_NEXT_IDX     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_HSCH_HSCH_L0_CFG_NEXT_IDX(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/**
 * \brief
 * Input of layer element connected to in selected layer
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_L0_CFG . NEXT_INP
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HSCH_HSCH_L0_CFG_NEXT_INP     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HSCH_HSCH_L0_CFG_NEXT_INP(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * A 8-bit vector which specifies preemptible queues within the 8
 * priorities (with bit-0 for priority-0 and bit-7 for priority-7).A value
 * of '1' in the bit positioned at 'p' indicates that the egress frame with
 * priority 'p' can be preemptible.This is nothing but "frame preemption
 * status" defined in IEEE802.1Qbu/D3.0 with an encoding of 'express=0' and
 * 'preemptible=1'.Note: This vector should be left to default value if
 * preemption is not supported on the port (i.e., all queues has express
 * traffic).
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_L0_CFG . P_QUEUES
 */
#define  VTSS_F_HSCH_HSCH_L0_CFG_P_QUEUES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_HSCH_L0_CFG_P_QUEUES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_HSCH_L0_CFG_P_QUEUES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[1] (??), 0-34
 */
#define VTSS_HSCH_HSCH_L1_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_HSCH,0x2340,gi,1,0,0)

/**
 * \brief
 * Index of layer 2 element connected to by this layer 1 element.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_L1_CFG . NEXT_IDX
 */
#define  VTSS_F_HSCH_HSCH_L1_CFG_NEXT_IDX(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_HSCH_HSCH_L1_CFG_NEXT_IDX     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_HSCH_HSCH_L1_CFG_NEXT_IDX(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/**
 * \brief
 * Input of layer 2 element connected to
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_L1_CFG . NEXT_INP
 */
#define  VTSS_F_HSCH_HSCH_L1_CFG_NEXT_INP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSCH_HSCH_L1_CFG_NEXT_INP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSCH_HSCH_L1_CFG_NEXT_INP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_CIR_CFG(gi)                VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,0)

/**
 * \brief
 * Leak rate for this shaper. Unit is defined by the leak list period the
 * shaper is attached to (see HSCH_TIMER_CFG.LEAK_TIME).
 *
 * \details
 * Field: ::VTSS_HSCH_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_HSCH_CIR_CFG_CIR_RATE(x)      VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_CIR_CFG_CIR_RATE         VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_CIR_CFG_CIR_RATE(x)      VTSS_EXTRACT_BITFIELD(x,6,17)

/**
 * \brief
 * Burst capacity of this shaper. Unit is 4096 bytes. The shaper is
 * disabled when CIR_BURST=0.
 *
 * \details
 * Field: ::VTSS_HSCH_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_HSCH_CIR_CFG_CIR_BURST(x)     VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_CIR_CFG_CIR_BURST        VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_CIR_CFG_CIR_BURST(x)     VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Excess rate configuration
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:EIR_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_EIR_CFG(gi)                VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,1)

/**
 * \brief
 * Leak rate for this shaper. Same unit as CIR_RATE unit.
 *
 * \details
 * Field: ::VTSS_HSCH_EIR_CFG . EIR_RATE
 */
#define  VTSS_F_HSCH_EIR_CFG_EIR_RATE(x)      VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_EIR_CFG_EIR_RATE         VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_EIR_CFG_EIR_RATE(x)      VTSS_EXTRACT_BITFIELD(x,6,17)

/**
 * \brief
 * Burst capacity of this shaper. Unit is 4096 bytes. The dual leaky bucket
 * shaper operates as a single leaky bucket shaper when EIR_BURST=0.
 *
 * \details
 * Field: ::VTSS_HSCH_EIR_CFG . EIR_BURST
 */
#define  VTSS_F_HSCH_EIR_CFG_EIR_BURST(x)     VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_EIR_CFG_EIR_BURST        VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_EIR_CFG_EIR_BURST(x)     VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Configuration of shaper and scheduling algorithm
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_SE_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,2)

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
 * Field: ::VTSS_HSCH_SE_CFG . SE_DWRR_CNT
 */
#define  VTSS_F_HSCH_SE_CFG_SE_DWRR_CNT(x)    VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_HSCH_SE_CFG_SE_DWRR_CNT       VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_HSCH_SE_CFG_SE_DWRR_CNT(x)    VTSS_EXTRACT_BITFIELD(x,6,5)

/**
 * \brief
 * Enable AVB mode for this shaper, creating burst capacity only when data
 * is available.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_CFG . SE_AVB_ENA
 */
#define  VTSS_F_HSCH_SE_CFG_SE_AVB_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSCH_SE_CFG_SE_AVB_ENA        VTSS_BIT(5)
#define  VTSS_X_HSCH_SE_CFG_SE_AVB_ENA(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Accounting mode for this shaper.
 *
 * \details
 * 0: Line rate. Shape bytes including HSCH_MISC_PORT_CFG.FRM_ADJ.
 * 1: Data rate. Shape bytes excluding IPG.
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape framed with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_HSCH_SE_CFG . SE_FRM_MODE
 */
#define  VTSS_F_HSCH_SE_CFG_SE_FRM_MODE(x)    VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_HSCH_SE_CFG_SE_FRM_MODE       VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_HSCH_SE_CFG_SE_FRM_MODE(x)    VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Accounting mode for the DWRR distribution.
 *
 * \details
 * 0: Line rate. Cost is frame length including HSCH_MISC_PORT_CFG.FRM_ADJ.
 * 1: Data rate. Cost is frame length excluding IPG.
 * 2. Frame rate. Cost is 1.
 * 3: Reserved.
 *
 * Field: ::VTSS_HSCH_SE_CFG . SE_DWRR_FRM_MODE
 */
#define  VTSS_F_HSCH_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HSCH_SE_CFG_SE_DWRR_FRM_MODE     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HSCH_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Block traffic through this element. This can be used for transferring
 * element to other locations in the scheduling hierarchy
 *
 * \details
 * 0: Traffic can flow through this element
 * 1: This element will block its output
 *
 * Field: ::VTSS_HSCH_SE_CFG . SE_STOP
 */
#define  VTSS_F_HSCH_SE_CFG_SE_STOP(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_SE_CFG_SE_STOP           VTSS_BIT(0)
#define  VTSS_X_HSCH_SE_CFG_SE_STOP(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of the connections between SEs
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CONNECT
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_SE_CONNECT(gi)             VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,3)

/**
 * \brief
 * Forms the leak chains.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_CONNECT . SE_LEAK_LINK
 */
#define  VTSS_F_HSCH_SE_CONNECT_SE_LEAK_LINK(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_HSCH_SE_CONNECT_SE_LEAK_LINK     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_HSCH_SE_CONNECT_SE_LEAK_LINK(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/**
 * \brief Configuration of which fill levels in the queue system that the DLB shapers use to trigger excess information rate
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_DLB_SENSE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_SE_DLB_SENSE(gi)           VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,4)

/**
 * \brief
 * QoS class used when SE_DLB_PRIO_ENA is set.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_DLB_SENSE . SE_DLB_PRIO
 */
#define  VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_PRIO     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * Destination port used when SE_DLB_DPORT_ENA is set.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_DLB_SENSE . SE_DLB_DPORT
 */
#define  VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_DPORT     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

/**
 * \brief
 * Let excess rate become active when connected SE is above the
 * QLIMIT_SE_EIR watermark.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_DLB_SENSE . SE_DLB_SE_ENA
 */
#define  VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_SE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_SE_ENA  VTSS_BIT(2)
#define  VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_SE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable priority awareness by the DLB shaper. If set, the DLB shaper
 * allows excess information rate when the egress buffer use for QoS class
 * SE_DLB_PRIO has reached threshold BUF_PRIO_SHR_E[SE_DLB_PRIO] minus 3000
 * bytes.If both SE_DLB_PRIO_ENA and SE_DLB_SPORT_ENA are set, the excess
 * information rate is alllowed when the ingress buffer use for QoS class
 * per source port has reached threshold BUF_Q_RSRV_I[SE_DLB_PRIO,
 * SE_DLB_SPORT] minus 3000 bytes. If both SE_DLB_PRIO_ENA and
 * SE_DLB_DPORT_ENA are set, the excess information rate is alllowed when
 * the egress buffer use for QoS class per destination port has reached
 * threshold BUF_Q_RSRV_E[SE_DLB_PRIO, SE_DLB_DPORT] minus 3000 bytes. If
 * multiple awareness functions (SE_DLB_PRIO_ENA, SE_DLB_SPORT_ENA,
 * SE_DLB_DPORT_ENA) are enabled, all relevant thresholds must be exceeded
 * before excess information rate is allowed.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_DLB_SENSE . SE_DLB_PRIO_ENA
 */
#define  VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA  VTSS_BIT(1)
#define  VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable destination port awareness by the DLB shaper. If set, the DLB
 * shaper allows excess information rate when the egress buffer use for
 * destination port SE_DLB_SPORT has reached threshold
 * BUF_P_RSRV_E[SE_DLB_DPORT] minus 3000 bytes.If multiple awareness
 * functions (SE_DLB_PRIO_ENA, SE_DLB_SPORT_ENA, SE_DLB_DPORT_ENA) are
 * enabled, all relevant thresholds must be exceeded before excess
 * information rate is allowed.
 *
 * \details
 * Field: ::VTSS_HSCH_SE_DLB_SENSE . SE_DLB_DPORT_ENA
 */
#define  VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_CIR_STATE(gi)              VTSS_IOREG_IX(VTSS_TO_HSCH,0x4000,gi,4,0,0)

/**
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details
 * Field: ::VTSS_HSCH_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_HSCH_CIR_STATE_CIR_LVL(x)     VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_CIR_STATE_CIR_LVL        VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_CIR_STATE_CIR_LVL(x)     VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief EIR status
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:EIR_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_EIR_STATE(gi)              VTSS_IOREG_IX(VTSS_TO_HSCH,0x4000,gi,4,0,1)

/**
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details
 * Field: ::VTSS_HSCH_EIR_STATE . EIR_LVL
 */
#define  VTSS_F_HSCH_EIR_STATE_EIR_LVL(x)     VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_EIR_STATE_EIR_LVL        VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_EIR_STATE_EIR_LVL(x)     VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief State of the inputs to this SE
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:SE_STATE
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_SE_STATE(gi)               VTSS_IOREG_IX(VTSS_TO_HSCH,0x4000,gi,4,0,2)

/**
 * \brief
 * The queue selector regards this element as being closed
 *
 * \details
 * Field: ::VTSS_HSCH_SE_STATE . REP_CLOSED
 */
#define  VTSS_F_HSCH_SE_STATE_REP_CLOSED(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_SE_STATE_REP_CLOSED      VTSS_BIT(0)
#define  VTSS_X_HSCH_SE_STATE_REP_CLOSED(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_WID[0] (??), 0-31
 */
#define VTSS_HSCH_QSHP_CIR_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_HSCH,0x2300,gi,2,0,0)

/**
 * \brief
 * Leak rate for this shaper. Unit is defined by the leak list period the
 * shaper is attached to (see HSCH_TIMER_CFG.LEAK_TIME).
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_HSCH_QSHP_CIR_CFG_CIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,17)
#define  VTSS_M_HSCH_QSHP_CIR_CFG_CIR_RATE     VTSS_ENCODE_BITMASK(6,17)
#define  VTSS_X_HSCH_QSHP_CIR_CFG_CIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,17)

/**
 * \brief
 * Burst capacity of this shaper. Unit is 4096 kilobytes. The shaper is
 * disabled when CIR_BURST=0.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_HSCH_QSHP_CIR_CFG_CIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_QSHP_CIR_CFG_CIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_QSHP_CIR_CFG_CIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Configuration of queue shaper
 *
 * \details
 * Register: \a HSCH:QSHP_CFG:QSHP_CFG
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_WID[0] (??), 0-31
 */
#define VTSS_HSCH_QSHP_CFG(gi)               VTSS_IOREG_IX(VTSS_TO_HSCH,0x2300,gi,2,0,1)

/**
 * \brief
 * Accounting mode for this shaper.
 *
 * \details
 * 0: Line rate. Shape bytes including HSCH_MISC_PORT_CFG.FRM_ADJ.
 * 1: Data rate. Shape bytes excluding IPG.
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape framed with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_HSCH_QSHP_CFG . SE_FRM_MODE
 */
#define  VTSS_F_HSCH_QSHP_CFG_SE_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_QSHP_CFG_SE_FRM_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_QSHP_CFG_SE_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_QSHP_ALLOC_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_HSCH,0x3000,gi,2,0,0)

/**
 * \brief
 * First input using queue shapers.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG . QSHP_MIN
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_MIN     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/**
 * \brief
 * Last input using queue shapers. A value lower than the SHP_MIN input
 * disables queue shaping.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG . QSHP_MAX
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_MAX     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 * First input using queue shapers are using this queue shaper index.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_ALLOC_CFG . QSHP_BASE
 */
#define  VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_BASE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_QSHP_ALLOC_CFG_QSHP_BASE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_BASE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief Configuration of the connections between queue shapers
 *
 * \details
 * Register: \a HSCH:QSHP_ALLOC_CFG:QSHP_CONNECT
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_CNT[0] (??), 0-1119
 */
#define VTSS_HSCH_QSHP_CONNECT(gi)           VTSS_IOREG_IX(VTSS_TO_HSCH,0x3000,gi,2,0,1)

/**
 * \brief
 * Forms the leak chains.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_CONNECT . SE_LEAK_LINK
 */
#define  VTSS_F_HSCH_QSHP_CONNECT_SE_LEAK_LINK(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_HSCH_QSHP_CONNECT_SE_LEAK_LINK     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_HSCH_QSHP_CONNECT_SE_LEAK_LINK(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

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
 * @param gi Replicator: x_GAZ_HSCH_SE_WID[0] (??), 0-31
 */
#define VTSS_HSCH_QSHP_CIR_STATE(gi)         VTSS_IOREG_IX(VTSS_TO_HSCH,0x2380,gi,1,0,0)

/**
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details
 * Field: ::VTSS_HSCH_QSHP_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_HSCH_QSHP_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_HSCH_QSHP_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_HSCH_QSHP_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,24)

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
 */
#define VTSS_HSCH_INP_STATE                  VTSS_IOREG(VTSS_TO_HSCH,0x2363)

/**
 * \brief
 * Returns the 32 input states for se cfg_se_idx, from offset
 * 32*replication
 *
 * \details
 * Field: ::VTSS_HSCH_INP_STATE . INP_STATE
 */
#define  VTSS_F_HSCH_INP_STATE_INP_STATE(x)   (x)
#define  VTSS_M_HSCH_INP_STATE_INP_STATE      0xffffffff
#define  VTSS_X_HSCH_INP_STATE_INP_STATE(x)   (x)

/**
 * Register Group: \a HSCH:HSCH_DWRR
 *
 * Configure DWRR weights
 */


/**
 * \brief Configuration and status of a DWRR entry
 *
 * \details
 * Register: \a HSCH:HSCH_DWRR:DWRR_ENTRY
 *
 * @param gi Replicator: x_GAZ_HSCH_SE_WID_MAX (??), 0-31
 */
#define VTSS_HSCH_DWRR_ENTRY(gi)             VTSS_IOREG_IX(VTSS_TO_HSCH,0x23a0,gi,1,0,0)

/**
 * \brief
 * When a specific input to an element is used, the cost is used when
 * updating the balance.
 *
 * \details
 * Field: ::VTSS_HSCH_DWRR_ENTRY . DWRR_COST
 */
#define  VTSS_F_HSCH_DWRR_ENTRY_DWRR_COST(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_HSCH_DWRR_ENTRY_DWRR_COST     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/**
 * \brief
 * Current balance of the input
 *
 * \details
 * Field: ::VTSS_HSCH_DWRR_ENTRY . DWRR_BALANCE
 */
#define  VTSS_F_HSCH_DWRR_ENTRY_DWRR_BALANCE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_HSCH_DWRR_ENTRY_DWRR_BALANCE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_HSCH_DWRR_ENTRY_DWRR_BALANCE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a HSCH:HSCH_MISC
 *
 * Miscellaneous scheduler configuration
 */


/**
 * \brief Misc common config for scheduler
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_MISC_CFG
 */
#define VTSS_HSCH_HSCH_MISC_CFG              VTSS_IOREG(VTSS_TO_HSCH,0x23c0)

/**
 * \brief
 * Set this to one to disabled all leaking from leaky bucket shapers
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_MISC_CFG . LEAK_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_CFG_LEAK_DIS   VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Port specific config for scheduler
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_MISC_PORT_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_HSCH_HSCH_MISC_PORT_CFG(ri)     VTSS_IOREG(VTSS_TO_HSCH,0x23c1 + (ri))

/**
 * \brief
 * Values to add each frame when frame length adjustment is in use.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_CFG . FRM_ADJ
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_CFG_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_CFG_FRM_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_CFG_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Configuration selection register
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_CFG_CFG
 */
#define VTSS_HSCH_HSCH_CFG_CFG               VTSS_IOREG(VTSS_TO_HSCH,0x2407)

/**
 * \brief
 * The DWRR balances and queue shapers will be accessed for the scheduling
 * element indexed by this field.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_CFG_CFG . CFG_SE_IDX
 */
#define  VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(x)  VTSS_ENCODE_BITFIELD(x,14,11)
#define  VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX     VTSS_ENCODE_BITMASK(14,11)
#define  VTSS_X_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,14,11)

/**
 * \brief
 * The HSCH layer set in this field will be accessed by the configuration
 * interfaces.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_CFG_CFG . HSCH_LAYER
 */
#define  VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HSCH_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Skip a hierarchy update every time this number of updates has been done.
 * If zero, the feature is disabled. Setting to 4095 will disable hierachy
 * updates.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_CFG_CFG . CSR_GRANT
 */
#define  VTSS_F_HSCH_HSCH_CFG_CFG_CSR_GRANT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_HSCH_CFG_CFG_CSR_GRANT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_HSCH_CFG_CFG_CSR_GRANT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief Per port PFC configuration
 *
 * \details
 * These configurations exists per front port.
 *
 * Register: \a HSCH:HSCH_MISC:PFC_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-29
 */
#define VTSS_HSCH_PFC_CFG(ri)                VTSS_IOREG(VTSS_TO_HSCH,0x2408 + (ri))

/**
 * \brief
 * Set the layer at which PFC status should be applied for this port. Only
 * layers 1 and 2 supports PFC blocking of the hierarchy.
 *
 * \details
 * 0: Do not block any branches through PFC status
 * 1: Use pfc status for the port on layer 1
 * 2: Use pfc status for the port on layer 2
 * 3: Reserved
 *
 * Field: ::VTSS_HSCH_PFC_CFG . PFC_LAYER
 */
#define  VTSS_F_HSCH_PFC_CFG_PFC_LAYER(x)     VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_HSCH_PFC_CFG_PFC_LAYER        VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_HSCH_PFC_CFG_PFC_LAYER(x)     VTSS_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * Set to the scheduling element number which should be affected by pfc
 * status for this port.
 *
 * \details
 * Field: ::VTSS_HSCH_PFC_CFG . PFC_SE
 */
#define  VTSS_F_HSCH_PFC_CFG_PFC_SE(x)        VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_PFC_CFG_PFC_SE           VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_PFC_CFG_PFC_SE(x)        VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Enable large scheduling elements
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_LARGE_ENA
 *
 * @param ri Replicator: x_GAZ_HSCH_LARGE_CFG_SIZE (??), 0-7
 */
#define VTSS_HSCH_HSCH_LARGE_ENA(ri)         VTSS_IOREG(VTSS_TO_HSCH,0x2449 + (ri))

/**
 * \brief
 * Bit n in replication k enables extended width on scheduling element
 * (32k+n)*4.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_LARGE_ENA . HSCH_LARGE_ENA
 */
#define  VTSS_F_HSCH_HSCH_LARGE_ENA_HSCH_LARGE_ENA(x)  (x)
#define  VTSS_M_HSCH_HSCH_LARGE_ENA_HSCH_LARGE_ENA     0xffffffff
#define  VTSS_X_HSCH_HSCH_LARGE_ENA_HSCH_LARGE_ENA(x)  (x)


/**
 * \brief Core events from the Scheduler
 *
 * \details
 * Core events from the Scheduler.
 *
 * Register: \a HSCH:HSCH_MISC:EVENTS_CORE
 */
#define VTSS_HSCH_EVENTS_CORE                VTSS_IOREG(VTSS_TO_HSCH,0x2451)

/**
 * \brief
 * Reports an event if the scheduler's capacity to process TAS gate
 * operations is exceeded.
 *
 * \details
 * Bit 3: Set to 1 if a gate operation from TAS was lost.
 * Other bits are reserved.
 *
 * Field: ::VTSS_HSCH_EVENTS_CORE . EV_HSCH
 */
#define  VTSS_F_HSCH_EVENTS_CORE_EV_HSCH(x)   VTSS_ENCODE_BITFIELD(x,6,7)
#define  VTSS_M_HSCH_EVENTS_CORE_EV_HSCH      VTSS_ENCODE_BITMASK(6,7)
#define  VTSS_X_HSCH_EVENTS_CORE_EV_HSCH(x)   VTSS_EXTRACT_BITFIELD(x,6,7)

/**
 * \brief
 * Look in the RTL!
 *
 * \details
 * Field: ::VTSS_HSCH_EVENTS_CORE . EV_FRD
 */
#define  VTSS_F_HSCH_EVENTS_CORE_EV_FRD(x)    VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_EVENTS_CORE_EV_FRD       VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_EVENTS_CORE_EV_FRD(x)    VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Internal control for debugging only
 *
 * \details
 * Core events.
 *
 * Register: \a HSCH:HSCH_MISC:DEBUG_CTRL
 */
#define VTSS_HSCH_DEBUG_CTRL                 VTSS_IOREG(VTSS_TO_HSCH,0x2452)

/**
 * \brief
 * Force port to be frame pending. To be used when a port for some unknown
 * reason gets stuck. The port configured in FLUSH_PORT will be marked
 * pending.
 *
 * \details
 * Field: ::VTSS_HSCH_DEBUG_CTRL . PORT_KICK
 */
#define  VTSS_F_HSCH_DEBUG_CTRL_PORT_KICK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_DEBUG_CTRL_PORT_KICK     VTSS_BIT(0)
#define  VTSS_X_HSCH_DEBUG_CTRL_PORT_KICK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Return information about scheduler busyness
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_UPDATE_STAT
 */
#define VTSS_HSCH_HSCH_UPDATE_STAT           VTSS_IOREG(VTSS_TO_HSCH,0x2453)

/**
 * \brief
 * Return the maximum period of constant update need. Clear by writing one
 * to the lsb of the register.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_UPDATE_STAT . HSCH_UPDATE_CNT
 */
#define  VTSS_F_HSCH_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_HSCH_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_HSCH_HSCH_UPDATE_STAT_HSCH_UPDATE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/**
 * \brief Force update of an element in the hierarchy
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_FORCE_CTRL
 */
#define VTSS_HSCH_HSCH_FORCE_CTRL            VTSS_IOREG(VTSS_TO_HSCH,0x2454)

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
 * Field: ::VTSS_HSCH_HSCH_FORCE_CTRL . HFORCE_LAYER
 */
#define  VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_LAYER(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HSCH_HSCH_FORCE_CTRL_HFORCE_LAYER     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HSCH_HSCH_FORCE_CTRL_HFORCE_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * Set to index of element to force
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_FORCE_CTRL . HFORCE_SE_IDX
 */
#define  VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_SE_IDX(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_HSCH_HSCH_FORCE_CTRL_HFORCE_SE_IDX     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_HSCH_HSCH_FORCE_CTRL_HFORCE_SE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/**
 * \brief
 * Update the requested scheduling element
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_FORCE_CTRL . HFORCE_1SHOT
 */
#define  VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_1SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_FORCE_CTRL_HFORCE_1SHOT  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_FORCE_CTRL_HFORCE_1SHOT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:HSCH_LEAK_LISTS
 *
 * Configuration of leak lists
 */


/**
 * \brief Leak configuration per leak group
 *
 * \details
 * Register: \a HSCH:HSCH_LEAK_LISTS:HSCH_TIMER_CFG
 *
 * @param gi Register: HSCH_LEAK_LISTS (??), 0-3
 * @param ri Register: HSCH_TIMER_CFG (??), 0-3
 */
#define VTSS_HSCH_HSCH_TIMER_CFG(gi,ri)      VTSS_IOREG_IX(VTSS_TO_HSCH,0x2455,gi,8,ri,0)

/**
 * \brief
 * Number of nanoseconds between each traversal of the leak list. A value
 * of 10000 correspond to 10us. Each traversal subtracts the configured
 * rate from the shaper buckets, counting bits. With the value of 10000, a
 * rate of 1 corresponds to 1 bit per 10us, or 100kbps.A leak group can be
 * set up for 16kbps unit by seting the leak_time to 1 bit per 62500
 * nanoseconds.
 *
 * \details
 * 0: Leaking disabled
 * 62500: 16kbps unit
 * 10000: 100kbps unit
 * 1000:  1Mbps unit
 * (any other)
 *
 * Field: ::VTSS_HSCH_HSCH_TIMER_CFG . LEAK_TIME
 */
#define  VTSS_F_HSCH_HSCH_TIMER_CFG_LEAK_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,18)
#define  VTSS_M_HSCH_HSCH_TIMER_CFG_LEAK_TIME     VTSS_ENCODE_BITMASK(0,18)
#define  VTSS_X_HSCH_HSCH_TIMER_CFG_LEAK_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,18)


/**
 * \brief Leak configuration per leak group
 *
 * \details
 * Register: \a HSCH:HSCH_LEAK_LISTS:HSCH_LEAK_CFG
 *
 * @param gi Register: HSCH_LEAK_LISTS (??), 0-3
 * @param ri Register: HSCH_LEAK_CFG (??), 0-3
 */
#define VTSS_HSCH_HSCH_LEAK_CFG(gi,ri)       VTSS_IOREG_IX(VTSS_TO_HSCH,0x2455,gi,8,ri,4)

/**
 * \brief
 * First shaper in the leak group
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_LEAK_CFG . LEAK_FIRST
 */
#define  VTSS_F_HSCH_HSCH_LEAK_CFG_LEAK_FIRST(x)  VTSS_ENCODE_BITFIELD(x,1,14)
#define  VTSS_M_HSCH_HSCH_LEAK_CFG_LEAK_FIRST     VTSS_ENCODE_BITMASK(1,14)
#define  VTSS_X_HSCH_HSCH_LEAK_CFG_LEAK_FIRST(x)  VTSS_EXTRACT_BITFIELD(x,1,14)

/**
 * \brief
 * The leak group didnt succeed traversing all shapers. Rates will be
 * wrong.
 *
 * \details
 * Field: ::VTSS_HSCH_HSCH_LEAK_CFG . LEAK_ERR
 */
#define  VTSS_F_HSCH_HSCH_LEAK_CFG_LEAK_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_LEAK_CFG_LEAK_ERR   VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_LEAK_CFG_LEAK_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:SYSTEM
 *
 * Egress configuration
 */


/**
 * \brief Egress queue status
 *
 * \details
 * Register: \a HSCH:SYSTEM:EQ_STAT
 */
#define VTSS_HSCH_EQ_STAT                    VTSS_IOREG(VTSS_TO_HSCH,0x2475)

/**
 * \brief
 * Number of free frame references.
 *
 * \details
 * Field: ::VTSS_HSCH_EQ_STAT . FP_FREE_CNT
 */
#define  VTSS_F_HSCH_EQ_STAT_FP_FREE_CNT(x)   VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSCH_EQ_STAT_FP_FREE_CNT      VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSCH_EQ_STAT_FP_FREE_CNT(x)   VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Enable flushing of selected framesy
 *
 * \details
 * Register: \a HSCH:SYSTEM:FLUSH_CTRL
 */
#define VTSS_HSCH_FLUSH_CTRL                 VTSS_IOREG(VTSS_TO_HSCH,0x2476)

/**
 * \brief
 * Set to enable flushing of all frames matching the flush criteria in this
 * register
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_ENA
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_ENA     VTSS_BIT(27)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Frame received on the configured port will be flushed if set.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_SRC
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_SRC(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_SRC     VTSS_BIT(26)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Frame transmitted on the configured port will be flushed if set.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_DST
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_DST(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_DST     VTSS_BIT(25)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_DST(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Flushing will only affect frames on this port.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_PORT
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_PORT     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/**
 * \brief
 * Frames transmitted from the configured queue specified in FLUSH_HIER
 * will be flushed.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_QUEUE
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_QUEUE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_QUEUE   VTSS_BIT(17)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_QUEUE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Frames transmitted from the configured SE index specified in FLUSH_HIER
 * will be flushed.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_SE
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_SE(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_SE      VTSS_BIT(16)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_SE(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Flushing will only affect frames from this queue or SE.
 *
 * \details
 * Field: ::VTSS_HSCH_FLUSH_CTRL . FLUSH_HIER
 */
#define  VTSS_F_HSCH_FLUSH_CTRL_FLUSH_HIER(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_HSCH_FLUSH_CTRL_FLUSH_HIER     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_HSCH_FLUSH_CTRL_FLUSH_HIER(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/**
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per switch port.
 *
 * Register: \a HSCH:SYSTEM:PORT_MODE
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_HSCH_PORT_MODE(ri)              VTSS_IOREG(VTSS_TO_HSCH,0x2477 + (ri))

/**
 * \brief
 * Disable dequeuing from the egress queues. Frames are not discarded, but
 * may become aged when dequeuing is re-enabled.
 *
 * \details
 * Field: ::VTSS_HSCH_PORT_MODE . DEQUEUE_DIS
 */
#define  VTSS_F_HSCH_PORT_MODE_DEQUEUE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSCH_PORT_MODE_DEQUEUE_DIS    VTSS_BIT(4)
#define  VTSS_X_HSCH_PORT_MODE_DEQUEUE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Disable aging of all frames transmitted to the port.Frame aging related
 * parameters:QSYS:SYSTEM:FRM_AGING.MAX_AGEHSCH:SYSTEM:PORT_MODE.AGE_DISDSM
 * :CFG:BUF_CFG.AGING_ENA
 *
 * \details
 * Field: ::VTSS_HSCH_PORT_MODE . AGE_DIS
 */
#define  VTSS_F_HSCH_PORT_MODE_AGE_DIS(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSCH_PORT_MODE_AGE_DIS        VTSS_BIT(3)
#define  VTSS_X_HSCH_PORT_MODE_AGE_DIS(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable truncation of stack learnall frames.
 *
 * \details
 * Field: ::VTSS_HSCH_PORT_MODE . TRUNC_ENA
 */
#define  VTSS_F_HSCH_PORT_MODE_TRUNC_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSCH_PORT_MODE_TRUNC_ENA      VTSS_BIT(2)
#define  VTSS_X_HSCH_PORT_MODE_TRUNC_ENA(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Increase DP by one in case scheduled frame passed due to excess rate
 * shaper.
 *
 * \details
 * Field: ::VTSS_HSCH_PORT_MODE . EIR_REMARK_ENA
 */
#define  VTSS_F_HSCH_PORT_MODE_EIR_REMARK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_PORT_MODE_EIR_REMARK_ENA  VTSS_BIT(1)
#define  VTSS_X_HSCH_PORT_MODE_EIR_REMARK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
 * Field: ::VTSS_HSCH_PORT_MODE . CPU_PRIO_MODE
 */
#define  VTSS_F_HSCH_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_PORT_MODE_CPU_PRIO_MODE  VTSS_BIT(0)
#define  VTSS_X_HSCH_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Cellbus configuration
 *
 * \details
 * Register: \a HSCH:SYSTEM:OUTB_SHARE_ENA
 *
 * @param ri Replicator: x_GAZ_CORE_INTPORT_CNT (??), 0-4
 */
#define VTSS_HSCH_OUTB_SHARE_ENA(ri)         VTSS_IOREG(VTSS_TO_HSCH,0x24bd + (ri))

/**
 * \brief
 * Sets the minimum distance between grants to an internal port. Extra
 * grants are disabled when configured value is 0, otherwise the port seeks
 * extra bandwidth, and the minimum distance in clock cycles is given by
 * this value. The replications are for internal CPU 0, internal CPU 1,
 * VDs.The minimum value accepted is 12. The internal ports will need a
 * delay of 12 at the switch to a new frame, which will reduce the total
 * bandwidth a bit for some frame sizes.The bandwidth with a grant value of
 * N with a core frequency of f MHz will grant 0.67f/N Gbps for smallest
 * frames.
 * Ex: A value of 12 grants: 23Gbps at 416 MHz,  28Gbps at 500 MHz, 35Gbps
 * at 625 MHz.
 *
 * \details
 * Field: ::VTSS_HSCH_OUTB_SHARE_ENA . OUTB_SHARE_ENA
 */
#define  VTSS_F_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_OUTB_SHARE_ENA_OUTB_SHARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Cellbus configuration
 *
 * \details
 * Register: \a HSCH:SYSTEM:OUTB_CPU_SHARE_ENA
 */
#define VTSS_HSCH_OUTB_CPU_SHARE_ENA         VTSS_IOREG(VTSS_TO_HSCH,0x24c2)

/**
 * \brief
 * When enabled, unused bandwidth sharing will be granted to the an
 * internal CPUport, only when the calendar designated port is another
 * internal CPU port. The OUTB_SHARE_ENA must be configured for the CPU
 * ports when this is enabled
 *
 * \details
 * Field: ::VTSS_HSCH_OUTB_CPU_SHARE_ENA . OUTB_CPU_SHARE_ENA
 */
#define  VTSS_F_HSCH_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_OUTB_CPU_SHARE_ENA_OUTB_CPU_SHARE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:MMGT
 *
 * Memory manager status
 */


/**
 * \brief Packet memory status
 *
 * \details
 * Register: \a HSCH:MMGT:MMGT
 */
#define VTSS_HSCH_MMGT                       VTSS_IOREG(VTSS_TO_HSCH,0x2369)

/**
 * \brief
 * Number of 6 frames awaiting releasing.
 *
 * \details
 * Field: ::VTSS_HSCH_MMGT . RELCNT
 */
#define  VTSS_F_HSCH_MMGT_RELCNT(x)           VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HSCH_MMGT_RELCNT              VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HSCH_MMGT_RELCNT(x)           VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Number of 6 free memory words.
 *
 * \details
 * Field: ::VTSS_HSCH_MMGT . FREECNT
 */
#define  VTSS_F_HSCH_MMGT_FREECNT(x)          VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSCH_MMGT_FREECNT             VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSCH_MMGT_FREECNT(x)          VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Packet Memory Status
 *
 * \details
 * Register: \a HSCH:MMGT:MMGT_FAST
 */
#define VTSS_HSCH_MMGT_FAST                  VTSS_IOREG(VTSS_TO_HSCH,0x236a)

/**
 * \brief
 * Number of words in the fast pool
 *
 * \details
 * Field: ::VTSS_HSCH_MMGT_FAST . FREEVLD
 */
#define  VTSS_F_HSCH_MMGT_FAST_FREEVLD(x)     VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSCH_MMGT_FAST_FREEVLD        VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSCH_MMGT_FAST_FREEVLD(x)     VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * Number of frames awaiting release in the fast pool
 *
 * \details
 * Field: ::VTSS_HSCH_MMGT_FAST . RELVLD
 */
#define  VTSS_F_HSCH_MMGT_FAST_RELVLD(x)      VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSCH_MMGT_FAST_RELVLD         VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSCH_MMGT_FAST_RELVLD(x)      VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Initialize memories
 * - Enable core
 *
 * Register: \a HSCH:MMGT:RESET_CFG
 */
#define VTSS_HSCH_RESET_CFG                  VTSS_IOREG(VTSS_TO_HSCH,0x236b)

/**
 * \brief
 * Switch core is enabled when this field is set.
 *
 * \details
 * Field: ::VTSS_HSCH_RESET_CFG . CORE_ENA
 */
#define  VTSS_F_HSCH_RESET_CFG_CORE_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_RESET_CFG_CORE_ENA       VTSS_BIT(0)
#define  VTSS_X_HSCH_RESET_CFG_CORE_ENA(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Packet memory status
 *
 * \details
 * Register: \a HSCH:MMGT:PMEM_SIZE
 */
#define VTSS_HSCH_PMEM_SIZE                  VTSS_IOREG(VTSS_TO_HSCH,0x236c)

/**
 * \brief
 * Must be set before core reset is released. Unit is 1104 bytes.
 *
 * \details
 * Field: ::VTSS_HSCH_PMEM_SIZE . PMEM_SIZE
 */
#define  VTSS_F_HSCH_PMEM_SIZE_PMEM_SIZE(x)   VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_HSCH_PMEM_SIZE_PMEM_SIZE      VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_HSCH_PMEM_SIZE_PMEM_SIZE(x)   VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a HSCH:TAS_CONFIG
 *
 * Time Aware Shaper configuration registers for schedule traffic.
 */


/**
 * \brief TAS parameters installer configuration register.
 *
 * \details
 * Register: \a HSCH:TAS_CONFIG:TAS_CFG_CTRL
 */
#define VTSS_HSCH_TAS_CFG_CTRL               VTSS_IOREG(VTSS_TO_HSCH,0x24c3)

/**
 * \brief
 * All lists less than this number will be traversed by the TAS state
 * machine. Other lists will not be processed.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_CFG_CTRL . LIST_NUM_MAX
 */
#define  VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM_MAX(x)  VTSS_ENCODE_BITFIELD(x,22,6)
#define  VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM_MAX     VTSS_ENCODE_BITMASK(22,6)
#define  VTSS_X_HSCH_TAS_CFG_CTRL_LIST_NUM_MAX(x)  VTSS_EXTRACT_BITFIELD(x,22,6)

/**
 * \brief
 * Specifies the list index which the TAS_LIST_CFG register group
 * access.Note: This value needs to be set first before configuring any of
 * above mentioned registers.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_CFG_CTRL . LIST_NUM
 */
#define  VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(x)  VTSS_ENCODE_BITFIELD(x,15,6)
#define  VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM     VTSS_ENCODE_BITMASK(15,6)
#define  VTSS_X_HSCH_TAS_CFG_CTRL_LIST_NUM(x)  VTSS_EXTRACT_BITFIELD(x,15,6)

/**
 * \brief
 * Global configuration, when set a guard band is implemented even for
 * schedule queues to scheduled queue transition.
 *
 * \details
 * 0: Guard band is implemented for non-schedule queues to schedule queues
 * transition.
 * 1: Guard band is implemented for any queue to schedule queue transition.
 *
 * Field: ::VTSS_HSCH_TAS_CFG_CTRL . ALWAYS_GUARD_BAND_SCH_Q
 */
#define  VTSS_F_HSCH_TAS_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSCH_TAS_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q  VTSS_BIT(14)
#define  VTSS_X_HSCH_TAS_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Specifies address of the gate control entry in the gate control
 * list.Note: This value needs to be set first before reading the
 * TAS_GCL_CFG register
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_CFG_CTRL . GCL_ENTRY_NUM
 */
#define  VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief TAS gate state address for TAS_GATE_STATE register.
 *
 * \details
 * Register must be set to the HSCH position to access the gates for, prior
 * reading or writing the HSCH_TAS_GATE_STATE register
 *
 * Register: \a HSCH:TAS_CONFIG:TAS_GATE_STATE_CTRL
 */
#define VTSS_HSCH_TAS_GATE_STATE_CTRL        VTSS_IOREG(VTSS_TO_HSCH,0x24c4)

/**
 * \brief
 * Set to the scheduling hierarchy location which this list should access.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_GATE_STATE_CTRL . HSCH_POS
 */
#define  VTSS_F_HSCH_TAS_GATE_STATE_CTRL_HSCH_POS(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_HSCH_TAS_GATE_STATE_CTRL_HSCH_POS     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_HSCH_TAS_GATE_STATE_CTRL_HSCH_POS(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief TAS parameters installer configuration register.
 *
 * \details
 * Register: \a HSCH:TAS_CONFIG:TAS_CFG_CTRL2
 */
#define VTSS_HSCH_TAS_CFG_CTRL2              VTSS_IOREG(VTSS_TO_HSCH,0x24c5)

/**
 * \brief
 * If guardbanding is activated as a result of TAS operation, values less
 * than this configuration will use MINIMUM_GB_VAL setting instead. This is
 * for taking internal transmit fifo data into account. Default value
 * corresponds to 320 bytes of data pending in transmit fifos.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_CFG_CTRL2 . MINIMUM_GB_VAL
 */
#define  VTSS_F_HSCH_TAS_CFG_CTRL2_MINIMUM_GB_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HSCH_TAS_CFG_CTRL2_MINIMUM_GB_VAL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HSCH_TAS_CFG_CTRL2_MINIMUM_GB_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Configure the state machine
 *
 * \details
 * Use to reduce the amount of list processings without any activity
 *
 * Register: \a HSCH:TAS_CONFIG:TAS_STATEMACHINE_CFG
 */
#define VTSS_HSCH_TAS_STATEMACHINE_CFG       VTSS_IOREG(VTSS_TO_HSCH,0x24c6)

/**
 * \brief
 * When a list is found to have the next gate event in X nanosecs, the list
 * will not be revisited before X * this / 256 state machine clock cycles
 * has elapsed.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_STATEMACHINE_CFG . REVISIT_DLY
 */
#define  VTSS_F_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_HSCH_TAS_STATEMACHINE_CFG_REVISIT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/**
 * \brief
 * The predicted run rate of the egress pipe will be adjusted by 1/value.
 * Even values increases bandwidth a bit with potential overshooting a tas
 * window. Odd values reduces bandwidth a bit with potential loss of
 * throughput.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_STATEMACHINE_CFG . TAS_CBSHP_ADJ
 */
#define  VTSS_F_HSCH_TAS_STATEMACHINE_CFG_TAS_CBSHP_ADJ(x)  VTSS_ENCODE_BITFIELD(x,10,12)
#define  VTSS_M_HSCH_TAS_STATEMACHINE_CFG_TAS_CBSHP_ADJ     VTSS_ENCODE_BITMASK(10,12)
#define  VTSS_X_HSCH_TAS_STATEMACHINE_CFG_TAS_CBSHP_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,10,12)

/**
 * \brief
 * Tas actions will taken place this amount of nsec in advance to better
 * hit timing on the physical interfaces
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_STATEMACHINE_CFG . TAS_PIPE_DLY_NS
 */
#define  VTSS_F_HSCH_TAS_STATEMACHINE_CFG_TAS_PIPE_DLY_NS(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_HSCH_TAS_STATEMACHINE_CFG_TAS_PIPE_DLY_NS     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_HSCH_TAS_STATEMACHINE_CFG_TAS_PIPE_DLY_NS(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a HSCH:TAS_PROFILE_CFG
 *
 * TAS Port configuration
 */


/**
 * \brief Time aware gate configuration register
 *
 * \details
 * Register: \a HSCH:TAS_PROFILE_CFG:TAS_PROFILE_CONFIG
 *
 * @param gi Replicator: x_GAZ_CORE_TAS_PORT_CNT (??), 0-29
 */
#define VTSS_HSCH_TAS_PROFILE_CONFIG(gi)     VTSS_IOREG_IX(VTSS_TO_HSCH,0x24c7,gi,17,0,0)

/**
 * \brief
 * Specifies the link speed for the port. This is used to evaluate the time
 * taken by a frame on the line.
 *
 * \details
 * The encoding of the bits is as follows:
 * 000: No guard banding
 * 001: 10 Mbps
 * 010: 100 Mbps.
 * 011: 1 Gbps.
 * 100: 2.5 Gbps.
 * 101: 5 Gbps.
 * 110: 10 Gbps.
 * 111: Reserved
 *
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . LINK_SPEED
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/**
 * \brief
 * A 8-bit vector that determines port queues which will allow scheduled
 * traffic among the 8 queues. If a bit is set then the corresponding queue
 * allows scheduled traffic.
 *
 * \details
 * For ith bit or bit[i] (corresponds to ith queue):
 * 1: the queue serves schedule traffic provided TAS is enabled for the
 * port.
 * 0: the queue does not serve scheduled traffic.

 *
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . SCH_TRAFFIC_QUEUES
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(x)  VTSS_ENCODE_BITFIELD(x,15,8)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES     VTSS_ENCODE_BITMASK(15,8)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(x)  VTSS_EXTRACT_BITFIELD(x,15,8)

/**
 * \brief
 * Sets the guard-band for the Set-And-Hold-MAC gate operation. The unit is
 * 64 bytes times the value of link_speed. A Set-And-Hold-MAC operation
 * takes effect this much time in advance of the nominal gate operation
 * time to leave time for the transmission of preemptible frames to
 * complete inside the MAC.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . HOLDADVANCE
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_HOLDADVANCE(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/**
 * \brief
 * A TAS gate will open a delay prior to the configured gate control
 * time.The delay is the sum of TAS_PIPE_DLY_NS and TAS_PORT_DLY. Unit is
 * 64 byte times on the port.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . TAS_PORT_DLY
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_TAS_PORT_DLY(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_TAS_PORT_DLY     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_TAS_PORT_DLY(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * A TAS gate will close a delay prior to the configured gate control
 * time.The delay is the sum of TAS_PIPE_DLY_NS, TAS_PORT_DLY,
 * TAS_CLOSE_DLY and the QMAXSDU based guard banding configured. Unit is 64
 * byte times on the port.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . TAS_CLOSE_DLY
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_TAS_CLOSE_DLY(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_TAS_CLOSE_DLY     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_TAS_CLOSE_DLY(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/**
 * \brief
 * Enable shaping of egress cell bus to accomplish better TAS window
 * accuracy.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_PROFILE_CONFIG . TAS_CBSHP_ENA
 */
#define  VTSS_F_HSCH_TAS_PROFILE_CONFIG_TAS_CBSHP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_TAS_PROFILE_CONFIG_TAS_CBSHP_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_TAS_PROFILE_CONFIG_TAS_CBSHP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief MAX SDU for traffic classes
 *
 * \details
 * Register: \a HSCH:TAS_PROFILE_CFG:TAS_QMAXSDU_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_TAS_PORT_CNT (??), 0-29
 * @param ri Register: TAS_QMAXSDU_CFG (??), 0-7
 */
#define VTSS_HSCH_TAS_QMAXSDU_CFG(gi,ri)     VTSS_IOREG_IX(VTSS_TO_HSCH,0x24c7,gi,17,ri,1)

/**
 * \brief
 * Specifies maximum allowed SDU for the traffic class N, when transmitted
 * on port P. P is the register group replication index, and N is the
 * register index.Value used for guard banding. It is together with
 * link_speed determining the time prior to a gate closing where the
 * scheduler stops selecting the class. The unit is 64 bytes times the
 * value of link_speedThe time specified with qmaxsdu_val and link_speed
 * should be smaller than the smallest value of time_interval in use for
 * this port. A queue will always be opened for a small amount of time,
 * even if the specified guard-banding is larger than qmaxsdu_val.
 * This setting can also be used for enqueue discards if QMAXSDU_DISC_ENA
 * is set
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_QMAXSDU_CFG . QMAXSDU_VAL
 */
#define  VTSS_F_HSCH_TAS_QMAXSDU_CFG_QMAXSDU_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_TAS_QMAXSDU_CFG_QMAXSDU_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_TAS_QMAXSDU_CFG_QMAXSDU_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief MAX SDU discard for traffic classes
 *
 * \details
 * Register: \a HSCH:TAS_PROFILE_CFG:QMAXSDU_DISC_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_TAS_PORT_CNT (??), 0-29
 * @param ri Register: QMAXSDU_DISC_CFG (??), 0-7
 */
#define VTSS_HSCH_QMAXSDU_DISC_CFG(gi,ri)    VTSS_IOREG_IX(VTSS_TO_HSCH,0x24c7,gi,17,ri,9)

/**
 * \brief
 * Specifies the 6 LSBs of the allowed maximum frame size for the traffic
 * class N, when transmitted on port P. Size is compared against the
 * ingress frame size, as discards are taking place before the egress path.
 * Discards are only taking place if enabled by the QMAXSDU_DISC_ENA
 * setting
 *
 * \details
 * Field: ::VTSS_HSCH_QMAXSDU_DISC_CFG . QMAXSDU_LSB
 */
#define  VTSS_F_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_LSB     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Enables discards of traffic per class using the QMAXSDU_VAL and
 * QMAXSDU_LSB values.
 *
 * \details
 * Field: ::VTSS_HSCH_QMAXSDU_DISC_CFG . QMAXSDU_DISC_ENA
 */
#define  VTSS_F_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_DISC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_DISC_ENA  VTSS_BIT(8)
#define  VTSS_X_HSCH_QMAXSDU_DISC_CFG_QMAXSDU_DISC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * Register Group: \a HSCH:TAS_LIST_CFG
 *
 * Time Aware Shapper Oper/Admin parameter/status registers.
 */


/**
 * \brief Base time for select GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_BASE_TIME_NSEC
 */
#define VTSS_HSCH_TAS_BASE_TIME_NSEC         VTSS_IOREG(VTSS_TO_HSCH,0x2370)

/**
 * \brief
 * 30 bit nanosecond part of the AdminBaseTime, as long as the list is in
 * ADMIN state. Register will automatically be updated to ConfigChangeTime
 * when he state is switched to ADVANCE. See the TAS_LIST_STATE register
 * for details.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_BASE_TIME_NSEC . BASE_TIME_NSEC
 */
#define  VTSS_F_HSCH_TAS_BASE_TIME_NSEC_BASE_TIME_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_HSCH_TAS_BASE_TIME_NSEC_BASE_TIME_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_HSCH_TAS_BASE_TIME_NSEC_BASE_TIME_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Base time for selected GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_BASE_TIME_SEC_LSB
 */
#define VTSS_HSCH_TAS_BASE_TIME_SEC_LSB      VTSS_IOREG(VTSS_TO_HSCH,0x2371)

/**
 * \brief
 * Least significant 32 bits of seconds part of base time.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_BASE_TIME_SEC_LSB . BASE_TIME_SEC_LSB
 */
#define  VTSS_F_HSCH_TAS_BASE_TIME_SEC_LSB_BASE_TIME_SEC_LSB(x)  (x)
#define  VTSS_M_HSCH_TAS_BASE_TIME_SEC_LSB_BASE_TIME_SEC_LSB     0xffffffff
#define  VTSS_X_HSCH_TAS_BASE_TIME_SEC_LSB_BASE_TIME_SEC_LSB(x)  (x)


/**
 * \brief Base time for selected GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_BASE_TIME_SEC_MSB
 */
#define VTSS_HSCH_TAS_BASE_TIME_SEC_MSB      VTSS_IOREG(VTSS_TO_HSCH,0x2372)

/**
 * \brief
 * Most significant 16 bits of seconds part of base time.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_BASE_TIME_SEC_MSB . BASE_TIME_SEC_MSB
 */
#define  VTSS_F_HSCH_TAS_BASE_TIME_SEC_MSB_BASE_TIME_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSCH_TAS_BASE_TIME_SEC_MSB_BASE_TIME_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSCH_TAS_BASE_TIME_SEC_MSB_BASE_TIME_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Next Gate Operation time for select GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_NEXT_OPER_TIME_NSEC
 */
#define VTSS_HSCH_TAS_NEXT_OPER_TIME_NSEC    VTSS_IOREG(VTSS_TO_HSCH,0x2373)

/**
 * \brief
 * 30 bit nanosecond part of next gate operation time.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_NEXT_OPER_TIME_NSEC . NEXT_OPER_TIME_NSEC
 */
#define  VTSS_F_HSCH_TAS_NEXT_OPER_TIME_NSEC_NEXT_OPER_TIME_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_HSCH_TAS_NEXT_OPER_TIME_NSEC_NEXT_OPER_TIME_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_HSCH_TAS_NEXT_OPER_TIME_NSEC_NEXT_OPER_TIME_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Next Gate Operation time for selected GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_NEXT_OPER_TIME_SEC_LSB
 */
#define VTSS_HSCH_TAS_NEXT_OPER_TIME_SEC_LSB  VTSS_IOREG(VTSS_TO_HSCH,0x2374)

/**
 * \brief
 * Least significant 32 bits of seconds part of next gate operation time.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_NEXT_OPER_TIME_SEC_LSB . NEXT_OPER_TIME_SEC_LSB
 */
#define  VTSS_F_HSCH_TAS_NEXT_OPER_TIME_SEC_LSB_NEXT_OPER_TIME_SEC_LSB(x)  (x)
#define  VTSS_M_HSCH_TAS_NEXT_OPER_TIME_SEC_LSB_NEXT_OPER_TIME_SEC_LSB     0xffffffff
#define  VTSS_X_HSCH_TAS_NEXT_OPER_TIME_SEC_LSB_NEXT_OPER_TIME_SEC_LSB(x)  (x)


/**
 * \brief Next Gate Operation time for selected GCL
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_NEXT_OPER_TIME_SEC_MSB
 */
#define VTSS_HSCH_TAS_NEXT_OPER_TIME_SEC_MSB  VTSS_IOREG(VTSS_TO_HSCH,0x2375)

/**
 * \brief
 * Most significant 16 bits of seconds part of next gate operation time.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_NEXT_OPER_TIME_SEC_MSB . NEXT_OPER_TIME_SEC_MSB
 */
#define  VTSS_F_HSCH_TAS_NEXT_OPER_TIME_SEC_MSB_NEXT_OPER_TIME_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSCH_TAS_NEXT_OPER_TIME_SEC_MSB_NEXT_OPER_TIME_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSCH_TAS_NEXT_OPER_TIME_SEC_MSB_NEXT_OPER_TIME_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief TAS Oper parameter/status Register - 4
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_CYCLE_TIME_CFG
 */
#define VTSS_HSCH_TAS_CYCLE_TIME_CFG         VTSS_IOREG(VTSS_TO_HSCH,0x2376)

/**
 * \brief
 * Register specifies duration of a control cycle in nanoseconds.A 32 bit
 * nano seconds value derived from 'OperCycleTime' (IEEE 802.1Qbv). The
 * specified value must be less than 1 second.Note: Actual value of
 * 'OperCycleTime' is in seconds (a rational number, expressed as numerator
 * and denominator).
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_CYCLE_TIME_CFG . CYCLE_TIME
 */
#define  VTSS_F_HSCH_TAS_CYCLE_TIME_CFG_CYCLE_TIME(x)  (x)
#define  VTSS_M_HSCH_TAS_CYCLE_TIME_CFG_CYCLE_TIME     0xffffffff
#define  VTSS_X_HSCH_TAS_CYCLE_TIME_CFG_CYCLE_TIME(x)  (x)


/**
 * \brief TAS List Replacement configuration
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_STARTUP_CFG
 */
#define VTSS_HSCH_TAS_STARTUP_CFG            VTSS_IOREG(VTSS_TO_HSCH,0x2377)

/**
 * \brief
 * Register configures the time prior to starting this list, where another
 * running list is asked to enter the TERMINATING state. If this list
 * starts, without the termination completed, the STARTUP_ERROR indication
 * is set.The startup time must not be 0, otherwise the list will be unable
 * to start.
 *
 * \details
 * xx: Obsoleting the other list xx*256 ns in advance
 *
 * Field: ::VTSS_HSCH_TAS_STARTUP_CFG . STARTUP_TIME
 */
#define  VTSS_F_HSCH_TAS_STARTUP_CFG_STARTUP_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_HSCH_TAS_STARTUP_CFG_STARTUP_TIME     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_HSCH_TAS_STARTUP_CFG_STARTUP_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,22)

/**
 * \brief
 * Set to the index of another list before switching away from ADMIN state,
 * in case this list should obsolete another one.Set to list index itself
 * to skip obsoleting another other list.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_STARTUP_CFG . OBSOLETE_IDX
 */
#define  VTSS_F_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/**
 * \brief
 * This flag is being set, if a list to be replaced was operating, when
 * this list commenced.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_STARTUP_CFG . STARTUP_ERROR
 */
#define  VTSS_F_HSCH_TAS_STARTUP_CFG_STARTUP_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HSCH_TAS_STARTUP_CFG_STARTUP_ERROR  VTSS_BIT(22)
#define  VTSS_X_HSCH_TAS_STARTUP_CFG_STARTUP_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)


/**
 * \brief TAS Oper parameter/status Register - 10
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_LIST_CFG
 */
#define VTSS_HSCH_TAS_LIST_CFG               VTSS_IOREG(VTSS_TO_HSCH,0x2378)

/**
 * \brief
 * Scheduling hierarchy location this list should operate on
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_CFG . LIST_HSCH_POS
 */
#define  VTSS_F_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(x)  VTSS_ENCODE_BITFIELD(x,19,11)
#define  VTSS_M_HSCH_TAS_LIST_CFG_LIST_HSCH_POS     VTSS_ENCODE_BITMASK(19,11)
#define  VTSS_X_HSCH_TAS_LIST_CFG_LIST_HSCH_POS(x)  VTSS_EXTRACT_BITFIELD(x,19,11)

/**
 * \brief
 * Physical port number this tas list operates on
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_CFG . LIST_PORT_NUM
 */
#define  VTSS_F_HSCH_TAS_LIST_CFG_LIST_PORT_NUM(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_HSCH_TAS_LIST_CFG_LIST_PORT_NUM     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_HSCH_TAS_LIST_CFG_LIST_PORT_NUM(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/**
 * \brief
 * Set the base address in the 3000 entries long control pool for the
 * selected list.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_CFG . LIST_BASE_ADDR
 */
#define  VTSS_F_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Time of day domain the list is synchronized to
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_CFG . LIST_TOD_DOM
 */
#define  VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HSCH_TAS_LIST_CFG_LIST_TOD_DOM     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(x)  VTSS_EXTRACT_BITFIELD(x,12,2)


/**
 * \brief TAS running state
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_LIST_STATE
 */
#define VTSS_HSCH_TAS_LIST_STATE             VTSS_IOREG(VTSS_TO_HSCH,0x2379)

/**
 * \brief
 * Current state of the list.ADMIN: List is in administrative state, and is
 * not traversed by the logic. All registers can be modified by
 * software.ADVANCING: List is calculating the ConfigChangeTime for the
 * list, and is replacing the AdminBaseTime with that. State is reached by
 * writing ADVANCING to this field through software access, and the list
 * will afterwards transition to the PENDING state when ConfigChangeTime
 * calculation is complete.PENDING: List is awaiting the time to start, as
 * found by the ADVANCING state. Some time before (see TAS_STARTUP_CFG),
 * another list may be asked to enter the TERMINATING state. When the
 * ConfigChangeTime is reached, the state is switched to
 * OPERATING.OPERATING: List is being executed until state is switched to
 * TERMINATING by another lists action from a PENDING state, or through
 * direct change by software. A switch from software must be checked by a
 * read of the state afterwards, and potentially rewritten.TERMINATING:
 * List is completing current cycle and switches to ADMIN
 * afterwards.Normally, no field under TAS_LIST_CFG should be modified by
 * software except when a list is in the ADMIN state. As an exception, an
 * active list can be stopped by writing TERMINATING to LIST_STATE, and
 * waiting for the list to move to ADMIN. As the fields under TAS_LIST_CFG
 * are regularly updated by the hardware, there is a race where the change
 * to TERMINATING state can be overridden by an actively processing list.
 * So after writing TERMINATING to LIST_STATE, software must read back the
 * current value, and repeat until the read value is either TERMINATING or
 * IDLE.
 *
 * \details
 * 000: ADMIN
 * 001: ADVANCING
 * 010: PENDING
 * 011: OPERATING
 * 100: TERMINATING

 *
 * Field: ::VTSS_HSCH_TAS_LIST_STATE . LIST_STATE
 */
#define  VTSS_F_HSCH_TAS_LIST_STATE_LIST_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HSCH_TAS_LIST_STATE_LIST_STATE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief TAS running pointer state
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_LIST_PTR_STATE
 */
#define VTSS_HSCH_TAS_LIST_PTR_STATE         VTSS_IOREG(VTSS_TO_HSCH,0x237a)

/**
 * \brief
 * Next entry to process by the list execution.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_PTR_STATE . CUR_PTR
 */
#define  VTSS_F_HSCH_TAS_LIST_PTR_STATE_CUR_PTR(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_TAS_LIST_PTR_STATE_CUR_PTR     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_TAS_LIST_PTR_STATE_CUR_PTR(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief TAS running state
 *
 * \details
 * Register: \a HSCH:TAS_LIST_CFG:TAS_LIST_STATE_INT
 */
#define VTSS_HSCH_TAS_LIST_STATE_INT         VTSS_IOREG(VTSS_TO_HSCH,0x237b)

/**
 * \brief
 * Amount of time left in current cycle.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_LIST_STATE_INT . CYC_TIME_REMAIN
 */
#define  VTSS_F_HSCH_TAS_LIST_STATE_INT_CYC_TIME_REMAIN(x)  (x)
#define  VTSS_M_HSCH_TAS_LIST_STATE_INT_CYC_TIME_REMAIN     0xffffffff
#define  VTSS_X_HSCH_TAS_LIST_STATE_INT_CYC_TIME_REMAIN(x)  (x)

/**
 * Register Group: \a HSCH:TAS_GCL_CFG
 *
 * Time Aware Shapper Oper parameter(s)/status registers.
 */


/**
 * \brief TAS - Oper Gate control list status register - 1
 *
 * \details
 * Register: \a HSCH:TAS_GCL_CFG:TAS_GCL_CTRL_CFG
 */
#define VTSS_HSCH_TAS_GCL_CTRL_CFG           VTSS_IOREG(VTSS_TO_HSCH,0x2364)

/**
 * \brief
 * A 8 bit vector determing gates state of 8 priorities for the scheduling
 * element. This is 'gateStatesValue' value (IEEE 802.1Qbv).
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_GCL_CTRL_CFG . GATE_STATE
 */
#define  VTSS_F_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/**
 * \brief
 * Selects the type of gate operation for the GCL entry.

 *
 * \details
 * The type of gate operation is determined as follows:
 * 00: SetGateStates. The state of queues are updated according to
 * GATE_STATE.
 * 01: Reserved
 * 10: Set-And-Release-MAC. The state of queues are updated according to
 *	     GATE_STATE. The MAC is signaled to release any hold of
 *	     preemptible frames set by Set-And-Hold-MAC.
 * 11: Set-And-Hold-MAC. The state of queues are updated according to
 * GATE_STATE.
 *	     The MAC is signaled to stop allowing the transmission of
 *	     preemptible frames, and any currently transmitting preemptible
 *	     frame is preempted if possible.

 *
 * Field: ::VTSS_HSCH_TAS_GCL_CTRL_CFG . OP_TYPE
 */
#define  VTSS_F_HSCH_TAS_GCL_CTRL_CFG_OP_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_TAS_GCL_CTRL_CFG_OP_TYPE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_TAS_GCL_CTRL_CFG_OP_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief TAS - Oper Gate control list status register - 2
 *
 * \details
 * Register: \a HSCH:TAS_GCL_CFG:TAS_GCL_CTRL_CFG2
 */
#define VTSS_HSCH_TAS_GCL_CTRL_CFG2          VTSS_IOREG(VTSS_TO_HSCH,0x2365)

/**
 * \brief
 * Points to the next GCL entry in the list after
 *	   this entry. The end of a list is marked by a GCL entry pointing
 * back
 *	   to the start of the list (as given by
 *	   QSYS:TAS_LIST_CFG:TAS_LIST_CFG.LIST_BASE_ADDR).
 *
 *	   The sequence of entries must not contain loops (other than the
 * last
 *	   entry pointing back to the first), otherwise the list will not
 * be
 *	   able to operate correctly. The sum of TIME_INTERVAL for all GCL
 *	   entries must not be greater than the CYCLE_TIME of the list;
 *	   otherwise the internal time calculations will underflow and
 *	   incorrect operation will result.

 *
 * \details
 * Field: ::VTSS_HSCH_TAS_GCL_CTRL_CFG2 . NEXT_GCL
 */
#define  VTSS_F_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSCH_TAS_GCL_CTRL_CFG2_NEXT_GCL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/**
 * \brief TAS - Oper Gate control list status register - 3
 *
 * \details
 * Register: \a HSCH:TAS_GCL_CFG:TAS_GCL_TIME_CFG
 */
#define VTSS_HSCH_TAS_GCL_TIME_CFG           VTSS_IOREG(VTSS_TO_HSCH,0x2366)

/**
 * \brief
 * Time interval expressed as nanoseconds used for execution of
 * corresponding gate state. This is 'timeIntervalValue' value (IEEE
 * 802.1Qbv).Reading this register actually performs RAM read for GCL entry
 * (GCL_ENTRY_NUM) with values {TIME_INTERVAL, GATE_STATE}.
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_GCL_TIME_CFG . TIME_INTERVAL
 */
#define  VTSS_F_HSCH_TAS_GCL_TIME_CFG_TIME_INTERVAL(x)  (x)
#define  VTSS_M_HSCH_TAS_GCL_TIME_CFG_TIME_INTERVAL     0xffffffff
#define  VTSS_X_HSCH_TAS_GCL_TIME_CFG_TIME_INTERVAL(x)  (x)

/**
 * Register Group: \a HSCH:HSCH_TAS_STATE
 *
 * Status of scheduling element inputs by TAS
 */


/**
 * \brief INPUT state
 *
 * \details
 * Register: \a HSCH:HSCH_TAS_STATE:TAS_GATE_STATE
 */
#define VTSS_HSCH_TAS_GATE_STATE             VTSS_IOREG(VTSS_TO_HSCH,0x2368)

/**
 * \brief
 * Mapped to the state of the gates pointed to by TAS_GATE_STATE_CTRL
 *
 * \details
 * Field: ::VTSS_HSCH_TAS_GATE_STATE . TAS_GATE_STATE
 */
#define  VTSS_F_HSCH_TAS_GATE_STATE_TAS_GATE_STATE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSCH_TAS_GATE_STATE_TAS_GATE_STATE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSCH_TAS_GATE_STATE_TAS_GATE_STATE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_LAGUNA_REGS_HSCH_H_ */
