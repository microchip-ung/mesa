// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_EXP_H_
#define _VTSS_MALIBU_REGS_EXP_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a EXP
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a EXP:EXP_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:EXP_CFG:CFG1
 */
#define VTSS_EXP_EXP_CFG_CFG1                VTSS_IOREG(0x1e, 1, 0xf100)

/** 
 * \brief
 * Reset the FIFO read port on Line 3
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . L3_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_L3_RESET     VTSS_BIT(31)

/** 
 * \brief
 * Reset the FIFO read port on Line 2
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . L2_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_L2_RESET     VTSS_BIT(30)

/** 
 * \brief
 * Reset the FIFO read port on Line 1
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . L1_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_L1_RESET     VTSS_BIT(29)

/** 
 * \brief
 * Reset the FIFO read port on Line 0
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . L0_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_L0_RESET     VTSS_BIT(28)

/** 
 * \brief
 * Reset the FIFO read port on Host 3
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . H3_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_H3_RESET     VTSS_BIT(27)

/** 
 * \brief
 * Reset the FIFO read port on Host 2
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . H2_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_H2_RESET     VTSS_BIT(26)

/** 
 * \brief
 * Reset the FIFO read port on Host 1
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . H1_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_H1_RESET     VTSS_BIT(25)

/** 
 * \brief
 * Reset the FIFO read port on Host 0
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_CFG1 . H0_RESET
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_H0_RESET     VTSS_BIT(24)

/** 
 * \brief
 * Bypass cross-connect functionality and pass data directly through
 * 
 * Note condition logic is still active in bypass mode
 *
 * \details 
 * 0: Enable Cross-connect
 * 1: Bypass Cross-connect
 *
 * Field: VTSS_EXP_EXP_CFG_CFG1 . BYPASS
 */
#define  VTSS_F_EXP_EXP_CFG_CFG1_BYPASS       VTSS_BIT(0)


/** 
 * \details
 * Register: \a EXP:EXP_CFG:COND_CFG
 */
#define VTSS_EXP_EXP_CFG_COND_CFG            VTSS_IOREG(0x1e, 1, 0xf101)

/** 
 * \brief
 * Invert corresponding GPIO input when used as a switch condition;  
 * One bit for each external input to the cross connect control function.
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_COND_CFG . INVERT_GPIO
 */
#define  VTSS_F_EXP_EXP_CFG_COND_CFG_INVERT_GPIO(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_EXP_CFG_COND_CFG_INVERT_GPIO     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_EXP_CFG_COND_CFG_INVERT_GPIO(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Invert EWIS LOF indicator when used as a switch condition
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_COND_CFG . INVERT_LOF
 */
#define  VTSS_F_EXP_EXP_CFG_COND_CFG_INVERT_LOF  VTSS_BIT(3)

/** 
 * \brief
 * Invert PMA LOS indicator when used as a switch condition
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_COND_CFG . INVERT_LOS
 */
#define  VTSS_F_EXP_EXP_CFG_COND_CFG_INVERT_LOS  VTSS_BIT(2)

/** 
 * \brief
 * Invert 1000Base-X PCS link_status indication when used as a switrch
 * condition
 *
 * \details 
 * Field: VTSS_EXP_EXP_CFG_COND_CFG . INVERT_LINK_STATUS
 */
#define  VTSS_F_EXP_EXP_CFG_COND_CFG_INVERT_LINK_STATUS  VTSS_BIT(1)

/**
 * Register Group: \a EXP:EXP_STATUS
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:EXP_STATUS:STAT1
 */
#define VTSS_EXP_EXP_STATUS_STAT1            VTSS_IOREG(0x1e, 1, 0xf102)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . L3_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_L3_SEL(x)  VTSS_ENCODE_BITFIELD(x,14,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_L3_SEL     VTSS_ENCODE_BITMASK(14,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_L3_SEL(x)  VTSS_EXTRACT_BITFIELD(x,14,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . L2_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_L2_SEL(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_L2_SEL     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_L2_SEL(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . L1_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_L1_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_L1_SEL     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_L1_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . L0_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_L0_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_L0_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_L0_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . H3_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_H3_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_H3_SEL     VTSS_ENCODE_BITMASK(6,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_H3_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . H2_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_H2_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_H2_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_H2_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . H1_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_H1_SEL(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_H1_SEL     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_H1_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_STAT1 . H0_SEL
 */
