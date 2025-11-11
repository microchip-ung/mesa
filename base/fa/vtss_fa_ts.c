// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_fa_cil.h"
#if defined(VTSS_ARCH_FA)

#if defined(VTSS_FEATURE_TIMESTAMP)
/* - CIL functions ------------------------------------------------- */

/* GPIO configuration */
#define GPIO_FUNC_INFO_SIZE 8
static vtss_gpio_func_info_t ptp_gpio[GPIO_FUNC_INFO_SIZE] = {};

static u64 nominal_tod_increment = 0;

#define HW_NS_PR_SEC    1000000000U
#define HW_PS_PR_SEC    1000000000000ULL
#define HW_PS_PR_NS     1000U
#define ADJ_UNITS_PR_NS 10U
#define PPS_WIDTH       1000000U /* Width of 1PPS pulse in ns */

/* Actions on PTP pins */
#define PTP_PIN_ACTION_IDLE   0U
#define PTP_PIN_ACTION_LOAD   1U
#define PTP_PIN_ACTION_SAVE   2U
#define PTP_PIN_ACTION_CLOCK  3U
#define PTP_PIN_ACTION_DELTA  4U
#define PTP_PIN_ACTION_NOSYNC 0U
#define PTP_PIN_ACTION_SYNC   3U

/* ACTION has to be done in two steps. First write SYNC and DOMAIN and then the
 * ACTION. */
/* This is a requirement on Laguna */
#define FA_PTP_PIN_ACTION(pin, act, sync, dom)                                                     \
    REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(pin),                                                      \
            VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SYNC(sync) |                                     \
                VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_DOM(dom),                                    \
            VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SYNC |                                           \
                VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_DOM);                                        \
    REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(pin), VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_ACTION(act),   \
            VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_ACTION);

static vtss_gpio_mode_t gpio_mode_calc(vtss_gpio_func_alt_t func_alt)
{
    vtss_gpio_mode_t ret;

    switch (func_alt) {
    case VTSS_GPIO_FUNC_ALT_0: ret = VTSS_GPIO_ALT_0; break;
    case VTSS_GPIO_FUNC_ALT_1: ret = VTSS_GPIO_ALT_1; break;
    case VTSS_GPIO_FUNC_ALT_2: ret = VTSS_GPIO_ALT_2; break;
    case VTSS_GPIO_FUNC_ALT_3: ret = VTSS_GPIO_ALT_3; break;
    default:                   ret = VTSS_GPIO_ALT_0; break;
    }
    return ret;
}

static vtss_rc fa_ts_io_pin_timeofday_get(vtss_state_t     *vtss_state,
                                          u32               io,
                                          vtss_timestamp_t *ts,
                                          u64              *tc)
{
    u32 value;

    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(io), &value);
    ts->sec_msb = (u16)VTSS_X_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(value);
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(io), &ts->seconds);
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(io), &value);
    ts->nanoseconds = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(value);
    if (ts->nanoseconds >= 0x3ffffff0U &&
        ts->nanoseconds <= 0x3fffffffU) { /* -1..-16 = 10^9-1..16 */
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds = 999999984U + (ts->nanoseconds & 0xfU);
    }
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(io), &value);
    /* In register it is 8 bit nano second fragments.
       Must return in 16 bit nano second fragments */
    ts->nanosecondsfrac = (u16)(VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(value) << 8U);
    /* Must return tc in 16 bit nano second fragments */
    *tc = ((u64)ts->nanoseconds << 16U) + (u64)ts->nanosecondsfrac;
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_read(vtss_state_t     *vtss_state,
                                    u32               domain,
                                    vtss_timestamp_t *ts,
                                    u64              *tc)
{
    FA_PTP_PIN_ACTION(RT_TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, domain);
    return fa_ts_io_pin_timeofday_get(vtss_state, RT_TOD_ACC_PIN, ts, tc);
}

static vtss_rc fa_ts_supported(vtss_state_t *vtss_state)
{
    return (vtss_state->vtss_features[FEATURE_TIMESTAMP] ? VTSS_RC_OK : VTSS_RC_ERROR);
}

vtss_rc vtss_cil_ts_domain_tod_get(struct vtss_state_s *vtss_state,
                                   u32                  domain,
                                   vtss_timestamp_t    *ts,
                                   u64                 *tc)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, tc));
    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb,
           ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_timeofday_get(struct vtss_state_s *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_tod_get(vtss_state, 0U, ts, tc);
}

static vtss_rc fa_ts_domain_timeofday_prev_pps_get(vtss_state_t     *vtss_state,
                                                   u32               domain,
                                                   vtss_timestamp_t *ts)
{
    u64 tc;

    VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, &tc));

    ts->nanoseconds = 0U;
    ts->nanosecondsfrac = 0;

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb,
           ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_domain_timeofday_next_pps_get(struct vtss_state_s *vtss_state,
                                                  u32                  domain,
                                                  vtss_timestamp_t    *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_RC(fa_ts_domain_timeofday_prev_pps_get(vtss_state, domain, ts));
    VTSS_RC(vtss_timestampAddSec(ts));

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb,
           ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_tod_next_pps_get(struct vtss_state_s *vtss_state, vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_timeofday_next_pps_get(vtss_state, 0U, ts);
}

vtss_rc vtss_cil_ts_tod_prev_pps_get(struct vtss_state_s *vtss_state, vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return fa_ts_domain_timeofday_prev_pps_get(vtss_state, 0U, ts);
}

vtss_rc vtss_cil_ts_multi_domain_timeofday_get(struct vtss_state_s    *vtss_state,
                                               const uint32_t          domain_cnt,
                                               vtss_timestamp_t *const ts)
{
    uint32_t          value, domain;
    vtss_timestamp_t *t_stamp;

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE(7),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE);

    for (domain = 0U; domain < domain_cnt; domain++) {
        t_stamp = &ts[domain];
        REG_RD(VTSS_DEVCPU_PTP_PTP_CUR_SEC_MSB(domain), &value);
        t_stamp->sec_msb = (u16)VTSS_X_DEVCPU_PTP_PTP_CUR_SEC_MSB_PTP_CUR_SEC_MSB(value);
        REG_RD(VTSS_DEVCPU_PTP_PTP_CUR_SEC_LSB(domain), &t_stamp->seconds);
        REG_RD(VTSS_DEVCPU_PTP_PTP_CUR_NSEC(domain), &value);
        t_stamp->nanoseconds = VTSS_X_DEVCPU_PTP_PTP_CUR_NSEC_PTP_CUR_NSEC(value);
        if (t_stamp->nanoseconds >= 0x3ffffff0U &&
            t_stamp->nanoseconds <= 0x3fffffffU) { /* -1..-16 = 10^9-1..16 */
            VTSS_RC(vtss_timestampSubSec(t_stamp));
            t_stamp->nanoseconds = 999999984U + (t_stamp->nanoseconds & 0xfU);
        }
        REG_RD(VTSS_DEVCPU_PTP_PTP_CUR_NSEC_FRAC(domain), &value);
        t_stamp->nanosecondsfrac =
            (u16)(VTSS_X_DEVCPU_PTP_PTP_CUR_NSEC_FRAC_PTP_CUR_NSEC_FRAC(value) << 8U);
        VTSS_I("domain %u ts sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u",
               domain, t_stamp->sec_msb, t_stamp->seconds, t_stamp->nanoseconds,
               t_stamp->nanosecondsfrac);
    }

    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE(0),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_TOD_FREEZE);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_domain_timeofday_set(struct vtss_state_s    *vtss_state,
                                         u32                     domain,
                                         const vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    /* must be in IDLE mode before the time can be loaded */
    FA_PTP_PIN_ACTION(RT_TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(RT_TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(RT_TOD_ACC_PIN), ts->seconds);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(RT_TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(RT_TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    FA_PTP_PIN_ACTION(RT_TOD_ACC_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, domain);

    VTSS_D("domain %u, sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", domain,
           ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_timeofday_set(struct vtss_state_s *vtss_state, const vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_timeofday_set(vtss_state, 0U, ts);
}

vtss_rc vtss_cil_ts_domain_timeofday_offset_set(struct vtss_state_s *vtss_state,
                                                u32                  domain,
                                                i32                  offset)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("offset before: %d", offset);
    /* must be in IDLE mode before the time can be loaded */
    FA_PTP_PIN_ACTION(RT_TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(RT_TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(-offset));
    FA_PTP_PIN_ACTION(RT_TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, domain);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_timeofday_offset_set(struct vtss_state_s *vtss_state, i32 offset)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_timeofday_offset_set(vtss_state, 0U, offset);
}

vtss_rc vtss_cil_ts_domain_tod_set_delta(struct vtss_state_s    *vtss_state,
                                         u32                     domain,
                                         const vtss_timestamp_t *ts,
                                         BOOL                    negative)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    if ((ts->seconds > 0U) || (ts->sec_msb > 0U) || (ts->nanoseconds > HW_NS_PR_SEC / 2U) ||
        (ts->nanosecondsfrac > 0U)) {
        vtss_timestamp_t ts_prev;
        u64              tc;

        /* Read current time */
        VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, &ts_prev, &tc));

        /* Calculate new time */
        if (negative) {
            VTSS_RC(vtss_timestampSub(&ts_prev, ts));
        } else {
            VTSS_RC(vtss_timestampAdd(&ts_prev, ts));
        }

        return vtss_cil_ts_domain_timeofday_set(vtss_state, domain, &ts_prev);
    } else {
        return vtss_cil_ts_domain_timeofday_offset_set(vtss_state, domain,
                                                       (negative) ? (i32)ts->nanoseconds
                                                                  : -(i32)ts->nanoseconds);
    }
}

vtss_rc vtss_cil_ts_timeofday_set_delta(struct vtss_state_s    *vtss_state,
                                        const vtss_timestamp_t *ts,
                                        BOOL                    negative)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_tod_set_delta(vtss_state, 0U, ts, negative);
}

vtss_rc vtss_cil_ts_domain_adjtimer_set(struct vtss_state_s *vtss_state, u32 domain)
{
    i32 adj, i;
    u32 adj_abs, dom_mask = (u32)0x01U << domain;
    u64 tod_inc, one_pico, tod_delta, tod_trunk;

    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("enter domain %u  nominal_tod_increment %" PRIu64 "", domain, nominal_tod_increment);

    if (domain >= VTSS_TS_DOMAIN_ARRAY_SIZE) {
        VTSS_D("domain %d is larger than VTSS_TS_DOMAIN_ARRAY_SIZE %u", domain,
               VTSS_TS_DOMAIN_ARRAY_SIZE);
        return VTSS_RC_ERROR;
    }
    adj = vtss_state->ts.conf.adj[domain];
    if (adj == INT32_MIN) {
        i = INT32_MAX;
    } else if (adj < 0) {
        i = -adj;
    } else {
        i = adj;
    }
    adj_abs = (u32)i;

    tod_inc = nominal_tod_increment; /* Fetch the nominal TOD increment as a
                                        baseline */

    /* Calculate the TOD increment delta value, that is a fraction of the
     * nominal TOD increment. */
    /* The fraction is given by 'adj' in 1E-10. The calculation is: tod_delta =
     * tod_inc * (adj / 1E10) */
    tod_trunk = tod_inc % 10000000000ULL; /* We will divide before multiplying to avoid overrun.
                                            The TOD truncated part is saved in 'tod_trunk' */
    tod_delta = (tod_inc / 10000000000ULL) * adj_abs; /* Divide and then multiply */
    tod_delta +=
        (tod_trunk * adj_abs) / 10000000000ULL; /* Now the truncated part is multiplied and then
                                                  divided. Result is added to 'tod_delta' */

    /* Check if the delta value is too large */
    one_pico = 0x0800000000000000U / 1000U; /* One pico is one nano divided by 1000.
                                               One nano in 5.59 notation is 0x0800000000000000 */
    VTSS_D("adj %d  tod_delta %" PRIu64 "  1.9pico %" PRIu64 "", adj, tod_delta,
           ((one_pico * 19U) / 10U));
    if (tod_delta > (one_pico * 19U) / 10U) { /* In case the numeric change is more than 1.9 pico
                                               seconds, PTP must be restarted so this is rejected */
        VTSS_I("Rejected restarting of PTP due to more than 1.9 pico second change in TOD increment");
        return VTSS_RC_ERROR;
    }

    /* Adjust the TOD increment with the delta value */
    if (adj > 0) {
        tod_inc += tod_delta;
    } else {
        tod_inc -= tod_delta;
    }

    /* Configure the new adjusted TOD increment value */
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(dom_mask),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);
    REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 0), (u32)(tod_inc & 0xFFFFFFFFU));
    REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 1), (u32)(tod_inc >> 32));
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(0),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_adjtimer_set(struct vtss_state_s *vtss_state)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    return vtss_cil_ts_domain_adjtimer_set(vtss_state, 0U);
}

/* Set the clock mode for the external clock */
vtss_rc vtss_cil_ts_external_clock_mode_set(struct vtss_state_s *vtss_state)
{
    vtss_ts_ext_clock_mode_t *ext_clock_mode = &vtss_state->ts.conf.ext_clock_mode;

    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("one_pps_mode: %u, enable: %u, freq: %u clk_domain:%u", ext_clock_mode->one_pps_mode,
           ext_clock_mode->enable, ext_clock_mode->freq, ext_clock_mode->domain);
    FA_PTP_PIN_ACTION(RT_EXT_CLK_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC,
                      ext_clock_mode->domain);
    if (ext_clock_mode->enable) {
        u32 dividers = HW_NS_PR_SEC / ext_clock_mode->freq;
        u32 high_div = dividers / 2U;
        u32 low_div = (dividers + 1U) / 2U;
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(RT_EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(RT_EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));

        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_EXT_CLK_PIN].gpio_no,
                                gpio_mode_calc(ptp_gpio[RT_EXT_CLK_PIN].alt));
        FA_PTP_PIN_ACTION(RT_EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC,
                          ext_clock_mode->domain);

    } else if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_EXT_CLK_PIN].gpio_no,
                                gpio_mode_calc(ptp_gpio[RT_EXT_CLK_PIN].alt));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(RT_EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(RT_EXT_CLK_PIN), 0);

        FA_PTP_PIN_ACTION(RT_EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC,
                          ext_clock_mode->domain);
    } else {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_EXT_CLK_PIN].gpio_no, VTSS_GPIO_IN);
    }

    return VTSS_RC_OK;
}

/* Get the saved nanosec counter */
vtss_rc vtss_cil_ts_alt_clock_saved_get(struct vtss_state_s *vtss_state, u64 *saved)
{
    u32 nsec, nsec_frac;

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(RT_ALT_LDST_PIN), &nsec);
    nsec = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(nsec);
    if (nsec >= 0x3ffffff0U) { /* -1..-16 = 10^9-1..16 */
        nsec = 999999984U + (nsec & 0xfU);
    }
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(RT_ALT_LDST_PIN), &nsec_frac);
    nsec_frac = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(nsec_frac);
    *saved = ((u64)nsec << 16U) + ((u64)nsec_frac << 8U);
    return VTSS_RC_OK;
}

/* Set the clock mode for the alternative clock
 * the modes are:
 *    BOOL one_pps_out;        Enable 1pps output
 *    BOOL one_pps_in;         Enable 1pps input
 *    BOOL save;               Save actual time counter at next 1 PPS input
 *    BOOL load;               Load actual time counter at next 1 PPS input
 */
