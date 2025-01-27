//===-- Unittests for strcspn ---------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// strcspn_test.cpp

#include "acutest.h"
#include "lm_utils.h"

void lmu_czstrcspn_ComplementarySpanShouldNotGoPastNullTerminator()
{
    const char src[5] = {'a', 'b', '\0', 'c', 'd'};
    TEST_CHECK(lmu_czstrcspn(src, "b") == (size_t)1);
    TEST_CHECK(lmu_czstrcspn(src, "d") == (size_t)2);

    // Same goes for the segment to be searched for.
    const char segment[5] = {'1', '2', '\0', '3', '4'};
    TEST_CHECK(lmu_czstrcspn("123", segment) == (size_t)0);
}

void lmu_czstrcspn_ComplementarySpanForEachIndividualCharacter()
{
    const char *src = "12345";
    // The complementary span size should increment accordingly.
    TEST_CHECK(lmu_czstrcspn(src, "1") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn(src, "2") == (size_t)1);
    TEST_CHECK(lmu_czstrcspn(src, "3") == (size_t)2);
    TEST_CHECK(lmu_czstrcspn(src, "4") == (size_t)3);
    TEST_CHECK(lmu_czstrcspn(src, "5") == (size_t)4);
}

void lmu_czstrcspn_ComplementarySpanIsStringLengthIfNoCharacterFound()
{
    // Null terminator.
    TEST_CHECK(lmu_czstrcspn("", "") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn("", "_") == (size_t)0);
    // Single character.
    TEST_CHECK(lmu_czstrcspn("a", "b") == (size_t)1);
    // Multiple characters.
    TEST_CHECK(lmu_czstrcspn("abc", "1") == (size_t)3);
}

void lmu_czstrcspn_DuplicatedCharactersNotPartOfComplementarySpan()
{
    // Complementary span should be zero in all these cases.
    TEST_CHECK(lmu_czstrcspn("a", "aa") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn("aa", "a") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn("aaa", "aa") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn("aaaa", "aa") == (size_t)0);
    TEST_CHECK(lmu_czstrcspn("aaaa", "baa") == (size_t)0);
}

TEST_LIST = {{"lmu_czstrcspn_ComplementarySpanShouldNotGoPastNullTerminator",
              lmu_czstrcspn_ComplementarySpanShouldNotGoPastNullTerminator},
             {"lmu_czstrcspn_ComplementarySpanForEachIndividualCharacter",
              lmu_czstrcspn_ComplementarySpanForEachIndividualCharacter},
             {"lmu_czstrcspn_ComplementarySpanIsStringLengthIfNoCharacterFound",
              lmu_czstrcspn_ComplementarySpanIsStringLengthIfNoCharacterFound},
             {"lmu_czstrcspn_DuplicatedCharactersNotPartOfComplementarySpan",
              lmu_czstrcspn_DuplicatedCharactersNotPartOfComplementarySpan},
             {NULL, NULL}};