#define  VTSS_F_EXP_EXP_STATUS_STAT1_H0_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_EXP_STATUS_STAT1_H0_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_EXP_STATUS_STAT1_H0_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:EXP_STATUS:INTR_EN
 */
#define VTSS_EXP_EXP_STATUS_INTR_EN          VTSS_IOREG(0x1e, 1, 0xf103)

/** 
 * \brief
 * Allow L3_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L3_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L3_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(23)

/** 
 * \brief
 * Allow L2_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L2_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L2_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(22)

/** 
 * \brief
 * Allow L1_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L1_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L1_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(21)

/** 
 * \brief
 * Allow L0_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L0_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L0_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(20)

/** 
 * \brief
 * Allow H3_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H3_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H3_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(19)

/** 
 * \brief
 * Allow H2_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H2_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H2_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(18)

/** 
 * \brief
 * Allow H1_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H1_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H1_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(17)

/** 
 * \brief
 * Allow H0_COND_ALT_UNF_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H0_COND_ALT_UNF_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H0_COND_ALT_UNF_DET_INTR_EN  VTSS_BIT(16)

/** 
 * \brief
 * Allow L3_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L3_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L3_COND_ALT_DET_INTR_EN  VTSS_BIT(15)

/** 
 * \brief
 * Allow L2_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L2_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L2_COND_ALT_DET_INTR_EN  VTSS_BIT(14)

/** 
 * \brief
 * Allow L1_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L1_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L1_COND_ALT_DET_INTR_EN  VTSS_BIT(13)

/** 
 * \brief
 * Allow L0_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L0_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L0_COND_ALT_DET_INTR_EN  VTSS_BIT(12)

/** 
 * \brief
 * Allow H3_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H3_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H3_COND_ALT_DET_INTR_EN  VTSS_BIT(11)

/** 
 * \brief
 * Allow H2_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H2_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H2_COND_ALT_DET_INTR_EN  VTSS_BIT(10)

/** 
 * \brief
 * Allow H1_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H1_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H1_COND_ALT_DET_INTR_EN  VTSS_BIT(9)

/** 
 * \brief
 * Allow H0_COND_ALT_DET_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H0_COND_ALT_DET_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H0_COND_ALT_DET_INTR_EN  VTSS_BIT(8)

/** 
 * \brief
 * Enable L3_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L3_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L3_SWITCH_INTR_EN  VTSS_BIT(7)

/** 
 * \brief
 * Enable L2_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L2_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L2_SWITCH_INTR_EN  VTSS_BIT(6)

/** 
 * \brief
 * Enable L1_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L1_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L1_SWITCH_INTR_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable L0_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . L0_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_L0_SWITCH_INTR_EN  VTSS_BIT(4)

/** 
 * \brief
 * Enable H3_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H3_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H3_SWITCH_INTR_EN  VTSS_BIT(3)

/** 
 * \brief
 * Enable H2_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H2_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H2_SWITCH_INTR_EN  VTSS_BIT(2)

/** 
 * \brief
 * Enable H1_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H1_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H1_SWITCH_INTR_EN  VTSS_BIT(1)

/** 
 * \brief
 * Enable H0_SWITCH_STICKY to propogate to INTR
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR_EN . H0_SWITCH_INTR_EN
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_EN_H0_SWITCH_INTR_EN  VTSS_BIT(0)


/** 
 * \details
 * Register: \a EXP:EXP_STATUS:INTR
 */
#define VTSS_EXP_EXP_STATUS_INTR             VTSS_IOREG(0x1e, 1, 0xf104)

