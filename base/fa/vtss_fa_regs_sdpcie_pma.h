// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_SDPCIE_PMA_H_
#define _VTSS_FA_REGS_SDPCIE_PMA_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a SDPCIE_PMA
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_0
 *
 * Register group for register 0x00
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_0:PMA_CMU_00
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_00           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x0)

/** 
 * \brief
 * Simulation speed up mode enable.0: no speed up.1: speed up. Note loss of
 * lock related functions will not be speed up.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_00 . R_HWT_SIMULATION_MODE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_00_R_HWT_SIMULATION_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_00_R_HWT_SIMULATION_MODE  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_00_R_HWT_SIMULATION_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_00 . CFG_PLL_LOL_SET
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOL_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOL_SET  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOL_SET(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_00 . CFG_PLL_LOS_SET
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOS_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOS_SET  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_LOS_SET(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_00 . CFG_PLL_TP_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_00_CFG_PLL_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_1
 *
 * Register group for registers 0x05 to 0x15
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_05
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_05           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x5)

/** 
 * \brief
 * 1: enable reference clock buffer.0: power down reference clock buffer.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_05 . CFG_REFCK_TERM_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_05_CFG_REFCK_TERM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_05_CFG_REFCK_TERM_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_05_CFG_REFCK_TERM_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_05 . CFG_BIAS_TP_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_05_CFG_BIAS_TP_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_05_CFG_BIAS_TP_SEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_05_CFG_BIAS_TP_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_06
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_06           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_DISLOS
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOS  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_DISLOL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOL  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_DISLOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_DCLOL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_DCLOL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_DCLOL  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_DCLOL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_FORCE_RX_FILT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_FORCE_RX_FILT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_FORCE_RX_FILT  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_FORCE_RX_FILT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_CTRL_LOGIC_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_CTRL_LOGIC_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_CTRL_LOGIC_PD  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_CTRL_LOGIC_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_VCO_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_PD  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_PD(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_VCO_CAL_RESETN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_RESETN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_RESETN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_RESETN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_06 . CFG_VCO_CAL_BYP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_BYP  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_06_CFG_VCO_CAL_BYP(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_07
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_07           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x7)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_07 . CFG_VCO_BYP_CTUNE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_BYP_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_BYP_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_07 . CFG_VCO_START_CODE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_START_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_START_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_07_CFG_VCO_START_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_08
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_08           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x8)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_08 . CFG_VFILT2PAD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_08_CFG_VFILT2PAD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_08_CFG_VFILT2PAD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_08_CFG_VFILT2PAD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_08 . CFG_EN_DUMMY
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_08_CFG_EN_DUMMY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_08_CFG_EN_DUMMY  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_08_CFG_EN_DUMMY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_08 . CFG_CK_TREE_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_08_CFG_CK_TREE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_08_CFG_CK_TREE_PD  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_08_CFG_CK_TREE_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_08 . CFG_RST_TREE_PD_MAN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_08 . CFG_RST_TREE_PD_MAN_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_08_CFG_RST_TREE_PD_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_09
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_09           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x9)

/** 
 * \brief
 * 1: enable PLL clock output buffers to the right hand side of common
 * block. PLL clock will output to the right at upper set of clock routing
 * in TX/RX lane.0: disable PLL clock output buffers to the right.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_09 . CFG_EN_TX_CK_UP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_UP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_UP  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_UP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1: enable PLL clock output buffers to the left hand side of common
 * block. PLL clock will output to the left at lower set of clock routing
 * in TX/RX lane.0: disable PLL clock output buffers to the left.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_09 . CFG_EN_TX_CK_DN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_DN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_DN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_09_CFG_EN_TX_CK_DN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * For PCIe Gen1, Gen2, , cfg_sw_8g=1For other rate, cfg_sw_8g=0 if no
 * specified.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_09 . CFG_SW_8G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_09_CFG_SW_8G(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_09_CFG_SW_8G  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_09_CFG_SW_8G(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * For PCIe Gen1, Gen2 , cfg_sw_10g=1For other rate, cfg_sw_10g=0 if no
 * specified.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_09 . CFG_SW_10G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_09_CFG_SW_10G(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_09_CFG_SW_10G  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_09_CFG_SW_10G(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0A
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0A           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xa)

/** 
 * \brief
 * VCO sub-rate divided ratio.000: /1001: /2001: /2011: /8
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0A . CFG_VCO_DIV_MODE_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0A_CFG_VCO_DIV_MODE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0A_CFG_VCO_DIV_MODE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0A_CFG_VCO_DIV_MODE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0B
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0B           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xb)

/** 
 * \brief
 * VCO bias current setting.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0B . CFG_I_VCO_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0B_CFG_I_VCO_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0B_CFG_I_VCO_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0B_CFG_I_VCO_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Charge pump base current coarse-tune.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0B . CFG_ICP_BASE_SEL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0B_CFG_ICP_BASE_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0B_CFG_ICP_BASE_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0B_CFG_ICP_BASE_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0C
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0C           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xc)

/** 
 * \brief
 * Charge pump current fine-tune.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0C . CFG_ICP_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0C_CFG_ICP_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0C_CFG_ICP_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0C_CFG_ICP_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0C . CFG_RSEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0C_CFG_RSEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0C_CFG_RSEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0C_CFG_RSEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0D
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0D           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xd)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0D . CFG_PD_DIV64
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV64(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV64  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV64(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0D . CFG_PD_DIV66
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV66(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV66  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0D_CFG_PD_DIV66(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0D . CFG_PMA_TX_CK_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0D_CFG_PMA_TX_CK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0D_CFG_PMA_TX_CK_PD  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0D_CFG_PMA_TX_CK_PD(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0D . CFG_JC_BYP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0D_CFG_JC_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0D_CFG_JC_BYP  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0D_CFG_JC_BYP(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0D . CFG_REFCK_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0D_CFG_REFCK_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0D_CFG_REFCK_PD  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0D_CFG_REFCK_PD(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0E
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0E           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xe)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0E . CFG_IPLL_DN_RESETB_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0E . CFG_IPLL_DN_TREE_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0E_CFG_IPLL_DN_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_0F
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_0F           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xf)

/** 
 * \brief
 * Fine tune bias current for refclk ssc PI.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0F . CFG_IPLL_UP_RESETB_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Fine tune the swing of ssc refclk swing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_0F . CFG_IPLL_UP_TREE_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_0F_CFG_IPLL_UP_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_10
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_10           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10)

/** 
 * \brief
 * Fine tune the swing of pll distributed clock.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_10 . CFG_IPLL_RESETB_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_RESETB_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_RESETB_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_10 . CFG_IPLL_TREE_BASE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_TREE_BASE(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_TREE_BASE     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_10_CFG_IPLL_TREE_BASE(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_11
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_11           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11)

/** 
 * \brief
 * Fine tune swing of PLL clock buffer.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_11 . CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_11_CFG_IPLL_IC500U_CLOCK_TREE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_12
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_12           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_12 . CFG_ITX_VC_DRIVER_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_DRIVER_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_DRIVER_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_12 . CFG_ITX_VC_BUF_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_BUF_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_BUF_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_12_CFG_ITX_VC_BUF_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_13
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_13           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13)

/** 
 * \brief
 * reference current/voltage fine-tune control. +/- 2.5% increase/decrease
 * code per step.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_13 . CFG_IBIAS_VC_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_13_CFG_IBIAS_VC_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_13_CFG_IBIAS_VC_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_13_CFG_IBIAS_VC_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_14
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_14           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_14 . CFG_IBIAS_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_PD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_14 . CFG_IBIAS_EN_EXTVBG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_EN_EXTVBG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_EN_EXTVBG  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_14_CFG_IBIAS_EN_EXTVBG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_1:PMA_CMU_15
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_15           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15)

/** 
 * \brief
 * PLL multiplying factor(Fref*N):000000: 64000001: 66000010: 80000011:
 * 100000100: 120001011: 400001100: 480010100: 240
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_15 . CFG_SEL_DIV_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_15_CFG_SEL_DIV_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_15_CFG_SEL_DIV_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_15_CFG_SEL_DIV_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_2
 *
 * Register group for register 0x17
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_2:PMA_CMU_17
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_17           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_17 . CFG_VC_REFP_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFP_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFP_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFP_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_17 . CFG_VC_REFN_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFN_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFN_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_17_CFG_VC_REFN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_3
 *
 * Register group for registers 0x1A to 0x1C
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_3:PMA_CMU_1A
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_1A           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a)

/** 
 * \brief
 * REFCLKP/REFCLKN termination resistor enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1A . CFG_REFCK_R_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1A_CFG_REFCK_R_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1A_CFG_REFCK_R_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1A_CFG_REFCK_R_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_3:PMA_CMU_1B
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_1B           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1B . CFG_RESERVE_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1B_CFG_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1B_CFG_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1B_CFG_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_3:PMA_CMU_1C
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_1C           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1C . CFG_RESERVE_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1C_CFG_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1C_CFG_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1C_CFG_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_4
 *
 * Register group for registers 0x1F to 0x26
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_1F
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_1F           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f)

/** 
 * \brief
 * Enable BG bias current source (20 lines) from common block to the left
 * hand side of TX/RX lane. Enable the desired current source from one
 * common block only. If more than 1 common block are used and both enabled
 * for this bit, bias current will be almost twice to the TX/RX lane which
 * will cause function improperly.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1F . CFG_BIAS_DN_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_DN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_DN_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_DN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable BG bias current source (20 lines) from common block to the right
 * hand side of TX/RX lane. Enable the desired current source from one
 * common block only. If more than 1 common block are used and both enabled
 * for this bit, bias current will be almost twice to the TX/RX lane which
 * will cause function improperly.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1F . CFG_BIAS_UP_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_UP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_UP_EN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1F_CFG_BIAS_UP_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 0: All bias are reference to internal BG resistor.1: Some bias currents
 * are reference to external 10K BG resistor.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1F . CFG_IC2IP_N
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1F_CFG_IC2IP_N(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1F_CFG_IC2IP_N  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1F_CFG_IC2IP_N(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_1F . CFG_VTUNE_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_1F_CFG_VTUNE_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_1F_CFG_VTUNE_SEL  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_1F_CFG_VTUNE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_20
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_20           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x20)

/** 
 * \brief
 * For TX lane to lane skew requirement, if more than 5 lanes in one side
 * of CMU to share the same TX clock transmission line, then insert common
 * block in between and activate TX clock buffer/repeater inside this
 * common block with this bit set to '1'. Refer to
 * 'IGPSERT18A_configuration_application_note.docx'
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_20 . CFG_LINK_BUF_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_20_CFG_LINK_BUF_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_20_CFG_LINK_BUF_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_20_CFG_LINK_BUF_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_21
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_21           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x21)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_21 . CFG_REFCK_BCNTMAXVAL_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_21_CFG_REFCK_BCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_22
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_22           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x22)

/** 
 * \brief
 * Refclk ssc enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_22 . CFG_REFCK_SSC_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_22 . CFG_REFCK_CENTER_SPREADING
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_CENTER_SPREADING(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_CENTER_SPREADING  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_CENTER_SPREADING(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_22 . CFG_REFCK_SSC_RTL_CLK_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RTL_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_22 . CFG_REFCK_SSC_RESETB
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RESETB  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_22_CFG_REFCK_SSC_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_23
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_23           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x23)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_23 . CFG_REFCK_MCNTMAXVAL_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_23_CFG_REFCK_MCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_24
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_24           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x24)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_24 . CFG_REFCK_NCNTMAXVAL_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_24_CFG_REFCK_NCNTMAXVAL_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_25
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_25           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x25)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_25 . CFG_REFCK_NCNTMAXVAL_10_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_25_CFG_REFCK_NCNTMAXVAL_10_8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_4:PMA_CMU_26
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_26           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x26)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_26 . CFG_REFCK_SSC_PI_BW_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_BW_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_BW_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_BW_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_26 . CFG_REFCK_SSC_PI_STEP_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_26_CFG_REFCK_SSC_PI_STEP_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_5
 *
 * Register group for registers 0x30 to 0x38
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_30
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_30           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x30)

/** 
 * \brief
 * PLL lol (loss of lock) status output enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_30 . R_PLL_DLOL_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_30_R_PLL_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_30_R_PLL_DLOL_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_30_R_PLL_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_31
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_31           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x31)

/** 
 * \brief
 * PLL loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_31 . R_PLL_LOL_DEASSERT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_31_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_31_R_PLL_LOL_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_31_R_PLL_LOL_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_32
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_32           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x32)

/** 
 * \brief
 * PLL loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_32 . R_PLL_LOL_DEASSERT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_32_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_32_R_PLL_LOL_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_32_R_PLL_LOL_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_33
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_33           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x33)

/** 
 * \brief
 * PLL loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_33 . R_PLL_LOL_ASSERT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_33_R_PLL_LOL_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_33_R_PLL_LOL_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_33_R_PLL_LOL_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_34
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_34           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x34)

/** 
 * \brief
 * PLL loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_34 . R_PLL_LOL_ASSERT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_34_R_PLL_LOL_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_34_R_PLL_LOL_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_34_R_PLL_LOL_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_35
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_35           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x35)

/** 
 * \brief
 * PLL loss of lock deassert dppm control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_35 . R_PLL_LOL_DF1_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_35_R_PLL_LOL_DF1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_35_R_PLL_LOL_DF1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_35_R_PLL_LOL_DF1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_36
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_36           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x36)

/** 
 * \brief
 * PLL loss of lock deassert dppm control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_36 . R_PLL_LOL_DF1_9_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_36_R_PLL_LOL_DF1_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_36_R_PLL_LOL_DF1_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_36_R_PLL_LOL_DF1_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_37
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_37           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x37)

/** 
 * \brief
 * PLL loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_37 . R_PLL_LOL_DF2_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_37_R_PLL_LOL_DF2_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_37_R_PLL_LOL_DF2_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_37_R_PLL_LOL_DF2_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_5:PMA_CMU_38
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_38           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x38)

/** 
 * \brief
 * PLL loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_38 . R_PLL_LOL_DF2_9_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_38_R_PLL_LOL_DF2_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_38_R_PLL_LOL_DF2_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_38_R_PLL_LOL_DF2_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_6
 *
 * Register group for registers 0x40 to 0x57
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_40
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_40           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x40)

/** 
 * \brief
 * T1 in Figure 3.2-1 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_40 . R_TIME_PLL2CKB_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_40_R_TIME_PLL2CKB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_40_R_TIME_PLL2CKB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_40_R_TIME_PLL2CKB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_41
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_41           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x41)

/** 
 * \brief
 * T1 = r_time_pll2ckb * 8t
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_41 . R_TIME_PLL2CKB_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_41_R_TIME_PLL2CKB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_41_R_TIME_PLL2CKB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_41_R_TIME_PLL2CKB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_42
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_42           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x42)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_42 . R_LOL_RESET
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_42_R_LOL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_42_R_LOL_RESET  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_42_R_LOL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * VCO pre-calibration0 : No VCO pre-calibration1 : Run the VCO
 * pre-calibration.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_42 . R_EN_PRE_CAL_VCO
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_42_R_EN_PRE_CAL_VCO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_42_R_EN_PRE_CAL_VCO  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_42_R_EN_PRE_CAL_VCO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Selection for T1 in Figure 3.2-1 if the power state is changed.0 : T1 =
 * r_time_pllckb*8t1 : T1 = r_time_pll2ckb_pwrchg*8t
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_42 . R_AUTO_PWRCHG_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_42_R_AUTO_PWRCHG_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_42_R_AUTO_PWRCHG_EN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_42_R_AUTO_PWRCHG_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Mask of resetn to PLL.0 : PLL will not be reset.1 : PLL can be reset by
 * reset sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_42 . R_MASK_PLL_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_42_R_MASK_PLL_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_42_R_MASK_PLL_RSTN  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_42_R_MASK_PLL_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_43
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_43           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x43)

/** 
 * \brief
 * T0 in Figure 3.2-1 (reset scheme).T0 = r_time_pweron2pll[5:0]* 1T
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_43 . R_TIME_PWRON2PLL_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_43_R_TIME_PWRON2PLL_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_43_R_TIME_PWRON2PLL_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_43_R_TIME_PWRON2PLL_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_44
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_44           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x44)

/** 
 * \brief
 * Reset signal for pll,low active.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_44 . R_PLL_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_44_R_PLL_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_44_R_PLL_RSTN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_44_R_PLL_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_44 . R_CK_RESETB
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_44_R_CK_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_44_R_CK_RESETB  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_44_R_CK_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_45
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_45           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x45)

/** 
 * \brief
 * 0 : Legacy mode1 : PCI-E auto detction 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_EN_RATECHG_CTRL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_EN_RATECHG_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_EN_RATECHG_CTRL  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_EN_RATECHG_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Data width/data rate/termination resistor of reference clock control
 * from register or hardware pin.0: cfg control 1:
 * pcs2pma_phymode[[4:0],hwt_cfg_sel_div[4:0]hwt_vco_sel_div[2:0]hwt_refck_
 * r_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_DWIDTHCTRL_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_DWIDTHCTRL_FROM_HWT  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . RESERVED
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_RESERVED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_RESERVED  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_RESERVED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The source of SSC control signals  selection0 : configuration register1
 * : configuration from
 * pinshwt_refck_ssc_en,hwt_refck_ssc_resetbhwt_refck_center_spreadinghwt_r
 * efck_mcntMaxVal[4:0]hwt_refck_ncntMaxVal[10:0]hwt_refck_ssc_pi_bw[2:0]hw
 * t_refck_ssc_pi_step[1:0]hwt_refck_ssc_rtl_clk_sel
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_REFCK_SSC_EN_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_REFCK_SSC_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_REFCK_SSC_EN_FROM_HWT  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_REFCK_SSC_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . RESERVED_2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_RESERVED_2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_RESERVED_2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_RESERVED_2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The source of link_buf_en selection0 : configuration register1 :
 * hwt_link_buf_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_LINK_BUF_EN_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_LINK_BUF_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_LINK_BUF_EN_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_LINK_BUF_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * The source of cfg_bias_dn_en/ cfg_bias_dn_en selection0 : configuration
 * register1 : hwt_bias_dn_en / hwt_bias_up_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_BIAS_EN_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_BIAS_EN_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_BIAS_EN_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_BIAS_EN_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Reset tree buffer power down control selection.0 : Configuration
 * registers1 : internal circuit.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_45 . R_AUTO_RST_TREE_PD_MAN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_45_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_45_R_AUTO_RST_TREE_PD_MAN  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_45_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_46
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_46           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x46)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_46 . R_DBG_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_46_R_DBG_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_46_R_DBG_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_46_R_DBG_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * The source of power control related signals.0 : configuration register1
 * :
 * hwt_refck_term_enhwt_ctrl_logic_pdhwt_vco_pdhwt_ck_tree_pdhwt_en_tx_ck_u
 * phwt_en_tx_ck_dnhwt_pd_div66hwt_pd_div64hwt_pma_tx_ck_pdhwt_ibias_pdhwt_
 * refck_pdhwt_en_dummy
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_46 . R_PWR_CTRL_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_46_R_PWR_CTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_46_R_PWR_CTRL_FROM_HWT  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_46_R_PWR_CTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * sel_div[5:0] selection0 : hwt_cfg_sel[5:0] or  cfg_sel_div[5:0] depend
 * on the r_DwidthCtrl_from_hwt1 : preset setting depend on the
 * pcs2pma_phymode
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_46 . R_EN_RATECHG_CTRL_SEL_DIV
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_46_R_EN_RATECHG_CTRL_SEL_DIV(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_46_R_EN_RATECHG_CTRL_SEL_DIV  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_46_R_EN_RATECHG_CTRL_SEL_DIV(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_47
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_47           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x47)

/** 
 * \brief
 * SATA/SAS : 5'b00_100PCIE Gen1/2 : 5'b00_011PCIE Gen3 : 5'b00_010(8G-12G
 * VCO)PCIE Gen3 : 5'b10_010(16G VCO)PCIE Gen4 : 5'b10_010DP mode Gen1 :
 * 5'b01_000DP mode Gen2 : 5'b01_001DP mode Gen3 : 5'b01_010DP mode Gen4 :
 * 5'b01_011Others : 5'b00_000
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_47 . R_PCS2PMA_PHYMODE_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_47_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_47_R_PCS2PMA_PHYMODE_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_47_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_48
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_48           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x48)

/** 
 * \brief
 * Preset cfg_sel_div[5:0] for PCIE Gen1/Gen2 , SATA/SAS or DP Gen1
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_48 . R_GEN12_SEL_DIV_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_48_R_GEN12_SEL_DIV_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_48_R_GEN12_SEL_DIV_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_48_R_GEN12_SEL_DIV_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_49
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_49           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x49)

/** 
 * \brief
 * Preset cfg_sel_div[5:0] for PCIE Gen3/Gen4 or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_49 . R_GEN34_SEL_DIV_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_49_R_GEN34_SEL_DIV_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_49_R_GEN34_SEL_DIV_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_49_R_GEN34_SEL_DIV_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4A
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4A           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4a)

/** 
 * \brief
 * Preset sw_8g for PCIE Gen1/Gen2, SATA/SAS or DP Gen1
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4A . R_SW_8G_GEN12
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN12(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN12  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN12(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Preset sw_10g for PCIE Gen1/Gen2, SATA/SAS or DP Gen1
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4A . R_SW_10G_GEN12
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN12(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN12  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN12(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Preset sw_8g for PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4A . R_SW_8G_GEN34
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN34(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN34  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4A_R_SW_8G_GEN34(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset sw_10g for PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4A . R_SW_10G_GEN34
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN34(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN34  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4A_R_SW_10G_GEN34(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4B
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4B           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4b)

/** 
 * \brief
 * T1 in Figure 3.2-1. Refer to the description of r_auto_pwrchg_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4B . R_TIME_PLL2CKB_PWRCHG_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4B_R_TIME_PLL2CKB_PWRCHG_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4B_R_TIME_PLL2CKB_PWRCHG_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4B_R_TIME_PLL2CKB_PWRCHG_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4C
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4C           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4c)

/** 
 * \brief
 * T1 in Figure 3.2-1. Refer to the description of r_auto_pwrchg_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4C . R_TIME_PLL2CKB_PWRCHG_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4C_R_TIME_PLL2CKB_PWRCHG_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4C_R_TIME_PLL2CKB_PWRCHG_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4C_R_TIME_PLL2CKB_PWRCHG_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4D
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4D           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4d)

/** 
 * \brief
 * Preset cfg_i_vco[3:0] for the PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4D . CFG_I_VCO_GEN34_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4D_CFG_I_VCO_GEN34_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4D_CFG_I_VCO_GEN34_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4D_CFG_I_VCO_GEN34_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset cfg_icp_sel[3:0] for the PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4D . CFG_ICP_SEL_GEN34_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4D_CFG_ICP_SEL_GEN34_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4D_CFG_ICP_SEL_GEN34_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4D_CFG_ICP_SEL_GEN34_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4E
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4E           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4e)

/** 
 * \brief
 * Preset cfg_icp_base_sel[3:0] for the PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4E . CFG_ICP_BASE_SEL_GEN34_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4E_CFG_ICP_BASE_SEL_GEN34_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4E_CFG_ICP_BASE_SEL_GEN34_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4E_CFG_ICP_BASE_SEL_GEN34_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset cfg_rsel_gen[2:0] for the PCIE Gen3/Gen4, SATA/SAS or DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4E . CFG_RSEL_GEN34_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4E_CFG_RSEL_GEN34_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4E_CFG_RSEL_GEN34_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4E_CFG_RSEL_GEN34_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_4F
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_4F           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x4f)

/** 
 * \brief
 * Preset cfg_sel_div[5:0] for DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_4F . R_DP_GEN3_SEL_DIV_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_4F_R_DP_GEN3_SEL_DIV_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_4F_R_DP_GEN3_SEL_DIV_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_4F_R_DP_GEN3_SEL_DIV_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_50
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_50           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x50)

/** 
 * \brief
 * Preset cfg_sel_div[5:0] for DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_50 . R_DP_GEN2_SEL_DIV_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_50_R_DP_GEN2_SEL_DIV_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_50_R_DP_GEN2_SEL_DIV_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_50_R_DP_GEN2_SEL_DIV_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_51
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_51           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x51)

/** 
 * \brief
 * Preset sw_8g for DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_51 . R_DP_GEN3_SW_8G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_8G(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_8G  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_8G(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Preset sw_8g for DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_51 . R_DP_GEN2_SW_8G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_8G(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_8G  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_8G(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Preset sw_10g for DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_51 . R_DP_GEN3_SW_10G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_10G(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_10G  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN3_SW_10G(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset sw_10g for DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_51 . R_DP_GEN2_SW_10G
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_10G(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_10G  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_51_R_DP_GEN2_SW_10G(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_52
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_52           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x52)

/** 
 * \brief
 * Preset cfg_i_vco[3:0] for the DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_52 . R_DP_GEN3_I_VCO_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN3_I_VCO_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN3_I_VCO_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN3_I_VCO_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset cfg_i_vco[3:0] for the DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_52 . R_DP_GEN2_I_VCO_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN2_I_VCO_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN2_I_VCO_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_52_R_DP_GEN2_I_VCO_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_53
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_53           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x53)

/** 
 * \brief
 * Preset cfg_icp_sel[2:0] for the DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_53 . R_DP_GEN3_ICP_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN3_ICP_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN3_ICP_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN3_ICP_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Preset cfg_icp_sel[2:0] for the DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_53 . R_DP_GEN2_ICP_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN2_ICP_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN2_ICP_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_53_R_DP_GEN2_ICP_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_54
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_54           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x54)

/** 
 * \brief
 * Preset cfg_icp_base_sel[3:0] for the DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_54 . R_DP_GEN3_ICP_BASE_SEL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN3_ICP_BASE_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN3_ICP_BASE_SEL_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN3_ICP_BASE_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset cfg_icp_base_sel[3:0] for the DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_54 . R_DP_GEN2_ICP_BASE_SEL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN2_ICP_BASE_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN2_ICP_BASE_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_54_R_DP_GEN2_ICP_BASE_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_55
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_55           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x55)

/** 
 * \brief
 * Preset cfg_rsel_sel[2:0] for the DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_55 . R_DP_GEN3_RSEL_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN3_RSEL_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN3_RSEL_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN3_RSEL_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Preset cfg_rsel_sel[2:0] for the DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_55 . R_DP_GEN2_RSEL_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN2_RSEL_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN2_RSEL_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_55_R_DP_GEN2_RSEL_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_56
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_56           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x56)

/** 
 * \brief
 * Preset vco_start_code for the DP Gen2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_56 . CFG_VCO_START_CODE_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset vco_start_code for the DP Gen3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_56 . CFG_VCO_START_CODE_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_56_CFG_VCO_START_CODE_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_6:PMA_CMU_57
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_57           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x57)

/** 
 * \brief
 * Preset vco_start_code for the DP Gen4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_57 . CFG_VCO_START_CODE_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_57_CFG_VCO_START_CODE_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_57_CFG_VCO_START_CODE_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_57_CFG_VCO_START_CODE_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_7
 *
 * Register group for registers 0xE0 to 0xE3
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_7:PMA_CMU_E0
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_E0           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xe0)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E0 . READ_VCO_CTUNE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E0_READ_VCO_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E0_READ_VCO_CTUNE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E0_READ_VCO_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Loss of lock of PLL
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E0 . PLL_LOL_UDL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E0_PLL_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E0_PLL_LOL_UDL  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E0_PLL_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_7:PMA_CMU_E1
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_E1           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xe1)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E1 . CFG_COMMON_STATUS_RESERVE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E1_CFG_COMMON_STATUS_RESERVE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_7:PMA_CMU_E2
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_E2           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xe2)

/** 
 * \brief
 * Valid if r_en_pre_cal_vco =10 : vco pre-calibration is on go-ing.1 : vco
 * pre-calibration is done.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E2 . VCO_CAL_DONE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E2_VCO_CAL_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E2_VCO_CAL_DONE  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E2_VCO_CAL_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Valid if r_en_pre_cal_vco =1Current vco code.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E2 . AUTO_VCO_BYP_CTUNE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E2_AUTO_VCO_BYP_CTUNE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E2_AUTO_VCO_BYP_CTUNE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E2_AUTO_VCO_BYP_CTUNE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_7:PMA_CMU_E3
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_E3           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xe3)

/** 
 * \brief
 * Valid if r_en_pre_cal_vco =1Pre-calibrated  vco code of PCI-E Gen1/Gen2.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E3 . GEN12_VCO_CTUNE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E3_GEN12_VCO_CTUNE(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E3_GEN12_VCO_CTUNE     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E3_GEN12_VCO_CTUNE(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Valid if r_en_pre_cal_vco =1Pre-calibrated  vco code of PCI-E Gen3/Gen4.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_E3 . GEN34_VCO_CTUNE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_E3_GEN34_VCO_CTUNE(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_E3_GEN34_VCO_CTUNE     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_E3_GEN34_VCO_CTUNE(x)  VTSS_EXTRACT_BITFIELD(x,4,4)

/**
 * Register Group: \a SDPCIE_PMA:PMA_CMU_GRP_8
 *
 * Register group for register 0xFF
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_CMU_GRP_8:PMA_CMU_FF
 */
