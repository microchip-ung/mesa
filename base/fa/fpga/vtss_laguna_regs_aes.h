/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#ifndef _VTSS_LAGUNA_REGS_AES_H_
#define _VTSS_LAGUNA_REGS_AES_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a AES
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a AES:AES_REGS
 *
 * Advanced Encryption Standard (AES) User Interface
 */


/**
 * \brief AES Control Register
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPCREN bit is cleared in the
 * AES Write Protection Mode Register.

 *
 * Register: \a AES:AES_REGS:AES_CR
 */
#define VTSS_AES_AES_CR                      VTSS_IOREG(VTSS_TO_AES,0x0)

/**
 * \brief
 * UNLOCK: Unlock Processing0: No effect.1: Unlocks the processing in case
 * of abnormal event detection if AES_WPMR.ACTION > 0.AES_WPSR must be
 * cleared before performing the unlock command.
 *
 * \details
 * Field: ::VTSS_AES_AES_CR . UNLOCK
 */
#define  VTSS_F_AES_AES_CR_UNLOCK(x)          VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_AES_AES_CR_UNLOCK             VTSS_BIT(24)
#define  VTSS_X_AES_AES_CR_UNLOCK(x)          VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * LOADSEED: Random Number Generator Seed Loading0: No effect.1: Restarts
 * the countermeasures generator to an internal predefined value.
 *
 * \details
 * Field: ::VTSS_AES_AES_CR . LOADSEED
 */
#define  VTSS_F_AES_AES_CR_LOADSEED(x)        VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AES_AES_CR_LOADSEED           VTSS_BIT(16)
#define  VTSS_X_AES_AES_CR_LOADSEED(x)        VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * SWRST: Software Reset0: No effect.1: Resets the AES. A
 * software-triggered hardware reset of the AES interface is performed.
 *
 * \details
 * Field: ::VTSS_AES_AES_CR . SWRST
 */
#define  VTSS_F_AES_AES_CR_SWRST(x)           VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_AES_AES_CR_SWRST              VTSS_BIT(8)
#define  VTSS_X_AES_AES_CR_SWRST(x)           VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * KSWP: Key Swap0: No effect.1: Activates the set of key registers defined
 * by AES_EMR.PKRS.
 *
 * \details
 * Field: ::VTSS_AES_AES_CR . KSWP
 */
#define  VTSS_F_AES_AES_CR_KSWP(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AES_AES_CR_KSWP               VTSS_BIT(1)
#define  VTSS_X_AES_AES_CR_KSWP(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * START: Start Processing0: No effect.1: Starts manual
 * encryption/decryption process.
 *
 * \details
 * Field: ::VTSS_AES_AES_CR . START
 */
#define  VTSS_F_AES_AES_CR_START(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_CR_START              VTSS_BIT(0)
#define  VTSS_X_AES_AES_CR_START(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Mode Register
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Notes: 1. All the countermeasures are enabled by default.
 * 2. CMTYPx bits are write-only and can only be modified if the CKEY field
 * is correctly configured.
 *
 * Register: \a AES:AES_REGS:AES_MR
 */
#define VTSS_AES_AES_MR                      VTSS_IOREG(VTSS_TO_AES,0x1)

/**
 * \brief
 * TAMPCLR: Tamper Clear Enable0: A tamper detection event has no effect on
 * the AES_KEYWRx key.1: A tamper detection event immediately clears the
 * AES_KEYWRx key
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . TAMPCLR
 */
#define  VTSS_F_AES_AES_MR_TAMPCLR(x)         VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_AES_AES_MR_TAMPCLR            VTSS_BIT(31)
#define  VTSS_X_AES_AES_MR_TAMPCLR(x)         VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * CMTYP7: Countermeasure Type 70 (NO_STARTDELAY): Countermeasure type 7 is
 * disabled.1 (STARTDELAY): Countermeasure type 7 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP7
 */
#define  VTSS_F_AES_AES_MR_CMTYP7(x)          VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_AES_AES_MR_CMTYP7             VTSS_BIT(30)
#define  VTSS_X_AES_AES_MR_CMTYP7(x)          VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * CMTYP6: Countermeasure Type 60 (NO_IDLECURRENT): Countermeasure type 6
 * is disabled.1 (IDLECURRENT): Countermeasure type 6 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP6
 */
#define  VTSS_F_AES_AES_MR_CMTYP6(x)          VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_AES_AES_MR_CMTYP6             VTSS_BIT(29)
#define  VTSS_X_AES_AES_MR_CMTYP6(x)          VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * CMTYP5: Countermeasure Type 50 (NO_ADDACCESS): Countermeasure type 5 is
 * disabled.1 (ADDACCESS): Countermeasure type 5 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP5
 */
#define  VTSS_F_AES_AES_MR_CMTYP5(x)          VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_AES_AES_MR_CMTYP5             VTSS_BIT(28)
#define  VTSS_X_AES_AES_MR_CMTYP5(x)          VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * CMTYP4: Countermeasure Type 40 (NO_RESTART): Countermeasure type 4 is
 * disabled.1 (RESTART): Countermeasure type 4 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP4
 */
#define  VTSS_F_AES_AES_MR_CMTYP4(x)          VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_AES_AES_MR_CMTYP4             VTSS_BIT(27)
#define  VTSS_X_AES_AES_MR_CMTYP4(x)          VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CMTYP3: Countermeasure Type 30 (NO_DUMMY): Countermeasure type 3 is
 * disabled.1 (DUMMY): Countermeasure type 3 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP3
 */
#define  VTSS_F_AES_AES_MR_CMTYP3(x)          VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_AES_AES_MR_CMTYP3             VTSS_BIT(26)
#define  VTSS_X_AES_AES_MR_CMTYP3(x)          VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * CMTYP2: Countermeasure Type 20 (NO_PAUSE): Countermeasure type 2 is
 * disabled.1 (PAUSE): Countermeasure type 2 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP2
 */
#define  VTSS_F_AES_AES_MR_CMTYP2(x)          VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_AES_AES_MR_CMTYP2             VTSS_BIT(25)
#define  VTSS_X_AES_AES_MR_CMTYP2(x)          VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * CMTYP1: Countermeasure Type 10 (NOPROT_EXTKEY): Countermeasure type 1 is
 * disabled.1 (PROT_EXTKEY): Countermeasure type 1 is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CMTYP1
 */
#define  VTSS_F_AES_AES_MR_CMTYP1(x)          VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_AES_AES_MR_CMTYP1             VTSS_BIT(24)
#define  VTSS_X_AES_AES_MR_CMTYP1(x)          VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CKEY: Countermeasure KeyValue    Name	  Description0xE
 * PASSWD    This field must be written
 * with 0xE to allow CMTYPx bit configuration changes. Any other values
 * will abort the write operation				  in CMTYPx
 * bits.				  Always reads as 0.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CKEY
 */
#define  VTSS_F_AES_AES_MR_CKEY(x)            VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_AES_AES_MR_CKEY               VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_AES_AES_MR_CKEY(x)            VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * CFBS: Cipher Feedback Data SizeValue   Name		      Description0
 *	   SIZE_128BIT	  128-bit1	    SIZE_64BIT	     64-bit2
 *   SIZE_32BIT       32-bit3	       SIZE_16BIT	16-bit4
 * SIZE_8BIT	     8-bit
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CFBS
 */
#define  VTSS_F_AES_AES_MR_CFBS(x)            VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_AES_AES_MR_CFBS               VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_AES_AES_MR_CFBS(x)            VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * LOD: Last Output Data Mode0: No effect.After each end of
 * encryption/decryption, the output data are available either on the
 * output data registers (Manual and Automodes) or at the address specified
 * in the Receive Pointer Register (AES_RPR) for PDCChannel Buffer Transfer
 * Descriptorfor DMA mode.In Manual and Auto modes, the DATRDY flag is
 * cleared when at least one of the Output Data registers is read.1: The
 * DATRDY flag is cleared when at least one of the Input Data Registers is
 * written.No more Output Data Register reads is necessary between
 * consecutive encryptions/decryptions (see Section 5.5 LastOutput Data
 * Mode (CBC-MAC)).Warning: In DMAPDC mode, reading to the Output Data
 * registers before the last data encryption/decryption process maylead to
 * unpredictable results.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . LOD
 */
#define  VTSS_F_AES_AES_MR_LOD(x)             VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_AES_AES_MR_LOD                VTSS_BIT(15)
#define  VTSS_X_AES_AES_MR_LOD(x)             VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * OPMOD: Operating ModeValue	 Name	       Description0	      ECB
 *	    ECB: Electronic Codebook mode1	     CBC	    CBC:
 * Cipher Block Chaining mode2		 OFB		OFB: Output
 * Feedback mode3	    CFB 	   CFB: Cipher Feedback mode4
 *     CTR	      CTR: Counter mode (16-bit internal counter)5
 *  GCM 	  GCM: Galois/Counter mode6	      XTS	     XTS:
 * XEX-based tweaked-codebook modeFor CBC-MAC operating mode, set OPMOD to
 * CBC and LOD to 1
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . OPMOD
 */
