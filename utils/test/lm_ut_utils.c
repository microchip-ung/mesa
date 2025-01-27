// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "acutest.h"
#include "lm_utils.h"

#define RBUF_SIZE 128

#define TEST_RC(expr)  TEST_CHECK((expr) == LM_RC_OK)
#define TEST_NRC(expr) TEST_CHECK((expr) != LM_RC_OK)

void lm_os_debug_console_put(const char *c, size_t length)
{
    size_t i;
    for (i = 0; i < length; i++) {
        putchar(*c++);
    }
}

void test_lmu_isxxxx()
{
    TEST_CASE("isspace");
    TEST_CHECK(lmu_isspace(' '));
    TEST_CHECK(lmu_isspace('\t'));
    TEST_CHECK(lmu_isspace('\n'));
    TEST_CHECK(lmu_isspace('\v'));
    TEST_CHECK(lmu_isspace('\f'));
    TEST_CHECK(lmu_isspace('\r'));
    TEST_CHECK(!lmu_isspace('a'));
    TEST_CHECK(!lmu_isspace('7'));

    TEST_CASE("isdigit");
    TEST_CHECK(lmu_isdigit('0'));
    TEST_CHECK(lmu_isdigit('5'));
    TEST_CHECK(lmu_isdigit('9'));
    TEST_CHECK(!lmu_isdigit('A'));

    TEST_CASE("islower");
    TEST_CHECK(lmu_islower('a'));
    TEST_CHECK(lmu_islower('j'));
    TEST_CHECK(lmu_islower('z'));
    TEST_CHECK(!lmu_islower('A'));
    TEST_CHECK(!lmu_islower('3'));

    TEST_CASE("isupper");
    TEST_CHECK(lmu_isupper('A'));
    TEST_CHECK(lmu_isupper('Z'));
    TEST_CHECK(lmu_isupper('J'));
    TEST_CHECK(!lmu_isupper('a'));
    TEST_CHECK(!lmu_isupper('3'));
}

void test_lmu_memmove()
{
    int  i, dest, size, offset;
    char buf_a[64];
    char buf_b[64];
    char name[128];

    for (offset = 16; offset < 20; ++offset) {
        for (size = 0; size < 10; ++size) {
            for (dest = 0; dest < 40; ++dest) {
                for (i = 0; i < 64; ++i) {
                    buf_a[i] = i;
                    buf_b[i] = i;
                }

                sprintf(name, "memmove offset=%d, size=%d, dest=%d", offset,
                        size, dest);
                TEST_CASE(name);
                memmove(&buf_a[dest], &buf_a[offset], size);
                lmu_memmove(&buf_b[dest], &buf_b[offset], size);
                TEST_CHECK(memcmp(buf_a, buf_b, 64) == 0);
            }
        }
    }
}

void test_lmu_czstrlen()
{
    TEST_CHECK(lmu_czstrlen(0) == 0);
    TEST_CHECK(lmu_czstrlen("") == 0);
    TEST_CHECK(lmu_czstrlen("a") == 1);
    TEST_CHECK(lmu_czstrlen("0") == 1);
    TEST_CHECK(lmu_czstrlen("00") == 2);
}

void test_lmu_czstrnlen()
{
    TEST_CHECK(lmu_czstrnlen(0, 10) == 0);
    TEST_CHECK(lmu_czstrnlen("", 10) == 0);
    TEST_CHECK(lmu_czstrnlen("a", 10) == 1);
    TEST_CHECK(lmu_czstrnlen("0", 10) == 1);
    TEST_CHECK(lmu_czstrnlen("00", 10) == 2);
    TEST_CHECK(lmu_czstrnlen("00", 1) == 1);
    TEST_CHECK(lmu_czstrnlen("00", 2) == 2);
    TEST_CHECK(lmu_czstrnlen("00", 3) == 2);
}

void str_to_czstr_check()
{
    lmu_str_t  s;
    lmu_str4_t s4 = {.data = {'a', 'b', 'c', 'd'}};
    lmu_str_init_str4(&s4, &s);
    char *c = lmu_str_to_czstr(&s);
    TEST_CHECK(c == 0);
    c = lmu_str_to_czstr_trunk(&s);
    TEST_CHECK(c != 0);
    const char *cmp = "abc";
    TEST_CHECK(strcmp(c, cmp) == 0);
}

void test_lmu_bin_cap()
{
    lmu_bin_t   b;
    lmu_bin32_t b32 = {};
    lmu_bin64_t b64 = {};
    lmu_cbin_t  cb;

    b32.length = 32;
    lmu_bin_init_bin32(&b32, &b);
    TEST_CHECK(lmu_bin_cap(&b) == 32);

    b32.length = 16;
    lmu_bin_init_bin32(&b32, &b);
    TEST_CHECK(lmu_bin_cap(&b) == 16);

    b64.length = 64;
    lmu_bin_init_bin64(&b64, &b);
    TEST_CHECK(lmu_bin_cap(&b) == 64);

    b64.length = 15;
    lmu_bin_init_bin64(&b64, &b);
    TEST_CHECK(lmu_bin_cap(&b) == 15);

    b32.length = 32;
    lmu_cbin_init_bin32(&b32, &cb);
    TEST_CHECK(lmu_cbin_cap(&cb) == 32);

    b32.length = 16;
    lmu_cbin_init_bin32(&b32, &cb);
    TEST_CHECK(lmu_cbin_cap(&cb) == 16);

    b64.length = 64;
    lmu_cbin_init_bin64(&b64, &cb);
    TEST_CHECK(lmu_cbin_cap(&cb) == 64);

    b64.length = 15;
    lmu_cbin_init_bin64(&b64, &cb);
    TEST_CHECK(lmu_cbin_cap(&cb) == 15);
}

void test_lmu_bin_copy()
{
    int         overflow = 0;
    lmu_bin_t   b, bc;
    lmu_bin32_t b32 = {};
    lmu_bin32_t b32c = {};
    lmu_cbin_t  cb;

    b32.length = 32;
    lmu_bin_init_bin32(&b32, &b);
    b32c.length = 32;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_bin_copy(&bc, &b, &overflow) == 32);
    TEST_CHECK(overflow == 0);

    b32.length = 16;
    lmu_bin_init_bin32(&b32, &b);
    b32c.length = 16;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_bin_copy(&bc, &b, &overflow) == 16);
    TEST_CHECK(overflow == 0);

    b32c.length = 15;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_bin_copy(&bc, &b, &overflow) == 15);
    TEST_CHECK(overflow == 1);

    b32.length = 15;
    lmu_bin_init_bin32(&b32, &b);
    b32c.length = 16;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_bin_copy(&bc, &b, &overflow) == 15);
    TEST_CHECK(overflow == 0);

    b32.length = 32;
    lmu_cbin_init_bin32(&b32, &cb);
    b32c.length = 32;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_cbin_copy(&bc, &cb, &overflow) == 32);
    TEST_CHECK(overflow == 0);

    b32.length = 16;
    lmu_cbin_init_bin32(&b32, &cb);
    b32c.length = 16;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_cbin_copy(&bc, &cb, &overflow) == 16);
    TEST_CHECK(overflow == 0);

    b32c.length = 15;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_cbin_copy(&bc, &cb, &overflow) == 15);
    TEST_CHECK(overflow == 1);

    b32.length = 15;
    lmu_cbin_init_bin32(&b32, &cb);
    b32c.length = 16;
    lmu_bin_init_bin32(&b32c, &bc);
    TEST_CHECK(lmu_cbin_copy(&bc, &cb, &overflow) == 15);
    TEST_CHECK(overflow == 0);
}

