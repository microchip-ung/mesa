// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_TRNG_H_
#define _VTSS_LAGUNA_REGS_TRNG_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a TRNG
 *
 * TRNG registers
 *
 ***********************************************************************/

/**
 * Register Group: \a TRNG:TRNG_REGS
 *
 * True Random Number Generator (TRNG) User Interface
 */


/**
 * \brief TRNG Control Register
 *
 * \details
 * This register can only be written if the WPCREN bit is cleared in the
 * TRNG Write Protection Mode Register.
 *
 * Register: \a TRNG:TRNG_REGS:TRNG_CR
 */
#define VTSS_TRNG_TRNG_CR                    VTSS_IOREG(VTSS_TO_TRNG,0x0)

/**
 * \brief
 * WAKEY: Register Write Access KeyValue	Name
 * Description0x524E47 PASSWD Writing any other value in this field aborts
 * the write operation.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_CR . WAKEY
 */
#define  VTSS_F_TRNG_TRNG_CR_WAKEY(x)         VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_TRNG_TRNG_CR_WAKEY            VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_TRNG_TRNG_CR_WAKEY(x)         VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * ENABLE: Enable TRNG to Provide Random Values0: Disables the TRNG if
 * 0x524E47 (RNG in ASCII) is written in WAKEY field at the same time.1:
 * Enables the TRNG if 0x524E47 (RNG in ASCII) is written in WAKEY field at
 * the same time.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_CR . ENABLE
 */
#define  VTSS_F_TRNG_TRNG_CR_ENABLE(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_CR_ENABLE           VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_CR_ENABLE(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Mode Register
 *
 * \details
 * This register can only be written if the WPEN bit is cleared in the TRNG
 * Write Protection Mode Register.
 *
 * Register: \a TRNG:TRNG_REGS:TRNG_MR
 */
#define VTSS_TRNG_TRNG_MR                    VTSS_IOREG(VTSS_TO_TRNG,0x1)

/**
 * \brief
 * DIFF: Minimum Hamming Distance0 (DISABLED): Delivers a new random sample
 * without condition with the previous sample (unless HD=1).1(ENABLED):
 * Delivers a new random sample only if it differs from the previous
 * delivered sample (unless HD=1).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_MR . DIFF
 */
#define  VTSS_F_TRNG_TRNG_MR_DIFF(x)          VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TRNG_TRNG_MR_DIFF             VTSS_BIT(7)
#define  VTSS_X_TRNG_TRNG_MR_DIFF(x)          VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * HDSEL: Minimum Hamming Distance0 (TWO): Two consecutive random samples
 * have a minimum Hamming distance of 2.1 (FOUR): Two consecutive random
 * samples have a minimum Hamming distance of 4.2 (EIGHT): Two consecutive
 * random samples have a minimum Hamming distance of 8.3 (SIXTEEN): Two
 * consecutive random samples have a minimum Hamming distance of 16.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_MR . HDSEL
 */
#define  VTSS_F_TRNG_TRNG_MR_HDSEL(x)         VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_TRNG_TRNG_MR_HDSEL            VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_TRNG_TRNG_MR_HDSEL(x)         VTSS_EXTRACT_BITFIELD(x,2,2)

/**
 * \brief
 * HD: Hamming Distance Check0 (DISABLED): Delivers a new random sample
 * without condition with the previous sample (unless DIFF=1).1 (ENABLED):
 * Delivers a new random sample only if it meets a minimum Hamming distance
 * with the previous deliveredsample (the HDSEL field defines the minimum
 * distance). When HD=1, DIFF has no effect.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_MR . HD
 */
#define  VTSS_F_TRNG_TRNG_MR_HD(x)            VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_MR_HD               VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_MR_HD(x)            VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * HALFR: Half Rate Enable0: Maximum stream rate provided.1: Half maximum
 * stream rate provided if the peripheral clock frequency is above 100 MHz.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_MR . HALFR
 */
#define  VTSS_F_TRNG_TRNG_MR_HALFR(x)         VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_MR_HALFR            VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_MR_HALFR(x)         VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Private Key Bus Control Register
 *
 * \details
 * This register can only be written if the WPCREN bit is cleared in the
 * TRNG Write Protection Mode Register.
 *
 * Register: \a TRNG:TRNG_REGS:TRNG_PKBCR
 */