#define  VTSS_F_AES_AES_MR_OPMOD(x)           VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_AES_AES_MR_OPMOD              VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_AES_AES_MR_OPMOD(x)           VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * KEYSIZE: Key SizeValue   Name		Description0
 * AES128 AES	 Key Size is 128 bits1		AES192 AES    Key Size is
 * 192 bits2	      AES256 AES    Key Size is 256 bits
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . KEYSIZE
 */
#define  VTSS_F_AES_AES_MR_KEYSIZE(x)         VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_AES_AES_MR_KEYSIZE            VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_AES_AES_MR_KEYSIZE(x)         VTSS_EXTRACT_BITFIELD(x,10,2)

/**
 * \brief
 * SMOD: Start ModeValue  Name			     Description0
 * MANUAL_START    Manual Mode1 	AUTO_START	   Auto Mode2
 *   IDATAR0_START    AES_IDATAR0 access only Auto Mode (DMAPDC)If a
 * DMA/PDC transfer is used, configure SMOD to 2. See Section 5.4.3 PDC
 * Mode, Section 5.4.4 DMA Mode for moredetails.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . SMOD
 */
#define  VTSS_F_AES_AES_MR_SMOD(x)            VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_AES_AES_MR_SMOD               VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_AES_AES_MR_SMOD(x)            VTSS_EXTRACT_BITFIELD(x,8,2)

/**
 * \brief
 * PROCDLY: Processing DelayProcessing Time = N x (PROCDLY + 1)whereN = 10
 * when KEYSIZE = 0N = 12 when KEYSIZE = 1N = 14 when KEYSIZE = 2The
 * processing time represents the number of clock cycles that the AES needs
 * in order to perform one encryption/decryptionwith no countermeasures
 * activated.Note: The best performance is achieved with PROCDLY equal to
 * 0.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . PROCDLY
 */
#define  VTSS_F_AES_AES_MR_PROCDLY(x)         VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_AES_AES_MR_PROCDLY            VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_AES_AES_MR_PROCDLY(x)         VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * DUALBUFF: Dual Input BufferValue   Name		Description0
 *   INACTIVE	    AES_IDATARx cannot be written during processing of
 * previous block.1	     ACTIVE	      AES_IDATARx can be written
 * during processing of previous block when SMOD = 2. It speeds up
 *			     the overall runtime of large files.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . DUALBUFF
 */
#define  VTSS_F_AES_AES_MR_DUALBUFF(x)        VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_AES_AES_MR_DUALBUFF           VTSS_BIT(3)
#define  VTSS_X_AES_AES_MR_DUALBUFF(x)        VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * GTAGEN: GCM Automatic Tag Generation Enable0: Automatic GCM Tag
 * generation disabled.1: Automatic GCM Tag generation enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . GTAGEN
 */
#define  VTSS_F_AES_AES_MR_GTAGEN(x)          VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AES_AES_MR_GTAGEN             VTSS_BIT(1)
#define  VTSS_X_AES_AES_MR_GTAGEN(x)          VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CIPHER: Processing Mode0: Decrypts data.1: Encrypts data.
 *
 * \details
 * Field: ::VTSS_AES_AES_MR . CIPHER
 */
#define  VTSS_F_AES_AES_MR_CIPHER(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_MR_CIPHER             VTSS_BIT(0)
#define  VTSS_X_AES_AES_MR_CIPHER(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Interrupt Enable Register
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPITEN bit is cleared in the
 * AES Write Protection Mode Register.
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Enables the corresponding interrupt.
 *
 * Register: \a AES:AES_REGS:AES_IER
 */
#define VTSS_AES_AES_IER                     VTSS_IOREG(VTSS_TO_AES,0x4)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . SECE
 */
#define  VTSS_F_AES_AES_IER_SECE(x)           VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_AES_AES_IER_SECE              VTSS_BIT(19)
#define  VTSS_X_AES_AES_IER_SECE(x)           VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * PLENERR: Padding Length Error Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . PLENERR
 */
#define  VTSS_F_AES_AES_IER_PLENERR(x)        VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_AES_AES_IER_PLENERR           VTSS_BIT(18)
#define  VTSS_X_AES_AES_IER_PLENERR(x)        VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * EOPAD: End of Padding Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . EOPAD
 */
#define  VTSS_F_AES_AES_IER_EOPAD(x)          VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_AES_AES_IER_EOPAD             VTSS_BIT(17)
#define  VTSS_X_AES_AES_IER_EOPAD(x)          VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * TAGRDY: GCM Tag Ready Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . TAGRDY
 */
#define  VTSS_F_AES_AES_IER_TAGRDY(x)         VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AES_AES_IER_TAGRDY            VTSS_BIT(16)
#define  VTSS_X_AES_AES_IER_TAGRDY(x)         VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . URAD
 */
#define  VTSS_F_AES_AES_IER_URAD(x)           VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_AES_AES_IER_URAD              VTSS_BIT(8)
#define  VTSS_X_AES_AES_IER_URAD(x)           VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Enable
 *
 * \details
 * Field: ::VTSS_AES_AES_IER . DATRDY
 */
#define  VTSS_F_AES_AES_IER_DATRDY(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_IER_DATRDY            VTSS_BIT(0)
#define  VTSS_X_AES_AES_IER_DATRDY(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Interrupt Disable Register
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPITEN bit is cleared in the
 * AES Write Protection Mode Register.
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Register: \a AES:AES_REGS:AES_IDR
 */
#define VTSS_AES_AES_IDR                     VTSS_IOREG(VTSS_TO_AES,0x5)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . SECE_IDR
 */
#define  VTSS_F_AES_AES_IDR_SECE_IDR(x)       VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_AES_AES_IDR_SECE_IDR          VTSS_BIT(19)
#define  VTSS_X_AES_AES_IDR_SECE_IDR(x)       VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * PLENERR: Padding Length Error Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . PLENERR_IDR
 */
#define  VTSS_F_AES_AES_IDR_PLENERR_IDR(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_AES_AES_IDR_PLENERR_IDR       VTSS_BIT(18)
#define  VTSS_X_AES_AES_IDR_PLENERR_IDR(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * EOPAD: End of Padding Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . EOPAD_IDR
 */
#define  VTSS_F_AES_AES_IDR_EOPAD_IDR(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_AES_AES_IDR_EOPAD_IDR         VTSS_BIT(17)
#define  VTSS_X_AES_AES_IDR_EOPAD_IDR(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * TAGRDY: GCM Tag Ready Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . TAGRDY_IDR
 */
#define  VTSS_F_AES_AES_IDR_TAGRDY_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AES_AES_IDR_TAGRDY_IDR        VTSS_BIT(16)
#define  VTSS_X_AES_AES_IDR_TAGRDY_IDR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . URAD_IDR
 */
#define  VTSS_F_AES_AES_IDR_URAD_IDR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_AES_AES_IDR_URAD_IDR          VTSS_BIT(8)
#define  VTSS_X_AES_AES_IDR_URAD_IDR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Disable
 *
 * \details
 * Field: ::VTSS_AES_AES_IDR . DATRDY_IDR
 */
#define  VTSS_F_AES_AES_IDR_DATRDY_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_IDR_DATRDY_IDR        VTSS_BIT(0)
#define  VTSS_X_AES_AES_IDR_DATRDY_IDR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Interrupt Mask Register
 *
 * \details
 *
 * Read-only
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Register: \a AES:AES_REGS:AES_IMR
 */
#define VTSS_AES_AES_IMR                     VTSS_IOREG(VTSS_TO_AES,0x6)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . SECE_IMR
 */
#define  VTSS_F_AES_AES_IMR_SECE_IMR(x)       VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_AES_AES_IMR_SECE_IMR          VTSS_BIT(19)
#define  VTSS_X_AES_AES_IMR_SECE_IMR(x)       VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * PLENERR: Padding Length Error Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . PLENERR_IMR
 */
#define  VTSS_F_AES_AES_IMR_PLENERR_IMR(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_AES_AES_IMR_PLENERR_IMR       VTSS_BIT(18)
#define  VTSS_X_AES_AES_IMR_PLENERR_IMR(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * EOPAD: End of Padding Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . EOPAD_IMR
 */
#define  VTSS_F_AES_AES_IMR_EOPAD_IMR(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_AES_AES_IMR_EOPAD_IMR         VTSS_BIT(17)
#define  VTSS_X_AES_AES_IMR_EOPAD_IMR(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * TAGRDY: GCM Tag Ready Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . TAGRDY_IMR
 */
#define  VTSS_F_AES_AES_IMR_TAGRDY_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AES_AES_IMR_TAGRDY_IMR        VTSS_BIT(16)
#define  VTSS_X_AES_AES_IMR_TAGRDY_IMR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . URAD_IMR
 */
#define  VTSS_F_AES_AES_IMR_URAD_IMR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_AES_AES_IMR_URAD_IMR          VTSS_BIT(8)
#define  VTSS_X_AES_AES_IMR_URAD_IMR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Mask
 *
 * \details
 * Field: ::VTSS_AES_AES_IMR . DATRDY_IMR
 */
