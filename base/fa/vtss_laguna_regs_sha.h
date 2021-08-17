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

#ifndef _VTSS_LAGUNA_REGS_SHA_H_
#define _VTSS_LAGUNA_REGS_SHA_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a SHA
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a SHA:SHA_REGS
 *
 * Secure Hash Algorithm (SHA) User Interface
 */


/**
 * \brief SHA Control Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_CR
 */
#define VTSS_SHA_SHA_CR                      VTSS_IOREG(VTSS_TO_SHA,0x0)

/**
 * \brief
 * UNLOCK: Unlock Processing0: No effect.1: Unlocks the processing in case
 * of abnormal event detection if SHA_WPMR.ACTION > 0.SHA_WPSR must be
 * cleared before performing the unlock command.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . UNLOCK
 */
#define  VTSS_F_SHA_SHA_CR_UNLOCK(x)          VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SHA_SHA_CR_UNLOCK             VTSS_BIT(24)
#define  VTSS_X_SHA_SHA_CR_UNLOCK(x)          VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * WUIEHV: Write User Initial or Expected Hash Values0: SHA_IDATARx
 * accesses are routed to the data registers.1: SHA_IDATARx accesses are
 * routed to the internal registers (IR1).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . WUIEHV
 */
#define  VTSS_F_SHA_SHA_CR_WUIEHV(x)          VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SHA_SHA_CR_WUIEHV             VTSS_BIT(13)
#define  VTSS_X_SHA_SHA_CR_WUIEHV(x)          VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * WUIHV: Write User Initial Hash Values0: SHA_IDATARx accesses are routed
 * to the data registers.1: SHA_IDATARx accesses are routed to the internal
 * registers (IR0).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . WUIHV
 */
#define  VTSS_F_SHA_SHA_CR_WUIHV(x)           VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SHA_SHA_CR_WUIHV              VTSS_BIT(12)
#define  VTSS_X_SHA_SHA_CR_WUIHV(x)           VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * SWRST: Software Reset0: No effect.1: Resets the SHA. A
 * software-triggered hardware reset of the SHA interface is performed.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . SWRST
 */
#define  VTSS_F_SHA_SHA_CR_SWRST(x)           VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SHA_SHA_CR_SWRST              VTSS_BIT(8)
#define  VTSS_X_SHA_SHA_CR_SWRST(x)           VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * FIRST: First Block of a Message0: No effect.1: Indicates that the next
 * block to process is the first one of a message.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . FIRST
 */
#define  VTSS_F_SHA_SHA_CR_FIRST(x)           VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SHA_SHA_CR_FIRST              VTSS_BIT(4)
#define  VTSS_X_SHA_SHA_CR_FIRST(x)           VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * START: Start Processing0: No effect.1: Starts manual hash algorithm
 * process.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_CR . START
 */
#define  VTSS_F_SHA_SHA_CR_START(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_CR_START              VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_CR_START(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Mode Register
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_MR
 */
#define VTSS_SHA_SHA_MR                      VTSS_IOREG(VTSS_TO_SHA,0x1)

/**
 * \brief
 * CHKCNT: Check CounterNumber of 32-bit words to check. The value 0
 * indicates that the number of words to compare will be based on the
 * algorithmselected (5 words for SHA1, 7 words for SHA224, 8 words for
 * SHA256, 12 words for SHA384, 16 words for SHA512).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . CHKCNT
 */
#define  VTSS_F_SHA_SHA_MR_CHKCNT(x)          VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SHA_SHA_MR_CHKCNT             VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SHA_SHA_MR_CHKCNT(x)          VTSS_EXTRACT_BITFIELD(x,28,4)

/**
 * \brief
 * CHECK: Hash CheckValue Name Description0 NO_CHECK No check is performed1
 * CHECK_EHV Check is performed with expected hash stored in internal
 * expected hash value registers.2 CHECK_MESSAGE Check is performed with
 * expected hash provided after the message.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . CHECK
 */
#define  VTSS_F_SHA_SHA_MR_CHECK(x)           VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SHA_SHA_MR_CHECK              VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SHA_SHA_MR_CHECK(x)           VTSS_EXTRACT_BITFIELD(x,24,2)

/**
 * \brief
 * DUALBUFF: Dual Input BufferValue	Name		Description0
 *    INACTIVE	    SHA_IDATARx and SHA_IODATARx cannot be written during
 * processing of previous block.1	    ACTIVE	    SHA_IDATARx and
 * SHA_IODATARx can be written during processing of previous block
 *			     when SMOD value = 2. It speeds up the overall
 * runtime of large files.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . DUALBUFF
 */
#define  VTSS_F_SHA_SHA_MR_DUALBUFF(x)        VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SHA_SHA_MR_DUALBUFF           VTSS_BIT(16)
#define  VTSS_X_SHA_SHA_MR_DUALBUFF(x)        VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * TMPLCK: Tamper Lock Enable0: A tamper event has no effect.1: A tamper
 * event locks the SHA until the tamper root cause is cleared and
 * SHA_CR.UNLOCK is written to 1.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . TMPLCK
 */
