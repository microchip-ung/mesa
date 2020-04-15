/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_CLKGEN_H_
#define _VTSS_FA_REGS_CLKGEN_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a CLKGEN
 *
 * Clock Generation Configuration and Status Registers
 *
 ***********************************************************************/

/**
 * Register Group: \a CLKGEN:AOUT
 *
 * Analog Test Ouput Configuration
 */


/** 
 * \brief AOUT Configuration
 *
 * \details
 * AOUT Configuration
 *
 * Register: \a CLKGEN:AOUT:AOUT_CFG
 */
#define VTSS_CLKGEN_AOUT_CFG                 VTSS_IOREG(VTSS_TO_CLKGEN,0x0)

/** 
 * \brief
 * Enable Analog Output 
 *
 * \details 
 * Field: ::VTSS_CLKGEN_AOUT_CFG . AOUT_ENA
 */
#define  VTSS_F_CLKGEN_AOUT_CFG_AOUT_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CLKGEN_AOUT_CFG_AOUT_ENA      VTSS_BIT(0)
#define  VTSS_X_CLKGEN_AOUT_CFG_AOUT_ENA(x)   VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CLKGEN:HSIO_CLKTREE
 *
 * HSIO Clock Tree Configuration and Status (LCPLL1)
 */


/** 
 * \brief HSIO_CLKTREE_CFG
 *
 * \details
 * Configuration Register of HSIO CLKTREE block (next to LCPLL1)
 *
 * Register: \a CLKGEN:HSIO_CLKTREE:HSIO_CLKTREE_CFG
 */
#define VTSS_CLKGEN_HSIO_CLKTREE_CFG         VTSS_IOREG(VTSS_TO_CLKGEN,0x1)

/** 
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_SPARE_CFG
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_SPARE_CFG(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_SPARE_CFG     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_SPARE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Tuning for clocktree BIAS
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_VREF_ADJ
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_VREF_ADJ(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_VREF_ADJ     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_VREF_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Base tuning for clocktree BIAS
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_COMMON_VREF_ADJ
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_COMMON_VREF_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_COMMON_VREF_ADJ     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_COMMON_VREF_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Enable high drive for clocktree BIAS
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_BIAS_H_DRIVE
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_BIAS_H_DRIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_BIAS_H_DRIVE  VTSS_BIT(13)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_BIAS_H_DRIVE(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Enable BIAS for clocktree buffers
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_ENA_BIAS
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BIAS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BIAS  VTSS_BIT(12)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BIAS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Tuning for bandgap voltage
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_BG_RADJ
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_BG_RADJ(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_BG_RADJ     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_BG_RADJ(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * Enable global 1.2V bandgap
 *
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_CFG . CTB_ENA_BANDGAP
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BANDGAP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BANDGAP  VTSS_BIT(0)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_CFG_CTB_ENA_BANDGAP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief HSIO_CLKTREE_STATUS
 *
 * \details
 * Status Register of HSIO CLKTREE block (next to LCPLL1)
 *
 * Register: \a CLKGEN:HSIO_CLKTREE:HSIO_CLKTREE_STATUS
 */
#define VTSS_CLKGEN_HSIO_CLKTREE_STATUS      VTSS_IOREG(VTSS_TO_CLKGEN,0x2)

/** 
 * \details 
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_STATUS . CTB_SPARE_STS
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_STATUS_CTB_SPARE_STS(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_STATUS_CTB_SPARE_STS     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_STATUS_CTB_SPARE_STS(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * bandgap voltage valid
 *
 * \details 
 * 1: bandgap OK
 *
 * Field: ::VTSS_CLKGEN_HSIO_CLKTREE_STATUS . CTB_BANDGAP_OK
 */
#define  VTSS_F_CLKGEN_HSIO_CLKTREE_STATUS_CTB_BANDGAP_OK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CLKGEN_HSIO_CLKTREE_STATUS_CTB_BANDGAP_OK  VTSS_BIT(0)
#define  VTSS_X_CLKGEN_HSIO_CLKTREE_STATUS_CTB_BANDGAP_OK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a CLKGEN:LCPLL1
 *
 * Configuration for LCPLL #1
 */


