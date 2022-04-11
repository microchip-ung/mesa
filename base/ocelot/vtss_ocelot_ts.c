// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_ocelot_cil.h"

#if defined(VTSS_ARCH_OCELOT)

#if defined(VTSS_FEATURE_TIMESTAMP)

/* - CIL functions ------------------------------------------------- */

#define HW_NS_PR_SEC 1000000000L
#define HW_CLK_CNT_PR_SEC 156250000L
#define HW_CLK_50_MS (HW_NS_PR_SEC/20)
#define HW_CLK_M950_MS (-HW_NS_PR_SEC + HW_CLK_50_MS)
#define EXT_SYNC_INPUT_LATCH_LATENCY 5 //(1*HW_NS_PR_SEC/HW_CLK_CNT_PR_SEC)  /* 1 clock cycle added to EXT_SYNC_CURRENT TIME */
#define ADJ_UNITS_PR_NS 10

#define HW_PS_PR_SEC 1000000000000LL
#define HW_PS_PR_NS  1000
#define PPS_WIDTH 200 /* Width of 1PPS pulse in ns */

/* Actions on PTP pins */
#define PTP_PIN_ACTION_IDLE  0
#define PTP_PIN_ACTION_LOAD  1
#define PTP_PIN_ACTION_SAVE  2
#define PTP_PIN_ACTION_CLOCK 3
#define PTP_PIN_ACTION_DELTA 4
#define PTP_PIN_ACTION_NOSYNC 0
#define PTP_PIN_ACTION_SYNC 1

#define OCELOT_PTP_PIN_ACTION(pin, act, sync, dom)                        \
SRVL_WRM(VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(pin),                     \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION(act) |   \
         (sync ? VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_SYNC : 0) |    \
         0,       \
         VTSS_M_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION |        \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_SYNC |          \
         VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_DOM);           \

/* No timestamper skew in Ocelot */
#define TIMESTAMPER_SKEW 0

/* Ocelot GPIO configuration */
static const u8 ptp_gpio[VTSS_TS_IO_ARRAY_SIZE] = {
    18, /* PTP_0 */
    19, /* PTP_1 */
    10, /* PTP_2 */
    11  /* PTP_3 */
};

static vtss_rc ocelot_ts_io_pin_timeofday_get_no_action(vtss_state_t *vtss_state, vtss_timestamp_t *ts, int io_pin)
{
    u32 value;
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(io_pin), &value);
    ts->sec_msb = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(value);
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(io_pin), &ts->seconds);
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(io_pin), &value);
    ts->nanoseconds = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(value);
    if (ts->nanoseconds >= 0x3ffffff0 && ts->nanoseconds <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds = 999999984 + (ts->nanoseconds & 0xf);
    }
    ts->nanosecondsfrac = 0;
    return VTSS_RC_OK;
}

static vtss_rc ocelot_ts_io_pin_timeofday_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts, int io_pin)
{
    OCELOT_PTP_PIN_ACTION(io_pin, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, 0);
    return ocelot_ts_io_pin_timeofday_get_no_action(vtss_state, ts, io_pin);
}

static vtss_rc ocelot_ts_io_pin_timeofday_sec_get(vtss_state_t *vtss_state, u32 *sec)
{
    OCELOT_PTP_PIN_ACTION(TOD_ACC_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, 0);
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(TOD_ACC_PIN), sec);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_timeofday_read(vtss_state_t *vtss_state, vtss_timestamp_t *ts, u64 *tc)
{
    vtss_rc rc;
    VTSS_D("Read timeofday via io-pin %d", TOD_ACC_PIN);
    rc = ocelot_ts_io_pin_timeofday_get(vtss_state, ts, TOD_ACC_PIN);
    *tc = ts->nanoseconds + (u64)ts->seconds*VTSS_ONE_MIA;
    /* tc is returned as 16 bit fraction of nanoseconds */
    *tc = *tc << 16;
    return rc;
}

static vtss_rc srvl_ts_timeofday_get(vtss_state_t     *vtss_state,
                                     vtss_timestamp_t *ts,
                                     u64              *tc)
{
    VTSS_RC(srvl_ts_timeofday_read(vtss_state, ts, tc));
    VTSS_D("ts->seconds: %u, ts->nanoseconds: %u, tc %" PRIu64 "", ts->seconds, ts->nanoseconds, *tc);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_timeofday_next_pps_get(vtss_state_t *vtss_state,
                                              vtss_timestamp_t *ts)
{
    u64 tc;
    VTSS_RC(srvl_ts_timeofday_read(vtss_state, ts, &tc));
    ++ts->seconds; /* sec counter is maintained in SW */
    ts->nanoseconds = 0;
    VTSS_D("ts->seconds: %u, ts->nanoseconds: %u", ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_timeofday_prev_pps_get(vtss_state_t *vtss_state,
        vtss_timestamp_t *ts)
{
    u64 tc;
    VTSS_RC(srvl_ts_timeofday_read(vtss_state, ts, &tc));
    ts->nanoseconds = 0;
    VTSS_D("ts->seconds: %u, ts->nanoseconds: %u", ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}


/*
 * Subtract the offset from the actual time. 
 * offset is in the range [-1..+1] sec.
 * alignment algorithm:
 *  offset > 50 ms => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds
 *    (TBD if this works, because the ADJ is < actual TOD_NANOSECS ??)
 *  50 ms > offset > -950 ms => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds + 1 sec
 *  -950 ms > offset => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds + 2 sec
 * The second offset is adjusted accordingly.
 *
 * In serval the ts_conf.sec_offset is only used for time adjustment. i.e if sec_offset != 0 
 *   then the sec counter is adjusted in the next onesec call: 
 *     1 => sec counter is incremented;
 *     2 => sec counter is decremented.
 */
static vtss_rc srvl_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    /* must be in IDLE mode before the time can be loaded */
    OCELOT_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(-offset));
    OCELOT_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, 0);
    VTSS_D("offset: %d", offset);
    return VTSS_RC_OK;
}
/*
 * When the time is set, the HW sec  counters are written. The HW clock is adjusted so that the timestamp nanoseconds
 * and the hw nanoseconds counters are aligned. This cannot be done with nanosecond precision, so the final alignment
 * is done by the clock rate adjustment. The hw nanoseconds counter is aligned by setting the
 * PTP_UPPER_LIMIT_1_TIME_ADJ. This register sets the next onesec period to [0.. 1.073.741.823] nanosec. 
 * A value of 0 makes no sense as this means two clock pulses with no time distance, therefore the algorithm sets the
 * period in the range [0,050..1,050] Sec.
 */
static vtss_rc srvl_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    //truncate nanosec value
    u32 ns = (ts->nanoseconds / vtss_state->ts.conf.clk_set_trunc) * vtss_state->ts.conf.clk_set_trunc;
    /* must be in IDLE mode before the time can be loaded */
    OCELOT_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(TOD_ACC_PIN), ts->seconds);
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(TOD_ACC_PIN),
           VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(ns));
    OCELOT_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, 0);
    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    VTSS_D("truncated ns: %u", ns);
    return VTSS_RC_OK;
}

