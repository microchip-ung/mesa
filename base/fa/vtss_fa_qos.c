// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_fa_cil.h"
#include "../ail/vtss_util.h"

#if defined(VTSS_ARCH_FA) && defined(VTSS_FEATURE_QOS)

/* Calculate Layer 0 Scheduler Element when using normal hierarchy */
#define FA_HSCH_L0_SE(port, queue) ((64 * port) + (8 * queue))

#define LB_PUP_TOKEN_MAX              (0x1FFF-1)        /* The MAX number of tokens to add each update. The value 0x1FFF is reserved for permanently open buckets */
#define LB_PUP_INTERVAL_MAX           0x7FFFF           /* The MAX updating interval */
#define LB_TOKENS_PER_FRAME_MAX       0x1FFF            /* The MAX frame size */
#define LB_THRES_MAX                  0x3FF             /* The MAX THRES value */
#define LB_THRES_SHIFT_MAX            0x1F              /* The MAX THRES_SHIFT value */
#define LB_XLB_NEXT_LBGRP_MAX         0x0F              /* The MAX LBGRP value */
#define LB_THRES_HYS_MIN              (LB_THRES_MAX+1)  /* The minimum bucket open hysteresis */
#define LB_THRES_HYS_NONE             0                 /* No hysteresis */
#define LB_2CYCLES_TYPE2_THRES_OFFSET 13                /* FA specific value */

static u64 lb_clk_in_hz;
static u64 lb_clk_in_hz_get(vtss_state_t *vtss_state)
{
    u32  clk_cfg, clk_period_in_100ps;
    u64  clk_in_hz;

    /* Read the nominal system clock period length in 100 ps */
    REG_RD(VTSS_HSCH_SYS_CLK_PER, &clk_cfg);
    clk_period_in_100ps = VTSS_X_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(clk_cfg);
    clk_in_hz = 10*1000*1000 / clk_period_in_100ps;
    clk_in_hz *= 1000;
    return(clk_in_hz);
}

static u64 lb_group_lb_min_rate_calc(u32 pup_interval)
{
    return VTSS_DIV64((u64)(1 * lb_clk_in_hz * 8), (u64)pup_interval);
}

static u64 lb_group_lb_max_rate_calc(u32 bs, u32 pup_interval)
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

