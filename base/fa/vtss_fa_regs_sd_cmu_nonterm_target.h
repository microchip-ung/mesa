// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_SD_CMU_NONTERM_TARGET_H_
#define _VTSS_FA_REGS_SD_CMU_NONTERM_TARGET_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD_CMU_NONTERM_TARGET
 *
 * \see vtss_target_SD_CMU_NONTERM_TARGET_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a SD_CMU_NONTERM_TARGET:SD_CMU_CFG
 *
 * Not documented
 */


/** 
 * \brief SD CMU Configuration 
 *
 * \details
 * Register: \a SD_CMU_NONTERM_TARGET:SD_CMU_CFG:SD_CMU_CFG
 *
 * @param target A \a ::vtss_target_SD_CMU_NONTERM_TARGET_e target
 */
#define VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_CFG(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Software Reset for SD LCPLL macro. 
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_CFG . CMU_RST
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST  VTSS_BIT(0)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_CMU_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Software Reset for SD configuration interface.
 *
 * \details 
 * 1: Reset active
 * 0: Reset incactive
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_CFG . EXT_CFG_RST
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_EXT_CFG_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_EXT_CFG_RST  VTSS_BIT(1)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_CMU_CFG_EXT_CFG_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief SD CMU Status
 *
 * \details
 * SD CMU Status as not available from internal SD registers
 *
 * Register: \a SD_CMU_NONTERM_TARGET:SD_CMU_CFG:SD_CMU_STAT
 *
 * @param target A \a ::vtss_target_SD_CMU_NONTERM_TARGET_e target
 */
#define VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_STAT(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Access to internal serdes state
 *
 * \details 
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_CMU_STAT . DBG_OBS
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_CMU_STAT_DBG_OBS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_CMU_STAT_DBG_OBS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_CMU_STAT_DBG_OBS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a SD_CMU_NONTERM_TARGET:SD_EXTCFG_CFG
 *
 * Configuration of SD local parallel configuration interface (EXT_CFG)
 */


/** 
 * \brief Configuration of SD local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a SD_CMU_NONTERM_TARGET:SD_EXTCFG_CFG:SD_EXTCFG_CFG
 *
 * @param target A \a ::vtss_target_SD_CMU_NONTERM_TARGET_e target
 */
#define VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Clock divider for EXTCFG Master. Divide the system clock by N + 2 to be
 * used as EXTCFG master clock for SerDes configuration.
 *
 * \details 
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG . CLK_DIV
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is asserted after driving address and write data.
 *
 * \details 
 * Total Wait States are N+2 clock cycles of EXT_CFG clock signal. 
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG . WS_SETUP_WR
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * write enable is deasserted again.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG . WS_EXEC_WR
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * start of next write access.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG . WS_HOLD_WR
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.Additional N wait states before
 * read data is sampled.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+3 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG . WS_EXEC_RD
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * Register Group: \a SD_CMU_NONTERM_TARGET:SD_LCPLL_CFG
 *
 * SD LCPLL Configuration Registers
 */


/** 
 * \brief LCPLL Termination Configuration
 *
 * \details
 * Register: \a SD_CMU_NONTERM_TARGET:SD_LCPLL_CFG:LCPLL_CFG
 *
 * @param target A \a ::vtss_target_SD_CMU_NONTERM_TARGET_e target
 */
#define VTSS_SD_CMU_NONTERM_TARGET_LCPLL_CFG(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Enable Reference Clock Termination in this LCPLL.Each LCPLL instance has
 * an optional termination resistor that is enabled by this bitNote:  A
 * number of LCPLLs share the same reference clock. Only the last on the
 * clock line should have this field set to '1', the others must remain '0'
 *
 * \details 
 * 1: RefClk termination enabled
 * 0: RefClk termination disabled

 *
 * Field: ::VTSS_SD_CMU_NONTERM_TARGET_LCPLL_CFG . LCPLL_REFCLK_TERM_ENA
 */
#define  VTSS_F_SD_CMU_NONTERM_TARGET_LCPLL_CFG_LCPLL_REFCLK_TERM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD_CMU_NONTERM_TARGET_LCPLL_CFG_LCPLL_REFCLK_TERM_ENA  VTSS_BIT(0)
#define  VTSS_X_SD_CMU_NONTERM_TARGET_LCPLL_CFG_LCPLL_REFCLK_TERM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_FA_REGS_SD_CMU_NONTERM_TARGET_H_ */
