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

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

#if defined(VTSS_FEATURE_TIMESTAMP)

/* - CIL functions ------------------------------------------------- */

/* GPIO configuration */
static const u8 ptp_gpio[4] = {
    8,  /* PTP_0 */
    9,  /* PTP_1 */
    24, /* PTP_2 */
    25  /* PTP_3 */
};

#define HW_NS_PR_SEC 1000000000L
#define HW_PS_PR_SEC 1000000000000LL
#define HW_PS_PR_NS  1000
#define ADJ_UNITS_PR_NS 10
#define PPS_WIDTH 200 /* Width of 1PPS pulse in ns */


/* Actions on PTP pins */
#define PTP_PIN_ACTION_IDLE  0
#define PTP_PIN_ACTION_LOAD  1
#define PTP_PIN_ACTION_SAVE  2
#define PTP_PIN_ACTION_CLOCK 3
#define PTP_PIN_ACTION_DELTA 4
#define PTP_PIN_ACTION_NOSYNC 0
#define PTP_PIN_ACTION_SYNC 1

#define FA_PTP_PIN_ACTION(pin, act, sync, dom)                        \
REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(pin),                     \
         VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_ACTION(act) |   \
         VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SYNC(sync) |    \
         VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_DOM(dom),       \
         VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_ACTION |        \
         VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SYNC |          \
         VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_DOM);           \


static vtss_rc timestampAddSec(vtss_timestamp_t *ts)
{
    if (ts->seconds == 0xffffffff) {
        ts->sec_msb++;
        ts->seconds = 0;
    } else {
        ts->seconds++;
    }
    return VTSS_RC_OK;
}

static vtss_rc timestampSubSec(vtss_timestamp_t *ts)
{
    if (ts->seconds == 0) {
        ts->sec_msb--;
        ts->seconds = 0xffffffff;
    } else {
        ts->seconds--;
    }
    return VTSS_RC_OK;
}

static vtss_rc timestampSubNanosec(vtss_timestamp_t *ts)
{
    if (ts->nanoseconds == 0) {
        VTSS_RC(timestampSubSec(ts));
        ts->nanoseconds = HW_NS_PR_SEC-1;
    } else {
        ts->nanoseconds--;
    }
    return VTSS_RC_OK;
}

static vtss_rc timestampAdd(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_add)
{
    ts->nanosecondsfrac += ts_add->nanosecondsfrac;
    if (ts->nanosecondsfrac < ts_add->nanosecondsfrac) {
        ts->nanoseconds++;
    }

    ts->nanoseconds += ts_add->nanoseconds;
    if (ts->nanoseconds >= HW_NS_PR_SEC) {
        VTSS_RC(timestampAddSec(ts));
        ts->nanoseconds -= HW_NS_PR_SEC;
    }

    ts->seconds += ts_add->seconds;
    if (ts->seconds < ts_add->seconds) {
        ts->sec_msb++;
    }

    ts->sec_msb += ts_add->sec_msb;
    return VTSS_RC_OK;
}

static vtss_rc timestampSub(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_sub)
{
    if (ts->nanosecondsfrac < ts_sub->nanosecondsfrac) {
        VTSS_RC(timestampSubNanosec(ts));
    }
    ts->nanosecondsfrac -= ts_sub->nanosecondsfrac;

    if (ts->nanoseconds < ts_sub->nanoseconds) {
        VTSS_RC(timestampSubSec(ts));
        ts->nanoseconds += HW_NS_PR_SEC;
    }
    ts->nanoseconds -= ts_sub->nanoseconds;

    if (ts->seconds < ts_sub->seconds) {
        ts->sec_msb--;
    }
    ts->seconds -= ts_sub->seconds;

    ts->sec_msb -= ts_sub->sec_msb;

    return VTSS_RC_OK;
}

static vtss_rc fa_ts_io_pin_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    u32 value;
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(io), &value);
    ts->sec_msb = VTSS_X_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(value);
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(io), &ts->seconds);
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(io), &value);
    ts->nanoseconds = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(value);
    if (ts->nanoseconds >= 0x3ffffff0 && ts->nanoseconds <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        VTSS_RC(timestampSubSec(ts));
        ts->nanoseconds = 999999984 + (ts->nanoseconds & 0xf);
    }
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(io), &value);
    ts->nanosecondsfrac = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(value) << 8;    /* In register it is 8 bit nano second fragments. Must return in 16 bit nano second fragments */
    *tc = ((u64)((u64)((u64)ts->seconds*VTSS_ONE_MIA) + (u64)ts->nanoseconds) << 16) + (u64)ts->nanosecondsfrac;  /* Must return tc in 16 bit nano second fragments */
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_read(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    FA_PTP_PIN_ACTION(TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, domain);
    return fa_ts_io_pin_timeofday_get(vtss_state, TOD_ACC_PIN, ts, tc);
}

