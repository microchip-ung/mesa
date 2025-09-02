// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_LINE_SLICE_H_
#define LAN80XX_MALIBU25G_REGS_LINE_SLICE_H_

#include "regs_lan80xx_common.h"

/***********************************************************************
 *
 * Target: \a LINE_SLICE
 *
 *
 *
 ***********************************************************************/

/**
 * Register Group: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET
 *
 * Generate the Reset for the block in Slice
 */


/**
 * \brief Line SD25G SerDes Resets
 *
 * \details
 * Line SD25G SerDes Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_SD25G_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_SD25G_RESET                                                         (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8100))

/**
 * \brief
 * Reset external SD25G interface logic, restore the SD25G register value
 * back to defaults
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_SD25G_RESET . LINE_SD25G_BASECK_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_BASECK_RST(x)                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Software reset bit for the PCS25G, PCS1G and KR IP transmit/receive
 * functions. This bit does not reset any PMA/SerDes functions. This reset
 * signal is synchronized by the PMA_TX_CK and PMA_RX_CK respectively
 * before apply to the registers on the transmit data path and receive data
 * path
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_SD25G_RESET . LINE_SD25G_LANE_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_LANE_RST(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_LANE_RST                                  (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_LANE_RST(x)                               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * SD25G fundamental global software reset
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_SD25G_RESET . LINE_SD25G_MACRO_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST                                 (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_LINE_SD25G_RESET_LINE_SD25G_MACRO_RST(x)                              (LAN80XX_EXTRACT_BITFIELD(x,2,1))


/**
 * \brief Line KR IP Resets
 *
 * \details
 * Line KR IP Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_KR_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_KR_RESET                                                            (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8101))

/**
 * \brief
 * Reset KR ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_KR_RESET . LINE_KR_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_KR_RESET_LINE_KR_INGR_RST(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_KR_RESET_LINE_KR_INGR_RST                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_KR_RESET_LINE_KR_INGR_RST(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset KR egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_KR_RESET . LINE_KR_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_KR_RESET_LINE_KR_EGR_RST(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_KR_RESET_LINE_KR_EGR_RST                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_KR_RESET_LINE_KR_EGR_RST(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief Line PCS1G Resets
 *
 * \details
 * Line PCS1G Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_PCS1G_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_PCS1G_RESET                                                         (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8102))

/**
 * \brief
 * Reset PCS1G ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_PCS1G_RESET . LINE_PCS1G_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_INGR_RST(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_INGR_RST                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_INGR_RST(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset PCS1G egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_PCS1G_RESET . LINE_PCS1G_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_EGR_RST(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_EGR_RST                                   (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_PCS1G_RESET_LINE_PCS1G_EGR_RST(x)                                (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief Line PCS25G Resets
 *
 * \details
 * Line PCS25G Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_PCS25G_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_PCS25G_RESET                                                        (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8103))

/**
 * \brief
 * Reset PCS25G ingress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_PCS25G_RESET . LINE_PCS25G_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_INGR_RST(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_INGR_RST                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_INGR_RST(x)                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset PCS25G egress logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_PCS25G_RESET . LINE_PCS25G_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_EGR_RST(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_EGR_RST                                 (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_PCS25G_RESET_LINE_PCS25G_EGR_RST(x)                              (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief Line XC Port Reset
 *
 * \details
 * Line XC Port Reset
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_XC_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_XC_RESET                                                            (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8104))

/**
 * \brief
 * Reset all four XC FIFO Read Ports toward this Line Port (H2L direction)
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_XC_RESET . LINE_XC_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_XC_RESET_LINE_XC_EGR_RST(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_XC_RESET_LINE_XC_EGR_RST                                         (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_XC_RESET_LINE_XC_EGR_RST(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \details
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:MISC_BLOCKS_RESET
 */
#define LAN80XX_LINE_SLICE_MISC_BLOCKS_RESET                                                        (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8105))

/**
 * \brief
 * Reset TWI logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_MISC_BLOCKS_RESET . TWI_HOST_RST
 */
#define  LAN80XX_F_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_MISC_BLOCKS_RESET_TWI_HOST_RST(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))


/**
 * \brief MACSEC IP Resets
 *
 * \details
 * MACSEC IP Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_MACSEC_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_MACSEC_RESET                                                        (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8106))

/**
 * \brief
 * Reset MACSEC Line Part Ingress function except MACSEC IP
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_LPART_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_INGR_RST(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_INGR_RST                               (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_INGR_RST(x)                            (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset MACSEC Line Part egress function except MACSEC IP
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_LPART_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_EGR_RST(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_EGR_RST                                (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_EGR_RST(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Reset MACSEC Host Part ingress function
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_HPART_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_INGR_RST(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_INGR_RST                               (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_INGR_RST(x)                            (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Reset MACSEC Host Part egress function
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_HPART_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_EGR_RST(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_EGR_RST                                (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_EGR_RST(x)                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Reset MACSEC IP ingress direction logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_IP_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_INGR_RST(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_INGR_RST                                  (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_INGR_RST(x)                               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Reset MACSEC IP egress direction logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_MACSEC_RESET . MACSEC_IP_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_EGR_RST(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_EGR_RST                                   (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_EGR_RST(x)                                (LAN80XX_EXTRACT_BITFIELD(x,5,1))


/**
 * \brief IP1588 Resets
 *
 * \details
 * IP1588 Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_IP1588_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_IP1588_RESET                                                        (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8107))

/**
 * \brief
 * Reset IP1588 ingress direction logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_IP1588_RESET . IP1588_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_IP1588_RESET_IP1588_INGR_RST(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_IP1588_RESET_IP1588_INGR_RST                                     (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_IP1588_RESET_IP1588_INGR_RST(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset IP1588 egress direction logic
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_IP1588_RESET . IP1588_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_IP1588_RESET_IP1588_EGR_RST(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_IP1588_RESET_IP1588_EGR_RST                                      (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_IP1588_RESET_IP1588_EGR_RST(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,1,1))


/**
 * \brief Line RA Resets
 *
 * \details
 * Line RA Resets
 *
 * Register: \a LINE_SLICE:LINE_SLICE_BLOCK_SOFTWARE_RESET:LINE_FIFO_RESET
 */
#define LAN80XX_LINE_SLICE_LINE_FIFO_RESET                                                          (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8108))

/**
 * \brief
 * Reset L2H_RA_FIFO
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_FIFO_RESET . L2H_RA_FIFO_INGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_FIFO_RESET_L2H_RA_FIFO_INGR_RST(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LINE_FIFO_RESET_L2H_RA_FIFO_INGR_RST                                  (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LINE_FIFO_RESET_L2H_RA_FIFO_INGR_RST(x)                               (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Reset H2L_RA_FIFO
 *
 * \details
 * 1: Reset active
 * 0: Reset inactive
 *
 * Field: ::LAN80XX_LINE_SLICE_LINE_FIFO_RESET . H2L_RA_FIFO_EGR_RST
 */
