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

#ifndef _VTSS_LAGUNA_REGS_CPU_SYSCNT_RO_H_
#define _VTSS_LAGUNA_REGS_CPU_SYSCNT_RO_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a CPU_SYSCNT_RO
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS
 *
 * Not documented
 */


/**
 * \brief Current value of Counter. Lower 32-bits.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CNTCVL
 */
#define VTSS_CPU_SYSCNT_RO_CNTCVL            VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x400)

/**
 * \brief
 * Current value of Counter. Lower 32-bits
 *
 * \details
 * Field: ::VTSS_CPU_SYSCNT_RO_CNTCVL . CNTCVL_L_32
 */
#define  VTSS_F_CPU_SYSCNT_RO_CNTCVL_CNTCVL_L_32(x)  (x)
#define  VTSS_M_CPU_SYSCNT_RO_CNTCVL_CNTCVL_L_32     0xffffffff
#define  VTSS_X_CPU_SYSCNT_RO_CNTCVL_CNTCVL_L_32(x)  (x)


/**
 * \brief Current value of Counter. Upper 32-bits.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CNTCVU
 */
#define VTSS_CPU_SYSCNT_RO_CNTCVU            VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x401)

/**
 * \brief
 * Current value of Counter. Upper 32-bits
 *
 * \details
 * Field: ::VTSS_CPU_SYSCNT_RO_CNTCVU . CNTCVU_U_32
 */
#define  VTSS_F_CPU_SYSCNT_RO_CNTCVU_CNTCVU_U_32(x)  (x)
#define  VTSS_M_CPU_SYSCNT_RO_CNTCVU_CNTCVU_U_32     0xffffffff
#define  VTSS_X_CPU_SYSCNT_RO_CNTCVU_CNTCVU_U_32(x)  (x)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer specific part number.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:PIDR0
 */
#define VTSS_CPU_SYSCNT_RO_PIDR0             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7f8)

/**
 * \brief
 * Bits [7:0] of the component part number. This is selected by the
 * designer of the component.
 *
 * \details
 * 0x01: Time_Stamp_Generator_Part_Number_Bits7to0 : Lowest 8 bits of the
 * Part Number, 0x101.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR0 . PART_0
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR0_PART_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR0_PART_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR0_PART_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer specific part number and part of the designer identity.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:PIDR1
 */
#define VTSS_CPU_SYSCNT_RO_PIDR1             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7f9)

/**
 * \brief
 * Bits [11:8] of the component part number. This is selected by the
 * designer of the component.
 *
 * \details
 * 0x1: Time_Stamp_Generator_Part_Number_Bits11to8 : Upper 4 bits of the
 * Part Number, 0x101.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR1 . PART_1
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR1_PART_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR1_PART_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR1_PART_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Bits [3:0] of the JEDEC identity code indicating the designer of the
 * component, together with the continuation code.
 *
 * \details
 * 0xB: ARM_JEP106_Identity_Code_Bits7to0 : Lowest 4 bits of the JEP106
 * Identity Code.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR1 . DES_0
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR1_DES_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR1_DES_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR1_DES_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer identity and the product revision.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:PIDR2
 */
#define VTSS_CPU_SYSCNT_RO_PIDR2             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7fa)

/**
 * \brief
 * Bits [6:4] of the JEDEC identity code indicating the designer of the
 * component, together with the continuation code.
 *
 * \details
 * 0x3: ARM_JEP106_Identity_Code_Bits6to4 : Upper 3 bits of the JEP106
 * Identity Code.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR2 . DES_1
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR2_DES_1(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR2_DES_1     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR2_DES_1(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Always set. Indicates that a JEDEC assigned value is used.
 *
 * \details
 * 0x1: JEDEC_Identity : The designer ID is specified by JEDEC
 * (http://www.jedec.org).

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR2 . JEDEC
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR2_JEDEC(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR2_JEDEC     VTSS_BIT(3)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR2_JEDEC(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

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
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR2 . REVISION
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR2_REVISION(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR2_REVISION     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR2_REVISION(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains the RevAnd and Customer Modified fields.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:PIDR3
 */
#define VTSS_CPU_SYSCNT_RO_PIDR3             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7fb)

