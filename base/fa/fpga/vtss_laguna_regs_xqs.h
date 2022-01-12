// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_XQS_H_
#define _VTSS_LAGUNA_REGS_XQS_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a XQS
 *
 * Queue Transfer Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a XQS:SYSTEM
 *
 * Switch configuration
 */


/**
 * \brief Statistics configuration
 *
 * \details
 * Register: \a XQS:SYSTEM:STAT_CNT_CFG
 */
#define VTSS_XQS_STAT_CNT_CFG                VTSS_IOREG(VTSS_TO_XQS,0x55c)

/**
 * \brief
 * When set, a frame discarded due to lack of resources is counted on the
 * egress port instead of the ingress. Side effect is a slower processing
 * of multiple drops on the same frame, causing potential head-of-line
 * blocking.
 *
 * \details
 * Field: ::VTSS_XQS_STAT_CNT_CFG . DROP_COUNT_EGRESS
 */
#define  VTSS_F_XQS_STAT_CNT_CFG_DROP_COUNT_EGRESS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_STAT_CNT_CFG_DROP_COUNT_EGRESS  VTSS_BIT(0)
#define  VTSS_X_XQS_STAT_CNT_CFG_DROP_COUNT_EGRESS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Index into large tables
 *
 * \details
 * Register: \a XQS:SYSTEM:MAP_CFG_CFG
 */
#define VTSS_XQS_MAP_CFG_CFG                 VTSS_IOREG(VTSS_TO_XQS,0x55d)

/**
 * \brief
 * This value is used for indexing into the QMAP_VPORT_TBL, QMAP_QOS_TBL,
 * QMAP_SE_TBL, and QLIMIT_QUEUE tables.
 *
 * \details
 * Field: ::VTSS_XQS_MAP_CFG_CFG . MAP_CFG_CFG
 */
#define  VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(x)  (x)
#define  VTSS_M_XQS_MAP_CFG_CFG_MAP_CFG_CFG     0xffffffff
#define  VTSS_X_XQS_MAP_CFG_CFG_MAP_CFG_CFG(x)  (x)


/**
 * \brief Forwarder mischeleaneous configuration
 *
 * \details
 * Register: \a XQS:SYSTEM:FWD_CTRL
 */
#define VTSS_XQS_FWD_CTRL                    VTSS_IOREG(VTSS_TO_XQS,0x55e)

/**
 * \brief
 * The maximum number of clock cycles between guaranteed CSR access to
 * res_stat counters.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_CTRL . FWD_IDLE_CNT
 */
#define  VTSS_F_XQS_FWD_CTRL_FWD_IDLE_CNT(x)  VTSS_ENCODE_BITFIELD(x,5,13)
#define  VTSS_M_XQS_FWD_CTRL_FWD_IDLE_CNT     VTSS_ENCODE_BITMASK(5,13)
#define  VTSS_X_XQS_FWD_CTRL_FWD_IDLE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,5,13)

/**
 * \brief
 * When the queue update fifo length exceeds this value, the copy generator
 * is slowed down.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_CTRL . FWD_SLOWDOWN_WM
 */
#define  VTSS_F_XQS_FWD_CTRL_FWD_SLOWDOWN_WM(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_XQS_FWD_CTRL_FWD_SLOWDOWN_WM     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_XQS_FWD_CTRL_FWD_SLOWDOWN_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief QS drop events per port and copy type
 *
 * \details
 * Register: \a XQS:SYSTEM:FWD_DROP_EVENTS
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_XQS_FWD_DROP_EVENTS(ri)         VTSS_IOREG(VTSS_TO_XQS,0x55f + (ri))

/**
 * \brief
 * A switched frame copy was cancelled to one or more egress ports.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_DROP_EVENTS . FWD_DROP_NORM_STICKY
 */
#define  VTSS_F_XQS_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XQS_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY  VTSS_BIT(4)
#define  VTSS_X_XQS_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * A CPU directed frame copy was cancelled.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_DROP_EVENTS . FWD_DROP_CPU_STICKY
 */
#define  VTSS_F_XQS_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XQS_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY  VTSS_BIT(3)
#define  VTSS_X_XQS_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * A learnall frame copy was cancelled.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_DROP_EVENTS . FWD_DROP_LEARN_STICKY
 */
#define  VTSS_F_XQS_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XQS_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY  VTSS_BIT(2)
#define  VTSS_X_XQS_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * A mirror copy was cancelled.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_DROP_EVENTS . FWD_DROP_MIRR_STICKY
 */
#define  VTSS_F_XQS_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XQS_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY  VTSS_BIT(1)
#define  VTSS_X_XQS_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * A frame copy was discarded due to a queuemapping violation.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_DROP_EVENTS . FWD_DROP_QMAP_STICKY
 */
#define  VTSS_F_XQS_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY  VTSS_BIT(0)
#define  VTSS_X_XQS_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Counters showing forwarding runs. Debugging purposes only
 *
 * \details
 * Five counters exists in the forwarding engine:
 * 0:  Cycles lost due to EQC backpressure
 * 1:  Cycles lost due to statistics backpressure
 * 2: SOF processings (cut through)
 * 3: EOF processings (cut through)
 * 4: SOF+EOF processings( store and forward)

 *
 * Register: \a XQS:SYSTEM:FWD_STAT_CNT
 *
 * @param ri Register: FWD_STAT_CNT (??), 0-4
 */
