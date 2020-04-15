#ifndef _VTSS_JAGUAR2C_REGS_HSIO_H_
#define _VTSS_JAGUAR2C_REGS_HSIO_H_

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
 * Target: \a HSIO
 *
 * Register Collection for Control of Macros (SERDES1G, SERDES6G, LCPLL)
 *
 ***********************************************************************/

/**
 * Register Group: \a HSIO:PLL5G_CFG
 *
 * PLL5G Configuration Registers
 */


/** 
 * \brief PLL5G Configuration 0
 *
 * \details
 * Configuration register 0 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG0
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,0)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_ROT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_ROT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_ROT  VTSS_BIT(31)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_ROT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * RCPLL Global enable for serdes lane.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_LANE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LANE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LANE  VTSS_BIT(30)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LANE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * RCPLL enable BIAS for clocktree buffer (active low) 0: enable BIAS, 1:
 * disable BIAS
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_CLKTREE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CLKTREE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CLKTREE  VTSS_BIT(29)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CLKTREE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . DIV4
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_DIV4(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_DIV4  VTSS_BIT(28)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_DIV4(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * enable fine locking, last stage in startup locking sequence
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_LOCK_FINE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LOCK_FINE(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LOCK_FINE  VTSS_BIT(27)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_LOCK_FINE(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * fine tune of bandgap voltage distribution 0: lowest voltage, 15: highest
 * voltage
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . SELBGV820
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_SELBGV820(x)  VTSS_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_SELBGV820     VTSS_ENCODE_BITMASK(23,4)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_SELBGV820(x)  VTSS_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * setting for filter resistor value 0: biggest resistance, 31: lowest
 * resistance
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . LOOP_BW_RES
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_LOOP_BW_RES(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_LOOP_BW_RES     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_LOOP_BW_RES(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * setting for chargepump current 0: lowest current, 3: highest current
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . SELCPI
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_SELCPI(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_SELCPI     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_SELCPI(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * enable fine VCO operating point regulator
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_VCO_CONTRH
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_CONTRH(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_CONTRH  VTSS_BIT(15)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_CONTRH(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * enable current mode chargepump, normal mode
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_CP1
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CP1(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CP1  VTSS_BIT(14)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_CP1(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * enable BIAS for LCPLL VCO output buffer
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_VCO_BUF
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_BUF(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_BUF  VTSS_BIT(13)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_VCO_BUF(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * enable BIAS circuitry incl. Bandgap, voltage regulators, etc.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . ENA_BIAS
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_BIAS(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_BIAS  VTSS_BIT(12)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_ENA_BIAS(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Setting for CPU clock divider
 *
 * \details 
 * 2: 500 MHz
 * 5: 250 MHz
 * 6: 416.66 MHz
 * 14: 312.5 MHz
 * 15: 166.66 MHz
 * Others: Reserved
 *
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . CPU_CLK_DIV
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_CPU_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_CPU_CLK_DIV     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_CPU_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * setting for core clock divider 0:625MHz, 1:312.5MHz, 2:500MHz,
 * 3:277.77MHz, 4:500MHz, 5:250MHz, 6:416.66MHz, 7:227.27MHz, 8:416.66MHz,
 * 9:208.33MHz, 10:357.14MHz, 11:192.3MHz, 12:357.14MHz, 13:178.57MHz,
 * 14:312.5MHz, 15:166.66,MHz, 17:156.25MHz, 33:625MHz
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0 . CORE_CLK_DIV
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief PLL5G Configuration 1
 *
 * \details
 * Configuration register 1 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG1
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,1)

/** 
 * \brief
 * enable for direct data mode (ATPG/JTAG) reference clock input buffer and
 * test output buffer
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . ENA_DIRECT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_ENA_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_ENA_DIRECT  VTSS_BIT(18)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_ENA_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . ROT_SPEED
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_SPEED(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_SPEED  VTSS_BIT(17)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . ROT_DIR
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_DIR  VTSS_BIT(16)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * RCPLL Selects whether (when set to '1') the frequency range setting from
 * the FSM can be read back at sx_pll_rb_data_o or (when cleared to '0')
 * the measured period.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . READBACK_DATA_SEL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_READBACK_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_READBACK_DATA_SEL  VTSS_BIT(15)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_READBACK_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * RCPLL Enable for startup FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . RC_ENABLE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_ENABLE  VTSS_BIT(14)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * RCPLL Control input for startup FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . RC_CTRL_DATA
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_CTRL_DATA     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_RC_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

/** 
 * \brief
 * RCPLL Enable for quarter rate mode
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . QUARTER_RATE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_QUARTER_RATE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_QUARTER_RATE  VTSS_BIT(5)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_QUARTER_RATE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * RCPLL Power down for the TX-path
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . PWD_TX
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_TX  VTSS_BIT(4)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_TX(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * RCPLL Power down for the RX-path
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . PWD_RX
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_RX  VTSS_BIT(3)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_PWD_RX(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * RCPLL Enable recalibration of PLL when out of range is detected
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . OUT_OF_RANGE_RECAL_ENA
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_OUT_OF_RANGE_RECAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_OUT_OF_RANGE_RECAL_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_OUT_OF_RANGE_RECAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * RCPLL Enable for half rate mode
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . HALF_RATE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_HALF_RATE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_HALF_RATE  VTSS_BIT(1)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_HALF_RATE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * RCPLL When set to '1' the value at sx_pll_fsm_ctrl_data_I is not taken
 * as reference value for the FSM, but is directly apllied to the PLL as
 * frequency range setting.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG1 . FORCE_SET_ENA
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG1_FORCE_SET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG1_FORCE_SET_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG1_FORCE_SET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PLL5G Configuration 2
 *
 * \details
 * Configuration register 2 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG2
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,2)

/** 
 * \brief
 * enables test modes, e.g. fbdivsel
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_TEST_MODE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_TEST_MODE  VTSS_BIT(30)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * enable flip of refclk and fbclk at PFD, used for 2nd chargepump
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_PFD_IN_FLIP
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_PFD_IN_FLIP(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_PFD_IN_FLIP  VTSS_BIT(29)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_PFD_IN_FLIP(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * enable VCO frequency control output
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_VCO_NREF_TESTOUT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_VCO_NREF_TESTOUT(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_VCO_NREF_TESTOUT  VTSS_BIT(28)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_VCO_NREF_TESTOUT(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * enable feedback divider output to test output buffer
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_FBTESTOUT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_FBTESTOUT(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_FBTESTOUT  VTSS_BIT(27)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_FBTESTOUT(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * enable RCPLL clock buffer in LCPLL VCO (sx_ena_vco_buf_i must be set to
 * 0)
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_RCPLL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_RCPLL(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_RCPLL  VTSS_BIT(26)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_RCPLL(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * enable resistor mode chargepump, test mode
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_CP2
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CP2(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CP2  VTSS_BIT(25)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CP2(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from extra dividers
 * (125MHz, 250MHz, 312.5MHz)
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_CLK_BYPASS1
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS1(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS1  VTSS_BIT(24)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS1(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from ref clock pad
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_CLK_BYPASS
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS  VTSS_BIT(23)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_CLK_BYPASS(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * force VCO amplitude control output to low (no VCO current) 0:force, 1:
 * no force
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . PWD_AMPCTRL_N
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_PWD_AMPCTRL_N(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_PWD_AMPCTRL_N  VTSS_BIT(22)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_PWD_AMPCTRL_N(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * enable automatic VCO amplitude control
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_AMPCTRL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMPCTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMPCTRL  VTSS_BIT(21)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMPCTRL(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * enable static VCO amplitude control
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_AMP_CTRL_FORCE
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMP_CTRL_FORCE(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMP_CTRL_FORCE  VTSS_BIT(20)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_AMP_CTRL_FORCE(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * static VCO amplitude control, active w/ ena_amp_ctrl_force 0: lowest
 * current, 255: highest current
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . AMPC_SEL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_AMPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,8)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_AMPC_SEL     VTSS_ENCODE_BITMASK(12,8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_AMPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,8)

/** 
 * \brief
 * forces the startup FSM to start ramp up the frequency by POR 0: no
 * force,1: force
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . FRC_FSM_POR
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_FRC_FSM_POR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_FRC_FSM_POR  VTSS_BIT(11)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_FRC_FSM_POR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * disables the startup FSM to start ramp up the frequency from POR 0:
 * normal,1: disable
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . DISABLE_FSM_POR
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM_POR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM_POR  VTSS_BIT(10)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM_POR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * setting for static VCO frequency stepping 0: lowest frequency,31:
 * highest frequency
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . GAIN_TEST
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_GAIN_TEST(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_GAIN_TEST     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_GAIN_TEST(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * enable FSM frequency deviation overrun
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . EN_RESET_OVERRUN
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_OVERRUN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_OVERRUN  VTSS_BIT(4)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_OVERRUN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * enable FSM limiter detection
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . EN_RESET_LIM_DET
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_LIM_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_LIM_DET  VTSS_BIT(3)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_LIM_DET(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * enable FSM frequency deviation detection
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . EN_RESET_FRQ_DET
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_FRQ_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_FRQ_DET  VTSS_BIT(2)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_EN_RESET_FRQ_DET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * disable automatic FSM startup frequency stepping
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . DISABLE_FSM
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM  VTSS_BIT(1)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_DISABLE_FSM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * enable static VCO frequency stepping
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG2 . ENA_GAIN_TEST
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_GAIN_TEST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_GAIN_TEST  VTSS_BIT(0)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG2_ENA_GAIN_TEST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PLL5G Configuration 3
 *
 * \details
 * Configuration register 3 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG3
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,3)

/** 
 * \brief
 * select analog test output input signal
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . TEST_ANA_OUT_SEL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_TEST_ANA_OUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_TEST_ANA_OUT_SEL     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_TEST_ANA_OUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Set to 3 to enable CLKOUT2 synchronous Ethernet reference clock output.
 * Applies only to PLL2.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . CLKOUT2_SEL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_CLKOUT2_SEL(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_CLKOUT2_SEL     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_CLKOUT2_SEL(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * enable analog test output
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . ENA_ANA_TEST_OUT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_ANA_TEST_OUT(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_ANA_TEST_OUT  VTSS_BIT(18)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_ANA_TEST_OUT(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * enable differential test output
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . ENA_TEST_OUT
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_TEST_OUT(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_TEST_OUT  VTSS_BIT(17)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_ENA_TEST_OUT(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * enable symmetric feedback divider clock output 0: fbclk/2, 1: fbclk
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . SEL_FBDCLK
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_FBDCLK(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_FBDCLK  VTSS_BIT(16)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_FBDCLK(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * select CML or CMOS phase/frequency detector 0: CML, 1: CMOS
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . SEL_CML_CMOS_PFD
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_CML_CMOS_PFD(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_CML_CMOS_PFD  VTSS_BIT(15)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_SEL_CML_CMOS_PFD(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * reset for feedback divider, active low 0: reset,1:no reset
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . RST_FB_N
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_RST_FB_N(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_RST_FB_N  VTSS_BIT(14)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_RST_FB_N(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * force vco contrh input to mid level (mid CML level)
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FORCE_VCO_CONTRH
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_VCO_CONTRH(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_VCO_CONTRH  VTSS_BIT(13)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_VCO_CONTRH(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * force chargepump output to low, gives lowest VCO frequency
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FORCE_LO
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_LO(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_LO  VTSS_BIT(12)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_LO(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * force chargepump output to high, gives highest VCO frequency
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FORCE_HI
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_HI(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_HI  VTSS_BIT(11)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_HI(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * enable force VCO frequency high/low (force_hi/lo)
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FORCE_ENA
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_ENA  VTSS_BIT(10)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * force chargepump output to nominal VCO operating point
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FORCE_CP
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_CP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_CP  VTSS_BIT(9)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FORCE_CP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * enable feedback divider testmode
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FBDIVSEL_TST_ENA
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL_TST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL_TST_ENA  VTSS_BIT(8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL_TST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * setting for feedback divider, divide by 12..255 12..255
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG3 . FBDIVSEL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG3_FBDIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief PLL5G Configuration 4
 *
 * \details
 * Configuration register 4 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG4
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG4(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,4)

/** 
 * \brief
 * settings for reference clock input buffer BIAS
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG4 . IB_BIAS_CTRL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_BIAS_CTRL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * settings for reference clock input buffer
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG4 . IB_CTRL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG4_IB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G Configuration 5
 *
 * \details
 * Configuration register 5 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG5
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG5(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,5)

/** 
 * \brief
 * settings for test output buffer BIAS
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG5 . OB_BIAS_CTRL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_BIAS_CTRL     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * settings for test output buffer
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG5 . OB_CTRL
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG5_OB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G Configuration 6
 *
 * \details
 * Configuration register 6 for PLL5G
 *
 * Register: \a HSIO:PLL5G_CFG:PLL5G_CFG6
 *
 * @param gi Register: PLL5G_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_CFG_PLL5G_CFG6(gi)   VTSS_IOREG_IX(VTSS_TO_HSIO,0x0,gi,7,0,6)

/** 
 * \brief
 * Enable reference CMOS 1/2 clock
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG6 . ENA_REFCLKC2
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_REFCLKC2(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_REFCLKC2  VTSS_BIT(7)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_REFCLKC2(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * enable feedback divider CMOS 1/2 clock (for FSM)
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG6 . ENA_FBCLKC2
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_FBCLKC2(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_FBCLKC2  VTSS_BIT(6)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG6_ENA_FBCLKC2(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Setting for DDR clock divider
 *
 * \details 
 * 2: 500 MHz
 * 5: 250 MHz
 * 6: 416.66 MHz
 * 14: 312.5 MHz
 * 15: 166.66 MHz
 * Others: Reserved
 *
 * Field: ::VTSS_HSIO_PLL5G_CFG_PLL5G_CFG6 . DDR_CLK_DIV
 */