/*
 * When the time is set, the HW sec  counters are written. The HW clock is adjusted so that the timestamp nanoseconds
 * and the hw nanoseconds counters are aligned. This cannot be done with nanosecond precision, so the final alignment
 * is done by the clock rate adjustment. The hw nanoseconds counter is aligned by setting the
 * PTP_UPPER_LIMIT_1_TIME_ADJ. This register sets the next onesec period to [0.. 1.073.741.823] nanosec. 
 * A value of 0 makes no sense as this means two clock pulses with no time distance, therefore the algorithm sets the
 * period in the range [0,050..1,050] Sec.
 */
static vtss_rc srvl_ts_timeofday_set_delta(vtss_state_t *vtss_state,
                                           const vtss_timestamp_t *ts, BOOL negative)
{
    vtss_rc rc = VTSS_RC_OK;
    if (ts->seconds > 0 || ts->sec_msb > 0 || ts->nanoseconds > HW_NS_PR_SEC/2) {
        vtss_timestamp_t ts_prev;
        u64              tc;

        /* Read current time */
        VTSS_RC(srvl_ts_timeofday_read(vtss_state, &ts_prev, &tc));

        /* Calculate new time */
        if (negative){
            VTSS_RC(vtss_timestampSub(&ts_prev, ts));
        } else {
            VTSS_RC(vtss_timestampAdd(&ts_prev, ts));
        }
        rc = srvl_ts_timeofday_set(vtss_state, &ts_prev);

    } else {
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(TOD_ACC_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(negative ? -(i32)ts->nanoseconds : ts->nanoseconds));
        OCELOT_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, 0);
    }

    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return rc;
}

/*
 * This function is called from interrupt, therefore the macros using vtss_state cannot be used.
 */
static u32 srvl_ts_ns_cnt_get(vtss_inst_t inst)
{
    u32 tmp;
    /* this code is a copy of the OCELOT_PTP_PIN_ACTION macro , but without using the register MACROS */
    (void)inst->init_conf.reg_read(0, VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(TOD_ACC_PIN), &tmp);
    tmp = tmp & ~(VTSS_M_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION |  VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_SYNC | VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_DOM);
    tmp |= VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG_PTP_PIN_ACTION(PTP_PIN_ACTION_SAVE);
    (void)inst->init_conf.reg_write(0, VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(TOD_ACC_PIN), tmp);

    /* Read the NSF register without using the register MACROS */
    (void)inst->init_conf.reg_read(0, VTSS_DEVCPU_PTP_PTP_PINS_PTP_NSF(TOD_ACC_PIN), &tmp);

    VTSS_D("Read ts_counter %u", tmp);
    return tmp;
}

static vtss_rc srvl_ts_timeofday_one_sec(vtss_state_t *vtss_state)
{
    /* nothing to do in ocelot */
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    i32 adj;
    adj = vtss_state->ts.conf.adj[0];

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
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ,
                   (adj_unit ? VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ_UNIT : 0) |
                   VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ_CLK_ADJ(adj_val));
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG,
                   (adj_dir ? VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_DIR : 0) |
                   VTSS_F_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_ENA);
        }
    }
    if (adj == 0) {
        /* Disable adjustment */
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG, 0);
    }
    VTSS_I("adj: %d", adj);
    return VTSS_RC_OK;
}

/* This function assumes that instance 0 of the EXT_SYNC_CURRENT_TIME_STAT is used*/
static vtss_rc srvl_ts_freq_offset_get(vtss_state_t *vtss_state, i32 *const adj)
{
    VTSS_E("Not implemented");
    return VTSS_RC_OK;
}

/* Set the clock mode for either idx 0 (GPIO pin 30,31) or idx 1 (GPIO pin 15,16) */
/* idx 0 = the alternative clock instance (PPS0), on the Ref board called RS422_1PPS
 * idx 1 = the default clock instance (PPS1), on the Ref board called SyncE1PPS, and also connected to the Tesla PHY's
 */
