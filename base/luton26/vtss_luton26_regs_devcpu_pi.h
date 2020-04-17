// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_DEVCPU_PI_H_
#define _VTSS_LUTON26_REGS_DEVCPU_PI_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEVCPU_PI
 *
 * CPU Device Parallel Interface
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_PI:PI
 *
 * Registers for the parallel interface
 */


/** 
 * \brief Control of PI accesses
 *
 * \details
 * Register: \a DEVCPU_PI:PI:PI_CTRL
 */
#define VTSS_DEVCPU_PI_PI_PI_CTRL            VTSS_IOREG(VTSS_TO_DEVCPU_PI,0x0)

/** 
 * \brief
 * Use this field to select a destination index register for slow access
 * results. By using different indexes it is possible to have more than one
 * outstanding slow-access at any given time. This may be utilized by
 * interrupt routines, just remember that an interrupt routine should
 * restore this register to its previous value before exiting the routine.
 * Note: If multiple levels of interrupts is required, more than there are
 * slow-access-indexes, then it is possible for the high-priority interrupt
 * routine to use normal-accesses (by disabling slow-access via SLOW_ENA),
 * then the PI will be occupied while reading - but that access will not
 * interfere with any ongoing slow accesses.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_CTRL . SLOW_IDX
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_CTRL_SLOW_IDX  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to enable slow accesses. For a normal accesses ("slow" is
 * not enabled) the PI access will be stalled until data is ready to be
 * read out of the device. When slow-data is enabled then a read from any 
 * register (except these PI registers) will return immediately - the read
 * will then be processed will the external CPU is free to do something
 * else.
 * The field SLOW_IN_PROGRESS indicates when slow accesses are done, once
 * the access has completed the result can be read from the SLOWDATA
 * register at the index corresponding to the SLOW_IDX that was used when
 * the access was initiated.
 * When slow access is enabled, the the data which is returned when the
 * access is started is actually the result from the corresponding SLOWDATA
 * register, this means that it is possible to do "back-to-back" slow
 * accesses, every time a new slow-access is started - the result of the
 * old access is read out.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_CTRL . SLOW_ENA
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_CTRL_SLOW_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration of PI accesses
 *
 * \details
 * Register: \a DEVCPU_PI:PI:PI_CFG
 */
#define VTSS_DEVCPU_PI_PI_PI_CFG             VTSS_IOREG(VTSS_TO_DEVCPU_PI,0x1)

/** 
 * \brief
 * Set this field to enable busy feedback to the physical PI. When set
 * origin-busy causes the physical interface to delay sampling of data (and
 * generating of ndone).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_CFG . BUSY_FEEDBACK_ENA
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_CFG_BUSY_FEEDBACK_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Set this field to hold write accesses until the write-request has
 * reached the target. By default write accesses is completed as soon as
 * the write is detected (by the PI).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_CFG . WR_ACK_ENA
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_CFG_WR_ACK_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Configures the delay from detecting asserted PI_nCS until the chip
 * samples the control signals. The delay is configured in steps of 8ns.
 * This field should be lowered to match the performance and interface
 * timing of the external CPU.
 * This field can be set to zero, in that case the control signals will be
 * sampled immediately when asserted PI_nCS is detected.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_CFG . PI_WAIT
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_CFG_PI_WAIT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_PI_PI_PI_CFG_PI_WAIT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_PI_PI_PI_CFG_PI_WAIT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Status for PI accesses
 *
 * \details
 * Register: \a DEVCPU_PI:PI:PI_STAT
 */
#define VTSS_DEVCPU_PI_PI_PI_STAT            VTSS_IOREG(VTSS_TO_DEVCPU_PI,0x2)

/** 
 * \brief
 * This field is set when accessing an unknown target or an unknown address
 * inside a known target.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_STAT . ORIGIN_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_STAT_ORIGIN_ERR_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * This field is set if a new access has been started on a busy slow index
 * (each bit in this field correspond to a slow index).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_STAT . SLOW_BUSY_STICKY
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY_STICKY(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY_STICKY     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * This field indicates if a slow access is in progress. When a bit is set
 * in this field, the corresponding slow access index is currently occupied
 * by an access.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_STAT . SLOW_BUSY
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_PI_PI_PI_STAT_SLOW_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * This field indicates if slow-data is pending: When a bit is set in this
 * field, the corresponding slow access index contains unread data. The
 * bits in this field is cleared when the corresponding slow-data index is
 * read.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_STAT . SLOW_DONE
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_STAT_SLOW_DONE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_PI_PI_PI_STAT_SLOW_DONE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_PI_PI_PI_STAT_SLOW_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Mode of the parallel interface
 *
 * \details
 * In order for the configuration to work independently of the current
 * transfer mode; The 8 low bits of this register must be mirrored
 * throughout the entire 32-bit dataword when writing. Also the
 * configuration must be written twice, this ensures that an 8-bit
 * interface correctly receives configuration from a 16-bit external CPU.
 * For example: For default nDone polarity, big-endian mode, auto-address
 * mode, and 16-bit data bus the low 8-bit of this register will be 0x0A.
 * Then the actual 32-bit write value is 0x0A0A0A0A.
 *
 * Register: \a DEVCPU_PI:PI:PI_MODE
 */
#define VTSS_DEVCPU_PI_PI_PI_MODE            VTSS_IOREG(VTSS_TO_DEVCPU_PI,0x3)

/** 
 * \brief
 * This field configures the data-width of the PI interface. Either 8-bit
 * or 16-bit data-bus is supported. By default the width is 8-bit, thus a
 * 16-bit processor has to configure this field to use the entire bus
 * width.
 *
 * \details 
 * 0 : Data bus is 8 bit wide
 * 1 : Data bus is 16 bit wide
 *
 * Field: ::VTSS_DEVCPU_PI_PI_PI_MODE . DATA_BUS_WID
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_MODE_DATA_BUS_WID  VTSS_BIT(3)

/** 
 * \brief
 * Disables automatic tracking of sub-word addresses. By default the low
 * two address bits are not needed, the device keeps track of addresses
 * inside 32-bit words and aligns data accordingly.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_PI_PI_PI_MODE . ADDR_AUTO_DIS
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_MODE_ADDR_AUTO_DIS  VTSS_BIT(2)

/** 
 * \brief
 * Configure the byte order mode on the parallel interface.
 *
 * \details 
 * 0 : Little Endian
 * 1 : Big Endian
 *
 * Field: ::VTSS_DEVCPU_PI_PI_PI_MODE . ENDIAN
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_MODE_ENDIAN   VTSS_BIT(1)

/** 
 * \brief
 * Configures the nDone pin's active level.
 *
 * \details 
 * 0 : nDone pin is active when low
 * 1 : nDone pin is active when high
 *
 * Field: ::VTSS_DEVCPU_PI_PI_PI_MODE . NDONE_POL
 */
#define  VTSS_F_DEVCPU_PI_PI_PI_MODE_NDONE_POL  VTSS_BIT(0)


/** 
 * \brief Slow Data
 *
 * \details
 * Register: \a DEVCPU_PI:PI:PI_SLOW_DATA
 *
 * @param ri Register: PI_SLOW_DATA (??), 0-1
 */
#define VTSS_DEVCPU_PI_PI_PI_SLOW_DATA(ri)   VTSS_IOREG(VTSS_TO_DEVCPU_PI,0x4 + (ri))


#endif /* _VTSS_LUTON26_REGS_DEVCPU_PI_H_ */
