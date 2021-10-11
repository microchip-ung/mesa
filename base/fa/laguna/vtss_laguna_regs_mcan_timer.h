// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_MCAN_TIMER_H_
#define _VTSS_LAGUNA_REGS_MCAN_TIMER_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a MCAN_TIMER
 *
 * MCAN_TIMER
 *
 ***********************************************************************/

/**
 * Register Group: \a MCAN_TIMER:TIMER_REG_CHANNEL
 *
 * Timer Register group
 */


/**
 * \brief TC Channel Control Register
 *
 * \details
 * TC Channel Control Register
 * This register can only be written if the WPCREN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_CCR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_CCR(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,0)

/**
 * \brief
 * Software Trigger Command
 *
 * \details
 * 0 No effect.
 * 1 Enables the clock if CLKDIS is not 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CCR . SWTRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CCR_SWTRG(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_CCR_SWTRG       VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_CCR_SWTRG(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Counter Clock Disable Command
 *
 * \details
 * 0 No effect.
 * 1 Disables the clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CCR . CLKDIS
 */
#define  VTSS_F_MCAN_TIMER_TC_CCR_CLKDIS(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_CCR_CLKDIS      VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_CCR_CLKDIS(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Counter Clock Enable Command
 *
 * \details
 * 0 No effect.
 * 1 Enables the clock if CLKDIS is not 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CCR . CLKEN
 */
#define  VTSS_F_MCAN_TIMER_TC_CCR_CLKEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_CCR_CLKEN       VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_CCR_CLKEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Channel Mode Register Capture Mode
 *
 * \details
 * TC Channel Mode Register Capture Mode
 * This register can be written only if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_CMR_CAPTURE
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_CMR_CAPTURE(gi)   VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,1)