static u64 lb_group_lb_pup_token_calc(u64 ir_in_bps, u32 pup_interval)
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
static vtss_rc lb_config(vtss_state_t *vtss_state, u32 grp_idx, u32 set_idx, u32 lb_idx, u32 *ir, u32 max_ir, u32 *bs, u32 bs_hyst, BOOL cf, BOOL frame_rate)
{
    vtss_qos_lb_group_t *group;
    u32                 i, pup_tokens, max_pup_tokens, bs_in_bytes, bs_hyst_in_bytes, thres, hyst, inh_mode, max_burst;
    u64                 ir_in_bps, max_ir_in_bps, max_rate, min_rate;

    VTSS_I("Enter grp_idx %u, set_idx %u lb_idx %u ir %u", grp_idx, set_idx, lb_idx, *ir);

    if (*ir == 0) {
        VTSS_D("No IR was requested");
        REG_WR(VTSS_ANA_AC_SDLB_PUP_TOKENS(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(0));
        REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(0), VTSS_M_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX);
        REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES(0), VTSS_M_ANA_AC_SDLB_THRES_THRES);
        REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES_HYS(0), VTSS_M_ANA_AC_SDLB_THRES_THRES_HYS);
        REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_INH_MODE(0), VTSS_M_ANA_AC_SDLB_INH_CTRL_INH_MODE);
        /* Write zero tokens and closed state */
        for (i = 0; i < 2; i++) {
            REG_WR(VTSS_ANA_AC_SDLB_TBL_ACC_VAL, i);
            REG_WR(VTSS_ANA_AC_SDLB_TBL_ACC_CTRL,
                   VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD(i ? 3 : 1) |
                   VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_CMD_EXEC(1) |
                   VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LBSET_ADDR(set_idx) |
                   VTSS_F_ANA_AC_SDLB_TBL_ACC_CTRL_TBL_LB_IDX(lb_idx));
        }
        return(VTSS_RC_OK);
    }
    if (grp_idx >= LB_GROUP_CNT) {
        VTSS_D("Invalid LB group index %u", grp_idx);
        return(VTSS_RC_ERROR);
    }
    group = &vtss_state->qos.lb_groups[grp_idx];

    ir_in_bps = (u64)*ir * 1000;
    max_ir_in_bps = (u64)max_ir * 1000;
    bs_in_bytes = *bs;
    bs_hyst_in_bytes = bs_hyst;
    if (frame_rate) {
       ir_in_bps = (u64)*ir * (u64)group->frame_size * 8;
       max_ir_in_bps = (u64)max_ir * (u64)group->frame_size * 8;
       bs_in_bytes = *bs * group->frame_size;
       bs_hyst_in_bytes = bs_hyst * group->frame_size;
    }

    max_burst = group->min_burst * 0x3FF;
    min_rate = lb_group_lb_min_rate_calc(group->pup_interval);

    /* Adjust bust size to fit into the group */
    if (bs_in_bytes < group->min_burst) {
        VTSS_D("Group %u.  Burst size %u is too low for this group - Burst size set to min of this group", grp_idx, bs_in_bytes);
        bs_in_bytes = group->min_burst;
    }
    if (bs_in_bytes > max_burst) {
        VTSS_D("Group %u.  Burst size %u is too high for this group", grp_idx, bs_in_bytes);
        bs_in_bytes = max_burst;
    }
    /* Now the maximun rate can be calculated based on the burst size */
    max_rate = lb_group_lb_max_rate_calc(bs_in_bytes, group->pup_interval);

    /* Adjust the information rate to fit into the group */
    if (ir_in_bps < min_rate) {
        VTSS_D("Group %u.  Information rate %" PRIu64 " is too low for this group (min_rate %" PRIu64 ")", grp_idx, ir_in_bps, min_rate);
        ir_in_bps = min_rate;
    }
    if (ir_in_bps > max_rate) {
        VTSS_D("Group %u.  Information rate %" PRIu64 " is too high for this group (max_rate %" PRIu64 ")", grp_idx, ir_in_bps, max_rate);
        ir_in_bps = max_rate;
    }

    /* Calculate the number of tokens required for this IR in this group (PUP_INTERVAL) */
    pup_tokens = lb_group_lb_pup_token_calc(ir_in_bps, group->pup_interval);

    // The following should NEVER trigger! The checking was done when selecting group.
    if ((pup_tokens == 0) && (ir_in_bps != 0)) {
        VTSS_D("Bucket %u cannot be added to group %u. Check flow parameters.", set_idx, grp_idx);
        return(VTSS_RC_ERROR);
    }
    if (pup_tokens > LB_PUP_TOKEN_MAX) {
        VTSS_D("Calculated pup tokens %u value exceeds max value", pup_tokens);
        return(VTSS_RC_ERROR);
    }

    /* Calculate the number of tokens required for this MAX IR in this group (PUP_INTERVAL) */
    max_pup_tokens = lb_group_lb_pup_token_calc(max_ir_in_bps, group->pup_interval);

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
    if (cf && (lb_idx == 0)) {    /* This is CIR LB and Coupling Flag - spilling into EIR LB */
        inh_mode = 2;
    }

    REG_WR(VTSS_ANA_AC_SDLB_PUP_TOKENS(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_PUP_TOKENS_PUP_TOKENS(pup_tokens));
    REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX(max_pup_tokens), VTSS_M_ANA_AC_SDLB_INH_CTRL_PUP_TOKENS_MAX);
    REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES(thres), VTSS_M_ANA_AC_SDLB_THRES_THRES);
    REG_WRM(VTSS_ANA_AC_SDLB_THRES(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_THRES_THRES_HYS(hyst), VTSS_M_ANA_AC_SDLB_THRES_THRES_HYS);
    REG_WRM(VTSS_ANA_AC_SDLB_INH_CTRL(set_idx, lb_idx), VTSS_F_ANA_AC_SDLB_INH_CTRL_INH_MODE(inh_mode), VTSS_M_ANA_AC_SDLB_INH_CTRL_INH_MODE);

    /* Revert the return values to interface */
    if (frame_rate) {
       ir_in_bps = ir_in_bps / (u64)group->frame_size * 8;
       bs_in_bytes = bs_in_bytes / group->frame_size;
    }
    *ir = (u32)(ir_in_bps / (u64)1000);
    *bs = bs_in_bytes;

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static BOOL bs_higher_in_next(vtss_state_t *vtss_state, u32 idx, u64 ir_in_bps, u32 cur_max_burst)
{
    i32                  i;
    vtss_qos_lb_group_t  *group;
    u32                  max_burst;
    u64                  min_rate;

    if (idx == 0) {
        return TRUE;
    }

    /* Find a group with higher max burst size where the requested information rate fit */
    for (i = (idx - 1); (i >= 0) && (i < LB_GROUP_CNT); i--) {
        group = &vtss_state->qos.lb_groups[i];
        min_rate = lb_group_lb_min_rate_calc(group->pup_interval);
        max_burst = group->min_burst * 0x3FF;
        if ((cur_max_burst < max_burst) && (ir_in_bps > min_rate)) {
            return TRUE;
        }
    }

    return FALSE;
}


/* Find best group for leaky bucket                              */
/* Choose the LB Group with the longest PUP_INTERVAL, that can support lb_rate while adding at most lb_thres tokens per PUP. */
/* ir in 1000 bit/s or f/s */
static vtss_rc lb_group_find(vtss_state_t *vtss_state, u32 ir, u32 bs, u32 bs_hyst, BOOL frame_rate, u32 *idx)
{
    i32                 i;
    u32                 pup_tokens, thres, bs_in_bytes, bs_hyst_in_bytes, max_burst;
    u64                 ir_in_bps, min_rate, max_rate;
    vtss_qos_lb_group_t *group;

    VTSS_D("Enter  ir %u  bs %u  frame_rate %u", ir, bs, frame_rate);

    ir_in_bps = (u64)ir * 1000;
    bs_in_bytes = bs;
    bs_hyst_in_bytes = bs_hyst;

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

        /* Calculate the maximum burt size and minimum information rate for this group */
        max_burst = group->min_burst * 0x3FF;
        min_rate = lb_group_lb_min_rate_calc(group->pup_interval);

        if (ir_in_bps < min_rate) {     /* Requested rate must be at least the minimum rate. Does not help to move on to next group */
            VTSS_D("Group %u.  Information rate %" PRIu64 " is too low for this group (min_rate %" PRIu64 ")", i, ir_in_bps, min_rate);
            ir_in_bps = min_rate;
        }
        if (bs_in_bytes < group->min_burst) {     /* Requested burst size must be at least the minimum burst size. Does not help to move on to next group */
            VTSS_D("Group %u.  Burst size %u is too low for this group - Burst size set to min of this group", i, bs_in_bytes);
            bs_in_bytes = group->min_burst;
        }
        if (bs_in_bytes > max_burst) {      /* Requested burst size is too big. It might be possible to go to next group */
            VTSS_D("Group %u.  Burst size %u is too high for this group", i, bs_in_bytes);
            /* Check if a group can be found with higher maximum burst size where the requested information rate fit */
            if (bs_higher_in_next(vtss_state, *idx, ir_in_bps, max_burst)) {
                continue;   /* Makes sense to go to next group */
            } else {
                VTSS_D("Have to stay in this group - Burst size set to max %u of this group", max_burst);
                bs_in_bytes = max_burst;    /* Have to stay in this group, so requested burst size must be max of this group */
            }
        }

        /* Now the maximum information rate of this group can be calculated based on burst size */
        max_rate = lb_group_lb_max_rate_calc(bs_in_bytes, group->pup_interval);
        if (ir_in_bps > max_rate) {     /* Check if the reqursted information rate is too high for this group */
            VTSS_D("Group %u.  Information rate %" PRIu64 " is too high for this group (max_rate %" PRIu64 ")", i, ir_in_bps, max_rate);
            if (i == 0) {   /* Have to stay in this group as it is the last */
                VTSS_D("Have to stay in this group - Information rate set to max %" PRIu64 " of this group", max_rate);
                ir_in_bps = max_rate;
            } else {
                continue;    /* Next group support higher rates. If burst size is too small in next group, it will be changed to min_bs */
            }
        }

        /* Check if PUP_TOKEN value fit into register */
        if ((pup_tokens = lb_group_lb_pup_token_calc(ir_in_bps, group->pup_interval)) > LB_PUP_TOKEN_MAX) {
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

        VTSS_D("Exit. Group %u was found for Information rate %" PRIu64 " and burst size %u.   Group min_burst %u  min_rate %" PRIu64 "  max_rate %" PRIu64 "  pup_interval %u", i, ir_in_bps, bs_in_bytes, group->min_burst, min_rate, max_rate, group->pup_interval);
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
    u64                 pup_interval, max_token;

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
    group->lb_set_count = 0;

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
        if (group->lb_set_count == 0) {
            VTSS_D("No LB in group");
            return(VTSS_RC_ERROR);
        }
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
    u32                  reg, sum, nxt_idx, i, mark_all_red = 0, drop_yellow = 0;
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
        VTSS_D("Cannot add LB %u to any group. Violation of Rule II.as sum is %u", lb_set_idx, sum);
        group->lb_set_count -= 1;
        return(VTSS_RC_ERROR);
    }

#if defined(VTSS_FEATURE_PSFP)
    mark_all_red = (conf->mark_all_red.enable ? 1 : 0);
    drop_yellow = (conf->drop_yellow ? 1 : 0);
    sum = 0;
    if (mark_all_red && conf->mark_all_red.value) {
        /* Force policer closed */
        conf->cir = 0;
        conf->eir = 0;
        sum = 1;
    }
    if (lb_set_idx < VTSS_EVC_POL_CNT) {
        vtss_state->l2.pol_status[lb_set_idx].mark_all_red = sum;
    }
    REG_WR(VTSS_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR,
           VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_LBSET(lb_set_idx) |
           VTSS_F_ANA_AC_SDLB_MARK_ALL_FRMS_RED_CLR_MARK_ALL_FRMS_RED_CLR_VLD(1));
#endif
    /* Configure the LB */
    /* Configure the per CIR and EIR related */
    VTSS_RC(lb_config(vtss_state, grp_idx, lb_set_idx, 0, &conf->cir, 0, &conf->cbs, LB_THRES_HYS_NONE, conf->cf, FALSE));  /* CIR */
    VTSS_RC(lb_config(vtss_state, grp_idx, lb_set_idx, 1, &conf->eir, 0, &conf->ebs, LB_THRES_HYS_NONE, conf->cf, FALSE));  /* EIR */

    /* Configure the CIR and EIR common */
    REG_WR(VTSS_ANA_AC_SDLB_DLB_MISC(lb_set_idx),
           VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_RATE_ENA(0) |
           VTSS_F_ANA_AC_SDLB_DLB_MISC_MARK_ALL_FRMS_RED_ENA(mark_all_red) |
           VTSS_F_ANA_AC_SDLB_DLB_MISC_DLB_FRM_ADJ(conf->line_rate ? 20 : 0));
    REG_WR(VTSS_ANA_AC_SDLB_DLB_CFG(lb_set_idx),
           VTSS_F_ANA_AC_SDLB_DLB_CFG_DROP_ON_YELLOW_ENA(drop_yellow) |
           VTSS_F_ANA_AC_SDLB_DLB_CFG_COLOR_AWARE_LVL(conf->cm ? 0 : 3) |
           VTSS_F_ANA_AC_SDLB_DLB_CFG_CIR_INC_DP_VAL(1) |
           VTSS_F_ANA_AC_SDLB_DLB_CFG_DLB_MODE(0) |
           VTSS_F_ANA_AC_SDLB_DLB_CFG_TRAFFIC_TYPE_MASK(3));

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
    /* Implementing Rule III in DS1110 */
    lb_group_add(vtss_state, 25000000000,     8192/1,         64,       0);    /*  25 G */
    lb_group_add(vtss_state, 15000000000,     8192/1,         64,       1);    /*  15 G */
    lb_group_add(vtss_state, 10000000000,     8192/1,         64,       2);    /*  10 G */
    lb_group_add(vtss_state,  5000000000,     8192/1,         64,       3);    /*   5 G */
    lb_group_add(vtss_state,  2500000000,     8192/1,         64,       4);    /* 2.5 G */
    lb_group_add(vtss_state,  1000000000,     8192/2,         64,       5);    /*   1 G */
    lb_group_add(vtss_state,   500000000,     8192/2,         64,       6);    /* 500 M */
    lb_group_add(vtss_state,   100000000,     8192/4,         64,       7);    /* 100 M */
    lb_group_add(vtss_state,    50000000,     8192/4,         64,       8);    /*  50 M */
    lb_group_add(vtss_state,     5000000,     8192/8,         64,       9);    /*  10 M */

    /* The LB LBGRP number is used to indicate if the LB is part of a group */
    for (i = 0; i < LB_SET_CNT; ++i) {
        vtss_state->qos.lb_set_grp_idx[i] = LB_GROUP_CNT;
    }

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_policer_init(vtss_state_t *vtss_state)
{
    u32 port;

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
                  // Not working: VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_PRIO_FORCE_INIT |
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_ACL_FORCE_INIT   |
                  VTSS_M_ANA_AC_POL_POL_ALL_CFG_POL_ALL_CFG_FORCE_INIT);

    /* Setup queue policer indexes */
    for (port = 0; port < VTSS_CHIP_PORTS; port++) {
        REG_WRM(VTSS_ANA_L2_PORT_DLB_CFG(port),
                VTSS_F_ANA_L2_PORT_DLB_CFG_QUEUE_DLB_IDX(VTSS_QUEUE_POL_IDX(port, 0)),
                VTSS_M_ANA_L2_PORT_DLB_CFG_QUEUE_DLB_IDX);
    }

    /* Enable ISDX lookup to make queue policer mapping work */
    REG_WRM_SET(VTSS_ANA_L2_FWD_CFG, VTSS_M_ANA_L2_FWD_CFG_ISDX_LOOKUP_ENA);

    /* Disable bundle policer */
    REG_WRM(VTSS_ANA_L2_FWD_CFG, 0, VTSS_M_ANA_L2_FWD_CFG_PORT_DEFAULT_BDLB_ENA);

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

    VTSS_D("Enter  lb_set_idx %u, enable %u", lb_set_idx, conf->enable);

    if (conf->type == VTSS_POLICER_TYPE_SINGLE) {
        /* Single bucket, disable EIR */
        conf->eir = 0;
        conf->ebs = 0;
        conf->cm = 0;
        conf->cf = 0;
    }

    /* Start removing the LB from any possible group */
    VTSS_RC(lb_group_lb_set_remove(vtss_state, lb_set_idx));

    if (conf->enable) { /* The LB is enabled. Find the suitable group */
        VTSS_RC(lb_group_find(vtss_state, conf->cir, conf->cbs, LB_THRES_HYS_NONE, FALSE, &grp_idx1));
        if (conf->eir != 0) {
            /* EIR present, create LB 2. In case of coupling, the max rate is the sum of CIR and EIR */
            VTSS_RC(lb_group_find(vtss_state, (conf->cf ? conf->cir : 0) + conf->eir, conf->ebs, LB_THRES_HYS_NONE, FALSE, &grp_idx2));
            grp_idx1 = MIN(grp_idx1, grp_idx2); // Smallest group (fastest update) is selected
        }
        VTSS_RC(lb_group_lb_set_add(vtss_state, grp_idx1, lb_set_idx, conf));
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

        VTSS_MEMSET(&dlb_conf, 0, sizeof(dlb_conf));
        dlb_conf.type = VTSS_POLICER_TYPE_SINGLE;
        dlb_conf.enable = (conf->rate == VTSS_BITRATE_DISABLED) ? FALSE : TRUE;
        dlb_conf.line_rate = 1;
        dlb_conf.cir = conf->rate;
        dlb_conf.cbs = conf->level;
        if (VTSS_RC_OK != vtss_fa_policer_conf_set(vtss_state, pol_idx, &dlb_conf)) {
            return VTSS_RC_ERROR;
        }
        /* The CIR and CBS value might have been changed in order to fit the Fireant LB group regime */
        conf->rate = dlb_conf.cir;
        conf->level = dlb_conf.cbs;
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

u32 vtss_fa_imap_key2clm(u16 imap_key, BOOL inner_tag)
{
    u32 key;

    switch (imap_key) {
    case VTSS_QOS_INGRESS_MAP_KEY_PCP:
        key = 4;
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
        key = (inner_tag ? 1 : 0);
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
        key = 6;
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
        key = 7;
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
        key = 3;
        break;
    default:
        key = 0;
        break;
    }
    return key;
}

static vtss_rc fa_qos_ingress_map_port_update(vtss_state_t         *vtss_state,
                                              const vtss_port_no_t port_no,
                                              const u16            id)
{
    u32 chip_port = VTSS_CHIP_PORT(port_no);
    u16 ix;
    u32 key;

    if (id < VTSS_QOS_INGRESS_MAP_IDS &&
        (ix = vtss_state->qos.imap.id.entry[id].ix) < VTSS_QOS_INGRESS_MAP_ROWS) {
        key = vtss_fa_imap_key2clm(vtss_state->qos.imap.ix[0].entry[ix].key, 0);
    } else {
        ix = 0;
        key = 15;
    }

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

    VTSS_D("Enter - layer %u, se %u, rate %u", layer, se, rate);

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
    u32                   cir, cbs;
    vtss_bitrate_t        resolution, frame_kbps;
    vtss_shaper_mode_t    mode;
    vtss_qos_leak_layer_t *ll = &vtss_state->qos.leak_conf.layer[layer];
    vtss_qos_leak_entry_t *le = &ll->entry[se];
    vtss_qos_leak_group_t *lg;

    VTSS_D("Enter - layer %u, se %u, rate %u, mode %u, dlb_sense_port %u, dlb_sense_qos %u!",
            layer, se, shaper->rate, shaper->mode, dlb_sense_port, dlb_sense_qos);

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
        if (shaper->mode != VTSS_SHAPER_MODE_FRAME) {
            VTSS_RC(fa_qos_leak_list_link(vtss_state, layer, se, shaper->rate, &resolution));

            cir = MIN(VTSS_BITMASK(17), VTSS_DIV_ROUND_UP(shaper->rate,  resolution));
            cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP(shaper->level, 4096));
            mode = shaper->mode;
        } else {
            /* This is Frame based shaping */

            /* Try with Low rate mode */
            /* Insert scheduler element in leak list based on frame_kbps */
            /* Call to fa_qos_leak_list_link() changes the le->group */
            frame_kbps = ((uint64_t)shaper->rate * 100000) / 1000;  /* Each frame uses 100000 tokens */
            VTSS_RC(fa_qos_leak_list_link(vtss_state, layer, se, frame_kbps, &resolution));
            lg = &ll->group[le->group];

            /* Uses 100000 tokens for every frame transmitted */
            /* At every leak timeout one token is taken - that is 0.00001 frame - it requires 100000 leak_time to send a frame */
            /* Calculate the frames per sec if cir is one */
            /* frame_time_ns = lg->leak_time * 100000; */
            /* frame_time_s = (lg->leak_time * 100000)/1000000000; */
            /* frame_per_sec = 1000000000/(lg->leak_time * 100000); */
            /* frame_per_sec = 10000/lg->leak_time; */
            /* Calculate the value for CIR */
            /* cir = shaper->rate / frame_per_sec; */
            cir = ((uint64_t)shaper->rate * lg->leak_time) / 10000;
            cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP((shaper->level * 10), 3));
            mode = 3;

            if (VTSS_BITMASK(17) < cir) {   /* Check if CIR fits into the register */
                /* Try with High rate mode. */
                /* Insert scheduler element in leak list based on frame_kbps */
                /* Call to fa_qos_leak_list_link() changes the le->group */
                frame_kbps = ((uint64_t)shaper->rate * 1000) / 1000; /* Each frame uses 1000 tokens */
                VTSS_RC(fa_qos_leak_list_unlink(vtss_state, layer, se));
                VTSS_RC(fa_qos_leak_list_link(vtss_state, layer, se, frame_kbps, &resolution));
                lg = &ll->group[le->group];

                /* Uses 1000 tokens for every frame transmitted */
                /* At every leak timeout one token is taken - that is 0.001 frame - it requires 1000 leak_time to send a frame */
                /* Calculate the frames per sec if cir is one */
                /* frame_time_ns = lg->leak_time * 1000; */
                /* frame_time_s = (lg->leak_time * 1000)/1000000000; */
                /* frame_per_sec = 1000000000/(lg->leak_time * 1000); */
                /* frame_per_sec = 1000000/lg->leak_time; */
                /* Calculate the value for CIR */
                /* cir = shaper->rate / frame_per_sec; */
                cir = ((uint64_t)shaper->rate * lg->leak_time) / 1000000;
                cbs = MIN(VTSS_BITMASK(6),  VTSS_DIV_ROUND_UP((shaper->level * 10), 328));
                mode = 2;
            }

            VTSS_D("cir %u  cbs %u  mode %u  leak_time %u", cir, cbs, mode, lg->leak_time);
            cir = MIN(VTSS_BITMASK(17), cir);
        }
        REG_WR(VTSS_HSCH_CIR_CFG(se),
               VTSS_F_HSCH_CIR_CFG_CIR_RATE(cir) |
               VTSS_F_HSCH_CIR_CFG_CIR_BURST(cbs));

        REG_WRM(VTSS_HSCH_SE_CFG(se),
                VTSS_F_HSCH_SE_CFG_SE_FRM_MODE(mode),
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

    VTSS_D("Enter - port_no: %u  chip_port %u", port_no, chip_port);
    for (queue = 0; queue < 8; queue++) {
        u32 se = FA_HSCH_L0_SE(chip_port, queue);
        VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &conf->shaper_queue[queue], layer, se, chip_port, queue));
        REG_WRM(VTSS_HSCH_SE_CFG(se),
                VTSS_F_HSCH_SE_CFG_SE_AVB_ENA(conf->shaper_queue[queue].credit_enable),
                VTSS_M_HSCH_SE_CFG_SE_AVB_ENA);
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_queue_cut_through_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                     q, sp, ct_ena = 0, port = VTSS_CHIP_PORT(port_no);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];
#endif

    VTSS_D("port_no: %u", port_no);
    switch (vtss_state->port.conf[port_no].speed) {
    case VTSS_SPEED_10M:
        sp = 1;
        break;
    case VTSS_SPEED_100M:
        sp = 2;
        break;
    case VTSS_SPEED_1G:
        sp = 3;
        break;
    case VTSS_SPEED_2500M:
        sp = 4;
        break;
    case VTSS_SPEED_5G:
        sp = 5;
        break;
    case VTSS_SPEED_10G:
        sp = 6;
        break;
    case VTSS_SPEED_25G:
        sp = 7;
        break;
    default:
        sp = 0;
        break;
    }
    for (q = 0; q < 8; q++) {
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        // If frame preemption is enabled, cut-through is disabled
        if (conf->enable_tx && conf->admin_status[q]) {
            continue;
        }
#endif
        if (vtss_state->qos.port_conf[port_no].cut_through_enable[q]) {
            ct_ena |= VTSS_BIT(q);
        }
    }
    REG_WRM(VTSS_XQS_FWD_CT_CFG(port),
            VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ISP(sp) |
            VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ESP(sp) |
            VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ENA(ct_ena),
            VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ISP |
            VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ESP |
            VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ENA);
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

#ifdef VTSS_FEATURE_QOS_WRED_V3
    // WRED group configuration.
    if (conf->wred_group > 2) {
        VTSS_E("Invalid WRED group: %u!", conf->wred_group);
        return VTSS_RC_ERROR;
    }
    REG_WR(VTSS_QRES_WRED_GROUP(chip_port),
           VTSS_F_QRES_WRED_GROUP_WRED_GROUP(conf->wred_group));
#endif
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
#ifdef VTSS_FEATURE_QOS_WRED_V3
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
#endif
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
    vtss_shaper_t  shaper;
    u32            port, queue, packet_rate, se;

    VTSS_D("Enter");
    VTSS_MEMSET(&shaper, 0, sizeof(shaper));
    shaper.rate  = rate;       // kbps
    shaper.level = (4096 * 4); // 16 kbytes burst size
    for (port = VTSS_CHIP_PORT_CPU_0; port <= VTSS_CHIP_PORT_CPU_1; port++) {
        /* CPU port shaper at layer 2 (kbps) */
        shaper.rate  = rate;       // kbps
        shaper.level = (4096 * 4); // 16 kbytes burst size
        VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &shaper, 2, port, 0, 0));

        /* CPU queue shapers at layer 0, 1 FPS corresponds to 100 kbps */
        for (queue = 0; queue < 8; queue++) {
            se = FA_HSCH_L0_SE(port, queue);
            packet_rate = vtss_state->packet.rx_conf.queue[queue].rate;
            shaper.rate  = (packet_rate == VTSS_PACKET_RATE_DISABLED ? VTSS_BITRATE_DISABLED : packet_rate * 100);
            shaper.level = 4096;
            VTSS_RC(vtss_fa_qos_shaper_conf_set(vtss_state, &shaper, 0, se, 0, 0));
            REG_WR(VTSS_HSCH_SE_CFG(se), VTSS_F_HSCH_SE_CFG_SE_FRM_MODE(3));
        }
    }
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

#define TAS_LIST_STATE_ADMIN       0
#define TAS_LIST_STATE_ADVANCING   1
#define TAS_LIST_STATE_PENDING     2
#define TAS_LIST_STATE_OPERATING   3
#define TAS_LIST_STATE_TERMINATING 4

