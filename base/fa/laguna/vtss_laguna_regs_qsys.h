// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_QSYS_H_
#define _VTSS_LAGUNA_REGS_QSYS_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a QSYS
 *
 * Queue System Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a QSYS:SYSTEM
 *
 * Switch configuration
 */


/**
 * \brief Control Energy Efficient Ethernet operation per front port.
 *
 * \details
 * Register: \a QSYS:SYSTEM:EEE_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-29
 */
#define VTSS_QSYS_EEE_CFG(ri)                VTSS_IOREG(VTSS_TO_QSYS,0x0 + (ri))

/**
 * \brief
 * Queues set in this mask activate the egress port immediately when any of
 * the queues have data available.
 *
 * \details
 * Field: ::VTSS_QSYS_EEE_CFG . EEE_FAST_QUEUES
 */
#define  VTSS_F_QSYS_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_EEE_CFG_EEE_FAST_QUEUES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Thresholds for delayed EEE queues
 *
 * \details
 * Register: \a QSYS:SYSTEM:EEE_THRES
 */
#define VTSS_QSYS_EEE_THRES                  VTSS_IOREG(VTSS_TO_QSYS,0x41)

/**
 * \brief
 * Maximum number of bytes in a queue before egress port is activated. Unit
 * is 60 bytes.
 *
 * \details
 * Field: ::VTSS_QSYS_EEE_THRES . EEE_HIGH_BYTES
 */
#define  VTSS_F_QSYS_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_QSYS_EEE_THRES_EEE_HIGH_BYTES     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_QSYS_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Maximum number of frames in a queue before the egress port is activated.
 * Unit is 1 frame.
 *
 * \details
 * Field: ::VTSS_QSYS_EEE_THRES . EEE_HIGH_FRAMES
 */
#define  VTSS_F_QSYS_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_EEE_THRES_EEE_HIGH_FRAMES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Frame aging configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:FRM_AGING
 */
#define VTSS_QSYS_FRM_AGING                  VTSS_IOREG(VTSS_TO_QSYS,0x42)

/**
 * \brief
 * Frames are aged and removed from the queue system when the frame's age
 * timer becomes two. The frame age timer is increased for all frames
 * whenever the configured time, MAX_AGE,  has passed. Effectively, this
 * means that a frame is aged when the frame has waited in the queue system
 * between one or two times the period specified by MAX_AGE.The periodd
 * configured by MAX_AGE is also termed an "age era".A value of zero
 * disables frame aging. Frame aging related
 * parameters:QSYS:SYSTEM:FRM_AGING.MAX_AGEHSCH:SYSTEM:PORT_MODE.AGE_DISDSM
 * :CFG:BUF_CFG.AGING_ENA
 *
 * \details
 * 0: Disable frame aging.
 * >=1: Era length in unit of 4us.
 *
 * Field: ::VTSS_QSYS_FRM_AGING . MAX_AGE
 */
#define  VTSS_F_QSYS_FRM_AGING_MAX_AGE(x)     VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_QSYS_FRM_AGING_MAX_AGE        VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_QSYS_FRM_AGING_MAX_AGE(x)     VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Map DP values to color
 *
 * \details
 * Register: \a QSYS:SYSTEM:DP_MAP
 */
#define VTSS_QSYS_DP_MAP                     VTSS_IOREG(VTSS_TO_QSYS,0x43)

/**
 * \brief
 * Drop precedence N uses mapping table given by bit N in this field.
 *
 * \details
 * xxx0: Map DP value 0 to DE value 0
 * xxx1: Map DP value 0 to DE value 1
 * ...
 * 0xxx: Map DP value 3 to DE value 0
 * 1xxx: Map DP value 3 to DE value 1

 *
 * Field: ::VTSS_QSYS_DP_MAP . DP
 */
#define  VTSS_F_QSYS_DP_MAP_DP(x)             VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_QSYS_DP_MAP_DP                VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_QSYS_DP_MAP_DP(x)             VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Statistics configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:STAT_CFG
 */
#define VTSS_QSYS_STAT_CFG                   VTSS_IOREG(VTSS_TO_QSYS,0x44)

