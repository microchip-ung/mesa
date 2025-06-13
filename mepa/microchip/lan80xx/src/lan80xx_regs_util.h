// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_LAN80XX_REGS_COMMON_H_
#define _MEPA_LAN80XX_REGS_COMMON_H_

#define LAN80XX_BIT(x)                   (1U << (x))
#define LAN80XX_BITMASK(x)               ((1U << (x)) - 1)
#define LAN80XX_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & LAN80XX_BITMASK(w))
#define LAN80XX_ENCODE_BITFIELD(x,o,w)   (((x) & LAN80XX_BITMASK(w)) << (o))
#define LAN80XX_ENCODE_BITMASK(o,w)      (LAN80XX_BITMASK(w) << (o))

#define LAN80XX_8_BIT_SHIFT      (8U)
#define LAN80XX_4_BIT_SHIFT      (4U)
#define LAN80XX_16_BIT_SHIFT     (16U)
#define LAN80XX_12_BIT_SHIFT     (12U)
#define LAN80XX_24_BIT_SHIFT     (24U)
#define LAN80XX_32_BIT_SHIFT     (32U)
#define LAN80XX_BYTE_MASK        (0xFFU)
#define LAN80XX_WORD_MASK        (0xFU)
#define LAN80XX_WORD(msb, lsb)   ((msb << 8U) | lsb)
#define LAN80XX_MASK_THIRD_BYTE  (0xFF0000U)
#define LAN80XX_32BIT_REG_MASK   (0xFFFFFFFF)

