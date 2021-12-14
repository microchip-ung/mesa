// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_SD_LANE_TARGET_H_
#define _VTSS_LAGUNA_REGS_SD_LANE_TARGET_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD_LANE_TARGET
 *
 * \see vtss_target_SD_LANE_TARGET_e
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a SD_LANE_TARGET:SD_RESET
 *
 * Not documented
 */


/**
 * \brief Software Reset for Serializer Clock
 *
 * \details
 * Register: \a SD_LANE_TARGET:SD_RESET:SD_SER_RST
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_SER_RST(target)  VTSS_IOREG(target,0x0)

/**
 * \brief
 * Software Reset for SD Serializer Clock
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_SER_RST . SER_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_SER_RST_SER_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_SER_RST_SER_RST  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_SER_RST_SER_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Software Reset for Deserializer Clock
 *
 * \details
 * Register: \a SD_LANE_TARGET:SD_RESET:SD_DES_RST
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_DES_RST(target)  VTSS_IOREG(target,0x1)

/**
 * \brief
 * Software Reset for SD Deserializer Clock
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_DES_RST . DES_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_DES_RST_DES_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_DES_RST_DES_RST  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_DES_RST_DES_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD_LANE_TARGET:SD_LANE_CFG_STAT
 *
 * SD Lane configuration and Status
 */


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a SD_LANE_TARGET:SD_LANE_CFG_STAT:SD_LANE_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_LANE_CFG(target)  VTSS_IOREG(target,0x2)

/**
 * \brief
 * Software Reset for SD Lane macro for fundamental reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . MACRO_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_MACRO_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_MACRO_RST  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_MACRO_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Software Reset for SD configuration interface.
 *
 * \details
 * 1: Reset active
 * 0: Reset incactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . EXT_CFG_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_EXT_CFG_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_EXT_CFG_RST  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_EXT_CFG_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Select sideband signals from one of attached CMUs depending on required
 * High Speed Reference clock
 *
 * \details
 * 00:	10.3125GHz  (MAIN)
 * 01:	10.0GHz  (AUXCK1)
 * 10:	12.5GHz  (AUXCK2)
 * 11:	12.5GHz  (AUXCK2)

 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . TX_REF_SEL
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_TX_REF_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_TX_REF_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_TX_REF_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Select reference clock signal from one of attached CMUs depending on
 * required High Speed Reference clock
 *
 * \details
 * 00:	10.3125GHz  (MAIN)
 * 01:	10.0GHz  (AUXCK1)
 * 10:	12.5GHz  (AUXCK2)
 * 11:	12.5GHz  (AUXCK2)

 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . RX_REF_SEL
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_RX_REF_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_RX_REF_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_RX_REF_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/**
 * \brief
 * Software Reset for SD Lane reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . LANE_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_LANE_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RST  VTSS_BIT(8)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_LANE_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Software Reset for SD Lane reset for TX data path.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . LANE_TX_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_LANE_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_TX_RST  VTSS_BIT(9)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_LANE_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Software Reset for SD Lane reset for RX data path.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_CFG . LANE_RX_RST
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST  VTSS_BIT(10)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_CFG_LANE_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,10,1)


/**
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a SD_LANE_TARGET:SD_LANE_CFG_STAT:SD_LANE_STAT
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_LANE_STAT(target)  VTSS_IOREG(target,0x3)

/**
 * \brief
 * PMA Reset done
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_STAT . PMA_RST_DONE
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_STAT_PMA_RST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_STAT_PMA_RST_DONE  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_STAT_PMA_RST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * DFE Reset done
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_STAT . DFE_RST_DONE
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_STAT_DFE_RST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_STAT_DFE_RST_DONE  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_STAT_DFE_RST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Access to internal serdes state
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_SD_LANE_STAT . DBG_OBS
 */
