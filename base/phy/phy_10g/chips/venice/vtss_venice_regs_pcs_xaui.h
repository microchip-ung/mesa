// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_PCS_XAUI_H_
#define _VTSS_VENICE_REGS_PCS_XAUI_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a PCS_XAUI
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a PCS_XAUI:PCS_XAUI_CONFIGURATION
 *
 * PCS XAUI Configuration
 */


/** 
 * \brief PCS XAUI Configuration
 *
 * \details
 * PCS XAUI Configuration Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG  VTSS_IOREG(0x04, 0, 0xf000)

/** 
 * \brief
 * Idle sequencing mode (IPG shrink mode support). When active, the first
 * ||I|| after ||T|| will be alternatingly ||K||, ||A|| or ||R|| instead of
 * ||K|| or ||A|| only in normal mode
 *
 * \details 
 * 0 = Normal idle sequencing
 * 1 = Modified idle sequencing for IPG shrink mode support

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG . IDLE_SEQ_MODE
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG_IDLE_SEQ_MODE  VTSS_BIT(12)

/** 
 * \brief
 * Disable RX Pad/Truncate Mode
 *
 * \details 
 * 0 = Normal operation
 * 1 = Disable pad/truncate
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG . PT_DIS
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG_PT_DIS  VTSS_BIT(2)

/** 
 * \brief
 * PCS enable
 *
 * \details 
 * 0 = Disable PCS
 * 1 = Enable PCS
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG . PCS_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG_PCS_ENA  VTSS_BIT(0)


/** 
 * \brief PCS XAUI Configuration
 *
 * \details
 * PCS XAUI Configuration Register 2
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG2  VTSS_IOREG(0x04, 0, 0xf001)

/** 
 * \brief
 * Line loopback H6 that passes through the entire PCS in both directions

 *
 * \details 
 * 0 = Normal  operation
 * 1 = Enable line loopback H6
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG2 . LINE_LOOP_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG2_LINE_LOOP_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Enables the reporting of disparity and illegal symbol errors on the
 * XGMII interface with the K30.7 code when bad symbols are received.
 *
 * \details 
 * 0 = Do not report disparity and illegal symbol errors on XGMII
 * 1 = Report disparity and illegal symbol errors on XGMII using the K30.7 
 * code
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG2 . RX_INGR_ERR_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_CFG2_RX_INGR_ERR_ENA  VTSS_BIT(1)


/** 
 * \brief PCS XAUI Extended Configuration
 *
 * \details
 * Special configuration bit groups for PCS XAUI
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_EXT_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_EXT_CFG  VTSS_IOREG(0x04, 0, 0xf002)


/** 
 * \brief PCS XAUI SignalDetect Configuration
 *
 * \details
 * PCS_XAUI signal_detect configuration
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_SD_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG  VTSS_IOREG(0x04, 0, 0xf003)

/** 
 * \brief
 * Bit to force the signal detect/LOS circuitry to indicate a loss of
 * signal (no valid signal). When asserted, the signal detect is forced low
 * internally causing a loss of synchronization.
 *
 * \details 
 * 0 = Normal operation
 * 1 = Signal Detection is forced to 0 (Signal Lost).
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG . FORCE_LOS
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_FORCE_LOS  VTSS_BIT(8)

/** 
 * \brief
 * LOS polarity: The signal level on los input pin must be equal to LOS_POL
 * to indicate loss of signal (LOS_ENA must be set).
 *
 * \details 
 * 0 = LOS input pin must be '0' to indicate a loss of signal
 * 1 = LOS input pin must be '1' to indicate a loss of signal
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG . LOS_POL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_LOS_POL  VTSS_BIT(5)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0 = Signal Detect input pin must be '0' to indicate a signal detection
 * 1 = Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG . SD_POL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_SD_POL  VTSS_BIT(4)

/** 
 * \brief
 * Loss-Of-Signal (LOS) Enable. When enabled, the LOS signal from the
 * external device is used to determine if a vaild signal is available.
 * When disabled, a vaild signal is assumed. The Signal Detect is ANDed
 * with the LOS if both are enabled. When both SD and LOS are enabled, both
 * must show valid signal for the PCS to see a vaild signal.
 *
 * \details 
 * 0 = The LOS input pin is ignored. The PCS assumes a valid signal at all
 * times
 * 1 = The LOS input pin is used to determine if a signal is detected
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG . LOS_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_LOS_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Signal Detect Enable. When enabled, the 4 signal detect signals from the
 * 4 lanes are used to determine if a vaild signal is available. When
 * disabled, a vaild signal is assumed. The Signal Detect is ANDed with the
 * LOS if both are enabled. When both SD and LOS are enabled, both must
 * show valid signal for the PCS to see a vaild signal.
 *
 * \details 
 * 0 = The Signal Detect input pins are ignored. The PCS assumes a valid
 * Signal Detect at all times
 * 1 = The Signal Detect input pins are used to determine if a signal is
 * detected
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG . SD_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SD_CFG_SD_ENA  VTSS_BIT(0)


/** 
 * \brief PCS Transmitter Sequence Configuration Register
 *
 * \details
 * Sequence Transmit Configuration Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_TX_SEQ_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG  VTSS_IOREG(0x04, 0, 0xf004)

/** 
 * \brief
 * Transmit ||Q|| code (Sequence information, i.e. lower 16 bit of a
 * Sequence)
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG . TX_Q
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG_TX_Q(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG_TX_Q     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG_TX_Q(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Transmitter Sequence Configuration Register
 *
 * \details
 * Sequence Transmit Configuration Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_TX_SEQ_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG2  VTSS_IOREG(0x04, 0, 0xf005)

/** 
 * \brief
 * Disable Transmit ||Q|| code replacement
 *
 * \details 
 * 0 = Enable
 * 1 = Disable

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG2 . TX_Q_DIS
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_TX_SEQ_CFG2_TX_Q_DIS  VTSS_BIT(0)


/** 
 * \brief PCS XAUI Receiver Error Counter Configuration
 *
 * \details
 * Error Counter Configuration Register (if a bit in the mask field is set,
 * the errors of that lane are not counted).
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_RX_ERR_CNT_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG  VTSS_IOREG(0x04, 0, 0xf006)

/** 
 * \brief
 * Disparity error counting mask, one mask bit per lane.  The lane will
 * count errors when the associated mask bit is '0'.
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0000 = Count errors of all lanes
 * 1110 = Count error of lane 0 only
 * ...
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG . DERR_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_DERR_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_DERR_MASK     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_DERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Codegroup error counting mask, one mask bit per lane.  The lane will
 * count errors when the associated mask bit is '0'.
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0000 = Count errors of all lanes
 * 1110 = Count error of lane 0 only
 * ...
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG . CERR_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_CERR_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_CERR_MASK     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_CERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Fifo underflow error counting mask, one mask bit per lane.  The lane
 * will count errors when the associated mask bit is '0'.
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0000 = Count errors of all lanes
 * 1110 = Count error of lane 0 only
 * ...
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG . UFERR_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_UFERR_MASK(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_UFERR_MASK     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_UFERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Fifo overflow error counting mask, one mask bit per lane.  The lane will
 * count errors when the associated mask bit is '0'.
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0000 = Count errors of all lanes
 * 1110 = Count error of lane 0 only
 * ...
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG . OFERR_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_OFERR_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_OFERR_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_RX_ERR_CNT_CFG_OFERR_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PCS Interleave Mode Configuration
 *
 * \details
 * Configuration register set for Interleave Mode (XAUI via two lanes) -
 * also known as DDR-XAUI
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_INTERLEAVE_MODE_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG  VTSS_IOREG(0x04, 0, 0xf007)

/** 
 * \brief
 * Comma replacement. In interleave mode (using /K/ byte orderung) one
 * 20-bit word must have only one comma for proper alignment. Misleading
 * commas are replaced by comma_repl in transmit direction and replaced by
 * K28.5-commas again in receive direction. Comma_repl has to be an unused
 * valid special code-group which does not contain a comma, i.e. K28.2,
 * K28.6 or K23.7 are possible replacements.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG . COMMA_REPL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG_COMMA_REPL(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG_COMMA_REPL     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG_COMMA_REPL(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Interleave mode selection. In interleave mode XAUI data are sent via two
 * 5Gbps lanes
 *
 * \details 
 * 0 = Interleave mode with /K/ comma based byte re-ordering (using comma
 * replacement)
 * 1 = Interleave mode with /A/ alignment symbol based byte re-ordering
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG . ILV_MODE
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG_ILV_MODE  VTSS_BIT(1)

/** 
 * \brief
 * Interleave mode enable. In interleave mode XAUI data are sent via two
 * 5Gbps lanes
 *
 * \details 
 * 0 = Normal XAUI mode
 * 1 = Interleave mode
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG . ILV_MODE_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG_ILV_MODE_ENA  VTSS_BIT(0)


/** 
 * \brief PCS Interleave Mode Configuration
 *
 * \details
 * Configuration register set for Interleave Mode (XAUI via two lanes) -
 * also known as DDR-XAUI
 *
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_INTERLEAVE_MODE_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG2  VTSS_IOREG(0x04, 0, 0xf008)

/** 
 * \brief
 * Dual column ||A|| alignment (||A|| are inserted on even columns only)
 *
 * \details 
 * 0 = Normal insertion
 * 1 = Even column insertion only
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG2 . DC_A_ALIGN_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG2_DC_A_ALIGN_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Comma synchronization mode
 *
 * \details 
 * 0 = Synchronize on any 7-bit comma (XAUI compliant)
 * 1 = Synchronize on K28.5 only (non XAUI compliant)
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG2 . K28_5_SYNC_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_INTERLEAVE_MODE_CFG2_K28_5_SYNC_ENA  VTSS_BIT(0)


/** 
 * \brief Spare Register
 *
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_CONFIGURATION:PCS_XAUI_SPARE
 */
