// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_MCU_TIMER_H_
#define _VTSS_MALIBU25G_REGS_MCU_TIMER_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a MCU_TIMER
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_TIMER:TIMER
 *
 * MCU TIMER Register set
 */


/**
 * \brief Timer x Control Register (TMR_CTLx)
 *
 * \details
 * Register: \a MCU_TIMER:TIMER:TIMER_CTL
 *
 * @param gi Register: TIMER (??), 0-3
 */
#define VTSS_MCU_TIMER_TIMER_CTL(gi)         VTSS_IOREG_IX(VTSS_TO_MCU_TIMER,0x0,gi,32,0,0)

/**
 * \brief
 * Reflects the state of the TIMER_CLK_REQx output signal.0 = Indicates the
 * source clock domain can be turned 'off' when appropriate1 = Indicates
 * the source clock domain is required to be 'on.'
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . TIMER_CLK_REQ
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_TIMER_CLK_REQ(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_TIMER_CLK_REQ  VTSS_BIT(12)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_TIMER_CLK_REQ(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * This bit reflects the state of the SLEEP_ENABLEx signal. This signal
 * stops the timer and resets the internal counter to the value in the
 * Timer x Reload Register (TMR_RELOAD). Once the timer is disabled, the
 * TIMERx_CLK_REQ bit will be deasserted. This signal does not clear the
 * ENABLE bit ifit is set. If the timer is enabled, the counter will resume
 * operation when the SLEEP_ENABLEx signal is deasserted. The timer is held
 * in reset as long as the input signal is asserted.
 *
 * \details
 * 0 = Normal timer operation. In Normal Mode, the timer operates as
 * configured. When returning from a sleep mode, if enabled, the counter
 * will be restarted from the preload value.
 * 1 = Sleep Mode Requested. In Sleep Mode, the timer is reset, the counter
 * is disabled, and the TIMERx_CLK_REQ output is deasserted.
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . SLEEP_ENABLE
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_SLEEP_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_SLEEP_ENABLE  VTSS_BIT(11)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_SLEEP_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RESERVED0_B10
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RESERVED0_B10(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RESERVED0_B10  VTSS_BIT(10)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RESERVED0_B10(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Power Down.0 = The timer is in a running state (default).1 = The timer
 * is powered down and all clocks are gated.
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . PD
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_PD(x)     VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_PD        VTSS_BIT(9)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_PD(x)     VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RESERVED0_B8
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RESERVED0_B8(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RESERVED0_B8  VTSS_BIT(8)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RESERVED0_B8(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * This bit controls how the timer is reloaded on overflow or underflow in
 * Event and Timer modes, it has no effect in One Shot mode.
 *
 * \details
 * 0 = Roll timer over to FFFFh and continue counting when counting down
 * and rolls over to 0000h and continues counting when counting up.
 * 1 = Reload timer from Timer Reload Register and continue counting.
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RLOAD
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RLOAD(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RLOAD     VTSS_BIT(7)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RLOAD(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RESERVED0_B6
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RESERVED0_B6(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RESERVED0_B6  VTSS_BIT(6)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RESERVED0_B6(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * In Event mode this bit selects the timer count direction.
 *
 * \details
 * Event Mode:
 * 0 = The timer counts down
 * 1 = The timer counts up

 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . UPDN
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_UPDN(x)   VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_UPDN      VTSS_BIT(5)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_UPDN(x)   VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RESERVED0_B4
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RESERVED0_B4(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RESERVED0_B4  VTSS_BIT(4)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RESERVED0_B4(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * These bits control the timer mode.
 *
 * \details
 * 00 = Timer Mode
 * 01 = Event Mode
 * 10 = One Shot Mode
 * 11 = Reserved
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . MODE
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_MODE(x)   VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_MODE      VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_MODE(x)   VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * This bit stops the timer and resets the internal counter to the value in
 * the Timer x Reload Register (TMR_RELOAD). This bit also clears the
 * ENABLE bit if it is set. This bit is self clearing after the timer is
 * reset. Firmware must poll this RESET bit to determine when the reset is
 * completed.
 *
 * \details
 * 0 = Normal timer operation
 * 1 = Timer reset
 * When the RESET takes effect interrupts are blocked. Interrupts are not
 * blocked until RESET takes effect and the ENABLE bit is cleared. If
 * interrupts are not desired, firmware must mask interrupt in the
 * interrupt block.
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . RESET
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_RESET     VTSS_BIT(1)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This bit is used to start and stop the timer. This bit does not reset
 * the timer count but does reset the timer pulse output. This bit will be
 * cleared when the timer starts counting in One-Shot mode.
 *
 * \details
 * 0 = Timer is disabled
 * 1 = Timer is enabled
 * This bit is cleared after the RESET cycle is done.
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CTL . ENABLE
 */