/**
 * \brief
 * Loading Edge Subsampling Ratio
 *
 * \details
 * 0 ONE Load a Capture register each selected edge.
 * 1 HALF Load a Capture register every 2 selected edges.
 * 2 FOURTH Load a Capture register every 4 selected edges.
 * 3 EIGHTH Load a Capture register every 8 selected edges.
 * 4 SIXTEENTH Load a Capture register every 16 selected edges.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . SBSMPLR
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_SBSMPLR(x)  VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_SBSMPLR     VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_SBSMPLR(x)  VTSS_EXTRACT_BITFIELD(x,20,3)

/**
 * \brief
 * RB Loading Edge Selection
 *
 * \details
 * 0 NONE None
 * 1 RISING Rising edge of TIOAx
 * 2 FALLING Falling edge of TIOAx
 * 3 EDGE Each edge of TIOAx
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . LDRB
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_LDRB(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_LDRB     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_LDRB(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * RA Loading Edge Selection
 *
 * \details
 * 0 NONE None
 * 1 RISING Rising edge of TIOAx
 * 2 FALLING Falling edge of TIOAx
 * 3 EDGE Each edge of TIOAx
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . LDRA
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_LDRA(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_LDRA     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_LDRA(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Waveform Mode
 *
 * \details
 * 0 Capture mode is enabled.
 * 1 Capture mode is disabled (Waveform mode is enabled).
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . WAVE_C
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_WAVE_C(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_WAVE_C  VTSS_BIT(15)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_WAVE_C(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * RC Compare Trigger Enable
 *
 * \details
 * 0 RC Compare has no effect on the counter and its clock.
 * 1 RC Compare resets the counter and starts the counter clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . CPCTRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_CPCTRG(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_CPCTRG  VTSS_BIT(14)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_CPCTRG(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * TIOAx or TIOBx External Trigger Selection
 *
 * \details
 * 0 TIOBx is used as an external trigger.
 * 1 TIOAx is used as an external trigger.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . ABETRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_ABETRG(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_ABETRG  VTSS_BIT(10)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_ABETRG(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * External Trigger Edge Selection
 *
 * \details
 * 0 NONE The clock is not gated by an external signal.
 * 1 RISING Rising edge
 * 2 FALLING Falling edge
 * 3 EDGE Each edge
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . ETRGEDG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_ETRGEDG(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_ETRGEDG     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_ETRGEDG(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Counter Clock Stopped with RB Loading
 *
 * \details
 * 0 Counter clock is not stopped when RB loading occurs.
 * 1 Counter clock is stopped when RB loading occurs.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . LDBSTOP
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_LDBSTOP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_LDBSTOP  VTSS_BIT(6)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_LDBSTOP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Burst Signal Selection
 *
 * \details
 * 0 NONE The clock is not gated by an external signal.
 * 1 XC0 XC0 is ANDed with the selected clock.
 * 2 XC1 XC1 is ANDed with the selected clock.
 * 3 XC2 XC2 is ANDed with the selected clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . BURST_C
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_BURST_C(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_BURST_C     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_BURST_C(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Clock Invert
 *
 * \details
 * 0 Counter is incremented on rising edge of the clock.
 * 1 Counter is incremented on falling edge of the clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . CLKI_C
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_CLKI_C(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_CLKI_C  VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_CLKI_C(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Clock Selection
 *
 * \details
 * 0 TIMER_CLOCK1 Clock selected: internal GCLK [35], GCLK [36] clock
 * signal (from PMC)
 * 1 TIMER_CLOCK2 Clock selected: internal System bus clock divided by 8
 * clock signal (from PMC)
 * 2 TIMER_CLOCK3 Clock selected: internal System bus clock divided by 32
 * clock signal (from PMC)
 * 3 TIMER_CLOCK4 Clock selected: internal System bus clock divided by 128
 * clock signal (from PMC)
 * 4 TIMER_CLOCK5 Clock selected: internal slow_clock clock signal (from
 * PMC)
 * 5 XC0 Clock selected: XC0
 * 6 XC1 Clock selected: XC1
 * 7 XC2 Clock selected: XC2
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_CAPTURE . TCCLKS_C
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_CAPTURE_TCCLKS_C(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_MCAN_TIMER_TC_CMR_CAPTURE_TCCLKS_C     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_MCAN_TIMER_TC_CMR_CAPTURE_TCCLKS_C(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief TC Channel Mode Register: Waveform Mode
 *
 * \details
 * TC Channel Mode Register: Waveform Mode
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_CMR_WAVE
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_CMR_WAVE(gi)      VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,1)

/**
 * \brief
 * Software Trigger Effect on TIOBx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . BSWTRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_BSWTRG(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_BSWTRG     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_BSWTRG(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/**
 * \brief
 * External Event Effect on TIOBx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . BEEVT
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_BEEVT(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_BEEVT     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_BEEVT(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/**
 * \brief
 * RC Compare Effect on TIOBx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . BCPC
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_BCPC(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_BCPC     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_BCPC(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/**
 * \brief
 * RB Compare Effect on TIOBx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . BCPB
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_BCPB(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_BCPB     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_BCPB(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * Software Trigger Effect on TIOAx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . ASWTRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_ASWTRG(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_ASWTRG     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_ASWTRG(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/**
 * \brief
 * External Event Effect on TIOAx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . AEEVT
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_AEEVT(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_AEEVT     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_AEEVT(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/**
 * \brief
 * RC Compare Effect on TIOAx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . ACPC
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_ACPC(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_ACPC     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_ACPC(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * RA Compare Effect on TIOAx
 *
 * \details
 * 0 NONE
 * 1 SET
 * 2 CLEAR
 * 3 TOGGLE
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . ACPA
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_ACPA(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_ACPA     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_ACPA(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Waveform Mode
 *
 * \details
 * 0 Waveform mode is disabled (Capture mode is enabled).
 * 1 Waveform mode is enabled.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . WAVE_W
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_WAVE_W(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_WAVE_W  VTSS_BIT(15)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_WAVE_W(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Waveform Selection
 *
 * \details
 * 0 UP UP mode without automatic trigger on RC Compare
 * 1 UPDOWN UPDOWN mode without automatic trigger on RC Compare
 * 2 UP_RC UP mode with automatic trigger on RC Compare
 * 3 UPDOWN_RC UPDOWN mode with automatic trigger on RC Compare
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . WAVSEL
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_WAVSEL(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_WAVSEL     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_WAVSEL(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * External Event Trigger EnableWhatever the value programmed in ENETRG,
 * the selected external event only controls the TIOAx output and TIOBxif
 * not used as input (trigger event input or other input used).
 *
 * \details
 * 0 The external event has no effect on the counter and its clock.
 * 1 The external event resets the counter and starts the counter clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . ENETRG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_ENETRG(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_ENETRG  VTSS_BIT(12)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_ENETRG(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * External Event SelectionSignal selected as external event.Note: If TIOB
 * is chosen as the external event signal, it is configured as an input and
 * no longer generates waveformsand subsequently no IRQs.
 *
 * \details
 * 0 TIOB Input
 * 1  XC0 Output
 * 2  XC1 Output
 * 3  XC2 Output
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . EEVT
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_EEVT(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_EEVT     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_EEVT(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * External Event Edge Selection
 *
 * \details
 * 0 NONE None
 * 1 RISING Rising edge
 * 2 FALLING Falling edge
 * 3 EDGE Each edge
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . EEVTEDG
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_EEVTEDG(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_EEVTEDG     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_EEVTEDG(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * Counter Clock Disable with RC Compare
 *
 * \details
 * 0 Counter clock is not disabled when counter reaches RC.
 * 1 Counter clock is disabled when counter reaches RC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . CPCDIS
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_CPCDIS(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_CPCDIS  VTSS_BIT(7)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_CPCDIS(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Counter Clock Stopped with RC Compare
 *
 * \details
 * 0 Counter clock is not stopped when counter reaches RC.
 * 1 Counter clock is stopped when counter reaches RC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . CPCSTOP
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_CPCSTOP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_CPCSTOP  VTSS_BIT(6)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_CPCSTOP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Burst Signal Selection
 *
 * \details
 * 0 NONE The clock is not gated by an external signal.
 * 1 XC0 XC0 is ANDed with the selected clock.
 * 2 XC1 XC1 is ANDed with the selected clock.
 * 3 XC2 XC2 is ANDed with the selected clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . BURST_W
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_BURST_W(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_BURST_W     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_BURST_W(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Clock Invert
 *
 * \details
 * 0 Counter is incremented on rising edge of the clock.
 * 1 Counter is incremented on falling edge of the clock.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . CLKI_W
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_CLKI_W(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_CLKI_W  VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_CLKI_W(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Clock SelectionTo operate at maximum peripheral clock frequency, see
 * TC_EMRx.
 *
 * \details
 * 0 TIMER_CLOCK1 Clock selected: internal GCLK [35], GCLK [36] clock
 * signal (from PMC)
 * 1 TIMER_CLOCK2 Clock selected: internal System bus clock divided by 8
 * clock signal (from PMC)
 * 2 TIMER_CLOCK3 Clock selected: internal System bus clock divided by 32
 * clock signal (from PMC)
 * 3 TIMER_CLOCK4 Clock selected: internal System bus clock divided by 128
 * clock signal (from PMC)
 * 4 TIMER_CLOCK5 Clock selected: internal slow_clock clock signal (from
 * PMC)
 * 5 XC0 Clock selected: XC0
 * 6 XC1 Clock selected: XC1
 * 7 XC2 Clock selected: XC2
 *
 * Field: ::VTSS_MCAN_TIMER_TC_CMR_WAVE . TCCLKS_W
 */
