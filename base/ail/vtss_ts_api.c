// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_TS
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_TIMESTAMP)

#define HW_NS_PR_SEC 1000000000L

vtss_rc vtss_timestampAddSec(vtss_timestamp_t *ts)
{
    if (ts->seconds == 0xffffffff) {
        ts->sec_msb++;
        ts->seconds = 0;
    } else {
        ts->seconds++;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_timestampSubSec(vtss_timestamp_t *ts)
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
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds = HW_NS_PR_SEC-1;
    } else {
        ts->nanoseconds--;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_timestampSub(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_sub)
{
    if (ts->nanosecondsfrac < ts_sub->nanosecondsfrac) {
        VTSS_RC(timestampSubNanosec(ts));
    }
    ts->nanosecondsfrac -= ts_sub->nanosecondsfrac;

    if (ts->nanoseconds < ts_sub->nanoseconds) {
        VTSS_RC(vtss_timestampSubSec(ts));
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

vtss_rc vtss_timestampAdd(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_add)
{
    ts->nanosecondsfrac += ts_add->nanosecondsfrac;
    if (ts->nanosecondsfrac < ts_add->nanosecondsfrac) {
        ts->nanoseconds++;
    }

    ts->nanoseconds += ts_add->nanoseconds;
    if (ts->nanoseconds >= HW_NS_PR_SEC) {
        VTSS_RC(vtss_timestampAddSec(ts));
        ts->nanoseconds -= HW_NS_PR_SEC;
    }

    ts->seconds += ts_add->seconds;
    if (ts->seconds < ts_add->seconds) {
        ts->sec_msb++;
    }

    ts->sec_msb += ts_add->sec_msb;
    return VTSS_RC_OK;
}

vtss_rc vtss_timestampAddNano(vtss_timestamp_t *ts, u64 nano)
{
    u64 seconds = nano / HW_NS_PR_SEC;
    u32 nano_30 = nano % HW_NS_PR_SEC;
    u32 sec_32 = (u32)seconds;
    u16 sec_msb = seconds >> 32;

    ts->nanoseconds += nano_30;
    if (ts->nanoseconds >= HW_NS_PR_SEC) {
        VTSS_RC(vtss_timestampAddSec(ts));
        ts->nanoseconds -= HW_NS_PR_SEC;
    }

    /* First 32 bits of seconds add to seconds */
    ts->seconds += sec_32;
    if (ts->seconds < seconds) {
        ts->sec_msb++;
    }

    /* Above 32 bits of seconds add to MSB seconds */
    ts->sec_msb += sec_msb;

    return VTSS_RC_OK;
}

vtss_rc vtss_timestampSubNano(vtss_timestamp_t *ts, u64 nano)
{
    u64 seconds = nano / HW_NS_PR_SEC;
    u32 nano_30 = nano % HW_NS_PR_SEC;
    u32 sec_32 = (u32)seconds;
    u16 sec_msb = seconds >> 32;

    if (ts->nanoseconds < nano_30) {
        VTSS_RC(vtss_timestampSubSec(ts));
        ts->nanoseconds += HW_NS_PR_SEC;
    }
    ts->nanoseconds -= nano_30;

    if (ts->seconds < sec_32) {
        ts->sec_msb--;
    }
    ts->seconds -= sec_32;

    ts->sec_msb -= sec_msb;

    return VTSS_RC_OK;
}

BOOL vtss_timestampLarger(const vtss_timestamp_t *ts1, const vtss_timestamp_t *ts2)
{
    if (ts1->sec_msb > ts2->sec_msb) {
        return TRUE;
    }
    if (ts1->sec_msb < ts2->sec_msb) {
        return FALSE;
    }
    if (ts1->seconds > ts2->seconds) {
        return TRUE;
    }
    if (ts1->seconds < ts2->seconds) {
        return FALSE;
    }
    if (ts1->nanoseconds > ts2->nanoseconds) {
        return TRUE;
    }
    if (ts1->nanoseconds < ts2->nanoseconds) {
        return FALSE;
    }
    if (ts1->nanosecondsfrac > ts2->nanosecondsfrac) {
        return TRUE;
    }
    if (ts1->nanosecondsfrac < ts2->nanosecondsfrac) {
        return FALSE;
    }
    return FALSE;
}

/* Get the current time in a Timestamp format, and the corresponding time counter */
vtss_rc vtss_ts_timeofday_get(const vtss_inst_t             inst,
                              vtss_timestamp_t              *const ts,
                              u64                           *const tc)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.timeofday_get,ts,tc);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the current raw time (without compensation for outstanding adjustments) in a Timestamp format, and the corresponding time counter */
vtss_rc vtss_ts_timeofday_raw(const vtss_inst_t             inst,
                              vtss_timestamp_t              *const ts,
                              u64                           *const tc)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.timeofday_raw,ts,tc);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the current time in a Timestamp format, and the corresponding time counter - only to be called from within another API function */
vtss_rc _vtss_ts_domain_timeofday_get(const vtss_inst_t            inst,
                                      const u32                    domain,
                                      vtss_timestamp_t             *const ts,
                                      u64                          *const tc)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.domain_timeofday_get, domain, ts, tc);
    }

    return rc;
}