vtss_rc vtss_cil_ts_alt_clock_mode_set(struct vtss_state_s *vtss_state)
{
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    VTSS_RC(fa_ts_supported(vtss_state));
    FA_PTP_PIN_ACTION(RT_ALT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_out) {
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(RT_ALT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(RT_ALT_PPS_PIN), 0);

        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_ALT_PPS_PIN].gpio_no,
                                gpio_mode_calc(ptp_gpio[RT_ALT_PPS_PIN].alt));
        FA_PTP_PIN_ACTION(RT_ALT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_ALT_PPS_PIN].gpio_no, VTSS_GPIO_IN);
    }

    FA_PTP_PIN_ACTION(RT_ALT_LDST_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
            return VTSS_RC_ERROR;
        } else if (alt_clock_mode->save) {
            (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_ALT_LDST_PIN].gpio_no,
                                    gpio_mode_calc(ptp_gpio[RT_ALT_LDST_PIN].alt));
            FA_PTP_PIN_ACTION(RT_ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_ALT_LDST_PIN].gpio_no,
                                    gpio_mode_calc(ptp_gpio[RT_ALT_LDST_PIN].alt));
            FA_PTP_PIN_ACTION(RT_ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        } else {
            /* MISRA - must be here */
        }
    } else {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[RT_ALT_LDST_PIN].gpio_no, VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

/* Set the time to be loaded into the PTP timer at the next 1PPS
 * It is assumed that this function is called at the beginning of a sec */
vtss_rc vtss_cil_ts_tod_next_pps_set(struct vtss_state_s *vtss_state, const vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_supported(vtss_state));
    if (vtss_state->ts.conf.alt_clock_mode.one_pps_in) {
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(RT_ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(RT_ALT_LDST_PIN), ts->seconds - 1U);
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(RT_ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(RT_ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    }

    VTSS_D("time at next pps: sec_msb %u, sec %u, ns %u", ts->sec_msb, ts->seconds,
           ts->nanoseconds);
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_ingress_latency_set(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf;
    u32                  rx_delay;
    u32                  port = VTSS_CHIP_PORT(port_no);
    i64                  latency;
    u64                  one_mia_shift;

    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }

    conf = &vtss_state->ts.port_conf[port_no];

    /* The ingress_latency is in nanoseconds<<16 so second must also be shifted 16  */
    one_mia_shift = VTSS_ONE_MIA << 16;

    /* Calculate the Ingress Latency nanosecond part by doing MOD with second */
    latency = VTSS_MOD64(conf->ingress_latency, (i64)one_mia_shift);

    /* The default_igr_latency is in picoseconds. */
    /* Register is in nanoseconds<<8 */
    /* Signed integer cannot be shifted.
        dividing by 256 is the same as >> 8
        multiplying by 256 is the same as << 8 */
    latency = (latency / 256) + ((conf->default_igr_latency * 256) / 1000);

    /* The register cannot have negative latency */
    if (latency < 0) {
        VTSS_I(" Negative ingress latency too high to be configured for port %d", port_no);
    }

    rx_delay = (u32)latency;

    if (rx_delay > 0xFFFFFFU) { /* Register max value is 0xFFFFFF */
        rx_delay = 0xFFFFFFU;
    }

    VTSS_I("rx_delay %d  ingr_latency %u  default_igr_latency %d", rx_delay,
           VTSS_INTERVAL_NS(conf->ingress_latency), conf->default_igr_latency);

    DEV_WRM(PTP_RXDLY_CFG, port, VTSS_F_DEV1G_PTP_RXDLY_CFG_PTP_RX_IO_DLY(rx_delay),
            VTSS_M_DEV1G_PTP_RXDLY_CFG_PTP_RX_IO_DLY);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_p2p_delay_set(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32                  p2p_delay = VTSS_INTERVAL_NS(conf->p2p_delay);

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_WR(VTSS_REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)),
           p2p_delay + VTSS_INTERVAL_NS(conf->delay_asymmetry));
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_egress_latency_set(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf;
    u32                  tx_delay;
    u32                  port = VTSS_CHIP_PORT(port_no);
    i64                  latency;
    u64                  one_mia_shift;

    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }

    conf = &vtss_state->ts.port_conf[port_no];

    /* The egress_latency is in nanoseconds<<16 so second must also be shifted 16  */
    one_mia_shift = VTSS_ONE_MIA << 16;

    /* Calculate the Egress Latency nanosecond part by doing MOD with second */
    latency = VTSS_MOD64(conf->egress_latency, (i64)one_mia_shift);

    /* The default_egr_latency is in picoseconds. */
    /* Register is in nanoseconds<<8 */
    /* Signed integer cannot be shifted.
        dividing by 256 is the same as >> 8
        multiplying by 256 is the same as << 8 */
    latency = (latency / 256) + ((conf->default_egr_latency * 256) / 1000);

    /* The register cannot have negative latency */
    if (latency < 0) {
        VTSS_I(" Negative egress latency too high to be configured for port %d", port_no);
    }

    tx_delay = (u32)latency;

    if (tx_delay > 0xFFFFFFU) { /* Register max value is 0xFFFFFF */
        tx_delay = 0xFFFFFFU;
    }

    VTSS_I("tx_delay %u  egress_latency %u  default_egr_latency %d", tx_delay,
           VTSS_INTERVAL_NS(conf->egress_latency), conf->default_egr_latency);

    DEV_WRM(PTP_TXDLY_CFG, port, VTSS_F_DEV1G_PTP_TXDLY_CFG_PTP_TX_IO_DLY(tx_delay),
            VTSS_M_DEV1G_PTP_TXDLY_CFG_PTP_TX_IO_DLY);

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_delay_asymmetry_set(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32                  delay = VTSS_INTERVAL_NS(conf->delay_asymmetry);

    VTSS_RC(fa_ts_supported(vtss_state));
    /* Used for Ingress asymmetry compensation (Pdelay_Resp) */
    REG_WR(VTSS_REW_PTP_IDLY1_CFG(VTSS_CHIP_PORT(port_no)), delay);
    /* Used for Egress asymmetry compensation (on Delay_Req and Pdelay_Req) */
    REG_WR(VTSS_REW_PTP_EDLY_CFG(VTSS_CHIP_PORT(port_no)), -delay);
    /* Used for Ingress asymmetry compensation (on Sync, therefore include
     * p2p_delay ) */
    REG_WR(VTSS_REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)),
           delay + VTSS_INTERVAL_NS(conf->p2p_delay));
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_operation_mode_set(struct vtss_state_s *vtss_state,
                                       vtss_port_no_t       port_no,
                                       BOOL                 mode_domain_config)
{
    vtss_ts_operation_mode_t *o_mode = &vtss_state->ts.port_conf[port_no].mode;
    vtss_ts_mode_t            mode = o_mode->mode;
    u32                       domain = o_mode->domain;
    vtss_ts_internal_fmt_t    fmt = vtss_state->ts.int_mode.int_fmt;
    u32                       mode_val = 0U;
    u32                       port = VTSS_CHIP_PORT(port_no);
    BOOL                      ret_err = FALSE;

    VTSS_RC(fa_ts_supported(vtss_state));
#if defined(VTSS_FEATURE_TIMESTAMP_PCH)
    BOOL high_dev = fa_is_high_speed_device(vtss_state, port_no);
    u32  tx_pch_mode = 0, rx_pch_mode = 0, val = 0, msk = 0;
    switch (o_mode->rx_pch_mode) {
    case VTSS_TS_PCH_RX_MODE_NONE:  rx_pch_mode = 0; break;
    case VTSS_TS_PCH_RX_MODE_32_0:  rx_pch_mode = 1; break;
    case VTSS_TS_PCH_RX_MODE_28_4:  rx_pch_mode = 2; break;
    case VTSS_TS_PCH_RX_MODE_24_8:  rx_pch_mode = 3; break;
    case VTSS_TS_PCH_RX_MODE_16_16: rx_pch_mode = 4; break;
    }

    switch (o_mode->tx_pch_mode) {
    case VTSS_TS_PCH_TX_MODE_NONE:                    tx_pch_mode = 0; break;
    case VTSS_TS_PCH_TX_MODE_ENCRYPT_NONE:            tx_pch_mode = 1; break;
    case VTSS_TS_PCH_TX_MODE_ENCRYPT_BIT:             tx_pch_mode = 2; break;
    case VTSS_TS_PCH_TX_MODE_ENCRYPT_BIT_INVERT_SMAC: tx_pch_mode = 3; break;
    }

    if (high_dev) {
#if defined(VTSS_ARCH_LAN969X)
        val = VTSS_F_DEV10G_PTP_CFG_PCH_ERR_MODE(3);
        msk = VTSS_M_DEV10G_PTP_CFG_PCH_ERR_MODE;
#endif
        REG_WRM(VTSS_DEV10G_PTP_CFG(VTSS_TO_HIGH_DEV(port)),
                VTSS_F_DEV10G_PTP_CFG_PCH_SUB_PORT_ID(o_mode->pch_port_id) |
                    VTSS_F_DEV10G_PTP_CFG_PTP_PCH_TX_ENA(tx_pch_mode) |
                    VTSS_F_DEV10G_PTP_CFG_PTP_PCH_RX_MODE(rx_pch_mode) | val,
                VTSS_M_DEV10G_PTP_CFG_PCH_SUB_PORT_ID | VTSS_M_DEV10G_PTP_CFG_PTP_PCH_TX_ENA |
                    VTSS_M_DEV10G_PTP_CFG_PTP_PCH_RX_MODE | msk);
    } else {
        vtss_port_conf_t *conf = &vtss_state->port.conf[port_no];
        if ((conf->if_type == VTSS_PORT_INTERFACE_RGMII) ||
            (conf->if_type == VTSS_PORT_INTERFACE_RGMII_RXID) ||
            (conf->if_type == VTSS_PORT_INTERFACE_RGMII_TXID) ||
            (conf->if_type == VTSS_PORT_INTERFACE_RGMII_ID)) {
#if defined(VTSS_ARCH_LAN969X)
            REG_WRM(VTSS_DEVRGMII_PTP_CFG(VTSS_TO_DEV2G5(port)),
                    VTSS_F_DEVRGMII_PTP_CFG_PCH_SUB_PORT_ID(o_mode->pch_port_id) |
                        VTSS_F_DEVRGMII_PTP_CFG_PTP_PCH_TX_ENA(tx_pch_mode) |
                        VTSS_F_DEVRGMII_PTP_CFG_PTP_PCH_RX_MODE(rx_pch_mode) |
                        VTSS_F_DEVRGMII_PTP_CFG_PCH_ERR_MODE(3),
                    VTSS_M_DEVRGMII_PTP_CFG_PCH_SUB_PORT_ID |
                        VTSS_M_DEVRGMII_PTP_CFG_PTP_PCH_TX_ENA |
                        VTSS_M_DEVRGMII_PTP_CFG_PTP_PCH_RX_MODE |
                        VTSS_M_DEVRGMII_PTP_CFG_PCH_ERR_MODE);
#endif
        } else {
#if defined(VTSS_ARCH_LAN969X)
            val = VTSS_F_DEV1G_PTP_CFG_PCH_ERR_MODE(3);
            msk = VTSS_M_DEV1G_PTP_CFG_PCH_ERR_MODE;
#endif
            REG_WRM(VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV2G5(port)),
                    VTSS_F_DEV1G_PTP_CFG_PCH_SUB_PORT_ID(o_mode->pch_port_id) |
                        VTSS_F_DEV1G_PTP_CFG_PTP_PCH_TX_ENA(tx_pch_mode) |
                        VTSS_F_DEV1G_PTP_CFG_PTP_PCH_RX_MODE(rx_pch_mode) | val,
                    VTSS_M_DEV1G_PTP_CFG_PCH_SUB_PORT_ID | VTSS_M_DEV1G_PTP_CFG_PTP_PCH_TX_ENA |
                        VTSS_M_DEV1G_PTP_CFG_PTP_PCH_RX_MODE | msk);
        }
    }
#endif

#if defined(VTSS_FEATURE_REDBOX)
    VTSS_RC(vtss_fa_rb_port_update(vtss_state, port_no));
    REG_WRM_CTL(VTSS_REW_PTP_MISC_CFG(port), o_mode->rb_srcid,
                VTSS_M_REW_PTP_MISC_CFG_PTP_RB_ID_SEL);
#endif

    if (!mode_domain_config) {
        return VTSS_RC_OK;
    }

    if (mode == TS_MODE_INTERNAL) {
        switch (fmt) {
        case TS_INTERNAL_FMT_RESERVED_LEN_30BIT: mode_val = 1U; break;
        case TS_INTERNAL_FMT_RESERVED_LEN_32BIT:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            ret_err = TRUE;
            break;
        case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            ret_err = TRUE;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF: mode_val = 2U; break;
        default:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            ret_err = TRUE;
            break;
        }
    }
    if (ret_err == TRUE) {
        return VTSS_RC_ERROR;
    }

    VTSS_I("port %d, mode %d, domain %u,mode_val %u", port_no, mode, domain, mode_val);
    REG_WRM(VTSS_REW_PTP_MODE_CFG(port, 0),
            VTSS_F_REW_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
                VTSS_F_REW_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PTP_MODE_CFG_PTP_MODE_VAL | VTSS_M_REW_PTP_MODE_CFG_PTP_DOM_VAL);
    REG_WRM(VTSS_REW_PTP_MODE_CFG(port, 1),
            VTSS_F_REW_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
                VTSS_F_REW_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PTP_MODE_CFG_PTP_MODE_VAL | VTSS_M_REW_PTP_MODE_CFG_PTP_DOM_VAL);
    // Set up pr port Delay_Req/Resp Processing
    REG_WRM(VTSS_ANA_ACL_PTP_CFG(port), VTSS_F_ANA_ACL_PTP_CFG_PTP_PORT_NUM(port_no + 1U),
            VTSS_M_ANA_ACL_PTP_CFG_PTP_PORT_NUM);
    // disable central counters in DEVCPU
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(0),
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA((u32)1U << domain));
    // Set domain in DEV_xxx
    DEV_WRM(PTP_CFG, port, VTSS_F_DEV1G_PTP_CFG_PTP_DOM(domain), VTSS_M_DEV1G_PTP_CFG_PTP_DOM);
    // enable central counters in DEVCPU
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA((u32)1U << domain),
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA((u32)1U << domain));

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_internal_mode_set(struct vtss_state_s *vtss_state)
{
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    vtss_rc                rc = VTSS_RC_OK;

    VTSS_RC(fa_ts_supported(vtss_state));

    switch (fmt) {
    case TS_INTERNAL_FMT_NONE:
    case TS_INTERNAL_FMT_RESERVED_LEN_30BIT:
    case TS_INTERNAL_FMT_RESERVED_LEN_32BIT:
    case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
    case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF:  break;
    default:
        VTSS_E("unsupported internal timestamp format: %u", fmt);
        rc = VTSS_RC_ERROR;
        break;
    }
    return rc;
}

static u32 api_port(vtss_state_t *vtss_state, u32 chip_port)
{
    u32 port_no;
    int found = 0;
    /* Map from chip port to API port */
    if (chip_port == RT_CHIP_PORT_CPU) {
        port_no = RT_CHIP_PORT_CPU;
    } else {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_CHIP_PORT(port_no) == chip_port) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            VTSS_E("unknown chip port: %u, port_no: %d", chip_port, port_no);
        }
    }
    return port_no;
}

#if defined(VTSS_ARCH_SPARX5)
vtss_rc vtss_cil_ts_timestamp_get(struct vtss_state_s *vtss_state)
{
    u32  value;
    u32  delay;
    u32  tx_port;
    u32  mess_id;
    BOOL overflow = FALSE;
    u32  sub_ns;

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
    while (VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(value)) {
        /* Read TX timestamp */
        if (!VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("TX timestamp expected but RX timestamp found");
            REG_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL,
                   VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP, &delay);
        tx_port = api_port(vtss_state, VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_PORT(value));
        REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP_SUBNS, &sub_ns);
        /* Read RX timestamp */
        REG_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
        if (!VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(value) ||
            VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("RX timestamp not found");
            REG_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL,
                   VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP, &mess_id);

        if (mess_id >= VTSS_TS_ID_SIZE) {
            VTSS_D("skip mess_id %u", mess_id);
        } else if (tx_port < VTSS_PORT_ARRAY_SIZE) {
            vtss_state->ts.status[mess_id].tx_tc[tx_port] = ((u64)delay << 16) | (sub_ns & 0xff)
                                                                                     << 8;
            vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
            vtss_state->ts.status[mess_id].valid_mask |= 1ULL << tx_port;
        } else {
            VTSS_E("invalid port (%u)", tx_port);
        }

        VTSS_I("value %x, delay %u, tx_port %u, mess_id %u", value, delay, tx_port, mess_id);
        REG_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
    }
    if (overflow) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}
#else
vtss_rc vtss_cil_ts_timestamp_get(struct vtss_state_s *vtss_state)
{
    u32  value;
    u32  delay;
    u32  tx_port;
    u32  mess_id;
    BOOL overflow = FALSE;
    u32  sub_ns;

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, &value);
    while (VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_VLD(value) != 0U) {
        /* Read TX timestamp */
        if (VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_STAMP_TX(value) == 0U) {
            VTSS_E("TX timestamp expected but RX timestamp found");
            REG_WR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, VTSS_F_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow =
            overflow || ((VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_OVFL(value) != 0U) ? TRUE : FALSE);
        REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_STAMP_NSEC, &delay);
        tx_port = api_port(vtss_state, VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_STAMP_PORT(value));
        REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_STAMP_SUBNS, &sub_ns);
        /* Read RX timestamp */
        REG_WR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, VTSS_F_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, &value);
        if ((VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_VLD(value) == 0U) ||
            (VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_STAMP_TX(value) != 0U)) {
            VTSS_E("RX timestamp not found");
            REG_WR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL,
                   VTSS_F_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(TRUE));
            REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow =
            overflow || (VTSS_X_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_OVFL(value) != 0U) ? TRUE : FALSE;
        REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_STAMP_NSEC, &mess_id);

        if (mess_id >= VTSS_TS_ID_SIZE) {
            VTSS_D("skip mess_id %u", mess_id);
        } else if (tx_port < VTSS_PORT_ARRAY_SIZE) {
            vtss_state->ts.status[mess_id].tx_tc[tx_port] = ((u64)delay << 16U) | (sub_ns & 0xffU)
                                                                                      << 8U;
            vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
            vtss_state->ts.status[mess_id].valid_mask |= 1ULL << tx_port;
        } else {
            VTSS_E("invalid port (%u)", tx_port);
        }

        VTSS_I("value %x, delay %u, tx_port %u, mess_id %u", value, delay, tx_port, mess_id);
        REG_WR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, VTSS_F_DEVCPU_PTP_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL, &value);
    }
    if (overflow) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}
