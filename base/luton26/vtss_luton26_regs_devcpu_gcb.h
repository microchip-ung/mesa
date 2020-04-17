// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_DEVCPU_GCB_H_
#define _VTSS_LUTON26_REGS_DEVCPU_GCB_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a DEVCPU_GCB
 *
 * CPU Device General Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a DEVCPU_GCB:CHIP_REGS
 *
 * Not documented
 */


/** 
 * \brief general purpose register
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:GENERAL_PURPOSE
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_GENERAL_PURPOSE  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x0)


/** 
 * \brief SI registers
 *
 * \details
 * Configuration of serial interface data format. This register modifies
 * how the SI receives and transmits data, when configuring this register
 * first write 0 (to get to a known state), then configure the desired
 * values.
 *
 * Register: \a DEVCPU_GCB:CHIP_REGS:SI
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_SI         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1)

/** 
 * \brief
 * Setup SI to use MSB or LSB first. See datasheet for more information.
 *
 * \details 
 * 0: SI expect/transmit MSB first
 * 1: SI expect/transmit LSB first
 *
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_SI . SI_LSB
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_SI_SI_LSB  VTSS_BIT(5)

/** 
 * \brief
 * Setup SI to use either big or little endian data format. See datasheet
 * for more information.
 *
 * \details 
 * 0: SI uses little endian notation
 * 1: SI uses big endian notation
 *
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_SI . SI_ENDIAN
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_SI_SI_ENDIAN  VTSS_BIT(4)

/** 
 * \brief
 * Configure the number of padding bytes that the SI must insert before
 * transmitting read-data during reading from the device.
 *
 * \details 
 * 0 : don't insert any padding
 * 1 : Insert 1 byte of padding
 * ...
 * 15: Insert 15 bytes of padding
 *
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_SI . SI_WAIT_STATES
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_SI_SI_WAIT_STATES(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_SI_SI_WAIT_STATES     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_SI_SI_WAIT_STATES(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief Chip Id
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:CHIP_ID
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x2)

/** 
 * \brief
 * Revision ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . REV_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Part ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . PART_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(x)  VTSS_ENCODE_BITFIELD(x,12,16)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID     VTSS_ENCODE_BITMASK(12,16)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_PART_ID(x)  VTSS_EXTRACT_BITFIELD(x,12,16)

/** 
 * \brief
 * Manufacturer's ID.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . MFG_ID
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID(x)  VTSS_ENCODE_BITFIELD(x,1,11)
#define  VTSS_M_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID     VTSS_ENCODE_BITMASK(1,11)
#define  VTSS_X_DEVCPU_GCB_CHIP_REGS_CHIP_ID_MFG_ID(x)  VTSS_EXTRACT_BITFIELD(x,1,11)

/** 
 * \brief
 * Returns '1'
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_CHIP_ID . ONE
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_CHIP_ID_ONE  VTSS_BIT(0)


/** 
 * \brief Startup state of the chip
 *
 * \details
 * Register: \a DEVCPU_GCB:CHIP_REGS:HW_STAT
 */
#define VTSS_DEVCPU_GCB_CHIP_REGS_HW_STAT    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x3)

/** 
 * \brief
 * This field is set if a hardware fail has been detected in any of the
 * memories during startup-initialization of the chip. This field is valid
 * after release of reset.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_CHIP_REGS_HW_STAT . MEM_FAIL
 */
#define  VTSS_F_DEVCPU_GCB_CHIP_REGS_HW_STAT_MEM_FAIL  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:DBG
 *
 * Not documented
 */

/**
 * Register Group: \a DEVCPU_GCB:SW_REGS
 *
 * Registers for software/software interaction
 */


/** 
 * \brief Semaphore SW interrupt enable
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:SEMA_INTR_ENA
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x5)

/** 
 * \brief
 * This is a bitwise AND of SEMA_FREE and SEMA_INTR_ENA providing an fast
 * access to the cause of an interrupt, given the current mask.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA . SEMA_INTR_IDENT
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_IDENT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_IDENT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_IDENT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Set bits in this register to enable interrupt when the corresponding
 * semaphore is free. In a multi-threaded environment, or with more than
 * one active processor the CPU_SEMA_ENA_SET and CPU_SEMA_ENA_CLR registers
 * can be used for atomic modifications of this register.
 * If interrupt is enabled for a particular semaphore, then software
 * interrupt will be asserted for as long as the semaphore is free (and
 * interrupt is enabled for that semaphore). The lower half of the
 * available semaphores are connected to software Interrupt 0 (SW0), the
 * upper half is connected to software interrupt 1 (SW1).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA . SEMA_INTR_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_ENA     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SEMA_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Clear of semaphore SW interrupt enables
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:SEMA_INTR_ENA_CLR
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_CLR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x6)

/** 
 * \brief
 * Set to clear corresponding interrupt enable in SEMA_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_CLR . SEMA_INTR_ENA_CLR
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_CLR_SEMA_INTR_ENA_CLR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_CLR_SEMA_INTR_ENA_CLR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_CLR_SEMA_INTR_ENA_CLR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Masking of semaphore
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:SEMA_INTR_ENA_SET
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SET  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7)

/** 
 * \brief
 * Set to set corresponding interrupt enable in SEMA_INTR_ENA.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SET . SEMA_INTR_ENA_SET
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SET_SEMA_INTR_ENA_SET(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SET_SEMA_INTR_ENA_SET     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SW_REGS_SEMA_INTR_ENA_SET_SEMA_INTR_ENA_SET(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Semaphore register
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:SEMA
 *
 * @param ri Replicator: x_NUM_SEMA (??), 0-7
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SEMA(ri)     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8 + (ri))

/** 
 * \brief
 * General Semaphore.The process to read this field will read a '1' and
 * thus be granted the semaphore. The semaphore is released by the
 * interface by writing a '1' to this field.
 *
 * \details 
 * Read :
 * '0': Semaphore was not granted.
 * '1': Semaphore was granted.
 * 
 * Write : 
 * '0': No action.
 * '1': Release semaphore.
 *
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA . SEMA
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_SEMA  VTSS_BIT(0)


/** 
 * \brief Semaphore status
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:SEMA_FREE
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SEMA_FREE    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x10)

/** 
 * \brief
 * Show which semaphores that are currently free.
 *
 * \details 
 * '0' : Corresponding semaphore is taken.
 * '1' : Corresponding semaphore is free.
 *
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SEMA_FREE . SEMA_FREE
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SEMA_FREE_SEMA_FREE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_SW_REGS_SEMA_FREE_SEMA_FREE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_SW_REGS_SEMA_FREE_SEMA_FREE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Manually assert software interrupt
 *
 * \details
 * This register provides a simple interface for interrupting on either
 * software interrupt 0 or 1, without implementing semaphore support. Note:
 * setting this field causes a short pulse on the corresponding interrupt
 * connection, this kind of interrupt cannot be used in combination with
 * the SW1_INTR_CONFIG.SW1_INTR_BYPASS feature.
 *
 * Register: \a DEVCPU_GCB:SW_REGS:SW_INTR
 */
