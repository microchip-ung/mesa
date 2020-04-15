/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_FA_REGS_DEVCPU_ORG_H_
#define _VTSS_FA_REGS_DEVCPU_ORG_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a DEVCPU_ORG
 *
 * \see vtss_target_DEVCPU_ORG_e
 *
 * CPU Device Origin
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_ORG:DEVCPU_ORG
 *
 * Origin registers
 */


/** 
 * \brief Physical interface control
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:IF_CTRL
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_IF_CTRL(target)      VTSS_IOREG(target,0x0)

/** 
 * \brief
 * This register configures critical interface parameters, it is
 * constructed so that it can always be written correctly no matter the
 * current state of the interface. When initializing a physical interface,
 * then this is the first register that must be written, the state of the
 * interface at that point may be unknown and therefore the following
 * scheme is required to bring the interface to a known state:When writing
 * a 4-bit value to this field construct a 32-bit data-word as follows: a)
 * copy the 4-bit value into bits 3:0, 11:8, 19:16, and 27:24. b) reverse
 * the 4-bit value and copy into bits 7:4, 15:12, 23:20, and 31:28.
 * Example: To write the value 2 to this field; the 32-bit data-word to
 * write is "0x42424242".Bit 0 configures endianness (when applicable),
 * 0:Little-Endian, 1:Big-Endian.Bit 1 configures bit-order (when
 * applicable), 0:MSB-first, 1:LSB-first.Bit 2,3 are reserved and should be
 * kept 0.For the SI interface the default value of this field is 0x1. For
 * all other interfaces the default value  is 0x0.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_IF_CTRL . IF_CTRL
 */
#define  VTSS_F_DEVCPU_ORG_IF_CTRL_IF_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_ORG_IF_CTRL_IF_CTRL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_ORG_IF_CTRL_IF_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Physical interface configuration and status
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:IF_CFGSTAT
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_IF_CFGSTAT(target)   VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Interface number; software can use this field to determine which
 * interface that is currently used for accessing the device.
 *
 * \details 
 * For a list of interface numbers and corresponding physical interfaces,
 * plase consult the datasheet!
 *
 * Field: ::VTSS_DEVCPU_ORG_IF_CFGSTAT . IF_NUM
 */
#define  VTSS_F_DEVCPU_ORG_IF_CFGSTAT_IF_NUM(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_DEVCPU_ORG_IF_CFGSTAT_IF_NUM     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_DEVCPU_ORG_IF_CFGSTAT_IF_NUM(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * SI interface: This field is set if the SI interface has read data from
 * device before it was ready (this can happen if the SI frequency is too
 * high or when too few padding bytes has been specified).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_IF_CFGSTAT . IF_STAT
 */
#define  VTSS_F_DEVCPU_ORG_IF_CFGSTAT_IF_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_DEVCPU_ORG_IF_CFGSTAT_IF_STAT  VTSS_BIT(16)
#define  VTSS_X_DEVCPU_ORG_IF_CFGSTAT_IF_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * SI interface: This is the number of padding bytes to insert before
 * read-data is shifted out of the device.This is needed when using high
 * serial interface frequencies.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_IF_CFGSTAT . IF_CFG
 */
#define  VTSS_F_DEVCPU_ORG_IF_CFGSTAT_IF_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_ORG_IF_CFGSTAT_IF_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_ORG_IF_CFGSTAT_IF_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Origin configuration
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:ORG_CFG
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_ORG_CFG(target)      VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Set this field to hold back CSR scheduling when this interface want to
 * access a target that is "in use".
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_CFG . BLOCKING_ENA
 */
#define  VTSS_F_DEVCPU_ORG_ORG_CFG_BLOCKING_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_DEVCPU_ORG_ORG_CFG_BLOCKING_ENA  VTSS_BIT(2)
#define  VTSS_X_DEVCPU_ORG_ORG_CFG_BLOCKING_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Set this field to schedule requests from this interface without looking
 * at the state of other interfaces. The default operation is that an
 * interface waits for a target to be free-up before scheduling (new)
 * requests for a particular target.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_CFG . DROP_MODE_ENA
 */