/**
 * \brief
 * Set to disable counting buffer drops (tail) in the general rx drop
 * counter.
 *
 * \details
 * Field: ::VTSS_QSYS_STAT_CFG . STAT_RX_TAILDROP_DIS
 */
#define  VTSS_F_QSYS_STAT_CFG_STAT_RX_TAILDROP_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_STAT_CFG_STAT_RX_TAILDROP_DIS  VTSS_BIT(0)
#define  VTSS_X_QSYS_STAT_CFG_STAT_RX_TAILDROP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Ingress queue delay setup
 *
 * \details
 * Register: \a QSYS:SYSTEM:IQUEUE_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-29
 */
#define VTSS_QSYS_IQUEUE_CFG(ri)             VTSS_IOREG(VTSS_TO_QSYS,0x45 + (ri))

/**
 * \brief
 * Enable cut-through out of the ingress queue for the port, by iprio
 * class.
 *
 * \details
 * Field: ::VTSS_QSYS_IQUEUE_CFG . CT_ENA
 */
#define  VTSS_F_QSYS_IQUEUE_CFG_CT_ENA(x)     VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_IQUEUE_CFG_CT_ENA        VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_IQUEUE_CFG_CT_ENA(x)     VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Hidden unusable features, primarily for testing
 *
 * \details
 * Special features.
 *
 * Register: \a QSYS:SYSTEM:DBG_UTIL
 */
#define VTSS_QSYS_DBG_UTIL                   VTSS_IOREG(VTSS_TO_QSYS,0x86)

/**
 * \brief
 * Use DMAC(..-0)SMAC(47-0) as destination set!
 *
 * \details
 * Field: ::VTSS_QSYS_DBG_UTIL . DST_BY_MACADDR
 */
#define  VTSS_F_QSYS_DBG_UTIL_DST_BY_MACADDR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSYS_DBG_UTIL_DST_BY_MACADDR  VTSS_BIT(1)
#define  VTSS_X_QSYS_DBG_UTIL_DST_BY_MACADDR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Use DMAC(31-24 as rewcmd!
 *
 * \details
 * Field: ::VTSS_QSYS_DBG_UTIL . REWCMD_BY_MACADDR
 */
#define  VTSS_F_QSYS_DBG_UTIL_REWCMD_BY_MACADDR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_DBG_UTIL_REWCMD_BY_MACADDR  VTSS_BIT(0)
#define  VTSS_X_QSYS_DBG_UTIL_REWCMD_BY_MACADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QSYS:MISC
 *
 * Miscellaneous
 */


/**
 * \brief Internal events for debugging only
 *
 * \details
 * Core events.
 *
 * Register: \a QSYS:MISC:EVENTS_CORE
 */
#define VTSS_QSYS_EVENTS_CORE                VTSS_IOREG(VTSS_TO_QSYS,0x87)

/**
 * \brief
 * Look in the RTL!
 *
 * \details
 * Field: ::VTSS_QSYS_EVENTS_CORE . EV_FWR
 */
#define  VTSS_F_QSYS_EVENTS_CORE_EV_FWR(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSYS_EVENTS_CORE_EV_FWR       VTSS_BIT(3)
#define  VTSS_X_QSYS_EVENTS_CORE_EV_FWR(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Look in the RTL!
 *
 * \details
 * Field: ::VTSS_QSYS_EVENTS_CORE . EV_FDC
 */
#define  VTSS_F_QSYS_EVENTS_CORE_EV_FDC(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_QSYS_EVENTS_CORE_EV_FDC       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_QSYS_EVENTS_CORE_EV_FDC(x)    VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a QSYS:PAUSE_CFG
 *
 * Watermarks for egress queue system
 */