#define  VTSS_F_MCAN_TIMER_TC_CMR_WAVE_TCCLKS_W(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_MCAN_TIMER_TC_CMR_WAVE_TCCLKS_W     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_MCAN_TIMER_TC_CMR_WAVE_TCCLKS_W(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief TC Stepper Motor Mode Register
 *
 * \details
 * TC Stepper Motor Mode Register
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_SMMR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_SMMR(gi)          VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,2)

/**
 * \brief
 * Down Count
 *
 * \details
 * 0 Up counter.
 * 1 Down counter.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SMMR . DOWN
 */
#define  VTSS_F_MCAN_TIMER_TC_SMMR_DOWN(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_SMMR_DOWN       VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_SMMR_DOWN(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Gray Count Enable
 *
 * \details
 * 0 TIOAx [x=0..2] and TIOBx [x=0..2] are driven by internal counter of
 * channel x.
 * 1 TIOAx [x=0..2] and TIOBx [x=0..2] are driven by a 2-bit Gray counter.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SMMR . GCEN
 */
#define  VTSS_F_MCAN_TIMER_TC_SMMR_GCEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_SMMR_GCEN       VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_SMMR_GCEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Register AB
 *
 * \details
 * TC Register AB
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_RAB
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_RAB(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,3)

/**
 * \brief
 * Register A or Register BRAB contains the next unread capture Register A
 * or Register B value in real time. It is usually read by the DMA aftera
 * request due to a valid load edge on TIOAx.When DMA is used, the RAB
 * register address must be configured as source address of the transfer
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_RAB . TC_RAB
 */
#define  VTSS_F_MCAN_TIMER_TC_RAB_TC_RAB(x)   (x)
#define  VTSS_M_MCAN_TIMER_TC_RAB_TC_RAB      0xffffffff
#define  VTSS_X_MCAN_TIMER_TC_RAB_TC_RAB(x)   (x)


/**
 * \brief TC Counter Value Register
 *
 * \details
 * TC Counter Value Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_CV
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_CV(gi)            VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,4)

/**
 * \brief
 * Counter ValueCV contains the counter value in real time.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_CV . TC_CV
 */
#define  VTSS_F_MCAN_TIMER_TC_CV_TC_CV(x)     (x)
#define  VTSS_M_MCAN_TIMER_TC_CV_TC_CV        0xffffffff
#define  VTSS_X_MCAN_TIMER_TC_CV_TC_CV(x)     (x)


/**
 * \brief TC Register A
 *
 * \details
 * TC Register A
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_RA
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_RA(gi)            VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,5)

/**
 * \brief
 * Register ARA contains the Register A value in real time.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_RA . RA
 */
#define  VTSS_F_MCAN_TIMER_TC_RA_RA(x)        (x)
#define  VTSS_M_MCAN_TIMER_TC_RA_RA           0xffffffff
#define  VTSS_X_MCAN_TIMER_TC_RA_RA(x)        (x)


/**
 * \brief TC Register B
 *
 * \details
 * TC Register B
 * This register has access Read-only if TC_CMRx.WAVE = 0, Read/Write if
 * TC_CMRx.WAVE = 1.
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_RB
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_RB(gi)            VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,6)

/**
 * \brief
 * Register BRB contains the Register B value in real time.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_RB . RB
 */
#define  VTSS_F_MCAN_TIMER_TC_RB_RB(x)        (x)
#define  VTSS_M_MCAN_TIMER_TC_RB_RB           0xffffffff
#define  VTSS_X_MCAN_TIMER_TC_RB_RB(x)        (x)


/**
 * \brief TC Register C
 *
 * \details
 * TC Register C
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_RC
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_RC(gi)            VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,7)

/**
 * \brief
 * Register CRC contains the Register C value in real time.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_RC . RC
 */
#define  VTSS_F_MCAN_TIMER_TC_RC_RC(x)        (x)
#define  VTSS_M_MCAN_TIMER_TC_RC_RC           0xffffffff
#define  VTSS_X_MCAN_TIMER_TC_RC_RC(x)        (x)


