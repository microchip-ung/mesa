// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVAL_REGS_QSYS_H_
#define _VTSS_SERVAL_REGS_QSYS_H_


#include "vtss_serval_regs_common.h"

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
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per frontport and for each of the two CPU
 * ports (11+12).
 *
 * Register: \a QSYS:SYSTEM:PORT_MODE
 *
 * @param ri Replicator: x_DPORT_CNT (??), 0-12
 */
#define VTSS_QSYS_SYSTEM_PORT_MODE(ri)       VTSS_IOREG(VTSS_TO_QSYS,0x5680 + (ri))

/** 
 * \brief
 * Disable dequeuing from the egress queues. Frames are not discarded, but
 * may become aged when dequeuing is reenabled.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_PORT_MODE . DEQUEUE_DIS
 */
#define  VTSS_F_QSYS_SYSTEM_PORT_MODE_DEQUEUE_DIS  VTSS_BIT(1)

/** 
 * \brief
 * Delay dequeuing from the egress queues. This might be necessary for
 * minimising flow control tails.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_PORT_MODE . DEQUEUE_LATE
 */
#define  VTSS_F_QSYS_SYSTEM_PORT_MODE_DEQUEUE_LATE  VTSS_BIT(0)


/** 
 * \brief Various switch port mode settings
 *
 * \details
 * Register: \a QSYS:SYSTEM:SWITCH_PORT_MODE
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-11
 */
#define VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_QSYS,0x568d + (ri))

/** 
 * \brief
 * Enable port for any frame transfer.
 * Frames to or from a port with PORT_ENA cleared are discarded.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE . PORT_ENA
 */
#define  VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA  VTSS_BIT(13)

/** 
 * \brief
 * When enabled for a port, frames -from- that port are discarded when the
 * controlling watermarks are hit. If disabled - the frame will stay in
 * memory until resources are available. If INGRESS_DROP_MODE or
 * EGRESS_DROP_MODE applies for a frame copy, it will be discared.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE . INGRESS_DROP_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE  VTSS_BIT(9)

/** 
 * \brief
 * When set the MAC sends PRIO pause control frames in the Tx direction
 * when congested.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE . TX_PFC_ENA
 */
#define  VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * When set, a congested priority request pause of all lower priorities as
 * well.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_SWITCH_PORT_MODE . TX_PFC_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_SWITCH_PORT_MODE_TX_PFC_MODE  VTSS_BIT(0)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:STAT_CNT_CFG
 */
#define VTSS_QSYS_SYSTEM_STAT_CNT_CFG        VTSS_IOREG(VTSS_TO_QSYS,0x5699)

/** 
 * \brief
 * Counter mode for the Tx priority counters for green frames
 * (C_TX_GREEN_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CNT_CFG . TX_GREEN_CNT_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_TX_GREEN_CNT_MODE  VTSS_BIT(5)

/** 
 * \brief
 * Counter mode for the Tx priority counters for green frames
 * (C_TX_YELLOW_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CNT_CFG . TX_YELLOW_CNT_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_TX_YELLOW_CNT_MODE  VTSS_BIT(4)

/** 
 * \brief
 * Counter mode for the drop counters for green frames (C_DR_GREEN_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CNT_CFG . DROP_GREEN_CNT_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_DROP_GREEN_CNT_MODE  VTSS_BIT(3)

/** 
 * \brief
 * Counter mode for the drop counters for green frames (C_DR_YELLOW_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CNT_CFG . DROP_YELLOW_CNT_MODE
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_DROP_YELLOW_CNT_MODE  VTSS_BIT(2)

/** 
 * \brief
 * When set, a frame discarded due to lack of resources is counted on the
 * egress port instead of the ingress. Side effect is a slower processing
 * of multiple drops on the same frame, causing potential head-of-line
 * blocking.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_STAT_CNT_CFG . DROP_COUNT_EGRESS
 */
#define  VTSS_F_QSYS_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS  VTSS_BIT(0)


/** 
 * \brief Control Energy Efficient Ethernet operation per front port.
 *
 * \details
 * Register: \a QSYS:SYSTEM:EEE_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-10
 */
#define VTSS_QSYS_SYSTEM_EEE_CFG(ri)         VTSS_IOREG(VTSS_TO_QSYS,0x569a + (ri))

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
#define VTSS_QSYS_SYSTEM_EEE_THRES           VTSS_IOREG(VTSS_TO_QSYS,0x56a5)

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
 * \brief Control shared memory users
 *
 * \details
 * Register: \a QSYS:SYSTEM:IGR_NO_SHARING
 */
#define VTSS_QSYS_SYSTEM_IGR_NO_SHARING      VTSS_IOREG(VTSS_TO_QSYS,0x56a6)

