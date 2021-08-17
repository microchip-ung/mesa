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

#ifndef _VTSS_LAGUNA_REGS_WDT_H_
#define _VTSS_LAGUNA_REGS_WDT_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a WDT
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a WDT:WDT
 *
 * Not documented
 */


/**
 * \brief Control Register
Reset Value: Register fields WDT_DFLT_RPL (3 bits), WDT_DFLT_RMOD (1 bit) and WDT_ALWAYS_EN (1 bit)
 *
 * \details
 * Register: \a WDT:WDT:WDT_CR
 */
#define VTSS_WDT_WDT_CR                      VTSS_IOREG(VTSS_TO_WDT,0x0)

/**
 * \brief
 * WDT enable.
 *  When the configuration parameter WDT_ALWAYS_EN = 0, this bit can be
 * set; otherwise, it is read-only. This bit is used to enable and disable
 * the DW_apb_wdt. When disabled, the counter does not decrement. Thus, no
 * interrupts or system resets are generated.
 *  The DW_apb_wdt is used to prevent system lock-up. To prevent a software
 * bug from disabling the DW_apb_wdt, once this bit has been enabled, it
 * can be cleared only by a system reset.
 * Reset Value: WDT_ALWAYS_EN
 *
 * \details
 * 0x0: Watchdog timer disabled
 * 0x1: Watchdog timer enabled

 *
 * Field: ::VTSS_WDT_WDT_CR . WDT_EN
 */
#define  VTSS_F_WDT_WDT_CR_WDT_EN(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_WDT_WDT_CR_WDT_EN             VTSS_BIT(0)
#define  VTSS_X_WDT_WDT_CR_WDT_EN(x)          VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Response mode.
 *  Writes have no effect when the parameter WDT_HC_RMOD = 1, thus this
 * register becomes read-only. Selects the output response generated to a
 * timeout.
 * Reset Value: WDT_DFLT_RMOD
 *
 * \details
 * 0x1: First generate an interrupt and even if it is cleared by the time a
 * second timeout occurs then generate a system reset
 * 0x0: Generate a system reset

 *
 * Field: ::VTSS_WDT_WDT_CR . RMOD
 */
#define  VTSS_F_WDT_WDT_CR_RMOD(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_WDT_WDT_CR_RMOD               VTSS_BIT(1)
#define  VTSS_X_WDT_WDT_CR_RMOD(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset pulse length.
 * Writes have no effect when the configuration parameter WDT_HC_RPL is 1,
 * making the register bits read-only. This is used to select
 * the number of pclk cycles for which the system reset stays asserted. The
 * range of values available is 2 to 256 pclk cycles.
 * Reset Value: WDT_DFLT_RPL
 * Note: When
 * WDT_SYNC_CLK_MOPE_ENABLE = 1, the total reset pulse length also includes
 * the reset synchronization delay and the time taken for pclk to be made
 * available. For details, refer to "System Resets" section of DW_apb_wdt
 * Databook.
 *
 * \details
 * 0x6: 128 pclk cycles
 * 0x3: 16  pclk cycles
 * 0x0: 2   pclk cycles
 * 0x7: 256 pclk cycles
 * 0x4: 32  pclk cycles
 * 0x1: 4   pclk cycles
 * 0x5: 64  pclk cycles
 * 0x2: 8   pclk cycles

 *
 * Field: ::VTSS_WDT_WDT_CR . RPL
 */
#define  VTSS_F_WDT_WDT_CR_RPL(x)             VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_WDT_WDT_CR_RPL                VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_WDT_WDT_CR_RPL(x)             VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Redundant R/W bit. Included for ping test purposes, as it is the only
 * R/W register bit that is in every configuration of the DW_apb_wdt.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_CR . NO_NAME
 */
#define  VTSS_F_WDT_WDT_CR_NO_NAME(x)         VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_WDT_WDT_CR_NO_NAME            VTSS_BIT(5)
#define  VTSS_X_WDT_WDT_CR_NO_NAME(x)         VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief Timeout Range Register
Reset Value: WDT_TOP_RST
 *
 * \details
 * Register: \a WDT:WDT:WDT_TORR
 */