/**
 * \brief TC Interrupt Status Register
 *
 * \details
 * TC Interrupt Status Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_SR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_SR(gi)            VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,8)

/**
 * \brief
 * TIOBx Mirror
 *
 * \details
 * 0 TIOBx is low. If TC_CMRx.WAVE = 0, TIOBx pin is low. If TC_CMRx.WAVE =
 * 1, TIOBx is driven low.
 * 1 TIOBx is high. If TC_CMRx.WAVE = 0, TIOBx pin is high. If TC_CMRx.WAVE
 * = 1, TIOBx is driven
 * high.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . MTIOB
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_MTIOB(x)     VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_MTIOB        VTSS_BIT(18)
#define  VTSS_X_MCAN_TIMER_TC_SR_MTIOB(x)     VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * TIOAx Mirror
 *
 * \details
 * 0 TIOAx is low. If TC_CMRx.WAVE = 0, TIOAx pin is low. If TC_CMRx.WAVE =
 * 1, TIOAx is driven low.
 * 1 TIOAx is high. If TC_CMRx.WAVE = 0, TIOAx pin is high. If TC_CMRx.WAVE
 * = 1, TIOAx is driven
 * high.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . MTIOA
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_MTIOA(x)     VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_MTIOA        VTSS_BIT(17)
#define  VTSS_X_MCAN_TIMER_TC_SR_MTIOA(x)     VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Clock Enabling Status
 *
 * \details
 * 0 Clock is disabled.
 * 1 Clock is enabled.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . CLKSTA
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_CLKSTA(x)    VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_CLKSTA       VTSS_BIT(16)
#define  VTSS_X_MCAN_TIMER_TC_SR_CLKSTA(x)    VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * External Trigger Status (cleared on read)
 *
 * \details
 * 0 External trigger has not occurred since the last read of the Status
 * Register.
 * 1 External trigger has occurred since the last read of the Status
 * Register.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . ETRGS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_ETRGS(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_ETRGS        VTSS_BIT(7)
#define  VTSS_X_MCAN_TIMER_TC_SR_ETRGS(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RA Loading Status (cleared on read)
 *
 * \details
 * 0 RA Load has not occurred since the last read of the Status Register or
 * TC_CMRx.WAVE = 1.
 * 1 RA Load has occurred since the last read of the Status Register, if
 * TC_CMRx.WAVE = 0.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . LDRAS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_LDRAS(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_LDRAS        VTSS_BIT(5)
#define  VTSS_X_MCAN_TIMER_TC_SR_LDRAS(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RC Compare Status (cleared on read)
 *
 * \details
 * 0 RC Compare has not occurred since the last read of the Status
 * Register.
 * 1 RC Compare has occurred since the last read of the Status Register.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . CPCS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_CPCS(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_CPCS         VTSS_BIT(4)
#define  VTSS_X_MCAN_TIMER_TC_SR_CPCS(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RB Compare Status (cleared on read)
 *
 * \details
 * 0 RB Compare has not occurred since the last read of the Status Register
 * or TC_CMRx.WAVE = 0.
 * 1 RB Compare has occurred since the last read of the Status Register, if
 * TC_CMRx.WAVE = 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . CPBS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_CPBS(x)      VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_CPBS         VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_SR_CPBS(x)      VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * CPAS RA Compare Status (cleared on read)
 *
 * \details
 * 0 RA Compare has not occurred since the last read of the Status Register
 * or TC_CMRx.WAVE = 0.
 * 1 RA Compare has occurred since the last read of the Status Register, if
 * TC_CMRx.WAVE = 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . CPAS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_CPAS(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_CPAS         VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_SR_CPAS(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Load Overrun Status (cleared on read)
 *
 * \details
 * 0 Load overrun has not occurred since the last read of the Status
 * Register or TC_CMRx.WAVE = 1.
 * 1 RA or RB have been loaded at least twice without any read of the
 * corresponding register since the last
 * read of the Status Register, if TC_CMRx.WAVE = 0.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . LOVRS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_LOVRS(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_LOVRS        VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_SR_LOVRS(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Counter Overflow Status (cleared on read)
 *
 * \details
 * 0 No counter overflow has occurred since the last read of the Status
 * Register.
 * 1 A counter overflow has occurred since the last read of the Status
 * Register.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_SR . COVFS
 */
#define  VTSS_F_MCAN_TIMER_TC_SR_COVFS(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_SR_COVFS        VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_SR_COVFS(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Interrupt Enable Register
 *
 * \details
 * TC Interrupt Enable Register
 * 0: No effect.
 * 1: Enables the corresponding interrupt.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_IER
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_IER(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,9)