/* Get the current time in a Timestamp format, and the corresponding time counter */
vtss_rc vtss_ts_domain_timeofday_get(const vtss_inst_t             inst,
                                     const u32                     domain,
                                     vtss_timestamp_t              *const ts,
                                     u64                           *const tc)
{
    vtss_rc rc;

    VTSS_ENTER();
    rc = _vtss_ts_domain_timeofday_get(inst, domain, ts, tc);
    VTSS_EXIT();

    return rc;
}

/* Get the time at the next 1PPS pulse edge in a Timestamp format. */
vtss_rc vtss_ts_timeofday_next_pps_get(const vtss_inst_t             inst,
                                       vtss_timestamp_t                     *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.timeofday_next_pps_get,ts);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the time at the previous 1PPS pulse edge in a Timestamp format. */
vtss_rc vtss_ts_timeofday_prev_pps_get(const vtss_inst_t             inst,
                                       vtss_timestamp_t                     *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.timeofday_prev_pps_get,ts);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the time at the next 1PPS pulse edge in a Timestamp format. */
vtss_rc vtss_ts_domain_timeofday_next_pps_get(const vtss_inst_t             inst,
                                              const u32                     domain,
                                              vtss_timestamp_t              *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.domain_timeofday_next_pps_get, domain, ts);
    }
    VTSS_EXIT();
    return rc;
}

/* Set the current time in a Timestamp format */
vtss_rc vtss_ts_timeofday_set(const vtss_inst_t             inst,
                              const vtss_timestamp_t               *ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.timeofday_set,ts);
    }
    VTSS_EXIT();
    return rc;
}

/* Set the current time in a Timestamp format */
vtss_rc vtss_ts_domain_timeofday_set(const vtss_inst_t             inst,
                                     const u32                     domain,
                                     const vtss_timestamp_t        *ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.domain_timeofday_set, domain, ts);
    }
    VTSS_EXIT();
    return rc;
}

/* Set delta from the current time in a Timestamp format */
vtss_rc vtss_ts_timeofday_set_delta(const vtss_inst_t       inst,
                              const vtss_timestamp_t         *ts,
                              BOOL                      negative)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.timeofday_set_delta,ts, negative);
    }
    VTSS_EXIT();
    return rc;
}

/* Set delta from the current time in a Timestamp format */
vtss_rc vtss_ts_domain_timeofday_set_delta(const vtss_inst_t        inst,
                                           const u32                domain,
                                           const vtss_timestamp_t   *ts,
                                           BOOL                     negative)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.domain_timeofday_set_delta, domain, ts, negative);
    }
    VTSS_EXIT();
    return rc;
}

/* Subtract offset from the current time */
vtss_rc vtss_ts_timeofday_offset_set(const vtss_inst_t          inst,
                                     const i32                  offset)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.timeofday_offset_set,offset);
    }
    VTSS_EXIT();
    return rc;
}

/* Subtract offset from the current time */
vtss_rc vtss_ts_domain_timeofday_offset_set(const vtss_inst_t          inst,
                                            const u32                  domain,
                                            const i32                  offset)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.domain_timeofday_offset_set, domain, offset);
    }
    VTSS_EXIT();
    return rc;
}



/* Do the one sec administration in the Timestamp function */
vtss_rc vtss_ts_adjtimer_one_sec(const vtss_inst_t             inst,
                                 BOOL                           *const ongoing_adjustment)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->ts.conf.outstanding_corr > VTSS_HW_TIME_MAX_FINE_ADJ || vtss_state->ts.conf.outstanding_corr < -VTSS_HW_TIME_MAX_FINE_ADJ) {
            *ongoing_adjustment = vtss_state->ts.conf.awaiting_adjustment;
        } else {
            *ongoing_adjustment = FALSE;
        }
        rc = VTSS_FUNC_COLD_0(ts.timeofday_one_sec);
    }
    VTSS_EXIT();
    return rc;
}

