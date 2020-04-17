// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_HOST_PLL5G_H_
#define _VTSS_MALIBU_REGS_HOST_PLL5G_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a HOST_PLL5G
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PLL5G:H_PLL5G
 *
 * H_PLL5G Configuration Registers
 */


/** 
 * \brief H_PLL5G Configuration 0A
 *
 * \details
 * Configuration register 0A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG0A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A  VTSS_IOREG(0x1e, 0, 0x8100)

/** 
 * \brief
 * setting for core clock divider 0:625MHz, 1:312.5MHz, 2:500MHz,
 * 3:277.77MHz, 4:500MHz, 5:250MHz, 6:416.66MHz, 7:227.27MHz, 8:416.66MHz,
 * 9:208.33MHz, 10:357.14MHz, 11:192.3MHz, 12:357.14MHz, 13:178.57MHz,
 * 14:312.5MHz, 15:166.66,MHz, 17:156,25MHz
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . CORE_CLK_DIV
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CORE_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CORE_CLK_DIV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CORE_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

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
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . CPU_CLK_DIV
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CPU_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CPU_CLK_DIV     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_CPU_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * enable BIAS circuitry incl. Bandgap, voltage regulators, etc.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . ENA_BIAS
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_ENA_BIAS  VTSS_BIT(12)

/** 
 * \brief
 * enable BIAS for LCPLL VCO output buffer
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . ENA_VCO_BUF
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_ENA_VCO_BUF  VTSS_BIT(13)

/** 
 * \brief
 * enable current mode chargepump, normal mode
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . ENA_CP1
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_ENA_CP1  VTSS_BIT(14)

/** 
 * \brief
 * enable fine VCO operating point regulator
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A . ENA_VCO_CONTRH
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0A_ENA_VCO_CONTRH  VTSS_BIT(15)


/** 
 * \brief H_PLL5G Configuration 0B
 *
 * \details
 * Configuration register 0B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG0B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B  VTSS_IOREG(0x1e, 0, 0x8101)

/** 
 * \brief
 * setting for chargepump current 0: lowest current, 3: highest current
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . SELCPI
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELCPI(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELCPI     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELCPI(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * setting for filter resistor value 0: biggest resistance, 31: lowest
 * resistance
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . LOOP_BW_RES
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_LOOP_BW_RES(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_LOOP_BW_RES     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_LOOP_BW_RES(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * fine tune of bandgap voltage distribution 0: lowest voltage, 15: highest
 * voltage
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . SELBGV820
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELBGV820(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELBGV820     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_SELBGV820(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * enable fine locking, last stage in startup locking sequence
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . ENA_LOCK_FINE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_ENA_LOCK_FINE  VTSS_BIT(11)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . DIV4
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_DIV4  VTSS_BIT(12)

/** 
 * \brief
 * RCPLL enable BIAS for clocktree buffer (active low) 0: enable BIAS, 1:
 * disable BIAS
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . ENA_CLKTREE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_ENA_CLKTREE  VTSS_BIT(13)

/** 
 * \brief
 * RCPLL Global enable for serdes lane.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . ENA_LANE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_ENA_LANE  VTSS_BIT(14)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B . ENA_ROT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG0B_ENA_ROT  VTSS_BIT(15)


/** 
 * \brief H_PLL5G Configuration 1A
 *
 * \details
 * Configuration register 1A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG1A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A  VTSS_IOREG(0x1e, 0, 0x8102)

/** 
 * \brief
 * RCPLL When set to '1' the value at sx_pll_fsm_ctrl_data_I is not taken
 * as reference value for the FSM, but is directly apllied to the PLL as
 * frequency range setting.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . FORCE_SET_ENA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_FORCE_SET_ENA  VTSS_BIT(0)

/** 
 * \brief
 * RCPLL Enable for half rate mode
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . HALF_RATE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_HALF_RATE  VTSS_BIT(1)

/** 
 * \brief
 * RCPLL Enable recalibration of PLL when out of range is detected
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . OUT_OF_RANGE_RECAL_ENA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_OUT_OF_RANGE_RECAL_ENA  VTSS_BIT(2)

/** 
 * \brief
 * RCPLL Power down for the RX-path
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . PWD_RX
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_PWD_RX  VTSS_BIT(3)

/** 
 * \brief
 * RCPLL Power down for the TX-path
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . PWD_TX
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_PWD_TX  VTSS_BIT(4)

/** 
 * \brief
 * RCPLL Enable for quarter rate mode
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . QUARTER_RATE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_QUARTER_RATE  VTSS_BIT(5)

/** 
 * \brief
 * RCPLL Control input for startup FSM
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . RC_CTRL_DATA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_RC_CTRL_DATA(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_RC_CTRL_DATA     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_RC_CTRL_DATA(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

/** 
 * \brief
 * RCPLL Enable for startup FSM
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . RC_ENABLE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_RC_ENABLE  VTSS_BIT(14)

/** 
 * \brief
 * RCPLL Selects whether (when set to '1') the frequency range setting from
 * the FSM can be read back at sx_pll_rb_data_o or (when cleared to 0) the
 * measured period.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A . READBACK_DATA_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1A_READBACK_DATA_SEL  VTSS_BIT(15)


/** 
 * \brief H_PLL5G Configuration 1B
 *
 * \details
 * Configuration register 1B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG1B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B  VTSS_IOREG(0x1e, 0, 0x8103)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B . ROT_DIR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B_ROT_DIR  VTSS_BIT(0)

/** 
 * \brief
 * RCPLL feedback divider setting
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B . ROT_SPEED
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B_ROT_SPEED  VTSS_BIT(1)

/** 
 * \brief
 * enable for direct data mode (ATPG/JTAG) reference clock input buffer and
 * test output buffer
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B . ENA_DIRECT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG1B_ENA_DIRECT  VTSS_BIT(2)


/** 
 * \brief H_PLL5G Configuration 2A
 *
 * \details
 * Configuration register 2A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG2A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A  VTSS_IOREG(0x1e, 0, 0x8104)

/** 
 * \brief
 * enable static VCO frequency stepping
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . ENA_GAIN_TEST
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_ENA_GAIN_TEST  VTSS_BIT(0)

/** 
 * \brief
 * disable automatic FSM startup frequency stepping
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . DISABLE_FSM
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_DISABLE_FSM  VTSS_BIT(1)

/** 
 * \brief
 * enable FSM frequency deviation detection
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . EN_RESET_FRQ_DET
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_EN_RESET_FRQ_DET  VTSS_BIT(2)

/** 
 * \brief
 * enable FSM limiter detection
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . EN_RESET_LIM_DET
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_EN_RESET_LIM_DET  VTSS_BIT(3)

/** 
 * \brief
 * enable FSM frequency deviation overrun
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . EN_RESET_OVERRUN
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_EN_RESET_OVERRUN  VTSS_BIT(4)

/** 
 * \brief
 * setting for static VCO frequency stepping 0: lowest frequency,31:
 * highest frequency
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . GAIN_TEST
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_GAIN_TEST(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_GAIN_TEST     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_GAIN_TEST(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * disables the startup FSM to start ramp up the frequency from POR 0:
 * normal,1: disable
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . DISABLE_FSM_POR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_DISABLE_FSM_POR  VTSS_BIT(10)

/** 
 * \brief
 * forces the startup FSM to start ramp up the frequency by POR 0: no
 * force,1: force
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . FRC_FSM_POR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_FRC_FSM_POR  VTSS_BIT(11)

/** 
 * \brief
 * enable static VCO amplitude control
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . ENA_AMP_CTRL_FORCE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_ENA_AMP_CTRL_FORCE  VTSS_BIT(12)

/** 
 * \brief
 * enable automatic VCO amplitude control
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . ENA_AMPCTRL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_ENA_AMPCTRL  VTSS_BIT(13)

/** 
 * \brief
 * force VCO amplitude control output to low (no VCO current) 0:force, 1:
 * no force
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . PWD_AMPCTRL_N
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_PWD_AMPCTRL_N  VTSS_BIT(14)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from ref clock pad
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A . ENA_CLK_BYPASS
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2A_ENA_CLK_BYPASS  VTSS_BIT(15)


/** 
 * \brief H_PLL5G Configuration 2B
 *
 * \details
 * Configuration register 2B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG2B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B  VTSS_IOREG(0x1e, 0, 0x8105)

/** 
 * \brief
 * static VCO amplitude control, active w/ ena_amp_ctrl_force 0: lowest
 * current, 255: highest current
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . AMPC_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_AMPC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_AMPC_SEL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_AMPC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * enable clock bypass for all output clocks to come from extra dividers
 * (125MHz, 250MHz, 312.5MHz)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_CLK_BYPASS1
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_CLK_BYPASS1  VTSS_BIT(8)

/** 
 * \brief
 * enable resistor mode chargepump, test mode
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_CP2
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_CP2  VTSS_BIT(9)

/** 
 * \brief
 * enable RCPLL clock buffer in LCPLL VCO (sx_ena_vco_buf_i must be set to
 * 0)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_RCPLL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_RCPLL  VTSS_BIT(10)

/** 
 * \brief
 * enable feedback divider output to test output buffer
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_FBTESTOUT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_FBTESTOUT  VTSS_BIT(11)

/** 
 * \brief
 * enable VCO frequency control output
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_VCO_NREF_TESTOUT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_VCO_NREF_TESTOUT  VTSS_BIT(12)

/** 
 * \brief
 * enable flip of refclk and fbclk at PFD, used for 2nd chargepump
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_PFD_IN_FLIP
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_PFD_IN_FLIP  VTSS_BIT(13)

/** 
 * \brief
 * enables test modes, e.g. fbdivsel
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B . ENA_TEST_MODE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG2B_ENA_TEST_MODE  VTSS_BIT(14)


/** 
 * \brief H_PLL5G Configuration 3A
 *
 * \details
 * Configuration register 3A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG3A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A  VTSS_IOREG(0x1e, 0, 0x8106)

/** 
 * \brief
 * setting for feedback divider, divide by 12..255
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FBDIVSEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FBDIVSEL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FBDIVSEL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FBDIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * enable feedback divider testmode
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FBDIVSEL_TST_ENA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FBDIVSEL_TST_ENA  VTSS_BIT(8)

/** 
 * \brief
 * force chargepump output to nominal VCO operating point
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FORCE_CP
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FORCE_CP  VTSS_BIT(9)

/** 
 * \brief
 * enable force VCO frequency high/low (force_hi/lo)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FORCE_ENA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FORCE_ENA  VTSS_BIT(10)

/** 
 * \brief
 * force chargepump output to high, gives highest VCO frequency
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FORCE_HI
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FORCE_HI  VTSS_BIT(11)

/** 
 * \brief
 * force chargepump output to low, gives lowest VCO frequency
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FORCE_LO
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FORCE_LO  VTSS_BIT(12)

/** 
 * \brief
 * force vco contrh input to mid level (mid CML level)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . FORCE_VCO_CONTRH
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_FORCE_VCO_CONTRH  VTSS_BIT(13)

/** 
 * \brief
 * reset for feedback divider, active low 0: reset,1:no reset
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . RST_FB_N
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_RST_FB_N  VTSS_BIT(14)

/** 
 * \brief
 * select CML or CMOS phase/frequency detector 0: CML, 1: CMOS
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A . SEL_CML_CMOS_PFD
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3A_SEL_CML_CMOS_PFD  VTSS_BIT(15)


/** 
 * \brief H_PLL5G Configuration 3B
 *
 * \details
 * Configuration register 3B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG3B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B  VTSS_IOREG(0x1e, 0, 0x8107)

/** 
 * \brief
 * enable symmetric feedback divider clock output 0: fbclk/2, 1: fbclk
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B . SEL_FBDCLK
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_SEL_FBDCLK  VTSS_BIT(0)

/** 
 * \brief
 * enable differential test output
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B . ENA_TEST_OUT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_ENA_TEST_OUT  VTSS_BIT(1)

/** 
 * \brief
 * enable analog test output
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B . ENA_ANA_TEST_OUT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_ENA_ANA_TEST_OUT  VTSS_BIT(2)

/** 
 * \brief
 * select test output buffer input signal
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B . TESTOUT_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TESTOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TESTOUT_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TESTOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * select analog test output input signal
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B . TEST_ANA_OUT_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TEST_ANA_OUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TEST_ANA_OUT_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG3B_TEST_ANA_OUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)


/** 
 * \brief H_PLL5G Configuration 4A
 *
 * \details
 * Configuration register 4A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG4A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4A  VTSS_IOREG(0x1e, 0, 0x8108)

/** 
 * \brief
 * Settings for HREFCK reference clock input buffer.
 * [1:0] = select value for adjustable reference voltage from bandgap
 * voltage:
 *	 0: 490mV
 *	 1: 508mV
 *	 2: 487mV
 *	 3: 478mV
 * 
 * [8:2] = reserved
 * 
 * [9] = enable common mode voltage termination to VDD:
 *	 1: enable
 *	 0: disable
 * 
 * [10] = enable_ib
 *	 1: enable
 *	 0: disable
 * 
 * [11] = reserved
 * 
 * [15:12] = value for resistor calibration (RCOMP):
 *	   15: lowest value
 *	    0: highest value
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4A . IB_CTRL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4A_IB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4A_IB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4A_IB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief H_PLL5G Configuration 4B
 *
 * \details
 * Configuration register 4B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG4B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4B  VTSS_IOREG(0x1e, 0, 0x8109)

/** 
 * \brief
 * settings for reference clock input buffer BIAS
 * 
 * [0] = enable single rail input from P branch, 1: enable, 0: disable
 * [1] = enable single rail input from N branch, 1: enable, 0: disable
 * [2] = reserved
 * [3] = enable input termination, 1: enable, 0: disable
 * [7:4] = reserved
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4B . IB_BIAS_CTRL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4B_IB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4B_IB_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG4B_IB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief H_PLL5G Configuration 5A
 *
 * \details
 * Configuration register 5A for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG5A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5A  VTSS_IOREG(0x1e, 0, 0x810a)

/** 
 * \brief
 * settings for test output buffer
 * 
 * [3:0] = value for resistor calibration (RCOMP), 15: lowest value 0:
 * highest value
 * [7:4] = Adjustment for Common Mode Voltage, 0: off --> results in a
 * value around 500mV, 1: 440mV, 2: 480mV, 3: 460mV, 4: 530mV, 6: 500mV, 8:
 * 570mV, 12: 550mV
 * [8] = disable VCM control, 1: disable, 0: enable
 * [9] = enable VREG measure, 1: enable, 0: disable
 * [10] = enable output buffer, 1: enable, 0: disable (powerdown)
 * [11] = reserved
 * [15:12] = select output level, 400mVppd (0) to 1100mVppd (15) in 50mVppd
 * steps

 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5A . OB_CTRL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5A_OB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5A_OB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5A_OB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief H_PLL5G Configuration 5B
 *
 * \details
 * Configuration register 5B for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG5B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5B  VTSS_IOREG(0x1e, 0, 0x810b)

/** 
 * \brief
 * settings for test output buffer BIAS
 * 
 * [2:0] = Sets the class AB bias current in the common mode control
 * circuit. 0.5 mA is expected to give sufficient performance (default 0x2
 * ) and is default. Other settings are for debug. Current range is 0 to
 * 1.75 mA in 0.25mA steps
 * [3] = enable internal CML to CMOS converter for input to test output
 * path
 * [5:4] = reserved
 * [7:6] = slope/slew rate control, 0: 45ps, 1: 85ps, 2: 105ps, 3: 115ps
 * rise/fall time (all values are typical)

 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5B . OB_BIAS_CTRL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5B_OB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5B_OB_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG5B_OB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief H_PLL5G Configuration 6
 *
 * \details
 * Configuration register 6 for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG6A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A  VTSS_IOREG(0x1e, 0, 0x810c)

/** 
 * \brief
 * Setting for DDR clock divider (see core_clk_div)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A . DDR_CLK_DIV
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DDR_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DDR_CLK_DIV     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DDR_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * enable feedback divider CMOS 1/2 clock (for FSM)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A . ENA_FBCLKC2
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_ENA_FBCLKC2  VTSS_BIT(6)

/** 
 * \brief
 * enable reference CMOS 1/2 clock
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A . ENA_REFCLKC2
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_ENA_REFCLKC2  VTSS_BIT(7)

/** 
 * \brief
 * select reference CML clock divider (8,9,10,12 to 255)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A . DIV125REF_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DIV125REF_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DIV125REF_SEL     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6A_DIV125REF_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,8)


/** 
 * \brief H_PLL5G Configuration 6B
 *
 * \details
 * Configuration register 6B for L_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_CFG6B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6B  VTSS_IOREG(0x1e, 0, 0x810d)

/** 
 * \brief
 * enable reference CMOS 1/2 clock (dummy)
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6B . POR_DEL_SEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6B_POR_DEL_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6B_POR_DEL_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_CFG6B_POR_DEL_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief H_PLL5G Status 0
 *
 * \details
 * Status register 0 for the H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_STATUS0
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0  VTSS_IOREG(0x1e, 0, 0x810e)

/** 
 * \brief
 * PLL lock status 0: not locked, 1: locked
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . LOCK_STATUS
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_LOCK_STATUS  VTSS_BIT(0)

/** 
 * \brief
 * RCPLL Interface to read back internal data of the FSM.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . READBACK_DATA
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_READBACK_DATA     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_READBACK_DATA(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/** 
 * \brief
 * RCPLL Flag that indicates that the calibration procedure has finished.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . CALIBRATION_DONE
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_CALIBRATION_DONE  VTSS_BIT(9)

/** 
 * \brief
 * RCPLL Flag that indicates errors that may occur during the calibration
 * procedure.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . CALIBRATION_ERR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_CALIBRATION_ERR  VTSS_BIT(10)

/** 
 * \brief
 * RCPLL Flag that indicates a out of range condition while NOT in
 * calibration mode.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . OUT_OF_RANGE_ERR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_OUT_OF_RANGE_ERR  VTSS_BIT(11)

/** 
 * \brief
 * RCPLL Flag range limiter signaling
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0 . RANGE_LIM
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS0_RANGE_LIM  VTSS_BIT(12)


/** 
 * \brief H_PLL5G Status 1A
 *
 * \details
 * Status register 1A for the H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_STATUS1A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A  VTSS_IOREG(0x1e, 0, 0x810f)

/** 
 * \brief
 * startup FSM lock status
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A . FSM_LOCK
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FSM_LOCK  VTSS_BIT(0)

/** 
 * \brief
 * startup FSM internal status
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A . FSM_STAT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FSM_STAT     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * VCO frequency difference to refclk
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A . FBCNT_DIF
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FBCNT_DIF(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FBCNT_DIF     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1A_FBCNT_DIF(x)  VTSS_EXTRACT_BITFIELD(x,4,10)


/** 
 * \brief H_PLL5G Status 1B
 *
 * \details
 * Status register 1B for the H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_STATUS1B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B  VTSS_IOREG(0x1e, 0, 0x8110)

/** 
 * \brief
 * VCO frequency step stop
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B . GAIN_STAT
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_GAIN_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_GAIN_STAT     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_GAIN_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/** 
 * \brief
 * sigma delta ADC output
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B . SIG_DEL
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_SIG_DEL(x)  VTSS_ENCODE_BITFIELD(x,5,8)
#define  VTSS_M_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_SIG_DEL     VTSS_ENCODE_BITMASK(5,8)
#define  VTSS_X_HOST_PLL5G_H_PLL5G_H_PLL5G_STATUS1B_SIG_DEL(x)  VTSS_EXTRACT_BITFIELD(x,5,8)


/** 
 * \brief H_PLL5G Interrupts
 *
 * \details
 * Interrupt registers for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_INTR
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR  VTSS_IOREG(0x1e, 0, 0x8111)

/** 
 * \brief
 * PLL LOCK_STATUS Interrupt Register
 * 1: H_PLL5G_STATUS0::LOCK_STATUS has changed state since the last time
 * this interrupt bit was cleared.
 * 0: H_PLL5G_STATUS0::LOCK_STATUS has not changed state since the last
 * time this interrupt bit was cleared.
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR . LOCK_STATUS_INTR
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR_LOCK_STATUS_INTR  VTSS_BIT(0)


/** 
 * \brief H_PLL5G Interrupt Masks
 *
 * \details
 * Interrupt masks for H_PLL5G
 *
 * Register: \a HOST_PLL5G:H_PLL5G:H_PLL5G_INTR_MASK
 */