#define VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SPARE  VTSS_IOREG(0x04, 0, 0xf009)

/** 
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SPARE . PCS_XAUI_SPARE
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SPARE_PCS_XAUI_SPARE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SPARE_PCS_XAUI_SPARE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_CONFIGURATION_PCS_XAUI_SPARE_PCS_XAUI_SPARE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCS_XAUI:PCS_XAUI_STATUS
 *
 * PCS XAUI Status
 */


/** 
 * \brief PCS_XAUI Status Register
 *
 * \details
 * PCS_XAUI Status Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS  VTSS_IOREG(0x04, 0, 0xf020)

/** 
 * \brief
 * Status of lane alignment
 *
 * \details 
 * 0 = No alignment reached
 * 1 = All lanes are aligned

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS . ALIGNMENT_STATUS
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS_ALIGNMENT_STATUS  VTSS_BIT(12)

/** 
 * \brief
 * Status of code group alignment (lane independent), one bit for each
 * lane.  The order of the bits is:
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 1111: All lanes in sync
 * 0001: Lane 0 is in sync
 * ...
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS . SYNC_STATUS
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS_SYNC_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS_SYNC_STATUS     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS_SYNC_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PCS Status Register
 *
 * \details
 * PCS Status Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_STATUS2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS2  VTSS_IOREG(0x04, 0, 0xf021)

/** 
 * \brief
 * Status of the link. When 1, the link is in the LINK_OK state. When 0,
 * the link is down (not in LINK_OK).
 *
 * \details 
 * 0 = Link is not in LINK_OK state
 * 1 = Link is in LINK_OK state
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS2 . LINK_STATE
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_STATUS2_LINK_STATE  VTSS_BIT(4)


/** 
 * \brief Interrupt Register
 *
 * \details
 * Register of interrupt generating sticky bits
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_INT
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT  VTSS_IOREG(0x04, 0, 0xf022)

/** 
 * \brief
 * Local Fault status (one or more of sync/align/fifo_of/fifo_uf/8b10b
 * error), one bit for each lane.  The order of the bits is:
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 1 = A fault occured
 * 0 = No fault detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . LOCAL_FAULT_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_LOCAL_FAULT_STICKY(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_LOCAL_FAULT_STICKY     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_LOCAL_FAULT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Interrupt indicating that the Ordered Set FIFO is full.
 *
 * \details 
 * 0 = Overhead FIFO not full
 * 1 = Overhead FIFO full.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . RX_OSET_FIFO_FULL_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_RX_OSET_FIFO_FULL_STICKY  VTSS_BIT(11)

/** 
 * \brief
 * Interrupt indicating that an ordered set was received and captured in
 * the FIFO.
 *
 * \details 
 * 0 = No ordered set captured
 * 1 = Ordered set captured in FIFO
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . RX_OSET_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_RX_OSET_STICKY  VTSS_BIT(10)

/** 
 * \brief
 * This bit is asserted when the PCS enters or leaves the LINK_OK state
 *
 * \details 
 * 0 = No change
 * 1 = Link has changed into or out of the LINK_OK state
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . LINK_CHANGE_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_LINK_CHANGE_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * A change was detected in ALIGNMENT_STATUS.
 *
 * \details 
 * 0 = No change
 * 1 = A change was detected (rising or falling)
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . ALIGNMENT_CHANGE_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_ALIGNMENT_CHANGE_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * A change was detected in SYNC_STATUS. One bit is asserted per lane: 
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0 = No change
 * 1 = A change was detected (rising or falling)
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT . SYNC_CHANGE_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_SYNC_CHANGE_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_SYNC_CHANGE_STICKY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT_SYNC_CHANGE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Interrupt Register
 *
 * \details
 * Register of interrupt generating sticky bits
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_INT2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2  VTSS_IOREG(0x04, 0, 0xf023)

/** 
 * \brief
 * Interrupt indicating that the Signal Ordered Set FIFO is full.
 *
 * \details 
 * 0 = Overhead FIFO not full
 * 1 = Overhead FIFO full.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . RX_FSET_FIFO_FULL_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_RX_FSET_FIFO_FULL_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt indicating that an signal ordered set was received and
 * captured in the FIFO.
 *
 * \details 
 * 0 = No signal ordered set captured
 * 1 = Signal ordered set captured in FIFO
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . RX_FSET_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_RX_FSET_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * Received ||Fsig|| code changed
 *
 * \details 
 * 1 = New ||Fsig|| has been received
 * 0 = No new ||Fsig|| since last read
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . RX_FSIG_CHANGED_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_RX_FSIG_CHANGED_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * Received ||Q|| code changed
 *
 * \details 
 * 1 = New ||Q|| has been received
 * 0 = No new ||Q|| since last read
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . RX_Q_CHANGED_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_RX_Q_CHANGED_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * Coding error detected in received 8B/10B encoded data
 *
 * \details 
 * 0 = No error found
 * 1 = Coding error detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . C8B10B_ERR_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_C8B10B_ERR_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * Alignment lost in deskew logic
 *
 * \details 
 * 0 = No misalignment occured
 * 1 = A (temporary) misalignment has been detected
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . ALIGNMENT_LOST_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_ALIGNMENT_LOST_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Synchronization lost in lane i (i = 0...3, one bit per lane)  The order
 * of the bits is:
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0 = No sync lost occured
 * 1 = Synchronization lost in lane i (temporarily)
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2 . SYNC_LOST_STICKY
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_SYNC_LOST_STICKY(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_SYNC_LOST_STICKY     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_INT2_SYNC_LOST_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Mask Register
 *
 * \details
 * Register of mask bits for PCS_XAUI_INT
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_MASK
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK  VTSS_IOREG(0x04, 0, 0xf024)

/** 
 * \brief
 * Interrupt mask for LOCAL_FAULT_STICKY, one bit for each lane.  The order
 * of the bits is:
 * 
 * <lane_3><lane_2><lane_1><lane_0>
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . LOCAL_FAULT_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_LOCAL_FAULT_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_LOCAL_FAULT_MASK     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_LOCAL_FAULT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Interrupt mask for RX_OSET_FIFO_FULL_STICKY.
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . RX_OSET_FIFO_FULL_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_RX_OSET_FIFO_FULL_MASK  VTSS_BIT(11)

/** 
 * \brief
 * Interrupt Mask for the RX_OSET_STICKY bit.
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . RX_OSET_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_RX_OSET_MASK  VTSS_BIT(10)

/** 
 * \brief
 * Interrupt mask for LINK_CHANGE_STICKY.
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . LINK_CHANGE_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_LINK_CHANGE_MASK  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt mask for ALIGNMENT_CHANGE_STICKY.
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . ALIGNMENT_CHANGE_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_ALIGNMENT_CHANGE_MASK  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt mask for SYNC_CHANGE_STICKY. One bit per lane.
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK . SYNC_CHANGE_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_SYNC_CHANGE_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_SYNC_CHANGE_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK_SYNC_CHANGE_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Mask Register
 *
 * \details
 * Register of mask bits for PCS_XAUI_INT2
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_MASK2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2  VTSS_IOREG(0x04, 0, 0xf025)

/** 
 * \brief
 * Interrupt mask bit for RX_FSET_FIFO_FULL_STICKY
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . RX_FSET_FIFO_FULL_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_RX_FSET_FIFO_FULL_MASK  VTSS_BIT(9)

/** 
 * \brief
 * Interrupt mask bit for RX_FSET_STICKY
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . RX_FSET_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_RX_FSET_MASK  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt mask for RX_FSIG_CHANGED_STICKY
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . RX_FSIG_CHANGED_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_RX_FSIG_CHANGED_MASK  VTSS_BIT(7)

/** 
 * \brief
 * Interrupt mask for RX_Q_CHANGED_STICKY
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . RX_Q_CHANGED_INT_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_RX_Q_CHANGED_INT_MASK  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt mask for C8B10B_ERR_STICKY.
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . C8B10B_ERR_INT_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_C8B10B_ERR_INT_MASK  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt mask for ALIGNMENT_LOST_STICKY
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . ALIGNMENT_LOST_INT_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_ALIGNMENT_LOST_INT_MASK  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt mask for SYNC_LOST_STICKY, one bit per lane.   
 *
 * \details 
 * 0 = Interrupt disabled
 * 1 = Interrupt enabled
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2 . SYNC_LOST_INT_MASK
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_SYNC_LOST_INT_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_SYNC_LOST_INT_MASK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_MASK2_SYNC_LOST_INT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PCS Receiver Sequence Result Register
 *
 * \details
 * ||Q|| Sequence Receive Status Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_RX_SEQ_REC_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_SEQ_REC_STATUS  VTSS_IOREG(0x04, 0, 0xf026)

/** 
 * \brief
 * Received ||Q|| code (Sequence information, i.e. lower 24 bit of a
 * Sequence)
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_SEQ_REC_STATUS . RX_Q
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_SEQ_REC_STATUS_RX_Q(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_SEQ_REC_STATUS_RX_Q     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_SEQ_REC_STATUS_RX_Q(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS Receiver Signal Ordered Set Result Register
 *
 * \details
 * ||Fsig|| Sequence Receive Status Register
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:PCS_XAUI_RX_FSIG_REC_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_FSIG_REC_STATUS  VTSS_IOREG(0x04, 0, 0xf027)

/** 
 * \brief
 * Received ||Fsig|| code (Sequence information, i.e. lower 24 bit of a
 * Sequence)
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_FSIG_REC_STATUS . RX_FSIG
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_FSIG_REC_STATUS_RX_FSIG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_FSIG_REC_STATUS_RX_FSIG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_PCS_XAUI_RX_FSIG_REC_STATUS_RX_FSIG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Status of ||Q|| overhead FIFO.
 *
 * \details
 * Contains status information for the FIFO containing captured Rx Sequence
 * Ordered Sets.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:RX_OSET_FIFO_STAT
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT  VTSS_IOREG(0x04, 0, 0xf028)

/** 
 * \brief
 * Indicates if the FIFO is full
 *
 * \details 
 * 0 = FIFO not full
 * 1 = FIFO full
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT . RX_OSET_FIFO_FULL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_FULL  VTSS_BIT(4)

/** 
 * \brief
 * Number of valid ordered sets in the FIFO that can be read.
 *
 * \details 
 * Binary number
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT . RX_OSET_FIFO_NUM
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_STAT_RX_OSET_FIFO_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Rx ||Q|| Overhead FIFO Data
 *
 * \details
 * The register interface to the sequence ordered set data
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:RX_OSET_FIFO_DATA
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_DATA  VTSS_IOREG(0x04, 0, 0xf029)

/** 
 * \brief
 * Register interface to the FIFO containing captured ordered sets. Each
 * read of this register pops a 16-bit ordered set off the FIFO and
 * increments the FIFO pointer. The data is only the upper 16 bits and does
 * not include the control character.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_DATA . RX_OSET_FIFO_DATA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_RX_OSET_FIFO_DATA_RX_OSET_FIFO_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Status of ||Fsig|| overhead FIFO.
 *
 * \details
 * Contains status information for the FIFO containing captured Rx Signal
 * Ordered Sets.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:RX_FSET_FIFO_STAT
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT  VTSS_IOREG(0x04, 0, 0xf02a)

/** 
 * \brief
 * Indicates if the FIFO is full
 *
 * \details 
 * 0 = FIFO not full
 * 1 = FIFO full
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT . RX_FSET_FIFO_FULL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_FULL  VTSS_BIT(4)

/** 
 * \brief
 * Number of valid ordered sets in the FIFO that can be read.
 *
 * \details 
 * Binary number
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT . RX_FSET_FIFO_NUM
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_STAT_RX_FSET_FIFO_NUM(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief Rx ||Fsig|| Overhead FIFO Data
 *
 * \details
 * The register interface to the signal ordered set data
 *
 * Register: \a PCS_XAUI:PCS_XAUI_STATUS:RX_FSET_FIFO_DATA
 */
