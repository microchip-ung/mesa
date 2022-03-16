// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_luton26_cil.h"

#if defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_FEATURE_TIMESTAMP)

/* - CIL functions ------------------------------------------------- */

#define HW_CLK_CNT_PR_SEC 250000000L
#define HW_NS_PR_SEC 1000000000L
#define HW_NS_PR_CLK_CNT (HW_NS_PR_SEC/HW_CLK_CNT_PR_SEC)

#define HW_CLK_50_MS (HW_CLK_CNT_PR_SEC/20)
#define HW_CLK_M950_MS (-HW_CLK_CNT_PR_SEC + HW_CLK_50_MS)
#define EXT_SYNC_INPUT_LATCH_LATENCY 3  /* subtracted from EXT_SYNC_CURRENT TIME */

#define SPEED_INDEX_10M   0
#define SPEED_INDEX_100M  1
#define SPEED_INDEX_1000M 2
#define SPEED_INDEX_2500M 3
#define SPEED_INDEX_MAX   4

#define L26_PTP_IO_PIN    0 // used as index in ptp_gpio
// L26 gpio configuration
static const u8 ptp_gpio[VTSS_TS_IO_ARRAY_SIZE] = {
    7
};
/*
 * Note: The values i have added to the table below ensures the correct path delay, byt the asymmetry may not be correct.
 */
static  const i32 latency_igr[SPEED_INDEX_MAX] = {
    [SPEED_INDEX_10M]   = 0,
    [SPEED_INDEX_100M]  = 537,
    [SPEED_INDEX_1000M] = 302,
    [SPEED_INDEX_2500M] = 0   /* Not used in L26 */
};

static  const i32 latency_egr[SPEED_INDEX_MAX] = {
    [SPEED_INDEX_10M]   = 0,
    [SPEED_INDEX_100M]  = 912,
    [SPEED_INDEX_1000M] = 112,
    [SPEED_INDEX_2500M] = 0    /* Not used in L26 */
};

static vtss_rc 
l26_ts_hw_timeofday_read(vtss_state_t   *vtss_state, 
                         u32            *tod_secs,
                         u32            *tod_nanosecs,
                         u64            *tc,
                         BOOL           reset)
{
    u32 tc_32;
    /* Latch PTP internal timers */
    L26_WR(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL, 
           VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_LATCH |
           VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TIMER_ENA |
           (reset ? VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TOD_RST : 0));

    L26_RD(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_DELAY, &tc_32);
    /* tc is returned as 16 bit fraction of nanoseconds */
    *tc = (u64)((u64)tc_32 << 16);
    L26_RD(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_SECS, tod_secs);
    L26_RD(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS, tod_nanosecs);
    if (*tod_nanosecs == 0) {
        ++*tod_secs; /* HW bug: the seconds counter is incremented one clock cycle after the ns counter wraps */
    }
    return VTSS_RC_OK;
}


static vtss_rc 
l26_ts_timeofday_get(vtss_state_t      *vtss_state, 
                     vtss_timestamp_t  *ts,
                     u64               *tc)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    u32 value;
    u32 value_ns;
    i32 x;

    VTSS_RC(l26_ts_hw_timeofday_read(vtss_state, &value, &value_ns, tc, FALSE));
    ts->sec_msb = 0; /* to be maintained in one sec interrupt */
    ts->seconds = conf->sec_offset + value;
    x = VTSS_X_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS(value_ns);
    /* DURING THE ADJUSTMENT PHASE THE ADJUST IS DONE IN sw */
    if (conf->awaiting_adjustment) {
        x -= conf->outstanding_corr;
        if (x < 0) {
            ts->seconds--;
            x += HW_CLK_CNT_PR_SEC;
        } else if (x >= HW_CLK_CNT_PR_SEC) {
            ts->seconds++;
            x -= HW_CLK_CNT_PR_SEC;
        }
    }
    ts->nanoseconds = x*HW_NS_PR_CLK_CNT;

    VTSS_D("ts->seconds: %u, ts->nanoseconds: %u", ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

static vtss_rc l26_ts_saved_timeofday_get(vtss_state_t *vtss_state, u32 io,
                                                vtss_timestamp_t *ts, u64 *tc)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    u32 value;
    u32 value_ns;
    i32 x;
    u32 cu,saved, deltat;

    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }

    VTSS_RC(l26_ts_hw_timeofday_read(vtss_state, &value, &value_ns, tc, FALSE));
    ts->sec_msb = 0; /* to be maintained in one sec interrupt */
    ts->seconds = conf->sec_offset + value;
    x = VTSS_X_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS(value_ns);
    /* DURING THE ADJUSTMENT PHASE THE ADJUST IS DONE IN sw */
    if (conf->awaiting_adjustment) {
        x -= conf->outstanding_corr;
        if (x < 0) {
            ts->seconds--;
            x += HW_CLK_CNT_PR_SEC;
        } else if (x >= HW_CLK_CNT_PR_SEC) {
            ts->seconds++;
            x -= HW_CLK_CNT_PR_SEC;
        }
    }
    ts->nanoseconds = x*HW_NS_PR_CLK_CNT;

    L26_RD(VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT,&cu);
    cu -= EXT_SYNC_INPUT_LATCH_LATENCY;
    saved =  cu * HW_NS_PR_CLK_CNT;
    deltat = (ts->nanoseconds > saved)? ts->nanoseconds-saved :ts->nanoseconds-saved + HW_NS_PR_SEC;
    ts->nanoseconds-=deltat;
    tc-=deltat;

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
 */
