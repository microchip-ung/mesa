// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_AFI
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"
#include "vtss_util.h"

#if defined(VTSS_FEATURE_AFI_SWC)

#if defined(VTSS_AFI_V1)
/*
 * Allocate an ID for a frame subject to periodical injection.
 */
vtss_rc vtss_afi_alloc(const vtss_inst_t inst, vtss_afi_frm_dscr_t *const dscr, vtss_afi_id_t *const id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if (dscr == NULL || id == NULL) {
        return VTSS_RC_ERROR;
    }

    if (dscr->fps <= 0 || dscr->fps > VTSS_AFI_FPS_MAX) {
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(afi.alloc, dscr, id);
    }

    VTSS_EXIT();

    return rc;
}

/*
 * Cancel and free a periodically injected frame.
 */
vtss_rc vtss_afi_free(const vtss_inst_t inst, vtss_afi_id_t id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(afi.free, id);
    }

    VTSS_EXIT();

    return rc;
}

/*
 * Check that the frame just transmitted to the AFI indeed gets to get known by
 * the AFI.
 */
vtss_rc vtss_afi_hijack(const vtss_inst_t inst, vtss_afi_id_t id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(afi.hijack, id);
    }

    VTSS_EXIT();

    return rc;
}
#endif /* defined(VTSS_AFI_V1) */

#if defined(VTSS_AFI_V2)

#define AFI_DELAY_CC_MIN 12

/******************************************************************************/
//
// Internal AIL: Generic resource control
//
/******************************************************************************/

/*
 * afi_res_is_free()
 *
 * Returns true if specific resource is free, FALSE otherwise.
 */
static BOOL afi_res_is_free(u32 *const alloc_table, u32 res_idx)
{
    u32 word_idx = res_idx / 32;
    u8  bit_idx  = res_idx - word_idx * 32;

    if ((alloc_table[word_idx] & (1 << bit_idx)) == 0) {
        // Not allocated!
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
 * afi_res_alloc()
 *
 * Generic function for FRM/DTI/TTI allocation
 */
static vtss_rc afi_res_alloc(vtss_state_t *const vtss_state,
                             u32          *const alloc_table,
                             u32                 res_cnt,
                             u32          *const alloced_res_idx, // res_idx of allocated resource
                             u32                 min_res_idx,     // Minimum res_idx
                             u32                 max_res_idx,     // Maximum res_idx
                             BOOL                rand_mode)       // Randomize resource allocation
{
    u32 res_idx, start_res_idx;

    if (!(min_res_idx < res_cnt && max_res_idx < res_cnt)) {
        VTSS_E("Unexpected min/max: %u/%u, res_cnt=%u", min_res_idx, max_res_idx, res_cnt);
        return VTSS_RC_ERROR;
    }

    if (rand_mode) {
        /*
         * Randomize resource allocation.
         * This is intended for TTI allocation, where spreading the allocated TTIs
         * throughout the TTI table will help reduce burstiness for many real-life
         * configurations.
         */
        start_res_idx = min_res_idx + VTSS_OS_RAND() % (max_res_idx - min_res_idx + 1);
    } else {
        start_res_idx = min_res_idx;
    }

    res_idx = start_res_idx;

    do {
        if (afi_res_is_free(alloc_table, res_idx)) {
            u32 word_idx = res_idx / 32;
            u8  bit_idx  = res_idx - word_idx * 32;

            alloc_table[word_idx] |= (1 << bit_idx);
            *alloced_res_idx = res_idx;
            return VTSS_RC_OK;
        }

        if (++res_idx > max_res_idx) {
            VTSS_D("Wrapping around. res_idx = %u, min_res_idx = %u, max_res_idx = %u, start_res_idx = %u", res_idx, min_res_idx, max_res_idx, start_res_idx);
            res_idx = min_res_idx;
        }
    } while (res_idx != start_res_idx);

    VTSS_I("Out of resources");
    return VTSS_RC_ERROR; // Out of resources
}

/*
 * afi_res_free()
 *
 * Generic function for FRM/DTI/TTI freeing
 */
static vtss_rc afi_res_free(vtss_state_t *const vtss_state,
                            u32          *const alloc_table,
                            u32                 res_idx)
{
    u32     word_idx = res_idx / 32;
    u8      bit_idx = res_idx - word_idx * 32;
    vtss_rc rc = VTSS_RC_OK;

    if (afi_res_is_free(alloc_table, res_idx)) {
        // Not alloced!
        VTSS_E("res_idx=%u not alloced", res_idx);
        rc = VTSS_RC_ERROR;
    }

    alloc_table[word_idx] &= ~(u32)(1 << bit_idx);

    return rc;
}

/*
 * afi_hijack_error_print()
 */
static vtss_rc afi_hijack_error_print(vtss_state_t *vtss_state)
{
    vtss_afi_state_t *afi = &vtss_state->afi;
    u32              dti_cnt, tti_cnt, frm_cnt, dly_cnt;
    vtss_afi_frm_t   *frm;
    u32              res_idx;

    // TTI table
    tti_cnt = 0;
    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->tti_tbl); res_idx++) {
        if (afi_res_is_free(afi->ttis_alloced, res_idx)) {
            continue;
        }

        tti_cnt++;
    }

    // DTI table
    dti_cnt = 0;
    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->dti_tbl); res_idx++) {
        if (afi_res_is_free(afi->dtis_alloced, res_idx)) {
            continue;
        }

        dti_cnt++;
    }

    // Frame table
    frm_cnt = 0;
    dly_cnt = 0;
    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->frm_tbl); res_idx++) {
        if (afi_res_is_free(afi->frms_alloced, res_idx)) {
            continue;
        }

        frm = &afi->frm_tbl[res_idx];
        if (frm->entry_type) {
            dly_cnt++;
        } else {
            frm_cnt++;
        }
    }

    VTSS_E("AIL: Currently allocated in S/W: dti_cnt = %u, tti_cnt = %u, frm_cnt = %u, dly_cnt = %u", dti_cnt, tti_cnt, frm_cnt, dly_cnt);
    return VTSS_RC_OK;
}

/*
 * afi_state_to_str()
 */
static const char *afi_state_to_str(vtss_afi_entry_state_t state)
{
    switch (state) {
    case VTSS_AFI_ENTRY_STATE_FREE:
        return "Free";

    case VTSS_AFI_ENTRY_STATE_STOPPED:
        return "Stopped";

    case VTSS_AFI_ENTRY_STATE_STARTED:
        return "Started";

    default:
        VTSS_E("Unknown state (%u)", state);
        return "Unknown";
    }
}

/******************************************************************************/
//
// FRM resource control
//
/******************************************************************************/

/*
 * afi_frm_init()
 */
static void afi_frm_init(vtss_afi_frm_t *frm)
{
    VTSS_MEMSET(frm, 0, sizeof(*frm));
}

/*
 * afi_frm_alloc()
 */
static vtss_rc afi_frm_alloc(vtss_state_t *const vtss_state, i32 *const frm_idx, i32 min_frm_idx, u8 entry_type, i32 prev_frm_tbl_idx)
{
    vtss_rc        rc;
    vtss_afi_frm_t *entry;

    if ((rc = afi_res_alloc(vtss_state, vtss_state->afi.frms_alloced, VTSS_AFI_FRM_CNT, (u32 *)frm_idx, min_frm_idx, VTSS_AFI_FRM_CNT - 1, FALSE)) != VTSS_RC_OK) {
        VTSS_E("Out of FRMs");
        return rc;
    }

    VTSS_D("Allocated entry in FRM_TBL[%u]", (u32)(*frm_idx));

    entry = &vtss_state->afi.frm_tbl[(u32)(*frm_idx)];
    afi_frm_init(entry);

    // It's either a frame entry (0) or a delay entry (1)
    entry->entry_type = entry_type;

    // Link the previous entry to this one
    if (prev_frm_tbl_idx >= 0) {
        vtss_state->afi.frm_tbl[prev_frm_tbl_idx].next_ptr = *frm_idx;
    }

    return VTSS_RC_OK;
}

/*
 * afi_frm_free()
 */
