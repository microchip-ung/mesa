// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_SD10G_LANE_TARGET_H_
#define _VTSS_LAGUNA_REGS_SD10G_LANE_TARGET_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD10G_LANE_TARGET
 *
 * \see vtss_target_SD10G_LANE_TARGET_e
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_0
 *
 * Register group for registers 0x00 to 0x43
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_00
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_00(target)  VTSS_IOREG(target,0x0)

/**
 * \brief
 * Simulation speed up mode enable.0: no speed up.1: speed up.Note that
 * loss of lock related functions will not be speed up.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_00 . R_SIMULATION_MODE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_00_R_SIMULATION_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_00_R_SIMULATION_MODE  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_00_R_SIMULATION_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_01
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_01(target)  VTSS_IOREG(target,0x1)

/**
 * \brief
 * Refer to hwt_pma_txck_sel[2:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_01 . CFG_PMA_TX_CK_BITWIDTH_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_01_CFG_PMA_TX_CK_BITWIDTH_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Refer to pcs2pma_txdetrx_en
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_01 . CFG_RXDET_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Refer to pcs2pma_txdetrx_str
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_01 . CFG_RXDET_STR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_STR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_STR  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_01_CFG_RXDET_STR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_02
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_02(target)  VTSS_IOREG(target,0x2)

/**
 * \brief
 * Enable pre-equalization control of TX.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_02 . CFG_EN_ADV
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_EN_ADV(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_EN_ADV  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_EN_ADV(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enable TX data path control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_02 . CFG_EN_MAIN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_EN_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_EN_MAIN  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_EN_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable 1st stage post-equalization control of TX.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_02 . CFG_EN_DLY
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_02 . CFG_EN_DLY2
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY2(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY2  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_EN_DLY2(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Pre-equalization level control of TX. Refer to section 2.6.2
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_02 . CFG_TAP_ADV_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_03
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_03(target)  VTSS_IOREG(target,0x3)

/**
 * \brief
 * TX data path setting. Should set to 1.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_03 . CFG_TAP_MAIN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_03_CFG_TAP_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_03_CFG_TAP_MAIN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_03_CFG_TAP_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_04
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_04(target)  VTSS_IOREG(target,0x4)

/**
 * \brief
 * 1st stage post-equalization level control of TX. Refer to section 2.6.2.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_04 . CFG_TAP_DLY_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_05
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_05(target)  VTSS_IOREG(target,0x5)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_05 . CFG_TAP_DLY2_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_05_CFG_TAP_DLY2_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_05_CFG_TAP_DLY2_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_05_CFG_TAP_DLY2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_06
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_06(target)  VTSS_IOREG(target,0x6)

/**
 * \brief
 * Power down control of TX driver to support EEE.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_PD_DRIVER
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_PD_DRIVER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_PD_DRIVER  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_PD_DRIVER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Power down control of PMAA TX clock.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_PD_CLK
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_PD_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_PD_CLK  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_PD_CLK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Power down control of PMAA TX serializer block.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_PD_CML
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_PD_CML(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_PD_CML  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_PD_CML(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * PMAA TX to RX loopback enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_TX2RX_LP_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_TX2RX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_TX2RX_LP_EN  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_TX2RX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * PMAA RX to TX loopback enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_RX2TX_LP_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_RX2TX_LP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_RX2TX_LP_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_RX2TX_LP_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_06 . CFG_EN_PREEMPH
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_06_CFG_EN_PREEMPH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_06_CFG_EN_PREEMPH  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_06_CFG_EN_PREEMPH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_07
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_07(target)  VTSS_IOREG(target,0x7)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_07 . CFG_RX_REG_BYP
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_BYP  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_BYP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * CTLE regulator enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_07 . CFG_RX_REG_PU
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_PU(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_PU  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_PU(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_07 . CFG_RX_REG_VSEL_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_VSEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_VSEL_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_07_CFG_RX_REG_VSEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_08
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_08(target)  VTSS_IOREG(target,0x8)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_08 . CFG_BYP_OC_CLK
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_08_CFG_BYP_OC_CLK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_08_CFG_BYP_OC_CLK  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_08_CFG_BYP_OC_CLK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_08 . CFG_CTLE_NEGC
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_08_CFG_CTLE_NEGC(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_08_CFG_CTLE_NEGC     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_08_CFG_CTLE_NEGC(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_09
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_09(target)  VTSS_IOREG(target,0x9)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_09 . CFG_EN_HYS_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_09_CFG_EN_HYS_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_09_CFG_EN_HYS_SQ  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_09_CFG_EN_HYS_SQ(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_09 . CFG_IP_RX_LS_SEL_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_09_CFG_IP_RX_LS_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_09_CFG_IP_RX_LS_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_09_CFG_IP_RX_LS_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0A(target)  VTSS_IOREG(target,0xa)

/**
 * \brief
 * Refer to hwt_lane_id[2:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0A . CFG_LANE_ID_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0A_CFG_LANE_ID_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0A_CFG_LANE_ID_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0A_CFG_LANE_ID_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0B(target)  VTSS_IOREG(target,0xb)

/**
 * \brief
 * CTLE gain control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0B . CFG_EQ_RES_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Power down control of CTLE block.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0B . CFG_PD_CTLE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_PD_CTLE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_PD_CTLE  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_PD_CTLE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0B . CFG_CTLE_TP_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_CTLE_TP_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_CTLE_TP_EN  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_CTLE_TP_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0B . CFG_RESETB_OSCAL_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_AFE  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0B . CFG_RESETB_OSCAL_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_SQ  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_RESETB_OSCAL_SQ(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0C(target)  VTSS_IOREG(target,0xc)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_OSCAL_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_AFE  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_AFE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_OSCAL_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_SQ  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_OSCAL_SQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_OSDAC_2X_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_AFE  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_AFE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_OSDAC_2X_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_SQ  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_OSDAC_2X_SQ(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_PD_OSDAC_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_AFE  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_AFE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_PD_OSDAC_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_SQ  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_PD_OSDAC_SQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_PD_RX_LS
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_PD_RX_LS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_PD_RX_LS  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_PD_RX_LS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0C . CFG_RX_PCIE_GEN12
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0C_CFG_RX_PCIE_GEN12(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0C_CFG_RX_PCIE_GEN12  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0C_CFG_RX_PCIE_GEN12(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0D(target)  VTSS_IOREG(target,0xd)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0D . CFG_CTLE_M_THR_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0D_CFG_CTLE_M_THR_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0D_CFG_CTLE_M_THR_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0D_CFG_CTLE_M_THR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0D . CFG_EQR_BYP
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0D_CFG_EQR_BYP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0D_CFG_EQR_BYP  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0D_CFG_EQR_BYP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0E(target)  VTSS_IOREG(target,0xe)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0E . CFG_EQC_FORCE_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * RX to TX loopback enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0E . CFG_RXLB_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_RXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_RXLB_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_RXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * TX to RX loopback enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0E . CFG_TXLB_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_TXLB_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_TXLB_EN  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_TXLB_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0E . CFG_SUM_SETCM_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_SUM_SETCM_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_SUM_SETCM_EN  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_SUM_SETCM_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_0F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_0F(target)  VTSS_IOREG(target,0xf)

/**
 * \brief
 *  [7:5] : PI bandwidth control, [4:0] : 1st CDR digital low pass filter
 * select.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_0F . R_CDR_M_GEN1_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_0F_R_CDR_M_GEN1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_0F_R_CDR_M_GEN1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_0F_R_CDR_M_GEN1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_10
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_10(target)  VTSS_IOREG(target,0x10)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_10 . R_CDR_M_GEN2_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_10_R_CDR_M_GEN2_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_10_R_CDR_M_GEN2_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_10_R_CDR_M_GEN2_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_11
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_11(target)  VTSS_IOREG(target,0x11)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_11 . R_CDR_M_GEN3_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_11_R_CDR_M_GEN3_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_12
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_12(target)  VTSS_IOREG(target,0x12)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_12 . R_CDR_M_GEN4_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_12_R_CDR_M_GEN4_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_12_R_CDR_M_GEN4_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_12_R_CDR_M_GEN4_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_13
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_13(target)  VTSS_IOREG(target,0x13)

/**
 * \brief
 * Power down control of CDR path buffer.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_13 . CFG_DCDR_PD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_13_CFG_DCDR_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_13_CFG_DCDR_PD  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_13_CFG_DCDR_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_13 . CFG_PHID_1T
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_13_CFG_PHID_1T(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_13_CFG_PHID_1T  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_13_CFG_PHID_1T(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * CDR Clock enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_13 . CFG_CDRCK_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_13_CFG_CDRCK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_13_CFG_CDRCK_EN  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_13_CFG_CDRCK_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_14
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_14(target)  VTSS_IOREG(target,0x14)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_14 . CFG_PI_EXT_DAC_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_14_CFG_PI_EXT_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_14_CFG_PI_EXT_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_14_CFG_PI_EXT_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_15
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_15(target)  VTSS_IOREG(target,0x15)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_15 . CFG_PI_EXT_DAC_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_15_CFG_PI_EXT_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_15_CFG_PI_EXT_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_15_CFG_PI_EXT_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_16
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_16(target)  VTSS_IOREG(target,0x16)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_16 . CFG_PI_EXT_DAC_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_16_CFG_PI_EXT_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_16_CFG_PI_EXT_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_16_CFG_PI_EXT_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_17
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_17(target)  VTSS_IOREG(target,0x17)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_17 . CFG_PI_EXT_DAC_30_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_17_CFG_PI_EXT_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_17_CFG_PI_EXT_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_17_CFG_PI_EXT_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_18
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_18(target)  VTSS_IOREG(target,0x18)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_18 . CFG_PI_EXT_OVR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_OVR  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_18 . CFG_PI_HOLD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_18_CFG_PI_HOLD(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_18_CFG_PI_HOLD  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_18_CFG_PI_HOLD(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_18 . CFG_PI_OFFSET_DIR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_DIR  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_DIR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_18 . CFG_PI_OFFSET_SET
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_SET(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_SET  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_18_CFG_PI_OFFSET_SET(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_18 . CFG_PI_EXT_QRT_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_QRT_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_QRT_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_18_CFG_PI_EXT_QRT_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_19
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_19(target)  VTSS_IOREG(target,0x19)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_19 . CFG_PI_OFFSET_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_19_CFG_PI_OFFSET_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_19_CFG_PI_OFFSET_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_19_CFG_PI_OFFSET_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1A(target)  VTSS_IOREG(target,0x1a)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1A . CFG_PI_R_SCAN_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_R_SCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_R_SCAN_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1A_CFG_PI_R_SCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1A . CFG_PI_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_EN  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1A_CFG_PI_EN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1A . CFG_PI_DFE_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1A . CFG_PI_STEPS
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_STEPS(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_STEPS  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1A_CFG_PI_STEPS(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1A . CFG_PI_FLOOP_STEPS_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_FLOOP_STEPS_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_FLOOP_STEPS_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1A_CFG_PI_FLOOP_STEPS_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1B(target)  VTSS_IOREG(target,0x1b)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1B . CFG_VCM_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1C(target)  VTSS_IOREG(target,0x1c)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1C . CFG_DFEDIG_BYP_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1D(target)  VTSS_IOREG(target,0x1d)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1D . CFG_DFE_BYP_H1_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1D_CFG_DFE_BYP_H1_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1D_CFG_DFE_BYP_H1_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1D_CFG_DFE_BYP_H1_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1E(target)  VTSS_IOREG(target,0x1e)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1E . CFG_DFE_BYP_H2_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_1F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_1F(target)  VTSS_IOREG(target,0x1f)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1F . CFG_DFE_BYP_H3_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_1F . CFG_DFE_BYP_H4_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_20
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_20(target)  VTSS_IOREG(target,0x20)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_20 . CFG_DFE_BYP_H5_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_21
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_21(target)  VTSS_IOREG(target,0x21)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_21 . CFG_DFE_DLEV_6_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_21_CFG_DFE_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_21_CFG_DFE_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_21_CFG_DFE_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_22
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_22(target)  VTSS_IOREG(target,0x22)

/**
 * \brief
 * Enable signal for DFE tap mux.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_22 . CFG_DFETAP_EN_5_1
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_22_CFG_DFETAP_EN_5_1(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_22_CFG_DFETAP_EN_5_1     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_22_CFG_DFETAP_EN_5_1(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_23
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_23(target)  VTSS_IOREG(target,0x23)

/**
 * \brief
 * Power down control of DFE block.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_23 . CFG_DFE_PD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_23 . CFG_EN_DFEDIG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable signal for DFE clock.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_23 . CFG_DFECK_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Power down control of error amplifier.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_23 . CFG_ERRAMP_PD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_23 . CFG_DFEDIG_M_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFEDIG_M_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFEDIG_M_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_23_CFG_DFEDIG_M_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_24
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_24(target)  VTSS_IOREG(target,0x24)

/**
 * \brief
 * PI bandwidth control,
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_24 . CFG_PI_BW_GEN1_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN1_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN1_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN1_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_24 . CFG_PI_BW_GEN2_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN2_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN2_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_24_CFG_PI_BW_GEN2_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_25
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_25(target)  VTSS_IOREG(target,0x25)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_25 . CFG_PI_BW_GEN3_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_25 . CFG_PI_BW_GEN4_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN4_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN4_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_25_CFG_PI_BW_GEN4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_26
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_26(target)  VTSS_IOREG(target,0x26)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_26 . CFG_ISCAN_EXT_DAC_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_26_CFG_ISCAN_EXT_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_27
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_27(target)  VTSS_IOREG(target,0x27)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_27 . CFG_ISCAN_EXT_DAC_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_27_CFG_ISCAN_EXT_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_27_CFG_ISCAN_EXT_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_27_CFG_ISCAN_EXT_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_28
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_28(target)  VTSS_IOREG(target,0x28)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_28 . CFG_ISCAN_EXT_DAC_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_28_CFG_ISCAN_EXT_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_28_CFG_ISCAN_EXT_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_28_CFG_ISCAN_EXT_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_29
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_29(target)  VTSS_IOREG(target,0x29)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_29 . CFG_ISCAN_EXT_DAC_30_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_29_CFG_ISCAN_EXT_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_29_CFG_ISCAN_EXT_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_29_CFG_ISCAN_EXT_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2A(target)  VTSS_IOREG(target,0x2a)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2A . CFG_ISCAN_EXT_OVR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_OVR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_OVR  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_OVR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2A . CFG_ISCAN_EXT_QRT_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_QRT_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_QRT_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2A_CFG_ISCAN_EXT_QRT_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2B(target)  VTSS_IOREG(target,0x2b)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_ISCAN_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_ISCAN_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_ISCAN_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_RSTN  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_ISCAN_STEPSIZE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_STEPSIZE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_STEPSIZE  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_STEPSIZE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Refer to hwt_fom_sel
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_FOM_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_ADD_VOLT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2B . CFG_MAN_VOLT_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2C(target)  VTSS_IOREG(target,0x2c)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2C . CFG_COMP_NUM_SEL_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2C_CFG_COMP_NUM_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2C_CFG_COMP_NUM_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2C_CFG_COMP_NUM_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2C . CFG_OS_MAN_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2C_CFG_OS_MAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2C_CFG_OS_MAN_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2C_CFG_OS_MAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2C . CFG_R_OFFSET_DIR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2C_CFG_R_OFFSET_DIR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2C_CFG_R_OFFSET_DIR  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2C_CFG_R_OFFSET_DIR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2D(target)  VTSS_IOREG(target,0x2d)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2D . CFG_MAN_VOLT_SEL_6_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2D_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2D_CFG_MAN_VOLT_SEL_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2D_CFG_MAN_VOLT_SEL_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2E(target)  VTSS_IOREG(target,0x2e)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2E . CFG_OS_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2E_CFG_OS_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2E_CFG_OS_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2E_CFG_OS_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_2F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_2F(target)  VTSS_IOREG(target,0x2f)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2F . CFG_VGA_CP_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_2F . CFG_VGA_CTRL_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_30
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_30(target)  VTSS_IOREG(target,0x30)

/**
 * \brief
 * Enable signal for summer block.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_30 . CFG_SUMMER_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_30_CFG_SUMMER_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_30_CFG_SUMMER_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_30_CFG_SUMMER_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Refer to hwt_pma_rxdiv_sel[2:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_30 . CFG_RXDIV_SEL_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_30_CFG_RXDIV_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_30_CFG_RXDIV_SEL_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_30_CFG_RXDIV_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_31
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_31(target)  VTSS_IOREG(target,0x31)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_PI_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_PI_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_PI_RSTN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_PI_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_CDR_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_CDR_RSTN  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_RSTN_DFEDIG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_CTLE_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_CTLE_RSTN  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_RSTN_DIV5_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DIV5_8(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DIV5_8  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DIV5_8(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_31 . CFG_R50_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_R50_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_R50_EN  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_31_CFG_R50_EN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_32
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_32(target)  VTSS_IOREG(target,0x32)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_32 . CFG_ITX_IPCLK_BASE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCLK_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCLK_BASE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCLK_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * TX predriver curent setting.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_32 . CFG_ITX_IPCML_BASE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCML_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_32_CFG_ITX_IPCML_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_33
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_33(target)  VTSS_IOREG(target,0x33)

/**
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_33 . CFG_ITX_IPDRIVER_BASE_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_33 . CFG_ITX_IPPREEMP_BASE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPPREEMP_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_34
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_34(target)  VTSS_IOREG(target,0x34)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_34 . CFG_RXTERM_PD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_34_CFG_RXTERM_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_34_CFG_RXTERM_PD  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_34_CFG_RXTERM_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Power down control of analog loss of signal squelch block. 1: power
 * down.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_34 . CFG_PD_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_34_CFG_PD_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_34_CFG_PD_SQ  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_34_CFG_PD_SQ(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_34 . CFG_DIS_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_34_CFG_DIS_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_34_CFG_DIS_SQ  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_34_CFG_DIS_SQ(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_34 . CFG_HIZ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_34_CFG_HIZ(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_34_CFG_HIZ  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_34_CFG_HIZ(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_35
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_35(target)  VTSS_IOREG(target,0x35)

/**
 * \brief
 * Refer to hwt_txrate_sel[1:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_35 . CFG_TXRATE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_35_CFG_TXRATE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_35_CFG_TXRATE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_35_CFG_TXRATE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Refer to hwt_rxrate_sel[1:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_35 . CFG_RXRATE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_35_CFG_RXRATE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_35_CFG_RXRATE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_35_CFG_RXRATE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_36
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_36(target)  VTSS_IOREG(target,0x36)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_36 . CFG_PREDRV_SLEWRATE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_36_CFG_PREDRV_SLEWRATE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_36_CFG_PREDRV_SLEWRATE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_36_CFG_PREDRV_SLEWRATE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_36 . CFG_EID_LP
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_36_CFG_EID_LP(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_36_CFG_EID_LP  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_36_CFG_EID_LP(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_36 . CFG_EN_PREDRV_EMPH
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_36_CFG_EN_PREDRV_EMPH(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_36_CFG_EN_PREDRV_EMPH  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_36_CFG_EN_PREDRV_EMPH(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_36 . CFG_PRBS_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SEL  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_36 . CFG_PRBS_SETB
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SETB(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SETB  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_36_CFG_PRBS_SETB(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_37
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_37(target)  VTSS_IOREG(target,0x37)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_37 . CFG_RXDET_COMP_PD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_37_CFG_RXDET_COMP_PD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_37_CFG_RXDET_COMP_PD  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_37_CFG_RXDET_COMP_PD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_37 . CFG_PD_RX_CKTREE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_37_CFG_PD_RX_CKTREE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_37_CFG_PD_RX_CKTREE  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_37_CFG_PD_RX_CKTREE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Refer to pcs2pma_txswing
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_37 . CFG_TXSWING_HALF
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_37_CFG_TXSWING_HALF(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_37_CFG_TXSWING_HALF  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_37_CFG_TXSWING_HALF(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_37 . CFG_IP_PRE_BASE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_37_CFG_IP_PRE_BASE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_37_CFG_IP_PRE_BASE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_37_CFG_IP_PRE_BASE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_38
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_38(target)  VTSS_IOREG(target,0x38)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_38 . CFG_TACC_SEL_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_38_CFG_TACC_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_38_CFG_TACC_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_38_CFG_TACC_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * CDR low pass filter threshold z
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_38 . CFG_RXFILT_Z_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_38_CFG_RXFILT_Z_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_38_CFG_RXFILT_Z_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_38_CFG_RXFILT_Z_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_39
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_39(target)  VTSS_IOREG(target,0x39)

/**
 * \brief
 * CDR low pass filter threshold y
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_39 . CFG_RXFILT_Y_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_39_CFG_RXFILT_Y_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_39_CFG_RXFILT_Y_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_39_CFG_RXFILT_Y_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_39 . CFG_RX_SSC_LH
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_39_CFG_RX_SSC_LH(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_39_CFG_RX_SSC_LH  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_39_CFG_RX_SSC_LH(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3A(target)  VTSS_IOREG(target,0x3a)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3A . CFG_MP_MIN_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3A . CFG_MP_MAX_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MAX_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MAX_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3A_CFG_MP_MAX_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3B(target)  VTSS_IOREG(target,0x3b)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3B . CFG_MF_MIN_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3B . CFG_MF_MAX_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MAX_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MAX_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3B_CFG_MF_MAX_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3C(target)  VTSS_IOREG(target,0x3c)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3C . CFG_DIS_ACC
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_ACC(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_ACC  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_ACC(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * 2nd order CDR disable signal.0 : Enable1 : Disable
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3C . CFG_DIS_2NDORDER
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_2NDORDER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_2NDORDER  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3C_CFG_DIS_2NDORDER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3D(target)  VTSS_IOREG(target,0x3d)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3D . CFG_ACC_THR_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3D_CFG_ACC_THR_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3D_CFG_ACC_THR_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3D_CFG_ACC_THR_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3E(target)  VTSS_IOREG(target,0x3e)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3E . CFG_OC_BYP_CODE_AFE_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_CODE_AFE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3E . CFG_OC_BYP_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_AFE  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3E_CFG_OC_BYP_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_3F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_3F(target)  VTSS_IOREG(target,0x3f)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3F . CFG_OC_BYP_CODE_SQ_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_CODE_SQ_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_3F . CFG_OC_BYP_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_SQ  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_3F_CFG_OC_BYP_SQ(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_40
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_40(target)  VTSS_IOREG(target,0x40)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_40 . CFG_LANE_RESERVE_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_40_CFG_LANE_RESERVE_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_40_CFG_LANE_RESERVE_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_40_CFG_LANE_RESERVE_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_41
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_41(target)  VTSS_IOREG(target,0x41)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_41 . CFG_LANE_RESERVE_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_41_CFG_LANE_RESERVE_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_41_CFG_LANE_RESERVE_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_41_CFG_LANE_RESERVE_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_42
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_42(target)  VTSS_IOREG(target,0x42)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_42 . CFG_CDR_KF_GEN1_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN1_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN1_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN1_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_42 . CFG_CDR_KF_GEN2_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN2_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN2_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_42_CFG_CDR_KF_GEN2_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_0:LANE_43
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_43(target)  VTSS_IOREG(target,0x43)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_43 . CFG_CDR_KF_GEN3_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN3_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN3_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN3_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_43 . CFG_CDR_KF_GEN4_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN4_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN4_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_43_CFG_CDR_KF_GEN4_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_1
 *
 * Register group for registers 0x48 to 0x50
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_48
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_48(target)  VTSS_IOREG(target,0x48)

/**
 * \brief
 * voltage threshold for squelch detection.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_48 . CFG_ALOS_THR_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_48_CFG_ALOS_THR_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_48_CFG_ALOS_THR_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_48_CFG_ALOS_THR_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Refer to aux_rxck_sel
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_48 . CFG_AUX_RXCK_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_48_CFG_AUX_RXCK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_48_CFG_AUX_RXCK_SEL  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_48_CFG_AUX_RXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_48 . CFG_CLK_ENQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_48_CFG_CLK_ENQ(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_48_CFG_CLK_ENQ  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_48_CFG_CLK_ENQ(x)  VTSS_EXTRACT_BITFIELD(x,5,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_49
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_49(target)  VTSS_IOREG(target,0x49)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_49 . CFG_CROSS_MARGIN_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_49_CFG_CROSS_MARGIN_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_49_CFG_CROSS_MARGIN_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_49_CFG_CROSS_MARGIN_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Fast eye scan method.0 : Calculate central phase1 : Calculate all phase
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_49 . CFG_FIGMERIT_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_49_CFG_FIGMERIT_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_49_CFG_FIGMERIT_SEL  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_49_CFG_FIGMERIT_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4A(target)  VTSS_IOREG(target,0x4a)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4A . CFG_RX_SP_CTLE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4A_CFG_RX_SP_CTLE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4A_CFG_RX_SP_CTLE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4A_CFG_RX_SP_CTLE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4B(target)  VTSS_IOREG(target,0x4b)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4B . CFG_CENTER_SPREADING
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4B_CFG_CENTER_SPREADING(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4B_CFG_CENTER_SPREADING  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4B_CFG_CENTER_SPREADING(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4C(target)  VTSS_IOREG(target,0x4c)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4C . CFG_MCNTMAXVAL_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4C_CFG_MCNTMAXVAL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4C_CFG_MCNTMAXVAL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4C_CFG_MCNTMAXVAL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4D(target)  VTSS_IOREG(target,0x4d)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4D . CFG_NCNTMAXVAL_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4D_CFG_NCNTMAXVAL_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4D_CFG_NCNTMAXVAL_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4D_CFG_NCNTMAXVAL_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4E(target)  VTSS_IOREG(target,0x4e)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4E . CFG_NCNTMAXVAL_10_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4E_CFG_NCNTMAXVAL_10_8(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4E_CFG_NCNTMAXVAL_10_8     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4E_CFG_NCNTMAXVAL_10_8(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_4F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_4F(target)  VTSS_IOREG(target,0x4f)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4F . CFG_SSC_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_4F . CFG_SSC_PI_BW_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_PI_BW_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_PI_BW_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_4F_CFG_SSC_PI_BW_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_1:LANE_50
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_50(target)  VTSS_IOREG(target,0x50)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_50 . CFG_SSC_PI_STEP_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_SSC_PI_STEP_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_SSC_PI_STEP_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_50_CFG_SSC_PI_STEP_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_50 . CFG_SSC_RESETB
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RESETB(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RESETB  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RESETB(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Refer to IGPSERT15A_connection_example.pdf for pin connection
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_50 . CFG_SSC_RTL_CLK_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RTL_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RTL_CLK_SEL  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_50_CFG_SSC_RTL_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Refer to aux_txck_sel
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_50 . CFG_AUX_TXCK_SEL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_AUX_TXCK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_AUX_TXCK_SEL  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_50_CFG_AUX_TXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_50 . CFG_JT_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_50_CFG_JT_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_50_CFG_JT_EN  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_50_CFG_JT_EN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_2
 *
 * Register group for register 0x52
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_2:LANE_52
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_52(target)  VTSS_IOREG(target,0x52)

/**
 * \brief
 * 8-bit for TX amplitude adjustment
 * {cfg_itx_ipdriver_base[1:0],cfg_ibias_tune_reserve[5:0]} from 0.4Vpp to
 * 1.2Vpp. 1LSB could increase/decrease 3.125mV. cfg_itx_ipdriver_base[2]
 * is reserved.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_52 . CFG_IBIAS_TUNE_RESERVE_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_3
 *
 * Register group for registers 0x58 to 0x5B
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_3:LANE_58
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_58(target)  VTSS_IOREG(target,0x58)

/**
 * \brief
 * Internal use signals
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_58 . CFG_TX_RSTB_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_58_CFG_TX_RSTB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_58_CFG_TX_RSTB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_58_CFG_TX_RSTB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_3:LANE_59
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_59(target)  VTSS_IOREG(target,0x59)

/**
 * \brief
 * Internal use signals
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_59 . CFG_TX_RSTB_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_59_CFG_TX_RSTB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_59_CFG_TX_RSTB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_59_CFG_TX_RSTB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_3:LANE_5A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_5A(target)  VTSS_IOREG(target,0x5a)

/**
 * \brief
 * Internal use signals
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_5A . CFG_TX_SETB_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_5A_CFG_TX_SETB_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_5A_CFG_TX_SETB_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_5A_CFG_TX_SETB_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_3:LANE_5B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_5B(target)  VTSS_IOREG(target,0x5b)

/**
 * \brief
 * Internal use signals
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_5B . CFG_TX_SETB_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_5B_CFG_TX_SETB_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_5B_CFG_TX_SETB_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_5B_CFG_TX_SETB_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_4
 *
 * Register group for registers 0x74 to 0x88
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_74
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_74(target)  VTSS_IOREG(target,0x74)

/**
 * \brief
 * 0x0000 : Infinite BIST run time
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_74 . R_BIST_TIMER_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_74_R_BIST_TIMER_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_74_R_BIST_TIMER_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_74_R_BIST_TIMER_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_75
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_75(target)  VTSS_IOREG(target,0x75)

/**
 * \brief
 * 0x0001 ~ 0xFFFF : BIST run time =(data width/bit rate) *1024*
 * r_bist_timer[15:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_75 . R_BIST_TIMER_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_75_R_BIST_TIMER_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_75_R_BIST_TIMER_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_75_R_BIST_TIMER_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_76
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_76(target)  VTSS_IOREG(target,0x76)

/**
 * \brief
 * BIST enable signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_76 . R_BIST_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_76_R_BIST_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BIST error injection enable
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_76 . R_BIST_ERRINJEC
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_ERRINJEC(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_ERRINJEC  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_76_R_BIST_ERRINJEC(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * 0 : non free running mode1 : free running mode
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_76 . R_FREE_RUN_MODE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_76_R_FREE_RUN_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_76_R_FREE_RUN_MODE  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_76_R_FREE_RUN_MODE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * BIST pattern selection000: PRBS7.001: PRBS9.010: PRBS11.011: PRBS15.100:
 * PRBS23.101: PRBS31.110: clock pattern.111: user defined pattern.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_76 . R_BIST_MODE_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_MODE_2_0(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_MODE_2_0     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_76_R_BIST_MODE_2_0(x)  VTSS_EXTRACT_BITFIELD(x,4,3)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_77
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_77(target)  VTSS_IOREG(target,0x77)

/**
 * \brief
 * BIST result compare enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_77 . R_BIST_CHK
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * 1: bist_err will assert if rx all zero data in PRBS mode.0: Treat all
 * zero data input as correct data. Note: r_bist_chk_zero must be set after
 * r_bist_ok is asserted.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_77 . R_BIST_CHK_ZERO
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK_ZERO(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK_ZERO  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK_ZERO(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * 1: bist_err counter will stop when reaching 32'hffff_ffff0: bist_err
 * counter will run continuously, will not saturate.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_77 . R_BIST_ERRSTOP
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_ERRSTOP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_ERRSTOP  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_77_R_BIST_ERRSTOP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_77 . R_BIST_RXERR_LBK
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_RXERR_LBK(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_RXERR_LBK  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_77_R_BIST_RXERR_LBK(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_78
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_78(target)  VTSS_IOREG(target,0x78)

/**
 * \brief
 * RX loss of lock deassert timing.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_78 . R_TIME_DEASSERT_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_78_R_TIME_DEASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_78_R_TIME_DEASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_78_R_TIME_DEASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_79
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_79(target)  VTSS_IOREG(target,0x79)

/**
 * \brief
 * RX loss of lock deassert timing.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_79 . R_TIME_DEASSERT_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_79_R_TIME_DEASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_79_R_TIME_DEASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_79_R_TIME_DEASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7A(target)  VTSS_IOREG(target,0x7a)

/**
 * \brief
 * RX loss of lock assert timing.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7A . R_TIME_ASSERT_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7A_R_TIME_ASSERT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7A_R_TIME_ASSERT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7A_R_TIME_ASSERT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7B(target)  VTSS_IOREG(target,0x7b)

/**
 * \brief
 * RX loss of lock assert timing.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7B . R_TIME_ASSERT_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7B_R_TIME_ASSERT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7B_R_TIME_ASSERT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7B_R_TIME_ASSERT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7C(target)  VTSS_IOREG(target,0x7c)

/**
 * \brief
 * RX loss of lock status output enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7C . R_DLOL_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7C_R_DLOL_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7C_R_DLOL_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7C_R_DLOL_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7D(target)  VTSS_IOREG(target,0x7d)

/**
 * \brief
 * RX loss of lock deassert dppm control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7D . R_DEASSERT_PPM_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7D_R_DEASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7D_R_DEASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7D_R_DEASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7E(target)  VTSS_IOREG(target,0x7e)

/**
 * \brief
 * RX loss of lock deassert dppm control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7E . R_DEASSERT_PPM_9_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7E_R_DEASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7E_R_DEASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7E_R_DEASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_7F
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_7F(target)  VTSS_IOREG(target,0x7f)

/**
 * \brief
 * RX loss of lock assert dppm control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_7F . R_ASSERT_PPM_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_7F_R_ASSERT_PPM_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_7F_R_ASSERT_PPM_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_7F_R_ASSERT_PPM_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_80
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_80(target)  VTSS_IOREG(target,0x80)

/**
 * \brief
 * RX loss of lock assert dppm control.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_80 . R_ASSERT_PPM_9_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_80_R_ASSERT_PPM_9_8(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_80_R_ASSERT_PPM_9_8     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_80_R_ASSERT_PPM_9_8(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_81
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_81(target)  VTSS_IOREG(target,0x81)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_81 . R_DLOS_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_81_R_DLOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_81_R_DLOS_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_81_R_DLOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_81 . R_LOS_CKONE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_81_R_LOS_CKONE_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_81_R_LOS_CKONE_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_81_R_LOS_CKONE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_82
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_82(target)  VTSS_IOREG(target,0x82)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_82 . R_TIME_LOS_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_82_R_TIME_LOS_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_82_R_TIME_LOS_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_82_R_TIME_LOS_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Analog loss of signal enable.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_82 . R_ALOS_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_82_R_ALOS_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_82_R_ALOS_EN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_82_R_ALOS_EN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_82 . R_LOL_RESET
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_82_R_LOL_RESET(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_82_R_LOL_RESET  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_82_R_LOL_RESET(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_82 . R_TX_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_82_R_TX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_82_R_TX_RSTN  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_82_R_TX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_82 . R_RX_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_82_R_RX_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_82_R_RX_RSTN  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_82_R_RX_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_83
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_83(target)  VTSS_IOREG(target,0x83)

/**
 * \brief
 * TX data bit reversal control. High active.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_TX_BIT_REVERSE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_TX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_TX_BIT_REVERSE  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_TX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * TX data bit polarity control. 1: polarity will be inverted.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_TX_POL_INV
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_TX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_TX_POL_INV  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_TX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * RX data bit reversal control. High active.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_RX_BIT_REVERSE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_RX_BIT_REVERSE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_RX_BIT_REVERSE  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_RX_BIT_REVERSE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * RX data bit polarity control. 1: polarity will be inverted.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_RX_POL_INV
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_RX_POL_INV(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_RX_POL_INV  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_RX_POL_INV(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_DFE_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_CDR_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_83 . R_CTLE_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_83_R_CTLE_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_83_R_CTLE_RSTN  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_83_R_CTLE_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_84
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_84(target)  VTSS_IOREG(target,0x84)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_84 . R_TXEI
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_84_R_TXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_84_R_TXEI  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_84_R_TXEI(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * RX loss of lock event clear.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_84 . R_LOL_CLR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_84_R_LOL_CLR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_84_R_LOL_CLR  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_84_R_LOL_CLR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_85
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_85(target)  VTSS_IOREG(target,0x85)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_85 . R_RESERVE_0_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_85_R_RESERVE_0_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_85_R_RESERVE_0_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_85_R_RESERVE_0_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_86
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_86(target)  VTSS_IOREG(target,0x86)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_86 . R_RESERVE_0_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_86_R_RESERVE_0_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_86_R_RESERVE_0_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_86_R_RESERVE_0_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_87
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_87(target)  VTSS_IOREG(target,0x87)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_87 . R_RESERVE_1_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_87_R_RESERVE_1_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_87_R_RESERVE_1_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_87_R_RESERVE_1_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_4:LANE_88
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_88(target)  VTSS_IOREG(target,0x88)

/**
 * \brief
 * Reserved
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_88 . R_RESERVE_1_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_88_R_RESERVE_1_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_88_R_RESERVE_1_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_88_R_RESERVE_1_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_5
 *
 * Register group for registers 0x90 to 0x9E
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_90
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_90(target)  VTSS_IOREG(target,0x90)

/**
 * \brief
 * T3 in Figure 3.2-1 or T2 in Figure 3.2-2 (reset scheme).00: 30t01:
 * 10000t10: 20000t11: 30000t
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_90 . R_TIME_CDR2TXRX_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_90_R_TIME_CDR2TXRX_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_90_R_TIME_CDR2TXRX_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_90_R_TIME_CDR2TXRX_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * T5 in Figure 3.2-1 or T4 in Figure 3.2-2 (reset scheme).0000: 30t.0001:
 * 250t.0010: 500t.0011: 750t.0100: 1000t.0101: 1500t.0110: 2000t.0111:
 * 2500t.1000: 3000t.1001: 3500t.1010: 4000t.1011: 4500t.1100: 5000t.1101:
 * 6000t.1110: 8000t.1111: 10000t.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_90 . R_TIME_CTLE2DFE_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_90_R_TIME_CTLE2DFE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_90_R_TIME_CTLE2DFE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_90_R_TIME_CTLE2DFE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_91
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_91(target)  VTSS_IOREG(target,0x91)

/**
 * \brief
 * 1: enable LS3 loopback path.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_91 . R_LBSLV_IN_PMAD
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_91_R_LBSLV_IN_PMAD(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_91_R_LBSLV_IN_PMAD  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_91_R_LBSLV_IN_PMAD(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Refer to hwt_multi_lane_mode
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_91 . R_MULTI_LANE_MODE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_91_R_MULTI_LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_91_R_MULTI_LANE_MODE  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_91_R_MULTI_LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_91 . R_MASK_EI_SOURCE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_91_R_MASK_EI_SOURCE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_91_R_MASK_EI_SOURCE  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_91_R_MASK_EI_SOURCE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_91 . R_DISABLE_EI_FILTER
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_91_R_DISABLE_EI_FILTER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_91_R_DISABLE_EI_FILTER  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_91_R_DISABLE_EI_FILTER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_91 . R_RXEI_FILTER_FACTOR_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_91_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_91_R_RXEI_FILTER_FACTOR_1_0     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_91_R_RXEI_FILTER_FACTOR_1_0(x)  VTSS_EXTRACT_BITFIELD(x,4,2)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_92
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_92(target)  VTSS_IOREG(target,0x92)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_92 . R_TXEI_DLY_SEL_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_92_R_TXEI_DLY_SEL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_92_R_TXEI_DLY_SEL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_92_R_TXEI_DLY_SEL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_92 . R_TXEI_ADV_SEL_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_92_R_TXEI_ADV_SEL_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_92_R_TXEI_ADV_SEL_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_92_R_TXEI_ADV_SEL_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_93
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_93(target)  VTSS_IOREG(target,0x93)

/**
 * \brief
 * Reset RX FIFO if RXEI is asserted0 : disable1 : enable
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_RXEI_FIFO_RST_EN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_RXEI_FIFO_RST_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_RXEI_FIFO_RST_EN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_RXEI_FIFO_RST_EN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Data width/data rate/termination resistor of reference clock control
 * from register or hardware pin.0: cfg control 1: hwt control
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_DWIDTHCTRL_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_DWIDTHCTRL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_DIS_RESTORE_DFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_DIS_RESTORE_DFE(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_DIS_RESTORE_DFE  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_DIS_RESTORE_DFE(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_EN_RATECHG_CTRL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_EN_RATECHG_CTRL(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_EN_RATECHG_CTRL  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_EN_RATECHG_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * To select between interface pin control (default) and register control
 * of1.???? TX FFE coefficient control2.???? TX swing control3.???? power
 * down controlEye scan enable
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_REG_MANUAL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Select aux_txck_sel/aux_rxck_sel is from hardware pin or configuration
 * registers.0 : Configuration register1 : pin interface
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_AUXCKSEL_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_AUXCKSEL_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_AUXCKSEL_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_AUXCKSEL_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Select lane_id is from hardware pin or configuration registers.0 :
 * Configuration register1 : pin interface
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_LANE_ID_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_LANE_ID_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_LANE_ID_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_LANE_ID_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 *  Internal use signal
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_93 . R_RX_PCIE_GEN12_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_93_R_RX_PCIE_GEN12_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_93_R_RX_PCIE_GEN12_FROM_HWT  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_93_R_RX_PCIE_GEN12_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_94
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_94(target)  VTSS_IOREG(target,0x94)

/**
 * \brief
 * Refer to hwt_data_width_sel[2:0]
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_94 . R_DWIDTHCTRL_2_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_94_R_DWIDTHCTRL_2_0(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_94_R_DWIDTHCTRL_2_0     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_94_R_DWIDTHCTRL_2_0(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * To select between interface pin control (default) and register control
 * of eye scan function0 : Pin control1 : Register control
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_94 . R_ISCAN_REG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * To select between interface pin control (default) and register control
 * of tx equalizer0 : Pin control1 : Register control
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_94 . R_TXEQ_REG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_94_R_TXEQ_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_94_R_TXEQ_REG  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_94_R_TXEQ_REG(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * To select between interface pin control (default) and register control
 * of miscellaneous signals.0 : Pin control1 : Register control
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_94 . R_MISC_REG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_94_R_MISC_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_94_R_MISC_REG  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_94_R_MISC_REG(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * To select between interface pin control (default) and register control
 * oftx swing0 : Pin control1 : Register control
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_94 . R_SWING_REG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_94_R_SWING_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_94_R_SWING_REG  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_94_R_SWING_REG(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_95
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_95(target)  VTSS_IOREG(target,0x95)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_95 . R_DBG_SEL_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_95_R_DBG_SEL_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_95_R_DBG_SEL_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_95_R_DBG_SEL_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_96
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_96(target)  VTSS_IOREG(target,0x96)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_96 . R_BIST_PATTERN_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_96_R_BIST_PATTERN_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_96_R_BIST_PATTERN_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_96_R_BIST_PATTERN_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_97
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_97(target)  VTSS_IOREG(target,0x97)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_97 . R_BIST_PATTERN_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_97_R_BIST_PATTERN_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_97_R_BIST_PATTERN_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_97_R_BIST_PATTERN_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_98
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_98(target)  VTSS_IOREG(target,0x98)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_98 . R_BIST_PATTERN_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_98_R_BIST_PATTERN_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_98_R_BIST_PATTERN_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_98_R_BIST_PATTERN_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_99
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_99(target)  VTSS_IOREG(target,0x99)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_99 . R_BIST_PATTERN_31_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_99_R_BIST_PATTERN_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_99_R_BIST_PATTERN_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_99_R_BIST_PATTERN_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_9A
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_9A(target)  VTSS_IOREG(target,0x9a)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9A . R_BIST_PATTERN_39_32
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9A_R_BIST_PATTERN_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9A_R_BIST_PATTERN_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9A_R_BIST_PATTERN_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_9B
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_9B(target)  VTSS_IOREG(target,0x9b)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9B . R_BIST_PATTERN_47_40
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9B_R_BIST_PATTERN_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9B_R_BIST_PATTERN_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9B_R_BIST_PATTERN_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_9C
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_9C(target)  VTSS_IOREG(target,0x9c)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9C . R_BIST_PATTERN_55_48
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9C_R_BIST_PATTERN_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9C_R_BIST_PATTERN_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9C_R_BIST_PATTERN_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_9D
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_9D(target)  VTSS_IOREG(target,0x9d)

/**
 * \brief
 * User defined BIST pattern
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9D . R_BIST_PATTERN_63_56
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9D_R_BIST_PATTERN_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9D_R_BIST_PATTERN_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9D_R_BIST_PATTERN_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_5:LANE_9E
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_9E(target)  VTSS_IOREG(target,0x9e)

/**
 * \brief
 * Select RXEQ control signals are from hardware pin or configuration
 * registers.0 : hardware pin1 : configuration registers
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9E . R_RXEQ_REG
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Reset tree buffer power down control selection.0 : Configuration
 * registers1 : internal circuit.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9E . R_AUTO_RST_TREE_PD_MAN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_AUTO_RST_TREE_PD_MAN  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9E_R_AUTO_RST_TREE_PD_MAN(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable CDR auto reset function. Reset CDR if loss of lock under SSC0 :
 * Disable CDR auto reset1 : Enable CDR auto reset.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_9E . R_EN_AUTO_CDR_RSTN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_9E_R_EN_AUTO_CDR_RSTN(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_EN_AUTO_CDR_RSTN  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_9E_R_EN_AUTO_CDR_RSTN(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_6
 *
 * Register group for registers 0xA0 to 0xA6
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A0
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A0(target)  VTSS_IOREG(target,0xa0)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A0 . R_DWF_TX_DIV_MODE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A0_R_DWF_TX_DIV_MODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A0_R_DWF_TX_DIV_MODE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A0_R_DWF_TX_DIV_MODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A0 . R_TXFIFO_INI_RDPTR_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A0_R_TXFIFO_INI_RDPTR_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A0_R_TXFIFO_INI_RDPTR_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A0_R_TXFIFO_INI_RDPTR_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A1
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A1(target)  VTSS_IOREG(target,0xa1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A1 . R_PMA_TXCK_DIV_SEL_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A1_R_PMA_TXCK_DIV_SEL_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Select ssc control signals are from hardware pin or configuration
 * registers.0 : Configuration register1 : From hardware pins
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A1 . R_SSC_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_SSC_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_SSC_FROM_HWT  VTSS_BIT(4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A1_R_SSC_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Select cdr control signals are from hardware pin or configuration
 * registers.0 : Configuration register1 : From hardware pins
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A1 . R_CDR_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_CDR_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_CDR_FROM_HWT  VTSS_BIT(5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A1_R_CDR_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Select pclk_gating is from hardware pin or configuration registers.0 :
 * Configuration register1 : From hardware pins
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A1 . R_PCLK_GATING_FROM_HWT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING_FROM_HWT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING_FROM_HWT  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING_FROM_HWT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Refer to pclk_gating
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A1 . R_PCLK_GATING
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING  VTSS_BIT(7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A1_R_PCLK_GATING(x)  VTSS_EXTRACT_BITFIELD(x,7,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A2
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A2(target)  VTSS_IOREG(target,0xa2)

/**
 * \brief
 * 5'b00_000
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A2 . R_PCS2PMA_PHYMODE_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A2_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A2_R_PCS2PMA_PHYMODE_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A2_R_PCS2PMA_PHYMODE_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A3
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A3(target)  VTSS_IOREG(target,0xa3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A3 . R_DEASSERT_PPM_SSC_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A3_R_DEASSERT_PPM_SSC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A3_R_DEASSERT_PPM_SSC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A3_R_DEASSERT_PPM_SSC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A4
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A4(target)  VTSS_IOREG(target,0xa4)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A4 . R_DASSERT_PPM_SSC_11_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A4_R_DASSERT_PPM_SSC_11_8(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A4_R_DASSERT_PPM_SSC_11_8     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A4_R_DASSERT_PPM_SSC_11_8(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A5
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A5(target)  VTSS_IOREG(target,0xa5)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A5 . R_ASSERT_PPM_SSC_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A5_R_ASSERT_PPM_SSC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A5_R_ASSERT_PPM_SSC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A5_R_ASSERT_PPM_SSC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_6:LANE_A6
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_A6(target)  VTSS_IOREG(target,0xa6)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_A6 . R_ASSERT_PPM_SSC_11_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_A6_R_ASSERT_PPM_SSC_11_8(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_A6_R_ASSERT_PPM_SSC_11_8     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_A6_R_ASSERT_PPM_SSC_11_8(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_7
 *
 * Register group for registers 0xC0 to 0xCD
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C0
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C0(target)  VTSS_IOREG(target,0xc0)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C0 . PI_DAC_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C0_PI_DAC_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C0_PI_DAC_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C0_PI_DAC_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C1
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C1(target)  VTSS_IOREG(target,0xc1)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C1 . PI_DAC_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C1_PI_DAC_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C1_PI_DAC_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C1_PI_DAC_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C2
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C2(target)  VTSS_IOREG(target,0xc2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C2 . PI_DAC_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C2_PI_DAC_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C2_PI_DAC_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C2_PI_DAC_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C3
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C3(target)  VTSS_IOREG(target,0xc3)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C3 . PI_DAC_30_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C3_PI_DAC_30_24(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C3_PI_DAC_30_24     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C3_PI_DAC_30_24(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C4
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C4(target)  VTSS_IOREG(target,0xc4)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C4 . PI_QRT_CODE_1_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C4_PI_QRT_CODE_1_0(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C4_PI_QRT_CODE_1_0     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C4_PI_QRT_CODE_1_0(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C4 . VGAR_CODE_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C4_VGAR_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,4,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C4_VGAR_CODE_3_0     VTSS_ENCODE_BITMASK(4,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C4_VGAR_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,4,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C5
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C5(target)  VTSS_IOREG(target,0xc5)

/**
 * \brief
 * DFE coefficient.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C5 . H1_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C5_H1_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C5_H1_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C5_H1_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C6
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C6(target)  VTSS_IOREG(target,0xc6)

/**
 * \brief
 * DFE coefficient.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C6 . H2_4_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C6_H2_4_0(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C6_H2_4_0     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C6_H2_4_0(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C7
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C7(target)  VTSS_IOREG(target,0xc7)

/**
 * \brief
 * DFE coefficient.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C7 . H3_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C7_H3_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C7_H3_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C7_H3_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C8
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C8(target)  VTSS_IOREG(target,0xc8)

/**
 * \brief
 * DFE coefficient.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C8 . H4_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C8_H4_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C8_H4_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C8_H4_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_C9
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_C9(target)  VTSS_IOREG(target,0xc9)

/**
 * \brief
 * DFE coefficient.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_C9 . H5_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_C9_H5_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_C9_H5_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_C9_H5_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_CA
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_CA(target)  VTSS_IOREG(target,0xca)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CA . DLEV_6_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CA_DLEV_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CA_DLEV_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CA_DLEV_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_CB
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_CB(target)  VTSS_IOREG(target,0xcb)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CB . OSDAC_CODE_AFE_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CB_OSDAC_CODE_AFE_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CB_OSDAC_CODE_AFE_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CB_OSDAC_CODE_AFE_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CB . CALEND_AFE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CB_CALEND_AFE(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CB_CALEND_AFE  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CB_CALEND_AFE(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_CC
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_CC(target)  VTSS_IOREG(target,0xcc)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CC . OSDAC_CODE_SQ_5_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CC_OSDAC_CODE_SQ_5_0(x)  VTSS_ENCODE_BITFIELD(x,0,6)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CC_OSDAC_CODE_SQ_5_0     VTSS_ENCODE_BITMASK(0,6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CC_OSDAC_CODE_SQ_5_0(x)  VTSS_EXTRACT_BITFIELD(x,0,6)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CC . CALEND_SQ
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CC_CALEND_SQ(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CC_CALEND_SQ  VTSS_BIT(6)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CC_CALEND_SQ(x)  VTSS_EXTRACT_BITFIELD(x,6,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_7:LANE_CD
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_CD(target)  VTSS_IOREG(target,0xcd)

/**
 * \brief
 * Reserved.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_CD . CFG_STATUS_RESERVE_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_CD_CFG_STATUS_RESERVE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_CD_CFG_STATUS_RESERVE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_CD_CFG_STATUS_RESERVE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a SD10G_LANE_TARGET:LANE_GRP_8
 *
 * Register group for registers 0xD0 to 0xE4
 */


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D0
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D0(target)  VTSS_IOREG(target,0xd0)

