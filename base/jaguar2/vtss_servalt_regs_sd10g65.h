#ifndef _VTSS_SERVALT_REGS_SD10G65_H_
#define _VTSS_SERVALT_REGS_SD10G65_H_

/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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

#include "vtss_servalt_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a SD10G65
 *
 * \see vtss_target_SD10G65_e
 *
 * Configuration and status for high speed macro.
 *
 ***********************************************************************/

/**
 * Register Group: \a SD10G65:SD10G65_DES
 *
 * SD10G65 DES Configuration and Status Register set
 */


/** 
 * \brief SD10G65 DES Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 DES.
 *
 * Register: \a SD10G65:SD10G65_DES:SD10G65_DES_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Invert output of high auxillary deserializer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_H
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_H(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_H  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_H(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Invert output of low auxillary deserializer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_L
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_L(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_L  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_L(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Invert output of main deserializer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_INV_M
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_M(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_M  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_INV_M(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Interface width
 *
 * \details 
 * 0: 8
 * 1: 10
 * 2: 16 (energy efficient)
 * 3: 20 (energy efficient)
 * 4: 32
 * 5: 40
 * 6: 16 bit (fast)
 * 7: 20 bit (fast)
 *
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_IF_MODE_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_IF_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Auxillary deserializer channels disable.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_VSC_DIS
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_VSC_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_VSC_DIS  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_VSC_DIS(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Deserializer disable.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_DES_CFG0 . DES_DIS
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_DIS  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_DES_CFG0_DES_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 MOEBDIV Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 MoebiusDivider
 *
 * Register: \a SD10G65:SD10G65_DES:SD10G65_MOEBDIV_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core NOT flags valid data
 * detected
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_A
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_A(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * Bandwidth selection for cp/md of cdr loop when core flags valid data
 * detected
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CDR_SEL_B
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CDR_SEL_B(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * Bandwidth selection for cp/md signals towards core
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_BW_CORE_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_BW_CORE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * CP/MD swapping
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_CPMD_SWAP
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_CPMD_SWAP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_CPMD_SWAP  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_CPMD_SWAP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * MD divider enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_DIV32_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIV32_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIV32_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIV32_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Divider disable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0 . MOEBDIV_DIS
 */
#define  VTSS_F_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIS  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_DES_SD10G65_MOEBDIV_CFG0_MOEBDIV_DIS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD10G65:SD10G65_OB
 *
 * SD10G65 OB Configuration and Status Register set
 */


/** 
 * \brief SD10G65 OB Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 OB.
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_OB_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Invert input to serializer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . SER_INV
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SER_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SER_INV  VTSS_BIT(23)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SER_INV(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Control of common mode voltage of clock buffer between synthesizer and
 * OB.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . CLK_BUF_CMV
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_CLK_BUF_CMV(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Pool of spare bits for use in late design changes.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . OB_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_OB_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_OB_SPARE_POOL     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_OB_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * Bypass data path (e.g. for JTAG), allows to drive output when
 * EN_DIRECT=1 and EN_OB=1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . BYP_D
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_BYP_D(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_BYP_D  VTSS_BIT(18)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_BYP_D(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Set digital part into pseudo reset
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . RST
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_RST  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_RST(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Enable pad loop
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . EN_PAD_LOOP
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_PAD_LOOP(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Enable input loop
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . EN_INP_LOOP
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_INP_LOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_INP_LOOP  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_INP_LOOP(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable direct path
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . EN_DIRECT
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_DIRECT(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_DIRECT  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_DIRECT(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Enable output buffer and serializer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . EN_OB
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_OB(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_OB  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_EN_OB(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Selects amplitude range controled via levn. See description of levn.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . INCR_LEVN
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_INCR_LEVN(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_INCR_LEVN  VTSS_BIT(8)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_INCR_LEVN(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Interface width
 *
 * \details 
 * 0: 8
 * 1: 10
 * 2: 16
 * 3: 20
 * 4: 32
 * 5: 40
 * 6-7: Reserved
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . SEL_IFW
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_SEL_IFW(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Amplitude control value. Step size is 25 mVpp, decreasing amplitude with
 * increasing control value. Range depends on incr_levn. Coding for
 * incr_levn=0: 31: 500mVpp, 30: 525mVpp, 29: 550mVpp, ..., 0: 1275mVpp.
 * Coding for incr_levn=1: 31: 300mVpp, 30: 325mVpp, 29: 350mVpp, .., 0:
 * 1075mVpp. (Note: maximum achievable amplitude depends on the supply
 * voltage)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG0 . LEVN
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_LEVN(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_LEVN     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG0_LEVN(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 OB Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 OB.
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_OB_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Enable amplitude compensation of AB bleed current
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . AB_COMP_EN
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_AB_COMP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_AB_COMP_EN  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_AB_COMP_EN(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Bleed current for class AB operation of driver
 *
 * \details 
 * 0: 1%
 * 1: 0.5%
 * 2: 2%
 * 3: reserved
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . DIODE_CUR
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_DIODE_CUR(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/** 
 * \brief
 * Level shift ctrl of class AB bias generator
 *
 * \details 
 * 0: 50mV
 * 1: 100mV
 * 2:150mV
 * 3: 200mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . LEV_SHFT
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT(x)  VTSS_ENCODE_BITFIELD(x,21,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT     VTSS_ENCODE_BITMASK(21,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_LEV_SHFT(x)  VTSS_EXTRACT_BITFIELD(x,21,2)

/** 
 * \brief
 * Slew rate ctrl of OB (R), encoding see PREDRV_C_CTRL
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . PREDRV_R_CTRL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL(x)  VTSS_ENCODE_BITFIELD(x,18,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL     VTSS_ENCODE_BITMASK(18,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_R_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,18,2)

/** 
 * \brief
 * Slew rate ctrl of OB (C)
 *
 * \details 
 * C=3 R=3: 25ps
 * C=3 R=0: 35ps
 * C=0 R=3: 55ps
 * C=1 R=0: 70ps
 * C=0 R=0: 120 ps
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . PREDRV_C_CTRL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_PREDRV_C_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * Tail voltage driver settings
 *
 * \details 
 * 0: reserved
 * 1: 75mV
 * 2: 100mV
 * 4: 125mV
 * 8: 150mV
 * 16: 175mV
 * 32: 200mV
 * Intermediate values possible when setting two bits
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . VTAIL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VTAIL(x)  VTSS_ENCODE_BITFIELD(x,10,6)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VTAIL     VTSS_ENCODE_BITMASK(10,6)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VTAIL(x)  VTSS_EXTRACT_BITFIELD(x,10,6)

/** 
 * \brief
 * Ctrl of cascade volt in drv stage
 *
 * \details 
 * 0: reserved
 * 1: 0
 * 2: 1/12
 * 4: 2/12
 * 8: 3/12
 * 16: 4/12
 * Intermediate values possible when setting two bits
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . VCAS
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VCAS(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VCAS     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_VCAS(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * Additional resistor calibration trim
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . R_COR
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_COR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_COR  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_COR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Offset resistance adjustment for CML cells (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG1 . R_I
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_I(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_I     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG1_R_I(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 OB Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 OB. D_filter contains four 6-bit
 * precalculated DA input values. Note the differences in programming for
 * various interface (IF) bit widths. For calculation details see
 * documentation of OB10G.
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_OB_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG2(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Transmit filter coefficients for FIR taps. Suggested start value (no
 * emphasis, max amplitude)
 *
 * \details 
 * 0x820820: for I/F width 8/10 bits
 * 0x7DF820: for I/F width 16/20/32/40 bits
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG2 . D_FILTER
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG2_D_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/** 
 * \brief SD10G65 OB Configuration register 3  access to receiver detect functionality
 *
 * \details
 * Configuration register 3 for SD10G65 OB.
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_OB_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * Indicates a completed receiver detect measurement. Should be one few us
 * after rec_det_start is set.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_DONE
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_DONE  VTSS_BIT(18)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_DONE(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Rising edge starts receiver detect measurement. Has to be keept set
 * until rec_det_value has been read.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_START
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_START(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_START  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_START(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Enable reciver detect function. MUST be disabled for normal operation
 * !!!
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_ENABLE
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_ENABLE  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Reciver detect threshold (suggested start value: 2)
 *
 * \details 
 * 0: reserved
 * 1: 0mV
 * 2: 8.3mV
 * 4: 16.7mV
 * 8: 25mV
 * Intermediate values possible when setting two bits
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_THRS
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_THRS(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_THRS     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_THRS(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Holds the time between the start and the flag of the receiver detect
 * measuremnet. Time [ns +/- 4 ns] = 8 * value - 12
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_OB_CFG3 . REC_DET_VALUE
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,12)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE     VTSS_ENCODE_BITMASK(0,12)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_OB_CFG3_REC_DET_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,12)


/** 
 * \brief SD10G65 SBUS TX CFG Service-Bus related setting
 *
 * \details
 * Configuration register for Service-Bus related setting. Note: this
 * register is only used for configuration if Tx is used stand alone,
 * otherwise SD10G65_SBUS_RX_CFG (Rx macro) is used for configuration!
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_SBUS_TX_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Pool of spare bits for use in late design changes.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_SPARE_POOL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Enable BiDi loop driver for F2DF testing
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_LOOPDRV_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_LOOPDRV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_LOOPDRV_ENA  VTSS_BIT(12)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_LOOPDRV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Analog test output
 *
 * \details 
 * 0: l0_ctrlspeed[0]
 * 1: vbulk
 * 2: nref
 * 3: vref820m
 * 4: vddfilt
 * 5: vddfilt
 * 6: ie_aout
 * 7: ib_aout
 * 8: ob_aout2
 * 9: pll_frange
 * 10: pll_srange
 * 11: pll_vreg820m_tx
 * 12: pll_vreg820m_rx
 * 13: ob_aout_n
 * 14: ob_aout_p
 * 15: vddfilt
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_ANAOUT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_SEL     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Enable analog test output
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_ANAOUT_EN
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_EN  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_ANAOUT_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Offset value for BIAS resistor calibration (2-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_RCOMP
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_RCOMP     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Bias speed selection
 *
 * \details 
 * 0: Below 4Gbps
 * 1: 4Gbps to 6Gbps
 * 2: 6Gbps to 9Gbps
 * 3: Above 9Gbps
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_BIAS_SPEED_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Bias enable
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG . SBUS_BIAS_EN
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65_TX subversion revision number
 *
 * \details
 * Subversion revision number for the RTL used in SD10G65_TX
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_TX_SVN_ID
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_TX_SVN_ID(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * SVN revision number of RTL sources
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_TX_SVN_ID . TX_SVN_ID
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_TX_SVN_ID_TX_SVN_ID(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_TX_SVN_ID_TX_SVN_ID     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_TX_SVN_ID_TX_SVN_ID(x)  (x)


/** 
 * \brief SD10G65_TX Revision ID
 *
 * \details
 * Revision numbers of the analog sub IPs used in the SD10G65_TX
 *
 * Register: \a SD10G65:SD10G65_OB:SD10G65_TX_REV_ID
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID(target)  VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Feature set number of output buffer (ob10g_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID . OB_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_OB_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Feature set number of synthesizer (syn_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID . SYNTH_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_SYNTH_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Feature set number of RC-PLL (pll10g_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID . RCPLL_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_RCPLL_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Feature set number of Toplevel (sd10g65_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID . TOP_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_SD10G65_OB_SD10G65_TX_REV_ID_TOP_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G65:SD10G65_IB
 *
 * SD10G65 IB Configuration and Status Register set
 */


