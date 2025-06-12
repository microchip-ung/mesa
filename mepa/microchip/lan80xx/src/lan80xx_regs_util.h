// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_LAN80XX_REGS_COMMON_H_
#define _MEPA_LAN80XX_REGS_COMMON_H_

#define LAN80XX_BIT(x)                   (1U << (x))
#define LAN80XX_BITMASK(x)               ((1U << (x)) - 1)
#define LAN80XX_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & LAN80XX_BITMASK(w))
#define LAN80XX_ENCODE_BITFIELD(x,o,w)   (((x) & LAN80XX_BITMASK(w)) << (o))
#define LAN80XX_ENCODE_BITMASK(o,w)      (LAN80XX_BITMASK(w) << (o))

#define LAN80XX_8_BIT_SHIFT     8
#define LAN80XX_4_BIT_SHIFT     4
#define LAN80XX_16_BIT_SHIFT    16
#define LAN80XX_12_BIT_SHIFT    12
#define LAN80XX_24_BIT_SHIFT    24
#define LAN80XX_32_BIT_SHIFT    32
#define LAN80XX_BYTE_MASK       0xFF
#define LAN80XX_WORD_MASK       0xF
#define LAN80XX_WORD(msb, lsb)  ((msb << 8) | lsb)
#define LAN80XX_MASK_THIRD_BYTE  0xFF0000
#define LAN80XX_32BIT_REG_MASK   0xFFFFFFFF

#define LAN80XX_HOST_LINE_REG(front,h_l,back) (h_l ? front##_LINE_##back : front##_HOST_##back)
#define LAN80XX_LINE_HOST_MAC_REG_EXPAN(front, is_host, back) (is_host ? front##_HOST_MAC_HOST_MAC_##back : front##_LINE_MAC_LINE_MAC_##back)
#define LAN80XX_HOST_LINE_INTR_REG(front, h_l, back) (h_l ? front##_LINE_INTR_CTRL_LINE_##back : front##_HOST_INTR_CTRL_HOST_##back)


#define VTSS_IO_OFFSET0(x) (x)

/*
 * @param dev  - device id
 * @param is32 - is register 32 bit
 * @param off  - subtarget offset
 */
#define LAN80XX_IOREG(mmd, is32, off)      _lan80xx_ioreg(&data->io_var, (mmd), (is32), (off))


/******************** DEVICE ID(MMD ID) ****************************/

