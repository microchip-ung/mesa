// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_SYS_H_
#define _VTSS_LUTON26_REGS_SYS_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SYS
 *
 * Switching Engine Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a SYS:SYSTEM
 *
 * Switch Configuration
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
 * Register: \a SYS:SYSTEM:RESET_CFG
 */
#define VTSS_SYS_SYSTEM_RESET_CFG            VTSS_IOREG(VTSS_TO_SYS,0x206c)

/** 
 * \brief
 * Switch core is enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . CORE_ENA
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_CORE_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Core memory controllers are enabled when this field is set.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . MEM_ENA
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete ( approx. 40 us).
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_RESET_CFG . MEM_INIT
 */
#define  VTSS_F_SYS_SYSTEM_RESET_CFG_MEM_INIT  VTSS_BIT(0)


/** 
 * \brief S-tag Ethernet Type
 *
 * \details
 * Register: \a SYS:SYSTEM:VLAN_ETYPE_CFG
 */
#define VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG       VTSS_IOREG(VTSS_TO_SYS,0x206e)

/** 
 * \brief
 * Custom Ethernet Type for S-tags. Tags with TPID = 0x88A8 are always
 * recognized as S-tags.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_VLAN_ETYPE_CFG . VLAN_S_TAG_ETYPE_VAL
 */
#define  VTSS_F_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SYS_SYSTEM_VLAN_ETYPE_CFG_VLAN_S_TAG_ETYPE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Per device port configuration
 *
 * \details
 * These configurations exists per frontport and for each of the two CPU
 * ports (26+27).
 *
 * Register: \a SYS:SYSTEM:PORT_MODE
 *
 * @param ri Replicator: x_DPORT_CNT (??), 0-27
 */
#define VTSS_SYS_SYSTEM_PORT_MODE(ri)        VTSS_IOREG(VTSS_TO_SYS,0x206f + (ri))

/** 
 * \brief
 * Enable frame analysis on Layer-3 and Layer-4 protocol information. If
 * cleared, all frames are seen as non-IP and are handled accordingly. This
 * affects all blocks using IP information such as classification, TCAM
 * lookups, IP flooding and forwarding, and DSCP rewriting.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . L3_PARSE_CFG
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_L3_PARSE_CFG  VTSS_BIT(2)

/** 
 * \brief
 * Disable dequeuing from the egress queues. Frames are not discarded, but
 * may become aged when dequeuing is re-enabled.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . DEQUEUE_DIS
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_DEQUEUE_DIS  VTSS_BIT(1)

/** 
 * \brief
 * Enable parsing of 64-bit injection header prepended all incoming frames
 * on this port. Numbering MSB of first byte as bit 63, the format is this:
 * 63: BYPASS. If set, the analyzer is bypassed, and the below fields are
 * used instead.
 * 62: PTP 2-step request for this transmission. (stamp must be included in
 * frame)
 * 61: PTP 1-step update of this frame.(stamp must be included in frame)
 * 59: PTP_ID. Two bit PTP ID for 2-step responses.
 * 32: DEST. 27-bit destination selection (per port).
 * 30: RESERVED. Two bits unused.
 * 28: POP_CNT. Two bit pop count (number of tags to be removed before tx).
 * Value 3 forces no rewriting of this frame.
 * 20: CPU_QUEUE. Eight bit queue mask for forwarding to cpu queues.
 * 17: QOS_CLASS. Three bit QoS class value (internal priority)
 * 16: TAG_TYPE. Classified tag type (Service/Custom)
 * 13: PCP. Three bit PCP
 * 12: DEI
 * 0:	VID. 12-bit VID
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_PORT_MODE . INCL_INJ_HDR
 */
#define  VTSS_F_SYS_SYSTEM_PORT_MODE_INCL_INJ_HDR  VTSS_BIT(0)


/** 
 * \brief Various Ethernet port configurations
 *
 * \details
 * Register: \a SYS:SYSTEM:FRONT_PORT_MODE
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-25
 */
#define VTSS_SYS_SYSTEM_FRONT_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_SYS,0x208b + (ri))

/** 
 * \brief
 * Enables the queue system to support the half duplex mode. Must be set
 * for a port when enabled for half-duplex mode (MAC_MODE_ENA.FDX_ENA
 * cleared).
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_FRONT_PORT_MODE . HDX_MODE
 */
#define  VTSS_F_SYS_SYSTEM_FRONT_PORT_MODE_HDX_MODE  VTSS_BIT(0)


/** 
 * \brief Various switch port mode settings
 *
 * \details
 * Register: \a SYS:SYSTEM:SWITCH_PORT_MODE
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_SYS_SYSTEM_SWITCH_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_SYS,0x20a5 + (ri))

/** 
 * \brief
 * Enable port for any frame transfer.
 * Frames to or from a port with PORT_ENA cleared are discarded.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_SWITCH_PORT_MODE . PORT_ENA
 */
#define  VTSS_F_SYS_SYSTEM_SWITCH_PORT_MODE_PORT_ENA  VTSS_BIT(3)


/** 
 * \brief Configure Frame Aging 
 *
 * \details
 * Register: \a SYS:SYSTEM:FRM_AGING
 */
#define VTSS_SYS_SYSTEM_FRM_AGING            VTSS_IOREG(VTSS_TO_SYS,0x20c0)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a SYS:SYSTEM:STAT_CFG
 */
#define VTSS_SYS_SYSTEM_STAT_CFG             VTSS_IOREG(VTSS_TO_SYS,0x20c1)

/** 
 * \brief
 * Counter mode for the Tx priority counters for green frames
 * (CNT_TX_GREEN_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . TX_GREEN_CNT_MODE
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_TX_GREEN_CNT_MODE  VTSS_BIT(10)

/** 
 * \brief
 * Counter mode for the Tx priority counters for green frames
 * (CNT_TX_YELLOW_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . TX_YELLOW_CNT_MODE
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_TX_YELLOW_CNT_MODE  VTSS_BIT(9)

/** 
 * \brief
 * Counter mode for the drop counters for green frames
 * (CNT_DR_GREEN_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . DROP_GREEN_CNT_MODE
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_DROP_GREEN_CNT_MODE  VTSS_BIT(8)

/** 
 * \brief
 * Counter mode for the drop counters for green frames
 * (CNT_DR_YELLOW_PRIO_x)
 *
 * \details 
 * 0: Count octets
 * 1: Count frames
 *
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . DROP_YELLOW_CNT_MODE
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_DROP_YELLOW_CNT_MODE  VTSS_BIT(7)

/** 
 * \brief
 * Select which port to clear counters for.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . STAT_CLEAR_PORT
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_PORT(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_PORT     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_PORT(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/** 
 * \brief
 * Set STAT_CLEAR_SHOT to clear all counters for the port selected by
 * STAT_CLEAR_PORT port. Auto-cleared when complete (1us).
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_STAT_CFG . STAT_CLEAR_SHOT
 */