/**
 * \brief
 * External Trigger
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . ETRGS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_ETRGS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_ETRGS_IE    VTSS_BIT(7)
#define  VTSS_X_MCAN_TIMER_TC_IER_ETRGS_IE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RB Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . LDRBS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_LDRBS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_LDRBS_IE    VTSS_BIT(6)
#define  VTSS_X_MCAN_TIMER_TC_IER_LDRBS_IE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RA Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . LDRAS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_LDRAS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_LDRAS_IE    VTSS_BIT(5)
#define  VTSS_X_MCAN_TIMER_TC_IER_LDRAS_IE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RC Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . CPCS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_CPCS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_CPCS_IE     VTSS_BIT(4)
#define  VTSS_X_MCAN_TIMER_TC_IER_CPCS_IE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RB Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . CPBS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_CPBS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_CPBS_IE     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_IER_CPBS_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RA Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . CPAS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_CPAS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_CPAS_IE     VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_IER_CPAS_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Load Overrun
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . LOVRS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_LOVRS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_LOVRS_IE    VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_IER_LOVRS_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Counter Overflow
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IER . COVFS_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_IER_COVFS_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_IER_COVFS_IE    VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_IER_COVFS_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Interrupt Disable Register
 *
 * \details
 * TC Interrupt Disable Register
 * 0: No effect.
 * 1: Enables the corresponding interrupt.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_IDR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_IDR(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,10)

/**
 * \brief
 * External Trigger
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . ETRGS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_ETRGS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_ETRGS_ID    VTSS_BIT(7)
#define  VTSS_X_MCAN_TIMER_TC_IDR_ETRGS_ID(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RB Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . LDRBS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_LDRBS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_LDRBS_ID    VTSS_BIT(6)
#define  VTSS_X_MCAN_TIMER_TC_IDR_LDRBS_ID(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RA Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . LDRAS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_LDRAS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_LDRAS_ID    VTSS_BIT(5)
#define  VTSS_X_MCAN_TIMER_TC_IDR_LDRAS_ID(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RC Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . CPCS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_CPCS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_CPCS_ID     VTSS_BIT(4)
#define  VTSS_X_MCAN_TIMER_TC_IDR_CPCS_ID(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RB Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . CPBS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_CPBS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_CPBS_ID     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_IDR_CPBS_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RA Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . CPAS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_CPAS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_CPAS_ID     VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_IDR_CPAS_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Load Overrun
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . LOVRS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_LOVRS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_LOVRS_ID    VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_IDR_LOVRS_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Counter Overflow
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IDR . COVFS_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_IDR_COVFS_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_IDR_COVFS_ID    VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_IDR_COVFS_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Interrupt Mask Register
 *
 * \details
 * TC Interrupt Mask Register
 * 0: No effect.
 * 1: Enables the corresponding interrupt.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_IMR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_IMR(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,11)

/**
 * \brief
 * External Trigger
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . ETRGS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_ETRGS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_ETRGS_IM    VTSS_BIT(7)
#define  VTSS_X_MCAN_TIMER_TC_IMR_ETRGS_IM(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * RB Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . LDRBS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_LDRBS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_LDRBS_IM    VTSS_BIT(6)
#define  VTSS_X_MCAN_TIMER_TC_IMR_LDRBS_IM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RA Loading
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . LDRAS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_LDRAS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_LDRAS_IM    VTSS_BIT(5)
#define  VTSS_X_MCAN_TIMER_TC_IMR_LDRAS_IM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * RC Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . CPCS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_CPCS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_CPCS_IM     VTSS_BIT(4)
#define  VTSS_X_MCAN_TIMER_TC_IMR_CPCS_IM(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RB Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . CPBS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_CPBS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_CPBS_IM     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_IMR_CPBS_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * RA Compare
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . CPAS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_CPAS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_CPAS_IM     VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_IMR_CPAS_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Load Overrun
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . LOVRS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_LOVRS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_LOVRS_IM    VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_IMR_LOVRS_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Counter Overflow
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_IMR . COVFS_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_IMR_COVFS_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_IMR_COVFS_IM    VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_IMR_COVFS_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Extended Mode Register
 *
 * \details
 * TC Extended Mode Register
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CHANNEL:TC_EMR
 *
 * @param gi Register: TIMER_REG_CHANNEL (??), 0-2
 */
#define VTSS_MCAN_TIMER_TC_EMR(gi)           VTSS_IOREG_IX(VTSS_TO_MCAN_TIMER,0x0,gi,16,0,12)

/**
 * \brief
 * No Divided Clock
 *
 * \details
 * 0 The selected clock is defined by field TCCLKS in TC_CMRx.
 * 1 The selected clock is peripheral clock and TCCLKS field (TC_CMRx) has
 * no effect.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_EMR . NODIVCLK
 */
#define  VTSS_F_MCAN_TIMER_TC_EMR_NODIVCLK(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_TIMER_TC_EMR_NODIVCLK    VTSS_BIT(8)
#define  VTSS_X_MCAN_TIMER_TC_EMR_NODIVCLK(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Trigger Source for Input B
 *
 * \details
 * 0 EXTERNAL_TIOBx The trigger/capture input B is driven by external pin
 * TIOBx
 * 1 PWMx For TC0_CH0/1/2, TC1_CH3/4: The trigger/capture input B is driven
 * internally by
 * the comparator output (see Synchronization with PWM) of the PWMx.
 * For TC1_CH5: The trigger/capture input B is driven internally by the
 * GTSUCOMP
 * signal of the Ethernet MAC (GMAC).
 *
 * Field: ::VTSS_MCAN_TIMER_TC_EMR . TRIGSRCB
 */
#define  VTSS_F_MCAN_TIMER_TC_EMR_TRIGSRCB(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCAN_TIMER_TC_EMR_TRIGSRCB     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCAN_TIMER_TC_EMR_TRIGSRCB(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * Trigger Source for Input A
 *
 * \details
 * 0 EXTERNAL_TIOAx The trigger/capture input A is driven by external pin
 * TIOAx
 * 1 PWMx The trigger/capture input A is driven internally by PWMx
 *
 * Field: ::VTSS_MCAN_TIMER_TC_EMR . TRIGSRCA
 */
#define  VTSS_F_MCAN_TIMER_TC_EMR_TRIGSRCA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MCAN_TIMER_TC_EMR_TRIGSRCA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MCAN_TIMER_TC_EMR_TRIGSRCA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a MCAN_TIMER:TIMER_REG_CFG
 *
 * Not documented
 */


/**
 * \brief TC Block Control Register
 *
 * \details
 * TC Block Control Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_BCR
 */
#define VTSS_MCAN_TIMER_TC_BCR               VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x30)

/**
 * \brief
 * Synchro Command
 *
 * \details
 * 0 No effect.
 * 1 Asserts the SYNC signal which generates a software trigger
 * simultaneously for each of the channels.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BCR . SYNC
 */
#define  VTSS_F_MCAN_TIMER_TC_BCR_SYNC(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_BCR_SYNC        VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_BCR_SYNC(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Block Mode Register
 *
 * \details
 * TC Block Mode Register
 * This register can only be written if the WPEN bit is cleared in the TC
 * Write Protection Mode Register.
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_BMR
 */
#define VTSS_MCAN_TIMER_TC_BMR               VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x31)

