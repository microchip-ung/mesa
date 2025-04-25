// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/**
 * \file
 * \brief OS Layer API
 * \details Definitions common to all OS.
 */

#ifndef _VTSS_OS_COMMON_H_
#define _VTSS_OS_COMMON_H_

/**
 * \brief Memory allocation flags.
 *
 * The VTSS API asks the application to
 * allocate dynamic memory for its internal structures
 * through calls to VTSS_OS_MALLOC().
 *
 * The application should normally just associate
 * this with a call to malloc() or kmalloc()
 * depending on the OS and the runtime model (API running
 * in Kernel or User space).
 *
 * The VTSS_MEM_FLAGS_DMA flag indicates that the memory needs to be
 * contiguous in physical address space so that it can be used by a
 * DMA. This physical address is possibly different than the CPU
 * address and can be retrieved with VTSS_OS_CPU_TO_DMA_ADDR().
 * The OS must guarantee that caching is disabled for the whole memory
 * chunk allocated.
 *
 * Also, to be able to support warm restart, another
 * enumeration, VTSS_MEM_FLAGS_PERSIST, tells
 * the application to allocate the memory in a part
 * of RAM that won't be affected by a subsequent boot.
 *
 * VTSS_OS_MALLOC() must not block or make waiting points
 * if called with flags != VTSS_MEM_FLAGS_NONE.
 *
 * Each of the enumerations are ORed together to form
 * the final flags that are used in a call to VTSS_OS_MALLOC().
 *
 * The same set of flags are used in calls to VTSS_OS_FREE().
 */
typedef enum {
    VTSS_MEM_FLAGS_NONE = 0x0,    /**< Allocate normally according to runtime model
                                     (User or Kernel space). */
    VTSS_MEM_FLAGS_DMA = 0x1,     /**< Allocate memory that can be used with a DMA. */
    VTSS_MEM_FLAGS_PERSIST = 0x2, /**< Allocate memory that will survive a warm restart. */
} vtss_mem_flags_t;

#endif