#define  VTSS_F_SHA_SHA_MR_TMPLCK(x)          VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SHA_SHA_MR_TMPLCK             VTSS_BIT(15)
#define  VTSS_X_SHA_SHA_MR_TMPLCK(x)          VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * ALGO: SHA AlgorithmValue   Name		     Description0
 * SHA1 		   SHA1 algorithm processed1	      SHA256
 *	   SHA256 algorithm processed2		SHA384
 * SHA384 algorithm processed3		SHA512		      SHA512
 * algorithm processed4 	 SHA224 		SHA224 algorithm
 * processed8	       HMAC_SHA1	 HMAC algorithm with SHA1 Hash
 * processed9	       HMAC_SHA256     HMAC algorithm with SHA256 Hash
 * processed10	      HMAC_SHA384     HMAC algorithm with SHA384 Hash
 * processed11	      HMAC_SHA512     HMAC algorithm with SHA512 Hash
 * processed12	      HMAC_SHA224     HMAC algorithm with SHA224 Hash
 * processedValues not listed in the table must be considered as reserved
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . ALGO
 */
#define  VTSS_F_SHA_SHA_MR_ALGO(x)            VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SHA_SHA_MR_ALGO               VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SHA_SHA_MR_ALGO(x)            VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * BPE: Block Processing End0: BPE must be cleared when a DMA transfers
 * data. When SMOD=2, SHA_ISR.DATRDY_ISR flag rises only when the SHA
 * orHMAC processing cycle has completed. No intermediate block processing
 * is reported.1: When processing small messages, data transfer by software
 * can improve performance compared to DMA. In this case,BPE can be written
 * to 1, forcing the SHA_ISR.DATRDY_ISR to rise when a data must be loaded
 * into SHA_IDATARx.When SMOD=2 and ALGO<5, the SHA_ISR.DATRDY_ISR flag
 * rises when each block has been processed.When SMOD=2 and ALGO>7, the
 * SHA_ISR.DATRDY_ISR rises when all blocks except the last one have been
 * processed.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . BPE
 */
#define  VTSS_F_SHA_SHA_MR_BPE(x)             VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SHA_SHA_MR_BPE                VTSS_BIT(7)
#define  VTSS_X_SHA_SHA_MR_BPE(x)             VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * UIEHV: User Initial or Expected Hash Value Registers0: The SHA algorithm
 * is started with the standard initial values as defined in the FIPS180-2
 * specification.1: The SHA algorithm is started with the user initial hash
 * values stored in the internal register 1 (IR1). If HMAC is
 * configured,UIEHV has no effect (i.e. IR1 is always selected).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . UIEHV
 */
#define  VTSS_F_SHA_SHA_MR_UIEHV(x)           VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SHA_SHA_MR_UIEHV              VTSS_BIT(6)
#define  VTSS_X_SHA_SHA_MR_UIEHV(x)           VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * UIHV: User Initial Hash Value Registers0: The SHA algorithm is started
 * with the standard initial values as defined in the FIPS180-2
 * specification.1: The SHA algorithm is started with the user initial hash
 * values stored in the internal register 0 (IR0). If HMAC is
 * configured,UIHV has no effect (i.e. IR0 is selected).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . UIHV
 */
#define  VTSS_F_SHA_SHA_MR_UIHV(x)            VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SHA_SHA_MR_UIHV               VTSS_BIT(5)
#define  VTSS_X_SHA_SHA_MR_UIHV(x)            VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * PROCDLY: Processing DelayValue     Name		 Description0
 *	SHORTEST     SHA processing runtime is the shortest one1
 * LONGEST	  SHA processing runtime is the longest one (reduces the
 * SHA bandwidth requirement,
 * reduces the system bus overload)When SHA1 algorithm is processed,
 * runtime period is either 85 or 209385 clock cycles.When SHA256 or SHA224
 * algorithm is processed, runtime period is either 72 or 194265 clock
 * cycles.When SHA384 or SHA512 algorithm is processed, runtime period is
 * either 88 or 209 clock cycles.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . PROCDLY
 */
#define  VTSS_F_SHA_SHA_MR_PROCDLY(x)         VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SHA_SHA_MR_PROCDLY            VTSS_BIT(4)
#define  VTSS_X_SHA_SHA_MR_PROCDLY(x)         VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SMOD: Start ModeValue   Name 			 Description0
 *    MANUAL_START	 Manual mode1	       AUTO_START	     Auto
 * mode2	  IDATAR0_START       SHA_IDATAR0 access only mode
 * (mandatory when DMA is used)Values not listed in the table must be
 * considered as reservedIf a DMA transfer is used, configure the SMOD
 * value to 2. See Section 5.9.4 DMA Mode for details.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MR . SMOD
 */
#define  VTSS_F_SHA_SHA_MR_SMOD(x)            VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SHA_SHA_MR_SMOD               VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SHA_SHA_MR_SMOD(x)            VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief SHA Interrupt Enable Register
 *
 * \details
 *
 * Write-only
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Enables the corresponding interrupt.
 *
 * Register: \a SHA:SHA_REGS:SHA_IER
 */
#define VTSS_SHA_SHA_IER                     VTSS_IOREG(VTSS_TO_SHA,0x4)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Enable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IER . SECE
 */
