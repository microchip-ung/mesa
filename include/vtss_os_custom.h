/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

/**
 * \file
 * \brief OS custom header file
 * \details This file is a skeleton to be replaced by for customer specific OS.
 */

#include <string.h>             /* For memset and friend (not in stdlib) */
#include <stdlib.h>             /* For malloc and friends */
#include <stdio.h>              /* For sprintf and friends */ 

#define uint unsigned int    /**< Define API uint type - unsigned 16 bits */
#define ulong unsigned long  /**< Define API ulong - unsigned 32 bits */

// Define how to do a 1 millisecond sleep
#define VTSS_MSLEEP(msec)  <your function> /**< Your function for sleeping for "msec" milli seconds */

// Define Timer function
typedef int vtss_mtimer_t; /**< Timer */
#define VTSS_MTIMER_START(pTimer,msec) <your impl> /**< Start the timer (pTimer) with a timeout after a number of milliseconds */
#define VTSS_MTIMER_TIMEOUT(pTimer)    <your impl> /**< Check if timer has timed out (Return TRUE in case of timeout else FALSE). */
#define VTSS_MTIMER_CANCEL(pTimer)     <your impl> /**< Stop the timer  */

#define VTSS_DIV64(dividend, divisor)  <your impl> /**< support for 64 bit division */
#define VTSS_MOD64(dividend, divisor)  <your impl> /**< support for 64 bit division */
#define VTSS_LABS(arg)                 <your impl> /**< long to abs */
#define VTSS_LLABS(arg)                <your impl> /**< long long to abs */

/**
 * Count trailing zeros of a 32-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ(0x00000001) =  0
 *   VTSS_OS_CTZ(0x80000000) = 31
 *   VTSS_OS_CTZ(0x00000000) >= 32 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 32).
 *
 * __builtin_ctz() is included in GCC 3.2.2 and later according to http://en.wikipedia.org/wiki/Find_first_set.
 */
#define VTSS_OS_CTZ(val32) <your impl>

/**
 * Count trailing zeros of a 64-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ64(0x00000000_00000001) =  0
 *   VTSS_OS_CTZ64(0x00000000_80000000) = 31
 *   VTSS_OS_CTZ64(0x00000001_00000000) = 32
 *   VTSS_OS_CTZ64(0x80000000_00000000) = 63
 *   VTSS_OS_CTZ64(0x00000000_00000000) >= 64 (if result is taken as unsigned; Most implementations return -1, and (u32)(-1) >= 64).
 */
#define VTSS_OS_CTZ64(val64) <your impl>

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
#define VTSS_OS_MALLOC(size, flags) <your impl>

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
#define VTSS_OS_FREE(ptr, flags) <your impl>

/**
 * Wrap of call to rand() defined in stdlib.h
 */
#define VTSS_OS_RAND() <your impl>

