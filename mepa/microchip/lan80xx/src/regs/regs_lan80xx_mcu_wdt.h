// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_MCU_WDT_H_
#define _VTSS_MALIBU25G_REGS_MCU_WDT_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a MCU_WDT
 *
 * Watch Dog Timer interface Registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_WDT:WDT
 *
 * WDT Registers
 */


/**
 * \brief WDT Load Register (WDT_LOAD)
 *
 * \details
 * Register: \a MCU_WDT:WDT:WDT_LOAD
 */
#define VTSS_MCU_WDT_WDT_LOAD                VTSS_IOREG(VTSS_TO_MCU_WDT,0x0)

/**
 * \brief
 * Writing this field reloads the Watch Dog Timer counter if Watch Dog is
 * not enabled.If Watch Dog is enabled, Watch Dog must be kicked for Watch
 * Dog Timer counter to be loaded with this value.This register cannot be
 * written once WDT_LOCK bit is set.The default of 0x3FFF equals 17
 * seconds.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_LOAD . WDT_LOAD
 */
#define  VTSS_F_MCU_WDT_WDT_LOAD_WDT_LOAD(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCU_WDT_WDT_LOAD_WDT_LOAD     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCU_WDT_WDT_LOAD_WDT_LOAD(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief WDT Control Register (WDT_CTL)
 *
 * \details
 * Register: \a MCU_WDT:WDT:WDT_CONTROL
 */
#define VTSS_MCU_WDT_WDT_CONTROL             VTSS_IOREG(VTSS_TO_MCU_WDT,0x1)

/**
 * \brief
 * Write to WDT_CONTROL register will be ignored if this field is not set
 * to 0xA5 during write.This field will always read back 0x0.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . WDT_CTL_KEY
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_WDT_CTL_KEY(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_WDT_CTL_KEY     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_WDT_CTL_KEY(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * This bit is used to enable the JTAG_Active, WDT STALL Operation.Firmware
 * must always set this bit to 1.Setting this bit to zero will prevent WDT
 * from stalling when MCU is halted by the debugger.This bit cannot be
 * written once WDT_LOCK bit is set.
 *
 * \details
 * 0 = JTAG_Active WDT STALL Operation not enabled
 * 1 = JTAG_Active WDT STALL Operation enabled (default)
 *
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . JTAG_STALL_EN
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_JTAG_STALL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_JTAG_STALL_EN  VTSS_BIT(4)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_JTAG_STALL_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Firmware must always set this bit to 0.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . WT_STALL_EN
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_WT_STALL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_WT_STALL_EN  VTSS_BIT(3)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_WT_STALL_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Firmware must always set this bit to 0.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . HT_STALL_EN
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_HT_STALL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_HT_STALL_EN  VTSS_BIT(2)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_HT_STALL_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This bit is set by hardware if the last reset was caused by an underflow
 * of the WDT.This bit must be cleared by firmware by writing a 1. Writing
 * a 0 to this bit has no effect.NOTE: Although this bit is set upon the
 * WDT timeout, it would be immediately reset upon the subsequent MCU reset
 * caused by the WDT timeout. Effectively, this bit is not useful.  See
 * MCU_RESET_REASON register for cause of reset.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . WDT_STATUS
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_WDT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_WDT_STATUS  VTSS_BIT(1)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_WDT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * In WDT Operation the WDT is activated by the sequence of operation "WDT
 * Activation Mechanism" and deactivated by the sequence of operations "WDT
 * Deactivation Mechanism".In WDT STALL Operation, hardware may be enabled
 * to automatically activate and deactivate the WDT.This bit cannot be
 * written once WDT_LOCK bit is set.
 *
 * \details
 * 0 - WDT is deactivated
 * 1 - WDT is activated (default)
 *
 * Field: ::VTSS_MCU_WDT_WDT_CONTROL . WDT_ENABLE
 */
#define  VTSS_F_MCU_WDT_WDT_CONTROL_WDT_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_WDT_WDT_CONTROL_WDT_ENABLE  VTSS_BIT(0)
#define  VTSS_X_MCU_WDT_WDT_CONTROL_WDT_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief WDT Kick Register (WDT_KICK)
 *
 * \details
 * Register: \a MCU_WDT:WDT:WDT_KICK
 */
#define VTSS_MCU_WDT_WDT_KICK                VTSS_IOREG(VTSS_TO_MCU_WDT,0x2)

/**
 * \brief
 * When the WDT_ENABLE bit in the WDT Control Register (WDT_CTL) is set to
 * 1, writing 0xA5 (Key) to this register causes the WDT Counter to reload
 * the WDT_LOAD value.Writing any other value has no effect.When the
 * WDT_ENABLE bit is cleared to 0, writes to this register have no
 * effect.Reads of this register return 0.Note: The actual kick to WDT will
 * be delayed due to cross-clock-domain synchronization so appropriate
 * margin must be provided when issuing the kick.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_KICK . WDT_KICK
 */
#define  VTSS_F_MCU_WDT_WDT_KICK_WDT_KICK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_WDT_WDT_KICK_WDT_KICK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_WDT_WDT_KICK_WDT_KICK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief WDT Count Register (WDT_COUNT)
 *
 * \details
 * Register: \a MCU_WDT:WDT:WDT_COUNT
 */
#define VTSS_MCU_WDT_WDT_COUNT               VTSS_IOREG(VTSS_TO_MCU_WDT,0x3)

/**
 * \brief
 * This register provides the current WDT count.
 *
 * \details
 * Field: ::VTSS_MCU_WDT_WDT_COUNT . WDT_COUNT
 */
#define  VTSS_F_MCU_WDT_WDT_COUNT_WDT_COUNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_MCU_WDT_WDT_COUNT_WDT_COUNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_MCU_WDT_WDT_COUNT_WDT_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief WDT Lock Register (WDT_LOCK)
 *
 * \details
 * Register: \a MCU_WDT:WDT:WDT_LOCK
 */
#define VTSS_MCU_WDT_WDT_LOCK                VTSS_IOREG(VTSS_TO_MCU_WDT,0x4)

/**
 * \brief
 * Setting this bit will lock WDT_LOAD and WDT_CONTROL registers from
 * further updates.Once set, this bit can only be cleared by WDT reset.
 *
 * \details
 * 0 - WDT is not locked
 * 1 - WDT is locked
 *
 * Field: ::VTSS_MCU_WDT_WDT_LOCK . WDT_LOCK
 */
#define  VTSS_F_MCU_WDT_WDT_LOCK_WDT_LOCK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_WDT_WDT_LOCK_WDT_LOCK     VTSS_BIT(0)
#define  VTSS_X_MCU_WDT_WDT_LOCK_WDT_LOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_MALIBU25G_REGS_MCU_WDT_H_ */
