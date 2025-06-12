// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU25G_REGS_COMMON_H_
#define _VTSS_MALIBU25G_REGS_COMMON_H_


#include <stdint.h>
#ifndef VTSS_BITOPS_DEFINED
#ifdef __ASSEMBLER__
#define VTSS_BIT(x)                   (1 << (x))
#define VTSS_BITMASK(x)               ((1 << (x)) - 1)
#else
#define VTSS_BIT(x)                   (1U << (x))
#define VTSS_BITMASK(x)               ((1U << (x)) - 1)
#define LAN80XX_BIT(x)                   (1U << (x))
#define LAN80XX_BITMASK(x)               ((1U << (x)) - 1)
#endif
#define VTSS_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & VTSS_BITMASK(w))
#define VTSS_ENCODE_BITFIELD(x,o,w)   (((x) & VTSS_BITMASK(w)) << (o))
#define VTSS_ENCODE_BITMASK(o,w)      (VTSS_BITMASK(w) << (o))

#define LAN80XX_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & LAN80XX_BITMASK(w))
#define LAN80XX_ENCODE_BITFIELD(x,o,w)   (((x) & LAN80XX_BITMASK(w)) << (o))
#define LAN80XX_ENCODE_BITMASK(o,w)      (LAN80XX_BITMASK(w) << (o))

#define VTSS_BITOPS_DEFINED

#define LAN80XX_EXTRACT_BITFIELD(x,o,w)  (((x) >> (o)) & LAN80XX_BITMASK(w))
#define LAN80XX_ENCODE_BITFIELD(x,o,w)   (((x) & LAN80XX_BITMASK(w)) << (o))
#define LAN80XX_ENCODE_BITMASK(o,w)      (LAN80XX_BITMASK(w) << (o))
#define LAN80XX_BITOPS_DEFINED

#endif /* VTSS_BITOPS_DEFINED */

#define VTSS_TO_PTP_PROC        VTSS_IO_OFFSET0(0x00000000) /*!< Base offset for target PTP_PROC */

/* IO address mapping macro - may be changed for platform */
#if !defined(VTSS_IOADDR)
#define VTSS_IOADDR(t,o)        ((t) + (o))
#endif

#if !defined(VTSS_IOADDR_IX)
#define VTSS_IOADDR_IX(t,o,g,gw,r,ro)     ((t) + (((o) + ((g) * (gw)) + (ro) + (r)) << 2))
#endif

/* IO register access macro - may be changed for platform */
#if !defined(VTSS_IOREG)
/**
 * @param t - target base offset
 * @param o - subtarget offset
 */
//#define VTSS_IOREG(t,o)      (*((volatile uint32_t*)(VTSS_IOADDR(t,o))))
#define VTSS_IOREG(t,o)        (VTSS_IOADDR(t,o))
#endif

/* IO indexed register access macro - may be changed for platform */
#if !defined(VTSS_IOREG_IX)
/**
 * @param t  - target base offset
 * @param o  - subtarget offset
 * @param g  - group instance,
 * @param gw - group width
 * @param ro - register offset,
 * @param r  - register (instance) number
 */
#define VTSS_IOREG_IX(t,o,g,gw,r,ro)   VTSS_IOREG(t,(o) + ((g) * (gw)) + (ro) + (r))
#define LAN80XX_IOREG_IX(t,o,g,gw,r,ro)   ((o) + ((g) * (gw)) + (ro) + (r))
#endif

/* Structures Used for Register Dumps */
typedef struct {
    char *str;   /* Register Name */
    u32  addr;   /* Register Address */
} phy25g_reg_dump_t;

typedef struct {
    char  *str;
    u32   base_addr;  /* Base Address of the Group */
    u8    grp_start;
    u8    grp_end;
} phy25g_pma_reg_dump_t;


#endif /* _VTSS_MALIBU25G_REGS_COMMON_H_ */