static vtss_rc
l26_ts_timeofday_offset_set(vtss_state_t *vtss_state, i32 offset)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    i32 corr;

    if (conf->awaiting_adjustment) {
        return VTSS_RC_ERROR;
     }
    conf->awaiting_adjustment = TRUE;
    conf->outstanding_adjustment = 0;
    
    corr = (offset/HW_NS_PR_CLK_CNT);
    
    if (corr > HW_CLK_50_MS) {
        --conf->sec_offset;
        conf->outstanding_adjustment = corr-1;
        conf->outstanding_corr = corr - HW_CLK_CNT_PR_SEC;
    } else if (corr < HW_CLK_M950_MS) {
        ++conf->sec_offset;
        conf->outstanding_adjustment = corr + 2*HW_CLK_CNT_PR_SEC-1;
        conf->outstanding_corr = corr + HW_CLK_CNT_PR_SEC;
    } else {
        conf->outstanding_corr = corr;
        conf->outstanding_adjustment = corr + HW_CLK_CNT_PR_SEC-1;
    }
    /* we wait until TOD_NANOSECS wraps */
    VTSS_D("offset = %d, adjust = %u, corr: %d", offset, conf->outstanding_adjustment, conf->outstanding_corr);
    return VTSS_RC_OK;
}


/*
 * Latch and reset the PTP timers in HW (the sec counter is reset)
 * The actual second counter is saved in SW.
 * The NS counter in hw (TOD_NANOSECS) has to be aligned with the ts.nanoseconds,
 * this is done by using the PTP_UPPER_LIMIT_1_TIME_ADJ:
 * This register can be used to change the one sec. period once, the period can 
 * be set to [0..268.435.455] periods of 4 ns = [0..1.073.741.820] ns.
 * alignment algorithm:
 *  (TOD_NANOSECS - ts.nanoseconds) > 50 ms => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds
 *    (TBD if this works, because the ADJ is < actual TOD_NANOSECS ??)
 *  50 ms > (TOD_NANOSECS - ts.nanoseconds) > -950 ms => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds + 1 sec
 *  -950 ms > (TOD_NANOSECS - ts.nanoseconds) => 
 *    PTP_UPPER_LIMIT_1_TIME_ADJ = TOD_NANOSECS - ts.nanoseconds + 2 sec
 * The second offset is adjusted accordingly.
 *
 */
static vtss_rc
l26_ts_timeofday_set(vtss_state_t *vtss_state, const vtss_timestamp_t *ts)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    i32 corr;
    u32 value;
    u32 value1;
    u64 value2 = 0;

    if (conf->awaiting_adjustment) {
        return VTSS_RC_ERROR;
    }

    /* Latch and reset PTP internal timers */
    VTSS_RC(l26_ts_hw_timeofday_read(vtss_state, &value1, &value, &value2, TRUE));
    conf->sec_offset = ts->seconds;
    VTSS_D("ts->seconds: %u, ts->nanoseconds: %u", ts->seconds, ts->nanoseconds);
    
    /* corr = PTP_NS - ts.ns */
    corr = value & VTSS_M_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS_PTP_TOD_NANOSECS;
    VTSS_RC(l26_ts_timeofday_offset_set(vtss_state, corr*HW_NS_PR_CLK_CNT - ts->nanoseconds));
    VTSS_D("PTP_TOD_SECS: %u, PTP_TOD_NANOSECS: %u, PTP_DELAY: %" PRIu64 "", conf->sec_offset , value, value2);
    return VTSS_RC_OK;
}