#define VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_DATA  VTSS_IOREG(0x04, 0, 0xf02b)

/** 
 * \brief
 * Register interface to the FIFO containing captured ordered sets. Each
 * read of this register pops a 16-bit ordered set off the FIFO and
 * increments the FIFO pointer. The data is only the upper 16 bits and does
 * not include the control character.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_DATA . RX_FSET_FIFO_DATA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_STATUS_RX_FSET_FIFO_DATA_RX_FSET_FIFO_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS
 *
 * PCS Error Counters
 */


/** 
 * \brief Alignment Error Counter
 *
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_RX_ALIGN_ERR_CNT
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_ALIGN_ERR_CNT  VTSS_IOREG(0x04, 0, 0xf040)

/** 
 * \brief
 * This counter counts the number of alignment errors in the RX direction. 
 * This counter will saturate at 0xffff.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_ALIGN_ERR_CNT . PCS_XAUI_RX_ALIGN_ERR_CNT
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_ALIGN_ERR_CNT_PCS_XAUI_RX_ALIGN_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_ALIGN_ERR_CNT_PCS_XAUI_RX_ALIGN_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_ALIGN_ERR_CNT_PCS_XAUI_RX_ALIGN_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief XGMII Sequence Error Counter
 *
 * \details
 * Counts the number of invalid  XGMII codes in the TX direction
 *
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_XGMII_ERR_CNT
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_XGMII_ERR_CNT  VTSS_IOREG(0x04, 0, 0xf041)

/** 
 * \brief
 * Counts the number of invalid control codes that are generated in the TX
 * path. This may be more than the number of invalid XGMII errors present
 * at the input XGMII interface. e.g. if 1 character in an input IDLE
 * column is corrupted, this will result in an invalid XGMII control code
 * and 4 output error characters. This counter will increment by 4 and will
 * saturate at 0xffff
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_XGMII_ERR_CNT . PCS_XAUI_XGMII_ERR_CNT
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_XGMII_ERR_CNT_PCS_XAUI_XGMII_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_XGMII_ERR_CNT_PCS_XAUI_XGMII_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_XGMII_ERR_CNT_PCS_XAUI_XGMII_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS RX Fifo Overflow Error and Lane 0 Error Counter
 *
 * \details
 * Receive Fifo Overflow error counter. In normal mode provides the count
 * of FIFO overflow errors. In test pattern check mode, this counter counts
 * the errors of lane 0. In the latter case the counter is incremented by
 * one whenever at least one out of eighty received bits (eight symbols) is
 * corrupted. In test-pattern mode, this counter is shared between normal
 * and PRBS pattern blocks.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS  VTSS_IOREG(0x04, 0, 0xf042)

/** 
 * \brief
 * Number of detected fifo overflow errors/Number of errors in lane 0. 
 * This counter will saturate at 0xffff.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS . ERR_CNT_FIFO_OF_L0
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS_ERR_CNT_FIFO_OF_L0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS_ERR_CNT_FIFO_OF_L0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_OF_ERR_L0_CNT_STATUS_ERR_CNT_FIFO_OF_L0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS RX Fifo Underflow Error and Lane 1 Error Counter
 *
 * \details
 * Receive Fifo Underflow error counter. In normal mode provides the count
 * of FIFO Underflow errors. In test pattern check mode, this counter
 * counts the errors of lane 1. In the latter case the counter is
 * incremented by one whenever at least one out of eighty received bits
 * (eight symbols) is corrupted. In test-pattern mode, this counter is
 * shared between normal and PRBS pattern blocks.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS  VTSS_IOREG(0x04, 0, 0xf043)

/** 
 * \brief
 * Number of detected fifo underflow errors/Number of errors in lane 1. 
 * This counter will saturate at 0xffff.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS . ERR_CNT_FIFO_UF_L1
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS_ERR_CNT_FIFO_UF_L1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS_ERR_CNT_FIFO_UF_L1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_UF_ERR_L1_CNT_STATUS_ERR_CNT_FIFO_UF_L1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS RX 10b8b Disparity Error and Lane 2 Error Counter
 *
 * \details
 * 10b8b Decoder Disparity error counter. In normal mode provides the count
 * of Disparity errors. In test pattern check mode, this counter counts the
 * errors of lane 2. In the latter case the counter is incremented by one
 * whenever at least one out of eighty received bits (eight symbols) is
 * corrupted. In test-pattern mode, this counter is shared between normal
 * and PRBS pattern blocks.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS  VTSS_IOREG(0x04, 0, 0xf044)

/** 
 * \brief
 * Number of detected disparity errors/Number of errors in lane 2.   This
 * counter will saturate at 0xffff.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS . ERR_CNT_10B8B_D_L2
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS_ERR_CNT_10B8B_D_L2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS_ERR_CNT_10B8B_D_L2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_D_ERR_L2_CNT_STATUS_ERR_CNT_10B8B_D_L2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PCS RX 10b8b Codegroup Error and Lane 3 Error Counter
 *
 * \details
 * 10b8b Decoder Codegroup error counter. In normal mode provides the count
 * of Codegroup errors. In test pattern check mode, this counter counts the
 * errors of lane 3. In the latter case the counter is incremented by one
 * whenever at least one out of eighty received bits (eight symbols) is
 * corrupted. In test-pattern mode, this counter is shared between normal
 * and PRBS pattern blocks.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_ERR_COUNTERS:PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS  VTSS_IOREG(0x04, 0, 0xf045)

/** 
 * \brief
 * Number of detected codegroup errors/Number of errors in lane 3.   This
 * counter will saturate at 0xffff.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS . ERR_CNT_10B8B_CG_L3
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS_ERR_CNT_10B8B_CG_L3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS_ERR_CNT_10B8B_CG_L3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_ERR_COUNTERS_PCS_XAUI_RX_FIFO_CG_ERR_L3_CNT_STATUS_ERR_CNT_10B8B_CG_L3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION
 *
 * XAUI PRBS Test Pattern Generator
 */