#define VTSS_WDT_WDT_TORR                    VTSS_IOREG(VTSS_TO_WDT,0x1)

/**
 * \brief
 * Timeout period.
 *  Writes have no effect when the configuration parameter WDT_HC_TOP = 1,
 * thus making this register read-only. This field is used to select the
 * timeout period from which the watchdog counter restarts. A change of the
 * timeout period takes effect only after the next counter restart (kick).
 *  The range of values is limited by the WDT_CNT_WIDTH. If TOP is
 * programmed to select a range that is greater than the counter width, the
 * timeout period is truncated to fit to the counter width. This affects
 * only the non-user specified values as users are limited to these
 * boundaries during configuration.
 *  The range of values available for a 32-bit watchdog counter are:
 *
 *	     Where i = TOP and t = timeout period
 *
 *	     For i = 0 to 15
 *
 *	       if WDT_USE_FIX_TOP==1
 *
 *		 t = 2(16 + i)
 *
 *	       else
 *
 *		 t = WDT_USER_TOP_(i)
 *
 * Reset Value: WDT_DFLT_TOP
 *
 * \details
 * 0x0: Time out of WDT_USER_TOP_0 or 64K Clocks
 * 0xa: Time out of WDT_USER_TOP_10 or 64M Clocks
 * 0xb: Time out of WDT_USER_TOP_11 or 128M Clocks
 * 0xc: Time out of WDT_USER_TOP_12 or 256M Clocks
 * 0xd: Time out of WDT_USER_TOP_13 or 512M Clocks
 * 0xe: Time out of WDT_USER_TOP_14 or 1G Clocks
 * 0xf: Time out of WDT_USER_TOP_15 or 2G Clocks
 * 0x1: Time out of WDT_USER_TOP_1 or 128K Clocks
 * 0x2: Time out of WDT_USER_TOP_2 or 256K Clocks
 * 0x3: Time out of WDT_USER_TOP_3 or 512K Clocks
 * 0x4: Time out of WDT_USER_TOP_4 or 1M Clocks
 * 0x5: Time out of WDT_USER_TOP_5 or 2M Clocks
 * 0x6: Time out of WDT_USER_TOP_6 or 4M Clocks
 * 0x7: Time out of WDT_USER_TOP_7 or 8M Clocks
 * 0x8: Time out of WDT_USER_TOP_8 or 16M Clocks
 * 0x9: Time out of WDT_USER_TOP_9 or 32M Clocks

 *
 * Field: ::VTSS_WDT_WDT_TORR . TOP
 */
#define  VTSS_F_WDT_WDT_TORR_TOP(x)           VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_WDT_WDT_TORR_TOP              VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_WDT_WDT_TORR_TOP(x)           VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * WDT_TORR[31:24] Reserved and read as zero (0).
 *
 * \details
 * Field: ::VTSS_WDT_WDT_TORR . RESERVED
 */
#define  VTSS_F_WDT_WDT_TORR_RESERVED(x)      VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_WDT_WDT_TORR_RESERVED         VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_WDT_WDT_TORR_RESERVED(x)      VTSS_EXTRACT_BITFIELD(x,8,24)


/**
 * \brief Current Counter Value Register.
Reset Value: WDT_CNT_RST
 *
 * \details
 * Register: \a WDT:WDT:WDT_CCVR
 */
#define VTSS_WDT_WDT_CCVR                    VTSS_IOREG(VTSS_TO_WDT,0x2)

/**
 * \brief
 * WDT Current Counter Value Register.
 *  This register, when read, is the current value of the internal counter.
 * This value is read coherently whenever it is read, which is relevant
 * when the APB_DATA_WIDTH is less than the counter width.
 * Reset Value: WDT_CNT_RST
 *
 * \details
 * Field: ::VTSS_WDT_WDT_CCVR . WDT_CCVR
 */