/** 
 * \brief SD10G65 IB Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 IB. Note: Configuration bit-grp
 * IB_CLKDIV_ENA was named IB_VSCOPE_CLK_ENA in an early revision of the
 * input buffer.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * Offset resistance adjustment for CML cells (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_RCML_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ(x)  VTSS_ENCODE_BITFIELD(x,27,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ     VTSS_ENCODE_BITMASK(27,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RCML_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,27,4)

/** 
 * \brief
 * Select termination voltage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_TERM_V_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL     VTSS_ENCODE_BITMASK(23,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_V_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,4)

/** 
 * \brief
 * Enable common mode termination
 *
 * \details 
 * 0: no common mode termination (only AC-common mode termination)
 * 1: termination to VDDI
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_TERM_VDD_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_VDD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_VDD_ENA  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_TERM_VDD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Shifts resistance adjustment value ib_rib_adj by +1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_RIB_SHIFT
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_SHIFT(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_SHIFT  VTSS_BIT(21)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_SHIFT(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Offset resistance adjustment for termination (two-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_RIB_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ(x)  VTSS_ENCODE_BITFIELD(x,17,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ     VTSS_ENCODE_BITMASK(17,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_RIB_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,17,4)

/** 
 * \brief
 * Is or'ed to the prim. input of the macro: sx_direct_data_ena_rx_i and is
 * used to enable the direct data path.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_DIRECT_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DIRECT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DIRECT_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DIRECT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable DFE stage (gates IB_ISEL_DFE)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_DFE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DFE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DFE_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_DFE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Select input buffer input signal
 *
 * \details 
 * 0: normal operation
 * 1: -6dB input
 * 2: OB->IB data loop or test signal
 * 3: RESERVED
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_SIG_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Controls Bulk Voltage of High Speed Cells
 *
 * \details 
 * 0: High
 * 1: Low (mission mode)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_VBULK_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VBULK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VBULK_SEL  VTSS_BIT(11)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VBULK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable for IA including ACJtag
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_IA_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_ENA  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 0 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_IA_SDET_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_SDET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_SDET_ENA  VTSS_BIT(9)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IA_SDET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * Enable for IA signal detect circuit (IB_SDET_SEL = 1 required)
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_IE_SDET_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IE_SDET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IE_SDET_ENA  VTSS_BIT(8)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_IE_SDET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * Enable for level detect circuit
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_LD_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_LD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_LD_ENA  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_LD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Enable for 1V mode
 *
 * \details 
 * 0: VDDI=1.2V
 * 1: VDDI=1.0V
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_1V_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_1V_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_1V_ENA  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_1V_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable clock dividers in sampling stag
 *
 * \details 
 * 0: Disable (use in double rate mode)
 * 1: Enable (use in full rate mode)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_CLKDIV_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_CLKDIV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_CLKDIV_ENA  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_CLKDIV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Routed to analog macro but not used inside! Vscope clock source is
 * selected via ib_sel_vclk.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_SPARE_POOL2
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SPARE_POOL2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SPARE_POOL2  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SPARE_POOL2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable VScope Path of Sampling-Stage
 *
 * \details 
 * 0: Disable
 * 1: Enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_VSCOPE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VSCOPE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VSCOPE_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_VSCOPE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable SAMpling stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_SAM_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SAM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SAM_ENA  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_SAM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable EQualiZation stage
 *
 * \details 
 * 0: Disable
 * 1: Enable (mission mode)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG0 . IB_EQZ_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_EQZ_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_EQZ_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG0_IB_EQZ_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief SD10G65 IB Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Inductor peaking of 1. stage Input buffer
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_AMP_L
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_L(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer0 (over all 2. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3db at 8GHz
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L0
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L0(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer1 (over all 3. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L1
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L1(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer2 (over all 4. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking > 3dB at 8GHz
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_L2
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_L2(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Inductor peaking of EQ-Buffer3 (over all 5. stage)
 *
 * \details 
 * 0: no peaking
 * 15: max. peaking
 * max. peaking >3dB at 8GHz
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_AGC_L
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AGC_L(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * C-gain peaking for IB-stage
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_ib
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_AMP_C
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_AMP_C(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage0
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es0
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C0
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C0(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage1
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es1
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C1
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C1(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * C-gain peaking for EQ-stage2
 *
 * \details 
 * 0: no peaking
 * 7: max. peaking
 * corner frequency adjustment with ib_eqz_c_adj_es2
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG1 . IB_EQZ_C2
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG1_IB_EQZ_C2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief SD10G65 IB Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG2(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Gain of Input Buffer
 *
 * \details 
 * 0-511 gain adjustment only in first stage > 511 gain in first stage at
 * max.
 * 512-639 gain in 2.stage increased from 1 to 2 > 639 gain = 2
 * 640-767 gain in 3.stage increased from 1 to 2 >767 gain = 2
 * 768-895 gain in 4.stage increased from 1 to 2
 * >895 gain at max.
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_GAIN
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_ENCODE_BITFIELD(x,18,10)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN     VTSS_ENCODE_BITMASK(18,10)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,18,10)

/** 
 * \brief
 * Amplification (gain) of AGC in Input Buffer (normal operation)
 *
 * \details 
 * after gain calibration
 * 0: gain = 0.3
 * 255: gain = 1.5
 * if disp/disn is active dac function for dfe gain calibration
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_AGC
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC(x)  VTSS_ENCODE_BITFIELD(x,10,8)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC     VTSS_ENCODE_BITMASK(10,8)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_AGC(x)  VTSS_EXTRACT_BITFIELD(x,10,8)

/** 
 * \brief
 * Offset value for IB-stage of Input Buffer
 *
 * \details 
 * 512: neutral
 * > 512: positive
 * < 512: negative
 * range +/- 600mV (low gain) to +/-30mV (high gain)
 * gain dependent offset sensitivity requiered for Base line wander
 * compensation
 * not supported in test chip
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG2 . IB_EQZ_OFFSET
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG2_IB_EQZ_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief SD10G65 IB Configuration register 3
 *
 * \details
 * Configuration register 1 for SD10G65 IB. Note: the behavior of
 * IB_EQ_LD1_OFFSET changes when APC is disabled. In this case
 * IB_EQ_LD1_OFFSET directly controls the level for Level-Detect circuitry
 * 1. Coding: 0: 20mV, 1: 25mV, ... 63: 340mV.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Dividing factor for SDET and LD circuits of IE.
 *
 * \details 
 * 0: 128
 * 1: 32
 * 2: 8
 * 3: 4
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_LDSD_DIVSEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_LDSD_DIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * Clock dividing factor for Signal Detect circuit of IA
 *
 * \details 
 * 0: 2
 * ...
 * 7: 256
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_SDET_CLK_DIV
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,27,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV     VTSS_ENCODE_BITMASK(27,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,27,3)

/** 
 * \brief
 * Force Signal-Detect output to high level
 *
 * \details 
 * 0: Normal operation
 * 1: Force sigdet high
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_SET_SDET
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SET_SDET(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Selects source of signal detect (ib_X_sdet_ena must be enabled
 * accordingly)
 *
 * \details 
 * 0: IA
 * 1: IE
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_SDET_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_SEL  VTSS_BIT(24)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_SDET_SEL(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Selects source of direct data path to core
 *
 * \details 
 * 0: IE
 * 1: IA
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_DIRECT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_DIRECT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_DIRECT_SEL  VTSS_BIT(23)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_DIRECT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * With APC enabled level offset (6bit-signed) compared to IB_EQ_LD0_LEVEL
 * for Level-Detect circuitry 1. Saturating between 20mV and 340mV. See
 * also note in register description.
 *
 * \details 
 * 0: no offset
 * 1: +5mV
 * 31: +155mV
 * 63(= -1): -5mV
 * 32(= -32): -160mV.
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_EQ_LD1_OFFSET
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_ENCODE_BITFIELD(x,17,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET     VTSS_ENCODE_BITMASK(17,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD1_OFFSET(x)  VTSS_EXTRACT_BITFIELD(x,17,6)

/** 
 * \brief
 * Level for Level-Detect circuitry 0.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * ...
 * 40: 220mV
 * ...
 * 63: 340mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_EQ_LD0_LEVEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,11,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL     VTSS_ENCODE_BITMASK(11,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_EQ_LD0_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,11,6)

/** 
 * \brief
 * Threshold value for IE Signal-Detect.
 *
 * \details 
 * 0: 20mV
 * 1: 25mV
 * 2: 30mV
 * ...
 * 63: 340mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_IE_SDET_LEVEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,5,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL     VTSS_ENCODE_BITMASK(5,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IE_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,5,6)

/** 
 * \brief
 * Threshold value for IA Signal-Detect.
 *
 * \details 
 * 0: 0mV
 * ...
 * 8: 80mV
 * ...
 * 31: 310mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG3 . IB_IA_SDET_LEVEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG3_IB_IA_SDET_LEVEL(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 IB Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG4
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 1.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_IB
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_ENCODE_BITFIELD(x,30,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB     VTSS_ENCODE_BITMASK(30,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_IB(x)  VTSS_EXTRACT_BITFIELD(x,30,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 2.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES2
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_ENCODE_BITFIELD(x,28,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2     VTSS_ENCODE_BITMASK(28,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES2(x)  VTSS_EXTRACT_BITFIELD(x,28,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 3.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES1
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES1(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * corner frequency selection for c-gain peaking 4.stage
 *
 * \details 
 * 0: lowest corner frequency
 * 3: highest corner frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_ADJ_ES0
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_ADJ_ES0(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Coder mode: APC L value to IE inductance
 *
 * \details 
 * 0: equ. distributed (double step 3->4)
 * 1: equ. distributed (no change 6+7)
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_L_MODE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_ENCODE_BITFIELD(x,21,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE     VTSS_ENCODE_BITMASK(21,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_L_MODE(x)  VTSS_EXTRACT_BITFIELD(x,21,3)

/** 
 * \brief
 * Coder mode: APC C value to IE capacitance
 *
 * \details 
 * 0: equ. distributed
 * 2: 1st buffer max - 2nd buffer max - ...
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_EQZ_C_MODE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_EQZ_C_MODE(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/** 
 * \brief
 * Threshold value (offset) for vscope-high sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_VSCOPE_H_THRES
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_ENCODE_BITFIELD(x,12,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES     VTSS_ENCODE_BITMASK(12,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_H_THRES(x)  VTSS_EXTRACT_BITFIELD(x,12,6)

/** 
 * \brief
 * Threshold value (offset) for vscope-low sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_VSCOPE_L_THRES
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_VSCOPE_L_THRES(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Threshold value (offset) for main sampling path
 *
 * \details 
 * 0: -max
 * 31: -0
 * 32: +0
 * 63: +max (depending on calibration)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG4 . IB_MAIN_THRES
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG4_IB_MAIN_THRES(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 5
 *
 * \details
 * Configuration register 5 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG5
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * Test generator amplitude setting
 *
 * \details 
 * 0: 0mV
 * ...
 * 15: 150mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_AMPL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * Test generator enable but data path selected with 'ib_sig_sel' (disable
 * input loop if testgenerator is used)
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_ENA  VTSS_BIT(27)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Test generator data
 *
 * \details 
 * 0: low
 * 1: high
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_DATA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_DATA  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_DATA(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Test generator data toggle enable
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_TSTGEN_TOGGLE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_TOGGLE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_TOGGLE_ENA  VTSS_BIT(25)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_TSTGEN_TOGGLE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Enable jump to opposite half of h-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_JUMPH_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPH_ENA  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Enable jump to opposite half of l-channel
 *
 * \details 
 * 0: Post main sampler
 * 1: Pre main sampler
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_JUMPL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPL_ENA  VTSS_BIT(21)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_JUMPL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * DFE output disable required to calibrate IS
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=196mV if ena1V = '1' (1V mode)
 * ampldfe=260mV if ena1V = '0' (1.2V mode)
 * 
 * xx= TBD
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_DFE_DIS
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS(x)  VTSS_ENCODE_BITFIELD(x,19,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS     VTSS_ENCODE_BITMASK(19,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_DFE_DIS(x)  VTSS_EXTRACT_BITFIELD(x,19,2)

/** 
 * \brief
 * AGC output disable required to calibrate DFE-gain
 *
 * \details 
 * 0: mission mode
 * 3: Vout = 0V
 * 1: Vout= xx*ampldfe/64
 * 2: Vout=-xx*ampldfe/64
 * 
 * ampldfe=270mV if ena1V = '1' (1V mode)
 * ampldfe=360mV if ena1V = '0' (1.2V mode)
 * 
 * xx=
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_AGC_DIS
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS(x)  VTSS_ENCODE_BITFIELD(x,17,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS     VTSS_ENCODE_BITMASK(17,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_AGC_DIS(x)  VTSS_EXTRACT_BITFIELD(x,17,2)

/** 
 * \brief
 * Selects EQ Level Detect for calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_EQ_LD_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_EQ_LD_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_EQ_LD_CAL_ENA  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_EQ_LD_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Selects IS threshold circuit for calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_THRES_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_THRES_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_THRES_CAL_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_THRES_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Selects IS offset circuit for calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_IS_OFFS_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IS_OFFS_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IS_OFFS_CAL_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IS_OFFS_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Selects IA offset circuit for calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_IA_OFFS_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IA_OFFS_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IA_OFFS_CAL_ENA  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IA_OFFS_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Selects IE Signal Detect for calibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_IE_SDET_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IE_SDET_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IE_SDET_CAL_ENA  VTSS_BIT(12)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_IE_SDET_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Enable calibration in order to eliminate hysteresis
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_HYS_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_HYS_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_HYS_CAL_ENA  VTSS_BIT(11)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_HYS_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enables IS MUX in detblk1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_CALMUX_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_CALMUX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_CALMUX_ENA  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_CALMUX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Selects calibration target (sample stage threshold, sample stage offset,
 * aux.-stage offset), dependend on calibration group, see encoding.
 *
 * \details 
 * When ib_thres_cal_ena = 1
 * 0: MD0 threshold
 * 1: MD1 threshold
 * 2: CP0 threshold
 * 3: CP1 threshold
 * 4: VH0 threshold
 * 5: VH1 threshold
 * 6: VL0 threshold
 * 7: VL1 threshold
 * When ib_is_offs_cal_ena = 1
 * 0: MD0 offset
 * 1: MD1 offset
 * 2: CP0 offset
 * 3: CP1 offset
 * 4: VH0 offset
 * 5: VH1 offset
 * 6: VL0 offset
 * 7: VL1 offset
 * When ib_ia_offs_cal_ena = 1
 * 0: Observe0 offset
 * 1: Observe1 offset
 * 2: Observe0 threshold
 * 3: Observe1 threshold
 * (MSB not used)
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_OFFS_BLKSEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_BLKSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/** 
 * \brief
 * Calibration value for IA/IS. Values for threshold calibration get
 * inverted for negative threshold voltages (ib_vscope_h_thres,
 * ib_vscope_l_thres or ib_main_thres).
 *
 * \details 
 * For offset calibration
 * 0: -max_offset * 32/32
 * 31: -max_offset * 1/32
 * 32: +max_offset * 1/32
 * 63: +max_offset * 32/32
 * For threshold calibration
 * 0: min_threshold
 * 63: max_threshold
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG5 . IB_OFFS_VALUE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG5_IB_OFFS_VALUE(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 6
 *
 * \details
 * Configuration register 6 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG6
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG6(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * 0dB Gain adjustment for EQZ-stages of Input Buffer
 *
 * \details 
 * level at LD0 = LD1 -> 0dB
 * level range 160mV-220mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG6 . IB_EQZ_GAIN_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,7)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,7)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,7)

/** 
 * \brief
 * Enable automatic AGC adjustment
 *
 * \details 
 * 1: AGC is adjusted automatically (IB_EQZ_AGC_ADJ value is not used)
 * 0: AGC is adjusted with value stored in IB_EQZ_AGC_ADJ
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG6 . IB_AUTO_AGC_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_AUTO_AGC_ADJ(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_AUTO_AGC_ADJ  VTSS_BIT(12)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_AUTO_AGC_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Gain adjustment of AGC-amplifier
 *
 * \details 
 * Bitgroup should be set to 2*IB_DFE_GAIN_ADJ
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG6 . IB_EQZ_AGC_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_ENCODE_BITFIELD(x,5,7)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ     VTSS_ENCODE_BITMASK(5,7)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_EQZ_AGC_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,5,7)

/** 
 * \brief
 * Range for offset calibration of all sampling pathes
 *
 * \details 
 * 0: 0mV
 * 32: 80mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG6 . IB_SAM_OFFS_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG6_IB_SAM_OFFS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief SD10G65 IB Configuration register 7
 *
 * \details
 * Configuration register 7 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG7
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7(target)  VTSS_IOREG(target,0x27)

/** 
 * \brief
 * Initial value for calibration of main sampling path
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_MAIN_THRES_CAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_ENCODE_BITFIELD(x,23,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL     VTSS_ENCODE_BITMASK(23,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_MAIN_THRES_CAL(x)  VTSS_EXTRACT_BITFIELD(x,23,6)

/** 
 * \brief
 * Selects higher or lower DFE offset for IS calibration
 *
 * \details 
 * 0: ib_dfe_offset_l
 * 1: ib_dfe_offset_h
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_H_L
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H_L(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H_L  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H_L(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Gain adjustment of DFEamplifier
 *
 * \details 
 * DFE Gain 1 Volt mode = 0dB
 * 1.2 Volt mode 1dB
 * measurement with int. DAC and Vscope Channels
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_GAIN_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Select configuration of DFEamplifier gain adjustment
 *
 * \details 
 * 0: Normal operation (APC can take over control)
 * 1: Enforce configuration via IB_DFE_GAIN_ADJ
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_GAIN_ADJ_S
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Higher threshold offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_H
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_ENCODE_BITFIELD(x,6,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H     VTSS_ENCODE_BITMASK(6,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_H(x)  VTSS_EXTRACT_BITFIELD(x,6,6)

/** 
 * \brief
 * Lower sample offset of DFE buffer for IS calibration
 *
 * \details 
 * 0: 0mv
 * 63: 200mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG7 . IB_DFE_OFFSET_L
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_OFFSET_L(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 IB Configuration register 8
 *
 * \details
 * Configuration register 8 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG8
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8(target)  VTSS_IOREG(target,0x28)

/** 
 * \brief
 * not used
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_AOUT_MUX
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_MUX(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_MUX  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_MUX(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Enable analog output decoder in IE
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_AOUT_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_ENA  VTSS_BIT(30)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Select analog signal routed to analog test output from either IB
 * sampling stage or equalizer. See also SD10G65_IB_CFG8.IB_AOUT_ENA and
 * SD10G65_SBUS_RX_CFG.SBUS_ANAOUT_SEL.
 *
 * \details 
 * Encoding for sampling stage:
 * 0: VCMT
 * 1: VCMR
 * 2: CMLCI
 * 3: RESIDL
 * 4: RESCML
 * 5: CMLSU
 * 6: CMLBI
 * 7: CMLRA
 * 8: VCN
 * 9: VCP
 * 10: DIFSRC
 * 11: VREGN
 * 12: VREGP
 * 13: TSTSRC
 * 14: TSTDRN
 * 15: TSTRES
 * 16: CMLBF1P
 * 17: CMLBF1N
 * 18: CMLBF2P
 * 19: CMLBF2P
 * 20: CMLBF3P
 * 21: CMLBF3P
 * 22: CMLBF4P
 * 23: CMLBF4P
 * 24 to 31: same coding as for 16 to 23
 * Encoding for equalizer:
 * 0: n.a.
 * 1: vddi_int
 * 2: eq1_vreg
 * 3: eq2_vreg
 * 4: eq3_vreg
 * 5: agc_vreg
 * 6: dfe_vreg
 * 7: dfe_p
 * 8: n.a.
 * 9: ib_cmv
 * 10: eq1_cmv
 * 11: eq2_cmv
 * 12: eq3_cmv
 * 13: agc_cmv
 * 14: dfe_cmv
 * 15: dfe_n
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_AOUT_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_POOL(x)  VTSS_ENCODE_BITFIELD(x,25,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_POOL     VTSS_ENCODE_BITMASK(25,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_AOUT_POOL(x)  VTSS_EXTRACT_BITFIELD(x,25,5)

/** 
 * \brief
 * EQZ current control
 *
 * \details 
 * 0: mission mode
 * 1: 1.5% current increase
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_EQ_CURR
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_EQ_CURR(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_EQ_CURR  VTSS_BIT(21)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_EQ_CURR(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Use separate vscope clock for vscope-channels
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_SEL_VCLK
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_SEL_VCLK(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_SEL_VCLK  VTSS_BIT(20)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_SEL_VCLK(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Bias regulation mode
 *
 * \details 
 * 0: constant resistor
 * 1: constant current
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_BIAS_MODE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_MODE  VTSS_BIT(19)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_MODE(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Enables neutral setting of latches
 *
 * \details 
 * 1: Reset to mid values
 * 0: Normal operation
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_LAT_NEUTRAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_LAT_NEUTRAL(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_LAT_NEUTRAL  VTSS_BIT(18)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_LAT_NEUTRAL(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Invert observe signal from auxilary stage that goes to calibration FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_IA_DOFS
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_DOFS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_DOFS  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_DOFS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Invert observe signal from sample stage that goes to calibration FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_IS_DOFS
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IS_DOFS(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IS_DOFS  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IS_DOFS(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Invert calibration value coming from the calibration FSM for IA
 * calibration.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_IA_CAL_VAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_CAL_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_CAL_VAL  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_IA_CAL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Invert calibration value coming from the calibration FSM for IS
 * threshold calibration.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_THR_CAL_VAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Invert calibration value coming from the calibration FSM for IS offset
 * calibration.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_OFFS_CAL_VAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_OFFS_CAL_VAL(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_OFFS_CAL_VAL  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_OFFS_CAL_VAL(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Amplitude of cml stages inside IS
 *
 * \details 
 * 0: 200mVppd
 * 7: 240mVppd
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_CML_AMPL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL(x)  VTSS_ENCODE_BITFIELD(x,10,3)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL     VTSS_ENCODE_BITMASK(10,3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_AMPL(x)  VTSS_EXTRACT_BITFIELD(x,10,3)

/** 
 * \brief
 * Gain of cml stages inside IS
 *
 * \details 
 * 0: 3dB
 * 31: 6dB
 * 63: 9dB
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_BIAS_ADJ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_BIAS_ADJ(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Current through CML Cells
 *
 * \details 
 * 0: 150%
 * 5: 100%
 * 15: 50%
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG8 . IB_CML_CURR
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG8_IB_CML_CURR(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 IB Configuration register 9  automatically adapted DFE coefficients
 *
 * \details
 * Configuration register 9 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG9
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG9(target)  VTSS_IOREG(target,0x29)

/** 
 * \brief
 * Weighting for fourth DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF4
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4(x)  VTSS_ENCODE_BITFIELD(x,24,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4     VTSS_ENCODE_BITMASK(24,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF4(x)  VTSS_EXTRACT_BITFIELD(x,24,5)

/** 
 * \brief
 * Weighting for third DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF3
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF3(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * Weighting for second DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF2
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF2(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Weighting for first DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG9 . IB_DFE_COEF1
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG9_IB_DFE_COEF1(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief SD10G65 IB Configuration register 10 JTAG related setting
 *
 * \details
 * Configuration register 10 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG10
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10(target)  VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * Data offset calibration result IA stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_DOFFS_CAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DOFFS_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DOFFS_CAL  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DOFFS_CAL(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Data offset calibration result IS stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IS_DOFFS_CAL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IS_DOFFS_CAL(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IS_DOFFS_CAL  VTSS_BIT(30)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IS_DOFFS_CAL(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET_PEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_PEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_PEDGE  VTSS_BIT(29)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_PEDGE(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Detection of toggling signal at PADP and PADN
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET_NEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_NEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_NEDGE  VTSS_BIT(28)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET_NEDGE(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Result signal detect of IE stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_SDET
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET(x)  VTSS_ENCODE_BITFIELD(!!(x),27,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET  VTSS_BIT(27)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_SDET(x)  VTSS_EXTRACT_BITFIELD(x,27,1)

/** 
 * \brief
 * Result signal detect of IA stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_SDET
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_SDET(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD1_PEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_PEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_PEDGE  VTSS_BIT(25)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_PEDGE(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Result of Level-Detect1 (after ES2-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD1_NEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_NEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_NEDGE  VTSS_BIT(24)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD1_NEDGE(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD0_PEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_PEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_PEDGE  VTSS_BIT(23)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_PEDGE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Result of Level-Detect0 (after IB-stage of EQZ) circuitry
 *
 * \details 
 * 1: Input level above threshold defined by IB_EQ_LD_LEV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_EQZ_LD0_NEDGE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_NEDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_NEDGE  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_EQZ_LD0_NEDGE(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Direct Data output from IE block
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IE_DIRECT_DATA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_DIRECT_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_DIRECT_DATA  VTSS_BIT(21)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IE_DIRECT_DATA(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Direct Data output from IA block
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_IA_DIRECT_DATA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DIRECT_DATA(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DIRECT_DATA  VTSS_BIT(20)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_IA_DIRECT_DATA(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * Receive enable for BiDi loop (a.k.a. PAD loop o. TX->RX loop). Is or'ed
 * with primary input: ib_pad_loop_ena_i. Disable testgenerator
 * 'ib_tstgen_ena' if input loop is used
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_LOOP_REC
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_REC(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Drive enable for BiDi loop (a.k.a. Input loop o. RX->TX loop). Is or'ed
 * with primary input: ib_inp_loop_ena_i. Is overruled by PAD loop.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_LOOP_DRV
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_DRV(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_DRV  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_LOOP_DRV(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * JTAG debug p-output
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_OUT_P
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_P(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_P  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_P(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * JTAG debug n-output
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_OUT_N
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_N(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_N  VTSS_BIT(9)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_OUT_N(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * JTAG debug threshold
 *
 * \details 
 * 0: 0mV
 * 1: 10mV
 * 31: 310mV
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_THRES
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES(x)  VTSS_ENCODE_BITFIELD(x,4,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES     VTSS_ENCODE_BITMASK(4,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_THRES(x)  VTSS_EXTRACT_BITFIELD(x,4,5)

/** 
 * \brief
 * JTAG debug p-input
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_IN_P
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_P(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_P  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_P(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * JTAG debug n-input
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_IN_N
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_N(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_N  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_IN_N(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * JTAG debug clk
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_CLK
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_CLK  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_CLK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * JTAG debug enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG10 . IB_JTAG_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG10_IB_JTAG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 IB Configuration register 11 JTAG related setting
 *
 * \details
 * Configuration register 11 for SD10G65 IB.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_IB_CFG11
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11(target)  VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11 . IB_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_SPARE_POOL  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * DFE Bias current settings (bit-group is gated with IB_DFE_ENA)
 *
 * \details 
 * 0: DFE disabled
 * 1: Minimum current
 * 15: Maximum current
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11 . IB_DFE_ISEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_DFE_ISEL(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * Increase current in first stage (only available in 1.2 Volt mode)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11 . IB_ENA_400_INP
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_ENA_400_INP(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_ENA_400_INP  VTSS_BIT(11)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_ENA_400_INP(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Gain temperature coefficient for DFE stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11 . IB_TC_DFE
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_DFE(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * Gain temperature coefficient for AGC stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_IB_CFG11 . IB_TC_EQ
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_IB_CFG11_IB_TC_EQ(x)  VTSS_EXTRACT_BITFIELD(x,1,5)


/** 
 * \brief SD10G65 SBUS RX CFG Service-Bus related setting
 *
 * \details
 * Configuration register for Service-Bus related setting. Note: SBUS
 * configuration applies for RX/TX aggregates only, any configuration
 * applied to SBUS_TX_CFG (output buffer cfg space) will be ignored.
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_SBUS_RX_CFG
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG(target)  VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Pool of spare bits for use in late design changes.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Enable BiDi loop driver for F2DF testing
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_LOOPDRV_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_LOOPDRV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_LOOPDRV_ENA  VTSS_BIT(12)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_LOOPDRV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/** 
 * \brief
 * Analog test output
 *
 * \details 
 * 0: l0_ctrlspeed[0]
 * 1: vbulk
 * 2: nref
 * 3: vref820m
 * 4: vddfilt
 * 5: vddfilt
 * 6: ie_aout
 * 7: ib_aout
 * 8: ob_aout2
 * 9: pll_frange
 * 10: pll_srange
 * 11: pll_vreg820m_tx
 * 12: pll_vreg820m_rx
 * 13: ob_aout_n
 * 14: ob_aout_p
 * 15: vddfilt
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_ANAOUT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Enable analog test output multiplexer
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_ANAOUT_EN
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_EN  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_ANAOUT_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * Offset value for BIAS resistor calibration (2-complement)
 *
 * \details 
 * 1000: -8
 * 1111: -1
 * 0000: 0
 * 0111: 7
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_RCOMP
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,3,4)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP     VTSS_ENCODE_BITMASK(3,4)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,3,4)

/** 
 * \brief
 * Bias speed selection
 *
 * \details 
 * 0: Below 4Gbps
 * 1: 4Gbps to 6Gbps
 * 2: 6Gbps to 9Gbps
 * 3: Above 9Gbps
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_BIAS_SPEED_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Bias enable
 *
 * \details 
 * 1: Enable
 * 0: Disable
 *
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG . SBUS_BIAS_EN
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_BIAS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65_RX subversion revision number
 *
 * \details
 * Subversion revision number for the RTL used in SD10G65_RX
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_RX_SVN_ID
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_RX_SVN_ID(target)  VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * SVN revision number of RTL sources
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_SVN_ID . RX_SVN_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_SVN_ID_RX_SVN_ID(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_SVN_ID_RX_SVN_ID     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_SVN_ID_RX_SVN_ID(x)  (x)


/** 
 * \brief SD10G65_RX Revision ID
 *
 * \details
 * Revision numbers of the analog sub IPs used in the SD10G65_RX
 *
 * Register: \a SD10G65:SD10G65_IB:SD10G65_RX_REV_ID
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID(target)  VTSS_IOREG(target,0x2e)

/** 
 * \brief
 * Feature set number of deserializer (des10g_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID . DES_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,26,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID     VTSS_ENCODE_BITMASK(26,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_DES_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,26,6)

/** 
 * \brief
 * Feature set number of input buffer (ib10g_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID . IB_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,20,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID     VTSS_ENCODE_BITMASK(20,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_IB_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,20,6)

/** 
 * \brief
 * Feature set number of synthesizer (syn_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID . SYNTH_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,14,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID     VTSS_ENCODE_BITMASK(14,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_SYNTH_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,14,6)

/** 
 * \brief
 * Feature set number of RC-PLL (pll10g_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID . RCPLL_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_RCPLL_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Feature set number of Toplevel (sd10g65_N)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID . TOP_REV_ID
 */
