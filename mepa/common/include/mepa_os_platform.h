// Copyright (c) 2004-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_OS_PLATFORM_H_
#define _MEPA_OS_PLATFORM_H_

#include <os_platform_api.h>

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef uint8_t   BOOL;

#define MEPA_OS_TRUE	(1U)
#define MEPA_OS_FALSE	(0U)

#define MEPA_DIV64(dividend, divisor) ((dividend) / (divisor))
#define MEPA_MOD64(dividend, divisor) ((dividend) % (divisor))

#define MEPA_LABS(arg) ((arg > 0) ? arg : -arg)

#define TICKS_PER_MS_300MHZ             (300000UL)
#define MAX_ALLOWED_TIME_DIFF			(4000U)

#define task_delay(delay) \
	    {volatile uint n = delay * 4; while (n > 0) n--; }

#define MEPA_NSLEEP(delay) task_delay(delay) /**< Sleep macro */

typedef u32 mepa_timeval_t;

typedef struct {
    mepa_timeval_t timeout;
    mepa_timeval_t now;
} mepa_mtimer_t;

#define MEPA_TIME_OF_DAY(t) { \
	t.now = os_platform_get_system_time();  \
} /**< System time macro */

#define MEPA_MTIMER_TIMEOUT(timer) ((((timer.now = os_platform_get_system_time()) - timer.timeout) > 0)?((timer.now/TICKS_PER_MS_300MHZ > MAX_ALLOWED_TIME_DIFF)? MEPA_OS_TRUE:MEPA_OS_FALSE):MEPA_OS_FALSE) /**< Timer timeout macro */

#endif /* _MEPA_OS_PLATFORM_H_ */
