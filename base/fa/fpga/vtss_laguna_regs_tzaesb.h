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

#ifndef _VTSS_LAGUNA_REGS_TZAESB_H_
#define _VTSS_LAGUNA_REGS_TZAESB_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a TZAESB
 *
 * \see vtss_target_TZAESB_e
 *
 * The TrustZone Advanced Encryption Standard Bridge (TZAESB) provides
 * on-the-fly off-chip
 * memory encryption/decryption compliant with the American FIPS (Federal
 * Information Processing
 * Standard) Publication 197 specification.

 *
 ***********************************************************************/

/**
 * Register Group: \a TZAESB:TZAESB_REGS
 *
 * Not documented
 */


/**
 * \brief TZAESB Control Register
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPCREN is cleared in the TZAESB
 * Write Protection Mode Register
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_CR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_CR(target)        VTSS_IOREG(target,0x0)

/**
 * \brief
 * UNLOCK: Unlock Processing0: No effect.1: Unlocks the processing in case
 * of abnormal event detection if TZAESB_WPMR.ACTION > 0.TZAESB_WPSR must
 * be cleared before performing the unlock command.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_CR . UNLOCK
 */
#define  VTSS_F_TZAESB_TZAESB_CR_UNLOCK(x)    VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_TZAESB_TZAESB_CR_UNLOCK       VTSS_BIT(24)
#define  VTSS_X_TZAESB_TZAESB_CR_UNLOCK(x)    VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * LOADSEED: Random Number Generator Seed Loading0: No effect.1: Restarts
 * the countermeasures generator to an internal pre-defined value.
 *
 * \details
 * 0: No effect
 * 1: Restarts the countermeasures generator to an internal pre-defined
 * value
 *
 * Field: ::VTSS_TZAESB_TZAESB_CR . LOADSEED
 */
#define  VTSS_F_TZAESB_TZAESB_CR_LOADSEED(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_TZAESB_TZAESB_CR_LOADSEED     VTSS_BIT(16)
#define  VTSS_X_TZAESB_TZAESB_CR_LOADSEED(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * SWRST: Software Reset0: No effect.1: Resets the TZAESB. A software
 * triggered hardware reset of the TZAESB interface is performed.
 *
 * \details
 * 0: No effect
 * 1: Resets the AESB. A software triggered hardware reset of the AESB
 * interface is performed.
 *
 * Field: ::VTSS_TZAESB_TZAESB_CR . SWRST
 */
#define  VTSS_F_TZAESB_TZAESB_CR_SWRST(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZAESB_TZAESB_CR_SWRST        VTSS_BIT(8)
#define  VTSS_X_TZAESB_TZAESB_CR_SWRST(x)     VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * START: Start Processing0: No effect.1: Starts manual
 * encryption/decryption process.
 *
 * \details
 * 0: No effect
 * 1: Starts manual encryption/decryption process
 *
 * Field: ::VTSS_TZAESB_TZAESB_CR . START
 */
#define  VTSS_F_TZAESB_TZAESB_CR_START(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZAESB_TZAESB_CR_START        VTSS_BIT(0)
#define  VTSS_X_TZAESB_TZAESB_CR_START(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESB Mode Register
 *
 * \details
 * Read/Write
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * Notes: 1. All the countermeasures are enabled by default.
 * 2. CMTYPx are write-only and can only be modified if CKEY is correctly
 * set.
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_MR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_MR(target)        VTSS_IOREG(target,0x1)

/**
 * \brief
 * TAMPCLR: Tamper Clear Enable0: A tamper detection event has no effect on
 * the TZAESB_KEYWRx key.1: A tamper detection event immediately clears the
 * TZAESB_KEYWRx key.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_MR . TAMPCLR
 */