#define  VTSS_F_SHA_SHA_IER_SECE(x)           VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SHA_SHA_IER_SECE              VTSS_BIT(24)
#define  VTSS_X_SHA_SHA_IER_SECE(x)           VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CHECKF: Check Done Interrupt Enable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IER . CHECKF
 */
#define  VTSS_F_SHA_SHA_IER_CHECKF(x)         VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SHA_SHA_IER_CHECKF            VTSS_BIT(16)
#define  VTSS_X_SHA_SHA_IER_CHECKF(x)         VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Enable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IER . URAD
 */
#define  VTSS_F_SHA_SHA_IER_URAD(x)           VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SHA_SHA_IER_URAD              VTSS_BIT(8)
#define  VTSS_X_SHA_SHA_IER_URAD(x)           VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Enable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IER . DATRDY
 */
#define  VTSS_F_SHA_SHA_IER_DATRDY(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_IER_DATRDY            VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_IER_DATRDY(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Interrupt Disable Register
 *
 * \details
 *
 * Write-only
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: No effect.
 * 1: Disables the corresponding interrupt.
 *
 * Register: \a SHA:SHA_REGS:SHA_IDR
 */
#define VTSS_SHA_SHA_IDR                     VTSS_IOREG(VTSS_TO_SHA,0x5)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Disable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDR . SECE_IDR
 */
#define  VTSS_F_SHA_SHA_IDR_SECE_IDR(x)       VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SHA_SHA_IDR_SECE_IDR          VTSS_BIT(24)
#define  VTSS_X_SHA_SHA_IDR_SECE_IDR(x)       VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CHECKF: Check Done Interrupt Disable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDR . CHECKF_IDR
 */
#define  VTSS_F_SHA_SHA_IDR_CHECKF_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SHA_SHA_IDR_CHECKF_IDR        VTSS_BIT(16)
#define  VTSS_X_SHA_SHA_IDR_CHECKF_IDR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Disable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDR . URAD_IDR
 */
#define  VTSS_F_SHA_SHA_IDR_URAD_IDR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SHA_SHA_IDR_URAD_IDR          VTSS_BIT(8)
#define  VTSS_X_SHA_SHA_IDR_URAD_IDR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Disable
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDR . DATRDY_IDR
 */
#define  VTSS_F_SHA_SHA_IDR_DATRDY_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_IDR_DATRDY_IDR        VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_IDR_DATRDY_IDR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Interrupt Mask Register
 *
 * \details
 *
 * Read-only
 * The following configuration values are valid for all listed bit names of
 * this register:
 * 0: The corresponding interrupt is not enabled.
 * 1: The corresponding interrupt is enabled.
 *
 * Register: \a SHA:SHA_REGS:SHA_IMR
 */
#define VTSS_SHA_SHA_IMR                     VTSS_IOREG(VTSS_TO_SHA,0x6)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Mask
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IMR . SECE_IMR
 */
#define  VTSS_F_SHA_SHA_IMR_SECE_IMR(x)       VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SHA_SHA_IMR_SECE_IMR          VTSS_BIT(24)
#define  VTSS_X_SHA_SHA_IMR_SECE_IMR(x)       VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CHECKF: Check Done Interrupt Mask
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IMR . CHECKF_IMR
 */
#define  VTSS_F_SHA_SHA_IMR_CHECKF_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SHA_SHA_IMR_CHECKF_IMR        VTSS_BIT(16)
#define  VTSS_X_SHA_SHA_IMR_CHECKF_IMR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Interrupt Mask
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IMR . URAD_IMR
 */
#define  VTSS_F_SHA_SHA_IMR_URAD_IMR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SHA_SHA_IMR_URAD_IMR          VTSS_BIT(8)
#define  VTSS_X_SHA_SHA_IMR_URAD_IMR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Mask
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IMR . DATRDY_IMR
 */
#define  VTSS_F_SHA_SHA_IMR_DATRDY_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_IMR_DATRDY_IMR        VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_IMR_DATRDY_IMR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Interrupt Status Register
 *
 * \details
 * Read-only
 *
 * Register: \a SHA:SHA_REGS:SHA_ISR
 */
#define VTSS_SHA_SHA_ISR                     VTSS_IOREG(VTSS_TO_SHA,0x7)