#define  LAN80XX_F_LINE_SLICE_LINE_FIFO_RESET_H2L_RA_FIFO_EGR_RST(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LINE_FIFO_RESET_H2L_RA_FIFO_EGR_RST                                   (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LINE_FIFO_RESET_H2L_RA_FIFO_EGR_RST(x)                                (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * Register Group: \a LINE_SLICE:LINE_PMA_PCS_LPBK
 *
 * Loopback at PMA and PCS
 */


/**
 * \brief Loopback at interface of PCS with PMA
 *
 * \details
 * Register: \a LINE_SLICE:LINE_PMA_PCS_LPBK:H2_LPBK
 */
#define LAN80XX_LINE_SLICE_H2_LPBK                                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0, 0x8110))

/**
 * \brief
 * Malibu-25G H2 Loopback.Loops Line PCS/FEC Tx data back toward Malibu-25G
 * core. This loopback works for all port speeds, both PCS and MAC Retimer
 * modes. Blocking/Forwarding behavior toward the Line SerDes is configured
 * using H2_LPBK_FW_SEL.
 *
 * \details
 * 0: Disable Loopback
 * 1: Enable Loopback
 *
 * Field: ::LAN80XX_LINE_SLICE_H2_LPBK . H2_LPBK
 */
#define  LAN80XX_F_LINE_SLICE_H2_LPBK_H2_LPBK(x)                                                    (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_H2_LPBK_H2_LPBK                                                       (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_H2_LPBK_H2_LPBK(x)                                                    (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Configures blocking/forwarding behavior for the H2 loopback.
 *
 * \details
 * 00: Forward looped data to the Line SerDes
 * 01: Send 0x0000 data to the Host SerDes
 * 10: Send 0x00FF data to the Host Serdes
 * 11: Reserved
 *
 * Field: ::LAN80XX_LINE_SLICE_H2_LPBK . H2_LPBK_FW_SEL
 */
#define  LAN80XX_F_LINE_SLICE_H2_LPBK_H2_LPBK_FW_SEL(x)                                             (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_SLICE_H2_LPBK_H2_LPBK_FW_SEL                                                (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_SLICE_H2_LPBK_H2_LPBK_FW_SEL(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,4,2))


/**
 * \brief Loopback at PCS XGMII interface
 *
 * \details
 * Register: \a LINE_SLICE:LINE_PMA_PCS_LPBK:H3P_LPBK
 */
#define LAN80XX_LINE_SLICE_H3P_LPBK                                                                 (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8111))

/**
 * \brief
 * Malibu-25G H3P Loopback. Loops Line PCS Tx XGMII arrival data back
 * toward Malibu-25G core. This loopback works for all port speeds, both
 * PCS and MAC Retimer modes. Blocking/Forwarding behavior toward the Line
 * PCS is configured using H3P_LPBK_FW_SEL.
 *
 * \details
 * 0: Disable Loopback
 * 1: Enable Loopback
 *
 * Field: ::LAN80XX_LINE_SLICE_H3P_LPBK . H3P_LPBK
 */
#define  LAN80XX_F_LINE_SLICE_H3P_LPBK_H3P_LPBK(x)                                                  (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_H3P_LPBK_H3P_LPBK                                                     (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_H3P_LPBK_H3P_LPBK(x)                                                  (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Configures blocking/forwarding behavior for the H3P loopback.
 *
 * \details
 * 0: Forward looped XGMII data to the Line PCS
 * 1: Send XGMII Idles to the Line PCS
 *
 * Field: ::LAN80XX_LINE_SLICE_H3P_LPBK . H3P_LPBK_FW_SEL
 */
#define  LAN80XX_F_LINE_SLICE_H3P_LPBK_H3P_LPBK_FW_SEL(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_H3P_LPBK_H3P_LPBK_FW_SEL                                              (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_H3P_LPBK_H3P_LPBK_FW_SEL(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * Register Group: \a LINE_SLICE:LINE_LED_AND_SERDES_LOS
 *
 * LED and SerDes LOS configuration registe
 */


/**
 * \brief LED and SerDes LOS configuration registe
 *
 * \details
 * Register: \a LINE_SLICE:LINE_LED_AND_SERDES_LOS:SERDES_LOS
 */
#define LAN80XX_LINE_SLICE_SERDES_LOS                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8112))

/**
 * \brief
 * Indication that Serdes has loss of signal fault from
 * pma2pcs_rei_filtered
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SERDES_LOS . LOS
 */
#define  LAN80XX_F_LINE_SLICE_SERDES_LOS_LOS(x)                                                     (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_SERDES_LOS_LOS                                                        (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_SERDES_LOS_LOS(x)                                                     (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 *  Enable sent SD25G Serdes LOS to PCS
 *
 * \details
 * 0: Serdes LOS is disabled
 * 1: Serdes LOS is enabled
 *
 * Field: ::LAN80XX_LINE_SLICE_SERDES_LOS . SD25G_LOS_EN
 */
#define  LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN                                               (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_SERDES_LOS_SD25G_LOS_EN(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 *  Invert SD25G Serdes LOS to PCS
 *
 * \details
 * 0: Serdes LOS is normal
 * 1: Serdes LOS is inverted
 *
 * Field: ::LAN80XX_LINE_SLICE_SERDES_LOS . SD25G_LOS_INV
 */
#define  LAN80XX_F_LINE_SLICE_SERDES_LOS_SD25G_LOS_INV(x)                                           (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_SERDES_LOS_SD25G_LOS_INV                                              (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_SERDES_LOS_SD25G_LOS_INV(x)                                           (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 *  Enable sent MOD Module LOS to PCS
 *
 * \details
 * 0: Module LOS is disabled
 * 1: Module LOS is enabled
 *
 * Field: ::LAN80XX_LINE_SLICE_SERDES_LOS . MOD_LOS_EN
 */
#define  LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(x)                                              (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_EN                                                 (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_SLICE_SERDES_LOS_MOD_LOS_EN(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 *  Invert Module  LOS to PCS
 *
 * \details
 * 0: Module LOS is normal
 * 1: Serdes LOS is Module
 *
 * Field: ::LAN80XX_LINE_SLICE_SERDES_LOS . MOD_LOS_INV
 */
#define  LAN80XX_F_LINE_SLICE_SERDES_LOS_MOD_LOS_INV(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_SLICE_SERDES_LOS_MOD_LOS_INV                                                (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_SLICE_SERDES_LOS_MOD_LOS_INV(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,7,1))


/**
 * \brief Device LED function Control
 *
 * \details
 * Register: \a LINE_SLICE:LINE_LED_AND_SERDES_LOS:LED_CONTROL
 */
#define LAN80XX_LINE_SLICE_LED_CONTROL                                                              (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0, 0x8113))

