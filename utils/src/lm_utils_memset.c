/*
 * Copyright (c) 2013-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// NOTE: The original version of this file is imported from
// URL: https://github.com/ARM-software/arm-trusted-firmware
// VERSION: v2.8.0 (9881bb93a3bc0a3ea37e9f093e09ab4b360a9e48)
// File: arm-trusted-firmware/lib/libc/memset.c

#include <lm_utils_memset.h>
#if defined(LMU_OS_LINUX)
#include <string.h>
#endif

void *lmu_memset_no_asm(void *dst, int val, size_t count)
{
    uint8_t  *ptr = dst;
    uint64_t *ptr64;
    uint64_t  fill = (unsigned char)val;

    /* Simplify code below by making sure we write at least one byte. */
    if (count == 0U) {
        return dst;
    }

    /* Handle the first part, until the pointer becomes 64-bit aligned. */
    while (((uintptr_t)ptr & 7U) != 0U) {
        *ptr = (uint8_t)val;
        ptr++;
        if (--count == 0U) {
            return dst;
        }
    }

    /* Duplicate the fill byte to the rest of the 64-bit word. */
    fill |= fill << 8U;
    fill |= fill << 16U;
    fill |= fill << 32U;

/* Use 64-bit writes for as long as possible. */
#pragma coverity compliance deviate                                            \
    "MISRA C-2023 Rule 11.3"                                                   \
    "Guarnteed to be alligned by the code above!"
    ptr64 = (uint64_t *)ptr;
    for (; count >= 8U; count -= 8U) {
        *ptr64 = fill;
        ptr64++;
    }

    /* Handle the remaining part byte-per-byte. */
    ptr = (uint8_t *)ptr64;
    while (count-- > 0U) {
        *ptr = (uint8_t)val;
        ptr++;
    }

    return dst;
}

void *lmu_memset_(void *dst, int val, size_t count)
{
#if defined(LMU_OS_LINUX)
    return memset(dst, val, count);
#else
#if defined(__arm__)
    return lmu_memset_arm(dst, val, count);
#elif defined(__aarch64__)
    return lmu_memset_aarch64(dst, val, count);
#else
    return lmu_memset_no_asm(dst, val, count);
#endif
#endif
}

void lmu_memset(void *dst, int val, size_t count)
{
    (void)lmu_memset_(dst, val, count);
}