#define  VTSS_F_SD_LANE_TARGET_SD_LANE_STAT_DBG_OBS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD_LANE_TARGET_SD_LANE_STAT_DBG_OBS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD_LANE_TARGET_SD_LANE_STAT_DBG_OBS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a SD_LANE_TARGET:SD_CFG
 *
 * SD Signal Detect Configuration
 */


/**
 * \brief SD Signal Detect Configuration
 *
 * \details
 * Serdes Signal Detect Configuration
 *
 * Register: \a SD_LANE_TARGET:SD_CFG:SD_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_CFG(target)   VTSS_IOREG(target,0x4)

/**
 * \brief
 * Signal Detect Enable
 *
 * \details
 * 0: The Signal Detect input pin is ignored active Signal Detect is
 * assumed at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_CFG . SD_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_CFG_SD_ENA  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_CFG . SD_POL
 */
#define  VTSS_F_SD_LANE_TARGET_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_SD_CFG_SD_POL  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_CFG . SD_SEL
 */
#define  VTSS_F_SD_LANE_TARGET_SD_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD_LANE_TARGET_SD_CFG_SD_SEL  VTSS_BIT(2)
#define  VTSS_X_SD_LANE_TARGET_SD_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * Register Group: \a SD_LANE_TARGET:SD_CLK_GATE
 *
 * Gating all macro generated clocks
 */


/**
 * \brief Gating all macro generated clocks
 *
 * \details
 * Gate SD generated clocks during speed change
 *
 * Register: \a SD_LANE_TARGET:SD_CLK_GATE:SD_CLK_GATE
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_CLK_GATE(target)  VTSS_IOREG(target,0x5)

/**
 * \details
 * 0 :	enable macro clock generation towards core (RX & TX)
 * 1 :	disable (gate) macro clock generation towards core (TX & TX)
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_CLK_GATE . SD_CLK_GATE
 */
#define  VTSS_F_SD_LANE_TARGET_SD_CLK_GATE_SD_CLK_GATE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SD_CLK_GATE_SD_CLK_GATE  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SD_CLK_GATE_SD_CLK_GATE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD_LANE_TARGET:SD_PWR_CFG
 *
 * SD Power configuration
 */


/**
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a SD_LANE_TARGET:SD_PWR_CFG:NORMAL_MODE
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_NORMAL_MODE(target)  VTSS_IOREG(target,0x6)

/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL modeBits 17 to 19 are
 * for TX direction, other bits are for RX direction.
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::VTSS_SD_LANE_TARGET_NORMAL_MODE . NORMAL_MODE
 */
#define  VTSS_F_SD_LANE_TARGET_NORMAL_MODE_NORMAL_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_SD_LANE_TARGET_NORMAL_MODE_NORMAL_MODE     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_SD_LANE_TARGET_NORMAL_MODE_NORMAL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,25)


/**
 * \brief Power settings for QUIET mode.
 *
 * \details
 * Register: \a SD_LANE_TARGET:SD_PWR_CFG:QUIET_MODE_6G
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_QUIET_MODE_6G(target)  VTSS_IOREG(target,0x7)

/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode.Bits 17 to 19 are
 * for TX direction, other bits are for RX direction.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::VTSS_SD_LANE_TARGET_QUIET_MODE_6G . QUIET_MODE
 */
#define  VTSS_F_SD_LANE_TARGET_QUIET_MODE_6G_QUIET_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_SD_LANE_TARGET_QUIET_MODE_6G_QUIET_MODE     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_SD_LANE_TARGET_QUIET_MODE_6G_QUIET_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,25)

/**
 * Register Group: \a SD_LANE_TARGET:SD_ANEG_CFG
 *
 * SD_ANEG_CFG
 */


/**
 * \brief SD_KR_ANEG_MODE
 *
 * \details
 * Configure ANEG to SerDes (TX) behavior
 *
 * Register: \a SD_LANE_TARGET:SD_ANEG_CFG:SD_KR_ANEG_MODE
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_KR_ANEG_MODE(target)  VTSS_IOREG(target,0x8)

/**
 * \brief
 * Configure how ANEG TX data is multiplexed into Serial Data stream
 *
 * \details
 * 00: auto (TX connection to Serializer controlled by KR block)
 * 01: reserved
 * 10: force off (i.e. ANEG TX data never connected to Serializer)
 * 11: force on (i.e. ANEG TX data always connected to Serializer)
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_KR_ANEG_MODE . TX_ANEG_MODE
 */