/* check if clock adjustment is ongoing */
vtss_rc vtss_ts_ongoing_adjustment(const vtss_inst_t           inst,
                                   BOOL                        *const ongoing_adjustment)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (vtss_state->ts.conf.outstanding_corr > VTSS_HW_TIME_MAX_FINE_ADJ || vtss_state->ts.conf.outstanding_corr < -VTSS_HW_TIME_MAX_FINE_ADJ) {
            *ongoing_adjustment = vtss_state->ts.conf.awaiting_adjustment;
        } else {
            *ongoing_adjustment = FALSE;
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Adjust the clock timer ratio */
vtss_rc vtss_ts_adjtimer_set(const vtss_inst_t              inst,
                             const i32                      adj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->ts.conf.adj[0] = adj;
        rc = VTSS_FUNC_COLD_0(ts.adjtimer_set);
    }
    VTSS_EXIT();
    return rc;
}

/* Get Adjust the clock timer ratio */
vtss_rc vtss_ts_adjtimer_get(const vtss_inst_t              inst,
                             i32                            *const adj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *adj = vtss_state->ts.conf.adj[0];
    }
    VTSS_EXIT();
    return rc;
}

/* Adjust the clock timer ratio */
vtss_rc vtss_ts_domain_adjtimer_set(const vtss_inst_t              inst,
                                    const u32                      domain,
                                    const i32                      adj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->ts.conf.adj[domain] = adj;
        rc = VTSS_FUNC_COLD(ts.domain_adjtimer_set, domain);
    }
    VTSS_EXIT();
    return rc;
}

/* Get Adjust the clock timer ratio */
vtss_rc vtss_ts_domain_adjtimer_get(const vtss_inst_t              inst,
                                    const u32                      domain,
                                    i32                            *const adj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *adj = vtss_state->ts.conf.adj[domain];
    }
    VTSS_EXIT();
    return rc;
}

/* Get get the clock internal timer frequency offset, compared to external clock input. */
vtss_rc vtss_ts_freq_offset_get(const vtss_inst_t              inst,
                                 i32                            *const adj)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.freq_offset_get, adj);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the external clock mode. */
vtss_rc vtss_ts_external_clock_mode_get(
                                const vtss_inst_t           inst,
                                vtss_ts_ext_clock_mode_t         *const ext_clock_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *ext_clock_mode = vtss_state->ts.conf.ext_clock_mode;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the external clock mode. */
vtss_rc vtss_ts_external_clock_mode_set(
                                const vtss_inst_t           inst,
                                const vtss_ts_ext_clock_mode_t   *const ext_clock_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->ts.conf.ext_clock_mode = *ext_clock_mode;
#if defined(VTSS_ARCH_OCELOT)
        rc = VTSS_FUNC_COLD(ts.external_clock_mode_set,1);
#else
        rc = VTSS_FUNC_COLD_0(ts.external_clock_mode_set);
#endif
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ts_external_clock_saved_get(
    const vtss_inst_t           inst,
    u32    *const               saved)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.external_clock_saved_get, saved);
    }
    VTSS_EXIT();
    return rc;
}


#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
vtss_rc vtss_ts_alt_clock_saved_get(
    const vtss_inst_t           inst,
    u64    *const               saved)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.alt_clock_saved_get, saved);
    }
    VTSS_EXIT();
    return rc;
}
                                       
#if defined(VTSS_ARCH_OCELOT)
vtss_rc vtss_ts_alt_clock_saved_timeofday_get(const vtss_inst_t     inst,
                                    vtss_timestamp_t  *const        ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.alt_clock_saved_timeofday_get, ts);
    }
    VTSS_EXIT();
    return rc;
}
#endif //defined(VTSS_ARCH_OCELOT)

/* Get the alternative external clock mode. */
vtss_rc vtss_ts_alt_clock_mode_get(
    const vtss_inst_t              inst,
    vtss_ts_alt_clock_mode_t       *const alt_clock_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *alt_clock_mode = vtss_state->ts.conf.alt_clock_mode;
    }
    VTSS_EXIT();
    return rc;
}
                                       
/* Set the alternative external clock mode. */
vtss_rc vtss_ts_alt_clock_mode_set(
    const vtss_inst_t              inst,
    const vtss_ts_alt_clock_mode_t *const alt_clock_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->ts.conf.alt_clock_mode = *alt_clock_mode;
        rc = VTSS_FUNC_COLD_0(ts.alt_clock_mode_set);
    }
    VTSS_EXIT();
    return rc;
}
                                       
/* Set the time at the next 1PPS pulse edge in a Timestamp format. */
vtss_rc vtss_ts_timeofday_next_pps_set(const vtss_inst_t       inst,
                                       const vtss_timestamp_t         *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_COLD(ts.timeofday_next_pps_set, ts);
    }
    VTSS_EXIT();
    return rc;
}

#endif /* defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) */

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
/*
 * Get the external io mode.
 */
