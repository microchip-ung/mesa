// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _LAN80XX_MALIBU25G_REGS_HOST_PMA_H_
#define _LAN80XX_MALIBU25G_REGS_HOST_PMA_H_

#include "regs_lan8042_common.h"

/***********************************************************************
 *
 * Target: \a HOST_PMA
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a HOST_PMA:SD_RESET
 *
 *  Software Reset for Serdes Tx/Rx
 */


/**
 * \brief Software reset bit for the PCS25G, PCS1G, and KR IP transmit functions
 *
 * \details
 * Register: \a HOST_PMA:SD_RESET:SD_SER_RST
 */
#define LAN80XX_HOST_PMA_SD_SER_RST             LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x8000)

/**
 * \brief
 * Software reset bit for the PCS25G, PCS1G, and KR IP transmit functions.
 * This bit does not reset any PMA/SerDes functions, but the reset signal
 * is synchronized to the PMA_TX_CK. The clock itself is not reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_PMA_SD_SER_RST . PCS_KR_TX_RST
 */
#define  LAN80XX_F_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST     LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_SER_RST_PCS_KR_TX_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Software reset bit for the PCS25G, PCS1G, and KR IP receive functions.
 *
 * \details
 * Register: \a HOST_PMA:SD_RESET:SD_DES_RST
 */
#define LAN80XX_HOST_PMA_SD_DES_RST             LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x8001)

/**
 * \brief
 * Software reset bit for the PCS25G, PCS1G, and KR IP receive functions.
 * This bit does not reset any PMA/SerDes functions, but the reset signal
 * is synchronized to the PMA_RX_CK. The clock itself is not reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_PMA_SD_DES_RST . PCS_KR_RX_RST
 */
#define  LAN80XX_F_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST     LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_DES_RST_PCS_KR_RX_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HOST_PMA:SD_LANE_CFG_STAT
 *
 * SD Lane configuration and Status
 */


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_0
 */
#define LAN80XX_HOST_PMA_SD_LANE_CFG_0          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8002)

/**
 * \brief
 * Software Reset for SD Lane macro fundamental reset.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . MACRO_RST
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_MACRO_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_MACRO_RST  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_MACRO_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Software Reset for SD configuration interface.
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . EXT_CFG_RST
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_EXT_CFG_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . PCS2PMA_PHYMODE
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE(x)  LAN80XX_ENCODE_BITFIELD(x,5,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE     LAN80XX_ENCODE_BITMASK(5,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_PCS2PMA_PHYMODE(x)  LAN80XX_EXTRACT_BITFIELD(x,5,3)

/**
 * \brief
 * Software Reset for SD Lane reset.

 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . LANE_RST
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_LANE_RST(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_LANE_RST  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_LANE_RST(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * PCS link train control: pre-equalization control of TX
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . PCS_EN_ADV
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_PCS_EN_ADV(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_PCS_EN_ADV  LAN80XX_BIT(9)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_PCS_EN_ADV(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * PCS link train control: TX data path control
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . PCS_EN_MAIN
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_PCS_EN_MAIN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),10,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_PCS_EN_MAIN  LAN80XX_BIT(10)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_PCS_EN_MAIN(x)  LAN80XX_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * PCS link train control: 1st-stage post-equalization
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . PCS_EN_DLY
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_PCS_EN_DLY(x)  LAN80XX_ENCODE_BITFIELD(!!(x),11,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_PCS_EN_DLY  LAN80XX_BIT(11)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_PCS_EN_DLY(x)  LAN80XX_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * PCS link train control: pre-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_0 . PCS_TAP_ADV
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_0_PCS_TAP_ADV(x)  LAN80XX_ENCODE_BITFIELD(x,12,4)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_0_PCS_TAP_ADV     LAN80XX_ENCODE_BITMASK(12,4)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_0_PCS_TAP_ADV(x)  LAN80XX_EXTRACT_BITFIELD(x,12,4)


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_1
 */
#define LAN80XX_HOST_PMA_SD_LANE_CFG_1          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8003)