#define MMD_ID_LINE_KR            0x7          /* Device ID for Line KR */
#define MMD_ID_HOST_KR            0xF          /* Device ID for Host KR */
#define MMD_ID_LINE_PCS_CFG       0x3          /* Device ID for LINE PCS CFG */
#define MMD_ID_LINE_PCS_CFG_1G    0x1          /* Device ID for LINE PCS CFG for 1G*/
#define MMD_ID_HOST_PCS_CFG       0xB          /* Device ID for HOST PCS CFG */
#define MMD_ID_HOST_PCS_CFG_1G    0x9          /* Device ID for HOST PCS CFG for 1G */
#define MMD_ID_LINE_PCS25G        0x3          /* Device ID for LINE PCS25G */
#define MMD_ID_HOST_PCS25G        0xB          /* Device ID for HOST PCS25G */
#define MMD_ID_LINE_PMA_8BIT      0x1          /* Device ID for LINE PMA */
#define MMD_ID_HOST_PMA_8BIT      0x9          /* Device ID for LINE PMA */
#define MMD_ID_LINE_PMA           0x1          /* Device ID for Line PMA */
#define MMD_ID_LINE_PMA_EXT       0x1          /* Device ID for Line PMA EXT*/
#define MMD_ID_HOST_PMA           0x9          /* Device ID for Host PMA */
#define MMD_ID_LINE_MAC           0x3          /* Device ID for LINE MAC  */
#define MMD_ID_HOST_MAC           0x3          /* Device ID for HOST MAC */
#define MMD_ID_LINE_SLICE         0x1          /* Device ID for LINE SLICE  */
#define MMD_ID_HOST_SLICE         0x9          /* Device ID for HOST SLICE */
#define MMD_ID_CROSS_CONN         0x1E         /* Device ID for CROSS CONNECT */
#define MMD_ID_MAC_FC_BUFF        0x3          /* Device ID for MAC_FC_BUFFER */
#define MMD_ID_MCU_IO_MISC        0x1E         /* Device ID for MCU_IO_MISC */
#define MMD_ID_GLOBAL_REGISTERS   0x1E         /* Device ID for Global Register */
#define MMD_ID_LINE_INTR_CTL      0x1          /* Device ID for Line Interrupt Control */
#define MMD_ID_HOST_INTR_CTL      0x9          /* Device ID for Host Interrupt Control */
#define MMD_ID_GPIO_CTRL          0x1E         /* Device ID for GPIO Control */
#define MMD_ID_PKT_BIST           0x09         /* Device ID for PKT Gen/Mon Conf */
#define MMD_ID_SFP_TWS            0x01         /* Device ID for SFP TWS */
#define MMD_ID_HOST_RSFEC         0x09
#define MMD_ID_LINE_RSFEC         0x01
#define MMD_ID_CLK_CFG            0x1E
/* MMD Address related to 1588*/
#define MMD_ID_PTP_BLOCK          0xA
#define MMD_ID_PTP_LTC            0x1E
// This is for ANAx_EGR and ANAx_INGR
#define MMD_ID_PTP_ANAx           0xA
// This is MACSEC related
#define MMD_ID_MACSEC_INGR        0x8
#define MMD_ID_MACSEC_EGR         0x1F
// MAILBOX
#define MMD_ID_MCU_MAILBOX        0x1E
#define MMD_ID_MCU_IO_MNGT_MISC   0x1E

/* Register Target Id */
#define LAN80XX_TARGET_ID_LINE_PMA             0x01
#define LAN80XX_TARGET_ID_LINE_PCS25G          0x03
#define LAN80XX_TARGET_ID_LINE_RS_FEC          0x13
#define LAN80XX_TARGET_ID_LINE_PCS_CFG         0x07
#define LAN80XX_TARGET_ID_LINE_KR              0x08
#define LAN80XX_TARGET_ID_LINE_INTR_CTRL       0x09
#define LAN80XX_TARGET_ID_LINE_MAC             0x0E
#define LAN80XX_TARGET_ID_SFP_TWS              0x0F
#define LAN80XX_TARGET_ID_LINE_PMA_8BIT        0x10
#define LAN80XX_TARGET_ID_PKT_BIST             0x11
#define LAN80XX_TARGET_ID_MAC_FC_BUFFER        0x0C
#define LAN80XX_TARGET_ID_HOST_MAC             0x0D
#define LAN80XX_TARGET_ID_LINE_SLICE           0x12
#define LAN80XX_TARGET_ID_HOST_PMA             0x41
#define LAN80XX_TARGET_ID_HOST_PCS25G          0x43
#define LAN80XX_TARGET_ID_HOST_RS_FEC          0x53
#define LAN80XX_TARGET_ID_HOST_PCS_CFG         0x47
#define LAN80XX_TARGET_ID_HOST_KR              0x48
#define LAN80XX_TARGET_ID_HOST_INTR_CTRL       0x49
#define LAN80XX_TARGET_ID_HOST_PMA_8BIT        0x50
#define LAN80XX_TARGET_ID_HOST_SLICE           0x52
#define LAN80XX_TARGET_ID_PTP_PROC             0x62
#define LAN80XX_TARGET_ID_PTP_ANA0_INGR_CFG    0x64
#define LAN80XX_TARGET_ID_PTP_ANA0_EGR_CFG     0x65
#define LAN80XX_TARGET_ID_PTP_ANA1_INGR_CFG    0x66
#define LAN80XX_TARGET_ID_PTP_ANA1_EGR_CFG     0x67
#define LAN80XX_TARGET_ID_PTP_ANA2_INGR_CFG    0x68
#define LAN80XX_TARGET_ID_PTP_ANA2_EGR_CFG     0x69
#define LAN80XX_TARGET_ID_MACSEC_INGR          0x0A
#define LAN80XX_TARGET_ID_MACSEC_INGR_CORE     0xAA
#define LAN80XX_TARGET_ID_MACSEC_EGR           0x0B
#define LAN80XX_TARGET_ID_MACSEC_EGR_CORE      0xBB
#define LAN80XX_TARGET_ID_PTP_LTC              0x60
#define LAN80XX_TARGET_ID_PTP_STI              0x63
#define LAN80XX_TARGET_ID_GLOBAL               0x61
#define LAN80XX_TARGET_ID_CROSS_CONNECT        0x6D
#define LAN80XX_TARGET_ID_GPIO_CTRL            0x6E
#define LAN80XX_TARGET_ID_CLK_CFG              0x70
#define LAN80XX_TARGET_ID_MCU_MAILBOX          0x1E
#define LAN80XX_TARGET_ID_MCU_IO_MNGT_MISC     0x7E