static vtss_rc srvl_ts_external_clock_mode_set(vtss_state_t *vtss_state, int idx)
{
    vtss_ts_ext_clock_mode_t *ext_clock_mode = &vtss_state->ts.conf.ext_clock_mode;
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    VTSS_I("one_pps_mode: %u, enable: %u, freq: %u", ext_clock_mode->one_pps_mode, ext_clock_mode->enable, ext_clock_mode->freq);
    // Alt clock mode overrules the external clock output in Ocelot
    if (!alt_clock_mode->one_pps_out) {

        OCELOT_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
        if (ext_clock_mode->enable) {
            u32 dividers = HW_NS_PR_SEC/ext_clock_mode->freq;
            u32 high_div = dividers/2;
            u32 low_div  = (dividers+1)/2;
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_PPS_PIN),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_PPS_PIN),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));

            (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
            OCELOT_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, 0);

        } else if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
            (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[EXT_PPS_PIN], VTSS_GPIO_ALT_0);
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_PPS_PIN),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_PPS_PIN), 0);
            OCELOT_PTP_PIN_ACTION (EXT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);

            // on ocelot both EXT_PPS_PIN and EXT_CLK_PIN are used as 1PPS output
            (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
                    VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
            SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);
            OCELOT_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
        }
    }
    if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_INPUT) {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

/* Get the saved nanosec conuter from counter */
static vtss_rc srvl_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
{
    u32 nsec;
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(ALT_LDST_PIN), &nsec);
    nsec = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(nsec);
    if (nsec >= 0x3ffffff0 && nsec <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        nsec = 999999984 + (nsec & 0xf);
    }
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
        } else if (alt_clock_mode->save) {
            OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        }
    }
    *saved = (u64)nsec << 16;
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_alt_clock_saved_timeofday_get(vtss_state_t *vtss_state,
                                                     vtss_timestamp_t  *ts)
{
    vtss_rc rc ;
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;
    rc = ocelot_ts_io_pin_timeofday_get_no_action(vtss_state, ts, ALT_LDST_PIN);
    VTSS_D("io pin %d, sec %d, nanosec %d", ALT_LDST_PIN, ts->seconds, ts->nanoseconds);
    if (alt_clock_mode->save) {
        OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
    }
    return rc;
}

/* Set the clock mode for external clock idx 0 (GPIO pin 30,31) */
/* idx 0 = the alternative clock instance (PPS0), on the Ref board called RS422_1PPS
 * the modes are: 
 *    BOOL one_pps_out;        Enable 1pps output
 *    BOOL one_pps_in;         Enable 1pps input
 *    BOOL save;               Save actual time counter at next 1 PPS input
 *    BOOL load;               Load actual time counter at next 1 PPS input
 * Register setting in PTP_MISC_CFG:
 *                     one_pps_out | one_pps_in |   save   |   load
 *                        T    F   |   T    F   |  T    F  |  T    F  |
 * EXT_SYNC_OUTP_SEL      1    0
 * EXT_SYNC_OUTP_ENA      1    0
 * EXT_SYNC_INP_ENA                    1    0
 * EXT_SYNC_CAP_ENA                                1    0
 * EXT_SYNC_ENA                                               1    0
 */
static vtss_rc srvl_ts_alt_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    if (alt_clock_mode->one_pps_out) {
        OCELOT_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(ALT_PPS_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(ALT_PPS_PIN), 0);

        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN], VTSS_GPIO_ALT_0);
        OCELOT_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    }

    OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
            return VTSS_RC_ERROR;
        } else if (alt_clock_mode->save) {
            (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_ALT_0);
            OCELOT_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        }
    } else {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN], VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

/* Set the time to be loaded into the Serval timer at the next 1PPS
 * It is assumed that this function is called at the beginning of a sec */