#define  VTSS_F_TZAESB_TZAESB_MR_TAMPCLR(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_TZAESB_TZAESB_MR_TAMPCLR      VTSS_BIT(31)
#define  VTSS_X_TZAESB_TZAESB_MR_TAMPCLR(x)   VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * CMTYP7: Countermeasure Type 70 (NO_STARTDELAY): Countermeasure type 7 is
 * disabled.1 (STARTDELAY): Countermeasure type 7 is enabled.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP7
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP7(x)    VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP7       VTSS_BIT(30)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP7(x)    VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * CMTYP6: CounterMeasure Type 6Notes: 1. All the countermeasures are
 * enabled by default.2. CMTYPx fields are write-only and can only be
 * modified if CKEY is correctly set.
 *
 * \details
 * 0 (NO_IDLECURRENT): Countermeasure type 6 is disabled.
 * 1 (IDLECURRENT): Countermeasure type 6 is enabled.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP6
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP6(x)    VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP6       VTSS_BIT(29)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP6(x)    VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * CMTYP5: Countermeasure Type 5
 *
 * \details
 * 0 (NO_ADDACCESS): Countermeasure type 5 is disabled.
 * 1 (ADDACCESS): Countermeasure type 5 is enabled.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP5
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP5(x)    VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP5       VTSS_BIT(28)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP5(x)    VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * CMTYP4: Countermeasure Type 4
 *
 * \details
 * 0 (NO_RESTART): Countermeasure type 4 is disabled.
 * 1 (RESTART): Countermeasure type 4 is enabled
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP4
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP4(x)    VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP4       VTSS_BIT(27)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP4(x)    VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * CMTYP3: Countermeasure Type 3
 *
 * \details
 * 0 (NO_DUMMY): Countermeasure type 3 is disabled.
 * 1 (DUMMY): Countermeasure type 3 is enabled.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP3
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP3(x)    VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP3       VTSS_BIT(26)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP3(x)    VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * CMTYP2: Countermeasure Type 2
 *
 * \details
 * 0 (NO_PAUSE): Countermeasure type 2 is disabled.
 * 1 (PAUSE): Countermeasure type 2 is enabled.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP2
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP2(x)    VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP2       VTSS_BIT(25)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP2(x)    VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * CMTYP1: Countermeasure Type 1
 *
 * \details
 * 0 (NOPROT_EXTKEY): Countermeasure type 1 is disabled.
 * 1 (PROT_EXTKEY): Countermeasure type 1 is enabled.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . CMTYP1
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CMTYP1(x)    VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_TZAESB_TZAESB_MR_CMTYP1       VTSS_BIT(24)
#define  VTSS_X_TZAESB_TZAESB_MR_CMTYP1(x)    VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CKEY: Countermeasure KeyValue Name Description0xE PASSWDMust be written
 * with 0xE to allowCMTYPx change. Any other values aborts the write
 * operation in CMTYPx.Always reads as 0.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_MR . CKEY
 */
#define  VTSS_F_TZAESB_TZAESB_MR_CKEY(x)      VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_TZAESB_TZAESB_MR_CKEY         VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_TZAESB_TZAESB_MR_CKEY(x)      VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * OPMOD: Operating ModeValue Name Description0x0  -  Reserved0x1  -
 * Reserved0x2	-  Reserved0x3	-  Reserved0x4 CTR Counter mode (16-bit
 * internal counter)Values which are not listed in the table must be
 * considered as reservedNote: If OPMOD is set to 0x4 and AAHB = 1, there
 * is no compliance with the standard CTR mode of operation but the mode of
 * operationis derived from CTR mode.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_MR . OPMOD
 */
#define  VTSS_F_TZAESB_TZAESB_MR_OPMOD(x)     VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_TZAESB_TZAESB_MR_OPMOD        VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_TZAESB_TZAESB_MR_OPMOD(x)     VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * PROCDLY: Processing DelayProcessing Time = 12 * (PROCDLY + 1)The
 * Processing Time represents the number of clock cycles that the AESB
 * needs in order to perform one encryption/decryption with no
 * countermeasures activated.Note: The best performance is achieved with
 * PROCDLY equal to "0".
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_MR . PROCDLY
 */
#define  VTSS_F_TZAESB_TZAESB_MR_PROCDLY(x)   VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_TZAESB_TZAESB_MR_PROCDLY      VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_TZAESB_TZAESB_MR_PROCDLY(x)   VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * \brief
 * DUALBUFF: Dual Input BufferValue Name Description0x0 INACTIVE New access
 * cannot be accepted during processing of previous block.0x1 ACTIVENew
 * access can be accepted during processing of previous block when SMOD =
 * 0x2. It speeds up theoverall runtime of large files.
 *
 * \details
 * 0x0 INACTIVE AESB_IDATARx cannot be written during processing of
 * previous block.
 * 0x1 ACTIVE
 * AESB_IDATARx can be written during processing of previous block when
 * SMOD = 0x2. It speeds up the
 * overall runtime of large files.
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . DUALBUFF
 */
