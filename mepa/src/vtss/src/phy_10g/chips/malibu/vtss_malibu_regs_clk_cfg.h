// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_CLK_CFG_H_
#define _VTSS_MALIBU_REGS_CLK_CFG_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a CLK_CFG
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a CLK_CFG:LINE_OB_CFG
 *
 * Configuration registers for line side clock output drivers
 */


/** 
 * \brief IDDQ enable for all line side clock output drivers
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:LINE_OB_IDDQ_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_LINE_OB_IDDQ_CTRL  VTSS_IOREG(0x1e, 0, 0x7200)

/** 
 * \brief
 * Put output buffers CKOUT2 and CKOUT3 into IDDQ mode
 *
 * \details 
 * 0 = IDDQ mode
 * 1 = Normal operation 
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_LINE_OB_IDDQ_CTRL . CKOUT23_IDDQN_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_LINE_OB_IDDQ_CTRL_CKOUT23_IDDQN_CTRL  VTSS_BIT(1)

/** 
 * \brief
 * Put output buffers CKOUT0 and CKOUT1 into IDDQ mode
 *
 * \details 
 * 0 = IDDQ mode
 * 1 = Normal operation 
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_LINE_OB_IDDQ_CTRL . CKOUT01_IDDQN_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_LINE_OB_IDDQ_CTRL_CKOUT01_IDDQN_CTRL  VTSS_BIT(0)


/** 
 * \brief CKOUT3 Bias Control
 *
 * \details
 * CKOUT3 Bias Control
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT3_BIAS_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x7201)

/** 
 * \brief
 * CKOUT3 Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_BIAS_CTRL . CKOUT3_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_BIAS_CTRL_CKOUT3_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT3_BIAS_CTRL_CKOUT3_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT3_BIAS_CTRL_CKOUT3_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT3 Control Registers
 *
 * \details
 * CKOUT3 Control Registers
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT3_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_CTRL  VTSS_IOREG(0x1e, 0, 0x7202)

/** 
 * \brief
 * CKOUT3 Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_CTRL . CKOUT3_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_CTRL_CKOUT3_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT3_CTRL_CKOUT3_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT3_CTRL_CKOUT3_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT3_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7203)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL . CKOUT3_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL_CKOUT3_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT3
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL . CKOUT3_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL_CKOUT3_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL_CKOUT3_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT3_SQUELCH_CTRL_CKOUT3_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT3 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT3_DATA_SEL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x7204)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL . CKOUT3_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL_CKOUT3_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT3 pin
 *
 * \details 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL . CKOUT3_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL_CKOUT3_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL_CKOUT3_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT3_DATA_SEL_CKOUT3_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT2 Bias Control
 *
 * \details
 * CKOUT2 Bias Control
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT2_BIAS_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x7205)

/** 
 * \brief
 * CKOUT2 Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_BIAS_CTRL . CKOUT2_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_BIAS_CTRL_CKOUT2_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT2_BIAS_CTRL_CKOUT2_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT2_BIAS_CTRL_CKOUT2_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT2 Control Registers
 *
 * \details
 * CKOUT2 Control Registers
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT2_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_CTRL  VTSS_IOREG(0x1e, 0, 0x7206)

/** 
 * \brief
 * CKOUT2 Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_CTRL . CKOUT2_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_CTRL_CKOUT2_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT2_CTRL_CKOUT2_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT2_CTRL_CKOUT2_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT2_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7207)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL . CKOUT2_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL_CKOUT2_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT2
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL . CKOUT2_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL_CKOUT2_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL_CKOUT2_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT2_SQUELCH_CTRL_CKOUT2_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT2 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT2_DATA_SEL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x7208)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL . CKOUT2_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL_CKOUT2_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT2 pin
 *
 * \details 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL . CKOUT2_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL_CKOUT2_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL_CKOUT2_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT2_DATA_SEL_CKOUT2_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT1 Bias Control
 *
 * \details
 * CKOUT1 Bias Control
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT1_BIAS_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x7209)

/** 
 * \brief
 * CKOUT1 Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_BIAS_CTRL . CKOUT1_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_BIAS_CTRL_CKOUT1_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT1_BIAS_CTRL_CKOUT1_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT1_BIAS_CTRL_CKOUT1_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT1 Control Registers
 *
 * \details
 * CKOUT1 Control Registers
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT1_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_CTRL  VTSS_IOREG(0x1e, 0, 0x720a)

/** 
 * \brief
 * CKOUT1 Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_CTRL . CKOUT1_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_CTRL_CKOUT1_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT1_CTRL_CKOUT1_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT1_CTRL_CKOUT1_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT1_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x720b)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL . CKOUT1_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL_CKOUT1_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT1
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL . CKOUT1_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL_CKOUT1_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL_CKOUT1_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT1_SQUELCH_CTRL_CKOUT1_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT1 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT1_DATA_SEL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x720c)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL . CKOUT1_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL_CKOUT1_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT1 pin
 *
 * \details 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL . CKOUT1_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL_CKOUT1_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL_CKOUT1_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT1_DATA_SEL_CKOUT1_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT0 Bias Control
 *
 * \details
 * CKOUT0 Bias Control
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT0_BIAS_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x720d)

/** 
 * \brief
 * CKOUT0 Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_BIAS_CTRL . CKOUT0_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_BIAS_CTRL_CKOUT0_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT0_BIAS_CTRL_CKOUT0_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT0_BIAS_CTRL_CKOUT0_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT0 Control Registers
 *
 * \details
 * CKOUT0 Control Registers
 *
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT0_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_CTRL  VTSS_IOREG(0x1e, 0, 0x720e)

/** 
 * \brief
 * CKOUT0 Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_CTRL . CKOUT0_CTRL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_CTRL_CKOUT0_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT0_CTRL_CKOUT0_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT0_CTRL_CKOUT0_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT0_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x720f)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL . CKOUT0_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL_CKOUT0_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT0
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL . CKOUT0_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL_CKOUT0_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL_CKOUT0_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT0_SQUELCH_CTRL_CKOUT0_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT0 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_OB_CFG:CKOUT0_DATA_SEL
 */