#define TAS_LIST_IDX_NONE    0xFFFFFFFF
#define TAS_PROFILE_IDX_NONE 0xFFFFFFFF
#define TAS_ENTRY_IDX_NONE   0xFFFFFFFF

static u32 tas_profile_allocate(vtss_state_t *vtss_state,  const vtss_port_no_t port_no)
{
    u32                 profile_idx;
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    for (profile_idx = 0; profile_idx < VTSS_TAS_NUMBER_OF_PROFILES; ++profile_idx) {
        if (!tas_profiles[profile_idx].in_use) { /* Find a unused profile */
            break;
        }
    }
    if (profile_idx == VTSS_TAS_NUMBER_OF_PROFILES) {
        VTSS_D("No free TAS profile was found");
        return TAS_PROFILE_IDX_NONE;
    }

    tas_profiles[profile_idx].in_use = TRUE;
    tas_profiles[profile_idx].port_no = port_no;

    return profile_idx;
}

static vtss_rc tas_profile_free(vtss_state_t *vtss_state,  u32 profile_idx)
{
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    if (profile_idx >= VTSS_TAS_NUMBER_OF_PROFILES) {
        return VTSS_RC_ERROR;
    }

    tas_profiles[profile_idx].in_use = FALSE;

    return VTSS_RC_OK;
}

static u32 tas_list_allocate(vtss_state_t *vtss_state,  u32 length)
{
    u32                     blocks, req_blocks, list_idx, row_idx, slot_cnt, block_idx = VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW;
    vtss_tas_entry_row_t    *row;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_entry_row_t    *tas_entry_rows = vtss_state->qos.tas.tas_entry_rows;
    vtss_tas_entry_block_t  (*tas_entry_blocks)[VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW] = vtss_state->qos.tas.tas_entry_blocks;

    VTSS_D("Enter length %u", length);

    /* Find the list */
    for (list_idx = 0; list_idx < VTSS_TAS_NUMBER_OF_LISTS; ++list_idx) {
        if (!tas_lists[list_idx].in_use) { /* Find a unused list */
            break;
        }
    }
    if (list_idx == VTSS_TAS_NUMBER_OF_LISTS) {
        VTSS_D("No free TAS list was found");
        return TAS_LIST_IDX_NONE;
    }

    /* Find the required entries for list */

    /* Calculate the required allocated entries in blocks. Minimum 1 block. Maximum VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW blocks */
    req_blocks = (length/VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK) + (((length%VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK) != 0) ? 1 : 0);
    /* Required blocks must be the size of a slot in a row. This must be 1-2-4 - ... - VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW blocks */
    for (blocks = 1; blocks <= VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW; blocks <<= 1) {
        if (req_blocks <= blocks) {
            req_blocks = blocks;
            break;
        }
    }
    if (blocks > VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW) {
        req_blocks = VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW;
    }

    /* Find the empty slot in a row */
    for (row_idx = 0; row_idx < VTSS_TAS_NUMBER_OF_ROWS; ++row_idx) {   /* Find a suitable row of blocks */
        row = &tas_entry_rows[row_idx];
        slot_cnt = (row->slot_size == 0) ? 0 : VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW/row->slot_size; /* Number of slots in this row */
        if ((row->in_use == 0) || ((row->in_use < slot_cnt) && (row->slot_size == req_blocks))) { /* A row can be used if empty or not full and the slot size match the required allocate blocks */
            if (row->in_use == 0) { /* This row is empty, take first slot */
                block_idx = 0;  /* Indicate that the first slot in in this row is in use */
            } else {    /* This row is not empty, find an empty slot */
                for (block_idx = 0; block_idx < VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW; ++block_idx) {   /* Find an empty slot in the row */
                    if (!tas_entry_blocks[row_idx][block_idx].in_use) {
                        break;
                    }
                }
            }
            break; /* The empty slot is found - break */
        }
    }

    if (block_idx < VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW) { /* An empty slot was found */
        tas_entry_blocks[row_idx][block_idx].in_use = TRUE; /* Indicate that the slot in the row is in use */
        row->in_use += 1;               /* Increment number of slots in use in the row */
        row->slot_size = req_blocks;    /* Give row its slot size */
        tas_lists[list_idx].in_use = TRUE; /* The found list is now in use */
        tas_lists[list_idx].entry_idx = ((row_idx * VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW) + block_idx) * VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK; /* Calculate entry index for this list */
    } else {
        VTSS_D("No free entry slot was found in any row");
        return TAS_LIST_IDX_NONE;
    }

    VTSS_D("Exit list_idx %u", list_idx);

    return list_idx;
}

static vtss_rc tas_list_free(vtss_state_t *vtss_state,  u32 list_idx)
{
    u32                     entry_idx, row_idx, block_idx, block_num;
    vtss_tas_list_t         *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_tas_entry_row_t    *tas_entry_rows = vtss_state->qos.tas.tas_entry_rows;
    vtss_tas_entry_block_t  (*tas_entry_blocks)[VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW] = vtss_state->qos.tas.tas_entry_blocks;

    if (list_idx >= VTSS_TAS_NUMBER_OF_LISTS) {
        return VTSS_RC_ERROR;
    }

    VTSS_D("Enter list_idx %u  entry_idx %u", list_idx, tas_lists[list_idx].entry_idx);

    if (tas_lists[list_idx].entry_idx < VTSS_TAS_NUMBER_OF_ENTRIES) { /* Check if the list has entries */
        entry_idx = tas_lists[list_idx].entry_idx;
        block_num = (entry_idx / VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK);
        row_idx = block_num / VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW;
        block_idx = block_num % VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW;

        tas_entry_blocks[row_idx][block_idx].in_use = FALSE; /* Free the slot in the row */
        if (tas_entry_rows[row_idx].in_use > 0) {
            tas_entry_rows[row_idx].in_use -= 1;    /* Decrement the number of used slots in the row */
            if (tas_entry_rows[row_idx].in_use == 0) {
                tas_entry_rows[row_idx].slot_size = 0;  /* The slot size of this empty row is unknown */
            }
        }
    }

    if (!tas_lists[list_idx].inherit_profile) {   /* Inherit profiles are not freed */
        (void)tas_profile_free(vtss_state, tas_lists[list_idx].profile_idx); /* Free any possible profile */
        (void)tas_profile_free(vtss_state, tas_lists[list_idx].hold_profile_idx); /* Free any possible hold MAC profile */
    }

    tas_lists[list_idx].in_use = FALSE; /* Free the list */
    tas_lists[list_idx].inherit_profile = FALSE;
    tas_lists[list_idx].profile_idx = TAS_PROFILE_IDX_NONE;
    tas_lists[list_idx].hold_profile_idx = TAS_PROFILE_IDX_NONE;
    tas_lists[list_idx].entry_idx = TAS_ENTRY_IDX_NONE;

    return VTSS_RC_OK;
}

static u8 tas_scheduled_calc(vtss_qos_tas_gce_t *gcl, u32 gcl_length)
{
    u32 i;
    u8  vector = 0;

    for (i = 0; i < gcl_length; ++i) {
        if (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC) { /* The MAC hold operation requires at least one open priority configured as 'scheduled' */
            vector |= vtss_bool8_to_u8(gcl[i].gate_open); 
        }
    }
    for (i = 0; i < gcl_length; ++i) {
        if (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC) { /* The MAC release operation requires all open priorities configured as not 'scheduled'*/
            vector &= ~vtss_bool8_to_u8(gcl[i].gate_open); 
        }
    }
    return vector;
}

static u8 tas_link_speed_calc(vtss_port_speed_t speed)
{
    switch (speed) {
        case VTSS_SPEED_UNDEFINED: return 0;
        case VTSS_SPEED_AUTO:      return 0;
        case VTSS_SPEED_10M:       return 1;
        case VTSS_SPEED_100M:      return 2;
        case VTSS_SPEED_1G:        return 3;
        case VTSS_SPEED_2500M:     return 4;
        case VTSS_SPEED_5G:        return 5;
        case VTSS_SPEED_10G:       return 6;
        case VTSS_SPEED_12G:       return 0;
        case VTSS_SPEED_25G:       return 7;
    }
    return 0;
}

static BOOL tas_time_stamp_diff(vtss_timestamp_t *ts, vtss_timestamp_t *ts_sub, u32 *diff)
{
    vtss_timestamp_t  diff_time;

    diff_time = *ts;
    if (vtss_timestampSub(&diff_time, ts_sub) != VTSS_RC_OK) {
        return FALSE;
    }

    /* Convert diff_time to u32 */
    *diff = diff_time.nanoseconds + diff_time.seconds * 1000000000; /* Without including 'sec_msb' the difference can be up to 136 years - must be enough */

    return TRUE;
}

static BOOL tas_trunk_port_conf_calc(vtss_qos_tas_port_conf_t  *current_port_conf,
                                     vtss_timestamp_t          *current_end_time,
                                     vtss_timestamp_t          *new_start_time,
                                     vtss_qos_tas_port_conf_t  *trunk_port_conf)
{
    /* Trunk list is calculated to start at the end of current list and to end cycle at new list start time */
    u32 trunk_duration, interval_sum = 0, i = 0;
    vtss_timestamp_t  trunk_duration_time;

    VTSS_MEMSET(trunk_port_conf, 0, sizeof(*trunk_port_conf));

    /* Calculate max duration of trunk list */
    trunk_duration_time = *new_start_time;
    if (vtss_timestampSub(&trunk_duration_time, current_end_time) != VTSS_RC_OK) {
        return FALSE;
    }

    /* Convert duration time to u32 */
    trunk_duration = trunk_duration_time.nanoseconds + trunk_duration_time.seconds * 1000000000; /* Without including 'sec_msb' the gap can be up to 136 years - must be enough */

    /* Copy the full current port configuration toe trunk */
    VTSS_MEMCPY(trunk_port_conf, current_port_conf, sizeof(*trunk_port_conf));

    /* Calculate the required number of GCL list entries in the trunk list */
    for (i = 0; i < current_port_conf->gcl_length; ++i) {
        if (trunk_duration >= (interval_sum + current_port_conf->gcl[i].time_interval)) {    /* Stop if the trunk list is getting longer than the required trunk duration */
            interval_sum += current_port_conf->gcl[i].time_interval;
        } else {
            break;
        }
    }

    /* Check if any entries got into the trunk list */
    if (i == 0) {
        return FALSE;
    }

    /* Set the length of the trunk list */
    trunk_port_conf->gcl_length = i;

    /* Set the base time of the trunk list to end of current list */
    trunk_port_conf->base_time = *current_end_time;

    /* Set the cycle time of the trunk list to the trunk duration. This might be longer than the trunk interval sum but then then last gate sate will be extended */
    trunk_port_conf->cycle_time = trunk_duration;

    return TRUE;
}

static void tas_stop_port_conf_calc(vtss_timestamp_t *current_end_time, BOOL *gate_open, vtss_qos_tas_port_conf_t *stop_port_conf)
{
    VTSS_MEMSET(stop_port_conf, 0, sizeof(*stop_port_conf));

    stop_port_conf->base_time = *current_end_time;
    stop_port_conf->cycle_time = 1000;
    stop_port_conf->gcl_length = 1;
    stop_port_conf->gcl[0].gate_operation = VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC;
    VTSS_MEMCPY(stop_port_conf->gcl[0].gate_open, gate_open, sizeof(stop_port_conf->gcl[0].gate_open));
    stop_port_conf->gcl[0].time_interval = 1000;
}

static vtss_rc tas_current_port_conf_calc(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_qos_tas_port_conf_t *current_port_conf)
{
    u32                   i, msb, profile_idx, store, value;
    u8                    gate_state, scheduled;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    vtss_tas_list_t       *tas_lists = vtss_state->qos.tas.tas_lists;

    VTSS_MEMSET(current_port_conf, 0, sizeof(*current_port_conf));
    if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
        return VTSS_RC_OK;
    }
    profile_idx = tas_lists[gcl_state->curr_list_idx].profile_idx;

    /* Store the currently selected list */
    REG_RD(VTSS_HSCH_TAS_CFG_CTRL, &store);

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(gcl_state->curr_list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);;

    /* Read list length and assure that the following entry access */
    REG_RD(VTSS_HSCH_TAS_LIST_CFG, &value);
    current_port_conf->gcl_length = VTSS_X_HSCH_TAS_LIST_CFG_LIST_LENGTH(value);

    /* Read the list elements */
    for (i = 0; i < current_port_conf->gcl_length; ++i) {
        /* Select the list entry */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(i), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM); /* The GCL_ENTRY_NUM is relative to the LIST_BASE_ADDR that is accessed latest  */

        /* Read the gate state */
        REG_RD(VTSS_HSCH_TAS_GCL_CTRL_CFG, &value);
        gate_state = VTSS_X_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(value);
        vtss_u8_to_bool8(gate_state, current_port_conf->gcl[i].gate_open);

        /* Read time interval */
        REG_RD(VTSS_HSCH_TAS_GCL_TIME_CFG, &current_port_conf->gcl[i].time_interval);

        /* Read scheduled configuration in the profile */
        REG_RD(VTSS_HSCH_TAS_PROFILE_CONFIG(profile_idx), &value);
        scheduled = VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(value);

        /* Calculate the gate operation */
        current_port_conf->gcl[i].gate_operation = VTSS_QOS_TAS_GCO_SET_GATE_STATES;
        if (scheduled & gate_state) {   /* If at least one open priority is configured as 'scheduled' it requires MAC hold operation */
            current_port_conf->gcl[i].gate_operation = VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC;
        }
        if ((scheduled & gate_state) == 0) {   /* If all open priority are configured as not 'scheduled' it requires MAC release operation */
            current_port_conf->gcl[i].gate_operation = VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC;
        }
    }

    REG_RD(VTSS_HSCH_TAS_BASE_TIME_NSEC, &current_port_conf->base_time.nanoseconds);
    REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, &current_port_conf->base_time.seconds);
    REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, &msb);
    current_port_conf->base_time.sec_msb = (u16)msb;
    REG_RD(VTSS_HSCH_TAS_CYCLE_TIME_CFG, &current_port_conf->cycle_time);

    /* Re-store the currently selected list */
    REG_WR(VTSS_HSCH_TAS_CFG_CTRL, store);

    return VTSS_RC_OK;
}

static void tas_list_state_write(vtss_state_t *vtss_state, u32 list_idx, u32 state)
{
    u32  i = 0, rc = 0, value, store;

    /* Store the currently selected list */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, &store) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Select the list */
    rc = (vtss_fa_wrm(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Write the TAS list state. Note that the written state must be read back with same value in oeder to assure correct write */
    do {
        rc = (vtss_fa_wrm(vtss_state, VTSS_HSCH_TAS_LIST_STATE, VTSS_F_HSCH_TAS_LIST_STATE_LIST_STATE(state), VTSS_M_HSCH_TAS_LIST_STATE_LIST_STATE) != VTSS_RC_OK) ? (rc + 1) : rc;
        rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_LIST_STATE, &value) != VTSS_RC_OK) ? (rc + 1) : rc;
        i++;
    } while((i < 10) && (VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(value) != state));

    /* Re-store the currently selected list */
    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, store) != VTSS_RC_OK) ? (rc + 1) : rc;

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }
}

