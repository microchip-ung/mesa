// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_PTP_H_
#define _VTSS_LAGUNA_REGS_PTP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a PTP
 *
 * DEVCPU Precision Timing Protocol Originator
 *
 ***********************************************************************/

/**
 * Register Group: \a PTP:PTP_CFG
 *
 * PTP controller configuration and status
 */


/**
 * \brief Pending interrupt mask
 *
 * \details
 * Register: \a PTP:PTP_CFG:PTP_PIN_INTR
 */
#define VTSS_PTP_PTP_PIN_INTR                VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x80)

/**
 * \brief
 * One bit per pin set when an active edge is seen.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_INTR . INTR_PTP
 */
#define  VTSS_F_PTP_PTP_PIN_INTR_INTR_PTP(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_PIN_INTR_INTR_PTP     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_PIN_INTR_INTR_PTP(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Enable interrupts per pin
 *
 * \details
 * Register: \a PTP:PTP_CFG:PTP_PIN_INTR_ENA
 */
#define VTSS_PTP_PTP_PIN_INTR_ENA            VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x81)

/**
 * \brief
 * Enable interrupt per ptp pin.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_INTR_ENA . INTR_PTP_ENA
 */
#define  VTSS_F_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_PIN_INTR_ENA_INTR_PTP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current interrupt status
 *
 * \details
 * Register: \a PTP:PTP_CFG:PTP_INTR_IDENT
 */
#define VTSS_PTP_PTP_INTR_IDENT              VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x82)

/**
 * \brief
 * Bit n will be high if an interrupt is currently pending for pin <n>.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_INTR_IDENT . INTR_PTP_IDENT
 */
#define  VTSS_F_PTP_PTP_INTR_IDENT_INTR_PTP_IDENT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_INTR_IDENT_INTR_PTP_IDENT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_INTR_IDENT_INTR_PTP_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Misc PTP configurations
 *
 * \details
 * Fields have a bit per domain, facilitating multiple doimains to be
 * simultaneously configured.
 *
 * Register: \a PTP:PTP_CFG:PTP_DOM_CFG
 */
#define VTSS_PTP_PTP_DOM_CFG                 VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x83)

/**
 * \brief
 * Enable master counter.
 *
 * \details
 * 0: Master counter disabled and reset
 * 1: Master counter enabled
 *
 * Field: ::VTSS_PTP_PTP_DOM_CFG . PTP_ENA
 */
#define  VTSS_F_PTP_PTP_DOM_CFG_PTP_ENA(x)    VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_PTP_PTP_DOM_CFG_PTP_ENA       VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_PTP_PTP_DOM_CFG_PTP_ENA(x)    VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Hold master counter.
 *
 * \details
 * 0: Master counter counts if enabled
 * 1: Master counter will stay at the reached value
 *
 * Field: ::VTSS_PTP_PTP_DOM_CFG . PTP_HOLD
 */
#define  VTSS_F_PTP_PTP_DOM_CFG_PTP_HOLD(x)   VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_PTP_PTP_DOM_CFG_PTP_HOLD      VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_PTP_PTP_DOM_CFG_PTP_HOLD(x)   VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * The PTP_CUR timers will be frozen when this field is set for a domain,
 * in order to return concurrent values.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_DOM_CFG . PTP_TOD_FREEZE
 */
#define  VTSS_F_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Disable reprogramming of clock period for the domain. This field should
 * be set, when clock cfg is changed through multiple register writes.
 *
 * \details
 * 0: Use CLK_PER_CFG registers
 * 1: Use latest programmed value
 *
 * Field: ::VTSS_PTP_PTP_DOM_CFG . PTP_CLKCFG_DIS
 */
#define  VTSS_F_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a PTP:PTP_TOD_DOMAINS
 *
 * Configuration and Status for PTP domains
 */


/**
 * \brief Time of day clock configuration
 *
 * \details
 * Each system clock cycle, the time-of-day is increased with the value set
 * in these registers, with fixed point 5.59 nanosecond value. Replication
 * 1 is the MSB part.

 *
 * Register: \a PTP:PTP_TOD_DOMAINS:CLK_PER_CFG
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 * @param ri Register: CLK_PER_CFG (??), 0-1
 */