/**
 * \brief
 * Maximum Consecutive Missing Pulses
 *
 * \details
 * 0 The flag MPE in TC_QISR never rises.
 * 1-15 Defines the number of consecutive missing pulses before a flag
 * report.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . MAXCMP
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_MAXCMP(x)   VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_MCAN_TIMER_TC_BMR_MAXCMP      VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_MCAN_TIMER_TC_BMR_MAXCMP(x)   VTSS_EXTRACT_BITFIELD(x,26,4)

/**
 * \brief
 * Maximum FilterPulses with a period shorter than MAXFILT+1 peripheral
 * clock cycles are discarded. For more details on MAXFILTconstraints, see
 * Input Preprocessing.
 *
 * \details
 * 1-63 Defines the filtering capabilities.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . MAXFILT
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_MAXFILT(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_MCAN_TIMER_TC_BMR_MAXFILT     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_MCAN_TIMER_TC_BMR_MAXFILT(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/**
 * \brief
 * AutoCorrection of missing pulses
 *
 * \details
 * 0 (DISABLED): The detection and autocorrection function is disabled.
 * 1 (ENABLED): The detection and autocorrection function is enabled.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . AUTOC
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_AUTOC(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_AUTOC       VTSS_BIT(18)
#define  VTSS_X_MCAN_TIMER_TC_BMR_AUTOC(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Index Pin is PHB Pin
 *
 * \details
 * 0 IDX pin of the rotary sensor must drive TIOA1.
 * 1 IDX pin of the rotary sensor must drive TIOB0.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . IDXPHB
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_IDXPHB(x)   VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_IDXPHB      VTSS_BIT(17)
#define  VTSS_X_MCAN_TIMER_TC_BMR_IDXPHB(x)   VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Swap PHA and PHB
 *
 * \details
 * 0 No swap between PHA and PHB.
 * 1 Swap PHA and PHB internally, prior to driving the QDEC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . SWAP
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_SWAP(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_SWAP        VTSS_BIT(16)
#define  VTSS_X_MCAN_TIMER_TC_BMR_SWAP(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Inverted Index
 *
 * \details
 * 0 IDX (TIOA1) is directly driving the QDEC.
 * 1 IDX is inverted before driving the QDEC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . INVIDX
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_INVIDX(x)   VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_INVIDX      VTSS_BIT(15)
#define  VTSS_X_MCAN_TIMER_TC_BMR_INVIDX(x)   VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Inverted PHB
 *
 * \details
 * 0 PHB (TIOB0) is directly driving the QDEC.
 * 1 PHB is inverted before driving the QDEC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . INVB
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_INVB(x)     VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_INVB        VTSS_BIT(14)
#define  VTSS_X_MCAN_TIMER_TC_BMR_INVB(x)     VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Inverted PHA
 *
 * \details
 * 0 PHA (TIOA0) is directly driving the QDEC.
 * 1 PHA is inverted before driving the QDEC.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . INVA
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_INVA(x)     VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_INVA        VTSS_BIT(13)
#define  VTSS_X_MCAN_TIMER_TC_BMR_INVA(x)     VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Edge on PHA Count Mode
 *
 * \details
 * 0 Edges are detected on PHA only.
 * 1 Edges are detected on both PHA and PHB.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . EDGPHA
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_EDGPHA(x)   VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_EDGPHA      VTSS_BIT(12)
#define  VTSS_X_MCAN_TIMER_TC_BMR_EDGPHA(x)   VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Quadrature Decoding Transparent
 *
 * \details
 * 0 Full quadrature decoding logic is active (direction change detected).
 * 1 Quadrature decoding logic is inactive (direction change inactive) but
 * input filtering and edge detection
 * are performed.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . QDTRANS
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_QDTRANS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_QDTRANS     VTSS_BIT(11)
#define  VTSS_X_MCAN_TIMER_TC_BMR_QDTRANS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Speed Enabled
 *
 * \details
 * 0 Disabled.
 * 1 Enables the speed measure on channel 0, the time base being provided
 * by channel 2.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . SPEEDEN
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_SPEEDEN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_SPEEDEN     VTSS_BIT(10)
#define  VTSS_X_MCAN_TIMER_TC_BMR_SPEEDEN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Position Enabled
 *
 * \details
 * 0 Disable position.
 * 1 Enables the position measure on channel 0 and 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . POSEN
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_POSEN(x)    VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_POSEN       VTSS_BIT(9)
#define  VTSS_X_MCAN_TIMER_TC_BMR_POSEN(x)    VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Quadrature Decoder EnabledQuadrature decoding (direction change) can be
 * disabled using QDTRANS bit.One of the POSEN or SPEEDEN bits must be also
 * enabled.
 *
 * \details
 * 0 Disabled.
 * 1 Enables the QDEC (filter, edge detection and quadrature decoding).
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . QDEN
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_QDEN(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_TIMER_TC_BMR_QDEN        VTSS_BIT(8)
#define  VTSS_X_MCAN_TIMER_TC_BMR_QDEN(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * External Clock Signal 2 Selection
 *
 * \details
 * 0 TCLK2 Signal connected to XC2: TCLK2
 * 1  Reserved
 * 2 TIOA0 Signal connected to XC2: TIOA0
 * 3 TIOA1 Signal connected to XC2: TIOA1
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . TC2XC2S
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_TC2XC2S(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_MCAN_TIMER_TC_BMR_TC2XC2S     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_MCAN_TIMER_TC_BMR_TC2XC2S(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * External Clock Signal 1 Selection
 *
 * \details
 * 0 TCLK1 Signal connected to XC1: TCLK1
 * 1 Reserved
 * 2 TIOA0 Signal connected to XC1: TIOA0
 * 3 TIOA2 Signal connected to XC1: TIOA2
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . TC1XC1S
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_TC1XC1S(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_MCAN_TIMER_TC_BMR_TC1XC1S     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_MCAN_TIMER_TC_BMR_TC1XC1S(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * External Clock Signal 0 Selection
 *
 * \details
 * 0 TCLK0 Signal connected to XC0: TCLK0
 * 1  Reserved
 * 2 TIOA1 Signal connected to XC0: TIOA1
 * 3 TIOA2 Signal connected to XC0: TIOA2
 *
 * Field: ::VTSS_MCAN_TIMER_TC_BMR . TC0XC0S
 */