static u32 tas_list_state_read(vtss_state_t *vtss_state, u32 list_idx)
{
    u32  store, value, state, rc = 0;

    /* Store the currently selected list */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, &store) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Select the list */
    rc = (vtss_fa_wrm(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Read the list state */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_LIST_STATE, &value) != VTSS_RC_OK) ? (rc + 1) : rc;
    state = VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(value);

    /* Re-store the currently selected list */
    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, store) != VTSS_RC_OK) ? (rc + 1) : rc;

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }

    return state;
}

static void tas_list_base_time_read(vtss_state_t *vtss_state, u32 list_idx, vtss_timestamp_t *base_time)
{
    u32  store, rc = 0, msb;

    /* Store the currently selected list */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, &store) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Select the list */
    rc = (vtss_fa_wrm(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Read the base time */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_BASE_TIME_NSEC, &base_time->nanoseconds) != VTSS_RC_OK) ? (rc + 1) : rc;
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, &base_time->seconds) != VTSS_RC_OK) ? (rc + 1) : rc;
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, &msb) != VTSS_RC_OK) ? (rc + 1) : rc;
    base_time->sec_msb = (u16)msb;

    /* Re-store the currently selected list */
    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, store) != VTSS_RC_OK) ? (rc + 1) : rc;

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }
}

static u32 tas_list_cycle_time_read(vtss_state_t *vtss_state, u32 list_idx)
{
    u32  store, rc = 0;
    u32 cycle_time;

    /* Store the currently selected list */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, &store) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Select the list */
    rc = (vtss_fa_wrm(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Read the cycle time */
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_CYCLE_TIME_CFG, &cycle_time) != VTSS_RC_OK) ? (rc + 1) : rc;

    /* Re-store the currently selected list */
    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_CFG_CTRL, store) != VTSS_RC_OK) ? (rc + 1) : rc;

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }

    return cycle_time;
}

static void tas_gate_state_write(vtss_state_t *vtss_state,  vtss_port_no_t port_no,  BOOL *gate_open)
{
    u32  rc = 0;
    vtss_port_no_t  chip_port = VTSS_CHIP_PORT(port_no);

    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_GATE_STATE_CTRL, 5040 + 64 + chip_port) != VTSS_RC_OK) ? (rc + 1) : rc;
    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_GATE_STATE, vtss_bool8_to_u8(gate_open)) != VTSS_RC_OK) ? (rc + 1) : rc;

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }
}

static void tas_gate_state_read(vtss_state_t *vtss_state,  vtss_port_no_t port_no,  BOOL *gate_open)
{
    u32  rc = 0, value;
    vtss_port_no_t  chip_port = VTSS_CHIP_PORT(port_no);

    rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_GATE_STATE_CTRL, 5040 + 64 + chip_port) != VTSS_RC_OK) ? (rc + 1) : rc;
    rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_GATE_STATE, &value) != VTSS_RC_OK) ? (rc + 1) : rc;

    vtss_u8_to_bool8(value, gate_open);

    if (rc != 0) {
        VTSS_E("Register operations failed");
    }
}

static BOOL tas_current_end_time_calc(vtss_state_t *vtss_state,  u32 current_list_idx,  vtss_timestamp_t *new_base_time,  vtss_timestamp_t *current_end_time)
{
    vtss_timestamp_t  current_base_time = {}, diff_base_time = {};
    u32               current_cycle_time;
    u64               diff_base_time_u64, current_elapse_time;

    VTSS_MEMSET(current_end_time, 0, sizeof(*current_end_time));

    if (current_list_idx != TAS_LIST_IDX_NONE) {
        /* Get the base time of current list */
        tas_list_base_time_read(vtss_state, current_list_idx, &current_base_time);

        /* Get the cycle time of current list */
        current_cycle_time = tas_list_cycle_time_read(vtss_state, current_list_idx);

        /* Calculate the end time of current list as this: */
        /* current_end_time = current_base_time + ((new_base_time - current_base_time) / current_cycle_time) * current_cycle_time */

        /* Calculate base time difference (new_base_time - current_base_time) */
        diff_base_time = *new_base_time;
        if (vtss_timestampSub(&diff_base_time, &current_base_time) != VTSS_RC_OK) {
            return FALSE;
        }

        /* Convert base time difference to u64 */
        diff_base_time_u64 = (u64)diff_base_time.nanoseconds + (u64)((u64)diff_base_time.seconds * (u64)1000000000); /* Without including 'sec_msb' the difference can be up to 136 years - must be enough */

        /* Calculate current elapse time (((new_base_time - current_base_time) / current_cycle_time) * current_cycle_time) */
        current_elapse_time = (diff_base_time_u64 / (u64)current_cycle_time) * (u64)current_cycle_time;

        /* Calculate the current_end_time = current_base_time + current_elapse_time */
        *current_end_time = current_base_time;
        if (vtss_timestampAddNano(current_end_time, current_elapse_time) != VTSS_RC_OK) {
            return FALSE;
        }
    }

    return TRUE;
}

static void tas_gcl_state_update(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                   next_state;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    if (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) {    /* Start next list is ongoing. Check if done */
        next_state = tas_list_state_read(vtss_state, gcl_state->next_list_idx);
        if ((next_state == TAS_LIST_STATE_OPERATING) ||
            (next_state == TAS_LIST_STATE_ADMIN)) {   /* Start next list is done or terminated */
            (void)tas_list_free(vtss_state, gcl_state->curr_list_idx);    /* Free any possible valid lists */
            (void)tas_list_free(vtss_state, gcl_state->trunk_list_idx);
            if (gcl_state->stop_ongoing) {  /* The next list is a stop list */
                (void)tas_list_free(vtss_state, gcl_state->next_list_idx);
                tas_list_state_write(vtss_state, gcl_state->next_list_idx, TAS_LIST_STATE_ADMIN);
                gcl_state->curr_list_idx = TAS_LIST_IDX_NONE;
            } else {
                gcl_state->curr_list_idx = gcl_state->next_list_idx;    /* Configure the possible new current list */
            }

            gcl_state->trunk_list_idx = TAS_LIST_IDX_NONE;
            gcl_state->next_list_idx = TAS_LIST_IDX_NONE;

            gcl_state->stop_ongoing = FALSE;        /* Stop of list is NOT ongoing */
            gcl_state->new_list_scheduled = FALSE;  /* Start of new list is NOT ongoing */
        }
    }
}

static vtss_rc tas_list_cancel(vtss_state_t *vtss_state, u32 list_index)
{
    tas_list_state_write(vtss_state, list_index, TAS_LIST_STATE_ADMIN);
    tas_list_free(vtss_state, list_index);

    return VTSS_RC_OK;
}

static vtss_rc hold_qmaxsdu_configure(vtss_state_t *vtss_state,  u32 profile_idx,  const vtss_port_no_t port_no)
{
    vtss_port_no_t  chip_port = VTSS_CHIP_PORT(port_no);
    u32 i, maxsdu;

    if (profile_idx == TAS_PROFILE_IDX_NONE) {
        return VTSS_RC_OK;
    }

    /* Calculate the Max SDU size based of FP fragment size */
    REG_RD(VTSS_DSM_PREEMPT_CFG(chip_port), &maxsdu);
    maxsdu += 1;    /* Must add 64 bytes as preemption must not be done if less than 64 bytes are remaining */

    /* Configure the hold MAC profile Max SDU size */
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        REG_WR(VTSS_HSCH_TAS_QMAXSDU_CFG(profile_idx, i), maxsdu);
    }

    return VTSS_RC_OK;
}

static vtss_rc gcl_port_profile_configure(vtss_state_t *vtss_state, u32 list_idx,
                                          vtss_qos_tas_gce_t *gcl, u32 gcl_length,
                                          const vtss_port_no_t port_no)
{
    u32  i, pindex;
    BOOL hold;
    u32  profile_idx = vtss_state->qos.tas.tas_lists[list_idx].profile_idx;
    u32  hold_profile_idx = vtss_state->qos.tas.tas_lists[list_idx].hold_profile_idx;
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    u32  fp_enable_tx = (vtss_state->qos.fp.port_conf[port_no].enable_tx ? 1 : 0);
#else
    u32  fp_enable_tx = FALSE;
#endif

    VTSS_D("gcl_port_profile_configure Enter  fp_enable_tx %u", fp_enable_tx);

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);

    /* Configure profile reference in the list elements */
    hold = FALSE;
    for (i = 0; i < gcl_length; ++i) {
        pindex = profile_idx;
        if (fp_enable_tx && (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC) && !hold) {
            /* FP is enabled and transition from no Hold MAC interval to Hold MAC interval */
            /* Use the specific profile for that with Max SDU size based on FP fragment size */
            pindex = hold_profile_idx;
        }
        if (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC) {
            /* Now in Hold MAC state */
            hold = TRUE;
        }
        if (gcl[i].gate_operation == VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC) {
            /* Now out of Hold MAC state */
            hold = FALSE;
        }

        /* Select the list entry */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(i), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM); /* The GCL_ENTRY_NUM is relative to the LIST_BASE_ADDR that is accessed latest  */

        /* Configure the profile reference */
        REG_WRM(VTSS_HSCH_TAS_GCL_CTRL_CFG, VTSS_F_HSCH_TAS_GCL_CTRL_CFG_PORT_PROFILE(pindex), VTSS_M_HSCH_TAS_GCL_CTRL_CFG_PORT_PROFILE);   /* Default scheduler element when HQoS is not present */
    }
    return VTSS_RC_OK;
}

