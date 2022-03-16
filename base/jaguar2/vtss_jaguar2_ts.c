// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_jaguar2_cil.h"

#if defined(VTSS_ARCH_JAGUAR_2)

#if defined(VTSS_FEATURE_TIMESTAMP)

/* - CIL functions ------------------------------------------------- */

/* GPIO configuration */
static const u8 ptp_gpio[4] = {
#if defined(VTSS_ARCH_SERVAL_T)
    10, /* PTP_0 */
    11, /* PTP_1 */
    18, /* PTP_2 */
    19  /* PTP_3 */
#else
    8,  /* PTP_0 */
    9,  /* PTP_1 */
    26, /* PTP_2 */
    27  /* PTP_3 */
#endif
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

#define JR2_PTP_PIN_ACTION(pin, act, sync, dom)                        \
JR2_WRM(VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(pin),                     \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION(act) |   \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_SYNC(sync) |    \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_DOM(dom),       \
         VTSS_M_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION |        \
         VTSS_M_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_SYNC |          \
         VTSS_M_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_DOM);           \

static vtss_rc jr2_ts_io_pin_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    u32 value, tc_32;
    JR2_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(io), &value);
    ts->sec_msb = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(value);
    JR2_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(io), &ts->seconds);
    JR2_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(io), &value);
    ts->nanoseconds = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(value);
    if (ts->nanoseconds >= 0x3ffffff0 && ts->nanoseconds <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds = 999999984 + (ts->nanoseconds & 0xf);
    }
    JR2_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_NSF(io), &tc_32);
    /* tc is returned as 16 bit fraction of nanoseconds */
    *tc = (u64)tc_32 << 16;
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_timeofday_read(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    JR2_PTP_PIN_ACTION(TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, domain);
    return jr2_ts_io_pin_timeofday_get(vtss_state, TOD_ACC_PIN, ts, tc);
}

static vtss_rc jr2_ts_timeofday_sample(vtss_state_t *vtss_state)
{
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    vtss_ts_ext_clock_one_pps_mode_t one_pps_mode = vtss_state->ts.conf.ext_clock_mode.one_pps_mode;
    u32 domain;
    if ((one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_INPUT) || (one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT) || (one_pps_mode == TS_EXT_CLOCK_MODE_MAX)) {
        /* This is for 'one_pps_mode'  TS_EXT_CLOCK_MODE_ONE_PPS_INPUT - TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT - TS_EXT_CLOCK_MODE_MAX */
        for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
            VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, &vtss_state->ts.conf.sample_ts[domain], &vtss_state->ts.conf.sample_tc[domain]));
            VTSS_I("domain %u, sample_ts: %u-%u:%u, tc %" PRIu64 "", domain, vtss_state->ts.conf.sample_ts[domain].sec_msb, vtss_state->ts.conf.sample_ts[domain].seconds, vtss_state->ts.conf.sample_ts[domain].nanoseconds, vtss_state->ts.conf.sample_tc[domain]);

        }
        JR2_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
    } else if (one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_OUT);
        for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
            VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, &vtss_state->ts.conf.sample_ts[domain], &vtss_state->ts.conf.sample_tc[domain]));
            VTSS_I("domain %u, sample_ts: %u-%u:%u, tc %" PRIu64 "", domain, vtss_state->ts.conf.sample_ts[domain].sec_msb, vtss_state->ts.conf.sample_ts[domain].seconds, vtss_state->ts.conf.sample_ts[domain].nanoseconds, vtss_state->ts.conf.sample_tc[domain]);
        }
        JR2_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
    }
#endif
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    if (vtss_state->ts.conf.ext_clock_mode.one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, ts, tc));
    } else {
        *ts = vtss_state->ts.conf.sample_ts[domain];
        *tc = vtss_state->ts.conf.sample_tc[domain];
    }
#else
    VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, ts, tc));
#endif
    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u, domain: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, domain);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_timeofday_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    return jr2_ts_domain_timeofday_get(vtss_state, 0, ts, tc);
}

static vtss_rc jr2_ts_domain_timeofday_prev_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    u64 tc;
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    if (vtss_state->ts.conf.ext_clock_mode.one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, ts, &tc));
    } else {
        *ts = vtss_state->ts.conf.sample_ts[domain];
    }
#else
    VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, ts, &tc));
#endif
    ts->nanoseconds = 0;

    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_domain_timeofday_next_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    VTSS_RC(jr2_ts_domain_timeofday_prev_pps_get(vtss_state, domain, ts));
    VTSS_RC(vtss_timestampAddSec(ts));

    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_timeofday_next_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return jr2_ts_domain_timeofday_next_pps_get(vtss_state, 0, ts);
}

static vtss_rc jr2_ts_timeofday_prev_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return jr2_ts_domain_timeofday_prev_pps_get(vtss_state, 0, ts);
}