#define VTSS_XQS_FWD_STAT_CNT(ri)            VTSS_IOREG(VTSS_TO_XQS,0x582 + (ri))

/**
 * \brief
 * Counts number of forwarding events since chip reset.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_STAT_CNT . FWD_STAT_CNT
 */
#define  VTSS_F_XQS_FWD_STAT_CNT_FWD_STAT_CNT(x)  (x)
#define  VTSS_M_XQS_FWD_STAT_CNT_FWD_STAT_CNT     0xffffffff
#define  VTSS_X_XQS_FWD_STAT_CNT_FWD_STAT_CNT(x)  (x)


/**
 * \brief Counter for number of frames discarded towards the CPU
 *
 * \details
 * Register: \a XQS:SYSTEM:FWD_CPU_DROP_CNT
 */
#define VTSS_XQS_FWD_CPU_DROP_CNT            VTSS_IOREG(VTSS_TO_XQS,0x587)

/**
 * \brief
 * Counts number of frames discarded towards the CPU, since queue system
 * reset.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_CPU_DROP_CNT . FWD_CPU_DROP_CNT
 */
#define  VTSS_F_XQS_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT(x)  (x)
#define  VTSS_M_XQS_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT     0xffffffff
#define  VTSS_X_XQS_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT(x)  (x)


/**
 * \brief Cut through settings
 *
 * \details
 * Enable cut through forwarding for the port.
 *
 * Register: \a XQS:SYSTEM:FWD_CT_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-29
 */
#define VTSS_XQS_FWD_CT_CFG(ri)              VTSS_IOREG(VTSS_TO_XQS,0x588 + (ri))

/**
 * \brief
 * Ingress speed of frames coming from the port, used for selecting between
 * store and forward queing and cut-through queuing.If the ingress speed is
 * lower than the egress speed, the frame is enqueued at end of frame,
 * otherwise at start of frame.Egress speed is selected by
 * XQS:QMAP_SE_TBL:QMAP_CT_ESP and XQS::FWD_CT_CFG.FWD_CT_ESP.
 *
 * \details
 * 0: Lowest speed
 * ...
 * 7: Highest speed
 *
 * Field: ::VTSS_XQS_FWD_CT_CFG . FWD_CT_ISP
 */
#define  VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ISP(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ISP     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_XQS_FWD_CT_CFG_FWD_CT_ISP(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * Egress speed of frames being transmitted to the port, used for selecting
 * between store and forward queing and cut-through queuing.Egress speed is
 * selected as the highest of XQS:QMAP_SE_TBL:QMAP_CT_ESP and this field.
 *
 * \details
 * 0: Lowest speed
 * ...
 * 7: Highest speed
 *
 * Field: ::VTSS_XQS_FWD_CT_CFG . FWD_CT_ESP
 */
#define  VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ESP(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ESP     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_XQS_FWD_CT_CFG_FWD_CT_ESP(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Cut through enable mask per scheduling QoS level. A frame will only be
 * eligible for cut-through forwarding, if the QoS class is enabled in this
 * mask.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_CT_CFG . FWD_CT_ENA
 */
#define  VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ENA(x)  VTSS_ENCODE_BITFIELD(x,7,8)
#define  VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ENA     VTSS_ENCODE_BITMASK(7,8)
#define  VTSS_X_XQS_FWD_CT_CFG_FWD_CT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,8)

/**
 * \brief
 * Number of cells to resource allocate at start of frame. Actual
 * consumption will be adjusted at end of frame.
 *
 * \details
 * Field: ::VTSS_XQS_FWD_CT_CFG . PREALLOC_CT_LEN
 */
#define  VTSS_F_XQS_FWD_CT_CFG_PREALLOC_CT_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_XQS_FWD_CT_CFG_PREALLOC_CT_LEN     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_XQS_FWD_CT_CFG_PREALLOC_CT_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Basic port mode for scheduling hierarchy of front ports
 *
 * \details
 * All ports have their own scheduling hierarchy defined, consisting of a
 * part for nonservice frames defined as frames having queing group
 * classified to 0, and a part for the rest. The two parts can be
 * identical if needed, in which case the modes for service and non service
 * must have the same setting.
 *
 * Register: \a XQS:SYSTEM:QMAP_PORT_MODE
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_XQS_QMAP_PORT_MODE(ri)          VTSS_IOREG(VTSS_TO_XQS,0x5a6 + (ri))

