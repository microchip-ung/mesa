// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_AFI
#include "vtss_jaguar2_cil.h"
#include <stdint.h>

#if defined(VTSS_ARCH_JAGUAR_2) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_AFI_V2)

#define JR2_AFI_CHIP_PORT(port_no) ((port_no) == VTSS_PORT_NO_NONE ? VTSS_CHIP_PORT_VD1 : VTSS_CHIP_PORT(port_no))
#define JR2_AFI_E_RETURN(rc, ...) do {VTSS_E(__VA_ARGS__); return rc;} while(0)

/******************************************************************************/
//
// Internal CIL: Misc. functions
//
/******************************************************************************/

/**
 * jr2_afi_clock_period_get()
 */
static vtss_rc jr2_afi_clock_period_get(vtss_state_t *vtss_state)
{
    u32 res;

#if defined(VTSS_ARCH_JAGUAR_2_B)
    res = 4000;
#elif defined(VTSS_ARCH_JAGUAR_2_C)
    u32 val;
    JR2_RD(VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0(0 /* TBD */), &val);
    val = VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV(val);
    switch (val) {
    case 0:
    case 33:
        // 625 MHz
        res = 1600;
        break;

    case 1:
        // 312.5 MHz
        res = 3200;
        break;

    case 2:
    case 4:
        // 500 MHz
        res = 2000;
        break;

    case 3:
        // 277.77 MHz
        res = 3600;
        break;

    case 5:
        // 250 MHz
        res = 4000;
        break;

    case 6:
    case 8:
        // 416.66 MHz
        res = 2400;
        break;

    case 7:
        // 227.27 MHz
        res = 4400;
        break;

    case 9:
        // 208.33 MHz
        res = 4800;
        break;

    case 10:
    case 12:
        // 357.14 MHz
        res = 2800;
        break;

    case 13:
        // 178.57 MHz
        res = 5600;
        break;

    case 14:
        // 312.5 MHz
        res = 3200;
        break;

    case 15:
        // 166.66 MHz
        res = 6000;
        break;

    case 17:
        // 156.25 MHz
        res = 6400;
        break;

    default:
        VTSS_E("Unknown core clock divider (%u). Assuming 4 ns clock period", val);
        res = 4000;
        break;
    }

#elif defined(VTSS_ARCH_SERVAL_T)
    u32 val, div2;

    JR2_RD(VTSS_HSIO_PLL5G_CFG_PLL5G_CFG0(0), &val);
    val = VTSS_X_HSIO_PLL5G_CFG_PLL5G_CFG0_CORE_CLK_DIV(val);

    switch (val) {
    case 17:
        // 156.25 MHz
        res = 6400;
        break;

    case 25:
        // 104.17 MHz
        res = 9600;
        break;

    default:
        VTSS_E("Unknown core clock divider (%u). Assuming 6.4 ns clock period", val);
        res = 6400;
        break;
    }

    JR2_RD(VTSS_HSIO_HW_CFGSTAT_CLK_CFG, &div2);
    if (VTSS_X_HSIO_HW_CFGSTAT_CLK_CFG_SWC_CLK_DIV2(div2)) {
        res *= 2;
    }
#else
#error "Update this piece of code."
#endif

    vtss_state->afi.clk_period_ps = res;
    return VTSS_RC_OK;
}

/**
 * jr2_afi_debug()
 */
static vtss_rc jr2_afi_debug(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    u64 t_us[8], base_us;
    u32 val, val0, val1, t[8], idx, frm_ptr, next_and_type, part0;

    // Timer Tick Table
    pr("Timer Tick Table\n");
    pr("Clock period: %" PRIu64 " ps\n", vtss_state->afi.clk_period_ps);
    pr("Idx  Value Length [us]\n");
    pr("---- ----- -----------\n");

    JR2_RD(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_0_3, &val0);
    JR2_RD(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_4_7, &val1);
    t[0] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN0(val0);
    t[1] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN1(val0);
    t[2] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN2(val0);
    t[3] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN3(val0);
    t[4] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN4(val1);
    t[5] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN5(val1);
    t[6] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN6(val1);
    t[7] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN7(val1);

    JR2_RD(VTSS_AFI_TTI_TICKS_TTI_TICK_BASE, &val);
    val0 = VTSS_X_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN(val);
    base_us = VTSS_DIV64(val0 * vtss_state->afi.clk_period_ps, 1000000LLU);
    pr("Base %5u %11" PRIu64 "\n", val0, base_us);

    for (idx = 0; idx < VTSS_ARRSZ(t); idx++) {
        t_us[idx] = (idx == 0 ? base_us : t_us[idx - 1]) * t[idx];
        pr("%4u %5u %11" PRIu64 "\n", idx, t[idx], t_us[idx]);
    }

    // TTI Table
    pr("\nTTI Table\n");
    pr("Idx  TickIdx TmrLen Period [us] Jit FrmPtr Type  NextPtr Part0\n");
    pr("---- ------- ------ ----------- --- ------ ----- ------- ----------\n");
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); idx++) {
        BOOL enabled;
        u32  tick_idx, tmr_len;

        JR2_RD(VTSS_AFI_TTI_TBL_TTI_TIMER(idx), &val);

#if defined(VTSS_ARCH_JAGUAR_2_B)
        enabled = VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN(val) != 0;
#else
        enabled = VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(val) && VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN(val) != 0;
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

        if (!enabled) {
            continue;
        }

        tick_idx = VTSS_X_AFI_TTI_TBL_TTI_TIMER_TICK_IDX(val);
        tmr_len  = VTSS_X_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN(val);

        // Get pointer to first frame table entry
        JR2_RD(VTSS_AFI_TTI_TBL_TTI_FRM(idx), &frm_ptr);
        frm_ptr = VTSS_X_AFI_TTI_TBL_TTI_FRM_FRM_PTR(frm_ptr);

        // Get what's in the first frame table entry
        JR2_RD(VTSS_AFI_FRM_TBL_FRM_NEXT_AND_TYPE(frm_ptr), &next_and_type);
        JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_ptr), &part0);

        pr("%4u %7u %6u %11" PRIu64 " %3u 0x%04x %-5s 0x%05x 0x%08x\n",
           idx,
           tick_idx,
           tmr_len,
           t_us[tick_idx] * tmr_len,
           VTSS_X_AFI_TTI_TBL_TTI_TIMER_JITTER(val),
           frm_ptr,
           VTSS_X_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE(next_and_type) == 0 ? "Frame" : "Delay",
           VTSS_X_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_NEXT_PTR(next_and_type),
           part0);
    }

    // DTI Table
    pr("\nDTI table\n");
    pr("Idx FrmPtr Type  NextPtr InjCnt FrmInfo Delay [ns] Part0\n");
    pr("--- ------ ----- ------- ------ ------- ---------- ----------\n");
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.dti_tbl); idx++) {
        char buf0[20];

        JR2_RD(VTSS_AFI_DTI_MISC_DTI_CTRL(idx), &val);

        if (!VTSS_X_AFI_DTI_MISC_DTI_CTRL_ENA(val)) {
            // DTI index not in use
            continue;
        }

        // Get pointer to first frame table entry
        JR2_RD(VTSS_AFI_DTI_TBL_DTI_FRM(idx), &frm_ptr);
        frm_ptr = VTSS_X_AFI_DTI_TBL_DTI_FRM_FIRST_FRM_PTR(frm_ptr);
        VTSS_SPRINTF(buf0, "%u", idx);

        while (1) {
            u32 frm_next, frm_type, inj_cnt, frm_info, delay_cc;
            u64 delay_ns;
            char buf1[20], buf2[20], buf3[20];

            // Get what's in the first frame table entry
            JR2_RD(VTSS_AFI_FRM_TBL_FRM_NEXT_AND_TYPE(frm_ptr), &next_and_type);
            JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_ptr), &part0);

            frm_next = VTSS_X_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_NEXT_PTR(next_and_type);
            frm_type = VTSS_X_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE(next_and_type);
            inj_cnt  = VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS,  VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID);
            frm_info = VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS, VTSS_AFI_FRM_TBL_PART0_FRM_INFO_WID);
            delay_cc = VTSS_EXTRACT_BITFIELD(part0, VTSS_AFI_FRM_TBL_PART0_DELAY_POS,    VTSS_AFI_FRM_TBL_PART0_DELAY_WID);

            if (frm_type == 0) {
                // Frame
                VTSS_SPRINTF(buf1, "%6u",    inj_cnt);  // Injection count
                VTSS_SPRINTF(buf2, "0x%05x", frm_info); // Frame info
                VTSS_SPRINTF(buf3, "%10s",   "");       // Delay is N/A
            } else {
                // Delay
                delay_ns = VTSS_DIV64(((u64)delay_cc * vtss_state->afi.clk_period_ps), 1000LLU);
                VTSS_SPRINTF(buf1, "%6s",        "");       // Injection count is N/A
                VTSS_SPRINTF(buf2, "%7s",        "");       // Frame info is N/A
                VTSS_SPRINTF(buf3, "%10" PRIu64, delay_ns); // Delay in nanoseconds
            }

            pr("%3s 0x%04x %-5s 0x%05x %s %s %s 0x%08x\n",
               buf0,
               frm_ptr,
               frm_type == 0 ? "Frame" : "Delay",
               frm_next,
               buf1,
               buf2,
               buf3,
               part0);

            frm_ptr = frm_next;

            if (frm_ptr == 0) {
                break;
            }

            // Only print the Idx column when we go no the next DTI table entry.
            buf0[0] = '\0';
        }
    }

    VTSS_RC(vtss_jr2_port_debug_qres(vtss_state, pr, FALSE));
    VTSS_RC(vtss_jr2_port_debug_qres(vtss_state, pr, TRUE));

    return VTSS_RC_OK;
}

