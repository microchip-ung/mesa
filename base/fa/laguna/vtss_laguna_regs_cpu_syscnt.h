// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_CPU_SYSCNT_H_
#define _VTSS_LAGUNA_REGS_CPU_SYSCNT_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a CPU_SYSCNT
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a CPU_SYSCNT:CXTSGEN_REGISTERS
 *
 * Not documented
 */


/**
 * \brief Controls counter operation by enabling or disabling or halting the counter
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CNTCR
 */
#define VTSS_CPU_SYSCNT_CNTCR                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x0)

/**
 * \brief
 * Enable or disable ID filitering for id's 0x0 to 0xF
 *
 * \details
 * 1: HIGH : Enabled and Counter is incrementing
 * 0: LOW : Disabled. It is also the reset value. Counter has stopped

 *
 * Field: ::VTSS_CPU_SYSCNT_CNTCR . CNTCR_EN
 */
#define  VTSS_F_CPU_SYSCNT_CNTCR_CNTCR_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_CPU_SYSCNT_CNTCR_CNTCR_EN     VTSS_BIT(0)
#define  VTSS_X_CPU_SYSCNT_CNTCR_CNTCR_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Halt the counter based on state of primary input. Halt on Debug
 *
 * \details
 * 1: HIGH : Debug signal into counter halts the counter
 * 0: LOW : Debug signal into counter has no effect

 *
 * Field: ::VTSS_CPU_SYSCNT_CNTCR . CNTCR_HDBG
 */
#define  VTSS_F_CPU_SYSCNT_CNTCR_CNTCR_HDBG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_SYSCNT_CNTCR_CNTCR_HDBG   VTSS_BIT(1)
#define  VTSS_X_CPU_SYSCNT_CNTCR_CNTCR_HDBG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Counter status register
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CNTSR
 */
#define VTSS_CPU_SYSCNT_CNTSR                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x1)

/**
 * \brief
 * Counter status register
 *
 * \details
 * 1: HIGH : Debug halted
 * 0: LOW : No Debug event has halted the counter

 *
 * Field: ::VTSS_CPU_SYSCNT_CNTSR . CNTSR_DBGH
 */
#define  VTSS_F_CPU_SYSCNT_CNTSR_CNTSR_DBGH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_CPU_SYSCNT_CNTSR_CNTSR_DBGH   VTSS_BIT(1)
#define  VTSS_X_CPU_SYSCNT_CNTSR_CNTSR_DBGH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief Current value of Counter. Lower 32-bits.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CNTCVL
 */
#define VTSS_CPU_SYSCNT_CNTCVL               VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x2)

/**
 * \brief
 * Current value of Counter. Lower 32-bits
 *
 * \details
 * Field: ::VTSS_CPU_SYSCNT_CNTCVL . CNTCVL_L_32
 */
#define  VTSS_F_CPU_SYSCNT_CNTCVL_CNTCVL_L_32(x)  (x)
#define  VTSS_M_CPU_SYSCNT_CNTCVL_CNTCVL_L_32     0xffffffff
#define  VTSS_X_CPU_SYSCNT_CNTCVL_CNTCVL_L_32(x)  (x)


/**
 * \brief Current value of Counter. Upper 32-bits.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CNTCVU
 */
#define VTSS_CPU_SYSCNT_CNTCVU               VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3)

/**
 * \brief
 * Current value of Counter. Upper 32-bits
 *
 * \details
 * Field: ::VTSS_CPU_SYSCNT_CNTCVU . CNTCVU_U_32
 */
#define  VTSS_F_CPU_SYSCNT_CNTCVU_CNTCVU_U_32(x)  (x)
#define  VTSS_M_CPU_SYSCNT_CNTCVU_CNTCVU_U_32     0xffffffff
#define  VTSS_X_CPU_SYSCNT_CNTCVU_CNTCVU_U_32(x)  (x)


/**
 * \brief Base Frequency ID
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CNTFID0
 */
#define VTSS_CPU_SYSCNT_CNTFID0              VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x8)

/**
 * \brief
 * Base Frequency ID
 *
 * \details
 * Field: ::VTSS_CPU_SYSCNT_CNTFID0 . CNTFID0
 */