#define  VTSS_F_WDT_WDT_CCVR_WDT_CCVR(x)      (x)
#define  VTSS_M_WDT_WDT_CCVR_WDT_CCVR         0xffffffff
#define  VTSS_X_WDT_WDT_CCVR_WDT_CCVR(x)      (x)


/**
 * \brief Counter Restart Register
Reset Value: 0x0
 *
 * \details
 * Register: \a WDT:WDT:WDT_CRR
 */
#define VTSS_WDT_WDT_CRR                     VTSS_IOREG(VTSS_TO_WDT,0x3)

/**
 * \brief
 * Counter Restart Register.
 *  This register is used to restart the WDT counter. As a safety feature
 * to prevent accidental restarts, the value 0x76 must be written. A
 * restart also clears the WDT interrupt. Reading this register returns
 * zero.
 * Reset Value: 0
 *
 * \details
 * 0x76: Watchdog timer restart command

 *
 * Field: ::VTSS_WDT_WDT_CRR . WDT_CRR
 */
#define  VTSS_F_WDT_WDT_CRR_WDT_CRR(x)        VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_WDT_WDT_CRR_WDT_CRR           VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_WDT_WDT_CRR_WDT_CRR(x)        VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Interrupt Status Register
Reset Value: 0x0
 *
 * \details
 * Register: \a WDT:WDT:WDT_STAT
 */
#define VTSS_WDT_WDT_STAT                    VTSS_IOREG(VTSS_TO_WDT,0x4)

/**
 * \brief
 * Interrupt status register
 *  This register shows the interrupt status of the WDT.
 * Reset Value	0
 *
 * \details
 * 0x1: Interrupt is active regardless of polarity
 * 0x0: Interrupt is inactive

 *
 * Field: ::VTSS_WDT_WDT_STAT . WDT_STAT
 */
#define  VTSS_F_WDT_WDT_STAT_WDT_STAT(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_WDT_WDT_STAT_WDT_STAT         VTSS_BIT(0)
#define  VTSS_X_WDT_WDT_STAT_WDT_STAT(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Interrupt Clear Register
Reset Value: 0x0
 *
 * \details
 * Register: \a WDT:WDT:WDT_EOI
 */
#define VTSS_WDT_WDT_EOI                     VTSS_IOREG(VTSS_TO_WDT,0x5)

/**
 * \brief
 * Interrupt Clear Register.
 *  Clears the watchdog interrupt. This can be used to clear the interrupt
 * without restarting the watchdog counter.
 * Reset Value: 0
 *
 * \details
 * Field: ::VTSS_WDT_WDT_EOI . WDT_EOI
 */
#define  VTSS_F_WDT_WDT_EOI_WDT_EOI(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_WDT_WDT_EOI_WDT_EOI           VTSS_BIT(0)
#define  VTSS_X_WDT_WDT_EOI_WDT_EOI(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Component Parameters Register 5
Note: This is a constant read-only register that contains encoded information about the component's parameter settings. The reset value depends on coreConsultant parameter(s).
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_PARAM_5
 */
#define VTSS_WDT_WDT_COMP_PARAM_5            VTSS_IOREG(VTSS_TO_WDT,0x39)

/**
 * \brief
 * Upper limit of Timeout Period parameters. The value of this register is
 * derived from the WDT_USER_TOP_* coreConsultant parameters.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_5 . CP_WDT_USER_TOP_MAX
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_5_CP_WDT_USER_TOP_MAX(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_PARAM_5_CP_WDT_USER_TOP_MAX     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_PARAM_5_CP_WDT_USER_TOP_MAX(x)  (x)


/**
 * \brief Component Parameters Register 4
Note: This is a constant read-only register that contains encoded information about the component's parameter settings. The reset value depends on coreConsultant parameter(s).
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_PARAM_4
 */
#define VTSS_WDT_WDT_COMP_PARAM_4            VTSS_IOREG(VTSS_TO_WDT,0x3a)