#define VTSS_DEVCPU_GCB_SW_REGS_SW_INTR      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x11)

/** 
 * \brief
 * Set this field to inject software interrupt 1. This field is
 * automatically cleared after interrupt has been generated.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SW_INTR . SW1_INTR
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SW_INTR_SW1_INTR  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to assert software interrupt 0. This field is
 * automatically cleared after interrupt has been generated.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SW_REGS_SW_INTR . SW0_INTR
 */
#define  VTSS_F_DEVCPU_GCB_SW_REGS_SW_INTR_SW0_INTR  VTSS_BIT(0)


/** 
 * \brief Mailbox register
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:MAILBOX
 */
#define VTSS_DEVCPU_GCB_SW_REGS_MAILBOX      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x12)


/** 
 * \brief Mailbox register atomic clear
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:MAILBOX_CLR
 */
#define VTSS_DEVCPU_GCB_SW_REGS_MAILBOX_CLR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x13)


/** 
 * \brief Mailbox register atomic set
 *
 * \details
 * Register: \a DEVCPU_GCB:SW_REGS:MAILBOX_SET
 */
#define VTSS_DEVCPU_GCB_SW_REGS_MAILBOX_SET  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x14)

/**
 * Register Group: \a DEVCPU_GCB:VCORE_ACCESS
 *
 * Not documented
 */


/** 
 * \brief Control register for VCore accesses
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_CTRL
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x15)

/** 
 * \brief
 * This field is set to the value of VA_CTRL:VA_ERR whenever one of the
 * data registers ACC_DATA, ACC_DATA_INCR, or ACC_DATA_RO is read. By
 * reading this field it is possible to determine if the last read-value
 * from one of these registers was erred.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_ERR_RD
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_ERR_RD  VTSS_BIT(3)

/** 
 * \brief
 * This field is set if the access inside the VCore domain was terminated
 * by an error. This situation can occur when accessing an unmapped part of
 * the VCore memory-map or when accessing a target that reports error (e.g.
 * accessing uninitialized DDR2 memory).
 * If an error occurs during reading, the read-data will be 0x80000000. So
 * as an optimization, software only has to check for error if 0x80000000
 * is returned (and in that case VA_ERR_RD should be checked). When writing
 * you should always check if sucessful.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_ERR
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_ERR  VTSS_BIT(2)

/** 
 * \brief
 * This field is set to the value of VA_CTRL:VA_BUSY whenever one of the
 * data registers ACC_DATA, ACC_DATA_INCR, or ACC_DATA_RO is read. By
 * reading this field it is possible to determine if the last read-value
 * from one of these registers was valid.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_BUSY_RD
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY_RD  VTSS_BIT(1)

/** 
 * \brief
 * This field is set by hardware when an access into VCore domain is
 * started, and cleared when the access is done.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL . VA_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_VCORE_ACCESS_VA_CTRL_VA_BUSY  VTSS_BIT(0)


/** 
 * \brief Address register for VCore accesses
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_ADDR
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_ADDR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x16)


/** 
 * \brief Data register for VCore accesses
 *
 * \details
 * The VA_DATA, VA_DATA_INCR, and VA_DATA_INERT registers are used for
 * indirect access into the VCore domain. The functionality of the
 * VA_DATA_INCR and VA_DATA_INERT registers are similar to this register -
 * but with minor exceptions. These exceptions are fleshed out in the
 * description of the respective registers.
 *
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x17)


/** 
 * \brief Data register for VCore accesses (w. auto increment of address)
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA_INCR
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA_INCR  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x18)


/** 
 * \brief Data register for VCore accesses (will not initiate access)
 *
 * \details
 * Register: \a DEVCPU_GCB:VCORE_ACCESS:VA_DATA_INERT
 */
#define VTSS_DEVCPU_GCB_VCORE_ACCESS_VA_DATA_INERT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x19)

/**
 * Register Group: \a DEVCPU_GCB:GPIO
 *
 * Not documented
 */


/** 
 * \brief GPIO output set
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT_SET
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_SET    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1a)


/** 
 * \brief GPIO output clear
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT_CLR
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT_CLR    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1b)


/** 
 * \brief GPIO output
 *
 * \details
 * In a multi-threaded software environment using the registers
 * GPIO_OUT_SET and GPIO_OUT_CLR for modifying GPIO values removes the need
 * for software-locked access.
 *
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OUT
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OUT        VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1c)


/** 
 * \brief GPIO input
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_IN
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_IN         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1d)


/** 
 * \brief GPIO pin direction
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_OE
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_OE         VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1e)


/** 
 * \brief GPIO interrupt
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR       VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x1f)


/** 
 * \brief GPIO interrupt enable
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR_ENA
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_ENA   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x20)


/** 
 * \brief GPIO interrupt identity
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_INTR_IDENT
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_INTR_IDENT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x21)


/** 
 * \brief GPIO alternate functions
 *
 * \details
 * Register: \a DEVCPU_GCB:GPIO:GPIO_ALT
 *
 * @param ri Register: GPIO_ALT (??), 0-1
 */
#define VTSS_DEVCPU_GCB_GPIO_GPIO_ALT(ri)    VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x22 + (ri))

/**
 * Register Group: \a DEVCPU_GCB:DEVCPU_RST_REGS
 *
 * Not documented
 */


/** 
 * \brief Reset part or the whole chip
 *
 * \details
 * Register: \a DEVCPU_GCB:DEVCPU_RST_REGS:SOFT_CHIP_RST
 */
#define VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x24)

/** 
 * \brief
 * Clear this field to release reset in the Cu-PHY. This field is
 * automatically set during hard-reset and soft-reset of the chip. After
 * reset is released the PHY will indicate when it is ready to be accessed
 * via DEVCPU_GCB::MISC_STAT.PHY_READY.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST . SOFT_PHY_RST
 */
#define  VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST_SOFT_PHY_RST  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to reset the whole chip. This field is automatically
 * cleared by the reset.
 * Note: It is possible for the VCore to protect itself from soft-reset of
 * the chip, for more info see RESET.CORE_RST_PROTECT inside the VCore
 * register space.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST . SOFT_CHIP_RST
 */
#define  VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_CHIP_RST_SOFT_CHIP_RST  VTSS_BIT(0)


/** 
 * \brief Soft reset of devcpu.
 *
 * \details
 * Register: \a DEVCPU_GCB:DEVCPU_RST_REGS:SOFT_DEVCPU_RST
 */
#define VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_DEVCPU_RST  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x25)