static vtss_rc tas_list_start(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                              u32 list_idx, u32 obsolete_list_idx,
                              vtss_qos_tas_port_conf_t *port_conf, u32 startup_time)
{
    u32                 i, value, time_interval_sum = 0, scheduled, maxsdu;
    u32                 profile_idx = vtss_state->qos.tas.tas_lists[list_idx].profile_idx;
    u32                 hold_profile_idx = vtss_state->qos.tas.tas_lists[list_idx].hold_profile_idx;
    u32                 entry_idx = vtss_state->qos.tas.tas_lists[list_idx].entry_idx;
    u16                 *max_sdu  = vtss_state->qos.tas.port_conf[port_no].max_sdu;
    vtss_port_no_t      chip_port = VTSS_CHIP_PORT(port_no);

    vtss_timestamp_t    *base_time = &port_conf->base_time;
    u32                 cycle_time = port_conf->cycle_time;
    u32                 gcl_length = port_conf->gcl_length;
    vtss_qos_tas_gce_t  *gcl = port_conf->gcl;

    VTSS_D("Enter list_idx %u  startup_time %u  obsolete_list_idx %u  entry_idx %u  profile_idx %u    hold_profile_idx %u  chip_port %u",
           list_idx, startup_time, obsolete_list_idx, entry_idx, profile_idx, hold_profile_idx, chip_port);

    if (startup_time < 256) {
        VTSS_D("The Startup time %u must be at least 256 ns", startup_time);
        return VTSS_RC_ERROR;
    }

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);

    /* List must be in ADMIN state */
    REG_RD(VTSS_HSCH_TAS_LIST_STATE, &value);
    if (VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(value) != TAS_LIST_STATE_ADMIN) {
        VTSS_D("The TAS list is not in admin state");
        return VTSS_RC_ERROR;
    }

    /* Configure the list */
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_NSEC, base_time->nanoseconds);
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, base_time->seconds);
    REG_WR(VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, base_time->sec_msb);
    REG_WR(VTSS_HSCH_TAS_CYCLE_TIME_CFG, cycle_time);
    REG_WR(VTSS_HSCH_TAS_STARTUP_CFG, VTSS_F_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX((obsolete_list_idx != TAS_LIST_IDX_NONE) ? obsolete_list_idx : list_idx) |
                                      VTSS_F_HSCH_TAS_STARTUP_CFG_STARTUP_TIME(startup_time/256));
    REG_WR(VTSS_HSCH_TAS_LIST_CFG, VTSS_F_HSCH_TAS_LIST_CFG_LIST_LENGTH(gcl_length) |
                                   VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(0) |
                                   VTSS_F_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(entry_idx));

    /* Configure the profile(s) */
    /* The profile for "normal" guard band - not Hold MAC guard band */
    scheduled = tas_scheduled_calc(gcl, gcl_length);
    REG_WR(VTSS_HSCH_TAS_PROFILE_CONFIG(profile_idx),
                                        VTSS_F_HSCH_TAS_PROFILE_CONFIG_PORT_NUM(chip_port) |
                                        VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(scheduled) |
                                        VTSS_F_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)));
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        maxsdu = (max_sdu[i] / 64) + ((max_sdu[i] % 64) ? 1 : 0);
        REG_WR(VTSS_HSCH_TAS_QMAXSDU_CFG(profile_idx, i), maxsdu);
    }
    if (hold_profile_idx != TAS_PROFILE_IDX_NONE) {
        /* The profile for "Hold MAC" guard band */
        REG_WR(VTSS_HSCH_TAS_PROFILE_CONFIG(hold_profile_idx),
                                            VTSS_F_HSCH_TAS_PROFILE_CONFIG_PORT_NUM(chip_port) |
                                            VTSS_F_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(scheduled) |
                                            VTSS_F_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)));
        if (hold_qmaxsdu_configure(vtss_state, hold_profile_idx, port_no) != VTSS_RC_OK) {
            VTSS_D("tas_qmaxsdu_configure failed");
            return VTSS_RC_ERROR;
        }
    }

    /* Configure the list elements */
    for (i = 0; i < gcl_length; ++i) {
        /* Select the list entry */
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(i), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM); /* The GCL_ENTRY_NUM is relative to the LIST_BASE_ADDR that is accessed latest  */

        /* Configure the list entry */
        REG_WR(VTSS_HSCH_TAS_GCL_CTRL_CFG, VTSS_F_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(vtss_bool8_to_u8(gcl[i].gate_open)) |
                                           VTSS_F_HSCH_TAS_GCL_CTRL_CFG_HSCH_POS(5040 + 64 + chip_port));   /* Default scheduler element when HQoS is not present */
        REG_WR(VTSS_HSCH_TAS_GCL_TIME_CFG, gcl[i].time_interval);

        /* Calculate the sum of time intervals */
        time_interval_sum += gcl[i].time_interval;
    }
    /* Configure the list elements profile reference. This is depending on Frame Preemption enable/disable */
    if (gcl_port_profile_configure(vtss_state, list_idx, gcl, gcl_length, port_no) != VTSS_RC_OK) {
        VTSS_D("gcl_port_profile_configure failed");
        return VTSS_RC_ERROR;
    }

    /* Check if the sum of intervals are larger that the requeste cycle time */
    if ((time_interval_sum > cycle_time) || (cycle_time > VTSS_QOS_TAS_CT_MAX) || (cycle_time == 0)) {
        VTSS_D("The TAS list cycle time is invalid. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
        return VTSS_RC_ERROR;
    }
    if (time_interval_sum != cycle_time) {
        VTSS_D("The TAS list cycle time is larger than list time interval sum. time_interval_sum %u  cycle_time %u", time_interval_sum, cycle_time);
    }

    /* Start the list */
    tas_list_state_write(vtss_state, list_idx, TAS_LIST_STATE_ADVANCING);

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_qos_tas_port_conf_update(struct vtss_state_s   *vtss_state,
                                         const vtss_port_no_t  port_no)
{
    u32                 i;
    vtss_tas_profile_t  *tas_profiles = vtss_state->qos.tas.tas_profiles;

    /* This must be done when the link comes up and link speed has been negotiated. */
    /* The profile used on this port must be configured to actual speed */
    for (i = 0; i < VTSS_TAS_NUMBER_OF_PROFILES; ++i) {
        if (tas_profiles[i].in_use && tas_profiles[i].port_no == port_no) {
            REG_WRM(VTSS_HSCH_TAS_PROFILE_CONFIG(i), VTSS_F_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(tas_link_speed_calc(vtss_state->port.conf[port_no].speed)),
                                                     VTSS_M_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED);
        }
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
static vtss_rc fa_qos_tas_update(struct vtss_state_s   *vtss_state,
                                 const vtss_port_no_t  port_no)
{
    vtss_qos_tas_port_conf_t *port_conf = &vtss_state->qos.tas.port_conf[port_no];
    u32                      gcl_length = port_conf->gcl_length;
    vtss_qos_tas_gce_t       *gcl = port_conf->gcl;
    vtss_tas_gcl_state_t     *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    vtss_tas_list_t          *tas_lists = vtss_state->qos.tas.tas_lists;

    VTSS_D("fa_qos_tas_update Enter");

    if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
        return VTSS_RC_OK;
    }

    /* Frame Preemption might have changed the fragment size the is used to configure Max SDU size in the hold MAC profile */
    if (hold_qmaxsdu_configure(vtss_state, tas_lists[gcl_state->curr_list_idx].hold_profile_idx, port_no) != VTSS_RC_OK) {
        VTSS_D("tas_qmaxsdu_configure failed");
        return VTSS_RC_ERROR;
    }

    /* Frame preemption might be enabled or disable so the GCL entry profile reference must be re-configured */
    if (gcl_port_profile_configure(vtss_state, gcl_state->curr_list_idx, gcl, gcl_length, port_no) != VTSS_RC_OK) {
        VTSS_D("gcl_port_profile_configure failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}
#endif

static int tas_base_time_in_future(vtss_state_t *vtss_state,  vtss_timestamp_t  *base_time,  u32 min_distance_time)
{
    u64               tc;
    vtss_timestamp_t  tod_time, distance_time;

    /* Get current time */
    _vtss_ts_domain_timeofday_get(vtss_state, 0, &tod_time, &tc);

    /* Check if base time is in the past */
    if (vtss_timestampLarger(&tod_time, base_time)) {
        VTSS_D("base time is in the past");
        return -1;
    }

    /* Check if base time is in the future. Check if it is too close  */
    distance_time = *base_time;
    if (vtss_timestampSub(&distance_time, &tod_time) != VTSS_RC_OK) {
        VTSS_D("Base time subtraction failed");
        return 0;
    }
    /* Must be more that min_distance_time in the future */
    if ((distance_time.sec_msb == 0) && (distance_time.seconds == 0) && (distance_time.nanoseconds < min_distance_time)) {
        VTSS_D("Scheduled list start is too close");
        return 0;
    }

    return 1;   /* Correctly in the future */
}

static BOOL tas_scheduled_cancel_ok(vtss_state_t *vtss_state,  vtss_tas_gcl_state_t  *gcl_state)
{
    u32               scheduled_list_idx;
    vtss_timestamp_t  scheduled_base_time;

    /* Check if a list is already scheduled to start */
    if (gcl_state->new_list_scheduled) {
        /* Read the base time of the scheduled list start */
        scheduled_list_idx = (gcl_state->trunk_list_idx != TAS_LIST_IDX_NONE) ? gcl_state->trunk_list_idx : gcl_state->next_list_idx;
        tas_list_base_time_read(vtss_state, scheduled_list_idx, &scheduled_base_time);

        return (tas_base_time_in_future(vtss_state, &scheduled_base_time, 500000000) == 1) ? TRUE : FALSE; /* Check if scheduled base time is ok. It must be in the future and not too close (500 ms) */
    }
    return TRUE;
}

static BOOL tas_cycle_time_ok(vtss_qos_tas_port_conf_t *new_port_conf)
{
    u32                 i, time_interval_sum = 0;

    if ((new_port_conf->cycle_time < VTSS_QOS_TAS_CT_MIN) || (new_port_conf->cycle_time > VTSS_QOS_TAS_CT_MAX)) {
        return FALSE;
    }

    for (i = 0; i < new_port_conf->gcl_length; ++i) {
        time_interval_sum += new_port_conf->gcl[i].time_interval;
    }

    if (new_port_conf->cycle_time < time_interval_sum) {
        return FALSE;
    }

    return TRUE;
}

static vtss_rc fa_qos_tas_conf_set(vtss_state_t *vtss_state)
{
    vtss_qos_tas_conf_t *conf = &vtss_state->qos.tas.global_conf;

    /* Configure all ways guard band */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q(conf->always_guard_band ? 1 : 0), VTSS_M_HSCH_TAS_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q);

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_tas_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    u32                      i, profile_idx, trunk_profile_idx, trunk_startup_time, stop_startup_time, time_gap,
                             new_startup_time = 2000;  /* two nanoseconds */
    u32                      list_idx, trunk_list_idx, obsolete_list_idx, stop_list_idx;
    vtss_qos_tas_port_conf_t *new_port_conf = &vtss_state->qos.tas.port_conf[port_no];
    vtss_qos_tas_port_conf_t trunk_port_conf, stop_port_conf, current_port_conf;
    vtss_tas_gcl_state_t     *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];
    vtss_tas_list_t          *tas_lists = vtss_state->qos.tas.tas_lists;
    vtss_timestamp_t         current_end_time, old_cycle_start_time, stop_base_time;
    u64                      tc;
    int                      rc;

    list_idx = trunk_list_idx = obsolete_list_idx = stop_list_idx = TAS_LIST_IDX_NONE;
    profile_idx = trunk_profile_idx = TAS_PROFILE_IDX_NONE;
    trunk_startup_time = stop_startup_time = time_gap = 0;
    VTSS_MEMSET(&current_end_time, 0, sizeof(current_end_time));

    /* Update the GCL state */
    tas_gcl_state_update(vtss_state, port_no);

    /* Calculate the current GCL */
    if (tas_current_port_conf_calc(vtss_state, port_no, &current_port_conf) == VTSS_RC_ERROR) {
        VTSS_D("Calculate the current GCL failed");
        return VTSS_RC_ERROR;
    }

    if (new_port_conf->gate_enabled) {
        /* Running list on port is enabled */
        if (new_port_conf->config_change) {
            /* Start new list */

            /* Check for correct max SDU size */
            for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
                if ((new_port_conf->max_sdu[i] < 64) || (new_port_conf->max_sdu[i] > (255 * 64))) {   /* The the max register value is 255. Resolution is 64 bytes */
                    VTSS_D("Check of MAX SDU size failed");
                    return VTSS_RC_ERROR;
                }
            }

            /* Check for correct cycle time */
            if (!tas_cycle_time_ok(new_port_conf)) {
                VTSS_D("Check of cycle time failed");
                return VTSS_RC_ERROR;
            }

            /* Check for correct cycle extension time */
            /* The cycle extension time must not be smaller than VTSS_QOS_TAS_CT_MIN as this time */
            /* will become the trunk list cycle time that again will be the new_startup_time when the */
            /* new list is started after the trunk list */
            if (new_port_conf->cycle_time_ext < VTSS_QOS_TAS_CT_MIN) {
                VTSS_D("Check of cycle extension time failed");
                return VTSS_RC_ERROR;
            }

            /* Calculate the end time of possible current list cycle */
            if (!tas_current_end_time_calc(vtss_state, gcl_state->curr_list_idx, &new_port_conf->base_time, &current_end_time)) {
                VTSS_D("Calculate the end time of current list cycle failed");
                return VTSS_RC_ERROR;
            }

            /* Check if requested base time is ok - in the future and not too close (two cycle times) */
            if ((rc = tas_base_time_in_future(vtss_state, &new_port_conf->base_time, (2 * new_port_conf->cycle_time))) != 1) {
                VTSS_D("The requested GCL base time is not OK");
                if ((rc == -1) && (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE)) {    /* Base time in the future and current list active */
                    gcl_state->config_change_error++;
                }
                return VTSS_RC_ERROR;
            }

            /* Check if a stop of list is on going - must finish */
            if (gcl_state->stop_ongoing) {
                VTSS_D("The TAS list stop is ongoing");
                return VTSS_RC_ERROR;
            }

            /* Check if a list is already scheduled to start */
            if (gcl_state->new_list_scheduled) {
                /* Check if it is ok to cancel scheduled list.  */
                if (!tas_scheduled_cancel_ok(vtss_state, gcl_state)) {
                    VTSS_D("A scheduled list start is on going");
                    return VTSS_RC_ERROR;
                }
                /* Cancel the scheduled list start */
                tas_list_cancel(vtss_state, gcl_state->trunk_list_idx);
                tas_list_cancel(vtss_state, gcl_state->next_list_idx);
            }

            /* Check if a list is currently running. Possible trunk list required */
            if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the time gap between current list cycle and beginning of new list */
                if (!tas_time_stamp_diff(&new_port_conf->base_time, &current_end_time, &time_gap)) {
                    VTSS_D("Calculate the time gap between current list cycle and beginning of new list failed");
                    return VTSS_RC_ERROR;
                }
                if (time_gap > new_port_conf->cycle_time_ext) { /* Check if gap is larger that the accepted extension time. Truncation of current list */
                    VTSS_D("GCL truncation");
                    if ((trunk_list_idx = tas_list_allocate(vtss_state, new_port_conf->gcl_length)) == TAS_LIST_IDX_NONE) {   /* Allocate trunk list */
                        VTSS_I("Allocate trunk list failed");
                        return VTSS_RC_ERROR;
                    }
                    tas_lists[trunk_list_idx].profile_idx = tas_lists[gcl_state->curr_list_idx].profile_idx;  /* The trunk list inherit profile from current list */;
                    tas_lists[trunk_list_idx].inherit_profile = TRUE;
                } else {
                    VTSS_D("GCL extension");
                }
            }

            /* Allocate resources for new list */
            if ((list_idx = tas_list_allocate(vtss_state, new_port_conf->gcl_length)) == TAS_LIST_IDX_NONE) {   /* Allocate new list */
                tas_list_free(vtss_state, trunk_list_idx);
                VTSS_I("No TAS list was allocated");
                return VTSS_RC_ERROR;
            }
            if ((profile_idx = tas_profile_allocate(vtss_state, port_no)) == TAS_PROFILE_IDX_NONE) {    /* Allocate new profile */
                tas_list_free(vtss_state, list_idx);
                tas_list_free(vtss_state, trunk_list_idx);
                VTSS_I("No TAS profiles was allocated");
                return VTSS_RC_ERROR;
            }
            tas_lists[list_idx].profile_idx = profile_idx;
            tas_lists[list_idx].inherit_profile = FALSE;
            if (tas_scheduled_calc(new_port_conf->gcl, new_port_conf->gcl_length) != 0) {
                /* This GCL contains hold/release MAC gate operations. */
                /* This require extra profile to configure the Frame Preemption fragment based MAX SDU size */
                if ((profile_idx = tas_profile_allocate(vtss_state, port_no)) == TAS_PROFILE_IDX_NONE) {    /* Allocate new profile */
                    tas_list_free(vtss_state, list_idx);
                    tas_list_free(vtss_state, trunk_list_idx);
                    VTSS_I("No TAS profiles was allocated");
                    return VTSS_RC_ERROR;
                }
                tas_lists[list_idx].hold_profile_idx = profile_idx;
            }
            obsolete_list_idx = gcl_state->curr_list_idx;

            /* Resources are now allocated - start the lists */

            /* Check if trunk list must be started */
            if (trunk_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the truncated GCL and startup time*/
                tas_trunk_port_conf_calc(&current_port_conf, &current_end_time, &new_port_conf->base_time, &trunk_port_conf);
                trunk_startup_time = current_port_conf.cycle_time;   /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). In this case this is equel to cycle time as there will be no gap between current list cycle end and trunk list cycle start */
                /* Start the trunk list */
                if (tas_list_start(vtss_state, port_no, trunk_list_idx, obsolete_list_idx, &trunk_port_conf, trunk_startup_time) != VTSS_RC_OK) {
                    /* Start failed */
                    tas_list_free(vtss_state, trunk_list_idx);
                    tas_list_free(vtss_state, list_idx);
                    VTSS_I("The trunk TAS list could not start");
                    return VTSS_RC_ERROR;
                }
                obsolete_list_idx = trunk_list_idx;
            }

            /* Start the new list */
            if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
                /* Calculate the 'old' last cycle start time */
                if (trunk_list_idx != TAS_LIST_IDX_NONE) {
                    old_cycle_start_time = trunk_port_conf.base_time;   /* Trunk list has only one cycle so the base time is the start of the last cycle */
                } else {
                    old_cycle_start_time = current_end_time;            /* Start of current last cycle is the end time of last cycle minus the cycle time */
                    if (vtss_timestampSubNano(&old_cycle_start_time, current_port_conf.cycle_time) != VTSS_RC_OK) {
                        VTSS_D("Calculate the 'old' last cycle start time failed");
                        return VTSS_RC_ERROR;
                    }
                }
                /* Calculate the new startup time */
                if (!tas_time_stamp_diff(&new_port_conf->base_time, &old_cycle_start_time, &new_startup_time)) { /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). */
                    VTSS_D("Calculate the new startup time failed");
                    return VTSS_RC_ERROR;
                }
            }
            if (tas_list_start(vtss_state, port_no, list_idx, obsolete_list_idx, new_port_conf, new_startup_time) != VTSS_RC_OK) {
                /* Start failed */
                tas_list_free(vtss_state, list_idx);

                /* Cancel the trunk list */
                tas_list_cancel(vtss_state, trunk_list_idx);

                VTSS_I("The new TAS list could not start");
                return VTSS_RC_ERROR;
            }

            gcl_state->next_list_idx = list_idx;
            gcl_state->trunk_list_idx = trunk_list_idx;
            gcl_state->new_list_scheduled = TRUE;  /* Start of new list is ongoing */

        } else {
            /* Check if a list is currently running */
            if (gcl_state->curr_list_idx == TAS_LIST_IDX_NONE) {
                tas_gate_state_write(vtss_state, port_no, new_port_conf->gate_open);   /* Set the gate state of the port to 'gate_open[]' */
            }
        }
    } else {
        /* Running list on port is disabled */

        /* Check if a stop of list is on going - must finish */
        if (gcl_state->stop_ongoing) {
            VTSS_D("The TAS list stop is ongoing");
            return VTSS_RC_ERROR;
        }

        /* Check if a list is scheduled to start */
        if (gcl_state->new_list_scheduled) {
            /* Check if it is ok to cancel scheduled list */
            if (!tas_scheduled_cancel_ok(vtss_state, gcl_state)) {    /* A scheduled list start is on going - must finish */
                VTSS_D("A scheduled list start is on going");
                return VTSS_RC_ERROR;
            }
            /* Cancel the scheduled list start */
            tas_list_cancel(vtss_state, gcl_state->trunk_list_idx);
            tas_list_cancel(vtss_state, gcl_state->next_list_idx);
        }

        /* Check if a list is currently running - must be stopped by a stop list */
        if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {
            /* Calculate first possible base time of stop list. This is TOD plus two times the current cycle time */
            _vtss_ts_domain_timeofday_get(vtss_state, 0, &stop_base_time, &tc);
             VTSS_D("stop base_time seconds %u  nanoseconds %u  sec_msb %u", stop_base_time.seconds, stop_base_time.nanoseconds, stop_base_time.sec_msb);
             VTSS_D("current base_time seconds %u  nanoseconds %u  sec_msb %u", current_port_conf.base_time.seconds, current_port_conf.base_time.nanoseconds, current_port_conf.base_time.sec_msb);

            /* Check if current base time is in the future. This should not happen as gcl_state say that list is started */
            if (vtss_timestampLarger(&current_port_conf.base_time, &stop_base_time)) {
                VTSS_D("current list base time is in the future");
                stop_base_time = current_port_conf.base_time;
            }

            if (vtss_timestampAddNano(&stop_base_time, 2 * current_port_conf.cycle_time) != VTSS_RC_OK) {
                VTSS_D("Calculate first possible base time of stop list failed.  cycle_time %u", current_port_conf.cycle_time);
                return VTSS_RC_ERROR;
            }
            /* Calculate the end time of current list cycle */
            if (!tas_current_end_time_calc(vtss_state, gcl_state->curr_list_idx, &stop_base_time, &current_end_time)) {
                VTSS_D("Calculate the end time of current list cycle failed");
                return VTSS_RC_ERROR;
            }

            /* Calculate the stop GCL and stop startup time */
            tas_stop_port_conf_calc(&current_end_time, new_port_conf->gate_open, &stop_port_conf);
            stop_startup_time = current_port_conf.cycle_time;   /* STARTUP_TIME := first_cycle_start(B) - last_cycle_start(A). In this case this is equal to cycle time as there will be no gap between current list cycle end and stop list cycle start */

            /* Allocate stop list */
            if ((stop_list_idx = tas_list_allocate(vtss_state, stop_port_conf.gcl_length)) == TAS_LIST_IDX_NONE) {
                VTSS_I("No TAS list was allocated");
                return VTSS_RC_ERROR;
            }
            tas_lists[stop_list_idx].profile_idx = tas_lists[gcl_state->curr_list_idx].profile_idx;  /* The stop list use same profile as current list */
            tas_lists[stop_list_idx].inherit_profile = TRUE;
            obsolete_list_idx = gcl_state->curr_list_idx;

            /* Start the stop list */
            if (tas_list_start(vtss_state, port_no, stop_list_idx, obsolete_list_idx, &stop_port_conf, stop_startup_time) != VTSS_RC_OK) {
                /* Start failed */
                tas_list_free(vtss_state, stop_list_idx);
                VTSS_I("The stop TAS list could not start");
                return VTSS_RC_ERROR;
            }
            gcl_state->trunk_list_idx = TAS_LIST_IDX_NONE;
            gcl_state->next_list_idx = stop_list_idx;
            gcl_state->stop_ongoing = TRUE;  /* Stop of new list is ongoing */
            gcl_state->config_change_error = 0;
        }

        return VTSS_RC_OK;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_tas_port_status_get(vtss_state_t              *vtss_state,
                                         const vtss_port_no_t       port_no,
                                         vtss_qos_tas_port_status_t *const status)
{
    u32                   list_idx = TAS_LIST_IDX_NONE;
    vtss_tas_gcl_state_t  *gcl_state = &vtss_state->qos.tas.tas_gcl_state[port_no];

    VTSS_MEMSET(status, 0, sizeof(*status));

    /* Update the GCL state */
    tas_gcl_state_update(vtss_state, port_no);

    /* Configuration is pending if next list is active. This is true if new start list is pending or stop list is pending */
    status->config_pending = (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) ? TRUE : FALSE;

    status->config_change_error = gcl_state->config_change_error;

    /* Read the base time that a pending configuration is going to be changed or the current configuration has been changed */
    if (gcl_state->next_list_idx != TAS_LIST_IDX_NONE) {
        list_idx = gcl_state->next_list_idx;    /* New list is pending */
    } else if (gcl_state->curr_list_idx != TAS_LIST_IDX_NONE) {    /* New list is not pending*/
        list_idx = gcl_state->curr_list_idx;    /* Current list is active */
    }
    if (list_idx != TAS_LIST_IDX_NONE) {
        tas_list_base_time_read(vtss_state, list_idx, &status->config_change_time);
    }

    /* Read the current gate state on the port */
    tas_gate_state_read(vtss_state, port_no, status->gate_open);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
static vtss_rc fa_qos_fp_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];
    u32                     enable_tx = (conf->enable_tx ? 1 : 0);
    u32                     i, unit, port = VTSS_CHIP_PORT(port_no);
    vtss_port_speed_t       speed = vtss_state->port.conf[port_no].speed;
    BOOL                    verify_dis = !(!conf->verify_disable_tx && conf->enable_tx);

    if (speed > VTSS_SPEED_10G) {
        VTSS_E("frame preemption is not supported for port speeds above 10G");
        return VTSS_RC_ERROR;
    }

    if (enable_tx) {
        if (speed == VTSS_SPEED_10G && vtss_state->init_conf.core_clock.freq < VTSS_CORE_CLOCK_500MHZ) {
            VTSS_E("frame preemption requires at least 500 MHz core clock for 10G ports");
            return VTSS_RC_ERROR;
        }
        if (conf->add_frag_size == 3) {
            VTSS_E("frame preemption does not support add_frag_size 3");
            return VTSS_RC_ERROR;
        }
        for (i = 0; i < 8; i++) {
            if (vtss_state->qos.port_conf[port_no].cut_through_enable[i]) {
                VTSS_E("frame preemption and cut through cannot both be enabled");
                return VTSS_RC_ERROR;
            }
        }
    }

    /* Unit depends on speed */
    switch (speed) {
    case VTSS_SPEED_10M:
    case VTSS_SPEED_100M:
    case VTSS_SPEED_1G:
    case VTSS_SPEED_5G:
        unit = 0;
        break;
    default:
        unit = 2;
        break;
    }

    DEV_WRM(VERIF_CONFIG, port,
            VTSS_F_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS(1),
            VTSS_M_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS);

    DEV_WR(VERIF_CONFIG, port,
           VTSS_F_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS(verify_dis) |
           VTSS_F_DEV1G_VERIF_CONFIG_PRM_VERIFY_TIME(conf->verify_time) |
           VTSS_F_DEV1G_VERIF_CONFIG_VERIF_TIMER_UNITS(unit));

    REG_WR(VTSS_DSM_PREEMPT_CFG(port),
           VTSS_F_DSM_PREEMPT_CFG_P_MIN_SIZE(conf->add_frag_size));
    REG_WR(VTSS_DSM_IPG_SHRINK_CFG(port),
           VTSS_F_DSM_IPG_SHRINK_CFG_IPG_SHRINK_ENA(enable_tx));

    for (i = 0; i < 8; i++) {
        /* Enable/disable preemptable queues */
        REG_WRM(VTSS_HSCH_HSCH_L0_CFG(FA_HSCH_L0_SE(port, i)),
                VTSS_F_HSCH_HSCH_L0_CFG_P_QUEUES(enable_tx && conf->admin_status[i] ? 0xff : 0),
                VTSS_M_HSCH_HSCH_L0_CFG_P_QUEUES);
        /* Force queue update */
        REG_WR(VTSS_HSCH_HSCH_FORCE_CTRL,
               VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_LAYER(0) |
               VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_SE_IDX(FA_HSCH_L0_SE(port, i)) |
               VTSS_F_HSCH_HSCH_FORCE_CTRL_HFORCE_1SHOT(1));
    }

    if (vtss_state->misc.chip_id.revision == 0) {
        /* Avoid forced FCS update for revision 0 if preemption is enabled */
        enable_tx = 0;
        for (port = 0; port < vtss_state->port_count; port++) {
            if (vtss_state->qos.fp.port_conf[port].enable_tx) {
                enable_tx = 1;
            }
        }
        REG_WRM(VTSS_ANA_ACL_VCAP_S2_MISC_CTRL,
                VTSS_F_ANA_ACL_VCAP_S2_MISC_CTRL_ACL_RT_SEL(enable_tx ? 0 : 1),
                VTSS_M_ANA_ACL_VCAP_S2_MISC_CTRL_ACL_RT_SEL);
    }
    (void)fa_qos_tas_update(vtss_state, port_no);

    return VTSS_RC_OK;
}

