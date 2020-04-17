// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_ANA_AC_POL_H_
#define _VTSS_FA_REGS_ANA_AC_POL_H_

#include "vtss_fa_regs_common.h"

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
 * \brief Configuration of storm policer rates
 *
 * \details
 * These registers configure the rates of the storm policers.
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4a30 + (ri))

/** 
 * \brief
 * Storm policer leaky bucket rate.Regarding unit, refer to
 * POL_UPD_INT.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_UPD_INT_CFG.POL_UPD_INTANA_AC_POL:
 * POL_ALL_CFG:POL_STORM_CTRL.STORM_FRAME_RATE_ENA
 *
 * \details 
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is disabled, policing is
 * performed in bits per second (bps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 1 x <unit> bps
 * n: Rate = n x <unit> bps
 * 
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is enabled, policing is
 * performed in frames per second (fps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = <unit> fps
 * n: Rate = n x <unit> fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG . STORM_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Configuration of storm policer thresholds
 *
 * \details
 * These registers configure the thresholds of the storm policers
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_THRES_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4a38 + (ri))

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192
 * bytes.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_STORM_CTRL.STORM_FRAME_RATE_ENA
 *
 * \details 
 * When POL_STORM_CTRL.STORM_FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * 
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
 * \brief Configuration of storm policer parameters
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STORM_CTRL
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_STORM_TOT_NUM_LB (??), 0-7
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4a40 + (ri))

/** 
 * \brief
 * Enable frame rate mode for the storm policer, where policer rates are
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
 * Controls policing of frames to the individual CPU queues for the storm
 * policers. If a bit is set in this mask, frames to the corresponding CPU
 * queue are allowed to be policed (frames may get discarded).
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
 * Configures the frame types to be policed by the policer. Each bit in the
 * mask enables policing of a specific frame type. Multiple frame types can
 * be enabled at the same time and a frame can belong to multiple frame
 * types.If a frame belongs to one or more enabled frame types, then the
 * frame is policed.The only exception to this is if the CPU queue bit is
 * cleared and the frame is destined to a CPU queue in the CPU_QU_MASK. In
 * this case the frame is NOT policed (by this policer), regardless of
 * other settings in TRAFFIC_TYPE_MASK. If a frame does not match any of
 * the enabled frame types, then the frame bypasses the policer (never
 * discarded and the bucket is not updated with the frame).Frame bypassing
 * one storm policer, may be subject to policing by one of the other storm
 * policers.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_STORM_CTRL.STORM_CPU_QU_MASK
 *
 * \details 
 * 'xxxxxxx1' : Known multicast frames are policed. 
 * 'xxxxxx1x' : Known broadcast frames are policed.
 * 'xxxxx1xx' : Known unicast frames are policed. 
 * 'xxxx1xxx' : Unknown multicast frames are policed. 
 * 'xxx1xxxx' : Unknown broadcast frames are policed.
 * 'xx1xxxxx' : Unknown unicast frames are policed. 
 * 'x0xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK bypass the
 * policer, regardless of other criteria in TRAFFIC_TYPE_MASK.
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
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-63
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4a48 + (ri))

/** 
 * \brief
 * ACL policer leaky bucket rate.Regarding unit, refer to
 * POL_UPD_INT.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_UPD_INT_CFG.POL_UPD_INTANA_AC_POL:
 * POL_ALL_CFG:POL_ACL_CTRL.FRAME_RATE_ENA
 *
 * \details 
 * When POL_ACL_CTRL.FRAME_RATE_ENA is disabled, policing is performed in
 * bits per second (bps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 1 x <unit> bps
 * n: Rate = n x <unit> bps
 * 
 * When POL_ACL_CTRL.FRAME_RATE_ENA is enabled, policing is performed in
 * frames per second (fps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = <unit> fps
 * n: Rate = n x <unit> fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG . ACL_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_ACL_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief Configuration of ACL policer thresholds
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_THRES_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-63
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4a88 + (ri))

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 8192
 * bytes.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_ACL_CTRL.FRAME_RATE_ENA
 *
 * \details 
 * When POL_ACL_CTRL.FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * 
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
 * \brief Configuration of ACL policer parameters
 *
 * \details
 * Only frames with an VCAP IS2 action with POLICE_ENA=1 are subject to ACL
 * policing. The policer index is then controlled by the VCAP IS2 action
 * field POLICE_IDX.
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ACL_CTRL
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_ACL_TOT_NUM_LB (??), 0-63
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4ac8 + (ri))

/** 
 * \brief
 * Configures the pipeline point per ACL policer.When injecting or looping
 * at a pipeline point after ACL_PIPELINE_PT will not cause ACL
 * policing.When extracting at a pipeline point before ACL_PIPELINE_PT will
 * not cause ACL policing.
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
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL . ACL_PIPELINE_PT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_PIPELINE_PT     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_ACL_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

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
 * -64 to +63 in two's complement format.Setting GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * GAP_VALUE to 0 corresponds to a data-rate measurement.
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
 * Configures the frame types to be policed by the policer. Each bit in the
 * mask enables a specific frame type.If a frame does not match any of the
 * enabled frame types, then the frame bypasses the policer (never
 * discarded and the bucket is not updated with the frame).
 *
 * \details 
 * '00': Police frame (if policer is not bypassed by ACL_PIPELINE_PT or
 * DP_BYPASS_LVL)
 * '01': Only frames to front ports are triggering policer and only front
 * port destinations are policed.
 * '10': Frames to CPU are triggering policer and only CPU destinations are
 * policed.
 * '11': Frames to front ports and/or CPU are triggering policer and being
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
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_PORT_FC_CFG
 *
 * @param ri Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-69
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4b08 + (ri))

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
 * discarded.PORT_FC_ENA must also be set to enable pause frames.
 * Furthermore DSM must be configured for flow control.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_ALL_CFG.PORT_FC_ENADSM:CFG:ETH_FC_
 * CFG.FC_ANA_ENA
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
 * \brief Miscellaneous policer parameters
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_ALL_CFG
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4b4e)

/** 
 * \brief
 * Enables subtraction of the DP from the priority. This enables logging of
 * differently colored frames in different log files when using the ANA
 * testbench.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . DBG_DP_CHG_PRIO_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DBG_DP_CHG_PRIO_ENA(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.Setting STORM_GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * STORM_GAP_VALUE to 0 corresponds to a data-rate measurement.
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
 * When set, the frame color used in statistics is based only on the color
 * determined by the SDLB policer.Related
 * parameters:ANA_AC:STAT_CNT_CFG_ISDX
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
 * ISDX counters.One bit for each of the four internal DP values.
 *
 * \details 
 * 0: DP value will be counted as green.
 * 1: DP value will be counted as yellow.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . DP_TO_COLOR_MAP
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Enables overall signaling of flow control from the port policers to DSM.
 * Flow control is enabled for each port policer in
 * POL_PORT_FC_CFG.FC_ENA.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_PORT_FC_CFG.FC_ENADSM:CFG:ETH_FC_C
 * FG.FC_ANA_ENA
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PORT_FC_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enables operation of port policers in parallel.In serial mode, each of
 * the active port policers for a port are checked one after another. If a
 * frame is discarded by a policer, the frame is not passed on to
 * subsequent policers.In parallel mode, each of the active port policers
 * for a port operate on all frames (policing and bucket updates) even
 * though one or more of the other port policers is be closed.
 *
 * \details 
 * 0: Port policer operates in serial mode. 
 * 1: Port policer operates in parallel mode. 
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . PORT_POL_IN_PARALLEL_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_POL_IN_PARALLEL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * If set, all storm policer buckets are forced closed (all frames are
 * policed and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All storm policer buckets are closed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_FORCE_CLOSE
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * If set, all storm policer buckets are forced open (no frames are policed
 * and no buckets are updated). The bit must be cleared for normal
 * operation.
 *
 * \details 
 * 0: Normal operation
 * 1: All storm policer buckets are forced open
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG . STORM_FORCE_OPEN
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * If set, all storm policers are initialized and buckets are open. The bit
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
 * 1: All port policer buckets are forced open
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
 * If set, the port policers operate on logical port numbers instead of
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
 * \brief Policer update interval
 *
 * \details
 * Configure the leaky bucket update interval for the ACL, storm- and port
 * policers. 
 * This configuration affects the policing rate unit for these 3 policers. 
 * By setting this parameter to a clock frequency dependent value, the rate
 * unit can be kept identical/similar across different system clock
 * frequencies.
 *
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_UPD_INT_CFG
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4b4f)

/** 
 * \brief
 * This configuration will affect the policing rate unit for the storm, ACL
 * and port policers. The rate unit is calculated as follows:Rate unit =
 * SYS_CLK / (POL_UPD_INT * 32) bpsRecommended value and corresponding rate
 * unit:250MHz: 312 => 25040bps500MHz: 624 => 25040bps625MHz: 780 =>
 * 25040bpsFrame rate mode is also affected be this setting. The default
 * frame rate unit is 10fps (frames per second). This is scaled according
 * to this formula:Frame rate = 10fps * (Rate unit / 25040bps)
 *
 * \details 
 * 0-31: Not allowed
 * N: Update interval

 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG . POL_UPD_INT
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Policer diagnostic information
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STICKY
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4b50)

/** 
 * \brief
 * Set if a storm policer is active.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Storm policer is active (frames added to leaky buckets)

 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Set if a storm policer has removed the front ports from a frame's
 * destination set due to policing. Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: A storm policer has removed the front ports from a frame's
 * destination set due to policing
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_DROP_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY  VTSS_BIT(21)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Set if a storm policer has removed the CPU ports from a frame's
 * destination set due to policing.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: A storm policer has removed the CPU ports from a frame's destination
 * set due to policing
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_STORM_DROP_CPU_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY  VTSS_BIT(20)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Set if a service policer has been bypassed due to a pipeline point.Bit
 * is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_DLB_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY  VTSS_BIT(19)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Set if frame has been dropped by a SDLB policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: DLB policer drop event has occurred
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_DLB_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY  VTSS_BIT(18)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_DLB_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set if a priority policer has been bypassed due to a pipeline point.Bit
 * is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY  VTSS_BIT(17)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Set if a priority policer is active.Bit is cleared by writing a 1 to
 * this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Priority policer is active (frames added to leaky buckets)
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Set if frame has been dropped due to priority policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: PRIO policer drop event has occurred
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY  VTSS_BIT(15)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Set if a priority policer has been bypassed due to a frame's DP level or
 * traffic type mask.Bit is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Priority policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PRIO_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PRIO_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set if an ACL policer has been bypassed due to a pipeline point.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY  VTSS_BIT(13)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set if an ACL policer is active.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: ACL policer is active (frames added to leaky buckets)
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY  VTSS_BIT(12)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set if frame has been dropped due to ACL policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: ACL policer drop event has occurred
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY  VTSS_BIT(11)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Set if an ACL policer has been bypassed due to a frame's DP level or
 * traffic type mask.Bit is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: ACL policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_ACL_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY  VTSS_BIT(10)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_ACL_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Set if an Port policer has been bypassed due to a pipeline point.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_PT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Set if a port policer is active.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Port policer is active (frames added to leaky buckets)
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Set if a port policer's flow control state has been cleared.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Port policer flow control state has been cleared
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_FC_CLEAR_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY  VTSS_BIT(4)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Set if flow control has been active for a port policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Port policer flow control has been activated
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_FC_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY  VTSS_BIT(3)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Set if a port policer has removed the front ports from a frame's
 * destination set due to policing. Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: A port policer has removed the front ports from a frame's destination
 * set due to policing
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_DROP_FWD_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set if a port policer has removed the CPU ports from a frame's
 * destination set due to policing.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: A port policer has removed the CPU ports from a frame's destination
 * set due to policing
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_DROP_CPU_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if a port policer has been bypassed due to a frame's DP level or
 * traffic type mask.Bit is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Port policer has been bypassed
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY . POL_PORT_BYPASS_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Policer diagnostic information
 *
 * \details
 * Register: \a ANA_AC_POL:POL_ALL_CFG:POL_STICKY1
 */