/**
 * \brief
 * Scheduling mode for frames classified to queing group /=0 (service
 * frames). QoS level for a frame is found by looking up the QoS definition
 * for the vport, in QMAP_QOS_TBL. That value is used to map into a
 * specific scheduling element and queue on it.Normal:	 se    =
 * QMAP_SE_TBL(vport+qos)  inp	 = ingress port numberHier:  se =
 * QMAP_SE_TBL(vport)  inp = qosMbh:  se = QMAP_SE_TBL(vport+qos)  inp=qgrp
 * mod 8In NORMAL mode, the queue number is looked up in the map tables at
 * index 8+qos_value.In GROUP mode, a scheduling element is assigned per
 * queueing group, with 8 queues attached. The queue number is looked up in
 * the tables at index qgrp.In MBH mode, the QoS is looked up at index
 * qgrp, and the scheduling index is looked up at index "(grp and not 0xf)
 * + qos_value".Internal ports defaults to Hier mode, and front ports
 * defaults to normal mode
 *
 * \details
 * 0: Normal mode
 * 1: Hier mode
 * 2: Mbh mode
 * 3: Default mode

 *
 * Field: ::VTSS_XQS_QMAP_PORT_MODE . QMAP_MODE_SERVICE
 */
#define  VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * Same function as for QMAP_MODE_SERVICE, except this mode is for qgrp=0
 * frames.
 *
 * \details
 * Field: ::VTSS_XQS_QMAP_PORT_MODE . QMAP_MODE_NONSERVICE
 */
#define  VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Mapping configuration for EACL responses
 *
 * \details
 * Register: \a XQS:SYSTEM:QMAP_EACL
 */
#define VTSS_XQS_QMAP_EACL                   VTSS_IOREG(VTSS_TO_XQS,0x5c9)

/**
 * \brief
 * Configures how the remark EACL action affects color of frame for use by
 * the rewriter.
 *
 * \details
 * 0: IFH.vstax.qos.dp will be left as classified by ingress analyzer
 * 1: IFH.vstax.qos.dp will be set to 1
 *
 * Field: ::VTSS_XQS_QMAP_EACL . QMAP_REMARK_REW
 */
#define  VTSS_F_XQS_QMAP_EACL_QMAP_REMARK_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_XQS_QMAP_EACL_QMAP_REMARK_REW  VTSS_BIT(9)
#define  VTSS_X_XQS_QMAP_EACL_QMAP_REMARK_REW(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Configures how the remark action result from the EACL engine affects
 * frame color in the congestion evaluation.
 *
 * \details
 * 0: Frame color is as determined from the ingress analyzer
 * 1: Frame color changed to yellow
 *
 * Field: ::VTSS_XQS_QMAP_EACL . QMAP_REMARK_YELLOW
 */
#define  VTSS_F_XQS_QMAP_EACL_QMAP_REMARK_YELLOW(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_XQS_QMAP_EACL_QMAP_REMARK_YELLOW  VTSS_BIT(8)
#define  VTSS_X_XQS_QMAP_EACL_QMAP_REMARK_YELLOW(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Bitmask defining whether the first or second internal CPU port should be
 * used for EACL requested CPU copies. Bit <n> in mask set to 1 makes CPU
 * copies to CPU queue <n> be forwarded to the second CPU port.
 *
 * \details
 * Field: ::VTSS_XQS_QMAP_EACL . QMAP_CPU_SEL
 */
#define  VTSS_F_XQS_QMAP_EACL_QMAP_CPU_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QMAP_EACL_QMAP_CPU_SEL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QMAP_EACL_QMAP_CPU_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Statistics configuration
 *
 * \details
 * Register: \a XQS:SYSTEM:STAT_CFG
 */
#define VTSS_XQS_STAT_CFG                    VTSS_IOREG(VTSS_TO_XQS,0x5ca)

/**
 * \brief
 * Set STAT_CLEAR_SHOT to clear counters for the port or service index
 * selected by STAT_VIEW. Auto-cleared when complete (1us). Multiple
 * counters can be cleared at the same time by setting multiple bits in
 * STAT_CLEAR_SHOT.
 *
 * \details
 * Bit 0: Clear Rx port counters (Packet, LS byte and MS byte)
 * Bit 1: Clear Tx port counters (Packet, LS byte and MS byte)
 * Bit 2: Clear ingress service counters (Packet, LS byte and MS byte)
 * Bit 3: Clear egress service counters (Packet, LS byte and MS byte)
 *
 * When bits 0-1 are used a port number must be configured in STAT_VIEW.
 * When bits 2 is used an ingress service index must be configured in
 * STAT_VIEW.
 * When bits 3 is used an egress service index must be configured in
 * STAT_VIEW.

 *
 * Field: ::VTSS_XQS_STAT_CFG . STAT_CLEAR_SHOT
 */
#define  VTSS_F_XQS_STAT_CFG_STAT_CLEAR_SHOT(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_XQS_STAT_CFG_STAT_CLEAR_SHOT     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_XQS_STAT_CFG_STAT_CLEAR_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Selects the port or service for which counters can be accessed using
 * XQS:STAT.Also used to select the port or service index for which to
 * clear statistics counters, ref. STAT_CFG.STAT_CLEAR_SHOT.
 *
 * \details
 * Field: ::VTSS_XQS_STAT_CFG . STAT_VIEW
 */
#define  VTSS_F_XQS_STAT_CFG_STAT_VIEW(x)     VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_XQS_STAT_CFG_STAT_VIEW        VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_XQS_STAT_CFG_STAT_VIEW(x)     VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \brief
 * Set to enable use of all of the service counter memory for packet
 * counting.
 *
 * \details
 * Field: ::VTSS_XQS_STAT_CFG . STAT_SRV_PKT_ONLY
 */