static vtss_rc fa_qos_fp_port_status_get(vtss_state_t              *vtss_state,
                                         const vtss_port_no_t      port_no,
                                         vtss_qos_fp_port_status_t *const status)
{
    u32 value, v, port = VTSS_CHIP_PORT(port_no);
    vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;

    if (speed > VTSS_SPEED_10G) {
        status->preemption_active = 0;
        status->status_verify = VTSS_MM_STATUS_VERIFY_DISABLED;
        return VTSS_RC_OK;
    }
    DEV_RD(MM_STATUS, port, &value);
    status->preemption_active = VTSS_X_DEV1G_MM_STATUS_PRMPT_ACTIVE_STATUS(value);
    if (vtss_state->qos.fp.port_conf[port_no].verify_disable_tx) {
        v = VTSS_MM_STATUS_VERIFY_DISABLED;
    } else {
        v = VTSS_X_DEV1G_MM_STATUS_PRMPT_VERIFY_STATE(value);

        if (v == 3 && conf->enable_tx) {
            /* Verification failed, restart it */
            DEV_WRM(VERIF_CONFIG, port,
                    VTSS_F_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS(1),
                    VTSS_M_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS);

            DEV_WRM(VERIF_CONFIG, port,
                    VTSS_F_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS(0),
                    VTSS_M_DEV1G_VERIF_CONFIG_PRM_VERIFY_DIS);
        }

        // DEV2G5 does not support full state
        v = (vtss_fa_port_is_high_speed(vtss_state, port) || v == 0 ? v : (v + 2));
    }
    status->status_verify = v;
    return VTSS_RC_OK;
}
#endif