// Reference to queue into which frame shall be injected.
typedef struct {
    vtss_phys_port_no_t chip_port;

#if defined(VTSS_ARCH_JAGUAR_2_B)
    u32 se_idx; // [0; 4065]
    u32 se_inp; // [0; VTSS_CHIP_PORT_VD1]
#else
    u32 qu_num; // [0; 3357] on ServalT and [0; 272xx] on Jaguar_2_C
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */
} jr2_afi_qu_ref_t;

/*
 * jr2_afi_port_prio_2_qu_ref()
 */
static vtss_rc jr2_afi_port_prio_2_qu_ref(vtss_state_t *const vtss_state, vtss_port_no_t port_no, vtss_prio_t prio, jr2_afi_qu_ref_t *qu_ref)
{
    qu_ref->chip_port = JR2_AFI_CHIP_PORT(port_no); // Destination port

#if defined(VTSS_ARCH_JAGUAR_2_B)
    // Prioritized traffic to VD1 is not supported.
    // Auto-pick Super Priority.
    if (qu_ref->chip_port == VTSS_CHIP_PORT_VD1) {
        if (prio < VTSS_PRIO_SUPER) {
            prio = VTSS_PRIO_SUPER;
        }
    }

    if (prio == VTSS_PRIO_SUPER) {
        // Super priority
        qu_ref->se_idx = 4064;
        qu_ref->se_inp = qu_ref->chip_port;
    } else if (prio > VTSS_PRIO_SUPER) {
        // Shaped super priority (no define for this yet).
        qu_ref->se_idx = 4065;
        qu_ref->se_inp = qu_ref->chip_port;
    } else {
        // For other priorities, we pick the CPU port as source.
        qu_ref->se_idx = qu_ref->chip_port * 8 + prio;
        qu_ref->se_inp = VTSS_CHIP_PORT_CPU_0;
    }

    VTSS_I("port_no = %d, prio = %u => se_idx = %u, se_inp = %u", port_no, prio, qu_ref->se_idx, qu_ref->se_inp);
#else
    // Other JR2 variants

#if defined(VTSS_ARCH_JAGUAR_2_C)
// Jaguar 2C
#define VTSS_AFI_QU_VD1           27199
#define VTSS_AFI_QU_SP0           27200
#define VTSS_AFI_QU_SP1           27264
#define VTSS_AFI_HSCH_LARGE_RATIO     8
#elif defined(VTSS_ARCH_SERVAL_T)
// Serval-T
#define VTSS_AFI_QU_VD1            3327
#define VTSS_AFI_QU_SP0            3328
#define VTSS_AFI_QU_SP1            3343
#define VTSS_AFI_HSCH_LARGE_RATIO     2

#else
#error "Update this for new chip variants"
#endif /* 2C/ServalT/other */

    if (prio == VTSS_PRIO_SUPER) {
        // Super priority
        qu_ref->qu_num = VTSS_AFI_QU_SP0 + qu_ref->chip_port;
    } else if (prio > VTSS_PRIO_SUPER) {
        qu_ref->qu_num = VTSS_AFI_QU_SP1 + qu_ref->chip_port;
    } else {
        if (qu_ref->chip_port == VTSS_CHIP_PORT_VD1) {
            qu_ref->qu_num = VTSS_AFI_QU_VD1;
        } else {
            // Assume the destination is not amongst the CPU ports when we
            // arrive here, because had it been so, the equation would have been
            // quite different. We pick the CPU port as source.
            // Default mapping
            qu_ref->qu_num = 8 * VTSS_AFI_HSCH_LARGE_RATIO * (qu_ref->chip_port * 8 + prio) + VTSS_CHIP_PORT_CPU_0;
        }
    }

    VTSS_I("port_no = %d, prio = %u => qu_num = %u", port_no, prio, qu_ref->qu_num);
#endif

   return VTSS_RC_OK;
}

/*
 * jr2_afi_port_tbl_entry()
 *
 * Takes a logical port number and returns a vtss_afi_port_t pointer.
 * The catch is that the function also supports Virtual Device #1,
 * which is indicated by port_no == VTSS_PORT_NO_NONE. In this case,
 * the last entry of the port_tbl[] array (which is one longer than
 * the number of front ports on this platform) is returned.
 */
static vtss_afi_port_t *jr2_afi_port_tbl_entry(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    return &vtss_state->afi.port_tbl[port_no == VTSS_PORT_NO_NONE ? VTSS_ARRSZ(vtss_state->afi.port_tbl) - 1 : port_no];
}

/*
 * jr2_afi_chip_port_flush()
 */
static vtss_rc jr2_afi_chip_port_flush(vtss_state_t *vtss_state, vtss_phys_port_no_t chip_port)
{
    vtss_mtimer_t timer;
    u32           cnt = 0;
    const u32     timeout = 2000 /* msecs */;
    vtss_rc       rc = VTSS_RC_OK;

    // At this point in time, all AFI flows on this port must have been
    // stopped, so that we can flush the port's queues.
    // If it isn't stopped, we might end up corrupting the queue system
    // and send garbage frames out when the port comes back up and the AFI
    // re-enables disabled flows (see BZ#20083, BZ#20189 and especially BZ#20191
    // See also APPL-1298, APPL-110, and APPL-963.

    // Here, we just make sure that the AFI has no frames outstanding in the
    // queue system by waiting up to 1 second for all AFI flows on this port to
    // get out of the queue system. The 1 second is chosen so that it's very
    // unlikely that the up to AFI::FRM_OUT_MAX frames don't get out of the
    // queue system even when a port shaper is enabled.
    VTSS_MTIMER_START(&timer, timeout);
    while (1) {
        u32 afi_val;

        cnt++;
        JR2_RD(VTSS_AFI_PORT_TBL_PORT_FRM_OUT(chip_port), &afi_val);

        if ((afi_val = VTSS_X_AFI_PORT_TBL_PORT_FRM_OUT_FRM_OUT_CNT(afi_val)) == 0) {
            // No more unack'ed frames, so flushing is complete
            break;
        }

        if (VTSS_MTIMER_TIMEOUT(&timer)) {
            // If this happens, it may be that the port's Tx clock is not
            // running, so that frames are not getting out. It could also be
            // (not confirmed with RTL developers) that the egress port is so
            // overwhelmed by frames coming from other ports - perhaps with
            // higher priority - that the QSYS doesn't ACK frames sent by the
            // AFI.
            VTSS_E("AFI's FRM_OUT_CNT is non-zero (%u) on chip port %u even after %u msecs of trying", afi_val, chip_port, timeout);
            rc = VTSS_RC_ERROR;
            goto do_exit;
        }
    }

do_exit:
    VTSS_MTIMER_CANCEL(&timer); // Needed?
    VTSS_I("Flush: Polled FRM_OUT_CNT %u times for chip port %u", cnt, chip_port);
    return rc;
}

/*
 * jr2_afi_chip_port_start()
 */
