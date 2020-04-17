// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2_REGS_QFWD_H_
#define _VTSS_JAGUAR2_REGS_QFWD_H_


#include "vtss_jaguar2_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a QFWD
 *
 * Queue System Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a QFWD:SYSTEM
 *
 * Switch configuration
 */


/** 
 * \brief Various switch port mode settings
 *
 * \details
 * Register: \a QFWD:SYSTEM:SWITCH_PORT_MODE
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x10e4 + (ri))

/** 
 * \brief
 * Enable port for any frame transfer.
 * Frames to or from a port with PORT_ENA cleared are discarded.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . PORT_ENA
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA  VTSS_BIT(10)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set the switching speed per port.
 *
 * \details 
 * 0: One forwarding guaranteed per 640 ns (1Gbps)
 *	   1: One forwarding per 240 ns (2.5Gbps)
 * 2: One copy per 64 ns (10Gbps)
 *  3:Fixed high priority port
 *
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . FWD_SPEED
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Enable yellow traffic to use reserved ingress space.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . YEL_RSRVD
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * When enabled for a port, frames -from- that port are discarded when the
 * controlling watermarks are hit. If disabled - the frame will stay in
 * memory until resources are available. If INGRESS_DROP_MODE or
 * EGRESS_DROP_MODE applies for a frame copy, it will be discared.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . INGRESS_DROP_MODE
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE  VTSS_BIT(3)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . IGR_NO_SHARING
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING  VTSS_BIT(2)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . EGR_NO_SHARING
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING  VTSS_BIT(1)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * When enabled for a port, frames -to- that port are discarded when the
 * controlling watermarks are hit. If disabled - the frame will stay in
 * memory until resources are available. If INGRESS_DROP_MODE or
 * EGRESS_DROP_MODE applies for a frame copy, it will be discared.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . EGRESS_DROP_MODE
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:STAT_CNT_CFG
 */
#define VTSS_QFWD_SYSTEM_STAT_CNT_CFG        VTSS_IOREG(VTSS_TO_QFWD,0x111d)

/** 
 * \brief
 * When set, a frame discarded due to lack of resources is counted on the
 * egress port instead of the ingress. Side effect is a slower processing
 * of multiple drops on the same frame, causing potential head-of-line
 * blocking.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_STAT_CNT_CFG . DROP_COUNT_EGRESS
 */
#define  VTSS_F_QFWD_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_STAT_CNT_CFG_DROP_COUNT_EGRESS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Forwarder idle counter configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_IDLE_CNT
 */
#define VTSS_QFWD_SYSTEM_FWD_IDLE_CNT        VTSS_IOREG(VTSS_TO_QFWD,0x111e)

/** 
 * \brief
 * The maximum number of clock cycles between guaranteed CSR access to
 * res_stat counters.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_IDLE_CNT . FWD_IDLE_CNT
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_IDLE_CNT_FWD_IDLE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_SYSTEM_FWD_IDLE_CNT_FWD_IDLE_CNT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_SYSTEM_FWD_IDLE_CNT_FWD_IDLE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Frame copying configuration
 *
 * \details
 * Configures how various frame copies are to be generated in the
 * forwarding core. 
 * 
 * Frame copies are made when the CPU should get one or more copies (some
 * CPU queues hit), when learn updates are to be generated, and when frame
 * mirroring is requested. 
 * 
 * Per copy reason, it is configured to which physical port the frame is to
 * be sent, and which QoS level to use in the egress queues. 
 * 
 * 0-7: Configuration for cpu queue N.
 * 8: Configuration for learn updates.
 * 9-11: Configuration for mirror probe 0-2.

 *
 * Register: \a QFWD:SYSTEM:FRAME_COPY_CFG
 *
 * @param ri Register: FRAME_COPY_CFG (??), 0-11
 */
#define VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x111f + (ri))

/** 
 * \brief
 * Physical port to send the frame to.
 * 
 * In case of replication 8 (Learn All frames), then the 2nd port used for
 * Learn All frames is configured in
 * FRAME_COPY_LRNA_CFG.FRMC_PORT_LRNA_VAL.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FRAME_COPY_CFG . FRMC_PORT_VAL
 */