#define VTSS_TRNG_TRNG_PKBCR                 VTSS_IOREG(VTSS_TO_TRNG,0x2)

/**
 * \brief
 * WAKEY: Register Write Access KeyValue       Name
 * Description0x524B	PASSWD	  Writing any other value in this field
 * aborts the write operation.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_PKBCR . WAKEY_PKBCR
 */
#define  VTSS_F_TRNG_TRNG_PKBCR_WAKEY_PKBCR(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_TRNG_TRNG_PKBCR_WAKEY_PKBCR     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_TRNG_TRNG_PKBCR_WAKEY_PKBCR(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * KLENGTH: Key LengthLength-1 in 32-bit words of the key(s) to be directly
 * loaded from the TRNG into the private key internal registers of the
 * privatekey bus target KTARGET.Note: Example: for one 64-bit key to be
 * loaded, KLENGTH must be written to 1. For 128-bit keys, KLENGTH must be
 * written to 3.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_PKBCR . KLENGTH
 */
#define  VTSS_F_TRNG_TRNG_PKBCR_KLENGTH(x)    VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_TRNG_TRNG_PKBCR_KLENGTH       VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_TRNG_TRNG_PKBCR_KLENGTH(x)    VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * KTARGET: Key Bus TargetPrivate key bus target to be loaded from the
 * TRNG.Value	      Name			  Description0
 * KB_TARGET_0_ID     Selects the KB_TARGET_0.1 	 KB_TARGET_1_ID
 * Selects the KB_TARGET_1.2	      KB_TARGET_2_ID	 Selects the
 * KB_TARGET_2.3	  KB_TARGET_3_ID     Selects the KB_TARGET_3.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_PKBCR . KTARGET
 */
#define  VTSS_F_TRNG_TRNG_PKBCR_KTARGET(x)    VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_TRNG_TRNG_PKBCR_KTARGET       VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_TRNG_TRNG_PKBCR_KTARGET(x)    VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * KID: Key ID (Must be Always Written to 0)Private Key ID of the targeted
 * private key bus target KTARGET to be loaded from the TRNG.Value Name
 * Description0 SECURE_KEY TrustZone Secure Key access.(1)1 NOT_SECURE_KEY
 * TrustZone Not Secure Key access.(1)Note: 1. TrustZone access protection
 * is only done at the selected key bus target according to its TrustZone
 * configuration.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_PKBCR . KID
 */
#define  VTSS_F_TRNG_TRNG_PKBCR_KID(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_PKBCR_KID           VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_PKBCR_KID(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Interrupt Enable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TRNG Write Protection Mode Register.
 *
 * Access: Write-only
 *
 * Register: \a TRNG:TRNG_REGS:TRNG_IER
 */
#define VTSS_TRNG_TRNG_IER                   VTSS_IOREG(VTSS_TO_TRNG,0x4)

/**
 * \brief
 * APHT: Adaptive Proportional Health Test Failure Detection (cleared on
 * read)0: No effect.1: Enables the corresponding interrupt
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IER . APHT
 */
#define  VTSS_F_TRNG_TRNG_IER_APHT(x)         VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_IER_APHT            VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_IER_APHT(x)         VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RCHT: Repetitive Count Health Test Failure Detection (cleared on read)0:
 * No effect.1: Enables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IER . RCHT
 */
#define  VTSS_F_TRNG_TRNG_IER_RCHT(x)         VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_IER_RCHT            VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_IER_RCHT(x)         VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * EOTPKB: End Of Transfer on Private Key Bus Interrupt Enable0: No
 * effect.1: Enables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IER . EOTPKB
 */
#define  VTSS_F_TRNG_TRNG_IER_EOTPKB(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_IER_EOTPKB          VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_IER_EOTPKB(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Enable0: No effect.1:
 * Enables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IER . SECE
 */
#define  VTSS_F_TRNG_TRNG_IER_SECE(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_IER_SECE            VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_IER_SECE(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Enable0: No effect.1: Enables the
 * corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IER . DATRDY
 */
#define  VTSS_F_TRNG_TRNG_IER_DATRDY(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_IER_DATRDY          VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_IER_DATRDY(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Interrupt Disable Register
 *
 * \details
 * This register can only be written if the WPITEN bit is cleared in the
 * TRNG Write Protection Mode Register.
 * Access: Write-only
 *
 * Register: \a TRNG:TRNG_REGS:TRNG_IDR
 */