/* Register Address */
#define LAN80XX_CMU_FF_REGISTER_ADDRESS                     0xF0FF
#define LAN80XX_PMA_CMU_GRP_START_ADDR                      0xF000
#define LAN80XX_PMA_CMU_GRP_END_ADDR                        0xF0C0
#define LAN80XX_PMA_LANE_GRP_START_ADDR                     0xF100
#define LAN80XX_PMA_LANE_GRP_END_ADDR                       0xF1E4
#define LAN80XX_LINE_PMA_PMA_STD_END_ADDR                   0x000F
#define LAN80XX_LINE_PMA_PMA_VENDOR_START_ADDR              0x8000
#define LAN80XX_LINE_PMA_PMA_VENDOR_END_ADDR                0x80FF
#define LAN80XX_LINE_KR_KR_STD_START_ADDR                   0x0090
#define LAN80XX_LINE_KR_KR_STD_END_ADDR                     0x009F
#define LAN80XX_LINE_KR_KR_VENDOR_START_ADDR                0x9100
#define LAN80XX_LINE_KR_KR_VENDOR_END_ADDR                  0x91FF
#define LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_START_ADDR      0x00A0
#define LAN80XX_LINE_PCS_CFG_BASE_R_FEC_STD_END_ADDR        0x00AF
#define LAN80XX_LINE_PCS_CFG_FEC_VENDOR_START_ADDR          0xE000
#define LAN80XX_LINE_PCS_CFG_FEC_VENDOR_END_ADDR            0xE0FF
#define LAN80XX_LINE_RS_FEC_RS_FEC_STD_START_ADDR           0x00C0
#define LAN80XX_LINE_RS_FEC_RS_FEC_STD_END_ADDR             0x00DF
#define LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_START_ADDR        0x8200
#define LAN80XX_LINE_RS_FEC_RS_FEC_VENDOR_END_ADDR          0x82FF
#define LAN80XX_LINE_SLICE_START_ADDR                       0x8100
#define LAN80XX_LINE_SLICE_END_ADDR                         0x81FF
#define LAN80XX_SFP_TWS_START_ADDR                          0xC000
#define LAN80XX_SFP_TWS_END_ADDR                            0xC00F
#define LAN80XX_LINE_INTR_CTRL_START_ADDR                   0xC010
#define LAN80XX_LINE_INTR_CTRL_END_ADDR                     0xC01F
#define LAN80XX_LINE_PMA_8BIT_START_ADDR                    0xF000
#define LAN80XX_LINE_PMA_8BIT_END_ADDR                      0xFFFF
#define LAN80XX_LINE_PCS25G_PCS_STD_START_ADDR              0x0000
#define LAN80XX_LINE_PCS25G_PCS_STD_END_ADDR                0x07FF
#define LAN80XX_LINE_PCS25G_PCS_VENDOR_START_ADDR           0x8000
#define LAN80XX_LINE_PCS25G_PCS_VENDOR_END_ADDR             0x8FFF
#define LAN80XX_LINE_PCS_CFG_START_ADDR                     0xE000
#define LAN80XX_LINE_PCS_CFG_END_ADDR                       0xE0FF
#define LAN80XX_MAC_FC_BUFFER_START_ADDR                    0xF000
#define LAN80XX_MAC_FC_BUFFER_END_ADDR                      0xF07F
#define LAN80XX_HOST_MAC_START_ADDR                         0xF100
#define LAN80XX_HOST_MAC_END_ADDR                           0xF1FF
#define LAN80XX_LINE_MAC_START_ADDR                         0xF300
#define LAN80XX_LINE_MAC_END_ADDR                           0xF3FF
#define LAN80XX_LINE_KR_ANEG_STD_START_ADDR                 0x0000
#define LAN80XX_LINE_KR_ANEG_STD_END_ADDR               0x7FFF
#define LAN80XX_LINE_KR_ANEG_VENDOR_START_ADDR              0x8000
#define LAN80XX_LINE_KR_ANEG_VENDOR_END_ADDR                0xFFFF
#define LAN80XX_MACSEC_START_ADDR                           0x0C40
#define LAN80XX_MACSEC_END_ADDR                             0x0CFF
#define LAN80XX_MACSEC_CORE_START_ADDR                      0x0000
#define LAN80XX_MACSEC_CORE_INTR_END_ADDR                   0x0C3F
#define LAN80XX_MACSEC_CORE_INTR_START_ADDR                 0x0D00
#define LAN80XX_MACSEC_CORE_END_ADDR                        0x7FFF
#define LAN80XX_HOST_PMA_START_ADDR                         0x8000
#define LAN80XX_HOST_PMA_END_ADDR                           0x80FF
#define LAN80XX_HOST_KR_KR_STD_START_ADDR                   0x0090
#define LAN80XX_HOST_KR_KR_STD_END_ADDR                     0x009F
#define LAN80XX_HOST_KR_KR_VENDOR_START_ADDR                0x9100
#define LAN80XX_HOST_KR_KR_VENDOR_END_ADDR                  0x91FF
#define LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_START_ADDR      0x00A0
#define LAN80XX_HOST_PCS_CFG_BASE_R_FEC_STD_END_ADDR        0x00AF
#define LAN80XX_HOST_PCS_CFG_FEC_VENDOR_START_ADDR          0xE000
#define LAN80XX_HOST_PCS_CFG_FEC_VENDOR_END_ADDR            0xE0FF
#define LAN80XX_HOST_RS_FEC_RS_FEC_STD_START_ADDR           0x00C0
#define LAN80XX_HOST_RS_FEC_RS_FEC_STD_END_ADDR             0x00DF
#define LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_START_ADDR        0x8200
#define LAN80XX_HOST_RS_FEC_RS_FEC_VENDOR_END_ADDR          0x82FF
#define LAN80XX_HOST_SLICE_START_ADDR                       0x8100
#define LAN80XX_HOST_SLICE_END_ADDR                         0x81FF
#define LAN80XX_HOST_INTR_CTRL_START_ADDR                   0xC010
#define LAN80XX_HOST_INTR_CTRL_END_ADDR                     0xC01F
#define LAN80XX_PKT_BIST_START_ADDR                         0xE900
#define LAN80XX_PKT_BIST_END_ADDR                           0xEAFF
#define LAN80XX_HOST_PMA_8BIT_START_ADDR                    0xF000
#define LAN80XX_HOST_PMA_8BIT_END_ADDR                      0xFFFF
#define LAN80XX_PTP_PROC_START_ADDR                         0x9000
#define LAN80XX_PTP_PROC_END_ADDR                           0x90FF
#define LAN80XX_PTP_ANA0_INGR_CFG_START_ADDR                0xA000
#define LAN80XX_PTP_ANA0_INGR_CFG_END_ADDR                  0xA3FF
#define LAN80XX_PTP_ANA0_EGR_CFG_START_ADDR                 0xA800
#define LAN80XX_PTP_ANA0_EGR_CFG_END_ADDR                   0xABFF
#define LAN80XX_PTP_ANA1_INGR_CFG_START_ADDR                0xB000
#define LAN80XX_PTP_ANA1_INGR_CFG_END_ADDR                  0xB3FF
#define LAN80XX_PTP_ANA1_EGR_CFG_START_ADDR                 0xB800
#define LAN80XX_PTP_ANA1_EGR_CFG_END_ADDR                   0xBBFF
#define LAN80XX_PTP_ANA2_INGR_CFG_START_ADDR                0xC000
#define LAN80XX_PTP_ANA2_INGR_CFG_END_ADDR                  0xC3FF
#define LAN80XX_PTP_ANA2_EGR_CFG_START_ADDR                 0xC800
#define LAN80XX_PTP_ANA2_EGR_CFG_END_ADDR                   0xCBFF
#define LAN80XX_HOST_PCS25G_PCS_STD_START_ADDR              0x0000
#define LAN80XX_HOST_PCS25G_PCS_STD_END_ADDR                0x7FFF
#define LAN80XX_HOST_PCS25G_PCS_VENDOR_START_ADDR           0x8000
#define LAN80XX_HOST_PCS25G_PCS_VENDOR_END_ADDR             0x8FFF
#define LAN80XX_HOST_PCS_CFG_START_ADDR                     0xE000
#define LAN80XX_HOST_PCS_CFG_END_ADDR                       0xE0FF
#define LAN80XX_HOST_KR2_ANEG_STD_START_ADDR                0x0000
#define LAN80XX_HOST_KR2_ANEG_STD_END_ADDR                  0x7FFF
#define LAN80XX_HOST_KR2_ANEG_VENDOR_START_ADDR             0x8000
#define LAN80XX_HOST_KR2_ANEG_VENDOR_END_ADDR               0xFFFF
#define LAN80XX_MCU_IO_MNGT_MISC_END_ADDR                   0x01FF
#define LAN80XX_GLOBAL_START_ADDR                           0x0200
#define LAN80XX_GLOBAL_END_ADDR                             0x05FF
#define LAN80XX_CLK_CFG_START_ADDR                          0x0600
#define LAN80XX_CLK_CFG_END_ADDR                            0x06FF
#define LAN80XX_GLOBAL_FAST_RESET_START_ADDR                0x8000
#define LAN80XX_GLOBAL_FAST_RESET_END_ADDR                  0x800F
#define LAN80XX_PTP_LTC_START_ADDR                          0xD000
#define LAN80XX_PTP_LTC_END_ADDR                            0xD0FF
#define LAN80XX_PTP_STI_START_ADDR                          0xD200
#define LAN80XX_PTP_STI_END_ADDR                            0xD2FF
#define LAN80XX_MCU_MAILBOX_START_ADDR                      0xD800
#define LAN80XX_MCU_MAILBOX_END_ADDR                        0xDA02
#define LAN80XX_CROSS_CONNECT_START_ADDR                    0xF100
#define LAN80XX_CROSS_CONNECT_END_ADDR                      0xF17F
#define LAN80XX_GPIO_CTRL_START_ADDR                        0xF200
#define LAN80XX_GPIO_CTRL_END_ADDR                          0xF27F


#endif /* _MEPA_LAN80XX_REGS_COMMON_H_ */
