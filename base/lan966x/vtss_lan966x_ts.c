// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_TIMESTAMP)

/* GPIO configuration */
#define PCB8291_GPIO_FUNC_INFO_SIZE 5
static vtss_gpio_func_info_t ptp_gpio[PCB8291_GPIO_FUNC_INFO_SIZE] = {   /* PCB8291 is default. This also cover PCB8290 except PTP2 is not connected */
    {.gpio_no = 35, //PTP_0
     .alt = VTSS_GPIO_FUNC_ALT_1},
    {.gpio_no = 36, //PTP_1
     .alt = VTSS_GPIO_FUNC_ALT_1},
    {.gpio_no = 37, //PTP_2
     .alt = VTSS_GPIO_FUNC_ALT_1},
    {.gpio_no = 38, //PTP_3
     .alt = VTSS_GPIO_FUNC_ALT_1},
    {.gpio_no = 39, //PTP_4
     .alt = VTSS_GPIO_FUNC_ALT_1},
};

static vtss_gpio_mode_t to_vtss_gpio_mode(vtss_gpio_func_alt_t alt) {
    switch (alt) {
        case VTSS_GPIO_FUNC_ALT_0:
            return VTSS_GPIO_ALT_0;
        case VTSS_GPIO_FUNC_ALT_1:
            return VTSS_GPIO_ALT_1;
        case VTSS_GPIO_FUNC_ALT_2:
            return VTSS_GPIO_ALT_2;
    }
    return VTSS_GPIO_ALT_0;
}

static u64 nominal_tod_increment;

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
#define PTP_PIN_ACTION_SYNC 3

#define LAN966X_PTP_PIN_ACTION(pin, act, sync, dom)  \
REG_WRM(PTP_PIN_CFG(pin),                       \
         PTP_PIN_CFG_PIN_ACTION(act) | PTP_PIN_CFG_PIN_SYNC(sync) | PTP_PIN_CFG_PIN_DOM(dom),   \
         PTP_PIN_CFG_PIN_ACTION_M | PTP_PIN_CFG_PIN_SYNC_M | PTP_PIN_CFG_PIN_DOM_M);

static vtss_rc lan966x_ts_io_pin_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
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
    return lan966x_ts_io_pin_timeofday_get(vtss_state, TOD_ACC_PIN, ts, tc);
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

static vtss_rc lan966x_ts_domain_timeofday_prev_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    u64 tc;

    VTSS_RC(lan966x_ts_timeofday_read(vtss_state, domain, ts, &tc));

    ts->nanoseconds = 0;
    ts->nanosecondsfrac = 0;

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_domain_timeofday_next_pps_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts)
{
    VTSS_RC(lan966x_ts_domain_timeofday_prev_pps_get(vtss_state, domain, ts));
    VTSS_RC(vtss_timestampAddSec(ts));

    VTSS_D("sec_msb: %u, seconds: %u, nanoseconds: %u, nanosecondsfrac: %u", ts->sec_msb, ts->seconds, ts->nanoseconds, ts->nanosecondsfrac);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_next_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return lan966x_ts_domain_timeofday_next_pps_get(vtss_state, 0, ts);
}

static vtss_rc lan966x_ts_timeofday_prev_pps_get(vtss_state_t *vtss_state, vtss_timestamp_t *ts)
{
    return lan966x_ts_domain_timeofday_prev_pps_get(vtss_state, 0, ts);
}

static vtss_rc lan966x_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    VTSS_D("offset before: %i", offset);
    /* must be in IDLE mode before the time can be loaded */
    LAN966X_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, domain);
    REG_WR(PTP_TOD_NSEC(TOD_ACC_PIN),
           PTP_TOD_NSEC_TOD_NSEC(-offset));
    LAN966X_PTP_PIN_ACTION (TOD_ACC_PIN, PTP_PIN_ACTION_DELTA, PTP_PIN_ACTION_NOSYNC, domain);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    return lan966x_ts_domain_timeofday_offset_set(vtss_state, 0, offset);
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

static vtss_rc lan966x_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    i32 nanoseconds;

    VTSS_D("domain: %u, negative: %u", domain, negative);

    nanoseconds = (ts->nanoseconds > 0x7FFFFFFF) ? 0x7FFFFFFF : ts->nanoseconds;

    if (ts->seconds > 0 || ts->sec_msb > 0 || ts->nanoseconds > HW_NS_PR_SEC/2 || ts->nanosecondsfrac > 0) {
        vtss_timestamp_t ts_prev;
        u64              tc;

        /* Read current time */
        VTSS_RC(lan966x_ts_timeofday_read(vtss_state, domain, &ts_prev, &tc));

        /* Calculate new time */
        if (negative){
            VTSS_RC(vtss_timestampSub(&ts_prev, ts));
        } else {
            VTSS_RC(vtss_timestampAdd(&ts_prev, ts));
        }

        return lan966x_ts_domain_timeofday_set(vtss_state, domain, &ts_prev);
    } else {
        return lan966x_ts_domain_timeofday_offset_set(vtss_state, domain, negative ? nanoseconds : -nanoseconds);  /* Function lan966x_ts_domain_timeofday_offset_set is subtracting nanoseconds from TOD, so 'negative' must be positive and visa versa */
    }
}

static vtss_rc lan966x_ts_timeofday_set_delta(vtss_state_t *vtss_state, const vtss_timestamp_t *ts, BOOL negative)
{
    return lan966x_ts_domain_timeofday_set_delta(vtss_state, 0, ts, negative);
}

