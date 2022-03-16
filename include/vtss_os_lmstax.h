// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_OS_LMSTAX_H_
#define _VTSS_OS_LMSTAX_H_

#include "lm_utils.h"

/** \brief Fallback Integer types */
typedef signed char        i8;   /**<  8-bit signed */
typedef signed short       i16;  /**< 16-bit signed */
typedef signed int         i32;  /**< 32-bit signed */
typedef signed long long   i64;  /**< 64-bit signed */

typedef unsigned char      u8;   /**<  8-bit unsigned */
typedef unsigned short     u16;  /**< 16-bit unsigned */
typedef unsigned int       u32;  /**< 32-bit unsigned */
typedef unsigned long long u64;  /**< 64-bit unsigned */

typedef unsigned char      BOOL; /**< Boolean implemented as 8-bit unsigned */
typedef unsigned int       uintptr_t; /**< Unsigned integer big enough to hold pointers */

#define VTSS_OS_RAND() lmu_pseudo_rand()
#define VTSS_OS_MALLOC(s, f) lmu_pseudo_malloc(s)
#define VTSS_OS_FREE(s, f)

#define VTSS_MEMSET(s, c, n) lmu_memset(s, c, n)
#define VTSS_MEMCMP(s, c, n) lmu_memcmp(s, c, n)
#define VTSS_MEMCPY(s, c, n) lmu_memcpy(s, c, n)

#define VTSS_STRLEN(s) lmu_czstrlen(s)
#define VTSS_STRCPY(sd, ss) lmu_czstrcpy(sd, ss)
#define VTSS_SPRINTF(...) lmu_sprintf(__VA_ARGS__)
#define VTSS_SNPRINTF(...) lmu_snprintf(__VA_ARGS__)

#define VTSS_DIV64(dividend, divisor) ((dividend) / (divisor))
#define VTSS_MOD64(dividend, divisor) ((dividend) % (divisor))

#define VTSS_LABS(arg) ((arg > 0) ? arg : -arg)

#define VTSS_TOUPPER(arg) (('a' <= arg && arg <= 'z') ? ((char) (arg - 'a' + 'A')) : arg)
#define VTSS_TOLOWER(arg) (('A' <= arg && arg <= 'Z') ? ((char) (arg - 'A' + 'a')) : arg)

/**
 * Count trailing zeros of a 32-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ(0x00000001) =  0
 *   VTSS_OS_CTZ(0x80000000) = 31
 *   VTSS_OS_CTZ(0x00000000) >= 32 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 32).
 *
 * __builtin_ctz() is included in GCC 3.2.2 and later according to http://en.wikipedia.org/wiki/Find_first_set.
 *
 * Note: __builtin_ctz() is undefined for zero input values.
 */
#define VTSS_OS_CTZ(val32) ((val32) == 0 ? 32 : __builtin_ctz(val32))

typedef struct {
    long    tv_sec;    /* seconds since Jan. 1, 1970 */
    long    tv_usec;   /* and microseconds */
} lm_timeval_t;

typedef struct {
    lm_timeval_t timeout;
    lm_timeval_t now;
} vtss_mtimer_t;

#define VTSS_MSLEEP(msec)
#define VTSS_NSLEEP(msec)

#define VTSS_GETTIMEOFDAY(time) ((time)->tv_sec = (time)->tv_usec = 0)
#define VTSS_TIMERCMP(time_a, time_b, cmp) ((time_a.tv_sec cmp time_b.tv_sec) ? TRUE : FALSE)

#define VTSS_MTIMER_START(timer, msec) { \
    (void) VTSS_GETTIMEOFDAY(&((timer)->timeout));   \
    (timer)->timeout.tv_usec+=msec*1000; \
    if ((timer)->timeout.tv_usec>=1000000) { (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000; (timer)->timeout.tv_usec%=1000000; } \
} /**< Start timer */

#define VTSS_MTIMER_TIMEOUT(timer) (VTSS_GETTIMEOFDAY(&((timer)->now))==0 && VTSS_TIMERCMP(&((timer)->now),&((timer)->timeout),>))

#endif //  _VTSS_OS_LMSTAX_H_
