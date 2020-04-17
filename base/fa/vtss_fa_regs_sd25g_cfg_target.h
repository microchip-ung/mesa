// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_REGS_SD25G_CFG_TARGET_H_
#define _VTSS_FA_REGS_SD25G_CFG_TARGET_H_

#include "vtss_fa_regs_common.h"

/***********************************************************************
 *
 * Target: \a SD25G_CFG_TARGET
 *
 * \see vtss_target_SD25G_CFG_TARGET_e
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_RESET
 *
 * Not documented
 */


/** 
 * \brief Software Reset for Serializer Clock
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SD_RESET:SD_SER_RST
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_SER_RST(target)  VTSS_IOREG(target,0x0)

/** 
 * \brief
 * Software Reset for SD Serializer Clock
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_SER_RST . SER_RST
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_SER_RST_SER_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_SER_RST_SER_RST  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_SER_RST_SER_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/** 
 * \brief Software Reset for Deserializer Clock
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SD_RESET:SD_DES_RST
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_DES_RST(target)  VTSS_IOREG(target,0x1)

/** 
 * \brief
 * Software Reset for SD Deserializer Clock
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_DES_RST . DES_RST
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_DES_RST_DES_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_DES_RST_DES_RST  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_DES_RST_DES_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_LANE_CFG_STAT
 *
 * SD Lane configuration and Status
 */