static vtss_rc lan966x_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    i32 adj;
    u32 adj_abs, dom_mask=0x01<<domain;
    u64 tod_inc, one_pico, tod_delta, tod_trunk;

    VTSS_D("enter domain %u  nominal_tod_increment %" PRIu64 "", domain, nominal_tod_increment);

    if (domain >= VTSS_TS_DOMAIN_ARRAY_SIZE) {
        VTSS_D("domain %d is larger than VTSS_TS_DOMAIN_ARRAY_SIZE %u", domain, VTSS_TS_DOMAIN_ARRAY_SIZE);
        return VTSS_RC_ERROR;
    }
    adj = vtss_state->ts.conf.adj[domain];
    adj_abs = VTSS_LABS(adj);

    tod_inc = nominal_tod_increment;  /* Fetch the nominal TOD increment as a baseline */

    /* Calculate the TOD increment delta value, that is a fraction of the nominal TOD increment. */
    /* The fraction is given by 'adj' in 1E-10. The calculation is: tod_delta = tod_inc * (adj / 1E10) */
    tod_trunk = tod_inc % 10000000000LL;   /* We will divide before multiplying to avoid overrun. The TOD truncated part is saved in 'tod_trunk' */
    tod_delta = (tod_inc / 10000000000LL) * adj_abs;    /* Divide and then multiply */
    tod_delta += (tod_trunk * adj_abs) / 10000000000LL; /* Now the truncated part is multiplied and then divided. Result is added to 'tod_delta' */

    /* Check if the delta value is too large */
    one_pico = 0x0800000000000000/1000;  /* One pico is one nano divided by 1000. One nano in 5.59 notation is 0x0800000000000000 */
    VTSS_D("adj %i  tod_delta %" PRIu64 "  1.9pico %" PRIu64 "", adj, tod_delta, ((one_pico*19)/10));
    if (tod_delta > (one_pico*19)/10) {    /* In case the numeric change is more than 1.9 pico seconds, PTP must be restarted so this is rejected */
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
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(dom_mask), PTP_DOM_CFG_CLKCFG_DIS_M);
    REG_WR(PTP_CLK_PER_CFG(domain, 0), (u32)(tod_inc & 0xFFFFFFFF));
    REG_WR(PTP_CLK_PER_CFG(domain, 1), (u32)(tod_inc >> 32));
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(0), PTP_DOM_CFG_CLKCFG_DIS_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    return lan966x_ts_domain_adjtimer_set(vtss_state, 0);
}

