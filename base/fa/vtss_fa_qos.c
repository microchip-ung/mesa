/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_QOS)

/* Calculate Layer 0 Scheduler Element when using normal hierarchy */
#define FA_HSCH_L0_SE(port, queue) ((64 * port) + (8 * queue))

#define LB_PUP_TOKEN_MAX              (0x1FFF-1)        /* The MAX number of tokens to add each update. The value 0x1FFF is reserved for permanently open buckets */
#define LB_PUP_INTERVAL_MAX           0xFFFFF           /* The MAX updating interval */
#define LB_TOKENS_PER_FRAME_MAX       0x1FFF            /* The MAX frame size */
#define LB_THRES_MAX                  0x3FF             /* The MAX THRES value */
#define LB_THRES_SHIFT_MAX            0x1F              /* The MAX THRES_SHIFT value */
#define LB_XLB_NEXT_LBGRP_MAX         0x0F              /* The MAX LBGRP value */
#define LB_THRES_HYS_MIN              (LB_THRES_MAX+1)  /* The minimum bucket open hysteresis */
#define LB_2CYCLES_TYPE2_THRES_OFFSET 13                /* FA specific value */

static u64 lb_clk_in_hz_get(vtss_state_t *vtss_state)
{
    u32  clk_cfg, clk_period_in_100ps;
    u64  lb_clk_in_hz;

    /* Read the nominal system clock period length in 100 ps */
    REG_RD(VTSS_HSCH_SYS_CLK_PER, &clk_cfg);
    clk_period_in_100ps = VTSS_X_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(clk_cfg);
    lb_clk_in_hz = 10*1000*1000 / clk_period_in_100ps;
    lb_clk_in_hz *= 1000;
    return (lb_clk_in_hz);
}

static u64 lb_group_lb_min_rate_calc(u64 lb_clk_in_hz, u32 pup_interval)
{
    return VTSS_DIV64((u64)(1 * lb_clk_in_hz * 8), (u64)pup_interval);
}

static u64 lb_group_lb_max_rate_calc(u32 bs, u64 lb_clk_in_hz, u32 pup_interval)
{
    u32 max_tokens;

    if (pup_interval == 0) {
        VTSS_D("pup_interval is zero");
        return (0xFFFFFFFFFFFFFFFF);
    }

    max_tokens = bs;    /* Cannot add more tokens than the burst size */

    // Saturate max tokens
    if (max_tokens > LB_PUP_TOKEN_MAX) {
        VTSS_N("Saturating maximum tokens per PUP to group's limit of %u tokens.  Requested BS %u", LB_PUP_TOKEN_MAX, bs);
        max_tokens = LB_PUP_TOKEN_MAX;
    }
    return VTSS_DIV64(((u64)max_tokens * lb_clk_in_hz * 8), (u64)pup_interval);
}

static u64 lb_group_lb_pup_token_calc(u64 ir_in_bps, u64 lb_clk_in_hz, u32 pup_interval)
{
    /* Calculate the number of tokens required for this IR in this group (PUP_INTERVAL) */
    /* PUP_TOKEN = (RATE * PUP_INTERVAL) / (clk_frequence * 8) */
    return VTSS_DIV64_ROUND_UP((ir_in_bps * (u64)pup_interval), (lb_clk_in_hz * 8));
}

static i32 lb_prev_lb_set_get(vtss_state_t *vtss_state, u32 grp_idx, u32 lb_set_idx)
{
    i32 i;

    for (i = (lb_set_idx - 1); (i >= 0); i--) {     /* LBs are ordered in a group so that the next LB is always with higher index */
        if (vtss_state->qos.lb_set_grp_idx[i] == grp_idx) {
            break;
        }
    }
    return i;
}

/* ir and max_ir in 1000 bit/s or f/s */
static vtss_rc lb_config(vtss_state_t *vtss_state, u32 grp_idx, u32 set_idx, u32 lb_idx, u32 ir, u32 max_ir, u32 bs, u32 bs_hyst, BOOL cf, BOOL frame_rate)
{
    vtss_qos_lb_group_t *group;
    u32                 pup_tokens, max_pup_tokens, bs_in_bytes, bs_hyst_in_bytes, thres, hyst, inh_mode;
    u64                 ir_in_bps, max_ir_in_bps, lb_clk_in_hz;

    VTSS_I("Enter grp_idx %u, set_idx %u lb_idx %u ir %u", grp_idx, set_idx, lb_idx, ir);

    if (ir == 0) {
        VTSS_D("No IR was requested");
        return(VTSS_RC_OK);
    }
    if (grp_idx >= LB_GROUP_CNT) {
        VTSS_D("Invalid LB group index %u", grp_idx);
        return(VTSS_RC_ERROR);
    }
    group = &vtss_state->qos.lb_groups[grp_idx];

    ir_in_bps = (u64)ir * 1000;
    max_ir_in_bps = (u64)max_ir * 1000;
    bs_in_bytes = bs;
    bs_hyst_in_bytes = bs_hyst;
    if (frame_rate) {
       ir_in_bps = (u64)ir * (u64)group->frame_size * 8;
       max_ir_in_bps = (u64)max_ir * (u64)group->frame_size * 8;
       bs_in_bytes = bs * group->frame_size;
       bs_hyst_in_bytes = bs_hyst * group->frame_size;
    }

    /* Get the system clock in Hz */
    lb_clk_in_hz = lb_clk_in_hz_get(vtss_state);

    /* Calculate the number of tokens required for this IR in this group (PUP_INTERVAL) */
    pup_tokens = lb_group_lb_pup_token_calc(ir_in_bps, lb_clk_in_hz, group->pup_interval);

    // The following should NEVER trigger! The checking was done when selecting group.
    if ((pup_tokens == 0) && (ir != 0)) {
        VTSS_D("Bucket %u cannot be added to group %u. Check flow parameters.", set_idx, grp_idx);
        return(VTSS_RC_ERROR);
    }
    if (pup_tokens > LB_PUP_TOKEN_MAX) {
        VTSS_D("Calculated pup tokens %u value exceeds max value", pup_tokens);
        return(VTSS_RC_ERROR);
    }

    /* Calculate the number of tokens required for this MAX IR in this group (PUP_INTERVAL) */
    max_pup_tokens = lb_group_lb_pup_token_calc(max_ir_in_bps, lb_clk_in_hz, group->pup_interval);

    // The following should NEVER trigger! The checking was done when selecting group.
    if ((max_pup_tokens == 0) && (max_ir != 0)) {
        VTSS_D("Bucket %u cannot be added to group %u. Check flow parameters.", set_idx, grp_idx);
        return(VTSS_RC_ERROR);
    }
    if (max_pup_tokens > LB_PUP_TOKEN_MAX) {
        VTSS_D("Calculated pup tokens %u value exceeds max value", max_pup_tokens);
        return(VTSS_RC_ERROR);
    }

    // Calculate the bucket threshold - that is the burst size
    // The threshold register unit is configured to be min_burst
    thres = VTSS_DIV_ROUND_UP(bs_in_bytes, group->min_burst);
    if (bs_in_bytes != (thres * group->min_burst)) {
        VTSS_D("Requested BS %u was not achieved BS %u.  thres %u  min_burst %u", bs_in_bytes, (thres * group->min_burst), thres, group->min_burst);
    }

    // Calculate bucket hysteresis
    // The hysteresis register unit is configured to be min_burst
    hyst = VTSS_DIV_ROUND_UP(bs_hyst_in_bytes, group->min_burst);
    if (bs_hyst_in_bytes != (hyst * group->min_burst)) {
        VTSS_D("Requested BS hysteresis %u was not achieved BS hysteresis %u.", bs_hyst_in_bytes, (hyst * group->min_burst));
    }

    // Calculate the Inherent mode
    inh_mode = 0;
    if (cf && (lb_idx == 1)) {    /* This is EIR LB and Coupling Flag */
        inh_mode = 2;
    }

    REG_WR(VTSS_ANA_AC_SDLB_PUP_TOKENS(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(pup_tokens));
    REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(max_pup_tokens), VTSS_M_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX);
    REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES(thres), VTSS_M_ANA_AC_SDLB_THRES_THRES);
    REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES_HYS(hyst), VTSS_M_ANA_AC_SDLB_THRES_THRES_HYS);
    REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_INH_MODE(inh_mode), VTSS_M_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX);

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

/* Find best group for leaky bucket                              */
/* Choose the LB Group with the longest PUP_INTERVAL, that can   */
/* support lb_rate while adding at most lb_thres tokens per PUP. */
/* ir in 1000 bit/s or f/s */
static vtss_rc lb_group_find(vtss_state_t *vtss_state, u32 ir, u32 bs, u32 bs_hyst, BOOL frame_rate, u32 *idx)
{
    i32                 i;
    u32                 pup_tokens, thres, bs_in_bytes, bs_hyst_in_bytes;
    u64                 ir_in_bps, min_rate, max_rate, lb_clk_in_hz;
    vtss_qos_lb_group_t *group;

    VTSS_D("Enter  ir %u  bs %u  frame_rate %u", ir, bs, frame_rate);

    ir_in_bps = (u64)ir * 1000;
    bs_in_bytes = bs;
    bs_hyst_in_bytes = bs_hyst;

    /* Get the system clock in Hz */
    lb_clk_in_hz = lb_clk_in_hz_get(vtss_state);

    for (i = *idx; (i >= 0) && (i < LB_GROUP_CNT); i--) {
        group = &vtss_state->qos.lb_groups[i];

        // In case of frame rate enabled, convert burst size from number of frames to bytes and information rate from f/s to 1000 bit/s
        if (frame_rate) {
            bs_in_bytes = bs * group->frame_size;
            bs_hyst_in_bytes = bs_hyst * group->frame_size;
            ir_in_bps = (u64)ir * 8 * (u64)group->frame_size;
        }

        if (bs_hyst == LB_THRES_HYS_MIN) {  /* Request for the group minimum burst size as hysteresis */
            bs_hyst_in_bytes = group->min_burst;
        }

        /* Check if the number of LB in the group exceeds PUP_INTERVAL/4-1. Rule I in DS1110 */
        if ((group->lb_set_count + 1) > ((group->pup_interval / 4) - 1)) {
            VTSS_D("Group %u.  Violation of Rule I.  LB count %u  PUP_INTERVAL %u.", i, group->lb_set_count, group->pup_interval);
            continue;
        }

        // Check if the burst size and hyst size is in a valid range
        if ((bs_in_bytes < group->min_burst) || ((bs_hyst_in_bytes > 0) && (bs_hyst_in_bytes < group->min_burst))) {
            VTSS_D("Group %u.  Burst size %u or non-zero hysteresis %u is smaller than group minimum burst %u", i, bs, bs_hyst, group->min_burst);
            continue;
        }

        // Calculate maximum feasible rate (bps) and minimum rate (bps) in this group for this LB.
        max_rate = lb_group_lb_max_rate_calc(bs, lb_clk_in_hz, group->pup_interval);
        min_rate = lb_group_lb_min_rate_calc(lb_clk_in_hz, group->pup_interval);

        // Check ir_in_bps against maximum and minimum feasible rate
        if ((ir_in_bps != 0) && (ir_in_bps > max_rate || ir_in_bps < min_rate)) {
            VTSS_D("Group %u.  Information rate %" PRIu64 " is outside the group limits (min_rate %" PRIu64 " - max_rate %" PRIu64 ")", i, ir_in_bps, min_rate, max_rate);
            continue;
        }

        /* Check if PUP_TOKEN value fit into register */
        if ((pup_tokens = lb_group_lb_pup_token_calc(ir_in_bps, lb_clk_in_hz, group->pup_interval)) > LB_PUP_TOKEN_MAX) {
            VTSS_D("Group %u.  Calculated pup tokens %u value exceeds max value for rate %" PRIu64 "", i, pup_tokens, ir_in_bps);
            continue;
        }

        /* Check if THRES value fit into register */
        if ((thres = VTSS_DIV_ROUND_UP(bs_in_bytes, group->min_burst)) > LB_THRES_MAX) {
            VTSS_D("Group %u.  Calculated bucket threshold %u value exceeds max value", i, thres);
            continue;
        }

        /* Check if THRES_HYST value fit into register */
        if ((thres = VTSS_DIV_ROUND_UP(bs_hyst_in_bytes, group->min_burst)) > LB_THRES_MAX) {
            VTSS_D("Group %u.  Calculated bucket threshold hysteresis %u value exceeds max value", i, thres);
            continue;
        }

        *idx = i;

        VTSS_D("Exit. Group %u was found for Information rate %" PRIu64 " and burst size %u.   Group min_burst %u  min_rate %" PRIu64 "  max_rate %" PRIu64 "  pup_interval %u", i, ir_in_bps, bs, group->min_burst, min_rate, max_rate, group->pup_interval);
        return VTSS_RC_OK;
    }

    VTSS_D("Exit. FAILURE: No group was found for Information rate %u and burst size %u", ir, bs);
    return VTSS_RC_ERROR;
}


/* A LB group will be configured that supports a LB with the rate 'max_rate' and the burst size 'min_burst' */
/* The 'min_burst' will give the burst size configuration unit. The combination of 'max_rate' and 'min_burst' will give the update interval of this group */
/* The update interval for the group dictates the minimum rate for the group */
/* It is possible to add LB with higher rate but then the bust size must also be higher */ 
/* max_rate in bps */
static vtss_rc lb_group_add(vtss_state_t *vtss_state, u64 max_rate, u32 min_burst, u32 frame_size, u32 idx)
{
    vtss_qos_lb_group_t *group;
    u32                 power = 0, mask = 0x01, thres_shift;
    u64                 pup_interval, max_token, lb_clk_in_hz;

    VTSS_D("Enter  idx %u", idx);

    if (idx >= LB_GROUP_CNT) {
        VTSS_E("Invalid LB group index %u", idx);
        return(VTSS_RC_ERROR);
    }
    group = &vtss_state->qos.lb_groups[idx];

    if (frame_size > LB_TOKENS_PER_FRAME_MAX) {
        VTSS_E("Invalid frame_size %u", frame_size);
        return(VTSS_RC_ERROR);
    }

    if (min_burst == 0) {
        VTSS_E("Invalid min_burst is zero");
        return(VTSS_RC_ERROR);
    }

    /* min_burst must be in powers of 2 */
    /* This is because the burst size register unit is in powers of 2 and the minimum value is 1 */
    while ((min_burst & mask) == 0) {
        power++;
        mask <<= 1;
    };
    if ((min_burst & ~mask) != 0) {
        VTSS_E("Invalid min_burst %u is not power of two", min_burst);
        return(VTSS_RC_ERROR);
    }

    /* Requested min_burst is evaluated to be equal to 2^power. */
    /* The bust size register unit is 2^(LB_2CYCLES_TYPE2_THRES_OFFSET - THRES_SHIFT) */
    /* Then it can be calculated that THRES_SHIFT = LB_2CYCLES_TYPE2_THRES_OFFSET - power */
    /* This means that the burst size register is configured in min_burst units */
    thres_shift = LB_2CYCLES_TYPE2_THRES_OFFSET - power;
    if (thres_shift > LB_THRES_SHIFT_MAX) {
        VTSS_E("Parameter min_burst %u calculate invalid THRES_SHIFT %u", min_burst, thres_shift);
        return(VTSS_RC_ERROR);
    }

    /* Get the system clock in Hz */
    lb_clk_in_hz = lb_clk_in_hz_get(vtss_state);

    /* Calculate the highest possible PUP_INTERVAL for the max_rate rate with the min_burst burst size. */
    /* The highest possible PUP_TOKENS value is equal to the bust size - in this case the min_burst we promised to support at the max_rate */
    max_token = (min_burst > LB_PUP_TOKEN_MAX) ? LB_PUP_TOKEN_MAX : min_burst;
    pup_interval = VTSS_DIV64((8 * lb_clk_in_hz * max_token), max_rate);
    if (pup_interval > LB_PUP_INTERVAL_MAX) {
        pup_interval = LB_PUP_INTERVAL_MAX;
    }
    if (pup_interval == 0) {
        pup_interval = 1;
    }

    /* Test passed, add group */
    group->min_burst = min_burst;         /* This is the minimum burst size - the bust size register configuration unit */
    group->pup_interval = (u32)pup_interval;
    group->frame_size = frame_size;

    /* Configure group */
    REG_WR(VTSS_ANA_AC_SDLB_PUP_INTERVAL(idx), VTSS_F_ANA_AC_SDLB_PUP_INTERVAL_PUP_INTERVAL((u32)pup_interval));
    REG_WR(VTSS_ANA_AC_SDLB_FRM_RATE_TOKENS(idx), VTSS_F_ANA_AC_SDLB_FRM_RATE_TOKENS_FRM_RATE_TOKENS(frame_size));
    REG_WR(VTSS_ANA_AC_SDLB_LBGRP_MISC(idx), VTSS_F_ANA_AC_SDLB_LBGRP_MISC_THRES_SHIFT(thres_shift));

    VTSS_D("Exit");

    return(VTSS_RC_OK);
}

