// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_CLOCK
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_CLOCK)

// ***************************************************************************
//
//  Direct register access functions to be used for testing
//
// ***************************************************************************

/* Directly read HW register */
vtss_rc vtss_clock_rd(const vtss_inst_t inst, const u32 addr, u32 *const value)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.rd, addr, value);
    }
    VTSS_EXIT();
    VTSS_I("reg addr: 0x%x, value: 0x%x", addr, *value);

    return rc;
}

/* Directly write HW register */
vtss_rc vtss_clock_wr(const vtss_inst_t inst, const u32 addr, const u32 value)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("reg addr: 0x%x, value: 0x%x", addr, value);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.wr, addr, value);
    }
    VTSS_EXIT();

    return rc;
}

/* Directly write HW register with mask I.e. read-modify-write*/
vtss_rc vtss_clock_wrm(const vtss_inst_t inst,
                       const u32         addr,
                       const u32         value,
                       const u32         mask)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("reg addr: 0x%x, value: 0x%x, mask: 0x%x", addr, value, mask);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.wrm, addr, value, mask);
    }
    VTSS_EXIT();

    return rc;
}

// ***************************************************************************
//
//  Configuration API
//
// ***************************************************************************

/* Set global enable */
vtss_rc vtss_clock_global_enable_set(const vtss_inst_t                inst,
                                     const vtss_clock_global_enable_t ena)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("ena: %d", ena);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.global_enable_set, ena);
    }
    VTSS_EXIT();

    return rc;
}

/* Get global enable */
vtss_rc vtss_clock_global_enable_get(const vtss_inst_t                 inst,
                                     vtss_clock_global_enable_t *const ena)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.global_enable_get, ena);
    }
    VTSS_EXIT();
    VTSS_I("ena: %d", *ena);

    return rc;
}

/* Pull SW reset and release again */
vtss_rc vtss_clock_global_sw_reset(const vtss_inst_t inst)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("sw reset");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.global_sw_reset);
    }
    VTSS_EXIT();

    return rc;
}

/* shutdown */
vtss_rc vtss_clock_shutdown(const vtss_inst_t inst)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("shutdown");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.clock_shutdown);
    }
    VTSS_EXIT();

    return rc;
}

/* Set Clock selection mode */
vtss_rc vtss_clock_selection_mode_set(const vtss_inst_t            inst,
                                      const vtss_clock_dpll_inst_t dpll,
                                      const vtss_clock_selection_conf_t
                                          *const conf)

{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("dpll: %u, conf.mode: %d, conf.clock_input: %d", dpll, conf->mode,
           conf->clock_input);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            if (conf->clock_input < vtss_state->clock.clock_input_cnt) {
                rc = VTSS_FUNC(clock.selection_mode_set, dpll, conf);
            } else {
                VTSS_E("illegal clock_input value: %u", conf->clock_input);
                rc = VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

/* Get Clock selection mode */
vtss_rc vtss_clock_selection_mode_get(const vtss_inst_t                  inst,
                                      const vtss_clock_dpll_inst_t       dpll,
                                      vtss_clock_selection_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.selection_mode_get, dpll, conf);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("dpll: %u, conf.mode: %d, conf.clock_input: %d", dpll, conf->mode,
           conf->clock_input);

    return rc;
}

vtss_rc vtss_clock_operation_conf_set(const vtss_inst_t                   inst,
                                      const vtss_clock_dpll_inst_t        dpll,
                                      const vtss_clock_dpll_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I(
        "dpll: %u, conf.mode: %d, conf.holdoff: %d, conf.holdover: %d, conf.wtr: %d",
        dpll, conf->mode, conf->holdoff, conf->holdover, conf->wtr);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.operation_conf_set, dpll, conf);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_operation_conf_get(const vtss_inst_t             inst,
                                      const vtss_clock_dpll_inst_t  dpll,
                                      vtss_clock_dpll_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.operation_conf_get, dpll, conf);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I(
        "dpll: %u, conf.mode: %d, conf.holdoff: %d, conf.holdover: %d, conf.wtr: %d",
        dpll, conf->mode, conf->holdoff, conf->holdover, conf->wtr);

    return rc;
}