#define  VTSS_F_AES_AES_IMR_DATRDY_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_IMR_DATRDY_IMR        VTSS_BIT(0)
#define  VTSS_X_AES_AES_IMR_DATRDY_IMR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Interrupt Status Register
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_ISR
 */
#define VTSS_AES_AES_ISR                     VTSS_IOREG(VTSS_TO_AES,0x7)

/**
 * \brief
 * SECE: Security and/or Safety Event (cleared on read)0: There is no
 * security report in AES_WPSR.1: One security flag is set in AES_WPSR.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . SECE_ISR
 */
#define  VTSS_F_AES_AES_ISR_SECE_ISR(x)       VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_AES_AES_ISR_SECE_ISR          VTSS_BIT(19)
#define  VTSS_X_AES_AES_ISR_SECE_ISR(x)       VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * PLENERR: Padding Length Error0: No Padding Length Error occurred.1:
 * Padding Length Error detected.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . PLENERR_ISR
 */
#define  VTSS_F_AES_AES_ISR_PLENERR_ISR(x)    VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_AES_AES_ISR_PLENERR_ISR       VTSS_BIT(18)
#define  VTSS_X_AES_AES_ISR_PLENERR_ISR(x)    VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * EOPAD: End of Padding0: Padding is not over.1: Padding phase is over.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . EOPAD_ISR
 */
#define  VTSS_F_AES_AES_ISR_EOPAD_ISR(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_AES_AES_ISR_EOPAD_ISR         VTSS_BIT(17)
#define  VTSS_X_AES_AES_ISR_EOPAD_ISR(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * TAGRDY: GCM Tag Ready0: GCM Tag is not valid.1: GCM Tag generation is
 * complete (cleared by reading GCM Tag, starting another processing or
 * when writing a new key).
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . TAGRDY_ISR
 */
#define  VTSS_F_AES_AES_ISR_TAGRDY_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_AES_AES_ISR_TAGRDY_ISR        VTSS_BIT(16)
#define  VTSS_X_AES_AES_ISR_TAGRDY_ISR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAT: Unspecified Register Access (cleared by writing SWRST in
 * AES_CR)Value    Name 				    Description0
 *	  IDR_WR_PROCESSING	 Input Data register written during the
 * data processing when SMOD = 2 mode.1 	  ODR_RD_PROCESSING
 * Output Data register read during the data processing.2
 * MR_WR_PROCESSING	 Mode register written during the data processing.3
 *	     ODR_RD_SUBKGEN	      Output Data register read during the
 * sub-keys generation.4	   MR_WR_SUBKGEN	     Mode register
 * written during the sub-keys generation.5	      WOR_RD_ACCESS
 *	Write-only register read access.Only the last Unspecified Register
 * Access Type is available through the URAT field.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . URAT_ISR
 */
#define  VTSS_F_AES_AES_ISR_URAT_ISR(x)       VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_AES_AES_ISR_URAT_ISR          VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_AES_AES_ISR_URAT_ISR(x)       VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Status (cleared by writing
 * SWRST in AES_CR)0: No unspecified register access has been detected
 * since the last SWRST.1: At least one unspecified register access has
 * been detected since the last SWRST.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . URAD_ISR
 */
#define  VTSS_F_AES_AES_ISR_URAD_ISR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_AES_AES_ISR_URAD_ISR          VTSS_BIT(8)
#define  VTSS_X_AES_AES_ISR_URAD_ISR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready (cleared by setting bit START or bit SWRST in AES_CR
 * or by reading AES_ODATARx)0: Output data not valid.1: Encryption or
 * decryption process is completed.Note: If AES_MR.LOD = 1: In Manual and
 * Auto mode, the DATRDY flag can also be cleared by writing at least one
 * AES_IDATARx.
 *
 * \details
 * Field: ::VTSS_AES_AES_ISR . DATRDY_ISR
 */
#define  VTSS_F_AES_AES_ISR_DATRDY_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_ISR_DATRDY_ISR        VTSS_BIT(0)
#define  VTSS_X_AES_AES_ISR_DATRDY_ISR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR0
 */
#define VTSS_AES_AES_KEYWR0                  VTSS_IOREG(VTSS_TO_AES,0x8)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR0 . KEYW0
 */
#define  VTSS_F_AES_AES_KEYWR0_KEYW0(x)       (x)
#define  VTSS_M_AES_AES_KEYWR0_KEYW0          0xffffffff
#define  VTSS_X_AES_AES_KEYWR0_KEYW0(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR1
 */
#define VTSS_AES_AES_KEYWR1                  VTSS_IOREG(VTSS_TO_AES,0x9)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR1 . KEYW1
 */
#define  VTSS_F_AES_AES_KEYWR1_KEYW1(x)       (x)
#define  VTSS_M_AES_AES_KEYWR1_KEYW1          0xffffffff
#define  VTSS_X_AES_AES_KEYWR1_KEYW1(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR2
 */
#define VTSS_AES_AES_KEYWR2                  VTSS_IOREG(VTSS_TO_AES,0xa)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR2 . KEYW2
 */
#define  VTSS_F_AES_AES_KEYWR2_KEYW2(x)       (x)
#define  VTSS_M_AES_AES_KEYWR2_KEYW2          0xffffffff
#define  VTSS_X_AES_AES_KEYWR2_KEYW2(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR3
 */
#define VTSS_AES_AES_KEYWR3                  VTSS_IOREG(VTSS_TO_AES,0xb)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR3 . KEYW3
 */
#define  VTSS_F_AES_AES_KEYWR3_KEYW3(x)       (x)
#define  VTSS_M_AES_AES_KEYWR3_KEYW3          0xffffffff
#define  VTSS_X_AES_AES_KEYWR3_KEYW3(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR4
 */
#define VTSS_AES_AES_KEYWR4                  VTSS_IOREG(VTSS_TO_AES,0xc)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR4 . KEYW4
 */
#define  VTSS_F_AES_AES_KEYWR4_KEYW4(x)       (x)
#define  VTSS_M_AES_AES_KEYWR4_KEYW4          0xffffffff
#define  VTSS_X_AES_AES_KEYWR4_KEYW4(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR5
 */
#define VTSS_AES_AES_KEYWR5                  VTSS_IOREG(VTSS_TO_AES,0xd)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR5 . KEYW5
 */
#define  VTSS_F_AES_AES_KEYWR5_KEYW5(x)       (x)
#define  VTSS_M_AES_AES_KEYWR5_KEYW5          0xffffffff
#define  VTSS_X_AES_AES_KEYWR5_KEYW5(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR6
 */
#define VTSS_AES_AES_KEYWR6                  VTSS_IOREG(VTSS_TO_AES,0xe)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR6 . KEYW6
 */
#define  VTSS_F_AES_AES_KEYWR6_KEYW6(x)       (x)
#define  VTSS_M_AES_AES_KEYWR6_KEYW6          0xffffffff
#define  VTSS_X_AES_AES_KEYWR6_KEYW6(x)       (x)


/**
 * \brief AES Key Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_KEYWR7
 */
#define VTSS_AES_AES_KEYWR7                  VTSS_IOREG(VTSS_TO_AES,0xf)

/**
 * \brief
 * KEYW: Key WordThe four/six/eight 32-bit Key Word registers set the
 * 128-bit/192-bit/256-bit cryptographic key used for
 * AESencryption/decryption.AES_KEYWR0 corresponds to the first word of the
 * key and respectively AES_KEYWR3/AES_KEYWR5/AES_KEYWR7 tothe last
 * one.Whenever a new key (AES_KEYWRx) is written to the hardware, two
 * automatic actions are processed:- GCM hash subkey generation-
 * AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic Hash Subkey
 * Calculation for details.These registers are write-only to prevent the
 * key from being read by another application.Note: 1. AES_KEYWRx registers
 * are not used if the private key internal registers are selected
 * (AES_EMR.PKRS=1).
 *
 * \details
 * Field: ::VTSS_AES_AES_KEYWR7 . KEYW7
 */
#define  VTSS_F_AES_AES_KEYWR7_KEYW7(x)       (x)
#define  VTSS_M_AES_AES_KEYWR7_KEYW7          0xffffffff
#define  VTSS_X_AES_AES_KEYWR7_KEYW7(x)       (x)


/**
 * \brief AES Input Data Register 0
 *
 * \details
 * Write-only
 *
 * Register: \a AES:AES_REGS:AES_IDATAR0
 */
#define VTSS_AES_AES_IDATAR0                 VTSS_IOREG(VTSS_TO_AES,0x10)

/**
 * \brief
 * IDATA: Input Data WordThe four 32-bit Input Data registers set the
 * 128-bit data block used for encryption/decryption.AES_IDATAR0
 * corresponds to the first word of the data to be encrypted/decrypted, and
 * AES_IDATAR3 to the last one.These registers are write-only to prevent
 * the input data from being read by another application.
 *
 * \details
 * Field: ::VTSS_AES_AES_IDATAR0 . IDATA0
 */
#define  VTSS_F_AES_AES_IDATAR0_IDATA0(x)     (x)
#define  VTSS_M_AES_AES_IDATAR0_IDATA0        0xffffffff
#define  VTSS_X_AES_AES_IDATAR0_IDATA0(x)     (x)


