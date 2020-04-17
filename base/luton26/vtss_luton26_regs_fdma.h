// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LUTON26_REGS_FDMA_H_
#define _VTSS_LUTON26_REGS_FDMA_H_


#include "vtss_luton26_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a FDMA
 *
 * VCore GPDMA Configuration
 *
 ***********************************************************************/

/**
 * Register Group: \a FDMA:CH
 *
 * DMA Channel Controller Configuration
 */


/** 
 * \brief Source Address
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 *
 * Register: \a FDMA:CH:SAR
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_SAR(gi)                 VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,0)


/** 
 * \brief Destination Address
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 *
 * Register: \a FDMA:CH:DAR
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_DAR(gi)                 VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,2)


/** 
 * \brief Linked List Pointer
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 *
 * Register: \a FDMA:CH:LLP
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_LLP(gi)                 VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,4)

/** 
 * \brief
 * Write the 32-bit aligned address of the first DCB in the chain of DCBs.
 * The DMA channel updates this field as it traverses the list of DCBs. The
 * two least significant bits are zeroed out before being used.
 *
 * \details 
 * 0 : Disable block chaining (initial read of DCB addressed by LLP before
 * a block transfer)
 * >0: Enable block chaining (initial read of DCB addressed by LLP before a
 * block transfer)
 *
 * Field: ::VTSS_FDMA_CH_LLP . LOC
 */
#define  VTSS_F_FDMA_CH_LLP_LOC(x)            VTSS_ENCODE_BITFIELD(x,2,29)
#define  VTSS_M_FDMA_CH_LLP_LOC               VTSS_ENCODE_BITMASK(2,29)
#define  VTSS_X_FDMA_CH_LLP_LOC(x)            VTSS_EXTRACT_BITFIELD(x,2,29)


/** 
 * \brief DMA Transfer Control
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 *
 * Register: \a FDMA:CH:CTL0
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_CTL0(gi)                VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,6)

/** 
 * \brief
 * Enable reload of SAR from next DCB in chain. When this field is set and
 * the LLP is non-zero, the SAR will be reloaded from the next DCB upon
 * completion of the current DCB.
 *
 * \details 
 * 0: Disable update 
 * 1: Enable 
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . LLP_SRC_EN
 */
#define  VTSS_F_FDMA_CH_CTL0_LLP_SRC_EN       VTSS_BIT(28)

/** 
 * \brief
 * Enable reload of DAR from next DCB in chain. When this field is set and
 * the LLP is non-zero, the DAR will be reloaded from the next DCB upon
 * completion of the current DCB.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . LLP_DST_EN
 */
#define  VTSS_F_FDMA_CH_CTL0_LLP_DST_EN       VTSS_BIT(27)

/** 
 * \brief
 * Source Master Select. 
 * INJ / GP: Must be set to 0
 * XTR: Must be set to 1
 *
 * \details 
 * 0 = AHB master 1
 * 1 = AHB master 2
 * Other: reserved
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . SMS
 */
#define  VTSS_F_FDMA_CH_CTL0_SMS(x)           VTSS_ENCODE_BITFIELD(x,25,2)
#define  VTSS_M_FDMA_CH_CTL0_SMS              VTSS_ENCODE_BITMASK(25,2)
#define  VTSS_X_FDMA_CH_CTL0_SMS(x)           VTSS_EXTRACT_BITFIELD(x,25,2)

/** 
 * \brief
 * Destination Master Select.
 * XTR / GP: Must be set to 0
 * INJ: Must be set to 1
 *
 * \details 
 * 0 = AHB master 1
 * 1 = AHB master 2
 * Other: Reserved
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . DMS
 */
#define  VTSS_F_FDMA_CH_CTL0_DMS(x)           VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_FDMA_CH_CTL0_DMS              VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_FDMA_CH_CTL0_DMS(x)           VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * Transfer Type and Flow Control.
 * GP: Must be set to 0
 * INJ: Must be set to 0 or 1
 * XTR: Must be set to 4
 *
 * \details 
 * 0 : Memory to Memory
 * 1 : Memory to Peripheral
 * 4 : Peripheral to Memory
 * Other: Reserved
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . TT_FC
 */
#define  VTSS_F_FDMA_CH_CTL0_TT_FC(x)         VTSS_ENCODE_BITFIELD(x,20,3)
#define  VTSS_M_FDMA_CH_CTL0_TT_FC            VTSS_ENCODE_BITMASK(20,3)
#define  VTSS_X_FDMA_CH_CTL0_TT_FC(x)         VTSS_EXTRACT_BITFIELD(x,20,3)

/** 
 * \brief
 * Source Burst Transaction Length. 
 * INJ / GP: Number of data items, each with a width of CTL.SRC_TR_WIDTH,
 * to be read from the source every time a source burst transaction request
 * is made from either the corresponding hardware or software handshaking
 * interface. 
 * XTR : Must be <3
 *
 * \details 
 * 0 : 1 word
 * 1 : 4 words
 * 2 : 8 words
 * 3: 16 words
 * 4: 32 words
 * 5: 64 words
 * 6: 128 words
 * 7: 256 words
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . SRC_MSIZE
 */