/** 
 * \brief Test Pattern Generator/Checker Control
 *
 * \details
 * Note: functions in this register are overridden by
 * PCS_XAUI_XGXS_TST_CTRL when PCS_XAUI_XGXS_TST_CTRL.TSTPAT_EN is set
 *
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_CTRL_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG  VTSS_IOREG(0x04, 0, 0xf0a0)

/** 
 * \brief
 * prbs flip pattern
 *
 * \details 
 * 0 = normal use of prbs
 * 1 = flip pattern from prbs generator

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . PRBS_BUS_FLIP
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_PRBS_BUS_FLIP  VTSS_BIT(13)

/** 
 * \brief
 * prbs pattern inversion
 *
 * \details 
 * 0 = normal polarity of polynomial
 * 1 = invert prbs polynomial

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . PRBS_POLY_INV
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_PRBS_POLY_INV  VTSS_BIT(12)

/** 
 * \brief
 * Capture current error counter values
 *
 * \details 
 * 0 = Normal operation
 * 1 = Capture 
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . FREEZE_ERR_CNT_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_FREEZE_ERR_CNT_ENA  VTSS_BIT(10)

/** 
 * \brief
 * Enable Test pattern checker
 *
 * \details 
 * 0 = No checking
 * 1 = Check

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . VT_CHK_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_CHK_ENA  VTSS_BIT(9)

/** 
 * \brief
 * Check test pattern
 *
 * \details 
 * 0000 = Reserved
 * 0001 = HFPAT
 * 0010 = LFPAT
 * 0011 = MFPAT
 * 0100 = Reserved
 * 0101 = Reserved
 * 0110 = Reserved
 * 0111 = PRBS (2^7-1)
 * 1000 = PRBS (2^23-1)
 * 1001 = PRBS (2^31-1)
 * 1010 = PRPAT
 * 1011..1111 = Reserved
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . VT_CHK_SEL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_CHK_SEL(x)  VTSS_ENCODE_BITFIELD(x,5,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_CHK_SEL     VTSS_ENCODE_BITMASK(5,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_CHK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,4)

/** 
 * \brief
 * Enable Test pattern generator
 *
 * \details 
 * 0 = normal operation
 * 1 = generate

 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . VT_GEN_ENA
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_GEN_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Generate test pattern
 *
 * \details 
 * 0000 = Idle
 * 0001 = HFPAT
 * 0010 = LFPAT
 * 0011 = MFPAT
 * 0100 = Reserved
 * 0101 = Reserved
 * 0110 = Reserved
 * 0111 = PRBS (2^7-1)
 * 1000 = PRBS (2^23-1)
 * 1001 = PRBS (2^31-1)
 * 1010 = PRPAT
 * 1011..1111 =  Idle
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG . VT_GEN_SEL
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_GEN_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_GEN_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_CTRL_CFG_VT_GEN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Programmable Pattern 0
 *
 * \details
 * Pattern provided at transmitter resp. pattern to check against in
 * receiver when Test Pattern Generator/Checker is in PRPAT (PRogrammable
 * PATtern) mode. This register is for lane 0 only.
 * 
 * The specified pattern is sent directly out on the wire, no disparity
 * protection is performed.  Try to use DC-balanced patterns otherwise
 * AC-coupled lines might saturate at a rail and cause errors.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L0_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG  VTSS_IOREG(0x04, 0, 0xf0a1)

/** 
 * \brief
 * Constant Generator Pattern for lane 0
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG . GEN_PAT_L0
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG_GEN_PAT_L0(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG_GEN_PAT_L0     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG_GEN_PAT_L0(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L0_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG2  VTSS_IOREG(0x04, 0, 0xf0a2)

/** 
 * \brief
 * Constant Checker Pattern for lane 0
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG2 . CHK_PAT_L0
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG2_CHK_PAT_L0(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG2_CHK_PAT_L0     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L0_CFG2_CHK_PAT_L0(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Programmable Pattern 1
 *
 * \details
 * Pattern provided at transmitter resp. pattern to check against in
 * receiver when Test Pattern Generator/Checker is in PRPAT (PRogrammable
 * PATtern) mode. This register is for lane 1 only.
 * 
 * The specified pattern is sent directly out on the wire, no disparity
 * protection is performed.  Try to use DC-balanced patterns otherwise
 * AC-coupled lines might saturate at a rail and cause errors.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L1_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG  VTSS_IOREG(0x04, 0, 0xf0a3)

/** 
 * \brief
 * Constant Generator Pattern for lane 1
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG . GEN_PAT_L1
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG_GEN_PAT_L1(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG_GEN_PAT_L1     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG_GEN_PAT_L1(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L1_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG2  VTSS_IOREG(0x04, 0, 0xf0a4)

/** 
 * \brief
 * Constant Checker Pattern for lane 1
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG2 . CHK_PAT_L1
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG2_CHK_PAT_L1(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG2_CHK_PAT_L1     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L1_CFG2_CHK_PAT_L1(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Programmable Pattern 2
 *
 * \details
 * Pattern provided at transmitter resp. pattern to check against in
 * receiver when Test Pattern Generator/Checker is in PRPAT (PRogrammable
 * PATtern) mode. This register is for lane 2 only.
 * 
 * The specified pattern is sent directly out on the wire, no disparity
 * protection is performed.  Try to use DC-balanced patterns otherwise
 * AC-coupled lines might saturate at a rail and cause errors.
 *
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L2_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG  VTSS_IOREG(0x04, 0, 0xf0a5)

/** 
 * \brief
 * Constant Generator Pattern for lane 2
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG . GEN_PAT_L2
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG_GEN_PAT_L2(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG_GEN_PAT_L2     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG_GEN_PAT_L2(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L2_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG2  VTSS_IOREG(0x04, 0, 0xf0a6)

/** 
 * \brief
 * Constant Checker Pattern for lane 2
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG2 . CHK_PAT_L2
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG2_CHK_PAT_L2(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG2_CHK_PAT_L2     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L2_CFG2_CHK_PAT_L2(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief Programmable Pattern 3
 *
 * \details
 * Pattern provided at transmitter resp. pattern to check against in
 * receiver when Test Pattern Generator/Checker is in PRPAT (PRogrammable
 * PATtern) mode. This register is for lane 3 only.
 * 
 * The specified pattern is sent directly out on the wire, no disparity
 * protection is performed.  Try to use DC-balanced patterns otherwise
 * AC-coupled lines might saturate at a rail and cause errors.

 *
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L3_CFG
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG  VTSS_IOREG(0x04, 0, 0xf0a7)

/** 
 * \brief
 * Constant Generator Pattern for lane 3
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG . GEN_PAT_L3
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG_GEN_PAT_L3(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG_GEN_PAT_L3     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG_GEN_PAT_L3(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_CONFIGURATION:PCS10G_TSTPAT_PRPAT_L3_CFG2
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG2  VTSS_IOREG(0x04, 0, 0xf0a8)

/** 
 * \brief
 * Constant Checker Pattern for lane 3
 *
 * \details 
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG2 . CHK_PAT_L3
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG2_CHK_PAT_L3(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG2_CHK_PAT_L3     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_CONFIGURATION_PCS10G_TSTPAT_PRPAT_L3_CFG2_CHK_PAT_L3(x)  VTSS_EXTRACT_BITFIELD(x,0,10)

/**
 * Register Group: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_STATUS
 *
 * XAUI PRBS Test Pattern Generator
 */


