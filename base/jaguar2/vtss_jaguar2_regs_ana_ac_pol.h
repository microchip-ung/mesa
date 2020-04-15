#ifndef _VTSS_JAGUAR2_REGS_ANA_AC_POL_H_
#define _VTSS_JAGUAR2_REGS_ANA_AC_POL_H_

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
 * Target: \a ANA_AC_POL
 *
 * Controls the various policers.
 *
 ***********************************************************************/

/**
 * Register Group: \a ANA_AC_POL:POL_ALL_CFG
 *
 * Various policer controls
 */


/** 
 * \brief Configuration of STORM policer rates
 *
 * \details
 * These registers configure the rates of the STORM policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8fc8 + (ri))

/** 
 * \brief
 * Storm policer leaky bucket rate. Unit is 25040 bps.
 *
 * \details 
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is disabled, policing is
 * performed in bits per second (bps). Policing rate is configured in units
 * of 25040 bps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 25040 bps
 * n: Rate = n x 25040 bps
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is enabled, policing is
 * performed in frames per second (fps). Policing rate is configured in
 * units of 10 fps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 10 fps
 * n: Rate = n*10 fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG . STORM_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


/** 
 * \brief Configuration of STORM policer thresholds
 *
 * \details
 * These registers configure the thresholds of the STORM policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_THRES_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8fd0 + (ri))

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192 bytes.
 *
 * \details 
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is enabled burst capacity is
 * configured in steps of 8192/2504 frames.
 * 0: Always closed
 * 1: Burst capacity = 1 x 8192/2504 frames
 * n: Burst capacity = n x 8192/2504 frames
 * 63: Burst capacity = 206 frames
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG . STORM_THRES
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG_STORM_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG_STORM_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG_STORM_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of storm policers
 *
 * \details
 * This register configures the storm policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_CTRL
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8fd8 + (ri))

/** 
 * \brief
 * Enables frame rate mode for the storm policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details 
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL . STORM_FRAME_RATE_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA  VTSS_BIT(18)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Controls policing of frames to the individual CPU queues for the port
 * policer. If a bit is set in this mask, frames to the corresponding CPU
 * queue are allowed to be policed (frames may get discarded and the bucket
 * is updated with the frame).
 *
 * \details 
 * '00..00': Disable policing of frames to all CPU queues
 * 'xx..x1 ': Allow policing of frames to CPU queue #0
 *     ...
 * '1x..xx' : Allow policing of frames to CPU queue #n
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL . STORM_CPU_QU_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * Enables removing the front ports from a policed frame's destination set.
 *
 * \details 
 * 0: The policer does not remove the front ports from the destination set
 * for a policed frame.
 * 0: The policer removes the front ports from the destination set for a
 * policed frame.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL . STORM_LIMIT_NONCPU_TRAFFIC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enables removing the CPU ports from a policed frame's destination set.
 *
 * \details 
 * 0: The policer does not remove the CPU ports from the destination set
 * for a policed frame.
 * 1: The policer removes the CPU ports from the destination set for a
 * policed frame.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL . STORM_LIMIT_CPU_TRAFFIC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Configures the traffic types to be policed by the policer. Each bit in
 * the mask enables a specific frame type. Multiple types can be enabled at
 * the same time. If the CPU queue bit is set, traffic to CPU queues
 * specified in CPU_QU_MASK are not policed.
 * If the CPU queue bit is cleared, frames destined for CPU queues
 * specified in CPU_QU_MASK bypass the policer even though the frames are
 * of a type marked elsewhere in TRAFFIC_TYPE_MASK. 
 * A frame can belong to multiple traffic types (for instance flooding and
 * multicast). If a frame type is not set in the mask, the frames of that
 * type only, bypass the policer (never discarded and the bucket is not
 * updated with the frame).

 *
 * \details 
 * 'xxxxxxx1' : Known multicast frames are policed. 
 * 'xxxxxx1x' : Known broadcast frames are policed.
 * 'xxxxx1xx' : Known unicast frames are policed. 
 * 'xxxx1xxx' : Unknown multicast frames are policed. 
 * 'xxx1xxxx' : Unknown broadcast frames are policed.
 * 'xx1xxxxx' : Unknown unicast frames are policed. 
 * 'x0xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK bypass the
 * policer.
 * 'x1xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK are policed.
 * '1xxxxxxx' : Learn frames are policed.
 * '00000000': Disable policer.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL . STORM_TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Configuration of ACL policer rates
 *
 * \details
 * These registers configure the rates of the ACL policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8fe0 + (ri))

/** 
 * \brief
 * ACL policer leaky bucket rate. Unit is 25040 bps.
 *
 * \details 
 * When POL_ACL_CTRL.FRAME_RATE_ENA is disabled, policing is performed in
 * bits per second (bps). Policing rate is configured in units of 25040
 * bps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 25040 bps
 * n: Rate = n x 25040 bps
 * When POL_ACL_CTRL.FRAME_RATE_ENA is enabled, policing is performed in
 * frames per second (fps). Policing rate is configured in units of 10 fps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 10 fps
 * n: Rate = n*10 fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG . ACL_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


/** 
 * \brief Configuration of ACL policer thresholds
 *
 * \details
 * These registers configure the thresholds of the ACL policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_THRES_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x9000 + (ri))

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192 bytes.
 *
 * \details 
 * When POL_ACL_CTRL.FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * When POL_ACL_CTRL.FRAME_RATE_ENA is enabled burst capacity is configured
 * in steps of 8192/2504 frames.
 * 0: Always closed
 * 1: Burst capacity = 1 x 8192/2504 frames
 * n: Burst capacity = n x 8192/2504 frames
 * 63: Burst capacity = 206 frames
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG . ACL_THRES
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_ACL_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_ACL_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_ACL_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Configuration of ACL policers
 *
 * \details
 * These registers configure the basic behavior of the ACL policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_CTRL
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-31
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x9020 + (ri))

/** 
 * \brief
 * Configuration of Drop Precedence bypass level. Frames with DP below
 * DP_BYPASS_LVL bypass the policer (frames are never policed and the
 * bucket is not updated with the frames).
 *
 * \details 
 * 0: No frames bypass the policer
 * 1: Frames with DP = 0 bypass the policer
 * 2: Frames with DP = 0 or 1 bypass the policer
 * 3: Frames with DP = 0, 1 or 2 bypass the policer
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL . DP_BYPASS_LVL
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.
 * When GAP_VALUE = 20, a line-rate measurement because each frame occupies
 * 12 bytes for the inter-frame gap and 8 bytes for the preamble on the
 * line. When GAP_VALUE = 0, a data-rate measurement is achived.
 *
 * \details 
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL . GAP_VALUE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_GAP_VALUE(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_GAP_VALUE     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_GAP_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * Configures the traffic types to be policed by the policer. Each bit in
 * the mask enables a specific frame type.
 * If a frame type is not set in the mask, the frames of that type only,
 * bypass the policer (never discarded and the bucket is not updated with
 * the frame).

 *
 * \details 
 * 0: Reserved (Policer disabled).
 * 1 : Only frames to front ports are triggering policer and only front
 * port destinations are policed.
 * 2 : Frames to CPU are triggering policer and only CPU destinations are
 * policed.
 * 3 : Frames to front ports and/or CPU are triggering policer and being
 * policed.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL . ACL_TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enables frame rate mode for the ACL policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details 
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL . FRAME_RATE_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_FRAME_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of port policer flow control
 *
 * \details
 * These registers configure flow control for the port policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_PORT_FC_CFG
 *
 * @param ri Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-56
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x9040 + (ri))

/** 
 * \brief
 * Current flow control state for the port policer.
 *
 * \details 
 * 0: Flow control is inactive
 * 1: Flow control is active
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG . FC_STATE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_STATE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_STATE  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_STATE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enables flow control mode for the port policer. If set, pause frames are
 * transmitted when the configured policer threshold is exceeded. If
 * cleared, frames exceeding the configured policer threshold are
 * discarded.
 * POL_ALL_CFG.PORT_FC_ENA must also be set to generate pause frames. In
 * order to generate pause frames, the DSM must be configured for flow
 * control.
 *
 * \details 
 * 0: Discard mode
 * 1: Flow control mode
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG . FC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Global configuration of policers
 *
 * \details
 * The register configures the basic behavior of all policers in the device
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ALL_CFG
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x9079)

/** 
 * \brief
 * Enables subtraction of the DP from the priority. This enables logging of
 * differently colored frames in different log files when using the ANA
 * testbench.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . DBG_DP_CHG_PRIO_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.
 * When GAP_VALUE = 20, a line-rate measurement because each frame occupies
 * 12 bytes for the inter-frame gap and 8 bytes for the preamble on the
 * line. When GAP_VALUE = 0, a data-rate measurement is achived.
 *
 * \details 
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_GAP_VALUE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/** 
 * \brief
 * Ignore DP level and yous count based on SDLB color.
 *
 * \details 
 * 0: DP level determines color
 * 1: SDLB determines color
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . USE_SDLB_COLOR_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_USE_SDLB_COLOR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_USE_SDLB_COLOR_ENA  VTSS_BIT(20)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_USE_SDLB_COLOR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Determines the mapping between internal DP value and the color used by
 * ISDX counters.
 *
 * \details 
 * 0: DP level will be counted as GREEN
 * 1: DP level will be counted as YELLOW
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . DP_TO_COLOR_MAP
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Enables overall signaling of flow control from the port policers to DSM.
 * Each port policers can enable flow control in POL_PORT_FC_CFG.FC_ENA.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PORT_FC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enables operation of port policers in parallel.
 *
 * \details 
 * 0: Port policer operates in serial mode. In serial mode, each of the
 * active port policers within a port are checked one after another. If a
 * frame is discarded by a policer, the frame is not passed on to
 * subsequent policers.
 * 1: Port policer operates in parallel mode. In parallel mode, each of the
 * active port policers within a port operate on all frames (policing and
 * bucket updates) even though one or more policers might be closed.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PORT_POL_IN_PARALLEL_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If set, all STORM policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.

 *
 * \details 
 * 0: Normal operation
 * 1: All ACL policer buckets are closed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_FORCE_CLOSE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * If set, all STORM policer buckets are forced open (no frames are policed
 * and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All ACL policer buckets are forced open
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_FORCE_OPEN
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * If set, all STORM policers are initialized and buckets are open. The bit
 * must be cleared for normal operation to resume.
 *
 * \details 
 * 0: Normal operation
 * 1: Initialization
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_FORCE_INIT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT  VTSS_BIT(10)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * If set, all priority policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All priority policer buckets are closed.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PRIO_FORCE_CLOSE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_CLOSE  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * If set, all priority policer buckets are forced open (no frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.

 *
 * \details 
 * 0: Normal operation
 * 1: All priority policer buckets are forced open
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PRIO_FORCE_OPEN
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_OPEN  VTSS_BIT(8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * If set, all priority policers are initialized and buckets are open. The
 * bit must be cleared for normal operation to resume.
 *
 * \details 
 * 0: Normal operation
 * 1: Initialization
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PRIO_FORCE_INIT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT  VTSS_BIT(7)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * If set, all ACL policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.

 *
 * \details 
 * 0: Normal operation
 * 1: All ACL policer buckets are closed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . ACL_FORCE_CLOSE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_CLOSE  VTSS_BIT(6)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * If set, all ACL policer buckets are forced open (no frames are policed
 * and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All ACL policer buckets are forced open
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . ACL_FORCE_OPEN
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_OPEN  VTSS_BIT(5)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * If set, all ACL policers are initialized and buckets are open. The bit
 * must be cleared for normal operation to resume.
 *
 * \details 
 * 0: Normal operation
 * 1: Initialization
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . ACL_FORCE_INIT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * If set, all port policer buckets are forced open (no frames are policed
 * and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All port policer buckets are forced ope
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . FORCE_OPEN
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_OPEN  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * If set, all port policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All port policer buckets are closed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . FORCE_CLOSE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_CLOSE  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * If set, the port policers operate on logical port numbers in stead of
 * physical port numbers.
 *
 * \details 
 * 0: Policing per physical port
 * 1: Policing per logical port
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . LPORT_POLICE_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_LPORT_POLICE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_LPORT_POLICE_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_LPORT_POLICE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * If set, all port policers are initialized and buckets are open. The bit
 * must be cleared for normal operation to resume.
 *
 * \details 
 * 0: Normal operation
 * 1: Initialization
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . FORCE_INIT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Policer Diagnostics
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STICKY
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x907a)

/** 
 * \brief
 * Set if a storm policer is active.
 *
 * \details 
 * 0: No event has occured
 * 1: Storm policer is active (frames added to leaky buckets)
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Set if a storm policer has removed the front ports from a frame's
 * destination set due to policing. 
 *
 * \details 
 * 0: No event has occured
 * 1: A storm policer has removed the front ports from a frame's
 * destination set due to policing
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_DROP_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY  VTSS_BIT(21)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set if a storm policer has removed the CPU ports from a frame's
 * destination set due to policer
 *
 * \details 
 * 0: No event has occured
 * 1: A storm policer has removed the CPU ports from a frame's destination
 * set due to policing
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_DROP_CPU_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY  VTSS_BIT(20)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set if a Service policer has been bypassed due to a Pipeline point.
 *
 * \details 
 * 0: No event has occured
 * 1: policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_DLB_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY  VTSS_BIT(19)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set if frame has been dropped by a DLB policer.
 *
 * \details 
 * 0: No event has occured
 * 1: DLB policer drop event has occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_DLB_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY  VTSS_BIT(18)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set if a priority policer has been bypassed due to a Pipeline point.
 *
 * \details 
 * 0: No event has occured
 * 1: policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY  VTSS_BIT(17)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set if a priority policer is active.
 *
 * \details 
 * 0: No event has occured
 * 1: Priority policer is active (frames added to leaky buckets)
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set if frame has been dropped due to priority policer.
 *
 * \details 
 * 0: No event has occured
 * 1: PRIO policer drop event has occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set if a priority policer has been bypassed due to a frame's DP level.
 *
 * \details 
 * 0: No event has occured
 * 1: Priority policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if an ACL policer has been bypassed due to a Pipeline point.
 *
 * \details 
 * 0: No event has occured
 * 1: policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if an ACL policer is active.
 *
 * \details 
 * 0: No event has occured
 * 1: ACL policer is active (frames added to leaky buckets)
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set if frame has been dropped due to ACL policer.
 *
 * \details 
 * 0: No event has occured
 * 1: ACL policer drop event has occured
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set if an ACL policer has been bypassed due to a frame's DP level.
 *
 * \details 
 * 0: No event has occured
 * 1: ACL policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY  VTSS_BIT(10)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set if an Port policer has been bypassed due to a Pipeline point.
 *
 * \details 
 * 0: No event has occured
 * 1: policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if a port policer is active.
 *
 * \details 
 * 0: No event has occured
 * 1: Port policer is active (frames added to leaky buckets)
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Set if a port policer's flow control state has been cleared.
 *
 * \details 
 * 0: No event has occured
 * 1: Port policer flow control state has been cleared
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_FC_CLEAR_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if a flow control has been active for a port policer.
 *
 * \details 
 * 0: No event has occured
 * 1: Port policer flow control has been activated
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_FC_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if a port policer has removed the front ports from a frame's
 * destination set due to policing. 
 *
 * \details 
 * 0: No event has occured
 * 1: A port policer has removed the front ports from a frame's destination
 * set due to policing
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_DROP_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if a port policer has removed the CPU ports from a frame's
 * destination set due to policer
 *
 * \details 
 * 0: No event has occured
 * 1: A port policer has removed the CPU ports from a frame's destination
 * set due to policing
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_DROP_CPU_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if a port policer has been bypassed due to a frame's DP level.
 *
 * \details 
 * 0: No event has occured
 * 1: Port policer has been bypassed
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC_POL:POL_PORT_CFG
 *
 * Port policer controls
 */