#endif

typedef struct {
    u32 rx;
    u32 tx;
} io_delay_t;
static io_delay_t seriel_1G_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_10G_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_2dot5G_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_25G_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_5G_delay[VTSS_PORT_COUNT];
static io_delay_t qsgmii_1G_delay[VTSS_PORT_COUNT];
static io_delay_t rgmii_1G_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_10G_kr_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_25G_kr_delay[VTSS_PORT_COUNT];
static io_delay_t seriel_25G_rs_delay[VTSS_PORT_COUNT];

/*
 * Signal port status (configuration actually) change (used to detect and
 * compensate for the internal ingress and egress latencies)
 */
vtss_rc vtss_cil_ts_status_change(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_interface_t interface;
    vtss_port_speed_t     speed;
    u32                   port, value;
    vtss_rc               rc = VTSS_RC_OK, rc2;
    u32                   rx_delay = 0U, tx_delay = 0U, delay_var = 0U;
    u32                   sd_indx, sd_type, sd_lane_tgt, sd_rx_delay_var = 0U, sd_tx_delay_var = 0U;
    i32                   delay_signed;
    io_delay_t           *dv_factor = NULL;
    io_delay_t            delay_var_factor[5] = {
        {64000U, 128000U},
        {25600U, 51200U },
        {12400U, 15500U },
        {18600U, 24800U },
        {0U,     0U     }
    }; /* SD_LANE_TARGET -   Speed 1G - 2.5G - 5G - 10G - 25G */
#if defined(VTSS_FEATURE_SD_25G)
    io_delay_t delay_var_factor_25G[5] = {
        {128000U, 128000U},
        {51200U,  51200U },
        {49600U,  37200U },
        {24800U,  18600U },
        {6200U,   6200U  }
    }; /* SD25G_CFG_TARGET - Speed 1G - 2.5G - 5G - 10G - 25G */
#endif

    VTSS_RC(fa_ts_supported(vtss_state));
    VTSS_D("Enter  port_no %d", port_no);
    (void)delay_var_factor;
    (void)value;

    interface = vtss_state->port.current_if_type[port_no];
    if (!vtss_state->port.conf_set_called[port_no] ||
        interface == VTSS_PORT_INTERFACE_NO_CONNECTION) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }

    speed = vtss_state->port.current_speed[port_no];
    port = VTSS_CHIP_PORT(port_no);

    /* Calculate the lane information based on the port */
    (void)vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type);
    dv_factor = delay_var_factor;
#if defined(VTSS_FEATURE_SD_25G)
    if (sd_type == FA_SERDES_TYPE_25G) {
        dv_factor = delay_var_factor_25G;
    }
#endif

    if (sd_type == FA_SERDES_TYPE_10G) {
        sd_indx = sd_indx + RT_SERDES_10G_START;
    } else if (sd_type == FA_SERDES_TYPE_25G) {
        sd_indx = sd_indx + RT_SERDES_25G_START;
    } else if (sd_type == FA_SERDES_TYPE_6G) {
        sd_indx = sd_indx + 0U;
    } else if (sd_type == FA_SERDES_TYPE_UNKNOWN) {
        /* Interface without SERDES */
        sd_indx = 0U;
    } else {
        VTSS_E("Unknown SERDES type %u", sd_type);
        return VTSS_RC_ERROR;
    }
    if (sd_type != FA_SERDES_TYPE_UNKNOWN) {
        /* Interface has a SERDES */
        sd_lane_tgt = VTSS_TO_SD_LANE(sd_indx);

        VTSS_D("chip_port %u  interface %u  speed %u  sd_type %u  sd_lane_tgt %u  sd_indx %u", port,
               interface, speed, sd_type, sd_lane_tgt, sd_indx);

        /* Read the GUC variable delay and correct the factor in case of
         * SD_LANE_TARGET and 5G and lane > 12 */
        if (sd_type == FA_SERDES_TYPE_25G) {
#if defined(VTSS_FEATURE_SD_25G)
            REG_RD(VTSS_SD25G_CFG_TARGET_SD_DELAY_VAR(sd_lane_tgt), &value);
            sd_rx_delay_var = VTSS_X_SD25G_CFG_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(value);
            sd_tx_delay_var = VTSS_X_SD25G_CFG_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(value);
#endif
        } else {
#if !defined(VTSS_ARCH_LAIKA)
            REG_RD(VTSS_SD_LANE_TARGET_SD_DELAY_VAR(sd_lane_tgt), &value);
            sd_rx_delay_var = VTSS_X_SD_LANE_TARGET_SD_DELAY_VAR_RX_DELAY_VAR(value);
            sd_tx_delay_var = VTSS_X_SD_LANE_TARGET_SD_DELAY_VAR_TX_DELAY_VAR(value);
            if (speed == VTSS_SPEED_5G) {
#if !defined(VTSS_ARCH_LAN969X)
                if (sd_indx > 12U)
#endif
                {
                    /* 5 Gbps and (on FA) lane > 12. The delay factor must be corrected */
                    delay_var_factor[2].rx = 37200U;
                    delay_var_factor[2].tx = 49600U;
                }
            }
#endif
        }
        VTSS_D("sd_rx_delay_var %u  sd_tx_delay_var %u", sd_rx_delay_var, sd_tx_delay_var);
    }

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        /* Single-Lane SerDes at 1 or 2.5 Gbps */
        if ((speed == VTSS_SPEED_10M) || (speed == VTSS_SPEED_100M)) { /* 10 Mbps - 100 Mbps */
            /* According to Morten this is not relevant */
        }
        if (speed == VTSS_SPEED_1G) { /* 1 Gbps */
            rx_delay = seriel_1G_delay[port].rx;
            tx_delay = seriel_1G_delay[port].tx;
            REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(VTSS_TO_DEV2G5(port)), &value);
            rx_delay +=
                800U * VTSS_X_DEV1G_PCS1G_LINK_STATUS_DELAY_VAR(value); /* Add the variable delay in
                                                                          the device */
            if (sd_type == FA_SERDES_TYPE_25G) {
                /* Calculate the variable RX delay in the SERDES. */
                /* On 25G SERDES 1G speed sd_rx_delay_var is signed */
                delay_signed = ((i16)sd_rx_delay_var * (i32)dv_factor[0].rx) / (i32)65536;
                /* Add it to the rx_delay */
                delay_signed = (i32)rx_delay + delay_signed;
                if (delay_signed < 0) {
                    VTSS_D("This should not happen - the rx_delay cannot be negative");
                    delay_signed = 0;
                }
                rx_delay = (u32)delay_signed;
            } else {
                rx_delay += (sd_rx_delay_var * dv_factor[0].rx) /
                            65536U; /* Add the variable RX delay in the SERDES */
            }
            tx_delay += (sd_tx_delay_var * dv_factor[0].tx) /
                        65536U; /* Add the variable TX delay in the SERDES */
        }
        if (speed == VTSS_SPEED_2500M) { /* 2.5 Gbps */
            rx_delay = seriel_2dot5G_delay[port].rx;
            tx_delay = seriel_2dot5G_delay[port].tx;
            REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(VTSS_TO_DEV2G5(port)), &value);
            rx_delay +=
                320U * VTSS_X_DEV1G_PCS1G_LINK_STATUS_DELAY_VAR(value); /* Add the variable delay in
                                                                          the device */
            if (sd_type == FA_SERDES_TYPE_25G) {
                /* Calculate the variable RX delay in the SERDES. */
                /* On 25G SERDES 2.5G speed sd_rx_delay_var is signed */
                delay_signed = ((i16)sd_rx_delay_var * (i32)dv_factor[1].rx) / (i32)65536;
                /* Add it to the rx_delay */
                delay_signed = (i32)rx_delay + delay_signed;
                if (delay_signed < 0) {
                    VTSS_D("This should not happen - the rx_delay cannot be negative");
                    delay_signed = 0;
                }
                rx_delay = (u32)delay_signed;
            } else {
                rx_delay += (sd_rx_delay_var * dv_factor[1].rx) /
                            65536U; /* Add the variable RX delay in the SERDES */
            }
            tx_delay += (sd_tx_delay_var * dv_factor[1].tx) /
                        65536U; /* Add the variable TX delay in the SERDES */
        }
        break;
    case VTSS_PORT_INTERFACE_RMII:
    case VTSS_PORT_INTERFACE_RGMII:
    case VTSS_PORT_INTERFACE_RGMII_ID:
    case VTSS_PORT_INTERFACE_RGMII_RXID:
    case VTSS_PORT_INTERFACE_RGMII_TXID:
        /* Multi-Lane SerDes at 1 */
        if ((speed == VTSS_SPEED_10M) || (speed == VTSS_SPEED_100M)) { /* 10 Mbps - 100 Mbps */
            /* According to Morten this is not relevant */
        }
        if (speed == VTSS_SPEED_1G) { /* 1 Gbps */
            rx_delay = rgmii_1G_delay[port].rx;
            tx_delay = rgmii_1G_delay[port].tx;
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        /* Single-Lane SerDes at 100 Mbps */
        /* According to Morten this is not relevant */
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* Single-Lane SerDes at 5 or 10 or 25 Gbps */
        if (speed == VTSS_SPEED_5G) { /* 5 Gbps */
            rx_delay = seriel_5G_delay[port].rx;
            tx_delay = seriel_5G_delay[port].tx;
            rx_delay += (sd_rx_delay_var * dv_factor[2].rx) /
                        65536U; /* Add the variable RX delay in the SERDES */
            tx_delay += (sd_tx_delay_var * dv_factor[2].tx) /
                        65536U; /* Add the variable TX delay in the SERDES */
        }
        if (speed == VTSS_SPEED_10G) { /* 10 Gbps */
#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)
            if (vtss_state->port.kr_fec[port_no].r_fec) {
                rx_delay = seriel_10G_kr_delay[port].rx;
                tx_delay = seriel_10G_kr_delay[port].tx;
                REG_RD(VTSS_PCS_10GBASE_R_KR_FEC_STATUS(VTSS_TO_PCS_TGT(port)), &value);
                rx_delay +=
                    ((VTSS_X_PCS_10GBASE_R_KR_FEC_STATUS_FEC_RX_SHIFT_CNT(value) - 1) % 66) * -97;
            } else {
                rx_delay = seriel_10G_delay[port].rx;
                tx_delay = seriel_10G_delay[port].tx;
            }
#else
            rx_delay = seriel_10G_delay[port].rx;
            tx_delay = seriel_10G_delay[port].tx;
#endif
            rx_delay += (sd_rx_delay_var * dv_factor[3].rx) /
                        65536U; /* Add the variable RX delay in the SERDES */
            tx_delay += (sd_tx_delay_var * dv_factor[3].tx) /
                        65536U; /* Add the variable TX delay in the SERDES */
        }
        if (speed == VTSS_SPEED_25G) { /* 25 Gbps */
#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)
            if (vtss_state->port.kr_fec[port_no].r_fec) {
                rx_delay = seriel_25G_kr_delay[port].rx;
                tx_delay = seriel_25G_kr_delay[port].tx;
            } else if (vtss_state->port.kr_fec[port_no].rs_fec) {
                rx_delay = seriel_25G_rs_delay[port].rx;
                tx_delay = seriel_25G_rs_delay[port].tx;
            } else {
                rx_delay = seriel_25G_delay[port].rx;
                tx_delay = seriel_25G_delay[port].tx;
            }
#else
            rx_delay = seriel_25G_delay[port].rx;
            tx_delay = seriel_25G_delay[port].tx;
#endif
            rx_delay += (sd_rx_delay_var * dv_factor[4].rx) /
                        65536U; /* Add the variable RX delay in the SERDES */
            tx_delay += (sd_tx_delay_var * dv_factor[4].tx) /
                        65536U; /* Add the variable TX delay in the SERDES */
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        /* Single-Lane SerDes at 4 Gbps (QSGMII) */
        rx_delay = qsgmii_1G_delay[port].rx;
        tx_delay = qsgmii_1G_delay[port].tx;
#if defined(VTSS_ARCH_SPARX5)
        if ((port % 8) < 4) {
            /* USGMII */
            REG_RD(VTSS_PORT_CONF_USGMII_STAT(port / 8), &value);
            delay_var = VTSS_X_PORT_CONF_USGMII_STAT_DELAY_VAR(value);
        } else {
            /* QSGMII */
            REG_RD(VTSS_PORT_CONF_QSGMII_STAT(port / 8), &value);
            delay_var = VTSS_X_PORT_CONF_QSGMII_STAT_DELAY_VAR(value);
        }
#else
        REG_RD(VTSS_PORT_CONF_QSGMII_STAT(port / 4U), &value);
        delay_var = VTSS_X_PORT_CONF_QSGMII_STAT_DELAY_VAR(value);
#endif
        rx_delay += (delay_var * 200U) - ((port % 4U) * 2000U);
        tx_delay += (port % 4U) * 2000U;

        rx_delay += (sd_rx_delay_var * dv_factor[0].rx) /
                    65536U; /* Add the variable RX delay in the SERDES */
        tx_delay += (sd_tx_delay_var * dv_factor[0].tx) /
                    65536U; /* Add the variable TX delay in the SERDES */
        break;
    case VTSS_PORT_INTERFACE_USGMII:
#if defined(VTSS_ARCH_SPARX5)
        REG_RD(VTSS_PORT_CONF_USGMII_STAT(port / 8), &value);
        delay_var = VTSS_X_PORT_CONF_USGMII_STAT_DELAY_VAR(value);
        rx_delay += (delay_var * 100) - ((port % 4) * 1000);
        tx_delay += (port % 4) * 1000;

        rx_delay += (sd_rx_delay_var * dv_factor[0].rx) /
                    65536; /* Add the variable RX delay in the SERDES */
        tx_delay += (sd_tx_delay_var * dv_factor[0].tx) /
                    65536; /* Add the variable TX delay in the SERDES */
#endif
        break;
    case VTSS_PORT_INTERFACE_USXGMII:
    case VTSS_PORT_INTERFACE_QXGMII:
    case VTSS_PORT_INTERFACE_DXGMII_5G:
    case VTSS_PORT_INTERFACE_DXGMII_10G:
        /* In case of this interface types it is the PHY in front that are doing
         * the time stamping */
        /* so in the switch the latency is configured as zero */
        rx_delay = 0U;
        tx_delay = 0U;
        break;
    default:
        rc = VTSS_RC_ERROR;
        VTSS_E("unsupported interface: %u", interface);
        break;
    }
    if (rc == VTSS_RC_ERROR) {
        return rc;
    }

    /* Add additional delays found in testing. Note that rx_delay and tx_delay
     * values are in pico seconds */
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
        if (speed == VTSS_SPEED_1G) { /* 1 Gbps */
            rx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 348U) : (1000U * 49U);
            tx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 348U) : (1000U * 49U);
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        /* Single-Lane SerDes at 1 or 2.5 Gbps */
        if ((speed == VTSS_SPEED_10M) || (speed == VTSS_SPEED_100M)) { /* 10 Mbps - 100 Mbps */
            /* According to Morten this is not relevant */
        }
        if (speed == VTSS_SPEED_1G) { /* 1 Gbps */
            rx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (100U * 1080U) : (1000U * 49U);
            tx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (100U * 1080U) : (1000U * 49U);
        }
        if (speed == VTSS_SPEED_2500M) { /* 2.5 Gbps */
            rx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 33U) : (1000U * 21U);
            tx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 33U) : (1000U * 21U);
#if defined(VTSS_ARCH_SPARX5)
            /* APPL-4485: additional adjustment for PCB135 */
            rx_delay += 5534U * 1000U;
            tx_delay += 4014U * 1000U;
