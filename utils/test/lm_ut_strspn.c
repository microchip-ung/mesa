//===-- Unittests for strspn ----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// strspn_test.cpp

#include "acutest.h"
#include "lm_utils.h"

void LlvmLibcStrSpnTest_EmptyStringShouldReturnZeroLengthSpan()
{
    // The search should not include the null terminator.
    TEST_CHECK(lmu_czstrspn("", "") == (size_t)0);
    TEST_CHECK(lmu_czstrspn("_", "") == (size_t)0);
    TEST_CHECK(lmu_czstrspn("", "_") == (size_t)0);
}

void LlvmLibcStrSpnTest_ShouldNotSpanAnythingAfterNullTerminator()
{
    const char src[4] = {'a', 'b', '\0', 'c'};
    TEST_CHECK(lmu_czstrspn(src, "ab") == (size_t)2);
    TEST_CHECK(lmu_czstrspn(src, "c") == (size_t)0);

    // Same goes for the segment to be searched for.
    const char segment[4] = {'1', '2', '\0', '3'};
    TEST_CHECK(lmu_czstrspn("123", segment) == (size_t)2);
}

void LlvmLibcStrSpnTest_SpanEachIndividualCharacter()
{
    const char *src = "12345";
    TEST_CHECK(lmu_czstrspn(src, "1") == (size_t)1);
    // Since '1' is not within the segment, the span
    // size should remain zero.
    TEST_CHECK(lmu_czstrspn(src, "2") == (size_t)0);
    TEST_CHECK(lmu_czstrspn(src, "3") == (size_t)0);
    TEST_CHECK(lmu_czstrspn(src, "4") == (size_t)0);
    TEST_CHECK(lmu_czstrspn(src, "5") == (size_t)0);
}

void LlvmLibcStrSpnTest_UnmatchedCharacterShouldNotBeCountedInSpan()
{
    TEST_CHECK(lmu_czstrspn("a", "b") == (size_t)0);
    TEST_CHECK(lmu_czstrspn("abcdef", "1") == (size_t)0);
    TEST_CHECK(lmu_czstrspn("123", "4") == (size_t)0);
}

void LlvmLibcStrSpnTest_SequentialCharactersShouldSpan()
{
    const char *src = "abcde";
    TEST_CHECK(lmu_czstrspn(src, "a") == (size_t)1);
    TEST_CHECK(lmu_czstrspn(src, "ab") == (size_t)2);
    TEST_CHECK(lmu_czstrspn(src, "abc") == (size_t)3);
    TEST_CHECK(lmu_czstrspn(src, "abcd") == (size_t)4);
    TEST_CHECK(lmu_czstrspn(src, "abcde") == (size_t)5);
    // Same thing for when the roles are reversed.
    TEST_CHECK(lmu_czstrspn("abcde", src) == (size_t)5);
    TEST_CHECK(lmu_czstrspn("abcd", src) == (size_t)4);
    TEST_CHECK(lmu_czstrspn("abc", src) == (size_t)3);
    TEST_CHECK(lmu_czstrspn("ab", src) == (size_t)2);
    TEST_CHECK(lmu_czstrspn("a", src) == (size_t)1);
}

void LlvmLibcStrSpnTest_NonSequentialCharactersShouldNotSpan()
{
    const char *src = "123456789";
    TEST_CHECK(lmu_czstrspn(src, "_1_abc_2_def_3_") == (size_t)3);
    // Only spans 4 since '5' is not within the span.
    TEST_CHECK(lmu_czstrspn(src, "67__34abc12") == (size_t)4);
}

void LlvmLibcStrSpnTest_ReverseCharacters()
{
    // Since these are still sequential, this should span.
    TEST_CHECK(lmu_czstrspn("12345", "54321") == (size_t)5);
    // Does not span any since '1' is not within the span.
    TEST_CHECK(lmu_czstrspn("12345", "432") == (size_t)0);
    // Only spans 1 since '2' is not within the span.
    TEST_CHECK(lmu_czstrspn("12345", "51") == (size_t)1);
}

void LlvmLibcStrSpnTest_DuplicatedCharactersToBeSearchedForShouldStillMatch()
{
    // Only a single character, so only spans 1.
    TEST_CHECK(lmu_czstrspn("a", "aa") == (size_t)1);
    // This should count once for each 'a' in the source string.
    TEST_CHECK(lmu_czstrspn("aa", "aa") == (size_t)2);
    TEST_CHECK(lmu_czstrspn("aaa", "aa") == (size_t)3);
    TEST_CHECK(lmu_czstrspn("aaaa", "aa") == (size_t)4);
}

TEST_LIST = {
    {"LlvmLibcStrSpnTest_EmptyStringShouldReturnZeroLengthSpan",
     LlvmLibcStrSpnTest_EmptyStringShouldReturnZeroLengthSpan},
    {"LlvmLibcStrSpnTest_ShouldNotSpanAnythingAfterNullTerminator",
     LlvmLibcStrSpnTest_ShouldNotSpanAnythingAfterNullTerminator},
    {"LlvmLibcStrSpnTest_SpanEachIndividualCharacter",
     LlvmLibcStrSpnTest_SpanEachIndividualCharacter},
    {"LlvmLibcStrSpnTest_UnmatchedCharacterShouldNotBeCountedInSpan",
     LlvmLibcStrSpnTest_UnmatchedCharacterShouldNotBeCountedInSpan},
    {"LlvmLibcStrSpnTest_SequentialCharactersShouldSpan",
     LlvmLibcStrSpnTest_SequentialCharactersShouldSpan},
    {"LlvmLibcStrSpnTest_NonSequentialCharactersShouldNotSpan",
     LlvmLibcStrSpnTest_NonSequentialCharactersShouldNotSpan},
    {"LlvmLibcStrSpnTest_ReverseCharacters",
     LlvmLibcStrSpnTest_ReverseCharacters},
    {"LlvmLibcStrSpnTest_DuplicatedCharactersToBeSearchedForShouldStillMatch",
     LlvmLibcStrSpnTest_DuplicatedCharactersToBeSearchedForShouldStillMatch},
    {NULL, NULL}};
