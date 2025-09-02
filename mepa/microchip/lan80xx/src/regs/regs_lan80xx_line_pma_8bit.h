// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_LINE_PMA_8BIT_H_
#define LAN80XX_MALIBU25G_REGS_LINE_PMA_8BIT_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a LINE_PMA_8BIT
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_PMA_8BIT:CMU_GRP_0
 *
 * Register group for registers 0x00 to 0x1F
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_00
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_00                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf000))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_00 . CFG_TX_RSTB_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_00_CFG_TX_RSTB_7_0(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_00_CFG_TX_RSTB_7_0                                             (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_00_CFG_TX_RSTB_7_0(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_01
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_01                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf001))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_01 . CFG_TX_RSTB_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_01_CFG_TX_RSTB_15_8(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_01_CFG_TX_RSTB_15_8                                            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_01_CFG_TX_RSTB_15_8(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_02
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_02                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf002))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_02 . CFG_TX_SETB_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_02_CFG_TX_SETB_7_0(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_02_CFG_TX_SETB_7_0                                             (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_02_CFG_TX_SETB_7_0(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_03
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_03                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf003))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_03 . CFG_TX_SETB_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_03_CFG_TX_SETB_15_8(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_03_CFG_TX_SETB_15_8                                            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_03_CFG_TX_SETB_15_8(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_04
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_04                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf004))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_04 . CFG_IC2IP_N
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_04_CFG_IC2IP_N(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_04_CFG_IC2IP_N                                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_04_CFG_IC2IP_N(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_04 . CFG_BIAS_TP_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_04_CFG_BIAS_TP_SEL_1_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_04_CFG_BIAS_TP_SEL_1_0                                         (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_04_CFG_BIAS_TP_SEL_1_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_05
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_05                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf005))

/**
 * \brief
 * Reference current/voltage fine-tuning control ~+/-2.5% increase/decrease
 * per code change
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_05 . CFG_IBIAS_VC_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_VC_3_0(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_VC_3_0                                            (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_VC_3_0(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_05 . CFG_IBIAS_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_PD(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_PD                                                (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_PD(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_05 . CFG_IBIAS_EN_EXTVBG
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_EN_EXTVBG(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_EN_EXTVBG                                         (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_05_CFG_IBIAS_EN_EXTVBG(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_06
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_06                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf006))

/**
 * \brief
 * Clock distribution buffer fine-tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_06 . CFG_IPLL_UP_TREE_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0                                   (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_TREE_BASE_1_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_06 . CFG_IPLL_UP_RESETB_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0                                 (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_06_CFG_IPLL_UP_RESETB_BASE_1_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_07
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_07                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf007))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_07 . CFG_IPLL_RESETB_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_07_CFG_IPLL_RESETB_BASE_1_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_07_CFG_IPLL_RESETB_BASE_1_0                                    (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_07_CFG_IPLL_RESETB_BASE_1_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * High speed CML & divider fine-tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_07 . CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0(x)                       (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0                          (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_07_CFG_IPLL_IC500U_CLOCKTREE_BASE_1_0(x)                       (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_08
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_08                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf008))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_08 . CFG_IPLL_DN_RESETB_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0                                 (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_08_CFG_IPLL_DN_RESETB_BASE_1_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_09
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_09                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf009))

/**
 * \brief
 * Ref clock receiver enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_09 . CFG_REFCK_TERM_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_09_CFG_REFCK_TERM_EN(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_09_CFG_REFCK_TERM_EN                                           (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_09_CFG_REFCK_TERM_EN(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_09 . CFG_EN_DUMMY
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_09_CFG_EN_DUMMY(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_09_CFG_EN_DUMMY                                                (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_09_CFG_EN_DUMMY(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_09 . CFG_PLL_LOS_SET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_09_CFG_PLL_LOS_SET(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_09_CFG_PLL_LOS_SET                                             (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_09_CFG_PLL_LOS_SET(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_09 . CFG_CTRL_LOGIC_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_09_CFG_CTRL_LOGIC_PD(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_09_CFG_CTRL_LOGIC_PD                                           (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_09_CFG_CTRL_LOGIC_PD(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_09 . CFG_PLL_TP_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_09_CFG_PLL_TP_SEL_1_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_09_CFG_PLL_TP_SEL_1_0                                          (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_09_CFG_PLL_TP_SEL_1_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0A
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0A                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0A . CFG_VCO_BYP_CTUNE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0A_CFG_VCO_BYP_CTUNE_3_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0A_CFG_VCO_BYP_CTUNE_3_0                                       (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0A_CFG_VCO_BYP_CTUNE_3_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0A . CFG_VCO_START_CODE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0A_CFG_VCO_START_CODE_3_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0A_CFG_VCO_START_CODE_3_0                                      (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0A_CFG_VCO_START_CODE_3_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0B
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0B                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00b))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_FORCE_RX_FILT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_FORCE_RX_FILT(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_FORCE_RX_FILT                                           (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_FORCE_RX_FILT(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_DISLOL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_DISLOL(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_DISLOL                                                  (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_DISLOL(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_RST_TREE_PD_MAN_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN_EN(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN_EN                                      (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN_EN(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * VCO calibration reset
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_VCO_CAL_RESETN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN                                          (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_VCO_CAL_RESETN(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_VFILT2PAD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_VFILT2PAD(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_VFILT2PAD                                               (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_VFILT2PAD(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_DISLOS
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_DISLOS(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_DISLOS                                                  (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_DISLOS(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_DCLOL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_DCLOL(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_DCLOL                                                   (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_DCLOL(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0B . CFG_RST_TREE_PD_MAN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN                                         (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0B_CFG_RST_TREE_PD_MAN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0C
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0C                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00c))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0C . CFG_PLL_LOL_SET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0C_CFG_PLL_LOL_SET(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0C_CFG_PLL_LOL_SET                                             (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0C_CFG_PLL_LOL_SET(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable clock distribution for TX Lane 2 + Lane 3
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0C . CFG_EN_TX_CK_DN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_DN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_DN                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_DN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Power down VCO
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0C . CFG_VCO_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0C_CFG_VCO_PD(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0C_CFG_VCO_PD                                                  (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0C_CFG_VCO_PD(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Enable clock distribution for TX Lane 0 + Lane 1
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0C . CFG_EN_TX_CK_UP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_UP(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_UP                                             (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0C_CFG_EN_TX_CK_UP(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * VCO divider setting,00, divide by 0 01, divide by 2
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0C . CFG_VCO_DIV_MODE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0C_CFG_VCO_DIV_MODE_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0C_CFG_VCO_DIV_MODE_1_0                                        (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0C_CFG_VCO_DIV_MODE_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0D
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0D                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0D . CFG_CK_TREE_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0D_CFG_CK_TREE_PD(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0D_CFG_CK_TREE_PD                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0D_CFG_CK_TREE_PD(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Enable clock distribution for RX Lane 2 + Lane 3
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0D . CFG_EN_RX_CK_DN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_DN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_DN                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_DN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable clock distribution for RX Lane 0 + Lane 1
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0D . CFG_EN_RX_CK_UP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_UP(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_UP                                             (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0D_CFG_EN_RX_CK_UP(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Bypass VCO calibration,Debug mode only
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0D . CFG_VCO_CAL_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0D_CFG_VCO_CAL_BYP(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0D_CFG_VCO_CAL_BYP                                             (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0D_CFG_VCO_CAL_BYP(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Reference clock divide 00  Divide-by-1 01  Divide-by-2 10  Divide-by-4
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0D . CFG_PRE_DIVSEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0D_CFG_PRE_DIVSEL_1_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0D_CFG_PRE_DIVSEL_1_0                                          (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0D_CFG_PRE_DIVSEL_1_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0E
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0E                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00e))

/**
 * \brief
 * Application notes for more details and restrictions.  Common
 * settings:0110: Divide by 160 1111: Divide by 330
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0E . CFG_SEL_DIV_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0E_CFG_SEL_DIV_3_0(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0E_CFG_SEL_DIV_3_0                                             (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0E_CFG_SEL_DIV_3_0(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0E . CFG_PMAA_CENTR_CK_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0E_CFG_PMAA_CENTR_CK_PD(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0E_CFG_PMAA_CENTR_CK_PD                                        (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0E_CFG_PMAA_CENTR_CK_PD(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_0F
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_0F                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf00f))

/**
 * \brief
 * PLL loop parameter tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0F . CFG_RSEL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0F_CFG_RSEL_2_0(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0F_CFG_RSEL_2_0                                                (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0F_CFG_RSEL_2_0(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * PLL loop parameter tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_0F . CFG_ICP_BASE_SEL_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_0F_CFG_ICP_BASE_SEL_3_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_0F_CFG_ICP_BASE_SEL_3_0                                        (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_0F_CFG_ICP_BASE_SEL_3_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_10
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_10                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf010))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_10 . CFG_PMAA_CENTR_BITWIDTH_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0                                 (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_10_CFG_PMAA_CENTR_BITWIDTH_2_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Power down buffers in ref clock path
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_10 . CFG_REFCK_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_10_CFG_REFCK_PD(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_10_CFG_REFCK_PD                                                (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_10_CFG_REFCK_PD(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_11
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_11                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf011))

/**
 * \brief
 * PLL loop parameter tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_11 . CFG_ICP_SEL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_11_CFG_ICP_SEL_2_0(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_11_CFG_ICP_SEL_2_0                                             (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_11_CFG_ICP_SEL_2_0(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_11 . CFG_PD_DIV66
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_11_CFG_PD_DIV66(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_11_CFG_PD_DIV66                                                (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_11_CFG_PD_DIV66(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_12
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_12                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf012))

/**
 * \brief
 * VCO current tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_12 . CFG_I_VCO_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_12_CFG_I_VCO_3_0(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_12_CFG_I_VCO_3_0                                               (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_12_CFG_I_VCO_3_0(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_12 . CFG_PD_DIV64
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_12_CFG_PD_DIV64(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_12_CFG_PD_DIV64                                                (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_12_CFG_PD_DIV64(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Switches between On-chip ref clock or External Bump ref clock
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_12 . CFG_JC_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_12_CFG_JC_BYP(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_12_CFG_JC_BYP                                                  (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_12_CFG_JC_BYP(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_12 . CFG_VCO_CAL_DIR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_12_CFG_VCO_CAL_DIR(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_12_CFG_VCO_CAL_DIR                                             (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_12_CFG_VCO_CAL_DIR(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,6,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_13
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_13                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf013))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_13 . CFG_PLL_RESERVE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_13_CFG_PLL_RESERVE_3_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_13_CFG_PLL_RESERVE_3_0                                         (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_13_CFG_PLL_RESERVE_3_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_13 . CFG_JT_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_13_CFG_JT_EN(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_13_CFG_JT_EN                                                   (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_13_CFG_JT_EN(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_14
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_14                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf014))

/**
 * \brief
 * T2 in figure 17 (reset scheme) 00: 30t 01: 10000t 10: 20000t 11: 30000t
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_14 . R_TIME_PLL2CDR_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_14_R_TIME_PLL2CDR_1_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_14_R_TIME_PLL2CDR_1_0                                          (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_14_R_TIME_PLL2CDR_1_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * T4 in figure 17 (reset scheme) 00: 30t 01: 10000t 10: 20000t 11: 30000t
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_14 . R_TIME_TXCAL2TXRX_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_14_R_TIME_TXCAL2TXRX_1_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_14_R_TIME_TXCAL2TXRX_1_0                                       (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_14_R_TIME_TXCAL2TXRX_1_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_15
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_15                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf015))

/**
 * \brief
 * T6 in figure 17 (reset scheme) 00: 30t 01: 1000t 10: 5000t 11: 10000t
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_15 . R_TIME_CTLE2DFE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_15_R_TIME_CTLE2DFE_1_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_15_R_TIME_CTLE2DFE_1_0                                         (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_15_R_TIME_CTLE2DFE_1_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_16
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_16                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf016))

/**
 * \brief
 * Simulation speed up mode enable. 0: no speed up 1: speed up. Note that
 * loss of lock related functions will not be speed up
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_16 . R_HWT_SIMULATION_MODE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_16_R_HWT_SIMULATION_MODE(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_16_R_HWT_SIMULATION_MODE                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_16_R_HWT_SIMULATION_MODE(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_17
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_17                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf017))

/**
 * \brief
 * BIST enable control for all lanes
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_17 . R_BIST_ALL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_17_R_BIST_ALL(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_17_R_BIST_ALL                                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_17_R_BIST_ALL(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * SD25G_LS3, Malibu_25G H4 and L4 Loopback.[DBG] 1:  Enable Loopback, 0:
 * Disable Loopback.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_17 . R_LBSLV_IN_PMAD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_17_R_LBSLV_IN_PMAD(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_17_R_LBSLV_IN_PMAD                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_17_R_LBSLV_IN_PMAD(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_18
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_18                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf018))

/**
 * \brief
 * Reset signal for pll, low active
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_18 . R_PLL_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_18_R_PLL_RSTN(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_18_R_PLL_RSTN                                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_18_R_PLL_RSTN(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_18 . R_PLL_LOL_SET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_18_R_PLL_LOL_SET(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_18_R_PLL_LOL_SET                                               (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_18_R_PLL_LOL_SET(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_18 . R_PLL_LOS_SET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_18_R_PLL_LOS_SET(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_18_R_PLL_LOS_SET                                               (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_18_R_PLL_LOS_SET(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_18 . R_PLL_TP_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_18_R_PLL_TP_SEL_1_0(x)                                         (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_18_R_PLL_TP_SEL_1_0                                            (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_18_R_PLL_TP_SEL_1_0(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_19
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_19                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf019))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_19 . R_CK_RESETB
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_19_R_CK_RESETB(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_19_R_CK_RESETB                                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_19_R_CK_RESETB(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_19 . R_PLL_DLOL_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_19_R_PLL_DLOL_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_19_R_PLL_DLOL_EN                                               (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_19_R_PLL_DLOL_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1A
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1A                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01a))

/**
 * \brief
 * Data width control:000: 10 bit 001: 16 bit 010: 20 bit 011: 32 bit 100:
 * 64 bit
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1A . R_DWIDTHCTRL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_2_0(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_2_0                                            (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_2_0(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Data width/rate control from register or hardward pin.0: cfg control 1:
 * hwt control
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1A . R_DWIDTHCTRL_FROM_HWT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_FROM_HWT(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_FROM_HWT                                       (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1A_R_DWIDTHCTRL_FROM_HWT(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1A . R_MASK_EI_SOURCE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1A_R_MASK_EI_SOURCE(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1A_R_MASK_EI_SOURCE                                            (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1A_R_MASK_EI_SOURCE(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Link based,To select between interface pin control (default) and
 * register control of 1. DFE coefficient control 2. Power down control 3.
 * 50ohm term control 4. Eye scan enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1A . R_REG_MANUAL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1A_R_REG_MANUAL(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1A_R_REG_MANUAL                                                (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1A_R_REG_MANUAL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,6,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1B
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1B                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01b))

/**
 * \brief
 * Deassert ppm control default :10'h032=50
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1B . R_PLL_LOL_DF1_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1B_R_PLL_LOL_DF1_7_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1B_R_PLL_LOL_DF1_7_0                                           (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1B_R_PLL_LOL_DF1_7_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1C
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1C                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01c))

/**
 * \brief
 * Deassert ppm control default :10'h032=50
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1C . R_PLL_LOL_DF1_9_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1C_R_PLL_LOL_DF1_9_8(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1C_R_PLL_LOL_DF1_9_8                                           (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1C_R_PLL_LOL_DF1_9_8(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1D
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1D                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01d))

/**
 * \brief
 * Assert ppm control default :10'h0c8=200
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1D . R_PLL_LOL_DF2_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1D_R_PLL_LOL_DF2_7_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1D_R_PLL_LOL_DF2_7_0                                           (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1D_R_PLL_LOL_DF2_7_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1E
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1E                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01e))

/**
 * \brief
 * Assert ppm control default :10'h0c8=200
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1E . R_PLL_LOL_DF2_9_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1E_R_PLL_LOL_DF2_9_8(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1E_R_PLL_LOL_DF2_9_8                                           (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1E_R_PLL_LOL_DF2_9_8(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_0:CMU_1F
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_1F                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf01f))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1F . R_RXEI_FILTER_FACTOR_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1F_R_RXEI_FILTER_FACTOR_1_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1F_R_RXEI_FILTER_FACTOR_1_0                                    (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1F_R_RXEI_FILTER_FACTOR_1_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_1F . R_MULTI_LANE_MODE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_1F_R_MULTI_LANE_MODE(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_1F_R_MULTI_LANE_MODE                                           (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_1F_R_MULTI_LANE_MODE(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * Register Group: \a LINE_PMA_8BIT:CMU_GRP_1
 *
 * Register group for registers 0x21 to 0x32
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_21
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_21                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf021))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_21 . R_BIST_PATTERN_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_21_R_BIST_PATTERN_7_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_21_R_BIST_PATTERN_7_0                                          (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_21_R_BIST_PATTERN_7_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_22
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_22                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf022))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_22 . R_BIST_PATTERN_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_22_R_BIST_PATTERN_15_8(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_22_R_BIST_PATTERN_15_8                                         (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_22_R_BIST_PATTERN_15_8(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_23
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_23                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf023))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_23 . R_BIST_PATTERN_23_16
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_23_R_BIST_PATTERN_23_16(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_23_R_BIST_PATTERN_23_16                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_23_R_BIST_PATTERN_23_16(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_24
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_24                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf024))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_24 . R_BIST_PATTERN_31_24
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_24_R_BIST_PATTERN_31_24(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_24_R_BIST_PATTERN_31_24                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_24_R_BIST_PATTERN_31_24(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_25
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_25                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf025))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_25 . R_BIST_PATTERN_39_32
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_25_R_BIST_PATTERN_39_32(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_25_R_BIST_PATTERN_39_32                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_25_R_BIST_PATTERN_39_32(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_26
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_26                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf026))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_26 . R_BIST_PATTERN_47_40
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_26_R_BIST_PATTERN_47_40(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_26_R_BIST_PATTERN_47_40                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_26_R_BIST_PATTERN_47_40(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_27
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_27                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf027))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_27 . R_BIST_PATTERN_55_48
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_27_R_BIST_PATTERN_55_48(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_27_R_BIST_PATTERN_55_48                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_27_R_BIST_PATTERN_55_48(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_28
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_28                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf028))

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_28 . R_BIST_PATTERN_63_56
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_28_R_BIST_PATTERN_63_56(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_28_R_BIST_PATTERN_63_56                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_28_R_BIST_PATTERN_63_56(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_29
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_29                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf029))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_29 . R_TXEI_DLY_SEL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_29_R_TXEI_DLY_SEL_2_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_29_R_TXEI_DLY_SEL_2_0                                          (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_29_R_TXEI_DLY_SEL_2_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_29 . R_DISABLE_EI_FILTER
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_29_R_DISABLE_EI_FILTER(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_29_R_DISABLE_EI_FILTER                                         (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_29_R_DISABLE_EI_FILTER(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Reset RX FIFO if RXEI is asserted:0 : disable,1 : enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_29 . R_RXEI_FIFO_RST_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_29_R_RXEI_FIFO_RST_EN(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_29_R_RXEI_FIFO_RST_EN                                          (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_29_R_RXEI_FIFO_RST_EN(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Refer to hwt_fom_sel
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_29 . R_FOM_SEL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_29_R_FOM_SEL(x)                                                (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_29_R_FOM_SEL                                                   (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_29_R_FOM_SEL(x)                                                (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_29 . R_INTBIST_RESULT_SEL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_29_R_INTBIST_RESULT_SEL(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_29_R_INTBIST_RESULT_SEL                                        (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_29_R_INTBIST_RESULT_SEL(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2A
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2A                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2A . R_DBG_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2A_R_DBG_SEL_1_0(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2A_R_DBG_SEL_1_0                                               (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2A_R_DBG_SEL_1_0(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2A . R_DBG_LINK_LANE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2A_R_DBG_LINK_LANE(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2A_R_DBG_LINK_LANE                                             (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2A_R_DBG_LINK_LANE(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2A . R_DBG_LOL_STATUS
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS                                            (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2A_R_DBG_LOL_STATUS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2B
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2B                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02b))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2B . R_DBG_LANE_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2B_R_DBG_LANE_SEL_1_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2B_R_DBG_LANE_SEL_1_0                                          (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2B_R_DBG_LANE_SEL_1_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2B . R_DBG_OBS_SEL_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2B_R_DBG_OBS_SEL_3_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2B_R_DBG_OBS_SEL_3_0                                           (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2B_R_DBG_OBS_SEL_3_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2C
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2C                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02c))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2C . R_PLL_LOL_ASSERT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2C_R_PLL_LOL_ASSERT_7_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2C_R_PLL_LOL_ASSERT_7_0                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2C_R_PLL_LOL_ASSERT_7_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2D
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2D                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2D . R_PLL_LOL_ASSERT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2D_R_PLL_LOL_ASSERT_15_8(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2D_R_PLL_LOL_ASSERT_15_8                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2D_R_PLL_LOL_ASSERT_15_8(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2E
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2E                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02e))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2E . R_PLL_LOL_DEASSERT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2E_R_PLL_LOL_DEASSERT_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2E_R_PLL_LOL_DEASSERT_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2E_R_PLL_LOL_DEASSERT_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_2F
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_2F                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf02f))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_2F . R_PLL_LOL_DEASSERT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_2F_R_PLL_LOL_DEASSERT_15_8(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_2F_R_PLL_LOL_DEASSERT_15_8                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_2F_R_PLL_LOL_DEASSERT_15_8(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_30
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_30                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf030))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_30 . R_TXFIFO_CK_DIV_PMAD_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0                                    (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_30 . R_RXFIFO_CK_DIV_PMAD_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0                                    (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_31
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_31                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf031))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_31 . CFG_COMMON_RESERVE_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_31_CFG_COMMON_RESERVE_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_31_CFG_COMMON_RESERVE_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_31_CFG_COMMON_RESERVE_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_1:CMU_32
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_32                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf032))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_32 . CFG_COMMON_RESERVE_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_32_CFG_COMMON_RESERVE_15_8(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_32_CFG_COMMON_RESERVE_15_8                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_32_CFG_COMMON_RESERVE_15_8(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a LINE_PMA_8BIT:CMU_GRP_2
 *
 * Register group for registers 0x40 to 0x4C
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_40
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_40                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf040))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_CKSKEW_CTRL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_CKSKEW_CTRL(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_CKSKEW_CTRL                                          (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_CKSKEW_CTRL(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_ISCAN_HOLD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_ISCAN_HOLD(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_ISCAN_HOLD                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_ISCAN_HOLD(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_PD_CLK
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_PD_CLK(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_PD_CLK                                               (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_PD_CLK(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_TXCAL_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_EN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_EN                                             (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_EN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_TXCAL_MAN_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_MAN_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_MAN_EN                                         (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_MAN_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_40 . L0_CFG_TXCAL_RST
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_RST(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_RST                                            (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_40_L0_CFG_TXCAL_RST(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_41
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_41                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf041))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_41 . L0_CFG_BW_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_41_L0_CFG_BW_1_0(x)                                            (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_41_L0_CFG_BW_1_0                                               (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_41_L0_CFG_BW_1_0(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_42
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_42                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf042))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_42 . L0_CFG_PHASE_MAN_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_42_L0_CFG_PHASE_MAN_4_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_42_L0_CFG_PHASE_MAN_4_0                                        (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_42_L0_CFG_PHASE_MAN_4_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_43
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_43                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf043))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_43 . L0_CFG_QUAD_MAN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_43_L0_CFG_QUAD_MAN(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_43_L0_CFG_QUAD_MAN                                             (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_43_L0_CFG_QUAD_MAN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_44
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_44                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf044))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_44 . L0_CFG_TXCAL_SHIFT_CODE_5_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0                                 (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_44_L0_CFG_TXCAL_SHIFT_CODE_5_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_45
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_45                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf045))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_45 . L0_CFG_TX_RESERVE_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_45_L0_CFG_TX_RESERVE_7_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_45_L0_CFG_TX_RESERVE_7_0                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_45_L0_CFG_TX_RESERVE_7_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_46
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_46                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf046))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_46 . L0_CFG_TX_RESERVE_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_46_L0_CFG_TX_RESERVE_15_8(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_46_L0_CFG_TX_RESERVE_15_8                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_46_L0_CFG_TX_RESERVE_15_8(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_47
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_47                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf047))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_47 . L0_CFG_ITX_IPCML_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0                                   (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_47 . L0_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0                                (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_48
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_48                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf048))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_48 . L0_CFG_ITX_VC_DRIVER_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0                                    (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_48_L0_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_48 . L0_CFG_TX_PREDIV_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_48_L0_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_48_L0_CFG_TX_PREDIV_1_0                                        (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_48_L0_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_49
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_49                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf049))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_49 . L2_CFG_ITX_IPCML_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0                                   (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_49 . L2_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0                                (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_49_L2_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_4A
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_4A                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf04a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4A . L2_CFG_ITX_VC_DRIVER_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0                                    (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4A_L2_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4A . L2_CFG_TX_PREDIV_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4A_L2_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4A_L2_CFG_TX_PREDIV_1_0                                        (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4A_L2_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_4B
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_4B                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf04b))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4B . L3_CFG_ITX_IPCML_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0                                   (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPCML_BASE_1_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4B . L3_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0                                (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4B_L3_CFG_ITX_IPDRIVER_BASE_2_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_2:CMU_4C
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_4C                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf04c))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4C . L3_CFG_ITX_VC_DRIVER_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0                                    (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4C_L3_CFG_ITX_VC_DRIVER_3_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_4C . L3_CFG_TX_PREDIV_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_4C_L3_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_4C_L3_CFG_TX_PREDIV_1_0                                        (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_4C_L3_CFG_TX_PREDIV_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,2))

/**
 * Register Group: \a LINE_PMA_8BIT:CMU_GRP_3
 *
 * Register group for register 0xC0
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_3:CMU_C0
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_C0                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0, 0xf0c0))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_C0 . READ_VCO_CTUNE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_C0_READ_VCO_CTUNE_3_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_C0_READ_VCO_CTUNE_3_0                                          (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_C0_READ_VCO_CTUNE_3_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Loss of lock (PLL)
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_C0 . PLL_LOL_UDL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_C0_PLL_LOL_UDL(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_C0_PLL_LOL_UDL                                                 (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_C0_PLL_LOL_UDL(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * Register Group: \a LINE_PMA_8BIT:CMU_GRP_4
 *
 * Register group for register 0xFF
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:CMU_GRP_4:CMU_FF
 */
#define LAN80XX_LINE_PMA_8BIT_CMU_FF                                                                (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0, 0xf0ff))

/**
 * \brief
 * Index for register access. When the index value is 0xFF, the COM
 * register space is active. When the index value is 0x00, the LANE
 * register space is active.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_CMU_FF . REGISTER_TABLE_INDEX
 */
#define  LAN80XX_F_LINE_PMA_8BIT_CMU_FF_REGISTER_TABLE_INDEX(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_CMU_FF_REGISTER_TABLE_INDEX                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_CMU_FF_REGISTER_TABLE_INDEX(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a LINE_PMA_8BIT:LANE_GRP_0
 *
 * Register group for registers 0x00 to 0x47
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_00
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_00                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf100))

/**
 * \brief
 * TX driver amplitude fine tuning
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_00 . LN_CFG_ITX_VC_DRIVER_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(x)                                (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0                                   (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(x)                                (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_00 . LN_CFG_ITX_IPCML_BASE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0(x)                               (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0                                  (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_00_LN_CFG_ITX_IPCML_BASE_1_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_01
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_01                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf101))

/**
 * \brief
 * 0:1000m 1:1200m 2: 900m 3: 800m 4: 700m 5: 500m 6: 400m 7: 600m
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_01 . LN_CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(x)                            (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0                               (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_01_LN_CFG_ITX_IPDRIVER_BASE_2_0(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * TX sub rate control
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_01 . LN_CFG_TX_PREDIV_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_01_LN_CFG_TX_PREDIV_1_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_01_LN_CFG_TX_PREDIV_1_0                                       (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_01_LN_CFG_TX_PREDIV_1_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_02
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_02                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf102))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_02 . LN_CFG_CKSKEW_CTRL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_02_LN_CFG_CKSKEW_CTRL(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_02_LN_CFG_CKSKEW_CTRL                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_02_LN_CFG_CKSKEW_CTRL(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_03
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_03                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf103))

/**
 * \brief
 * 1st stage post-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_03 . LN_CFG_TAP_DLY_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0                                         (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_03_LN_CFG_TAP_DLY_4_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_04
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_04                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf104))

/**
 * \brief
 * For Malibu-25G H1/L1 loopback, LN_CFG_TX2RX_LP_EN and LN_CFG_TXLB_EN
 * must both be set to 1
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_TX2RX_LP_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_TX2RX_LP_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * For Malibu-25G H6/L6 Loopback, LN_CFG_RX2TX_LP_EN and LN_CFG_RXLB_EN
 * must both be set to 1, and LN_CFG_CDRCK_EN must be set to 0. For
 * Malibu-25G H5/L5 Loopback, LN_CFG_RX2TX_LP_EN, LN_CFG_RXLB_EN and
 * LN_CFG_CDRCK_EN must all be set to 1
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_RX2TX_LP_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_RX2TX_LP_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Power down CML circuits
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_PD_CML
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CML(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CML                                              (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CML(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Power down clock circuits
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_PD_CLK
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CLK(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CLK                                              (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_CLK(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Power down TX driver
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_PD_DRIVER
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER                                           (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_PD_DRIVER(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * TX data path setting. Should set to 1.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_04 . LN_CFG_TAP_MAIN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN                                            (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_04_LN_CFG_TAP_MAIN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_05
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_05                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf105))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_05 . LN_CFG_TAP_DLY2_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_05_LN_CFG_TAP_DLY2_3_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_05_LN_CFG_TAP_DLY2_3_0                                        (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_05_LN_CFG_TAP_DLY2_3_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_05 . LN_CFG_BW_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_05_LN_CFG_BW_1_0(x)                                           (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_05_LN_CFG_BW_1_0                                              (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_05_LN_CFG_BW_1_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_06
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_06                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf106))

/**
 * \brief
 * Enable TX data path control.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_06 . LN_CFG_EN_MAIN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN                                             (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_06_LN_CFG_EN_MAIN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Pre-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_06 . LN_CFG_TAP_ADV_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0                                         (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_06_LN_CFG_TAP_ADV_3_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_07
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_07                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf107))

/**
 * \brief
 * Enable pre-equalization control of TX.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_07 . LN_CFG_EN_ADV
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_ADV(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_ADV                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_ADV(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_07 . LN_CFG_EN_DLY2
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY2(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY2                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY2(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable 1st stage post-equalization control of TX.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_07 . LN_CFG_EN_DLY
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY                                              (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_07_LN_CFG_EN_DLY(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_08
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_08                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf108))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_08 . LN_CFG_PHASE_MAN_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_08_LN_CFG_PHASE_MAN_4_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_08_LN_CFG_PHASE_MAN_4_0                                       (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_08_LN_CFG_PHASE_MAN_4_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_09
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_09                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf109))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_09 . LN_CFG_TXCAL_VALID_SEL_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(x)                              (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0                                 (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_09_LN_CFG_TXCAL_VALID_SEL_3_0(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0A
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0A                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0A . LN_CFG_TXCAL_SHIFT_CODE_5_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(x)                             (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0                                (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0A_LN_CFG_TXCAL_SHIFT_CODE_5_0(x)                             (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0B
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0B                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10b))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0B . LN_CFG_TXCAL_MAN_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_MAN_EN(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_MAN_EN                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_MAN_EN(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0B . LN_CFG_TXCAL_RST
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_RST(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_RST                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0B_LN_CFG_TXCAL_RST(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0B . LN_CFG_QUAD_MAN_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0B_LN_CFG_QUAD_MAN_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0B_LN_CFG_QUAD_MAN_1_0                                        (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0B_LN_CFG_QUAD_MAN_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0C
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0C                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10c))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0C . LN_CFG_PMA_TX_CK_BITWIDTH_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(x)                           (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0                              (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(x)                           (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0C . LN_CFG_TXCAL_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0C_LN_CFG_TXCAL_EN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0C_LN_CFG_TXCAL_EN                                            (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0C_LN_CFG_TXCAL_EN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0C . LN_CFG_RXTERM_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0C_LN_CFG_RXTERM_PD(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0C_LN_CFG_RXTERM_PD                                           (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0C_LN_CFG_RXTERM_PD(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0D
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0D                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0D . LN_CFG_RXTERM_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_RXTERM_2_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_RXTERM_2_0                                          (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0D_LN_CFG_RXTERM_2_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * PMAA FIFO clock reset
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0D . LN_CFG_RSTN_DIV5_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_RSTN_DIV5_8(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_RSTN_DIV5_8                                         (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0D_LN_CFG_RSTN_DIV5_8(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0D . LN_CFG_SUMMER_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN                                           (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0D_LN_CFG_SUMMER_EN(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0D . LN_CFG_DMUX_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD                                             (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0D_LN_CFG_DMUX_PD(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * DFE related clock enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0D . LN_CFG_DFECK_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN                                            (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0D_LN_CFG_DFECK_EN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0E
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0E                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10e))

/**
 * \brief
 * Eye scan enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0E . LN_CFG_ISCAN_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0E_LN_CFG_ISCAN_EN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0E . LN_CFG_DMUX_CLK_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0E_LN_CFG_DMUX_CLK_PD(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Enable DFE digital adaptation
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0E . LN_CFG_EN_DFEDIG
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0E_LN_CFG_EN_DFEDIG(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Time constant for DFE adaptation
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0E . LN_CFG_DFEDIG_M_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0E_LN_CFG_DFEDIG_M_2_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0E_LN_CFG_DFEDIG_M_2_0                                        (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0E_LN_CFG_DFEDIG_M_2_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_0F
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_0F                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf10f))

/**
 * \brief
 * DFE tap enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_0F . LN_CFG_DFETAP_EN_5_1
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1                                       (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_0F_LN_CFG_DFETAP_EN_5_1(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_10
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_10                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf110))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_10 . LN_CFG_DFE_DLEV_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_10_LN_CFG_DFE_DLEV_6_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_10_LN_CFG_DFE_DLEV_6_0                                        (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_10_LN_CFG_DFE_DLEV_6_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_11
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_11                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf111))

/**
 * \brief
 * Bypass DFE coefficient
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_11 . LN_CFG_DFE_BYP_H5_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0                                      (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H5_3_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Bypass DFE coefficient
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_11 . LN_CFG_DFE_BYP_H4_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0                                      (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_11_LN_CFG_DFE_BYP_H4_3_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_12
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_12                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf112))

/**
 * \brief
 * Bypass DFE coefficient
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_12 . LN_CFG_DFE_BYP_H3_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_12_LN_CFG_DFE_BYP_H3_3_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_12_LN_CFG_DFE_BYP_H3_3_0                                      (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_12_LN_CFG_DFE_BYP_H3_3_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_13
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_13                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf113))

/**
 * \brief
 * Bypass DFE coefficient
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_13 . LN_CFG_DFE_BYP_H2_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_13_LN_CFG_DFE_BYP_H2_4_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_13_LN_CFG_DFE_BYP_H2_4_0                                      (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_13_LN_CFG_DFE_BYP_H2_4_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_14
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_14                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf114))

/**
 * \brief
 * Bypass DFE coefficient
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_14 . LN_CFG_DFE_BYP_H1_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_14_LN_CFG_DFE_BYP_H1_4_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_14_LN_CFG_DFE_BYP_H1_4_0                                      (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_14_LN_CFG_DFE_BYP_H1_4_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_15
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_15                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf115))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_15 . LN_CFG_DFEDIG_BYP_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_15_LN_CFG_DFEDIG_BYP_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_16
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_16                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf116))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_16 . LN_CFG_DFEDIG_BYP_10_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_16_LN_CFG_DFEDIG_BYP_10_8(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_16_LN_CFG_DFEDIG_BYP_10_8                                     (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_16_LN_CFG_DFEDIG_BYP_10_8(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_17
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_17                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf117))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_17 . LN_CFG_COMP_NUM_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_17_LN_CFG_COMP_NUM_SEL_1_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_17_LN_CFG_COMP_NUM_SEL_1_0                                    (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_17_LN_CFG_COMP_NUM_SEL_1_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_18
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_18                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf118))

/**
 * \brief
 * For Malibu-25G H6/L6 Loopback, LN_CFG_RX2TX_LP_EN and LN_CFG_RXLB_EN
 * must both be set to 1, and LN_CFG_CDRCK_EN must be set to 0. For
 * Malibu-25G H5/L5 Loopback,LN_CFG_RX2TX_LP_EN, LN_CFG_RXLB_EN and
 * LN_CFG_CDRCK_EN must all be set to 1.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_18 . LN_CFG_CDRCK_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_18_LN_CFG_CDRCK_EN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_18 . LN_CFG_ADD_VOLT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT                                            (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_18_LN_CFG_ADD_VOLT(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_18 . LN_CFG_MAN_VOLT_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_MAN_VOLT_EN(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_MAN_VOLT_EN                                         (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_18_LN_CFG_MAN_VOLT_EN(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Power down error amplifier for DFE adaptation
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_18 . LN_CFG_ERRAMP_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD                                           (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_18_LN_CFG_ERRAMP_PD(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * See application note
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_18 . LN_CFG_RXDIV_SEL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_18_LN_CFG_RXDIV_SEL_2_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_18_LN_CFG_RXDIV_SEL_2_0                                       (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_18_LN_CFG_RXDIV_SEL_2_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_19
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_19                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf119))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_DCDR_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD                                             (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_DCDR_PD(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_ECDR_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_ECDR_PD(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_ISCAN_SEL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_ISCAN_SEL(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * For Malibu-25G H1/L1 Loopback, LN_CFG_RX2TX_LP_EN and LN_CFG_TXLB_EN
 * must both set to 1.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_TXLB_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN                                             (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_TXLB_EN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Power up RX regulator
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_RX_REG_PU
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU                                           (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_PU(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Bypass RX regulator
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_RX_REG_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_BYP(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_BYP                                          (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_RX_REG_BYP(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_PD_RMS_DET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET                                          (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_RMS_DET(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Power down CTLE
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_19 . LN_CFG_PD_CTLE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE                                             (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_19_LN_CFG_PD_CTLE(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1A
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1A                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1A . LN_CFG_CTLE_TP_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1A_LN_CFG_CTLE_TP_EN(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1A_LN_CFG_CTLE_TP_EN                                          (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1A_LN_CFG_CTLE_TP_EN(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1A . LN_CFG_CDR_KF_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1A_LN_CFG_CDR_KF_2_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1A_LN_CFG_CDR_KF_2_0                                          (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1A_LN_CFG_CDR_KF_2_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1B
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1B                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11b))

/**
 * \brief
 * CDR BW setting
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1B . LN_CFG_CDR_M_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1B_LN_CFG_CDR_M_7_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1B_LN_CFG_CDR_M_7_0                                           (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1B_LN_CFG_CDR_M_7_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1C
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1C                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11c))

/**
 * \brief
 * CDR resetn
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1C . LN_CFG_CDR_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1C_LN_CFG_CDR_RSTN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Power down DFE analog circuits
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1C . LN_CFG_DFE_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD                                              (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFE_PD(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1C . LN_CFG_DFEDMX_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD                                           (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1C_LN_CFG_DFEDMX_PD(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * CTLE C setting
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1C . LN_CFG_EQC_FORCE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0                                       (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1C_LN_CFG_EQC_FORCE_3_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1D
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1D                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_ISCAN_EXT_OVR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_EXT_OVR(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_EXT_OVR                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_EXT_OVR(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_ISCAN_HOLD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_HOLD(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_HOLD                                          (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_HOLD(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Eye scan resetn
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_ISCAN_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_RSTN(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_RSTN                                          (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_ISCAN_RSTN(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_AGC_ADPT_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_AGC_ADPT_BYP(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_AGC_ADPT_BYP                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_AGC_ADPT_BYP(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_PHID_1T
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_PHID_1T(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_PHID_1T                                             (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_PHID_1T(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Required for DFE
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_PI_DFE_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN                                           (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_DFE_EN(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_PI_EXT_OVR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_EXT_OVR(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_EXT_OVR                                          (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_EXT_OVR(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Place CDR in "holding" state Recovered clock does not track data
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1D . LN_CFG_PI_HOLD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_HOLD(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_HOLD                                             (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1D_LN_CFG_PI_HOLD(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1E
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1E                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11e))

/**
 * \brief
 * PI step size
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1E . LN_CFG_PI_STEPS_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_PI_STEPS_1_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_PI_STEPS_1_0                                        (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1E_LN_CFG_PI_STEPS_1_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * For Malibu-25G H6/L6 Loopback, LN_CFG_RX2TX_LP_EN and LN_CFG_RXLB_EN
 * must both be set to 1, and LN_CFG_CDRCK_EN must be set to 0. For
 * Malibu-25G H5/L5 Loopback,LN_CFG_RX2TX_LP_EN, LN_CFG_RXLB_EN and
 * LN_CFG_CDRCK_EN must all be set to 1.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1E . LN_CFG_RXLB_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN                                             (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1E_LN_CFG_RXLB_EN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Required.  Set to 1 in normal mode
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1E . LN_CFG_SUM_SETCM_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_SUM_SETCM_EN(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_SUM_SETCM_EN                                        (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1E_LN_CFG_SUM_SETCM_EN(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1E . LN_CFG_R_OFFSET_DIR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_R_OFFSET_DIR(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_R_OFFSET_DIR                                        (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1E_LN_CFG_R_OFFSET_DIR(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1E . LN_CFG_PMAD_CK_PD
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD                                          (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1E_LN_CFG_PMAD_CK_PD(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_1F
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_1F                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf11f))

/**
 * \brief
 * CTLE "R" bypass
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1F . LN_CFG_EQR_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1F_LN_CFG_EQR_BYP(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1F_LN_CFG_EQR_BYP                                             (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1F_LN_CFG_EQR_BYP(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_1F . LN_CFG_OS_MAN_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_1F_LN_CFG_OS_MAN_EN(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_1F_LN_CFG_OS_MAN_EN                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_1F_LN_CFG_OS_MAN_EN(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_20
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_20                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf120))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_20 . LN_CFG_MAN_VOLT_SEL_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0                                    (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_20_LN_CFG_MAN_VOLT_SEL_6_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_21
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_21                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf121))

/**
 * \brief
 * VGA code bypass
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_21 . LN_CFG_VGA_CTRL_BYP_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0                                    (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_22
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_22                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf122))

/**
 * \brief
 * CTLE "R" code
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_22 . LN_CFG_EQR_FORCE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0                                       (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_22_LN_CFG_EQR_FORCE_3_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_23
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_23                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf123))

/**
 * \brief
 * CDR phase interpolator enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_23 . LN_CFG_PI_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_23_LN_CFG_PI_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_23_LN_CFG_PI_EN                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_23_LN_CFG_PI_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * VGA code bypass
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_23 . LN_CFG_VGA_BYP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_23_LN_CFG_VGA_BYP(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_23_LN_CFG_VGA_BYP                                             (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_23_LN_CFG_VGA_BYP(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_24
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_24                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf124))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_24 . LN_CFG_OS_5_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_24_LN_CFG_OS_5_0(x)                                           (LAN80XX_ENCODE_BITFIELD(x,0,6))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_24_LN_CFG_OS_5_0                                              (LAN80XX_ENCODE_BITMASK(0,6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_24_LN_CFG_OS_5_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,6))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_25
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_25                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf125))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_25 . LN_CFG_INIT_POS_ISCAN_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0                                  (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_25_LN_CFG_INIT_POS_ISCAN_6_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_26
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_26                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf126))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_26 . LN_CFG_INIT_POS_IPI_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_26_LN_CFG_INIT_POS_IPI_6_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_26_LN_CFG_INIT_POS_IPI_6_0                                    (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_26_LN_CFG_INIT_POS_IPI_6_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_27
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_27                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf127))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_27 . LN_CFG_INIT_POS_QPI_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_27_LN_CFG_INIT_POS_QPI_6_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_27_LN_CFG_INIT_POS_QPI_6_0                                    (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_27_LN_CFG_INIT_POS_QPI_6_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_28
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_28                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf128))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_28 . LN_CFG_ISCAN_MODE_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_28_LN_CFG_ISCAN_MODE_EN(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_28 . LN_CFG_RX_SSC_LH
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SSC_LH(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SSC_LH                                           (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SSC_LH(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Fast eye scan method.0:Calculate central phase 1:Calculate all phase
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_28 . LN_CFG_FIGMERIT_SEL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_28_LN_CFG_FIGMERIT_SEL(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_28_LN_CFG_FIGMERIT_SEL                                        (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_28_LN_CFG_FIGMERIT_SEL(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * full/subrate frequency selection:00: full 01: 1/2 10: 1/4 11: 1/8
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_28 . LN_CFG_RX_SUBRATE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SUBRATE_2_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SUBRATE_2_0                                      (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_28_LN_CFG_RX_SUBRATE_2_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_29
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_29                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf129))

/**
 * \brief
 * 2nd order CDR setting.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_29 . LN_CFG_FILTER2ND_YZ_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_29_LN_CFG_FILTER2ND_YZ_6_0(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_29_LN_CFG_FILTER2ND_YZ_6_0                                    (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_29_LN_CFG_FILTER2ND_YZ_6_0(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2A
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2A                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12a))

/**
 * \brief
 * 2nd order CDR tracking setting
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2A . LN_CFG_PI_FLOOP_STEPS_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0(x)                               (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0                                  (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2A_LN_CFG_PI_FLOOP_STEPS_2_0(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2A . LN_CFG_DISLOL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2A_LN_CFG_DISLOL(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2A_LN_CFG_DISLOL                                              (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2A_LN_CFG_DISLOL(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2B
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2B                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12b))

/**
 * \brief
 * Phase interpolator bandwidth setting,data rate dependent
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2B . LN_CFG_PI_BW_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2B_LN_CFG_PI_BW_3_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2B_LN_CFG_PI_BW_3_0                                           (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2B_LN_CFG_PI_BW_3_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2B . LN_CFG_RSTN_DMUX_SUBR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_DMUX_SUBR(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_DMUX_SUBR                                      (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_DMUX_SUBR(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2B . LN_CFG_RSTN_TXDUPU
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_TXDUPU(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_TXDUPU                                         (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2B_LN_CFG_RSTN_TXDUPU(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2C
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2C                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12c))

/**
 * \brief
 * full/subrate frequency selection:00: full 01: 1/2 10: 1/4 11: 1/8
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2C . LN_CFG_TX_SUBRATE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2C_LN_CFG_TX_SUBRATE_2_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2C_LN_CFG_TX_SUBRATE_2_0                                      (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2C_LN_CFG_TX_SUBRATE_2_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Disable 2nd order CDR
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2C . LN_CFG_DIS_2NDORDER
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2C_LN_CFG_DIS_2NDORDER(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2C_LN_CFG_DIS_2NDORDER                                        (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2C_LN_CFG_DIS_2NDORDER(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2D
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2D                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2D . LN_CFG_ALOS_THR_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2D_LN_CFG_ALOS_THR_2_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2D_LN_CFG_ALOS_THR_2_0                                        (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2D_LN_CFG_ALOS_THR_2_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2D . LN_CFG_SAT_CNTSEL_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2D_LN_CFG_SAT_CNTSEL_2_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2D_LN_CFG_SAT_CNTSEL_2_0                                      (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2D_LN_CFG_SAT_CNTSEL_2_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2E
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2E                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12e))

/**
 * \brief
 * Fast eye scan enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_EN_FAST_ISCAN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_EN_FAST_ISCAN(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_DIS_SQ
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_SQ(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_SQ                                              (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_SQ(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_PD_SQ
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ                                               (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_PD_SQ(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_DIS_ALOS
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_ALOS(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_ALOS                                            (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_DIS_ALOS(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_RESETN_AGC
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_RESETN_AGC(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_RESETN_AGC                                          (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_RESETN_AGC(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Reset DFE digital adaptation
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_RSTN_DFEDIG
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG                                         (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_RSTN_DFEDIG(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Reset PI controller
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_PI_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_PI_RSTN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_PI_RSTN                                             (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_PI_RSTN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2E . LN_CFG_CTLE_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2E_LN_CFG_CTLE_RSTN(x)                                        (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2E_LN_CFG_CTLE_RSTN                                           (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2E_LN_CFG_CTLE_RSTN(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_2F
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_2F                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf12f))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2F . LN_CFG_XS_MARGIN_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2F_LN_CFG_XS_MARGIN_3_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2F_LN_CFG_XS_MARGIN_3_0                                       (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2F_LN_CFG_XS_MARGIN_3_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_2F . LN_CFG_RX_SP_CTLE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_2F_LN_CFG_RX_SP_CTLE_1_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_2F_LN_CFG_RX_SP_CTLE_1_0                                      (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_2F_LN_CFG_RX_SP_CTLE_1_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_30
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_30                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf130))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_30 . LN_CFG_ISEL_CTLE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_30_LN_CFG_ISEL_CTLE_1_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_30_LN_CFG_ISEL_CTLE_1_0                                       (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_30_LN_CFG_ISEL_CTLE_1_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_30 . LN_CFG_RX_REG_VSEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_30_LN_CFG_RX_REG_VSEL_1_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_30_LN_CFG_RX_REG_VSEL_1_0                                     (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_30_LN_CFG_RX_REG_VSEL_1_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_31
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_31                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf131))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_31 . LN_CFG_AGC_CNT_SEL_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_31_LN_CFG_AGC_CNT_SEL_1_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_31_LN_CFG_AGC_CNT_SEL_1_0                                     (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_31_LN_CFG_AGC_CNT_SEL_1_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_31 . LN_CFG_CTLE_TP_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_31_LN_CFG_CTLE_TP_2_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_31_LN_CFG_CTLE_TP_2_0                                         (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_31_LN_CFG_CTLE_TP_2_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_32
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_32                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf132))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_32 . LN_CFG_AGC_VPP_THR_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_32_LN_CFG_AGC_VPP_THR_2_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_32_LN_CFG_AGC_VPP_THR_2_0                                     (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_32_LN_CFG_AGC_VPP_THR_2_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_32 . LN_CFG_CTLE_M_THR_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_32_LN_CFG_CTLE_M_THR_1_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_32_LN_CFG_CTLE_M_THR_1_0                                      (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_32_LN_CFG_CTLE_M_THR_1_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_33
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_33                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf133))

/**
 * \brief
 * BIST enable signal
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_33 . LN_R_BIST_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_33_LN_R_BIST_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_33_LN_R_BIST_EN                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_33_LN_R_BIST_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * BIST error injection enable
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_33 . LN_R_BIST_ERRINJEC
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_33_LN_R_BIST_ERRINJEC(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_33_LN_R_BIST_ERRINJEC                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_33_LN_R_BIST_ERRINJEC(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * BIST pattern selection
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_33 . LN_R_BIST_MODE_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_33_LN_R_BIST_MODE_2_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,4,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_33_LN_R_BIST_MODE_2_0                                         (LAN80XX_ENCODE_BITMASK(4,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_33_LN_R_BIST_MODE_2_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,3))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_34
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_34                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf134))

/**
 * \brief
 * BIST result compare enable.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_34 . LN_R_BIST_CHK
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * 1: bist_err will assert if rx all zero data in PRBS mode.0: Treat all
 * zero data input as correct data Note: r_bist_chk_zero must be set after
 * r_bist_ok is asserted.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_34 . LN_R_BIST_CHK_ZERO
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK_ZERO(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK_ZERO                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_34_LN_R_BIST_CHK_ZERO(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * 1: bist_err counter will stop when reaching 0xffff_ffff 0: bist_err
 * counter will run continuously, will not saturate.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_34 . LN_R_BIST_ERRSTOP
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_34_LN_R_BIST_ERRSTOP(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_34_LN_R_BIST_ERRSTOP                                          (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_34_LN_R_BIST_ERRSTOP(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_34 . LN_R_BIST_RXERR_LBK
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_34_LN_R_BIST_RXERR_LBK(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_34_LN_R_BIST_RXERR_LBK                                        (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_34_LN_R_BIST_RXERR_LBK(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * 0 : non free running mode 1 : free running mode
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_34 . LN_R_FREE_RUN_MODE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_34_LN_R_FREE_RUN_MODE(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_34_LN_R_FREE_RUN_MODE                                         (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_34_LN_R_FREE_RUN_MODE(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_35
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_35                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf135))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_35 . LN_R_TIME_DEASSERT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_35_LN_R_TIME_DEASSERT_7_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_35_LN_R_TIME_DEASSERT_7_0                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_35_LN_R_TIME_DEASSERT_7_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_36
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_36                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf136))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_36 . LN_R_TIME_DEASSERT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_36_LN_R_TIME_DEASSERT_15_8(x)                                 (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_36_LN_R_TIME_DEASSERT_15_8                                    (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_36_LN_R_TIME_DEASSERT_15_8(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_37
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_37                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf137))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_37 . LN_R_TIME_ASSERT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_37_LN_R_TIME_ASSERT_7_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_37_LN_R_TIME_ASSERT_7_0                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_37_LN_R_TIME_ASSERT_7_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_38
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_38                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf138))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_38 . LN_R_TIME_ASSERT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_38_LN_R_TIME_ASSERT_15_8(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_38_LN_R_TIME_ASSERT_15_8                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_38_LN_R_TIME_ASSERT_15_8(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_39
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_39                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf139))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_39 . LN_R_DLOL_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_39_LN_R_DLOL_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_39_LN_R_DLOL_EN                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_39_LN_R_DLOL_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3A
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3A                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13a))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3A . LN_R_DEASSERT_PPM_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3A_LN_R_DEASSERT_PPM_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3A_LN_R_DEASSERT_PPM_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3A_LN_R_DEASSERT_PPM_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3B
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3B                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13b))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3B . LN_R_DEASSERT_PPM_9_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3B_LN_R_DEASSERT_PPM_9_8(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3B_LN_R_DEASSERT_PPM_9_8                                      (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3B_LN_R_DEASSERT_PPM_9_8(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3C
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3C                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13c))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3C . LN_R_ASSERT_PPM_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3C_LN_R_ASSERT_PPM_7_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3C_LN_R_ASSERT_PPM_7_0                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3C_LN_R_ASSERT_PPM_7_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3D
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3D                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13d))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3D . LN_R_ASSERT_PPM_9_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3D_LN_R_ASSERT_PPM_9_8(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3D_LN_R_ASSERT_PPM_9_8                                        (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3D_LN_R_ASSERT_PPM_9_8(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3E
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3E                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13e))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3E . LN_R_DLOS_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3E_LN_R_DLOS_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3E_LN_R_DLOS_EN                                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3E_LN_R_DLOS_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3E . LN_R_LOS_CKONE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3E_LN_R_LOS_CKONE_1_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3E_LN_R_LOS_CKONE_1_0                                         (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3E_LN_R_LOS_CKONE_1_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_3F
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_3F                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf13f))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3F . LN_R_TIME_LOS_2_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3F_LN_R_TIME_LOS_2_0(x)                                       (LAN80XX_ENCODE_BITFIELD(x,0,3))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_TIME_LOS_2_0                                          (LAN80XX_ENCODE_BITMASK(0,3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3F_LN_R_TIME_LOS_2_0(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,0,3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3F . LN_R_ALOS_EN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3F_LN_R_ALOS_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_ALOS_EN                                               (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3F_LN_R_ALOS_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3F . LN_R_LOL_RESET
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3F_LN_R_LOL_RESET(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_LOL_RESET                                             (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3F_LN_R_LOL_RESET(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3F . LN_R_TX_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3F_LN_R_TX_RSTN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_TX_RSTN                                               (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3F_LN_R_TX_RSTN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_3F . LN_R_RX_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_3F_LN_R_RX_RSTN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_3F_LN_R_RX_RSTN                                               (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_3F_LN_R_RX_RSTN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_40
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_40                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf140))

/**
 * \brief
 * TX bit order reversal
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_TX_BIT_REVERSE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_TX_BIT_REVERSE(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_TX_BIT_REVERSE                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_TX_BIT_REVERSE(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * TX polarity invert
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_TX_POL_INV
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_TX_POL_INV(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_TX_POL_INV                                            (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_TX_POL_INV(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * RX bit order reversal
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_RX_BIT_REVERSE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_RX_BIT_REVERSE(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_BIT_REVERSE                                        (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_RX_BIT_REVERSE(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * RX polarity invert
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_RX_POL_INV
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV                                            (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_RX_POL_INV(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * CDR reset
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_CDR_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_CDR_RSTN(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_CDR_RSTN                                              (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_CDR_RSTN(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * DFE reset
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_DFE_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN                                              (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_DFE_RSTN(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_40 . LN_R_CTLE_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_40_LN_R_CTLE_RSTN(x)                                          (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_40_LN_R_CTLE_RSTN                                             (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_40_LN_R_CTLE_RSTN(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,6,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_41
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_41                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf141))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_41 . LN_CFG_TXEI
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_41_LN_CFG_TXEI(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_41_LN_CFG_TXEI                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_41_LN_CFG_TXEI(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_41 . LN_LOL_CLR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_41_LN_LOL_CLR(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_41_LN_LOL_CLR                                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_41_LN_LOL_CLR(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_41 . LN_R_TXCAL_RSTN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_41_LN_R_TXCAL_RSTN(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_41_LN_R_TXCAL_RSTN                                            (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_41_LN_R_TXCAL_RSTN(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_42
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_42                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf142))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_42 . LN_CFG_TX_RESERVE_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_42_LN_CFG_TX_RESERVE_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_42_LN_CFG_TX_RESERVE_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_42_LN_CFG_TX_RESERVE_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_43
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_43                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf143))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_43 . LN_CFG_TX_RESERVE_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_43_LN_CFG_TX_RESERVE_15_8(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_43_LN_CFG_TX_RESERVE_15_8                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_43_LN_CFG_TX_RESERVE_15_8(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_44
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_44                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf144))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_44 . LN_CFG_RX_RESERVE_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_44_LN_CFG_RX_RESERVE_7_0(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_44_LN_CFG_RX_RESERVE_7_0                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_44_LN_CFG_RX_RESERVE_7_0(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_45
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_45                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf145))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_45 . LN_CFG_RX_RESERVE_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_45_LN_CFG_RX_RESERVE_15_8(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_45_LN_CFG_RX_RESERVE_15_8                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_45_LN_CFG_RX_RESERVE_15_8(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_46
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_46                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf146))

/**
 * \brief
 * 0x0000 : Infinite BIST run time
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_46 . LN_R_BIST_TIMER_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_46_LN_R_BIST_TIMER_7_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_46_LN_R_BIST_TIMER_7_0                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_46_LN_R_BIST_TIMER_7_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_0:LANE_47
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_47                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf147))

/**
 * \brief
 * 0x0001 ~ 0xFFFF : BIST run time =(data width/bit rate) *1024*
 * r_bist_timer[15:0]
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_47 . LN_R_BIST_TIMER_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_47_LN_R_BIST_TIMER_15_8(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_47_LN_R_BIST_TIMER_15_8                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_47_LN_R_BIST_TIMER_15_8(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))

/**
 * Register Group: \a LINE_PMA_8BIT:LANE_GRP_1
 *
 * Register group for registers 0xC0 to 0xDE
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C0
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C0                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c0))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C0 . LN_TX_CALX_STAT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C0_LN_TX_CALX_STAT(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C0_LN_TX_CALX_STAT                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C0_LN_TX_CALX_STAT(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C0 . LN_TX_CALY_STAT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C0_LN_TX_CALY_STAT(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C0_LN_TX_CALY_STAT                                            (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C0_LN_TX_CALY_STAT(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C0 . LN_TX_CAL_ERR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C0_LN_TX_CAL_ERR(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C0_LN_TX_CAL_ERR                                              (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C0_LN_TX_CAL_ERR(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C1
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C1                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C1 . LN_TX_PHI_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C1_LN_TX_PHI_4_0(x)                                           (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C1_LN_TX_PHI_4_0                                              (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C1_LN_TX_PHI_4_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C2
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C2                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C2 . LN_TX_QRT_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C2_LN_TX_QRT_1_0(x)                                           (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C2_LN_TX_QRT_1_0                                              (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C2_LN_TX_QRT_1_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C3
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C3                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c3))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C3 . LN_FAST_EYE_SCAN_FAIL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C3_LN_FAST_EYE_SCAN_FAIL(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C3_LN_FAST_EYE_SCAN_FAIL                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C3_LN_FAST_EYE_SCAN_FAIL(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C3 . LN_SQUELCH
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C3_LN_SQUELCH(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C3_LN_SQUELCH                                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C3_LN_SQUELCH(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C4
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C4                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c4))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C4 . LN_PI_DAC_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C4_LN_PI_DAC_7_0(x)                                           (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C4_LN_PI_DAC_7_0                                              (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C4_LN_PI_DAC_7_0(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C5
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C5                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c5))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C5 . LN_PI_DAC_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C5_LN_PI_DAC_15_8(x)                                          (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C5_LN_PI_DAC_15_8                                             (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C5_LN_PI_DAC_15_8(x)                                          (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C6
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C6                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c6))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C6 . LN_PI_DAC_23_16
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C6_LN_PI_DAC_23_16(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C6_LN_PI_DAC_23_16                                            (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C6_LN_PI_DAC_23_16(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C7
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C7                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c7))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C7 . LN_PI_DAC_30_24
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C7_LN_PI_DAC_30_24(x)                                         (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C7_LN_PI_DAC_30_24                                            (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C7_LN_PI_DAC_30_24(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C8
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C8                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c8))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C8 . LN_PI_QRT_CODE_1_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C8_LN_PI_QRT_CODE_1_0(x)                                      (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C8_LN_PI_QRT_CODE_1_0                                         (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C8_LN_PI_QRT_CODE_1_0(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,2))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C8 . LN_VGAR_CODE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C8_LN_VGAR_CODE_3_0(x)                                        (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C8_LN_VGAR_CODE_3_0                                           (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C8_LN_VGAR_CODE_3_0(x)                                        (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_C9
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_C9                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1c9))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_C9 . LN_ALOS
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_C9_LN_ALOS(x)                                                 (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_C9_LN_ALOS                                                    (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_C9_LN_ALOS(x)                                                 (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CA
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CA                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1ca))

/**
 * \brief
 * DFE H1 readback
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CA . LN_H1_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CA_LN_H1_4_0(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CA_LN_H1_4_0                                                  (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CA_LN_H1_4_0(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CB
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CB                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1cb))

/**
 * \brief
 * DFE H2 readback
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CB . LN_H2_4_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CB_LN_H2_4_0(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,5))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CB_LN_H2_4_0                                                  (LAN80XX_ENCODE_BITMASK(0,5))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CB_LN_H2_4_0(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,5))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CC
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CC                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1cc))

/**
 * \brief
 * DFE H3 readback
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CC . LN_H3_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CC_LN_H3_3_0(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CC_LN_H3_3_0                                                  (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CC_LN_H3_3_0(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CD
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CD                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1cd))

/**
 * \brief
 * DFE H4 readback
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CD . LN_H4_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CD_LN_H4_3_0(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CD_LN_H4_3_0                                                  (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CD_LN_H4_3_0(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CE
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CE                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1ce))

/**
 * \brief
 * DFE H5 readback
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CE . LN_H5_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CE_LN_H5_3_0(x)                                               (LAN80XX_ENCODE_BITFIELD(x,0,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CE_LN_H5_3_0                                                  (LAN80XX_ENCODE_BITMASK(0,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CE_LN_H5_3_0(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,0,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_CF
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_CF                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1cf))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_CF . LN_DLEV_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_CF_LN_DLEV_6_0(x)                                             (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_CF_LN_DLEV_6_0                                                (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_CF_LN_DLEV_6_0(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D0
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D0                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d0))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D0 . LN_ISCAN_RESULTS_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D0_LN_ISCAN_RESULTS_7_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D0_LN_ISCAN_RESULTS_7_0                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D0_LN_ISCAN_RESULTS_7_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D1
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D1                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d1))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D1 . LN_ISCAN_RESULTS_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D1_LN_ISCAN_RESULTS_15_8(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D1_LN_ISCAN_RESULTS_15_8                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D1_LN_ISCAN_RESULTS_15_8(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D2
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D2                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d2))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D2 . LN_ISCAN_RESULTS_23_16
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D2_LN_ISCAN_RESULTS_23_16(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D2_LN_ISCAN_RESULTS_23_16                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D2_LN_ISCAN_RESULTS_23_16(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D3
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D3                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d3))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D3 . LN_ISCAN_RESULTS_31_24
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D3_LN_ISCAN_RESULTS_31_24(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D3_LN_ISCAN_RESULTS_31_24                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D3_LN_ISCAN_RESULTS_31_24(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D4
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D4                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d4))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D4 . LN_ISCAN_RESULTS_39_32
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D4_LN_ISCAN_RESULTS_39_32(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D4_LN_ISCAN_RESULTS_39_32                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D4_LN_ISCAN_RESULTS_39_32(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D5
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D5                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d5))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D5 . LN_ISCAN_RESULTS_47_40
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D5_LN_ISCAN_RESULTS_47_40(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D5_LN_ISCAN_RESULTS_47_40                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D5_LN_ISCAN_RESULTS_47_40(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D6
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D6                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d6))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D6 . LN_ISCAN_RESULTS_55_48
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D6_LN_ISCAN_RESULTS_55_48(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D6_LN_ISCAN_RESULTS_55_48                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D6_LN_ISCAN_RESULTS_55_48(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D7
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D7                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d7))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D7 . LN_ISCAN_RESULTS_63_56
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D7_LN_ISCAN_RESULTS_63_56(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D7_LN_ISCAN_RESULTS_63_56                                     (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D7_LN_ISCAN_RESULTS_63_56(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D8
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D8                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d8))

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D8 . LN_ISCAN_RESULTS_64
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D8_LN_ISCAN_RESULTS_64(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D8_LN_ISCAN_RESULTS_64                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D8_LN_ISCAN_RESULTS_64(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_D9
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_D9                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1d9))

/**
 * \brief
 * Eye scan result for single point scan
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_D9 . LN_ISCAN_RESULT
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_D9_LN_ISCAN_RESULT(x)                                         (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_D9_LN_ISCAN_RESULT                                            (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_D9_LN_ISCAN_RESULT(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_DA
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_DA                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1da))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DA . LN_ISCAN_VOLT_STAT_6_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DA_LN_ISCAN_VOLT_STAT_6_0(x)                                  (LAN80XX_ENCODE_BITFIELD(x,0,7))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DA_LN_ISCAN_VOLT_STAT_6_0                                     (LAN80XX_ENCODE_BITMASK(0,7))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DA_LN_ISCAN_VOLT_STAT_6_0(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,7))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_DB
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_DB                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1db))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DB . LN_ISCAN_ERR_CNT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DB_LN_ISCAN_ERR_CNT_7_0(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DB_LN_ISCAN_ERR_CNT_7_0                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DB_LN_ISCAN_ERR_CNT_7_0(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_DC
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_DC                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1dc))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DC . LN_ISCAN_ERR_CNT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DC_LN_ISCAN_ERR_CNT_15_8(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DC_LN_ISCAN_ERR_CNT_15_8                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DC_LN_ISCAN_ERR_CNT_15_8(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_DD
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_DD                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1dd))

/**
 * \brief
 * Eye scan complete
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DD . LN_ISCAN_DONE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE                                              (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DD_LN_ISCAN_DONE(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Read back RXEQ"C"code
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DD . LN_EQC_CODE_3_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DD_LN_EQC_CODE_3_0(x)                                         (LAN80XX_ENCODE_BITFIELD(x,4,4))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DD_LN_EQC_CODE_3_0                                            (LAN80XX_ENCODE_BITMASK(4,4))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DD_LN_EQC_CODE_3_0(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,4,4))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_1:LANE_DE
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_DE                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1de))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DE . LN_LOL_UDL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DE_LN_LOL_UDL(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DE_LN_LOL_UDL                                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DE_LN_LOL_UDL(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DE . LN_LOL
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DE_LN_LOL(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DE_LN_LOL                                                     (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DE_LN_LOL(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DE . LN_PMA2PCS_RXEI_FILTERED
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DE_LN_PMA2PCS_RXEI_FILTERED(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DE_LN_PMA2PCS_RXEI_FILTERED                                   (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DE_LN_PMA2PCS_RXEI_FILTERED(x)                                (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Internal use
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_DE . LN_PMA_RXEI
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_DE_LN_PMA_RXEI(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_DE_LN_PMA_RXEI                                                (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_DE_LN_PMA_RXEI(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * Register Group: \a LINE_PMA_8BIT:LANE_GRP_2
 *
 * Register group for registers 0xE0 to 0xE4
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_2:LANE_E0
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_E0                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1e0))

/**
 * \brief
 * BIST is active.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E0 . LN_BIST_RUN
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E0_LN_BIST_RUN(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_RUN                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E0_LN_BIST_RUN(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * BIST is ok.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E0 . LN_BIST_OK
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E0_LN_BIST_OK(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_OK                                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E0_LN_BIST_OK(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * BIST is error.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E0 . LN_BIST_ERR
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E0_LN_BIST_ERR(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_ERR                                                (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E0_LN_BIST_ERR(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * The bist time is time out.Bist time = (data width/bit rate)
 * *1024*r_bist_timer
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E0 . LN_BIST_DONE
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E0_LN_BIST_DONE(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E0_LN_BIST_DONE                                               (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E0_LN_BIST_DONE(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,3,1))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_2:LANE_E1
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_E1                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1e1))

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E1 . LN_BIST_ERR_CNT_7_0
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E1_LN_BIST_ERR_CNT_7_0(x)                                     (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E1_LN_BIST_ERR_CNT_7_0                                        (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E1_LN_BIST_ERR_CNT_7_0(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_2:LANE_E2
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_E2                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1e2))

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E2 . LN_BIST_ERR_CNT_15_8
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E2_LN_BIST_ERR_CNT_15_8(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E2_LN_BIST_ERR_CNT_15_8                                       (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E2_LN_BIST_ERR_CNT_15_8(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_2:LANE_E3
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_E3                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1e3))

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E3 . LN_BIST_ERR_CNT_23_16
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E3_LN_BIST_ERR_CNT_23_16(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E3_LN_BIST_ERR_CNT_23_16                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E3_LN_BIST_ERR_CNT_23_16(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a LINE_PMA_8BIT:LANE_GRP_2:LANE_E4
 */
#define LAN80XX_LINE_PMA_8BIT_LANE_E4                                                               (LAN80XX_IOREG(MMD_ID_LINE_PMA_8BIT, 0 ,0xf1e4))

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::LAN80XX_LINE_PMA_8BIT_LANE_E4 . LN_BIST_ERR_CNT_31_24
 */
#define  LAN80XX_F_LINE_PMA_8BIT_LANE_E4_LN_BIST_ERR_CNT_31_24(x)                                   (LAN80XX_ENCODE_BITFIELD(x,0,8))
#define  LAN80XX_M_LINE_PMA_8BIT_LANE_E4_LN_BIST_ERR_CNT_31_24                                      (LAN80XX_ENCODE_BITMASK(0,8))
#define  LAN80XX_X_LINE_PMA_8BIT_LANE_E4_LN_BIST_ERR_CNT_31_24(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,8))


#endif /* _LAN80XX_MALIBU25G_REGS_LINE_PMA_8BIT_H_ */
