// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_OS_LINUX_H_
#define _MEPA_OS_LINUX_H_

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef uint8_t   BOOL;

#define MEPA_DIV64(dividend, divisor) ((dividend) / (divisor))
#define MEPA_MOD64(dividend, divisor) ((dividend) % (divisor))

#define MEPA_LABS(arg)                labs(arg)

typedef struct {
    struct timeval timeout;   /**< Timeout */
    struct timeval now;       /**< Time right now */
} mepa_mtimer_t;

#define MEPA_NSLEEP(nsec) {                                     \
    struct timespec ts;                                         \
    ts.tv_sec = 0;                                              \
    ts.tv_nsec = nsec;                                          \
    while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
    }                                                           \
}

/** Sleep for \param msec milliseconds */
#define MEPA_MSLEEP(msec) {                                     \
    struct timespec ts;                                         \
    ts.tv_sec = msec / 1000;                                    \
    ts.tv_nsec = (msec % 1000) * 1000000;                       \
    while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
    }                                                           \
}

#define MEPA_MTIMER_START(timer,msec) { \
    (void) gettimeofday(&((timer)->timeout),NULL);   \
    (timer)->timeout.tv_usec+=msec*1000; \
    if ((timer)->timeout.tv_usec>=1000000) { (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000; (timer)->timeout.tv_usec%=1000000; } \
} /**< Start timer */

#define MEPA_MTIMER_TIMEOUT(timer) (gettimeofday(&((timer)->now),NULL)==0 && timercmp(&((timer)->now),&((timer)->timeout),>)) /**< Timer timeout */

#define MEPA_MTIMER_CANCEL(timer) /**< No action in this implementation. */

/**< Time of day struct */
typedef struct {
    time_t sec; /**< Time of day in seconds */
} mepa_timeofday_t;

#define MEPA_TIME_OF_DAY(tod) { \
    struct timeval tve; \
    (void)gettimeofday(&tve,NULL);  \
    tod.sec = tve.tv_sec; \
} /**< Time of day macro */

#define MEPA_LLABS(arg)               llabs(arg)


#endif /* _MEPA_OS_LINUX_H_ */