#define  VTSS_F_HSIO_PLL5G_CFG_PLL5G_CFG6_DDR_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_PLL5G_CFG_PLL5G_CFG6_DDR_CLK_DIV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG6_DDR_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HSIO:PLL5G_STATUS
 *
 * PLL5G Status Registers
 */


/** 
 * \brief PLL5G Status 0
 *
 * \details
 * Status register 0 for the PLL5G
 *
 * Register: \a HSIO:PLL5G_STATUS:PLL5G_STATUS0
 *
 * @param gi Register: PLL5G_STATUS (??), 0-1
 */
#define VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0xe,gi,2,0,0)

/** 
 * \brief
 * RCPLL Flag range limiter signaling
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . RANGE_LIM
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_RANGE_LIM(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_RANGE_LIM  VTSS_BIT(12)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_RANGE_LIM(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * RCPLL Flag that indicates a out of range condition while NOT in
 * calibration mode.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . OUT_OF_RANGE_ERR
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_OUT_OF_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_OUT_OF_RANGE_ERR  VTSS_BIT(11)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_OUT_OF_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * RCPLL Flag that indicates errors that may occur during the calibration
 * procedure.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . CALIBRATION_ERR
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_ERR  VTSS_BIT(10)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_ERR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * RCPLL Flag that indicates that the calibration procedure has finished.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . CALIBRATION_DONE
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_DONE  VTSS_BIT(9)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_CALIBRATION_DONE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * RCPLL Interface to read back internal data of the FSM.
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . READBACK_DATA
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * PLL lock status 0: not locked, 1: locked
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS0 . LOCK_STATUS
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS0_LOCK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS0_LOCK_STATUS  VTSS_BIT(0)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS0_LOCK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PLL5G Status 1
 *
 * \details
 * Status register 1 for the PLL5G
 *
 * Register: \a HSIO:PLL5G_STATUS:PLL5G_STATUS1
 *
 * @param gi Register: PLL5G_STATUS (??), 0-1
 */
#define VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0xe,gi,2,0,1)

/** 
 * \brief
 * sigma delta ADC output
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1 . SIG_DEL
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS1_SIG_DEL(x)  VTSS_ENCODE_BITFIELD(x,19,8)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS1_SIG_DEL     VTSS_ENCODE_BITMASK(19,8)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS1_SIG_DEL(x)  VTSS_EXTRACT_BITFIELD(x,19,8)

/** 
 * \brief
 * VCO frequency step stop
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1 . GAIN_STAT
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS1_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,14,5)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS1_GAIN_STAT     VTSS_ENCODE_BITMASK(14,5)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS1_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,14,5)

/** 
 * \brief
 * VCO frequency difference to refclk
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1 . FBCNT_DIF
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FBCNT_DIF(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FBCNT_DIF     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FBCNT_DIF(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * startup FSM internal status
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1 . FSM_STAT
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_STAT     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * startup FSM lock status
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_STATUS_PLL5G_STATUS1 . FSM_LOCK
 */
#define  VTSS_F_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_LOCK  VTSS_BIT(0)
#define  VTSS_X_HSIO_PLL5G_STATUS_PLL5G_STATUS1_FSM_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSIO:PLL5G_BIST_CFG
 *
 * PLL5G BIST Configuration Register set
 */


/** 
 * \brief PLL5G BIST Configuration register 0A
 *
 * \details
 * Configuration register 0A for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_CFG:PLL5G_BIST_CFG0A
 *
 * @param gi Register: PLL5G_BIST_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0A(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x12,gi,4,0,0)

/** 
 * \brief
 * BIST compare pre divider M
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0A . PLLB_DIV_FACTOR_PRE
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0A_PLLB_DIV_FACTOR_PRE(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0A_PLLB_DIV_FACTOR_PRE     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0A_PLLB_DIV_FACTOR_PRE(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Configuration register 0B
 *
 * \details
 * Configuration register 0B for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_CFG:PLL5G_BIST_CFG0B
 *
 * @param gi Register: PLL5G_BIST_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x12,gi,4,0,1)

/** 
 * \brief
 * BIST start, 0: reset BIST, 1: start/enable BIST
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B . PLLB_START_BIST
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_START_BIST(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_START_BIST  VTSS_BIT(15)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_START_BIST(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * BIST measure mode, 0: frequency, 1: phase
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B . PLLB_MEAS_MODE
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_MEAS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_MEAS_MODE  VTSS_BIT(14)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_MEAS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * BIST compare divider repeat count
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B . PLLB_LOCK_REPEAT
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_REPEAT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_REPEAT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_REPEAT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * BIST compare divider phase uncertainty
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B . PLLB_LOCK_UNCERT
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_UNCERT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_UNCERT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG0B_PLLB_LOCK_UNCERT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief PLL5G BIST Configuration register 1
 *
 * \details
 * Configuration register 1 for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_CFG:PLL5G_BIST_CFG1
 *
 * @param gi Register: PLL5G_BIST_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG1(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x12,gi,4,0,2)

/** 
 * \brief
 * BIST compare divider M
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG1 . PLLB_DIV_FACTOR_M
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG1_PLLB_DIV_FACTOR_M(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_CFG:PLL5G_BIST_CFG2
 *
 * @param gi Register: PLL5G_BIST_CFG (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG2(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x12,gi,4,0,3)

/** 
 * \brief
 * BIST compare divider N
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG2 . PLLB_DIV_FACTOR_N
 */
#define  VTSS_F_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_BIST_CFG_PLL5G_BIST_CFG2_PLLB_DIV_FACTOR_N(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HSIO:PLL5G_BIST_STATUS
 *
 * PLL5G BIST Status Register set
 */


/** 
 * \brief PLL5G BIST Status register 0
 *
 * \details
 * Status register 0 for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_STATUS:PLL5G_BIST_STAT0
 *
 * @param gi Register: PLL5G_BIST_STATUS (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x1a,gi,3,0,0)

/** 
 * \brief
 * BIST pll_cnt upper limit at max. frequency
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0 . PLLB_FSM_STAT
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FSM_STAT     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * BIST busy, 0: not busy, 1: busy
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0 . PLLB_BUSY
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_BUSY  VTSS_BIT(2)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST done, 0: done, 1: not done
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0 . PLLB_DONE_N
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_DONE_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_DONE_N  VTSS_BIT(1)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_DONE_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST pass/fail, 0: passed, 1: failed
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0 . PLLB_FAIL
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FAIL  VTSS_BIT(0)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT0_PLLB_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief PLL5G BIST Status register 1A
 *
 * \details
 * Status register 1A for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_STATUS:PLL5G_BIST_STAT1A
 *
 * @param gi Register: PLL5G_BIST_STATUS (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1A(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x1a,gi,3,0,1)

/** 
 * \brief
 * BIST compare divider phase difference
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1A . PLLB_CNT_REF_DIFF
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1A_PLLB_CNT_REF_DIFF(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1A_PLLB_CNT_REF_DIFF     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1A_PLLB_CNT_REF_DIFF(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief PLL5G BIST Status register 1B
 *
 * \details
 * Status register 1B for PLL5G BIST.
 *
 * Register: \a HSIO:PLL5G_BIST_STATUS:PLL5G_BIST_STAT1B
 *
 * @param gi Register: PLL5G_BIST_STATUS (??), 0-1
 */
#define VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1B(gi)  VTSS_IOREG_IX(VTSS_TO_HSIO,0x1a,gi,3,0,2)

/** 
 * \brief
 * BIST compare divider phase difference
 *
 * \details 
 * Field: ::VTSS_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1B . PLLB_CNT_OUT
 */
#define  VTSS_F_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1B_PLLB_CNT_OUT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1B_PLLB_CNT_OUT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_PLL5G_BIST_STATUS_PLL5G_BIST_STAT1B_PLLB_CNT_OUT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HSIO:RCOMP_CFG
 *
 * RCOMP Configuration Registers
 */


/** 
 * \brief RCOMP Configuration 0
 *
 * \details
 * Configuration register 0 for RCOMP
 *
 * Register: \a HSIO:RCOMP_CFG:RCOMP_CFG0
 */
#define VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0       VTSS_IOREG(VTSS_TO_HSIO,0x20)

/** 
 * \brief
 * Enable power-down after calibration was done
 *
 * \details 
 * 0: disable power-down
 * 1: enable power-down
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . PWD_ENA
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_PWD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_PWD_ENA  VTSS_BIT(13)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_PWD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Start calibration
 *
 * \details 
 * 0: idle/inactive
 * 1: start (activate)
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . RUN_CAL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_RUN_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_RUN_CAL  VTSS_BIT(12)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_RUN_CAL(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Speed selection. Setting time for analog circuit after changing resistor
 * settings.
 *
 * \details 
 * 0: max period
 * 1: max period/2
 * 2: max period/4
 * 3: max period/8
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . SPEED_SEL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * RCOMP operation mode
 *
 * \details 
 * 0: inactive
 * 1: perform calibration permanently
 * 2: perform calibration once
 * 3: perform calibration once and generate alarm if necessary
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . MODE_SEL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Overwrite measured resistor value with value programmed in rcomp_val
 *
 * \details 
 * 0: normal mode
 * 1: overwrite mode
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . FORCE_ENA
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_FORCE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_FORCE_ENA  VTSS_BIT(4)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_FORCE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Resistor comparator value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: ::VTSS_HSIO_RCOMP_CFG_RCOMP_CFG0 . RCOMP_VAL
 */
#define  VTSS_F_HSIO_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a HSIO:RCOMP_STATUS
 *
 * RCOMP Status Registers
 */


/** 
 * \brief RCOMP Status
 *
 * \details
 * Status register bits for the RCOMP
 *
 * Register: \a HSIO:RCOMP_STATUS:RCOMP_STATUS
 */
#define VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x21)

/** 
 * \brief
 * Resistor comparison activity
 *
 * \details 
 * 0: resistor measurement finished or inactive
 * 1: resistor measurement in progress
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . BUSY
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_BUSY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_RCOMP_STATUS_RCOMP_STATUS_BUSY  VTSS_BIT(12)
#define  VTSS_X_HSIO_RCOMP_STATUS_RCOMP_STATUS_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Alarm signal if rcomp isn't best choice anymore
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . DELTA_ALERT
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT  VTSS_BIT(7)
#define  VTSS_X_HSIO_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Measured resistor value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: ::VTSS_HSIO_RCOMP_STATUS_RCOMP_STATUS . RCOMP
 */
#define  VTSS_F_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a HSIO:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/** 
 * \brief SYNC ETH Configuration
 *
 * \details
 * This register is replicated once per recovered clock output.
 *
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_CFG
 *
 * @param ri Register: SYNC_ETH_CFG (??), 0-3
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG(ri)  VTSS_IOREG(VTSS_TO_HSIO,0x22 + (ri))

/** 
 * \brief
 * Select recovered clock source.
 *
 * \details 
 * 0 through 8: Select SD1G 0 through 8.
 * 9 through 24: Select SD6G 0 through 15.
 * 25 through 28: Select SD10G 0 through 3.
 * 29 through 36: Select SD6G 16 through 23.
 * 37 selects LCPLL2 CPU clock output.
 * Other values are reserved.
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG . SEL_RECO_CLK_SRC
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_ENCODE_BITFIELD(x,3,6)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC     VTSS_ENCODE_BITMASK(3,6)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_EXTRACT_BITFIELD(x,3,6)

/** 
 * \brief
 * Select recovered clock divider.
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG . SEL_RECO_CLK_DIV
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Set to enable recovered clock pad
 *
 * \details 
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG . RECO_CLK_ENA
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Configuration of recovered clock from 2'nd PLL
 *
 * \details
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_PLL2_CFG
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x26)

/** 
 * \brief
 * This field is used instead of HSIO::PLL5G_CFG0.CPU_CLK_DIV for the PLL
 * number 2.
 *
 * \details 
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG . CPU_CLK_DIV
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_CPU_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,2,6)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_CPU_CLK_DIV     VTSS_ENCODE_BITMASK(2,6)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_CPU_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,2,6)

/** 
 * \brief
 * Divider setting for the PLL number 2's recovered clock output. These
 * settings are applied prior to sending recovered clock to the optional
 * PAD-divder (see HSIO::SYNC_ETH_CFG.SEL_RECO_CLK_DIV.)
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 2
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG . PLL2_RECO_CLK_DIV
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_RECO_CLK_DIV  VTSS_BIT(1)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet clock output: when set the
 * clock output will stop toggling (keep its last value constantly) when
 * PLL is out of lock.
 *
 * \details 
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG . PLL2_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_AUTO_SQUELCH_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_PLL2_CFG_PLL2_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \details
 * Register: \a HSIO:SYNC_ETH_CFG:SYNC_ETH_SD10G_CFG
 *
 * @param ri Register: SYNC_ETH_SD10G_CFG (??), 0-3
 */