static vtss_rc afi_frm_free(vtss_state_t *const vtss_state, i32 frm_idx)
{
    if (frm_idx >= VTSS_AFI_FRM_CNT) {
        VTSS_E("frm_idx=%i > %u", frm_idx, VTSS_AFI_FRM_CNT);
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(&vtss_state->afi.frm_tbl[frm_idx], 0, sizeof(vtss_state->afi.frm_tbl[frm_idx]));
    return afi_res_free(vtss_state, vtss_state->afi.frms_alloced, frm_idx);
}

/******************************************************************************/
//
// Internal AIL: DTI resource control
//
/******************************************************************************/

/*
 * afi_dti_init()
 */
static void afi_dti_init(vtss_afi_dti_t *dti)
{
    VTSS_MEMSET(dti, 0, sizeof(vtss_afi_dti_t));
    dti->paused  = 1;  // Not started yet
}

/*
 * afi_dti_alloc()
 */
static vtss_rc afi_dti_alloc(vtss_state_t *const vtss_state, u32 *const dti_idx)
{
    vtss_rc rc;

    if ((rc = afi_res_alloc(vtss_state, vtss_state->afi.dtis_alloced, VTSS_AFI_FAST_INJ_CNT, dti_idx /* min_res_idx+max_res_idx (full range allowed) */, 0, VTSS_AFI_FAST_INJ_CNT - 1, FALSE)) != VTSS_RC_OK) {
        VTSS_E("Out of DTIs");
        return rc;
    }

    afi_dti_init(&vtss_state->afi.dti_tbl[*dti_idx]);

    return VTSS_RC_OK;
}

/*
 * afi_dti_free()
 */
static vtss_rc afi_dti_free(vtss_state_t *const vtss_state, u32 dti_idx)
{
    if (dti_idx >= VTSS_AFI_FAST_INJ_CNT) {
        VTSS_E("dti_idx=%u > %u", dti_idx, VTSS_AFI_FAST_INJ_CNT);
        return VTSS_RC_ERROR;
    }

    // Clear state before sending it back to free pool.
    afi_dti_init(&vtss_state->afi.dti_tbl[dti_idx]);

    return afi_res_free(vtss_state, vtss_state->afi.dtis_alloced, dti_idx);
}

/*
 * afi_dti_frm_free()
 *
 * If deleting delay-entries only, only delay entries will get freed, while all
 * frames in this DTI's frame list will be linked together.
 * Otherwise, both frame and delay entries will get freed.
 */
static vtss_rc afi_dti_frm_free(vtss_state_t *const vtss_state, vtss_afi_dti_t *dti, BOOL delay_entries_only)
{
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    i32            frm_idx;
    vtss_afi_frm_t *prev_frm_entry = NULL;

    frm_idx = dti->first_frm_idx;
    dti->trailing_delay_seq_cnt = 0;

    if (frm_idx < 0) {
        // No frames allocated.
        return VTSS_RC_OK;
    }

    while (frm_idx) {
        vtss_afi_frm_t *entry = &frm_tbl[frm_idx];
        u32 next_ptr = entry->next_ptr;

        if (delay_entries_only && entry->entry_type == 0) {
            // This is a frame entry that we need to stay in the list.
            // Update the previous frame's next_ptr to point to this one.
            if (prev_frm_entry) {
                prev_frm_entry->next_ptr = frm_idx;
            }

            prev_frm_entry  = entry;
            entry->next_ptr = 0;
            entry->frm_delay.frm.inj_cnt  = 1;
        } else {
            // Either remove both frame and delay entries or only delay entries.
            VTSS_RC(afi_frm_free(vtss_state, frm_idx));
        }

        frm_idx = next_ptr;
    }

    return VTSS_RC_OK;
}

/*
 * afi_dti_cnt_get()
 */
static vtss_rc afi_dti_cnt_get(vtss_state_t *const vtss_state, u32 dti_idx, u32 *total_cnt, u32 *frm_cnt, u32 *hijacked_cnt)
{
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];
    u32            frm_idx;

    *total_cnt    = 0;
    *frm_cnt      = 0;
    *hijacked_cnt = 0;

    for (frm_idx = dti->first_frm_idx; frm_idx != 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        (*total_cnt)++;

        if (frm_tbl[frm_idx].entry_type == 0) {
            (*frm_cnt)++;

            if (frm_tbl[frm_idx].frm_delay.frm.frm_size) {
                (*hijacked_cnt)++;
            }
        }
    }

    return VTSS_RC_OK;
}

/*
 * afi_dti_delay_alloc()
 */