static vtss_rc jr2_afi_chip_port_start(vtss_state_t *const vtss_state, vtss_phys_port_no_t chip_port, vtss_afi_port_t *afi_port)
{
    // Set FRM_OUT_MAX back to normal
    JR2_WRM(VTSS_AFI_PORT_TBL_PORT_CFG(chip_port),
            VTSS_F_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX(afi_port->frm_out_max),
            VTSS_M_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX);

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    // Set FRM_RM_ONLY back to 0
    JR2_WRM(VTSS_AFI_PORT_TBL_PORT_CFG(chip_port),
            VTSS_F_AFI_PORT_TBL_PORT_CFG_FRM_RM_ONLY(0),
            VTSS_M_AFI_PORT_TBL_PORT_CFG_FRM_RM_ONLY);
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

    // Set FC_SKIP_TTI_INJ=0
    JR2_WRM(VTSS_AFI_PORT_TBL_PORT_CFG(chip_port),
            VTSS_F_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ(0),
            VTSS_M_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ);

    VTSS_I("Reallowed injection to chip-port %u, and set frame out max back to %u", chip_port, afi_port->frm_out_max);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_chip_port_stop()
 */
static vtss_rc jr2_afi_chip_port_stop(vtss_state_t *const vtss_state, vtss_phys_port_no_t chip_port)
{
    u32 frm_out_max;

#if defined(VTSS_ARCH_JAGUAR_2_B)
    // Set FC_SKIP_TTI_INJ = 1
    // Use FRM_OUT_MAX = 0 to stop port
    frm_out_max = 0;
    JR2_WRM(VTSS_AFI_PORT_TBL_PORT_CFG(chip_port),
            VTSS_F_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ(1) | VTSS_F_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX(frm_out_max),
            VTSS_M_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ    | VTSS_M_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX);
#else
    // Set FC_SKIP_TTI_INJ = 1
    // Use FRM_RM_ONLY = 1 to stop port
    // In order to ensure that we can remove all flows in this state, increase
    // FRM_OUT_MAX to 1000 (otherwise, the FRM_GONE bit might not be set if the
    // MAC's Tx clock is not running, FRM_OUT_MAX is reached, and a frame
    // removal afterwards is issued). It will be set back to its normal when
    // jr2_afi_port_start() is invoked, that is, when link comes back up.
    frm_out_max = 1000;
    JR2_WRM(VTSS_AFI_PORT_TBL_PORT_CFG(chip_port),
            VTSS_F_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ(1) | VTSS_F_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX(frm_out_max) | VTSS_F_AFI_PORT_TBL_PORT_CFG_FRM_RM_ONLY(1),
            VTSS_M_AFI_PORT_TBL_PORT_CFG_FC_SKIP_TTI_INJ    | VTSS_M_AFI_PORT_TBL_PORT_CFG_FRM_OUT_MAX              | VTSS_M_AFI_PORT_TBL_PORT_CFG_FRM_RM_ONLY);
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

    VTSS_I("Stopped injection to chip-port %u, and increased frame out max to %u", chip_port, frm_out_max);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_port_start()
 */
static vtss_rc jr2_afi_port_start(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    return jr2_afi_chip_port_start(vtss_state, JR2_AFI_CHIP_PORT(port_no), jr2_afi_port_tbl_entry(vtss_state, port_no));
}

/*
 * jr2_afi_port_stop()
 */
static vtss_rc jr2_afi_port_stop(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    vtss_phys_port_no_t chip_port = JR2_AFI_CHIP_PORT(port_no);

    VTSS_I("port_no = %d, chip_port = %u", port_no, chip_port);

    VTSS_RC(jr2_afi_chip_port_stop( vtss_state, chip_port));

    return jr2_afi_chip_port_flush(vtss_state, chip_port);
}

/*
 * jr2_afi_port_link_up()
 */
static vtss_rc jr2_afi_port_link_up(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %u, link = %d, started = %d", port_no, port->link, port->started);

    if (port->started) {
        VTSS_RC(jr2_afi_port_start(vtss_state, port_no));
    }

    port->link = 1;
    VTSS_I("Exit.  port = %u, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_port_link_down()
 */
static vtss_rc jr2_afi_port_link_down(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %u, link = %d, started = %d", port_no, port->link, port->started);

    VTSS_RC(jr2_afi_port_stop(vtss_state, port_no));
    port->link = 0;

    VTSS_I("Exit.  port = %u, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_hijack_error_print()
 * In case of a hijack timeout, we print the frame references tracked per
 * destination counters for VD1. This is where the number of AFI-held frames are
 * stored in QSYS.
 * In previous versions of the software, these numbers could get very high,
 * because of a bug in the chip, where an AFI frame could get released both by
 * the AFI itself (which is fine), and through flush of a front port that had a
 * reference to an AFI frame that was going to be transmitted on that port.
 */
static vtss_rc jr2_afi_hijack_error_print(vtss_state_t *const vtss_state)
{
    u32  cnt, val, idx;
    char buf1[300], buf2[300];

    cnt = VTSS_SNPRINTF(buf1, sizeof(buf1), "QRES:RES_CTRL[VD1 = %u]:RES_STAT\n", VTSS_CHIP_PORT_VD1);
    for (idx = 0; idx < 8; idx++) {
        JR2_RD(VTSS_QRES_RES_CTRL_RES_STAT(3 * 1024 + VTSS_CHIP_PORT_VD1 * 8 + idx), &val);
        cnt += VTSS_SNPRINTF(buf1 + cnt, sizeof(buf1) - cnt,  "Qu = %u: Cnt = %u\n", idx, val);
    }

    cnt = VTSS_SNPRINTF(buf2, sizeof(buf2), "QRES:RES_CTRL[VD1 = %u]:RES_STAT_CUR\n", VTSS_CHIP_PORT_VD1);
    for (idx = 0; idx < 8; idx++) {
        JR2_RD(VTSS_QRES_RES_CTRL_RES_STAT_CUR(3 * 1024 + VTSS_CHIP_PORT_VD1 * 8 + idx), &val);
        cnt += VTSS_SNPRINTF(buf2 + cnt, sizeof(buf2) - cnt,  "Qu = %u: Cnt = %u\n", idx, val);
    }

    VTSS_E("CIL: Timeout waiting for NEW_FRM_CTRL.VLD\n%s\n%s", buf1, buf2);
    return VTSS_RC_OK;
}

/*
 * jr2_afi_frm_hijack()
 *
 * Setup frame, hijacked by AFI
 */
static vtss_rc jr2_afi_frm_hijack(vtss_state_t *const vtss_state, i32 frm_idx)
{
    vtss_afi_frm_t *frm = &vtss_state->afi.frm_tbl[frm_idx];
    vtss_mtimer_t  timer;
    u32            new_frm_vld, frm_info, cnt = 0;

    // Wait for frame to be hijacked. This can take up to an unspecified amount
    // of time, because it depends on the time between the application transmits
    // the frame and then calls the hijack function.
    // In the Microsemi application, the AFI module waits for an acknowledgement
    // from the packet module that the frame is transmitted before invoking
    // the hijack function. The problem is that this acknowledgement may come
    // way before the frame has actually hit the hardware (under Linux). Let's
    // compensate for that and allow up to ten seconds to elapse here.
    VTSS_MTIMER_START(&timer, 10000);
    while (1) {
        cnt++;
        JR2_RD(VTSS_AFI_MISC_NEW_FRM_CTRL, &new_frm_vld);
        if (VTSS_X_AFI_MISC_NEW_FRM_CTRL_VLD(new_frm_vld)) {
            break;
        }

        if (VTSS_MTIMER_TIMEOUT(&timer)) {
            VTSS_MTIMER_CANCEL(&timer); // Needed?
            (void)jr2_afi_hijack_error_print(vtss_state);
            return VTSS_RC_ERROR;
        }
    }

    VTSS_MTIMER_CANCEL(&timer);
    VTSS_I("Reads = %u", cnt);

    // Get frm_info for hijacked frame
    JR2_RD(VTSS_AFI_MISC_NEW_FRM_INFO, &frm_info);
    frm_info = VTSS_X_AFI_MISC_NEW_FRM_INFO_FRM_INFO(frm_info);
    frm->frm_delay.frm.frm_info.fp =
        VTSS_EXTRACT_BITFIELD(frm_info,
                              VTSS_AFI_FRM_INFO_FP_POS,
                              VTSS_AFI_FRM_INFO_FP_WID);
    frm->frm_delay.frm.frm_info.fshort =
        VTSS_EXTRACT_BITFIELD(frm_info,
                              VTSS_AFI_FRM_INFO_SHORT_POS,
                              VTSS_AFI_FRM_INFO_SHORT_WID);
    frm->frm_delay.frm.frm_info.eprio =
        VTSS_EXTRACT_BITFIELD(frm_info,
                              VTSS_AFI_FRM_INFO_EPRIO_POS,
                              VTSS_AFI_FRM_INFO_EPRIO_WID);

    // Setup FRM_TBL entry
    JR2_WRM(VTSS_AFI_FRM_TBL_FRM_NEXT_AND_TYPE(frm_idx),
            VTSS_F_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE(0),
            VTSS_M_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE);

    JR2_WR(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx),
           (frm->frm_delay.frm.frm_info.fp     << (VTSS_AFI_FRM_INFO_FP_POS    + VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS)) |
           (frm->frm_delay.frm.frm_info.fshort << (VTSS_AFI_FRM_INFO_SHORT_POS + VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS)) |
           (frm->frm_delay.frm.frm_info.eprio  << (VTSS_AFI_FRM_INFO_EPRIO_POS + VTSS_AFI_FRM_TBL_PART0_FRM_INFO_POS)));

    JR2_WR(VTSS_AFI_MISC_NEW_FRM_CTRL, VTSS_F_AFI_MISC_NEW_FRM_CTRL_VLD(0));

    return VTSS_RC_OK;
}

/*
 * jr2_afi_set_bit_field()
 *
 * Set value of field within u32.
 * offset : Offset of field within val32
 * wid    : Width of field
 * fld_val: Field value
 */
static void jr2_afi_set_bit_field(u32 *const val32, u8 offset, u8 wid, u32  fld_val)
{
    if ((fld_val >> wid) != 0) {
        VTSS_E("Invalid arguments: fld_val = 0x%x, wid = %u, offset = %u", fld_val, wid, offset);
    }

    *val32 = (*val32 & ~(u32)(((1 << wid) - 1) << offset)) | (fld_val << offset);
}

/*
 * jr2_afi_frm_setup()
 *
 * Configure Frame entry in FRM_TBL
 * Note: In PART0 only INJ_CNT is updated.
 */
static vtss_rc jr2_afi_frm_setup(vtss_state_t *const vtss_state, i32 frm_idx)
{
    vtss_afi_frm_t *frm = &vtss_state->afi.frm_tbl[frm_idx];
    u32            frm_tbl_part0;

    JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), &frm_tbl_part0);
    jr2_afi_set_bit_field(&frm_tbl_part0,
                          VTSS_AFI_FRM_TBL_PART0_INJ_CNT_POS,
                          VTSS_AFI_FRM_TBL_PART0_INJ_CNT_WID,
                          frm->frm_delay.frm.inj_cnt);
    JR2_WR(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), frm_tbl_part0);

    JR2_WR(VTSS_AFI_FRM_TBL_FRM_NEXT_AND_TYPE(frm_idx),
           VTSS_F_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_NEXT_PTR(frm->next_ptr) |
           VTSS_F_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE(0));

    return VTSS_RC_OK;
}

/*
 * jr2_afi_delay_setup()
 *
 * Configure Delay entry in FRM_TBL
 * Note: In PART0 only DELAY is updated
 */
static vtss_rc jr2_afi_delay_setup(vtss_state_t *const vtss_state, i32 frm_idx)
{
    vtss_afi_frm_t *frm = &vtss_state->afi.frm_tbl[frm_idx];
    u32             frm_tbl_part0;

    JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), &frm_tbl_part0);
    jr2_afi_set_bit_field(&frm_tbl_part0,
                          VTSS_AFI_FRM_TBL_PART0_DELAY_POS,
                          VTSS_AFI_FRM_TBL_PART0_DELAY_WID,
                          frm->frm_delay.delay.delay);
    JR2_WR(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), frm_tbl_part0);

    JR2_WR(VTSS_AFI_FRM_TBL_FRM_NEXT_AND_TYPE(frm_idx),
           VTSS_F_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_NEXT_PTR(frm->next_ptr) |
           VTSS_F_AFI_FRM_TBL_FRM_NEXT_AND_TYPE_ENTRY_TYPE(1));

    return VTSS_RC_OK;
}