#define VTSS_PTP_CLK_PER_CFG(gi,ri)          VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,ri,0)

/**
 * \brief
 * Clock period configuration for the domain.
 *
 * \details
 * Field: ::VTSS_PTP_CLK_PER_CFG . CLK_PER_VAL
 */
#define  VTSS_F_PTP_CLK_PER_CFG_CLK_PER_VAL(x)  (x)
#define  VTSS_M_PTP_CLK_PER_CFG_CLK_PER_VAL     0xffffffff
#define  VTSS_X_PTP_CLK_PER_CFG_CLK_PER_VAL(x)  (x)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, nanoseconds part.
 *
 * Register: \a PTP:PTP_TOD_DOMAINS:PTP_CUR_NSEC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_PTP_PTP_CUR_NSEC(gi)            VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,0,2)

/**
 * \brief
 * Time of day nanoseconds.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_CUR_NSEC . PTP_CUR_NSEC
 */
#define  VTSS_F_PTP_PTP_CUR_NSEC_PTP_CUR_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_PTP_CUR_NSEC_PTP_CUR_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_PTP_CUR_NSEC_PTP_CUR_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, fractional nanoseconds part.
 *
 * Register: \a PTP:PTP_TOD_DOMAINS:PTP_CUR_NSEC_FRAC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_PTP_PTP_CUR_NSEC_FRAC(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,0,3)

/**
 * \brief
 * Time of day fractional naoseconds (unit is nsec/256), latched when NSEC
 * was read.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_CUR_NSEC_FRAC . PTP_CUR_NSEC_FRAC
 */
#define  VTSS_F_PTP_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current time of day
 *
 * \details
 * Register: \a PTP:PTP_TOD_DOMAINS:PTP_CUR_SEC_LSB
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_PTP_PTP_CUR_SEC_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,0,4)

/**
 * \brief
 * Value of current tod secs, latched when NSEC was read.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_CUR_SEC_LSB . PTP_CUR_SEC_LSB
 */
#define  VTSS_F_PTP_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB(x)  (x)


/**
 * \brief Current time of day
 *
 * \details
 * Register: \a PTP:PTP_TOD_DOMAINS:PTP_CUR_SEC_MSB
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_PTP_PTP_CUR_SEC_MSB(gi)         VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,0,5)

/**
 * \brief
 * Current time of day, seconds part, latched when NSEC was read
 *
 * \details
 * Field: ::VTSS_PTP_PTP_CUR_SEC_MSB . PTP_CUR_SEC_MSB
 */
#define  VTSS_F_PTP_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, NTP fractional seconds part.
 *
 * Register: \a PTP:PTP_TOD_DOMAINS:NTP_CUR_NSEC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_TOD_DOMAINS (??), 0-2
 */
#define VTSS_PTP_NTP_CUR_NSEC(gi)            VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x84,gi,7,0,6)

/**
 * \brief
 * Time of day fractional second, latched when NSEC was read.
 *
 * \details
 * Field: ::VTSS_PTP_NTP_CUR_NSEC . NTP_CUR_NSEC
 */
#define  VTSS_F_PTP_NTP_CUR_NSEC_NTP_CUR_NSEC(x)  (x)
#define  VTSS_M_PTP_NTP_CUR_NSEC_NTP_CUR_NSEC     0xffffffff
#define  VTSS_X_PTP_NTP_CUR_NSEC_NTP_CUR_NSEC(x)  (x)

/**
 * Register Group: \a PTP:PTP_PINS
 *
 * Timing synchronization
 */