#define  VTSS_F_SD_LANE_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD_LANE_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD_LANE_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SD_LANE_TARGET:SD_EXTCFG_CFG
 *
 * Configuration of SD local parallel configuration interface (EXT_CFG)
 */


/**
 * \brief Configuration of SD local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a SD_LANE_TARGET:SD_EXTCFG_CFG:SD_EXTCFG_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG(target)  VTSS_IOREG(target,0x9)

/**
 * \brief
 * Clock divider for EXTCFG Master. Divide the system clock by N + 2 to be
 * used as EXTCFG master clock for SerDes configuration.
 *
 * \details
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG . CLK_DIV
 */
#define  VTSS_F_SD_LANE_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD_LANE_TARGET_SD_EXTCFG_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD_LANE_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is asserted after driving address and write data.
 *
 * \details
 * Total Wait States are N+2 clock cycles of EXT_CFG clock signal.
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG . WS_SETUP_WR
 */
#define  VTSS_F_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is deasserted again.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG . WS_EXEC_WR
 */
#define  VTSS_F_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * start of next write access.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG . WS_HOLD_WR
 */
#define  VTSS_F_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * read data is sampled.
 *
 * \details
 * Total Wait States (i.e. pulse width) are N+3 clock cycles of EXT_CFG
 * clock signal.
 *
 * Field: ::VTSS_SD_LANE_TARGET_SD_EXTCFG_CFG . WS_EXEC_RD
 */
#define  VTSS_F_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD_LANE_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * Register Group: \a SD_LANE_TARGET:SD_FIFO_DELAY
 *
 * Registers for precise FIFO delay measurement
 */


/**
 * \brief FIFO delay measurement configuration
 *
 * \details
 * FIFO delay measurement configuration register
 *
 * Register: \a SD_LANE_TARGET:SD_FIFO_DELAY:SD_DELAY_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_DELAY_CFG(target)  VTSS_IOREG(target,0xa)

/**
 * \brief
 * Configures the number of cycles the skew detector should run before
 * returning serdes delay
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_SD_DELAY_CFG . SAMPLE_TIME
 */
#define  VTSS_F_SD_LANE_TARGET_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD_LANE_TARGET_SD_DELAY_CFG_SAMPLE_TIME     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD_LANE_TARGET_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a SD_LANE_TARGET:SD_FIFO_DELAY:SD_DELAY_VAR
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SD_DELAY_VAR(target)  VTSS_IOREG(target,0xb)

/**
 * \brief
 * Rx delay reported as 2**16 times the Serdes fifo size in time, which
 * must be well known to determine the delay. Example: A 80 bit fifo with a
 * bit clock of 800 picosec, and a skew of 16384 means a serdes delay of 80
 * x (800 picosec) x (16384/65536) = 1.6 nanosec.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_SD_DELAY_VAR . RX_DELAY_VAR
 */
#define  VTSS_F_SD_LANE_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD_LANE_TARGET_SD_DELAY_VAR_RX_DELAY_VAR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD_LANE_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Tx delay reported as 2**16 times the Serdes fifo size in time, which
 * must be well known to determine the delay. Example: A 80 bit fifo with a
 * bit clock of 800 picosec, and a skew of 16384 means a serdes delay of 80
 * x (800 picosec) x (16384/65536) = 1.6 nanosec.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_SD_DELAY_VAR . TX_DELAY_VAR
 */
