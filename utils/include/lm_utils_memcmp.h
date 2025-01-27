// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_MEMCMP_H
#define LM_UTILS_MEMCMP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int lmu_memcmp(const void *s1, const void *s2, size_t n);

#if defined(__aarch64__)
#pragma coverity compliance deviate                                            \
    "MISRA C-2023 Rule 8.6"                                                    \
    "This is implemented in ASM which is not being picked up by coverity"
int lmu_memcmp_aarch64(const void *s1, const void *s2, size_t n);
#endif

int lmu_memcmp_no_asm(const void *s1, const void *s2, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