/** 
 * \brief Port policer upper threshold configuration
 *
 * \details
 * These registers configure the upper thresholds of the port policers. The
 * registers are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_THRES_CFG_0
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-227
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8000 + (ri))

/** 
 * \brief
 * Threshold size for port policer (burst capacity).
 *
 * \details 
 * When POL_PORT_CFG.FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * When POL_PORT_CFG.FRAME_RATE_ENA is enabled burst capacity is configured
 * in steps of 8192/2504 frames.
 * 0: Always closed
 * 1: Burst capacity = 1 x 8192/2504 frames
 * n: Burst capacity = n x 8192/2504 frames
 * 63: Burst capacity = 206 frames
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0 . PORT_THRES0
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0_PORT_THRES0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0_PORT_THRES0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0_PORT_THRES0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Port policer lower threshold configuration
 *
 * \details
 * These registers configure the lower thresholds of the port policers. The
 * registers are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_THRES_CFG_1
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-227
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8100 + (ri))

/** 
 * \brief
 * Hysteresis size for port policer. Unit is 8192 bytes. PORT_THRES1 is
 * used when a port policer is in flow control mode. Flow control is
 * asserted when the bucket level exceeds PORT_THRES0. Flow control is
 * deasserted when the bucket has leaked PORT_THRES1 bytes since the
 * assertion. PORT_THRES1 must be programmed smaller or equal to
 * PORT_THRES0.
 *
 * \details 
 * 0 : No hysteresis
 * 1: Deassert flow control when bucket has leaked 8192 bytes
 * ...
 * n: Deassert flow control when bucket has leaked n * 8192 bytes

 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1 . PORT_THRES1
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1_PORT_THRES1(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1_PORT_THRES1     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1_PORT_THRES1(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Port policer rate configuration
 *
 * \details
 * These registers configure the rates of the port policers. The registers
 * are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-227
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8200 + (ri))

/** 
 * \brief
 * Port policer leaky bucket rate.
 *
 * \details 
 * When POL_PORT_CFG.FRAME_RATE_ENA is disabled, policing is performed in
 * bits per second (bps). Policing rate is configured in units of 25040
 * bps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 25040 bps
 * n: Rate = n x 25040 bps
 * When POL_PORT_CFG.FRAME_RATE_ENA is enabled, policing is performed in
 * frames per second (fps). Policing rate is configured in units of 10 fps.
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 10 fps
 * n: Rate = n*10 fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG . PORT_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a ANA_AC_POL:POL_PORT_CTRL
 *
 * Port policer controls indexed per port
 */