/**
 * \brief AES Input Data Register 0
 *
 * \details
 * Write-only
 *
 * Register: \a AES:AES_REGS:AES_IDATAR1
 */
#define VTSS_AES_AES_IDATAR1                 VTSS_IOREG(VTSS_TO_AES,0x11)

/**
 * \brief
 * IDATA: Input Data WordThe four 32-bit Input Data registers set the
 * 128-bit data block used for encryption/decryption.AES_IDATAR0
 * corresponds to the first word of the data to be encrypted/decrypted, and
 * AES_IDATAR3 to the last one.These registers are write-only to prevent
 * the input data from being read by another application.
 *
 * \details
 * Field: ::VTSS_AES_AES_IDATAR1 . IDATA1
 */
#define  VTSS_F_AES_AES_IDATAR1_IDATA1(x)     (x)
#define  VTSS_M_AES_AES_IDATAR1_IDATA1        0xffffffff
#define  VTSS_X_AES_AES_IDATAR1_IDATA1(x)     (x)


/**
 * \brief AES Input Data Register 0
 *
 * \details
 * Write-only
 *
 * Register: \a AES:AES_REGS:AES_IDATAR2
 */
#define VTSS_AES_AES_IDATAR2                 VTSS_IOREG(VTSS_TO_AES,0x12)

/**
 * \brief
 * IDATA: Input Data WordThe four 32-bit Input Data registers set the
 * 128-bit data block used for encryption/decryption.AES_IDATAR0
 * corresponds to the first word of the data to be encrypted/decrypted, and
 * AES_IDATAR3 to the last one.These registers are write-only to prevent
 * the input data from being read by another application.
 *
 * \details
 * Field: ::VTSS_AES_AES_IDATAR2 . IDATA2
 */
#define  VTSS_F_AES_AES_IDATAR2_IDATA2(x)     (x)
#define  VTSS_M_AES_AES_IDATAR2_IDATA2        0xffffffff
#define  VTSS_X_AES_AES_IDATAR2_IDATA2(x)     (x)


/**
 * \brief AES Input Data Register 0
 *
 * \details
 * Write-only
 *
 * Register: \a AES:AES_REGS:AES_IDATAR3
 */
#define VTSS_AES_AES_IDATAR3                 VTSS_IOREG(VTSS_TO_AES,0x13)

/**
 * \brief
 * IDATA: Input Data WordThe four 32-bit Input Data registers set the
 * 128-bit data block used for encryption/decryption.AES_IDATAR0
 * corresponds to the first word of the data to be encrypted/decrypted, and
 * AES_IDATAR3 to the last one.These registers are write-only to prevent
 * the input data from being read by another application.
 *
 * \details
 * Field: ::VTSS_AES_AES_IDATAR3 . IDATA3
 */
#define  VTSS_F_AES_AES_IDATAR3_IDATA3(x)     (x)
#define  VTSS_M_AES_AES_IDATAR3_IDATA3        0xffffffff
#define  VTSS_X_AES_AES_IDATAR3_IDATA3(x)     (x)


/**
 * \brief AES Output Data Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_ODATAR0
 */
#define VTSS_AES_AES_ODATAR0                 VTSS_IOREG(VTSS_TO_AES,0x14)

/**
 * \brief
 * ODATA: Output DataThe four 32-bit Output Data registers contain the
 * 128-bit data block that has been encrypted/decrypted.AES_ODATAR0
 * corresponds to the first word, AES_ODATAR3 to the last one.
 *
 * \details
 * Field: ::VTSS_AES_AES_ODATAR0 . ODATA0
 */
#define  VTSS_F_AES_AES_ODATAR0_ODATA0(x)     (x)
#define  VTSS_M_AES_AES_ODATAR0_ODATA0        0xffffffff
#define  VTSS_X_AES_AES_ODATAR0_ODATA0(x)     (x)


/**
 * \brief AES Output Data Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_ODATAR1
 */
#define VTSS_AES_AES_ODATAR1                 VTSS_IOREG(VTSS_TO_AES,0x15)

/**
 * \brief
 * ODATA: Output DataThe four 32-bit Output Data registers contain the
 * 128-bit data block that has been encrypted/decrypted.AES_ODATAR0
 * corresponds to the first word, AES_ODATAR3 to the last one.
 *
 * \details
 * Field: ::VTSS_AES_AES_ODATAR1 . ODATA1
 */
#define  VTSS_F_AES_AES_ODATAR1_ODATA1(x)     (x)
#define  VTSS_M_AES_AES_ODATAR1_ODATA1        0xffffffff
#define  VTSS_X_AES_AES_ODATAR1_ODATA1(x)     (x)


/**
 * \brief AES Output Data Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_ODATAR2
 */
#define VTSS_AES_AES_ODATAR2                 VTSS_IOREG(VTSS_TO_AES,0x16)

/**
 * \brief
 * ODATA: Output DataThe four 32-bit Output Data registers contain the
 * 128-bit data block that has been encrypted/decrypted.AES_ODATAR0
 * corresponds to the first word, AES_ODATAR3 to the last one.
 *
 * \details
 * Field: ::VTSS_AES_AES_ODATAR2 . ODATA2
 */
#define  VTSS_F_AES_AES_ODATAR2_ODATA2(x)     (x)
#define  VTSS_M_AES_AES_ODATAR2_ODATA2        0xffffffff
#define  VTSS_X_AES_AES_ODATAR2_ODATA2(x)     (x)


/**
 * \brief AES Output Data Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_ODATAR3
 */
#define VTSS_AES_AES_ODATAR3                 VTSS_IOREG(VTSS_TO_AES,0x17)

/**
 * \brief
 * ODATA: Output DataThe four 32-bit Output Data registers contain the
 * 128-bit data block that has been encrypted/decrypted.AES_ODATAR0
 * corresponds to the first word, AES_ODATAR3 to the last one.
 *
 * \details
 * Field: ::VTSS_AES_AES_ODATAR3 . ODATA3
 */
#define  VTSS_F_AES_AES_ODATAR3_ODATA3(x)     (x)
#define  VTSS_M_AES_AES_ODATAR3_ODATA3        0xffffffff
#define  VTSS_X_AES_AES_ODATAR3_ODATA3(x)     (x)


/**
 * \brief AES Initialization Vector Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_IVR0
 */
#define VTSS_AES_AES_IVR0                    VTSS_IOREG(VTSS_TO_AES,0x18)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AES_IVR0 corresponds to
 * the first word of the Initialization Vector, AES_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC, OFB and CFB modes, the
 * IV input value corresponds to the initialization vector.For CTR mode,
 * the IV input value corresponds to the initial counter value.Note: These
 * registers are not used in ECB mode and must not be written.
 *
 * \details
 * Field: ::VTSS_AES_AES_IVR0 . IV0
 */
#define  VTSS_F_AES_AES_IVR0_IV0(x)           (x)
#define  VTSS_M_AES_AES_IVR0_IV0              0xffffffff
#define  VTSS_X_AES_AES_IVR0_IV0(x)           (x)


/**
 * \brief AES Initialization Vector Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_IVR1
 */
#define VTSS_AES_AES_IVR1                    VTSS_IOREG(VTSS_TO_AES,0x19)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AES_IVR0 corresponds to
 * the first word of the Initialization Vector, AES_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC, OFB and CFB modes, the
 * IV input value corresponds to the initialization vector.For CTR mode,
 * the IV input value corresponds to the initial counter value.Note: These
 * registers are not used in ECB mode and must not be written.
 *
 * \details
 * Field: ::VTSS_AES_AES_IVR1 . IV1
 */
#define  VTSS_F_AES_AES_IVR1_IV1(x)           (x)
#define  VTSS_M_AES_AES_IVR1_IV1              0xffffffff
#define  VTSS_X_AES_AES_IVR1_IV1(x)           (x)


/**
 * \brief AES Initialization Vector Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_IVR2
 */
#define VTSS_AES_AES_IVR2                    VTSS_IOREG(VTSS_TO_AES,0x1a)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AES_IVR0 corresponds to
 * the first word of the Initialization Vector, AES_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC, OFB and CFB modes, the
 * IV input value corresponds to the initialization vector.For CTR mode,
 * the IV input value corresponds to the initial counter value.Note: These
 * registers are not used in ECB mode and must not be written.
 *
 * \details
 * Field: ::VTSS_AES_AES_IVR2 . IV2
 */
#define  VTSS_F_AES_AES_IVR2_IV2(x)           (x)
#define  VTSS_M_AES_AES_IVR2_IV2              0xffffffff
#define  VTSS_X_AES_AES_IVR2_IV2(x)           (x)


/**
 * \brief AES Initialization Vector Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_IVR3
 */
#define VTSS_AES_AES_IVR3                    VTSS_IOREG(VTSS_TO_AES,0x1b)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AES_IVR0 corresponds to
 * the first word of the Initialization Vector, AES_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC, OFB and CFB modes, the
 * IV input value corresponds to the initialization vector.For CTR mode,
 * the IV input value corresponds to the initial counter value.Note: These
 * registers are not used in ECB mode and must not be written.
 *
 * \details
 * Field: ::VTSS_AES_AES_IVR3 . IV3
 */