int  lmu_cbin_cmp(const lmu_cbin_t *a, const lmu_cbin_t *b);
void test_lmu_cbin_cmp()
{
    lmu_cbin_t  cb, cbc;
    lmu_bin32_t b32 = {};
    lmu_bin32_t b32c = {};

    b32.length = 32;
    b32.data[0] = 0xAA;
    b32.data[31] = 0xBB;
    lmu_cbin_init_bin32(&b32, &cb);
    b32c.length = 32;
    b32c.data[0] = 0xAA;
    b32c.data[31] = 0xBB;
    lmu_cbin_init_bin32(&b32c, &cbc);
    TEST_CHECK(lmu_cbin_cmp(&cbc, &cb) == 0);

    b32c.data[16] = 0xCC;
    TEST_CHECK(lmu_cbin_cmp(&cbc, &cb) == 1);

    b32c.length = 31;
    b32c.data[16] = 0;
    b32c.data[30] = 0xBB;
    b32.data[30] = 0xBB;
    lmu_cbin_init_bin32(&b32c, &cbc);
    TEST_CHECK(lmu_cbin_cmp(&cbc, &cb) == -1);

    b32c.length = 32;
    b32.length = 31;
    lmu_cbin_init_bin32(&b32, &cb);
    lmu_cbin_init_bin32(&b32c, &cbc);
    TEST_CHECK(lmu_cbin_cmp(&cbc, &cb) == 1);
}

void strlen_()
{
    lmu_str_t  s;
    lmu_str4_t s4 = {.data = {'a', 'b', 'c', 'd'}};
    lmu_str4_t s3 = {.data = {'a', 'b', 'c', 0}};
    lmu_str4_t s2 = {.data = {'a', 'b', 0, 0}};
    lmu_str4_t s1 = {.data = {'a', 0, 0, 0}};
    lmu_str4_t s0 = {.data = {0, 0, 0, 0}};

    lmu_str_init_str4(&s4, &s);
    TEST_CHECK(lmu_str_len(&s) == 4);

    lmu_str_init_str4(&s3, &s);
    TEST_CHECK(lmu_str_len(&s) == 3);

    lmu_str_init_str4(&s2, &s);
    TEST_CHECK(lmu_str_len(&s) == 2);

    lmu_str_init_str4(&s1, &s);
    TEST_CHECK(lmu_str_len(&s) == 1);

    lmu_str_init_str4(&s0, &s);
    TEST_CHECK(lmu_str_len(&s) == 0);
}

void fmt_u32_chk(int line, uint32_t val, const char *printf_fmt, size_t limit)
{
    size_t          res_e;
    lmu_ss_t        ss = {};
    char            expect[128];
    char            actual[128];
    char            name[128];
    lmu_fmt_state_t state = {};

    state.fmt = printf_fmt;
    state.ss = &ss;

    sprintf(name, "fmt_u32_chk:%d(%u, \"%s\", %zd)", line, val, printf_fmt,
            limit);

    TEST_CASE(name);

    memset(actual, 'x', 128);

    ss.buf.begin = actual;
    ss.buf.end = actual + limit;

    res_e = snprintf(expect, limit + 1, printf_fmt, val);
    lmu_fmt_u32(&state, val);

    if (ss.sslength == limit) {
        TEST_CHECK(*(ss.buf.begin + ss.sslength) == 'x');
        *(ss.buf.begin + ss.sslength) = 0;
    }

    if (limit < res_e) {
        TEST_CHECK(ss.overflow == 1);
        TEST_MSG("val: %u/%x", val, val);
        TEST_MSG("overflow: %u", ss.overflow);
    } else {
        TEST_CHECK(ss.sslength == res_e);
        TEST_MSG("val: %u/%x", val, val);
        TEST_MSG("Expect: %zu", res_e);
        TEST_MSG("Actual: %u", ss.sslength);
        TEST_CHECK(ss.overflow == 0);
    }
    TEST_CHECK(strcmp(expect, ss.buf.begin) == 0);
    TEST_MSG("Expect: >%s<", expect);
    TEST_MSG("Actual: >%s<", ss.buf.begin);
}

void fmt_u32_chk3(int line, uint32_t val, const char *printf_fmt_u,
                  const char *printf_fmt_x, const char *printf_fmt_X,
                  size_t limit)
{
    fmt_u32_chk(line, val, printf_fmt_u, limit);
    fmt_u32_chk(line, val, printf_fmt_x, limit);
    fmt_u32_chk(line, val, printf_fmt_X, limit);
}

void fmt_u32()
{
    fmt_u32_chk3(__LINE__, 0, "%u", "%x", "%X", 4);
    fmt_u32_chk3(__LINE__, 10, "%u", "%x", "%X", 4);
    fmt_u32_chk3(__LINE__, 123, "%u", "%x", "%X", 4);
    fmt_u32_chk3(__LINE__, 123, "%u", "%x", "%X", 3);
    fmt_u32_chk3(__LINE__, 123, "%u", "%x", "%X", 2);
    fmt_u32_chk3(__LINE__, 123, "%u", "%x", "%X", 1);
    fmt_u32_chk3(__LINE__, 123, "%u", "%x", "%X", 0);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%u", "%x", "%X", 20);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%u", "%x", "%X", 10);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%u", "%x", "%X", 9);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%u", "%x", "%X", 8);
    fmt_u32_chk3(__LINE__, 0xfffffffe, "%u", "%x", "%X", 20);

    fmt_u32_chk3(__LINE__, 255, "%hhu", "%hhx", "%hhX", 10);
    fmt_u32_chk3(__LINE__, 256, "%hhu", "%hhx", "%hhX", 10);
    fmt_u32_chk3(__LINE__, 257, "%hhu", "%hhx", "%hhX", 10);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%hhu", "%hhx", "%hhX", 10);

    fmt_u32_chk3(__LINE__, 0xffff, "%hu", "%hx", "%hX", 10);
    fmt_u32_chk3(__LINE__, 0xaffff, "%hu", "%hx", "%hX", 10);
    fmt_u32_chk3(__LINE__, 0xffffffff, "%hu", "%hx", "%hX", 10);

    fmt_u32_chk3(__LINE__, 1234, "%0u", "%0x", "%0X", 10);

    fmt_u32_chk3(__LINE__, 0x12AE, "%6u", "%6x", "%6X", 10);
    fmt_u32_chk3(__LINE__, 0x12AE, "%06u", "%06x", "%06X", 10);
    fmt_u32_chk3(__LINE__, 0x12AE, "%-6u", "%-6x", "%-6X", 10);

    fmt_u32_chk3(__LINE__, 0x12AE, "%6u", "%6x", "%6X", 5);
    fmt_u32_chk3(__LINE__, 0x12AE, "%06u", "%06x", "%06X", 5);
    fmt_u32_chk3(__LINE__, 0x12AE, "%-6u", "%-6x", "%-6X", 5);

    fmt_u32_chk3(__LINE__, 0x12AE, "%9u", "%9x", "%9X", 5);
    fmt_u32_chk3(__LINE__, 0x12AE, "%09u", "%09x", "%09X", 5);
    fmt_u32_chk3(__LINE__, 0x12AE, "%-9u", "%-9x", "%-9X", 5);
}