static vtss_rc jr2_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    //truncate nanosec value
    u32 ns = (ts->nanoseconds / vtss_state->ts.conf.clk_set_trunc) * vtss_state->ts.conf.clk_set_trunc;
    /* must be in IDLE mode before the time can be loaded */
    JR2_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
    JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(TOD_ACC_PIN), ts->seconds);
    JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(ns));
    JR2_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, domain);
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(jr2_ts_timeofday_sample(vtss_state));
#endif
    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u, domain %d", ts->sec_msb, ts->seconds, ts->nanoseconds, domain);
    VTSS_D("truncated ns: %u truncate value %d", ns, vtss_state->ts.conf.clk_set_trunc);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    return jr2_ts_domain_timeofday_set(vtss_state, 0, ts);

}
static vtss_rc jr2_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    VTSS_D("offset before: %d", offset);
    //truncate nanosec value
    offset = (offset / vtss_state->ts.conf.clk_set_trunc) * vtss_state->ts.conf.clk_set_trunc;
    /* must be in IDLE mode before the time can be loaded */
    JR2_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(-offset));
    JR2_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, domain);

#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(jr2_ts_timeofday_sample(vtss_state));
#endif
    VTSS_D("Time after offset_set: %d, %d, %d",vtss_state->ts.conf.sample_ts[domain].sec_msb,vtss_state->ts.conf.sample_ts[domain].seconds,vtss_state->ts.conf.sample_ts[domain].nanoseconds);
    VTSS_D("offset: %d", offset);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    return jr2_ts_domain_timeofday_offset_set(vtss_state, 0, offset);
}

static vtss_rc jr2_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    if (ts->seconds > 0 || ts->sec_msb > 0 || ts->nanoseconds > HW_NS_PR_SEC/2) {
        vtss_timestamp_t ts_prev;
        u64              tc;

        /* Read current time */
        VTSS_RC(jr2_ts_timeofday_read(vtss_state, domain, &ts_prev, &tc));

        /* Calculate new time */
        if (negative){
            VTSS_RC(vtss_timestampSub(&ts_prev, ts));
        } else {
            VTSS_RC(vtss_timestampAdd(&ts_prev, ts));
        }

        return jr2_ts_domain_timeofday_set(vtss_state, domain, &ts_prev);
    } else {
        return jr2_ts_domain_timeofday_offset_set(vtss_state, domain, negative ? (i32)ts->nanoseconds : -ts->nanoseconds);  /* Function jr2_ts_domain_timeofday_offset_set is subtracting nanoseconds from TOD, so 'negative' must be positive and visa versa */
    }
}

static vtss_rc jr2_ts_timeofday_set_delta(vtss_state_t *vtss_state, const vtss_timestamp_t *ts, BOOL negative)
{
    return jr2_ts_domain_timeofday_set_delta(vtss_state, 0, ts, negative);
}

static vtss_rc jr2_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    i32 adj;
    if (domain >= VTSS_TS_DOMAIN_ARRAY_SIZE) {
        return VTSS_RC_ERROR;
    } else {
        adj = vtss_state->ts.conf.adj[domain];

        if (adj != 0) {
            u32 adj_dir = (adj < 0 ? 1 : 0);
            u64 adj_abs = VTSS_LABS(adj);
            u64 adj_val = VTSS_DIV64((u64)HW_PS_PR_SEC*(u64)ADJ_UNITS_PR_NS, adj_abs);
            u32 adj_unit = 0; /* Default to picoseconds unit */
            if (adj_val >= (1L << 30)) {
                /* The adjustment value is too large to be in ps */
                adj_val = VTSS_DIV64(adj_val, (u64)HW_PS_PR_NS);
                adj_unit = 1; /* Use nanosecond uint */
            }
            if (adj_val >= (1L << 30)) { /* if it is still too big then rate is 0 */
                /* The adjustment value is too large to be in ns */
                adj = 0;
            } else {
                /* Configure and enable adjustment */
                JR2_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ(domain),
                       VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ_UNIT(adj_unit) |
                       VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ(adj_val));
                JR2_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG(domain),
                       VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_DIR(adj_dir) |
                       VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_ENA(1));
            }
        }
        if (adj == 0) {
            /* Disable adjustment */
            JR2_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG(domain), 0);
        }
        VTSS_I("domain: %u, adj: %d", domain, adj);
        return VTSS_RC_OK;
    }
}

static vtss_rc jr2_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    return jr2_ts_domain_adjtimer_set(vtss_state, 0);
}

/* Set the clock mode for the external clock */
static vtss_rc jr2_ts_external_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_ext_clock_mode_t *ext_clock_mode = &vtss_state->ts.conf.ext_clock_mode;

    VTSS_D("one_pps_mode: %u, enable: %u, freq: %u", ext_clock_mode->one_pps_mode, ext_clock_mode->enable, ext_clock_mode->freq);
    JR2_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (ext_clock_mode->enable) {
        /* When external sync pulse is enabled the 'one_pps_mode' is not considered */
        u32 dividers = HW_NS_PR_SEC/ext_clock_mode->freq;
        u32 high_div = dividers/2;
        u32 low_div  = (dividers+1)/2;
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));

        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
        JR2_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, 0);
    } else if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);

        JR2_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        /* This is for 'one_pps_mode'  TS_EXT_CLOCK_MODE_ONE_PPS_INPUT - TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT_INPUT - TS_EXT_CLOCK_MODE_MAX */
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_IN);
    }
    if (ext_clock_mode->one_pps_mode != TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        /* This for any not disabled 'one_pps_mode' */
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_PPS_PIN), 0);
        JR2_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        /* This for disabled 'one_pps_mode' */
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_IN);
    }