/** 
 * \brief
 * Set this field to reset the extraction logic. The reset remains asserted
 * until this field is cleared.
 * Note: Extraction logic is also reset while
 * SOFT_CHIP_RST.SOFT_NON_CFG_RST is set.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_DEVCPU_RST . SOFT_XTR_RST
 */
#define  VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_DEVCPU_RST_SOFT_XTR_RST  VTSS_BIT(1)

/** 
 * \brief
 * Set this field to reset the injection logic. The reset remains asserted
 * until this field is cleared.
 * Note: Injection logic is also reset while SOFT_CHIP_RST.SOFT_NON_CFG_RST
 * is set.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_DEVCPU_RST . SOFT_INJ_RST
 */
#define  VTSS_F_DEVCPU_GCB_DEVCPU_RST_REGS_SOFT_DEVCPU_RST_SOFT_INJ_RST  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:ALIGN
 *
 * Not documented
 */

/**
 * Register Group: \a DEVCPU_GCB:MIIM
 *
 * Not documented
 */


/** 
 * \brief MIIM Status
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_STATUS
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_STATUS(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,0)

/** 
 * \brief
 * Indicates the current state of the MIIM controller. When read operations
 * are done (no longer busy), then read data is available via the
 * DEVCPU_GCB::MII_DATA register.
 *
 * \details 
 * 0: MIIM controller is in idle state
 * 1: MIIM controller is busy performing MIIM cmd (Either read or read
 * cmd).
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_BUSY  VTSS_BIT(3)

/** 
 * \brief
 * The MIIM controller has a CMD fifo of depth one. When this field is 0,
 * then it is safe to write another MIIM command to the MIIM controller.
 *
 * \details 
 * 0 : Read or write not pending
 * 1 : Read or write pending.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_OPR_PEND
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_OPR_PEND  VTSS_BIT(2)

/** 
 * \brief
 * Indicates whether a read operation via the MIIM interface is in progress
 * or not.
 *
 * \details 
 * 0 : Read not in progress
 * 1 : Read in progress.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_PENDING_RD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_RD  VTSS_BIT(1)

/** 
 * \brief
 * Indicates whether a write operation via the MIIM interface is in
 * progress or not.
 *
 * \details 
 * 0 : Write not in progress
 * 1 : Write in progress.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_STAT_PENDING_WR
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_STAT_PENDING_WR  VTSS_BIT(0)

/** 
 * \brief
 * Signals if all PHYs have been scanned ( with auto scan ) at least once.
 *
 * \details 
 * 0 : Auto scan has not scanned all PHYs.
 * 1 : Auto scan has scanned all PHY at least once.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_STATUS . MIIM_SCAN_COMPLETE
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_STATUS_MIIM_SCAN_COMPLETE  VTSS_BIT(4)


/** 
 * \brief MIIM Command
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CMD
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_CMD(gi)     VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,2)

/** 
 * \brief
 * Must be set for starting a new PHY access. This bit is automatically
 * cleared.
 *
 * \details 
 * 0 : Write to this register is ignored.
 * 1 : Write to this register is processed.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_VLD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_VLD  VTSS_BIT(31)

/** 
 * \brief
 * Indicates the addressed PHY number.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_PHYAD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_PHYAD(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/** 
 * \brief
 * Indicates the addressed of the register within the PHY that shall be
 * accessed.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_REGAD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_REGAD(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/** 
 * \brief
 * Data to be written in the PHY register.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_WRDATA
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_ENCODE_BITFIELD(x,4,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA     VTSS_ENCODE_BITMASK(4,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_WRDATA(x)  VTSS_EXTRACT_BITFIELD(x,4,16)

/** 
 * \brief
 * Select if scanning of the PHY shall be done once, or scanning should be
 * done continuously.
 *
 * \details 
 * 0 : Do continuously PHY scanning 
 * 1 : Stop once all PHY have been scanned.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_SINGLE_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_SINGLE_SCAN  VTSS_BIT(3)

/** 
 * \brief
 * Indicates type of operation.
 *
 * \details 
 * Clause 22:
 * 
 * 01 : Write
 * 10 : Read
 * 
 * Clause 45:
 * 
 * 00 : Address
 * 01 : Write
 * 10 : Read inc.
 * 11 : Read.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_OPR_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_OPR_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Indicates whether automatic scanning of PHY registers is enabled. When
 * enabled, the PHY-number for each automatic read is continuously
 * round-robined from PHY_ADDR_LOW through PHY_ADDR_HIGH. This function is
 * started upon a read operation (ACCESS_TYPE).
 * Scan MUST be disabled when doing any configuration of the MIIM
 * controller.
 *
 * \details 
 * 0 : Disabled
 * 1 : Enabled.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CMD . MIIM_CMD_SCAN
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CMD_MIIM_CMD_SCAN  VTSS_BIT(0)


/** 
 * \brief MIIM Reply Data
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_DATA
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_DATA(gi)    VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,3)

/** 
 * \brief
 * Indicates whether a read operation failed or succeeded.
 *
 * \details 
 * 00 : OK
 * 11 : Error
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_DATA . MIIM_DATA_SUCCESS
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_SUCCESS(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Data read from PHY register.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_DATA . MIIM_DATA_RDDATA
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_DATA_MIIM_DATA_RDDATA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MIIM Configuration
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_CFG
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,4)

/** 
 * \brief
 * Configures the MIIM clock frequency. This is computed as
 * system_clk/(2*(1+X)), where X is the value written to this register.
 * Note : Setting X to 0 is invalid and will result in the same frequency
 * as setting X to 1.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CFG . MIIM_CFG_PRESCALE
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CFG_MIIM_CFG_PRESCALE(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * The ST (start-of-frame) field of the MIIM frame format adopts the value
 * of this field. This must be configured for either clause 22 or 45 MIIM
 * operation.
 *
 * \details 
 * "01": Clause 22
 * "00": Clause 45
 * Other values are reserved.
 *
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_CFG . MIIM_ST_CFG_FIELD
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_CFG_MIIM_ST_CFG_FIELD(x)  VTSS_EXTRACT_BITFIELD(x,9,2)


/** 
 * \brief MIIM Scan 0
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_0
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,5)

/** 
 * \brief
 * Indicates the high PHY number to scan during automatic scanning.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0 . MIIM_SCAN_PHYADHI
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADHI(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Indicates the low PHY number to scan during automatic scanning.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_0 . MIIM_SCAN_PHYADLO
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_0_MIIM_SCAN_PHYADLO(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief MIIM Scan 1
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_1
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,6)

/** 
 * \brief
 * Indicates the mask for comparing the PHY registers during automatic
 * scan.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1 . MIIM_SCAN_MASK
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Indicates the expected value for comparing the PHY registers during
 * automatic scan.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MIIM_MII_SCAN_1 . MIIM_SCAN_EXPECT
 */