/**
 * \brief Watermarks for flow control condition per switch port.
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:PAUSE_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_PAUSE_CFG(ri)              VTSS_IOREG(VTSS_TO_QSYS,0x88 + (ri))

/**
 * \brief
 * Start pausing ingress stream when the amount of memory consumed by the
 * port exceeds this watermark. The TOTPAUSE condition must also be met.
 *
 * \details
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG . PAUSE_START
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_START(x)  VTSS_ENCODE_BITFIELD(x,14,11)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_START     VTSS_ENCODE_BITMASK(14,11)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_START(x)  VTSS_EXTRACT_BITFIELD(x,14,11)

/**
 * \brief
 * Stop pausing ingress stream when the amount of memory consumed by the
 * port is below  this watermark.
 *
 * \details
 * See RES_CFG.
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG . PAUSE_STOP
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_STOP(x)  VTSS_ENCODE_BITFIELD(x,2,11)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_STOP     VTSS_ENCODE_BITMASK(2,11)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,2,11)

/**
 * \brief
 * Enable pause feedback to the MAC, allowing transmission of pause frames
 * or HDX collisions to limit ingress data rate.
 *
 * \details
 * Field: ::VTSS_QSYS_PAUSE_CFG . PAUSE_ENA
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_ENA      VTSS_BIT(1)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_ENA(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_QSYS_PAUSE_CFG . AGGRESSIVE_TAILDROP_ENA
 */
#define  VTSS_F_QSYS_PAUSE_CFG_AGGRESSIVE_TAILDROP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_PAUSE_CFG_AGGRESSIVE_TAILDROP_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_PAUSE_CFG_AGGRESSIVE_TAILDROP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configure total memory pause condition
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:PAUSE_TOT_CFG
 */
#define VTSS_QSYS_PAUSE_TOT_CFG              VTSS_IOREG(VTSS_TO_QSYS,0xce)

/**
 * \brief
 * Assert TOTPAUSE condition when total memory allocation is above this
 * watermark.
 *
 * \details
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_TOT_CFG . PAUSE_TOT_START
 */
#define  VTSS_F_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_ENCODE_BITFIELD(x,12,11)
#define  VTSS_M_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_START     VTSS_ENCODE_BITMASK(12,11)
#define  VTSS_X_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_EXTRACT_BITFIELD(x,12,11)

/**
 * \brief
 * Deassert TOTPAUSE condition when total memory allocation is below this
 * watermark.
 *
 * \details
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_TOT_CFG . PAUSE_TOT_STOP
 */
#define  VTSS_F_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_QSYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Tail dropping level
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:ATOP
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_ATOP(ri)                   VTSS_IOREG(VTSS_TO_QSYS,0xcf + (ri))

/**
 * \brief
 * When a source port consumes more than this level in the packet memory,
 * frames are tail dropped, unconditionally of destination.
 *
 * \details
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_ATOP . ATOP
 */
#define  VTSS_F_QSYS_ATOP_ATOP(x)             VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_QSYS_ATOP_ATOP                VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_QSYS_ATOP_ATOP(x)             VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Forward pressure level
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:FWD_PRESSURE
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_FWD_PRESSURE(ri)           VTSS_IOREG(VTSS_TO_QSYS,0x115 + (ri))

/**
 * \brief
 * When ingress queue request count exceeds FWD_PRESSURE level, forward
 * pressure is enabled for frames arriving on the port. Multicasts from
 * this port are discarded towards destinations that have used all reserved
 * references. Forward pressure on any port in combination with aggressive
 * taildropping (PAUSE_CFG.AGGRESSIVE_TAILDROP_ENA), affects discard policy
 * on other ingress ports with the following conditions true: - Mac- or
 * priority based flow control disabled- Has accumulated more traffic per
 * priority than the PAUSE_START/STOP registers are set to. -Are sending
 * traffic towards a destination port which has no port reserved references
 * left for the frame's priority.Under these conditions, the destination in
 * question is removed from the set of destinations for the frame. (The
 * frame is discarded towards that destination)
 *
 * \details
 * Field: ::VTSS_QSYS_FWD_PRESSURE . FWD_PRESSURE
 */
#define  VTSS_F_QSYS_FWD_PRESSURE_FWD_PRESSURE(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_QSYS_FWD_PRESSURE_FWD_PRESSURE     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_QSYS_FWD_PRESSURE_FWD_PRESSURE(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/**
 * \brief
 * Disable forward pressure per ingress port
 *
 * \details
 * Field: ::VTSS_QSYS_FWD_PRESSURE . FWD_PRESSURE_DIS
 */
#define  VTSS_F_QSYS_FWD_PRESSURE_FWD_PRESSURE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_FWD_PRESSURE_FWD_PRESSURE_DIS  VTSS_BIT(0)
#define  VTSS_X_QSYS_FWD_PRESSURE_FWD_PRESSURE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Total raw memory use before tail dropping is activated
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:ATOP_TOT_CFG
 */