/**
 * \brief
 * PCS link train control: TX data path setting
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS_TAP_MAIN
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_MAIN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * PCS link train control: 1st-stage post-equalization level control of TX
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS_TAP_DLY
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_DLY(x)  LAN80XX_ENCODE_BITFIELD(x,1,5)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_DLY     LAN80XX_ENCODE_BITMASK(1,5)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS_TAP_DLY(x)  LAN80XX_EXTRACT_BITFIELD(x,1,5)

/**
 * \brief
 * RX traditional eye scan monitor enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS_ISCAN_EN
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),6,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN  LAN80XX_BIT(6)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS_ISCAN_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * RX fast eye scan monitor enable
 *
 * \details
 * 1: enable
 * 0: disable
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS_EN_FAST_ISCAN
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),7,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN  LAN80XX_BIT(7)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS_EN_FAST_ISCAN(x)  LAN80XX_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Controls transmitter voltage swing level
 *
 * \details
 * 0: full swing
 * 1: low swing
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS2PMA_TXSWING
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING(x)  LAN80XX_ENCODE_BITFIELD(!!(x),8,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING  LAN80XX_BIT(8)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXSWING(x)  LAN80XX_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Transmit path electrical idle
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS2PMA_TXEI
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI(x)  LAN80XX_ENCODE_BITFIELD(!!(x),9,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI  LAN80XX_BIT(9)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXEI(x)  LAN80XX_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Transmitter voltage level control
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS2PMA_TXMARGIN
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TXMARGIN(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)

/**
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_1 . PCS2PMA_TX_SPEED
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED(x)  LAN80XX_ENCODE_BITFIELD(x,13,2)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED     LAN80XX_ENCODE_BITMASK(13,2)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_1_PCS2PMA_TX_SPEED(x)  LAN80XX_EXTRACT_BITFIELD(x,13,2)


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_2
 */
#define LAN80XX_HOST_PMA_SD_LANE_CFG_2          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8004)

/**
 * \brief
 * RXFIFO clock divider
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_2 . RXFIFO_CK_DIV
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_2_RXFIFO_CK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)

/**
 * \brief
 * TXFIFO clock divider
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_2 . TXFIFO_CK_DIV
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,3,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV     LAN80XX_ENCODE_BITMASK(3,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_2_TXFIFO_CK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * PMA transmit clock frequency selection
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_2 . PMA_TXCK_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,6,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL     LAN80XX_ENCODE_BITMASK(6,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_2_PMA_TXCK_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * PMA receiver clock frequency selection
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_2 . PMA_RXDIV_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_2_PMA_RXDIV_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)

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
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_2 . DATA_WIDTH_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,13,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL     LAN80XX_ENCODE_BITMASK(13,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_2_DATA_WIDTH_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,13,3)


/**
 * \brief SD Lane Configuration
 *
 * \details
 * Configuration of SD lane macro via core interface signals
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_CFG_3
 */
#define LAN80XX_HOST_PMA_SD_LANE_CFG_3          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8005)

/**
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_3 . HWT_PRE_DIVSEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_3_HWT_PRE_DIVSEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)

/**
 * \brief
 * PMA VCO post divider ratio selection (or reference clock multiplying
 * factor)
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_3 . HWT_VCO_DIV_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,2,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL     LAN80XX_ENCODE_BITMASK(2,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_3_HWT_VCO_DIV_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * PLL multiplying factor (Fref*N)
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_3 . HWT_CFG_SEL_DIV
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,5,4)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV     LAN80XX_ENCODE_BITMASK(5,4)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_3_HWT_CFG_SEL_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,5,4)

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
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_3 . TXRATE_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,10,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_3_TXRATE_SEL     LAN80XX_ENCODE_BITMASK(10,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_3_TXRATE_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,10,3)

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
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_CFG_3 . RXRATE_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,13,3)
#define  LAN80XX_M_HOST_PMA_SD_LANE_CFG_3_RXRATE_SEL     LAN80XX_ENCODE_BITMASK(13,3)
#define  LAN80XX_X_HOST_PMA_SD_LANE_CFG_3_RXRATE_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,13,3)


/**
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_STAT_0
 */
#define LAN80XX_HOST_PMA_SD_LANE_STAT_0         LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8006)