#define VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x7210)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL . CKOUT0_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL_CKOUT0_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT0 pin
 *
 * \details 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL . CKOUT0_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL_CKOUT0_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL_CKOUT0_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_OB_CFG_CKOUT0_DATA_SEL_CKOUT0_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a CLK_CFG:LINE_SD_DBG_SIG_SEL
 *
 * Select internal signal to observe on CKOUT pin
 */


/** 
 * \brief Line SerDes3 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_SD_DBG_SIG_SEL:LINE_SD3_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7211)

/** 
 * \brief
 * Select internal signal from line side serdes 3 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL . LINE_SD3_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL_LINE_SD3_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Line SerDes2 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_SD_DBG_SIG_SEL:LINE_SD2_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7212)

/** 
 * \brief
 * Select internal signal from line side serdes 2 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL . LINE_SD2_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL_LINE_SD2_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Line SerDes1 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_SD_DBG_SIG_SEL:LINE_SD1_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7213)

/** 
 * \brief
 * Select internal signal from line side serdes 1 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL . LINE_SD1_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL_LINE_SD1_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Line SerDes0 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_SD_DBG_SIG_SEL:LINE_SD0_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7214)

/** 
 * \brief
 * Select internal signal from line side serdes 0 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL . LINE_SD0_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL_LINE_SD0_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Line F2DF/DF2F Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:LINE_SD_DBG_SIG_SEL:LINE_F2DF_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_F2DF_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7215)

/** 
 * \brief
 * Select internal signal from line side f2df/df2f serdes to observe on a
 * CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_F2DF_DBG_SIG_SEL . F2DF_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_F2DF_DBG_SIG_SEL_F2DF_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_F2DF_DBG_SIG_SEL_F2DF_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_LINE_SD_DBG_SIG_SEL_LINE_F2DF_DBG_SIG_SEL_F2DF_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a CLK_CFG:HOST_OB_CFG
 *
 * Configuration registers for host side clock output drivers
 */