#define  VTSS_F_AES_AES_IVR3_IV3(x)           (x)
#define  VTSS_M_AES_AES_IVR3_IV3              0xffffffff
#define  VTSS_X_AES_AES_IVR3_IV3(x)           (x)


/**
 * \brief AES Additional Authenticated Data Length Register
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_AADLENR
 */
#define VTSS_AES_AES_AADLENR                 VTSS_IOREG(VTSS_TO_AES,0x1c)

/**
 * \brief
 * AADLEN: Additional Authenticated Data LengthLength in bytes of the
 * Additional Authenticated Data (AAD) that is to be processed.Note: The
 * maximum byte length of the AAD portion of a message is limited to the
 * 32-bit counter length.
 *
 * \details
 * Field: ::VTSS_AES_AES_AADLENR . AADLEN
 */
#define  VTSS_F_AES_AES_AADLENR_AADLEN(x)     (x)
#define  VTSS_M_AES_AES_AADLENR_AADLEN        0xffffffff
#define  VTSS_X_AES_AES_AADLENR_AADLEN(x)     (x)


/**
 * \brief AES Plaintext/Ciphertext Length Register
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_CLENR
 */
#define VTSS_AES_AES_CLENR                   VTSS_IOREG(VTSS_TO_AES,0x1d)

/**
 * \brief
 * CLEN: Plaintext/Ciphertext LengthLength in bytes of the
 * plaintext/ciphertext (C) data that is to be processed.Note: The maximum
 * byte length of the C portion of a message is limited to the 32-bit
 * counter length.
 *
 * \details
 * Field: ::VTSS_AES_AES_CLENR . CLEN
 */
#define  VTSS_F_AES_AES_CLENR_CLEN(x)         (x)
#define  VTSS_M_AES_AES_CLENR_CLEN            0xffffffff
#define  VTSS_X_AES_AES_CLENR_CLEN(x)         (x)


/**
 * \brief AES GCM Intermediate Hash Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GHASHR0
 */
#define VTSS_AES_AES_GHASHR0                 VTSS_IOREG(VTSS_TO_AES,0x1e)

/**
 * \brief
 * GHASH: Intermediate GCM Hash Word xThe four 32-bit Intermediate Hash
 * Word registers expose the intermediate GHASH value. May be read to save
 * the currentGHASH value so processing can later be resumed, presumably on
 * a later message fragment. Whenever a new key is writtento the AES Key
 * Register two automatic actions are processed:- GCM hash subkey
 * generation- AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.If an application software-specific
 * hash initial value is needed for the GHASH, it must be written to
 * AES_GHASHRx:-  after a write to the AES Key Register, if any,-  before
 * starting the input data feed.
 *
 * \details
 * Field: ::VTSS_AES_AES_GHASHR0 . GHASH0
 */
#define  VTSS_F_AES_AES_GHASHR0_GHASH0(x)     (x)
#define  VTSS_M_AES_AES_GHASHR0_GHASH0        0xffffffff
#define  VTSS_X_AES_AES_GHASHR0_GHASH0(x)     (x)


/**
 * \brief AES GCM Intermediate Hash Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GHASHR1
 */
#define VTSS_AES_AES_GHASHR1                 VTSS_IOREG(VTSS_TO_AES,0x1f)

/**
 * \brief
 * GHASH: Intermediate GCM Hash Word xThe four 32-bit Intermediate Hash
 * Word registers expose the intermediate GHASH value. May be read to save
 * the currentGHASH value so processing can later be resumed, presumably on
 * a later message fragment. Whenever a new key is writtento the AES Key
 * Register two automatic actions are processed:- GCM hash subkey
 * generation- AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.If an application software-specific
 * hash initial value is needed for the GHASH, it must be written to
 * AES_GHASHRx:-  after a write to the AES Key Register, if any,-  before
 * starting the input data feed.
 *
 * \details
 * Field: ::VTSS_AES_AES_GHASHR1 . GHASH1
 */
#define  VTSS_F_AES_AES_GHASHR1_GHASH1(x)     (x)
#define  VTSS_M_AES_AES_GHASHR1_GHASH1        0xffffffff
#define  VTSS_X_AES_AES_GHASHR1_GHASH1(x)     (x)


/**
 * \brief AES GCM Intermediate Hash Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GHASHR2
 */
#define VTSS_AES_AES_GHASHR2                 VTSS_IOREG(VTSS_TO_AES,0x20)

/**
 * \brief
 * GHASH: Intermediate GCM Hash Word xThe four 32-bit Intermediate Hash
 * Word registers expose the intermediate GHASH value. May be read to save
 * the currentGHASH value so processing can later be resumed, presumably on
 * a later message fragment. Whenever a new key is writtento the AES Key
 * Register two automatic actions are processed:- GCM hash subkey
 * generation- AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.If an application software-specific
 * hash initial value is needed for the GHASH, it must be written to
 * AES_GHASHRx:-  after a write to the AES Key Register, if any,-  before
 * starting the input data feed.
 *
 * \details
 * Field: ::VTSS_AES_AES_GHASHR2 . GHASH2
 */
#define  VTSS_F_AES_AES_GHASHR2_GHASH2(x)     (x)
#define  VTSS_M_AES_AES_GHASHR2_GHASH2        0xffffffff
#define  VTSS_X_AES_AES_GHASHR2_GHASH2(x)     (x)


/**
 * \brief AES GCM Intermediate Hash Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GHASHR3
 */
#define VTSS_AES_AES_GHASHR3                 VTSS_IOREG(VTSS_TO_AES,0x21)

/**
 * \brief
 * GHASH: Intermediate GCM Hash Word xThe four 32-bit Intermediate Hash
 * Word registers expose the intermediate GHASH value. May be read to save
 * the currentGHASH value so processing can later be resumed, presumably on
 * a later message fragment. Whenever a new key is writtento the AES Key
 * Register two automatic actions are processed:- GCM hash subkey
 * generation- AES_GHASHRx ClearSee Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.If an application software-specific
 * hash initial value is needed for the GHASH, it must be written to
 * AES_GHASHRx:-  after a write to the AES Key Register, if any,-  before
 * starting the input data feed.
 *
 * \details
 * Field: ::VTSS_AES_AES_GHASHR3 . GHASH3
 */
#define  VTSS_F_AES_AES_GHASHR3_GHASH3(x)     (x)
#define  VTSS_M_AES_AES_GHASHR3_GHASH3        0xffffffff
#define  VTSS_X_AES_AES_GHASHR3_GHASH3(x)     (x)


/**
 * \brief AES GCM Authentication Tag Word Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_TAGR0
 */
#define VTSS_AES_AES_TAGR0                   VTSS_IOREG(VTSS_TO_AES,0x22)

/**
 * \brief
 * TAG: GCM Authentication Tag xThe four 32-bit Tag registers contain the
 * final 128-bit GCM Authentication tag (T) when GCM processing is
 * complete.TAG0 corresponds to the first word, TAG3 to the last word.
 *
 * \details
 * Field: ::VTSS_AES_AES_TAGR0 . TAG0
 */
#define  VTSS_F_AES_AES_TAGR0_TAG0(x)         (x)
#define  VTSS_M_AES_AES_TAGR0_TAG0            0xffffffff
#define  VTSS_X_AES_AES_TAGR0_TAG0(x)         (x)


/**
 * \brief AES GCM Authentication Tag Word Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_TAGR1
 */
#define VTSS_AES_AES_TAGR1                   VTSS_IOREG(VTSS_TO_AES,0x23)

/**
 * \brief
 * TAG: GCM Authentication Tag xThe four 32-bit Tag registers contain the
 * final 128-bit GCM Authentication tag (T) when GCM processing is
 * complete.TAG0 corresponds to the first word, TAG3 to the last word.
 *
 * \details
 * Field: ::VTSS_AES_AES_TAGR1 . TAG1
 */
#define  VTSS_F_AES_AES_TAGR1_TAG1(x)         (x)
#define  VTSS_M_AES_AES_TAGR1_TAG1            0xffffffff
#define  VTSS_X_AES_AES_TAGR1_TAG1(x)         (x)


/**
 * \brief AES GCM Authentication Tag Word Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_TAGR2
 */
#define VTSS_AES_AES_TAGR2                   VTSS_IOREG(VTSS_TO_AES,0x24)

/**
 * \brief
 * TAG: GCM Authentication Tag xThe four 32-bit Tag registers contain the
 * final 128-bit GCM Authentication tag (T) when GCM processing is
 * complete.TAG0 corresponds to the first word, TAG3 to the last word.
 *
 * \details
 * Field: ::VTSS_AES_AES_TAGR2 . TAG2
 */
#define  VTSS_F_AES_AES_TAGR2_TAG2(x)         (x)
#define  VTSS_M_AES_AES_TAGR2_TAG2            0xffffffff
#define  VTSS_X_AES_AES_TAGR2_TAG2(x)         (x)


/**
 * \brief AES GCM Authentication Tag Word Register 0
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_TAGR3
 */