/**
 * \brief
 * PMA Reset done. Asserted when reset is completed following MACRO_RST
 * deassertion.
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_STAT_0 . PMA_RST_DONE
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_STAT_0_PMA_RST_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_STAT_0_PMA_RST_DONE  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_LANE_STAT_0_PMA_RST_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Lane Reset done. Asserted when reset is completed following LANE_RST
 * deassertion
 *
 * \details
 * 1:  Reset done
 * 0:  Reset pending or in progress
 *
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_STAT_0 . LANE_RST_DONE
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_STAT_0_LANE_RST_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_SD_LANE_STAT_0_LANE_RST_DONE  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_SD_LANE_STAT_0_LANE_RST_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief SD Lane Status
 *
 * \details
 * SD Lane Status as not available from internal SD register
 *
 * Register: \a HOST_PMA:SD_LANE_CFG_STAT:SD_LANE_STAT_1
 */
#define LAN80XX_HOST_PMA_SD_LANE_STAT_1         LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8007)

/**
 * \brief
 * Access to internal serdes state
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_LANE_STAT_1 . DBG_OBS
 */
#define  LAN80XX_F_HOST_PMA_SD_LANE_STAT_1_DBG_OBS(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_SD_LANE_STAT_1_DBG_OBS     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_SD_LANE_STAT_1_DBG_OBS(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PMA:SD_CFG
 *
 * SD Signal Detect Configuration
 */


/**
 * \brief SD Signal Detect Configuration
 *
 * \details
 * Serdes Signal Detect Configuration
 *
 * Register: \a HOST_PMA:SD_CFG:SD_CFG
 */
#define LAN80XX_HOST_PMA_SD_CFG                 LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8008)

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
 * Field: ::LAN80XX_HOST_PMA_SD_CFG . SD_ENA
 */
#define  LAN80XX_F_HOST_PMA_SD_CFG_SD_ENA(x)     LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_CFG_SD_ENA        LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_CFG_SD_ENA(x)     LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Signal detect polarity: The signal level on signal_detect input pin must
 * be equal to SD_POL to indicate signal detection (SD_ENA must be set)
 *
 * \details
 * 0: Signal Detect input pin must be '0' to indicate a signal detection
 * 1: Signal Detect input pin must be '1' to indicate a signal detection
 *
 * Field: ::LAN80XX_HOST_PMA_SD_CFG . SD_POL
 */
#define  LAN80XX_F_HOST_PMA_SD_CFG_SD_POL(x)     LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_SD_CFG_SD_POL        LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_SD_CFG_SD_POL(x)     LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Signal detect selection (select input for internal signal_detect line)
 *
 * \details
 * 0: Select signal_detect line from hardmacro
 * 1: Select external signal_detect line
 *
 * Field: ::LAN80XX_HOST_PMA_SD_CFG . SD_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_CFG_SD_SEL(x)     LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_PMA_SD_CFG_SD_SEL        LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_PMA_SD_CFG_SD_SEL(x)     LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 *  50 ohm Termination of REFCKP/N control from pin
 *
 * \details
 * 0: Choose the SerDes IP register for Termination control
 * 1: Host 0 and Host 3 terminations controlled by CLKTERMH0 and CLKTERMH3.
 * Host 1 and Host 2 terminations disabled
 *
 * Field: ::LAN80XX_HOST_PMA_SD_CFG . HWT_REFCLK_R_SEL
 */
#define  LAN80XX_F_HOST_PMA_SD_CFG_HWT_REFCLK_R_SEL(x)  LAN80XX_ENCODE_BITFIELD(!!(x),5,1)
#define  LAN80XX_M_HOST_PMA_SD_CFG_HWT_REFCLK_R_SEL  LAN80XX_BIT(5)
#define  LAN80XX_X_HOST_PMA_SD_CFG_HWT_REFCLK_R_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,5,1)

/**
 * Register Group: \a HOST_PMA:SD_CLK_GATE
 *
 * Gating all macro generated clocks
 */