/**
 * \brief
 * set 1 to enable the led function .
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_LED_CONTROL . LED_ENABLE
 */
#define  LAN80XX_F_LINE_SLICE_LED_CONTROL_LED_ENABLE(x)                                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_LED_CONTROL_LED_ENABLE                                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_LED_CONTROL_LED_ENABLE(x)                                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * LED mode control
 *
 * \details
 * 0:  Display activity at same blink for all speed
 * 1:  Display activity 0.5Sec when there is data transaction
 *
 * Field: ::LAN80XX_LINE_SLICE_LED_CONTROL . LED_MODE
 */
#define  LAN80XX_F_LINE_SLICE_LED_CONTROL_LED_MODE(x)                                               (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_LED_CONTROL_LED_MODE                                                  (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_LED_CONTROL_LED_MODE(x)                                               (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * LED blink time setting .
 *
 * \details
 * 00: LED blink rate 50ms
 * 01: LED blink rate 100ms
 * 10: LED blink rate 150ms
 * 11: LED blink rate 200ms
 *
 * Field: ::LAN80XX_LINE_SLICE_LED_CONTROL . BLINK_TIME_SET
 */
#define  LAN80XX_F_LINE_SLICE_LED_CONTROL_BLINK_TIME_SET(x)                                         (LAN80XX_ENCODE_BITFIELD(x,4,2))
#define  LAN80XX_M_LINE_SLICE_LED_CONTROL_BLINK_TIME_SET                                            (LAN80XX_ENCODE_BITMASK(4,2))
#define  LAN80XX_X_LINE_SLICE_LED_CONTROL_BLINK_TIME_SET(x)                                         (LAN80XX_EXTRACT_BITFIELD(x,4,2))

/**
 * Register Group: \a LINE_SLICE:H2L_RA_FIFO_INT_MASK
 *
 * H2L RA FIFO Interrupt Enables
 */


/**
 * \brief H2L RA FIFO Interrupt Enables
 *
 * \details
 * Register: \a LINE_SLICE:H2L_RA_FIFO_INT_MASK:H2L_RA_FIFO_INT_MASK
 */
#define LAN80XX_LINE_SLICE_H2L_RA_FIFO_INT_MASK                                                     (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8114))

/**
 * \brief
 * Interrupt enable for H2L_RA_FIFO_OVERFLOW
 *
 * \details
 * 0 = H2L_RA_FIFO_OVERFLOW will not propagate to interrupt
 * 1 = H2L_RA_FIFO_OVERFLOW will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_INT_MASK . H2L_RA_FIFO_OVERFLOW_INTR_EN
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_OVERFLOW_INTR_EN(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_OVERFLOW_INTR_EN                     (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_OVERFLOW_INTR_EN(x)                  (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Interrupt enable for H2L_RA_FIFO_UNDERFLOW
 *
 * \details
 * 0 = H2L_RA_FIFO_UNDERFLOW will not propagate to interrupt
 * 1 = H2L_RA_FIFO_UNDEFLOW will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_INT_MASK . H2L_RA_FIFO_UNDERFLOW_INTR_EN
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_UNDERFLOW_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_UNDERFLOW_INTR_EN                    (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_INT_MASK_H2L_RA_FIFO_UNDERFLOW_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a LINE_SLICE:H2L_RA_FIFO_INFO
 *
 * H2L RA FIFO Status
 */


/**
 * \brief H2L RA FIFO Status
 *
 * \details
 * Register: \a LINE_SLICE:H2L_RA_FIFO_INFO:H2L_RA_FIFO_STATUS
 */
#define LAN80XX_LINE_SLICE_H2L_RA_FIFO_STATUS                                                       (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8115))

/**
 * \brief
 * Overflow status bit for the H2L RA FIFO in the chip's egress data path.
 * The H2L RA FIFO is enabled when the MACs are disabled.
 *
 * \details
 * Status:
 * 0: No overflow
 * 1: Overflow
 * Write one to clear
 *
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_STATUS . H2L_RA_FIFO_OVERFLOW
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_OVERFLOW(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_OVERFLOW                               (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_OVERFLOW(x)                            (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Underflow status bit for the H2L RA FIFO in the chip'sengress data path.
 *  The H2L RA FIFO is enabled when the MACs are disabled.
 *
 * \details
 * Status:
 * 0: No underflow
 * 1: Underflow
 * Write one to clear
 *
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_STATUS . H2L_RA_FIFO_UNDERFLOW
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_UNDERFLOW(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_UNDERFLOW                              (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_STATUS_H2L_RA_FIFO_UNDERFLOW(x)                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a LINE_SLICE:H2L_RA_FIFO_IDLE_INFO
 *
 * H2L RA FIFO Idle Status
 */


/**
 * \brief H2L RA FIFO Idle Add Count
 *
 * \details
 * Register: \a LINE_SLICE:H2L_RA_FIFO_IDLE_INFO:H2L_RA_FIFO_IDLE_ADD_COUNT
 */
#define LAN80XX_LINE_SLICE_H2L_RA_FIFO_IDLE_ADD_COUNT                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x810a))

/**
 * \brief
 * Idle group count added in the H2L RA FIFO for line/host clock rate
 * compensating in the chip's egress data path.  The counter saturates when
 * the maximum value is exceeded.  The counter is cleared when the register
 * is read.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_IDLE_ADD_COUNT . H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_IDLE_ADD_COUNT_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT(x)        (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_IDLE_ADD_COUNT_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT           (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_IDLE_ADD_COUNT_H2L_RA_FIFO_IDLE_GROUP_ADD_COUNT(x)        (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief H2L RA FIFO Idle Drop Count
 *
 * \details
 * Register: \a LINE_SLICE:H2L_RA_FIFO_IDLE_INFO:H2L_RA_FIFO_IDLE_DROP_COUNT
 */
#define LAN80XX_LINE_SLICE_H2L_RA_FIFO_IDLE_DROP_COUNT                                              (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x810b))

/**
 * \brief
 * Idle group count dropped in the H2L RA FIFO for line/host clock rate
 * compensating in the chip's egress data path.  The counter saturates when
 * the maximum value is exceeded.  The counter is cleared when the register
 * is read.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_H2L_RA_FIFO_IDLE_DROP_COUNT . H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT
 */
#define  LAN80XX_F_LINE_SLICE_H2L_RA_FIFO_IDLE_DROP_COUNT_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT(x)      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_H2L_RA_FIFO_IDLE_DROP_COUNT_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_H2L_RA_FIFO_IDLE_DROP_COUNT_H2L_RA_FIFO_IDLE_GROUP_DROP_COUNT(x)      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_SLICE:L2H_RA_FIFO_INT_MASK
 *
 * L2H RA FIFO Interrupt Enables
 */


/**
 * \details
 * Register: \a LINE_SLICE:L2H_RA_FIFO_INT_MASK:L2H_RA_FIFO_INT_MASK
 */
