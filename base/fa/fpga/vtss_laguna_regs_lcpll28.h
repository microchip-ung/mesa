/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_LAGUNA_REGS_LCPLL28_H_
#define _VTSS_LAGUNA_REGS_LCPLL28_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a LCPLL28
 *
 * LC-PLL 28nm IP
 *
 ***********************************************************************/

/**
 * Register Group: \a LCPLL28:LCPLL28
 *
 * LC-PLL configuartion and status register set
 */


/**
 * \brief LC-PLL configuration register 1
 *
 * \details
 * LC-PLL configuration register 1
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_CONFIG1
 */
#define VTSS_LCPLL28_LCPLL_CONFIG1           VTSS_IOREG(VTSS_TO_LCPLL28_1,0x0)

/**
 * \brief
 * LCPLL Adaptation C offset. Each LSB is 1 LSB of SELCFIN_BIN
 *
 * \details
 * 0: Add no offset
 * >0: Adding offset
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . SELCOFFSET
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_SELCOFFSET(x)  VTSS_ENCODE_BITFIELD(x,24,7)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_SELCOFFSET     VTSS_ENCODE_BITMASK(24,7)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_SELCOFFSET(x)  VTSS_EXTRACT_BITFIELD(x,24,7)

/**
 * \brief
 * VCO power setting. (Binary code)
 *
 * \details
 * 0: Lowest power
 * 1: Higher Power
 * 2: Even Higher Power
 * ...
 * 15: Max power (recommended setting)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . SPRF
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_SPRF(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_SPRF     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_SPRF(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * FST Varactor Bank adjust. Thermometer Coding.
 *
 * \details
 * 0: All varactors off
 * 1: 1 Bank on
 * 3: 2 Banks on
 * 7: 3 Banks on
 * 15: 4 Banks on
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . FSTCTRL
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_FSTCTRL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_FSTCTRL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_FSTCTRL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Set Coarse Metal Cap Select. Used when ADAP is set to 0.
 *
 * \details
 * 0: Max VCO Freq
 * ....
 * 7: Min VCO freq
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . SELCCRS_BIN
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_SELCCRS_BIN(x)  VTSS_ENCODE_BITFIELD(x,13,3)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_SELCCRS_BIN     VTSS_ENCODE_BITMASK(13,3)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_SELCCRS_BIN(x)  VTSS_EXTRACT_BITFIELD(x,13,3)

/**
 * \brief
 * Set Fine Metal Cap Select. Used when ADAP is set to 0.
 *
 * \details
 * 0: Max VCO Freq
 * ....
 * 7: Min VCO freq
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . SELCFIN_BIN
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_SELCFIN_BIN(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_SELCFIN_BIN     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_SELCFIN_BIN(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * LCPLL VCO Range adapatation
 *
 * \details
 * 0: Set manually
 * 1: Adapt
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . ADAP
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_ADAP(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_ADAP    VTSS_BIT(9)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_ADAP(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Bypass Resistor LUT
 *
 * \details
 * 0: Use LUT
 * 1: Bypass LUT. Value of SELFR passed directly to R array
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . RBYP
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_RBYP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_RBYP    VTSS_BIT(8)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_RBYP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Charge pump gain setting. When SDUAL=1, Charge Pump Gain setting for
 * integral path. When SDUAL=0, Charge pump gain setting in summation with
 * STOPCPP.Enable/disable transistor pairs. Thermometer coding.
 *
 * \details
 * 0: Max gain
 * 1: Less gain
 * 3: Even less gain
 * 7: Less than even less gain
 * 15: No gain (do not use)
 * Others: reserved
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . STOPCPI
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_STOPCPI(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_STOPCPI     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_STOPCPI(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * PLL Filter Capacitor SelectThermometer Coding
 *
 * \details
 * 0: Min Cap
 * 1:
 * 3:
 * 7:
 * 15: Max Cap
 * Others: reserved
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG1 . SELFC
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG1_SELFC(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG1_SELFC     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG1_SELFC(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief LC-PLL configuration register 2
 *
 * \details
 * LC-PLL configuration register 2
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_CONFIG2
 */
#define VTSS_LCPLL28_LCPLL_CONFIG2           VTSS_IOREG(VTSS_TO_LCPLL28_1,0x1)