/** 
 * \brief
 * L3 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L3_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L3_COND_ALT_UNF_DET_STICKY  VTSS_BIT(23)

/** 
 * \brief
 * L2 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L2_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L2_COND_ALT_UNF_DET_STICKY  VTSS_BIT(22)

/** 
 * \brief
 * L1 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L1_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L1_COND_ALT_UNF_DET_STICKY  VTSS_BIT(21)

/** 
 * \brief
 * L0 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L0_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L0_COND_ALT_UNF_DET_STICKY  VTSS_BIT(20)

/** 
 * \brief
 * H3 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H3_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H3_COND_ALT_UNF_DET_STICKY  VTSS_BIT(19)

/** 
 * \brief
 * H2 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H2_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H2_COND_ALT_UNF_DET_STICKY  VTSS_BIT(18)

/** 
 * \brief
 * H1 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H1_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H1_COND_ALT_UNF_DET_STICKY  VTSS_BIT(17)

/** 
 * \brief
 * H0 COND_ALT (unfiltered) change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H0_COND_ALT_UNF_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H0_COND_ALT_UNF_DET_STICKY  VTSS_BIT(16)

/** 
 * \brief
 * L3 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L3_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L3_COND_ALT_DET_STICKY  VTSS_BIT(15)

/** 
 * \brief
 * L2 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L2_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L2_COND_ALT_DET_STICKY  VTSS_BIT(14)

/** 
 * \brief
 * L1 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L1_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L1_COND_ALT_DET_STICKY  VTSS_BIT(13)

/** 
 * \brief
 * L0 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L0_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L0_COND_ALT_DET_STICKY  VTSS_BIT(12)

/** 
 * \brief
 * H3 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H3_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H3_COND_ALT_DET_STICKY  VTSS_BIT(11)

/** 
 * \brief
 * H2 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H2_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H2_COND_ALT_DET_STICKY  VTSS_BIT(10)

/** 
 * \brief
 * H1 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H1_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H1_COND_ALT_DET_STICKY  VTSS_BIT(9)

/** 
 * \brief
 * H0 filetered COND_ALT change detected
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H0_COND_ALT_DET_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H0_COND_ALT_DET_STICKY  VTSS_BIT(8)

/** 
 * \brief
 * L3 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L3_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L3_SWITCH_STICKY  VTSS_BIT(7)

/** 
 * \brief
 * L2 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L2_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L2_SWITCH_STICKY  VTSS_BIT(6)

/** 
 * \brief
 * L1 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L1_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L1_SWITCH_STICKY  VTSS_BIT(5)

/** 
 * \brief
 * L0 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . L0_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_L0_SWITCH_STICKY  VTSS_BIT(4)

/** 
 * \brief
 * H3 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H3_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H3_SWITCH_STICKY  VTSS_BIT(3)

/** 
 * \brief
 * H2 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H2_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H2_SWITCH_STICKY  VTSS_BIT(2)

/** 
 * \brief
 * H1 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H1_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H1_SWITCH_STICKY  VTSS_BIT(1)

/** 
 * \brief
 * H0 source selection has changed
 *
 * \details 
 * Field: VTSS_EXP_EXP_STATUS_INTR . H0_SWITCH_STICKY
 */
#define  VTSS_F_EXP_EXP_STATUS_INTR_H0_SWITCH_STICKY  VTSS_BIT(0)

/**
 * Register Group: \a EXP:HOST0_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:HOST0_CFG:H0_SRC_SEL
 */
#define VTSS_EXP_HOST0_CFG_H0_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf105)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Line 0 link status
 * 13 = Line 1 link status
 * 14 = Line 2 link status
 * 15 = Line 3 link status
 * 16 = Line 0 serdes los
 * 17 = Line 1 serdes los
 * 18 = Line 2 serdes los
 * 19 = Line 3 serdes los
 * 20 = Line 0 10g wis lof
 * 21 = Line 1 10g wis lof
 * 22 = Line 2 10g wis lof
 * 23 = Line 3 10g wis lof
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_HOST0_CFG_H0_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_HOST0_CFG_H0_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_HOST0_CFG_H0_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_HOST0_CFG_H0_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_HOST0_CFG_H0_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_HOST0_CFG_H0_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_HOST0_CFG_H0_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_HOST0_CFG_H0_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_HOST0_CFG_H0_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:HOST0_CFG:H0_FILTER
 */
#define VTSS_EXP_HOST0_CFG_H0_FILTER         VTSS_IOREG(0x1e, 1, 0xf106)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_HOST0_CFG_H0_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_HOST0_CFG_H0_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_HOST0_CFG_H0_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_HOST0_CFG_H0_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_HOST0_CFG_H0_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_HOST0_CFG_H0_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST0_CFG_H0_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_HOST0_CFG_H0_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_HOST0_CFG_H0_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_HOST0_CFG_H0_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:HOST1_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:HOST1_CFG:H1_SRC_SEL
 */
