// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "lm_utils_trace_conf_priv.h"

#define SEPERATOR 0xffU

#define LEVEL_MAX 7

// 1 for the level, 1 for seperator and one extra to mark the last.
#define ENTRY_MAX_OVERHEAD 3U

// 1 for the level, 1 for seperator
#define ENTRY_OVERHEAD 2U

void lmu_trace_conf_init(lmu_bin_t *ds)
{
    size_t size = lmu_ptrdiff_to_size_t(ds->end, ds->begin);
    lmu_memset(ds->begin, (int)SEPERATOR, size);
}

// Internal function to check the level of the entry pointed to by 'begin'.
//
// On success, returns number of bytes to advance the pointer beyound the level
// marker (with current implementation this is 1).
//
// On failure return 0.
static uint32_t lmu_trace_conf_level(uint8_t *begin, uint8_t *end,
                                     uint8_t *level)
{
    if (begin != end && *begin != SEPERATOR) {
        *level = *begin;
        return 1;
    }

    return 0;
}

// Internal function used check if the current entry matches the 'name'.
//
// where:
// begin [IN]: is the pointer to the start of the collection
// end [IN]: end of collection
// name [IN]: Name of the channel we are looking for.
// match [out]: Indicating it the current element matches
// return: Size in bytes of current element. If '0' is returned, then the are no
// more entries.
uint32_t lmu_trace_conf_match_name(const uint8_t *begin, const uint8_t *end,
                                   const char *name, lmu_bool_t *match)
{
    const uint8_t *i = begin;
    lmu_bool_t     no_match = LMU_FALSE;

    // Continue until end of DS, or hit seperator
    while (i != end && *i != SEPERATOR) {
        if (*i != (uint8_t)*name) {
            // No-match condition, but continue iterating as we need to return
            // number of bytes to advance the pointer to get to next entry.
            no_match = LMU_TRUE;
        }

        if (*name != '\0' && *name != '/') {
            name++;
        }
        i++;
    }

    if (!no_match && (*name == '\0' || *name == '/') && *i == SEPERATOR) {
        *match = LMU_TRUE;
    } else {
        *match = LMU_FALSE;
    }

    if (i == begin) {
        // End of DS, or fist char of the DS was a SEPERATOR - this means no
        // more entries
        return 0;
    }

    if (i != end) {
        // Consume the seperator as well
        i++;
    }

    return (uint32_t)lmu_ptrdiff_to_size_t(i, begin);
}

static uint32_t lmu_trace_conf_walk(uint8_t *begin, uint8_t *end,
                                    const char *name, lmu_bool_t *match,
                                    uint8_t *level)
{
    uint32_t res_level = 0, res_match = 0;

    res_level = lmu_trace_conf_level(begin, end, level);
    if (res_level != 0U) {
        res_match =
            lmu_trace_conf_match_name(begin + res_level, end, name, match);
    } else {
        *match = LMU_FALSE;
    }

    return res_level + res_match;
}

static lmu_bool_t lmu_trace_conf_match_level_name(uint8_t **begin, uint8_t *end,
                                                  const char *name,
                                                  uint8_t     trace_level,
                                                  lmu_bool_t *active)
{
    lmu_bool_t match;
    uint8_t   *i = *begin;
    uint8_t    entry_level;
    uint32_t   res_level = 0, res_match = 0;

    // The fast path - start!
    res_level = lmu_trace_conf_level(i, end, &entry_level);

    // If we are at the end of the collection, or configured levels are larger
    // than what we are looking for - then stop searching, conclude not active.
    if (res_level == 0U) {
        *active = LMU_FALSE;
        return LMU_FALSE;
    }

    // If the configured levels are larger than what we are looking for - then
    // stop searching, conclude not active.
    if (trace_level > entry_level) {
        *active = LMU_FALSE;
        return LMU_FALSE;
    }
    // The fast path - end!

    i += res_level;
    res_match = lmu_trace_conf_match_name(i, end, name, &match);

    if (match) {
        if (trace_level <= entry_level) {
            *active = LMU_TRUE;
        } else {
            *active = LMU_FALSE;
        }

        return LMU_FALSE;
    }

    i += res_match;
    *begin = i;
    return LMU_TRUE;
}

static lm_rc_t lmu_trace_conf_add(lmu_bin_t *ds, const char *name,
                                  uint8_t level)
{
    lmu_bool_t  match;
    uint8_t    *b = ds->begin, entry_level;
    size_t      size, used, front, headroom;
    size_t      name_size = 0;
    const char *name_i = name;

    while (*name_i != '\0' && *name_i != '/') {
        name_i++;
        name_size++;
    }

    // TODO, check validity of name and level

    // Start by making sure that it is not already present, and find the end of
    // the collection (needed to calculate if we have room for more).
    size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    while (size > 0U) {
        if (match) {
            return LM_RC_ERROR;
        }

        b += size;
        size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    }

    headroom = lmu_ptrdiff_to_size_t(ds->end, b);
    used = lmu_ptrdiff_to_size_t(b, ds->begin);
    b = ds->begin;

    if (name_size + ENTRY_MAX_OVERHEAD > headroom) {
        return LM_RC_ERROR;
    }

    // Find where to insert
    size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    while (size > 0U) {
        if (level > entry_level) {
            // Break before increment b! We must insert before this entry.
            break;
        }

        b += size;
        size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    }

    front = lmu_ptrdiff_to_size_t(b, ds->begin);
    lmu_memmove(b + name_size + ENTRY_OVERHEAD, b, used - front);
    // todo, assert
    *b = level;
    b++;

    lmu_memcpy(b, name, name_size);
    // todo, assert
    b += name_size;
    *b = SEPERATOR;

    return LM_RC_OK;
}

lm_rc_t lmu_trace_conf_set(lmu_bin_t *ds, const char *name, uint8_t level)
{
    lmu_bool_t match;
    uint8_t   *b = ds->begin;
    uint8_t    entry_level;
    uint32_t   size;

    size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    while (size > 0U) {
        if (match) {
            break;
        }

        b += size;
        size = lmu_trace_conf_walk(b, ds->end, name, &match, &entry_level);
    }

    if (match) {
        // Do a memmove to delete the current entry
        lmu_memmove(b, b + size,
                    (size_t)(lmu_ptrdiff_to_size_t(ds->end, b) - size));
        // todo, assert

        // Fill the potential undefined bytes in the end
        lmu_memset(ds->end - size, (int)SEPERATOR, size);
        // todo, assert
    }

    // Re-add with updated level to get it correctly inserted
    return lmu_trace_conf_add(ds, name, level);
}

lmu_bool_t lmu_trace_conf_active(lmu_bin_t *ds, const char *name, uint8_t level)
{
    lmu_bool_t active;
    uint8_t   *b = ds->begin;

    while (lmu_trace_conf_match_level_name(&b, ds->end, name, level, &active)) {
        // empty on purpose
    }

    return active;
}