#define  VTSS_F_DEVCPU_ORG_ORG_CFG_DROP_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_DEVCPU_ORG_ORG_CFG_DROP_MODE_ENA  VTSS_BIT(1)
#define  VTSS_X_DEVCPU_ORG_ORG_CFG_DROP_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Clear this field to make write accesses return status. By default write
 * operations return status OK because they are finished before status of
 * the access is known. All non-OK responses will be logged in
 * DEVCPU_ORG::ERR_CNTS no matter the value of this field.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ORG_CFG . FAST_WR
 */
#define  VTSS_F_DEVCPU_ORG_ORG_CFG_FAST_WR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_ORG_ORG_CFG_FAST_WR    VTSS_BIT(0)
#define  VTSS_X_DEVCPU_ORG_ORG_CFG_FAST_WR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Error counters
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:ERR_CNTS
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_ERR_CNTS(target)     VTSS_IOREG(target,0x3)

/** 
 * \brief
 * The "Target Busy" indication is triggered when an interface tries to
 * access a target which is currently reset or if another interface is
 * using the target.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ERR_CNTS . ERR_TGT_BUSY
 */
#define  VTSS_F_DEVCPU_ORG_ERR_CNTS_ERR_TGT_BUSY(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_DEVCPU_ORG_ERR_CNTS_ERR_TGT_BUSY     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_DEVCPU_ORG_ERR_CNTS_ERR_TGT_BUSY(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * The "Watch Dog Drop Origin" indication is triggered when the origin does
 * not receive reply from the CSR ring within a given amount of time. This
 * cannot happen during normal operation.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ERR_CNTS . ERR_WD_DROP_ORG
 */
#define  VTSS_F_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP_ORG(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP_ORG     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP_ORG(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * The "Watch Dog Drop" indication is triggered when a target is too long
 * about processing a request. Usually requests are processed immediately
 * but some accesses requires interaction with the core-logic, when this
 * logic is in reset or during very heavy traffic load there is a chance of
 * timing out in the target.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ERR_CNTS . ERR_WD_DROP
 */
#define  VTSS_F_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_DEVCPU_ORG_ERR_CNTS_ERR_WD_DROP(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * The "No Action" indication is triggered when a target is accessed with a
 * non-existing address. In other words, the target did not contain a
 * register at the requested address.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ERR_CNTS . ERR_NO_ACTION
 */
#define  VTSS_F_DEVCPU_ORG_ERR_CNTS_ERR_NO_ACTION(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_DEVCPU_ORG_ERR_CNTS_ERR_NO_ACTION     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_DEVCPU_ORG_ERR_CNTS_ERR_NO_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * The "Unknown Target Module" indication is triggered when a non-existing
 * target is requested. In other words there was no target with the
 * requested target-id.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_ERR_CNTS . ERR_UTM
 */