#endif
        }
        break;
    case VTSS_PORT_INTERFACE_RGMII:
        /* Single-Lane SerDes at 1 Gbps */
        if ((speed == VTSS_SPEED_10M) || (speed == VTSS_SPEED_100M)) { /* 10 Mbps - 100 Mbps */
            /* According to Morten this is not relevant */
        }
        if (speed == VTSS_SPEED_1G) { /* 1 Gbps */
            rx_delay += (1000U * 49U);
            tx_delay += (1000U * 49U);
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        /* Single-Lane SerDes at 100 Mbps */
        /* According to Morten this is not relevant */
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* Single-Lane SerDes at 5 or 10 or 25 Gbps */
        if (speed == VTSS_SPEED_5G) { /* 5 Gbps */
            rx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 25U) : (1000U * 8U);
            tx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (1000U * 25U) : (1000U * 8U);
        }
        if (speed == VTSS_SPEED_10G) { /* 10 Gbps */
            rx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (100U * 135U) : (1000U * 5U);
            tx_delay += (sd_type == FA_SERDES_TYPE_25G) ? (100U * 135U) : (1000U * 5U);
        }
        if (speed == VTSS_SPEED_25G) { /* 25 Gbps */
            rx_delay += 1000U * 8U;
            tx_delay += 1000U * 8U;
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        /* Single-Lane SerDes at 4 Gbps (QSGMII) */
        /* Approximated by port calibration and taking 1-PPS error into account*/
        rx_delay += 230U * 1000U + 63999U;
        tx_delay += 230U * 1000U - 63999U;

        if (speed == VTSS_SPEED_100M) { /* APPL-5631: Additional adjustment for
                                           100 Mbps */
            rx_delay += (2000U * 1000U);
            tx_delay += (2000U * 1000U);
        }
        break;

    default: VTSS_D("MISRA NON empty default"); break;
    }

#if defined(VTSS_ARCH_LAN969X)
    {
        uint32_t i, enable;
        enable = 1U;
        value = 0U;
        /* Configure TS phase detection */
        if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_328MHZ) {
            switch (speed) {
            case VTSS_SPEED_10M:
            case VTSS_SPEED_100M:
                enable = 0U;
                value = 3U;
                break;
            case VTSS_SPEED_1G:    value = 1U; break;
            case VTSS_SPEED_2500M: value = 3U; break;
            case VTSS_SPEED_5G:    value = 1U; break;
            case VTSS_SPEED_10G:   value = 2U; break;
            default:               VTSS_D("Unexpected link speed %d", speed); break;
            }
        } else if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_180MHZ) {
            switch (speed) {
            case VTSS_SPEED_10M:
            case VTSS_SPEED_100M:
                enable = 0U;
                value = 5U;
                break;
            case VTSS_SPEED_1G:    value = 2U; break;
            case VTSS_SPEED_2500M: value = 5U; break;
            case VTSS_SPEED_5G:    value = 2U; break;
            case VTSS_SPEED_10G:   value = 2U; break;
            default:               VTSS_D("Unexpected link speed %d", speed); break;
            }
        } else {
            VTSS_D("Unexpected Core Clock Frequency %d", vtss_state->init_conf.core_clock.freq);
        }
        for (i = 0U; i < 2U; ++i) {
            DEV_WRM_IDX(PHAD_CTRL, i, port, VTSS_F_DEV1G_PHAD_CTRL_DIV_CFG(value),
                        VTSS_M_DEV1G_PHAD_CTRL_DIV_CFG);
            DEV_WRM_IDX(PHAD_CTRL, i, port, VTSS_F_DEV1G_PHAD_CTRL_PHAD_ENA(enable),
                        VTSS_M_DEV1G_PHAD_CTRL_PHAD_ENA);
        }
    }
#endif

    /* rx_delay and tx_delay are in picoseconds.  */
    VTSS_I(" port_no %d speed %d interface %d rx_dly %u tx_dly %u", port_no, speed, interface,
           rx_delay, tx_delay);
    vtss_state->ts.port_conf[port_no].default_igr_latency = (i32)rx_delay;
    vtss_state->ts.port_conf[port_no].default_egr_latency = (i32)tx_delay;
    rc = vtss_cil_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = vtss_cil_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

vtss_rc vtss_cil_ts_timestamp_id_release(struct vtss_state_s *vtss_state, u32 ts_id)
{
    return fa_ts_supported(vtss_state);
}

vtss_rc vtss_cil_ts_external_io_mode_set(struct vtss_state_s *vtss_state, u32 io)
{
    vtss_ts_ext_io_mode_t *ext_io_mode;

    VTSS_RC(fa_ts_supported(vtss_state));
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];

    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin,
           ext_io_mode->domain, ext_io_mode->freq);
    FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    /* Set gpio mode */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[io].gpio_no, VTSS_GPIO_IN);
    } else {
        (void)vtss_fa_gpio_mode(vtss_state, 0U, ptp_gpio[io].gpio_no,
                                gpio_mode_calc(ptp_gpio[io].alt));
    }
    /* Set pin configuration */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        u32 dividers = HW_NS_PR_SEC / ext_io_mode->freq;
        u32 high_div = dividers / 2U - 1U;
        u32 low_div = (dividers + 1U) / 2U - 1U;
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(io), 0);
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else {
        VTSS_E("invalid pin cfg: %u", ext_io_mode->pin);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_ts_saved_timeofday_get(struct vtss_state_s *vtss_state,
                                        u32                  io,
                                        vtss_timestamp_t    *ts,
                                        u64                 *tc)
{
    vtss_rc                rc;
    vtss_ts_ext_io_mode_t *ext_io_mode;

    VTSS_RC(fa_ts_supported(vtss_state));
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin,
           ext_io_mode->domain, ext_io_mode->freq);
    rc = fa_ts_io_pin_timeofday_get(vtss_state, io, ts, tc);
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        FA_PTP_PIN_ACTION(io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    }
    return rc;
}

vtss_rc vtss_cil_ts_output_clock_edge_offset_get(struct vtss_state_s *vtss_state,
                                                 u32                  io,
                                                 u32                 *offset)
{
    u32 value;

    VTSS_RC(fa_ts_supported(vtss_state));
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_CFG(io), &value);
    *offset = VTSS_X_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(value);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
vtss_rc vtss_cil_ts_autoresp_cfg_set(struct vtss_state_s *vtss_state, u8 ctrl)
{
    vtss_ts_autoresp_dom_cfg_t *cfg;

    VTSS_RC(fa_ts_supported(vtss_state));
    if (ctrl < VTSS_TS_RESP_CTRL_ARRAY_SIZE) {
        cfg = &vtss_state->ts.auto_resp_cfg[ctrl];
        u32 msb = (cfg->clock_identity[0] << 24) + (cfg->clock_identity[1] << 16) +
                  (cfg->clock_identity[2] << 8) + (cfg->clock_identity[3]);
        u32 lsb = (cfg->clock_identity[4] << 24) + (cfg->clock_identity[5] << 16) +
                  (cfg->clock_identity[6] << 8) + (cfg->clock_identity[7]);
        REG_WR(VTSS_ANA_ACL_PTP_CLOCK_ID_MSB(ctrl),
               VTSS_F_ANA_ACL_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(msb));
        REG_WR(VTSS_ANA_ACL_PTP_CLOCK_ID_LSB(ctrl),
               VTSS_F_ANA_ACL_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(lsb));
        REG_WR(VTSS_ANA_ACL_PTP_SRC_PORT_CFG(ctrl),
               VTSS_F_ANA_ACL_PTP_SRC_PORT_CFG_PORT_NUM_SEL(cfg->ptp_port_individual) |
                   VTSS_F_ANA_ACL_PTP_SRC_PORT_CFG_PORT_NUM(cfg->ptp_port_msb));
        REG_WR(VTSS_ANA_ACL_PTP_MISC_CFG(ctrl),
               VTSS_F_ANA_ACL_PTP_MISC_CFG_FLAG_FIELD_MASK(cfg->flag_field_update.mask) |
                   VTSS_F_ANA_ACL_PTP_MISC_CFG_FLAG_FIELD(cfg->flag_field_update.value));
        return VTSS_RC_OK;
    } else {
        return VTSS_RC_ERROR;
    }
}

vtss_rc vtss_cil_ts_smac_set(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    // Set up pr port Source Mac address
    vtss_mac_t smac = vtss_state->ts.port_conf[port_no].smac;
    u32        smac_high = (smac.addr[0] << 8) + (smac.addr[1]);
    u32        smac_low =
        (smac.addr[2] << 24) + (smac.addr[3] << 16) + (smac.addr[4] << 8) + (smac.addr[5]);

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_WR(VTSS_REW_PTP_SMAC_LOW(port), VTSS_F_REW_PTP_SMAC_LOW_PTP_SMAC_LOW(smac_low));
    REG_WR(VTSS_REW_PTP_SMAC_HIGH(port), VTSS_F_REW_PTP_SMAC_HIGH_PTP_SMAC_HIGH(smac_high));
    return VTSS_RC_OK;
}
#endif // defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)

vtss_rc vtss_cil_ts_seq_cnt_get(struct vtss_state_s *vtss_state, u32 sec_cntr, u16 *const cnt_val)
{
    vtss_rc rc = VTSS_RC_OK;
    u32     value;

    VTSS_RC(fa_ts_supported(vtss_state));
    if (sec_cntr <= 1023U) {
        // read sec counter REW:PTP_SEQ_NO:PTP_SEQ_NO[0-1023].PTP_SEQ_NO
        REG_RD(VTSS_REW_PTP_SEQ_NO(sec_cntr), &value);
        *cnt_val = (u16)VTSS_X_REW_PTP_SEQ_NO_PTP_SEQ_NO(value);
    } else {
        VTSS_E("Invalid sequence counter number %d", sec_cntr);
        rc = VTSS_RC_ERROR;
    }
    return rc;
}

vtss_rc vtss_cil_ts_conf_set(struct vtss_state_s *vtss_state, const vtss_ts_conf_t *const conf)
{
    u32 i;

    VTSS_RC(fa_ts_supported(vtss_state));
    REG_WR(VTSS_ANA_AC_SG_ACCESS_SG_PTP_DOMAIN_CFG,
           VTSS_F_ANA_AC_SG_ACCESS_SG_PTP_DOMAIN_CFG_PTP_DOMAIN(conf->tsn_domain));

    for (i = 0U; i < RT_TAS_NUMBER_OF_LISTS; ++i) {
        REG_WRM(VTSS_HSCH_TAS_CFG_CTRL, VTSS_F_HSCH_TAS_CFG_CTRL_LIST_NUM(i),
                VTSS_M_HSCH_TAS_CFG_CTRL_LIST_NUM);
        REG_WRM(VTSS_HSCH_TAS_LIST_CFG, VTSS_F_HSCH_TAS_LIST_CFG_LIST_TOD_DOM(conf->tsn_domain),
                VTSS_M_HSCH_TAS_LIST_CFG_LIST_TOD_DOM);
    }
    return VTSS_RC_OK;
}

// Unsupported APIs
u32 vtss_cil_ts_ns_cnt_get(vtss_inst_t inst) { return 0U; }

vtss_rc vtss_cil_ts_timeofday_raw(struct vtss_state_s *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_ts_timeofday_one_sec(struct vtss_state_s *vtss_state) { return VTSS_RC_ERROR; }

vtss_rc vtss_cil_ts_freq_offset_get(struct vtss_state_s *vtss_state, i32 *adj)
{
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_ts_external_clock_saved_get(struct vtss_state_s *vtss_state, u32 *saved)
{
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_ts_timestamp_convert(struct vtss_state_s *vtss_state,
                                      vtss_port_no_t       port_no,
                                      u64                 *ts)
{
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cil_ts_link_up(struct vtss_state_s *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_ERROR;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc fa_debug_ts(vtss_state_t                  *vtss_state,
                           lmu_ss_t                      *ss,
                           const vtss_debug_info_t *const info)
{
    u32           port;
    lmu_fmt_buf_t buf;
    u32           idx;

    /* REW:PORT */
    for (port = 0U; port <= RT_CHIP_PORTS; port++) {
        VTSS_FMT(buf, "REW:PORT[%u]", port);
        vtss_fa_debug_reg_header(ss, buf.s);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_MODE_CFG(port, 0)),
                          "PTP_MODE_CFG[0]");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_MODE_CFG(port, 1)),
                          "PTP_MODE_CFG[1]");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_MISC_CFG(port)), "PTP_MISC_CFG");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_EDLY_CFG(port)), "PTP_EDLY_CFG");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_EDLY_CFG1(port)), "PTP_EDLY_CFG1");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_IDLY1_CFG(port)), "PTP_IDLY1_CFG");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_IDLY1_CFG1(port)),
                          "PTP_IDLY1_CFG1");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_IDLY2_CFG(port)), "PTP_IDLY2_CFG");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_IDLY2_CFG1(port)),
                          "PTP_IDLY2_CFG1");
    }

    /* REW:PTP_CTRL */
    vtss_fa_debug_reg_header(ss, "REW:PTP_CTRL");
#if defined(VTSS_ARCH_SPARX5)
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL),
                      "PTP_TWOSTEP_CTRL");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP),
                      "PTP_TWOSTEP_STAMP");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP_SUBNS),
                      "PTP_TWOSTEP_STAMP_SUBNS");
#else
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_CTRL),
                      "PTP_TWOSTEP_CTRL");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_STAMP_NSEC),
                      "PTP_TWOSTEP_STAMP");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TWOSTEP_STAMP_SUBNS),
                      "PTP_TWOSTEP_STAMP_SUBNS");
#endif

    /* DEVCPU_PTP:PTP_CFG */
    vtss_fa_debug_reg_header(ss, "DEVCPU_PTP:PTP_CFG");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_PIN_INTR), "PTP_PIN_INTR");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA),
                      "PTP_PIN_INTR_ENA");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_INTR_IDENT),
                      "PTP_PIN_INTR_IDENT");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_DOM_CFG), "PTP_DOM_CFG");

    /* DEVCPU_PTP:PTP_PINS */
    for (idx = 0U; idx <= 3U; idx++) {
        VTSS_FMT(buf, "DEVCPU_PTP:PTP_PINS[%u]", idx);
        vtss_fa_debug_reg_header(ss, buf.s);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_PIN_CFG(idx)),
                          "PTP_PIN_CFG");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(idx)),
                          "PTP_TOD_SEC_MSB");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(idx)),
                          "PTP_TOD_SEC_LSB");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(idx)),
                          "PTP_TOD_NSEC");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(idx)),
                          "PTP_TOD_NSEC_FRAC");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_NTP_NSEC(idx)), "NTP_NSEC");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(idx)),
                          "PIN_WF_HIGH_PERIOD");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(idx)),
                          "PIN_WF_LOW_PERIOD");
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEVCPU_PTP_PIN_IOBOUNCH_DELAY(idx)),
                          "PIN_IOBOUNCH_DELAY");
    }

    /* ANA_ACL::PTP_MISC_CTRL */
    vtss_fa_debug_reg_header(ss, "ANA_ACL::PTP_MISC_CTRL");
    vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_ACL_PTP_MISC_CTRL), "PTP_MISC_CTRL");

    /* ANA_ACL::PTP_MASTER */
    vtss_fa_debug_reg_header(ss, "ANA_ACL::PTP_MASTER_CFG");
    for (idx = 0; idx < VTSS_TS_RESP_CTRL_ARRAY_SIZE; idx++) {
        VTSS_FMT(buf, "PTP_CLOCK_ID_MSB[%u]", idx);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_ACL_PTP_CLOCK_ID_MSB(idx)), buf.s);
        VTSS_FMT(buf, "PTP_CLOCK_ID_LSB[%u]", idx);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_ACL_PTP_CLOCK_ID_LSB(idx)), buf.s);
        VTSS_FMT(buf, "PTP_SRC_PORT_CFG[%u]", idx);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_ACL_PTP_SRC_PORT_CFG(idx)), buf.s);
        VTSS_FMT(buf, "PTP_MISC_CFG[%u]", idx);
        vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_ANA_ACL_PTP_MISC_CFG(idx)), buf.s);
    }

    vtss_port_no_t port_no;
    /* DEV1G:DEV_CFG_STATUS / DEV10G:DEV_CFG_STATUS */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        switch (vtss_state->port.conf[port_no].if_type) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_CISCO:
        case VTSS_PORT_INTERFACE_SERDES:
        case VTSS_PORT_INTERFACE_VAUI:
        case VTSS_PORT_INTERFACE_SGMII_2G5:
        case VTSS_PORT_INTERFACE_100FX:
        case VTSS_PORT_INTERFACE_QSGMII:
            VTSS_FMT(buf, "DEV1G (port_no %u):PTP_CFG_STATUS", port_no);
            vtss_fa_debug_reg_header(ss, buf.s);
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV2G5(port))),
                              "PTP_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_RXDLY_CFG(VTSS_TO_DEV2G5(port))),
                              "PTP_RXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_TXDLY_CFG(VTSS_TO_DEV2G5(port))),
                              "PTP_TXDLY_CFG");
#if !defined(VTSS_ARCH_LAIKA)
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_PREDICT_CFG(VTSS_TO_DEV2G5(port))),
                              "PTP_PREDICT_CFG");
#endif
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEV1G_DEV_TX_CFG(VTSS_TO_DEV2G5(port))),
                              "DEV_TX_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_DEV_PFRAME_CFG(VTSS_TO_DEV2G5(port))),
                              "DEV_PFRAME_CFG");
            break;
        case VTSS_PORT_INTERFACE_SFI:
        case VTSS_PORT_INTERFACE_XAUI:
        case VTSS_PORT_INTERFACE_RXAUI:
            VTSS_FMT(buf, "DEV10G (port_no %u):DEV_CFG_STATUS", port_no);
            vtss_fa_debug_reg_header(ss, buf.s);
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV10G(port))),
                              "PTP_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_RXDLY_CFG(VTSS_TO_DEV10G(port))),
                              "PTP_RXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_TXDLY_CFG(VTSS_TO_DEV10G(port))),
                              "PTP_TXDLY_CFG");