/** 
 * \brief IDDQ enable for all host side clock output drivers
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:HOST_OB_IDDQ_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_HOST_OB_IDDQ_CTRL  VTSS_IOREG(0x1e, 0, 0x7216)

/** 
 * \brief
 * Put output buffers CKOUT6 and CKOUT7 into IDDQ mode
 *
 * \details 
 * 0 = IDDQ mode
 * 1 = Normal operation 
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_HOST_OB_IDDQ_CTRL . CKOUT67_IDDQN_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_HOST_OB_IDDQ_CTRL_CKOUT67_IDDQN_CTRL  VTSS_BIT(1)

/** 
 * \brief
 * Put output buffers CKOUT4 and CKOUT5 into IDDQ mode
 *
 * \details 
 * 0 = IDDQ mode
 * 1 = Normal operation 
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_HOST_OB_IDDQ_CTRL . CKOUT45_IDDQN_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_HOST_OB_IDDQ_CTRL_CKOUT45_IDDQN_CTRL  VTSS_BIT(0)


/** 
 * \brief CKOUT7 Bias Control
 *
 * \details
 * CKOUT7 Bias Control
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT7_BIAS_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x7217)

/** 
 * \brief
 * CKOUT7 Output Buffer Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_BIAS_CTRL . CKOUT7_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_BIAS_CTRL_CKOUT7_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT7_BIAS_CTRL_CKOUT7_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT7_BIAS_CTRL_CKOUT7_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT7 Control Registers
 *
 * \details
 * CKOUT7 Control Registers
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT7_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_CTRL  VTSS_IOREG(0x1e, 0, 0x7218)

/** 
 * \brief
 * CKOUT7 Output Buffer Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_CTRL . CKOUT7_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_CTRL_CKOUT7_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT7_CTRL_CKOUT7_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT7_CTRL_CKOUT7_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT7_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7219)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL . CKOUT7_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL_CKOUT7_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT7
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL . CKOUT7_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL_CKOUT7_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL_CKOUT7_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT7_SQUELCH_CTRL_CKOUT7_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT7 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT7_DATA_SEL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x721a)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL . CKOUT7_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL_CKOUT7_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT7 pin
 *
 * \details 
 * 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL . CKOUT7_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL_CKOUT7_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL_CKOUT7_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT7_DATA_SEL_CKOUT7_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT6 Bias Control
 *
 * \details
 * CKOUT6 Bias Control
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT6_BIAS_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x721b)

/** 
 * \brief
 * CKOUT6 Output Buffer Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_BIAS_CTRL . CKOUT6_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_BIAS_CTRL_CKOUT6_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT6_BIAS_CTRL_CKOUT6_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT6_BIAS_CTRL_CKOUT6_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT6 Control Registers
 *
 * \details
 * CKOUT6 Control Registers
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT6_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_CTRL  VTSS_IOREG(0x1e, 0, 0x721c)

/** 
 * \brief
 * CKOUT6 Output Buffer Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_CTRL . CKOUT6_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_CTRL_CKOUT6_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT6_CTRL_CKOUT6_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT6_CTRL_CKOUT6_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT6_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x721d)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL . CKOUT6_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL_CKOUT6_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT6
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL . CKOUT6_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL_CKOUT6_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL_CKOUT6_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT6_SQUELCH_CTRL_CKOUT6_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT6 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT6_DATA_SEL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x721e)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL . CKOUT6_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL_CKOUT6_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT6 pin
 *
 * \details 
 * 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL . CKOUT6_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL_CKOUT6_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL_CKOUT6_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT6_DATA_SEL_CKOUT6_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT5 Bias Control
 *
 * \details
 * CKOUT5 Bias Control
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT5_BIAS_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x721f)

/** 
 * \brief
 * CKOUT5 Output Buffer Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_BIAS_CTRL . CKOUT5_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_BIAS_CTRL_CKOUT5_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT5_BIAS_CTRL_CKOUT5_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT5_BIAS_CTRL_CKOUT5_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT5 Control Registers
 *
 * \details
 * CKOUT5 Control Registers
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT5_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_CTRL  VTSS_IOREG(0x1e, 0, 0x7220)

/** 
 * \brief
 * CKOUT5 Output Buffer Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_CTRL . CKOUT5_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_CTRL_CKOUT5_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT5_CTRL_CKOUT5_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT5_CTRL_CKOUT5_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT5_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7221)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL . CKOUT5_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL_CKOUT5_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT5
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL . CKOUT5_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL_CKOUT5_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL_CKOUT5_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT5_SQUELCH_CTRL_CKOUT5_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT5 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT5_DATA_SEL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x7222)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL . CKOUT5_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL_CKOUT5_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT5 pin
 *
 * \details 
 * 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL . CKOUT5_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL_CKOUT5_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL_CKOUT5_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT5_DATA_SEL_CKOUT5_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT4 Bias Control
 *
 * \details
 * CKOUT4 Bias Control
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT4_BIAS_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_BIAS_CTRL  VTSS_IOREG(0x1e, 0, 0x7223)

/** 
 * \brief
 * CKOUT4 Output Buffer Bias Control
 * [1:0]: sel_vref490m, fine tune of OBs internal 490mV reference voltage
 * [3]:   ena_data_cml2cmos, 1: enable feedback CMOS output (clock input
 * directly fed back as CMOS signal, not used in malibu), 0: disable CMOS
 * output
 * [5:4]: sel_ena_abc, input mux, selects input source, 0: primary input,
 * 1: sec. input (not used in malibu), 2: direct data path
 * [7:6]: reserved
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_BIAS_CTRL . CKOUT4_BIAS_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_BIAS_CTRL_CKOUT4_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT4_BIAS_CTRL_CKOUT4_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT4_BIAS_CTRL_CKOUT4_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CKOUT4 Control Registers
 *
 * \details
 * CKOUT4 Control Registers
 *
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT4_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_CTRL  VTSS_IOREG(0x1e, 0, 0x7224)

/** 
 * \brief
 * CKOUT4 Output Buffer Control Registers
 * [3:0]: rsel, resistor calibration input (large value: r-slow, small
 * value: r-fast)
 * [7:4]: reserved
 * [8]:   ena_cterm_drv, increases amplitude by 25% if OB is connected to a
 * receiver whose common mode is terminated to VDDIO, 0: receivers common
 * mode is terminated to VDDIO. 1: otherwise
 * [9]:   reserved
 * [10]:  enable_ob, 1: enable, 0: disable (powerdown)
 * [11]:  ena_1v2, selects if OB is supplied from 1V or 1.2V, 1: 1.2V, 0:
 * 1.0V
 * [15:12]: sel, selects drive amplitude. Max setting is limited in VDDOB =
 * 1.0V mode, 0: lowest ampl. (300mV-400mV), 15: highest ampl.
 * (550mV-700mV)
 *
 * \details 
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_CTRL . CKOUT4_CTRL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_CTRL_CKOUT4_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT4_CTRL_CKOUT4_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT4_CTRL_CKOUT4_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT4_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7225)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL . CKOUT4_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL_CKOUT4_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for CKOUT4
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL . CKOUT4_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL_CKOUT4_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL_CKOUT4_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT4_SQUELCH_CTRL_CKOUT4_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CKOUT4 Data Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_OB_CFG:CKOUT4_DATA_SEL
 */