#define  VTSS_F_DEVCPU_ORG_ERR_CNTS_ERR_UTM(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_ORG_ERR_CNTS_ERR_UTM     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_ORG_ERR_CNTS_ERR_UTM(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Timeout configuration
 *
 * \details
 * This register is shared between all interfaces on the Origin.
 *
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:TIMEOUT_CFG
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_TIMEOUT_CFG(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * The contents of this field controls the timeout delay for the CSR
 * system. Setting this field to 0 disables timeout. Timeout is handled as
 * follows: A counter that decrements continually, when reaching 0 it will
 * wrap to the value specified by this field. When a target has been
 * processing a request for three "wraps" the target time-out and generate
 * a WD_DROP indication. In the origin an Interface that has been
 * processing a request for four "wraps" will time out and generate a
 * WD_DROP_ORG indication.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_TIMEOUT_CFG . TIMEOUT_CFG
 */
#define  VTSS_F_DEVCPU_ORG_TIMEOUT_CFG_TIMEOUT_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_ORG_TIMEOUT_CFG_TIMEOUT_CFG     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_ORG_TIMEOUT_CFG_TIMEOUT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief General purpose register
 *
 * \details
 * This register is shared between all interfaces on the Origin.
 *
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:GPR
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_GPR(target)          VTSS_IOREG(target,0x5)

/** 
 * \brief
 * General purpose 32-bit registers for debug and software development. The
 * contents of this register can always (safely) be read. However write
 * operations from different masters (to this register), which occur at
 * (exactly) the same time, will fail.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_GPR . GPR
 */
#define  VTSS_F_DEVCPU_ORG_GPR_GPR(x)         (x)
#define  VTSS_M_DEVCPU_ORG_GPR_GPR            0xffffffff
#define  VTSS_X_DEVCPU_ORG_GPR_GPR(x)         (x)


/** 
 * \brief Atomic set of mailbox
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:MAILBOX_SET
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_MAILBOX_SET(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Set bits in this register to atomically set corresponding bits in the
 * DEVCPU_ORG::MAILBOX register. This register return 0 on read.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_MAILBOX_SET . MAILBOX_SET
 */
#define  VTSS_F_DEVCPU_ORG_MAILBOX_SET_MAILBOX_SET(x)  (x)
#define  VTSS_M_DEVCPU_ORG_MAILBOX_SET_MAILBOX_SET     0xffffffff
#define  VTSS_X_DEVCPU_ORG_MAILBOX_SET_MAILBOX_SET(x)  (x)


/** 
 * \brief Atomic clear of mailbox
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:MAILBOX_CLR
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_MAILBOX_CLR(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Set bits in this register to atomically clear corresponding bits in the
 * DEVCPU_ORG::MAILBOX register. This register return 0 on read.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_MAILBOX_CLR . MAILBOX_CLR
 */
#define  VTSS_F_DEVCPU_ORG_MAILBOX_CLR_MAILBOX_CLR(x)  (x)
#define  VTSS_M_DEVCPU_ORG_MAILBOX_CLR_MAILBOX_CLR     0xffffffff
#define  VTSS_X_DEVCPU_ORG_MAILBOX_CLR_MAILBOX_CLR(x)  (x)


/** 
 * \brief Mailbox
 *
 * \details
 * This register is shared between all interfaces on the Origin.
 *
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:MAILBOX
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_MAILBOX(target)      VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Mailbox register which is shared between all interfaces on the Origin.
 * Atomic (safe) modifications to the contents of this register can be
 * performed by using the DEVCPU_ORG::MAILBOX_CLR and
 * DEVCPU_ORG::MAILBOX_SET registers.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_ORG_MAILBOX . MAILBOX
 */
#define  VTSS_F_DEVCPU_ORG_MAILBOX_MAILBOX(x)  (x)
#define  VTSS_M_DEVCPU_ORG_MAILBOX_MAILBOX     0xffffffff
#define  VTSS_X_DEVCPU_ORG_MAILBOX_MAILBOX(x)  (x)


/** 
 * \brief Semaphore configuration
 *
 * \details
 * This register is shared between all interfaces on the Origin.
 *
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:SEMA_CFG
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_SEMA_CFG(target)     VTSS_IOREG(target,0x9)

/** 
 * \brief
 * By default semaphore-interrupt is generated when a semaphore is free. By
 * setting this field interrupt is generated when semaphore is taken, bit 0
 * corresponds to semaphore 0, bit 1 to semaphore 1.
 *
 * \details 
 * 0: Interrupt on taken semaphore
 * 1: Interrupt on free semaphore
 *
 * Field: ::VTSS_DEVCPU_ORG_SEMA_CFG . SEMA_INTR_POL
 */
#define  VTSS_F_DEVCPU_ORG_SEMA_CFG_SEMA_INTR_POL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_DEVCPU_ORG_SEMA_CFG_SEMA_INTR_POL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_DEVCPU_ORG_SEMA_CFG_SEMA_INTR_POL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief Semaphore 0
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:SEMA0
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_SEMA0(target)        VTSS_IOREG(target,0xa)

/** 
 * \brief
 * General Semaphore.The first interface to read this field will be granted
 * the semaphore (reading this field returns 0x1). Once the semaphore has
 * been granted, all reads return '0' from this field (until the semaphore
 * has been released). Any interface can release the semaphore by writing
 * (any value) to this field.
 *
 * \details 
 * 0: Semaphore ownership denied.
 * 1: Semaphore has been granted.
 *
 * Field: ::VTSS_DEVCPU_ORG_SEMA0 . SEMA0
 */
#define  VTSS_F_DEVCPU_ORG_SEMA0_SEMA0(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_ORG_SEMA0_SEMA0        VTSS_BIT(0)
#define  VTSS_X_DEVCPU_ORG_SEMA0_SEMA0(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Semaphore 0 owner
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:SEMA0_OWNER
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_SEMA0_OWNER(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Current owner of the semaphore. This field is a one-hot encoded vector,
 * each bit in this vector correspond to an interface on the origin. If
 * this field return 0, then the semaphore was free at the time of reading
 * the register.
 *
 * \details 
 * For a list of interface numbers and corresponding physical interfaces,
 * plase consult the datasheet!
 *
 * Field: ::VTSS_DEVCPU_ORG_SEMA0_OWNER . SEMA0_OWNER
 */
#define  VTSS_F_DEVCPU_ORG_SEMA0_OWNER_SEMA0_OWNER(x)  (x)
#define  VTSS_M_DEVCPU_ORG_SEMA0_OWNER_SEMA0_OWNER     0xffffffff
#define  VTSS_X_DEVCPU_ORG_SEMA0_OWNER_SEMA0_OWNER(x)  (x)


/** 
 * \brief Semaphore 1
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:SEMA1
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_SEMA1(target)        VTSS_IOREG(target,0xc)

/** 
 * \brief
 * General Semaphore.The first interface to read this field will be granted
 * the semaphore (reading this field returns 0x1). Once the semaphore has
 * been granted, all reads return '0' from this field (until the semaphore
 * has been released). Any interface can release the semaphore by writing
 * (any value) to this field.
 *
 * \details 
 * 0: Semaphore ownership denied.
 * 1: Semaphore has been granted.
 *
 * Field: ::VTSS_DEVCPU_ORG_SEMA1 . SEMA1
 */
#define  VTSS_F_DEVCPU_ORG_SEMA1_SEMA1(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_DEVCPU_ORG_SEMA1_SEMA1        VTSS_BIT(0)
#define  VTSS_X_DEVCPU_ORG_SEMA1_SEMA1(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Semaphore 1 owner
 *
 * \details
 * Register: \a DEVCPU_ORG:DEVCPU_ORG:SEMA1_OWNER
 *
 * @param target A \a ::vtss_target_DEVCPU_ORG_e target
 */
#define VTSS_DEVCPU_ORG_SEMA1_OWNER(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Current owner of the semaphore. This field is a one-hot encoded vector,
 * each bit in this vector correspond to an interface on the origin. If
 * this field return 0, then the semaphore was free at the time of reading
 * the register.
 *
 * \details 
 * For a list of interface numbers and corresponding physical interfaces,
 * plase consult the datasheet!
 *
 * Field: ::VTSS_DEVCPU_ORG_SEMA1_OWNER . SEMA1_OWNER
 */
#define  VTSS_F_DEVCPU_ORG_SEMA1_OWNER_SEMA1_OWNER(x)  (x)
#define  VTSS_M_DEVCPU_ORG_SEMA1_OWNER_SEMA1_OWNER     0xffffffff
#define  VTSS_X_DEVCPU_ORG_SEMA1_OWNER_SEMA1_OWNER(x)  (x)


#endif /* _VTSS_FA_REGS_DEVCPU_ORG_H_ */