#define VTSS_TRNG_TRNG_IDR                   VTSS_IOREG(VTSS_TO_TRNG,0x5)

/**
 * \brief
 * APHT: Adaptive Proportional Health Test Failure Detection (cleared on
 * read)0: No effect.1: Disables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IDR . APHT_IDR
 */
#define  VTSS_F_TRNG_TRNG_IDR_APHT_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_IDR_APHT_IDR        VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_IDR_APHT_IDR(x)     VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RCHT: Repetitive Count Health Test Failure Detection (cleared on read)0:
 * No effect.1: Disables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IDR . RCHT_IDR
 */
#define  VTSS_F_TRNG_TRNG_IDR_RCHT_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_IDR_RCHT_IDR        VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_IDR_RCHT_IDR(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * EOTPKB: End Of Transfer on Private Key Bus Interrupt Disable0: No
 * effect.1: Disables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IDR . EOTPKB_IDR
 */
#define  VTSS_F_TRNG_TRNG_IDR_EOTPKB_IDR(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_IDR_EOTPKB_IDR      VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_IDR_EOTPKB_IDR(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Disable0: No effect.1:
 * Disables the corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IDR . SECE_IDR
 */
#define  VTSS_F_TRNG_TRNG_IDR_SECE_IDR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_IDR_SECE_IDR        VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_IDR_SECE_IDR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Disable0: No effect.1: Disables the
 * corresponding interrupt.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IDR . DATRDY_IDR
 */
#define  VTSS_F_TRNG_TRNG_IDR_DATRDY_IDR(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_IDR_DATRDY_IDR      VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_IDR_DATRDY_IDR(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Interrupt Mask Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_IMR
 */
#define VTSS_TRNG_TRNG_IMR                   VTSS_IOREG(VTSS_TO_TRNG,0x6)

/**
 * \brief
 * APHT: Adaptive Proportional Health Test Failure Detection (cleared on
 * read)0: The corresponding interrupt is not enabled.1: The corresponding
 * interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IMR . APHT_IMR
 */
#define  VTSS_F_TRNG_TRNG_IMR_APHT_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_IMR_APHT_IMR        VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_IMR_APHT_IMR(x)     VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RCHT: Repetitive Count Health Test Failure Detection (cleared on read)0:
 * The corresponding interrupt is not enabled.1: The corresponding
 * interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IMR . RCHT_IMR
 */
#define  VTSS_F_TRNG_TRNG_IMR_RCHT_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_IMR_RCHT_IMR        VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_IMR_RCHT_IMR(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * EOTPKB: End Of Transfer on Private Key Bus Interrupt Mask0: The
 * corresponding interrupt is not enabled.1: The corresponding interrupt is
 * enabled.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IMR . EOTPKB_IMR
 */
#define  VTSS_F_TRNG_TRNG_IMR_EOTPKB_IMR(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_IMR_EOTPKB_IMR      VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_IMR_EOTPKB_IMR(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * SECE: Security and/or Safety Event Interrupt Mask0: The corresponding
 * interrupt is not enabled.1: The corresponding interrupt is enabled
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IMR . SECE_IMR
 */
#define  VTSS_F_TRNG_TRNG_IMR_SECE_IMR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_IMR_SECE_IMR        VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_IMR_SECE_IMR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DATRDY: Data Ready Interrupt Mask0: The corresponding interrupt is not
 * enabled.1: The corresponding interrupt is enabled.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_IMR . DATRDY_IMR
 */
#define  VTSS_F_TRNG_TRNG_IMR_DATRDY_IMR(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_IMR_DATRDY_IMR      VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_IMR_DATRDY_IMR(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Interrupt Status Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_ISR
 */
#define VTSS_TRNG_TRNG_ISR                   VTSS_IOREG(VTSS_TO_TRNG,0x7)

/**
 * \brief
 * APHT: Adaptive Proportional Health Test Failure Detection (cleared on
 * read)0: No loss of entropy detected in the TRNG noise source since the
 * last read of the Interrupt Status register.1: A significant loss of
 * entropy has been detected in the TRNG noise source since the last read
 * of the Interrupt Statusregister.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ISR . APHT_ISR
 */