#define LAN80XX_LINE_SLICE_L2H_RA_FIFO_INT_MASK                                                     (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8118))

/**
 * \brief
 * Interrupt enable for L2H_RA_FIFO_OVERFLOW
 *
 * \details
 * 0 = L2H_RA_FIFO_OVERFLOW will not propagate to interrupt
 * 1 = L2H_RA_FIFO_OVERFLOW will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_INT_MASK . L2H_RA_FIFO_OVERFLOW_INTR_EN
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_OVERFLOW_INTR_EN(x)                  (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_OVERFLOW_INTR_EN                     (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_OVERFLOW_INTR_EN(x)                  (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Interrupt enable for L2H_RA_FIFO_UNDERFLOW
 *
 * \details
 * 0 = L2H_RA_FIFO_UNDERFLOW will not propagate to interrupt
 * 1 = L2H_RA_FIFO_UNDERFLOW will propagate to interrupt
 *
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_INT_MASK . L2H_RA_FIFO_UNDERFLOW_INTR_EN
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_UNDERFLOW_INTR_EN(x)                 (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_UNDERFLOW_INTR_EN                    (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_INT_MASK_L2H_RA_FIFO_UNDERFLOW_INTR_EN(x)                 (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a LINE_SLICE:L2H_RA_FIFO_INFO
 *
 * L2H RA FIFO Status
 */


/**
 * \brief L2H RA FIFO Status
 *
 * \details
 * Register: \a LINE_SLICE:L2H_RA_FIFO_INFO:L2H_RA_FIFO_STATUS
 */
#define LAN80XX_LINE_SLICE_L2H_RA_FIFO_STATUS                                                       (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8119))

/**
 * \brief
 * Overflow status bit for the L2H RA FIFO in the chip's ingress data path.
 *
 * \details
 * Status:
 * 0: No overflow
 * 1: Overflow
 * Write one to clear
 *
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_STATUS . L2H_RA_FIFO_OVERFLOW
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_OVERFLOW(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_OVERFLOW                               (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_OVERFLOW(x)                            (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Underflow status bit for the L2H RA FIFO in the chip's ingress data
 * path.  The ingress FIFO is enabled when the MACs are disabled.
 *
 * \details
 * Status:
 * 0: No underflow
 * 1: Underflow
 * Write one to clear
 *
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_STATUS . L2H_RA_FIFO_UNDERFLOW
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_UNDERFLOW(x)                           (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_UNDERFLOW                              (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_STATUS_L2H_RA_FIFO_UNDERFLOW(x)                           (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * Register Group: \a LINE_SLICE:L2H_RA_FIFO_IDLE_INFO
 *
 * L2H RA FIFO Idle Status
 */


/**
 * \brief RA FIFO Idle Add Count
 *
 * \details
 * Register: \a LINE_SLICE:L2H_RA_FIFO_IDLE_INFO:L2H_RA_FIFO_IDLE_ADD_COUNT
 */
#define LAN80XX_LINE_SLICE_L2H_RA_FIFO_IDLE_ADD_COUNT                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x810c))

/**
 * \brief
 * Idle group count added in the L2H RA FIFO for line/host clock rate
 * compensating in the chip's ingress data path.  The counter saturates
 * when the maximum value is exceeded.  The counter is cleared when the
 * register is read.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_IDLE_ADD_COUNT . L2H_RA_FIFO_IDLE_GROUP_ADD_COUNT
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_IDLE_ADD_COUNT_L2H_RA_FIFO_IDLE_GROUP_ADD_COUNT(x)        (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_IDLE_ADD_COUNT_L2H_RA_FIFO_IDLE_GROUP_ADD_COUNT           (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_IDLE_ADD_COUNT_L2H_RA_FIFO_IDLE_GROUP_ADD_COUNT(x)        (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief RA FIFO Idle Drop Count
 *
 * \details
 * Register: \a LINE_SLICE:L2H_RA_FIFO_IDLE_INFO:L2H_RA_FIFO_IDLE_DROP_COUNT
 */
#define LAN80XX_LINE_SLICE_L2H_RA_FIFO_IDLE_DROP_COUNT                                              (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x810d))

/**
 * \brief
 * Idle group count dropped in the L2H RA FIFO for line/host clock rate
 * compensating in the chip's ingress data path.  The counter saturates
 * when the maximum value is exceeded.  The counter is cleared when the
 * register is read.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_L2H_RA_FIFO_IDLE_DROP_COUNT . L2H_RA_FIFO_IDLE_GROUP_DROP_COUNT
 */
#define  LAN80XX_F_LINE_SLICE_L2H_RA_FIFO_IDLE_DROP_COUNT_L2H_RA_FIFO_IDLE_GROUP_DROP_COUNT(x)      (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_L2H_RA_FIFO_IDLE_DROP_COUNT_L2H_RA_FIFO_IDLE_GROUP_DROP_COUNT         (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_L2H_RA_FIFO_IDLE_DROP_COUNT_L2H_RA_FIFO_IDLE_GROUP_DROP_COUNT(x)      (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_SLICE:LINE_CORE_CFG
 *
 * Line slice core configuration Registers
 */


/**
 * \brief Line Slice Configuration
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:SLICE_CONFIG
 */
#define LAN80XX_LINE_SLICE_SLICE_CONFIG                                                             (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8120))

/**
 * \brief
 * Mux select of MAC ReTiming Mode or PCS ReTiming Mode
 *
 * \details
 * 0 = PCS ReTiming Mode
 * 1 = MAC ReTiming Mode
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . MAC_RETIMING_MODE
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE                                        (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_MAC_RETIMING_MODE(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Select MCH header replace Preamble and SFD in the packet or not
 *
 * \details
 * 0 = Peamble and SFD in the head of the packet
 * 1 = MCH header replace preamble and SFD
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . MCH_ENABLE
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE(x)                                            (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE                                               (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE(x)                                            (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Determine Local Fault/Remode Fault terminated at Line MAC or System MAC.
 *
 * \details
 * 0 = Local fault/Remote fault terminated at system MAC
 * 1 = Local fault/Remote fault terminated at Line MAC
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . LF_RF_LINE_MAC_MODE
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_LF_RF_LINE_MAC_MODE(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_LF_RF_LINE_MAC_MODE                                      (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_LF_RF_LINE_MAC_MODE(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Determine verify and response of Preemption terminated at LINE MAC or
 * System MAC.
 *
 * \details
 * 0 = Verify and response terminated at system MAC
 * 1 = Verify and response terminated at Line MAC
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . VERIFY_RESPONSE_LINE_MAC_MODE
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_VERIFY_RESPONSE_LINE_MAC_MODE(x)                         (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_VERIFY_RESPONSE_LINE_MAC_MODE                            (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_VERIFY_RESPONSE_LINE_MAC_MODE(x)                         (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * MACsec Ingress Host Format Number Select
 *
 * \details
 * 00 : ingress host format 0 is selected
 * 01 : ingress host format 1 is selected
 * 10 : ingress host format 2 is selected
 * 11 : ingress host format 3 is selected
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . INGRESS_HOST_FORMAT
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_INGRESS_HOST_FORMAT(x)                                   (LAN80XX_ENCODE_BITFIELD(x,2,2))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_INGRESS_HOST_FORMAT                                      (LAN80XX_ENCODE_BITMASK(2,2))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_INGRESS_HOST_FORMAT(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,2,2))

/**
 * \brief
 * MACsec Egress Host Format Number Select
 *
 * \details
 * 00 : egress host format 0 is selected
 * 01 : egress host format 1 is selected
 * 10 : egress host format 2 is selected
 * 11 : egress host format 3 is selected
 *
 * Field: ::LAN80XX_LINE_SLICE_SLICE_CONFIG . EGRESS_HOST_FORMAT
 */