#define  VTSS_F_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G65_SD10G65_IB_SD10G65_RX_REV_ID_TOP_REV_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G65:SD10G65_RX_RCPLL
 *
 * SD10G65 RX RCPLL Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX RCPLL Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 RX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0(target)  VTSS_IOREG(target,0x30)

/** 
 * \brief
 * Preload value of the ramp up counter, reduces ramp up time for higher
 * frequencies
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_START_CNT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Enable feedback clock usage instead of DES/SER par. clock,
 *
 * \details 
 * 0: disable
 * 1: enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_SYN_CLK_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable predivider for feedback clock to allow for faster clocks,
 *
 * \details 
 * 0: disable
 * 1: enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_FBDIV_PRE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_FBDIV_PRE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_FBDIV_PRE  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_FBDIV_PRE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Select output on pllf_ref_cnt_stat,
 *
 * \details 
 * 0: ref_cnt
 * 1: pll_cnt_diff
 * 2: syn_cnt
 * 3: pll_cnt
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_REF_CNT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_REF_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_REF_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_REF_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable PLL loop ctrl by pllf_loop_ena,
 *
 * \details 
 * 0: enable loop ctrl by FSM
 * 1: enable loop ctrl by pllf_loop_ena
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_LOOP_CTRL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable closed loop, selected with pllf_loop_ctrl_ena=1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_LOOP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Sets the ramp characteristic of the FSM, higher values give faster ramp
 * up but less accuracy,
 *
 * \details 
 * 0: normal (default) ramping
 * 1: faster ramping
 * 2: fastest ramping
 * 3: slow ramping
 * uses all possible values of r_ctrl
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_RAMP_MODE_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Enable VCO control signal out of range recalibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_OOR_RECAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable restart of FSM from frequency deviation/unlock condition
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_RST_FRQDET_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable restart of FSM from overrun
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_RST_OVERRUN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_load,
 *
 * \details 
 * 0: enable vco load by FSM
 * 1: enable vco load by pllf_vco_load
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_VCO_LOAD_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_fast,
 *
 * \details 
 * 0: enable vco fast by FSM
 * 1: enable vco load by pllf_vco_fast
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_VCO_FAST_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_FAST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_FAST_ENA  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_FAST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_slow,
 *
 * \details 
 * 0: enable vco slow by FSM
 * 1: enable vco load by pllf_vco_slow
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_VCO_SLOW_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable RCPLL FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0 . PLLF_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX RCPLL Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 RX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1(target)  VTSS_IOREG(target,0x31)

/** 
 * \brief
 * Target value: 1/vco_frq * par.bit.width * 512 * ref_clk_frq
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_REF_CNT_END
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * enable special BIST settings
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_BIST_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_BIST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_BIST_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_BIST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Select vco static frequency by load,
 *
 * \details 
 * 0: VCO off

 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_VCO_LOAD
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_LOAD(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_LOAD     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_LOAD(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Select vco static frequency by feedforward (higher freq.),
 *
 * \details 
 * 0: min. freq
 * 3: max. freq.
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_VCO_FAST
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_FAST(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_FAST     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_FAST(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Select vco static frequency by feedback (lower freq.),
 *
 * \details 
 * 0: max. freq
 * 3: min. freq.
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1 . PLLF_VCO_SLOW
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_SLOW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_SLOW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG1_PLLF_VCO_SLOW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SD10G65 RX RCPLL Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * Select VCO regulated supply (820mV),
 *
 * \details 
 * 0: 820mv
 * 4: 860mV
 * 6: 950mV
 * 7: short to VDDA
 * all others reserved
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_FBSEL820
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_FBSEL820(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_FBSEL820     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_FBSEL820(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Select VCO load switch gate voltage,
 *
 * \details 
 * 0: 1.4V
 * 1: 1.5V
 * 2: 1.6V
 * 3: 1.7V
 * 15: max.
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_VREG18
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Debug, short P bulk voltage of OpAmps,
 *
 * \details 
 * 0: P bulk unequal supply
 * 1: short to supply
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_SHORT_BULKHP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Debug, short N bulk voltage of OpAmps,
 *
 * \details 
 * 0: N bulk unequal 0
 * 1: short to VSSA
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_SHORT_BULKHN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Debug, short P bulk voltage of VCO,
 *
 * \details 
 * 0: P bulk unequal supply
 * 1: short to supply
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_SHORT_BULKP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Debug, short N bulk voltage of VCO,
 *
 * \details 
 * 0: N bulk unequal 0
 * 1: short to VSSA
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_SHORT_BULKN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Select chargepump current,
 *
 * \details 
 * 0: 50uA
 * 1: 100uA
 * 2: 150uA
 * 3: 200uA
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_LPF_CUR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Select loop filter resistor value,
 *
 * \details 
 * 0: not allowed
 * 1: 2400
 * 2: 1600
 * 3: 960
 * 4: 1200
 * 5: 800
 * 6: 685
 * 7: 533
 * 8: 800
 * 9: 600
 * 10: 533
 * 11: 436
 * 12: 480
 * 13: 400
 * 14: 369
 * 15: 320
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_LPF_RES
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Select vco current,
 *
 * \details 
 * 0: lowest current
 * 31: highest current
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_VCO_CUR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Not used
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_CAL_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable analog RCPLL part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2 . PLL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX RCPLL Status register 0
 *
 * \details
 * Status register 0 for SD10G65 RX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_STAT0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0(target)  VTSS_IOREG(target,0x33)

/** 
 * \brief
 * PLL lock status,
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLLF_LOCK_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Out of range status bit, sticky bit,
 *
 * \details 
 * 0: within range
 * 1: out of range
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLL_RANGE_LIMIT_STY
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Out of range status bit,
 *
 * \details 
 * 0: within range
 * 1: out of range
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLL_RANGE_LIMIT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLL_RANGE_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Actual value of VCO load, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLLF_VCO_LOAD_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Actual value of VCO fast portion, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLLF_VCO_FAST_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_FAST_STAT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_FAST_STAT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_FAST_STAT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Actual value of VCO slow portion, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0 . PLLF_VCO_SLOW_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SD10G65 RX RCPLL Status register 1
 *
 * \details
 * Status register 1 for SD10G65 RX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_RX_RCPLL:SD10G65_RX_RCPLL_STAT1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * Internal FSM values selected by pllf_ref_cnt_sel
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1 . PLLF_REF_CNT_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_REF_CNT_STAT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_REF_CNT_STAT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_REF_CNT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Actual value of step up counter
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1 . PLLF_FSM_CNT_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_CNT_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,11)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_CNT_STAT     VTSS_ENCODE_BITMASK(4,11)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_CNT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,11)

/** 
 * \brief
 * Actual value of the FSM stage,
 *
 * \details 
 * 0: reset state
 * 1: init state after reset
 * 3: ramp up state checks for the counters and ramps up the frequency
 * 6: additional wait state for internal BIAS settling
 * 8: additional wait state 1
 * 9: additional wait state 2
 * 10; additional wait state 3
 * 11: additional wait state 4
 * 12: 1st locking state enables dynamic locking
 * 13: final locking state checks for out of lock and overrun condition
 * 14: error state low frequency
 * 15: error state high frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1 . PLLF_FSM_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SD10G65:SD10G65_RX_SYNTH
 *
 * SD10G65 RX SYNTH Configuration and Status Register set
 */


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0(target)  VTSS_IOREG(target,0x40)