#define VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG(ri)  VTSS_IOREG(VTSS_TO_HSIO,0x27 + (ri))

/** 
 * \brief
 * Divider setting for the SD10G recovered clock output. These settings are
 * applied prior to sending recovered clock to the optional PAD-divder (see
 * HSIO::SYNC_ETH_CFG.SEL_RECO_CLK_DIV.)
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 2
 * 2: Divide clock by (66/32)
 * 3: reserved
 *
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG . SD10G_RECO_CLK_DIV
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Set to enable auto-squelching for sync. ethernet clock output: when set
 * the clock output will stop toggling (keep its last value constantly)
 * when PCS looses link synchrony.
 *
 * \details 
 * Field: ::VTSS_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG . SD10G_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SYNC_ETH_CFG_SYNC_ETH_SD10G_CFG_SD10G_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSIO:SERDES1G_ANA_CFG
 *
 * SERDES1G Analog Configuration Registers
 */


/** 
 * \brief SERDES1G Deserializer Cfg
 *
 * \details
 * Configuration register for SERDES1G deserializer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_DES_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2b)

/** 
 * \brief
 * Control of phase regulator logic. Bit 3 must be set to 0.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled with 99 ppm limit
 * 2: Enabled with 202 ppm limit
 * 3: Enabled with 485 ppm limit
 * 4: Enabled if corresponding PCS is in sync with 50 ppm limit
 * 5: Enabled if corresponding PCS is in sync with 99 ppm limit
 * 6: Enabled if corresponding PCS is in sync with 202 ppm limit
 * 7: Enabled if corresponding PCS is in sync with 485 ppm limit
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_PHS_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_PHS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Deserializer phase control, main CP/MD select
 *
 * \details 
 * 0: Directly from DES
 * 1: Through hysteresis stage from DES
 * 2: From core
 * 3: Disabled
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Des phase control for 180 degrees deadlock block mode of operation
 *
 * \details 
 * 0: Depending on density of input pattern
 * 1: Active until PCS has synchronized
 * 2: Depending on density of input pattern until PCS has synchronized
 * 3: Never
 * 4: Always
 * 5-7: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_MBTR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/** 
 * \brief
 * Bandwidth selection for proportional path of CDR loop.
 *
 * \details 
 * 0: No division
 * 1: Divide by 2
 * 2: Divide by 4
 * 3: Divide by 8
 * 4: Divide by 16
 * 5: Divide by 32
 * 6: Divide by 64
 * 7: Divide by 128
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_BW_ANA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Swap non-hysteresis CP/MD signals.
 *
 * \details 
 * 0: No swapping
 * 1: Swapping
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_SWAP_ANA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_ANA  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selection of time constant for integrative path of CDR loop.
 *
 * \details 
 * 0: Divide by 2
 * 1: Divide by 4
 * 2: Divide by 8
 * 3: Divide by 16
 * 4: Divide by 32
 * 5: Divide by 64
 * 6: Divide by 128
 * 7: Divide by 256
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_BW_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_BW_HYST(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Swap hysteresis CP/MD signals.
 *
 * \details 
 * 0: No swapping
 * 1: Swapping
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG . DES_SWAP_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_HYST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_HYST  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_DES_CFG_DES_SWAP_HYST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G Input Buffer Cfg
 *
 * \details
 * Configuration register for SERDES1G input buffer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_IB_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2c)

/** 
 * \brief
 * Switches signal detect circuit into low frequency mode, must be used in
 * FX100 mode
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_FX100_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA  VTSS_BIT(27)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_FX100_ENA(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Hysteresis level for AC-JTAG Input
 *
 * \details 
 * 0: low
 * 7: high
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . ACJTAG_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_ACJTAG_HYST(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_ACJTAG_HYST     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_ACJTAG_HYST(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Detect thresholds:
 *
 * \details 
 * 0: 159-189mVppd
 * 1: 138-164mVppd
 * 2: 109-124mVppd
 * 3: 74-89mVppd
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_DET_LEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_DET_LEV(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * Input buffer hysteresis levels:
 *
 * \details 
 * 0: 59-79mV
 * 1: 81-124mV
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_HYST_LEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_HYST_LEV(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_HYST_LEV  VTSS_BIT(14)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_HYST_LEV(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enable common mode voltage termination
 *
 * \details 
 * 0: Low termination (VDD_A x 0.7)
 * 1: High termination (VDD_A)
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_CMV_TERM
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM  VTSS_BIT(13)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_CMV_TERM(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Enable dc-coupling of input signal
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_DC_COUPLING
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING  VTSS_BIT(12)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DC_COUPLING(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Enable detect level circuit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_DETLEV
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV  VTSS_BIT(11)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_DETLEV(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable hysteresis for input signal. Hystesis can only be enabled if DC
 * offset compensation is disabled.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_HYST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_HYST(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_HYST  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_HYST(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Enable offset compensation of input stage. This bit must be disabled to
 * enable hysteresis (IB_ENA_HYST).
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_ENA_OFFSET_COMP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_ENA_OFFSET_COMP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Selects weighting between AC and DC input path:
 *
 * \details 
 * 0: Reserved
 * 1: Reserved
 * 2: 0dB (recommended value)
 * 3: 1.5dB
 * 4: 3dB
 * 5: 6dB
 * 6: 9dB
 * 12.5dB
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_EQ_GAIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_EQ_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Corner frequencies of AC path:
 *
 * \details 
 * 0: 1.3GHz
 * 1: 1.5GHz
 * 2: 1.6GHz
 * 3: 1.8GHz
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_SEL_CORNER_FREQ
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_SEL_CORNER_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP. (default:
 * -3)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG . IB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_IB_CFG_IB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES1G Output Buffer Cfg
 *
 * \details
 * Configuration register for SERDES1G output buffer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_OB_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2d)

/** 
 * \brief
 * Slope / slew rate control:
 *
 * \details 
 * 0: 45ps
 * 1: 85ps
 * 2: 105ps
 * 3: 115ps
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_SLP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_SLP(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Amplitude control in steps of 50mVppd.
 *
 * \details 
 * 0: 0.4Vppd
 * 15: 1.1Vppd
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_AMP_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_AMP_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * CMM bias control
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_CMM_BIAS_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_CMM_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_CMM_BIAS_CTRL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_CMM_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Disable VCM control
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_DIS_VCM_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_DIS_VCM_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_DIS_VCM_CTRL  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_DIS_VCM_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable measure vreg
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_EN_MEAS_VREG
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_EN_MEAS_VREG(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_EN_MEAS_VREG  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_EN_MEAS_VREG(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Common mode voltage control:
 *
 * \details 
 * 0: Reserved
 * 1: 440mV
 * 2: 480mV
 * 3: 460mV
 * 4: 530mV
 * 5: 500mV
 * 6: 570mV
 * 7: 550mV
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_VCM_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_VCM_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Resistor control. Value must be taken from RCOMP_STATUS.RCOMP. (default:
 * +1)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG . OB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES1G Serializer Cfg
 *
 * \details
 * Configuration register for SERDES1G serializer
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_SER_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2e)

/** 
 * \brief
 * Invert output D0b for idle-mode of OB
 *
 * \details 
 * 0: Non-inverting
 * 1. Inverting
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_IDLE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Invert and delays (one clk cycle) output D1 for de-emphasis of OB
 *
 * \details 
 * 0: Non-inverting and non-delaying
 * 1: Inverting and delaying
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_DEEMPH
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_DEEMPH(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_DEEMPH  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_DEEMPH(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Select source of CP/MD signals
 *
 * \details 
 * 0: Phase alignment block
 * 1: Core
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_CPMD_SEL  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Swap CP/MD signals of phase alignment circuit
 *
 * \details 
 * 0: Disable swapping
 * 1: Enable swapping
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_SWAP_CPMD
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_SWAP_CPMD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_SWAP_CPMD  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_SWAP_CPMD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Select reference clock source for phase alignment
 *
 * \details 
 * 0: RXCLKP
 * 1: RefClk15MHz
 * 2: RXCLKN
 * 3: ext. ALICLK
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_ALISEL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ALISEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ALISEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ALISEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable hysteresis for phase alignment
 *
 * \details 
 * 0: Disable hysteresis
 * 1: Enable hysteresis
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_ENHYS
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENHYS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENHYS  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENHYS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Use wider window for phase alignment
 *
 * \details 
 * 0: Use small window for low jitter (100 to 200ps)
 * 1: Use wide window for higher jitter (150 to 300 ps)
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_BIG_WIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_BIG_WIN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_BIG_WIN  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_BIG_WIN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable window for phase alignment
 *
 * \details 
 * 0: Disable window
 * 1: Enable window
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_EN_WIN
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_EN_WIN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_EN_WIN  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_EN_WIN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable phase alignment
 *
 * \details 
 * 0: Disable phase alignment
 * 1: Enable phase alignment
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG . SER_ENALI
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_SER_CFG_SER_ENALI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G Common Cfg
 *
 * \details
 * Configuration register for common SERDES1G functions Note: When enabling
 * the facility loop (ena_floop) also the phase alignment in the serializer
 * has to be enabled and configured adequate.
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_COMMON_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x2f)

/** 
 * \brief
 * System reset (low active)
 *
 * \details 
 * 0: Apply reset (not self-clearing)
 * 1: Reset released
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . SYS_RST
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST  VTSS_BIT(31)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SYS_RST(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet clock output: when set the
 * clock output will stop toggling (keep its last value constantly) when
 * PCS looses link synchrony.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . SE_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA  VTSS_BIT(21)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Enable lane
 *
 * \details 
 * 0: Disable lane
 * 1: Enable line
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_LANE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE  VTSS_BIT(18)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_LANE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Power-down RX-path
 *
 * \details 
 * 0: Normal mode
 * 1: Power down mode
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . PWD_RX
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_RX  VTSS_BIT(17)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_RX(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Power-down TX-path
 *
 * \details 
 * 0: Normal mode
 * 1: Power down mode
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . PWD_TX
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_TX  VTSS_BIT(16)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_PWD_TX(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Hidden spare bits (not connected internally yet)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . LANE_CTRL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_LANE_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_LANE_CTRL     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_LANE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/** 
 * \brief
 * Enable direct line
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_DIRECT
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_DIRECT  VTSS_BIT(12)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Enable equipment loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_ELOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP  VTSS_BIT(11)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ELOOP(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable facility loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_FLOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_FLOOP(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Enable input loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_ILOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ILOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ILOOP  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_ILOOP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable pad loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . ENA_PLOOP
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_PLOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_PLOOP  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_ENA_PLOOP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable half rate
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . HRATE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_HRATE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_HRATE  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_HRATE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Interface mode
 *
 * \details 
 * 0: 8-bit mode
 * 1: 10-bit mode
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG . IF_MODE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_IF_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_IF_MODE  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_COMMON_CFG_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G Pll Cfg
 *
 * \details
 * Configuration register for SERDES1G RCPLL
 *
 * Register: \a HSIO:SERDES1G_ANA_CFG:SERDES1G_PLL_CFG
 */
#define VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x30)

/** 
 * \brief
 * Enable feedback divider (divide by two)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_ENA_FB_DIV2
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_FB_DIV2(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_FB_DIV2  VTSS_BIT(22)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_FB_DIV2(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Enable reference clock divider (divide by two)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_ENA_RC_DIV2
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_RC_DIV2(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_RC_DIV2  VTSS_BIT(21)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_ENA_RC_DIV2(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Control data for FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_CTRL_DATA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enable FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable FSM forcing
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_FORCE_SET_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_FORCE_SET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_FORCE_SET_ENA  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_FORCE_SET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable FSM recalibration
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_FSM_OOR_RECAL_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Select RB data
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG . PLL_RB_DATA_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_RB_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_RB_DATA_SEL  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_ANA_CFG_SERDES1G_PLL_CFG_PLL_RB_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * Register Group: \a HSIO:SERDES1G_ANA_STATUS
 *
 * SERDES1G Analog Status Register
 */


