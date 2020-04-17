// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2C_REGS_QSYS_H_
#define _VTSS_JAGUAR2C_REGS_QSYS_H_


#include "vtss_jaguar2c_regs_common.h"

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
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QSYS_SYSTEM_EEE_CFG(ri)         VTSS_IOREG(VTSS_TO_QSYS,0x2 + (ri))

/** 
 * \brief
 * Queues set in this mask activate the egress port immediately when any of
 * the queues have data available.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_EEE_CFG . EEE_FAST_QUEUES
 */
#define  VTSS_F_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Thresholds for delayed EEE queues
 *
 * \details
 * Register: \a QSYS:SYSTEM:EEE_THRES
 */
#define VTSS_QSYS_SYSTEM_EEE_THRES           VTSS_IOREG(VTSS_TO_QSYS,0x3b)

/** 
 * \brief
 * Maximum number of bytes in a queue before egress port is activated. Unit
 * is 60 bytes.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_EEE_THRES . EEE_HIGH_BYTES
 */
#define  VTSS_F_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Maximum number of frames in a queue before the egress port is activated.
 * Unit is 1 frame.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_EEE_THRES . EEE_HIGH_FRAMES
 */
#define  VTSS_F_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


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
 * Register: \a QSYS:SYSTEM:RESET_CFG
 */
#define VTSS_QSYS_SYSTEM_RESET_CFG           VTSS_IOREG(VTSS_TO_QSYS,0x3c)

/** 
 * \brief
 * Switch core is enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_RESET_CFG . CORE_ENA
 */
#define  VTSS_F_QSYS_SYSTEM_RESET_CFG_CORE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_SYSTEM_RESET_CFG_CORE_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_SYSTEM_RESET_CFG_CORE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Packet memory status
 *
 * \details
 * Register: \a QSYS:SYSTEM:PMEM_SIZE
 */
#define VTSS_QSYS_SYSTEM_PMEM_SIZE           VTSS_IOREG(VTSS_TO_QSYS,0x3d)

/** 
 * \brief
 * Must be set before core reset is released. Unit is  bytes.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_PMEM_SIZE . PMEM_SIZE
 */
#define  VTSS_F_QSYS_SYSTEM_PMEM_SIZE_PMEM_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_SYSTEM_PMEM_SIZE_PMEM_SIZE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_SYSTEM_PMEM_SIZE_PMEM_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Frame aging configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:FRM_AGING
 */
#define VTSS_QSYS_SYSTEM_FRM_AGING           VTSS_IOREG(VTSS_TO_QSYS,0x3e)

/** 
 * \brief
 * Frames are aged and removed from the queue system when the frame's age
 * timer becomes two. The frame age timer is increased for all frames
 * whenever the configured time, MAX_AGE,  has passed. 
 * 
 * Effectively, this means that a frame is aged when the frame has waited
 * in the queue system between one or two times the period specified by
 * MAX_AGE.
 * 
 * The periodd configured by MAX_AGE is also termed an "age era".
 * 
 * A value of zero disables frame aging. 
 * 
 * Frame aging related parameters:
 * QSYS:SYSTEM:FRM_AGING.MAX_AGE
 * HSCH:HSCH_MISC:PORT_MODE.AGE_DIS
 * DSM:CFG:BUF_CFG.AGING_ENA
 *
 * \details 
 * 0: Disable frame aging.
 * >=1: Era length in unit of 4us.
 *
 * Field: ::VTSS_QSYS_SYSTEM_FRM_AGING . MAX_AGE
 */
#define  VTSS_F_QSYS_SYSTEM_FRM_AGING_MAX_AGE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_QSYS_SYSTEM_FRM_AGING_MAX_AGE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_QSYS_SYSTEM_FRM_AGING_MAX_AGE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:STAT_CFG
 */
#define VTSS_QSYS_SYSTEM_STAT_CFG            VTSS_IOREG(VTSS_TO_QSYS,0x3f)

/** 
 * \brief
 * Set to disable counting buffer drops (tail) in the designated tail drop
 * counter.
 *  When disabled, the per priority buffer drop counter is used instead.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CFG . STAT_RX_TAILDROP_DIS
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CFG_STAT_RX_TAILDROP_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_SYSTEM_STAT_CFG_STAT_RX_TAILDROP_DIS  VTSS_BIT(0)
#define  VTSS_X_QSYS_SYSTEM_STAT_CFG_STAT_RX_TAILDROP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Map DP values to color
 *
 * \details
 * Register: \a QSYS:SYSTEM:DP_MAP
 */