#define VTSS_EXP_HOST1_CFG_H1_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf107)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Line 0 link status
 * 13 = Line 1 link status
 * 14 = Line 2 link status
 * 15 = Line 3 link status
 * 16 = Line 0 serdes los
 * 17 = Line 1 serdes los
 * 18 = Line 2 serdes los
 * 19 = Line 3 serdes los
 * 20 = Line 0 10g wis lof
 * 21 = Line 1 10g wis lof
 * 22 = Line 2 10g wis lof
 * 23 = Line 3 10g wis lof
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_HOST1_CFG_H1_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_HOST1_CFG_H1_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_HOST1_CFG_H1_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_HOST1_CFG_H1_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_HOST1_CFG_H1_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_HOST1_CFG_H1_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_HOST1_CFG_H1_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_HOST1_CFG_H1_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_HOST1_CFG_H1_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:HOST1_CFG:H1_FILTER
 */
#define VTSS_EXP_HOST1_CFG_H1_FILTER         VTSS_IOREG(0x1e, 1, 0xf108)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_HOST1_CFG_H1_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_HOST1_CFG_H1_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_HOST1_CFG_H1_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_HOST1_CFG_H1_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_HOST1_CFG_H1_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_HOST1_CFG_H1_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST1_CFG_H1_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_HOST1_CFG_H1_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_HOST1_CFG_H1_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_HOST1_CFG_H1_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:HOST2_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:HOST2_CFG:H2_SRC_SEL
 */
#define VTSS_EXP_HOST2_CFG_H2_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf109)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Line 0 link status
 * 13 = Line 1 link status
 * 14 = Line 2 link status
 * 15 = Line 3 link status
 * 16 = Line 0 serdes los
 * 17 = Line 1 serdes los
 * 18 = Line 2 serdes los
 * 19 = Line 3 serdes los
 * 20 = Line 0 10g wis lof
 * 21 = Line 1 10g wis lof
 * 22 = Line 2 10g wis lof
 * 23 = Line 3 10g wis lof
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_HOST2_CFG_H2_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_HOST2_CFG_H2_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_HOST2_CFG_H2_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_HOST2_CFG_H2_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_HOST2_CFG_H2_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_HOST2_CFG_H2_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_HOST2_CFG_H2_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_HOST2_CFG_H2_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_HOST2_CFG_H2_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:HOST2_CFG:H2_FILTER
 */
#define VTSS_EXP_HOST2_CFG_H2_FILTER         VTSS_IOREG(0x1e, 1, 0xf10a)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_HOST2_CFG_H2_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_HOST2_CFG_H2_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_HOST2_CFG_H2_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_HOST2_CFG_H2_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_HOST2_CFG_H2_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_HOST2_CFG_H2_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST2_CFG_H2_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_HOST2_CFG_H2_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_HOST2_CFG_H2_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_HOST2_CFG_H2_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:HOST3_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:HOST3_CFG:H3_SRC_SEL
 */
#define VTSS_EXP_HOST3_CFG_H3_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf10b)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Line 0 link status
 * 13 = Line 1 link status
 * 14 = Line 2 link status
 * 15 = Line 3 link status
 * 16 = Line 0 serdes los
 * 17 = Line 1 serdes los
 * 18 = Line 2 serdes los
 * 19 = Line 3 serdes los
 * 20 = Line 0 10g wis lof
 * 21 = Line 1 10g wis lof
 * 22 = Line 2 10g wis lof
 * 23 = Line 3 10g wis lof
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_HOST3_CFG_H3_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_HOST3_CFG_H3_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_HOST3_CFG_H3_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_HOST3_CFG_H3_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_HOST3_CFG_H3_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_HOST3_CFG_H3_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_HOST3_CFG_H3_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default line rx from which host tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_HOST3_CFG_H3_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_HOST3_CFG_H3_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:HOST3_CFG:H3_FILTER
 */
#define VTSS_EXP_HOST3_CFG_H3_FILTER         VTSS_IOREG(0x1e, 1, 0xf10c)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_HOST3_CFG_H3_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_HOST3_CFG_H3_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_HOST3_CFG_H3_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_HOST3_CFG_H3_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_HOST3_CFG_H3_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_HOST3_CFG_H3_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_HOST3_CFG_H3_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_HOST3_CFG_H3_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_HOST3_CFG_H3_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_HOST3_CFG_H3_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:LINE0_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:LINE0_CFG:L0_SRC_SEL
 */