#define  VTSS_F_XQS_STAT_CFG_STAT_SRV_PKT_ONLY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_XQS_STAT_CFG_STAT_SRV_PKT_ONLY  VTSS_BIT(4)
#define  VTSS_X_XQS_STAT_CFG_STAT_SRV_PKT_ONLY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Counters are by default wrapping when exceeding their maximum value, and
 * software must thus do a subtraction with the previous readen value to
 * see how much the total count has changed.If wrapping is disabled, the
 * counters will clear on read, and saturate at their maximum value.
 * Software can thus detect that a counter overflow has happened, and do
 * not need storing the previous read values.The configuration exists
 * replicated per statistics group as the STAT_CLEAR_SHOT describes.
 *
 * \details
 * Field: ::VTSS_XQS_STAT_CFG . STAT_WRAP_DIS
 */
#define  VTSS_F_XQS_STAT_CFG_STAT_WRAP_DIS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_XQS_STAT_CFG_STAT_WRAP_DIS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_XQS_STAT_CFG_STAT_WRAP_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Mirroring configuration
 *
 * \details
 * Register: \a XQS:SYSTEM:MIRROR_CFG
 */
#define VTSS_XQS_MIRROR_CFG                  VTSS_IOREG(VTSS_TO_XQS,0x5cb)

/**
 * \brief
 * One bit per mirror probe enabling generation of mirror copies also for
 * frames discarded due to buffer discards.
 *
 * \details
 * Field: ::VTSS_XQS_MIRROR_CFG . MIRROR_DISCARDS
 */
#define  VTSS_F_XQS_MIRROR_CFG_MIRROR_DISCARDS(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_XQS_MIRROR_CFG_MIRROR_DISCARDS     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_XQS_MIRROR_CFG_MIRROR_DISCARDS(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Discard frames destined for specific CPU queues
 *
 * \details
 * Register: \a XQS:SYSTEM:CPUQ_DISCARD
 */
#define VTSS_XQS_CPUQ_DISCARD                VTSS_IOREG(VTSS_TO_XQS,0x5cc)

/**
 * \brief
 * Disable enqueuing of traffic to specific CPU queues.
 *
 * \details
 * xxxxxxx1: Discard frames to CPU queue 0
 * xxxxxx1x: Discard frames to CPU queue 1
 * ...
 * 1xxxxxxx: Discard frames to CPU queue 7
 *
 * Field: ::VTSS_XQS_CPUQ_DISCARD . CPUQ_DISCARD
 */
#define  VTSS_F_XQS_CPUQ_DISCARD_CPUQ_DISCARD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_CPUQ_DISCARD_CPUQ_DISCARD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_CPUQ_DISCARD_CPUQ_DISCARD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a XQS:QMAP_VPORT_TBL
 *
 * Mapping into virtual ports
 */


/**
 * \brief Mapping into virtual ports
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_VPORT_TBL:QMAP_VPORT_TBL
 *
 * @param gi Register: QMAP_VPORT_TBL (??), 0-3
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_XQS_QMAP_VPORT_TBL(gi,ri)       VTSS_IOREG_IX(VTSS_TO_XQS,0x400,gi,64,ri,0)

/**
 * \brief
 * Maps the indexed (QGRP,DPORT) set into a virtual port number. This
 * number is used by the queue mapping system when determining target queue
 * through QMAP_SE_TBL and QMAP_QOS_TBL.
 *
 * \details
 * Field: ::VTSS_XQS_QMAP_VPORT_TBL . QMAP_VPORT_VAL
 */
#define  VTSS_F_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,11)

/**
 * Register Group: \a XQS:QMAP_SE_TBL
 *
 * Select scheduling modes
 */


/**
 * \brief Per port mapping of qgrp
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_SE_TBL:QMAP_SE_TBL
 *
 * @param gi Register: QMAP_SE_TBL (??), 0-3
 */
#define VTSS_XQS_QMAP_SE_TBL(gi)             VTSS_IOREG_IX(VTSS_TO_XQS,0x550,gi,2,0,0)

/**
 * \brief
 * Scheduling element to use for frames going to the specific port with the
 * specific lookup index
 *
 * \details
 * Field: ::VTSS_XQS_QMAP_SE_TBL . QMAP_SE_VAL
 */
#define  VTSS_F_XQS_QMAP_SE_TBL_QMAP_SE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_XQS_QMAP_SE_TBL_QMAP_SE_VAL     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_XQS_QMAP_SE_TBL_QMAP_SE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Per port mapping of qgrp
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_SE_TBL:QMAP_CT_ESP
 *
 * @param gi Register: QMAP_SE_TBL (??), 0-3
 */
#define VTSS_XQS_QMAP_CT_ESP(gi)             VTSS_IOREG_IX(VTSS_TO_XQS,0x550,gi,2,0,1)

/**
 * \brief
 * Speed of destination port in the mapping.  The highest value of this
 * field and the port default value found in QMAP_CT_ESP will be chosen.
 *
 * \details
 * See FWD_CT_CFG.FWD_CT_ESP

 *
 * Field: ::VTSS_XQS_QMAP_CT_ESP . QMAP_CT_ESP
 */
