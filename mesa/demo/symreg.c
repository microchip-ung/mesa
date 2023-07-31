// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <ctype.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "symreg.h"

#define _BF_SIZE(n)      ((n+7)/8)
#define _BF_GET(a, n)    ((a[(n)/8] & (1<<((n)%8))) ? 1 : 0)
#define _BF_SET(a, n, v)              \
do {                                  \
    if (v) {                          \
        a[(n)/8] |= (1U<<((n)%8));    \
    } else {                          \
        a[(n)/8] &= ~(1U<<((n)%8));   \
    }                                 \
} while (0)

#define _BF_CLR(a, n)    (memset(a, 0, _BF_SIZE(n)))

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static mscc_appl_trace_module_t trace_module = {
    .name = "symreg"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

/******************************************************************************/
//
// Module Private Data
//
/******************************************************************************/

#define SYMREG_REPL_LEN_MAX 32 /* Allocate 32 chars for the user to specify a replication list */
#define SYMREG_REPL_CNT_MAX 8192
#define SYMREG_NAME_LEN_MAX 100

/**
 * SymReg module error codes (mesa_rc)
 */
enum {
    SYMREG_RC_PARAM = -100,
    SYMREG_RC_OUT_OF_MEMORY,
    SYMREG_RC_PAT_TOO_MANY_COLONS,
    SYMREG_RC_PAT_COMPONENT_TOO_LONG,
    SYMREG_RC_PAT_AT_LEAST_ONE_COMPONENT_MUST_BE_SPECIFIED,
    SYMREG_RC_PAT_TWO_LEFT_BRACKETS_SEEN,
    SYMREG_RC_PAT_RIGHT_BRACKET_SEEN_BEFORE_LEFT_BRACKET,
    SYMREG_RC_PAT_EXTRA_CHARACTERS_AFTER_END_BRACKET,
    SYMREG_RC_PAT_MISSING_RIGHT_BRACKET,
    SYMREG_RC_PAT_INVALID_REPLICATION_LIST,
    SYMREG_RC_NO_SUCH_REPL_TGT,
    SYMREG_RC_NO_SUCH_REPL_GRP,
    SYMREG_RC_NO_SUCH_REPL_REG,
    SYMREG_RC_NO_SUCH_TGT,
    SYMREG_RC_NO_SUCH_GRP,
    SYMREG_RC_NO_SUCH_REG,
    SYMREG_RC_NO_MORE_REGS,
}; // Leave it anonymous

typedef enum {
    SYMREG_COMPONENTS_TGT,
    SYMREG_COMPONENTS_GRP,
    SYMREG_COMPONENTS_REG,
    SYMREG_COMPONENTS_LAST
} symreg_components_t;

typedef struct {
    mesa_bool_t wildcards;
    mesa_bool_t all_repls;
    uint8_t repls[_BF_SIZE(SYMREG_REPL_CNT_MAX)];
    char pattern[SYMREG_NAME_LEN_MAX + SYMREG_REPL_LEN_MAX + 1];

    // State variables that remember where we got to.
    int  cur_idx;
    int  cur_repl;
    uint32_t  match_cnt;
    uint8_t   matched_repls[_BF_SIZE(SYMREG_REPL_CNT_MAX)];
    mesa_bool_t matched_at_least_one_name;
    char match_name[SYMREG_NAME_LEN_MAX + SYMREG_REPL_LEN_MAX + 1];
    uint32_t  match_width;
    uint32_t  match_addr;

    union {
        const mesa_symreg_target_t *t;
        const mesa_symreg_reggrp_t *g;
        const mesa_symreg_reg_t    *r;
    } u;

    // For debug
    const char *self_name;
} symreg_state_t;

typedef struct {
    symreg_state_t state[SYMREG_COMPONENTS_LAST];
} symreg_inst_t;

static mesa_symreg_data_t SYMREG_DATA;

/******************************************************************************/
//
// Module Helper functions
//
/******************************************************************************/

/* Convert text to list or bit field */
mesa_rc txt2list_bf(char *buf, mesa_bool_t *list, uint32_t min, uint32_t max,
                    mesa_bool_t def, mesa_bool_t bf)
{
    uint32_t   i, start = 0, n;
    char  *p, *end;
    mesa_bool_t  error, range = 0, comma = 0;

    /* Clear list by default */
    if (bf) {
        _BF_CLR(list, max + 1);
    } else {
        for (i = min; i <= max; i++) {
            list[i] = 0;
        }
    }

    p = buf;
    error = (p == NULL);
    while (p != NULL && *p != '\0') {
        /* Read integer */
        n = strtoul(p, &end, 0);
        if (end == p) {
            error = 1;
            break;
        }
        p = end;

        /* Check legal range */
        if (n < min || n > max) {
            error = 1;
            break;
        }

        if (range) {
            /* End of range has been read */
            if (n < start) {
                error = 1;
                break;
            }
            for (i = start ; i <= n; i++) {
                if (bf) {
                    _BF_SET(list, i, 1);
                } else {
                    list[i] = 1;
                }
            }
            range = 0;
        } else if (*p == '-') {
            /* Start of range has been read */
            start = n;
            range = 1;
            p++;
        } else {
            /* Single value has been read */
            if (bf) {
                _BF_SET(list, n, 1);
            } else {
                list[n] = 1;
            }
        }

        comma = 0;
        if (!range && *p == ',') {
            comma = 1;
            p++;
        }
    }

    /* Check for trailing comma/dash */
    if (comma || range) {
        error = 1;
    }

    /* Restore defaults if error */
    if (error) {
        if (bf) {
            memset(list, def ? 0xff : 0x00, _BF_SIZE(max + 1));
        } else {
            for (i = min; i <= max; i++) {
                list[i] = def;
            }
        }
    }
    return (error ? MESA_RC_ERROR : MESA_RC_OK);
}

/* Convert list to text
 * The resulting buf will contain numbers in range [min + 1; max + 1]
 * or [min; max] if #one_based is FALSE.
 * The case where #one_based == TRUE is a legacy case, that actually
 * never should have been implemented, or implemented differently.
 * It should have been using iport2uport(i) and iport2uport(i - 1)
 */
static char *list2txt(mesa_bool_t *list, int min, int max,
                      char *buf, mesa_bool_t bf, mesa_bool_t one_based)
{
    int  i, count = 0;
    mesa_bool_t member, first = TRUE;
    char *p;

    p = buf;
    *p = '\0';

    for (i = min; i <= max; i++) {
        member = bf ? _BF_GET(list, i) : list[i];
        if ((member && (count == 0 || i == max)) || (!member && count > 1)) {
            p += sprintf(p, "%s%d", first ? "" : count > (member ? 1 : 2) ? "-" : ",", one_based ? (member ? i + 1 : i) : (member ? i : i - 1));
            first = FALSE;
        }

        if (member) {
            count++;
        } else {
            count = 0;
        }
    }

    return buf;
}

/******************************************************************************/
//
// Module Private functions
//
/******************************************************************************/

/******************************************************************************/
// SYMREG_component_to_name()
/******************************************************************************/
static const char *SYMREG_component_to_name(int component)
{
    switch (component) {
    case SYMREG_COMPONENTS_TGT:
        return "Tgt";

    case SYMREG_COMPONENTS_GRP:
        return "Grp";

    case SYMREG_COMPONENTS_REG:
        return "Reg";

    default:
        return "Unknown";
    }
}

/******************************************************************************/
// SYMREG_print_match_pattern()
/******************************************************************************/
static void SYMREG_print_match_pattern(int component, symreg_state_t *s)
{
    char buf[SYMREG_REPL_LEN_MAX + 1]; // Output of mgmt_bf2txt() cannot exceed input to mgmt_txt2bf() in size.

    T_D("%s:", SYMREG_component_to_name(component));
    T_D("Wildcards: %s", s->wildcards ? "Yes" : "No");
    T_D("Replications: %s", s->all_repls ? "All" : list2txt(s->repls, 0, SYMREG_REPL_CNT_MAX - 1, buf, 1, 0));
    T_D("Pattern: %s\n", s->pattern);
}

/****************************************************************************/
// SYMREG_wildcmp()
// Searches for #w (which may contain wildcards ('*' and '?')) in #s
// and returns TRUE if we have a match, FALSE otherwise.
/****************************************************************************/
static mesa_bool_t SYMREG_wildcmp(const char *w, const char *s)
{
    const char *cp = NULL, *mp = NULL;
    const char *wild = w, *string = s;

    while (*string && *wild != '*') {
        if (*wild != *string && *wild != '?') {
            return FALSE;
        }

        wild++;
        string++;
    }

    while (*string) {
        if (*wild == '*') {
            if (!*++wild) {
                return TRUE;
            }

            mp = wild;
            cp = string + 1;
        } else if ((*wild == *string) || (*wild == '?')) {
            wild++;
            string++;
        } else {
            if (cp == NULL) {
                T_E("Error when matching wild = %s against string = %s", w, s);
                return FALSE;
            }

            wild = mp;
            string = cp++;
        }
    }

    if (wild == NULL) {
        T_E("Error when matching wild = %s against string = %s", w, s);
        return FALSE;
    }

    while (*wild == '*') {
        wild++;
    }

    return !*wild;
}

/****************************************************************************/
// SYMREG_match_name()
/****************************************************************************/
static mesa_bool_t SYMREG_match_name(symreg_state_t *s, const char *name)
{
    mesa_bool_t result;
    if (s->wildcards) {
        result = SYMREG_wildcmp(s->pattern, name);
    } else {
        // User has requested an exact pattern
        result = strcmp(s->pattern, name) == 0;
    }

    T_N("%s: Considering %s: %s", s->self_name, name, result ? "Yes" : "No");
    return result;
}

/****************************************************************************/
// SYMREG_match_repl()
/****************************************************************************/
static inline mesa_bool_t SYMREG_match_repl(symreg_state_t *s, uint32_t repl)
{
    if (s->all_repls) {
        return TRUE;
    } else {
        return _BF_GET(s->repls, repl);
    }
}

/****************************************************************************/
// SYMREG_reg_next()
/****************************************************************************/
static mesa_bool_t SYMREG_reg_next(symreg_state_t *r, mesa_symreg_reg_t const *regs)
{
    if (r->cur_idx < 0 || r->cur_repl >= (int)regs[r->cur_idx].repl_cnt - 1) {
        // Either we're not started, or we've matched the last
        // replication in the previous iteration. Find next
        // matching register by name.
        r->cur_repl = -1;
        r->cur_idx++;
    }

    while (regs[r->cur_idx].name != NULL) {
        uint32_t repl;

        r->u.r = &regs[r->cur_idx];

        if (SYMREG_match_name(r, r->u.r->name)) {
            // Name match. Check to see if there is a replication fit.
            r->matched_at_least_one_name = TRUE;

            for (repl = r->cur_repl + 1; repl < r->u.r->repl_cnt; repl++) {
                if (SYMREG_match_repl(r, repl)) {
                    r->cur_repl = repl;
                    r->match_cnt++;
                    r->match_addr = 4 * (repl * r->u.r->repl_width + r->u.r->addr);

                    if (r->u.r->repl_cnt == 1) {
                        strcpy(r->match_name, r->u.r->name);
                    } else {
                        sprintf(r->match_name, "%s[%u]", r->u.r->name, r->cur_repl);
                    }

                    r->match_width = strlen(r->match_name);
                    return TRUE;
                }
            }
        }

        // No replication match
        r->cur_repl = -1;
        r->cur_idx++;
    }

    return FALSE;
}

/****************************************************************************/
// SYMREG_grp_next()
/****************************************************************************/
static mesa_bool_t SYMREG_grp_next(symreg_state_t *g, mesa_symreg_reggrp_t const *reggrps)
{
    if (g->cur_idx < 0 || g->cur_repl >= (int)reggrps[g->cur_idx].repl_cnt - 1) {
        // Either we're not started, or we've matched the last
        // replication in the previous iteration. Find next
        // matching group by name.
        g->cur_repl = -1;
        g->cur_idx++;
    }

    while (reggrps[g->cur_idx].name != NULL) {
        uint32_t repl;

        g->u.g = &reggrps[g->cur_idx];

        if (SYMREG_match_name(g, g->u.g->name)) {
            // Name match. Check to see if there is a replication fit.
            g->matched_at_least_one_name = TRUE;

            for (repl = g->cur_repl + 1; repl < g->u.g->repl_cnt; repl++) {
                if (SYMREG_match_repl(g, repl)) {
                    g->cur_repl = repl;
                    g->match_cnt++;
                    g->match_addr = 4 * (g->u.g->base_addr + repl * g->u.g->repl_width);

                    if (g->u.g->repl_cnt == 1) {
                        strcpy(g->match_name, g->u.g->name);
                    } else {
                        sprintf(g->match_name, "%s[%u]", g->u.g->name, g->cur_repl);
                    }

                    g->match_width = strlen(g->match_name);
                    return TRUE;
                }
            }
        }

        // No replication match
        g->cur_repl = -1;
        g->cur_idx++;
    }

    return FALSE;
}

/****************************************************************************/
// SYMREG_tgt_next()
/****************************************************************************/
static mesa_bool_t SYMREG_tgt_next(symreg_state_t *t)
{
    // Each target only has one replication.
    t->cur_idx++;

    while (t->cur_idx < SYMREG_DATA.targets_cnt) {
        t->u.t = &SYMREG_DATA.targets[t->cur_idx];

        if (SYMREG_match_name(t, t->u.t->name)) {
            // Target repolications are special in that a replication number
            // of -1 indicates that it's not replicated. All replications
            // are explicit, because targets may lie on different base
            // addresses, which are not evenly distanced.
            // We allow targets with no replications to be indexed by
            // replication 0:
            uint32_t repl = t->u.t->repl_number < 0 ? 0 : t->u.t->repl_number;

            t->matched_at_least_one_name = TRUE;

            if (SYMREG_match_repl(t, repl)) {
                t->cur_repl = repl; // Zero-based (not -1)
                t->match_cnt++;
                t->match_addr = t->u.t->base_addr;

                if (t->u.t->repl_number < 0) {
                    // Target not replicated
                    strcpy(t->match_name, t->u.t->name);
                } else {
                    sprintf(t->match_name, "%s[%u]", t->u.t->name, t->cur_repl);
                }

                t->match_width = strlen(t->match_name);
                return TRUE;
            }
        }

        t->cur_idx++;
    }

    return FALSE;
}

/****************************************************************************/
// SYMREG_state_clear()
/****************************************************************************/
static void SYMREG_state_clear(symreg_state_t *s, mesa_bool_t all)
{
    s->cur_idx  = -1;
    s->cur_repl = -1;

    if (all) {
        s->match_cnt                 = 0;
        s->matched_at_least_one_name = FALSE;
        memset(s->matched_repls, 0, sizeof(s->matched_repls));
    }
}

/****************************************************************************/
// SYMREG_all_repls_present()
/****************************************************************************/
static mesa_bool_t SYMREG_all_repls_present(uint8_t *requested_repls, uint8_t *matched_repls)
{
    uint32_t repl;

    // When the user has requested a particular set of replications
    // to match, all the requested replications must be present.
    for (repl = 0; repl < SYMREG_REPL_CNT_MAX; repl++) {
        if (_BF_GET(requested_repls, repl) && !_BF_GET(matched_repls, repl)) {
            return FALSE;
        }
    }

    return TRUE;
}

/****************************************************************************/
// SYMREG_check_pattern()
/****************************************************************************/
static mesa_rc SYMREG_check_pattern(symreg_inst_t *inst, uint32_t *max_width, uint32_t *reg_cnt)
{
    symreg_state_t *t = &inst->state[SYMREG_COMPONENTS_TGT];
    symreg_state_t *g = &inst->state[SYMREG_COMPONENTS_GRP];
    symreg_state_t *r = &inst->state[SYMREG_COMPONENTS_REG];
    int            i;

    for (i = 0; i < SYMREG_COMPONENTS_LAST; i++) {
        SYMREG_state_clear(&inst->state[i], TRUE);
    }

    *max_width = 0;

    while (SYMREG_tgt_next(t)) {
        SYMREG_state_clear(g, FALSE);

        while (SYMREG_grp_next(g, t->u.t->reggrps)) {
            SYMREG_state_clear(r, FALSE);

            while (SYMREG_reg_next(r, g->u.g->regs)) {
                uint32_t width = t->match_width + g->match_width + r->match_width + 2 /* Colons */;

                if (width > *max_width) {
                    *max_width = width;
                }

                // Keep track of the replications that matched.
                _BF_SET(t->matched_repls, t->cur_repl, 1);
                _BF_SET(g->matched_repls, g->cur_repl, 1);
                _BF_SET(r->matched_repls, r->cur_repl, 1);

                T_D("%s:%s:%s", t->match_name, g->match_name, r->match_name);
            }
        }
    }

    *reg_cnt = r->match_cnt;

    T_D("Reg-count = %u", *reg_cnt);
    T_D("Max. width = %u", *max_width);

    // Final checks so that we can return the correct error code.
    // Discern between a name not found and a replication not found.
    if (!t->matched_at_least_one_name) {
        return SYMREG_RC_NO_SUCH_TGT;
    }

    if (!g->matched_at_least_one_name) {
        return SYMREG_RC_NO_SUCH_GRP;
    }

    if (!r->matched_at_least_one_name) {
        return SYMREG_RC_NO_SUCH_REG;
    }

    if (!t->all_repls && !SYMREG_all_repls_present(t->repls, t->matched_repls)) {
        return SYMREG_RC_NO_SUCH_REPL_TGT;
    }

    if (!g->all_repls && !SYMREG_all_repls_present(g->repls, g->matched_repls)) {
        return SYMREG_RC_NO_SUCH_REPL_GRP;
    }

    if (!r->all_repls && !SYMREG_all_repls_present(r->repls, r->matched_repls)) {
        return SYMREG_RC_NO_SUCH_REPL_REG;
    }

    return MESA_RC_OK;
}

/******************************************************************************/
// symreg_error_txt()
/******************************************************************************/
static const char *symreg_error_txt(mesa_rc rc)
{
    switch (rc) {
    case SYMREG_RC_PARAM:
        return "Invalid parameter";

    case SYMREG_RC_OUT_OF_MEMORY:
        return "Out of memory";

    case SYMREG_RC_PAT_TOO_MANY_COLONS:
        return "Syntax error: Too many colons";

    case SYMREG_RC_PAT_COMPONENT_TOO_LONG:
        return "Syntax error: Sub-component too long";

    case SYMREG_RC_PAT_AT_LEAST_ONE_COMPONENT_MUST_BE_SPECIFIED:
        return "Syntax error: At least one target, one register group, or one register must be specified. You don't want to see all registers in the chip";

    case SYMREG_RC_PAT_TWO_LEFT_BRACKETS_SEEN:
        return "Syntax error: Two left-brackets seen in one sub-component";

    case SYMREG_RC_PAT_RIGHT_BRACKET_SEEN_BEFORE_LEFT_BRACKET:
        return "Syntax error: Right-bracket seen before left-bracket in a sub-component";

    case SYMREG_RC_PAT_EXTRA_CHARACTERS_AFTER_END_BRACKET:
        return "Syntax error: Extra characters after end-bracket in a sub-component";

    case SYMREG_RC_PAT_MISSING_RIGHT_BRACKET:
        return "Syntax error: Missing right-bracket in a sub-component";

    case SYMREG_RC_PAT_INVALID_REPLICATION_LIST:
        return "Syntax error: Invalid replication list within brackets of a sub-component";

    case SYMREG_RC_NO_SUCH_REPL_TGT:
        return "No such target replication found";

    case SYMREG_RC_NO_SUCH_REPL_GRP:
        return "No such register group replication found";

    case SYMREG_RC_NO_SUCH_REPL_REG:
        return "No such register replication found";

    case SYMREG_RC_NO_SUCH_TGT:
        return "No such target. Try using wildcards";

    case SYMREG_RC_NO_SUCH_GRP:
        return "No such register group. Try using wildcards";

    case SYMREG_RC_NO_SUCH_REG:
        return "No such register. Try using wildcards";

    case SYMREG_RC_NO_MORE_REGS:
        return "No more registers (this is not an error, so please correct use of this return code)";

    default:
        return "Unknown SymReg module error";
    }
}

/******************************************************************************/
// symreg_query_init()
/******************************************************************************/
static mesa_rc symreg_query_init(void **handle, char *pattern,
                                 uint32_t *max_width, uint32_t *reg_cnt)
{
    symreg_inst_t *inst;
    int           i;
    char          *str1 = pattern, *str2;
    size_t        cnt;
    mesa_bool_t          at_least_one_component_found = FALSE;
    mesa_rc       rc = MESA_RC_OK;

    if (handle == NULL || pattern == NULL) {
        return SYMREG_RC_PARAM;
    }

    *handle = NULL;

    if ((inst = (symreg_inst_t *)malloc(sizeof(symreg_inst_t))) == NULL) {
        return SYMREG_RC_OUT_OF_MEMORY;
    }

    memset(inst, 0, sizeof(*inst));

    // For debug:
    inst->state[SYMREG_COMPONENTS_TGT].self_name = "Tgt";
    inst->state[SYMREG_COMPONENTS_GRP].self_name = "Grp";
    inst->state[SYMREG_COMPONENTS_REG].self_name = "Reg";

    // Time to parse syntax
    for (i = 0; i < SYMREG_COMPONENTS_LAST; i++) {
        if (str1 == NULL) {
            break;
        }

        str2 = strstr(str1, ":");
        if (str2) {
            // Colon found
            if (i == SYMREG_COMPONENTS_REG) {
                rc = SYMREG_RC_PAT_TOO_MANY_COLONS;
                goto do_exit;
            }

            cnt = str2 - str1;
        } else {
            // Colon not found.
            cnt = strlen(str1);
        }

        if (cnt + 1 > sizeof(inst->state[i].pattern)) {
            rc = SYMREG_RC_PAT_COMPONENT_TOO_LONG;
            goto do_exit;
        }

        if (cnt > 0) {
            strncpy(inst->state[i].pattern, str1,
                    SYMREG_NAME_LEN_MAX + SYMREG_REPL_LEN_MAX + 1);
            // Terminate in case a colon was found in str1.
            inst->state[i].pattern[cnt] = '\0';
            at_least_one_component_found = TRUE;
        }

        if (str2 && str2[0] == ':') {
            str1 = str2 + 1;
        } else {
            str1 = NULL;
        }
    }

    if (!at_least_one_component_found) {
        rc = SYMREG_RC_PAT_AT_LEAST_ONE_COMPONENT_MUST_BE_SPECIFIED;
        goto do_exit;
    }

    // Loop once more and find replications and whether it contains wildcards
    for (i = 0; i < SYMREG_COMPONENTS_LAST; i++) {
        char *bracket_start = NULL;
        char *bracket_end   = NULL;
        int  j;

        str1 = inst->state[i].pattern;
        cnt = strlen(str1);
        for (j = 0; j < (int)cnt; j++) {
            *str1 = toupper(*str1);

            if (*str1 == '?' || *str1 == '*') {
                inst->state[i].wildcards = TRUE;
            }

            if (*str1 == '[') {
                if (bracket_start != NULL) {
                    rc = SYMREG_RC_PAT_TWO_LEFT_BRACKETS_SEEN;
                    goto do_exit;
                }

                bracket_start = str1;
            } else if (bracket_end == NULL && *str1 == ']') {
                if (bracket_start == NULL) {
                    rc = SYMREG_RC_PAT_RIGHT_BRACKET_SEEN_BEFORE_LEFT_BRACKET;
                    goto do_exit;
                }

                bracket_end = str1;
            } else if (bracket_end != NULL) {
                rc = SYMREG_RC_PAT_EXTRA_CHARACTERS_AFTER_END_BRACKET;
                goto do_exit;
            }

            str1++;
        }

        if (bracket_start && !bracket_end) {
            rc = SYMREG_RC_PAT_MISSING_RIGHT_BRACKET;
            goto do_exit;
        } else if (bracket_start == NULL || bracket_end == NULL || bracket_end == bracket_start + 1) {
            // If no brackets are found, or an empty list is given (e.g. dev1g[<nothing_here>]:xxx:xxx), show all replications.
            inst->state[i].all_repls = TRUE;
        } else {
            inst->state[i].all_repls = FALSE;

            // Parse the list, but first terminate it in both ends.
            *bracket_start = *bracket_end = '\0';
            if (txt2list_bf(bracket_start + 1, inst->state[i].repls, 0, SYMREG_REPL_CNT_MAX - 1, 0, 1) != MESA_RC_OK) {
                rc = SYMREG_RC_PAT_INVALID_REPLICATION_LIST;
                goto do_exit;
            }
        }

        if (inst->state[i].pattern[0] == '\0') {
            // Wildcard it if empty
            strcpy(inst->state[i].pattern, "*");
            inst->state[i].wildcards = TRUE;
        }
    }

    for (i = 0; i < SYMREG_COMPONENTS_LAST; i++) {
        SYMREG_print_match_pattern(i, &inst->state[i]);
    }

    // Check the pattern against the actual registers in the chip.
    rc = SYMREG_check_pattern(inst, max_width, reg_cnt);

do_exit:
    if (rc == MESA_RC_OK) {
        *handle = inst;
    } else {
        free(inst);
    }

    return rc;
}

/******************************************************************************/
// symreg_query_uninit()
/******************************************************************************/
static mesa_rc symreg_query_uninit(void *handle)
{
    if (handle == NULL) {
        return SYMREG_RC_PARAM;
    }

    free(handle);
    return MESA_RC_OK;
}

/****************************************************************************/
// symreg_query_next()
/****************************************************************************/
static mesa_rc symreg_query_next(void *handle, char *const name, uint32_t *addr,
                                 uint32_t *offset, mesa_bool_t next)
{
    symreg_inst_t  *inst  = (symreg_inst_t *)handle;
    symreg_state_t *t     = &inst->state[SYMREG_COMPONENTS_TGT];
    symreg_state_t *g     = &inst->state[SYMREG_COMPONENTS_GRP];
    symreg_state_t *r     = &inst->state[SYMREG_COMPONENTS_REG];
    int            i;

    if (handle == NULL || name == NULL || addr == NULL || offset == NULL) {
        return SYMREG_RC_PARAM;
    }

    if (!next) {
        for (i = 0; i < SYMREG_COMPONENTS_LAST; i++) {
            SYMREG_state_clear(&inst->state[i], TRUE);
        }
    }

    while (next || SYMREG_tgt_next(t)) {
        if (!next) {
            SYMREG_state_clear(g, FALSE);
        }

        while (next || SYMREG_grp_next(g, t->u.t->reggrps)) {
            if (!next) {
                SYMREG_state_clear(r, FALSE);
            }

            next = FALSE;

            while (SYMREG_reg_next(r, g->u.g->regs)) {
                sprintf(name, "%s:%s:%s", t->match_name, g->match_name, r->match_name);
                *addr = t->match_addr + g->match_addr + r->match_addr;
                *offset = *addr - SYMREG_DATA.io_origin1_offset;
                T_D("name = %s, addr = %u ", name, *addr);

                return MESA_RC_OK;
            }
        }
    }

    return SYMREG_RC_NO_MORE_REGS;
}

/******************************************************************************/
//
// Public functions
//
/******************************************************************************/

void symreg_cli_regs_print(symreg_func_t func, char *pattern, uint32_t value)
{
    mesa_rc     rc = MESA_RC_OK;
    void        *handle;
    uint32_t    max_width, reg_cnt, addr, the_offset;
    mesa_bool_t next = FALSE;
    char        *name = NULL;

    if ((rc = symreg_query_init(&handle, pattern, &max_width, &reg_cnt)) != MESA_RC_OK) {
        cli_printf("%% %s\n", symreg_error_txt(rc));
        return;
    }

    if ((name = (char *)malloc(max_width + 1)) == NULL) {
        cli_printf("%% Out of memory while attempting to allocate %u bytes\n", max_width + 1);
        goto do_exit;
    }

    while ((rc = symreg_query_next(handle, name, &addr, &the_offset, next)) == MESA_RC_OK) {
        // Compute the address to provide to mesa_reg_read/write().
        // These functions need the 32-bit address offset relative to the
        // beginning of the switch core base address (VTSS_IO_ORIGIN1_OFFSET).
        // This is what is presented in #the_offset.
        // The functions are luckily able to access CPU-domain registers and
        // are also dual-chip aware.
        // Both #the_offset and #addr are byte addresses (always jumps in steps of 4),
        // but the mesa_reg_read/write() functions expect 32-bit addresses, hence the
        // division by 4 (right-shift by 2).
        uint32_t offset = the_offset >> 2, v = 0;
        int j;
        mesa_chip_no_t chip_no = 0;

        if (func == READ) {
            rc = mesa_reg_read(NULL, chip_no, offset, &v);
        } else if (func == WRITE) {
            rc = mesa_reg_write(NULL, chip_no, offset, value);
            v  = value;
        } else {
            rc = MESA_RC_OK;
        }

        if (rc != MESA_RC_OK) {
            cli_printf("%% Failed to access register %s at address 0x%08x (which is offset = 0x%08x)\n", name, addr, offset);
            goto do_exit;
        }

        if (!next) {
            next = TRUE;

            if (func == QUERY) {
                cli_printf("%-*s %-10s\n", max_width, "Register", "Address");
            } else {
                cli_printf("%-*s %-10s %-10s 31     24 23     16 15      8 7       0\n", max_width, "Register", "Value", "Decimal");
            }
        }

        if (func == QUERY) {
            cli_printf("%-*s 0x%08x\n", max_width, name, addr);
        } else {
            cli_printf("%-*s 0x%08x %10u ", max_width, name, v, v);
            for (j = 31; j >= 0; j--) {
                cli_printf("%d%s", v & (1 << j) ? 1 : 0, j == 0 ? "\n" : (j % 4) ? "" : ".");
            }
        }
    }

    if (rc != SYMREG_RC_NO_MORE_REGS) {
        cli_printf("%% %s\n", symreg_error_txt(rc));
        goto do_exit;
    }

    cli_printf("%u match%s found\n", reg_cnt, reg_cnt != 1 ? "es" : "");

do_exit:
    if (name) {
        free(name);
    }

    if ((rc = symreg_query_uninit(handle)) != MESA_RC_OK) {
        cli_printf("%% %s\n", symreg_error_txt(rc));
    }

    return;
}

/******************************************************************************/
// symreg_init()
/******************************************************************************/
static void symreg_init(void)
{
    if (mesa_symreg_data_get(0, &SYMREG_DATA) != MESA_RC_OK) {
        T_E("Failed to get symreg-data");
    }

    if (SYMREG_DATA.repl_cnt_max > SYMREG_REPL_CNT_MAX) {
        T_E("SYMREG_REPL_CNT_MAX repl buffer is too small (%u > %u) - will cause memory overwrite!", SYMREG_DATA.repl_cnt_max, SYMREG_REPL_CNT_MAX);
        T_E("This is a bug!");
    }

    if (SYMREG_DATA.name_len_max > SYMREG_NAME_LEN_MAX) {
        T_E("SYMREG_REPL_CNT_MAX name buffer is too small (%u > %u) - will cause memory overwrite!", SYMREG_DATA.name_len_max, SYMREG_NAME_LEN_MAX);
        T_E("This is a bug!");
    }
}

void mscc_appl_symreg_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        symreg_init();
        break;

    default:
        break;
    }
}