#define  VTSS_F_TRNG_TRNG_ISR_APHT_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_ISR_APHT_ISR        VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_ISR_APHT_ISR(x)     VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * RCHT: Repetitive Count Health Test Failure Detection (cleared on read)0:
 * No important failure detected in the TRNG noise source since the last
 * read of the Interrupt Status register.1: An important failure has been
 * detected in the TRNG noise source since the last read of the Interrupt
 * Status register.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ISR . RCHT_ISR
 */
#define  VTSS_F_TRNG_TRNG_ISR_RCHT_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_ISR_RCHT_ISR        VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_ISR_RCHT_ISR(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * EOTPKB: End Of Transfer on Private Key Bus (cleared on read)0: No
 * private key bus transfer has ended since the last read of the Interrupt
 * Status Register.1: The private key bus transfer has ended.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ISR . EOTPKB_ISR
 */
#define  VTSS_F_TRNG_TRNG_ISR_EOTPKB_ISR(x)   VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_ISR_EOTPKB_ISR      VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_ISR_EOTPKB_ISR(x)   VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * SECE: Security and/or Safety Event (cleared on read)0: No security or
 * safety event occurred.1: One or more safety or security event occurred
 * since the last read of TRNG_ISR. For details on the event, see TRNGWrite
 * Protection Status Register.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ISR . SECE_ISR
 */
#define  VTSS_F_TRNG_TRNG_ISR_SECE_ISR(x)     VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_ISR_SECE_ISR        VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_ISR_SECE_ISR(x)     VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * DATRDY: Data Ready (cleared on read or when TRNG_ODATA is read)0: Output
 * data is not valid or TRNG is disabled.1: New random value has been
 * completed since the last read of TRNG_ISR or TRNG_ODATA.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ISR . DATRDY_ISR
 */
#define  VTSS_F_TRNG_TRNG_ISR_DATRDY_ISR(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_ISR_DATRDY_ISR      VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_ISR_DATRDY_ISR(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Health Test Mode Register
 *
 * \details
 * Access: Read/Write
 * This register can only be written if the WPEN bit is cleared in the TRNG
 * Write Protection Mode Register.

 *
 * Register: \a TRNG:TRNG_REGS:TRNG_HTMR
 */
#define VTSS_TRNG_TRNG_HTMR                  VTSS_IOREG(VTSS_TO_TRNG,0xc)

/**
 * \brief
 * THRESHOLD: Failure Detection Threshold for SP800-90B Adaptive Proportion
 * Test
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_HTMR . THRESHOLD
 */
#define  VTSS_F_TRNG_TRNG_HTMR_THRESHOLD(x)   VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_TRNG_TRNG_HTMR_THRESHOLD      VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_TRNG_TRNG_HTMR_THRESHOLD(x)   VTSS_EXTRACT_BITFIELD(x,16,10)

/**
 * \brief
 * APSRCSEL: Adaptive Proportional Source Selection0 (EXTPHASEDIFF):
 * Selects the random value produced every 84/168 clock cycles (mix of
 * LFSRs).1 (RINGPHASEDIFF): Selects the phase difference of the first ring
 * oscillator as the data to analyze by adaptive proportionaltest. The
 * phase of the first ring oscillator is sampled every 84/168 clock cycles
 * and the difference is created withthe previous period.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_HTMR . APSRCSEL
 */
#define  VTSS_F_TRNG_TRNG_HTMR_APSRCSEL(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_HTMR_APSRCSEL       VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_HTMR_APSRCSEL(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * MPERIOD: Monitoring Window for SP800-90B Adaptive Proportion Test0
 * (W512): Selects the window monitoring period as 512 noise source
 * samples.1 (W1024): Selects the window monitoring period as 1024 noise
 * source samples.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_HTMR . MPERIOD
 */
#define  VTSS_F_TRNG_TRNG_HTMR_MPERIOD(x)     VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_HTMR_MPERIOD        VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_HTMR_MPERIOD(x)     VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Fault Injection Register
 *
 * \details
 * Access: Write-only
 * This register can only be written if the WPCREN bit is cleared in the
 * TRNG Write Protection Mode Register.

 *
 * Register: \a TRNG:TRNG_REGS:TRNG_FIR
 */