/**
 * \brief Configuration of use of the register group
 *
 * \details
 * Select action of the pins assigned to the load/store instance.

 *
 * Register: \a PTP:PTP_PINS:PTP_PIN_CFG
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PTP_PIN_CFG(gi)             VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,0)

/**
 * \brief
 * Defined actions are:   IDLE: No operation   LOAD:   Load TimeOfDay with
 * configured values  STORE:  Store TimeOfDay of selected time domain
 * CLOCK:  Generate a clock output, or a 1PPS pulse  DELTA:  Add
 * PTP_TOD_NSEC field as a signed integer to TimeOfDay	TOD:	Transmit
 * serial version of TimeOfDay for selected domain.The LOAD/STORE/DELTA
 * actions will automatically return to IDLE when complete. If the
 * PTP_PIN_SYNC is set, the action will be executed when an active edge is
 * seen on the pin; otherwise immediately.The CLOCK action generates a
 * waveform dependent on the PTP_PIN_SYNC setting:0: Generates a repeated
 * waveform with PIN_WF_HIGH_PERIOD (WFH) nanoseconds high, and
 * PIN_WF_LOW_PERIOD (WFL) nanoseconds low.1: Generates a 1PPS pulse at
 * time WFL, with a pulse width of WFH.The pin option bit 0 being set
 * instead connects the nsec value from timeofday, bit <(WFH mod 16)> to
 * the output. Ex: set it to 7, to get nsec bit 7 out on the pin.The TOD
 * action generates a serial stream with the seconds part of the TimeOfDay.
 * The stream is initiated when the nanoseconds part equals WFL, and the
 * bit period is configured in WFH. The stream consists of a 21 bit long
 * preamble with value 1000...0, and 16 bytes of information. Each byte is
 * transmitted as 1<lsb><bit 1>...<bit 7>0 (10 bits in total). Of the 16
 * bytes, the first 6 contains the seconds. These are transmitted with
 * least significant byte first. The remaining 10 bytes are all zeros.The
 * bit order can be reversed with pin option bit 0 (PTP_PIN_OPT), and the
 * byte order with pin option bit 1.preamble of 1
 *
 * \details
 * 0: IDLE
 * 1: LOAD
 * 2: STORE
 * 3: CLOCK
 * 4: DELTA
 * 5: TOD
 * 6-7: reserved

 *
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_ACTION
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_ACTION(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_ACTION     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/**
 * \brief
 * For LOAD/STORE/DELTA actions, setting this option will suspend the
 * action until an active edge is seen on the pins. Otherwise it will be
 * done immediately.For the CLOCK action, the sync option makes the pin
 * generate a single pulse, <WAFEFORM_LOW> nanoseconds after the time of
 * day has increased the seconds. The pulse will get a width of
 * <WAVEFORM_HIGH> nanoseconds. Setting this field to 3 make the controller
 * repeat its action at the next active edge.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_SYNC
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_SYNC(x)  VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_SYNC     VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,25,2)

/**
 * \brief
 * Polarity of the PTP pins.
 *
 * \details
 * 0: Active high
 * 1: Active low

 *
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_INV_POL
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_INV_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_INV_POL  VTSS_BIT(24)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_INV_POL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Selects which ptp pin the load store controller input should connect to.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_SELECT
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_SELECT     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/**
 * \brief
 * Selects which ptp pin to use for syncronization. If a clock is used for
 * pin input, the load/store time is adjusted to the accurate time of the
 * rising clock edge at which the pin was active. If a clock is used for
 * pin output, the generated waveform is resynchronized to the selected
 * clock.Clock can be embedded into the pin data by setting the
 * PTP_PIN_EMBEDDED_CLK option. Used as an input, the load/store time is
 * adjusted to the time at which the duty cycle became more than 10% off
 * 50/50. Using the pin as an output will drive the selected clock on the
 * pin, and generate a 75/25 duty cycle every time a rising edge is seen on
 * the generated waveform.
 *
 * \details
 * 0-3: GPIO_PIN_<n>
 * 4: No resync of external pin
 * 5: External reference clock
 * 6: External reference clock div4
 * 7: External reference clock div8
 *
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_CLK_SELECT
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_CLK_SELECT(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_CLK_SELECT     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_CLK_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * Configures the time domain the pin is connected to.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_DOM
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_DOM(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_DOM     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_DOM(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * \brief
 * Special options for an action. See the action descriptions.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_OPT
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_OPT(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_OPT     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_OPT(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/**
 * \brief
 * If this bit is set, clock and data will be usiung the same pin. See the
 * PTP_CLK_SELECT.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_EMBEDDED_CLK
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK  VTSS_BIT(13)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * This field tells the distance from the the desired previous clock edge
 * to the actual time it was generated. Ie. an output edge is asked to be
 * created at 12.0 ns, and the internal time of day had the value of 12.45
 * ns. This field will then ben set to 0.45. Format is 5.8 fixedpoint.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_PIN_CFG . PTP_PIN_OUTP_OFS
 */