/** 
 * \brief Port policer GAP configuration
 *
 * \details
 * These registers configure the gap value for the port policers, which is
 * common for all port policers within a port
 *
 * Register: \a ANA_AC_POL:POL_PORT_CTRL:POL_PORT_GAP
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-56
 */
#define VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x8e00,gi,8,0,0)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.
 * When GAP_VALUE = 20, a line-rate measurement because each frame occupies
 * 12 bytes for the inter-frame gap and 8 bytes for the preamble on the
 * line. When GAP_VALUE = 0, a data-rate measurement is achived.
 *
 * \details 
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP . GAP_VALUE
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Port policer configuration
 *
 * \details
 * These registers configure the behavior of port policer.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CTRL:POL_PORT_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-56
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_LB_SET_SIZE (??), 0-3
 */
#define VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x8e00,gi,8,ri,1)

/** 
 * \brief
 * Controls policing of frames to the individual CPU queues for the port
 * policer. If a bit is set in this mask, frames to the corresponding CPU
 * queue are allowed to be policed (frames may get discarded and the bucket
 * is updated with the frame).
 *
 * \details 
 * '00..00': Disable policing of frames to all CPU queues
 * 'xx..x1 ': Allow policing of frames to CPU queue #0
 *     ...
 * '1x..xx' : Allow policing of frames to CPU queue #n
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . CPU_QU_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Configuration of Drop Precedence bypass level. Frames with DP below
 * DP_BYPASS_LVL bypass the policer (frames are never policed and the
 * bucket is not updated with the frames).
 *
 * \details 
 * 0: No frames bypass the policer
 * 1: Frames with DP = 0 bypass the policer
 * 2: Frames with DP = 0 or 1 bypass the policer
 * 3: Frames with DP = 0, 1 or 2 bypass the policer
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . DP_BYPASS_LVL
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enables frame rate mode for the port policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details 
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . FRAME_RATE_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enables removing the front ports from a policed frame's destination set.
 *
 * \details 
 * 0: The policer does not remove the front ports from the destination set
 * for a policed frame.
 * 0: The policer removes the front ports from the destination set for a
 * policed frame.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . LIMIT_NONCPU_TRAFFIC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA  VTSS_BIT(10)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Enables removing the CPU ports from a policed frame's destination set.
 *
 * \details 
 * 0: The policer does not remove the CPU ports from the destination set
 * for a policed frame.
 * 1: The policer removes the CPU ports from the destination set for a
 * policed frame.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . LIMIT_CPU_TRAFFIC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Configures the traffic types to be policed by the policer. Each bit in
 * the mask enables a specific frame type. Multiple types can be enabled at
 * the same time. If the CPU queue bit is set, traffic to CPU queues
 * specified in CPU_QU_MASK are not policed.
 * If the CPU queue bit is cleared, frames destined for CPU queues
 * specified in CPU_QU_MASK bypass the policer even though the frames are
 * of a type marked elsewhere in TRAFFIC_TYPE_MASK. 
 * A frame can belong to multiple traffic types (for instance flooding and
 * multicast). If a frame type is not set in the mask, the frames of that
 * type only, bypass the policer (never discarded and the bucket is not
 * updated with the frame).

 *
 * \details 
 * 'xxxxxxx1' : Known multicast frames are policed. 
 * 'xxxxxx1x' : Known broadcast frames are policed.
 * 'xxxxx1xx' : Known unicast frames are policed. 
 * 'xxxx1xxx' : Unknown multicast frames are policed. 
 * 'xxx1xxxx' : Unknown broadcast frames are policed.
 * 'xx1xxxxx' : Unknown unicast frames are policed. 
 * 'x0xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK bypass the
 * policer.
 * 'x1xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK are policed.
 * '1xxxxxxx' : Learn frames are policed.
 * '00000000': Disable policer.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a ANA_AC_POL:POL_PRIO_CFG
 *
 * Priority policer controls
 */


