// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <lm_utils.h>
#ifdef LMU_DEBUG
#include <unistd.h>
#endif

lmu_bool_t lmu_isspace(char c)
{
    return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\v') ||
           (c == '\f') || (c == '\r');
}

lmu_bool_t lmu_isdigit(char c) { return (c >= '0') && (c <= '9'); }
lmu_bool_t lmu_isxdigit(char c)
{
    return (lmu_isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}
lmu_bool_t lmu_islower(char c) { return (c >= 'a') && (c <= 'z'); }
lmu_bool_t lmu_isupper(char c) { return (c >= 'A') && (c <= 'Z'); }

const char *lmu_czstrchr(const char *s, int c)
{
    while (LMU_TRUE) {
        if (*s == (char)c) {
            return s;
        }

        if (*s == '\0') {
            break;
        }

        s++;
    }

    return NULL;
}

const char *lmu_czstrrchr(const char *s, int c)
{
    const char *r = NULL;

    while (LMU_TRUE) {
        if (*s == (char)c) {
            r = (const char *)s;
        }

        if (*s == '\0') {
            break;
        }

        s++;
    }

    return r;
}

size_t lmu_ptrdiff_to_size_t(const void *a, const void *b)
{
    ptrdiff_t d = a - b;
    if (d >= 0) {
        return (size_t)(d);
    } else {
        LMU_ASSERT(0);
        return 0;
    }
}

size_t lmu_czstrspn(const char *s, const char *accept)
{
    size_t i = 0;

    while (s[i] != (char)0 && lmu_czstrchr(accept, (int)s[i]) != NULL) {
        i++;
    }

    return i;
}

size_t lmu_czstrcspn(const char *s, const char *reject)
{
    size_t i = 0;

    while (s[i] != '\0' && lmu_czstrchr(reject, (int)s[i]) == NULL) {
        i++;
    }

    return i;
}

void *lmu_memchr(void *ptr, int ch, size_t n)
{
    char  *s = (char *)ptr;
    size_t i;
    for (i = 0; i < n; i++) {
        if (s[i] == (char)ch) {
            return (void *)&s[i];
        }
    }
    return NULL;
}

const void *lmu_memchr_const(const void *ptr, int ch, size_t n)
{
    const char *s = (const char *)ptr;
    size_t      i;
    for (i = 0; i < n; i++) {
        if (s[i] == (char)ch) {
            return (const void *)&s[i];
        }
    }
    return NULL;
}

int lmu_czstrcmp(const char *s1, const char *s2)
{
    int8_t res;

    if (s1 == NULL && s2 == NULL) {
        return 0;
    }

    if (s1 == NULL) {
        return -1;
    }

    if (s2 == NULL) {
        return 1;
    }

    while (*s1 != '\0') {
        if (*s1 != *s2) {
            break;
        }

        ++s1;
        ++s2;
    }

    res = *(const int8_t *)s1 - *(const int8_t *)s2;

    if (res < 0) {
        return -1;
    } else if (res > 0) {
        return 1;
    } else {
        return 0;
    }
}

uint16_t lmu_htons(uint16_t hostshort)
{
#if (defined(BYTE_ORDER) && defined(BIG_ENDIAN) &&                             \
     (BYTE_ORDER == BIG_ENDIAN)) ||                                            \
    (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) &&               \
     (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
    return hostshort;
#elif (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) &&                        \
       (BYTE_ORDER == LITTLE_ENDIAN)) ||                                       \
    (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) &&            \
     (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
    uint16_t lsb = (hostshort & 0xFFU) << 8U;
    uint16_t msb = (hostshort & 0xFF00U) >> 8U;
    return lsb | msb;
#else
#error "Must be either little or big endian!"
#endif
}

uint16_t lmu_ntohs(uint16_t netshort)
{
    // They do the same... Just swapping bytes if little endian.
    return lmu_htons(netshort);
}

uint32_t lmu_htonl(uint32_t hostlong)
{
#if (defined(BYTE_ORDER) && defined(BIG_ENDIAN) &&                             \
     (BYTE_ORDER == BIG_ENDIAN)) ||                                            \
    (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) &&               \
     (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
    return hostlong;
#elif (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) &&                        \
       (BYTE_ORDER == LITTLE_ENDIAN)) ||                                       \
    (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) &&            \
     (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
    uint32_t b3 = (hostlong & 0x000000FFU) << 24U;
    uint32_t b2 = (hostlong & 0x0000FF00U) << 8U;
    uint32_t b1 = (hostlong & 0x00FF0000U) >> 8U;
    uint32_t b0 = (hostlong & 0xFF000000U) >> 24U;
    return b3 | b2 | b1 | b0;
#else
#error "Must be either little or big endian!"
#endif
}

uint32_t lmu_ntohl(uint32_t netlong)
{
    // They do the same... Just swapping bytes if little endian.
    return lmu_htonl(netlong);
}

uint64_t lmu_hton64(uint64_t hostlong)
{
#if (defined(BYTE_ORDER) && defined(BIG_ENDIAN) &&                             \
     (BYTE_ORDER == BIG_ENDIAN)) ||                                            \
    (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) &&               \
     (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
    return hostlong;
#elif (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) &&                        \
       (BYTE_ORDER == LITTLE_ENDIAN)) ||                                       \
    (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) &&            \
     (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
    uint64_t b7 = (hostlong & (uint64_t)0x00000000000000ffULL) << 56U;
    uint64_t b6 = (hostlong & (uint64_t)0x000000000000ff00ULL) << 40U;
    uint64_t b5 = (hostlong & (uint64_t)0x0000000000ff0000ULL) << 24U;
    uint64_t b4 = (hostlong & (uint64_t)0x00000000ff000000ULL) << 8U;
    uint64_t b3 = (hostlong & (uint64_t)0x000000ff00000000ULL) >> 8U;
    uint64_t b2 = (hostlong & (uint64_t)0x0000ff0000000000ULL) >> 24U;
    uint64_t b1 = (hostlong & (uint64_t)0x00ff000000000000ULL) >> 40U;
    uint64_t b0 = (hostlong & (uint64_t)0xff00000000000000ULL) >> 56U;
    return b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0;
#else
#error "Must be either little or big endian!"
#endif
}

uint64_t lmu_ntoh64(uint64_t netlong)
{
    // They do the same... Just swapping bytes if little endian
    return lmu_hton64(netlong);
}

void lmu_rca(uint32_t line, lm_rca_t *rca, lm_rc_t rc)
{
    if ((rca->rc == LM_RC_OK) && (rc != LM_RC_OK)) {
        rca->rc = rc;
        rca->line = line;
    }
}

lmu_bool_t lmu_vid_valid(lm_vid_t vid) { return (vid > 0U && vid < 4096U); }

int lmu_mac_cmp(const lm_mac_t *const a, const lm_mac_t *const b)
{
    uint8_t i;

    for (i = 0U; i < 6U; i++) {
        if (a->data[i] > b->data[i]) {
            return 1;
        } else if (a->data[i] < b->data[i]) {
            return -1;
        } else {
            // Empty on purpose
        }
    }
    return 0;
}

lmu_bool_t lmu_mac_equal(const lm_mac_t *const a, const lm_mac_t *const b)
{
    return lmu_memcmp(a, b, sizeof(*a)) == 0;
}

lmu_bool_t lmu_mac_is_null(const lm_mac_t *const m)
{
    lm_mac_t n = {};
    return lmu_mac_equal(m, &n);
}

lmu_bool_t lmu_mac_is_bcast(const lm_mac_t *const m)
{
    lm_mac_t b = {.data = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};
    return lmu_mac_equal(m, &b);
}

void lmu_mac_set_null(lm_mac_t *const m) { lmu_memset(m, 0, sizeof(*m)); }

void lmu_mac_set_bcast(lm_mac_t *const m) { lmu_memset(m, 0xff, sizeof(*m)); }

void lmu_mac_copy(const lm_mac_t *const src, lm_mac_t *const dst)
{
    lmu_memcpy(dst, src, sizeof(*dst));
}

int lmu_ipv4_cmp(const lm_ipv4_t *const a, const lm_ipv4_t *const b)
{
    uint32_t ua, ub;

    ua = (uint32_t)a->data[0];
    ua <<= 8U;
    ua |= (uint32_t)a->data[1];
    ua <<= 8U;
    ua |= (uint32_t)a->data[2];
    ua <<= 8U;
    ua |= (uint32_t)a->data[3];

    ub = (uint32_t)b->data[0];
    ub <<= 8U;
    ub |= (uint32_t)b->data[1];
    ub <<= 8U;
    ub |= (uint32_t)b->data[2];
    ub <<= 8U;
    ub |= (uint32_t)b->data[3];

    if (ua == ub) {
        return 0;
    } else if (ua < ub) {
        return -1;
    } else {
        return 1;
    }
}

lmu_bool_t lmu_ipv4_equal(const lm_ipv4_t *const a, const lm_ipv4_t *const b)
{
    return (lmu_ipv4_cmp(a, b) == 0);
}

lmu_bool_t lmu_ipv4_is_null(const lm_ipv4_t *const m)
{
    return m->data[0] == 0U && m->data[1] == 0U && m->data[2] == 0U &&
           m->data[3] == 0U;
}

void lmu_ipv4_set_null(lm_ipv4_t *const m)
{
    m->data[0] = 0U;
    m->data[1] = 0U;
    m->data[2] = 0U;
    m->data[3] = 0U;
}

void lmu_ipv4_copy(const lm_ipv4_t *const src, lm_ipv4_t *const dst)
{
    dst->data[0] = src->data[0];
    dst->data[1] = src->data[1];
    dst->data[2] = src->data[2];
    dst->data[3] = src->data[3];
}

lmu_bool_t lmu_ipv4_prefix_equal(const lm_ipv4_prefix_t *const a,
                                 const lm_ipv4_prefix_t *const b)
{
    return (lmu_ipv4_equal(&a->ipv4, &b->ipv4) && (a->prefix == b->prefix));
}

uint8_t lmu_ipv4_mask2prefix(uint32_t mask)
{
    uint8_t  i;
    uint32_t m = 0x80000000U;

    for (i = 0; i < 32U; i++) {
        if ((mask & m) == 0U) {
            break;
        }
        m >>= 1;
    }
    return i;
}

void lmu_port_list_clear(lm_port_list_t *port_list)
{
    lmu_memset(port_list, 0, sizeof(*port_list));
}

void lmu_port_list_set(lm_port_list_t *port_list, uint8_t port, uint8_t val)
{
    uint8_t idx = (port / 8U);
    uint8_t msk = (1U << (port % 8U));

    if (val != 0U) {
        port_list->private_[idx] |= msk;
    } else {
        port_list->private_[idx] &= ~msk;
    }
}

uint8_t lmu_port_list_get(lm_port_list_t *port_list, uint8_t port)
{
    if ((port_list->private_[port / 8U] & ((1U << (port % 8U)))) == 0U) {
        return 0U;
    } else {
        return 1U;
    }
}

lm_rc_t lmu_uintlist_push(lm_uint_list_t *list, uint32_t val)
{
    lm_rc_t rc = LM_RC_ERROR;

    if (list->end < list->begin + list->cap) {
        *list->end++ = val;
        rc = LM_RC_OK;
    }

    return rc;
}

int lmu_uintlist_cmp(const lm_uint_list_t *const a,
                     const lm_uint_list_t *const b)
{
    uint32_t i;

    if (a->cap > b->cap) {
        return 1;
    } else if (a->cap < b->cap) {
        return -1;
    } else {
        // Empty on purpose
    }

    for (i = 0U; i < a->cap; i++) {
        if (a->begin[i] > b->begin[i]) {
            return 1;
        } else if (a->begin[i] < b->begin[i]) {
            return -1;
        } else {
            // Empty on purpose
        }
    }

    return 0;
}

size_t lmu_czstrlen(const char *s)
{
    size_t i;
    if (s == NULL) {
        return 0;
    }
    i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

void lmu_czstrcpy(char *ds, const char *ss)
{
    if (ds == NULL || ss == NULL) {
        return;
    }
    while (*ss != '\0') {
        *ds = *ss;
        ds++;
        ss++;
    }
    *ds = '\0';
    return;
}

size_t lmu_czstrnlen(const char *s, size_t maxlen)
{
    size_t i = 0;
    if (s == NULL) {
        return 0;
    }

    while (i < maxlen && *s != '\0') {
        i++;
        s++;
    }

    return i;
}

lmu_cstr_t lmu_czstr_to_cstr(const char *cstr)
{
    lmu_cstr_t s;
    s.begin = (const char *)cstr;
    s.end = (const char *)cstr + lmu_czstrlen(cstr);
    return s;
}

lmu_cstr_t lmu_ss_to_cstr(const lmu_ss_t *ss)
{
    lmu_cstr_t s;
    s.begin = ss->buf.begin;
    s.end = ss->buf.begin + ss->sslength;
    return s;
}

int lmu_cbe_cbe_cmp(const char *a_begin, const char *a_end, const char *b_begin,
                    const char *b_end)
{
    const char *a_, *b_;

    a_ = a_begin;
    b_ = b_begin;
    while (a_ != a_end && b_ != b_end && *a_ != '\0' && *b_ != '\0') {
        if (*a_ != *b_) {
            break;
        }
        a_++;
        b_++;
    }

    if ((a_ == a_end || (*a_) == '\0') && (b_ == b_end || (*b_) == '\0')) {
        return 0;
    } else if ((a_ == a_end || (*a_) == '\0') && (b_ != b_end && *b_ != '\0')) {
        return -1;
    } else if ((a_ != a_end && *a_ != '\0') && (b_ == b_end || (*b_) == '\0')) {
        return 1;
    } else {
        if (*a_ < *b_) {
            return -1;
        } else {
            return 1;
        }
    }
}

int lmu_cstr_cmp(const lmu_cstr_t *a, const lmu_cstr_t *b)
{
    return lmu_cbe_cbe_cmp(a->begin, a->end, b->begin, b->end);
}

int lmu_str_cmp(const lmu_str_t *a, const lmu_str_t *b)
{
    return lmu_cbe_cbe_cmp(a->begin, a->end, b->begin, b->end);
}

int lmu_cbin_cmp(const lmu_cbin_t *a, const lmu_cbin_t *b)
{
    const uint8_t *a_, *b_;

    a_ = a->begin;
    b_ = b->begin;
    while (a_ != a->end && b_ != b->end) {
        if (*a_ != *b_) {
            break;
        }
        a_++;
        b_++;
    }

    if ((a_ == a->end) && (b_ == b->end)) {
        return 0;
    } else if ((a_ == a->end) && (b_ != b->end)) {
        return -1;
    } else if ((a_ != a->end) && (b_ == b->end)) {
        return 1;
    } else {
        if (*a_ < *b_) {
            return -1;
        } else {
            return 1;
        }
    }
}

int lmu_cbe_czstr_cmp(const char *a_begin, const char *a_end, const char *b)
{
    return lmu_cbe_cbe_cmp(a_begin, a_end, b, b + lmu_czstrlen(b));
}

int lmu_cstr_czstr_cmp(const lmu_cstr_t *a, const char *b)
{
    return lmu_cbe_czstr_cmp(a->begin, a->end, b);
}

int lmu_str_czstr_cmp(const lmu_str_t *a, const char *b)
{
    return lmu_cbe_czstr_cmp(a->begin, a->end, b);
}

char *lmu_str_to_czstr_trunk(lmu_str_t *str)
{
    char *e = str->end - 1;
    *e = '\0';
    return str->begin;
}

// Returns a czstring which is guaranteed to be null terminated - or a null-ptr.
// If the input string uses the full capacity of the buffer, then return
// null-ptr.
char *lmu_str_to_czstr(lmu_str_t *str)
{
    if (lmu_str_len(str) == lmu_str_cap(str)) {
        return NULL;
    }
    return lmu_str_to_czstr_trunk(str);
}

// Capacity of string
size_t lmu_cbe_cap(const char *begin, const char *end)
{
    ptrdiff_t res = 0;
    LMU_ASSERT2(end >= begin);
    res = end - begin;
    return (size_t)res;
}

size_t lmu_cstr_cap(const lmu_cstr_t *s)
{
    return lmu_cbe_cap(s->begin, s->end);
}

size_t lmu_str_cap(const lmu_str_t *s) { return lmu_cbe_cap(s->begin, s->end); }

size_t lmu_cbe_len(const char *begin, const char *end)
{
    return lmu_czstrnlen(begin, lmu_cbe_cap(begin, end));
}

// Returns the string length of s. The length is defined as the number of
// none NULL leading chars in 'data' and never more than the capacity of the
// string.
size_t lmu_cstr_len(const lmu_cstr_t *s)
{
    return lmu_cbe_len(s->begin, s->end);
}
size_t lmu_str_len(const lmu_str_t *s) { return lmu_cbe_len(s->begin, s->end); }

void lmu_str_init_str4(lmu_str4_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 4;
}

void lmu_str_init_str8(lmu_str8_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 8;
}

void lmu_str_init_str16(lmu_str16_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 16;
}

void lmu_str_init_str32(lmu_str32_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 32;
}

void lmu_str_init_str64(lmu_str64_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 64;
}

void lmu_str_init_str128(lmu_str128_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 128;
}

void lmu_str_init_str256(lmu_str256_t *in, lmu_str_t *out)
{
    out->begin = in->data;
    out->end = in->data + 256;
}

void lmu_cstr_init_str4(const lmu_str4_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 4;
}

void lmu_cstr_init_str8(const lmu_str8_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 8;
}

void lmu_cstr_init_str16(const lmu_str16_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 16;
}

void lmu_cstr_init_str32(const lmu_str32_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 32;
}

void lmu_cstr_init_str64(const lmu_str64_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 64;
}

void lmu_cstr_init_str128(const lmu_str128_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 128;
}

void lmu_cstr_init_str256(const lmu_str256_t *in, lmu_cstr_t *out)
{
    out->begin = in->data;
    out->end = in->data + 256;
}

void lmu_ss_init_str4(lmu_str4_t *in, lmu_ss_t *out)
{
    lmu_str_init_str4(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str8(lmu_str8_t *in, lmu_ss_t *out)
{
    lmu_str_init_str8(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str16(lmu_str16_t *in, lmu_ss_t *out)
{
    lmu_str_init_str16(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str32(lmu_str32_t *in, lmu_ss_t *out)
{
    lmu_str_init_str32(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str64(lmu_str64_t *in, lmu_ss_t *out)
{
    lmu_str_init_str64(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str128(lmu_str128_t *in, lmu_ss_t *out)
{
    lmu_str_init_str128(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

void lmu_ss_init_str256(lmu_str256_t *in, lmu_ss_t *out)
{
    lmu_str_init_str256(in, &out->buf);
    out->overflow = 0;
    out->sslength = 0;
}

size_t lmu_ss_cap(lmu_ss_t *ss)
{
    return lmu_ptrdiff_to_size_t(ss->buf.end, ss->buf.begin);
}

static size_t lmu_ss_headroom(lmu_ss_t *ss)
{
    return lmu_ss_cap(ss) - ss->sslength;
}

const char *lmu_ss_czstr_trunk(lmu_ss_t *ss)
{
    char *e = ss->buf.end;
    if (ss->buf.begin == e) {
        return NULL;
    }

    if (lmu_ss_headroom(ss) == 0U) {
        ss->sslength--;
    }

    e--;
    *e = '\0';

    return ss->buf.begin;
}

size_t lmu_cbe_copy(lmu_str_t *dst, const char *src_begin, const char *src_end,
                    int *overflow)
{
    size_t cnt = 0;
    size_t src_len = lmu_cbe_len(src_begin, src_end);

    if (src_len > lmu_str_cap(dst)) {
        cnt = lmu_str_cap(dst);
        if (overflow != NULL) {
            *overflow = 1;
        }
    } else if (src_len == lmu_str_cap(dst)) {
        cnt = src_len;
    } else {
        // Remember to null-terminate if we do not use full capacity
        cnt = src_len;
        *(dst->begin + src_len) = '\0';
    }

    lmu_memcpy(dst->begin, src_begin, cnt);
    return cnt;
}

size_t lmu_cstr_copy(lmu_str_t *dst, const lmu_cstr_t *src, int *overflow)
{
    return lmu_cbe_copy(dst, src->begin, src->end, overflow);
}

size_t lmu_str_copy(lmu_str_t *dst, const lmu_str_t *src, int *overflow)
{
    return lmu_cbe_copy(dst, src->begin, src->end, overflow);
}

size_t lmu_cbe_bin_cap(const uint8_t *begin, const uint8_t *end)
{
    ptrdiff_t res = 0;
    LMU_ASSERT2(end >= begin);
    res = end - begin;
    return (size_t)res;
}

size_t lmu_cbin_cap(const lmu_cbin_t *s)
{
    return lmu_cbe_bin_cap(s->begin, s->end);
}

size_t lmu_bin_cap(const lmu_bin_t *s)
{
    return lmu_cbe_bin_cap(s->begin, s->end);
}

void lmu_cbin_init_bin32(const lmu_bin32_t *in, lmu_cbin_t *out)
{
    out->begin = in->data;
    out->end = in->data + ((in->length > 32U) ? 32U : in->length);
}

void lmu_cbin_init_bin64(const lmu_bin64_t *in, lmu_cbin_t *out)
{
    out->begin = in->data;
    out->end = in->data + ((in->length > 64U) ? 64U : in->length);
}

void lmu_bin_init_bin32(lmu_bin32_t *in, lmu_bin_t *out)
{
    out->begin = in->data;
    out->end = in->data + ((in->length > 32U) ? 32U : in->length);
}

void lmu_bin_init_bin64(lmu_bin64_t *in, lmu_bin_t *out)
{
    out->begin = in->data;
    out->end = in->data + ((in->length > 64U) ? 64U : in->length);
}

size_t lmu_cbe_bin_copy(lmu_bin_t *dst, const uint8_t *src_begin,
                        const uint8_t *src_end, int *overflow)
{
    size_t cnt = 0;

    if (overflow != NULL) {
        *overflow = 0;
    }
    cnt = lmu_cbe_bin_cap(src_begin, src_end);
    if (cnt > lmu_bin_cap(dst)) {
        cnt = lmu_bin_cap(dst);
        if (overflow != NULL) {
            *overflow = 1;
        }
    }

    lmu_memset(dst->begin, 0, lmu_bin_cap(dst));
    lmu_memcpy(dst->begin, src_begin, cnt);

    return cnt;
}

size_t lmu_cbin_copy(lmu_bin_t *dst, const lmu_cbin_t *src, int *overflow)
{
    return lmu_cbe_bin_copy(dst, src->begin, src->end, overflow);
}

size_t lmu_bin_copy(lmu_bin_t *dst, const lmu_bin_t *src, int *overflow)
{
    return lmu_cbe_bin_copy(dst, src->begin, src->end, overflow);
}

static void lmu_str_copy_fill(lmu_ss_t *ss, const lmu_cstr_t *src,
                              lmu_fmt_t *fmt)
{
    size_t i, fill_cnt = 0;

    if (fmt->width == 0U) {
        lmu_ss_append_cstr(ss, src);
        return;
    }

    if (fmt->width > lmu_cstr_len(src)) {
        fill_cnt = fmt->width - lmu_cstr_len(src);
    }

    // Fill left of value
    if ((fmt->lmu_fmt_flag &
         (LMU_FMT_FLAG_PAD_ZERO | LMU_FMT_FLAG_PAD_SPACE)) != 0U) {
        char c = ' ';
        if ((fmt->lmu_fmt_flag & LMU_FMT_FLAG_PAD_ZERO) != 0U) {
            c = '0';
        }

        for (i = 0; i < fill_cnt; ++i) {
            lmu_ss_append_char(ss, c);
        }

        lmu_ss_append_cstr(ss, src);
        return;
    }

    // Fill right of value
    lmu_ss_append_cstr(ss, src);
    for (i = 0; i < fill_cnt; ++i) {
        lmu_ss_append_char(ss, ' ');
    }
}

static void lmu_ss_copy_fill(lmu_ss_t *dest, const lmu_ss_t *src,
                             lmu_fmt_t *fmt)
{
    lmu_cstr_t s;
    s.begin = src->buf.begin;
    s.end = s.begin + src->sslength;
    lmu_str_copy_fill(dest, &s, fmt);
}

static void lmu_fmt_iu32(lmu_ss_t *ss, lmu_fmt_t *fmt, uint32_t val,
                         uint8_t radix, char hexbase, int neg)
{
    lmu_str16_t rbuf;
    lmu_cstr_t  res;
    lmu_str_t   rs;
    char       *p;

    lmu_str_init_str16(&rbuf, &rs);
    p = rs.end - 1;

    if (val == 0U) {
        *p-- = '0';
    }

    while (val != 0U) {
        if (p < rs.begin) {
            break;
        }

        uint8_t v = (uint8_t)(val % radix);
        if (v > 9U) {
            *p-- = (char)v - (char)10 + hexbase;
        } else {
            char base_char = '0';
            base_char += (char)v;
            *p-- = base_char;
        }
        val /= radix;
    }

    if (neg != 0) {
        *p-- = '-';
    } else if (fmt->conv == LMU_FMT_CONV_DEC_SIGNED) {
        if ((fmt->lmu_fmt_flag & LMU_FMT_FLAG_SIGN_FORCE) != 0U) {
            *p-- = '+';
        } else if ((fmt->lmu_fmt_flag & LMU_FMT_FLAG_SIGN_SPACE) != 0U) {
            *p-- = ' ';
        } else {
            // Empty on purpose
        }

    } else {
        // Empty on purpose
    }

    res.begin = p + 1;
    res.end = rs.end;

    lmu_str_copy_fill(ss, &res, fmt);
}

static void lmu_fmt_iu64(lmu_ss_t *ss, lmu_fmt_t *fmt, uint64_t val,
                         uint8_t radix, char hexbase, int neg)
{
    lmu_str32_t rbuf;
    lmu_cstr_t  res;
    lmu_str_t   rs;
    char       *p;

    lmu_str_init_str32(&rbuf, &rs);
    p = rs.end - 1;

    if (val == 0LLU) {
        *p-- = '0';
    }

    while (val != 0LLU) {
        if (p < rs.begin) {
            break;
        }

        uint8_t val_ = (uint8_t)(val % radix);
        char    v = (char)val_;
        if (v > (char)9) {
            *p-- = v - (char)10 + hexbase;
        } else {
            char base_char = '0';
            base_char += (char)v;
            *p-- = base_char;
        }
        val /= radix;
    }

    if (neg != 0) {
        *p-- = '-';
    } else if (fmt->conv == LMU_FMT_CONV_DEC_SIGNED) {
        if ((fmt->lmu_fmt_flag & LMU_FMT_FLAG_SIGN_FORCE) != 0U) {
            *p-- = '+';
        } else if ((fmt->lmu_fmt_flag & LMU_FMT_FLAG_SIGN_SPACE) != 0U) {
            *p-- = ' ';
        } else {
            // Empty on purpose
        }
    } else {
        // Empty on purpose
    }

    res.begin = p + 1;
    res.end = rs.end;

    lmu_str_copy_fill(ss, &res, fmt);
}

void lmu_fmt_i64(lmu_fmt_state_t *state, int64_t ival)
{
    lmu_fmt_t fmt = {};
    if (lmu_ss_fmt_next(state, &fmt)) {
        if (ival < 0) {
            ival *= -1LL;
            lmu_fmt_iu64(state->ss, &fmt, (uint64_t)ival, 10U, '\0', 1);
        } else {
            lmu_fmt_iu64(state->ss, &fmt, (uint64_t)ival, 10U, '\0', 0);
        }
    }
}

void lmu_fmt_u64(lmu_fmt_state_t *state, uint64_t val)
{
    lmu_fmt_t fmt = {};
    if (lmu_ss_fmt_next(state, &fmt)) {
        switch (fmt.conv) {
        case LMU_FMT_CONV_HEX_LC:
            lmu_fmt_iu64(state->ss, &fmt, val, 16U, 'a', 0);
            break;
        case LMU_FMT_CONV_HEX_UC:
            lmu_fmt_iu64(state->ss, &fmt, val, 16U, 'A', 0);
            break;
        case LMU_FMT_CONV_DEC_UNSIGNED:
        default:
            lmu_fmt_iu64(state->ss, &fmt, val, 10U, '\0', 0);
            break;
        }
    }
}

#if defined(__aarch64__)
void lmu_fmt_ull(lmu_fmt_state_t *state, uint64_t val)
{
    lmu_fmt_u64(state, val);
}
#endif

void lmu_fmt_i32(lmu_fmt_state_t *state, int32_t ival)
{
    uint32_t  val = (uint32_t)ival;
    lmu_fmt_t fmt = {};

    if (lmu_ss_fmt_next(state, &fmt)) {
        switch (fmt.len) {
        case LMU_FMT_LENMOD_HH:
            val &= 0xffU;
            ival = (int8_t)val; // sign extend
            break;
        case LMU_FMT_LENMOD_H:
            val &= 0xffffU;
            ival = (int16_t)val; // sign extend
            break;
        default:
            // Do nothing on purpose!
            break;
        }

        switch (fmt.conv) {
        case LMU_FMT_CONV_DEC_UNSIGNED:
            lmu_fmt_iu32(state->ss, &fmt, val, 10U, '\0', 0);
            break;

        case LMU_FMT_CONV_HEX_LC:
            lmu_fmt_iu32(state->ss, &fmt, val, 16U, 'a', 0);
            break;

        case LMU_FMT_CONV_HEX_UC:
            lmu_fmt_iu32(state->ss, &fmt, val, 16U, 'A', 0);
            break;

        case LMU_FMT_CONV_CHAR:
            lmu_ss_append_char(state->ss, (char)ival);
            break;

        case LMU_FMT_CONV_CZSTR:
        case LMU_FMT_CONV_DEC_SIGNED:
        default:
            if (ival < 0) {
                ival *= -1;
                lmu_fmt_iu32(state->ss, &fmt, (uint32_t)ival, 10U, '\0', 1);
            } else {
                lmu_fmt_iu32(state->ss, &fmt, (uint32_t)ival, 10U, '\0', 0);
            }
            break;
        }
    }
}

void lmu_fmt_u32(lmu_fmt_state_t *state, uint32_t val)
{
    lmu_fmt_i32(state, (int32_t)val);
}

void lmu_fmt_u16(lmu_fmt_state_t *state, uint16_t val)
{
    lmu_fmt_i32(state, (int32_t)val);
}

void lmu_fmt_u8(lmu_fmt_state_t *state, uint8_t val)
{
    lmu_fmt_i32(state, (int32_t)val);
}

void lmu_fmt_bool(lmu_fmt_state_t *state, lmu_bool_t val)
{
    if (val) {
        lmu_fmt_i32(state, 1);
    } else {
        lmu_fmt_i32(state, 0);
    }
}

void lmu_fmt_char(lmu_fmt_state_t *state, char val)
{
    lmu_fmt_i32(state, (int32_t)val);
}

void lmu_fmt_i16(lmu_fmt_state_t *state, int16_t ival)
{
    lmu_fmt_i32(state, (int32_t)ival);
}

void lmu_fmt_i8(lmu_fmt_state_t *state, int8_t ival)
{
    lmu_fmt_i32(state, (int32_t)ival);
}

void lmu_fmt_czstr(lmu_fmt_state_t *state, const char *val)
{
    lmu_fmt_t fmt = {};
    if (lmu_ss_fmt_next(state, &fmt)) {
        lmu_cstr_t s = lmu_czstr_to_cstr(val);
        lmu_str_copy_fill(state->ss, &s, &fmt);
    }
}

void lmu_fmt_cstr(lmu_fmt_state_t *state, const lmu_cstr_t *str)
{
    lmu_fmt_t fmt = {};

    if (lmu_ss_fmt_next(state, &fmt)) {
        lmu_str_copy_fill(state->ss, str, &fmt);
    }
}

void lmu_fmt_str(lmu_fmt_state_t *state, const lmu_str_t *str)
{
    lmu_fmt_t  fmt = {};
    lmu_cstr_t s = {.begin = str->begin, .end = str->end};

    if (lmu_ss_fmt_next(state, &fmt)) {
        lmu_str_copy_fill(state->ss, &s, &fmt);
    }
}

void lmu_fmt_buf(lmu_fmt_state_t *state, const lmu_fmt_buf_t *buf)
{
    lmu_fmt_t  fmt = {};
    lmu_cstr_t s = {.begin = buf->ss.buf.begin, .end = buf->ss.buf.end};

    if (lmu_ss_fmt_next(state, &fmt)) {
        lmu_str_copy_fill(state->ss, &s, &fmt);
    }
}

void lmu_fmt_ipv4(lmu_fmt_state_t *state, const lm_ipv4_t *ip)
{
    lmu_str32_t s32;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};

    lmu_ss_init_str32(&s32, &ss);

    if (lmu_ss_fmt_next(state, &fmt)) {
        if ((fmt.lmu_fmt_flag & LMU_FMT_FLAG_PAD_ZERO) != 0U) {
            fmt.lmu_fmt_flag &= (uint8_t)(~LMU_FMT_FLAG_PAD_ZERO);
            LMU_SS_FMT(&ss, "%03d.%03d.%03d.%03d", ip->data[0], ip->data[1],
                       ip->data[2], ip->data[3]);
        } else {
            LMU_SS_FMT(&ss, "%d.%d.%d.%d", ip->data[0], ip->data[1],
                       ip->data[2], ip->data[3]);
        }

        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

void lmu_fmt_ipv4_prefix(lmu_fmt_state_t *state, const lm_ipv4_prefix_t *ip)
{
    lmu_str32_t s32;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};

    lmu_ss_init_str32(&s32, &ss);

    if (lmu_ss_fmt_next(state, &fmt)) {
        if ((fmt.lmu_fmt_flag & LMU_FMT_FLAG_PAD_ZERO) != 0U) {
            fmt.lmu_fmt_flag &= (uint8_t)(~LMU_FMT_FLAG_PAD_ZERO);
            LMU_SS_FMT(&ss, "%03d.%03d.%03d.%03d/%u", ip->ipv4.data[0],
                       ip->ipv4.data[1], ip->ipv4.data[2], ip->ipv4.data[3],
                       ip->prefix);
        } else {
            LMU_SS_FMT(&ss, "%d.%d.%d.%d/%u", ip->ipv4.data[0],
                       ip->ipv4.data[1], ip->ipv4.data[2], ip->ipv4.data[3],
                       ip->prefix);
        }

        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

// Example formats (leading zeros omitted)
// 11:2233:4455:6677:8899:AABB:CCDD:EEFF/128
// 2233:4455::EEFF/128
// ::/0
// ::1/128
// 1::/16
static void lmu_fmt_ipv6_pfx(lmu_fmt_state_t *state, const lm_ipv6_t *ip,
                             const uint8_t pfx)
{
    lmu_str64_t s64;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};
    uint8_t     i, j, cnt = 0, ndx = 8U, max = 1;

    // Find longest chunk with zeros
    for (i = 0; i < 8U; i++) {
        if (lmu_data_u16_get(&ip->data[i * 2U]) == 0U) {
            if (cnt == 0U) {
                // Beginning of chunk
                j = i;
            }
            cnt++;
            if (cnt > max) {
                // Longer chunk found, save index and count
                ndx = j;
                max = cnt;
            }
        } else {
            cnt = 0;
        }
    }

    // Print segments
    lmu_ss_init_str64(&s64, &ss);
    if (lmu_ss_fmt_next(state, &fmt)) {
        for (i = 0; i < 8U; i++) {
            if (i >= ndx && i < (ndx + max)) {
                // Part of longest zero chunk
                if (i == ndx) {
                    LMU_SS_FMT(&ss, "::");
                }
            } else {
                LMU_SS_FMT(&ss, "%X", lmu_data_u16_get(&ip->data[i * 2U]));
                j = (i + 1U);
                if (j != ndx && j != 8U) {
                    LMU_SS_FMT(&ss, ":");
                }
            }
        }
        if (pfx <= 128U) {
            LMU_SS_FMT(&ss, "/%u", pfx);
        }
        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

void lmu_fmt_ipv6(lmu_fmt_state_t *state, const lm_ipv6_t *ip)
{
    lmu_fmt_ipv6_pfx(state, ip, 255);
}

void lmu_fmt_ipv6_prefix(lmu_fmt_state_t *state, const lm_ipv6_prefix_t *ip)
{
    lmu_fmt_ipv6_pfx(state, &ip->ipv6, ip->prefix);
}

void lmu_fmt_mac(lmu_fmt_state_t *state, const lm_mac_t *mac)
{
    lmu_str32_t s32;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};

    lmu_ss_init_str32(&s32, &ss);
    if (lmu_ss_fmt_next(state, &fmt)) {
        LMU_SS_FMT(&ss, "%02X-%02X-%02X-%02X-%02X-%02X", mac->data[0],
                   mac->data[1], mac->data[2], mac->data[3], mac->data[4],
                   mac->data[5]);
        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

void lmu_fmt_bin4(lmu_fmt_state_t *state, const lmu_bin4_t *bin4)
{
    lmu_str32_t s32;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};

    lmu_ss_init_str32(&s32, &ss);
    if (lmu_ss_fmt_next(state, &fmt)) {
        LMU_SS_FMT(&ss, "%02X-%02X-%02X-%02X", bin4->data[0], bin4->data[1],
                   bin4->data[2], bin4->data[3]);
        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

void lmu_fmt_port_list(lmu_fmt_state_t *state, const lm_port_list_t *pl)
{
    lmu_str32_t s32;
    lmu_ss_t    ss;
    lmu_fmt_t   fmt = {};

    lmu_ss_init_str32(&s32, &ss);
    if (lmu_ss_fmt_next(state, &fmt)) {
        LMU_SS_FMT(&ss, "%02X%02X%02X%02X", pl->private_[3], pl->private_[2],
                   pl->private_[1], pl->private_[0]);
        lmu_ss_copy_fill(state->ss, &ss, &fmt);
    }
}

static int lmu_parse_u32_char(char c, uint8_t radix, uint32_t *val_out)
{
    int v;

    if (radix != 2U && radix != 8U && radix != 10U && radix != 16U) {
        return 0;
    }

    if (c >= '0' && c <= '9') {
        v = c - '0';
    } else if (c >= 'a' && c <= 'f') {
        v = (c - 'a') + 10;
    } else if (c >= 'A' && c <= 'F') {
        v = (c - 'A') + 10;
    } else {
        return 0;
    }

    if ((uint8_t)v >= radix) {
        return 0;
    }

    *val_out = (uint32_t)v;
    return 1;
}

size_t lmu_parse_u32(const lmu_cstr_t *str, lmu_parse_u32_cxt_t *cxt)
{
    uint32_t    val = 0U;
    uint64_t    val_ = 0;
    uint32_t    digit_cnt = 0;
    const char *b;
    uint8_t     radix = 10;

    if (cxt->radix != 0U) {
        radix = cxt->radix;
    }

    for (b = str->begin; *b != '\0' && b != str->end; b++) {
        uint32_t digit;
        if (lmu_parse_u32_char(*b, radix, &digit) == 0) {
            break;
        }

        val_ *= radix;
        val_ += digit;
        if (val_ > 0xffffffffU) {
            // Overflow detected
            break;
        }

        if (cxt->max_val != 0U && val_ > cxt->max_val) {
            // It was better before consuming this char
            break;
        }

        val = (uint32_t)val_;
        digit_cnt++;

        if (cxt->max_digit != 0U && digit_cnt == cxt->max_digit) {
            break;
        }
    }

    if (cxt->min_digit != 0U && digit_cnt < cxt->min_digit) {
        return 0;
    }

    if (cxt->min_val != 0U && val < cxt->min_val) {
        return 0;
    }

    cxt->val = val;
    return digit_cnt;
}

// Accepted format: "[whitespace]xx-xx-xx-xx-xx-xx" where x is a hex digit
// Everything after last x is ignored
// Returns length including initial whitespace or 0 on errors
#define LM_MAC_LENGTH 17U
size_t lmu_parse_mac(const lmu_cstr_t *str, lm_mac_t *const mac)
{
    lm_mac_t    m = {0};
    int         ix = 0;
    size_t      len;
    const char *b;

    for (b = str->begin; *b != '\0' && b != str->end; b++) {
        if (!lmu_isspace(*b)) {
            break;
        }
    }
    if ((str->end - b) < (int)LM_MAC_LENGTH) {
        return 0; // Not enough characters left
    }

    // Add initial whitespace
    len = lmu_ptrdiff_to_size_t(b, str->begin) + LM_MAC_LENGTH;

    while (b < str->end) {
        uint32_t msn, lsn; // Most/Least Significant Nibble
        if (lmu_parse_u32_char(*b, 16, &msn) == 0) {
            return 0; // Not a hex digit
        }
        b++;
        if (lmu_parse_u32_char(*b, 16, &lsn) == 0) {
            return 0; // Not a hex digit
        }
        b++;
        if ((ix < 5) && (*b != '-')) {
            return 0; // Not a '-'
        }
        b++;
        m.data[ix++] = (uint8_t)((msn << 4U) + lsn);
        if (ix > 5) {
            break; // We got them all
        }
    }
    *mac = m;
    return len;
}
#undef LM_MAC_LENGTH

// Accepted format: "[whitespace]d.d.d.d" where d is a decimal number 0..255
// Everything after last d is ignored
// Returns length including initial whitespace or 0 on errors
size_t lmu_parse_ipv4(const lmu_cstr_t *str, lm_ipv4_t *const ipv4)
{
    lmu_cstr_t          out, in = *str;
    lm_ipv4_t           ipv4_ = {0};
    size_t              len = 0;
    lmu_str_split_t     res;
    int                 i;
    lmu_parse_u32_cxt_t cxt = {.radix = 10};
    char                cxt_data[2] = {'.', '\0'};

    // Ignore initial whitespace
    for (; in.begin != NULL && in.begin != in.end; in.begin++) {
        if (!lmu_isspace(*in.begin)) {
            break;
        }
        len++;
    }

    for (i = 0; i < 4; i++) {
        size_t sz;
        res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
        if (res != LMU_STR_SPLIT_TOKEN) {
            return 0; // No token
        }
        if (i < 3) { // Invalid chars are allowed after the last number
            for (const char *c = out.begin; c != out.end; c++) {
                if (!lmu_isdigit(*c)) {
                    return 0; // Invalid char
                }
            }
        }
        in.begin = out.end;

        sz = lmu_parse_u32(&out, &cxt);
        if ((sz == 0U) || (cxt.val > 255U)) {
            return 0; // Invalid value
        }
        len += sz;
        ipv4_.data[i] = (uint8_t)cxt.val;

        res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
        in.begin = out.end;
        if (i < 3) {
            if (res != LMU_STR_SPLIT_DELIM) {
                return 0; // No delimiter
            }
            len++;
        } else {
            if (res != LMU_STR_SPLIT_END) {
                return 0; // No end
            }
        }
    }
    *ipv4 = ipv4_;
    return len;
}

// Accepted format: "[whitespace]d.d.d.d/p" where d is a decimal number 0..255
// and p is a decimal number 0..32
// Everything after p is ignored
// Returns length including initial whitespace or 0 on errors
size_t lmu_parse_ipv4_prefix(const lmu_cstr_t *str, lm_ipv4_prefix_t *const ip)
{
    lmu_cstr_t          out, in = *str;
    size_t              sz, len = 0;
    lmu_str_split_t     res;
    lmu_parse_u32_cxt_t cxt = {.radix = 10};
    char                cxt_data[2] = {'/', '\0'};

    res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
    if (res != LMU_STR_SPLIT_TOKEN) {
        return 0; // No token
    }

    sz = lmu_parse_ipv4(&out, &ip->ipv4);
    if (sz != lmu_cstr_len(&out)) {
        return 0; // No ipv4 found
    }
    len += sz;

    in.begin = out.end;
    res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
    if (res != LMU_STR_SPLIT_DELIM) {
        return 0; // No delimiter
    }
    len++;

    in.begin = out.end;
    res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
    if (res != LMU_STR_SPLIT_TOKEN) {
        return 0; // No token
    }

    if (!lmu_isdigit(*out.begin)) {
        return 0; // Value after '/' is not a digit
    }
    sz = lmu_parse_u32(&out, &cxt);
    if (cxt.val > 32U) {
        return 0; // Invalid value
    }
    len += sz;
    ip->prefix = (uint8_t)cxt.val;

    in.begin = out.end;
    res = lmu_cstr_split(&in, &lmu_parse_flag_, cxt_data, &out);
    if (res != LMU_STR_SPLIT_END) {
        return 0; // No end
    }

    return len;
}

// IPv6 address formats:
// ::
// ::1
// 1::2
// 1122:3344:5566:7788:99AA:BBCC:DDEE:FF00
// 1122:3344:5566:7788:99AA:BBCC:1.2.3.4
// ::1.2.3.4
// 1::5.6.7.8
static size_t lmu_parse_ipv6_pfx(const lmu_cstr_t *str, lm_ipv6_t *const ip,
                                 uint8_t *const pfx)
{
    size_t              len;
    lmu_cstr_t          cs = *str;
    lmu_parse_u32_cxt_t cxt = {};
    uint8_t             i, cnt, max = 8, z = max;
    uint16_t            a[8], val;
    lm_ipv4_t           ipv4;

    if (ip == NULL) {
        return 0;
    }

    // Parse 16-bit segments
    // cxt.max_val = 0xffff;
    cxt.radix = 16;
    i = 0;
    while (i < max) {
        if (*cs.begin == ':') {
            cs.begin++;
            if (*cs.begin == ':') {
                // Zero chunk marker '::' found
                if (z < max) {
                    // Only one zero chunk allowed
                    return 0;
                }
                z = i;
                a[i++] = 0;
                cs.begin++;
                if (i >= max) {
                    return 0;
                }
            }
        }
        len = lmu_parse_ipv4(&cs, &ipv4);
        if (len != 0U) {
            a[i++] = lmu_data_u16_get(&ipv4.data[0]);
            if (i >= max) {
                return 0;
            }
            a[i++] = lmu_data_u16_get(&ipv4.data[2]);
            cs.begin += len;
            break;
        }
        len = lmu_parse_u32(&cs, &cxt);
        if (len == 0U || len > 4U) {
            break;
        }
        a[i++] = (uint16_t)cxt.val;
        cs.begin += len;
    }

    // Check if all segments were found
    cnt = i;
    if (cnt < max && z == max) {
        return 0;
    }

    // Parse prefix size
    if (pfx != NULL) {
        if (*cs.begin != '/') {
            return 0;
        }
        cs.begin++;
        cxt.radix = 10;
        cxt.max_val = 128;
        len = lmu_parse_u32(&cs, &cxt);
        if (len == 0U) {
            return 0;
        }
        *pfx = (uint8_t)cxt.val;
        cs.begin += len;
    }

    // Check for trailing characters
    if (cs.begin != cs.end) {
        return 0;
    }

    // Fill out returned address
    cnt = (max - cnt); // Number of extra zero segments
    for (i = 0; i < max; i++) {
        if (i < z) {
            // Before zero chunk
            val = a[i];
        } else if (i > (cnt + z)) {
            // After zero chunk
            val = a[i - cnt];
        } else {
            // In zero chunk
            val = 0;
        }
        lmu_data_u16_put(&ip->data[2U * i], val);
    }
    return lmu_cstr_len(str);
}

size_t lmu_parse_ipv6(const lmu_cstr_t *str, lm_ipv6_t *const ip)
{
    return lmu_parse_ipv6_pfx(str, ip, NULL);
}

size_t lmu_parse_ipv6_prefix(const lmu_cstr_t *str, lm_ipv6_prefix_t *const ip)
{
    return lmu_parse_ipv6_pfx(str, &ip->ipv6, &ip->prefix);
}

void lmu_fmt_state_buf128_init(lmu_fmt_state_buf128_t *state, const char *fmt)
{
    state->state.ss = &state->ss;
    state->state.fmt = fmt;
    state->state.fmt_offset = 0;
    lmu_ss_init_str128(&state->buf, &state->ss);
}

lmu_bool_t lmu_ss_fmt_next(lmu_fmt_state_t *state, lmu_fmt_t *fmt)
{
    int                 has_minus = 0;
    lmu_cstr_t          new_str;
    lmu_parse_u32_cxt_t int_cxt = {};
    size_t              res;
    lmu_bool_t          found_format_spec = LMU_FALSE;

    lmu_memset(fmt, 0, sizeof(*fmt));

    // Consume chars until the first conversion specifier is found (different
    // from '%%').
    while (found_format_spec == LMU_FALSE) {
        lmu_bool_t found_procent = LMU_FALSE;
        while (*state->fmt != '\0' && !found_procent) {
            if (*state->fmt != '%') {
                lmu_ss_append_char(state->ss, *state->fmt);
                state->fmt++;
            } else {
                found_procent = LMU_TRUE;
            }
        }

        if (*state->fmt == '\0') {
            return LMU_FALSE;
        } else {
            state->fmt++;
        }

        if (*state->fmt == '\0') {
            return LMU_FALSE;
        }

        // We will handle '%%' directly here as it does not allow any
        // flags/widths
        if (*state->fmt == '%') {
            lmu_ss_append_char(state->ss, '%');
            state->fmt++;
        } else {
            found_format_spec = LMU_TRUE;
        }
    }

    // Parse flags
    while (*state->fmt != '\0') {
        if (*state->fmt == '0') {
            fmt->lmu_fmt_flag |= LMU_FMT_FLAG_PAD_ZERO;
            state->fmt++;
        } else if (*state->fmt == '-') {
            has_minus = 1;
            state->fmt++;
        } else if (*state->fmt == ' ') {
            fmt->lmu_fmt_flag |= LMU_FMT_FLAG_SIGN_SPACE;
            state->fmt++;
        } else if (*state->fmt == '+') {
            fmt->lmu_fmt_flag |= LMU_FMT_FLAG_SIGN_FORCE;
            state->fmt++;
        } else {
            break;
        }
    }

    new_str = lmu_czstr_to_cstr(state->fmt);
    int_cxt.max_val = 255U;
    res = lmu_parse_u32(&new_str, &int_cxt);
    if (res != 0U) {
        lmu_bool_t pad_zero = (fmt->lmu_fmt_flag & LMU_FMT_FLAG_PAD_ZERO) != 0U;
        if (has_minus == 0 && !(pad_zero)) {
            fmt->lmu_fmt_flag |= LMU_FMT_FLAG_PAD_SPACE;
        }
        fmt->width = (uint8_t)int_cxt.val;
    }

    state->fmt += res;
    if (*state->fmt == '\0') {
        return LMU_TRUE;
    }

    switch (*state->fmt) {
    case 'h':
        fmt->len = LMU_FMT_LENMOD_H;
        state->fmt++;
        break;
    case 'l':
        fmt->len = LMU_FMT_LENMOD_L;
        state->fmt++;
        break;
    case 'z':
        fmt->len = LMU_FMT_LENMOD_Z;
        state->fmt++;
        break;
    case 't':
        fmt->len = LMU_FMT_LENMOD_T;
        state->fmt++;
        break;
    default:
        // Do nothing on purpose!
        break;
    }

    if (*state->fmt == '\0') {
        return LMU_TRUE;
    }

    switch (*state->fmt) {
    case 'h':
        fmt->len = LMU_FMT_LENMOD_HH;
        state->fmt++;
        break;
    case 'l':
        fmt->len = LMU_FMT_LENMOD_LL;
        state->fmt++;
        break;
    default:
        // Do nothing on purpose!
        break;
    }

    if (*state->fmt == '\0') {
        return LMU_TRUE;
    }

    if (*state->fmt == 'd' || *state->fmt == 'i') {
        fmt->conv = LMU_FMT_CONV_DEC_SIGNED;
        state->fmt++;
    } else if (*state->fmt == 'u') {
        fmt->conv = LMU_FMT_CONV_DEC_UNSIGNED;
        state->fmt++;
    } else if (*state->fmt == 'x') {
        fmt->conv = LMU_FMT_CONV_HEX_LC;
        state->fmt++;
    } else if (*state->fmt == 'X') {
        fmt->conv = LMU_FMT_CONV_HEX_UC;
        state->fmt++;
    } else if (*state->fmt == 'c') {
        fmt->len = LMU_FMT_LENMOD_HH;
        fmt->conv = LMU_FMT_CONV_CHAR;
        state->fmt++;
    } else if (*state->fmt == 's') {
        fmt->conv = LMU_FMT_CONV_CZSTR;
        state->fmt++;
    } else if (*state->fmt == 'p') {
        fmt->conv = LMU_FMT_CONV_HEX_LC;
#if __SIZEOF_POINTER__ == 8
        fmt->len = LMU_FMT_LENMOD_LL;
#elif __SIZEOF_POINTER__ == 4
        fmt->len = LMU_FMT_LENMOD_L;
#else
#error __SIZEOF_POINTER__ should be either 4 or 8
#endif
        state->fmt++;
    } else {
        // empty on purpose
    }

    return LMU_TRUE;
}

void lmu_ss_fmt_last(lmu_fmt_state_t *state)
{
    // Still need to handle cases of '%%'
    while (LMU_TRUE) {
        lmu_bool_t found_procent = LMU_FALSE;
        while (*state->fmt != '\0' && !found_procent) {
            if (*state->fmt != '%') {
                lmu_ss_append_char(state->ss, *state->fmt);
                state->fmt++;
            } else {
                found_procent = LMU_TRUE;
            }
        }

        if (*state->fmt == '\0') {
            return;
        } else {
            state->fmt++;
        }

        if (*state->fmt == '\0') {
            return;
        }

        // We will handle '%%' directly here as it does not allow any
        // flags/widths
        if (*state->fmt == '%') {
            state->fmt++;
            lmu_ss_append_char(state->ss, '%');
        }
    }
}

void lmu_ss_fmt_no_args(lmu_ss_t *ss, const char *fmt)
{
    lmu_fmt_state_t s = {.fmt_offset = 0, .fmt = fmt, .ss = ss};
    lmu_ss_fmt_last(&s);
}

size_t lmu_parse_fmt(const lmu_cstr_t *str, lmu_fmt_t *cxt)
{
    lmu_cstr_t          new_str;
    const char         *b = str->begin;
    lmu_fmt_t           val = {};
    int                 has_minus = 0;
    lmu_parse_u32_cxt_t int_cxt = {};
    size_t              res;

    new_str.end = str->end;

    if (*b == '\0' || b == str->end) {
        return 0;
    }

    if (*b != '%') {
        return 0;
    } else {
        b++;
    }

    if (*b == '\0' || b == str->end) {
        return 0;
    }

    lmu_memset(cxt, 0, sizeof(*cxt));

    // Parse flags
    while (*b != '\0' && b != str->end) {
        if (*b == '0') {
            val.lmu_fmt_flag |= LMU_FMT_FLAG_PAD_ZERO;
            b++;
        } else if (*b == '-') {
            has_minus = 1;
            b++;
        } else if (*b == ' ') {
            val.lmu_fmt_flag |= LMU_FMT_FLAG_SIGN_SPACE;
            b++;
        } else if (*b == '+') {
            val.lmu_fmt_flag |= LMU_FMT_FLAG_SIGN_FORCE;
            b++;
        } else {
            break;
        }
    }

    new_str.begin = b;
    int_cxt.max_val = 255U;
    res = lmu_parse_u32(&new_str, &int_cxt);
    if (res != 0U) {
        lmu_bool_t zero_pad = (val.lmu_fmt_flag & LMU_FMT_FLAG_PAD_ZERO) != 0U;
        if (has_minus == 0 && !(zero_pad)) {
            val.lmu_fmt_flag |= LMU_FMT_FLAG_PAD_SPACE;
        }
        val.width = (uint8_t)int_cxt.val;
    }

    new_str.begin += res;
    b = new_str.begin;
    if (*b == '\0' || b == str->end) {
        return 0;
    }

    switch (*b) {
    case 'h':
        val.len = LMU_FMT_LENMOD_H;
        b++;
        break;
    case 'l':
        val.len = LMU_FMT_LENMOD_L;
        b++;
        break;
    case 'z':
        val.len = LMU_FMT_LENMOD_Z;
        b++;
        break;
    case 't':
        val.len = LMU_FMT_LENMOD_T;
        b++;
        break;
    default:
        // Do nothing on purpose!
        break;
    }

    if (*b == '\0' || b == str->end) {
        return 0;
    }

    switch (*b) {
    case 'h':
        val.len = LMU_FMT_LENMOD_HH;
        b++;
        break;
    case 'l':
        val.len = LMU_FMT_LENMOD_LL;
        b++;
        break;
    default:
        // Do nothing on purpose!
        break;
    }

    if (*b == '\0' || b == str->end) {
        return 0;
    }

    if (*b == 'd' || *b == 'i') {
        val.conv = LMU_FMT_CONV_DEC_SIGNED;
        b++;
    } else if (*b == 'u') {
        val.conv = LMU_FMT_CONV_DEC_UNSIGNED;
        b++;
    } else if (*b == 'x') {
        val.conv = LMU_FMT_CONV_HEX_LC;
        b++;
    } else if (*b == 'X') {
        val.conv = LMU_FMT_CONV_HEX_UC;
        b++;
    } else if (*b == 'c') {
        val.conv = LMU_FMT_CONV_CHAR;
        b++;
    } else if (*b == 's') {
        val.conv = LMU_FMT_CONV_CZSTR;
        b++;
    } else if (*b == 'p') {
        val.conv = LMU_FMT_CONV_HEX_LC;
#if __SIZEOF_POINTER__ == 8
        val.len = LMU_FMT_LENMOD_LL;
#elif __SIZEOF_POINTER__ == 4
        val.len = LMU_FMT_LENMOD_L;
#else
#error __SIZEOF_POINTER__ should be either 4 or 8
#endif
        b++;
    } else {
        return 0;
    }

    *cxt = val;
    return lmu_ptrdiff_to_size_t(b, str->begin);
}

size_t lmu_parse_fmt_(const lmu_cstr_t *str, void *cxt)
{
    return lmu_parse_fmt(str, (lmu_fmt_t *)cxt);
}

size_t lmu_cstr_find_char(lmu_cstr_t *str, char c)
{
    const char *b;
    size_t      cnt = 0;
    for (b = str->begin; *b != '\0' && b != str->end; b++) {
        if (*b == c) {
            cnt++;
        }
    }
    return cnt;
}

size_t lmu_parse_flags(const lmu_cstr_t *str, const char *flags)
{
    const char *b;
    lmu_cstr_t  str_flags = lmu_czstr_to_cstr(flags);

    b = str->begin;
    while (b != str->end && *b != '\0' &&
           lmu_cstr_find_char(&str_flags, *b) != 0U) {
        b++;
    }

    return lmu_ptrdiff_to_size_t(b, str->begin);
}
size_t lmu_parse_flags_(const lmu_cstr_t *str, void *cxt)
{
    return lmu_parse_flags(str, (const char *)cxt);
}

size_t lmu_parse_flag(const lmu_cstr_t *str, const char *flags)
{
    lmu_cstr_t str_flags;
    if (str->begin == str->end && *str->begin != '\0') {
        return 0;
    }

    str_flags = lmu_czstr_to_cstr(flags);
    if (lmu_cstr_find_char(&str_flags, *str->begin) != 0U) {
        return 1;
    }

    return 0;
}
size_t lmu_parse_flag_(const lmu_cstr_t *str, void *cxt)
{
    return lmu_parse_flag(str, (const char *)cxt);
}

lmu_str_split_t lmu_cstr_split(const lmu_cstr_t *in, lmu_parse_t delim,
                               void *delim_cxt, lmu_cstr_t *out)
{
    const char *b;
    size_t      res;
    lmu_cstr_t  in_;
    in_.end = in->end;

    if (in->begin == NULL) {
        return LMU_STR_SPLIT_END;
    }

    for (b = in->begin; b != in->end && *b != '\0'; b++) {
        in_.begin = b;
        res = delim(&in_, delim_cxt);
        if (res != 0U && b == in->begin) {
            // Start with a delimitor
            out->begin = in->begin;
            out->end = in->begin + res;
            return LMU_STR_SPLIT_DELIM;
        } else if (res != 0U) {
            out->begin = in->begin;
            out->end = b;
            return LMU_STR_SPLIT_TOKEN;
        } else {
            // Empty on purpose
        }
    }
    *out = *in;

    if (in->begin == in->end) {
        return LMU_STR_SPLIT_END;
    }

    return LMU_STR_SPLIT_TOKEN;
}

void lmu_fmt_buf_init(lmu_fmt_buf_t *buf)
{
    lmu_ss_init_str256(&buf->buf, &buf->ss);
    buf->ss.buf.end--;
    *buf->ss.buf.end = 0;
    buf->s = buf->ss.buf.begin;
    *buf->s = 0;
}

void lmu_ss_append_char(lmu_ss_t *ss, char c)
{
    char *p = ss->buf.begin + ss->sslength;
    if (p == ss->buf.end) {
        ss->overflow = 1;
        return;
    }

    *p++ = c;
    ss->sslength++;

    if (p != ss->buf.end) {
        *p = '\0';
    }
}

void lmu_ss_append_cstr(lmu_ss_t *ss, const lmu_cstr_t *str)
{
    uint32_t    cnt = 0;
    const char *p;
    char       *dest, *dest_end;

    p = str->begin;
    dest = ss->buf.begin + ss->sslength;
    dest_end = ss->buf.end;

    while (dest != dest_end && p != str->end && *p != '\0') {
        *dest++ = *p++;
        cnt++;
    }

    ss->sslength += cnt;
    if (p != str->end && *p != '\0') {
        ss->overflow = 1;
    }

    if (dest != dest_end) {
        *dest = '\0';
    }
}

void lmu_ss_append_czstr(lmu_ss_t *ss, const char *cstr)
{
    lmu_cstr_t str = lmu_czstr_to_cstr(cstr);
    lmu_ss_append_cstr(ss, &str);
}

lmu_bool_t lmu_isprint(char c) { return c >= (char)0x20 && c < (char)0x7f; }

uint16_t lmu_data_u16_get(const uint8_t *data)
{
    uint16_t i, val = 0;

    for (i = 0; i < 2U; i++) {
        val <<= 8;
        val += data[i];
    }
    return val;
}

uint32_t lmu_data_u32_get(const uint8_t *data)
{
    uint32_t i, val = 0;

    for (i = 0; i < 4U; i++) {
        val <<= 8;
        val += data[i];
    }
    return val;
}

void lmu_data_ipv4_get(uint8_t *data, lm_ipv4_t *val)
{
    lmu_memcpy(val->data, data, 4);
}

void lmu_data_mac_get(uint8_t *data, lm_mac_t *val)
{
    lmu_memcpy(val->data, data, 6);
}

void lmu_data_u16_put(uint8_t *data, uint16_t val)
{
    int i;

    for (i = 1; i >= 0; i--) {
        data[i] = (uint8_t)(val & 0xffU);
        val >>= 8;
    }
}

void lmu_data_u32_put(uint8_t *data, uint32_t val)
{
    int i;

    for (i = 3; i >= 0; i--) {
        data[i] = (uint8_t)(val & 0xffU);
        val >>= 8;
    }
}

void lmu_data_ipv4_put(uint8_t *data, lm_ipv4_t *val)
{
    lmu_memcpy(data, val->data, 4);
}

void lmu_data_mac_put(uint8_t *data, lm_mac_t *val)
{
    lmu_memcpy(data, val->data, 6);
}

static void lmu_frame_reset(lmu_frame_t *frame, lmu_frame_state_t direction)
{
    LMU_ASSERT(direction != lmu_frame_state_free);

    lmu_memset(frame, 0, sizeof(*frame));
    frame->state = direction;
}

void lmu_frame_reset_rx(lmu_frame_t *frame)
{
    lmu_frame_reset(frame, lmu_frame_state_rx);
}

void lmu_frame_reset_tx(lmu_frame_t *frame)
{
    lmu_frame_reset(frame, lmu_frame_state_tx);
}

uint8_t *lmu_frame_buf_get(lmu_frame_t *frame)
{
    LMU_ASSERT(frame->state != lmu_frame_state_free);
    return frame->frame_data;
}

// return index of the first layer matching the protocol label
//     or -1 if not available
static int lmu_frame_find_layer_index(const lmu_frame_t *frame,
                                      lmu_frame_proto_t  protocol)
{
    int index;
    LMU_ASSERT(frame->state != lmu_frame_state_free);

    for (index = 0; index < LMU_FRAME_MAX_LAYER_COUNT; index++) {
        if (frame->layers[index].protocol == protocol) {
            return index;
        }
    }
    return -1;
}

static lmu_frame_layer_t *lmu_frame_layer_get(lmu_frame_t *frame,
                                              int          layer_index)
{
    LMU_ASSERT(frame != NULL);
    LMU_ASSERT(frame->state != lmu_frame_state_free);
    if ((layer_index >= 0) && (layer_index < LMU_FRAME_MAX_LAYER_COUNT)) {
        return &(frame->layers[layer_index]);
    }
    return NULL;
}

// return pointer to the first layer matching the protocol label,
//     or NULL if not available
static lmu_frame_layer_t *lmu_frame_find_layer(lmu_frame_t      *frame,
                                               lmu_frame_proto_t protocol)
{
    LMU_ASSERT(frame->state != lmu_frame_state_free);
    return lmu_frame_layer_get(frame,
                               lmu_frame_find_layer_index(frame, protocol));
}

lmu_bool_t lmu_frame_layer_exists(lmu_frame_t      *frame,
                                  lmu_frame_proto_t protocol)
{
    return (NULL != lmu_frame_find_layer(frame, protocol));
}

lm_rc_t lmu_frame_add_existing_layer(lmu_frame_t      *frame,
                                     lmu_frame_proto_t protocol, uint8_t *data,
                                     uint16_t length)
{
    int                layer_index;
    lmu_frame_layer_t *layer = NULL;
#ifdef LMU_DEBUG
    uint8_t *allowed_start = NULL;
    uint8_t *allowed_end = NULL;
#endif

    // confirm frame is allocated
    RC_ASSERT(frame != NULL);
    RC_ASSERT(frame->state != lmu_frame_state_free);

    // confirm protocol range
    RC_ASSERT(protocol > LMU_FRAME_PROTO_UNUSED);
    RC_ASSERT(protocol < LMU_FRAME_PROTO_COUNT);

    layer_index = lmu_frame_find_layer_index(frame, LMU_FRAME_PROTO_UNUSED);

    // confirm unused layer is found,
    //   if failing, consider increasing LMU_FRAME_MAX_LAYER_COUNT
    RC_ASSERT(layer_index >= 0);

#ifdef LMU_DEBUG
    if (layer_index > 0) {
        // make sure the new layer fits with in the previous layer
        layer = lmu_frame_layer_get(frame, layer_index - 1);
        allowed_start = layer->data;
        allowed_end = (layer->data + layer->length);
    } else {
        // make sure the new layer fits with in the base buffer.
        allowed_start = frame->frame_data;
        allowed_end = (frame->frame_data + LMU_FRAME_MAX_SIZE);
    }

    // check region is with in the frame buffer
    RC_ASSERT(data >= allowed_start);
    RC_ASSERT((data + length) <= allowed_end);
#endif

    layer = lmu_frame_layer_get(frame, layer_index);

    layer->protocol = protocol;
    layer->data = data;
    layer->length = length;

    return LM_RC_OK;
}

lmu_bool_t lmu_frame_protocol_exists(lmu_frame_t      *frame,
                                     lmu_frame_proto_t test_protocol)
{
    return (lmu_frame_find_layer_index(frame, test_protocol) >= 0 ? LMU_TRUE
                                                                  : LMU_FALSE);
}

lm_rc_t lmu_frame_data_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                            uint16_t starting_offset, uint8_t *destination,
                            uint16_t length)
{
    RC_ASSERT(frame != NULL);
    RC_ASSERT(frame->state != lmu_frame_state_free);
    lmu_frame_layer_t *layer = lmu_frame_find_layer(frame, protocol);

    RC_ASSERT(layer != NULL);

    // make sure requested data is available
    RC_ASSERT(layer->data != NULL);

    if ((starting_offset + length) <= layer->length) {
        lmu_memcpy(destination, layer->data + starting_offset, length);
        return LM_RC_OK;
    }

    return LM_RC_ERROR;
}

lm_rc_t lmu_frame_data_write(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                             uint16_t starting_offset, uint8_t *src,
                             uint16_t length)
{
    RC_ASSERT(frame != NULL);
    RC_ASSERT(frame->state != lmu_frame_state_free);
    lmu_frame_layer_t *layer = lmu_frame_find_layer(frame, protocol);

    RC_ASSERT(layer != NULL);

    // make sure requested data is available
    RC_ASSERT(layer->data != NULL);
    RC_ASSERT((starting_offset + length) <= layer->length);

    lmu_memcpy(layer->data + starting_offset, src, length);

    return LM_RC_OK;
}

lm_rc_t lmu_frame_u8_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                          uint16_t offset, uint8_t *destination)
{
    return lmu_frame_data_read(frame, protocol, offset, destination, 1U);
}

lm_rc_t lmu_frame_u16_read(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                           uint16_t offset, uint16_t *destination)
{
    uint8_t data[2];

    RC(lmu_frame_data_read(frame, protocol, offset, data, 2U))
    // NOTE: lmu_ntohs was not working yet, so using this endian conversion
    (*destination) =
        (((uint16_t)(data[0])) << 8U) | (((uint16_t)(data[1])) << 0U);

    return LM_RC_OK;
}

void lmu_frame_layer_region_get(lmu_frame_t *frame, lmu_frame_proto_t protocol,
                                uint8_t **data, uint16_t *length)
{
    LMU_ASSERT(frame != NULL);
    LMU_ASSERT(frame->state != lmu_frame_state_free);

    lmu_frame_layer_t *layer = lmu_frame_find_layer(frame, protocol);

    LMU_ASSERT(layer != NULL);

    if (data != NULL) {
        (*data) = layer->data;
    }
    if (length != NULL) {
        (*length) = layer->length;
    }
}

lm_rc_t lmu_frame_layer_push(lmu_frame_t *frame, lmu_frame_proto_t protocol)
{
    int layer_index = lmu_frame_find_layer_index(frame, LMU_FRAME_PROTO_UNUSED);
    uint8_t *newData = NULL;

    if (layer_index < 0) {
        // not enough layers, consider increasing LMU_FRAME_MAX_LAYER_COUNT
        LMU_ASSERT(0);
        return LM_RC_ERROR;
    }

    if (layer_index > 0) {
        lmu_frame_layer_t *lower_layer =
            lmu_frame_layer_get(frame, layer_index - 1);
        LMU_ASSERT(lower_layer->data != NULL);
        LMU_ASSERT(lower_layer->length > 0);
        newData = lower_layer->data + lower_layer->length;
    } else {
        newData = frame->frame_data;
    }

    lmu_frame_layer_t *layer = lmu_frame_layer_get(frame, layer_index);

    LMU_ASSERT(layer != NULL);

    layer->protocol = protocol;
    layer->data = newData;
    layer->length = 0;

    return LM_RC_OK;
}

lm_rc_t lmu_frame_proto_data_push(lmu_frame_t      *frame,
                                  lmu_frame_proto_t protocol, uint8_t *source,
                                  uint16_t length)
{
    uint8_t           *data;
    int                layer_index;
    int                index;
    lmu_frame_layer_t *layer;

    layer_index = lmu_frame_find_layer_index(frame, protocol);
    RC_ASSERT(layer_index >= 0);
    layer = lmu_frame_layer_get(frame, layer_index);

    LMU_ASSERT(source != NULL);
    LMU_ASSERT(layer != NULL);
    data = &(layer->data[layer->length]);

#ifdef LMU_DEBUG
    // make sure each lower layer ends at the same location as the target layer
    for (index = layer_index - 1; index >= 0; index--) {
        lmu_frame_layer_t *lower_layer = lmu_frame_layer_get(frame, index);
        LMU_ASSERT(data == &(lower_layer->data[lower_layer->length]));
    }
#endif

    // make sure the data to add will fit in the frame_data buffer
#pragma coverity compliance deviate                                            \
    "MISRA C-2023 Rule 18.3"                                                   \
    "LMU_FALSE positive. data is pointing with in frame->frame_data."
    RC_ASSERT(&(data[length]) <= &(frame->frame_data[LMU_FRAME_MAX_SIZE]));

    lmu_memmove(data, source, length);

    // move lengths forward for this layer and each lower layer.
    for (index = layer_index; index >= 0; index--) {
        lmu_frame_layer_t *lower_layer = lmu_frame_layer_get(frame, index);
        lower_layer->length += length;
    }

    return LM_RC_OK;
}

static lm_rc_t lmu_frame_get_highest_protocol(lmu_frame_t       *frame,
                                              lmu_frame_proto_t *protocol)
{
    int layer_index;

    LMU_ASSERT(frame != NULL);
    LMU_ASSERT(frame->state != lmu_frame_state_free);

    // set layer_index to highest USED layer.
    layer_index = lmu_frame_find_layer_index(frame, LMU_FRAME_PROTO_UNUSED);
    if (layer_index >= 0) {
        // an unused layer was found, the highest used layer is the one below.

        if (layer_index == 0) {
            // layer_index can not be 0, since that means there is no used layer
            //   must call lma_frame_layer_push first.
            LMU_ASSERT(0);
            return LM_RC_ERROR;
        }

        // set layer_index to next lower layer.
        layer_index--;
    } else {
        // no unused layer found, so assume all layers are used.
        // set layer_index to highest possible layer.
        layer_index = LMU_FRAME_MAX_LAYER_COUNT - 1;
    }
    if (protocol != NULL) {
        (*protocol) = frame->layers[layer_index].protocol;
#ifdef LMU_DEBUG
        // make sure this protocol does not also exist in lower layers
        for (int index = 0; index < layer_index; index++) {
            LMU_ASSERT(frame->layers[index].protocol != (*protocol));
        }
#endif
    }
    return LM_RC_OK;
}

lm_rc_t lmu_frame_data_push(lmu_frame_t *frame, uint8_t *source,
                            uint16_t length)
{
    lmu_frame_proto_t protocol;

    RC(lmu_frame_get_highest_protocol(frame, &protocol));

    return lmu_frame_proto_data_push(frame, protocol, source, length);
}

lm_rc_t lmu_frame_u8_push(lmu_frame_t *frame, uint8_t value)
{
    return lmu_frame_data_push(frame, &value, (uint16_t)sizeof(value));
}

lm_rc_t lmu_frame_u16_push(lmu_frame_t *frame, uint16_t value)
{
    // NOTE: lmu_htons was not working yet, so using this endian conversion
    uint8_t data[2];

    data[0] = (uint8_t)((value >> 8U) & 0xffU);
    data[1] = (uint8_t)((value >> 0U) & 0xffU);
    return lmu_frame_data_push(frame, data, 2);
}

lm_rc_t lmu_frame_u24_push(lmu_frame_t *frame, uint32_t value)
{
    // NOTE: lmu_htonl was not working yet, so using this endian conversion
    uint8_t data[3];

    data[0] = (uint8_t)((value >> 16U) & 0xffU);
    data[1] = (uint8_t)((value >> 8U) & 0xffU);
    data[2] = (uint8_t)((value >> 0U) & 0xffU);
    return lmu_frame_data_push(frame, data, 3);
}

lm_rc_t lmu_frame_u32_push(lmu_frame_t *frame, uint32_t value)
{
    // NOTE: lmu_htonl was not working yet, so using this endian conversion
    uint8_t data[4];

    data[0] = (uint8_t)((value >> 24U) & 0xffU);
    data[1] = (uint8_t)((value >> 16U) & 0xffU);
    data[2] = (uint8_t)((value >> 8U) & 0xffU);
    data[3] = (uint8_t)((value >> 0U) & 0xffU);
    return lmu_frame_data_push(frame, data, 4);
}

lm_rc_t lmu_frame_u48_push(lmu_frame_t *frame, uint64_t value)
{
    // NOTE: lmu_htonl was not working yet, so using this endian conversion
    uint8_t data[6];

    data[0] = (uint8_t)((value >> 40U) & 0xffU);
    data[1] = (uint8_t)((value >> 32U) & 0xffU);
    data[2] = (uint8_t)((value >> 24U) & 0xffU);
    data[3] = (uint8_t)((value >> 16U) & 0xffU);
    data[4] = (uint8_t)((value >> 8U) & 0xffU);
    data[5] = (uint8_t)((value >> 0U) & 0xffU);
    return lmu_frame_data_push(frame, data, 6);
}

lm_rc_t lmu_frame_u48_data_push(lmu_frame_t *frame, uint8_t *data)
{
    return lmu_frame_data_push(frame, data, 6);
}

void lmu_frame_dump(lmu_frame_t *frame)
{
#ifdef LMU_DEBUG
    LMU_ASSERT(frame != NULL);
    uint8_t *data = NULL;
    uint16_t length = 0;
    uint16_t index = 0;

    lmu_frame_proto_t proto = frame->layers[0].protocol;
    if ((proto <= LMU_FRAME_PROTO_UNUSED) || (proto >= LMU_FRAME_PROTO_COUNT)) {
        LMU_PRINTF("lma_frame_dump: base layer not found\n");
        return;
    }
    data = frame->layers[0].data;
    length = frame->layers[0].length;
    LMU_PRINTF("lmu_frame_dump: protocol = %d\n", proto);
    for (index = 0; index < length; index++) {
        if ((index % 16U) == 0U) {
            if (index != 0) {
                LMU_PRINTF("\n");
            }
            LMU_PRINTF("  %04X", index);
        }
        if ((index % 4U) == 0U) {
            LMU_PRINTF(" ");
        }
        LMU_PRINTF(" %02X", data[index]);
    }
    LMU_PRINTF("\n");
#endif // LMA_DEBUG
}

lm_rc_t lmu_eth_dmac_get(lmu_frame_t *frame, lm_mac_t *dmac)
{
    return lmu_frame_data_read(frame, LMU_FRAME_PROTO_ETH, 0, (uint8_t *)dmac,
                               (uint16_t)sizeof(*dmac));
}

lm_rc_t lmu_eth_smac_get(lmu_frame_t *frame, lm_mac_t *smac)
{
    return lmu_frame_data_read(frame, LMU_FRAME_PROTO_ETH, 6, (uint8_t *)smac,
                               (uint16_t)sizeof(*smac));
}

lm_rc_t lmu_eth_etype_get(lmu_frame_t *frame, uint16_t *etype)
{
    return lmu_frame_u16_read(frame, LMU_FRAME_PROTO_ETH, 12, etype);
}

lm_rc_t lmu_eth_header_push(lmu_frame_t *frame, lm_mac_t dmac, lm_mac_t smac,
                            uint16_t etype)
{
    RC(lmu_frame_layer_push(frame, LMU_FRAME_PROTO_ETH));
    RC(lmu_frame_u48_data_push(frame, (uint8_t *)&dmac));
    RC(lmu_frame_u48_data_push(frame, (uint8_t *)&smac));
    RC(lmu_frame_u16_push(frame, etype));

    return LM_RC_OK;
}

uint32_t lmu_inet_chksum32(const uint8_t *data, uint32_t length)
{
    uint32_t sum = 0U;
    uint32_t i = 0;

    while (i < length) {
        sum += ((uint32_t)data[i] << 8U);
        i++;
        if (i < length) {
            sum += (uint32_t)data[i];
        }
        i++;
    }

    return sum;
}

uint16_t lmu_inet_chksum(uint32_t sum, const uint8_t *data, uint32_t length)
{
    sum += lmu_inet_chksum32(data, length);

    // Add carry twice (the first addition may cause another, e.g. 0x1ffff)
    sum = ((sum >> 16U) + (sum & 0xffffU));
    sum = ((sum >> 16U) + (sum & 0xffffU));

    sum = ~sum;
    return (uint16_t)sum;
}

lm_rc_t lmu_ipv4_sip_get(lmu_frame_t *frame, lm_ipv4_t *addr)
{
    return lmu_frame_data_read(frame, LMU_FRAME_PROTO_IPV4, 12, (uint8_t *)addr,
                               (uint16_t)sizeof(*addr));
}

lm_rc_t lmu_ipv4_dip_get(lmu_frame_t *frame, lm_ipv4_t *addr)
{
    return lmu_frame_data_read(frame, LMU_FRAME_PROTO_IPV4, 16, (uint8_t *)addr,
                               (uint16_t)sizeof(*addr));
}

lm_rc_t lmu_ipv4_protocol_get(lmu_frame_t *frame, uint8_t *protocol)
{
    return lmu_frame_u8_read(frame, LMU_FRAME_PROTO_IPV4, 9, protocol);
}

lm_rc_t lmu_ipv4_header_push(lmu_frame_t *frame, lm_ipv4_t sip, lm_ipv4_t dip,
                             uint8_t protocol)
{
    RC(lmu_frame_layer_push(frame, LMU_FRAME_PROTO_IPV4));
    RC(lmu_frame_u8_push(frame, 0x45U)); // version=4, IHL=5
    RC(lmu_frame_u8_push(frame, 0x00U)); // Type of Service = 0
    RC(lmu_frame_u16_push(frame, 0U));   // Total length = 0,to be updated on tx
    RC(lmu_frame_u32_push(frame, 0U));   // ID=0,Flags=0,Frag Offset = 0
    RC(lmu_frame_u8_push(frame, 0x1FU)); // TTL = 0x1f
    RC(lmu_frame_u8_push(frame, protocol)); // set protocol
    RC(lmu_frame_u16_push(frame,
                          0U)); // Header Checksum = 0.to be updated on tx
    RC(lmu_frame_data_push(frame, (uint8_t *)&sip,
                           (uint16_t)sizeof(sip))); // source ip address
    RC(lmu_frame_data_push(frame, (uint8_t *)&dip,
                           (uint16_t)sizeof(dip))); // dest ip address

    return LM_RC_OK;
}

lm_rc_t lmu_ipv4_checksum(lmu_frame_t *frame, lmu_bool_t check)
{
    uint8_t *data = NULL;
    uint16_t length = 0, hsum, csum;
    uint8_t  ihl;

    lmu_frame_layer_region_get(frame, LMU_FRAME_PROTO_IPV4, &data, &length);

    ihl = ((data[0] & 0x0FU) * 4U);
    if (ihl < 20U) {
        LMU_PRINTF("lmu_ipv4_checksum: IHL too short\n");
        return LM_RC_ERROR;
    }

    if (length < ihl) {
        LMU_PRINTF("lmu_ipv4_checksum: IHL exceeds length\n");
        return LM_RC_ERROR;
    }

    // Store and clear checksum field
    hsum = (((uint16_t)data[10] << 8U) + (uint16_t)data[11]);
    data[10] = 0U;
    data[11] = 0U;

    // Calculate checksum
    csum = lmu_inet_chksum(0U, data, ihl);
    if (check && csum != hsum) {
        LMU_PRINTF("lmu_ipv4_checksum fails, csum: 0x%x, hsum: 0x%x\n", csum,
                   hsum);
        return LM_RC_ERROR;
    }

    // Update/restore checksum field
    data[10] = (uint8_t)(csum >> 8U);
    data[11] = (uint8_t)csum;

    return LM_RC_OK;
}

lm_rc_t lmu_ipv4_header_finalize(lmu_frame_t *frame)
{
    uint8_t *ipv4_data = NULL;
    uint16_t ipv4_length = 0;

    lmu_frame_layer_region_get(frame, LMU_FRAME_PROTO_IPV4, &ipv4_data,
                               &ipv4_length);

    // set length
    ipv4_data[2] = (uint8_t)(ipv4_length >> 8U);
    ipv4_data[3] = (uint8_t)(ipv4_length);

    // set checksum
    RC(lmu_ipv4_checksum(frame, LMU_FALSE));

    return LM_RC_OK;
}

lm_rc_t lmu_udp_dport_get(lmu_frame_t *frame, uint16_t *dport)
{
    return lmu_frame_u16_read(frame, LMU_FRAME_PROTO_UDP, 2, dport);
}

lm_rc_t lmu_udp_sport_get(lmu_frame_t *frame, uint16_t *sport)
{
    return lmu_frame_u16_read(frame, LMU_FRAME_PROTO_UDP, 0, sport);
}

lm_rc_t lmu_udp_header_push(lmu_frame_t *frame, uint16_t sport, uint16_t dport)
{
    RC(lmu_frame_layer_push(frame, LMU_FRAME_PROTO_UDP));
    RC(lmu_frame_u16_push(frame, sport));
    RC(lmu_frame_u16_push(frame, dport));
    RC(lmu_frame_u16_push(frame, 0U)); // length = 0, to be updated on tx
    RC(lmu_frame_u16_push(frame, 0U)); // checksum = 0, to be updated on tx

    return LM_RC_OK;
}

lm_rc_t lmu_udp_checksum(lmu_frame_t *frame, lmu_bool_t check)
{
    uint32_t sum;
    uint8_t *data = NULL;
    uint16_t length = 0, hsum, csum;
    uint8_t  hdr[12];

    // Pseudo header: IP fields
    lmu_frame_layer_region_get(frame, LMU_FRAME_PROTO_IPV4, &data, &length);
    if (length < 20U) {
        LMU_PRINTF("lmu_udp_checksum: IP length too short\n");
        return LM_RC_ERROR;
    }
    lmu_memcpy(&hdr[0], data + 12, 8); // SIP and DIP
    hdr[8] = 0;                        // Zero
    hdr[9] = data[9];                  // IP protocol

    // Pseudo header: UDP fields
    lmu_frame_layer_region_get(frame, LMU_FRAME_PROTO_UDP, &data, &length);
    if (length < 8U) {
        LMU_PRINTF("lmu_udp_checksum: UDP length too short\n");
        return LM_RC_ERROR;
    }
    hdr[10] = data[4]; // UDP length
    hdr[11] = data[5]; // UDP length

    // Calculate pseudo header checksum
    sum = lmu_inet_chksum32(hdr, 12U);

    // Store and clear UDP checksum field
    hsum = (((uint16_t)data[6] << 8U) + (uint16_t)data[7]);
    data[6] = 0U;
    data[7] = 0U;

    // Calculate total header checksum
    csum = lmu_inet_chksum(sum, data, length);

    if (check && hsum != 0U && csum != hsum) {
        LMU_PRINTF("lmu_udp_checksum fails, csum: 0x%x, hsum: 0x%x\n", csum,
                   hsum);
        return LM_RC_ERROR;
    }

    // Update/restore checksum field
    data[6] = (uint8_t)(csum >> 8U);
    data[7] = (uint8_t)csum;

    return LM_RC_OK;
}

lm_rc_t lmu_udp_header_finalize(lmu_frame_t *frame)
{
    uint8_t *udp_data = NULL;
    uint16_t udp_length = 0;

    lmu_frame_layer_region_get(frame, LMU_FRAME_PROTO_UDP, &udp_data,
                               &udp_length);

    // set length
    udp_data[4] = (uint8_t)(udp_length >> 8U);
    udp_data[5] = (uint8_t)(udp_length);

    // set checksum
    RC(lmu_udp_checksum(frame, LMU_FALSE));

    return LM_RC_OK;
}

lm_rc_t lmu_dtls_priv_mup1_get(lmu_frame_t *frame, uint16_t *mup1)
{
    return lmu_frame_u16_read(frame, LMU_FRAME_PROTO_DTLS_PRIV,
                              LMU_DTLS_PRIV_MUP1_OFFSET, mup1);
}

lm_rc_t lmu_dtls_priv_sip_get(lmu_frame_t *frame, lm_ipv4_t *addr)
{
    return lmu_frame_data_read(frame, LMU_FRAME_PROTO_DTLS_PRIV,
                               LMU_DTLS_PRIV_SIP_OFFSET, (uint8_t *)addr,
                               (uint16_t)sizeof(*addr));
}

lm_rc_t lmu_dtls_priv_sport_get(lmu_frame_t *frame, uint16_t *sport)
{
    return lmu_frame_u16_read(frame, LMU_FRAME_PROTO_DTLS_PRIV,
                              LMU_DTLS_PRIV_SPORT_OFFSET, sport);
}

/************* RINGBUFFER UTILITIES *****************/

void lmu_rbuf_init(lmu_rbuf_t *rb, uint8_t *buf, uint32_t size)
{
    LMU_ASSERT(rb);
    LMU_ASSERT(buf);
    LMU_ASSERT(size > 0U);

    rb->buf = buf;
    rb->head = 0U;
    rb->tail = 0U;
    rb->size = size;
}

void lmu_rbuf_reset(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    rb->head = 0U;
    rb->tail = 0U;
}

lmu_bool_t lmu_rbuf_empty(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    return (rb->head == rb->tail);
}

lmu_bool_t lmu_rbuf_full(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    return ((rb->head + 1U) % rb->size) == rb->tail;
}

// returns maximum buffer capacity
uint32_t lmu_rbuf_capacity(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    return rb->size - 1U;
}

// returns remaining buffer size
uint32_t lmu_rbuf_remaining(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    return lmu_rbuf_capacity(rb) - lmu_rbuf_size(rb);
}

// returns current buffer size
uint32_t lmu_rbuf_size(lmu_rbuf_t *rb)
{
    LMU_ASSERT(rb);

    uint32_t size;

    if (rb->head >= rb->tail) {
        size = (rb->head - rb->tail);
    } else {
        size = (rb->size + rb->head - rb->tail);
    }

    return size;
}

// write data to the buffer
lm_rc_t lmu_rbuf_push(lmu_rbuf_t *rb, uint32_t len, const uint8_t *data)
{
    lm_rc_t r = LM_RC_OUT_OF_MEMORY;
    LMU_ASSERT(rb);
    LMU_ASSERT(rb->buf);

    if (len <= lmu_rbuf_remaining(rb)) {
        for (uint32_t i = 0; i < len; i++) {
            rb->buf[rb->head] = *data++;
            ++(rb->head);
            if (rb->head == rb->size) {
                rb->head = 0;
            }
        }
        r = LM_RC_OK;
    }

    return r;
}

// read data from the buffer
lm_rc_t lmu_rbuf_pop(lmu_rbuf_t *rb, uint32_t len, uint8_t *data)
{
    lm_rc_t r = LM_RC_ERROR;
    LMU_ASSERT(rb);
    LMU_ASSERT(rb->buf);

    if (len <= lmu_rbuf_size(rb)) {
        for (uint32_t i = 0; i < len; i++) {
            *data++ = rb->buf[rb->tail];
            ++(rb->tail);
            if (rb->tail == rb->size) {
                rb->tail = 0;
            }
        }
        r = LM_RC_OK;
    }

    return r;
}

// non-destructive read data from the buffer
lm_rc_t lmu_rbuf_read(lmu_rbuf_t *rb, uint32_t offset, uint32_t len,
                      uint8_t *data)
{
    LMU_ASSERT(rb);
    LMU_ASSERT(rb->buf);

    if ((offset + len) <= lmu_rbuf_size(rb)) {
        uint32_t tail = rb->tail + offset;
        if (tail >= rb->size) {
            tail -= rb->size;
        }
        for (uint32_t i = 0; i < len; i++) {
            *data++ = rb->buf[tail];
            tail++;
            if (tail == rb->size) {
                tail = 0;
            }
        }
        return LM_RC_OK;
    }

    return LM_RC_ERROR;
}

// advance read index in the buffer
lm_rc_t lmu_rbuf_advance(lmu_rbuf_t *rb, uint32_t len)
{
    LMU_ASSERT(rb);
    LMU_ASSERT(rb->buf);

    if (len <= lmu_rbuf_size(rb)) {
        for (uint32_t i = 0; i < len; i++) {
            ++(rb->tail);
            if (rb->tail == rb->size) {
                rb->tail = 0;
            }
        }
        return LM_RC_OK;
    }

    return LM_RC_ERROR;
}

// discard previously pushed data by decrementing head index
lm_rc_t lmu_rbuf_discard(lmu_rbuf_t *rb, uint32_t len)
{
    LMU_ASSERT(rb);
    LMU_ASSERT(rb->buf);

    if (len <= lmu_rbuf_size(rb)) {
        for (uint32_t i = 0; i < len; i++) {
            if (rb->head == 0U) {
                rb->head = rb->size;
            }
            --(rb->head);
        }
        return LM_RC_OK;
    }

    return LM_RC_ERROR;
}

uint8_t lmu_pseudo_rand(void)
{
    static uint16_t randn = 0;
    randn = (((randn * 3U) + 2U) % 0x1FFU);
    return (uint8_t)randn;
}

int32_t lmu_log2n_round_up(uint32_t num)
{
    int32_t  log2_val = -1;
    uint32_t temp = num;

    if (temp < 2u) {
        log2_val = 0;
    } else {
        while (temp != 0U) {
            log2_val++;
            temp = temp >> 1u;
        }

        if ((num & (num - 1u)) != 0U) {
            log2_val++; // not power of 2, round up value
        }
    }

    return log2_val;
}

static char lmu_nibble_to_hex(uint8_t nibble)
{
    if (nibble < 0xAU) {
        return '0' + nibble;
    } else if (nibble < 0x10U) {
        return 'A' + nibble - 0xA;
    } else {
        return 'X';
    }
}

void lmu_dump_data(const char *prefix, const uint8_t *data, size_t size)
{
    LMU_ASSERT(prefix != NULL);
    LMU_ASSERT(data != NULL);
    LMU_PRINTF("%s[0x%08X]\n", prefix, ((uintptr_t)data));

    char line[80];
    int  line_index = 0;
    LMU_ZERO_SET(line);
    uint32_t data_index = 0;
    while (data_index < size) {
        if ((data_index % 16U) == 0U) {
            if (line_index > 0) {
                // flush previous line
                LMU_PRINTF("%s\n", line);
                LMU_ZERO_SET(line);
                line_index = 0;
            }
            line[line_index++] =
                lmu_nibble_to_hex((uint8_t)((data_index >> 12) & 0xFU));
            line[line_index++] =
                lmu_nibble_to_hex((uint8_t)((data_index >> 8) & 0xFU));
            line[line_index++] =
                lmu_nibble_to_hex((uint8_t)((data_index >> 4) & 0xFU));
            line[line_index++] =
                lmu_nibble_to_hex((uint8_t)((data_index >> 0) & 0xFU));
        }
        if ((data_index % 4U) == 0U) {
            line[line_index++] = ' ';
        }
        line[line_index++] = ' ';
        line[line_index++] =
            lmu_nibble_to_hex((uint8_t)((data[data_index] >> 4) & 0xFU));
        line[line_index++] =
            lmu_nibble_to_hex((uint8_t)((data[data_index] >> 0) & 0xFU));
        data_index++;
    }
    if (line_index > 0) {
        // flush previous line
        LMU_PRINTF("%s\n", line);
    }
}
