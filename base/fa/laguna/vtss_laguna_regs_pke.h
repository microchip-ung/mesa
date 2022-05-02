// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_PKE_H_
#define _VTSS_LAGUNA_REGS_PKE_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a PKE
 *
 * Public Key Crypto Engine
 *
 ***********************************************************************/

/**
 * Register Group: \a PKE:PKE_REGS
 *
 * Public Key Crypto Engine Registers
 */


/**
 * \brief Pointers register
 *
 * \details
 * When executing some operations, more flexibility is given with the use
 * of pointers defining locations where
 * operands & results are stored in the data memory.
 *
 * Register: \a PKE:PKE_REGS:PK_POINTERREG
 */
#define VTSS_PKE_PK_POINTERREG               VTSS_IOREG(VTSS_TO_PKE,0x0)

/**
 * \brief
 * When executing primitive arithmetic operations, this pointer defines the
 * location where the modulus is located in memory (location 0x0 to 0xF).
 *
 * \details
 * Field: ::VTSS_PKE_PK_POINTERREG . OPPTRN
 */
#define  VTSS_F_PKE_PK_POINTERREG_OPPTRN(x)   VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_PKE_PK_POINTERREG_OPPTRN      VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_PKE_PK_POINTERREG_OPPTRN(x)   VTSS_EXTRACT_BITFIELD(x,24,4)

/**
 * \brief
 * When executing primitive arithmetic operations, this pointer defines the
 * location (0x0 to 0xF) where the result will be stored in memory.
 *
 * \details
 * Field: ::VTSS_PKE_PK_POINTERREG . OPPTRC
 */
#define  VTSS_F_PKE_PK_POINTERREG_OPPTRC(x)   VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_PKE_PK_POINTERREG_OPPTRC      VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_PKE_PK_POINTERREG_OPPTRC(x)   VTSS_EXTRACT_BITFIELD(x,16,4)

/**
 * \brief
 * When executing primitive arithmetic operations, this Pointer defines
 * where operand B is located in memory (location 0x0 to 0xF).
 *
 * \details
 * Field: ::VTSS_PKE_PK_POINTERREG . OPPTRB
 */
#define  VTSS_F_PKE_PK_POINTERREG_OPPTRB(x)   VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_PKE_PK_POINTERREG_OPPTRB      VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_PKE_PK_POINTERREG_OPPTRB(x)   VTSS_EXTRACT_BITFIELD(x,8,4)

/**
 * \brief
 * When executing primitive arithmetic operations, this Pointer defines
 * where operand A is located in memory (location 0x0 to 0xF).
 *
 * \details
 * Field: ::VTSS_PKE_PK_POINTERREG . OPPTRA
 */
#define  VTSS_F_PKE_PK_POINTERREG_OPPTRA(x)   VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_PKE_PK_POINTERREG_OPPTRA      VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_PKE_PK_POINTERREG_OPPTRA(x)   VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief Command register
 *
 * \details
 * The Micro-Code-driven architecture offers the possibility to implement
 * low-level arithmetic operations as well
 * high-level cryptography algorithms.
 *
 * Register: \a PKE:PKE_REGS:PK_COMMANDREG
 */
#define VTSS_PKE_PK_COMMANDREG               VTSS_IOREG(VTSS_TO_PKE,0x1)

/**
 * \brief
 * This bit indicates  if the IP has to calculate R2 mod N for the next
 * operation. This bit must be set to 1 when a new prime number has been
 * programmed. This bit is used for some primitive operations (see Section
 * 6.1.2) and ignored for the other operations.0: dont recalculate R2 mod
 * N1: recalculate R2 mod N
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . CALCR2
 */
#define  VTSS_F_PKE_PK_COMMANDREG_CALCR2(x)   VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PKE_PK_COMMANDREG_CALCR2      VTSS_BIT(31)
#define  VTSS_X_PKE_PK_COMMANDREG_CALCR2(x)   VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * See operation description
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . FLAG_B
 */
#define  VTSS_F_PKE_PK_COMMANDREG_FLAG_B(x)   VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PKE_PK_COMMANDREG_FLAG_B      VTSS_BIT(30)
#define  VTSS_X_PKE_PK_COMMANDREG_FLAG_B(x)   VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * See operation description
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . FLAG_A
 */
