// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_FC_BUFFER_H_
#define _VTSS_VENICE_REGS_FC_BUFFER_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a FC_BUFFER
 *
 * Flow control buffer resgisters
 *
 ***********************************************************************/

/**
 * Register Group: \a FC_BUFFER:CONFIG
 *
 * Flow control buffer configuration registers
 */


/** 
 * \brief Enable flow control buffer operation register
 *
 * \details
 * Enable flow control buffer in ingress and egress paths
 *
 * Register: \a FC_BUFFER:CONFIG:FC_ENA_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_FC_ENA_CFG     VTSS_IOREG(0x03, 1, 0xf000)

/** 
 * \brief
 * Enable egress flow control buffer
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_ENA_CFG . TX_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_ENA_CFG_TX_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Enable ingress flow control buffer
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_ENA_CFG . RX_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_ENA_CFG_RX_ENA  VTSS_BIT(4)


/** 
 * \brief Flow control mode configuration register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:FC_MODE_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG    VTSS_IOREG(0x03, 1, 0xf001)

/** 
 * \brief
 * Enable pause reaction and pause timer maintenance in egress flow control
 * buffer
 *
 * \details 
 * 0: Disable pause reaction and pause timer
 * 1: Enable pause reaction and pause timer
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . PAUSE_REACT_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_PAUSE_REACT_ENA  VTSS_BIT(8)

/** 
 * \brief
 * Enable PPM rate adaptation in ingress flow control buffer. 
 * This is achieved by asserting shrint_ipg_shot signal towards host MAC10G
 * after the ingress flow control buffer crosses RX_PPM_RATE_ADAPT_THRES
 * value.
 *
 * \details 
 * 0: Disable PPM rate adaptation
 * 1: Enable PPM rate adaptation
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . RX_PPM_RATE_ADAPT_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_RX_PPM_RATE_ADAPT_ENA  VTSS_BIT(12)

/** 
 * \brief
 * Enable PPM rate adaptation in egress flow control buffer. 
 * This is achieved by asserting shrint_ipg_shot signal towards line MAC10G
 * after egress flow control buffer crosses RX_PPM_RATE_ADAPT_THRES value.
 * This is applicable only to data queue.
 *
 * \details 
 * 0: Disable PPM rate adaptation
 * 1: Enable PPM rate adaptation
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . TX_PPM_RATE_ADAPT_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_TX_PPM_RATE_ADAPT_ENA  VTSS_BIT(16)

/** 
 * \brief
 * Enable using of control queue in egress flow control buffer
 *
 * \details 
 * 0: Disable control queue
 * 1: Enable control queue
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . TX_CTRL_QUEUE_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_TX_CTRL_QUEUE_ENA  VTSS_BIT(20)

/** 
 * \brief
 * Enable XON and XOFF pause frames based on XON and XOFF thresholds
 *
 * \details 
 * 0: Disable XON/XOFF generation
 * 1: Enable XON/XOFF generation
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . PAUSE_GEN_ENA
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_PAUSE_GEN_ENA  VTSS_BIT(24)

/** 
 * \brief
 * Enable use of pause received signals from line MAC in XON/XOFF
 * generation
 *
 * \details 
 * 0: Disable pause received in XON/XOFF generation
 * 1: Enable pause received in XON/XOFF generation
 *
 * Field: VTSS_FC_BUFFER_CONFIG_FC_MODE_CFG . INCLUDE_PAUSE_RCVD_IN_PAUSE_GEN
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_MODE_CFG_INCLUDE_PAUSE_RCVD_IN_PAUSE_GEN  VTSS_BIT(28)


/** 
 * \brief PPM rate adaptation threshold configuration register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:PPM_RATE_ADAPT_THRESH_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG  VTSS_IOREG(0x03, 1, 0xf002)

/** 
 * \brief
 * Threshold of data queue in egress flow control buffer after which IPG
 * will be shrunk by 8 bytes to compensate read and write clocks PPM
 * differences. The recommended value is 2+TX_READ_THRESH.
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG . TX_PPM_RATE_ADAPT_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_TX_PPM_RATE_ADAPT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Threshold of data queue in ingress flow control buffer after which IPG
 * shrink is asserted to host MAC10G. The recommended value is
 * 2+RX_READ_THRESH.
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG . RX_PPM_RATE_ADAPT_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH(x)  VTSS_ENCODE_BITFIELD(x,20,12)
#define  VTSS_M_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH     VTSS_ENCODE_BITMASK(20,12)
#define  VTSS_X_FC_BUFFER_CONFIG_PPM_RATE_ADAPT_THRESH_CFG_RX_PPM_RATE_ADAPT_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,20,12)


/** 
 * \brief Tx control queue configuration register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:TX_CTRL_QUEUE_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG  VTSS_IOREG(0x03, 1, 0xf003)

/** 
 * \brief
 * Start address/location for control queue in egress flow control buffer
 * where control frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG . TX_CTRL_QUEUE_START
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_START(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_START     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_START(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * End address/location for control queue in egress flow control buffer
 * where control frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG . TX_CTRL_QUEUE_END
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_CTRL_QUEUE_CFG_TX_CTRL_QUEUE_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Tx data queue configuration register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:TX_DATA_QUEUE_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG  VTSS_IOREG(0x03, 1, 0xf004)

/** 
 * \brief
 * Start address/location for data queue in egress flow control buffer
 * where data frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG . TX_DATA_QUEUE_START
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_START(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_START     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_START(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * End address/location for data queue in egress flow control buffer where
 * data frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG . TX_DATA_QUEUE_END
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_DATA_QUEUE_CFG_TX_DATA_QUEUE_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Rx data queue configuration register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:RX_DATA_QUEUE_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG  VTSS_IOREG(0x03, 1, 0xf005)

/** 
 * \brief
 * Start address/location for data queue in ingress flow control buffer
 * where data frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG . RX_DATA_QUEUE_START
 */