#define VTSS_SDPCIE_PMA_PMA_CMU_FF           VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0xff)

/** 
 * \brief
 * This register provides RW access switch between CMU registers , LANE
 * registers through EXT CFG i/f Val 0-CMU access, 1-LANE access
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_CMU_FF . MSCC_PMA_CMU_LANE_ACCESS
 */
#define  VTSS_F_SDPCIE_PMA_PMA_CMU_FF_MSCC_PMA_CMU_LANE_ACCESS(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_CMU_FF_MSCC_PMA_CMU_LANE_ACCESS  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_CMU_FF_MSCC_PMA_CMU_LANE_ACCESS(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SDPCIE_PMA:PMA_LANE_GRP_0
 *
 * Register group for registers 0x00 to 0xE4
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_00
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_00          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x100)

/** 
 * \brief
 * Simulation speed up mode enable.0: no speed up.1: speed up. Note loss of
 * lock related functions will not be speed up.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_00 . R_SIMULATION_MODE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_00_R_SIMULATION_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_00_R_SIMULATION_MODE  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_00_R_SIMULATION_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_01
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_01          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x101)

/** 
 * \brief
 * Refer to hwt_pma_txck_sel[2:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_01 . CFG_PMA_TX_CK_BITWIDTH_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Refer to pcs2pma_txdetrx_en
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_01 . CFG_RXDET_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Refer to pcs2pma_txdetrx_str
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_01 . CFG_RXDET_STR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_STR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_STR  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_01_CFG_RXDET_STR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_02
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_02          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x102)

/** 
 * \brief
 * Enable pre-equalization control of TX.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_02 . CFG_EN_ADV
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_02_CFG_EN_ADV(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_02_CFG_EN_ADV  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_02_CFG_EN_ADV(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Enable TX data path control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_02 . CFG_EN_MAIN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_02_CFG_EN_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_02_CFG_EN_MAIN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_02_CFG_EN_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable 1st stage post-equalization control of TX.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_02 . CFG_EN_DLY
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_02 . CFG_EN_DLY2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY2  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_02_CFG_EN_DLY2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * TX data path setting. Should set to 1.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_02 . CFG_TAP_MAIN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_02_CFG_TAP_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_02_CFG_TAP_MAIN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_02_CFG_TAP_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_03
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_03          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x103)

/** 
 * \brief
 * Pre-equalization level control of TX. Refer to section 2.6.2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_03 . CFG_TAP_ADV_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_03_CFG_TAP_ADV_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_03_CFG_TAP_ADV_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_03_CFG_TAP_ADV_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_04
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_04          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x104)

/** 
 * \brief
 * 1st stage post-equalization level control of TX. Refer to section 2.6.2.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_04 . CFG_TAP_DLY_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_04_CFG_TAP_DLY_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_04_CFG_TAP_DLY_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_04_CFG_TAP_DLY_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_05
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_05          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x105)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_05 . CFG_TAP_DLY2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_05_CFG_TAP_DLY2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_05_CFG_TAP_DLY2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_05_CFG_TAP_DLY2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_06
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_06          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x106)

/** 
 * \brief
 * Power down control of TX driver to support EEE.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_PD_DRIVER
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_PD_DRIVER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_PD_DRIVER  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_PD_DRIVER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Power down control of PMAA TX clock.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_PD_CLK
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CLK  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CLK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Power down control of PMAA TX serializer block.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_PD_CML
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CML(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CML  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_PD_CML(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * PMAA TX to RX loopback enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_TX2RX_LP_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_TX2RX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_TX2RX_LP_EN  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_TX2RX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * PMAA RX to TX loopback enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_RX2TX_LP_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_RX2TX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_RX2TX_LP_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_RX2TX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_06 . CFG_EN_PREEMPH
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_06_CFG_EN_PREEMPH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_06_CFG_EN_PREEMPH  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_06_CFG_EN_PREEMPH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_07
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_07          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x107)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_07 . CFG_RX_REG_BYP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_BYP  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_BYP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * CTLE regulator enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_07 . CFG_RX_REG_PU
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_PU(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_PU  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_PU(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_07 . CFG_RX_REG_VSEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_VSEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_VSEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_07_CFG_RX_REG_VSEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_08
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_08          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x108)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_08 . CFG_BYP_OC_CLK
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_08_CFG_BYP_OC_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_08_CFG_BYP_OC_CLK  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_08_CFG_BYP_OC_CLK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_08 . CFG_CTLE_NEGC
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_08_CFG_CTLE_NEGC(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_08_CFG_CTLE_NEGC     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_08_CFG_CTLE_NEGC(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_09
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_09          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x109)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_09 . CFG_EN_HYS_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_09_CFG_EN_HYS_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_09_CFG_EN_HYS_SQ  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_09_CFG_EN_HYS_SQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_09 . CFG_IP_RX_LS_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_09_CFG_IP_RX_LS_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_09_CFG_IP_RX_LS_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_09_CFG_IP_RX_LS_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10a)

/** 
 * \brief
 * Refer to hwt_lane_id[2:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0A . CFG_LANE_ID_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0A_CFG_LANE_ID_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0A_CFG_LANE_ID_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0A_CFG_LANE_ID_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0A . CFG_SUM_SETCM_EN_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0A . CFG_SUM_SETCM_EN_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0A . CFG_SUM_SETCM_EN_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0A_CFG_SUM_SETCM_EN_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10b)

/** 
 * \brief
 * CTLE gain control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0B . CFG_EQ_RES_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0B_CFG_EQ_RES_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0B_CFG_EQ_RES_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0B_CFG_EQ_RES_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Power down control of CTLE block.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0B . CFG_PD_CTLE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0B_CFG_PD_CTLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0B_CFG_PD_CTLE  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0B_CFG_PD_CTLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0B . CFG_CTLE_TP_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0B_CFG_CTLE_TP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0B_CFG_CTLE_TP_EN  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0B_CFG_CTLE_TP_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0B . CFG_RESETB_OSCAL_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_AFE  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0B . CFG_RESETB_OSCAL_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_SQ  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0B_CFG_RESETB_OSCAL_SQ(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10c)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_OSCAL_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_AFE  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_AFE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_OSCAL_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_SQ  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_OSCAL_SQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_OSDAC_2X_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_AFE  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_AFE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_OSDAC_2X_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_SQ  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_OSDAC_2X_SQ(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_PD_OSDAC_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_AFE  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_AFE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_PD_OSDAC_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_SQ  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_OSDAC_SQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_PD_RX_LS
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_RX_LS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_RX_LS  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_PD_RX_LS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0C . CFG_RX_PCIE_GEN12
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0C_CFG_RX_PCIE_GEN12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0C_CFG_RX_PCIE_GEN12  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0C_CFG_RX_PCIE_GEN12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10d)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0D . CFG_CTLE_M_THR_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0D_CFG_CTLE_M_THR_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0D_CFG_CTLE_M_THR_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0D_CFG_CTLE_M_THR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0D . CFG_EQR_BYP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0D_CFG_EQR_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0D_CFG_EQR_BYP  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0D_CFG_EQR_BYP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10e)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0E . CFG_EQC_FORCE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0E_CFG_EQC_FORCE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0E_CFG_EQC_FORCE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0E_CFG_EQC_FORCE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * RX to TX loopback enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0E . CFG_RXLB_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0E_CFG_RXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0E_CFG_RXLB_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0E_CFG_RXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * TX to RX loopback enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0E . CFG_TXLB_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0E_CFG_TXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0E_CFG_TXLB_EN  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0E_CFG_TXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0E . CFG_SUM_SETCM_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0E_CFG_SUM_SETCM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0E_CFG_SUM_SETCM_EN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0E_CFG_SUM_SETCM_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_0F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_0F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x10f)

/** 
 * \brief
 * PCIE Gen1 / SATA I / SAS 1.5G/other rate[7:5] : PI bandwidth control,
 * [4:0] : 1st CDR digital low pass filter select.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_0F . R_CDR_M_GEN1_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_0F_R_CDR_M_GEN1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_0F_R_CDR_M_GEN1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_0F_R_CDR_M_GEN1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_10
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_10          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x110)

/** 
 * \brief
 * PCIE Gen2 / SATA II/ SAS 3G[7:5] : PI bandwidth control, [4:0] : 1st CDR
 * digital low pass filter select.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_10 . R_CDR_M_GEN2_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_10_R_CDR_M_GEN2_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_10_R_CDR_M_GEN2_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_10_R_CDR_M_GEN2_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_11
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_11          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x111)

/** 
 * \brief
 * PCIE Gen3 / SATA III/ SAS 6G[7:5] : PI bandwidth control, [4:0] : 1st
 * CDR digital low pass filter select.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_11 . R_CDR_M_GEN3_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_11_R_CDR_M_GEN3_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_11_R_CDR_M_GEN3_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_11_R_CDR_M_GEN3_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_12
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_12          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x112)

/** 
 * \brief
 * SAS 12G[7:5] : PI bandwidth control, [4:0] : 1st CDR digital low pass
 * filter select.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_12 . R_CDR_M_GEN4_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_12_R_CDR_M_GEN4_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_12_R_CDR_M_GEN4_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_12_R_CDR_M_GEN4_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_13
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_13          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x113)

/** 
 * \brief
 * Power down control of CDR path buffer.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_13 . CFG_DCDR_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_13_CFG_DCDR_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_13_CFG_DCDR_PD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_13_CFG_DCDR_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_13 . CFG_PHID_1T
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_13_CFG_PHID_1T(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_13_CFG_PHID_1T  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_13_CFG_PHID_1T(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * CDR Clock enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_13 . CFG_CDRCK_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_13_CFG_CDRCK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_13_CFG_CDRCK_EN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_13_CFG_CDRCK_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_14
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_14          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x114)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_14 . CFG_PI_EXT_DAC_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_14_CFG_PI_EXT_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_14_CFG_PI_EXT_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_14_CFG_PI_EXT_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_15
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_15          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x115)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_15 . CFG_PI_EXT_DAC_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_15_CFG_PI_EXT_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_15_CFG_PI_EXT_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_15_CFG_PI_EXT_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_16
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_16          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x116)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_16 . CFG_PI_EXT_DAC_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_16_CFG_PI_EXT_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_16_CFG_PI_EXT_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_16_CFG_PI_EXT_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_17
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_17          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x117)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_17 . CFG_PI_EXT_DAC_30_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_17_CFG_PI_EXT_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_17_CFG_PI_EXT_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_17_CFG_PI_EXT_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_18
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_18          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x118)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_18 . CFG_PI_EXT_OVR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_OVR  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_18 . CFG_PI_HOLD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_18_CFG_PI_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_18_CFG_PI_HOLD  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_18_CFG_PI_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_18 . CFG_PI_OFFSET_DIR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_DIR  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_DIR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_18 . CFG_PI_OFFSET_SET
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_SET  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_18_CFG_PI_OFFSET_SET(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_18 . CFG_PI_EXT_QRT_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_QRT_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_QRT_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_18_CFG_PI_EXT_QRT_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_19
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_19          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x119)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_19 . CFG_PI_OFFSET_GEN1_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_19_CFG_PI_OFFSET_GEN1_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_19_CFG_PI_OFFSET_GEN1_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_19_CFG_PI_OFFSET_GEN1_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11a)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1A . CFG_PI_R_SCAN_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_R_SCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_R_SCAN_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_R_SCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1A . CFG_PI_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_EN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1A . CFG_PI_DFE_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_DFE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_DFE_EN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_DFE_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1A . CFG_PI_STEPS_GEN1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_STEPS_GEN1(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_STEPS_GEN1  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_STEPS_GEN1(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1A . CFG_PI_FLOOP_STEPS_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_FLOOP_STEPS_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_FLOOP_STEPS_GEN1_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1A_CFG_PI_FLOOP_STEPS_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11b)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_VCM_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_VCM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_VCM_SEL  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_VCM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_HOLD_DFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_HOLD_DFE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_HOLD_DFE  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_HOLD_DFE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_SGN_H1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_SGN_H1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_SGN_H1  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_SGN_H1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_RX_PCIE_GEN12_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_RX_PCIE_GEN12_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1B . CFG_RX_PCIE_GEN12_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1B_CFG_RX_PCIE_GEN12_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11c)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1C . CFG_DFEDIG_BYP_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1C_CFG_DFEDIG_BYP_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1C_CFG_DFEDIG_BYP_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1C_CFG_DFEDIG_BYP_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11d)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1D . CFG_DFE_BYP_H1_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1D_CFG_DFE_BYP_H1_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1D_CFG_DFE_BYP_H1_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1D_CFG_DFE_BYP_H1_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11e)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1E . CFG_DFE_BYP_H2_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1E_CFG_DFE_BYP_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1E_CFG_DFE_BYP_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1E_CFG_DFE_BYP_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_1F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_1F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x11f)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1F . CFG_DFE_BYP_H3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_1F . CFG_DFE_BYP_H4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H4_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_1F_CFG_DFE_BYP_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_20
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_20          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x120)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_20 . CFG_DFE_BYP_H5_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_20_CFG_DFE_BYP_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_20_CFG_DFE_BYP_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_20_CFG_DFE_BYP_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_21
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_21          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x121)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_21 . CFG_DFE_DLEV_6_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_21_CFG_DFE_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_21_CFG_DFE_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_21_CFG_DFE_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_22
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_22          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x122)

/** 
 * \brief
 * Enable signal for DFE tap mux.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_22 . CFG_DFETAP_EN_5_1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_22_CFG_DFETAP_EN_5_1(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_22_CFG_DFETAP_EN_5_1     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_22_CFG_DFETAP_EN_5_1(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_23
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_23          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x123)

/** 
 * \brief
 * Power down control of DFE block.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_23 . CFG_DFE_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_23_CFG_DFE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_23_CFG_DFE_PD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_23_CFG_DFE_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_23 . CFG_EN_DFEDIG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_23_CFG_EN_DFEDIG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_23_CFG_EN_DFEDIG  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_23_CFG_EN_DFEDIG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable signal for DFE clock.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_23 . CFG_DFECK_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_23_CFG_DFECK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_23_CFG_DFECK_EN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_23_CFG_DFECK_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Power down control of error amplifier.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_23 . CFG_ERRAMP_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_23_CFG_ERRAMP_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_23_CFG_ERRAMP_PD  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_23_CFG_ERRAMP_PD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_23 . CFG_DFEDIG_M_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_23_CFG_DFEDIG_M_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_23_CFG_DFEDIG_M_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_23_CFG_DFEDIG_M_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_24
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_24          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x124)

/** 
 * \brief
 * PCIE Gen1 / SATA I / SAS 1.5G/other ratePI bandwidth control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_24 . CFG_PI_BW_GEN1_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN1_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN1_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN1_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * PCIE Gen2 / SATA II / SAS 3GPI bandwidth control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_24 . CFG_PI_BW_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN2_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_24_CFG_PI_BW_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_25
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_25          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x125)

/** 
 * \brief
 * PCIE Gen3 / SATA III / SAS 6GPI bandwidth control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_25 . CFG_PI_BW_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * SAS 12GPI bandwidth control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_25 . CFG_PI_BW_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN4_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_25_CFG_PI_BW_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_26
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_26          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x126)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_26 . CFG_ISCAN_EXT_DAC_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_26_CFG_ISCAN_EXT_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_26_CFG_ISCAN_EXT_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_26_CFG_ISCAN_EXT_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_27
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_27          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x127)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_27 . CFG_ISCAN_EXT_DAC_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_27_CFG_ISCAN_EXT_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_27_CFG_ISCAN_EXT_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_27_CFG_ISCAN_EXT_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_28
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_28          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x128)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_28 . CFG_ISCAN_EXT_DAC_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_28_CFG_ISCAN_EXT_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_28_CFG_ISCAN_EXT_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_28_CFG_ISCAN_EXT_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_29
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_29          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x129)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_29 . CFG_ISCAN_EXT_DAC_30_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_29_CFG_ISCAN_EXT_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_29_CFG_ISCAN_EXT_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_29_CFG_ISCAN_EXT_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12a)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2A . CFG_ISCAN_EXT_OVR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_OVR  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2A . CFG_ISCAN_EXT_QRT_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_QRT_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_QRT_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2A_CFG_ISCAN_EXT_QRT_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12b)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_ISCAN_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * PI usage. Set the signal before pcs_iscan_en is asserted.0 : DFE
 * purpose1 : Eye scan purpose
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_ISCAN_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_SEL  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_ISCAN_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_RSTN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_ISCAN_STEPSIZE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_STEPSIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_STEPSIZE  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_ISCAN_STEPSIZE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Refer to hwt_fom_sel
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_FOM_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_FOM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_FOM_SEL  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_FOM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_ADD_VOLT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_ADD_VOLT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_ADD_VOLT  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_ADD_VOLT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2B . CFG_MAN_VOLT_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2B_CFG_MAN_VOLT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2B_CFG_MAN_VOLT_EN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2B_CFG_MAN_VOLT_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12c)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2C . CFG_COMP_NUM_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2C_CFG_COMP_NUM_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2C_CFG_COMP_NUM_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2C_CFG_COMP_NUM_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2C . CFG_OS_MAN_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2C_CFG_OS_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2C_CFG_OS_MAN_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2C_CFG_OS_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2C . CFG_R_OFFSET_DIR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2C_CFG_R_OFFSET_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2C_CFG_R_OFFSET_DIR  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2C_CFG_R_OFFSET_DIR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12d)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2D . CFG_MAN_VOLT_SEL_6_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2D_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2D_CFG_MAN_VOLT_SEL_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2D_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12e)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2E . CFG_OS_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2E_CFG_OS_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2E_CFG_OS_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2E_CFG_OS_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_2F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_2F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x12f)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2F . CFG_VGA_CP_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CP_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CP_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CP_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_2F . CFG_VGA_CTRL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CTRL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CTRL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_2F_CFG_VGA_CTRL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_30
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_30          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x130)

/** 
 * \brief
 * Enable signal for summer block.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_30 . CFG_SUMMER_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_30_CFG_SUMMER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_30_CFG_SUMMER_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_30_CFG_SUMMER_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Refer to hwt_pma_rxdiv_sel[2:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_30 . CFG_RXDIV_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_30_CFG_RXDIV_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_30_CFG_RXDIV_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_30_CFG_RXDIV_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_31
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_31          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x131)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_PI_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_PI_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_PI_RSTN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_PI_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_CDR_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_CDR_RSTN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_RSTN_DFEDIG_GEN1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DFEDIG_GEN1(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DFEDIG_GEN1  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DFEDIG_GEN1(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_CTLE_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_CTLE_RSTN  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_RSTN_DIV5_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DIV5_8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DIV5_8  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_RSTN_DIV5_8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_31 . CFG_R50_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_31_CFG_R50_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_31_CFG_R50_EN  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_31_CFG_R50_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_32
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_32          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x132)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_32 . CFG_ITX_IPCLK_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCLK_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCLK_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCLK_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * TX predriver curent setting.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_32 . CFG_ITX_IPCML_BASE_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCML_BASE_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCML_BASE_GEN1_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_32_CFG_ITX_IPCML_BASE_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_33
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_33          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x133)

/** 
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_33 . CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_33 . CFG_ITX_IPPREEMP_BASE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_34
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_34          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x134)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_RXTERM_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_RXTERM_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_RXTERM_PD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_RXTERM_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Power down control of analog loss of signal squelch block. 1: power
 * down.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_PD_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_PD_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_PD_SQ  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_PD_SQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_DIS_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_DIS_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_DIS_SQ  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_DIS_SQ(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_HIZ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_HIZ(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_HIZ  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_HIZ(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_EN_DFEDIG_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_EN_DFEDIG_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_34 . CFG_EN_DFEDIG_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_34_CFG_EN_DFEDIG_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_35
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_35          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x135)

/** 
 * \brief
 * Refer to hwt_txrate_sel[1:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_35 . CFG_TXRATE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_35_CFG_TXRATE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_35_CFG_TXRATE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_35_CFG_TXRATE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Refer to hwt_rxrate_sel[1:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_35 . CFG_RXRATE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_35_CFG_RXRATE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_35_CFG_RXRATE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_35_CFG_RXRATE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_36
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_36          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x136)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_36 . CFG_PREDRV_SLEWRATE_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_36_CFG_PREDRV_SLEWRATE_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_36_CFG_PREDRV_SLEWRATE_GEN1_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_36_CFG_PREDRV_SLEWRATE_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_36 . CFG_EID_LP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_36_CFG_EID_LP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_36_CFG_EID_LP  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_36_CFG_EID_LP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_36 . CFG_EN_PREDRV_EMPH
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_36_CFG_EN_PREDRV_EMPH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_36_CFG_EN_PREDRV_EMPH  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_36_CFG_EN_PREDRV_EMPH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_36 . CFG_PRBS_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SEL  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_36 . CFG_PRBS_SETB
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SETB(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SETB  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_36_CFG_PRBS_SETB(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_37
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_37          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x137)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_37 . CFG_RXDET_COMP_PD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_37_CFG_RXDET_COMP_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_37_CFG_RXDET_COMP_PD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_37_CFG_RXDET_COMP_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_37 . CFG_PD_RX_CKTREE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_37_CFG_PD_RX_CKTREE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_37_CFG_PD_RX_CKTREE  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_37_CFG_PD_RX_CKTREE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Refer to pcs2pma_txswing
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_37 . CFG_TXSWING_HALF
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_37_CFG_TXSWING_HALF(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_37_CFG_TXSWING_HALF  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_37_CFG_TXSWING_HALF(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_37 . CFG_IP_PRE_BASE_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_37_CFG_IP_PRE_BASE_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_37_CFG_IP_PRE_BASE_GEN1_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_37_CFG_IP_PRE_BASE_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_38
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_38          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x138)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_38 . CFG_TACC_SEL_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_38_CFG_TACC_SEL_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_38_CFG_TACC_SEL_GEN1_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_38_CFG_TACC_SEL_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * CDR low pass filter threshold z
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_38 . CFG_RXFILT_Z_GEN1_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_38_CFG_RXFILT_Z_GEN1_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_38_CFG_RXFILT_Z_GEN1_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_38_CFG_RXFILT_Z_GEN1_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_39
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_39          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x139)

/** 
 * \brief
 * CDR low pass filter threshold y
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_39 . CFG_RXFILT_Y_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_39_CFG_RXFILT_Y_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_39_CFG_RXFILT_Y_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_39_CFG_RXFILT_Y_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_39 . CFG_RX_SSC_LH_GEN1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_39_CFG_RX_SSC_LH_GEN1(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_39_CFG_RX_SSC_LH_GEN1  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_39_CFG_RX_SSC_LH_GEN1(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13a)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3A . CFG_MP_MIN_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3A . CFG_MP_MAX_GEN1_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MAX_GEN1_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MAX_GEN1_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3A_CFG_MP_MAX_GEN1_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13b)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3B . CFG_MF_MIN_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3B . CFG_MF_MAX_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MAX_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MAX_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3B_CFG_MF_MAX_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13c)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3C . CFG_DIS_ACC
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_ACC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_ACC  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_ACC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 2nd order CDR disable signal.0 : Enable.1 : Disable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3C . CFG_DIS_2NDORDER_GEN1
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_2NDORDER_GEN1(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_2NDORDER_GEN1  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3C_CFG_DIS_2NDORDER_GEN1(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3C . CFG_ISCAN_EXT_DAC_B7_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3C . CFG_ISCAN_EXT_DAC_B7_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3C . CFG_ISCAN_EXT_DAC_B7_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3C_CFG_ISCAN_EXT_DAC_B7_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13d)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3D . CFG_ACC_THR_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3D_CFG_ACC_THR_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3D_CFG_ACC_THR_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3D_CFG_ACC_THR_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13e)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3E . CFG_OC_BYP_CODE_AFE_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3E . CFG_OC_BYP_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_AFE  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3E_CFG_OC_BYP_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_3F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_3F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x13f)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3F . CFG_OC_BYP_CODE_SQ_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_3F . CFG_OC_BYP_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_SQ  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_3F_CFG_OC_BYP_SQ(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_40
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_40          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x140)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_40 . CFG_LANE_RESERVE_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_40_CFG_LANE_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_40_CFG_LANE_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_40_CFG_LANE_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_41
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_41          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x141)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_41 . CFG_LANE_RESERVE_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_41_CFG_LANE_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_41_CFG_LANE_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_41_CFG_LANE_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_42
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_42          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x142)

/** 
 * \brief
 * PCIE Gen1 / SATA I / SAS 1.5G/other rate.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_42 . CFG_CDR_KF_GEN1_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN1_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN1_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN1_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * PCIE Gen2 / SATA II / SAS 3G.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_42 . CFG_CDR_KF_GEN2_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN2_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN2_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_42_CFG_CDR_KF_GEN2_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_43
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_43          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x143)

/** 
 * \brief
 * PCIE Gen3 / SATA III / SAS 6G.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_43 . CFG_CDR_KF_GEN3_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN3_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN3_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN3_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * SAS 12G
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_43 . CFG_CDR_KF_GEN4_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN4_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN4_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_43_CFG_CDR_KF_GEN4_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_44
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_44          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x144)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_44 . CFG_CTLE_NEGC_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN2     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_44 . CFG_CTLE_NEGC_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_44 . CFG_CTLE_NEGC_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_44_CFG_CTLE_NEGC_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_45
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_45          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x145)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_45 . CFG_IP_RX_LS_SEL_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_45 . CFG_IP_RX_LS_SEL_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN3     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_45_CFG_IP_RX_LS_SEL_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_46
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_46          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x146)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_46 . CFG_IP_RX_LS_SEL_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_46_CFG_IP_RX_LS_SEL_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_46_CFG_IP_RX_LS_SEL_GEN4     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_46_CFG_IP_RX_LS_SEL_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_47
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_47          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x147)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_47 . CFG_PI_EXT_DAC_B23TOB22_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN2     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_47 . CFG_PI_EXT_DAC_B23TOB22_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_47 . CFG_PI_EXT_DAC_B23TOB22_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_47_CFG_PI_EXT_DAC_B23TOB22_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_48
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_48          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x148)

/** 
 * \brief
 * voltage threshold for squelch detection.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_48 . CFG_ALOS_THR_GEN1_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_48_CFG_ALOS_THR_GEN1_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_48_CFG_ALOS_THR_GEN1_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_48_CFG_ALOS_THR_GEN1_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Refer to aux_rxck_sel
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_48 . CFG_AUX_RXCK_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_48_CFG_AUX_RXCK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_48_CFG_AUX_RXCK_SEL  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_48_CFG_AUX_RXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_48 . CFG_CLK_ENQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_48_CFG_CLK_ENQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_48_CFG_CLK_ENQ  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_48_CFG_CLK_ENQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_49
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_49          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x149)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_49 . CFG_CROSS_MARGIN_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_49_CFG_CROSS_MARGIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_49_CFG_CROSS_MARGIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_49_CFG_CROSS_MARGIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Fast eye scan method.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_49 . CFG_FIGMERIT_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_49_CFG_FIGMERIT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_49_CFG_FIGMERIT_SEL  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_49_CFG_FIGMERIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14a)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4A . CFG_RX_SP_CTLE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_SP_CTLE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_SP_CTLE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_SP_CTLE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4A . CFG_RX_REG_BYP_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4A . CFG_RX_REG_BYP_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4A . CFG_RX_REG_BYP_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4A_CFG_RX_REG_BYP_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14b)

/** 
 * \brief
 * 0 : SSC down spreading.1 : SSC center spreading.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4B . CFG_CENTER_SPREADING
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4B_CFG_CENTER_SPREADING(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4B_CFG_CENTER_SPREADING  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4B_CFG_CENTER_SPREADING(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14c)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4C . CFG_MCNTMAXVAL_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4C_CFG_MCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4C_CFG_MCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4C_CFG_MCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14d)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4D . CFG_NCNTMAXVAL_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4D_CFG_NCNTMAXVAL_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4D_CFG_NCNTMAXVAL_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4D_CFG_NCNTMAXVAL_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14e)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4E . CFG_NCNTMAXVAL_10_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4E_CFG_NCNTMAXVAL_10_8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4E_CFG_NCNTMAXVAL_10_8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4E_CFG_NCNTMAXVAL_10_8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_4F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_4F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x14f)

/** 
 * \brief
 * 0 : Disable SSC.1 : Enable SSC.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4F . CFG_SSC_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_4F . CFG_SSC_PI_BW_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_PI_BW_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_PI_BW_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_4F_CFG_SSC_PI_BW_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_50
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_50          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x150)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_50 . CFG_SSC_PI_STEP_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_PI_STEP_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_PI_STEP_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_PI_STEP_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Reset signal for SSC (active low)
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_50 . CFG_SSC_RESETB
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RESETB  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_50 . CFG_SSC_RTL_CLK_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RTL_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RTL_CLK_SEL  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_50_CFG_SSC_RTL_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Refer to aux_txck_sel
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_50 . CFG_AUX_TXCK_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_50_CFG_AUX_TXCK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_50_CFG_AUX_TXCK_SEL  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_50_CFG_AUX_TXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_50 . CFG_JT_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_50_CFG_JT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_50_CFG_JT_EN  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_50_CFG_JT_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_51
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_51          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x151)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_51 . CFG_EQC_FORCE_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_51 . CFG_EQC_FORCE_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_51_CFG_EQC_FORCE_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_52
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_52          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x152)

/** 
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_52 . CFG_IBIAS_TUNE_RESERVE_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_53
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_53          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x153)

/** 
 * \brief
 * T2 of Figure3.2-1 for power change operation.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_53 . R_TIME_CKB2CDR_PWRCHG_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_53_R_TIME_CKB2CDR_PWRCHG_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_53_R_TIME_CKB2CDR_PWRCHG_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_53_R_TIME_CKB2CDR_PWRCHG_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_54
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_54          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x154)

/** 
 * \brief
 * T2 of Figure3.2-1 for power change operation.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_54 . R_TIME_CKB2CDR_PWRCHG_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_54_R_TIME_CKB2CDR_PWRCHG_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_54_R_TIME_CKB2CDR_PWRCHG_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_54_R_TIME_CKB2CDR_PWRCHG_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_55
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_55          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x155)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_55 . CFG_EQC_FORCE_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_55_CFG_EQC_FORCE_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_55_CFG_EQC_FORCE_GEN4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_55_CFG_EQC_FORCE_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_55 . CFG_EN_PREDRV_EMPH_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_55 . CFG_EN_PREDRV_EMPH_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_55 . CFG_EN_PREDRV_EMPH_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_55_CFG_EN_PREDRV_EMPH_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_56
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_56          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x156)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_56 . CFG_VGA_CTRL_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_56 . CFG_VGA_CTRL_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_56_CFG_VGA_CTRL_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_57
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_57          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x157)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_57 . CFG_VGA_CTRL_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_57_CFG_VGA_CTRL_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_57_CFG_VGA_CTRL_GEN4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_57_CFG_VGA_CTRL_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_58
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_58          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x158)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_58 . CFG_TX_RSTB_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_58_CFG_TX_RSTB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_58_CFG_TX_RSTB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_58_CFG_TX_RSTB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_59
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_59          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x159)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_59 . CFG_TX_RSTB_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_59_CFG_TX_RSTB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_59_CFG_TX_RSTB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_59_CFG_TX_RSTB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15a)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5A . CFG_TX_SETB_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5A_CFG_TX_SETB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5A_CFG_TX_SETB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5A_CFG_TX_SETB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15b)

/** 
 * \brief
 * Internal use signals
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5B . CFG_TX_SETB_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5B_CFG_TX_SETB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5B_CFG_TX_SETB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5B_CFG_TX_SETB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15c)

/** 
 * \brief
 * The time interval to change the value of each power control bit.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5C . LX_PWRCHG_INTERVAL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5C_LX_PWRCHG_INTERVAL_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5C_LX_PWRCHG_INTERVAL_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5C_LX_PWRCHG_INTERVAL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15d)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[0] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5D . LX_PWRCHG_TIMER_B0_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5D_LX_PWRCHG_TIMER_B0_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5D_LX_PWRCHG_TIMER_B0_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5D_LX_PWRCHG_TIMER_B0_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15e)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[1] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5E . LX_PWRCHG_TIMER_B1_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5E_LX_PWRCHG_TIMER_B1_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5E_LX_PWRCHG_TIMER_B1_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5E_LX_PWRCHG_TIMER_B1_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_5F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_5F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x15f)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[2] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_5F . LX_PWRCHG_TIMER_B2_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_5F_LX_PWRCHG_TIMER_B2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_5F_LX_PWRCHG_TIMER_B2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_5F_LX_PWRCHG_TIMER_B2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_60
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_60          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x160)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[8:4] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_60 . LX_PWRCHG_TIMER_B8TOB4_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_60_LX_PWRCHG_TIMER_B8TOB4_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_60_LX_PWRCHG_TIMER_B8TOB4_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_60_LX_PWRCHG_TIMER_B8TOB4_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_61
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_61          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x161)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[11] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_61 . LX_PWRCHG_TIMER_B11_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_61_LX_PWRCHG_TIMER_B11_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_61_LX_PWRCHG_TIMER_B11_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_61_LX_PWRCHG_TIMER_B11_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_62
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_62          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x162)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[12] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_62 . LX_PWRCHG_TIMER_B12_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_62_LX_PWRCHG_TIMER_B12_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_62_LX_PWRCHG_TIMER_B12_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_62_LX_PWRCHG_TIMER_B12_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_63
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_63          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x163)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[13] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_63 . LX_PWRCHG_TIMER_B13_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_63_LX_PWRCHG_TIMER_B13_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_63_LX_PWRCHG_TIMER_B13_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_63_LX_PWRCHG_TIMER_B13_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_64
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_64          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x164)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[14] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_64 . LX_PWRCHG_TIMER_B14_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_64_LX_PWRCHG_TIMER_B14_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_64_LX_PWRCHG_TIMER_B14_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_64_LX_PWRCHG_TIMER_B14_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_65
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_65          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x165)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[15] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_65 . LX_PWRCHG_TIMER_B15_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_65_LX_PWRCHG_TIMER_B15_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_65_LX_PWRCHG_TIMER_B15_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_65_LX_PWRCHG_TIMER_B15_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_66
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_66          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x166)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[16] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_66 . LX_PWRCHG_TIMER_B16_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_66_LX_PWRCHG_TIMER_B16_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_66_LX_PWRCHG_TIMER_B16_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_66_LX_PWRCHG_TIMER_B16_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_67
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_67          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x167)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[17] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_67 . LX_PWRCHG_TIMER_B17_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_67_LX_PWRCHG_TIMER_B17_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_67_LX_PWRCHG_TIMER_B17_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_67_LX_PWRCHG_TIMER_B17_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_68
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_68          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x168)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[18] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_68 . LX_PWRCHG_TIMER_B18_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_68_LX_PWRCHG_TIMER_B18_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_68_LX_PWRCHG_TIMER_B18_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_68_LX_PWRCHG_TIMER_B18_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_69
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_69          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x169)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[19] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_69 . LX_PWRCHG_TIMER_B19_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_69_LX_PWRCHG_TIMER_B19_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_69_LX_PWRCHG_TIMER_B19_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_69_LX_PWRCHG_TIMER_B19_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16a)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[20] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6A . LX_PWRCHG_TIMER_B20_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6A_LX_PWRCHG_TIMER_B20_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6A_LX_PWRCHG_TIMER_B20_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6A_LX_PWRCHG_TIMER_B20_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16b)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[22] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6B . LX_PWRCHG_TIMER_B22_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6B_LX_PWRCHG_TIMER_B22_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6B_LX_PWRCHG_TIMER_B22_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6B_LX_PWRCHG_TIMER_B22_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16c)

/** 
 * \brief
 * The order of pcs2pma_power_ctrl[24] in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6C . LX_PWRCHG_TIMER_B24_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6C_LX_PWRCHG_TIMER_B24_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6C_LX_PWRCHG_TIMER_B24_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6C_LX_PWRCHG_TIMER_B24_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16d)

/** 
 * \brief
 * The order of tx_deemph related signals in the power change sequence.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6D . LX_PWRCHG_TIMER_TX_DEEMPH_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6D_LX_PWRCHG_TIMER_TX_DEEMPH_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6D_LX_PWRCHG_TIMER_TX_DEEMPH_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6D_LX_PWRCHG_TIMER_TX_DEEMPH_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16e)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6E . CFG_MF_MIN_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6E . CFG_MF_MIN_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6E_CFG_MF_MIN_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_6F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_6F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x16f)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_6F . CFG_MF_MIN_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_6F_CFG_MF_MIN_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_6F_CFG_MF_MIN_GEN4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_6F_CFG_MF_MIN_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_70
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_70          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x170)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_70 . CFG_RX_SP_CTLE_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN2     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_70 . CFG_RX_SP_CTLE_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN3(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN3     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_70 . CFG_RX_SP_CTLE_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN4(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN4     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_70_CFG_RX_SP_CTLE_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_71
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_71          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x171)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_71 . CFG_PI_EXT_DAC_B20TOB18_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_71 . CFG_PI_EXT_DAC_B20TOB18_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN3     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_71_CFG_PI_EXT_DAC_B20TOB18_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_72
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_72          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x172)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_72 . CFG_PI_EXT_DAC_B20TOB18_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_72_CFG_PI_EXT_DAC_B20TOB18_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_72_CFG_PI_EXT_DAC_B20TOB18_GEN4     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_72_CFG_PI_EXT_DAC_B20TOB18_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_73
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_73          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x173)

/** 
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_73 . CFG_ITX_IPDRIVER_BASE_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN2     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_73 . CFG_ITX_IPDRIVER_BASE_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN3     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_73_CFG_ITX_IPDRIVER_BASE_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_74
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_74          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x174)

/** 
 * \brief
 * 0x0000: infinite BIST run time. 0x0001~0xFFFF: BIST run time = (data
 * wicth/bit reate)* r_bist_timer[15:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_74 . R_BIST_TIMER_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_74_R_BIST_TIMER_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_74_R_BIST_TIMER_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_74_R_BIST_TIMER_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_75
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_75          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x175)

/** 
 * \brief
 * See above description 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_75 . R_BIST_TIMER_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_75_R_BIST_TIMER_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_75_R_BIST_TIMER_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_75_R_BIST_TIMER_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_76
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_76          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x176)

/** 
 * \brief
 * BIST enable signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_76 . R_BIST_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_76_R_BIST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_76_R_BIST_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_76_R_BIST_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * BIST error injection enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_76 . R_BIST_ERRINJEC
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_76_R_BIST_ERRINJEC(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_76_R_BIST_ERRINJEC  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_76_R_BIST_ERRINJEC(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 0: non free running mode.1: free running mode.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_76 . R_FREE_RUN_MODE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_76_R_FREE_RUN_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_76_R_FREE_RUN_MODE  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_76_R_FREE_RUN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * BIST pattern selection.000: PRBS7.001: PRBS9.010: PRBS11.011:
 * PRBS15.100: PRBS23.101: PRBS31.110: clock pattern.111: user defined
 * pattern.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_76 . R_BIST_MODE_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_76_R_BIST_MODE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_76_R_BIST_MODE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_76_R_BIST_MODE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_77
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_77          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x177)

/** 
 * \brief
 * BIST result compare enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_77 . R_BIST_CHK
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * 1: bist_err will assert if rx all zero data in PRBS mode..0: Treat all
 * zero data input as correct data. Note: r_bist_chk_zero must be set after
 * r_bist_ok is asserted.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_77 . R_BIST_CHK_ZERO
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK_ZERO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK_ZERO  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_77_R_BIST_CHK_ZERO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * 1: bist_err counter will stop when reaching 32'hffff_ffff.0: bist_err
 * counter will run continuously, will not saturate.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_77 . R_BIST_ERRSTOP
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_77_R_BIST_ERRSTOP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_77_R_BIST_ERRSTOP  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_77_R_BIST_ERRSTOP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_77 . R_BIST_RXERR_LBK
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_77_R_BIST_RXERR_LBK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_77_R_BIST_RXERR_LBK  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_77_R_BIST_RXERR_LBK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_78
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_78          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x178)

/** 
 * \brief
 * RX loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_78 . R_TIME_DEASSERT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_78_R_TIME_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_78_R_TIME_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_78_R_TIME_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_79
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_79          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x179)

/** 
 * \brief
 * RX loss of lock deassert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_79 . R_TIME_DEASSERT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_79_R_TIME_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_79_R_TIME_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_79_R_TIME_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17a)

/** 
 * \brief
 * RX loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7A . R_TIME_ASSERT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7A_R_TIME_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7A_R_TIME_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7A_R_TIME_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17b)

/** 
 * \brief
 * RX loss of lock assert timing.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7B . R_TIME_ASSERT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7B_R_TIME_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7B_R_TIME_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7B_R_TIME_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17c)

/** 
 * \brief
 * RX loss of lock status output enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7C . R_DLOL_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7C_R_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7C_R_DLOL_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7C_R_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17d)

/** 
 * \brief
 * RX loss of lock deassert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7D . R_DEASSERT_PPM_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7D_R_DEASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7D_R_DEASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7D_R_DEASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17e)

/** 
 * \brief
 * RX loss of lock deassert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7E . R_DEASSERT_PPM_9_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7E_R_DEASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7E_R_DEASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7E_R_DEASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_7F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_7F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x17f)

/** 
 * \brief
 * RX loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_7F . R_ASSERT_PPM_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_7F_R_ASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_7F_R_ASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_7F_R_ASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_80
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_80          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x180)

/** 
 * \brief
 * RX loss of lock assert dppm control. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_80 . R_ASSERT_PPM_9_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_80_R_ASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_80_R_ASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_80_R_ASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_81
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_81          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x181)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_81 . R_DLOS_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_81_R_DLOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_81_R_DLOS_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_81_R_DLOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_81 . R_LOS_CKONE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_81_R_LOS_CKONE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_81_R_LOS_CKONE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_81_R_LOS_CKONE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_82
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_82          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x182)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_82 . R_TIME_LOS_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_82_R_TIME_LOS_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_82_R_TIME_LOS_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_82_R_TIME_LOS_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Analog loss of signal enable.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_82 . R_ALOS_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_82_R_ALOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_82_R_ALOS_EN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_82_R_ALOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_82 . R_LOL_RESET
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_82_R_LOL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_82_R_LOL_RESET  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_82_R_LOL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_82 . R_TX_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_82_R_TX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_82_R_TX_RSTN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_82_R_TX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_82 . R_RX_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_82_R_RX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_82_R_RX_RSTN  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_82_R_RX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_83
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_83          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x183)

/** 
 * \brief
 * TX data bit reversal control. High active.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_TX_BIT_REVERSE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_TX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_TX_BIT_REVERSE  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_TX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * TX data bit polarity control. 1: polarity will be inverted.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_TX_POL_INV
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_TX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_TX_POL_INV  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_TX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * RX data bit reversal control. High active.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_RX_BIT_REVERSE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_RX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_RX_BIT_REVERSE  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_RX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * RX data bit polarity control. 1: polarity will be inverted.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_RX_POL_INV
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_RX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_RX_POL_INV  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_RX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_DFE_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_DFE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_DFE_RSTN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_DFE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_CDR_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_CDR_RSTN  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_83 . R_CTLE_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_83_R_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_83_R_CTLE_RSTN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_83_R_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_84
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_84          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x184)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_84 . R_TXEI
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_84_R_TXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_84_R_TXEI  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_84_R_TXEI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * RX loss of lock event clear.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_84 . R_LOL_CLR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_84_R_LOL_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_84_R_LOL_CLR  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_84_R_LOL_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_84 . R_LOGICAL_RXEI_SEL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_84_R_LOGICAL_RXEI_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_84_R_LOGICAL_RXEI_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_84_R_LOGICAL_RXEI_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_85
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_85          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x185)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_85 . R_RESERVE_0_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_85_R_RESERVE_0_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_85_R_RESERVE_0_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_85_R_RESERVE_0_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_86
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_86          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x186)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_86 . R_RESERVE_0_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_86_R_RESERVE_0_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_86_R_RESERVE_0_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_86_R_RESERVE_0_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_87
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_87          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x187)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_87 . R_RESERVE_1_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_87_R_RESERVE_1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_87_R_RESERVE_1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_87_R_RESERVE_1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_88
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_88          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x188)

/** 
 * \brief
 * Reserved
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_88 . R_RESERVE_1_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_88_R_RESERVE_1_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_88_R_RESERVE_1_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_88_R_RESERVE_1_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_89
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_89          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x189)

/** 
 * \brief
 * T2 in Figure 3.2-1 or T1 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_89 . R_TIME_CKB2CDR_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_89_R_TIME_CKB2CDR_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_89_R_TIME_CKB2CDR_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_89_R_TIME_CKB2CDR_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18a)

/** 
 * \brief
 * T2 in Figure 3.2-1 or T1 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8A . R_TIME_CKB2CDR_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8A_R_TIME_CKB2CDR_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8A_R_TIME_CKB2CDR_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8A_R_TIME_CKB2CDR_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18b)

/** 
 * \brief
 * T3 in Figure 3.2-1 or T2 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8B . R_TIME_CDR2TXRX_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8B_R_TIME_CDR2TXRX_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8B_R_TIME_CDR2TXRX_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8B_R_TIME_CDR2TXRX_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18c)

/** 
 * \brief
 * T3 in Figure 3.2-1 or T2 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8C . R_TIME_CDR2TXRX_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8C_R_TIME_CDR2TXRX_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8C_R_TIME_CDR2TXRX_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8C_R_TIME_CDR2TXRX_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18d)

/** 
 * \brief
 * T5 in Figure 3.2-1 or T4 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8D . R_TIME_CTLE2DFE_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8D_R_TIME_CTLE2DFE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8D_R_TIME_CTLE2DFE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8D_R_TIME_CTLE2DFE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18e)

/** 
 * \brief
 * T5 in Figure 3.2-1 or T4 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8E . R_TIME_CTLE2DFE_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8E_R_TIME_CTLE2DFE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8E_R_TIME_CTLE2DFE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8E_R_TIME_CTLE2DFE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_8F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_8F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x18f)

/** 
 * \brief
 * T4 in Figure 3.2-1 or T3 in Figure 3.2-2 (reset scheme).
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_8F . R_TIME_TXRX2CTLE_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_8F_R_TIME_TXRX2CTLE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_8F_R_TIME_TXRX2CTLE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_8F_R_TIME_TXRX2CTLE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_90
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_90          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x190)

/** 
 * \brief
 * Clock source of clk_out.00 : TX /16 /20 /32 or /64 clock.01 : TX /16
 * clock10 : RX /16 /20 /32 or /64 clock 11 : RX /16 clock
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_90 . R_CLK_OUT_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_90_R_CLK_OUT_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_90_R_CLK_OUT_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_90_R_CLK_OUT_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * The ckb2cdr timer selection for power change event.0 :
 * r_time_ckb2cdr[15:0] 1 : r_time_ckb2cdr_pwrchg
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_90 . R_EN_PWRCHG_RST_TIMER
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_90_R_EN_PWRCHG_RST_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_90_R_EN_PWRCHG_RST_TIMER  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_90_R_EN_PWRCHG_RST_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * The source of cfg_resetb_oscal_afe, cfg_pd_osdac_afe and cfg_oscal_afe.
 * 0 : Pins interface1 : configuration registers
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_90 . R_OSCAL_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_90_R_OSCAL_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_90_R_OSCAL_REG  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_90_R_OSCAL_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable the auto RX offset cancellation.Priority : r_auto_oscal_afe>
 * r_oscal_reg 0 : Manual mode.1 : Auto RX offset cancellation.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_90 . R_AUTO_OSCAL_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_AFE  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Enable the auto SQ offset cancellation.0 : Manual mode.1 : Auto mode.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_90 . R_AUTO_OSCAL_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_SQ  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_90_R_AUTO_OSCAL_SQ(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_91
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_91          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x191)

/** 
 * \brief
 * 1: enable LS3 loopback path.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_91 . R_LBSLV_IN_PMAD
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_91_R_LBSLV_IN_PMAD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_91_R_LBSLV_IN_PMAD  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_91_R_LBSLV_IN_PMAD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Refer to hwt_multi_lane_mode
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_91 . R_MULTI_LANE_MODE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_91_R_MULTI_LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_91_R_MULTI_LANE_MODE  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_91_R_MULTI_LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_91 . R_MASK_EI_SOURCE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_91_R_MASK_EI_SOURCE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_91_R_MASK_EI_SOURCE  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_91_R_MASK_EI_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_91 . R_DISABLE_EI_FILTER
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_91_R_DISABLE_EI_FILTER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_91_R_DISABLE_EI_FILTER  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_91_R_DISABLE_EI_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_91 . R_RXEI_FILTER_FACTOR_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_91_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_91_R_RXEI_FILTER_FACTOR_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_91_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_92
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_92          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x192)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_92 . R_TXEI_DLY_SEL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_92_R_TXEI_DLY_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_92_R_TXEI_DLY_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_92_R_TXEI_DLY_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_92 . R_TXEI_ADV_SEL_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_92_R_TXEI_ADV_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_92_R_TXEI_ADV_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_92_R_TXEI_ADV_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_93
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_93          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x193)

/** 
 * \brief
 * Reset RX FIFO if RXEI is asserted0 : disable1 : enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_RXEI_FIFO_RST_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_RXEI_FIFO_RST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_RXEI_FIFO_RST_EN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_RXEI_FIFO_RST_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Data width/data rate/termination resistor of reference clock control
 * from register or hardware pin.0: cfg control 1: hwt control
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_DWIDTHCTRL_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_DWIDTHCTRL_FROM_HWT  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_DIS_RESTORE_DFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_DIS_RESTORE_DFE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_DIS_RESTORE_DFE  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_DIS_RESTORE_DFE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * 0 : Legacy mode1 : PCI-E auto detection.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_EN_RATECHG_CTRL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_EN_RATECHG_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_EN_RATECHG_CTRL  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_EN_RATECHG_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * To select between interface pin control (default) and register control
 * of1.???? TX FFE coefficient control2.???? TX swing control3.???? power
 * down controlEye scan enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_REG_MANUAL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_REG_MANUAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_REG_MANUAL  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_REG_MANUAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Select aux_txck_sel/aux_rxck_sel is from hardware pin or configuration
 * registers.0 : Configuration register1 : pin interface
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_AUXCKSEL_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_AUXCKSEL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_AUXCKSEL_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_AUXCKSEL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Select lane_id is from hardware pin or configuration registers.0 :
 * Configuration register1 : pin interface
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_LANE_ID_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_LANE_ID_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_LANE_ID_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_LANE_ID_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Select pcie gen1/2 mode is from hardware pin or configuration
 * registers.0 : Configuration register1 : From cfg_sel_div
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_93 . R_RX_PCIE_GEN12_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_93_R_RX_PCIE_GEN12_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_93_R_RX_PCIE_GEN12_FROM_HWT  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_93_R_RX_PCIE_GEN12_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_94
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_94          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x194)

/** 
 * \brief
 * Refer to hwt_data_width_sel[2:0]
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_94 . R_DWIDTHCTRL_2_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_94_R_DWIDTHCTRL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_94_R_DWIDTHCTRL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_94_R_DWIDTHCTRL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * To select between interface pin control (default) and register control
 * of eye scan function0 : Pin control1 : Register control
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_94 . R_ISCAN_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_94_R_ISCAN_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_94_R_ISCAN_REG  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_94_R_ISCAN_REG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * To select between interface pin control (default) and register control
 * of tx equalizer0 : Pin control1 : Register control
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_94 . R_TXEQ_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_94_R_TXEQ_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_94_R_TXEQ_REG  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_94_R_TXEQ_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * To select between interface pin control (default) and register control
 * of miscellaneous signals.0 : Pin control1 : Register control
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_94 . R_MISC_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_94_R_MISC_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_94_R_MISC_REG  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_94_R_MISC_REG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * To select between interface pin control (default) and register control
 * oftx swing0 : Pin control1 : Register control
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_94 . R_SWING_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_94_R_SWING_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_94_R_SWING_REG  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_94_R_SWING_REG(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_95
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_95          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x195)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_95 . R_DBG_SEL_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_95_R_DBG_SEL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_95_R_DBG_SEL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_95_R_DBG_SEL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_96
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_96          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x196)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_96 . R_BIST_PATTERN_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_96_R_BIST_PATTERN_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_96_R_BIST_PATTERN_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_96_R_BIST_PATTERN_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_97
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_97          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x197)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_97 . R_BIST_PATTERN_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_97_R_BIST_PATTERN_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_97_R_BIST_PATTERN_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_97_R_BIST_PATTERN_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_98
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_98          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x198)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_98 . R_BIST_PATTERN_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_98_R_BIST_PATTERN_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_98_R_BIST_PATTERN_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_98_R_BIST_PATTERN_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_99
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_99          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x199)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_99 . R_BIST_PATTERN_31_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_99_R_BIST_PATTERN_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_99_R_BIST_PATTERN_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_99_R_BIST_PATTERN_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9A
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9A          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19a)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9A . R_BIST_PATTERN_39_32
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9A_R_BIST_PATTERN_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9A_R_BIST_PATTERN_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9A_R_BIST_PATTERN_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9B
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9B          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19b)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9B . R_BIST_PATTERN_47_40
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9B_R_BIST_PATTERN_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9B_R_BIST_PATTERN_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9B_R_BIST_PATTERN_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9C
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9C          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19c)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9C . R_BIST_PATTERN_55_48
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9C_R_BIST_PATTERN_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9C_R_BIST_PATTERN_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9C_R_BIST_PATTERN_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9D
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9D          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19d)

/** 
 * \brief
 * User defined BIST pattern
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9D . R_BIST_PATTERN_63_56
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9D_R_BIST_PATTERN_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9D_R_BIST_PATTERN_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9D_R_BIST_PATTERN_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9E
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9E          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19e)

/** 
 * \brief
 * Select RXEQ control signals are from hardware pin or configuration
 * registers.0 : hardware pin1 : configuration registers
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_RXEQ_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_RXEQ_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_RXEQ_REG  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_RXEQ_REG(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Reset tree buffer power down control selection.0 : Configuration
 * registers1 : internal circuit.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_AUTO_RST_TREE_PD_MAN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_AUTO_RST_TREE_PD_MAN  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Enable CDR auto reset function. Reset CDR if loss of lock under SSC0 :
 * Disable CDR auto reset1 : Enable CDR auto reset.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_EN_AUTO_CDR_RSTN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_EN_AUTO_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_EN_AUTO_CDR_RSTN  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_EN_AUTO_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * SATA speed change mode.0 : Disable. The pcs2pma_spd_chg is invalid.1 :
 * Enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_SATA_CHG_MODE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_SATA_CHG_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_SATA_CHG_MODE  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_SATA_CHG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_DFETAP_SGN_MAG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_DFETAP_SGN_MAG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_DFETAP_SGN_MAG  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_DFETAP_SGN_MAG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Source selection of tx_beacon_en and tx_beacon_d0 : pins interface1 :
 * configuration registers
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_TX_BEACON_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_REG  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Enable the beacon transimission.0 : Disable1 : Enable
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_TX_BEACON_EN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_EN  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Beacon data pattern.0 : TXP = 0: TXN= 11 : TXP = 1 : TXN =0
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9E . R_TX_BEACON_D
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_D(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_D  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9E_R_TX_BEACON_D(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_9F
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_9F          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x19f)

/** 
 * \brief
 * Source selection of ALOS threshold 0 : configuration registers.1 : pins
 * interface
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_ALOS_THR_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_ALOS_THR_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_ALOS_THR_FROM_HWT  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_ALOS_THR_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Source selection of cfg_rxdet_en and cfg_rxdet_str.0 : pins interface1 :
 * configuration registers.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_RXDET_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_RXDET_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_RXDET_REG  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_RXDET_REG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_SWING_RATECHG_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_SWING_RATECHG_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_SWING_RATECHG_REG  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_SWING_RATECHG_REG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_TXEQ_RATECHG_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_TXEQ_RATECHG_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_TXEQ_RATECHG_REG  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_TXEQ_RATECHG_REG(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_RXEQ_RATECHG_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_RXEQ_RATECHG_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_RXEQ_RATECHG_REG  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_RXEQ_RATECHG_REG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_PI_HOLD_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_PI_HOLD_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_PI_HOLD_REG  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_PI_HOLD_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_9F . R_SUM_SETCM_EN_REG
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_9F_R_SUM_SETCM_EN_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_9F_R_SUM_SETCM_EN_REG  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_9F_R_SUM_SETCM_EN_REG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a0)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A0 . R_DWF_TX_DIV_MODE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A0_R_DWF_TX_DIV_MODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A0_R_DWF_TX_DIV_MODE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A0_R_DWF_TX_DIV_MODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A0 . R_TXFIFO_INI_RDPTR_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A0_R_TXFIFO_INI_RDPTR_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A0_R_TXFIFO_INI_RDPTR_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A0_R_TXFIFO_INI_RDPTR_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A1 . R_PMA_TXCK_DIV_SEL_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Select ssc control signals are from hardware pin or configuration
 * registers.0 : Configuration register1 : From hardware pins
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A1 . R_SSC_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A1_R_SSC_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A1_R_SSC_FROM_HWT  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A1_R_SSC_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Select cdr control signals are from hardware pin or configuration
 * registers.0 : Configuration register1 : From hardware pins
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A1 . R_CDR_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A1_R_CDR_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A1_R_CDR_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A1_R_CDR_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Select pclk_gating is from hardware pin or configuration registers.0 :
 * Configuration register1 : From hardware pins
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A1 . R_PCLK_GATING_FROM_HWT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/** 
 * \brief
 * Gating the pma_tx_ck_src,pma_rx_ck and pclk when speed change
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A1 . R_PCLK_GATING
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING  VTSS_BIT(7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A1_R_PCLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a2)

/** 
 * \brief
 * SATA/SAS : 5'b00_100PCIE Gen1/2 : 5'b00_011PCIE Gen3 : 5'b00_010(8G-12G
 * VCO)PCIE Gen3 : 5'b10_010(16G VCO)PCIE Gen4 : 5'b10_010DP mode Gen1 :
 * 5'b01_000DP mode Gen2 : 5'b01_001DP mode Gen3 : 5'b01_010DP mode Gen4 :
 * 5'b01_011Others : 5'b00_000
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A2 . R_PCS2PMA_PHYMODE_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A2_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A2_R_PCS2PMA_PHYMODE_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A2_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a3)

/** 
 * \brief
 * RX loss of lock deassert  ppm control for SSC. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A3 . R_DEASSERT_PPM_SSC_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A3_R_DEASSERT_PPM_SSC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A3_R_DEASSERT_PPM_SSC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A3_R_DEASSERT_PPM_SSC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a4)

/** 
 * \brief
 * RX loss of lock deassert  ppm control for SSC. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A4 . R_DEASSERT_PPM_SSC_11_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A4_R_DEASSERT_PPM_SSC_11_8(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A4_R_DEASSERT_PPM_SSC_11_8     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A4_R_DEASSERT_PPM_SSC_11_8(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A5
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A5          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a5)

/** 
 * \brief
 * RX loss of lock assert  ppm control for SSC. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A5 . R_ASSERT_PPM_SSC_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A5_R_ASSERT_PPM_SSC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A5_R_ASSERT_PPM_SSC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A5_R_ASSERT_PPM_SSC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A6
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A6          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a6)

/** 
 * \brief
 * RX loss of lock assert  ppm control for SSC. 
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A6 . R_ASSERT_PPM_SSC_11_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A6_R_ASSERT_PPM_SSC_11_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A6_R_ASSERT_PPM_SSC_11_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A6_R_ASSERT_PPM_SSC_11_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A7
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A7          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a7)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A7 . CFG_PI_FLOOP_STEPS_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN2_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A7 . CFG_PI_FLOOP_STEPS_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN3_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A7_CFG_PI_FLOOP_STEPS_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A8
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A8          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a8)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A8 . CFG_PI_FLOOP_STEPS_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A8_CFG_PI_FLOOP_STEPS_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A8_CFG_PI_FLOOP_STEPS_GEN4_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A8_CFG_PI_FLOOP_STEPS_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_A9
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_A9          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1a9)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_A9 . CFG_ISCAN_EXT_DAC_B12TOB8_GEN2_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_A9_CFG_ISCAN_EXT_DAC_B12TOB8_GEN2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_A9_CFG_ISCAN_EXT_DAC_B12TOB8_GEN2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_A9_CFG_ISCAN_EXT_DAC_B12TOB8_GEN2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AA
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AA          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1aa)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AA . CFG_ISCAN_EXT_DAC_B12TOB8_GEN3_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AA_CFG_ISCAN_EXT_DAC_B12TOB8_GEN3_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AA_CFG_ISCAN_EXT_DAC_B12TOB8_GEN3_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AA_CFG_ISCAN_EXT_DAC_B12TOB8_GEN3_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AB
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AB          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ab)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AB . CFG_ISCAN_EXT_DAC_B12TOB8_GEN4_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AB_CFG_ISCAN_EXT_DAC_B12TOB8_GEN4_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AB_CFG_ISCAN_EXT_DAC_B12TOB8_GEN4_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AB_CFG_ISCAN_EXT_DAC_B12TOB8_GEN4_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AC
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AC          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ac)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AC . CFG_ALOS_THR_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AC . CFG_ALOS_THR_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AC_CFG_ALOS_THR_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AD
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AD          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ad)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AD . CFG_ALOS_THR_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AD_CFG_ALOS_THR_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AD_CFG_ALOS_THR_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AD_CFG_ALOS_THR_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AE
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AE          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ae)

/** 
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AE . CFG_ITX_IPDRIVER_BASE_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AE_CFG_ITX_IPDRIVER_BASE_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AE_CFG_ITX_IPDRIVER_BASE_GEN4     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AE_CFG_ITX_IPDRIVER_BASE_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AE . CFG_VGA_CAP_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AE_CFG_VGA_CAP_GEN2(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AE_CFG_VGA_CAP_GEN2     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AE_CFG_VGA_CAP_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_AF
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_AF          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1af)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AF . CFG_VGA_CAP_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN3(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN3     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_AF . CFG_VGA_CAP_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN4(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN4     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_AF_CFG_VGA_CAP_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b0)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B0 . CFG_RXFILT_Z_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN2_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B0 . CFG_RXFILT_Z_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN3_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B0_CFG_RXFILT_Z_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B1 . CFG_RXFILT_Z_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B1_CFG_RXFILT_Z_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B1_CFG_RXFILT_Z_GEN4_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B1_CFG_RXFILT_Z_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B1 . CFG_DIS_2NDORDER_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B1 . CFG_DIS_2NDORDER_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B1 . CFG_DIS_2NDORDER_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B1_CFG_DIS_2NDORDER_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b2)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B2 . CFG_PI_EXT_DAC_B17TOB14_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B2 . CFG_PI_EXT_DAC_B17TOB14_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B2_CFG_PI_EXT_DAC_B17TOB14_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b3)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B3 . CFG_PI_EXT_DAC_B17TOB14_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B17TOB14_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B17TOB14_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B17TOB14_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B3 . CFG_PI_EXT_DAC_B21_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B3 . CFG_PI_EXT_DAC_B21_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B3 . CFG_PI_EXT_DAC_B21_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B3_CFG_PI_EXT_DAC_B21_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b4)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_RX_SSC_LH_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN2  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_RX_SSC_LH_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN3  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_RX_SSC_LH_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN4  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_RX_SSC_LH_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_PI_STEPS_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_PI_STEPS_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B4 . CFG_PI_STEPS_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B4_CFG_PI_STEPS_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B5
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B5          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b5)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B5 . CFG_PI_OFFSET_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B5 . CFG_PI_OFFSET_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B5_CFG_PI_OFFSET_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B6
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B6          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b6)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B6 . CFG_PI_OFFSET_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B6_CFG_PI_OFFSET_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B6_CFG_PI_OFFSET_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B6_CFG_PI_OFFSET_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B7
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B7          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b7)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B7 . CFG_TACC_SEL_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN2_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B7 . CFG_TACC_SEL_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN3_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B7_CFG_TACC_SEL_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B8
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B8          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b8)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B8 . CFG_TACC_SEL_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B8_CFG_TACC_SEL_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B8_CFG_TACC_SEL_GEN4_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B8_CFG_TACC_SEL_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_B9
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_B9          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1b9)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B9 . CFG_PI_EXT_DAC_B3TOB0_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_B9 . CFG_PI_EXT_DAC_B3TOB0_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_B9_CFG_PI_EXT_DAC_B3TOB0_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BA
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BA          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ba)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BA . CFG_PI_EXT_DAC_B3TOB0_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BA_CFG_PI_EXT_DAC_B3TOB0_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BA_CFG_PI_EXT_DAC_B3TOB0_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BA_CFG_PI_EXT_DAC_B3TOB0_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BB
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BB          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1bb)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BB . CFG_ISCAN_EXT_DAC_B4TOB0_GEN2_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BB_CFG_ISCAN_EXT_DAC_B4TOB0_GEN2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BB_CFG_ISCAN_EXT_DAC_B4TOB0_GEN2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BB_CFG_ISCAN_EXT_DAC_B4TOB0_GEN2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BC
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BC          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1bc)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BC . CFG_ISCAN_EXT_DAC_B4TOB0_GEN3_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BC_CFG_ISCAN_EXT_DAC_B4TOB0_GEN3_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BC_CFG_ISCAN_EXT_DAC_B4TOB0_GEN3_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BC_CFG_ISCAN_EXT_DAC_B4TOB0_GEN3_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BD
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BD          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1bd)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BD . CFG_ISCAN_EXT_DAC_B4TOB0_GEN4_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BD_CFG_ISCAN_EXT_DAC_B4TOB0_GEN4_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BD_CFG_ISCAN_EXT_DAC_B4TOB0_GEN4_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BD_CFG_ISCAN_EXT_DAC_B4TOB0_GEN4_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BE
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BE          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1be)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_RSTN_DFEDIG_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN2  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_RSTN_DFEDIG_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN3  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_RSTN_DFEDIG_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN4  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_RSTN_DFEDIG_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_ISCAN_EXT_DAC_B30_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN2(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN2  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_ISCAN_EXT_DAC_B30_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN3(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN3  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BE . CFG_ISCAN_EXT_DAC_B30_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN4(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN4  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BE_CFG_ISCAN_EXT_DAC_B30_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_BF
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_BF          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1bf)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BF . R_REFCLK_DIV
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BF_R_REFCLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BF_R_REFCLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BF_R_REFCLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BF . R_AUTO_PWRON_ISCAN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BF_R_AUTO_PWRON_ISCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BF_R_AUTO_PWRON_ISCAN  VTSS_BIT(4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BF_R_AUTO_PWRON_ISCAN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BF . R_SHORT_CALCNT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BF_R_SHORT_CALCNT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BF_R_SHORT_CALCNT  VTSS_BIT(5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BF_R_SHORT_CALCNT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_BF . R_SPDCHG_RECAL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_BF_R_SPDCHG_RECAL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_BF_R_SPDCHG_RECAL  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_BF_R_SPDCHG_RECAL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c0)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C0 . PI_DAC_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C0_PI_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C0_PI_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C0_PI_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c1)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C1 . PI_DAC_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C1_PI_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C1_PI_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C1_PI_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C2 . PI_DAC_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C2_PI_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C2_PI_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C2_PI_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c3)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C3 . PI_DAC_30_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C3_PI_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C3_PI_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C3_PI_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c4)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C4 . PI_QRT_CODE_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C4_PI_QRT_CODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C4_PI_QRT_CODE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C4_PI_QRT_CODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C4 . VGAR_CODE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C4_VGAR_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C4_VGAR_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C4_VGAR_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C5
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C5          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c5)

/** 
 * \brief
 * DFE coefficient.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C5 . H1_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C5_H1_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C5_H1_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C5_H1_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C6
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C6          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c6)

/** 
 * \brief
 * DFE coefficient.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C6 . H2_4_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C6_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C6_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C6_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C7
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C7          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c7)

/** 
 * \brief
 * DFE coefficient.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C7 . H3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C7_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C7_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C7_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C8
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C8          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c8)

/** 
 * \brief
 * DFE coefficient.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C8 . H4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C8_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C8_H4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C8_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_C9
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_C9          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1c9)

/** 
 * \brief
 * DFE coefficient.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_C9 . H5_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_C9_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_C9_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_C9_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CA
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CA          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ca)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CA . DLEV_6_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CA_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CA_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CA_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CB
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CB          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1cb)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CB . OSDAC_CODE_AFE_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CB_OSDAC_CODE_AFE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CB_OSDAC_CODE_AFE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CB_OSDAC_CODE_AFE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CB . CALEND_AFE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CB_CALEND_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CB_CALEND_AFE  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CB_CALEND_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CC
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CC          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1cc)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CC . OSDAC_CODE_SQ_5_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CC_OSDAC_CODE_SQ_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CC_OSDAC_CODE_SQ_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CC_OSDAC_CODE_SQ_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CC . CALEND_SQ
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CC_CALEND_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CC_CALEND_SQ  VTSS_BIT(6)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CC_CALEND_SQ(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CD
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CD          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1cd)

/** 
 * \brief
 * Reserved.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CD . CFG_STATUS_RESERVE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CD_CFG_STATUS_RESERVE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CD_CFG_STATUS_RESERVE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CD_CFG_STATUS_RESERVE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CE
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CE          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1ce)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CE . PHYMODE_CUR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CE_PHYMODE_CUR(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CE_PHYMODE_CUR     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CE_PHYMODE_CUR(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_CF
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_CF          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1cf)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CF . RXRATE_CUR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CF_RXRATE_CUR(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CF_RXRATE_CUR     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CF_RXRATE_CUR(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_CF . TXRATE_CUR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_CF_TXRATE_CUR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_CF_TXRATE_CUR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_CF_TXRATE_CUR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d0)

/** 
 * \brief
 * 0 : Fast eye scan is correct.1 : Fast eye scan is failed. The upper
 * bound or low bound of eye can not be found.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D0 . FAST_EYE_SCAN_FAIL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D0_FAST_EYE_SCAN_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D0_FAST_EYE_SCAN_FAIL  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D0_FAST_EYE_SCAN_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Eye scan status0 : eye scan is on-going1 : eye scan process is done.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D0 . ISCAN_DONE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D0_ISCAN_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D0_ISCAN_DONE  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D0_ISCAN_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d1)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D1 . ISCAN_RESULTS_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D1_ISCAN_RESULTS_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D1_ISCAN_RESULTS_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D1_ISCAN_RESULTS_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d2)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D2 . ISCAN_RESULTS_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D2_ISCAN_RESULTS_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D2_ISCAN_RESULTS_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D2_ISCAN_RESULTS_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d3)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D3 . ISCAN_RESULTS_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D3_ISCAN_RESULTS_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D3_ISCAN_RESULTS_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D3_ISCAN_RESULTS_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d4)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D4 . ISCAN_RESULTS_31_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D4_ISCAN_RESULTS_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D4_ISCAN_RESULTS_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D4_ISCAN_RESULTS_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D5
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D5          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d5)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D5 . ISCAN_RESULTS_39_32
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D5_ISCAN_RESULTS_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D5_ISCAN_RESULTS_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D5_ISCAN_RESULTS_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D6
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D6          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d6)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D6 . ISCAN_RESULTS_47_40
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D6_ISCAN_RESULTS_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D6_ISCAN_RESULTS_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D6_ISCAN_RESULTS_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D7
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D7          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d7)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D7 . ISCAN_RESULTS_55_48
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D7_ISCAN_RESULTS_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D7_ISCAN_RESULTS_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D7_ISCAN_RESULTS_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D8
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D8          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d8)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D8 . ISCAN_RESULTS_63_56
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D8_ISCAN_RESULTS_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D8_ISCAN_RESULTS_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D8_ISCAN_RESULTS_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_D9
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_D9          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1d9)

/** 
 * \brief
 * Eye scan result
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_D9 . ISCAN_RESULTS_64
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_D9_ISCAN_RESULTS_64(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_D9_ISCAN_RESULTS_64  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_D9_ISCAN_RESULTS_64(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DA
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DA          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1da)

/** 
 * \brief
 * Eye scan result for single point scan.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DA . ISACN_RESULT
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DA_ISACN_RESULT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DA_ISACN_RESULT  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DA_ISACN_RESULT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DB
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DB          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1db)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DB . ISACN_VOLT_STAT_6_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DB_ISACN_VOLT_STAT_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DB_ISACN_VOLT_STAT_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DB_ISACN_VOLT_STAT_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DC
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DC          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1dc)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DC . ISCAN_ERR_CNT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DC_ISCAN_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DC_ISCAN_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DC_ISCAN_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DD
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DD          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1dd)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DD . ISCAN_ERR_CNT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DD_ISCAN_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DD_ISCAN_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DD_ISCAN_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DE
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DE          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1de)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DE . EQC_CODE_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DE_EQC_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DE_EQC_CODE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DE_EQC_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_DF
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_DF          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1df)

/** 
 * \brief
 * RX loss of lock event indicator. (latch-high signal).0: RX clock is
 * locked to PLL clock.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DF . LOL_UDL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DF_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DF_LOL_UDL  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DF_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * RX loss of lock indicator. 0: RX clock is locked to PLL clock..
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DF . LOL
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DF_LOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DF_LOL    VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DF_LOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Loss of signal state.0: RX signal is detected. Note this bit is RX data
 * pattern dependent. Non-standard application with this signal is
 * recommended to check with GUC designers.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DF . PMA2PCS_RXEI_FILTERED
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DF_PMA2PCS_RXEI_FILTERED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DF_PMA2PCS_RXEI_FILTERED  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DF_PMA2PCS_RXEI_FILTERED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * Squelch status.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_DF . SQUELCH
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_DF_SQUELCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_DF_SQUELCH  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_DF_SQUELCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_E0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_E0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1e0)

/** 
 * \brief
 * BIST is active.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E0 . BIST_RUN
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E0_BIST_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E0_BIST_RUN  VTSS_BIT(0)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E0_BIST_RUN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * BIST is ok.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E0 . BIST_OK
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E0_BIST_OK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E0_BIST_OK  VTSS_BIT(1)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E0_BIST_OK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * BIST is error.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E0 . BIST_ERR
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E0_BIST_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E0_BIST_ERR  VTSS_BIT(2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E0_BIST_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/** 
 * \brief
 * The bist time is time out.Bist time = (data width/bit rate)*1024 *
 * r_bist_timer.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E0 . BIST_DONE
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E0_BIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E0_BIST_DONE  VTSS_BIT(3)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E0_BIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_E1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_E1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1e1)

/** 
 * \brief
 * BIST Error counter
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E1 . BIST_ERR_CNT_7_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E1_BIST_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E1_BIST_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E1_BIST_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_E2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_E2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1e2)

/** 
 * \brief
 * BIST Error counter
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E2 . BIST_ERR_CNT_15_8
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E2_BIST_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E2_BIST_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E2_BIST_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_E3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_E3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1e3)

/** 
 * \brief
 * BIST Error counter
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E3 . BIST_ERR_CNT_23_16
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E3_BIST_ERR_CNT_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E3_BIST_ERR_CNT_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E3_BIST_ERR_CNT_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_0:PMA_LANE_E4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_E4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1e4)

/** 
 * \brief
 * BIST Error counter
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_E4 . BIST_ERR_CNT_31_24
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_E4_BIST_ERR_CNT_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_E4_BIST_ERR_CNT_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_E4_BIST_ERR_CNT_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SDPCIE_PMA:PMA_LANE_GRP_1
 *
 * Register group for registers 0xF0 to 0xFE
 */


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F0
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F0          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f0)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F0 . CFG_PREDRV_SLEWRATE_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN2_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F0 . CFG_PREDRV_SLEWRATE_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN3_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F0_CFG_PREDRV_SLEWRATE_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F1
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F1          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f1)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F1 . CFG_PREDRV_SLEWRATE_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F1_CFG_PREDRV_SLEWRATE_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F1_CFG_PREDRV_SLEWRATE_GEN4_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F1_CFG_PREDRV_SLEWRATE_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F2
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F2          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f2)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F2 . CFG_MP_MAX_GEN2_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F2 . CFG_MP_MAX_GEN3_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN3_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F2_CFG_MP_MAX_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F3
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F3          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f3)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F3 . CFG_MP_MAX_GEN4_3_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F3_CFG_MP_MAX_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F3_CFG_MP_MAX_GEN4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F3_CFG_MP_MAX_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F3 . CFG_ITX_IPCML_BASE_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F3_CFG_ITX_IPCML_BASE_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F3_CFG_ITX_IPCML_BASE_GEN2_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F3_CFG_ITX_IPCML_BASE_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F4
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F4          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f4)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F4 . CFG_ITX_IPCML_BASE_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN3_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F4 . CFG_ITX_IPCML_BASE_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN4_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F4_CFG_ITX_IPCML_BASE_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F5
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F5          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f5)

