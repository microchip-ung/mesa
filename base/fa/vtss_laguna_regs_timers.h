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

#ifndef _VTSS_LAGUNA_REGS_TIMERS_H_
#define _VTSS_LAGUNA_REGS_TIMERS_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a TIMERS
 *
 * DW_apb_timers memory map
 *
 ***********************************************************************/

/**
 * Register Group: \a TIMERS:TIMERS
 *
 * DW_apb_timers address block
 */


/**
 * \brief Value to be loaded into Timer N
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER1LOADCOUNT
 */
#define VTSS_TIMERS_TIMER1LOADCOUNT          VTSS_IOREG(VTSS_TO_TIMERS,0x0)

/**
 * \brief
 * Value to be loaded into Timer N. This is the value from which counting
 * commences. Any value written to this register is loaded into the
 * associated timer.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER1LOADCOUNT . TIMERNLOADCOUNT
 */
#define  VTSS_F_TIMERS_TIMER1LOADCOUNT_TIMERNLOADCOUNT(x)  (x)
#define  VTSS_M_TIMERS_TIMER1LOADCOUNT_TIMERNLOADCOUNT     0xffffffff
#define  VTSS_X_TIMERS_TIMER1LOADCOUNT_TIMERNLOADCOUNT(x)  (x)


/**
 * \brief Current value of Timer N
Reset value: (TIM_NEWMODE == 1) ?  '2 power ((TIMER_WIDTH_1)-1)' : 0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER1CURRENTVAL
 */
#define VTSS_TIMERS_TIMER1CURRENTVAL         VTSS_IOREG(VTSS_TO_TIMERS,0x1)

/**
 * \brief
 * Current Value of Timer N. When TIM_NEWMODE=0, This register is supported
 * only when timer_N_clk is synchronous to pclk. Reading this register when
 * using independent clocks results in an undefined value. When
 * TIM_NEWMODE=1, no restrictions apply.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER1CURRENTVAL . TIMERNCURRENTVALUE
 */
#define  VTSS_F_TIMERS_TIMER1CURRENTVAL_TIMERNCURRENTVALUE(x)  (x)
#define  VTSS_M_TIMERS_TIMER1CURRENTVAL_TIMERNCURRENTVALUE     0xffffffff
#define  VTSS_X_TIMERS_TIMER1CURRENTVAL_TIMERNCURRENTVALUE(x)  (x)


/**
 * \brief Control Register for Timer N. This register controls enabling, operating mode (free-running or defined-count), and interrupt mask of Timer N. You can program each Timer1ControlReg to enable or disable a specific timer and to control its mode of operation.
Reset value: ((TIM_0N100_PWM_MODE==1) && (TIMER_HAS_TOGGLE_1==1) && (TIMER_0N100_PWM_HC_EN==1)) ? 0x10 : 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER1CONTROLREG
 */
#define VTSS_TIMERS_TIMER1CONTROLREG         VTSS_IOREG(VTSS_TO_TIMERS,0x2)

/**
 * \brief
 * Timer enable bit for Timer N.
 *
 * \details
 * 0x0: Timer N is disabled
 * 0x1: Timer N is enabled

 *
 * Field: ::VTSS_TIMERS_TIMER1CONTROLREG . TIMER1CONTROLREG_TIMER_ENABLE
 */
#define  VTSS_F_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_ENABLE  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Timer mode for Timer N.
 * Note: You must set the Timer1LoadCount register to all 1s before
 * enabling the timer in free-running mode.
 *
 * \details
 * 0x0: Free Running mode of operation
 * 0x1: User-Defined mode of operation

 *
 * Field: ::VTSS_TIMERS_TIMER1CONTROLREG . TIMER1CONTROLREG_TIMER_MODE
 */
#define  VTSS_F_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_MODE  VTSS_BIT(1)
#define  VTSS_X_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Timer interrupt mask for Timer N.
 *
 * \details
 * 0x1: Timer N interrupt is   masked
 * 0x0: Timer N interrupt is unmasked

 *
 * Field: ::VTSS_TIMERS_TIMER1CONTROLREG . TIMER1CONTROLREG_TIMER_INTERRUPT_MASK
 */