#define  VTSS_F_XQS_QMAP_CT_ESP_QMAP_CT_ESP(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_XQS_QMAP_CT_ESP_QMAP_CT_ESP     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_XQS_QMAP_CT_ESP_QMAP_CT_ESP(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a XQS:QMAP_QOS_TBL
 *
 * Select scheduling modes
 */


/**
 * \brief Per port mapping of qgrp
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_QOS_TBL:QMAP_QOS_TBL
 *
 * @param gi Register: QMAP_QOS_TBL (??), 0-3
 */
#define VTSS_XQS_QMAP_QOS_TBL(gi)            VTSS_IOREG_IX(VTSS_TO_XQS,0x540,gi,4,0,0)

/**
 * \brief
 * Configures which classified parameter to use when selecting scheduling
 * input.
 *
 * \details
 * 0: Use IPRIO as input selector (SRCP for normal queue mode)
 * 1: Use COSID as input selector
 * 2: Use TC as input selector
 * 3: Use PCP as input selector

 *
 * Field: ::VTSS_XQS_QMAP_QOS_TBL . QMAP_QOS_SEL
 */
#define  VTSS_F_XQS_QMAP_QOS_TBL_QMAP_QOS_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_XQS_QMAP_QOS_TBL_QMAP_QOS_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_XQS_QMAP_QOS_TBL_QMAP_QOS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Per port mapping of qgrp
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_QOS_TBL:QMAP_QOS_SIZE
 *
 * @param gi Register: QMAP_QOS_TBL (??), 0-3
 */
#define VTSS_XQS_QMAP_QOS_SIZE(gi)           VTSS_IOREG_IX(VTSS_TO_XQS,0x540,gi,4,0,1)

/**
 * \brief
 * Configures amount of QoS levels in the queue mapping. Reducing the
 * number of mapped levels to 4 provides the option to share scheduling
 * elements between multiple vports.
 *
 * \details
 * x0: Selected QoS used in mapping
 * 01: Selected QoS mod 4 used in mapping
 * 11: Selected (QoS mod 4)+4 used in mapping

 *
 * Field: ::VTSS_XQS_QMAP_QOS_SIZE . QMAP_QOS_SIZE
 */
#define  VTSS_F_XQS_QMAP_QOS_SIZE_QMAP_QOS_SIZE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_XQS_QMAP_QOS_SIZE_QMAP_QOS_SIZE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_XQS_QMAP_QOS_SIZE_QMAP_QOS_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Per egress port mapping of qgrp to drop stat index
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QMAP_QOS_TBL:DROP_STAT_CTRL
 *
 * @param gi Register: QMAP_QOS_TBL (??), 0-3
 */
#define VTSS_XQS_DROP_STAT_CTRL(gi)          VTSS_IOREG_IX(VTSS_TO_XQS,0x540,gi,4,0,2)

/**
 * \brief
 * Drop counter set base address.
 *
 * \details
 * Field: ::VTSS_XQS_DROP_STAT_CTRL . DROP_STAT_BASE_ADDR
 */
#define  VTSS_F_XQS_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_XQS_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_XQS_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Configures which OAM is counted in the from stat counter.Ref:
 * ANA_L2:ISDX:QGRP_CFG.QGRP_OAM_TYPE
 *
 * \details
 * bit0: Enable / disable drop count of EVC MEP OAM
 * bit1: Enable / disable drop count of OVC / PW MEP OAM
 * bit2: Enable / disable drop count of DOWN MEP OAM
 *
 * Field: ::VTSS_XQS_DROP_STAT_CTRL . DROP_STAT_OAM_CNT_SEL
 */
#define  VTSS_F_XQS_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_XQS_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_XQS_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures which classified parameter to use when selecting drop stat
 * index.
 *
 * \details
 * 0: Use IPRIO as COS input selector
 * 1: Use COSID as COS input selector
 * 2: Use TC as COS input selector
 * 3: Use PCP as COS input selector

 *
 * Field: ::VTSS_XQS_DROP_STAT_CTRL . DROP_STAT_COS_SEL
 */
#define  VTSS_F_XQS_DROP_STAT_CTRL_DROP_STAT_COS_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_XQS_DROP_STAT_CTRL_DROP_STAT_COS_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_XQS_DROP_STAT_CTRL_DROP_STAT_COS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Select the number of counters for this VPORT.
 *
 * \details
 * 0: 4 counters included. QoS x and x+4 shares counter
 * 1: 8 counters included, and two counter sets will be used
 *
 * Field: ::VTSS_XQS_DROP_STAT_CTRL . DROP_STAT_COS8_ENA
 */
#define  VTSS_F_XQS_DROP_STAT_CTRL_DROP_STAT_COS8_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_DROP_STAT_CTRL_DROP_STAT_COS8_ENA  VTSS_BIT(0)
#define  VTSS_X_XQS_DROP_STAT_CTRL_DROP_STAT_COS8_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a XQS:QLIMIT_QUEUE
 *
 * Queue Size Table
 */