vtss_rc vtss_ts_external_io_mode_get(
                                const vtss_inst_t           inst,
                                const u32                   io,
                                vtss_ts_ext_io_mode_t    *const ext_io_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (io < VTSS_TS_IO_ARRAY_SIZE) {
            *ext_io_mode = vtss_state->ts.io_cfg[io];
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

/*
 * Set the external io mode.
 */
vtss_rc vtss_ts_external_io_mode_set(
                                const vtss_inst_t              inst,
                                const u32                      io,
                                const vtss_ts_ext_io_mode_t    *const ext_io_mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (io < VTSS_TS_IO_ARRAY_SIZE) {
            vtss_state->ts.io_cfg[io] = *ext_io_mode;
            rc = VTSS_FUNC_COLD(ts.external_io_mode_set,io);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ts_saved_timeofday_get(const vtss_inst_t               inst,
                                    const u32                       io,
                                    vtss_timestamp_t                *const ts,
                                    u64                             *const tc)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (io < VTSS_TS_IO_ARRAY_SIZE) {
            rc = VTSS_FUNC_COLD(ts.saved_timeofday_get,io, ts, tc);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ts_output_clock_edge_offset_get(const vtss_inst_t inst,
                                             const u32    io,
                                             u32               *const offset)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (io < VTSS_TS_IO_ARRAY_SIZE) {
            rc = VTSS_FUNC_COLD(ts.output_clock_edge_offset_get, io, offset);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

/* Set the ingress latency */
vtss_rc vtss_ts_ingress_latency_set(const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    const vtss_timeinterval_t             *const ingress_latency)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ts.port_conf[port_no].ingress_latency = *ingress_latency;
        rc = VTSS_FUNC_COLD(ts.ingress_latency_set,port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the ingress latency */
vtss_rc vtss_ts_ingress_latency_get(const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    vtss_timeinterval_t                   *const ingress_latency)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *ingress_latency = vtss_state->ts.port_conf[port_no].ingress_latency;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the P2P delay */
vtss_rc vtss_ts_p2p_delay_set(const vtss_inst_t              inst,
                              const vtss_port_no_t           port_no,
                              const vtss_timeinterval_t             *const p2p_delay)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ts.port_conf[port_no].p2p_delay = *p2p_delay;
        rc = VTSS_FUNC_COLD(ts.p2p_delay_set,port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the P2P delay */
vtss_rc vtss_ts_p2p_delay_get(const vtss_inst_t              inst,
                              const vtss_port_no_t           port_no,
                              vtss_timeinterval_t                   *const p2p_delay)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *p2p_delay = vtss_state->ts.port_conf[port_no].p2p_delay;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the egress latency */
vtss_rc vtss_ts_egress_latency_set(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   const vtss_timeinterval_t             *const egress_latency)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ts.port_conf[port_no].egress_latency = *egress_latency;
        rc = VTSS_FUNC_COLD(ts.egress_latency_set,port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the egress latency */
vtss_rc vtss_ts_egress_latency_get(const vtss_inst_t        inst,
                                   const vtss_port_no_t     port_no,
                                   vtss_timeinterval_t             *const egress_latency)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *egress_latency = vtss_state->ts.port_conf[port_no].egress_latency;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the delay asymmetry */
vtss_rc vtss_ts_delay_asymmetry_set(const vtss_inst_t           inst,
                                   const vtss_port_no_t         port_no,
                                   const vtss_timeinterval_t    *const delay_asymmetry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->ts.port_conf[port_no].delay_asymmetry = *delay_asymmetry;
        rc = VTSS_FUNC_COLD(ts.delay_asymmetry_set,port_no);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the delay asymmetry */
vtss_rc vtss_ts_delay_asymmetry_get(const vtss_inst_t           inst,
                                   const vtss_port_no_t         port_no,
                                   vtss_timeinterval_t          *const delay_asymmetry)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *delay_asymmetry = vtss_state->ts.port_conf[port_no].delay_asymmetry;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the timestamping operation mode for a port */
vtss_rc vtss_ts_operation_mode_set(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   const vtss_ts_operation_mode_t      *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        if ((mode->domain != vtss_state->ts.port_conf[port_no].mode.domain) ||
                (mode->mode != vtss_state->ts.port_conf[port_no].mode.mode)) {
            vtss_state->ts.port_conf[port_no].mode = *mode;
            rc = VTSS_FUNC_COLD(ts.operation_mode_set,port_no);
        }
#else
        vtss_state->ts.port_conf[port_no].mode = *mode;
        rc = VTSS_FUNC_COLD(ts.operation_mode_set,port_no);
#endif
    }
    VTSS_EXIT();
    return rc;
}

/* Get the timestamping operation mode for a port */
vtss_rc vtss_ts_operation_mode_get(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   vtss_ts_operation_mode_t            *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *mode = vtss_state->ts.port_conf[port_no].mode;
    }
    VTSS_EXIT();
    return rc;
}

/* Set the timestamping internal mode */
vtss_rc vtss_ts_internal_mode_set(const vtss_inst_t              inst,
                                   const vtss_ts_internal_mode_t      *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        vtss_state->ts.int_mode = *mode;
        rc = VTSS_FUNC_COLD_0(ts.internal_mode_set);
    }
    VTSS_EXIT();
    return rc;
}

/* Get the timestamping internal mode */
vtss_rc vtss_ts_internal_mode_get(const vtss_inst_t              inst,
                                   vtss_ts_internal_mode_t            *const mode)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *mode = vtss_state->ts.int_mode;
    }
    VTSS_EXIT();
    return rc;
}

/* Flush the timestamp FIFO  */
static void vtss_timestamp_flush(vtss_state_t *vtss_state)
{
    int     id;
    (void) VTSS_FUNC_0(ts.timestamp_get);
    VTSS_D("Flushing timestamp fifo");
    for (id = 0; id < VTSS_TS_ID_SIZE; id++) {
        vtss_state->ts.status[id].reserved_mask = 0LL;
        vtss_state->ts.status[id].valid_mask = 0LL;
        vtss_state->ts.status[id].rx_tc_valid = FALSE;
        vtss_state->ts.status[id].age = 0;
        (void) VTSS_FUNC(ts.timestamp_id_release, id);
    }
}
                                   

/* Update the internal timestamp table, from HW */
vtss_rc vtss_tx_timestamp_update(const vtss_inst_t              inst)
{
    vtss_state_t *vtss_state;
    vtss_rc rc;
    u64 port_mask;
    vtss_ts_timestamp_t ts;
    vtss_state_t *my_vtss_state;
    int port_idx = 0;
    int ts_idx = 0;
    void (*cb)(void *context, u32 port_no, vtss_ts_timestamp_t *ts);
    void *cx;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_0(ts.timestamp_get);
        VTSS_D("rc = %d", rc);
        while ((port_idx < VTSS_PORT_ARRAY_SIZE) && (ts_idx < TS_IDS_RESERVED_FOR_SW)) {
            if (vtss_state->ts.status[ts_idx].valid_mask != 0) {   /* We just check if any TS on this TS index */
                port_mask = 1LL<<port_idx;
                if ((vtss_state->ts.status[ts_idx].valid_mask & port_mask) && (vtss_state->ts.status[ts_idx].reserved_mask & port_mask)) {  /* There is a TS and this TS index is reserved */
                    vtss_state->ts.status[ts_idx].valid_mask &= ~port_mask;
                    vtss_state->ts.status[ts_idx].reserved_mask &= ~port_mask;
                    ts.id = vtss_state->ts.status[ts_idx].tx_id[port_idx];
                    ts.ts = vtss_state->ts.status[ts_idx].tx_tc[port_idx];
                    ts.ts_valid = TRUE;
                    if (vtss_state->ts.status[ts_idx].cb[port_idx] && vtss_state->ts.status[ts_idx].context[port_idx]) {
                        my_vtss_state = vtss_state; /* save context */
                        /* avoid using vtss_state while outside the API lock, as the API may be called from an other thread */
                        cb = vtss_state->ts.status[ts_idx].cb[port_idx];
                        cx = vtss_state->ts.status[ts_idx].context[port_idx];
                        vtss_state->ts.status[ts_idx].cb[port_idx] = NULL;
                        vtss_state->ts.status[ts_idx].context[port_idx] = NULL;
                        VTSS_EXIT();
                        /* call out of the API */
                        cb(cx, port_idx, &ts);
                        VTSS_ENTER();
                        vtss_state = my_vtss_state; /* restore context */
                    } else {
                        VTSS_E("undefined TS callback port_idx %d, ts_idx %d", port_idx, ts_idx);
                    }
                    VTSS_D("port_no %d, ts_id %d, ts %" PRIu64 "(%d)", port_idx, ts.id, ts.ts, ts.ts_valid);
                }
            } else {
                port_idx = VTSS_PORT_ARRAY_SIZE;    /* No TS on this TS index - skip all ports */
            }
            if (++port_idx >= VTSS_PORT_ARRAY_SIZE) {
                port_idx = 0;
                ++ts_idx;
            }
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Get the FIFO rx timestamp for a {timestampId} - only to be called from within another API function */
vtss_rc _vtss_rx_timestamp_get(const vtss_inst_t              inst,
                               const vtss_ts_id_t             *const ts_id,
                               vtss_ts_timestamp_t            *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_0(ts.timestamp_get);
        if (ts_id->ts_id >= VTSS_TS_ID_SIZE) {
            /* invalid timestamp id indicates FIFO overflow */
            vtss_timestamp_flush(vtss_state);
            rc = VTSS_RC_ERROR;
        } else {
            ts->ts = vtss_state->ts.status[ts_id->ts_id].rx_tc;
            ts->ts_valid = vtss_state->ts.status[ts_id->ts_id].rx_tc_valid;
            if (ts->ts_valid) {
                vtss_state->ts.status[ts_id->ts_id].rx_tc_valid = FALSE;
                if (vtss_state->ts.status[ts_id->ts_id].reserved_mask == 0LL) {
                    vtss_state->ts.status[ts_id->ts_id].age = 0;
                    rc = VTSS_FUNC(ts.timestamp_id_release, ts_id->ts_id);
                }
            }
        }
    }
    return rc;
}

/* Get the FIFO rx timestamp for a {timestampId} */
vtss_rc vtss_rx_timestamp_get(const vtss_inst_t              inst,
                              const vtss_ts_id_t             *const ts_id,
                              vtss_ts_timestamp_t            *const ts)
{
    vtss_rc rc;

    VTSS_ENTER();
    rc = _vtss_rx_timestamp_get(inst, ts_id, ts);
    VTSS_EXIT();

    return rc;
}

/* Release the FIFO rx timestamp id  */
vtss_rc _vtss_rx_timestamp_id_release(const vtss_inst_t              inst,
                              const vtss_ts_id_t             *const ts_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (ts_id->ts_id >= VTSS_TS_ID_SIZE) {
            /* invalid timestamp id indicates FIFO overflow */
            vtss_timestamp_flush(vtss_state);
            rc = VTSS_RC_ERROR;
        } else {
            rc = VTSS_FUNC(ts.timestamp_id_release, ts_id->ts_id);
        }
    }
    return rc;
}

/* Release the FIFO rx timestamp id  */
vtss_rc vtss_rx_timestamp_id_release(const vtss_inst_t              inst,
                              const vtss_ts_id_t             *const ts_id)
{
    vtss_rc      rc;

    VTSS_ENTER();
    rc = _vtss_rx_timestamp_id_release(inst, ts_id);
    VTSS_EXIT();
    return rc;
}

/* Get rx timestamp from a port (convert from slave time to the master time) */
vtss_rc vtss_rx_master_timestamp_get(const vtss_inst_t              inst,
                                     const vtss_port_no_t           port_no,
                                     vtss_ts_timestamp_t                 *const ts)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.timestamp_convert, port_no, &ts->ts);
        if (rc == VTSS_RC_OK) {
            ts->ts_valid = TRUE;
        } else {
            ts->ts_valid = FALSE;
        }

    }
    VTSS_EXIT();
    return rc;
}


/* Allocate a timestamp id for a two step transmission */
vtss_rc vtss_tx_timestamp_idx_alloc(const vtss_inst_t          inst,
                                   const vtss_ts_timestamp_alloc_t *const alloc_parm,
                                   vtss_ts_id_t               *const ts_id)
{
    vtss_state_t *vtss_state;
    int port_idx = 0;
    vtss_rc rc = VTSS_RC_ERROR;
    u32 id;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_RC_ERROR;
        /* Find a free ts_id */
        for (id = 0; id < TS_IDS_RESERVED_FOR_SW; id++) {
            if ((vtss_state->ts.status[id].reserved_mask & alloc_parm->port_mask) == 0) {
                vtss_state->ts.status[id].reserved_mask |= alloc_parm->port_mask;
                for (port_idx = 0; port_idx < VTSS_PORT_ARRAY_SIZE; port_idx++) {
                    if (alloc_parm->port_mask & (1LL<<port_idx)) {
                        vtss_state->ts.status[id].context[port_idx] = alloc_parm->context;
                        vtss_state->ts.status[id].cb[port_idx] = alloc_parm->cb;
                    }
                }
                vtss_state->ts.status[id].age = 0;
                ts_id->ts_id = id;
                VTSS_I("portmask = %" PRIx64 ", reserved_mask = %" PRIx64 " id = %u", alloc_parm->port_mask, vtss_state->ts.status[id].reserved_mask, ts_id->ts_id);
                rc = VTSS_RC_OK;
                break;
            }
        } 
    }
    VTSS_EXIT();
    return rc;
}


#define TSID_TX_MAX_TIMETICKS 3
#define TSID_RX_MAX_TIMETICKS 100
/* Age the FIFO timestamps */
vtss_rc vtss_timestamp_age(const vtss_inst_t              inst)
{
    vtss_state_t *vtss_state;
    int id;
    u64 port_mask;
    vtss_ts_timestamp_t ts;
    vtss_state_t *my_vtss_state;
    vtss_rc rc;
    void (*cb)(void *context, u32 port_no, vtss_ts_timestamp_t *ts);
    void *cx;

#if defined(VTSS_MISSING_TX_TIMESTAMP_INTERRUPT)
    // Luton26 does not generate tx timestamp interrupt, so first check if
    // there are any valid timestamps
    VTSS_RC(vtss_tx_timestamp_update(inst));
#endif

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) != VTSS_RC_OK) {
        goto do_exit;
    }

    for (id = 0; id < VTSS_TS_ID_SIZE; id++) {
       vtss_ts_timestamp_status_t *status = &vtss_state->ts.status[id];
       u32                        max_age;
       int                        port_idx;

        if (status->reserved_mask == 0LL && !status->rx_tc_valid) {
            continue;
        }

        if (status->reserved_mask != 0LL) {
            max_age = TSID_TX_MAX_TIMETICKS;
        } else {
            max_age = TSID_RX_MAX_TIMETICKS;
        }

        if (++status->age <= max_age) {
            continue;
        }

        VTSS_D("Aging timestamp ts_id = %d, reserved_mask = %" PRIx64 "", id, status->reserved_mask);
        port_idx = 0;

        while (status->reserved_mask && port_idx < VTSS_PORT_ARRAY_SIZE) {
            port_mask = 1LL << port_idx;

            if ((status->reserved_mask & port_mask)) {
                status->reserved_mask &= ~port_mask;
                ts.id = id;
                ts.ts = 0;
                ts.ts_valid = FALSE;
                if (status->cb[port_idx] && status->context[port_idx]) {
                    // Avoid using vtss_state while outside the API lock, as the
                    // API may be called from an other thread
                    my_vtss_state = vtss_state;
                    cb = status->cb[port_idx];
                    cx = status->context[port_idx];
                    status->cb[port_idx] = NULL;
                    status->context[port_idx] = NULL;
                    VTSS_EXIT();
                    // Call out of the API, to indicate timeout
                    cb(cx, port_idx, &ts);
                    VTSS_ENTER();
                    vtss_state = my_vtss_state; /* restore context */
                } else {
                    VTSS_D("Undefined TS callback port_idx %d, ts_idx %d", port_idx, id);
                }

                VTSS_D("port_no %d, ts_id %d, ts %" PRIu64 "(%d)", port_idx, ts.id, ts.ts, ts.ts_valid);
            }

            port_idx++;
        }

        status->reserved_mask = 0LL;
        status->valid_mask    = 0LL;
        status->rx_tc_valid   = FALSE;
        status->age           = 0;

        if ((rc = VTSS_FUNC(ts.timestamp_id_release, id)) != VTSS_RC_OK) {
            goto do_exit;
        }
    }