static vtss_rc srvl_ts_timeofday_next_pps_set(vtss_state_t *vtss_state,
                                              const vtss_timestamp_t *const ts)
{
    if (vtss_state->ts.conf.alt_clock_mode.one_pps_in) {
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(ts->sec_msb));
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(ALT_LDST_PIN), ts->seconds-1);
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(ALT_LDST_PIN),
               VTSS_F_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(ts->nanoseconds));
    }

    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 rx_delay = 0;
    if (vtss_state->port.conf[port_no].loop != VTSS_PORT_LOOP_PCS_HOST) {   /* When loop is enabled on the port the latency must be zero */
        rx_delay = VTSS_INTERVAL_NS(conf->ingress_latency);
        rx_delay += -TIMESTAMPER_SKEW + conf->default_igr_latency;
        if ((rx_delay < -TIMESTAMPER_SKEW) || (rx_delay > 0x7fffff)) {
            VTSS_D("Invalid ingress latency %d", rx_delay);
            return VTSS_RC_ERROR;
        }
        /* the RX_PATH_DELAY is added to the rx timestamp, therefore it is -ingress_latency */
        rx_delay = -rx_delay;
    }

    VTSS_D("rx_delay %d", rx_delay);
    VTSS_D("port_no %d, chip port %d", port_no, VTSS_CHIP_PORT(port_no));
    SRVL_WRM(VTSS_DEV_PORT_MODE_RX_PATH_DELAY(VTSS_TO_DEV(VTSS_CHIP_PORT(port_no))),
             VTSS_F_DEV_PORT_MODE_RX_PATH_DELAY_RX_PATH_DELAY(rx_delay),
             VTSS_M_DEV_PORT_MODE_RX_PATH_DELAY_RX_PATH_DELAY);
    VTSS_D("WRM done");
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 p2p_delay = VTSS_INTERVAL_NS(conf->p2p_delay);
    p2p_delay += VTSS_INTERVAL_NS(conf->delay_asymmetry);
    SRVL_WR(VTSS_ANA_PORT_PTP_DLY2_CFG(VTSS_CHIP_PORT(port_no)), 
             p2p_delay);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 tx_delay = 0;
    if (vtss_state->port.conf[port_no].loop != VTSS_PORT_LOOP_PCS_HOST) {   /* When loop is enabled on the port the latency must be zero */
        tx_delay = VTSS_INTERVAL_NS(conf->egress_latency);
        tx_delay += TIMESTAMPER_SKEW + conf->default_egr_latency;
        if ((tx_delay < 0) || (tx_delay > 0x7fffff)) {
            VTSS_D("Invalid egress latency %d", tx_delay);
            return VTSS_RC_ERROR;
        }
    }

    VTSS_D("tx_delay %d", tx_delay);
    SRVL_WRM(VTSS_DEV_PORT_MODE_TX_PATH_DELAY(VTSS_TO_DEV(VTSS_CHIP_PORT(port_no))),
             VTSS_F_DEV_PORT_MODE_TX_PATH_DELAY_TX_PATH_DELAY(tx_delay),
             VTSS_M_DEV_PORT_MODE_TX_PATH_DELAY_TX_PATH_DELAY);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_delay_asymmetry_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 delay = VTSS_INTERVAL_NS(conf->delay_asymmetry);
    /* Used for Ingress asymmetry compensation (Pdelay_Resp) */
    SRVL_WR(VTSS_ANA_PORT_PTP_DLY1_CFG(VTSS_CHIP_PORT(port_no)), 
            delay);
    /* Used for Egress asymmetry compensation (on Delay_Req and Pdelay_Req) */
    SRVL_WR(VTSS_REW_PORT_PTP_DLY1_CFG(VTSS_CHIP_PORT(port_no)), 
            -delay);
    /* Used for Ingress asymmetry compensation (on Sync, therefore include p2p_delay ) */
    delay += VTSS_INTERVAL_NS(conf->p2p_delay);
    SRVL_WR(VTSS_ANA_PORT_PTP_DLY2_CFG(VTSS_CHIP_PORT(port_no)), 
            delay);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_mode_t mode = vtss_state->ts.port_conf[port_no].mode.mode;
    u32 ana_mode = 0;
    u32 rew_mode = 0;
    if (mode == TS_MODE_INTERNAL) {
        ana_mode = VTSS_F_ANA_PORT_PTP_CFG_PTP_BACKPLANE_MODE;
        rew_mode = VTSS_F_REW_PORT_PTP_CFG_PTP_BACKPLANE_MODE;
    }
    SRVL_WRM(VTSS_ANA_PORT_PTP_CFG(VTSS_CHIP_PORT(port_no)),
             ana_mode,
             VTSS_F_ANA_PORT_PTP_CFG_PTP_BACKPLANE_MODE);
    SRVL_WRM(VTSS_REW_PORT_PTP_CFG(VTSS_CHIP_PORT(port_no)), 
             rew_mode, 
             VTSS_F_REW_PORT_PTP_CFG_PTP_BACKPLANE_MODE);
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_internal_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    u32 stamp_wid = 30;
    u32 roll_mode = 0;
    switch (fmt) {
        case TS_INTERNAL_FMT_RESERVED_LEN_30BIT:
            stamp_wid = 30;
            roll_mode = 0;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_32BIT:
            stamp_wid = 32;
            roll_mode = 0;
            break;
        case TS_INTERNAL_FMT_SUB_ADD_LEN_44BIT_CF62:
            stamp_wid = 44;
            roll_mode = 2;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_3_0:
            stamp_wid = 48;
            roll_mode = 0;
            break;
        case TS_INTERNAL_FMT_RESERVED_LEN_48BIT_CF_0:
            stamp_wid = 48;
            roll_mode = 1;
            break;
        default:
            VTSS_E("unsupported internal timestamp format: %u", fmt);
            return VTSS_RC_ERROR;
    }
    VTSS_D("timestamp_width %d, roll_mode %d",stamp_wid, roll_mode);
    if (stamp_wid >=44) {
        vtss_state->ts.add_sub_option = TRUE;
    } else {
        vtss_state->ts.add_sub_option = FALSE;
    }
    SRVL_WRM(VTSS_SYS_PTP_PTP_CFG, 
             VTSS_F_SYS_PTP_PTP_CFG_PTP_STAMP_WID(stamp_wid) | VTSS_F_SYS_PTP_PTP_CFG_PTP_CF_ROLL_MODE(roll_mode), 
             VTSS_M_SYS_PTP_PTP_CFG_PTP_STAMP_WID | VTSS_M_SYS_PTP_PTP_CFG_PTP_CF_ROLL_MODE);
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


static vtss_rc srvl_ts_timestamp_get(vtss_state_t *vtss_state)
{
    u32 value;
    u32 delay;
    u32 tx_port;
    u32 mess_id;
    u32 seq_no;
    u32 sec;
    BOOL overflow = FALSE;
    u32 ts_sec;
    /* PTP_STATUS */
    SRVL_RD(VTSS_SYS_PTP_PTP_STATUS, &value);
    while (value & VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_VLD) {
        overflow |= (value & VTSS_F_SYS_PTP_PTP_STATUS_PTP_OVFL) ? TRUE : FALSE;
        SRVL_RD(VTSS_SYS_PTP_PTP_TXSTAMP, &delay);
        ts_sec = (delay & VTSS_F_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP_SEC) ? 1 : 0;
        delay = VTSS_X_SYS_PTP_PTP_TXSTAMP_PTP_TXSTAMP(delay); /* extract nanoseconds */
        /* Convert the tx timestamp to 32 bit value to make it comparable to the rx timestamp */
        VTSS_RC(ocelot_ts_io_pin_timeofday_sec_get(vtss_state, &sec));
        if ((sec & 0x1) != ts_sec) { // sec has incremented since timestamp was registered
            --sec;
        }
        delay += sec*1000000000L;
        tx_port = api_port(vtss_state, VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(value));
        mess_id = VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_ID(value);
        seq_no  = VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_SEQ_ID(value);
#if defined(VTSS_FEATURE_VOP) && defined(VTSS_FEATURE_TIMESTAMP)
        if (value & VTSS_F_SYS_PTP_PTP_STATUS_PTP_TXSTAMP_OAM) {
            if (mess_id >= VTSS_PATH_SERVICE_VOE_CNT) {
                VTSS_E("invalid mess_id (%u)", mess_id);
            } else {
                VTSS_I("OAM timestamps received:");
                if (++vtss_state->ts.oam_ts_status[mess_id].last >= VTSS_SERVAL_MAX_OAM_ENTRIES) vtss_state->ts.oam_ts_status[mess_id].last = 0;
                vtss_state->ts.oam_ts_status[mess_id].entry[vtss_state->ts.oam_ts_status[mess_id].last].tc = delay;
                vtss_state->ts.oam_ts_status[mess_id].entry[vtss_state->ts.oam_ts_status[mess_id].last].id = mess_id;
                vtss_state->ts.oam_ts_status[mess_id].entry[vtss_state->ts.oam_ts_status[mess_id].last].sq = seq_no;
                vtss_state->ts.oam_ts_status[mess_id].entry[vtss_state->ts.oam_ts_status[mess_id].last].port = tx_port;
                vtss_state->ts.oam_ts_status[mess_id].entry[vtss_state->ts.oam_ts_status[mess_id].last].valid = TRUE;
                VTSS_I(" port %d, id %d, tc %u, sq %u", tx_port, mess_id, delay, seq_no);
            }
        } else
#endif /* VTSS_FEATURE_VOP && VTSS_FEATURE_TIMESTAMP*/
        {
            if (mess_id >= VTSS_TS_ID_SIZE) {
                VTSS_D("invalid mess_id (%u)", mess_id);
            } else {
                if (tx_port < VTSS_PORT_ARRAY_SIZE) {
                    vtss_state->ts.status[mess_id].tx_tc[tx_port] = (u64)delay << 16; /* 0 - 15 bits are meant for fractional nano seconds. */
                    vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
                    vtss_state->ts.status[mess_id].tx_sq[tx_port] = seq_no;
                    vtss_state->ts.status[mess_id].valid_mask |= 1LL<<tx_port;
                } else {
                    VTSS_E("invalid port (%u)", tx_port);
                }
            }
        }
        VTSS_D("value %x, delay %u, tx_port %u, mess_id %u, seq_no %u", value, delay, tx_port, mess_id, seq_no);
        SRVL_WR(VTSS_SYS_PTP_PTP_NXT, VTSS_F_SYS_PTP_PTP_NXT_PTP_NXT);
        SRVL_RD(VTSS_SYS_PTP_PTP_STATUS, &value);
    }
    if (overflow ) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}

