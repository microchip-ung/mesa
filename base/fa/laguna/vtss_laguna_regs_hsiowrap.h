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
 * Register Group: \a HSIOWRAP:GPIO_CFG
 *
 * Registers for accessing the GPIO pad cell configuration
 */


/**
 * \brief GPIO pad cell configuration
 *
 * \details
 * Register: \a HSIOWRAP:GPIO_CFG:GPIO_CFG
 *
 * @param ri Register: GPIO_CFG (??), 0-24
 */
#define VTSS_HSIOWRAP_GPIO_CFG(ri)           VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x0 + (ri))

/**
 * \brief
 * Bus hold enable
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . HE
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_HE(x)       VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_HE          VTSS_BIT(7)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_HE(x)       VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Schmitt-trigger
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . ST
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_ST(x)       VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_ST          VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_ST(x)       VTSS_EXTRACT_BITFIELD(x,5,2)

/**
 * \brief
 * Slew rate limit enable
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . SL
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_SL(x)       VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_SL          VTSS_BIT(4)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_SL(x)       VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable pull up resistor on GPIO inputs. Should not be set to '1' when
 * G_PD is '1'
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . PU
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_PU(x)       VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_PU          VTSS_BIT(3)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_PU(x)       VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable pull down resistor on GPIO inputs. Should not be set to '1' when
 * G_PU is '1'
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . PD
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_PD(x)       VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_PD          VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_PD(x)       VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Controls the drive strength of GPIO outputs
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_GPIO_CFG . DS
 */
#define  VTSS_F_HSIOWRAP_GPIO_CFG_DS(x)       VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HSIOWRAP_GPIO_CFG_DS          VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HSIOWRAP_GPIO_CFG_DS(x)       VTSS_EXTRACT_BITFIELD(x,0,2)

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
#define VTSS_HSIOWRAP_SYNC_ETH_CFG(ri)       VTSS_IOREG(VTSS_TO_HSIO_WRAP,0x19 + (ri))

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
 * @param gi Register: XMII_CFG (??), 0-1
 */
#define VTSS_HSIOWRAP_XMII_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_HSIO_WRAP,0x1d,gi,5,0,0)

/**
 * \details
 * 0: GPIO
 * 1: RGMII
 * 2: RMII
 * 3: reserved
 *
 * Field: ::VTSS_HSIOWRAP_XMII_CFG . GPIO_XMII_CFG
 */
#define  VTSS_F_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_HSIOWRAP_XMII_CFG_GPIO_XMII_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Enable the MAC-MERGE Layer Receive block.
 *
 * \details
 * Must reflect the value of
 * DEVRGMII[0-1]:MM_CONFIG:ENABLE_CONFIG.MM_RX_ENA
 *
 * Field: ::VTSS_HSIOWRAP_XMII_CFG . MM_RX_ENA
 */
#define  VTSS_F_HSIOWRAP_XMII_CFG_MM_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_XMII_CFG_MM_RX_ENA   VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_XMII_CFG_MM_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of RGMII mode
 *
 * \details
 * Register: \a HSIOWRAP:XMII_CFG:RGMII_CFG
 *
 * @param gi Register: XMII_CFG (??), 0-1
 */
#define VTSS_HSIOWRAP_RGMII_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_HSIO_WRAP,0x1d,gi,5,0,1)