/**
 * \brief
 * Upper limit of Initial Timeout Period parameters. The value of this
 * register is derived from the WDT_USER_TOP_INIT_* coreConsultant
 * parameters.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_4 . CP_WDT_USER_TOP_INIT_MAX
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_4_CP_WDT_USER_TOP_INIT_MAX(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_PARAM_4_CP_WDT_USER_TOP_INIT_MAX     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_PARAM_4_CP_WDT_USER_TOP_INIT_MAX(x)  (x)


/**
 * \brief Component Parameters Register 3
Note: This is a constant read-only register that contains encoded information about the component's parameter settings. The reset value depends on coreConsultant parameter(s).
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_PARAM_3
 */
#define VTSS_WDT_WDT_COMP_PARAM_3            VTSS_IOREG(VTSS_TO_WDT,0x3b)

/**
 * \brief
 * The value of this register is derived from the WDT_TOP_RST
 * coreConsultant parameter.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_3 . CD_WDT_TOP_RST
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_3_CD_WDT_TOP_RST(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_PARAM_3_CD_WDT_TOP_RST     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_PARAM_3_CD_WDT_TOP_RST(x)  (x)


/**
 * \brief Component Parameters Register 2
Note: This is a constant read-only register that contains encoded information about the component's parameter settings. The reset value depends on coreConsultant parameter(s).
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_PARAM_2
 */
#define VTSS_WDT_WDT_COMP_PARAM_2            VTSS_IOREG(VTSS_TO_WDT,0x3c)

/**
 * \brief
 * The value of this register is derived from the WDT_RST_CNT
 * coreConsultant parameter.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_2 . CP_WDT_CNT_RST
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_2_CP_WDT_CNT_RST(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_PARAM_2_CP_WDT_CNT_RST     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_PARAM_2_CP_WDT_CNT_RST(x)  (x)


/**
 * \brief Component Parameters Register 1
Note:This is a constant read-only register that contains encoded information about the component's parameter settings. Some of the reset values depend on coreConsultant parameter(s).
Reset Value:  Configuration dependent
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_PARAM_1
 */
#define VTSS_WDT_WDT_COMP_PARAM_1            VTSS_IOREG(VTSS_TO_WDT,0x3d)

