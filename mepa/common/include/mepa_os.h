// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_OS_H_
#define _MEPA_OS_H_

// These files must ensure that the common stdint types (uint8_t, ...) and the
// short (u8, ...) types are defined.
// These types must be binary compatible (safe to cast!)
// u8 must be printable using "%hhu"
// u16 must be printable using "%hu"
// u32 must be printable using "%u"
// u64 must be printable using "%llu"
// i8 must be printable using "%hhd"
// i16 must be printable using "%hd"
// i32 must be printable using "%d"
// i64 must be printable using "%lld"

//
// MEPA_OPSYS_PLATFORM:
//	os_platform is OS agnostic environment of Trafford family.
//	It is based on POSIX and provides APIs and framework regardless of
//	Linux or FreeRTOS.
//

#if defined(MEPA_OPSYS_LMSTAX)
 #include <mepa_os_lmstax.h>
#elif defined(MEPA_OPSYS_PLATFORM)
 #include <mepa_os_platform.h>
#else
 #include <mepa_os_linux.h>
#endif

static inline u64 to_u64(uint64_t i) { return (u64)i; }
static inline u32 to_u32(uint32_t i) { return (u32)i; }
static inline u16 to_u16(uint16_t i) { return (u16)i; }
static inline u8  to_u8( uint8_t i)  { return (u8)i; }

static inline uint64_t to_uint64_t(uint64_t i) { return (uint64_t)i; }
static inline uint32_t to_uint32_t(uint32_t i) { return (uint32_t)i; }
static inline uint16_t to_uint16_t(uint16_t i) { return (uint16_t)i; }
static inline uint8_t  to_uint8_t(uint8_t i)   { return (uint8_t)i; }


#endif /* _MEPA_OS_H_ */