#define  VTSS_F_PKE_PK_COMMANDREG_FLAG_A(x)   VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PKE_PK_COMMANDREG_FLAG_A      VTSS_BIT(29)
#define  VTSS_X_PKE_PK_COMMANDREG_FLAG_A(x)   VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Swap the bytes on AHB interface:0: Native format (little endian)1: Byte
 * swapped (big endian)See also Section 4.2.1.This bit must be programmed
 * before writing/reading any data in data memory. This Swap Bytes
 * functionality is not supported when the memory is accessed through AHB
 * Master (g_AHBMaster = True).
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . SWAP_BYTES
 */
#define  VTSS_F_PKE_PK_COMMANDREG_SWAP_BYTES(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_PKE_PK_COMMANDREG_SWAP_BYTES  VTSS_BIT(28)
#define  VTSS_X_PKE_PK_COMMANDREG_SWAP_BYTES(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/**
 * \brief
 * Enable Edwards curve (see operation description)
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . EDWARDS
 */
#define  VTSS_F_PKE_PK_COMMANDREG_EDWARDS(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_PKE_PK_COMMANDREG_EDWARDS     VTSS_BIT(26)
#define  VTSS_X_PKE_PK_COMMANDREG_EDWARDS(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Enable randomization of projective coordinates (counter measure)
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . RANDPROJ
 */
#define  VTSS_F_PKE_PK_COMMANDREG_RANDPROJ(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PKE_PK_COMMANDREG_RANDPROJ    VTSS_BIT(25)
#define  VTSS_X_PKE_PK_COMMANDREG_RANDPROJ(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Enable randomization of exponent/scalar (counter-measure)
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . RANDKE
 */
#define  VTSS_F_PKE_PK_COMMANDREG_RANDKE(x)   VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PKE_PK_COMMANDREG_RANDKE      VTSS_BIT(24)
#define  VTSS_X_PKE_PK_COMMANDREG_RANDKE(x)   VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Enable accelerator for specific curve modulus:0x0: No acceleration
 * (default)0x1: P2560x2: P3840x3: P5210x4: P1920x5: Curve255190x6:
 * Ed25519This field has no effect when the optional acceleration hardware
 * is not included.
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . SELCURVE
 */
#define  VTSS_F_PKE_PK_COMMANDREG_SELCURVE(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_PKE_PK_COMMANDREG_SELCURVE     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_PKE_PK_COMMANDREG_SELCURVE(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/**
 * \brief
 * Enable randomization of modulus (counter-measure)
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . RANDMOD
 */
#define  VTSS_F_PKE_PK_COMMANDREG_RANDMOD(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_PKE_PK_COMMANDREG_RANDMOD     VTSS_BIT(19)
#define  VTSS_X_PKE_PK_COMMANDREG_RANDMOD(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * This field defines the size (= number of bytes minus one) of the
 * operands for the current operation. Possible values are limited by the
 * maximum supported operand sizeExamples:0x014 -> ECC on curve K-1630x01F
 * -> ECC on curve P-2560x02F -> ECC on curve P-3840x033 -> ECC on curve
 * K-4090x041 -> ECC on curve P-5210x07F -> 1024-bit RSA0x09F -> 1280-bit
 * RSA0x1FF -> 4096-bit RSA0x3FF -> 8192-bit RSA
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . SIZE_OF_OPERANDS
 */
#define  VTSS_F_PKE_PK_COMMANDREG_SIZE_OF_OPERANDS(x)  VTSS_ENCODE_BITFIELD(x,8,9)
#define  VTSS_M_PKE_PK_COMMANDREG_SIZE_OF_OPERANDS     VTSS_ENCODE_BITMASK(8,9)
#define  VTSS_X_PKE_PK_COMMANDREG_SIZE_OF_OPERANDS(x)  VTSS_EXTRACT_BITFIELD(x,8,9)

/**
 * \brief
 * 0 : Field GF(p)1: Field GF)2m)
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . FIELD
 */
#define  VTSS_F_PKE_PK_COMMANDREG_FIELD(x)    VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_PKE_PK_COMMANDREG_FIELD       VTSS_BIT(7)
#define  VTSS_X_PKE_PK_COMMANDREG_FIELD(x)    VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * This field defines the operation to be performed. PLease refer Table
 * 4.4 Types of operation in BA414EP datasheet.
 *
 * \details
 * Field: ::VTSS_PKE_PK_COMMANDREG . TYPE_OF_OPERATION
 */