/** 
 * \brief SERDES1G Pll Status
 *
 * \details
 * Status register of SERDES1G RCPLL
 *
 * Register: \a HSIO:SERDES1G_ANA_STATUS:SERDES1G_PLL_STATUS
 */
#define VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x31)

/** 
 * \brief
 * Calibration status
 *
 * \details 
 * 0: Calibration not started or ongoing
 * 1: Calibration finished
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS . PLL_CAL_NOT_DONE
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_NOT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_NOT_DONE  VTSS_BIT(12)
#define  VTSS_X_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_NOT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Calibration error
 *
 * \details 
 * 0: No error during calibration
 * 1: Errors occured during calibration
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS . PLL_CAL_ERR
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_ERR  VTSS_BIT(11)
#define  VTSS_X_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_CAL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Out of range error
 *
 * \details 
 * 0: No out of range condition detected
 * 1: Out of range condition since last calibration detected
 *
 * Field: ::VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS . PLL_OUT_OF_RANGE_ERR
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * PLL read-back data, depending on "pll_rb_data_sel" either the calibrated
 * setting or the measured period
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS . PLL_RB_DATA
 */
#define  VTSS_F_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_RB_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSIO_SERDES1G_ANA_STATUS_SERDES1G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a HSIO:SERDES1G_DIG_CFG
 *
 * SERDES1G Digital Configuration Register
 */


/** 
 * \brief SERDES1G DFT Configuration register 0
 *
 * \details
 * Configuration register 0 for SERDES1G DFT functions
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG0
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x32)

/** 
 * \brief
 * Lazy designers spare bit
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . LAZYBIT
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_LAZYBIT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_LAZYBIT  VTSS_BIT(31)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_LAZYBIT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Disable output inverter of BIST PRBS generator
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . INV_DIS
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_INV_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_INV_DIS  VTSS_BIT(23)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_INV_DIS(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Select PRBS pattern for BIST
 *
 * \details 
 * 0: G(x) = x^7 + x^6 + 1
 * 1: G(x) = x^15 + x^14 + 1
 * 2: G(x) = x^23 + x^18 + 1
 * 3: G(x) = x^31 + x^28 + 1
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . PRBS_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_PRBS_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_PRBS_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_PRBS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Selection of test mode
 *
 * \details 
 * 0: Normal operation
 * 1: BIST
 * 2: Fixed pattern
 * 3: Random pattern
 * 4-7: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . TEST_MODE
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TEST_MODE     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Disable influence of external phase correction on step controller
 *
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . RX_PHS_CORR_DIS
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PHS_CORR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PHS_CORR_DIS  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PHS_CORR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable sensitivity for phasedetector CP/MD (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . RX_PDSENS_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PDSENS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PDSENS_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_PDSENS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * General enable for Jitter-Injection/Frequency-Offset-Generation Block
 * (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . RX_DFT_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_DFT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_DFT_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_RX_DFT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * General enable for Jitter-Injection/Frequency-Offset-Generation Block
 * (TX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0 . TX_DFT_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TX_DFT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TX_DFT_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG0_TX_DFT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G DFT Configuration register 1
 *
 * \details
 * Configuration register 1 for SERDES1G DFT functions (TX direction)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG1
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x33)

/** 
 * \brief
 * Amplitude of jitter for Jitter-Injection (TX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_JITTER_AMPL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JITTER_AMPL(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JITTER_AMPL     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JITTER_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Stepping frequency for Jitter-Injection/Frequency-Offset-Generation
 * (1/2^n) (TX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_STEP_FREQ
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_STEP_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_STEP_FREQ     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_STEP_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Enable TX jitter intertion
 *
 * \details 
 * 0: Off
 * 1:On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_JI_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JI_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JI_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_JI_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select waveform for Jitter-Injection (TX-Path)
 *
 * \details 
 * 0: Triangular
 * 1: Flattened (sinusoidal)
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_WAVEFORM_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_WAVEFORM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_WAVEFORM_SEL  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_WAVEFORM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Direction of Frequency-Offset (TX-Path)
 *
 * \details 
 * 0: Down
 * 1: Up
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_FREQOFF_DIR
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_DIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_DIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable Frequency-Offset-Generation (TX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1 . TX_FREQOFF_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG1_TX_FREQOFF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G DFT Configuration register 2
 *
 * \details
 * Configuration register 2 for SERDES1G DFT functions (RX direction)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_DFT_CFG2
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0x34)

/** 
 * \brief
 * Amplitude of jitter for Link-Quality-Evaluation/Jitter-Injection
 * (RX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_JITTER_AMPL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JITTER_AMPL(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JITTER_AMPL     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JITTER_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Stepping frequency for Jitter-Injection/Frequency-Offset-Generation
 * (1/2^n) (RX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_STEP_FREQ
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_STEP_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_STEP_FREQ     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_STEP_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Enable RX jitter intertion
 *
 * \details 
 * 0: Off
 * 1:On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_JI_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JI_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JI_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_JI_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select waveform for Jitter-Injection (RX-Path)
 *
 * \details 
 * 0: Triangular
 * 1: Flattened
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_WAVEFORM_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_WAVEFORM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_WAVEFORM_SEL  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_WAVEFORM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Direction of Frequency-Offset (RX-Path)
 *
 * \details 
 * 0: Down
 * 1: Up
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_FREQOFF_DIR
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_DIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_DIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable Frequency-Offset-Generation (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2 . RX_FREQOFF_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_DFT_CFG2_RX_FREQOFF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES1G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_TP_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x35)

/** 
 * \brief
 * Static pattern tranferred in fixed pattern test mode, LSB is transferred
 * first
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG . STATIC_PATTERN
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG_STATIC_PATTERN(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG_STATIC_PATTERN     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_TP_CFG_STATIC_PATTERN(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief SERDES1G RCPLL BIST Configuration
 *
 * \details
 * Configuration register for the 1G RC-PLL BIST
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_RC_PLL_BIST_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x36)

/** 
 * \brief
 * Enables the BIST for the RC-PLL
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG . PLL_BIST_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_ENA  VTSS_BIT(20)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Feedback divider setting for closed loop test at high frequency. B1:
 * Rc_div2, B0: Fb_div2.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG . PLL_BIST_FBS_HIGH
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Higher frequnecy for the RC-PLL BIST
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG . PLL_BIST_HIGH
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_HIGH(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_HIGH     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Lower frequnecy for the RC-PLL BIST
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG . PLL_BIST_LOW
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_LOW     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_RC_PLL_BIST_CFG_PLL_BIST_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief SERDES1G Misc Configuration
 *
 * \details
 * Configuration register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES1G_DIG_CFG:SERDES1G_MISC_CFG
 */
#define VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x37)

/** 
 * \brief
 * Select mode of kick-out-of-180-degree functionality
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . DES_100FX_KICK_MODE
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_KICK_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_KICK_MODE     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_KICK_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Swap cp/md signals in 100fx mode
 *
 * \details 
 * 0: No swapping of cp and md
 * 1: Swap cp and md
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . DES_100FX_CPMD_SWAP
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_SWAP  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Select simple 100fx mode
 *
 * \details 
 * 0: Normal mode
 * 1: Simple mode
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . DES_100FX_CPMD_MODE
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_MODE  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable deserializer cp/md handling for 100fx mode
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . DES_100FX_CPMD_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_DES_100FX_CPMD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable RX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . RX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_LPI_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_LPI_MODE_ENA  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_LPI_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable TX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . TX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_LPI_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_LPI_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_LPI_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable data inversion received from Deserializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . RX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_DATA_INV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_DATA_INV_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_RX_DATA_INV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable data inversion sent to Serializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . TX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_DATA_INV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_DATA_INV_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_TX_DATA_INV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Lane Reset
 *
 * \details 
 * 0: No reset
 * 1: Reset (not self-clearing)
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG . LANE_RST
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_CFG_SERDES1G_MISC_CFG_LANE_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSIO:SERDES1G_DIG_STATUS
 *
 * SERDES1G Digital Status Register
 */


/** 
 * \brief SERDES1G DFT Status
 *
 * \details
 * Status register of SERDES1G DFT functions
 *
 * Register: \a HSIO:SERDES1G_DIG_STATUS:SERDES1G_DFT_STATUS
 */
#define VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x38)

/** 
 * \brief
 * RC-PLL BIST not done flag
 *
 * \details 
 * 0: BIST done
 * 1: BIST not started or active
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . PLL_BIST_NOT_DONE
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_NOT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_NOT_DONE  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_NOT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * RC-PLL BIST result
 *
 * \details 
 * 0: No error found
 * 1: Errors during BIST found
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . PLL_BIST_FAILED
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_FAILED  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * RC-PLL BIST timeout error flag
 *
 * \details 
 * 0: No timeout occured
 * 1: Timeout occured
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . PLL_BIST_TIMEOUT_ERR
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * BIST activity
 *
 * \details 
 * 0: BIST inactive
 * 1: BIST active
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . BIST_ACTIVE
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ACTIVE  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * BIST sync result
 *
 * \details 
 * 0: Synchronization successful
 * 1: Synchronization on BIST data failed
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . BIST_NOSYNC
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_NOSYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_NOSYNC  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_NOSYNC(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST completion state (low-active)
 *
 * \details 
 * 0: BIST completed
 * 1: not completed
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . BIST_COMPLETE_N
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_COMPLETE_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_COMPLETE_N  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_COMPLETE_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST result
 *
 * \details 
 * 0: No error found
 * 1: Errors during BIST found
 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS . BIST_ERROR
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ERROR  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_DFT_STATUS_BIST_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES1G Misc Status
 *
 * \details
 * Status register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES1G_DIG_STATUS:SERDES1G_MISC_STATUS
 */
#define VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_MISC_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x39)

/** 
 * \brief
 * Phase selection of DES in 100fx mode
 *
 * \details 
 * 0: CDR locked at bit 9
 * 1: CDR locked at bit 4

 *
 * Field: ::VTSS_HSIO_SERDES1G_DIG_STATUS_SERDES1G_MISC_STATUS . DES_100FX_PHASE_SEL
 */
#define  VTSS_F_HSIO_SERDES1G_DIG_STATUS_SERDES1G_MISC_STATUS_DES_100FX_PHASE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES1G_DIG_STATUS_SERDES1G_MISC_STATUS_DES_100FX_PHASE_SEL  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES1G_DIG_STATUS_SERDES1G_MISC_STATUS_DES_100FX_PHASE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSIO:MCB_SERDES1G_CFG
 *
 * MCB SERDES1G Configuration Register
 */


/** 
 * \brief MCB SERDES1G Address Cfg
 *
 * \details
 * Configuration of SERDES1G MCB slaves to be accessed
 *
 * Register: \a HSIO:MCB_SERDES1G_CFG:MCB_SERDES1G_ADDR_CFG
 */
#define VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x3a)

/** 
 * \brief
 * Initiate a write access to marked SERDES1G slaves
 *
 * \details 
 * 0: No write operation pending
 * 1: Initiate write to slaves (kept 1 until write operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_WR_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT  VTSS_BIT(31)
#define  VTSS_X_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_WR_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Initiate a read access to marked SERDES1G slaves
 *
 * \details 
 * 0: No read operation pending (read op finished after bit has been set)
 * 1: Initiate a read access (kept 1 until read operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_RD_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT  VTSS_BIT(30)
#define  VTSS_X_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Activation vector for SERDES1G-Slaves, one-hot coded, each bit is
 * related to one macro, e.g. bit 0 enables/disables access to macro no. 0.
 *
 * \details 
 * 0: Disable macro access via MCB
 * 1: Enable macro access via MCB
 *
 * Field: ::VTSS_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG . SERDES1G_ADDR
 */
#define  VTSS_F_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,9)
#define  VTSS_M_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR     VTSS_ENCODE_BITMASK(0,9)
#define  VTSS_X_HSIO_MCB_SERDES1G_CFG_MCB_SERDES1G_ADDR_CFG_SERDES1G_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a HSIO:SERDES6G_DIG_CFG
 *
 * SERDES6G Digital Configuration Registers
 */