/** 
 * \brief Test pattern status register
 *
 * \details
 * Register: \a PCS_XAUI:PCS_XAUI_PRBS_TSTPAT_STATUS:PCS10G_TSTPAT_STATUS
 */
#define VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_STATUS_PCS10G_TSTPAT_STATUS  VTSS_IOREG(0x04, 0, 0xf0c0)

/** 
 * \brief
 * For each lane, indicates if the selected pattern is matching what is
 * being received
 * Applies to per-lane test patterns configured in PCS10G_TSTPAT_CTRL_CFG

 *
 * \details 
 * 0 = No match
 * 1 = Match
 *
 * Field: VTSS_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_STATUS_PCS10G_TSTPAT_STATUS . PATTERN_MATCH
 */
#define  VTSS_F_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_STATUS_PCS10G_TSTPAT_STATUS_PATTERN_MATCH(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_STATUS_PCS10G_TSTPAT_STATUS_PATTERN_MATCH     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PCS_XAUI_PCS_XAUI_PRBS_TSTPAT_STATUS_PCS10G_TSTPAT_STATUS_PATTERN_MATCH(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a PCS_XAUI:ANEG_CFG
 *
 * ANEG Configuration Registers
 */


/** 
 * \brief ANEG Configuration
 *
 * \details
 * Auto-negotiation configuration register. Note: Setting one of the
 * parallel detect wait times to 0 disables parallel detect function for
 * that specific mode.
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_CFG
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_CFG      VTSS_IOREG(0x04, 0, 0xf0e0)

/** 
 * \brief
 * Disable automatic ANEG OB configuration
 *
 * \details 
 * 0 = Allow ANEG block to control OB during auto-negotiation
 * 1 = OB settings are not touched by ANEG block
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_CFG . ANEG_OB_CTRL_DIS
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_CFG_ANEG_OB_CTRL_DIS  VTSS_BIT(16)

/** 
 * \brief
 * Parallel detect wait time for 10G using four lanes
 *
 * \details 
 * 0 = 0 ms
 * 1 = 10 ms
 * 2 = 20 ms
 * 3 = 40 ms
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_CFG . PD_TIMER_10GKX4
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_CFG_PD_TIMER_10GKX4(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Restart negotiation process. This is a one-shot and writing a '1'
 * asserts the restart. The bit is deasserted automatically.
 *
 * \details 
 * Write 1: Restart
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_CFG . RESTART_ANEG_ONE_SHOT
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_CFG_RESTART_ANEG_ONE_SHOT  VTSS_BIT(1)

/** 
 * \brief
 * Auto-negotiation enable
 *
 * \details 
 * 0 = Disable
 * 1 = Enable
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_CFG . ANEG_ENA
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_CFG_ANEG_ENA  VTSS_BIT(0)


/** 
 * \brief ANEG Advertised Ability 0
 *
 * \details
 * 48 bits that contain the advertised abilities link code word for
 * auto-negotiation (here: lower 32 bit).
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_ADV_ABILITY_0
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0  VTSS_IOREG(0x04, 0, 0xf0e1)

/** 
 * \brief
 * Reserved for future technology as defined in IEEE 802.3ap clause 73.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . ADV_ABIL_LSB
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ADV_ABIL_LSB(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Technology Ability to be advertised (here: 10GBase-KR). Should be left
 * at its default value.
 *
 * \details 
 * 0 = Do not advertise 10GB-KR capability
 * 1 = Advertise 10GB-KR capability
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_10GKR
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKR  VTSS_BIT(23)

/** 
 * \brief
 * Technology Ability to be advertised (here: 10GBase-KX4)
 *
 * \details 
 * 0 = Do not advertise 10GB-KX4 capability
 * 1 = Advertise 10GB-KX4 capability
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_10GKX4
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_10GKX4  VTSS_BIT(22)

/** 
 * \brief
 * Technology Ability to be advertised (here: 1000Base-KX). Should be left
 * at its default value.
 *
 * \details 
 * 0 = Do not advertise 1GB-KX capability
 * 1 = Advertise 1GB-KX capability
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . CAP_1GKX
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_CAP_1GKX  VTSS_BIT(21)

/** 
 * \brief
 * Initial value for Transmit-Nonce field
 *
 * \details 
 * 5-bit binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . TX_NONCE
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_TX_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Next page exchange desired
 *
 * \details 
 * 0 = Disable NP exchange
 * 1 = Enable NP exchange
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . NP
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_NP  VTSS_BIT(15)

/** 
 * \brief
 * Remote Fault (RF) bit (initial value)
 *
 * \details 
 * 0 = No fault
 * 1 = Fault
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . RF
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_RF  VTSS_BIT(13)

/** 
 * \brief
 * Pause field
 *
 * \details 
 * 0 = Pause not supported
 * 1 = Pause supported
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . PAUSE
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_PAUSE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Reserved for echoed nonce field. Should be 0 when ACKN is set to 0. Set
 * to the received NONCE from the link partner when ACKN is 1.
 *
 * \details 
 * binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . ECHOED_NONCE
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Selector field (must be 0x1)
 *
 * \details 
 * binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0 . SEL_FIELD
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief ANEG Advertised Ability 1
 *
 * \details
 * 48 bits that contain the advertised abilities link code word for
 * auto-negotiation (here: upper 16 bit).
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_ADV_ABILITY_1
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1  VTSS_IOREG(0x04, 0, 0xf0e2)

/** 
 * \brief
 * FEC capability (bit 14: FEC ability, bit 15: FEC requested) - Only used
 * with 10GBase-KR and should be set to 0 by default. Should be left at its
 * default value.
 *
 * \details 
 * Bit 14 = 0 : FEC not available
 * Bit 14 = 1 : FEC available
 * Bit 15 = 0 : Do Not Request FEC
 * Bit 15 = 1: Request FEC
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1 . FEC
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_FEC(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Reserved for future technology as defined in IEEE 802.3ap clause 73.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1 . ADV_ABIL_MSB
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_ADV_ABILITY_1_ADV_ABIL_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief ANEG Next Page 0
 *
 * \details
 * 48 bits that contain the new next page to transmit during
 * auto-negotiation (here: lower 32 bits).
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_NEXT_PAGE_0
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_0  VTSS_IOREG(0x04, 0, 0xf0e3)


/** 
 * \brief ANEG Next Page 1
 *
 * \details
 * 48 bits that contain the new next page to transmit during
 * auto-negotiation (here: upper 16 bits).
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_NEXT_PAGE_1
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1  VTSS_IOREG(0x04, 0, 0xf0e4)

/** 
 * \brief
 * Must be set when a new next page is programmed (self-clearing)
 *
 * \details 
 * Write 1: Indicate that a page was programmed.
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1 . NEXT_PAGE_LOADED_ONE_SHOT
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1_NEXT_PAGE_LOADED_ONE_SHOT  VTSS_BIT(31)

/** 
 * \brief
 * Upper 16 bits of next page link code word
 *
 * \details 
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1 . NP_TX_MSB
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PCS_XAUI_ANEG_CFG_ANEG_NEXT_PAGE_1_NP_TX_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Mask bits for interrupts
 *
 * \details
 * The bits in the interrupt mask register are used to enable the
 * associated interrupts. Status is available in ANEG_STATUS. Setting the
 * bit to '1' enables the interrupt.
 *
 * Register: \a PCS_XAUI:ANEG_CFG:ANEG_MASK
 */