static vtss_rc fa_ts_timeofday_sample(vtss_state_t *vtss_state)
{
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    vtss_ts_ext_clock_one_pps_mode_t one_pps_mode = vtss_state->ts.conf.ext_clock_mode.one_pps_mode;
    u32 domain;
    if (one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_INPUT) {
        for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
            VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, &vtss_state->ts.conf.sample_ts[domain], &vtss_state->ts.conf.sample_tc[domain]));
            VTSS_I("domain %u, sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", domain, vtss_state->ts.conf.sample_ts[domain].sec_msb, vtss_state->ts.conf.sample_ts[domain].seconds, vtss_state->ts.conf.sample_ts[domain].nanoseconds, vtss_state->ts.conf.sample_ts[domain].nanosecondsfrac);
        }
        FA_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
    } else if (one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_OUT);
        for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
            VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, &vtss_state->ts.conf.sample_ts[domain], &vtss_state->ts.conf.sample_tc[domain]));
            VTSS_I("domain %u, sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", domain, vtss_state->ts.conf.sample_ts[domain].sec_msb, vtss_state->ts.conf.sample_ts[domain].seconds, vtss_state->ts.conf.sample_ts[domain].nanoseconds, vtss_state->ts.conf.sample_ts[domain].nanosecondsfrac);
        }
        FA_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    if (vtss_state->ts.conf.ext_clock_mode.one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, tc));
    } else {
        *ts = vtss_state->ts.conf.sample_ts[domain];
        *tc = vtss_state->ts.conf.sample_tc[domain];
    }
#else
    VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, tc));
#endif
    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    return fa_ts_domain_timeofday_get(vtss_state, 0, ts, tc);
}

static vtss_rc fa_ts_domain_timeofday_prev_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    u64 tc;
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    if (vtss_state->ts.conf.ext_clock_mode.one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, &tc));
    } else {
        *ts = vtss_state->ts.conf.sample_ts[domain];
    }
#else
    VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, ts, &tc));
#endif
    ts->nanoseconds = 0;
    ts->nanosecondsfrac = 0;

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_domain_timeofday_next_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    VTSS_RC(fa_ts_domain_timeofday_prev_pps_get(vtss_state, domain, ts));
    VTSS_RC(timestampAddSec(ts));

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_next_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return fa_ts_domain_timeofday_next_pps_get(vtss_state, 0, ts);
}

static vtss_rc fa_ts_timeofday_prev_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return fa_ts_domain_timeofday_prev_pps_get(vtss_state, 0, ts);
}

static vtss_rc fa_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    /* must be in IDLE mode before the time can be loaded */
    FA_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(TOD_ACC_PIN), ts->seconds);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    FA_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, domain);
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(fa_ts_timeofday_sample(vtss_state));
#endif
    VTSS_D("domain %u, sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", domain, ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    return fa_ts_domain_timeofday_set(vtss_state, 0, ts);
}

static vtss_rc fa_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    VTSS_D("offset before: %d", offset);
    /* must be in IDLE mode before the time can be loaded */
    FA_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(-offset));
    FA_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, domain);

#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(fa_ts_timeofday_sample(vtss_state));
#endif
    VTSS_D("Time after offset_set: %d, %d, %d",vtss_state->ts.conf.sample_ts[domain].sec_msb,vtss_state->ts.conf.sample_ts[domain].seconds,vtss_state->ts.conf.sample_ts[domain].nanoseconds);
    VTSS_D("offset: %d", offset);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    return fa_ts_domain_timeofday_offset_set(vtss_state, 0, offset);
}

static vtss_rc fa_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    if (ts->seconds > 0 || ts->sec_msb > 0 || ts->nanoseconds > HW_NS_PR_SEC/2 || ts->nanosecondsfrac > 0) {
        vtss_timestamp_t ts_prev;
        u64              tc;

        /* Read current time */
        VTSS_RC(fa_ts_timeofday_read(vtss_state, domain, &ts_prev, &tc));

        /* Calculate new time */
        if (negative){
            VTSS_RC(timestampSub(&ts_prev, ts));
        } else {
            VTSS_RC(timestampAdd(&ts_prev, ts));
        }

        return fa_ts_domain_timeofday_set(vtss_state, domain, &ts_prev);
    } else {
        return fa_ts_domain_timeofday_offset_set(vtss_state, domain, negative ? -(i32)ts->nanoseconds : ts->nanoseconds);
    }
}

static vtss_rc fa_ts_timeofday_set_delta(vtss_state_t *vtss_state, const vtss_timestamp_t *ts, BOOL negative)
{
    return fa_ts_domain_timeofday_set_delta(vtss_state, 0, ts, negative);
}

static u64 nominal_tod_increment(vtss_state_t *vtss_state)
{
    u32 clk_in_100ps, clk_cfg;

    /* Read the nominal system clock period length in 100 ps */
    REG_RD(VTSS_HSCH_SYS_CLK_PER, &clk_cfg);
    clk_in_100ps = VTSS_X_HSCH_SYS_CLK_PER_SYS_CLK_PER_100PS(clk_cfg);

    /* Calculate the nominal TOD increment per clock cycle */
    /* The TOD increment is a 64 bit value with 59 bits as the nano second fragment. This give a nano second resolution of 0x08000000 00000000 */
    /* This divided by 10 gives approx. 0x00CCCCCC CCCCCCCC that is the TOD increment per 100 ps */
    return (clk_in_100ps * 0x00CCCCCCCCCCCCCC);
}

static vtss_rc fa_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    i32 adj;
    u32 adj_abs;
    u64 tod_inc, tod_delta, tod_trunk;

    if (domain >= VTSS_TS_DOMAIN_ARRAY_SIZE) {
        return VTSS_RC_ERROR;
    }
    adj = vtss_state->ts.conf.adj[domain];
    adj_abs = VTSS_LABS(adj);

    tod_inc = nominal_tod_increment(vtss_state);  /* Fetch the nominal TOD increment as a baseline */

    /* Calculate the TOD increment delta value, that is a fraction of the nominal TOD increment. */
    /* The fraction is given by 'adj' in 1E-10. The calculation is: tod_delta = tod_inc * (adj / 1E10) */
    tod_trunk = tod_inc % 10000000000LL;   /* We will divide before multiplying to avoid overrun. The TOD truncated part is saved in 'tod_trunk' */ 
    tod_delta = (tod_inc / 10000000000LL) * adj_abs;    /* Divide and then multiply */
    tod_delta += (tod_trunk * adj_abs) / 10000000000LL; /* Now the truncated part is multiplied and then divided. Result is added to 'tod_delta' */

    /* Adjust the TOD increment with the delta value */
    if (adj > 0) {
        tod_inc += tod_delta;
    } else {
        tod_inc -= tod_delta;
    }

    /* Write back the adjusted TOD increment */
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(7), VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);
    REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 0), (u32)(tod_inc >> 32));
    REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 1), (u32)(tod_inc | 0xFFFFFFFF));
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(0), VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);

    return VTSS_RC_OK;
}

