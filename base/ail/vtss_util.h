// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef VTSS_UTIL_H
#define VTSS_UTIL_H

#include "vtss_api.h"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

/* Round x divided by y to nearest integer. x and y are integers */
#define VTSS_ROUNDING_DIVISION(x, y) (((x) + ((y) / 2)) / (y))

/* Round x divided by y to nearest higher integer. x and y are integers */
#define VTSS_DIV_ROUND_UP(x, y)   (((x) + (y) - 1) / (y))
#define VTSS_DIV64_ROUND_UP(x, y) (VTSS_DIV64(((x) + (y) - 1), (y)))

#ifndef VTSS_BITOPS_DEFINED
#ifdef __ASSEMBLER__
#define VTSS_BIT(x)     (1 << (x))
#define VTSS_BITMASK(x) ((1 << (x)) - 1)
#else
#define VTSS_BIT(x)     ((u32)1U << (x))
#define VTSS_BITMASK(x) (((u32)1U << (x)) - 1U)
#endif
#define VTSS_EXTRACT_BITFIELD(x, o, w) (((x) >> (o)) & VTSS_BITMASK(w))
#define VTSS_ENCODE_BITFIELD(x, o, w)  (((u32)(x) & VTSS_BITMASK(w)) << (o))
#define VTSS_ENCODE_BITMASK(o, w)      (VTSS_BITMASK(w) << (o))
#define VTSS_BITOPS_DEFINED
#endif /* VTSS_BITOPS_DEFINED */

u8   vtss_bs_bit_get(const void *vptr, u32 offset);
void vtss_bs_bit_set(void *vptr, u32 offset, u8 value);
void vtss_bs_set(void *vptr, u32 offset, u32 len, u32 value);
u32  vtss_bs_get(const void *vptr, u32 offset, u32 len);

u8   vtss_bool8_to_u8(BOOL *array);
void vtss_u8_to_bool8(u8 value, BOOL *array);

#endif /* VTSS_UTIL_H */