#if !defined(VTSS_ARCH_LAIKA)
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_PTP_PREDICT_CFG(VTSS_TO_DEV10G(port))),
                              "PTP_PREDICT_CFG");
#endif
            vtss_fa_debug_reg(vtss_state, ss, REG_ADDR(VTSS_DEV1G_DEV_TX_CFG(VTSS_TO_DEV10G(port))),
                              "DEV_TX_CFG");
            vtss_fa_debug_reg(vtss_state, ss,
                              REG_ADDR(VTSS_DEV1G_DEV_PFRAME_CFG(VTSS_TO_DEV10G(port))),
                              "DEV_PFRAME_CFG");
            break;
        default: VTSS_D("MISRA NON empty default"); break;
        }
    }

    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_ts_debug_print(vtss_state_t                  *vtss_state,
                               lmu_ss_t                      *ss,
                               const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, fa_debug_ts, vtss_state, ss, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_ts_init(vtss_state_t *vtss_state)
{
    u32 domain;
#if !defined(VTSS_ARCH_LAIKA)
    u32 i;
#endif

    /* Disable PTP (all 3 domains)*/
    REG_WR(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(0));

    /* Enable PTP Delay_Req/resp processing, use default values for other bits */
    REG_WRM(VTSS_ANA_ACL_PTP_MISC_CTRL,
            VTSS_F_ANA_ACL_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA(1) |
                VTSS_F_ANA_ACL_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52(0),
            VTSS_M_ANA_ACL_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA |
                VTSS_M_ANA_ACL_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52);
    /* Configure the nominal TOD increment per clock cycle */
    switch (vtss_state->init_conf.core_clock.freq) {
    /* 250 MHz gives 4.0 ns */
    /* Due to fractional mode 250 MHz gives 3.99218750 ns - MESA-825*/
    /* 1 ns is 0x0800000000000000. */
    /* 0x0800000000000000 * 0.99218750 gives 0x07F0000000000000 */
    case VTSS_CORE_CLOCK_250MHZ:
        nominal_tod_increment = ((u64)(3) << 59U) + (u64)0x07F0000000000000;
        break;
    /* Due to fractional mode 500 MHz gives 1.99609375 ns - MESA-825 */
    /* 1 ns is 0x0800000000000000. */
    /* 0x0800000000000000 * 0.99609375 gives 0x07F8000000000000 */
    case VTSS_CORE_CLOCK_500MHZ:
        nominal_tod_increment = ((u64)(1) << 59U) + (u64)0x07F8000000000000;
        break;
    /* Due to fractional mode 625 MHz gives 1.59687500 ns - MESA-825 */
    /* 1 ns is 0x0800000000000000. */
    /* 0x0800000000000000 * 0.59687500 gives 0x04C6666666666666 */
    case VTSS_CORE_CLOCK_625MHZ:
        nominal_tod_increment = ((u64)(1) << 59U) + (u64)0x04C6666666666666;
        break;
    /* 733MHz gives a period of 1.364256ns
       0x0800000000000000 * 0.364256 gives 0x02E9FF4D2F261176 */
    case VTSS_CORE_CLOCK_733MHZ:
        nominal_tod_increment = ((u64)(1) << 59U) + (u64)0x02E9FF4D2F261176;
        break;
    /* This is according to values given in Jira UNG_LAGUNA-585 */
    case VTSS_CORE_CLOCK_328MHZ:
        if (vtss_state->init_conf.core_clock.ref_freq == VTSS_CORE_REF_CLK_25MHZ) {
            nominal_tod_increment = 0x186044FEF1EA9C10;
        }
        if (vtss_state->init_conf.core_clock.ref_freq == VTSS_CORE_REF_CLK_39MHZ) {
            nominal_tod_increment = 0x18604697DD0F9B5B;
        }
        break;
    /* This is according to values given in Jira UNG_LAGUNA-585 */
    case VTSS_CORE_CLOCK_180MHZ:
        if (vtss_state->init_conf.core_clock.ref_freq == VTSS_CORE_REF_CLK_25MHZ) {
            nominal_tod_increment = 0x2C8346575A51DBE7;
        }
        if (vtss_state->init_conf.core_clock.ref_freq == VTSS_CORE_REF_CLK_39MHZ) {
            nominal_tod_increment = 0x2C834656FFBDCFFA;
        }
        break;
    default: VTSS_D("MISRA NON empty default"); break;
    }

    /* Configure the calculated increment */
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(7),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);
    for (domain = 0U; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
        REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 0), (u32)(nominal_tod_increment & 0xFFFFFFFFU));
        REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 1), (u32)(nominal_tod_increment >> 32));
    }
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(0),
            VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);

    /* Enable PTP (all 3 domains)*/
    REG_WR(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(7));

    /* Configure the PTP pin to GPIO selection */
#if defined(VTSS_ARCH_SPARX5)
    for (i = 0U; i < 4U; ++i) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(i), VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(i),
                VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT);
    }
#endif
#if defined(VTSS_ARCH_LAN969X)
    /* The PTP pin clock generator will only work when the PTP_PIN number is
     * the same as PTPSYNC number. */
    /* The 1PPS out is PTPSYNC4 so only PTP_PIN number 4 can be used */
    REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(4), VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(4),
            VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT);
    REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(5), VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(5),
            VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT);

    for (i = 0U; i < RT_CHIP_PORTS_ALL; i++) {
        if (VTSS_PORT_IS_5G(i) || VTSS_PORT_IS_10G(i)) {
            REG_WR(VTSS_DEV10G_PTP_STAMPER_CFG(VTSS_TO_HIGH_DEV(i)), 5U);
        }
    }
#endif
    /* Get the GPIO functionality information */
    vtss_rc rc = VTSS_RC_OK;
    if (vtss_state->init_conf.gpio_func_info_get != NULL) {
        VTSS_MEMSET(ptp_gpio, 0, sizeof(ptp_gpio));
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_0, &ptp_gpio[0]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_1, &ptp_gpio[1]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_2, &ptp_gpio[2]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_3, &ptp_gpio[3]);
#if defined(VTSS_ARCH_LAN969X)
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_4, &ptp_gpio[4]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_5, &ptp_gpio[5]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_6, &ptp_gpio[6]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_7, &ptp_gpio[7]);
#endif
        if (rc != VTSS_RC_OK) {
            VTSS_E("Not able to get valid GPIO functionallity information");
        }
    } else {
        VTSS_E("gpio_func_info_get is NULL");
    }

    VTSS_MEMSET(seriel_1G_delay, 0, sizeof(seriel_1G_delay));
    VTSS_MEMSET(seriel_10G_delay, 0, sizeof(seriel_10G_delay));
    VTSS_MEMSET(seriel_2dot5G_delay, 0, sizeof(seriel_2dot5G_delay));
    VTSS_MEMSET(seriel_5G_delay, 0, sizeof(seriel_5G_delay));
    VTSS_MEMSET(seriel_25G_delay, 0, sizeof(seriel_25G_delay));
    VTSS_MEMSET(qsgmii_1G_delay, 0, sizeof(qsgmii_1G_delay));
    VTSS_MEMSET(seriel_25G_kr_delay, 0, sizeof(seriel_25G_kr_delay));
    VTSS_MEMSET(seriel_25G_rs_delay, 0, sizeof(seriel_25G_rs_delay));