/**
 * \brief
 * SECE: Security and/or Safety Event0: There is no report in SHA_WPSR.1:
 * There is a Security and/or Safety Event reported in SHA_WPSR.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . SECE_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_SECE_ISR(x)       VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SHA_SHA_ISR_SECE_ISR          VTSS_BIT(24)
#define  VTSS_X_SHA_SHA_ISR_SECE_ISR(x)       VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * CHKST: Check Status (cleared by writing START or SWRST bits in SHA_CR or
 * by reading SHA_IODATARx)Value 5 indicates identical hash values
 * (expected hash = hash result). Any other value indicates different hash
 * values.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . CHKST_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_CHKST_ISR(x)      VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SHA_SHA_ISR_CHKST_ISR         VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SHA_SHA_ISR_CHKST_ISR(x)      VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * CHECKF: Check Done Status (cleared by writing START or SWRST bits in
 * SHA_CR or by readingSHA_IODATARx)0: Hash check has not been computed.1:
 * Hash check has been computed, status is available in the CHKST bits.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . CHECKF_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_CHECKF_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SHA_SHA_ISR_CHECKF_ISR        VTSS_BIT(16)
#define  VTSS_X_SHA_SHA_ISR_CHECKF_ISR(x)     VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * URAT: Unspecified Register Access Type (cleared by writing a 1 to SWRST
 * bit in SHA_CR)Value	  Description0		 SHA_IDATAR0 to
 * SHA_IDATAR15 written during the data processing in DMAPDC mode (URAD = 1
 * and URAT		  = 0 can occur only if DUALBUFF is cleared in
 * SHA_MR).1		Output Data Register read during the data
 * processing.2 	   SHA_MR written during the data processing.3
 *	  Write-only register read access.Only the last Unspecified
 * Register Access Type is available through the URAT field.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . URAT_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_URAT_ISR(x)       VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_SHA_SHA_ISR_URAT_ISR          VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_SHA_SHA_ISR_URAT_ISR(x)       VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * URAD: Unspecified Register Access Detection Status (cleared by writing a
 * 1 to SWRST bit in SHA_CR)0: No unspecified register access has been
 * detected since the last SWRST.1: At least one unspecified register
 * access has been detected since the last SWRST.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . URAD_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_URAD_ISR(x)       VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SHA_SHA_ISR_URAD_ISR          VTSS_BIT(8)
#define  VTSS_X_SHA_SHA_ISR_URAD_ISR(x)       VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * WRDY: Input Data Register Write Ready0: SHA_IDATAR0 cannot be written1:
 * SHA_IDATAR0 can be written
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . WRDY_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_WRDY_ISR(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SHA_SHA_ISR_WRDY_ISR          VTSS_BIT(4)
#define  VTSS_X_SHA_SHA_ISR_WRDY_ISR(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * DATRDY: Data Ready (cleared by writing a 1 to bit SWRST or START in
 * SHA_CR, or by reading SHA_IODATARx)0: Output data is not valid.1:
 * 512/1024-bit block process is completed.DATRDY is cleared when one of
 * the following conditions is met:Bit START in SHA_CR is set.Bit SWRST in
 * SHA_CR is set.The hash result is read.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_ISR . DATRDY_ISR
 */
#define  VTSS_F_SHA_SHA_ISR_DATRDY_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_ISR_DATRDY_ISR        VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_ISR_DATRDY_ISR(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Message Size Register
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_MSR
 */
#define VTSS_SHA_SHA_MSR                     VTSS_IOREG(VTSS_TO_SHA,0x8)

/**
 * \brief
 * MSGSIZE: Message SizeThe size in bytes of the message. When MSGSIZE
 * differs from 0, the SHA appends the corresponding value converted inbits
 * after the padding section, as described in the FIPS180-2
 * specification.To disable automatic padding, MSGSIZE field must be
 * written to 0.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_MSR . MSGSIZE
 */
#define  VTSS_F_SHA_SHA_MSR_MSGSIZE(x)        (x)
#define  VTSS_M_SHA_SHA_MSR_MSGSIZE           0xffffffff
#define  VTSS_X_SHA_SHA_MSR_MSGSIZE(x)        (x)


/**
 * \brief SHA Bytes Count Register
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_BCR
 */
#define VTSS_SHA_SHA_BCR                     VTSS_IOREG(VTSS_TO_SHA,0xc)

/**
 * \brief
 * BYTCNT: Remaining Byte Count Before Auto Padding:When the hash
 * processing starts from the beginning of a message (without preprocessed
 * hash part), BYTCNT must bewritten with the same value as the MSGSIZE. If
 * a part of the message has been already hashed and the hash does notstart
 * from the beginning, BYTCNT must be configured with the number of bytes
 * remaining to process before paddingsection.When read, provides the size
 * in bytes of message remaining to be written before the automatic padding
 * starts.BYTCNT field is automatically updated each time a write occurs in
 * the SHA_IDATARx and SHA_IODATARx.When BYTCNT reaches 0, the MSGSIZE is
 * converted into bit count and appended at the end of the message after
 * thepadding as described in the FIPS180-2 specification.To disable
 * automatic padding, MSGSIZE and BYTCNT fields must be written to 0.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_BCR . BYTCNT
 */
#define  VTSS_F_SHA_SHA_BCR_BYTCNT(x)         (x)
#define  VTSS_M_SHA_SHA_BCR_BYTCNT            0xffffffff
#define  VTSS_X_SHA_SHA_BCR_BYTCNT(x)         (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR0
 */
#define VTSS_SHA_SHA_IDATAR0                 VTSS_IOREG(VTSS_TO_SHA,0x10)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR0 . IDATA0
 */
#define  VTSS_F_SHA_SHA_IDATAR0_IDATA0(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR0_IDATA0        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR0_IDATA0(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR1
 */
#define VTSS_SHA_SHA_IDATAR1                 VTSS_IOREG(VTSS_TO_SHA,0x11)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR1 . IDATA1
 */
#define  VTSS_F_SHA_SHA_IDATAR1_IDATA1(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR1_IDATA1        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR1_IDATA1(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR2
 */