vtss_rc vtss_clock_ho_stack_conf_set(const vtss_inst_t            inst,
                                     const vtss_clock_dpll_inst_t dpll,
                                     const vtss_clock_ho_stack_conf_t
                                         *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("dpll: %u, conf.ho_post_filtering_bw: %u, conf.ho_qual_time_conf: %u",
           dpll, conf->ho_post_filtering_bw, conf->ho_qual_time_conf);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.ho_stack_conf_set, dpll, conf);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_ho_stack_conf_get(const vtss_inst_t                 inst,
                                     const vtss_clock_dpll_inst_t      dpll,
                                     vtss_clock_ho_stack_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.ho_stack_conf_get, dpll, conf);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("dpll: %u, conf.ho_post_filtering_bw: %u, conf.ho_qual_time_conf: %u",
           dpll, conf->ho_post_filtering_bw, conf->ho_qual_time_conf);

    return rc;
}

vtss_rc vtss_clock_ho_stack_content_get(const vtss_inst_t            inst,
                                        const vtss_clock_dpll_inst_t dpll,
                                        vtss_clock_ho_stack_content_t
                                            *const cont)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;
    int     level;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.ho_stack_content_get, dpll, cont);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    for (level = 0; level < VTSS_CLOCK_HO_STACK_SIZE; level++) {
        VTSS_I("dpll: %u, cont.stack_value[%u]: %" PRIu64 "", dpll, level,
               cont->stack_value[level]);
    }
    VTSS_I(
        "dpll: %u, cont.ho_sel: %u, cont.ho_min_fill_lvl: %u, cont.ho_filled: %d",
        dpll, cont->ho_sel, cont->ho_min_fill_lvl, cont->ho_filled);

    return rc;
}

vtss_rc vtss_clock_dco_frequency_offset_set(const vtss_inst_t            inst,
                                            const vtss_clock_dpll_inst_t dpll,
                                            const i64                    offset)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("DPLL: %u, offset: %" PRIi64 "", dpll, offset);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.dco_frequency_offset_set, dpll, offset);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_dco_frequency_offset_get(const vtss_inst_t            inst,
                                            const vtss_clock_dpll_inst_t dpll,
                                            i64 *const                   offset)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.dco_frequency_offset_get, dpll, offset);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("DPLL: %u, offset: %" PRIi64 "", dpll, *offset);

    return rc;
}

vtss_rc vtss_clock_output_filter_bw_set(const vtss_inst_t inst,
                                        const u8          clock_output,
                                        const u32         bw_100uhz)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, bw_100uhz: %u", clock_output, bw_100uhz);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_filter_bw_set, clock_output, bw_100uhz);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_filter_bw_get(const vtss_inst_t inst,
                                        const u8          clock_output,
                                        u32              *bw_100uhz)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_filter_bw_get, clock_output, bw_100uhz);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, bw_100uhz: %u", clock_output, *bw_100uhz);

    return rc;
}

vtss_rc vtss_clock_output_filter_lock_fast_set(const vtss_inst_t inst,
                                               const u8          clock_output)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, filter lock fast", clock_output);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_filter_lock_fast_set, clock_output);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_filter_lock_fast_get(const vtss_inst_t inst,
                                               const u8          clock_output,
                                               BOOL             *lock_completed)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_filter_lock_fast_get, clock_output,
                           lock_completed);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, lock_completed: %s", clock_output,
           *lock_completed ? "TRUE" : "FALSE");

    return rc;
}