static vtss_rc afi_dti_delay_alloc(vtss_state_t *const vtss_state, vtss_afi_dti_t *dti, i32 *const frm_idx, i32 prev_idx, u32 next_ptr)
{
    vtss_rc rc;

    VTSS_D("Allocating and linking new delay entry");
    if ((rc = afi_frm_alloc(vtss_state, frm_idx, 1, 1, prev_idx)) != VTSS_RC_OK) {
        // Free all currently allocated delay entries, but leave the frm
        // entries.
        (void)afi_dti_frm_free(vtss_state, dti, TRUE);
        VTSS_E("Unable to allocate more delay entries (FRM_TBL[] full)");
        return VTSS_RC_ERROR;
    }

    vtss_state->afi.frm_tbl[*frm_idx].next_ptr = next_ptr;

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// Internal AIL: TTI resource control
//
/******************************************************************************/

/*
 * afi_tti_init()
 */
static void afi_tti_init(vtss_afi_tti_t *tti)
{
    VTSS_MEMSET(tti, 0, sizeof(vtss_afi_tti_t));
    tti->frm_idx = -1; // frm_idx == -1 <=> No FRM allocated.
    tti->paused  = 1;  // Not started yet
}

/*
 * afi_tti_alloc()
 */
static vtss_rc afi_tti_alloc(vtss_state_t *const vtss_state,
                             u32          *const tti_idx,
                             u32                 min_tti_idx,
                             u32                 max_tti_idx)
{
    vtss_rc rc;

    if ((rc = afi_res_alloc(vtss_state, vtss_state->afi.ttis_alloced, VTSS_AFI_SLOW_INJ_CNT, tti_idx, min_tti_idx, max_tti_idx, TRUE)) != VTSS_RC_OK) {
        VTSS_E("Out of TTIs");
        return rc;
    }

    afi_tti_init(&vtss_state->afi.tti_tbl[*tti_idx]);

    return VTSS_RC_OK;
}

/*
 * afi_tti_free()
 */
static vtss_rc afi_tti_free(vtss_state_t *const vtss_state, const u32 tti_idx)
{
    if (tti_idx >= VTSS_AFI_SLOW_INJ_CNT) {
        VTSS_E("tti_idx=%u > %u", tti_idx, VTSS_AFI_SLOW_INJ_CNT);
        return VTSS_RC_ERROR;
    }

    // Clear state before sending it back to free pool.
    afi_tti_init(&vtss_state->afi.tti_tbl[tti_idx]);

    return afi_res_free(vtss_state, vtss_state->afi.ttis_alloced, tti_idx);
}

/******************************************************************************/
//
// Internal AIL: Argument checking
//
/******************************************************************************/

/*
 * afi_frm_idx_chk()
 */
vtss_rc afi_frm_idx_chk(struct vtss_state_s *const vtss_state, i32 frm_idx)
{
    if (frm_idx < 0 || frm_idx >= VTSS_AFI_FRM_CNT) {
        VTSS_E("frm_idx == %i illegal", frm_idx);
        return VTSS_RC_ERROR;
    }

    if (afi_res_is_free(vtss_state->afi.frms_alloced, frm_idx)) {
        VTSS_E("frm_idx == %i not alloced", frm_idx);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/*
 * afi_dti_idx_chk()
 */
static vtss_rc afi_dti_idx_chk(struct vtss_state_s *const vtss_state, u32 dti_idx)
{
    if (dti_idx >= VTSS_AFI_FAST_INJ_CNT) {
        VTSS_E("dti_idx == %u illegal", dti_idx);
        return VTSS_RC_ERROR;
    }

    if (afi_res_is_free(vtss_state->afi.dtis_alloced, dti_idx)) {
        VTSS_E("dti_idx == %u not alloced", dti_idx);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/*
 * afi_tti_idx_chk()
 */
static vtss_rc afi_tti_idx_chk(struct vtss_state_s *const vtss_state, u32 tti_idx)
{
    if (tti_idx >= VTSS_AFI_SLOW_INJ_CNT) {
        VTSS_E("tti_idx == %u illegal", tti_idx)
        return VTSS_RC_ERROR;
    }

    if (afi_res_is_free(vtss_state->afi.ttis_alloced, tti_idx)) {
        VTSS_E("tti_idx == %u not alloced", tti_idx);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// Internal AIL: Other functions
//
/******************************************************************************/

/*
 * afi_tti_start_cfg_cmp()
 *
 * Compare TTI start_cfgs. 0 => Identical
 */
static int afi_tti_start_cfg_cmp(const vtss_afi_slow_inj_start_cfg_t *const cfg1, const vtss_afi_slow_inj_start_cfg_t *const cfg2)
{
    return VTSS_MEMCMP(cfg1, cfg2, sizeof(vtss_afi_slow_inj_start_cfg_t));
}

/*
 * afi_tti_start_cfg_cp()
 *
 * Copy cfg2 to cfg1
 */
static void afi_tti_start_cfg_cp(vtss_afi_slow_inj_start_cfg_t *const cfg1, const vtss_afi_slow_inj_start_cfg_t *const cfg2)
{
    VTSS_MEMCPY(cfg1, cfg2, sizeof(vtss_afi_slow_inj_start_cfg_t));
}

/*
 * afi_div_round32()
 */
static u32 afi_div_round32(u32 dividend, u32 divisor)
{
    return ((dividend + (divisor / 2)) / divisor);
}

/*
 * afi_timer_prec_ok()
 *
 * Check that actual timer_len is with +/- prec_pct of requested value
 */
static BOOL afi_timer_prec_ok(u32 timer_len_us_requested, u32 timer_len_us_actual, u32 prec_pct)
{
    BOOL result;
    u32 abs_diff  = timer_len_us_requested > timer_len_us_actual ? timer_len_us_requested - timer_len_us_actual : timer_len_us_actual - timer_len_us_actual;
    u32 alwd_diff = ((u64)prec_pct * timer_len_us_requested) / 100LLU;

    result = abs_diff <= alwd_diff;

    VTSS_D("timer_len_us_requested = %u, timer_len_us_actual = %u, prec_pct = %u => abs_diff = %u && alwd_diff = %u => result = %d",
           timer_len_us_requested, timer_len_us_actual, prec_pct, abs_diff, alwd_diff, result);

    return result;
}

/*
 * afi_min64()
 */
static u64 afi_min64(u64 a, u64 b)
{
    return (a < b) ? a : b;
}

/*
 * afi_max64()
 */
static u64 afi_max64(u64 a, u64 b)
{
    return (a > b) ? a : b;
}

/******************************************************************************/
//
// Internal AIL: DTI bandwidth calculation
//
/******************************************************************************/

/*
 * afi_dti_delay_assign()
 *
 * Assign a delay to a delay entry in the frame table. Make sure it's not
 * overflowing the entry and return the remainder.
 * delay_cc  is the place to put the result.
 * delay_xm  is the requested delay multiplied by @scale.
 * scale     is the scale
 * saturated will become TRUE if #delay_cc is at its maximum value, FALSE otherwise.
 */
static u64 afi_dti_delay_assign(u32 *delay_cc, u64 delay_xm, u64 scale, BOOL *saturated)
{
    u64 act_delay_xm, rem_xm, d;

    // The maximum allowed delay (in clock cycles) per frame table entry (this
    // constant is chip-specific, but defined manually in vtss_afi_state.h, as
    // there is no corresponding auto-generated one in vtss_XXX_regs_afi.h).
    const u32 delay_cc_max = VTSS_BIT(VTSS_AFI_FRM_TBL_PART0_DELAY_WID) - 1;

    VTSS_D("delay_xm = %" PRIu64 ", delay_cc_max = %u, scale = %" PRIu64, delay_xm, delay_cc_max, scale);

    // Set frame delay to truncation of delay_xm - minimum AFI_DELAY_CC_MIN (to be able to
    // process the delay entry).
    d = afi_max64(VTSS_DIV64(delay_xm, scale), AFI_DELAY_CC_MIN);

    // Don't allow it to overflow the delay field in the frame table.
    *delay_cc = afi_min64(d, delay_cc_max);
    *saturated = *delay_cc == delay_cc_max;

    act_delay_xm = (u64)*delay_cc * scale;
    VTSS_D("act_delay_xm = %" PRIu64, act_delay_xm);

    // Return the remaining delay scaled with @scale.
    // Since we require a minimum delay of AFI_DELAY_CC_MIN, it could be that
    // act_delay_xm becomes bigger than delay_xm, so return 0 if that's the
    // case (otherwise, the caller may allocate another delay entry or adjust
    // the current), otherwise the difference.
    rem_xm = act_delay_xm < delay_xm ? delay_xm - act_delay_xm : 0;

    VTSS_D("act_delay_xm = %" PRIu64 " => delay in reg = %u, return = %" PRIu64, act_delay_xm, *delay_cc, rem_xm);

    return rem_xm;
}

/*
 * afi_dti_delay_calc_do()
 *
 * Handles computation and allocation of delay elements when requested BW is
 * non-zero.
 */
static vtss_rc afi_dti_delay_calc_do(vtss_state_t *const vtss_state, u32 dti_idx, const vtss_afi_fast_inj_start_cfg_t *const cfg)
{
    vtss_afi_dti_t  *dti = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t  *frm_tbl = vtss_state->afi.frm_tbl;
    u64             exs_delay_cc = 0, delay_xm = 0; // Delay measured in clock cycles multiplied by a million (hence "_xm" suffix).
    u32             delay_slot_cnt = 0, frm_idx, cnt = 0, i;
    i32             frm_tbl_delay_idx, last_frm_tbl_idx = 0;
    BOOL            last_delay_slot_saturated, add_to_last;
    frm_tbl_delay_t *last_delay_slot = NULL;
    frm_tbl_frm_t   *last_frm = NULL;
    u32             frame_indices[VTSS_AFI_FAST_INJ_FRM_CNT_MAX];

    // The scale we use to get fractions of a clock cycle when we adjust the
    // trailing delays.
    const u64 scale = 1e6;

    // Algorithm
    // ---------
    // 1)  For each frame, assign delays proportional to the frame size and
    //     resulting in a rate equal to or higher than the requested rate.
    // 2)  If the requested BW is equal to the actual from 1), we are done.
    // 3)  Otherwise, if more than one delay entry is assigned to a given frame
    //     (due to H/W saturation of the delay entries for low frame rates), add
    //     a clock cycle to the last delay to ensure the actual BW gets below the
    //     requested BW. Done.
    // 3)  Otherwise calculate "excess delay", i.e. the number of delay clock
    //     cycles beyond the AFI_DELAY_CC_MIN clock cycles it takes to process
    //     each pair of Frame/Delay-entries.
    // 3a) If one frame in flow:
    //     Fine-tune BW using INJ_CNT and an additional delay.
    //     Make sure INJ_CNT is high enough to have excess delay >=
    //     AFI_DELAY_CC_MIN cycles.
    // 3b) Otherwise (more than one frame in flow):
    //     If excess >= 12 cycles, fine-tune BW with an additional delay entry.
    //     If excess <  12 cycles, add one to the last delay to ensure actual
    //     BW gets below requested BW.
    VTSS_MEMSET(frame_indices, 0, sizeof(frame_indices));
    for (frm_idx = dti->first_frm_idx; frm_idx != 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        if (cnt >= VTSS_ARRSZ(frame_indices)) {
            VTSS_E("Corrupt frame table for DTI #%u", dti_idx);
            return VTSS_RC_ERROR;
        }

        frame_indices[cnt++] = frm_idx;
    }

    if (cnt != dti->frm_cnt) {
        VTSS_E("Found %u frames in frame table, expected %u", cnt, dti->frm_cnt);
        return VTSS_RC_ERROR;
    }

    // Variables post-fixed with "_xm" have been multiplied by 1e6 to improve accuracy.
    for (i = 0; i < dti->frm_cnt; i++) {
        u64             factor1, factor2;

        last_frm_tbl_idx = frame_indices[i];
        last_frm = &frm_tbl[last_frm_tbl_idx].frm_delay.frm;

        last_frm->inj_cnt = 1;

        // Calculate delay required to achieve bps.
        // The formula is:
        //    delay_xm = [frm_size * 8 * (1e18 / bps)] / clk_period_ps
        // It is the delay in clock cycles multiplied by 1e6 in order to get
        // the miscalculation fraction, which is inserted in a trailing delay
        // slot. In order for the dividend of the above equation not to overflow
        // a 64-bit unsigned (2^64 - 1 ~= 1.8e19), [1e18 / bps] cannot exceed
        // [1.8e19 / 1e5] = 1.8e14, which means that bps cannot be lower than
        // 1e18 / 1.8e14 = 5556 bps, so let's move a factor of 10 outside the
        // division when bps < 10000.
        if (cfg->bps < 10000) {
            factor1 = 10;
        } else {
            factor1 = 1;
        }

        factor2 = scale / factor1;

        // Notice the "+=": We carry over any delay fraction from the previous
        // frame to this frame.
        delay_xm += factor1 * VTSS_DIV64((u64)last_frm->frm_size * 8LLU * VTSS_DIV64(1e12 * factor2, cfg->bps), vtss_state->afi.clk_period_ps);

        // There must be a minimum delay between frames, so whatever delay_xm is
        // now, we must ensure it's at least AFI_DELAY_CC_MIN x scale (there's
        // guaranteed room for this without delay_xm overflowing).
        delay_xm = afi_max64(delay_xm, AFI_DELAY_CC_MIN * scale);

        VTSS_D("frm_size = %u, rate = %" PRIu64 " bps, clock cycle = %" PRIu64 " ps => delay_xm = %" PRIu64, last_frm->frm_size, cfg->bps, vtss_state->afi.clk_period_ps, delay_xm);

        // Keep adding delay entries until we only have the residual left
        while (delay_xm >= scale) {
            delay_slot_cnt++;

            VTSS_D("Delay entry #%u for frame #%u: Considering delay_xm = %" PRIu64, delay_slot_cnt, i, delay_xm);

            // We are definitely going to need a delay element.
            // Allocate one and link it in.
            VTSS_RC((afi_dti_delay_alloc(vtss_state, dti, &frm_tbl_delay_idx, last_frm_tbl_idx, i < (u32)(dti->frm_cnt - 1) ? frame_indices[i + 1] : 0)));
            last_frm_tbl_idx = frm_tbl_delay_idx;
            last_delay_slot = &frm_tbl[frm_tbl_delay_idx].frm_delay.delay;

            // Assign the delay while taking saturation and minimum values
            // into account. The function returns the remainder.
            delay_xm = afi_dti_delay_assign(&last_delay_slot->delay, delay_xm, scale, &last_delay_slot_saturated);
        }

        // Excess delay is only used if it's a multi-frame flow and each frame
        // comes with exactly one single delay entry.
        exs_delay_cc += (last_delay_slot->delay - AFI_DELAY_CC_MIN);
    }

    // Here, delay_xm is what we still need to apply to a trailing delay slot or
    // - in case that's impossible - to the last delay slot if there's room (if
    // not, we have to create a new delay slot in order not to exceed the
    // requested bandwidth).

    // There are two cases to consider. Both cases will only work if each frame
    // comes with exactly one delay entry.
    // 1) Single-frame case, where we use the frame's "inj_cnt" entry to repeat
    //    both the frame and the subsequent delay a number of times before
    //    ending with a trailing delay.
    // 2) Multi-frame case, where we fine-tune using the Trailing Delay (TD).

    if (delay_xm == 0) {
        // Done. No trailing delays needed.
        return VTSS_RC_OK;
    }

    // Figure out whether we can use inj_cnt/TD to fine-tune. #add_to_last
    // remains FALSE if we can.
    add_to_last = FALSE;
    if (delay_slot_cnt != dti->frm_cnt) {
        // We know that at least one delay slot will be allocated per frame. So
        // if the total number of delay slots isn't equal to the number of
        // frames, we cannot use "inj_cnt" (single-frame) or TD (multi-frame) to
        // adjust the trailing delay.
        // Instead, we simply add a clock cycle to the last delay entry (if
        // there's room).
        add_to_last = TRUE;
    }

    if (dti->frm_cnt == 1 && !add_to_last) {
        // Sub-clock-cycle optimization to get as close to the correct
        // rate as possible.
        u32 delay_best         = 0;
        u32 inj_cnt_best       = 0;
        i32 carry_xm_diff_best = (i32)scale;
        u32 inj_cnt, delay;

        VTSS_D("Trying to cater for non-zero fraction (%u)", (u32)delay_xm);

        // Loop through possible delay values and search for closest match for
        // delay_xm. Use same max value for inj_cnt as for
        // TRAILING_DELAY_SEQ_CNT.
        for (inj_cnt = 1; inj_cnt <= VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX; inj_cnt++) {
            for (delay = 1; delay <= inj_cnt; delay++) {
                i32 carry_xm_diff = (i32)((delay * scale) / inj_cnt - delay_xm);

                VTSS_N("inj_cnt = %u, delay = %u, carry_xm_diff = %i", inj_cnt, delay, carry_xm_diff);

                // Delay must be bigger than the carry (otherwise BW will be
                // above requested rate).
                if (carry_xm_diff < 0) {
                    continue;
                }

                // Make sure there is sufficient excess delay to process the
                // additional delay entry. Here, #last_delay_slot is the one and
                // only delay element folowing the frame.
                if ((last_delay_slot->delay - AFI_DELAY_CC_MIN) * inj_cnt < AFI_DELAY_CC_MIN) {
                    continue;
                }

                if (carry_xm_diff < carry_xm_diff_best) {
                    // Found new best
                    carry_xm_diff_best = carry_xm_diff;
                    inj_cnt_best       = inj_cnt;
                    delay_best         = delay;
                }
            }
        }

        VTSS_D("delay_best = %u, inj_cnt_best = %u", delay_best, inj_cnt_best);

        if (delay_best != 0) {
            // Need a trailing delay element. Allocate one.
            VTSS_RC((afi_dti_delay_alloc(vtss_state, dti, &frm_tbl_delay_idx, last_frm_tbl_idx, 0)));

            // Update the frame
            last_frm->inj_cnt = inj_cnt_best;

            // and the trailing delay.
            frm_tbl[frm_tbl_delay_idx].frm_delay.delay.delay = delay_best;
        } else {
            // Add a clock cycle to the last delay entry.
            add_to_last = TRUE;
        }
    } else if (dti->frm_cnt > 1 && !add_to_last) {
        // For multi-frames, we must also have at least AFI_DELAY_CC_MIN clock
        // cycles excess delay in order to utilize the TD, since a TD entry
        // takes AFI_DELAY_CC_MIN cycles to process.
        if (exs_delay_cc >= AFI_DELAY_CC_MIN) {
            // Best value for TRAILING_DELAY_SEQ_CNT + Delay
            // - and corresponding diff against delay_xm
            u32 td_seq_cnt_best    = 0;
            u32 td_delay_best      = 0;
            i32 carry_xm_diff_best = (i32)1e6;
            u32 tds, delay;

            // Loop through possible TDS values and search for closest match for carry
            for (tds = 1; tds <= VTSS_AFI_TRAILING_DELAY_SEQ_CNT_MAX; tds++) {
                for (delay = 1; delay <= tds; delay++) {
                    i32 carry_xm_diff = (i32)((u64)(delay * 1e6 / tds) - delay_xm);

                    // Delay must be bigger than the carry (otherwise BW gets above requested rate)
                    if (carry_xm_diff < 0) {
                        continue;
                    }

                    if (carry_xm_diff < carry_xm_diff_best) {
                        // Found new best
                        carry_xm_diff_best = carry_xm_diff;
                        td_seq_cnt_best    = tds;
                        td_delay_best      = delay;
                    }
                }
            }

            VTSS_D("td_seq_cnt_best = %u, td_delay_best = %u", td_seq_cnt_best, td_delay_best);

            if (td_seq_cnt_best != 0) {
                // Found TD adjustment
                // Need a trailing delay element. Allocate one.
                VTSS_RC((afi_dti_delay_alloc(vtss_state, dti, &frm_tbl_delay_idx, last_frm_tbl_idx, 0)));

                dti->trailing_delay_seq_cnt = td_seq_cnt_best;

                // and the trailing delay.
                frm_tbl[frm_tbl_delay_idx].frm_delay.delay.delay = td_delay_best;
            }
        } else {
            // Cannot use TDS. Add 1 to last delay to avoid being above requested BW
            add_to_last = TRUE;
        }
    }

    if (add_to_last) {
        // We couldn't use the inj_cnt/TD properties to add a trailing delay, so
        // add one clock cycle to the last delay entry - if there's room.
        if (last_delay_slot_saturated) {
            // There's not room in last entry, so add a new.
            VTSS_RC((afi_dti_delay_alloc(vtss_state, dti, &frm_tbl_delay_idx, last_frm_tbl_idx, 0)));
            frm_tbl[frm_tbl_delay_idx].frm_delay.delay.delay = AFI_DELAY_CC_MIN;
        } else {
            last_delay_slot->delay++;
        }
    }

    return VTSS_RC_OK;
}

/*
 * afi_dti_bps_actual_calc()
 *
 * Calculate cfg->bps_actual for DTI's Frame-Delay configuration
 */
static vtss_rc afi_dti_bps_actual_calc(vtss_state_t *const vtss_state, u32 dti_idx, vtss_afi_fast_inj_start_cfg_t *const cfg)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    i32            frm_idx;
    u32            frm_size_sum = 0;
    u64            delay_sum_xm = 0;
    u32            entry_cnt    = 0; // Number of FRM_TBL entries in Frame-Delay sequence
    vtss_afi_frm_t *frm_prev;

    frm_idx = dti->first_frm_idx;
    VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));

    frm_prev = NULL;

    // Walk-through all FRM_TBL entries in sequence and calculate number of
    // bytes and number of delay clock cycles in entire sequence.
    while (frm_idx) {
        vtss_afi_frm_t *entry = &frm_tbl[frm_idx];
        entry_cnt++;

        VTSS_D("entry_cnt == %u, entry->entry_type = %s", entry_cnt, entry->entry_type == 0 ? "frame" : "delay");

        if (entry->entry_type == 0) {
            // Frame
            VTSS_D("frm_size_sum before = %u", frm_size_sum);
            frm_size_sum += entry->frm_delay.frm.frm_size * entry->frm_delay.frm.inj_cnt;
            VTSS_D("frm_size_sum after = %u", frm_size_sum);
        } else {
            // Delay
            if (frm_prev && frm_prev->entry_type == 0) {
                // Previous entry was a frame, so multiply delay with inj_cnt
                VTSS_D("delay_sum_xm before = %" PRIu64", delay = %u inj_cnt = %u", delay_sum_xm, entry->frm_delay.delay.delay, frm_prev->frm_delay.frm.inj_cnt);
                delay_sum_xm += (u64)(entry->frm_delay.delay.delay * (u64)frm_prev->frm_delay.frm.inj_cnt * (u64)1e6);
                VTSS_D("delay_sum_xm after = %" PRIu64, delay_sum_xm);
            } else {
                if (entry->next_ptr == 0) {
                    if (dti->trailing_delay_seq_cnt > 0) {
                        // Trailing delay
                        VTSS_D("Trailing w/ seq_cnt > 0: delay_sum_xm before = %" PRIu64", delay = %u trailing_delay_seq_cnt = %u", delay_sum_xm, entry->frm_delay.delay.delay, dti->trailing_delay_seq_cnt);
                        delay_sum_xm += VTSS_DIV64((u64)entry->frm_delay.delay.delay * (u64)1e6, (u64)dti->trailing_delay_seq_cnt);
                        VTSS_D("Trailing w/ seq_cnt > 0: delay_sum_xm after = %" PRIu64, delay_sum_xm);
                    } else {
                        VTSS_D("Trailing w/ seq_cnt == 0: delay_sum_xm before = %" PRIu64 ", delay = %u", delay_sum_xm, entry->frm_delay.delay.delay);
                        delay_sum_xm += (u64)entry->frm_delay.delay.delay * (u64)1e6;
                        VTSS_D("Trailing w/ seq_cnt == 0: delay_sum_xm after = %" PRIu64, delay_sum_xm);
                    }
                } else {
                    VTSS_D("Not trailing: delay_sum_xm before = %" PRIu64 ", delay = %u", delay_sum_xm, entry->frm_delay.delay.delay);
                    delay_sum_xm += (u64)entry->frm_delay.delay.delay * (u64)1e6;
                    VTSS_D("Not trailing: delay_sum_xm after = %" PRIu64, delay_sum_xm);
                }
            }
        }

        frm_prev = entry;
        frm_idx  = entry->next_ptr;
    }

    if (frm_size_sum == 0) {
        VTSS_E("frm_size_sum=%u", frm_size_sum);
        return VTSS_RC_ERROR;
    }

    VTSS_D("Final delay_sum_xm = %" PRIu64, delay_sum_xm);

    if (delay_sum_xm) {
        // Calculate bps_actual
        // To avoid overflow in 64 bit calculations different expressions and to
        // increase accuracy depending on delay_sum_xm.
        if (delay_sum_xm > 1e12) {
            cfg->bps_actual = VTSS_DIV64(VTSS_DIV64((u64)frm_size_sum * (u64)8 * VTSS_DIV64((u64)1e18, VTSS_DIV64(delay_sum_xm, (u64)1e6)), vtss_state->afi.clk_period_ps) + (u64)5e5, (u64)1e6);
        } else if (delay_sum_xm > 1e10) {
            cfg->bps_actual =            VTSS_DIV64((u64)frm_size_sum * (u64)8 * VTSS_DIV64((u64)1e6 * VTSS_DIV64((u64)1e18, delay_sum_xm), vtss_state->afi.clk_period_ps) + (u64)5e5, (u64)1e6);
        } else {
            cfg->bps_actual =            VTSS_DIV64((u64)frm_size_sum * (u64)8 * (u64)1e6 * VTSS_DIV64(VTSS_DIV64((u64)1e18, delay_sum_xm), vtss_state->afi.clk_period_ps) + (u64)5e5, (u64)1e6);
        }
    } else {
        VTSS_E("delay_sum_xm=%" PRIu64, delay_sum_xm);
        return VTSS_RC_ERROR;
    }

    VTSS_D("cfg->bps_actual = %" PRIu64, cfg->bps_actual);

    return VTSS_RC_OK;
}

/*
 * afi_dti_delay_calc()
 *
 * Update Frame-Delay sequence for DTI to match requested configuration
 */
static vtss_rc afi_dti_delay_calc(vtss_state_t *const vtss_state, u32 dti_idx, vtss_afi_fast_inj_start_cfg_t *const cfg)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

    VTSS_RC(afi_dti_idx_chk(vtss_state, dti_idx));

    // First release all current delay entries in frame table for this DTI.
    // afi_dti_frm_free() also stitches together the frame entries and sets
    // inj_cnt to 1.
    VTSS_RC(afi_dti_frm_free(vtss_state, dti, TRUE));

    if (cfg->bps == 0) {
        // No delays, just inject as fast as possible, relying on FRM_OUT_MAX
        // to throttle bandwidth down to port's bandwidth.
        // The frames are already stitched together by the call to afi_dti_frm_free().
        cfg->bps_actual = 0;
    } else {
        // Calculate delays
        VTSS_RC(afi_dti_delay_calc_do(vtss_state, dti_idx, cfg));

        // Calculate cfg->actual_bps
        VTSS_RC(afi_dti_bps_actual_calc(vtss_state, dti_idx, cfg));
    }

    return VTSS_RC_OK;
}

/*
 * afi_dti_inj_start()
 */
static vtss_rc afi_dti_inj_start(vtss_state_t *vtss_state, vtss_afi_fastid_t fastid, vtss_afi_fast_inj_start_cfg_t *const cfg, BOOL start_flow)
{
    vtss_afi_dti_t *dti;
    BOOL           do_frm_delay_config = FALSE;
    u32            total_cnt, frm_cnt, hijacked_cnt;
    vtss_rc        rc;

    VTSS_I("Enter, ID = %u, bps = %" PRIu64 ", seq_cnt = %u", fastid, cfg->bps, cfg->seq_cnt);

    dti = &vtss_state->afi.dti_tbl[fastid];

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("DTI already started");
        return VTSS_RC_ERROR;
    }

    if (dti->frm_cnt == 0) {
        VTSS_E("frm_cnt = %u", dti->frm_cnt);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(afi_dti_cnt_get(vtss_state, fastid, &total_cnt, &frm_cnt, &hijacked_cnt));

    if (frm_cnt != hijacked_cnt || frm_cnt != dti->frm_cnt) {
        VTSS_E("Not all frames were hijacked. Expected %u, got %u/%u", frm_cnt, hijacked_cnt, dti->frm_cnt);
        return VTSS_RC_ERROR;
    }

    if (cfg->bps > (u64)VTSS_AFI_FAST_INJ_BPS_MAX) {
        VTSS_E("bps=%" PRIu64 " too high", cfg->bps);
        return VTSS_RC_ERROR;
    }

    if (cfg->bps < (u64)VTSS_AFI_FAST_INJ_BPS_MIN) {
        VTSS_E("bps=%" PRIu64 " too low", cfg->bps);
        return VTSS_RC_ERROR;
    }

    if (cfg->bps != dti->start_cfg.bps) {
        // Bandwidth has changed => Recalculate delays
        VTSS_RC(afi_dti_delay_calc(vtss_state, fastid, cfg));

        dti->bw = (cfg->bps >= VTSS_AFI_DTI_BW1_THRES_BPS);
        do_frm_delay_config = TRUE;
    }

    dti->mode = (cfg->seq_cnt == 0 ? 1 : 0);
    dti->frm_inj_cnt = cfg->seq_cnt;

    rc = vtss_state->afi.dti_start(vtss_state, fastid, do_frm_delay_config, TRUE /* do_dti_config */, start_flow);
    VTSS_I("Exit, ID = %u", fastid);

    return rc;
}

/******************************************************************************/
//
// External AIL: Fast injections
//
/******************************************************************************/

/*
 * vtss_afi_fast_inj_alloc()
 */
vtss_rc vtss_afi_fast_inj_alloc(const vtss_inst_t inst, const vtss_afi_fast_inj_alloc_cfg_t *const cfg, vtss_afi_fastid_t *const fastid)
{
    vtss_state_t   *vtss_state;
    u32            dti_idx;
    i32            frm_idx, prev_frm_idx;
    i32            i;
    vtss_rc        rc = VTSS_RC_ERROR;
    vtss_afi_dti_t *dti;

    VTSS_I("Enter(port_no = %d)", cfg->port_no);

    // Argument checks
    if (cfg == NULL || fastid == NULL) {
        VTSS_E("cfg or fastid is NULL");
        return VTSS_RC_ERROR;
    }

    *fastid = 0;

    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_none_check(inst, &vtss_state, cfg->port_no)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if (cfg->port_no == VTSS_PORT_NO_NONE) {
        // Masquerading. Check masquerade port
        if ((rc = vtss_port_no_check(vtss_state, cfg->masquerade_port_no)) != VTSS_RC_OK) {
            VTSS_E("When creating up-flows, fill in #masquerade_port_no member");
            goto do_exit;
        }
    }

    if (cfg->frm_cnt == 0 || cfg->frm_cnt > VTSS_AFI_FAST_INJ_FRM_CNT_MAX) {
        VTSS_E("Illegal frm_cnt (%u)", cfg->frm_cnt);
        rc  = VTSS_RC_ERROR;
        goto do_exit;
    }

    if (cfg->prio > VTSS_PRIO_SUPER + 1) {
        VTSS_E("Illegal prio (%u)", cfg->prio);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    // On first alloc, enable AFI (if not already done)
    if (!vtss_state->afi.afi_ena) {
        if ((rc = vtss_state->afi.afi_enable(vtss_state)) != VTSS_RC_OK) {
            goto do_exit;
        }

        vtss_state->afi.afi_ena = 1;
    }

    // Allocate entry in DTI_TBL[].
    if ((rc = afi_dti_alloc(vtss_state, &dti_idx)) != VTSS_RC_OK) {
        goto do_exit;
    }

    *fastid = dti_idx;
    dti = &vtss_state->afi.dti_tbl[dti_idx];

    // Allocate entries in FRM_TBL[].
    // Here, we only allocate frame entries. Only when we get a request to start
    // the flow with a particular speed, will we allocate the delay entries.
    prev_frm_idx = -1;
    for (i = 0; (u32)i < cfg->frm_cnt; i++) {
        if ((rc = afi_frm_alloc(vtss_state, &frm_idx, 1, 0, prev_frm_idx)) != VTSS_RC_OK) {
            // Free allocated frame and delay entries in the FRM_TBL[]
            (void)afi_dti_frm_free(vtss_state, dti, FALSE);

            // Free allocated DTI
            (void)afi_dti_free(vtss_state, dti_idx);
            goto do_exit;
        }

        if (i == 0) {
            dti->first_frm_idx = frm_idx;
        }

        prev_frm_idx = frm_idx;
    }

    dti->state              = VTSS_AFI_ENTRY_STATE_STOPPED; // Entry allocated, but not yet started
    dti->port_no            = cfg->port_no;
    dti->masquerade_port_no = cfg->port_no == VTSS_PORT_NO_NONE ? cfg->masquerade_port_no : VTSS_PORT_NO_NONE;
    dti->prio               = cfg->prio;

do_exit:
    VTSS_I("Exit, fastid = %u, port_no = %d, rc = %u", *fastid, cfg->port_no, rc);
    VTSS_EXIT();
    return rc;
}

/*
 * vtss_afi_fast_inj_free()
 */
vtss_rc vtss_afi_fast_inj_free(const vtss_inst_t inst, vtss_afi_fastid_t fastid)
{
    vtss_state_t   *vtss_state;
    vtss_afi_dti_t *dti;
    vtss_rc        rc;
#if VTSS_OPT_TRACE
    vtss_port_no_t port_no = -2;
#endif

    VTSS_I("Enter, fastid = %u", fastid);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_dti_idx_chk(vtss_state, fastid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    dti = &vtss_state->afi.dti_tbl[fastid];

#if VTSS_OPT_TRACE
    port_no = dti->port_no;
#endif

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("Injection must be stopped before freeing");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    // Inject frames for removal - if any
    if (dti->frm_cnt) {
        if ((rc = vtss_state->afi.dti_frm_rm_inj(vtss_state, fastid)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

    // Free resources from FRM_TBL[]
    if ((rc = afi_dti_frm_free(vtss_state, dti, FALSE)) != VTSS_RC_OK) {
        goto do_exit;
    }

    // Free resources from DTI_TBL[]
    rc = afi_dti_free(vtss_state, fastid);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit, fastid = %u, port_no = %d", fastid, port_no);
    return rc;
}

/*
 * vtss_afi_fast_inj_frm_hijack()
 */
vtss_rc vtss_afi_fast_inj_frm_hijack(const vtss_inst_t inst, vtss_afi_fastid_t fastid, const vtss_afi_fast_inj_frm_cfg_t *const cfg)
{
    vtss_afi_dti_t *dti;
    vtss_state_t   *vtss_state;
    u32            total_cnt, frm_cnt, hijacked_cnt;
    vtss_rc        rc;

    if (cfg == NULL) {
        VTSS_E("cfg is NULL");
        return VTSS_RC_ERROR;
    }

    VTSS_I("Enter, fastid = %u", fastid);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_dti_idx_chk(vtss_state, fastid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    // Check to see that this function is not called more times than allowed to.
    dti = &vtss_state->afi.dti_tbl[fastid];

    if (dti->frm_cnt >= VTSS_AFI_FAST_INJ_FRM_CNT_MAX) {
        VTSS_E("Frame count is already at its max of %u", VTSS_AFI_FAST_INJ_FRM_CNT_MAX);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    VTSS_RC(afi_frm_idx_chk(vtss_state, dti->first_frm_idx));

    VTSS_RC(afi_dti_cnt_get(vtss_state, fastid, &total_cnt, &frm_cnt, &hijacked_cnt));

    if (hijacked_cnt != dti->frm_cnt) {
        VTSS_E("Internal error: hijacked_cnt = %u, dti->frm_cnt = %u", hijacked_cnt, dti->frm_cnt);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    if (dti->frm_cnt >= frm_cnt) {
        // The upcoming frame has no allocation in the frame table.
        VTSS_E("Only %u frame count entries were requested during vtss_afi_fast_inj_alloc(), but hijack is now invoked %u times", frm_cnt, dti->frm_cnt + 1);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    if ((rc = vtss_state->afi.dti_frm_hijack(vtss_state, fastid, cfg->frm_size)) != VTSS_RC_OK) {
        (void)afi_hijack_error_print(vtss_state);
    }

    if (dti->frm_cnt == frm_cnt) {
        // The CIL layer increases dti->frm_cnt, so if this is now equal to the
        // number of requested frames, we're done. In order to be able to remove
        // a flow without actually starting it, we must pseudo-start it with
        // some dummy configuration.
        vtss_afi_fast_inj_start_cfg_t pseudo_cfg;

        VTSS_I("Hijacking done. Pseudo-starting flow");
        VTSS_MEMSET(&pseudo_cfg, 0, sizeof(pseudo_cfg));
        pseudo_cfg.bps = VTSS_AFI_FAST_INJ_BPS_MIN;
        if ((rc = afi_dti_inj_start(vtss_state, fastid, &pseudo_cfg, FALSE)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit, fastid = %u", fastid);

    return rc;
}

/*
 * vtss_afi_fast_inj_start()
 */
vtss_rc vtss_afi_fast_inj_start(const vtss_inst_t inst, vtss_afi_fastid_t fastid, vtss_afi_fast_inj_start_cfg_t *const cfg)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if (cfg == NULL) {
        VTSS_E("cfg is NULL");
        return VTSS_RC_ERROR;
    }

    VTSS_I("Enter, ID = %u, bps = %" PRIu64 ", seq_cnt = %u", fastid, cfg->bps, cfg->seq_cnt);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_dti_idx_chk(vtss_state, fastid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    rc = afi_dti_inj_start(vtss_state, fastid, cfg, TRUE);

do_exit:
    VTSS_EXIT();

    VTSS_I("Exit(fastid = %u)", fastid);

    return rc;
}

/*
 * vtss_afi_fast_inj_stop()
 */
vtss_rc vtss_afi_fast_inj_stop(const vtss_inst_t inst, vtss_afi_fastid_t fastid)
{
    vtss_state_t   *vtss_state;
    vtss_afi_dti_t *dti;
    vtss_rc        rc;

    VTSS_I("Enter, fastid = %u", fastid);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_dti_idx_chk(vtss_state, fastid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    dti = &vtss_state->afi.dti_tbl[fastid];

    if (dti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        VTSS_E("DTI not started");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    rc = vtss_state->afi.dti_stop(vtss_state, fastid);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit, fastid = %u", fastid);
    return rc;
}

/*
 * vtss_afi_fast_inj_seq_cnt_get()
 */
vtss_rc vtss_afi_fast_inj_seq_cnt_get(const vtss_inst_t inst, vtss_afi_fastid_t fastid, u32 *const seq_cnt)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("Enter, fast = %u", fastid);

    if (seq_cnt == NULL) {
        VTSS_E("seq_cnt is NULL");
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_dti_idx_chk(vtss_state, fastid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    rc = vtss_state->afi.dti_cnt_get(vtss_state, fastid, seq_cnt);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit, fastid = %u", fastid);
    return rc;
}

/******************************************************************************/
//
// External AIL: Slow injections
//
/******************************************************************************/

/*
 * vtss_afi_slow_inj_alloc()
 */
vtss_rc vtss_afi_slow_inj_alloc(const vtss_inst_t                          inst,
                                const vtss_afi_slow_inj_alloc_cfg_t *const cfg,
                                vtss_afi_slowid_t                   *const slowid)
{
    vtss_state_t   *vtss_state;
    u32            tti_idx;
    i32            frm_idx;
    vtss_afi_tti_t *tti;
    vtss_rc        rc;

    VTSS_I("Enter(port_no = %d)", cfg->port_no);

    // Argument checks
    if (cfg == NULL || slowid == NULL) {
        VTSS_E("cfg or slowid is NULL");
        return VTSS_RC_ERROR;
    }

    *slowid = 0;

    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_none_check(inst, &vtss_state, cfg->port_no)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if (cfg->port_no == VTSS_PORT_NO_NONE) {
        // Masquerading. Check masquerade port
        if ((rc = vtss_port_no_check(vtss_state, cfg->masquerade_port_no)) != VTSS_RC_OK) {
            VTSS_E("When creating up-flows, fill in #masquerade_port_no member");
            goto do_exit;
        }
    }

    if (cfg->prio > VTSS_PRIO_SUPER + 1) {
        VTSS_E("Illegal prio (%u)", cfg->prio);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    // On first alloc, enable AFI and TTIs (if not already done)
    if (!vtss_state->afi.afi_ena) {
        if ((rc = vtss_state->afi.afi_enable(vtss_state)) != VTSS_RC_OK) {
            goto do_exit;
        }

        vtss_state->afi.afi_ena = 1;
    }

    if (!vtss_state->afi.tti_ena) {
        if ((rc = vtss_state->afi.ttis_enable(vtss_state)) != VTSS_RC_OK) {
            goto do_exit;
        }

        vtss_state->afi.tti_ena = 1;
    }

    // Allocate a TTI
    if ((rc = afi_tti_alloc(vtss_state, &tti_idx, 0 /* min_tti_idx */, VTSS_AFI_SLOW_INJ_CNT - 1 /* max_tti_idx */)) != VTSS_RC_OK) {
        goto do_exit;
    }

    *slowid = tti_idx;
    tti = &vtss_state->afi.tti_tbl[tti_idx];

    // Allocate a FRM
    if ((rc = afi_frm_alloc(vtss_state, &frm_idx, 0, 0, -1)) != VTSS_RC_OK) {
        (void)afi_tti_free(vtss_state, tti_idx);
        goto do_exit;
    }

    tti->state              = VTSS_AFI_ENTRY_STATE_STOPPED;
    tti->frm_idx            = frm_idx;
    tti->port_no            = cfg->port_no;
    tti->masquerade_port_no = cfg->port_no == VTSS_PORT_NO_NONE ? cfg->masquerade_port_no : VTSS_PORT_NO_NONE;
    tti->prio               = cfg->prio;

do_exit:
    VTSS_I("Exit. slowid = %u, port_no = %d, rc = %u", *slowid, cfg->port_no, rc);
    VTSS_EXIT();
    return rc;
}

/*
 * vtss_afi_slow_inj_free()
 */
vtss_rc vtss_afi_slow_inj_free(const vtss_inst_t inst, vtss_afi_slowid_t slowid)
{
    vtss_state_t   *vtss_state;
    vtss_afi_tti_t *tti;
    vtss_rc        rc;

    VTSS_I("Enter. slowid = %u", slowid);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_tti_idx_chk(vtss_state, slowid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    tti = &vtss_state->afi.tti_tbl[slowid];

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("Injection must be stopped before freeing");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    // Inject frame for removal - if any
    if (tti->hijacked) {
        if ((rc = vtss_state->afi.tti_frm_rm_inj(vtss_state, slowid)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

    // Free resources
    if ((rc = afi_frm_free(vtss_state, vtss_state->afi.tti_tbl[slowid].frm_idx)) != VTSS_RC_OK) {
        goto do_exit;
    }

    rc = afi_tti_free(vtss_state, slowid);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(slowid = %u)", slowid);
    return rc;
}

/*
 * vtss_afi_slow_inj_frm_hijack()
 */
vtss_rc vtss_afi_slow_inj_frm_hijack(const vtss_inst_t inst, vtss_afi_slowid_t slowid)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("Enter. slowid = %u", slowid);
    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_tti_idx_chk(vtss_state, slowid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = vtss_state->afi.tti_frm_hijack(vtss_state, slowid)) == VTSS_RC_OK) {
        // Frame is now transferred to H/W
        vtss_state->afi.tti_tbl[slowid].hijacked = TRUE;
    } else {
        (void)afi_hijack_error_print(vtss_state);
    }

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(slowid = %u)", slowid);
    return rc;
}

/*
 * vtss_afi_slow_inj_start()
 */
vtss_rc vtss_afi_slow_inj_start(const vtss_inst_t inst, vtss_afi_slowid_t slowid, const vtss_afi_slow_inj_start_cfg_t *const cfg)
{
    vtss_state_t   *vtss_state;
    vtss_afi_tti_t *tti;
    BOOL           do_config = 0;
    int            tick_idx;
    const u32      TIMER_LEN_MAX = (1 << VTSS_AFI_TTI_TBL_TIMER_LEN_WID) - 2;
    u32            timer_len_us;
    u32            timer_len_ticks;
    vtss_rc        rc;

    VTSS_I("Enter. slowid = %u", slowid);

    VTSS_ENTER();

    // Argument checking
    if (cfg == NULL) {
        VTSS_E("cfg is NULL");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_tti_idx_chk(vtss_state, slowid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if (cfg->fph == 0) {
        VTSS_E("cfg->fph == 0");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    if (cfg->jitter_mode > 3) {
        VTSS_E("cfg->jitter_mode=%u", cfg->jitter_mode);
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    tti = &vtss_state->afi.tti_tbl[slowid];

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        VTSS_E("TTI already started");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    timer_len_us = (3600LLU * 1000000LLU) / cfg->fph;

    VTSS_D("Got %" PRIu64 " fph, so searching for timer_len_us = %u", cfg->fph, timer_len_us);

    if (afi_tti_start_cfg_cmp(&tti->start_cfg, cfg) != 0) {
        afi_tti_start_cfg_cp(&tti->start_cfg, cfg);

        // Calculate tick_idx and timer_len based on cfg->fph
        if (cfg->jitter_mode != 0) {
            // Choose fastest possible tick to obtain largest set of values to randomize among
            BOOL tick_found = 0;
            for (tick_idx = 0; tick_idx < 8; tick_idx++) {
                u32 tick_len_us = vtss_state->afi.tick_len_us[tick_idx];
                timer_len_ticks = afi_div_round32(timer_len_us, tick_len_us);
                VTSS_D("Considering tick_idx = %u: timer_len_ticks = %u = timer_len_us (%u) / tick_len_us (%u) (TIMER_LEN_MAX = %u)", tick_idx, timer_len_ticks, timer_len_us, tick_len_us, TIMER_LEN_MAX);
                if (timer_len_ticks <= TIMER_LEN_MAX) {
                    VTSS_D("Got it");
                    vtss_state->afi.tti_tbl[slowid].timer_len = timer_len_ticks;
                    vtss_state->afi.tti_tbl[slowid].tick_idx  = tick_idx;
                    tick_found = 1;
                    break;
                }

                VTSS_D("Nah, next");
            }

            if (!tick_found) {
                VTSS_E("No tick found for fph = %" PRIu64, cfg->fph);
                rc = VTSS_RC_ERROR;
                goto do_exit;
            }
        } else {
            // Choose slowest possible tick resulting in timer_len_ticks >= 8.
            // This reduces the frequency with which TICK_CNT shall be decremented
            // (thus making the walk-through of TTI_TBL as fast as possible)
            // while ensuring some room for randomization of time to first injection.
            BOOL tick_found = 0;

            for (tick_idx = 7; tick_idx >= 0; tick_idx--) {
                BOOL timer_prec_ok;
                u32 tick_len_us = vtss_state->afi.tick_len_us[tick_idx];
                timer_len_ticks = afi_div_round32(timer_len_us, tick_len_us);

                // Check that resulting timer is correct within 5%
                // If not within 5% then a faster tick must be used.
                timer_prec_ok = afi_timer_prec_ok(timer_len_us, timer_len_ticks * tick_len_us, 5);

                VTSS_D("Considering tick_idx = %u: timer_len_ticks = %u = timer_len_us (%u) / tick_len_us (%u) (timer_prec_ok = %d)", tick_idx, timer_len_ticks, timer_len_us, tick_len_us, timer_prec_ok);

                if (timer_len_ticks >= 8 && timer_prec_ok) {
                    VTSS_D("Got it");
                    vtss_state->afi.tti_tbl[slowid].timer_len = timer_len_ticks;
                    vtss_state->afi.tti_tbl[slowid].tick_idx  = tick_idx;
                    tick_found = 1;
                    break;
                }

                VTSS_D("Nah, next");
            }

            if (!tick_found) {
                VTSS_E("No tick found for fph = %" PRIu64, cfg->fph);
                rc = VTSS_RC_ERROR;
                goto do_exit;
            }
        }

        do_config = 1;
    } else {
        // Configuration unchanged => Just start TTI
        do_config = 0;
    }

    rc = vtss_state->afi.tti_start(vtss_state, slowid, do_config);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(slowid = %u)", slowid);
    return rc;
}

/*
 * vtss_afi_slow_inj_stop()
 */
vtss_rc vtss_afi_slow_inj_stop(const vtss_inst_t inst, vtss_afi_slowid_t slowid)
{
    vtss_state_t   *vtss_state;
    vtss_afi_tti_t *tti;
    vtss_rc        rc;

    VTSS_I("Enter. slowid = %u", slowid);

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    if ((rc = afi_tti_idx_chk(vtss_state, slowid)) != VTSS_RC_OK) {
        goto do_exit;
    }

    tti = &vtss_state->afi.tti_tbl[slowid];

    if (tti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        VTSS_E("TTI not started");
        rc = VTSS_RC_ERROR;
        goto do_exit;
    }

    rc = vtss_state->afi.tti_stop(vtss_state, slowid);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(slowid = %u)", slowid);
    return rc;
}

/******************************************************************************/
//
// External AIL: Other functions
//
/******************************************************************************/

/*
 * vtss_afi_port_start()
 */
vtss_rc vtss_afi_port_start(const vtss_inst_t inst, vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_I("Enter(port_no = %u)", port_no);
    VTSS_ENTER();

    if ((rc = vtss_inst_port_no_none_check(inst, &vtss_state, port_no)) != VTSS_RC_OK) {
        goto do_exit;
    }

    rc = vtss_state->afi.port_admin_start(vtss_state, port_no);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(port_no = %u)", port_no);
    return rc;
}

/*
 * vtss_afi_port_stop()
 */
vtss_rc vtss_afi_port_stop(const vtss_inst_t inst, vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    VTSS_I("Enter(port_no = %u)", port_no);

    if ((rc = vtss_inst_port_no_none_check(inst, &vtss_state, port_no)) != VTSS_RC_OK) {
        goto do_exit;
    }

    rc = vtss_state->afi.port_admin_stop(vtss_state, port_no);

do_exit:
    VTSS_EXIT();
    VTSS_I("Exit(port_no = %u)", port_no);
    return rc;
}

/*
 * vtss_afi_debug_print()
 */
void vtss_afi_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    vtss_afi_state_t *afi = &vtss_state->afi;
    vtss_afi_frm_t   *frm;
    vtss_afi_dti_t   *dti;
    vtss_afi_tti_t   *tti;
    vtss_port_no_t   port_no;
    u32              res_idx;
    i32              frm_idx;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_AFI)) {
        return;
    }

    pr("TTI Table\n");
    pr("#    Port Dir  Prio Frames/hour TickIdx TmrLen Jit FrmTblIdx TickCnt User State Driver State\n");
    pr("---- ---- ---- ---- ----------- ------- ------ --- --------- ------- ---------- ------------\n");

    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->tti_tbl); res_idx++) {
        if (afi_res_is_free(afi->ttis_alloced, res_idx)) {
            continue;
        }

        tti = &afi->tti_tbl[res_idx];
        pr("%4u %4d %4s %4u %11" PRIu64 " %7u %6u %3u %9i %7u %10s %12s\n", res_idx,
           tti->port_no == VTSS_PORT_NO_NONE ? tti->masquerade_port_no : tti->port_no,
           tti->port_no == VTSS_PORT_NO_NONE ? "Up" : "Down",
           tti->prio, tti->start_cfg.fph, tti->tick_idx,
           tti->timer_len, tti->jitter, tti->frm_idx, tti->tick_cnt,
           afi_state_to_str(tti->state), tti->paused ? "Paused" : "Running");
    }

    pr("\nDTI Table\n");
    pr("#  Port Dir  Prio FrmInjCnt  User State Driver State Indices into Frame Table\n");
    pr("-- ---- ---- ---- ---------- ---------- ------------ ------------------------\n");

    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->dti_tbl); res_idx++) {
        if (afi_res_is_free(afi->dtis_alloced, res_idx)) {
            continue;
        }

        dti = &afi->dti_tbl[res_idx];
        pr("%2u %4d %4s %4u %10u %10s %12s", res_idx,
           dti->port_no == VTSS_PORT_NO_NONE ? dti->masquerade_port_no : dti->port_no,
           dti->port_no == VTSS_PORT_NO_NONE ? "Up" : "Down",
           dti->prio, dti->frm_inj_cnt,
           afi_state_to_str(dti->state), dti->paused ? "Paused" : "Running");
        for (frm_idx = dti->first_frm_idx; frm_idx != 0; frm_idx = afi->frm_tbl[frm_idx].next_ptr) {
            pr(" %i", frm_idx);
        }

        pr("\n");
    }

    pr("\nFrame Table\n");
    pr("#    Type  FrmSz InjCnt Delay     \n");
    pr("---- ----- ----- ------ ----------\n");

    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->frm_tbl); res_idx++) {
        if (afi_res_is_free(afi->frms_alloced, res_idx)) {
            continue;
        }

        frm = &afi->frm_tbl[res_idx];
        if (frm->entry_type) {
            pr("%4u Delay %5s %6s %10u\n", res_idx, "N/A",                      "N/A",                       frm->frm_delay.delay.delay);
        } else {
            pr("%4u Frame %5u %6u %10s\n", res_idx, frm->frm_delay.frm.frm_size, frm->frm_delay.frm.inj_cnt, "N/A");
        }
    }

    pr("\nTTI Ticks\n");
    pr("#   TickLen [us]\n");
    pr("--- ------------\n");
    for (res_idx = 0; res_idx < VTSS_ARRSZ(afi->tick_len_us); res_idx++) {
        pr("%3u %12u\n", res_idx, afi->tick_len_us[res_idx]);
    }

    pr("\nPort Table\n");
    pr("Port Link\n");
    pr("---- ----\n");
    for (port_no = 0; port_no < VTSS_ARRSZ(vtss_state->afi.port_tbl); port_no++) {
        vtss_afi_port_t *afi_port = &vtss_state->afi.port_tbl[port_no];
        pr("%4d %4s\n", port_no == VTSS_ARRSZ(vtss_state->afi.port_tbl) - 1 ? (u32)(-1) : port_no, afi_port->link ? "Yes" : "No");
    }

    pr("\n");
}

/*
 * vtss_afi_inst_create()
 *
 * Instance creation and initialization
 */
vtss_rc vtss_afi_inst_create(vtss_state_t *vtss_state)
{
    vtss_afi_state_t *state = &vtss_state->afi;
    vtss_port_no_t   port_no;

    // Set chip default values
    for (port_no = 0; port_no < VTSS_ARRSZ(state->port_tbl); port_no++) {
        state->port_tbl[port_no].frm_out_max = VTSS_AFI_FRM_OUT_MAX_DEF;
    }

    return VTSS_RC_OK;
}

#endif /* defined(VTSS_AFI_V2) */
#endif /* defined(VTSS_FEATURE_AFI_SWC) */