#define  VTSS_F_FDMA_CH_CTL0_SRC_MSIZE(x)     VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_FDMA_CH_CTL0_SRC_MSIZE        VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_FDMA_CH_CTL0_SRC_MSIZE(x)     VTSS_EXTRACT_BITFIELD(x,14,3)

/** 
 * \brief
 * Destination Burst Transaction Length.
 * INJ / GP: Number of data items, each with a width of CTL.DST_TR_WIDTH,
 * to be written to the destination every time a destination burst
 * transaction request is made from either the corresponding hardware or
 * software handshaking interface.
 * XTR : Must be <3
 *
 * \details 
 * 0 : 1 word
 * 1 : 4 words
 * 2 : 8 words
 * 3: 16 words
 * 4: 32 words
 * 5: 64 words
 * 6: 128 words
 * 7: 256 words
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . DEST_MSIZE
 */
#define  VTSS_F_FDMA_CH_CTL0_DEST_MSIZE(x)    VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_FDMA_CH_CTL0_DEST_MSIZE       VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_FDMA_CH_CTL0_DEST_MSIZE(x)    VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Source Address Increment.
 * INJ / GP: Indicates whether to increment or decrement the source address
 * on every source transfer. If the device is fetching data from a source
 * peripheral FIFO with a fixed address, then set this field to no change.
 * XTR: Must be set to no change.
 *
 * \details 
 * 00 : Increment
 * 01 : Decrement
 * 1x : No change
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . SINC
 */
#define  VTSS_F_FDMA_CH_CTL0_SINC(x)          VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_FDMA_CH_CTL0_SINC             VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_FDMA_CH_CTL0_SINC(x)          VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * Destination Address Increment.
 * XTR / GP: Indicates whether to increment or decrement the destination
 * address on every destination transfer. If your device is writing data to
 * a destination peripheral FIFO with a fixed address, then set this field
 * to no change.
 * INJ: Must be set to no change.
 *
 * \details 
 * 00 : Increment
 * 01 : Decrement
 * 1x : No change
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . DINC
 */
#define  VTSS_F_FDMA_CH_CTL0_DINC(x)          VTSS_ENCODE_BITFIELD(x,7,2)
#define  VTSS_M_FDMA_CH_CTL0_DINC             VTSS_ENCODE_BITMASK(7,2)
#define  VTSS_X_FDMA_CH_CTL0_DINC(x)          VTSS_EXTRACT_BITFIELD(x,7,2)

/** 
 * \brief
 * Source Transfer Width.
 * GP:	Specifies source address alignment (for example, 32-bit transfer
 * can only be 32-bit aligned).
 * INJ /  XTR: Must be set to 2.
 *
 * \details 
 * 0 : 8-bit
 * 1 : 16-bit
 * 2 : 32-bit
 * Other : Undefined
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . SRC_TR_WIDTH
 */
#define  VTSS_F_FDMA_CH_CTL0_SRC_TR_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_FDMA_CH_CTL0_SRC_TR_WIDTH     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_FDMA_CH_CTL0_SRC_TR_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/** 
 * \brief
 * Destination Transfer Width.
 * GP:	Specifies destination address alignment (for example, 32-bit
 * transfer can only be 32-bit aligned).
 * INJ /  XTR: Must be set to 2.
 *
 * \details 
 * 0 : 8-bit
 * 1 : 16-bit
 * 2 : 32-bit
 * Other : Undefined
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . DST_TR_WIDTH
 */
#define  VTSS_F_FDMA_CH_CTL0_DST_TR_WIDTH(x)  VTSS_ENCODE_BITFIELD(x,1,3)
#define  VTSS_M_FDMA_CH_CTL0_DST_TR_WIDTH     VTSS_ENCODE_BITMASK(1,3)
#define  VTSS_X_FDMA_CH_CTL0_DST_TR_WIDTH(x)  VTSS_EXTRACT_BITFIELD(x,1,3)

/** 
 * \brief
 * Interrupt Enable Bit. If set, then all interrupt-generating sources are
 * enabled.
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_FDMA_CH_CTL0 . INT_EN
 */
#define  VTSS_F_FDMA_CH_CTL0_INT_EN           VTSS_BIT(0)


/** 
 * \brief DMA Transfer Control
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 * If status write-back is enabled, the register is used to update the
 * control register location of the DCB in system memory at the end of the
 * block transfer.
 *
 * Register: \a FDMA:CH:CTL1
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_CTL1(gi)                VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,7)

/** 
 * \brief
 * Done bit.
 * Software can poll the DCB CTL.DONE bit to see when a block transfer is
 * complete. The DCB CTL.DONE bit should be cleared when the linked lists
 * are set up in memory prior to enabling the channel.
 *
 * \details 
 * 0: Block transfer is not done
 * 0: Block transfer is done
 *
 * Field: ::VTSS_FDMA_CH_CTL1 . DONE
 */
#define  VTSS_F_FDMA_CH_CTL1_DONE             VTSS_BIT(12)

/** 
 * \brief
 * Block Transfer Size.
 * INJ / GP : The number programmed into BLOCK_TS indicates the total
 * number of single transactions to perform for every block transfer.
 * XTR: Updated with the number of 32-bits words returned.
 * Once the transfer starts, the read-back value is the total number of
 * data items already read from the source peripheral.
 *
 * \details 
 * Field: ::VTSS_FDMA_CH_CTL1 . BLOCK_TS
 */
