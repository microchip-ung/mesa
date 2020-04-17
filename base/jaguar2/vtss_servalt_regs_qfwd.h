// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_SERVALT_REGS_QFWD_H_
#define _VTSS_SERVALT_REGS_QFWD_H_


#include "vtss_servalt_regs_common.h"

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
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 */
#define VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x1100 + (ri))

/** 
 * \brief
 * Enable port for any frame transfer.
 * Frames to or from a port with PORT_ENA cleared are discarded.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . PORT_ENA
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA  VTSS_BIT(17)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set the switching speed per port. One forwarding guaranteed every this
 * value of clock cycles has passed
 *  Example with 10: One forwarding per 10 cycles (at 6.4 ns every 64 ns -
 * 10Gport minimum)
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . FWD_URGENCY
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY(x)  VTSS_ENCODE_BITFIELD(x,9,8)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY     VTSS_ENCODE_BITMASK(9,8)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_FWD_URGENCY(x)  VTSS_EXTRACT_BITFIELD(x,9,8)

/** 
 * \brief
 * Enable yellow traffic to use reserved ingress space.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . YEL_RSRVD
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_YEL_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

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
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE  VTSS_BIT(4)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_INGRESS_DROP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

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
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING  VTSS_BIT(3)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_IGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING  VTSS_BIT(2)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_EGR_NO_SHARING(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

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
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE  VTSS_BIT(1)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_DROP_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set this to clear (port) and (port,qos) reservations for the destination
 * port. This is required to be able to move queues between ports.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE . EGRESS_RSRV_DIS
 */
#define  VTSS_F_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_RSRV_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_RSRV_DIS  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_EGRESS_RSRV_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SE resource mode
 *
 * \details
 * Register: \a QFWD:SYSTEM:RES_SE_CFG
 *
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 */
#define VTSS_QFWD_SYSTEM_RES_SE_CFG(ri)      VTSS_IOREG(VTSS_TO_QFWD,0x110f + (ri))

/** 
 * \brief
 * Configures the resource mode for destination memory tracking. When
 * cleared frames are using resources per (port,priority). When watermark
 * for that resources is reached, the resources for the port are used, and
 * by the shared resources if also no port resource is available.
 * When set, frames are using resources for the scheduling element they are
 * enqueued to, then by the port, and then by the shared resources. If this
 * mode is used for a port, no (port,prio) resource will be granted. Frames
 * discarded only due to the SE resource being depleted cannot be discarded
 * in parallel for multicast discards.
 * 
 * Watermarks for SEs must not be changed when data is available in them.
 *
 * \details 
 * 0: Reserve memory per priority and port
 * 1: Reserve memory per scheduling element
 *
 * Field: ::VTSS_QFWD_SYSTEM_RES_SE_CFG . RES_SE_RSRVD
 */
#define  VTSS_F_QFWD_SYSTEM_RES_SE_CFG_RES_SE_RSRVD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_RES_SE_CFG_RES_SE_RSRVD  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_RES_SE_CFG_RES_SE_RSRVD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Statistics configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:STAT_CNT_CFG
 */
#define VTSS_QFWD_SYSTEM_STAT_CNT_CFG        VTSS_IOREG(VTSS_TO_QFWD,0x111e)

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
 * \brief Forwarder mischeleaneous configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_CTRL
 */
#define VTSS_QFWD_SYSTEM_FWD_CTRL            VTSS_IOREG(VTSS_TO_QFWD,0x111f)