#define VTSS_QSYS_SYSTEM_DP_MAP              VTSS_IOREG(VTSS_TO_QSYS,0x40)

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
 * Field: ::VTSS_QSYS_SYSTEM_DP_MAP . DP
 */
#define  VTSS_F_QSYS_SYSTEM_DP_MAP_DP(x)      VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_QSYS_SYSTEM_DP_MAP_DP         VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_QSYS_SYSTEM_DP_MAP_DP(x)      VTSS_EXTRACT_BITFIELD(x,0,4)

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
#define VTSS_QSYS_MISC_EVENTS_CORE           VTSS_IOREG(VTSS_TO_QSYS,0x41)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_QSYS_MISC_EVENTS_CORE . EV_FWR
 */
#define  VTSS_F_QSYS_MISC_EVENTS_CORE_EV_FWR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QSYS_MISC_EVENTS_CORE_EV_FWR  VTSS_BIT(3)
#define  VTSS_X_QSYS_MISC_EVENTS_CORE_EV_FWR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Look in the RTL!
 *
 * \details 
 * Field: ::VTSS_QSYS_MISC_EVENTS_CORE . EV_FDC
 */
#define  VTSS_F_QSYS_MISC_EVENTS_CORE_EV_FDC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_QSYS_MISC_EVENTS_CORE_EV_FDC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_QSYS_MISC_EVENTS_CORE_EV_FDC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

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
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QSYS_PAUSE_CFG_PAUSE_CFG(ri)    VTSS_IOREG(VTSS_TO_QSYS,0x42 + (ri))

/** 
 * \brief
 * Start pausing ingress stream when the amount of memory consumed by the
 * port exceeds this watermark. The TOTPAUSE condition must also be met.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_PAUSE_CFG . PAUSE_START
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_ENCODE_BITFIELD(x,13,12)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START     VTSS_ENCODE_BITMASK(13,12)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_EXTRACT_BITFIELD(x,13,12)

/** 
 * \brief
 * Stop pausing ingress stream when the amount of memory consumed by the
 * port is below  this watermark.
 *
 * \details 
 * See RES_CFG.
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_PAUSE_CFG . PAUSE_STOP
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_ENCODE_BITFIELD(x,1,12)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP     VTSS_ENCODE_BITMASK(1,12)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,1,12)

/** 
 * \brief
 * Enable pause feedback to the MAC, allowing transmission of pause frames
 * or HDX collisions to limit ingress data rate.
 *
 * \details 
 * Field: ::VTSS_QSYS_PAUSE_CFG_PAUSE_CFG . PAUSE_ENA
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configure total memory pause condition
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:PAUSE_TOT_CFG
 */
#define VTSS_QSYS_PAUSE_CFG_PAUSE_TOT_CFG    VTSS_IOREG(VTSS_TO_QSYS,0x7b)

/** 
 * \brief
 * Assert TOTPAUSE condition when total memory allocation is above this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_START
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_ENCODE_BITFIELD(x,12,12)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START     VTSS_ENCODE_BITMASK(12,12)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_EXTRACT_BITFIELD(x,12,12)

/** 
 * \brief
 * Deassert TOTPAUSE condition when total memory allocation is below this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_STOP
 */
#define  VTSS_F_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Tail dropping level
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:ATOP
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QSYS_PAUSE_CFG_ATOP(ri)         VTSS_IOREG(VTSS_TO_QSYS,0x7c + (ri))

/** 
 * \brief
 * When a source port consumes more than this level in the packet memory,
 * frames are tail dropped, unconditionally of destination. 
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_ATOP . ATOP
 */
#define  VTSS_F_QSYS_PAUSE_CFG_ATOP_ATOP(x)   VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_PAUSE_CFG_ATOP_ATOP      VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_PAUSE_CFG_ATOP_ATOP(x)   VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Forward pressure level
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:FWD_PRESSURE
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QSYS_PAUSE_CFG_FWD_PRESSURE(ri)  VTSS_IOREG(VTSS_TO_QSYS,0xb5 + (ri))

/** 
 * \brief
 * When ingress queue request count exceeds this level, maximum number of
 * generated frame copies is limited to the FWD_PRESSURE_COPYCNT value. 
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_FWD_PRESSURE . FWD_PRESSURE
 */
