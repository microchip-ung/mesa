#ifndef _VTSS_JAGUAR2_REGS_HSCH_H_
#define _VTSS_JAGUAR2_REGS_HSCH_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HSCH
 *
 * Hierarchical Scheduler Configuration
 *
 ***********************************************************************/

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
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
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
 * Burst capacity of this shaper. Unit is 4096 kilobytes. The shaper is
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
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_CFG_EIR_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,1)

/** 
 * \brief
 * Leak rate for this shaper. Same unit as CIR_RATE unit. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_EIR_CFG . EIR_RATE
 */
#define  VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,7,17)
#define  VTSS_M_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE     VTSS_ENCODE_BITMASK(7,17)
#define  VTSS_X_HSCH_HSCH_CFG_EIR_CFG_EIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,7,17)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4096 bytes. The dual leaky bucket
 * shaper operates as a single leaky bucket shaper when EIR_BURST=0. 
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_EIR_CFG . EIR_BURST
 */
#define  VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_HSCH_HSCH_CFG_EIR_CFG_EIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * If a frame is scheduled with excess information rate, the frame color
 * can be changed to yellow.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_EIR_CFG . EIR_MARK_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_EIR_CFG_EIR_MARK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_CFG_EIR_CFG_EIR_MARK_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_CFG_EIR_CFG_EIR_MARK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of shaper and scheduling algorithm
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CFG
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
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
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Enable AVB mode for this shaper, creating burst capacity only when data
 * is available.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CFG . SE_AVB_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA  VTSS_BIT(4)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_AVB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

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
#define  VTSS_F_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CFG_SE_DWRR_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Configuration of the connections between SEs
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_CONNECT
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_CFG_SE_CONNECT(gi)    VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,3)

/** 
 * \brief
 * layer 1+2: Index of se in lower layer.
 * Layer 0: Port number the SE is used for.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CONNECT . SE_INP_IDX
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CONNECT_SE_INP_IDX(x)  VTSS_ENCODE_BITFIELD(x,18,12)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CONNECT_SE_INP_IDX     VTSS_ENCODE_BITMASK(18,12)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_INP_IDX(x)  VTSS_EXTRACT_BITFIELD(x,18,12)

/** 
 * \brief
 * Layer 1+2: Forms the leak chains.
 * Layer 0: This field must be set to the port number the element controls.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CONNECT . SE_LEAK_IDX
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_IDX(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_IDX     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_LEAK_IDX(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Reference to higher layer in the hierarchy, or portno for the top.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CONNECT . SE_OUTP_IDX
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_IDX(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_IDX     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_IDX(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * The input port on the next SE, which this SE connects to. The next SE is
 * selected by SE_OUTP_IDX.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_CONNECT . SE_OUTP_CON
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_CON(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_CON     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_CONNECT_SE_OUTP_CON(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of which fill levels in the queue system that the DLB shapers use to trigger excess information rate
 *
 * \details
 * Register: \a HSCH:HSCH_CFG:SE_DLB_SENSE
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x0,gi,8,0,4)

/** 
 * \brief
 * QoS class used when SE_DLB_PRIO_ENA is set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_PRIO
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/** 
 * \brief
 * Source port used when SE_DLB_SPORT_ENA is set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_SPORT
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT(x)  VTSS_ENCODE_BITFIELD(x,9,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT     VTSS_ENCODE_BITMASK(9,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT(x)  VTSS_EXTRACT_BITFIELD(x,9,6)

/** 
 * \brief
 * Destination port used when SE_DLB_DPORT_ENA is set.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_DPORT
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

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
 * Enable source port awareness by the DLB shaper. If set, the DLB shaper
 * allows excess information rate when the ingress buffer use for source
 * port SE_DLB_SPORT has reached threshold BUF_P_RSRV_I[SE_DLB_SPORT] minus
 * 3000 bytes.
 * 
 * If multiple awareness functions (SE_DLB_PRIO_ENA, SE_DLB_SPORT_ENA,
 * SE_DLB_DPORT_ENA) are enabled, all relevant thresholds must be exceeded
 * before excess information rate is allowed.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_CFG_SE_DLB_SENSE . SE_DLB_SPORT_ENA
 */
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_ENA  VTSS_BIT(1)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_SPORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

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
#define  VTSS_F_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_CFG_SE_DLB_SENSE_SE_DLB_DPORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_STATUS_CIR_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x8000,gi,4,0,0)