/** 
 * \brief
 * reg. pool for late changes/fixes. Used bits: Bit3-1: Synthesizer BIAS
 * adjust in steps of ~3%.
 *
 * \details 
 * 0: 100%
 * 7: 121%
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,22,8)

/** 
 * \brief
 * Enable for different offset compensation stages
 *
 * \details 
 * bit 0: Feedback buffer
 * bit 1: Synthesizer main rotator
 * bit 2: CDR rotator
 * bit 3: VCO buffer
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_OFF_COMP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA     VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,4)

/** 
 * \brief
 * selects feedback divider setting.
 *
 * \details 
 * 0: divide by 1
 * 1: divide by 2
 * 2: divide by 4
 * 3: reserved
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_FBDIV_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * selects step width for sync output
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_FB_STEP
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_STEP(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * inverts direction of sync out part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_FB_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_DIR  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_FB_DIR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * selects step width for integrator2
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I2_STEP
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_STEP(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * inverts direction of integral2 part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I2_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_DIR  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_DIR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * enable contribution of integral2 part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I2_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_ENA  VTSS_BIT(9)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I2_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * selects step width for integrator1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I1_STEP
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_STEP(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_STEP  VTSS_BIT(8)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_STEP(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * inverts direction of integral1 part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_I1_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_DIR  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_I1_DIR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * selects step width for propotional
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_P_STEP
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_STEP(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_STEP  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_STEP(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * inverts direction of propotional part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_P_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_DIR  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_P_DIR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selects circuit speed.
 *
 * \details 
 * 0: for settings with synth_fbdiv_sel = 2
 * 1: for setting with synth_fbdiv_sel less than 2
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_SPEED_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPEED_SEL  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * enables half rate mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_HRATE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_HRATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_HRATE_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_HRATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * enables CML2CMOS converter (low speed part of synthesizer)
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_CONV_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * synthesizer enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0 . SYNTH_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1(target)  VTSS_IOREG(target,0x41)

/** 
 * \brief
 * frequency multiplier decoder bypass
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT_BYP
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * frequency multiplier MSBits in bypass mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT_HI
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_EXTRACT_BITFIELD(x,22,4)

/** 
 * \brief
 * frequency multiplier
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/** 
 * \brief
 * frequency m setting bits 35:32
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQM_1
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * frequency n setting bits 35:32
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQN_1
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2(target)  VTSS_IOREG(target,0x42)

/** 
 * \brief
 * Rising edge triggers bit skip forward in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_FWD
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_FWD(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_FWD  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_FWD(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Rising edge triggers bit skip reverse in serial data stream. Used to
 * align data to parallel interface boundaries.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_SKIP_BIT_REV
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_REV(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_REV  VTSS_BIT(30)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_SKIP_BIT_REV(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Enable ET-Serdes test mode. In this test mode the data_valid input port
 * of SD10G65_RX switches between lock2data mode (data_valid = 0) and
 * lock2ref mode (data_valid = 1). Do not use in mission mode.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_ETSD_MODE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_ETSD_MODE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),28,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_ETSD_MODE_ENA  VTSS_BIT(28)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_ETSD_MODE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,28,1)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I2 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I2E
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_ENCODE_BITFIELD(x,26,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E     VTSS_ENCODE_BITMASK(26,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I2E(x)  VTSS_EXTRACT_BITFIELD(x,26,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 max function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1M
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1M(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * Controls the data valid behavior for the CDRLF I1 enable function: b0 =
 * 0 => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_I1E
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_ENCODE_BITFIELD(x,22,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E     VTSS_ENCODE_BITMASK(22,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_I1E(x)  VTSS_EXTRACT_BITFIELD(x,22,2)

/** 
 * \brief
 * Controls the data valid behavior for the moebdiv select function: b0 = 0
 * => external signal controls, 1 => b1 controls
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_DV_CTRL_MD
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_ENCODE_BITFIELD(x,20,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD     VTSS_ENCODE_BITMASK(20,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_DV_CTRL_MD(x)  VTSS_EXTRACT_BITFIELD(x,20,2)

/** 
 * \brief
 * Cp/md dig select. Coding 0: select Bit 0/5 as cp/md (FX100 mode); 1: use
 * cp/md from core
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_SEL  VTSS_BIT(18)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_SEL(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * uses cp/md selected via synth_cpmd_dig_sel instead of cp/md from sample
 * stage
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_CPMD_DIG_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_ENA  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_CPMD_DIG_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * enables clock for VScope / APC auxillary data chanels
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_AUX_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_AUX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_AUX_ENA  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_AUX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * relationship phase center/edge
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_PHASE_DATA
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_ENCODE_BITFIELD(x,8,7)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA     VTSS_ENCODE_BITMASK(8,7)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_DATA(x)  VTSS_EXTRACT_BITFIELD(x,8,7)

/** 
 * \brief
 * relationship phase center/aux
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2 . SYNTH_PHASE_AUX
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG2_SYNTH_PHASE_AUX(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3(target)  VTSS_IOREG(target,0x43)

/** 
 * \brief
 * frequency m setting bits 31:0
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3 . SYNTH_FREQM_0
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0(x)  (x)


/** 
 * \brief SD10G65 RX Synthesizer Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CFG4
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4(target)  VTSS_IOREG(target,0x44)

/** 
 * \brief
 * frequency n setting bits 31:0
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4 . SYNTH_FREQN_0
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0(x)  (x)


/** 
 * \brief SD10G65 RX Synthesizer Register CDR loopfilter control
 *
 * \details
 * Register for CDR loopfilter control for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_CDRLF
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF(target)  VTSS_IOREG(target,0x45)

/** 
 * \brief
 * max value of integrator 1 during normal operation
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX1
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_ENCODE_BITFIELD(x,21,5)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1     VTSS_ENCODE_BITMASK(21,5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX1(x)  VTSS_EXTRACT_BITFIELD(x,21,5)

/** 
 * \brief
 * max value of integrator 1 during init phase
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_MAX0
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_ENCODE_BITFIELD(x,16,5)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0     VTSS_ENCODE_BITMASK(16,5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_MAX0(x)  VTSS_EXTRACT_BITFIELD(x,16,5)

/** 
 * \brief
 * limit of integrator 1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_LIM
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_ENCODE_BITFIELD(x,11,5)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM     VTSS_ENCODE_BITMASK(11,5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_LIM(x)  VTSS_EXTRACT_BITFIELD(x,11,5)

/** 
 * \brief
 * frequency select of integrator 1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG1_FSEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_ENCODE_BITFIELD(x,6,5)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL     VTSS_ENCODE_BITMASK(6,5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG1_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,6,5)

/** 
 * \brief
 * frequency select of integrator 2
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF . SYNTH_INTEG2_FSEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CDRLF_SYNTH_INTEG2_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief SD10G65 RX Synthesizer Register 0 for qualifier access
 *
 * \details
 * Register 0 for qualifier access for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_QUALIFIER0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0(target)  VTSS_IOREG(target,0x46)

/** 
 * \brief
 * Clear for sticky flag "synth_i1_sat_det"
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I1_SAT_DET_CLR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET_CLR  VTSS_BIT(25)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET_CLR(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Sticky flag to indicate saturating of Integrator1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I1_SAT_DET
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET  VTSS_BIT(24)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I1_SAT_DET(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Controls Integrator2 behavior: '0': wrapping; '1': saturating.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_INHIBIT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_INHIBIT(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_INHIBIT  VTSS_BIT(23)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_INHIBIT(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Clear for sticky flag "synth_I2_wrap_det"
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_DET_CLR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET_CLR  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET_CLR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Sticky flag to indicate a wrap/saturating of Integrator2
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_I2_WRAP_DET
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET  VTSS_BIT(21)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_I2_WRAP_DET(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/** 
 * \brief
 * Rising edge captures qualifier for readback
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_CAPTURE_QUAL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_CAPTURE_QUAL(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_CAPTURE_QUAL  VTSS_BIT(20)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_CAPTURE_QUAL(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/** 
 * \brief
 * MS Bits of captured integrator 2
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I2_MSB
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I2_MSB(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * Captured integrator 1 value
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0 . SYNTH_QUAL_I1
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER0_SYNTH_QUAL_I1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief SD10G65 RX Synthesizer Register 1 for qualifier access
 *
 * \details
 * Register 1 for qualifier access for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_QUALIFIER1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1(target)  VTSS_IOREG(target,0x47)

/** 
 * \brief
 * LS Bits of captured integrator 2
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1 . SYNTH_QUAL_I2_LSB
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1_SYNTH_QUAL_I2_LSB(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1_SYNTH_QUAL_I2_LSB     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_QUALIFIER1_SYNTH_QUAL_I2_LSB(x)  (x)


/** 
 * \brief SD10G65 RX Synthesizer Register for sync control data
 *
 * \details
 * Register 0 for sync control data for SD10G65 RX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:SD10G65_RX_SYNTH_SYNC_CTRL
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL(target)  VTSS_IOREG(target,0x48)

/** 
 * \brief
 * Sticky bit that indicates a sync control protocol error.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_PROTOCOL_ERR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR  VTSS_BIT(19)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/** 
 * \brief
 * Clear for synth_sc_protocol_err sticky bit. Rising edge causes the
 * clearing and a concurrent error event has higher priority.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_PROTOCOL_ERR_CLR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR_CLR  VTSS_BIT(18)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_PROTOCOL_ERR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/** 
 * \brief
 * Enables sync control test generator. Before enabling the test generator
 * the sync timer must be disabled (synth_sc_sync_timer_sel = 0) and the
 * integrator 2 has to be cleared (synth_dv_ctrl_i2e = 1).
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_TEST_ENABLE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_ENABLE  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Triggers sync control test generator. In INC resp. DEC mode both edges
 * act as trigger event. In WOBBLE mode a 1 enables wobbling. Disabling in
 * WOBBEL mode lets current wobble cycle finish before stopping. I.e. the
 * I2 values reaches its value prior wobbling again.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_TEST_TRIGGER
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_TRIGGER(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_TRIGGER  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_TRIGGER(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Selects sync control test generator mode: 0: INC, 1: DEC, 2: WOBBLE
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_TEST_MODE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_MODE(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_MODE     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_MODE(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \brief
 * Selects sync control test generator period. Test generator period, i.e.
 * number of INC resp. DEC steps, equal programmed value + 1.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_TEST_COUNT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_COUNT(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_COUNT     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_TEST_COUNT(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Selects the synchronization period for the I2 value via sync control
 * bus. Must be disabled (0) when sync control test generator is used.
 * Coding in 312.5MHz clock cycles: 0: disabled, 1: 2^6, 2: 2^7, .., 15:
 * 2^20.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL . SYNTH_SC_SYNC_TIMER_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_SYNC_CTRL_SYNTH_SC_SYNC_TIMER_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF Configuration / status register
 *
 * \details
 * Configuration / status register for the F2DF control logic.
 *
 * Register: \a SD10G65:SD10G65_RX_SYNTH:F2DF_CFG_STAT
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT(target)  VTSS_IOREG(target,0x49)

/** 
 * \brief
 * Sampling divider: sample every 2^f2df_sample_div parallel data word.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SAMPLE_DIV
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_ENCODE_BITFIELD(x,25,3)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV     VTSS_ENCODE_BITMASK(25,3)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SAMPLE_DIV(x)  VTSS_EXTRACT_BITFIELD(x,25,3)

/** 
 * \brief
 * Actual FSM state: '0': Iffy; '1': WrongSide; '2': PropperSide; '3':
 * Lock.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_FSM_STATE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_FSM_STATE(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_FSM_STATE     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_FSM_STATE(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * Sticky bit: indicate loosing propper side detection in lock state.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_STICKY
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_STICKY  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Select bit from input data used for side detection. Debug feature: '31'
 * select constant zero, '30' select constant one.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_BIT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL     VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_BIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,5)

/** 
 * \brief
 * Sample '1' => increment 8bit filter saturating counter by 2**n. Cnt >=
 * 0xC0 => PropperSide detected.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ONES_WEIGHT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ONES_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/** 
 * \brief
 * Sample '0' => decrement 8bit filter saturating counter by 2**n. Cnt <
 *
 * \details 
 * 0x40 => WrongSide detected.
 *
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_SIDE_DET_ZEROS_WEIGHT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_SIDE_DET_ZEROS_WEIGHT(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Sticky bit: indicate missing toggle of MD sampler in lock state.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_TOG_DET_STICKY
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_STICKY  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Determines the number of samples that have to show at least one toggle.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_TOG_DET_CNT
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_ENCODE_BITFIELD(x,4,6)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT     VTSS_ENCODE_BITMASK(4,6)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_TOG_DET_CNT(x)  VTSS_EXTRACT_BITFIELD(x,4,6)

/** 
 * \brief
 * Data valid value in "PropperSide" state. '0': data valid flaged only in
 * "Lock" state; '1' data valid also flaged in "PropperSide" state.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_DATA_VALID_PROPPER_SIDE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_DATA_VALID_PROPPER_SIDE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_DATA_VALID_PROPPER_SIDE  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_DATA_VALID_PROPPER_SIDE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Clear all sticky bits.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_STICKY_CLR
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_STICKY_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_STICKY_CLR  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_STICKY_CLR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * F2df enable. Enabling the f2df circuit automatically switches the input
 * of the CDR-loop to the f2df control block (overrules synth_cpmd_dig_sel
 * and synth_cpmd_dig_ena) and replaces the data valid signal from the core
 * logic by the data valid signal generated by the f2df control logic.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT . F2DF_ENABLE
 */