/**
 * \brief Gating all macro generated clocks
 *
 * \details
 * Gate SD generated clocks during speed change
 *
 * Register: \a HOST_PMA:SD_CLK_GATE:SD_CLK_GATE
 */
#define LAN80XX_HOST_PMA_SD_CLK_GATE            LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x8009)

/**
 * \details
 * 0 :  enable macro clock generation towards core (RX & TX)
 * 1 :  disable (gate) macro clock generation towards core (TX & TX)
 *
 * Field: ::LAN80XX_HOST_PMA_SD_CLK_GATE . SD_CLK_GATE
 */
#define  LAN80XX_F_HOST_PMA_SD_CLK_GATE_SD_CLK_GATE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_SD_CLK_GATE_SD_CLK_GATE     LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_SD_CLK_GATE_SD_CLK_GATE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a HOST_PMA:SD_PWR_CFG
 *
 * SD Power configuration
 */


/**
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a HOST_PMA:SD_PWR_CFG:NORMAL_MODE_0
 */
#define LAN80XX_HOST_PMA_NORMAL_MODE_0          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x800a)

/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_HOST_PMA_NORMAL_MODE_0 . NORMAL_MODE_0
 */
#define  LAN80XX_F_HOST_PMA_NORMAL_MODE_0_NORMAL_MODE_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_NORMAL_MODE_0_NORMAL_MODE_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_NORMAL_MODE_0_NORMAL_MODE_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Power settings for NORMAL mode.
 *
 * \details
 * Register: \a HOST_PMA:SD_PWR_CFG:NORMAL_MODE_1
 */
#define LAN80XX_HOST_PMA_NORMAL_MODE_1          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x800b)

/**
 * \brief
 * Power Down Control settings for SD Lane in NORMAL mode
 * Bits 17 to 19 are for TX direction, other bits are for RX direction.
 * The default value is power-down mode, to ensure low power usage after
 * reset. Needs to be configured to a power-up mode as part of serdes
 * configuration.
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_HOST_PMA_NORMAL_MODE_1 . NORMAL_MODE_1
 */
#define  LAN80XX_F_HOST_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_HOST_PMA_NORMAL_MODE_1_NORMAL_MODE_1     LAN80XX_ENCODE_BITMASK(0,9)
#define  LAN80XX_X_HOST_PMA_NORMAL_MODE_1_NORMAL_MODE_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief
 * Power Control Select. Use to switch SerDes power mode state.
 * SerDes comes up in a low power state after reset from the default value
 *
 * \details
 * 0: Select SD lane low power setting from register LOWPWR_MODE_0 and LOWPWR_MODE_1.
 * 1: Select SD lane normal power setting from register NORMAL_MODE_0 and NORMAL_MODE_1.
 *
 * Field: ::LAN80XX_HOST_PMA_NORMAL_MODE_1 . PWR_CTRL_SEL
 */
#define  LAN80XX_F_HOST_PMA_NORMAL_MODE_1_PWR_CTRL_SEL(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_HOST_PMA_NORMAL_MODE_1_PWR_CTRL_SEL     LAN80XX_BIT(15)
#define  LAN80XX_X_HOST_PMA_NORMAL_MODE_1_PWR_CTRL_SEL(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * \brief Power settings for Low Power mode.
 *
 * \details
 * Register: \a HOST_PMA:SD_PWR_CFG:LOWPWR_MODE_0
 */
#define LAN80XX_HOST_PMA_LOWPWR_MODE_0          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x800c)

/**
 * \brief
 * Power Down Control settings for SD Lane in Low Power Mode
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_HOST_PMA_LOWPWR_MODE_0 . LOWPWR_MODE_0
 */
#define  LAN80XX_F_HOST_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_LOWPWR_MODE_0_LOWPWR_MODE_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * \brief Power settings for Low Power mode.
 *
 * \details
 * Register: \a HOST_PMA:SD_PWR_CFG:LOWPWR_MODE_1
 */
#define LAN80XX_HOST_PMA_LOWPWR_MODE_1          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0, 0x800d)

/**
 * \brief
 * Power Down Control settings for SD Lane in Low Power Mode
 *
 * \details
 * Refer to GUC documentation
 *
 * Field: ::LAN80XX_HOST_PMA_LOWPWR_MODE_1 . LOWPWR_MODE_1
 */