#define  VTSS_F_FDMA_CH_CTL1_BLOCK_TS(x)      VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_FDMA_CH_CTL1_BLOCK_TS         VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_FDMA_CH_CTL1_BLOCK_TS(x)      VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief Source Status
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.

 *
 * Register: \a FDMA:CH:SSTAT
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_SSTAT(gi)               VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,8)


/** 
 * \brief Destination Status
 *
 * \details
 * This register is part of the DCB (and is updated on a DCB-by-DCB basis)
 * when block chaining is enabled.
 *
 * Register: \a FDMA:CH:DSTAT
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_DSTAT(gi)               VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,10)


/** 
 * \brief Source Status Address Location
 *
 * \details
 * Register: \a FDMA:CH:SSTATAR
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_SSTATAR(gi)             VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,12)


/** 
 * \brief Destination Status Address Location
 *
 * \details
 * Register: \a FDMA:CH:DSTATAR
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_DSTATAR(gi)             VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,14)


/** 
 * \brief DMA Transfer Configuration (CFG0)
 *
 * \details
 * This register contains fields that configure the DMA transfer and
 * remains fixed for all blocks of a multi-block transfer.
 *
 * Register: \a FDMA:CH:CFG0
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_CFG0(gi)                VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,16)

/** 
 * \brief
 * GP: Automatic destination reload. The DAR register can be automatically
 * reloaded from its initial value at the end of every block for
 * multi-block transfers. A new block transfer is then initiated.
 * INJ / XTR : Must be zero.
 *
 * \details 
 * 0 : Disable
 * 1:  Enable
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . RELOAD_DST
 */
#define  VTSS_F_FDMA_CH_CFG0_RELOAD_DST       VTSS_BIT(31)

/** 
 * \brief
 * GP: Automatic source reload. The SAR register can be automatically
 * reloaded from its initial value at the end of every block for
 * multi-block transfers. A new block transfer is then initiated.
 * INJ / XTR : Must be zero.
 *
 * \details 
 * Field: ::VTSS_FDMA_CH_CFG0 . RELOAD_SRC
 */
#define  VTSS_F_FDMA_CH_CFG0_RELOAD_SRC       VTSS_BIT(30)

/** 
 * \brief
 * Bus lock bit. When active, the AHB bus master signal block is asserted
 * for the duration specified in CFG.LOCK_B_L. 
 *
 * \details 
 * Field: ::VTSS_FDMA_CH_CFG0 . LOCK_B
 */
#define  VTSS_F_FDMA_CH_CFG0_LOCK_B           VTSS_BIT(17)

/** 
 * \brief
 * Channel lock bit. When the channel is granted control of the master bus
 * interface and if the CFG0.LOCK_CH bit is asserted, then no other
 * channels are granted control of the master bus interface for the
 * duration specified in CFG0.LOCK_CH_L. Indicates to the master bus
 * interface arbiter that this channel wants exclusive access to the master
 * bus interface for the duration specified in CFG0.LOCK_CH_L.
 *
 * \details 
 * Field: ::VTSS_FDMA_CH_CFG0 . LOCK_CH
 */
#define  VTSS_F_FDMA_CH_CFG0_LOCK_CH          VTSS_BIT(16)

/** 
 * \brief
 * Bus lock level. Indicates the duration over which CFG0.LOCK_B bit
 * applies.
 *
 * \details 
 * 0 : Over complete DMA transfer
 * 1 : Over complete DMA block transfer
 * Other:  Over complete DMA transaction
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . LOCK_B_L
 */
#define  VTSS_F_FDMA_CH_CFG0_LOCK_B_L(x)      VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_FDMA_CH_CFG0_LOCK_B_L         VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_FDMA_CH_CFG0_LOCK_B_L(x)      VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Channel lock level. Indicates the duration over which CFG0.LOCK_CH bit
 * applies.
 *
 * \details 
 * 0 : Over complete DMA transfer
 * 1 : Over complete DMA block transfer
 * Other : Over complete DMA transaction
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . LOCK_CH_L
 */
#define  VTSS_F_FDMA_CH_CFG0_LOCK_CH_L(x)     VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_FDMA_CH_CFG0_LOCK_CH_L        VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_FDMA_CH_CFG0_LOCK_CH_L(x)     VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Source software or hardware handshaking select.
 * INJ / GP :  Must be 1
 * XTR: Must be 0
 *
 * \details 
 * 0 = Hardware handshaking interface. Software-initiated transaction
 * requests are ignored.
 * 1 = Software handshaking interface. Hardware-initiated transaction
 * requests are ignored.
 * If the source peripheral is memory, then this bit is ignored.
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . HS_SEL_SRC
 */
#define  VTSS_F_FDMA_CH_CFG0_HS_SEL_SRC       VTSS_BIT(11)

/** 
 * \brief
 * Destination software or hardware handshaking select.
 * This register selects which of the handshaking interfaces (hardware or
 * software) is active for destination requests on this channel.
 * XTR / GP : Must be 1
 *
 * \details 
 * 0 = Hardware handshaking interface. Software-initiated transaction
 * requests are ignored.
 * 1 = Software handshaking interface. Hardware-initiated transaction
 * requests are ignored.
 * If the destination peripheral is memory, then this bit is ignored.
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . HS_SEL_DST
 */