#define  VTSS_F_CPU_SYSCNT_CNTFID0_CNTFID0(x)  (x)
#define  VTSS_M_CPU_SYSCNT_CNTFID0_CNTFID0     0xffffffff
#define  VTSS_X_CPU_SYSCNT_CNTFID0_CNTFID0(x)  (x)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer specific part number.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:PIDR0
 */
#define VTSS_CPU_SYSCNT_PIDR0                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3f8)

/**
 * \brief
 * Bits [7:0] of the component part number. This is selected by the
 * designer of the component.
 *
 * \details
 * 0x01: Time_Stamp_Generator_Part_Number_Bits7to0 : Lowest 8 bits of the
 * Part Number, 0x101.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR0 . PART_0
 */
#define  VTSS_F_CPU_SYSCNT_PIDR0_PART_0(x)    VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_PIDR0_PART_0       VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_PIDR0_PART_0(x)    VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer specific part number and part of the designer identity.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:PIDR1
 */
#define VTSS_CPU_SYSCNT_PIDR1                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3f9)

/**
 * \brief
 * Bits [11:8] of the component part number. This is selected by the
 * designer of the component.
 *
 * \details
 * 0x1: Time_Stamp_Generator_Part_Number_Bits11to8 : Upper 4 bits of the
 * Part Number, 0x101.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR1 . PART_1
 */
#define  VTSS_F_CPU_SYSCNT_PIDR1_PART_1(x)    VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_PIDR1_PART_1       VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_PIDR1_PART_1(x)    VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Bits [3:0] of the JEDEC identity code indicating the designer of the
 * component, together with the continuation code.
 *
 * \details
 * 0xB: ARM_JEP106_Identity_Code_Bits7to0 : Lowest 4 bits of the JEP106
 * Identity Code.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR1 . DES_0
 */
#define  VTSS_F_CPU_SYSCNT_PIDR1_DES_0(x)     VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_PIDR1_DES_0        VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_PIDR1_DES_0(x)     VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer identity and the product revision.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:PIDR2
 */
#define VTSS_CPU_SYSCNT_PIDR2                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3fa)

/**
 * \brief
 * Bits [6:4] of the JEDEC identity code indicating the designer of the
 * component, together with the continuation code.
 *
 * \details
 * 0x3: ARM_JEP106_Identity_Code_Bits6to4 : Upper 3 bits of the JEP106
 * Identity Code.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR2 . DES_1
 */