#define  VTSS_F_SD_LANE_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD_LANE_TARGET_SD_DELAY_VAR_TX_DELAY_VAR     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD_LANE_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a SD_LANE_TARGET:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/**
 * \brief 10G Recovered Clock Configuration
 *
 * \details
 * Register: \a SD_LANE_TARGET:SYNC_ETH_CFG:SYNC_ETH_SD_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG(target)  VTSS_IOREG(target,0xc)

/**
 * \brief
 * Set to enable auto-squelching for sync. ethernet clock output: when set
 * the clock output will stop toggling (keep its last value constantly)
 * when when SerDes looses signal detect state.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG . SD_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Use Link Status information of connected PCS or extender for squelching
 * of recovered clock.
 *
 * \details
 * 1: Use link status information for squelching
 * 0: Don't use link status information for squelching

 *
 * Field: ::VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG . SD_LINK_STAT_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Divider setting for the SD recovered clock output. These settings are
 * applied prior to sending recovered clock to the optional PAD-divider
 * (see HSIOWRAP::SYNC_ETH_CFG[X].SEL_RECO_CLK_DIV.)For the TX clock
 * recovery value 2 is also reserved, it is not possible to divide by 66/32
 * for TX clock.
 *
 * \details
 * 0: No clock dividing
 * 1: Divide clock by 2
 * 2: Divide clock by (66/32)
 * 3: reserved
 *
 * Field: ::VTSS_SD_LANE_TARGET_SYNC_ETH_SD_CFG . SD_RECO_CLK_DIV
 */
#define  VTSS_F_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD_LANE_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SD_LANE_TARGET:HW_CFG
 *
 * Hardware Configuration
 */


/**
 * \brief KR ANEG Configuration
 *
 * \details
 * Common KR ANEG configuration, used across all instances.
 *
 * Register: \a SD_LANE_TARGET:HW_CFG:KR_DATA_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_KR_DATA_CFG(target)  VTSS_IOREG(target,0xd)

/**
 * \brief
 * Revert 10B data bus portion.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD_LANE_TARGET_KR_DATA_CFG . REVERT_10B
 */
#define  VTSS_F_SD_LANE_TARGET_KR_DATA_CFG_REVERT_10B(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_KR_DATA_CFG_REVERT_10B  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_KR_DATA_CFG_REVERT_10B(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD_LANE_TARGET_KR_DATA_CFG . REVERT_64B_TX
 */
#define  VTSS_F_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_TX  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD_LANE_TARGET_KR_DATA_CFG . REVERT_64B_RX
 */
#define  VTSS_F_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_RX  VTSS_BIT(2)
#define  VTSS_X_SD_LANE_TARGET_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * Register Group: \a SD_LANE_TARGET:CFG_STAT_FX100
 *
 * Configuration and statistics parameters for 100Base-FX
 */


/**
 * \brief Miscellaneous parameters
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:MISC
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_MISC(target)     VTSS_IOREG(target,0xe)

/**
 * \brief
 * Disable reset for part of 100FX block, which is clocked by 125MHz clock
 * from SD10G.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_MISC . SD_125_RST_DIS
 */
#define  VTSS_F_SD_LANE_TARGET_MISC_SD_125_RST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_MISC_SD_125_RST_DIS  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_MISC_SD_125_RST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable extraction of 100FX clock and data, and clear outgoing reset.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_MISC . RX_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_MISC_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_MISC_RX_ENA    VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_MISC_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable signaling of 100Base-FX clock, reset, data and lock to device.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_MISC . MUX_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_MISC_MUX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD_LANE_TARGET_MISC_MUX_ENA   VTSS_BIT(2)
#define  VTSS_X_SD_LANE_TARGET_MISC_MUX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Core clock frequency.
 *
 * \details
 * 0: 625MHz
 * 1: 500MHz
 * 2: 250MHz
 * 3: 280MHz
 *
 * Field: ::VTSS_SD_LANE_TARGET_MISC . CORE_CLK_FREQ
 */
#define  VTSS_F_SD_LANE_TARGET_MISC_CORE_CLK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD_LANE_TARGET_MISC_CORE_CLK_FREQ     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD_LANE_TARGET_MISC_CORE_CLK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief Sticky bits
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:STICKY_BITS
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_STICKY_BITS(target)  VTSS_IOREG(target,0xf)