#if defined (TOD_ACC_EXT_PPS_PIN_SHARED)
    VTSS_RC(jr2_ts_timeofday_sample(vtss_state));
#endif

    return VTSS_RC_OK;
}

/* Get the saved nanosec counter */
static vtss_rc jr2_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
{
    u32                       nsec;
    vtss_ts_alt_clock_mode_t  *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    JR2_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(ALT_LDST_PIN), &nsec);
    nsec = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(nsec);
    if (nsec >= 0x3ffffff0 && nsec <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        nsec = 999999984 + (nsec & 0xf);
    }
    *saved = (u64)nsec << 16;
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
        } else if (alt_clock_mode->save) {
            JR2_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, 0);
        } else if (alt_clock_mode->load) {
            JR2_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, 0);
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
static vtss_rc jr2_ts_alt_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    JR2_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_out) {
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(ALT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(ALT_PPS_PIN), 0);

        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN], VTSS_GPIO_ALT_0);
        JR2_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN], VTSS_GPIO_IN);
    }

    JR2_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
            return VTSS_RC_ERROR;
        } else if (alt_clock_mode->save) {
            (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            JR2_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            JR2_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        }
    } else {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

/* Set the time to be loaded into the PTP timer at the next 1PPS
 * It is assumed that this function is called at the beginning of a sec */
static vtss_rc jr2_ts_timeofday_next_pps_set(vtss_state_t *vtss_state, const vtss_timestamp_t *const ts)
{
    if (vtss_state->ts.conf.alt_clock_mode.one_pps_in) {
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(ALT_LDST_PIN), ts->seconds-1);
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
    }

    VTSS_D("time at next pps: sec_msb %u, sec %u, ns %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_interface_t interface = vtss_state->port.conf[port_no].if_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    vtss_ts_port_conf_t   *conf = &vtss_state->ts.port_conf[port_no];
    i32                   rx_delay = VTSS_INTERVAL_NS(conf->ingress_latency) + conf->default_igr_latency;
    if (rx_delay < 0) {
        VTSS_D("invalid ingress latency %d", rx_delay);
        return VTSS_RC_ERROR;
    }
    if (rx_delay > 0x1ff) { /* Register max value is 0x1FF */
        rx_delay = 0x1ff;
    }
    VTSS_D("rx_delay %d", rx_delay);

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_100FX:
    case VTSS_PORT_INTERFACE_QSGMII:
        JR2_WRM(VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV1G(port)),
                VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(rx_delay),
                VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_SFI:
    case VTSS_PORT_INTERFACE_XAUI:
    case VTSS_PORT_INTERFACE_RXAUI:
        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV(port)),
                VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY(rx_delay),
                VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_RX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32                 p2p_delay = VTSS_INTERVAL_NS(conf->p2p_delay);
    JR2_WR(VTSS_REW_PORT_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), p2p_delay + VTSS_INTERVAL_NS(conf->delay_asymmetry));
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_port_interface_t interface = vtss_state->port.conf[port_no].if_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    vtss_ts_port_conf_t   *conf = &vtss_state->ts.port_conf[port_no];
    i32                   tx_delay = VTSS_INTERVAL_NS(conf->egress_latency) + conf->default_egr_latency;
    if (tx_delay < 0) {
        VTSS_D("invalid egress latency %d", tx_delay);
        return VTSS_RC_ERROR;
    }
    if (tx_delay > 0x1ff) { /* Register max value is 0x1FF */
        tx_delay = 0x1ff;
    }
    VTSS_D("tx_delay %d", tx_delay);

    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_100FX:
    case VTSS_PORT_INTERFACE_QSGMII:
        JR2_WRM(VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV1G(port)),
                VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(tx_delay),
                VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_SFI:
    case VTSS_PORT_INTERFACE_XAUI:
    case VTSS_PORT_INTERFACE_RXAUI:
        JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV(port)),
                VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY(tx_delay),
                VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_TX_IO_DLY);
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_delay_asymmetry_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 delay = VTSS_INTERVAL_NS(conf->delay_asymmetry);
    /* Used for Ingress asymmetry compensation (Pdelay_Resp) */
    JR2_WR(VTSS_REW_PORT_PTP_IDLY1_CFG(VTSS_CHIP_PORT(port_no)), delay);
    /* Used for Egress asymmetry compensation (on Delay_Req and Pdelay_Req) */
    JR2_WR(VTSS_REW_PORT_PTP_EDLY_CFG(VTSS_CHIP_PORT(port_no)), -delay);
    /* Used for Ingress asymmetry compensation (on Sync, therefore include p2p_delay ) */
    JR2_WR(VTSS_REW_PORT_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), delay + VTSS_INTERVAL_NS(conf->p2p_delay));
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
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
            mode_val = 2;
            break;
        case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
            mode_val = 3;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF:
            mode_val = 4;
            break;
        default:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            return VTSS_RC_ERROR;
        }
    }
    VTSS_I("port %d, mode %d, domain %u,mode_val %u", port_no, mode, domain, mode_val);
    JR2_WRM(VTSS_REW_PORT_PTP_MODE_CFG(port, 0),
            VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
            VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL |
            VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL);
    JR2_WRM(VTSS_REW_PORT_PTP_MODE_CFG(port, 1),
            VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL(mode_val) |
            VTSS_F_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL(domain),
            VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_MODE_VAL |
            VTSS_M_REW_PORT_PTP_MODE_CFG_PTP_DOM_VAL);
    //Set up pr port Delay_Req/Resp Processing
    JR2_WRM(VTSS_ANA_ACL_PORT_PTP_CFG(port),
            VTSS_F_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM(port_no+1) |
            VTSS_F_ANA_ACL_PORT_PTP_CFG_PTP_DOMAIN(domain),
            VTSS_M_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM |
            VTSS_M_ANA_ACL_PORT_PTP_CFG_PTP_DOMAIN);
    // disable central counters in DEVCPU
    JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG,
            VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA(0),
            VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA(1<<domain));
    // Set domain in DEV_xxx

    switch (interface) {
        case VTSS_PORT_INTERFACE_SGMII:
        case VTSS_PORT_INTERFACE_SGMII_2G5:
        case VTSS_PORT_INTERFACE_SGMII_CISCO:
        case VTSS_PORT_INTERFACE_SERDES:
        case VTSS_PORT_INTERFACE_VAUI:
        case VTSS_PORT_INTERFACE_100FX:
        case VTSS_PORT_INTERFACE_QSGMII:
            VTSS_I("chip port %d, dev1 %d", port, VTSS_TO_DEV1G(port));
            JR2_WRM(VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV1G(port)),
                    VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(domain),
                    VTSS_M_DEV1G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM);
            break;
        case VTSS_PORT_INTERFACE_SFI:
        case VTSS_PORT_INTERFACE_XAUI:
        case VTSS_PORT_INTERFACE_RXAUI:
            VTSS_I("chip port %d, dev10 %d", port, VTSS_TO_DEV(port));
            JR2_WRM(VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV(port)),
                    VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM(domain),
                    VTSS_M_DEV10G_DEV_CFG_STATUS_PTP_CFG_PTP_DOM);
            break;

        default:
            VTSS_E("unsupported interface: %u", interface);
            return VTSS_RC_ERROR;
    }
    // enable central counters in DEVCPU
    JR2_WRM(VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG,
            VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA(1<<domain),
            VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA(1<<domain));

    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_internal_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    switch (fmt) {
    case TS_INTERNAL_FMT_NONE:
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

static vtss_rc jr2_ts_timestamp_get(vtss_state_t *vtss_state)
{
    u32  value;
    u32  delay;
    u32  tx_port;
    u32  mess_id;
    BOOL overflow = FALSE;

    JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
    while (VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(value)) {
        /* Read TX timestamp */
        if (!VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("TX timestamp expected but RX timestamp found");
            JR2_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP, &delay);
        tx_port = vtss_api_port(vtss_state, VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_PORT(value));

        /* Read RX timestamp */
        JR2_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
        if (!VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_VLD(value) ||
            VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_STAMP_TX(value)) {
            VTSS_E("RX timestamp not found");
            JR2_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
            JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= VTSS_X_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_OVFL(value);
        JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP, &mess_id);

        if (mess_id >= VTSS_TS_ID_SIZE) {
            VTSS_D("skip mess_id %u", mess_id);
        } else if (tx_port < VTSS_PORT_ARRAY_SIZE) {
            vtss_state->ts.status[mess_id].tx_tc[tx_port] = (u64)delay << 16; // 0-15 bits are meant for fractional nano seconds.
            vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
            vtss_state->ts.status[mess_id].valid_mask |= 1LL<<tx_port;
        } else {
            VTSS_E("invalid port (%u)", tx_port);
        }

        VTSS_D("value %x, delay %u, tx_port %u, mess_id %u", value, delay, tx_port, mess_id);
        JR2_WR(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, VTSS_F_REW_PTP_CTRL_PTP_TWOSTEP_CTRL_PTP_NXT(1));
        JR2_RD(VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, &value);
    }
    if (overflow) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}

/*
* Signal port status change (used to detect and compensate for the internal ingress and egress latencies)
*/
static vtss_rc jr2_ts_status_change(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc               rc = VTSS_RC_OK, rc2;
    i32                   rx_delay = 0, tx_delay = 0;
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SERVAL_T)
    vtss_port_interface_t interface = vtss_state->port.conf[port_no].if_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   value;
#endif /* VTSS_ARCH_JAGUAR_2_B/SERVAL_T */
    VTSS_D("port status change. port %d  interface %u", port_no, interface);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return rc;
    }

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
    /* I/O delays taken from DSH1061 section 2.31.9 */
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_QSGMII) {
        interface = VTSS_PORT_INTERFACE_QSGMII;
    } else if (interface == VTSS_PORT_INTERFACE_SGMII_2G5) {
        if (vtss_state->port.conf[port_no].speed == VTSS_SPEED_2500M) {
            interface = VTSS_PORT_INTERFACE_VAUI;
        }
    }
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
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
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
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
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 32 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value) / 10;
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
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
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
        JR2_RD(VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_STAT(port / 4), &value);
        rx_delay += 2 * VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_DELAY_VAR_X200PS(value);
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
        JR2_RD(VTSS_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_DESKEW_STATUS(VTSS_TO_DEV(port)), &value);
        rx_delay += 32 * (VTSS_X_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_DESKEW_STATUS_LANE_DESKEW_DELAY(value) % 16);
        JR2_RD(VTSS_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_CGALIGN_STATUS(VTSS_TO_DEV(port)), &value);
        rx_delay += 32 * (VTSS_X_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_CGALIGN_STATUS_LANE_CGALIGN_DELAY(value) % 32) / 10;
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
        JR2_RD(VTSS_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_DESKEW_STATUS(VTSS_TO_DEV(port)), &value);
        rx_delay += 32 * (VTSS_X_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_DESKEW_STATUS_LANE_DESKEW_DELAY(value) % 16);
        JR2_RD(VTSS_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_CGALIGN_STATUS(VTSS_TO_DEV(port)), &value);
        rx_delay += 16 * (VTSS_X_DEV10G_PCS_XAUI_STATUS_PCS_XAUI_CGALIGN_STATUS_LANE_CGALIGN_DELAY(value) % 32) / 10;
        break;

    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    /* Add additional delays found in testing */
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
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
    case VTSS_PORT_INTERFACE_SFI:
        /* 10G */
        rx_delay += 60;
        tx_delay += 60;
        break;
    default:
        /* No additional delays */
        break;
    }
