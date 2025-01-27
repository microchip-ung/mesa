// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_MEMSET_H
#define LM_UTILS_MEMSET_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Typically these functions are used wihtout a need for a return type.
void lmu_memset(void *dst, int val, size_t count);

#if defined(__arm__)
#pragma coverity compliance deviate                                            \
    "MISRA C-2023 Rule 8.6"                                                    \
    "This is implemented in ASM which is not being picked up by coverity"
void *lmu_memset_arm(void *dst, int val, size_t count);
#elif defined(__aarch64__)
#pragma coverity compliance deviate                                            \
    "MISRA C-2023 Rule 8.6"                                                    \
    "This is implemented in ASM which is not being picked up by coverity"
void *lmu_memset_aarch64(void *dst, int val, size_t count);
#endif

void *lmu_memset_(void *dst, int val, size_t count);
void *lmu_memset_no_asm(void *dst, int val, size_t count);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