#define  VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_PORT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Selected QoS level to use in the egress queues

 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FRAME_COPY_CFG . FRMC_QOS_VAL
 */
#define  VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_VAL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_VAL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Set to enable use of use FRMC_QOS_VAL. Otherwise classified priority is
 * used.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FRAME_COPY_CFG . FRMC_QOS_ENA
 */
#define  VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_ENA  VTSS_BIT(2)
#define  VTSS_X_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_QOS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Use super priority enqueuing.
 * 
 * Note that even when SP is used, QoS value still controls from which pool
 * ressources are allocated, so it may be relevant to also set
 * FRMC_QOS_ENA=1 and FRMC_QOS_VAL.

 *
 * \details 
 * 0: Use normal queues
 * 1: Use super priority queue bypassing all shapers 
 * 2: Use super priority queue obeying/updating port shaper
 * 3: reserved
 *
 * Field: ::VTSS_QFWD_SYSTEM_FRAME_COPY_CFG . FRMC_SP_ENA
 */
#define  VTSS_F_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_SP_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_SP_ENA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QFWD_SYSTEM_FRAME_COPY_CFG_FRMC_SP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Frame copying configuration
 *
 * \details
 * Configures 2nd port for sending Learn All frame copies. 
 * 
 * If only one Learn All port is to be used, this port number MUST be
 * configured to the same port as FRMC_PORT_VAL:8.

 *
 * Register: \a QFWD:SYSTEM:FRAME_COPY_LRNA_CFG
 */
#define VTSS_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG  VTSS_IOREG(VTSS_TO_QFWD,0x112b)

/** 
 * \brief
 * Physical port to send Learn All frame to.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG . FRMC_PORT_LRNA_VAL
 */
#define  VTSS_F_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG_FRMC_PORT_LRNA_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG_FRMC_PORT_LRNA_VAL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG_FRMC_PORT_LRNA_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief QS drop events per port and copy type
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_DROP_EVENTS
 *
 * @param ri Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x112c + (ri))

/** 
 * \brief
 * A switched frame copy was canceled to one or more egress ports.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS . FWD_DROP_NORM_STICKY
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY  VTSS_BIT(4)
#define  VTSS_X_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_NORM_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * A CPU directed frame copy was canceled.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS . FWD_DROP_CPU_STICKY
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY  VTSS_BIT(3)
#define  VTSS_X_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * A learnall frame copy was canceled.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS . FWD_DROP_LEARN_STICKY
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY  VTSS_BIT(2)
#define  VTSS_X_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_LEARN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * A mirror copy was canceled.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS . FWD_DROP_MIRR_STICKY
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY  VTSS_BIT(1)
#define  VTSS_X_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_MIRR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * A frame copy was discarded due to a queuemapping violation.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS . FWD_DROP_QMAP_STICKY
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_FWD_DROP_EVENTS_FWD_DROP_QMAP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Counter for number of frames discarded towards the cpu
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_CPU_DROP_CNT
 */
#define VTSS_QFWD_SYSTEM_FWD_CPU_DROP_CNT    VTSS_IOREG(VTSS_TO_QFWD,0x1165)

/** 
 * \brief
 * Counts number of frames discarded towards the cpu, since queue system
 * reset.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_CPU_DROP_CNT . FWD_CPU_DROP_CNT
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT(x)  (x)
#define  VTSS_M_QFWD_SYSTEM_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT     0xffffffff
#define  VTSS_X_QFWD_SYSTEM_FWD_CPU_DROP_CNT_FWD_CPU_DROP_CNT(x)  (x)


/** 
 * \brief Counter for number of frames forwarding aborted due to forward pressure
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_PRESS_DROP_CNT
 */
#define VTSS_QFWD_SYSTEM_FWD_PRESS_DROP_CNT  VTSS_IOREG(VTSS_TO_QFWD,0x1166)