/*
 * When the time is set, the SW sec  counters are written. The HW ns clock is adjusted in the next 1 sec call. 
 */
static vtss_rc l26_ts_timeofday_set_delta(vtss_state_t *vtss_state,
                                          const vtss_timestamp_t *ts, BOOL negative)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    i32 corr;

    if (conf->awaiting_adjustment) {
        return VTSS_RC_ERROR;
    }
    if (ts->nanoseconds != 0) {
        if (negative) {
            corr = ts->nanoseconds;
        } else {
            corr = -(i32)ts->nanoseconds;
        }        
        VTSS_RC(l26_ts_timeofday_offset_set(vtss_state, corr));
    }
    if (negative) {
        conf->sec_offset -= ts->seconds;
    } else {
        conf->sec_offset += ts->seconds;
    }
    
    VTSS_D("ts->sec_msb: %u, ts->seconds: %u, ts->nanoseconds: %u", ts->sec_msb, ts->seconds, ts->nanoseconds);
    return VTSS_RC_OK;
}

/*
 * This function is called from interrupt, therefore the macros using vtss_state cannot be used.
 */
static u32 l26_ts_ns_cnt_get(vtss_inst_t inst)
{
    u32 value;

    /* read nanosec clock counter */
    (void)inst->init_conf.reg_read(0, VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT, &value);
    return VTSS_X_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT_PTP_CURRENT_TIME(value)*HW_NS_PR_CLK_CNT;
}


static vtss_rc
l26_ts_timeofday_one_sec(vtss_state_t *vtss_state)
{
    vtss_ts_conf_t *conf = &vtss_state->ts.conf;
    u32 value, value1;

    if (conf->awaiting_adjustment) {
        /* For debug: read the internal NS counter */
        L26_WR(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL, 
                    VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_LATCH |
                    VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TIMER_ENA);
        L26_RD(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS, &value);
        L26_RD(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_DELAY, &value1);
        VTSS_D("TOD_NANOSECS %u, PTP_DELAY %u", value, value1);

        if (conf->outstanding_adjustment != 0) {
            if (value > conf->outstanding_adjustment) {
                VTSS_D("Too large interrupt latency to adjust %u (*4ns)", value);
            } else {
                /*PTP_UPPER_LIMIT_1_TIME_ADJ = x */
                L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG, 
                       conf->outstanding_adjustment |
                       VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_SHOT);
                VTSS_D("onetime adjustment done %u", conf->outstanding_adjustment);
                conf->outstanding_adjustment = 0;
            }
        } else {
            conf->awaiting_adjustment = FALSE;
            VTSS_D("awaiting_adjustment cleared");
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc
    l26_ts_adjtimer_set(vtss_state_t *vtss_state)
{
    /* adj in units of 0,1 pbb */
    i32 adj = vtss_state->ts.conf.adj[0]/10L;
    u32 clk_adj = HW_CLK_CNT_PR_SEC;
    u32 sticky;
    /* CLK_ADJ = clock_rate/|adj|
    * CLK_ADJ_DIR = adj>0 ? Positive : Negative
    */
    if (adj != 0) {
        clk_adj = VTSS_LABS((HW_NS_PR_SEC)/adj)-1;
    }
    if (clk_adj > HW_CLK_CNT_PR_SEC) clk_adj = HW_CLK_CNT_PR_SEC;
    
    if ((adj != 0)) {
        clk_adj |= VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_ENA;
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ADJ_ENA);
    } else {
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ADJ_ENA);
    }
    if (adj < 0) {
        clk_adj |= VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_DIR;
    } 
    //clk_adj |= VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_UPD;
    L26_RD(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT,&sticky);
    //if (sticky & VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY) {
    //    L26_WR(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT, VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY);
    //} else {
    //    VTSS_E("more than one update pr sec is performed");
    //}
    L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG, clk_adj);
    
    VTSS_D("adj: %d, CLK_ACJ_CFG: %x", adj, clk_adj);
    return VTSS_RC_OK;
}