#define VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL  VTSS_IOREG(0x1e, 0, 0x7226)

/** 
 * \details 
 * 0 = Generate full-rate clock (i.e. LAN: 322.25MHz, WAN: 311.04MHz, 1G:
 * 125MHz)
 * 1 = Generate divide-by-2 version (i.e. LAN: 161.12MHz, etc)
 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL . CKOUT4_DIVIDE_BY_2
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL_CKOUT4_DIVIDE_BY_2  VTSS_BIT(8)

/** 
 * \brief
 * Select data to be transmitted from CKOUT4 pin
 *
 * \details 
 * 
 * 0 = Line 0 Transmit Clock
 * 1 = Line 1 Transmit Clock
 * 2 = Line 2 Transmit Clock
 * 3 = Line 3 Transmit Clock
 * 4 = Host 0 Transmit Clock
 * 5 = Host 1 Transmit Clock
 * 6 = Host 2 Transmit Clock
 * 7 = Host 3 Transmit Clock
 * 8 = Line 0 Recovered Clock
 * 9 = Line 1 Recovered Clock
 * 10= Line 2 Recovered Clock
 * 11= Line 3 Recovered Clock
 * 12= Host 0 Recovered Clock
 * 13= Host 1 Recovered Clock
 * 14= Host 2 Recovered Clock
 * 15= Host 3 Recovered Clock
 * 16= Host Pll Clock
 * 17= Line Pll Clock
 * 18= CSR Clock
 * 19= LTC Clock
 * 20= Df2f clk
 * 21= F2df clk
 * 29= Debug
 * 30= Debug
 * 31= Oscillator output 

 *
 * Field: VTSS_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL . CKOUT4_DATA_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL_CKOUT4_DATA_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL_CKOUT4_DATA_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_OB_CFG_CKOUT4_DATA_SEL_CKOUT4_DATA_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a CLK_CFG:HOST_SD_DBG_SIG_SEL
 *
 * Select internal signal to observe on CKOUT pin
 */