#define VTSS_TRNG_TRNG_FIR                   VTSS_IOREG(VTSS_TO_TRNG,0x10)

/**
 * \brief
 * FIKEY: Fault Injection Access KeyValue	   Name
 * Description0x544649	  PASSWD	 Writing any other value in this
 * field aborts the write operation.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . FIKEY
 */
#define  VTSS_F_TRNG_TRNG_FIR_FIKEY(x)        VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_TRNG_TRNG_FIR_FIKEY           VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_TRNG_TRNG_FIR_FIKEY(x)        VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * NSFHT: Noise Source Failure for Health Test0 (NONE): No effect.1
 * (FAIL_ONCE): Injects a fault on the noise source (if TRNG_CR.ENABLE=1,
 * TRNG_ISR.RCHT=0 andTRNG_ISR.APHT=0) for a period that will automatically
 * end as soon as TRNG_ISR.APHT=1 and TRNG_ISR.RCHT=1.For security reasons,
 * any further command (NSFHT=1) will not be processed (no effect) until
 * the next system reset.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . NSFHT
 */
#define  VTSS_F_TRNG_TRNG_FIR_NSFHT(x)        VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TRNG_TRNG_FIR_NSFHT           VTSS_BIT(7)
#define  VTSS_X_TRNG_TRNG_FIR_NSFHT(x)        VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * FSEQE: Single Fault for TRNG_MR0 (NO_EFFECT): No effect.1
 * (INJECT_CLEAR): Injects a single fault on TRNG_MR if the TRNG is
 * disabled (for security reasons). As a consequence,the flag
 * TRNG_WPSR.SEQE raises and the flag TRNG_ISR.SECE=1. Clears the fault if
 * it has been previously injected.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . FSEQE
 */
#define  VTSS_F_TRNG_TRNG_FIR_FSEQE(x)        VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TRNG_TRNG_FIR_FSEQE           VTSS_BIT(5)
#define  VTSS_X_TRNG_TRNG_FIR_FSEQE(x)        VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * F4: Single Fault for TRNG Interrupt Mask Bit (TRNG_IMR.DATRDY)0: Clears
 * the fault. The flag TRNG_WPSR.SDEE is automatically cleared.1: Injects a
 * single fault on the reinforced safety memory cell for the
 * TRNG_IMR.WPCREN bit if 0x544649 ( "TFI" in ASCII) iswritten in the FIKEY
 * field at the same time. The TRNG remains in the same state, the flag
 * TRNG_ISR.SECE=1 and the flagTRNG_WPSR.SDEE=1.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . F4
 */
#define  VTSS_F_TRNG_TRNG_FIR_F4(x)           VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_FIR_F4              VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_FIR_F4(x)           VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * F3: Single Fault for TRNG Write Protection Bit (TRNG_WPMR.WPCREN)0:
 * Clears the fault. The flag TRNG_WPSR.SDEE is automatically cleared if no
 * other fault exists.1: Injects a single fault on the reinforced safety
 * memory cell for the TRNG_WPMR.WPEN bit if 0x544649 ("TFI" in ASCII)
 * iswritten in the FIKEY field at the same time. The TRNG Control register
 * remains protected, the flag TRNG_ISR.SECE=1and the flag
 * TRNG_WPSR.SDEE=1.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . F3
 */
#define  VTSS_F_TRNG_TRNG_FIR_F3(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_FIR_F3              VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_FIR_F3(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * F2: Single Fault for TRNG Write Protection Bit (TRNG_WPMR.WPITEN)0:
 * Clears the fault. The flag TRNG_WPSR.SDEE is automatically cleared if no
 * other fault exists.1: Injects a single fault on the reinforced safety
 * memory cell for the TRNG_WPMR.WPITEN bit if 0x544649  ( "TFI" in
 * ASCII)is written in the FIKEY field at the same time. The TRNG
 * protection remains active for interrupt registers, the
 * flagTRNG_ISR.SECE=1 and the flag TRNG_WPSR.SDEE=1.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . F2
 */