#define  VTSS_F_PTP_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(x)  VTSS_ENCODE_BITFIELD(x,0,13)
#define  VTSS_M_PTP_PTP_PIN_CFG_PTP_PIN_OUTP_OFS     VTSS_ENCODE_BITMASK(0,13)
#define  VTSS_X_PTP_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(x)  VTSS_EXTRACT_BITFIELD(x,0,13)


/**
 * \brief Time Of Day MSB
 *
 * \details
 * Register: \a PTP:PTP_PINS:PTP_TOD_SEC_MSB
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PTP_TOD_SEC_MSB(gi)         VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,1)

/**
 * \brief
 * Bits 47:32 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TOD_SEC_MSB . PTP_TOD_SEC_MSB
 */
#define  VTSS_F_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Time Of Day LSB
 *
 * \details
 * Register: \a PTP:PTP_PINS:PTP_TOD_SEC_LSB
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PTP_TOD_SEC_LSB(gi)         VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,2)

/**
 * \brief
 * Bits 31:0 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TOD_SEC_LSB . PTP_TOD_SEC_LSB
 */
#define  VTSS_F_PTP_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB(x)  (x)


/**
 * \brief Time Of Day nanosecs part
 *
 * \details
 * Register: \a PTP:PTP_PINS:PTP_TOD_NSEC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PTP_TOD_NSEC(gi)            VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,3)

/**
 * \brief
 * Time Of Day nanoseconds loaded or stored into TimeOfDay. A synced store
 * operation may return a value between -2 and 999.999.999 in this field.
 * To normalize the complete TOD, in case field is read 0x3ffffffe/f,
 * software must subtract one from the SEC part, and add 1.000.000.000 to
 * the NSEC part.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TOD_NSEC . PTP_TOD_NSEC
 */
#define  VTSS_F_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Time Of Day nanosecs fractional part
 *
 * \details
 * Register: \a PTP:PTP_PINS:PTP_TOD_NSEC_FRAC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PTP_TOD_NSEC_FRAC(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,4)

/**
 * \brief
 * Time Of Day fractional nanoseconds loaded or stored into TimeOfDay.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TOD_NSEC_FRAC . PTP_TOD_NSEC_FRAC
 */
#define  VTSS_F_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current time of day, NTP sub-second
 *
 * \details
 * Register: \a PTP:PTP_PINS:NTP_NSEC
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_NTP_NSEC(gi)                VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,5)

/**
 * \brief
 * Value of NTP counter when load/save action was executed. This value will
 * not be loaded into the timers upon a LOAD operation.
 *
 * \details
 * Field: ::VTSS_PTP_NTP_NSEC . NTP_NSEC
 */
#define  VTSS_F_PTP_NTP_NSEC_NTP_NSEC(x)      (x)
#define  VTSS_M_PTP_NTP_NSEC_NTP_NSEC         0xffffffff
#define  VTSS_X_PTP_NTP_NSEC_NTP_NSEC(x)      (x)


