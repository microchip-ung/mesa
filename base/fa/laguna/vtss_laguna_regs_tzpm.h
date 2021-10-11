// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_TZPM_H_
#define _VTSS_LAGUNA_REGS_TZPM_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a TZPM
 *
 * Trust Zone Peripheral Manager
 *
 ***********************************************************************/

/**
 * Register Group: \a TZPM:TZPM_REGS
 *
 * TZPM regsisters
 */


/**
 * \brief Trust Zone peripheral manager enable
 *
 * \details
 * Register: \a TZPM:TZPM_REGS:TZPM_EN
 */
#define VTSS_TZPM_TZPM_EN                    VTSS_IOREG(VTSS_TO_TZPM,0x0)

/**
 * \brief
 * TZPM enable configuration. When TZPM is disbaled, NS bit in CPU
 * subsystem is ignored and all transactions  from masters are treated as
 * secure transactions.
 *
 * \details
 *  1: TZPM enabled
 *  0: TZPM disbaled
 *
 * Field: ::VTSS_TZPM_TZPM_EN . TZPM_EN
 */
#define  VTSS_F_TZPM_TZPM_EN_TZPM_EN(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZPM_TZPM_EN_TZPM_EN          VTSS_BIT(0)
#define  VTSS_X_TZPM_TZPM_EN_TZPM_EN(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Trust Zone peripheral manager enable
 *
 * \details
 * Register: \a TZPM:TZPM_REGS:TZPM_KEY
 */
#define VTSS_TZPM_TZPM_KEY                   VTSS_IOREG(VTSS_TO_TZPM,0x1)

/**
 * \brief
 *
 * TZPMKEY: Key preventing TZPCTLx (where x is from 0 to 3) registers to be
 * modified unintentionally by softwareValue Name Description0x12AC4B5D
 * PASSWD
 * Writing any other value in this field aborts the write operation of the
 * TZPCTLx Registers.
 * Always reads as 0.
 *
 * \details
 * Field: ::VTSS_TZPM_TZPM_KEY . TZPMKEY
 */
#define  VTSS_F_TZPM_TZPM_KEY_TZPMKEY(x)      (x)
#define  VTSS_M_TZPM_TZPM_KEY_TZPMKEY         0xffffffff
#define  VTSS_X_TZPM_TZPM_KEY_TZPMKEY(x)      (x)


/**
 * \brief Trust Zone peripheral control 0
 *
 * \details
 * All programmable bits definition in this register
 *
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * All HSS HBRIDGE peripherals added in this register
 *
 * Register: \a TZPM:TZPM_REGS:TZPCTL0
 */
#define VTSS_TZPM_TZPCTL0                    VTSS_IOREG(VTSS_TO_TZPM,0x2)

/**
 * \brief
 * Programmable secure access control for QSPI2 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . QSPI2
 */
#define  VTSS_F_TZPM_TZPCTL0_QSPI2(x)         VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_TZPM_TZPCTL0_QSPI2            VTSS_BIT(13)
#define  VTSS_X_TZPM_TZPCTL0_QSPI2(x)         VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Programmable secure access control for SDMMC target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . SDMMC
 */
#define  VTSS_F_TZPM_TZPCTL0_SDMMC(x)         VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_TZPM_TZPCTL0_SDMMC            VTSS_BIT(12)
#define  VTSS_X_TZPM_TZPCTL0_SDMMC(x)         VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Programmable secure access control for TC1 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . TC1
 */
#define  VTSS_F_TZPM_TZPCTL0_TC1(x)           VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_TZPM_TZPCTL0_TC1              VTSS_BIT(9)
#define  VTSS_X_TZPM_TZPCTL0_TC1(x)           VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Programmable secure access control for MCAN1 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . MCAN1
 */
#define  VTSS_F_TZPM_TZPCTL0_MCAN1(x)         VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_TZPM_TZPCTL0_MCAN1            VTSS_BIT(8)
#define  VTSS_X_TZPM_TZPCTL0_MCAN1(x)         VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Programmable secure access control for MCAN0 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . MCAN0
 */
#define  VTSS_F_TZPM_TZPCTL0_MCAN0(x)         VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_TZPM_TZPCTL0_MCAN0            VTSS_BIT(7)
#define  VTSS_X_TZPM_TZPCTL0_MCAN0(x)         VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Programmable secure access control for TZAESBS target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . TZAESBS
 */
#define  VTSS_F_TZPM_TZPCTL0_TZAESBS(x)       VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_TZPM_TZPCTL0_TZAESBS          VTSS_BIT(6)
#define  VTSS_X_TZPM_TZPCTL0_TZAESBS(x)       VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Programmable secure access control for TZAESBNS target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . TZAESBNS
 */