#define  VTSS_F_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_INTERRUPT_MASK  VTSS_BIT(2)
#define  VTSS_X_TIMERS_TIMER1CONTROLREG_TIMER1CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Clears the interrupt from Timer N
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER1EOI
 */
#define VTSS_TIMERS_TIMER1EOI                VTSS_IOREG(VTSS_TO_TIMERS,0x3)

/**
 * \brief
 * Reading from this register returns all zeros (0) and clears the
 * interrupt from Timer N.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER1EOI . TIMERNEOI
 */
#define  VTSS_F_TIMERS_TIMER1EOI_TIMERNEOI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER1EOI_TIMERNEOI    VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER1EOI_TIMERNEOI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Contains the interrupt status for Timer N
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER1INTSTAT
 */
#define VTSS_TIMERS_TIMER1INTSTAT            VTSS_IOREG(VTSS_TO_TIMERS,0x4)

/**
 * \brief
 * Contains the interrupt status for Timer N.
 *
 * \details
 * 0x1: Timer N Interrupt is active
 * 0x0: Timer N Interrupt is inactive

 *
 * Field: ::VTSS_TIMERS_TIMER1INTSTAT . TIMERNINTSTATUS
 */
#define  VTSS_F_TIMERS_TIMER1INTSTAT_TIMERNINTSTATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER1INTSTAT_TIMERNINTSTATUS  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER1INTSTAT_TIMERNINTSTATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Name: Timer2 Load Count Register
  Size: 8-32 bits
  Address Offset: 20
  Read/Write Access: Read/Write
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER2LOADCOUNT
 */
#define VTSS_TIMERS_TIMER2LOADCOUNT          VTSS_IOREG(VTSS_TO_TIMERS,0x5)

/**
 * \brief
 * Value to be loaded into Timer2. This is the value from which counting
 *   commences. Any value written to this register is loaded into the
 * associated timer.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER2LOADCOUNT . TIMER2LOADCOUNT
 */
#define  VTSS_F_TIMERS_TIMER2LOADCOUNT_TIMER2LOADCOUNT(x)  (x)
#define  VTSS_M_TIMERS_TIMER2LOADCOUNT_TIMER2LOADCOUNT     0xffffffff
#define  VTSS_X_TIMERS_TIMER2LOADCOUNT_TIMER2LOADCOUNT(x)  (x)


/**
 * \brief Name: Timer2 Current Value
  Size: 8-32 bits
  Address Offset: 24
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER2CURRENTVAL
 */
#define VTSS_TIMERS_TIMER2CURRENTVAL         VTSS_IOREG(VTSS_TO_TIMERS,0x6)

/**
 * \brief
 * Current Value of Timer2. This register is supported only
 *   when timer_2_clk is synchronous to pclk. Reading this
 *   register when using independent clocks results in an
 *   undefined value.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER2CURRENTVAL . TIMER2CURRENTVAL
 */
#define  VTSS_F_TIMERS_TIMER2CURRENTVAL_TIMER2CURRENTVAL(x)  (x)
#define  VTSS_M_TIMERS_TIMER2CURRENTVAL_TIMER2CURRENTVAL     0xffffffff
#define  VTSS_X_TIMERS_TIMER2CURRENTVAL_TIMER2CURRENTVAL(x)  (x)


/**
 * \brief Name: Timer2 Control Register
  Size: 3 bits
  Address Offset: 28
  Read/Write Access: Read/Write
  This register controls enabling, operating mode (free-running or defined-count), and interrupt mask of
  Timer2. You can program each Timer2ControlReg to enable or disable a specific timer and to control
  its mode of operation.
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER2CONTROLREG
 */
#define VTSS_TIMERS_TIMER2CONTROLREG         VTSS_IOREG(VTSS_TO_TIMERS,0x7)