/** 
 * \brief
 * Counts number of frames discarded due to forward pressure, since queue
 * system reset.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_PRESS_DROP_CNT . FWD_PRESS_DROP_CNT
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_PRESS_DROP_CNT_FWD_PRESS_DROP_CNT(x)  (x)
#define  VTSS_M_QFWD_SYSTEM_FWD_PRESS_DROP_CNT_FWD_PRESS_DROP_CNT     0xffffffff
#define  VTSS_X_QFWD_SYSTEM_FWD_PRESS_DROP_CNT_FWD_PRESS_DROP_CNT(x)  (x)


/** 
 * \brief Counters showing forwarding runs. Debugging purposes only
 *
 * \details
 * Three counters exists in the forwarder. Replication 0 counts each
 * executed queue head processing. Replication 1 counts each occurance of a
 * delayed processing due to egress queue system pressure, and replication
 * 2 counts occurances of delayed process due to statistics event pressure.
 *
 * Register: \a QFWD:SYSTEM:FWD_STAT_CNT
 *
 * @param ri Register: FWD_STAT_CNT (??), 0-2
 */
#define VTSS_QFWD_SYSTEM_FWD_STAT_CNT(ri)    VTSS_IOREG(VTSS_TO_QFWD,0x1167 + (ri))

/** 
 * \brief
 * Counts number of forwarding events since chip reset.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_STAT_CNT . FWD_STAT_CNT
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_STAT_CNT_FWD_STAT_CNT(x)  (x)
#define  VTSS_M_QFWD_SYSTEM_FWD_STAT_CNT_FWD_STAT_CNT     0xffffffff
#define  VTSS_X_QFWD_SYSTEM_FWD_STAT_CNT_FWD_STAT_CNT(x)  (x)


/** 
 * \brief Mirroring configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:MIRROR_CFG
 */
#define VTSS_QFWD_SYSTEM_MIRROR_CFG          VTSS_IOREG(VTSS_TO_QFWD,0x116a)

/** 
 * \brief
 * One bit per mirror probe enabling generation of mirror copies also for
 * frames discarded due to buffer discards.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_MIRROR_CFG . MIRROR_DISCARDS
 */
#define  VTSS_F_QFWD_SYSTEM_MIRROR_CFG_MIRROR_DISCARDS(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_QFWD_SYSTEM_MIRROR_CFG_MIRROR_DISCARDS     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_QFWD_SYSTEM_MIRROR_CFG_MIRROR_DISCARDS(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Discard frames destined for specific CPU queues
 *
 * \details
 * Register: \a QFWD:SYSTEM:CPUQ_DISCARD
 */
#define VTSS_QFWD_SYSTEM_CPUQ_DISCARD        VTSS_IOREG(VTSS_TO_QFWD,0x116b)

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
 * Field: ::VTSS_QFWD_SYSTEM_CPUQ_DISCARD . CPUQ_DISCARD
 */
#define  VTSS_F_QFWD_SYSTEM_CPUQ_DISCARD_CPUQ_DISCARD(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_QFWD_SYSTEM_CPUQ_DISCARD_CPUQ_DISCARD     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_QFWD_SYSTEM_CPUQ_DISCARD_CPUQ_DISCARD(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a QFWD:QMAP
 *
 * Mapping frames to scheduling elements
 */