#define  VTSS_F_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MIIM_MII_SCAN_1_MIIM_SCAN_EXPECT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_LAST_RSLTS(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,7)


/** 
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM:MII_SCAN_LAST_RSLTS_VLD
 *
 * @param gi Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_MII_SCAN_LAST_RSLTS_VLD(gi)  VTSS_IOREG_IX(VTSS_TO_DEVCPU_GCB,0x28,gi,9,0,8)

/**
 * Register Group: \a DEVCPU_GCB:MIIM_READ_SCAN
 *
 * Not documented
 */


/** 
 * \brief MIIM Results
 *
 * \details
 * Register: \a DEVCPU_GCB:MIIM_READ_SCAN:MII_SCAN_RSLTS_STICKY
 *
 * @param ri Replicator: x_NUM_OF_MIIM_INTERFACES (??), 0-1
 */
#define VTSS_DEVCPU_GCB_MIIM_READ_SCAN_MII_SCAN_RSLTS_STICKY(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x3a + (ri))

/**
 * Register Group: \a DEVCPU_GCB:FEATURES
 *
 * Feature control/status
 */


/** 
 * \brief Encoded features
 *
 * \details
 * Register: \a DEVCPU_GCB:FEATURES:FEA_STAT
 *
 * @param ri Register: FEA_STAT (??), 0-7
 */
#define VTSS_DEVCPU_GCB_FEATURES_FEA_STAT(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x3c + (ri))

/**
 * Register Group: \a DEVCPU_GCB:RAM_STAT
 *
 * Not documented
 */


/** 
 * \brief QS RAM status
 *
 * \details
 * Register: \a DEVCPU_GCB:RAM_STAT:RAM_INTEGRITY_ERR_STICKY
 */
#define VTSS_DEVCPU_GCB_RAM_STAT_RAM_INTEGRITY_ERR_STICKY  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x45)

/** 
 * \brief
 * Integrity error for QS_XTR RAM
 *
 * \details 
 * '0': No RAM integrity check error occurred
 * '1': A RAM integrity check error occurred
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEVCPU_GCB_RAM_STAT_RAM_INTEGRITY_ERR_STICKY . QS_XTR_RAM_INTGR_ERR_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_RAM_STAT_RAM_INTEGRITY_ERR_STICKY_QS_XTR_RAM_INTGR_ERR_STICKY  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:MISC
 *
 * Miscellaneous Registers
 */


/** 
 * \brief Miscellaneous Configuration Register
 *
 * \details
 * Register to control various muxing in the IO-ring.
 *
 * Register: \a DEVCPU_GCB:MISC:MISC_CFG
 */
#define VTSS_DEVCPU_GCB_MISC_MISC_CFG        VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x46)

/** 
 * \brief
 * Select if PHY or SwC should control the SyncE pins.
 *
 * \details 
 * 0: SwC owns SyncE pins
 * 1: PHY owns SyncE pins 
 *
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . SYNCE_SRC_CTRL
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_SYNCE_SRC_CTRL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_DEVCPU_GCB_MISC_MISC_CFG_SYNCE_SRC_CTRL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_DEVCPU_GCB_MISC_MISC_CFG_SYNCE_SRC_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Set the sw_mode for HSIO.
 *
 * \details 
 * 00 - mode 0 - 3*QSGMII, 1*2G5, 1*SGMII
 * 01 - mode 1 - 2*2G5, 10*SGMII
 * 10 - mode 2 - 2*QSGMII, 8*SGMII
 *
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . SW_MODE
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_DEVCPU_GCB_MISC_MISC_CFG_SW_MODE(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \brief
 * Flip or swap lanes in QSGMII#1.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_FLIP_LANE1
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_FLIP_LANE1  VTSS_BIT(5)

/** 
 * \brief
 * Flip or swap lanes in QSGMII#2.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_FLIP_LANE2
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_FLIP_LANE2  VTSS_BIT(4)

/** 
 * \brief
 * Flip or swap lanes in QSGMII#3.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_FLIP_LANE3
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_FLIP_LANE3  VTSS_BIT(3)

/** 
 * \brief
 * Disable hysteresis of synchronization state machine.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_SHYST_DIS
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_SHYST_DIS  VTSS_BIT(2)

/** 
 * \brief
 * Enable 8b10b error propagation (8b10b error code-groups are replaced by
 * K70.7 error symbols.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_E_DET_ENA
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_E_DET_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Use I1 during idle sequencing only.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_CFG . QSGMII_USE_I1_ENA
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_CFG_QSGMII_USE_I1_ENA  VTSS_BIT(0)


/** 
 * \details
 * Register: \a DEVCPU_GCB:MISC:MISC_STAT
 */
#define VTSS_DEVCPU_GCB_MISC_MISC_STAT       VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x47)

/** 
 * \brief
 * This field is set high when the PHY is ready for access after release of
 * PHY reset via DEVCPU_GCB::SOFT_CHIP_RST.SOFT_PHY_RST.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_MISC_STAT . PHY_READY
 */
#define  VTSS_F_DEVCPU_GCB_MISC_MISC_STAT_PHY_READY  VTSS_BIT(3)


/** 
 * \details
 * Register: \a DEVCPU_GCB:MISC:PHY_SPEED_1000_STAT
 */
#define VTSS_DEVCPU_GCB_MISC_PHY_SPEED_1000_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x48)

/** 
 * \brief
 * p2m_speed1000c status from PHY
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_PHY_SPEED_1000_STAT . SPEED_1000
 */
#define  VTSS_F_DEVCPU_GCB_MISC_PHY_SPEED_1000_STAT_SPEED_1000(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_MISC_PHY_SPEED_1000_STAT_SPEED_1000     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_MISC_PHY_SPEED_1000_STAT_SPEED_1000(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \details
 * Register: \a DEVCPU_GCB:MISC:PHY_SPEED_100_STAT
 */
#define VTSS_DEVCPU_GCB_MISC_PHY_SPEED_100_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x49)

/** 
 * \brief
 * p2m_speed100 status from PHY
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_PHY_SPEED_100_STAT . SPEED_100
 */
#define  VTSS_F_DEVCPU_GCB_MISC_PHY_SPEED_100_STAT_SPEED_100(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_MISC_PHY_SPEED_100_STAT_SPEED_100     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_MISC_PHY_SPEED_100_STAT_SPEED_100(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \details
 * Register: \a DEVCPU_GCB:MISC:PHY_SPEED_10_STAT
 */
#define VTSS_DEVCPU_GCB_MISC_PHY_SPEED_10_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x4a)

/** 
 * \brief
 * p2m_speed10 status from PHY
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_PHY_SPEED_10_STAT . SPEED_10
 */