/**
 * \brief
 * Timer enable bit for Timer2.
 *   0: disable
 *   1: enable
 *
 * \details
 * 0x0: Timer2 is disabled
 * 0x1: Timer2 is enabled

 *
 * Field: ::VTSS_TIMERS_TIMER2CONTROLREG . TIMER2CONTROLREG_TIMER_ENABLE
 */
#define  VTSS_F_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_ENABLE  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Timer mode for Timer2.
 *   0: free-running mode
 *   1: user-defined count mode
 *   NOTE: You must set the Timer2LoadCount register to all 1s before
 *   enabling the timer in free-running mode.
 *
 * \details
 * 0x0: Free Running mode of operation
 * 0x1: User-Defined mode of operation

 *
 * Field: ::VTSS_TIMERS_TIMER2CONTROLREG . TIMER2CONTROLREG_TIMER_MODE
 */
#define  VTSS_F_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_MODE  VTSS_BIT(1)
#define  VTSS_X_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Timer interrupt mask for Timer2.
 *   0: not masked
 *   1: masked
 *
 * \details
 * 0x1: Timer2 interrupt is   masked
 * 0x0: Timer2 interrupt is unmasked

 *
 * Field: ::VTSS_TIMERS_TIMER2CONTROLREG . TIMER2CONTROLREG_TIMER_INTERRUPT_MASK
 */
#define  VTSS_F_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_INTERRUPT_MASK  VTSS_BIT(2)
#define  VTSS_X_TIMERS_TIMER2CONTROLREG_TIMER2CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Name: Timer2 End-of-Interrupt Register
  Size: 1 bit
  Address Offset: 32
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER2EOI
 */
#define VTSS_TIMERS_TIMER2EOI                VTSS_IOREG(VTSS_TO_TIMERS,0x8)

/**
 * \brief
 * Reading from this register
 *   returns all zeros (0) and clears the interrupt from Timer2.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER2EOI . TIMER2EOI
 */
#define  VTSS_F_TIMERS_TIMER2EOI_TIMER2EOI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER2EOI_TIMER2EOI    VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER2EOI_TIMER2EOI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Name: Timer2 Interrupt Status Register
  Size: 1 bit
  Address Offset: 36
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER2INTSTAT
 */
#define VTSS_TIMERS_TIMER2INTSTAT            VTSS_IOREG(VTSS_TO_TIMERS,0x9)

/**
 * \brief
 * Contains the interrupt status for Timer2.
 *
 * \details
 * 0x1: Timer2 Interrupt is   active
 * 0x0: Timer2 Interrupt is inactive

 *
 * Field: ::VTSS_TIMERS_TIMER2INTSTAT . TIMER2INTSTAT
 */
#define  VTSS_F_TIMERS_TIMER2INTSTAT_TIMER2INTSTAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER2INTSTAT_TIMER2INTSTAT  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER2INTSTAT_TIMER2INTSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Name: Timer3 Load Count Register
  Size: 8-32 bits
  Address Offset: 40
  Read/Write Access: Read/Write
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER3LOADCOUNT
 */
#define VTSS_TIMERS_TIMER3LOADCOUNT          VTSS_IOREG(VTSS_TO_TIMERS,0xa)

/**
 * \brief
 * Value to be loaded into Timer3. This is the value from which counting
 *   commences. Any value written to this register is loaded into the
 * associated timer.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER3LOADCOUNT . TIMER3LOADCOUNT
 */
#define  VTSS_F_TIMERS_TIMER3LOADCOUNT_TIMER3LOADCOUNT(x)  (x)
#define  VTSS_M_TIMERS_TIMER3LOADCOUNT_TIMER3LOADCOUNT     0xffffffff
#define  VTSS_X_TIMERS_TIMER3LOADCOUNT_TIMER3LOADCOUNT(x)  (x)


/**
 * \brief Name: Timer3 Current Value
  Size: 8-32 bits
  Address Offset: 44
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER3CURRENTVAL
 */
#define VTSS_TIMERS_TIMER3CURRENTVAL         VTSS_IOREG(VTSS_TO_TIMERS,0xb)