static vtss_rc lb_group_lb_set_remove(vtss_state_t *vtss_state, u32 lb_set_idx)
{
    vtss_qos_lb_group_t *group;
    u32                 reg, nxt_idx, grp_idx;
    i32                 prev_idx;

    VTSS_D("Enter  lb_set_idx %u", lb_set_idx);

    if (lb_set_idx >= LB_SET_CNT) {
        VTSS_D("Invalid LB set index %u", lb_set_idx);
        return(VTSS_RC_ERROR);
    }

    if ((grp_idx = vtss_state->qos.lb_set_grp_idx[lb_set_idx]) < LB_GROUP_CNT) {
        /* The LB set is in a group - remove it */
        VTSS_D("LB %u is removed from group %u", lb_set_idx, grp_idx);
        group = &vtss_state->qos.lb_groups[grp_idx];
        VTSS_D("count: %u", group->lb_set_count);
        group->lb_set_count--;

        if (group->lb_set_count == 0) {   /* Check if this LB is it the last LB set in the group */
            VTSS_D("Disable Group");
            REG_WRM(VTSS_ANA_AC_SDLB_PUP_CTRL(grp_idx), VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_ENA(0), VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_ENA);   /* Group disable */
        } else {
            /* Find the previous LB in group - the one with lower index */
            prev_idx = lb_prev_lb_set_get(vtss_state, grp_idx, lb_set_idx);

            REG_RD(VTSS_ANA_AC_SDLB_XLB_NEXT(lb_set_idx), &reg);
            nxt_idx = VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(reg);      /* Next LB is take from this LB set */
            nxt_idx = (nxt_idx == lb_set_idx) ? prev_idx : nxt_idx;     /* If this LB is pointing to itself then it is last so previous LB is now last pointing to itself */

            VTSS_D("Remove LB %u  prev_idx %i  nxt_idx %u", lb_set_idx, prev_idx, nxt_idx);
            if (prev_idx < 0) { /* No previous LB was found */
                REG_WR(VTSS_ANA_AC_SDLB_XLB_START(grp_idx), VTSS_F_ANA_AC_SDLB_XLB_START_LBSET_START(nxt_idx));   /* Group is pointing to next LB */
            } else { /* Previous LB was found */
                REG_WRM(VTSS_ANA_AC_SDLB_XLB_NEXT(prev_idx),
                        VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(nxt_idx), VTSS_M_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT); /* Previous LB is pointing to next LB */
            }

            REG_WRM(VTSS_ANA_AC_SDLB_PUP_CTRL(grp_idx),     /* The LB update delta time must be recalculated */
                    VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(group->pup_interval / group->lb_set_count),
                    VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT);
        }
    }
    /* Disable policer */
    REG_WR(VTSS_ANA_AC_SDLB_PUP_TOKENS(lb_set_idx, 0), VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(0x1fff));
    REG_WR(VTSS_ANA_AC_SDLB_PUP_TOKENS(lb_set_idx, 1), VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(0x1fff));
    REG_WRM(VTSS_ANA_AC_SDLB_XLB_NEXT(lb_set_idx), VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(lb_set_idx), VTSS_M_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT); /* Point to self */
    vtss_state->qos.lb_set_grp_idx[lb_set_idx] = LB_GROUP_CNT;     /* This LB set is no longer in a group */

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static vtss_rc lb_group_lb_set_add(vtss_state_t *vtss_state, u32 grp_idx, u32 lb_set_idx, vtss_dlb_policer_conf_t *conf)
{
    u32                  reg, sum, nxt_idx, i;
    i32                  prev_idx;
    vtss_qos_lb_group_t  *group, *grp;

    VTSS_D("Enter  grp_idx %u  lb_set_idx %u", grp_idx, lb_set_idx);

    if (lb_set_idx >= LB_SET_CNT) {
        VTSS_D("Invalid LB set index %u", lb_set_idx);
        return(VTSS_RC_ERROR);
    }

    if (vtss_state->qos.lb_set_grp_idx[lb_set_idx] < LB_GROUP_CNT) {
        /* The LB is already in a group - cannot be added */
        VTSS_D("LB %u is already in a group %u", lb_set_idx, vtss_state->qos.lb_set_grp_idx[lb_set_idx]);
        return(VTSS_RC_ERROR);
    }

    if (grp_idx >= LB_GROUP_CNT) {
        VTSS_D("Invalid LB group index %u", grp_idx);
        return(VTSS_RC_ERROR);
    }
    group = &vtss_state->qos.lb_groups[grp_idx];

    group->lb_set_count++;  /* Increment the number of LB in the group */

    /* Check if all LB in all groups can be updated within the configured PUP_INTERVALS. Rule II in DS1110 */
    for (i = 0, sum = 0; i < LB_GROUP_CNT; ++i) {
        grp = &vtss_state->qos.lb_groups[i];
        if (grp->pup_interval > 1) {
            sum = sum + (grp->lb_set_count / (grp->pup_interval / 2));
        }
    }
    if (sum >= 1) {
        VTSS_D("Cannot add LB %u to any group. Violation of Rule II.", lb_set_idx);
        group->lb_set_count -= 1;
        return(VTSS_RC_ERROR);
    }

    /* Configure the LB */
    /* Configure the per CIR and EIR related */
    VTSS_RC(lb_config(vtss_state, grp_idx, lb_set_idx, 0, conf->cir, 0, conf->cbs, group->min_burst, conf->cf, FALSE));  /* CIR */
    VTSS_RC(lb_config(vtss_state, grp_idx, lb_set_idx, 1, conf->eir, 0, conf->ebs, group->min_burst, conf->cf, FALSE));  /* EIR */

    /* Configure the CIR and EIR common */
    REG_WRM(VTSS_ANA_AC_SDLB_DLB_MISC(lb_set_idx),
            VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA(0) |
            VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ(conf->line_rate ? 20 : 0),
            VTSS_M_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA |
            VTSS_M_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ);
    REG_WRM(VTSS_ANA_AC_SDLB_DLB_CFG(lb_set_idx),
            VTSS_F_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL(conf->cm ? 0 : 3) |
            VTSS_F_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL(1) |
            VTSS_F_ANA_AC_SDLB_DLB_CFG_DLB_MODE(0),
            VTSS_M_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL |
            VTSS_M_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL |
            VTSS_M_ANA_AC_SDLB_DLB_CFG_DLB_MODE);

    /* Insert the LB into the group */
    if (group->lb_set_count == 1) {   /* Check if it is the first LB in the group? */
        /* Write group LB start, set PUP_ENA, write PUP_LB_DT */
        VTSS_D("Enable Group");
        REG_WR(VTSS_ANA_AC_SDLB_XLB_NEXT(lb_set_idx),
               (VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(lb_set_idx) | VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBGRP(grp_idx))); /* This LB is pointing to this LB - end of list */
        REG_WR(VTSS_ANA_AC_SDLB_XLB_START(grp_idx), VTSS_F_ANA_AC_SDLB_XLB_START_LBSET_START(lb_set_idx));         /* Group is pointing to this LB */
        REG_WRM(VTSS_ANA_AC_SDLB_PUP_CTRL(grp_idx), VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(0), VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT); /* LB update delta time is zero - This is take from TCL script */
        REG_WRM(VTSS_ANA_AC_SDLB_PUP_CTRL(grp_idx), VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_ENA(1), VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_ENA);     /* Group enable */
    } else {
        /* Find the previous LB in group - the one with lower index */
        prev_idx = lb_prev_lb_set_get(vtss_state, grp_idx, lb_set_idx);
        if (prev_idx < 0) { /* No previous LB was found */
            REG_RD(VTSS_ANA_AC_SDLB_XLB_START(grp_idx), &reg)
            nxt_idx = VTSS_X_ANA_AC_SDLB_XLB_START_LBSET_START(reg);    /* Next LB is take from the group */
            REG_WR(VTSS_ANA_AC_SDLB_XLB_NEXT(lb_set_idx),
                (VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(nxt_idx) | VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBGRP(grp_idx))); /* This LB is pointing to next LB */
            REG_WR(VTSS_ANA_AC_SDLB_XLB_START(grp_idx), VTSS_F_ANA_AC_SDLB_XLB_START_LBSET_START(lb_set_idx))    /* Group is pointing to this LB */
        } else { /* Previous LB was found */
            REG_RD(VTSS_ANA_AC_SDLB_XLB_NEXT(prev_idx), &reg)
            nxt_idx = VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(reg);      /* Next LB is take from previous LB */
            nxt_idx = (nxt_idx == prev_idx) ? lb_set_idx : nxt_idx;     /* If previous LB is pointing to itself then it is last so this LB is now last pointing to itself */
            REG_WR(VTSS_ANA_AC_SDLB_XLB_NEXT(lb_set_idx),
                (VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(nxt_idx) | VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBGRP(grp_idx))); /* This LB is pointing to next LB */
            REG_WRM(VTSS_ANA_AC_SDLB_XLB_NEXT(prev_idx),
                    VTSS_F_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(lb_set_idx), VTSS_M_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT)  /* Previous LB is pointing to this LB */
        }
        REG_WRM(VTSS_ANA_AC_SDLB_PUP_CTRL(grp_idx),     /* The LB update delta time must be recalculated */
                VTSS_F_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(group->pup_interval / group->lb_set_count),
                VTSS_M_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT);
    }

    vtss_state->qos.lb_set_grp_idx[lb_set_idx] = grp_idx;   /* This LB set is now in a group */

    VTSS_D("Exit");

    return(VTSS_RC_OK);
}

/* - CIL functions ------------------------------------------------- */

static vtss_rc fa_qos_lb_init(vtss_state_t *vtss_state)
{
    u32 i;

    VTSS_D("Enter");

    /* Add groups. The max_rate parameter is in bps */
    /*                          max_rate,  min_burst, frame_size, grp_idx */
    lb_group_add(vtss_state, 25000000000,     8192/1,         64,       0);    /*  25 G */
    lb_group_add(vtss_state, 15000000000,     8192/1,         64,       1);    /*  15 G */
    lb_group_add(vtss_state, 10000000000,     8192/1,         64,       2);    /*  10 G */
    lb_group_add(vtss_state,  5000000000,     8192/1,         64,       3);    /*   5 G */
    lb_group_add(vtss_state,  2500000000,     8192/1,         64,       4);    /* 2.5 G */
    lb_group_add(vtss_state,  1000000000,     8192/2,         64,       5);    /*   1 G */
    lb_group_add(vtss_state,   500000000,     8192/2,         64,       6);    /* 500 M */
    lb_group_add(vtss_state,   100000000,     8192/2,         64,       7);    /* 100 M */
    lb_group_add(vtss_state,    50000000,     8192/2,         64,       8);    /*  50 M */
    lb_group_add(vtss_state,    10000000,     8192/4,         64,       9);    /*  10 M */

    /* The LB LBGRP number is used to indicate if the LB is part of a group */
    for (i = 0; i < LB_SET_CNT; ++i) {
        vtss_state->qos.lb_set_grp_idx[i] = LB_GROUP_CNT;
    }

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_policer_init(vtss_state_t *vtss_state)
{
    VTSS_D("Enter");

    // Initialize policers
    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE(20)  | /* GAP_VALUE = 20 : Use line-rate measurement */
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP(0xe) | /* Non-zero DPL means yellow statistics */
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA(1)       | /* Enable overall signaling of flow control from the port policers to DSM */
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT(1)  |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT(1)   |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT(1)    |
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT(1),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_DP_TO_COLOR_MAP      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PORT_FC_ENA          |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT     |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT      |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT       |
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);

    // TDB_VK: Initialize policer related statistics

    // Await policer initialization (init bits cleared)
    REG_POLL_MASK(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG,
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_INIT |
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT  |
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT   |
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

/* Calculate 20 bit policer rate

   If input rate is kbps (frame_rate = FALSE) then output rate is calculated like this:
   output rate = ((input rate * 1000) + 25039) / 25040
   This will round up the rate to the nearest possible value:
     0      -> 0 (Open until burst capacity is used, then closed)
     1..25  -> 1 ( 25040 bps)
    26..50  -> 2 ( 50080 bps)
    51..75  -> 3 ( 75120 bps)
    76..100 -> 4 (100160 bps)
   ...

   If input rate is frames per second (frame_rate = TRUE) then output rate is calculated like this:
   output rate = ((input rate) + 9) / 10
   This will round up the rate to the nearest possible value:
     0     -> 0 (Open until burst capacity is used, then closed)
     1..10 -> 1 (10 fps)
    11..20 -> 2 (20 fps)
    21..30 -> 3 (30 fps)
    31..40 -> 4 (40 fps)
   ...

   In both cases the maximum rate returned is limited to 0xFFFFF (26,256,318,000 bps or 10,485,750 fps).
*/
static u32 fa_calc_policer_rate(u32 rate, BOOL frame_rate)
{
    // TBD_VK: Check that VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT is set correctly.

    if (!frame_rate) { /* input rate is measured in kbps */
        rate = VTSS_DIV64(((u64)rate * 1000) + 25039, 25040);
    } else { /* input rate is measured in fps */
        rate = VTSS_DIV64(((u64)rate) + 9, 10);
    }
    return MIN(0xfffff, rate);
}

/* Calculate 6 bit policer burst level

   If input rate is kbps (frame_rate = FALSE) then output burst level is calculated like this:
   output burst level = (input burst level + 8191) / 8192
   This will round up the burst level to the nearest possible value:
       0        -> 0 (Always closed)
       1.. 8192 -> 1 ( 8.192 bytes)
    8193..16384 -> 2 (16.384 bytes)
   16385..24576 -> 3 (24.576 bytes)
   ...

   If input rate is frames per second (frame_rate = TRUE) then output burst level is set to max.

   In both cases the maximum level returned is limited to 0x3F (516.096 bytes or 206 frames).
*/
static u32 fa_calc_policer_level(u32 level, u32 rate, BOOL frame_rate)
{
    if (rate == 0) {
        return 0;                                /* Always closed */
    } else if ((rate == VTSS_BITRATE_DISABLED) || frame_rate) {
        return 0x3f;                             /* Maximum burst level */
    } else {
        return MIN(0x3f, (level + 8191) / 8192); /* Calculated value 0..0x3f ~ 0..516.096 bytes in steps of 8.192 bytes */
    }
}

static vtss_rc fa_port_policer_set(vtss_state_t       *vtss_state,
                                   u32                chip_port,
                                   u32                idx,
                                   vtss_policer_t     *conf,
                                   vtss_policer_ext_t *conf_ext)
{
    u32 pol_idx = ((VTSS_PORT_POLICERS * chip_port) + idx);
    u32 cpu_qu_mask = 0, q, traffic_type_mask = 0;

    VTSS_D("Enter - chip port %u, policer %u", chip_port, idx);

    /* Burst size and rate */
    REG_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(pol_idx), fa_calc_policer_level(conf->level, conf->rate, conf_ext->frame_rate));
    REG_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(pol_idx), conf_ext->flow_control ? 1 : 0); /* 8192 bytes flow control deassert threshold */
    REG_WR(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(pol_idx), fa_calc_policer_rate(conf->rate, conf_ext->frame_rate));

    // Policer GAP_VALUE = 20 : Use line-rate measurement.
    REG_WRM(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(chip_port),
            VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE(20),
            VTSS_M_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE);

    /* CPU queue mask */
    for (q = 0; q < 8; q++) {
        if (conf_ext->cpu_queue[q]) {
            cpu_qu_mask |= VTSS_BIT(q);
        }
    }

    /* Traffic type mask */
    if (conf->rate != VTSS_BITRATE_DISABLED) {  /* traffic_type_mask == 0 (init value) means policer is disabled */
        if (conf_ext->known_multicast) {
            traffic_type_mask |= VTSS_BIT(0);
        }
        if (conf_ext->known_broadcast) {
            traffic_type_mask |= VTSS_BIT(1);
        }
        if (conf_ext->known_unicast) {
            traffic_type_mask |= VTSS_BIT(2);
        }
        if (conf_ext->unknown_multicast) {
            traffic_type_mask |= VTSS_BIT(3);
        }
        if (conf_ext->unknown_broadcast) {
            traffic_type_mask |= VTSS_BIT(4);
        }
        if (conf_ext->unknown_unicast) {
            traffic_type_mask |= VTSS_BIT(5);
        }
        if (conf_ext->to_cpu) {
            traffic_type_mask |= VTSS_BIT(6);
        }
        if (conf_ext->learning) {
            traffic_type_mask |= VTSS_BIT(7);
        }
    }

    REG_WR(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(chip_port, idx),
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK(cpu_qu_mask)                                 |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_SERVICE_BYPASS_ENA(1)                                    |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL(conf_ext->dp_bypass_level)                 |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA(conf_ext->frame_rate)                     |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA(conf_ext->limit_noncpu_traffic) |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA(conf_ext->limit_cpu_traffic)       |
           VTSS_F_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK(traffic_type_mask));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_policer_conf_set(vtss_state_t *vtss_state, u32 lb_set_idx, vtss_dlb_policer_conf_t *conf)
{
    u32 grp_idx1 = (LB_GROUP_CNT - 1), grp_idx2 = grp_idx1;
    vtss_dlb_policer_conf_t cfg = *conf;

    VTSS_D("Enter  lb_set_idx %u, enable %u", lb_set_idx, cfg.enable);

    if (cfg.type == VTSS_POLICER_TYPE_SINGLE) {
        /* Single bucket, disable EIR */
        cfg.eir = 0;
        cfg.ebs = 0;
        cfg.cm = 0;
        cfg.cf = 0;
    }

    /* Start removing the LB from any possible group */
    VTSS_RC(lb_group_lb_set_remove(vtss_state, lb_set_idx));

    if (cfg.enable) { /* The LB is enabled. Find the suitable group */
        VTSS_RC(lb_group_find(vtss_state, cfg.cir, cfg.cbs, LB_THRES_HYS_MIN, FALSE, &grp_idx1));
        if (cfg.eir != 0) {
            /* EIR present, create LB 2. In case of coupling, the max rate is the sum of CIR and EIR */
            VTSS_RC(lb_group_find(vtss_state, (cfg.cf ? cfg.cir : 0) + cfg.eir, cfg.ebs, LB_THRES_HYS_MIN, FALSE, &grp_idx2));
            grp_idx1 = MIN(grp_idx1, grp_idx2); // Smallest group (fastest update) is selected
        }
        VTSS_RC(lb_group_lb_set_add(vtss_state, grp_idx1, lb_set_idx, &cfg));
    }

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_queue_policer_set(vtss_state_t *vtss_state,
                                    u32 port, u32 queue, vtss_policer_t *conf)
{
    if (port < VTSS_CHIP_PORTS) {
        u32                     pol_idx = VTSS_QUEUE_POL_IDX(port, queue);
        vtss_dlb_policer_conf_t dlb_conf;

        memset(&dlb_conf, 0, sizeof(dlb_conf));
        dlb_conf.type = VTSS_POLICER_TYPE_SINGLE;
        dlb_conf.enable = (conf->rate == VTSS_BITRATE_DISABLED) ? FALSE : TRUE;
        dlb_conf.line_rate = 1;
        dlb_conf.cir = conf->rate;
        dlb_conf.cbs = conf->level;
        return vtss_fa_policer_conf_set(vtss_state, pol_idx, &dlb_conf);
    }
    return VTSS_RC_OK;
}


vtss_rc vtss_fa_port_policer_fc_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                  i, fc_ena = 0;
    u32                  chip_port = VTSS_CHIP_PORT(port_no);
    vtss_port_conf_t     *port_conf = &vtss_state->port.conf[port_no];
    vtss_qos_port_conf_t *qos_conf = &vtss_state->qos.port_conf[port_no];

    VTSS_D("Enter - port %u, chip_port %u", port_no, chip_port);

    if (port_conf->flow_control.generate) {
        for (i = 0; i < VTSS_PORT_POLICERS; i++) {
            if ((qos_conf->policer_port[i].rate != VTSS_BITRATE_DISABLED) && qos_conf->policer_ext_port[i].flow_control) {
                fc_ena |= 1 << i;
            }
        }
    }
    // Enable flow control for the port policers (bit mask).
    // Flow control is already globally (and constantly) enabled during initialization.
    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(chip_port),
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA(fc_ena),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA);
    // Configure DSM for flow control
    REG_WRM(VTSS_DSM_ETH_FC_CFG(chip_port),
            VTSS_F_DSM_ETH_FC_CFG_FC_ANA_ENA(!!fc_ena),
            VTSS_M_DSM_ETH_FC_CFG_FC_ANA_ENA);

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_port_update(vtss_state_t         *vtss_state,
                                              const vtss_port_no_t port_no,
                                              const u16            id)
{
    u16 ix = vtss_state->qos.imap.id.entry[id].ix;
    u16 key = vtss_state->qos.imap.ix[0].entry[ix].key;
    u32 chip_port = VTSS_CHIP_PORT(port_no);

    VTSS_D("Enter - port_no: %u", port_no);
    VTSS_D("Ingress map: id %u, map_idx %u, map_key %u", id, ix, key);
    // At the moment, we only support configuration for lookup #0.
    REG_WR(VTSS_ANA_CL_MAP_CFG(chip_port, 0),
           VTSS_F_ANA_CL_MAP_CFG_MAP_KEY(key) |
           VTSS_F_ANA_CL_MAP_CFG_MAP_IDX(ix));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_dwrr_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf        = &vtss_state->qos.port_conf[port_no];
    u32                  chip_port    = VTSS_CHIP_PORT(port_no);
    u32                  layer        = 2;         /* Default layer for DWRR when HQoS is not present */
    u32                  se           = chip_port; /* Default se when HQoS is not present */
    u8                   dwrr_cost[8] = {0};
    u32                  dwrr_cnt, dwrr_num;
    u32                  queue;

    // TBD_VK: When HQoS is added, the {layer, se} needs to be updated accordingly.

    // 1) Determine the number of queues in DWRR mode.
    // Note: We can only have between 2 and 8 queues in DWRR mode,
    // otherwise DWRR does not make sense and we run in strict mode.
    if (conf->dwrr_enable) {
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
        dwrr_cnt = conf->dwrr_cnt;
        if (dwrr_cnt <= 1) {
            dwrr_cnt = 0;
        } else if (dwrr_cnt > 8) {
            dwrr_cnt = 8;
        }
#else
        // Default DWRR configuration is to use strict mode for the top two
        // queues and DWRR for the rest.
        dwrr_cnt = 6;
#endif /* defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT) */
    } else {
        // All queues are running in strict mode.
        dwrr_cnt = 0;
    }
    dwrr_num = dwrr_cnt;

    if (dwrr_cnt) {
        // Value in HW is already offset by one, so we decrement...
        // e.g. SE_DWRR_CNT = 1 in HW means 2 queues in DWRR mode.
        dwrr_cnt--;
    }

    // 2) Select layer and scheduler element to configure.
    REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer) |
            VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER |
            VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

    // 3) Configure it...
    // a. No. of DWRR inputs
    REG_WRM(VTSS_HSCH_SE_CFG(se),
            VTSS_F_HSCH_SE_CFG_SE_DWRR_CNT(dwrr_cnt),
            VTSS_M_HSCH_SE_CFG_SE_DWRR_CNT);
    // b. Cost for each input
    VTSS_RC(vtss_cmn_qos_weight2cost(conf->queue_pct, dwrr_cost, dwrr_num, VTSS_QOS_DWRR_COST_BIT_WIDTH));
    for (queue = 0; queue < 8; queue++) {
        REG_WRM(VTSS_HSCH_DWRR_ENTRY(queue),
                VTSS_F_HSCH_DWRR_ENTRY_DWRR_COST(dwrr_cost[queue]),
                VTSS_M_HSCH_DWRR_ENTRY_DWRR_COST);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_list_init(vtss_state_t *vtss_state)
{
    vtss_qos_leak_layer_t *ll;
    vtss_qos_leak_group_t *lg;
    u32                   layer, group, leak_interval;
    u32                   sys_clk_per_100ps = 16; // Unit is 100 pS. Default value.

    VTSS_D("Enter");

    /* Init allocation data for layer 0 */
    ll = &vtss_state->qos.leak_conf.layer[0];
    ll->entry = vtss_state->qos.leak_conf.l0_alloc;
    ll->entries = VTSS_HSCH_L0_SES;

    /* Leak lists are currently not used in layer 1 */

    /* Init allocation data for layer 2 */
    ll = &vtss_state->qos.leak_conf.layer[2];
    ll->entry = vtss_state->qos.leak_conf.l2_alloc;
    ll->entries = VTSS_HSCH_L2_SES;

    /* Init allocation data for layer 3 */
    ll = &vtss_state->qos.leak_conf.layer[3];
    ll->entry = vtss_state->qos.leak_conf.l3_alloc;
    ll->entries = VTSS_HSCH_L3_QSHPS;

    // TBD_VK: Check that this register is being set during init.
    REG_RD(VTSS_HSCH_SYS_CLK_PER, &sys_clk_per_100ps);

    /* We use the same leak chain setup for all layers. Setup layer 0 and then final copy to other layers */
    ll = &vtss_state->qos.leak_conf.layer[0];
    ll->group[0].max_rate = VTSS_HSCH_MAX_RATE_GROUP_0;
    ll->group[1].max_rate = VTSS_HSCH_MAX_RATE_GROUP_1;
    ll->group[2].max_rate = VTSS_HSCH_MAX_RATE_GROUP_2;
    ll->group[3].max_rate = VTSS_HSCH_MAX_RATE_GROUP_3;

    for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
        lg = &ll->group[group];
        leak_interval  = (131071 * 1000) / lg->max_rate; /* Calculate leak_interval in uS (max_rate is kbps) */
        lg->resolution = 1000 / leak_interval; /* Calculate resolution in kbps (leak_interval is in uS) */
        lg->leak_time  = 1000 * leak_interval; /* Calculate leak_time in 1nS units (leak_interval is in uS) */
        lg->max_ses    = (1000 * leak_interval) / sys_clk_per_100ps; /* We can service one SE in ~10 cycles.
                                                                        Calculate the maximum number of SEs
                                                                        we can service in each leak_interval */
    }
    /* Copy all groups from layer 0 to all other layers */
    for (layer = 1; layer < VTSS_HSCH_LAYERS; layer++) {
        for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
            vtss_state->qos.leak_conf.layer[layer].group[group] = ll->group[group];
        }
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_first(vtss_state_t *vtss_state,
                                 const u32    layer,
                                 const u32    group,
                                 const u32    se)
{
    REG_WRM(VTSS_HSCH_HSCH_LEAK_CFG(layer, group),
            VTSS_F_HSCH_HSCH_LEAK_CFG_LEAK_FIRST(se),
            VTSS_M_HSCH_HSCH_LEAK_CFG_LEAK_FIRST);

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_link(vtss_state_t *vtss_state,
                                const u32    layer,
                                const u32    group,
                                const u32    se,
                                const u32    se_next)
{
    if (layer == 3) { /* Queue shapers */
        REG_WR(VTSS_HSCH_QSHP_CONNECT(se), se_next);
    } else {
        /* Select layer */
        REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer),
                VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER);

        REG_WR(VTSS_HSCH_SE_CONNECT(se), se_next);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_time(vtss_state_t *vtss_state,
                                const u32    layer,
                                const u32    group,
                                const u32    leak_time)
{
    REG_WR(VTSS_HSCH_HSCH_TIMER_CFG(layer, group), leak_time);

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_list_unlink(vtss_state_t *vtss_state,
                                       const u32    layer,
                                       const u32    se)
{
    vtss_qos_leak_layer_t *ll = &vtss_state->qos.leak_conf.layer[layer];
    vtss_qos_leak_entry_t *le = &ll->entry[se];

    VTSS_D("Enter - layer %u, se %u", layer, se);

    if (layer >= VTSS_HSCH_LAYERS) {
        VTSS_E("Invalid layer %u!", layer);
        return VTSS_RC_ERROR;
    }

    if (se >= vtss_state->qos.leak_conf.layer[layer].entries) {
        VTSS_E("se %u >= %u in layer %u!", se, vtss_state->qos.leak_conf.layer[layer].entries, layer);
        return VTSS_RC_ERROR;
    }

    if (le->enabled) {
        vtss_qos_leak_group_t *lg   = &ll->group[le->group];
        BOOL                  first = (se == le->prev);
        BOOL                  last  = (se == le->next);

        /*
         * Shaper(s) MUST be disabled before calling this function!
         * The leak algorithm needs to run at least once in order to stop the shaper.
         * If the shaper is active (is shaping) and the leaking is disabled before the
         * leak algorithm has been run, all traffic is blocked by the shaper.
         */

        VTSS_NSLEEP(lg->leak_time);     /* Sleep one leak period */

        if (first) {
            if (last) {
                /* This is the one and only entry in the list. Disable leaking by setting leak_time to zero */
                lg->head.prev    = 0;
                lg->head.next    = 0;
                lg->head.group   = 0;
                lg->head.enabled = FALSE;
                VTSS_RC(fa_qos_leak_time(vtss_state, layer, le->group, 0));
                if (lg->cur_ses != 1) {
                    VTSS_E("Layer %u, group %u. Unlink first&last SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            } else { /* not last */
                lg->head.next = le->next;
                ll->entry[le->next].prev = le->next;
                VTSS_RC(fa_qos_leak_first(vtss_state, layer, le->group, le->next));
                if (lg->cur_ses < 2) {
                    VTSS_E("Layer %u, group %u. Unlink first SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            }
        } else { /* not first */
            if (last) {
                lg->head.prev = le->prev;
                ll->entry[le->prev].next = le->prev;
                VTSS_RC(fa_qos_leak_link(vtss_state, layer, le->group, le->prev, le->prev));
                if (lg->cur_ses < 2) {
                    VTSS_E("Layer %u, group %u. Unlink last SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            } else { /* not last */
                ll->entry[le->prev].next = le->next;
                ll->entry[le->next].prev = le->prev;
                VTSS_RC(fa_qos_leak_link(vtss_state, layer, le->group, le->prev, le->next));
                if (lg->cur_ses < 3) {
                    VTSS_E("Layer %u, group %u. Unlink middle SE but lg->cur_ses == %u!", layer, le->group, lg->cur_ses);
                    return VTSS_RC_ERROR;
                }
            }
        }
        le->enabled = FALSE;
        lg->cur_ses--;
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_leak_list_link(vtss_state_t         *vtss_state,
                                     const u32            layer,
                                     const u32            se,
                                     const vtss_bitrate_t rate,
                                     vtss_bitrate_t       *resolution)
{
    vtss_qos_leak_layer_t *ll = &vtss_state->qos.leak_conf.layer[layer];
    vtss_qos_leak_entry_t *le = &ll->entry[se];
    vtss_qos_leak_group_t *lg = &ll->group[le->group];
    vtss_bitrate_t        current_max_rate = ll->group[le->group].max_rate;
    int                   group;
    BOOL                  change_group = FALSE;

    VTSS_D("Enter - layer %u, se %u", layer, se);

    if (layer >= VTSS_HSCH_LAYERS) {
        VTSS_E("Invalid layer %u!", layer);
        return VTSS_RC_ERROR;
    }

    if (se >= vtss_state->qos.leak_conf.layer[layer].entries) {
        VTSS_E("se %u >= %u in layer %u!", se, vtss_state->qos.leak_conf.layer[layer].entries, layer);
        return VTSS_RC_ERROR;
    }

    if (le->enabled) {
        if (rate > current_max_rate) {
            change_group = TRUE;
        } else {
            /* Check if we can find a better group. We expect the groups to be ordered by rate with lowest rate at group[0] */
            for (group = le->group - 1; group >= 0; group--) {
                lg = &ll->group[group];
                if ((rate <= lg->max_rate) && (lg->max_rate < current_max_rate) && (lg->cur_ses < lg->max_ses)) {
                    change_group = TRUE;
                    break;
                }
            }
        }
        if (change_group) {
            VTSS_RC(fa_qos_leak_list_unlink(vtss_state, layer, se));
        } else {
            *resolution = ll->group[le->group].resolution;
            return VTSS_RC_OK;
        }
    }
    /* Find best possible new group */
    for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
        lg = &ll->group[group];
        if ((lg->cur_ses < lg->max_ses) && /* There must be free sessions left */
            ((rate <= lg->max_rate) ||     /* Rate must not exceed max_rate unless it is the last group */
             (group == (VTSS_HSCH_LEAK_LISTS - 1)))) {
            *resolution = lg->resolution;
            break;
        }
    }
    if (group == VTSS_HSCH_LEAK_LISTS) {
        *resolution = 0;
        VTSS_E("No free entries in leak lists!");
        return VTSS_RC_ERROR;
    }
    le->enabled = TRUE;
    le->group   = group;
    le->prev    = se; /* Always insert at head of chain */
    if (lg->head.enabled) { /* This is NOT the first entry in group */
        ll->entry[lg->head.next].prev = se;
        le->next = lg->head.next;
    } else { /* This is the first entry in group */
        le->next         = se;
        lg->head.prev    = se;
        lg->head.enabled = TRUE;
    }
    lg->head.next = se;
    lg->cur_ses++;
    VTSS_RC(fa_qos_leak_time(vtss_state, layer, group, 0)); /* stop leaking */
    VTSS_RC(fa_qos_leak_link(vtss_state, layer, group, se, le->next));
    VTSS_RC(fa_qos_leak_first(vtss_state, layer, group, se));
    VTSS_RC(fa_qos_leak_time(vtss_state, layer, group, lg->leak_time)); /* start leaking */

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_qos_shaper_conf_set(vtss_state_t *vtss_state, vtss_shaper_t *shaper, u32 layer, u32 se, u32 dlb_sense_port, u32 dlb_sense_qos)
{
    u32            cir, cbs, eir, ebs;
    vtss_bitrate_t resolution;

    VTSS_D("Enter - layer %u, se %u, dlb_sense_port %u, dlb_sense_qos %u!", layer, se, dlb_sense_port, dlb_sense_qos);

    /* Shaper rate configuration.
     * Resolution is determined by the actual leak list. Example if resolution is 100 kbps:
     * The value (in kbps) is rounded up to the next possible value:
     *        0 -> 0 (Open until burst capacity is used, then closed)
     *   1..100 -> 1 (100 kbps)
     * 101..200 -> 2 (200 kbps)
     * 201..300 -> 3 (300 kbps)
     */

    /* Shaper burst level configuration
     * The value is rounded up to the next possible value:
     *           0 -> 0 (Shaper disabled)
     *    1.. 4096 -> 1 ( 4 KB)
     * 4097.. 8192 -> 2 ( 8 KB)
     * 8193..12288 -> 3 (12 KB)
     */

    /* Select layer */
    REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer),
            VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER);

    if (shaper->rate != VTSS_BITRATE_DISABLED) {
        VTSS_RC(fa_qos_leak_list_link(vtss_state, layer, se, shaper->rate, &resolution));

        cir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(shaper->rate,  resolution));
        cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->level, 4096));

        REG_WR(VTSS_HSCH_CIR_CFG(se),
               VTSS_F_HSCH_CIR_CFG_CIR_RATE(cir) |
               VTSS_F_HSCH_CIR_CFG_CIR_BURST(cbs));

        if (shaper->eir != VTSS_BITRATE_DISABLED) {
            eir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(shaper->eir, resolution));
            ebs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->ebs, 4096));

            REG_WR(VTSS_HSCH_EIR_CFG(se),
                   VTSS_F_HSCH_EIR_CFG_EIR_RATE(eir) |
                   VTSS_F_HSCH_EIR_CFG_EIR_BURST(ebs));

            REG_WRM(VTSS_HSCH_SE_DLB_SENSE(se),
                    VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(dlb_sense_qos)   |
                    VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(dlb_sense_port) |
                    VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA(1)           |
                    VTSS_F_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA(1),
                    VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_PRIO                  |
                    VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_DPORT                 |
                    VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA              |
                    VTSS_M_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA);
        } else {
            REG_WR(VTSS_HSCH_EIR_CFG(se),      0); /* Disable EIR */
            REG_WR(VTSS_HSCH_SE_DLB_SENSE(se), 0); /* Disable DLB */
        }
        REG_WRM(VTSS_HSCH_SE_CFG(se),
                VTSS_F_HSCH_SE_CFG_SE_FRM_MODE(shaper->mode),
                VTSS_M_HSCH_SE_CFG_SE_FRM_MODE);
    } else {
        REG_WR(VTSS_HSCH_CIR_CFG(se),      0); /* Disable CIR */
        REG_WR(VTSS_HSCH_EIR_CFG(se),      0); /* Disable EIR */
        REG_WR(VTSS_HSCH_SE_DLB_SENSE(se), 0); /* Disable DLB */
        REG_WRM(VTSS_HSCH_SE_CFG(se),
                VTSS_F_HSCH_SE_CFG_SE_FRM_MODE(0), /* Set to default */
                VTSS_M_HSCH_SE_CFG_SE_FRM_MODE);

        VTSS_RC(fa_qos_leak_list_unlink(vtss_state, layer, se));
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_queue_shaper_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    u32                  chip_port = VTSS_CHIP_PORT(port_no);
    u32                  layer = 0; /* Default layer on all variants */
    int                  queue;

    VTSS_D("Enter - port_no: %u", port_no);
    for (queue = 0; queue < 8; queue++) {
        u32 se = FA_HSCH_L0_SE(chip_port, queue);
        VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &conf->shaper_queue[queue], layer, se, chip_port, queue));
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_queue_cut_through_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    VTSS_D("Enter - port_no: %u", port_no);

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_port_conf_t *conf = &vtss_state->qos.port_conf[port_no];
    vtss_qos_port_conf_t *old_conf = &vtss_state->qos.port_conf_old;
    u32                  chip_port = VTSS_CHIP_PORT(port_no);
    u32                  pcp, dei, tag_pcp_cfg, tag_dei_cfg, class, policer, queue;

    VTSS_D("Enter - port_no: %u", port_no);

    // Port specific configuration for:
    // * Default PCP classification (ingress)
    // * Default DEI classification (ingress)
    // * Basic QoS classification (ingress)
    // * Basic DP classification (ingress)
    // * Basic DSCP classification (ingress)
    // * Basic CoSID classification (ingress)
    REG_WRM(VTSS_ANA_CL_VLAN_CTRL(chip_port),
            VTSS_F_ANA_CL_VLAN_CTRL_PORT_PCP(conf->usr_prio)     |
            VTSS_F_ANA_CL_VLAN_CTRL_PORT_DEI(conf->default_dei),
            VTSS_M_ANA_CL_VLAN_CTRL_PORT_PCP                     |
            VTSS_M_ANA_CL_VLAN_CTRL_PORT_DEI);
    REG_WRM(VTSS_ANA_CL_QOS_CFG(chip_port),
            VTSS_F_ANA_CL_QOS_CFG_DEFAULT_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->default_prio)) |
            VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA(conf->tag_class_enable)                                 |
            VTSS_F_ANA_CL_QOS_CFG_DSCP_TRANSLATE_ENA(conf->dscp_translate)                                |
            VTSS_F_ANA_CL_QOS_CFG_DSCP_QOS_ENA(conf->dscp_class_enable)                                   |
            VTSS_F_ANA_CL_QOS_CFG_DEFAULT_DP_VAL(conf->default_dpl)                                       |
            VTSS_F_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA(conf->tag_class_enable)                                  |
            VTSS_F_ANA_CL_QOS_CFG_DSCP_DP_ENA(conf->dscp_class_enable)                                    |
            VTSS_F_ANA_CL_QOS_CFG_DSCP_REWR_MODE_SEL(conf->dscp_mode)                                     |
            VTSS_F_ANA_CL_QOS_CFG_DEFAULT_COSID_ENA(1)                                                    |
            VTSS_F_ANA_CL_QOS_CFG_DEFAULT_COSID_VAL(conf->cosid),
            VTSS_M_ANA_CL_QOS_CFG_DEFAULT_QOS_VAL                                                         |
            VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA                                                         |
            VTSS_M_ANA_CL_QOS_CFG_DSCP_TRANSLATE_ENA                                                      |
            VTSS_M_ANA_CL_QOS_CFG_DSCP_QOS_ENA                                                            |
            VTSS_M_ANA_CL_QOS_CFG_DEFAULT_DP_VAL                                                          |
            VTSS_M_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA                                                          |
            VTSS_M_ANA_CL_QOS_CFG_DSCP_DP_ENA                                                             |
            VTSS_M_ANA_CL_QOS_CFG_DSCP_REWR_MODE_SEL                                                      |
            VTSS_M_ANA_CL_QOS_CFG_DEFAULT_COSID_ENA                                                       |
            VTSS_M_ANA_CL_QOS_CFG_DEFAULT_COSID_VAL);

    // Basic QoS and DP classification (ingress):
    // Map from (PCP, DEI) to QoS class and DP level.
    for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
        for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
            REG_WR(VTSS_ANA_CL_PCP_DEI_MAP_CFG(chip_port, (8 * dei + pcp)),
                   VTSS_F_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_DP_VAL(conf->dp_level_map[pcp][dei]) |
                   VTSS_F_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->qos_class_map[pcp][dei])));
        }
    }

    // Port configuration for ingress mapping lookups (lookup 0 only for now)
    VTSS_RC(fa_qos_ingress_map_port_update(vtss_state, port_no, conf->ingress_map));

    // Port policing configuration.
    for (policer = 0; policer < VTSS_PORT_POLICERS; policer++) {
        VTSS_RC(fa_port_policer_set(vtss_state, chip_port, policer, &conf->policer_port[policer], &conf->policer_ext_port[policer]));
    }

    /* Queue policer configuration */
    for (queue = 0; queue < 8; queue++) {
        if ((conf->policer_queue[queue].level != old_conf->policer_queue[queue].level) || (conf->policer_queue[queue].rate != old_conf->policer_queue[queue].rate)) {  /* Do not configure unchanged policer as it will be temporary disabled then */
            VTSS_RC(fa_queue_policer_set(vtss_state, chip_port, queue, &conf->policer_queue[queue]));
        }
    }

    // Port policer flow control configuration.
    VTSS_RC(vtss_fa_port_policer_fc_set(vtss_state, port_no));

    // Port bandwidth distribution configuration.
    VTSS_RC(fa_qos_dwrr_conf_set(vtss_state, port_no));

    // Port shaper configuration. Use scheduler element in layer 2 indexed by chip_port.
    VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &conf->shaper_port, 2, chip_port, chip_port, 0));

    // Queue shaper configuration.
    VTSS_RC(fa_qos_queue_shaper_conf_set(vtss_state, port_no));

    // Cut-through configuration.
    VTSS_RC(fa_qos_queue_cut_through_set(vtss_state, port_no));

    // WRED group configuration.
    if (conf->wred_group > 2) {
        VTSS_E("Invalid WRED group: %u!", conf->wred_group);
        return VTSS_RC_ERROR;
    }
    REG_WR(VTSS_QRES_WRED_GROUP(chip_port),
           VTSS_F_QRES_WRED_GROUP_WRED_GROUP(conf->wred_group));

    // Tag remarking configuration (egress)
    // Port default PCP and DEI values (egress)
    REG_WRM(VTSS_REW_PORT_VLAN_CFG(chip_port),
            VTSS_F_REW_PORT_VLAN_CFG_PORT_PCP(conf->tag_default_pcp) |
            VTSS_F_REW_PORT_VLAN_CFG_PORT_DEI(conf->tag_default_dei),
            VTSS_M_REW_PORT_VLAN_CFG_PORT_PCP                        |
            VTSS_M_REW_PORT_VLAN_CFG_PORT_DEI);
    // Configure mode of PCP/DEI selection for the tag.
    // Currently we only support 3 modes:
    // * Classified PCP/DEI
    // * Port PCP/DEI
    // * PCP/DEI taken from mapping table with [DE, classified QoS] as key
    switch (conf->tag_remark_mode) {
    case VTSS_TAG_REMARK_MODE_DEFAULT:
        tag_pcp_cfg = 1; /* PORT_PCP */
        tag_dei_cfg = 1; /* PORT_DEI */
        break;
    case VTSS_TAG_REMARK_MODE_MAPPED:
        tag_pcp_cfg = 2; /* DE and classified QoS mapped to PCP (PCP_MAP_DEx */
        tag_dei_cfg = 2; /* DE and classified QoS mapped to DEI (DEI_MAP_DEx */
        break;
    default:
        tag_pcp_cfg = 0; /* Classified PCP */
        tag_dei_cfg = 0; /* Classified DEI */
        break;
    }
    REG_WRM(VTSS_REW_TAG_CTRL(chip_port),
            VTSS_F_REW_TAG_CTRL_TAG_PCP_CFG(tag_pcp_cfg) |
            VTSS_F_REW_TAG_CTRL_TAG_DEI_CFG(tag_dei_cfg),
            VTSS_M_REW_TAG_CTRL_TAG_PCP_CFG              |
            VTSS_M_REW_TAG_CTRL_TAG_DEI_CFG);
    // Mapping tables for [classified QoS, DE (colour)] to PCP and DEI
    for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
        REG_WR(VTSS_REW_PCP_MAP_DE0(chip_port, class),
               VTSS_F_REW_PCP_MAP_DE0_PCP_DE0(conf->tag_pcp_map[class][0]));
        REG_WR(VTSS_REW_PCP_MAP_DE1(chip_port, class),
               VTSS_F_REW_PCP_MAP_DE1_PCP_DE1(conf->tag_pcp_map[class][1]));
        REG_WR(VTSS_REW_DEI_MAP_DE0(chip_port, class),
               VTSS_F_REW_DEI_MAP_DE0_DEI_DE0(conf->tag_dei_map[class][0]));
        REG_WR(VTSS_REW_DEI_MAP_DE1(chip_port, class),
               VTSS_F_REW_DEI_MAP_DE1_DEI_DE1(conf->tag_dei_map[class][1]));
    }

    // Egress DSCP remarking (legacy) configuration.
    REG_WRM(VTSS_REW_DSCP_MAP(chip_port),
            VTSS_F_REW_DSCP_MAP_DSCP_UPDATE_ENA((conf->dscp_emode > VTSS_DSCP_EMODE_DISABLE)) |
            VTSS_F_REW_DSCP_MAP_DSCP_REMAP_ENA((conf->dscp_emode > VTSS_DSCP_EMODE_REMARK)),
            VTSS_M_REW_DSCP_MAP_DSCP_UPDATE_ENA                                               |
            VTSS_M_REW_DSCP_MAP_DSCP_REMAP_ENA);

    // Update ES0-based default port QoS egress mapping
    VTSS_RC(vtss_fa_vcap_port_update(vtss_state, port_no));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_storm_policer_set(vtss_state_t             *vtss_state,
                                    u32                       idx,
                                    vtss_packet_rate_t        rate,
                                    BOOL                      frame_rate,
                                    vtss_storm_policer_mode_t mode)
{
    BOOL noncpu_traffic, cpu_traffic;
    u32  traffic_type_mask;

    if (idx > 2) {
        VTSS_E("Invalid storm policer index: %u!", idx);
        return VTSS_RC_ERROR;
    }

    if (rate == VTSS_PACKET_RATE_DISABLED) {
        /* Apply default values */
        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(idx), 0);
        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(idx), 0);
        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(idx),
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(1));
    } else {
        if (mode == VTSS_STORM_POLICER_MODE_PORTS_ONLY) {
            noncpu_traffic = TRUE;
            cpu_traffic    = FALSE;
        } else if (mode == VTSS_STORM_POLICER_MODE_CPU_ONLY) {
            noncpu_traffic = FALSE;
            cpu_traffic    = TRUE;
        } else {
            noncpu_traffic = TRUE;
            cpu_traffic    = TRUE;
        }

        if (idx == 0) {
            traffic_type_mask = 0x20; /* Unknown unicast:   0b0010.0000 */
        } else if (idx == 1) {
            traffic_type_mask = 0x08; /* Unknown multicast: 0b0000.1000 */
        } else {
            traffic_type_mask = 0x10; /* Unknown broadcast: 0b0001.0000 */
        }

        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(idx),
               fa_calc_policer_rate(rate, frame_rate));
        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(idx),
               fa_calc_policer_level(8192 * 2, rate, frame_rate));
        REG_WR(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(idx),
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA(frame_rate)               |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK(0)                           |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(noncpu_traffic) |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA(cpu_traffic)       |
               VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK(traffic_type_mask));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_wred_conf_set(vtss_state_t *vtss_state)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    u32              group, queue, dpl, wm_high;

    VTSS_D("Enter");
    for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
        for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
            // TBD_VK: Determine WM_HIGH, when FA datasheet is ready.
            //wm_high = vtss_jr2_wm_high_get(vtss_state, queue);
            wm_high = 0;

            for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                vtss_red_v3_t *red = &conf->red_v3[queue][dpl][group];
                vtss_pct_t     max_dp = 100;
                vtss_pct_t     max_fl = 100;
                u32            wm_red_low, wm_red_high;

                /* Sanity check */
                if (red->min_fl > 100) {
                    VTSS_E("illegal min_fl (%u) on group %d, queue %d, dpl %d", red->min_fl, group, queue, dpl + 1);
                    return VTSS_RC_ERROR;
                }
                if ((red->max < 1) || (red->max > 100)) {
                    VTSS_E("illegal max (%u) on group %d, queue %d, dpl %d", red->max, group, queue, dpl + 1);
                    return VTSS_RC_ERROR;
                }
                if ((red->max_unit != VTSS_WRED_V2_MAX_DP) && (red->max_unit != VTSS_WRED_V2_MAX_FL)) {
                    VTSS_E("illegal max_unit (%u) on group %d, queue %d, dpl %d", red->max_unit, group, queue, dpl + 1);
                    return VTSS_RC_ERROR;
                }
                if (red->max_unit == VTSS_WRED_V2_MAX_DP) {
                    max_dp = red->max; /* Unit is drop probability - save specified value */
                } else {
                    if (red->min_fl >= red->max) {
                        VTSS_E("min_fl (%u) >= max fl (%u) on group %d, queue %d, dpl %d", red->min_fl, red->max, group, queue, dpl + 1);
                        return VTSS_RC_ERROR;
                    } else {
                        max_fl = red->max; /* Unit is fill level - save specified value */
                    }
                }
                if (red->enable) {
                    wm_red_low  = wm_high * red->min_fl / 100;                              /* Convert from % to actual value in bytes */
                    wm_red_high = wm_high * max_fl / 100;                                   /* Convert from % to actual value in bytes */
                    wm_red_high = ((wm_red_high - wm_red_low) * 100 / max_dp) + wm_red_low; /* Adjust wm_red_high to represent 100% drop probability */
                    wm_red_low  = MIN(wm_red_low / 2944, VTSS_BITMASK(11));                 /* Convert from bytes to 2944 byte chunks and prevent overflow */
                    wm_red_high = MIN(wm_red_high / 2944, VTSS_BITMASK(11));                /* Convert from bytes to 2944 byte chunks and prevent overflow */
                } else {
                    wm_red_low = wm_red_high = VTSS_BITMASK(11);                            /* Disable red by setting both fields to max */
                }

                REG_WR(VTSS_QRES_WRED_PROFILE((24 * group) + (8 * dpl) + queue),            /* Red profile for qroup, queue, dpl */
                       VTSS_F_QRES_WRED_PROFILE_WM_RED_LOW(wm_red_low) |
                       VTSS_F_QRES_WRED_PROFILE_WM_RED_HIGH(wm_red_high));
            }
        }
    }

    // TBD_VK: waiting for the FA WM framework to be implemented.
    //VTSS_RC(vtss_jr2_wm_update(vtss_state)); /* Update watermarks */

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_conf_set(vtss_state_t *vtss_state, BOOL changed)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    u32             i;

    VTSS_D("Enter");

    // Global configuration for:
    // * Basic QoS classification
    // * Basic DP classification
    // * Basic DSCP classification
    // * Egress DSCP remarking
    for (i = 0; i < 64; i++) {
        REG_WRM(VTSS_ANA_CL_DSCP_CFG(i),
                VTSS_F_ANA_CL_DSCP_CFG_DSCP_TRANSLATE_VAL(conf->dscp_translate_map[i])                               |
                VTSS_F_ANA_CL_DSCP_CFG_DSCP_TRUST_ENA(conf->dscp_trust[i])                                           |
                VTSS_F_ANA_CL_DSCP_CFG_DSCP_QOS_VAL(vtss_cmn_qos_chip_prio(vtss_state, conf->dscp_qos_class_map[i])) |
                VTSS_F_ANA_CL_DSCP_CFG_DSCP_DP_VAL(conf->dscp_dp_level_map[i])                                       |
                VTSS_F_ANA_CL_DSCP_CFG_DSCP_REWR_ENA(conf->dscp_remark[i]),
                VTSS_M_ANA_CL_DSCP_CFG_DSCP_TRANSLATE_VAL                                                            |
                VTSS_M_ANA_CL_DSCP_CFG_DSCP_TRUST_ENA                                                                |
                VTSS_M_ANA_CL_DSCP_CFG_DSCP_QOS_VAL                                                                  |
                VTSS_M_ANA_CL_DSCP_CFG_DSCP_DP_VAL                                                                   |
                VTSS_M_ANA_CL_DSCP_CFG_DSCP_REWR_ENA);
        REG_WRM(VTSS_REW_DSCP_REMAP(i),
                VTSS_F_REW_DSCP_REMAP_DSCP_REMAP(conf->dscp_remap[i]),
                VTSS_M_REW_DSCP_REMAP_DSCP_REMAP);
    }

    // Basic DSCP classification:
    // Map from classified (QoS, DP) to DSCP.
    for (i = 0; i < 8; i++) {
        REG_WR(VTSS_ANA_CL_QOS_MAP_CFG(i),
               VTSS_F_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map[i]));
        REG_WR(VTSS_ANA_CL_QOS_MAP_CFG(i +  8),
               VTSS_F_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp1[i]));
        REG_WR(VTSS_ANA_CL_QOS_MAP_CFG(i + 16),
               VTSS_F_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp2[i]));
        REG_WR(VTSS_ANA_CL_QOS_MAP_CFG(i + 24),
               VTSS_F_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(conf->dscp_qos_map_dp3[i]));

    }

    // Storm policing configuration:
    // Eight individual storm policers are available in HW,
    // however we currently only support 3:
    // * Policer 0:   Unicast (unknown unicast frames).
    // * Policer 1:   Multicast (unknown multicast frames).
    // * Policer 2:   Broadcast (known and unknown broadcast frames).
    // * Policer 3-7: Not used.
    VTSS_RC(fa_storm_policer_set(vtss_state, 0, conf->policer_uc, conf->policer_uc_frame_rate, conf->policer_uc_mode));
    VTSS_RC(fa_storm_policer_set(vtss_state, 1, conf->policer_mc, conf->policer_mc_frame_rate, conf->policer_mc_mode));
    VTSS_RC(fa_storm_policer_set(vtss_state, 2, conf->policer_bc, conf->policer_bc_frame_rate, conf->policer_bc_mode));

    // WRED configuration:
    VTSS_RC(fa_qos_wred_conf_set(vtss_state));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_vcap_update(vtss_state_t *vtss_state,
                                              const u16    id)
{
    vtss_port_no_t port_no;

    VTSS_D("Enter");
    VTSS_D("Ingress map id %u", id);

    // Update port ingress mapping lookup configuration for each port
    // that is using the respective ingress mapping.
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (id == vtss_state->qos.port_conf[port_no].ingress_map) {
            // Port configuration for ingress mapping lookups (lookup 0 only for now)
            VTSS_RC(fa_qos_ingress_map_port_update(vtss_state, port_no, id));
        }
    }

    // Update any CLM entries that use the above ingress mapping
    VTSS_RC(vtss_vcap_clm_update(vtss_state, id));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_hw_entry_update(vtss_state_t                        *vtss_state,
                                                  const u32                           row,
                                                  const u32                           col,
                                                  const vtss_qos_ingress_map_values_t *const val)
{
    REG_WRM(VTSS_ANA_CL_MAP_ENTRY(row, col),
            VTSS_F_ANA_CL_MAP_ENTRY_PATH_COLOR_VAL(!!val->dpl)      |
            VTSS_F_ANA_CL_MAP_ENTRY_PATH_COSID_VAL(val->path_cosid) |
            VTSS_F_ANA_CL_MAP_ENTRY_DP_VAL(val->dpl)                |
            VTSS_F_ANA_CL_MAP_ENTRY_COSID_VAL(val->cosid)           |
            VTSS_F_ANA_CL_MAP_ENTRY_QOS_VAL(val->cos)               |
            VTSS_F_ANA_CL_MAP_ENTRY_DEI_VAL(val->dei)               |
            VTSS_F_ANA_CL_MAP_ENTRY_PCP_VAL(val->pcp)               |
            VTSS_F_ANA_CL_MAP_ENTRY_DSCP_VAL(val->dscp)             |
            VTSS_F_ANA_CL_MAP_ENTRY_TC_VAL(val->mpls_tc),
            VTSS_M_ANA_CL_MAP_ENTRY_PATH_COLOR_VAL                  |
            VTSS_M_ANA_CL_MAP_ENTRY_PATH_COSID_VAL                  |
            VTSS_M_ANA_CL_MAP_ENTRY_DP_VAL                          |
            VTSS_M_ANA_CL_MAP_ENTRY_COSID_VAL                       |
            VTSS_M_ANA_CL_MAP_ENTRY_QOS_VAL                         |
            VTSS_M_ANA_CL_MAP_ENTRY_DEI_VAL                         |
            VTSS_M_ANA_CL_MAP_ENTRY_PCP_VAL                         |
            VTSS_M_ANA_CL_MAP_ENTRY_DSCP_VAL                        |
            VTSS_M_ANA_CL_MAP_ENTRY_TC_VAL);

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_hw_update(vtss_state_t *vtss_state,
                                             const u16    res,
                                             const u16    ix,
                                             const int    len,
                                             const void   *const map)
{
    const vtss_qos_ingress_map_t *const m = map;
    u32                                 col, row;

    VTSS_D("Enter");
    VTSS_D("Resource %u, row (ix) %u, length %u", res, ix, len);

    if (m) {
        u32 action =
            VTSS_F_ANA_CL_SET_CTRL_PATH_ENA(m->action.path)   |
            VTSS_F_ANA_CL_SET_CTRL_TC_ENA(m->action.mpls_tc)  |
            VTSS_F_ANA_CL_SET_CTRL_DP_ENA(m->action.dpl)      |
            VTSS_F_ANA_CL_SET_CTRL_COSID_ENA(m->action.cosid) |
            VTSS_F_ANA_CL_SET_CTRL_QOS_ENA(m->action.cos)     |
            VTSS_F_ANA_CL_SET_CTRL_DEI_ENA(m->action.dei)     |
            VTSS_F_ANA_CL_SET_CTRL_PCP_ENA(m->action.pcp)     |
            VTSS_F_ANA_CL_SET_CTRL_DSCP_ENA(m->action.dscp);

        switch (m->key) {
        case VTSS_QOS_INGRESS_MAP_KEY_PCP:
            /* Add 1 row with PCP values */
            REG_WR(VTSS_ANA_CL_SET_CTRL(ix), action);
            for (col = 0; col < 8; col++) {
                VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, ix, col, &m->maps.pcp[col]));
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
            /* Add 2 row with PCP/DEI values */
            for (row = 0; row < 2; row++) {
                REG_WR(VTSS_ANA_CL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.pcp_dei[col][row]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                REG_WR(VTSS_ANA_CL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.dscp[(row * 8) + col]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                REG_WR(VTSS_ANA_CL_SET_CTRL(ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, ix + row, col, &m->maps.dpd.dscp[(row * 8) + col]));
                }
            }
            /* Add 2 rows with PCP/DEI values after the 8 DSCP rows */
            for (row = 0; row < 2; row++) {
                REG_WR(VTSS_ANA_CL_SET_CTRL(8 + ix + row), action);
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, 8 + ix + row, col, &m->maps.dpd.pcp_dei[col][row]));
                }
            }
            break;
        case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
            /* Add 1 row with MPLS TC values */
            REG_WR(VTSS_ANA_CL_SET_CTRL(ix), action);
            for (col = 0; col < 8; col++) {
                VTSS_RC(fa_qos_ingress_map_hw_entry_update(vtss_state, ix, col, &m->maps.mpls_tc[col]));
            }
            break;
        default:
            VTSS_E("Invalid ingress map key: %u!", m->key);
            return VTSS_RC_ERROR;
        }
    } else {
        /* Set rows to zero */
        for (row = 0; row < len; row++) {
            REG_WR(VTSS_ANA_CL_SET_CTRL(ix + row), 0);
            for (col = 0; col < 8; col++) {
                REG_WR(VTSS_ANA_CL_MAP_ENTRY(ix + row, col), 0);
            }
        }
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_hw_copy(vtss_state_t *vtss_state,
                                           const u16    res,
                                           const u16    src,
                                           const u16    dst,
                                           const int    len)
{
    u32 col, row, val;

    VTSS_D("Enter");
    VTSS_D("Resource %u, copying from row %u to row %u, length %d", res, src, dst, len);

    for (row = 0; row < len; row++) {
        REG_RD(VTSS_ANA_CL_SET_CTRL(src + row), &val);
        REG_WR(VTSS_ANA_CL_SET_CTRL(dst + row), val);
        for (col = 0; col < 8; col++) {
            REG_RD(VTSS_ANA_CL_MAP_ENTRY(src + row, col), &val);
            REG_WR(VTSS_ANA_CL_MAP_ENTRY(dst + row, col), val);
        }
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_ingress_map_add(vtss_state_t *vtss_state, const vtss_qos_ingress_map_t *const map)
{
    VTSS_D("Redirecting to AIL with egress map id %u, key %u", map->id, map->key);
    return vtss_cmn_qos_map_add(vtss_state, &vtss_state->qos.imap, map->id, map->key, 0, map);
}

static vtss_rc fa_qos_ingress_map_del(vtss_state_t *vtss_state, const vtss_qos_ingress_map_id_t id)
{
    VTSS_D("Redirecting to AIL with egress map id %u", id);
    return vtss_cmn_qos_map_del(vtss_state, &vtss_state->qos.imap, id);
}

static vtss_rc fa_qos_egress_map_vcap_update(vtss_state_t *vtss_state,
                                              const u16    id)
{
    vtss_port_no_t port_no;

    VTSS_D("Enter");
    VTSS_D("Egress map id %u", id);

    // Update port egress mapping default configuration for each port
    // that is using the respective egress mapping.
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (id == vtss_state->qos.port_conf[port_no].egress_map) {
            // Update ES0-based default port QoS egress mapping
            VTSS_RC(vtss_fa_vcap_port_update(vtss_state, port_no));
        }
    }

    // Update any ES0 entries that use the above egress mapping
    VTSS_RC(vtss_vcap_es0_emap_update(vtss_state, id));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_egress_map_hw_entry_update(vtss_state_t                       *vtss_state,
                                                 const u32                          res,
                                                 const u32                          row,
                                                 const u32                          col,
                                                 const vtss_qos_egress_map_values_t *const val)
{
    if (res == 0) { // Resource A
        REG_WR(VTSS_REW_MAP_VAL_A((row * 8) + col),
               VTSS_F_REW_MAP_VAL_A_OAM_COLOR(val->dei)        |
               VTSS_F_REW_MAP_VAL_A_OAM_COSID(val->path_cosid) |
               VTSS_F_REW_MAP_VAL_A_DSCP_VAL(val->dscp)        |
               VTSS_F_REW_MAP_VAL_A_DEI_VAL(val->dei)          |
               VTSS_F_REW_MAP_VAL_A_PCP_VAL(val->pcp)          |
               VTSS_F_REW_MAP_VAL_A_TC_VAL(val->mpls_tc));
    } else { // Resource B
        REG_WR(VTSS_REW_MAP_VAL_B((row * 8) + col),
               VTSS_F_REW_MAP_VAL_B_OAM_COLOR(val->dei)        |
               VTSS_F_REW_MAP_VAL_B_OAM_COSID(val->path_cosid) |
               VTSS_F_REW_MAP_VAL_B_DSCP_VAL(val->dscp)        |
               VTSS_F_REW_MAP_VAL_B_DEI_VAL(val->dei)          |
               VTSS_F_REW_MAP_VAL_B_PCP_VAL(val->pcp)          |
               VTSS_F_REW_MAP_VAL_B_TC_VAL(val->mpls_tc));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_egress_map_hw_update(vtss_state_t *vtss_state,
                                            const u16     res,
                                            const u16     ix,
                                            const int     len,
                                            const void   *const map)
{
    u32 col, row, dpl;
    const vtss_qos_egress_map_t *const m = map;

    VTSS_D("Enter");
    VTSS_D("Resource %u, row (ix) %u, length %u", res, ix, len);

    if (m) {
        switch (m->key) {
        case VTSS_QOS_EGRESS_MAP_KEY_COSID:
            /* Add 1 row with COSID values */
            for (col = 0; col < 8; col++) {
                VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix, col, &m->maps.cosid[col]));
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL:
            /* Add 4 rows with COSID/DPL values */
            for (row = 0; row < 4; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.cosid_dpl[col][row]));
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP:
            /* Add 8 rows with DSCP values */
            for (row = 0; row < 8; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.dscp[(row * 8) + col]));
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL:
            /* Add 32 rows with DSCP/DPL values */
            for (dpl = 0; dpl < 4; dpl++) {
                for (row = 0; row < 8; row++) {
                    for (col = 0; col < 8; col++) {
                        VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix + row + (dpl * 8), col, &m->maps.dscp_dpl[(row * 8) + col][dpl]));
                    }
                }
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC:
            /* Add 1 row with TC values */
            for (col = 0; col < 8; col++) {
                VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix, col, &m->maps.mpls_tc[col]));
            }
            break;
        case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL:
            /* Add 4 rows with MPLS TC/DPL values */
            for (row = 0; row < 4; row++) {
                for (col = 0; col < 8; col++) {
                    VTSS_RC(fa_qos_egress_map_hw_entry_update(vtss_state, res, ix + row, col, &m->maps.mpls_tc_dpl[col][row]));
                }
            }
            break;
        default:
            VTSS_E("Invalid ingress map key: %u!", m->key);
            return VTSS_RC_ERROR;
        }
    } else {
        /* Set rows to zero */
        for (row = 0; row < len; row++) {
            for (col = 0; col < 8; col++) {
                if (res == 0) { // Resource A
                    REG_WR(VTSS_REW_MAP_VAL_A(((ix + row) * 8) + col), 0);
                } else { // Resource B
                    REG_WR(VTSS_REW_MAP_VAL_B(((ix + row) * 8) + col), 0);
                }
            }
        }
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_egress_map_hw_copy(vtss_state_t *vtss_state,
                                          const u16    res,
                                          const u16    src,
                                          const u16    dst,
                                          const int    len)
{
    u32 col, row, val;

    VTSS_D("Enter");
    VTSS_D("Resource %u, copying from row %u to row %u, length %d", res, src, dst, len);

    for (row = 0; row < len; row++) {
        for (col = 0; col < 8; col++) {
            if (res == 0) { // Resource A
                REG_RD(VTSS_REW_MAP_VAL_A(((src + row) * 8) + col), &val);
                REG_WR(VTSS_REW_MAP_VAL_A(((dst + row) * 8) + col), val);
            } else { // Resource B
                REG_RD(VTSS_REW_MAP_VAL_B(((src + row) * 8) + col), &val);
                REG_WR(VTSS_REW_MAP_VAL_B(((dst + row) * 8) + col), val);
            }
        }
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_egress_map_add(vtss_state_t *vtss_state, const vtss_qos_egress_map_t *const map)
{
    u8 flags = 0;

    if (map->action.pcp) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_PCP;
    }
    if (map->action.dei) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_DEI;
    }
    if (map->action.dscp) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_DSCP;
    }
    if (map->action.path) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_PATH;
    }
    if (map->action.mpls_tc) {
        flags |= VTSS_QOS_EGRESS_MAP_ACTION_MPLS_TC;
    }

    VTSS_D("Redirecting to AIL with egress map id %u, key %u", map->id, map->key);
    return vtss_cmn_qos_map_add(vtss_state, &vtss_state->qos.emap, map->id, map->key, flags, map);
}