static vtss_rc lan966x_ts_external_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_ext_clock_mode_t *ext_clock_mode = &vtss_state->ts.conf.ext_clock_mode;

    VTSS_D("one_pps_mode: %u, enable: %u, freq: %u", ext_clock_mode->one_pps_mode, ext_clock_mode->enable, ext_clock_mode->freq);
    LAN966X_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (ext_clock_mode->enable) {
        u32 dividers = HW_NS_PR_SEC/ext_clock_mode->freq;
        u32 high_div = dividers/2;
        u32 low_div  = (dividers+1)/2;
        REG_WR(PTP_WF_HIGH_PERIOD(EXT_CLK_PIN),
               PTP_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(PTP_WF_LOW_PERIOD(EXT_CLK_PIN),
               PTP_WF_LOW_PERIOD_PIN_WFL(low_div));

        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN].gpio_no, to_vtss_gpio_mode(ptp_gpio[EXT_CLK_PIN].alt));
        LAN966X_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, 0);

    } else if (ext_clock_mode->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN].gpio_no, to_vtss_gpio_mode(ptp_gpio[EXT_CLK_PIN].alt));
        REG_WR(PTP_WF_HIGH_PERIOD(EXT_CLK_PIN),
               PTP_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(PTP_WF_LOW_PERIOD(EXT_CLK_PIN), 0);

        LAN966X_PTP_PIN_ACTION (EXT_CLK_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[EXT_CLK_PIN].gpio_no, VTSS_GPIO_IN);
    }

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_saved_get(vtss_state_t *vtss_state, u64 *const saved)
{
    u32                       nsec, nsec_frac;
    vtss_ts_alt_clock_mode_t  *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    REG_RD(PTP_TOD_NSEC(ALT_LDST_PIN), &nsec);
    nsec = PTP_TOD_NSEC_TOD_NSEC_X(nsec);
    if (nsec >= 0x3ffffff0 && nsec <= 0x3fffffff) { /* -1..-16 = 10^9-1..16 */
        nsec = 999999984 + (nsec & 0xf);
    }
    REG_RD(PTP_TOD_NSEC_FRAC(ALT_LDST_PIN), &nsec_frac);
    nsec_frac = PTP_TOD_NSEC_FRAC_TOD_NSEC_FRAC_X(nsec_frac);
    *saved = ((u64)nsec << 16) + ((u64)nsec_frac << 8);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
        } else if (alt_clock_mode->save) {
            LAN966X_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_NOSYNC, 0);
        } else if (alt_clock_mode->load) {
            LAN966X_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_NOSYNC, 0);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_alt_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_alt_clock_mode_t *alt_clock_mode = &vtss_state->ts.conf.alt_clock_mode;

    LAN966X_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_out) {
        REG_WR(PTP_WF_HIGH_PERIOD(ALT_PPS_PIN),
               PTP_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(PTP_WF_LOW_PERIOD(ALT_PPS_PIN), 0);

        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN].gpio_no, to_vtss_gpio_mode(ptp_gpio[ALT_PPS_PIN].alt));
        LAN966X_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, 0);
    } else {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[ALT_PPS_PIN].gpio_no, VTSS_GPIO_IN);
    }

    LAN966X_PTP_PIN_ACTION (ALT_PPS_PIN, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, 0);
    if (alt_clock_mode->one_pps_in) {
        if (alt_clock_mode->save && alt_clock_mode->load) {
            VTSS_E("save and load cannot be enabled at the same time");
            return VTSS_RC_ERROR;
        } else if (alt_clock_mode->save) {
            (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN].gpio_no, to_vtss_gpio_mode(ptp_gpio[ALT_LDST_PIN].alt));
            LAN966X_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, 0);
        } else if (alt_clock_mode->load) {
            (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN].gpio_no, to_vtss_gpio_mode(ptp_gpio[ALT_LDST_PIN].alt));
            LAN966X_PTP_PIN_ACTION (ALT_LDST_PIN, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, 0);
        }
    } else {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[ALT_LDST_PIN].gpio_no, VTSS_GPIO_IN);
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timeofday_next_pps_set(vtss_state_t *vtss_state, const vtss_timestamp_t *const ts)
{
    if (vtss_state->ts.conf.alt_clock_mode.one_pps_in) {
        REG_WR(PTP_TOD_SEC_MSB(ALT_LDST_PIN),
               PTP_TOD_SEC_MSB_TOD_SEC_MSB(ts->sec_msb));
        REG_WR(PTP_TOD_SEC_LSB(ALT_LDST_PIN), ts->seconds-1);
        REG_WR(PTP_TOD_NSEC(ALT_LDST_PIN),
               PTP_TOD_NSEC_TOD_NSEC(ts->nanoseconds));
        REG_WR(PTP_TOD_NSEC_FRAC(ALT_LDST_PIN),
               PTP_TOD_NSEC_FRAC_TOD_NSEC_FRAC(ts->nanosecondsfrac));
    }

    VTSS_D("time at next pps: sec_msb %u, sec %u, ns %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32                   port;
    vtss_ts_port_conf_t   *conf;
    i32                   rx_delay;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }

    port = VTSS_CHIP_PORT(port_no);
    conf = &vtss_state->ts.port_conf[port_no];

    /* The default_igr_latency is in picoseconds */
    /* The ingress_latency is in nanoseconds<<16  */
    /* Register is in nanoseconds<<8 */
    rx_delay = (VTSS_MOD64(conf->ingress_latency, ((u64)VTSS_ONE_MIA << 16)) >> 8) + ((conf->default_igr_latency << 8)/1000);

    if (rx_delay > 0xFFFFFF) { /* Register max value is 0xFFFFFF */
        rx_delay = 0xFFFFFF;
    }
    VTSS_I("rx_delay %i  egress_latency %u  default_igr_latency %u", rx_delay, VTSS_INTERVAL_NS(conf->egress_latency), conf->default_igr_latency);

    REG_WRM(SYS_PTP_RXDLY_CFG(port),
            SYS_PTP_RXDLY_CFG_PTP_RX_IO_DLY(rx_delay),
            SYS_PTP_RXDLY_CFG_PTP_RX_IO_DLY_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32                 p2p_delay = VTSS_INTERVAL_NS(conf->p2p_delay) * 4;  /* Registers are in 0.25 ns resolution */
    REG_WR(REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), p2p_delay + (VTSS_INTERVAL_NS(conf->delay_asymmetry) * 4));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32                   port;
    vtss_ts_port_conf_t   *conf;
    u32                   tx_delay;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }

    port = VTSS_CHIP_PORT(port_no);
    conf = &vtss_state->ts.port_conf[port_no];

    /* The default_egr_latency is in picoseconds */
    /* The egress_latency is in nanoseconds<<16  */
    /* Register is in nanoseconds<<8 */
    tx_delay = (VTSS_MOD64(conf->egress_latency, ((u64)VTSS_ONE_MIA << 16)) >> 8) + ((conf->default_egr_latency << 8)/1000);

    if (tx_delay > 0xFFFFFF) { /* Register max value is 0xFFFFFF */
        tx_delay = 0xFFFFFF;
    }
    VTSS_I("tx_delay %u  egress_latency %u  default_egr_latency %u", tx_delay, VTSS_INTERVAL_NS(conf->egress_latency), conf->default_egr_latency);

    REG_WRM(SYS_PTP_TXDLY_CFG(port),
            SYS_PTP_TXDLY_CFG_PTP_TX_IO_DLY(tx_delay),
            SYS_PTP_TXDLY_CFG_PTP_TX_IO_DLY_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_delay_asymmetry_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 delay = VTSS_INTERVAL_NS(conf->delay_asymmetry) * 4;    /* Registers are in 0.25 ns resolution */
    /* Used for Ingress asymmetry compensation (Pdelay_Resp) */
    REG_WR(REW_PTP_IDLY1_CFG(VTSS_CHIP_PORT(port_no)), delay);
    /* Used for Egress asymmetry compensation (on Delay_Req and Pdelay_Req) */
    REG_WR(REW_PTP_EDLY_CFG(VTSS_CHIP_PORT(port_no)), -delay);
    /* Used for Ingress asymmetry compensation (on Sync, therefore include p2p_delay ) */
    REG_WR(REW_PTP_IDLY2_CFG(VTSS_CHIP_PORT(port_no)), delay + VTSS_INTERVAL_NS(conf->p2p_delay));
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_mode_t         mode = vtss_state->ts.port_conf[port_no].mode.mode;
    u32                    domain = vtss_state->ts.port_conf[port_no].mode.domain;
    vtss_ts_internal_fmt_t fmt = vtss_state->ts.int_mode.int_fmt;
    u32                    mode_val = 0;
    u32                    port = VTSS_CHIP_PORT(port_no);

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
    REG_WRM(SYS_PTP_MODE_CFG(port, 0),
            SYS_PTP_MODE_CFG_PTP_MODE_VAL(mode_val),
            SYS_PTP_MODE_CFG_PTP_MODE_VAL_M);
    REG_WRM(SYS_PTP_MODE_CFG(port, 1),
            SYS_PTP_MODE_CFG_PTP_MODE_VAL(mode_val),
            SYS_PTP_MODE_CFG_PTP_MODE_VAL_M);
    REG_WRM(SYS_PTP_CFG(port),
            SYS_PTP_CFG_PTP_DOM_VAL(domain),
            SYS_PTP_CFG_PTP_DOM_VAL_M);
    // disable central counters in DEVCPU
    REG_WRM(PTP_DOM_CFG,
            PTP_DOM_CFG_ENA(0),
            PTP_DOM_CFG_ENA(1<<domain));
    // Set domain in DEV_xxx
    REG_WRM(SYS_PTP_CFG(port),
            SYS_PTP_CFG_PTP_DOM_VAL(domain),
            SYS_PTP_CFG_PTP_DOM_VAL_M);
    // enable central counters in DEVCPU
    REG_WRM(PTP_DOM_CFG,
            PTP_DOM_CFG_ENA(1<<domain),
            PTP_DOM_CFG_ENA(1<<domain));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_internal_mode_set(vtss_state_t *vtss_state)
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

static u32 api_port(vtss_state_t *vtss_state, u32 chip_port)
{
    u32 port_no;
    int found = 0;
    /* Map from chip port to API port */
    if (chip_port == VTSS_CHIP_PORT_CPU) {
        port_no = VTSS_CHIP_PORT_CPU;
    } else {
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if ((u32)VTSS_CHIP_PORT(port_no) == chip_port) {
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

static vtss_rc lan966x_ts_timestamp_get(vtss_state_t *vtss_state)
{
    u32  value, tx_stamp, rx_stamp, tx_port, mess_id;
    BOOL overflow = FALSE;

    REG_RD(PTP_TWOSTEP_CTRL, &value);
    while (PTP_TWOSTEP_CTRL_VLD_X(value)) {
        /* Read TX timestamp */
        if (!PTP_TWOSTEP_CTRL_STAMP_TX_X(value)) {
            VTSS_E("TX timestamp expected but RX timestamp found");
            REG_WR(PTP_TWOSTEP_CTRL, PTP_TWOSTEP_CTRL_NXT(1));
            REG_RD(PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= PTP_TWOSTEP_CTRL_OVFL_X(value);
        tx_port = api_port(vtss_state, PTP_TWOSTEP_CTRL_STAMP_PORT_X(value));
        REG_RD(PTP_TWOSTEP_STAMP, &tx_stamp);

        /* Read RX timestamp */
        REG_WR(PTP_TWOSTEP_CTRL, PTP_TWOSTEP_CTRL_NXT(1));
        REG_RD(PTP_TWOSTEP_CTRL, &value);
        if (!PTP_TWOSTEP_CTRL_VLD_X(value) ||
            PTP_TWOSTEP_CTRL_STAMP_TX_X(value)) {
            VTSS_E("RX timestamp not found");
            REG_WR(PTP_TWOSTEP_CTRL, PTP_TWOSTEP_CTRL_NXT(1));
            REG_RD(PTP_TWOSTEP_CTRL, &value);
            continue;
        }
        overflow |= PTP_TWOSTEP_CTRL_OVFL_X(value);
        REG_RD(PTP_TWOSTEP_STAMP, &rx_stamp);

        mess_id = PTP_TWOSTEP_STAMP_STAMP_NSEC_X(rx_stamp); /* The RX timestamp ns part is used as the message id. This will only work if this is not a real RX timestamp by something inserted in IFH by SW when injecting */
        if (mess_id >= VTSS_TS_ID_SIZE) {
            VTSS_D("skip mess_id %u", mess_id);
        } else if (tx_port < VTSS_PORT_ARRAY_SIZE) {
            vtss_state->ts.status[mess_id].tx_tc[tx_port] = ((u64)PTP_TWOSTEP_STAMP_STAMP_NSEC_X(tx_stamp) << 16) | (PTP_TWOSTEP_STAMP_STAMP_SUB_NSEC_X(tx_stamp) << 14);    /* Sub ns is only two bits */
            vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
            vtss_state->ts.status[mess_id].valid_mask |= 1LL<<tx_port;
        } else {
            VTSS_E("invalid port (%u)", tx_port);
        }

        VTSS_D("value %x, tx_stamp %u, tx_port %u, mess_id %u", value, tx_stamp, tx_port, mess_id);
        REG_WR(PTP_TWOSTEP_CTRL, PTP_TWOSTEP_CTRL_NXT(1));
        REG_RD(PTP_TWOSTEP_CTRL, &value);
    }
    if (overflow) {
        VTSS_E("Timestamp fifo overflow occurred");
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    return VTSS_RC_OK;
}

typedef struct {
    u32 rx;
    u32 tx;
} io_delay_t;
static io_delay_t gmii_delay[VTSS_PORT_COUNT];
static io_delay_t qsgmii_delay[VTSS_PORT_COUNT];
static io_delay_t sgmii_delay[VTSS_PORT_COUNT];
static io_delay_t sgmii_2g5_delay[VTSS_PORT_COUNT];
static io_delay_t swc_gmii_delay[VTSS_PORT_COUNT];
static io_delay_t swc_gmii_2g5_delay[VTSS_PORT_COUNT];

/*
* Signal port status (configuration actually) change (used to detect and compensate for the internal ingress and egress latencies)
*/
static vtss_rc lan966x_ts_status_change(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_port_interface_t interface;
    vtss_port_speed_t     speed;
    u32                   port, value;
    vtss_rc               rc = VTSS_RC_OK, rc2;
    u32                   rx_delay = 0, tx_delay = 0;

    VTSS_D("Enter  port_no %d", port_no);

    if (!vtss_state->port.conf_set_called[port_no]) {
        VTSS_I("port %d status change called before port is configured", port_no);
        return VTSS_RC_OK;
    }
    interface = vtss_state->port.current_if_type[port_no];
    speed = vtss_state->port.current_speed[port_no];

    port = VTSS_CHIP_PORT(port_no);

    VTSS_D("chip_port %u  interface %d  speed %u", port, interface, speed);
    REG_RD(DEV_PCS1G_LINK_STATUS(port), &value);
    switch (interface) {
    case VTSS_PORT_INTERFACE_GMII:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay = gmii_delay[port].rx;
            tx_delay = gmii_delay[port].tx;
            rx_delay += 800 * DEV_PCS1G_LINK_STATUS_DELAY_VAR_X(value);      /* Add the variable delay in the device */
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay = sgmii_delay[port].rx;
            tx_delay = sgmii_delay[port].tx;
            rx_delay += 800 * DEV_PCS1G_LINK_STATUS_DELAY_VAR_X(value);      /* Add the variable delay in the device */
        }
        if (speed == VTSS_SPEED_2500M) {   /* 2.5 Gbps */
            rx_delay = sgmii_2g5_delay[port].rx;
            tx_delay = sgmii_2g5_delay[port].tx;
            rx_delay += 320 * DEV_PCS1G_LINK_STATUS_DELAY_VAR_X(value);      /* Add the variable delay in the device */
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay = qsgmii_delay[port].rx;
            tx_delay = qsgmii_delay[port].tx;
            rx_delay += 800 * DEV_PCS1G_LINK_STATUS_DELAY_VAR_X(value);      /* Add the variable delay in the device */
        }
        break;
    default:
        VTSS_E("unsupported interface: %u", interface);
        return VTSS_RC_ERROR;
    }

    /* Add additional delays found in testing. Note that rx_delay and tx_delay values are in pico seconds */
    switch (interface) {
    case VTSS_PORT_INTERFACE_GMII:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay += (1000 * 276);
            tx_delay += (1000 * 276);
        }
        break;
    case VTSS_PORT_INTERFACE_SGMII:
    case VTSS_PORT_INTERFACE_SERDES:
    case VTSS_PORT_INTERFACE_VAUI:
    case VTSS_PORT_INTERFACE_SGMII_CISCO:
    case VTSS_PORT_INTERFACE_SGMII_2G5:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay += (1000 * 39);
            tx_delay += (1000 * 39);
        }
        if (speed == VTSS_SPEED_2500M) {   /* 2.5 Gbps */
            rx_delay += (1000 * 18);
            tx_delay += (1000 * 18);
        }
        break;
    case VTSS_PORT_INTERFACE_QSGMII:
        if (speed == VTSS_SPEED_1G) {   /* 1 Gbps */
            rx_delay += (1000 * 558);
            tx_delay += (1000 * 558);
        }
        break;
    default:
        break;
    }

    /* rx_delay and tx_delay are in picoseconds.  */
    VTSS_I(" port_no %d speed %d interface %d rx_dly %u tx_dly %u", port_no, speed, interface, rx_delay, tx_delay);
    vtss_state->ts.port_conf[port_no].default_igr_latency = rx_delay;
    vtss_state->ts.port_conf[port_no].default_egr_latency = tx_delay;
    rc = lan966x_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = lan966x_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

#if !defined(VTSS_VOE_CNT)
#define VTSS_VOE_CNT 8
#endif

static vtss_rc lan966x_ts_seq_cnt_get(vtss_state_t *vtss_state,  u32 sec_cntr,  u16 *const cnt_val)
{
    vtss_rc rc = VTSS_RC_OK;
    u32 value;

    /* Point to the sequence number update configuration for PTP. */
    /* VOP and DLR got the first 2*VTSS_VOE_CNT counter sets as they require 32 bit */
    /* MPR got the next VTSS_VOE_CNT/2 counter sets as they require 16 bit */
    /* PTP requires 16 bit */
    /* sec_cntr is calculated as a 16 bit counter offset */
    sec_cntr += ((VTSS_VOE_CNT*2) + (VTSS_VOE_CNT*2) + VTSS_VOE_CNT);
    if (sec_cntr <= 255*2) {
        // read sec counter REW:PTP_SEQ_NO:PTP_SEQ_NO[0-255]
        REG_RD(REW_PTP_SEQ_NO(sec_cntr/2), &value);
        *cnt_val = (sec_cntr%2) ? REW_PTP_SEQ_NO_PTP_SEQ_NO_1_X(value) : REW_PTP_SEQ_NO_PTP_SEQ_NO_0_X(value);
    } else {
        VTSS_E("Invalid sequence counter number %d", sec_cntr);
        rc = VTSS_RC_ERROR;
    }
    return rc;
}

static vtss_rc lan966x_ts_external_io_mode_set(vtss_state_t *vtss_state, u32 io)
{
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];

    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    /* Set gpio mode */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[io].gpio_no, VTSS_GPIO_IN);
    } else {
        (void) vtss_lan966x_gpio_mode(vtss_state, 0, ptp_gpio[io].gpio_no, to_vtss_gpio_mode(ptp_gpio[io].alt));
    }
    /* Set pin configuration */
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
        u32 dividers = HW_NS_PR_SEC/ext_io_mode->freq;
        u32 high_div = dividers/2 - 1;
        u32 low_div  = (dividers+1)/2 - 1;
        REG_WR(PTP_WF_HIGH_PERIOD(io),
               PTP_WF_HIGH_PERIOD_PIN_WFH(high_div));
        REG_WR(PTP_WF_LOW_PERIOD(io),
               PTP_WF_LOW_PERIOD_PIN_WFL(low_div));
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        REG_WR(PTP_WF_HIGH_PERIOD(io),
               PTP_WF_HIGH_PERIOD_PIN_WFH(PPS_WIDTH));
        REG_WR(PTP_WF_LOW_PERIOD(io), 0);
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_CLOCK, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_LOAD) {
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_LOAD, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_IDLE, PTP_PIN_ACTION_NOSYNC, ext_io_mode->domain);
    } else {
        VTSS_E("invalid pin cfg: %u", ext_io_mode->pin);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_saved_timeofday_get(vtss_state_t *vtss_state, u32 io, vtss_timestamp_t *ts, u64 *tc)
{
    vtss_rc rc ;
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);
    rc = lan966x_ts_io_pin_timeofday_get(vtss_state, io, ts, tc);
    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
        LAN966X_PTP_PIN_ACTION (io, PTP_PIN_ACTION_SAVE, PTP_PIN_ACTION_SYNC, ext_io_mode->domain);
    }
    return rc;
}