/**
 * \brief
 * Current Value of Timer3. This register is supported only
 *   when timer_3_clk is synchronous to pclk. Reading this
 *   register when using independent clocks results in an
 *   undefined value.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER3CURRENTVAL . TIMER3CURRENTVAL
 */
#define  VTSS_F_TIMERS_TIMER3CURRENTVAL_TIMER3CURRENTVAL(x)  (x)
#define  VTSS_M_TIMERS_TIMER3CURRENTVAL_TIMER3CURRENTVAL     0xffffffff
#define  VTSS_X_TIMERS_TIMER3CURRENTVAL_TIMER3CURRENTVAL(x)  (x)


/**
 * \brief Name: Timer3 Control Register
  Size: 4 bits
  Address Offset: 48
  Read/Write Access: Read/Write
  This register controls enabling, operating mode (free-running or defined-count), and interrupt mask of
  Timer3. You can program each Timer3ControlReg to enable or disable a specific timer and to control
  its mode of operation.
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER3CONTROLREG
 */
#define VTSS_TIMERS_TIMER3CONTROLREG         VTSS_IOREG(VTSS_TO_TIMERS,0xc)

/**
 * \brief
 * Timer enable bit for Timer3.
 *   0: disable
 *   1: enable
 *
 * \details
 * 0x0: Timer3 is disabled
 * 0x1: Timer3 is enabled

 *
 * Field: ::VTSS_TIMERS_TIMER3CONTROLREG . TIMER3CONTROLREG_TIMER_ENABLE
 */
#define  VTSS_F_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_ENABLE  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Timer mode for Timer3.
 *   0: free-running mode
 *   1: user-defined count mode
 *   NOTE: You must set the Timer3LoadCount register to all 1s before
 *   enabling the timer in free-running mode.
 *
 * \details
 * 0x0: Free Running mode of operation
 * 0x1: User-Defined mode of operation

 *
 * Field: ::VTSS_TIMERS_TIMER3CONTROLREG . TIMER3CONTROLREG_TIMER_MODE
 */
#define  VTSS_F_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_MODE  VTSS_BIT(1)
#define  VTSS_X_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Timer interrupt mask for Timer3.
 *   0: not masked
 *   1: masked
 *
 * \details
 * 0x1: Timer3 interrupt is   masked
 * 0x0: Timer3 interrupt is unmasked

 *
 * Field: ::VTSS_TIMERS_TIMER3CONTROLREG . TIMER3CONTROLREG_TIMER_INTERRUPT_MASK
 */
#define  VTSS_F_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_INTERRUPT_MASK  VTSS_BIT(2)
#define  VTSS_X_TIMERS_TIMER3CONTROLREG_TIMER3CONTROLREG_TIMER_INTERRUPT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Name: Timer3 End-of-Interrupt Register
  Size: 1 bit
  Address Offset: 52
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER3EOI
 */
#define VTSS_TIMERS_TIMER3EOI                VTSS_IOREG(VTSS_TO_TIMERS,0xd)

/**
 * \brief
 * Reading from this register
 *   returns all zeros (0) and clears the interrupt from Timer3.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMER3EOI . TIMER3EOI
 */
#define  VTSS_F_TIMERS_TIMER3EOI_TIMER3EOI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER3EOI_TIMER3EOI    VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER3EOI_TIMER3EOI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Name: Timer3 Interrupt Status Register
  Size: 1 bit
  Address Offset: 56
  Read/Write Access: Read
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMER3INTSTAT
 */
#define VTSS_TIMERS_TIMER3INTSTAT            VTSS_IOREG(VTSS_TO_TIMERS,0xe)

/**
 * \brief
 * Contains the interrupt status for Timer3.
 *
 * \details
 * 0x1: Timer3 Interrupt is   active
 * 0x0: Timer3 Interrupt is inactive

 *
 * Field: ::VTSS_TIMERS_TIMER3INTSTAT . TIMER3INTSTAT
 */