#define VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4b51)

/** 
 * \brief
 * Set if BUM policer has been active.One bit per BUM policer.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: BUM policer has been active.
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1 . POL_BUM_SLB_ACTIVE_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_ACTIVE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_ACTIVE_STICKY     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_ACTIVE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Set if frame has been dropped by a BUM policer.One bit per BUM
 * policer.Bit is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: BUM policer drop event has occurred
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1 . POL_BUM_SLB_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_DROP_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BUM_SLB_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set if frame has been dropped by a BDLB policer.Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: BDLB policer drop event has occurred
 *
 * Field: ::VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1 . POL_BDLB_DROP_STICKY
 */
#define  VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BDLB_DROP_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BDLB_DROP_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY1_POL_BDLB_DROP_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC_POL:POL_PORT_CFG
 *
 * Rate and threshold configuration for port policers.
 */


/** 
 * \brief Port policer upper threshold configuration
 *
 * \details
 * The registers are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_THRES_CFG_0
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-279
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4000 + (ri))

/** 
 * \brief
 * Threshold size for port policer (burst capacity).Related
 * parameters:ANA_AC_POL:POL_PORT_CTRL:POL_PORT_CFG.FRAME_RATE_ENA
 *
 * \details 
 * When POL_PORT_CFG.FRAME_RATE_ENA is disabled burst capacity is
 * configured in steps of 8192 bytes.
 * 0: Always closed
 * 1: Burst capacity = 8192 bytes
 * n: Burst capacity = n x 8192 bytes
 * 63: Burst capacity = 516096 bytes
 * 
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
 * The registers are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_THRES_CFG_1
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-279
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4200 + (ri))

/** 
 * \brief
 * Hysteresis size for port policer. Unit is 8192 bytes. PORT_THRES1 is
 * used when a port policer is in flow control mode. Flow control is
 * asserted when the bucket level exceeds PORT_THRES0. Flow control is
 * deasserted when the bucket has leaked PORT_THRES1 bytes since the
 * assertion. PORT_THRES1 must be programmed smaller or equal to
 * PORT_THRES0.Related
 * parameters:ANA_AC_POL:POL_PORT_CFG:POL_PORT_THRES_CFG_0.PORT_THRES0ANA_A
 * C_POL:POL_ALL_CFG:POL_PORT_FC_CFG.FC_ENA
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
 * The registers are index by 4 x port number + port policer index.
 *
 * Register: \a ANA_AC_POL:POL_PORT_CFG:POL_PORT_RATE_CFG
 *
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_TOT_NUM_LB (??), 0-279
 */