#define VTSS_SHA_SHA_IDATAR2                 VTSS_IOREG(VTSS_TO_SHA,0x12)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR2 . IDATA2
 */
#define  VTSS_F_SHA_SHA_IDATAR2_IDATA2(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR2_IDATA2        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR2_IDATA2(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR3
 */
#define VTSS_SHA_SHA_IDATAR3                 VTSS_IOREG(VTSS_TO_SHA,0x13)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR3 . IDATA3
 */
#define  VTSS_F_SHA_SHA_IDATAR3_IDATA3(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR3_IDATA3        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR3_IDATA3(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR4
 */
#define VTSS_SHA_SHA_IDATAR4                 VTSS_IOREG(VTSS_TO_SHA,0x14)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR4 . IDATA4
 */
#define  VTSS_F_SHA_SHA_IDATAR4_IDATA4(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR4_IDATA4        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR4_IDATA4(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR5
 */
#define VTSS_SHA_SHA_IDATAR5                 VTSS_IOREG(VTSS_TO_SHA,0x15)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR5 . IDATA5
 */
#define  VTSS_F_SHA_SHA_IDATAR5_IDATA5(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR5_IDATA5        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR5_IDATA5(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR6
 */
#define VTSS_SHA_SHA_IDATAR6                 VTSS_IOREG(VTSS_TO_SHA,0x16)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR6 . IDATA6
 */
#define  VTSS_F_SHA_SHA_IDATAR6_IDATA6(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR6_IDATA6        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR6_IDATA6(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR7
 */
#define VTSS_SHA_SHA_IDATAR7                 VTSS_IOREG(VTSS_TO_SHA,0x17)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR7 . IDATA7
 */
#define  VTSS_F_SHA_SHA_IDATAR7_IDATA7(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR7_IDATA7        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR7_IDATA7(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR8
 */
#define VTSS_SHA_SHA_IDATAR8                 VTSS_IOREG(VTSS_TO_SHA,0x18)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR8 . IDATA8
 */
#define  VTSS_F_SHA_SHA_IDATAR8_IDATA8(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR8_IDATA8        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR8_IDATA8(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR9
 */
#define VTSS_SHA_SHA_IDATAR9                 VTSS_IOREG(VTSS_TO_SHA,0x19)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR9 . IDATA9
 */
#define  VTSS_F_SHA_SHA_IDATAR9_IDATA9(x)     (x)
#define  VTSS_M_SHA_SHA_IDATAR9_IDATA9        0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR9_IDATA9(x)     (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR10
 */
#define VTSS_SHA_SHA_IDATAR10                VTSS_IOREG(VTSS_TO_SHA,0x1a)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR10 . IDATA10
 */
#define  VTSS_F_SHA_SHA_IDATAR10_IDATA10(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR10_IDATA10      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR10_IDATA10(x)   (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR11
 */
#define VTSS_SHA_SHA_IDATAR11                VTSS_IOREG(VTSS_TO_SHA,0x1b)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR11 . IDATA11
 */
#define  VTSS_F_SHA_SHA_IDATAR11_IDATA11(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR11_IDATA11      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR11_IDATA11(x)   (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR12
 */
#define VTSS_SHA_SHA_IDATAR12                VTSS_IOREG(VTSS_TO_SHA,0x1c)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR12 . IDATA12
 */
#define  VTSS_F_SHA_SHA_IDATAR12_IDATA12(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR12_IDATA12      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR12_IDATA12(x)   (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR13
 */
#define VTSS_SHA_SHA_IDATAR13                VTSS_IOREG(VTSS_TO_SHA,0x1d)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR13 . IDATA13
 */
#define  VTSS_F_SHA_SHA_IDATAR13_IDATA13(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR13_IDATA13      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR13_IDATA13(x)   (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR14
 */
#define VTSS_SHA_SHA_IDATAR14                VTSS_IOREG(VTSS_TO_SHA,0x1e)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR14 . IDATA14
 */
#define  VTSS_F_SHA_SHA_IDATAR14_IDATA14(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR14_IDATA14      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR14_IDATA14(x)   (x)


/**
 * \brief SHA Input Data 0 Register
 *
 * \details
 * Write-only
 *
 * Register: \a SHA:SHA_REGS:SHA_IDATAR15
 */
#define VTSS_SHA_SHA_IDATAR15                VTSS_IOREG(VTSS_TO_SHA,0x1f)

/**
 * \brief
 * IDATA: Input DataThe 32-bit Input Data registers allow to load the data
 * block used for hash processing.These registers are write-only to prevent
 * the input data from being read by another application.SHA_IDATAR0
 * corresponds to the first word of the block, SHA_IDATAR15 to the last
 * word of the last block in case SHAalgorithm is set to SHA1, SHA224,
 * SHA256 or SHA_IODATA15R to the last word of the block if SHA algorithm
 * is SHA384or SHA512 (see Section 6.10 SHA Input/Output Data Register x).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IDATAR15 . IDATA15
 */