/**
 * \brief
 * Where the component is reusable IP, this value indicates if the customer
 * has modified the behavior of the component. In most cases this field is
 * zero.
 *
 * \details
 * 0x0: No_Mods : Indicates that there have been no modifications made.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR3 . CMOD
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR3_CMOD(x)   VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR3_CMOD      VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR3_CMOD(x)   VTSS_EXTRACT_BITFIELD(x,0,4)

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
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR3 . REVAND
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR3_REVAND(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR3_REVAND     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR3_REVAND(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief Part of the set of Peripheral Identification registers. Contains part of the designer identity and the memory footprint indicator.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:PIDR4
 */
#define VTSS_CPU_SYSCNT_RO_PIDR4             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7f4)

/**
 * \brief
 * JEDEC continuation code indicating the designer of the component,
 * together with the identity code.
 *
 * \details
 * 0x4: ARM_JEP106_Continuation_Code : Indicates that ARM's JEDEC identity
 * code is on the 5th bank.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR4 . DES_2
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR4_DES_2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR4_DES_2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR4_DES_2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

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
 * Field: ::VTSS_CPU_SYSCNT_RO_PIDR4 . SIZE
 */
#define  VTSS_F_CPU_SYSCNT_RO_PIDR4_SIZE(x)   VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_RO_PIDR4_SIZE      VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_RO_PIDR4_SIZE(x)   VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CIDR0
 */
#define VTSS_CPU_SYSCNT_RO_CIDR0             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7fc)

/**
 * \brief
 * Contains bits [24:31] of the component identification.
 *
 * \details
 * 0x0D: ID_Value_0D : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_CIDR0 . PRMBL_0
 */
#define  VTSS_F_CPU_SYSCNT_RO_CIDR0_PRMBL_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_RO_CIDR0_PRMBL_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_RO_CIDR0_PRMBL_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief A component identification register, that indicates that the identification registers are present. This register also indicates the component class.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CIDR1
 */
#define VTSS_CPU_SYSCNT_RO_CIDR1             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7fd)

/**
 * \brief
 * Contains bits [19:16] of the component identification.
 *
 * \details
 * 0x0: ID_Value_0 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_CIDR1 . PRMBL_1
 */
#define  VTSS_F_CPU_SYSCNT_RO_CIDR1_PRMBL_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_CPU_SYSCNT_RO_CIDR1_PRMBL_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_CPU_SYSCNT_RO_CIDR1_PRMBL_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Class of the component, for example, ROM table or CoreSight component.
 *
 * \details
 * 0xF: Primecell_component : Indicates the component is a CoreSight
 * component.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_CIDR1 . CLASS
 */
#define  VTSS_F_CPU_SYSCNT_RO_CIDR1_CLASS(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_CPU_SYSCNT_RO_CIDR1_CLASS     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_CPU_SYSCNT_RO_CIDR1_CLASS(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CIDR2
 */
#define VTSS_CPU_SYSCNT_RO_CIDR2             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7fe)

/**
 * \brief
 * Contains bits [15:8] of the component identification.
 *
 * \details
 * 0x05: ID_Value_05 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_CIDR2 . PRMBL_2
 */
#define  VTSS_F_CPU_SYSCNT_RO_CIDR2_PRMBL_2(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_RO_CIDR2_PRMBL_2     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_RO_CIDR2_PRMBL_2(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief A component identification register, that indicates that the identification registers are present.
 *
 * \details
 * Register: \a CPU_SYSCNT_RO:CXTSGEN_READ_REGISTERS:CIDR3
 */
#define VTSS_CPU_SYSCNT_RO_CIDR3             VTSS_IOREG(VTSS_TO_CPU_SYSCNT_RO,0x7ff)

/**
 * \brief
 * Contains bits [7:0] of the component identification.
 *
 * \details
 * 0xB1: ID_Value_B1 : Identification value.

 *
 * Field: ::VTSS_CPU_SYSCNT_RO_CIDR3 . PRMBL_3
 */
#define  VTSS_F_CPU_SYSCNT_RO_CIDR3_PRMBL_3(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_CPU_SYSCNT_RO_CIDR3_PRMBL_3     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_CPU_SYSCNT_RO_CIDR3_PRMBL_3(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_LAGUNA_REGS_CPU_SYSCNT_RO_H_ */