#define  VTSS_F_FDMA_CH_CFG0_HS_SEL_DST       VTSS_BIT(10)

/** 
 * \brief
 * Indicates if there is data left in the channel FIFO. Can be used in
 * conjunction with CFG0.CH_SUSP to cleanly disable a channel.
 *
 * \details 
 * 1 = Channel FIFO empty
 * 0 = Channel FIFO not empty
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . FIFO_EMPTY
 */
#define  VTSS_F_FDMA_CH_CFG0_FIFO_EMPTY       VTSS_BIT(9)

/** 
 * \brief
 * Channel suspend. Suspends all DMA data transfers from the source until
 * this bit is cleared. There is no guarantee that the current transaction
 * will complete. Can also be used in conjunction with CFG0.FIFO_EMPTY to
 * cleanly disable a channel without losing any data.
 *
 * \details 
 * 0 = Not suspended
 * 1 = Suspend DMA transfer from the source
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . CH_SUSP
 */
#define  VTSS_F_FDMA_CH_CFG0_CH_SUSP          VTSS_BIT(8)

/** 
 * \brief
 * Channel priority.
 *
 * \details 
 * 0 : Lowest priority
 * ...
 * 7 : Highest priority
 *
 * Field: ::VTSS_FDMA_CH_CFG0 . CH_PRIOR
 */
#define  VTSS_F_FDMA_CH_CFG0_CH_PRIOR(x)      VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_FDMA_CH_CFG0_CH_PRIOR         VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_FDMA_CH_CFG0_CH_PRIOR(x)      VTSS_EXTRACT_BITFIELD(x,5,3)


/** 
 * \brief DMA Transfer Configuration (CFG1)
 *
 * \details
 * This register contains fields that configure the DMA transfer and
 * remains fixed for all blocks of a multi-block transfer.
 *
 * Register: \a FDMA:CH:CFG1
 *
 * @param gi Register: CH (??), 0-7
 */
#define VTSS_FDMA_CH_CFG1(gi)                VTSS_IOREG_IX(VTSS_TO_DMAC,0x0,gi,22,0,17)

/** 
 * \brief
 * INJ: Destination peripheral handshaking interface. Valid if
 * CFG0.HS_SEL_DST field is 0. Otherwise, this field is ignored.
 * XTR/GP: Not used
 *
 * \details 
 * Must be mapped according the channel number, that is, channel number 0
 * must be assigned interface 0, and so on.
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . DST_PER
 */
#define  VTSS_F_FDMA_CH_CFG1_DST_PER(x)       VTSS_ENCODE_BITFIELD(x,11,4)
#define  VTSS_M_FDMA_CH_CFG1_DST_PER          VTSS_ENCODE_BITMASK(11,4)
#define  VTSS_X_FDMA_CH_CFG1_DST_PER(x)       VTSS_EXTRACT_BITFIELD(x,11,4)

/** 
 * \brief
 * XTR: Source peripheral handshaking interface. Valid if CFG0.HS_SEL_SRC
 * field is 0. Otherwise, this field is ignored.
 * INJ/GP: Not used
 *
 * \details 
 * Must be mapped according the channel number, that is, channel number 0
 * must be assigned interface 0, and so on.
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . SRC_PER
 */
#define  VTSS_F_FDMA_CH_CFG1_SRC_PER(x)       VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_FDMA_CH_CFG1_SRC_PER          VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_FDMA_CH_CFG1_SRC_PER(x)       VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Source status update enable.
 * GP: Source status information is fetched only from the location pointed
 * to by the SSTATAR register, stored in the SSTAT register, and written
 * out to the DCB SSTAT  if SS_UPD_EN is high.
 * INJ / XTR : Must be zero
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . SS_UPD_EN
 */
#define  VTSS_F_FDMA_CH_CFG1_SS_UPD_EN        VTSS_BIT(6)

/** 
 * \brief
 * Destination status update enable.
 * GP: Destination status information is fetched from the location pointed
 * to by the DSTATAR register, stored in the DSTAT register, and written
 * out to the DCB DSTAT only if DS_UPD_EN is high.
 * INJ : Must be zero
 * XTR : Must be one
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . DS_UPD_EN
 */
#define  VTSS_F_FDMA_CH_CFG1_DS_UPD_EN        VTSS_BIT(5)

/** 
 * \brief
 * FIFO mode select. Determines how much space or data needs to be
 * available in the FIFO before a burst transaction request is serviced.
 *
 * \details 
 * 0 = Space/data available for single AHB transfer of the specified
 * transfer width.
 * 1 = Space/data available is greater than or equal to half the FIFO depth
 * for destination transfers and less than half the FIFO depth for source
 * transfers. The exceptions are at the end of a burst transaction request
 * or at the end of a block transfer.
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . FIFOMODE
 */
#define  VTSS_F_FDMA_CH_CFG1_FIFOMODE         VTSS_BIT(1)