/** 
 * \brief Host SerDes3 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_SD_DBG_SIG_SEL:HOST_SD3_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7227)

/** 
 * \brief
 * Select internal signal from host side serdes 3 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL . HOST_SD3_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL_HOST_SD3_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Host SerDes2 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_SD_DBG_SIG_SEL:HOST_SD2_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7228)

/** 
 * \brief
 * Select internal signal from host side serdes 2 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL . HOST_SD2_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL_HOST_SD2_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Host SerDes1 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_SD_DBG_SIG_SEL:HOST_SD1_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x7229)

/** 
 * \brief
 * Select internal signal from host side serdes 1 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL . HOST_SD1_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL_HOST_SD1_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief Host SerDes0 Debug Signal Selection
 *
 * \details
 * Register: \a CLK_CFG:HOST_SD_DBG_SIG_SEL:HOST_SD0_DBG_SIG_SEL
 */
#define VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL  VTSS_IOREG(0x1e, 0, 0x722a)

/** 
 * \brief
 * Select internal signal from host side serdes 0 to observe on a CKOUT pin
 *
 * \details 
 * 0 = rx_clk
 * 1 = tx_clk
 * 2 = rx_pll_lock
 * 3 = tx_pll_lock
 * 4 = cp
 * 5 = md
 * 6 = direct_data (from Rx)
 * 7 = sig_det from IA
 * 8 = sig_det from IS
 * 9 = rec_det
 * 10 = ibiados
 * 11 = ibisdos
 * 12 = f2df_side_det
 * 13 = f2df_tog_det
 * 14 = ssc_sync
 * 15 = acjtag_stat[0]
 * 16 = acjtag_stat[1]
 * 17 = lev_det0
 * 18 = lev_det1
 *
 * Field: VTSS_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL . HOST_SD0_DBG_SIG_SEL
 */
#define  VTSS_F_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_HOST_SD_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL_HOST_SD0_DBG_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a CLK_CFG:CS
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a CLK_CFG:CS:LINE_CLK_SEL
 *
 * @param ri Register: LINE_CLK_SEL, 0-3
 */
#define VTSS_CLK_CFG_CS_LINE_CLK_SEL(ri)     VTSS_IOREG(0x1e, 0, 0x722b + (ri))

/** 
 * \brief
 * Selects the source to which the given line transmit clock will be
 * synchronoized
 *
 * \details 
 * 0 = Line 0 recovered clock
 * 1 = Line 1 recovered clock
 * 2 = Line 2 recovered clock
 * 3 = Line 3 recovered clock
 * 4 = Host 0 recovered clock
 * 5 = Host 1 recovered clock
 * 6 = Host 2 recovered clock
 * 7 = Host 3 recovered clock
 * 8 = SREFCK
 * 9-15 = Synchronization disabled
 *
 * Field: VTSS_CLK_CFG_CS_LINE_CLK_SEL . LINE_CLK_SEL
 */
#define  VTSS_F_CLK_CFG_CS_LINE_CLK_SEL_LINE_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CLK_CFG_CS_LINE_CLK_SEL_LINE_CLK_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CLK_CFG_CS_LINE_CLK_SEL_LINE_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \details
 * Register: \a CLK_CFG:CS:HOST_CLK_SEL
 *
 * @param ri Register: HOST_CLK_SEL, 0-3
 */
#define VTSS_CLK_CFG_CS_HOST_CLK_SEL(ri)     VTSS_IOREG(0x1e, 0, 0x722f + (ri))

/** 
 * \brief
 * Selects the source to which the given host transmit clock will be
 * synchronoized
 *
 * \details 
 * 0 = Line 0 recovered clock
 * 1 = Line 1 recovered clock
 * 2 = Line 2 recovered clock
 * 3 = Line 3 recovered clock
 * 4 = Host 0 recovered clock
 * 5 = Host 1 recovered clock
 * 6 = Host 2 recovered clock
 * 7 = Host 3 recovered clock
 * 8 = SREFCK
 * 9-15 = Synchronization disabled
 *
 * Field: VTSS_CLK_CFG_CS_HOST_CLK_SEL . HOST_CLK_SEL
 */
#define  VTSS_F_CLK_CFG_CS_HOST_CLK_SEL_HOST_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CLK_CFG_CS_HOST_CLK_SEL_HOST_CLK_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CLK_CFG_CS_HOST_CLK_SEL_HOST_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \details
 * Register: \a CLK_CFG:CS:SCKOUT_CLK_SEL
 */