/**
 * \brief
 * PLL Loop Filter R select
 *
 * \details
 * If RBYP = 0:
 * Binary Coding:
 * 0: Max R
 * ...
 * 0xFF: Min R
 *
 * If RBYP = 1:
 * Resistor Weights are as follows. Can use any combination of resistors
 * desired.
 * 0x1: 68.8k
 * 0x2: 34.4k
 * 0x4: 17.2k
 * 0x8: 8.6k
 * 0x10: 4.3k
 * 0x20: 2.15k
 * 0x40: 1.075k
 * 0x80: 537.5

 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG2 . SELFR
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG2_SELFR(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG2_SELFR     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG2_SELFR(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * F in alpha (F/R) For fractional divider. Keep at 0 for normal operation.
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG2 . F
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG2_F(x)    VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG2_F       VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG2_F(x)    VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief LC-PLL configuration register 3
 *
 * \details
 * LC-PLL configuration register 3
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_CONFIG3
 */
#define VTSS_LCPLL28_LCPLL_CONFIG3           VTSS_IOREG(VTSS_TO_LCPLL28_1,0x2)

/**
 * \brief
 * Digital Logic Reset
 *
 * \details
 * 0: Reset
 * 1: Normal Operation
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG3 . RSTN
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG3_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG3_RSTN    VTSS_BIT(27)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG3_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Divide by 2.
 *
 * \details
 * 0: Divide by 2 (Normal Operation)
 * 1: Divide by 1

 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG3 . HLF
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG3_HLF(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG3_HLF     VTSS_BIT(26)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG3_HLF(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * PD Sigma Delta
 *
 * \details
 * 0: Sigma Delta Enabled. Frac-N Operation
 * 1: Power Down Sigma Delta (Normal Operation)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG3 . PDSIG
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG3_PDSIG(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG3_PDSIG   VTSS_BIT(25)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG3_PDSIG(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * R in alpha (alpha = F/R) for fractional divider. Keep at 0x0F4240 for
 * normal operation
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG3 . R
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG3_R(x)    VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG3_R       VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG3_R(x)    VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief LC-PLL configuration register 4
 *
 * \details
 * LC-PLL configuration register 4
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_CONFIG4
 */
#define VTSS_LCPLL28_LCPLL_CONFIG4           VTSS_IOREG(VTSS_TO_LCPLL28_1,0x3)

/**
 * \brief
 * LCPLL Test Mode
 *
 * \details
 * 0:  Normal Operation
 * 1: Adds another Divide by 4 on feedback divider (ATE test only)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG4 . TESTMODE
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG4_TESTMODE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG4_TESTMODE  VTSS_BIT(28)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG4_TESTMODE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Time limit for phase lock detector.	It is the number of clock counts of
 * reference clock.  Within this time, if the number of error is larger
 * than ERRBUF, the lock detector will trigger LOS signal. Good value is
 * 0x14
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG4 . TIMELMT
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG4_TIMELMT(x)  VTSS_ENCODE_BITFIELD(x,23,5)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG4_TIMELMT     VTSS_ENCODE_BITMASK(23,5)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG4_TIMELMT(x)  VTSS_EXTRACT_BITFIELD(x,23,5)

/**
 * \brief
 * Error Buffer. Set to 0x1.
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG4 . ERRBUF
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG4_ERRBUF(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG4_ERRBUF     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG4_ERRBUF(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/**
 * \brief
 * Select source of the LCPLL integer divider value N used for VCO
 * frequency control:When N_SRC_SEL is '0' the value of N is controlled by
 * the reference clock selection strapping pins and the LCPLL_CONFIG4.N
 * register is ignored.When N_SRC_SEL is '1' the value of N is controlled
 * by the LCPLL_CONFIG4.N register.
 *
 * \details
 * 0: Use strapping pins to select N value
 * 1: Use LCPLL_CONFIG4.N register to select N value
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG4 . N_SRC_SEL
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG4_N_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG4_N_SRC_SEL  VTSS_BIT(17)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG4_N_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * N integer divider.  VCO freq = REFCLKIN * N. Target is 10GHz.Minimum: 32
 * (0x20)Maximum: 2^16: 1 The configured value is ignored if
 * LCPLL_CONFIG4.N_SRC_SEL = '0'
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG4 . N
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG4_N(x)    VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG4_N       VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG4_N(x)    VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LC-PLL configuration register 5
 *
 * \details
 * LC-PLL configuration register 5
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_CONFIG5
 */
#define VTSS_LCPLL28_LCPLL_CONFIG5           VTSS_IOREG(VTSS_TO_LCPLL28_1,0x4)