#define VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4400 + (ri))

/** 
 * \brief
 * Port policer leaky bucket rate. Regarding unit, refer to
 * POL_UPD_INT.Related
 * parameters:ANA_AC_POL:POL_ALL_CFG:POL_UPD_INT_CFG.POL_UPD_INTANA_AC_POL:
 * POL_PORT_CTRL:POL_PORT_CFG.FRAME_RATE_ENA
 *
 * \details 
 * When POL_PORT_CFG.FRAME_RATE_ENA is disabled, policing is performed in
 * bits per second (bps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = 1 x <unit> bps
 * n: Rate = n x <unit> bps
 * 
 * When POL_PORT_CFG.FRAME_RATE_ENA is enabled, policing is performed in
 * frames per second (fps). 
 * 0: Open until burst capacity is used, then closed.
 * 1: Rate = <unit> fps
 * n: Rate = n x <unit> fps
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG . PORT_RATE
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE(x)  VTSS_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a ANA_AC_POL:POL_PORT_CTRL
 *
 * Port policer configuration and status per port
 */


/** 
 * \brief Port policer gap and pipeline point configuration
 *
 * \details
 * Register: \a ANA_AC_POL:POL_PORT_CTRL:POL_PORT_GAP
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-69
 */
#define VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x4800,gi,8,0,0)