/** 
 * \brief SD Lane Configuration 
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a SD25G_CFG_TARGET:SD_LANE_CFG_STAT:SD_LANE_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(target)  VTSS_IOREG(target,0x2)

/** 
 * \brief
 * Software Reset for SD Lane macro for fundamental reset.
 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . MACRO_RST
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_MACRO_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Software Reset for SD configuration interface.
 *
 * \details 
 * 1: Reset active
 * 0: Reset incactive
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . EXT_CFG_RST
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST  VTSS_BIT(1)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . HWT_MULTI_LANE_MODE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_HWT_MULTI_LANE_MODE(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_HWT_MULTI_LANE_MODE  VTSS_BIT(4)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_HWT_MULTI_LANE_MODE(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/** 
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS2PMA_PHYMODE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_PHYMODE(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_PHYMODE     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_PHYMODE(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Software Reset for SD Lane reset.

 *
 * \details 
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . LANE_RST
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST  VTSS_BIT(8)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/** 
 * \brief
 * PCS link train control: pre-equalization control of TX
 *
 * \details 
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_EN_ADV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_ADV(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_ADV  VTSS_BIT(9)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_ADV(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/** 
 * \brief
 * PCS link train control: TX data path control
 *
 * \details 
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_EN_MAIN
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_MAIN  VTSS_BIT(10)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/** 
 * \brief
 * PCS link train control: 1st-stage post-equalization
 *
 * \details 
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_EN_DLY
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_DLY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_DLY  VTSS_BIT(11)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_DLY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/** 
 * \brief
 * PCS link train control: pre-equalization level control of TX
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_TAP_ADV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_ADV(x)  VTSS_ENCODE_BITFIELD(x,12,4)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_ADV     VTSS_ENCODE_BITMASK(12,4)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_ADV(x)  VTSS_EXTRACT_BITFIELD(x,12,4)

/** 
 * \brief
 * PCS link train control: TX data path setting
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_TAP_MAIN
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_MAIN(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_MAIN  VTSS_BIT(16)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_MAIN(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/** 
 * \brief
 * PCS link train control: 1st-stage post-equalization level control of TX
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_TAP_DLY
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_DLY(x)  VTSS_ENCODE_BITFIELD(x,17,5)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_DLY     VTSS_ENCODE_BITMASK(17,5)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_TAP_DLY(x)  VTSS_EXTRACT_BITFIELD(x,17,5)

/** 
 * \brief
 * RX traditional eye scan monitor enable
 *
 * \details 
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_ISCAN_EN
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_ISCAN_EN(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_ISCAN_EN  VTSS_BIT(22)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_ISCAN_EN(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/** 
 * \brief
 * RX fast eye scan monitor enable
 *
 * \details 
 * 1: enable
 * 0: disable
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS_EN_FAST_ISCAN
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_FAST_ISCAN(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_FAST_ISCAN  VTSS_BIT(23)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS_EN_FAST_ISCAN(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/** 
 * \brief
 * Controls transmitter voltage swing level
 *
 * \details 
 * 0: full swing
 * 1: low swing
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS2PMA_TXSWING
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXSWING(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXSWING  VTSS_BIT(24)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXSWING(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/** 
 * \brief
 * Transmit path electrical idle
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS2PMA_TXEI
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXEI(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXEI  VTSS_BIT(25)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXEI(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/** 
 * \brief
 * Transmitter voltage level control
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG . PCS2PMA_TXMARGIN
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXMARGIN(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXMARGIN     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG_PCS2PMA_TXMARGIN(x)  VTSS_EXTRACT_BITFIELD(x,26,3)


/** 
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a SD25G_CFG_TARGET:SD_LANE_CFG_STAT:SD_LANE_CFG2
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2(target)  VTSS_IOREG(target,0x3)

/** 
 * \brief
 * TX/RX data width selection
 *
 * \details 
 * 000: 10-bit mode
 * 001: 16-bit mode
 * 010: 20-bit mode
 * 011: 32-bit mode
 * 100: 40-bit mode
 * 101: 64-bit mode
 * 110: Reserved
 * 111: Reserved
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . DATA_WIDTH_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_DATA_WIDTH_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_DATA_WIDTH_SEL     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_DATA_WIDTH_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * PMA transmit clock frequency selection
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . PMA_TXCK_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_TXCK_SEL(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_TXCK_SEL     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_TXCK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/** 
 * \brief
 * PMA receiver clock frequency selection
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . PMA_RXDIV_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_RXDIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_RXDIV_SEL     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_PMA_RXDIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . PCS2PMA_TX_SPEED
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_PCS2PMA_TX_SPEED(x)  VTSS_ENCODE_BITFIELD(x,9,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_PCS2PMA_TX_SPEED     VTSS_ENCODE_BITMASK(9,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_PCS2PMA_TX_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,9,2)

/** 
 * \brief
 * TXFIFO clock divider
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . TXFIFO_CK_DIV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_TXFIFO_CK_DIV(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_TXFIFO_CK_DIV     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_TXFIFO_CK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * RXFIFO clock divider
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . RXFIFO_CK_DIV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_RXFIFO_CK_DIV(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_RXFIFO_CK_DIV     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_RXFIFO_CK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/** 
 * \brief
 * PMA VCO post divider ratio selection (or reference clock multiplying
 * factor)
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . HWT_VCO_DIV_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_VCO_DIV_SEL(x)  VTSS_ENCODE_BITFIELD(x,17,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_VCO_DIV_SEL     VTSS_ENCODE_BITMASK(17,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_VCO_DIV_SEL(x)  VTSS_EXTRACT_BITFIELD(x,17,3)

/** 
 * \brief
 * PLL multiplying factor (Fref*N)
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . HWT_CFG_SEL_DIV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_CFG_SEL_DIV(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_CFG_SEL_DIV     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_CFG_SEL_DIV(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . HWT_PRE_DIVSEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_PRE_DIVSEL(x)  VTSS_ENCODE_BITFIELD(x,24,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_PRE_DIVSEL     VTSS_ENCODE_BITMASK(24,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_HWT_PRE_DIVSEL(x)  VTSS_EXTRACT_BITFIELD(x,24,2)

/** 
 * \brief
 * PMA transmit clock full/subrate frequency selection
 *
 * \details 
 * 00: full
 * 01: 1/2
 * 10: 1/4
 * 11: 1/8
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . TXRATE_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_TXRATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_TXRATE_SEL     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_TXRATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,26,3)

/** 
 * \brief
 * PMA receive clock full/subrate frequency selection
 *
 * \details 
 * 00: full
 * 01: 1/2
 * 10: 1/4
 * 11: 1/8
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_CFG2 . RXRATE_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG2_RXRATE_SEL(x)  VTSS_ENCODE_BITFIELD(x,29,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG2_RXRATE_SEL     VTSS_ENCODE_BITMASK(29,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_CFG2_RXRATE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,29,3)


/** 
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a SD25G_CFG_TARGET:SD_LANE_CFG_STAT:SD_LANE_STAT
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_LANE_STAT(target)  VTSS_IOREG(target,0x4)

/** 
 * \brief
 * PMA Reset done. Asserted when reset is completed following MACRO_RST
 * deassertion.
 *
 * \details 
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_STAT . PMA_RST_DONE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_STAT_PMA_RST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_STAT_PMA_RST_DONE  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_STAT_PMA_RST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Lane Reset done. Asserted when reset is completed following LANE_RST
 * deassertion
 *
 * \details 
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_STAT . LANE_RST_DONE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_STAT_LANE_RST_DONE(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_STAT_LANE_RST_DONE  VTSS_BIT(1)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_STAT_LANE_RST_DONE(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Access to internal serdes state
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_LANE_STAT . DBG_OBS
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_LANE_STAT_DBG_OBS(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD25G_CFG_TARGET_SD_LANE_STAT_DBG_OBS     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD25G_CFG_TARGET_SD_LANE_STAT_DBG_OBS(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_CFG
 *
 * SD Signal Detect Configuration
 */