/**
 * \brief
 * Only effective when SDUAL=1. Sets DC voltage level for proportional
 * path.
 *
 * \details
 * 0x0: 3/4 of 0.9v supply
 * 0x1: 1/2 of 0.9v supply
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . SVCMHLF
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_SVCMHLF(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_SVCMHLF  VTSS_BIT(28)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_SVCMHLF(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * When SDUAL=1, Charge pump gain setting for proportional path. When
 * SDUAL=0, Charge Pump gain setting in summation with
 * STOPCPIEnable/disable transistor pairs. Thermometer coding.
 *
 * \details
 * 0x0: Max gain
 * 0x1: Less gain
 * 0x3: Even less gain
 * 0x7: Less than even less gain
 * 0xF: No gain (do not use)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . STOPCPP
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_STOPCPP(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_STOPCPP     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_STOPCPP(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * CML power setting.
 *
 * \details
 * 0x0: Min Power
 * 0x1: More Power
 * ...
 * 0xF: Max Power
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . SNRF
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_SNRF(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_SNRF     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_SNRF(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * PLL loop mode setting.
 *
 * \details
 * 0x0: Single loop
 * 0x1: Dual loop
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . SDUAL
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_SDUAL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_SDUAL   VTSS_BIT(16)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_SDUAL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Charge Pump Current Select (Binary Weighted)
 *
 * \details
 * 0: Minimum
 * 1: More
 * 2: More still
 * ...
 * 31: Max
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . SELCPI
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_SELCPI(x)  VTSS_ENCODE_BITFIELD(x,10,5)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_SELCPI     VTSS_ENCODE_BITMASK(10,5)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_SELCPI(x)  VTSS_EXTRACT_BITFIELD(x,10,5)

/**
 * \brief
 * Digital Mux Select
 *
 * \details
 * 0: CK625M (625MHz)
 * 1: CCK (Feedback clock going back into PFD)
 * 2: RKO (Buffered clock inside PLL feeding PFD)
 * 3: CLKREF (Buffered clock from REFCLK Buffer)
 * 4 - 15: Reserved. (Bits 2 and 3 do not drive anything)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . DMUX_SEL
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_DMUX_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_DMUX_SEL     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_DMUX_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \brief
 * Digital Mux Enable. For test purposes only.
 *
 * \details
 * 0: Disabled. Output is static low.
 * 1: DMUX enabled
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . DMUX_EN
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_DMUX_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_DMUX_EN  VTSS_BIT(5)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_DMUX_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * AMUX select. Select analog signal to monitor.The analog output pin must
 * be enabled to monitor the output from the AMUX. See
 * register:CLKGEN:AOUT:AOUT_CFG.AOUT_ENA
 *
 * \details
 * 0: VSS (0V)
 * 1: VDD1P8 (1.8V)
 * 2: VDD0P9A (0.9V)
 * 3: VDD (0.9V)
 * 4: FSTDC (LC VCO control Voltage)
 * 5: VBG227 (0.227V)
 * 6: VBG454 (0.454V)
 * 7: BG1P2 (1.2V)
 * 8: NRF_PLL (0.9V CML reference voltage)
 * 9: NRFB (1.8V CML reference voltage)
 * 10: NRFT(1.8V CML reference voltage)
 * 11 - 15: VSS (0V)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . AMUX_SEL
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_AMUX_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,4)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_AMUX_SEL     VTSS_ENCODE_BITMASK(1,4)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_AMUX_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,4)

/**
 * \brief
 * AMUX Enable. For Diagnostic purposes only.The analog output pin must be
 * enabled to monitor the output from the AMUX. See
 * registerCLKGEN:AOUT:AOUT_CFG.AOUT_ENA
 *
 * \details
 * 0: Disable AMUX (normal operation. Output set to 0V)
 * 1: Enable AMUX
 *
 * Field: ::VTSS_LCPLL28_LCPLL_CONFIG5 . AMUX_EN
 */
#define  VTSS_F_LCPLL28_LCPLL_CONFIG5_AMUX_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LCPLL28_LCPLL_CONFIG5_AMUX_EN  VTSS_BIT(0)
#define  VTSS_X_LCPLL28_LCPLL_CONFIG5_AMUX_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief LC-PLL miscellaneous configuration register
 *
 * \details
 * LC-PLL miscellaneous configuration register
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_MISC_CONFIG
 */
#define VTSS_LCPLL28_LCPLL_MISC_CONFIG       VTSS_IOREG(VTSS_TO_LCPLL28_1,0x5)

/**
 * \brief
 * CML 10G Clock Buffer Left Enable.
 *
 * \details
 * 0:  Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_LCPLL28_LCPLL_MISC_CONFIG . CLK_BRANCH_LEFT_EN
 */