do_exit:
    VTSS_EXIT();
    return rc;
}

/* Signal port status change (used to detect and compensate for the internal ingress and egress latencies) */
vtss_rc vtss_ts_status_change(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.status_change, port_no);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
/* Set auto response behavior pr. domain. */
vtss_rc vtss_ts_autoresp_dom_cfg_set(const vtss_inst_t                  inst,
                                     const u8                           domain,
                                     const vtss_ts_autoresp_dom_cfg_t   *const cfg)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();

    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (domain < VTSS_TS_DOMAIN_ARRAY_SIZE) {
            vtss_state->ts.auto_resp_cfg[domain] = *cfg;
            VTSS_D("domain %d, ptp_port_individual %d, ptp_port_msb %d, ", domain, cfg->ptp_port_individual, cfg->ptp_port_msb);
            rc = VTSS_FUNC(ts.autoresp_cfg_set, domain);
        } else {
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Get auto response behaviour pr. domain. */
vtss_rc vtss_ts_autoresp_dom_cfg_get(const vtss_inst_t                  inst,
                                     const u8                           domain,
                                     vtss_ts_autoresp_dom_cfg_t         *const cfg)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (domain < VTSS_TS_DOMAIN_ARRAY_SIZE) {
            *cfg = vtss_state->ts.auto_resp_cfg[domain];
            VTSS_D("domain %d, ptp_port_individual %d, ptp_port_msb %d, ", domain, cfg->ptp_port_individual, cfg->ptp_port_msb);
        }
    }
    VTSS_EXIT();
    return rc;
}