/*
 * jr2_afi_set_frm_rm()
 *
 * Set FRM_RM = 1 for frame
 */
static vtss_rc jr2_afi_set_frm_rm(vtss_state_t *const vtss_state, i32 frm_idx)
{
    u32 frm_tbl_part0;

    VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));

    JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), &frm_tbl_part0);

    if (VTSS_EXTRACT_BITFIELD(frm_tbl_part0, VTSS_AFI_FRM_TBL_PART0_FRM_RM_POS, 1)) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "frm_rm already set");
    }

    if (VTSS_EXTRACT_BITFIELD(frm_tbl_part0, VTSS_AFI_FRM_TBL_PART0_FRM_GONE_POS, 1)) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "frm_gone already set");
    }

    frm_tbl_part0 |= (1 << VTSS_AFI_FRM_TBL_PART0_FRM_RM_POS);
    JR2_WR(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), frm_tbl_part0);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_frm_gone_get()
 */
static vtss_rc jr2_afi_frm_gone_get(vtss_state_t *const vtss_state, u8 *const frm_gone, i32 frm_idx)
{
    u32 frm_tbl_part0;

    JR2_RD(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), &frm_tbl_part0);
    *frm_gone = VTSS_EXTRACT_BITFIELD(frm_tbl_part0, VTSS_AFI_FRM_TBL_PART0_FRM_GONE_POS, 1);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_dti_pause_resume()
 */
static vtss_rc jr2_afi_dti_pause_resume(vtss_state_t *const vtss_state, u32 dti_idx, BOOL pause)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

    VTSS_I("Enter. %sing dti_idx = %u", pause ? "Paus" : "Resum", dti_idx);

    // Start/Stop
    JR2_WRM(VTSS_AFI_DTI_MISC_DTI_CTRL(dti_idx),
            VTSS_F_AFI_DTI_MISC_DTI_CTRL_ENA(pause ? 0 : 1),
            VTSS_M_AFI_DTI_MISC_DTI_CTRL_ENA);

    dti->paused = pause;

    VTSS_I("Exit (%u)", dti_idx);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_tti_pause_resume()
 */
static vtss_rc jr2_afi_tti_pause_resume(vtss_state_t *const vtss_state, u32 tti_idx, BOOL pause)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter. %sing tti_idx = %u", pause ? "Paus" : "Resum", tti_idx);

#if defined(VTSS_ARCH_JAGUAR_2_B)
    // Jaguar2B: Stop timer by setting timer_len to zero. Start by setting to
    // TTI's timer length.
    JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN(pause ? 0 : tti->timer_len),
            VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN);
#else
    // Start and stop timer using timer_ena
    JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(pause ? 0 : 1),
            VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA);
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

    tti->paused = pause;

    VTSS_I("Exit (%u)", tti_idx);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_up_flows_pause_resume()
 */
static vtss_rc jr2_afi_up_flows_pause_resume(vtss_state_t *const vtss_state, vtss_port_no_t port_no, BOOL pause)
{
    u32  dti_idx, tti_idx;
    BOOL at_least_one_paused_or_resumed = FALSE;

    VTSS_I("Enter. %sing up-flows on port_no = %u", pause ? "Paus" : "Resum", port_no);

    // Pause or resume all DTIs egressing VD1 (ingressing #port_no)
    for (dti_idx = 0; dti_idx < VTSS_ARRSZ(vtss_state->afi.dti_tbl); dti_idx++) {
        vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

        if (dti->state              == VTSS_AFI_ENTRY_STATE_STARTED &&
            dti->paused             != pause                        &&
            dti->port_no            == VTSS_PORT_NO_NONE            &&
            dti->masquerade_port_no == port_no) {
            VTSS_RC(jr2_afi_dti_pause_resume(vtss_state, dti_idx, pause));
            at_least_one_paused_or_resumed = TRUE;
        }
    }

    // Pause or resume all TTIs egressing VD1 (ingressing #port_no).
    for (tti_idx = 0; tti_idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); tti_idx++) {
        vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

        if (tti->state              == VTSS_AFI_ENTRY_STATE_STARTED &&
            tti->paused             != pause                        &&
            tti->port_no            == VTSS_PORT_NO_NONE            &&
            tti->masquerade_port_no == port_no) {
            VTSS_RC(jr2_afi_tti_pause_resume(vtss_state, tti_idx, pause));
            at_least_one_paused_or_resumed = TRUE;
        }
    }

    if (pause && at_least_one_paused_or_resumed) {
        // At most frm_out_max frames can be outstanding. They must all be gone
        // before the up-port gets flushed, or we might end up freeing frames in
        // the queue system (due to a chip-bug).
        // VD1 is a 10G port and W/C is frm_out_max jumbo frames of, say
        // 10 kbytes = 80 kbits, which then takes 8 us per frame to get out of
        // VD1 (provided the analyzer doesn't back-pressures VD1, which we have
        // to assume it doesn't).
        u32 frm_out_max = jr2_afi_port_tbl_entry(vtss_state, VTSS_PORT_NO_NONE)->frm_out_max;
        u32 sleep_ms = (8 * frm_out_max) / 1000;

        // Sleep at least one millisecond
        sleep_ms = sleep_ms ? sleep_ms : 1;

        VTSS_I("Sleeping %u ms", sleep_ms);
        VTSS_MSLEEP(sleep_ms);
    }

    VTSS_I("Exit (%sing up-flows on port_no = %u)", pause ? "paus" : "resum", port_no);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_port_fwd_set()
 */