#if defined(VTSS_ARCH_SPARX5)
    if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_250MHZ) {
        /* The below is based on numbers from front end simulation and is only
         * valid for 250 MHZ. */
        seriel_1G_delay[0].rx = 23587;
        seriel_1G_delay[0].tx = 129596;
        seriel_1G_delay[1].rx = 23587;
        seriel_1G_delay[1].tx = 129596;
        seriel_1G_delay[2].rx = 23587;
        seriel_1G_delay[2].tx = 129596;
        seriel_1G_delay[3].rx = 39601;
        seriel_1G_delay[3].tx = 145597;
        seriel_1G_delay[4].rx = 39601;
        seriel_1G_delay[4].tx = 145597;
        seriel_1G_delay[5].rx = 39601;
        seriel_1G_delay[5].tx = 145597;
        seriel_1G_delay[6].rx = 39601;
        seriel_1G_delay[6].tx = 145597;
        seriel_1G_delay[7].rx = 47605;
        seriel_1G_delay[7].tx = 153597;
        seriel_1G_delay[8].rx = 47605;
        seriel_1G_delay[8].tx = 153597;
        seriel_1G_delay[9].rx = 39601;
        seriel_1G_delay[9].tx = 145597;
        seriel_1G_delay[10].rx = 39601;
        seriel_1G_delay[10].tx = 145597;
        seriel_1G_delay[11].rx = 39601;
        seriel_1G_delay[11].tx = 145597;
        seriel_1G_delay[12].rx = 39601;
        seriel_1G_delay[12].tx = 145597;
        seriel_1G_delay[13].rx = 47605;
        seriel_1G_delay[13].tx = 153597;
        seriel_1G_delay[14].rx = 55599;
        seriel_1G_delay[14].tx = 161597;
        seriel_1G_delay[15].rx = 47605;
        seriel_1G_delay[15].tx = 153597;
        seriel_1G_delay[48].rx = 79609;
        seriel_1G_delay[48].tx = 185597;
        seriel_1G_delay[49].rx = 79609;
        seriel_1G_delay[49].tx = 185597;
        seriel_1G_delay[50].rx = 79609;
        seriel_1G_delay[50].tx = 185597;
        seriel_1G_delay[51].rx = 79609;
        seriel_1G_delay[51].tx = 185597;
        seriel_1G_delay[52].rx = 71597;
        seriel_1G_delay[52].tx = 177597;
        seriel_1G_delay[53].rx = 71597;
        seriel_1G_delay[53].tx = 177597;
        seriel_1G_delay[54].rx = 71597;
        seriel_1G_delay[54].tx = 177597;
        seriel_1G_delay[55].rx = 71597;
        seriel_1G_delay[55].tx = 177597;
        seriel_1G_delay[56].rx = 71597;
        seriel_1G_delay[56].tx = 177597;
        seriel_1G_delay[57].rx = 71597;
        seriel_1G_delay[57].tx = 177597;
        seriel_1G_delay[58].rx = 63595;
        seriel_1G_delay[58].tx = 169597;
        seriel_1G_delay[59].rx = 63595;
        seriel_1G_delay[59].tx = 169597;
        seriel_1G_delay[60].rx = 55599;
        seriel_1G_delay[60].tx = 161597;
        seriel_1G_delay[61].rx = 55599;
        seriel_1G_delay[61].tx = 161597;
        seriel_1G_delay[62].rx = 55599;
        seriel_1G_delay[62].tx = 161597;
        seriel_1G_delay[63].rx = 47605;
        seriel_1G_delay[63].tx = 153597;
        seriel_1G_delay[64].rx = 23587;
        seriel_1G_delay[64].tx = 129596;

        seriel_10G_delay[12].rx = 66774;
        seriel_10G_delay[12].tx = 216382;
        seriel_10G_delay[13].rx = 72979;
        seriel_10G_delay[13].tx = 222616;
        seriel_10G_delay[14].rx = 79204;
        seriel_10G_delay[14].tx = 228819;
        seriel_10G_delay[15].rx = 72979;
        seriel_10G_delay[15].tx = 222616;
        seriel_10G_delay[48].rx = 97814;
        seriel_10G_delay[48].tx = 247457;
        seriel_10G_delay[49].rx = 104030;
        seriel_10G_delay[49].tx = 253665;
        seriel_10G_delay[50].rx = 104030;
        seriel_10G_delay[50].tx = 253665;
        seriel_10G_delay[51].rx = 97814;
        seriel_10G_delay[51].tx = 247457;
        seriel_10G_delay[52].rx = 91627;
        seriel_10G_delay[52].tx = 241242;
        seriel_10G_delay[53].rx = 91627;
        seriel_10G_delay[53].tx = 241242;
        seriel_10G_delay[54].rx = 91627;
        seriel_10G_delay[54].tx = 241242;
        seriel_10G_delay[55].rx = 91627;
        seriel_10G_delay[55].tx = 241242;
        seriel_10G_delay[56].rx = 107211;
        seriel_10G_delay[56].tx = 253644;
        seriel_10G_delay[57].rx = 107211;
        seriel_10G_delay[57].tx = 253644;
        seriel_10G_delay[58].rx = 100999;
        seriel_10G_delay[58].tx = 247440;
        seriel_10G_delay[59].rx = 100999;
        seriel_10G_delay[59].tx = 247440;
        seriel_10G_delay[60].rx = 94787;
        seriel_10G_delay[60].tx = 241234;
        seriel_10G_delay[61].rx = 94787;
        seriel_10G_delay[61].tx = 241234;
        seriel_10G_delay[62].rx = 94787;
        seriel_10G_delay[62].tx = 241234;
        seriel_10G_delay[63].rx = 88581;
        seriel_10G_delay[63].tx = 235029;

        seriel_2dot5G_delay[0].rx = 8241;
        seriel_2dot5G_delay[0].tx = 53033;
        seriel_2dot5G_delay[1].rx = 8241;
        seriel_2dot5G_delay[1].tx = 53033;
        seriel_2dot5G_delay[2].rx = 8241;
        seriel_2dot5G_delay[2].tx = 53033;
        seriel_2dot5G_delay[3].rx = 14656;
        seriel_2dot5G_delay[3].tx = 59433;
        seriel_2dot5G_delay[4].rx = 14656;
        seriel_2dot5G_delay[4].tx = 59433;
        seriel_2dot5G_delay[5].rx = 14656;
        seriel_2dot5G_delay[5].tx = 59433;
        seriel_2dot5G_delay[6].rx = 14656;
        seriel_2dot5G_delay[6].tx = 59433;
        seriel_2dot5G_delay[7].rx = 17822;
        seriel_2dot5G_delay[7].tx = 62633;
        seriel_2dot5G_delay[8].rx = 17822;
        seriel_2dot5G_delay[8].tx = 62633;
        seriel_2dot5G_delay[9].rx = 14656;
        seriel_2dot5G_delay[9].tx = 59433;
        seriel_2dot5G_delay[10].rx = 14656;
        seriel_2dot5G_delay[10].tx = 59433;
        seriel_2dot5G_delay[11].rx = 14656;
        seriel_2dot5G_delay[11].tx = 59433;
        seriel_2dot5G_delay[12].rx = 14656;
        seriel_2dot5G_delay[12].tx = 59433;
        seriel_2dot5G_delay[13].rx = 17822;
        seriel_2dot5G_delay[13].tx = 62633;
        seriel_2dot5G_delay[14].rx = 21025;
        seriel_2dot5G_delay[14].tx = 65833;
        seriel_2dot5G_delay[15].rx = 17822;
        seriel_2dot5G_delay[15].tx = 62633;
        seriel_2dot5G_delay[48].rx = 30623;
        seriel_2dot5G_delay[48].tx = 75433;
        seriel_2dot5G_delay[49].rx = 30623;
        seriel_2dot5G_delay[49].tx = 75433;
        seriel_2dot5G_delay[50].rx = 30623;
        seriel_2dot5G_delay[50].tx = 75433;
        seriel_2dot5G_delay[51].rx = 30623;
        seriel_2dot5G_delay[51].tx = 75433;
        seriel_2dot5G_delay[52].rx = 27427;
        seriel_2dot5G_delay[52].tx = 72233;
        seriel_2dot5G_delay[53].rx = 27427;
        seriel_2dot5G_delay[53].tx = 72233;
        seriel_2dot5G_delay[54].rx = 27427;
        seriel_2dot5G_delay[54].tx = 72233;
        seriel_2dot5G_delay[55].rx = 27427;
        seriel_2dot5G_delay[55].tx = 72233;
        seriel_2dot5G_delay[56].rx = 27427;
        seriel_2dot5G_delay[56].tx = 72233;
        seriel_2dot5G_delay[57].rx = 27427;
        seriel_2dot5G_delay[57].tx = 72233;
        seriel_2dot5G_delay[58].rx = 24227;
        seriel_2dot5G_delay[58].tx = 69033;
        seriel_2dot5G_delay[59].rx = 24227;
        seriel_2dot5G_delay[59].tx = 69033;
        seriel_2dot5G_delay[60].rx = 21025;
        seriel_2dot5G_delay[60].tx = 65833;
        seriel_2dot5G_delay[61].rx = 21025;
        seriel_2dot5G_delay[61].tx = 65833;
        seriel_2dot5G_delay[62].rx = 21025;
        seriel_2dot5G_delay[62].tx = 65833;
        seriel_2dot5G_delay[63].rx = 17822;
        seriel_2dot5G_delay[63].tx = 62633;
        seriel_2dot5G_delay[64].rx = 8241;
        seriel_2dot5G_delay[64].tx = 53033;

        seriel_5G_delay[0].rx = 98359;
        seriel_5G_delay[0].tx = 384286;
        seriel_5G_delay[1].rx = 98359;
        seriel_5G_delay[1].tx = 384286;
        seriel_5G_delay[2].rx = 98359;
        seriel_5G_delay[2].tx = 384286;
        seriel_5G_delay[3].rx = 113866;
        seriel_5G_delay[3].tx = 399780;
        seriel_5G_delay[4].rx = 113866;
        seriel_5G_delay[4].tx = 399780;
        seriel_5G_delay[5].rx = 113866;
        seriel_5G_delay[5].tx = 399780;
        seriel_5G_delay[6].rx = 113866;
        seriel_5G_delay[6].tx = 399780;
        seriel_5G_delay[7].rx = 116975;
        seriel_5G_delay[7].tx = 402898;
        seriel_5G_delay[8].rx = 116975;
        seriel_5G_delay[8].tx = 402898;
        seriel_5G_delay[9].rx = 104564;
        seriel_5G_delay[9].tx = 390468;
        seriel_5G_delay[10].rx = 104564;
        seriel_5G_delay[10].tx = 390468;
        seriel_5G_delay[11].rx = 104564;
        seriel_5G_delay[11].tx = 390468;
        seriel_5G_delay[12].rx = 135585;
        seriel_5G_delay[12].tx = 430805;
        seriel_5G_delay[13].rx = 147997;
        seriel_5G_delay[13].tx = 443244;
        seriel_5G_delay[14].rx = 160423;
        seriel_5G_delay[14].tx = 455659;
        seriel_5G_delay[15].rx = 147997;
        seriel_5G_delay[15].tx = 443244;
        seriel_5G_delay[48].rx = 197656;
        seriel_5G_delay[48].tx = 492866;
        seriel_5G_delay[49].rx = 210070;
        seriel_5G_delay[49].tx = 505280;
        seriel_5G_delay[50].rx = 210070;
        seriel_5G_delay[50].tx = 505280;
        seriel_5G_delay[51].rx = 197656;
        seriel_5G_delay[51].tx = 492866;
        seriel_5G_delay[52].rx = 185245;
        seriel_5G_delay[52].tx = 480454;
        seriel_5G_delay[53].rx = 185245;
        seriel_5G_delay[53].tx = 480454;
        seriel_5G_delay[54].rx = 185245;
        seriel_5G_delay[54].tx = 480454;
        seriel_5G_delay[55].rx = 185245;
        seriel_5G_delay[55].tx = 480454;
        seriel_5G_delay[56].rx = 216469;
        seriel_5G_delay[56].tx = 505279;
        seriel_5G_delay[57].rx = 216469;
        seriel_5G_delay[57].tx = 505279;
        seriel_5G_delay[58].rx = 204058;
        seriel_5G_delay[58].tx = 492866;
        seriel_5G_delay[59].rx = 204058;
        seriel_5G_delay[59].tx = 492866;
        seriel_5G_delay[60].rx = 191648;
        seriel_5G_delay[60].tx = 480454;
        seriel_5G_delay[61].rx = 191648;
        seriel_5G_delay[61].tx = 480454;
        seriel_5G_delay[62].rx = 191648;
        seriel_5G_delay[62].tx = 480454;
        seriel_5G_delay[63].rx = 179228;
        seriel_5G_delay[63].tx = 468042;
        seriel_5G_delay[64].rx = 92152;
        seriel_5G_delay[64].tx = 368744;
    }

    if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_500MHZ) {
        /* The below is based on numbers from front end simulation and is only
         * valid for 500 MHZ. */
        seriel_1G_delay[0].rx = 24584;
        seriel_1G_delay[0].tx = 128595;
        seriel_1G_delay[1].rx = 24584;
        seriel_1G_delay[1].tx = 128595;
        seriel_1G_delay[2].rx = 24584;
        seriel_1G_delay[2].tx = 128595;
        seriel_1G_delay[3].rx = 40584;
        seriel_1G_delay[3].tx = 144595;
        seriel_1G_delay[4].rx = 40584;
        seriel_1G_delay[4].tx = 144595;
        seriel_1G_delay[5].rx = 40584;
        seriel_1G_delay[5].tx = 144595;
        seriel_1G_delay[6].rx = 40584;
        seriel_1G_delay[6].tx = 144595;
        seriel_1G_delay[7].rx = 48589;
        seriel_1G_delay[7].tx = 152595;
        seriel_1G_delay[8].rx = 48589;
        seriel_1G_delay[8].tx = 152595;
        seriel_1G_delay[9].rx = 40584;
        seriel_1G_delay[9].tx = 144595;
        seriel_1G_delay[10].rx = 40584;
        seriel_1G_delay[10].tx = 144595;
        seriel_1G_delay[11].rx = 40584;
        seriel_1G_delay[11].tx = 144595;
        seriel_1G_delay[12].rx = 40584;
        seriel_1G_delay[12].tx = 144595;
        seriel_1G_delay[13].rx = 48589;
        seriel_1G_delay[13].tx = 152595;
        seriel_1G_delay[14].rx = 56601;
        seriel_1G_delay[14].tx = 160595;
        seriel_1G_delay[15].rx = 48589;
        seriel_1G_delay[15].tx = 152595;
        seriel_1G_delay[48].rx = 80583;
        seriel_1G_delay[48].tx = 184595;
        seriel_1G_delay[49].rx = 80583;
        seriel_1G_delay[49].tx = 184595;
        seriel_1G_delay[50].rx = 80583;
        seriel_1G_delay[50].tx = 184595;
        seriel_1G_delay[51].rx = 80583;
        seriel_1G_delay[51].tx = 184595;
        seriel_1G_delay[52].rx = 72587;
        seriel_1G_delay[52].tx = 176595;
        seriel_1G_delay[53].rx = 72587;
        seriel_1G_delay[53].tx = 176595;
        seriel_1G_delay[54].rx = 72587;
        seriel_1G_delay[54].tx = 176595;
        seriel_1G_delay[55].rx = 72587;
        seriel_1G_delay[55].tx = 176595;
        seriel_1G_delay[56].rx = 72587;
        seriel_1G_delay[56].tx = 176595;
        seriel_1G_delay[57].rx = 72587;
        seriel_1G_delay[57].tx = 176595;
        seriel_1G_delay[58].rx = 64575;
        seriel_1G_delay[58].tx = 168595;
        seriel_1G_delay[59].rx = 64575;
        seriel_1G_delay[59].tx = 168595;
        seriel_1G_delay[60].rx = 56601;
        seriel_1G_delay[60].tx = 160595;
        seriel_1G_delay[61].rx = 56601;
        seriel_1G_delay[61].tx = 160595;
        seriel_1G_delay[62].rx = 56601;
        seriel_1G_delay[62].tx = 160595;
        seriel_1G_delay[63].rx = 48589;
        seriel_1G_delay[63].tx = 152595;
        seriel_1G_delay[64].rx = 24584;
        seriel_1G_delay[64].tx = 128595;

        seriel_10G_delay[12].rx = 67793;
        seriel_10G_delay[12].tx = 215431;
        seriel_10G_delay[13].rx = 73995;
        seriel_10G_delay[13].tx = 221603;
        seriel_10G_delay[14].rx = 80198;
        seriel_10G_delay[14].tx = 227822;
        seriel_10G_delay[15].rx = 73995;
        seriel_10G_delay[15].tx = 221603;
        seriel_10G_delay[48].rx = 98823;
        seriel_10G_delay[48].tx = 246437;
        seriel_10G_delay[49].rx = 105028;
        seriel_10G_delay[49].tx = 252642;
        seriel_10G_delay[50].rx = 105028;
        seriel_10G_delay[50].tx = 252642;
        seriel_10G_delay[51].rx = 98823;
        seriel_10G_delay[51].tx = 246437;
        seriel_10G_delay[52].rx = 92617;
        seriel_10G_delay[52].tx = 240238;
        seriel_10G_delay[53].rx = 92617;
        seriel_10G_delay[53].tx = 240238;
        seriel_10G_delay[54].rx = 92617;
        seriel_10G_delay[54].tx = 240238;
        seriel_10G_delay[55].rx = 92617;
        seriel_10G_delay[55].tx = 240238;
        seriel_10G_delay[56].rx = 108235;
        seriel_10G_delay[56].tx = 252643;
        seriel_10G_delay[57].rx = 108235;
        seriel_10G_delay[57].tx = 252643;
        seriel_10G_delay[58].rx = 102032;
        seriel_10G_delay[58].tx = 246446;
        seriel_10G_delay[59].rx = 102032;
        seriel_10G_delay[59].tx = 246446;
        seriel_10G_delay[60].rx = 95824;
        seriel_10G_delay[60].tx = 240233;
        seriel_10G_delay[61].rx = 95824;
        seriel_10G_delay[61].tx = 240233;
        seriel_10G_delay[62].rx = 95824;
        seriel_10G_delay[62].tx = 240233;
        seriel_10G_delay[63].rx = 89614;
        seriel_10G_delay[63].tx = 234027;

        seriel_2dot5G_delay[0].rx = 9214;
        seriel_2dot5G_delay[0].tx = 52042;
        seriel_2dot5G_delay[1].rx = 9214;
        seriel_2dot5G_delay[1].tx = 52042;
        seriel_2dot5G_delay[2].rx = 9214;
        seriel_2dot5G_delay[2].tx = 52042;
        seriel_2dot5G_delay[3].rx = 15636;
        seriel_2dot5G_delay[3].tx = 58440;
        seriel_2dot5G_delay[4].rx = 15636;
        seriel_2dot5G_delay[4].tx = 58440;
        seriel_2dot5G_delay[5].rx = 15636;
        seriel_2dot5G_delay[5].tx = 58440;
        seriel_2dot5G_delay[6].rx = 15636;
        seriel_2dot5G_delay[6].tx = 58440;
        seriel_2dot5G_delay[7].rx = 18840;
        seriel_2dot5G_delay[7].tx = 61641;
        seriel_2dot5G_delay[8].rx = 18840;
        seriel_2dot5G_delay[8].tx = 61641;
        seriel_2dot5G_delay[9].rx = 15636;
        seriel_2dot5G_delay[9].tx = 58440;
        seriel_2dot5G_delay[10].rx = 15636;
        seriel_2dot5G_delay[10].tx = 58440;
        seriel_2dot5G_delay[11].rx = 15636;
        seriel_2dot5G_delay[11].tx = 58440;
        seriel_2dot5G_delay[12].rx = 15636;
        seriel_2dot5G_delay[12].tx = 58440;
        seriel_2dot5G_delay[13].rx = 18840;
        seriel_2dot5G_delay[13].tx = 61641;
        seriel_2dot5G_delay[14].rx = 22016;
        seriel_2dot5G_delay[14].tx = 64840;
        seriel_2dot5G_delay[15].rx = 18840;
        seriel_2dot5G_delay[15].tx = 61641;
        seriel_2dot5G_delay[48].rx = 31623;
        seriel_2dot5G_delay[48].tx = 74440;
        seriel_2dot5G_delay[49].rx = 31623;
        seriel_2dot5G_delay[49].tx = 74440;
        seriel_2dot5G_delay[50].rx = 31623;
        seriel_2dot5G_delay[50].tx = 74440;
        seriel_2dot5G_delay[51].rx = 31623;
        seriel_2dot5G_delay[51].tx = 74440;
        seriel_2dot5G_delay[52].rx = 28425;
        seriel_2dot5G_delay[52].tx = 71242;
        seriel_2dot5G_delay[53].rx = 28425;
        seriel_2dot5G_delay[53].tx = 71242;
        seriel_2dot5G_delay[54].rx = 28425;
        seriel_2dot5G_delay[54].tx = 71242;
        seriel_2dot5G_delay[55].rx = 28425;
        seriel_2dot5G_delay[55].tx = 71242;
        seriel_2dot5G_delay[56].rx = 28425;
        seriel_2dot5G_delay[56].tx = 71242;
        seriel_2dot5G_delay[57].rx = 28425;
        seriel_2dot5G_delay[57].tx = 71242;
        seriel_2dot5G_delay[58].rx = 25234;
        seriel_2dot5G_delay[58].tx = 68041;
        seriel_2dot5G_delay[59].rx = 25234;
        seriel_2dot5G_delay[59].tx = 68041;
        seriel_2dot5G_delay[60].rx = 22016;
        seriel_2dot5G_delay[60].tx = 64840;
        seriel_2dot5G_delay[61].rx = 22016;
        seriel_2dot5G_delay[61].tx = 64840;
        seriel_2dot5G_delay[62].rx = 22016;
        seriel_2dot5G_delay[62].tx = 64840;
        seriel_2dot5G_delay[63].rx = 18840;
        seriel_2dot5G_delay[63].tx = 61641;
        seriel_2dot5G_delay[64].rx = 9214;
        seriel_2dot5G_delay[64].tx = 52042;

        seriel_25G_delay[56].rx = 23503;
        seriel_25G_delay[56].tx = 71943;
        seriel_25G_delay[57].rx = 23503;
        seriel_25G_delay[57].tx = 71943;
        seriel_25G_delay[58].rx = 21956;
        seriel_25G_delay[58].tx = 70392;
        seriel_25G_delay[59].rx = 21956;
        seriel_25G_delay[59].tx = 70392;
        seriel_25G_delay[62].rx = 20387;
        seriel_25G_delay[62].tx = 68836;
        seriel_25G_delay[63].rx = 18849;
        seriel_25G_delay[63].tx = 67292;

        seriel_5G_delay[0].rx = 99357;
        seriel_5G_delay[0].tx = 383265;
        seriel_5G_delay[1].rx = 99357;
        seriel_5G_delay[1].tx = 383265;
        seriel_5G_delay[2].rx = 99357;
        seriel_5G_delay[2].tx = 383265;
        seriel_5G_delay[3].rx = 114871;
        seriel_5G_delay[3].tx = 398773;
        seriel_5G_delay[4].rx = 114871;
        seriel_5G_delay[4].tx = 398773;
        seriel_5G_delay[5].rx = 114871;
        seriel_5G_delay[5].tx = 398773;
        seriel_5G_delay[6].rx = 114871;
        seriel_5G_delay[6].tx = 398773;
        seriel_5G_delay[7].rx = 117977;
        seriel_5G_delay[7].tx = 401882;
        seriel_5G_delay[8].rx = 117977;
        seriel_5G_delay[8].tx = 401882;
        seriel_5G_delay[9].rx = 105568;
        seriel_5G_delay[9].tx = 389470;
        seriel_5G_delay[10].rx = 105568;
        seriel_5G_delay[10].tx = 389470;
        seriel_5G_delay[11].rx = 105568;
        seriel_5G_delay[11].tx = 389470;
        seriel_5G_delay[12].rx = 136597;
        seriel_5G_delay[12].tx = 429808;
        seriel_5G_delay[13].rx = 149004;
        seriel_5G_delay[13].tx = 442220;
        seriel_5G_delay[14].rx = 161418;
        seriel_5G_delay[14].tx = 454634;
        seriel_5G_delay[15].rx = 149004;
        seriel_5G_delay[15].tx = 442220;
        seriel_5G_delay[48].rx = 198649;
        seriel_5G_delay[48].tx = 491864;
        seriel_5G_delay[49].rx = 211061;
        seriel_5G_delay[49].tx = 504247;
        seriel_5G_delay[50].rx = 211061;
        seriel_5G_delay[50].tx = 504247;
        seriel_5G_delay[51].rx = 198649;
        seriel_5G_delay[51].tx = 491864;
        seriel_5G_delay[52].rx = 186244;
        seriel_5G_delay[52].tx = 479451;
        seriel_5G_delay[53].rx = 186244;
        seriel_5G_delay[53].tx = 479451;
        seriel_5G_delay[54].rx = 186244;
        seriel_5G_delay[54].tx = 479451;
        seriel_5G_delay[55].rx = 186244;
        seriel_5G_delay[55].tx = 479451;
        seriel_5G_delay[56].rx = 217464;
        seriel_5G_delay[56].tx = 504277;
        seriel_5G_delay[57].rx = 217464;
        seriel_5G_delay[57].tx = 504277;
        seriel_5G_delay[58].rx = 205051;
        seriel_5G_delay[58].tx = 491865;
        seriel_5G_delay[59].rx = 205051;
        seriel_5G_delay[59].tx = 491865;
        seriel_5G_delay[60].rx = 192640;
        seriel_5G_delay[60].tx = 479454;
        seriel_5G_delay[61].rx = 192640;
        seriel_5G_delay[61].tx = 479454;
        seriel_5G_delay[62].rx = 192640;
        seriel_5G_delay[62].tx = 479454;
        seriel_5G_delay[63].rx = 180225;
        seriel_5G_delay[63].tx = 467041;
        seriel_5G_delay[64].rx = 93148;
        seriel_5G_delay[64].tx = 367767;

        seriel_25G_rs_delay[56].rx = 452787;
        seriel_25G_rs_delay[56].tx = 160088;
        seriel_25G_rs_delay[57].rx = 452787;
        seriel_25G_rs_delay[57].tx = 160088;
        seriel_25G_rs_delay[58].rx = 451235;
        seriel_25G_rs_delay[58].tx = 158535;
        seriel_25G_rs_delay[59].rx = 451235;
        seriel_25G_rs_delay[59].tx = 158535;
        seriel_25G_rs_delay[62].rx = 449650;
        seriel_25G_rs_delay[62].tx = 156988;
        seriel_25G_rs_delay[63].rx = 448093;
        seriel_25G_rs_delay[63].tx = 155436;
    }

    if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_625MHZ) {
        /* The below is based on numbers from front end simulation and is only
         * valid for 625 MHZ. */
        seriel_1G_delay[0].rx = 24812;
        seriel_1G_delay[0].tx = 128395;
        seriel_1G_delay[1].rx = 24812;
        seriel_1G_delay[1].tx = 128395;
        seriel_1G_delay[2].rx = 24812;
        seriel_1G_delay[2].tx = 128395;
        seriel_1G_delay[3].rx = 40807;
        seriel_1G_delay[3].tx = 144395;
        seriel_1G_delay[4].rx = 40807;
        seriel_1G_delay[4].tx = 144395;
        seriel_1G_delay[5].rx = 40807;
        seriel_1G_delay[5].tx = 144395;
        seriel_1G_delay[6].rx = 40807;
        seriel_1G_delay[6].tx = 144395;
        seriel_1G_delay[7].rx = 48809;
        seriel_1G_delay[7].tx = 152387;
        seriel_1G_delay[8].rx = 48809;
        seriel_1G_delay[8].tx = 152387;
        seriel_1G_delay[9].rx = 40807;
        seriel_1G_delay[9].tx = 144395;
        seriel_1G_delay[10].rx = 40807;
        seriel_1G_delay[10].tx = 144395;
        seriel_1G_delay[11].rx = 40807;
        seriel_1G_delay[11].tx = 144395;
        seriel_1G_delay[12].rx = 40807;
        seriel_1G_delay[12].tx = 144395;
        seriel_1G_delay[13].rx = 48809;
        seriel_1G_delay[13].tx = 152387;
        seriel_1G_delay[14].rx = 56814;
        seriel_1G_delay[14].tx = 160387;
        seriel_1G_delay[15].rx = 48809;
        seriel_1G_delay[15].tx = 152387;
        seriel_1G_delay[48].rx = 80796;
        seriel_1G_delay[48].tx = 184395;
        seriel_1G_delay[49].rx = 80796;
        seriel_1G_delay[49].tx = 184395;
        seriel_1G_delay[50].rx = 80796;
        seriel_1G_delay[50].tx = 184395;
        seriel_1G_delay[51].rx = 80796;
        seriel_1G_delay[51].tx = 184395;
        seriel_1G_delay[52].rx = 72802;
        seriel_1G_delay[52].tx = 176395;
        seriel_1G_delay[53].rx = 72802;
        seriel_1G_delay[53].tx = 176395;
        seriel_1G_delay[54].rx = 72802;
        seriel_1G_delay[54].tx = 176395;
        seriel_1G_delay[55].rx = 72802;
        seriel_1G_delay[55].tx = 176395;
        seriel_1G_delay[56].rx = 72802;
        seriel_1G_delay[56].tx = 176395;
        seriel_1G_delay[57].rx = 72802;
        seriel_1G_delay[57].tx = 176395;
        seriel_1G_delay[58].rx = 64810;
        seriel_1G_delay[58].tx = 168395;
        seriel_1G_delay[59].rx = 64810;
        seriel_1G_delay[59].tx = 168395;
        seriel_1G_delay[60].rx = 56814;
        seriel_1G_delay[60].tx = 160387;
        seriel_1G_delay[61].rx = 56814;
        seriel_1G_delay[61].tx = 160387;
        seriel_1G_delay[62].rx = 56814;
        seriel_1G_delay[62].tx = 160387;
        seriel_1G_delay[63].rx = 48809;
        seriel_1G_delay[63].tx = 152387;
        seriel_1G_delay[64].rx = 24812;
        seriel_1G_delay[64].tx = 128395;

        seriel_10G_delay[12].rx = 68003;
        seriel_10G_delay[12].tx = 215211;
        seriel_10G_delay[13].rx = 74208;
        seriel_10G_delay[13].tx = 221406;
        seriel_10G_delay[14].rx = 80416;
        seriel_10G_delay[14].tx = 227609;
        seriel_10G_delay[15].rx = 74208;
        seriel_10G_delay[15].tx = 221406;
        seriel_10G_delay[48].rx = 99033;
        seriel_10G_delay[48].tx = 246229;
        seriel_10G_delay[49].rx = 105238;
        seriel_10G_delay[49].tx = 252437;
        seriel_10G_delay[50].rx = 105238;
        seriel_10G_delay[50].tx = 252437;
        seriel_10G_delay[51].rx = 99033;
        seriel_10G_delay[51].tx = 246229;
        seriel_10G_delay[52].rx = 92836;
        seriel_10G_delay[52].tx = 240023;
        seriel_10G_delay[53].rx = 92836;
        seriel_10G_delay[53].tx = 240023;
        seriel_10G_delay[54].rx = 92836;
        seriel_10G_delay[54].tx = 240023;
        seriel_10G_delay[55].rx = 92836;
        seriel_10G_delay[55].tx = 240023;
        seriel_10G_delay[56].rx = 108444;
        seriel_10G_delay[56].tx = 252430;
        seriel_10G_delay[57].rx = 108444;
        seriel_10G_delay[57].tx = 252430;
        seriel_10G_delay[58].rx = 102236;
        seriel_10G_delay[58].tx = 246221;
        seriel_10G_delay[59].rx = 102236;
        seriel_10G_delay[59].tx = 246221;
        seriel_10G_delay[60].rx = 96037;
        seriel_10G_delay[60].tx = 240014;
        seriel_10G_delay[61].rx = 96037;
        seriel_10G_delay[61].tx = 240014;
        seriel_10G_delay[62].rx = 96037;
        seriel_10G_delay[62].tx = 240014;
        seriel_10G_delay[63].rx = 89821;
        seriel_10G_delay[63].tx = 233818;

        seriel_2dot5G_delay[0].rx = 9436;
        seriel_2dot5G_delay[0].tx = 51842;
        seriel_2dot5G_delay[1].rx = 9436;
        seriel_2dot5G_delay[1].tx = 51842;
        seriel_2dot5G_delay[2].rx = 9436;
        seriel_2dot5G_delay[2].tx = 51842;
        seriel_2dot5G_delay[3].rx = 15835;
        seriel_2dot5G_delay[3].tx = 58239;
        seriel_2dot5G_delay[4].rx = 15835;
        seriel_2dot5G_delay[4].tx = 58239;
        seriel_2dot5G_delay[5].rx = 15835;
        seriel_2dot5G_delay[5].tx = 58239;
        seriel_2dot5G_delay[6].rx = 15835;
        seriel_2dot5G_delay[6].tx = 58239;
        seriel_2dot5G_delay[7].rx = 19029;
        seriel_2dot5G_delay[7].tx = 61441;
        seriel_2dot5G_delay[8].rx = 19029;
        seriel_2dot5G_delay[8].tx = 61441;
        seriel_2dot5G_delay[9].rx = 15835;
        seriel_2dot5G_delay[9].tx = 58239;
        seriel_2dot5G_delay[10].rx = 15835;
        seriel_2dot5G_delay[10].tx = 58239;
        seriel_2dot5G_delay[11].rx = 15835;
        seriel_2dot5G_delay[11].tx = 58239;
        seriel_2dot5G_delay[12].rx = 15835;
        seriel_2dot5G_delay[12].tx = 58239;
        seriel_2dot5G_delay[13].rx = 19029;
        seriel_2dot5G_delay[13].tx = 61441;
        seriel_2dot5G_delay[14].rx = 22241;
        seriel_2dot5G_delay[14].tx = 64640;
        seriel_2dot5G_delay[15].rx = 19029;
        seriel_2dot5G_delay[15].tx = 61441;
        seriel_2dot5G_delay[48].rx = 31827;
        seriel_2dot5G_delay[48].tx = 74239;
        seriel_2dot5G_delay[49].rx = 31827;
        seriel_2dot5G_delay[49].tx = 74239;
        seriel_2dot5G_delay[50].rx = 31827;
        seriel_2dot5G_delay[50].tx = 74239;
        seriel_2dot5G_delay[51].rx = 31827;
        seriel_2dot5G_delay[51].tx = 74239;
        seriel_2dot5G_delay[52].rx = 28643;
        seriel_2dot5G_delay[52].tx = 71040;
        seriel_2dot5G_delay[53].rx = 28643;
        seriel_2dot5G_delay[53].tx = 71040;
        seriel_2dot5G_delay[54].rx = 28643;
        seriel_2dot5G_delay[54].tx = 71040;
        seriel_2dot5G_delay[55].rx = 28643;
        seriel_2dot5G_delay[55].tx = 71040;
        seriel_2dot5G_delay[56].rx = 28643;
        seriel_2dot5G_delay[56].tx = 71040;
        seriel_2dot5G_delay[57].rx = 28643;
        seriel_2dot5G_delay[57].tx = 71040;
        seriel_2dot5G_delay[58].rx = 25435;
        seriel_2dot5G_delay[58].tx = 67841;
        seriel_2dot5G_delay[59].rx = 25435;
        seriel_2dot5G_delay[59].tx = 67841;
        seriel_2dot5G_delay[60].rx = 22241;
        seriel_2dot5G_delay[60].tx = 64640;
        seriel_2dot5G_delay[61].rx = 22241;
        seriel_2dot5G_delay[61].tx = 64640;
        seriel_2dot5G_delay[62].rx = 22241;
        seriel_2dot5G_delay[62].tx = 64640;
        seriel_2dot5G_delay[63].rx = 19029;
        seriel_2dot5G_delay[63].tx = 61441;
        seriel_2dot5G_delay[64].rx = 9436;
        seriel_2dot5G_delay[64].tx = 51842;

        seriel_25G_delay[56].rx = 23699;
        seriel_25G_delay[56].tx = 71738;
        seriel_25G_delay[57].rx = 23699;
        seriel_25G_delay[57].tx = 71738;
        seriel_25G_delay[58].rx = 22148;
        seriel_25G_delay[58].tx = 70193;
        seriel_25G_delay[59].rx = 22148;
        seriel_25G_delay[59].tx = 70193;
        seriel_25G_delay[60].rx = 20608;
        seriel_25G_delay[60].tx = 68634;
        seriel_25G_delay[61].rx = 20608;
        seriel_25G_delay[61].tx = 68634;
        seriel_25G_delay[62].rx = 20608;
        seriel_25G_delay[62].tx = 68634;
        seriel_25G_delay[63].rx = 19047;
        seriel_25G_delay[63].tx = 67090;

        seriel_5G_delay[0].rx = 99571;
        seriel_5G_delay[0].tx = 383068;
        seriel_5G_delay[1].rx = 99571;
        seriel_5G_delay[1].tx = 383068;
        seriel_5G_delay[2].rx = 99571;
        seriel_5G_delay[2].tx = 383068;
        seriel_5G_delay[3].rx = 115088;
        seriel_5G_delay[3].tx = 398560;
        seriel_5G_delay[4].rx = 115088;
        seriel_5G_delay[4].tx = 398560;
        seriel_5G_delay[5].rx = 115088;
        seriel_5G_delay[5].tx = 398560;
        seriel_5G_delay[6].rx = 115088;
        seriel_5G_delay[6].tx = 398560;
        seriel_5G_delay[7].rx = 118190;
        seriel_5G_delay[7].tx = 401682;
        seriel_5G_delay[8].rx = 118190;
        seriel_5G_delay[8].tx = 401682;
        seriel_5G_delay[9].rx = 105776;
        seriel_5G_delay[9].tx = 389231;
        seriel_5G_delay[10].rx = 105776;
        seriel_5G_delay[10].tx = 389231;
        seriel_5G_delay[11].rx = 105776;
        seriel_5G_delay[11].tx = 389231;
        seriel_5G_delay[12].rx = 136813;
        seriel_5G_delay[12].tx = 429546;
        seriel_5G_delay[13].rx = 149215;
        seriel_5G_delay[13].tx = 442000;
        seriel_5G_delay[14].rx = 161624;
        seriel_5G_delay[14].tx = 454449;
        seriel_5G_delay[15].rx = 149215;
        seriel_5G_delay[15].tx = 442000;
        seriel_5G_delay[48].rx = 198881;
        seriel_5G_delay[48].tx = 491650;
        seriel_5G_delay[49].rx = 211285;
        seriel_5G_delay[49].tx = 504035;
        seriel_5G_delay[50].rx = 211285;
        seriel_5G_delay[50].tx = 504035;
        seriel_5G_delay[51].rx = 198881;
        seriel_5G_delay[51].tx = 491650;
        seriel_5G_delay[52].rx = 186459;
        seriel_5G_delay[52].tx = 479234;
        seriel_5G_delay[53].rx = 186459;
        seriel_5G_delay[53].tx = 479234;
        seriel_5G_delay[54].rx = 186459;
        seriel_5G_delay[54].tx = 479234;
        seriel_5G_delay[55].rx = 186459;
        seriel_5G_delay[55].tx = 479234;
        seriel_5G_delay[56].rx = 217680;
        seriel_5G_delay[56].tx = 504083;
        seriel_5G_delay[57].rx = 217680;
        seriel_5G_delay[57].tx = 504083;
        seriel_5G_delay[58].rx = 205272;
        seriel_5G_delay[58].tx = 491645;
        seriel_5G_delay[59].rx = 205272;
        seriel_5G_delay[59].tx = 491645;
        seriel_5G_delay[60].rx = 192865;
        seriel_5G_delay[60].tx = 479233;
        seriel_5G_delay[61].rx = 192865;
        seriel_5G_delay[61].tx = 479233;
        seriel_5G_delay[62].rx = 192865;
        seriel_5G_delay[62].tx = 479233;
        seriel_5G_delay[63].rx = 180462;
        seriel_5G_delay[63].tx = 466852;
        seriel_5G_delay[64].rx = 93374;
        seriel_5G_delay[64].tx = 367528;

        qsgmii_1G_delay[0].rx = 93612;
        qsgmii_1G_delay[0].tx = 158695;
        qsgmii_1G_delay[1].rx = 93612;
        qsgmii_1G_delay[1].tx = 158695;
        qsgmii_1G_delay[2].rx = 93612;
        qsgmii_1G_delay[2].tx = 158695;
        qsgmii_1G_delay[3].rx = 101612;
        qsgmii_1G_delay[3].tx = 166696;
        qsgmii_1G_delay[4].rx = 85606;
        qsgmii_1G_delay[4].tx = 158693;
        qsgmii_1G_delay[5].rx = 85606;
        qsgmii_1G_delay[5].tx = 158693;
        qsgmii_1G_delay[6].rx = 85606;
        qsgmii_1G_delay[6].tx = 158693;
        qsgmii_1G_delay[7].rx = 85606;
        qsgmii_1G_delay[7].tx = 158693;
        qsgmii_1G_delay[8].rx = 105607;
        qsgmii_1G_delay[8].tx = 170694;
        qsgmii_1G_delay[9].rx = 97607;
        qsgmii_1G_delay[9].tx = 162695;
        qsgmii_1G_delay[10].rx = 97607;
        qsgmii_1G_delay[10].tx = 162695;
        qsgmii_1G_delay[11].rx = 97607;
        qsgmii_1G_delay[11].tx = 162695;
        qsgmii_1G_delay[12].rx = 77610;
        qsgmii_1G_delay[12].tx = 150694;
        qsgmii_1G_delay[13].rx = 77610;
        qsgmii_1G_delay[13].tx = 150694;
        qsgmii_1G_delay[14].rx = 85606;
        qsgmii_1G_delay[14].tx = 158693;
        qsgmii_1G_delay[15].rx = 77610;
        qsgmii_1G_delay[15].tx = 150694;
        qsgmii_1G_delay[16].rx = 113610;
        qsgmii_1G_delay[16].tx = 178685;
        qsgmii_1G_delay[17].rx = 113610;
        qsgmii_1G_delay[17].tx = 178685;
        qsgmii_1G_delay[18].rx = 113610;
        qsgmii_1G_delay[18].tx = 178685;
        qsgmii_1G_delay[19].rx = 113610;
        qsgmii_1G_delay[19].tx = 178685;
        qsgmii_1G_delay[20].rx = 93609;
        qsgmii_1G_delay[20].tx = 166696;
        qsgmii_1G_delay[21].rx = 93609;
        qsgmii_1G_delay[21].tx = 166696;
        qsgmii_1G_delay[22].rx = 93609;
        qsgmii_1G_delay[22].tx = 166696;
        qsgmii_1G_delay[23].rx = 93609;
        qsgmii_1G_delay[23].tx = 166696;
        qsgmii_1G_delay[24].rx = 113610;
        qsgmii_1G_delay[24].tx = 178685;
        qsgmii_1G_delay[25].rx = 113610;
        qsgmii_1G_delay[25].tx = 178685;
        qsgmii_1G_delay[26].rx = 113610;
        qsgmii_1G_delay[26].tx = 178685;
        qsgmii_1G_delay[27].rx = 113610;
        qsgmii_1G_delay[27].tx = 178685;
        qsgmii_1G_delay[28].rx = 93609;
        qsgmii_1G_delay[28].tx = 166696;
        qsgmii_1G_delay[29].rx = 93609;
        qsgmii_1G_delay[29].tx = 166696;
        qsgmii_1G_delay[30].rx = 93609;
        qsgmii_1G_delay[30].tx = 166696;
        qsgmii_1G_delay[31].rx = 93609;
        qsgmii_1G_delay[31].tx = 166696;
        qsgmii_1G_delay[32].rx = 109610;
        qsgmii_1G_delay[32].tx = 174697;
        qsgmii_1G_delay[33].rx = 109610;
        qsgmii_1G_delay[33].tx = 174697;
        qsgmii_1G_delay[34].rx = 109610;
        qsgmii_1G_delay[34].tx = 174697;
        qsgmii_1G_delay[35].rx = 109610;
        qsgmii_1G_delay[35].tx = 174697;
        qsgmii_1G_delay[36].rx = 89612;
        qsgmii_1G_delay[36].tx = 162695;
        qsgmii_1G_delay[37].rx = 89612;
        qsgmii_1G_delay[37].tx = 162695;
        qsgmii_1G_delay[38].rx = 89612;
        qsgmii_1G_delay[38].tx = 162695;
        qsgmii_1G_delay[39].rx = 89612;
        qsgmii_1G_delay[39].tx = 162695;
        qsgmii_1G_delay[40].rx = 109610;
        qsgmii_1G_delay[40].tx = 174697;
        qsgmii_1G_delay[41].rx = 109610;
        qsgmii_1G_delay[41].tx = 174697;
        qsgmii_1G_delay[42].rx = 109610;
        qsgmii_1G_delay[42].tx = 174697;
        qsgmii_1G_delay[43].rx = 109610;
        qsgmii_1G_delay[43].tx = 174697;
        qsgmii_1G_delay[44].rx = 89612;
        qsgmii_1G_delay[44].tx = 162695;
        qsgmii_1G_delay[45].rx = 89612;
        qsgmii_1G_delay[45].tx = 162695;
        qsgmii_1G_delay[46].rx = 89612;
        qsgmii_1G_delay[46].tx = 162695;
        qsgmii_1G_delay[47].rx = 89612;
        qsgmii_1G_delay[47].tx = 162695;

        seriel_10G_kr_delay[48].rx = 347816;
        seriel_10G_kr_delay[48].tx = 265473;
        seriel_10G_kr_delay[49].rx = 354057;
        seriel_10G_kr_delay[49].tx = 271663;
        seriel_10G_kr_delay[50].rx = 354057;
        seriel_10G_kr_delay[50].tx = 271663;
        seriel_10G_kr_delay[51].rx = 347816;
        seriel_10G_kr_delay[51].tx = 265473;
        seriel_10G_kr_delay[52].rx = 341609;
        seriel_10G_kr_delay[52].tx = 259263;
        seriel_10G_kr_delay[53].rx = 341609;
        seriel_10G_kr_delay[53].tx = 259263;
        seriel_10G_kr_delay[54].rx = 341609;
        seriel_10G_kr_delay[54].tx = 259263;
        seriel_10G_kr_delay[55].rx = 341609;
        seriel_10G_kr_delay[55].tx = 259263;
        seriel_10G_kr_delay[56].rx = 357207;
        seriel_10G_kr_delay[56].tx = 271658;
        seriel_10G_kr_delay[57].rx = 357207;
        seriel_10G_kr_delay[57].tx = 271658;
        seriel_10G_kr_delay[58].rx = 350978;
        seriel_10G_kr_delay[58].tx = 265474;
        seriel_10G_kr_delay[59].rx = 350978;
        seriel_10G_kr_delay[59].tx = 265474;
        seriel_10G_kr_delay[60].rx = 344845;
        seriel_10G_kr_delay[60].tx = 259259;
        seriel_10G_kr_delay[61].rx = 344845;
        seriel_10G_kr_delay[61].tx = 259259;
        seriel_10G_kr_delay[62].rx = 344845;
        seriel_10G_kr_delay[62].tx = 259259;
        seriel_10G_kr_delay[63].rx = 338601;
        seriel_10G_kr_delay[63].tx = 253061;

        seriel_25G_kr_delay[56].rx = 123604;
        seriel_25G_kr_delay[56].tx = 81992;
        seriel_25G_kr_delay[57].rx = 123604;
        seriel_25G_kr_delay[57].tx = 81992;
        seriel_25G_kr_delay[58].rx = 122019;
        seriel_25G_kr_delay[58].tx = 80459;
        seriel_25G_kr_delay[59].rx = 122019;
        seriel_25G_kr_delay[59].tx = 80459;
        seriel_25G_kr_delay[60].rx = 120493;
        seriel_25G_kr_delay[60].tx = 78892;
        seriel_25G_kr_delay[61].rx = 120493;
        seriel_25G_kr_delay[61].tx = 78892;
        seriel_25G_kr_delay[62].rx = 120493;
        seriel_25G_kr_delay[62].tx = 78892;
        seriel_25G_kr_delay[63].rx = 118915;
        seriel_25G_kr_delay[63].tx = 77351;

        seriel_25G_rs_delay[56].rx = 453039;
        seriel_25G_rs_delay[56].tx = 159891;
        seriel_25G_rs_delay[57].rx = 453039;
        seriel_25G_rs_delay[57].tx = 159891;
        seriel_25G_rs_delay[58].rx = 451410;
        seriel_25G_rs_delay[58].tx = 158353;
        seriel_25G_rs_delay[59].rx = 451410;
        seriel_25G_rs_delay[59].tx = 158353;
        seriel_25G_rs_delay[60].rx = 449874;
        seriel_25G_rs_delay[60].tx = 156792;
        seriel_25G_rs_delay[61].rx = 449874;
        seriel_25G_rs_delay[61].tx = 156792;
        seriel_25G_rs_delay[62].rx = 449874;
        seriel_25G_rs_delay[62].tx = 156792;
        seriel_25G_rs_delay[63].rx = 448318;
        seriel_25G_rs_delay[63].tx = 155254;
    }