#define  LAN80XX_F_HOST_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,9)
#define  LAN80XX_M_HOST_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1     LAN80XX_ENCODE_BITMASK(0,9)
#define  LAN80XX_X_HOST_PMA_LOWPWR_MODE_1_LOWPWR_MODE_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,9)

/**
 * Register Group: \a HOST_PMA:SD_ANEG_CFG
 *
 * PCS and ANEG data selection control for TX
 */


/**
 * \brief SD_KR_ANEG_MODE
 *
 * \details
 * Configure ANEG to SerDes (TX) behavior
 *
 * Register: \a HOST_PMA:SD_ANEG_CFG:SD_KR_ANEG_MODE
 */
#define LAN80XX_HOST_PMA_SD_KR_ANEG_MODE        LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8010)

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
 * Field: ::LAN80XX_HOST_PMA_SD_KR_ANEG_MODE . TX_ANEG_MODE
 */
#define  LAN80XX_F_HOST_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  LAN80XX_ENCODE_BITFIELD(x,0,2)
#define  LAN80XX_M_HOST_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE     LAN80XX_ENCODE_BITMASK(0,2)
#define  LAN80XX_X_HOST_PMA_SD_KR_ANEG_MODE_TX_ANEG_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a HOST_PMA:SD_EXTCFG_CFG
 *
 * Configuration of SD local parallel configuration interface (EXT_CFG)
 */


/**
 * \brief Configuration of SD local parallel configuration interface (EXT_CFG)
 *
 * \details
 * Register: \a HOST_PMA:SD_EXTCFG_CFG:SD_EXTCFG_CFG
 */
#define LAN80XX_HOST_PMA_SD_EXTCFG_CFG          LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8011)

/**
 * \brief
 * Clock divider for EXTCFG Master.
 * Divide the system clock by N + 2 to be used as EXTCFG master clock for
 * SerDes configuration.
 *
 * \details
 * N: core clock (system clock) is divided by N+2.
 *
 * Field: ::LAN80XX_HOST_PMA_SD_EXTCFG_CFG . CLK_DIV
 */
#define  LAN80XX_F_HOST_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_HOST_PMA_SD_EXTCFG_CFG_CLK_DIV     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_HOST_PMA_SD_EXTCFG_CFG_CLK_DIV(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)

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
 * Field: ::LAN80XX_HOST_PMA_SD_EXTCFG_CFG . WS_SETUP_WR
 */
#define  LAN80XX_F_HOST_PMA_SD_EXTCFG_CFG_WS_SETUP_WR(x)  LAN80XX_ENCODE_BITFIELD(x,4,2)
#define  LAN80XX_M_HOST_PMA_SD_EXTCFG_CFG_WS_SETUP_WR     LAN80XX_ENCODE_BITMASK(4,2)
#define  LAN80XX_X_HOST_PMA_SD_EXTCFG_CFG_WS_SETUP_WR(x)  LAN80XX_EXTRACT_BITFIELD(x,4,2)

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
 * Field: ::LAN80XX_HOST_PMA_SD_EXTCFG_CFG . WS_EXEC_WR
 */
#define  LAN80XX_F_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_WR(x)  LAN80XX_ENCODE_BITFIELD(x,8,2)
#define  LAN80XX_M_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_WR     LAN80XX_ENCODE_BITMASK(8,2)
#define  LAN80XX_X_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_WR(x)  LAN80XX_EXTRACT_BITFIELD(x,8,2)

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
 * Field: ::LAN80XX_HOST_PMA_SD_EXTCFG_CFG . WS_HOLD_WR
 */
#define  LAN80XX_F_HOST_PMA_SD_EXTCFG_CFG_WS_HOLD_WR(x)  LAN80XX_ENCODE_BITFIELD(x,12,2)
#define  LAN80XX_M_HOST_PMA_SD_EXTCFG_CFG_WS_HOLD_WR     LAN80XX_ENCODE_BITMASK(12,2)
#define  LAN80XX_X_HOST_PMA_SD_EXTCFG_CFG_WS_HOLD_WR(x)  LAN80XX_EXTRACT_BITFIELD(x,12,2)

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
 * Field: ::LAN80XX_HOST_PMA_SD_EXTCFG_CFG . WS_EXEC_RD
 */