/** 
 * \brief
 * The maximum number of clock cycles between guaranteed CSR access to
 * res_stat counters.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_CTRL . FWD_IDLE_CNT
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_CTRL_FWD_IDLE_CNT(x)  VTSS_ENCODE_BITFIELD(x,1,13)
#define  VTSS_M_QFWD_SYSTEM_FWD_CTRL_FWD_IDLE_CNT     VTSS_ENCODE_BITMASK(1,13)
#define  VTSS_X_QFWD_SYSTEM_FWD_CTRL_FWD_IDLE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,1,13)

/** 
 * \brief
 * Await an afi busy phase between enqueings to the AFI controller
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_CTRL . FWD_AFI_HANDSHAKE
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x1120 + (ri))

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
 * resources are allocated, so it may be relevant to also set
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
#define VTSS_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG  VTSS_IOREG(VTSS_TO_QFWD,0x112c)

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
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 */
#define VTSS_QFWD_SYSTEM_FWD_DROP_EVENTS(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x112d + (ri))

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
#define VTSS_QFWD_SYSTEM_FWD_CPU_DROP_CNT    VTSS_IOREG(VTSS_TO_QFWD,0x113c)

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
#define VTSS_QFWD_SYSTEM_FWD_PRESS_DROP_CNT  VTSS_IOREG(VTSS_TO_QFWD,0x113d)

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
#define VTSS_QFWD_SYSTEM_FWD_STAT_CNT(ri)    VTSS_IOREG(VTSS_TO_QFWD,0x113e + (ri))

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
#define VTSS_QFWD_SYSTEM_MIRROR_CFG          VTSS_IOREG(VTSS_TO_QFWD,0x1141)

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
#define VTSS_QFWD_SYSTEM_CPUQ_DISCARD        VTSS_IOREG(VTSS_TO_QFWD,0x1142)

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
 * \brief Basic port mode for scheduling hierarchy
 *
 * \details
 * All ports have their own scheduling hierarchy defined, consisting of a
 * part for nonservice frames defined as frames having queing group
 * classified to 0, and a part for the rest. The two parts can be 
 * identical if needed, in which case the modes for service and non service
 * must have the same setting.
 *
 * Register: \a QFWD:SYSTEM:QMAP_PORT_MODE
 *
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-10
 */
#define VTSS_QFWD_SYSTEM_QMAP_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x1143 + (ri))

/** 
 * \brief
 * Scheduling mode for frames classified to queing group /=0 (service
 * frames).
 * 
 * In NORMAL mode, the queue number is looked up in the map tables at index
 * 128+qos_value.
 * 
 * In GROUP mode, a scheduling element is assigned per queueing group, with
 * 8 queues attached. The queue number is looked up in the tables at index
 * qgrp.
 * 
 * In MBH mode, the qos is looked up at index qgrp, and the scheduling
 * index is looked up at index "(grp and not 0xf) + qos_value".
 * 
 * A minimum hierachy also exist. It corresponds to GROUP mode, but the
 * qgrp is regarded zero in the mapping. 
 *
 * \details 
 * 0: Normal mode
 * 1: Hier mode
 * 2: Mbh mode
 * 3: Mini mode

 *
 * Field: ::VTSS_QFWD_SYSTEM_QMAP_PORT_MODE . QMAP_MODE_SERVICE
 */
#define  VTSS_F_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_SERVICE(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_SERVICE     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_SERVICE(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Same function as for QMAP_MODE_SERVICE, except this mode is for qgrp=0
 * frames.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_QMAP_PORT_MODE . QMAP_MODE_NONSERVICE
 */
#define  VTSS_F_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QFWD_SYSTEM_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a QFWD:QMAP_SE_TBL
 *
 * Select scheduling modes
 */


/** 
 * \brief Per port mapping of qgrp
 *
 * \details
 * Register: \a QFWD:QMAP_SE_TBL:QMAP_SE_TBL
 *
 * @param gi Replicator: x_GAZ_CORE_QMAP_CNT (??), 0-135
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-10
 */
#define VTSS_QFWD_QMAP_SE_TBL_QMAP_SE_TBL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x3000,gi,16,ri,0)

/** 
 * \brief
 * Scheduling element to use for frames going to the specific port with the
 * specific lookup index
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_SE_TBL_QMAP_SE_TBL . QMAP_SE_VAL
 */
#define  VTSS_F_QFWD_QMAP_SE_TBL_QMAP_SE_TBL_QMAP_SE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_QFWD_QMAP_SE_TBL_QMAP_SE_TBL_QMAP_SE_VAL     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_QFWD_QMAP_SE_TBL_QMAP_SE_TBL_QMAP_SE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a QFWD:QMAP_QOS_TBL
 *
 * Select scheduling modes
 */


/** 
 * \brief Per port mapping of qgrp
 *
 * \details
 * Register: \a QFWD:QMAP_QOS_TBL:QMAP_QOS_TBL
 *
 * @param gi Replicator: x_GAZ_CORE_QMAP_CNT (??), 0-135
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-10
 */
#define VTSS_QFWD_QMAP_QOS_TBL_QMAP_QOS_TBL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x0,gi,32,ri,0)

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
 * Field: ::VTSS_QFWD_QMAP_QOS_TBL_QMAP_QOS_TBL . QMAP_QOS_SEL
 */
