// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_util.h"
#include "vtss_state.h"

#define BPC 8U /* Bits per (unsigned) char */

/* The functions below operate on an array of u32 words of data.
   These data are stored according to the CPU endianness.
   The endianness affects the mapping from a given bit to corresponding byte
   offset. */
#ifdef VTSS_OS_BIG_ENDIAN
#define BYTE_OFFSET(offset) (((offset) / BPC) + 3U - 2U * (((offset) / BPC) % 4U))
#else
#define BYTE_OFFSET(offset) ((offset) / BPC)
#endif /* VTSS_OS_BIG_ENDIAN */

/*
 * Get bit
 */
u8 vtss_bs_bit_get(const void *vptr, u32 offset)
{
    u32 boff = BYTE_OFFSET(offset);
    u8  mask = (u8)VTSS_BIT(offset % BPC);
    return ((const u8 *)vptr)[boff] & mask;
}

/*
 * Set bit
 */
void vtss_bs_bit_set(void *vptr, u32 offset, u8 value)
{
    u32 boff = BYTE_OFFSET(offset);
    u8 *cptr = vptr;
    u8  mask = (u8)VTSS_BIT(offset % BPC);
    if (value > 0U) {
        cptr[boff] |= mask;
    } else {
        cptr[boff] &= ~mask;
    }
}

/*
 * Set byte (or part of) at aligned byte offset
 */
static void bs_byte_set(u8 *cptr, u32 offset, u32 len, u8 value)
{
    u32 boff = BYTE_OFFSET(offset);
    u8  mask = (u8)VTSS_BITMASK(len);
    cptr[boff] = (cptr[boff] & ~mask) | (value & mask);
}

void vtss_bs_set(void *vptr, u32 offset, u32 len, u32 value)
{
    u8 *cptr = vptr;
    while (len > 0U) {
        /* Get Easy case - byte aligned */
        if (len > 1U && (offset % BPC) == 0U) {
            unsigned int niblen = MIN(BPC, len);
            bs_byte_set(cptr, offset, niblen, (u8)value);
            len -= niblen;
            offset += niblen;
            value >>= niblen;
        } else {
            /* Work bit by bit */
            vtss_bs_bit_set(cptr, offset, (value & 1U) > 0U ? 1U : 0U);
            offset++;
            len--;
            value >>= 1;
        }
    }
}

u32 vtss_bs_get(const void *vptr, u32 offset, u32 len)
{
    const u8 *cptr = vptr;
    u32       value = 0U;
    offset += len; /* We work backwards when extracting */
    while (len > 0U) {
        /* Work bit by bit */
        value <<= 1;
        if (vtss_bs_bit_get(cptr, --offset) > 0U) {
            value++;
        }
        len--;
    }
    return value;
}

u8 vtss_bool8_to_u8(BOOL *array)
{
    u8 i, value = 0, mask = 1;

    for (i = 0; i < 8U; i++) {
        if (array[i]) {
            value |= mask;
        }
        mask <<= 1;
    }
    return value;
}

void vtss_u8_to_bool8(u8 value, BOOL *array)
{
    u8 i, mask = 1;

    for (i = 0; i < 8U; i++) {
        if ((value & mask) > 0U) {
            array[i] = TRUE;
        } else {
            array[i] = FALSE;
        }
        mask <<= 1;
    }
}

u32 vtss_u16_get(const u8 *p)
{
    u32 x = p[0];

    x <<= 8;
    x += p[1];
    return x;
}

u32 vtss_u24_get(const u8 *p)
{
    u32 x = vtss_u16_get(p);

    x <<= 8;
    x += p[2];
    return x;
}

u32 vtss_u32_get(const u8 *p)
{
    u32 x = vtss_u24_get(p);

    x <<= 8;
    x += p[3];
    return x;
}

#if defined(VTSS_OPSYS_LINUX)

__attribute__((weak)) void *vtss_os_malloc(size_t size, vtss_mem_flags_t flags)
{
    return malloc(size);
}

__attribute__((weak)) void vtss_os_free(void *ptr, vtss_mem_flags_t flags) { free(ptr); }

__attribute__((weak)) uintptr_t vtss_os_cpu_to_dma_addr(void *ptr) { return 0; }

__attribute__((weak)) void vtss_os_nsleep(u32 nsec)
{
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = (long)nsec;
    while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {
    }
}

__attribute__((weak)) void vtss_os_msleep(u32 msec)
{
    struct timespec ts;
    u32             sec = (msec / 1000U);
    u32             nsec = ((msec % 1000U) * 1000000U);
    ts.tv_sec = (time_t)sec;
    ts.tv_nsec = (long)nsec;
    while (nanosleep(&ts, &ts) == -1 && errno == EINTR) {
    }
}

#endif