static vtss_rc lan966x_ts_output_clock_edge_offset_get(vtss_state_t *vtss_state, u32 io, u32 *offset)
{
    u32  value;

    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }

    REG_RD(PTP_PIN_CFG(io), &value);
    *offset = PTP_PIN_CFG_PIN_OUTP_OFS_X(value);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_ts_link_up(vtss_state_t *vtss_state, const vtss_port_no_t  port_no)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    /* Link is coming up - disable and enable the phase detector */
    REG_WRM(DEV_PHAD_CTRL(port, 0), DEV_PHAD_CTRL_PHAD_ENA(0) | DEV_PHAD_CTRL_DIV_CFG(0),
                                    DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M);
    REG_WRM(DEV_PHAD_CTRL(port, 1), DEV_PHAD_CTRL_PHAD_ENA(0) | DEV_PHAD_CTRL_DIV_CFG(0),
                                    DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M);

    REG_WRM(DEV_PHAD_CTRL(port, 0), DEV_PHAD_CTRL_PHAD_ENA(1) | DEV_PHAD_CTRL_DIV_CFG(3),
                                    DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M);
    REG_WRM(DEV_PHAD_CTRL(port, 1), DEV_PHAD_CTRL_PHAD_ENA(1) | DEV_PHAD_CTRL_DIV_CFG(3),
                                    DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M);

    return VTSS_RC_OK;
}