/**
 * \brief
 * Configures the WDT to be enabled from reset. If this setting is 1, the
 * WDT is always enabled and a write to the WDT_EN field (bit 0) of the
 * Watchdog Timer Control Register (WDT_CR) to disable it has no effect.
 *
 * \details
 * 0x0: Watchdog timer disabled on reset
 * 0x1: Watchdog timer enabled on reset

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_ALWAYS_EN
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_ALWAYS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_ALWAYS_EN  VTSS_BIT(0)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_ALWAYS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Describes the output response mode that is available directly after
 * reset. Indicates the output response the WDT gives if a zero count is
 * reached; that is, a system reset if equals 0 and an interrupt followed
 * by a system reset, if equals 1. If WDT_HC_RMOD is 1, then default
 * response mode is the only possible output response mode.
 *
 * \details
 * 0x0: System reset only
 * 0x1: Interrupt and system reset

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_DFLT_RMOD
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RMOD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RMOD  VTSS_BIT(1)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RMOD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When set to 1, includes a second timeout period that is used for
 * initialization prior to the first kick.
 *
 * \details
 * 0x0: Second timeout period is not present
 * 0x1: Second timeout period is present

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_DUAL_TOP
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_DUAL_TOP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_DUAL_TOP  VTSS_BIT(2)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_DUAL_TOP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Configures the output response mode to be hard coded.
 *
 * \details
 * 0x1: Output response mode is hard coded
 * 0x0: Output response mode is programmable

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_HC_RMOD
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_HC_RMOD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_HC_RMOD  VTSS_BIT(3)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_HC_RMOD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Configures the reset pulse length to be hard coded.
 *
 * \details
 * 0x1: Reset pulse length is hardcoded
 * 0x0: Reset pulse length is programmable

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_HC_RPL
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_HC_RPL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_HC_RPL  VTSS_BIT(4)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_HC_RPL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * When set to 1, the selected timeout period(s) is set to be hard coded.
 *
 * \details
 * 0x1: Timeout period is hard coded
 * 0x0: Timeout period is programmable

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_HC_TOP
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_HC_TOP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_HC_TOP  VTSS_BIT(5)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_HC_TOP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When this parameter is set to 1, timeout period range is fixed. The
 * range increments by the power of 2 from 2^16 to 2^(WDT_CNT_WIDTH-1).
 * When this parameter is set to 0, the user must define the timeout period
 * range (2^8 to 2^(WDT_CNT_WIDTH)-1) using the WDT_USER_TOP_(i) parameter.
 *
 * \details
 * 0x1: Use predefined timeout values
 * 0x0: User must define timeout values

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_USE_FIX_TOP
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_USE_FIX_TOP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_USE_FIX_TOP  VTSS_BIT(6)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_USE_FIX_TOP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configures the peripheral to have a pause enable signal (pause) on the
 * interface that can be used to freeze the watchdog counter during pause
 * mode.
 *
 * \details
 * 0x0: Pause enable signal is non existent
 * 0x1: Pause enable signal is included

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_PAUSE
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_PAUSE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_PAUSE  VTSS_BIT(7)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_PAUSE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Width of the APB Data Bus to which this component is attached.
 *
 * \details
 * 0x1: APB data width is 16 bits
 * 0x2: APB data width is 32 bits
 * 0x0: APB data width is 8 bits

 *
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . APB_DATA_WIDTH
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_APB_DATA_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_APB_DATA_WIDTH     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_APB_DATA_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * The reset pulse length that is available directly after reset.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_DFLT_RPL
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RPL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RPL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_DFLT_RPL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/**
 * \brief
 * Selects the timeout period that is available directly after reset. It
 * controls the reset value of the register. If WDT_HC_TOP is set to 1,
 * then the default timeout period is the only possible timeout period. Can
 * choose one of 16 values.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_DFLT_TOP
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * Describes the initial timeout period that is available directly after
 * reset.  It controls the reset value of the register. If WDT_HC_TOP is 1,
 * then the default initial time period is the only possible period.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_DFLT_TOP_INIT
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_DFLT_TOP_INIT(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * The Watchdog Timer counter width.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_PARAM_1 . WDT_CNT_WIDTH
 */
#define  VTSS_F_WDT_WDT_COMP_PARAM_1_WDT_CNT_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_WDT_WDT_COMP_PARAM_1_WDT_CNT_WIDTH     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_WDT_WDT_COMP_PARAM_1_WDT_CNT_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,24,5)


/**
 * \brief Component Version Register
Reset Value: WDT_VERSION_ID
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_VERSION
 */
#define VTSS_WDT_WDT_COMP_VERSION            VTSS_IOREG(VTSS_TO_WDT,0x3e)

/**
 * \brief
 * ASCII value for each number in the version, followed by *. For example,
 * 32_30_31_2A represents the version 2.01*.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_VERSION . WDT_COMP_VERSION
 */
#define  VTSS_F_WDT_WDT_COMP_VERSION_WDT_COMP_VERSION(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_VERSION_WDT_COMP_VERSION     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_VERSION_WDT_COMP_VERSION(x)  (x)


/**
 * \brief Component Type Register
 Reset Value: WDT_PERIPHERAL_ID
 *
 * \details
 * Register: \a WDT:WDT:WDT_COMP_TYPE
 */
#define VTSS_WDT_WDT_COMP_TYPE               VTSS_IOREG(VTSS_TO_WDT,0x3f)

/**
 * \brief
 * Designware Component Type number = 0x44_57_01_20. This assigned unique
 * hex value is constant, and is derived from the two ASCII letters "DW"
 * followed by a 16-bit unsigned number.
 *
 * \details
 * Field: ::VTSS_WDT_WDT_COMP_TYPE . WDT_COMP_TYPE
 */
#define  VTSS_F_WDT_WDT_COMP_TYPE_WDT_COMP_TYPE(x)  (x)
#define  VTSS_M_WDT_WDT_COMP_TYPE_WDT_COMP_TYPE     0xffffffff
#define  VTSS_X_WDT_WDT_COMP_TYPE_WDT_COMP_TYPE(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_WDT_H_ */
