// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_TIMESTAMP)
static vtss_rc lan966x_ts_timeofday_read(vtss_state_t *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_get(vtss_state_t     *vtss_state,
                                        vtss_timestamp_t *ts,
                                        u64              *tc)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_next_pps_get(vtss_state_t *vtss_state,
                                                 vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_prev_pps_get(vtss_state_t *vtss_state,
                                                 vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_set_delta(vtss_state_t *vtss_state,
                                              const vtss_timestamp_t *ts, BOOL negative)
{
    return VTSS_RC_OK;
}

static u32 lan966x_ts_ns_cnt_get(vtss_inst_t inst)
{
    return 0;
}

static vtss_rc lan966x_ts_timeofday_one_sec(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_freq_offset_get(vtss_state_t *vtss_state, i32 *const adj)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_external_clock_mode_set(vtss_state_t *vtss_state, int idx)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_saved_timeofday_get(vtss_state_t *vtss_state,
                                                        vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_next_pps_set(vtss_state_t *vtss_state,
                                                 const vtss_timestamp_t *const ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_delay_asymmetry_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_internal_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timestamp_get(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_status_change(vtss_state_t         *vtss_state,
                                        const vtss_port_no_t port_no)
{
    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

vtss_rc vtss_lan966x_ts_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state,
                                                  u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_next_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_ts_init(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = lan966x_ts_timeofday_get;
        state->timeofday_raw = lan966x_ts_timeofday_read;
        state->timeofday_set = lan966x_ts_timeofday_set;
        state->timeofday_set_delta = lan966x_ts_timeofday_set_delta;
        state->timeofday_next_pps_get = lan966x_ts_timeofday_next_pps_get;
        state->timeofday_prev_pps_get = lan966x_ts_timeofday_prev_pps_get;
        state->timeofday_offset_set = lan966x_ts_timeofday_offset_set;
        state->ns_cnt_get = lan966x_ts_ns_cnt_get;
        state->timeofday_one_sec = lan966x_ts_timeofday_one_sec;
        state->adjtimer_set = lan966x_ts_adjtimer_set;
        state->freq_offset_get = lan966x_ts_freq_offset_get;
        state->external_clock_mode_set = lan966x_ts_external_clock_mode_set;
        state->alt_clock_saved_get = lan966x_ts_alt_clock_saved_get;
        state->alt_clock_saved_timeofday_get = lan966x_ts_alt_clock_saved_timeofday_get;
        state->alt_clock_mode_set = lan966x_ts_alt_clock_mode_set;
        state->timeofday_next_pps_set = lan966x_ts_timeofday_next_pps_set;
        state->ingress_latency_set = lan966x_ts_ingress_latency_set;
        state->p2p_delay_set = lan966x_ts_p2p_delay_set;
        state->egress_latency_set = lan966x_ts_egress_latency_set;
        state->delay_asymmetry_set = lan966x_ts_delay_asymmetry_set;
        state->operation_mode_set = lan966x_ts_operation_mode_set;
        state->internal_mode_set = lan966x_ts_internal_mode_set;
        state->timestamp_get = lan966x_ts_timestamp_get;
        state->timestamp_id_release = lan966x_ts_timestamp_id_release;
        state->status_change = lan966x_ts_status_change;
        state->domain_timeofday_get = lan966x_ts_domain_timeofday_get;
        state->domain_timeofday_set = lan966x_ts_domain_timeofday_set;
        state->domain_timeofday_set_delta = lan966x_ts_domain_timeofday_set_delta;
        state->domain_timeofday_next_pps_get = lan966x_ts_domain_timeofday_next_pps_get;
        state->domain_timeofday_offset_set = lan966x_ts_domain_timeofday_offset_set;
        state->domain_adjtimer_set = lan966x_ts_domain_adjtimer_set;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_ts_init(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
