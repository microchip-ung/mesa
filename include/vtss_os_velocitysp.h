// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_OS_VELOCITYSP_H_
#define _VTSS_OS_VELOCITYSP_H_

#include "lm_utils.h"
#include "lm_switch.h"
#include "lm_os.h"

/** \brief Fallback Integer types */
typedef signed char  i8;  /**<  8-bit signed */
typedef signed short i16; /**< 16-bit signed */
typedef signed int   i32; /**< 32-bit signed */

typedef unsigned char  u8;  /**<  8-bit unsigned */
typedef unsigned short u16; /**< 16-bit unsigned */
typedef unsigned int   u32; /**< 32-bit unsigned */

#if __INTPTR_MAX__ == __INT64_MAX__
typedef signed long   i64; /**< 64-bit signed */
typedef unsigned long u64; /**< 64-bit unsigned */
#elif __INTPTR_MAX__ == __INT32_MAX__
typedef signed long long   i64; /**< 64-bit signed */
typedef unsigned long long u64; /**< 64-bit unsigned */
#else
#error "Environment not 32 or 64-bit."
#endif

typedef unsigned char BOOL; /**< Boolean implemented as 8-bit unsigned */

typedef struct {
    long int tv_sec;
    long int tv_usec;
} vtss_timeval_t;

typedef struct {
    vtss_timeval_t timeout;
    vtss_timeval_t now;
} vtss_mtimer_t;

uint8_t lm_mesa_timeval_init(vtss_timeval_t *timeval);
void   *lm_mesa_pseudo_malloc(uint32_t size, vtss_mem_flags_t f);

#define VTSS_OS_RAND()             lmu_pseudo_rand()
#define VTSS_OS_MALLOC(s, f)       lm_mesa_pseudo_malloc(s, f)
#define VTSS_OS_CPU_TO_DMA_ADDR(a) lm_os_to_dma_addr(a)

#define VTSS_OS_FREE(s, f)

#define VTSS_MEMSET(s, c, n) lmu_memset(s, c, n)
#define VTSS_MEMCMP(s, c, n) lmu_memcmp(s, c, n)
#define VTSS_MEMCPY(s, c, n) lmu_memcpy(s, c, n)

#define VTSS_STRLEN(s)      lmu_czstrlen(s)
#define VTSS_STRCPY(sd, ss) lmu_czstrcpy(sd, ss)

#define VTSS_DIV64(dividend, divisor) ((dividend) / (divisor))
#define VTSS_MOD64(dividend, divisor) ((dividend) % (divisor))

#define VTSS_LABS(arg)  ((arg > 0) ? arg : -arg)
#define VTSS_LLABS(arg) ((arg > 0) ? arg : -arg)

#define VTSS_TOUPPER(arg) (('a' <= arg && arg <= 'z') ? ((char)(arg - 'a' + 'A')) : arg)
#define VTSS_TOLOWER(arg) (('A' <= arg && arg <= 'Z') ? ((char)(arg - 'A' + 'a')) : arg)

/**
 * Count trailing zeros of a 32-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ(0x00000001) =  0
 *   VTSS_OS_CTZ(0x80000000) = 31
 *   VTSS_OS_CTZ(0x00000000) >= 32 (if result is taken as unsigned; Most
 * implementations return -1, and (u32)(-1) >= 32).
 *
 * __builtin_ctz() is included in GCC 3.2.2 and later according to
 * http://en.wikipedia.org/wiki/Find_first_set.
 *
 * Note: __builtin_ctz() is undefined for zero input values.
 */
#define VTSS_OS_CTZ(val32) ((val32) == 0 ? 32 : __builtin_ctz(val32))

#define VTSS_MSLEEP(msec)                                                                          \
    {                                                                                              \
        lm_os_nssleep(msec * 1000000);                                                             \
    }
#define VTSS_NSLEEP(nsec)                                                                          \
    {                                                                                              \
        lm_os_nssleep(nsec);                                                                       \
    }

#define VTSS_TIMERCMP(time_a, time_b, cmp) ((time_a.tv_sec cmp time_b.tv_sec) ? TRUE : FALSE)

#define VTSS_MTIMER_START(timer, msec)                                                             \
    {                                                                                              \
        lm_mesa_timeval_init(&((timer)->timeout));                                                 \
        (timer)->timeout.tv_usec += msec * 1000;                                                   \
        if ((timer)->timeout.tv_usec >= 1000000) {                                                 \
            (timer)->timeout.tv_sec += (timer)->timeout.tv_usec / 1000000;                         \
            (timer)->timeout.tv_usec %= 1000000;                                                   \
        }                                                                                          \
    }

#define VTSS_MTIMER_TIMEOUT(timer)                                                                 \
    (lm_mesa_timeval_init(&((timer)->now)) && VTSS_TIMERCMP((timer)->now, (timer)->timeout, >))

#define VTSS_TIME_OF_DAY(time)                                                                     \
    {                                                                                              \
        lm_mesa_timeval_init((time));                                                              \
    }

#define VTSS_OS_NTOHL(X) lmu_ntohl(X)

#define LM_PROF_ID_MESA_INIT     20U
#define LM_PROF_ID_MESA_PMAP     21U
#define VTSS_PROF_ENTER(id, sub) lm_os_prof_enter(id, sub)
#define VTSS_PROF_EXIT(id, sub)  lm_os_prof_exit(id, sub)

#endif //  _VTSS_OS_VELOCITYSP_H_