/** 
 * \brief CORE Clock Configuration
 *
 * \details
 * LCPLL1 Core Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_CORE_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x3)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * 0: no additional division for fractional divider
 * 1: additional division by 2 for fractional divider
 * 2: additional division by 3 for fractional divider
 * 3: additional division by 4 for fractional divider
 * others: reserved

 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Phase rotation direction
 *
 * \details 
 * 0: rotate down to lower frequencies (bigger fractional division factor),
 * e.g. 4/5
 * 1: rotate up to higher frequencies (smaller fractional division factor),
 * e.g. 4/3

 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Fractional division by phase rotator, value depends also on CORE_ROT_DIR
 *
 * \details 
 * 0: rotator switched off (save power)
 * 1: fractional division 4/3 or 4/5
 * 2: fractional division 8/7 or 8/9
 * 3: fractional division 16/15 or 16/17

 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Switches between integer and fractional division (optional)
 *
 * \details 
 * 0: integer division
 * 1: fractional division (optional)

 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CORE_CLK_CFG . CORE_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_CORE_CLK_CFG_CORE_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief DDR Clock Configuration
 *
 * \details
 * LCPLL1 DDR Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_DDR_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG       VTSS_IOREG(VTSS_TO_CLKGEN,0x4)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_DDR_CLK_CFG . DDR_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_DDR_CLK_CFG_DDR_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief CPU2 Clock Configuration
 *
 * \details
 * LCPLL1 CPU2 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_CPU2_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x5)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * 25:	100MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_CPU2_CLK_CFG . CPU2_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_CPU2_CLK_CFG_CPU2_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief AUX3 Clock Configuration
 *
 * \details
 * LCPLL1 AUX3 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_ARM2_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x6)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_ARM2_CLK_CFG . ARM2_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_ARM2_CLK_CFG_ARM2_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief AUX1 Clock Configuration
 *
 * \details
 * LCPLL1 AUX1 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_AUX1_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x7)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX1_CLK_CFG . AUX1_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_AUX1_CLK_CFG_AUX1_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief AUX2 Clock Configuration
 *
 * \details
 * LCPLL1 AUX3 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_AUX2_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x8)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX2_CLK_CFG . AUX2_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_AUX2_CLK_CFG_AUX2_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief AUX3 Clock Configuration
 *
 * \details
 * LCPLL1 AUX3 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_AUX3_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0x9)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX3_CLK_CFG . AUX3_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_AUX3_CLK_CFG_AUX3_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief AUX3 Clock Configuration
 *
 * \details
 * LCPLL1 AUX3 Clock Configuration
 *
 * Register: \a CLKGEN:LCPLL1:LCPLL1_AUX4_CLK_CFG
 */
#define VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG      VTSS_IOREG(VTSS_TO_CLKGEN,0xa)

/** 
 * \brief
 * Clock Divider Configuration
 *
 * \details 
 * 4:  625MHz
 * 5:  500MHz
 * 6:  416.667MHz
 * 8:  312.5MHz
 * 10:	250MHz
 * 12:	208.33MHz
 * 16:	156.25MHz
 * 16:	156.25MHz
 * 20:	125MHz
 * Other:  Reserved
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_CLK_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_DIV     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * Pre divider configuration
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_PRE_DIV
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_PRE_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_PRE_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_PRE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Rotation Direction
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_ROT_DIR
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_DIR  VTSS_BIT(11)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Rotation Selection
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_ROT_SEL
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable Rotation
 *
 * \details 
 * To  Be Added by Koehne
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_ROT_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_ENA  VTSS_BIT(14)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_ROT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Clock enable
 *
 * \details 
 * 0 : disable 
 * 1 : enable
 *
 * Field: ::VTSS_CLKGEN_LCPLL1_AUX4_CLK_CFG . AUX4_CLK_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_CLKGEN_LCPLL1_AUX4_CLK_CFG_AUX4_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)


/** 
 * \brief PLL Recovered Clock Configuration
 *
 * \details
 * Register: \a CLKGEN:LCPLL1:LCPLL1_SYNCE_CFG
 */
#define VTSS_CLKGEN_LCPLL1_SYNCE_CFG         VTSS_IOREG(VTSS_TO_CLKGEN,0xb)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet clock output: when set the
 * clock output will stop toggling (keep its last value constantly) when
 * PLL is out of lock.
 *
 * \details 
 * Field: ::VTSS_CLKGEN_LCPLL1_SYNCE_CFG . PLL_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_CLKGEN_LCPLL1_SYNCE_CFG_PLL_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CLKGEN_LCPLL1_SYNCE_CFG_PLL_AUTO_SQUELCH_ENA  VTSS_BIT(0)
#define  VTSS_X_CLKGEN_LCPLL1_SYNCE_CFG_PLL_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_FA_REGS_CLKGEN_H_ */