#define  VTSS_F_SYS_SYSTEM_STAT_CFG_STAT_CLEAR_SHOT  VTSS_BIT(0)


/** 
 * \brief Control Energy Efficient Ethernet operation per front port.
 *
 * \details
 * Register: \a SYS:SYSTEM:EEE_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-25
 */
#define VTSS_SYS_SYSTEM_EEE_CFG(ri)          VTSS_IOREG(VTSS_TO_SYS,0x20c2 + (ri))

/** 
 * \brief
 * Enable EEE operation on the port.
 * 
 * A port enters the low power mode when no egress queues have data ready.
 * 
 * The port is activated when one of the following conditions is true:
 * - A queue has been non-empty for EEE_TIMER_AGE.
 * - A queue has more than EEE_HIGH_FRAMES frames pending.
 * - A queue has more than EEE_HIGH_BYTES bytes pending.
 * - A queue is marked as a fast queue, and has data pending.

 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EEE_CFG . EEE_ENA
 */
#define  VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_ENA    VTSS_BIT(29)

/** 
 * \brief
 * Queues set in this mask activate the egress port immediately when any of
 * the queues have data available.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EEE_CFG . EEE_FAST_QUEUES
 */
#define  VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_ENCODE_BITFIELD(x,21,8)
#define  VTSS_M_SYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES     VTSS_ENCODE_BITMASK(21,8)
#define  VTSS_X_SYS_SYSTEM_EEE_CFG_EEE_FAST_QUEUES(x)  VTSS_EXTRACT_BITFIELD(x,21,8)

/** 
 * \brief
 * Maximum time frames in any queue must wait before the port is activated.
 * The default value corresponds to 48 us.

 *
 * \details 
 * Time = 4**(EEE_TIMER_AGE/16) * (EEE_TIMER_AGE mod 16) microseconds
 *
 * Field: ::VTSS_SYS_SYSTEM_EEE_CFG . EEE_TIMER_AGE
 */
#define  VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_ENCODE_BITFIELD(x,14,7)
#define  VTSS_M_SYS_SYSTEM_EEE_CFG_EEE_TIMER_AGE     VTSS_ENCODE_BITMASK(14,7)
#define  VTSS_X_SYS_SYSTEM_EEE_CFG_EEE_TIMER_AGE(x)  VTSS_EXTRACT_BITFIELD(x,14,7)

/** 
 * \brief
 * Time from the egress port is activated until frame transmission is
 * restarted. Default value corresponds to 16 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_WAKEUP/16) * (EEE_TIMER_WAKEUP mod 16) microseconds
 *
 * Field: ::VTSS_SYS_SYSTEM_EEE_CFG . EEE_TIMER_WAKEUP
 */
#define  VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_SYS_SYSTEM_EEE_CFG_EEE_TIMER_WAKEUP     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_SYS_SYSTEM_EEE_CFG_EEE_TIMER_WAKEUP(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/** 
 * \brief
 * When all queues are empty, the port is kept active until this time has
 * passed. Default value corresponds to 5 us.
 *
 * \details 
 * Time = 4**(EEE_TIMER_HOLDOFF/16) * (EEE_TIMER_HOLDOFF mod 16)
 * microseconds
 *
 * Field: ::VTSS_SYS_SYSTEM_EEE_CFG . EEE_TIMER_HOLDOFF
 */
#define  VTSS_F_SYS_SYSTEM_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SYS_SYSTEM_EEE_CFG_EEE_TIMER_HOLDOFF     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SYS_SYSTEM_EEE_CFG_EEE_TIMER_HOLDOFF(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Thresholds for delayed EEE queues
 *
 * \details
 * Register: \a SYS:SYSTEM:EEE_THRES
 */
#define VTSS_SYS_SYSTEM_EEE_THRES            VTSS_IOREG(VTSS_TO_SYS,0x20dc)

/** 
 * \brief
 * Maximum number of bytes in a queue before egress port is activated. Unit
 * is 48 bytes.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EEE_THRES . EEE_HIGH_BYTES
 */
#define  VTSS_F_SYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SYS_SYSTEM_EEE_THRES_EEE_HIGH_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Maximum number of frames in a queue before the egress port is activated.
 * Unit is 1 frame.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EEE_THRES . EEE_HIGH_FRAMES
 */
#define  VTSS_F_SYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_SYSTEM_EEE_THRES_EEE_HIGH_FRAMES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Control shared memory users
 *
 * \details
 * Register: \a SYS:SYSTEM:IGR_NO_SHARING
 */
#define VTSS_SYS_SYSTEM_IGR_NO_SHARING       VTSS_IOREG(VTSS_TO_SYS,0x20dd)

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
 * Field: ::VTSS_SYS_SYSTEM_IGR_NO_SHARING . IGR_NO_SHARING
 */
#define  VTSS_F_SYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_SYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_SYS_SYSTEM_IGR_NO_SHARING_IGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Control shared memory users
 *
 * \details
 * Register: \a SYS:SYSTEM:EGR_NO_SHARING
 */
#define VTSS_SYS_SYSTEM_EGR_NO_SHARING       VTSS_IOREG(VTSS_TO_SYS,0x20de)

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
 * Field: ::VTSS_SYS_SYSTEM_EGR_NO_SHARING . EGR_NO_SHARING
 */
#define  VTSS_F_SYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_SYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_SYS_SYSTEM_EGR_NO_SHARING_EGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief Various status info per switch port
 *
 * \details
 * Register: \a SYS:SYSTEM:SW_STATUS
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_SYS_SYSTEM_SW_STATUS(ri)        VTSS_IOREG(VTSS_TO_SYS,0x20df + (ri))

/** 
 * \brief
 * Status bit per egress queue indicating whether data is ready for
 * transmission.

 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_SW_STATUS . EQ_AVAIL
 */
#define  VTSS_F_SYS_SYSTEM_SW_STATUS_EQ_AVAIL(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_SYS_SYSTEM_SW_STATUS_EQ_AVAIL     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_SYS_SYSTEM_SW_STATUS_EQ_AVAIL(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/** 
 * \brief
 * Status bit indicating whether port is in low-power-idle due to the LPI
 * algorithm (EEE_CFG). If set, transmissions are held back.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_SW_STATUS . PORT_LPI
 */
#define  VTSS_F_SYS_SYSTEM_SW_STATUS_PORT_LPI  VTSS_BIT(1)

/** 
 * \brief
 * Status bit indicating whether the switch core is instructing the MAC to
 * pause the ingress port.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_SW_STATUS . PORT_RX_PAUSED
 */
#define  VTSS_F_SYS_SYSTEM_SW_STATUS_PORT_RX_PAUSED  VTSS_BIT(0)


/** 
 * \brief Truncate frames in queue
 *
 * \details
 * Register: \a SYS:SYSTEM:EQ_TRUNCATE
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_SYS_SYSTEM_EQ_TRUNCATE(ri)      VTSS_IOREG(VTSS_TO_SYS,0x20fa + (ri))

/** 
 * \brief
 * If a bit is set, frames transmitted from corresponding egress queue are
 * truncated to 92 bytes.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EQ_TRUNCATE . EQ_TRUNCATE
 */