vtss_rc vtss_clock_output_psl_conf_set(const vtss_inst_t inst,
                                       const u8          clock_output,
                                       const vtss_clock_psl_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I(
        "clock_output: %u, conf.limit_ppb: %u, conf.phase_build_out_ena %d, conf.ho_based %d",
        clock_output, conf->limit_ppb, conf->phase_build_out_ena,
        conf->ho_based);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_psl_conf_set, clock_output, conf);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_psl_conf_get(const vtss_inst_t inst,
                                       const u8          clock_output,
                                       vtss_clock_psl_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_psl_conf_get, clock_output, conf);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I(
        "clock_output: %u, conf.limit_ppb: %u, conf.phase_build_out_ena %d, conf.ho_based %d",
        clock_output, conf->limit_ppb, conf->phase_build_out_ena,
        conf->ho_based);

    return rc;
}

vtss_rc vtss_clock_adj_frequency_set(const vtss_inst_t inst,
                                     const u8          clock_output,
                                     const i64         adj)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, adj: %" PRIi64 "", clock_output, adj);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.adj_frequency_set, clock_output, adj);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_adj_frequency_get(const vtss_inst_t inst,
                                     const u8          clock_output,
                                     i64 *const        adj)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.adj_frequency_get, clock_output, adj);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, adj: %" PRIi64 "", clock_output, *adj);

    return rc;
}

vtss_rc vtss_clock_adj_phase_set(const vtss_inst_t inst,
                                 const u8          clock_output,
                                 const i32         adj)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, adj: %d", clock_output, adj);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < 16) {
            rc = VTSS_FUNC(clock.adj_phase_set, clock_output, adj);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_adj_phase_get(const vtss_inst_t inst,
                                 BOOL *const       adj_ongoing)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(clock.adj_phase_get, adj_ongoing);
    }
    VTSS_EXIT();
    VTSS_I("adj_ongoing: %s", *adj_ongoing ? "TRUE" : "FALSE");

    return rc;
}

vtss_rc vtss_clock_priority_set(const vtss_inst_t            inst,
                                const vtss_clock_dpll_inst_t dpll,
                                const u8                     clock_input,
                                const vtss_clock_priority_selector_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("dpll: %u, clock_input: %u, conf.priority: %d, conf.enable %d", dpll,
           clock_input, conf->priority, conf->enable);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            if (clock_input < vtss_state->clock.clock_input_cnt) {
                rc = VTSS_FUNC(clock.priority_set, dpll, clock_input, conf);
            } else {
                VTSS_E("illegal clock_input value: %u", clock_input);
                rc = VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_priority_get(const vtss_inst_t            inst,
                                const vtss_clock_dpll_inst_t dpll,
                                const u8                     clock_input,
                                vtss_clock_priority_selector_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            if (clock_input < vtss_state->clock.clock_input_cnt) {
                rc = VTSS_FUNC(clock.priority_get, dpll, clock_input, conf);
            } else {
                VTSS_E("illegal clock_input value: %u", clock_input);
                rc = VTSS_RC_ERROR;
            }
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("dpll: %u, clock_input: %u, conf.priority: %d, conf.enable %d", dpll,
           clock_input, conf->priority, conf->enable);

    return rc;
}

vtss_rc vtss_clock_input_frequency_set(const vtss_inst_t inst,
                                       const u8          clock_input,
                                       const u32         freq_khz,
                                       const BOOL        use_internal_clock_src)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_input: %u, freq_khz: %u, use_internal_clock_src %d",
           clock_input, freq_khz, use_internal_clock_src);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_frequency_set, clock_input, freq_khz,
                           use_internal_clock_src);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_frequency_get(const vtss_inst_t inst,
                                       const u8          clock_input,
                                       u32 *const        freq_khz,
                                       BOOL *const       use_internal_clock_src)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_frequency_get, clock_input, freq_khz,
                           use_internal_clock_src);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_input: %u, freq_khz: %u, use_internal_clock_src %s",
           clock_input, *freq_khz, *use_internal_clock_src ? "TRUE" : "FALSE");

    return rc;
}