void fmt_i32_chk(int line, int32_t val, const char *printf_fmt, lmu_fmt_t *fmt,
                 size_t limit)
{
    size_t          res_e;
    lmu_ss_t        ss = {};
    char            expect[128];
    char            actual[128];
    char            name[128];
    lmu_fmt_state_t state = {};

    memset(actual, 'x', 128);

    sprintf(name, "fmt_i32_chk:%d(%i, \"%s\", %zd)", line, val, printf_fmt,
            limit);

    TEST_CASE(name);
    ss.buf.begin = actual;
    ss.buf.end = actual + limit;
    state.fmt = printf_fmt;
    state.ss = &ss;

    res_e = snprintf(expect, limit + 1, printf_fmt, val);
    lmu_fmt_i32(&state, val);

    if (ss.sslength == limit) {
        TEST_CHECK(*(ss.buf.begin + ss.sslength) == 'x');
        *(ss.buf.begin + ss.sslength) = 0;
    }

    if (limit < res_e) {
        TEST_CHECK(ss.overflow == 1);
        TEST_MSG("val: %d/%x", val, val);
        TEST_MSG("overflow: %u", ss.overflow);
    } else {
        TEST_CHECK(ss.sslength == res_e);
        TEST_MSG("val: %d/%x", val, val);
        TEST_MSG("Expect: %zu", res_e);
        TEST_MSG("Actual: %u", ss.sslength);
        TEST_CHECK(ss.overflow == 0);
    }
    TEST_CHECK(strcmp(expect, ss.buf.begin) == 0);
    TEST_MSG("Expect: >%s<", expect);
    TEST_MSG("Actual: >%s<", ss.buf.begin);
}