#define VTSS_AES_AES_TAGR3                   VTSS_IOREG(VTSS_TO_AES,0x25)

/**
 * \brief
 * TAG: GCM Authentication Tag xThe four 32-bit Tag registers contain the
 * final 128-bit GCM Authentication tag (T) when GCM processing is
 * complete.TAG0 corresponds to the first word, TAG3 to the last word.
 *
 * \details
 * Field: ::VTSS_AES_AES_TAGR3 . TAG3
 */
#define  VTSS_F_AES_AES_TAGR3_TAG3(x)         (x)
#define  VTSS_M_AES_AES_TAGR3_TAG3            0xffffffff
#define  VTSS_X_AES_AES_TAGR3_TAG3(x)         (x)


/**
 * \brief AES GCM Encryption Counter Value Register
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_CTRR
 */
#define VTSS_AES_AES_CTRR                    VTSS_IOREG(VTSS_TO_AES,0x26)

/**
 * \brief
 * CTR: GCM Encryption CounterReports the current value of the 32-bit GCM
 * counter.
 *
 * \details
 * Field: ::VTSS_AES_AES_CTRR . CTR
 */
#define  VTSS_F_AES_AES_CTRR_CTR(x)           (x)
#define  VTSS_M_AES_AES_CTRR_CTR              0xffffffff
#define  VTSS_X_AES_AES_CTRR_CTR(x)           (x)


/**
 * \brief AES GCM H Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GCMHR0
 */
#define VTSS_AES_AES_GCMHR0                  VTSS_IOREG(VTSS_TO_AES,0x27)

/**
 * \brief
 * H: GCM H Word xThe four 32-bit H Word registers contain the 128-bit GCM
 * hash subkey H value.Whenever a new key is written to the AES Key
 * Register, two automatic actions are processed:- GCM hash subkey H
 * generation- AES_GHASHRx ClearIf the application software requires a
 * specific hash subkey, the automatically-generated H value can be
 * overwritten inAES_GCMHRx. See Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.Generating a GCM hash subkey H by a
 * write in AES_GCMHRx enables to:- select the GCM hash subkey H for GHASH
 * operations,- select one operand to process a single GF128 multiply.
 *
 * \details
 * Field: ::VTSS_AES_AES_GCMHR0 . H0
 */
#define  VTSS_F_AES_AES_GCMHR0_H0(x)          (x)
#define  VTSS_M_AES_AES_GCMHR0_H0             0xffffffff
#define  VTSS_X_AES_AES_GCMHR0_H0(x)          (x)


/**
 * \brief AES GCM H Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GCMHR1
 */
#define VTSS_AES_AES_GCMHR1                  VTSS_IOREG(VTSS_TO_AES,0x28)

/**
 * \brief
 * H: GCM H Word xThe four 32-bit H Word registers contain the 128-bit GCM
 * hash subkey H value.Whenever a new key is written to the AES Key
 * Register, two automatic actions are processed:- GCM hash subkey H
 * generation- AES_GHASHRx ClearIf the application software requires a
 * specific hash subkey, the automatically-generated H value can be
 * overwritten inAES_GCMHRx. See Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.Generating a GCM hash subkey H by a
 * write in AES_GCMHRx enables to:- select the GCM hash subkey H for GHASH
 * operations,- select one operand to process a single GF128 multiply.
 *
 * \details
 * Field: ::VTSS_AES_AES_GCMHR1 . H1
 */
#define  VTSS_F_AES_AES_GCMHR1_H1(x)          (x)
#define  VTSS_M_AES_AES_GCMHR1_H1             0xffffffff
#define  VTSS_X_AES_AES_GCMHR1_H1(x)          (x)


/**
 * \brief AES GCM H Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GCMHR2
 */
#define VTSS_AES_AES_GCMHR2                  VTSS_IOREG(VTSS_TO_AES,0x29)

/**
 * \brief
 * H: GCM H Word xThe four 32-bit H Word registers contain the 128-bit GCM
 * hash subkey H value.Whenever a new key is written to the AES Key
 * Register, two automatic actions are processed:- GCM hash subkey H
 * generation- AES_GHASHRx ClearIf the application software requires a
 * specific hash subkey, the automatically-generated H value can be
 * overwritten inAES_GCMHRx. See Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.Generating a GCM hash subkey H by a
 * write in AES_GCMHRx enables to:- select the GCM hash subkey H for GHASH
 * operations,- select one operand to process a single GF128 multiply.
 *
 * \details
 * Field: ::VTSS_AES_AES_GCMHR2 . H2
 */
#define  VTSS_F_AES_AES_GCMHR2_H2(x)          (x)
#define  VTSS_M_AES_AES_GCMHR2_H2             0xffffffff
#define  VTSS_X_AES_AES_GCMHR2_H2(x)          (x)


/**
 * \brief AES GCM H Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_GCMHR3
 */
#define VTSS_AES_AES_GCMHR3                  VTSS_IOREG(VTSS_TO_AES,0x2a)

/**
 * \brief
 * H: GCM H Word xThe four 32-bit H Word registers contain the 128-bit GCM
 * hash subkey H value.Whenever a new key is written to the AES Key
 * Register, two automatic actions are processed:- GCM hash subkey H
 * generation- AES_GHASHRx ClearIf the application software requires a
 * specific hash subkey, the automatically-generated H value can be
 * overwritten inAES_GCMHRx. See Section 5.6.2 Key Writing and Automatic
 * Hash Subkey Calculation for details.Generating a GCM hash subkey H by a
 * write in AES_GCMHRx enables to:- select the GCM hash subkey H for GHASH
 * operations,- select one operand to process a single GF128 multiply.
 *
 * \details
 * Field: ::VTSS_AES_AES_GCMHR3 . H3
 */
#define  VTSS_F_AES_AES_GCMHR3_H3(x)          (x)
#define  VTSS_M_AES_AES_GCMHR3_H3             0xffffffff
#define  VTSS_X_AES_AES_GCMHR3_H3(x)          (x)


/**
 * \brief AES Extended Mode Register
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_EMR
 */
#define VTSS_AES_AES_EMR                     VTSS_IOREG(VTSS_TO_AES,0x2c)

/**
 * \brief
 * BPE: Block Processing End0: AES_ISR.DATRDY_ISR flag reports only the end
 * message encryption processing. No intermediate block processing
 * isreported when SMOD=0x2 or 0x3. When a DMA is used to transfer data,
 * BPE must be cleared.1: AES_ISR.DATRDY_ISR flag reports each end of block
 * processing when SMOD=0x2 or 0x3. When AES_IDATARx are notloaded by a DMA
 * and SMOD=0x2/0x3, this bit can be written to 1 to rise the
 * AES_ISR.DATRDY_ISR flag when a new datablock can be written.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . BPE
 */
#define  VTSS_F_AES_AES_EMR_BPE(x)            VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_AES_AES_EMR_BPE               VTSS_BIT(31)
#define  VTSS_X_AES_AES_EMR_BPE(x)            VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * NHEAD: IPSEC Next Header0-255: IPSEC Next Header field
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . NHEAD
 */
#define  VTSS_F_AES_AES_EMR_NHEAD(x)          VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_AES_AES_EMR_NHEAD             VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_AES_AES_EMR_NHEAD(x)          VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * PADLEN: Auto Padding Length0-255: Padding length in bytes
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . PADLEN
 */
#define  VTSS_F_AES_AES_EMR_PADLEN(x)         VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AES_AES_EMR_PADLEN            VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AES_AES_EMR_PADLEN(x)         VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * PKRS: Private Key Internal Register Select0: The key used by the AES is
 * in the AES_KEYWRx registers.1: The key used by the AES is in the private
 * key internal registers written via the private key bus.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . PKRS
 */
#define  VTSS_F_AES_AES_EMR_PKRS(x)           VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_AES_AES_EMR_PKRS              VTSS_BIT(7)
#define  VTSS_X_AES_AES_EMR_PKRS(x)           VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * PKWL: Private Key Write Lock0: The private key internal registers can be
 * written multiple times via the private key bus.1: The private key
 * internal registers can be written only once via the private key bus
 * until hardware reset.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . PKWL
 */
#define  VTSS_F_AES_AES_EMR_PKWL(x)           VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_AES_AES_EMR_PKWL              VTSS_BIT(6)
#define  VTSS_X_AES_AES_EMR_PKWL(x)           VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * PLIPD: Protocol Layer Improved Performance Decipher0: Protocol layer
 * improved performance is in ciphering mode.1: Protocol layer improved
 * performance is in deciphering mode.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . PLIPD
 */
#define  VTSS_F_AES_AES_EMR_PLIPD(x)          VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_AES_AES_EMR_PLIPD             VTSS_BIT(5)
#define  VTSS_X_AES_AES_EMR_PLIPD(x)          VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * PLIPEN: Protocol Layer Improved Performance Enable0: Protocol layer
 * improved performance is disabled.1: Protocol layer improved performance
 * is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . PLIPEN
 */
#define  VTSS_F_AES_AES_EMR_PLIPEN(x)         VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_AES_AES_EMR_PLIPEN            VTSS_BIT(4)
#define  VTSS_X_AES_AES_EMR_PLIPEN(x)         VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * APM: Auto Padding Mode0: Auto Padding performed according to IPSEC
 * standard.1: Auto Padding performed according to SSL standard.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . APM
 */