vtss_rc vtss_clock_input_frequency_ratio_set(const vtss_inst_t inst,
                                             const u8          clock_input,
                                             const u32         freq_khz,
                                             const vtss_clock_ratio_t
                                                 *const ratio,
                                             const BOOL use_internal_clock_src)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I(
        "clock_input: %u, freq_khz: %u, ratio: %u/%u, use_internal_clock_src %d",
        clock_input, freq_khz, ratio->num, ratio->den, use_internal_clock_src);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_frequency_ratio_set, clock_input,
                           freq_khz, ratio, use_internal_clock_src);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_frequency_ratio_get(const vtss_inst_t inst,
                                             const u8          clock_input,
                                             u32 *const        freq_khz,
                                             vtss_clock_ratio_t *const ratio,
                                             BOOL *const use_internal_clock_src)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_frequency_ratio_get, clock_input,
                           freq_khz, ratio, use_internal_clock_src);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_input: %u, freq_khz: %u, ratio %u/%u, use_internal_clock_src %s",
           clock_input, *freq_khz, ratio->num, ratio->den,
           *use_internal_clock_src ? "TRUE" : "FALSE");

    return rc;
}

vtss_rc vtss_clock_output_frequency_set(const vtss_inst_t inst,
                                        const u8          clock_output,
                                        const u32         freq_khz,
                                        const u32         par_freq_khz)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, freq_khz: %u, par_freq_khz: %u", clock_output,
           freq_khz, par_freq_khz);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_frequency_set, clock_output, freq_khz,
                           par_freq_khz);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_frequency_get(const vtss_inst_t inst,
                                        const u8          clock_output,
                                        u32 *const        freq_khz,
                                        u32 *const        par_freq_khz)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_frequency_get, clock_output, freq_khz,
                           par_freq_khz);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, freq_khz: %u, par_freq_khz: %u", clock_output,
           *freq_khz, *par_freq_khz);

    return rc;
}

vtss_rc vtss_clock_output_frequency_ratio_set(const vtss_inst_t inst,
                                              const u8          clock_output,
                                              const u32         freq_khz,
                                              const u32         par_freq_khz,
                                              const vtss_clock_ratio_t
                                                  *const ratio)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, freq_khz: %u, par_freq_khz: %u, ratio %u/%u",
           clock_output, freq_khz, par_freq_khz, ratio->num, ratio->den);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_frequency_ratio_set, clock_output,
                           freq_khz, par_freq_khz, ratio);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_frequency_ratio_get(const vtss_inst_t inst,
                                              const u8          clock_output,
                                              u32 *const        freq_khz,
                                              u32 *const        par_freq_khz,
                                              vtss_clock_ratio_t *const ratio)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_frequency_ratio_get, clock_output,
                           freq_khz, par_freq_khz, ratio);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, freq_khz: %u, par_freq_khz: %u, ratio %u/%u",
           clock_output, *freq_khz, *par_freq_khz, ratio->num, ratio->den);

    return rc;
}

vtss_rc vtss_clock_output_level_set(const vtss_inst_t inst,
                                    const u8          clock_output,
                                    const u16         level_mv)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, level_mv: %u", clock_output, level_mv);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_level_set, clock_output, level_mv);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_level_get(const vtss_inst_t inst,
                                    const u8          clock_output,
                                    u16 *const        level_mv)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_level_get, clock_output, level_mv);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, level_mv: %u", clock_output, *level_mv);

    return rc;
}

vtss_rc vtss_clock_output_selector_set(const vtss_inst_t inst,
                                       const u8          clock_output,
                                       const vtss_clock_input_selector_t
                                           *const input)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_output: %u, input.input_type: %d, input.input_inst: %d",
           clock_output, input->input_type, input->input_inst);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_selector_set, clock_output, input);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_output_selector_get(const vtss_inst_t inst,
                                       const u8          clock_output,
                                       vtss_clock_input_selector_t *const input)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_output < vtss_state->clock.clock_output_cnt) {
            rc = VTSS_FUNC(clock.output_selector_get, clock_output, input);
        } else {
            VTSS_E("illegal clock_output value: %u", clock_output);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_output: %u, input.input_type: %d, input.input_inst: %d",
           clock_output, input->input_type, input->input_inst);

    return rc;
}