#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

static vtss_rc lan966x_debug_ts(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    u32            port;
    vtss_port_no_t port_no;
    char           buf[64];
    int            idx;

    /* REW:PORT */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "REW:PORT[%u]", port);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_MISC_CFG(port)), "REW_PTP_MISC_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_EDLY_CFG(port)), "REW_PTP_EDLY_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_IDLY1_CFG(port)), "REW_PTP_IDLY1_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_IDLY2_CFG(port)), "REW_PTP_IDLY2_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_SMAC_LOW(port)), "REW_PTP_SMAC_LOW");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(REW_PTP_SMAC_HIGH(port)), "REW_PTP_SMAC_HIGH");
    }

    /* SYS:PTPPORT */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "SYS:PTPPORT[%u]", port);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PCH_CFG(port)), "SYS_PCH_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_CFG(port)), "SYS_PTP_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_RXDLY_CFG(port)), "SYS_PTP_RXDLY_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_TXDLY_CFG(port)), "SYS_PTP_TXDLY_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_EVENTS(port)), "SYS_PTP_EVENTS");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_MODE_CFG(port, 0)), "SYS_PTP_MODE_CFG[0]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(SYS_PTP_MODE_CFG(port, 1)), "SYS_PTP_MODE_CFG[1]");
    }

    /* PTP:PTP_CFG */
    vtss_lan966x_debug_reg_header(pr, "DEVCPU_PTP:PTP_CFG");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_PIN_INTR), "PTP_PIN_INTR");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_PIN_INTR_ENA), "PTP_PIN_INTR_ENA");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_INTR_IDENT), "PTP_INTR_IDENT");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_DOM_CFG), "PTP_DOM_CFG");

    /* PTP:PTP_PINS */
    for (idx = 0; idx <= 7; idx++) {
        VTSS_SPRINTF(buf, "PTP:PTP_PINS[%u]", idx);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_PIN_CFG(idx)), "PTP_PIN_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TOD_SEC_MSB(idx)), "PTP_TOD_SEC_MSB");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TOD_SEC_LSB(idx)), "PTP_TOD_SEC_LSB");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TOD_NSEC(idx)), "PTP_TOD_NSEC");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TOD_NSEC_FRAC(idx)), "PTP_TOD_NSEC_FRAC");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_NTP_NSEC(idx)), "PTP_NTP_NSEC");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_WF_HIGH_PERIOD(idx)), "PTP_WF_HIGH_PERIOD");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_WF_LOW_PERIOD(idx)), "PTP_WF_LOW_PERIOD");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_PIN_IO_DELAY(idx)), "PTP_PIN_IO_DELAY");
    }

    /* PTP:PTP_TS_FIFO */
    vtss_lan966x_debug_reg_header(pr, "PTP:PTP_TS_FIFO");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TWOSTEP_CTRL), "PTP_TWOSTEP_CTRL");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_TWOSTEP_STAMP), "PTP_TWOSTEP_STAMP");
    vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(PTP_WRP), "PTP_WRP");

    /* DEV:PORT_MODE */
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        port = VTSS_CHIP_PORT(port_no);
        VTSS_SPRINTF(buf, "DEV:PORT_MODE[%u]", port);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PTP_MISC_CFG(port)), "PTP_MISC_CFG");

        VTSS_SPRINTF(buf, "DEV[%u]:PHASE_DETECTOR_CTRL[0-1]", port);
        vtss_lan966x_debug_reg_header(pr, buf);
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_CTRL(port,0)), "PHAD_CTRL[0]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_CTRL(port,1)), "PHAD_CTRL[1]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_CYC_STAT(port,0)), "PHAD_CYC_STAT[0]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_CYC_STAT(port,1)), "PHAD_CYC_STAT[1]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_ERR_STAT(port,0)), "PHAD_ERR_STAT[0]");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(DEV_PHAD_ERR_STAT(port,1)), "PHAD_ERR_STAT[1]");
    }

    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_ts_debug_print(vtss_state_t *vtss_state,
                                    const vtss_debug_printf_t pr,
                                    const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, lan966x_debug_ts, vtss_state, pr, info);
}
#endif // VTSS_OPT_DEBUG_PRINT