/** 
 * \brief
 * Flow control mode.
 * GP : Determines when source transaction requests are serviced when the
 * Destination Peripheral is the flow controller.
 * INJ / XTR : Must be one
 *
 * \details 
 * 0 = Source transaction requests are serviced when they occur. Data
 * pre-fetching is enabled.
 * 1 = Source transaction requests are not serviced until a destination
 * transaction request occurs. In this mode, the amount of data transferred
 * from the source is limited so that it is guaranteed to be transferred to
 * the destination prior to block termination by the destination. Data
 * pre-fetching is disabled.
 *
 * Field: ::VTSS_FDMA_CH_CFG1 . FCMODE
 */
#define  VTSS_F_FDMA_CH_CFG1_FCMODE           VTSS_BIT(0)

/**
 * Register Group: \a FDMA:INTR
 *
 * DMA Interrupt Configuration
 */


/** 
 * \brief Raw Status for IntTfr Interrupt
 *
 * \details
 * This interrupt is generated when the FDMA reaches the end of a DCB chain
 * (done processing a DCB with LLP field = NULL) or when completing a
 * general purpose operation that does not use DCBs.
 *
 * Register: \a FDMA:INTR:RAW_TFR
 */
#define VTSS_FDMA_INTR_RAW_TFR               VTSS_IOREG(VTSS_TO_DMAC,0xb0)

/** 
 * \brief
 * Raw interrupt status. Interrupt events are stored in this field before
 * masking. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt condition has occurred.
 *
 * Field: ::VTSS_FDMA_INTR_RAW_TFR . RAW_TFR
 */
#define  VTSS_F_FDMA_INTR_RAW_TFR_RAW_TFR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_RAW_TFR_RAW_TFR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_RAW_TFR_RAW_TFR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Raw Status for IntBlock Interrupt
 *
 * \details
 * BLOCK: This interrupt is generated when the FDMA has processed one DCB
 * or when completing a general purpose operation that does not use DCBs.
 *
 * Register: \a FDMA:INTR:RAW_BLOCK
 */
#define VTSS_FDMA_INTR_RAW_BLOCK             VTSS_IOREG(VTSS_TO_DMAC,0xb2)

/** 
 * \brief
 * Raw interrupt status. Interrupt events are stored in this field before
 * masking. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt condition has occurred.
 *
 * Field: ::VTSS_FDMA_INTR_RAW_BLOCK . RAW_BLOCK
 */
#define  VTSS_F_FDMA_INTR_RAW_BLOCK_RAW_BLOCK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_RAW_BLOCK_RAW_BLOCK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_RAW_BLOCK_RAW_BLOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Raw Status for IntErr Interrupt
 *
 * \details
 * ERR: This interrupt is set if the FDMA receives an error-response on the
 * AHB interface (i.e. accessing un-mapped memory space). This condition
 * will not occur unless the FDMA has been misconfigured.
 *
 * Register: \a FDMA:INTR:RAW_ERR
 */
#define VTSS_FDMA_INTR_RAW_ERR               VTSS_IOREG(VTSS_TO_DMAC,0xb8)

/** 
 * \brief
 * Raw interrupt status. Interrupt events are stored in this field before
 * masking. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt condition has occurred.
 *
 * Field: ::VTSS_FDMA_INTR_RAW_ERR . RAW_ERR
 */
#define  VTSS_F_FDMA_INTR_RAW_ERR_RAW_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_RAW_ERR_RAW_ERR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_RAW_ERR_RAW_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Status for IntTfr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:STATUS_TFR
 */
#define VTSS_FDMA_INTR_STATUS_TFR            VTSS_IOREG(VTSS_TO_DMAC,0xba)

/** 
 * \brief
 * Interrupt status. Interrupt events are stored in this field after
 * masking. If an interrupt is no masked, it will propagate to this field.
 * Each bit in this field corresponds to a channel in the FDMA, i.e. bit 0
 * correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUS_TFR . STATUS_TFR
 */
#define  VTSS_F_FDMA_INTR_STATUS_TFR_STATUS_TFR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_STATUS_TFR_STATUS_TFR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_STATUS_TFR_STATUS_TFR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Status for IntBlock Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:STATUS_BLOCK
 */
#define VTSS_FDMA_INTR_STATUS_BLOCK          VTSS_IOREG(VTSS_TO_DMAC,0xbc)

/** 
 * \brief
 * Interrupt status. Interrupt events are stored in this field after
 * masking. If an interrupt is no masked, it will propagate to this field.
 * Each bit in this field corresponds to a channel in the FDMA, i.e. bit 0
 * correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUS_BLOCK . STATUS_BLOCK
 */
#define  VTSS_F_FDMA_INTR_STATUS_BLOCK_STATUS_BLOCK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_STATUS_BLOCK_STATUS_BLOCK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_STATUS_BLOCK_STATUS_BLOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Status for IntErr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:STATUS_ERR
 */
#define VTSS_FDMA_INTR_STATUS_ERR            VTSS_IOREG(VTSS_TO_DMAC,0xc2)

/** 
 * \brief
 * Interrupt status. Interrupt events are stored in this field after
 * masking. If an interrupt is no masked, it will propagate to this field.
 * Each bit in this field corresponds to a channel in the FDMA, i.e. bit 0
 * correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No interrupt has occurred.
 * 1 : Interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUS_ERR . STATUS_ERR
 */
#define  VTSS_F_FDMA_INTR_STATUS_ERR_STATUS_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_STATUS_ERR_STATUS_ERR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_STATUS_ERR_STATUS_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Mask for IntTfr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:MASK_TFR
 */