#define LAN80XX_HOST_LINE_REG(front,h_l,back) \
	(((h_l) != 0U) ? (front##_LINE_##back) : (front##_HOST_##back))

#define LAN80XX_LINE_HOST_MAC_REG_EXPAN(front, is_host, back) \
	(((is_host) != 0U) ? (front##_HOST_MAC_HOST_MAC_##back) : (front##_LINE_MAC_LINE_MAC_##back))


#define LAN80XX_HOST_LINE_INTR_REG(front, h_l, back) \
	(((h_l) != 0U) ? (front##_LINE_INTR_CTRL_LINE_##back) : (front##_HOST_INTR_CTRL_HOST_##back))


#define VTSS_IO_OFFSET0(x) (x)

/*
 * @param dev  - device id
 * @param is32 - is register 32 bit
 * @param off  - subtarget offset
 */
#define LAN80XX_IOREG(mmd, is32, off)      _lan80xx_ioreg(&data->io_var, (mmd), (mepa_bool_t)(is32), (off))


/******************** DEVICE ID(MMD ID) ****************************/

/* Device ID for Line KR */
#define MMD_ID_LINE_KR            (0x7U)
/* Device ID for Host KR */
#define MMD_ID_HOST_KR            (0xFU)
/* Device ID for LINE PCS CFG */
#define MMD_ID_LINE_PCS_CFG       (0x3U)
/* Device ID for LINE PCS CFG for 1G */
#define MMD_ID_LINE_PCS_CFG_1G    (0x1U)
/* Device ID for HOST PCS CFG */
#define MMD_ID_HOST_PCS_CFG       (0xBU)
/* Device ID for HOST PCS CFG for 1G */
#define MMD_ID_HOST_PCS_CFG_1G    (0x9U)
/* Device ID for LINE PCS25G */
#define MMD_ID_LINE_PCS25G        (0x3U)
/* Device ID for HOST PCS25G */
#define MMD_ID_HOST_PCS25G        (0xBU)
/* Device ID for LINE PMA */
#define MMD_ID_LINE_PMA_8BIT      (0x1U)
/* Device ID for LINE PMA */
#define MMD_ID_LINE_PMA           (0x1U)
/* Device ID for LINE PMA EXT */
#define MMD_ID_LINE_PMA_EXT       (0x1U)
/* Device ID for Host PMA */
#define MMD_ID_HOST_PMA_8BIT      (0x9U)
/* Device ID for Host PMA */
#define MMD_ID_HOST_PMA           (0x9U)
/* Device ID for LINE MAC */
#define MMD_ID_LINE_MAC           (0x3U)
/* Device ID for HOST MAC */
#define MMD_ID_HOST_MAC           (0x3U)
/* Device ID for LINE SLICE */
#define MMD_ID_LINE_SLICE         (0x1U)
/* Device ID for HOST SLICE */
#define MMD_ID_HOST_SLICE         (0x9U)
/* Device ID for CROSS CONNECT */
#define MMD_ID_CROSS_CONN         (0x1EU)
/* Device ID for MAC_FC_BUFFER */
#define MMD_ID_MAC_FC_BUFF        (0x3U)
/* Device ID for MCU_IO_MISC */
#define MMD_ID_MCU_IO_MISC        (0x1EU)
/* Device ID for Global Register */
#define MMD_ID_GLOBAL_REGISTERS   (0x1EU)
/* Device ID for Line Interrupt Control */
#define MMD_ID_LINE_INTR_CTL      (0x1U)
/* Device ID for Host Interrupt Control */
#define MMD_ID_HOST_INTR_CTL      (0x9U)
/* Device ID for GPIO Control */
#define MMD_ID_GPIO_CTRL          (0x1EU)
/* Device ID for PKT Gen/Mon Conf */
#define MMD_ID_PKT_BIST           (0x09U)
/* Device ID for SFP TWS */
#define MMD_ID_SFP_TWS            (0x01U)
/* Device ID for HOST RSFEC */
#define MMD_ID_HOST_RSFEC         (0x09U)
/* Device ID for LINE RSFEC */
#define MMD_ID_LINE_RSFEC         (0x01U)
/* Device ID for CLK CFG */
#define MMD_ID_CLK_CFG            (0x1EU)
/* MMD Address related to 1588 */
#define MMD_ID_PTP_BLOCK          (0xAU)
/* Device ID for PTP LTC */
#define MMD_ID_PTP_LTC            (0x1EU)
/* Device ID for PTP ANAx_EGR and ANAx_INGR */
#define MMD_ID_PTP_ANAx           (0xAU)
/* Device ID for MACSEC INGR */
#define MMD_ID_MACSEC_INGR        (0x8U)
/* Device ID for MACSEC EGR */
#define MMD_ID_MACSEC_EGR         (0x1FU)
/* Device ID for MCU MAILBOX */
#define MMD_ID_MCU_MAILBOX        (0x1EU)
/* Device ID for MCU IO MNGT MISC */
#define MMD_ID_MCU_IO_MNGT_MISC   (0x1EU)


/* Register Target Id */
#define LAN80XX_TARGET_ID_LINE_PMA             (0x01U)
#define LAN80XX_TARGET_ID_LINE_PCS25G          (0x03U)
#define LAN80XX_TARGET_ID_LINE_RS_FEC          (0x13U)
#define LAN80XX_TARGET_ID_LINE_PCS_CFG         (0x07U)
#define LAN80XX_TARGET_ID_LINE_KR              (0x08U)
#define LAN80XX_TARGET_ID_LINE_INTR_CTRL       (0x09U)
#define LAN80XX_TARGET_ID_LINE_MAC             (0x0EU)
#define LAN80XX_TARGET_ID_SFP_TWS              (0x0FU)
#define LAN80XX_TARGET_ID_LINE_PMA_8BIT        (0x10U)
#define LAN80XX_TARGET_ID_PKT_BIST             (0x11U)
#define LAN80XX_TARGET_ID_MAC_FC_BUFFER        (0x0CU)
#define LAN80XX_TARGET_ID_HOST_MAC             (0x0DU)
#define LAN80XX_TARGET_ID_LINE_SLICE           (0x12U)
#define LAN80XX_TARGET_ID_HOST_PMA             (0x41U)
#define LAN80XX_TARGET_ID_HOST_PCS25G          (0x43U)
#define LAN80XX_TARGET_ID_HOST_RS_FEC          (0x53U)
#define LAN80XX_TARGET_ID_HOST_PCS_CFG         (0x47U)
#define LAN80XX_TARGET_ID_HOST_KR              (0x48U)
#define LAN80XX_TARGET_ID_HOST_INTR_CTRL       (0x49U)
#define LAN80XX_TARGET_ID_HOST_PMA_8BIT        (0x50U)
#define LAN80XX_TARGET_ID_HOST_SLICE           (0x52U)
#define LAN80XX_TARGET_ID_PTP_PROC             (0x62U)
#define LAN80XX_TARGET_ID_PTP_ANA0_INGR_CFG    (0x64U)
#define LAN80XX_TARGET_ID_PTP_ANA0_EGR_CFG     (0x65U)
#define LAN80XX_TARGET_ID_PTP_ANA1_INGR_CFG    (0x66U)
#define LAN80XX_TARGET_ID_PTP_ANA1_EGR_CFG     (0x67U)
#define LAN80XX_TARGET_ID_PTP_ANA2_INGR_CFG    (0x68U)
#define LAN80XX_TARGET_ID_PTP_ANA2_EGR_CFG     (0x69U)
#define LAN80XX_TARGET_ID_MACSEC_INGR          (0x0AU)
#define LAN80XX_TARGET_ID_MACSEC_INGR_CORE     (0xAAU)
#define LAN80XX_TARGET_ID_MACSEC_EGR           (0x0BU)
#define LAN80XX_TARGET_ID_MACSEC_EGR_CORE      (0xBBU)
#define LAN80XX_TARGET_ID_PTP_LTC              (0x60U)
#define LAN80XX_TARGET_ID_PTP_STI              (0x63U)
#define LAN80XX_TARGET_ID_GLOBAL               (0x61U)
#define LAN80XX_TARGET_ID_CROSS_CONNECT        (0x6DU)
#define LAN80XX_TARGET_ID_GPIO_CTRL            (0x6EU)
#define LAN80XX_TARGET_ID_CLK_CFG              (0x70U)
#define LAN80XX_TARGET_ID_MCU_MAILBOX          (0x1EU)
#define LAN80XX_TARGET_ID_MCU_IO_MNGT_MISC     (0x7EU)


/* Register Address */
#define LAN80XX_CMU_FF_REGISTER_ADDRESS                     (0xF0FFU)
#define LAN80XX_PMA_CMU_GRP_START_ADDR                      (0xF000U)
#define LAN80XX_PMA_CMU_GRP_END_ADDR                        (0xF0C0U)
#define LAN80XX_PMA_LANE_GRP_START_ADDR                     (0xF100U)
#define LAN80XX_PMA_LANE_GRP_END_ADDR                       (0xF1E4U)
#define LAN80XX_LINE_PMA_PMA_STD_END_ADDR                   (0x000FU)
#define LAN80XX_LINE_PMA_PMA_VENDOR_START_ADDR              (0x8000U)
#define LAN80XX_LINE_PMA_PMA_VENDOR_END_ADDR                (0x80FFU)
#define LAN80XX_LINE_KR_KR_STD_START_ADDR                   (0x0090U)
#define LAN80XX_LINE_KR_KR_STD_END_ADDR                     (0x009FU)
#define LAN80XX_LINE_KR_KR_VENDOR_START_ADDR                (0x9100U)
#define LAN80XX_LINE_KR_KR_VENDOR_END_ADDR                  (0x91FFU)
#define LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_START_ADDR      (0x00A0U)
#define LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_END_ADDR        (0x00AFU)
#define LAN80XX_LINE_PCS_CFG_FEC_VENDOR_START_ADDR          (0xE000U)
#define LAN80XX_LINE_PCS_CFG_FEC_VENDOR_END_ADDR            (0xE0FFU)
#define LAN80XX_LINE_RS_FEC_RS_FEC_STD_START_ADDR           (0x00C0U)
#define LAN80XX_LINE_RS_FEC_RS_FEC_STD_END_ADDR             (0x00DFU)
#define LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_START_ADDR        (0x8200U)
#define LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_END_ADDR          (0x82FFU)
#define LAN80XX_LINE_SLICE_START_ADDR                       (0x8100U)
#define LAN80XX_LINE_SLICE_END_ADDR                         (0x81FFU)
#define LAN80XX_SFP_TWS_START_ADDR                          (0xC000U)
#define LAN80XX_SFP_TWS_END_ADDR                            (0xC00FU)
#define LAN80XX_LINE_INTR_CTRL_START_ADDR                   (0xC010U)
#define LAN80XX_LINE_INTR_CTRL_END_ADDR                     (0xC01FU)
#define LAN80XX_LINE_PMA_8BIT_START_ADDR                    (0xF000U)
#define LAN80XX_LINE_PMA_8BIT_END_ADDR                      (0xFFFFU)
#define LAN80XX_LINE_PCS25G_PCS_STD_START_ADDR              (0x0000U)
#define LAN80XX_LINE_PCS25G_PCS_STD_END_ADDR                (0x07FFU)
#define LAN80XX_LINE_PCS25G_PCS_VENDOR_START_ADDR           (0x8000U)
#define LAN80XX_LINE_PCS25G_PCS_VENDOR_END_ADDR             (0x8FFFU)
#define LAN80XX_LINE_PCS_CFG_START_ADDR                     (0xE000U)
#define LAN80XX_LINE_PCS_CFG_END_ADDR                       (0xE0FFU)
#define LAN80XX_MAC_FC_BUFFER_START_ADDR                    (0xF000U)
#define LAN80XX_MAC_FC_BUFFER_END_ADDR                      (0xF07FU)
#define LAN80XX_HOST_MAC_START_ADDR                         (0xF100U)
#define LAN80XX_HOST_MAC_END_ADDR                           (0xF1FFU)
#define LAN80XX_LINE_MAC_START_ADDR                         (0xF300U)
#define LAN80XX_LINE_MAC_END_ADDR                           (0xF3FFU)
#define LAN80XX_LINE_KR_ANEG_STD_START_ADDR                 (0x0000U)
#define LAN80XX_LINE_KR_ANEG_STD_END_ADDR                   (0x7FFFU)
#define LAN80XX_LINE_KR_ANEG_VENDOR_START_ADDR              (0x8000U)
#define LAN80XX_LINE_KR_ANEG_VENDOR_END_ADDR                (0xFFFFU)
#define LAN80XX_MACSEC_START_ADDR                           (0x0C40U)
#define LAN80XX_MACSEC_END_ADDR                             (0x0CFFU)
#define LAN80XX_MACSEC_CORE_START_ADDR                      (0x0000U)
#define LAN80XX_MACSEC_CORE_INTR_END_ADDR                   (0x0C3FU)
#define LAN80XX_MACSEC_CORE_INTR_START_ADDR                 (0x0D00U)
#define LAN80XX_MACSEC_CORE_END_ADDR                        (0x7FFFU)
#define LAN80XX_HOST_PMA_START_ADDR                         (0x8000U)
#define LAN80XX_HOST_PMA_END_ADDR                           (0x80FFU)
#define LAN80XX_HOST_KR_KR_STD_START_ADDR                   (0x0090U)
#define LAN80XX_HOST_KR_KR_STD_END_ADDR                     (0x009FU)
#define LAN80XX_HOST_KR_KR_VENDOR_START_ADDR                (0x9100U)
#define LAN80XX_HOST_KR_KR_VENDOR_END_ADDR                  (0x91FFU)
#define LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_START_ADDR      (0x00A0U)
#define LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_END_ADDR        (0x00AFU)
#define LAN80XX_HOST_PCS_CFG_FEC_VENDOR_START_ADDR          (0xE000U)
#define LAN80XX_HOST_PCS_CFG_FEC_VENDOR_END_ADDR            (0xE0FFU)
#define LAN80XX_HOST_RS_FEC_RS_FEC_STD_START_ADDR           (0x00C0U)
#define LAN80XX_HOST_RS_FEC_RS_FEC_STD_END_ADDR             (0x00DFU)
#define LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_START_ADDR        (0x8200U)
#define LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_END_ADDR          (0x82FFU)
#define LAN80XX_HOST_SLICE_START_ADDR                       (0x8100U)
#define LAN80XX_HOST_SLICE_END_ADDR                         (0x81FFU)
#define LAN80XX_HOST_INTR_CTRL_START_ADDR                   (0xC010U)
#define LAN80XX_HOST_INTR_CTRL_END_ADDR                     (0xC01FU)
#define LAN80XX_PKT_BIST_START_ADDR                         (0xE900U)
#define LAN80XX_PKT_BIST_END_ADDR                           (0xEAFFU)
#define LAN80XX_HOST_PMA_8BIT_START_ADDR                    (0xF000U)
#define LAN80XX_HOST_PMA_8BIT_END_ADDR                      (0xFFFFU)
#define LAN80XX_PTP_PROC_START_ADDR                         (0x9000U)
#define LAN80XX_PTP_PROC_END_ADDR                           (0x90FFU)
#define LAN80XX_PTP_ANA0_INGR_CFG_START_ADDR                (0xA000U)
#define LAN80XX_PTP_ANA0_INGR_CFG_END_ADDR                  (0xA3FFU)
#define LAN80XX_PTP_ANA0_EGR_CFG_START_ADDR                 (0xA800U)
#define LAN80XX_PTP_ANA0_EGR_CFG_END_ADDR                   (0xABFFU)
#define LAN80XX_PTP_ANA1_INGR_CFG_START_ADDR                (0xB000U)
#define LAN80XX_PTP_ANA1_INGR_CFG_END_ADDR                  (0xB3FFU)
#define LAN80XX_PTP_ANA1_EGR_CFG_START_ADDR                 (0xB800U)
#define LAN80XX_PTP_ANA1_EGR_CFG_END_ADDR                   (0xBBFFU)
#define LAN80XX_PTP_ANA2_INGR_CFG_START_ADDR                (0xC000U)
#define LAN80XX_PTP_ANA2_INGR_CFG_END_ADDR                  (0xC3FFU)
#define LAN80XX_PTP_ANA2_EGR_CFG_START_ADDR                 (0xC800U)
#define LAN80XX_PTP_ANA2_EGR_CFG_END_ADDR                   (0xCBFFU)
#define LAN80XX_HOST_PCS25G_PCS_STD_START_ADDR              (0x0000U)
#define LAN80XX_HOST_PCS25G_PCS_STD_END_ADDR                (0x7FFFU)
#define LAN80XX_HOST_PCS25G_PCS_VENDOR_START_ADDR           (0x8000U)
#define LAN80XX_HOST_PCS25G_PCS_VENDOR_END_ADDR             (0x8FFFU)
#define LAN80XX_HOST_PCS_CFG_START_ADDR                     (0xE000U)
#define LAN80XX_HOST_PCS_CFG_END_ADDR                       (0xE0FFU)
#define LAN80XX_HOST_KR2_ANEG_STD_START_ADDR                (0x0000U)
#define LAN80XX_HOST_KR2_ANEG_STD_END_ADDR                  (0x7FFFU)
#define LAN80XX_HOST_KR2_ANEG_VENDOR_START_ADDR             (0x8000U)
#define LAN80XX_HOST_KR2_ANEG_VENDOR_END_ADDR               (0xFFFFU)
#define LAN80XX_MCU_IO_MNGT_MISC_END_ADDR                   (0x01FFU)
#define LAN80XX_GLOBAL_START_ADDR                           (0x0200U)
#define LAN80XX_GLOBAL_END_ADDR                             (0x05FFU)
#define LAN80XX_CLK_CFG_START_ADDR                          (0x0600U)
#define LAN80XX_CLK_CFG_END_ADDR                            (0x06FFU)
#define LAN80XX_GLOBAL_FAST_RESET_START_ADDR                (0x8000U)
#define LAN80XX_GLOBAL_FAST_RESET_END_ADDR                  (0x800FU)
#define LAN80XX_PTP_LTC_START_ADDR                          (0xD000U)
#define LAN80XX_PTP_LTC_END_ADDR                            (0xD0FFU)
#define LAN80XX_PTP_STI_START_ADDR                          (0xD200U)
#define LAN80XX_PTP_STI_END_ADDR                            (0xD2FFU)
#define LAN80XX_MCU_MAILBOX_START_ADDR                      (0xD800U)
#define LAN80XX_MCU_MAILBOX_END_ADDR                        (0xDA02U)
#define LAN80XX_CROSS_CONNECT_START_ADDR                    (0xF100U)
#define LAN80XX_CROSS_CONNECT_END_ADDR                      (0xF17FU)
#define LAN80XX_GPIO_CTRL_START_ADDR                        (0xF200U)
#define LAN80XX_GPIO_CTRL_END_ADDR                          (0xF27FU)


#endif /* _MEPA_LAN80XX_REGS_COMMON_H_ */