/** 
 * \brief
 * Control whether frames received on the port may use shared resources. If
 * ingress port or queue has reserved memory left to use, frame enqueuing
 * is always allowed.
 *
 * \details 
 * 0: Use shared memory as well
 * 1: Do not use shared memory
 *
 * Field: ::VTSS_QSYS_SYSTEM_IGR_NO_SHARING . IGR_NO_SHARING
 */
#define  VTSS_F_QSYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Control shared memory users
 *
 * \details
 * Register: \a QSYS:SYSTEM:EGR_NO_SHARING
 */
#define VTSS_QSYS_SYSTEM_EGR_NO_SHARING      VTSS_IOREG(VTSS_TO_QSYS,0x56a7)

/** 
 * \brief
 * Control whether frames forwarded to the port may use shared resources.
 * If egress port or queue has reserved memory left to use, frame enqueuing
 * is always allowed.
 *
 * \details 
 * 0: Use shared memory as well
 * 1: Do not use shared memory
 *
 * Field: ::VTSS_QSYS_SYSTEM_EGR_NO_SHARING . EGR_NO_SHARING
 */
#define  VTSS_F_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Various status info per switch port
 *
 * \details
 * Register: \a QSYS:SYSTEM:SW_STATUS
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-11
 */
#define VTSS_QSYS_SYSTEM_SW_STATUS(ri)       VTSS_IOREG(VTSS_TO_QSYS,0x56a8 + (ri))

/** 
 * \brief
 * Status bit per egress queue indicating whether data is ready for
 * transmission.

 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_SW_STATUS . EQ_AVAIL
 */
#define  VTSS_F_QSYS_SYSTEM_SW_STATUS_EQ_AVAIL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_SYSTEM_SW_STATUS_EQ_AVAIL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_SYSTEM_SW_STATUS_EQ_AVAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief External CPU port configuration
 *
 * \details
 * Register: \a QSYS:SYSTEM:EXT_CPU_CFG
 */
#define VTSS_QSYS_SYSTEM_EXT_CPU_CFG         VTSS_IOREG(VTSS_TO_QSYS,0x56b4)

/** 
 * \brief
 * Select the port to use as the external CPU port.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_EXT_CPU_CFG . EXT_CPU_PORT
 */
#define  VTSS_F_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Frames destined for a CPU extraction queue set in this mask are sent to
 * the external CPU defined by EXT_CPU_PORT instead of the internal CPU.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_EXT_CPU_CFG . EXT_CPUQ_MSK
 */
#define  VTSS_F_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Map CPU extraction queues to CPU ports
 *
 * \details
 * Register: \a QSYS:SYSTEM:CPU_GROUP_MAP
 */
#define VTSS_QSYS_SYSTEM_CPU_GROUP_MAP       VTSS_IOREG(VTSS_TO_QSYS,0x56b6)

/** 
 * \brief
 * Map the 8 CPU extraction queues to the two CPU ports. Bit <n> set to 1
 * directs CPU extraction queue <n> to CPU port 12. Bit <n> set to 0
 * directs CPU extraction queue <n> to CPU port 11.
 *
 * \details 
 * Field: ::VTSS_QSYS_SYSTEM_CPU_GROUP_MAP . CPU_GROUP_MAP
 */
#define  VTSS_F_QSYS_SYSTEM_CPU_GROUP_MAP_CPU_GROUP_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_SYSTEM_CPU_GROUP_MAP_CPU_GROUP_MAP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_SYSTEM_CPU_GROUP_MAP_CPU_GROUP_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a QSYS:QMAP
 *
 * Mapping frames to scheduling elements
 */


/** 
 * \brief Mapping frames to scheduling elements per egress port
 *
 * \details
 * Register: \a QSYS:QMAP:QMAP
 *
 * @param gi Replicator: x_DPORT_CNT (??), 0-12
 */
#define VTSS_QSYS_QMAP_QMAP(gi)              VTSS_IOREG_IX(VTSS_TO_QSYS,0x56b7,gi,1,0,0)

/** 
 * \brief
 * Base index of scheduling elements associated with the egress port.
 * 
 * Scheduling element number = SE_BASE + SE_IDX_SEL.
 * Input port number on scheduling element = SE_INP_SEL.
 * 
 * Example:
 * SE_BASE = 0, SE_IDX_SEL = 0 (ingress port), and SE_INP_SEL = 1 (QoS
 * class).
 * Scheduling elements 0, 1, ..., 11 are assigned to the egress port. For a
 * frame received on port 5 and classified to QoS class 2, input port 2 on
 * scheduling element 5 is selected for the frame.
 * 
 * Note that the highest indexable scheduling element number is 217 and the
 * highest indexable input port number is 11.
 * 
 * Default:
 * When SE_IDX_SEL=0, a default configuration overrules other configured
 * values in QMAP. In this configuration, 1st level scheduling towards the
 * egress queues operates at the QoS class, and 2nd level towards the
 * egress port operates at the source port. SE_BASE is automaticaly set to
 * 8 times the egress port number.
 *
 * \details 
 * Field: ::VTSS_QSYS_QMAP_QMAP . SE_BASE
 */