/** 
 * \brief Mapping frames to scheduling elements per egress port
 *
 * \details
 * Configures how the queue number is calculated for each egress port. The
 * queue number is based on the the channel number and the qos value. These
 * are found through the QMAP_CH_SEL, and QMAP_QOS_SEL fields.
 * The queue number is calculated as a base number + (channel << N) + qos,
 * or same with channel/qos swapped.
 * 
 * Default setting is queue = (dstport x 512) + (iprio x 64) + (srcport)
 * QMAP_BASE=512*index
 * QMAP_CH_SEL=3 (source)
 * QMAP_QOS_SEL=0 (iprio)
 * QMAP_CFG_SFT_VAL=0 (Multiple the qos value)
 * QMAP_CFG_SFT_CNT=6 (-by 64)
 * QMAP_SE_WIDTH=1 (64 queues per SE)

 *
 * Register: \a QFWD:QMAP:QMAP_CFG
 *
 * @param gi Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_QMAP_QMAP_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_QFWD,0x1000,gi,4,0,0)

/** 
 * \brief
 * Configured channel mapping. 
 * Note: The virtual device (Routing loop) uses only one channel per qos
 * class,  and default value is hardware initialized to 4.
 *
 * \details 
 * 000: Select QMAP_TBL_0 mapping
 * 001: Select QMAP_TBL_1 mapping 
 * 010: Channel set to ISDX
 * 011: Channel set to source port number
 * 100: Channel 0
 * 101: Channel set to ISDX/8
 *
 * Field: ::VTSS_QFWD_QMAP_QMAP_CFG . QMAP_CH_SEL
 */
#define  VTSS_F_QFWD_QMAP_QMAP_CFG_QMAP_CH_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_QFWD_QMAP_QMAP_CFG_QMAP_CH_SEL     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_QFWD_QMAP_QMAP_CFG_QMAP_CH_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Configured QOS mapping
 *
 * \details 
 * 000: Use IPRIO for all ISDXs
 * 001: Use CID for all ISDXs
 * 010: Use ISDXs(2..0) for all ISDXs
 * 011: Set the qos to 0 
 * 100: Use qos selector QMAP_USE_CID_0
 * 101: Use qos selector QMAP_USE_CID_1
 * 110: Use qos selector QMAP_USE_CID_2
 * 111: Use qos selector QMAP_USE_CID_3

 *
 * Field: ::VTSS_QFWD_QMAP_QMAP_CFG . QMAP_QOS_SEL
 */
#define  VTSS_F_QFWD_QMAP_QMAP_CFG_QMAP_QOS_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_QFWD_QMAP_QMAP_CFG_QMAP_QOS_SEL     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_QFWD_QMAP_QMAP_CFG_QMAP_QOS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Select which of the channel/qos to shift into the queue number
 *
 * \details 
 * 0: Queue = CHANNEL + (QOS<<SFT)
 * 1: Queue = QOS + (CHANNEL<<SFT)

 *
 * Field: ::VTSS_QFWD_QMAP_QMAP_CFG . QMAP_SFT_VAL
 */
#define  VTSS_F_QFWD_QMAP_QMAP_CFG_QMAP_SFT_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QFWD_QMAP_QMAP_CFG_QMAP_SFT_VAL  VTSS_BIT(4)
#define  VTSS_X_QFWD_QMAP_QMAP_CFG_QMAP_SFT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Value for shift amount (see QMAP_SFT_VAL)
 *
 * \details 
 * 0: Multiply by 1
 * 1: Multiply by 2
 * ...
 * 6: Multiply by 64
 * ...
 * 15: Multiply by 32768

 *
 * Field: ::VTSS_QFWD_QMAP_QMAP_CFG . QMAP_SFT_CNT
 */
#define  VTSS_F_QFWD_QMAP_QMAP_CFG_QMAP_SFT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_QFWD_QMAP_QMAP_CFG_QMAP_SFT_CNT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_QFWD_QMAP_QMAP_CFG_QMAP_SFT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Define limits for this port
 *
 * \details
 * Register: \a QFWD:QMAP:QMAP_RANGES
 *
 * @param gi Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_QMAP_QMAP_RANGES(gi)       VTSS_IOREG_IX(VTSS_TO_QFWD,0x1000,gi,4,0,1)

/** 
 * \brief
 * Defines the first channel in use on this port. When the channel is used
 * in the queue number expression, this value will be subtracted before
 * use.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_QMAP_RANGES . QMAP_CH_BASE
 */