#define  VTSS_F_MCAN_TIMER_TC_BMR_TC0XC0S(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MCAN_TIMER_TC_BMR_TC0XC0S     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MCAN_TIMER_TC_BMR_TC0XC0S(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief TC QDEC Interrupt Enable Register
 *
 * \details
 * TC QDEC Interrupt Enable Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_QIER
 */
#define VTSS_MCAN_TIMER_TC_QIER              VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x32)

/**
 * \brief
 * Consecutive Missing Pulse Error
 *
 * \details
 * 0 No effect.
 * 1 Enables the interrupt when an occurrence of MAXCMP consecutive missing
 * pulses is detected.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIER . MPE_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_QIER_MPE_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_QIER_MPE_IE     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_QIER_MPE_IE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Quadrature Error
 *
 * \details
 * 0 No effect.
 * 1 Enables the interrupt when a quadrature error occurs on PHA, PHB.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIER . QERR_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_QIER_QERR_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_QIER_QERR_IE    VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_QIER_QERR_IE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Direction Change
 *
 * \details
 * 0 No effect.
 * 1 Enables the interrupt when a change on rotation direction is detected
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIER . DIRCHG_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_QIER_DIRCHG_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_QIER_DIRCHG_IE  VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_QIER_DIRCHG_IE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Index
 *
 * \details
 * 0 No effect.
 * 1 Enables the interrupt when a rising edge occurs on IDX input.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIER . IDX_IE
 */
#define  VTSS_F_MCAN_TIMER_TC_QIER_IDX_IE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_QIER_IDX_IE     VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_QIER_IDX_IE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC QDEC Interrupt Disable Register
 *
 * \details
 * TC QDEC Interrupt Disable Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_QIDR
 */
#define VTSS_MCAN_TIMER_TC_QIDR              VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x33)

/**
 * \brief
 * Consecutive Missing Pulse Error
 *
 * \details
 * 0 No effect.
 * 1 Disables the interrupt when an occurrence of MAXCMP consecutive
 * missing pulses is detected.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIDR . MPE_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_QIDR_MPE_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_QIDR_MPE_ID     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_QIDR_MPE_ID(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Quadrature Error
 *
 * \details
 * 0 No effect.
 * 1 Disables the interrupt when a quadrature error occurs on PHA, PHB.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIDR . QERR_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_QIDR_QERR_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_QIDR_QERR_ID    VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_QIDR_QERR_ID(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Direction Change
 *
 * \details
 * 0 No effect.
 * 1 Disables the interrupt when a change on rotation direction is detected
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIDR . DIRCHG_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_QIDR_DIRCHG_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_QIDR_DIRCHG_ID  VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_QIDR_DIRCHG_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Index
 *
 * \details
 * 0 No effect.
 * 1 Disables the interrupt when a rising edge occurs on IDX input.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIDR . IDX_ID
 */
#define  VTSS_F_MCAN_TIMER_TC_QIDR_IDX_ID(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_QIDR_IDX_ID     VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_QIDR_IDX_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC QDEC Interrupt Mask Register
 *
 * \details
 * TC QDEC Interrupt Mask Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_QIMR
 */
#define VTSS_MCAN_TIMER_TC_QIMR              VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x34)

/**
 * \brief
 * Consecutive Missing Pulse Error
 *
 * \details
 * 0 No effect.
 * 1 Masks the interrupt when an occurrence of MAXCMP consecutive missing
 * pulses is detected.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIMR . MPE_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_QIMR_MPE_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_QIMR_MPE_IM     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_QIMR_MPE_IM(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Quadrature Error
 *
 * \details
 * 0 No effect.
 * 1 Masks the interrupt when a quadrature error occurs on PHA, PHB.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIMR . QERR_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_QIMR_QERR_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_QIMR_QERR_IM    VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_QIMR_QERR_IM(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Direction Change
 *
 * \details
 * 0 No effect.
 * 1 Masks the interrupt when a change on rotation direction is detected
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIMR . DIRCHG_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_QIMR_DIRCHG_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_QIMR_DIRCHG_IM  VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_QIMR_DIRCHG_IM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Index
 *
 * \details
 * 0 No effect.
 * 1 Masks the interrupt when a rising edge occurs on IDX input.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QIMR . IDX_IM
 */
#define  VTSS_F_MCAN_TIMER_TC_QIMR_IDX_IM(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_QIMR_IDX_IM     VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_QIMR_IDX_IM(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC QDEC Interrupt Status Register
 *
 * \details
 * TC QDEC Interrupt Status Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_QISR
 */
#define VTSS_MCAN_TIMER_TC_QISR              VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x35)

/**
 * \brief
 * DirectionReturns an image of the current rotation direction.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_QISR . DIR
 */