void fmt_i32()
{
    int       i;
    lmu_fmt_t fmt = {};
    fmt.conv = LMU_FMT_CONV_DEC_SIGNED;

    fmt_i32_chk(__LINE__, 0, "%d", &fmt, 4);
    fmt_i32_chk(__LINE__, 1, "%d", &fmt, 4);
    fmt_i32_chk(__LINE__, -1, "%d", &fmt, 4);
    fmt_i32_chk(__LINE__, 10, "%d", &fmt, 4);
    fmt_i32_chk(__LINE__, 110, "%d", &fmt, 4);
    fmt_i32_chk(__LINE__, -110, "%d", &fmt, 4);

    fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_FORCE;
    fmt_i32_chk(__LINE__, 0, "%+d", &fmt, 4);
    fmt_i32_chk(__LINE__, 1, "%+d", &fmt, 4);
    fmt_i32_chk(__LINE__, -1, "%+d", &fmt, 4);
    fmt_i32_chk(__LINE__, 10, "%+d", &fmt, 4);
    fmt_i32_chk(__LINE__, 1120, "%+d", &fmt, 4);
    fmt_i32_chk(__LINE__, -1120, "%+d", &fmt, 4);

    fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_SPACE;
    fmt_i32_chk(__LINE__, 0, "% d", &fmt, 4);
    fmt_i32_chk(__LINE__, 1, "% d", &fmt, 4);
    fmt_i32_chk(__LINE__, -1, "% d", &fmt, 4);
    fmt_i32_chk(__LINE__, 10, "% d", &fmt, 4);
    fmt_i32_chk(__LINE__, 1120, "% d", &fmt, 4);
    fmt_i32_chk(__LINE__, -1120, "% d", &fmt, 4);

    for (i = 0; i < 10; ++i) {
        fmt.width = 6;
        fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_SPACE | LMU_FMT_FLAG_PAD_SPACE;
        fmt_i32_chk(__LINE__, 0, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1120, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1120, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, -12013, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, 11012, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, -120123, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, 110123, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1120123, "% 6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1120123, "% 6d", &fmt, i);
        fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_FORCE | LMU_FMT_FLAG_PAD_SPACE;
        fmt_i32_chk(__LINE__, 0, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1120, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1120, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, -11320, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, 11230, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, -114420, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, 114420, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1166620, "%+6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1155520, "%+6d", &fmt, i);
        fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_SPACE;
        fmt_i32_chk(__LINE__, 0, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1120, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1120, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, -14120, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, 11420, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, -155120, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, 115520, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1666120, "% -6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1155520, "% -6d", &fmt, i);
        fmt.lmu_fmt_flag = LMU_FMT_FLAG_SIGN_FORCE;
        fmt_i32_chk(__LINE__, 0, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1120, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1120, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, -13120, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, 11320, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, -144120, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, 114420, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, -1555120, "%+-6d", &fmt, i);
        fmt_i32_chk(__LINE__, 1155520, "%+-6d", &fmt, i);
    }

    fmt.width = 0;
    fmt.lmu_fmt_flag = LMU_FMT_FLAG_NONE;

    for (i = -300; i < 300; i++) {
        fmt.len = LMU_FMT_LENMOD_NONE;
        fmt_i32_chk(__LINE__, i, "%d", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_H;
        fmt_i32_chk(__LINE__, i, "%hd", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_HH;
        fmt_i32_chk(__LINE__, i, "%hhd", &fmt, 4);
    }

    for (i = 0xfffa; i < 0x1000a; i++) {
        fmt.len = LMU_FMT_LENMOD_NONE;
        fmt_i32_chk(__LINE__, i, "%d", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_H;
        fmt_i32_chk(__LINE__, i, "%hd", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_HH;
        fmt_i32_chk(__LINE__, i, "%hhd", &fmt, 4);
    }

    for (i = 0x7ffa; i < 0x800a; i++) {
        fmt.len = LMU_FMT_LENMOD_NONE;
        fmt_i32_chk(__LINE__, i, "%d", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_H;
        fmt_i32_chk(__LINE__, i, "%hd", &fmt, 4);
        fmt.len = LMU_FMT_LENMOD_HH;
        fmt_i32_chk(__LINE__, i, "%hhd", &fmt, 4);
    }
}

void parse_u32_(int line, const char *in, uint32_t expect, size_t size,
                uint8_t radix, uint8_t min_digit, uint8_t max_digit,
                uint32_t max_val, uint32_t min_val)
{
    size_t              res;
    lmu_cstr_t          s;
    lmu_parse_u32_cxt_t conf = {};

    char name[200];
    sprintf(name, "parse_u32_:%d str: >%s<, size: %zd, d: %d/%d, v: %u/%u",
            line, in, size, min_digit, max_digit, min_val, max_val);

    TEST_CASE(name);

    s = lmu_czstr_to_cstr(in);
    conf.radix = radix;
    conf.min_digit = min_digit;
    conf.max_digit = max_digit;
    conf.max_val = max_val;
    conf.min_val = min_val;
    res = lmu_parse_u32(&s, &conf);
    TEST_CHECK(res == size);
    TEST_MSG("Actual: %zu", res);
    TEST_MSG("Expect: %zu", size);

    TEST_CHECK(conf.val == expect);
    TEST_MSG("Actual: %u", conf.val);
    TEST_MSG("Expect: %u", expect);
}

void parse_u32()
{
    parse_u32_(__LINE__, "", 0, 0, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "0", 0, 1, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "00", 0, 2, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "001", 1, 3, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "1", 1, 1, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "1a", 1, 1, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "4294967295", 4294967295, 10, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "4312345678", 431234567, 9, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "4294967296", 429496729, 9, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "42949672959", 4294967295, 10, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "10000000000", 1000000000, 10, 0, 0, 0, 0, 0);
    parse_u32_(__LINE__, "12345678912", 1234567891, 10, 0, 0, 0, 0, 0);
}

void parse_fmt_(int line, const char *in, size_t size, uint8_t lmu_fmt_flag,
                uint8_t width, uint8_t len, uint8_t conv)
{
    size_t     res;
    lmu_cstr_t s;
    lmu_fmt_t  val = {};

    s = lmu_czstr_to_cstr(in);

    char name[200];
    sprintf(name, "parse_fmt:%d str: >%s<, %zu %hhx/%hhu/%hhu/%hhu", line, in,
            size, lmu_fmt_flag, width, len, conv);

    TEST_CASE(name);
    res = lmu_parse_fmt(&s, &val);

    TEST_CHECK(res == size);
    TEST_MSG("Actual: %zu", res);
    TEST_MSG("Expect: %zu", size);

    TEST_CHECK(val.width == width);
    TEST_MSG("Actual: %hhu", val.width);
    TEST_MSG("Expect: %hhu", width);

    TEST_CHECK(val.lmu_fmt_flag == lmu_fmt_flag);
    TEST_MSG("Actual: %hhx", (uint8_t)val.lmu_fmt_flag);
    TEST_MSG("Expect: %hhx", lmu_fmt_flag);

    TEST_CHECK(val.len == len);
    TEST_MSG("Actual: %hhx", (uint8_t)val.len);
    TEST_MSG("Expect: %hhx", len);

    TEST_CHECK(val.conv == conv);
    TEST_MSG("Actual: %hhx", (uint8_t)val.conv);
    TEST_MSG("Expect: %hhx", conv);
}

void parse_fmt()
{
    parse_fmt_(__LINE__, "%d", 2, 0, 0, 0, LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "%k", 0, 0, 0, 0, 0);
    parse_fmt_(__LINE__, " %d", 0, 0, 0, 0, 0);
    parse_fmt_(__LINE__, "%4di", 3, LMU_FMT_FLAG_PAD_SPACE, 4, 0,
               LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "%-4di", 4, 0, 4, 0, LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "% -4dasd", 5, LMU_FMT_FLAG_SIGN_SPACE, 4, 0,
               LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "%+-4dd", 5, LMU_FMT_FLAG_SIGN_FORCE, 4, 0,
               LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "%+4dx", 4,
               LMU_FMT_FLAG_PAD_SPACE | LMU_FMT_FLAG_SIGN_FORCE, 4, 0,
               LMU_FMT_CONV_DEC_SIGNED);
    parse_fmt_(__LINE__, "%06u", 4, LMU_FMT_FLAG_PAD_ZERO, 6, 0,
               LMU_FMT_CONV_DEC_UNSIGNED);
    parse_fmt_(__LINE__, "%06hu", 5, LMU_FMT_FLAG_PAD_ZERO, 6, LMU_FMT_LENMOD_H,
               LMU_FMT_CONV_DEC_UNSIGNED);
    parse_fmt_(__LINE__, "%06hhu", 6, LMU_FMT_FLAG_PAD_ZERO, 6,
               LMU_FMT_LENMOD_HH, LMU_FMT_CONV_DEC_UNSIGNED);
}

void str_cmp()
{
    int         i, r, rr;
    lmu_cstr_t  sa, sb;
    const char *a[] = {"aaaa", "aaa", "aaaa", "aab", "aac"};
    const char *b[] = {"aaaa", "aaaa", "aaa", "aac", "aab"};
    const int   res[] = {0, -1, 1, -1, 1};
    char        name[128];

    for (i = 0; i < 5; i++) {
        sprintf(name, "i==%d: %s cmp %s -> %d", i, a[i], b[i], res[i]);
        TEST_CASE(name);
        sa = lmu_czstr_to_cstr(a[i]);
        sb = lmu_czstr_to_cstr(b[i]);
        rr = strcmp(a[i], b[i]);
        r = lmu_cstr_cmp(&sa, &sb);
        TEST_CHECK(r == res[i]);
        TEST_MSG("Actual: %d", r);
        TEST_MSG("Expect: %d", res[i]);
        TEST_MSG("Expect (sslength): %d", rr);
        TEST_CHECK(r == (rr < 0 ? -1 : (rr > 0 ? 1 : 0)));
        TEST_MSG("Actual: %d", r);
        TEST_MSG("Expect: %d", res[i]);
        TEST_MSG("Expect (sslength): %d", rr);
    }
}

void cstr_split()
{
    int         res, i = 0;
    lmu_cstr_t  in, out;
    const char *_in = "asdf,ASDF-AA..,as";
    const char *a[] = {"asdf", ",", "ASDF-AA..", ",", "as"};
    const int   rr[] = {LMU_STR_SPLIT_TOKEN, LMU_STR_SPLIT_DELIM,
                        LMU_STR_SPLIT_TOKEN, LMU_STR_SPLIT_DELIM,
                        LMU_STR_SPLIT_TOKEN};
    char        name[128];

    in = lmu_czstr_to_cstr(_in);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_TOKEN);
    TEST_MSG("res: %d", res);
    TEST_CHECK(lmu_cstr_czstr_cmp(&out, "asdf") == 0);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_DELIM);
    TEST_MSG("res: %d", res);
    TEST_CHECK(lmu_cstr_czstr_cmp(&out, ",") == 0);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_TOKEN);
    TEST_MSG("res: %d", res);
    TEST_CHECK(lmu_cstr_czstr_cmp(&out, "ASDF-AA..") == 0);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_DELIM);
    TEST_MSG("res: %d", res);
    TEST_CHECK(lmu_cstr_czstr_cmp(&out, ",") == 0);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_TOKEN);
    TEST_MSG("res: %d", res);
    TEST_CHECK(lmu_cstr_czstr_cmp(&out, "as") == 0);

    res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out);
    in.begin = out.end;
    TEST_CHECK(res == LMU_STR_SPLIT_END);
    TEST_MSG("res: %d", res);

    in.begin = (char *)_in;
    in.end = (char *)_in + lmu_czstrlen(_in);
    while ((res = lmu_cstr_split(&in, &lmu_parse_flag_, ",", &out))) {
        sprintf(name, "loop %d", i);
        TEST_CASE(name);
        TEST_CHECK(res == rr[i]);
        TEST_MSG("%d == rr[%d]/%d", res, i, rr[i]);
        TEST_CHECK(lmu_cstr_czstr_cmp(&out, a[i]) == 0);
        i++;
        in.begin = out.end;
    }
}

void ss_fmt()
{
    lmu_str32_t      s32;
    lmu_str64_t      s64;
    lmu_ss_t         ss;
    lmu_str_t        str;
    lm_ipv4_t        ipv4 = {.data = {1, 2, 3, 4}};
    lm_ipv4_prefix_t ipv4p = {.ipv4 = ipv4, .prefix = 16};
    lm_ipv6_t        ipv6 = {};
    lm_ipv6_prefix_t ipv6p = {};
    lm_mac_t         mac = {.data = {0, 0xde, 0xad, 0xbe, 0xef, 0}};
    lmu_bin4_t       bin4 = {.data = {0x20, 0x24, 0x12, 0x24}, .length = 4};
    lm_port_list_t   pl = {.private_ = {0x11, 0x22, 0x44, 0x88}};
    uint8_t          i;

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %s, %d", "world", 3);

    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello world, 3") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %-15s", &ipv4);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 1.2.3.4        ") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %15s", &ipv4);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello         1.2.3.4") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %020s", &ipv4);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 001.002.003.004     ") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv4p);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 1.2.3.4/16") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str64(&s64, &str);
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello ::") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    ipv6.data[15] = 16;
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello ::10") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    ipv6.data[0] = 1;
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 100::10") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    ipv6.data[7] = 8;
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 100:0:0:8::10") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    for (i = 0; i < 16; i++) {
        ipv6.data[i] = (i + 1);
    }
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6);
    TEST_CHECK(
        lmu_str_czstr_cmp(&str, "Hello 102:304:506:708:90A:B0C:D0E:F10") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6p);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello ::/0") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    ipv6p.ipv6 = ipv6;
    ipv6p.prefix = 128;
    lmu_ss_init_str64(&s64, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &ipv6p);
    TEST_CHECK(lmu_str_czstr_cmp(
                   &str, "Hello 102:304:506:708:90A:B0C:D0E:F10/128") == 0);
    TEST_MSG("Actual: >%s<", s64.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &mac);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 00-DE-AD-BE-EF-00") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &bin4);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 20-24-12-24") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %s", &pl);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello 88442211") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %%");
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello %") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    char char_val = 'a';
    LMU_SS_FMT(&ss, "Hello %c", char_val);
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello a") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    lmu_str_init_str32(&s32, &str);
    lmu_ss_init_str32(&s32, &ss);
    LMU_SS_FMT(&ss, "Hello %c", 'a');
    TEST_CHECK(lmu_str_czstr_cmp(&str, "Hello a") == 0);
    TEST_MSG("Actual: >%s<", s32.data);

    {
        int64_t value = 0LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 0") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 1000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 1000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 2000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 2000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 3000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 3000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 4000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 4000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 5000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 5000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        value = 6000000000LL;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "int64_t value(as lld) = %lld", value);
        TEST_CHECK(
            lmu_str_czstr_cmp(&str, "int64_t value(as lld) = 6000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);
    }
    {
        uint64_t uvalue = 0LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(&str, "uint64_t uvalue(as llu) = 0") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 1000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 1000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 2000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 2000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 3000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 3000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 4000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 4000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 5000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 5000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);

        uvalue = 6000000000LLU;
        lmu_str_init_str64(&s64, &str);
        lmu_ss_init_str64(&s64, &ss);
        LMU_SS_FMT(&ss, "uint64_t uvalue(as llu) = %llu", uvalue);
        TEST_CHECK(lmu_str_czstr_cmp(
                       &str, "uint64_t uvalue(as llu) = 6000000000") == 0);
        TEST_MSG("Actual: >%s<", s64.data);
    }
}