#define  VTSS_F_TRNG_TRNG_FIR_F2(x)           VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_FIR_F2              VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_FIR_F2(x)           VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * F1: Single Fault for TRNG Write Protection Bit (TRNG_WPMR.WPEN)0: Clears
 * the fault. The flag TRNG_WPSR.SDEE is automatically cleared if no other
 * fault exists.1: Injects a single fault on the reinforced safety memory
 * cell for the TRNG_WPMR.WPEN bit if 0x544649 ("TFI" in ASCII) iswritten
 * in the FIKEY field at the same time. The TRNG protection remains active
 * for Mode registers, the flagTRNG_ISR.SECE=1 and the flag
 * TRNG_WPSR.SDEE=1.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . F1
 */
#define  VTSS_F_TRNG_TRNG_FIR_F1(x)           VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_FIR_F1              VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_FIR_F1(x)           VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * F0: Single Fault for TRNG Enable Bit (TRNG_CR.ENABLE)0: Clears the
 * fault. The flag TRNG_WPSR.SDEE is automatically cleared.1: Injects a
 * single fault on the reinforced safety memory cell for the TRNG_CR.ENABLE
 * bit if 0x544649 ("TFI" in ASCII) iswritten in the FIKEY field at the
 * same time. The TRNG remains in the same state, the flag TRNG_ISR.SECE=1
 * and the flagTRNG_WPSR.SDEE=1.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_FIR . F0
 */
#define  VTSS_F_TRNG_TRNG_FIR_F0(x)           VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_FIR_F0              VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_FIR_F0(x)           VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Output Data Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_ODATA
 */
#define VTSS_TRNG_TRNG_ODATA                 VTSS_IOREG(VTSS_TO_TRNG,0x14)

/**
 * \brief
 * ODATA: Output DataThe 32-bit Output Data register contains the 32-bit
 * random data.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_ODATA . ODATA
 */
#define  VTSS_F_TRNG_TRNG_ODATA_ODATA(x)      (x)
#define  VTSS_M_TRNG_TRNG_ODATA_ODATA         0xffffffff
#define  VTSS_X_TRNG_TRNG_ODATA_ODATA(x)      (x)


/**
 * \brief TRNG Write Protection Mode Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_WPMR
 */
#define VTSS_TRNG_TRNG_WPMR                  VTSS_IOREG(VTSS_TO_TRNG,0x39)

/**
 * \brief
 * WPKEY: Write Protection KeyValue	       Name
 * Description0x524E47	   PASSWD	       Writing any other value in
 * this field aborts the write operation of bits WPEN, WPITEN and
 *					   WPCREN.
 *			     Always reads as 0.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . WPKEY
 */
#define  VTSS_F_TRNG_TRNG_WPMR_WPKEY(x)       VTSS_ENCODE_BITFIELD(x,8,24)
#define  VTSS_M_TRNG_TRNG_WPMR_WPKEY          VTSS_ENCODE_BITMASK(8,24)
#define  VTSS_X_TRNG_TRNG_WPMR_WPKEY(x)       VTSS_EXTRACT_BITFIELD(x,8,24)

/**
 * \brief
 * LCKCREN: Write Protection Lock Enable for Control Registers0: No
 * effect.1: Locks the write access to the WPCREN bit until the next system
 * reset. WPCREN must be set to perform the action.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . LCKCREN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_LCKCREN(x)     VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TRNG_TRNG_WPMR_LCKCREN        VTSS_BIT(7)
#define  VTSS_X_TRNG_TRNG_WPMR_LCKCREN(x)     VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * LCKITEN: Write Protection Lock Enable for Interrupt Register0: No
 * effect.1: Locks the write access to the WPITEN bit until the next system
 * reset. WPITEN must be set to perform the action.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . LCKITEN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_LCKITEN(x)     VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TRNG_TRNG_WPMR_LCKITEN        VTSS_BIT(6)
#define  VTSS_X_TRNG_TRNG_WPMR_LCKITEN(x)     VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * LCKWPEN: Write Protection Lock Enable for Configuration Register0: No
 * effect.1: Locks the write access to the WPEN bit until the next system
 * reset. WPEN must be set to perform the action.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . LCKWPEN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_LCKWPEN(x)     VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TRNG_TRNG_WPMR_LCKWPEN        VTSS_BIT(5)
#define  VTSS_X_TRNG_TRNG_WPMR_LCKWPEN(x)     VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * FIRSTE: First Error Report Enable0: The last write protection violation
 * source is reported in TRNG_WPSR.WPVSRC and the last software control
 * error typeis reported in TRNG_WPSR.SWETYP. The TRNG_ISR.SECE_ISR flag is
 * set at the first error occurrence within a series.1: Only the first
 * write protection violation source is reported in TRNG_WPSR.WPVSRC and
 * only the first software controlerror type is reported in
 * TRNG_WPSR.SWETYP. The TRNG_ISR.SECE_ISR flag is set at the first error
 * occurrence within aseries.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . FIRSTE
 */
