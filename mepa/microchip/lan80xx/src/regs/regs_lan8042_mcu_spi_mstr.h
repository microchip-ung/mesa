// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_MCU_SPI_MSTR_H_
#define _VTSS_MALIBU25G_REGS_MCU_SPI_MSTR_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a MCU_SPI_MSTR
 *
 * MCU SPI Controller Registers
 *
 ***********************************************************************/

/**
 * Register Group: \a MCU_SPI_MSTR:SPI_MSTR_AHB
 *
 * MCU SPI Controller Registers
 */


/**
 * \brief SPI Controller Configuration Register: SPI_FR_OPCODE, SPI_TR_OPCODE, SPI_CMD_LEN, SPI_CTL
 *
 * \details
 * Though this register can be accessed as 32-bits, SPI_CMD_LEN and the
 * SPI_CTL_GO fields should not be written at the same time.  SPI_CTL_GO
 * must only be set after other fields in the register have been
 * configured.
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_CONFIG
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x0)

/**
 * \brief
 * This is the opcode used when the processor does a fast read.  Consult
 * the SPI FLASH datasheet for appropriate values.Typical values are:0x0B:
 * Single output read0x3B: Dual output read
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_FR_OPCODE
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_FR_OPCODE(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_FR_OPCODE     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_FR_OPCODE(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * This is the opcode used when the processor does a write to 0x6100_BFFE
 * or 0x6100_BFFF.Note: This field defaults to 0x0 so it must be
 * configured.Use the value of 0xDB.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_TF_OPCODE
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_TF_OPCODE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_TF_OPCODE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_TF_OPCODE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * This is the length of the SPI transaction length for firmware initiated
 * transactions.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CMD_LEN
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CMD_LEN(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CMD_LEN     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CMD_LEN(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Set the speed of SPI operation.  SPI speed can be set dynamically
 * between commands but it is recommended that it be set based on expected
 * usage.Setting this bit to 1 will operate the SPI SCK at maximum
 * frequency of 50MHz.Setting this bit to 0 will operate the SPI SCK at
 * one-half frequency of 25MHz.Note: When using TRACE FIFO only, this bit
 * should be set to 1 for maximum throughput.When using with SPI FLASH this
 * bit should be set to 0 unless the FLASH device used can support clock to
 * data out of less than 6ns.
 *
 * \details
 * 0: 25 MHz
 * 1: 50 MHz
 *
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_SPI_SPEED
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_SPI_SPEED(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_SPI_SPEED  VTSS_BIT(7)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_SPI_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * When this bit is set, it forces the SPI chip enable low. This bit should
 * only be set when using the SPI command buffer. It should never be set
 * when doing direct accesses from the AHB bus.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_FORCE_CE
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_FORCE_CE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_FORCE_CE  VTSS_BIT(4)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_FORCE_CE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Dual output fast read enable
 *
 * \details
 * 0: Dual output disabled for fast reads
 * 1: Dual output enabled for fast reads.
 *
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_DUAL_OUT_EN
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_DUAL_OUT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_DUAL_OUT_EN  VTSS_BIT(3)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_DUAL_OUT_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * This set the SPI clock mode
 *
 * \details
 * 0: Mode 0
 * 1: Mode 3
 *
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_MODE_SEL
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_MODE_SEL  VTSS_BIT(2)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable the SPI cache
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_CACHE_EN
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_CACHE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_CACHE_EN  VTSS_BIT(1)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_CACHE_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This is a self clearing bit. Setting this bit will cause the SPI
 * transaction to initiate.This bit must only be set after other fields in
 * the register have been fully configured by a separate write operation.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG . SPI_CTL_GO
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_GO(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_GO  VTSS_BIT(0)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CONFIG_SPI_CTL_GO(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SPI Controller Command Buffer A: SPI_CMD_BUF3[7:0] , SPI_CMD_BUF2[7:0] , SPI_CMD_BUF1[7:0], SPI_CMD_BUF0[7:0]
 *
 * \details
 * This buffer is used by processor to store outgoing SPI commands.
 * Bytes will go out lower buffer number to higher buffer number.
 * MCU_SPI_MSTR_CMD_BUFB extends the number of buffers.
 * Total number of bytes sent is determined by CMD_LEN field of
 * MCU_SPI_MSRE_CONFIG register.
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_CMD_BUFA
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x2)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA . SPI_CMD_BUF3
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA . SPI_CMD_BUF2
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA . SPI_CMD_BUF1
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA . SPI_CMD_BUF0
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFA_SPI_CMD_BUF0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SPI Controller Command Buffer B: SPI_CMD_BUF7[7:0] , SPI_CMD_BUF6[7:0] , SPI_CMD_BUF5[7:0], SPI_CMD_BUF4[7:0]
 *
 * \details
 * This buffer is used by processor to store outgoing SPI commands.
 * This extents MCU_SPI_MSTR_CMD_BUFA.
 * Bytes will go out lower buffer number to higher buffer number after
 * MCU_SPI_MSTR_CMD_BUFA has been sent.
 * Total number of bytes sent is determined by CMD_LEN field of
 * MCU_SPI_MSRE_CONFIG register.
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_CMD_BUFB
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x3)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB . SPI_CMD_BUF7
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF7(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF7     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF7(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB . SPI_CMD_BUF6
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF6(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF6     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF6(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB . SPI_CMD_BUF5
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Outgoing SPI command byte buffer.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB . SPI_CMD_BUF4
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_CMD_BUFB_SPI_CMD_BUF4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SPI Controller Command Buffer A: SPI_RSP_BUF3[7:0] , SPI_RSP_BUF2[7:0] , SPI_RSP_BUF1[7:0], SPI_RSP_BUF0[7:0]
 *
 * \details
 * This buffer is used by processor to store incoming SPI responses.
 * Bytes are received in the lower buffer number to higher buffer number.
 * MCU_SPI_MSTR_RSP_BUFB extends the number of buffers.
 * Total number of bytes received is determined by CMD_LEN field of
 * MCU_SPI_MSRE_CONFIG register.
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_RSP_BUFA
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x4)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA . SPI_RSP_BUF3
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF3(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF3     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF3(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA . SPI_RSP_BUF2
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF2(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF2     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF2(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA . SPI_RSP_BUF1
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF1(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF1     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF1(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA . SPI_RSP_BUF0
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFA_SPI_RSP_BUF0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SPI Controller Command Buffer B: SPI_RSP_BUF7[7:0] , SPI_RSP_BUF6[7:0] , SPI_RSP_BUF5[7:0], SPI_RSP_BUF4[7:0]
 *
 * \details
 * This buffer is used by processor to store incoming SPI responses.
 * This extents MCU_SPI_MSTR_RSP_BUFA.
 * Bytes are received in the lower buffer number to higher buffer number
 * after MCU_SPI_MSTR_RSP_BUFA has been filled.
 * Total number of bytes received is determined by CMD_LEN field of
 * MCU_SPI_MSRE_CONFIG register.
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_RSP_BUFB
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x5)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB . SPI_RSP_BUF7
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF7(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF7     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF7(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB . SPI_RSP_BUF6
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF6(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF6     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF6(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB . SPI_RSP_BUF5
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF5(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF5     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF5(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Incoming SPI response byte.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB . SPI_RSP_BUF4
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF4(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF4     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_RSP_BUFB_SPI_RSP_BUF4(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief SPI Controller Pad Control Register
 *
 * \details
 * SPI Controller Pad Control Register
 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_PAD_CTL
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x6)

/**
 * \brief
 * PAD MUX override.Setting this bit to 1 will take over associated pads
 * for SPI Controller usage.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL . SPI_PAD_MUX_OVRD
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_SPI_PAD_MUX_OVRD(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_SPI_PAD_MUX_OVRD  VTSS_BIT(7)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_SPI_PAD_MUX_OVRD(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL . MCU_SPI_MSTR_PAD_CTL_RESERVED
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_MCU_SPI_MSTR_PAD_CTL_RESERVED(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_MCU_SPI_MSTR_PAD_CTL_RESERVED     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_PAD_CTL_MCU_SPI_MSTR_PAD_CTL_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SPI Controller Trace FIFO Write Register
 *
 * \details
 * SPI Controller Trace FIFO Write Register
 * Note: Only the upper half word, bits [31:16], are valid.
 * This register must be written as a byte at byte address offset 0xBFFE or
 * 0xBFFF, or half-word (16-bits) at byte address offset 0xBFFE only.  A
 * 32-bit write will have no effect.
 * Data written to this register is sent out as a Trace FIFO transfer.
 * CAUTION: A read of this register will cause bus error.

 *
 * Register: \a MCU_SPI_MSTR:SPI_MSTR_AHB:MCU_SPI_MSTR_TRFIFO_WR
 */
#define VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR  VTSS_IOREG(VTSS_TO_MCU_SPI_MSTR,0x2fff)

/**
 * \brief
 * Writing a byte to this register address will initiate a Trace FIFO
 * transfer with the byte written as the data.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR . TRFIFO_BFFF
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFF(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFF     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFF(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Writing a byte to this register address will initiate a Trace FIFO
 * transfer with the byte written as the data.
 *
 * \details
 * Field: ::VTSS_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR . TRFIFO_BFFE
 */
#define  VTSS_F_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFE(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFE     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_MCU_SPI_MSTR_MCU_SPI_MSTR_TRFIFO_WR_TRFIFO_BFFE(x)  VTSS_EXTRACT_BITFIELD(x,16,8)


#endif /* _VTSS_MALIBU25G_REGS_MCU_SPI_MSTR_H_ */