/** 
 * \brief Priority policer rate configuration
 *
 * \details
 * These registers configure the rates of the priority policers. The
 * registers are index queue index.
 *
 * Register: \a ANA_AC_POL:POL_PRIO_CFG:POL_PRIO_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_QU_TOT_NUM_LB (??), 0-455
 */
#define VTSS_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8400 + (ri))

/** 
 * \brief
 * Policer leaky bucket rate. Unit is 25040 bps.
 *
 * \details 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 25040 bps
 * n: Rate = n x 25040 bps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_RATE_CFG . PRIO_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_RATE_CFG_PRIO_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_RATE_CFG_PRIO_RATE     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_RATE_CFG_PRIO_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


/** 
 * \brief Priority policer threshold configuration
 *
 * \details
 * These registers configure the thresholds of the priority policers. The
 * registers uses per queue index.
 *
 * Register: \a ANA_AC_POL:POL_PRIO_CFG:POL_PRIO_THRES_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_QU_TOT_NUM_LB (??), 0-455
 */
#define VTSS_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_THRES_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8600 + (ri))

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192 bytes.
 *
 * \details 
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * ...
 * n: Burst capacity = n x 8192 bytes
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_THRES_CFG . PRIO_THRES
 */
#define  VTSS_F_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_THRES_CFG_PRIO_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_THRES_CFG_PRIO_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_ANA_AC_POL_POL_PRIO_CFG_POL_PRIO_THRES_CFG_PRIO_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a ANA_AC_POL:POL_PRIO_CTRL
 *
 * Priority policer configuration indexed per queue.
 */