/** 
 * \brief
 * Current fill level. Unit is 1 bit.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,2,24)
#define  VTSS_M_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(2,24)
#define  VTSS_X_HSCH_HSCH_STATUS_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,2,24)

/** 
 * \brief
 * These bits are not functionally connected
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_CIR_STATE . RESERVED
 */
#define  VTSS_F_HSCH_HSCH_STATUS_CIR_STATE_RESERVED(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_HSCH_STATUS_CIR_STATE_RESERVED     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_HSCH_STATUS_CIR_STATE_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief EIR status
 *
 * \details
 * Register: \a HSCH:HSCH_STATUS:EIR_STATE
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_STATUS_EIR_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x8000,gi,4,0,1)

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
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_STATUS_SE_STATE(gi)   VTSS_IOREG_IX(VTSS_TO_HSCH,0x8000,gi,4,0,2)

/** 
 * \brief
 * State. Tells that this SE has data available for transmission
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_SE_STATE . SE_IS_OPEN
 */
#define  VTSS_F_HSCH_HSCH_STATUS_SE_STATE_SE_IS_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_HSCH_STATUS_SE_STATE_SE_IS_OPEN  VTSS_BIT(1)
#define  VTSS_X_HSCH_HSCH_STATUS_SE_STATE_SE_IS_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Last schedulling was yellow for this SE
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_STATUS_SE_STATE . SE_WAS_YEL
 */
#define  VTSS_F_HSCH_HSCH_STATUS_SE_STATE_SE_WAS_YEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_STATUS_SE_STATE_SE_WAS_YEL  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_STATUS_SE_STATE_SE_WAS_YEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSCH:HSCH_INP_STATE
 *
 * Status of scheduling element inputs
 */


/** 
 * \brief INPUT state for inputs 0-31
 *
 * \details
 * Register: \a HSCH:HSCH_INP_STATE:INP_STATE
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_INP_STATE_INP_STATE(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xc000,gi,2,0,0)

/** 
 * \brief
 * Bit n will be set if input n has data ready
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_INP_STATE_INP_STATE . INP_STATE
 */
#define  VTSS_F_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE(x)  (x)
#define  VTSS_M_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE     0xffffffff
#define  VTSS_X_HSCH_HSCH_INP_STATE_INP_STATE_INP_STATE(x)  (x)


/** 
 * \brief INPUT state for inputs 32-63
 *
 * \details
 * Register: \a HSCH:HSCH_INP_STATE:INP_STATE1
 *
 * @param gi Replicator: x_HSCH_SE_CNT (??), 0-4064
 */
#define VTSS_HSCH_HSCH_INP_STATE_INP_STATE1(gi)  VTSS_IOREG_IX(VTSS_TO_HSCH,0xc000,gi,2,0,1)

/** 
 * \brief
 * Bit n will be set if input 32+n has data ready
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_INP_STATE_INP_STATE1 . INP_STATE1
 */
#define  VTSS_F_HSCH_HSCH_INP_STATE_INP_STATE1_INP_STATE1(x)  (x)
#define  VTSS_M_HSCH_HSCH_INP_STATE_INP_STATE1_INP_STATE1     0xffffffff
#define  VTSS_X_HSCH_HSCH_INP_STATE_INP_STATE1_INP_STATE1(x)  (x)

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
 * @param gi Replicator: x_HSCH_DWRR_CNT (??), 0-63
 */