/** 
 * \brief SD Signal Detect Configuration
 *
 * \details
 * Serdes Signal Detect Configuration
 *
 * Register: \a SD25G_CFG_TARGET:SD_CFG:SD_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_CFG(target)  VTSS_IOREG(target,0x5)

/** 
 * \brief
 * Signal Detect Enable
 *
 * \details 
 * 0: The Signal Detect input pin is ignored active Signal Detect is
 * assumed at all times
 * 1: The Signal Detect input pin is used to determine if a signal is
 * detected
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_CFG . SD_ENA
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_CFG_SD_ENA  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_CFG_SD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details 
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_CFG . SD_POL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_POL(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_CFG_SD_POL  VTSS_BIT(1)
#define  VTSS_X_SD25G_CFG_TARGET_SD_CFG_SD_POL(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details 
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_CFG . SD_SEL
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_CFG_SD_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_CFG_SD_SEL  VTSS_BIT(2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_CFG_SD_SEL(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_CLK_GATE
 *
 * Gating all macro generated clocks
 */


/** 
 * \brief Gating all macro generated clocks
 *
 * \details
 * Gate SD generated clocks during speed change
 *
 * Register: \a SD25G_CFG_TARGET:SD_CLK_GATE:SD_CLK_GATE
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_CLK_GATE(target)  VTSS_IOREG(target,0x6)

/** 
 * \details 
 * 0 :	enable macro clock generation towards core (RX & TX)
 * 1 :	disable (gate) macro clock generation towards core (TX & TX)
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_CLK_GATE . SD_CLK_GATE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_CLK_GATE_SD_CLK_GATE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SD_CLK_GATE_SD_CLK_GATE  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SD_CLK_GATE_SD_CLK_GATE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_PWR_CFG
 *
 * SD Power configuration
 */


/** 
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SD_PWR_CFG:NORMAL_MODE
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_NORMAL_MODE(target)  VTSS_IOREG(target,0x7)

/** 
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode
 * 
 * Bits 17 to 19 are for TX direction, other bits are for RX direction.
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details 
 * Refer to GUC documentation
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_NORMAL_MODE . NORMAL_MODE
 */
#define  VTSS_F_SD25G_CFG_TARGET_NORMAL_MODE_NORMAL_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_SD25G_CFG_TARGET_NORMAL_MODE_NORMAL_MODE     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_SD25G_CFG_TARGET_NORMAL_MODE_NORMAL_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,25)


/** 
 * \brief Power settings for QUIET mode.
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SD_PWR_CFG:QUIET_MODE_6G
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_QUIET_MODE_6G(target)  VTSS_IOREG(target,0x8)

/** 
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode.
 * 
 * Bits 17 to 19 are for TX direction, other bits are for RX direction.
 *
 * \details 
 * Refer to GUC documentation
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_QUIET_MODE_6G . QUIET_MODE
 */