static vtss_rc jr2_afi_port_fwd_set(vtss_state_t *const vtss_state, vtss_port_no_t port_no, BOOL new_fwd, BOOL *old_fwd)
{
    vtss_phys_port_no_t chip_port = JR2_AFI_CHIP_PORT(port_no);
    u32                 val;

    JR2_RD(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(chip_port), &val);

    VTSS_I("Enter(port_no = %d => chip_port = %u, new_fwd = %d, val before = 0x%08x", port_no, chip_port, new_fwd, val);

    if (old_fwd) {
        *old_fwd = VTSS_X_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA(val);
    }

    if (new_fwd) {
        val |= VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA;
    } else {
        val &= ~VTSS_M_QFWD_SYSTEM_SWITCH_PORT_MODE_PORT_ENA;
    }

    JR2_WR(VTSS_QFWD_SYSTEM_SWITCH_PORT_MODE(chip_port), val);
    VTSS_I("Exit(port_no = %d => chip_port = %u, new_fwd = %d, val after = 0x%08x", port_no, chip_port, new_fwd, val);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_frm_gone_wait()
 */
static vtss_rc jr2_afi_frm_gone_wait(vtss_state_t *vtss_state, u32 idx, vtss_port_no_t port_no, i32 frm_idx, BOOL is_dti)
{
    u32             poll_cnt, poll_cnt_max, method;
    BOOL            frm_gone = FALSE, old_fwd = TRUE;
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. %s_idx = %u on port %d", is_dti ? "dti" : "tti", idx, port_no);

    if (is_dti) {
        poll_cnt_max = 1000;
    } else {
        // Assumption:
        // Each poll takes at least 50 clk cycles.
        // One TTI is processed every 4 clk cycles.
        poll_cnt_max = (VTSS_AFI_SLOW_INJ_CNT * 4) / 50;
    }

    // We're now ready for removal injection. A removal injection from the AFI
    // tells the QSYS to free the frame. This is an injection like any other AFI
    // injection. The AFI can only have frm_out_max outstanding frames on a
    // given port, and if the flows out of the port get starved due to other
    // higher priority flows or other higher priority frames coming from other
    // front ports, it may happen that the AFI can't get rid of the removal
    // injected frame, so that FRM_GONE never gets set.
    // The following code attempts to wait for FRM_GONE in three rounds:
    // 1) Simply wait for FRM_GONE by polling up to poll_cnt_max times.
    // 2) If not gone, stop forwarding into and out of the port in question and
    //    wait for FRM_GONE again by polling up to poll_cnt_max times.
    // 3) Since other AFI frames injected on the port in question may still
    //    starve the flow we are currently removing (because the AFI injects
    //    directly into the port and doesn't obey the forwarding, we set in step
    //    2), stop all other AFI flows on the port and wait for FRM_GONE again
    //    by polling up to poll_cnt_max times.
    //
    // It has been considered to stop both all up-flows (through VD1) and all
    // flows on the port in question and waiting for FRM_OUT_CNT to go to 0
    // before waiting for FRM_GONE. This has the unfortunate side-effect that
    // e.g. CCM frames may be delayed more than 10 ms, causing the remote end
    // to raise an alarm. This may still happen for up-flows if step #2 and #3
    // takes more than 10 ms, and for down-flows if step #3 takes more than 10
    // ms.

    // Notice, if QLIM is enabled (at the time of writing, it isn't), one has to
    // change the queue number before removing a flow (see MESA-320).
    // When doing so, there's no guarantee that frames will be acknowledged
    // by the QSYS in the same order as they are injected by the AFI, so
    // when removing a frame with QLIM enabled, the port needs to be stopped and
    // flushed before starting the removal injection. Otherwise, we could end up
    // freeing the frame from the QSYS before all references to it were out.

    for (method = 1; method < 4; method++) {
        switch (method) {
        case 1:
            // Simply poll without doing anything special
            break;

        case 2:
            // Stop port forwarding before polling again.
            VTSS_RC(jr2_afi_port_fwd_set(vtss_state, port_no, 0, &old_fwd));
            break;

        case 3:
            // Stop and flush other AFI flows on this port before polling again.
            VTSS_RC(jr2_afi_port_stop(vtss_state, port_no));
            break;
        }

        // Poll for FRM_GONE == 1 for last frame
        poll_cnt = 0;
        while (!frm_gone && poll_cnt++ < poll_cnt_max) {
            VTSS_RC(jr2_afi_frm_gone_get(vtss_state, &frm_gone, frm_idx));
        }

        if (frm_gone) {
            break;
        }
    }

    // Clean up.
    switch (method) {
    case 4:
    case 3:
        // Restart other AFI flows on this port if they were started at all
        if (port->link && port->started) {
            VTSS_RC(jr2_afi_port_start(vtss_state, port_no));
        }

        // Fallthrough

    case 2:
        // Set port forwarding back to what is was
        VTSS_RC(jr2_afi_port_fwd_set(vtss_state, port_no, old_fwd, NULL));

        // Fallthrough

    case 1:
        // Nothing more to do
        break;
    }

    if (frm_gone) {
        VTSS_I("%s_idx = %u on port %d: Polled %u times out of %u using method %u. FRM_GONE = %d", is_dti ? "dti" : "tti", idx, port_no, poll_cnt, poll_cnt_max, method, frm_gone);
    } else {
        VTSS_E("%s_idx = %u on port %d: Polled %u times out of %u using method %u. FRM_GONE = %d", is_dti ? "dti" : "tti", idx, port_no, poll_cnt, poll_cnt_max, method, frm_gone);
        return VTSS_RC_ERROR;

    }

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// Internal CIL: DTI functions
//
/******************************************************************************/

/*
 * jr2_afi_dti_qu_ref_update()
 */
static vtss_rc jr2_afi_dti_qu_ref_update(vtss_state_t *const vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t   *dti = &vtss_state->afi.dti_tbl[dti_idx];
    jr2_afi_qu_ref_t qu_ref;

    VTSS_RC(jr2_afi_port_prio_2_qu_ref(vtss_state, dti->port_no, dti->prio, &qu_ref));

#if defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WR(VTSS_AFI_DTI_TBL_DTI_PORT_QU(dti_idx),
           VTSS_F_AFI_DTI_TBL_DTI_PORT_QU_SE_INP(qu_ref.se_inp) |
           VTSS_F_AFI_DTI_TBL_DTI_PORT_QU_SE_IDX(qu_ref.se_idx) |
           VTSS_F_AFI_DTI_TBL_DTI_PORT_QU_PORT_NUM(qu_ref.chip_port));
#else
    JR2_WR(VTSS_AFI_DTI_TBL_DTI_PORT_QU(dti_idx),
           VTSS_F_AFI_DTI_TBL_DTI_PORT_QU_QU_NUM(qu_ref.qu_num) |
           VTSS_F_AFI_DTI_TBL_DTI_PORT_QU_PORT_NUM(qu_ref.chip_port));
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// Internal CIL: TTI functions
//
/******************************************************************************/

/*
 * jr2_afi_tti_cal_init()
 *
 * Initialize TTI calendar
 */
static vtss_rc jr2_afi_tti_cal_init(vtss_state_t *const vtss_state)
{
    u32  max_poll_cnt = 5;
    u32  val;
    BOOL tti_init = 1 /* picky compiler */;

    JR2_WRM(VTSS_AFI_TTI_MISC_TTI_CTRL,
            VTSS_F_AFI_TTI_MISC_TTI_CTRL_TTI_INIT(1),
            VTSS_M_AFI_TTI_MISC_TTI_CTRL_TTI_INIT);

    // Wait for device to clear TTI_INIT
    while (max_poll_cnt-- > 0) {
        JR2_RD(VTSS_AFI_TTI_MISC_TTI_CTRL, &val);
        if ((tti_init = VTSS_X_AFI_TTI_MISC_TTI_CTRL_TTI_INIT(val)) == 0) {
            break;
        }
    }

    if (tti_init == 1) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "Timeout waiting for TTI_CTRL.TTI_INIT == 0");
    }

    return VTSS_RC_OK;
}

/*
 * jr2_afi_tti_tick_init()
 */
static vtss_rc jr2_afi_tti_tick_init(vtss_state_t *const vtss_state)
{
    u32 tick_base_len, val0, val1, idx;
    u64 t_ps[8], tick_base_ps;

    // Find a suitable base tick, given that we want the first tick length to be VTSS_AFI_TTI_TICK_LEN0_US
    tick_base_len = VTSS_DIV64(VTSS_AFI_TTI_TICK_LEN0_US * 1000000LLU, vtss_state->afi.clk_period_ps);
    if (tick_base_len == 0 || tick_base_len > VTSS_M_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "Unable to find a suitable tick base given the first tick index request (%u us)", VTSS_AFI_TTI_TICK_LEN0_US);
    }

    JR2_WRM(VTSS_AFI_TTI_TICKS_TTI_TICK_BASE,
            VTSS_F_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN(tick_base_len),
            VTSS_M_AFI_TTI_TICKS_TTI_TICK_BASE_BASE_LEN);

    // Get true tick base without rounding errors.
    tick_base_ps = tick_base_len * vtss_state->afi.clk_period_ps;

    // Configure tick lengths
    JR2_WR(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_0_3,
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN0(VTSS_DIV64(VTSS_AFI_TTI_TICK_LEN0_US * 1000000LLU, tick_base_ps)) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN1(VTSS_AFI_TTI_TICK_LEN1_US / VTSS_AFI_TTI_TICK_LEN0_US) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN2(VTSS_AFI_TTI_TICK_LEN2_US / VTSS_AFI_TTI_TICK_LEN1_US) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN3(VTSS_AFI_TTI_TICK_LEN3_US / VTSS_AFI_TTI_TICK_LEN2_US));

    JR2_WR(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_4_7,
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN4(VTSS_AFI_TTI_TICK_LEN4_US / VTSS_AFI_TTI_TICK_LEN3_US) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN5(VTSS_AFI_TTI_TICK_LEN5_US / VTSS_AFI_TTI_TICK_LEN4_US) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN6(VTSS_AFI_TTI_TICK_LEN6_US / VTSS_AFI_TTI_TICK_LEN5_US) |
           VTSS_F_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN7(VTSS_AFI_TTI_TICK_LEN7_US / VTSS_AFI_TTI_TICK_LEN6_US));

    // Now that we have made the rounding errors that will come from using
    // these constants, update the array that the rest of the code uses.
    JR2_RD(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_0_3, &val0);
    JR2_RD(VTSS_AFI_TTI_TICKS_TTI_TICK_LEN_4_7, &val1);

    // In order to not accummulate rounding errors, first compute the
    // tick lengths in ps and then found them to microseconds.
    t_ps[0] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN0(val0) * tick_base_ps;
    t_ps[1] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN1(val0) * t_ps[0];
    t_ps[2] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN2(val0) * t_ps[1];
    t_ps[3] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_0_3_LEN3(val0) * t_ps[2];
    t_ps[4] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN4(val1) * t_ps[3];
    t_ps[5] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN5(val1) * t_ps[4];
    t_ps[6] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN6(val1) * t_ps[5];
    t_ps[7] = VTSS_X_AFI_TTI_TICKS_TTI_TICK_LEN_4_7_LEN7(val1) * t_ps[6];

    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tick_len_us); idx++) {
        vtss_state->afi.tick_len_us[idx] = VTSS_DIV64(t_ps[idx], 1000000LLU);
    }

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    // On JR2C and later, a new bit, TIMER_ENA, was introduced with
    // a default value of 1 to be backward compatible. This has
    // the unfortunate side-effect that the very first frame of
    // a flow *may* come as the flow is started and the next frame
    // some random time after, so that the two frames aren't spaced
    // with the required amount of time.
    // To make sure that this very first frame isn't transmitted
    // by accident, we therefore disable all TTI timers during boot.
    for (idx = 0; idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); idx++) {
        JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(idx), VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(0), VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA);
    }
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) */

    return VTSS_RC_OK;
}