#define  VTSS_F_TZAESB_TZAESB_MR_DUALBUFF(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TZAESB_TZAESB_MR_DUALBUFF     VTSS_BIT(3)
#define  VTSS_X_TZAESB_TZAESB_MR_DUALBUFF(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * AAHB: Automatic Bridge Mode0: Automatic Bridge mode disabled.1:
 * Automatic Bridge mode enabled.
 *
 * \details
 * 0: Automatic Bridge mode disabled
 * 1: Automatic Bridge mode enabled
 *
 * Field: ::VTSS_TZAESB_TZAESB_MR . AAHB
 */
#define  VTSS_F_TZAESB_TZAESB_MR_AAHB(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TZAESB_TZAESB_MR_AAHB         VTSS_BIT(2)
#define  VTSS_X_TZAESB_TZAESB_MR_AAHB(x)      VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief TZAESB Interrupt Enable Register
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPITEN is cleared in the TZAESB
 * Write Protection Mode Register
 *
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Enables the corresponding interrupt.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IER
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IER(target)       VTSS_IOREG(target,0x4)

/**
 * \brief
 * SECE: Security and/or Safety Event
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IER . SECE
 */
#define  VTSS_F_TZAESB_TZAESB_IER_SECE(x)     VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_TZAESB_TZAESB_IER_SECE        VTSS_BIT(19)
#define  VTSS_X_TZAESB_TZAESB_IER_SECE(x)     VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Enable
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IER . URAD
 */
#define  VTSS_F_TZAESB_TZAESB_IER_URAD(x)     VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZAESB_TZAESB_IER_URAD        VTSS_BIT(8)
#define  VTSS_X_TZAESB_TZAESB_IER_URAD(x)     VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief TZAESB Interrupt Disable Register
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPITEN is cleared in the TZAESB
 * Write Protection Mode Register
 *
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IDR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IDR(target)       VTSS_IOREG(target,0x5)

/**
 * \brief
 * SECE: Security and/or Safety Event
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IDR . SECE_IDR
 */
#define  VTSS_F_TZAESB_TZAESB_IDR_SECE_IDR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_TZAESB_TZAESB_IDR_SECE_IDR    VTSS_BIT(19)
#define  VTSS_X_TZAESB_TZAESB_IDR_SECE_IDR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Disable
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IDR . URAD_IDR
 */
#define  VTSS_F_TZAESB_TZAESB_IDR_URAD_IDR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZAESB_TZAESB_IDR_URAD_IDR    VTSS_BIT(8)
#define  VTSS_X_TZAESB_TZAESB_IDR_URAD_IDR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief TZAESB Interrupt Mask Register
 *
 * \details
 * Read-only
 *
 *
 *
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IMR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IMR(target)       VTSS_IOREG(target,0x6)

/**
 * \brief
 * SECE: Security and/or Safety Event
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IMR . SECE_IMR
 */
#define  VTSS_F_TZAESB_TZAESB_IMR_SECE_IMR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_TZAESB_TZAESB_IMR_SECE_IMR    VTSS_BIT(19)
#define  VTSS_X_TZAESB_TZAESB_IMR_SECE_IMR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Mask
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IMR . URAD_IMR
 */
#define  VTSS_F_TZAESB_TZAESB_IMR_URAD_IMR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZAESB_TZAESB_IMR_URAD_IMR    VTSS_BIT(8)
#define  VTSS_X_TZAESB_TZAESB_IMR_URAD_IMR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief TZAESB Interrupt Status Register
 *
 * \details
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_ISR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_ISR(target)       VTSS_IOREG(target,0x7)

/**
 * \brief
 * SECE: Security and/or Safety Event0: There is no security report in
 * TZAESB_WPSR.1: One security flag is set in TZAESB_WPSR.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_ISR . SECE_ISR
 */