#define  VTSS_F_TRNG_TRNG_WPMR_FIRSTE(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_WPMR_FIRSTE         VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_WPMR_FIRSTE(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * WPCREN: Write Protection Control Enable0: Disables the write protection
 * on control register if WPKEY corresponds to 0x524E47 (RNG in ASCII).1:
 * Enables the write protection on control register if WPKEY corresponds to
 * 0x524E47 (RNG in ASCII).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . WPCREN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_WPCREN(x)      VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_WPMR_WPCREN         VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_WPMR_WPCREN(x)      VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * WPITEN: Write Protection Interrupt Enable0: Disables the write
 * protection on interrupt registers if WPKEY corresponds to 0x524E47 (RNG
 * in ASCII).1: Enables the write protection on interrupt registers if
 * WPKEY corresponds to 0x524E47 (RNG in ASCII).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . WPITEN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_WPITEN(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_WPMR_WPITEN         VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_WPMR_WPITEN(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPEN: Write Protection Enable0: Disables the write protection if WPKEY
 * corresponds to 0x524E47 (RNG in ASCII).1: Enables the write protection
 * if WPKEY corresponds to 0x524E47 (RNG in ASCII).See Section 6.3 Register
 * Write Protection for the list of registers that can be write-protected.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPMR . WPEN
 */
#define  VTSS_F_TRNG_TRNG_WPMR_WPEN(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_WPMR_WPEN           VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_WPMR_WPEN(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Write Protection Status Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_WPSR
 */
#define VTSS_TRNG_TRNG_WPSR                  VTSS_IOREG(VTSS_TO_TRNG,0x3a)

/**
 * \brief
 * ECLASS: Software Error Class (cleared on read)Value Name Description0
 * WARNING An abnormal access that does not affect system functionality.1
 * ERRORReading TRNG_ODATA when TRNG was disabled or TRNG used for private
 * key bustransfer. TRNG does not provide a random value.Writing to the
 * PKB_CTRL register while a private key bus transfer is ongoing doesnot
 * launch a new private key bus transfer.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . ECLASS
 */
#define  VTSS_F_TRNG_TRNG_WPSR_ECLASS(x)      VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_TRNG_TRNG_WPSR_ECLASS         VTSS_BIT(31)
#define  VTSS_X_TRNG_TRNG_WPSR_ECLASS(x)      VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * SWETYP: Software Error Type (cleared on read)Value Name Description0
 * READ_WO TRNG is enabled and a write-only register has been read
 * (Warning).1 WRITE_RO TRNG is enabled and a write access has been
 * performed on a read-only register (Warning).2 UNDEF_RW Access to an
 * undefined address.3 TRNG_DISThe TRNG_ODATA register was read when TRNG
 * was disabled or TRNG used for private keybus transfer (Error).4
 * PKB_BUSYA write access to the PKB_CTRL register has been attempted
 * during a private key bus transfer(Error).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . SWETYP
 */
#define  VTSS_F_TRNG_TRNG_WPSR_SWETYP(x)      VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_TRNG_TRNG_WPSR_SWETYP         VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_TRNG_TRNG_WPSR_SWETYP(x)      VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * WPVSRC: Write Protection Violation Source (cleared on read)When WPVS =
 * 1, WPVSRC indicates the register address offset at which a write access
 * has been attempted.When WPVS=0 and SWE=1, WPVSRC reports the address of
 * the incorrect software access. As soon as WPVS=1,WPVSRC returns the
 * address of the write-protected violation.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . WPVSRC
 */
#define  VTSS_F_TRNG_TRNG_WPSR_WPVSRC(x)      VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_TRNG_TRNG_WPSR_WPVSRC         VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_TRNG_TRNG_WPSR_WPVSRC(x)      VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * SDEE: Single or Dual Event Error (cleared by reconfiguring the faulty
 * registers or by clearing the error viaTRNG_FIR)0: No single or dual
 * error detected in TRNG_CR.ENABLE, TRNG_WPMR{WPEN,WPITEN,WPCREN} and
 * TRNG_IMRbits.1: Single or dual error detected in TRNG_CR.ENABLE,
 * TRNG_WPMR{WPEN,WPITEN,WPCREN} and TRNG_IMRbits. If a single error event
 * occurred, the error is filtered and has no effect on TRNG.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . SDEE
 */
#define  VTSS_F_TRNG_TRNG_WPSR_SDEE(x)        VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TRNG_TRNG_WPSR_SDEE           VTSS_BIT(4)
#define  VTSS_X_TRNG_TRNG_WPSR_SDEE(x)        VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * SWE: Software Control Error (cleared on read)0: No software error has
 * occurred since the last read of TRNG_WPSR.1: A software error has
 * occurred since the last read of TRNG_WPSR. The field SWETYP details the
 * type of software error;the associated incorrect software access is
 * reported in the field WPVSRC (if WPVS=0).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . SWE
 */
#define  VTSS_F_TRNG_TRNG_WPSR_SWE(x)         VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TRNG_TRNG_WPSR_SWE            VTSS_BIT(3)
#define  VTSS_X_TRNG_TRNG_WPSR_SWE(x)         VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * SEQE: Internal Sequencer Error (cleared on read)0: No peripheral
 * internal sequencer error has occurred since the last read of
 * TRNG_WPSR.1: A peripheral internal sequencer error has occurred since
 * the last read of TRNG_WPSR. This flag is set under abnormaloperating
 * conditions.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . SEQE
 */
#define  VTSS_F_TRNG_TRNG_WPSR_SEQE(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TRNG_TRNG_WPSR_SEQE           VTSS_BIT(2)
#define  VTSS_X_TRNG_TRNG_WPSR_SEQE(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * CGD: Clock Glitch Detected (cleared on read)0: The clock monitoring
 * circuitry has not been corrupted since the last read of TRNG_WPSR. Under
 * normal operating conditions,this bit is always cleared.1: The clock
 * monitoring circuitry has been corrupted since the last read of
 * TRNG_WPSR. This flag is set in case of abnormalclock signal waveform
 * (glitch).
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . CGD
 */
#define  VTSS_F_TRNG_TRNG_WPSR_CGD(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TRNG_TRNG_WPSR_CGD            VTSS_BIT(1)
#define  VTSS_X_TRNG_TRNG_WPSR_CGD(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * WPVS: Write Protection Violation Status (cleared on read)0: No write
 * protection violation has occurred since the last read of TRNG_WPSR.1: A
 * write protection violation has occurred since the last read of
 * TRNG_WPSR. If this violation is an unauthorized attemptto write a
 * protected register, the associated violation is reported into field
 * WPVSRC.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_WPSR . WPVS
 */
#define  VTSS_F_TRNG_TRNG_WPSR_WPVS(x)        VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TRNG_TRNG_WPSR_WPVS           VTSS_BIT(0)
#define  VTSS_X_TRNG_TRNG_WPSR_WPVS(x)        VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief TRNG Version Register
 *
 * \details
 * Register: \a TRNG:TRNG_REGS:TRNG_VERSION
 */
#define VTSS_TRNG_TRNG_VERSION               VTSS_IOREG(VTSS_TO_TRNG,0x3f)

/**
 * \brief
 * MFN: Metal Fix NumberReserved. Value subject to change. No functionality
 * associated.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_VERSION . MFN
 */
#define  VTSS_F_TRNG_TRNG_VERSION_MFN(x)      VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_TRNG_TRNG_VERSION_MFN         VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_TRNG_TRNG_VERSION_MFN(x)      VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * VERSION: Version of the Hardware ModuleReserved. Value subject to
 * change. No functionality associated. This is the internal version of the
 * macrocell.
 *
 * \details
 * Field: ::VTSS_TRNG_TRNG_VERSION . VERSION
 */
#define  VTSS_F_TRNG_TRNG_VERSION_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_TRNG_TRNG_VERSION_VERSION     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_TRNG_TRNG_VERSION_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_TRNG_H_ */