#define  LAN80XX_F_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_RD(x)  LAN80XX_ENCODE_BITFIELD(x,14,2)
#define  LAN80XX_M_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_RD     LAN80XX_ENCODE_BITMASK(14,2)
#define  LAN80XX_X_HOST_PMA_SD_EXTCFG_CFG_WS_EXEC_RD(x)  LAN80XX_EXTRACT_BITFIELD(x,14,2)

/**
 * Register Group: \a HOST_PMA:SD_FIFO_DELAY
 *
 * Registers for precise FIFO delay measurement
 */


/**
 * \brief FIFO delay measurement configuration
 *
 * \details
 * FIFO delay measurement configuration register
 *
 * Register: \a HOST_PMA:SD_FIFO_DELAY:SD_DELAY_CFG
 */
#define LAN80XX_HOST_PMA_SD_DELAY_CFG           LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8012)

/**
 * \brief
 * Configures the number of cycles the skew detector should run before
 * returning serdes delay
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_DELAY_CFG . SAMPLE_TIME
 */
#define  LAN80XX_F_HOST_PMA_SD_DELAY_CFG_SAMPLE_TIME(x)  LAN80XX_ENCODE_BITFIELD(x,0,3)
#define  LAN80XX_M_HOST_PMA_SD_DELAY_CFG_SAMPLE_TIME     LAN80XX_ENCODE_BITMASK(0,3)
#define  LAN80XX_X_HOST_PMA_SD_DELAY_CFG_SAMPLE_TIME(x)  LAN80XX_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a HOST_PMA:SD_FIFO_DELAY:SD_RX_DELAY_VAR
 */
#define LAN80XX_HOST_PMA_SD_RX_DELAY_VAR        LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8013)

/**
 * \brief
 * Link-up dynamic delay to be added to the PTP RX I/O link delay
 * configuration. Value is the fraction of 65536 of the maximum delay at a
 * given speed and lane index.1.0 Gbps: 128 ns10.0 Gbps: 24.8 ns25.0 Gbps:
 * 6.2 ns
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_RX_DELAY_VAR . RX_DELAY_VAR
 */
#define  LAN80XX_F_HOST_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_SD_RX_DELAY_VAR_RX_DELAY_VAR(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief FIFO delay measurement
 *
 * \details
 * FIFO delay measurement register
 *
 * Register: \a HOST_PMA:SD_FIFO_DELAY:SD_TX_DELAY_VAR
 */
#define LAN80XX_HOST_PMA_SD_TX_DELAY_VAR        LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8014)

/**
 * \brief
 * Link-up dynamic delay to be added to the PTP TX I/O link delay
 * configuration. Value is the fraction of 65536 of the maximum delay at a
 * given speed and lane index.1.0 Gbps: 128 ns10.0 Gbps: 18.6 ns25.0 Gbps:
 * 6.2 ns
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_SD_TX_DELAY_VAR . TX_DELAY_VAR
 */
#define  LAN80XX_F_HOST_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_SD_TX_DELAY_VAR_TX_DELAY_VAR(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a HOST_PMA:HW_CFG
 *
 * Hardware Configuration
 */


/**
 * \brief KR ANEG Configuration
 *
 * \details
 * Common KR ANEG configuration, used across all instances.
 *
 * Register: \a HOST_PMA:HW_CFG:KR_DATA_CFG
 */
#define LAN80XX_HOST_PMA_KR_DATA_CFG            LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8016)

/**
 * \brief
 * Revert 10B data bus portion.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::LAN80XX_HOST_PMA_KR_DATA_CFG . REVERT_10B
 */
#define  LAN80XX_F_HOST_PMA_KR_DATA_CFG_REVERT_10B(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_KR_DATA_CFG_REVERT_10B  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_KR_DATA_CFG_REVERT_10B(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::LAN80XX_HOST_PMA_KR_DATA_CFG . REVERT_64B_TX
 */