#define  LAN80XX_F_LINE_SLICE_SLICE_CONFIG_EGRESS_HOST_FORMAT(x)                                    (LAN80XX_ENCODE_BITFIELD(x,0,2))
#define  LAN80XX_M_LINE_SLICE_SLICE_CONFIG_EGRESS_HOST_FORMAT                                       (LAN80XX_ENCODE_BITMASK(0,2))
#define  LAN80XX_X_LINE_SLICE_SLICE_CONFIG_EGRESS_HOST_FORMAT(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,0,2))


/**
 * \brief bit[15:0] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_0
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_0                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8121))

/**
 * \brief
 * This is the bit[15:0] of dummy sectag insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_0 . DUMMY_SECTAG_INS_PATTERN_0
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_0_DUMMY_SECTAG_INS_PATTERN_0(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_0_DUMMY_SECTAG_INS_PATTERN_0                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_0_DUMMY_SECTAG_INS_PATTERN_0(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[31:16] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_1
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_1                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8122))

/**
 * \brief
 * This is the bit[31:16] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_1 . DUMMY_SECTAG_INS_PATTERN_1
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_1_DUMMY_SECTAG_INS_PATTERN_1(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_1_DUMMY_SECTAG_INS_PATTERN_1                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_1_DUMMY_SECTAG_INS_PATTERN_1(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[47:32] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_2
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_2                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8123))

/**
 * \brief
 * This is the bit[47:32] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_2 . DUMMY_SECTAG_INS_PATTERN_2
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_2_DUMMY_SECTAG_INS_PATTERN_2(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_2_DUMMY_SECTAG_INS_PATTERN_2                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_2_DUMMY_SECTAG_INS_PATTERN_2(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[63:48] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_3
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_3                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8124))

/**
 * \brief
 * This is the bit[63:48] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_3 . DUMMY_SECTAG_INS_PATTERN_3
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_3_DUMMY_SECTAG_INS_PATTERN_3(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_3_DUMMY_SECTAG_INS_PATTERN_3                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_3_DUMMY_SECTAG_INS_PATTERN_3(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[79:64] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_4
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_4                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8125))

/**
 * \brief
 * This is the bit[79:64] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_4 . DUMMY_SECTAG_INS_PATTERN_4
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_4_DUMMY_SECTAG_INS_PATTERN_4(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_4_DUMMY_SECTAG_INS_PATTERN_4                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_4_DUMMY_SECTAG_INS_PATTERN_4(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[95:80] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_5
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_5                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8126))

/**
 * \brief
 * This is the bit[95:80] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_5 . DUMMY_SECTAG_INS_PATTERN_5
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_5_DUMMY_SECTAG_INS_PATTERN_5(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_5_DUMMY_SECTAG_INS_PATTERN_5                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_5_DUMMY_SECTAG_INS_PATTERN_5(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[111:96] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_6
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_6                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8127))

/**
 * \brief
 * This is the bit[111:96] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_6 . DUMMY_SECTAG_INS_PATTERN_6
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_6_DUMMY_SECTAG_INS_PATTERN_6(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_6_DUMMY_SECTAG_INS_PATTERN_6                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_6_DUMMY_SECTAG_INS_PATTERN_6(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[127:112] of dummy sectag insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_SECTAG_INS_PATTERN_7
 */
#define LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_7                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8128))

/**
 * \brief
 * This is the bit[127:112] of dummy sectag insert pattern when MACsec
 * ingress host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_7 . DUMMY_SECTAG_INS_PATTERN_7
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_7_DUMMY_SECTAG_INS_PATTERN_7(x)              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_7_DUMMY_SECTAG_INS_PATTERN_7                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_SECTAG_INS_PATTERN_7_DUMMY_SECTAG_INS_PATTERN_7(x)              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[15:0] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_0
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_0                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8129))

/**
 * \brief
 * This is the bit[15:0] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_0 . DUMMY_ICV_INS_PATTERN_0
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_0_DUMMY_ICV_INS_PATTERN_0(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_0_DUMMY_ICV_INS_PATTERN_0                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_0_DUMMY_ICV_INS_PATTERN_0(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[31:16] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_1
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_1                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812a))

/**
 * \brief
 * This is the bit[31:16] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_1 . DUMMY_ICV_INS_PATTERN_1
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_1_DUMMY_ICV_INS_PATTERN_1(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_1_DUMMY_ICV_INS_PATTERN_1                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_1_DUMMY_ICV_INS_PATTERN_1(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[47:32] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_2
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_2                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812b))

/**
 * \brief
 * This is the bit[47:32] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_2 . DUMMY_ICV_INS_PATTERN_2
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_2_DUMMY_ICV_INS_PATTERN_2(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_2_DUMMY_ICV_INS_PATTERN_2                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_2_DUMMY_ICV_INS_PATTERN_2(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[63:48] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_3
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_3                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812c))

/**
 * \brief
 * This is the bit[63:48] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_3 . DUMMY_ICV_INS_PATTERN_3
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_3_DUMMY_ICV_INS_PATTERN_3(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_3_DUMMY_ICV_INS_PATTERN_3                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_3_DUMMY_ICV_INS_PATTERN_3(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[79:64] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_4
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_4                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812d))

/**
 * \brief
 * This is the bit[79:64] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_4 . DUMMY_ICV_INS_PATTERN_4
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_4_DUMMY_ICV_INS_PATTERN_4(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_4_DUMMY_ICV_INS_PATTERN_4                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_4_DUMMY_ICV_INS_PATTERN_4(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[95:80] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_5
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_5                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812e))

/**
 * \brief
 * This is the bit[95:80] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_5 . DUMMY_ICV_INS_PATTERN_5
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_5_DUMMY_ICV_INS_PATTERN_5(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_5_DUMMY_ICV_INS_PATTERN_5                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_5_DUMMY_ICV_INS_PATTERN_5(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[111:96] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_6
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_6                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x812f))

/**
 * \brief
 * This is the bit[111:96] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_6 . DUMMY_ICV_INS_PATTERN_6
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_6_DUMMY_ICV_INS_PATTERN_6(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_6_DUMMY_ICV_INS_PATTERN_6                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_6_DUMMY_ICV_INS_PATTERN_6(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[127:112] of dummy icv insert pattern
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:DUMMY_ICV_INS_PATTERN_7
 */