static vtss_rc
    l26_ts_freq_offset_get(vtss_state_t *vtss_state, i32 *const adj)
{
    i32 offset; /* frequency offset in clock counts pr sec */
    u32 cu;
    L26_RD(VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT,&cu);
    cu -= EXT_SYNC_INPUT_LATCH_LATENCY;
    offset = VTSS_X_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT_EXT_SYNC_CURRENT_TIME(cu) - HW_CLK_CNT_PR_SEC;
    /* convert to units of 0,1 ppb */
    *adj = HW_NS_PR_CLK_CNT*10*offset;
    
    
    VTSS_D("cu: %u adj: %d", cu, *adj);
    return VTSS_RC_OK;
}


static vtss_rc
l26_ts_external_clock_mode_set(vtss_state_t *vtss_state)
{
    vtss_ts_ext_clock_mode_t *conf = &vtss_state->ts.conf.ext_clock_mode;
    u32 dividers;
    u32 high_div;
    u32 low_div;

    if (!conf->enable && conf->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE) {
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA);
        /* disable clock output */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
        /* disable alternate 1 for GPIO_7 (clock output). */
        (void) vtss_l26_gpio_mode(vtss_state, 0, ptp_gpio[L26_PTP_IO_PIN], VTSS_GPIO_IN);
    } else {
        /* enable alternate 1 for GPIO_7 (clock output). */
        (void) vtss_l26_gpio_mode(vtss_state, 0, ptp_gpio[L26_PTP_IO_PIN], VTSS_GPIO_ALT_0);

        if (conf->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT) {
            /* 1 pps output enabled */
            L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
            L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
            L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
        } else if (conf->one_pps_mode == TS_EXT_CLOCK_MODE_ONE_PPS_INPUT) {
            /* 1 pps input enabled */
            L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
            L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
            L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                            VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
        } else {
            /* clock frequency output */
            L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, 
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
            /* set dividers; enable clock output. */
            dividers = (HW_CLK_CNT_PR_SEC/(conf->freq));
            high_div = (dividers/2)-1;
            low_div =  ((dividers+1)/2)-1;
            L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG, high_div  &
                        VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD);
            L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG, low_div  &
                        VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD);
            L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc l26_ts_external_io_mode_set(vtss_state_t *vtss_state, u32 io) {
    vtss_ts_ext_io_mode_t *ext_io_mode;
    if (io >= VTSS_TS_IO_ARRAY_SIZE) {
        VTSS_E("invalid io pin: %u", io);
        return VTSS_RC_ERROR;
    }
    ext_io_mode = &vtss_state->ts.io_cfg[io];
    ext_io_mode->domain = 0;
    u32 dividers;
    u32 high_div;
    u32 low_div;
    VTSS_D("io pin %d, pin cfg: %u, domain: %u, freq: %u", io, ext_io_mode->pin, ext_io_mode->domain, ext_io_mode->freq);

    if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_DISABLE) {
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA);
        /* disable clock output */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);

        (void) vtss_l26_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_IN);
    } else {
        (void) vtss_l26_gpio_mode(vtss_state, 0, ptp_gpio[io], VTSS_GPIO_ALT_0);
    }
    if (ext_io_mode->pin == TS_EXT_IO_MODE_WAVEFORM_OUTPUT) {
     /* clock frequency output */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
     /* set dividers; enable clock output. */
        dividers = (HW_CLK_CNT_PR_SEC/(ext_io_mode->freq));
        high_div = (dividers/2)-1;
        low_div =  ((dividers+1)/2)-1;
        L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG, high_div  &
                        VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG_GEN_EXT_CLK_HIGH_PERIOD);
        L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG, low_div  &
                        VTSS_M_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG_GEN_EXT_CLK_LOW_PERIOD);
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
    } else if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_OUTPUT) {
        /* 1 pps output enabled */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                     VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                    VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);

    } else  if (ext_io_mode->pin == TS_EXT_IO_MODE_ONE_PPS_SAVE) {
         /* 1 pps input enabled */
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG_GEN_EXT_CLK_ENA);
        L26_WRM_CLR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_SEL |
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_OUTP_ENA);
        L26_WRM_SET(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG,
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_SEL |
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_INP_ENA |
                        VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_EXT_SYNC_ENA);
    }
    return VTSS_RC_OK;
}