/**
 * \brief
 * Overflow in FIFO of received bits encountered.This could be caused by
 * the SerDes not being configured for 1.25Gbps mode.Related
 * parameters:SD10G_LANE:LANE_GRP_0:LANE_35.CFG_RXRATE_1_0SD10G_LANE:LANE_G
 * RP_0:LANE_35.CFG_TXRATE_1_0
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_STICKY_BITS . FIFO_OFLW_STICKY
 */
#define  VTSS_F_SD_LANE_TARGET_STICKY_BITS_FIFO_OFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_STICKY_BITS_FIFO_OFLW_STICKY  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_STICKY_BITS_FIFO_OFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Underflow in FIFO of received bits encountered.This may occur during
 * initial enabling of fx100, but following that it should never happen.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_STICKY_BITS . FIFO_UFLW_STICKY
 */
#define  VTSS_F_SD_LANE_TARGET_STICKY_BITS_FIFO_UFLW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_STICKY_BITS_FIFO_UFLW_STICKY  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_STICKY_BITS_FIFO_UFLW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Parameters related to locating rising edge in bit stream from SD10G
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:EDGE_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_EDGE_CFG(target)  VTSS_IOREG(target,0x10)

/**
 * \brief
 * Threshold for when to adjust rising edge pointer.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_EDGE_CFG . PTR_DIR_SUM_ABS_THRES
 */
#define  VTSS_F_SD_LANE_TARGET_EDGE_CFG_PTR_DIR_SUM_ABS_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD_LANE_TARGET_EDGE_CFG_PTR_DIR_SUM_ABS_THRES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD_LANE_TARGET_EDGE_CFG_PTR_DIR_SUM_ABS_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Distance from rising edge to (assumed) value bit.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_EDGE_CFG . DIST_EDGE_TO_VAL
 */
#define  VTSS_F_SD_LANE_TARGET_EDGE_CFG_DIST_EDGE_TO_VAL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD_LANE_TARGET_EDGE_CFG_DIST_EDGE_TO_VAL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD_LANE_TARGET_EDGE_CFG_DIST_EDGE_TO_VAL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)


/**
 * \brief Parameters related to lock period.
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:LOCK_PERIOD
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_LOCK_PERIOD(target)  VTSS_IOREG(target,0x11)

/**
 * \brief
 * Length in FX cycles of the period over which lock criterion is
 * evaluated.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_LOCK_PERIOD . LOCK_PERIOD_LEN
 */
#define  VTSS_F_SD_LANE_TARGET_LOCK_PERIOD_LOCK_PERIOD_LEN(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD_LANE_TARGET_LOCK_PERIOD_LOCK_PERIOD_LEN     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD_LANE_TARGET_LOCK_PERIOD_LOCK_PERIOD_LEN(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief
 * Current lock state.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_LOCK_PERIOD . IN_LOCK
 */
#define  VTSS_F_SD_LANE_TARGET_LOCK_PERIOD_IN_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD_LANE_TARGET_LOCK_PERIOD_IN_LOCK  VTSS_BIT(31)
#define  VTSS_X_SD_LANE_TARGET_LOCK_PERIOD_IN_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,31,1)


/**
 * \brief Criterion for declaring locked state.
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES(target)  VTSS_IOREG(target,0x12)

/**
 * \brief
 * Maximum absolute sum of edge pointer changes allowed during
 * LOCK_PERIOD_LEN FX cycles.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES . LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES
 */
#define  VTSS_F_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES_LOCK_PERIOD_PTR_ADJ_SUM_ABS_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Criterion for declaring locked state.
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:LOCK_PERIOD_PTR_ADJ_CNT_THRES
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_CNT_THRES(target)  VTSS_IOREG(target,0x13)