#define  VTSS_F_TZAESB_TZAESB_ISR_SECE_ISR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_TZAESB_TZAESB_ISR_SECE_ISR    VTSS_BIT(19)
#define  VTSS_X_TZAESB_TZAESB_ISR_SECE_ISR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * URAT: Unspecified Register AccessOnly the last Unspecified Register
 * Access Type is available through the URAT field.URAT field is reset only
 * by the SWRST bit in AESB_CR.0x0 IDR_WR_PROCESSING Input Data Register
 * written during the data processing when SMOD = 0x2 mode0x1
 * ODR_RD_PROCESSING Output Data Register read during the data
 * processing0x2 MR_WR_PROCESSING Mode Register written during the data
 * processing0x3 ODR_RD_SUBKGEN Output Data Register read during the
 * sub-keys generation0x4 MR_WR_SUBKGEN Mode Register written during the
 * sub-keys generation0x5 WOR_RD_ACCESS Write-only register read access
 *
 * \details
 * 0x0 IDR_WR_PROCESSING Input Data Register written during the data
 * processing when SMOD = 0x2 mode
 * 0x1 ODR_RD_PROCESSING Output Data Register read during the data
 * processing
 * 0x2 MR_WR_PROCESSING Mode Register written during the data processing
 * 0x3 ODR_RD_SUBKGEN Output Data Register read during the sub-keys
 * generation
 * 0x4 MR_WR_SUBKGEN Mode Register written during the sub-keys generation
 * 0x5 WOR_RD_ACCESS Write-only register read access
 *
 * Field: ::VTSS_TZAESB_TZAESB_ISR . URAT_ISR
 */
#define  VTSS_F_TZAESB_TZAESB_ISR_URAT_ISR(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_TZAESB_TZAESB_ISR_URAT_ISR     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_TZAESB_TZAESB_ISR_URAT_ISR(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * URAD: Unspecified Register Access Detection StatusURAD bit is reset only
 * by the SWRST bit in AESB_CR.0: No unspecified register access has been
 * detected since the last SWRST.1: At least one unspecified register
 * access has been detected since the last SWRST.
 *
 * \details
 * 0: No unspecified register access has been detected since the last
 * SWRST.
 * 1: At least one unspecified register access has been detected since the
 * last SWRST.
 *
 * Field: ::VTSS_TZAESB_TZAESB_ISR . URAD_ISR
 */
#define  VTSS_F_TZAESB_TZAESB_ISR_URAD_ISR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZAESB_TZAESB_ISR_URAD_ISR    VTSS_BIT(8)
#define  VTSS_X_TZAESB_TZAESB_ISR_URAD_ISR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief TZAESB Key Word Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * These registers are write-only to prevent the key from being read by
 * another application.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_KEYWR0
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_KEYWR0(target)    VTSS_IOREG(target,0x8)

/**
 * \brief
 * KEYW: Key WordThe four 32-bit Key Word registers set the 128-bit
 * cryptographic key used for encryption/decryption.AESB_KEYWR0 corresponds
 * to the first word of the key, AESB_KEYWR3 to the last one.These
 * registers are write-only to prevent the key from being read by another
 * application.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_KEYWR0 . KEYW0
 */
#define  VTSS_F_TZAESB_TZAESB_KEYWR0_KEYW0(x)  (x)
#define  VTSS_M_TZAESB_TZAESB_KEYWR0_KEYW0     0xffffffff
#define  VTSS_X_TZAESB_TZAESB_KEYWR0_KEYW0(x)  (x)


/**
 * \brief TZAESB Key Word Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * These registers are write-only to prevent the key from being read by
 * another application.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_KEYWR1
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_KEYWR1(target)    VTSS_IOREG(target,0x9)

/**
 * \brief
 * KEYW: Key WordThe four 32-bit Key Word registers set the 128-bit
 * cryptographic key used for encryption/decryption.AESB_KEYWR0 corresponds
 * to the first word of the key, AESB_KEYWR3 to the last one.These
 * registers are write-only to prevent the key from being read by another
 * application.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_KEYWR1 . KEYW1
 */
#define  VTSS_F_TZAESB_TZAESB_KEYWR1_KEYW1(x)  (x)
#define  VTSS_M_TZAESB_TZAESB_KEYWR1_KEYW1     0xffffffff
#define  VTSS_X_TZAESB_TZAESB_KEYWR1_KEYW1(x)  (x)