#define  VTSS_F_SHA_SHA_IDATAR15_IDATA15(x)   (x)
#define  VTSS_M_SHA_SHA_IDATAR15_IDATA15      0xffffffff
#define  VTSS_X_SHA_SHA_IDATAR15_IDATA15(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR0
 */
#define VTSS_SHA_SHA_IODATAR0                VTSS_IOREG(VTSS_TO_SHA,0x20)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR0 . IODATA0
 */
#define  VTSS_F_SHA_SHA_IODATAR0_IODATA0(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR0_IODATA0      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR0_IODATA0(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR1
 */
#define VTSS_SHA_SHA_IODATAR1                VTSS_IOREG(VTSS_TO_SHA,0x21)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR1 . IODATA1
 */
#define  VTSS_F_SHA_SHA_IODATAR1_IODATA1(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR1_IODATA1      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR1_IODATA1(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR2
 */
#define VTSS_SHA_SHA_IODATAR2                VTSS_IOREG(VTSS_TO_SHA,0x22)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR2 . IODATA2
 */
#define  VTSS_F_SHA_SHA_IODATAR2_IODATA2(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR2_IODATA2      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR2_IODATA2(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR3
 */
#define VTSS_SHA_SHA_IODATAR3                VTSS_IOREG(VTSS_TO_SHA,0x23)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR3 . IODATA3
 */
#define  VTSS_F_SHA_SHA_IODATAR3_IODATA3(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR3_IODATA3      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR3_IODATA3(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR4
 */
#define VTSS_SHA_SHA_IODATAR4                VTSS_IOREG(VTSS_TO_SHA,0x24)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR4 . IODATA4
 */
#define  VTSS_F_SHA_SHA_IODATAR4_IODATA4(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR4_IODATA4      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR4_IODATA4(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR5
 */
#define VTSS_SHA_SHA_IODATAR5                VTSS_IOREG(VTSS_TO_SHA,0x25)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR5 . IODATA5
 */
#define  VTSS_F_SHA_SHA_IODATAR5_IODATA5(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR5_IODATA5      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR5_IODATA5(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR6
 */
#define VTSS_SHA_SHA_IODATAR6                VTSS_IOREG(VTSS_TO_SHA,0x26)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR6 . IODATA6
 */
#define  VTSS_F_SHA_SHA_IODATAR6_IODATA6(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR6_IODATA6      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR6_IODATA6(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR7
 */
#define VTSS_SHA_SHA_IODATAR7                VTSS_IOREG(VTSS_TO_SHA,0x27)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR7 . IODATA7
 */
#define  VTSS_F_SHA_SHA_IODATAR7_IODATA7(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR7_IODATA7      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR7_IODATA7(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR8
 */
#define VTSS_SHA_SHA_IODATAR8                VTSS_IOREG(VTSS_TO_SHA,0x28)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR8 . IODATA8
 */
#define  VTSS_F_SHA_SHA_IODATAR8_IODATA8(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR8_IODATA8      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR8_IODATA8(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR9
 */
#define VTSS_SHA_SHA_IODATAR9                VTSS_IOREG(VTSS_TO_SHA,0x29)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR9 . IODATA9
 */
#define  VTSS_F_SHA_SHA_IODATAR9_IODATA9(x)   (x)
#define  VTSS_M_SHA_SHA_IODATAR9_IODATA9      0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR9_IODATA9(x)   (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR10
 */
#define VTSS_SHA_SHA_IODATAR10               VTSS_IOREG(VTSS_TO_SHA,0x2a)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR10 . IODATA10
 */
#define  VTSS_F_SHA_SHA_IODATAR10_IODATA10(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR10_IODATA10     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR10_IODATA10(x)  (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR11
 */
#define VTSS_SHA_SHA_IODATAR11               VTSS_IOREG(VTSS_TO_SHA,0x2b)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR11 . IODATA11
 */
#define  VTSS_F_SHA_SHA_IODATAR11_IODATA11(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR11_IODATA11     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR11_IODATA11(x)  (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR12
 */
#define VTSS_SHA_SHA_IODATAR12               VTSS_IOREG(VTSS_TO_SHA,0x2c)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR12 . IODATA12
 */
#define  VTSS_F_SHA_SHA_IODATAR12_IODATA12(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR12_IODATA12     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR12_IODATA12(x)  (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR13
 */
#define VTSS_SHA_SHA_IODATAR13               VTSS_IOREG(VTSS_TO_SHA,0x2d)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR13 . IODATA13
 */
#define  VTSS_F_SHA_SHA_IODATAR13_IODATA13(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR13_IODATA13     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR13_IODATA13(x)  (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR14
 */
#define VTSS_SHA_SHA_IODATAR14               VTSS_IOREG(VTSS_TO_SHA,0x2e)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR14 . IODATA14
 */
#define  VTSS_F_SHA_SHA_IODATAR14_IODATA14(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR14_IODATA14     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR14_IODATA14(x)  (x)


/**
 * \brief SHA Input/Output Data Register 0
 *
 * \details
 * Read/Write
 *
 * Register: \a SHA:SHA_REGS:SHA_IODATAR15
 */
#define VTSS_SHA_SHA_IODATAR15               VTSS_IOREG(VTSS_TO_SHA,0x2f)