/** 
 * \brief
 * Configures the pipeline point per port policer.When injecting or looping
 * at a pipeline point after PORT_PIPELINE_PT will not cause port
 * policing.When extracting at a pipeline point before PORT_PIPELINE_PT
 * will not cause port policing.
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
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP . PORT_PIPELINE_PT
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_PORT_PIPELINE_PT(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_PORT_PIPELINE_PT     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_PORT_PIPELINE_PT(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.Setting GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * GAP_VALUE to 0 corresponds to a data-rate measurement.
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
 * Register: \a ANA_AC_POL:POL_PORT_CTRL:POL_PORT_CFG
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PORT_POL (??), 0-69
 * @param ri Replicator: x_FFL_ANA_AC_POL_PORT_LB_SET_SIZE (??), 0-3
 */
#define VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x4800,gi,8,ri,1)

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
 * Configures if service frames (ISDX <> 0) bypasses the port policers.
 *
 * \details 
 * 0: All frames are applicable for port policing
 * 1: Only non service frames are applicable for port policing 
 *
 * Field: ::VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG . SERVICE_BYPASS_ENA
 */
#define  VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_SERVICE_BYPASS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_SERVICE_BYPASS_ENA  VTSS_BIT(14)
#define  VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_SERVICE_BYPASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Configuration of DP bypass level. Frames with DP below DP_BYPASS_LVL
 * bypass the port policers (frames are never policed and the bucket is not
 * updated with the frames).
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
 * Enables frame rate mode for the port policers, where policer rates are
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
 * Configures the frame types to be policed by the policer. Each bit in the
 * mask enables policing of a specific frame type. Multiple frame types can
 * be enabled at the same time and a frame can belong to multiple frame
 * types.If a frame belongs to one or more enabled frame types, then the
 * frame is policed.The only exception to this is if the CPU queue bit is
 * cleared and the frame is destined to a CPU queue in the CPU_QU_MASK. In
 * this case the frame is NOT policed (by this policer), regardless of
 * other settings in TRAFFIC_TYPE_MASK. If a frame does not match any of
 * the enabled frame types, then the frame bypasses the policer (never
 * discarded and the bucket is not updated with the frame).Frame bypassing
 * one port policer, may be subject to policing by one of the other port
 * policers.Related
 * parameters:ANA_AC_POL:POL_PORT_CTRL[0-56]:POL_PORT_CFG.CPU_QU_MASK
 *
 * \details 
 * 'xxxxxxx1' : Known multicast frames are policed. 
 * 'xxxxxx1x' : Known broadcast frames are policed.
 * 'xxxxx1xx' : Known unicast frames are policed. 
 * 'xxxx1xxx' : Unknown multicast frames are policed. 
 * 'xxx1xxxx' : Unknown broadcast frames are policed.
 * 'xx1xxxxx' : Unknown unicast frames are policed. 
 * 'x0xxxxxx' : Frames to a CPU queue selected by CPU_QU_MASK bypass the
 * policer, regardless of other criteria in TRAFFIC_TYPE_MASK.
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
 * repl:0 NONE, XTR_LATE_REW
 * repl:1 INJ, INJ_MASQ, LBK_ASM
 * repl:2 XTR
 * repl:3 XTR_UPMEP
 * repl:4 LBK_QS
 *
 * Register: \a ANA_AC_POL:PORT_PT_CTRL:ACTION_CTRL
 *
 * @param gi Replicator: x_FFL_ANA_NUM_PT_CTRL_IDX (??), 0-95
 * @param ri Register: ACTION_CTRL (??), 0-4
 */
#define VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x4b52,gi,5,ri,0)

/** 
 * \brief
 * Disable Port VOE LM updates.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . PVOE_DIS
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PVOE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Disable port statistics.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL . PSTAT_DIS
 */
#define  VTSS_F_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_PORT_PT_CTRL_ACTION_CTRL_PSTAT_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC_POL:COMMON_BDLB
 *
 * Common LB configuration and status registers
 */


/** 
 * \brief Configuration of common leaky bucket handling
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_BDLB:DLB_CTRL
 */
#define VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4d32)