static vtss_rc fa_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    return fa_ts_domain_adjtimer_set(vtss_state, 0);
}

/* Set the clock mode for the external clock */
static vtss_rc fa_ts_external_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_ext_clock_mode_t *ext_clock_mode = &vtss_state->ts.conf.ext_clock_mode;

    VTSS_D("one_pps_mode: %u, enable: %u, freq: %u", ext_clock_mode->one_pps_mode, ext_clock_mode->enable, ext_clock_mode->freq);
    FA_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (ext_clock_mode->enable) {
        u32 dividers = HW_NS_PR_SEC/ext_clock_mode->freq;
        u32 high_div = dividers/2;
        u32 low_div  = (dividers+1)/2;
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));

        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
        FA_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, 0);

    } else if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);

        FA_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_IN);
    }
    if (ext_clock_mode->one_pps_mode != TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(EXT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(EXT_PPS_PIN), 0);
    } else {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_IN);
    }
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(fa_ts_timeofday_sample(vtss_state));
#endif

    return VTSS_RC_OK;
}

/* Get the saved nanosec counter */
static vtss_rc fa_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
{
    u32                       nsec, nsec_frac;
    vtss_ts_alt_clock_mode_t  *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(ALT_LDST_PIN), &nsec);
    nsec = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(nsec);
    if (nsec >= 0x3ffffff0 && nsec <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        nsec = 999999984 + (nsec & 0xf);
    }
    REG_RD(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(ALT_LDST_PIN), &nsec_frac);
    nsec_frac = VTSS_X_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(nsec_frac);
    *saved = ((u64)nsec << 16) + ((u64)nsec_frac << 8);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
        } else if (alt_clock_mode->save) {
            FA_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, 0);
        } else if (alt_clock_mode->load) {
            FA_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, 0);
        }
    }
    return VTSS_RC_OK;
}

/* Set the clock mode for the alternative clock
 * the modes are:
 *    BOOL one_pps_out;        Enable 1pps output
 *    BOOL one_pps_in;         Enable 1pps input
 *    BOOL save;               Save actual time counter at next 1 PPS input
 *    BOOL load;               Load actual time counter at next 1 PPS input
 */