#define  VTSS_F_QSYS_QMAP_QMAP_SE_BASE(x)     VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_QSYS_QMAP_QMAP_SE_BASE        VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_QSYS_QMAP_QMAP_SE_BASE(x)     VTSS_EXTRACT_BITFIELD(x,5,8)

/** 
 * \brief
 * Scheduling element selector for the egress port. The egress port use the
 * scheduling elements selected by SE_BASE + SE_IDX_SEL. See SE_BASE.
 *
 * \details 
 * 000: Default configuration for port schedulling
 * 001: One level queueing. Only one scheduling element in use.
 * 010: Reserved
 * 011: Reserved
 * 100: Add the frame's ingress port to SE_BASE to select scheduling
 * element.
 * 101: Add the frame's QoS class to SE_BASE to select the scheduling
 * element.
 * 110: Add the frame's service group to SE_BASE to select the scheduling
 * element.
 * 111: Add the frame's service group modulus 16 to SE_BASE to select the
 * scheduling element.

 *
 * Field: ::VTSS_QSYS_QMAP_QMAP . SE_IDX_SEL
 */
#define  VTSS_F_QSYS_QMAP_QMAP_SE_IDX_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_QSYS_QMAP_QMAP_SE_IDX_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_QSYS_QMAP_QMAP_SE_IDX_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Select the input port on the scheduling element selected by SE_BASE and
 * SE_IDX_SEL. See SE_BASE.
 *
 * \details 
 * 00: Use the frame's ingress port as input port number on the scheduling
 * element.
 * 01: Use the frame's QoS class as input port number on the scheduling
 * element.
 * 10: Use the frame's service group as input port number on the scheduling
 * element.
 * 11: Use the frame's service group modulus 16 as input port number on the
 * scheduling element.
 *
 * Field: ::VTSS_QSYS_QMAP_QMAP . SE_INP_SEL
 */
#define  VTSS_F_QSYS_QMAP_QMAP_SE_INP_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QSYS_QMAP_QMAP_SE_INP_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QSYS_QMAP_QMAP_SE_INP_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a QSYS:SGRP
 *
 * Not documented
 */


/** 
 * \brief Configures service group per ISDX
 *
 * \details
 * Register: \a QSYS:SGRP:ISDX_SGRP
 *
 * @param gi Replicator: x_ISDX_CNT (??), 0-1023
 */
#define VTSS_QSYS_SGRP_ISDX_SGRP(gi)         VTSS_IOREG_IX(VTSS_TO_QSYS,0x6000,gi,1,0,0)

/** 
 * \brief
 * Service group value used in the egress scheduler. The service group
 * enables per service egress scheduling as the service group selects which
 * set of egress queues to use. See QSYS::QMAP for more details.
 *
 * \details 
 * Field: ::VTSS_QSYS_SGRP_ISDX_SGRP . ISDX_SGRP
 */
#define  VTSS_F_QSYS_SGRP_ISDX_SGRP_ISDX_SGRP(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_QSYS_SGRP_ISDX_SGRP_ISDX_SGRP     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_QSYS_SGRP_ISDX_SGRP_ISDX_SGRP(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a QSYS:TIMED_FRAME_DB
 *
 * Not documented
 */


/** 
 * \brief Timed frame descriptor
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_DB:TIMED_FRAME_ENTRY
 *
 * @param gi Replicator: x_TFRM_CNT (??), 0-1023
 */
#define VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY(gi)  VTSS_IOREG_IX(VTSS_TO_QSYS,0x6400,gi,1,0,0)

/** 
 * \brief
 * Entry is valid
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY . TFRM_VLD
 */
#define  VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_VLD  VTSS_BIT(23)

/** 
 * \brief
 * Reference to frame descriptor for timed frame
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY . TFRM_FP
 */
#define  VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_FP(x)  VTSS_ENCODE_BITFIELD(x,8,15)
#define  VTSS_M_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_FP     VTSS_ENCODE_BITMASK(8,15)
#define  VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_FP(x)  VTSS_EXTRACT_BITFIELD(x,8,15)

/** 
 * \brief
 * Port number to which the frame should be transmitted.
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY . TFRM_PORTNO
 */
#define  VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_PORTNO(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_PORTNO     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_PORTNO(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Selected timer for this entry (8 timers available)
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY . TFRM_TM_SEL
 */
#define  VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_SEL     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Toggles when delivered to frame reader
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY . TFRM_TM_T
 */