#define  VTSS_F_AES_AES_EMR_APM(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AES_AES_EMR_APM               VTSS_BIT(1)
#define  VTSS_X_AES_AES_EMR_APM(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * APEN: Auto Padding Enable0: Auto Padding feature is disabled.1: Auto
 * Padding feature is enabled.
 *
 * \details
 * Field: ::VTSS_AES_AES_EMR . APEN
 */
#define  VTSS_F_AES_AES_EMR_APEN(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_EMR_APEN              VTSS_BIT(0)
#define  VTSS_X_AES_AES_EMR_APEN(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Byte Counter Register
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_BCNT
 */
#define VTSS_AES_AES_BCNT                    VTSS_IOREG(VTSS_TO_AES,0x2d)

/**
 * \brief
 * BCNT: Auto Padding Byte CounterAuto padding byte counter value. BCNT
 * must be greater than 0.
 *
 * \details
 * Field: ::VTSS_AES_AES_BCNT . BCNT
 */
#define  VTSS_F_AES_AES_BCNT_BCNT(x)          VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_AES_AES_BCNT_BCNT             VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_AES_AES_BCNT_BCNT(x)          VTSS_EXTRACT_BITFIELD(x,0,31)


/**
 * \brief AES Tweak Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_TWR0
 */
#define VTSS_AES_AES_TWR0                    VTSS_IOREG(VTSS_TO_AES,0x30)

/**
 * \brief
 * TWEAK: Tweak Word xThe four 32-bit Tweak Word registers contain the
 * 128-bit Tweak value.
 *
 * \details
 * Field: ::VTSS_AES_AES_TWR0 . TWEAK0
 */
#define  VTSS_F_AES_AES_TWR0_TWEAK0(x)        (x)
#define  VTSS_M_AES_AES_TWR0_TWEAK0           0xffffffff
#define  VTSS_X_AES_AES_TWR0_TWEAK0(x)        (x)


/**
 * \brief AES Tweak Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_TWR1
 */
#define VTSS_AES_AES_TWR1                    VTSS_IOREG(VTSS_TO_AES,0x31)

/**
 * \brief
 * TWEAK: Tweak Word xThe four 32-bit Tweak Word registers contain the
 * 128-bit Tweak value.
 *
 * \details
 * Field: ::VTSS_AES_AES_TWR1 . TWEAK1
 */
#define  VTSS_F_AES_AES_TWR1_TWEAK1(x)        (x)
#define  VTSS_M_AES_AES_TWR1_TWEAK1           0xffffffff
#define  VTSS_X_AES_AES_TWR1_TWEAK1(x)        (x)


/**
 * \brief AES Tweak Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_TWR2
 */
#define VTSS_AES_AES_TWR2                    VTSS_IOREG(VTSS_TO_AES,0x32)

/**
 * \brief
 * TWEAK: Tweak Word xThe four 32-bit Tweak Word registers contain the
 * 128-bit Tweak value.
 *
 * \details
 * Field: ::VTSS_AES_AES_TWR2 . TWEAK2
 */
#define  VTSS_F_AES_AES_TWR2_TWEAK2(x)        (x)
#define  VTSS_M_AES_AES_TWR2_TWEAK2           0xffffffff
#define  VTSS_X_AES_AES_TWR2_TWEAK2(x)        (x)


/**
 * \brief AES Tweak Word Register 0
 *
 * \details
 *
 * Read/Write
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_TWR3
 */
#define VTSS_AES_AES_TWR3                    VTSS_IOREG(VTSS_TO_AES,0x33)

/**
 * \brief
 * TWEAK: Tweak Word xThe four 32-bit Tweak Word registers contain the
 * 128-bit Tweak value.
 *
 * \details
 * Field: ::VTSS_AES_AES_TWR3 . TWEAK3
 */
#define  VTSS_F_AES_AES_TWR3_TWEAK3(x)        (x)
#define  VTSS_M_AES_AES_TWR3_TWEAK3           0xffffffff
#define  VTSS_X_AES_AES_TWR3_TWEAK3(x)        (x)


/**
 * \brief AES Alpha Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_ALPHAR0
 */
#define VTSS_AES_AES_ALPHAR0                 VTSS_IOREG(VTSS_TO_AES,0x34)

/**
 * \brief
 * ALPHA: Alpha Word xThe four 32-bit Alpha Word registers contain the
 * 128-bit primitive of GF(2128) to use for the first processing.
 *
 * \details
 * Field: ::VTSS_AES_AES_ALPHAR0 . ALPHA0
 */
#define  VTSS_F_AES_AES_ALPHAR0_ALPHA0(x)     (x)
#define  VTSS_M_AES_AES_ALPHAR0_ALPHA0        0xffffffff
#define  VTSS_X_AES_AES_ALPHAR0_ALPHA0(x)     (x)


/**
 * \brief AES Alpha Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_ALPHAR1
 */
#define VTSS_AES_AES_ALPHAR1                 VTSS_IOREG(VTSS_TO_AES,0x35)

/**
 * \brief
 * ALPHA: Alpha Word xThe four 32-bit Alpha Word registers contain the
 * 128-bit primitive of GF(2128) to use for the first processing.
 *
 * \details
 * Field: ::VTSS_AES_AES_ALPHAR1 . ALPHA1
 */
#define  VTSS_F_AES_AES_ALPHAR1_ALPHA1(x)     (x)
#define  VTSS_M_AES_AES_ALPHAR1_ALPHA1        0xffffffff
#define  VTSS_X_AES_AES_ALPHAR1_ALPHA1(x)     (x)


/**
 * \brief AES Alpha Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_ALPHAR2
 */
#define VTSS_AES_AES_ALPHAR2                 VTSS_IOREG(VTSS_TO_AES,0x36)

/**
 * \brief
 * ALPHA: Alpha Word xThe four 32-bit Alpha Word registers contain the
 * 128-bit primitive of GF(2128) to use for the first processing.
 *
 * \details
 * Field: ::VTSS_AES_AES_ALPHAR2 . ALPHA2
 */
#define  VTSS_F_AES_AES_ALPHAR2_ALPHA2(x)     (x)
#define  VTSS_M_AES_AES_ALPHAR2_ALPHA2        0xffffffff
#define  VTSS_X_AES_AES_ALPHAR2_ALPHA2(x)     (x)


/**
 * \brief AES Alpha Word Register 0
 *
 * \details
 *
 * Write-only
 * This register can only be written if the WPEN bit is cleared in the AES
 * Write Protection Mode Register.
 *
 * Register: \a AES:AES_REGS:AES_ALPHAR3
 */
#define VTSS_AES_AES_ALPHAR3                 VTSS_IOREG(VTSS_TO_AES,0x37)

/**
 * \brief
 * ALPHA: Alpha Word xThe four 32-bit Alpha Word registers contain the
 * 128-bit primitive of GF(2128) to use for the first processing.
 *
 * \details
 * Field: ::VTSS_AES_AES_ALPHAR3 . ALPHA3
 */
#define  VTSS_F_AES_AES_ALPHAR3_ALPHA3(x)     (x)
#define  VTSS_M_AES_AES_ALPHAR3_ALPHA3        0xffffffff
#define  VTSS_X_AES_AES_ALPHAR3_ALPHA3(x)     (x)


/**
 * \brief AES Write Protection Mode Register
 *
 * \details
 * Read/Write
 *
 * Register: \a AES:AES_REGS:AES_WPMR
 */
#define VTSS_AES_AES_WPMR                    VTSS_IOREG(VTSS_TO_AES,0x39)

/**
 * \brief
 * WPKEY: Write Protection KeyValue Name Description0x414553 PASSWDWriting
 * any other value in this field aborts the write operation of the
 * WPEN,WPITEN,WPCREN bits.Always reads as 0.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . WPKEY
 */
#define  VTSS_F_AES_AES_WPMR_WPKEY(x)         VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_AES_AES_WPMR_WPKEY            VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_AES_AES_WPMR_WPKEY(x)         VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * ACTION: Action on Abnormal Event DetectionValue Name Description0
 * REPORT_ONLYNo action (stop or clear key) is performed when one of
 * PKRPVS, WPVS, CGD, SEQE,or SWE flags is set.1 LOCK_PKRPVS_WPVS_SWEIf a
 * processing is in progress when the AES_WPSR.PKRPVS/WPVS/SWE
 * eventdetection occurs, the current processing is ended normally but no
 * other processing isstarted while a AES_CR.UNLOCK command is issued.2
 * LOCK_CGD_SEQEIf a processing is in progress when the AES_WPSR.CGD/SEQE
 * event detectionoccurs, the current processing is ended normally but no
 * other processing is startedwhile a AES_CR.UNLOCK command is issued.3
 * LOCK_ANY_EVIf a processing is in progress when
 * theAES_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection occurs, the
 * currentprocessing is ended normally but no other processing is started
 * while aAES_CR.UNLOCK command is issued.4 CLEAR_PKRPVS_WPVS_SWEIf a
 * processing is in progress when the AES_WPSR.PKRPVS/WPVS/SWE
 * eventsdetection occurs, the current processing is ended normally but no
 * other processing isstarted while a AES_CR.UNLOCK command is
 * issued.Moreover, the AES_KEYWRx key is immedialely cleared.5
 * CLEAR_CGD_SEQEIf a processing is in progress when the AES_WPSR.CGD/SEQE
 * events detectionoccurs, the current processing is ended normally but no
 * other processing is startedwhile a AES_CR.UNLOCK command is
 * issued.Moreover, the AES_KEYWRx key is immedialely cleared.6
 * CLEAR_ANY_EVIf a processing is in progress when
 * theAES_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection occurs, the
 * currentprocessing is ended normally but no other processing is started
 * while aAES_CR.UNLOCK command is issued.Moreover, the AES_KEYWRx key is
 * immedialely cleared.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . ACTION
 */