#define  VTSS_F_DEVCPU_GCB_MISC_PHY_SPEED_10_STAT_SPEED_10(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_MISC_PHY_SPEED_10_STAT_SPEED_10     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_MISC_PHY_SPEED_10_STAT_SPEED_10(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \details
 * Register: \a DEVCPU_GCB:MISC:DUPLEXC_PORT_STAT
 */
#define VTSS_DEVCPU_GCB_MISC_DUPLEXC_PORT_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x4b)

/** 
 * \brief
 * p2m_duplexc_port status from PHY
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MISC_DUPLEXC_PORT_STAT . DUPLEXC
 */
#define  VTSS_F_DEVCPU_GCB_MISC_DUPLEXC_PORT_STAT_DUPLEXC(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_MISC_DUPLEXC_PORT_STAT_DUPLEXC     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_MISC_DUPLEXC_PORT_STAT_DUPLEXC(x)  VTSS_EXTRACT_BITFIELD(x,0,12)

/**
 * Register Group: \a DEVCPU_GCB:SIO_CTRL
 *
 * Serial IO control configuration
 */


/** 
 * \brief Input data registers
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INPUT_DATA
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INPUT_DATA(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x4c + (ri))


/** 
 * \brief Interrupt polarity for each GPIO
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INT_POL
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_POL(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x50 + (ri))


/** 
 * \brief Interrupt enable register for each port.
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_INT_ENA
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_INT_ENA  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x54)


/** 
 * \brief Configuration of output data values
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_CONFIG
 *
 * @param ri Replicator: x_SIO_PORT_CNT (??), 0-31
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x55 + (ri))

/** 
 * \brief
 * Output source select for the four outputs from each port.
 * The source select is encoded using three bits for each output bit.
 *
 * \details 
 * The placement of the source select bits for each output bit in the
 * register:
 * Output bit 0: (2 down to 0)
 * Output bit 1: (5 down to 3)
 * Output bit 2: (8 down to 6)
 * Output bit 3: (11 down to 9)
 * Source select encoding for each output bit:
 * 0 : Forced '0'
 * 1 : Forced '1'
 * 2 : Blink mode 0
 * 3 : Blink mode 1
 * 4 : Link activity blink mode 0
 * 5 : Link activity blink mode 1
 * 6 : Link activity blink mode 0 inversed polarity
 * 7 : Link activity blink mode 1 inversed polarity
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG . BIT_SOURCE
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_PORT_CONFIG_BIT_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Port enable register
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_PORT_ENABLE
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_PORT_ENABLE  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x75)


/** 
 * \brief General configuration register
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CONFIG
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x76)

/** 
 * \brief
 * Configuration for blink mode 1.
 * Supports three different blink modes and a "burst toggle" mode in which
 * blink mode 1 will alternate for each burst.
 *
 * \details 
 * 0 : Blink freq appr. 20Hz.
 * 1 : Blink freq appr. 10Hz.
 * 2 : Blink freq  appr. 5Hz.
 * 3 : Burst toggle.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BMODE_1
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_1(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Configuration of blink mode 0. Supports four different blink modes.
 *
 * \details 
 * 0 : Blink freq appr. 20Hz.
 * 1 : Blink freq appr. 10Hz.
 * 2 : Blink freq  appr. 5Hz.
 * 3 : Blink freq  appr. 2.5Hz.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BMODE_0
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BMODE_0(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Reset the blink counters. Used to synchronize the blink modes between
 * different chips.
 *
 * \details 
 * 0 : Blink counter is running.
 * 1 : Blink counter is reset until sio_blink_reset is unset again.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BLINK_RESET
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BLINK_RESET  VTSS_BIT(17)

/** 
 * \brief
 * Bit interrupt enable. Enables interrupts for the four gpios in a port.
 * Is applied to all ports.
 *
 * \details 
 * 0: Interrupt is disabled for bit n for all ports.
 * 1: Interrupt is enabled for bit n for all ports.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_INT_ENA
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(x)  VTSS_ENCODE_BITFIELD(x,13,4)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA     VTSS_ENCODE_BITMASK(13,4)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_INT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,4)

/** 
 * \brief
 * Set to disable burst gap.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BURST_GAP_DIS
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP_DIS  VTSS_BIT(12)

/** 
 * \brief
 * Configures the length of burst gap in steps of approx. 1 ms. Burst gap
 * can be disabled by setting SIO_CONFIG.SIO_BURST_GAP_DIS.
 *
 * \details 
 * 0: 1.05 ms burst gap.
 * 1: 2.10 ms burst gap.
 * 31: 33.55 ms burst gap.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_BURST_GAP
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP(x)  VTSS_ENCODE_BITFIELD(x,7,5)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP     VTSS_ENCODE_BITMASK(7,5)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_BURST_GAP(x)  VTSS_EXTRACT_BITFIELD(x,7,5)

/** 
 * \brief
 * Use this to output a single burst. Will be cleared by hardware when the
 * burst has finished.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_SINGLE_SHOT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_SINGLE_SHOT  VTSS_BIT(6)

/** 
 * \brief
 * Use this to output repeated bursts interleaved with burst gaps. Must be
 * manually reset again to stop output of bursts.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_AUTO_REPEAT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_AUTO_REPEAT  VTSS_BIT(5)

/** 
 * \brief
 * Polarity of the "Ld" signal
 *
 * \details 
 * 0: load signal is active low
 * 1: load signal is active high
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_LD_POLARITY
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_LD_POLARITY  VTSS_BIT(4)

/** 
 * \brief
 * Number of gpios pr. port.
 *
 * \details 
 * 0: 1 gpio pr. port.
 * 1: 2 gpios pr. port.
 * 2: 3 gpios pr. port.
 * 3: 4 gpios pr. port.  
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_PORT_WIDTH
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_PORT_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Reverse the output bitstream.
 * 
 * The default order of the output bit stream is (displayed in transmitted
 * order):
 * (portN bit3, portN bit2, ...., port0 bit1, port0 bit0)
 * 
 * The reverse order of the output bit stream is (displayed in transmitted
 * order):
 * (port0 bit0, port0 bit1, ...., portN bit2, portN bit3)
 *
 * \details 
 * 0 : Do not reverse.
 * 1 : Reverse.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_REVERSE_OUTPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_REVERSE_OUTPUT  VTSS_BIT(1)

/** 
 * \brief
 * Reverse the input bitstream.
 * The default order of the input bit stream is (displayed in received
 * order):
 * (port0 bit0, port0 bit1, ...., portN bit2, portN bit3)
 * The reverse order of the input bit stream is (displayed in received
 * order):
 * (portN bit3, portN bit2, ...., port0 bit1, port0 bit0)
 *
 * \details 
 * 0: Do not reverse.
 * 1: Reverse.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG . SIO_REVERSE_INPUT
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CONFIG_SIO_REVERSE_INPUT  VTSS_BIT(0)


/** 
 * \brief Configuration of the serial IO clock frequency
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_CLOCK
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK   VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x77)

/** 
 * \brief
 * SIO controller clock frequency. Divides the 250MHz system clk with value
 * of this field. E.g. the system clk is 250 MHz and this field is set to
 * 10, the output frequency will be 25 MHz.
 *
 * \details 
 * 0 : Disable clock.
 * 1 : Reserved, do not use.
 * Others : Clock divider value.
 *
 * Field: ::VTSS_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK . SIO_CLK_FREQ
 */