/**
 * \brief
 * Maximum number of edge pointer changes allowed during LOCK_PERIOD_LEN FX
 * cycles.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_CNT_THRES . LOCK_PERIOD_PTR_ADJ_CNT_THRES
 */
#define  VTSS_F_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_CNT_THRES_LOCK_PERIOD_PTR_ADJ_CNT_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,15)
#define  VTSS_M_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_CNT_THRES_LOCK_PERIOD_PTR_ADJ_CNT_THRES     VTSS_ENCODE_BITMASK(0,15)
#define  VTSS_X_SD_LANE_TARGET_LOCK_PERIOD_PTR_ADJ_CNT_THRES_LOCK_PERIOD_PTR_ADJ_CNT_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,15)


/**
 * \brief Filter configuration
 *
 * \details
 * A pattern mask is found if any a sequence of SD bits matching the
 * following expression is found.
 *
 * FILTER_ENA=1:
 * (sd_bit_seq & FILTER_MASK) == (FILTER_PATTERN & FILTER_MASK)
 *
 * FILTER_INV_ENA=1:
 * (sd_bit_seq & FILTER_MASK) == (~FILTER_PATTERN & FILTER_MASK)
 *
 * If a match is found, then the following modification is performed
 * sd_bit_seq[FILTER_BIT_IDX_INV] = !sd_bit_seq[FILTER_BIT_IDX_INV]

 *
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:FILTER_CFG
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 * @param ri Replicator: x_GUC_SD10G_FX100_FILTER_CNT (??), 0-1
 */
#define VTSS_SD_LANE_TARGET_FILTER_CFG(target,ri)  VTSS_IOREG(target,0x14 + (ri))

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_FILTER_CFG . FILTER_PATTERN
 */
#define  VTSS_F_SD_LANE_TARGET_FILTER_CFG_FILTER_PATTERN(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_SD_LANE_TARGET_FILTER_CFG_FILTER_PATTERN     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_SD_LANE_TARGET_FILTER_CFG_FILTER_PATTERN(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_FILTER_CFG . FILTER_MASK
 */
#define  VTSS_F_SD_LANE_TARGET_FILTER_CFG_FILTER_MASK(x)  VTSS_ENCODE_BITFIELD(x,12,9)
#define  VTSS_M_SD_LANE_TARGET_FILTER_CFG_FILTER_MASK     VTSS_ENCODE_BITMASK(12,9)
#define  VTSS_X_SD_LANE_TARGET_FILTER_CFG_FILTER_MASK(x)  VTSS_EXTRACT_BITFIELD(x,12,9)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_FILTER_CFG . FILTER_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_FILTER_CFG_FILTER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD_LANE_TARGET_FILTER_CFG_FILTER_ENA  VTSS_BIT(24)
#define  VTSS_X_SD_LANE_TARGET_FILTER_CFG_FILTER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_FILTER_CFG . FILTER_INV_ENA
 */
#define  VTSS_F_SD_LANE_TARGET_FILTER_CFG_FILTER_INV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD_LANE_TARGET_FILTER_CFG_FILTER_INV_ENA  VTSS_BIT(25)
#define  VTSS_X_SD_LANE_TARGET_FILTER_CFG_FILTER_INV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_FILTER_CFG . FILTER_BIT_IDX_INV
 */
#define  VTSS_F_SD_LANE_TARGET_FILTER_CFG_FILTER_BIT_IDX_INV(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SD_LANE_TARGET_FILTER_CFG_FILTER_BIT_IDX_INV     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SD_LANE_TARGET_FILTER_CFG_FILTER_BIT_IDX_INV(x)  VTSS_EXTRACT_BITFIELD(x,28,4)


/**
 * \brief Measurement control
 *
 * \details
 * To help configure filters, measurement can be used to determine
 * characteristics of the received bit stream.
 *
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:M_CTRL
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_M_CTRL(target)   VTSS_IOREG(target,0x16)

/**
 * \brief
 * To start a new measurement, M_START must be set to 0 and then
 * immediately after to 1.When measurement has completed, HW will set
 * M_DONE (unless M_PERIOD_LEN=0).If M_PERIOD_LEN=0, then the measurement
 * will run until M_START is set to 0.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_CTRL . M_START
 */