#define  VTSS_F_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_START(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_START     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_START(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * End address/location for data queue in ingress flow control buffer where
 * data frames are stored
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG . RX_DATA_QUEUE_END
 */
#define  VTSS_F_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FC_BUFFER_CONFIG_RX_DATA_QUEUE_CFG_RX_DATA_QUEUE_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Tx flow control buffer pause frame generation thresholds register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:TX_BUFF_XON_XOFF_THRESH_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG  VTSS_IOREG(0x03, 1, 0xf006)

/** 
 * \brief
 * Egress data buffer threshold for generating XOFF pause frame to host
 * (Pause transmission from host, for example). The recommended value is
 * 1792.
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG . TX_XOFF_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XOFF_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XOFF_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XOFF_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Egress data buffer threshold for generating XON pause frame to host
 * (Transmission resumed, for example). The recommended value is 1280.
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG . TX_XON_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XON_THRESH(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XON_THRESH     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_BUFF_XON_XOFF_THRESH_CFG_TX_XON_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Flow control buffer read threshold register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:FC_READ_THRESH_CFG
 */
#define VTSS_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG  VTSS_IOREG(0x03, 1, 0xf007)

/** 
 * \brief
 * Egress flow control data buffer minimum threshold after which frames are
 * read from the flow control buffer and transmitted to the line.
 * Recommended values:-
 * LAN mode: 5
 * WAN mode: 2
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG . TX_READ_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_TX_READ_THRESH(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_TX_READ_THRESH     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_TX_READ_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Ingress flow control buffer minimum threshold after which frames are
 * read from the flow control buffer and transmitted to the host.
 * Recommended values:-
 * LAN mode: 4
 * WAN mode: 127
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG . RX_READ_THRESH
 */
#define  VTSS_F_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_RX_READ_THRESH(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_RX_READ_THRESH     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_FC_BUFFER_CONFIG_FC_READ_THRESH_CFG_RX_READ_THRESH(x)  VTSS_EXTRACT_BITFIELD(x,16,16)


/** 
 * \brief Tx frame gap compensation register
 *
 * \details
 * Register: \a FC_BUFFER:CONFIG:TX_FRM_GAP_COMP
 */
#define VTSS_FC_BUFFER_CONFIG_TX_FRM_GAP_COMP  VTSS_IOREG(0x03, 1, 0xf008)

/** 
 * \brief
 * Tx frame gap compensation
 *
 * \details 
 * Field: VTSS_FC_BUFFER_CONFIG_TX_FRM_GAP_COMP . TX_FRM_GAP_COMP
 */
#define  VTSS_F_FC_BUFFER_CONFIG_TX_FRM_GAP_COMP_TX_FRM_GAP_COMP(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_FC_BUFFER_CONFIG_TX_FRM_GAP_COMP_TX_FRM_GAP_COMP     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_FC_BUFFER_CONFIG_TX_FRM_GAP_COMP_TX_FRM_GAP_COMP(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a FC_BUFFER:STATUS
 *
 * Flow control buffer status registers
 */


/** 
 * \brief Sticky bits register
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:STICKY
 */
#define VTSS_FC_BUFFER_STATUS_STICKY         VTSS_IOREG(0x03, 1, 0xf009)

