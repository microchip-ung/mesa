// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <lm_utils.h>
#if defined(LMU_OS_LINUX)
#include <string.h>
#endif

void *lmu_memmove_no_asm(void *dst, const void *src, size_t n)
{
    uint8_t       *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    if (s < d) {
        s += n;
        d += n;
        while ((n--) != 0U) {
            *--d = *--s;
        }
    } else {
        while ((n--) != 0U) {
            *d++ = *s++;
        }
    }

    return dst;
}

void *lmu_memmove_(void *dst, const void *src, size_t n)
{
#if defined(LMU_OS_LINUX)
    return memmove(dst, src, n);
#else
#if defined(__aarch64__)
    return lmu_memmove_aarch64(dst, src, n);
#else
    return lmu_memmove_no_asm(dst, src, n);
#endif
#endif
}

void lmu_memmove(void *dst, const void *src, size_t n)
{
    (void)lmu_memmove_(dst, src, n);
}