void test_lmu_parse_mac()
{
    lm_mac_t   m = {0};
    lmu_cstr_t s;
    size_t     sz;

    s = lmu_czstr_to_cstr("  01-22-33-44-fF-ac");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 19);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK(((m.data[0] == 0x01) && (m.data[1] == 0x22) &&
                (m.data[2] == 0x33) && (m.data[3] == 0x44) &&
                (m.data[4] == 0xFF) && (m.data[5] == 0xAC)));

    s = lmu_czstr_to_cstr("ff-ff-ff-FF-FF-FF");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 17);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK(((m.data[0] == 0xFF) && (m.data[1] == 0xFF) &&
                (m.data[2] == 0xFF) && (m.data[3] == 0xFF) &&
                (m.data[4] == 0xFF) && (m.data[5] == 0xFF)));

    s = lmu_czstr_to_cstr("  gg-00-11-FF-FF-FF");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 0);

    s = lmu_czstr_to_cstr("asdf");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 0);

    s = lmu_czstr_to_cstr(" asdf01-22-33-44-fF-ac");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 0);

    s = lmu_czstr_to_cstr("    01-22-33-44-fF-acextra");
    sz = lmu_parse_mac(&s, &m);
    TEST_CHECK(sz == 21);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK(((m.data[0] == 0x01) && (m.data[1] == 0x22) &&
                (m.data[2] == 0x33) && (m.data[3] == 0x44) &&
                (m.data[4] == 0xFF) && (m.data[5] == 0xAC)));
}