#define VTSS_FDMA_INTR_MASK_TFR              VTSS_IOREG(VTSS_TO_DMAC,0xc4)

/** 
 * \brief
 * Interrupt mask write enable. In order to write the INT_MASK_TFR field,
 * the corresponding bit in this field must also be set, i.e. to write bit
 * 3 in INT_MASK_TFR bit 3 in this field must also be set at the same time
 * (during the same register write operation).
 *
 * \details 
 * 0 : Writing is disabled.
 * 1 : Writing is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_TFR . INT_MASK_WE_TFR
 */
#define  VTSS_F_FDMA_INTR_MASK_TFR_INT_MASK_WE_TFR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_INTR_MASK_TFR_INT_MASK_WE_TFR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_INTR_MASK_TFR_INT_MASK_WE_TFR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Interrupt mask. Setting a bit in this field enables the corresponding
 * interrupt to propagate from RAW_TFT to STATUS_TFR and thus activate
 * interrupt. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 * In order to write this field the corresponding bit must be set in
 * INT_MASK_WE_TFR.
 *
 * \details 
 * 0 : Interrupt is disabled.
 * 1 : Interrupt is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_TFR . INT_MASK_TFR
 */
#define  VTSS_F_FDMA_INTR_MASK_TFR_INT_MASK_TFR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_MASK_TFR_INT_MASK_TFR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_MASK_TFR_INT_MASK_TFR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Mask for IntBlock Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:MASK_BLOCK
 */
#define VTSS_FDMA_INTR_MASK_BLOCK            VTSS_IOREG(VTSS_TO_DMAC,0xc6)

/** 
 * \brief
 * Interrupt mask write enable. In order to write the INT_MASK_BLOCK field,
 * the corresponding bit in this field must also be set, i.e. to write bit
 * 3 in INT_MASK_BLOCK bit 3 in this field must also be set at the same
 * time (during the same register write operation).
 *
 * \details 
 * 0 : Writing is disabled.
 * 1 : Writing is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_BLOCK . INT_MASK_WE_BLOCK
 */
#define  VTSS_F_FDMA_INTR_MASK_BLOCK_INT_MASK_WE_BLOCK(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_INTR_MASK_BLOCK_INT_MASK_WE_BLOCK     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_INTR_MASK_BLOCK_INT_MASK_WE_BLOCK(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Interrupt mask. Setting a bit in this field enables the corresponding
 * interrupt to propagate from RAW_BLOCK to STATUS_BLOCK and thus activate
 * interrupt. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 * In order to write this field the corresponding bit must be set in
 * INT_MASK_WE_BLOCK.
 *
 * \details 
 * 0 : Interrupt is disabled.
 * 1 : Interrupt is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_BLOCK . INT_MASK_BLOCK
 */
#define  VTSS_F_FDMA_INTR_MASK_BLOCK_INT_MASK_BLOCK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_MASK_BLOCK_INT_MASK_BLOCK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_MASK_BLOCK_INT_MASK_BLOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Mask for IntErr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:MASK_ERR
 */
#define VTSS_FDMA_INTR_MASK_ERR              VTSS_IOREG(VTSS_TO_DMAC,0xcc)

/** 
 * \brief
 * Interrupt mask write enable. In order to write the INT_MASK_ERR field,
 * the corresponding bit in this field must also be set, i.e. to write bit
 * 3 in INT_MASK_ERR bit 3 in this field must also be set at the same time
 * (during the same register write operation).
 *
 * \details 
 * 0 : Writing is disabled.
 * 1 : Writing is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_ERR . INT_MASK_WE_ERR
 */
#define  VTSS_F_FDMA_INTR_MASK_ERR_INT_MASK_WE_ERR(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_INTR_MASK_ERR_INT_MASK_WE_ERR     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_INTR_MASK_ERR_INT_MASK_WE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Interrupt mask. Setting a bit in this field enables the corresponding
 * interrupt to propagate from RAW_ERR to STATUS_ERR and thus activate
 * interrupt. Each bit in this field corresponds to a channel in the FDMA,
 * i.e. bit 0 correspond to channel 0, and so on.
 * In order to write this field the corresponding bit must be set in
 * INT_MASK_WE_ERR.
 *
 * \details 
 * 0 : Interrupt is disabled.
 * 1 : Interrupt is enabled.
 *
 * Field: ::VTSS_FDMA_INTR_MASK_ERR . INT_MASK_ERR
 */
#define  VTSS_F_FDMA_INTR_MASK_ERR_INT_MASK_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_MASK_ERR_INT_MASK_ERR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_MASK_ERR_INT_MASK_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Clear for IntTfr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:CLEAR_TFR
 */
#define VTSS_FDMA_INTR_CLEAR_TFR             VTSS_IOREG(VTSS_TO_DMAC,0xce)

/** 
 * \brief
 * Interrupt clear. Setting this field clears interrupt indications from
 * the RAW_TFR and STATUS_TFR registers. Each bit in this field corresponds
 * to a channel in the FDMA, i.e. bit 0 correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No effect.
 * 1 : Clear interrupt indication.
 *
 * Field: ::VTSS_FDMA_INTR_CLEAR_TFR . CLEAR_TFR
 */