#define  VTSS_F_QSYS_TIMED_FRAME_DB_TIMED_FRAME_ENTRY_TFRM_TM_T  VTSS_BIT(0)

/**
 * Register Group: \a QSYS:TIMED_FRAME_CFG
 *
 * Not documented
 */


/** 
 * \brief Timed frame configuration
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_MISC
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC  VTSS_IOREG(VTSS_TO_QSYS,0x56c4)

/** 
 * \brief
 * Specify slot of timed frame to cancel
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC . TIMED_CANCEL_SLOT
 */
#define  VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_SLOT(x)  VTSS_ENCODE_BITFIELD(x,9,10)
#define  VTSS_M_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_SLOT     VTSS_ENCODE_BITMASK(9,10)
#define  VTSS_X_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_SLOT(x)  VTSS_EXTRACT_BITFIELD(x,9,10)

/** 
 * \brief
 * Set this field to cancel a timed transmission. Auto cleared when
 * complete.
 *
 * \details 
 * Field: ::VTSS_QSYS_TIMED_FRAME_CFG_TFRM_MISC . TIMED_CANCEL_1SHOT
 */
#define  VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_MISC_TIMED_CANCEL_1SHOT  VTSS_BIT(8)


/** 
 * \brief Interleaved transmission setup
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_PORT_DLY
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_PORT_DLY  VTSS_IOREG(VTSS_TO_QSYS,0x56c5)

/** 
 * \brief
 * When multiple timed frames are ready for transmission at the same time,
 * they are by default transmitted as fast as they can, resulting in a
 * burst of frames. By enabling the interleave mode, timer 8 must run out
 * between each frame being transmitted on a port.
 *
 * \details 
 * 0: Send frames in burst
 * 1: Send frames interleaved
 *
 * Field: ::VTSS_QSYS_TIMED_FRAME_CFG_TFRM_PORT_DLY . TFRM_PORT_DLY_ENA
 */
#define  VTSS_F_QSYS_TIMED_FRAME_CFG_TFRM_PORT_DLY_TFRM_PORT_DLY_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QSYS_TIMED_FRAME_CFG_TFRM_PORT_DLY_TFRM_PORT_DLY_ENA     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QSYS_TIMED_FRAME_CFG_TFRM_PORT_DLY_TFRM_PORT_DLY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_1
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_1  VTSS_IOREG(VTSS_TO_QSYS,0x56c6)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_2
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_2  VTSS_IOREG(VTSS_TO_QSYS,0x56c7)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_3
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_3  VTSS_IOREG(VTSS_TO_QSYS,0x56c8)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_4
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_4  VTSS_IOREG(VTSS_TO_QSYS,0x56c9)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_5
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_5  VTSS_IOREG(VTSS_TO_QSYS,0x56ca)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_6
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_6  VTSS_IOREG(VTSS_TO_QSYS,0x56cb)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_7
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_7  VTSS_IOREG(VTSS_TO_QSYS,0x56cc)


/** 
 * \brief Configures timers for timed transmissions
 *
 * \details
 * Register: \a QSYS:TIMED_FRAME_CFG:TFRM_TIMER_CFG_8
 */
#define VTSS_QSYS_TIMED_FRAME_CFG_TFRM_TIMER_CFG_8  VTSS_IOREG(VTSS_TO_QSYS,0x56cd)

/**
 * Register Group: \a QSYS:RES_QOS_ADV
 *
 * Not documented
 */


/** 
 * \brief Random Early Discard (RED) configuration
 *
 * \details
 * Configuration of Random Early Discard (RED) profile per QoS class per
 * drop precedence level. Profiles 0-7 are for frames with QoS class 0-7
 * and drop precedence level 0. Profiles 8-15 are for frames with QoS class
 * 0-7 and drop precedence level 1.
 *
 * Register: \a QSYS:RES_QOS_ADV:RED_PROFILE
 *
 * @param ri Register: RED_PROFILE (??), 0-15
 */
#define VTSS_QSYS_RES_QOS_ADV_RED_PROFILE(ri)  VTSS_IOREG(VTSS_TO_QSYS,0x56ce + (ri))

/** 
 * \brief
 * When enqueuing a frame, RED is active if the ingress memory consumption
 * by the frame's QoS class is above WM_RED_LEVEL. The probability of
 * random early discarding is calculated as: (Memory consumption by the
 * frame's QoS class - WM_RED_LOW)/(WM_RED_HIGH - WM_RED_LOW).
 * Unit is 960 bytes.
 *
 * \details 
 * Field: ::VTSS_QSYS_RES_QOS_ADV_RED_PROFILE . WM_RED_LOW
 */