/** 
 * \brief Priority policer GAP configuration
 *
 * \details
 * Register: \a ANA_AC_POL:POL_PRIO_CTRL:POL_PRIO_GAP
 *
 * @param gi Replicator: x_FFL_ANA_NUM_QU_POL (??), 0-455
 */
#define VTSS_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_GAP(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x8800,gi,2,0,0)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.
 * When GAP_VALUE = 20, a line-rate measurement because each frame occupies
 * 12 bytes for the inter-frame gap and 8 bytes for the preamble on the
 * line. When GAP_VALUE = 0, a data-rate measurement is achived.
 *
 * \details 
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_GAP . GAP_VALUE
 */
#define  VTSS_F_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_GAP_GAP_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_GAP_GAP_VALUE     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_GAP_GAP_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief Priority policer configuration
 *
 * \details
 * Register: \a ANA_AC_POL:POL_PRIO_CTRL:POL_PRIO_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_QU_POL (??), 0-455
 */
#define VTSS_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x8800,gi,2,0,1)

/** 
 * \brief
 * Configures the traffic types to be policed by the policer. Each bit in
 * the mask enables a specific frame type.
 * If a frame type is not set in the mask, the frames of that type only,
 * bypass the policer (never discarded and the bucket is not updated with
 * the frame).

 *
 * \details 
 * 0: Reserved (Policer disabled).
 * 1 : Only frames to front ports are triggering policer and only front
 * port destinations are policed.
 * 2 : Frames to CPU are triggering policer and only CPU destinations are
 * policed.
 * 3 : Frames to front ports and/or CPU are triggering policer and being
 * policed.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Configuration of Drop Precedence bypass level. Frames with DP below
 * DP_BYPASS_LVL bypass the policer (frames are never policed and the
 * bucket is not updated with the frames).
 *
 * \details 
 * 0: No frames bypass the policer
 * 1: Frames with DP = 0 bypass the policer
 * 2: Frames with DP = 0 or 1 bypass the policer
 * 3: Frames with DP = 0, 1 or 2 bypass the policer
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG . DP_BYPASS_LVL
 */