#endif /* VTSS_ARCH_JAGUAR_2_B */

#if defined(VTSS_ARCH_SERVAL_T)
    /* I/O delays taken from DSH1064 section 2.32.9 (@156.25MHz) */
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
        /* Internal Copper PHY */
        switch (vtss_state->port.conf[port_no].speed) {
        case VTSS_SPEED_10M:
            JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(3) |
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG(0x30));
            break;
        case VTSS_SPEED_100M:
            JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(2) |
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG(0x0E));
            break;
        case VTSS_SPEED_1G:
            JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(1) |
                   VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHY_PREDICT_CFG(0x01));
            break;
        default:
            VTSS_E("unsupported speed: %u", vtss_state->port.conf[port_no].speed);
            return VTSS_RC_ERROR;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII_2G5:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
        /* SerDes 1G */
        if (port <= 4) {
            rx_delay = 432;
            tx_delay = 447;
        } else if (port >= 5 && port <= 6) {
            rx_delay = 517;
            tx_delay = 439;
        } else if (port >= 7 && port <= 10) {
            rx_delay = 955;
            tx_delay = 768;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
        JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
               VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(1));
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* SerDes 2.5G */
        if (port >= 5 && port <= 6) {
            rx_delay = 220;
            tx_delay = 141;
        } else if (port >= 7 && port <= 8) {
            rx_delay = 405;
            tx_delay = 294;
        } else if (port >= 9 && port <= 10) {
            rx_delay = 399;
            tx_delay = 292;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 32 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value) / 10;
        JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
               VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(5));
        break;
    case VTSS_PORT_INTERFACE_100FX:
        /* SerDes 100M */
        if (port <= 4) {
            rx_delay = 693;
            tx_delay = 795;
        } else if (port >= 5 && port <= 6) {
            rx_delay = 782;
            tx_delay = 808;
        } else if (port >= 7 && port <= 10) {
            rx_delay = 1237;
            tx_delay = 1131;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        JR2_RD(VTSS_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV1G(port)), &value);
        rx_delay += 8 * VTSS_X_DEV1G_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
        JR2_WR(VTSS_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV1G(port)),
               VTSS_F_DEV1G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(1));
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* SerDes 10G */
        if (port >= 9 && port <= 10) {
            rx_delay = 1118;
            tx_delay = 1621;
        } else {
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
        }
        JR2_WR(VTSS_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG(VTSS_TO_DEV(port)),
               VTSS_F_DEV10G_DEV_CFG_STATUS_PTP_PREEDICT_CFG_PTP_PHASE_PREDICT_CFG(4));
        break;
    case VTSS_PORT_INTERFACE_NO_CONNECTION:
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    /* Add additional delays found in testing */
    switch (interface) {
    case VTSS_PORT_INTERFACE_SGMII:
        /* Internal Copper PHY */
        switch (vtss_state->port.conf[port_no].speed) {
            case VTSS_SPEED_10M:
//                rx_delay += 46290; // these big numbers are not supported
//                tx_delay += 58410; // these big numbers are not supported
                break;
            case VTSS_SPEED_100M:
//                rx_delay += 3300;
                tx_delay += 5110;// + 3300; //511 ns is the max possible value
                break;
            case VTSS_SPEED_1G:
                rx_delay += 2020 + 320;
                tx_delay += 1390 - 240;
                break;
        default:
            /* No additional delays */
            break;
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        /* SerDes 1G */
        if (port <= 4) {
            rx_delay += 110;
            tx_delay += 260;
        } else if (port >= 5 && port <= 6) {
            rx_delay += 160;
            tx_delay += 260;
        } else if (port >= 7 && port <= 10) {
            tx_delay += 310;
        }
        break;
    case VTSS_PORT_INTERFACE_VAUI:
        /* SerDes 2.5G */
        if (port >= 5 && port <= 6) {
            rx_delay += 90;
            tx_delay += 90;
        } else if (port >= 7 && port <= 10) {
            rx_delay += 50;
            tx_delay += 50;
        }
        break;
    case VTSS_PORT_INTERFACE_100FX:
        /* SerDes 100M */
        if (port <= 4) {
            rx_delay += 230;
            tx_delay += 230;
        } else if (port >= 5 && port <= 6) {
            rx_delay += 220;
            tx_delay += 220;
        } else if (port >= 7 && port <= 10) {
            rx_delay += 200;
            tx_delay += 200;
        }
        break;
    case VTSS_PORT_INTERFACE_SFI:
        /* SerDes 10G */
        if (port >= 9 && port <= 10) {
            rx_delay += 120;
        }
        break;

    default:
        /* No additional delays */
        break;
    }
#endif /* VTSS_ARCH_SERVAL_T */

    rx_delay = (rx_delay + 5) / 10;
    tx_delay = (tx_delay + 5) / 10;
    vtss_state->ts.port_conf[port_no].default_igr_latency = rx_delay;
    vtss_state->ts.port_conf[port_no].default_egr_latency = tx_delay;
    VTSS_D("port_no %d, igr_latency %d, egr_latency %d", port_no, rx_delay, tx_delay);
    rc = jr2_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = jr2_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

static vtss_rc
jr2_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_external_io_mode_set(vtss_state_t *vtss_state, u32 io)
{
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];

    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    /* Set gpio mode */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_IN);
    } else {
        (void) vtss_jr2_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
    }
    /* Set pin configuration */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        u32 dividers = HW_NS_PR_SEC/ext_io_mode->freq;
        u32 high_div = dividers/2;
        u32 low_div  = (dividers+1)/2;
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(io),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        JR2_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);     /* TBD_henrikb Why is this register write to EXT_CLK_PIN? Should it have been 'io' as all other operations in this function. */
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else {
        VTSS_E("invalid pin cfg: %u", ext_io_mode->pin);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc jr2_ts_saved_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    vtss_rc rc ;
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    rc = jr2_ts_io_pin_timeofday_get(vtss_state, io, ts, tc);
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        JR2_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    }
    return rc;
}

