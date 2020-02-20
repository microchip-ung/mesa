// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_TIMESTAMP)
static u64 nominal_tod_increment;

/* Actions on PTP pins */
#define PTP_PIN_ACTION_IDLE  0
#define PTP_PIN_ACTION_LOAD  1
#define PTP_PIN_ACTION_SAVE  2
#define PTP_PIN_ACTION_CLOCK 3
#define PTP_PIN_ACTION_DELTA 4
#define PTP_PIN_ACTION_NOSYNC 0
#define PTP_PIN_ACTION_SYNC 3

#define LAN966X_PTP_PIN_ACTION(pin, act, sync, dom)  \
REG_WRM(PTP_PIN_CFG(pin),                       \
         PTP_PIN_CFG_PIN_ACTION(act) | PTP_PIN_CFG_PIN_SYNC(sync) | PTP_PIN_CFG_PIN_DOM(dom),   \
         PTP_PIN_CFG_PIN_ACTION_M | PTP_PIN_CFG_PIN_SYNC_M | PTP_PIN_CFG_PIN_DOM_M);

static vtss_rc fa_ts_io_pin_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    u32 value;
    REG_RD(PTP_TOD_SEC_MSB(io), &value);
    ts->sec_msb = PTP_TOD_SEC_MSB_TOD_SEC_MSB_X(value);
    REG_RD(PTP_TOD_SEC_LSB(io), &ts->seconds);
    REG_RD(PTP_TOD_NSEC(io), &value);
    ts->nanoseconds = PTP_TOD_NSEC_TOD_NSEC_X(value);
    if (ts->nanoseconds >= 0x3ffffff0 && ts->nanoseconds <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds = 999999984 + (ts->nanoseconds & 0xf);
    }
    REG_RD(PTP_TOD_NSEC_FRAC(io), &value);
    ts->nanosecondsfrac = PTP_TOD_NSEC_FRAC_TOD_NSEC_FRAC_X(value) << 8;    /* In register it is 8 bit nano second fragments. Must return in 16 bit nano second fragments */
    *tc = ((u64)ts->nanoseconds << 16) + (u64)ts->nanosecondsfrac;  /* Must return tc in 16 bit nano second fragments */
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_read(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    LAN966X_PTP_PIN_ACTION(TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, domain);
    return fa_ts_io_pin_timeofday_get(vtss_state, TOD_ACC_PIN, ts, tc);
}

static vtss_rc lan966x_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    VTSS_RC(lan966x_ts_timeofday_read(vtss_state, domain, ts, tc));
    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_get(vtss_state_t     *vtss_state,
                                        vtss_timestamp_t *ts,
                                        u64              *tc)
{
    return lan966x_ts_domain_timeofday_get(vtss_state, 0, ts, tc);
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

static vtss_rc lan966x_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    /* must be in IDLE mode before the time can be loaded */
    LAN966X_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(PTP_TOD_SEC_MSB(TOD_ACC_PIN),
           PTP_TOD_SEC_MSB_TOD_SEC_MSB(ts->sec_msb));
    REG_WR(PTP_TOD_SEC_LSB(TOD_ACC_PIN), ts->seconds);
    REG_WR(PTP_TOD_NSEC(TOD_ACC_PIN),
           PTP_TOD_NSEC_TOD_NSEC(ts->nanoseconds));
    REG_WR(PTP_TOD_NSEC_FRAC(TOD_ACC_PIN),
           PTP_TOD_NSEC_FRAC_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    LAN966X_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, domain);

    VTSS_D("domain %u, sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", domain, ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    return lan966x_ts_domain_timeofday_set(vtss_state, 0, ts);
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

static vtss_rc lan966x_ts_external_clock_mode_set(vtss_state_t *vtss_state)
{
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
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

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_ts_init(vtss_state_t *vtss_state)
{
    u32 domain, clk_in_100ps;

    /* Disable PTP (all 3 domains)*/
    REG_WR(PTP_DOM_CFG, PTP_DOM_CFG_ENA(0));

    /* Configure the nominal TOD increment per clock cycle */
    /* Read the nominal system clock period length in 100 ps */
    clk_in_100ps = vtss_lan966x_clk_period_ps(vtss_state) / 100;

    /* The TOD increment is a 64 bit value with 59 bits as the nano second fragment. This give a nano second resolution of 0x08000000 00000000 */
    nominal_tod_increment = ((clk_in_100ps/10) * 0x0800000000000000) + (((clk_in_100ps%10) * 0x0800000000000000)/10);

    /* Configure the calculated increment */
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(7), PTP_DOM_CFG_CLKCFG_DIS_M);
    for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
        REG_WR(PTP_CLK_PER_CFG(domain, 0), (u32)(nominal_tod_increment & 0xFFFFFFFF));
        REG_WR(PTP_CLK_PER_CFG(domain, 1), (u32)(nominal_tod_increment >> 32));
    }
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(0), PTP_DOM_CFG_CLKCFG_DIS_M);

    /* Enable PTP (all 3 domains)*/
    REG_WR(PTP_DOM_CFG, PTP_DOM_CFG_ENA(7));

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = lan966x_ts_timeofday_get;
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