/**
 * \brief TZAESB Key Word Register x
 *
 * \details
 * Write_Only
 *
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * These registers are write-only to prevent the key from being read by
 * another application.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_KEYWR2
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_KEYWR2(target)    VTSS_IOREG(target,0xa)

/**
 * \brief
 * KEYW: Key WordThe four 32-bit Key Word registers set the 128-bit
 * cryptographic key used for encryption/decryption.AESB_KEYWR0 corresponds
 * to the first word of the key, AESB_KEYWR3 to the last one.These
 * registers are write-only to prevent the key from being read by another
 * application.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_KEYWR2 . KEYW2
 */
#define  VTSS_F_TZAESB_TZAESB_KEYWR2_KEYW2(x)  (x)
#define  VTSS_M_TZAESB_TZAESB_KEYWR2_KEYW2     0xffffffff
#define  VTSS_X_TZAESB_TZAESB_KEYWR2_KEYW2(x)  (x)


/**
 * \brief TZAESB Key Word Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * These registers are write-only to prevent the key from being read by
 * another application.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_KEYWR3
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_KEYWR3(target)    VTSS_IOREG(target,0xb)

/**
 * \brief
 * KEYW: Key WordThe four 32-bit Key Word registers set the 128-bit
 * cryptographic key used for encryption/decryption.AESB_KEYWR0 corresponds
 * to the first word of the key, AESB_KEYWR3 to the last one.These
 * registers are write-only to prevent the key from being read by another
 * application.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_KEYWR3 . KEYW3
 */
#define  VTSS_F_TZAESB_TZAESB_KEYWR3_KEYW3(x)  (x)
#define  VTSS_M_TZAESB_TZAESB_KEYWR3_KEYW3     0xffffffff
#define  VTSS_X_TZAESB_TZAESB_KEYWR3_KEYW3(x)  (x)


/**
 * \brief TZAESB Initialization Vector Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IVR0
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IVR0(target)      VTSS_IOREG(target,0x18)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.TZAESB_IVR0 corresponds
 * to the first word of the Initialization Vector, TZAESB_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC mode, the IV input value
 * corresponds to the initialization vector.For CTR mode, the IV input
 * value corresponds to the initial counter value.Note: These registers are
 * not used in ECB mode and must not be written. For Automatic Bridge
 * dedicated mode, the IV input valuecorresponds to the initial nonce.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IVR0 . IV0
 */
#define  VTSS_F_TZAESB_TZAESB_IVR0_IV0(x)     (x)
#define  VTSS_M_TZAESB_TZAESB_IVR0_IV0        0xffffffff
#define  VTSS_X_TZAESB_TZAESB_IVR0_IV0(x)     (x)


/**
 * \brief TZAESB Initialization Vector Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IVR1
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IVR1(target)      VTSS_IOREG(target,0x19)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AESB_IVR0 corresponds
 * to the first word of the Initialization Vector, AESB_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC mode, the IV input value
 * corresponds to the initialization vector.For CTR mode, the IV input
 * value corresponds to the initial counter value.Note: These registers are
 * not used in ECB mode and must not be written. For Automatic Bridge
 * dedicated mode, the IV input valuecorresponds to the initial nonce.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IVR1 . IV1
 */
#define  VTSS_F_TZAESB_TZAESB_IVR1_IV1(x)     (x)
#define  VTSS_M_TZAESB_TZAESB_IVR1_IV1        0xffffffff
#define  VTSS_X_TZAESB_TZAESB_IVR1_IV1(x)     (x)


/**
 * \brief TZAESB Initialization Vector Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IVR2
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IVR2(target)      VTSS_IOREG(target,0x1a)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AESB_IVR0 corresponds
 * to the first word of the Initialization Vector, AESB_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC mode, the IV input value
 * corresponds to the initialization vector.For CTR mode, the IV input
 * value corresponds to the initial counter value.Note: These registers are
 * not used in ECB mode and must not be written. For Automatic Bridge
 * dedicated mode, the IV input valuecorresponds to the initial nonce.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IVR2 . IV2
 */
#define  VTSS_F_TZAESB_TZAESB_IVR2_IV2(x)     (x)
#define  VTSS_M_TZAESB_TZAESB_IVR2_IV2        0xffffffff
#define  VTSS_X_TZAESB_TZAESB_IVR2_IV2(x)     (x)