#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
static vtss_rc jr2_autoresp_dom_cfg_set(vtss_state_t *vtss_state, u8      domain)
{
    vtss_ts_autoresp_dom_cfg_t *cfg;
    if (domain < VTSS_TS_DOMAIN_ARRAY_SIZE) {
        cfg = &vtss_state->ts.auto_resp_cfg[domain];
        u32 msb = (cfg->clock_identity[0]<<24) + (cfg->clock_identity[1]<<16) + (cfg->clock_identity[2]<<8) + (cfg->clock_identity[3]);
        u32 lsb = (cfg->clock_identity[4]<<24) + (cfg->clock_identity[5]<<16) + (cfg->clock_identity[6]<<8) + (cfg->clock_identity[7]);
        JR2_WR(VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB(domain),
               VTSS_F_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB_CLOCK_ID_MSB(msb));
        JR2_WR(VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB(domain),
               VTSS_F_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB_CLOCK_ID_LSB(lsb));
        JR2_WR(VTSS_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG(domain),
               VTSS_F_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM_SEL(cfg->ptp_port_individual)  |
               VTSS_F_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG_PORT_NUM(cfg->ptp_port_msb));
        JR2_WR(VTSS_ANA_ACL_PTP_DOM_PTP_MISC_CFG(domain),
               VTSS_F_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD_MASK(cfg->flag_field_update.mask)  |
               VTSS_F_ANA_ACL_PTP_DOM_PTP_MISC_CFG_FLAG_FIELD(cfg->flag_field_update.value));
        return VTSS_RC_OK;
    } else {
        return VTSS_RC_ERROR;
    }

}

