// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_COMMON_H_
#define _VTSS_VENICE_REGS_COMMON_H_


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
#define VTSS_IOREG_IX(dev, is32, o, g, gw, r, ro)   VTSS_IOREG(dev, is32, (o) + (((g) * (gw)) + (ro) + (r)))
#endif

/* Target IDs */
#define VTSS_VENICE_TARGET_VENICE_DEV1           0x01
#define VTSS_VENICE_TARGET_VENICE_KR_DEV1        0x07
#define VTSS_VENICE_TARGET_SFP_I2C               0x0f
#define VTSS_VENICE_TARGET_VENICE_DEV1_32        0x10
#define VTSS_VENICE_TARGET_VENICE_WIS            0x02
#define VTSS_VENICE_TARGET_VENICE_PCS            0x03
#define VTSS_VENICE_TARGET_PCS1G_HOST            0x05
#define VTSS_VENICE_TARGET_PCS1G_LINE            0x06
#define VTSS_VENICE_TARGET_FC_BUFFER             0x0c
#define VTSS_VENICE_TARGET_HOST_MAC              0x0d
#define VTSS_VENICE_TARGET_LINE_MAC              0x0e
#define VTSS_VENICE_TARGET_VENICE_DEV4           0x09
#define VTSS_VENICE_TARGET_FIFO_BIST             0x11
#define VTSS_VENICE_TARGET_PCS_XAUI              0x04
#define VTSS_VENICE_TARGET_VENICE_KR_DEV7        0x08
#define VTSS_VENICE_TARGET_MACSEC_INGR           0x0a
#define VTSS_VENICE_TARGET_MACSEC_EGR            0x0b
#define VTSS_VENICE_TARGET_VENICE_GLOBAL         0x61
#define VTSS_VENICE_TARGET_GLOBAL_FAST_RESET     0xff
#define VTSS_VENICE_TARGET_HOST_PLL5G            0x6b
#define VTSS_VENICE_TARGET_LINE_PLL5G            0x6c
#define VTSS_VENICE_TARGET_PTP_0                 0x62
#define VTSS_VENICE_TARGET_PTP_1                 0x63
#define VTSS_VENICE_TARGET_PTP_ANA0_INGR_CFG     0x64
#define VTSS_VENICE_TARGET_PTP_ANA0_EGR_CFG      0x65
#define VTSS_VENICE_TARGET_PTP_ANA1_INGR_CFG     0x66
#define VTSS_VENICE_TARGET_PTP_ANA1_EGR_CFG      0x67
#define VTSS_VENICE_TARGET_PTP_ANA2_INGR_CFG     0x68
#define VTSS_VENICE_TARGET_PTP_ANA2_EGR_CFG      0x69
#define VTSS_VENICE_TARGET_VENICE_GLOBAL32       0x6a

#endif /* _VTSS_VENICE_REGS_COMMON_H_ */