#define  VTSS_F_SYS_SYSTEM_EQ_TRUNCATE_EQ_TRUNCATE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_SYSTEM_EQ_TRUNCATE_EQ_TRUNCATE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_SYSTEM_EQ_TRUNCATE_EQ_TRUNCATE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Precedence for source ports
 *
 * \details
 * Register: \a SYS:SYSTEM:EQ_PREFER_SRC
 */
#define VTSS_SYS_SYSTEM_EQ_PREFER_SRC        VTSS_IOREG(VTSS_TO_SYS,0x2115)

/** 
 * \brief
 * When multiple sources have data in the same priority, ingress ports set
 * in this mask are preferred over ingress ports not set when arbitrating
 * frames from ingress to egress. When multiple ports are set, the
 * arbitration between these ports are round-robin.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EQ_PREFER_SRC . EQ_PREFER_SRC
 */
#define  VTSS_F_SYS_SYSTEM_EQ_PREFER_SRC_EQ_PREFER_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_SYS_SYSTEM_EQ_PREFER_SRC_EQ_PREFER_SRC     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_SYS_SYSTEM_EQ_PREFER_SRC_EQ_PREFER_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,27)


/** 
 * \brief External CPU port configuration
 *
 * \details
 * Register: \a SYS:SYSTEM:EXT_CPU_CFG
 */
#define VTSS_SYS_SYSTEM_EXT_CPU_CFG          VTSS_IOREG(VTSS_TO_SYS,0x2116)

/** 
 * \brief
 * Select the port to use as the external CPU port.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EXT_CPU_CFG . EXT_CPU_PORT
 */
#define  VTSS_F_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPU_PORT(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Frames destined for a CPU extraction queue set in this mask are sent to
 * the external CPU defined by EXT_CPU_PORT instead of the internal CPU.
 *
 * \details 
 * Field: ::VTSS_SYS_SYSTEM_EXT_CPU_CFG . EXT_CPUQ_MSK
 */
#define  VTSS_F_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_SYSTEM_EXT_CPU_CFG_EXT_CPUQ_MSK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SYS:SCH
 *
 * Scheduler registers
 */


/** 
 * \brief Leaky bucket frame adjustment
 *
 * \details
 * Register: \a SYS:SCH:LB_DWRR_FRM_ADJ
 */
#define VTSS_SYS_SCH_LB_DWRR_FRM_ADJ         VTSS_IOREG(VTSS_TO_SYS,0x2117)

/** 
 * \brief
 * Value added to leaky buckets and DWRR each time a frame is scheduled. If
 * set to 20, this corresponds to inclusion of minimum Ethernet IFG and
 * preamble.

 *
 * \details 
 * 0-31: Number of bytes added at start of frame
 *
 * Field: ::VTSS_SYS_SCH_LB_DWRR_FRM_ADJ . FRM_ADJ
 */
#define  VTSS_F_SYS_SCH_LB_DWRR_FRM_ADJ_FRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SYS_SCH_LB_DWRR_FRM_ADJ_FRM_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SYS_SCH_LB_DWRR_FRM_ADJ_FRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Leaky bucked frame adjustment
 *
 * \details
 * Register: \a SYS:SCH:LB_DWRR_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-25
 */
#define VTSS_SYS_SCH_LB_DWRR_CFG(ri)         VTSS_IOREG(VTSS_TO_SYS,0x2118 + (ri))

/** 
 * \brief
 * If enabled, the value configured in SCH_LB_DWRR_FRM_ADJ.FRM_ADJ is added
 * to the frame length for each frame. 
 * 
 * The modified frame length is used by both the leaky bucket and DWRR
 * algorithm. 
 *
 * \details 
 * 0:Disable frame length adjustment.
 * 1:Enable frame length adjustment.
 *
 * Field: ::VTSS_SYS_SCH_LB_DWRR_CFG . FRM_ADJ_ENA
 */
#define  VTSS_F_SYS_SCH_LB_DWRR_CFG_FRM_ADJ_ENA  VTSS_BIT(0)


/** 
 * \brief Deficit weighted round robin control register
 *
 * \details
 * Register: \a SYS:SCH:SCH_DWRR_CFG
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-25
 */
#define VTSS_SYS_SCH_SCH_DWRR_CFG(ri)        VTSS_IOREG(VTSS_TO_SYS,0x2132 + (ri))

/** 
 * \brief
 * Configure DWRR scheduling for port. Weighted- and strict prioritization
 * can be configured.
 *
 * \details 
 * 0: All priorities are scheduled strict
 * 1: The two highest priorities (6, 7) are strict. The rest is DWRR

 *
 * Field: ::VTSS_SYS_SCH_SCH_DWRR_CFG . DWRR_MODE
 */
#define  VTSS_F_SYS_SCH_SCH_DWRR_CFG_DWRR_MODE  VTSS_BIT(30)

/** 
 * \brief
 * Queue cost configuration. Bit vector used to configure the cost of each
 * priority.
 * Bits 4:0: Cost for queue 0.
 * Bits 9:5: Cost for queue 1.
 * Bits 14:10: Cost for queue 2.
 * Bits 19:15: Cost for queue 3.
 * Bits 24:20: Cost for queue 4.
 * Bits 29:25: Cost for queue 5.
 * Within each cost field, the following encoding is used:
 *
 * \details 
 * 0: Cost 1
 * 1: Cost 2
 * ...
 * 31: Cost 32
 *
 * Field: ::VTSS_SYS_SCH_SCH_DWRR_CFG . COST_CFG
 */
#define  VTSS_F_SYS_SCH_SCH_DWRR_CFG_COST_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_SYS_SCH_SCH_DWRR_CFG_COST_CFG     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_SYS_SCH_SCH_DWRR_CFG_COST_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/** 
 * \brief Deficit weighted round robin queuing control
 *
 * \details
 * Register: \a SYS:SCH:SCH_DWRR_CTRL
 */
#define VTSS_SYS_SCH_SCH_DWRR_CTRL           VTSS_IOREG(VTSS_TO_SYS,0x214c)


/** 
 * \brief Scheduler shaping control register
 *
 * \details
 * Register: \a SYS:SCH:SCH_SHAPING_CTRL
 *
 * @param ri Replicator: x_FPORT_CNT (??), 0-25
 */
#define VTSS_SYS_SCH_SCH_SHAPING_CTRL(ri)    VTSS_IOREG(VTSS_TO_SYS,0x214d + (ri))

/** 
 * \brief
 * Enable priority shaping. If enabled the BW of a priority is limited to
 * SCH_LB::LB_RATE.
 *
 * \details 
 * xxxxxxx1: Enable shaping for Prio 0
 * xxxxxx1x: Enable shaping for Prio 1
 * ...
 * 1xxxxxxx: Enable shaping for Prio N
 *
 * Field: ::VTSS_SYS_SCH_SCH_SHAPING_CTRL . PRIO_SHAPING_ENA
 */