/* - Initialization ------------------------------------------------ */

static vtss_rc lan966x_ts_init(vtss_state_t *vtss_state)
{
    u32 domain, i, rc=0;

    /* Disable PTP (all 3 domains)*/
    REG_WR(PTP_DOM_CFG, PTP_DOM_CFG_ENA(0));

    /* Configure the nominal TOD increment per clock cycle */
    /* This is based on 165.625MHz clock frequency that gives period of 6.0377358490566037735ns */
    /* 1 ns is 0x0800000000000000. */
    /* 0x0800000000000000 * 0.0377358490566037735 gives ~004D4873 ECADE305 */
    nominal_tod_increment = ((u64)(6) << 59) + (u64)0x004D4873ECADE305;

    /* Configure the calculated increment */
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(7), PTP_DOM_CFG_CLKCFG_DIS_M);
    for (domain = 0; domain < VTSS_TS_DOMAIN_ARRAY_SIZE; domain++) {
        REG_WR(PTP_CLK_PER_CFG(domain, 0), (u32)(nominal_tod_increment & 0xFFFFFFFF));
        REG_WR(PTP_CLK_PER_CFG(domain, 1), (u32)(nominal_tod_increment >> 32));
    }
    REG_WRM(PTP_DOM_CFG, PTP_DOM_CFG_CLKCFG_DIS(0), PTP_DOM_CFG_CLKCFG_DIS_M);

    /* Enable PTP (all 3 domains)*/
    REG_WR(PTP_DOM_CFG, PTP_DOM_CFG_ENA(7));

    /* Configure the PTP pin to GPIO selection */
    for (i = 0; i < 8; ++i) {
        REG_WRM(PTP_PIN_CFG(i), PTP_PIN_CFG_PIN_SELECT(i), PTP_PIN_CFG_PIN_SELECT_M);
    }

    /* Get the GPIO functionality information */
    if (vtss_state->init_conf.gpio_func_info_get != NULL) {
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_0, &ptp_gpio[0]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_1, &ptp_gpio[1]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_2, &ptp_gpio[2]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_3, &ptp_gpio[3]);
        rc += vtss_state->init_conf.gpio_func_info_get(NULL, VTSS_GPIO_FUNC_PTP_4, &ptp_gpio[4]);
        if (rc != VTSS_RC_OK) {
            VTSS_I("Not able to get valid GPIO functionality information");
        }
    } else {
        VTSS_I("gpio_func_info_get is NULL");
    }

    VTSS_MEMSET(gmii_delay, 0, sizeof(gmii_delay));
    VTSS_MEMSET(qsgmii_delay, 0, sizeof(qsgmii_delay));
    VTSS_MEMSET(sgmii_delay, 0, sizeof(sgmii_delay));
    VTSS_MEMSET(sgmii_2g5_delay, 0, sizeof(sgmii_2g5_delay));
    VTSS_MEMSET(swc_gmii_delay, 0, sizeof(swc_gmii_delay));
    VTSS_MEMSET(swc_gmii_2g5_delay, 0, sizeof(swc_gmii_2g5_delay));

    gmii_delay[2].rx = 146879;    gmii_delay[2].tx = 93300;
    gmii_delay[3].rx = 146879;    gmii_delay[3].tx = 93300;
    gmii_delay[5].rx = 138879;    gmii_delay[5].tx = 93294;
    gmii_delay[6].rx = 138879;    gmii_delay[6].tx = 93294;

    qsgmii_delay[0].rx = 120810;    qsgmii_delay[0].tx = 158009;
    qsgmii_delay[1].rx = 120810;    qsgmii_delay[1].tx = 158009;
    qsgmii_delay[2].rx = 120810;    qsgmii_delay[2].tx = 158009;
    qsgmii_delay[3].rx = 120810;    qsgmii_delay[3].tx = 158009;
    qsgmii_delay[4].rx = 120810;    qsgmii_delay[4].tx = 158009;
    qsgmii_delay[5].rx = 120810;    qsgmii_delay[5].tx = 158009;
    qsgmii_delay[6].rx = 120810;    qsgmii_delay[6].tx = 158009;
    qsgmii_delay[7].rx = 120810;    qsgmii_delay[7].tx = 158009;

    sgmii_delay[0].rx = 114733;    sgmii_delay[0].tx = 207688;
    sgmii_delay[1].rx = 114733;    sgmii_delay[1].tx = 207688;
    sgmii_delay[2].rx = 114733;    sgmii_delay[2].tx = 207688;
    sgmii_delay[3].rx = 114733;    sgmii_delay[3].tx = 207688;
    sgmii_delay[4].rx = 114733;    sgmii_delay[4].tx = 207688;

    sgmii_2g5_delay[2].rx = 45790;    sgmii_2g5_delay[2].tx = 82862;
    sgmii_2g5_delay[3].rx = 45790;    sgmii_2g5_delay[3].tx = 82862;
    sgmii_2g5_delay[4].rx = 45791;    sgmii_2g5_delay[4].tx = 83051;

    swc_gmii_delay[0].rx = 88070;    swc_gmii_delay[0].tx = 72045;
    swc_gmii_delay[1].rx = 88070;    swc_gmii_delay[1].tx = 72045;
    swc_gmii_delay[2].rx = 88070;    swc_gmii_delay[2].tx = 72045;
    swc_gmii_delay[3].rx = 88070;    swc_gmii_delay[3].tx = 72045;
    swc_gmii_delay[4].rx = 88070;    swc_gmii_delay[4].tx = 72045;
    swc_gmii_delay[5].rx = 88070;    swc_gmii_delay[5].tx = 72045;
    swc_gmii_delay[6].rx = 88070;    swc_gmii_delay[6].tx = 72045;
    swc_gmii_delay[7].rx = 88070;    swc_gmii_delay[7].tx = 72045;

    swc_gmii_2g5_delay[2].rx = 35065;    swc_gmii_2g5_delay[2].tx = 28876;
    swc_gmii_2g5_delay[3].rx = 35065;    swc_gmii_2g5_delay[3].tx = 28876;
    swc_gmii_2g5_delay[4].rx = 35065;    swc_gmii_2g5_delay[4].tx = 28876;

    /* Enable Phase detector on all ports for increased time stamping precision */
    for (i = 0; i < VTSS_CHIP_PORTS; i++) {
        REG_WRM(DEV_PHAD_CTRL(i, 0), DEV_PHAD_CTRL_PHAD_ENA(1) | DEV_PHAD_CTRL_DIV_CFG(3) | DEV_PHAD_CTRL_TWEAKS(1) | DEV_PHAD_CTRL_REALIGN_OFS(5) | DEV_PHAD_CTRL_LOCK_ACC(2),
                                     DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M | DEV_PHAD_CTRL_TWEAKS_M | DEV_PHAD_CTRL_REALIGN_OFS_M | DEV_PHAD_CTRL_LOCK_ACC_M);
        REG_WRM(DEV_PHAD_CTRL(i, 1), DEV_PHAD_CTRL_PHAD_ENA(1) | DEV_PHAD_CTRL_DIV_CFG(3) | DEV_PHAD_CTRL_TWEAKS(1) | DEV_PHAD_CTRL_REALIGN_OFS(5) | DEV_PHAD_CTRL_LOCK_ACC(2),
                                     DEV_PHAD_CTRL_PHAD_ENA_M | DEV_PHAD_CTRL_DIV_CFG_M | DEV_PHAD_CTRL_TWEAKS_M | DEV_PHAD_CTRL_REALIGN_OFS_M | DEV_PHAD_CTRL_LOCK_ACC_M);
    }

    // Disable PTP towards CPU
    for (i = VTSS_CHIP_PORT_CPU_0; i <= VTSS_CHIP_PORT_CPU_1; i++) {
        REG_WR(SYS_PTP_MODE_CFG(i, 0), SYS_PTP_MODE_CFG_PTP_MODE_VAL(3));
    }
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
        state->adjtimer_set = lan966x_ts_adjtimer_set;
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

        state->external_io_mode_set = lan966x_ts_external_io_mode_set;
        state->saved_timeofday_get = lan966x_ts_saved_timeofday_get;
        state->output_clock_edge_offset_get = lan966x_ts_output_clock_edge_offset_get;

        state->seq_cnt_get = lan966x_ts_seq_cnt_get;
        state->link_up = lan966x_ts_link_up;
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