#define VTSS_CLK_CFG_CS_SCKOUT_CLK_SEL       VTSS_IOREG(0x1e, 0, 0x7233)

/** 
 * \brief
 * Selects the source to which the SCKOUT transmit clock will be
 * synchronoized
 *
 * \details 
 * 0 = Line 0 recovered clock
 * 1 = Line 1 recovered clock
 * 2 = Line 2 recovered clock
 * 3 = Line 3 recovered clock
 * 4 = Host 0 recovered clock
 * 5 = Host 1 recovered clock
 * 6 = Host 2 recovered clock
 * 7 = Host 3 recovered clock
 * 8 = SREFCK
 * 9-15 = Synchronization disabled
 *
 * Field: VTSS_CLK_CFG_CS_SCKOUT_CLK_SEL . SCKOUT_CLK_SEL
 */
#define  VTSS_F_CLK_CFG_CS_SCKOUT_CLK_SEL_SCKOUT_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CLK_CFG_CS_SCKOUT_CLK_SEL_SCKOUT_CLK_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CLK_CFG_CS_SCKOUT_CLK_SEL_SCKOUT_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Squelch Control
 *
 * \details
 * Register: \a CLK_CFG:CS:SCKOUT_SQUELCH_CTRL
 */
#define VTSS_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL  VTSS_IOREG(0x1e, 0, 0x7234)

/** 
 * \details 
 * 0 = Use Squelch_src as is
 * 1 = Invert Squelch_src
 *
 * Field: VTSS_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL . SCKOUT_SQUELCH_INV
 */
#define  VTSS_F_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL_SCKOUT_SQUELCH_INV  VTSS_BIT(8)

/** 
 * \brief
 * Source of auto-squelch logic for SCKOUT
 *
 * \details 
 * 0  = from gpio 0
 * 1  = from gpio 1
 * 2  = from gpio 2
 * 3  = from gpio 3
 * 4  = from gpio 4
 * 5  = from gpio 5
 * 6  = from gpio 6
 * 7  = from gpio 7
 * 8  = 1g/10g link status from line 0
 * 9  = 1g/10g link status from line 1
 * 10 = 1g/10g link status from line 2
 * 11 = 1g/10g link status from line 3
 * 12 = 1g/10g link status from host 0
 * 13 = 1g/10g link status from host 1
 * 14 = 1g/10g link status from host 2
 * 15 = 1g/10g link status from host 3
 * 16 = serdes los from line 0
 * 17 = serdes los from line 1
 * 18 = serdes los from line 2
 * 19 = serdes los from line 3
 * 20 = serdes los from host 0
 * 21 = serdes los from host 1
 * 22 = serdes los from host 2
 * 23 = serdes los from host 3
 * 24 = 1g/10g link status from line 0 KR
 * 25 = 1g/10g link status from line 1 KR
 * 26 = 1g/10g link status from line 2 KR
 * 27 = 1g/10g link status from line 3 KR
 * 28 = 1g/10g link status from host 0 KR
 * 29 = 1g/10g link status from host 1 KR
 * 30 = 1g/10g link status from host 2 KR
 * 31 = 1g/10g link status from host 3 KR
 * 32-63 = No Squelch

 *
 * Field: VTSS_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL . SCKOUT_SQUELCH_SRC
 */
#define  VTSS_F_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL_SCKOUT_SQUELCH_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL_SCKOUT_SQUELCH_SRC     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_CLK_CFG_CS_SCKOUT_SQUELCH_CTRL_SCKOUT_SQUELCH_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \details
 * Register: \a CLK_CFG:CS:FIFO_ERR_STAT
 */
#define VTSS_CLK_CFG_CS_FIFO_ERR_STAT        VTSS_IOREG(0x1e, 0, 0x7235)