#define VTSS_QSYS_ATOP_TOT_CFG               VTSS_IOREG(VTSS_TO_QSYS,0x15b)

/**
 * \brief
 * Tail dropping is activate on a port when the port use has exceeded the
 * ATOP watermark for the port, and the total memory use has exceeded this
 * watermark.
 *
 * \details
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_ATOP_TOT_CFG . ATOP_TOT
 */
#define  VTSS_F_QSYS_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_QSYS_ATOP_TOT_CFG_ATOP_TOT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_QSYS_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Various switch port mode settings
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:PFC_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_PFC_CFG(ri)                VTSS_IOREG(VTSS_TO_QSYS,0x15c + (ri))

/**
 * \brief
 * When set the MAC sends PRIO pause control frames in the Tx direction
 * when congested.
 *
 * \details
 * Field: ::VTSS_QSYS_PFC_CFG . TX_PFC_ENA
 */
#define  VTSS_F_QSYS_PFC_CFG_TX_PFC_ENA(x)    VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_QSYS_PFC_CFG_TX_PFC_ENA       VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_QSYS_PFC_CFG_TX_PFC_ENA(x)    VTSS_EXTRACT_BITFIELD(x,1,8)

/**
 * \brief
 * When set, a congested priority request pause of all lower priorities as
 * well.
 *
 * \details
 * Field: ::VTSS_QSYS_PFC_CFG . TX_PFC_MODE
 */
#define  VTSS_F_QSYS_PFC_CFG_TX_PFC_MODE(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_PFC_CFG_TX_PFC_MODE      VTSS_BIT(0)
#define  VTSS_X_QSYS_PFC_CFG_TX_PFC_MODE(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QSYS:MMGT_PORT
 *
 * Memory manager status
 */


/**
 * \brief Port to see values for
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_PORT_VIEW
 */
#define VTSS_QSYS_MMGT_PORT_VIEW             VTSS_IOREG(VTSS_TO_QSYS,0x17f)

/**
 * \brief
 * Select port to see consumption values for
 *
 * \details
 * Field: ::VTSS_QSYS_MMGT_PORT_VIEW . MMGT_PORT_VIEW
 */
#define  VTSS_F_QSYS_MMGT_PORT_VIEW_MMGT_PORT_VIEW(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_QSYS_MMGT_PORT_VIEW_MMGT_PORT_VIEW     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_QSYS_MMGT_PORT_VIEW_MMGT_PORT_VIEW(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Total consumption per ingress port
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_PORT_USE
 */
#define VTSS_QSYS_MMGT_PORT_USE              VTSS_IOREG(VTSS_TO_QSYS,0x180)

/**
 * \brief
 * Total consumption per port in the memory manager. Unit is one cell (176
 * bytes).
 *
 * \details
 * Field: ::VTSS_QSYS_MMGT_PORT_USE . MMGT_PORT_USE
 */
#define  VTSS_F_QSYS_MMGT_PORT_USE_MMGT_PORT_USE(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_QSYS_MMGT_PORT_USE_MMGT_PORT_USE     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_QSYS_MMGT_PORT_USE_MMGT_PORT_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/**
 * \brief Packet memory use count per port and priority
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_PRIO_USE
 *
 * @param ri Register: MMGT_PRIO_USE (??), 0-7
 */
#define VTSS_QSYS_MMGT_PRIO_USE(ri)          VTSS_IOREG(VTSS_TO_QSYS,0x181 + (ri))

/**
 * \brief
 * Total consumption per port and priority  in the memory manager. Unit is
 * one cell (176 bytes).
 *
 * \details
 * Field: ::VTSS_QSYS_MMGT_PRIO_USE . MMGT_PRIO_USE
 */
#define  VTSS_F_QSYS_MMGT_PRIO_USE_MMGT_PRIO_USE(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_QSYS_MMGT_PRIO_USE_MMGT_PRIO_USE     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_QSYS_MMGT_PRIO_USE_MMGT_PRIO_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/**
 * \brief Ingress queue status
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_IQ_STAT
 */