/**
 * \brief TZAESB Initialization Vector Register x
 *
 * \details
 * Write_Only
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register
 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_IVR3
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_IVR3(target)      VTSS_IOREG(target,0x1b)

/**
 * \brief
 * IV: Initialization VectorThe four 32-bit Initialization Vector registers
 * set the 128-bit Initialization Vector data block that is used by some
 * modes ofoperation as an additional initial input.AESB_IVR0 corresponds
 * to the first word of the Initialization Vector, AESB_IVR3 to the last
 * one.These registers are write-only to prevent the Initialization Vector
 * from being read by another application.For CBC mode, the IV input value
 * corresponds to the initialization vector.For CTR mode, the IV input
 * value corresponds to the initial counter value.Note: These registers are
 * not used in ECB mode and must not be written. For Automatic Bridge
 * dedicated mode, the IV input valuecorresponds to the initial nonce.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_IVR3 . IV3
 */
#define  VTSS_F_TZAESB_TZAESB_IVR3_IV3(x)     (x)
#define  VTSS_M_TZAESB_TZAESB_IVR3_IV3        0xffffffff
#define  VTSS_X_TZAESB_TZAESB_IVR3_IV3(x)     (x)


/**
 * \brief TZAESB Extended Mode Register
 *
 * \details
 * Read/Write
 *
 * This register can only be written if WPEN is cleared in the TZAESB Write
 * Protection Mode Register.

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_EMR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_EMR(target)       VTSS_IOREG(target,0x2c)

/**
 * \brief
 * PKWO: Private Key Write Once0: The Private Key Internal register can be
 * written multiple times through the Private Key Bus.1: The Private Key
 * Internal register can be written only once through the Private Key Bus
 * until hardware reset.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_EMR . PKRS
 */
#define  VTSS_F_TZAESB_TZAESB_EMR_PKRS(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TZAESB_TZAESB_EMR_PKRS        VTSS_BIT(7)
#define  VTSS_X_TZAESB_TZAESB_EMR_PKRS(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * PKRS: Private Key Internal Register Select0: The key used by the TZAESB
 * is in the TZAESB_KEYWRx.1: The key used by the TZAESB is in the Private
 * Key Internal register written through the Private Key Bus.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_EMR . PKWO
 */
#define  VTSS_F_TZAESB_TZAESB_EMR_PKWO(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TZAESB_TZAESB_EMR_PKWO        VTSS_BIT(6)
#define  VTSS_X_TZAESB_TZAESB_EMR_PKWO(x)     VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief TZAESB Write Protection Mode Register
 *
 * \details
 * Read/Write

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_WPMR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_WPMR(target)      VTSS_IOREG(target,0x39)