#define  VTSS_F_AES_AES_WPMR_ACTION(x)        VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_AES_AES_WPMR_ACTION           VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_AES_AES_WPMR_ACTION(x)        VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * FIRSTE: First Error Report Enable0: The last write protection violation
 * source is reported in AES_WPSR.WPVSRC and the last software control
 * error type isreported in AES_WPSR.SWETYP. The AES_ISR.SECE_ISR flag is
 * set at the first error occurrence within a series.1: Only the first
 * write protection violation source is reported in AES_WPSR.WPVSRC and
 * only the first software controlerror type is reported in
 * AES_WPSR.SWETYP. The AES_ISR.SECE_ISR flag is set at the first error
 * occurrence within a series.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . FIRSTE
 */
#define  VTSS_F_AES_AES_WPMR_FIRSTE(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_AES_AES_WPMR_FIRSTE           VTSS_BIT(4)
#define  VTSS_X_AES_AES_WPMR_FIRSTE(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * WPCREN: Write Protection Control Enable0: Disables the write protection
 * on control register if WPKEY corresponds to 0x414553 (AES in ASCII).1:
 * Enables the write protection on control register if WPKEY corresponds to
 * 0x414553 (AES in ASCII).
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . WPCREN
 */
#define  VTSS_F_AES_AES_WPMR_WPCREN(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AES_AES_WPMR_WPCREN           VTSS_BIT(2)
#define  VTSS_X_AES_AES_WPMR_WPCREN(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interruption Enable0: Disables the write
 * protection on interrupt registers if WPKEY corresponds to 0x414553 (AES
 * in ASCII).1: Enables the write protection on interrupt registers if
 * WPKEY corresponds to 0x414553 (AES in ASCII).
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . WPITEN
 */
#define  VTSS_F_AES_AES_WPMR_WPITEN(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AES_AES_WPMR_WPITEN           VTSS_BIT(1)
#define  VTSS_X_AES_AES_WPMR_WPITEN(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Configuration Enable0: Disables the write
 * protection on configuration registers if WPKEY corresponds to 0x414553
 * (AES in ASCII).1: Enables the write protection on configuration
 * registers if WPKEY corresponds to 0x414553 (AES in ASCII).See Section
 * 5.10.5 Register Write Protection for the list of registers that can be
 * write-protected.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPMR . WPEN
 */
#define  VTSS_F_AES_AES_WPMR_WPEN(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_WPMR_WPEN             VTSS_BIT(0)
#define  VTSS_X_AES_AES_WPMR_WPEN(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Write Protection Status Register
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_WPSR
 */
#define VTSS_AES_AES_WPSR                    VTSS_IOREG(VTSS_TO_AES,0x3a)

/**
 * \brief
 * ECLASS: Software Error Class (cleared on read)0 (WARNING): An abnormal
 * access that does not affect system functionality1 (ERROR): An access is
 * performed into key, input data, control registers while the AES is
 * performing an encryption/decryption or a start is request by software or
 * DMA while the key is not fully configured.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . ECLASS
 */
#define  VTSS_F_AES_AES_WPSR_ECLASS(x)        VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_AES_AES_WPSR_ECLASS           VTSS_BIT(31)
#define  VTSS_X_AES_AES_WPSR_ECLASS(x)        VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * SWETYP: Software Error Type (cleared on read)Value Name Description0
 * READ_WO A write-only register has been read (Warning).1 WRITE_RO AES is
 * enabled and a write access has been performed on a read-only register
 * (Warning).2 UNDEF_RW Access to an undefined address (Warning).3
 * CTRL_START Abnormal use of AES_CR.START command when DMA access is
 * configured.4 WEIRD_ACTIONA key write, init value write, output data
 * read, AES_MR and AES_EMR write, GCMconfiguration registers write,
 * AES_TWRx and AES_ALPHARx registers write,AES_BCNT write, private key bus
 * access has been performed while a current processingis in progress
 * (abnormal).5 INCOMPLETE_KEYA tentative of start is required while the
 * key is not fully loaded into the AES_KEYWRxregisters.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . SWETYP
 */
#define  VTSS_F_AES_AES_WPSR_SWETYP(x)        VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_AES_AES_WPSR_SWETYP           VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_AES_AES_WPSR_SWETYP(x)        VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS=1, WPVSRC indicates
 * the register address offset at which a write access has been
 * attempted.When WPVS=0 and SWE=1, WPVSRC reports the address of the
 * incorrect software access. As soon as WPVS=1,WPVSRC returns the address
 * of the write-protected violation.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . WPVSRC
 */
#define  VTSS_F_AES_AES_WPSR_WPVSRC(x)        VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_AES_AES_WPSR_WPVSRC           VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_AES_AES_WPSR_WPVSRC(x)        VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * PKRPVS: Private Key Internal Register Protection Violation Status
 * (cleared on read)0: No private key internal register access violation
 * has occurred since the last read of AES_WPSR.1: A private key internal
 * register access violation has occurred since the last read of AES_WPSR.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . PKRPVS
 */
#define  VTSS_F_AES_AES_WPSR_PKRPVS(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_AES_AES_WPSR_PKRPVS           VTSS_BIT(4)
#define  VTSS_X_AES_AES_WPSR_PKRPVS(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SWE: Software Control Error (cleared on read)0: No software error has
 * occurred since the last read of AES_WPSR.1: A software error has
 * occurred since the last read of AES_WPSR. The field SWETYP details the
 * type of software error;the associated incorrect software access is
 * reported in the field WPVSRC (if WPVS=0).
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . SWE
 */
#define  VTSS_F_AES_AES_WPSR_SWE(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_AES_AES_WPSR_SWE              VTSS_BIT(3)
#define  VTSS_X_AES_AES_WPSR_SWE(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SEQE: Internal Sequencer Error (cleared on read)0: No peripheral
 * internal sequencer error has occurred since the last read of AES_WPSR.1:
 * A peripheral internal sequencer error has occurred since the last read
 * of AES_WPSR. This flag can only be set underabnormal operating
 * conditions.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . SEQE
 */
#define  VTSS_F_AES_AES_WPSR_SEQE(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_AES_AES_WPSR_SEQE             VTSS_BIT(2)
#define  VTSS_X_AES_AES_WPSR_SEQE(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CGD: Clock Glitch Detected (cleared on read)0: The clock monitoring
 * circuitry has not been corrupted since the last read of AES_WPSR. Under
 * normal operating conditions,this bit is always cleared.1: The clock
 * monitoring circuitry has been corrupted since the last read of AES_WPSR.
 * This flag can only be set in case ofan abnormal clock signal waveform
 * (glitch).
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . CGD
 */
#define  VTSS_F_AES_AES_WPSR_CGD(x)           VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_AES_AES_WPSR_CGD              VTSS_BIT(1)
#define  VTSS_X_AES_AES_WPSR_CGD(x)           VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPVS: Write Protection Violation Status (cleared on read)0: No write
 * protect violation has occurred since the last read of AES_WPSR.1: A
 * write protect violation has occurred since the last read of AES_WPSR.
 * The address offset of the violated register isreported into field
 * WPVSRC.
 *
 * \details
 * Field: ::VTSS_AES_AES_WPSR . WPVS
 */
#define  VTSS_F_AES_AES_WPSR_WPVS(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_AES_AES_WPSR_WPVS             VTSS_BIT(0)
#define  VTSS_X_AES_AES_WPSR_WPVS(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief AES Version Register
 *
 * \details
 * Read-only
 *
 * Register: \a AES:AES_REGS:AES_VERSION
 */
#define VTSS_AES_AES_VERSION                 VTSS_IOREG(VTSS_TO_AES,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_AES_AES_VERSION . MFN
 */
#define  VTSS_F_AES_AES_VERSION_MFN(x)        VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_AES_AES_VERSION_MFN           VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_AES_AES_VERSION_MFN(x)        VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the Atmel internal version
 * of the macrocell.
 *
 * \details
 * Field: ::VTSS_AES_AES_VERSION . VERSION
 */
#define  VTSS_F_AES_AES_VERSION_VERSION(x)    VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_AES_AES_VERSION_VERSION       VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_AES_AES_VERSION_VERSION(x)    VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_AES_H_ */
