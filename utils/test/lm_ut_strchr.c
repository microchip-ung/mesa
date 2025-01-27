//===-- Unittests for strchr ----------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// strchr_test.cpp

#include "acutest.h"
#include "lm_utils.h"

#define ASSERT_STREQ(a, b) TEST_CHECK(lmu_czstrcmp(a, b) == 0)

void lmu_czstrchr_FindsFirstCharacter()
{
    const char *src = "abcde";

    // Should return original string since 'a' is the first character.
    ASSERT_STREQ(lmu_czstrchr(src, 'a'), "abcde");
    // Source string should not change.
    ASSERT_STREQ(src, "abcde");
}

void lmu_czstrchr_FindsMiddleCharacter()
{
    const char *src = "abcde";

    // Should return characters after (and including) 'c'.
    ASSERT_STREQ(lmu_czstrchr(src, 'c'), "cde");
    // Source string should not change.
    ASSERT_STREQ(src, "abcde");
}

void lmu_czstrchr_FindsLastCharacterThatIsNotNullTerminator()
{
    const char *src = "abcde";

    // Should return 'e' and null-terminator.
    ASSERT_STREQ(lmu_czstrchr(src, 'e'), "e");
    // Source string should not change.
    ASSERT_STREQ(src, "abcde");
}

void lmu_czstrchr_FindsNullTerminator()
{
    const char *src = "abcde";

    // Should return null terminator.
    ASSERT_STREQ(lmu_czstrchr(src, '\0'), "");
    // Source string should not change.
    ASSERT_STREQ(src, "abcde");
}

void lmu_czstrchr_CharacterNotWithinStringShouldReturnNullptr()
{
    // Since 'z' is not within the string, should return nullptr.
    ASSERT_STREQ(lmu_czstrchr("123?", 'z'), NULL);
}

void lmu_czstrchr_TheSourceShouldNotChange()
{
    const char *src = "abcde";
    // When the character is found, the source string should not change.
    lmu_czstrchr(src, 'd');
    ASSERT_STREQ(src, "abcde");
    // Same case for when the character is not found.
    lmu_czstrchr(src, 'z');
    ASSERT_STREQ(src, "abcde");
    // Same case for when looking for nullptr.
    lmu_czstrchr(src, '\0');
    ASSERT_STREQ(src, "abcde");
}

void lmu_czstrchr_ShouldFindFirstOfDuplicates()
{
    // '1' is duplicated in the string, but it should find the first copy.
    ASSERT_STREQ(lmu_czstrchr("abc1def1ghi", '1'), "1def1ghi");

    const char *dups = "XXXXX";
    // Should return original string since 'X' is the first character.
    ASSERT_STREQ(lmu_czstrchr(dups, 'X'), dups);
}

void lmu_czstrchr_EmptyStringShouldOnlyMatchNullTerminator()
{
    // Null terminator should match.
    ASSERT_STREQ(lmu_czstrchr("", '\0'), "");
    // All other characters should not match.
    ASSERT_STREQ(lmu_czstrchr("", 'Z'), NULL);
    ASSERT_STREQ(lmu_czstrchr("", '3'), NULL);
    ASSERT_STREQ(lmu_czstrchr("", '*'), NULL);
}

TEST_LIST = {
    {"lmu_czstrchr_FindsFirstCharacter", lmu_czstrchr_FindsFirstCharacter},
    {"lmu_czstrchr_FindsMiddleCharacter", lmu_czstrchr_FindsMiddleCharacter},
    {"lmu_czstrchr_FindsLastCharacterThatIsNotNullTerminator",
     lmu_czstrchr_FindsLastCharacterThatIsNotNullTerminator},
    {"lmu_czstrchr_FindsNullTerminator", lmu_czstrchr_FindsNullTerminator},
    {"lmu_czstrchr_CharacterNotWithinStringShouldReturnNullptr",
     lmu_czstrchr_CharacterNotWithinStringShouldReturnNullptr},
    {"lmu_czstrchr_TheSourceShouldNotChange",
     lmu_czstrchr_TheSourceShouldNotChange},
    {"lmu_czstrchr_ShouldFindFirstOfDuplicates",
     lmu_czstrchr_ShouldFindFirstOfDuplicates},
    {"lmu_czstrchr_EmptyStringShouldOnlyMatchNullTerminator",
     lmu_czstrchr_EmptyStringShouldOnlyMatchNullTerminator},

    {NULL, NULL}};