/* Set the source mac address used in autp Delay_Req/Resp */
vtss_rc vtss_ts_smac_set(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              const vtss_mac_t  *const smac)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        vtss_state->ts.port_conf[port_no].smac = *smac;
        rc = VTSS_FUNC_COLD(ts.smac_set,port_no);
#else
        rc = VTSS_RC_ERROR;
#endif
    }
    VTSS_EXIT();
    return rc;
}

/* Get the source mac address used in autp Delay_Req/Resp */
vtss_rc vtss_ts_smac_get(const vtss_inst_t    inst,
                              const vtss_port_no_t port_no,
                              vtss_mac_t  *const smac)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        *smac = vtss_state->ts.port_conf[port_no].smac;
#else
        rc = VTSS_RC_ERROR;
#endif
    }
    VTSS_EXIT();
    return rc;
}
#endif //defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)

vtss_rc vtss_ts_seq_cnt_get(const vtss_inst_t                inst,
                            const u32                   sec_cntr,
                            u16 *const                  cnt_val)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(ts.seq_cnt_get, sec_cntr, cnt_val);
    }
    if (rc != VTSS_RC_OK) {
        *cnt_val = 0;
    }
    VTSS_EXIT();
    return rc;
}

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_ts_inst_create(vtss_state_t *vtss_state)
{
#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
    u32 i;

    for (i = 0; i < VTSS_TS_DOMAIN_ARRAY_SIZE; ++i) {
        vtss_state->ts.auto_resp_cfg[i].ptp_port_msb = TS_PORT_ID_PORT_NUMBER_DEFAULT;  /* Default value in register */
    }
#endif
    return VTSS_RC_OK;
}