#define  VTSS_F_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_ENABLE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_ENABLE  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_ENABLE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD10G65:SD10G65_TX_SYNTH
 *
 * SD10G65 TX SYNTH Configuration and Status Register set
 */


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 TX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0(target)  VTSS_IOREG(target,0x50)

/** 
 * \brief
 * reg. pool for late changes/fixes.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_SPARE_POOL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL     VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_EXTRACT_BITFIELD(x,26,4)

/** 
 * \brief
 * Synthesizer BIAS adjust in steps of ~3%, 0: 100%, 7: 121%
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_BIAS_ADJUST
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_BIAS_ADJUST(x)  VTSS_ENCODE_BITFIELD(x,23,3)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_BIAS_ADJUST     VTSS_ENCODE_BITMASK(23,3)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_BIAS_ADJUST(x)  VTSS_EXTRACT_BITFIELD(x,23,3)

/** 
 * \brief
 * Enable for different offset compensation stages
 *
 * \details 
 * bit 0: Feedback buffer
 * bit 1: Synthesizer main rotator
 * bit 2: VCO buffer
 * bit 3: OB clk gen
 * bit 4: Select source for OB clk gen. Coding: 0: incl. OB; 1: excl. OB
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_OFF_COMP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA     VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,5)

/** 
 * \brief
 * selects feedback divider setting
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_FBDIV_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_FBDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/** 
 * \brief
 * comon sync speed
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_CS_SPEED
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * lane sync speed
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_LS_SPEED
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_SPEED(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_SPEED  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * lane sync direction
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_LS_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR  VTSS_BIT(9)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * lane sync enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_LS_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_ENA  VTSS_BIT(8)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * dig. sync speed
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_DS_SPEED
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_SPEED(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_SPEED  VTSS_BIT(7)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/** 
 * \brief
 * dig. sync direction
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_DS_DIR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * dig. sync enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_DS_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_ENA  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Selects circuit speed. Coding: 0 for settings with synth_fbdiv_sel = 2;
 * 1 for setting with synth_fbdiv_sel smaller than 2.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_SPEED_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPEED_SEL  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * half rate enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_HRATE_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_HRATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_HRATE_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_HRATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * enable sync unit
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_ENA_SYNC_UNIT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * enables CML2CMOS converter
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_CONV_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * synthesizer enable
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0 . SYNTH_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 TX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1(target)  VTSS_IOREG(target,0x51)

/** 
 * \brief
 * frequency multiplier decoder bypass
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQ_MULT_BYP
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/** 
 * \brief
 * frequency multiplier MSBits in bypass mode
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQ_MULT_HI
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_EXTRACT_BITFIELD(x,22,4)

/** 
 * \brief
 * frequency multiplier
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQ_MULT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_ENCODE_BITFIELD(x,8,14)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT     VTSS_ENCODE_BITMASK(8,14)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT(x)  VTSS_EXTRACT_BITFIELD(x,8,14)

/** 
 * \brief
 * frequency m setting bits 35:32
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQM_1
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQM_1(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/** 
 * \brief
 * frequency n setting bits 35:32
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQN_1
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQN_1(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 3
 *
 * \details
 * Configuration register 3 for SD10G65 TX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG3
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3(target)  VTSS_IOREG(target,0x52)

/** 
 * \brief
 * frequency m setting bits 31:0
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3 . SYNTH_FREQM_0
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0(x)  (x)


/** 
 * \brief SD10G65 TX Synthesizer Configuration register 4
 *
 * \details
 * Configuration register 4 for SD10G65 TX SYNTH.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_TX_SYNTH_CFG4
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4(target)  VTSS_IOREG(target,0x53)

/** 
 * \brief
 * frequency n setting bits 31:0
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4 . SYNTH_FREQN_0
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0(x)  (x)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0     0xffffffff
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0(x)  (x)


/** 
 * \brief SD10G65 SSC generator Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 SSC generator.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_SSC_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0(target)  VTSS_IOREG(target,0x54)

/** 
 * \brief
 * SSC modulation amplitude limiter
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_LIM
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM(x)  VTSS_ENCODE_BITFIELD(x,19,13)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM     VTSS_ENCODE_BITMASK(19,13)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_LIM(x)  VTSS_EXTRACT_BITFIELD(x,19,13)

/** 
 * \brief
 * SSC modulation period / amplitude.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_PERIOD
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,7,12)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD     VTSS_ENCODE_BITMASK(7,12)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,7,12)

/** 
 * \brief
 * SSC modulation frequency fine tuning control
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_MOD_FREQ
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ(x)  VTSS_ENCODE_BITFIELD(x,1,6)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ     VTSS_ENCODE_BITMASK(1,6)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_MOD_FREQ(x)  VTSS_EXTRACT_BITFIELD(x,1,6)

/** 
 * \brief
 * SSC generator enable.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0 . SSC_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG0_SSC_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 SSC generator Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 SSC generator.
 *
 * Register: \a SD10G65:SD10G65_TX_SYNTH:SD10G65_SSC_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1(target)  VTSS_IOREG(target,0x55)

/** 
 * \brief
 * Sticky bit that indicates a sync control protocol error.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_PROTOCOL_ERR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Clear for synth_sc_protocol_err sticky bit. Rising edge causes the
 * clearing and a concurrent error event has higher priority.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_PROTOCOL_ERR_CLR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),30,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR_CLR  VTSS_BIT(30)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_PROTOCOL_ERR_CLR(x)  VTSS_EXTRACT_BITFIELD(x,30,1)

/** 
 * \brief
 * Select between the internal and external MLD phase detector: 0:
 * internal; 1: external
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_SRC_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_SRC_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_SRC_SEL  VTSS_BIT(29)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_SRC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/** 
 * \brief
 * Control of the internal MLD phase detector: b0: enable; b1: enable hyst.
 * b2: enable window function; b3: select window size
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_CTRL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL(x)  VTSS_ENCODE_BITFIELD(x,25,4)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL     VTSS_ENCODE_BITMASK(25,4)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,25,4)

/** 
 * \brief
 * Select the MLD clock source for the internal MLD phase detector
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . MLD_SYNC_CLK_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(x,23,2)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL     VTSS_ENCODE_BITMASK(23,2)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_MLD_SYNC_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,23,2)

/** 
 * \brief
 * Controls integrator 2 replica behavior: '0': wrapping; '1': saturating.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_WRAP_INHIBIT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_WRAP_INHIBIT(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_WRAP_INHIBIT  VTSS_BIT(22)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_WRAP_INHIBIT(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * Frequency select of integrator 2 replica used for lane sync.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SYNC_CTRL_FSEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL(x)  VTSS_ENCODE_BITFIELD(x,16,6)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL     VTSS_ENCODE_BITMASK(16,6)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SYNC_CTRL_FSEL(x)  VTSS_EXTRACT_BITFIELD(x,16,6)

/** 
 * \brief
 * Enables Smooth generator
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SMOOTH_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SMOOTH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SMOOTH_ENA  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SMOOTH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * SSC sigma delta gain.
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_SD_GAIN
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SD_GAIN(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/** 
 * \brief
 * SSC modulation start position on synchronization trigger
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_SYNC_POS
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_SYNC_POS(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * SSC modulation period multiplier encoded 2**n: 0 => 1; 1 => 2; 2 => 4, 3
 * => 8 ...
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1 . SSC_MOD_MUL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G65_SD10G65_TX_SYNTH_SD10G65_SSC_CFG1_SSC_MOD_MUL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * Register Group: \a SD10G65:SD10G65_TX_RCPLL
 *
 * SD10G65 TX RCPLL Configuration and Status Register set
 */