#define  VTSS_F_TZPM_TZPCTL0_TZAESBNS(x)      VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TZPM_TZPCTL0_TZAESBNS         VTSS_BIT(5)
#define  VTSS_X_TZPM_TZPCTL0_TZAESBNS(x)      VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Programmable secure access control for HICM target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . ICM
 */
#define  VTSS_F_TZPM_TZPCTL0_ICM(x)           VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TZPM_TZPCTL0_ICM              VTSS_BIT(4)
#define  VTSS_X_TZPM_TZPCTL0_ICM(x)           VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Programmable secure access control for USB Device target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . UDPHS0
 */
#define  VTSS_F_TZPM_TZPCTL0_UDPHS0(x)        VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TZPM_TZPCTL0_UDPHS0           VTSS_BIT(2)
#define  VTSS_X_TZPM_TZPCTL0_UDPHS0(x)        VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Programmable secure access control for QSPI0 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . QSPI0
 */
#define  VTSS_F_TZPM_TZPCTL0_QSPI0(x)         VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TZPM_TZPCTL0_QSPI0            VTSS_BIT(1)
#define  VTSS_X_TZPM_TZPCTL0_QSPI0(x)         VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Programmable secure access control for HMATRIX target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL0 . HMATRIX
 */
#define  VTSS_F_TZPM_TZPCTL0_HMATRIX(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZPM_TZPCTL0_HMATRIX          VTSS_BIT(0)
#define  VTSS_X_TZPM_TZPCTL0_HMATRIX(x)       VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Trust Zone peripheral control 1
 *
 * \details
 * All programmable bits definition in this register
 *
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * All MAIN1 & MAIN2 HBRIDGE peripherals added in this register
 *
 * Register: \a TZPM:TZPM_REGS:TZPCTL1
 */
#define VTSS_TZPM_TZPCTL1                    VTSS_IOREG(VTSS_TO_TZPM,0x3)

/**
 * \brief
 * Programmable secure access control for FLEXCOM4 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . FLEXCOM4
 */
#define  VTSS_F_TZPM_TZPCTL1_FLEXCOM4(x)      VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_TZPM_TZPCTL1_FLEXCOM4         VTSS_BIT(20)
#define  VTSS_X_TZPM_TZPCTL1_FLEXCOM4(x)      VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Programmable secure access control for SHA target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . SHA
 */
#define  VTSS_F_TZPM_TZPCTL1_SHA(x)           VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_TZPM_TZPCTL1_SHA              VTSS_BIT(19)
#define  VTSS_X_TZPM_TZPCTL1_SHA(x)           VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Programmable secure access control for XDMA target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . XDMA
 */
#define  VTSS_F_TZPM_TZPCTL1_XDMA(x)          VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_TZPM_TZPCTL1_XDMA             VTSS_BIT(18)
#define  VTSS_X_TZPM_TZPCTL1_XDMA(x)          VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Programmable secure access control for FLEXCOM3 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . FLEXCOM3
 */
#define  VTSS_F_TZPM_TZPCTL1_FLEXCOM3(x)      VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_TZPM_TZPCTL1_FLEXCOM3         VTSS_BIT(17)
#define  VTSS_X_TZPM_TZPCTL1_FLEXCOM3(x)      VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Programmable secure access control for FLEXCOM2 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . FLEXCOM2
 */
#define  VTSS_F_TZPM_TZPCTL1_FLEXCOM2(x)      VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_TZPM_TZPCTL1_FLEXCOM2         VTSS_BIT(16)
#define  VTSS_X_TZPM_TZPCTL1_FLEXCOM2(x)      VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Programmable secure access control for QSPI1 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . QSPI1
 */
#define  VTSS_F_TZPM_TZPCTL1_QSPI1(x)         VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_TZPM_TZPCTL1_QSPI1            VTSS_BIT(5)
#define  VTSS_X_TZPM_TZPCTL1_QSPI1(x)         VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Programmable secure access control for AESB_ASC target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . AESB_ASC
 */
#define  VTSS_F_TZPM_TZPCTL1_AESB_ASC(x)      VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_TZPM_TZPCTL1_AESB_ASC         VTSS_BIT(4)
#define  VTSS_X_TZPM_TZPCTL1_AESB_ASC(x)      VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Programmable secure access control for AES target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . AES
 */
#define  VTSS_F_TZPM_TZPCTL1_AES(x)           VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_TZPM_TZPCTL1_AES              VTSS_BIT(3)
#define  VTSS_X_TZPM_TZPCTL1_AES(x)           VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Programmable secure access control for TRNG target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . TRNG
 */
#define  VTSS_F_TZPM_TZPCTL1_TRNG(x)          VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_TZPM_TZPCTL1_TRNG             VTSS_BIT(2)
#define  VTSS_X_TZPM_TZPCTL1_TRNG(x)          VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Programmable secure access control for FLEXCOM1 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . FLEXCOM1
 */
