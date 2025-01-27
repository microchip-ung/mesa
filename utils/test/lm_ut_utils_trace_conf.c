// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "acutest.h"
#include "../src/lm_utils_trace_conf_priv.h"

void lmu_trace_conf_basics()
{
    lmu_bin32_t data_ = {};
    lmu_bin_t   ds = {.begin = data_.data,
                      .end = data_.data + sizeof(data_.data)};

    lmu_trace_conf_init(&ds);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 0) == 0);
    TEST_CHECK(lmu_trace_conf_set(&ds, "fo", 2) == LM_RC_OK);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 3) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 7) == 0);

    TEST_CHECK(lmu_trace_conf_set(&ds, "b", 3) == LM_RC_OK);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 3) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 7) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 3) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 7) == 0);

    TEST_CHECK(lmu_trace_conf_set(&ds, "bar", 1) == LM_RC_OK);

    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 3) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "b", 7) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 3) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "fo", 7) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 0) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 2) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 3) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 4) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 5) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 6) == 0);
    TEST_CHECK(lmu_trace_conf_active(&ds, "bar", 7) == 0);

    lmu_trace_conf_init(&ds);
    TEST_CHECK(lmu_trace_conf_set(&ds, "asdf/base", 1) == LM_RC_OK);
    TEST_CHECK(lmu_trace_conf_set(&ds, "asdf/vvv", 2) == LM_RC_OK);
    TEST_DUMP("DS: ", ds.begin, ds.end - ds.begin);
    TEST_CHECK(lmu_trace_conf_set(&ds, "xyz", 4) == LM_RC_OK);

    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf", 3) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/base", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/base", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/base", 3) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/vvv", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/vvv", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/vvv", 3) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/i", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/i", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/i", 3) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/", 1) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/", 2) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "asdf/", 3) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz", 3) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz", 4) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz", 5) == 0);

    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz/jj", 3) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz/jj", 4) == 1);
    TEST_CHECK(lmu_trace_conf_active(&ds, "xyz/jj", 5) == 0);
}

void test_match_name(const char *ds, const char *m, lmu_bool_t match_expect,
                     uint32_t size_expect)
{
    lmu_bool_t match_actual;
    uint32_t   size_actual;
    size_actual = lmu_trace_conf_match_name((const uint8_t *)ds,
                                            (const uint8_t *)(ds + strlen(ds)),
                                            m, &match_actual);

    TEST_CHECK(size_actual == size_expect);
    TEST_DUMP("DS: ", ds, strlen(ds));
    TEST_MSG("%u == %u", size_actual, size_expect);
    TEST_CHECK(match_actual == match_expect);
    TEST_DUMP("DS: ", ds, strlen(ds));
    TEST_MSG("%d == %d", match_actual, match_expect);
}

void test_lmu_trace_conf_match_name()
{
    test_match_name("", "bb", 0, 0);
    test_match_name("\xff", "bb", 0, 0);

    test_match_name("asdf\xff\x01asdh\xff", "asdf", 1, 5);
    test_match_name("asdf\xff\x01asdh\xff", "asdff", 0, 5);
    test_match_name("asdf\xff\x01asdh\xff", "asd", 0, 5);
    test_match_name("asdf\xff\x01asdh\xff", "bb", 0, 5);
    test_match_name("asdf\xff", "bb", 0, 5);

    test_match_name("asdf\xff\x01asdh\xff", "asdf/asdfasdf", 1, 5);
    test_match_name("asdf\xff\x01asdh\xff", "asdff/aa", 0, 5);
    test_match_name("asdf\xff\x01asdh\xff", "asd/asdf", 0, 5);
    test_match_name("asdf\xff\x01asdh\xff", "bb/aa", 0, 5);
    test_match_name("asdf\xff", "bb\\aa", 0, 5);

    test_match_name("a\xff\x01asdh\xff", "a", 1, 2);
    test_match_name("a\xff\x01asdh\xff", "aa", 0, 2);
    test_match_name("a\xff\x01asdh\xff", "b", 0, 2);
    test_match_name("a\xff\x01asdh\xff", "bb", 0, 2);

    test_match_name("a\xff\x01asdh\xff", "a/a", 1, 2);
    test_match_name("a\xff\x01asdh\xff", "aa/a", 0, 2);
}

TEST_LIST = {{"lmu_trace_conf_basics", lmu_trace_conf_basics},
             {"test_lmu_trace_conf_match_name", test_lmu_trace_conf_match_name},
             {NULL, NULL}};