#define VTSS_QSYS_MMGT_IQ_STAT               VTSS_IOREG(VTSS_TO_QSYS,0x189)

/**
 * \brief
 * Number of frame copies pending in the ingress queue
 *
 * \details
 * Field: ::VTSS_QSYS_MMGT_IQ_STAT . MMGT_IQ_SIZE
 */
#define  VTSS_F_QSYS_MMGT_IQ_STAT_MMGT_IQ_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_QSYS_MMGT_IQ_STAT_MMGT_IQ_SIZE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_QSYS_MMGT_IQ_STAT_MMGT_IQ_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Tail drop count.
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_TAILDROP_CNT
 */
#define VTSS_QSYS_MMGT_TAILDROP_CNT          VTSS_IOREG(VTSS_TO_QSYS,0x18a)

/**
 * \brief
 * Returns the number of buffer drops due to ATOP reached, or lack of free
 * memory. Values returned for the port mapped in MMGT_PORT_VIEW.Counter
 * wraps when maximum is reached reached.
 *
 * \details
 * Field: ::VTSS_QSYS_MMGT_TAILDROP_CNT . MMGT_TAILDROP_CNT
 */
#define  VTSS_F_QSYS_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a QSYS:SOFDATA_POOL
 *
 * Configuration and status for EACL data pool
 */


/**
 * \brief Status of  of the SOF pool
 *
 * \details
 * Register: \a QSYS:SOFDATA_POOL:SOFDATA_STAT_SHR
 */
#define VTSS_QSYS_SOFDATA_STAT_SHR           VTSS_IOREG(VTSS_TO_QSYS,0x18b)

/**
 * \brief
 * Amount of SOF words in shared use.
 *
 * \details
 * Field: ::VTSS_QSYS_SOFDATA_STAT_SHR . SOFDATA_SHR_USE
 */
#define  VTSS_F_QSYS_SOFDATA_STAT_SHR_SOFDATA_SHR_USE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_QSYS_SOFDATA_STAT_SHR_SOFDATA_SHR_USE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_QSYS_SOFDATA_STAT_SHR_SOFDATA_SHR_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief Status of  of the SOF pool
 *
 * \details
 * Register: \a QSYS:SOFDATA_POOL:SOFDATA_STAT
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_SOFDATA_STAT(ri)           VTSS_IOREG(VTSS_TO_QSYS,0x18c + (ri))

/**
 * \brief
 * Amount of SOF words in use by the by the port.
 *
 * \details
 * Field: ::VTSS_QSYS_SOFDATA_STAT . SOFDATA_PORT_USE
 */
#define  VTSS_F_QSYS_SOFDATA_STAT_SOFDATA_PORT_USE(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_QSYS_SOFDATA_STAT_SOFDATA_PORT_USE     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_QSYS_SOFDATA_STAT_SOFDATA_PORT_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/**
 * \brief Configures egress ACL lookups per port
 *
 * \details
 * Register: \a QSYS:SOFDATA_POOL:SOFDATA_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_QSYS_SOFDATA_CFG(ri)            VTSS_IOREG(VTSS_TO_QSYS,0x1d2 + (ri))

/**
 * \brief
 * Selects the watermark to use for this port, when evaluating whether more
 * SOF data can be allocated to it. If a port cannot be granted more SOF
 * data storage, the EACL module will be given void sof data, and can react
 * on that. A port using more than the watermark value will consume from a
 * shared pool. Size of that pool is compared with the SOFDATA_WM_VAL(4).
 * If both watermarks are reached, no more storage for sof data from the
 * port is granted.
 *
 * \details
 * 0: Use SOFDATA_WM_VAL(0)
 * 1: Use SOFDATA_WM_VAL(1)
 * 2: Use SOFDATA_WM_VAL(2)
 * 3: Use SOFDATA_WM_VAL(3)

 *
 * Field: ::VTSS_QSYS_SOFDATA_CFG . SOFDATA_WM_SEL
 */
#define  VTSS_F_QSYS_SOFDATA_CFG_SOFDATA_WM_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QSYS_SOFDATA_CFG_SOFDATA_WM_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QSYS_SOFDATA_CFG_SOFDATA_WM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Watermarks for SOF Data
 *
 * \details
 * Register: \a QSYS:SOFDATA_POOL:SOFDATA_WM_VAL
 *
 * @param ri Register: SOFDATA_WM_VAL (??), 0-4
 */