/** 
 * \brief SERDES6G Digital Configuration register
 *
 * \details
 * Configuration register for SERDES6G digital functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DIG_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x3b)

/** 
 * \brief
 * General purpose bits, reserved for future use.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . GP
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_GP(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_GP     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_GP(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Select bit doubling mode
 *
 * \details 
 * 0: (20 bit) Data word contains two byte constant for 2 UI
 * 1: Every bit is streched to two UI.
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . TX_BIT_DOUBLING_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_TX_BIT_DOUBLING_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_TX_BIT_DOUBLING_MODE_ENA  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_TX_BIT_DOUBLING_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Reserved for test purposes. SigDet timer values are divided by 2^6
 *
 * \details 
 * 1: Enable division
 * 0: Normal operation
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_TESTMODE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_TESTMODE  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Signal detect assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 35 us
 * 2: 70 us
 * 3: 105 us
 * 4: 140 us
 * 5..7: reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_AST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_AST(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Signal detect de-assertion time
 *
 * \details 
 * 0: 0 us
 * 1: 250 us
 * 2: 350 us
 * 3: 450 us
 * 4: 550 us
 * 5..7: reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG . SIGDET_DST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DIG_CFG_SIGDET_DST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G DFT Configuration register 0
 *
 * \details
 * Configuration register 0 for SERDES6G DFT functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG0
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x3c)

/** 
 * \brief
 * Lazy designers spare bit
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . LAZYBIT
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_LAZYBIT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_LAZYBIT  VTSS_BIT(31)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_LAZYBIT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Disable output inverter of BIST PRBS generator
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . INV_DIS
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_INV_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_INV_DIS  VTSS_BIT(23)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_INV_DIS(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Select PRBS pattern for BIST
 *
 * \details 
 * 0: G(x) = x^7 + x^6 + 1
 * 1: G(x) = x^15 + x^14 + 1
 * 2: G(x) = x^23 + x^18 + 1
 * 3: G(x) = x^31 + x^28 + 1
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . PRBS_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_PRBS_SEL(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_PRBS_SEL     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_PRBS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Selection of test mode
 *
 * \details 
 * 0: Normal operation
 * 1: BIST
 * 2: Fixed pattern
 * 3: Random pattern
 * 4: Jitter injection
 * 5-7: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . TEST_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Disable influence of external phase correction on step controller
 *
 * \details 
 * 0: Enable
 * 1: Disable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . RX_PHS_CORR_DIS
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PHS_CORR_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PHS_CORR_DIS  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PHS_CORR_DIS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable sensitivity for phasedetector CP/MD (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . RX_PDSENS_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PDSENS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PDSENS_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_PDSENS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * General enable for Jitter-Injection/Frequency-Offset-Generation Block
 * (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . RX_DFT_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_DFT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_DFT_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_RX_DFT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * General enable for Jitter-Injection/Frequency-Offset-Generation Block
 * (TX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0 . TX_DFT_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TX_DFT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TX_DFT_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG0_TX_DFT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G DFT Configuration register 1
 *
 * \details
 * Configuration register 1 for SERDES6G DFT functions (TX direction)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG1
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x3d)

/** 
 * \brief
 * Amplitude of jitter for Jitter-Injection (TX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_JITTER_AMPL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JITTER_AMPL(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JITTER_AMPL     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JITTER_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Stepping frequency for Jitter-Injection/Frequency-Offset-Generation
 * (1/2^n) (RX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_STEP_FREQ
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_STEP_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_STEP_FREQ     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_STEP_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Enable TX jitter intertion
 *
 * \details 
 * 0: Off
 * 1:On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_JI_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JI_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JI_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_JI_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select waveform for Jitter-Injection (TX-Path)
 *
 * \details 
 * 0: Triangular
 * 1: Flattened (sinusoidal)
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_WAVEFORM_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_WAVEFORM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_WAVEFORM_SEL  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_WAVEFORM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Direction of Frequency-Offset (TX-Path)
 *
 * \details 
 * 0: Down
 * 1: Up
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_FREQOFF_DIR
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_DIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_DIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable Frequency-Offset-Generation (TX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1 . TX_FREQOFF_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG1_TX_FREQOFF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G DFT Configuration register 2
 *
 * \details
 * Configuration register 2 for SERDES6G DFT functions (RX direction)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_DFT_CFG2
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0x3e)

/** 
 * \brief
 * Amplitude of jitter for Link-Quality-Evaluation/Jitter-Injection
 * (RX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_JITTER_AMPL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JITTER_AMPL(x)  VTSS_ENCODE_BITFIELD(x,8,10)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JITTER_AMPL     VTSS_ENCODE_BITMASK(8,10)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JITTER_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,8,10)

/** 
 * \brief
 * Stepping frequency for Jitter-Injection/Frequency-Offset-Generation
 * (1/2^n) (TX-Path)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_STEP_FREQ
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_STEP_FREQ(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_STEP_FREQ     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_STEP_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Enable RX jitter intertion
 *
 * \details 
 * 0: Off
 * 1:On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_JI_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JI_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JI_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_JI_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select waveform for Jitter-Injection (RX-Path)
 *
 * \details 
 * 0: Triangular
 * 1: Flattened
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_WAVEFORM_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_WAVEFORM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_WAVEFORM_SEL  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_WAVEFORM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Direction of Frequency-Offset (RX-Path)
 *
 * \details 
 * 0: Down
 * 1: Up
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_FREQOFF_DIR
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_DIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_DIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable Frequency-Offset-Generation (RX-Path)
 *
 * \details 
 * 0: Off
 * 1: On
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2 . RX_FREQOFF_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_DFT_CFG2_RX_FREQOFF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern)
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_TP_CFG0
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0  VTSS_IOREG(VTSS_TO_HSIO,0x3f)

/** 
 * \brief
 * Static pattern tranferred in fixed pattern test mode, LSB is transferred
 * first
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0 . STATIC_PATTERN0
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0_STATIC_PATTERN0(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0_STATIC_PATTERN0     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG0_STATIC_PATTERN0(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief SERDES6G Test Pattern Configuration
 *
 * \details
 * Test bits (pattern) for SERDES6G lane. These bits are used when
 * Lane_Test_cfg.Test_mode is set to 2 (fixed pattern) and
 * Lane_cfg.hr_mode_ena = '0'. In 20 bit modes bits from static_pattern and
 * static_pattern2 are transmitted alternating.
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_TP_CFG1
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x40)

/** 
 * \brief
 * Static pattern 2nd part only used in 20 bit mode, LSB is transferred
 * first
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1 . STATIC_PATTERN1
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1_STATIC_PATTERN1(x)  VTSS_ENCODE_BITFIELD(x,0,20)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1_STATIC_PATTERN1     VTSS_ENCODE_BITMASK(0,20)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_TP_CFG1_STATIC_PATTERN1(x)  VTSS_EXTRACT_BITFIELD(x,0,20)


/** 
 * \brief SERDES6G RCPLL BIST Configuration
 *
 * \details
 * Configuration register for the 6G RC-PLL BIST
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_RC_PLL_BIST_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x41)

/** 
 * \brief
 * Enables the BIST for the RC-PLL
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG . PLL_BIST_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_ENA  VTSS_BIT(20)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Feedback divider setting for closed loop test at high frequency. B3:
 * Div4, B2: Ena_rot, B1: Rot_dir, B0: Rot_frq
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG . PLL_BIST_FBS_HIGH
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_FBS_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Higher frequnecy for the RC-PLL BIST
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG . PLL_BIST_HIGH
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_HIGH(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_HIGH     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_HIGH(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Lower frequnecy for the RC-PLL BIST
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG . PLL_BIST_LOW
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_LOW(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_LOW     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_RC_PLL_BIST_CFG_PLL_BIST_LOW(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief SERDES6G Misc Configuration
 *
 * \details
 * Configuration register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_MISC_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x42)

/** 
 * \brief
 * Select recovered clock divider
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . SEL_RECO_CLK
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_SEL_RECO_CLK(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Select mode of kick-out-of-180-degree functionality
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_KICK_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_KICK_MODE(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_KICK_MODE     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_KICK_MODE(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Swap cp/md signals in 100fx mode
 *
 * \details 
 * 0: No swapping of cp and md
 * 1: Swap cp and md
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_CPMD_SWAP
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_SWAP  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Select simple 100fx mode
 *
 * \details 
 * 0: Normal mode
 * 1: Simple mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_CPMD_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable deserializer cp/md handling for 100fx mode
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . DES_100FX_CPMD_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_DES_100FX_CPMD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable flipping rx databus (MSB - LSB)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_BUS_FLIP_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_BUS_FLIP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_BUS_FLIP_ENA  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_BUS_FLIP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable flipping tx databus (MSB - LSB)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_BUS_FLIP_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_BUS_FLIP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_BUS_FLIP_ENA  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_BUS_FLIP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable RX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_LPI_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable TX-Low-Power feature (Power control by LPI-FSM in connected PCS)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_LPI_MODE_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_LPI_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable data inversion received from Deserializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . RX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_DATA_INV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_DATA_INV_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_RX_DATA_INV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable data inversion sent to Serializer
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . TX_DATA_INV_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_DATA_INV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_DATA_INV_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_TX_DATA_INV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Lane Reset
 *
 * \details 
 * 0: No reset
 * 1: Reset (not self-clearing)
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG . LANE_RST
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_MISC_CFG_LANE_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G OB ANEG Configuration
 *
 * \details
 * Configuration register for ANEG Output Buffer overwrite parameter. The
 * values are used during Backplane Ethernet Auto-Negotiation when the
 * output level of transmitter (OB output) have to be reduced.
 *
 * Register: \a HSIO:SERDES6G_DIG_CFG:SERDES6G_OB_ANEG_CFG
 */
#define VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x43)

/** 
 * \brief
 * ANEG overwrite value for SERDES6G_OB_CFG.post0
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG . AN_OB_POST0
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST0(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST0     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST0(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * ANEG overwrite value for SERDES6G_OB_CFG.post1
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG . AN_OB_POST1
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST1(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST1     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_POST1(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * ANEG overwrite value for SERDES6G_OB_CFG.prec
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG . AN_OB_PREC
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_PREC(x)  VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_PREC     VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_PREC(x)  VTSS_EXTRACT_BITFIELD(x,13,5)

/** 
 * \brief
 * ANEG overwrite value for SERDES6G_OB_CFG1.ob_ena_cas
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG . AN_OB_ENA_CAS
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_ENA_CAS(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_ENA_CAS     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_ENA_CAS(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * ANEG overwrite value for SERDES6G_OB_CFG1.ob_lev
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG . AN_OB_LEV
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_LEV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_LEV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_DIG_CFG_SERDES6G_OB_ANEG_CFG_AN_OB_LEV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a HSIO:SERDES6G_DIG_STATUS
 *
 * SERDES6G Digital Status Register
 */


/** 
 * \brief SERDES6G DFT Status
 *
 * \details
 * Status register of SERDES6G DFT functions
 *
 * Register: \a HSIO:SERDES6G_DIG_STATUS:SERDES6G_DFT_STATUS
 */
#define VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x44)

/** 
 * \brief
 * PRBS synchronization status
 *
 * \details 
 * 0: PRBS checker not synchronized
 * 1: PRBS checker synchronized
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . PRBS_SYNC_STAT
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PRBS_SYNC_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PRBS_SYNC_STAT  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PRBS_SYNC_STAT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * RC-PLL BIST not done flag
 *
 * \details 
 * 0: BIST done
 * 1: BIST not started or active
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . PLL_BIST_NOT_DONE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_NOT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_NOT_DONE  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_NOT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * RC-PLL BIST result
 *
 * \details 
 * 0: No error found
 * 1: Errors during BIST found
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . PLL_BIST_FAILED
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_FAILED  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * RC-PLL BIST timeout error flag
 *
 * \details 
 * 0: No timeout occured
 * 1: Timeout occured
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . PLL_BIST_TIMEOUT_ERR
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_PLL_BIST_TIMEOUT_ERR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * BIST activity
 *
 * \details 
 * 0: BIST inactive
 * 1: BIST active
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . BIST_ACTIVE
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ACTIVE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ACTIVE  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ACTIVE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * BIST sync result
 *
 * \details 
 * 0: Synchronization successful
 * 1: Synchronization on BIST data failed
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . BIST_NOSYNC
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_NOSYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_NOSYNC  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_NOSYNC(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST completion state (low-active)
 *
 * \details 
 * 0: BIST completed
 * 1: not completed
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . BIST_COMPLETE_N
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_COMPLETE_N(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_COMPLETE_N  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_COMPLETE_N(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST result
 *
 * \details 
 * 0: No error found
 * 1: Errors during BIST found
 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS . BIST_ERROR
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ERROR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ERROR  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_DFT_STATUS_BIST_ERROR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G Error Counter
 *
 * \details
 * Error counter for SERDES6G PRBS
 *
 * Register: \a HSIO:SERDES6G_DIG_STATUS:SERDES6G_ERR_CNT
 */
#define VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT  VTSS_IOREG(VTSS_TO_HSIO,0x45)

/** 
 * \brief
 * PRBS error counter
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT . PRBS_ERR_CNT
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT_PRBS_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT_PRBS_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_ERR_CNT_PRBS_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SERDES6G Misc Status
 *
 * \details
 * Status register for miscellaneous functions
 *
 * Register: \a HSIO:SERDES6G_DIG_STATUS:SERDES6G_MISC_STATUS
 */
#define VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_MISC_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x46)