#define  VTSS_F_PKE_PK_COMMANDREG_TYPE_OF_OPERATION(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_PKE_PK_COMMANDREG_TYPE_OF_OPERATION     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_PKE_PK_COMMANDREG_TYPE_OF_OPERATION(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Control register
 *
 * \details
 * write-only register
 *
 * Register: \a PKE:PKE_REGS:PK_CONTROLREG
 */
#define VTSS_PKE_PK_CONTROLREG               VTSS_IOREG(VTSS_TO_PKE,0x2)

/**
 * \brief
 * Writing a 1 clears the IRQ output.
 *
 * \details
 * Field: ::VTSS_PKE_PK_CONTROLREG . CLEARIRQ
 */
#define  VTSS_F_PKE_PK_CONTROLREG_CLEARIRQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_PKE_PK_CONTROLREG_CLEARIRQ    VTSS_BIT(1)
#define  VTSS_X_PKE_PK_CONTROLREG_CLEARIRQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Writing a 1 starts the processing
 *
 * \details
 * Field: ::VTSS_PKE_PK_CONTROLREG . PK_START
 */
#define  VTSS_F_PKE_PK_CONTROLREG_PK_START(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_PKE_PK_CONTROLREG_PK_START    VTSS_BIT(0)
#define  VTSS_X_PKE_PK_CONTROLREG_PK_START(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief status register
 *
 * \details
 * Register: \a PKE:PKE_REGS:PK_STATUSREG
 */
#define VTSS_PKE_PK_STATUSREG                VTSS_IOREG(VTSS_TO_PKE,0x3)

/**
 * \brief
 * These bits indicate which data location generated the error flag. They
 * are not available for all error flags.
 *
 * \details
 * Field: ::VTSS_PKE_PK_STATUSREG . FAILPTR
 */
#define  VTSS_F_PKE_PK_STATUSREG_FAILPTR(x)   VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_PKE_PK_STATUSREG_FAILPTR      VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_PKE_PK_STATUSREG_FAILPTR(x)   VTSS_EXTRACT_BITFIELD(x,24,5)

/**
 * \brief
 * This bit reflects the IRQ output value.It is set when the operation is
 * finished. It is cleared when the CPU writes the bit 1 of Control
 * Register or when a new operation is started.
 *
 * \details
 * Field: ::VTSS_PKE_PK_STATUSREG . INTERRUPT_STATUS
 */
#define  VTSS_F_PKE_PK_STATUSREG_INTERRUPT_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PKE_PK_STATUSREG_INTERRUPT_STATUS  VTSS_BIT(17)
#define  VTSS_X_PKE_PK_STATUSREG_INTERRUPT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * This bit reflects the BUSY output value. It is set when the operation
 * starts and it is cleared when theoperation is finished.
 *
 * \details
 * Field: ::VTSS_PKE_PK_STATUSREG . PK_BUSY
 */
#define  VTSS_F_PKE_PK_STATUSREG_PK_BUSY(x)   VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PKE_PK_STATUSREG_PK_BUSY      VTSS_BIT(16)
#define  VTSS_X_PKE_PK_STATUSREG_PK_BUSY(x)   VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * These bits indicate an error condition. They are updated at the end of
 * the operation. They are cleared when starting a new operation.PLease
 * refer Table 4.7 Error flags in BA414EP datasheet
 *
 * \details
 * Field: ::VTSS_PKE_PK_STATUSREG . ERRORFLAGS
 */
#define  VTSS_F_PKE_PK_STATUSREG_ERRORFLAGS(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_PKE_PK_STATUSREG_ERRORFLAGS     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_PKE_PK_STATUSREG_ERRORFLAGS(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Timer register
 *
 * \details
 * The timer counts the number of clock cycles when the PKC Engine is busy.
 * It is not cleared automatically. It
 * can be written by software (when the PK is idle). The register is
 * updated at the end of every operation (reading
 * it when the PKC Engine is running returns the initial value of the
 * counter, not the current value).
 *
 * Register: \a PKE:PKE_REGS:PK_TIMERREG
 */
#define VTSS_PKE_PK_TIMERREG                 VTSS_IOREG(VTSS_TO_PKE,0x5)

/**
 * \brief
 * Number of core clock cycles
 *
 * \details
 * Field: ::VTSS_PKE_PK_TIMERREG . TIMER
 */