/** 
 * \brief
 * Specifies the clock period in unit of 0.1ns.
 *
 * \details 
 * 16: 1.6ns (625MHz)
 * 20: 2ns (500MHz)
 * 40: 4ns (250MHz)
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL . CLK_PERIOD_01NS
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(x)  VTSS_ENCODE_BITFIELD(x,19,8)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS     VTSS_ENCODE_BITMASK(19,8)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_CLK_PERIOD_01NS(x)  VTSS_EXTRACT_BITFIELD(x,19,8)

/** 
 * \brief
 * TIMESCALE_VAL and BASE_TICK_CNT controls the the rate interval as well
 * as the rate granularity available for LB rate configuration Refer to
 * TIMESCALE_VAL for details.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL . BASE_TICK_CNT
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,15)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_BASE_TICK_CNT     VTSS_ENCODE_BITMASK(4,15)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,15)

/** 
 * \brief
 * Enables leaking from the leaky buckets.
 *
 * \details 
 * 0: Disable bucket leaking
 * 1: Enable bucket leaking
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL . LEAK_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_LEAK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_LEAK_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_LEAK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables adding of frame bytes to the leaky buckets.
 *
 * \details 
 * 0: Disable bucket addition
 * 1: Enable bucket addition
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_CTRL . DLB_ADD_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_DLB_ADD_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief LB policer diagnostic
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_BDLB:DLB_STICKY
 */
#define VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4d33)

/** 
 * \brief
 * Set when a LB scan completes.Bit is cleared by writing a 1.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan completes
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . LEAK_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Set when a LB scan starts.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan started
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . LEAK_SCAN_STARTED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY  VTSS_BIT(30)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Set when a LB scan could not start because a scan is already ongoing. If
 * this occur, BASE_TICK_CNT is set too low and must be increased.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan could not start at time
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . LEAK_START_DELAYED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY  VTSS_BIT(29)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Set when the frame rate is exceeding the Peak Information Rate.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: PIR exceeded
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . PIR_EXCEEDED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_PIR_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_PIR_EXCEEDED_STICKY  VTSS_BIT(2)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_PIR_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set when the frame rate is exceeding the Committed Information Rate.Bit
 * is cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: CIR exceeded
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . CIR_EXCEEDED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_EXCEEDED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_EXCEEDED_STICKY  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_EXCEEDED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Set when the frame rate is below both the Committed Information Rate and
 * the Peak Information Rate.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Traffic received without triggering CIR and PIR policing
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BDLB_DLB_STICKY . CIR_PIR_OPEN_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_BDLB_DLB_STICKY_CIR_PIR_OPEN_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a ANA_AC_POL:BDLB
 *
 * Leaky bucket configuration & status
 */


/** 
 * \brief Configuration of various LB policer handles
 *
 * \details
 * Register: \a ANA_AC_POL:BDLB:MISC_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 */
#define VTSS_ANA_AC_POL_BDLB_MISC_CFG(gi)    VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,0,0)

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
 * Field: ::VTSS_ANA_AC_POL_BDLB_MISC_CFG . DP_BYPASS_LVL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_MISC_CFG_DP_BYPASS_LVL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_ANA_AC_POL_BDLB_MISC_CFG_DP_BYPASS_LVL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_ANA_AC_POL_BDLB_MISC_CFG_DP_BYPASS_LVL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enables frame rate mode for the policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details 
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_MISC_CFG . FRAME_RATE_ENA
 */
#define  VTSS_F_ANA_AC_POL_BDLB_MISC_CFG_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_BDLB_MISC_CFG_FRAME_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_BDLB_MISC_CFG_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of DLB policer
 *
 * \details
 * Register: \a ANA_AC_POL:BDLB:DLB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 */
#define VTSS_ANA_AC_POL_BDLB_DLB_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,0,1)