#define  VTSS_F_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_DEVCPU_GCB_SIO_CTRL_SIO_CLOCK_SIO_CLK_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Interrupt register
 *
 * \details
 * Register: \a DEVCPU_GCB:SIO_CTRL:SIO_INT_REG
 *
 * @param ri Replicator: x_SIO_IOS_PR_PORT (??), 0-3
 */
#define VTSS_DEVCPU_GCB_SIO_CTRL_SIO_INT_REG(ri)  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x78 + (ri))

/**
 * Register Group: \a DEVCPU_GCB:FAN_CFG
 *
 * Configuration register for the fan controller
 */


/** 
 * \brief Configuration register for the fan controller
 *
 * \details
 * Register: \a DEVCPU_GCB:FAN_CFG:FAN_CFG
 */
#define VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG      VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7c)

/** 
 * \brief
 * Set the frquency of the PWM output 
 *
 * \details 
 * 
 * 0: 25 kHz
 * 1: 120 Hz
 * 2: 100 Hz
 * 3: 80 Hz
 * 4: 60 Hz
 * 5: 40 Hz
 * 6: 20 Hz
 * 7: 10 Hz
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . PWM_FREQ
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * Define the polarity of the PWM output.
 *
 * \details 
 * 0: PWM is logic 1 when "on"
 * 1: PWM is logic 0 when "on"
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . INV_POL
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_INV_POL  VTSS_BIT(2)

/** 
 * \brief
 * Enable gating of the TACH input by the PWM output so that only TACH
 * pulses received when PWM is "on" are counted.
 *
 * \details 
 * 0: Disabled
 * 1: Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . GATE_ENA
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_GATE_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Configure the PWM output to be open collector
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . PWM_OPEN_COL_ENA
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_PWM_OPEN_COL_ENA  VTSS_BIT(0)

/** 
 * \brief
 * Define the duty cycle
 *
 * \details 
 * 0x00: Always "off"
 * 0xFF: Always "on"
 *
 * Field: ::VTSS_DEVCPU_GCB_FAN_CFG_FAN_CFG . DUTY_CYCLE
 */
#define  VTSS_F_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_DEVCPU_GCB_FAN_CFG_FAN_CFG_DUTY_CYCLE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * Register Group: \a DEVCPU_GCB:FAN_STAT
 *
 * Fan controller statistics
 */


/** 
 * \brief TACH counter
 *
 * \details
 * Register: \a DEVCPU_GCB:FAN_STAT:FAN_CNT
 */
#define VTSS_DEVCPU_GCB_FAN_STAT_FAN_CNT     VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7d)

/** 
 * \brief
 * Counts the number of rising edges on the TACH input. The counter is
 * wrapping.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_FAN_STAT_FAN_CNT . FAN_CNT
 */
#define  VTSS_F_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_FAN_STAT_FAN_CNT_FAN_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a DEVCPU_GCB:PTP_CFG
 *
 * Configuration registers for PTP
 */


/** 
 * \brief Misc Configuration Register for PTP
 *
 * \details
 * Misc Configuration Register for PTP
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_MISC_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7e)

/** 
 * \brief
 * GPIO selection of external sync output.
 *
 * \details 
 * '0': External sync output is mapped to GPIO_TIME_TICK_0
 * '1': External sync output is mapped to GPIO_TIME_TICK_1 - (same as
 * generated clk GPIO)
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_SEL
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL  VTSS_BIT(7)

/** 
 * \brief
 * Inversion of external sync output.
 *
 * \details 
 * '0': External sync output is not inverted
 * '1': External sync output is inverted
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_INV
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_INV  VTSS_BIT(6)

/** 
 * \brief
 * External sync output enable.
 *
 * \details 
 * 0': External sync output is disabled
 * '1': External sync output is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_OUTP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA  VTSS_BIT(5)

/** 
 * \brief
 * Select of external sync input GPIO.
 *
 * \details 
 * '0': External sync input is GPIO_TIME_TICK_0
 * '1': External sync input is GPIO_TIME_TICK_1
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_INP_SEL
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL  VTSS_BIT(4)

/** 
 * \brief
 * Inversion of external sync input.
 *
 * \details 
 * '0': External sync input is not inverted
 * '1': External sync input is inverted
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_INP_INV
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_INV  VTSS_BIT(3)

/** 
 * \brief
 * External sync input enable.
 *
 * \details 
 * '0': External sync input is disabled
 * '1': External sync input is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_INP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA  VTSS_BIT(2)

/** 
 * \brief
 * Enable synchronization to external sync.
 *
 * \details 
 * '0': Sync on external signal is disabled
 * '1': Sync on external signal is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . EXT_SYNC_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable master counter.
 *
 * \details 
 * 0: Master counter disabled.
 * 1: Master counter enabled.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG . PTP_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_PTP_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration register for master counter upper limit
 *
 * \details
 * Configuration register for master counter upper limit
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_UPPER_LIMIT_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x7f)

/** 
 * \brief
 * Counter value where the Master counter should be reset
 *
 * \details 
 * Units is time in clock_ticks.
 * 1 clock tick is 4 ns, if system_clk is set to 250MHz.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG . PTP_UPPER_LIMIT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG_PTP_UPPER_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Configuration register for master counter upper limit one time adjustment
 *
 * \details
 * Configuration register for master counter upper limit one time
 * adjustment
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_UPPER_LIMIT_1_TIME_ADJ_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x80)

/** 
 * \brief
 * One time enable for PTP_UPPER_LIMIT_1_TIME_ADJ
 *
 * \details 
 * 0: Normal operation
 * 1: Timer is adjusted by usage of PTP_UPPER_LIMIT_1_TIME_ADJ
 * Bit is cleared by HW
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG . PTP_UPPER_LIMIT_1_TIME_ADJ_SHOT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_SHOT  VTSS_BIT(31)

/** 
 * \brief
 * Counter value where the Master counter should be reset
 *
 * \details 
 * Units is time in clock_ticks.
 * 1 clock tick is 4 ns
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG . PTP_UPPER_LIMIT_1_TIME_ADJ
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Sync Interrupt enable register
 *
 * \details
 * Sync Interrupt enable register
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:PTP_SYNC_INTR_ENA_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x81)

/** 
 * \brief
 * Interrupt mask. Masks interrupt generation when a synchronization pulse
 * is received on external sync input pin.
 *
 * \details 
 * '0': Interrupt is not generated
 * '1': Interrupt is generated
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG . EXT_SYNC_CURRENT_TIME_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_EXT_SYNC_CURRENT_TIME_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Interrupt mask. Masks interrupt generation when Master Timer generates a
 * synchronization pulse.
 *
 * \details 
 * '0': Interrupt is not generated
 * '1': Interrupt is generated
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG . SYNC_STAT_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG_SYNC_STAT_ENA  VTSS_BIT(0)


/** 
 * \brief Generated external clock high period configuration register
 *
 * \details
 * Generated external clock high period configuration register
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_HIGH_PERIOD_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x82)

/** 
 * \brief
 * High period for generated external clock in system clock cycles.
 *
 * \details 
 * N: External clock signal is high for (N+1)*system_clk cycles.
 * E.g. N=999, system clock = 250 MHz which means 4 ns clk period.
 * High Phase is 4 us.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG . GEN_EXT_CLK_HIGH_PERIOD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Generated external clock low period configuration register
 *
 * \details
 * Generated external clock low period configuration register
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_LOW_PERIOD_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x83)

/** 
 * \brief
 * Low period for generated external clock in system clock cycles.
 *
 * \details 
 * N: External clock signal is low for (N+1)*system_clk cycles.
 * E.g. N=999, system clock = 250 MHz which means 4 ns clk period.
 * Low Phase is 4 us.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG . GEN_EXT_CLK_LOW_PERIOD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Configuration register for sync. of external clock to internal master sync.
 *
 * \details
 * Configuration register for synchronization of external clock to internal
 * master sync.
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:GEN_EXT_CLK_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x84)

/** 
 * \brief
 * Enable sync of generated external clock to PTP sync master.
 *
 * \details 
 * 0: Synchronization is disabled
 * 1: Synchronization is enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_SYNC_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA  VTSS_BIT(2)

/** 
 * \brief
 * External clock frequency adjustment enable.
 *
 * \details 
 * 0: Adjustment Disabled
 * 1: Adjustment Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_ADJ_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ADJ_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable generated external clock.
 *
 * \details 
 * 0: Generated external clock disabled.
 * 1: Generated external clock enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG . GEN_EXT_CLK_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA  VTSS_BIT(0)


/** 
 * \brief Configuration register for generated clock frequency adjustment
 *
 * \details
 * Configuration register for generated clock frequency adjustment
 *
 * Register: \a DEVCPU_GCB:PTP_CFG:CLK_ADJ_CFG
 */