#define  VTSS_F_FDMA_INTR_CLEAR_TFR_CLEAR_TFR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_CLEAR_TFR_CLEAR_TFR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_CLEAR_TFR_CLEAR_TFR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Clear for IntBlock Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:CLEAR_BLOCK
 */
#define VTSS_FDMA_INTR_CLEAR_BLOCK           VTSS_IOREG(VTSS_TO_DMAC,0xd0)

/** 
 * \brief
 * Interrupt clear. Setting this field clears interrupt indications from
 * the RAW_BLOCK and STATUS_BLOCK registers. Each bit in this field
 * corresponds to a channel in the FDMA, i.e. bit 0 correspond to channel
 * 0, and so on.
 *
 * \details 
 * 0 : No effect.
 * 1 : Clear interrupt indication.
 *
 * Field: ::VTSS_FDMA_INTR_CLEAR_BLOCK . CLEAR_BLOCK
 */
#define  VTSS_F_FDMA_INTR_CLEAR_BLOCK_CLEAR_BLOCK(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_CLEAR_BLOCK_CLEAR_BLOCK     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_CLEAR_BLOCK_CLEAR_BLOCK(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Clear for IntErr Interrupt
 *
 * \details
 * Register: \a FDMA:INTR:CLEAR_ERR
 */
#define VTSS_FDMA_INTR_CLEAR_ERR             VTSS_IOREG(VTSS_TO_DMAC,0xd6)

/** 
 * \brief
 * Interrupt clear. Setting this field clears interrupt indications from
 * the RAW_ERR and STATUS_ERR registers. Each bit in this field corresponds
 * to a channel in the FDMA, i.e. bit 0 correspond to channel 0, and so on.
 *
 * \details 
 * 0 : No effect.
 * 1 : Clear interrupt indication.
 *
 * Field: ::VTSS_FDMA_INTR_CLEAR_ERR . CLEAR_ERR
 */
#define  VTSS_F_FDMA_INTR_CLEAR_ERR_CLEAR_ERR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_INTR_CLEAR_ERR_CLEAR_ERR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_INTR_CLEAR_ERR_CLEAR_ERR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Status for each interrupt type
 *
 * \details
 * Register: \a FDMA:INTR:STATUSINT
 */
#define VTSS_FDMA_INTR_STATUSINT             VTSS_IOREG(VTSS_TO_DMAC,0xd8)

/** 
 * \brief
 * This field is set if any of the STATUS_ERR.STATUS_ERR interrupts are
 * active.
 *
 * \details 
 * 0 : No ERR interrupts are active.
 * 1 : At least one ERR interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUSINT . ERR
 */
#define  VTSS_F_FDMA_INTR_STATUSINT_ERR       VTSS_BIT(4)

/** 
 * \brief
 * This field is set if any of the STATUS_BLOCK.STATUS_BLOCK interrupts are
 * active.
 *
 * \details 
 * 0 : No BLOCK interrupts are active.
 * 1 : At least one BLOCK interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUSINT . BLOCK
 */
#define  VTSS_F_FDMA_INTR_STATUSINT_BLOCK     VTSS_BIT(1)

/** 
 * \brief
 * This field is set if any of the STATUS_TFR.STATUS_TFR interrupts are
 * active.
 *
 * \details 
 * 0 : No TFR interrupts are active.
 * 1 : At least one TFR interrupt is active.
 *
 * Field: ::VTSS_FDMA_INTR_STATUSINT . TFR
 */
#define  VTSS_F_FDMA_INTR_STATUSINT_TFR       VTSS_BIT(0)

/**
 * Register Group: \a FDMA:HS
 *
 * Handshaking Registers
 */


/** 
 * \brief Source Software Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:REQ_SRC_REG
 */
#define VTSS_FDMA_HS_REQ_SRC_REG             VTSS_IOREG(VTSS_TO_DMAC,0xda)

/** 
 * \brief
 * Source request write enable

 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_REQ_SRC_REG . SRC_REQ_WE
 */
#define  VTSS_F_FDMA_HS_REQ_SRC_REG_SRC_REQ_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_REQ_SRC_REG_SRC_REQ_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_REQ_SRC_REG_SRC_REQ_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Source request
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_REQ_SRC_REG . SRC_REQ
 */
#define  VTSS_F_FDMA_HS_REQ_SRC_REG_SRC_REQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_REQ_SRC_REG_SRC_REQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_REQ_SRC_REG_SRC_REQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Destination Software Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:REQ_DST_REG
 */
#define VTSS_FDMA_HS_REQ_DST_REG             VTSS_IOREG(VTSS_TO_DMAC,0xdc)

/** 
 * \brief
 * Destination request write enable

 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_REQ_DST_REG . DST_REQ_WE
 */
#define  VTSS_F_FDMA_HS_REQ_DST_REG_DST_REQ_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_REQ_DST_REG_DST_REQ_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_REQ_DST_REG_DST_REQ_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Destination request
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_REQ_DST_REG . DST_REQ
 */
#define  VTSS_F_FDMA_HS_REQ_DST_REG_DST_REQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_REQ_DST_REG_DST_REQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_REQ_DST_REG_DST_REQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Single Source Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:SGL_REQ_SRC_REG
 */