/** 
 * \brief
 * Phase selection of DES in 100fx mode
 *
 * \details 
 * 0: CDR locked at bit 9
 * 1: CDR locked at bit 4

 *
 * Field: ::VTSS_HSIO_SERDES6G_DIG_STATUS_SERDES6G_MISC_STATUS . DES_100FX_PHASE_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_DIG_STATUS_SERDES6G_MISC_STATUS_DES_100FX_PHASE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_DIG_STATUS_SERDES6G_MISC_STATUS_DES_100FX_PHASE_SEL  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_DIG_STATUS_SERDES6G_MISC_STATUS_DES_100FX_PHASE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HSIO:SERDES6G_ANA_CFG
 *
 * SERDES6G Analog ConfigStatus Registers
 */


/** 
 * \brief SERDES6G Deserializer Cfg
 *
 * \details
 * Configuration register for SERDES6G deserializer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_DES_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x47)

/** 
 * \brief
 * Control of phase regulator logic (bit 3 selects input to integrator
 * block - 0: cp/md from DES, 1: cp/md from core)
 *
 * \details 
 * 0: Disabled
 * 1: Enabled with 99 ppm limit
 * 2: Enabled with 202 ppm limit
 * 3: Enabled with 485 ppm limit
 * 4: Enabled if corresponding PCS is in sync with 50 ppm limit
 * 5: Enabled if corresponding PCS is in sync with 99 ppm limit
 * 6: Enabled if corresponding PCS is in sync with 202 ppm limit
 * 7: Enabled if corresponding PCS is in sync with 485 ppm limit
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_PHS_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_PHS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Des phase control for 180 degrees deadlock block mode of operation
 *
 * \details 
 * 000: Depending on density of input pattern
 * 001: Active until PCS has synchronized
 * 010: Depending on density of input pattern until PCS has synchronized
 * 011: Never
 * 100: Always
 * 111: Debug feature: Add cp/md of DES and cp/md from core
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_MBTR_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_MBTR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * DES phase control, main cp/md select
 *
 * \details 
 * 00: Directly from DES
 * 01: Through hysteresis stage from DES
 * 10: From core
 * 11: Disabled
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: Divide by 2
 * 1: Divide by 4
 * 2: Divide by 8
 * 3: Divide by 16
 * 4: Divide by 32
 * 5: Divide by 64
 * 6: Divide by 128
 * 7: Divide by 256
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_BW_HYST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_HYST(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Swap hysteresis cp/md signals.
 *
 * \details 
 * 0: No swapping
 * 1: Swapping
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_SWAP_HYST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_HYST(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_HYST  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_HYST(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Bandwidth selection. Selects dividing factor for non-hysteresis CP/MD
 * outputs.
 *
 * \details 
 * 0: No division
 * 1: Divide by 2
 * 2: Divide by 4
 * 3: Divide by 8
 * 4: Divide by 16
 * 5: Divide by 32
 * 6: Divide by 64
 * 7: Divide by 128
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_BW_ANA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_BW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Swap non-hysteresis cp/md signals.
 *
 * \details 
 * 0: No swapping
 * 1: Swapping
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG . DES_SWAP_ANA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_ANA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_DES_CFG_DES_SWAP_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G IB Configuration register 0
 *
 * \details
 * Configuration settings 0
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x48)

/** 
 * \brief
 * Select location of offset correction inside equalizer
 *
 * \details 
 * 0: No offset correction
 * 1: First stage (preferred)
 * 2: Last stage
 * 3: First and last stage
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_SOFSI
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SOFSI(x)  VTSS_ENCODE_BITFIELD(x,29,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SOFSI     VTSS_ENCODE_BITMASK(29,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SOFSI(x)  VTSS_EXTRACT_BITFIELD(x,29,2)

/** 
 * \brief
 * Controls Bulk Voltage of High Speed Cells
 *
 * \details 
 * 0: Reserved
 * 1: Low (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_VBULK_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBULK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBULK_SEL  VTSS_BIT(28)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_VBULK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Resistance adjustment for termination and CML cell regulation.
 * This configuration defines an offset (2-complement) to the RCOMP value.
 * The effective value is limited between 0 to 15.
 *
 * \details 
 * 7: RCOMP+7
 * 1: RCOMP+1
 * 0: RCOMP
 * 15: RCOMP-1
 * 8: RCOMP -8
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_RTRM_ADJ
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_RTRM_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Current adjustment for CML cells
 *
 * \details 
 * 0: low current
 * 1: high current
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_ICML_ADJ
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ICML_ADJ(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ICML_ADJ     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ICML_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Select common mode termination voltage.

 *
 * \details 
 * 0: Open - recommended mission mode for DC-coupling
 * 1: VCM ref - recommended mission mode for AC-coupling
 * 2: VDD - used to increase amplitude in certain DC-coupled modes
 * 3: capacitance only - Reserved for debug test purpose
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_TERM_MODE_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_TERM_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_TERM_MODE_SEL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_TERM_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Select signal detect clock: Frequency = 125 MHz / 2**n
 * Set to 0 for ATE testing (reduces test-time)
 * Set to 7 for optimized performance in mission mode 
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_SIG_DET_CLK_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/** 
 * \brief
 * Selects pattern detection for regulation of high-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified basic and critical pattern are
 * detected.
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_REG_PAT_SEL_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_HP(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_HP     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_HP(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Selects pattern detection for regulation of mid-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified basic and critical pattern are
 * detected.
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_REG_PAT_SEL_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_MID(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_MID     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_MID(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Selects pattern detection for regulation of low-pass-gain
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified basic and critical pattern are
 * detected.
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_REG_PAT_SEL_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_LP(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_LP     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_LP(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Selects pattern detection for regulation of offset
 *
 * \details 
 * 0: Only regulation assessment if basic pattern is detected
 * 1: Regulation assessment if basic and simplified pattern are detected
 * 2: Regulation assessment if basic and critical pattern are detected
 * 3: Regulation assessment if simplified basic and critical pattern are
 * detected.
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_REG_PAT_SEL_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET     VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_PAT_SEL_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * Enable analog test output.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_ANA_TEST_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ANA_TEST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ANA_TEST_ENA  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_ANA_TEST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable signal detection.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_SIG_DET_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SIG_DET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selection between constant current and constant resistor mode for CML
 * cells
 *
 * \details 
 * 0: Constant resistor mode
 * 1: Constant current mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_CONCUR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CONCUR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable calibration
 * IB calibration should be started after SERDES6G_COMMON_CFG.ENA_LANE was
 * set to '1'.
 * Calibration procedure takes up to 1sec depending on configuration of
 * SERDES6G_IB_CFG0.IB_SIG_DET_CLK_SEL.
 * Max.- calibration time is for SERDES6G_IB_CFG0.IB_SIG_DET_CLK_SEL set to
 * 7.
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_CAL_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable SAMpling stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_SAM_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_SAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable EQualiZation-Stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_EQZ_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_EQZ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable equalizer REGulation stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG . IB_REG_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG_IB_REG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G IB Configuration register 1
 *
 * \details
 * Configuration settings 1
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG1
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x49)

/** 
 * \brief
 * Selects threshold voltage for ac-jtag. Voltage = (n + 1) * 20 mV.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_TJTAG
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TJTAG(x)  VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TJTAG     VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TJTAG(x)  VTSS_EXTRACT_BITFIELD(x,17,5)

/** 
 * \brief
 * Selects threshold voltage for signal detect. Voltage = (n + 1) * 20 mV.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_TSDET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(x)  VTSS_ENCODE_BITFIELD(x,12,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET     VTSS_ENCODE_BITMASK(12,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_TSDET(x)  VTSS_EXTRACT_BITFIELD(x,12,5)

/** 
 * \brief
 * Selects number of calibration cycles for equalizer, sampling stage,
 * signal-detect and AC-JTAG comparator, BIAS.
 * 0: no calibration --> neutral values are used.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_SCALY
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_SCALY(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_SCALY     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_SCALY(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Selects doubled filtering of high-pass-gain regulation or set it to hold
 * if ib_frc_hp = 1
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FILT_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_HP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Selects doubled filtering of mid-pass-gain regulation or set it to hold
 * if ib_frc_mid = 1
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FILT_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_MID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Selects doubled filtering of low-pass-gain regulation or set it to hold
 * if ib_frc_lp = 1
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FILT_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_LP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selects doubled filtering of offset regulation or set it to hold if
 * ib_frc_offset = 1
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FILT_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FILT_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Selects manual control for high-pass-gain regulation if enabled
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FRC_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_HP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Selects manual control for mid-pass-gain regulaltion if enabled
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FRC_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_MID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Selects manual control for low-pass-gain regulation if enabled
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FRC_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_LP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Selects manual control for offset regulation if enabled
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1 . IB_FRC_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG1_IB_FRC_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G IB Configuration register 2
 *
 * \details
 * Configuration settings 2
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG2
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2  VTSS_IOREG(VTSS_TO_HSIO,0x4a)

/** 
 * \brief
 * Selects maximum threshold influence for threshold calibration of vscope
 * samplers. 
 *
 * \details 
 * 0: 40mV
 * 1: 80mV 
 * ...
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_TINFV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TINFV(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TINFV     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TINFV(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Selects maximum offset influence for offset regulation.
 *
 * \details 
 * 0: 10mV
 * 1: 20mV
 * ...
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_OINFI
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFI(x)  VTSS_ENCODE_BITFIELD(x,22,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFI     VTSS_ENCODE_BITMASK(22,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFI(x)  VTSS_EXTRACT_BITFIELD(x,22,5)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_TAUX
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TAUX(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TAUX     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TAUX(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/** 
 * \brief
 * Selects maximum offset influence for offset calibration of main
 * samplers.
 *
 * \details 
 * 0: 40mV
 * 1: 80mV
 * ...
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_OINFS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFS(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFS     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OINFS(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/** 
 * \brief
 * Selects offset voltage for main sampler calibration. 
 *
 * \details 
 * 0: -70mV
 *  ...
 * 31: -0mV
 * 32: +0mV
 *  ...
 * 63: 70mV
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_OCALS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OCALS(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OCALS     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_OCALS(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Selects threshold voltage for VScope sampler calibration.
 *
 * \details 
 * 0: 10mV
 * 1: 20mV
 * ...
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_TCALV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TCALV(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TCALV     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_TCALV(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Tunes common mode voltage to adapt to max. voltage of input signal.
 *
 * \details 
 * 0: 320mVppd
 * 1: 480mVppd
 * 2: 640mVppd (recommended for mission mode)
 * 3: 800mVppd
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_UMAX
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UMAX(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UMAX     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UMAX(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * 0dB regulation voltage for high-speed-cells.

 *
 * \details 
 * 0: 160mV
 * 1: 180mV
 * 2: 200mV
 * 3: 220mV
 * 4: 240mV (recommended for mission mode)
 * 5: 260mV
 * 6: 280mV
 * 7: 300mV
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2 . IB_UREG
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG2_IB_UREG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SERDES6G IB Configuration register 3
 *
 * \details
 * Configuration settings 3
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG3
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3  VTSS_IOREG(VTSS_TO_HSIO,0x4b)

/** 
 * \brief
 * Init force value for high-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3 . IB_INI_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_HP(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Init force value for mid-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3 . IB_INI_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_MID(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Init force value for low-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3 . IB_INI_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_LP(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Init force value for offset gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3 . IB_INI_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG3_IB_INI_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 4
 *
 * \details
 * Configuration settings 4
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG4
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4  VTSS_IOREG(VTSS_TO_HSIO,0x4c)

/** 
 * \brief
 * Max value for high-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4 . IB_MAX_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_HP(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_HP     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_HP(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Max value for mid-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4 . IB_MAX_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_MID(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_MID     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_MID(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Max value for low-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4 . IB_MAX_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_LP(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_LP     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_LP(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Max value for offset gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4 . IB_MAX_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG4_IB_MAX_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G IB Configuration register 5
 *
 * \details
 * Configuration settings 5
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_IB_CFG5
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5  VTSS_IOREG(VTSS_TO_HSIO,0x4d)

/** 
 * \brief
 * Min value for high-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5 . IB_MIN_HP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_HP(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_HP     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_HP(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Min value for mid-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5 . IB_MIN_MID
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_MID(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_MID     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_MID(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Min value for low-pass gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5 . IB_MIN_LP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_LP(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_LP     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_LP(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Min value for offset gain regulation
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5 . IB_MIN_OFFSET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_OFFSET     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_IB_CFG5_IB_MIN_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G Output Buffer Cfg 0
 *
 * \details
 * Configuration register 0 for SERDES6G output buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_OB_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x4e)

/** 
 * \brief
 * PCIe support
 *
 * \details 
 * 1: idle - force to 0V differential
 * 0: Normal mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_IDLE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE  VTSS_BIT(31)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_IDLE(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Output buffer supply voltage
 *
 * \details 
 * 1: Set to nominal 1V
 * 0: Set to higher voltage
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_ENA1V_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE  VTSS_BIT(30)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_ENA1V_MODE(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Polarity of output signal
 *
 * \details 
 * 0: Normal
 * 1: Inverted
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL  VTSS_BIT(29)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POL(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Coefficients for 1st Post Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POST0
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST0(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * Coefficients for Pre Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_PREC
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_PREC(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * Resistor adjust mux, driving strength selection of mux
 *
 * \details 
 * 1: Reduced
 * 0: Normal
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_R_ADJ_MUX
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_MUX(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_MUX  VTSS_BIT(17)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_MUX(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Resistor adjust predriver, driving strength selection of predriver
 *
 * \details 
 * 1: Reduced
 * 0: Normal
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_R_ADJ_PDR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_PDR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_PDR  VTSS_BIT(16)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_ADJ_PDR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Coefficients for 2nd Post Cursor (MSB is sign)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_POST1
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_POST1(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/** 
 * \brief
 * Reduce the impedance by 3%
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_R_COR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_COR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_COR  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_R_COR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Select resistor control
 *
 * \details 
 * 0: Automatic mode
 * 1: Manual mode - use ob_r_adj_mux and ob_r_adj_pdr for driving strength
 * control
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_SEL_RCTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SEL_RCTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SEL_RCTRL  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SEL_RCTRL(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Half the predriver speed, use for slew rate control
 *
 * \details 
 * 0: Disable - slew rate < 60 ps
 * 1: Enable - slew rate > 60 ps
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_SR_H
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR_H(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Driver speed, fine adjustment of slew rate 30-60ps (if OB_SR_H = 0),
 * 60-140ps (if OB_SR_H = 1).
 * 
 * LSB is not used.

 *
 * \details 
 * 000x: ~30ps/60ps
 * ...
 * 111x: ~60ps/140ps
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_SR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_SR(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * Resistance adjustment for termination and CML cell regulation.
 * This configuration defines an offset (2-complement) to the RCOMP value.
 * The effective value is limited between 0 to 15.
 *
 * \details 
 * 7: RCOMP+7
 * 1: RCOMP+1
 * 0: RCOMP
 * 15: RCOMP-1
 * 8: RCOMP -8
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG . OB_RESISTOR_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG_OB_RESISTOR_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SERDES6G Output Buffer Cfg1
 *
 * \details
 * Configuration register 1 for SERDES6G output buffer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_OB_CFG1
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1  VTSS_IOREG(VTSS_TO_HSIO,0x4f)

/** 
 * \brief
 * Output skew, used for skew adjustment in SGMII mode - 1bit-hot-coded
 *
 * \details 
 * 000: Non-SGMII/1Gbps modes
 * 001: Lowest skew
 * 010: SGMII/1Gbps mode
 * 100: Highest skew
 * All other settings: Reserved
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_ENA_CAS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_ENA_CAS(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Level of output amplitude
 * for 1V mode: max: ~48
 * for 1.2V mode: max: 63
 *
 * \details 
 * 0: lowest level
 * 63: highest level
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1 . OB_LEV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_OB_CFG1_OB_LEV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G Serializer Cfg
 *
 * \details
 * Configuration register for SERDES6G serializer
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_SER_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x50)

/** 
 * \brief
 * Enable the fourth cml output Q3 for POST1 input of OB8G
 *
 * \details 
 * 0: Disable 4th output
 * 1: Enable 4th output
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_4TAP_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_4TAP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_4TAP_ENA  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_4TAP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Select source of cp/md signals
 *
 * \details 
 * 0: Phase alignment block
 * 1: Core
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_CPMD_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_CPMD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_CPMD_SEL  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_CPMD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Swap cp/md signals
 *
 * \details 
 * 0: Disable swapping
 * 1: Enable swapping
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_SWAP_CPMD
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_SWAP_CPMD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_SWAP_CPMD  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_SWAP_CPMD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Select reference clock source for phase alignment

 *
 * \details 
 * 00: RXCLKP (for facility loop mode)
 * 01: RefClk15MHz (for XAUI/RXAUI)
 * 10: RXCLKN (debug)
 * 11: ext. ALICLK (debug)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ALISEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ALISEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Enable hysteresis for phase alignment
 *
 * \details 
 * 0: Disable hysteresis
 * 1: Enable hysteresis
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENHYS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENHYS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENHYS  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENHYS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Use wider window for phase alignment
 *
 * \details 
 * 0: Use small-window
 * 1: Use wide window
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_BIG_WIN
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_BIG_WIN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_BIG_WIN  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_BIG_WIN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable window for phase alignment
 *
 * \details 
 * 0: Disable window
 * 1: Enable window
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_EN_WIN
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_EN_WIN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable phase alignment
 *
 * \details 
 * 0: Disable phase alignment
 * 1: Enable phase alignment (required for MLD-modes - XAUI/RXAUI - and
 * facility loop mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG . SER_ENALI
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_SER_CFG_SER_ENALI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G Common Cfg
 *
 * \details
 * Configuration register for common SERDES6G functions
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_COMMON_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x51)

/** 
 * \brief
 * System reset (low active)
 * 
 * Should be set after SERDES6G_COMMON_CFG.ENA_LANE was set to 1.
 *
 * \details 
 * 0: Apply reset (not self-clearing)
 * 1: Reset released (mission mode)
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . SYS_RST
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST  VTSS_BIT(16)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SYS_RST(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Enable auto-squelching for sync. ethernet clock output: when set the
 * clock output will stop toggling (keep its last value constantly) when
 * PCS looses link synchrony.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . SE_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA  VTSS_BIT(15)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_SE_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable lane
 *
 * \details 
 * 0: Disable lane
 * 1: Enable line
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_LANE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE  VTSS_BIT(14)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_LANE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Power-down RX-path
 *
 * \details 
 * 0: Normal mode
 * 1: Power down mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . PWD_RX
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX  VTSS_BIT(13)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_RX(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Power-down TX-path
 *
 * \details 
 * 0: Normal mode
 * 1: Power down mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . PWD_TX
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX  VTSS_BIT(12)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_PWD_TX(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Hidden spare bits (not connected internally yet)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . LANE_CTRL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_LANE_CTRL(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_LANE_CTRL     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_LANE_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Enable direct line
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_DIRECT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_DIRECT  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable equipment loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_ELOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ELOOP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable facility loop
 * 
 * SERDES6G_SER_CFG.SER_ENALI must be set to 1
 * SERDES6G_SER_CFG.SER_ALISEL must be set to 0
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_FLOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_FLOOP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable input loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_ILOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_ILOOP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable pad loop
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . ENA_PLOOP
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_PLOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_PLOOP  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_ENA_PLOOP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable half rate
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE

 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . HRATE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_HRATE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable quarter rate
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE

 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . QRATE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_QRATE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Interface mode
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE

 *
 * \details 
 * 0: 8-bit mode
 * 1: 10-bit mode
 * 2: 16-bit mode
 * 3: 20-bit mode
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG . IF_MODE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_COMMON_CFG_IF_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SERDES6G Pll Cfg
 *
 * \details
 * Configuration register for SERDES6G RCPLL
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_PLL_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x52)

/** 
 * \brief
 * Enable offset compensation B1: Feedback path; B0: VCO.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ENA_OFFS
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_OFFS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_OFFS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_OFFS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Enable div4 mode
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_DIV4
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4  VTSS_BIT(15)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_DIV4(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable rotation
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ENA_ROT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT  VTSS_BIT(14)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ENA_ROT(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Control data for PLL-FSM
 * 
 * Encoding below are only examples for some modes.
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE

 *
 * \details 
 * 60: SGMII/1G-Modes
 * 48: XAUI/2.5Gbps
 * 96: RXAUI
 * 120: QSGMII
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_CTRL_DATA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

/** 
 * \brief
 * Enable FSM
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable FSM forcing
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_FORCE_SET_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_FORCE_SET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_FORCE_SET_ENA  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_FORCE_SET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable FSM recalibration
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_FSM_OOR_RECAL_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_FSM_OOR_RECAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Select RB data
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_RB_DATA_SEL
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_RB_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_RB_DATA_SEL  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_RB_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Select rotation direction
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ROT_DIR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_DIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Select rotation frequency
 * 
 * Baudrate configuration is controlled by:
 * SERDES6G_COMMON_CFG.PLL_DIV4
 * SERDES6G_COMMON_CFG.PLL_ROT_FRQ
 * SERDES6G_COMMON_CFG.PLL_ROT_DIR
 * SERDES6G_COMMON_CFG.PLL_ENA_ROT
 * SERDES6G_COMMON_CFG.IF_MODE
 * SERDES6G_COMMON_CFG.HRATE
 * SERDES6G_COMMON_CFG.QRATE
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG . PLL_ROT_FRQ
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_PLL_CFG_PLL_ROT_FRQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G ACJTAG Cfg
 *
 * \details
 * Configuration register for (AC)JTAG debug capability
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_ACJTAG_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x53)

/** 
 * \brief
 * ACJTAG init data for n leg
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_DATA_N
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_N(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_N  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_N(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * ACJTAG init data for p leg
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_DATA_P
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_P(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_P  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_DATA_P(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * ACJTAG clock line
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_INIT_CLK
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_CLK  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_INIT_CLK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * JTAG direct output (directly driven)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . OB_DIRECT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_OB_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_OB_DIRECT  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_OB_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * ACJTAG enable (ac_mode)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . ACJTAG_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_ENA  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_ACJTAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable JTAG control via CSR
 *
 * \details 
 * 0: External controlled
 * 1: CSR controlled
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG . JTAG_CTRL_ENA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_JTAG_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_JTAG_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_ACJTAG_CFG_JTAG_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G GP CFG
 *
 * \details
 * General purpose register A
 *
 * Register: \a HSIO:SERDES6G_ANA_CFG:SERDES6G_GP_CFG
 */