vtss_rc vtss_clock_input_alarm_conf_set(const vtss_inst_t inst,
                                        const u8          clock_input,
                                        const vtss_clock_input_conf_t
                                            *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I(
        "clock_input: %u, conf.los_active_high: %d, conf.alarm_ena: %d,%d,%d,%d,%d,%d ",
        clock_input, conf->los_active_high, conf->alarm_ena.los,
        conf->alarm_ena.pfm, conf->alarm_ena.cfm, conf->alarm_ena.scm,
        conf->alarm_ena.gst, conf->alarm_ena.lol);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_alarm_conf_set, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_alarm_conf_get(const vtss_inst_t inst,
                                        const u8          clock_input,
                                        vtss_clock_input_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_alarm_conf_get, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I(
        "clock_input: %u, conf.los_active_high: %d, conf.alarm_ena: %d,%d,%d,%d,%d,%d ",
        clock_input, conf->los_active_high, conf->alarm_ena.los,
        conf->alarm_ena.pfm, conf->alarm_ena.cfm, conf->alarm_ena.scm,
        conf->alarm_ena.gst, conf->alarm_ena.lol);

    return rc;
}

vtss_rc vtss_clock_input_cfm_conf_set(const vtss_inst_t inst,
                                      const u8          clock_input,
                                      const vtss_clock_cfm_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_input: %u, conf.cfm_set_ppb: %u, conf.cfm_clr_ppb: %u",
           clock_input, conf->cfm_set_ppb, conf->cfm_clr_ppb);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_cfm_conf_set, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_cfm_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_cfm_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_cfm_conf_get, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_input: %u, conf.cfm_set_ppb: %u, conf.cfm_clr_ppb: %u",
           clock_input, conf->cfm_set_ppb, conf->cfm_clr_ppb);

    return rc;
}

vtss_rc vtss_clock_input_pfm_conf_set(const vtss_inst_t inst,
                                      const u8          clock_input,
                                      const vtss_clock_pfm_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_input: %u, conf.pfm_set_ppb: %u, conf.pfm_clr_ppb: %u",
           clock_input, conf->pfm_set_ppb, conf->pfm_clr_ppb);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_pfm_conf_set, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_pfm_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_pfm_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_pfm_conf_get, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_input: %u, conf.pfm_set_ppb: %u, conf.pfm_clr_ppb: %u",
           clock_input, conf->pfm_set_ppb, conf->pfm_clr_ppb);

    return rc;
}

vtss_rc vtss_clock_input_gst_conf_set(const vtss_inst_t inst,
                                      const u8          clock_input,
                                      const vtss_clock_gst_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I(
        "clock_input: %u, conf.disqualification_time_us: %d, conf.qualification_time_us: %d,conf.los %d,conf.pfm %d,conf.cfm %d,conf.scm %d,conf.lol %d ",
        clock_input, conf->disqualification_time_us,
        conf->qualification_time_us, conf->los, conf->pfm, conf->cfm, conf->scm,
        conf->lol);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_gst_conf_set, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_input_gst_conf_get(const vtss_inst_t            inst,
                                      const u8                     clock_input,
                                      vtss_clock_gst_conf_t *const conf)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_gst_conf_get, clock_input, conf);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I(
        "clock_input: %u, conf.disqualification_time_us: %d, conf.qualification_time_us: %d,conf.los %d,conf.pfm %d,conf.cfm %d,conf.scm %d,conf.lol %d ",
        clock_input, conf->disqualification_time_us,
        conf->qualification_time_us, conf->los, conf->pfm, conf->cfm, conf->scm,
        conf->lol);

    return rc;
}

// ***************************************************************************
//
//  Status API
//
// ***************************************************************************