#define VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x85)

/** 
 * \brief
 * Clock frequency adjustment direction.
 *
 * \details 
 * 0: Positive adjustment. Every N cycles a 1 is added to the counter. =>
 * clock period is decrease, clock frequency is increased.
 * 1: Negative adjustment. Every N cycles a 1 is subtracted from the
 * counter. => clock period is increase, clock frequency is decreased.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_DIR
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_DIR  VTSS_BIT(31)

/** 
 * \brief
 * Clock frequency adjust enable.
 *
 * \details 
 * 0: Adjustment Disabled
 * 1: Adjustment Enabled
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_ENA  VTSS_BIT(30)

/** 
 * \brief
 * Defines when the updated adjustment value and direction takes effect.
 *
 * \details 
 * 0: updated values take immediate effect.
 * 1: updated values take effect after the next sync pulse.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ_UPD
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_UPD  VTSS_BIT(29)

/** 
 * \brief
 * Clock frequency adjust.
 *
 * \details 
 * N: Number of clock cycles minus 1 after which the counter for the clock
 * must be adjusted.
 * E.g. setting CLK_ADJ to 1 would adjust the clock counter every 2nd clock
 * cycle.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG . CLK_ADJ
 */
#define  VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,28)

/**
 * Register Group: \a DEVCPU_GCB:PTP_STAT
 *
 * Status registers for PTP
 */


/** 
 * \brief Current PTP master timer value
 *
 * \details
 * Current PTP master timer value
 *
 * Register: \a DEVCPU_GCB:PTP_STAT:PTP_CURRENT_TIME_STAT
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x86)

/** 
 * \brief
 * Current master counter value. Unit is 4 ns.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT . PTP_CURRENT_TIME
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief External sync current time status register
 *
 * \details
 * External sync current time status register
 *
 * Register: \a DEVCPU_GCB:PTP_STAT:EXT_SYNC_CURRENT_TIME_STAT
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x87)

/** 
 * \brief
 * Snapshot of current time, when a rising edge was seen in on the external
 * sync input.
 * Note: A new value is only captured when the associated sticky bit is not
 * set.
 *
 * \details 
 * Current time in clock_ticks when the rising edge on the external sync
 * input was seen.
 * Note: This has to be adjusted by 3 clock ticks for synchronizing the
 * signal to core clock.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT . EXT_SYNC_CURRENT_TIME
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Stick register for external sync current time status
 *
 * \details
 * Stick register for external sync current time status
 *
 * Register: \a DEVCPU_GCB:PTP_STAT:PTP_EVT_STAT
 */
#define VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x88)

/** 
 * \brief
 * Identifies if the adjust value update has already happened in case the
 * adjustment is only allowed to take place at sync.
 * If update is allowed to take place immediately the sticky bit is unused.
 *
 * \details 
 * 0: updated has not yet happened
 * 1: updated has happened
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . CLK_ADJ_UPD_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * Sticky bit that indicates a synchronization pulse has been captured on
 * external sync input pin.
 *
 * \details 
 * '0': No Timestamp has been captured
 * '1': New Timestamp has been captured
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . EXT_SYNC_CURRENT_TIME_STICKY
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * Master timer has generated a synchronization pulse to the Slave Timers.
 *
 * \details 
 * '0': No master timer wrap happened.
 * '1': Master timer wrap happened.
 * Bit is cleared by writing a '1' to this position.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT . SYNC_STAT
 */
#define  VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_SYNC_STAT  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:PTP_TIMERS
 *
 * Latched values of time of day timer for PTP measurements
 */


/** 
 * \brief Time of day (Seconds)
 *
 * \details
 * Time of day (Seconds)
 *
 * Register: \a DEVCPU_GCB:PTP_TIMERS:PTP_TOD_SECS
 */
#define VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_SECS  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x89)


/** 
 * \brief Time of day (Nanoseconds)
 *
 * \details
 * Time of day (Nanoseconds)
 *
 * Register: \a DEVCPU_GCB:PTP_TIMERS:PTP_TOD_NANOSECS
 */
#define VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8a)

/** 
 * \brief
 * Nanoseconds fraction of time of day timer at latch time
 * (PTP_TIMER_CTRL.PTP_LATCH). Unit is 4 ns.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS . PTP_TOD_NANOSECS
 */
#define  VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Delay timer
 *
 * \details
 * Register: \a DEVCPU_GCB:PTP_TIMERS:PTP_DELAY
 */