#define VTSS_PCS_XAUI_ANEG_CFG_ANEG_MASK     VTSS_IOREG(0x04, 0, 0xf0e5)

/** 
 * \brief
 * Mask bit for INCOMPATIBLE_LINK_STICKY
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_MASK . INCOMPATIBLE_LINK_MASK
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_MASK_INCOMPATIBLE_LINK_MASK  VTSS_BIT(21)

/** 
 * \brief
 * Interrupt mask for PAR_DETECT_FAULT.
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_MASK . PAR_DETECT_FAULT_MASK
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_MASK_PAR_DETECT_FAULT_MASK  VTSS_BIT(16)

/** 
 * \brief
 * Interrupt mask for PAGE_RX_STICKY.
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_MASK . PAGE_RX_MASK
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_MASK_PAGE_RX_MASK  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt mask for ANEG_COMPLETE_STICKY.
 *
 * \details 
 * 0 = Interrupt Disabled
 * 1 = Interrupt Enabled
 *
 * Field: VTSS_PCS_XAUI_ANEG_CFG_ANEG_MASK . ANEG_COMPLETE_MASK
 */
#define  VTSS_F_PCS_XAUI_ANEG_CFG_ANEG_MASK_ANEG_COMPLETE_MASK  VTSS_BIT(1)

