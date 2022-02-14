// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_HSIOWRAP_H_
#define _VTSS_LAGUNA_REGS_HSIOWRAP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a HSIOWRAP
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a HSIOWRAP:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/**
 * \brief Recovered Clock Configuration
 *
 * \details
 * This register is replicated once per recovered clock destination.
 * Replications 0-3 are GPIO mapped recovered clocks 0 though 3.
 * Replications 4-7 are SD10G mapped recovered clocks.
 *
 * Register: \a HSIOWRAP:SYNC_ETH_CFG:SYNC_ETH_CFG
 *
 * @param ri Register: SYNC_ETH_CFG (??), 0-3
 */
#define VTSS_HSIOWRAP_SYNC_ETH_CFG(ri)       VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x0 + (ri))

/**
 * \brief
 * Select recovered clock source.
 *
 * \details
 * 0-16: Select SD6G 0 through 16 recovered RX data clock
 * 17-32: Select SD10G 0 through 15 recovered RX data lock
 * 33: Select AUX1 clock from LCPLL1 reference
 * 34: Select AUX2 clock from LCPLL1 reference
 * 35: Select AUX3 clock from LCPLL1 reference
 * 36: Select AUX4 clock from LCPLL1 reference
 * Other values are reserved.
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . SEL_RECO_CLK_SRC
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_SRC(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Select recovered clock divider.
 *
 * \details
 * 0: Divide clock by 2
 * 1: Divide clock by 4
 * 2: Divide clock by 8
 * 3: Divide clock by 16
 * 4: Divide clock by 5
 * 5: Divide clock by 25
 * 6: No clock dividing
 * 7: Reserved
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . SEL_RECO_CLK_DIV
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_SEL_RECO_CLK_DIV(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * Set to enable recovered clock generation. Bit is also used to enable
 * corresponding GPIO pad.
 *
 * \details
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: ::VTSS_HSIOWRAP_SYNC_ETH_CFG . RECO_CLK_ENA
 */
#define  VTSS_F_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA  VTSS_BIT(12)
#define  VTSS_X_HSIOWRAP_SYNC_ETH_CFG_RECO_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * Register Group: \a HSIOWRAP:XMII_CFG
 *
 * RGMII and RMII configuration
 */


/**
 * \brief RGMII and RMII configuration
 *
 * \details
 * Register: \a HSIOWRAP:XMII_CFG:XMII_CFG
 *
 * @param ri Register: XMII_CFG (??), 0-1
 */
#define VTSS_HSIOWRAP_XMII_CFG(ri)           VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x4 + (ri))

/**
 * \details
 * 0: GPIO
 * 1: RGMII
 * 2: RMII
 * 3: reserved
 *
 * Field: ::VTSS_HSIOWRAP_XMII_CFG . GPIO_XMII_CFG
 */
#define  VTSS_F_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_HSIOWRAP_H_ */