/** 
 * \brief
 * The time - in BASE_TICK_CNTs - at which last leak was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . TIMESTAMP_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_TIMESTAMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,17,11)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_TIMESTAMP_VAL     VTSS_ENCODE_BITMASK(17,11)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_TIMESTAMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,17,11)

/** 
 * \brief
 * Set Coupling Flag (MEF CF).Depending on the setting of COUPLING_MODE,
 * LB_CFG[0] and LB_CFG[1] must be configured as
 * follows:COUPLING_MODE=0:LB_CFG[0].RATE_VAL  must be configured to MEF
 * CIRLB_CFG[0].THRES_VAL must be configured to MEF CBSLB_CFG[1].RATE_VAL 
 * must be configured to MEF EIRLB_CFG[1].THRES_VAL must be configured to
 * MEF EBSCOUPLING_MODE=1:LB_CFG[0].RATE_VAL  must be configured to MEF
 * CIRLB_CFG[0].THRES_VAL must be configured to MEF CBSLB_CFG[1].RATE_VAL 
 * must be configured to MEF EIR + MEF CIRLB_CFG[1].THRES_VAL must be
 * configured to MEF EBS + MEF CBS
 *
 * \details 
 * 0: CF=0
 * 1: CF=1
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . COUPLING_MODE
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_COUPLING_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_COUPLING_MODE  VTSS_BIT(16)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_COUPLING_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Configuration of dual leaky bucket color awareness.Frames with DP below
 * or equal to COLOR_AWARE_LVL is treated as green. Frames with DP above
 * COLOR_AWARE_LVL are treated as yellow.
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
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . COLOR_AWARE_LVL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_COLOR_AWARE_LVL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_COLOR_AWARE_LVL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Configuration of the drop precedence change for EIR traffic. Frames
 * accounted for in the EIR bucket are subject to incrementing the DP level
 * with CIR_INC_DP_VAL. This is independent of settings in COLOR_AWARE_LVL. 
 *
 * \details 
 * 0: DP is not increased.
 * n: DP is increased with n for EIR traffic.
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . CIR_INC_DP_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_CIR_INC_DP_VAL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_CIR_INC_DP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Configures action to be applied to policed frames.
 *
 * \details 
 * 0: No action.
 * 1: Remove front ports from frame's destination port set.
 * 2: Remove CPU ports from frame's destination port set.
 * 3: Remove both front ports and CPU ports from frame's destination port
 * set.
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * Configures if stripped encapsulation data (normalized data) is policed
 * by the policer. 
 *
 * \details 
 * 0: Encapsulation data is counted as frame data.
 * 1: Encapsulation data in not counted as frame data.
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . ENCAP_DATA_DIS
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_ENCAP_DATA_DIS  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_ENCAP_DATA_DIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.Setting GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * GAP_VALUE to 0 corresponds to a data-rate measurement.
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
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . GAP_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_GAP_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,7)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_GAP_VAL     VTSS_ENCODE_BITMASK(2,7)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_GAP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,7)

/** 
 * \brief
 * TIMESCALE_VAL and BASE_TICK_CNT controls the the rate interval as well
 * as the rate granularity available for LB rate configuration The rate
 * granularity is calculated as follows:    8 / (BASE_TICK_CNT*1e-10 * 2^(3
 * * TIMESCALE_VAL)The rate granularity also becomes the smallest
 * configurable rate.The largest configurable rate is	  granularity *
 * (2**<width of RATE_VAL>-2)
 *
 * \details 
 * Assuming BASE_TICK_CNT= 9765, RATE_VAL width = 12 bits:
 * 0: Granularity: 8,192,524bps. Range: 8193kbps - 33.6Gbps
 * 1: Granularity: 1,024,066bps. Range 1024kbps - 4.19Gbps
 * 2: Granularity: 128,008bps. Range: 128kbps - 523Mbps
 * 3: Granularity: 16,001bps. Range: 16kbps - 65Mbps
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_DLB_CFG . TIMESCALE_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_DLB_CFG_TIMESCALE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_POL_BDLB_DLB_CFG_TIMESCALE_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_POL_BDLB_DLB_CFG_TIMESCALE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Threshold and rate configuration
 *
 * \details
 * Register: \a ANA_AC_POL:BDLB:LB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 * @param ri Replicator: x_ANA_DLB_LB_SET_SIZE (??), 0-1
 */
#define VTSS_ANA_AC_POL_BDLB_LB_CFG(gi,ri)   VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,ri,2)

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 2048 bytes
 *
 * \details 
 * 0: Threshold = 0 bytes (no burst allowed)
 * 1: Threshold = 2048 bytes
 * n: Threshold = n x 2048 bytes
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_LB_CFG . THRES_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_LB_CFG_THRES_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ANA_AC_POL_BDLB_LB_CFG_THRES_VAL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ANA_AC_POL_BDLB_LB_CFG_THRES_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Specify rate in steps of configured granularity.The rate granularity is
 * configured in TIMESCALE_VAL.
 *
 * \details 
 * 0: Disable leak. For THRES_VAL = 0 bucket is always closed. For
 * THRES_VAL > 0, the configured burst size is available.
 * 1: 1 * granularity
 * 2: 2 * granularity
 * ...
 * max_value-1: (max_value-1)*granularity
 * max_value: Disable leaky bucket (always open)
 *
 * Field: ::VTSS_ANA_AC_POL_BDLB_LB_CFG . RATE_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_LB_CFG_RATE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_AC_POL_BDLB_LB_CFG_RATE_VAL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_AC_POL_BDLB_LB_CFG_RATE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Configuration of leaky bucket value
 *
 * \details
 * Register: \a ANA_AC_POL:BDLB:LB_BUCKET_VAL
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 * @param ri Replicator: x_ANA_DLB_LB_SET_SIZE (??), 0-1
 */
#define VTSS_ANA_AC_POL_BDLB_LB_BUCKET_VAL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x0,gi,8,ri,4)

/** 
 * \brief
 * Number of bytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BDLB_LB_BUCKET_VAL . BUCKET_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,20)
#define  VTSS_M_ANA_AC_POL_BDLB_LB_BUCKET_VAL_BUCKET_VAL     VTSS_ENCODE_BITMASK(9,20)
#define  VTSS_X_ANA_AC_POL_BDLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,20)

/** 
 * \brief
 * Number of subbytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BDLB_LB_BUCKET_VAL . REM_VAL
 */
#define  VTSS_F_ANA_AC_POL_BDLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_POL_BDLB_LB_BUCKET_VAL_REM_VAL     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_POL_BDLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a ANA_AC_POL:COMMON_BUM_SLB
 *
 * Common LB configuration and status registers
 */


/** 
 * \brief Configuration of common leaky bucket handling
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_BUM_SLB:DLB_CTRL
 */
#define VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4d34)