#define  LAN80XX_F_HOST_PMA_KR_DATA_CFG_REVERT_64B_TX(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_KR_DATA_CFG_REVERT_64B_TX  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_KR_DATA_CFG_REVERT_64B_TX(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Revert 64B data bus portion for transmit direction.
 *
 * \details
 * 1 : Revert bit order
 * 0 : Default bit order
 *
 * Field: ::LAN80XX_HOST_PMA_KR_DATA_CFG . REVERT_64B_RX
 */
#define  LAN80XX_F_HOST_PMA_KR_DATA_CFG_REVERT_64B_RX(x)  LAN80XX_ENCODE_BITFIELD(!!(x),2,1)
#define  LAN80XX_M_HOST_PMA_KR_DATA_CFG_REVERT_64B_RX  LAN80XX_BIT(2)
#define  LAN80XX_X_HOST_PMA_KR_DATA_CFG_REVERT_64B_RX(x)  LAN80XX_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * The bus width selection of KR with Serdes interface.
 *
 * \details
 * 1 : Configure the data bus width to 64 bits.
 * 0 : Configure the data bus width to 40 bits, this is default
 *
 * Field: ::LAN80XX_HOST_PMA_KR_DATA_CFG . KR_DATA_BUS_MODE
 */
#define  LAN80XX_F_HOST_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),3,1)
#define  LAN80XX_M_HOST_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE  LAN80XX_BIT(3)
#define  LAN80XX_X_HOST_PMA_KR_DATA_CFG_KR_DATA_BUS_MODE(x)  LAN80XX_EXTRACT_BITFIELD(x,3,1)

/**
 * Register Group: \a HOST_PMA:PMA_INT
 *
 * PMA_INT
 */


/**
 * \brief PMA interrupt register. All sticky
 *
 * \details
 * Register: \a HOST_PMA:PMA_INT:PMA_IRQ_VEC
 */
#define LAN80XX_HOST_PMA_PMA_IRQ_VEC            LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8018)

/**
 * \brief
 * pma rx electrical idle signal interrupt, write one to clear
 *
 * \details
 * 0 = pma doesn't detect RX electrical idle
 * 1 = pma detects RX electrical idle
 *
 * Field: ::LAN80XX_HOST_PMA_PMA_IRQ_VEC . PMA_RXEI_FILTERED_INT
 */
#define  LAN80XX_F_HOST_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_PMA_IRQ_VEC_PMA_RXEI_FILTERED_INT(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * pma reset done interrupt, write one to clear
 *
 * \details
 * 0 = pma reset sequence is not complete
 * 1 = pma accomplished the global reset
 *
 * Field: ::LAN80XX_HOST_PMA_PMA_IRQ_VEC . PMA_RESET_DONE
 */
#define  LAN80XX_F_HOST_PMA_PMA_IRQ_VEC_PMA_RESET_DONE(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_PMA_IRQ_VEC_PMA_RESET_DONE  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_PMA_IRQ_VEC_PMA_RESET_DONE(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)


/**
 * \brief interrupt mask
 *
 * \details
 * Register: \a HOST_PMA:PMA_INT:PMA_IRQ_MASK
 */
#define LAN80XX_HOST_PMA_PMA_IRQ_MASK           LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x8019)

/**
 * \brief
 * Interrupt enable for pma rx signal idle
 *
 * \details
 * 0 = pma_rxei_filtered_int will not propagate to interrupt
 * 1 = pma_rxei_filtered_int will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PMA_PMA_IRQ_MASK . PMA_RXEI_FILTERED_INT_EN
 */
#define  LAN80XX_F_HOST_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),0,1)
#define  LAN80XX_M_HOST_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN  LAN80XX_BIT(0)
#define  LAN80XX_X_HOST_PMA_PMA_IRQ_MASK_PMA_RXEI_FILTERED_INT_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Interrupt enable for pma reset done
 *
 * \details
 * 0 = pma_reset_done will not propagate to interrupt
 * 1 = pma_reset_done will propagate to interrupt
 *
 * Field: ::LAN80XX_HOST_PMA_PMA_IRQ_MASK . PMA_RESET_DONE_INT_EN
 */