/**
 * \brief
 * Link status received inband
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_RX_LINK_STATUS
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_RX_LINK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_RX_LINK_STATUS  VTSS_BIT(15)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_RX_LINK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Duplex status received inband
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_RX_DUPLEX
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_RX_DUPLEX(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_RX_DUPLEX  VTSS_BIT(14)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_RX_DUPLEX(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Speed status received inband
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_RX_SPEED
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_RX_SPEED(x)  VTSS_ENCODE_BITFIELD(x,12,2)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_RX_SPEED     VTSS_ENCODE_BITMASK(12,2)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_RX_SPEED(x)  VTSS_EXTRACT_BITFIELD(x,12,2)

/**
 * \brief
 * Llink status to signal  inband
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_TX_LINK_STATUS
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_TX_LINK_STATUS(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_TX_LINK_STATUS  VTSS_BIT(11)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_TX_LINK_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * FDX mode to signal inband
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_TX_FDX
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_TX_FDX(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_TX_FDX  VTSS_BIT(10)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_TX_FDX(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * MII speed to signal inband
 *
 * \details
 * 0: 100M
 * 1: 10M
 *
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_TX_MII_SPD
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_TX_MII_SPD(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_TX_MII_SPD  VTSS_BIT(9)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_TX_MII_SPD(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Signal inband that the transmission speed is 1G
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_TX_SPD_1G
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_TX_SPD_1G(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_TX_SPD_1G  VTSS_BIT(8)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_TX_SPD_1G(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable transmission of inband RGMII status
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_TX_ENA
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_TX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_TX_ENA  VTSS_BIT(7)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_TX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable reception of inband RGMII data
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_RX_ENA
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_RX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_RX_ENA  VTSS_BIT(6)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_RX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable transmitting and reception of inband RGMII information. Must be
 * set to enable inband functionality
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . IB_ENA
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_IB_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_IB_ENA     VTSS_BIT(5)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_IB_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Configure TX clock frequency
 *
 * \details
 * 0: Disable TX clock generation
 * 1: 125MHz for 1000Mbps operation
 * 2: 25MHz for 100Mbps operation
 * 3: 2.5MHz for 10Mbps operation
 * 4-7: Reserved
 *
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . TX_CLK_CFG
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_TX_CLK_CFG(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_TX_CLK_CFG     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_TX_CLK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Reset RGMII Tx clock domains
 *
 * \details
 * 0: The RGMII Tx clock domain is not reset
 * 1: The RGMII Tx clock domain is reset.
 *
 * Note: The RGMII Tx clock domain remains reset until 0 is written to this
 * register field.
 *
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . RGMII_TX_RST
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_RGMII_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_RGMII_TX_RST  VTSS_BIT(1)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_RGMII_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset RGMII Rx clock domains
 *
 * \details
 * 0: The RGMII Rx clock domain is not reset
 * 1: The RGMII Rx clock domain is reset.
 *
 * Note: The RGMII Rx clock domain remains reset until 0 is written to this
 * register field.
 *
 * Field: ::VTSS_HSIOWRAP_RGMII_CFG . RGMII_RX_RST
 */
#define  VTSS_F_HSIOWRAP_RGMII_CFG_RGMII_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_RGMII_CFG_RGMII_RX_RST  VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_RGMII_CFG_RGMII_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of RMII mode
 *
 * \details
 * Used when the port is in RMII mode
 *
 * Register: \a HSIOWRAP:XMII_CFG:RMII_CFG
 *
 * @param gi Register: XMII_CFG (??), 0-1
 */
#define VTSS_HSIOWRAP_RMII_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_HSIO_WRAP,0x1d,gi,5,0,2)

/**
 * \details
 * 0: Use internally generated 50MHz RMII reference clock.
 * 1: Use GPIO46 or GPIO58 pin as external RMII reference clock
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_REF_CLK_SEL
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_REF_CLK_SEL(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_REF_CLK_SEL  VTSS_BIT(6)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_REF_CLK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Select clock edge to use when driving RMII TXD and TX_EN outputs
 *
 * \details
 * 0: Use positive edge
 * 1: Use negative edge
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_CFG_TX_EDGE
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_CFG_TX_EDGE(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_CFG_TX_EDGE  VTSS_BIT(5)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_CFG_TX_EDGE(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Configure duplex mode of the RMII interface
 *
 * \details
 * 0: HDX
 * 1: FDX
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_FDX_CFG
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_FDX_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_FDX_CFG  VTSS_BIT(4)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_FDX_CFG(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Configure speed of RMII interface
 *
 * \details
 * 0: 10M
 * 1: 100M
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_SPEED_CFG
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_SPEED_CFG(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_SPEED_CFG  VTSS_BIT(3)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_SPEED_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Reset RMII Tx clock domains
 *
 * \details
 * 0: The RMII Tx clock domain is not reset.
 * 1: The RMII Tx clock domain is reset.
 *
 * Note: The RMII Tx clock domain remains reset until 0 is written to this
 * register field.
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_TX_RST
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_TX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_TX_RST  VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_TX_RST(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Reset RMII Rx clock domains
 *
 * \details
 * 0: The RMII Rx clock domain is not reset
 * 1: The RMII Rx clock domain is reset.
 *
 * Note: The RMII Rx clock domain remains reset until 0 is written to this
 * register field.
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_RX_RST
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_RX_RST(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_RX_RST  VTSS_BIT(1)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_RX_RST(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable RMII mode.
 *
 * \details
 * 0: RGMII mode
 * 1: RMII mode
 *
 * Field: ::VTSS_HSIOWRAP_RMII_CFG . RMII_ENA
 */
