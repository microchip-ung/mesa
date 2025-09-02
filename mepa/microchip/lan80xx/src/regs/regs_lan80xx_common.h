// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN80XX_MALIBU25G_REGS_COMMON_H_
#define LAN80XX_MALIBU25G_REGS_COMMON_H_


#include <stdint.h>
#define LAN80XX_EXTRACT_BITFIELD(x,o,w)                                                             (((x) >> (o)) & LAN80XX_BITMASK(w))
#define LAN80XX_ENCODE_BITFIELD(x,o,w)                                                              (((x) & LAN80XX_BITMASK(w)) << (o))
#define LAN80XX_ENCODE_BITMASK(o,w)                                                                 (LAN80XX_BITMASK(w) << (o))
#define LAN80XX_BITOPS_DEFINED

#define LAN80XX_IOREG_IX(t,o,g,gw,r,ro)                                                             ((o) + ((g) * (gw)) + (ro) + (r))

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

#endif