/**
 * jr2_afi_tti_qu_ref_update()
 */
static vtss_rc jr2_afi_tti_qu_ref_update(vtss_state_t *const vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];
    jr2_afi_qu_ref_t qu_ref;

    VTSS_RC(jr2_afi_port_prio_2_qu_ref(vtss_state, tti->port_no, tti->prio, &qu_ref));

    // (Re)write configuration
#if defined(VTSS_ARCH_JAGUAR_2_B)
    JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(tti_idx),
           VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_SE_INP(qu_ref.se_inp) |
           VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_SE_IDX(qu_ref.se_idx) |
           VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(qu_ref.chip_port));
#else
    JR2_WR(VTSS_AFI_TTI_TBL_TTI_PORT_QU(tti_idx),
           VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_QU_NUM(qu_ref.qu_num) |
           VTSS_F_AFI_TTI_TBL_TTI_PORT_QU_PORT_NUM(qu_ref.chip_port));
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: DTI functions
//
/******************************************************************************/

/*
 * jr2_afi_dti_start()
 *
 * do_frm_delay_config: (Re)configure frame-delay sequence before (re)starting
 * do_dti_config:       (Re)configure DTI before (re)starting
 */
static vtss_rc jr2_afi_dti_start(vtss_state_t *const vtss_state, u32 dti_idx, BOOL do_frm_delay_config, BOOL do_dti_config, BOOL start_flow)
{
    vtss_afi_dti_t *dti     = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    u32            frm_inj_cnt, frm_idx;
    BOOL           link;
    vtss_port_no_t port_no;

    VTSS_I("Enter: Starting dti_idx = %u (do_config = %d)", dti_idx, do_dti_config);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "DTI already started");
    }

    if (do_frm_delay_config) {
        // (Re)write FRM_TBL configuration for DTI
        frm_idx = dti->first_frm_idx;
        while (frm_idx > 0) {
            if (frm_tbl[frm_idx].entry_type) {
                VTSS_RC(jr2_afi_delay_setup(vtss_state, frm_idx));
            } else {
                VTSS_RC(jr2_afi_frm_setup(vtss_state, frm_idx));
            }

            frm_idx = frm_tbl[frm_idx].next_ptr;
        }
    }

    if (do_dti_config) {
        u32 dti_mode_val, dti_mode_mask;

        dti_mode_val =
            VTSS_F_AFI_DTI_TBL_DTI_MODE_MODE(dti->mode) |
            VTSS_F_AFI_DTI_TBL_DTI_MODE_TRAILING_DELAY_SEQ_CNT(dti->trailing_delay_seq_cnt) |
            VTSS_F_AFI_DTI_TBL_DTI_MODE_FRM_INJ_CNT(0)
#if !defined(VTSS_ARCH_JAGUAR_2_B)
            | VTSS_F_AFI_DTI_TBL_DTI_MODE_DTI_NEXT(dti->dti_next)
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) */
            ;

        dti_mode_mask = VTSS_M_AFI_DTI_TBL_DTI_MODE_MODE |
                        VTSS_M_AFI_DTI_TBL_DTI_MODE_TRAILING_DELAY_SEQ_CNT |
                        VTSS_M_AFI_DTI_TBL_DTI_MODE_FRM_INJ_CNT
#if !defined(VTSS_ARCH_JAGUAR_2_B)
                        | VTSS_M_AFI_DTI_TBL_DTI_MODE_DTI_NEXT
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) */
                        ;

        // (Re)write DTI configuration
        JR2_WRM(VTSS_AFI_DTI_TBL_DTI_MODE(dti_idx), dti_mode_val, dti_mode_mask);

        VTSS_RC(jr2_afi_dti_qu_ref_update(vtss_state, dti_idx));
    }

    // Configuration settings performed regardless of do_dti_config
    JR2_WRM(VTSS_AFI_DTI_TBL_DTI_FRM(dti_idx),
            VTSS_F_AFI_DTI_TBL_DTI_FRM_NEXT_FRM_PTR(dti->first_frm_idx),
            VTSS_M_AFI_DTI_TBL_DTI_FRM_NEXT_FRM_PTR);
    if (dti->mode == 0 || dti->mode == 2) {
        frm_inj_cnt = dti->frm_inj_cnt;
    } else {
        frm_inj_cnt = 0;
    }

    JR2_WRM(VTSS_AFI_DTI_TBL_DTI_CNT(dti_idx),
            VTSS_F_AFI_DTI_TBL_DTI_CNT_CNT(frm_inj_cnt),
            VTSS_M_AFI_DTI_TBL_DTI_CNT_CNT);
    JR2_WR(VTSS_AFI_DTI_MISC_DTI_CNT_DOWN(dti_idx), 0);

#if !defined(VTSS_ARCH_JAGUAR_2_B) && !defined(VTSS_ARCH_SERVAL_T)
    // This must be enabled for JR2C and later.
    JR2_WR(VTSS_AFI_DTI_TBL_DTI_DURATION(dti_idx), 0);
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) && !defined(VTSS_ARCH_SERVAL_T) */

    JR2_WR(VTSS_AFI_DTI_MISC_DTI_CTRL(dti_idx), VTSS_F_AFI_DTI_MISC_DTI_CTRL_BW(dti->bw));

    if (!start_flow) {
        VTSS_I("Exit without starting flow. dti_idx = %u", dti_idx);
        return VTSS_RC_OK;
    }

    // Always start down-flows, because a per-port AFI mechanism ensures that
    // flows are not really started until the port gets link.
    // Only start up-flows if there's link on the port. Calls to
    // jr2_afi_link_state_change() ensure that these up-flows are started and
    // stopped by link state changes.
    port_no = dti->port_no != VTSS_PORT_NO_NONE ? dti->port_no : dti->masquerade_port_no;
    link    = dti->port_no != VTSS_PORT_NO_NONE ? TRUE         : jr2_afi_port_tbl_entry(vtss_state, port_no)->link;

    VTSS_I("port_no = %d: link = %d", port_no, link);
    VTSS_RC(jr2_afi_dti_pause_resume(vtss_state, dti_idx, !link));

    // User has started this flow now, even though it may not be started in
    // reality.
    dti->state = VTSS_AFI_ENTRY_STATE_STARTED;

    VTSS_I("Exit. dti_idx = %u, paused = %d", dti_idx, dti->paused);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_dti_stop()
 */
static vtss_rc jr2_afi_dti_stop(vtss_state_t *const vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

    VTSS_I("Enter. Stopping dti_idx = %u", dti_idx);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "DTI not started");
    }

    VTSS_RC(jr2_afi_dti_pause_resume(vtss_state, dti_idx, 1));

    dti->state = VTSS_AFI_ENTRY_STATE_STOPPED;

    VTSS_I("Exit (%u)", dti_idx);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_dti_frm_hijack()
 */
static vtss_rc jr2_afi_dti_frm_hijack(vtss_state_t *const vtss_state, u32 dti_idx, u32 frm_size)
{
    vtss_afi_dti_t *dti     = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t *frm_tbl = vtss_state->afi.frm_tbl;
    u32            frm_idx  = dti->first_frm_idx, i;
    vtss_afi_frm_t *frm;

    VTSS_I("Enter(%u)", dti_idx);

    // Locate the right entry in the frame table.
    for (i = 0; i < dti->frm_cnt; i++) {
        frm_idx = frm_tbl[frm_idx].next_ptr;

        if (frm_idx == 0) {
            // Error
            break;
        }
    }

    if (frm_idx == 0) {
        // Don't use frm_idx == 0 for DTI (cannot link to it with NEXT_PTR)
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "Frame idx for dti->first_frm_idx = %u is 0, when iterating %u times", dti->first_frm_idx, dti->frm_cnt);
    }

    VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));

    frm = &vtss_state->afi.frm_tbl[frm_idx];

    VTSS_RC(jr2_afi_frm_hijack(vtss_state, frm_idx));
    frm->frm_delay.frm.frm_size = frm_size;

    if (dti->frm_cnt++ == 0) {
        // Setup FIRST_FRM_PTR
        JR2_WRM(VTSS_AFI_DTI_TBL_DTI_FRM(dti_idx),
                VTSS_F_AFI_DTI_TBL_DTI_FRM_FIRST_FRM_PTR(frm_idx),
                VTSS_M_AFI_DTI_TBL_DTI_FRM_FIRST_FRM_PTR);
    }

    VTSS_I("Exit(%u)", dti_idx);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_dti_frm_rm_inj()
 */