/** 
 * \brief
 * Current DF2F lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . DF2F_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_DF2F_FIFO_ERR_STAT  VTSS_BIT(8)

/** 
 * \brief
 * Current host 3 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . HOST3_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_HOST3_FIFO_ERR_STAT  VTSS_BIT(7)

/** 
 * \brief
 * Current host 2 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . HOST2_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_HOST2_FIFO_ERR_STAT  VTSS_BIT(6)

/** 
 * \brief
 * Current host 1 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . HOST1_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_HOST1_FIFO_ERR_STAT  VTSS_BIT(5)

/** 
 * \brief
 * Current host 0 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . HOST0_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_HOST0_FIFO_ERR_STAT  VTSS_BIT(4)

/** 
 * \brief
 * Current line 3 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . LINE3_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_LINE3_FIFO_ERR_STAT  VTSS_BIT(3)

/** 
 * \brief
 * Current line 2 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . LINE2_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_LINE2_FIFO_ERR_STAT  VTSS_BIT(2)

/** 
 * \brief
 * Current line 1 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . LINE1_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_LINE1_FIFO_ERR_STAT  VTSS_BIT(1)

/** 
 * \brief
 * Current line 0 lane sync fifo error status
 *
 * \details 
 * 0 = No Error
 * 1 = FIFO Error
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_STAT . LINE0_FIFO_ERR_STAT
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_STAT_LINE0_FIFO_ERR_STAT  VTSS_BIT(0)


/** 
 * \details
 * Register: \a CLK_CFG:CS:FIFO_ERR_MASK
 */
#define VTSS_CLK_CFG_CS_FIFO_ERR_MASK        VTSS_IOREG(0x1e, 0, 0x7236)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = DF2F_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = DF2F_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . DF2F_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_DF2F_FIFO_ERR_INTR_EN  VTSS_BIT(8)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = HOST3_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = HOST3_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . HOST3_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_HOST3_FIFO_ERR_INTR_EN  VTSS_BIT(7)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = HOST2_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = HOST2_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . HOST2_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_HOST2_FIFO_ERR_INTR_EN  VTSS_BIT(6)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = HOST1_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = HOST1_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . HOST1_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_HOST1_FIFO_ERR_INTR_EN  VTSS_BIT(5)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = HOST0_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = HOST0_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . HOST0_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_HOST0_FIFO_ERR_INTR_EN  VTSS_BIT(4)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = LINE3_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = LINE3_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . LINE3_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_LINE3_FIFO_ERR_INTR_EN  VTSS_BIT(3)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = LINE2_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = LINE2_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . LINE2_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_LINE2_FIFO_ERR_INTR_EN  VTSS_BIT(2)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = LINE1_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = LINE1_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . LINE1_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_LINE1_FIFO_ERR_INTR_EN  VTSS_BIT(1)

/** 
 * \brief
 * Interrupt enable for line 0 lane sync fifo
 *
 * \details 
 * 0 = LINE0_FIFO_ERR_STICKY will not propagate to interrupt
 * 1 = LINE0_FIFO_ERR_STICKY will propagate to interrupt
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_MASK . LINE0_FIFO_ERR_INTR_EN
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_MASK_LINE0_FIFO_ERR_INTR_EN  VTSS_BIT(0)


/** 
 * \details
 * Register: \a CLK_CFG:CS:FIFO_ERR_INTR
 */
#define VTSS_CLK_CFG_CS_FIFO_ERR_INTR        VTSS_IOREG(0x1e, 0, 0x7237)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . DF2F_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_DF2F_FIFO_ERR_STICKY  VTSS_BIT(8)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . HOST3_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_HOST3_FIFO_ERR_STICKY  VTSS_BIT(7)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . HOST2_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_HOST2_FIFO_ERR_STICKY  VTSS_BIT(6)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . HOST1_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_HOST1_FIFO_ERR_STICKY  VTSS_BIT(5)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . HOST0_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_HOST0_FIFO_ERR_STICKY  VTSS_BIT(4)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . LINE3_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_LINE3_FIFO_ERR_STICKY  VTSS_BIT(3)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . LINE2_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_LINE2_FIFO_ERR_STICKY  VTSS_BIT(2)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . LINE1_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_LINE1_FIFO_ERR_STICKY  VTSS_BIT(1)

/** 
 * \details 
 * 0 = FIFO error not detected since last cleared
 * 1 = FIFO error detected since last cleared
 *
 * Field: VTSS_CLK_CFG_CS_FIFO_ERR_INTR . LINE0_FIFO_ERR_STICKY
 */
#define  VTSS_F_CLK_CFG_CS_FIFO_ERR_INTR_LINE0_FIFO_ERR_STICKY  VTSS_BIT(0)


#endif /* _VTSS_MALIBU_REGS_CLK_CFG_H_ */