vtss_rc vtss_clock_selector_state_get(const vtss_inst_t            inst,
                                      const vtss_clock_dpll_inst_t dpll,
                                      vtss_clock_selector_state_t
                                          *const selector_state,
                                      u8 *const  clock_input)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.selector_state_get, dpll, selector_state,
                           clock_input);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_D("dpll: %d, selector_state: %d, clock_input %d", dpll,
           *selector_state, *clock_input);

    return rc;
}

vtss_rc vtss_clock_dpll_state_get(const vtss_inst_t              inst,
                                  const vtss_clock_dpll_inst_t   dpll,
                                  vtss_clock_dpll_state_t *const pll_state)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.dpll_state_get, dpll, pll_state);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_D("dpll: %d, pll_state: freq_lock %d, phase_lock %d, losx %d, lol %d",
           dpll, pll_state->pll_freq_lock, pll_state->pll_phase_lock,
           pll_state->pll_losx, pll_state->pll_lol);

    return rc;
}

vtss_rc vtss_clock_ho_stack_frequency_offset_get(const vtss_inst_t inst,
                                                 const vtss_clock_dpll_inst_t
                                                            dpll,
                                                 i64 *const offset)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.ho_stack_frequency_offset_get, dpll, offset);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("dpll: %d, offset: %" PRIi64 "", dpll, *offset);

    return rc;
}

vtss_rc vtss_clock_input_state_get(const vtss_inst_t               inst,
                                   const u8                        clock_input,
                                   vtss_clock_input_state_t *const input_state)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_state_get, clock_input, input_state);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_D("clock_input: %d, input_state: los %d, pfm %d, cfm %d, scm %d, lol %d",
           clock_input, input_state->los, input_state->pfm, input_state->cfm,
           input_state->scm, input_state->lol);

    return rc;
}

// ***************************************************************************
//
//  Event (interrupt) handling API
//
// ***************************************************************************

vtss_rc vtss_clock_input_event_poll(const vtss_inst_t inst,
                                    const u8          clock_input,
                                    vtss_clock_input_event_type_t *const ev_mask)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_event_poll, clock_input, ev_mask);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("clock_input: %d, ev_mask: %x", clock_input, *ev_mask);

    return rc;
}

vtss_rc vtss_clock_input_event_enable(const vtss_inst_t inst,
                                      const u8          clock_input,
                                      const vtss_clock_input_event_type_t
                                                 ev_mask,
                                      const BOOL enable)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("clock_input: %d, ev_mask: %x enable %d", clock_input, ev_mask,
           enable);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (clock_input < vtss_state->clock.clock_input_cnt) {
            rc = VTSS_FUNC(clock.input_event_enable, clock_input, ev_mask,
                           enable);
        } else {
            VTSS_E("illegal clock_input value: %u", clock_input);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

vtss_rc vtss_clock_dpll_event_poll(const vtss_inst_t                   inst,
                                   const vtss_clock_dpll_inst_t        dpll,
                                   vtss_clock_dpll_event_type_t *const ev_mask)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.dpll_event_poll, dpll, ev_mask);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    VTSS_I("dpll: %d, ev_mask: %x", dpll, *ev_mask);

    return rc;
}

vtss_rc vtss_clock_dpll_event_enable(const vtss_inst_t                  inst,
                                     const vtss_clock_dpll_inst_t       dpll,
                                     const vtss_clock_dpll_event_type_t ev_mask,
                                     const BOOL                         enable)
{
    vtss_state_t
           *vtss_state; /* set by the vtss_inst_check function called below */
    vtss_rc rc;

    VTSS_I("dpll: %d, ev_mask: %x, enable %d", dpll, ev_mask, enable);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (dpll < vtss_state->clock.dpll_cnt) {
            rc = VTSS_FUNC(clock.dpll_event_enable, dpll, ev_mask, enable);
        } else {
            VTSS_E("illegal dpll value: %u", dpll);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();

    return rc;
}

#endif /* VTSS_FEATURE_CLOCK */
