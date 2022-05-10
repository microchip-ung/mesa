// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Linux OS API
 * \details This header file describes OS functions for Linux
 */

#ifndef _VTSS_OS_LINUX_H_
#define _VTSS_OS_LINUX_H_

#ifndef __KERNEL__

#include <endian.h>
#include <asm/byteorder.h>
#include <stdint.h>
#include <inttypes.h>

/** \brief C99 Integer types */
typedef signed char        i8;   /**<  8-bit signed */
typedef int16_t            i16;  /**< 16-bit signed */
typedef int32_t            i32;  /**< 32-bit signed */
typedef int64_t            i64;  /**< 64-bit signed */

typedef uint8_t            u8;   /**<  8-bit unsigned */
typedef uint16_t           u16;  /**< 16-bit unsigned */
typedef uint32_t           u32;  /**< 32-bit unsigned */
typedef uint64_t           u64;  /**< 64-bit unsigned */

typedef u8                 BOOL; /**< Boolean implemented as 8-bit unsigned */
typedef BOOL               bool;

/**
 * \brief VTSS_OS_BIG_ENDIAN:
 *   If undefined, we're running little endian.
 *   If defined we're running big endian.
 */
#if __BYTE_ORDER == __BIG_ENDIAN
#define VTSS_OS_BIG_ENDIAN /**< We're running big endian */
#endif

#define VTSS_OS_NTOHL(x) __be32_to_cpu(x) /**< Convert a 32-bit value from network to host order */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>             /* For memset and friend (not in stdlib) */

#include <errno.h>
#include <time.h>
#include <sys/time.h>

#if defined(BOARD_SERVAL_VSIM)||defined(BOARD_JAGUAR2_VSIM)
void vsim_nsleep(u32 n);
/** VSIM control time passing **/
#define VTSS_NSLEEP(nsec) vsim_nsleep(nsec)
/** Sleep for \param msec milliseconds */
#define VTSS_MSLEEP(msec) vsim_nsleep(msec*1000000)
#else
/** Sleep for \param nsec nanoseconds */
#ifndef _VTSS_MAIN_TYPES_H_
#define VTSS_NSLEEP(nsec) {                                     \
    struct timespec ts;                                         \
    ts.tv_sec = 0;                                              \
    ts.tv_nsec = nsec;                                          \
    while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
    }                                                           \
}

/** Sleep for \param msec milliseconds */
#define VTSS_MSLEEP(msec) {                                     \
    struct timespec ts;                                         \
    ts.tv_sec = msec / 1000;                                    \
    ts.tv_nsec = (msec % 1000) * 1000000;                       \
    while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
    }                                                           \
}
#endif  // _VTSS_MAIN_TYPES_H_
#endif /* BOARD_SERVAL_VSIM */

#ifndef _VTSS_MAIN_TYPES_H_
/** \brief Timer structure */
typedef struct {
    struct timeval timeout;   /**< Timeout */
    struct timeval now;       /**< Time right now */
} vtss_mtimer_t;

#define VTSS_MTIMER_START(timer,msec) { \
    (void) gettimeofday(&((timer)->timeout),NULL);   \
    (timer)->timeout.tv_usec+=msec*1000; \
    if ((timer)->timeout.tv_usec>=1000000) { (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000; (timer)->timeout.tv_usec%=1000000; } \
} /**< Start timer */

#define VTSS_MTIMER_TIMEOUT(timer) (gettimeofday(&((timer)->now),NULL)==0 && timercmp(&((timer)->now),&((timer)->timeout),>)) /**< Timer timeout */
#endif  // _VTSS_MAIN_TYPES_H_

#define VTSS_MTIMER_CANCEL(timer) /**< No action in this implementation. */

/**< Time of day struct */
typedef struct {
    time_t sec; /**< Time of day in seconds */
} vtss_timeofday_t;

#define VTSS_TIME_OF_DAY(tod) { \
    struct timeval tve; \
    (void)gettimeofday(&tve,NULL);  \
    tod.sec = tve.tv_sec; \
} /**< Time of day macro */

// vtss_jaguar_1.c requires these defines. When compiling for the
// Genie board we're not in kernel mode and the application is 
// single-threaded, so we can live with not doing anything in these functions.
/**
 * VTSS_OS_SCHEDULER_FLAGS
 * VTSS_OS_SCHEDULER_LOCK(flags)
 * VTSS_OS_SCHEDULER_UNLOCK(flags)
 *   These functions are called by API code that consists of a user-level part
 *   and a deferred interrupt handler part.
 *   Only the user-level part will call the VTSS_OS_SCHEDULER_LOCK()/UNLOCK()
 *   functions, since it is assumed that the deferred interrupt handler will
 *   have atomic access throughout its execution.
 *   Each module within the API that contains such functionality will have
 *   an option to call either the VTSS_OS_SCHEDULER_(UN)LOCK() functions
 *   or the VTSS_OS_INTERRUPT_DISABLE()/RESTORE() functions.
 */