#define  VTSS_F_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_LOW(x)  VTSS_ENCODE_BITFIELD(x,11,11)
#define  VTSS_M_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_LOW     VTSS_ENCODE_BITMASK(11,11)
#define  VTSS_X_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_LOW(x)  VTSS_EXTRACT_BITFIELD(x,11,11)

/** 
 * \brief
 * See WM_RED_LOW. Unit is 960 bytes.
 *
 * \details 
 * Field: ::VTSS_QSYS_RES_QOS_ADV_RED_PROFILE . WM_RED_HIGH
 */
#define  VTSS_F_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_HIGH     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_QSYS_RES_QOS_ADV_RED_PROFILE_WM_RED_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Shared QOS resource mode
 *
 * \details
 * Register: \a QSYS:RES_QOS_ADV:RES_QOS_MODE
 */
#define VTSS_QSYS_RES_QOS_ADV_RES_QOS_MODE   VTSS_IOREG(VTSS_TO_QSYS,0x56de)

/** 
 * \brief
 * When a qos class is enabled in this mask, the class will have guaranteed
 * shared space. The watermarks found in RES_CFG are used for setting the
 * amount of space set aside.
 *
 * \details 
 * Field: ::VTSS_QSYS_RES_QOS_ADV_RES_QOS_MODE . RES_QOS_RSRVD
 */
#define  VTSS_F_QSYS_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QSYS_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QSYS_RES_QOS_ADV_RES_QOS_MODE_RES_QOS_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a QSYS:RES_CTRL
 *
 * Watermarks and status for egress queue system
 */


/** 
 * \brief Watermark configuration
 *
 * \details
 * The queue system tracks four resource consumptions:
 * Resource 0: Memory tracked per source
 * Resource 1: Frame references tracked per source
 * Resource 2: Memory tracked per destination
 * Resource 3: Frame references tracked per destination
 * 
 * Before a frame is added to the queue system, some conditions must be
 * met:
 * - Reserved memory for the specific (SRC, PRIO) or for the specific SRC
 * is available
 * OR
 * - Reserved memory for the specific (DST,PRIO) or for the specific DST is
 * available
 * OR
 * - Shared memory is available
 * 
 * The frame reference resources are checked for availability like the
 * memory resources. Enqueuing of a frame is allowed if both the memory
 * resource check and the frame reference resource check succeed.
 * 
 * The extra resources consumed when enqueuing a frame are first taken from
 * the reserved (SRC,PRIO), next from the reserved SRC, and last from the
 * shared memory area. The same is done for DST. Both memory consumptions
 * and frame reference consumptions are updated.
 * 
 * The register is layed out the following way for source memory (resource
 * 0):
 * Index 0-95: Q_RSRV - Reserved amount for (SRC,PRIO) at index 8*SRC+PRIO
 * Index 216-223: PRIO_SHR - Maximum allowed use of the shared buffer for
 * PRIO at index PRIO+216
 * Index 224-235: P_RSRV - Reserved amount for SRC at index SRC+224.
 * Index 254: COL_SHR - Maximum allowed use of the shared buffer for frames
 * with DP=1.
 * Index 255: COL_SHR Maximum allowed use of the shared buffer for source.
 * 
 * The layout is similar for resources 1, 2, and 3. Resource 1 uses indices
 * 256-511, resource 2 uses indices 512-767, and resource 3 uses indices
 * 768-1023.
 * 
 * The allocation size for memory tracking is 60 bytes. All frames are
 * prepended with a 16-byte header.
 *
 * Register: \a QSYS:RES_CTRL:RES_CFG
 *
 * @param gi Register: RES_CTRL (??), 0-1023
 */
#define VTSS_QSYS_RES_CTRL_RES_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_QSYS,0x5800,gi,2,0,0)

/** 
 * \brief
 * Watermark for resource.
 * Note, the default value depends on the index. Refer to the congestion
 * scheme documentation for details.
 *
 * \details 
 * Bit 10:   Unit; 0:1, 1:16
 * Bits 9-0: Value to be multiplied with unit

 *
 * Field: ::VTSS_QSYS_RES_CTRL_RES_CFG . WM_HIGH
 */
#define  VTSS_F_QSYS_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_RES_CTRL_RES_CFG_WM_HIGH     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Resource status
 *
 * \details
 * Register: \a QSYS:RES_CTRL:RES_STAT
 *
 * @param gi Register: RES_CTRL (??), 0-1023
 */
#define VTSS_QSYS_RES_CTRL_RES_STAT(gi)      VTSS_IOREG_IX(VTSS_TO_QSYS,0x5800,gi,2,0,1)

/** 
 * \brief
 * Current consumption for corresponding watermark in RES_CFG.
 *
 * \details 
 * Field: ::VTSS_QSYS_RES_CTRL_RES_STAT . INUSE
 */