static vtss_rc
l26_ts_ingress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 rx_delay = VTSS_INTERVAL_NS(conf->ingress_latency)/HW_NS_PR_CLK_CNT;
    rx_delay += (conf->default_igr_latency/HW_NS_PR_CLK_CNT);
    L26_WRM(VTSS_SYS_PTP_PTP_CFG(VTSS_CHIP_PORT(port_no)), 
            VTSS_F_SYS_PTP_PTP_CFG_IO_RX_DELAY(rx_delay), 
            VTSS_M_SYS_PTP_PTP_CFG_IO_RX_DELAY);
    return VTSS_RC_OK;
}

static vtss_rc
l26_ts_p2p_delay_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_D("Not to be used,a d L26 only supports up to 1 us p2pdelay");
    return VTSS_RC_OK;
}

static vtss_rc
l26_ts_egress_latency_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_ts_port_conf_t *conf = &vtss_state->ts.port_conf[port_no];
    i32 tx_delay = VTSS_INTERVAL_NS(conf->egress_latency)/HW_NS_PR_CLK_CNT;
    tx_delay += (conf->default_egr_latency/HW_NS_PR_CLK_CNT);
    L26_WRM(VTSS_SYS_PTP_PTP_CFG(VTSS_CHIP_PORT(port_no)), 
            VTSS_F_SYS_PTP_PTP_CFG_IO_TX_DELAY(tx_delay), 
            VTSS_M_SYS_PTP_PTP_CFG_IO_TX_DELAY);
    return VTSS_RC_OK;
}