/**
 * \brief Current queue size
 *
 * \details
 * This table of registers are indirectly accessed through the MAP_CFG_CFG
 * registers. In order to access table entry N, MAP_CFG_CFG should be set
 * to N, and replication 0 of this table will afterwards be mapped to table
 * entry N.

 *
 * Register: \a XQS:QLIMIT_QUEUE:QUEUE_SIZE
 *
 * @param gi Register: QLIMIT_QUEUE (??), 0-3
 */
#define VTSS_XQS_QUEUE_SIZE(gi)              VTSS_IOREG_IX(VTSS_TO_XQS,0x558,gi,1,0,0)

/**
 * \brief
 * Current size of queue used for queue size limitation
 *
 * \details
 * Field: ::VTSS_XQS_QUEUE_SIZE . QUEUE_SIZE
 */
#define  VTSS_F_XQS_QUEUE_SIZE_QUEUE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_XQS_QUEUE_SIZE_QUEUE_SIZE     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_XQS_QUEUE_SIZE_QUEUE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/**
 * \brief
 * This queue was have had one or more discards due to the queue limitation
 * algorithm
 *
 * \details
 * Field: ::VTSS_XQS_QUEUE_SIZE . QUEUE_KILLED
 */
#define  VTSS_F_XQS_QUEUE_SIZE_QUEUE_KILLED(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XQS_QUEUE_SIZE_QUEUE_KILLED   VTSS_BIT(1)
#define  VTSS_X_XQS_QUEUE_SIZE_QUEUE_KILLED(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Deny all further enqueing to this queue
 *
 * \details
 * Field: ::VTSS_XQS_QUEUE_SIZE . QUEUE_DENY
 */
#define  VTSS_F_XQS_QUEUE_SIZE_QUEUE_DENY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_QUEUE_SIZE_QUEUE_DENY     VTSS_BIT(0)
#define  VTSS_X_XQS_QUEUE_SIZE_QUEUE_DENY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a XQS:QLIMIT_SE
 *
 * SE Size Table
 */


/**
 * \brief Scheduling element configuration
 *
 * \details
 * Register: \a XQS:QLIMIT_SE:QLIMIT_SE_CFG
 *
 * @param gi Register: QLIMIT_SE (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SE_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_XQS,0x500,gi,16,0,0)

/**
 * \brief
 * Set this field to 1, when scheduling element <idx x 8> is enabled for
 * large use.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SE_CFG . SE_LARGE
 */
#define  VTSS_F_XQS_QLIMIT_SE_CFG_SE_LARGE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_QLIMIT_SE_CFG_SE_LARGE    VTSS_BIT(0)
#define  VTSS_X_XQS_QLIMIT_SE_CFG_SE_LARGE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Current use for the scheduling element
 *
 * \details
 * Register: \a XQS:QLIMIT_SE:QLIMIT_SE_USE
 *
 * @param gi Register: QLIMIT_SE (??), 0-3
 * @param ri Replicator: x_GAZ_HSCH_LARGE_RATIO (??), 0-4
 */
#define VTSS_XQS_QLIMIT_SE_USE(gi,ri)        VTSS_IOREG_IX(VTSS_TO_XQS,0x500,gi,16,ri,1)

/**
 * \brief
 * Total use for all queues on the schedulling element
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SE_USE . QLIMIT_SE_USE
 */
#define  VTSS_F_XQS_QLIMIT_SE_USE_QLIMIT_SE_USE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SE_USE_QLIMIT_SE_USE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SE_USE_QLIMIT_SE_USE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current congestion count for the scheduling element
 *
 * \details
 * Register: \a XQS:QLIMIT_SE:QLIMIT_CONG_CNT
 *
 * @param gi Register: QLIMIT_SE (??), 0-3
 * @param ri Replicator: x_GAZ_HSCH_LARGE_RATIO (??), 0-4
 */
#define VTSS_XQS_QLIMIT_CONG_CNT(gi,ri)      VTSS_IOREG_IX(VTSS_TO_XQS,0x500,gi,16,ri,6)

/**
 * \brief
 * Number of congested queues on the scheduling element
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_CONG_CNT . QLIMIT_CONG_CNT
 */
#define  VTSS_F_XQS_QLIMIT_CONG_CNT_QLIMIT_CONG_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_XQS_QLIMIT_CONG_CNT_QLIMIT_CONG_CNT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_XQS_QLIMIT_CONG_CNT_QLIMIT_CONG_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a XQS:QLIMIT_CFG
 *
 * Queue Limitation Configuration
 */


/**
 * \brief Queue Limitation Configuration
 *
 * \details
 * Register: \a XQS:QLIMIT_CFG:QLIMIT_PORT_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-34
 */
#define VTSS_XQS_QLIMIT_PORT_CFG(ri)         VTSS_IOREG(VTSS_TO_XQS,0x5cd + (ri))

/**
 * \brief
 * Index of shared resource to use
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_PORT_CFG . QLIMIT_SHR_VAL
 */
#define  VTSS_F_XQS_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_XQS_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_XQS_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Disable queue limitation for the port. If either queue limitation is
 * disabled for the source port, or for the destination port, the queue
 * limitation algorithm is bypassed.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_PORT_CFG . QLIMIT_IGR_DIS
 */