#define  VTSS_F_TZPM_TZPCTL1_FLEXCOM1(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TZPM_TZPCTL1_FLEXCOM1         VTSS_BIT(1)
#define  VTSS_X_TZPM_TZPCTL1_FLEXCOM1(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Programmable secure access control for FLEXCOM0 target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL1 . FLEXCOM0
 */
#define  VTSS_F_TZPM_TZPCTL1_FLEXCOM0(x)      VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZPM_TZPCTL1_FLEXCOM0         VTSS_BIT(0)
#define  VTSS_X_TZPM_TZPCTL1_FLEXCOM0(x)      VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Trust Zone peripheral control 2
 *
 * \details
 * All programmable bits definition in this register
 *
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * All CSS HBRIDGE peripherals added in this register
 *
 * Register: \a TZPM:TZPM_REGS:TZPCTL2
 */
#define VTSS_TZPM_TZPCTL2                    VTSS_IOREG(VTSS_TO_TZPM,0x4)

/**
 * \brief
 * Programmable secure access control for TZPM target (read-only)
 *
 * \details
 * Field: ::VTSS_TZPM_TZPCTL2 . TZPM
 */
#define  VTSS_F_TZPM_TZPCTL2_TZPM(x)          VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_TZPM_TZPCTL2_TZPM             VTSS_BIT(1)
#define  VTSS_X_TZPM_TZPCTL2_TZPM(x)          VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Programmable secure access control for PKCC target
 *
 * \details
 * 0: Secure Accesses only are allowed
 * 1: Non Secure Accesses are allowed
 *
 * Field: ::VTSS_TZPM_TZPCTL2 . PKCC
 */
#define  VTSS_F_TZPM_TZPCTL2_PKCC(x)          VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_TZPM_TZPCTL2_PKCC             VTSS_BIT(0)
#define  VTSS_X_TZPM_TZPCTL2_PKCC(x)          VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Trust Zone peripheral control 3
 *
 * \details
 * All programmable bits definition in this register.
 *
 * 0 : Secure transactions are generated.
 * 1: Non-secure transactions are generated.
 *
 * Security unaware Initiators added in this register.

 *
 * Register: \a TZPM:TZPM_REGS:TZPCTL3
 */
#define VTSS_TZPM_TZPCTL3                    VTSS_IOREG(VTSS_TO_TZPM,0x5)

/**
 * \brief
 * Programmable secure/non-secure transactions generation for PCIE IB
 * Initiator
 *
 * \details
 * 0 : Secure transactions are generated.
 * 1: Non-secure transactions are generated.
 *
 * Field: ::VTSS_TZPM_TZPCTL3 . PCIE_IB
 */
#define  VTSS_F_TZPM_TZPCTL3_PCIE_IB(x)       VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_TZPM_TZPCTL3_PCIE_IB          VTSS_BIT(27)
#define  VTSS_X_TZPM_TZPCTL3_PCIE_IB(x)       VTSS_EXTRACT_BITFIELD(x,27,1)

/**
 * \brief
 * Programmable secure/non-secure transactions generation for RTE Initiator
 *
 * \details
 * 0 : Secure transactions are generated.
 * 1: Non-secure transactions are generated.
 *
 * Field: ::VTSS_TZPM_TZPCTL3 . RTE
 */
#define  VTSS_F_TZPM_TZPCTL3_RTE(x)           VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_TZPM_TZPCTL3_RTE              VTSS_BIT(26)
#define  VTSS_X_TZPM_TZPCTL3_RTE(x)           VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Programmable secure/non-secure transactions generation for FDMA
 * Initiator
 *
 * \details
 * 0 : Secure transactions are generated.
 * 1: Non-secure transactions are generated.
 *
 * Field: ::VTSS_TZPM_TZPCTL3 . FDMA
 */
#define  VTSS_F_TZPM_TZPCTL3_FDMA(x)          VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_TZPM_TZPCTL3_FDMA             VTSS_BIT(25)
#define  VTSS_X_TZPM_TZPCTL3_FDMA(x)          VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Programmable secure/non-secure transactions generation for EXT_INITIATOR
 * Initiator
 *
 * \details
 * 0 : Secure transactions are generated.
 * 1: Non-secure transactions are generated.
 *
 * Field: ::VTSS_TZPM_TZPCTL3 . EXT_INITIATOR
 */
#define  VTSS_F_TZPM_TZPCTL3_EXT_INITIATOR(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_TZPM_TZPCTL3_EXT_INITIATOR    VTSS_BIT(24)
#define  VTSS_X_TZPM_TZPCTL3_EXT_INITIATOR(x)  VTSS_EXTRACT_BITFIELD(x,24,1)


#endif /* _VTSS_LAGUNA_REGS_TZPM_H_ */