#define  VTSS_F_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE(x)  VTSS_ENCODE_BITFIELD(x,3,12)
#define  VTSS_M_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE     VTSS_ENCODE_BITMASK(3,12)
#define  VTSS_X_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE(x)  VTSS_EXTRACT_BITFIELD(x,3,12)

/** 
 * \brief
 * Maximum frame copy count when fwd pressure is activated. 
 *
 * \details 
 * Field: ::VTSS_QSYS_PAUSE_CFG_FWD_PRESSURE . FWD_PRESSURE_COPYCNT
 */
#define  VTSS_F_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE_COPYCNT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE_COPYCNT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_QSYS_PAUSE_CFG_FWD_PRESSURE_FWD_PRESSURE_COPYCNT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Total raw memory use before tail dropping is activated
 *
 * \details
 * Register: \a QSYS:PAUSE_CFG:ATOP_TOT_CFG
 */
#define VTSS_QSYS_PAUSE_CFG_ATOP_TOT_CFG     VTSS_IOREG(VTSS_TO_QSYS,0xee)

/** 
 * \brief
 * Tail dropping is activate on a port when the port use has exceeded the
 * ATOP watermark for the port, and the total memory use has exceeded this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_QSYS_PAUSE_CFG_ATOP_TOT_CFG . ATOP_TOT
 */
#define  VTSS_F_QSYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a QSYS:MMGT
 *
 * Memory manager status
 */


/** 
 * \brief Packet memory status
 *
 * \details
 * Register: \a QSYS:MMGT:MMGT
 */
#define VTSS_QSYS_MMGT_MMGT                  VTSS_IOREG(VTSS_TO_QSYS,0xef)

/** 
 * \brief
 * Number of 6 frames awaiting releasing.
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_MMGT . RELCNT
 */
#define  VTSS_F_QSYS_MMGT_MMGT_RELCNT(x)      VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_QSYS_MMGT_MMGT_RELCNT         VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_QSYS_MMGT_MMGT_RELCNT(x)      VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Number of 6 free memory words.
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_MMGT . FREECNT
 */
#define  VTSS_F_QSYS_MMGT_MMGT_FREECNT(x)     VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_MMGT_MMGT_FREECNT        VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_MMGT_MMGT_FREECNT(x)     VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Packet Memory Status
 *
 * \details
 * Register: \a QSYS:MMGT:MMGT_FAST
 */
#define VTSS_QSYS_MMGT_MMGT_FAST             VTSS_IOREG(VTSS_TO_QSYS,0xf0)

/** 
 * \brief
 * Number of words in the fast pool

 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_MMGT_FAST . FREEVLD
 */
#define  VTSS_F_QSYS_MMGT_MMGT_FAST_FREEVLD(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_QSYS_MMGT_MMGT_FAST_FREEVLD     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_QSYS_MMGT_MMGT_FAST_FREEVLD(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Number of frames awaiting release in the fast pool
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_MMGT_FAST . RELVLD
 */
#define  VTSS_F_QSYS_MMGT_MMGT_FAST_RELVLD(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_QSYS_MMGT_MMGT_FAST_RELVLD     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_QSYS_MMGT_MMGT_FAST_RELVLD(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

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
#define VTSS_QSYS_MMGT_PORT_MMGT_PORT_VIEW   VTSS_IOREG(VTSS_TO_QSYS,0xf1)

/** 
 * \brief
 * Select port to see consumption values for
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_PORT_MMGT_PORT_VIEW . MMGT_PORT_VIEW
 */
#define  VTSS_F_QSYS_MMGT_PORT_MMGT_PORT_VIEW_MMGT_PORT_VIEW(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_QSYS_MMGT_PORT_MMGT_PORT_VIEW_MMGT_PORT_VIEW     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_QSYS_MMGT_PORT_MMGT_PORT_VIEW_MMGT_PORT_VIEW(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Total consumption per ingress port
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_PORT_USE
 */
#define VTSS_QSYS_MMGT_PORT_MMGT_PORT_USE    VTSS_IOREG(VTSS_TO_QSYS,0xf2)

/** 
 * \brief
 * Total consumption per port in the memory manager. Unit is one cell (176
 * bytes).
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_PORT_MMGT_PORT_USE . MMGT_PORT_USE
 */
#define  VTSS_F_QSYS_MMGT_PORT_MMGT_PORT_USE_MMGT_PORT_USE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_MMGT_PORT_MMGT_PORT_USE_MMGT_PORT_USE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_MMGT_PORT_MMGT_PORT_USE_MMGT_PORT_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Ingress queue status
 *
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_IQ_STAT
 */