static vtss_rc srvl_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    /* Clear bit corresponding to ts_id */
    if (ts_id <TS_IDS_RESERVED_FOR_SW) {
        vtss_state->ts.conf.sw_ts_id_res[ts_id] = 0;
    } else if (ts_id <=31) {
        SRVL_WR(VTSS_ANA_ANA_TABLES_PTP_ID_LOW, VTSS_BIT(ts_id));
    } else if (ts_id <=63) {
        SRVL_WR(VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, VTSS_BIT(ts_id-32));
    } else {
        VTSS_D("invalid ts_id %d", ts_id);
    }
    return VTSS_RC_OK;
}

/*
* Signal port status change (used to detect and compensate for the internal ingress and egress latencies)
*/
static vtss_rc srvl_ts_status_change(vtss_state_t         *vtss_state,
                                     const vtss_port_no_t port_no)
{
    vtss_rc               rc = VTSS_RC_OK, rc2;
    i32                   rx_delay = 0, tx_delay = 0;
    vtss_port_interface_t interface = vtss_state->port.conf[port_no].if_type;
    u32                   port = VTSS_CHIP_PORT(port_no);
    u32                   value;
    VTSS_D("port status change %d", port_no);


    /* I/O delays taken from DSH1064 section 2.32.9 (@156.25MHz) */
    switch (interface) {
        case VTSS_PORT_INTERFACE_SGMII:
            /* Internal Copper PHY */
            switch (vtss_state->port.conf[port_no].speed) {
                case VTSS_SPEED_10M:
                    SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(3) |
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHY_PREDICT_CFG(0x30));
                    break;
                case VTSS_SPEED_100M:
                    SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(2) |
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHY_PREDICT_CFG(0x0E));
                    break;
                case VTSS_SPEED_1G:
                    SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(1) |
                           VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHY_PREDICT_CFG(0x01));
                    break;
                default:
                    VTSS_E("unsupported speed: %u", vtss_state->port.conf[port_no].speed);
                    return VTSS_RC_ERROR;
            }
            break;
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
            SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV(port)), &value);
            rx_delay += 8 * VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
            SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                   VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(1));
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
            SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV(port)), &value);
            rx_delay += 32 * VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value) / 10;
            SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                   VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(5));
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
            SRVL_RD(VTSS_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS(VTSS_TO_DEV(port)), &value);
            rx_delay += 8 * VTSS_X_DEV_PCS1G_CFG_STATUS_PCS1G_LINK_STATUS_DELAY_VAR(value);
            SRVL_WR(VTSS_DEV_PORT_MODE_PTP_PREDICT_CFG(VTSS_TO_DEV(port)),
                   VTSS_F_DEV_PORT_MODE_PTP_PREDICT_CFG_PTP_PHASE_PREDICT_CFG(1));
            break;
        case VTSS_PORT_INTERFACE_SFI:
            VTSS_E("unsupported interface %u on port %u", interface, port);
            return VTSS_RC_ERROR;
            break;
        case VTSS_PORT_INTERFACE_QSGMII:
            SRVL_RD(VTSS_HSIO_HW_CFGSTAT_HW_QSGMII_STAT, &value);
            rx_delay += 2 * VTSS_X_HSIO_HW_CFGSTAT_HW_QSGMII_STAT_DELAY_VAR_X200PS(value);
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
        case VTSS_PORT_INTERFACE_GMII:
            /* Internal Copper PHY */
            switch (vtss_state->port.conf[port_no].speed) {
                case VTSS_SPEED_10M:
                    rx_delay += 16090;
                    tx_delay += 92610;
                    break;
                case VTSS_SPEED_100M:
                    rx_delay += 3300;
                    tx_delay += 5110 + 3300;
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
            /* SerDes 1G */
            if (port <= 4) {
                rx_delay += 110 + 250;
                tx_delay += 260 + 530;
            } else if (port == 6) {
                rx_delay += 160 + 130;
                tx_delay += 260 + 510;
            } else if (port == 9) {
                rx_delay += 160 - 140;
                tx_delay += 260 +150;
            } else if (port == 10 || port == 8) {
                rx_delay -= 40;
                tx_delay += 310 + 160;
            } else {
                rx_delay -= 60;
                tx_delay += 180;
            }
            break;
        case VTSS_PORT_INTERFACE_VAUI:
            /* SerDes 2.5G */
            if (port == 5 || port == 8 || port == 10) {
                rx_delay += 50 - 80;
                tx_delay += 50 + 160;
            }
            break;
        case VTSS_PORT_INTERFACE_100FX:
            /* SerDes 100M */
            if (port <= 4) {
                rx_delay += 230 + 6450;
                tx_delay += 230 + 1050;
            } else if (port == 6) {
                rx_delay += 220 + 6320;
                tx_delay += 220 + 1180;
            } else if (port == 9) {
                rx_delay += 220 + 5900;
                tx_delay += 220 + 900;
            } else if (port == 10) {
                rx_delay += 200 + 5990;
                tx_delay += 200 + 810;
            } else if (port == 8) {
                rx_delay += 200 + 6020;
                tx_delay += 200 + 680;
            } else if (port == 5) {
                rx_delay += 200 + 5970;
                tx_delay += 200 + 850;
            }
            break;

        default:
            /* No additional delays */
            break;
    }

    rx_delay = (rx_delay + 5) / 10;
    tx_delay = (tx_delay + 5) / 10;
    vtss_state->ts.port_conf[port_no].default_igr_latency = rx_delay;
    vtss_state->ts.port_conf[port_no].default_egr_latency = tx_delay;
    VTSS_I("port_no %d, igr_latency %d, egr_latency %d", port_no, rx_delay, tx_delay);
    rc = srvl_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = srvl_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc srvl_debug_ts(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info)
{
    u32  port;
    int  ix;
    char buf[32];

    /* DEVCPU_PTP:PTP_PINS */
    for (ix = 0; ix <= 4; ix++) {
        VTSS_SPRINTF(buf, "DEVCPU_PTP:PTP_PINS[%u]", ix);
        vtss_srvl_debug_reg_header(pr, buf);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_PIN_CFG(ix), "PTP_PIN_CFG");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_MSB(ix), "PTP_TOD_SEC_MSB");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_SEC_LSB(ix), "PTP_TOD_SEC_LSB");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(ix), "PTP_TOD_NSEC");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PTP_NSF(ix), "PTP_NSF");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(ix), "PIN_WF_HIGH_PERIOD");
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(ix), "PIN_WF_LOW_PERIOD");
    }

    /* DEVCPU_PTP: PTP_CFG */
    vtss_srvl_debug_reg_header(pr, "GCB:PTP_CFG");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG, "PTP_MISC_CFG");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_CFG, "CLK_ADJ_CFG");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_CLK_ADJ_FRQ, "CLK_ADJ_FRQ");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR, "PTP_PIN_INTR");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_PIN_INTR_ENA, "PTP_PIN_INTR_ENA");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_INTR_IDENT, "PTP_INTR_IDENT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG, "PTP_SYS_CLK_CFG");
    /* DEVCPU_PTP: PTP_STATUS */
    vtss_srvl_debug_reg_header(pr, "GCB:PTP_STAT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_STATUS_PTP_CUR_NSF, "PTP_STATUS_PTP_CUR_NSF");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_STATUS_PTP_CUR_NSEC, "PTP_STATUS_PTP_CUR_NSEC");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_STATUS_PTP_CUR_SEC_LSB, "PTP_STATUS_PTP_CUR_SEC_LSB");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEVCPU_PTP_PTP_STATUS_PTP_CUR_SEC_MSB, "PTP_STATUS_PTP_CUR_SEC_MSB");

    /* DEV:PORT_MODE */
    vtss_srvl_debug_reg_header(pr, "DEV:PORT_MODE");
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "RX_PATH_DELAY_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEV_PORT_MODE_RX_PATH_DELAY(VTSS_TO_DEV(port)), buf);
        VTSS_SPRINTF(buf, "TX_PATH_DELAY_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_DEV_PORT_MODE_TX_PATH_DELAY(VTSS_TO_DEV(port)), buf);
    }

    /* SYS:PTP (common to Serval1 and Ocelot) */
    vtss_srvl_debug_reg_header(pr, "SYS:PTP");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_STATUS, "PTP_STATUS");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_TXSTAMP, "PTP_TXSTAMP");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_NXT, "PTP_NXT");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_CFG, "PTP_CFG");

    /* SYS_PORT:PTP (common to Serval1 and Ocelot) */
    vtss_srvl_debug_reg_header(pr, "REW:PORT");
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "PTP_CFG_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_CFG(port), buf);
        VTSS_SPRINTF(buf, "PTP_DLY1_CFG_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_REW_PORT_PTP_DLY1_CFG(port), buf);
    }
    /* ANA_PORT:PTP (common to Serval1 and Ocelot) */
    vtss_srvl_debug_reg_header(pr, "ANA:PORT");
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "PTP_CFG_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_PORT_PTP_CFG(port), buf);
        VTSS_SPRINTF(buf, "PTP_DLY1_CFG_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_PORT_PTP_DLY1_CFG(port), buf);
        VTSS_SPRINTF(buf, "PTP_DLY2_CFG_%u", port);
        vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_PORT_PTP_DLY2_CFG(port), buf);
    }

    /* ANA:: (common to Serval1 and Ocelot) */
    vtss_srvl_debug_reg_header(pr, "ANA::PTP");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, "PTP_ID_HIGH");
    vtss_srvl_debug_reg(vtss_state, pr, VTSS_ANA_ANA_TABLES_PTP_ID_LOW, "PTP_ID_LOW");
    
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_srvl_ts_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, srvl_debug_ts, vtss_state, pr, info);
}