#define  VTSS_F_HSIOWRAP_RMII_CFG_RMII_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_RMII_CFG_RMII_ENA    VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_RMII_CFG_RMII_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of RGMII delay lines
 *
 * \details
 * RGMII delay line configuration.
 *
 * There are two RGMII delay lines. The replication is as follows:
 *
 * 0: RGMII_RXC (RX clock)
 * 1: RGMII_TXC (TX clock)

 *
 * Register: \a HSIOWRAP:XMII_CFG:DLL_CFG
 *
 * @param gi Register: XMII_CFG (??), 0-1
 * @param ri Register: DLL_CFG (??), 0-1
 */
#define VTSS_HSIOWRAP_DLL_CFG(gi,ri)         VTSS_IOREG_IX(VTSS_TO_HSIO_WRAP,0x1d,gi,5,ri,3)

/**
 * \brief
 * When enabled the DLL is used in RGMII clock paths. When '0' the DLL is
 * bypassed
 *
 * \details
 * 0: Bypass DLL
 * 1: Use DLL
 *
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . DLL_CLK_ENA
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_DLL_CLK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_HSIOWRAP_DLL_CFG_DLL_CLK_ENA  VTSS_BIT(17)
#define  VTSS_X_HSIOWRAP_DLL_CFG_DLL_CLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Default tap used to prevent glitches that might occur when delay is
 * first locked
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . TAP_SEL
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_TAP_SEL(x)   VTSS_ENCODE_BITFIELD(x,10,7)
#define  VTSS_M_HSIOWRAP_DLL_CFG_TAP_SEL      VTSS_ENCODE_BITMASK(10,7)
#define  VTSS_X_HSIOWRAP_DLL_CFG_TAP_SEL(x)   VTSS_EXTRACT_BITFIELD(x,10,7)

/**
 * \brief
 * Default value used to adjust the tuned tap to compensate output mux
 * delay
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . TAP_ADJ
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_TAP_ADJ(x)   VTSS_ENCODE_BITFIELD(x,3,7)
#define  VTSS_M_HSIOWRAP_DLL_CFG_TAP_ADJ      VTSS_ENCODE_BITMASK(3,7)
#define  VTSS_X_HSIOWRAP_DLL_CFG_TAP_ADJ(x)   VTSS_EXTRACT_BITFIELD(x,3,7)

/**
 * \brief
 * Enable or disable delay line in signal path
 *
 * \details
 * 1: clk_2ns_delay -> clk_source_out
 * 0: clk_source_in -> clk_source_out

 *
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . DELAY_ENA
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_DELAY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_HSIOWRAP_DLL_CFG_DELAY_ENA    VTSS_BIT(2)
#define  VTSS_X_HSIOWRAP_DLL_CFG_DELAY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable delay by starting the delay tune FSM
 *
 * \details
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . DLL_ENA
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_DLL_ENA(x)   VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_HSIOWRAP_DLL_CFG_DLL_ENA      VTSS_BIT(1)
#define  VTSS_X_HSIOWRAP_DLL_CFG_DLL_ENA(x)   VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Reset the DLL. Active high
 *
 * \details
 * 0: The DLL can be used
 * 1: Reset
 *
 * Field: ::VTSS_HSIOWRAP_DLL_CFG . DLL_RST
 */
#define  VTSS_F_HSIOWRAP_DLL_CFG_DLL_RST(x)   VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_HSIOWRAP_DLL_CFG_DLL_RST      VTSS_BIT(0)
#define  VTSS_X_HSIOWRAP_DLL_CFG_DLL_RST(x)   VTSS_EXTRACT_BITFIELD(x,0,1)


#endif /* _VTSS_LAGUNA_REGS_HSIOWRAP_H_ */