#define  VTSS_F_QFWD_QMAP_QOS_TBL_QMAP_QOS_TBL_QMAP_QOS_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QFWD_QMAP_QOS_TBL_QMAP_QOS_TBL_QMAP_QOS_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QFWD_QMAP_QOS_TBL_QMAP_QOS_TBL_QMAP_QOS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Per egress port mapping of qgrp to drop stat index
 *
 * \details
 * Register: \a QFWD:QMAP_QOS_TBL:DROP_STAT_CTRL
 *
 * @param gi Replicator: x_GAZ_CORE_QMAP_CNT (??), 0-135
 * @param ri Replicator: x_GAZ_CORE_ETHPORT_CNT (??), 0-10
 */
#define VTSS_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x0,gi,32,ri,11)

/** 
 * \brief
 * Drop counter set base address.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL . DROP_STAT_BASE_ADDR
 */
#define  VTSS_F_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR(x)  VTSS_ENCODE_BITFIELD(x,12,10)
#define  VTSS_M_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR     VTSS_ENCODE_BITMASK(12,10)
#define  VTSS_X_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_BASE_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,12,10)

/** 
 * \brief
 * Configures which OAM is counted in the from stat counter.
 * 
 * Ref: ANA_L2:ISDX:QGRP_CFG.QGRP_OAM_TYPE
 *
 * \details 
 * bit0: Enable / disable drop count of EVC MEP OAM
 * bit1: Enable / disable drop count of OVC / PW MEP OAM
 * bit2: Enable / disable drop count of DOWN MEP OAM
 *
 * Field: ::VTSS_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL . DROP_STAT_OAM_CNT_SEL
 */
#define  VTSS_F_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_OAM_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

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
 * Field: ::VTSS_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL . DROP_STAT_COS_SEL
 */
#define  VTSS_F_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_SEL     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * Ingress service counter set assignment per COS ID. Setting bit n makes
 * cos n the last contributer to a counter. The counter in use for frames
 * with cos C will therefore be counted at the base index + number-of-ones
 * below C in this mask. Examples: 00...0: All cos values are counted at
 * the same index. 11....1: All cos values are counted at their own index.
 * 0101010: Cos 0+1, 2+3, 4+5 and 6+7.
 *
 * \details 
 * Field: ::VTSS_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL . DROP_STAT_COS_MAP
 */
#define  VTSS_F_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_MAP(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_MAP     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_QFWD_QMAP_QOS_TBL_DROP_STAT_CTRL_DROP_STAT_COS_MAP(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a QFWD:QLIMIT_QUEUE
 *
 * Queue Size Table
 */


/** 
 * \brief Current queue size
 *
 * \details
 * Register: \a QFWD:QLIMIT_QUEUE:QUEUE_SIZE
 *
 * @param gi Replicator: x_GAZ_CORE_QUEUE_CNT (??), 0-3357
 */
#define VTSS_QFWD_QLIMIT_QUEUE_QUEUE_SIZE(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x2000,gi,1,0,0)

/** 
 * \brief
 * Current size of queue used for queue size limitation
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_QUEUE_QUEUE_SIZE . QUEUE_SIZE
 */
#define  VTSS_F_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_SIZE(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_SIZE     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_SIZE(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/** 
 * \brief
 * This queue was have had one or more discards due to the queue limitation
 * algorithm
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_QUEUE_QUEUE_SIZE . QUEUE_KILLED
 */
#define  VTSS_F_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_KILLED(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_KILLED  VTSS_BIT(0)
#define  VTSS_X_QFWD_QLIMIT_QUEUE_QUEUE_SIZE_QUEUE_KILLED(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QFWD:QLIMIT_PORT
 *
 * Queue Limitation Configuration
 */


/** 
 * \brief Queue Limitation Configuration
 *
 * \details
 * Replication 0-7 used for service traffic, 8-15 for nonservice traffic.
 *
 * Register: \a QFWD:QLIMIT_PORT:QLIMIT_PORT_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 * @param ri Register: QLIMIT_PORT_CFG (??), 0-15
 */
#define VTSS_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x114e,gi,17,ri,0)

/** 
 * \brief
 * Index of shared resource to use
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG . QLIMIT_SHR_VAL
 */