static vtss_rc srvl_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    if (domain == 0) {
        return srvl_ts_timeofday_get(vtss_state, ts, tc);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc srvl_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    if (domain == 0) {
        return srvl_ts_timeofday_set(vtss_state, ts);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc srvl_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    if (domain == 0) {
        return srvl_ts_timeofday_set_delta(vtss_state, ts, negative);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc srvl_ts_domain_timeofday_next_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    if (domain == 0) {
        return srvl_ts_timeofday_next_pps_get(vtss_state, ts);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc srvl_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    if (domain == 0) {
        return srvl_ts_timeofday_offset_set(vtss_state, offset);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc srvl_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    if (domain == 0) {
        return srvl_ts_adjtimer_set(vtss_state);
    } else {
        return VTSS_RC_ERROR;
    }
}
#if !defined(VTSS_ARCH_OCELOT)
/* serval gpio config*/
static const u8 ptp_gpio_srvl[4] = {
    30, /* GPIO_30 */
    31, /* GPIO_31 */
    15, /* GPIO_15 */
    16  /* GPIO_16 */
};
#endif

static vtss_rc srvl_ts_saved_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    vtss_rc rc = VTSS_RC_OK ;
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
#if defined(VTSS_ARCH_OCELOT)
    u32 tc_ns;
    rc = ocelot_ts_io_pin_timeofday_get_no_action(vtss_state, ts, io);
    VTSS_D("io pin %d, sec %d, nanosec %d", io, ts->seconds, ts->nanoseconds);
    SRVL_RD(VTSS_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC(io), &tc_ns);
    *tc = VTSS_X_DEVCPU_PTP_PTP_PINS_PTP_TOD_NSEC_PTP_TOD_NSEC(tc_ns);
    if (*tc >= 0x3ffffff0 && *tc <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        *tc = 999999984 + (*tc & 0xf);
    }
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
    }

#else
    u32 saved;
    u32 saved_ns;
    u32 reg = (io == 0?0:1) ;
    VTSS_RC(srvl_ts_timeofday_read(vtss_state, ts, tc));
    SRVL_RD(VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT(reg), &saved);
    // saved ns counter (not clock cycles as described in the register doc.
    saved = VTSS_X_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(saved);
    *tc = saved;
    if (saved < (((u32)HW_NS_PR_SEC * 3) / (u32)HW_CLK_CNT_PR_SEC)) {
        saved = saved + HW_NS_PR_SEC;
    }
    saved_ns = saved - (((u32)HW_NS_PR_SEC * 3) / (u32)HW_CLK_CNT_PR_SEC);
    //saved_ns = saved >= HW_NS_PR_SEC ? saved - HW_NS_PR_SEC : saved;
    VTSS_D("saved:  %u, saved_ns %u, s %u, ns %u", saved, saved_ns, ts->seconds, ts->nanoseconds);
    if (saved_ns > ts->nanoseconds) {
        if (--ts->seconds == 0xffffffff) --ts->sec_msb;
    }
    ts->nanoseconds = saved_ns;
    VTSS_D("s %u, ns %u", ts->seconds, ts->nanoseconds);
#endif
    return rc;
}

static vtss_rc srvl_ts_external_io_mode_set(vtss_state_t *vtss_state, u32 io) {

#if defined(VTSS_ARCH_OCELOT)
    vtss_ts_ext_io_mode_t *ext_io_mode;

    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    ext_io_mode->domain = 0;
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_IN);
    }

    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
        u32 dividers = HW_NS_PR_SEC/ext_io_mode->freq;
        u32 high_div = dividers/2;
        u32 low_div  = (dividers+1)/2;
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(io),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(high_div));
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(io),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD_PIN_WFL(low_div));
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, 0);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(io),
                   VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(io), 0);
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);

        // on ocelot both EXT_PPS_PIN and EXT_CLK_PIN are used as 1PPS output
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN], VTSS_GPIO_ALT_0);
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD(EXT_CLK_PIN),
        VTSS_F_DEVCPU_PTP_PTP_PINS_PIN_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        SRVL_WR(VTSS_DEVCPU_PTP_PTP_PINS_PIN_WF_LOW_PERIOD(EXT_CLK_PIN), 0);
        OCELOT_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
        OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
         OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
         (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
         OCELOT_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
    }
    return VTSS_RC_OK;
