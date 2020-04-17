// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_SD25G_TARGET_H_
#define _VTSS_FA_REGS_SD25G_TARGET_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD25G_TARGET
 *
 * \see vtss_target_SD25G_TARGET_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a SD25G_TARGET:CMU_GRP_0
 *
 * Register group for registers 0x00 to 0x1F
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_00
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_00(target)     VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_00 . CFG_TX_RSTB_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_01
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_01(target)     VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_01 . CFG_TX_RSTB_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_02
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_02(target)     VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_02 . CFG_TX_SETB_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_02_CFG_TX_SETB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_02_CFG_TX_SETB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_02_CFG_TX_SETB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_03
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_03(target)     VTSS_IOREG(target,0x3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_03 . CFG_TX_SETB_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_03_CFG_TX_SETB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_03_CFG_TX_SETB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_03_CFG_TX_SETB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_04
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_04(target)     VTSS_IOREG(target,0x4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_04 . CFG_IC2IP_N
 */
#define  VTSS_F_SD25G_TARGET_CMU_04_CFG_IC2IP_N(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_04_CFG_IC2IP_N  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_04_CFG_IC2IP_N(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_04 . CFG_BIAS_TP_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_04_CFG_BIAS_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_04_CFG_BIAS_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_04_CFG_BIAS_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_05
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_05(target)     VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Reference current/voltage fine-tuning control ~+/-2.5% increase/decrease
 * per code change
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_05 . CFG_IBIAS_VC_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_05_CFG_IBIAS_VC_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_05_CFG_IBIAS_VC_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_05_CFG_IBIAS_VC_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_05 . CFG_IBIAS_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_05_CFG_IBIAS_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_05_CFG_IBIAS_PD  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_05_CFG_IBIAS_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_05 . CFG_IBIAS_EN_EXTVBG
 */
#define  VTSS_F_SD25G_TARGET_CMU_05_CFG_IBIAS_EN_EXTVBG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_05_CFG_IBIAS_EN_EXTVBG  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_05_CFG_IBIAS_EN_EXTVBG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_06
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_06(target)     VTSS_IOREG(target,0x6)

/** 
 * \brief
 * Clock distribution buffer fine-tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_06 . CFG_IPLL_UP_TREE_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_06 . CFG_IPLL_UP_RESETB_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_07
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_07(target)     VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_07 . CFG_IPLL_RESETB_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_07_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_07_CFG_IPLL_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_07_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * High speed CML & divider fine-tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_07 . CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_08
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_08(target)     VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_08 . CFG_IPLL_DN_RESETB_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_09
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_09(target)     VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Ref clock receiver enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_09 . CFG_REFCK_TERM_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_09_CFG_REFCK_TERM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_09_CFG_REFCK_TERM_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_09_CFG_REFCK_TERM_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_09 . CFG_EN_DUMMY
 */
#define  VTSS_F_SD25G_TARGET_CMU_09_CFG_EN_DUMMY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_09_CFG_EN_DUMMY  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_09_CFG_EN_DUMMY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_09 . CFG_PLL_LOS_SET
 */
#define  VTSS_F_SD25G_TARGET_CMU_09_CFG_PLL_LOS_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_09_CFG_PLL_LOS_SET  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_09_CFG_PLL_LOS_SET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_09 . CFG_CTRL_LOGIC_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_09_CFG_CTRL_LOGIC_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_CMU_09_CFG_CTRL_LOGIC_PD  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_CMU_09_CFG_CTRL_LOGIC_PD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_09 . CFG_PLL_TP_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_09_CFG_PLL_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_09_CFG_PLL_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_09_CFG_PLL_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0A(target)     VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0A . CFG_VCO_BYP_CTUNE_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0A_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_0A_CFG_VCO_BYP_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_0A_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0A . CFG_VCO_START_CODE_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0A_CFG_VCO_START_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_CMU_0A_CFG_VCO_START_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_CMU_0A_CFG_VCO_START_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0B(target)     VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_FORCE_RX_FILT
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_FORCE_RX_FILT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_FORCE_RX_FILT  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_FORCE_RX_FILT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_DISLOL
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_DISLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_DISLOL  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_DISLOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_RST_TREE_PD_MAN_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN_EN  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * VCO calibration reset
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_VCO_CAL_RESETN
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_VCO_CAL_RESETN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_VFILT2PAD
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_VFILT2PAD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_VFILT2PAD  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_VFILT2PAD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_DISLOS
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_DISLOS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_DISLOS  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_DISLOS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_DCLOL
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_DCLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_DCLOL  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_DCLOL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0B . CFG_RST_TREE_PD_MAN
 */
#define  VTSS_F_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_CMU_0B_CFG_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0C(target)     VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0C . CFG_PLL_LOL_SET
 */
#define  VTSS_F_SD25G_TARGET_CMU_0C_CFG_PLL_LOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_0C_CFG_PLL_LOL_SET  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_0C_CFG_PLL_LOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable clock distribution for TX Lane 2 + Lane 3
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0C . CFG_EN_TX_CK_DN
 */
#define  VTSS_F_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_DN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_DN  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_DN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Power down VCO
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0C . CFG_VCO_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_0C_CFG_VCO_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_0C_CFG_VCO_PD  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_0C_CFG_VCO_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Enable clock distribution for TX Lane 0 + Lane 1
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0C . CFG_EN_TX_CK_UP
 */
#define  VTSS_F_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_UP  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_CMU_0C_CFG_EN_TX_CK_UP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * VCO divider setting,00, divide by 0 01, divide by 2
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0C . CFG_VCO_DIV_MODE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0C_CFG_VCO_DIV_MODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_0C_CFG_VCO_DIV_MODE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_0C_CFG_VCO_DIV_MODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0D(target)     VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0D . CFG_CK_TREE_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_0D_CFG_CK_TREE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_0D_CFG_CK_TREE_PD  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_0D_CFG_CK_TREE_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable clock distribution for RX Lane 2 + Lane 3
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0D . CFG_EN_RX_CK_DN
 */
#define  VTSS_F_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_DN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_DN  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_DN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable clock distribution for RX Lane 0 + Lane 1
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0D . CFG_EN_RX_CK_UP
 */
#define  VTSS_F_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_UP  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_0D_CFG_EN_RX_CK_UP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Bypass VCO calibration,Debug mode only
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0D . CFG_VCO_CAL_BYP
 */
#define  VTSS_F_SD25G_TARGET_CMU_0D_CFG_VCO_CAL_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_CMU_0D_CFG_VCO_CAL_BYP  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_CMU_0D_CFG_VCO_CAL_BYP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Reference clock divide 00  Divide-by-1 01  Divide-by-2 10  Divide-by-4
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0D . CFG_PRE_DIVSEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0D_CFG_PRE_DIVSEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_0D_CFG_PRE_DIVSEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_0D_CFG_PRE_DIVSEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0E(target)     VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Application notes for more details and restrictions.  Common
 * settings:0110: Divide by 160 1111: Divide by 330
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0E . CFG_SEL_DIV_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0E_CFG_SEL_DIV_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_0E_CFG_SEL_DIV_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_0E_CFG_SEL_DIV_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0E . CFG_PMAA_CENTR_CK_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_0E_CFG_PMAA_CENTR_CK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_0E_CFG_PMAA_CENTR_CK_PD  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_0E_CFG_PMAA_CENTR_CK_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_0F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_0F(target)     VTSS_IOREG(target,0xf)

/** 
 * \brief
 * PLL loop parameter tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0F . CFG_RSEL_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0F_CFG_RSEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_0F_CFG_RSEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_0F_CFG_RSEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * PLL loop parameter tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_0F . CFG_ICP_BASE_SEL_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_0F_CFG_ICP_BASE_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_CMU_0F_CFG_ICP_BASE_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_CMU_0F_CFG_ICP_BASE_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_10
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_10(target)     VTSS_IOREG(target,0x10)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_10 . CFG_PMAA_CENTR_BITWIDTH_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Power down buffers in ref clock path
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_10 . CFG_REFCK_PD
 */
#define  VTSS_F_SD25G_TARGET_CMU_10_CFG_REFCK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_10_CFG_REFCK_PD  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_10_CFG_REFCK_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_11
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_11(target)     VTSS_IOREG(target,0x11)

/** 
 * \brief
 * PLL loop parameter tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_11 . CFG_ICP_SEL_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_11_CFG_ICP_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_11_CFG_ICP_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_11_CFG_ICP_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_11 . CFG_PD_DIV66
 */
#define  VTSS_F_SD25G_TARGET_CMU_11_CFG_PD_DIV66(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_11_CFG_PD_DIV66  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_11_CFG_PD_DIV66(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_12
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_12(target)     VTSS_IOREG(target,0x12)

/** 
 * \brief
 * VCO current tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_12 . CFG_I_VCO_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_12_CFG_I_VCO_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_12_CFG_I_VCO_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_12_CFG_I_VCO_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_12 . CFG_PD_DIV64
 */
#define  VTSS_F_SD25G_TARGET_CMU_12_CFG_PD_DIV64(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_12_CFG_PD_DIV64  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_12_CFG_PD_DIV64(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Switches between On-chip ref clock or External Bump ref clock
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_12 . CFG_JC_BYP
 */
#define  VTSS_F_SD25G_TARGET_CMU_12_CFG_JC_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_12_CFG_JC_BYP  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_12_CFG_JC_BYP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_12 . CFG_VCO_CAL_DIR
 */
#define  VTSS_F_SD25G_TARGET_CMU_12_CFG_VCO_CAL_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_CMU_12_CFG_VCO_CAL_DIR  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_CMU_12_CFG_VCO_CAL_DIR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_13
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_13(target)     VTSS_IOREG(target,0x13)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_13 . CFG_PLL_RESERVE_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_13_CFG_PLL_RESERVE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_13 . CFG_JT_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_13_CFG_JT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_13_CFG_JT_EN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_13_CFG_JT_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_14
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_14(target)     VTSS_IOREG(target,0x14)

/** 
 * \brief
 * T2 in figure 17 (reset scheme) 00: 30t 01: 10000t 10: 20000t 11: 30000t
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_14 . R_TIME_PLL2CDR_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_14_R_TIME_PLL2CDR_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_14_R_TIME_PLL2CDR_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_14_R_TIME_PLL2CDR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * T4 in figure 17 (reset scheme) 00: 30t 01: 10000t 10: 20000t 11: 30000t
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_14 . R_TIME_TXCAL2TXRX_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_14_R_TIME_TXCAL2TXRX_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_14_R_TIME_TXCAL2TXRX_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_14_R_TIME_TXCAL2TXRX_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_15
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_15(target)     VTSS_IOREG(target,0x15)

/** 
 * \brief
 * T6 in figure 17 (reset scheme) 00: 30t 01: 1000t 10: 5000t 11: 10000t
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_15 . R_TIME_CTLE2DFE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_15_R_TIME_CTLE2DFE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_15_R_TIME_CTLE2DFE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_15_R_TIME_CTLE2DFE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_16
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_16(target)     VTSS_IOREG(target,0x16)

/** 
 * \brief
 * Simulation speed up mode enable. 0: no speed up 1: speed up. Note that
 * loss of lock related functions will not be speed up
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_16 . R_HWT_SIMULATION_MODE
 */
#define  VTSS_F_SD25G_TARGET_CMU_16_R_HWT_SIMULATION_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_16_R_HWT_SIMULATION_MODE  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_16_R_HWT_SIMULATION_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_17
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_17(target)     VTSS_IOREG(target,0x17)

/** 
 * \brief
 * BIST enable control for all lanes
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_17 . R_BIST_ALL
 */
#define  VTSS_F_SD25G_TARGET_CMU_17_R_BIST_ALL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_17_R_BIST_ALL  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_17_R_BIST_ALL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1: enable LS3 loopback path.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_17 . R_LBSLV_IN_PMAD
 */
#define  VTSS_F_SD25G_TARGET_CMU_17_R_LBSLV_IN_PMAD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_17_R_LBSLV_IN_PMAD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_17_R_LBSLV_IN_PMAD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_18
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_18(target)     VTSS_IOREG(target,0x18)

/** 
 * \brief
 * Reset signal for pll, low active
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_18 . R_PLL_RSTN
 */
#define  VTSS_F_SD25G_TARGET_CMU_18_R_PLL_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_18_R_PLL_RSTN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_18_R_PLL_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_18 . R_PLL_LOL_SET
 */
#define  VTSS_F_SD25G_TARGET_CMU_18_R_PLL_LOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_18_R_PLL_LOL_SET  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_18_R_PLL_LOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_18 . R_PLL_LOS_SET
 */
#define  VTSS_F_SD25G_TARGET_CMU_18_R_PLL_LOS_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_18_R_PLL_LOS_SET  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_18_R_PLL_LOS_SET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_18 . R_PLL_TP_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_18_R_PLL_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_18_R_PLL_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_18_R_PLL_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_19
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_19(target)     VTSS_IOREG(target,0x19)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_19 . R_CK_RESETB
 */
#define  VTSS_F_SD25G_TARGET_CMU_19_R_CK_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_19_R_CK_RESETB  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_19_R_CK_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_19 . R_PLL_DLOL_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_19_R_PLL_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_19_R_PLL_DLOL_EN  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_19_R_PLL_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1A(target)     VTSS_IOREG(target,0x1a)

/** 
 * \brief
 * Data width control:000: 10 bit 001: 16 bit 010: 20 bit 011: 32 bit 100: 
 * 64 bit
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1A . R_DWIDTHCTRL_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Data width/rate control from register or hardward pin.0: cfg control 1:
 * hwt control
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1A . R_DWIDTHCTRL_FROM_HWT
 */
#define  VTSS_F_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_FROM_HWT  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1A . R_MASK_EI_SOURCE
 */
#define  VTSS_F_SD25G_TARGET_CMU_1A_R_MASK_EI_SOURCE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_1A_R_MASK_EI_SOURCE  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_1A_R_MASK_EI_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Link based,To select between interface pin control (default) and
 * register control of 1. DFE coefficient control 2. Power down control 3.
 * 50ohm term control 4. Eye scan enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1A . R_REG_MANUAL
 */
#define  VTSS_F_SD25G_TARGET_CMU_1A_R_REG_MANUAL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_CMU_1A_R_REG_MANUAL  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_CMU_1A_R_REG_MANUAL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1B(target)     VTSS_IOREG(target,0x1b)

/** 
 * \brief
 * Deassert ppm control default :10'h032=50
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1B . R_PLL_LOL_DF1_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_1B_R_PLL_LOL_DF1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_1B_R_PLL_LOL_DF1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_1B_R_PLL_LOL_DF1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1C(target)     VTSS_IOREG(target,0x1c)

/** 
 * \brief
 * Deassert ppm control default :10'h032=50
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1C . R_PLL_LOL_DF1_9_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_1C_R_PLL_LOL_DF1_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_1C_R_PLL_LOL_DF1_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_1C_R_PLL_LOL_DF1_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1D(target)     VTSS_IOREG(target,0x1d)

/** 
 * \brief
 * Assert ppm control default :10'h0c8=200
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1D . R_PLL_LOL_DF2_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_1D_R_PLL_LOL_DF2_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_1D_R_PLL_LOL_DF2_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_1D_R_PLL_LOL_DF2_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1E(target)     VTSS_IOREG(target,0x1e)

/** 
 * \brief
 * Assert ppm control default :10'h0c8=200
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1E . R_PLL_LOL_DF2_9_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_1E_R_PLL_LOL_DF2_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_1E_R_PLL_LOL_DF2_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_1E_R_PLL_LOL_DF2_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_0:CMU_1F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_1F(target)     VTSS_IOREG(target,0x1f)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1F . R_RXEI_FILTER_FACTOR_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_1F_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_1F_R_RXEI_FILTER_FACTOR_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_1F_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_1F . R_MULTI_LANE_MODE
 */
#define  VTSS_F_SD25G_TARGET_CMU_1F_R_MULTI_LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_1F_R_MULTI_LANE_MODE  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_1F_R_MULTI_LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * Register Group: \a SD25G_TARGET:CMU_GRP_1
 *
 * Register group for registers 0x21 to 0x32
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_21
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_21(target)     VTSS_IOREG(target,0x21)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_21 . R_BIST_PATTERN_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_21_R_BIST_PATTERN_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_21_R_BIST_PATTERN_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_21_R_BIST_PATTERN_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_22
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_22(target)     VTSS_IOREG(target,0x22)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_22 . R_BIST_PATTERN_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_22_R_BIST_PATTERN_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_22_R_BIST_PATTERN_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_22_R_BIST_PATTERN_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_23
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_23(target)     VTSS_IOREG(target,0x23)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_23 . R_BIST_PATTERN_23_16
 */
#define  VTSS_F_SD25G_TARGET_CMU_23_R_BIST_PATTERN_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_23_R_BIST_PATTERN_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_23_R_BIST_PATTERN_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_24
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_24(target)     VTSS_IOREG(target,0x24)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_24 . R_BIST_PATTERN_31_24
 */
#define  VTSS_F_SD25G_TARGET_CMU_24_R_BIST_PATTERN_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_24_R_BIST_PATTERN_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_24_R_BIST_PATTERN_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_25
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_25(target)     VTSS_IOREG(target,0x25)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_25 . R_BIST_PATTERN_39_32
 */
#define  VTSS_F_SD25G_TARGET_CMU_25_R_BIST_PATTERN_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_25_R_BIST_PATTERN_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_25_R_BIST_PATTERN_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_26
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_26(target)     VTSS_IOREG(target,0x26)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_26 . R_BIST_PATTERN_47_40
 */
#define  VTSS_F_SD25G_TARGET_CMU_26_R_BIST_PATTERN_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_26_R_BIST_PATTERN_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_26_R_BIST_PATTERN_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_27
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_27(target)     VTSS_IOREG(target,0x27)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_27 . R_BIST_PATTERN_55_48
 */
#define  VTSS_F_SD25G_TARGET_CMU_27_R_BIST_PATTERN_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_27_R_BIST_PATTERN_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_27_R_BIST_PATTERN_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_28
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_28(target)     VTSS_IOREG(target,0x28)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_28 . R_BIST_PATTERN_63_56
 */
#define  VTSS_F_SD25G_TARGET_CMU_28_R_BIST_PATTERN_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_28_R_BIST_PATTERN_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_28_R_BIST_PATTERN_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_29
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_29(target)     VTSS_IOREG(target,0x29)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_29 . R_TXEI_DLY_SEL_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_29_R_TXEI_DLY_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_29_R_TXEI_DLY_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_29_R_TXEI_DLY_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_29 . R_DISABLE_EI_FILTER
 */
#define  VTSS_F_SD25G_TARGET_CMU_29_R_DISABLE_EI_FILTER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_29_R_DISABLE_EI_FILTER  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_29_R_DISABLE_EI_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Reset RX FIFO if RXEI is asserted:0 : disable,1 : enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_29 . R_RXEI_FIFO_RST_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_29_R_RXEI_FIFO_RST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_29_R_RXEI_FIFO_RST_EN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_29_R_RXEI_FIFO_RST_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Refer to hwt_fom_sel
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_29 . R_FOM_SEL
 */
#define  VTSS_F_SD25G_TARGET_CMU_29_R_FOM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_CMU_29_R_FOM_SEL  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_CMU_29_R_FOM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_29 . R_INTBIST_RESULT_SEL
 */
#define  VTSS_F_SD25G_TARGET_CMU_29_R_INTBIST_RESULT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_CMU_29_R_INTBIST_RESULT_SEL  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_CMU_29_R_INTBIST_RESULT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2A(target)     VTSS_IOREG(target,0x2a)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2A . R_DBG_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_2A_R_DBG_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_2A_R_DBG_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_2A_R_DBG_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2A . R_DBG_LINK_LANE
 */
#define  VTSS_F_SD25G_TARGET_CMU_2A_R_DBG_LINK_LANE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_2A_R_DBG_LINK_LANE  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_2A_R_DBG_LINK_LANE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2A . R_DBG_LOL_STATUS
 */
#define  VTSS_F_SD25G_TARGET_CMU_2A_R_DBG_LOL_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_2A_R_DBG_LOL_STATUS  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_2A_R_DBG_LOL_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2B(target)     VTSS_IOREG(target,0x2b)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2B . R_DBG_LANE_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_2B_R_DBG_LANE_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_2B_R_DBG_LANE_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_2B_R_DBG_LANE_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2B . R_DBG_OBS_SEL_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_2B_R_DBG_OBS_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_CMU_2B_R_DBG_OBS_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_CMU_2B_R_DBG_OBS_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2C(target)     VTSS_IOREG(target,0x2c)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2C . R_PLL_LOL_ASSERT_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_2C_R_PLL_LOL_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_2C_R_PLL_LOL_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_2C_R_PLL_LOL_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2D(target)     VTSS_IOREG(target,0x2d)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2D . R_PLL_LOL_ASSERT_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_2D_R_PLL_LOL_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_2D_R_PLL_LOL_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_2D_R_PLL_LOL_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2E(target)     VTSS_IOREG(target,0x2e)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2E . R_PLL_LOL_DEASSERT_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_2E_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_2E_R_PLL_LOL_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_2E_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_2F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_2F(target)     VTSS_IOREG(target,0x2f)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_2F . R_PLL_LOL_DEASSERT_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_2F_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_2F_R_PLL_LOL_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_2F_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_30
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_30(target)     VTSS_IOREG(target,0x30)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_30 . R_TXFIFO_CK_DIV_PMAD_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_30 . R_RXFIFO_CK_DIV_PMAD_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_31
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_31(target)     VTSS_IOREG(target,0x31)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_31 . CFG_COMMON_RESERVE_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_1:CMU_32
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_32(target)     VTSS_IOREG(target,0x32)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_32 . CFG_COMMON_RESERVE_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_32_CFG_COMMON_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_32_CFG_COMMON_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_32_CFG_COMMON_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD25G_TARGET:CMU_GRP_2
 *
 * Register group for registers 0x40 to 0x4C
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_40
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_40(target)     VTSS_IOREG(target,0x40)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_CKSKEW_CTRL
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_CKSKEW_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_CKSKEW_CTRL  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_CKSKEW_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_ISCAN_HOLD
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_ISCAN_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_ISCAN_HOLD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_ISCAN_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_PD_CLK
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_PD_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_PD_CLK  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_PD_CLK(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_TXCAL_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_EN  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_TXCAL_MAN_EN
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_MAN_EN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_40 . L0_CFG_TXCAL_RST
 */
#define  VTSS_F_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_RST  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_CMU_40_L0_CFG_TXCAL_RST(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_41
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_41(target)     VTSS_IOREG(target,0x41)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_41 . L0_CFG_BW_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_41_L0_CFG_BW_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_41_L0_CFG_BW_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_41_L0_CFG_BW_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_42
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_42(target)     VTSS_IOREG(target,0x42)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_42 . L0_CFG_PHASE_MAN_4_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_42_L0_CFG_PHASE_MAN_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_CMU_42_L0_CFG_PHASE_MAN_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_CMU_42_L0_CFG_PHASE_MAN_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_43
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_43(target)     VTSS_IOREG(target,0x43)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_43 . L0_CFG_QUAD_MAN
 */
#define  VTSS_F_SD25G_TARGET_CMU_43_L0_CFG_QUAD_MAN(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_43_L0_CFG_QUAD_MAN     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_43_L0_CFG_QUAD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_44
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_44(target)     VTSS_IOREG(target,0x44)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_44 . L0_CFG_TXCAL_SHIFT_CODE_5_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD25G_TARGET_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD25G_TARGET_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_45
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_45(target)     VTSS_IOREG(target,0x45)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_45 . L0_CFG_TX_RESERVE_7_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_45_L0_CFG_TX_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_45_L0_CFG_TX_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_45_L0_CFG_TX_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_46
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_46(target)     VTSS_IOREG(target,0x46)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_46 . L0_CFG_TX_RESERVE_15_8
 */
#define  VTSS_F_SD25G_TARGET_CMU_46_L0_CFG_TX_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_46_L0_CFG_TX_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_46_L0_CFG_TX_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_47
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_47(target)     VTSS_IOREG(target,0x47)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_47 . L0_CFG_ITX_IPCML_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_47 . L0_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_48
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_48(target)     VTSS_IOREG(target,0x48)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_48 . L0_CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_48 . L0_CFG_TX_PREDIV_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_48_L0_CFG_TX_PREDIV_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_48_L0_CFG_TX_PREDIV_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_48_L0_CFG_TX_PREDIV_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_49
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_49(target)     VTSS_IOREG(target,0x49)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_49 . L2_CFG_ITX_IPCML_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_49 . L2_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_4A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_4A(target)     VTSS_IOREG(target,0x4a)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4A . L2_CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4A . L2_CFG_TX_PREDIV_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4A_L2_CFG_TX_PREDIV_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_4A_L2_CFG_TX_PREDIV_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_4A_L2_CFG_TX_PREDIV_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_4B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_4B(target)     VTSS_IOREG(target,0x4b)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4B . L3_CFG_ITX_IPCML_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4B . L3_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_2:CMU_4C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_4C(target)     VTSS_IOREG(target,0x4c)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4C . L3_CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_4C . L3_CFG_TX_PREDIV_1_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_4C_L3_CFG_TX_PREDIV_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_CMU_4C_L3_CFG_TX_PREDIV_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_CMU_4C_L3_CFG_TX_PREDIV_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SD25G_TARGET:CMU_GRP_3
 *
 * Register group for register 0xC0
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_3:CMU_C0
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_C0(target)     VTSS_IOREG(target,0xc0)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_C0 . READ_VCO_CTUNE_3_0
 */
#define  VTSS_F_SD25G_TARGET_CMU_C0_READ_VCO_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_CMU_C0_READ_VCO_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_CMU_C0_READ_VCO_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Loss of lock (PLL)
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_C0 . PLL_LOL_UDL
 */
#define  VTSS_F_SD25G_TARGET_CMU_C0_PLL_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_CMU_C0_PLL_LOL_UDL  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_CMU_C0_PLL_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * Register Group: \a SD25G_TARGET:CMU_GRP_4
 *
 * Register group for register 0xFF
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:CMU_GRP_4:CMU_FF
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_CMU_FF(target)     VTSS_IOREG(target,0xff)

/** 
 * \brief
 * Index for register access
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_CMU_FF . REGISTER_TABLE_INDEX
 */
#define  VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD25G_TARGET:LANE_GRP_0
 *
 * Register group for registers 0x00 to 0x47
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_00
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_00(target)    VTSS_IOREG(target,0x100)

/** 
 * \brief
 * TX driver amplitude fine tuning
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_00 . LN_CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_00 . LN_CFG_ITX_IPCML_BASE_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_01
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_01(target)    VTSS_IOREG(target,0x101)

/** 
 * \brief
 * 0:1000m 1:1200m 2: 900m 3: 800m 4: 700m 5: 500m 6: 400m 7: 600m
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_01 . LN_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * TX sub rate control
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_01 . LN_CFG_TX_PREDIV_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_01_LN_CFG_TX_PREDIV_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_01_LN_CFG_TX_PREDIV_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_01_LN_CFG_TX_PREDIV_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_02
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_02(target)    VTSS_IOREG(target,0x102)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_02 . LN_CFG_CKSKEW_CTRL
 */
#define  VTSS_F_SD25G_TARGET_LANE_02_LN_CFG_CKSKEW_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_02_LN_CFG_CKSKEW_CTRL  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_02_LN_CFG_CKSKEW_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_03
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_03(target)    VTSS_IOREG(target,0x103)

/** 
 * \brief
 * 1st stage post-equalization level control of TX
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_03 . LN_CFG_TAP_DLY_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_04
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_04(target)    VTSS_IOREG(target,0x104)

/** 
 * \brief
 * TX to RX loopback enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_TX2RX_LP_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_TX2RX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_TX2RX_LP_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_TX2RX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * RX to TX loopback enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_RX2TX_LP_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_RX2TX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_RX2TX_LP_EN  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_RX2TX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Power down CML circuits
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_PD_CML
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_PD_CML(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_PD_CML  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_PD_CML(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Power down clock circuits
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_PD_CLK
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_PD_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_PD_CLK  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_PD_CLK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Power down TX driver
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_PD_DRIVER
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_PD_DRIVER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_PD_DRIVER  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_PD_DRIVER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * TX data path setting. Should set to 1.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_04 . LN_CFG_TAP_MAIN
 */
#define  VTSS_F_SD25G_TARGET_LANE_04_LN_CFG_TAP_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_04_LN_CFG_TAP_MAIN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_04_LN_CFG_TAP_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_05
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_05(target)    VTSS_IOREG(target,0x105)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_05 . LN_CFG_TAP_DLY2_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_05_LN_CFG_TAP_DLY2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_05_LN_CFG_TAP_DLY2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_05_LN_CFG_TAP_DLY2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_05 . LN_CFG_BW_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_05_LN_CFG_BW_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_05_LN_CFG_BW_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_05_LN_CFG_BW_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_06
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_06(target)    VTSS_IOREG(target,0x106)

/** 
 * \brief
 * Enable TX data path control.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_06 . LN_CFG_EN_MAIN
 */
#define  VTSS_F_SD25G_TARGET_LANE_06_LN_CFG_EN_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_06_LN_CFG_EN_MAIN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_06_LN_CFG_EN_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Pre-equalization level control of TX
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_06 . LN_CFG_TAP_ADV_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_07
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_07(target)    VTSS_IOREG(target,0x107)

/** 
 * \brief
 * Enable pre-equalization control of TX.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_07 . LN_CFG_EN_ADV
 */
#define  VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_07 . LN_CFG_EN_DLY2
 */
#define  VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY2(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY2  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY2(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable 1st stage post-equalization control of TX.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_07 . LN_CFG_EN_DLY
 */
#define  VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_08
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_08(target)    VTSS_IOREG(target,0x108)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_08 . LN_CFG_PHASE_MAN_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_08_LN_CFG_PHASE_MAN_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_08_LN_CFG_PHASE_MAN_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_08_LN_CFG_PHASE_MAN_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_09
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_09(target)    VTSS_IOREG(target,0x109)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_09 . LN_CFG_TXCAL_VALID_SEL_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0A(target)    VTSS_IOREG(target,0x10a)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0A . LN_CFG_TXCAL_SHIFT_CODE_5_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD25G_TARGET_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD25G_TARGET_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0B(target)    VTSS_IOREG(target,0x10b)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0B . LN_CFG_TXCAL_MAN_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_MAN_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0B . LN_CFG_TXCAL_RST
 */
#define  VTSS_F_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_RST  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_0B_LN_CFG_TXCAL_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0B . LN_CFG_QUAD_MAN_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_0B_LN_CFG_QUAD_MAN_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_0B_LN_CFG_QUAD_MAN_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_0B_LN_CFG_QUAD_MAN_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0C(target)    VTSS_IOREG(target,0x10c)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0C . LN_CFG_PMA_TX_CK_BITWIDTH_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0C . LN_CFG_TXCAL_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_0C_LN_CFG_TXCAL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_0C_LN_CFG_TXCAL_EN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_0C_LN_CFG_TXCAL_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0C . LN_CFG_RXTERM_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_0C_LN_CFG_RXTERM_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_0C_LN_CFG_RXTERM_PD  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_0C_LN_CFG_RXTERM_PD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0D(target)    VTSS_IOREG(target,0x10d)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0D . LN_CFG_RXTERM_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_RXTERM_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_RXTERM_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_0D_LN_CFG_RXTERM_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * PMAA FIFO clock reset
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0D . LN_CFG_RSTN_DIV5_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_RSTN_DIV5_8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_RSTN_DIV5_8  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_0D_LN_CFG_RSTN_DIV5_8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0D . LN_CFG_SUMMER_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_SUMMER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_SUMMER_EN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_0D_LN_CFG_SUMMER_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0D . LN_CFG_DMUX_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_DMUX_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_DMUX_PD  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_0D_LN_CFG_DMUX_PD(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * DFE related clock enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0D . LN_CFG_DFECK_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0E(target)    VTSS_IOREG(target,0x10e)

/** 
 * \brief
 * Eye scan enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0E . LN_CFG_ISCAN_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_ISCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_ISCAN_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_0E_LN_CFG_ISCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0E . LN_CFG_DMUX_CLK_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_DMUX_CLK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_DMUX_CLK_PD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_0E_LN_CFG_DMUX_CLK_PD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable DFE digital adaptation
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0E . LN_CFG_EN_DFEDIG
 */
#define  VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Time constant for DFE adaptation
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0E . LN_CFG_DFEDIG_M_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_DFEDIG_M_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_DFEDIG_M_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_0E_LN_CFG_DFEDIG_M_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_0F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_0F(target)    VTSS_IOREG(target,0x10f)

/** 
 * \brief
 * DFE tap enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_0F . LN_CFG_DFETAP_EN_5_1
 */
#define  VTSS_F_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_10
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_10(target)    VTSS_IOREG(target,0x110)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_10 . LN_CFG_DFE_DLEV_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_10_LN_CFG_DFE_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_10_LN_CFG_DFE_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_10_LN_CFG_DFE_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_11
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_11(target)    VTSS_IOREG(target,0x111)

/** 
 * \brief
 * Bypass DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_11 . LN_CFG_DFE_BYP_H5_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Bypass DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_11 . LN_CFG_DFE_BYP_H4_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_12
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_12(target)    VTSS_IOREG(target,0x112)

/** 
 * \brief
 * Bypass DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_12 . LN_CFG_DFE_BYP_H3_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_13
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_13(target)    VTSS_IOREG(target,0x113)

/** 
 * \brief
 * Bypass DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_13 . LN_CFG_DFE_BYP_H2_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_14
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_14(target)    VTSS_IOREG(target,0x114)

/** 
 * \brief
 * Bypass DFE coefficient
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_14 . LN_CFG_DFE_BYP_H1_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_14_LN_CFG_DFE_BYP_H1_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_14_LN_CFG_DFE_BYP_H1_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_14_LN_CFG_DFE_BYP_H1_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_15
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_15(target)    VTSS_IOREG(target,0x115)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_15 . LN_CFG_DFEDIG_BYP_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_15_LN_CFG_DFEDIG_BYP_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_15_LN_CFG_DFEDIG_BYP_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_15_LN_CFG_DFEDIG_BYP_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_16
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_16(target)    VTSS_IOREG(target,0x116)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_16 . LN_CFG_DFEDIG_BYP_10_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_16_LN_CFG_DFEDIG_BYP_10_8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_16_LN_CFG_DFEDIG_BYP_10_8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_16_LN_CFG_DFEDIG_BYP_10_8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_17
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_17(target)    VTSS_IOREG(target,0x117)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_17 . LN_CFG_COMP_NUM_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_17_LN_CFG_COMP_NUM_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_17_LN_CFG_COMP_NUM_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_17_LN_CFG_COMP_NUM_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_18
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_18(target)    VTSS_IOREG(target,0x118)

/** 
 * \brief
 * CDR clock enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_18 . LN_CFG_CDRCK_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_CDRCK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_CDRCK_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_18_LN_CFG_CDRCK_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_18 . LN_CFG_ADD_VOLT
 */
#define  VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_ADD_VOLT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ADD_VOLT  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_18_LN_CFG_ADD_VOLT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_18 . LN_CFG_MAN_VOLT_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_MAN_VOLT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_MAN_VOLT_EN  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_18_LN_CFG_MAN_VOLT_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Power down error amplifier for DFE adaptation
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_18 . LN_CFG_ERRAMP_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * See application note
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_18 . LN_CFG_RXDIV_SEL_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_19
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_19(target)    VTSS_IOREG(target,0x119)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_DCDR_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_DCDR_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_DCDR_PD  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_DCDR_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_ECDR_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_ECDR_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_ECDR_PD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_ECDR_PD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_ISCAN_SEL
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_ISCAN_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_ISCAN_SEL  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_ISCAN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * TX loopback enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_TXLB_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_TXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_TXLB_EN  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_TXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Power up RX regulator
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_RX_REG_PU
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_PU(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_PU  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_PU(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Bypass RX regulator
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_RX_REG_BYP
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_BYP  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_RX_REG_BYP(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_PD_RMS_DET
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_PD_RMS_DET(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_PD_RMS_DET  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_PD_RMS_DET(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Power down CTLE
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_19 . LN_CFG_PD_CTLE
 */
#define  VTSS_F_SD25G_TARGET_LANE_19_LN_CFG_PD_CTLE(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_PD_CTLE  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_19_LN_CFG_PD_CTLE(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1A(target)    VTSS_IOREG(target,0x11a)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1A . LN_CFG_CTLE_TP_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1A_LN_CFG_CTLE_TP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_1A_LN_CFG_CTLE_TP_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_1A_LN_CFG_CTLE_TP_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1A . LN_CFG_CDR_KF_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_1A_LN_CFG_CDR_KF_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_1A_LN_CFG_CDR_KF_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_1A_LN_CFG_CDR_KF_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1B(target)    VTSS_IOREG(target,0x11b)

/** 
 * \brief
 * CDR BW setting
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1B . LN_CFG_CDR_M_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_1B_LN_CFG_CDR_M_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_1B_LN_CFG_CDR_M_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_1B_LN_CFG_CDR_M_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1C(target)    VTSS_IOREG(target,0x11c)

/** 
 * \brief
 * CDR resetn
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1C . LN_CFG_CDR_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Power down DFE analog circuits
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1C . LN_CFG_DFE_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1C . LN_CFG_DFEDMX_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * CTLE “C” setting
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1C . LN_CFG_EQC_FORCE_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1D(target)    VTSS_IOREG(target,0x11d)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_ISCAN_EXT_OVR
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_EXT_OVR  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_ISCAN_HOLD
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_HOLD  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Eye scan resetn
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_ISCAN_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_RSTN  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_ISCAN_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_AGC_ADPT_BYP
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_AGC_ADPT_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_AGC_ADPT_BYP  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_AGC_ADPT_BYP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_PHID_1T
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PHID_1T(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PHID_1T  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_PHID_1T(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Required for DFE
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_PI_DFE_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_PI_EXT_OVR
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PI_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PI_EXT_OVR  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_PI_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Place CDR in "holding" state Recovered clock does not track data
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1D . LN_CFG_PI_HOLD
 */
#define  VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PI_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PI_HOLD  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_1D_LN_CFG_PI_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1E(target)    VTSS_IOREG(target,0x11e)

/** 
 * \brief
 * PI step size
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1E . LN_CFG_PI_STEPS_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_PI_STEPS_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_PI_STEPS_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_1E_LN_CFG_PI_STEPS_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * RX loopback enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1E . LN_CFG_RXLB_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_RXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_RXLB_EN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_1E_LN_CFG_RXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Required.  Set to 1 in normal mode
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1E . LN_CFG_SUM_SETCM_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_SUM_SETCM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_SUM_SETCM_EN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_1E_LN_CFG_SUM_SETCM_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1E . LN_CFG_R_OFFSET_DIR
 */
#define  VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_R_OFFSET_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_R_OFFSET_DIR  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_1E_LN_CFG_R_OFFSET_DIR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1E . LN_CFG_PMAD_CK_PD
 */
#define  VTSS_F_SD25G_TARGET_LANE_1E_LN_CFG_PMAD_CK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_1E_LN_CFG_PMAD_CK_PD  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_1E_LN_CFG_PMAD_CK_PD(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_1F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_1F(target)    VTSS_IOREG(target,0x11f)

/** 
 * \brief
 * CTLE "R" bypass
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1F . LN_CFG_EQR_BYP
 */
#define  VTSS_F_SD25G_TARGET_LANE_1F_LN_CFG_EQR_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_1F_LN_CFG_EQR_BYP  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_1F_LN_CFG_EQR_BYP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_1F . LN_CFG_OS_MAN_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_1F_LN_CFG_OS_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_1F_LN_CFG_OS_MAN_EN  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_1F_LN_CFG_OS_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_20
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_20(target)    VTSS_IOREG(target,0x120)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_20 . LN_CFG_MAN_VOLT_SEL_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_21
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_21(target)    VTSS_IOREG(target,0x121)

/** 
 * \brief
 * VGA code bypass
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_21 . LN_CFG_VGA_CTRL_BYP_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_22
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_22(target)    VTSS_IOREG(target,0x122)

/** 
 * \brief
 * CTLE "R" code
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_22 . LN_CFG_EQR_FORCE_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_23
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_23(target)    VTSS_IOREG(target,0x123)

/** 
 * \brief
 * CDR phase interpolator enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_23 . LN_CFG_PI_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_23_LN_CFG_PI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_23_LN_CFG_PI_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_23_LN_CFG_PI_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * VGA code bypass
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_23 . LN_CFG_VGA_BYP
 */
#define  VTSS_F_SD25G_TARGET_LANE_23_LN_CFG_VGA_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_23_LN_CFG_VGA_BYP  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_23_LN_CFG_VGA_BYP(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_24
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_24(target)    VTSS_IOREG(target,0x124)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_24 . LN_CFG_OS_5_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_24_LN_CFG_OS_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD25G_TARGET_LANE_24_LN_CFG_OS_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD25G_TARGET_LANE_24_LN_CFG_OS_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_25
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_25(target)    VTSS_IOREG(target,0x125)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_25 . LN_CFG_INIT_POS_ISCAN_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_26
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_26(target)    VTSS_IOREG(target,0x126)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_26 . LN_CFG_INIT_POS_IPI_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_26_LN_CFG_INIT_POS_IPI_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_26_LN_CFG_INIT_POS_IPI_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_26_LN_CFG_INIT_POS_IPI_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_27
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_27(target)    VTSS_IOREG(target,0x127)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_27 . LN_CFG_INIT_POS_QPI_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_27_LN_CFG_INIT_POS_QPI_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_27_LN_CFG_INIT_POS_QPI_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_27_LN_CFG_INIT_POS_QPI_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_28
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_28(target)    VTSS_IOREG(target,0x128)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_28 . LN_CFG_ISCAN_MODE_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_ISCAN_MODE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_ISCAN_MODE_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_28_LN_CFG_ISCAN_MODE_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_28 . LN_CFG_RX_SSC_LH
 */
#define  VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_RX_SSC_LH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_RX_SSC_LH  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_28_LN_CFG_RX_SSC_LH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Fast eye scan method.0:Calculate central phase 1:Calculate all phase
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_28 . LN_CFG_FIGMERIT_SEL
 */
#define  VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_FIGMERIT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_FIGMERIT_SEL  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_28_LN_CFG_FIGMERIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * full/subrate frequency selection:00: full 01: 1/2 10: 1/4 11: 1/8
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_28 . LN_CFG_RX_SUBRATE_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_RX_SUBRATE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_RX_SUBRATE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_28_LN_CFG_RX_SUBRATE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_29
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_29(target)    VTSS_IOREG(target,0x129)

/** 
 * \brief
 * 2nd order CDR setting.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_29 . LN_CFG_FILTER2ND_YZ_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_29_LN_CFG_FILTER2ND_YZ_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_29_LN_CFG_FILTER2ND_YZ_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_29_LN_CFG_FILTER2ND_YZ_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2A(target)    VTSS_IOREG(target,0x12a)

/** 
 * \brief
 * 2nd order CDR tracking setting
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2A . LN_CFG_PI_FLOOP_STEPS_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2A . LN_CFG_DISLOL
 */
#define  VTSS_F_SD25G_TARGET_LANE_2A_LN_CFG_DISLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_2A_LN_CFG_DISLOL  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_2A_LN_CFG_DISLOL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2B(target)    VTSS_IOREG(target,0x12b)

/** 
 * \brief
 * Phase interpolator bandwidth setting,data rate dependent
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2B . LN_CFG_PI_BW_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2B_LN_CFG_PI_BW_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_2B_LN_CFG_PI_BW_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_2B_LN_CFG_PI_BW_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2B . LN_CFG_RSTN_DMUX_SUBR
 */
#define  VTSS_F_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_DMUX_SUBR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_DMUX_SUBR  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_DMUX_SUBR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2B . LN_CFG_RSTN_TXDUPU
 */
#define  VTSS_F_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_TXDUPU(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_TXDUPU  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_2B_LN_CFG_RSTN_TXDUPU(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2C(target)    VTSS_IOREG(target,0x12c)

/** 
 * \brief
 * full/subrate frequency selection:00: full 01: 1/2 10: 1/4 11: 1/8
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2C . LN_CFG_TX_SUBRATE_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2C_LN_CFG_TX_SUBRATE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_2C_LN_CFG_TX_SUBRATE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_2C_LN_CFG_TX_SUBRATE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Disable 2nd order CDR
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2C . LN_CFG_DIS_2NDORDER
 */
#define  VTSS_F_SD25G_TARGET_LANE_2C_LN_CFG_DIS_2NDORDER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_2C_LN_CFG_DIS_2NDORDER  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_2C_LN_CFG_DIS_2NDORDER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2D(target)    VTSS_IOREG(target,0x12d)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2D . LN_CFG_ALOS_THR_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2D_LN_CFG_ALOS_THR_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_2D_LN_CFG_ALOS_THR_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_2D_LN_CFG_ALOS_THR_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2D . LN_CFG_SAT_CNTSEL_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2D_LN_CFG_SAT_CNTSEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_2D_LN_CFG_SAT_CNTSEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_2D_LN_CFG_SAT_CNTSEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2E(target)    VTSS_IOREG(target,0x12e)

/** 
 * \brief
 * Fast eye scan enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_EN_FAST_ISCAN
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_EN_FAST_ISCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_EN_FAST_ISCAN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_EN_FAST_ISCAN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_DIS_SQ
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_DIS_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_DIS_SQ  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_DIS_SQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_PD_SQ
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_PD_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_PD_SQ  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_PD_SQ(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_DIS_ALOS
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_DIS_ALOS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_DIS_ALOS  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_DIS_ALOS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_RESETN_AGC
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RESETN_AGC(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RESETN_AGC  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_RESETN_AGC(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Reset DFE digital adaptation
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_RSTN_DFEDIG
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Reset PI controller
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_PI_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_PI_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_PI_RSTN  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_PI_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2E . LN_CFG_CTLE_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_CTLE_RSTN  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_2F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_2F(target)    VTSS_IOREG(target,0x12f)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2F . LN_CFG_XS_MARGIN_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2F_LN_CFG_XS_MARGIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_2F_LN_CFG_XS_MARGIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_2F_LN_CFG_XS_MARGIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_2F . LN_CFG_RX_SP_CTLE_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_2F_LN_CFG_RX_SP_CTLE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_2F_LN_CFG_RX_SP_CTLE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_2F_LN_CFG_RX_SP_CTLE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_30
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_30(target)    VTSS_IOREG(target,0x130)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_30 . LN_CFG_ISEL_CTLE_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_30_LN_CFG_ISEL_CTLE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_30_LN_CFG_ISEL_CTLE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_30_LN_CFG_ISEL_CTLE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_30 . LN_CFG_RX_REG_VSEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_30_LN_CFG_RX_REG_VSEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_30_LN_CFG_RX_REG_VSEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_30_LN_CFG_RX_REG_VSEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_31
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_31(target)    VTSS_IOREG(target,0x131)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_31 . LN_CFG_AGC_CNT_SEL_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_31_LN_CFG_AGC_CNT_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_31_LN_CFG_AGC_CNT_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_31_LN_CFG_AGC_CNT_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_31 . LN_CFG_CTLE_TP_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_31_LN_CFG_CTLE_TP_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_31_LN_CFG_CTLE_TP_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_31_LN_CFG_CTLE_TP_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_32
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_32(target)    VTSS_IOREG(target,0x132)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_32 . LN_CFG_AGC_VPP_THR_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_32_LN_CFG_AGC_VPP_THR_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_32_LN_CFG_AGC_VPP_THR_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_32_LN_CFG_AGC_VPP_THR_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_32 . LN_CFG_CTLE_M_THR_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_32_LN_CFG_CTLE_M_THR_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_32_LN_CFG_CTLE_M_THR_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_32_LN_CFG_CTLE_M_THR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_33
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_33(target)    VTSS_IOREG(target,0x133)

/** 
 * \brief
 * BIST enable signal
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_33 . LN_R_BIST_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_33_LN_R_BIST_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * BIST error injection enable
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_33 . LN_R_BIST_ERRINJEC
 */
#define  VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_ERRINJEC(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_ERRINJEC  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_33_LN_R_BIST_ERRINJEC(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST pattern selection
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_33 . LN_R_BIST_MODE_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_MODE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_MODE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD25G_TARGET_LANE_33_LN_R_BIST_MODE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_34
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_34(target)    VTSS_IOREG(target,0x134)

/** 
 * \brief
 * BIST result compare enable.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_34 . LN_R_BIST_CHK
 */
#define  VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_CHK  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_34_LN_R_BIST_CHK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1: bist_err will assert if rx all zero data in PRBS mode.0: Treat all
 * zero data input as correct data Note: r_bist_chk_zero must be set after
 * r_bist_ok is asserted.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_34 . LN_R_BIST_CHK_ZERO
 */
#define  VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_CHK_ZERO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_CHK_ZERO  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_34_LN_R_BIST_CHK_ZERO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 1: bist_err counter will stop when reaching 32'hffff_ffff 0: bist_err
 * counter will run continuously, will not saturate.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_34 . LN_R_BIST_ERRSTOP
 */
#define  VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_ERRSTOP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_ERRSTOP  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_34_LN_R_BIST_ERRSTOP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_34 . LN_R_BIST_RXERR_LBK
 */
#define  VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_RXERR_LBK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_RXERR_LBK  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_34_LN_R_BIST_RXERR_LBK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * 0 : non free running mode 1 : free running mode
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_34 . LN_R_FREE_RUN_MODE
 */
#define  VTSS_F_SD25G_TARGET_LANE_34_LN_R_FREE_RUN_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_34_LN_R_FREE_RUN_MODE  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_34_LN_R_FREE_RUN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_35
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_35(target)    VTSS_IOREG(target,0x135)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_35 . LN_R_TIME_DEASSERT_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_35_LN_R_TIME_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_35_LN_R_TIME_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_35_LN_R_TIME_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_36
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_36(target)    VTSS_IOREG(target,0x136)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_36 . LN_R_TIME_DEASSERT_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_36_LN_R_TIME_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_36_LN_R_TIME_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_36_LN_R_TIME_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_37
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_37(target)    VTSS_IOREG(target,0x137)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_37 . LN_R_TIME_ASSERT_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_37_LN_R_TIME_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_37_LN_R_TIME_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_37_LN_R_TIME_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_38
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_38(target)    VTSS_IOREG(target,0x138)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_38 . LN_R_TIME_ASSERT_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_38_LN_R_TIME_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_38_LN_R_TIME_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_38_LN_R_TIME_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_39
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_39(target)    VTSS_IOREG(target,0x139)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_39 . LN_R_DLOL_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_39_LN_R_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_39_LN_R_DLOL_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_39_LN_R_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3A
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3A(target)    VTSS_IOREG(target,0x13a)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3A . LN_R_DEASSERT_PPM_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_3A_LN_R_DEASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_3A_LN_R_DEASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_3A_LN_R_DEASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3B
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3B(target)    VTSS_IOREG(target,0x13b)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3B . LN_R_DEASSERT_PPM_9_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_3B_LN_R_DEASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_3B_LN_R_DEASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_3B_LN_R_DEASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3C
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3C(target)    VTSS_IOREG(target,0x13c)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3C . LN_R_ASSERT_PPM_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_3C_LN_R_ASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_3C_LN_R_ASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_3C_LN_R_ASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3D
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3D(target)    VTSS_IOREG(target,0x13d)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3D . LN_R_ASSERT_PPM_9_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_3D_LN_R_ASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_3D_LN_R_ASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_3D_LN_R_ASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3E
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3E(target)    VTSS_IOREG(target,0x13e)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3E . LN_R_DLOS_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_3E_LN_R_DLOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_3E_LN_R_DLOS_EN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_3E_LN_R_DLOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3E . LN_R_LOS_CKONE_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_3E_LN_R_LOS_CKONE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_TARGET_LANE_3E_LN_R_LOS_CKONE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_TARGET_LANE_3E_LN_R_LOS_CKONE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_3F
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_3F(target)    VTSS_IOREG(target,0x13f)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3F . LN_R_TIME_LOS_2_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_3F_LN_R_TIME_LOS_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_TARGET_LANE_3F_LN_R_TIME_LOS_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_TARGET_LANE_3F_LN_R_TIME_LOS_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3F . LN_R_ALOS_EN
 */
#define  VTSS_F_SD25G_TARGET_LANE_3F_LN_R_ALOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_3F_LN_R_ALOS_EN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_3F_LN_R_ALOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3F . LN_R_LOL_RESET
 */
#define  VTSS_F_SD25G_TARGET_LANE_3F_LN_R_LOL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_3F_LN_R_LOL_RESET  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_3F_LN_R_LOL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3F . LN_R_TX_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_3F_LN_R_TX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_3F_LN_R_TX_RSTN  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_3F_LN_R_TX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_3F . LN_R_RX_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_3F_LN_R_RX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD25G_TARGET_LANE_3F_LN_R_RX_RSTN  VTSS_BIT(7)
#define  VTSS_X_SD25G_TARGET_LANE_3F_LN_R_RX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_40
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_40(target)    VTSS_IOREG(target,0x140)

/** 
 * \brief
 * TX bit order reversal
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_TX_BIT_REVERSE
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_TX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_TX_BIT_REVERSE  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_TX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * TX polarity invert
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_TX_POL_INV
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_TX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_TX_POL_INV  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_TX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * RX bit order reversal
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_RX_BIT_REVERSE
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_RX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_RX_BIT_REVERSE  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_RX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * RX polarity invert
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_RX_POL_INV
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_RX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_RX_POL_INV  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_RX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * CDR reset
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_CDR_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN  VTSS_BIT(4)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * DFE reset
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_DFE_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN  VTSS_BIT(5)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_40 . LN_R_CTLE_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_40_LN_R_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD25G_TARGET_LANE_40_LN_R_CTLE_RSTN  VTSS_BIT(6)
#define  VTSS_X_SD25G_TARGET_LANE_40_LN_R_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_41
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_41(target)    VTSS_IOREG(target,0x141)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_41 . LN_CFG_TXEI
 */
#define  VTSS_F_SD25G_TARGET_LANE_41_LN_CFG_TXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_41_LN_CFG_TXEI  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_41_LN_CFG_TXEI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_41 . LN_LOL_CLR
 */
#define  VTSS_F_SD25G_TARGET_LANE_41_LN_LOL_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_41_LN_LOL_CLR  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_41_LN_LOL_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_41 . LN_R_TXCAL_RSTN
 */
#define  VTSS_F_SD25G_TARGET_LANE_41_LN_R_TXCAL_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_41_LN_R_TXCAL_RSTN  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_41_LN_R_TXCAL_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_42
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_42(target)    VTSS_IOREG(target,0x142)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_42 . LN_CFG_TX_RESERVE_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_42_LN_CFG_TX_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_42_LN_CFG_TX_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_42_LN_CFG_TX_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_43
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_43(target)    VTSS_IOREG(target,0x143)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_43 . LN_CFG_TX_RESERVE_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_43_LN_CFG_TX_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_43_LN_CFG_TX_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_43_LN_CFG_TX_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_44
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_44(target)    VTSS_IOREG(target,0x144)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_44 . LN_CFG_RX_RESERVE_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_45
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_45(target)    VTSS_IOREG(target,0x145)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_45 . LN_CFG_RX_RESERVE_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_45_LN_CFG_RX_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_45_LN_CFG_RX_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_45_LN_CFG_RX_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_46
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_46(target)    VTSS_IOREG(target,0x146)

/** 
 * \brief
 * 0x0000 : Infinite BIST run time
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_46 . LN_R_BIST_TIMER_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_46_LN_R_BIST_TIMER_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_46_LN_R_BIST_TIMER_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_46_LN_R_BIST_TIMER_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_0:LANE_47
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_47(target)    VTSS_IOREG(target,0x147)

/** 
 * \brief
 * 0x0001 ~ 0xFFFF : BIST run time =(data width/bit rate) *1024*
 * r_bist_timer[15:0]
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_47 . LN_R_BIST_TIMER_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_47_LN_R_BIST_TIMER_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_47_LN_R_BIST_TIMER_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_47_LN_R_BIST_TIMER_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD25G_TARGET:LANE_GRP_1
 *
 * Register group for registers 0xC0 to 0xDE
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C0
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C0(target)    VTSS_IOREG(target,0x1c0)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C0 . LN_TX_CALX_STAT
 */
#define  VTSS_F_SD25G_TARGET_LANE_C0_LN_TX_CALX_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_C0_LN_TX_CALX_STAT  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_C0_LN_TX_CALX_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C0 . LN_TX_CALY_STAT
 */
#define  VTSS_F_SD25G_TARGET_LANE_C0_LN_TX_CALY_STAT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_C0_LN_TX_CALY_STAT  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_C0_LN_TX_CALY_STAT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C0 . LN_TX_CAL_ERR
 */
#define  VTSS_F_SD25G_TARGET_LANE_C0_LN_TX_CAL_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_C0_LN_TX_CAL_ERR  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_C0_LN_TX_CAL_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C1
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C1(target)    VTSS_IOREG(target,0x1c1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C1 . LN_TX_PHI_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_C1_LN_TX_PHI_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_C1_LN_TX_PHI_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_C1_LN_TX_PHI_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C2
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C2(target)    VTSS_IOREG(target,0x1c2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C2 . LN_TX_QRT_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_C2_LN_TX_QRT_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_C2_LN_TX_QRT_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_C2_LN_TX_QRT_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C3
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C3(target)    VTSS_IOREG(target,0x1c3)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C3 . LN_FAST_EYE_SCAN_FAIL
 */
#define  VTSS_F_SD25G_TARGET_LANE_C3_LN_FAST_EYE_SCAN_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_C3_LN_FAST_EYE_SCAN_FAIL  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_C3_LN_FAST_EYE_SCAN_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C3 . LN_SQUELCH
 */
#define  VTSS_F_SD25G_TARGET_LANE_C3_LN_SQUELCH(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_C3_LN_SQUELCH  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_C3_LN_SQUELCH(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C4
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C4(target)    VTSS_IOREG(target,0x1c4)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C4 . LN_PI_DAC_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_C4_LN_PI_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_C4_LN_PI_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_C4_LN_PI_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C5
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C5(target)    VTSS_IOREG(target,0x1c5)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C5 . LN_PI_DAC_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_C5_LN_PI_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_C5_LN_PI_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_C5_LN_PI_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C6
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C6(target)    VTSS_IOREG(target,0x1c6)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C6 . LN_PI_DAC_23_16
 */
#define  VTSS_F_SD25G_TARGET_LANE_C6_LN_PI_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_C6_LN_PI_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_C6_LN_PI_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C7
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C7(target)    VTSS_IOREG(target,0x1c7)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C7 . LN_PI_DAC_30_24
 */
#define  VTSS_F_SD25G_TARGET_LANE_C7_LN_PI_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_C7_LN_PI_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_C7_LN_PI_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C8
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C8(target)    VTSS_IOREG(target,0x1c8)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C8 . LN_PI_QRT_CODE_1_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_C8_LN_PI_QRT_CODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_TARGET_LANE_C8_LN_PI_QRT_CODE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_TARGET_LANE_C8_LN_PI_QRT_CODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C8 . LN_VGAR_CODE_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_C8_LN_VGAR_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_LANE_C8_LN_VGAR_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_LANE_C8_LN_VGAR_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_C9
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_C9(target)    VTSS_IOREG(target,0x1c9)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_C9 . LN_ALOS
 */
#define  VTSS_F_SD25G_TARGET_LANE_C9_LN_ALOS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_C9_LN_ALOS  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_C9_LN_ALOS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CA
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CA(target)    VTSS_IOREG(target,0x1ca)

/** 
 * \brief
 * DFE H1 readback
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CA . LN_H1_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CA_LN_H1_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_CA_LN_H1_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_CA_LN_H1_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CB
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CB(target)    VTSS_IOREG(target,0x1cb)

/** 
 * \brief
 * DFE H2 readback
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CB . LN_H2_4_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CB_LN_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD25G_TARGET_LANE_CB_LN_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD25G_TARGET_LANE_CB_LN_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CC
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CC(target)    VTSS_IOREG(target,0x1cc)

/** 
 * \brief
 * DFE H3 readback
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CC . LN_H3_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CC_LN_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_CC_LN_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_CC_LN_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CD
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CD(target)    VTSS_IOREG(target,0x1cd)

/** 
 * \brief
 * DFE H4 readback
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CD . LN_H4_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CD_LN_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_CD_LN_H4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_CD_LN_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CE
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CE(target)    VTSS_IOREG(target,0x1ce)

/** 
 * \brief
 * DFE H5 readback
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CE . LN_H5_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CE_LN_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD25G_TARGET_LANE_CE_LN_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD25G_TARGET_LANE_CE_LN_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_CF
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_CF(target)    VTSS_IOREG(target,0x1cf)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_CF . LN_DLEV_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_CF_LN_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_CF_LN_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_CF_LN_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D0
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D0(target)    VTSS_IOREG(target,0x1d0)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D0 . LN_ISCAN_RESULTS_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_D0_LN_ISCAN_RESULTS_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D0_LN_ISCAN_RESULTS_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D0_LN_ISCAN_RESULTS_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D1
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D1(target)    VTSS_IOREG(target,0x1d1)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D1 . LN_ISCAN_RESULTS_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_D1_LN_ISCAN_RESULTS_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D1_LN_ISCAN_RESULTS_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D1_LN_ISCAN_RESULTS_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D2
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D2(target)    VTSS_IOREG(target,0x1d2)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D2 . LN_ISCAN_RESULTS_23_16
 */
#define  VTSS_F_SD25G_TARGET_LANE_D2_LN_ISCAN_RESULTS_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D2_LN_ISCAN_RESULTS_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D2_LN_ISCAN_RESULTS_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D3
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D3(target)    VTSS_IOREG(target,0x1d3)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D3 . LN_ISCAN_RESULTS_31_24
 */
#define  VTSS_F_SD25G_TARGET_LANE_D3_LN_ISCAN_RESULTS_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D3_LN_ISCAN_RESULTS_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D3_LN_ISCAN_RESULTS_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D4
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D4(target)    VTSS_IOREG(target,0x1d4)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D4 . LN_ISCAN_RESULTS_39_32
 */
#define  VTSS_F_SD25G_TARGET_LANE_D4_LN_ISCAN_RESULTS_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D4_LN_ISCAN_RESULTS_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D4_LN_ISCAN_RESULTS_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D5
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D5(target)    VTSS_IOREG(target,0x1d5)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D5 . LN_ISCAN_RESULTS_47_40
 */
#define  VTSS_F_SD25G_TARGET_LANE_D5_LN_ISCAN_RESULTS_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D5_LN_ISCAN_RESULTS_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D5_LN_ISCAN_RESULTS_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D6
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D6(target)    VTSS_IOREG(target,0x1d6)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D6 . LN_ISCAN_RESULTS_55_48
 */
#define  VTSS_F_SD25G_TARGET_LANE_D6_LN_ISCAN_RESULTS_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D6_LN_ISCAN_RESULTS_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D6_LN_ISCAN_RESULTS_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D7
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D7(target)    VTSS_IOREG(target,0x1d7)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D7 . LN_ISCAN_RESULTS_63_56
 */
#define  VTSS_F_SD25G_TARGET_LANE_D7_LN_ISCAN_RESULTS_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_D7_LN_ISCAN_RESULTS_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_D7_LN_ISCAN_RESULTS_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D8
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D8(target)    VTSS_IOREG(target,0x1d8)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D8 . LN_ISCAN_RESULTS_64
 */
#define  VTSS_F_SD25G_TARGET_LANE_D8_LN_ISCAN_RESULTS_64(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_D8_LN_ISCAN_RESULTS_64  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_D8_LN_ISCAN_RESULTS_64(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_D9
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_D9(target)    VTSS_IOREG(target,0x1d9)

/** 
 * \brief
 * Eye scan result for single point scan
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_D9 . LN_ISCAN_RESULT
 */
#define  VTSS_F_SD25G_TARGET_LANE_D9_LN_ISCAN_RESULT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_D9_LN_ISCAN_RESULT  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_D9_LN_ISCAN_RESULT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_DA
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_DA(target)    VTSS_IOREG(target,0x1da)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DA . LN_ISCAN_VOLT_STAT_6_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_DA_LN_ISCAN_VOLT_STAT_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD25G_TARGET_LANE_DA_LN_ISCAN_VOLT_STAT_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD25G_TARGET_LANE_DA_LN_ISCAN_VOLT_STAT_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_DB
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_DB(target)    VTSS_IOREG(target,0x1db)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DB . LN_ISCAN_ERR_CNT_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_DB_LN_ISCAN_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_DB_LN_ISCAN_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_DB_LN_ISCAN_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_DC
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_DC(target)    VTSS_IOREG(target,0x1dc)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DC . LN_ISCAN_ERR_CNT_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_DC_LN_ISCAN_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_DC_LN_ISCAN_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_DC_LN_ISCAN_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_DD
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_DD(target)    VTSS_IOREG(target,0x1dd)

/** 
 * \brief
 * Eye scan complete
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DD . LN_ISCAN_DONE
 */
#define  VTSS_F_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Read back RXEQ"C"code
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DD . LN_EQC_CODE_3_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_DD_LN_EQC_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD25G_TARGET_LANE_DD_LN_EQC_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD25G_TARGET_LANE_DD_LN_EQC_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_1:LANE_DE
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_DE(target)    VTSS_IOREG(target,0x1de)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DE . LN_LOL_UDL
 */
#define  VTSS_F_SD25G_TARGET_LANE_DE_LN_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_DE_LN_LOL_UDL  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_DE_LN_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DE . LN_LOL
 */
#define  VTSS_F_SD25G_TARGET_LANE_DE_LN_LOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_DE_LN_LOL   VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_DE_LN_LOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DE . LN_PMA2PCS_RXEI_FILTERED
 */
#define  VTSS_F_SD25G_TARGET_LANE_DE_LN_PMA2PCS_RXEI_FILTERED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_DE_LN_PMA2PCS_RXEI_FILTERED  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_DE_LN_PMA2PCS_RXEI_FILTERED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_DE . LN_PMA_RXEI
 */
#define  VTSS_F_SD25G_TARGET_LANE_DE_LN_PMA_RXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_DE_LN_PMA_RXEI  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_DE_LN_PMA_RXEI(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * Register Group: \a SD25G_TARGET:LANE_GRP_2
 *
 * Register group for registers 0xE0 to 0xE4
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_2:LANE_E0
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_E0(target)    VTSS_IOREG(target,0x1e0)

/** 
 * \brief
 * BIST is active.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E0 . LN_BIST_RUN
 */
#define  VTSS_F_SD25G_TARGET_LANE_E0_LN_BIST_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_TARGET_LANE_E0_LN_BIST_RUN  VTSS_BIT(0)
#define  VTSS_X_SD25G_TARGET_LANE_E0_LN_BIST_RUN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * BIST is ok.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E0 . LN_BIST_OK
 */
#define  VTSS_F_SD25G_TARGET_LANE_E0_LN_BIST_OK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_TARGET_LANE_E0_LN_BIST_OK  VTSS_BIT(1)
#define  VTSS_X_SD25G_TARGET_LANE_E0_LN_BIST_OK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST is error.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E0 . LN_BIST_ERR
 */
#define  VTSS_F_SD25G_TARGET_LANE_E0_LN_BIST_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_TARGET_LANE_E0_LN_BIST_ERR  VTSS_BIT(2)
#define  VTSS_X_SD25G_TARGET_LANE_E0_LN_BIST_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The bist time is time out.Bist time = (data width/bit rate)
 * *1024*r_bist_timer
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E0 . LN_BIST_DONE
 */
#define  VTSS_F_SD25G_TARGET_LANE_E0_LN_BIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD25G_TARGET_LANE_E0_LN_BIST_DONE  VTSS_BIT(3)
#define  VTSS_X_SD25G_TARGET_LANE_E0_LN_BIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_2:LANE_E1
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_E1(target)    VTSS_IOREG(target,0x1e1)

/** 
 * \brief
 * BIST Error counter.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E1 . LN_BIST_ERR_CNT_7_0
 */
#define  VTSS_F_SD25G_TARGET_LANE_E1_LN_BIST_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_E1_LN_BIST_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_E1_LN_BIST_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_2:LANE_E2
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_E2(target)    VTSS_IOREG(target,0x1e2)

/** 
 * \brief
 * BIST Error counter.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E2 . LN_BIST_ERR_CNT_15_8
 */
#define  VTSS_F_SD25G_TARGET_LANE_E2_LN_BIST_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_E2_LN_BIST_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_E2_LN_BIST_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_2:LANE_E3
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_E3(target)    VTSS_IOREG(target,0x1e3)

/** 
 * \brief
 * BIST Error counter.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E3 . LN_BIST_ERR_CNT_23_16
 */
#define  VTSS_F_SD25G_TARGET_LANE_E3_LN_BIST_ERR_CNT_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_E3_LN_BIST_ERR_CNT_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_E3_LN_BIST_ERR_CNT_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD25G_TARGET:LANE_GRP_2:LANE_E4
 *
 * @param target A \a ::vtss_target_SD25G_TARGET_e target
 */
#define VTSS_SD25G_TARGET_LANE_E4(target)    VTSS_IOREG(target,0x1e4)

/** 
 * \brief
 * BIST Error counter.
 *
 * \details 
 * Field: ::VTSS_SD25G_TARGET_LANE_E4 . LN_BIST_ERR_CNT_31_24
 */
#define  VTSS_F_SD25G_TARGET_LANE_E4_LN_BIST_ERR_CNT_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD25G_TARGET_LANE_E4_LN_BIST_ERR_CNT_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD25G_TARGET_LANE_E4_LN_BIST_ERR_CNT_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_FA_REGS_SD25G_TARGET_H_ */