/**
 * \brief
 * IODATA: Input/Output DataThese registers can be used to read the
 * resulting message digest and to write the second part of the message
 * block whenthe SHA algorithm is SHA-384 or SHA-512.SHA_IODATA0R to
 * SHA_IODATA15R can be written or read but reading these offsets does not
 * return the content of correspondingparts (words) of the message block.
 * Only results from SHA calculation can be read through these
 * registers.When SHA processing is in progress, these registers return
 * 0x0000.SHA_IODATAR0 corresponds to the first word of the message digest;
 * SHA_IODATAR4 to the last one in SHA1 mode,SHA_ODATAR6 in SHA224,
 * SHA_IODATAR7 in SHA256, SHA_IODATAR11 in SHA384 or SHA_IODATAR15 in
 * SHA512.When SHA224 is selected, the content of SHA_ODATAR7 must be
 * ignored.When SHA384 is selected, the content of SHA_IODATAR12 to
 * SHA_IODATAR15 must be ignored.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_IODATAR15 . IODATA15
 */
#define  VTSS_F_SHA_SHA_IODATAR15_IODATA15(x)  (x)
#define  VTSS_M_SHA_SHA_IODATAR15_IODATA15     0xffffffff
#define  VTSS_X_SHA_SHA_IODATAR15_IODATA15(x)  (x)


/**
 * \brief SHA Write Protection Mode Register
 *
 * \details
 * Register: \a SHA:SHA_REGS:SHA_WPMR
 */
#define VTSS_SHA_SHA_WPMR                    VTSS_IOREG(VTSS_TO_SHA,0x39)

/**
 * \brief
 * WPKEY: Write Protection KeyValue	   Name
 * Description0x534841 PASSWD	 Writing any other value in this field
 * aborts the write operation of the WPEN,WPITEN,WPCREN
 *		    bits. Always reads as 0.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . WPKEY
 */
#define  VTSS_F_SHA_SHA_WPMR_WPKEY(x)         VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_SHA_SHA_WPMR_WPKEY            VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_SHA_SHA_WPMR_WPKEY(x)         VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * ACTION: Action on Abnormal Event DetectionValue   Name
 *	    Description0	  REPORT_ONLY		No action (stop or
 * clear key) is performed when one of WPVS,CGD,SEQE, or SWE flag is
 *					      set.1	     LOCK_WPVS_SWE
 *     If a processing is in progress when the SHA_WPSR.WPVS/SWE event
 * detection						       occurs, the
 * current processing is ended normally but no other processing is started
 * while						      a
 * SHA_CR.UNLOCK command is issued.2	       LOCK_CGD_SEQE	  If a
 * processing is in progress when the SHA_WPSR.CGD/SEQE event detection
 * occurs,						       the current
 * processing is ended normally but no other processing is started while a
 *
 * SHA_CR.UNLOCK command is issued.3		LOCK_ANY_EV	      If a
 * processing is in progress when the SHA_WPSR.WPVS/CGD/SEQE/SWE events
 *						      detection occurs, the
 * current processing is ended normally but no other processing is
 *					    started while a SHA_CR.UNLOCK
 * command is issued.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . ACTION
 */
#define  VTSS_F_SHA_SHA_WPMR_ACTION(x)        VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_SHA_SHA_WPMR_ACTION           VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_SHA_SHA_WPMR_ACTION(x)        VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * FIRSTE: First Error Report Enable0: The last write protection violation
 * source is reported in SHA_WPSR.WPVSRC and the last software control
 * error type isreported in SHA_WPSR.SWETYP. The SHA_ISR.SECE_ISR flag is
 * set at the first error occurrence within a series.1: Only the first
 * write protection violation source is reported in SHA_WPSR.WPVSRC and
 * only the first software controlerror type is reported in
 * SHA_WPSR.SWETYP. The SHA_ISR.SECE_ISR flag is set at the first error
 * occurrence within a series.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . FIRSTE
 */
#define  VTSS_F_SHA_SHA_WPMR_FIRSTE(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SHA_SHA_WPMR_FIRSTE           VTSS_BIT(4)
#define  VTSS_X_SHA_SHA_WPMR_FIRSTE(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * WPCREN: Write Protection Control Enable0: Disables the write protection
 * on control register if WPKEY corresponds to 0x534841 (SHA in ASCII).1:
 * Enables the write protection on control register if WPKEY corresponds to
 * 0x534841 (SHA in ASCII).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . WPCREN
 */
#define  VTSS_F_SHA_SHA_WPMR_WPCREN(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SHA_SHA_WPMR_WPCREN           VTSS_BIT(2)
#define  VTSS_X_SHA_SHA_WPMR_WPCREN(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interruption Enable0: Disables the write
 * protection on interrupt registers if WPKEY corresponds to 0x534841 (SHA
 * in ASCII).1: Enables the write protection on interrupt registers if
 * WPKEY corresponds to 0x534841 (SHA in ASCII).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . WPITEN
 */
