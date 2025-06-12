// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_MCU_MAILBOX_H_
#define _LAN80XX_MALIBU25G_REGS_MCU_MAILBOX_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a MCU_MAILBOX
 *
 * mailbox registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_MAILBOX:MAILBOX_FLAG
 *
 * mailbox flag registers
 */


/**
 * \brief Mailbox Flag Register
 *
 * \details
 * Mailbox Flag Register
 * [31:24] MAILBOX_FLAG_CLEAR
 * [23:16] MAILBOX_FLAG_SET
 * [7:0] MAILBOX_FLAG
 *
 * Register: \a MCU_MAILBOX:MAILBOX_FLAG:MAILBOX_FLAG
 */
#define LAN80XX_MCU_MAILBOX_MAILBOX_FLAG        LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, 0xda00)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[7]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect

 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_7
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_7(x)  LAN80XX_ENCODE_BITFIELD(!!(x),31,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_7  LAN80XX_BIT(31)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_7(x)  LAN80XX_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[6]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_6
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_6(x)  LAN80XX_ENCODE_BITFIELD(!!(x),30,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_6  LAN80XX_BIT(30)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_6(x)  LAN80XX_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[5]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_5
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_5(x)  LAN80XX_ENCODE_BITFIELD(!!(x),29,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_5  LAN80XX_BIT(29)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_5(x)  LAN80XX_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[4]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_4
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_4(x)  LAN80XX_ENCODE_BITFIELD(!!(x),28,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_4  LAN80XX_BIT(28)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_4(x)  LAN80XX_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[3]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_3
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_3(x)  LAN80XX_ENCODE_BITFIELD(!!(x),27,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_3  LAN80XX_BIT(27)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_3(x)  LAN80XX_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[2]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_2
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_2(x)  LAN80XX_ENCODE_BITFIELD(!!(x),26,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_2  LAN80XX_BIT(26)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_2(x)  LAN80XX_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[1]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_1
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_1(x)  LAN80XX_ENCODE_BITFIELD(!!(x),25,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_1  LAN80XX_BIT(25)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_1(x)  LAN80XX_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Writing a 1 to a selected bit will clear MAILBOX_FLAG[0]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: clear
 * 0: has no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_CLEAR_0
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_0(x)  LAN80XX_ENCODE_BITFIELD(!!(x),24,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_0  LAN80XX_BIT(24)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_CLEAR_0(x)  LAN80XX_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[7]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_7
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_7(x)  LAN80XX_ENCODE_BITFIELD(!!(x),23,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_7  LAN80XX_BIT(23)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_7(x)  LAN80XX_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[6]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_6
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_6(x)  LAN80XX_ENCODE_BITFIELD(!!(x),22,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_6  LAN80XX_BIT(22)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_6(x)  LAN80XX_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[5]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_5
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_5(x)  LAN80XX_ENCODE_BITFIELD(!!(x),21,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_5  LAN80XX_BIT(21)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_5(x)  LAN80XX_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[4]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_4
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_4(x)  LAN80XX_ENCODE_BITFIELD(!!(x),20,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_4  LAN80XX_BIT(20)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_4(x)  LAN80XX_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[3]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_3
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_3(x)  LAN80XX_ENCODE_BITFIELD(!!(x),19,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_3  LAN80XX_BIT(19)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_3(x)  LAN80XX_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[2]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_2
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_2(x)  LAN80XX_ENCODE_BITFIELD(!!(x),18,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_2  LAN80XX_BIT(18)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_2(x)  LAN80XX_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[1]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_1
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_1(x)  LAN80XX_ENCODE_BITFIELD(!!(x),17,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_1  LAN80XX_BIT(17)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_1(x)  LAN80XX_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Writing a 1 to a selected bit will set MAILBOX_FLAG[0]Writing a 0 to a
 * selected bit has no effect.Reads of this field always return zero.
 *
 * \details
 * 1: set
 * 0: no effect
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG_SET_0
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_0(x)  LAN80XX_ENCODE_BITFIELD(!!(x),16,1)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_0  LAN80XX_BIT(16)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG_SET_0(x)  LAN80XX_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * The Mailbox Flags are read through these bits.
 *
 * \details
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_FLAG . MAILBOX_FLAG
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_FLAG_MAILBOX_FLAG(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MCU_MAILBOX:MAILBOX_INT_MASK
 *
 * Mailbox interrupt mask registers
 */


/**
 * \brief Mailbox MCU Interrupt Mask Register
 *
 * \details
 * Mailbox MCU Interrupt Mask Register (MAILBOX_MCU_INT_MASK)
 *
 * Register: \a MCU_MAILBOX:MAILBOX_INT_MASK:MAILBOX_MCU_INT_MASK
 */
#define LAN80XX_MCU_MAILBOX_MAILBOX_MCU_INT_MASK  LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, 0xda01)

/**
 * \brief
 * A 1 on a bit enables(i.e. the mask bit is active low) the generation of
 * an MCU interrupt caused by a MAILBOX_FLAG bit.
 *
 * \details
 * 1: interrupt enabled
 * 0: interrupt masked
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_MCU_INT_MASK . MAILBOX_MCU_INT_MASK
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_MCU_INT_MASK_MAILBOX_MCU_INT_MASK(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_MCU_INT_MASK_MAILBOX_MCU_INT_MASK     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_MCU_INT_MASK_MAILBOX_MCU_INT_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Mailbox Host Interrupt Mask Register
 *
 * \details
 * Mailbox Host Interrupt Mask Register (MAILBOX_HOST_INT_MASK)
 *
 * Register: \a MCU_MAILBOX:MAILBOX_INT_MASK:MAILBOX_HOST_INT_MASK
 */
#define LAN80XX_MCU_MAILBOX_MAILBOX_HOST_INT_MASK  LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, 0xda02)

/**
 * \brief
 * A 1 on a bit enables(i.e. the mask bit is active low) the generation of
 * a Host interrupt caused by a MAILBOX_FLAG bit.
 *
 * \details
 * 1: interrupt enabled
 * 0: interrupt masked
 *
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_HOST_INT_MASK . MAILBOX_HOST_INT_MASK
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_HOST_INT_MASK_MAILBOX_HOST_INT_MASK(x)  LAN80XX_ENCODE_BITFIELD(x,0,8)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_HOST_INT_MASK_MAILBOX_HOST_INT_MASK     LAN80XX_ENCODE_BITMASK(0,8)
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_HOST_INT_MASK_MAILBOX_HOST_INT_MASK(x)  LAN80XX_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a MCU_MAILBOX:MAILBOX_DATA
 *
 * mailbox data register
 */


/**
 * \brief mailbox data register
 *
 * \details
 * the mailbox data mapped to a 512x32 ram
 *
 * Register: \a MCU_MAILBOX:MAILBOX_DATA:MAILBOX_DATA_REG
 *
 * @param ri Register: MAILBOX_DATA_REG (??), 0-511
 */
#define LAN80XX_MCU_MAILBOX_MAILBOX_DATA_REG(ri)  LAN80XX_IOREG(MMD_ID_MCU_MAILBOX, 1, 0xd800 + (ri))

/**
 * \brief
 * the mailbox data mapped to an entry of the ram
 *
 * \details
 * Field: ::LAN80XX_MCU_MAILBOX_MAILBOX_DATA_REG . MBOX_DATA
 */
#define  LAN80XX_F_MCU_MAILBOX_MAILBOX_DATA_REG_MBOX_DATA(x)  (x)
#define  LAN80XX_M_MCU_MAILBOX_MAILBOX_DATA_REG_MBOX_DATA     0xffffffff
#define  LAN80XX_X_MCU_MAILBOX_MAILBOX_DATA_REG_MBOX_DATA(x)  (x)


#endif /* _LAN80XX_MALIBU25G_REGS_MCU_MAILBOX_H_ */