#define  VTSS_F_MCAN_TIMER_TC_QISR_DIR(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_MCAN_TIMER_TC_QISR_DIR        VTSS_BIT(8)
#define  VTSS_X_MCAN_TIMER_TC_QISR_DIR(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Consecutive Missing Pulse Error
 *
 * \details
 * 0 The number of consecutive missing pulses has not reached the maximum
 * value specified in MAXCMP
 * since the last read of TC_QISR.
 * 1 An occurrence of MAXCMP consecutive missing pulses has been detected
 * since the last read of
 * TC_QISR.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QISR . MPE_SR
 */
#define  VTSS_F_MCAN_TIMER_TC_QISR_MPE_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCAN_TIMER_TC_QISR_MPE_SR     VTSS_BIT(3)
#define  VTSS_X_MCAN_TIMER_TC_QISR_MPE_SR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Quadrature Error
 *
 * \details
 * 0 No quadrature error since the last read of TC_QISR.
 * 1 A quadrature error occurred since the last read of TC_QISR.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QISR . QERR_SR
 */
#define  VTSS_F_MCAN_TIMER_TC_QISR_QERR_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCAN_TIMER_TC_QISR_QERR_SR    VTSS_BIT(2)
#define  VTSS_X_MCAN_TIMER_TC_QISR_QERR_SR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Direction Change
 *
 * \details
 * 0 No change on rotation direction since the last read of TC_QISR.
 * 1 The rotation direction changed since the last read of TC_QISR.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QISR . DIRCHG_SR
 */
#define  VTSS_F_MCAN_TIMER_TC_QISR_DIRCHG_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_QISR_DIRCHG_SR  VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_QISR_DIRCHG_SR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Index
 *
 * \details
 * 0 No Index input change since the last read of TC_QISR.
 * 1 The IDX input has changed since the last read of TC_QISR.
 * SAMA5D2 Series
 * Timer Counter (TC)
 *
 * Field: ::VTSS_MCAN_TIMER_TC_QISR . IDX_SR
 */
#define  VTSS_F_MCAN_TIMER_TC_QISR_IDX_SR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_QISR_IDX_SR     VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_QISR_IDX_SR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Fault Mode Register
 *
 * \details
 * TC Fault Mode Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_FMR
 */
#define VTSS_MCAN_TIMER_TC_FMR               VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x36)

/**
 * \brief
 * Enable Compare Fault Channel 1
 *
 * \details
 * 0 Disables the FAULT output source (CPCS flag) from channel 1.
 * 1 Enables the FAULT output source (CPCS flag) from channel 1.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_FMR . ENCF1
 */
#define  VTSS_F_MCAN_TIMER_TC_FMR_ENCF1(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCAN_TIMER_TC_FMR_ENCF1       VTSS_BIT(1)
#define  VTSS_X_MCAN_TIMER_TC_FMR_ENCF1(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable Compare Fault Channel 0
 *
 * \details
 * 0 Disables the FAULT output source (CPCS flag) from channel 0.
 * 1 Enables the FAULT output source (CPCS flag) from channel 0.
 *
 * Field: ::VTSS_MCAN_TIMER_TC_FMR . ENCF0
 */
#define  VTSS_F_MCAN_TIMER_TC_FMR_ENCF0(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_FMR_ENCF0       VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_FMR_ENCF0(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TC Write Protection Mode Register
 *
 * \details
 * TC Write Protection Mode Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_WPMR
 */
#define VTSS_MCAN_TIMER_TC_WPMR              VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x37)

/**
 * \brief
 * Write Protection Key
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_WPMR . WPKEY
 */
#define  VTSS_F_MCAN_TIMER_TC_WPMR_WPKEY(x)   VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_MCAN_TIMER_TC_WPMR_WPKEY      VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_MCAN_TIMER_TC_WPMR_WPKEY(x)   VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * Write Protection EnableThe Timer Counter clock of the first channel must
 * be enabled to access this register.See Register Write Protection for a
 * list of registers that can be write-protected and Timer Counter clock
 * conditions.
 *
 * \details
 * 0 Disables the write protection if WPKEY corresponds to 0x54494D ("TIM"
 * in ASCII).
 * 1 Enables the write protection if WPKEY corresponds to 0x54494D ("TIM"
 * in ASCII).
 *
 * Field: ::VTSS_MCAN_TIMER_TC_WPMR . WPEN
 */
#define  VTSS_F_MCAN_TIMER_TC_WPMR_WPEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCAN_TIMER_TC_WPMR_WPEN       VTSS_BIT(0)
#define  VTSS_X_MCAN_TIMER_TC_WPMR_WPEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Version Register
 *
 * \details
 * Version Register
 *
 * Register: \a MCAN_TIMER:TIMER_REG_CFG:TC_VER
 */
#define VTSS_MCAN_TIMER_TC_VER               VTSS_IOREG(VTSS_TO_MCAN_TIMER,0x38)

/**
 * \brief
 * Version of the Hardware ModuleReserved. Value subject to change. No
 * functionality associated. This is the Atmel internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_VER . VERSION
 */
#define  VTSS_F_MCAN_TIMER_TC_VER_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_MCAN_TIMER_TC_VER_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_MCAN_TIMER_TC_VER_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * \brief
 * Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_MCAN_TIMER_TC_VER . MFN
 */
#define  VTSS_F_MCAN_TIMER_TC_VER_MFN(x)      VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_MCAN_TIMER_TC_VER_MFN         VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_MCAN_TIMER_TC_VER_MFN(x)      VTSS_EXTRACT_BITFIELD(x,16,3)


#endif /* _VTSS_LAGUNA_REGS_MCAN_TIMER_H_ */