#define  VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_SHAPING_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_SCH_SCH_SHAPING_CTRL_PRIO_SHAPING_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_SCH_SCH_SHAPING_CTRL_PRIO_SHAPING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Enable port shaping. If enabled the total BW of a port is limited to
 * SCH_LB::LB_RATE.
 *
 * \details 
 * 0:  Disable port shaping
 * 1:  Enable port shaping
 *
 * Field: ::VTSS_SYS_SCH_SCH_SHAPING_CTRL . PORT_SHAPING_ENA
 */
#define  VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PORT_SHAPING_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Allow this queue to use excess bandwidth. If none of the priorities are
 * allowed (by their priority LB) to transmit.
 * 
 * The resulting BW of a queue is a function of the port- and queue LBs,
 * the DWRR and the excess enable bit:
 * 1)	  Port LB closed. Hold back frames.
 * 2)	  Port LB open -> Use strict- or DWRR scheduling to distribute
 * traffic between open Queue LBs
 * 3)	  All Queue LBs closed -> Hold back frames except for Queues which
 * have PRIO_LB_EXS_ENA set. The excess BW is distributed using strict- or
 * DWRR scheduling. 

 *
 * \details 
 * xxxxxxx1: Enable excess BW for Prio 0
 * xxxxxx1x: Enable excess BW for Prio 1
 * ...
 * 1xxxxxxx: Enable excess BW for Prio N
 *
 * Field: ::VTSS_SYS_SCH_SCH_SHAPING_CTRL . PRIO_LB_EXS_ENA
 */
#define  VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_EXS_ENA(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_EXS_ENA     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_EXS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Enable AV Bridging (AVB) shaping mode for queues. In AVB mode the burst
 * capacity of a queue is limited. An AVB queue can only build up burst
 * capacity when it has traffic to send.

 *
 * \details 
 * xxxxxxx1: Enable AVB mode for Prio 0
 * xxxxxx1x: Enable AVB mode for Prio 1
 * ...
 * 1xxxxxxx: Enable AVB mode for Prio N
 *
 * Field: ::VTSS_SYS_SCH_SCH_SHAPING_CTRL . PRIO_LB_AVB_ENA
 */
#define  VTSS_F_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_AVB_ENA(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_AVB_ENA     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SYS_SCH_SCH_SHAPING_CTRL_PRIO_LB_AVB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/** 
 * \brief Leaky bucket control
 *
 * \details
 * Register: \a SYS:SCH:SCH_LB_CTRL
 */
#define VTSS_SYS_SCH_SCH_LB_CTRL             VTSS_IOREG(VTSS_TO_SYS,0x2167)

/** 
 * \brief
 * Set to 1 to force a complete initialization of state and configuration
 * of leaky buckets.
 * Must be done before the scheduler is used. Field is automatically
 * cleared whether initialization is complete.

 *
 * \details 
 * 0: No Action
 * 1: Force initialization.
 *
 * Field: ::VTSS_SYS_SCH_SCH_LB_CTRL . LB_INIT
 */
#define  VTSS_F_SYS_SCH_SCH_LB_CTRL_LB_INIT   VTSS_BIT(0)


/** 
 * \brief Map CPU queues to CPU ports
 *
 * \details
 * Register: \a SYS:SCH:SCH_CPU
 */
#define VTSS_SYS_SCH_SCH_CPU                 VTSS_IOREG(VTSS_TO_SYS,0x2168)

/** 
 * \brief
 * Maps the 8 CPU queues to CPU port 26 or 27. Bit <n> set directs CPU
 * queue <n> to CPU port 26/27.
 *
 * \details 
 * Field: ::VTSS_SYS_SCH_SCH_CPU . SCH_CPU_MAP
 */
#define  VTSS_F_SYS_SCH_SCH_CPU_SCH_CPU_MAP(x)  VTSS_ENCODE_BITFIELD(x,2,8)
#define  VTSS_M_SYS_SCH_SCH_CPU_SCH_CPU_MAP     VTSS_ENCODE_BITMASK(2,8)
#define  VTSS_X_SYS_SCH_SCH_CPU_SCH_CPU_MAP(x)  VTSS_EXTRACT_BITFIELD(x,2,8)

/** 
 * \brief
 * Set the scheduler for CPU port <n> to run round robin between queues
 * instead of strict.
 *
 * \details 
 * Field: ::VTSS_SYS_SCH_SCH_CPU . SCH_CPU_RR
 */
#define  VTSS_F_SYS_SCH_SCH_CPU_SCH_CPU_RR(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SYS_SCH_SCH_CPU_SCH_CPU_RR     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SYS_SCH_SCH_CPU_SCH_CPU_RR(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SYS:SCH_LB
 *
 * Scheduler leaky bucket registers
 */


/** 
 * \brief Leaky bucket threshold
 *
 * \details
 * Register: \a SYS:SCH_LB:LB_THRES
 *
 * @param ri Replicator: x_SCH_LB_CNT (??), 0-233
 */
#define VTSS_SYS_SCH_LB_LB_THRES(ri)         VTSS_IOREG(VTSS_TO_SYS,0xe00 + (ri))

/** 
 * \brief
 * Burst capacity of leaky buckets
 * 
 * The unit is 4KB (1KB = 1024Bytes). The largest supported threshold is
 * 252KB
 * when the register value is set to all "1"s.
 * 
 * Queue shaper Q on port  P uses shaper 9*P+Q. Port shaper on port P uses
 * shaper 9*P+8.
 *
 * \details 
 * 0: Always closed
 * 1: Burst capacity = 4096 bytes
 * ...
 * n: Burst capacity = n x 4096 bytes
 *
 * Field: ::VTSS_SYS_SCH_LB_LB_THRES . LB_THRES
 */
#define  VTSS_F_SYS_SCH_LB_LB_THRES_LB_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SYS_SCH_LB_LB_THRES_LB_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SYS_SCH_LB_LB_THRES_LB_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Leaky bucket rate 
 *
 * \details
 * Register: \a SYS:SCH_LB:LB_RATE
 *
 * @param ri Replicator: x_SCH_LB_CNT (??), 0-233
 */
#define VTSS_SYS_SCH_LB_LB_RATE(ri)          VTSS_IOREG(VTSS_TO_SYS,0xf00 + (ri))

/** 
 * \brief
 * Leaky bucket rate in unit of 100160 bps. 
 * 
 * Queue shaper Q on port  P uses shaper 9*P+Q. Port shaper on port P uses
 * shaper 9*P+8.
 *
 * \details 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 100160 bps
 * n: Rate = n x 100160 bps

 *
 * Field: ::VTSS_SYS_SCH_LB_LB_RATE . LB_RATE
 */