#define  VTSS_F_QFWD_QMAP_QMAP_RANGES_QMAP_CH_BASE(x)  VTSS_ENCODE_BITFIELD(x,15,12)
#define  VTSS_M_QFWD_QMAP_QMAP_RANGES_QMAP_CH_BASE     VTSS_ENCODE_BITMASK(15,12)
#define  VTSS_X_QFWD_QMAP_QMAP_RANGES_QMAP_CH_BASE(x)  VTSS_EXTRACT_BITFIELD(x,15,12)

/** 
 * \brief
 * Maximum queue number (before adding QMAP_BASE) for this port. If a queue
 * number calculation falls outside this limit, the frame will be
 * discarded, and the FWD_DROP_MAP_STICKY will be set.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_QMAP_RANGES . QMAP_QUEUE_MAX
 */
#define  VTSS_F_QFWD_QMAP_QMAP_RANGES_QMAP_QUEUE_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_QFWD_QMAP_QMAP_RANGES_QMAP_QUEUE_MAX     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_QFWD_QMAP_QMAP_RANGES_QMAP_QUEUE_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/** 
 * \brief Configures set of SEs to be used by this port
 *
 * \details
 * Register: \a QFWD:QMAP:QMAP_SE_CFG
 *
 * @param gi Replicator: x_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_QMAP_QMAP_SE_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_QFWD,0x1000,gi,4,0,2)

/** 
 * \brief
 * First scheduling element used for this port.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_QMAP_SE_CFG . QMAP_SE_BASE
 */
#define  VTSS_F_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_BASE(x)  VTSS_ENCODE_BITFIELD(x,1,12)
#define  VTSS_M_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_BASE     VTSS_ENCODE_BITMASK(1,12)
#define  VTSS_X_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_BASE(x)  VTSS_EXTRACT_BITFIELD(x,1,12)

/** 
 * \brief
 * Configures the number of queues per scheduling element on the first
 * layer. This setting MUST match HSCH::HSCH_MISC_CFG.HSCH_LARGE_CNT value
 * of the scheduler.
 *
 * \details 
 * 0: 8 queues per element
 * 1: 64 queue per element

 *
 * Field: ::VTSS_QFWD_QMAP_QMAP_SE_CFG . QMAP_SE_WIDTH
 */
#define  VTSS_F_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_WIDTH(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_WIDTH  VTSS_BIT(0)
#define  VTSS_X_QFWD_QMAP_QMAP_SE_CFG_QMAP_SE_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QFWD:QMAP_TBL
 *
 * Not documented
 */


/** 
 * \brief Configures a mapped isdx values for the queue calculation
 *
 * \details
 * Register: \a QFWD:QMAP_TBL:QMAP_TBL_CFG
 *
 * @param gi Replicator: x_ISDX_CNT (??), 0-4095
 */
#define VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x0,gi,1,0,0)

/** 
 * \brief
 * Use this channel number when the port uses table 0.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_CH_0_VAL
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_0_VAL(x)  VTSS_ENCODE_BITFIELD(x,14,10)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_0_VAL     VTSS_ENCODE_BITMASK(14,10)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_0_VAL(x)  VTSS_EXTRACT_BITFIELD(x,14,10)

/** 
 * \brief
 * Use this channel number when the port uses table 1.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_CH_1_VAL
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_1_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_1_VAL     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_CH_1_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * If set, use the Class Of Service ID for queue selection; otherwise the
 * internal priority
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_USE_CID_0
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_0(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_0  VTSS_BIT(3)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_0(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * If set, use the Class Of Service ID for queue selection; otherwise the
 * internal priority
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_USE_CID_1
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_1  VTSS_BIT(2)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If set, use the Class Of Service ID for queue selection; otherwise the
 * internal priority
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_USE_CID_2
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_2  VTSS_BIT(1)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If set, use the Class Of Service ID for queue selection; otherwise the
 * internal priority
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_TBL_QMAP_TBL_CFG . QMAP_USE_CID_3
 */
#define  VTSS_F_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_3(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_3  VTSS_BIT(0)
#define  VTSS_X_QFWD_QMAP_TBL_QMAP_TBL_CFG_QMAP_USE_CID_3(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2_REGS_QFWD_H_ */