#if VTSS_OPT_DEBUG_PRINT

/* - Debug print --------------------------------------------------- */

static const char *one_pps_mode_disp(vtss_ts_ext_clock_one_pps_mode_t m)
{
    switch (m) {
        case TS_EXT_CLOCK_MODE_ONE_PPS_DISABLE: return "Disable";
        case TS_EXT_CLOCK_MODE_ONE_PPS_OUTPUT: return "Output";
        case TS_EXT_CLOCK_MODE_ONE_PPS_INPUT: return "Input";
        default: return "unknown";
    }
}

void vtss_ts_debug_print(vtss_state_t *vtss_state,
                         const vtss_debug_printf_t pr,
                         const vtss_debug_info_t   *const info)
{
    u32               i,j;
    vtss_ts_conf_t *ts_conf;
    vtss_ts_port_conf_t *ts_port_conf;
    vtss_ts_timestamp_status_t *status;
    BOOL first = TRUE;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_TS))
        return;

    ts_conf = &vtss_state->ts.conf;

    pr("One-Second Timer:\n");
    for (i = 0; i < VTSS_TS_DOMAIN_ARRAY_SIZE; i++) {
        pr("Adjustment rate[%u]: %i ppb, \nOne_pps mode: %s ExternalClockOut mode: %s freq %d Hz\nClock offset %d sec\n",
                    i, ts_conf->adj[i],
                    one_pps_mode_disp(ts_conf->ext_clock_mode.one_pps_mode),
                    ts_conf->ext_clock_mode.enable ? "enable" : "disable",
                    ts_conf->ext_clock_mode.freq,
                    ts_conf->sec_offset);
    }
    pr("Port timestamp parameters:\n");
    pr("Port  IngressLatency  PeerDelay  EgressLatency  OperationMode\n");
    for (i = 0; i < VTSS_PORT_ARRAY_SIZE; i++) {
        ts_port_conf = &vtss_state->ts.port_conf[i];
        pr("%-4d  %-14i  %-9i  %-13i  %-d\n",
           i,
           VTSS_INTERVAL_NS(ts_port_conf->ingress_latency),
           VTSS_INTERVAL_NS(ts_port_conf->p2p_delay),
           VTSS_INTERVAL_NS(ts_port_conf->egress_latency),
           ts_port_conf->mode.mode);
    }
    
    
    (void)VTSS_FUNC_0(ts.timestamp_get);
    pr("Timestamp fifo data:\n");
    
    for (i = 0; i < VTSS_TS_ID_SIZE; i++) {
        status = &vtss_state->ts.status[i];
        if (status->reserved_mask != 0) {
            pr("Timestamp_id : %d  Reserved_mask: %" PRIx64 ", age %d\n", i, status->reserved_mask, status->age);
        }
        if (status->valid_mask != 0) {
            pr("                    Valid_mask: %" PRIx64 "\n", status->valid_mask);
        }
        first = TRUE;
        for (j = 0; j < VTSS_PORT_ARRAY_SIZE; j++) {
            if (status->valid_mask & 1LL<<j) {
                if (first) {
                    pr("Tx Port  time counter  time id\n");
                    first = FALSE;
                }
                pr("%-9d  %-14" PRIu64 " %-14d \n", j, status->tx_tc[j], status->tx_id[j]);
            }
        }
        if (status->rx_tc_valid) {
            pr("Rx Timestamp_id : %d  Rx timecounter: %d, \n", i, status->rx_tc);
        }
    }
    pr("\n");
}
#endif // VTSS_OPT_DEBUG_PRINT
#endif /* VTSS_FEATURE_TIMESTAMP */