#define  VTSS_F_SD_LANE_TARGET_M_CTRL_M_START(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_LANE_TARGET_M_CTRL_M_START  VTSS_BIT(0)
#define  VTSS_X_SD_LANE_TARGET_M_CTRL_M_START(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Measurement has completed.HW clears this bit shortly after M_START is
 * set and sets it again when measurement has completed.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_CTRL . M_DONE
 */
#define  VTSS_F_SD_LANE_TARGET_M_CTRL_M_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_LANE_TARGET_M_CTRL_M_DONE  VTSS_BIT(1)
#define  VTSS_X_SD_LANE_TARGET_M_CTRL_M_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Latch the following
 * information:M_STAT_MISC.M_RIS_EDGE_PTR_ADJ_SUMM_STAT_MISC.M_LOCK_CNTM_ST
 * AT_FX_ONE_CNT.M_FX_ONE_CNTM_STAT_SD_ONE_CNT.M_SD_ONE_CNTM_STAT_FILTER_MA
 * TCH_CNT.M_FILTER_MATCH_CNTTo latch the information M_LATCH must be set
 * to 0 and then immediately after to 1.The latched information is
 * available a few clock cycles after setting M_LATCH=1.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_CTRL . M_LATCH
 */
#define  VTSS_F_SD_LANE_TARGET_M_CTRL_M_LATCH(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD_LANE_TARGET_M_CTRL_M_LATCH  VTSS_BIT(2)
#define  VTSS_X_SD_LANE_TARGET_M_CTRL_M_LATCH(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Control how M_PERIOD_LEN is measured.
 *
 * \details
 * 0: M_PERIOD_LEN is measured in FX bits received.
 * 1: M_PERIOD_LEN is measured in FX edges (0->1, 1->0)
 *
 * Field: ::VTSS_SD_LANE_TARGET_M_CTRL . M_PERIOD_LEN_TYPE
 */
#define  VTSS_F_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN_TYPE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN_TYPE  VTSS_BIT(3)
#define  VTSS_X_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Length of measurement period.Unit is controlled by M_PERIOD_LEN_TYPE.0
 * => Run until SW sets M_START=0.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_CTRL . M_PERIOD_LEN
 */
#define  VTSS_F_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN(x)  VTSS_ENCODE_BITFIELD(x,8,20)
#define  VTSS_M_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN     VTSS_ENCODE_BITMASK(8,20)
#define  VTSS_X_SD_LANE_TARGET_M_CTRL_M_PERIOD_LEN(x)  VTSS_EXTRACT_BITFIELD(x,8,20)


/**
 * \brief M_PERIOD_LEN miscellaneous statistics.
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:M_STAT_MISC
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_M_STAT_MISC(target)  VTSS_IOREG(target,0x17)

/**
 * \brief
 * The sum of all rising edge pointer adjustments during measurement
 * period.Two's complement encoded.The field is set to 0 when measurement
 * is started.If sender is faster than receiver, then the number will
 * become postive.If sender is slower than receiver, then the number will
 * become negative.Saturates at maximum/minimum value.Before reading this
 * field, M_LATCH must be set to latch current value.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_STAT_MISC . M_RIS_EDGE_PTR_ADJ_SUM
 */
#define  VTSS_F_SD_LANE_TARGET_M_STAT_MISC_M_RIS_EDGE_PTR_ADJ_SUM(x)  VTSS_ENCODE_BITFIELD(x,0,22)
#define  VTSS_M_SD_LANE_TARGET_M_STAT_MISC_M_RIS_EDGE_PTR_ADJ_SUM     VTSS_ENCODE_BITMASK(0,22)
#define  VTSS_X_SD_LANE_TARGET_M_STAT_MISC_M_RIS_EDGE_PTR_ADJ_SUM(x)  VTSS_EXTRACT_BITFIELD(x,0,22)