/**
 * \brief Waveform programming
 *
 * \details
 * Register: \a PTP:PTP_PINS:PIN_WF_HIGH_PERIOD
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PIN_WF_HIGH_PERIOD(gi)      VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,6)

/**
 * \brief
 * Configure waveform. Unit is nanoseconds.EX. 25MHz 60/40 clock:
 * PIN_ACTION=CLOCK, PIN_SYNC=0, PIN_WFH=24, PIN_WFL=16EX. 1 us pulse after
 * 150 ns  PIN_ACTION=CLOCK, PIN_SYNC=1, PIN_WFH=1000, PIN_WFL=150
 *
 * \details
 * Field: ::VTSS_PTP_PIN_WF_HIGH_PERIOD . PIN_WFH
 */
#define  VTSS_F_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Waveform programming
 *
 * \details
 * Register: \a PTP:PTP_PINS:PIN_WF_LOW_PERIOD
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PIN_WF_LOW_PERIOD(gi)       VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,7)

/**
 * \brief
 * Configure waveform
 *
 * \details
 * Field: ::VTSS_PTP_PIN_WF_LOW_PERIOD . PIN_WFL
 */
#define  VTSS_F_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_PIN_WF_LOW_PERIOD_PIN_WFL     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Privide the average skew betwen output and input pin
 *
 * \details
 * Register: \a PTP:PTP_PINS:PIN_IOBOUNCH_DELAY
 *
 * @param gi Replicator: x_PTP_CFG_NUM_LS_CTRLS (??), 0-7
 */
#define VTSS_PTP_PIN_IOBOUNCH_DELAY(gi)      VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x0,gi,16,0,8)

/**
 * \brief
 * Return the skew between output and input pin values for the loadstore
 * controller. A value of 0 indicates no skew. A vaule of N indicates a
 * skew of (N>>17)*period of generated clock.
 *
 * \details
 * Field: ::VTSS_PTP_PIN_IOBOUNCH_DELAY . PIN_IOBOUNCH_VAL
 */
#define  VTSS_F_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/**
 * \brief
 * Set the time for which the skew detection should run.
 *
 * \details
 * 0: Sample 65K core cycles
 * 1: Sample 256K core cycles
 * n: Sample 65K * 4^n cycles
 *
 * Field: ::VTSS_PTP_PIN_IOBOUNCH_DELAY . PIN_IOBOUNCH_CFG
 */
#define  VTSS_F_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a PTP:PTP_TS_FIFO
 *
 * PTP TS FIFO access
 */


/**
 * \brief Configuration register for PTP stamping
 *
 * \details
 * Register: \a PTP:PTP_TS_FIFO:PTP_TWOSTEP_CTRL
 */
#define VTSS_PTP_PTP_TWOSTEP_CTRL            VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x99)

/**
 * \brief
 * If the fifo is overflown, additional stamps will overwrite older.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . PTP_OVWR_ENA
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA  VTSS_BIT(12)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_PTP_OVWR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Write one to advance the stamp queue to the next available.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . PTP_NXT
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_PTP_NXT  VTSS_BIT(11)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * The stamp queue is non empty
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . PTP_VLD
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_PTP_VLD(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_PTP_VLD  VTSS_BIT(10)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_PTP_VLD(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Current stamp is an egress stamp
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . STAMP_TX
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_STAMP_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_STAMP_TX  VTSS_BIT(9)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_STAMP_TX(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Field contains the port number the stamp was made on
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . STAMP_PORT
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_STAMP_PORT(x)  VTSS_ENCODE_BITFIELD(x,1,8)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_STAMP_PORT     VTSS_ENCODE_BITMASK(1,8)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_STAMP_PORT(x)  VTSS_EXTRACT_BITFIELD(x,1,8)

/**
 * \brief
 * The stamp is overflown, and some stamps are lost.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_CTRL . PTP_OVFL
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_CTRL_PTP_OVFL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_PTP_TWOSTEP_CTRL_PTP_OVFL  VTSS_BIT(0)
#define  VTSS_X_PTP_PTP_TWOSTEP_CTRL_PTP_OVFL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Ingress time stamp
 *
 * \details
 * Register: \a PTP:PTP_TS_FIFO:PTP_TWOSTEP_STAMP_NSEC
 */
#define VTSS_PTP_PTP_TWOSTEP_STAMP_NSEC      VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x9a)