static vtss_rc jr2_afi_dti_frm_rm_inj(vtss_state_t *const vtss_state, u32 dti_idx)
{
    vtss_afi_dti_t  *dti = &vtss_state->afi.dti_tbl[dti_idx];
    vtss_afi_frm_t  *frm_tbl = vtss_state->afi.frm_tbl;
    i32             frm_idx, last_frm_idx = 0;

    VTSS_I("Removing dti_idx = %u", dti_idx);

    if (dti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "ID = %u: Injection must be stopped before rm injection", dti_idx);
    }

    // Set the FRM_RM bit for each frame to be removed in the Frame Table.
    for (frm_idx = dti->first_frm_idx; frm_idx > 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        if (frm_tbl[frm_idx].entry_type != 0) {
            // Not a frame entry
            continue;
        }

        // This is a frame. Remove it.
        VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));
        VTSS_RC(jr2_afi_set_frm_rm(vtss_state, frm_idx));
        last_frm_idx = frm_idx;
    }

    // Set DTI_FRM.NEXT_FRM_PTR to DTI_FRM.FIRST_FRM_PTR
    JR2_WRM(VTSS_AFI_DTI_TBL_DTI_FRM(dti_idx),
            VTSS_F_AFI_DTI_TBL_DTI_FRM_NEXT_FRM_PTR(dti->first_frm_idx),
            VTSS_M_AFI_DTI_TBL_DTI_FRM_NEXT_FRM_PTR);

    // Set DTI_MODE.MODE=0
    // Set DTI_MODE.FRM_INJ_CNT to 0.
    if (dti->mode != 0) {
        JR2_WRM(VTSS_AFI_DTI_TBL_DTI_MODE(dti_idx),
                VTSS_F_AFI_DTI_TBL_DTI_MODE_MODE(0) |
                VTSS_F_AFI_DTI_TBL_DTI_MODE_FRM_INJ_CNT(0),
                VTSS_M_AFI_DTI_TBL_DTI_MODE_MODE |
                VTSS_M_AFI_DTI_TBL_DTI_MODE_FRM_INJ_CNT);
    }

    // Set DTI_CNT.CNT=1
    JR2_WRM(VTSS_AFI_DTI_TBL_DTI_CNT(dti_idx),
            VTSS_F_AFI_DTI_TBL_DTI_CNT_CNT(1),
            VTSS_M_AFI_DTI_TBL_DTI_CNT_CNT);

    // Set all delays in sequence to 0 to speed up the removal procedure
    for (frm_idx = dti->first_frm_idx; frm_idx > 0; frm_idx = frm_tbl[frm_idx].next_ptr) {
        if (frm_tbl[frm_idx].entry_type != 1) {
            // Not a delay entry
            continue;
        }

        // This is a delay. Clear it.
        VTSS_RC(afi_frm_idx_chk(vtss_state, frm_idx));
        JR2_WR(VTSS_AFI_FRM_TBL_FRM_ENTRY_PART0(frm_idx), 0);
    }

    JR2_WR(VTSS_AFI_DTI_MISC_DTI_CNT_DOWN(dti_idx), 0);

    // Start removal injection!
    JR2_WR(VTSS_AFI_DTI_MISC_DTI_CTRL(dti_idx),
           VTSS_F_AFI_DTI_MISC_DTI_CTRL_ENA(1) |
           VTSS_F_AFI_DTI_MISC_DTI_CTRL_BW(0));

    // Wait until the frame is gone.
    VTSS_RC(jr2_afi_frm_gone_wait(vtss_state, dti_idx, dti->port_no, last_frm_idx, TRUE));

    return VTSS_RC_OK;
}

/*
 * jr2_afi_dti_cnt_get()
 */
static vtss_rc jr2_afi_dti_cnt_get(vtss_state_t *const vtss_state, u32 dti_idx, u32 *const cnt)
{
    VTSS_I("Enter(%u)", dti_idx);
    JR2_RD(VTSS_AFI_DTI_TBL_DTI_CNT(dti_idx), cnt);
    VTSS_I("Exit(%u = %u)", dti_idx, *cnt);
    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: TTI functions
//
/******************************************************************************/

/*
 * jr2_afi_ttis_enable()
 */
static vtss_rc jr2_afi_ttis_enable(vtss_state_t *const vtss_state)
{
    VTSS_I("Enter");
    JR2_WRM(VTSS_AFI_TTI_MISC_TTI_CTRL,
            VTSS_F_AFI_TTI_MISC_TTI_CTRL_TTI_ENA(1),
            VTSS_M_AFI_TTI_MISC_TTI_CTRL_TTI_ENA);
    VTSS_I("Exit");

    return VTSS_RC_OK;
}

/*
 * jr2_afi_tti_start()
 *
 * do_config: (Re)configure TTI before (re)starting
 */
static vtss_rc jr2_afi_tti_start(vtss_state_t *const vtss_state, u32 tti_idx, BOOL do_config)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];
    u32            rand_tick_cnt;
    BOOL           link;
    vtss_port_no_t port_no;

    VTSS_I("Enter. Starting tti_idx = %u (do_config = %d)", tti_idx, do_config);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "TTI already started");
    }

    if (do_config) {
        VTSS_RC(jr2_afi_tti_qu_ref_update(vtss_state, tti_idx));

        JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
                VTSS_F_AFI_TTI_TBL_TTI_TIMER_TICK_IDX(tti->tick_idx) |
                VTSS_F_AFI_TTI_TBL_TTI_TIMER_JITTER(tti->jitter),
                VTSS_M_AFI_TTI_TBL_TTI_TIMER_TICK_IDX |
                VTSS_M_AFI_TTI_TBL_TTI_TIMER_JITTER);

#if !defined(VTSS_ARCH_JAGUAR_2_B)
        JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
                VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN(tti->timer_len),
                VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN);
#endif /* (!)defined(VTSS_ARCH_JAGUAR_2_B) */

        JR2_WR(VTSS_AFI_TTI_TBL_TTI_FRM(tti_idx),
               VTSS_F_AFI_TTI_TBL_TTI_FRM_FRM_PTR(tti->frm_idx));
    }

    // Set TICK_CNT to a random value in range [1-TIMER_LEN]
    rand_tick_cnt = tti->start_cfg.first_frame_urgent ? 1 : 1 + (rand() % tti->timer_len);

    JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TICKS(tti_idx),
            VTSS_F_AFI_TTI_TBL_TTI_TICKS_TICK_CNT(rand_tick_cnt),
            VTSS_M_AFI_TTI_TBL_TTI_TICKS_TICK_CNT);

    // Always start down-flows, because a per-port AFI mechanism ensures that
    // flows are not really started until the port gets link.
    // Only start up-flows if there's link on the port. Calls to
    // jr2_afi_link_state_change() ensure that these up-flows are started and
    // stopped by link state changes.
    port_no = tti->port_no != VTSS_PORT_NO_NONE ? tti->port_no : tti->masquerade_port_no;
    link    = tti->port_no != VTSS_PORT_NO_NONE ? TRUE         : jr2_afi_port_tbl_entry(vtss_state, port_no)->link;

    VTSS_I("port_no = %d: link = %d", port_no, link);
    VTSS_RC(jr2_afi_tti_pause_resume(vtss_state, tti_idx, !link));

    // User has started this flow now, even though it may not be started in
    // reality.
    tti->state = VTSS_AFI_ENTRY_STATE_STARTED;

    VTSS_I("Exit. tti_idx = %u, paused = %d", tti_idx, tti->paused);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_tti_stop()
 */
static vtss_rc jr2_afi_tti_stop(vtss_state_t *const vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter. Stopping tti_idx = %u", tti_idx);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STARTED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "DTI not started");
    }

    VTSS_RC(jr2_afi_tti_pause_resume(vtss_state, tti_idx, 1));

    tti->state = VTSS_AFI_ENTRY_STATE_STOPPED;

    VTSS_I("Exit(%u)", tti_idx);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_tti_frm_hijack()
 */
static vtss_rc jr2_afi_tti_frm_hijack(vtss_state_t *const vtss_state, u32 tti_idx)
{
    vtss_rc rc;
    VTSS_I("Enter(%u)", tti_idx);
    rc = jr2_afi_frm_hijack(vtss_state, vtss_state->afi.tti_tbl[tti_idx].frm_idx);
    VTSS_I("Exit(%u)", tti_idx);
    return rc;
}