#define  VTSS_F_MCU_TIMER_TIMER_CTL_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_TIMER_TIMER_CTL_ENABLE    VTSS_BIT(0)
#define  VTSS_X_MCU_TIMER_TIMER_CTL_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Timer x Clock and Event Control Register (TMR_CLK_EVT_CTLx)
 *
 * \details
 * Register: \a MCU_TIMER:TIMER:TIMER_CLK_EVT_CTL
 *
 * @param gi Register: TIMER (??), 0-3
 */
#define VTSS_MCU_TIMER_TIMER_CLK_EVT_CTL(gi)  VTSS_IOREG_IX(VTSS_TO_MCU_TIMER,0x0,gi,32,0,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CLK_EVT_CTL . RESERVED1_B11_B8
 */
#define  VTSS_F_MCU_TIMER_TIMER_CLK_EVT_CTL_RESERVED1_B11_B8(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_MCU_TIMER_TIMER_CLK_EVT_CTL_RESERVED1_B11_B8     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_MCU_TIMER_TIMER_CLK_EVT_CTL_RESERVED1_B11_B8(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * This bit is used to select the count source when the timer is operating
 * in eventmode.
 *
 * \details
 * 0 = Timer x-1 overflow is count source
 * 1 = Reserved
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CLK_EVT_CTL . EVENT
 */
#define  VTSS_F_MCU_TIMER_TIMER_CLK_EVT_CTL_EVENT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_TIMER_TIMER_CLK_EVT_CTL_EVENT  VTSS_BIT(7)
#define  VTSS_X_MCU_TIMER_TIMER_CLK_EVT_CTL_EVENT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * These bits are used to select the edge type that the timer counts. In
 * One-Shotmode these bits select which edge starts the timer.
 *
 * \details
 * Event:
 * 00 = Counts falling edges
 * 01 = Counts rising edges
 * 10 = Counts rising and falling edges
 * 11 = No event selected
 * One-shot:
 * 00 = Start counting on a falling edge
 * 01 = start counting on a rising edge
 * 10 = start counting on a rising or falling edge
 * 11 = start counting when the Enable bit is set
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CLK_EVT_CTL . EDGE
 */
#define  VTSS_F_MCU_TIMER_TIMER_CLK_EVT_CTL_EDGE(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_MCU_TIMER_TIMER_CLK_EVT_CTL_EDGE     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_MCU_TIMER_TIMER_CLK_EVT_CTL_EDGE(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * This field is the Timer Clock Select, used to determine the clock source
 * to the 16-bit timer.
 *
 * \details
 * 0000 = 60.00 MHz
 * 0001 = 30.00 MHz
 * 0010 = 15.00 MHz
 * 0011 = 7.5 MHz
 * 0100 = 3.75 MHz
 * 0101 = 1.88 MHz
 * 0110 = 0.94MHz
 * 0111 = 469 kHz
 * 1xxx = Reserved
 *
 * Field: ::VTSS_MCU_TIMER_TIMER_CLK_EVT_CTL . TCLK
 */
#define  VTSS_F_MCU_TIMER_TIMER_CLK_EVT_CTL_TCLK(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_MCU_TIMER_TIMER_CLK_EVT_CTL_TCLK     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_MCU_TIMER_TIMER_CLK_EVT_CTL_TCLK(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Timer x Reload Register (TMR_RELOAD)
 *
 * \details
 * Register: \a MCU_TIMER:TIMER:TIMER_RELOAD
 *
 * @param gi Register: TIMER (??), 0-3
 */
#define VTSS_MCU_TIMER_TIMER_RELOAD(gi)      VTSS_IOREG_IX(VTSS_TO_MCU_TIMER,0x0,gi,32,0,2)

/**
 * \brief
 * Used in Timer and One-Shot modes to set the lower limit of the timer. In
 * Event mode the Timer Reload register sets either the upper or lower
 * limit of the timer depending on if the timer is counting up or down.
 * Valid values are 0001h - FFFFh. If the timer is running, the reload
 * value will not be updated until the timer overflows or
 * underflows.Programming a 0000h as a preload value is not a valid count
 * value.
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_RELOAD . TIMER_RELOAD
 */
#define  VTSS_F_MCU_TIMER_TIMER_RELOAD_TIMER_RELOAD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCU_TIMER_TIMER_RELOAD_TIMER_RELOAD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCU_TIMER_TIMER_RELOAD_TIMER_RELOAD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Timer x Count Register (TMR_CNT)
 *
 * \details
 * Register: \a MCU_TIMER:TIMER:TIMER_CNT
 *
 * @param gi Register: TIMER (??), 0-3
 */
#define VTSS_MCU_TIMER_TIMER_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_MCU_TIMER,0x0,gi,32,0,3)

/**
 * \brief
 * This field returns the current value of the timer in all modes.
 *
 * \details
 * Field: ::VTSS_MCU_TIMER_TIMER_CNT . TIMER_CNT
 */
#define  VTSS_F_MCU_TIMER_TIMER_CNT_TIMER_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCU_TIMER_TIMER_CNT_TIMER_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCU_TIMER_TIMER_CNT_TIMER_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_MALIBU25G_REGS_MCU_TIMER_H_ */
