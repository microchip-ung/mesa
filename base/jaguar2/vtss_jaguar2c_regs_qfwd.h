#ifndef _VTSS_JAGUAR2C_REGS_QFWD_H_
#define _VTSS_JAGUAR2C_REGS_QFWD_H_

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

#include "vtss_jaguar2c_regs_common.h"

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
 * @param ri Replicator: x_GAZ_CORE_PORT_CNT (??), 0-56
 */
#define VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x0 + (ri))

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
 * \brief Forwarder mischeleaneous configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_CTRL
 */
#define VTSS_QFWD_SYSTEM_FWD_CTRL            VTSS_IOREG(VTSS_TO_QFWD,0x39)

/** 
 * \brief
 * Await an afi busy phase between enqueings to the AFI controller
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_CTRL . FWD_AFI_HANDSHAKE
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE  VTSS_BIT(1)
#define  VTSS_X_QFWD_SYSTEM_FWD_CTRL_FWD_AFI_HANDSHAKE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Process only one discard per cycle, required for egress drop statistics
 * mode. Side effect is a slower processing of multiple drops on the same
 * frame, causing potential head-of-line blocking.
 *
 * \details 
 * Field: ::VTSS_QFWD_SYSTEM_FWD_CTRL . DROP_SINGLE
 */
#define  VTSS_F_QFWD_SYSTEM_FWD_CTRL_DROP_SINGLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_QFWD_SYSTEM_FWD_CTRL_DROP_SINGLE  VTSS_BIT(0)
#define  VTSS_X_QFWD_SYSTEM_FWD_CTRL_DROP_SINGLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


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
#define VTSS_QFWD_SYSTEM_FRAME_COPY_CFG(ri)  VTSS_IOREG(VTSS_TO_QFWD,0x3a + (ri))

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
#define VTSS_QFWD_SYSTEM_FRAME_COPY_LRNA_CFG  VTSS_IOREG(VTSS_TO_QFWD,0x46)

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
 * \brief Counter for number of frames forwarding aborted due to forward pressure
 *
 * \details
 * Register: \a QFWD:SYSTEM:FWD_PRESS_DROP_CNT
 */
#define VTSS_QFWD_SYSTEM_FWD_PRESS_DROP_CNT  VTSS_IOREG(VTSS_TO_QFWD,0x47)

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
 * \brief Mirroring configuration
 *
 * \details
 * Register: \a QFWD:SYSTEM:MIRROR_CFG
 */
#define VTSS_QFWD_SYSTEM_MIRROR_CFG          VTSS_IOREG(VTSS_TO_QFWD,0x48)

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
#define VTSS_QFWD_SYSTEM_CPUQ_DISCARD        VTSS_IOREG(VTSS_TO_QFWD,0x49)

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


#endif /* _VTSS_JAGUAR2C_REGS_QFWD_H_ */