#define  VTSS_F_PKE_PK_TIMERREG_TIMER(x)      (x)
#define  VTSS_M_PKE_PK_TIMERREG_TIMER         0xffffffff
#define  VTSS_X_PKE_PK_TIMERREG_TIMER(x)      (x)


/**
 * \brief Hardware configuration register
 *
 * \details
 * This register gives information about the hardware included (see Section
 * 2).
 *
 * Register: \a PKE:PKE_REGS:PK_HWCONFIGREG
 */
#define VTSS_PKE_PK_HWCONFIGREG              VTSS_IOREG(VTSS_TO_PKE,0x6)

/**
 * \brief
 * State of DisableCM input (high when counter-measures are disabled)
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . DISABLECM
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_DISABLECM(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_DISABLECM  VTSS_BIT(31)
#define  VTSS_X_PKE_PK_HWCONFIGREG_DISABLECM(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/**
 * \brief
 * State of DisableClrMem input
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . DISABLECLRMEM
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_DISABLECLRMEM(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_DISABLECLRMEM  VTSS_BIT(30)
#define  VTSS_X_PKE_PK_HWCONFIGREG_DISABLECLRMEM(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/**
 * \brief
 * State of DisableSMx input
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . DISABLESMX
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_DISABLESMX(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_DISABLESMX  VTSS_BIT(29)
#define  VTSS_X_PKE_PK_HWCONFIGREG_DISABLESMX(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * 0:  Memory access through AHB Slave and internally in the PKE.1:  Memory
 * access through AHB Master, outside the PKE.
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . AHBMASTER
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_AHBMASTER(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_AHBMASTER  VTSS_BIT(25)
#define  VTSS_X_PKE_PK_HWCONFIGREG_AHBMASTER(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Support Curve25519/Ed25519 acceleration
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . C_ED_25519
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_C_ED_25519(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_C_ED_25519  VTSS_BIT(24)
#define  VTSS_X_PKE_PK_HWCONFIGREG_C_ED_25519(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Support ECC P192 acceleration
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . P192
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_P192(x)    VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_P192       VTSS_BIT(23)
#define  VTSS_X_PKE_PK_HWCONFIGREG_P192(x)    VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Support ECC P521 acceleration
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . P521
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_P521(x)    VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_P521       VTSS_BIT(22)
#define  VTSS_X_PKE_PK_HWCONFIGREG_P521(x)    VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Support ECC P384 acceleration
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . P384
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_P384(x)    VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_P384       VTSS_BIT(21)
#define  VTSS_X_PKE_PK_HWCONFIGREG_P384(x)    VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Support ECC P256 acceleration
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . P256
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_P256(x)    VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_P256       VTSS_BIT(20)
#define  VTSS_X_PKE_PK_HWCONFIGREG_P256(x)    VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Support RAM error correction
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . ECC
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_ECC(x)     VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_ECC        VTSS_BIT(18)
#define  VTSS_X_PKE_PK_HWCONFIGREG_ECC(x)     VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Support binary field
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . BINRARYFIELD
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_BINRARYFIELD(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_BINRARYFIELD  VTSS_BIT(17)
#define  VTSS_X_PKE_PK_HWCONFIGREG_BINRARYFIELD(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Support prime field
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . PRIMEFIELD
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_PRIMEFIELD(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_PKE_PK_HWCONFIGREG_PRIMEFIELD  VTSS_BIT(16)
#define  VTSS_X_PKE_PK_HWCONFIGREG_PRIMEFIELD(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Number of multipliers:0x0: 1 multiplier0x1: 4 multipliers0x2: 16
 * multipliers0x4: 64 multipliers0x8: 256 multipliers
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . NBMULT
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_NBMULT(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_PKE_PK_HWCONFIGREG_NBMULT     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_PKE_PK_HWCONFIGREG_NBMULT(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/**
 * \brief
 * Maximum operand size (number of bytes)
 *
 * \details
 * Field: ::VTSS_PKE_PK_HWCONFIGREG . MAXOPSIZE
 */
#define  VTSS_F_PKE_PK_HWCONFIGREG_MAXOPSIZE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_PKE_PK_HWCONFIGREG_MAXOPSIZE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_PKE_PK_HWCONFIGREG_MAXOPSIZE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


#endif /* _VTSS_LAGUNA_REGS_PKE_H_ */