/**
 * \brief
 * Contains the 30 bit time stamp.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_STAMP_NSEC . STAMP_NSEC
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_STAMP_NSEC_STAMP_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_PTP_TWOSTEP_STAMP_NSEC_STAMP_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_PTP_TWOSTEP_STAMP_NSEC_STAMP_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Ingress time stamp
 *
 * \details
 * Register: \a PTP:PTP_TS_FIFO:PTP_TWOSTEP_STAMP_SUBNS
 */
#define VTSS_PTP_PTP_TWOSTEP_STAMP_SUBNS     VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x9b)

/**
 * \brief
 * Contains the sub nanoseconds part of a time stamp.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_TWOSTEP_STAMP_SUBNS . STAMP_SUB_NSEC
 */
#define  VTSS_F_PTP_PTP_TWOSTEP_STAMP_SUBNS_STAMP_SUB_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_PTP_TWOSTEP_STAMP_SUBNS_STAMP_SUB_NSEC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_PTP_TWOSTEP_STAMP_SUBNS_STAMP_SUB_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Write pointer into TS buffer
 *
 * \details
 * Register: \a PTP:PTP_TS_FIFO:PTP_WRP
 */
#define VTSS_PTP_PTP_WRP                     VTSS_IOREG(VTSS_TO_DEVCPU_PTP,0x9c)

/**
 * \brief
 * Address of next fifo entry to store bus events into.
 *
 * \details
 * Field: ::VTSS_PTP_PTP_WRP . PTP_WRP
 */
#define  VTSS_F_PTP_PTP_WRP_PTP_WRP(x)        VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_PTP_WRP_PTP_WRP           VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_PTP_WRP_PTP_WRP(x)        VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PTP:PHASE_DETECTOR_CTRL
 *
 * High precission event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 *
 * Register: \a PTP:PHASE_DETECTOR_CTRL:PHAD_CTRL
 *
 * @param gi Replicator: x_PHASE_DETECTOR_INSTANCES (??), 0-7
 */
#define VTSS_PTP_PHAD_CTRL(gi)               VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x9d,gi,3,0,0)

/**
 * \brief
 * Phase detector is locked to port clock. This indicates that the error
 * level has been lower than the cfg_lock configuration for the past 5
 * times an error is seen.
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . PHAD_LOCK
 */
#define  VTSS_F_PTP_PHAD_CTRL_PHAD_LOCK(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_PHAD_CTRL_PHAD_LOCK       VTSS_BIT(18)
#define  VTSS_X_PTP_PHAD_CTRL_PHAD_LOCK(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Event clock is currently divided by this
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . DIV_STATE
 */
#define  VTSS_F_PTP_PHAD_CTRL_DIV_STATE(x)    VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_PHAD_CTRL_DIV_STATE       VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_PHAD_CTRL_DIV_STATE(x)    VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . PHAD_ADJ
 */
#define  VTSS_F_PTP_PHAD_CTRL_PHAD_ADJ(x)     VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_PTP_PHAD_CTRL_PHAD_ADJ        VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_PTP_PHAD_CTRL_PHAD_ADJ(x)     VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * Configure wjat the PHAD_ERR_STAT shows
 *
 * \details
 * 0: Show the latest error level
 * 1: Show the largests error level
 *
 * Field: ::VTSS_PTP_PHAD_CTRL . ERR_MAX_ENA
 */
#define  VTSS_F_PTP_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_PHAD_CTRL_ERR_MAX_ENA     VTSS_BIT(12)
#define  VTSS_X_PTP_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Divide port clock by the power of this
 *
 * \details
 * 0: Auto detect.
 * 1: Divide port clock by one
 * 2: Divide port clock by two.
 * ...
 * 7: Divide port clock by 7.
 *
 * Field: ::VTSS_PTP_PHAD_CTRL . DIV_CFG
 */