#define VTSS_EXP_LINE0_CFG_L0_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf10d)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Host 0 link status
 * 13 = Host 1 link status
 * 14 = Host 2 link status
 * 15 = Host 3 link status
 * 16 = Host 0 serdes los
 * 17 = Host 1 serdes los
 * 18 = Host 2 serdes los
 * 19 = Host 3 serdes los
 * 20 = Always false
 * 21 = Always false
 * 22 = Always false
 * 23 = Always false
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_LINE0_CFG_L0_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_LINE0_CFG_L0_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_LINE0_CFG_L0_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_LINE0_CFG_L0_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_LINE0_CFG_L0_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_LINE0_CFG_L0_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_LINE0_CFG_L0_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_LINE0_CFG_L0_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_LINE0_CFG_L0_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:LINE0_CFG:L0_FILTER
 */
#define VTSS_EXP_LINE0_CFG_L0_FILTER         VTSS_IOREG(0x1e, 1, 0xf10e)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_LINE0_CFG_L0_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_LINE0_CFG_L0_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_LINE0_CFG_L0_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_LINE0_CFG_L0_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_LINE0_CFG_L0_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_LINE0_CFG_L0_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE0_CFG_L0_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_LINE0_CFG_L0_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_LINE0_CFG_L0_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_LINE0_CFG_L0_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:LINE1_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:LINE1_CFG:L1_SRC_SEL
 */
#define VTSS_EXP_LINE1_CFG_L1_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf10f)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Host 0 link status
 * 13 = Host 1 link status
 * 14 = Host 2 link status
 * 15 = Host 3 link status
 * 16 = Host 0 serdes los
 * 17 = Host 1 serdes los
 * 18 = Host 2 serdes los
 * 19 = Host 3 serdes los
 * 20 = Always false
 * 21 = Always false
 * 22 = Always false
 * 23 = Always false
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_LINE1_CFG_L1_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_LINE1_CFG_L1_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_LINE1_CFG_L1_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_LINE1_CFG_L1_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_LINE1_CFG_L1_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_LINE1_CFG_L1_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_LINE1_CFG_L1_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_LINE1_CFG_L1_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_LINE1_CFG_L1_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:LINE1_CFG:L1_FILTER
 */
#define VTSS_EXP_LINE1_CFG_L1_FILTER         VTSS_IOREG(0x1e, 1, 0xf110)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_LINE1_CFG_L1_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_LINE1_CFG_L1_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_LINE1_CFG_L1_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_LINE1_CFG_L1_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_LINE1_CFG_L1_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_LINE1_CFG_L1_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE1_CFG_L1_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_LINE1_CFG_L1_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_LINE1_CFG_L1_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_LINE1_CFG_L1_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:LINE2_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:LINE2_CFG:L2_SRC_SEL
 */
#define VTSS_EXP_LINE2_CFG_L2_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf111)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Host 0 link status
 * 13 = Host 1 link status
 * 14 = Host 2 link status
 * 15 = Host 3 link status
 * 16 = Host 0 serdes los
 * 17 = Host 1 serdes los
 * 18 = Host 2 serdes los
 * 19 = Host 3 serdes los
 * 20 = Always false
 * 21 = Always false
 * 22 = Always false
 * 23 = Always false
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_LINE2_CFG_L2_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_LINE2_CFG_L2_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_LINE2_CFG_L2_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_LINE2_CFG_L2_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_LINE2_CFG_L2_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_LINE2_CFG_L2_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_LINE2_CFG_L2_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_LINE2_CFG_L2_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_LINE2_CFG_L2_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:LINE2_CFG:L2_FILTER
 */
#define VTSS_EXP_LINE2_CFG_L2_FILTER         VTSS_IOREG(0x1e, 1, 0xf112)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_LINE2_CFG_L2_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_LINE2_CFG_L2_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_LINE2_CFG_L2_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_LINE2_CFG_L2_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_LINE2_CFG_L2_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_LINE2_CFG_L2_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE2_CFG_L2_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_LINE2_CFG_L2_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_LINE2_CFG_L2_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_LINE2_CFG_L2_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a EXP:LINE3_CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a EXP:LINE3_CFG:L3_SRC_SEL
 */
#define VTSS_EXP_LINE3_CFG_L3_SRC_SEL        VTSS_IOREG(0x1e, 1, 0xf113)