#define VTSS_QSYS_MMGT_PORT_MMGT_IQ_STAT     VTSS_IOREG(VTSS_TO_QSYS,0xf3)

/** 
 * \brief
 * Number of frame copies pending in the ingress queue
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_PORT_MMGT_IQ_STAT . MMGT_IQ_SIZE
 */
#define  VTSS_F_QSYS_MMGT_PORT_MMGT_IQ_STAT_MMGT_IQ_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_QSYS_MMGT_PORT_MMGT_IQ_STAT_MMGT_IQ_SIZE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_QSYS_MMGT_PORT_MMGT_IQ_STAT_MMGT_IQ_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \details
 * Register: \a QSYS:MMGT_PORT:MMGT_TAILDROP_CNT
 */
#define VTSS_QSYS_MMGT_PORT_MMGT_TAILDROP_CNT  VTSS_IOREG(VTSS_TO_QSYS,0xf4)

/** 
 * \brief
 * Returns the number of buffer drops due to ATOP reached, or lack of free
 * memory. Values returned for the port mapped in MMGT_PORT_VIEW.
 * 
 * Counter wraps when maximum is reached reached.
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_PORT_MMGT_TAILDROP_CNT . MMGT_TAILDROP_CNT
 */
#define  VTSS_F_QSYS_MMGT_PORT_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_MMGT_PORT_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_MMGT_PORT_MMGT_TAILDROP_CNT_MMGT_TAILDROP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a QSYS:CALCFG
 *
 * Not documented
 */


/** 
 * \brief Automatic calendar setup
 *
 * \details
 * These four registers configures the automaric calendar for the next 16
 * ports from 'repl'*16.
 *
 * Register: \a QSYS:CALCFG:CAL_AUTO
 *
 * @param ri Replicator: x_CBC_AUTO_REGS (??), 0-3
 */
#define VTSS_QSYS_CALCFG_CAL_AUTO(ri)        VTSS_IOREG(VTSS_TO_QSYS,0xf5 + (ri))

/** 
 * \brief
 * Per port setting for internal bandwidth for 16 ports. Replication M,
 * Bits 2N+1 and 2N is a two bit value for port M*16+N, encoded as seen
 * below.
 *
 * \details 
 * 00: Port not active
 * 01: Port granted 1Gbps
 * 10: Port granted 2.5Gbps
 * 11: Port granted 10Gbps
 *
 * Field: ::VTSS_QSYS_CALCFG_CAL_AUTO . CAL_AUTO
 */
#define  VTSS_F_QSYS_CALCFG_CAL_AUTO_CAL_AUTO(x)  (x)
#define  VTSS_M_QSYS_CALCFG_CAL_AUTO_CAL_AUTO     0xffffffff
#define  VTSS_X_QSYS_CALCFG_CAL_AUTO_CAL_AUTO(x)  (x)


/** 
 * \brief Manual calendar setup
 *
 * \details
 * Register: \a QSYS:CALCFG:CAL_SEQ
 */
#define VTSS_QSYS_CALCFG_CAL_SEQ             VTSS_IOREG(VTSS_TO_QSYS,0xf9)

/** 
 * \brief
 * Last entry in manual sequence. CAL_SEQ only accessible while calendar is
 * halted.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_SEQ . CAL_SEQ_LEN
 */
#define  VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_LEN(x)  VTSS_ENCODE_BITFIELD(x,13,9)
#define  VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_LEN     VTSS_ENCODE_BITMASK(13,9)
#define  VTSS_X_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_LEN(x)  VTSS_EXTRACT_BITFIELD(x,13,9)

/** 
 * \brief
 * Port to service in the cycle given by the CAL_SEQ_LEN value.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_SEQ . CAL_SEQ_CUR_VAL
 */
#define  VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_CUR_VAL(x)  VTSS_ENCODE_BITFIELD(x,7,6)
#define  VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_CUR_VAL     VTSS_ENCODE_BITMASK(7,6)
#define  VTSS_X_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_CUR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,7,6)

/** 
 * \brief
 * The CAL_SEQ_PGM_VAL is written into the sequence entry CAL_SEQ_LEN.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_SEQ . CAL_SEQ_PGM_VAL
 */
#define  VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_VAL(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_VAL     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * Enable update of the CAL_SEQ.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_SEQ . CAL_SEQ_PGM_ENA
 */
#define  VTSS_F_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_CALCFG_CAL_SEQ_CAL_SEQ_PGM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Calendar configuration
 *
 * \details
 * Register: \a QSYS:CALCFG:CAL_CTRL
 */
