// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_OS_VELOCITYSP_H_
#define _MEPA_OS_VELOCITYSP_H_

#include "lm_utils.h"
#include "lm_os.h"

typedef signed char        i8;
typedef signed short       i16;
typedef signed int         i32;
typedef signed long long   i64;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;
typedef unsigned char      BOOL;
//typedef unsigned int       uintptr_t; /**< Unsigned integer big enough to hold pointers */

#define MEPA_DIV64(dividend, divisor) ((dividend) / (divisor))
#define MEPA_MOD64(dividend, divisor) ((dividend) % (divisor))

#define MEPA_LABS(arg)  (((arg) > 0) ? arg : -arg)
#define MEPA_LLABS(arg) (((arg) > 0) ? arg : -arg)
#define MEPA_ABS(arg)   (((arg) > 0) ? arg : -arg)

#define MEPA_MSLEEP(msec) { lm_os_nssleep(msec * 1000000); }
#define MEPA_NSLEEP(nsec) { lm_os_nssleep(nsec); }

typedef struct {
    long int tv_sec;
    long int tv_usec;
} mepa_timeval_t;

typedef struct {
    mepa_timeval_t timeout;
    mepa_timeval_t now;
} mepa_mtimer_t;

#define MEPA_TIMERCMP(time_a, time_b, cmp) ((time_a.tv_sec cmp time_b.tv_sec) ? 1 : 0)

#define MEPA_MTIMER_START(timer, msec) { \
    uint64_t ns = lm_os_ext_time_get(); \
    uint64_t sec = (ns / 1000000000U); \
    uint64_t usec = ((ns % 1000000000U) / 1000000U); \
    (timer)->timeout.tv_sec = (int32_t)sec; \
    (timer)->timeout.tv_usec = (int32_t)usec; \
    (timer)->timeout.tv_usec += msec * 1000; \
    if ((timer)->timeout.tv_usec >= 1000000) { \
        (timer)->timeout.tv_sec += (timer)->timeout.tv_usec / 1000000; \
        (timer)->timeout.tv_usec %= 1000000; \
    } \
}

#define MEPA_MTIMER_TIMEOUT(timer) ({ \
    uint64_t ns = lm_os_ext_time_get(); \
    uint64_t sec = (ns / 1000000000U); \
    uint64_t usec = ((ns % 1000000000U) / 1000000U); \
    (timer)->now.tv_sec = (int32_t)sec; \
    (timer)->now.tv_usec = (int32_t)usec; \
    MEPA_TIMERCMP((timer)->now, (timer)->timeout, >); \
})

#endif //  _MEPA_OS_VELOCITYSP_H_
