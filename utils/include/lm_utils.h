// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_H
#define LM_UTILS_H

#include <stddef.h>
#include <stdint.h>
#if !defined(LMU_BOOL_IS_UINT8)
#include <stdbool.h>
#endif
#include <lm_utils_pp.h>
#include <lm_utils_memcmp.h>
#include <lm_utils_memcpy.h>
#include <lm_utils_memmove.h>
#include <lm_utils_memset.h>

#ifdef LMU_DEBUG
#include <assert.h>
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(LMU_BOOL_IS_UINT8)
typedef uint8_t lmu_bool_t;
#define LMU_FALSE 0
#define LMU_TRUE  1
#else
typedef bool lmu_bool_t;
#define LMU_FALSE false
#define LMU_TRUE  true
#endif

#ifdef LMU_DEBUG

#define LMU_DEBUG_ONLY(statement) statement
#define LMU_PRINTF(fmt, ...)                                                   \
    {                                                                          \
        lmu_ss_t     ss;                                                       \
        lmu_str128_t s128;                                                     \
        lmu_ss_init_str128(&s128, &ss);                                        \
        LMU_SS_FMT(&ss, fmt, ##__VA_ARGS__);                                   \
        ssize_t res = write(1, ss.buf.begin, ss.sslength);                     \
        (void)res;                                                             \
    }

#define LMU_ASSERT(condition)                                                  \
    if (!(condition)) {                                                        \
        LMU_PRINTF("ASSERTION FAILED: file = %s, line = %d\n", __FILE__,       \
                   __LINE__);                                                  \
        assert(0);                                                             \
        while (1)                                                              \
            ;                                                                  \
    }

#else // LMU_DEBUG

#define LMU_DEBUG_ONLY(statement)
#define LMU_PRINTF(_fmt, ...)
#define LMU_ASSERT(condition)

#endif // LMU_DEBUG

// High-frequence, low risk assert macros. Not enabled on target
#define LMU_ASSERT2(expr)

#define RC_ASSERT(condition)                                                   \
    if (!(condition)) {                                                        \
        LMU_ASSERT(0);                                                         \
        return LM_RC_ERROR;                                                    \
    }

#define RC(expr)                                                               \
    {                                                                          \
        lm_rc_t __rc = (expr);                                                 \
        if (__rc != LM_RC_OK) {                                                \
            return __rc;                                                       \
        }                                                                      \
    }

// The purpose of this structure is to avoid LMU_FALSE positive reporting in
// Coverity implementation of MISRA Rule 20.7
#define LMU_TYPE_TO_PTR(type) __typeof__(__typeof__(type) *)

#define LMU_ALIGN(x, a)         LMU_ALIGN_MASK(x, (typeof(x))(a)-1U)
#define LMU_ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))

#define LMU_ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

#define LMU_OFFSET_OF(type, member) __builtin_offsetof(type, member)

#define LMU_CONTAINER_OF(ptr, type, member)                                    \
    ((LMU_TYPE_TO_PTR(type))((void *)(ptr)-LMU_OFFSET_OF(type, member)))

#define LMU_SIZE_OF_MEMBER(type, member) (sizeof(((type *)0)->member))

#define LMU_BIT(x) ((uint32_t)1U << (x))

#define LM_VID_MAX_VALUE 0xFFFU
typedef uint16_t lm_vid_t;

typedef struct {
    uint8_t data[4];
} lm_ipv4_t;

typedef struct {
    lm_ipv4_t ipv4;
    uint8_t   prefix;
} lm_ipv4_prefix_t;

typedef struct {
    uint8_t data[16];
} lm_ipv6_t;

typedef struct {
    lm_ipv6_t ipv6;
    uint8_t   prefix;
} lm_ipv6_prefix_t;

typedef struct {
    uint8_t data[6];
} lm_mac_t;

typedef uint8_t lm_portno_t;
typedef uint8_t lm_aggr_t;

typedef struct {
    uint8_t private_[4];
} lm_port_list_t;

typedef struct {
    uint32_t *begin;
    uint32_t *end;
    uint32_t  cap;
} lm_uint_list_t;

typedef int32_t lm_rc_t;

#define LM_RC_OK            (0)
#define LM_RC_ERROR         (-1)
#define LM_RC_TIMEOUT       (-2)
#define LM_RC_OUT_OF_MEMORY (-3)
#define LM_RC_EXIST         (-4)
#define LM_RC_BUSY          (-5)
#define LM_RC_INCOMPLETE    (-6)
#define LM_RC_NOT_FOUND     (-7)
#define LM_RC_NO_MORE       (-8)
#define LM_RC_NOT_ALLOWED   (-9)

lmu_bool_t lmu_isspace(char c);
lmu_bool_t lmu_isdigit(char c);
lmu_bool_t lmu_isxdigit(char c);
lmu_bool_t lmu_islower(char c);
lmu_bool_t lmu_isupper(char c);

size_t lmu_ptrdiff_to_size_t(const void *a, const void *b);

void       *lmu_memchr(void *ptr, int ch, size_t n);
const void *lmu_memchr_const(const void *ptr, int ch, size_t n);

#define LMU_ZERO_SET(object) lmu_memset(&(object), 0, sizeof(object))

uint16_t lmu_htons(uint16_t hostshort);
uint16_t lmu_ntohs(uint16_t netshort);
uint32_t lmu_htonl(uint32_t hostlong);
uint32_t lmu_ntohl(uint32_t netlong);
uint64_t lmu_hton64(uint64_t hostlong);
uint64_t lmu_ntoh64(uint64_t netlong);

lmu_bool_t lmu_vid_valid(lm_vid_t vid);

int        lmu_mac_cmp(const lm_mac_t *const a, const lm_mac_t *const b);
lmu_bool_t lmu_mac_equal(const lm_mac_t *const a, const lm_mac_t *const b);
lmu_bool_t lmu_mac_is_null(const lm_mac_t *const m);
lmu_bool_t lmu_mac_is_bcast(const lm_mac_t *const m);

void lmu_mac_set_null(lm_mac_t *const m);
void lmu_mac_set_bcast(lm_mac_t *const m);

void lmu_mac_copy(const lm_mac_t *const src, lm_mac_t *const dst);

int        lmu_ipv4_cmp(const lm_ipv4_t *const a, const lm_ipv4_t *const b);
lmu_bool_t lmu_ipv4_equal(const lm_ipv4_t *const a, const lm_ipv4_t *const b);
lmu_bool_t lmu_ipv4_is_null(const lm_ipv4_t *const m);
void       lmu_ipv4_set_null(lm_ipv4_t *const m);
void       lmu_ipv4_copy(const lm_ipv4_t *const src, lm_ipv4_t *const dst);
uint8_t    lmu_ipv4_mask2prefix(uint32_t mask);

lmu_bool_t lmu_ipv4_prefix_equal(const lm_ipv4_prefix_t *const a,
                                 const lm_ipv4_prefix_t *const b);

void    lmu_port_list_clear(lm_port_list_t *port_list);
void    lmu_port_list_set(lm_port_list_t *port_list, uint8_t port, uint8_t val);
uint8_t lmu_port_list_get(lm_port_list_t *port_list, uint8_t port);

lm_rc_t lmu_uintlist_push(lm_uint_list_t *list, uint32_t val);
int     lmu_uintlist_cmp(const lm_uint_list_t *const a,
                         const lm_uint_list_t *const b);

size_t lmu_czstrlen(const char *s);
size_t lmu_czstrnlen(const char *s, size_t maxlen);
void   lmu_czstrcpy(char *ds, const char *ss);

size_t lmu_czstrspn(const char *s, const char *accept);
size_t lmu_czstrcspn(const char *s, const char *reject);

const char *lmu_czstrchr(const char *s, int c);
const char *lmu_czstrrchr(const char *s, int c);

// Fixed length string buffers. These types are used to store strings variable
// size, from zero length up to the full capacity of the buffer. Strings smaller
// than the capacity of the buffer shall be null terminated. If the string
// length is equal to the capacity of the buffer, then no null termination will
// be used.
typedef struct {
    char data[4];
} lmu_str4_t;

typedef struct {
    char data[8];
} lmu_str8_t;

typedef struct {
    char data[16];
} lmu_str16_t;

typedef struct {
    char data[32];
} lmu_str32_t;

typedef struct {
    char data[64];
} lmu_str64_t;

typedef struct {
    char data[128];
} lmu_str128_t;

typedef struct {
    char data[256];
} lmu_str256_t;

// Variable length string type. Should only be used temporary (do not put in
// state variable).
// Purpose of this type is to provide an abstraction of the fixed length
// strings.
typedef struct {
    char *begin;
    char *end;
} lmu_str_t;

typedef struct {
    const char *begin;
    const char *end;
} lmu_cstr_t;

lmu_cstr_t lmu_czstr_to_cstr(const char *cstr);

int lmu_czstrcmp(const char *s1, const char *s2);
int lmu_cbe_cbe_cmp(const char *a_begin, const char *a_end, const char *b_begin,
                    const char *b_end);
int lmu_str_cmp(const lmu_str_t *a, const lmu_str_t *b);
int lmu_cstr_cmp(const lmu_cstr_t *a, const lmu_cstr_t *b);
int lmu_cbe_czstr_cmp(const char *a_begin, const char *a_end, const char *b);
int lmu_cstr_czstr_cmp(const lmu_cstr_t *a, const char *b);
int lmu_str_czstr_cmp(const lmu_str_t *a, const char *b);

// Capacity of string
size_t lmu_cbe_cap(const char *begin, const char *end);
size_t lmu_cstr_cap(const lmu_cstr_t *s);
size_t lmu_str_cap(const lmu_str_t *s);

// Copy leading first MIN(lmu_str_len(src), lmu_str_cap(dst)) chars from src to
// dest. If lmu_str_len(src) > lmu_str_cap(dst), set the overflow flag.
// Return number of bytes copied.
size_t lmu_cbe_copy(lmu_str_t *dst, const char *src_begin, const char *src_end,
                    int *overflow);
size_t lmu_cstr_copy(lmu_str_t *dst, const lmu_cstr_t *src, int *overflow);
size_t lmu_str_copy(lmu_str_t *dst, const lmu_str_t *src, int *overflow);

// Returns a czstring which is guaranteed to be null terminated. If the input
// string uses the full capacity of the buffer, then the last byte is replaced
// with a \0 char.
// The implementation shall always change the last char in the data buffer to be
// '\0'.
char *lmu_str_to_czstr_trunk(lmu_str_t *str);

// Returns a czstring which is guaranteed to be null terminated - or a null-ptr.
// If the input string uses the full capacity of the buffer, then return
// null-ptr.
char *lmu_str_to_czstr(lmu_str_t *str);

// Returns the string length of s. The length is defined as the number of
// none NULL leading chars in 'data' and never more than the capacity of the
// string.
size_t lmu_cbe_len(const char *begin, const char *end);
size_t lmu_cstr_len(const lmu_cstr_t *s);
size_t lmu_str_len(const lmu_str_t *s);

// Utility functions to initialize the lmu_str_t types. These functions shall
// never change the content of the input buffer, but only fill the 'data'
// pointer and the 'data_size' based on the capacity of the given type.
void lmu_str_init_str4(lmu_str4_t *in, lmu_str_t *out);
void lmu_str_init_str8(lmu_str8_t *in, lmu_str_t *out);
void lmu_str_init_str16(lmu_str16_t *in, lmu_str_t *out);
void lmu_str_init_str32(lmu_str32_t *in, lmu_str_t *out);
void lmu_str_init_str64(lmu_str64_t *in, lmu_str_t *out);
void lmu_str_init_str128(lmu_str128_t *in, lmu_str_t *out);
void lmu_str_init_str256(lmu_str256_t *in, lmu_str_t *out);

// Same as above but with const data for read-only.
void lmu_cstr_init_str4(const lmu_str4_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str8(const lmu_str8_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str16(const lmu_str16_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str32(const lmu_str32_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str64(const lmu_str64_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str128(const lmu_str128_t *in, lmu_cstr_t *out);
void lmu_cstr_init_str256(const lmu_str256_t *in, lmu_cstr_t *out);

// String stream type. Allowing to build strings by appending content to a
// buffer.
typedef struct {
    lmu_str_t buf;
    int       overflow;
    uint32_t  sslength; // Do not use size_t, as we do not need this to be
                        // 64bit on 64bit platforms.
} lmu_ss_t;

// Utility function to initialize a 'lmu_ss_t' using a string buffer as storage
// backend. These functions never changes the input buffer.
// Requirements:
// - 'buf' member shall be initialized using the lmu_str_init_<TYPE> function
// - 'overflow' is set to zero,
// - 'strlen' shall be initialized using 'lmu_strnlen' where
void lmu_ss_init_str4(lmu_str4_t *in, lmu_ss_t *out);
void lmu_ss_init_str8(lmu_str8_t *in, lmu_ss_t *out);
void lmu_ss_init_str16(lmu_str16_t *in, lmu_ss_t *out);
void lmu_ss_init_str32(lmu_str32_t *in, lmu_ss_t *out);
void lmu_ss_init_str64(lmu_str64_t *in, lmu_ss_t *out);
void lmu_ss_init_str128(lmu_str128_t *in, lmu_ss_t *out);
void lmu_ss_init_str256(lmu_str256_t *in, lmu_ss_t *out);

size_t lmu_ss_cap(lmu_ss_t *ss);

lmu_cstr_t lmu_ss_to_cstr(const lmu_ss_t *ss);

// Return a pointer guarnteed to be null-terminated. This may truncate the
// string if full capacity is used.
const char *lmu_ss_czstr_trunk(lmu_ss_t *ss);

// Fixed length binary string buffers. Number of bytes in use are indicated by
// the length field.
typedef struct {
    uint8_t length;
    uint8_t data[4];
} lmu_bin4_t;

typedef struct {
    uint8_t length;
    uint8_t data[16];
} lmu_bin16_t;

typedef struct {
    uint8_t length;
    uint8_t data[32];
} lmu_bin32_t;

typedef struct {
    uint8_t length;
    uint8_t data[64];
} lmu_bin64_t;

typedef struct {
    uint16_t length;
    uint8_t  data[256];
} lmu_bin256_t;

typedef struct {
    uint16_t length;
    uint8_t  data[512];
} lmu_bin512_t;

// Variable length binary string type. Should only be used temporary (do not put
// in state variable).
// Purpose of this type is to provide an abstraction of the fixed length
// binary strings.
typedef struct {
    uint8_t *begin;
    uint8_t *end;
} lmu_bin_t;

typedef struct {
    const uint8_t *begin;
    const uint8_t *end;
} lmu_cbin_t;

// Capacity of binary string
size_t lmu_cbe_bin_cap(const uint8_t *begin, const uint8_t *end);
size_t lmu_cbin_cap(const lmu_cbin_t *s);
size_t lmu_bin_cap(const lmu_bin_t *s);

void lmu_cbin_init_bin32(const lmu_bin32_t *in, lmu_cbin_t *out);
void lmu_bin_init_bin32(lmu_bin32_t *in, lmu_bin_t *out);
void lmu_cbin_init_bin64(const lmu_bin64_t *in, lmu_cbin_t *out);
void lmu_bin_init_bin64(lmu_bin64_t *in, lmu_bin_t *out);

// Copy leading first lmu_bin_cap(dst) chars from src to
// dest. If lmu_bin_cap(src) > lmu_bin_cap(dst), set the overflow flag.
// Return number of bytes copied.
size_t lmu_cbe_bin_copy(lmu_bin_t *dst, const uint8_t *src_begin,
                        const uint8_t *src_end, int *overflow);
size_t lmu_cbin_copy(lmu_bin_t *dst, const lmu_cbin_t *src, int *overflow);
size_t lmu_bin_copy(lmu_bin_t *dst, const lmu_bin_t *src, int *overflow);

int lmu_cbin_cmp(const lmu_cbin_t *a, const lmu_cbin_t *b);

#define LMU_FMT_FLAG_NONE       0x00u
#define LMU_FMT_FLAG_PAD_ZERO   0x01u
#define LMU_FMT_FLAG_PAD_SPACE  0x02u
#define LMU_FMT_FLAG_SIGN_FORCE 0x08u
#define LMU_FMT_FLAG_SIGN_SPACE 0x10u

typedef enum {
    LMU_FMT_LENMOD_NONE,
    LMU_FMT_LENMOD_HH, // 8bit-value
    LMU_FMT_LENMOD_H,  // 16bit-value
    LMU_FMT_LENMOD_L,  // 32bit-value
    LMU_FMT_LENMOD_LL, // 64bit-value
    LMU_FMT_LENMOD_Z,  // size_t size
    LMU_FMT_LENMOD_T,  // ptrdiff
} lmu_fmt_lenmod_t;

typedef enum {
    LMU_FMT_CONV_DEC_SIGNED,
    LMU_FMT_CONV_DEC_UNSIGNED,
    LMU_FMT_CONV_HEX_LC,
    LMU_FMT_CONV_HEX_UC,
    LMU_FMT_CONV_CHAR,
    LMU_FMT_CONV_CZSTR,
} lmu_fmt_conv_t;

typedef struct lmu_fmt {
    uint8_t          lmu_fmt_flag;
    lmu_fmt_lenmod_t len  : 8;
    lmu_fmt_conv_t   conv : 8;
    uint8_t          width;
} lmu_fmt_t;

// IMPORTANT: This is not using sprintf/va_args based formatting, but it
// uses the C11 _Generic keyword to implement something which is _enough_
// comparable with sprintf, but type-safe, and easy to extend with custom types.
//
// Unlike printf, the conversion argument is only used as hints - the compiler
// selects the correct function to handle a given type. It is not a bug to use
// "%s" to format an integer!
//
// Supported formatting:
// %[flags][width][length modifier]conversion
//
// Compatibility with printf and friends:
//
//   Supported flags
//   - '0'
//   - '-'
//   - ' '
//   - '+'
//
//   Supported length modifier
//   - 'hh'
//   - 'h'
//   - 'l'
//   - 'll'
//   - 'z'
//   - 't'
//
//   Conversion
//   - 'd', 'i'  Signed decimal conversion
//   - 'u'       Unsigned decimal conversion
//   - 'x', 'X'  Unsigned hex conversion (lower-case or upper case)
//   - 'c'       Print as char (no length modifier allowed)
//   - 's'       Print czstr (must be null-terminated)
//   - 'p'       Print pointer (no length modifier allowed)
//   - '%'       Print the '%' char
//
//   Not supported:
//   - All unicode/multibyte handling
//   - Float and double (conversion specifier: eEfFgGaA)
//   - Octal conversion: (conversion specifier: o)
//   - Other conversion specifier: 'C', 'S', 'n' and 'm'
//   - Position specific identifier ("%1$")
//   - Runtime length specification ("%*d", width, num)
//   - Flag '\'' to group output numbers with thousands
//   - Flag 'I' to do local specific conversion
//   - Flag '#' trigger alternative representation
//
//   Example:
//    lmu_str32_t s32;
//    lmu_ss_t ss;
//    lm_ipv4_t ipv4;  // assume initialized
//    lm_mac_t mac;    // assume initialized
//    lmu_lm_str4_t s4;    // assume initialized
//    lmu_ss_init_str32(&s32, &ss);
//
//    lmu_ss_fmt(ss, "MAC: %s IP: %-15s", &mac, &ipv4);
//    // "MAC: 01-80-ff-00-00-00 IP: 100.200.300.400"
//
//    lmu_ss_fmt(ss, "String buf4 %s", &strbuf4);

// Basic structure to with the lmu_fmt_* functions assuming that the
// stringstream and string buffers are implemented else-where.
typedef struct {
    size_t      fmt_offset;
    const char *fmt;
    lmu_ss_t   *ss;
} lmu_fmt_state_t;

// An extension of lmu_fmt_state_t with build-in buffers
typedef struct {
    lmu_ss_t        ss;
    lmu_str128_t    buf;
    lmu_fmt_state_t state;
} lmu_fmt_state_buf128_t;

void lmu_fmt_state_buf128_init(lmu_fmt_state_buf128_t *state, const char *fmt);
lmu_bool_t lmu_ss_fmt_next(lmu_fmt_state_t *state, lmu_fmt_t *fmt);
void       lmu_ss_fmt_last(lmu_fmt_state_t *state);
void       lmu_ss_fmt_no_args(lmu_ss_t *ss, const char *fmt);

typedef struct {
    lmu_ss_t     ss;
    lmu_str256_t buf;
    char        *s;
} lmu_fmt_buf_t;

void lmu_fmt_buf_init(lmu_fmt_buf_t *buf);

void lmu_ss_append_czstr(lmu_ss_t *ss, const char *cstr);
void lmu_ss_append_cstr(lmu_ss_t *ss, const lmu_cstr_t *str);
void lmu_ss_append_char(lmu_ss_t *ss, char c);

// clang-format off
// Special handling of bool formating
#if defined(LMU_BOOL_IS_UINT8)
// needs to be empty to avoid clashing wiht uint8_t handler
#define LMU_FMT_GENERIC_BOOL
#else
#define LMU_FMT_GENERIC_BOOL lmu_bool_t : lmu_fmt_bool,
#endif

// Special handling of uintptr_t formating
#if defined(__arm__) && !defined(__linux__)
#define LMU_FMT_GENERIC_UINTPTR uintptr_t : lmu_fmt_i32,
#else
// needs to be empty to avoid clashing wiht uint32_t/uint64_t
#define LMU_FMT_GENERIC_UINTPTR
#endif

// Special handling of unsigned long long formating
#if defined(__aarch64__)
#define LMU_FMT_GENERIC_ULL unsigned long long : lmu_fmt_ull,
#else
// needs to be empty to avoid clashing wiht uint64_t
#define LMU_FMT_GENERIC_ULL
#endif

#define LMU_FMT_GENERIC_COMMON                                                 \
        LMU_FMT_GENERIC_BOOL                                                   \
        LMU_FMT_GENERIC_UINTPTR                                                \
        LMU_FMT_GENERIC_ULL                                                    \
        uint64_t            : lmu_fmt_u64,                                     \
        uint32_t            : lmu_fmt_u32,                                     \
        uint16_t            : lmu_fmt_u16,                                     \
        uint8_t             : lmu_fmt_u8,                                      \
        int64_t             : lmu_fmt_i64,                                     \
        int32_t             : lmu_fmt_i32,                                     \
        int16_t             : lmu_fmt_i16,                                     \
        int8_t              : lmu_fmt_i8,                                      \
        char                : lmu_fmt_char,                                    \
        char *              : lmu_fmt_czstr,                                   \
        const char *        : lmu_fmt_czstr,                                   \
        lmu_str_t *         : lmu_fmt_str,                                     \
        lmu_cstr_t *        : lmu_fmt_cstr,                                    \
        const lmu_cstr_t *  : lmu_fmt_cstr,                                    \
        lmu_fmt_buf_t *     : lmu_fmt_buf,                                    \
        lm_ipv4_t *         : lmu_fmt_ipv4,                                    \
        lm_ipv4_prefix_t *  : lmu_fmt_ipv4_prefix,                             \
        lm_ipv6_t *         : lmu_fmt_ipv6,                                    \
        lm_ipv6_prefix_t *  : lmu_fmt_ipv6_prefix,                             \
        lmu_bin4_t *        : lmu_fmt_bin4,                                    \
        lm_port_list_t *    : lmu_fmt_port_list,                               \
        lm_mac_t *          : lmu_fmt_mac
// clang-format off

#define LMU_FMT_GENERIC(FMT_STATE, X)                                          \
    _Generic((X),                                                              \
        LMU_FMT_GENERIC_COMMON                                                 \
    )((FMT_STATE), (X))

#define LMU_FMT_GENERIC_INNER(FMT_STATE, X) LMU_FMT_GENERIC(FMT_STATE, X);

// Version with 1 or more arguments
#define LMU_SS_FMT1(SS, fmt_str, ...)                                          \
    do {                                                                       \
        lmu_fmt_state_t lmu_fmt_state__ = {                                    \
            .fmt_offset = 0, .fmt = (fmt_str), .ss = (SS)};                    \
        LMU_PP_FOREACH_1ARG(LMU_FMT_GENERIC_INNER, &lmu_fmt_state__,           \
                            ##__VA_ARGS__);                                    \
        lmu_ss_fmt_last(&lmu_fmt_state__);                                     \
    } while (LMU_FALSE)

// Version with 0 or more arguments
#define LMU_SS_FMT0(SS, fmt_str, ...) lmu_ss_fmt_no_args(SS, fmt_str)

#define LMU_SS_FMT(SS, fmt_str, ...)                                           \
    LMU_PP_VA_ARGS_OVERLOAD_ONE_OR_MORE(LMU_SS_FMT, ##__VA_ARGS__)             \
    ((SS), (fmt_str), ##__VA_ARGS__)

void lmu_fmt_bool(lmu_fmt_state_t *state, lmu_bool_t val);
void lmu_fmt_char(lmu_fmt_state_t *state, char val);
void lmu_fmt_cstr(lmu_fmt_state_t *state, const lmu_cstr_t *str);
void lmu_fmt_czstr(lmu_fmt_state_t *state, const char *val);
void lmu_fmt_buf(lmu_fmt_state_t *state, const lmu_fmt_buf_t *buf);
void lmu_fmt_i16(lmu_fmt_state_t *state, int16_t ival);
void lmu_fmt_i32(lmu_fmt_state_t *state, int32_t ival);
void lmu_fmt_i64(lmu_fmt_state_t *state, int64_t ival);
void lmu_fmt_i8(lmu_fmt_state_t *state, int8_t ival);
void lmu_fmt_ipv4(lmu_fmt_state_t *state, const lm_ipv4_t *ip);
void lmu_fmt_ipv4_prefix(lmu_fmt_state_t *state, const lm_ipv4_prefix_t *ip);
void lmu_fmt_ipv6(lmu_fmt_state_t *state, const lm_ipv6_t *ip);
void lmu_fmt_ipv6_prefix(lmu_fmt_state_t *state, const lm_ipv6_prefix_t *ip);
void lmu_fmt_mac(lmu_fmt_state_t *state, const lm_mac_t *mac);
void lmu_fmt_bin4(lmu_fmt_state_t *state, const lmu_bin4_t *bin4);
void lmu_fmt_port_list(lmu_fmt_state_t *state, const lm_port_list_t *pl);
void lmu_fmt_str(lmu_fmt_state_t *state, const lmu_str_t *str);
void lmu_fmt_u16(lmu_fmt_state_t *state, uint16_t val);
void lmu_fmt_u32(lmu_fmt_state_t *state, uint32_t val);
void lmu_fmt_u64(lmu_fmt_state_t *state, uint64_t val);
#if defined(__aarch64__)
void lmu_fmt_ull(lmu_fmt_state_t *state, uint64_t val);
#endif
void lmu_fmt_u8(lmu_fmt_state_t *state, uint8_t val);

typedef size_t (*lmu_parse_t)(const lmu_cstr_t *str, void *data);

typedef struct {
    uint8_t  radix; // default radix 10
    uint8_t  min_digit;
    uint8_t  max_digit;
    uint32_t max_val;
    uint32_t min_val;
    uint32_t val;
} lmu_parse_u32_cxt_t;

size_t lmu_cstr_find_char(lmu_cstr_t *str, char c);
size_t lmu_parse_mac(const lmu_cstr_t *str, lm_mac_t *const mac);
size_t lmu_parse_ipv4(const lmu_cstr_t *str, lm_ipv4_t *const ipv4);
size_t lmu_parse_ipv4_prefix(const lmu_cstr_t *str, lm_ipv4_prefix_t *const ip);
size_t lmu_parse_ipv6(const lmu_cstr_t *str, lm_ipv6_t *const ip);
size_t lmu_parse_ipv6_prefix(const lmu_cstr_t *str, lm_ipv6_prefix_t *const ip);
size_t lmu_parse_u32(const lmu_cstr_t *str, lmu_parse_u32_cxt_t *cxt);
size_t lmu_parse_flag(const lmu_cstr_t *str, const char *flags);
size_t lmu_parse_flag_(const lmu_cstr_t *str, void *cxt);
size_t lmu_parse_flags(const lmu_cstr_t *str, const char *flags);
size_t lmu_parse_flags_(const lmu_cstr_t *str, void *cxt);
size_t lmu_parse_fmt(const lmu_cstr_t *str, lmu_fmt_t *cxt);
size_t lmu_parse_fmt_(const lmu_cstr_t *str, void *cxt);

typedef enum {
    LMU_STR_SPLIT_END = 0,
    LMU_STR_SPLIT_TOKEN = 1,
    LMU_STR_SPLIT_DELIM = 2,
} lmu_str_split_t;

// Split a string into a sequence of (possible empty) sub-strings and
// delimeters. The delimitor is represented by a parser. If the parse matches
// more than 0 of the beginning of the string, then it will be interperted as a
// delimitor.
// 'out' is always set to value of matched string.
// return 0 on empty string.
// return 1 on non-delimitor match
// return 2 on delimitor match
//
// Example: Iterate through a comma seperated string
//    while ((res = lmu_str_split(&in, &lmu_parse_flag_, ",", &out))) {
//        if (res == 1) {
//           // use-value
//        }
//        in.begin = out.end;
//    }
lmu_str_split_t lmu_cstr_split(const lmu_cstr_t *in, lmu_parse_t delim,
                               void *delim_cxt, lmu_cstr_t *out);

lmu_bool_t lmu_isprint(char c);

typedef struct {
    lm_rc_t  rc;
    uint32_t line;
} lm_rca_t;

void lmu_rca(uint32_t line, lm_rca_t *rca, lm_rc_t rc);
#define LM_RCA(rc) lmu_rca(__LINE__, &rca, rc);

uint32_t lmu_inet_chksum32(const uint8_t *data, uint32_t length);
uint16_t lmu_inet_chksum(uint32_t sum, const uint8_t *data, uint32_t length);

// Data get utilities
uint16_t lmu_data_u16_get(const uint8_t *data);
uint32_t lmu_data_u32_get(const uint8_t *data);
void     lmu_data_ipv4_get(uint8_t *data, lm_ipv4_t *val);
void     lmu_data_mac_get(uint8_t *data, lm_mac_t *val);

// Data put utilities
void lmu_data_u16_put(uint8_t *data, uint16_t val);
void lmu_data_u32_put(uint8_t *data, uint32_t val);
void lmu_data_ipv4_put(uint8_t *data, lm_ipv4_t *val);
void lmu_data_mac_put(uint8_t *data, lm_mac_t *val);

/************* FRAME UTILITIES *****************/

#define LMU_FRAME_MAX_LAYER_COUNT (6)
#define LMU_FRAME_MAX_SIZE        (1518U)

#define LMU_PHC_CNT (3U)

// VLAN tag
typedef struct {
    uint16_t   etype;         // Ethernet Type
    uint8_t    pcp;           // Priority Code Point
    uint8_t    dei;           // Drop Eligible Indicator
    lm_vid_t   vid;           // VLAN ID
    lmu_bool_t popped;        // Tag was popped
    lmu_bool_t type_mismatch; // Frame type mismatch
    lmu_bool_t vid_mismatch;  // VLAN membership mismatch
} lmu_frame_vlan_tag_t;

// Timestamp with fractional nanosecond
typedef struct {
    uint64_t sec;      // Seconds
    uint32_t nsec;     // Nanoseconds
    uint16_t nsecfrac; // 16 bit fraction of nano seconds
} lmu_timestamp_t;

// Rx frame information
typedef struct {
    lm_portno_t          port;                   // Ingress port
    uint16_t             length;                 // Packet length
    lmu_frame_vlan_tag_t tag;                    // VLAN tag
    lmu_timestamp_t      timestamp[LMU_PHC_CNT]; // timestamp in ns for each
                                                 // hardware physical clock
} lmu_frame_rx_info_t;

// Tx frame information
typedef struct {
    lmu_bool_t           switch_frame; // Switched or port transmission
    lm_portno_t          port;         // Egress port (if not switched)
    lmu_frame_vlan_tag_t tag;          // VLAN tag information
} lmu_frame_tx_info_t;

typedef enum {
    LMU_FRAME_PROTO_UNUSED = 0, /* must be lowest before real protocol IDs */

    LMU_FRAME_PROTO_ETH,
    LMU_FRAME_PROTO_MUP1,

    LMU_FRAME_PROTO_ARP,
    LMU_FRAME_PROTO_LLDP,

    LMU_FRAME_PROTO_IPV4,

    LMU_FRAME_PROTO_IP_DATA, // Generic IP protocol for unit-test
    LMU_FRAME_PROTO_ICMP,
    LMU_FRAME_PROTO_UDP,

    LMU_FRAME_PROTO_UDP_DATA, // Generic UDP protocol for unit-test
    LMU_FRAME_PROTO_DTLS_RECORD,
    LMU_FRAME_PROTO_DTLS_RECORD_PAYLOAD = LMU_FRAME_PROTO_DTLS_RECORD + 1,
    LMU_FRAME_PROTO_DTLS_HANDSHAKE = LMU_FRAME_PROTO_DTLS_RECORD_PAYLOAD,
    LMU_FRAME_PROTO_DTLS_HANDSHAKE_PAYLOAD,
    // LMU_FRAME_PROTO_DTLS_HANDSHAKE_HEADER,
    // LMU_FRAME_PROTO_DTLS_HANDSHAKE_BODY,
    LMU_FRAME_PROTO_DTLS_PRIV,
    LMU_FRAME_PROTO_COAP,
    LMU_FRAME_PROTO_DHCP,

    LMU_FRAME_PROTO_COUNT, /* must be last, to support range checking */
} lmu_frame_proto_t;

typedef struct {
    lmu_frame_proto_t protocol : 8;
    uint16_t          length;
    uint8_t          *data;
} lmu_frame_layer_t;

typedef enum {
    lmu_frame_state_free = 0, // used to indicate frame free in pool
    lmu_frame_state_rx,
    lmu_frame_state_tx,
} lmu_frame_state_t;

typedef struct {
    lmu_frame_state_t state;
    union {
        lmu_frame_rx_info_t rx_info;
        lmu_frame_tx_info_t tx_info;
    };

    lmu_frame_layer_t layers[LMU_FRAME_MAX_LAYER_COUNT];

    /* frame_data: real storage for frame data */
    uint8_t frame_data[LMU_FRAME_MAX_SIZE];
} lmu_frame_t;

#define LMU_FRAME_DIR_CHECK(frame, dir) LMU_ASSERT((frame)->state == (dir))

// Reset the frame to its newly allocated state.
void lmu_frame_reset_rx(lmu_frame_t *frame);
void lmu_frame_reset_tx(lmu_frame_t *frame);

// Check if a frame layer exists
lmu_bool_t lmu_frame_layer_exists(lmu_frame_t      *frame,
                                  lmu_frame_proto_t protocol);

// returns the base frame buffer. The size is LMU_FRAME_MAX_SIZE
uint8_t *lmu_frame_buf_get(lmu_frame_t *frame);

// Adds a new layer region to the frame.
lm_rc_t lmu_frame_add_existing_layer(lmu_frame_t      *frame,
                                     lmu_frame_proto_t protocol, uint8_t *data,
                                     uint16_t length);

// returns LMU_TRUE if test_protocol is present in the frame, LMU_FALSE
// otherwise.
lmu_bool_t lmu_frame_protocol_exists(lmu_frame_t      *frame,
                                     lmu_frame_proto_t test_protocol);

// Read data from a specified location with in a protocol's region.
lm_rc_t lmu_frame_data_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                            uint16_t starting_offset, uint8_t *destination,
                            uint16_t length);

// Write data to a specified location with in a protocol's region
lm_rc_t lmu_frame_data_write(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                             uint16_t starting_offset, uint8_t *src,
                             uint16_t length);

// Read a uint8_t from a specified offset with in a protocol's region
lm_rc_t lmu_frame_u8_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                          uint16_t offset, uint8_t *destination);

// Read a uint16_t from a specified offset with in a protocol's region.
lm_rc_t lmu_frame_u16_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                           uint16_t offset, uint16_t *destination);

// Gets the data pointer and length of the specified protocol region
void lmu_frame_layer_region_get(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                                uint8_t **data, uint16_t *length);

// Pushes a new layer on to the layer stack. No actual data is added to the
//   frame by this function. This function simply marks the beginning of the
//   new protocol region.
lm_rc_t lmu_frame_layer_push(lmu_frame_t *frame, lmu_frame_proto_t protocol);

// Pushes new data into the frame, at the specified layer.
// Lower layers are also expanded, higher layers are not.
lm_rc_t lmu_frame_proto_data_push(lmu_frame_t      *frame,
                                  lmu_frame_proto_t protocol, uint8_t *source,
                                  uint16_t length);

// Pushes new data into the frame. Data is pushed into the highest layer.
//   All lower layers will be expanded to accomodate the expansion of the
//   highest protocol layer
lm_rc_t lmu_frame_data_push(lmu_frame_t *frame, uint8_t *source,
                            uint16_t length);

// pushes a byte to the frame.
lm_rc_t lmu_frame_u8_push(lmu_frame_t *frame, uint8_t value);

// Pushes a uint16_t to the frame.
// Interally does endian conversion if necessary.
lm_rc_t lmu_frame_u16_push(lmu_frame_t *frame, uint16_t value);

// Pushes the lower 24 bits of uint32_t to the frame
// Internally does endian conversion if necessary.
lm_rc_t lmu_frame_u24_push(lmu_frame_t *frame, uint32_t value);

// Pushes a uint32_t to the frame.
// Internally does endian conversion if necessary
lm_rc_t lmu_frame_u32_push(lmu_frame_t *frame, uint32_t value);

// Pushes the least significant 48 bit of a uint64_t to the frame.
// Internally does endian conversion if necessary
lm_rc_t lmu_frame_u48_push(lmu_frame_t *frame, uint64_t value);

// Pushes a 6 byte buffer to the frame
lm_rc_t lmu_frame_u48_data_push(lmu_frame_t *frame, uint8_t *data);

// dump frame to debug console
void lmu_frame_dump(lmu_frame_t *frame);

// gets the destination mac address from the ethernet header
lm_rc_t lmu_eth_dmac_get(lmu_frame_t *frame, lm_mac_t *dmac);

// gets the source mac address from the ethernet header
lm_rc_t lmu_eth_smac_get(lmu_frame_t *frame, lm_mac_t *smac);

// gets the ether type field from the ethernet header
lm_rc_t lmu_eth_etype_get(lmu_frame_t *frame, uint16_t *etype);

// pushes ethernet header to frame
lm_rc_t lmu_eth_header_push(lmu_frame_t *frame, lm_mac_t dmac, lm_mac_t smac,
                            uint16_t etype);

// gets the source ip address from the ipv4 header
lm_rc_t lmu_ipv4_sip_get(lmu_frame_t *frame, lm_ipv4_t *addr);

// gets the destination ip address from the ipv4 header
lm_rc_t lmu_ipv4_dip_get(lmu_frame_t *frame, lm_ipv4_t *addr);

// gets the protocol field from the ipv4 header
lm_rc_t lmu_ipv4_protocol_get(lmu_frame_t *frame, uint8_t *protocol);

// pushes ipv4 header to frame
lm_rc_t lmu_ipv4_header_push(lmu_frame_t *frame, lm_ipv4_t sip, lm_ipv4_t dip,
                             uint8_t protocol);

// calculates the ipv4 header checksum
lm_rc_t lmu_ipv4_checksum(lmu_frame_t *frame, lmu_bool_t check);

// update length and checksum to make frame ready for transmission
lm_rc_t lmu_ipv4_header_finalize(lmu_frame_t *frame);

// gets the destination port from the udp header
lm_rc_t lmu_udp_dport_get(lmu_frame_t *frame, uint16_t *dport);

// gets the source port from the udp header
lm_rc_t lmu_udp_sport_get(lmu_frame_t *frame, uint16_t *sport);

// pushes udp header to frame
lm_rc_t lmu_udp_header_push(lmu_frame_t *frame, uint16_t sport, uint16_t dport);

// calculates the udp checksum
lm_rc_t lmu_udp_checksum(lmu_frame_t *frame, lmu_bool_t check);

// updates length and checksum to make frame ready for transmission
lm_rc_t lmu_udp_header_finalize(lmu_frame_t *frame);

#define LMU_DTLS_PRIV_MUP1_OFFSET  (0U)
#define LMU_DTLS_PRIV_SIP_OFFSET   (18U)
#define LMU_DTLS_PRIV_SPORT_OFFSET (24U)

// gets the mup1 flag from the dtls priv header
lm_rc_t lmu_dtls_priv_mup1_get(lmu_frame_t *frame, uint16_t *mup1);

// gets the source ip address from the dtls priv header
lm_rc_t lmu_dtls_priv_sip_get(lmu_frame_t *frame, lm_ipv4_t *addr);

// gets the source port from the dtls priv header
lm_rc_t lmu_dtls_priv_sport_get(lmu_frame_t *frame, uint16_t *sport);

/************* RINGBUFFER UTILITIES *****************/
// Usage:
// LMU_RBUF_DEF(rb, cap) creates and initializes a ring buffer and a handle for
// it. The buffer can contain cap uint8_t elements. It is operated completely
// via the lmu_rbuf_xxx() functions and its handle.
// The size of the buffer (cap) is limited to 2^16 - 2.
typedef struct {
    uint8_t *buf;
    uint32_t head;
    uint32_t tail;
    uint32_t size; // of the buffer
} lmu_rbuf_t;

#define LMU_RBUF_DEF(rb, cap)                                                  \
    uint8_t    rb##_data[(cap) + 1];                                           \
    lmu_rbuf_t rb = {.buf = rb##_data, .head = 0, .tail = 0, .size = (cap) + 1};

// initialize a ring buffer
void lmu_rbuf_init(lmu_rbuf_t *rb, uint8_t *buf, uint32_t size);

// resets a ring buffer
void lmu_rbuf_reset(lmu_rbuf_t *rb);

// checks if buffer is empty
lmu_bool_t lmu_rbuf_empty(lmu_rbuf_t *rb);

// checks if buffer is full
lmu_bool_t lmu_rbuf_full(lmu_rbuf_t *rb);

// returns maximum buffer capacity
uint32_t lmu_rbuf_capacity(lmu_rbuf_t *rb);

// returns remaining buffer size
uint32_t lmu_rbuf_remaining(lmu_rbuf_t *rb);

// returns current buffer size
uint32_t lmu_rbuf_size(lmu_rbuf_t *rb);

// write data to the buffer
lm_rc_t lmu_rbuf_push(lmu_rbuf_t *rb, uint32_t len, const uint8_t *data);

// read data from the buffer
lm_rc_t lmu_rbuf_pop(lmu_rbuf_t *rb, uint32_t len, uint8_t *data);

// non-destructive read data from the buffer
lm_rc_t lmu_rbuf_read(lmu_rbuf_t *rb, uint32_t offset, uint32_t len,
                      uint8_t *data);

// advance read index in the buffer
lm_rc_t lmu_rbuf_advance(lmu_rbuf_t *rb, uint32_t len);

// discard previously pushed data
lm_rc_t lmu_rbuf_discard(lmu_rbuf_t *rb, uint32_t len);

uint8_t lmu_pseudo_rand(void);

// Calculate the log2 result of a given argument and rounds up the result,
// if not power of two
int32_t lmu_log2n_round_up(uint32_t num);

void lmu_dump_data(const char *prefix, const uint8_t *data, size_t size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