/**
 * Register Group: \a PCS_XAUI:ANEG_STATUS
 *
 * ANEG Status Registers
 */


/** 
 * \brief ANEG Link Partner Advertised Ability 0
 *
 * \details
 * 48 bits that contain the link partner's advertised abilities / next page
 * information (received link code word, lower 32 bits, received during
 * auto-negotiation). The bit groups are only valid for base pages; for
 * next page data exchange a different bit group coding has to be applied.
 *
 * Register: \a PCS_XAUI:ANEG_STATUS:ANEG_LP_ADV_ABILITY_0
 */
#define VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0  VTSS_IOREG(0x04, 0, 0xf100)

/** 
 * \brief
 * Bits 31 down to 24 of link code word received from link partner.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . LP_ADV_ABIL_LSB
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_LP_ADV_ABIL_LSB(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 10GBase-KR)
 *
 * \details 
 * 0 = LP is not 10GB-KR capable
 * 1 = LP is 10GB-KR capable
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_10GKR
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKR  VTSS_BIT(23)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 10GBase-KX4)
 *
 * \details 
 * 0 = LP is not 10GB-KX4 capable
 * 1 = LP is 10GB-KX4 capable
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_10GKX4
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_10GKX4  VTSS_BIT(22)

/** 
 * \brief
 * Technology Ability advertised by LP (here: 1000Base-KX)
 *
 * \details 
 * 0 = LP is not 1GB-KX capable
 * 1 = LP is 1GB-KX capable
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . CAP_1GKX
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_CAP_1GKX  VTSS_BIT(21)

/** 
 * \brief
 * Transmit-Nonce field (received from LinkPartner)
 *
 * \details 
 * 5-bit binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . TX_NONCE
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_TX_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Next page exchange desired by LP
 *
 * \details 
 * 0 = No NP exchange desired
 * 1 = NP exchange desired
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . NP
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_NP  VTSS_BIT(15)

/** 
 * \brief
 * Acknowledge bit (this bit is automatically overwritten by ANEG)
 *
 * \details 
 * 0 = Link Codeword not received by partner
 * 1 = Link Codeword received by partner
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . ACKN
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ACKN  VTSS_BIT(14)

/** 
 * \brief
 * Remote Fault (RF) bit
 *
 * \details 
 * 0 = No fault
 * 1 = Fault
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . RF
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_RF  VTSS_BIT(13)

/** 
 * \brief
 * Pause field
 *
 * \details 
 * 0 = Pause not supported
 * 1 = Pause supported
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . PAUSE
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_PAUSE(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Echoed nonce field
 *
 * \details 
 * binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . ECHOED_NONCE
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_ECHOED_NONCE(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Selector field
 *
 * \details 
 * binary number
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0 . SEL_FIELD
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_0_SEL_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief ANEG Link Partner Advertised Ability 1
 *
 * \details
 * 48 bits that contain the link partner's advertised abilities or next
 * page information (received link code word, upper 16 bits, received
 * during auto-negotiation). The bit groups are only valid for base pages;
 * for next page data exchange a different bit group coding has to be
 * applied.
 *
 * Register: \a PCS_XAUI:ANEG_STATUS:ANEG_LP_ADV_ABILITY_1
 */