#define  VTSS_F_SD25G_CFG_TARGET_QUIET_MODE_6G_QUIET_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,25)
#define  VTSS_M_SD25G_CFG_TARGET_QUIET_MODE_6G_QUIET_MODE     VTSS_ENCODE_BITMASK(0,25)
#define  VTSS_X_SD25G_CFG_TARGET_QUIET_MODE_6G_QUIET_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,25)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_ANEG_CFG
 *
 * SD_ANEG_CFG
 */


/** 
 * \brief SD_KR_ANEG_MODE
 *
 * \details
 * Configure ANEG to SerDes (TX) behavior
 *
 * Register: \a SD25G_CFG_TARGET:SD_ANEG_CFG:SD_KR_ANEG_MODE
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_KR_ANEG_MODE(target)  VTSS_IOREG(target,0x9)

/** 
 * \brief
 * Configure how ANEG TX data is multiplexed into Serial Data stream
 *
 * \details 
 * 00: auto (TX connection to Serializer controlled by KR block)
 * 01: reserved
 * 10: force off (i.e. ANEG TX data never connected to Serializer)
 * 11: force on (i.e. ANEG TX data always connected to Serializer)
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_KR_ANEG_MODE . TX_ANEG_MODE
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_EXTCFG_CFG
 *
 * Configuration of SD local parallel configuration interface (EXT_CFG)
 */


/** 
 * \brief Configuration of SD local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SD_EXTCFG_CFG:SD_EXTCFG_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG(target)  VTSS_IOREG(target,0xa)

/** 
 * \brief
 * Clock divider for EXTCFG Master. 
 * Divide the system clock by N + 2 to be used as EXTCFG master clock for
 * SerDes configuration.
 *
 * \details 
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG . CLK_DIV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_EXTCFG_CFG_CLK_DIV     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_EXTCFG_CFG_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,0,3)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.
 * 
 * Additional N wait states before write enable is asserted after driving
 * address and write data.
 *
 * \details 
 * Total Wait States are N+2 clock cycles of EXT_CFG clock signal. 
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG . WS_SETUP_WR
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_SETUP_WR(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.
 * 
 * Additional N wait states before write enable is deasserted again.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG . WS_EXEC_WR
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_WR(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.
 * 
 * Additional N wait states before start of next write access.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+2 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG . WS_HOLD_WR
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_HOLD_WR(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/** 
 * \brief
 * EXTCFG Interface Timing configuration.
 * 
 * Additional N wait states before read data is sampled.
 *
 * \details 
 * Total Wait States (i.e. pulse width) are N+3 clock cycles of EXT_CFG
 * clock signal. 
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_EXTCFG_CFG . WS_EXEC_RD
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_ENCODE_BITFIELD(x,16,2)
#define  VTSS_M_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD     VTSS_ENCODE_BITMASK(16,2)
#define  VTSS_X_SD25G_CFG_TARGET_SD_EXTCFG_CFG_WS_EXEC_RD(x)  VTSS_EXTRACT_BITFIELD(x,16,2)

/**
 * Register Group: \a SD25G_CFG_TARGET:SD_FIFO_DELAY
 *
 * Registers for precise FIFO delay measurement
 */


/** 
 * \brief FIFO delay measurement configuration
 *
 * \details
 * FIFO delay measurement configuration register
 *
 * Register: \a SD25G_CFG_TARGET:SD_FIFO_DELAY:SD_DELAY_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_DELAY_CFG(target)  VTSS_IOREG(target,0xb)

/** 
 * \brief
 * Configures the number of cycles the skew detector should run before
 * returning serdes delay
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_DELAY_CFG . SAMPLE_TIME
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_SD25G_CFG_TARGET_SD_DELAY_CFG_SAMPLE_TIME     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_SD25G_CFG_TARGET_SD_DELAY_CFG_SAMPLE_TIME(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a SD25G_CFG_TARGET:SD_FIFO_DELAY:SD_DELAY_VAR
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SD_DELAY_VAR(target)  VTSS_IOREG(target,0xc)

/** 
 * \brief
 * Rx delay reported as 2**16 times the Serdes fifo size in time, which
 * must be well known to determine the delay. Example: A 80 bit fifo with a
 * bit clock of 800 picosec, and a skew of 16384 means a serdes delay of 80
 * x (800 picosec) x (16384/65536) = 1.6 nanosec.
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_DELAY_VAR . RX_DELAY_VAR
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_SD25G_CFG_TARGET_SD_DELAY_VAR_RX_DELAY_VAR     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_SD25G_CFG_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/** 
 * \brief
 * Tx delay reported as 2**16 times the Serdes fifo size in time, which
 * must be well known to determine the delay. Example: A 80 bit fifo with a
 * bit clock of 800 picosec, and a skew of 16384 means a serdes delay of 80
 * x (800 picosec) x (16384/65536) = 1.6 nanosec.
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SD_DELAY_VAR . TX_DELAY_VAR
 */