#else
    if (vtss_state->init_conf.core_clock.freq == VTSS_CORE_CLOCK_328MHZ) {
        /* The below is based on numbers from front end simulation and is only
         * valid for 328 MHZ. (Laguna) */
        seriel_1G_delay[0].rx = 150666U;
        seriel_1G_delay[0].tx = 162490U;
        seriel_1G_delay[4].rx = 150666U;
        seriel_1G_delay[4].tx = 162490U;
        seriel_1G_delay[8].rx = 150666U;
        seriel_1G_delay[8].tx = 162490U;
        seriel_1G_delay[12].rx = 150666U;
        seriel_1G_delay[12].tx = 162490U;
        seriel_1G_delay[16].rx = 150666U;
        seriel_1G_delay[16].tx = 162490U;
        seriel_1G_delay[20].rx = 150666U;
        seriel_1G_delay[20].tx = 162490U;
        seriel_1G_delay[24].rx = 150666U;
        seriel_1G_delay[24].tx = 162490U;
        seriel_1G_delay[25].rx = 150666U;
        seriel_1G_delay[25].tx = 162490U;
        seriel_1G_delay[26].rx = 150666U;
        seriel_1G_delay[26].tx = 162490U;
        seriel_1G_delay[27].rx = 150666U;
        seriel_1G_delay[27].tx = 162490U;

        seriel_2dot5G_delay[0].rx = 55163U;
        seriel_2dot5G_delay[0].tx = 70010U;
        seriel_2dot5G_delay[4].rx = 55163U;
        seriel_2dot5G_delay[4].tx = 70010U;
        seriel_2dot5G_delay[8].rx = 55163U;
        seriel_2dot5G_delay[8].tx = 70010U;
        seriel_2dot5G_delay[12].rx = 55163U;
        seriel_2dot5G_delay[12].tx = 70010U;
        seriel_2dot5G_delay[16].rx = 55163U;
        seriel_2dot5G_delay[16].tx = 70010U;
        seriel_2dot5G_delay[20].rx = 55163U;
        seriel_2dot5G_delay[20].tx = 70010U;
        seriel_2dot5G_delay[24].rx = 55163U;
        seriel_2dot5G_delay[24].tx = 70010U;
        seriel_2dot5G_delay[25].rx = 55163U;
        seriel_2dot5G_delay[25].tx = 70010U;
        seriel_2dot5G_delay[26].rx = 55163U;
        seriel_2dot5G_delay[26].tx = 70010U;
        seriel_2dot5G_delay[27].rx = 55163U;
        seriel_2dot5G_delay[27].tx = 70010U;

        seriel_5G_delay[0].rx = 221389U;
        seriel_5G_delay[0].tx = 295367U;
        seriel_5G_delay[4].rx = 221389U;
        seriel_5G_delay[4].tx = 295367U;
        seriel_5G_delay[8].rx = 221389U;
        seriel_5G_delay[8].tx = 295367U;
        seriel_5G_delay[12].rx = 221389U;
        seriel_5G_delay[12].tx = 295367U;
        seriel_5G_delay[16].rx = 221389U;
        seriel_5G_delay[16].tx = 295367U;
        seriel_5G_delay[20].rx = 221389U;
        seriel_5G_delay[20].tx = 295367U;
        seriel_5G_delay[24].rx = 221389U;
        seriel_5G_delay[24].tx = 295367U;
        seriel_5G_delay[25].rx = 221389U;
        seriel_5G_delay[25].tx = 295367U;
        seriel_5G_delay[26].rx = 221389U;
        seriel_5G_delay[26].tx = 295367U;
        seriel_5G_delay[27].rx = 221389U;
        seriel_5G_delay[27].tx = 295367U;

        seriel_10G_delay[0].rx = 102946U;
        seriel_10G_delay[0].tx = 155386U;
        seriel_10G_delay[4].rx = 102946U;
        seriel_10G_delay[4].tx = 155386U;
        seriel_10G_delay[8].rx = 102946U;
        seriel_10G_delay[8].tx = 155386U;
        seriel_10G_delay[12].rx = 102946U;
        seriel_10G_delay[12].tx = 155386U;
        seriel_10G_delay[16].rx = 102946U;
        seriel_10G_delay[16].tx = 155386U;
        seriel_10G_delay[20].rx = 102946U;
        seriel_10G_delay[20].tx = 155386U;
        seriel_10G_delay[24].rx = 102958U;
        seriel_10G_delay[24].tx = 155434U;
        seriel_10G_delay[25].rx = 102958U;
        seriel_10G_delay[25].tx = 155434U;
        seriel_10G_delay[26].rx = 102958U;
        seriel_10G_delay[26].tx = 155434U;
        seriel_10G_delay[27].rx = 102958U;
        seriel_10G_delay[27].tx = 155434U;

        qsgmii_1G_delay[0].rx = 195352U;
        qsgmii_1G_delay[0].tx = 176949U;
        qsgmii_1G_delay[1].rx = 203353U;
        qsgmii_1G_delay[1].tx = 184950U;
        qsgmii_1G_delay[2].rx = 203353U;
        qsgmii_1G_delay[2].tx = 184950U;
        qsgmii_1G_delay[3].rx = 203353U;
        qsgmii_1G_delay[3].tx = 184950U;
        qsgmii_1G_delay[4].rx = 195352U;
        qsgmii_1G_delay[4].tx = 176949U;
        qsgmii_1G_delay[5].rx = 203353U;
        qsgmii_1G_delay[5].tx = 184950U;
        qsgmii_1G_delay[6].rx = 203353U;
        qsgmii_1G_delay[6].tx = 184950U;
        qsgmii_1G_delay[7].rx = 203353U;
        qsgmii_1G_delay[7].tx = 184950U;
        qsgmii_1G_delay[8].rx = 195352U;
        qsgmii_1G_delay[8].tx = 176949U;
        qsgmii_1G_delay[9].rx = 195352U;
        qsgmii_1G_delay[9].tx = 176949U;
        qsgmii_1G_delay[10].rx = 203353U;
        qsgmii_1G_delay[10].tx = 184950U;
        qsgmii_1G_delay[11].rx = 203353U;
        qsgmii_1G_delay[11].tx = 184950U;
        qsgmii_1G_delay[12].rx = 195352U;
        qsgmii_1G_delay[12].tx = 176949U;
        qsgmii_1G_delay[13].rx = 195352U;
        qsgmii_1G_delay[13].tx = 176949U;
        qsgmii_1G_delay[14].rx = 203353U;
        qsgmii_1G_delay[14].tx = 184950U;
        qsgmii_1G_delay[15].rx = 203353U;
        qsgmii_1G_delay[15].tx = 184950U;
        qsgmii_1G_delay[16].rx = 195352U;
        qsgmii_1G_delay[16].tx = 176949U;
        qsgmii_1G_delay[17].rx = 195352U;
        qsgmii_1G_delay[17].tx = 176949U;
        qsgmii_1G_delay[18].rx = 203353U;
        qsgmii_1G_delay[18].tx = 184950U;
        qsgmii_1G_delay[19].rx = 203353U;
        qsgmii_1G_delay[19].tx = 184950U;
        qsgmii_1G_delay[20].rx = 195352U;
        qsgmii_1G_delay[20].tx = 176949U;
        qsgmii_1G_delay[21].rx = 195352U;
        qsgmii_1G_delay[21].tx = 176949U;
        qsgmii_1G_delay[22].rx = 203353U;
        qsgmii_1G_delay[22].tx = 184950U;
        qsgmii_1G_delay[23].rx = 203353U;
        qsgmii_1G_delay[23].tx = 184950U;

        rgmii_1G_delay[28].rx = 171936U;
        qsgmii_1G_delay[22].tx = 105058U;
        rgmii_1G_delay[29].rx = 171936U;
        qsgmii_1G_delay[23].tx = 105058U;

        seriel_10G_kr_delay[0].rx = 345538U;
        seriel_10G_kr_delay[0].tx = 180780U;
        seriel_10G_kr_delay[4].rx = 345538U;
        seriel_10G_kr_delay[4].tx = 180780U;
        seriel_10G_kr_delay[8].rx = 345538U;
        seriel_10G_kr_delay[8].tx = 180780U;
        seriel_10G_kr_delay[12].rx = 345538U;
        seriel_10G_kr_delay[12].tx = 180780U;
        seriel_10G_kr_delay[16].rx = 345538U;
        seriel_10G_kr_delay[16].tx = 180780U;
        seriel_10G_kr_delay[20].rx = 345538U;
        seriel_10G_kr_delay[20].tx = 180780U;
        seriel_10G_kr_delay[24].rx = 345538U;
        seriel_10G_kr_delay[24].tx = 180780U;
        seriel_10G_kr_delay[25].rx = 345538U;
        seriel_10G_kr_delay[25].tx = 180780U;
        seriel_10G_kr_delay[26].rx = 345538U;
        seriel_10G_kr_delay[26].tx = 180780U;
        seriel_10G_kr_delay[27].rx = 345538U;
        seriel_10G_kr_delay[27].tx = 180780U;
    }
#endif
    return VTSS_RC_OK;
}

#define DEV_REPLI_WR(name, repli, port, value)                                                     \
    {                                                                                              \
        REG_WR(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port), repli), value);                             \
        if (!VTSS_PORT_IS_2G5(port)) {                                                             \
            REG_WR(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port), repli), value);                      \
        }                                                                                          \
    }

vtss_rc vtss_fa_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    u32 port, port_no;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE: break;
    case VTSS_INIT_CMD_INIT:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 80);
        VTSS_RC(fa_ts_init(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 80);
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_PMAP, 80);
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            port = VTSS_CHIP_PORT(port_no);

            /* Initialize the PTP Port ID port number. This is done anyway in
             * the jr2_ts_operation_mode_set() function but this is only called
             * from AIL in case of changes in mode or domain. */
            REG_WRM(VTSS_ANA_ACL_PTP_CFG(port), VTSS_F_ANA_ACL_PTP_CFG_PTP_PORT_NUM(port_no + 1U),
                    VTSS_M_ANA_ACL_PTP_CFG_PTP_PORT_NUM);
        }
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_PMAP, 80);
        break;
    default: VTSS_D("MISRA NON empty default"); break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_FA */