#define  VTSS_F_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_LEFT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_LEFT_EN  VTSS_BIT(0)
#define  VTSS_X_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_LEFT_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * CML 10G Clock Buffer Right Enable.
 *
 * \details
 * 0:  Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_LCPLL28_LCPLL_MISC_CONFIG . CLK_BRANCH_RIGHT_EN
 */
#define  VTSS_F_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_RIGHT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_RIGHT_EN  VTSS_BIT(1)
#define  VTSS_X_LCPLL28_LCPLL_MISC_CONFIG_CLK_BRANCH_RIGHT_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * LC Cap Calibration Toggle. This bit is toggled low -> high -> low to
 * start the calibration FSM to select the fine and coarse values for the
 * LC tank.
 *
 * \details
 * 0: Normal Operation
 * 0 -> 1 -> 0: Triggers FSM to run and find proper values for LC tank.
 * 1: Clears FSM.
 *
 * Field: ::VTSS_LCPLL28_LCPLL_MISC_CONFIG . CAP_CALIB_TOGGLE
 */
#define  VTSS_F_LCPLL28_LCPLL_MISC_CONFIG_CAP_CALIB_TOGGLE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_LCPLL28_LCPLL_MISC_CONFIG_CAP_CALIB_TOGGLE  VTSS_BIT(2)
#define  VTSS_X_LCPLL28_LCPLL_MISC_CONFIG_CAP_CALIB_TOGGLE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Misc. configuration bits for LCPLL. Currently not used.
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_MISC_CONFIG . MISC_CONFIG
 */
#define  VTSS_F_LCPLL28_LCPLL_MISC_CONFIG_MISC_CONFIG(x)  VTSS_ENCODE_BITFIELD(x,3,13)
#define  VTSS_M_LCPLL28_LCPLL_MISC_CONFIG_MISC_CONFIG     VTSS_ENCODE_BITMASK(3,13)
#define  VTSS_X_LCPLL28_LCPLL_MISC_CONFIG_MISC_CONFIG(x)  VTSS_EXTRACT_BITFIELD(x,3,13)


/**
 * \brief LC-PLL status register
 *
 * \details
 * LC-PLL status register
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_STATUS
 */
#define VTSS_LCPLL28_LCPLL_STATUS            VTSS_IOREG(VTSS_TO_LCPLL28_1,0x6)

/**
 * \brief
 * LCPLL Loss of Lock Status
 *
 * \details
 * 0: PLL Sync'd (Normal Operation)
 * 1: LOL
 *
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . LOL
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_LOL(x)   VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_LOL      VTSS_BIT(13)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_LOL(x)   VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * LCPLL adaptation done
 *
 * \details
 * 0: Running
 * 1: Done (Stable PLL Output)
 *
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . DONE
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_DONE     VTSS_BIT(12)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_DONE(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * LCPLL C Fine slowLow value found for fine select when doing adaptation
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . CFINSLOW
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_CFINSLOW(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_CFINSLOW     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_CFINSLOW(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * LCPLL C Fine HighHigh value found for fine select when doing adaptation
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . CFINFAST
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_CFINFAST(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_CFINFAST     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_CFINFAST(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * LCPLL C Coarse LowLow value found for coarse select when doing
 * adaptation
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . CCRSSLOW
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_CCRSSLOW(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_CCRSSLOW     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_CCRSSLOW(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * LCPLL C Coarse HighHigh value found for coarse select when doing
 * adaptation
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_STATUS . CCRSFAST
 */
#define  VTSS_F_LCPLL28_LCPLL_STATUS_CCRSFAST(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_LCPLL28_LCPLL_STATUS_CCRSFAST     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_LCPLL28_LCPLL_STATUS_CCRSFAST(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief LC-PLL miscellaneous status register
 *
 * \details
 * LC-PLL miscellaneous status register
 *
 * Register: \a LCPLL28:LCPLL28:LCPLL_MISC_STATUS
 */
#define VTSS_LCPLL28_LCPLL_MISC_STATUS       VTSS_IOREG(VTSS_TO_LCPLL28_1,0x7)

/**
 * \brief
 * No connection. Nothing being utilized. Tied Logic Low inside the LCPLL.
 *
 * \details
 * Field: ::VTSS_LCPLL28_LCPLL_MISC_STATUS . MISC_STATUS
 */
#define  VTSS_F_LCPLL28_LCPLL_MISC_STATUS_MISC_STATUS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_LCPLL28_LCPLL_MISC_STATUS_MISC_STATUS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_LCPLL28_LCPLL_MISC_STATUS_MISC_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LAGUNA_REGS_LCPLL28_H_ */
