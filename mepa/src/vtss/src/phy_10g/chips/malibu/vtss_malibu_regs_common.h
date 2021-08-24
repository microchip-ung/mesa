// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_COMMON_H_
#define _VTSS_MALIBU_REGS_COMMON_H_


#ifndef VTSS_BITOPS_DEFINED
#ifdef __ASSEMBLER__
#define VTSS_BIT(x)                   (1 << (x))
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#else
#define VTSS_BIT(x)                   (1U << (x))
#define VTSS_BITMASK(x)               ((1U << (x)) - 1)
#endif
#define VTSS_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))
#define VTSS_ENCODE_BITFIELD(x,o,w)   (((x) & VTSS_BITMASK(w)) << (o))
#define VTSS_ENCODE_BITMASK(o,w)      (VTSS_BITMASK(w) << (o))
#define VTSS_BITOPS_DEFINED
#endif /* VTSS_BITOPS_DEFINED */

/* IO register access macro - must be defined for platform */
#ifdef notdef
/** 
 * @param dev  - device id
 * @param is32 - is register 32 bit
 * @param off  - subtarget offset
 */
#define VTSS_IOREG(dev, is32, off)      (...)
#endif

/* IO indexed register access macro - may be changed for platform */
#if !defined(VTSS_IOREG_IX)
/** 
 * @param dev  - device id
 * @param is32 - is register 32 bit
 * @param g    - group instance, 
 * @param gw   - group width
 * @param ro   - register offset, 
 * @param r    - register (instance) number
 */
#define VTSS_IOREG_IX(dev, is32, o, g, gw, r, ro)   VTSS_IOREG(dev, is32, o | (((g) * (gw)) + (ro) + (r)))
#endif

/* Target IDs */
#define VTSS_MALIBU_TARGET_LINE_PMA              0x01
#define VTSS_MALIBU_TARGET_LINE_KR_DEV1          0x07
#define VTSS_MALIBU_TARGET_SFP_TWS               0x0f
#define VTSS_MALIBU_TARGET_GPIO_INTR_CTRL        0x09
#define VTSS_MALIBU_TARGET_LINE_PMA_32BIT        0x10
#define VTSS_MALIBU_TARGET_HOST_PMA              0x41
#define VTSS_MALIBU_TARGET_HOST_KR_DEV1          0x47
#define VTSS_MALIBU_TARGET_HOST_PMA_32BIT        0x50
#define VTSS_MALIBU_TARGET_WIS                   0x02
#define VTSS_MALIBU_TARGET_LINE_PCS10G           0x03
#define VTSS_MALIBU_TARGET_HOST_PCS10G           0x43
#define VTSS_MALIBU_TARGET_HOST_PCS1G            0x05
#define VTSS_MALIBU_TARGET_LINE_PCS1G            0x06
#define VTSS_MALIBU_TARGET_MAC_FC_BUFFER         0x0c
#define VTSS_MALIBU_TARGET_HOST_MAC              0x0d
#define VTSS_MALIBU_TARGET_LINE_MAC              0x0e
#define VTSS_MALIBU_TARGET_FIFO_BIST             0x11
#define VTSS_MALIBU_TARGET_LINE_KR_DEV7          0x08
#define VTSS_MALIBU_TARGET_HOST_KR_DEV7          0x48
#define VTSS_MALIBU_TARGET_MACSEC_INGR           0x0a
#define VTSS_MALIBU_TARGET_MACSEC_EGR            0x0b
#define VTSS_MALIBU_TARGET_GLOBAL                0x61
#define VTSS_MALIBU_TARGET_CLK_CFG               0x70
#define VTSS_MALIBU_TARGET_GLOBAL_RESET          0xff
#define VTSS_MALIBU_TARGET_HOST_PLL5G            0x6b
#define VTSS_MALIBU_TARGET_LINE_PLL5G            0x6c
#define VTSS_MALIBU_TARGET_PTP_0                 0x62
#define VTSS_MALIBU_TARGET_PTP_1                 0x63
#define VTSS_MALIBU_TARGET_PTP_ANA0_INGR_CFG01   0x64
#define VTSS_MALIBU_TARGET_PTP_ANA0_EGR_CFG01    0x65
#define VTSS_MALIBU_TARGET_PTP_ANA1_INGR_CFG01   0x66
#define VTSS_MALIBU_TARGET_PTP_ANA1_EGR_CFG01    0x67
#define VTSS_MALIBU_TARGET_PTP_ANA2_INGR_CFG01   0x68
#define VTSS_MALIBU_TARGET_PTP_ANA2_EGR_CFG01    0x69
#define VTSS_MALIBU_TARGET_F2DF_DF2F_16BIT       0x6f
#define VTSS_MALIBU_TARGET_F2DF_DF2F_32BIT       0x6a
#define VTSS_MALIBU_TARGET_EXP                   0x6d
#define VTSS_MALIBU_TARGET_GPIO_CTRL             0x6e
#define VTSS_MALIBU_TARGET_PTP_2                 0x72
#define VTSS_MALIBU_TARGET_PTP_3                 0x73
#define VTSS_MALIBU_TARGET_PTP_ANA0_INGR_CFG23   0x74
#define VTSS_MALIBU_TARGET_PTP_ANA0_EGR_CFG23    0x75
#define VTSS_MALIBU_TARGET_PTP_ANA1_INGR_CFG23   0x76
#define VTSS_MALIBU_TARGET_PTP_ANA1_EGR_CFG23    0x77
#define VTSS_MALIBU_TARGET_PTP_ANA2_INGR_CFG23   0x78
#define VTSS_MALIBU_TARGET_PTP_ANA2_EGR_CFG23    0x79

#endif /* _VTSS_MALIBU_REGS_COMMON_H_ */