vtss_rc vtss_fa_qos_port_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL is_reset)
{
    /* Setup depending on port reset status */
    return (is_reset ? fa_qos_queue_cut_through_set(vtss_state, port_no) : VTSS_RC_OK);
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
                        pr("\n");
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
    pr("%-32s: %6u\n\n", "SE_DLB_SE_ENA", VTSS_X_HSCH_SE_DLB_SENSE_SE_DLB_SE_ENA(value));

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_qos_ingress_mapping(vtss_state_t              *vtss_state,
                                         const vtss_debug_printf_t pr,
                                         const u32                 ix_start,
                                         const int                 length)
{
    u32  ix, col, value;
    int  len;
    char buf[100];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        pr("Index %u, (%u of %u)\n", ix, len + 1, length);
        pr("%-32s: PATH  TC  DP  COSID  QOS  DEI  PCP  DSCP\n", "");
        REG_RD(VTSS_ANA_CL_SET_CTRL(ix), &value);
        VTSS_SPRINTF(buf, "    MAP_TBL[%u]:SET_CTRL", ix);
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
            VTSS_SPRINTF(buf, "    MAP_TBL[%u]:MAP_ENTRY[%u]", ix, col);
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
    char buf[100];

    for (len = 0; len < length; len++) {
        ix = ix_start + len;
        VTSS_SPRINTF(buf, "Index %u, (%u of %u)", ix, len + 1, length);
        pr("%-32s: OAM_COLOR  OAM_COSID  TC  DSCP  DEI  PCP\n", buf);
        for (col = 0; col < 8; col++) {
            addr = (ix * 8) + col;
            if (res == 0) { // Resource A
                REG_RD(VTSS_REW_MAP_VAL_A(addr), &value);
                VTSS_SPRINTF(buf, "    MAP_RES_A[%u]:MAP_VAL_A", addr);
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
                VTSS_SPRINTF(buf, "    MAP_RES_B[%u]:MAP_VAL_B", addr);
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
        VTSS_SPRINTF(buf, "QoS %s Mapping Tables Res %u", m->name, res);
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

#define FA_DSM_CAL_ROW_CNT 9
#define FA_DSM_CAL_COL_CNT 13
static const u8 fa_dsm_cal[FA_DSM_CAL_ROW_CNT][FA_DSM_CAL_COL_CNT] = {
    {57,12, 0, 1, 2,16,17,18,19,20,21,22,23},
    {58,13, 3, 4, 5,24,25,26,27,28,29,30,31},
    {59,14, 6, 7, 8,32,33,34,35,36,37,38,39},
    {60,15, 9,10,11,40,41,42,43,44,45,46,47},
    {61,48,49,50,99,99,99,99,99,99,99,99,99},
    {62,51,52,53,99,99,99,99,99,99,99,99,99},
    {56,63,54,55,99,99,99,99,99,99,99,99,99},
    {64,99,99,99,99,99,99,99,99,99,99,99,99},
    {65,99,99,99,99,99,99,99,99,99,99,99,99}
};

static char *debug_tas_state_string(u32 value)
{
    switch (value) {
        case 0:    return("ADMIN");
        case 1:    return("ADVANCING");
        case 2:    return("PENDING");
        case 3:    return("OPERATING");
        case 4:    return("TERMINATING");
        default:   return("UNKNOWN");
    }
    return("INVALID");
}

static vtss_rc debug_tas_conf_print(vtss_state_t *vtss_state,  const vtss_debug_printf_t pr,  u32 list_idx,  BOOL any_state)
{
    u32   i, j, value, state, gcl_length, entry_idx, profile_idx;

    /* Select the list */
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(list_idx), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);
    REG_RD(VTSS_HSCH_TAS_LIST_STATE, &state);

    if ((VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(state) != 0) || any_state) {    /* Print list not in ADMIN state */
        pr("GCL Index: %u\n", list_idx);
        pr("----------------\n");
        REG_RD(VTSS_HSCH_TAS_BASE_TIME_NSEC, &value);
        pr("    %s: %u\n", "BASE_TIME_NSEC", value);
        REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_LSB, &value);
        pr("    %s: %u\n", "BASE_TIME_SEC_LSB", value);
        REG_RD(VTSS_HSCH_TAS_BASE_TIME_SEC_MSB, &value);
        pr("    %s: %u\n", "BASE_TIME_SEC_MSB", value);
        REG_RD(VTSS_HSCH_TAS_CYCLE_TIME_CFG, &value);
        pr("    %s: %u\n", "CYCLE_TIME_CFG", value);
        REG_RD(VTSS_HSCH_TAS_STARTUP_CFG, &value);
        pr("    %s: %u\n", "OBSOLETE_IDX", VTSS_X_HSCH_TAS_STARTUP_CFG_OBSOLETE_IDX(value));
        pr("    %s: %u\n", "STARTUP_TIME", VTSS_X_HSCH_TAS_STARTUP_CFG_STARTUP_TIME(value));
        REG_RD(VTSS_HSCH_TAS_LIST_CFG, &value);
        gcl_length = VTSS_X_HSCH_TAS_LIST_CFG_LIST_LENGTH(value);
        pr("    %s: %u\n", "LIST_LENGTH", gcl_length);
        pr("    %s: %u\n", "LIST_TOD_DOM", VTSS_X_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(value));
        entry_idx = VTSS_X_HSCH_TAS_LIST_CFG_LIST_BASE_ADDR(value);
        pr("    %s: %u\n", "LIST_BASE_ADDR", entry_idx);
        pr("    %s: %s\n", "LIST_STATE", debug_tas_state_string(VTSS_X_HSCH_TAS_LIST_STATE_LIST_STATE(state)));
        pr("\n");
    
        /* Read the list elements */
        for (i = 0; i < gcl_length; ++i) {
            pr("    Enty Index: %u\n", i);
            pr("    ----------------\n");

            /* Select the list entry */
            REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM(i), VTSS_M_HSCH_TAS_CFG_CTRL_GCL_ENTRY_NUM); /* The GCL_ENTRY_NUM is relative to the LIST_BASE_ADDR that is accessed latest  */

            /* Read the gate state */
            REG_RD(VTSS_HSCH_TAS_GCL_CTRL_CFG, &value);
            profile_idx = VTSS_X_HSCH_TAS_GCL_CTRL_CFG_PORT_PROFILE(value);
            pr("        %s: 0x%X\n", "GATE_STATE", VTSS_X_HSCH_TAS_GCL_CTRL_CFG_GATE_STATE(value));
            pr("        %s: %u\n", "PORT_PROFILE", profile_idx);
            pr("        %s: %u\n", "HSCH_POS", VTSS_X_HSCH_TAS_GCL_CTRL_CFG_HSCH_POS(value));

            /* Read time interval */
            REG_RD(VTSS_HSCH_TAS_GCL_TIME_CFG, &value);
            pr("        %s: %u\n", "TIME_INTERVAL", value);

            /* Read max SDU configuration in the profile */
            pr("        %s: ", "QMAXSDU_VAL");
            for (j = 0; j < VTSS_QUEUE_ARRAY_SIZE; ++j) {
                REG_RD(VTSS_HSCH_TAS_QMAXSDU_CFG(profile_idx, j), &value);
                pr("%u-", value);
            }
            pr("\n");

            /* Read scheduled configuration in the profile */
            REG_RD(VTSS_HSCH_TAS_PROFILE_CONFIG(profile_idx), &value);
            pr("        %s: %u\n", "PORT_NUM", VTSS_X_HSCH_TAS_PROFILE_CONFIG_PORT_NUM(value));
            pr("        %s: %u\n", "LINK_SPEED", VTSS_X_HSCH_TAS_PROFILE_CONFIG_LINK_SPEED(value));
            pr("        %s: 0x%X\n", "SCH_TRAFFIC_QUEUES", VTSS_X_HSCH_TAS_PROFILE_CONFIG_SCH_TRAFFIC_QUEUES(value));
        }
        pr("\n");
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_debug_qos(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    vtss_port_no_t      port_no, chip_port, tas_port=0;
    u32                 i, j, max_burst, min_token, value = 0, service_pol_set_idx = 0, tas_list_idx = 0, div = 0, addr, len;
    u64                 min_rate, lowest_max_nxt;
    vtss_qos_lb_group_t *group, *group_nxt;
    BOOL                show_act, basics_act, ingr_mapping_act, gen_pol_act, service_pol_grp_act, service_pol_set_act, port_pol_act,
                        storm_pol_act, schedul_act, band_act, shape_act, leak_act, wred_act, tag_remark_act, egr_mapping_act, tas_act,
                        tas_state_act, tas_count_act;

    VTSS_D("has_action %u  action %u", info->has_action, info->action);

    show_act = basics_act = ingr_mapping_act = gen_pol_act = service_pol_grp_act = service_pol_set_act = port_pol_act =
    storm_pol_act = schedul_act = tas_act = band_act = shape_act = leak_act = wred_act = tag_remark_act = egr_mapping_act =
    tas_state_act = tas_count_act = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show_act =             (info->action == 0)  ? TRUE : FALSE;
        basics_act =           (info->action == 1)  ? TRUE : FALSE;
        ingr_mapping_act =     (info->action == 2)  ? TRUE : FALSE;
        gen_pol_act =          (info->action == 3)  ? TRUE : FALSE;
        port_pol_act =         (info->action == 4)  ? TRUE : FALSE;
        storm_pol_act =        (info->action == 5)  ? TRUE : FALSE;
        schedul_act =          (info->action == 6)  ? TRUE : FALSE;
        tas_act =              (info->action == 7)  ? TRUE : FALSE;
        tas_state_act =        (info->action == 8)  ? TRUE : FALSE;
        tas_count_act =        (info->action == 9)  ? TRUE : FALSE;
        band_act =             (info->action == 10) ? TRUE : FALSE;
        shape_act =            (info->action == 11) ? TRUE : FALSE;
        leak_act =             (info->action == 12) ? TRUE : FALSE;
        wred_act =             (info->action == 13) ? TRUE : FALSE;
        tag_remark_act =       (info->action == 14) ? TRUE : FALSE;
        egr_mapping_act =      (info->action == 15) ? TRUE : FALSE;
        service_pol_grp_act =  (info->action == 16) ? TRUE : FALSE;
        service_pol_set_act =  (info->action == 17) ? TRUE : FALSE;
    }

    if (info->action > 17) { /* This potentially a Service policing set action or TAS configuration or analyze action */
        for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
            tas_act = ((info->action / div) == 7) ? TRUE : FALSE;
            tas_state_act = ((info->action / div) == 8) ? TRUE : FALSE;
            tas_count_act = ((info->action / div) == 9) ? TRUE : FALSE;
            service_pol_set_act = (info->action / div == 17) ? TRUE : FALSE;

            if (service_pol_set_act || tas_act || tas_state_act || tas_count_act) {
                break;
            }
        }
        if (service_pol_set_act) {
            service_pol_set_idx = info->action % div;
        }
        if (tas_act) {
            tas_list_idx = info->action % div;
        }
        if (tas_state_act || tas_count_act) {
            tas_port = info->action % div;
        }
        VTSS_D("service_pol_set_act %u  tas_act %u  tas_state_act %u  tas_count_act %u  service_pol_set_idx %u  tas_list_idx %u  tas_port %u  div %u",
                service_pol_set_act, tas_act, tas_state_act, tas_count_act, service_pol_set_idx, tas_list_idx, tas_port, div);
    }

    VTSS_D("show %u  basic %u  ingr_map %u  gen_pol %u  port_pol %u  storm_pol %u  schedul %u  band %u  shape %u  leak %u  wred  %u  tag_remark  %u  egr_map  %u",
            show_act, basics_act, ingr_mapping_act, gen_pol_act, port_pol_act, storm_pol_act, schedul_act, band_act, shape_act, leak_act, wred_act, tag_remark_act, egr_mapping_act);

    if (show_act) {
        pr("QOS Debug Group action:\n");
        pr("    0:      Show possible actions\n");
        pr("    1:      Print Basic configuration\n");
        pr("    2:      Print Ingress mapping configuration\n");
        pr("    3:      Print General policing configurations\n");
        pr("    4:      Print Port policing configurations\n");
        pr("    5:      Print Storm Policing configurations\n");
        pr("    6:      Print Scheduling hierarchy configurations\n");
        pr("    7XXXX   Print Time Aware Scheduling configurations. All active liats or the XXXX specified\n");
        pr("    8XXXX   Print Time Aware Scheduling gate state analyze. Port is the XXXX specified\n");
        pr("    9XXXX   Print Time Aware Scheduling counter analyze. Port is the XXXX specified\n");
        pr("    10:     Print Bandwidth distribution configurations\n");
        pr("    11:     Print Shapers configurations\n");
        pr("    12:     Print Leak chain configurations\n");
        pr("    13:     Print WRED configurations\n");
        pr("    14:     Print Tag remarking configurations\n");
        pr("    15:     Print Egress mapping configurations\n");
        pr("    16:     Print Service policing group configurations\n");
        pr("    17XXXX: Print Service policing set XXXX configurations\n");
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
                    class_ct += VTSS_SNPRINTF(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim,
                                        VTSS_X_ANA_CL_PCP_DEI_MAP_CFG_PCP_DEI_QOS_VAL(value));
                    dpl_ct   += VTSS_SNPRINTF(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim,
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
        for (i = 0; i < LB_GROUP_CNT; ++i) {
            group = &vtss_state->qos.lb_groups[i];
            max_burst = group->min_burst * 0x3FF;
            min_rate = lb_group_lb_min_rate_calc(group->pup_interval);
            min_token = 1;
            if (i < (LB_GROUP_CNT - 1)) {   /* This is not the last group */
                group_nxt = &vtss_state->qos.lb_groups[i + 1];
                lowest_max_nxt = lb_group_lb_max_rate_calc(group_nxt->min_burst, group_nxt->pup_interval);
                min_token = lb_group_lb_pup_token_calc(lowest_max_nxt + 1, group->pup_interval); /* The lowest max rate (+1) of next group is possible lowest rate in this group */
            }
            pr("%-3u  %-9u  %-9u  %-8" PRIu64 "  %-13" PRIu64 "  %-13" PRIu64 "  %-9u  %-7u  %-10u  %-9u  %-6u\n",
               i, group->min_burst, max_burst, min_rate,
               lb_group_lb_max_rate_calc(group->min_burst, group->pup_interval),
               lb_group_lb_max_rate_calc(max_burst, group->pup_interval),
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

    if (!info->has_action || tas_act) { /* SAT configuration must be printed */
        vtss_tas_gcl_state_t *gcl;
        vtss_tas_list_t *lists = vtss_state->qos.tas.tas_lists;

        vtss_debug_print_header(pr, "QoS Time Aware Scheduler");
        if (div == 0) {
            pr("GCLs allocated:\n");
            pr("port   stop  scheduled  list        list_in_use  list_entry_idx  list_profile_idx\n");
            pr("---------------------------------------------------------------------------------\n");

            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                /* Update the GCL state */
                tas_gcl_state_update(vtss_state, port_no);

                gcl = &vtss_state->qos.tas.tas_gcl_state[port_no];

                if (gcl->stop_ongoing || gcl->new_list_scheduled || (gcl->curr_list_idx != TAS_LIST_IDX_NONE) || (gcl->trunk_list_idx != TAS_LIST_IDX_NONE) || (gcl->next_list_idx != TAS_LIST_IDX_NONE)) {
                    pr("%-7u%-6u%-11u", port_no, gcl->stop_ongoing, gcl->new_list_scheduled);
                    if (gcl->curr_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%-12u%-13u%-16u%-16u\n", gcl->curr_list_idx, lists[gcl->curr_list_idx].in_use, lists[gcl->curr_list_idx].entry_idx, lists[gcl->curr_list_idx].profile_idx);
                    } else {
                        pr("%-12s%-13s%-16s%-16s\n", "-", "-", "-", "-");
                    }
                    if (gcl->trunk_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%24s%-12u%-13u%-16u%-16u\n", "trunk   ", gcl->trunk_list_idx, lists[gcl->trunk_list_idx].in_use, lists[gcl->trunk_list_idx].entry_idx, lists[gcl->trunk_list_idx].profile_idx);
                    }
                    if (gcl->next_list_idx != TAS_LIST_IDX_NONE) {
                        pr("%24s%-12u%-13u%-16u%-16u\n", "next   ", gcl->next_list_idx, lists[gcl->next_list_idx].in_use, lists[gcl->next_list_idx].entry_idx, lists[gcl->next_list_idx].profile_idx);
                    }
                }
            }
            pr("\n");

            pr("Entry blocks:\n");
            pr("Row   Block  in_use\n");
            pr("-------------------\n");
            for (i = 0; i < VTSS_TAS_NUMBER_OF_ROWS; i++) {
                for (j = 0; j < VTSS_TAS_NUMBER_OF_BLOCKS_PER_ROW; j++) {
                    if (vtss_state->qos.tas.tas_entry_blocks[i][j].in_use) {
                        pr("%-6u%-7u%-6u\n", i, j, vtss_state->qos.tas.tas_entry_blocks[i][j].in_use);
                    }
                }
            }
            pr("\n");

            pr("Entry rows:\n");
            pr("Row   in_use  slot_size\n");
            pr("-----------------------\n");
            for (i = 0; i < VTSS_TAS_NUMBER_OF_ROWS; i++) {
                if (vtss_state->qos.tas.tas_entry_rows[i].in_use) {
                    pr("%-6u%-7u%-9u\n", i, vtss_state->qos.tas.tas_entry_rows[i].in_use, vtss_state->qos.tas.tas_entry_rows[i].slot_size);
                }
            }
            pr("\n");
        }
        pr("GCL register configuration:\n");
        for (i = 0; i < VTSS_TAS_NUMBER_OF_LISTS; i++) {
            if ((div > 1) && (tas_list_idx != i)) {   /* A specific TAS list must be printed - this is not the one */
                continue;
            }
            (void)debug_tas_conf_print(vtss_state, pr, i, (div > 1));
        }
    }

#define PRIO_MASK 0x01
#define CYCLE_TIME 12480000
    if (tas_state_act && (div > 1)) { /* SAT state analyze must be printed */
        vtss_port_no_t   chip_port = VTSS_CHIP_PORT(tas_port-1);
        u32              gate_state, index = 0, rc = 0;
        u64              tc;
        vtss_timestamp_t ts0, ts1, distance;
        struct {
            u8               gate_state;
            vtss_timestamp_t ts;
        } buffer[1000];

        _vtss_ts_domain_timeofday_get(NULL, 0, &ts0, &tc);
        rc = (vtss_fa_wr(vtss_state, VTSS_HSCH_TAS_GATE_STATE_CTRL, (5040 + 64 + chip_port)) != VTSS_RC_OK) ? (rc + 1) : rc;
        while (1) {
            _vtss_ts_domain_timeofday_get(NULL, 0, &ts1, &tc);
            rc = (vtss_fa_rd(vtss_state, VTSS_HSCH_TAS_GATE_STATE, &gate_state) != VTSS_RC_OK) ? (rc + 1) : rc;
            if ((index == 0) || (gate_state != buffer[index-1].gate_state)) {
                buffer[index].gate_state = (u8)(gate_state);
                buffer[index].ts = ts1;
                index++;
            }
            if (((ts1.seconds - ts0.seconds) > 2) || (index >= 1000)) break;
        }

        for (i=0; i<index; ++i) {
            if (i > 1) {
                distance = buffer[i].ts;
                (void)vtss_timestampSub(&distance, &buffer[i-1].ts);
                pr("state %X  sec %u  nsec %u  distance %u\n", buffer[i].gate_state, buffer[i].ts.seconds, buffer[i].ts.nanoseconds, distance.nanoseconds);
            }
        }
        pr("index %u  ts1.seconds %u  ts0.seconds %u  rc %u\n", index, ts1.seconds, ts0.seconds, rc);
    }

    if (tas_count_act && (div > 1)) { /* SAT counter analyze must be printed */
        vtss_port_no_t  chip_port = VTSS_CHIP_PORT(tas_port-1);
        u32 count, old_count, equal_count, index = 0;
        BOOL interval_start;
        i32 off;
        vtss_timestamp_t ts0, ts1, distance;
        u64              tc;
        struct {
            u8               count;
            vtss_timestamp_t ts;
        } buffer[1000];

        _vtss_ts_domain_timeofday_get(NULL, 0, &ts0, &tc);
        REG_RD(VTSS_ASM_RX_UC_CNT(chip_port), &old_count);
        interval_start = FALSE;
        equal_count = 0;
        index = 0;
        while (1) {
            _vtss_ts_domain_timeofday_get(NULL, 0, &ts1, &tc);
            REG_RD(VTSS_ASM_TX_UC_CNT(chip_port), &count);
            equal_count = (count == old_count) ? (equal_count + 1) : 0;
            if ((equal_count == 0) && (interval_start == TRUE)) {    // Start of interval
                interval_start = FALSE;
                buffer[index].count = count;
                buffer[index].ts = ts1;
                index++;
            } else if (equal_count == 50) {    // No frame transmitted in approx 193 us (Frame size 500). Next transmission is start of interval
                interval_start = TRUE;
            }
            old_count = count;
            if (((ts1.seconds - ts0.seconds) > 2) || (index >= 1000)) break;
        }

        for (i=0; i<index; ++i) {
            if (i > 0) {
                distance = buffer[i].ts;
                (void)vtss_timestampSub(&distance, &buffer[i-1].ts);
                off = distance.nanoseconds - CYCLE_TIME;
                pr("count %u  sec %u  nsec %u  distance %u  off %i\n", buffer[i].count, buffer[i].ts.seconds, buffer[i].ts.nanoseconds, distance.nanoseconds, off);
            }
        }
        pr("index %u  chip_port %u  ts1.seconds %u  ts0.seconds %u\n", index, chip_port, ts1.seconds, ts0.seconds);
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
                cost_ct += VTSS_SNPRINTF(cost_buf + cost_ct, sizeof(cost_buf) - cost_ct, "%s%2u",
                                delim,
                                VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(value));
            }
            pr("%-32s: %s\n", "DWRR_COST", "C0 C1 C2 C3 C4 C5 C6 C7");
            pr("%-32s: %s\n", "", cost_buf);
    
            pr("\n");
        }

        vtss_debug_print_header(pr, "DSM calendar (index)");
        for (i = 0; i < FA_DSM_CAL_ROW_CNT; i++) {
            addr = VTSS_DSM_TAXI_CAL_CFG(i);
            REG_RD(addr, &value);
            len = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(value);
            pr("%u: ", i);
            for (j = 0; j <= len; j++) {
                REG_WR(addr, VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(j));
                REG_RD(addr, &value);
                pr("%02u%s",
                   VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(value),
                   j == len ? "\n" : (j % 8) == 7 ? "-" : ".");
            }
        }
        pr("\n");

        vtss_debug_print_header(pr, "DSM calendar (devices)");
        for (i = 0; i < FA_DSM_CAL_ROW_CNT; i++) {
            addr = VTSS_DSM_TAXI_CAL_CFG(i);
            REG_RD(addr, &value);
            len = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_LEN(value);
            pr("%u: ", i);
            for (j = 0; j <= len; j++) {
                REG_WR(addr, VTSS_F_DSM_TAXI_CAL_CFG_CAL_IDX(j));
                REG_RD(addr, &value);
                value = VTSS_X_DSM_TAXI_CAL_CFG_CAL_CUR_VAL(value);
                pr("%02u%s",
                   value < FA_DSM_CAL_COL_CNT ? fa_dsm_cal[i][value] : 88,
                   j == len ? "\n" : (j % 8) == 7 ? "-" : ".");
            }
        }
        pr("\n");

        vtss_debug_print_header(pr, "DSM groups");
        for (i = 0; i < FA_DSM_CAL_ROW_CNT; i++) {
            pr("%u: ", i);
            for (j = 0; j < FA_DSM_CAL_COL_CNT; j++) {
                pr("%02u%s",
                   fa_dsm_cal[i][j],
                   j == (FA_DSM_CAL_COL_CNT - 1) ? "\n" : (j % 8) == 7 ? "-" : ".");
            }
        }
        pr("\n");

        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            char buf[32];
            u32  port, tgt;
            if (info->port_list[port_no]) {
                port = VTSS_CHIP_PORT(port_no);
                VTSS_SPRINTF(buf, "Port %u (%u)", port, port_no);
                vtss_fa_debug_reg_header(pr, buf);
                if (vtss_fa_port_is_high_speed(vtss_state, port)) {
                    tgt = VTSS_TO_HIGH_DEV(port);
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_ENABLE_CONFIG(tgt), port, "DEV10G:ENABLE_CONFIG");
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_VERIF_CONFIG(tgt), port, "DEV10G:VERIF_CONFIG");
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV10G_MM_STATUS(tgt), port, "DEV10G:MM_STATUS");
                } else {
                    tgt = VTSS_TO_DEV2G5(port);
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_ENABLE_CONFIG(tgt), port, "DEV1G:ENABLE_CONFIG");
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_VERIF_CONFIG(tgt), port, "DEV1G:VERIF_CONFIG");
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DEV1G_MM_STATUS(tgt), port, "DEV1G:MM_STATUS");
                }
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DSM_PREEMPT_CFG(port), port, "DSM:PREEMPT_CFG");
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_DSM_IPG_SHRINK_CFG(port), port, "DSM:IPG_SHRINK_CFG");
                for (i = 0; i < 8; i++) {
                    j = FA_HSCH_L0_SE(port, i);
                    vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_HSCH_HSCH_L0_CFG(j), j, "HSCH_L0_CFG");
                }
                pr("\n");
            }
        }

        for (i = 0; i < 5120; i++) {
            REG_RD(VTSS_QRES_RES_STAT_CUR(i), &value);
            if (value != 0) {
                vtss_fa_debug_reg_header(pr, "QRES");
                vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_QRES_RES_STAT_CUR(i), i, "QRES:RES_STAT_CUR");
            }
        }

    }

    if (!info->has_action || shape_act) { /* Shapers configuration must be printed */
        vtss_debug_print_header(pr, "QoS Shapers");
        pr("Port configuration:\n");
        pr("-------------------\n");
        for (port_no = VTSS_PORT_NO_START; port_no < (vtss_state->port_count + 2); port_no++) {
            u32 layer = 2, se;
            if (port_no < vtss_state->port_count) {
                if (info->port_list[port_no] == 0) {
                    continue;
                }
                chip_port = VTSS_CHIP_PORT(port_no);
                pr("Port %u (chip port %u):\n", port_no, chip_port);
            } else {
                i = (port_no - vtss_state->port_count);
                chip_port = (VTSS_CHIP_PORT_CPU_0 + i);
                pr("Port CPU_%u (chip port %u):\n", i, chip_port);
            }
            se = chip_port;
            pr("Port shaper, layer %u, se %u:\n", layer, se);
            fa_debug_qos_scheduler_element(vtss_state, pr, layer, se);
    
            layer = 0;
            for (i = 0; i < 8; i++) {
                se = FA_HSCH_L0_SE(chip_port, i);
                pr("Queue %u shaper, layer %u, se %u:\n", i, layer, se);
                fa_debug_qos_scheduler_element(vtss_state, pr, layer, se);
            }
        }
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
#ifdef VTSS_FEATURE_QOS_WRED_V3
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
#endif
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
                pcp_de0_ct += VTSS_SNPRINTF(pcp_de0_buf + pcp_de0_ct, sizeof(pcp_de0_buf) - pcp_de0_ct, "%s%u",
                                delim,
                                VTSS_X_REW_PCP_MAP_DE0_PCP_DE0(pcp_de0));
                pcp_de1_ct += VTSS_SNPRINTF(pcp_de1_buf + pcp_de1_ct, sizeof(pcp_de1_buf) - pcp_de1_ct, "%s%u",
                                delim,
                                VTSS_X_REW_PCP_MAP_DE1_PCP_DE1(pcp_de1));
                dei_de0_ct += VTSS_SNPRINTF(dei_de0_buf + dei_de0_ct, sizeof(dei_de0_buf) - dei_de0_ct, "%s%u",
                                delim,
                                VTSS_X_REW_DEI_MAP_DE0_DEI_DE0(dei_de0));
                dei_de1_ct += VTSS_SNPRINTF(dei_de1_buf + dei_de1_ct, sizeof(dei_de1_buf) - dei_de1_ct, "%s%u",
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
    u32 i, port;

    VTSS_D("Enter");

    /* Get the system clock in Hz */
    lb_clk_in_hz = lb_clk_in_hz_get(vtss_state);

    // Initialize policers
    VTSS_RC(fa_qos_policer_init(vtss_state));

    // Initialize shaper leak chains
    VTSS_RC(fa_qos_leak_list_init(vtss_state));

    // Initialize service LBs
    VTSS_RC(fa_qos_lb_init(vtss_state));

    // Initialize the TAS max number of GCL
    REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM_MAX(VTSS_TAS_NUMBER_OF_LISTS-1), VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM_MAX);

    // The maximum length of a GCL must be a multiple number of blocks
    if (VTSS_QOS_TAS_GCL_LEN_MAX % VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK) {
        VTSS_E("VTSS_QOS_TAS_GCL_LEN_MAX %u is invalid", VTSS_QOS_TAS_GCL_LEN_MAX);
    }

    for (u32 port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_state->qos.tas.tas_gcl_state[port_no].stop_ongoing = FALSE;
        vtss_state->qos.tas.tas_gcl_state[port_no].new_list_scheduled = FALSE;
        vtss_state->qos.tas.tas_gcl_state[port_no].config_change_error = 0;
        vtss_state->qos.tas.tas_gcl_state[port_no].curr_list_idx = TAS_LIST_IDX_NONE;
        vtss_state->qos.tas.tas_gcl_state[port_no].trunk_list_idx = TAS_LIST_IDX_NONE;
        vtss_state->qos.tas.tas_gcl_state[port_no].next_list_idx = TAS_LIST_IDX_NONE;
        for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
            vtss_state->qos.tas.port_conf[port_no].max_sdu[i] = 24 * 64;   /* Default register value is 24. Resolution is 64 bytes */
        }
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        vtss_state->qos.fp.port_conf[port_no].add_frag_size = 1;    // P_MIN_SIZE default value is 1
#endif
    }
    VTSS_MEMSET(&vtss_state->qos.tas.tas_lists, 0, sizeof(vtss_state->qos.tas.tas_lists));
    VTSS_MEMSET(&vtss_state->qos.tas.tas_profiles, 0, sizeof(vtss_state->qos.tas.tas_profiles));
    VTSS_MEMSET(&vtss_state->qos.tas.tas_entry_blocks, 0, sizeof(vtss_state->qos.tas.tas_entry_blocks));
    VTSS_MEMSET(&vtss_state->qos.tas.tas_entry_rows, 0, sizeof(vtss_state->qos.tas.tas_entry_rows));

    for (i = 0; i < VTSS_TAS_NUMBER_OF_LISTS; i++) {
        vtss_state->qos.tas.tas_lists[i].profile_idx = TAS_PROFILE_IDX_NONE;
        vtss_state->qos.tas.tas_lists[i].hold_profile_idx = TAS_PROFILE_IDX_NONE;
    }

    /* Normal scheduling mode for CPU ports */
    for (port = VTSS_CHIP_PORT_CPU_0; port <= VTSS_CHIP_PORT_CPU_1; port++) {
        REG_WR(VTSS_XQS_QMAP_PORT_MODE(port),
               VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(0) |
               VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(0));
        REG_WR(VTSS_XQS_QMAP_VPORT_TBL(0, port), port * 8);
    }

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