/** 
 * \brief
 * Preset registers for PCIE-G2, SATA-2 or DP-G2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F5 . CFG_IP_PRE_BASE_GEN2_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN2_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN2_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN2_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/** 
 * \brief
 * Preset registers for PCIE-G3, SATA-3 or DP-G3
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F5 . CFG_IP_PRE_BASE_GEN3_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN3_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN3_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F5_CFG_IP_PRE_BASE_GEN3_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F6
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F6          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f6)

/** 
 * \brief
 * Preset registers for PCIE-G4, SAS-3 or DP-G4
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F6 . CFG_IP_PRE_BASE_GEN4_1_0
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F6_CFG_IP_PRE_BASE_GEN4_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F6_CFG_IP_PRE_BASE_GEN4_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F6_CFG_IP_PRE_BASE_GEN4_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F7
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F7          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f7)

/** 
 * \brief
 * Pre-equalization level control of TX. Refer to section 2.6.2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F7 . CFG_TAP_ADV_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F7_CFG_TAP_ADV_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F7_CFG_TAP_ADV_GEN2     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F7_CFG_TAP_ADV_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F8
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F8          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f8)

/** 
 * \brief
 * Pre-equalization level control of TX. Refer to section 2.6.2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F8 . CFG_TAP_ADV_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F8_CFG_TAP_ADV_GEN3(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F8_CFG_TAP_ADV_GEN3     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F8_CFG_TAP_ADV_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_F9
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_F9          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1f9)

/** 
 * \brief
 * Pre-equalization level control of TX. Refer to section 2.6.2
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_F9 . CFG_TAP_ADV_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_F9_CFG_TAP_ADV_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_F9_CFG_TAP_ADV_GEN4     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_F9_CFG_TAP_ADV_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_FA
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_FA          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1fa)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FA . CFG_TAP_DLY_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FA_CFG_TAP_DLY_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FA_CFG_TAP_DLY_GEN2     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FA_CFG_TAP_DLY_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_FB
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_FB          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1fb)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FB . CFG_TAP_DLY_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FB_CFG_TAP_DLY_GEN3(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FB_CFG_TAP_DLY_GEN3     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FB_CFG_TAP_DLY_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_FC
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_FC          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1fc)

/** 
 * \brief
 * Internal use signal.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FC . CFG_TAP_DLY_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FC_CFG_TAP_DLY_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FC_CFG_TAP_DLY_GEN4     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FC_CFG_TAP_DLY_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_FD
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_FD          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1fd)

/** 
 * \brief
 * CTLE gain control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FD . CFG_EQ_RES_GEN2
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN2(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN2     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN2(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/** 
 * \brief
 * CTLE gain control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FD . CFG_EQ_RES_GEN3
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN3(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN3     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FD_CFG_EQ_RES_GEN3(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/** 
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SDPCIE_PMA:PMA_LANE_GRP_1:PMA_LANE_FE
 */
#define VTSS_SDPCIE_PMA_PMA_LANE_FE          VTSS_IOREG(VTSS_TO_SDPCIE_PMA,0x1fe)

/** 
 * \brief
 * CTLE gain control.
 *
 * \details 
 * Field: ::VTSS_SDPCIE_PMA_PMA_LANE_FE . CFG_EQ_RES_GEN4
 */
#define  VTSS_F_SDPCIE_PMA_PMA_LANE_FE_CFG_EQ_RES_GEN4(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SDPCIE_PMA_PMA_LANE_FE_CFG_EQ_RES_GEN4     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SDPCIE_PMA_PMA_LANE_FE_CFG_EQ_RES_GEN4(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_FA_REGS_SDPCIE_PMA_H_ */