#define  VTSS_F_TIMERS_TIMER3INTSTAT_TIMER3INTSTAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TIMERS_TIMER3INTSTAT_TIMER3INTSTAT  VTSS_BIT(0)
#define  VTSS_X_TIMERS_TIMER3INTSTAT_TIMER3INTSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Contains the interrupt status of all timers in the component.
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMERSINTSTATUS
 */
#define VTSS_TIMERS_TIMERSINTSTATUS          VTSS_IOREG(VTSS_TO_TIMERS,0x28)

/**
 * \brief
 * Contains the interrupt status of all timers in the component. If a bit
 * of
 * this register is 0, then the corresponding timer interrupt is not active
 * and the corresponding interrupt could be on either the timer_intr bus
 * or the timer_intr_n bus, depending on the interrupt polarity you have
 * chosen. Similarly, if a bit of this register is 1, then the
 * corresponding
 * interrupt bit has been set in the relevant interrupt bus. In both cases,
 * the status reported is the status after the interrupt mask has been
 * applied. Reading from this register does not clear any active
 * interrupts.
 *
 * \details
 * 0x1: Timer_intr(_n) is active
 * 0x0: Timer_intr(_n) is inactive

 *
 * Field: ::VTSS_TIMERS_TIMERSINTSTATUS . TIMERSINTSTATUS
 */
#define  VTSS_F_TIMERS_TIMERSINTSTATUS_TIMERSINTSTATUS(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TIMERS_TIMERSINTSTATUS_TIMERSINTSTATUS     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TIMERS_TIMERSINTSTATUS_TIMERSINTSTATUS(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Returns all zeros (0) and clears all active interrupts.
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMERSEOI
 */
#define VTSS_TIMERS_TIMERSEOI                VTSS_IOREG(VTSS_TO_TIMERS,0x29)

/**
 * \brief
 * Reading this register returns all zeros (0) and clears all active
 * interrupts.
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMERSEOI . TIMERSEOI
 */
#define  VTSS_F_TIMERS_TIMERSEOI_TIMERSEOI(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TIMERS_TIMERSEOI_TIMERSEOI     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TIMERS_TIMERSEOI_TIMERSEOI(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Contains the unmasked interrupt status of all timers in the component.
Reset value: 0x0
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMERSRAWINTSTATUS
 */
#define VTSS_TIMERS_TIMERSRAWINTSTATUS       VTSS_IOREG(VTSS_TO_TIMERS,0x2a)

/**
 * \brief
 * The register contains the unmasked interrupt status of all timers in
 * the component.
 *
 * \details
 * 0x1: Raw Timer_intr(_n) is	active
 * 0x0: Raw Timer_intr(_n) is inactive

 *
 * Field: ::VTSS_TIMERS_TIMERSRAWINTSTATUS . TIMERSRAWINTSTAT
 */
#define  VTSS_F_TIMERS_TIMERSRAWINTSTATUS_TIMERSRAWINTSTAT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_TIMERS_TIMERSRAWINTSTATUS_TIMERSRAWINTSTAT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_TIMERS_TIMERSRAWINTSTATUS_TIMERSRAWINTSTAT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Current revision number of the DW_apb_timers component.
Reset value: TIM_VERSION_ID
 *
 * \details
 * Register: \a TIMERS:TIMERS:TIMERS_COMP_VERSION
 */
#define VTSS_TIMERS_TIMERS_COMP_VERSION      VTSS_IOREG(VTSS_TO_TIMERS,0x2b)

/**
 * \brief
 * Current revision number of the DW_apb_timers component.For the value,
 * see the releases table in the AMBA 2 release notes
 *
 * \details
 * Field: ::VTSS_TIMERS_TIMERS_COMP_VERSION . TIMERSCOMPVERSION
 */
#define  VTSS_F_TIMERS_TIMERS_COMP_VERSION_TIMERSCOMPVERSION(x)  (x)
#define  VTSS_M_TIMERS_TIMERS_COMP_VERSION_TIMERSCOMPVERSION     0xffffffff
#define  VTSS_X_TIMERS_TIMERS_COMP_VERSION_TIMERSCOMPVERSION(x)  (x)


#endif /* _VTSS_LAGUNA_REGS_TIMERS_H_ */