/**
 * \brief
 * WPKEY: Write Protection KeyValue Name Description0x414553 PASSWDWriting
 * any other value in this field aborts the write operation of the
 * WPEN,WPITEN,WPCREN bits.Always reads as 0
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . WPKEY
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_WPKEY(x)   VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_TZAESB_TZAESB_WPMR_WPKEY      VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_TZAESB_TZAESB_WPMR_WPKEY(x)   VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * ACTION: Action on Abnormal Event DetectionValue Name Description0
 * REPORT_ONLYNo action (stop or clear key) is performed when one of
 * PKRPVS, WPVS, CGD, SEQE,or SWE flags is set.1 LOCK_PKRPVS_WPVS_SWEIf a
 * processing is in progress when the TZAESB_WPSR.PKRPVS/WPVS/SWE
 * eventdetection occurs, the current processing is ended normally but no
 * other processing isstarted while a TZAESB_CR.UNLOCK command is issued.2
 * LOCK_CGD_SEQEIf a processing is in progress when the
 * TZAESB_WPSR.CGD/SEQE event detectionoccurs, the current processing is
 * ended normally but no other processing is startedwhile a
 * TZAESB_CR.UNLOCK command is issued.3 LOCK_ANY_EVIf a processing is in
 * progress when theTZAESB_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection
 * occurs, thecurrent processing is ended normally but no other processing
 * is started while aTZAESB_CR.UNLOCK command is issued.4
 * CLEAR_PKRPVS_WPVS_SWEIf a processing is in progress when the
 * TZAESB_WPSR.PKRPVS/WPVS/SWE eventsdetection occurs, the current
 * processing is ended normally but no other processing isstarted while a
 * TZAESB_CR.UNLOCK command is issued.Moreover, the TZAESB_KEYWRx key is
 * immediately cleared.5 CLEAR_CGD_SEQEIf a processing is in progress when
 * the TZAESB_WPSR.CGD/SEQE events detectionoccurs, the current processing
 * is ended normally but no other processing is startedwhile a
 * TZAESB_CR.UNLOCK command is issued.Moreover, the TZAESB_KEYWRx key is
 * immediately cleared.6 CLEAR_ANY_EVIf a processing is in progress when
 * theTZAESB_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection occurs,
 * thecurrent processing is ended normally but no other processing is
 * started while aTZAESB_CR.UNLOCK command is issued.Moreover, the
 * TZAESB_KEYWRx key is immediately cleared.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . ACTION
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_ACTION(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_TZAESB_TZAESB_WPMR_ACTION     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_TZAESB_TZAESB_WPMR_ACTION(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * FIRSTE: First Error Report Enable0: The last write protection violation
 * source is reported in TZAESB_WPSR.WPVSRC and the last software control
 * errortype is reported in TZAESB_WPSR.SWETYP. The TZAESB_ISR.SECE_ISR
 * flag is set at the first error occurrence within aseries.1: Only the
 * first write protection violation source is reported in
 * TZAESB_WPSR.WPVSRC and only the first software controlerror type is
 * reported in TZAESB_WPSR.SWETYP. The TZAESB_ISR.SECE_ISR flag is set at
 * the first error occurrence withina series.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . FIRSTE
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_FIRSTE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TZAESB_TZAESB_WPMR_FIRSTE     VTSS_BIT(4)
#define  VTSS_X_TZAESB_TZAESB_WPMR_FIRSTE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * WPCREN: Write Protection Control Enable0: Disables the write protection
 * on control register if WPKEY corresponds to 0x414553 (AES in ASCII).1:
 * Enables the write protection on control register if WPKEY corresponds to
 * 0x414553 (AES in ASCII).
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . WPCREN
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_WPCREN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TZAESB_TZAESB_WPMR_WPCREN     VTSS_BIT(2)
#define  VTSS_X_TZAESB_TZAESB_WPMR_WPCREN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interruption Enable0: Disables the write
 * protection on interrupt registers if WPKEY corresponds to 0x414553 (AES
 * in ASCII).1: Enables the write protection on interrupt registers if
 * WPKEY corresponds to 0x414553 (AES in ASCII).
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . WPITEN
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_WPITEN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TZAESB_TZAESB_WPMR_WPITEN     VTSS_BIT(1)
#define  VTSS_X_TZAESB_TZAESB_WPMR_WPITEN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Configuration Enable0: Disables the write
 * protection on configuration registers if WPKEY corresponds to 0x414553
 * (AES in ASCII).1: Enables the write protection on configuration
 * registers if WPKEY corresponds to 0x414553 (AES in ASCII).See Section
 * 6.4.5 Register Write Protection for the list of registers that can be
 * write-protected.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPMR . WPEN
 */
#define  VTSS_F_TZAESB_TZAESB_WPMR_WPEN(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZAESB_TZAESB_WPMR_WPEN       VTSS_BIT(0)
#define  VTSS_X_TZAESB_TZAESB_WPMR_WPEN(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESB Write Protection Status Register
 *
 * \details
 * Read-only

 *
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_WPSR
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_WPSR(target)      VTSS_IOREG(target,0x3a)