/**
 * \brief
 * 0 : Fast eye scan is correct.1 : Fast eye scan is failed. The upper
 * bound or low bound of eye can not be found.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D0 . FAST_EYE_SCAN_FAIL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D0_FAST_EYE_SCAN_FAIL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D0_FAST_EYE_SCAN_FAIL  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D0_FAST_EYE_SCAN_FAIL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Eye scan status0 : eye scan is on-going1 : eye scan process is done.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D0 . ISCAN_DONE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D1
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D1(target)  VTSS_IOREG(target,0xd1)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D1 . ISCAN_RESULTS_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D1_ISCAN_RESULTS_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D1_ISCAN_RESULTS_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D1_ISCAN_RESULTS_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D2
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D2(target)  VTSS_IOREG(target,0xd2)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D2 . ISCAN_RESULTS_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D2_ISCAN_RESULTS_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D2_ISCAN_RESULTS_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D2_ISCAN_RESULTS_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D3
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D3(target)  VTSS_IOREG(target,0xd3)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D3 . ISCAN_RESULTS_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D3_ISCAN_RESULTS_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D3_ISCAN_RESULTS_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D3_ISCAN_RESULTS_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D4
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D4(target)  VTSS_IOREG(target,0xd4)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D4 . ISCAN_RESULTS_31_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D4_ISCAN_RESULTS_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D4_ISCAN_RESULTS_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D4_ISCAN_RESULTS_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D5
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D5(target)  VTSS_IOREG(target,0xd5)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D5 . ISCAN_RESULTS_39_32
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D5_ISCAN_RESULTS_39_32(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D5_ISCAN_RESULTS_39_32     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D5_ISCAN_RESULTS_39_32(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D6
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D6(target)  VTSS_IOREG(target,0xd6)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D6 . ISCAN_RESULTS_47_40
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D6_ISCAN_RESULTS_47_40(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D6_ISCAN_RESULTS_47_40     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D6_ISCAN_RESULTS_47_40(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D7
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D7(target)  VTSS_IOREG(target,0xd7)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D7 . ISCAN_RESULTS_55_48
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D7_ISCAN_RESULTS_55_48(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D7_ISCAN_RESULTS_55_48     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D7_ISCAN_RESULTS_55_48(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D8
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D8(target)  VTSS_IOREG(target,0xd8)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D8 . ISCAN_RESULTS_63_56
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D8_ISCAN_RESULTS_63_56(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D8_ISCAN_RESULTS_63_56     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D8_ISCAN_RESULTS_63_56(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_D9
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_D9(target)  VTSS_IOREG(target,0xd9)

/**
 * \brief
 * Eye scan result
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_D9 . ISCAN_RESULTS_64
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_D9_ISCAN_RESULTS_64(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_D9_ISCAN_RESULTS_64  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_D9_ISCAN_RESULTS_64(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DA
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DA(target)  VTSS_IOREG(target,0xda)

/**
 * \brief
 * Eye scan result for single point scan.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DA . ISACN_RESULT
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DA_ISACN_RESULT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DA_ISACN_RESULT  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DA_ISACN_RESULT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DB
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DB(target)  VTSS_IOREG(target,0xdb)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DB . ISACN_VOLT_STAT_6_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DB_ISACN_VOLT_STAT_6_0(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DB_ISACN_VOLT_STAT_6_0     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DB_ISACN_VOLT_STAT_6_0(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DC
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DC(target)  VTSS_IOREG(target,0xdc)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DC . ISCAN_ERR_CNT_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DC_ISCAN_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DC_ISCAN_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DC_ISCAN_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DD
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DD(target)  VTSS_IOREG(target,0xdd)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DD . ISCAN_ERR_CNT_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DD_ISCAN_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DD_ISCAN_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DD_ISCAN_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DE
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DE(target)  VTSS_IOREG(target,0xde)

/**
 * \brief
 * Internal use signal.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DE . EQC_CODE_3_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DE_EQC_CODE_3_0(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DE_EQC_CODE_3_0     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DE_EQC_CODE_3_0(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_DF
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_DF(target)  VTSS_IOREG(target,0xdf)

/**
 * \brief
 * RX loss of lock event indicator. (latch-high signal)0: RX clock is
 * locked to PLL clock.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DF . LOL_UDL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DF_LOL_UDL(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DF_LOL_UDL  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DF_LOL_UDL(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * RX loss of lock indicator. 0: RX clock is locked to PLL clock.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DF . LOL
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DF_LOL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DF_LOL  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DF_LOL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Loss of signal state.0: RX signal is detected. Note that this bit is RX
 * data pattern dependent. Non-standard application with this signal is
 * recommended to check with GUC designers.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DF . PMA2PCS_RXEI_FILTERED
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DF_PMA2PCS_RXEI_FILTERED(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DF_PMA2PCS_RXEI_FILTERED  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DF_PMA2PCS_RXEI_FILTERED(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Squelch status.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_DF . SQUELCH
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_DF_SQUELCH(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_DF_SQUELCH  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_DF_SQUELCH(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_E0
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_E0(target)  VTSS_IOREG(target,0xe0)

/**
 * \brief
 * BIST is active.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E0 . BIST_RUN
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E0_BIST_RUN(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E0_BIST_RUN  VTSS_BIT(0)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E0_BIST_RUN(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * BIST is ok.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E0 . BIST_OK
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E0_BIST_OK(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E0_BIST_OK  VTSS_BIT(1)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E0_BIST_OK(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * BIST is error.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E0 . BIST_ERR
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E0_BIST_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E0_BIST_ERR  VTSS_BIT(2)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E0_BIST_ERR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * The bist time is time out.Bist time = (data width/bit rate)
 * *1024*r_bist_timer
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E0 . BIST_DONE
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E0_BIST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E0_BIST_DONE  VTSS_BIT(3)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E0_BIST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_E1
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_E1(target)  VTSS_IOREG(target,0xe1)

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E1 . BIST_ERR_CNT_7_0
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E1_BIST_ERR_CNT_7_0(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E1_BIST_ERR_CNT_7_0     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E1_BIST_ERR_CNT_7_0(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_E2
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_E2(target)  VTSS_IOREG(target,0xe2)

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E2 . BIST_ERR_CNT_15_8
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E2_BIST_ERR_CNT_15_8(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E2_BIST_ERR_CNT_15_8     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E2_BIST_ERR_CNT_15_8(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_E3
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_E3(target)  VTSS_IOREG(target,0xe3)

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E3 . BIST_ERR_CNT_23_16
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E3_BIST_ERR_CNT_23_16(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E3_BIST_ERR_CNT_23_16     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E3_BIST_ERR_CNT_23_16(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief CMU Configuration Register
 *
 * \details
 * Register: \a SD10G_LANE_TARGET:LANE_GRP_8:LANE_E4
 *
 * @param target A \a ::vtss_target_SD10G_LANE_TARGET_e target
 */
#define VTSS_SD10G_LANE_TARGET_LANE_E4(target)  VTSS_IOREG(target,0xe4)

/**
 * \brief
 * BIST Error counter.
 *
 * \details
 * Field: ::VTSS_SD10G_LANE_TARGET_LANE_E4 . BIST_ERR_CNT_31_24
 */
#define  VTSS_F_SD10G_LANE_TARGET_LANE_E4_BIST_ERR_CNT_31_24(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_SD10G_LANE_TARGET_LANE_E4_BIST_ERR_CNT_31_24     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_SD10G_LANE_TARGET_LANE_E4_BIST_ERR_CNT_31_24(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_LAGUNA_REGS_SD10G_LANE_TARGET_H_ */