#define VTSS_HSCH_HSCH_DWRR_DWRR_ENTRY(gi)   VTSS_IOREG_IX(VTSS_TO_HSCH,0x7f40,gi,1,0,0)

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
#define VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG    VTSS_IOREG(VTSS_TO_HSCH,0x7f80)

/** 
 * \brief
 * Set to one when the SE connection configuration is valid. Set to zero
 * when reconfiguring SE inter connections
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . SE_CONNECT_VLD
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_SE_CONNECT_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_SE_CONNECT_VLD  VTSS_BIT(15)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_SE_CONNECT_VLD(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set this to one to disabled all leaking from leaky bucket shapers
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . LEAK_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS  VTSS_BIT(14)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_LEAK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Values to add each frame when frame length adjustment is in use.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . FRM_ADJ
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,9,5)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ     VTSS_ENCODE_BITMASK(9,5)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,9,5)

/** 
 * \brief
 * For the queue connected layer, the first <this value>scheduling elements
 * are connected to 64 input queues, the rest to 8.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_MISC_CFG . HSCH_LARGE_CNT
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_MISC_CFG_HSCH_LARGE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_MISC_CFG_HSCH_LARGE_CNT     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_MISC_CFG_HSCH_LARGE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


/** 
 * \brief Configuration selection register
 *
 * \details
 * Register: \a HSCH:HSCH_MISC:HSCH_CFG_CFG
 */
#define VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG     VTSS_IOREG(VTSS_TO_HSCH,0x7f81)

/** 
 * \brief
 * The DWRR balances will be accessed for the scheduling element indexed by
 * this field.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG . DWRR_IDX
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_DWRR_IDX(x)  VTSS_ENCODE_BITFIELD(x,2,12)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_DWRR_IDX     VTSS_ENCODE_BITMASK(2,12)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_CFG_CFG_DWRR_IDX(x)  VTSS_EXTRACT_BITFIELD(x,2,12)

/** 
 * \brief
 * The HSCH layer set in this field will be accessed by the configuration
 * interfaces.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_HSCH_CFG_CFG . HSCH_LAYER
 */
#define  VTSS_F_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSCH_HSCH_MISC_HSCH_CFG_CFG_HSCH_LAYER(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per frontport and for each of the two CPU
 * ports (11+12).
 *
 * Register: \a HSCH:HSCH_MISC:PORT_MODE
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_HSCH_HSCH_MISC_PORT_MODE(ri)    VTSS_IOREG(VTSS_TO_HSCH,0x7f82 + (ri))

/** 
 * \brief
 * Disable dequeuing from the egress queues. Frames are not discarded, but
 * may become aged when dequeuing is reenabled.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . DEQUEUE_DIS
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS  VTSS_BIT(5)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_DEQUEUE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable flushing of all frames to the port.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . FLUSH_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_FLUSH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_FLUSH_ENA  VTSS_BIT(4)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_FLUSH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE  VTSS_BIT(1)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_CPU_PRIO_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables the middle layer for the port. Otherwise buttom and top layer
 * are directly connected in the hierarchy.
 *
 * \details 
 * Field: ::VTSS_HSCH_HSCH_MISC_PORT_MODE . MIDLAYER_ENA
 */
#define  VTSS_F_HSCH_HSCH_MISC_PORT_MODE_MIDLAYER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_HSCH_MISC_PORT_MODE_MIDLAYER_ENA  VTSS_BIT(0)
#define  VTSS_X_HSCH_HSCH_MISC_PORT_MODE_MIDLAYER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
 * @param gi Register: HSCH_LEAK_LISTS (??), 0-2
 * @param ri Register: HSCH_LEAK_CFG (??), 0-3
 */
#define VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_HSCH,0x7f08,gi,4,ri,0)