#define  VTSS_F_PTP_PHAD_CTRL_DIV_CFG(x)      VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_PTP_PHAD_CTRL_DIV_CFG         VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_PTP_PHAD_CTRL_DIV_CFG(x)      VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Internal tweaks. Can be left at default value.
 *
 * \details
 * xx1: Count up to 4K port cycles when detecting port clock period.
 * Otherwise up to 128K cycles. If more than 1 ms has passed in the
 * counting, the evaluation stops at the next power of two port cycles
 * 00x: In sync mode, delay chain is 8 inverter pairs long
 * 01x: In sync mode, delay chain is 6 inverter pairs long
 * 10x: In sync mode, delay chain is 4 inverter pairs long
 * 11x: In sync mode, delay chain is 2 inverter pairs long

 *
 * Field: ::VTSS_PTP_PHAD_CTRL . TWEAKS
 */
#define  VTSS_F_PTP_PHAD_CTRL_TWEAKS(x)       VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_PTP_PHAD_CTRL_TWEAKS          VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_PTP_PHAD_CTRL_TWEAKS(x)       VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Enable high accuracy TOD transfer
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . PHAD_ENA
 */
#define  VTSS_F_PTP_PHAD_CTRL_PHAD_ENA(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_PHAD_CTRL_PHAD_ENA        VTSS_BIT(5)
#define  VTSS_X_PTP_PHAD_CTRL_PHAD_ENA(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * The high accuracy TOD traphase detector can operator in two
 * modes:RANGEMODE: Main TOD is sampled at every port clock edge and
 * verified to be within 0-1 main LTC clock cycles off predicted port TOD.
 * Otherwise port TOD is moved into range.SYNCMODE: Main TOD is sampled at
 * main clock edges falling close to a port clock edge, and port TOD is set
 * to the sampled value. The close edge detection is based on concurrent
 * sampling of the port clock and a delayed version (see TWEAKS).
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . PHAD_MODE
 */
#define  VTSS_F_PTP_PHAD_CTRL_PHAD_MODE(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PTP_PHAD_CTRL_PHAD_MODE       VTSS_BIT(4)
#define  VTSS_X_PTP_PHAD_CTRL_PHAD_MODE(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.

 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . PHAD_FAILED
 */
#define  VTSS_F_PTP_PHAD_CTRL_PHAD_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_PHAD_CTRL_PHAD_FAILED     VTSS_BIT(3)
#define  VTSS_X_PTP_PHAD_CTRL_PHAD_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Phase is assumed locked when it is never outside 60 ps x (2**LOCK_ACC)
 * from expected range.
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CTRL . LOCK_ACC
 */
#define  VTSS_F_PTP_PHAD_CTRL_LOCK_ACC(x)     VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_PHAD_CTRL_LOCK_ACC        VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_PHAD_CTRL_LOCK_ACC(x)     VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP:PHASE_DETECTOR_CTRL:PHAD_CYC_STAT
 *
 * @param gi Replicator: x_PHASE_DETECTOR_INSTANCES (??), 0-7
 */
#define VTSS_PTP_PHAD_CYC_STAT(gi)           VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x9d,gi,3,0,1)

/**
 * \brief
 * Detected event clock period in 16.16 fixedpoint format.
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_CYC_STAT . PHAD_CYCLETIME
 */
#define  VTSS_F_PTP_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)
#define  VTSS_M_PTP_PHAD_CYC_STAT_PHAD_CYCLETIME     0xffffffff
#define  VTSS_X_PTP_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP:PHASE_DETECTOR_CTRL:PHAD_ERR_STAT
 *
 * @param gi Replicator: x_PHASE_DETECTOR_INSTANCES (??), 0-7
 */
#define VTSS_PTP_PHAD_ERR_STAT(gi)           VTSS_IOREG_IX(VTSS_TO_DEVCPU_PTP,0x9d,gi,3,0,2)

/**
 * \brief
 * Latest or maximum error detected in alignment process with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_PHAD_ERR_STAT . PHAD_ERR_STAT
 */
#define  VTSS_F_PTP_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_PHAD_ERR_STAT_PHAD_ERR_STAT     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,19)


#endif /* _VTSS_LAGUNA_REGS_PTP_H_ */