static vtss_rc fa_qos_port_map_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    u32            port;

    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        // Enable cut-through for ingress queues, disable for egress queues
        REG_WR(VTSS_QSYS_IQUEUE_CFG(port), VTSS_F_QSYS_IQUEUE_CFG_CT_ENA(0xff));
        REG_WRM(VTSS_XQS_FWD_CT_CFG(port),
                VTSS_F_XQS_FWD_CT_CFG_FWD_CT_ENA(0),
                VTSS_M_XQS_FWD_CT_CFG_FWD_CT_ENA);
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        // Always enable Rx frame preemption
        DEV_WR(ENABLE_CONFIG, port,
               VTSS_F_DEV1G_ENABLE_CONFIG_MM_RX_ENA(1) |
               VTSS_F_DEV1G_ENABLE_CONFIG_MM_TX_ENA(1) |
               VTSS_F_DEV1G_ENABLE_CONFIG_KEEP_S_AFTER_D(0));

        DEV_WRM(DEV_PFRAME_CFG, port,
                VTSS_F_DEV1G_DEV_PFRAME_CFG_DEV_FRAGMENT_IFG(12),
                VTSS_M_DEV1G_DEV_PFRAME_CFG_DEV_FRAGMENT_IFG);

        if (!VTSS_PORT_IS_2G5(port)) {
            REG_WRM(VTSS_DEV10G_MAC_ADV_CHK_CFG(VTSS_TO_HIGH_DEV(port)),
                    VTSS_F_DEV10G_MAC_ADV_CHK_CFG_SFD_CHK_ENA(0),
                    VTSS_M_DEV10G_MAC_ADV_CHK_CFG_SFD_CHK_ENA);
        }
#endif
    }
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

#if defined(VTSS_FEATURE_QOS_TAS)
        state->tas_conf_set        = fa_qos_tas_conf_set;
        state->tas_port_conf_set   = fa_qos_tas_port_conf_set;
        state->tas_port_status_get = fa_qos_tas_port_status_get;
#endif

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        state->fp_port_conf_set = fa_qos_fp_port_conf_set;
        state->fp_port_status_get = fa_qos_fp_port_status_get;
#endif
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_qos_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_RC(fa_qos_port_map_set(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA && VTSS_FEATURE_QOS */