#define  VTSS_F_XQS_QLIMIT_PORT_CFG_QLIMIT_IGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_XQS_QLIMIT_PORT_CFG_QLIMIT_IGR_DIS  VTSS_BIT(3)
#define  VTSS_X_XQS_QLIMIT_PORT_CFG_QLIMIT_IGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Disable queue limitation for the port. If either queue limitation is
 * disabled for the source port, or for the destination port, the queue
 * limitation algorithm is bypassed.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_PORT_CFG . QLIMIT_EGR_DIS
 */
#define  VTSS_F_XQS_QLIMIT_PORT_CFG_QLIMIT_EGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_XQS_QLIMIT_PORT_CFG_QLIMIT_EGR_DIS  VTSS_BIT(2)
#define  VTSS_X_XQS_QLIMIT_PORT_CFG_QLIMIT_EGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If set, frames from the port will only be added if the queue or
 * scheduling element is uncongested.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_PORT_CFG . QLIMIT_NO_ISHR
 */
#define  VTSS_F_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ISHR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ISHR  VTSS_BIT(1)
#define  VTSS_X_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ISHR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If set, frames to the port will only be added if the queue or scheduling
 * element is uncongested.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_PORT_CFG . QLIMIT_NO_ESHR
 */
#define  VTSS_F_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ESHR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ESHR  VTSS_BIT(0)
#define  VTSS_X_XQS_QLIMIT_PORT_CFG_QLIMIT_NO_ESHR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Queue Limitation Configuration
 *
 * \details
 * Replications are for DP levels 0-3
 *
 * Register: \a XQS:QLIMIT_CFG:QLIMIT_DP_CFG
 *
 * @param ri Register: QLIMIT_DP_CFG (??), 0-3
 */
#define VTSS_XQS_QLIMIT_DP_CFG(ri)           VTSS_IOREG(VTSS_TO_XQS,0x5f0 + (ri))

/**
 * \brief
 * Bit N set in this mask makes DP level N pass data through if its queue
 * filling is less than the QLIMIT_QUE_CONG watermark. Otherwise SEs using
 * more than the fair share will start discarding traffic with the DP
 * level.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_DP_CFG . QLIMIT_DP_RSRV
 */
#define  VTSS_F_XQS_QLIMIT_DP_CFG_QLIMIT_DP_RSRV(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_XQS_QLIMIT_DP_CFG_QLIMIT_DP_RSRV  VTSS_BIT(8)
#define  VTSS_X_XQS_QLIMIT_DP_CFG_QLIMIT_DP_RSRV(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Amount of memory below the dynamic watermark at which all frames of the
 * DP values are to be discarded.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_DP_CFG . QLIMIT_DP_CUT
 */
#define  VTSS_F_XQS_QLIMIT_DP_CFG_QLIMIT_DP_CUT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_DP_CFG_QLIMIT_DP_CUT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_DP_CFG_QLIMIT_DP_CUT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a XQS:QLIMIT_SHR
 *
 * Shared memory pool configuration
 */


/**
 * \brief Maximum size of shared area
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_TOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_TOP_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,0)

/**
 * \brief
 * When total consumption of a shared area exceeds this level, all queues
 * belonging to the area start tail dropping
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_TOP_CFG . QLIMIT_SHR_TOP
 */
#define  VTSS_F_XQS_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Maximum congested size of shared area
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_ATOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_ATOP_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,1)

/**
 * \brief
 * When filling exceeds this level, all active queues start tail dropping.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_ATOP_CFG . QLIMIT_SHR_ATOP
 */
#define  VTSS_F_XQS_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Maximum congested size of shared area
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_CTOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_CTOP_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,2)

/**
 * \brief
 * When filling exceeds this level, all congested queues start tail
 * dropping.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_CTOP_CFG . QLIMIT_SHR_CTOP
 */
#define  VTSS_F_XQS_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Maximum area use before queue limitation kicks in
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_QLIM_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_QLIM_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,3)

/**
 * \brief
 * When filling exceeds this level, all queues are limited in size
 * depending on number of congested queues.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_QLIM_CFG . QLIMIT_SHR_QLIM
 */
#define  VTSS_F_XQS_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Maximum area to distribute between large SE users
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_QDIV_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_QDIV_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,4)

/**
 * \brief
 * This amount can be shared between large SEs. Note: This field MUST be
 * set to the same value as the QLIM_SHR_QLIM is set to.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_QDIV_CFG . QLIMIT_SHR_QDIV
 */
#define  VTSS_F_XQS_QLIMIT_SHR_QDIV_CFG_QLIMIT_SHR_QDIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_QDIV_CFG_QLIMIT_SHR_QDIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_QDIV_CFG_QLIMIT_SHR_QDIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Size of a congested queue
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_QUE_CONG_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_QUE_CONG_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,5)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_QUE_CONG_CFG . QLIMIT_QUE_CONG
 */
#define  VTSS_F_XQS_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_XQS_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_XQS_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief Size of congested SE
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SE_CONG_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SE_CONG_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,6)