#define VTSS_OS_SCHEDULER_FLAGS         int
#define VTSS_OS_SCHEDULER_LOCK(flags)   do {flags = flags;} while (0); /**< Lock scheduler */
#define VTSS_OS_SCHEDULER_UNLOCK(flags) do {flags = flags;} while (0); /**< Unlock scheduler */

/**
 * VTSS_DIV64 - perform 64/32 bit division yelding 32 bit (at least) output
 */
#define VTSS_DIV64(dividend, divisor) ((dividend) / (divisor))
/**
 * VTSS_MOD64 - perform 64/32 bit modulus yelding 32 bit (at least) output
 */
#define VTSS_MOD64(dividend, divisor) ((dividend) % (divisor))
/**
 * VTSS_LABS - perform abs() on long
 */
#define VTSS_LABS(arg)                labs(arg)

/**
 * VTSS_LLABS - perform abs() on long long
 */
#define VTSS_LLABS(arg)               llabs(arg)

#else

/* __KERNEL__ */

#include <linux/stddef.h>
#include <linux/types.h>        /* ulong and friends */
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/slab.h>         /* for kmalloc/kfree */
#include <linux/vmalloc.h>      /* for vmalloc/vfree */
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/math64.h>

#define VTSS_OS_NTOHL(x) __be32_to_cpu(x) /**< Convert a 32-bit value from network to host order */

#define VTSS_HAVE_U_TYPES       /* Namespace coexistance - use the ones from the kernel */

typedef struct {
    struct timeval timeout;
    struct timeval now;
} vtss_mtimer_t;

#define VTSS_NSLEEP(nsec) ndelay(nsec) /**< Sleep for "msec" milliseconds */
#define VTSS_MSLEEP(msec) mdelay(msec) /**< Sleep for "nsec" nanoseconds  */

#define VTSS_MTIMER_START(timer,msec) {                                 \
        (void) do_gettimeofday(&((timer)->timeout));                     \
        (timer)->timeout.tv_usec+=msec*1000;                            \
        if ((timer)->timeout.tv_usec>=1000000) {                        \
            (timer)->timeout.tv_sec+=(timer)->timeout.tv_usec/1000000;  \
            (timer)->timeout.tv_usec%=1000000;                          \
        }                                                               \
    }

static __always_inline int vtss_mtimer_timeout(vtss_mtimer_t *t)
{
    do_gettimeofday(&t->now);
    if(timeval_compare(&t->now, &t->timeout) > 0)
        return true;
    udelay(1);                  /* Be nice */
    return false;
}

#define VTSS_MTIMER_TIMEOUT(timer) vtss_mtimer_timeout(timer)

#define VTSS_MTIMER_CANCEL(timer) /* No action in this implementation. */

#define VTSS_DIV64 div64_u64

static inline u32 vtss_mod64(u64 div, u32 base)
{
    return do_div(div, base);   /* Remainder *returned* by do_div */
}

#define VTSS_MOD64 vtss_mod64

#define VTSS_LABS(arg)                __builtin_labs(arg)

static __always_inline long long
vtss_llabs(long long j)
{
    return (j < 0 ? -j : j);
}

#define VTSS_LLABS(arg)               vtss_llabs(arg)

/******************************************************************************/
// PLATFORM SECTION
/******************************************************************************/

#include <asm/io.h>

/******************************************************************************/
// TASK SWITCH/INTERRUPT SECTION
/******************************************************************************/

#include <linux/interrupt.h>

/*
 * VTSS_OS_SCHEDULER_FLAGS
 * VTSS_OS_SCHEDULER_LOCK(flags)
 * VTSS_OS_SCHEDULER_UNLOCK(flags)
 *   These functions are called by API code that consists of a user-level part
 *   and a deferred interrupt handler part.
 *   Only the user-level part will call the VTSS_OS_SCHEDULER_LOCK()/UNLOCK()
 *   functions, since it is assumed that the deferred interrupt handler will
 *   have atomic access throughout its execution.
 *   Each module within the API that contains such functionality will have
 *   an option to call either the VTSS_OS_SCHEDULER_(UN)LOCK() functions
 *   or the VTSS_OS_INTERRUPT_DISABLE()/RESTORE() functions.
 */
#define VTSS_OS_SCHEDULER_FLAGS         unsigned long
#define VTSS_OS_SCHEDULER_LOCK(flags)   local_irq_save(flags)
#define VTSS_OS_SCHEDULER_UNLOCK(flags) local_irq_restore(flags)