void test_lmu_parse_ipv4()
{
    lm_ipv4_t  i = {0};
    lmu_cstr_t s;
    size_t     sz;

    // These must pass:
    s = lmu_czstr_to_cstr("1.2.3.4");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 7);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 1) && (i.data[1] == 2) && (i.data[2] == 3) &&
               (i.data[3] == 4));

    s = lmu_czstr_to_cstr("011.022.033.044");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 15);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 11) && (i.data[1] == 22) && (i.data[2] == 33) &&
               (i.data[3] == 44));

    // Ignore initial whitespace
    s = lmu_czstr_to_cstr("   5.6.007.8");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 12);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 5) && (i.data[1] == 6) && (i.data[2] == 7) &&
               (i.data[3] == 8));

    // Ignore data after ipv4
    s = lmu_czstr_to_cstr("5.6.7.8-");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 7);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 5) && (i.data[1] == 6) && (i.data[2] == 7) &&
               (i.data[3] == 8));

    // Ignore data after ipv4
    s = lmu_czstr_to_cstr("5.6.7.8asdf");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 7);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 5) && (i.data[1] == 6) && (i.data[2] == 7) &&
               (i.data[3] == 8));

    // Ignore data after ipv4
    s = lmu_czstr_to_cstr("5.6.7.8    ");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 7);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.data[0] == 5) && (i.data[1] == 6) && (i.data[2] == 7) &&
               (i.data[3] == 8));

    // These must fail:
    s = lmu_czstr_to_cstr("5.6.7.256");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("5.6.7.");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("5.6.7");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("1-2-3-4");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("1::5.6.7.8");
    sz = lmu_parse_ipv4(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);
}

void test_lmu_parse_ipv4_prefix()
{
    lm_ipv4_prefix_t i = {0};
    lmu_cstr_t       s;
    size_t           sz;

    // These must pass:
    s = lmu_czstr_to_cstr("1.2.3.4/16");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 10);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.ipv4.data[0] == 1) && (i.ipv4.data[1] == 2) &&
               (i.ipv4.data[2] == 3) && (i.ipv4.data[3] == 4) &&
               (i.prefix == 16));

    s = lmu_czstr_to_cstr("  1.2.3.4/16");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 12);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.ipv4.data[0] == 1) && (i.ipv4.data[1] == 2) &&
               (i.ipv4.data[2] == 3) && (i.ipv4.data[3] == 4) &&
               (i.prefix == 16));

    s = lmu_czstr_to_cstr("1.2.3.4/16asdf");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 10);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.ipv4.data[0] == 1) && (i.ipv4.data[1] == 2) &&
               (i.ipv4.data[2] == 3) && (i.ipv4.data[3] == 4) &&
               (i.prefix == 16));

    s = lmu_czstr_to_cstr("1.2.3.4/0");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 9);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.ipv4.data[0] == 1) && (i.ipv4.data[1] == 2) &&
               (i.ipv4.data[2] == 3) && (i.ipv4.data[3] == 4) &&
               (i.prefix == 0));

    s = lmu_czstr_to_cstr("1.2.3.4/32");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 10);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK((i.ipv4.data[0] == 1) && (i.ipv4.data[1] == 2) &&
               (i.ipv4.data[2] == 3) && (i.ipv4.data[3] == 4) &&
               (i.prefix == 32));

    // These must fail:
    s = lmu_czstr_to_cstr("1.2.3.4 /16");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("1.2.3.4/ 16");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("1.2.3.4/33");
    sz = lmu_parse_ipv4_prefix(&s, &i);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);
}

void test_lmu_parse_ipv6()
{
    lm_ipv6_t        a = {0}, e = {};
    lm_ipv6_prefix_t pfx = {};
    uint8_t         *p = e.data, i;
    lmu_cstr_t       s;
    size_t           sz;

    TEST_CASE("Address parser tests");
    s = lmu_czstr_to_cstr("::");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 2);
    TEST_MSG("Size: %zu", sz);
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr("1::2");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 4);
    TEST_MSG("Size: %zu", sz);
    p[1] = 1;
    p[15] = 2;
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr("102:304:506:708:90a:B0C:d0E:f10");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 31);
    TEST_MSG("Size: %zu", sz);
    for (i = 0; i < 16; i++) {
        p[i] = (i + 1);
    }
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr("102:304::d0E:f10");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 16);
    TEST_MSG("Size: %zu", sz);
    for (i = 0; i < 16; i++) {
        p[i] = ((i < 4 || i > 11) ? (i + 1) : 0);
    }
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr("::12.13.14.15");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 13);
    TEST_MSG("Size: %zu", sz);
    for (i = 0; i < 16; i++) {
        p[i] = (i > 11 ? i : 0);
    }
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr("1::12.13.14.15");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 14);
    TEST_MSG("Size: %zu", sz);
    for (i = 0; i < 16; i++) {
        p[i] = ((i < 2 || i > 11) ? i : 0);
    }
    TEST_CHECK(lmu_memcmp(a.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", a.data, 16);
    TEST_DUMP("Expected:", e.data, 16);

    s = lmu_czstr_to_cstr(":::");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr(":: ");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr(" :: ");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    s = lmu_czstr_to_cstr("12345::");
    sz = lmu_parse_ipv6(&s, &a);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);

    TEST_CASE("Prefix parser tests");
    s = lmu_czstr_to_cstr("::/0");
    sz = lmu_parse_ipv6_prefix(&s, &pfx);
    TEST_CHECK(sz == 4);
    TEST_MSG("Size: %zu", sz);
    for (i = 0; i < 16; i++) {
        p[i] = 0;
    }
    TEST_CHECK(lmu_memcmp(pfx.ipv6.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", pfx.ipv6.data, 16);
    TEST_DUMP("Expected:", e.data, 16);
    TEST_CHECK(pfx.prefix == 0);

    s = lmu_czstr_to_cstr("1::2/128");
    sz = lmu_parse_ipv6_prefix(&s, &pfx);
    TEST_CHECK(sz == 8);
    TEST_MSG("Size: %zu", sz);
    p[1] = 1;
    p[15] = 2;
    TEST_CHECK(lmu_memcmp(pfx.ipv6.data, e.data, 16) == 0);
    TEST_DUMP("Actual:", pfx.ipv6.data, 16);
    TEST_DUMP("Expected:", e.data, 16);
    TEST_CHECK(pfx.prefix == 128);

    s = lmu_czstr_to_cstr("1::2/129");
    sz = lmu_parse_ipv6_prefix(&s, &pfx);
    TEST_CHECK(sz == 0);
    TEST_MSG("Size: %zu", sz);
}

void test_lmu_ss_append_cstr()
{
    lmu_str8_t s8;
    lmu_ss_t   ss;
    lmu_cstr_t cs;

    lmu_ss_init_str8(&s8, &ss);
    TEST_CHECK(ss.sslength == 0);
    TEST_CHECK(ss.overflow == 0);

    cs = lmu_czstr_to_cstr("asdf");
    lmu_ss_append_cstr(&ss, &cs);
    TEST_CHECK(ss.sslength == 4);
    TEST_CHECK(ss.overflow == 0);

    cs = lmu_czstr_to_cstr("1234");
    lmu_ss_append_cstr(&ss, &cs);
    TEST_CHECK(ss.sslength == 8);
    TEST_CHECK(ss.overflow == 0);

    cs = lmu_czstr_to_cstr("?");
    lmu_ss_append_cstr(&ss, &cs);
    TEST_CHECK(ss.sslength == 8);
    TEST_CHECK(ss.overflow == 1);
}

void test_lmu_rbuf_reset()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);

    rbuf.head = 4;
    rbuf.tail = 7;

    lmu_rbuf_reset(&rbuf);
    TEST_CHECK(rbuf.head == 0);
    TEST_CHECK(rbuf.tail == 0);
}