static vtss_rc jr2_ts_smac_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32                   port = VTSS_CHIP_PORT(port_no);
    //Set up pr port Source Mac address
    vtss_mac_t smac = vtss_state->ts.port_conf[port_no].smac;
    u32 smac_high = (smac.addr[0]<<8) + (smac.addr[1]);
    u32 smac_low = (smac.addr[2]<<24) + (smac.addr[3]<<16) + (smac.addr[4]<<8) + (smac.addr[5]);
    JR2_WR(VTSS_REW_PORT_PTP_SMAC_LOW(port),
           VTSS_F_REW_PORT_PTP_SMAC_LOW_PTP_SMAC_LOW(smac_low));
    JR2_WR(VTSS_REW_PORT_PTP_SMAC_HIGH(port),
           VTSS_F_REW_PORT_PTP_SMAC_HIGH_PTP_SMAC_HIGH(smac_high));
    return VTSS_RC_OK;
}
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)

static vtss_rc jr2_ts_seq_cnt_get(vtss_state_t *vtss_state,
                         u32                   sec_cntr,
                         u16 *const            cnt_val)
{
    vtss_rc rc = VTSS_RC_OK;
    u32 value;
    if (sec_cntr <= 255) {
        // read sec counter REW:PTP_SEQ_NO:PTP_SEQ_NO[0-255].PTP_SEQ_NO
        JR2_RD(VTSS_REW_PTP_SEQ_NO_PTP_SEQ_NO(sec_cntr), &value);
        *cnt_val = VTSS_X_REW_PTP_SEQ_NO_PTP_SEQ_NO_PTP_SEQ_NO(value);
    } else {
        VTSS_E("Invalid sequence counter number %d", sec_cntr);
        rc = VTSS_RC_ERROR;
    }
    return rc;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc jr2_debug_ts(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    u32            port;
    vtss_port_no_t port_no;
    char           buf[64];
    int            idx;

    /* REW:PORT */
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "REW:PORT[%u]", port);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_MODE_CFG(port, 0), "PTP_MODE_CFG[0]");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_MODE_CFG(port, 1), "PTP_MODE_CFG[1]");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_EDLY_CFG(port), "PTP_EDLY_CFG");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_IDLY1_CFG(port), "PTP_IDLY1_CFG");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_IDLY2_CFG(port), "PTP_IDLY2_CFG");
    }

    /* REW:PTP_CTRL */
    vtss_jr2_debug_reg_header(pr, "REW:PTP_CTRL");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PTP_CTRL_PTP_TWOSTEP_CTRL, "PTP_TWOSTEP_CTRL");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_REW_PTP_CTRL_PTP_TWOSTEP_STAMP, "PTP_TWOSTEP_STAMP");

    /* DEVCPU_PTP:PTP_CFG */
    vtss_jr2_debug_reg_header(pr, "DEVCPU_PTP:PTP_CFG");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG, "PTP_MISC_CFG");

    /* ANA_ACL::PTP_MISC_CTRL */
    vtss_jr2_debug_reg_header(pr, "ANA_ACL::PTP_MISC_CTRL");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL, "PTP_MISC_CTRL");

    for (idx = 0; idx <= 2; idx++) {
        VTSS_SPRINTF(buf, "CLK_ADJ_CFG[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG(idx), buf);
    }
    for (idx = 0; idx <= 2; idx++) {
        VTSS_SPRINTF(buf, "CLK_ADJ_FRQ[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ(idx), buf);
    }
    for (idx = 0; idx <= 2; idx++) {
        VTSS_SPRINTF(buf, "DOM_PTP_CLOCK_ID_MSB[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_MSB(idx), buf);
        VTSS_SPRINTF(buf, "DOM_PTP_CLOCK_ID_LSB[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_DOM_PTP_CLOCK_ID_LSB(idx), buf);
        VTSS_SPRINTF(buf, "DOM_PTP_SRC_PORT_CFG[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_DOM_PTP_SRC_PORT_CFG(idx), buf);
        VTSS_SPRINTF(buf, "PTP_DOM_PTP_MISC_CFG[%u]", idx);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_ANA_ACL_PTP_DOM_PTP_MISC_CFG(idx), buf);
    }

    vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, "PTP_PIN_INTR");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA, "PTP_PIN_INTR_ENA");
    vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_INTR_IDENT, "PTP_PIN_INTR_IDENT");

    /* DEVCPU_PTP:PTP_PINS */
    for (idx = 0; idx <= 3; idx++) {
        VTSS_SPRINTF(buf, "DEVCPU_PTP:PTP_PINS[%u]", idx);
        vtss_jr2_debug_reg_header(pr, buf);
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(idx), "PTP_PIN_CFG");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(idx), "PTP_TOD_SEC_MSB");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(idx), "PTP_TOD_SEC_LSB");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(idx), "PTP_TOD_NSEC");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_NSF(idx), "PTP_NSF");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(idx), "PIN_WF_HIGH_PERIOD");
        vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(idx), "PIN_WF_LOW_PERIOD");
    }

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
            VTSS_SPRINTF(buf, "DEV1G (port_no %u):DEV_CFG_STATUS", port_no);
            vtss_jr2_debug_reg_header(pr, buf);
            vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEV1G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV1G(port)), "PTP_CFG");
            break;
        case VTSS_PORT_INTERFACE_SFI:
        case VTSS_PORT_INTERFACE_XAUI:
        case VTSS_PORT_INTERFACE_RXAUI:
            VTSS_SPRINTF(buf, "DEV10G (port_no %u):DEV_CFG_STATUS", port_no);
            vtss_jr2_debug_reg_header(pr, buf);
            vtss_jr2_debug_reg(vtss_state, pr, VTSS_DEV10G_DEV_CFG_STATUS_PTP_CFG(VTSS_TO_DEV(port)), "PTP_CFG");
            break;
        default:
            break;
        }
    }

    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_ts_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, jr2_debug_ts, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc jr2_ts_init(vtss_state_t *vtss_state)
{
    u32 clk_cfg, clk_pr_ns, clk_pr_100ps;

    /* Enable PTP (all 3 domains)*/
    JR2_WR(VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG, VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA(7));
    /* Enable PTP Delay_Req/resp processing, use default values for other bits */
    JR2_WRM(VTSS_ANA_ACL_VCAP_S2_PTP_MISC_CTRL,
            VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA(1) | VTSS_F_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52(0),
            VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_ALLOW_ACL_REW_ENA | VTSS_M_ANA_ACL_VCAP_S2_PTP_MISC_CTRL_PTP_DELAY_REQ_UDP_LEN52);
    JR2_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG, &clk_cfg);
    // the clock period is read back from the chip, and the clk_set_trunc is calculated as a multiplum of the clock period multiplied with the lowest number that results in an integer number of ns.
    clk_pr_ns = VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_NS(clk_cfg);
    clk_pr_100ps = VTSS_X_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG_PTP_SYS_CLK_PER_PS100(clk_cfg);
    vtss_state->ts.conf.clk_set_trunc = 10 * clk_pr_ns  +  clk_pr_100ps;
    while ((vtss_state->ts.conf.clk_set_trunc % 10) != 0) {
        vtss_state->ts.conf.clk_set_trunc += 10 * clk_pr_ns  +  clk_pr_100ps;
    }
    vtss_state->ts.conf.clk_set_trunc = vtss_state->ts.conf.clk_set_trunc / 10;
    VTSS_D("PTP clock period %u.%u => clk_set_trunc %u", clk_pr_ns, clk_pr_100ps, vtss_state->ts.conf.clk_set_trunc);
    return VTSS_RC_OK;
}