/*
 * jr2_afi_tti_frm_rm_inj()
 */
static vtss_rc jr2_afi_tti_frm_rm_inj(vtss_state_t *const vtss_state, u32 tti_idx)
{
    vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

    VTSS_I("Enter(%u)", tti_idx);

    if (tti->state != VTSS_AFI_ENTRY_STATE_STOPPED) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "ID = %u: Injection must be stopped before rm injection", tti_idx);
    }

    VTSS_RC(jr2_afi_set_frm_rm(vtss_state, tti->frm_idx));

    // Start removal injection!
    // Set TIMER_LEN to max value (=> inject ASAP)
    JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN((1 << VTSS_AFI_TTI_TBL_TIMER_LEN_WID) - 1),
            VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_LEN);

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    // Make sure timer is started
    JR2_WRM(VTSS_AFI_TTI_TBL_TTI_TIMER(tti_idx),
            VTSS_F_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA(1),
            VTSS_M_AFI_TTI_TBL_TTI_TIMER_TIMER_ENA);
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) */

    // Wait until the frame is gone.
    VTSS_RC(jr2_afi_frm_gone_wait(vtss_state, tti_idx, tti->port_no, tti->frm_idx, FALSE));

    VTSS_I("Exit(%u)", tti_idx);

    return VTSS_RC_OK;
}

/******************************************************************************/
//
// External CIL: Other functions
//
/******************************************************************************/

/*
 * jr2_afi_link_state_change()
 */
static vtss_rc jr2_afi_link_state_change(vtss_state_t *const vtss_state, vtss_port_no_t port_no, BOOL *link_up)
{
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);
    BOOL return_val = port->link;

    VTSS_I("Enter. port_no = %d, current link = %d, new link = %d", port_no, return_val, *link_up);

    if (*link_up) {
        // Re-allow frame injection to this port
        VTSS_RC(jr2_afi_port_link_up(vtss_state, port_no));

        // Start all VD1 flows that utilize this port ingress-wise
        VTSS_RC(jr2_afi_up_flows_pause_resume(vtss_state, port_no, FALSE));
    } else if (port->link) {
        // Stop all VD1 flows that utilize this port ingress-wise
        VTSS_RC(jr2_afi_up_flows_pause_resume(vtss_state, port_no, TRUE));

        // Disable frame injection to this port.
        VTSS_RC(jr2_afi_port_link_down(vtss_state, port_no));
    }

    *link_up = return_val;

    VTSS_I("Exit(port_no = %u)", port_no);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_qu_ref_update()
 */
static vtss_rc jr2_afi_qu_ref_update(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    u32 dti_idx, tti_idx;

    // Injection must already have been stopped on #port_no.

    // Update the queue number for all DTIs egressing #port_no (down-flows)
    for (dti_idx = 0; dti_idx < VTSS_ARRSZ(vtss_state->afi.dti_tbl); dti_idx++) {
        vtss_afi_dti_t *dti = &vtss_state->afi.dti_tbl[dti_idx];

        if (dti->state != VTSS_AFI_ENTRY_STATE_FREE && dti->port_no == port_no) {
            VTSS_RC(jr2_afi_dti_qu_ref_update(vtss_state, dti_idx));
        }
    }

    // Update the queue number for all TTIs egressing #port_no (down-flows)
    for (tti_idx = 0; tti_idx < VTSS_ARRSZ(vtss_state->afi.tti_tbl); tti_idx++) {
        vtss_afi_tti_t *tti = &vtss_state->afi.tti_tbl[tti_idx];

        if (tti->state != VTSS_AFI_ENTRY_STATE_FREE && tti->port_no == port_no) {
            VTSS_RC(jr2_afi_tti_qu_ref_update(vtss_state, tti_idx));
        }
    }

    return VTSS_RC_OK;
}

/*
 * jr2_afi_enable()
 */
static vtss_rc jr2_afi_enable(vtss_state_t *const vtss_state)
{
    VTSS_I("Enter");

#if !defined(VTSS_ARCH_JAGUAR_2_B)
    // Enable AFI first (power saving feature added on ServalT)
    JR2_WRM(VTSS_AFI_MISC_MISC_CTRL,
            VTSS_F_AFI_MISC_MISC_CTRL_AFI_ENA(1),
            VTSS_M_AFI_MISC_MISC_CTRL_AFI_ENA);
#endif /* !defined(VTSS_ARCH_JAGUAR_2_B) */

    VTSS_RC(jr2_afi_tti_cal_init(vtss_state));

    VTSS_I("Exit");

    return VTSS_RC_OK;
}

/*
 * jr2_afi_port_admin_start()
 *
 * Administrative port start
 * Upon init, the ports are in started state.
 */
static vtss_rc jr2_afi_port_admin_start(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    if (port->started) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "Port %u already started", port_no);
    }

    if (port->link) {
        VTSS_RC(jr2_afi_port_start(vtss_state, port_no));
    }

    port->started = 1;

    VTSS_I("Exit. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

/*
 * jr2_afi_port_admin_stop()
 *
 * Administrative port stop
 * Upon init, the ports are in started state.
 */
static vtss_rc jr2_afi_port_admin_stop(vtss_state_t *const vtss_state, vtss_port_no_t port_no)
{
    vtss_afi_port_t *port = jr2_afi_port_tbl_entry(vtss_state, port_no);

    VTSS_I("Enter. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    if (!port->started) {
        JR2_AFI_E_RETURN(VTSS_RC_ERROR, "Port %u not started", port_no);
    }

    // Stop all VD1 flows that utilize this port ingress-wise
    VTSS_RC(jr2_afi_up_flows_pause_resume(vtss_state, port_no, TRUE));

    // Disable frame injection to this port.
    VTSS_RC(jr2_afi_port_stop(vtss_state, port_no));
    port->started = 0;

    VTSS_I("Exit. port = %d, link = %d, started = %d", port_no, port->link, port->started);

    return VTSS_RC_OK;
}

/*
 * vtss_jr2_afi_debug_print()
 */
vtss_rc vtss_jr2_afi_debug_print(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, const vtss_debug_info_t *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_AFI, jr2_afi_debug, vtss_state, pr, info);
}

/*
 * vtss_jr2_afi_init()
 */
vtss_rc vtss_jr2_afi_init(vtss_state_t *const vtss_state, const vtss_init_cmd_t cmd)
{
    vtss_afi_state_t    *state = &vtss_state->afi;
    vtss_port_no_t      port_no;
    vtss_phys_port_no_t chip_port;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        // Assign CIL function pointers
        state->afi_enable        = jr2_afi_enable;
        state->ttis_enable       = jr2_afi_ttis_enable;

        state->tti_start         = jr2_afi_tti_start;
        state->tti_stop          = jr2_afi_tti_stop;
        state->tti_frm_hijack    = jr2_afi_tti_frm_hijack;
        state->tti_frm_rm_inj    = jr2_afi_tti_frm_rm_inj;

        state->dti_start         = jr2_afi_dti_start;
        state->dti_stop          = jr2_afi_dti_stop;
        state->dti_frm_hijack    = jr2_afi_dti_frm_hijack;
        state->dti_frm_rm_inj    = jr2_afi_dti_frm_rm_inj;
        state->dti_cnt_get       = jr2_afi_dti_cnt_get;

        state->port_admin_start  = jr2_afi_port_admin_start;
        state->port_admin_stop   = jr2_afi_port_admin_stop;
        state->link_state_change = jr2_afi_link_state_change;
        state->qu_ref_update     = jr2_afi_qu_ref_update;

        // Initialize ports to started = 1. This corresponds to
        // calling jr2_afi_port_admin_start() during boot.
        for (port_no = 0; port_no < VTSS_ARRSZ(vtss_state->afi.port_tbl); port_no++) {
            vtss_state->afi.port_tbl[port_no].started = 1;
        }
        break;

    case VTSS_INIT_CMD_INIT:
        // The switch core clock period differs from JR2 chip-variant to chip-variant,
        // and we rely heavily on it in this module, so get it.
        VTSS_RC(jr2_afi_clock_period_get(vtss_state));

        // Initialize the tick table
        VTSS_RC(jr2_afi_tti_tick_init(vtss_state));

        // Stop injection on all ports, corresponding to link == 0.
        // Will be started upon link up.
        for (chip_port = 0; chip_port < VTSS_CHIP_PORTS_ALL; chip_port++) {
            VTSS_RC(jr2_afi_chip_port_stop(vtss_state, chip_port));
        }

        break;

    case VTSS_INIT_CMD_PORT_MAP:
        // Now that the port map is set, we can use "port_no".
        // VD1 always has "link up". It is indexed with port_no == VTSS_PORT_NO_NONE
        VTSS_RC(jr2_afi_port_link_up(vtss_state, VTSS_PORT_NO_NONE));
        break;

    case VTSS_INIT_CMD_POLL:
        break;

    default:
        break;
    }

    return VTSS_RC_OK;
}

#endif /* defined(VTSS_AFI_V2) && defined(VTSS_FEATURE_AFI_SWC) && defined(VTSS_ARCH_JAGUAR_2) */