#define VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x54)

/** 
 * \brief
 * To be defined
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG . GP_MSB
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_MSB(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_MSB     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_MSB(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Bit 9: SNFBC Select negative feedback center - enable for hysteresis
 * suppression in main sampler FFs 
 * Bit 8: SNFBV Select negative feedback Vscope - enable for hysteresis
 * suppression in vscope sampler FFs 
 * Bit 1: ERLS (used for debug only, allows for manual stepping through
 * calibration procedure)
 * Bit 0: CRLS (used for debug only, allows for manual stepping through
 * calibration procedure)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG . GP_LSB
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HSIO_SERDES6G_ANA_CFG_SERDES6G_GP_CFG_GP_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HSIO:SERDES6G_ANA_STATUS
 *
 * SERDES6G Analog Status Registers
 */


/** 
 * \brief SERDES6G IB Status register 0
 *
 * \details
 * Status register for Signal Detect
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_IB_STATUS0
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0  VTSS_IOREG(VTSS_TO_HSIO,0x55)

/** 
 * \brief
 * Signals mission mode after calibration was done.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_CAL_DONE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_CAL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_CAL_DONE  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_CAL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Flag high-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_HP_GAIN_ACT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_HP_GAIN_ACT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_HP_GAIN_ACT  VTSS_BIT(7)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_HP_GAIN_ACT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Flag mid-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_MID_GAIN_ACT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_MID_GAIN_ACT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_MID_GAIN_ACT  VTSS_BIT(6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_MID_GAIN_ACT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Flag low-pass-gain regulation activity. Caution: currently this signal
 * is generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_LP_GAIN_ACT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_LP_GAIN_ACT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_LP_GAIN_ACT  VTSS_BIT(5)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_LP_GAIN_ACT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Flag offset regulation activity. Caution: currently this signal is
 * generated with a clock of datarate/16 and NOT captured (sticky).
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_ACT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ACT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ACT  VTSS_BIT(4)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ACT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Valid average data of calibration process at ib_offset_stat available.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_VLD
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_VLD  VTSS_BIT(3)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_VLD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Overflow error during calibration process. Value at ib_offset_stat not
 * valid.
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSET_ERR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ERR  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSET_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Detection of offset direction in selected (ib_offsx) sampling channels
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_OFFSDIR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSDIR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSDIR  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_OFFSDIR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0 . IB_SIG_DET
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_SIG_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_SIG_DET  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS0_IB_SIG_DET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G IB Status register 1
 *
 * \details
 * Regulation stage status register
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_IB_STATUS1
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1  VTSS_IOREG(VTSS_TO_HSIO,0x56)

/** 
 * \brief
 * Current high-pass-gain regulation value
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1 . IB_HP_GAIN_STAT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_HP_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,18,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_HP_GAIN_STAT     VTSS_ENCODE_BITMASK(18,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_HP_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,18,6)

/** 
 * \brief
 * Current mid-pass-gain regulation value
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1 . IB_MID_GAIN_STAT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_MID_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_MID_GAIN_STAT     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_MID_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Current low-pass-gain regulation value
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1 . IB_LP_GAIN_STAT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_LP_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_LP_GAIN_STAT     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_LP_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Current offset regulation value
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1 . IB_OFFSET_STAT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_OFFSET_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_OFFSET_STAT     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_IB_STATUS1_IB_OFFSET_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SERDES6G ACJTAG Status
 *
 * \details
 * Status register of (AC)JTAG debug capability
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_ACJTAG_STATUS
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x57)

/** 
 * \brief
 * ACJTAG captured data for n leg
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . ACJTAG_CAPT_DATA_N
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_N(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_N  VTSS_BIT(2)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_N(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * ACJTAG captured data for p leg
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . ACJTAG_CAPT_DATA_P
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_P(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_P  VTSS_BIT(1)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_ACJTAG_CAPT_DATA_P(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * JTAG direct input (directly driven)
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS . IB_DIRECT
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_IB_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_IB_DIRECT  VTSS_BIT(0)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_ACJTAG_STATUS_IB_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SERDES6G Pll Status
 *
 * \details
 * Status register of SERDES6G RCPLL
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_PLL_STATUS
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS  VTSS_IOREG(VTSS_TO_HSIO,0x58)

/** 
 * \brief
 * Calibration status
 *
 * \details 
 * 0: Calibration not started or ongoing
 * 1: Calibration finished
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_CAL_NOT_DONE
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE  VTSS_BIT(10)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_NOT_DONE(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Calibration error
 *
 * \details 
 * 0: No error during calibration
 * 1: Errors occured during calibration
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_CAL_ERR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR  VTSS_BIT(9)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_CAL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Out of range error
 *
 * \details 
 * 0: No out of range condition detected
 * 1: Out of range condition since last calibration detected
 *
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_OUT_OF_RANGE_ERR
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR  VTSS_BIT(8)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_OUT_OF_RANGE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * PLL read-back data, depending on "pll_rb_data_sel" either the calibrated
 * setting or the measured period
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS . PLL_RB_DATA
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_PLL_STATUS_PLL_RB_DATA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief SERDES6G REVID
 *
 * \details
 * Revision ID register
 *
 * Register: \a HSIO:SERDES6G_ANA_STATUS:SERDES6G_REVID
 */