void test_lmu_rbuf_empty()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    lmu_bool_t test;

    test = lmu_rbuf_empty(&rbuf);
    TEST_CHECK(test == LMU_TRUE);

    rbuf.head = 4;
    rbuf.tail = 7;
    test = lmu_rbuf_empty(&rbuf);
    TEST_CHECK(test == LMU_FALSE);

    rbuf.tail = 4;
    test = lmu_rbuf_empty(&rbuf);
    TEST_CHECK(test == LMU_TRUE);
}

void test_lmu_rbuf_full()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    lmu_bool_t test;

    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_FALSE);

    rbuf.head = 4;
    rbuf.tail = 7;
    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_FALSE);

    rbuf.tail = 4;
    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_FALSE);

    rbuf.tail = 5;
    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_TRUE);

    rbuf.head = 0;
    rbuf.tail = 1;
    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_TRUE);

    rbuf.head = RBUF_SIZE;
    rbuf.tail = 0;
    test = lmu_rbuf_full(&rbuf);
    TEST_CHECK(test == LMU_TRUE);
}

void test_lmu_rbuf_capacity()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    uint16_t test;

    test = lmu_rbuf_capacity(&rbuf);
    TEST_CHECK(test == RBUF_SIZE);
}

void test_lmu_rbuf_remaining()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    uint16_t test;

    test = lmu_rbuf_remaining(&rbuf);
    TEST_CHECK(test == RBUF_SIZE);

    rbuf.head = 0;
    rbuf.tail = 1;
    test = lmu_rbuf_remaining(&rbuf);
    TEST_CHECK(test == 0);

    rbuf.head = 1;
    rbuf.tail = 0;
    test = lmu_rbuf_remaining(&rbuf);
    TEST_CHECK(test == RBUF_SIZE - 1);
}

void test_lmu_rbuf_size()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    uint16_t test;

    test = lmu_rbuf_size(&rbuf);
    TEST_CHECK(test == 0);

    rbuf.head = 1;
    rbuf.tail = 1;
    test = lmu_rbuf_size(&rbuf);
    TEST_CHECK(test == 0);

    rbuf.head = RBUF_SIZE;
    rbuf.tail = RBUF_SIZE;
    test = lmu_rbuf_size(&rbuf);
    TEST_CHECK(test == 0);

    rbuf.head = 1;
    rbuf.tail = 0;
    test = lmu_rbuf_size(&rbuf);
    TEST_CHECK(test == 1);

    rbuf.head = 9;
    rbuf.tail = RBUF_SIZE;
    test = lmu_rbuf_size(&rbuf);
    TEST_CHECK(test == 10);
}

void test_lmu_rbuf_push()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);
    uint8_t  data[] = {12, 23, 34, 45, 56, 67, 78};
    uint32_t i;
    lm_rc_t  rc;

    rc = lmu_rbuf_push(&rbuf, 1, &data[0]);
    TEST_CHECK(rc == LM_RC_OK);
    TEST_CHECK(rbuf.buf[0] == data[0]);
    TEST_CHECK(rbuf.head == 1);
    TEST_CHECK(rbuf.tail == 0);

    for (i = 1; i < sizeof(data); ++i) {
        rc = lmu_rbuf_push(&rbuf, 1, &data[i]);
        TEST_CHECK(rc == LM_RC_OK);
        TEST_CHECK(rbuf.buf[i] == data[i]);
        TEST_CHECK(rbuf.head == i + 1);
        TEST_CHECK(rbuf.tail == 0);
    }

    lmu_rbuf_reset(&rbuf);
    rbuf.head = RBUF_SIZE - 1;
    rc = lmu_rbuf_push(&rbuf, 1, &data[0]);
    TEST_CHECK(rc == LM_RC_OK);
    rc = lmu_rbuf_push(&rbuf, 1, &data[1]);
    TEST_CHECK(rc == LM_RC_OUT_OF_MEMORY);
}

void test_lmu_rbuf_pop()
{
    LMU_RBUF_DEF(rbuf, RBUF_SIZE);

    uint8_t data[] = {12, 23, 34, 45, 56, 67, 78};
    uint8_t i;
    uint8_t test[sizeof(data)];
    lm_rc_t rc;

    rc = lmu_rbuf_push(&rbuf, sizeof(data), data);
    TEST_CHECK(rc == LM_RC_OK);

    rc = lmu_rbuf_pop(&rbuf, sizeof(data), test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < sizeof(data); ++i) {
        TEST_CHECK(test[i] == data[i]);
    }

    rc = lmu_rbuf_pop(&rbuf, 1, test);
    TEST_CHECK(rc = LM_RC_ERROR);

    rbuf.tail = RBUF_SIZE - sizeof(data) / 2;
    rbuf.head = rbuf.tail;

    rc = lmu_rbuf_push(&rbuf, sizeof(data), data);
    TEST_CHECK(rc == LM_RC_OK);

    rc = lmu_rbuf_pop(&rbuf, sizeof(data), test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < sizeof(data); ++i) {
        TEST_CHECK(test[i] == data[i]);
    }

    rc = lmu_rbuf_pop(&rbuf, 1, test);
    TEST_CHECK(rc = LM_RC_ERROR);
}

