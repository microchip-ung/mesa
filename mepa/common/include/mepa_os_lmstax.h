// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_OS_LMSTAX_H_
#define _MEPA_OS_LMSTAX_H_

#include "lm_utils.h"

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

#define MEPA_LABS(arg) ((arg > 0) ? arg : -arg)

typedef struct {
    long    tv_sec;    /* seconds since Jan. 1, 1970 */
    long    tv_usec;   /* and microseconds */
} mepa_timeval_t;

typedef struct {
    mepa_timeval_t timeout;
    mepa_timeval_t now;
} mepa_mtimer_t;

#define MEPA_MSLEEP(msec)

#define MEPA_GETTIMEOFDAY(time) ((time)->tv_sec = (time)->tv_usec = 0)
#define MEPA_TIMERCMP(time_a, time_b, cmp) ((time_a.tv_sec cmp time_b.tv_sec) ? TRUE : FALSE)

#define MEPA_MTIMER_START(timer, msec) { \
    (void) MEPA_GETTIMEOFDAY(&((timer)->timeout));   \
    (timer)->timeout.tv_usec+=msec*1000; \
    if ((timer)->timeout.tv_usec>=1000000) { (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000; (timer)->timeout.tv_usec%=1000000; } \
} /**< Start timer */

#define MEPA_MTIMER_TIMEOUT(timer) (MEPA_GETTIMEOFDAY(&((timer)->now))==0 && MEPA_TIMERCMP(&((timer)->now),&((timer)->timeout),>))

#endif //  _MEPA_OS_LMSTAX_H_