#define  VTSS_F_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_POL_POL_PRIO_CTRL_POL_PRIO_CFG_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a ANA_AC_POL:PORT_PT_CTRL
 *
 * Pipeline configuration indexed per port.
 */


/** 
 * \brief Configures stat and policer pipeline point per pipeline action
 *
 * \details
 * Configures pipeline location for the various stat and policer entity for
 * each pipeline action:
 * repl:0 Normal 
 * repl:1 INJECT
 * repl:2 EXTRACT
 * repl:3 EXTRACT UPMEP
 * repl:4 LOOPBACK
 *
 * Register: \a ANA_AC_POL:PORT_PT_CTRL:ACTION_CTRL
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PT_CTRL_IDX (??), 0-63
 * @param ri Register: ACTION_CTRL (??), 0-4
 */
#define VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x8c00,gi,8,ri,0)

/** 
 * \brief
 * Configures the pipeline point for SDLB policing and ISDX STAT handling.
 * 
 * When injecting or looping at a pipeline point after ISDX_PT will not
 * cause counter and SDLB policing.
 * 
 * When extracting at a pipeline point before ISDX_PT will not cause
 * counter and SDLB policing.
 *
 * \details 
 * 0: NONE
 * 1: ANA_VRAP
 * 2: ANA_PORT_VOE 
 * 3: ANA_CL
 * 4: ANA_CLM
 * 5: ANA_IPT_PROT 
 * 6: ANA_OU_MIP
 * 7: ANA_OU_SW
 * 8: ANA_OU_PROT
 * 9: ANA_OU_VOE
 * 10: ANA_MID_PROT
 * 11: ANA_IN_VOE
 * 12: ANA_IN_PROT
 * 13: ANA_IN_SW
 * 14: ANA_IN_MIP
 * 15: ANA_VLAN
 *
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . ISDX_PT
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_ISDX_PT(x)  VTSS_ENCODE_BITFIELD(x,14,4)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_ISDX_PT     VTSS_ENCODE_BITMASK(14,4)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_ISDX_PT(x)  VTSS_EXTRACT_BITFIELD(x,14,4)

/** 
 * \brief
 * Configures profile to always disable Port VOE LM updates.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . PVOE_DIS
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Configures profile to always disable Port stat updates.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . PSTAT_DIS
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Configures the pipeline point for Inner ACL policing and ACL STAT
 * handling. See ISDX_PT for description.
 *
 * \details 
 * See ISDX_PT encoding
 *
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . IN_ACL_PT
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_IN_ACL_PT(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_IN_ACL_PT     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_IN_ACL_PT(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Configures the pipeline point for Outer ACL policing and ACL STAT
 * handling. See ISDX_PT for description.
 *
 * \details 
 * See ISDX_PT encoding
 *
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . OU_ACL_PT
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_OU_ACL_PT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_OU_ACL_PT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_OU_ACL_PT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Configures the pipeline point for PORT policing and PORT STAT handling.
 * See ISDX_PT for description.
 *
 * \details 
 * See ISDX_PT encoding
 *
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . PORT_PT
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PORT_PT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PORT_PT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PORT_PT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a ANA_AC_POL:COMMON_SDLB
 *
 * Common DLB configuration and status registers
 */


/** 
 * \brief Configuration of common dual leaky bucket handling
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_SDLB:DLB_CTRL
 */
#define VTSS_ANA_AC_POL_COMMON_SDLB_DLB_CTRL  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8b90)