/** 
 * \brief
 * Specifies the clock period in unit of 0.1ns.
 *
 * \details 
 * 16: 1.6ns (625MHz)
 * 20: 2ns (500MHz)
 * 40: 4ns (250MHz)
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL . CLK_PERIOD_01NS
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(x)  VTSS_ENCODE_BITFIELD(x,19,8)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS     VTSS_ENCODE_BITMASK(19,8)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_CLK_PERIOD_01NS(x)  VTSS_EXTRACT_BITFIELD(x,19,8)

/** 
 * \brief
 * TIMESCALE_VAL and BASE_TICK_CNT controls the the rate interval as well
 * as the rate granularity available for LB rate configuration Refer to
 * TIMESCALE_VAL for details.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL . BASE_TICK_CNT
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,15)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_BASE_TICK_CNT     VTSS_ENCODE_BITMASK(4,15)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_BASE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,15)

/** 
 * \brief
 * Enables leaking from the leaky buckets.
 *
 * \details 
 * 0: Disable bucket leaking
 * 1: Enable bucket leaking
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL . LEAK_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_LEAK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_LEAK_ENA  VTSS_BIT(1)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_LEAK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enables adding of frame bytes to the leaky buckets.
 *
 * \details 
 * 0: Disable bucket addition
 * 1: Enable bucket addition
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL . DLB_ADD_ENA
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_DLB_ADD_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_DLB_CTRL_DLB_ADD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Frame type selection per policer
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_BUM_SLB:TRAFFIC_MASK_CFG
 *
 * @param ri Replicator: x_ANA_DLB_LB_SET_SIZE (??), 0-2
 */
#define VTSS_ANA_AC_POL_COMMON_BUM_SLB_TRAFFIC_MASK_CFG(ri)  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4d35 + (ri))

/** 
 * \brief
 * Configures the frame types to be policed by the policer.Each bit in the
 * mask enables policing of a specific frame type.Multiple frame types can
 * be enabled at the same time and a frame can belong to multiple frame
 * types.If a frame belongs to one or more enabled frame types, then the
 * frame is policed.
 *
 * \details 
 * 'xxxxxx1' : Unknown broadcast frames are policed.
 * 'xxxxx1x' : Unknown multicast frames are policed.
 * 'xxxx1xx' : Unknown unicast frames are policed.
 * 'xxx1xxx' : Known broadcast frames are policed.
 * 'xx1xxxx' : Known multicast frames are policed.
 * 'x1xxxxx' : Known unicast frames are policed.
 * '1xxxxxx' : Learn frames are policed.
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_TRAFFIC_MASK_CFG . TRAFFIC_TYPE_MASK
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_TRAFFIC_MASK_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_TRAFFIC_MASK_CFG_TRAFFIC_TYPE_MASK     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_TRAFFIC_MASK_CFG_TRAFFIC_TYPE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief SLB policer diagnostic
 *
 * \details
 * Register: \a ANA_AC_POL:COMMON_BUM_SLB:SLB_STICKY
 */
#define VTSS_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY  VTSS_IOREG(VTSS_TO_ANA_AC_POL,0x4d38)

/** 
 * \brief
 * Set when a LB scan completes.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan completes
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY . LEAK_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_COMPLETED_STICKY  VTSS_BIT(31)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Set when a LB scan starts.Bit is cleared by writing a 1 to this
 * position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan started
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY . LEAK_SCAN_STARTED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_STARTED_STICKY  VTSS_BIT(30)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Set when a LB scan could not start because a scan is already ongoing.If
 * this occur, BASE_TICK_CNT is set too low and must be increased.Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: Leak scan could not start at time
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY . LEAK_START_DELAYED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_START_DELAYED_STICKY  VTSS_BIT(29)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_LEAK_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Set when the frame rate is exceeding the configured rate.Bit is cleared
 * by writing a 1 to this position.
 *
 * \details 
 * 0: No event has occurred
 * 1: CIR exceeded
 *
 * Field: ::VTSS_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY . SLB_CLOSED_STICKY
 */
#define  VTSS_F_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_SLB_CLOSED_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_SLB_CLOSED_STICKY     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_ANA_AC_POL_COMMON_BUM_SLB_SLB_STICKY_SLB_CLOSED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a ANA_AC_POL:BUM_SLB
 *
 * Leaky bucket configuration & status
 */


/** 
 * \brief Configuration of various LB policer handles
 *
 * \details
 * Register: \a ANA_AC_POL:BUM_SLB:MISC_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 */
#define VTSS_ANA_AC_POL_BUM_SLB_MISC_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x2000,gi,8,0,0)

/** 
 * \brief
 * Enables frame rate mode for the policer, where policer rates are
 * measured in frames per second instead of bits per second.
 *
 * \details 
 * 0: Rates measured in bits per second
 * 1: Rates measured in frames per second
 *
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_MISC_CFG . FRAME_RATE_ENA
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_MISC_CFG_FRAME_RATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_MISC_CFG_FRAME_RATE_ENA  VTSS_BIT(0)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_MISC_CFG_FRAME_RATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of BUM SLB policer
 *
 * \details
 * Register: \a ANA_AC_POL:BUM_SLB:SLB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 */
#define VTSS_ANA_AC_POL_BUM_SLB_SLB_CFG(gi)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x2000,gi,8,0,1)