#define LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_7                                                  (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8130))

/**
 * \brief
 * This is the bit[127:112] of dummy icv insert pattern when MACsec ingress
 * host format 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_DUMMY_ICV_INS_PATTERN_7 . DUMMY_ICV_INS_PATTERN_7
 */
#define  LAN80XX_F_LINE_SLICE_DUMMY_ICV_INS_PATTERN_7_DUMMY_ICV_INS_PATTERN_7(x)                    (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_DUMMY_ICV_INS_PATTERN_7_DUMMY_ICV_INS_PATTERN_7                       (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_DUMMY_ICV_INS_PATTERN_7_DUMMY_ICV_INS_PATTERN_7(x)                    (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[15:0] of 32 bits pattern that indicate to remove 8 bytes SecTag
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:RM_DUMMY_PATTERN0_0
 */
#define LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN0_0                                                      (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8131))

/**
 * \brief
 * This is the bit[15:0] of dummy sectag remove pattern 0 when MACsec
 * egress host format 1 or 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN0_0 . DUMMY_SECTAG_RM_PATTERN0_0
 */
#define  LAN80XX_F_LINE_SLICE_RM_DUMMY_PATTERN0_0_DUMMY_SECTAG_RM_PATTERN0_0(x)                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_RM_DUMMY_PATTERN0_0_DUMMY_SECTAG_RM_PATTERN0_0                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_RM_DUMMY_PATTERN0_0_DUMMY_SECTAG_RM_PATTERN0_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[31:16] of 32 bits pattern that indicate to remove 8 bytes SecTag
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:RM_DUMMY_PATTERN0_1
 */
#define LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN0_1                                                      (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8132))

/**
 * \brief
 * This is the bit[31:16] of dummy sectag remove pattern 0 when MACsec
 * egress host format 1 or 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN0_1 . DUMMY_SECTAG_RM_PATTERN0_1
 */
#define  LAN80XX_F_LINE_SLICE_RM_DUMMY_PATTERN0_1_DUMMY_SECTAG_RM_PATTERN0_1(x)                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_RM_DUMMY_PATTERN0_1_DUMMY_SECTAG_RM_PATTERN0_1                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_RM_DUMMY_PATTERN0_1_DUMMY_SECTAG_RM_PATTERN0_1(x)                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[15:0] of 32 bits pattern that indicate to remove 16 bytes SecTag
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:RM_DUMMY_PATTERN1_0
 */
#define LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN1_0                                                      (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8133))

/**
 * \brief
 * This is the bit[15:0] of dummy sectag remove pattern 1 when MACsec
 * egress host format 1 or 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN1_0 . DUMMY_SECTAG_RM_PATTERN1_0
 */
#define  LAN80XX_F_LINE_SLICE_RM_DUMMY_PATTERN1_0_DUMMY_SECTAG_RM_PATTERN1_0(x)                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_RM_DUMMY_PATTERN1_0_DUMMY_SECTAG_RM_PATTERN1_0                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_RM_DUMMY_PATTERN1_0_DUMMY_SECTAG_RM_PATTERN1_0(x)                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief bit[31:16] of 32 bits pattern that indicate to remove 16 bytes SecTag
 *
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_CFG:RM_DUMMY_PATTERN1_1
 */
#define LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN1_1                                                      (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8134))

/**
 * \brief
 * This is the bit[31:16] of dummy sectag remove pattern 1 when MACsec
 * egress host format 1 or 2 is selected.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_RM_DUMMY_PATTERN1_1 . DUMMY_SECTAG_RM_PATTERN1_1
 */
#define  LAN80XX_F_LINE_SLICE_RM_DUMMY_PATTERN1_1_DUMMY_SECTAG_RM_PATTERN1_1(x)                     (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_RM_DUMMY_PATTERN1_1_DUMMY_SECTAG_RM_PATTERN1_1                        (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_RM_DUMMY_PATTERN1_1_DUMMY_SECTAG_RM_PATTERN1_1(x)                     (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_SLICE:LINE_CORE_STATUS
 *
 * Line core status Registers
 */


/**
 * \details
 * Register: \a LINE_SLICE:LINE_CORE_STATUS:MACSEC_STATUS
 */
#define LAN80XX_LINE_SLICE_MACSEC_STATUS                                                            (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8140))

/**
 * \brief
 * Sticky bit for pkt_tx_split_tag_sc_err. This will only happen in ingress
 * path
 *
 * \details
 * 0 = pkt_tx_split_tag_sc_err did not happen
 * 1 = pkt_tx_split_tag_sc_err happened
 *
 * Field: ::LAN80XX_LINE_SLICE_MACSEC_STATUS . PKT_TX_SPLIT_TAG_SC_ERR_STICKY
 */
#define  LAN80XX_F_LINE_SLICE_MACSEC_STATUS_PKT_TX_SPLIT_TAG_SC_ERR_STICKY(x)                       (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_MACSEC_STATUS_PKT_TX_SPLIT_TAG_SC_ERR_STICKY                          (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_MACSEC_STATUS_PKT_TX_SPLIT_TAG_SC_ERR_STICKY(x)                       (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Sticky bit for pkt_tx_min_frag_err_ingr
 *
 * \details
 * 0 = pkt_tx_min_frag_err_ingr did not happen
 * 1 = pkt_tx_min_frag_err_ingr happened
 *
 * Field: ::LAN80XX_LINE_SLICE_MACSEC_STATUS . PKT_TX_MIN_FRAG_ERR_INGR
 */
#define  LAN80XX_F_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_INGR(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_INGR                                (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_INGR(x)                             (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Sticky bit for pkt_dummy_rm_neq_tag_add. This will only happen in egress
 * path
 *
 * \details
 * 0 = pkt_dummy_rm_neq_tag_add did not happen
 * 1 = pkt_dummy_rm_neq_tag_add happened
 *
 * Field: ::LAN80XX_LINE_SLICE_MACSEC_STATUS . PKT_DUMMY_RM_NEQ_TAG_ADD_STICKY
 */
#define  LAN80XX_F_LINE_SLICE_MACSEC_STATUS_PKT_DUMMY_RM_NEQ_TAG_ADD_STICKY(x)                      (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_SLICE_MACSEC_STATUS_PKT_DUMMY_RM_NEQ_TAG_ADD_STICKY                         (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_SLICE_MACSEC_STATUS_PKT_DUMMY_RM_NEQ_TAG_ADD_STICKY(x)                      (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Sticky bit for pkt_tx_min_frag_err_egr
 *
 * \details
 * 0 = pkt_tx_min_frag_err_egr did not happen
 * 1 = pkt_tx_min_frag_err_egr happened
 *
 * Field: ::LAN80XX_LINE_SLICE_MACSEC_STATUS . PKT_TX_MIN_FRAG_ERR_EGR
 */
