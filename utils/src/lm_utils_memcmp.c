// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <lm_utils_memcmp.h>
#if defined(LMU_OS_LINUX)
#include <string.h>
#endif

int lmu_memcmp_no_asm(const void *s1, const void *s2, size_t n)
{
    const uint8_t *a = (const uint8_t *)s1;
    const uint8_t *b = (const uint8_t *)s2;

    if (a == b) {
        return 0;
    }

    while ((n--) != 0U) {
        if (*a < *b) {
            return -1;
        }

        if (*a > *b) {
            return 1;
        }

        a++;
        b++;
    }

    return 0;
}

int lmu_memcmp(const void *s1, const void *s2, size_t n)
{
#if defined(LMU_OS_LINUX)
    return memcmp(s1, s2, n);
#else
#if defined(__aarch64__)
    return lmu_memcmp_aarch64(s1, s2, n);
#else
    return lmu_memcmp_no_asm(s1, s2, n);
#endif
#endif
}