vtss_rc vtss_jr2_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;
    u32             port_no, port;
    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = jr2_ts_timeofday_get;
        state->domain_timeofday_get = jr2_ts_domain_timeofday_get;
        state->timeofday_set = jr2_ts_timeofday_set;
        state->domain_timeofday_set = jr2_ts_domain_timeofday_set;
        state->timeofday_set_delta = jr2_ts_timeofday_set_delta;
        state->domain_timeofday_set_delta = jr2_ts_domain_timeofday_set_delta;
        state->timeofday_next_pps_get = jr2_ts_timeofday_next_pps_get;
        state->timeofday_prev_pps_get = jr2_ts_timeofday_prev_pps_get;
        state->domain_timeofday_next_pps_get = jr2_ts_domain_timeofday_next_pps_get;
        state->timeofday_offset_set = jr2_ts_timeofday_offset_set;
        state->domain_timeofday_offset_set = jr2_ts_domain_timeofday_offset_set;
        state->adjtimer_set = jr2_ts_adjtimer_set;
        state->domain_adjtimer_set = jr2_ts_domain_adjtimer_set;
        state->timeofday_one_sec = jr2_ts_timeofday_sample;
        state->external_clock_mode_set = jr2_ts_external_clock_mode_set;
        state->alt_clock_saved_get = jr2_ts_alt_clock_saved_get;
        state->alt_clock_mode_set = jr2_ts_alt_clock_mode_set;
        state->timeofday_next_pps_set = jr2_ts_timeofday_next_pps_set;
        state->ingress_latency_set = jr2_ts_ingress_latency_set;
        state->p2p_delay_set = jr2_ts_p2p_delay_set;
        state->egress_latency_set = jr2_ts_egress_latency_set;
        state->delay_asymmetry_set = jr2_ts_delay_asymmetry_set;
        state->operation_mode_set = jr2_ts_operation_mode_set;
        state->internal_mode_set = jr2_ts_internal_mode_set;
        state->timestamp_get = jr2_ts_timestamp_get;
        state->status_change = jr2_ts_status_change;
        state->timestamp_id_release = jr2_ts_timestamp_id_release;
        state->external_io_mode_set = jr2_ts_external_io_mode_set;
        state->saved_timeofday_get = jr2_ts_saved_timeofday_get;
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        state->autoresp_cfg_set = jr2_autoresp_dom_cfg_set;
        state->smac_set = jr2_ts_smac_set;
#endif //defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        state->seq_cnt_get = jr2_ts_seq_cnt_get;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(jr2_ts_init(vtss_state));
        break;
    case VTSS_INIT_CMD_PORT_MAP:
        /* Initialize the PTP Port ID port number. This is done anyway in the jr2_ts_operation_mode_set() function but this is only called from AIL in case of changes in mode or domain. */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            port = VTSS_CHIP_PORT(port_no);
            JR2_WRM(VTSS_ANA_ACL_PORT_PTP_CFG(port), VTSS_F_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM(port_no+1), VTSS_M_ANA_ACL_PORT_PTP_CFG_PTP_PORT_NUM);
        }
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_JAGUAR_2 */