static vtss_rc
l26_ts_operation_mode_set(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return VTSS_RC_ERROR;
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

static vtss_rc 
l26_ts_timestamp_get(vtss_state_t *vtss_state)
{
    u32 value;
    u32 delay;
    u32 tx_port;
    u32 mess_id;
    /* PTP_STATUS */
    L26_RD(VTSS_SYS_PTP_PTP_STATUS, &value);
    while (value & VTSS_F_SYS_PTP_PTP_STATUS_PTP_MESS_VLD) {
        L26_RD(VTSS_SYS_PTP_PTP_DELAY, &delay);
        tx_port = VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_TXPORT(value);
        tx_port = api_port(vtss_state, tx_port);
        mess_id = VTSS_X_SYS_PTP_PTP_STATUS_PTP_MESS_ID(value);
        if (mess_id >= VTSS_TS_ID_SIZE) {
            VTSS_D("invalid mess_id (%u)", mess_id);
        } else {
            if (tx_port < VTSS_PORT_ARRAY_SIZE) {
                vtss_state->ts.status[mess_id].tx_tc[tx_port] = (u64)delay << 16; // 0-15 bits are meant for fractional nano seconds.
                vtss_state->ts.status[mess_id].tx_id[tx_port] = mess_id;
                vtss_state->ts.status[mess_id].valid_mask |= 1LL<<tx_port;
            } else if (tx_port == VTSS_CHIP_PORT_CPU) {
                vtss_state->ts.status[mess_id].rx_tc = delay;
                vtss_state->ts.status[mess_id].rx_tc_valid = TRUE;
            } else {
                VTSS_I("invalid port (%u)", tx_port);
            }
        }
        VTSS_D("value %u, delay %u, tx_port %u, mess_id %u", value, delay, tx_port, mess_id);
        L26_WR(VTSS_SYS_PTP_PTP_NXT, VTSS_F_SYS_PTP_PTP_NXT_PTP_NXT);
        L26_RD(VTSS_SYS_PTP_PTP_STATUS, &value);
    }
    return VTSS_RC_OK;
}



static vtss_rc 
l26_ts_timestamp_id_release(vtss_state_t *vtss_state, u32 ts_id)
{
    /* Clear bit corresponding to ts_id */
    if (ts_id <TS_IDS_RESERVED_FOR_SW) {
        vtss_state->ts.conf.sw_ts_id_res[ts_id] = 0;
    } else if (ts_id <=31) {
        L26_WR(VTSS_ANA_ANA_TABLES_PTP_ID_LOW, VTSS_BIT(ts_id));
    } else if (ts_id <=63) {
        L26_WR(VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, VTSS_BIT(ts_id-32));
    } else {
        VTSS_D("invalid ts_id %d", ts_id);
    }
    return VTSS_RC_OK;
}

/*
* Signal port status change (used to detect and compensate for the internal ingress and egress latencies)
*/
static vtss_rc l26_ts_status_change(vtss_state_t         *vtss_state,
                                    const vtss_port_no_t port_no)
{
    vtss_rc rc = VTSS_RC_OK, rc2;
    VTSS_D("port status change %d", port_no);
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    u32 speed_index = speed == VTSS_SPEED_10M ? SPEED_INDEX_10M : speed == VTSS_SPEED_100M ? SPEED_INDEX_100M :
                      speed == VTSS_SPEED_1G ? SPEED_INDEX_1000M : speed == VTSS_SPEED_2500M ? SPEED_INDEX_2500M : SPEED_INDEX_MAX;
    if (speed == VTSS_SPEED_UNDEFINED) {
        vtss_state->ts.port_conf[port_no].default_igr_latency = 0;
        vtss_state->ts.port_conf[port_no].default_egr_latency = 0;
    } else if (speed_index < SPEED_INDEX_MAX) {
        vtss_state->ts.port_conf[port_no].default_igr_latency = latency_igr[speed_index];
        vtss_state->ts.port_conf[port_no].default_egr_latency = latency_egr[speed_index];
    } else {
        VTSS_E("invalid port speed %u on port_no %u", speed, port_no);
        return VTSS_RC_ERROR;
    }
    VTSS_D("port_no %d, igr_latency %d, egr_latency %d", port_no, vtss_state->ts.port_conf[port_no].default_igr_latency, vtss_state->ts.port_conf[port_no].default_egr_latency);
    rc = l26_ts_ingress_latency_set(vtss_state, port_no);
    rc2 = l26_ts_egress_latency_set(vtss_state, port_no);
    if (rc == VTSS_RC_OK) {
        rc = rc2;
    }
    return rc;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc l26_debug_ts(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info)
{
    u32  value;
    u32  port;
    char buf[32];

    /* DEVCPU_GCB: PTP_TIMER */
    vtss_l26_debug_reg_header(pr, "GCB:PTP_TIMER");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_SECS, "PTP_TOD_SECS");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TOD_NANOSECS, "PTP_TOD_NANOSECS");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_DELAY, "PTP_DELAY");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL, "PTP_TIMER_CTRL");
    /* DEVCPU_GCB: PTP_CFG */
    vtss_l26_debug_reg_header(pr, "GCB:PTP_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, "PTP_MISC_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_CFG, "PTP_UPPER_LIMIT_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_PTP_UPPER_LIMIT_1_TIME_ADJ_CFG, "PTP_UPPER_LIMIT_1_TIME_ADJ_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_PTP_SYNC_INTR_ENA_CFG, "PTP_SYNC_INTR_ENA_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_HIGH_PERIOD_CFG, "GEN_EXT_CLK_HIGH_PERIOD_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_LOW_PERIOD_CFG, "GEN_EXT_CLK_LOW_PERIOD_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_GEN_EXT_CLK_CFG, "GEN_EXT_CLK_CFG");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG, "CLK_ADJ_CFG");
    /* DEVCPU_GCB: PTP_STAT */
    vtss_l26_debug_reg_header(pr, "GCB:PTP_STAT");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_STAT_PTP_CURRENT_TIME_STAT, "PTP_CURRENT_TIME_STAT");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_DEVCPU_GCB_PTP_STAT_EXT_SYNC_CURRENT_TIME_STAT, "EXT_SYNC_CURRENT_TIME_STAT");

    L26_RD(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT, &value);
    L26_WR(VTSS_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT, value);
    vtss_debug_print_sticky(pr, "CLK_ADJ_UPD_STICKY", value, VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_CLK_ADJ_UPD_STICKY);
    vtss_debug_print_sticky(pr, "EXT_SYNC_CURRENT_TIME_STICKY", value, VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_EXT_SYNC_CURRENT_TIME_STICKY);
    vtss_debug_print_sticky(pr, "SYNC_STAT", value, VTSS_F_DEVCPU_GCB_PTP_STAT_PTP_EVT_STAT_SYNC_STAT);
    
    /* SYS_PORT:PTP */
    vtss_l26_debug_reg_header(pr, "SYS:PORT:PTP");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_STATUS, "PTP_STATUS");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_DELAY, "PTP_DELAY");
    for (port = 0; port <= VTSS_CHIP_PORTS; port++) {
        VTSS_SPRINTF(buf, "PTP_CFG(%u)", port);
        vtss_l26_debug_reg(vtss_state, pr, VTSS_SYS_PTP_PTP_CFG(port), buf);
    }

    /* ANA:: */
    vtss_l26_debug_reg_header(pr, "ANA::PTP");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, "PTP_ID_HIGH");
    vtss_l26_debug_reg(vtss_state, pr, VTSS_ANA_ANA_TABLES_PTP_ID_LOW, "PTP_ID_LOW");
    
    
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_l26_ts_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_TS, l26_debug_ts, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc l26_ts_init(vtss_state_t *vtss_state)
{
    L26_WR(VTSS_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL, 
           VTSS_F_DEVCPU_GCB_PTP_TIMERS_PTP_TIMER_CTRL_PTP_TIMER_ENA);
    L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG, VTSS_F_DEVCPU_GCB_PTP_CFG_PTP_MISC_CFG_PTP_ENA);
    L26_WR(VTSS_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG,  HW_CLK_CNT_PR_SEC |
            VTSS_F_DEVCPU_GCB_PTP_CFG_CLK_ADJ_CFG_CLK_ADJ_UPD);
    /* release all timestamp id's except those that are reserved for SW*/
    L26_WR(VTSS_ANA_ANA_TABLES_PTP_ID_LOW, VTSS_ENCODE_BITMASK(TS_IDS_RESERVED_FOR_SW,32-TS_IDS_RESERVED_FOR_SW));
    L26_WR(VTSS_ANA_ANA_TABLES_PTP_ID_HIGH, 0xffffffff); /* assuming <32 are reserved for SW */

    return VTSS_RC_OK;
}