/** 
 * \brief
 * Specifies the number of clock cycles for a tick.
 *
 * \details 
 * 0: 1 clk
 * ...
 * n: 1+n clk
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_CTRL . BASE_TICK_CNT
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,13)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_BASE_TICK_CNT     VTSS_ENCODE_BITMASK(4,13)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,13)

/** 
 * \brief
 * Enables leaking from the dual leaky buckets.
 *
 * \details 
 * 0: Disable bucket leaking
 * 1: Enable bucket leaking
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_CTRL . LEAK_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_LEAK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_LEAK_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_LEAK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables adding of frame bytes to the dual leaky buckets.
 *
 * \details 
 * 0: Disable bucket addition
 * 1: Enable bucket addition
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_CTRL . DLB_ADD_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_DLB_ADD_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of common dual leaky bucket burst handling
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_SDLB:BURST_CTRL
 */
#define VTSS_ANA_AC_POL_COMMON_SDLB_BURST_CTRL  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8b91)

/** 
 * \brief
 * Configures MTU burst adjust for frames larger than one cell.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_BURST_CTRL . DLB_BURST_ADJ_VAL
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_VAL(x)  VTSS_ENCODE_BITFIELD(x,4,16)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_VAL     VTSS_ENCODE_BITMASK(4,16)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_VAL(x)  VTSS_EXTRACT_BITFIELD(x,4,16)

/** 
 * \brief
 * Configures testing frames larger than 1 cell against threshold - MTU.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_BURST_CTRL . DLB_BURST_ADJ_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_BURST_CTRL_DLB_BURST_ADJ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief DLB policer diagnostic
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_SDLB:DLB_STICKY
 */
#define VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x8b92)

/** 
 * \brief
 * Set when a DLB scan completes.
 *
 * \details 
 * 0: No event has occured
 * 1: Leak scan completes
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . LEAK_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Set when a DLB scan starts.
 *
 * \details 
 * 0: No event has occured
 * 1: Leak scan started
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . LEAK_SCAN_STARTED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY  VTSS_BIT(30)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Set when a DLB scan could not start because a scan is already ongoing -
 * BASE_TICK_CNT must be increased.
 *
 * \details 
 * 0: No event has occured
 * 1: Leak scan could not start at time
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . LEAK_START_DELAYED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY  VTSS_BIT(29)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Set when the frame rate is exceeding the Peak Information Rate.
 *
 * \details 
 * 0: No event has occured
 * 1: PIR exceeded
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . PIR_EXCEEDED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_PIR_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_PIR_EXCEEDED_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_PIR_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set when the frame rate is exceeding the Committed Information Rate.
 *
 * \details 
 * 0: No event has occured
 * 1: CIR exceeded
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . CIR_EXCEEDED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_EXCEEDED_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when the frame rate is below both the Committed Information Rate and
 * the Peak Information Rate.
 *
 * \details 
 * 0: No event has occured
 * 1: Traffic received without triggering CIR and PIR policing
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_SDLB_DLB_STICKY . CIR_PIR_OPEN_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_SDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC_POL:SDLB
 *
 * Dual leaky buckets
 */


/** 
 * \brief Configuration of DLB policer
 *
 * \details
 * Register: \a ANA_AC_POL:SDLB:DLB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-4095
 */
#define VTSS_ANA_AC_POL_SDLB_DLB_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,0,0)