static vtss_rc fa_ts_alt_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    FA_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_out) {
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(ALT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(ALT_PPS_PIN), 0);

        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN], VTSS_GPIO_ALT_0);
        FA_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN], VTSS_GPIO_IN);
    }

    FA_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
            return VTSS_RC_ERROR;
        } else if (alt_clock_mode->save) {
            (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            FA_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            FA_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        }
    } else {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

/* Set the time to be loaded into the PTP timer at the next 1PPS
 * It is assumed that this function is called at the beginning of a sec */
static vtss_rc fa_ts_timeofday_next_pps_set(vtss_state_t *vtss_state, const vtss_timestamp_t *const ts)
{
    if (vtss_state->ts.conf.alt_clock_mode.one_pps_in) {
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(ALT_LDST_PIN), ts->seconds-1);
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
        REG_WR(VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_TOD_NSEC_FRAC_PTP_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    }

    VTSS_D("time at next pps: sec_msb %u, sec %u, ns %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_interface_t interface;
    u32                   port;
    vtss_ts_port_conf_t   *conf;
    i32                   rx_delay;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }
    interface = vtss_state->port.conf[port_no].if_type;
    port = VTSS_CHIP_PORT(port_no);

    conf = &vtss_state->ts.port_conf[port_no];
    rx_delay = (VTSS_INTERVAL_NS(conf->ingress_latency) + conf->default_igr_latency) / 256;
    if ((rx_delay < 0) || (rx_delay > 0xFFF)) {
        VTSS_D("invalid ingress latency %d", rx_delay);
        return VTSS_RC_ERROR;
    }
    VTSS_D("rx_delay %d", rx_delay);

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_100FX:
    case VTSS_PORT_INTERFACE_QSGMII:
        REG_WRM(VTSS_DEV1G_PTP_RXDLY_CFG(VTSS_TO_DEV2G5(port)),
                VTSS_F_DEV1G_PTP_RXDLY_CFG_PTP_RX_IO_DLY(rx_delay),
                VTSS_M_DEV1G_PTP_RXDLY_CFG_PTP_RX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_SFI:
    case VTSS_PORT_INTERFACE_XAUI:
    case VTSS_PORT_INTERFACE_RXAUI:
        REG_WRM(VTSS_DEV10G_PTP_RXDLY_CFG(VTSS_TO_DEV10G(port)),
                VTSS_F_DEV10G_PTP_RXDLY_CFG_PTP_RX_IO_DLY(rx_delay),
                VTSS_M_DEV10G_PTP_RXDLY_CFG_PTP_RX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32                 p2p_delay = VTSS_INTERVAL_NS(conf->p2p_delay);
    REG_WR(VTSS_REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), p2p_delay + VTSS_INTERVAL_NS(conf->delay_asymmetry));
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_interface_t interface;
    u32                   port;
    vtss_ts_port_conf_t   *conf;
    i32                   tx_delay;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }
    interface = vtss_state->port.conf[port_no].if_type;

    port = VTSS_CHIP_PORT(port_no);
    conf = &vtss_state->ts.port_conf[port_no];
    tx_delay = (VTSS_INTERVAL_NS(conf->egress_latency) + conf->default_egr_latency) / 256;

    if ((tx_delay < 0) || (tx_delay > 0xFFF)) {
        VTSS_D("invalid egress latency %d", tx_delay);
        return VTSS_RC_ERROR;
    }
    VTSS_D("tx_delay %d", tx_delay);

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_100FX:
    case VTSS_PORT_INTERFACE_QSGMII:
        REG_WRM(VTSS_DEV1G_PTP_TXDLY_CFG(VTSS_TO_DEV2G5(port)),
                VTSS_F_DEV1G_PTP_TXDLY_CFG_PTP_TX_IO_DLY(tx_delay),
                VTSS_M_DEV1G_PTP_TXDLY_CFG_PTP_TX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_SFI:
    case VTSS_PORT_INTERFACE_XAUI:
    case VTSS_PORT_INTERFACE_RXAUI:
        REG_WRM(VTSS_DEV10G_PTP_TXDLY_CFG(VTSS_TO_DEV10G(port)),
                VTSS_F_DEV10G_PTP_TXDLY_CFG_PTP_TX_IO_DLY(tx_delay),
                VTSS_M_DEV10G_PTP_TXDLY_CFG_PTP_TX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_ts_delay_asymmetry_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 delay = VTSS_INTERVAL_NS(conf->delay_asymmetry);
    /* Used for Ingress asymmetry compensation (Pdelay_Resp) */
    REG_WR(VTSS_REW_PTP_IDLY1_CFG(VTSS_CHIP_PORT(port_no)), delay);
    /* Used for Egress asymmetry compensation (on Delay_Req and Pdelay_Req) */
    REG_WR(VTSS_REW_PTP_EDLY_CFG(VTSS_CHIP_PORT(port_no)), -delay);
    /* Used for Ingress asymmetry compensation (on Sync, therefore include p2p_delay ) */
    REG_WR(VTSS_REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), delay + VTSS_INTERVAL_NS(conf->p2p_delay));
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_mode_t         mode = vtss_state->ts.port_conf[port_no].mode.mode;
    u32                    domain = vtss_state->ts.port_conf[port_no].mode.domain;
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    u32                    mode_val = 0;
    vtss_port_interface_t interface = vtss_state->port.conf[port_no].if_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    if (mode == TS_MODE_INTERNAL) {
        switch (fmt) {
        case TS_INTERNAL_FMT_RESERVED_LEN_30BIT:
            mode_val = 1;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_32BIT:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            return VTSS_RC_ERROR;
        case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            return VTSS_RC_ERROR;
        case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF:
            mode_val = 2;
            break;
        default:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            return VTSS_RC_ERROR;
        }
    }
    VTSS_I("port %d, mode %d, domain %u,mode_val %u", port_no, mode, domain, mode_val);
    REG_WRM(VTSS_REW_PTP_MODE_CFG(port, 0),
            VTSS_F_REW_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
            VTSS_F_REW_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PTP_MODE_CFG_PTP_MODE_VAL |
            VTSS_M_REW_PTP_MODE_CFG_PTP_DOM_VAL);
    REG_WRM(VTSS_REW_PTP_MODE_CFG(port, 1),
            VTSS_F_REW_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
            VTSS_F_REW_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PTP_MODE_CFG_PTP_MODE_VAL |
            VTSS_M_REW_PTP_MODE_CFG_PTP_DOM_VAL);
    //Set up pr port Delay_Req/Resp Processing
    REG_WRM(VTSS_ANA_ACL_PTP_CFG(port),
            VTSS_F_ANA_ACL_PTP_CFG_PTP_PORT_NUM(port_no+1),
            VTSS_M_ANA_ACL_PTP_CFG_PTP_PORT_NUM);
    // disable central counters in DEVCPU
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG,
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(0),
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(1<<domain));
    // Set domain in DEV_xxx

    switch (interface) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_CISCO:
        case VTSS_PORT_INTERFACE_SERDES:
        case VTSS_PORT_INTERFACE_VAUI:
        case VTSS_PORT_INTERFACE_100FX:
        case VTSS_PORT_INTERFACE_QSGMII:
            VTSS_I("chip port %d, dev1 %d", port, VTSS_TO_DEV2G5(port));
            REG_WRM(VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV2G5(port)),
                    VTSS_F_DEV1G_PTP_CFG_PTP_DOM(domain),
                    VTSS_M_DEV1G_PTP_CFG_PTP_DOM);
            break;
        case VTSS_PORT_INTERFACE_SFI:
        case VTSS_PORT_INTERFACE_XAUI:
        case VTSS_PORT_INTERFACE_RXAUI:
            VTSS_I("chip port %d, dev10 %d", port, VTSS_TO_DEV10G(port));
            REG_WRM(VTSS_DEV10G_PTP_CFG(VTSS_TO_DEV10G(port)),
                    VTSS_F_DEV10G_PTP_CFG_PTP_DOM(domain),
                    VTSS_M_DEV10G_PTP_CFG_PTP_DOM);
            break;

        default:
            VTSS_E("unsupported interface: %u", interface);
            return VTSS_RC_ERROR;
    }
    // enable central counters in DEVCPU
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG,
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(1<<domain),
            VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(1<<domain));

    return VTSS_RC_OK;
}