#define  VTSS_F_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Usage mode for queues in the shared area
 *
 * \details 
 * 0: Queue limitation based on individual queues
 * 1: Queue limitation based on queue on same small element
 * 2: Queue limitation based on queues on same large element
 * 3: Reserved

 *
 * Field: ::VTSS_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG . QLIMIT_SHR_MODE
 */
#define  VTSS_F_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_QFWD_QLIMIT_PORT_QLIMIT_PORT_CFG_QLIMIT_SHR_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Queue Limitation Configuration
 *
 * \details
 * Disabling queue limitation per port.
 *
 * Register: \a QFWD:QLIMIT_PORT:QLIMIT_DIS_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_PORT_CNT (??), 0-14
 */
#define VTSS_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x114e,gi,17,0,16)

/** 
 * \brief
 * Disable queue limitation for the port. If either queue limitation is
 * disabled for the source port, or for the destination port, the queue
 * limitation algorithm is bypassed.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG . QLIMIT_IGR_DIS
 */
#define  VTSS_F_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS  VTSS_BIT(1)
#define  VTSS_X_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_IGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Disable queue limitation for the port. If either queue limitation is
 * disabled for the source port, or for the destination port, the queue
 * limitation algorithm is bypassed.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG . QLIMIT_EGR_DIS
 */
#define  VTSS_F_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS  VTSS_BIT(0)
#define  VTSS_X_QFWD_QLIMIT_PORT_QLIMIT_DIS_CFG_QLIMIT_EGR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a QFWD:QLIMIT_SHR
 *
 * Shared memory pool configuration
 */


/** 
 * \brief Maximum size of shared area
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_SHR_TOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 * @param ri Register: QLIMIT_SHR_TOP_CFG (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,ri,0)

/** 
 * \brief
 * When total consumption of a shared area exceeds this level, all queues
 * belonging to the area starts tail dropping
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG . QLIMIT_SHR_TOP
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_SHR_TOP_CFG_QLIMIT_SHR_TOP(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Maximum congested size of shared area
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_SHR_ATOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 * @param ri Register: QLIMIT_SHR_ATOP_CFG (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,ri,2)

/** 
 * \brief
 * When less than this amount of memory is left before TOP is reached, all
 * active queues are tail dropping.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG . QLIMIT_SHR_ATOP
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_SHR_ATOP_CFG_QLIMIT_SHR_ATOP(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Maximum congested size of shared area
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_SHR_CTOP_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 * @param ri Register: QLIMIT_SHR_CTOP_CFG (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,ri,4)

/** 
 * \brief
 * When less than this amount of memory is left before TOP is reached, all
 * congested queues are tail dropping.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG . QLIMIT_SHR_CTOP
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_SHR_CTOP_CFG_QLIMIT_SHR_CTOP(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Maximum area use before queue limitation kicks in
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_SHR_QLIM_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 * @param ri Register: QLIMIT_SHR_QLIM_CFG (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,ri,6)

/** 
 * \brief
 * When less than this amount of memory is left before TOP is reached, all
 * queues are limited in size depending on number of congested queues.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG . QLIMIT_SHR_QLIM
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_SHR_QLIM_CFG_QLIMIT_SHR_QLIM(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Size of a congested queue
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_QUE_CONG_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,0,8)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG . QLIMIT_QUE_CONG
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_QUE_CONG_CFG_QLIMIT_QUE_CONG(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Size of an active queue
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_QUE_ACT_CFG
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,0,9)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG . QLIMIT_QUE_ACT
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG_QLIMIT_QUE_ACT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG_QLIMIT_QUE_ACT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_QUE_ACT_CFG_QLIMIT_QUE_ACT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Current value of dynamic watermark
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_DYN_WM_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 * @param ri Register: QLIMIT_DYN_WM_STAT (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_DYN_WM_STAT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,ri,10)

/** 
 * \brief
 * Current value of the maximum queue size allowed.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_DYN_WM_STAT . QLIMIT_DYN_WM
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_DYN_WM_STAT_QLIMIT_DYN_WM(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_DYN_WM_STAT_QLIMIT_DYN_WM     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_DYN_WM_STAT_QLIMIT_DYN_WM(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Current amount of congested queues in the share
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_CONG_CNT_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,0,12)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT . QLIMIT_CONG_CNT
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT(x)  VTSS_ENCODE_BITFIELD(x,13,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT     VTSS_ENCODE_BITMASK(13,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_CONG_CNT(x)  VTSS_EXTRACT_BITFIELD(x,13,13)

/** 
 * \brief
 * Return the current number of active queues in the share.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT . QLIMIT_ACT_CNT
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_ACT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_ACT_CNT     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_CONG_CNT_STAT_QLIMIT_ACT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Current use of the shared area
 *
 * \details
 * Register: \a QFWD:QLIMIT_SHR:QLIMIT_SHR_FILL_STAT
 *
 * @param gi Replicator: x_GAZ_CORE_QLIM_SHR_CNT (??), 0-31
 */