#define VTSS_QSYS_SOFDATA_WM_VAL(ri)         VTSS_IOREG(VTSS_TO_QSYS,0x218 + (ri))

/**
 * \brief
 * Watermark value to use for SOF Data allocation. Watermarks 0-3 are used
 * by per port reservations. Watermark 4 is used for the shared pool of sof
 * data.
 *
 * \details
 * Field: ::VTSS_QSYS_SOFDATA_WM_VAL . SOFDATA_WM_VAL
 */
#define  VTSS_F_QSYS_SOFDATA_WM_VAL_SOFDATA_WM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_QSYS_SOFDATA_WM_VAL_SOFDATA_WM_VAL     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_QSYS_SOFDATA_WM_VAL_SOFDATA_WM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a QSYS:CALCFG
 *
 * Not documented
 */


/**
 * \brief Automatic calendar setup
 *
 * \details
 * These registers configures the automaric calendar for the next 10 ports
 * from 'repl'*10.
 *
 * Register: \a QSYS:CALCFG:CAL_AUTO
 *
 * @param ri Replicator: x_GAZ_CORE_CBC_AUTO_REGS (??), 0-3
 */
#define VTSS_QSYS_CAL_AUTO(ri)               VTSS_IOREG(VTSS_TO_QSYS,0x21d + (ri))

/**
 * \brief
 * Per port setting for internal bandwidth for 10 ports. Replication M,
 * Bits 3N+2 down to 3N is a three bit value for port M*10+N, encoded as
 * seen below.Related
 * parameters:HSCH:SYSTEM:OUTB_SHARE_ENA.OUTB_SHARE_ENAHSCH:SYSTEM:OUTB_CPU
 * _SHARE_ENA.OUTB_CPU_SHARE_ENA
 *
 * \details
 * 000: Port not active
 * 001: Port granted 1	 Gbps
 * 010: Port granted 2.5 Gbps
 * 011: Port granted 5	 Gbps
 * 100: Port granted 10  Gbps
 * 101: Port granted 25  Gbps
 * 110: Port granted 0.5 Gbps
 * 111: Port granted 12.5Gbps

 *
 * Field: ::VTSS_QSYS_CAL_AUTO . CAL_AUTO
 */
#define  VTSS_F_QSYS_CAL_AUTO_CAL_AUTO(x)     VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_QSYS_CAL_AUTO_CAL_AUTO        VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_QSYS_CAL_AUTO_CAL_AUTO(x)     VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Manual calendar setup
 *
 * \details
 * Register: \a QSYS:CALCFG:CAL_SEQ
 */
#define VTSS_QSYS_CAL_SEQ                    VTSS_IOREG(VTSS_TO_QSYS,0x224)

/**
 * \brief
 * Last entry in manual sequence.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ . CAL_SEQ_LEN
 */
#define  VTSS_F_QSYS_CAL_SEQ_CAL_SEQ_LEN(x)   VTSS_ENCODE_BITFIELD(x,15,11)
#define  VTSS_M_QSYS_CAL_SEQ_CAL_SEQ_LEN      VTSS_ENCODE_BITMASK(15,11)
#define  VTSS_X_QSYS_CAL_SEQ_CAL_SEQ_LEN(x)   VTSS_EXTRACT_BITFIELD(x,15,11)

/**
 * \brief
 * Port to service in the cycle given by the CAL_SEQ_LEN value. Calendar
 * sequence can only be read back when the calendar mode isn't
 * CAL_MODE_SEQ.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ . CAL_SEQ_CUR_VAL
 */
#define  VTSS_F_QSYS_CAL_SEQ_CAL_SEQ_CUR_VAL(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_QSYS_CAL_SEQ_CAL_SEQ_CUR_VAL     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_QSYS_CAL_SEQ_CAL_SEQ_CUR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/**
 * \brief
 * The CAL_SEQ_PGM_VAL is written into the sequence entry CAL_SEQ_LEN.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ . CAL_SEQ_PGM_VAL
 */