#define VTSS_FDMA_HS_SGL_REQ_SRC_REG         VTSS_IOREG(VTSS_TO_DMAC,0xde)

/** 
 * \brief
 * Single write enable

 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_SGL_REQ_SRC_REG . SRC_SGLREQ_WE
 */
#define  VTSS_F_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Source single request
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_SGL_REQ_SRC_REG . SRC_SGLREQ
 */
#define  VTSS_F_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_SGL_REQ_SRC_REG_SRC_SGLREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Single Destination Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:SGL_REQ_DST_REG
 */
#define VTSS_FDMA_HS_SGL_REQ_DST_REG         VTSS_IOREG(VTSS_TO_DMAC,0xe0)

/** 
 * \brief
 * Destination write enable
 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_SGL_REQ_DST_REG . DST_SGLREQ_WE
 */
#define  VTSS_F_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Destination single or burst request
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_SGL_REQ_DST_REG . DST_SGLREQ
 */
#define  VTSS_F_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_SGL_REQ_DST_REG_DST_SGLREQ(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Last Source Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:LST_SRC_REG
 */
#define VTSS_FDMA_HS_LST_SRC_REG             VTSS_IOREG(VTSS_TO_DMAC,0xe2)

/** 
 * \brief
 * Source last transaction request write enable
 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_LST_SRC_REG . LSTSRC_WE
 */
#define  VTSS_F_FDMA_HS_LST_SRC_REG_LSTSRC_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_LST_SRC_REG_LSTSRC_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_LST_SRC_REG_LSTSRC_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Source last transaction request
 * 0 = Not last transaction in current block
 * 1 = Last transaction in current block
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_LST_SRC_REG . LSTSRC
 */
#define  VTSS_F_FDMA_HS_LST_SRC_REG_LSTSRC(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_LST_SRC_REG_LSTSRC     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_LST_SRC_REG_LSTSRC(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Last Destination Transaction Request Register
 *
 * \details
 * Register: \a FDMA:HS:LST_DST_REG
 */
#define VTSS_FDMA_HS_LST_DST_REG             VTSS_IOREG(VTSS_TO_DMAC,0xe4)

/** 
 * \brief
 * Destination last transaction request write enable
 *
 * \details 
 * 0: Write disabled
 * 1: Write enabled
 *
 * Field: ::VTSS_FDMA_HS_LST_DST_REG . LSTDST_WE
 */
#define  VTSS_F_FDMA_HS_LST_DST_REG_LSTDST_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_HS_LST_DST_REG_LSTDST_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_HS_LST_DST_REG_LSTDST_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Destination last transaction request
 * 0 = Not last transaction in current block
 * 1 = Last transaction in current block
 *
 * \details 
 * Field: ::VTSS_FDMA_HS_LST_DST_REG . LSTDST
 */
#define  VTSS_F_FDMA_HS_LST_DST_REG_LSTDST(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_HS_LST_DST_REG_LSTDST     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_HS_LST_DST_REG_LSTDST(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a FDMA:MISC
 *
 * Miscellaneous FDMA Registers
 */


/** 
 * \brief DMA Enable
 *
 * \details
 * Register: \a FDMA:MISC:DMA_CFG_REG
 */
#define VTSS_FDMA_MISC_DMA_CFG_REG           VTSS_IOREG(VTSS_TO_DMAC,0xe6)

/** 
 * \brief
 * DMA enable bit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_FDMA_MISC_DMA_CFG_REG . DMA_EN
 */
#define  VTSS_F_FDMA_MISC_DMA_CFG_REG_DMA_EN  VTSS_BIT(0)


/** 
 * \brief DMA Channel Enable
 *
 * \details
 * Register: \a FDMA:MISC:CH_EN_REG
 */
#define VTSS_FDMA_MISC_CH_EN_REG             VTSS_IOREG(VTSS_TO_DMAC,0xe8)

/** 
 * \brief
 * Channel enable write enable
 *
 * \details 
 * Field: ::VTSS_FDMA_MISC_CH_EN_REG . CH_EN_WE
 */
#define  VTSS_F_FDMA_MISC_CH_EN_REG_CH_EN_WE(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_FDMA_MISC_CH_EN_REG_CH_EN_WE     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_FDMA_MISC_CH_EN_REG_CH_EN_WE(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Enables or disables the channel. Setting this bit enables a channel;
 * clearing this bit disables the channel.
 * The bit is automatically cleared by hardware to disable the channel
 * after the last DMA transfer to the destination has completed. Software
 * can therefore poll this bit to determine when this channel is free for a
 * new DMA transfer.
 *
 * \details 
 * 0: Disable the channel
 * 1: Enable the channel

 *
 * Field: ::VTSS_FDMA_MISC_CH_EN_REG . CH_EN
 */
#define  VTSS_F_FDMA_MISC_CH_EN_REG_CH_EN(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_FDMA_MISC_CH_EN_REG_CH_EN     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_FDMA_MISC_CH_EN_REG_CH_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief DMA Version
 *
 * \details
 * Register: \a FDMA:MISC:DMA_COMP_VERSION
 */
#define VTSS_FDMA_MISC_DMA_COMP_VERSION      VTSS_IOREG(VTSS_TO_DMAC,0xff)


#endif /* _VTSS_LUTON26_REGS_FDMA_H_ */