static vtss_rc l26_ts_domain_timeofday_get(vtss_state_t *vtss_state, u32 domain, vtss_timestamp_t *ts, u64 *tc)
{
    if (domain == 0) {
        return l26_ts_timeofday_get(vtss_state, ts, tc);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc l26_ts_domain_timeofday_set(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts)
{
    if (domain == 0) {
        return l26_ts_timeofday_set(vtss_state, ts);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc l26_ts_domain_timeofday_set_delta(vtss_state_t *vtss_state, u32 domain, const vtss_timestamp_t *ts, BOOL negative)
{
    if (domain == 0) {
        return l26_ts_timeofday_set_delta(vtss_state, ts, negative);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc l26_ts_domain_timeofday_offset_set(vtss_state_t *vtss_state, u32 domain, i32 offset)
{
    if (domain == 0) {
        return l26_ts_timeofday_offset_set(vtss_state, offset);
    } else {
        return VTSS_RC_ERROR;
    }
}

static vtss_rc l26_ts_domain_adjtimer_set(vtss_state_t *vtss_state, u32 domain)
{
    if (domain == 0) {
        return l26_ts_adjtimer_set(vtss_state);
    } else {
        return VTSS_RC_ERROR;
    }
}


vtss_rc vtss_l26_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_ts_state_t *state = &vtss_state->ts;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->timeofday_get = l26_ts_timeofday_get;
        state->timeofday_set = l26_ts_timeofday_set;
        state->timeofday_set_delta = l26_ts_timeofday_set_delta;
        state->timeofday_offset_set = l26_ts_timeofday_offset_set;
        state->ns_cnt_get = l26_ts_ns_cnt_get;
        state->timeofday_one_sec = l26_ts_timeofday_one_sec;
        state->adjtimer_set = l26_ts_adjtimer_set;
        state->freq_offset_get = l26_ts_freq_offset_get;
        state->external_clock_mode_set = l26_ts_external_clock_mode_set;
        state->external_io_mode_set = l26_ts_external_io_mode_set;
        state->saved_timeofday_get = l26_ts_saved_timeofday_get;
        state->ingress_latency_set = l26_ts_ingress_latency_set;
        state->p2p_delay_set = l26_ts_p2p_delay_set;
        state->egress_latency_set = l26_ts_egress_latency_set;
        state->operation_mode_set = l26_ts_operation_mode_set;
        state->timestamp_get = l26_ts_timestamp_get;
        state->timestamp_id_release = l26_ts_timestamp_id_release;
        state->status_change = l26_ts_status_change;
        /* domain specific functions added for new architectures */
        state->domain_timeofday_get = l26_ts_domain_timeofday_get;
        state->domain_timeofday_set = l26_ts_domain_timeofday_set;
        state->domain_timeofday_set_delta = l26_ts_domain_timeofday_set_delta;
        state->domain_timeofday_offset_set = l26_ts_domain_timeofday_offset_set;
        state->domain_adjtimer_set = l26_ts_domain_adjtimer_set;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(l26_ts_init(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_TIMESTAMP */
#endif /* VTSS_ARCH_LUTON26 */