#define  VTSS_F_CPU_SYSCNT_PIDR2_DES_1(x)     VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CPU_SYSCNT_PIDR2_DES_1        VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CPU_SYSCNT_PIDR2_DES_1(x)     VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Always set. Indicates that a JEDEC assigned value is used.
 *
 * \details
 * 0x1: JEDEC_Identity : The designer ID is specified by JEDEC
 * (http://www.jedec.org).

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR2 . JEDEC
 */
#define  VTSS_F_CPU_SYSCNT_PIDR2_JEDEC(x)     VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_SYSCNT_PIDR2_JEDEC        VTSS_BIT(3)
#define  VTSS_X_CPU_SYSCNT_PIDR2_JEDEC(x)     VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The Revision field is an incremental value starting at 0x0 for the first
 * design of this component. This only increases by 1 for both major and
 * minor revisions and is used as a look-up to establish the exact major
 * and minor revision.
 *
 * \details
 * 0x1: r0p1 : This device is at r0p1.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR2 . REVISION
 */
#define  VTSS_F_CPU_SYSCNT_PIDR2_REVISION(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_PIDR2_REVISION     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_PIDR2_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains the RevAnd and Customer Modified fields.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:PIDR3
 */
#define VTSS_CPU_SYSCNT_PIDR3                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3fb)

/**
 * \brief
 * Where the component is reusable IP, this value indicates if the customer
 * has modified the behavior of the component. In most cases this field is
 * zero.
 *
 * \details
 * 0x0: No_Mods : Indicates that there have been no modifications made.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR3 . CMOD
 */
#define  VTSS_F_CPU_SYSCNT_PIDR3_CMOD(x)      VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_PIDR3_CMOD         VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_PIDR3_CMOD(x)      VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * This field indicates minor errata fixes specific to this design, for
 * example metal fixes after implementation. In most cases this field is
 * zero. It is recommended that component designers ensure this field can
 * be changed by a metal fix if required, for example by driving it from
 * registers that reset to zero.
 *
 * \details
 * 0x0: No_Mods : Indicates that there have been no metal fixes to this
 * component.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR3 . REVAND
 */
#define  VTSS_F_CPU_SYSCNT_PIDR3_REVAND(x)    VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_PIDR3_REVAND       VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_PIDR3_REVAND(x)    VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer identity and the memory footprint indicator.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:PIDR4
 */
#define VTSS_CPU_SYSCNT_PIDR4                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3f4)

/**
 * \brief
 * JEDEC continuation code indicating the designer of the component,
 * together with the identity code.
 *
 * \details
 * 0x4: ARM_JEP106_Continuation_Code : Indicates that ARM's JEDEC identity
 * code is on the 5th bank.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR4 . DES_2
 */
#define  VTSS_F_CPU_SYSCNT_PIDR4_DES_2(x)     VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_PIDR4_DES_2        VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_PIDR4_DES_2(x)     VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * This is a 4-bit value that indicates the total contiguous size of the
 * memory window used by this component in powers of 2 from the standard
 * 4KB. If a component only requires the standard 4KB, this must read as
 * 0x0, 4KB only. For 8KB set to 0x1, for 16KB set to 0x2, for 32KB set to
 * 0x3, and so on.
 *
 * \details
 * 0x0: Size_4kB : Indicates that the device only occupies 4KB of memory.

 *
 * Field: ::VTSS_CPU_SYSCNT_PIDR4 . SIZE
 */
#define  VTSS_F_CPU_SYSCNT_PIDR4_SIZE(x)      VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_PIDR4_SIZE         VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_PIDR4_SIZE(x)      VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CIDR0
 */
#define VTSS_CPU_SYSCNT_CIDR0                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3fc)

/**
 * \brief
 * Contains bits[7:0] of the component identification code.
 *
 * \details
 * 0x0D: ID_Value_0D : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_CIDR0 . PRMBL_0
 */
#define  VTSS_F_CPU_SYSCNT_CIDR0_PRMBL_0(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_CIDR0_PRMBL_0      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_CIDR0_PRMBL_0(x)   VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief A component identification register, that indicates that the identification registers are present. This register also indicates the component class.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CIDR1
 */
#define VTSS_CPU_SYSCNT_CIDR1                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3fd)

/**
 * \brief
 * Contains bits[11:8] of the component identification code.
 *
 * \details
 * 0x0: ID_Value_0 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_CIDR1 . PRMBL_1
 */
#define  VTSS_F_CPU_SYSCNT_CIDR1_PRMBL_1(x)   VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_CIDR1_PRMBL_1      VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_CIDR1_PRMBL_1(x)   VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Class of the component, for example, ROM table or CoreSight component.
 *
 * \details
 * 0xF: Primecell_component : Indicates the component is a Primecell
 * component.

 *
 * Field: ::VTSS_CPU_SYSCNT_CIDR1 . CLASS
 */
#define  VTSS_F_CPU_SYSCNT_CIDR1_CLASS(x)     VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_CIDR1_CLASS        VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_CIDR1_CLASS(x)     VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CIDR2
 */
#define VTSS_CPU_SYSCNT_CIDR2                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3fe)

/**
 * \brief
 * Contains bits[23:16] of the component identification code.
 *
 * \details
 * 0x05: ID_Value_05 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_CIDR2 . PRMBL_2
 */
#define  VTSS_F_CPU_SYSCNT_CIDR2_PRMBL_2(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_CIDR2_PRMBL_2      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_CIDR2_PRMBL_2(x)   VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT:CXTSGEN_REGISTERS:CIDR3
 */
#define VTSS_CPU_SYSCNT_CIDR3                VTSS_IOREG(VTSS_TO_CPU_SYSCNT,0x3ff)

/**
 * \brief
 * Contains bits[31:24] of the component identification code.
 *
 * \details
 * 0xB1: ID_Value_B1 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_CIDR3 . PRMBL_3
 */
#define  VTSS_F_CPU_SYSCNT_CIDR3_PRMBL_3(x)   VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_CIDR3_PRMBL_3      VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_CIDR3_PRMBL_3(x)   VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_LAGUNA_REGS_CPU_SYSCNT_H_ */