#define  VTSS_F_SYS_SCH_LB_LB_RATE_LB_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_SYS_SCH_LB_LB_RATE_LB_RATE     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_SYS_SCH_LB_LB_RATE_LB_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,15)

/**
 * Register Group: \a SYS:COREMEM
 *
 * Access core memory
 */


/** 
 * \brief Address selection
 *
 * \details
 * Register: \a SYS:COREMEM:CM_ADDR
 */
#define VTSS_SYS_COREMEM_CM_ADDR             VTSS_IOREG(VTSS_TO_SYS,0xde6)

/** 
 * \brief
 * Address selection within selected core memory (CMID register). Address
 * is automatically advanced at every data access.
 *
 * \details 
 * Field: ::VTSS_SYS_COREMEM_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_SYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_SYS_COREMEM_CM_ADDR_CM_ADDR     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_SYS_COREMEM_CM_ADDR_CM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/** 
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a SYS:COREMEM:CM_DATA
 */
#define VTSS_SYS_COREMEM_CM_DATA             VTSS_IOREG(VTSS_TO_SYS,0xde7)

/**
 * Register Group: \a SYS:RES_CTRL
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
 * The register is layed out the following way:
 * Index 0-215: Reserved amount for (x,PRIO) at index 8*x+PRIO, x=SRC or
 * DST
 * Index 224-250: Reserved amount for (x)
 * Resource 0 is accessed at index 0-255, 1 at index 256-511 etc.
 * 
 * The amount of shared memory is located at index 255. An extra watermark
 * at 254 is used for limiting amount of shared memory used before yellow
 * traffic is discarded.
 * The amount of shared references is located at index 511. An extra
 * watermark at 510 is used for limiting amount of shared references for
 * yellow traffic.
 * 
 * At index 216-223 there is a watermarks per priority used for limiting
 * how much of the shared buffer must be used per priority.
 * Likewise at offset 472 there are priority watermarks for references.
 * The allocation size for memory tracking is 48 bytes, and all frames is
 * added a 4 byte header internally.
 *
 * Register: \a SYS:RES_CTRL:RES_CFG
 *
 * @param gi Register: RES_CTRL (??), 0-1023
 */
#define VTSS_SYS_RES_CTRL_RES_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_SYS,0x1000,gi,2,0,0)

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
 * Field: ::VTSS_SYS_RES_CTRL_RES_CFG . WM_HIGH
 */
#define  VTSS_F_SYS_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_SYS_RES_CTRL_RES_CFG_WM_HIGH     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_SYS_RES_CTRL_RES_CFG_WM_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Resource status
 *
 * \details
 * Register: \a SYS:RES_CTRL:RES_STAT
 *
 * @param gi Register: RES_CTRL (??), 0-1023
 */
#define VTSS_SYS_RES_CTRL_RES_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_SYS,0x1000,gi,2,0,1)

/** 
 * \brief
 * Current consumption for corresponding watermark in RES_CFG.
 *
 * \details 
 * Field: ::VTSS_SYS_RES_CTRL_RES_STAT . INUSE
 */
#define  VTSS_F_SYS_RES_CTRL_RES_STAT_INUSE(x)  VTSS_ENCODE_BITFIELD(x,14,14)
#define  VTSS_M_SYS_RES_CTRL_RES_STAT_INUSE     VTSS_ENCODE_BITMASK(14,14)
#define  VTSS_X_SYS_RES_CTRL_RES_STAT_INUSE(x)  VTSS_EXTRACT_BITFIELD(x,14,14)

/** 
 * \brief
 * Maximum consumption since last read for corresponding watermark in
 * RES_CFG.
 *
 * \details 
 * Field: ::VTSS_SYS_RES_CTRL_RES_STAT . MAXUSE
 */
#define  VTSS_F_SYS_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_SYS_RES_CTRL_RES_STAT_MAXUSE     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_SYS_RES_CTRL_RES_STAT_MAXUSE(x)  VTSS_EXTRACT_BITFIELD(x,0,14)

/**
 * Register Group: \a SYS:PAUSE_CFG
 *
 * Watermarks for egress queue system
 */


/** 
 * \brief Watermarks for flow control condition per switch port.
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:PAUSE_CFG
 *
 * @param ri Register: PAUSE_CFG (??), 0-26
 */
#define VTSS_SYS_PAUSE_CFG_PAUSE_CFG(ri)     VTSS_IOREG(VTSS_TO_SYS,0x2169 + (ri))

/** 
 * \brief
 * Start pausing ingress stream when the amount of memory consumed by the
 * port exceeds this watermark. The TOTPAUSE condition must also be met.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_START
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_ENCODE_BITFIELD(x,12,11)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START     VTSS_ENCODE_BITMASK(12,11)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_START(x)  VTSS_EXTRACT_BITFIELD(x,12,11)

/** 
 * \brief
 * Stop pausing ingress stream when the amount of memory consumed by the
 * port is below  this watermark.
 *
 * \details 
 * See RES_CFG.
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_STOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_STOP(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/** 
 * \brief
 * Enable pause feedback to the MAC, allowing transmission of pause frames
 * or HDX collisions to limit ingress data rate.
 *
 * \details 
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_CFG . PAUSE_ENA
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_CFG_PAUSE_ENA  VTSS_BIT(0)


/** 
 * \brief Configure total memory pause condition
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:PAUSE_TOT_CFG
 */
#define VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG     VTSS_IOREG(VTSS_TO_SYS,0x2184)

/** 
 * \brief
 * Assert TOTPAUSE condition when total memory allocation is above this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_START
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_ENCODE_BITFIELD(x,11,11)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START     VTSS_ENCODE_BITMASK(11,11)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_START(x)  VTSS_EXTRACT_BITFIELD(x,11,11)

/** 
 * \brief
 * Deassert TOTPAUSE condition when total memory allocation is below this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_PAUSE_TOT_CFG . PAUSE_TOT_STOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_SYS_PAUSE_CFG_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Tail dropping level
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:ATOP
 *
 * @param ri Replicator: x_SPORT_CNT (??), 0-26
 */
#define VTSS_SYS_PAUSE_CFG_ATOP(ri)          VTSS_IOREG(VTSS_TO_SYS,0x2185 + (ri))

/** 
 * \brief
 * When a source port consumes more than this level in the packet memory,
 * frames are tail dropped, unconditionally of destination. 
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_ATOP . ATOP
 */
#define  VTSS_F_SYS_PAUSE_CFG_ATOP_ATOP(x)    VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_SYS_PAUSE_CFG_ATOP_ATOP       VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_SYS_PAUSE_CFG_ATOP_ATOP(x)    VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Total raw memory use before tail dropping is activated
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:ATOP_TOT_CFG
 */
#define VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG      VTSS_IOREG(VTSS_TO_SYS,0x21a0)

/** 
 * \brief
 * Tail dropping is activate on a port when the port use has exceeded the
 * ATOP watermark for the port, and the total memory use has exceeded this
 * watermark.
 *
 * \details 
 * See RES_CFG
 *
 * Field: ::VTSS_SYS_PAUSE_CFG_ATOP_TOT_CFG . ATOP_TOT
 */