/**
 * \brief
 * An SE is regarded congested when its total queue size exceeds this.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SE_CONG_CFG . QLIMIT_SE_CONG
 */
#define  VTSS_F_XQS_QLIMIT_SE_CONG_CFG_QLIMIT_SE_CONG(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_XQS_QLIMIT_SE_CONG_CFG_QLIMIT_SE_CONG     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_XQS_QLIMIT_SE_CONG_CFG_QLIMIT_SE_CONG(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Maximum extra area of to distribute between large SE users
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_QDIVMAX_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_QDIVMAX_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,7)

/**
 * \brief
 * A random extra amount of words to be shared between large SE. The amount
 * is uniform distributed betwen 0 and this field.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_QDIVMAX_CFG . QLIMIT_SHR_QDIVMAX
 */
#define  VTSS_F_XQS_QLIMIT_SHR_QDIVMAX_CFG_QLIMIT_SHR_QDIVMAX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_QDIVMAX_CFG_QLIMIT_SHR_QDIVMAX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_QDIVMAX_CFG_QLIMIT_SHR_QDIVMAX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Size of semi-congested SE
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SE_EIR_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SE_EIR_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,8)

/**
 * \brief
 * An SE is enabling excess information rate if the filling exceeds this
 * level.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SE_EIR_CFG . QLIMIT_SE_EIR
 */
#define  VTSS_F_XQS_QLIMIT_SE_EIR_CFG_QLIMIT_SE_EIR(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_XQS_QLIMIT_SE_EIR_CFG_QLIMIT_SE_EIR     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_XQS_QLIMIT_SE_EIR_CFG_QLIMIT_SE_EIR(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief Current amount of congested scheduling elements in the share
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_CONG_CNT_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_CONG_CNT_STAT(gi)    VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,9)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_CONG_CNT_STAT . QLIMIT_CONG_CNT
 */
#define  VTSS_F_XQS_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_XQS_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_XQS_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Current use of the shared area
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_FILL_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_FILL_STAT(gi)    VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,10)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_FILL_STAT . QLIMIT_SHR_FILL
 */
#define  VTSS_F_XQS_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current per SE watermark
 *
 * \details
 * Register: \a XQS:QLIMIT_SHR:QLIMIT_SHR_WM_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_WM_STAT(gi)      VTSS_IOREG_IX(VTSS_TO_XQS,0x5f4,gi,12,0,11)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_WM_STAT . QLIMIT_SHR_WM
 */
#define  VTSS_F_XQS_QLIMIT_SHR_WM_STAT_QLIMIT_SHR_WM(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_WM_STAT_QLIMIT_SHR_WM     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_WM_STAT_QLIMIT_SHR_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a XQS:QLIMIT_MON
 *
 * Shared memory pool monitoring
 */


/**
 * \brief Monitor configuration
 *
 * \details
 * Replicated for each classified priority
 *
 * Register: \a XQS:QLIMIT_MON:QLIMIT_MON_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_MON_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_XQS,0x624,gi,3,0,0)

/**
 * \brief
 * Clear shared memory pool monitoring statistics.
 *
 * \details
 * Field: ::VTSS_XQS_QLIMIT_MON_CFG . QLIMIT_SHR_MON_CLR
 */
#define  VTSS_F_XQS_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_XQS_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR  VTSS_BIT(0)
#define  VTSS_X_XQS_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Maximum amount of congested scheduling elements in the share
 *
 * \details
 * Register: \a XQS:QLIMIT_MON:QLIMIT_CONG_CNT_MAX_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT(gi)  VTSS_IOREG_IX(VTSS_TO_XQS,0x624,gi,3,0,1)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_CONG_CNT_MAX_STAT . QLIMIT_CONG_CNT_MAX
 */
#define  VTSS_F_XQS_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_XQS_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_XQS_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/**
 * \brief Maximum use of the shared area
 *
 * \details
 * Register: \a XQS:QLIMIT_MON:QLIMIT_SHR_FILL_MAX_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-3
 */
#define VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT(gi)  VTSS_IOREG_IX(VTSS_TO_XQS,0x624,gi,3,0,2)

/**
 * \details
 * Field: ::VTSS_XQS_QLIMIT_SHR_FILL_MAX_STAT . QLIMIT_SHR_FILL_MAX
 */
#define  VTSS_F_XQS_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_XQS_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_XQS_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a XQS:STAT
 *
 * Frame statistics
 */


/**
 * \brief Counter values
 *
 * \details
 * See description for XQS:STAT.
 *
 * Register: \a XQS:STAT:CNT
 *
 * @param gi Register: STAT (??), 0-1023
 */
#define VTSS_XQS_CNT(gi)                     VTSS_IOREG_IX(VTSS_TO_XQS,0x0,gi,1,0,0)

/**
 * \brief
 * Counter value, ref. XQS:STAT.
 *
 * \details
 * Field: ::VTSS_XQS_CNT . CNT
 */
#define  VTSS_F_XQS_CNT_CNT(x)                (x)
#define  VTSS_M_XQS_CNT_CNT                   0xffffffff
#define  VTSS_X_XQS_CNT_CNT(x)                (x)


#endif /* _VTSS_LAGUNA_REGS_XQS_H_ */