#define  VTSS_F_SHA_SHA_WPMR_WPITEN(x)        VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SHA_SHA_WPMR_WPITEN           VTSS_BIT(1)
#define  VTSS_X_SHA_SHA_WPMR_WPITEN(x)        VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Configuration Enable0: Disables the write
 * protection on configuration registers if WPKEY corresponds to 0x534841
 * (SHA in ASCII).1: Enables the write protection on configuration
 * registers if WPKEY corresponds to 0x534841 (SHA in ASCII).See Section
 * 5.10.2 Register Write Protection for the list of registers that can be
 * write-protected.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPMR . WPEN
 */
#define  VTSS_F_SHA_SHA_WPMR_WPEN(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_WPMR_WPEN             VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_WPMR_WPEN(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief SHA Write Protection Status Register
 *
 * \details
 * Register: \a SHA:SHA_REGS:SHA_WPSR
 */
#define VTSS_SHA_SHA_WPSR                    VTSS_IOREG(VTSS_TO_SHA,0x3a)

/**
 * \brief
 * ECLASS: Software Error Class (cleared on read)0 (WARNING): An abnormal
 * access that does not affect system functionality1 (ERROR): An access is
 * performed into key, input data, control registers while the SHA is
 * performing an encryption/decryption or a start is request by software or
 * DMA while the key is not fully configured.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . ECLASS
 */
#define  VTSS_F_SHA_SHA_WPSR_ECLASS(x)        VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SHA_SHA_WPSR_ECLASS           VTSS_BIT(31)
#define  VTSS_X_SHA_SHA_WPSR_ECLASS(x)        VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * SWETYP: Software Error Type (cleared on read)Value  Name
 * Description0 	READ_WO       A write-only register has been read
 * (Warning).1	       WRITE_RO      SHA is enabled and a write access has
 * been performed on a read-only register (Warning).2	      UNDEF_RW
 * Access to an undefined address (Warning).3	      CTRL_START  SHA is
 * locked and a start command with SHA_CR.START has been performed.4
 *  AUTO_START	SHA is locked and a tentative automatic start has been
 * performed by writing input data
 * registers (SHA_MR.SMOD>0).5	       BAD_START      SHA is not locked and
 * a start command with SHA_CR.START has been performed
 *		    whereas Start mode is automatic (SHA_MR.SMOD>0)
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . SWETYP
 */
#define  VTSS_F_SHA_SHA_WPSR_SWETYP(x)        VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_SHA_SHA_WPSR_SWETYP           VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_SHA_SHA_WPSR_SWETYP(x)        VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * WPVSRC: Write Protection Violation SourceWhen WPVS=1, WPVSRC indicates
 * the register address offset at which a write access has been
 * attempted.When WPVS=0 and SWE=1, WPVSRC reports the address of the
 * incorrect software access. As soon as WPVS=1,WPVSRC returns the address
 * of the write-protected violation.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . WPVSRC
 */
#define  VTSS_F_SHA_SHA_WPSR_WPVSRC(x)        VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_SHA_SHA_WPSR_WPVSRC           VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_SHA_SHA_WPSR_WPVSRC(x)        VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * SWE: Software Control Error (cleared on read)0: No software error has
 * occurred since the last read of SHA_WPSR.1: A software error has
 * occurred since the last read of SHA_WPSR. The field SWETYP details the
 * type of software error;the associated incorrect software access is
 * reported in the field WPVSRC (if WPVS=0).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . SWE
 */
#define  VTSS_F_SHA_SHA_WPSR_SWE(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SHA_SHA_WPSR_SWE              VTSS_BIT(3)
#define  VTSS_X_SHA_SHA_WPSR_SWE(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SEQE: Internal Sequencer Error (cleared on read)0: No peripheral
 * internal sequencer error has occurred since the last read of SHA_WPSR.1:
 * A peripheral internal sequencer error has occurred since the last read
 * of SHA_WPSR. This flag can only be set underabnormal operating
 * conditions.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . SEQE
 */
#define  VTSS_F_SHA_SHA_WPSR_SEQE(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SHA_SHA_WPSR_SEQE             VTSS_BIT(2)
#define  VTSS_X_SHA_SHA_WPSR_SEQE(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CGD: Clock Glitch Detected (cleared on read)0: No clock glitch has
 * occurred since the last read of SHA_WPSR. Under normal operating
 * conditions, this bit is alwayscleared.1: A clock glitch has occurred
 * since the last read of SHA_WPSR. This flag can only be set in case of an
 * abnormal clock signalwaveform (glitch).
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . CGD
 */
#define  VTSS_F_SHA_SHA_WPSR_CGD(x)           VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SHA_SHA_WPSR_CGD              VTSS_BIT(1)
#define  VTSS_X_SHA_SHA_WPSR_CGD(x)           VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPVS: Write Protection Violation Status (cleared on read)0: No write
 * protect violation has occurred since the last read of SHA_WPSR.1: A
 * write protect violation has occurred since the last read of SHA_WPSR.
 * The address offset of the violated register isreported into field
 * WPVSRC.
 *
 * \details
 * Field: ::VTSS_SHA_SHA_WPSR . WPVS
 */
#define  VTSS_F_SHA_SHA_WPSR_WPVS(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SHA_SHA_WPSR_WPVS             VTSS_BIT(0)
#define  VTSS_X_SHA_SHA_WPSR_WPVS(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_SHA_H_ */