static vtss_rc fa_qos_egress_map_del(vtss_state_t *vtss_state, const vtss_qos_egress_map_id_t id)
{
    VTSS_D("Redirecting to AIL with egress map id %u", id);
    return vtss_cmn_qos_map_del(vtss_state, &vtss_state->qos.emap, id);
}

static vtss_rc fa_qos_cpu_port_shaper_set(vtss_state_t *vtss_state, const vtss_bitrate_t rate)
{
    vtss_shaper_t cpu_shaper;

    VTSS_D("Enter");

    memset(&cpu_shaper, 0, sizeof(cpu_shaper));
    cpu_shaper.rate  = rate;       // kbps
    cpu_shaper.level = (4096 * 4); // 16 kbytes burst size
    cpu_shaper.eir   = VTSS_BITRATE_DISABLED;
    VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &cpu_shaper, 2, VTSS_CHIP_PORT_CPU_0, 0, 0));
    VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &cpu_shaper, 2, VTSS_CHIP_PORT_CPU_1, 0, 0));

    VTSS_D("Exit");
    return  VTSS_RC_OK;
}

static vtss_rc fa_qos_status_get(vtss_state_t *vtss_state, vtss_qos_status_t *status)
{
    u32 value;

    VTSS_D("Enter");
    /* Read and clear sticky register */
    REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY, &value);
    REG_WRM(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY,
            VTSS_F_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(0xFF),
            VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY);

    /* Detect storm events */
    status->storm = VTSS_BOOL(VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(value));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_qbv_conf_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_qbv_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_qbv_port_status_get(vtss_state_t              *vtss_state,
                                         const vtss_port_no_t       port_no,
                                         vtss_qos_qbv_port_status_t *const status)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_fp_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_fp_port_status_get(vtss_state_t              *vtss_state,
                                         const vtss_port_no_t      port_no,
                                         vtss_qos_fp_port_status_t *const status)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */
static void fa_debug_print_reg2bf(const vtss_debug_printf_t pr, u32 value, u32 len)
{
    u32 i;

    for (i = 0; i < len; i++) {
        pr("%s%u", i == 0 || (i % 8) ? "" : ".", value & (1 << (len - 1 - i)) ? 1 : 0);
    }
    pr("\n");
}

static vtss_rc fa_debug_qos_leak_chain(vtss_state_t              *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       const vtss_debug_info_t   *const info)
{
    u32                   layer, group, se, cnt, value;
    vtss_qos_leak_layer_t *ll;
    vtss_qos_leak_group_t *lg;

    vtss_debug_print_header(pr, "QoS Leak List Configuration");

    REG_RD(VTSS_HSCH_SYS_CLK_PER, &value);
    pr("SYS_CLK_PER_100PS: %u\n\n", VTSS_X_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(value));
    for (layer = 0; layer < VTSS_HSCH_LAYERS; layer++) {
        // Select layer to be accessed.
        REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer),
                VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER);

        ll = &vtss_state->qos.leak_conf.layer[layer];
        if (ll->entry == NULL) {
            continue; // Skip unused layer
        }
        for (group = 0; group < VTSS_HSCH_LEAK_LISTS; group++) {
            lg = &ll->group[group];
            se = lg->head.next;
            pr("Layer %u, leak group %u\n", layer, group);
            REG_RD(VTSS_HSCH_HSCH_TIMER_CFG(layer, group), &value);
            pr("%-32s: %8u\n", "LEAK_TIME", VTSS_X_HSCH_HSCH_TIMER_CFG_LEAK_TIME(value));
            REG_RD(VTSS_HSCH_HSCH_LEAK_CFG(layer, group), &value);
            pr("%-32s: %8u\n", "LEAK_FIRST", VTSS_X_HSCH_HSCH_LEAK_CFG_LEAK_FIRST(value));
            pr("%-32s: %8u\n", "LEAK_ERR", VTSS_X_HSCH_HSCH_LEAK_CFG_LEAK_ERR(value));
            pr("%-32s: %8u\n", "Resolution (kbps)", lg->resolution);
            pr("%-32s: %8u\n", "Max. rate (kbps)", lg->max_rate);
            pr("%-32s: %8u\n", "Current no. of SEs", lg->cur_ses);
            pr("%-32s: %8u\n", "Max. no. of SEs", lg->max_ses);
            if (lg->head.enabled) {
                u32 hw_next;
                /* Check for consistency with leak first in hw */
                REG_RD(VTSS_HSCH_HSCH_LEAK_CFG(layer, group), &value);
                hw_next = VTSS_X_HSCH_HSCH_LEAK_CFG_LEAK_FIRST(value);
                if (se != hw_next) {
                    pr("Error: se %u != first hw_next %u!\n", se, hw_next);
                }
                cnt = 0;
                while (1) {
                    cnt++;
                    if (se >= ll->entries) {
                        pr("Error: Se %u >= %u!\n", se, ll->entries);
                        break;
                    }
                    if (cnt > lg->max_ses) {
                        pr("Error: cnt %u > %u!\n", cnt, lg->max_ses);
                        break;
                    }
                    pr("%u<%u>%u ", ll->entry[se].prev, se, ll->entry[se].next);
                    /* Check for consistency with leak chain in hw */
                    if (layer == 3) { /* Queue shapers */
                        REG_RD(VTSS_HSCH_QSHP_CONNECT(se), &value);
                        hw_next = VTSS_X_HSCH_QSHP_CONNECT_SE_LEAK_LINK(value);
                    } else {
                        REG_RD(VTSS_HSCH_SE_CONNECT(se), &value);
                        hw_next = VTSS_X_HSCH_SE_CONNECT_SE_LEAK_LINK(value);
                    }
                    if (ll->entry[se].next != hw_next) {
                        pr("Error: ll->entry[se].next %u != hw_next %u!\n", se, hw_next);
                    }

                    if (se == ll->entry[se].next) { /* End of list? */
                        if (cnt != lg->cur_ses) {
                            pr("Error: cnt %u != cur_ses %u!\n", cnt, lg->cur_ses);
                        }
                        break;
                    } else {
                        se = ll->entry[se].next;
                    }
                }
            }
            pr("\n");
        }
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_qos_scheduler_element(vtss_state_t              *vtss_state,
                                              const vtss_debug_printf_t pr,
                                              const u32                 layer,
                                              const u32                 se)
{
    u32 value;

    // Select the respective [layer, se] to access
    REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer) |
            VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER |
            VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

    REG_RD(VTSS_HSCH_CIR_CFG(se), &value);
    pr("%-32s: %6u\n", "CIR_RATE", VTSS_X_HSCH_CIR_CFG_CIR_RATE(value));
    pr("%-32s: %6u\n", "CIR_BURST", VTSS_X_HSCH_CIR_CFG_CIR_BURST(value));
    REG_RD(VTSS_HSCH_EIR_CFG(se), &value);
    pr("%-32s: %6u\n", "EIR_RATE", VTSS_X_HSCH_EIR_CFG_EIR_RATE(value));
    pr("%-32s: %6u\n", "EIR_BURST", VTSS_X_HSCH_EIR_CFG_EIR_BURST(value));
    REG_RD(VTSS_HSCH_SE_CFG(se), &value);
    pr("%-32s: %6u\n", "SE_AVB_ENA", VTSS_X_HSCH_SE_CFG_SE_AVB_ENA(value));
    pr("%-32s: %6u\n", "SE_FRM_MODE", VTSS_X_HSCH_SE_CFG_SE_FRM_MODE(value));
    pr("%-32s: %6u\n", "SE_STOP", VTSS_X_HSCH_SE_CFG_SE_STOP(value));
    REG_RD(VTSS_HSCH_SE_DLB_SENSE(se), &value);
    pr("%-32s: %6u\n", "SE_DLB_PRIO_ENA", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_PRIO_ENA(value));
    pr("%-32s: %6u\n", "SE_DLB_PRIO", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_PRIO(value));
    pr("%-32s: %6u\n", "SE_DLB_DPORT_ENA", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_DPORT_ENA(value));
    pr("%-32s: %6u\n", "SE_DLB_DPORT", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_DPORT(value));
    pr("%-32s: %6u\n", "SE_DLB_SE_ENA", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_SE_ENA(value));

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_qos_ingress_mapping(vtss_state_t              *vtss_state,
                                         const vtss_debug_printf_t pr,
                                         const u32                 ix_start,
                                         const int                 length)
{
    u32  ix, col, value;
    int  len;
    char buf[32];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        pr("Index %u, (%u of %u)\n", ix, len + 1, length);
        pr("%-32s: PATH  TC  DP  COSID  QOS  DEI  PCP  DSCP\n", "");
        REG_RD(VTSS_ANA_CL_SET_CTRL(ix), &value);
        sprintf(buf, "    MAP_TBL[%u]:SET_CTRL", ix);
        pr("%-32s: %4u  %2u  %2u  %5u  %3u  %3u  %3u  %4u\n",
               buf,
               VTSS_X_ANA_CL_SET_CTRL_PATH_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_TC_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_DP_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_COSID_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_QOS_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_DEI_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_PCP_ENA(value),
               VTSS_X_ANA_CL_SET_CTRL_DSCP_ENA(value));
        pr("%-32s: FWD_DIS  PATH_COLOR  PATH_COSID  TC  DP  COSID  QOS  DEI  PCP  DSCP\n", "");
        for (col = 0; col < 8; col++) {
            REG_RD(VTSS_ANA_CL_MAP_ENTRY(ix, col), &value);
            sprintf(buf, "    MAP_TBL[%u]:MAP_ENTRY[%u]", ix, col);
            pr("%-32s: %7u  %10u  %10u  %2u  %2u  %5u  %3u  %3u  %3u  %4u\n",
               buf,
               VTSS_X_ANA_CL_MAP_ENTRY_FWD_DIS(value),
               VTSS_X_ANA_CL_MAP_ENTRY_PATH_COLOR_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_PATH_COSID_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_TC_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_DP_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_COSID_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_QOS_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_DEI_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_PCP_VAL(value),
               VTSS_X_ANA_CL_MAP_ENTRY_DSCP_VAL(value));
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_qos_egress_mapping(vtss_state_t              *vtss_state,
                                        const vtss_debug_printf_t pr,
                                        const u32                 res,
                                        const u32                 ix_start,
                                        const int                 length)
{
    u32  ix, col, addr, value;
    int  len;
    char buf[32];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        sprintf(buf, "Index %u, (%u of %u)", ix, len + 1, length);
        pr("%-32s: OAM_COLOR  OAM_COSID  TC  DSCP  DEI  PCP\n", buf);
        for (col = 0; col < 8; col++) {
            addr = (ix * 8) + col;
            if (res == 0) { // Resource A
                REG_RD(VTSS_REW_MAP_VAL_A(addr), &value);
                sprintf(buf, "    MAP_RES_A[%u]:MAP_VAL_A", addr);
                pr("%-32s: %9u  %9u  %2u  %4u  %3u  %3u\n",
                   buf,
                   VTSS_X_REW_MAP_VAL_A_OAM_COLOR(value),
                   VTSS_X_REW_MAP_VAL_A_OAM_COSID(value),
                   VTSS_X_REW_MAP_VAL_A_TC_VAL(value),
                   VTSS_X_REW_MAP_VAL_A_DSCP_VAL(value),
                   VTSS_X_REW_MAP_VAL_A_DEI_VAL(value),
                   VTSS_X_REW_MAP_VAL_A_PCP_VAL(value));
            } else { // Resource B
                REG_RD(VTSS_REW_MAP_VAL_B(addr), &value);
                sprintf(buf, "    MAP_RES_B[%u]:MAP_VAL_B", addr);
                pr("%-32s: %9u  %9u  %2u  %4u  %3u  %3u\n",
                   buf,
                   VTSS_X_REW_MAP_VAL_B_OAM_COLOR(value),
                   VTSS_X_REW_MAP_VAL_B_OAM_COSID(value),
                   VTSS_X_REW_MAP_VAL_B_TC_VAL(value),
                   VTSS_X_REW_MAP_VAL_B_DSCP_VAL(value),
                   VTSS_X_REW_MAP_VAL_B_DEI_VAL(value),
                   VTSS_X_REW_MAP_VAL_B_PCP_VAL(value));
            }
        }
    }

    return VTSS_RC_OK;
}

static void fa_debug_qos_mapping(vtss_state_t              *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info,
                                 const vtss_qos_map_adm_t  *const m)
{
    u32 i, res;

    for (res = 0; res < VTSS_QOS_MAP_RESOURCES; res++) {
        char buf[64];
        if (m->ix[res].entry == NULL) {
            continue; /* Resource not present */
        }
        sprintf(buf, "QoS %s Mapping Tables Res %u", m->name, res);
        vtss_debug_print_header(pr, buf);
        if (info->full) {
            if (m->kind == VTSS_QOS_MAP_KIND_INGRESS) {
                for (i = 0; i < VTSS_QOS_INGRESS_MAP_ROWS; i++) {
                    (void) fa_debug_qos_ingress_mapping(vtss_state, pr, i, 1);
                }
            } else {
                for (i = 0; i < VTSS_QOS_EGRESS_MAP_ROWS; i++) {
                    (void) fa_debug_qos_egress_mapping(vtss_state, pr, res, i, 1);
                }
            }
        } else {
            int  len;
            BOOL empty = TRUE;

            i = 0;
            while (i < m->ix[res].free) {
                len = m->key2len(m->ix[res].entry[i].key);
                if (m->ix[res].entry[i].id != VTSS_QOS_MAP_ID_NONE) {
                    if (m->kind == VTSS_QOS_MAP_KIND_INGRESS) {
                        (void) fa_debug_qos_ingress_mapping(vtss_state, pr, i, len);
                    } else {
                        (void) fa_debug_qos_egress_mapping(vtss_state, pr, res, i, len);
                    }
                    empty = FALSE;
                }
                if (len) {
                    i += len;
                } else {
                    pr("Error: ix[%u].entry[%u].key %d gives zero length!\n", res, i, m->ix[res].entry[i].key);
                    break;
                }
            }
            if (empty) {
                pr("No entries allocated!\n");
            }
            pr("Use 'full' to see all entries!\n");
        }
        pr("\n");
    }
}

static vtss_rc fa_debug_qos(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    vtss_port_no_t      port_no, chip_port;
    u32                 i, max_burst, min_token, value = 0, service_pol_set_idx = 0, div = 0;
    u64                 lb_clk_in_hz, min_rate, lowest_max_nxt;
    vtss_qos_lb_group_t *group, *group_nxt;
    BOOL                show_act, basics_act, ingr_mapping_act, gen_pol_act, service_pol_grp_act, service_pol_set_act, port_pol_act,
                        storm_pol_act, schedul_act, band_act, shape_act, leak_act, wred_act, tag_remark_act, egr_mapping_act;

    VTSS_D("has_action %u  action %u", info->has_action, info->action);

    show_act = basics_act = ingr_mapping_act = gen_pol_act = service_pol_grp_act = service_pol_set_act = port_pol_act =
    storm_pol_act = schedul_act = band_act = shape_act = leak_act = wred_act = tag_remark_act = egr_mapping_act = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show_act =             (info->action == 0)  ? TRUE : FALSE;
        basics_act =           (info->action == 1)  ? TRUE : FALSE;
        ingr_mapping_act =     (info->action == 2)  ? TRUE : FALSE;
        gen_pol_act =          (info->action == 3)  ? TRUE : FALSE;
        port_pol_act =         (info->action == 4)  ? TRUE : FALSE;
        storm_pol_act =        (info->action == 5)  ? TRUE : FALSE;
        schedul_act =          (info->action == 6)  ? TRUE : FALSE;
        band_act =             (info->action == 7)  ? TRUE : FALSE;
        shape_act =            (info->action == 8)  ? TRUE : FALSE;
        leak_act =             (info->action == 9)  ? TRUE : FALSE;
        wred_act =             (info->action == 10) ? TRUE : FALSE;
        tag_remark_act =       (info->action == 11) ? TRUE : FALSE;
        egr_mapping_act =      (info->action == 12) ? TRUE : FALSE;
        service_pol_grp_act =  (info->action == 13) ? TRUE : FALSE;
    }

    if (info->action > 13) { /* This potentially a Service policing set action */
        for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
            service_pol_set_act = (info->action / div == 14) ? TRUE : FALSE;
            if (service_pol_set_act) {
                break;
            }
        }
        if (service_pol_set_act) {    /* Calculate the possible VOE/MIP index */
            service_pol_set_idx = info->action % div;
        }
        VTSS_D("service_pol_set_act %u  service_pol_set_idx %u  div %u",
                service_pol_set_act, service_pol_set_idx, div);
    }

    VTSS_D("show %u  basic %u  ingr_map %u  gen_pol %u  port_pol %u  storm_pol %u  schedul %u  band %u  shape %u  leak %u  wred  %u  tag_remark  %u  egr_map  %u",
            show_act, basics_act, ingr_mapping_act, gen_pol_act, port_pol_act, storm_pol_act, schedul_act, band_act, shape_act, leak_act, wred_act, tag_remark_act, egr_mapping_act);

    if (show_act) {
        pr("OAM Debug Group action:\n");
        pr("    0:      Show possible actions\n");
        pr("    1:      Print Basic configuration\n");
        pr("    2:      Print Ingress mapping configuration\n");
        pr("    3:      Print General policing configurations\n");
        pr("    4:      Print Port policing configurations\n");
        pr("    5:      Print Storm Policing configurations\n");
        pr("    6:      Print Scheduling hierarchy configurations\n");
        pr("    7:      Print Bandwidth distribution configurations\n");
        pr("    8:      Print Shapers configurations\n");
        pr("    9:      Print Leak chain configurations\n");
        pr("    10:     Print WRED configurations\n");
        pr("    11:     Print Tag remarking configurations\n");
        pr("    12:     Print Egress mapping configurations\n");
        pr("    13:     Print Service policing group configurations\n");
        pr("    14XXXX: Print Service policing set XXXX configurations\n");
        pr("\n");
    }

    if (!info->has_action || basics_act) { /* Basic configuration must be printed */
        vtss_debug_print_header(pr, "QoS basic classification (ingress) configuration");

        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 dei, pcp, class_ct = 0, dpl_ct = 0;
            char class_buf[40], dpl_buf[40];
            if (!info->port_list[port_no]) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            REG_RD(VTSS_ANA_CL_VLAN_CTRL(chip_port), &value);
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            pr("%-32s: %2u\n", "PORT_PCP", VTSS_X_ANA_CL_VLAN_CTRL_PORT_PCP(value));
            pr("%-32s: %2u\n", "PORT_DEI", VTSS_X_ANA_CL_VLAN_CTRL_PORT_DEI(value));
            REG_RD(VTSS_ANA_CL_QOS_CFG(chip_port), &value);
            pr("%-32s: %2u\n", "DEFAULT_QOS_VAL", VTSS_X_ANA_CL_QOS_CFG_DEFAULT_QOS_VAL(value));
            pr("%-32s: %2u\n", "PCP_DEI_QOS_ENA", VTSS_X_ANA_CL_QOS_CFG_PCP_DEI_QOS_ENA(value));
            pr("%-32s: %2u\n", "DSCP_TRANSLATE_ENA", VTSS_X_ANA_CL_QOS_CFG_DSCP_TRANSLATE_ENA(value));
            pr("%-32s: %2u\n", "DSCP_QOS_ENA", VTSS_X_ANA_CL_QOS_CFG_DSCP_QOS_ENA(value));
            pr("%-32s: %2u\n", "DEFAULT_DP_VAL", VTSS_X_ANA_CL_QOS_CFG_DEFAULT_DP_VAL(value));
            pr("%-32s: %2u\n", "PCP_DEI_DP_ENA", VTSS_X_ANA_CL_QOS_CFG_PCP_DEI_DP_ENA(value));
            pr("%-32s: %2u\n", "DSCP_DP_ENA", VTSS_X_ANA_CL_QOS_CFG_DSCP_DP_ENA(value));
            pr("%-32s: %2u\n", "DSCP_REWR_MODE_SEL", VTSS_X_ANA_CL_QOS_CFG_DSCP_REWR_MODE_SEL(value));
            pr("%-32s: %2u\n", "DEFAULT_COSID_ENA", VTSS_X_ANA_CL_QOS_CFG_DEFAULT_COSID_ENA(value));
            pr("%-32s: %2u\n", "DEFAULT_COSID_VAL", VTSS_X_ANA_CL_QOS_CFG_DEFAULT_COSID_VAL(value));
            pr("%-32s:\n", "PCP_DEI_MAP_CFG (8 * DEI + PCP)");
            for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
                for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
                    const char *delim = (pcp == VTSS_PCP_START) ? " | " : ",";
                    REG_RD(VTSS_ANA_CL_PCP_DEI_MAP_CFG(chip_port, (8 * dei + pcp)), &value);
                    class_ct += snprintf(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                        VTSS_X_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(value));
                    dpl_ct   += snprintf(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
                                        VTSS_X_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_DP_VAL(value));
                }
            }
            pr("%-32s: %s\n", "    PCP_DEI_QOS_VAL", class_buf);
            pr("%-32s: %s\n", "    PCP_DEI_DP_VAL", dpl_buf);
            pr("\n");
        }
        pr("Global configuration:\n");
        pr("---------------------\n");
        pr("DSCP configuration:\n");
        pr("DSCP TRANSLATE_VAL TRUST_ENA QOS_VAL DP_VAL REWR_ENA\n");
        for (i = 0; i < 64; i++) {
            REG_RD(VTSS_ANA_CL_DSCP_CFG(i), &value);
            pr("%4u %13u %9u %7u %6u %8u\n",
            i,
            VTSS_X_ANA_CL_DSCP_CFG_DSCP_TRANSLATE_VAL(value),
            VTSS_X_ANA_CL_DSCP_CFG_DSCP_TRUST_ENA(value),
            VTSS_X_ANA_CL_DSCP_CFG_DSCP_QOS_VAL(value),
            VTSS_X_ANA_CL_DSCP_CFG_DSCP_DP_VAL(value),
            VTSS_X_ANA_CL_DSCP_CFG_DSCP_REWR_ENA(value));
        }
        pr("DSCP rewrite map:\n");
        pr("QoS DSCP_DP0 DSCP_DP1 DSCP_DP2 DSCP_DP3\n");
        for (i = 0; i < 8; i++) {
            u32 qos_dp0, qos_dp1, qos_dp2, qos_dp3;
            REG_RD(VTSS_ANA_CL_QOS_MAP_CFG(i),      &qos_dp0);
            REG_RD(VTSS_ANA_CL_QOS_MAP_CFG(i +  8), &qos_dp1);
            REG_RD(VTSS_ANA_CL_QOS_MAP_CFG(i + 16), &qos_dp2);
            REG_RD(VTSS_ANA_CL_QOS_MAP_CFG(i + 24), &qos_dp3);
            pr("%3u %8u %8u %8u %8u\n",
            i,
            VTSS_X_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp0),
            VTSS_X_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp1),
            VTSS_X_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp2),
            VTSS_X_ANA_CL_QOS_MAP_CFG_DSCP_REWR_VAL(qos_dp3));
        }
        pr("\n");
    }

    if (!info->has_action || ingr_mapping_act) { /* Ingress mapping configuration must be printed */
        vtss_debug_print_header(pr, "QoS ingress mapping tables");
        fa_debug_qos_mapping(vtss_state, pr, info, &vtss_state->qos.imap);
        pr("\n");
    }

    if (!info->has_action || gen_pol_act) { /* General policing configuration must be printed */
        vtss_debug_print_header(pr, "QoS Policing (general configuration)");
        REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG, &value);
        pr("%-32s: %4u\n", "POL_UPD_INT", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_UPD_INT_CFG_POL_UPD_INT(value));
        pr("\n");
    }

    if (!info->has_action || service_pol_grp_act) { /* Service policing group configuration must be printed */
        vtss_debug_print_header(pr, "QoS Service Policing");
        pr("LB Group configuration:\n");
        pr("-----------------------\n");
        pr("IDX             ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            pr("%10u", i);
        }
        pr("\n");
        pr("----------------%s%s%s%s%s%s%s%s%s%s\n", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------");
        pr("PUP_ENA         ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_CTRL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_PUP_CTRL_PUP_ENA(value));
        }
        pr("\n");
        pr("PUP_LB_DT       ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_CTRL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_PUP_CTRL_PUP_LB_DT(value));
        }
        pr("\n");
        pr("LBSET_START     ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_XLB_START(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_XLB_START_LBSET_START(value));
        }
        pr("\n");
        pr("PUP_INTERVAL    ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_INTERVAL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_PUP_INTERVAL_PUP_INTERVAL(value));
        }
        pr("\n");
        pr("THRES_SHIFT     ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_LBGRP_MISC(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_LBGRP_MISC_THRES_SHIFT(value));
        }
        pr("\n");
        pr("FRM_RATE_TOKENS ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_FRM_RATE_TOKENS(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_FRM_RATE_TOKENS_FRM_RATE_TOKENS(value));
        }
        pr("\n");
        pr("\n");

        pr("LB Group status:\n");
        pr("----------------\n");
        pr("IDX            ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            pr("%10u", i);
        }
        pr("\n");
        pr("---------------%s%s%s%s%s%s%s%s%s%s\n", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------", "----------");
        pr("PUP_ONGOING    ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_CTRL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_ONGOING(value));
        }
        pr("\n");
        pr("PUP_WAIT_ACK   ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_CTRL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_WAIT_ACK(value));
        }
        pr("\n");
        pr("PUP_LBSET_NEXT ");
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            REG_RD(VTSS_ANA_AC_SDLB_PUP_CTRL(i), &value);
            pr("%10u", VTSS_X_ANA_AC_SDLB_LBGRP_STATE_TBL_PUP_LBSET_NEXT(value));
        }
        pr("\n");
        pr("\n");

        pr("LB Group Table:\n");
        pr("---------------\n");
        pr("When a policer is created the group with the satisfying lowest max_rate is selected, giving the longest update interval and smallest granularity.\n");
        pr("That is why the min_rate (granularity) of a group is only theoretically, as the highest min_rate is still lower than the lowest max rate.\n");
        pr("The possible lowest rate in a group is the lowest max_rate (+1) in the next group.\n");
        pr("\n");
        pr("Token Count is equal to (rate * pup_int) / (clk_freq * 8) in a group.\n");
        pr("Token Count has a max value of 8190 (in register) that gives the maximum rate in a group.\n");
        pr("Token Count has a min value of 1 that gives the theoretically minimum rate and rate granularity in a group.\n");
        pr("Token Count has a largest value that is the burst size of the policer - up to max value (8190). This gives the maximum rate\n");
        pr("\n");
        pr("Rates are in bps.\n");
        pr("Update interval is in clock cycles.\n");
        pr("Burst sizes are in bytes.\n");
        pr("\n");
        pr("min_burst is the minimum burst size and the burst granularity of LBs in the group.\n");
        pr("max_burst is the maximum burst size of LBs in the group.\n");
        pr("min_rate is the theoretically minimum rate with Token Count = 1. This is the rate granularity in the group.\n");
        pr("max_rate(min) is the maximum rate with burst size == min_burst. Token Count = min_burst.\n");
        pr("max_rate(max) is the maximum rate with burst size >= 8190. Token Count = maximum value. \n");
        pr("min_token is the token count for the possible lowest rate in the group. This rate is higher than the lowest max_rate in next group\n");
        pr("pup_int is the update interval in the group.\n");
        pr("frame_size is the frame token size in case of frame based LB.\n");
        pr("lb_count is the current number of LBs in the group.\n");
        pr("lb_max is the maximum number of LBs in the group.\n");
        pr("\n");
        pr("idx  min_burst  max_burst  min_rate  max_rate(min)  max_rate(max)  min_token  pup_int  frame_size  lb_count  lb_max\n");
        /* Get the system clock in Hz */
        lb_clk_in_hz = lb_clk_in_hz_get(vtss_state);
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            group = &vtss_state->qos.lb_groups[i];
            max_burst = group->min_burst * 0x3FF;
            min_rate = lb_group_lb_min_rate_calc(lb_clk_in_hz, group->pup_interval);
            min_token = 1;
            if (i < (LB_GROUP_CNT - 1)) {   /* This is not the last group */
                group_nxt = &vtss_state->qos.lb_groups[i + 1];
                lowest_max_nxt = lb_group_lb_max_rate_calc(group_nxt->min_burst, lb_clk_in_hz, group_nxt->pup_interval);
                min_token = lb_group_lb_pup_token_calc(lowest_max_nxt + 1, lb_clk_in_hz, group->pup_interval); /* The lowest max rate (+1) of next group is possible lowest rate in this group */
            }
            pr("%-3u  %-9u  %-9u  %-8" PRIu64 "  %-13" PRIu64 "  %-13" PRIu64 "  %-9u  %-7u  %-10u  %-9u  %-6u\n",
               i, group->min_burst, max_burst, min_rate,
               lb_group_lb_max_rate_calc(group->min_burst, lb_clk_in_hz, group->pup_interval),
               lb_group_lb_max_rate_calc(max_burst, lb_clk_in_hz, group->pup_interval),
               min_token, group->pup_interval, group->frame_size, group->lb_set_count, ((group->pup_interval / 4) - 1));
        }
        pr("\n");
    }

    if ((!info->has_action && info->full) || (service_pol_set_act && ((div > 1) || info->full))) { /* Service policing LB set configuration must be printed. All sets are only printed if 'full' parameter is present */
        pr("LB Set Table:\n");
        pr("-------------------\n");
        for (i = 0; i < LB_SET_CNT; ++i) {
            if (service_pol_set_act && (div > 1) && (service_pol_set_idx != i)) {   /* A specific LB set must be printed - this is not the one */
                continue;
            }
            if ((vtss_state->qos.lb_set_grp_idx[i] < LB_SET_CNT) || (div > 1)) { /* Only print LB set in a group unless a specific LB set */
                pr("LB_SET %u\n", i);
                pr("%-32s: %4u\n", "lb_set_grp_idx ", vtss_state->qos.lb_set_grp_idx[i]);
                REG_RD(VTSS_ANA_AC_SDLB_PUP_TOKENS(i, 0), &value);
                pr("%-32s: %4u\n", "PUP_TOKENS[0] ", VTSS_X_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(value));
                REG_RD(VTSS_ANA_AC_SDLB_THRES(i, 0), &value);
                pr("%-32s: %4u\n", "THRES[0] ", VTSS_X_ANA_AC_SDLB_THRES_THRES(value));
                pr("%-32s: %4u\n", "THRES_HYS[0] ", VTSS_X_ANA_AC_SDLB_THRES_THRES_HYS(value));
                REG_RD(VTSS_ANA_AC_SDLB_INH_CTRL(i, 0), &value);
                pr("%-32s: %4u\n", "PUP_TOKENS_MAX[0] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(value));
                pr("%-32s: %4u\n", "INH_MODE[0] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_MODE(value));
                pr("%-32s: %4u\n", "INH_LB[0] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_LB(value));
                REG_RD(VTSS_ANA_AC_SDLB_PUP_TOKENS(i, 1), &value);
                pr("%-32s: %4u\n", "PUP_TOKENS[1] ", VTSS_X_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(value));
                REG_RD(VTSS_ANA_AC_SDLB_THRES(i, 1), &value);
                pr("%-32s: %4u\n", "THRES[1] ", VTSS_X_ANA_AC_SDLB_THRES_THRES(value));
                pr("%-32s: %4u\n", "THRES_HYST[1] ", VTSS_X_ANA_AC_SDLB_THRES_THRES_HYS(value));
                REG_RD(VTSS_ANA_AC_SDLB_INH_CTRL(i, 1), &value);
                pr("%-32s: %4u\n", "PUP_TOKENS_MAX[1] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(value));
                pr("%-32s: %4u\n", "INH_MODE[1] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_MODE(value));
                pr("%-32s: %4u\n", "INH_LB[1] ", VTSS_X_ANA_AC_SDLB_INH_CTRL_INH_LB(value));
                REG_RD(VTSS_ANA_AC_SDLB_XLB_NEXT(i), &value);
                pr("%-32s: %4u\n", "LBSET_NEXT ", VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBSET_NEXT(value));
                pr("%-32s: %4u\n", "LBGRP ", VTSS_X_ANA_AC_SDLB_XLB_NEXT_LBGRP(value));
                REG_RD(VTSS_ANA_AC_SDLB_INH_LBSET_ADDR(i), &value);
                pr("%-32s: %4u\n", "INH_LBSET_ADDR ", VTSS_X_ANA_AC_SDLB_INH_LBSET_ADDR_INH_LBSET_ADDR(value));
                REG_RD(VTSS_ANA_AC_SDLB_DLB_MISC(i), &value);
                pr("%-32s: %4u\n", "DLB_FRM_RATE_ENA ", VTSS_X_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA(value));
                pr("%-32s: %4u\n", "MARK_ALL_FRMS_RED_ENA ", VTSS_X_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_ENA(value));
                pr("%-32s: %4u\n", "DLB_FRM_ADJ ", VTSS_X_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ(value));
                REG_RD(VTSS_ANA_AC_SDLB_DLB_CFG(i), &value);
                pr("%-32s: %4u\n", "DROP_ON_YELLOW_ENA ", VTSS_X_ANA_AC_SDLB_DLB_CFG_DROP_ON_YELLOW_ENA(value));
                pr("%-32s: %4u\n", "DP_BYPASS_LVL ", VTSS_X_ANA_AC_SDLB_DLB_CFG_DP_BYPASS_LVL(value));
                pr("%-32s: %4u\n", "HIER_DLB_DIS ", VTSS_X_ANA_AC_SDLB_DLB_CFG_HIER_DLB_DIS(value));
                pr("%-32s: %4u\n", "ENCAP_DATA_DIS ", VTSS_X_ANA_AC_SDLB_DLB_CFG_ENCAP_DATA_DIS(value));
                pr("%-32s: %4u\n", "COLOR_AWARE_LVL ", VTSS_X_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL(value));
                pr("%-32s: %4u\n", "CIR_INC_DP_VAL ", VTSS_X_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL(value));
                pr("%-32s: %4u\n", "DLB_MODE ", VTSS_X_ANA_AC_SDLB_DLB_CFG_DLB_MODE(value));
                pr("%-32s: %4u\n", "TRAFFIC_TYPE_MASK ", VTSS_X_ANA_AC_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(value));
            }
        }
    }

    if (!info->has_action || port_pol_act) { /* Port policing configuration must be printed */
        vtss_debug_print_header(pr, "QoS Port Policing");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 pol_idx;
            if (!info->port_list[port_no]) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            REG_RD(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP(chip_port), &value);
            pr("%-32s: %4u\n", "PORT_PIPELINE_PT", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_PORT_PIPELINE_PT(value));
            pr("%-32s: %4u\n", "GAP_VALUE", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_GAP_GAP_VALUE(value));
            REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG(chip_port), &value);
            pr("%-32s: %4u\n", "FC_STATE", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_STATE(value));
            pr("%-32s: ", "FC_ENA");
            fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_FC_ENA(value), 4);
            REG_RD(VTSS_DSM_ETH_FC_CFG(chip_port), &value);
            pr("%-32s: %4u\n", "FC_ANA_ENA", VTSS_X_DSM_ETH_FC_CFG_FC_ANA_ENA(value));
            for (i = 0; i < VTSS_PORT_POLICERS; i++) {
                pol_idx = ((VTSS_PORT_POLICERS * chip_port) + i);
                pr("Policer %u:\n", i);
                REG_RD(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG(pol_idx), &value);
                pr("%-32s: %8u\n", "PORT_RATE", VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_PORT_RATE(value));
                REG_RD(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0(pol_idx), &value);
                pr("%-32s: %8u\n", "PORT_THRES0", VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0_PORT_THRES0(value));
                REG_RD(VTSS_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1(pol_idx), &value);
                pr("%-32s: %8u\n", "PORT_THRES1", VTSS_X_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1_PORT_THRES1(value));
                REG_RD(VTSS_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG(chip_port, i), &value);
                pr("%-32s: ", "CPU_QU_MASK");
                fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_CPU_QU_MASK(value), 8);
                pr("%-32s: %8u\n", "SERVICE_BYPASS_ENA", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_SERVICE_BYPASS_ENA(value));
                pr("%-32s: %8u\n", "DP_BYPASS_LVL", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_DP_BYPASS_LVL(value));
                pr("%-32s: %8u\n", "FRAME_RATE_ENA", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_FRAME_RATE_ENA(value));
                pr("%-32s: %8u\n", "NONCPU_TRAFFIC_ENA", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_NONCPU_TRAFFIC_ENA(value));
                pr("%-32s: %8u\n", "CPU_TRAFFIC_ENA", VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_LIMIT_CPU_TRAFFIC_ENA(value));
                pr("%-32s: ", "TRAFFIC_TYPE_MASK");
                fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_PORT_CTRL_POL_PORT_CFG_TRAFFIC_TYPE_MASK(value), 8);
            }
            pr("\n");
        }
        pr("Port policer sticky bits:\n");
        REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY, &value);
        pr("%-32s: %u\n", "POL_PORT_ACTIVE_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_ACTIVE_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_DROP_FWD_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_FWD_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_DROP_CPU_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_DROP_CPU_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_BYPASS_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_BYPASS_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_PT_BYPASS_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_PT_BYPASS_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_FC_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_STICKY(value));
        pr("%-32s: %u\n", "POL_PORT_FC_CLEAR_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_PORT_FC_CLEAR_STICKY(value));
        pr("\n");
    }

    if (!info->has_action || storm_pol_act) { /* Storm Policing configuration must be printed */
        vtss_debug_print_header(pr, "QoS Storm Policing");
        REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG, &value);
        pr("%-32s: %3u\n", "STORM_GAP_VALUE", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_GAP_VALUE(value));
        pr("%-32s: %3u\n", "STORM_FORCE_CLOSE", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_CLOSE(value));
        pr("%-32s: %3u\n", "STORM_FORCE_OPEN", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_STORM_FORCE_OPEN(value));
        for (i = 0; i < 8; i++) {
            pr("Policer %u:\n", i);
            REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG(i), &value);
            pr("%-32s: %8u\n", "STORM_RATE", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_RATE_CFG_STORM_RATE(value));
            REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG(i), &value);
            pr("%-32s: %8u\n", "STORM_THRES", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_THRES_CFG_STORM_THRES(value));
            REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL(i), &value);
            pr("%-32s: %8u\n", "STORM_FRAME_RATE_ENA", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_FRAME_RATE_ENA(value));
            pr("%-32s: ", "STORM_CPU_QU_MASK");
            fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_CPU_QU_MASK(value), 8);
            pr("%-32s: %8u\n", "STORM_LIMIT_NONCPU_TRAFFIC_ENA", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_NONCPU_TRAFFIC_ENA(value));
            pr("%-32s: %8u\n", "STORM_LIMIT_CPU_TRAFFIC_ENA", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_LIMIT_CPU_TRAFFIC_ENA(value));
            pr("%-32s: ", "STORM_TRAFFIC_TYPE_MASK");
            fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STORM_CTRL_STORM_TRAFFIC_TYPE_MASK(value), 8);
        }
        pr("Storm policer sticky bits:\n");
        REG_RD(VTSS_ANA_AC_POL_POL_ALL_CFG_POL_STICKY, &value);
        pr("%-32s: ", "POL_STORM_ACTIVE_STICKY");
        fa_debug_print_reg2bf(pr, VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_ACTIVE_STICKY(value), 8);
        pr("%-32s: %8u\n", "POL_STORM_DROP_FWD_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_FWD_STICKY(value));
        pr("%-32s: %8u\n", "POL_STORM_DROP_CPU_STICKY", VTSS_X_ANA_AC_POL_POL_ALL_CFG_POL_STICKY_POL_STORM_DROP_CPU_STICKY(value));
        pr("\n");
    }

    if (!info->has_action || schedul_act) { /* Scheduling hierarchy configuration must be printed */
        // Only show the scheduling hierarchy if HQoS is not present, otherwise use the HQoS debug cmd
        vtss_debug_print_header(pr, "QoS scheduler hierarchy (L0 SEs in normal mode)");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 l0_se;
            if (info->port_list[port_no] == 0) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            pr("Queue    SE  NEXT_LAYER  NEXT_IDX  NEXT_INP\n");
            for (i = 0; i < 8; i++) {
                l0_se = FA_HSCH_L0_SE(chip_port, i);
                REG_RD(VTSS_HSCH_HSCH_L0_CFG(l0_se), &value);
                pr("%5u  %4u  %10u  %8u  %8u\n",
                i,
                l0_se,
                VTSS_X_HSCH_HSCH_L0_CFG_NEXT_LAYER(value),
                VTSS_X_HSCH_HSCH_L0_CFG_NEXT_IDX(value),
                VTSS_X_HSCH_HSCH_L0_CFG_NEXT_INP(value));
            }
            pr("\n");
        }
        pr("\n");
    }

    if (!info->has_action || band_act) { /* Bandwidth distribution configuration must be printed */
        vtss_debug_print_header(pr, "QoS bandwidth distribution configuration");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 layer = 2, se, cost_ct = 0;
            char cost_buf[40];
            if (!info->port_list[port_no]) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            se = chip_port;
            pr("Port %2u (chip port %2u), layer %u, se %4u:\n", port_no, chip_port, layer, se);
            REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer) |
                VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(se),
                VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER |
                VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);
            REG_RD(VTSS_HSCH_SE_CFG(se), &value);
            pr("%-32s: %2u\n", "SE_DWRR_CNT", VTSS_X_HSCH_SE_CFG_SE_DWRR_CNT(value));
            pr("%-32s: %2u\n", "SE_DWRR_FRM_MODE", VTSS_X_HSCH_SE_CFG_SE_DWRR_FRM_MODE(value));
            for (i = VTSS_QUEUE_START; i < VTSS_QUEUE_END; i++) {
                const char *delim = (i == VTSS_QUEUE_START) ? "" : " ";
                REG_RD(VTSS_HSCH_DWRR_ENTRY(i), &value);
                cost_ct += snprintf(cost_buf + cost_ct, sizeof(cost_buf) - cost_ct, "%s%2u",
                                delim,
                                VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(value));
            }
            pr("%-32s: %s\n", "DWRR_COST", "C0 C1 C2 C3 C4 C5 C6 C7");
            pr("%-32s: %s\n", "", cost_buf);
    
            pr("\n");
        }
    }

    if (!info->has_action || shape_act) { /* Shapers configuration must be printed */
        vtss_debug_print_header(pr, "QoS Shapers");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 layer = 2, se;
            if (info->port_list[port_no] == 0) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            se = chip_port;
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            pr("Port shaper, layer %u, se %4u:\n", layer, se);
            fa_debug_qos_scheduler_element(vtss_state, pr, layer, se);
    
            layer = 0;
            for (i = 0; i < 8; i++) {
                se = FA_HSCH_L0_SE(chip_port, i);
                pr("Queue %u shaper, layer %u, se %4u:\n", i, layer, se);
                fa_debug_qos_scheduler_element(vtss_state, pr, layer, se);
            }
            pr("\n");
        }
        pr("Port CPU_0 (chip port %2u):\n", VTSS_CHIP_PORT_CPU_0);
        fa_debug_qos_scheduler_element(vtss_state, pr, 2, VTSS_CHIP_PORT_CPU_0);
        pr("\n");
        pr("Port CPU_1 (chip port %2u):\n", VTSS_CHIP_PORT_CPU_1);
        fa_debug_qos_scheduler_element(vtss_state, pr, 2, VTSS_CHIP_PORT_CPU_1);
        pr("\n");
    }

    if (!info->has_action || leak_act) { /* Leak chain configuration must be printed */
        // Leak (DLB shaper) chain configuration.
        fa_debug_qos_leak_chain(vtss_state, pr, info);
    }

    if (!info->has_action || wred_act) { /* WRED configuration must be printed */
        vtss_debug_print_header(pr, "QoS WRED configuration");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (!info->port_list[port_no]) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            REG_RD(VTSS_QRES_WRED_GROUP(chip_port), &value);
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            pr("%-32s: %u\n", "WRED_GROUP", VTSS_X_QRES_WRED_GROUP_WRED_GROUP(value));
            pr("\n");
        }
        pr("Global configuration:\n");
        pr("---------------------\n");
        pr("WRED profile configuration:\n");
        pr("WRED_GROUP  QOS_CLASS  DPL  WM_RED_LOW  WM_RED_HIGH\n");
        for (i = 0; i < VTSS_WRED_GROUP_CNT; i++) {
            u32 queue, dpl;
            for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
                for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                    REG_RD(VTSS_QRES_WRED_PROFILE((24 * i) + (8 * dpl) + queue), &value);
                    pr("%10u  %9u  %3u  %10u  %11u\n",
                    i,
                    queue,
                    dpl + 1,
                    VTSS_X_QRES_WRED_PROFILE_WM_RED_LOW(value),
                    VTSS_X_QRES_WRED_PROFILE_WM_RED_HIGH(value));
                }
            }
        }
        pr("\n");
    }

    if (!info->has_action || tag_remark_act) { /* Tag remarking configuration must be printed */
        vtss_debug_print_header(pr, "QoS tag remarking (egress) configuration");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            u32 i, pcp_de0, pcp_de1, dei_de0, dei_de1;
            u32 pcp_de0_ct = 0, pcp_de1_ct = 0, dei_de0_ct = 0, dei_de1_ct = 0;
            char pcp_de0_buf[40], pcp_de1_buf[40], dei_de0_buf[40], dei_de1_buf[40];
            if (!info->port_list[port_no]) {
                continue;
            }
            chip_port = VTSS_CHIP_PORT(port_no);
            REG_RD(VTSS_REW_PORT_VLAN_CFG(chip_port), &value);
            pr("Port %2u (chip port %2u):\n", port_no, chip_port);
            pr("%-32s: %2u\n", "PORT_PCP", VTSS_X_REW_PORT_VLAN_CFG_PORT_PCP(value));
            pr("%-32s: %2u\n", "PORT_DEI", VTSS_X_REW_PORT_VLAN_CFG_PORT_DEI(value));
            REG_RD(VTSS_REW_TAG_CTRL(chip_port), &value);
            pr("%-32s: %2u\n", "TAG_PCP_CFG", VTSS_X_REW_TAG_CTRL_TAG_PCP_CFG(value));
            pr("%-32s: %2u\n", "TAG_DEI_CFG", VTSS_X_REW_TAG_CTRL_TAG_DEI_CFG(value));
            for (i = VTSS_QUEUE_START; i < VTSS_QUEUE_END; i++) {
                const char *delim = (i == VTSS_QUEUE_START) ? " " : ",";
                REG_RD(VTSS_REW_PCP_MAP_DE0(port_no, i), &pcp_de0);
                REG_RD(VTSS_REW_PCP_MAP_DE1(port_no, i), &pcp_de1);
                REG_RD(VTSS_REW_DEI_MAP_DE0(port_no, i), &dei_de0);
                REG_RD(VTSS_REW_DEI_MAP_DE1(port_no, i), &dei_de1);
                pcp_de0_ct += snprintf(pcp_de0_buf + pcp_de0_ct, sizeof(pcp_de0_buf) - pcp_de0_ct, "%s%u",
                                delim,
                                VTSS_X_REW_PCP_MAP_DE0_PCP_DE0(pcp_de0));
                pcp_de1_ct += snprintf(pcp_de1_buf + pcp_de1_ct, sizeof(pcp_de1_buf) - pcp_de1_ct, "%s%u",
                                delim,
                                VTSS_X_REW_PCP_MAP_DE1_PCP_DE1(pcp_de1));
                dei_de0_ct += snprintf(dei_de0_buf + dei_de0_ct, sizeof(dei_de0_buf) - dei_de0_ct, "%s%u",
                                delim,
                                VTSS_X_REW_DEI_MAP_DE0_DEI_DE0(dei_de0));
                dei_de1_ct += snprintf(dei_de1_buf + dei_de1_ct, sizeof(dei_de1_buf) - dei_de1_ct, "%s%u",
                                delim,
                                VTSS_X_REW_DEI_MAP_DE0_DEI_DE0(dei_de1));
            }
            pr("%-32s:\n", "PCP_MAP_DEx[CL_QoS]");
            pr("%-32s: %s\n", "    PCP_DE0", pcp_de0_buf);
            pr("%-32s: %s\n", "    PCP_DE1", pcp_de1_buf);
            pr("%-32s:\n", "DEI_MAP_DEx[CL_QoS]");
            pr("%-32s: %s\n", "    DEI_DE0", dei_de0_buf);
            pr("%-32s: %s\n", "    DEI_DE1", dei_de1_buf);
            REG_RD(VTSS_REW_DSCP_MAP(chip_port), &value);
            pr("%-32s: %2u\n", "DSCP_UPDATE_ENA", VTSS_X_REW_DSCP_MAP_DSCP_UPDATE_ENA(value));
            pr("%-32s: %2u\n", "DSCP_REMAP_ENA", VTSS_X_REW_DSCP_MAP_DSCP_REMAP_ENA(value));
    
            pr("\n");
        }
        pr("Global configuration:\n");
        pr("---------------------\n");
        pr("DSCP remarking (legacy) configuration:\n");
        pr("DSCP DSCP_REMAP\n");
        for (i = 0; i < 64; i++) {
            REG_RD(VTSS_REW_DSCP_REMAP(i), &value);
            pr("%4u %10u\n",
            i,
            VTSS_X_REW_DSCP_REMAP_DSCP_REMAP(value));
        }
        pr("\n");
    }

    if (!info->has_action || egr_mapping_act) { /* Egress mapping configuration must be printed */
        vtss_debug_print_header(pr, "QoS egress mapping tables");
        fa_debug_qos_mapping(vtss_state, pr, info, &vtss_state->qos.emap);
        pr("\n");
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_qos_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_QOS, fa_debug_qos, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */
static vtss_rc fa_qos_init(vtss_state_t *vtss_state)
{
    VTSS_D("Enter");

    // Initialize policers
    VTSS_RC(fa_qos_policer_init(vtss_state));

    // Initialize shaper leak chains
    VTSS_RC(fa_qos_leak_list_init(vtss_state));

    // Initialize service LBs
    VTSS_RC(fa_qos_lb_init(vtss_state));

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_qos_state_t   *state = &vtss_state->qos;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->conf_set = fa_qos_conf_set;

        state->port_conf_set = vtss_cmn_qos_port_conf_set;
        state->port_conf_update = fa_qos_port_conf_set;

        state->qce_add = vtss_cmn_qce_add;
        state->qce_del = vtss_cmn_qce_del;

        state->ingress_map_add         = fa_qos_ingress_map_add;
        state->ingress_map_del         = fa_qos_ingress_map_del;
        state->ingress_map_vcap_update = fa_qos_ingress_map_vcap_update;
        state->ingress_map_hw_update   = fa_qos_ingress_map_hw_update;
        state->ingress_map_hw_copy     = fa_qos_ingress_map_hw_copy;

        state->egress_map_add          = fa_qos_egress_map_add;
        state->egress_map_del          = fa_qos_egress_map_del;
        state->egress_map_vcap_update  = fa_qos_egress_map_vcap_update;
        state->egress_map_hw_update    = fa_qos_egress_map_hw_update;
        state->egress_map_hw_copy      = fa_qos_egress_map_hw_copy;

        state->cpu_port_shaper_set = fa_qos_cpu_port_shaper_set;

        state->prio_count = FA_PRIOS;

        state->status_get = fa_qos_status_get;

        state->qbv_conf_set        = fa_qos_qbv_conf_set;
        state->qbv_port_conf_set   = fa_qos_qbv_port_conf_set;
        state->qbv_port_status_get = fa_qos_qbv_port_status_get;

        state->fp_port_conf_set   = fa_qos_fp_port_conf_set;
        state->fp_port_status_get = fa_qos_fp_port_status_get;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_qos_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA && VTSS_FEATURE_QOS */