static vtss_rc fa_ts_internal_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    switch (fmt) {
    case TS_INTERNAL_FMT_RESERVED_LEN_30BIT:
    case TS_INTERNAL_FMT_RESERVED_LEN_32BIT:
    case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
    case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF:
        break;
    default:
        VTSS_E("unsupported internal timestamp format: %u", fmt);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static u32 api_port(vtss_state_t *vtss_state, u32 chip_port)
{
    u32 port_no;
    int found = 0;
    /* Map from chip port to API port */
    if (chip_port == VTSS_CHIP_PORT_CPU) {
        port_no = VTSS_CHIP_PORT_CPU;
    } else {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (VTSS_CHIP_PORT(port_no) == chip_port) {
                found = 1;
                break;
            }
        }
        if (!found) {
            VTSS_E("unknown chip port: %u, port_no: %d", chip_port, port_no);
        }
    }
    return port_no;
}

static vtss_rc fa_ts_timestamp_get(vtss_state_t *vtss_state)
{
    u32  value;
    u32  delay;
    u32  tx_port;
    u32  mess_id;
    BOOL overflow = FALSE;
    u32  sub_ns;

    REG_RD(VTSS_REW_PTP_TWOSTEP_CTRL, &value);
    while (VTSS_X_REW_PTP_TWOSTEP_CTRL_PTP_VLD(value)) {
        /* Read TX timestamp */
        if (!VTSS_X_REW_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("TX timestamp expected but RX timestamp found");
            REG_WR(VTSS_REW_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            REG_RD(VTSS_REW_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        REG_RD(VTSS_REW_PTP_TWOSTEP_STAMP, &delay);
        tx_port = api_port(vtss_state, VTSS_X_REW_PTP_TWOSTEP_CTRL_STAMP_PORT(value));
        REG_RD(VTSS_REW_PTP_TWOSTEP_STAMP_SUBNS, &sub_ns);
        /* Read RX timestamp */
        REG_WR(VTSS_REW_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_REW_PTP_TWOSTEP_CTRL, &value);
        if (!VTSS_X_REW_PTP_TWOSTEP_CTRL_PTP_VLD(value) ||
            VTSS_X_REW_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("RX timestamp not found");
            REG_WR(VTSS_REW_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            REG_RD(VTSS_REW_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        REG_RD(VTSS_REW_PTP_TWOSTEP_STAMP, &mess_id);

        if (tx_port < VTSS_PORT_ARRAY_SIZE) {
            vtss_state->ts.status[mess_id].tx_tc[tx_port] = ((u64)delay << 16) | (sub_ns & 0xffff);
            vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
            vtss_state->ts.status[mess_id].valid_mask |= 1LL<<tx_port;
        } else {
            VTSS_E("invalid port (%u)", tx_port);
        }

        VTSS_D("value %x, delay %u, tx_port %u, mess_id %u", value, delay, tx_port, mess_id);
        REG_WR(VTSS_REW_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        REG_RD(VTSS_REW_PTP_TWOSTEP_CTRL, &value);
    }
    if (overflow) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}

/*
* Signal port status (configuration actually) change (used to detect and compensate for the internal ingress and egress latencies)
*/
static vtss_rc fa_ts_status_change(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_interface_t interface;
    u32                   port, value;
    vtss_rc               rc = VTSS_RC_OK, rc2;
    i32                   rx_delay = 0, tx_delay = 0;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }
    interface = vtss_state->port.conf[port_no].if_type;
    port = VTSS_CHIP_PORT(port_no);

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
        /* Single-Lane SerDes at 1 Gbps */
        if (port <= 7 || port == 48) {
            rx_delay = 576;
            tx_delay = 380;
        } else if (port >= 8 && port <= 15) {
            rx_delay = 655;
            tx_delay = 470;
        } else if (port >= 16 && port <= 23) {
            rx_delay = 655;
            tx_delay = 630;
        } else if (port >= 24 && port <= 31) {
            rx_delay = 815;
            tx_delay = 630;
        } else if (port >= 49 && port <= 52) {
            rx_delay = 1103;
            tx_delay = 710;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(VTSS_TO_DEV2G5(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_LINK_STATUS_DELAY_VAR(value);
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* Single-Lane SerDes at 2.5 Gbps */
        if (port >= 8 && port <= 15) {
            rx_delay = 260;
            tx_delay = 180;
        } else if (port >= 16 && port <= 23) {
            rx_delay = 260;
            tx_delay = 240;
        } else if (port >= 24 && port <= 31) {
            rx_delay = 320;
            tx_delay = 240;
        } else if (port >= 49 && port <= 52) {
            rx_delay = 440;
            tx_delay = 280;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(VTSS_TO_DEV2G5(port)), &value);
        rx_delay += 32 * VTSS_X_DEV1G_PCS1G_LINK_STATUS_DELAY_VAR(value) / 10;
        break;
    case VTSS_PORT_INTERFACE_100FX:
        /* Single-Lane SerDes at 100 Mbps */
        if (port <= 7 || port == 48) {
            rx_delay = 962;
            tx_delay = 700;
        } else if (port >= 8 && port <= 15) {
            rx_delay = 1039;
            tx_delay = 800;
        } else if (port >= 16 && port <= 23) {
            rx_delay = 1039;
            tx_delay = 960;
        } else if (port >= 24 && port <= 31) {
            rx_delay = 1199;
            tx_delay = 960;
        } else if (port == 49) {
            rx_delay = 1440;
            tx_delay = 1030;
        } else if (port == 50 || port == 51) {
            rx_delay = 1425;
            tx_delay = 1030;
        } else if (port == 52) {
            rx_delay = 1483;
            tx_delay = 1030;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        REG_RD(VTSS_DEV1G_PCS1G_LINK_STATUS(VTSS_TO_DEV2G5(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_LINK_STATUS_DELAY_VAR(value);
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* Single-Lane SerDes at 10 Gbps */
        if (port >= 49 && port <= 52) {
            rx_delay = 1170;
            tx_delay = 1510;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        /* Single-Lane SerDes at 4 Gbps (QSGMII) */
        if (port <= 15) {
            rx_delay = 1103;
            tx_delay = 577;
        } else if (port >= 16 && port <= 47) {
            rx_delay = 1100;
            tx_delay = 657;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_XAUI:
        /* Four-Lane SerDes at 10 Gbps (XAUI) */
        if (port == 49 || port == 50) {
            rx_delay = 868;
            tx_delay = 1170;
        } else if (port == 51 || port == 52) {
            rx_delay = 804;
            tx_delay = 1170;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_RXAUI:
        /* Two-Lane SerDes at 10 Gbps (RXAUI) */
        if (port == 49 || port == 50) {
            rx_delay = 916;
            tx_delay = 1168;
        } else if (port == 51 || port == 52) {
            rx_delay = 852;
            tx_delay = 1168;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        break;

    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    /* Add additional delays found in testing */
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_100FX:
        if ((port >= 8 && port <= 31) || (port >= 48 && port <= 52)) {
            /* DEV2G5 */
            rx_delay += 160;
            tx_delay += 160;
        }
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        rx_delay += 70;
        tx_delay += 70;
        break;
    default:
        /* No additional delays */
        break;
    }

    rx_delay = (rx_delay + 5) / 10;
    tx_delay = (tx_delay + 5) / 10;
    vtss_state->ts.port_conf[port_no].default_igr_latency = rx_delay;
    vtss_state->ts.port_conf[port_no].default_egr_latency = tx_delay;
    VTSS_D("port_no %d, igr_latency %d, egr_latency %d", port_no, rx_delay, tx_delay);
    rc = fa_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = fa_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

static vtss_rc fa_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_external_io_mode_set(vtss_state_t *vtss_state, u32 io)
{
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];

    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    /* Set gpio mode */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_IN);
    } else {
        (void) vtss_fa_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
    }
    /* Set pin configuration */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        u32 dividers = HW_NS_PR_SEC/ext_io_mode->freq;
        u32 high_div = dividers/2 - 1;
        u32 low_div  = (dividers+1)/2 - 1;
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else {
        VTSS_E("invalid pin cfg: %u", ext_io_mode->pin);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_ts_saved_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    vtss_rc rc ;
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    rc = fa_ts_io_pin_timeofday_get(vtss_state, io, ts, tc);
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        FA_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    }
    return rc;
}

static vtss_rc fa_ts_output_clock_edge_offset_get(vtss_state_t *vtss_state, u32 io, u32 *offset)
{
    u32  value;

    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_DEVCPU_PTP_PTP_PIN_CFG(io), &value);
    *offset = VTSS_X_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_OUTP_OFS(value);

    return VTSS_RC_OK;
}

#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
static vtss_rc fa_autoresp_ctrl_cfg_set(vtss_state_t *vtss_state, u8 ctrl)
{
    vtss_ts_autoresp_ctrl_cfg_t *cfg;
    if (ctrl < VTSS_TS_RESP_CTRL_ARRAY_SIZE) {
        cfg = &vtss_state->ts.auto_resp_cfg[ctrl];
        u32 msb = (cfg->clock_identity[0]<<24) + (cfg->clock_identity[1]<<16) + (cfg->clock_identity[2]<<8) + (cfg->clock_identity[3]);
        u32 lsb = (cfg->clock_identity[4]<<24) + (cfg->clock_identity[5]<<16) + (cfg->clock_identity[6]<<8) + (cfg->clock_identity[7]);
        REG_WR(VTSS_ANA_ACL_PTP_CLOCK_ID_MSB(ctrl),
               VTSS_F_ANA_ACL_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(msb));
        REG_WR(VTSS_ANA_ACL_PTP_CLOCK_ID_LSB(ctrl),
               VTSS_F_ANA_ACL_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(lsb));
        REG_WR(VTSS_ANA_ACL_PTP_SRC_PORT_CFG(ctrl),
               VTSS_F_ANA_ACL_PTP_SRC_PORT_CFG_PORT_NUM_SEL(cfg->ptp_port_individual)  |
               VTSS_F_ANA_ACL_PTP_SRC_PORT_CFG_PORT_NUM(cfg->ptp_port_msb));
        REG_WR(VTSS_ANA_ACL_PTP_MISC_CFG(ctrl),
               VTSS_F_ANA_ACL_PTP_MISC_CFG_FLAG_FIELD_MASK(cfg->flag_field_update.mask)  |
               VTSS_F_ANA_ACL_PTP_MISC_CFG_FLAG_FIELD(cfg->flag_field_update.value));
        return VTSS_RC_OK;
    } else {
        return VTSS_RC_ERROR;
    }

}

static vtss_rc fa_ts_smac_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32                   port = VTSS_CHIP_PORT(port_no);
    //Set up pr port Source Mac address
    vtss_mac_t smac = vtss_state->ts.port_conf[port_no].smac;
    u32 smac_high = (smac.addr[0]<<8) + (smac.addr[1]);
    u32 smac_low = (smac.addr[2]<<24) + (smac.addr[3]<<16) + (smac.addr[4]<<8) + (smac.addr[5]);
    REG_WR(VTSS_REW_PTP_SMAC_LOW(port),
           VTSS_F_REW_PTP_SMAC_LOW_PTP_SMAC_LOW(smac_low));
    REG_WR(VTSS_REW_PTP_SMAC_HIGH(port),
           VTSS_F_REW_PTP_SMAC_HIGH_PTP_SMAC_HIGH(smac_high));
    return VTSS_RC_OK;
}
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)

static vtss_rc fa_ts_seq_cnt_get(vtss_state_t *vtss_state,
                                 uint32_t                   sec_cntr,
                                 uint16_t *const            cnt_val)
{
    vtss_rc rc = VTSS_RC_OK;
    u32 value;
    if (sec_cntr <= 255) {
        // read sec counter REW:PTP_SEQ_NO:PTP_SEQ_NO[0-255].PTP_SEQ_NO
        REG_RD(VTSS_REW_PTP_SEQ_NO(sec_cntr), &value);
        *cnt_val = VTSS_X_REW_PTP_SEQ_NO_PTP_SEQ_NO(value);
    } else {
        VTSS_E("Invalid sequence counter number %d", sec_cntr);
        rc = VTSS_RC_ERROR;
    }
    return rc;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc fa_debug_ts(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    u32            port;
    vtss_port_no_t port_no;
    char           buf[64];
    int            idx;

    /* REW:PORT */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        sprintf(buf, "REW:PORT[%u]", port);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_MODE_CFG(port, 0), "PTP_MODE_CFG[0]");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_MODE_CFG(port, 1), "PTP_MODE_CFG[1]");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_MISC_CFG(port), "PTP_MISC_CFG");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_EDLY_CFG(port), "PTP_EDLY_CFG");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_EDLY_CFG1(port), "PTP_EDLY_CFG1");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_IDLY1_CFG(port), "PTP_IDLY1_CFG");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_IDLY1_CFG1(port), "PTP_IDLY1_CFG1");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_IDLY2_CFG(port), "PTP_IDLY2_CFG");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_IDLY2_CFG1(port), "PTP_IDLY2_CFG1");
    }

    /* REW:PTP_CTRL */
    vtss_fa_debug_reg_header(pr, "REW:PTP_CTRL");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_TWOSTEP_CTRL, "PTP_TWOSTEP_CTRL");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_TWOSTEP_STAMP, "PTP_TWOSTEP_STAMP");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_PTP_TWOSTEP_STAMP_SUBNS, "PTP_TWOSTEP_STAMP_SUBNS");

    /* DEVCPU_PTP:PTP_CFG */
    vtss_fa_debug_reg_header(pr, "DEVCPU_PTP:PTP_CFG");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PIN_INTR, "PTP_PIN_INTR");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PIN_INTR_ENA, "PTP_PIN_INTR_ENA");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_INTR_IDENT, "PTP_PIN_INTR_IDENT");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_DOM_CFG, "PTP_DOM_CFG");

    /* DEVCPU_PTP:PTP_PINS */
    for (idx = 0; idx <= 3; idx++) {
        sprintf(buf, "DEVCPU_PTP:PTP_PINS[%u]", idx);
        vtss_fa_debug_reg_header(pr, buf);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PIN_CFG(idx), "PTP_PIN_CFG");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_TOD_SEC_MSB(idx), "PTP_TOD_SEC_MSB");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_TOD_SEC_LSB(idx), "PTP_TOD_SEC_LSB");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_TOD_NSEC(idx), "PTP_TOD_NSEC");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_TOD_NSEC_FRAC(idx), "PTP_TOD_NSEC_FRAC");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_NTP_NSEC(idx), "NTP_NSEC");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PIN_WF_HIGH_PERIOD(idx), "PIN_WF_HIGH_PERIOD");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PIN_WF_LOW_PERIOD(idx), "PIN_WF_LOW_PERIOD");
        vtss_fa_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PIN_IOBOUNCH_DELAY(idx), "PIN_IOBOUNCH_DELAY");
    }

    /* ANA_ACL::PTP_MISC_CTRL */
    vtss_fa_debug_reg_header(pr, "ANA_ACL::PTP_MISC_CTRL");
    vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_MISC_CTRL, "PTP_MISC_CTRL");

    /* ANA_ACL::PTP_MASTER */
    vtss_fa_debug_reg_header(pr, "ANA_ACL::PTP_MASTER_CFG");
    for (idx = 0; idx <= VTSS_TS_RESP_CTRL_ARRAY_SIZE; idx++) {
        sprintf(buf, "PTP_CLOCK_ID_MSB[%u]", idx);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_CLOCK_ID_MSB(idx), buf);
        sprintf(buf, "PTP_CLOCK_ID_LSB[%u]", idx);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_CLOCK_ID_LSB(idx), buf);
        sprintf(buf, "PTP_SRC_PORT_CFG[%u]", idx);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_SRC_PORT_CFG(idx), buf);
        sprintf(buf, "PTP_MISC_CFG[%u]", idx);
        vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_MISC_CFG(idx), buf);
    }

    /* DEV1G:DEV_CFG_STATUS / DEV10G:DEV_CFG_STATUS */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        switch (vtss_state->port.conf[port_no].if_type) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_CISCO:
        case VTSS_PORT_INTERFACE_SERDES:
        case VTSS_PORT_INTERFACE_VAUI:
        case VTSS_PORT_INTERFACE_100FX:
        case VTSS_PORT_INTERFACE_QSGMII:
            sprintf(buf, "DEV1G (port_no %u):PTP_CFG_STATUS", port_no);
            vtss_fa_debug_reg_header(pr, buf);
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV2G5(port)), "PTP_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_RXDLY_CFG(VTSS_TO_DEV2G5(port)), "PTP_RXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_TXDLY_CFG(VTSS_TO_DEV2G5(port)), "PTP_TXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_PREDICT_CFG(VTSS_TO_DEV2G5(port)), "PTP_PREDICT_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_DEV_TX_CFG(VTSS_TO_DEV2G5(port)), "DEV_TX_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_DEV_PFRAME_CFG(VTSS_TO_DEV2G5(port)), "DEV_PFRAME_CFG");
            break;
        case VTSS_PORT_INTERFACE_SFI:
        case VTSS_PORT_INTERFACE_XAUI:
        case VTSS_PORT_INTERFACE_RXAUI:
            sprintf(buf, "DEV10G (port_no %u):DEV_CFG_STATUS", port_no);
            vtss_fa_debug_reg_header(pr, buf);
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_CFG(VTSS_TO_DEV10G(port)), "PTP_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_RXDLY_CFG(VTSS_TO_DEV10G(port)), "PTP_RXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_TXDLY_CFG(VTSS_TO_DEV10G(port)), "PTP_TXDLY_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_PTP_PREDICT_CFG(VTSS_TO_DEV10G(port)), "PTP_PREDICT_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_DEV_TX_CFG(VTSS_TO_DEV10G(port)), "DEV_TX_CFG");
            vtss_fa_debug_reg(vtss_state, pr, VTSS_DEV1G_DEV_PFRAME_CFG(VTSS_TO_DEV10G(port)), "DEV_PFRAME_CFG");
            break;
        default:
            break;
        }
    }

    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_ts_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, fa_debug_ts, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_ts_init(vtss_state_t *vtss_state)
{
    u32 i, domain;
    u64 tod_inc;

    /* Enable PTP (all 3 domains)*/
    REG_WR(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_ENA(7));

    /* Enable PTP Delay_Req/resp processing, use default values for other bits */
    REG_WRM(VTSS_ANA_ACL_PTP_MISC_CTRL,
            VTSS_F_ANA_ACL_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA(1) | VTSS_F_ANA_ACL_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52(0),
            VTSS_M_ANA_ACL_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA | VTSS_M_ANA_ACL_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52);


    /* Configure the nominal TOD increment per clock cycle */
    tod_inc = nominal_tod_increment(vtss_state);  /* Fetch the nominal TOD increment */
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(7), VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);
    for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
        REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 0), (u32)(tod_inc >> 32));
        REG_WR(VTSS_DEVCPU_PTP_CLK_PER_CFG(domain, 1), (u32)(tod_inc | 0xFFFFFFFF));
    }
    REG_WRM(VTSS_DEVCPU_PTP_PTP_DOM_CFG, VTSS_F_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS(0), VTSS_M_DEVCPU_PTP_PTP_DOM_CFG_PTP_CLKCFG_DIS);

    /* Configure the PTP pin to GPIO selection */
    for (i = 0; i < 4; ++i) {
        REG_WRM(VTSS_DEVCPU_PTP_PTP_PIN_CFG(i), VTSS_F_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT(i), VTSS_M_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT);
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = fa_ts_timeofday_get;
        state->domain_timeofday_get = fa_ts_domain_timeofday_get;
        state->timeofday_set = fa_ts_timeofday_set;
        state->domain_timeofday_set = fa_ts_domain_timeofday_set;
        state->timeofday_set_delta = fa_ts_timeofday_set_delta;
        state->domain_timeofday_set_delta = fa_ts_domain_timeofday_set_delta;
        state->timeofday_next_pps_get = fa_ts_timeofday_next_pps_get;
        state->timeofday_prev_pps_get = fa_ts_timeofday_prev_pps_get;
        state->domain_timeofday_next_pps_get = fa_ts_domain_timeofday_next_pps_get;
        state->timeofday_offset_set = fa_ts_timeofday_offset_set;
        state->domain_timeofday_offset_set = fa_ts_domain_timeofday_offset_set;
        state->adjtimer_set = fa_ts_adjtimer_set;
        state->domain_adjtimer_set = fa_ts_domain_adjtimer_set;
        state->timeofday_one_sec = fa_ts_timeofday_sample;
        state->external_clock_mode_set = fa_ts_external_clock_mode_set;
        state->alt_clock_saved_get = fa_ts_alt_clock_saved_get;
        state->alt_clock_mode_set = fa_ts_alt_clock_mode_set;
        state->timeofday_next_pps_set = fa_ts_timeofday_next_pps_set;
        state->ingress_latency_set = fa_ts_ingress_latency_set;
        state->p2p_delay_set = fa_ts_p2p_delay_set;
        state->egress_latency_set = fa_ts_egress_latency_set;
        state->delay_asymmetry_set = fa_ts_delay_asymmetry_set;
        state->operation_mode_set = fa_ts_operation_mode_set;
        state->internal_mode_set = fa_ts_internal_mode_set;
        state->timestamp_get = fa_ts_timestamp_get;
        state->status_change = fa_ts_status_change;
        state->timestamp_id_release = fa_ts_timestamp_id_release;
        state->external_io_mode_set = fa_ts_external_io_mode_set;
        state->saved_timeofday_get = fa_ts_saved_timeofday_get;
        state->output_clock_edge_offset_get = fa_ts_output_clock_edge_offset_get;
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        state->autoresp_cfg_set = fa_autoresp_ctrl_cfg_set;
        state->smac_set = fa_ts_smac_set;
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        state->seq_cnt_get = fa_ts_seq_cnt_get;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_ts_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_FA */