#define  VTSS_F_QSYS_CAL_SEQ_CAL_SEQ_PGM_VAL(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_QSYS_CAL_SEQ_CAL_SEQ_PGM_VAL     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_QSYS_CAL_SEQ_CAL_SEQ_PGM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/**
 * \brief
 * Enable update of the CAL_SEQ.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ . CAL_SEQ_PGM_ENA
 */
#define  VTSS_F_QSYS_CAL_SEQ_CAL_SEQ_PGM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_CAL_SEQ_CAL_SEQ_PGM_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_CAL_SEQ_CAL_SEQ_PGM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Manual calendar control.
 *
 * \details
 * Control part of calendar sequence in use
 *
 * Register: \a QSYS:CALCFG:CAL_SEQ_SEL_CFG
 */
#define VTSS_QSYS_CAL_SEQ_SEL_CFG            VTSS_IOREG(VTSS_TO_QSYS,0x225)

/**
 * \brief
 * Sequenced calendar is active from CAL_SEQ_FIRST to CAL_SEQ_LAST
 * (including), of the 2048 long sequence memory. If the first entry index
 * is higher than the last index, the sequence reader will automaticaly
 * continue from index 0 after the last memory entry.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ_SEL_CFG . CAL_SEQ_FIRST
 */
#define  VTSS_F_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_FIRST(x)  VTSS_ENCODE_BITFIELD(x,12,11)
#define  VTSS_M_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_FIRST     VTSS_ENCODE_BITMASK(12,11)
#define  VTSS_X_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_FIRST(x)  VTSS_EXTRACT_BITFIELD(x,12,11)

/**
 * \brief
 * Last entry of active sequence.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ_SEL_CFG . CAL_SEQ_LAST
 */
#define  VTSS_F_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_LAST(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_LAST     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_LAST(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/**
 * \brief
 * The field must be set to 1 for activating a new sequence subspace. Field
 * is automatically cleared when switch has been made - which is done when
 * the current active calendar has read its last entry.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_SEQ_SEL_CFG . CAL_SEQ_SWITCH
 */
#define  VTSS_F_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_SWITCH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_SWITCH  VTSS_BIT(0)
#define  VTSS_X_QSYS_CAL_SEQ_SEL_CFG_CAL_SEQ_SWITCH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Calendar configuration
 *
 * \details
 * Register: \a QSYS:CALCFG:CAL_CTRL
 */
#define VTSS_QSYS_CAL_CTRL                   VTSS_IOREG(VTSS_TO_QSYS,0x226)

/**
 * \brief
 * Whenever no ports needs a grant, the slot will be marked as available to
 * internal ports. Every 256 times this value cycles, the next idle slot
 * will be marked as forced idle, assuring processing time for background
 * processes in the involved pipelines.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_CTRL . CAL_IDLE_RATE
 */
#define  VTSS_F_QSYS_CAL_CTRL_CAL_IDLE_RATE(x)  VTSS_ENCODE_BITFIELD(x,15,6)
#define  VTSS_M_QSYS_CAL_CTRL_CAL_IDLE_RATE     VTSS_ENCODE_BITMASK(15,6)
#define  VTSS_X_QSYS_CAL_CTRL_CAL_IDLE_RATE(x)  VTSS_EXTRACT_BITFIELD(x,15,6)

/**
 * \brief
 * The internal bus calendars can be set to an automatic sequence generated
 * by the CAL_AUTO registers, or to a specific sequence programmed through
 * the CAL_SEQ fields.
 *
 * \details
 * 8:  CAL_AUTO port setting
 * 9:  Sequence program
 * 10: Halt
 * others: reserved
 *
 * Field: ::VTSS_QSYS_CAL_CTRL . CAL_MODE
 */
#define  VTSS_F_QSYS_CAL_CTRL_CAL_MODE(x)     VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_QSYS_CAL_CTRL_CAL_MODE        VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_QSYS_CAL_CTRL_CAL_MODE(x)     VTSS_EXTRACT_BITFIELD(x,11,4)

/**
 * \brief
 * Configures the time between bus grants to 1g ports, in nanosecond unit.
 * Other speeds will be adjusted relative to this. Default value of 670 ns
 * corresponds to the minimum packet time (64 bytes) added minor overspeed.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_CTRL . CAL_AUTO_GRANT_RATE
 */
