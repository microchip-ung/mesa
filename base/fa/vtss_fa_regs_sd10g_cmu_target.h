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

#ifndef _VTSS_FA_REGS_SD10G_CMU_TARGET_H_
#define _VTSS_FA_REGS_SD10G_CMU_TARGET_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD10G_CMU_TARGET
 *
 * \see vtss_target_SD10G_CMU_TARGET_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_0
 *
 * Register group for register 0x00
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_0:CMU_00
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_00(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Simulation speed up mode enable.0: no speed up.1: speed up. Note loss of
 * lock related functions will not be speed up.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_00 . R_HWT_SIMULATION_MODE
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_00_R_HWT_SIMULATION_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_00_R_HWT_SIMULATION_MODE  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_00_R_HWT_SIMULATION_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_00 . CFG_PLL_LOL_SET
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOL_SET  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_00 . CFG_PLL_LOS_SET
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOS_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOS_SET  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_00_CFG_PLL_LOS_SET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_00 . CFG_PLL_TP_SEL_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_00_CFG_PLL_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_00_CFG_PLL_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_00_CFG_PLL_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_1
 *
 * Register group for registers 0x05 to 0x15
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_05
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_05(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * 1: enable reference clock buffer.0: power down reference clock buffer.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_05 . CFG_REFCK_TERM_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_05_CFG_REFCK_TERM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_05_CFG_REFCK_TERM_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_05_CFG_REFCK_TERM_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_05 . CFG_BIAS_TP_SEL_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_05_CFG_BIAS_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_05_CFG_BIAS_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_05_CFG_BIAS_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_06
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_06(target)  VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_DISLOS
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_DISLOS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_DISLOS  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_DISLOS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_DISLOL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_DISLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_DISLOL  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_DISLOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_DCLOL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_DCLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_DCLOL  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_DCLOL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_FORCE_RX_FILT
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_FORCE_RX_FILT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_FORCE_RX_FILT  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_FORCE_RX_FILT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_CTRL_LOGIC_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_CTRL_LOGIC_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_CTRL_LOGIC_PD  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_CTRL_LOGIC_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_VCO_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_VCO_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_VCO_PD  VTSS_BIT(5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_VCO_PD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_VCO_CAL_RESETN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_RESETN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_RESETN  VTSS_BIT(6)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_RESETN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_06 . CFG_VCO_CAL_BYP
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_BYP  VTSS_BIT(7)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_06_CFG_VCO_CAL_BYP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_07
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_07(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_07 . CFG_VCO_BYP_CTUNE_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_07_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_07_CFG_VCO_BYP_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_07_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_07 . CFG_VCO_START_CODE_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_07_CFG_VCO_START_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_07_CFG_VCO_START_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_07_CFG_VCO_START_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_08
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_08(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_08 . CFG_VFILT2PAD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_VFILT2PAD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_VFILT2PAD  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_08_CFG_VFILT2PAD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_08 . CFG_EN_DUMMY
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_EN_DUMMY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_EN_DUMMY  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_08_CFG_EN_DUMMY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_08 . CFG_CK_TREE_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_CK_TREE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_CK_TREE_PD  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_08_CFG_CK_TREE_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_08 . CFG_RST_TREE_PD_MAN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_08 . CFG_RST_TREE_PD_MAN_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_08_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_09
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_09(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * 1: enable PLL clock output buffers to the right hand side of common
 * block. PLL clock will output to the right at upper set of clock routing
 * in TX/RX lane.0: disable PLL clock output buffers to the right.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_09 . CFG_EN_TX_CK_UP
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1: enable PLL clock output buffers to the left hand side of common
 * block. PLL clock will output to the left at lower set of clock routing
 * in TX/RX lane.0: disable PLL clock output buffers to the left.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_09 . CFG_EN_TX_CK_DN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal..
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_09 . CFG_SW_8G
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_SW_8G(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_SW_8G  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_09_CFG_SW_8G(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal..
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_09 . CFG_SW_10G
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_SW_10G(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_SW_10G  VTSS_BIT(5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_09_CFG_SW_10G(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0A
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0A(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * VCO sub-rate divided ratio.000: /1001: /2010: /41: enable PLL clock
 * output buffers to the right hand side of common block. PLL clock will
 * output to the right at upper set of clock routing in TX/RX lane.0:
 * disable PLL clock output buffers to the right.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0A . CFG_VCO_DIV_MODE_2_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0A_CFG_VCO_DIV_MODE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0A_CFG_VCO_DIV_MODE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0A_CFG_VCO_DIV_MODE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0B
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0B(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * VCO bias current setting.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0B . CFG_I_VCO_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0B_CFG_I_VCO_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0B_CFG_I_VCO_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0B_CFG_I_VCO_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Charge pump base current coarse-tune.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0B . CFG_ICP_BASE_SEL_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0B_CFG_ICP_BASE_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0B_CFG_ICP_BASE_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0B_CFG_ICP_BASE_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0C
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0C(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Charge pump current fine-tune.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0C . CFG_ICP_SEL_2_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0C_CFG_ICP_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0C_CFG_ICP_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0C_CFG_ICP_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0C . CFG_RSEL_2_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0C_CFG_RSEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0C_CFG_RSEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0C_CFG_RSEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0D
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0D(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0D . CFG_PD_DIV64
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV64(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV64  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV64(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0D . CFG_PD_DIV66
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV66(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV66  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV66(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0D . CFG_PMA_TX_CK_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_PMA_TX_CK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_PMA_TX_CK_PD  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0D_CFG_PMA_TX_CK_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0D . CFG_JC_BYP
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_JC_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_JC_BYP  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0D_CFG_JC_BYP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0D . CFG_REFCK_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_REFCK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_REFCK_PD  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0D_CFG_REFCK_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0E
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0E(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0E . CFG_IPLL_DN_RESETB_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0E . CFG_IPLL_DN_TREE_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_0F
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_0F(target)  VTSS_IOREG(target,0xf)

/** 
 * \brief
 * Fine tune bias current for refclk ssc PI.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0F . CFG_IPLL_UP_RESETB_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Fine tune the swing of ssc refclk swing.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_0F . CFG_IPLL_UP_TREE_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_10
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_10(target)  VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Fine tune the swing of pll distributed clock.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_10 . CFG_IPLL_RESETB_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_10 . CFG_IPLL_TREE_BASE
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_TREE_BASE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_TREE_BASE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_10_CFG_IPLL_TREE_BASE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_11
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_11(target)  VTSS_IOREG(target,0x11)

/** 
 * \brief
 * Fine tune swing of PLL clock buffer.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_11 . CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_12
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_12(target)  VTSS_IOREG(target,0x12)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_12 . CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_12 . CFG_ITX_VC_BUF_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_BUF_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_BUF_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_12_CFG_ITX_VC_BUF_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_13
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_13(target)  VTSS_IOREG(target,0x13)

/** 
 * \brief
 * reference current/voltage fine-tune control. +/- 2.5% increase/decrease
 * code per step.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_13 . CFG_IBIAS_VC_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_13_CFG_IBIAS_VC_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_13_CFG_IBIAS_VC_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_13_CFG_IBIAS_VC_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_14
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_14(target)  VTSS_IOREG(target,0x14)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_14 . CFG_IBIAS_PD
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_PD  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_14 . CFG_IBIAS_EN_EXTVBG
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_EN_EXTVBG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_EN_EXTVBG  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_14_CFG_IBIAS_EN_EXTVBG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_1:CMU_15
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_15(target)  VTSS_IOREG(target,0x15)

/** 
 * \brief
 * PLL multiplying factor(Fref*N):00000: 64.00001: 66.00010: 80.00011:
 * 100.00100: 120.01011: 400.01100: 480.10100: 240.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_15 . CFG_SEL_DIV_4_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_15_CFG_SEL_DIV_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_15_CFG_SEL_DIV_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_15_CFG_SEL_DIV_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_2
 *
 * Register group for register 0x17
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_2:CMU_17
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_17(target)  VTSS_IOREG(target,0x17)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_17 . CFG_VC_REFP_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFP_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFP_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFP_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_17 . CFG_VC_REFN_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFN_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFN_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_17_CFG_VC_REFN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_3
 *
 * Register group for registers 0x1A to 0x1C
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_3:CMU_1A
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_1A(target)  VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * REFCLKP/REFCLKN termination resistor enable.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1A . CFG_REFCK_R_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1A_CFG_REFCK_R_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1A_CFG_REFCK_R_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1A_CFG_REFCK_R_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_3:CMU_1B
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_1B(target)  VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1B . CFG_RESERVE_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1B_CFG_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1B_CFG_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1B_CFG_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_3:CMU_1C
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_1C(target)  VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1C . CFG_RESERVE_15_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1C_CFG_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1C_CFG_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1C_CFG_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_4
 *
 * Register group for registers 0x1F to 0x26
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_1F
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_1F(target)  VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * Enable BG bias current source (20 lines) from common block to the left
 * hand side of TX/RX lane. Enable the desired current source from one
 * common block only. If more than 1 common block are used and both enabled
 * for this bit, bias current will be almost twice to the TX/RX lane which
 * will cause function improperly.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1F . CFG_BIAS_DN_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_DN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_DN_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_DN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable BG bias current source (20 lines) from common block to the right
 * hand side of TX/RX lane. Enable the desired current source from one
 * common block only. If more than 1 common block are used and both enabled
 * for this bit, bias current will be almost twice to the TX/RX lane which
 * will cause function improperly.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1F . CFG_BIAS_UP_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_UP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_UP_EN  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1F_CFG_BIAS_UP_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 0: All bias are reference to internal BG resistor.1: Some bias currents
 * are reference to external 10K BG resistor.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1F . CFG_IC2IP_N
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_IC2IP_N(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_IC2IP_N  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1F_CFG_IC2IP_N(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_1F . CFG_VTUNE_SEL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_1F_CFG_VTUNE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_1F_CFG_VTUNE_SEL  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_1F_CFG_VTUNE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_20
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_20(target)  VTSS_IOREG(target,0x20)

/** 
 * \brief
 * For TX lane to lane skew requirement, if more than 5 lanes in one side
 * of CMU to share the same TX clock transmission line, then insert common
 * block in between and activate TX clock buffer/repeater inside this
 * common block with this bit set to '1'. Refer to
 * 'IGPSERT15A_configuration_application_note.docx'
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_20 . CFG_LINK_BUF_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_20_CFG_LINK_BUF_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_20_CFG_LINK_BUF_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_20_CFG_LINK_BUF_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_21
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_21(target)  VTSS_IOREG(target,0x21)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_21 . CFG_REFCK_BCNTMAXVAL_4_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_22
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_22(target)  VTSS_IOREG(target,0x22)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_22 . CFG_REFCK_SSC_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_22 . CFG_REFCK_CENTER_SPREADING
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_CENTER_SPREADING(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_CENTER_SPREADING  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_CENTER_SPREADING(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_22 . CFG_REFCK_SSC_RTL_CLK_SEL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_22 . CFG_REFCK_SSC_RESETB
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RESETB  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_22_CFG_REFCK_SSC_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_23
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_23(target)  VTSS_IOREG(target,0x23)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_23 . CFG_REFCK_MCNTMAXVAL_4_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_24
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_24(target)  VTSS_IOREG(target,0x24)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_24 . CFG_REFCK_NCNTMAXVAL_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_25
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_25(target)  VTSS_IOREG(target,0x25)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_25 . CFG_REFCK_NCNTMAXVAL_10_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_4:CMU_26
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_26(target)  VTSS_IOREG(target,0x26)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_26 . CFG_REFCK_SSC_PI_BW_2_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_BW_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_BW_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_BW_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_26 . CFG_REFCK_SSC_PI_STEP_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_5
 *
 * Register group for registers 0x30 to 0x38
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_30
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_30(target)  VTSS_IOREG(target,0x30)

/** 
 * \brief
 * PLL lol (loss of lock) status output enable
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_30 . R_PLL_DLOL_EN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_30_R_PLL_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_30_R_PLL_DLOL_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_30_R_PLL_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_31
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_31(target)  VTSS_IOREG(target,0x31)

/** 
 * \brief
 * PLL loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_31 . R_PLL_LOL_DEASSERT_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_31_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_31_R_PLL_LOL_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_31_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_32
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_32(target)  VTSS_IOREG(target,0x32)

/** 
 * \brief
 * PLL loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_32 . R_PLL_LOL_DEASSERT_15_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_32_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_32_R_PLL_LOL_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_32_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_33
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_33(target)  VTSS_IOREG(target,0x33)

/** 
 * \brief
 * PLL loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_33 . R_PLL_LOL_ASSERT_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_33_R_PLL_LOL_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_33_R_PLL_LOL_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_33_R_PLL_LOL_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_34
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_34(target)  VTSS_IOREG(target,0x34)

/** 
 * \brief
 * PLL loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_34 . R_PLL_LOL_ASSERT_15_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_34_R_PLL_LOL_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_34_R_PLL_LOL_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_34_R_PLL_LOL_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_35
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_35(target)  VTSS_IOREG(target,0x35)

/** 
 * \brief
 * PLL loss of lock deassert dppm control.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_35 . R_PLL_LOL_DF1_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_35_R_PLL_LOL_DF1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_35_R_PLL_LOL_DF1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_35_R_PLL_LOL_DF1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_36
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_36(target)  VTSS_IOREG(target,0x36)

/** 
 * \brief
 * PLL loss of lock deassert dppm control.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_36 . R_PLL_LOL_DF1_9_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_36_R_PLL_LOL_DF1_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_36_R_PLL_LOL_DF1_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_36_R_PLL_LOL_DF1_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_37
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_37(target)  VTSS_IOREG(target,0x37)

/** 
 * \brief
 * PLL loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_37 . R_PLL_LOL_DF2_7_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_37_R_PLL_LOL_DF2_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_37_R_PLL_LOL_DF2_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_37_R_PLL_LOL_DF2_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_5:CMU_38
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_38(target)  VTSS_IOREG(target,0x38)

/** 
 * \brief
 * PLL loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_38 . R_PLL_LOL_DF2_9_8
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_38_R_PLL_LOL_DF2_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_38_R_PLL_LOL_DF2_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_38_R_PLL_LOL_DF2_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_6
 *
 * Register group for registers 0x42 to 0x47
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_42
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_42(target)  VTSS_IOREG(target,0x42)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_42 . R_LOL_RESET
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_42_R_LOL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_42_R_LOL_RESET  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_42_R_LOL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_43
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_43(target)  VTSS_IOREG(target,0x43)

/** 
 * \brief
 * T1 in Figure 3.2-1 (reset scheme).00: 30t01: 10000t10: 20000t11: 30000t
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_43 . R_TIME_PLL2CDR_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_43_R_TIME_PLL2CDR_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_43_R_TIME_PLL2CDR_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_43_R_TIME_PLL2CDR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_44
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_44(target)  VTSS_IOREG(target,0x44)

/** 
 * \brief
 * Reset signal for pll, low active.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_44 . R_PLL_RSTN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_44_R_PLL_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_44 . R_CK_RESETB
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_44_R_CK_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_44_R_CK_RESETB  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_44_R_CK_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_45
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_45(target)  VTSS_IOREG(target,0x45)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_EN_RATECHG_CTRL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_EN_RATECHG_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_EN_RATECHG_CTRL  VTSS_BIT(0)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_EN_RATECHG_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Data width/data rate/termination resistor of reference clock control
 * from register or hardware pin.0: cfg control 1:
 * pcs2pma_phymode[[4:0],hwt_cfg_sel_div[4:0]hwt_vco_sel_div[2:0]hwt_refck_
 * r_en
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_DWIDTHCTRL_FROM_HWT
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_DWIDTHCTRL_FROM_HWT  VTSS_BIT(1)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . RESERVED
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_RESERVED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_RESERVED  VTSS_BIT(2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The source of hwt_refck_* control signals  selection0 : configuration
 * register1 : configuration from pins:hwt_refck_ssc_en,  
 * hwt_refck_ssc_resetb   hwt_refck_center_spreading  
 * hwt_refck_mcntMaxVal[4:0]   hwt_refck_ncntMaxVal[10:0]  
 * hwt_refck_ssc_pi_bw[2:0]   hwt_refck_ssc_pi_step[1:0]  
 * hwt_refck_ssc_rtl_clk_sel
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_REFCK_SSC_EN_FROM_HWT
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_REFCK_SSC_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_REFCK_SSC_EN_FROM_HWT  VTSS_BIT(3)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_REFCK_SSC_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . RESERVED_2
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_RESERVED_2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_RESERVED_2  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_RESERVED_2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The source of link_buf_en selection0 : configuration register1 :
 * hwt_link_buf_en
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_LINK_BUF_EN_FROM_HWT
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_LINK_BUF_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_LINK_BUF_EN_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_LINK_BUF_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * The source of cfg_bias_dn_en/ cfg_bias_dn_en selection0 : configuration
 * register1 : hwt_bias_dn_en / hwt_bias_up_en
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_BIAS_EN_FROM_HWT
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_BIAS_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_BIAS_EN_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_BIAS_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Reset tree buffer power down control selection.0 : Configuration
 * registers1 : internal circuit.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_45 . R_AUTO_RST_TREE_PD_MAN
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_45_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_45_R_AUTO_RST_TREE_PD_MAN  VTSS_BIT(7)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_45_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_46
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_46(target)  VTSS_IOREG(target,0x46)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_46 . R_DBG_SEL_1_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_46_R_DBG_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_46_R_DBG_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_46_R_DBG_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_6:CMU_47
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_47(target)  VTSS_IOREG(target,0x47)

/** 
 * \brief
 * 5'b00_000
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_47 . R_PCS2PMA_PHYMODE_4_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_47_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_47_R_PCS2PMA_PHYMODE_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_47_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)

/**
 * Register Group: \a SD10G_CMU_TARGET:CMU_GRP_7
 *
 * Register group for registers 0xE0 to 0xE1
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_7:CMU_E0
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_E0(target)  VTSS_IOREG(target,0xe0)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_E0 . READ_VCO_CTUNE_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_E0_READ_VCO_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_E0_READ_VCO_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_E0_READ_VCO_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Loss of lock of PLL
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_E0 . PLL_LOL_UDL
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_E0_PLL_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_E0_PLL_LOL_UDL  VTSS_BIT(4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_E0_PLL_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_CMU_TARGET:CMU_GRP_7:CMU_E1
 *
 * @param target A \a ::vtss_target_SD10G_CMU_TARGET_e target
 */
#define VTSS_SD10G_CMU_TARGET_CMU_E1(target)  VTSS_IOREG(target,0xe1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SD10G_CMU_TARGET_CMU_E1 . CFG_COMMON_STATUS_RESERVE_3_0
 */
#define  VTSS_F_SD10G_CMU_TARGET_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_CMU_TARGET_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_CMU_TARGET_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_FA_REGS_SD10G_CMU_TARGET_H_ */