#define VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID  VTSS_IOREG(VTSS_TO_HSIO,0x59)

/** 
 * \brief
 * Serdes revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . SERDES_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SERDES_REV(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SERDES_REV     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SERDES_REV(x)  VTSS_EXTRACT_BITFIELD(x,26,6)

/** 
 * \brief
 * RCPLL revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . RCPLL_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_RCPLL_REV(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_RCPLL_REV     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_RCPLL_REV(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * SER revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . SER_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SER_REV(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SER_REV     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_SER_REV(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * DES revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . DES_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_DES_REV(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_DES_REV     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_DES_REV(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * OB revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . OB_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_OB_REV(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_OB_REV     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_OB_REV(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * IB revision
 *
 * \details 
 * Field: ::VTSS_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID . IB_REV
 */
#define  VTSS_F_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_IB_REV(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_IB_REV     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HSIO_SERDES6G_ANA_STATUS_SERDES6G_REVID_IB_REV(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a HSIO:MCB_SERDES6G_CFG
 *
 * MCB SERDES6G Configuration Register
 */


/** 
 * \brief MCB SERDES6G Address Cfg
 *
 * \details
 * Configuration of SERDES6G MCB Slaves to be accessed
 *
 * Register: \a HSIO:MCB_SERDES6G_CFG:MCB_SERDES6G_ADDR_CFG
 */
#define VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG  VTSS_IOREG(VTSS_TO_HSIO,0x5a)

/** 
 * \brief
 * Initiate a write access to marked SERDES6G Slaves
 *
 * \details 
 * 0: No write operation pending
 * 1: Initiate write to slaves (kept 1 until write operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_WR_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT  VTSS_BIT(31)
#define  VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_WR_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Initiate a read access to marked SERDES6G Slaves
 *
 * \details 
 * 0: No read operation pending (read op finished after bit has been set)
 * 1: Initiate a read access (kept 1 until read operation has finished)
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_RD_ONE_SHOT
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT  VTSS_BIT(30)
#define  VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_RD_ONE_SHOT(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Activation vector for SERDES6G-Slaves, one-hot coded, each bit is
 * related to one macro, e.g. bit 0 enables/disables access to macro no. 0.
 *
 * \details 
 * 0: Disable macro access via MCB
 * 1: Enable macro access via MCB
 *
 * Field: ::VTSS_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG . SERDES6G_ADDR
 */
#define  VTSS_F_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_HSIO_MCB_SERDES6G_CFG_MCB_SERDES6G_ADDR_CFG_SERDES6G_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,25)

/**
 * Register Group: \a HSIO:HW_CFGSTAT
 *
 * General high-speed IO configuration and status
 */


/** 
 * \brief Various configration
 *
 * \details
 * Register: \a HSIO:HW_CFGSTAT:HW_CFG
 */
#define VTSS_HSIO_HW_CFGSTAT_HW_CFG          VTSS_IOREG(VTSS_TO_HSIO,0x5b)

/** 
 * \brief
 * Set to enable drive of analog test-output pin.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . ANAOUT_ENA
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_ANAOUT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_ANAOUT_ENA  VTSS_BIT(20)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_ANAOUT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * See DEVCPU_GCB::DEV10G_0_MODE for description.
 *
 * \details 
 * 0: DEV10G_3 XFI-mode via SerDes10G_3.
 * 1: DEV10G_3 XAUI-mode via SerDes6G_12, SerDes6G_13, SerDes6G_14, and
 * SerDes6G_15.
 * 2: DEV10G_3 RXAUI-mode via SerDes6G_12 and SerDes6G_14.
 * 3: DEV2G5_28 via SerDes10G_3.
 *
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . DEV10G_3_MODE
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_3_MODE(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_3_MODE     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_3_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * See DEVCPU_GCB::DEV10G_0_MODE for description.
 *
 * \details 
 * 0: DEV10G_2 XFI-mode via SerDes10G_2.
 * 1: DEV10G_2 XAUI-mode via SerDes6G_8, SerDes6G_9, SerDes6G_10, and
 * SerDes6G_11.
 * 2: DEV10G_2 RXAUI-mode via SerDes6G_8 and SerDes6G_10.
 * 3: DEV2G5_27 via SerDes10G_2.
 *
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . DEV10G_2_MODE
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_2_MODE(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_2_MODE     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_2_MODE(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * See DEVCPU_GCB::DEV10G_0_MODE for description.
 *
 * \details 
 * 0: DEV10G_1 XFI-mode via SerDes10G_1.
 * 1: DEV10G_1 XAUI-mode via SerDes6G_20, SerDes6G_21, SerDes6G_22, and
 * SerDes6G_23.
 * 2: DEV10G_1 RXAUI-mode via SerDes6G_20 and SerDes6G_22.
 * 3: DEV2G5_26 via SerDes10G_1.
 *
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . DEV10G_1_MODE
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_1_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_1_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_1_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Configure mode of DEV10G and hookup of SerDes10G blocks. The device has
 * dedicated DEV10G for 10 Gbit/sec speed, and DEV2G5 for 2.5 Gbit/sec and
 * lower speeds. The DEV10G and corresponding DEV2G5 cannot be active at
 * the same time.
 *
 * \details 
 * 0: DEV10G_0 XFI-mode via SerDes10G_0.
 * 1: DEV10G_0 XAUI-mode via SerDes6G_16, SerDes6G_17, SerDes6G_18, and
 * SerDes6G_19.
 * 2: DEV10G_0 RXAUI-mode via SerDes6G_16 and SerDes6G_18.
 * 3: DEV2G5_25 via SerDes10G_0.
 *
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . DEV10G_0_MODE
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_0_MODE(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_0_MODE     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_DEV10G_0_MODE(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Set bit 0 to enable QSGMII mode for devices DEV1G_0, DEV1G_1, DEV1G_2,
 * and DEV1G_3 via SerDes6G_4.
 * Set bit 1 to enable QSGMII mode for devices DEV1G_4, DEV1G_5, DEV1G_6,
 * and DEV1G_7 via SerDes6G_5.
 * Set bit 2 to enable QSGMII mode for devices DEV2G5_0, DEV2G5_1,
 * DEV2G5_2, and DEV2G5_3 via SerDes6G_6.
 * Set bit 3 to enable QSGMII mode for devices DEV2G5_4, DEV2G5_5,
 * DEV2G5_6, and DEV2G5_7 via SerDes6G_7.
 * Set bit 4 to enable QSGMII mode for devices DEV2G5_8, DEV2G5_9,
 * DEV2G5_10, and DEV2G5_11 via SerDes6G_8.
 * Set bit 5 to enable QSGMII mode for devices DEV2G5_12, DEV2G5_13,
 * DEV2G5_14, and DEV2G5_15 via SerDes6G_9.
 * Set bit 6 to enable QSGMII mode for devices DEV2G5_16, DEV2G5_17,
 * DEV2G5_18, and DEV2G5_19 via SerDes6G_10.
 * Set bit 7 to enable QSGMII mode for devices DEV2G5_20, DEV2G5_21,
 * DEV2G5_22, and DEV2G5_23 via SerDes6G_11.
 * Set bit 8 to enable QSGMII mode for devices DEV1G_8, DEV1G_9, DEV1G_10,
 * and DEV1G_11 via SerDes6G_12.
 * Set bit 9 to enable QSGMII mode for devices DEV1G_12, DEV1G_13,
 * DEV1G_14, and DEV1G_15 via SerDes6G_13.
 * Set bit 10 to enable QSGMII mode for devices DEV1G_16, DEV1G_17,
 * DEV1G_18, and DEV1G_19 via SerDes6G_14.
 * Set bit 11 to enable QSGMII mode for devices DEV1G_20, DEV1G_21,
 * DEV1G_22, and DEV1G_23 via SerDes6G_15.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_CFG . QSGMII_ENA
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_CFG_QSGMII_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Additional configuration for QSGMII channels
 *
 * \details
 * Register: \a HSIO:HW_CFGSTAT:HW_QSGMII_CFG
 */
#define VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_CFG   VTSS_IOREG(VTSS_TO_HSIO,0x5c)

/** 
 * \brief
 * Set to disable hysteresis of receive synchronization state machine. This
 * setting applies to all QSGMII channels.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_CFG . SHYST_DIS
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_SHYST_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_SHYST_DIS  VTSS_BIT(14)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_SHYST_DIS(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Set to enable 8b10b receive error propagation; 8b10b error code-groups
 * are replaced by K70.7 error symbols. This setting applies to all QSGMII
 * channels.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_CFG . E_DET_ENA
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_E_DET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_E_DET_ENA  VTSS_BIT(13)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_E_DET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Set to transmit I1 during idle sequencing only. This setting applies to
 * all QSGMII channels.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_CFG . USE_I1_ENA
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_USE_I1_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_USE_I1_ENA  VTSS_BIT(12)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_USE_I1_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Set to flip QSGMII lanes: Lane 0 is interchanged with 3, and 1 is
 * interchanged with 2 for both receie and transmit directions. Each bit in
 * this field correspond to a QSGMII channel, bit 0 configures QSGMII#0,
 * bit 1 configures QSGMII#1, etc.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_CFG . FLIP_LANES
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_FLIP_LANES(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_FLIP_LANES     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_CFG_FLIP_LANES(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Additional status from QSGMII channels
 *
 * \details
 * Register: \a HSIO:HW_CFGSTAT:HW_QSGMII_STAT
 *
 * @param ri Register: HW_QSGMII_STAT (??), 0-11
 */
#define VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_STAT(ri)  VTSS_IOREG(VTSS_TO_HSIO,0x5d + (ri))

/** 
 * \brief
 * Variable delay in QSGMII ingress path provided in steps of 200ps, values
 * 0 though 39 is possible allowing a span from 0ns to 7.8ns. Each
 * replication of this register correspond to a QSGMII channel, replication
 * 0 is from QSGMII#0, replication 1 is from QSGMII#1, etc.
 * The value for a QSGMII channel is valid when it has synchronized to an
 * incomming QSGMII signal, and will remain constant while the channel
 * stays in sync.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_STAT . DELAY_VAR_X200PS
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_DELAY_VAR_X200PS(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_DELAY_VAR_X200PS     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_DELAY_VAR_X200PS(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * Set when QSGMII channel has successfully synchronized on K28.1
 * code-group, this field is only valid when
 * DEVCPU_GCB::HW_QSGMII_CFG.SHYST_DIS is 0.
 *
 * \details 
 * Field: ::VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_STAT . SYNC
 */
#define  VTSS_F_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_SYNC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_SYNC  VTSS_BIT(0)
#define  VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_JAGUAR2C_REGS_HSIO_H_ */