/** 
 * \brief
 * Number of system cycles between each traversal of the leak list. System
 * cycle is 4 ns, making a value of 2500 correspond to 10us. Each traversal
 * subtracts the configured rate from the shaper buckets, counting bits.
 * With the value of 2500, a rate of 1 corresponds to 1 bit per 10us, or
 * 100kbps.
 * A leak group can be set up for 16kbps unit by seting the leak_time to 1
 * bit per 3906 cycles, giving a unit of 64.004kbps.

 *
 * \details 
 * 0: Leaking disabled
 * 2500: 100kbps unit
 * 3906: 64kbps unit
 * 25000: 1Mbps unit
 * (any other)
 *
 * Field: ::VTSS_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG . LEAK_TIME
 */
#define  VTSS_F_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME(x)  VTSS_ENCODE_BITFIELD(x,13,16)
#define  VTSS_M_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME     VTSS_ENCODE_BITMASK(13,16)
#define  VTSS_X_HSCH_HSCH_LEAK_LISTS_HSCH_LEAK_CFG_LEAK_TIME(x)  VTSS_EXTRACT_BITFIELD(x,13,16)

/** 
 * \brief
 * First SE in the leak group
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

/**
 * Register Group: \a HSCH:MISC
 *
 * Miscellaneous
 */


/** 
 * \brief Internal events for debugging only
 *
 * \details
 * Core events.
 *
 * Register: \a HSCH:MISC:EVENTS_CORE
 */
#define VTSS_HSCH_MISC_EVENTS_CORE           VTSS_IOREG(VTSS_TO_HSCH,0x7f14)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENTS_CORE . EV_HSCH
 */
#define  VTSS_F_HSCH_MISC_EVENTS_CORE_EV_HSCH(x)  VTSS_ENCODE_BITFIELD(x,5,7)
#define  VTSS_M_HSCH_MISC_EVENTS_CORE_EV_HSCH     VTSS_ENCODE_BITMASK(5,7)
#define  VTSS_X_HSCH_MISC_EVENTS_CORE_EV_HSCH(x)  VTSS_EXTRACT_BITFIELD(x,5,7)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENTS_CORE . EV_FRD
 */
#define  VTSS_F_HSCH_MISC_EVENTS_CORE_EV_FRD(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_HSCH_MISC_EVENTS_CORE_EV_FRD     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_HSCH_MISC_EVENTS_CORE_EV_FRD(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * If an frame is added to an invalid queue in the scheduling hierarchy,
 * this sticky bit will be set, and the violating request is see the
 * EVENT_ENQ_ERR register.
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENTS_CORE . EV_ENQ_ERR
 */
#define  VTSS_F_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR  VTSS_BIT(0)
#define  VTSS_X_HSCH_MISC_EVENTS_CORE_EV_ENQ_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Information about enqueueing error
 *
 * \details
 * Register: \a HSCH:MISC:EVENT_ENQ_ERR
 */
#define VTSS_HSCH_MISC_EVENT_ENQ_ERR         VTSS_IOREG(VTSS_TO_HSCH,0x7f15)

/** 
 * \brief
 * Contains last enqueuing error egress port number
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENT_ENQ_ERR . ENQ_ERR_PORT
 */
#define  VTSS_F_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_PORT(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Scheduling element being violated.
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENT_ENQ_ERR . ENQ_ERR_SE
 */
#define  VTSS_F_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_SE(x)  VTSS_ENCODE_BITFIELD(x,6,12)
#define  VTSS_M_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_SE     VTSS_ENCODE_BITMASK(6,12)
#define  VTSS_X_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_SE(x)  VTSS_EXTRACT_BITFIELD(x,6,12)

/** 
 * \brief
 * Input number violating the SE
 *
 * \details 
 * Field: ::VTSS_HSCH_MISC_EVENT_ENQ_ERR . ENQ_ERR_INP
 */
#define  VTSS_F_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_INP(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_INP     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSCH_MISC_EVENT_ENQ_ERR_ENQ_ERR_INP(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


#endif /* _VTSS_JAGUAR2_REGS_HSCH_H_ */