#define VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR_MASK  VTSS_IOREG(0x1e, 0, 0x8112)

/** 
 * \brief
 * Interrupt mask for PLL LOCK_STATUS.	H_PLL5G_INTR::LOCK_STATUS_INTR
 * contributes to the chip's interrupt output pin when enabled.
 * 1: Interrupt enabled
 * 0: Interrupt disabled
 *
 * \details 
 * Field: VTSS_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR_MASK . LOCK_STATUS_INTR_MASK
 */
#define  VTSS_F_HOST_PLL5G_H_PLL5G_H_PLL5G_INTR_MASK_LOCK_STATUS_INTR_MASK  VTSS_BIT(0)

/**
 * Register Group: \a HOST_PLL5G:H_PLL5G_BIST
 *
 * Host PLL5G BIST Configuration Register set
 */


/** 
 * \brief PLL5G BIST Configuration register 0A
 *
 * \details
 * Configuration register 0A for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_CFG0A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_CFG0A  VTSS_IOREG(0x1e, 0, 0x8120)


/** 
 * \brief PLL5G BIST Configuration register 0B
 *
 * \details
 * Configuration register 0B for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_CFG0B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_CFG0B  VTSS_IOREG(0x1e, 0, 0x8121)


/** 
 * \brief PLL5G BIST Configuration register 1
 *
 * \details
 * Configuration register 1 for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_CFG1
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_CFG1  VTSS_IOREG(0x1e, 0, 0x8122)


/** 
 * \brief PLL5G BIST Configuration register 2
 *
 * \details
 * Configuration register 2 for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_CFG2
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_CFG2  VTSS_IOREG(0x1e, 0, 0x8123)


/** 
 * \brief PLL5G BIST Status register 0
 *
 * \details
 * Status register 0 for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_STAT0
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_STAT0  VTSS_IOREG(0x1e, 0, 0x8124)


/** 
 * \brief PLL5G BIST Status register 1A
 *
 * \details
 * Status register 1A for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_STAT1A
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_STAT1A  VTSS_IOREG(0x1e, 0, 0x8125)


/** 
 * \brief PLL5G BIST Status register 1B
 *
 * \details
 * Status register 1B for PLL5G BIST.
 *
 * Register: \a HOST_PLL5G:H_PLL5G_BIST:H_PLL5G_BIST_STAT1B
 */
#define VTSS_HOST_PLL5G_H_PLL5G_BIST_H_PLL5G_BIST_STAT1B  VTSS_IOREG(0x1e, 0, 0x8126)


#endif /* _VTSS_MALIBU_REGS_HOST_PLL5G_H_ */