#else

    vtss_ts_ext_io_mode_t *ext_io_mode;
    vtss_gpio_mode_t gpio_alternate_mode;
    u32 cfg_bit_field_in = 0, ri;
    u32 cfg_bit_field_out = 0;

    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    ext_io_mode->domain = 0;

    if (io == 0) {
#if defined(VTSS_ARCH_SEVILLE_2)
        return VTSS_RC_ERROR;
#endif
        if (ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_OUTPUT || ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
            return VTSS_RC_ERROR;
        }
        cfg_bit_field_in = 0x1;
        ri = 0;
        gpio_alternate_mode = VTSS_GPIO_ALT_0;
    } else if (io == 1) {
#if defined(VTSS_ARCH_SEVILLE_2)
        return VTSS_RC_ERROR;
#endif
        if (ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_LOAD || ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_SAVE) {
             return VTSS_RC_ERROR;
        }
        cfg_bit_field_out = 0x1;
        ri = 0;
        gpio_alternate_mode = VTSS_GPIO_ALT_0;
    } else if (io == 2) {
        if (ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_OUTPUT || ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
            return VTSS_RC_ERROR;
        }
        cfg_bit_field_in = 0x2;
        ri = 1;
#if !defined(VTSS_ARCH_SEVILLE_2)
        gpio_alternate_mode = VTSS_GPIO_ALT_1;
#endif /* VTSS_ARCH_SEVILLE_2 */
    } else if (io == 3) {
        if (ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_LOAD || ext_io_mode->pin == VTSS_TS_EXT_IO_MODE_ONE_PPS_SAVE) {
            return VTSS_RC_ERROR;
        }
        cfg_bit_field_out = 0x2;
        ri = 1;
        gpio_alternate_mode = VTSS_GPIO_ALT_0;
#if !defined(VTSS_ARCH_SEVILLE_2)
        gpio_alternate_mode = VTSS_GPIO_ALT_1;
#endif /* VTSS_ARCH_SEVILLE_2 */
    }
VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);

    #if !defined(VTSS_ARCH_SEVILLE_2)
    /* Set gpio mode */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio_srvl[io], VTSS_GPIO_IN);
    } else {
        (void) vtss_srvl_gpio_mode(vtss_state, 0, ptp_gpio_srvl[io],gpio_alternate_mode);
    }
    #endif
    SRVL_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG(ri),
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA);

    /* Set pin configuration */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        /* set dividers; enable clock output. */
        u32 dividers = (HW_CLK_CNT_PR_SEC/(ext_io_mode->freq));
        u32 high_div = (dividers/2)-1;
        u32 low_div =  ((dividers+1)/2)-1;
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG(ri),
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA);
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA(cfg_bit_field_out));
        SRVL_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG(ri), high_div  &
               VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD);
        SRVL_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG(ri), low_div  &
               VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        /* disable clock output, 1 pps output enabled */
        SRVL_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG(ri),
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA);
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL(cfg_bit_field_out) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA(cfg_bit_field_out));
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        SRVL_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG(ri),
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_SYNC_ENA);
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA(cfg_bit_field_in) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_CAP_ENA(cfg_bit_field_in));
        SRVL_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA(cfg_bit_field_in));
    } else if(ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        /*  load enabled */
        SRVL_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA(cfg_bit_field_in));
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        SRVL_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL(cfg_bit_field_out) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA(cfg_bit_field_out) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA(cfg_bit_field_in) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_CAP_ENA(cfg_bit_field_in) |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA(cfg_bit_field_in));
    } else {
        VTSS_E("invalid pin cfg: %u", ext_io_mode->pin);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
#endif
}

/* - Initialization ------------------------------------------------ */

static vtss_rc srvl_ts_init(vtss_state_t *vtss_state)
{
    u32 clk_cfg, clk_pr_ns, clk_pr_100ps;
    // Disable and reset master counter
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG, 0);
    // Enable master counter
    SRVL_WR(VTSS_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG, VTSS_F_DEVCPU_PTP_PTP_CFG_PTP_MISC_CFG_PTP_ENA);
    /* release all timestamp id's except those that are reserved for SW*/
    SRVL_WR(VTSS_ANA_ANA_TABLES_PTP_ID_LOW, VTSS_ENCODE_BITMASK(TS_IDS_RESERVED_FOR_SW,32-TS_IDS_RESERVED_FOR_SW));
    SRVL_WR(VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, 0xffffffff); /* assuming 32 are reserved for HW */
    /* pr default use 30 bit timestamping in the reserved field in the PTP packets (backplane mode) */
    SRVL_WRM(VTSS_SYS_PTP_PTP_CFG, VTSS_F_SYS_PTP_PTP_CFG_PTP_STAMP_WID(30), VTSS_M_SYS_PTP_PTP_CFG_PTP_STAMP_WID);

    SRVL_RD(VTSS_DEVCPU_PTP_PTP_CFG_PTP_SYS_CLK_CFG, &clk_cfg);
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

vtss_rc vtss_srvl_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = srvl_ts_timeofday_get;
        state->timeofday_raw = srvl_ts_timeofday_read;
        state->timeofday_set = srvl_ts_timeofday_set;
        state->timeofday_set_delta = srvl_ts_timeofday_set_delta;
        state->timeofday_next_pps_get = srvl_ts_timeofday_next_pps_get;
        state->timeofday_prev_pps_get = srvl_ts_timeofday_prev_pps_get;
        state->timeofday_offset_set = srvl_ts_timeofday_offset_set;
        state->ns_cnt_get = srvl_ts_ns_cnt_get;
        state->timeofday_one_sec = srvl_ts_timeofday_one_sec;
        state->adjtimer_set = srvl_ts_adjtimer_set;
        state->freq_offset_get = srvl_ts_freq_offset_get;
        state->external_clock_mode_set = srvl_ts_external_clock_mode_set;
        state->alt_clock_saved_get = srvl_ts_alt_clock_saved_get;
        state->alt_clock_saved_timeofday_get = srvl_ts_alt_clock_saved_timeofday_get;

        state->alt_clock_mode_set = srvl_ts_alt_clock_mode_set;
        state->timeofday_next_pps_set = srvl_ts_timeofday_next_pps_set;
        state->ingress_latency_set = srvl_ts_ingress_latency_set;
        state->p2p_delay_set = srvl_ts_p2p_delay_set;
        state->egress_latency_set = srvl_ts_egress_latency_set;
        state->delay_asymmetry_set = srvl_ts_delay_asymmetry_set;
        state->operation_mode_set = srvl_ts_operation_mode_set;
        state->internal_mode_set = srvl_ts_internal_mode_set;
        state->timestamp_get = srvl_ts_timestamp_get;
        state->timestamp_id_release = srvl_ts_timestamp_id_release;
        state->status_change = srvl_ts_status_change;
        /* domain specific functions added for new architectures */
        state->domain_timeofday_get = srvl_ts_domain_timeofday_get;
        state->domain_timeofday_set = srvl_ts_domain_timeofday_set;
        state->domain_timeofday_set_delta = srvl_ts_domain_timeofday_set_delta;
        state->domain_timeofday_next_pps_get = srvl_ts_domain_timeofday_next_pps_get;
        state->domain_timeofday_offset_set = srvl_ts_domain_timeofday_offset_set;
        state->domain_adjtimer_set = srvl_ts_domain_adjtimer_set;
        state->saved_timeofday_get = srvl_ts_saved_timeofday_get;
        state->external_io_mode_set = srvl_ts_external_io_mode_set;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(srvl_ts_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* VTSS_FEATURE_TIMESTAMP */

#endif /* VTSS_ARCH_OCELOT */