#define  VTSS_F_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_SYS_PAUSE_CFG_ATOP_TOT_CFG_ATOP_TOT(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Configures egress ports for flowcontrol
 *
 * \details
 * Register: \a SYS:PAUSE_CFG:EGR_DROP_FORCE
 */
#define VTSS_SYS_PAUSE_CFG_EGR_DROP_FORCE    VTSS_IOREG(VTSS_TO_SYS,0x21a1)

/** 
 * \brief
 * When enabled for a port, frames to the port are discarded, even when the
 * ingress port is enabled for flow control. Applicable to egress ports
 * that should not create head-of-line blocking in ingress ports operating
 * in flow control mode. An example is the CPU port.
 *
 * \details 
 * Field: ::VTSS_SYS_PAUSE_CFG_EGR_DROP_FORCE . EGRESS_DROP_FORCE
 */
#define  VTSS_F_SYS_PAUSE_CFG_EGR_DROP_FORCE_EGRESS_DROP_FORCE(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_SYS_PAUSE_CFG_EGR_DROP_FORCE_EGRESS_DROP_FORCE     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_SYS_PAUSE_CFG_EGR_DROP_FORCE_EGRESS_DROP_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,0,27)

/**
 * Register Group: \a SYS:MMGT
 *
 * Memory manager status
 */


/** 
 * \brief Packet Memory Status
 *
 * \details
 * Register: \a SYS:MMGT:MMGT
 */
#define VTSS_SYS_MMGT_MMGT                   VTSS_IOREG(VTSS_TO_SYS,0xde8)

/** 
 * \brief
 * Number of 192-byte free memory words.
 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_MMGT . FREECNT
 */
#define  VTSS_F_SYS_MMGT_MMGT_FREECNT(x)      VTSS_ENCODE_BITFIELD(x,8,12)
#define  VTSS_M_SYS_MMGT_MMGT_FREECNT         VTSS_ENCODE_BITMASK(8,12)
#define  VTSS_X_SYS_MMGT_MMGT_FREECNT(x)      VTSS_EXTRACT_BITFIELD(x,8,12)


/** 
 * \brief Egress queue status
 *
 * \details
 * Register: \a SYS:MMGT:EQ_CTRL
 */
#define VTSS_SYS_MMGT_EQ_CTRL                VTSS_IOREG(VTSS_TO_SYS,0xdea)

/** 
 * \brief
 * Number of free frame references.
 *
 * \details 
 * Field: ::VTSS_SYS_MMGT_EQ_CTRL . FP_FREE_CNT
 */
#define  VTSS_F_SYS_MMGT_EQ_CTRL_FP_FREE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_SYS_MMGT_EQ_CTRL_FP_FREE_CNT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_SYS_MMGT_EQ_CTRL_FP_FREE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * Register Group: \a SYS:MISC
 *
 * Miscellaneous
 */


/** 
 * \brief Frame repeating setup
 *
 * \details
 * Register: \a SYS:MISC:REPEATER
 */
#define VTSS_SYS_MISC_REPEATER               VTSS_IOREG(VTSS_TO_SYS,0xdf1)

/** 
 * \brief
 * A bit set in this mask makes the corresponding port skip dequeing from
 * the queue selected by the scheduler. This can be used for simple frame
 * generation and scheduler experiments.
 *
 * \details 
 * Field: ::VTSS_SYS_MISC_REPEATER . REPEATER
 */
#define  VTSS_F_SYS_MISC_REPEATER_REPEATER(x)  VTSS_ENCODE_BITFIELD(x,0,27)
#define  VTSS_M_SYS_MISC_REPEATER_REPEATER     VTSS_ENCODE_BITMASK(0,27)
#define  VTSS_X_SYS_MISC_REPEATER_REPEATER(x)  VTSS_EXTRACT_BITFIELD(x,0,27)

/**
 * Register Group: \a SYS:STAT
 *
 * Frame statistics
 */


/** 
 * \brief Counter values
 *
 * \details
 * Register: \a SYS:STAT:CNT
 *
 * @param gi Register: STAT (??), 0-3557
 */
#define VTSS_SYS_STAT_CNT(gi)                VTSS_IOREG_IX(VTSS_TO_SYS,0x0,gi,1,0,0)

/**
 * Register Group: \a SYS:PTP
 *
 * Precission time protocol
 */


/** 
 * \brief Stored timestamp and timestamp queue status
 *
 * \details
 * Register: \a SYS:PTP:PTP_STATUS
 */
#define VTSS_SYS_PTP_PTP_STATUS              VTSS_IOREG(VTSS_TO_SYS,0x21a2)

/** 
 * \brief
 * If set, the timestamp queue has overflown implying a timestamp entry
 * could not enqueued. The PTP_OVFL bit is not cleared until the timestamp
 * queue is completely empty.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_OVFL
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_OVFL   VTSS_BIT(12)

/** 
 * \brief
 * A timestamp entry is ready for reading. PTP_MESS_ID, PTP_MESS_TXPORT,
 * and PTP_DELAY contain the data of the timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_VLD
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_VLD  VTSS_BIT(11)

/** 
 * \brief
 * Timestamp identifier for head-of-line timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_ID
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_ID(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_SYS_PTP_PTP_STATUS_PTP_MESS_ID     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * The transmit port for the head-of-line timestamp entry.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_STATUS . PTP_MESS_TXPORT
 */
#define  VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief Timestamp value
 *
 * \details
 * Register: \a SYS:PTP:PTP_DELAY
 */
#define VTSS_SYS_PTP_PTP_DELAY               VTSS_IOREG(VTSS_TO_SYS,0x21a3)


/** 
 * \brief Configuration of Rx and Tx hardware timestamping
 *
 * \details
 * Register: \a SYS:PTP:PTP_CFG
 *
 * @param ri Replicator: x_DPORT_CNT (??), 0-27
 */
#define VTSS_SYS_PTP_PTP_CFG(ri)             VTSS_IOREG(VTSS_TO_SYS,0x21a4 + (ri))

/** 
 * \brief
 * Disable updating of the correction field in PTP frames. This overrules
 * the IS2 PTP_ENA[0] action.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_CFG . PTP_1STEP_DIS
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_PTP_1STEP_DIS  VTSS_BIT(17)

/** 
 * \brief
 * Disable adding the entries to the timestamp queue. This overrules the
 * IS2 PTP_ENA[1] action.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_CFG . PTP_2STEP_DIS
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_PTP_2STEP_DIS  VTSS_BIT(16)

/** 
 * \brief
 * Delay added to the sampled departure time. Unit is 4 ns.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_CFG . IO_TX_DELAY
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_IO_TX_DELAY(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SYS_PTP_PTP_CFG_IO_TX_DELAY     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SYS_PTP_PTP_CFG_IO_TX_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Delay subtracted from the sampled arrival time. Unit is 4 ns.
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_CFG . IO_RX_DELAY
 */
