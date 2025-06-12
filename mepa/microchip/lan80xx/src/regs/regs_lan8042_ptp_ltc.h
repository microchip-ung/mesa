// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_PTP_LTC_H_
#define _VTSS_MALIBU25G_REGS_PTP_LTC_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a PTP_LTC
 *
 * DEVCPU Precision Timing Protocol Originator
 *
 ***********************************************************************/

/**
 * Register Group: \a PTP_LTC:PHASE_DETECTOR_CTRL
 *
 * High precision event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the mac clock
 * domains must be reset after clock change, ie when the link is detected
 * up and stable.
 *
 * Register: \a PTP_LTC:PHASE_DETECTOR_CTRL:PHAD_CTRL
 *
 * @param gi Register: PHASE_DETECTOR_CTRL (??), 0-3
 */
#define LAN80XX_PTP_LTC_PHAD_CTRL(gi)         LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd040,gi,3,0,0))

/**
 * \brief
 * Phase detector is locked to port clock. This indicates that the error
 * level has been lower than the cfg_lock configuration for the past 5
 * times an error is seen.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . PHAD_LOCK
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_PHAD_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_PHAD_LOCK     VTSS_BIT(18)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_PHAD_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Event clock is currently divided by this
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . DIV_STATE
 */
#define  LAN80XX_F_PTP_LTC_PHAD_CTRL_DIV_STATE(x)  LAN80XX_ENCODE_BITFIELD(x,15,3)
#define  LAN80XX_M_PTP_LTC_PHAD_CTRL_DIV_STATE     LAN80XX_ENCODE_BITMASK(15,3)
#define  LAN80XX_X_PTP_LTC_PHAD_CTRL_DIV_STATE(x)  LAN80XX_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . PHAD_ADJ
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_PHAD_ADJ(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_PHAD_ADJ     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_PHAD_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * Configure wjat the PHAD_ERR_STAT shows
 *
 * \details
 * 0: Show the latest error level
 * 1: Show the largests error level
 *
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . ERR_MAX_ENA
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_ERR_MAX_ENA  VTSS_BIT(12)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . DIV_CFG
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_DIV_CFG(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_DIV_CFG     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_DIV_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

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
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . TWEAKS
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_TWEAKS(x)   VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_TWEAKS      VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_TWEAKS(x)   VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Enable high accuracy TOD transfer
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . PHAD_ENA
 */
#define  LAN80XX_F_PTP_LTC_PHAD_CTRL_PHAD_ENA(x)  LAN80XX_ENCODE_BITFIELD((x),5,1)
#define  LAN80XX_M_PTP_LTC_PHAD_CTRL_PHAD_ENA     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_LTC_PHAD_CTRL_PHAD_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

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
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . PHAD_MODE
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_PHAD_MODE   VTSS_BIT(4)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.

 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . PHAD_FAILED
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_PHAD_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_PHAD_FAILED  VTSS_BIT(3)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_PHAD_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Phase is assumed locked when it is never outside 60 ps x (2**LOCK_ACC)
 * from expected range.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CTRL . LOCK_ACC
 */
#define  VTSS_F_PTP_LTC_PHAD_CTRL_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_LTC_PHAD_CTRL_LOCK_ACC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_LTC_PHAD_CTRL_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_LTC:PHASE_DETECTOR_CTRL:PHAD_CYC_STAT
 *
 * @param gi Register: PHASE_DETECTOR_CTRL (??), 0-3
 */
#define VTSS_PTP_LTC_PHAD_CYC_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd040,gi,3,0,1)

/**
 * \brief
 * Detected event clock period in 16.16 fixedpoint format.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_CYC_STAT . PHAD_CYCLETIME
 */
#define  VTSS_F_PTP_LTC_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)
#define  VTSS_M_PTP_LTC_PHAD_CYC_STAT_PHAD_CYCLETIME     0xffffffff
#define  VTSS_X_PTP_LTC_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_LTC:PHASE_DETECTOR_CTRL:PHAD_ERR_STAT
 *
 * @param gi Register: PHASE_DETECTOR_CTRL (??), 0-3
 */
#define VTSS_PTP_LTC_PHAD_ERR_STAT(gi)       VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd040,gi,3,0,2)

/**
 * \brief
 * Latest or maximum error detected in alignment process with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PHAD_ERR_STAT . PHAD_ERR_STAT
 */
#define  VTSS_F_PTP_LTC_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_LTC_PHAD_ERR_STAT_PHAD_ERR_STAT     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_LTC_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_LTC:PTP_PINS
 *
 * Timing synchronization
 */


/**
 * \brief Configuration of use of the register group
 *
 * \details
 * Select action of the pins assigned to the load/store instance.

 *
 * Register: \a PTP_LTC:PTP_PINS:PTP_PIN_CFG
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PTP_PIN_CFG(gi)         VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,0)
#define LAN80XX_PTP_LTC_PTP_PIN_CFG(gi)      LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,0))

/**
 * \brief
 * Defined actions are:IDLE: No operationLOAD: Load TimeOfDay with
 * configured valuesSTORE: Store TimeOfDay of selected time domainCLOCK:
 * Generate a clock output, or a 1PPS pulseDELTA: Add PTP_TOD_NSEC and
 * PTP_TOD_NSEC_FRAC fields as a signed integer to TimeOfDayTOD: Transmit
 * serial version of TimeOfDay for selected domain.The LOAD/STORE/DELTA
 * actions will be executed immediately and will automatically return to
 * IDLE when complete.The PTP_PIN_SYNC alters the LOAD/STORE/DELTA actions
 * as follows (PTP_PIN_OPT = 00):00:  actions are executed immediately.01:
 * will be executed when an active edge is seen on the pin10: reserved?11:
 * action is repeated at next active edge.The PTP_PIN_SYNC alters the CLOCK
 * action as follows (PTP_PIN_OPT = 00):00: Generates a repeated waveform
 * with PIN_WF_HIGH_PERIOD (WFH) nanoseconds high, and PIN_WF_LOW_PERIOD
 * (WFL) nanoseconds low.01: Generates a 1PPS pulse at time WFL, with a
 * pulse width of WFH.'10/11: reserved?The PTP_PIN_OPT alters the CLOCK
 * action as follows (PTP_PIN_SYNC = 00):00: as above01: connects the nsec
 * value from timeofday, bit <(WFH mod 16)> to the output. Ex: set it to 7,
 * to get nsec bit 7 out on the pin.10/11: reserved?The TOD action
 * generates a serial stream output with the seconds part of the TimeOfDay.
 * The stream is initiated when the nanoseconds part (PTP_CUR_NSEC[29:0])
 * equals WFL, and the bit period is configured in WFH. The stream consists
 * of a 21 bit long preamble with value 1000...0, and 16 bytes of
 * information. Each byte is transmitted as 1<lsb><bit 1>...<bit 7>0 (10
 * bits in total). Of the 16 bytes, the first 6 contains the seconds. These
 * are transmitted with least significant byte first. The remaining 10
 * bytes are all zeros.The bit order can be reversed with PTP_PIN_OPT bit
 * 0, and the byte order with PTP_PIN_OPT bit 1.
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
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_ACTION
 */
#define  VTSS_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,24,3)


#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(x)  LAN80XX_ENCODE_BITFIELD(x,29,3)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION     LAN80XX_ENCODE_BITMASK(29,3)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,29,3)

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
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_SYNC
 */
#define  VTSS_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(x)  VTSS_ENCODE_BITFIELD(x,27,2)
#define  VTSS_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC     VTSS_ENCODE_BITMASK(27,2)
#define  VTSS_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(x)  VTSS_EXTRACT_BITFIELD(x,27,2)

#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(x)  LAN80XX_ENCODE_BITFIELD(x,27,2)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC     LAN80XX_ENCODE_BITMASK(27,2)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(x)  LAN80XX_EXTRACT_BITFIELD(x,27,2)
/**
 * \brief
 * Polarity of the PTP pins.
 *
 * \details
 * 0: Active high
 * 1: Active low

 *
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_INV_POL
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(x)  LAN80XX_ENCODE_BITFIELD((x),26,1)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL     LAN80XX_BIT(26)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(x)  LAN80XX_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Selects which ptp pin the load store controller input should connect to.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_SELECT
 */
#define  VTSS_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(x)  LAN80XX_ENCODE_BITFIELD(x,24,2)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT     LAN80XX_ENCODE_BITMASK(24,2)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(x)  LAN80XX_EXTRACT_BITFIELD(x,24,2)
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
 * the generated waveform.  If PTP_CLK_SELECT is equivalent to 3'b100, it
 * indicates the sampling of 1PPS is at Async Mode. Otherwise, it is at
 * Sync mode.
 *
 * \details
 * 0-3: PTP1588_LSC_PIN_<n>
 * 4: No resync of external pin
 * 5: External reference clock
 * 6: External reference clock div4
 * 7: External reference clock div8
 *
 * Field: ::LAN80XX_PTP_LTC_PTP_PIN_CFG . PTP_CLK_SELECT
 */

#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(x)  LAN80XX_ENCODE_BITFIELD(x,20,4)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT     LAN80XX_ENCODE_BITMASK(20,4)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(x)  LAN80XX_EXTRACT_BITFIELD(x,20,3)
/**
 * \brief
 * Special options for an action. See the action descriptions.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_OPT
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT(x)  LAN80XX_ENCODE_BITFIELD(x,18,2)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT     LAN80XX_ENCODE_BITMASK(18,2)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT(x)  LAN80XX_EXTRACT_BITFIELD(x,18,2)

/**
 * \brief
 * If this bit is set, clock and data will be using the same pin. See the
 * PTP_CLK_SELECT.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_EMBEDDED_CLK
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK(x)  LAN80XX_ENCODE_BITFIELD((x),17,1)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK     LAN80XX_BIT(17)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK(x)  LAN80XX_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * This field tells the distance from the desired previous clock edge to
 * the actual time it was generated. Ie. an output edge is asked to be
 * created at 12.0 ns, and the internal time of day had the value of 12.45
 * ns. This field will then ben set to 0.45. Format is 5.8 fixedpoint.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_CFG . PTP_PIN_OUTP_OFS
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(x)  LAN80XX_ENCODE_BITFIELD(x,0,17)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OUTP_OFS     LAN80XX_ENCODE_BITMASK(0,17)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,17)


/**
 * \brief Time Of Day MSB
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PTP_TOD_SEC_MSB
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PTP_TOD_SEC_MSB(gi)     VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,1)
#define LAN80XX_PTP_LTC_PTP_TOD_SEC_MSB(gi)     LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,1))
/**
 * \brief
 * Bits 47:32 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_SEC_MSB . PTP_TOD_SEC_MSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Time Of Day LSB
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PTP_TOD_SEC_LSB
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PTP_TOD_SEC_LSB(gi)     VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,2)
#define LAN80XX_PTP_LTC_PTP_TOD_SEC_LSB(gi)  LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,2))
/**
 * \brief
 * Bits 31:0 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_SEC_LSB . PTP_TOD_SEC_LSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_LTC_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_LTC_PTP_TOD_SEC_LSB_PTP_TOD_SEC_LSB(x)  (x)


/**
 * \brief Time Of Day nanosecs part
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PTP_TOD_NSEC
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PTP_TOD_NSEC(gi)        VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,3)
#define LAN80XX_PTP_LTC_PTP_TOD_NSEC(gi)     LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,3))

/**
 * \brief
 * Time Of Day nanoseconds loaded or stored into TimeOfDay. A synced store
 * operation may return a value between -2 and 999.999.999 in this field.
 * To normalize the complete TOD, in case field is read 0x3ffffffe/f,
 * software must subtract one from the SEC part, and add 1.000.000.000 to
 * the NSEC part.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_NSEC . PTP_TOD_NSEC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_NSEC_PTP_TOD_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_LTC_PTP_TOD_NSEC_PTP_TOD_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_LTC_PTP_TOD_NSEC_PTP_TOD_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Time Of Day nanosecs fractional part
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PTP_TOD_NSEC_FRAC
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PTP_TOD_NSEC_FRAC(gi)   VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,4)
#define LAN80XX_PTP_LTC_PTP_TOD_NSEC_FRAC(gi)  LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,4))
/**
 * \brief
 * Time Of Day fractional nanoseconds loaded or stored into TimeOfDay.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_NSEC_FRAC . PTP_TOD_NSEC_FRAC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_LTC_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_LTC_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current time of day, NTP sub-second
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:NTP_NSEC
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_NTP_NSEC(gi)            VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,5)

/**
 * \brief
 * Value of NTP counter when load/save action was executed. This value will
 * not be loaded into the timers upon a LOAD operation.  This is for debug
 * only (not visible to customers, not supported in MB25).
 *
 * \details
 * Field: ::VTSS_PTP_LTC_NTP_NSEC . NTP_NSEC
 */
#define  VTSS_F_PTP_LTC_NTP_NSEC_NTP_NSEC(x)  (x)
#define  VTSS_M_PTP_LTC_NTP_NSEC_NTP_NSEC     0xffffffff
#define  VTSS_X_PTP_LTC_NTP_NSEC_NTP_NSEC(x)  (x)


/**
 * \brief Waveform programming
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PIN_WF_HIGH_PERIOD
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PIN_WF_HIGH_PERIOD(gi)  VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,6)
#define LAN80XX_PTP_LTC_PIN_WF_HIGH_PERIOD(gi)  LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,6))

/**
 * \brief
 * Configure waveform. Unit is nanoseconds.EX. 25MHz 60/40 clock:
 * PIN_ACTION=CLOCK, PIN_SYNC=0, PIN_WFH=24, PIN_WFL=16EX. 1 us pulse after
 * 150 ns  PIN_ACTION=CLOCK, PIN_SYNC=1, PIN_WFH=1000, PIN_WFL=150
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PIN_WF_HIGH_PERIOD . PIN_WFH
 */
#define  LAN80XX_F_PTP_LTC_PIN_WF_HIGH_PERIOD_PIN_WFH(x)  LAN80XX_ENCODE_BITFIELD(x,0,30)
#define  LAN80XX_M_PTP_LTC_PIN_WF_HIGH_PERIOD_PIN_WFH     LAN80XX_ENCODE_BITMASK(0,30)
#define  LAN80XX_X_PTP_LTC_PIN_WF_HIGH_PERIOD_PIN_WFH(x)  LAN80XX_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Waveform programming
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PIN_WF_LOW_PERIOD
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PIN_WF_LOW_PERIOD(gi)   VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,7)
#define LAN80XX_PTP_LTC_PIN_WF_LOW_PERIOD(gi)   LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,7))

/**
 * \brief
 * Configure waveform
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PIN_WF_LOW_PERIOD . PIN_WFL
 */
#define  LAN80XX_F_PTP_LTC_PIN_WF_LOW_PERIOD_PIN_WFL(x)  LAN80XX_ENCODE_BITFIELD(x,0,30)
#define  LAN80XX_M_PTP_LTC_PIN_WF_LOW_PERIOD_PIN_WFL     LAN80XX_ENCODE_BITMASK(0,30)
#define  LAN80XX_X_PTP_LTC_PIN_WF_LOW_PERIOD_PIN_WFL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Provide the average skew between output and input pin
 *
 * \details
 * Register: \a PTP_LTC:PTP_PINS:PIN_IOBOUNCH_DELAY
 *
 * @param gi Register: PTP_PINS (??), 0-3
 */
#define VTSS_PTP_LTC_PIN_IOBOUNCH_DELAY(gi)  VTSS_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,8)

/**
 * \brief
 * Return the skew between output and input pin values for the loadstore
 * controller. A value of 0 indicates no skew. A vaule of N indicates a
 * skew of (N>>17)*period of generated clock.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PIN_IOBOUNCH_DELAY . PIN_IOBOUNCH_VAL
 */
#define  VTSS_F_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL(x)  VTSS_ENCODE_BITFIELD(x,3,16)
#define  VTSS_M_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL     VTSS_ENCODE_BITMASK(3,16)
#define  VTSS_X_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_VAL(x)  VTSS_EXTRACT_BITFIELD(x,3,16)

/**
 * \brief
 * Set the time for which the skew detection should run.
 *
 * \details
 * 0: Sample 65K core cycles
 * 1: Sample 256K core cycles
 * n: Sample 65K * 4^n cycles
 *
 * Field: ::VTSS_PTP_LTC_PIN_IOBOUNCH_DELAY . PIN_IOBOUNCH_CFG
 */
#define  VTSS_F_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_LTC_PIN_IOBOUNCH_DELAY_PIN_IOBOUNCH_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)



#define LAN80XX_PTP_EPPS_DET_ADJ(gi)   LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, LAN80XX_IOREG_IX(VTSS_TO_PTP_LTC,0xd000,gi,16,0,9))



#define LAN80XX_F_PTP_EPPS_DET_CFG       LAN80XX_ENCODE_BITFIELD(x,0,6)
#define LAN80XX_M_PTP_EPPS_DEG_CFG       LAN80XX_ENCODE_BITMASK(0,6)
#define LAN80XX_X_PTP_EPPS_DEG_CFG       LAN80XX_EXTRACT_BITFIELD(x,0,6)



/**
 * Register Group: \a PTP_LTC:PTP_CFG
 *
 * PTP controller configuration and status
 */


/**
 * \brief Misc PTP configurations
 *
 * \details
 * Fields have a bit per domain, facilitating multiple doimains to be
 * simultaneously configured.
 *
 * Register: \a PTP_LTC:PTP_CFG:PTP_DOM_CFG
 */
#define VTSS_PTP_LTC_PTP_DOM_CFG             VTSS_IOREG(VTSS_TO_PTP_LTC,0xd04c)
#define LAN80XX_PTP_LTC_PTP_DOM_CFG          LAN80XX_IOREG(MMD_ID_PTP_LTC, 1 , 0xd04c)

/**
 * \brief
 * Enable Main counter.
 *
 * \details
 * 0: Main counter disabled and reset
 * 1: Main counter enabled
 *
 * Field: ::VTSS_PTP_LTC_PTP_DOM_CFG . PTP_ENA
 */

#define  LAN80XX_F_PTP_LTC_PTP_DOM_CFG_PTP_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_PTP_LTC_PTP_DOM_CFG_PTP_ENA   LAN80XX_BIT(3)
#define  LAN80XX_X_PTP_LTC_PTP_DOM_CFG_PTP_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)
/**
 * \brief
 * Hold Main counter.
 *
 * \details
 * 0: Main counter counts if enabled
 * 1: Main counter will stay at the reached value
 *
 * Field: ::VTSS_PTP_LTC_PTP_DOM_CFG . PTP_HOLD
 */
#define  VTSS_F_PTP_LTC_PTP_DOM_CFG_PTP_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_LTC_PTP_DOM_CFG_PTP_HOLD  VTSS_BIT(2)
#define  VTSS_X_PTP_LTC_PTP_DOM_CFG_PTP_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * The PTP_CUR timers will be frozen when this field is set for a domain,
 * in order to return concurrent values.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_DOM_CFG . PTP_TOD_FREEZE
 */
#define  VTSS_F_PTP_LTC_PTP_DOM_CFG_PTP_TOD_FREEZE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_LTC_PTP_DOM_CFG_PTP_TOD_FREEZE  VTSS_BIT(1)
#define  VTSS_X_PTP_LTC_PTP_DOM_CFG_PTP_TOD_FREEZE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Disable reprogramming of clock period for the domain. This field should
 * be set, when clock cfg is changed through multiple register writes.
 *
 * \details
 * 0: Use CLK_PER_CFG registers
 * 1: Use latest programmed value
 *
 * Field: ::VTSS_PTP_LTC_PTP_DOM_CFG . PTP_CLKCFG_DIS
 */
#define  VTSS_F_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_F_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS  VTSS_BIT(0)

#define  LAN80XX_X_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)
#define  LAN80XX_M_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS  LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PTP Clock Reference  configuration
 *
 * \details
 * Register: \a PTP_LTC:PTP_CFG:PTP_CLK_REF_CFG
 */
#define LAN80XX_PTP_LTC_PTP_CLK_REF_CFG         LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd04d)

/**
 * \brief
 * Select which PTP1588_LSC[3:0] pins is used as the clock for synchronous
 * 1PPS in Load/Store operation or the reference clock for 1588_PLL in LTC
 * _CLK generation.
 *
 * \details
 * 0: 1588_LSC[0] is selected
 * 1: 1588_LSC[1] is selected
 * 2: 1588_LSC[2] is selected
 * 3: 1588_LSC[3] is selected
 * 4-7: GND
 *
 * Field: ::VTSS_PTP_LTC_PTP_CLK_REF_CFG . PTP_CLK_REF_SELECT
 */
#define  LAN80XX_F_PTP_LTC_PTP_CLK_REF_CFG_PTP_CLK_REF_SELECT(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_PTP_LTC_PTP_CLK_REF_CFG_PTP_CLK_REF_SELECT     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_PTP_LTC_PTP_CLK_REF_CFG_PTP_CLK_REF_SELECT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


#define PTP1588_LSC_0       0
#define PTP1588_LSC_1       1
#define PTP1588_LSC_2       2
#define PTP1588_LSC_3_P_N   3

/**
 * Register Group: \a PTP_LTC:PTP_INTR
 *
 * PTP controller configuration and status
 */


/**
 * \brief Pending interrupt mask
 *
 * \details
 * Register: \a PTP_LTC:PTP_INTR:PTP_PIN_INTR
 */
#define VTSS_PTP_LTC_PTP_PIN_INTR            VTSS_IOREG(VTSS_TO_PTP_LTC,0xd04e)
#define LAN80XX_PTP_LTC_PTP_PIN_INTR         LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd04e)
/**
 * \brief
 * One bit per pin set when an active edge is seen. (write one to clear)
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_INTR . INTR_PTP
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_INTR_INTR_PTP(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_INTR_INTR_PTP     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_INTR_INTR_PTP(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Enable interrupts per pin
 *
 * \details
 * Register: \a PTP_LTC:PTP_INTR:PTP_PIN_INTR_ENA
 */
#define VTSS_PTP_LTC_PTP_PIN_INTR_ENA        VTSS_IOREG(VTSS_TO_PTP_LTC,0xd04f)
#define LAN80XX_PTP_LTC_PTP_PIN_INTR_ENA     LAN80XX_IOREG(MMD_ID_PTP_LTC, 1 , 0xd04f)
/**
 * \brief
 * Enable interrupt per ptp pin.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_PIN_INTR_ENA . INTR_PTP_ENA
 */
#define  LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(x)  LAN80XX_ENCODE_BITFIELD(x,0,4)
#define  LAN80XX_M_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA     LAN80XX_ENCODE_BITMASK(0,4)
#define  LAN80XX_X_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief LTC drift meas_reach_intr status
 *
 * \details
 * Register: \a PTP_LTC:PTP_INTR:LTC_MEAS_INTR
 */
#define VTSS_PTP_LTC_LTC_MEAS_INTR           VTSS_IOREG(VTSS_TO_PTP_LTC,0xd050)
#define LAN80XX_PTP_LTC_LTC_MEAS_INTR        LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd050)
/**
 * \brief
 * When set, it indicates the meas_counter has reached the threshold.This
 * is a sticky bit. It is write-one cleared.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_INTR . PTP_MEAS_CNT_REACH
 */
#define  LAN80XX_F_PTP_LTC_LTC_MEAS_INTR_PTP_MEAS_CNT_REACH(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_LTC_LTC_MEAS_INTR_PTP_MEAS_CNT_REACH     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_LTC_MEAS_INTR_PTP_MEAS_CNT_REACH(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief LTC drift meas_reach_intr enable
 *
 * \details
 * Register: \a PTP_LTC:PTP_INTR:LTC_MEAS_INTR_ENA
 */
#define VTSS_PTP_LTC_LTC_MEAS_INTR_ENA       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd051)
#define LAN80XX_PTP_LTC_LTC_MEAS_INTR_ENA    LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd051)
/**
 * \brief
 * When set, it will enable a meas_count_reach interrupt when the
 * meas_counter reaches its threshold.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_INTR_ENA . PTP_MEAS_CNT_REACH_INTR_ENA
 */
#define  LAN80XX_F_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Serial embedded TOD store interrupt status
 *
 * \details
 * This is the SER_TOD_STORE interrupt status bit
 *
 * Register: \a PTP_LTC:PTP_INTR:SER_TOD_STORE_INTR
 */
#define VTSS_PTP_LTC_SER_TOD_STORE_INTR      VTSS_IOREG(VTSS_TO_PTP_LTC,0xd052)
#define LAN80XX_PTP_LTC_SER_TOD_STORE_INTR   LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd052)
/**
 * \brief
 * This status bit indicates an embedded TOD is latched into PTP_TOD_SEC
 * field within the selected Load/Store unit. This is write-one cleared.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_SER_TOD_STORE_INTR . TOD_LATCH_DONE
 */
#define  LAN80XX_F_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Serial embedded TOD store interrupt enable
 *
 * \details
 * This bit enable SER_TOD_STORE interrupt. When an embedded TOD value is
 * latched from the selected ptp1588_LSC pin, an interrupt will be
 * generated if this bit is set.

 *
 * Register: \a PTP_LTC:PTP_INTR:SER_TOD_STORE_INT_ENA
 */
#define VTSS_PTP_LTC_SER_TOD_STORE_INT_ENA   VTSS_IOREG(VTSS_TO_PTP_LTC,0xd053)
#define LAN80XX_PTP_LTC_SER_TOD_STORE_INT_ENA LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd053)
/**
 * \brief
 * This bit enable embedded TOD store interrupt. When an embedded TOD value
 * is latched from the selected ptp1588_LSC pin, an interrupt will be
 * generated if this bit is set.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_SER_TOD_STORE_INT_ENA . SER_TOD_STORE_INTR_ENA
 */
#define  LAN80XX_F_PTP_LTC_SER_TOD_STORE_INT_ENA_SER_TOD_STORE_INTR_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_PTP_LTC_SER_TOD_STORE_INT_ENA_SER_TOD_STORE_INTR_ENA     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_SER_TOD_STORE_INT_ENA_SER_TOD_STORE_INTR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Serial embedded TOD load interrupt status
 *
 * \details
 * This is the SER_TOD_LOAD interrupt status bit

 *
 * Register: \a PTP_LTC:PTP_INTR:SER_TOD_LOAD_INTR
 */
#define VTSS_PTP_LTC_SER_TOD_LOAD_INTR       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd054)
#define LAN80XX_PTP_LTC_SER_TOD_LOAD_INTR    LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd054)
/**
 * \brief
 * This status bit indicates an embedded TOD is sent to the Main Count for
 * loading. This status is write-one cleared.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_SER_TOD_LOAD_INTR . TOD_LOAD_DONE
 */
#define  LAN80XX_F_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Serial embedded TOD load interrupt enable
 *
 * \details
 * This bit enable SER_TOD_LOAD interrupt. When an embedded TOD value is
 * sent to the Main count for loading, an interrupt will be generated if
 * this bit is set.

 *
 * Register: \a PTP_LTC:PTP_INTR:SER_TOD_LOAD_INT_ENA
 */
#define VTSS_PTP_LTC_SER_TOD_LOAD_INT_ENA    VTSS_IOREG(VTSS_TO_PTP_LTC,0xd055)
#define LAN80XX_PTP_LTC_SER_TOD_LOAD_INT_ENA LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd055)
/**
 * \brief
 * This bit enable embedded TOD load interrupt. When an embedded TOD value
 * is sent to the Main count for loading, an interrupt will be generated if
 * this bit is set.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_SER_TOD_LOAD_INT_ENA . SER_TOD_LOAD_INTR_ENA
 */
#define  LAN80XX_F_PTP_LTC_SER_TOD_LOAD_INT_ENA_SER_TOD_LOAD_INTR_ENA(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_PTP_LTC_SER_TOD_LOAD_INT_ENA_SER_TOD_LOAD_INTR_ENA  LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_SER_TOD_LOAD_INT_ENA_SER_TOD_LOAD_INTR_ENA(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Current interrupt status
 *
 * \details
 * Register: \a PTP_LTC:PTP_INTR:PTP_INTR_IDENT
 */
#define VTSS_PTP_LTC_PTP_INTR_IDENT          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd056)
#define LAN80XX_PTP_LTC_PTP_INTR_IDENT       LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd056)

/**
 * \brief
 * Bit n will be high if an interrupt is currently pending for pin
 * <n>.Bit[6]: Embedded TOD load interrupt pendingBit[5]: Embedded TOD
 * store interrupt pendingBit[4]: LTC drift measurement interrupt
 * pendingBit[3]: ptp1588_lsc_p/n[3] pin event interrupt pendingBit[2]:
 * ptp1588_lsc[2] pin event interrupt pendingbit[1]: ptp1588_lsc[1] pin
 * event interrupt pendingbit[0]: ptp1588_lsc[0] pin event interrupt
 * pending
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_INTR_IDENT . INTR_PTP_IDENT
 */
#define  LAN80XX_F_PTP_LTC_PTP_INTR_IDENT_INTR_PTP_IDENT(x)  LAN80XX_ENCODE_BITFIELD(x,0,7)
#define  LAN80XX_M_PTP_LTC_PTP_INTR_IDENT_INTR_PTP_IDENT     LAN80XX_ENCODE_BITMASK(0,7)
#define  LAN80XX_X_PTP_LTC_PTP_INTR_IDENT_INTR_PTP_IDENT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,7)

/**
 * Register Group: \a PTP_LTC:PTP_TOD_DOMAINS
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
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:CLK_PER_CFG
 *
 * @param ri Register: CLK_PER_CFG (??), 0-1
 */
#define VTSS_PTP_LTC_CLK_PER_CFG(ri)         VTSS_IOREG(VTSS_TO_PTP_LTC,0xd057 + (ri))
#define LAN80XX_PTP_LTC_CLK_PER_CFG(ri)      LAN80XX_IOREG(MMD_ID_PTP_LTC,1, (0xd057 + (ri)))

/**
 * \brief
 * Clock period configuration for the domain.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_CLK_PER_CFG . CLK_PER_VAL
 */
#define  VTSS_F_PTP_LTC_CLK_PER_CFG_CLK_PER_VAL(x)  (x)
#define  VTSS_M_PTP_LTC_CLK_PER_CFG_CLK_PER_VAL     0xffffffff
#define  VTSS_X_PTP_LTC_CLK_PER_CFG_CLK_PER_VAL(x)  (x)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, nanoseconds part.
 *
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:PTP_CUR_NSEC
 */
#define LAN80XX_PTP_LTC_PTP_CUR_NSEC            (0xd059)

/**
 * \brief
 * Time of day nanoseconds.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_CUR_NSEC . PTP_CUR_NSEC
 */
#define  VTSS_F_PTP_LTC_PTP_CUR_NSEC_PTP_CUR_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_LTC_PTP_CUR_NSEC_PTP_CUR_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_LTC_PTP_CUR_NSEC_PTP_CUR_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, fractional nanoseconds part.
 *
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:PTP_CUR_NSEC_FRAC
 */
#define LAN80XX_PTP_LTC_PTP_CUR_NSEC_FRAC       (0xd05a)

/**
 * \brief
 * Time of day fractional naoseconds (unit is nsec/256), latched when NSEC
 * was read.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_CUR_NSEC_FRAC . PTP_CUR_NSEC_FRAC
 */
#define  VTSS_F_PTP_LTC_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_LTC_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_LTC_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Current time of day
 *
 * \details
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:PTP_CUR_SEC_LSB
 */
#define LAN80XX_PTP_LTC_PTP_CUR_SEC_LSB         (0xd05b)

/**
 * \brief
 * Value of current tod secs, latched when NSEC was read.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_CUR_SEC_LSB . PTP_CUR_SEC_LSB
 */
#define  VTSS_F_PTP_LTC_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_LTC_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_LTC_PTP_CUR_SEC_LSB_PTP_CUR_SEC_LSB(x)  (x)


/**
 * \brief Current time of day
 *
 * \details
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:PTP_CUR_SEC_MSB
 */
#define LAN80XX_PTP_LTC_PTP_CUR_SEC_MSB         (0xd05c)




/**
 * \brief
 * Current time of day, seconds part, latched when NSEC was read
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_CUR_SEC_MSB . PTP_CUR_SEC_MSB
 */
#define  VTSS_F_PTP_LTC_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Current time of day
 *
 * \details
 * Current time of day, NTP fractional seconds part.
 * This is for debug only.
 *
 * Register: \a PTP_LTC:PTP_TOD_DOMAINS:NTP_CUR_NSEC
 */
#define VTSS_PTP_LTC_NTP_CUR_NSEC            VTSS_IOREG(VTSS_TO_PTP_LTC,0xd05d)

/**
 * \brief
 * Time of day fractional second, latched when NSEC was read.This is for
 * debug only, not supported in MB25.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_NTP_CUR_NSEC . NTP_CUR_NSEC
 */
#define  VTSS_F_PTP_LTC_NTP_CUR_NSEC_NTP_CUR_NSEC(x)  (x)
#define  VTSS_M_PTP_LTC_NTP_CUR_NSEC_NTP_CUR_NSEC     0xffffffff
#define  VTSS_X_PTP_LTC_NTP_CUR_NSEC_NTP_CUR_NSEC(x)  (x)

/**
 * Register Group: \a PTP_LTC:PTP_LOAD_STORE_DELAY_CONFIGURATION
 *
 * PTP Load and Store Delay Control group
 */


/**
 * \brief Load Delay Configuration
 *
 * \details
 * Register: \a PTP_LTC:PTP_LOAD_STORE_DELAY_CONFIGURATION:PIN_LOAD_DELAY_CFG
 */
#define LAN80XX_PTP_LTC_PIN_LOAD_DELAY_CFG      LAN80XX_IOREG(MMD_ID_PTP_LTC, 1, 0xd05e)

/**
 * \brief
 * This register is used for delay configuration used in Async/Sync
 * embedded or non-embedded load  operation. It could include the delay
 * from the external module generating the 1PPS pulse to the pin of MB25
 * (external delay) and the delay from the pin (PTP1588_LSC[x]) to internal
 * event sampling logic (internal delay). The user has to adjust the value
 * of this register depending on 1) embedded or non-embedded LOAD operation
 * is executed 2) which LS_controllers is used 3) which PTP1588_LSC[x] is
 * selected. This value will be added to TOD during load.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PIN_LOAD_DELAY_CFG . PTP_LOAD_DELAY
 */
#define  LAN80XX_F_PTP_LTC_PIN_LOAD_DELAY_CFG_PTP_LOAD_DELAY(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_PTP_LTC_PIN_LOAD_DELAY_CFG_PTP_LOAD_DELAY     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_PTP_LTC_PIN_LOAD_DELAY_CFG_PTP_LOAD_DELAY(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Store  Pin Delay Configuration One
 *
 * \details
 * Register: \a PTP_LTC:PTP_LOAD_STORE_DELAY_CONFIGURATION:PIN_STORE_DELAY_CFG
 *
 * @param ri Register: PIN_STORE_DELAY_CFG (??), 0-3
 */
#define VTSS_PTP_LTC_PIN_STORE_DELAY_CFG(ri)  VTSS_IOREG(VTSS_TO_PTP_LTC,0xd05f + (ri))

/**
 * \brief
 * This register is used for delay configuration used in Async/Sync
 * embedded or non-embedded store operation. It could include the delay
 * from the external module generating the 1PPS pulse to the pin of MB25
 * (external delay) and the delay from the pin (PTP1588_LSC[x]) to internal
 * event sampling logic (internal delay). The user has to adjust the value
 * of this register depending on 1) embedded or non-embedded LOAD operation
 * is executed 2) which LS_controllers is used 3) which PTP1588_LSC[x] is
 * selected. This value will subtracted from TOD during store.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PIN_STORE_DELAY_CFG . PTP_STORE_DELAY
 */
#define  VTSS_F_PTP_LTC_PIN_STORE_DELAY_CFG_PTP_STORE_DELAY(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_PIN_STORE_DELAY_CFG_PTP_STORE_DELAY     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_PIN_STORE_DELAY_CFG_PTP_STORE_DELAY(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a PTP_LTC:PTP_SER_TOD_LOAD_STORE
 *
 * PTP Serial TOD Load Control group
 */


/**
 * \brief Serial TOD Load Configuration
 *
 * \details
 * Register: \a PTP_LTC:PTP_SER_TOD_LOAD_STORE:PTP_SER_TOD_LOAD_STORE_CFG
 */
#define LAN80XX_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG  LAN80XX_IOREG(MMD_ID_PTP_LTC, 1 ,0xd063)

/**
 * \brief
 * This bit enables the fast mode. (for simulation purpose only)Once the
 * FASTMODE is on, the following  configurable count is fixed at much
 * shorted value as shown below:PIN_SER_TOD_ONE_USECOND_PERIOD_CFG =
 * 10'd9PIN_SER_TOD_ONE_SECOND_PERIOD_CFG =  20'd499Note: This is for
 * simulation purpose only. It should not be turned on in the real
 * application.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_FASTMODE_EN
 */
#define  VTSS_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_FASTMODE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_FASTMODE_EN  VTSS_BIT(31)
#define  VTSS_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_FASTMODE_EN(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * This control bits select which load/store unit is used in SER_TOD_LOAD
 * function.Once the load/store unit is selected, its PTP_PIN_SELECT,
 * PTP_CLK_SELECT and PTP_PIN_INV_POL controls will be used in PTP serial
 * TOD load and store configuration.
 *
 * \details
 * 2'b00 : Load/Store unit 0 (or ptp_ls_0)
 * 2'b01:  Load/Store unit 1 (or ptp_ls_1)
 * 2'b10:  Load/Store unit 2 (or ptp_ls_2)
 * 2'b11:  Load/Store unit 3 (or ptp_ls_3)

 *
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_LS_UNIT_SEL
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LS_UNIT_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,7,2)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LS_UNIT_SEL     LAN80XX_ENCODE_BITMASK(7,2)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LS_UNIT_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,7,2)