/** 
 * \brief
 * Indicates one or more frames in the egress flow control buffer were
 * dropped due to ECC failure. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No frame with ECC error was detected
 * 1: One or more frames with ECC error were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . TX_UNCORRECTED_FRM_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_TX_UNCORRECTED_FRM_DROP_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Indicates one or more frames in the ingress flow control buffer were
 * dropped due to ECC failure. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No frame with ECC error was detected
 * 1: One or more frames with ECC error were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . RX_UNCORRECTED_FRM_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_RX_UNCORRECTED_FRM_DROP_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * Indicates an overflow has occurred in the control queue of an egress
 * flow control buffer. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No overflow was detected
 * 1: One or more overflows were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY  VTSS_BIT(16)

/** 
 * \brief
 * Indicates an underflow has occurred in the control queue of an egress
 * flow control buffer. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No underflow was detected
 * 1: One or more underflows were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY  VTSS_BIT(17)

/** 
 * \brief
 * Indicates an overflow has occurred in the data queue of an egress flow
 * control buffer. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No overflow is detected
 * 1: One or more overflow were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . TX_DATA_QUEUE_OVERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_TX_DATA_QUEUE_OVERFLOW_DROP_STICKY  VTSS_BIT(18)

/** 
 * \brief
 * Indicates an underflow has occurred in the data queue of an egress flow
 * control buffer. This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No underflow is detected
 * 1: One or more underflow were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY  VTSS_BIT(19)

/** 
 * \brief
 * Indicates an overflow has occurred in the ingress flow control buffer.
 * This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No overflow is detected
 * 1: One or more overflow were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . RX_OVERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_RX_OVERFLOW_DROP_STICKY  VTSS_BIT(20)

/** 
 * \brief
 * Indicates an underflow has occurred in the ingress flow control buffer.
 * This bit is cleared by writing a 1.
 *
 * \details 
 * 0: No underflow is detected
 * 1: One or more underflow were detected
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY . RX_UNDERFLOW_DROP_STICKY
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_RX_UNDERFLOW_DROP_STICKY  VTSS_BIT(21)


/** 
 * \brief Sticky bits interrupt mask register
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:STICKY_MASK
 */
#define VTSS_FC_BUFFER_STATUS_STICKY_MASK    VTSS_IOREG(0x03, 1, 0xf00a)

/** 
 * \brief
 * Interrupt mask for TX_UNCORRECTED_FRM_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . TX_UNCORRECTED_FRM_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_TX_UNCORRECTED_FRM_DROP_STICKY_MASK  VTSS_BIT(2)

/** 
 * \brief
 * Interrupt mask for RX_UNCORRECTED_FRM_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . RX_UNCORRECTED_FRM_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_RX_UNCORRECTED_FRM_DROP_STICKY_MASK  VTSS_BIT(3)

/** 
 * \brief
 * Interrupt mask for TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_TX_CTRL_QUEUE_OVERFLOW_DROP_STICKY_MASK  VTSS_BIT(16)

/** 
 * \brief
 * Interrupt mask for TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_TX_CTRL_QUEUE_UNDERFLOW_DROP_STICKY_MASK  VTSS_BIT(17)

/** 
 * \brief
 * Interrupt mask for TX_DATA_QUEUE_OVERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . TX_DATA_QUEUE_OVERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_TX_DATA_QUEUE_OVERFLOW_DROP_STICKY_MASK  VTSS_BIT(18)

/** 
 * \brief
 * Interrupt mask for TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_TX_DATA_QUEUE_UNDERFLOW_DROP_STICKY_MASK  VTSS_BIT(19)

/** 
 * \brief
 * Interrupt mask for RX_OVERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . RX_OVERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_RX_OVERFLOW_DROP_STICKY_MASK  VTSS_BIT(20)

/** 
 * \brief
 * Interrupt mask for RX_UNDERFLOW_DROP_STICKY
 *
 * \details 
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: VTSS_FC_BUFFER_STATUS_STICKY_MASK . RX_UNDERFLOW_DROP_STICKY_MASK
 */
#define  VTSS_F_FC_BUFFER_STATUS_STICKY_MASK_RX_UNDERFLOW_DROP_STICKY_MASK  VTSS_BIT(21)


/** 
 * \brief Tx control queue overflow frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_CTRL_QUEUE_OVERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_CTRL_QUEUE_OVERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf00b)


/** 
 * \brief Tx control queue underflow frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_CTRL_QUEUE_UNDERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_CTRL_QUEUE_UNDERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf00c)


/** 
 * \brief Tx uncorrected control frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_CTRL_UNCORRECTED_FRM_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_CTRL_UNCORRECTED_FRM_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf00d)


/** 
 * \brief Tx data queue overflow drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_DATA_QUEUE_OVERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_DATA_QUEUE_OVERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf00e)


/** 
 * \brief Tx data queue underflow drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_DATA_QUEUE_UNDERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_DATA_QUEUE_UNDERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf00f)


/** 
 * \brief Tx uncorrected data frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:TX_DATA_UNCORRECTED_FRM_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_TX_DATA_UNCORRECTED_FRM_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf010)


/** 
 * \brief Rx overflow frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:RX_OVERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_RX_OVERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf011)


/** 
 * \brief Rx underflow frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:RX_UNDERFLOW_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_RX_UNDERFLOW_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf012)


/** 
 * \brief Rx uncorrected frame drop counter
 *
 * \details
 * Register: \a FC_BUFFER:STATUS:RX_UNCORRECTED_FRM_DROP_CNT
 */
#define VTSS_FC_BUFFER_STATUS_RX_UNCORRECTED_FRM_DROP_CNT  VTSS_IOREG(0x03, 1, 0xf013)


#endif /* _VTSS_VENICE_REGS_FC_BUFFER_H_ */