/** 
 * \brief SD10G65 TX RCPLL Configuration register 0
 *
 * \details
 * Configuration register 0 for SD10G65 TX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0(target)  VTSS_IOREG(target,0x60)

/** 
 * \brief
 * Preload value of the ramp up counter, reduces ramp up time for higher
 * frequencies
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_START_CNT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,10)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT     VTSS_ENCODE_BITMASK(16,10)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_START_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,10)

/** 
 * \brief
 * Enable feedback clock usage instead of DES/SER par. clock,
 *
 * \details 
 * 0: disable
 * 1: enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_SYN_CLK_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Enable predivider for feedback clock to allow for faster clocks,
 *
 * \details 
 * 0: disable
 * 1: enable
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_FBDIV_PRE
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_FBDIV_PRE(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_FBDIV_PRE  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_FBDIV_PRE(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Select output on pllf_ref_cnt_stat,
 *
 * \details 
 * 0: ref_cnt
 * 1: pll_cnt_diff
 * 2: syn_cnt
 * 3: pll_cnt
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_REF_CNT_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_REF_CNT_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_REF_CNT_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_REF_CNT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * Enable PLL loop ctrl by pllf_loop_ena,
 *
 * \details 
 * 0: enable loop ctrl by FSM
 * 1: enable loop ctrl by pllf_loop_ena
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_LOOP_CTRL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * Enable closed loop, selected with pllf_loop_ctrl_ena=1
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_LOOP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * Sets the ramp characteristic of the FSM, higher values give faster ramp
 * up but less accuracy,
 *
 * \details 
 * 0: normal (default) ramping
 * 1: faster ramping
 * 2: fastest ramping
 * 3: slow ramping
 * uses all possible values of r_ctrl
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_RAMP_MODE_SEL
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RAMP_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/** 
 * \brief
 * Enable VCO control signal out of range recalibration
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_OOR_RECAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable restart of FSM from frequency deviation/unlock condition
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_RST_FRQDET_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA  VTSS_BIT(5)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_FRQDET_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable restart of FSM from overrun
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_RST_OVERRUN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA  VTSS_BIT(4)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_RST_OVERRUN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_load,
 *
 * \details 
 * 0: enable vco load by FSM
 * 1: enable vco load by pllf_vco_load
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_VCO_LOAD_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA  VTSS_BIT(3)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_LOAD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_fast,
 *
 * \details 
 * 0: enable vco fast by FSM
 * 1: enable vco load by pllf_vco_fast
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_VCO_FAST_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_FAST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_FAST_ENA  VTSS_BIT(2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_FAST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable vco load by pllf_vco_slow,
 *
 * \details 
 * 0: enable vco slow by FSM
 * 1: enable vco load by pllf_vco_slow
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_VCO_SLOW_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_VCO_SLOW_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable RCPLL FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0 . PLLF_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 TX RCPLL Configuration register 1
 *
 * \details
 * Configuration register 1 for SD10G65 TX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1(target)  VTSS_IOREG(target,0x61)

/** 
 * \brief
 * Target value: 1/vco_frq * par.bit.width * 512 * ref_clk_frq
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_REF_CNT_END
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_REF_CNT_END(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * enable special BIST settings
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_BIST_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_BIST_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_BIST_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_BIST_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Select vco static frequency by load,
 *
 * \details 
 * 0: VCO off

 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_VCO_LOAD
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_LOAD(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_LOAD     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_LOAD(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Select vco static frequency by feedforward (higher freq.),
 *
 * \details 
 * 0: min. freq
 * 3: max. freq.
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_VCO_FAST
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_FAST(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_FAST     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_FAST(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Select vco static frequency by feedback (lower freq.),
 *
 * \details 
 * 0: max. freq
 * 3: min. freq.
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1 . PLLF_VCO_SLOW
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_SLOW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_SLOW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG1_PLLF_VCO_SLOW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SD10G65 TX RCPLL Configuration register 2
 *
 * \details
 * Configuration register 2 for SD10G65 TX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_CFG2
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2(target)  VTSS_IOREG(target,0x62)

/** 
 * \brief
 * Select VCO regulated supply (820mV),
 *
 * \details 
 * 0: 820mv
 * 4: 860mV
 * 6: 950mV
 * 7: short to VDDA
 * all others reserved
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_FBSEL820
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_FBSEL820(x)  VTSS_ENCODE_BITFIELD(x,24,3)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_FBSEL820     VTSS_ENCODE_BITMASK(24,3)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_FBSEL820(x)  VTSS_EXTRACT_BITFIELD(x,24,3)

/** 
 * \brief
 * Select VCO load switch gate voltage,
 *
 * \details 
 * 0: 1.4V
 * 1: 1.5V
 * 2: 1.6V
 * 3: 1.7V
 * 15: max.
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_VREG18
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * Debug, short P bulk voltage of OpAmps,
 *
 * \details 
 * 0: P bulk unequal supply
 * 1: short to supply
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_SHORT_BULKHP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Debug, short N bulk voltage of OpAmps,
 *
 * \details 
 * 0: N bulk unequal 0
 * 1: short to VSSA
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_SHORT_BULKHN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA  VTSS_BIT(15)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKHN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/** 
 * \brief
 * Debug, short P bulk voltage of VCO,
 *
 * \details 
 * 0: P bulk unequal supply
 * 1: short to supply
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_SHORT_BULKP_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA  VTSS_BIT(14)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/** 
 * \brief
 * Debug, short N bulk voltage of VCO,
 *
 * \details 
 * 0: N bulk unequal 0
 * 1: short to VSSA
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_SHORT_BULKN_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA  VTSS_BIT(13)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_SHORT_BULKN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/** 
 * \brief
 * Select chargepump current,
 *
 * \details 
 * 0: 50uA
 * 1: 100uA
 * 2: 150uA
 * 3: 200uA
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_LPF_CUR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_CUR(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/** 
 * \brief
 * Select loop filter resistor value,
 *
 * \details 
 * 0: not allowed
 * 1: 2400
 * 2: 1600
 * 3: 960
 * 4: 1200
 * 5: 800
 * 6: 685
 * 7: 533
 * 8: 800
 * 9: 600
 * 10: 533
 * 11: 436
 * 12: 480
 * 13: 400
 * 14: 369
 * 15: 320
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_LPF_RES
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_ENCODE_BITFIELD(x,7,4)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES     VTSS_ENCODE_BITMASK(7,4)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_LPF_RES(x)  VTSS_EXTRACT_BITFIELD(x,7,4)

/** 
 * \brief
 * Select vco current,
 *
 * \details 
 * 0: lowest current
 * 31: highest current
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_VCO_CUR
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/** 
 * \brief
 * Not used
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_CAL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_CAL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_CAL_ENA  VTSS_BIT(1)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_CAL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable analog RCPLL part
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_ENA
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_ENA  VTSS_BIT(0)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief SD10G65 TX RCPLL Status register 0
 *
 * \details
 * Status register 0 for SD10G65 TX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_STAT0
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0(target)  VTSS_IOREG(target,0x63)

/** 
 * \brief
 * PLL lock status,
 *
 * \details 
 * 0: not locked
 * 1: locked
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLLF_LOCK_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),31,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT  VTSS_BIT(31)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_LOCK_STAT(x)  VTSS_EXTRACT_BITFIELD(x,31,1)

/** 
 * \brief
 * Out of range status bit, sticky bit,
 *
 * \details 
 * 0: within range
 * 1: out of range
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLL_RANGE_LIMIT_STY
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY  VTSS_BIT(17)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT_STY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/** 
 * \brief
 * Out of range status bit,
 *
 * \details 
 * 0: within range
 * 1: out of range
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLL_RANGE_LIMIT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT  VTSS_BIT(16)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLL_RANGE_LIMIT(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * Actual value of VCO load, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLLF_VCO_LOAD_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,10)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT     VTSS_ENCODE_BITMASK(4,10)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_LOAD_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,10)

/** 
 * \brief
 * Actual value of VCO fast portion, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLLF_VCO_FAST_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_FAST_STAT(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_FAST_STAT     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_FAST_STAT(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Actual value of VCO slow portion, set by FSM
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0 . PLLF_VCO_SLOW_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT0_PLLF_VCO_SLOW_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief SD10G65 TX RCPLL Status register 1
 *
 * \details
 * Status register 1 for SD10G65 TX RCPLL.
 *
 * Register: \a SD10G65:SD10G65_TX_RCPLL:SD10G65_TX_RCPLL_STAT1
 *
 * @param target A \a ::vtss_target_SD10G65_e target
 */