#define  LAN80XX_F_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_EGR(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_EGR                                 (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_SLICE_MACSEC_STATUS_PKT_TX_MIN_FRAG_ERR_EGR(x)                              (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * Register Group: \a LINE_SLICE:SPARE
 *
 * Spare Registers
 */


/**
 * \brief Spare Read writeable register 0
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RW_0
 */
#define LAN80XX_LINE_SLICE_SPARE_RW_0                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8150))

/**
 * \brief
 * Spare read writeable register 0
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RW_0 . SPARE_RW_0
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RW_0_SPARE_RW_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RW_0_SPARE_RW_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RW_0_SPARE_RW_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Read writeable register 1
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RW_1
 */
#define LAN80XX_LINE_SLICE_SPARE_RW_1                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8151))

/**
 * \brief
 * Spare read writeable register 1
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RW_1 . SPARE_RW_1
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RW_1_SPARE_RW_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RW_1_SPARE_RW_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RW_1_SPARE_RW_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Read writeable register 2
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RW_2
 */
#define LAN80XX_LINE_SLICE_SPARE_RW_2                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8152))

/**
 * \brief
 * Spare read writeable register 2
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RW_2 . SPARE_RW_2
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RW_2_SPARE_RW_2(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RW_2_SPARE_RW_2                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RW_2_SPARE_RW_2(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Read writeable register 3
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RW_3
 */
#define LAN80XX_LINE_SLICE_SPARE_RW_3                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8153))

/**
 * \brief
 * Spare read writeable register 3
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RW_3 . SPARE_RW_3
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RW_3_SPARE_RW_3(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RW_3_SPARE_RW_3                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RW_3_SPARE_RW_3(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Read only register 0
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RO_0
 */
#define LAN80XX_LINE_SLICE_SPARE_RO_0                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8154))

/**
 * \brief
 * Spare read only register 0
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RO_0 . SPARE_RO_0
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RO_0_SPARE_RO_0(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RO_0_SPARE_RO_0                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RO_0_SPARE_RO_0(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))


/**
 * \brief Spare Read only register 1
 *
 * \details
 * Register: \a LINE_SLICE:SPARE:SPARE_RO_1
 */
#define LAN80XX_LINE_SLICE_SPARE_RO_1                                                               (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8155))

/**
 * \brief
 * Spare read only register 1
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_SPARE_RO_1 . SPARE_RO_1
 */
#define  LAN80XX_F_LINE_SLICE_SPARE_RO_1_SPARE_RO_1(x)                                              (LAN80XX_ENCODE_BITFIELD(x,0,16))
#define  LAN80XX_M_LINE_SLICE_SPARE_RO_1_SPARE_RO_1                                                 (LAN80XX_ENCODE_BITMASK(0,16))
#define  LAN80XX_X_LINE_SLICE_SPARE_RO_1_SPARE_RO_1(x)                                              (LAN80XX_EXTRACT_BITFIELD(x,0,16))

/**
 * Register Group: \a LINE_SLICE:BIST1_REG
 *
 * BIST1 control and status register
 */


/**
 * \brief BIST1 Start/Go Register
 *
 * \details
 * Register: \a LINE_SLICE:BIST1_REG:BIST1_GO
 */