#define  VTSS_F_QSYS_RES_CTRL_RES_STAT_INUSE(x)  VTSS_ENCODE_BITFIELD(x,15,15)
#define  VTSS_M_QSYS_RES_CTRL_RES_STAT_INUSE     VTSS_ENCODE_BITMASK(15,15)
#define  VTSS_X_QSYS_RES_CTRL_RES_STAT_INUSE(x)  VTSS_EXTRACT_BITFIELD(x,15,15)

/** 
 * \brief
 * Maximum consumption since last read for corresponding watermark in
 * RES_CFG.
 *
 * \details 
 * Field: ::VTSS_QSYS_RES_CTRL_RES_STAT . MAXUSE
 */
#define  VTSS_F_QSYS_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_QSYS_RES_CTRL_RES_STAT_MAXUSE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_QSYS_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a QSYS:DROP_CFG
 *
 * Watermarks for egress queue system
 */


/** 
 * \brief Configures egress ports for flowcontrol
 *
 * \details
 * Register: \a QSYS:DROP_CFG:EGR_DROP_MODE
 */
#define VTSS_QSYS_DROP_CFG_EGR_DROP_MODE     VTSS_IOREG(VTSS_TO_QSYS,0x56df)

/** 
 * \brief
 * When enabled for a port, frames -to- that port are discarded when the
 * controlling watermarks are hit. If disabled - the frame will stay in
 * memory until resources are available. If INGRESS_DROP_MODE or
 * EGRESS_DROP_MODE applies for a frame copy, it will be discared.
 *
 * \details 
 * Field: ::VTSS_QSYS_DROP_CFG_EGR_DROP_MODE . EGRESS_DROP_MODE
 */
#define  VTSS_F_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_QSYS_DROP_CFG_EGR_DROP_MODE_EGRESS_DROP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a QSYS:MMGT
 *
 * Memory manager status
 */


/** 
 * \brief Egress queue status
 *
 * \details
 * Register: \a QSYS:MMGT:EQ_CTRL
 */
#define VTSS_QSYS_MMGT_EQ_CTRL               VTSS_IOREG(VTSS_TO_QSYS,0x56e0)

/** 
 * \brief
 * Number of free frame references.
 *
 * \details 
 * Field: ::VTSS_QSYS_MMGT_EQ_CTRL . FP_FREE_CNT
 */
#define  VTSS_F_QSYS_MMGT_EQ_CTRL_FP_FREE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_QSYS_MMGT_EQ_CTRL_FP_FREE_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_QSYS_MMGT_EQ_CTRL_FP_FREE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a QSYS:MISC
 *
 * Miscellaneous
 */

/**
 * Register Group: \a QSYS:HSCH
 *
 * Configuration of scheduling system and shapers
 */


/** 
 * \brief Shaping configuration of the SE
 *
 * \details
 * Register: \a QSYS:HSCH:CIR_CFG
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_CIR_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,0)

/** 
 * \brief
 * Leak rate for this shaper. Unit is 100 kbps.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_QSYS_HSCH_CIR_CFG_CIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,15)
#define  VTSS_M_QSYS_HSCH_CIR_CFG_CIR_RATE     VTSS_ENCODE_BITMASK(6,15)
#define  VTSS_X_QSYS_HSCH_CIR_CFG_CIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,15)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4 kilobytes. The shaper is
 * disabled when CIR_BURST=0.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_QSYS_HSCH_CIR_CFG_CIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_QSYS_HSCH_CIR_CFG_CIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_QSYS_HSCH_CIR_CFG_CIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Excess rate configuration
 *
 * \details
 * Register: \a QSYS:HSCH:EIR_CFG
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_EIR_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,1)

/** 
 * \brief
 * Leak rate for this shaper. Unit is 100 kbps. 
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_EIR_CFG . EIR_RATE
 */
#define  VTSS_F_QSYS_HSCH_EIR_CFG_EIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,7,15)
#define  VTSS_M_QSYS_HSCH_EIR_CFG_EIR_RATE     VTSS_ENCODE_BITMASK(7,15)
#define  VTSS_X_QSYS_HSCH_EIR_CFG_EIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,7,15)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4 kilobytes. The dual leaky
 * bucket shaper operates as a single leaky bucket shaper when EIR_BURST=0. 
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_EIR_CFG . EIR_BURST
 */
#define  VTSS_F_QSYS_HSCH_EIR_CFG_EIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_QSYS_HSCH_EIR_CFG_EIR_BURST     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_QSYS_HSCH_EIR_CFG_EIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * If a frame is scheduled with excess information rate, the frame color
 * can be changed to yellow.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_EIR_CFG . EIR_MARK_ENA
 */
#define  VTSS_F_QSYS_HSCH_EIR_CFG_EIR_MARK_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration of shaper and scheduling algorithm
 *
 * \details
 * Register: \a QSYS:HSCH:SE_CFG
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_SE_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,2)