#define VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1(target)  VTSS_IOREG(target,0x64)

/** 
 * \brief
 * Internal FSM values selected by pllf_ref_cnt_sel
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1 . PLLF_REF_CNT_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_REF_CNT_STAT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_REF_CNT_STAT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_REF_CNT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/** 
 * \brief
 * Actual value of step up counter
 *
 * \details 
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1 . PLLF_FSM_CNT_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_CNT_STAT(x)  VTSS_ENCODE_BITFIELD(x,4,11)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_CNT_STAT     VTSS_ENCODE_BITMASK(4,11)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_CNT_STAT(x)  VTSS_EXTRACT_BITFIELD(x,4,11)

/** 
 * \brief
 * Actual value of the FSM stage,
 *
 * \details 
 * 0: reset state
 * 1: init state after reset
 * 3: ramp up state checks for the counters and ramps up the frequency
 * 6: additional wait state for internal BIAS settling
 * 8: additional wait state 1
 * 9: additional wait state 2
 * 10; additional wait state 3
 * 11: additional wait state 4
 * 12: 1st locking state enables dynamic locking
 * 13: final locking state checks for out of lock and overrun condition
 * 14: error state low frequency
 * 15: error state high frequency
 *
 * Field: ::VTSS_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1 . PLLF_FSM_STAT
 */
#define  VTSS_F_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G65_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_SERVALT_REGS_SD10G65_H_ */