#define LAN80XX_LINE_SLICE_BIST1_GO                                                                 (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8160))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . INGR_SA_CONTEXT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_INGR_SA_CONTEXT_BIST_GO(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_INGR_SA_CONTEXT_BIST_GO                                      (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_INGR_SA_CONTEXT_BIST_GO(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . INGR_SA_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_INGR_SA_STAT_BIST_GO(x)                                      (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_INGR_SA_STAT_BIST_GO                                         (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_INGR_SA_STAT_BIST_GO(x)                                      (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . INGR_CLASS_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_INGR_CLASS_STAT_BIST_GO(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_INGR_CLASS_STAT_BIST_GO                                      (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_INGR_CLASS_STAT_BIST_GO(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . INGR_VPORT_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_INGR_VPORT_STAT_BIST_GO(x)                                   (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_INGR_VPORT_STAT_BIST_GO                                      (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_INGR_VPORT_STAT_BIST_GO(x)                                   (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_SA_CONTEXT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_SA_CONTEXT_BIST_GO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_SA_CONTEXT_BIST_GO                                       (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_SA_CONTEXT_BIST_GO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_SA_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_SA_STAT_BIST_GO(x)                                       (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_SA_STAT_BIST_GO                                          (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_SA_STAT_BIST_GO(x)                                       (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_CLASS_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_CLASS_STAT_BIST_GO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_CLASS_STAT_BIST_GO                                       (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_CLASS_STAT_BIST_GO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_VPORT_STAT_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_VPORT_STAT_BIST_GO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_VPORT_STAT_BIST_GO                                       (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_VPORT_STAT_BIST_GO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_CAPTURE_FIFO_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_CAPTURE_FIFO_BIST_GO(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_CAPTURE_FIFO_BIST_GO                                     (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_CAPTURE_FIFO_BIST_GO(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . INGR_FC_BUFFER_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_INGR_FC_BUFFER_BIST_GO(x)                                    (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_INGR_FC_BUFFER_BIST_GO                                       (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_INGR_FC_BUFFER_BIST_GO(x)                                    (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * Set 1: Enable BIST. This bit must be cleared when associated DONE bit
 * reads one.
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_GO . EGR_FC_BUFFER_BIST_GO
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_GO_EGR_FC_BUFFER_BIST_GO(x)                                     (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_GO_EGR_FC_BUFFER_BIST_GO                                        (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_SLICE_BIST1_GO_EGR_FC_BUFFER_BIST_GO(x)                                     (LAN80XX_EXTRACT_BITFIELD(x,10,1))


/**
 * \brief BIST1 Done Status Register
 *
 * \details
 * Register: \a LINE_SLICE:BIST1_REG:BIST1_STATUS
 */
#define LAN80XX_LINE_SLICE_BIST1_STATUS                                                             (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8161))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . INGR_SA_CONTEXT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_INGR_SA_CONTEXT_BIST_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_INGR_SA_CONTEXT_BIST_DONE                                (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_INGR_SA_CONTEXT_BIST_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . INGR_SA_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_INGR_SA_STAT_BIST_DONE(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_INGR_SA_STAT_BIST_DONE                                   (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_INGR_SA_STAT_BIST_DONE(x)                                (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . INGR_CLASS_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_INGR_CLASS_STAT_BIST_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_INGR_CLASS_STAT_BIST_DONE                                (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_INGR_CLASS_STAT_BIST_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . INGR_VPORT_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_INGR_VPORT_STAT_BIST_DONE(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_INGR_VPORT_STAT_BIST_DONE                                (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_INGR_VPORT_STAT_BIST_DONE(x)                             (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_SA_CONTEXT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_SA_CONTEXT_BIST_DONE(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_SA_CONTEXT_BIST_DONE                                 (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_SA_CONTEXT_BIST_DONE(x)                              (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_SA_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_SA_STAT_BIST_DONE(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_SA_STAT_BIST_DONE                                    (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_SA_STAT_BIST_DONE(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_CLASS_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_CLASS_STAT_BIST_DONE(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_CLASS_STAT_BIST_DONE                                 (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_CLASS_STAT_BIST_DONE(x)                              (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_VPORT_STAT_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_VPORT_STAT_BIST_DONE(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_VPORT_STAT_BIST_DONE                                 (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_VPORT_STAT_BIST_DONE(x)                              (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_CAPTURE_FIFO_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_CAPTURE_FIFO_BIST_DONE(x)                            (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_CAPTURE_FIFO_BIST_DONE                               (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_CAPTURE_FIFO_BIST_DONE(x)                            (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . INGR_FC_BUFFER_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_INGR_FC_BUFFER_BIST_DONE(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_INGR_FC_BUFFER_BIST_DONE                                 (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_INGR_FC_BUFFER_BIST_DONE(x)                              (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * 1: Done
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_STATUS . EGR_FC_BUFFER_BIST_DONE
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_STATUS_EGR_FC_BUFFER_BIST_DONE(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_STATUS_EGR_FC_BUFFER_BIST_DONE                                  (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_SLICE_BIST1_STATUS_EGR_FC_BUFFER_BIST_DONE(x)                               (LAN80XX_EXTRACT_BITFIELD(x,10,1))


/**
 * \brief BIST1 Result Register
 *
 * \details
 * Register: \a LINE_SLICE:BIST1_REG:BIST1_RESULT
 */
#define LAN80XX_LINE_SLICE_BIST1_RESULT                                                             (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8162))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . INGR_SA_CONTEXT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_INGR_SA_CONTEXT_BIST_STS(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),0,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_INGR_SA_CONTEXT_BIST_STS                                 (LAN80XX_BIT(0))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_INGR_SA_CONTEXT_BIST_STS(x)                              (LAN80XX_EXTRACT_BITFIELD(x,0,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . INGR_SA_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_INGR_SA_STAT_BIST_STS(x)                                 (LAN80XX_ENCODE_BITFIELD(!!(x),1,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_INGR_SA_STAT_BIST_STS                                    (LAN80XX_BIT(1))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_INGR_SA_STAT_BIST_STS(x)                                 (LAN80XX_EXTRACT_BITFIELD(x,1,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . INGR_CLASS_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_INGR_CLASS_STAT_BIST_STS(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),2,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_INGR_CLASS_STAT_BIST_STS                                 (LAN80XX_BIT(2))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_INGR_CLASS_STAT_BIST_STS(x)                              (LAN80XX_EXTRACT_BITFIELD(x,2,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . INGR_VPORT_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_INGR_VPORT_STAT_BIST_STS(x)                              (LAN80XX_ENCODE_BITFIELD(!!(x),3,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_INGR_VPORT_STAT_BIST_STS                                 (LAN80XX_BIT(3))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_INGR_VPORT_STAT_BIST_STS(x)                              (LAN80XX_EXTRACT_BITFIELD(x,3,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_SA_CONTEXT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_SA_CONTEXT_BIST_STS(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),4,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_SA_CONTEXT_BIST_STS                                  (LAN80XX_BIT(4))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_SA_CONTEXT_BIST_STS(x)                               (LAN80XX_EXTRACT_BITFIELD(x,4,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_SA_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_SA_STAT_BIST_STS(x)                                  (LAN80XX_ENCODE_BITFIELD(!!(x),5,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_SA_STAT_BIST_STS                                     (LAN80XX_BIT(5))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_SA_STAT_BIST_STS(x)                                  (LAN80XX_EXTRACT_BITFIELD(x,5,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_CLASS_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_CLASS_STAT_BIST_STS(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),6,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_CLASS_STAT_BIST_STS                                  (LAN80XX_BIT(6))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_CLASS_STAT_BIST_STS(x)                               (LAN80XX_EXTRACT_BITFIELD(x,6,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_VPORT_STAT_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_VPORT_STAT_BIST_STS(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),7,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_VPORT_STAT_BIST_STS                                  (LAN80XX_BIT(7))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_VPORT_STAT_BIST_STS(x)                               (LAN80XX_EXTRACT_BITFIELD(x,7,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_CAPTURE_FIFO_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_CAPTURE_FIFO_BIST_STS(x)                             (LAN80XX_ENCODE_BITFIELD(!!(x),8,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_CAPTURE_FIFO_BIST_STS                                (LAN80XX_BIT(8))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_CAPTURE_FIFO_BIST_STS(x)                             (LAN80XX_EXTRACT_BITFIELD(x,8,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . INGR_FC_BUFFER_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_INGR_FC_BUFFER_BIST_STS(x)                               (LAN80XX_ENCODE_BITFIELD(!!(x),9,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_INGR_FC_BUFFER_BIST_STS                                  (LAN80XX_BIT(9))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_INGR_FC_BUFFER_BIST_STS(x)                               (LAN80XX_EXTRACT_BITFIELD(x,9,1))

/**
 * \brief
 * 1: Pass 0: Fail
 *
 * \details
 * Field: ::LAN80XX_LINE_SLICE_BIST1_RESULT . EGR_FC_BUFFER_BIST_STS
 */
#define  LAN80XX_F_LINE_SLICE_BIST1_RESULT_EGR_FC_BUFFER_BIST_STS(x)                                (LAN80XX_ENCODE_BITFIELD(!!(x),10,1))
#define  LAN80XX_M_LINE_SLICE_BIST1_RESULT_EGR_FC_BUFFER_BIST_STS                                   (LAN80XX_BIT(10))
#define  LAN80XX_X_LINE_SLICE_BIST1_RESULT_EGR_FC_BUFFER_BIST_STS(x)                                (LAN80XX_EXTRACT_BITFIELD(x,10,1))

/**
 * \brief LINE RAM INIT Register
 *
 * \details
 * Register: \a LINE_SLICE:LINE_RAM_INIT:RAM_INIT
 */
#define LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT                                                   (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8170))

/**
 * \brief LINE RAM INIT BUSY Register
 *
 * \details
 * Register: \a LINE_SLICE:LINE_RAM_INII:RAM_INIT_BUSY
 */
#define LAN80XX_LINE_SLICE_LINE_RAM_INIT_RAM_INIT_BUSY                                              (LAN80XX_IOREG(MMD_ID_LINE_SLICE, 0,0x8171))
#endif /* _LAN80XX_MALIBU25G_REGS_LINE_SLICE_H_ */