/**
 * \brief
 * When set, the serial TOD out will be loopback to serial TOD in. This is
 * mainly for serial TOD loopback test only.It's good for input/output pin
 * delay adjustment test. To get this loopback mode working, the TOD out
 * and TOD in configuration has to be insync which includes pin select,
 * polarity, fast mode and the pulse period, etc.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_PAD_LPBK
 */
#define  VTSS_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_PAD_LPBK(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_PAD_LPBK  VTSS_BIT(6)
#define  VTSS_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_PAD_LPBK(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When set, the data is at {bit7,...,bit0} order.When cleared, the data is
 * at {bit0,...,bit7} order.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_INPUT_MSB_BIT_FIRST
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BIT_FIRST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BIT_FIRST     LAN80XX_BIT(5)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BIT_FIRST(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When set, the data is at {MSB, ..., LSB} order.When cleared, the data is
 * at {LSB,..., MSB} order.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_INPUT_MSB_BYTE_FIRST
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BYTE_FIRST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),4,1)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BYTE_FIRST     LAN80XX_BIT(4)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BYTE_FIRST(x)  LAN80XX_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * When set, the SER_TOD_INPUT_EN control bit will be cleared once the
 * embed TOD is loaded into Main TOD register. So, the TOD update will be
 * done once.When cleared, the SER_TOD_INPUT_EN control bit will stay at
 * high till it is configured to zero.  So, the TOD update will be done
 * every second till either SER_TOD_LOAD_EN/SER_TOD_SZTORE_EN is cleared or
 * SER_TOD_LOAD_STORE_AUTO_CLR is set. Expect an interrupt will be
 * generated immediately after a TOD is stored at the selected load/store
 * unit.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_LOAD_STORE_AUTO_CLR
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_STORE_AUTO_CLR(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_STORE_AUTO_CLR     LAN80XX_BIT(2)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_STORE_AUTO_CLR(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This bit will Enable TOD store operation from the selected Load/Store
 * unit.The PTP_PIN_SELECT control bits selects which ptp1588_LSC[3:0] pins
 * is used for embedded TOD latch.Once the embedded TOD value is latched
 * from the selected ptp1588_LSC pins, the captured value plus one is
 * loaded into the PTP_TOD_SEC_MSB and PTP_TOD_SEC_LSB field within the L/S
 * unit. This control bit will be auto clear when the embedded TOD value is
 * latched if SER_TOD_LOAD_STORE_AUTO_CLR is set. An interrupt will be
 * generated when TOD value is loaded into PTP_TOD_SEC if the associated
 * interrupt is enable.Note: ePPS is not supported in this feature.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_STORE_EN
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_STORE_EN(x)  LAN80XX_ENCODE_BITFIELD((x),1,1)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_STORE_EN     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_STORE_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable TOD load operation from one of the four PPS TOD embedded
 * LSC[3:0] pins.This control bit will be auto clear if
 * SER_TOD_LOAD_AUTO_CLR is set.Note: ePPS is not supported in this
 * feature.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG . SER_TOD_LOAD_EN
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_EN(x)  LAN80XX_ENCODE_BITFIELD((x),0,1)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_EN     LAN80XX_BIT(0)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief PTP Serial TOD Load Period Configuration
 *
 * \details
 * Register: \a PTP_LTC:PTP_SER_TOD_LOAD_STORE:PTP_SER_TOD_LOAD_PERIOD_CFG
 */
#define LAN80XX_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG  LAN80XX_IOREG(MMD_ID_PTP_LTC,1,0xd064)

/**
 * \brief
 * This bits defines one micro-second period in term of how many 1588 clock
 * cycles.If 1588 clock rate is 318.31 MHz, the register will be configured
 * as 9'd318 at default[Note: 1000/318.31 ~= 3.141592.  1000/3.141592 =
 * 318.31]318 x 3.141592 ~= 999.03 ns  ( 1ns is short for every 1 us
 * period.)This inaccuracy per 1 us should not cause a problem to latch the
 * embedded TOD correctly.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG . PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG
 */
#define  LAN80XX_S_F_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG(x) LAN80XX_ENCODE_BITFIELD(x,20,10)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG      LAN80XX_ENCODE_BITMASK(20,10)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG(x)   LAN80XX_EXTRACT_BITFIELD(x,20,10)

/**
 * \brief
 * These bits defines roughly the 1 SEC wait period in term of how many
 * microsecond cycles defined in PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG
 * which the DUT should wait before it starts to detect a pulse and treat
 * it as the next PPS for load.  The default value of this register is
 * 1000000.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG . PIN_SER_TOD_ONE_SECOND_WAIT_PERIOD_CFG
 */
#define  LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_SECOND_WAIT_PERIOD_CFG(x)  LAN80XX_ENCODE_BITFIELD(x,0,20)
#define  LAN80XX_M_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_SECOND_WAIT_PERIOD_CFG     LAN80XX_ENCODE_BITMASK(0,20)
#define  LAN80XX_X_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_SECOND_WAIT_PERIOD_CFG(x)  LAN80XX_EXTRACT_BITFIELD(x,0,20)

/**
 * Register Group: \a PTP_LTC:DRIFT_MEAS_CTRL
 *
 * Drift Measurement Control
 */


/**
 * \brief LTC drift measurement control
 *
 * \details
 * This register mainly controls the measurement operation.

 *
 * Register: \a PTP_LTC:DRIFT_MEAS_CTRL:LTC_MEAS_CTRL
 */
#define VTSS_PTP_LTC_LTC_MEAS_CTRL           VTSS_IOREG(VTSS_TO_PTP_LTC,0xd065)

/**
 * \brief
 * Select reference clock from 1588_lsc pins or LTC clockDefault: 3'b100
 *
 * \details
 * 3'b000: select PTP1588_LSC[0]
 * 3'b001: select PTP1588_LSC[1]
 * 3'b010: select PTP1588_LSC[2]
 * 3'b011: select PTP1588_LSC[3]
 * 3'b100: select LTC_CLK
 *
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . REF_CLK_SEL
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_REF_CLK_SEL     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Write one to reset meas_counter and TOD1/TOD2 registers. This command
 * should be issued before starting drift measurement. This bit is
 * self-clearing.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . INIT_MEAS_CMD
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_INIT_MEAS_CMD(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_INIT_MEAS_CMD  VTSS_BIT(7)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_INIT_MEAS_CMD(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This status bit indicates the drift measurement is active or not. It
 * will be active when START_MEAS_CMD is issued. It will be off when the
 * following conditions meet:1) The meas_count reaches the threshold and
 * the loop count is disabled.2) The init_mea_cmd is issued3) The
 * freeze_mease_counter command is issued.
 *
 * \details
 * 1: ON (Drift measurement is active right now.)
 * 0: OFF( Drift measurement is off right now.)

 *
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . DRIFT_MEAS_ON_OFF_STAT
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_DRIFT_MEAS_ON_OFF_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_DRIFT_MEAS_ON_OFF_STAT  VTSS_BIT(3)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_DRIFT_MEAS_ON_OFF_STAT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 *
 * Write one to this bit will activate the following operations:1) Freeze
 * the counting on meas_counter. The value of the meas_counter could be
 * read out by s/w for diagnostic. 2) Capture the converted TOD to TOD1
 * register while the meas_counter is frozen.3) Shift TOD1 data to TOD2
 * register at the same time.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . FREEZE_MEAS_COUNTER
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_FREEZE_MEAS_COUNTER(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_FREEZE_MEAS_COUNTER  VTSS_BIT(2)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_FREEZE_MEAS_COUNTER(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * when set, the meas_counter will wrap around to zero when hits the
 * programmed threshold value and continue counting from zero.when cleared,
 * the meas_counter will stop counting when the meas_count hits the
 * threshold value and stays with the value.The interrupt for the
 * meas_count reaches the threshold value will be generated if the
 * interrupt enable is set.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . LOOP_COUNT_EN
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_LOOP_COUNT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_LOOP_COUNT_EN  VTSS_BIT(1)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_LOOP_COUNT_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Write one to this bit to start LTC drift measurement operation. This bit
 * is self-clearing.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_MEAS_CTRL . START_MEAS_CMD
 */
#define  VTSS_F_PTP_LTC_LTC_MEAS_CTRL_START_MEAS_CMD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PTP_LTC_LTC_MEAS_CTRL_START_MEAS_CMD  VTSS_BIT(0)
#define  VTSS_X_PTP_LTC_LTC_MEAS_CTRL_START_MEAS_CMD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief the current value of meas_counter
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_CTRL:MEAS_COUNT
 *
 * @param ri Register: MEAS_COUNT (??), 0-1
 */
#define VTSS_PTP_LTC_MEAS_COUNT(ri)          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd066 + (ri))

/**
 * \brief
 * the current value of meas_counter. This counter is incremented by 1 per
 * reference clock cycle when DRIFT_MEAS_ON_OFF_STAT is one. Its value will
 * be read out after a freeze_meas_counter command is issued.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_MEAS_COUNT . MEAS_COUNT_VAL
 */
#define  VTSS_F_PTP_LTC_MEAS_COUNT_MEAS_COUNT_VAL(x)  (x)
#define  VTSS_M_PTP_LTC_MEAS_COUNT_MEAS_COUNT_VAL     0xffffffff
#define  VTSS_X_PTP_LTC_MEAS_COUNT_MEAS_COUNT_VAL(x)  (x)


/**
 * \brief the threshold value of meas_count
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_CTRL:MEAS_THRESHOLD
 *
 * @param ri Register: MEAS_THRESHOLD (??), 0-1
 */
#define VTSS_PTP_LTC_MEAS_THRESHOLD(ri)      VTSS_IOREG(VTSS_TO_PTP_LTC,0xd068 + (ri))

/**
 * \brief
 * The targeted counter value to generate a pulse to latch a converted TOD
 * to PTP_TOD_1 and shift PTP_TOD_1 to PTP_TOD_2 when the meas_counter
 * reaches this value.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_MEAS_THRESHOLD . MEAS_THRESHOLD_VAL
 */
#define  VTSS_F_PTP_LTC_MEAS_THRESHOLD_MEAS_THRESHOLD_VAL(x)  (x)
#define  VTSS_M_PTP_LTC_MEAS_THRESHOLD_MEAS_THRESHOLD_VAL     0xffffffff
#define  VTSS_X_PTP_LTC_MEAS_THRESHOLD_MEAS_THRESHOLD_VAL(x)  (x)

/**
 * Register Group: \a PTP_LTC:DRIFT_MEAS_TOD
 *
 * Drift Measurement latched TOD
 */


/**
 * \brief Time Of Day MSB
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_1_SEC_MSB
 */
#define VTSS_PTP_LTC_PTP_TOD_1_SEC_MSB       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06a)

/**
 * \brief
 * Bits 47:32 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_1_SEC_MSB . PTP_TOD_1_SEC_MSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_1_SEC_MSB_PTP_TOD_1_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_PTP_TOD_1_SEC_MSB_PTP_TOD_1_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_PTP_TOD_1_SEC_MSB_PTP_TOD_1_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Time Of Day LSB
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_1_SEC_LSB
 */
#define VTSS_PTP_LTC_PTP_TOD_1_SEC_LSB       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06b)

/**
 * \brief
 * Bits 31:0 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_1_SEC_LSB . PTP_TOD_1_SEC_LSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_1_SEC_LSB_PTP_TOD_1_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_LTC_PTP_TOD_1_SEC_LSB_PTP_TOD_1_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_LTC_PTP_TOD_1_SEC_LSB_PTP_TOD_1_SEC_LSB(x)  (x)


/**
 * \brief Time Of Day nanosecs part
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_1_NSEC
 */
#define VTSS_PTP_LTC_PTP_TOD_1_NSEC          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06c)

/**
 * \brief
 * Time Of Day nanoseconds loaded or stored into TimeOfDay. A synced store
 * operation may return a value between -2 and 999.999.999 in this field.
 * To normalize the complete TOD, in case field is read 0x3ffffffe/f,
 * software must subtract one from the SEC part, and add 1.000.000.000 to
 * the NSEC part.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_1_NSEC . PTP_TOD_1_NSEC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_1_NSEC_PTP_TOD_1_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_LTC_PTP_TOD_1_NSEC_PTP_TOD_1_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_LTC_PTP_TOD_1_NSEC_PTP_TOD_1_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Time Of Day nanosecs fractional part
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_1_NSEC_FRAC
 */
#define VTSS_PTP_LTC_PTP_TOD_1_NSEC_FRAC     VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06d)
/**
 * \brief
 * Time Of Day fractional nanoseconds loaded or stored into TimeOfDay.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_1_NSEC_FRAC . PTP_TOD_1_NSEC_FRAC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_1_NSEC_FRAC_PTP_TOD_1_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_LTC_PTP_TOD_1_NSEC_FRAC_PTP_TOD_1_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_LTC_PTP_TOD_1_NSEC_FRAC_PTP_TOD_1_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Time Of Day MSB
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_2_SEC_MSB
 */
#define VTSS_PTP_LTC_PTP_TOD_2_SEC_MSB       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06e)

/**
 * \brief
 * Bits 47:32 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_2_SEC_MSB . PTP_TOD_2_SEC_MSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_2_SEC_MSB_PTP_TOD_2_SEC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_PTP_TOD_2_SEC_MSB_PTP_TOD_2_SEC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_PTP_TOD_2_SEC_MSB_PTP_TOD_2_SEC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Time Of Day LSB
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_2_SEC_LSB
 */
#define VTSS_PTP_LTC_PTP_TOD_2_SEC_LSB       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd06f)

/**
 * \brief
 * Bits 31:0 of the time-of-day seconds
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_2_SEC_LSB . PTP_TOD_2_SEC_LSB
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_2_SEC_LSB_PTP_TOD_2_SEC_LSB(x)  (x)
#define  VTSS_M_PTP_LTC_PTP_TOD_2_SEC_LSB_PTP_TOD_2_SEC_LSB     0xffffffff
#define  VTSS_X_PTP_LTC_PTP_TOD_2_SEC_LSB_PTP_TOD_2_SEC_LSB(x)  (x)


/**
 * \brief Time Of Day nanosecs part
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_2_NSEC
 */
#define VTSS_PTP_LTC_PTP_TOD_2_NSEC          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd070)

/**
 * \brief
 * Time Of Day nanoseconds loaded or stored into TimeOfDay. A synced store
 * operation may return a value between -2 and 999.999.999 in this field.
 * To normalize the complete TOD, in case field is read 0x3ffffffe/f,
 * software must subtract one from the SEC part, and add 1.000.000.000 to
 * the NSEC part.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_2_NSEC . PTP_TOD_2_NSEC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_2_NSEC_PTP_TOD_2_NSEC(x)  VTSS_ENCODE_BITFIELD(x,0,30)
#define  VTSS_M_PTP_LTC_PTP_TOD_2_NSEC_PTP_TOD_2_NSEC     VTSS_ENCODE_BITMASK(0,30)
#define  VTSS_X_PTP_LTC_PTP_TOD_2_NSEC_PTP_TOD_2_NSEC(x)  VTSS_EXTRACT_BITFIELD(x,0,30)


/**
 * \brief Time Of Day nano-secs fractional part
 *
 * \details
 * Register: \a PTP_LTC:DRIFT_MEAS_TOD:PTP_TOD_2_NSEC_FRAC
 */
#define VTSS_PTP_LTC_PTP_TOD_2_NSEC_FRAC     VTSS_IOREG(VTSS_TO_PTP_LTC,0xd071)

/**
 * \brief
 * Time Of Day fractional nanoseconds loaded or stored into TimeOfDay.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_PTP_TOD_2_NSEC_FRAC . PTP_TOD_2_NSEC_FRAC
 */
#define  VTSS_F_PTP_LTC_PTP_TOD_2_NSEC_FRAC_PTP_TOD_2_NSEC_FRAC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_PTP_LTC_PTP_TOD_2_NSEC_FRAC_PTP_TOD_2_NSEC_FRAC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_PTP_LTC_PTP_TOD_2_NSEC_FRAC_PTP_TOD_2_NSEC_FRAC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a PTP_LTC:DRIFT_PHASE_DETECTOR_CTRL
 *
 * High precision event detection Configuration and Status Registers
 */


/**
 * \brief Phase detection control
 *
 * \details
 * For timestamping and phase detection to work reliably, the clock domains
 * must be reset after clock change, ie when the link is detected up and
 * stable.
 *
 * Register: \a PTP_LTC:DRIFT_PHASE_DETECTOR_CTRL:DF_PHAD_CTRL
 */
#define VTSS_PTP_LTC_DF_PHAD_CTRL            VTSS_IOREG(VTSS_TO_PTP_LTC,0xd072)

/**
 * \brief
 * Phase detector is locked to port clock. This indicates that the error
 * level has been lower than the cfg_lock configuration for the past 5
 * times an error is seen.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . PHAD_LOCK
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_PHAD_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_PHAD_LOCK  VTSS_BIT(18)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_PHAD_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Event clock is currently divided by this
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . DIV_STATE
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_DIV_STATE(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_DIV_STATE     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_DIV_STATE(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Phase detector has adjusted phase down(bit 0) or up(bit 1).

 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . PHAD_ADJ
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_PHAD_ADJ(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_PHAD_ADJ     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_PHAD_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/**
 * \brief
 * Configure wjat the PHAD_ERR_STAT shows
 *
 * \details
 * 0: Show the latest error level
 * 1: Show the largests error level
 *
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . ERR_MAX_ENA
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_ERR_MAX_ENA  VTSS_BIT(12)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_ERR_MAX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

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
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . DIV_CFG
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_DIV_CFG(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_DIV_CFG     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_DIV_CFG(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

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
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . TWEAKS
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_TWEAKS(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_TWEAKS     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_TWEAKS(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Enable high accuracy TOD transfer
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . PHAD_ENA
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_PHAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_PHAD_ENA  VTSS_BIT(5)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_PHAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * The high accuracy TOD phase detector can operator in two
 * modes:RANGEMODE: Main TOD is sampled at every port clock edge and
 * verified to be within 0-1 main LTC clock cycles off predicted port TOD.
 * Otherwise port TOD is moved into range.SYNCMODE: Main TOD is sampled at
 * main clock edges falling close to a port clock edge, and port TOD is set
 * to the sampled value. The close edge detection is based on concurrent
 * sampling of the port clock and a delayed version (see TWEAKS).
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . PHAD_MODE
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_PHAD_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_PHAD_MODE  VTSS_BIT(4)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_PHAD_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Phase detector has lost lock since the clearing of the bit. Can be
 * cleared writing one to this field.

 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . PHAD_FAILED
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_PHAD_FAILED(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_PHAD_FAILED  VTSS_BIT(3)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_PHAD_FAILED(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Phase is assumed locked when it is never outside 60 ps x (2**LOCK_ACC)
 * from expected range.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CTRL . LOCK_ACC
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CTRL_LOCK_ACC(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_PTP_LTC_DF_PHAD_CTRL_LOCK_ACC     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_PTP_LTC_DF_PHAD_CTRL_LOCK_ACC(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Phase detection status
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_LTC:DRIFT_PHASE_DETECTOR_CTRL:DF_PHAD_CYC_STAT
 */
#define VTSS_PTP_LTC_DF_PHAD_CYC_STAT        VTSS_IOREG(VTSS_TO_PTP_LTC,0xd073)

/**
 * \brief
 * Detected event clock period in 16.16 fixedpoint format.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_CYC_STAT . PHAD_CYCLETIME
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)
#define  VTSS_M_PTP_LTC_DF_PHAD_CYC_STAT_PHAD_CYCLETIME     0xffffffff
#define  VTSS_X_PTP_LTC_DF_PHAD_CYC_STAT_PHAD_CYCLETIME(x)  (x)


/**
 * \brief Phase detection error
 *
 * \details
 * Cycle time detected
 *
 * Register: \a PTP_LTC:DRIFT_PHASE_DETECTOR_CTRL:DF_PHAD_ERR_STAT
 */
#define VTSS_PTP_LTC_DF_PHAD_ERR_STAT        VTSS_IOREG(VTSS_TO_PTP_LTC,0xd074)

/**
 * \brief
 * Latest or maximum error detected in alignment process with format 10.8
 * fixedpoint format. ERR_MAX_ENA determines mode.
 *
 * \details
 * Field: ::VTSS_PTP_LTC_DF_PHAD_ERR_STAT . PHAD_ERR_STAT
 */
#define  VTSS_F_PTP_LTC_DF_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_PTP_LTC_DF_PHAD_ERR_STAT_PHAD_ERR_STAT     VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_PTP_LTC_DF_PHAD_ERR_STAT_PHAD_ERR_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,19)

/**
 * Register Group: \a PTP_LTC:LTC_SPARE_REG
 *
 * LTC spare register
 */


/**
 * \brief LTC spare register configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_SPARE_REG:LTC_SPARE_REG_CFG
 */
#define VTSS_PTP_LTC_LTC_SPARE_REG_CFG       VTSS_IOREG(VTSS_TO_PTP_LTC,0xd075)

/**
 * \brief
 * LTC 32-bit spare register . default; FF00_0000
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_SPARE_REG_CFG . LTC_SPACE_REGS
 */
#define  VTSS_F_PTP_LTC_LTC_SPARE_REG_CFG_LTC_SPACE_REGS(x)  (x)
#define  VTSS_M_PTP_LTC_LTC_SPARE_REG_CFG_LTC_SPACE_REGS     0xffffffff
#define  VTSS_X_PTP_LTC_LTC_SPARE_REG_CFG_LTC_SPACE_REGS(x)  (x)

/**
 * Register Group: \a PTP_LTC:LTC_DEBUG
 *
 * LTC Debug register
 */


/**
 * \brief LTC debug 0 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG0_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG0_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0f8)

/**
 * \brief
 * LTC debug 0 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG0_CFG . LTC_DEBUG0
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG0_CFG_LTC_DEBUG0(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG0_CFG_LTC_DEBUG0     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG0_CFG_LTC_DEBUG0(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 1 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG1_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG1_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0f9)

/**
 * \brief
 * LTC debug 1 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG1_CFG . LTC_DEBUG1
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG1_CFG_LTC_DEBUG1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG1_CFG_LTC_DEBUG1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG1_CFG_LTC_DEBUG1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 2 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG2_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG2_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0fa)

/**
 * \brief
 * LTC debug 2 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG2_CFG . LTC_DEBUG2
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG2_CFG_LTC_DEBUG2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG2_CFG_LTC_DEBUG2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG2_CFG_LTC_DEBUG2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 3 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG3_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG3_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0fb)

/**
 * \brief
 * LTC debug 3 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG3_CFG . LTC_DEBUG3
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG3_CFG_LTC_DEBUG3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG3_CFG_LTC_DEBUG3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG3_CFG_LTC_DEBUG3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 4 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG4_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG4_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0fc)

/**
 * \brief
 * LTC debug 4 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG4_CFG . LTC_DEBUG4
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG4_CFG_LTC_DEBUG4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG4_CFG_LTC_DEBUG4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG4_CFG_LTC_DEBUG4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 5 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG5_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG5_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0fd)

/**
 * \brief
 * LTC debug 5 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG5_CFG . LTC_DEBUG5
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG5_CFG_LTC_DEBUG5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG5_CFG_LTC_DEBUG5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG5_CFG_LTC_DEBUG5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 6 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG6_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG6_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0fe)

/**
 * \brief
 * LTC debug 6 register
 *
 * \details
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG6_CFG . LTC_DEBUG6
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG6_CFG_LTC_DEBUG6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG6_CFG_LTC_DEBUG6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG6_CFG_LTC_DEBUG6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief LTC debug 7 configuration
 *
 * \details
 * Register: \a PTP_LTC:LTC_DEBUG:LTC_DEBUG7_CFG
 */
#define VTSS_PTP_LTC_LTC_DEBUG7_CFG          VTSS_IOREG(VTSS_TO_PTP_LTC,0xd0ff)

/**
 * \brief
 * LTC debug 7 register
 *
 * \details
 * bit[1:0]: select 1 out of  4 sub-groups for LTC_DEBUG0
 * bit[3;2]: select 1 out of  4 sub-groups for LTC_DEBUG1
 * bit[5:4]: select 1 out of  4 sub-groups for LTC_DEBUG2
 * bit[7:6]: select 1 out of  4 sub-groups for LTC_DEBUG3
 * bit[9:8]: select 1 out of  4 sub-groups for LTC_DEBUG4
 * bit[12:10]: select 1 out of 8 sub-groups for LTC_DEBUG5    [note:
 * bit[12] may not be used when only 4 sub-groups are provided.]
 * bit[15:13]: select 1 out of 8 sub-groups for LTC_DEBUG6    [note:
 * bit[15] may not be used when only 4 sub-groups are provided.]
 *
 * Field: ::VTSS_PTP_LTC_LTC_DEBUG7_CFG . LTC_DEBUG7
 */
#define  VTSS_F_PTP_LTC_LTC_DEBUG7_CFG_LTC_DEBUG7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PTP_LTC_LTC_DEBUG7_CFG_LTC_DEBUG7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PTP_LTC_LTC_DEBUG7_CFG_LTC_DEBUG7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_MALIBU25G_REGS_PTP_LTC_H_ */