/*
 * VTSS_OS_INTERRUPT_FLAGS
 * VTSS_OS_INTERRUPT_DISABLE(flags)
 * VTSS_OS_INTERRUPT_RESTORE(flags)
 *   These functions are called by API code that consists of a user-level part
 *   and an interrupt handler part executing directly in interrupt context.
 *   Only the user-level part will call the VTSS_OS_INTERRUPT_DISABLE()/RESTORE()
 *   functions, since it is assumed that the interrupt handler will
 *   have atomic access throughout its execution.
 *   Each module within the API that contains such functionality will have
 *   an option to call either the VTSS_OS_SCHEDULER_(UN)LOCK() functions
 *   or the VTSS_OS_INTERRUPT_DISABLE()/RESTORE() functions.
 */
#define VTSS_OS_INTERRUPT_FLAGS          NOT_NEEDED
#define VTSS_OS_INTERRUPT_DISABLE(flags) NOT_NEEDED
#define VTSS_OS_INTERRUPT_RESTORE(flags) NOT_NEEDED

#endif /* __KERNEL__ */

// Whether __KERNEL__ or not.

/**
 * VTSS_OS_CTZ(val32)
 *
 * Count trailing zeros of a 32-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ(0x00000001) =  0
 *   VTSS_OS_CTZ(0x80000000) = 31
 *   VTSS_OS_CTZ(0x00000000) >= 32 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 32).
 *
 * \param val32 The value to decode
 *
 * \return Number of trailing zeroes - or - the bit index of the
 * lowest bit set in the input given.
 * 
 * \note __builtin_ctz() is included in GCC 3.2.2 and later according
 * to http://en.wikipedia.org/wiki/Find_first_set.
 *
 * Note: __builtin_ctzl() is undefined for zero input values.
 */
#define VTSS_OS_CTZ(val32) ((val32) == 0 ? 32 : __builtin_ctzl((unsigned long)val32))

/**
 * Count trailing zeros of a 64-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ64(0x00000000_00000001) =  0
 *   VTSS_OS_CTZ64(0x00000000_80000000) = 31
 *   VTSS_OS_CTZ64(0x00000001_00000000) = 32
 *   VTSS_OS_CTZ64(0x80000000_00000000) = 63
 *   VTSS_OS_CTZ64(0x00000000_00000000) >= 64 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 64).
 */
#define VTSS_OS_CTZ64(val64) ({                            \
    u32 _r = VTSS_OS_CTZ((u32)(val64));                    \
    (val64) == 0 ? 64 :                                    \
    _r < 32 ? _r : 32 + VTSS_OS_CTZ((u32)((val64) >> 32)); \
})

#if defined(VTSS_NO_CTZL) || (defined(__GNUC__) && __GNUC__ < 3)
static inline int __builtin_ctzl(unsigned long val32)
{
#if defined(CONFIG_CPU_MIPSR2) || defined(CONFIG_CPU_MIPS64)
    unsigned int obits;
    __asm__("clz %0, %1" : "=r" (obits) : "r" (val32));
    return 31 - obits;
#else
    unsigned int i, mask = 1;
    for (i = 0; i < 32; i++) {
        if (val32 & mask) {
            return i;
        }
        mask <<= 1;
    }
    return i;
#endif
}
#endif

/**
 * Request OS to allocate size bytes of memory.
 *
 * The first argument is the number of bytes that must
 * be allocated. Type is size_t.
 *
 * The second argument is a mask of flags that the
 * implementation must obey. Type is vtss_mem_flags_t.
 *
 * The returned pointer should be at least 8-byte aligned,
 * to make it suitable for a struct.
 */
#ifdef __KERNEL__
#define VTSS_OS_MALLOC(size, flags) vmalloc(size)


#else
#define VTSS_OS_MALLOC(size, flags) malloc(size)
#endif

/**
 * Request OS to free memory previously allocated with
 * VTSS_OS_MALLOC().
 *
 * The first argument is the pointer previously
 * obtained with a call to VTSS_OS_MALLOC(). Type is
 * void *.
 *
 * The second argument is a mask of flags identical to
 * those passed to VTSS_OS_MALLOC() when the memory
 * was requested.
 */
#ifdef __KERNEL__
#define VTSS_OS_FREE(ptr, flags) vfree(ptr)
#else
#define VTSS_OS_FREE(ptr, flags) free(ptr)
#endif

/**
 * Wrap of call to rand() defined in stdlib.h
 */
#define VTSS_OS_RAND() rand()

#define VTSS_MEMSET(s, c, n) memset(s, c, n)
#define VTSS_MEMCMP(s, c, n) memcmp(s, c, n)
#define VTSS_MEMCPY(s, c, n) memcpy(s, c, n)

#define VTSS_STRLEN(s) strlen(s)
#define VTSS_STRCPY(sd, ss) strcpy(sd, ss)
#define VTSS_SPRINTF(...) sprintf(__VA_ARGS__)
#define VTSS_SNPRINTF(...) snprintf(__VA_ARGS__)

#define VTSS_TOUPPER(arg) (toupper(arg))
#define VTSS_TOLOWER(arg) (toupper(arg))

#endif /* _VTSS_OS_LINUX_H_ */