/**
 * \brief
 * ECLASS: Software Error Class (cleared on read)0 (WARNING): An abnormal
 * access that does not affect system functionality1 (ERROR): An access is
 * performed into key, input data, control registers while the TZAESB is
 * performing an encryption/decryption or a start is request by software or
 * DMA while the key is not fully configured.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . ECLASS
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_ECLASS(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_ECLASS     VTSS_BIT(31)
#define  VTSS_X_TZAESB_TZAESB_WPSR_ECLASS(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * SWETYP: Software Error Type (cleared on read)Value Name Description0
 * READ_WO A write-only register has been read (Warning).1 WRITE_ROTZAESB
 * is enabled and a write access has been performed on a read-only
 * register(Warning).2 UNDEF_RW Access to an undefined address (Warning).3
 * CTRL_START Abnormal use of TZAESB_CR.START command when DMA access is
 * configured.4 WEIRD_ACTIONA Private Key Bus access, key write, init value
 * write, output data read or TZAESB_MRand TZAESB_EMR write has been
 * performed while a process is in progress (abnormal).5 INCOMPLETE_KEYA
 * tentative of start is required while the key is not fully loaded into
 * the TZAESB_KEYWRxregisters.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . SWETYP
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_SWETYP(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_TZAESB_TZAESB_WPSR_SWETYP     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_TZAESB_TZAESB_WPSR_SWETYP(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS=1, WPVSRC indicates
 * the register address offset at which a write access has been
 * attempted.When WPVS=0 and SWE=1, WPVSRC reports the address of the
 * incorrect software access. As soon as WPVS=1,WPVSRC returns the address
 * of the write-protected violation.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . WPVSRC
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_WPVSRC(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_TZAESB_TZAESB_WPSR_WPVSRC     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_TZAESB_TZAESB_WPSR_WPVSRC(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * PKRPVS: Private Key Internal Register Protection Violation Status
 * (cleared on read)0: No Private Key Internal Register access violation
 * has occurred since the last read of TZAESB_WPSR.1: A Private Key
 * Internal Register access violation has occurred since the last read of
 * TZAESB_WPSR.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . PKRPVS
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_PKRPVS(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_PKRPVS     VTSS_BIT(4)
#define  VTSS_X_TZAESB_TZAESB_WPSR_PKRPVS(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SWE: Software Control Error (cleared on read)0: No software error has
 * occurred since the last read of TZAESB_WPSR.1: A software error has
 * occurred since the last read of TZAESB_WPSR. The field SWETYP details
 * the type of softwareerror; the associated incorrect software access is
 * reported in the field WPVSRC (if WPVS=0).
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . SWE
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_SWE(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_SWE        VTSS_BIT(3)
#define  VTSS_X_TZAESB_TZAESB_WPSR_SWE(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SEQE: Internal Sequencer Error (cleared on read)0: No peripheral
 * internal sequencer error has occurred since the last read of
 * TZAESB_WPSR.1: A peripheral internal sequencer error has occurred since
 * the last read of TZAESB_WPSR. This flag can only be setunder abnormal
 * operating conditions.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . SEQE
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_SEQE(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_SEQE       VTSS_BIT(2)
#define  VTSS_X_TZAESB_TZAESB_WPSR_SEQE(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CGD: Clock Glitch Detected (cleared on read)0: No clock glitch has
 * occurred since the last read of TZAESB_WPSR. Under normal operating
 * conditions, this bit is alwayscleared.1: A clock glitch has occurred
 * since the last read of TZAESB_WPSR. This flag can only be set in case of
 * an abnormal clocksignal waveform (glitch).
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . CGD
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_CGD(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_CGD        VTSS_BIT(1)
#define  VTSS_X_TZAESB_TZAESB_WPSR_CGD(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPVS: Write Protection Violation Status (cleared on read)0: No write
 * protect violation has occurred since the last read of TZAESB_WPSR.1: A
 * write protect violation has occurred since the last read of TZAESB_WPSR.
 * The address offset of the violated registeris reported into field
 * WPVSRC.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_WPSR . WPVS
 */
#define  VTSS_F_TZAESB_TZAESB_WPSR_WPVS(x)    VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZAESB_TZAESB_WPSR_WPVS       VTSS_BIT(0)
#define  VTSS_X_TZAESB_TZAESB_WPSR_WPVS(x)    VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TZAESB Version Register
 *
 * \details
 * Register: \a TZAESB:TZAESB_REGS:TZAESB_VERSION
 *
 * @param target A \a ::vtss_target_TZAESB_e target
 */
#define VTSS_TZAESB_TZAESB_VERSION(target)   VTSS_IOREG(target,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_VERSION . MFN
 */
#define  VTSS_F_TZAESB_TZAESB_VERSION_MFN(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_TZAESB_TZAESB_VERSION_MFN     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_TZAESB_TZAESB_VERSION_MFN(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the Atmel internal version
 * of the macrocell.
 *
 * \details
 * Field: ::VTSS_TZAESB_TZAESB_VERSION . VERSION
 */
#define  VTSS_F_TZAESB_TZAESB_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_TZAESB_TZAESB_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_TZAESB_TZAESB_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_TZAESB_H_ */