#define VTSS_QSYS_CALCFG_CAL_CTRL            VTSS_IOREG(VTSS_TO_QSYS,0xfa)

/** 
 * \brief
 * The internal bus calendars can be set to a predefined port mode
 * (settings 0-3), to an automatic sequence generated by the CAL_AUTO
 * registers, or to a specific sequence programmed through the CAL_SEQ
 * fields. 
 *
 * \details 
 * 0: 48x1G + 2x10G
 * 1:  Reserved
 * 2:  52x1G
 * 3:  8x1G + 24x2.5G
 * 4:  8x1G + 8x2.5G + 4x10G
 * 5:  24x1G + 4x10G
 * 8:  CAL_AUTO port setting 
 * 9:  Sequence program
 * 10: Halt
 *
 * Field: ::VTSS_QSYS_CALCFG_CAL_CTRL . CAL_MODE
 */
#define  VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_MODE     VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_QSYS_CALCFG_CAL_CTRL_CAL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,4)

/** 
 * \brief
 * Configures the time between bus grants to 10g ports, in 0.1 nanosecond
 * unit. Other speeds will be adjusted relative to the 10g setting. Default
 * value of 8 matches the nominal minimum packet time on a 10g port.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_CTRL . CAL_AUTO_GRANT_RATE
 */
#define  VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_GRANT_RATE(x)  VTSS_ENCODE_BITFIELD(x,1,10)
#define  VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_GRANT_RATE     VTSS_ENCODE_BITMASK(1,10)
#define  VTSS_X_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_GRANT_RATE(x)  VTSS_EXTRACT_BITFIELD(x,1,10)

/** 
 * \brief
 * The automatic calendar failed to service all ports.
 *
 * \details 
 * Field: ::VTSS_QSYS_CALCFG_CAL_CTRL . CAL_AUTO_ERROR
 */
#define  VTSS_F_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_ERROR  VTSS_BIT(0)
#define  VTSS_X_QSYS_CALCFG_CAL_CTRL_CAL_AUTO_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_QSYS_RAM_CTRL_RAM_INIT          VTSS_IOREG(VTSS_TO_QSYS,0xfb)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete ( approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_QSYS_RAM_CTRL_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_QSYS_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QSYS_RAM_CTRL_RAM_INIT_RAM_INIT  VTSS_BIT(1)
#define  VTSS_X_QSYS_RAM_CTRL_RAM_INIT_RAM_INIT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Core memory controllers are enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_QSYS_RAM_CTRL_RAM_INIT . RAM_ENA
 */
#define  VTSS_F_QSYS_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QSYS_RAM_CTRL_RAM_INIT_RAM_ENA  VTSS_BIT(0)
#define  VTSS_X_QSYS_RAM_CTRL_RAM_INIT_RAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

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
#define VTSS_QSYS_COREMEM_CM_ADDR            VTSS_IOREG(VTSS_TO_QSYS,0x0)

/** 
 * \brief
 * Refer to cmid.xls in the AS1000, misc_docs folder.
 *
 * \details 
 * Field: ::VTSS_QSYS_COREMEM_CM_ADDR . CM_ID
 */
#define  VTSS_F_QSYS_COREMEM_CM_ADDR_CM_ID(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_QSYS_COREMEM_CM_ADDR_CM_ID     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_QSYS_COREMEM_CM_ADDR_CM_ID(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Address selection within selected core memory (CMID register). Address
 * is automatically advanced at every data access.
 *
 * \details 
 * Field: ::VTSS_QSYS_COREMEM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_QSYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_QSYS_COREMEM_CM_ADDR_CM_ADDR     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_QSYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a QSYS:COREMEM:CM_DATA
 */
#define VTSS_QSYS_COREMEM_CM_DATA            VTSS_IOREG(VTSS_TO_QSYS,0x1)

/** 
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 BIT inspection space.
 *
 * \details 
 * Field: ::VTSS_QSYS_COREMEM_CM_DATA . CM_DATA
 */
#define  VTSS_F_QSYS_COREMEM_CM_DATA_CM_DATA(x)  (x)
#define  VTSS_M_QSYS_COREMEM_CM_DATA_CM_DATA     0xffffffff
#define  VTSS_X_QSYS_COREMEM_CM_DATA_CM_DATA(x)  (x)


#endif /* _VTSS_JAGUAR2C_REGS_QSYS_H_ */