#define VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_DELAY  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8b)


/** 
 * \brief Control register for PTP timers
 *
 * \details
 * Control register for PTP timers
 *
 * Register: \a DEVCPU_GCB:PTP_TIMERS:PTP_TIMER_CTRL
 */
#define VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8c)

/** 
 * \brief
 * Latch time of day counter at the same time as the delay timer.

 *
 * \details 
 * 0: No action.
 * 1: The time of day counter and the delay timer are latched at the same
 * time. The results are stored in PTP_TOD_SECS, PTP_TOD_NANOSECS, and
 * PTP_DELAY.
 *
 * Field: ::VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL . PTP_LATCH
 */
#define  VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_LATCH  VTSS_BIT(2)

/** 
 * \brief
 * Enable delay timer.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL . PTP_TIMER_ENA
 */
#define  VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TIMER_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Reset the seconds fraction of the time of day counter.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL . PTP_TOD_RST
 */
#define  VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TOD_RST  VTSS_BIT(0)

/**
 * Register Group: \a DEVCPU_GCB:MEMITGR
 *
 * Memory integrity monitor
 */


/** 
 * \brief Monitor control
 *
 * \details
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_CTRL
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8d)

/** 
 * \brief
 * Setting this field transitions the integrity monitor between operating
 * modes. Transitioning between modes takes time, this field remains set
 * until the new mode is reached. During this time the monitor also reports
 * busy (MEMITGR_MODE.MODE_BUSY is set).
 * From IDLE (MEMITGR_MODE.MODE_IDLE is set) the monitor can transition
 * into either DETECT or LISTEN mode, the DETECT mode is entered if a
 * memory reports an indication - the LISTEN mode is entered if no
 * indications are reported. The first time after reset the monitor will
 * not detect indications, that is; it will transition directly from IDLE
 * to LISTEN mode.
 * From DETECT (MEMITGR_MODE.MODE_DETECT is set) the monitor can transition
 * into either DETECT or LISTEN mode, the DETECT mode is entered if more
 * indications are reported - the LISTEN mode is entered if no more
 * indications are reported.
 * From LISTEN (MEMITGR_MODE.MODE_LISTEN is set) the monitor can transition
 * into IDLE mode.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL . ACTIVATE
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_CTRL_ACTIVATE  VTSS_BIT(0)


/** 
 * \brief Monitor status
 *
 * \details
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_STAT
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8e)

/** 
 * \brief
 * If this field is set then there is an indication from one of the
 * memories that needs to be analyzed. An indication is either a parity
 * detection or an error correction.
 * This field is only set when the monitor is in LISTEN mode
 * (MEMITGR_MODE.MODE_LISTEN is set), in all other states (including BUSY)
 * this field returns 0.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . INDICATION
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_INDICATION  VTSS_BIT(4)

/** 
 * \brief
 * This field is set when the monitor is in LISTEN mode, during listen mode
 * the monitor continually check for parity/correction indications from the
 * memories.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_LISTEN
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_LISTEN  VTSS_BIT(3)

/** 
 * \brief
 * This field is set when the monitor is in DETECT mode, during detect mode
 * the MEMITGR_INFO register contains valid information about one
 * indication.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_DETECT
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_DETECT  VTSS_BIT(2)

/** 
 * \brief
 * This field is set when the monitor is in IDLE mode.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_IDLE
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_IDLE  VTSS_BIT(1)

/** 
 * \brief
 * The busy signal is a copy of the MEMITGR_CTRL.ACTIVATE field, see
 * description of that field for more information about the different
 * states/modes of the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_STAT . MODE_BUSY
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_STAT_MODE_BUSY  VTSS_BIT(0)


/** 
 * \brief Memory indication
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (MEMITGR_MODE.MODE_DETECT is set) mode.
 *
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_INFO
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x8f)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ERR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ERR  VTSS_BIT(31)

/** 
 * \brief
 * This field is set if the monitor has detected a correction.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_COR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_COR  VTSS_BIT(30)

/** 
 * \brief
 * This field is set if the monitor has detected a parity indication (or an
 * unrecoverable correction) for which the address has not been recorded.
 * If MEMITGR_INFO.MEM_ERR is set then there has been more than one
 * indication, then only the address of the newest indication has been
 * kept. 
 * If MEMITGR_INFO.MEM_ERR is cleared then an indication has occurred for
 * which the address could not be stored, this is a very rare situation
 * that can only happen if an indication is detected just as the memory is
 * talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ERR_OVF
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ERR_OVF  VTSS_BIT(29)

/** 
 * \brief
 * This field is set if the monitor has correction indication for which the
 * address has not been recorded.
 * If MEMITGR_INFO.MEM_ERR is set then there has also been a parity
 * indication (or an unrecoverable correction) which takes priority over
 * correction indications.
 * If MEMITGR_INFO.MEM_ERR is cleared and MEMITGR_INFO.MEM_COR is set then
 * there has been more than one correction indication, then only the
 * address of the newest correction indication has been kept.
 * If MEMITGR_INFO.MEM_ERR and MEMITGR_INFO.MEM_COR is both cleared then a
 * correction indication has occurred for which the address could not be
 * stored, this is a very rare situaltion that can only happen if an
 * indication is detected just as the memory is talking to the monitor.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_COR_OVF
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_COR_OVF  VTSS_BIT(28)

/** 
 * \brief
 * This field is valid only when MEMITGR.MEM_ERR or MEMITGR.MEM_COR is set.
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_INFO . MEM_ADDR
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR(x)  VTSS_ENCODE_BITFIELD(x,0,28)
#define  VTSS_M_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR     VTSS_ENCODE_BITMASK(0,28)
#define  VTSS_X_DEVCPU_GCB_MEMITGR_MEMITGR_INFO_MEM_ADDR(x)  VTSS_EXTRACT_BITFIELD(x,0,28)


/** 
 * \brief Memory index
 *
 * \details
 * This field is only valid when the monitor is in the DETECT
 * (MEMITGR_MODE.MODE_DETECT is set) mode.
 *
 * Register: \a DEVCPU_GCB:MEMITGR:MEMITGR_IDX
 */
#define VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_IDX  VTSS_IOREG(VTSS_TO_DEVCPU_GCB,0x90)

/** 
 * \brief
 * This field contains a unique index for the memory for which info is
 * currently provided in MEMITGR_MEMINFO. Indexes are counted from 1 (not
 * 0).
 *
 * \details 
 * Field: ::VTSS_DEVCPU_GCB_MEMITGR_MEMITGR_IDX . MEM_IDX
 */
#define  VTSS_F_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_DEVCPU_GCB_MEMITGR_MEMITGR_IDX_MEM_IDX(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


#endif /* _VTSS_LUTON26_REGS_DEVCPU_GCB_H_ */