/** 
 * \brief
 * The time - in BASE_TICK_CNTs - at which last leak was performed.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_SLB_CFG . TIMESTAMP_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESTAMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,10,11)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESTAMP_VAL     VTSS_ENCODE_BITMASK(10,11)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESTAMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,10,11)

/** 
 * \brief
 * Configures if stripped encapsulation data (normalized data) is policed
 * by the policer. 
 *
 * \details 
 * 0: Encapsulation data is counted as frame data.
 * 1: Encapsulation data in not counted as frame data.
 *
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_SLB_CFG . ENCAP_DATA_DIS
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_SLB_CFG_ENCAP_DATA_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_SLB_CFG_ENCAP_DATA_DIS  VTSS_BIT(9)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_SLB_CFG_ENCAP_DATA_DIS(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Value added to each frame before updating the bucket. Gap value range:
 * -64 to +63 in two's complement format.Setting GAP_VALUE to 20
 * corresponds to a line-rate measurement, since on the line each frame
 * will be preceded by 12 bytes of IFG and 8 bytes of preamble.Setting
 * GAP_VALUE to 0 corresponds to a data-rate measurement.
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
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_SLB_CFG . GAP_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_SLB_CFG_GAP_VAL(x)  VTSS_ENCODE_BITFIELD(x,2,7)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_SLB_CFG_GAP_VAL     VTSS_ENCODE_BITMASK(2,7)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_SLB_CFG_GAP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,2,7)

/** 
 * \brief
 * TIMESCALE_VAL and BASE_TICK_CNT controls the the rate interval as well
 * as the rate granularity available for LB rate configuration The rate
 * granularity is calculated as follows:    8 / (BASE_TICK_CNT*1e-10 * 2^(3
 * * TIMESCALE_VAL)The rate granularity also becomes the smallest
 * configurable rate.The largest configurable rate is	  granularity *
 * (2**<width of RATE_VAL>-2)
 *
 * \details 
 * Assuming BASE_TICK_CNT= 9765, RATE_VAL width = 12 bits:
 * 0: Granularity: 8,192,524bps. Range: 8193kbps - 33.6Gbps
 * 1: Granularity: 1,024,066bps. Range 1024kbps - 4.19Gbps
 * 2: Granularity: 128,008bps. Range: 128kbps - 523Mbps
 * 3: Granularity: 16,001bps. Range: 16kbps - 65Mbps
 *
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_SLB_CFG . TIMESCALE_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESCALE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESCALE_VAL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_SLB_CFG_TIMESCALE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Threshold and rate configuration
 *
 * \details
 * Configures each Single LB
 *
 * Register: \a ANA_AC_POL:BUM_SLB:LB_CFG
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 * @param ri Replicator: x_ANA_DLB_LB_SET_SIZE (??), 0-2
 */
#define VTSS_ANA_AC_POL_BUM_SLB_LB_CFG(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x2000,gi,8,ri,2)

/** 
 * \brief
 * Policer threshold size (a.ka. burst capacity). Unit is 2048 bytes
 *
 * \details 
 * 0: Threshold = 0 bytes (no burst allowed)
 * 1: Threshold = 2048 bytes
 * n: Threshold = n x 2048 bytes
 *
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_LB_CFG . THRES_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_LB_CFG_THRES_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_LB_CFG_THRES_VAL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_LB_CFG_THRES_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * Specify rate in steps of configured granularity.The rate granularity is
 * configured in TIMESCALE_VAL.
 *
 * \details 
 * 0: Disable leak. For THRES_VAL = 0 bucket is always closed. For
 * THRES_VAL > 0, the configured burst size is available.
 * 1: 1 * granularity
 * 2: 2 * granularity
 * ...
 * max_value-1: (max_value-1)*granularity
 * max_value: Disable leaky bucket (always open)
 *
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_LB_CFG . RATE_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_LB_CFG_RATE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_LB_CFG_RATE_VAL     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_LB_CFG_RATE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Configuration of leaky bucket value
 *
 * \details
 * Configures each Single LB
 *
 * Register: \a ANA_AC_POL:BUM_SLB:LB_BUCKET_VAL
 *
 * @param gi Replicator: x_ANA_NUM_DLB (??), 0-1023
 * @param ri Replicator: x_ANA_DLB_LB_SET_SIZE (??), 0-2
 */
#define VTSS_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL(gi,ri)  VTSS_IOREG_IX(VTSS_TO_ANA_AC_POL,0x2000,gi,8,ri,5)

/** 
 * \brief
 * Number of bytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL . BUCKET_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_ENCODE_BITFIELD(x,9,20)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_BUCKET_VAL     VTSS_ENCODE_BITMASK(9,20)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_BUCKET_VAL(x)  VTSS_EXTRACT_BITFIELD(x,9,20)

/** 
 * \brief
 * Number of subbytes in leaky bucket.
 *
 * \details 
 * Field: ::VTSS_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL . REM_VAL
 */
#define  VTSS_F_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_REM_VAL     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_ANA_AC_POL_BUM_SLB_LB_BUCKET_VAL_REM_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,9)


#endif /* _VTSS_FA_REGS_ANA_AC_POL_H_ */