/**
 * \brief
 * Number of times lock state has been entered during measurement
 * period.The field is set to 0 when measurement is started.Saturates at
 * maximum value.Before reading this field, M_LATCH must be set to latch
 * current value.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_STAT_MISC . M_LOCK_CNT
 */
#define  VTSS_F_SD_LANE_TARGET_M_STAT_MISC_M_LOCK_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_SD_LANE_TARGET_M_STAT_MISC_M_LOCK_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_SD_LANE_TARGET_M_STAT_MISC_M_LOCK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)


/**
 * \brief M_PERIOD_LEN statistics for "1 counting".
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:M_STAT_SD_ONE_CNT
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_M_STAT_SD_ONE_CNT(target)  VTSS_IOREG(target,0x18)

/**
 * \brief
 * Number of SD 1s seen, minus M_FX_ONE_CNT*10 seen during measurement
 * period.Two's complement encoded.Saturates at maximum/minimum value.The
 * field is set to 0 when measurement is started.May be used to detect duty
 * cycle distortion in received bit stream.Before reading this field,
 * M_LATCH must be set to latch current value.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_STAT_SD_ONE_CNT . M_SD_ONE_CNT
 */
#define  VTSS_F_SD_LANE_TARGET_M_STAT_SD_ONE_CNT_M_SD_ONE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD_LANE_TARGET_M_STAT_SD_ONE_CNT_M_SD_ONE_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD_LANE_TARGET_M_STAT_SD_ONE_CNT_M_SD_ONE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief M_PERIOD_LEN statistics for "1 counting".
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:M_STAT_FX_ONE_CNT
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 */
#define VTSS_SD_LANE_TARGET_M_STAT_FX_ONE_CNT(target)  VTSS_IOREG(target,0x19)

/**
 * \brief
 * Number of FX 1s seen during measurement period.Saturates at maximum
 * value.The field is set to 0 when measurement is started.Before reading
 * this field, M_LATCH must be set to latch current value.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_STAT_FX_ONE_CNT . M_FX_ONE_CNT
 */
#define  VTSS_F_SD_LANE_TARGET_M_STAT_FX_ONE_CNT_M_FX_ONE_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_SD_LANE_TARGET_M_STAT_FX_ONE_CNT_M_FX_ONE_CNT     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_SD_LANE_TARGET_M_STAT_FX_ONE_CNT_M_FX_ONE_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/**
 * \brief M_PERIOD_LEN statistics for number of filter matches.
 *
 * \details
 * Register: \a SD_LANE_TARGET:CFG_STAT_FX100:M_STAT_FILTER_MATCH_CNT
 *
 * @param target A \a ::vtss_target_SD_LANE_TARGET_e target
 * @param ri Replicator: x_GUC_SD10G_FX100_FILTER_CNT (??), 0-1
 */
#define VTSS_SD_LANE_TARGET_M_STAT_FILTER_MATCH_CNT(target,ri)  VTSS_IOREG(target,0x1a + (ri))

/**
 * \brief
 * Number of times filter has matched (due to either FILTER_ENA or
 * FILTER_INV_ENA) during measurement period.Saturates at maximum value.The
 * field is set to 0 when measurement is started.Before reading this field,
 * M_LATCH must be set to latch current value.
 *
 * \details
 * Field: ::VTSS_SD_LANE_TARGET_M_STAT_FILTER_MATCH_CNT . M_FILTER_MATCH_CNT
 */
#define  VTSS_F_SD_LANE_TARGET_M_STAT_FILTER_MATCH_CNT_M_FILTER_MATCH_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD_LANE_TARGET_M_STAT_FILTER_MATCH_CNT_M_FILTER_MATCH_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD_LANE_TARGET_M_STAT_FILTER_MATCH_CNT_M_FILTER_MATCH_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LAGUNA_REGS_SD_LANE_TARGET_H_ */