#define VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_FILL_STAT(gi)  VTSS_IOREG_IX(VTSS_TO_QFWD,0x124d,gi,14,0,13)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_SHR_QLIMIT_SHR_FILL_STAT . QLIMIT_SHR_FILL
 */
#define  VTSS_F_QFWD_QLIMIT_SHR_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_SHR_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_SHR_QLIMIT_SHR_FILL_STAT_QLIMIT_SHR_FILL(x)  VTSS_EXTRACT_BITFIELD(x,0,13)

/**
 * Register Group: \a QFWD:QLIMIT_MON
 *
 * Shared memory pool monitoring
 */


/** 
 * \brief Monitor configuration
 *
 * \details
 * Replicated for each classified priority
 *
 * Register: \a QFWD:QLIMIT_MON:QLIMIT_MON_CFG
 */
#define VTSS_QFWD_QLIMIT_MON_QLIMIT_MON_CFG  VTSS_IOREG(VTSS_TO_QFWD,0x140d)

/** 
 * \brief
 * Selected share to monitor
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_MON_QLIMIT_MON_CFG . QLIMIT_SHR_MON_SEL
 */
#define  VTSS_F_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_SEL     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/** 
 * \brief
 * Clear lowest dynamic watermark value
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_MON_QLIMIT_MON_CFG . QLIMIT_SHR_MON_CLR
 */
#define  VTSS_F_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR  VTSS_BIT(0)
#define  VTSS_X_QFWD_QLIMIT_MON_QLIMIT_MON_CFG_QLIMIT_SHR_MON_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Lowest value of dynamic watermark
 *
 * \details
 * Register: \a QFWD:QLIMIT_MON:QLIMIT_DYN_WM_LOW_STAT
 *
 * @param ri Register: QLIMIT_DYN_WM_LOW_STAT (??), 0-1
 */
#define VTSS_QFWD_QLIMIT_MON_QLIMIT_DYN_WM_LOW_STAT(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x140e + (ri))

/** 
 * \brief
 * Lowest value of the maximum queue size allowed.
 *
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_MON_QLIMIT_DYN_WM_LOW_STAT . QLIMIT_DYN_WM_LOW
 */
#define  VTSS_F_QFWD_QLIMIT_MON_QLIMIT_DYN_WM_LOW_STAT_QLIMIT_DYN_WM_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_MON_QLIMIT_DYN_WM_LOW_STAT_QLIMIT_DYN_WM_LOW     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_MON_QLIMIT_DYN_WM_LOW_STAT_QLIMIT_DYN_WM_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Current amount of congested queues in the share
 *
 * \details
 * Register: \a QFWD:QLIMIT_MON:QLIMIT_CONG_CNT_MAX_STAT
 */
#define VTSS_QFWD_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT  VTSS_IOREG(VTSS_TO_QFWD,0x1410)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT . QLIMIT_CONG_CNT_MAX
 */
#define  VTSS_F_QFWD_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_MON_QLIMIT_CONG_CNT_MAX_STAT_QLIMIT_CONG_CNT_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/** 
 * \brief Maximum use of the shared area
 *
 * \details
 * Register: \a QFWD:QLIMIT_MON:QLIMIT_SHR_FILL_MAX_STAT
 */
#define VTSS_QFWD_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT  VTSS_IOREG(VTSS_TO_QFWD,0x1411)

/** 
 * \details 
 * Field: ::VTSS_QFWD_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT . QLIMIT_SHR_FILL_MAX
 */
#define  VTSS_F_QFWD_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_QFWD_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_QFWD_QLIMIT_MON_QLIMIT_SHR_FILL_MAX_STAT_QLIMIT_SHR_FILL_MAX(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


#endif /* _VTSS_SERVALT_REGS_QFWD_H_ */