#define  VTSS_F_SD25G_CFG_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_SD25G_CFG_TARGET_SD_DELAY_VAR_TX_DELAY_VAR     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_SD25G_CFG_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * Register Group: \a SD25G_CFG_TARGET:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/** 
 * \brief 10G Recovered Clock Configuration
 *
 * \details
 * Register: \a SD25G_CFG_TARGET:SYNC_ETH_CFG:SYNC_ETH_SD_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG(target)  VTSS_IOREG(target,0xd)

/** 
 * \brief
 * Set to enable auto-squelching for sync. ethernet clock output: when set
 * the clock output will stop toggling (keep its last value constantly)
 * when when SerDes looses signal detect state.
 *
 * \details 
 * Field: ::VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG . SD_AUTO_SQUELCH_ENA
 */
#define  VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_AUTO_SQUELCH_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Use Link Status information of connected PCS or extender for squelching
 * of recovered clock.
 *
 * \details 
 * 1: Use link status information for squelching
 * 0: Don't use link status information for squelching

 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG . SD_LINK_STAT_ENA
 */
#define  VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA  VTSS_BIT(1)
#define  VTSS_X_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_LINK_STAT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Divider setting for the SD recovered clock output. These settings are
 * applied prior to sending recovered clock to the optional PAD-divider
 * (see HSIOWRAP::SYNC_ETH_CFG[X].SEL_RECO_CLK_DIV.)
 * For the TX clock recovery value 2 is also reserved, it is not possible
 * to divide by 66/32 for TX clock.
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 2
 * 2: Divide clock by (66/32)
 * 3: reserved
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG . SD_RECO_CLK_DIV
 */
#define  VTSS_F_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_SD25G_CFG_TARGET_SYNC_ETH_SD_CFG_SD_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * Register Group: \a SD25G_CFG_TARGET:HW_CFG
 *
 * Hardware Configuration
 */


/** 
 * \brief KR ANEG Configuration
 *
 * \details
 * Common KR ANEG configuration, used across all instances.
 *
 * Register: \a SD25G_CFG_TARGET:HW_CFG:KR_DATA_CFG
 *
 * @param target A \a ::vtss_target_SD25G_CFG_TARGET_e target
 */
#define VTSS_SD25G_CFG_TARGET_KR_DATA_CFG(target)  VTSS_IOREG(target,0xe)

/** 
 * \brief
 * Revert 10B data bus portion. 
 *
 * \details 
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_KR_DATA_CFG . REVERT_10B
 */
#define  VTSS_F_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_10B(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_10B  VTSS_BIT(0)
#define  VTSS_X_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_10B(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/** 
 * \brief
 * Revert 64B data bus portion for transmit direction. 
 *
 * \details 
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_KR_DATA_CFG . REVERT_64B_TX
 */
#define  VTSS_F_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_TX  VTSS_BIT(1)
#define  VTSS_X_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_TX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/** 
 * \brief
 * Revert 64B data bus portion for transmit direction. 
 *
 * \details 
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::VTSS_SD25G_CFG_TARGET_KR_DATA_CFG . REVERT_64B_RX
 */
#define  VTSS_F_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_RX  VTSS_BIT(2)
#define  VTSS_X_SD25G_CFG_TARGET_KR_DATA_CFG_REVERT_64B_RX(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


#endif /* _VTSS_FA_REGS_SD25G_CFG_TARGET_H_ */