#define  LAN80XX_F_HOST_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN(x)  LAN80XX_ENCODE_BITFIELD(!!(x),1,1)
#define  LAN80XX_M_HOST_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN  LAN80XX_BIT(1)
#define  LAN80XX_X_HOST_PMA_PMA_IRQ_MASK_PMA_RESET_DONE_INT_EN(x)  LAN80XX_EXTRACT_BITFIELD(x,1,1)

/**
 * Register Group: \a HOST_PMA:HOST_PMA_DEBUG
 *
 * HOST_PMA debug registers
 */


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 7
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_7
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_7   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80f8)

/**
 * \brief
 * HOST_PMA debug register 7
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_7 . HOST_PMA_DBG_REG_7
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_7_HOST_PMA_DBG_REG_7(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_7_HOST_PMA_DBG_REG_7     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_7_HOST_PMA_DBG_REG_7(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 6
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_6
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_6   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80f9)

/**
 * \brief
 * HOST_PMA debug register 6
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_6 . HOST_PMA_DBG_REG_6
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_6_HOST_PMA_DBG_REG_6(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_6_HOST_PMA_DBG_REG_6     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_6_HOST_PMA_DBG_REG_6(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 5
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_5
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_5   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80fa)

/**
 * \brief
 * HOST_PMA debug register 5
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_5 . HOST_PMA_DBG_REG_5
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_5_HOST_PMA_DBG_REG_5(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_5_HOST_PMA_DBG_REG_5     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_5_HOST_PMA_DBG_REG_5(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 4
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_4
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_4   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80fb)

/**
 * \brief
 * HOST_PMA debug register 4
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_4 . HOST_PMA_DBG_REG_4
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_4_HOST_PMA_DBG_REG_4(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_4_HOST_PMA_DBG_REG_4     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_4_HOST_PMA_DBG_REG_4(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 3
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_3
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_3   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80fc)

/**
 * \brief
 * HOST_PMA debug register 3
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_3 . HOST_PMA_DBG_REG_3
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_3_HOST_PMA_DBG_REG_3(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_3_HOST_PMA_DBG_REG_3     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_3_HOST_PMA_DBG_REG_3(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 2
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_2
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_2   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80fd)

/**
 * \brief
 * HOST_PMA debug register 2
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_2 . HOST_PMA_DBG_REG_2
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_2_HOST_PMA_DBG_REG_2(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_2_HOST_PMA_DBG_REG_2     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_2_HOST_PMA_DBG_REG_2(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 1
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_1
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_1   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80fe)

/**
 * \brief
 * HOST_PMA debug register 1
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_1 . HOST_PMA_DBG_REG_1
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_1_HOST_PMA_DBG_REG_1(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_1_HOST_PMA_DBG_REG_1     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_1_HOST_PMA_DBG_REG_1(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Debug registers
 *
 * \details
 * HOST_PMA debug register 0
 *
 * Register: \a HOST_PMA:HOST_PMA_DEBUG:HOST_PMA_DEBUG_REG_0
 */
#define LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_0   LAN80XX_IOREG(MMD_ID_HOST_PMA, 0,0x80ff)

/**
 * \brief
 * HOST_PMA debug register 0
 *
 * \details
 * Field: ::LAN80XX_HOST_PMA_HOST_PMA_DEBUG_REG_0 . HOST_PMA_DBG_REG_0
 */
#define  LAN80XX_F_HOST_PMA_HOST_PMA_DEBUG_REG_0_HOST_PMA_DBG_REG_0(x)  LAN80XX_ENCODE_BITFIELD(x,0,16)
#define  LAN80XX_M_HOST_PMA_HOST_PMA_DEBUG_REG_0_HOST_PMA_DBG_REG_0     LAN80XX_ENCODE_BITMASK(0,16)
#define  LAN80XX_X_HOST_PMA_HOST_PMA_DEBUG_REG_0_HOST_PMA_DBG_REG_0(x)  LAN80XX_EXTRACT_BITFIELD(x,0,16)


#endif /* _LAN80XX_MALIBU25G_REGS_HOST_PMA_H_ */