#define  VTSS_F_QSYS_CAL_CTRL_CAL_AUTO_GRANT_RATE(x)  VTSS_ENCODE_BITFIELD(x,1,10)
#define  VTSS_M_QSYS_CAL_CTRL_CAL_AUTO_GRANT_RATE     VTSS_ENCODE_BITMASK(1,10)
#define  VTSS_X_QSYS_CAL_CTRL_CAL_AUTO_GRANT_RATE(x)  VTSS_EXTRACT_BITFIELD(x,1,10)

/**
 * \brief
 * The automatic calendar failed to service all ports.
 *
 * \details
 * Field: ::VTSS_QSYS_CAL_CTRL . CAL_AUTO_ERROR
 */
#define  VTSS_F_QSYS_CAL_CTRL_CAL_AUTO_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_CAL_CTRL_CAL_AUTO_ERROR  VTSS_BIT(0)
#define  VTSS_X_QSYS_CAL_CTRL_CAL_AUTO_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QSYS:RAM_CTRL
 *
 * Access core memory
 */


/**
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a QSYS:RAM_CTRL:RAM_INIT
 */
#define VTSS_QSYS_RAM_INIT                   VTSS_IOREG(VTSS_TO_QSYS,0x227)

/**
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details
 * Field: ::VTSS_QSYS_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_QSYS_RAM_INIT_RAM_INIT(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSYS_RAM_INIT_RAM_INIT        VTSS_BIT(1)
#define  VTSS_X_QSYS_RAM_INIT_RAM_INIT(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details
 * Field: ::VTSS_QSYS_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_QSYS_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_RAM_INIT_RAM_CFG_HOOK    VTSS_BIT(0)
#define  VTSS_X_QSYS_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QSYS:COREMEM
 *
 * Access core memory
 */


/**
 * \brief Address selection
 *
 * \details
 * Register: \a QSYS:COREMEM:CM_ADDR
 */
#define VTSS_QSYS_CM_ADDR                    VTSS_IOREG(VTSS_TO_QSYS,0x228)

/**
 * \brief
 * Address selection for the ram debug address space.
 *
 * \details
 * Field: ::VTSS_QSYS_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_QSYS_CM_ADDR_CM_ADDR(x)       (x)
#define  VTSS_M_QSYS_CM_ADDR_CM_ADDR          0xffffffff
#define  VTSS_X_QSYS_CM_ADDR_CM_ADDR(x)       (x)


/**
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a QSYS:COREMEM:CM_DATA_WR
 */
#define VTSS_QSYS_CM_DATA_WR                 VTSS_IOREG(VTSS_TO_QSYS,0x229)

/**
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.
 *
 * \details
 * Field: ::VTSS_QSYS_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_QSYS_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_QSYS_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_QSYS_CM_DATA_WR_CM_DATA_WR(x)  (x)


/**
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a QSYS:COREMEM:CM_DATA_RD
 */
#define VTSS_QSYS_CM_DATA_RD                 VTSS_IOREG(VTSS_TO_QSYS,0x22a)

/**
 * \brief
 * Read result
 *
 * \details
 * Field: ::VTSS_QSYS_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_QSYS_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_QSYS_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_QSYS_CM_DATA_RD_CM_DATA_RD(x)  (x)


/**
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a QSYS:COREMEM:CM_OP
 */
#define VTSS_QSYS_CM_OP                      VTSS_IOREG(VTSS_TO_QSYS,0x22b)

/**
 * \brief
 * Ask the memory debug system to read or write a specific location. If no
 * response is received from a memory, due to timeout, or selected address
 * out of range, the state machine can be reset by issuing the 11
 * command.Field will return to 00 upon completion.
 *
 * \details
 * 00: NOP
 * 01: Read from selected address into CM_DATA_RD
 * 10: Write CM_DATA_WR into selected address
 * 11: Reset debug access
 *
 * Field: ::VTSS_QSYS_CM_OP . CM_OP
 */
#define  VTSS_F_QSYS_CM_OP_CM_OP(x)           VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QSYS_CM_OP_CM_OP              VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QSYS_CM_OP_CM_OP(x)           VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_QSYS_H_ */