#define VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1  VTSS_IOREG(0x04, 0, 0xf101)

/** 
 * \brief
 * FEC capability (bit 14: FEC ability, bit 15: FEC requested) - Only used
 * with 10GBase-KR
 *
 * \details 
 * Bit 14 = 0 : FEC not available
 * Bit 14 = 1 : FEC available
 * Bit 15 = 0 : Do Not Request FEC
 * Bit 15 = 1: Request FEC
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1 . FEC
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_FEC(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Bits 45 down to 32 of link code word received from link partner.
 *
 * \details 
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1 . LP_ADV_ABIL_MSB
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,14)
#define  VTSS_M_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB     VTSS_ENCODE_BITMASK(0,14)
#define  VTSS_X_PCS_XAUI_ANEG_STATUS_ANEG_LP_ADV_ABILITY_1_LP_ADV_ABIL_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,14)


/** 
 * \brief ANEG Status
 *
 * \details
 * Auto negotiation status register
 *
 * Register: \a PCS_XAUI:ANEG_STATUS:ANEG_STATUS
 */
#define VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS  VTSS_IOREG(0x04, 0, 0xf102)

/** 
 * \brief
 * Sticky bit for the INCOMPATIBLE_LINK status bit. The sticky is set
 * whenever the state of INCOMPATIBLE_LINK is set. Bit is cleared by
 * writing a 1 to this position.
 *
 * \details 
 * 0 = INCOMPATIBLE_LINK is not set (link compatible)
 * 1 = INCOMPATIBLE_LINK has been set
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . INCOMPATIBLE_LINK_STICKY
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_INCOMPATIBLE_LINK_STICKY  VTSS_BIT(21)

/** 
 * \brief
 * Error condition indicating that no compatible link was found.
 *
 * \details 
 * 0 = Link is compatible
 * 1 = Link is incompatible
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . INCOMPATIBLE_LINK
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_INCOMPATIBLE_LINK  VTSS_BIT(17)

/** 
 * \brief
 * Error condition indicating errors during parallel detection. Bit is
 * cleared by writing a 1 to this position.
 *
 * \details 
 * 0 = No fault detected
 * 1 = Parallel Detection Fault detected
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . PAR_DETECT_FAULT_STICKY
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_PAR_DETECT_FAULT_STICKY  VTSS_BIT(16)

/** 
 * \brief
 * Sticky bit set when PAGE_RX is set.
 *
 * \details 
 * 0 = PAGE_RX bit has not been set.
 * 1 = PAGE_RX bit has changed from 0 to 1.
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . PAGE_RX_STICKY
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_PAGE_RX_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * Status indicating whether a new page has been received.
 *
 * \details 
 * 0 = No page received
 * 1 = Page received
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . PAGE_RX
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_PAGE_RX  VTSS_BIT(3)

/** 
 * \brief
 * Status indicating whether the link partner supports auto-negotiation.
 *
 * \details 
 * 0 = Link Partner does NOT support ANEG
 * 1 = Link Partner supports ANEG
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . LP_ANEG_ABLE
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_LP_ANEG_ABLE  VTSS_BIT(2)

/** 
 * \brief
 * Sticky for ANEG_COMPLETE. Bit is set whenever the ANEG_COMPLETE status
 * is set.
 *
 * \details 
 * 0 = ANEG_COMPLETE status is not set.
 * 1 = ANEG_COMPLETE status set to 1.
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . ANEG_COMPLETE_STICKY
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_ANEG_COMPLETE_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Status indicating whether auto-negotiation has completed.
 *
 * \details 
 * 0 = Autonegotiation not started or not completed
 * 1 = Autonegotiation complete
 *
 * Field: VTSS_PCS_XAUI_ANEG_STATUS_ANEG_STATUS . ANEG_COMPLETE
 */
#define  VTSS_F_PCS_XAUI_ANEG_STATUS_ANEG_STATUS_ANEG_COMPLETE  VTSS_BIT(0)


#endif /* _VTSS_VENICE_REGS_PCS_XAUI_H_ */
