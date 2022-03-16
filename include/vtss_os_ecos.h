// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief eCos OS API
 * \details This header file describes OS functions for eCos
 */

#ifndef _VTSS_OS_ECOS_H_
#define _VTSS_OS_ECOS_H_

#include "vtss/api/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>

#include <cyg/kernel/kapi.h>
#include <cyg/hal/hal_cache.h>  /* For cache line size and cache manipulation routines */
#include <cyg/hal/hal_arch.h>   /* For HAL_REORDER_BARRIER()                           */
#include <cyg/hal/hal_endian.h> /* For endianness                                      */

#ifdef __cplusplus
extern "C" {
#endif

#define VTSS_MSLEEP(msec)       HAL_DELAY_US(msec*1000)    /**< Sleep for "msec" milliseconds */
#define VTSS_NSLEEP(nsec)       HAL_DELAY_US((nsec)/1000)  /**< Sleep for "nsec" nanoseconds  */

typedef cyg_tick_count_t vtss_mtimer_t;                                                /**< Timer                             */
#define VTSS_MTIMER_START(pTimer,msec)  *pTimer = cyg_current_time() + ((msec)/10) + 1 /**< Starting Timer                    */
#define VTSS_MTIMER_TIMEOUT(pTimer) (cyg_current_time() > *(pTimer))                   /**< Timer timeout                     */
#define VTSS_MTIMER_CANCEL(pTimer)                                                     /**< No action in this implementation. */

/** \brief Time of day structure */
typedef struct {
    u32 sec; /**< Time of day in seconds */
} vtss_timeofday_t;

#define VTSS_TIME_OF_DAY(tod) (tod.sec = (cyg_current_time() / CYGNUM_HAL_RTC_DENOMINATOR)) /**< Time of day macro */

/**
 * \brief Obtain the absolute value of a long long integer.
 *
 * \param val [IN] The value to convert to absolute value.
 * \return         The absolute value of val.
*/
extern long long int llabs(long long int val);

#define VTSS_DIV64(dividend, divisor) ((dividend) / (divisor)) /**< support for 64 bit division */
#define VTSS_MOD64(dividend, divisor) ((dividend) % (divisor)) /**< support for 64 bit division */
#define VTSS_LABS(arg)                labs(arg)                /**< long to abs */
#define VTSS_LLABS(arg)               llabs(arg)               /**< long long to abs */

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

/**
 * Count trailing zeros of a 64-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ64(0x00000000_00000001) =  0
 *   VTSS_OS_CTZ64(0x00000000_80000000) = 31
 *   VTSS_OS_CTZ64(0x00000001_00000000) = 32
 *   VTSS_OS_CTZ64(0x80000000_00000000) = 63
 *   VTSS_OS_CTZ64(0x00000000_00000000) >= 64 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 64).
 *
 * Note: __builtin_ctzll() is undefined for zero input values.
 */
#define VTSS_OS_CTZ64(val64) ((val64) == 0 ? 64 : __builtin_ctzll(val64))

/**
 * \brief Callout to allocate memory.
 *
 * [IN]/[OUT] seen from called function.
 * \param size  [IN] Number of bytes to allocate.
 * \param flags [IN] See vtss_mem_flags_t for details.
 * \return Pointer to allocated area.
*/
void *vtss_callout_malloc(size_t size, vtss_mem_flags_t flags);

/**
 * \brief Callout to free memory.
 *
 * [IN]/[OUT] seen from called function.
 * \param ptr   [IN] Pointer previously obtained with call to vtss_callout_malloc().
 * \param flags [IN] See vtss_mem_flags_t for details.
*/
void vtss_callout_free(void *ptr, vtss_mem_flags_t flags);

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
#define VTSS_OS_MALLOC(size, flags) vtss_callout_malloc(size, flags)

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
#define VTSS_OS_FREE(ptr, flags) vtss_callout_free(ptr, flags)

/**
 * Wrap of call to rand() defined in stdlib.h
 */
#define VTSS_OS_RAND() rand()
 
/******************************************************************************/
// COMPILER SECTION
/******************************************************************************/
/**
 * The compiler may swap instructions to optimize performance of the final
 *   code (size- or speed-wise). When configuration of hardware is involved,
 *   it may not always be valid to swap two statements. Consider for instance
 *   the following two writes to two FDMA registers:
 *      Write the source address to the FDMA
 *      Enable the FDMA.
 *   To the compiler, these two writes can be executed in any order and still
 *   semantically yield the correct result, had it been normal RAM they were
 *   written to. But since they are written to actual hardware, it is crucial
 *   that they are executed in the correct order.
 *   The VTSS_OS_REORDER_BARRIER() macro should implement code that ensures that the
 *   compiler doesn't optimize across the barrier.
 */
#define VTSS_OS_REORDER_BARRIER() HAL_REORDER_BARRIER()

/**
 * In some special cases, it is of utmost importance that a certain variable
 *   has a certain memory alignment. Applications for this is e.g. placing variables
 *   on cache-line boundaries.
 */
#define VTSS_OS_COMPILER_ATTRIBUTE_ALIGNED(x) __attribute ((aligned(x)))

/******************************************************************************/
// CACHE SECTION
/******************************************************************************/

/**
 * The number of bytes one DCache-line is made up of.
 */
#define VTSS_OS_DCACHE_LINE_SIZE_BYTES HAL_DCACHE_LINE_SIZE

/**
 * Invalidate \@size bytes at virtual address \@virt_addr of the DCache.
 * After invalidation, the invalidated area will be fetched from RAM.
 */
#define VTSS_OS_DCACHE_INVALIDATE(virt_addr, size) HAL_DCACHE_INVALIDATE(virt_addr, size)

/**
 * Force a write of \@size bytes of dirty cache lines to RAM starting at
 * virtual address \@virt_addr.
 */
#define VTSS_OS_DCACHE_FLUSH(virt_addr, size) HAL_DCACHE_STORE(virt_addr, size)

/**
 *   Macro that implements the conversion from a virtual to a physical address.
 *   In OSs with a flat memory layout, this could be as simple as (u32)(addr).
 */
#define VTSS_OS_VIRT_TO_PHYS(addr) (u32)CYGARC_PHYSICAL_ADDRESS(addr)

/******************************************************************************/
// PLATFORM SECTION
/******************************************************************************/

/**
 * \brief VTSS_OS_BIG_ENDIAN: 
 * If undefined, we're running little endian.
 * If defined we're running big endian.
 */
#if (CYG_BYTEORDER == CYG_MSBFIRST)
  #define VTSS_OS_BIG_ENDIAN    /**< We're running big endian */
  #define VTSS_OS_NTOHL(x) (x)  /**< Convert from network to host order */
#else

/* Yes, this looks clumsy, but its not possible to use <sys/byteorder.h> */
#define VTSS_OS_NTOHL(v1) ((((v1) >> 24) & 0x000000FF) | (((v1) >> 8) & 0x0000FF00) | (((v1) << 8) & 0x00FF0000) | (((v1) << 24) & 0xFF000000)) /**< Convert a 32-bit value from network to host order */

#endif

/******************************************************************************/
// TASK SWITCH/INTERRUPT SECTION
/******************************************************************************/

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
 * The __attribute__((unused))  ensures that we don't get compiler warnings.
 */
#define VTSS_OS_SCHEDULER_FLAGS cyg_uint32  __attribute__((unused))
/**
 * Lock scheduler.
 */
#define VTSS_OS_SCHEDULER_LOCK(flags) cyg_scheduler_lock(__FILE__, __LINE__)
/**
 * Unlock scheduler.
 */
#define VTSS_OS_SCHEDULER_UNLOCK(flags) cyg_scheduler_unlock(__FILE__, __LINE__)

/**
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
 * Not needed in eCos, since all interrupt handlers will be called in deferred context.
 */
#define VTSS_OS_INTERRUPT_FLAGS          NOT_NEEDED
/**
 * Disable interrupts.
 */
#define VTSS_OS_INTERRUPT_DISABLE(flags) NOT_NEEDED
/**
 Enable interrupts.
 */
#define VTSS_OS_INTERRUPT_RESTORE(flags) NOT_NEEDED

#define VTSS_MEMSET(s, c, n) memset(s, c, n)
#define VTSS_MEMCMP(s, c, n) memcmp(s, c, n)
#define VTSS_MEMCPY(s, c, n) memcpy(s, c, n)

#define VTSS_STRLEN(s) strlen(s)
#define VTSS_STRCPY(sd, ss) strcpy(sd, ss)
#define VTSS_SPRINTF(...) sprintf(__VA_ARGS__)
#define VTSS_SNPRINTF(...) snprintf(__VA_ARGS__)

#define VTSS_TOUPPER(arg) (toupper(arg))
#define VTSS_TOLOWER(arg) (toupper(arg))

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_OS_ECOS_H_ */