/** 
 * \brief
 * Event source used to trigger a switch to ALT_CH
 *
 * \details 
 * 0 = GPIO0
 * 1 = GPIO1
 * 2 = GPIO2
 * 3 = GPIO3
 * 4 = GPIO4
 * 5 = GPIO5
 * 6 = GPIO6
 * 7 = GPIO7
 * 8 = Always false
 * 9 = Always false
 * 10 = Always false
 * 11 = Always false
 * 12 = Host 0 link status
 * 13 = Host 1 link status
 * 14 = Host 2 link status
 * 15 = Host 3 link status
 * 16 = Host 0 serdes los
 * 17 = Host 1 serdes los
 * 18 = Host 2 serdes los
 * 19 = Host 3 serdes los
 * 20 = Always false
 * 21 = Always false
 * 22 = Always false
 * 23 = Always false
 * 24 = Always false
 * 25 = Always false
 * 26 = Always false
 * 27 = Always false
 * 28 = Always false
 * 29 = Always false
 * 30 = Always false
 * 31 = Always true

 *
 * Field: VTSS_EXP_LINE3_CFG_L3_SRC_SEL . ALT_SRC
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_SRC_SEL_ALT_SRC(x)  VTSS_ENCODE_BITFIELD(x,8,5)
#define  VTSS_M_EXP_LINE3_CFG_L3_SRC_SEL_ALT_SRC     VTSS_ENCODE_BITMASK(8,5)
#define  VTSS_X_EXP_LINE3_CFG_L3_SRC_SEL_ALT_SRC(x)  VTSS_EXTRACT_BITFIELD(x,8,5)

/** 
 * \brief
 * Enable filtering of condition source
 *
 * \details 
 * 0 = No filtering (assertion of selected condition source causes
 * immediate switch to ALT_CH)
 * 1 = Filtering enabled
 *
 * Field: VTSS_EXP_LINE3_CFG_L3_SRC_SEL . FILTER_EN
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_SRC_SEL_FILTER_EN  VTSS_BIT(5)

/** 
 * \brief
 * Enable conditional switching to ALTernate channel
 *
 * \details 
 * 0 = Force default channel
 * 1 = Allow switching to ALTernate channel based on source selection and
 * filtering
 *
 * Field: VTSS_EXP_LINE3_CFG_L3_SRC_SEL . ALT_EN
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_SRC_SEL_ALT_EN  VTSS_BIT(4)

/** 
 * \brief
 * Alternate host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_SRC_SEL . ALT_CH
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_SRC_SEL_ALT_CH(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_EXP_LINE3_CFG_L3_SRC_SEL_ALT_CH     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_EXP_LINE3_CFG_L3_SRC_SEL_ALT_CH(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Default host rx from which line tx receives traffic
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_SRC_SEL . DEFAULT_CH
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_SRC_SEL_DEFAULT_CH(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_EXP_LINE3_CFG_L3_SRC_SEL_DEFAULT_CH     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_EXP_LINE3_CFG_L3_SRC_SEL_DEFAULT_CH(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \details
 * Register: \a EXP:LINE3_CFG:L3_FILTER
 */
#define VTSS_EXP_LINE3_CFG_L3_FILTER         VTSS_IOREG(0x1e, 1, 0xf114)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB2316 is the
 * upper 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_FILTER . COUNTB2316
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_FILTER_COUNTB2316(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_EXP_LINE3_CFG_L3_FILTER_COUNTB2316     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_EXP_LINE3_CFG_L3_FILTER_COUNTB2316(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/** 
 * \brief
 * COUNTB is the number of CSR clock cycles needed for selected condition
 * to be continously false before event can be cleared.  COUNTB70 is the
 * lower 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_FILTER . COUNTB70
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_FILTER_COUNTB70(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_EXP_LINE3_CFG_L3_FILTER_COUNTB70     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_EXP_LINE3_CFG_L3_FILTER_COUNTB70(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA2316 is the upper
 * 8 bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_FILTER . COUNTA2316
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_FILTER_COUNTA2316(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_EXP_LINE3_CFG_L3_FILTER_COUNTA2316     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_EXP_LINE3_CFG_L3_FILTER_COUNTA2316(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * COUNTA is the number of CSR clock cycles needed for selected condition
 * to be continously true before event can be set.  COUNTA70 is the lower 8
 * bits of this 24 bit threshold.
 *
 * \details 
 * Field: VTSS_EXP_LINE3_CFG_L3_FILTER . COUNTA70
 */
#define  VTSS_F_EXP_LINE3_CFG_L3_FILTER_COUNTA70(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_EXP_LINE3_CFG_L3_FILTER_COUNTA70     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_EXP_LINE3_CFG_L3_FILTER_COUNTA70(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


#endif /* _VTSS_MALIBU_REGS_EXP_H_ */