void test_lmu_rbuf_read_advance()
{
    LMU_RBUF_DEF(rbuf, 8);

    uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint8_t test[8];
    lm_rc_t rc;
    uint8_t i;

    // Check size = 0
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 0);

    rc = lmu_rbuf_push(&rbuf, 8, data);
    TEST_CHECK(rc == LM_RC_OK);

    // Check size = 8
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);

    // Check that push fails
    rc = lmu_rbuf_push(&rbuf, 1, data);
    TEST_CHECK(rc != LM_RC_OK);

    // Check that pop(4) is ok
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_pop(&rbuf, 4, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i] == data[i]);
    }

    // Check size = 4
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 4);

    // Check that read(4) is ok
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_read(&rbuf, 0, 4, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i] == data[i + 4]);
    }

    // Check that read(5) fails
    rc = lmu_rbuf_read(&rbuf, 0, 5, test);
    TEST_CHECK(rc != LM_RC_OK);

    // Add 4 more that wraps
    rc = lmu_rbuf_push(&rbuf, 4, data);
    TEST_CHECK(rc == LM_RC_OK);

    // Check size = 8
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);

    // Test wrapped read
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_read(&rbuf, 0, 8, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i] == data[i + 4]);
    }
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i + 4] == data[i]);
    }

    // Test wrapped read with offset
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_read(&rbuf, 2, 6, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 2; i++) {
        TEST_CHECK(test[i] == data[i + 6]);
    }
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i + 2] == data[i]);
    }

    // Check size = 8
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);

    rc = lmu_rbuf_advance(&rbuf, 2);
    // Check size = 6
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 6);

    // Test wrapped read after advance
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_read(&rbuf, 0, 6, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 2; i++) {
        TEST_CHECK(test[i] == data[i + 6]);
    }
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i + 2] == data[i]);
    }

    rc = lmu_rbuf_advance(&rbuf, 4);
    // Check size = 2
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 2);

    // Test read after advance
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_read(&rbuf, 0, 2, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 2; i++) {
        TEST_CHECK(test[i] == data[i + 2]);
    }

    // Check that read(3) fails
    rc = lmu_rbuf_read(&rbuf, 0, 3, test);
    TEST_CHECK(rc != LM_RC_OK);

    // Check size = 6
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 2);
}

void test_lmu_rbuf_discard()
{
    LMU_RBUF_DEF(rbuf, 8);

    uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint8_t test[8];
    lm_rc_t rc;
    uint8_t i;

    // Check size = 0
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 0);

    // push 8
    rc = lmu_rbuf_push(&rbuf, 8, data);
    TEST_CHECK(rc == LM_RC_OK);
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);

    // discard 4
    rc = lmu_rbuf_discard(&rbuf, 4);
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 4);

    // push 4
    rc = lmu_rbuf_push(&rbuf, 4, data);
    TEST_CHECK(rc == LM_RC_OK);
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);

    // pop 4
    memset(test, 0, sizeof(test));
    rc = lmu_rbuf_pop(&rbuf, 4, test);
    TEST_CHECK(rc == LM_RC_OK);
    for (i = 0; i < 4; i++) {
        TEST_CHECK(test[i] == data[i]);
    }
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 4);

    // push 4 (head must wrap here)
    rc = lmu_rbuf_push(&rbuf, 4, data);
    TEST_CHECK(rc == LM_RC_OK);
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 8);
    TEST_CHECK(rbuf.head == 3);
    TEST_CHECK(rbuf.tail == 4);

    // discard 6 (head must wrap here)
    rc = lmu_rbuf_discard(&rbuf, 6);
    TEST_CHECK(lmu_rbuf_size(&rbuf) == 2);
    TEST_CHECK(rbuf.head == 6);
    TEST_CHECK(rbuf.tail == 4);
}

void test_lmu_data()
{
    uint8_t   i, data[6];
    lm_ipv4_t addr = {.data = {4, 5, 6, 7}};
    lm_mac_t  mac = {.data = {1, 2, 3, 4, 5, 6}};

    TEST_CASE("data_u16");
    lmu_data_u16_put(data, 0x0102);
    for (i = 0; i < 2; i++) {
        data[i]++;
    }
    TEST_CHECK(lmu_data_u16_get(data) == 0x0203);

    TEST_CASE("data_u32");
    lmu_data_u32_put(data, 0x01020304);
    for (i = 0; i < 4; i++) {
        data[i]++;
    }
    TEST_CHECK(lmu_data_u32_get(data) == 0x02030405);

    TEST_CASE("data_ipv4");
    lmu_data_ipv4_put(data, &addr);
    for (i = 0; i < 4; i++) {
        data[i]++;
    }
    lmu_data_ipv4_get(data, &addr);
    TEST_CHECK(lmu_data_u32_get(addr.data) == 0x5060708);

    TEST_CASE("data_mac");
    lmu_data_mac_put(data, &mac);
    for (i = 0; i < 6; i++) {
        data[i]++;
    }
    lmu_data_mac_get(data, &mac);
    TEST_CHECK(lmu_data_u32_get(mac.data) == 0x02030405);
    TEST_CHECK(lmu_data_u32_get(&mac.data[2]) == 0x04050607);
}

TEST_LIST = {{"lmu_isxxxx", test_lmu_isxxxx},
             {"lmu_memmove", test_lmu_memmove},
             {"lmu_czstrlen", test_lmu_czstrlen},
             {"lmu_czstrnlen", test_lmu_czstrnlen},
             {"lmu_str_to_czstr", str_to_czstr_check},
             {"lmu_str_len", strlen_},
             {"lmu_fmt_u32", fmt_u32},
             {"lmu_fmt_i32", fmt_i32},
             {"lmu_parse_u32", parse_u32},
             {"lmu_parse_fmt", parse_fmt},
             {"lmu_str_cmp", str_cmp},
             {"lmu_cstr_split", cstr_split},
             {"lmu_ss_fmt", ss_fmt},
             {"lmu_parse_mac", test_lmu_parse_mac},
             {"lmu_parse_ipv4", test_lmu_parse_ipv4},
             {"lmu_parse_ipv4_prefix", test_lmu_parse_ipv4_prefix},
             {"lmu_parse_ipv6", test_lmu_parse_ipv6},
             {"lmu_ss_append_cstr", test_lmu_ss_append_cstr},
             {"lmu_rbuf_reset", test_lmu_rbuf_reset},
             {"lmu_rbuf_empty", test_lmu_rbuf_empty},
             {"lmu_rbuf_full", test_lmu_rbuf_full},
             {"lmu_rbuf_capacity", test_lmu_rbuf_capacity},
             {"lmu_rbuf_remaining", test_lmu_rbuf_remaining},
             {"lmu_rbuf_size", test_lmu_rbuf_size},
             {"lmu_rbuf_push", test_lmu_rbuf_push},
             {"lmu_rbuf_pop", test_lmu_rbuf_pop},
             {"lmu_rbuf_read_advance", test_lmu_rbuf_read_advance},
             {"lmu_rbuf_discard", test_lmu_rbuf_discard},
             {"lmu_bin_cap", test_lmu_bin_cap},
             {"lmu_bin_copy", test_lmu_bin_copy},
             {"lmu_cbin_cmp", test_lmu_cbin_cmp},
             {"lmu_data", test_lmu_data},
             {NULL, NULL}};