#define  VTSS_F_SYS_PTP_PTP_CFG_IO_RX_DELAY(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SYS_PTP_PTP_CFG_IO_RX_DELAY     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SYS_PTP_PTP_CFG_IO_RX_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Advancing the timestamp queue
 *
 * \details
 * Register: \a SYS:PTP:PTP_NXT
 */
#define VTSS_SYS_PTP_PTP_NXT                 VTSS_IOREG(VTSS_TO_SYS,0x21c0)

/** 
 * \brief
 * Advance to the next timestamp entry. Registers PTP_STATUS amd PTP_DELAY
 * points to the next entry. 
 *
 * \details 
 * Field: ::VTSS_SYS_PTP_PTP_NXT . PTP_NXT
 */
#define  VTSS_F_SYS_PTP_PTP_NXT_PTP_NXT       VTSS_BIT(0)

/**
 * Register Group: \a SYS:POL
 *
 * Not documented
 */


/** 
 * \brief Peak Information Rate configuration for this policer
 *
 * \details
 * Register: \a SYS:POL:POL_PIR_CFG
 *
 * @param gi Register: POL (??), 0-255
 */
#define VTSS_SYS_POL_POL_PIR_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_SYS,0x1800,gi,8,0,0)

/** 
 * \brief
 * Accepted rate for this policer. Unit is 100 kbps.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_PIR_CFG . PIR_RATE
 */
#define  VTSS_F_SYS_POL_POL_PIR_CFG_PIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,15)
#define  VTSS_M_SYS_POL_POL_PIR_CFG_PIR_RATE     VTSS_ENCODE_BITMASK(6,15)
#define  VTSS_X_SYS_POL_POL_PIR_CFG_PIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,15)

/** 
 * \brief
 * Burst capacity of this policer. Unit is 4 kilobytes.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_PIR_CFG . PIR_BURST
 */
#define  VTSS_F_SYS_POL_POL_PIR_CFG_PIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SYS_POL_POL_PIR_CFG_PIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SYS_POL_POL_PIR_CFG_PIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Committed Information Rate configuration for this policer
 *
 * \details
 * Register: \a SYS:POL:POL_CIR_CFG
 *
 * @param gi Register: POL (??), 0-255
 */
#define VTSS_SYS_POL_POL_CIR_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_SYS,0x1800,gi,8,0,1)

/** 
 * \brief
 * Accepted rate for this policer. Unit is 100 kbps.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_CIR_CFG . CIR_RATE
 */
#define  VTSS_F_SYS_POL_POL_CIR_CFG_CIR_RATE(x)  VTSS_ENCODE_BITFIELD(x,6,15)
#define  VTSS_M_SYS_POL_POL_CIR_CFG_CIR_RATE     VTSS_ENCODE_BITMASK(6,15)
#define  VTSS_X_SYS_POL_POL_CIR_CFG_CIR_RATE(x)  VTSS_EXTRACT_BITFIELD(x,6,15)

/** 
 * \brief
 * Burst capacity of this policer. Unit is 4 kilobytes.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_CIR_CFG . CIR_BURST
 */
#define  VTSS_F_SYS_POL_POL_CIR_CFG_CIR_BURST(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SYS_POL_POL_CIR_CFG_CIR_BURST     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SYS_POL_POL_CIR_CFG_CIR_BURST(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Common configuration for this policer
 *
 * \details
 * Register: \a SYS:POL:POL_MODE_CFG
 *
 * @param gi Register: POL (??), 0-255
 */
#define VTSS_SYS_POL_POL_MODE_CFG(gi)        VTSS_IOREG_IX(VTSS_TO_SYS,0x1800,gi,8,0,2)

/** 
 * \brief
 * Size of IPG to add to each frame if line rate policing is chosen in
 * FRM_MODE.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_MODE_CFG . IPG_SIZE
 */
#define  VTSS_F_SYS_POL_POL_MODE_CFG_IPG_SIZE(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_SYS_POL_POL_MODE_CFG_IPG_SIZE     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_SYS_POL_POL_MODE_CFG_IPG_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Accounting mode of this policer.
 *
 * \details 
 * 0: Line rate. Police bytes including IPG_SIZE.
 * 1: Data rate. Police bytes excluding IPG.
 * 2. Frame rate. Police frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Police frame with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_SYS_POL_POL_MODE_CFG . FRM_MODE
 */
#define  VTSS_F_SYS_POL_POL_MODE_CFG_FRM_MODE(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SYS_POL_POL_MODE_CFG_FRM_MODE     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SYS_POL_POL_MODE_CFG_FRM_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * Dual Leaky Bucket function of this policer.
 *
 * \details 
 * 0. Do CIR/PIR policing w/o coupling
 * 1: Do CIR/PIR policing w coupling
 *
 * Field: ::VTSS_SYS_POL_POL_MODE_CFG . DLB_COUPLED
 */
#define  VTSS_F_SYS_POL_POL_MODE_CFG_DLB_COUPLED  VTSS_BIT(2)

/** 
 * \brief
 * Enable yellow marking when commited rate is reached.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_MODE_CFG . CIR_ENA
 */
#define  VTSS_F_SYS_POL_POL_MODE_CFG_CIR_ENA  VTSS_BIT(1)

/** 
 * \brief
 * If set, overshoot is allowed. This implies that a frame of any length is
 * accepted if the policer is open even if the frame causes the bucket to
 * use more than the remaining capacity. 
 * If cleared, overshoot is not allowed. This implies that it is checked
 * that the frame will not use more than the remaining capacity in the
 * bucket before accepting the frame.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_MODE_CFG . OVERSHOOT_ENA
 */
#define  VTSS_F_SYS_POL_POL_MODE_CFG_OVERSHOOT_ENA  VTSS_BIT(0)


/** 
 * \brief State of this policer
 *
 * \details
 * Register: \a SYS:POL:POL_PIR_STATE
 *
 * @param gi Register: POL (??), 0-255
 */
#define VTSS_SYS_POL_POL_PIR_STATE(gi)       VTSS_IOREG_IX(VTSS_TO_SYS,0x1800,gi,8,0,3)

/** 
 * \brief
 * Current fill level of this policer. Unit is 0.5 bits.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_PIR_STATE . PIR_LVL
 */
#define  VTSS_F_SYS_POL_POL_PIR_STATE_PIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_SYS_POL_POL_PIR_STATE_PIR_LVL     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_SYS_POL_POL_PIR_STATE_PIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


/** 
 * \brief State of this policer
 *
 * \details
 * Register: \a SYS:POL:POL_CIR_STATE
 *
 * @param gi Register: POL (??), 0-255
 */
#define VTSS_SYS_POL_POL_CIR_STATE(gi)       VTSS_IOREG_IX(VTSS_TO_SYS,0x1800,gi,8,0,4)