/** 
 * \brief
 * Number of inputs running with DWRR algorithm, otherwise strict. Strict
 * inputs always have the highest input index.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CFG . SE_DWRR_CNT
 */
#define  VTSS_F_QSYS_HSCH_SE_CFG_SE_DWRR_CNT(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_QSYS_HSCH_SE_CFG_SE_DWRR_CNT     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_QSYS_HSCH_SE_CFG_SE_DWRR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * The DWRR algorithm is replaced with frame-based round robin.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CFG . SE_RR_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_CFG_SE_RR_ENA    VTSS_BIT(5)

/** 
 * \brief
 * Enable AVB mode for this shaper, creating burst capacity only when data
 * is available.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CFG . SE_AVB_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_CFG_SE_AVB_ENA   VTSS_BIT(4)

/** 
 * \brief
 * Accounting mode for this shaper.
 *
 * \details 
 * 0: Line rate. Shape bytes including HSCH_MISC::FRM_ADJ.
 * 1: Data rate. Shape bytes excluding IPG.
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape framed with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_QSYS_HSCH_SE_CFG . SE_FRM_MODE
 */
#define  VTSS_F_QSYS_HSCH_SE_CFG_SE_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_QSYS_HSCH_SE_CFG_SE_FRM_MODE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_QSYS_HSCH_SE_CFG_SE_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Allow bandwidth out of this element to exceed configured levels. Still -
 * arbitrations always prefers inputs not exceeding configured levels.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CFG . SE_EXC_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_CFG_SE_EXC_ENA   VTSS_BIT(1)


/** 
 * \brief Configuration of the DWRR costs
 *
 * \details
 * Register: \a QSYS:HSCH:SE_DWRR_CFG
 *
 * @param gi Register: HSCH (??), 0-691
 * @param ri Register: SE_DWRR_CFG (??), 0-11
 */
#define VTSS_QSYS_HSCH_SE_DWRR_CFG(gi,ri)    VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,ri,3)

/** 
 * \brief
 * DWRR cost configuration
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_DWRR_CFG . DWRR_COST
 */
#define  VTSS_F_QSYS_HSCH_SE_DWRR_CFG_DWRR_COST(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_QSYS_HSCH_SE_DWRR_CFG_DWRR_COST     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_QSYS_HSCH_SE_DWRR_CFG_DWRR_COST(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Configuration of the connections between SEs
 *
 * \details
 * Register: \a QSYS:HSCH:SE_CONNECT
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_SE_CONNECT(gi)        VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,15)

/** 
 * \brief
 * The output port on this SE is connected to the SE selected by
 * SE_OUTP_IDX. SE_OUTP_CON selects the input port number on the SE. If the
 * SE_TERMINAL is set, the output port on this SE is connected to the
 * egress port selected by SE_OUTP_IDX instead.
 * 
 * The connections are automatically configured after reset to a source
 * port fair strict priority scheme:
 * SEs 0-7 connect to  SE 218: Priority scheduler for port 0
 * SEs 8-15 connect to SE 219: Priority scheduler for port 1
 * ...
 * SEs 96-103 connect to SE 230: Priority scheduler for CPU port 12
 * 
 * SEs 218+N connect to egress port N with SE_TERMINAL set.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CONNECT . SE_OUTP_IDX
 */
#define  VTSS_F_QSYS_HSCH_SE_CONNECT_SE_OUTP_IDX(x)  VTSS_ENCODE_BITFIELD(x,17,8)
#define  VTSS_M_QSYS_HSCH_SE_CONNECT_SE_OUTP_IDX     VTSS_ENCODE_BITMASK(17,8)
#define  VTSS_X_QSYS_HSCH_SE_CONNECT_SE_OUTP_IDX(x)  VTSS_EXTRACT_BITFIELD(x,17,8)

/** 
 * \brief
 * The inputs on this SE are the output ports of the consequtive range of
 * SEs starting at index SE_INP_IDX and ending at SE_INP_IDX+SE_INP_CNT-1.
 * The 2616 queues connect 12 at a time to the first 218 SEs, and the
 * SE_INP_IDX does not apply for those.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CONNECT . SE_INP_IDX
 */
#define  VTSS_F_QSYS_HSCH_SE_CONNECT_SE_INP_IDX(x)  VTSS_ENCODE_BITFIELD(x,9,8)
#define  VTSS_M_QSYS_HSCH_SE_CONNECT_SE_INP_IDX     VTSS_ENCODE_BITMASK(9,8)
#define  VTSS_X_QSYS_HSCH_SE_CONNECT_SE_INP_IDX(x)  VTSS_EXTRACT_BITFIELD(x,9,8)