/** 
 * \brief
 * Timestamp used for performing delta leaking.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . TIMESTAMP_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_TIMESTAMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,17,11)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_TIMESTAMP_VAL     VTSS_ENCODE_BITMASK(17,11)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_TIMESTAMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,17,11)

/** 
 * \brief
 * Enables leaky bucket coupling mode.
 * When operating in non coupled mode, yellow frames are bounded by Excess
 * Information Rate only.
 * When operating in coupled mode, yellow frames are bounded by Committed
 * Information Rate + Excess Information Rate
 * meaning that PIR bucket will also be be leaked with unused CIR rate
 * (when CIR bucket is empty)
 * 
 * This is only useful when color aware (see:COLOR_AWARE_LVL)
 *
 * \details 
 * 0: Uncoupled (PIR will only be leaked with PIR RATE_VAL)
 * 1: Coupled (PIR can be leaked with PIR RATE_VAL and unused CIR RATE_VAL)
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . COUPLING_MODE
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_COUPLING_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_COUPLING_MODE  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_COUPLING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Configuration of leaky bucket color awareness.
 * Frames with DP below or equal to level is treated as GREEN and use CIR
 * bandwidth before PIR bandwidth. Frames with DP above level are treated
 * as YELLOW and use PIR bandwidth.
 *
 * \details 
 * 0: DLB policer is color aware. Incoming frames with DP=0 are green and
 * frames with DP>0 are yellow. 
 * 1: DLB policer is color aware. Incoming frames with DP<=1 are green and
 * frames with DP>1 are yellow. 
 * 2: DLB policer is color aware. Incoming frames with DP<=2 are green and
 * frames with DP>2 are yellow. 
 * 3: DLB policer is color unaware. All incoming frames are green.
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . COLOR_AWARE_LVL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_COLOR_AWARE_LVL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Configuration of the drop precedence change for green frames being
 * remarked to yellow. The DP level for yellow frames is incremented with
 * CIR_INC_DP_VAL. 
 *
 * \details 
 * 0: DP is not increased.
 * n: DP is increased with n for PIR traffic.
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . CIR_INC_DP_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_CIR_INC_DP_VAL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Configures the traffic types to be policed by the policer. Each bit in
 * the mask enables policing of a specific frame type.

 *
 * \details 
 * 0: Reserved (Policer disabled).
 * 1 : Only front port destinations are policed.
 * 2 : Only CPU destinations are policed.
 * 3 : Both front ports and/or CPU destinations are being policed.
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Configures if stripped encapsulation data (normalized data) is policed
 * by the policer. 
 *
 * \details 
 * 0: Encapsulation data is counted as frame data.
 * 0: Encapsulation data in not counted as frame data.
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . ENCAP_DATA_DIS
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_ENCAP_DATA_DIS  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.
 * When GAP_VALUE = 20, a line-rate measurement because each frame occupies
 * 12 bytes for the inter-frame gap and 8 bytes for the preamble on the
 * line. When GAP_VALUE = 0, a data-rate measurement is achived..
 *
 * \details 
 * 0x40: -64
 * 0x41: -63
 *    ...
 * 0x7F: -1
 * 0x00: 0
 * 0x01: 1
 *    ...
 * 0x3F: 63
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . GAP_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_GAP_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,7)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_GAP_VAL     VTSS_ENCODE_BITMASK(2,7)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_GAP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,7)

/** 
 * \brief
 * Configures the leaky bucket scale to enable from 16 kbps up to 10Gbps
 * rates.
 *
 * \details 
 * 0: Up to 10Gbps rates configured with 8196721 bps(= 8192 kbps)
 * granularity
 * 1: Up to 2Gbps rates configured with 1024590 bps (= 1024 kbps)
 * granularity
 * 2: Up to 200Mbps rates configured with 128074 bps (= 128 kbps)
 * granularity
 * 3: Up to 32 Mbps rates configured with 16009 bps (= 16 kbps) granularity
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_DLB_CFG . TIMESCALE_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_DLB_CFG_TIMESCALE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_POL_SDLB_DLB_CFG_TIMESCALE_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_POL_SDLB_DLB_CFG_TIMESCALE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Configuration of leaky buckets
 *
 * \details
 * LB_CFG:0 configures CIR and LB_CFG:1 configures PIR
 *
 * Register: \a ANA_AC_POL:SDLB:LB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-4095
 * @param ri Register: LB_CFG (??), 0-1
 */
#define VTSS_ANA_AC_POL_SDLB_LB_CFG(gi,ri)   VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,ri,1)

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 2048 bytes
 *
 * \details 
 * 0: Threshold = 0 bytes (no burst allowed)
 * 1: Threshold = 2048 bytes
 * n: Threshold = n x 2048 bytes
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_LB_CFG . THRES_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_LB_CFG_THRES_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_ANA_AC_POL_SDLB_LB_CFG_THRES_VAL     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_ANA_AC_POL_SDLB_LB_CFG_THRES_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Specify rate in steps of configured granularity
 *
 * \details 
 * 0: Disable leak. For THRES_VAL = 0 bucket is always closed. For
 * THRES_VAL > 0, the configured burst size is available.
 * 1: 1 * granularity
 * 2: 2 * granularity
 * ...
 * n-1: (n-1)*granularity
 * n: Disable leaky bucket (always open)
 *
 * Field: ::VTSS_ANA_AC_POL_SDLB_LB_CFG . RATE_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_LB_CFG_RATE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,11)
#define  VTSS_M_ANA_AC_POL_SDLB_LB_CFG_RATE_VAL     VTSS_ENCODE_BITMASK(0,11)
#define  VTSS_X_ANA_AC_POL_SDLB_LB_CFG_RATE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,11)


/** 
 * \brief Configuration of leaky bucket value
 *
 * \details
 * LB_CFG:0 configures CIR and LB_CFG:1 configures PIR
 *
 * Register: \a ANA_AC_POL:SDLB:LB_BUCKET_VAL
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-4095
 * @param ri Register: LB_BUCKET_VAL (??), 0-1
 */
#define VTSS_ANA_AC_POL_SDLB_LB_BUCKET_VAL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,ri,3)

/** 
 * \brief
 * Number of bytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_SDLB_LB_BUCKET_VAL . BUCKET_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,19)
#define  VTSS_M_ANA_AC_POL_SDLB_LB_BUCKET_VAL_BUCKET_VAL     VTSS_ENCODE_BITMASK(9,19)
#define  VTSS_X_ANA_AC_POL_SDLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,19)

/** 
 * \brief
 * Number of subbytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_SDLB_LB_BUCKET_VAL . REM_VAL
 */
#define  VTSS_F_ANA_AC_POL_SDLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_POL_SDLB_LB_BUCKET_VAL_REM_VAL     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_POL_SDLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


#endif /* _VTSS_JAGUAR2_REGS_ANA_AC_POL_H_ */