/** 
 * \brief
 * Current fill level of this policer. Unit is 0.5 bits.
 *
 * \details 
 * Field: ::VTSS_SYS_POL_POL_CIR_STATE . CIR_LVL
 */
#define  VTSS_F_SYS_POL_POL_CIR_STATE_CIR_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_SYS_POL_POL_CIR_STATE_CIR_LVL     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_SYS_POL_POL_CIR_STATE_CIR_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,22)

/**
 * Register Group: \a SYS:POL_MISC
 *
 * Flow control configuration
 */


/** 
 * \brief Flow control configuration per policer
 *
 * \details
 * Register: \a SYS:POL_MISC:POL_FLOWC
 *
 * @param ri Register: POL_FLOWC (??), 0-26
 */
#define VTSS_SYS_POL_MISC_POL_FLOWC(ri)      VTSS_IOREG(VTSS_TO_SYS,0x21c1 + (ri))

/** 
 * \brief
 * Use MAC flow control for lowering ingress rate
 *
 * \details 
 * 0: Standard policing. Frames are discarded when the rate is exceeded.
 * 1: Flow control policing. Policer instructs the MAC to issue pause
 * frames when the rate is exceeded.

 *
 * Field: ::VTSS_SYS_POL_MISC_POL_FLOWC . POL_FLOWC
 */
#define  VTSS_F_SYS_POL_MISC_POL_FLOWC_POL_FLOWC  VTSS_BIT(0)


/** 
 * \brief Set delay between flow control clearings
 *
 * \details
 * Register: \a SYS:POL_MISC:POL_HYST
 */
#define VTSS_SYS_POL_MISC_POL_HYST           VTSS_IOREG(VTSS_TO_SYS,0x21dc)

/** 
 * \brief
 * Set hysteresis for when to re-open a bucket after the burst capacity has
 * been used. Unit is 1 kilobytes. This applies to policer in flow control
 * mode (POL_FLOWC=1).
 *
 * \details 
 * Field: ::VTSS_SYS_POL_MISC_POL_HYST . POL_FC_HYST
 */
#define  VTSS_F_SYS_POL_MISC_POL_HYST_POL_FC_HYST(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SYS_POL_MISC_POL_HYST_POL_FC_HYST     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SYS_POL_MISC_POL_HYST_POL_FC_HYST(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Set hysteresis for when to re-open a bucket after the burst capacity has
 * been used. Unit is 2 kilobytes. This applies to policer in drop mode
 * (POL_FLOWC=0).
 *
 * \details 
 * Field: ::VTSS_SYS_POL_MISC_POL_HYST . POL_DROP_HYST
 */
#define  VTSS_F_SYS_POL_MISC_POL_HYST_POL_DROP_HYST(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SYS_POL_MISC_POL_HYST_POL_DROP_HYST     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SYS_POL_MISC_POL_HYST_POL_DROP_HYST(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SYS:ISHP
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a SYS:ISHP:ISHP_CFG
 *
 * @param gi Register: ISHP (??), 0-26
 */
#define VTSS_SYS_ISHP_ISHP_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_SYS,0x2000,gi,4,0,0)

/** 
 * \brief
 * Accepted rate for this shaper. Unit is 100 kbps.
 *
 * \details 
 * Field: ::VTSS_SYS_ISHP_ISHP_CFG . ISHP_RATE
 */
#define  VTSS_F_SYS_ISHP_ISHP_CFG_ISHP_RATE(x)  VTSS_ENCODE_BITFIELD(x,7,15)
#define  VTSS_M_SYS_ISHP_ISHP_CFG_ISHP_RATE     VTSS_ENCODE_BITMASK(7,15)
#define  VTSS_X_SYS_ISHP_ISHP_CFG_ISHP_RATE(x)  VTSS_EXTRACT_BITFIELD(x,7,15)

/** 
 * \brief
 * Burst capacity of this shaper. Unit is 4kB
 *
 * \details 
 * Field: ::VTSS_SYS_ISHP_ISHP_CFG . ISHP_BURST
 */
#define  VTSS_F_SYS_ISHP_ISHP_CFG_ISHP_BURST(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_SYS_ISHP_ISHP_CFG_ISHP_BURST     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_SYS_ISHP_ISHP_CFG_ISHP_BURST(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * Enable ingress shaping for this port.
 *
 * \details 
 * Field: ::VTSS_SYS_ISHP_ISHP_CFG . ISHP_ENA
 */
#define  VTSS_F_SYS_ISHP_ISHP_CFG_ISHP_ENA    VTSS_BIT(0)


/** 
 * \details
 * Register: \a SYS:ISHP:ISHP_MODE_CFG
 *
 * @param gi Register: ISHP (??), 0-26
 */
#define VTSS_SYS_ISHP_ISHP_MODE_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_SYS,0x2000,gi,4,0,1)

/** 
 * \brief
 * Size of IPG to add each frame if line rate shaping is chosen in
 * ISHP_MODE.
 *
 * \details 
 * Field: ::VTSS_SYS_ISHP_ISHP_MODE_CFG . ISHP_IPG_SIZE
 */
#define  VTSS_F_SYS_ISHP_ISHP_MODE_CFG_ISHP_IPG_SIZE(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_SYS_ISHP_ISHP_MODE_CFG_ISHP_IPG_SIZE     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_SYS_ISHP_ISHP_MODE_CFG_ISHP_IPG_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Accounting mode of this shaper.
 *
 * \details 
 * 0: Line rate. Shape bytes including IPG_size
 * 1: Data rate. Shape bytes excluding IPG
 * 2. Frame rate. Shape frames with rate unit = 100 fps and burst unit =
 * 32.8 frames.
 * 3: Frame rate. Shape frame with rate unit = 1 fps and burst unit = 0.3
 * frames.
 *
 * Field: ::VTSS_SYS_ISHP_ISHP_MODE_CFG . ISHP_MODE
 */
#define  VTSS_F_SYS_ISHP_ISHP_MODE_CFG_ISHP_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SYS_ISHP_ISHP_MODE_CFG_ISHP_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SYS_ISHP_ISHP_MODE_CFG_ISHP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief State of this shaper
 *
 * \details
 * Register: \a SYS:ISHP:ISHP_STATE
 *
 * @param gi Register: ISHP (??), 0-26
 */
#define VTSS_SYS_ISHP_ISHP_STATE(gi)         VTSS_IOREG_IX(VTSS_TO_SYS,0x2000,gi,4,0,2)

/** 
 * \brief
 * Current fill level of this shaper. Unit is 0.5 bits.
 *
 * \details 
 * Field: ::VTSS_SYS_ISHP_ISHP_STATE . ISHP_LVL
 */
#define  VTSS_F_SYS_ISHP_ISHP_STATE_ISHP_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_SYS_ISHP_ISHP_STATE_ISHP_LVL     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_SYS_ISHP_ISHP_STATE_ISHP_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,22)


#endif /* _VTSS_LUTON26_REGS_SYS_H_ */