/** 
 * \brief
 * The input port on the next SE, which this SE connects to. The next SE is
 * selected by SE_OUTP_IDX.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CONNECT . SE_OUTP_CON
 */
#define  VTSS_F_QSYS_HSCH_SE_CONNECT_SE_OUTP_CON(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_QSYS_HSCH_SE_CONNECT_SE_OUTP_CON     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_QSYS_HSCH_SE_CONNECT_SE_OUTP_CON(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Number of input ports on to this SE. Default values matches the default
 * scheduling hierarchy described in the datasheet.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CONNECT . SE_INP_CNT
 */
#define  VTSS_F_QSYS_HSCH_SE_CONNECT_SE_INP_CNT(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_QSYS_HSCH_SE_CONNECT_SE_INP_CNT     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_QSYS_HSCH_SE_CONNECT_SE_INP_CNT(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/** 
 * \brief
 * If set, this SE is connected to egress port SE_OUTP_IDX
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_CONNECT . SE_TERMINAL
 */
#define  VTSS_F_QSYS_HSCH_SE_CONNECT_SE_TERMINAL  VTSS_BIT(0)


/** 
 * \brief Configuration of which fill levels in the queue system that the DLB shapers use to trigger excess information rate
 *
 * \details
 * Register: \a QSYS:HSCH:SE_DLB_SENSE
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_SE_DLB_SENSE(gi)      VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,16)

/** 
 * \brief
 * QoS class used when SE_DLB_PRIO_ENA is set.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_PRIO
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_PRIO     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Source port used when SE_DLB_SPORT_ENA is set.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_SPORT
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_SPORT(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_SPORT     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_SPORT(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Destination port used when SE_DLB_DPORT_ENA is set.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_DPORT
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_DPORT     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

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
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_PRIO_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA  VTSS_BIT(2)

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
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_SPORT_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_SPORT_ENA  VTSS_BIT(1)

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
 * Field: ::VTSS_QSYS_HSCH_SE_DLB_SENSE . SE_DLB_DPORT_ENA
 */
#define  VTSS_F_QSYS_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA  VTSS_BIT(0)


/** 
 * \brief CIR status
 *
 * \details
 * Register: \a QSYS:HSCH:CIR_STATE
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_CIR_STATE(gi)         VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,17)

/** 
 * \brief
 * Current fill level. Unit is 0.5 bits.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_QSYS_HSCH_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,4,22)
#define  VTSS_M_QSYS_HSCH_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(4,22)
#define  VTSS_X_QSYS_HSCH_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,4,22)


/** 
 * \brief EIR status
 *
 * \details
 * Register: \a QSYS:HSCH:EIR_STATE
 *
 * @param gi Register: HSCH (??), 0-691
 */
#define VTSS_QSYS_HSCH_EIR_STATE(gi)         VTSS_IOREG_IX(VTSS_TO_QSYS,0x0,gi,32,0,18)

/** 
 * \brief
 * Current fill level. Unit is 0.5 bits.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_EIR_STATE . EIR_LVL
 */
#define  VTSS_F_QSYS_HSCH_EIR_STATE_EIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_QSYS_HSCH_EIR_STATE_EIR_LVL     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_QSYS_HSCH_EIR_STATE_EIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,22)

/**
 * Register Group: \a QSYS:HSCH_MISC
 *
 * Miscellaneous scheduler configuration
 */


/** 
 * \brief Common config for HSCH and policer module
 *
 * \details
 * Register: \a QSYS:HSCH_MISC:HSCH_MISC_CFG
 */
#define VTSS_QSYS_HSCH_MISC_HSCH_MISC_CFG    VTSS_IOREG(VTSS_TO_QSYS,0x56e2)

/** 
 * \brief
 * Set to one when the SE connection configuration is valid. Set to zero
 * when reconfiguring SE inter connections
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_MISC_HSCH_MISC_CFG . SE_CONNECT_VLD
 */
#define  VTSS_F_QSYS_HSCH_MISC_HSCH_MISC_CFG_SE_CONNECT_VLD  VTSS_BIT(7)

/** 
 * \brief
 * Values to add each frame when frame length adjustment is in use.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_MISC_HSCH_MISC_CFG . FRM_ADJ
 */
#define  VTSS_F_QSYS_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_QSYS_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_QSYS_HSCH_MISC_HSCH_MISC_CFG_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * When set closed queue shapers will be schedulled as excessed, and can be
 * schedulled if no other inputs are available.
 *
 * \details 
 * Field: ::VTSS_QSYS_HSCH_MISC_HSCH_MISC_CFG . QSHP_EXC_ENA
 */
#define  VTSS_F_QSYS_HSCH_MISC_HSCH_MISC_CFG_QSHP_EXC_ENA  VTSS_BIT(0)


#endif /* _VTSS_SERVAL_REGS_QSYS_H_ */
